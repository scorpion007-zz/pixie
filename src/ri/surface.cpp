//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright © 1999 - 2003, Okan Arikan
//
// Contact: okan@cs.utexas.edu
//
//	This library is free software; you can redistribute it and/or
//	modify it under the terms of the GNU Lesser General Public
//	License as published by the Free Software Foundation; either
//	version 2.1 of the License, or (at your option) any later version.
//
//	This library is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//	Lesser General Public License for more details.
//
//	You should have received a copy of the GNU Lesser General Public
//	License along with this library; if not, write to the Free Software
//	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
//
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//
//  File				:	surface.cpp
//  Classes				:	CPatch
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "common/global.h"
#include "common/polynomial.h"
#include "surface.h"
#include "memory.h"
#include "stats.h"
#include "shading.h"
#include "renderer.h"
#include "rendererContext.h"
#include "error.h"
#include "debug.h"


const	int		SPLIT_NONE	=	0;
const	int		SPLIT_U		=	1;
const	int		SPLIT_V		=	2;
const	int		SPLIT_UV	=	3;




///////////////////////////////////////////////////////////////////////
// Function				:	minCocPixels
// Description			:	return the minimum circle of confusion
// Return Value			:
// Comments				:	(inline for speed, needed for CSurface::dice() )
static inline float	minCocPixels(float z1, float z2) {
	return min(cocPixels(z1),cocPixels(z2));
}



///////////////////////////////////////////////////////////////////////
// Class				:	CPatch
// Method				:	CPatch
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CPatch::CPatch(CAttributes *a,CXform *x,CSurface *o,float umin,float umax,float vmin,float vmax,int depth,int minDepth) : CObject(a,x) {
	atomicIncrement(&stats.numGprims);
	atomicIncrement(&stats.numSurfaces);
	if (stats.numSurfaces > stats.numPeakSurfaces)	stats.numPeakSurfaces	=	stats.numSurfaces;

	// Record the stuff
	this->object	=	o;
	this->umin		=	umin;
	this->umax		=	umax;
	this->vmin		=	vmin;
	this->vmax		=	vmax;
	this->depth		=	depth;
	this->minDepth	=	minDepth;
	this->udiv		=	-1;
	this->vdiv		=	-1;
	this->object->attach();	
	movvv(this->bmin,o->bmin);
	movvv(this->bmax,o->bmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPatch
// Method				:	~CPatch
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CPatch::~CPatch() {
	atomicDecrement(&stats.numGprims);
	atomicDecrement(&stats.numSurfaces);

	object->detach();
}


static	inline int	cull(float *bmin,float *bmax,const float *P,const float *N,int k,int doubleSided,int disable) {
	int	i;

	// Update the bounding box
	for (i=k;i>0;i--) {
		addBox(bmin,bmax,P);
		P			+=	3;
	}

	// Check the back face culling
	if (doubleSided == FALSE  && !disable) {
		P	-=	k*3;

		if (CRenderer::projection == OPTIONS_PROJECTION_PERSPECTIVE) {
			for (i=k;i>0;i--) {
				if (dotvv(P,N) < 0)	break;
				N	+=	3;
				P	+=	3;
			}
		} else {
			for (i=k;i>0;i--) {
				if (N[COMP_Z] < 0)	break;
				N	+=	3;
				P	+=	3;
			}
		}

		// The patch is looking away from us
		if (i == 0) {
			return TRUE;
		}
	}

	return FALSE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPatch
// Method				:	dice
// Description			:	Dice the surface into smaller primitives
// Return Value			:	-
// Comments				:
void	CPatch::dice(CShadingContext *r) {

	// Have we checked size of this piece before ?
	if ((udiv == -1) && (vdiv == -1)) {

		int			minDivU,minDivV;
		object->getDicingStats(depth,minDivU,minDivV);

		// No, probe the surface and find the bounding box
		float		*Pmov;
		float		maxBound;
		int			up,vp;
		int			k;
		int			cullFlags	=	TRUE;
		int			moving		=	(CRenderer::flags & OPTIONS_FLAGS_MOTIONBLUR) && (object->moving());
		
		if (moving == TRUE) {
			Pmov	=	(float *) alloca(CRenderer::maxGridSize*3*2*sizeof(float));
		}
		
		// We need to split this patch, so no need to compute udiv / vdiv

		// Get some misc variables for fast access
		const int		disableCull		=	attributes->flags & ATTRIBUTES_FLAGS_SHADE_BACKFACE;
		const int		nonrasterorient	=	attributes->flags & ATTRIBUTES_FLAGS_NONRASTERORIENT_DICE;
		int				numUprobes		=	attributes->numUProbes;
		int				numVprobes		=	attributes->numVProbes;
		float			**varying		=	r->currentShadingState->varying;

		// Estimate the grid size until convergence
		for(int numTries=0;numTries<5;++numTries) {

			// Sample points on the patch
			const double	ustart			=	umin;
			const double	vstart			=	vmin;
			const double	ustep			=	(umax - ustart) / (double) (numUprobes-1);
			const double	vstep			=	(vmax - vstart) / (double) (numVprobes-1);
			double			u,v;

			// If the parametric range is too small, we have to abort
			if (((float) (ustart + ustep)) <= ((float) ustart))	return;
			if (((float) (vstart + vstep)) <= ((float) vstart))	return;

			// The current u/v/time vectors
			float			*uv				=	varying[VARIABLE_U];
			float			*vv				=	varying[VARIABLE_V];
			float			*timev			=	varying[VARIABLE_TIME];

			// Init the bounding box to zero
			initv(bmin,C_INFINITY);
			initv(bmax,-C_INFINITY);

			// Take care of the motion first
			if (moving == TRUE) {

				// Compute the sample positions and corresponding normal vectors
				for (vp=0,v=vstart,k=0;vp<numVprobes;vp++,v+=vstep) {
					for (up=0,u=ustart;up<numUprobes;up++,u+=ustep,k++) {
						uv[k]		=	(float) u;
						vv[k]		=	(float) v;
						timev[k]	=	1;
					}
				}
				
				assert(k <= (int) CRenderer::maxGridSize);
				r->displaceEstimate(object,numUprobes,numVprobes,SHADING_2D_GRID,PARAMETER_P | PARAMETER_N | PARAMETER_END_SAMPLE);
				cullFlags			&=	cull(bmin,bmax,varying[VARIABLE_P],varying[VARIABLE_N],k,attributes->flags & ATTRIBUTES_FLAGS_DOUBLE_SIDED,disableCull);

				// Save the end positions
				assert(numUprobes*numVprobes <= CRenderer::maxGridSize);
				memcpy(Pmov,varying[VARIABLE_P],numUprobes*numVprobes*3*sizeof(float));
			}

			// Compute the sample positions and corresponding normal vectors
			for (vp=0,v=vstart,k=0;vp<numVprobes;vp++,v+=vstep) {
				for (up=0,u=ustart;up<numUprobes;up++,u+=ustep,k++) {
					uv[k]		=	(float) u;
					vv[k]		=	(float) v;
					timev[k]	=	0;
				}
			}
			
			assert(k <= (int) CRenderer::maxGridSize);

// FIXME: correct this
#if 1
			r->displaceEstimate(object,numUprobes,numVprobes,SHADING_2D_GRID,PARAMETER_P | PARAMETER_N | PARAMETER_BEGIN_SAMPLE);
#else
			r->displaceEstimate(object,numUprobes,numVprobes,SHADING_2D_GRID,PARAMETER_P | PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_N | PARAMETER_BEGIN_SAMPLE);


			////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// OK, we sampled the surface but is it accurate enough?
			// To verify it compare the numerical derivative against the analytical one
			// FIXME: We may want to do the centered derivative estimate here


			// Compare the derivatives
			bool		inconsistent	=	false;
			const float	*P				=	varying[VARIABLE_P];
			const float	*dPdu			=	varying[VARIABLE_DPDU];
			for (int i=0;i<numVprobes;++i) {
				const float	*cP			=	P + i*numUprobes*3;
				const float	*cdPdu		=	dPdu + i*numUprobes*3;
				for (int j=numUprobes-1;j>0;--j,cP+=3,cdPdu+=3) {
					vector	D1,D2;
					subvv(D1,cP + 3,cP);
					mulvf(D2,cdPdu,(float) ustep);
					subvv(D2,D1);
					if (dotvv(D2,D2) > 0.25f*dotvv(D1,D1)) {		// More than %50 relative error?
						inconsistent	=	true;
						break;
					}
				}

				if (inconsistent) break;
			}

			// Are we still going?
			if (inconsistent == false) {
				const float	*dPdv			=	varying[VARIABLE_DPDV];
				for (int i=0;i<numUprobes;++i) {
					const float	*cP			=	P + i*3;
					const float	*cdPdv		=	dPdv + i*3;
					const int	step		=	numUprobes*3;
					for (int j=numVprobes-1;j>0;--j,cP+=step,cdPdv+=step) {
						vector	D1,D2;
						subvv(D1,cP + step,cP);
						mulvf(D2,cdPdv,(float) vstep);
						subvv(D2,D1);
						if (dotvv(D2,D2) > 0.25f*dotvv(D1,D1)) {	// More than %50 relative error?
							inconsistent	=	true;
							break;
						}
					}

					if (inconsistent) break;
				}
			}

			// OK, if we're inconsistent, this probe was not accurate enough
			if (inconsistent) {
				// Let's double the probes and re-estimate
				numUprobes	*=	2;
				numVprobes	*=	2;
				continue;
			}

#endif





			cullFlags			&=	cull(bmin,bmax,varying[VARIABLE_P],varying[VARIABLE_N],k,attributes->flags & ATTRIBUTES_FLAGS_DOUBLE_SIDED,disableCull);

//FIXME: implies if either end is culled we cull - wrong
			// Are we culled ?
			if (cullFlags)	return;

			// Expand the bound
			maxBound		=	max(bmax[COMP_X]-bmin[COMP_X],bmax[COMP_Y]-bmin[COMP_Y]);
			maxBound		=	max(bmax[COMP_Z]-bmin[COMP_Z],maxBound);
			maxBound		*=	attributes->rasterExpand;
			if (maxBound == 0)	return;

			bmin[COMP_X]	-=	maxBound;
			bmin[COMP_Y]	-=	maxBound;
			bmin[COMP_Z]	-=	maxBound;
			bmax[COMP_X]	+=	maxBound;
			bmax[COMP_Y]	+=	maxBound;
			bmax[COMP_Z]	+=	maxBound;

			// Account for the displacement on the surface
			subvf(bmin,attributes->maxDisplacement);
			addvf(bmax,attributes->maxDisplacement);

			// Frustrum culling
			if (CRenderer::inFrustrum(bmin,bmax) == FALSE)	return;

			// Can we make the perspective divide ?
			if ((bmin[COMP_Z] > C_EPSILON) && (depth >= minDepth)) {
				
				// Figure out the subdivision we want to make
				float	shadingRate	=	attributes->shadingRate;

				// Correct shading rate with dof factor
				if (CRenderer::flags & OPTIONS_FLAGS_FOCALBLUR) {
					const float coc =	minCocPixels(bmin[COMP_Z],bmax[COMP_Z]);
					shadingRate		*=	max(1,0.5f*coc);
				}
				
				// Optionally correct shading rate with motionfactor
				if ((CRenderer::flags & OPTIONS_FLAGS_MOTIONBLUR) && (object->moving())) {

					// Project the vertices
					memcpy(Pmov + numUprobes*numVprobes*3,varying[VARIABLE_P],numUprobes*numVprobes*3*sizeof(float));
					camera2pixels(numUprobes*numVprobes*2,Pmov);

					// Compute the amount of motion on the screen
					float		blurDistance	=	0;
					const float	*P				=	Pmov + numUprobes*numVprobes*3;
					for (int i=numUprobes*numVprobes;i>0;i--,Pmov+=3,P+=3) {
						vector	D;
						subvv(D,Pmov,P);
						blurDistance		+=	sqrtf(D[0]*D[0] + D[1]*D[1]);
					}
					Pmov						-=	numUprobes*numVprobes*3;

					// Update the shading rate accordingly
					shadingRate += attributes->motionFactor*shadingRate*blurDistance / (float) (numUprobes*numVprobes);
				}
				
				// Estimate the grid size
				estimateDicing(varying[VARIABLE_P],numUprobes-1,numVprobes-1,udiv,vdiv,shadingRate,nonrasterorient);

			} else {

				// Are we making too many splits ?
				if (depth >= CRenderer::maxEyeSplits) {
					warning(CODE_SYSTEM,"Too many eye splits for primitive \"%s\"\n",attributes->name);
					return;
				}

				// We can not make the perspective divide, so make sure we split into 4 next time
				udiv	=	0;
				break;
			}

			// clamp to the surface dice stats
			udiv = max(minDivU,udiv);
			vdiv = max(minDivV,vdiv);

			// Check the size ... If we're too big, we should be split
			if ((udiv+1)*(vdiv+1) > CRenderer::maxGridSize)	{
				break;
			}

			// Did we converge ?
			if ((numUprobes == (udiv+1)) && (numVprobes == (vdiv+1))) {

				// FIXME: If the grid is close to the bucket we're rendering, we must dispatch now
				// GSH: the disadvantage of doing this is that we will retain a higher cost grid
				// even if it would get totally culled
				
				break;
			}
			
			// Go again
			numUprobes	=	udiv+1;
			numVprobes	=	vdiv+1;
		}

		// Finally record the surface with the rasterizer
		r->drawObject(this);

	} else {
		if (udiv == 0) {
			// We're spanning the eye plane
			splitToChildren(r,2);
		} else if (((udiv+1)*(vdiv+1)) > CRenderer::maxGridSize) {
			// We're too big, split the surface further
			if (udiv == vdiv) {
				splitToChildren(r,2);
			} else if (udiv > vdiv) {
				splitToChildren(r,0);
			} else {
				splitToChildren(r,1);
			}
		} else {
			// We're small enough, just dispatch the grid
			r->drawGrid(object,udiv,vdiv,umin,umax,vmin,vmax);
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPatch
// Method				:	split
// Description			:	Split the surface into smaller ones
// Return Value			:	-
// Comments				:
void	CPatch::splitToChildren(CShadingContext *r,int dir) {
	CPatch	*p1,*p2,*p3,*p4;
	float	umid,vmid;

	switch(dir) {
	case 0:
		if (umax <= umin)	break;

		// Split along one direction
		umid			=	(umin + umax)*0.5f;
		p1				=	new CPatch(attributes,xform,object,umin,umid,vmin,vmax,depth+1,minDepth);
		p2				=	new CPatch(attributes,xform,object,umid,umax,vmin,vmax,depth+1,minDepth);
		p1->attach();
		p2->attach();

		p1->dice(r);
		p2->dice(r);

		p1->detach();
		p2->detach();
		stats.numSplits++;
		stats.numUsplits++;
		break;
	case 1:
		if (vmax <= vmin)	break;

		// Split along one direction
		vmid			=	(vmin + vmax)*0.5f;
		p1				=	new CPatch(attributes,xform,object,umin,umax,vmin,vmid,depth+1,minDepth);	
		p2				=	new CPatch(attributes,xform,object,umin,umax,vmid,vmax,depth+1,minDepth);	
		p1->attach();
		p2->attach();

		p1->dice(r);
		p2->dice(r);

		p1->detach();
		p2->detach();
		stats.numSplits++;
		stats.numVsplits++;
		break;
	case 2:
		if (vmax <= vmin)	break;
		if (umax <= umin)	break;

		// Split along one direction
		vmid			=	(vmin + vmax)*0.5f;
		umid			=	(umin + umax)*0.5f;
		p1				=	new CPatch(attributes,xform,object,umin,umid,vmin,vmid,depth+1,minDepth);
		p2				=	new CPatch(attributes,xform,object,umid,umax,vmin,vmid,depth+1,minDepth);
		p3				=	new CPatch(attributes,xform,object,umin,umid,vmid,vmax,depth+1,minDepth);
		p4				=	new CPatch(attributes,xform,object,umid,umax,vmid,vmax,depth+1,minDepth);
		p1->attach();
		p2->attach();
		p3->attach();
		p4->attach();

		p1->dice(r);
		p2->dice(r);
		p3->dice(r);
		p4->dice(r);

		p1->detach();
		p2->detach();
		p3->detach();
		p4->detach();
		stats.numSplits++;
		stats.numUVsplits++;

		break;
	}
}









//////////////////////////////////////////////
///
///	On-Demand Tesselation Implementation
///
/////////////////////////////////////////////


// FIXMES:
// remove or support minDepth / maxDepth usage (reinstate splits attributes)
//	- careful because we us r tests to bail from higher tesselations
// remove udiv,vdiv and hardcode the divisions?

//#define DEBUG_STATS 20
//#define DEBUG_HITS
#define DEBUG_TESSELATIONS 0


int					*CTesselationPatch::lastRefNumbers[TESSELATION_NUM_LEVELS];
int					*CTesselationPatch::tesselationUsedMemory[TESSELATION_NUM_LEVELS];
int					CTesselationPatch::tesselationMaxMemory[TESSELATION_NUM_LEVELS];
CTesselationPatch	*CTesselationPatch::tesselationList;


#ifdef DEBUG_STATS
static int tessPerLevel[DEBUG_STATS*TESSELATION_NUM_LEVELS];
static int tessPerDepth[DEBUG_STATS];
#endif

///////////////////////////////////////////////////////////////////////
// Class				:	CTesselationPatch
// Method				:	CTesselationPatch
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CTesselationPatch::CTesselationPatch(CAttributes *a,CXform *x,CSurface *o,float umin,float umax,float vmin,float vmax,char depth,char minDepth,float r) : CObject(a,x) {
	// Work out whether we're moving and mark us as a tesselation
	this->flags		|=	OBJECT_TESSELATION;
	if (o->moving()) 
		this->flags |= OBJECT_MOVING_TESSELATION;
	
	// Statistics
	stats.tesselationOverhead += sizeof(CTesselationPatch) + sizeof(int)*CRenderer::numThreads;
	
	// Record the stuff
	this->object	=	o;
	this->umin		=	umin;
	this->umax		=	umax;
	this->vmin		=	vmin;
	this->vmax		=	vmax;
	this->depth		=	depth;
	this->minDepth	=	minDepth;
	movvv(this->bmin,o->bmin);
	movvv(this->bmax,o->bmax);
	
	// Initialize each subtesselation
	for (int i=0;i<TESSELATION_NUM_LEVELS; i++) {
		CPurgableTesselation **cTess		=	new CPurgableTesselation*[CRenderer::numThreads];
		for (int j=0;j<CRenderer::numThreads; j++) {
			cTess[j]	=	NULL;
		}
		
		levels[i].threadTesselation	=	cTess;
	}
	
	// Maintain the linked list
	prev						=	NULL;
	next						=	tesselationList;
	if (tesselationList != NULL)
		tesselationList->prev	=	this;
	tesselationList				=	this;
	
	// Set the initial guess for the grid size
	this->rmax					=	r;
	
	#ifdef DEBUG_STATS
	tessPerDepth[depth]++;
	#endif
}


///////////////////////////////////////////////////////////////////////
// Class				:	CTesselationPatch
// Method				:	~CTesselationPatch
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CTesselationPatch::~CTesselationPatch() {
	// Maintain the linked list
	if (next != NULL)	next->prev						=	prev;
	if (prev != NULL)	prev->next						=	next;
	else				tesselationList					=	next;

	// clean up tesselations
	for(int i=0;i<TESSELATION_NUM_LEVELS;i++) {
		for (int j=0;j<CRenderer::numThreads; j++) {
			if (levels[i].threadTesselation[j] != NULL) {
				stats.tesselationMemory -= levels[i].threadTesselation[j]->size;
				free_untyped(levels[i].threadTesselation[j]);
			}
		}
		delete[] levels[i].threadTesselation;
	}
	
	// Statistics
	// Note: it has been verified that this returns to 0, but
	// it's more useful for stats reporting that it can be seen in end of frame
	//stats.tesselationOverhead -= sizeof(CTesselationPatch) + sizeof(int)*CRenderer::numThreads;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CTesselationPatch
// Method				:	intersect
// Description			:	intersect a ray with a tesselation patch
// Return Value			:	-
// Comments				:
void	CTesselationPatch::intersect(CShadingContext *context,CRay *cRay) {
	// Check the ray conditions before proceeding
	
	if (! (cRay->flags & attributes->flags) )	return;

	if (attributes->flags & ATTRIBUTES_FLAGS_LOD) {
		const float importance = attributes->lodImportance;
		if (importance >= 0) {
			if (cRay->jimp > importance)			return;
		} else {
			if ((1-cRay->jimp) >= -importance)		return;
		}
	}
	
	// Intersect with our bounding box
	float t = nearestBox(bmin,bmax,cRay->from,cRay->invDir,cRay->tmin,cRay->t);
	
	// Bail out if the hit point is already further than the ray got
	if (!(t < cRay->t)) return;
	
	// Calculate the required tesselation
	float requiredR = cRay->da * t + cRay->db;
	
	// Bail very early if this ray should have been handled by a coarser tesselation
	if (rmax*2.0f < requiredR && depth > 0) {
		// do not proceed further
		return;
	}

	// We must find the appropriate tesselation level
	float	rCur		=	rmax;
	int		div			=	1;
	int		level		=	0;
	int		subsample	=	FALSE;
	for (level=0;level<TESSELATION_NUM_LEVELS;level++) {
		if (rCur < requiredR+C_EPSILON) {
			break;
		}
		rCur	*=	0.25;
		div		=	div<<2;
	}
	//rCur = rmax/(float)div;
	
	// Decide whether to subsample
	if (rCur*2.0f < requiredR+C_EPSILON) {
		rCur		*=	2.0f;
		subsample	=	TRUE;
	}

	if((flags & OBJECT_TERMINAL_TESSELATION) && (level >= TESSELATION_NUM_LEVELS)) {
		// If this tesselation is marked as final then clamp the level
		// See below (for non-displaced raytracing)
		level = TESSELATION_NUM_LEVELS-1;
		div = 16;
		rCur = rmax/16;
	}

	// Did we find a tesselation in this tesselationPatch?
	if (level < TESSELATION_NUM_LEVELS) {
		// Yes, our r is sufficient
		
		const int thread = context->thread;
		
		
		// Verify we have a tesselation
		if (levels[level].threadTesselation[thread] == NULL) {
			// No, we must get one, lock first
			
			#ifdef DEBUG_STATS
			tessPerLevel[depth*3+level]++;
			#endif
			
			// Create the tesselation
			levels[level].threadTesselation[thread]				=	tesselate(context,div,FALSE);
			
			// Restore the refCount
			levels[level].threadTesselation[thread]->lastRefNumber	=	lastRefNumbers[level][thread];
			
			/// FIXME make these context stats
			// Update stats
			stats.tesselationMemory								+=	levels[level].threadTesselation[thread]->size;
			if (stats.tesselationPeakMemory < stats.tesselationMemory) {
				stats.tesselationPeakMemory = stats.tesselationMemory;
			}
			// Update stats
			atomicIncrement(&stats.tesselationCacheMisses);
						
			tesselationUsedMemory[level][thread] 				+=	levels[level].threadTesselation[thread]->size;
			
			// Purge if we exceeded the max memory for this thread
			if (tesselationUsedMemory[level][thread] > tesselationMaxMemory[level]) {
				purgeTesselations(context,this,thread,level,FALSE);
			}
		} else {
			/// FIXME make these context stats
			// Update stats
			atomicIncrement(&stats.tesselationCacheHits);
		}
		
		// Bump the tesselation refCount
		lastRefNumbers[level][thread]++;
		levels[level].threadTesselation[thread]->lastRefNumber	=	lastRefNumbers[level][thread];
		
		// Grab the threadTesselation and use from now on
		CPurgableTesselation *thisTesselation	=	levels[level].threadTesselation[thread];
		
		
		
		// Intersect the ray
		
		#ifdef DEBUG_HITS
			#define debugHit()														\
										CDebugView	d("/tmp/tesselate.dat",TRUE);	\
										vector p;									\
										mulvf(p,cRay->dir,cRay->t);					\
										addvv(p,cRay->from);						\
										d.point(p);
		#else
			#define debugHit()
		#endif
	
		#define solve()															\
				if ((v > 0) && (v < 1)) {										\
					{															\
						const double	a	=	v*A2 + B2;						\
						const double	b	=	v*(A2 - A1) + B2 - B1;			\
						if (b*b >= a*a)	u	=	(v*(C1 - C2) + D1 - D2) / b;	\
						else			u	=	(-v*C2 - D2) / a;				\
					}															\
																				\
					if ((u > 0) && (u < 1)) {									\
						double	P[3];											\
																				\
						P[0]	=	a[0]*u*v + b[0]*u + c[0]*v + d[0];			\
						P[1]	=	a[1]*u*v + b[1]*u + c[1]*v + d[1];			\
						P[2]	=	a[2]*u*v + b[2]*u + c[2]*v + d[2];			\
																				\
						if ((q[COMP_X]*q[COMP_X] >= q[COMP_Y]*q[COMP_Y]) && (q[COMP_X]*q[COMP_X] >= q[COMP_Z]*q[COMP_Z]))	\
							t	=	(P[COMP_X] - r[COMP_X]) * iq[COMP_X];		\
						else if (q[COMP_Y]*q[COMP_Y] >= q[COMP_Z]*q[COMP_Z])	\
							t	=	(float) ((P[COMP_Y] - r[COMP_Y]) * iq[COMP_Y]);		\
						else													\
							t	=	(float) ((P[COMP_Z] - r[COMP_Z]) * iq[COMP_Z]);		\
																				\
						if ((t > cRay->tmin) && (t < cRay->t)) {				\
							vector	dPdu,dPdv,N;								\
							vector	tmp1,tmp2;									\
							subvv(tmp1,P10,P00);								\
							subvv(tmp2,P11,P01);								\
							interpolatev(dPdu,tmp1,tmp2,(float) v);				\
							subvv(tmp1,P01,P00);								\
							subvv(tmp2,P11,P10);								\
							interpolatev(dPdv,tmp1,tmp2,(float) u);				\
							crossvv(N,dPdu,dPdv);								\
							if ((attributes->flags & ATTRIBUTES_FLAGS_INSIDE) ^ xform->flip) mulvf(N,-1);	\
							if (attributes->flags & ATTRIBUTES_FLAGS_DOUBLE_SIDED) {						\
								cRay->object	=	object;						\
								cRay->u			=	umin + ((float) u + i)*urg;	\
								cRay->v			=	vmin + ((float) v + j)*vrg;	\
								cRay->t			=	(float) t;					\
								movvv(cRay->N,N);								\
								debugHit();										\
							} else {											\
								if (dotvv(q,N) < 0) {							\
									cRay->object	=	object;					\
									cRay->u			=	umin + ((float) u + i)*urg;	\
									cRay->v			=	vmin + ((float) v + j)*vrg;	\
									cRay->t			=	(float) t;					\
									movvv(cRay->N,N);								\
									debugHit();										\
								}												\
							}													\
						}														\
					}															\
				}

				/*
				Note: 
				
				initv(NN,
					-2.0f*( (P01[COMP_Z] - P10[COMP_Z])*(P00[COMP_Y] - P11[COMP_Y])	
						   -(P01[COMP_Y] - P10[COMP_Y])*(P00[COMP_Z] - P11[COMP_Z])),
					-2.0f*(-(P01[COMP_Z] - P10[COMP_Z])*(P00[COMP_X] - P11[COMP_X])
						   +(P01[COMP_X] - P10[COMP_X])*(P00[COMP_Z] - P11[COMP_Z])),
					-2.0f*( (P01[COMP_Y] - P10[COMP_Y])*(P00[COMP_X] - P11[COMP_X])
						   -(P01[COMP_X] - P10[COMP_X])*(P00[COMP_Y] - P11[COMP_Y])));
				
				equivalent to individual cross products and sums
				*/


		#define intersectQuadsBilin()											\
				vector		a,b,c,d;											\
																				\
				subvv(a,P11,P10);												\
				subvv(a,P01);													\
				addvv(a,P00);													\
				subvv(b,P10,P00);												\
				subvv(c,P01,P00);												\
				movvv(d,P00);													\
																				\
				const double	A1	=	a[COMP_X]*q[COMP_Z] - a[COMP_Z]*q[COMP_X];											\
				const double	B1	=	b[COMP_X]*q[COMP_Z] - b[COMP_Z]*q[COMP_X];											\
				const double	C1	=	c[COMP_X]*q[COMP_Z] - c[COMP_Z]*q[COMP_X];											\
				const double	D1	=	(d[COMP_X] - r[COMP_X])*q[COMP_Z] - (d[COMP_Z] - r[COMP_Z])*q[COMP_X];				\
				const double	A2	=	a[COMP_Y]*q[COMP_Z] - a[COMP_Z]*q[COMP_Y];											\
				const double	B2	=	b[COMP_Y]*q[COMP_Z] - b[COMP_Z]*q[COMP_Y];											\
				const double	C2	=	c[COMP_Y]*q[COMP_Z] - c[COMP_Z]*q[COMP_Y];											\
				const double	D2	=	(d[COMP_Y] - r[COMP_Y])*q[COMP_Z] - (d[COMP_Z] - r[COMP_Z])*q[COMP_Y];				\
																															\
				double			roots[2];																					\
				double			u,v,t;																						\
				switch (solveQuadric<double>(A2*C1 - A1*C2,A2*D1 - A1*D2 + B2*C1 - B1*C2,B2*D1 - B1*D2,roots)) {			\
					case 0:														\
						break;													\
					case 1:														\
						v	=	roots[0];										\
						solve();												\
						break;													\
					case 2:														\
						v	=	roots[0];										\
						solve();												\
						v	=	roots[1];										\
						solve();												\
						break;													\
				}
								
			#define intersectQuadsFlat()										\
				vector NN,tmp1,tmp2;											\
				subvv(tmp1,P01,P00);											\
				subvv(tmp2,P10,P00);											\
				crossvv(NN,tmp2,tmp1);											\
				float th = dotvv(q,NN);											\
				if (th != 0) {													\
					const float d = dotvv(NN,P00);								\
					const float ha = th = dotvv(q,NN);							\
					th = (d - dotvv(r,NN)) / th;								\
					if ((th > cRay->tmin) && (th < cRay->t)) {					\
						float atop,aright,abottom,aleft;						\
						int hit = FALSE;										\
						vector hp;												\
																				\
						mulvf(hp,q,th);											\
						addvv(hp,r);											\
																				\
						int majorAxis	=	COMP_X;								\
						if (fabs(NN[COMP_Y]) > fabs(NN[COMP_X]))	majorAxis	=	COMP_Y;		\
						if (fabs(NN[COMP_Z]) > fabs(NN[majorAxis]))	majorAxis	=	COMP_Z;		\
																				\
						switch(majorAxis) {										\
							case COMP_X:										\
								if ((NN[COMP_X]<0.0f))							\
									hit = 		((atop		= area(hp[COMP_Y],hp[COMP_Z],P00[COMP_Y],P00[COMP_Z],P10[COMP_Y],P10[COMP_Z])) < 0.0f)	\
											&&	((aright	= area(hp[COMP_Y],hp[COMP_Z],P10[COMP_Y],P10[COMP_Z],P11[COMP_Y],P11[COMP_Z])) < 0.0f)	\
											&&	((abottom	= area(hp[COMP_Y],hp[COMP_Z],P11[COMP_Y],P11[COMP_Z],P01[COMP_Y],P01[COMP_Z])) < 0.0f)	\
											&&	((aleft		= area(hp[COMP_Y],hp[COMP_Z],P01[COMP_Y],P01[COMP_Z],P00[COMP_Y],P00[COMP_Z])) < 0.0f);\
								else											\
									hit = 		((atop		= area(hp[COMP_Y],hp[COMP_Z],P00[COMP_Y],P00[COMP_Z],P10[COMP_Y],P10[COMP_Z])) > 0.0f)	\
											&&	((aright	= area(hp[COMP_Y],hp[COMP_Z],P10[COMP_Y],P10[COMP_Z],P11[COMP_Y],P11[COMP_Z])) > 0.0f)	\
											&&	((abottom	= area(hp[COMP_Y],hp[COMP_Z],P11[COMP_Y],P11[COMP_Z],P01[COMP_Y],P01[COMP_Z])) > 0.0f)	\
											&&	((aleft		= area(hp[COMP_Y],hp[COMP_Z],P01[COMP_Y],P01[COMP_Z],P00[COMP_Y],P00[COMP_Z])) > 0.0f);\
								break;											\
							case COMP_Y:										\
								if (NN[COMP_Y]<0.0f)							\
									hit	=		 ((atop		= area(hp[COMP_Z],hp[COMP_X],P00[COMP_Z],P00[COMP_X],P10[COMP_Z],P10[COMP_X])) < 0.0f)	\
											&&	 ((aright	= area(hp[COMP_Z],hp[COMP_X],P10[COMP_Z],P10[COMP_X],P11[COMP_Z],P11[COMP_X])) < 0.0f)	\
											&&	 ((abottom	= area(hp[COMP_Z],hp[COMP_X],P11[COMP_Z],P11[COMP_X],P01[COMP_Z],P01[COMP_X])) < 0.0f)	\
											&&	 ((aleft	= area(hp[COMP_Z],hp[COMP_X],P01[COMP_Z],P01[COMP_X],P00[COMP_Z],P00[COMP_X])) < 0.0f);\
								else											\
									hit	=		 ((atop		= area(hp[COMP_Z],hp[COMP_X],P00[COMP_Z],P00[COMP_X],P10[COMP_Z],P10[COMP_X])) > 0.0f)	\
											&&	 ((aright	= area(hp[COMP_Z],hp[COMP_X],P10[COMP_Z],P10[COMP_X],P11[COMP_Z],P11[COMP_X])) > 0.0f)	\
											&&	 ((abottom	= area(hp[COMP_Z],hp[COMP_X],P11[COMP_Z],P11[COMP_X],P01[COMP_Z],P01[COMP_X])) > 0.0f)	\
											&&	 ((aleft	= area(hp[COMP_Z],hp[COMP_X],P01[COMP_Z],P01[COMP_X],P00[COMP_Z],P00[COMP_X])) > 0.0f);\
								break;											\
							case COMP_Z:										\
								if (NN[COMP_Z]<0.0f)							\
									hit = 		((atop		= area(hp[COMP_X],hp[COMP_Y],P00[COMP_X],P00[COMP_Y],P10[COMP_X],P10[COMP_Y])) < 0.0f)	\
											&&	((aright	= area(hp[COMP_X],hp[COMP_Y],P10[COMP_X],P10[COMP_Y],P11[COMP_X],P11[COMP_Y])) < 0.0f)	\
											&&	((abottom	= area(hp[COMP_X],hp[COMP_Y],P11[COMP_X],P11[COMP_Y],P01[COMP_X],P01[COMP_Y])) < 0.0f)	\
											&&	((aleft		= area(hp[COMP_X],hp[COMP_Y],P01[COMP_X],P01[COMP_Y],P00[COMP_X],P00[COMP_Y])) < 0.0f);\
								else											\
									hit = 		((atop		= area(hp[COMP_X],hp[COMP_Y],P00[COMP_X],P00[COMP_Y],P10[COMP_X],P10[COMP_Y])) > 0.0f)	\
											&&	((aright	= area(hp[COMP_X],hp[COMP_Y],P10[COMP_X],P10[COMP_Y],P11[COMP_X],P11[COMP_Y])) > 0.0f)	\
											&&	((abottom	= area(hp[COMP_X],hp[COMP_Y],P11[COMP_X],P11[COMP_Y],P01[COMP_X],P01[COMP_Y])) > 0.0f)	\
											&&	((aleft		= area(hp[COMP_X],hp[COMP_Y],P01[COMP_X],P01[COMP_Y],P00[COMP_X],P00[COMP_Y])) > 0.0f);\
								break;											\
						}														\
						if (hit) {												\
							const float u	=	aleft / (aleft + aright);		\
							const float v	=	atop / (atop + abottom);		\
							if ((u>0.0f) && (u<1.0f) && (v>0.0f) && (v<1.0f)) {	\
								t = th;											\
								if ((attributes->flags & ATTRIBUTES_FLAGS_INSIDE) ^ xform->flip) mulvf(NN,-1); 	\
								if (attributes->flags & ATTRIBUTES_FLAGS_DOUBLE_SIDED) {		\
									cRay->object	=	object;									\
									cRay->u			=	umin + ((float) u + i)*urg;				\
									cRay->v			=	vmin + ((float) v + j)*vrg;				\
									cRay->t			=	(float) t;				\
									movvv(cRay->N,NN);							\
								} else {										\
									if (dotvv(q,NN) < 0.0f) {					\
										cRay->object	=	object;				\
										cRay->u			=	umin + ((float) u + i)*urg;			\
										cRay->v			=	vmin + ((float) v + j)*vrg;			\
										cRay->t			=	(float) t;							\
										movvv(cRay->N,NN);						\
									}											\
								}												\
							}													\
						}														\
					}															\
				}
			
			#define intersectQuads()	\
				intersectQuadsBilin()
				
				//intersectQuadsFlat()
				//intersectQuadsBilin()
		
		// Common ray properties
		const float	*r		=	cRay->from;
		const float	*q		=	cRay->dir;
		const double*iq		=	cRay->invDir;

		// We treat moving patches differently
		if (!(flags & OBJECT_MOVING_TESSELATION)) {
		
			// No motion
			if (div == 1) {
				// 1x1			
				const float	*P00	=	thisTesselation->P;
				const float	*P10	=	P00+3;
				const float	*P01	=	P00+6;
				const float	*P11	=	P00+9;
				
				const float urg		=	(umax - umin);
				const float vrg		=	(vmax - vmin);
			
				const int i = 0;
				const int j = 0;
				
				intersectQuads();
				return;
				
			} else if (div <= 4) {
				if (subsample) {
					// downsample 4x4 to 2x2 (not the same as above because we divided
					// in the parametric space here we quads intersect directly
					
					const float urg		=	2.0f*(umax - umin) / (float) div;
					const float vrg		=	2.0f*(vmax - vmin) / (float) div;
					
					const int nb = div>>1;
					
					const float	*cP		=	thisTesselation->P;
					
					for (int j=0;j<nb;j++) {
						for (int i=0;i<nb;i++,cP+=6) {
							const float	*P00	=	cP;
							const float	*P10	=	cP+6;
							const float	*P01	=	cP+(div+1)*6;
							const float	*P11	=	cP+(div+1)*6+6;
			
							intersectQuads();
						}
						cP += (div+1)*3 +3;
					}
				} else {
					// 2x2 or 4x4 quads intersect directly
										
					const float urg		=	(umax - umin) / (float) div;
					const float vrg		=	(vmax - vmin) / (float) div;
					
					const float	*cP		=	thisTesselation->P;
			
					for (int j=0;j<div;j++) {
						for (int i=0;i<div;i++,cP+=3) {
							const float	*P00	=	cP;
							const float	*P10	=	cP+3;
							const float	*P01	=	cP+(div+1)*3;
							const float	*P11	=	cP+(div+1)*3+3;
			
							intersectQuads();
						}
						cP += 3;
					}
				}
				return;
			} else {
				if (subsample) {
					// downsample 8x8 to 4x4 or 16x16 to 8x8
					// 8x8 or 16x16 quads (or greater if 3*maxGridSize allows)
					// we bound-intersect each 2x2 subgrid before intersecting quads
										
					const float urg		=	2.0f*(umax - umin) / (float) div;
					const float vrg		=	2.0f*(vmax - vmin) / (float) div;
					
					const int nb		=	div>>2;
					
					const float	*P		=	thisTesselation->P;
					const float	*cB		=	P+(div+1)*(div+1)*3;
					
					for (int y=0;y<nb;y++) {
						for (int x=0;x<nb;x++,cB+=6) {
							
							float tmin = cRay->tmin;
							float tmax = cRay->t;
							if (!intersectBox(cB,cB+3,cRay->from,cRay->dir,cRay->invDir,tmin,tmax)) {	// TODO: pull out ray t etc to shadows
								continue;
							}
							
							const float	*cP	=	P + (x*4 + y*4*(div+1))*3;
			
							for (int cj=0;cj<2;cj++) {
								for (int ci=0;ci<2;ci++,cP+=6) {
									const float	*P00	=	cP;
									const float	*P10	=	cP+6;
									const float	*P01	=	cP+(div+1)*6;
									const float	*P11	=	cP+(div+1)*6 + 6;
					
									const int i = x*2+ci;
									const int j	= y*2+cj;
									
									intersectQuads();
								}
								cP += (div+1)*3 + (div-4+1)*3;
							}
						}
					}
				} else {
					// 8x8 or 16x16 quads (or greater if 3*maxGridSize allows)
					// we bound-intersect each 4x4 subgrid before intersecting quads
										
					const float urg		=	(umax - umin) / (float) div;
					const float vrg		=	(vmax - vmin) / (float) div;
			
					const int nb		=	div>>2;
								
					const float	*P		=	thisTesselation->P;
					const float	*cB		=	P+(div+1)*(div+1)*3;
					
					for (int y=0;y<nb;y++) {
						for (int x=0;x<nb;x++,cB+=6) {
							
							float tmin = cRay->tmin;
							float tmax = cRay->t;
							if (!intersectBox(cB,cB+3,cRay->from,cRay->dir,cRay->invDir,tmin,tmax)) {	// TODO: pull out ray t etc to shadows
								continue;
							}
							
							const float	*cP	=	P + (x*4 + y*4*(div+1))*3;
			
							for (int cj=0;cj<4;cj++) {
								for (int ci=0;ci<4;ci++,cP += 3) {
									const float	*P00	=	cP;
									const float	*P10	=	cP+3;
									const float	*P01	=	cP+(div+1)*3;
									const float	*P11	=	cP+(div+1)*3 + 3;
					
									const int i = x*4+ci;
									const int j	= y*4+cj;
									
									intersectQuads();
								}
								cP += (div-4+1)*3;
							}
						}
					}
		
				}
			}
		} else {
		
			// We're moving
			
			const float timev = cRay->time;
			
			vector P00,P10,P01,P11;
			
			if (div == 1) {
				const float	*Pt0	=	thisTesselation->P;
				const float	*Pt1	=	Pt0 + 4*3;
				
				interpolatev(P00,Pt0,  Pt1,  timev);
				interpolatev(P10,Pt0+3,Pt1+3,timev);
				interpolatev(P01,Pt0+6,Pt1+6,timev);
				interpolatev(P11,Pt0+9,Pt1+9,timev);
								
				const float urg		=	(umax - umin);
				const float vrg		=	(vmax - vmin);
			
				const int i = 0;
				const int j = 0;
				
				intersectQuads();
				return;
				
			} else if (div <= 4) {				
				if (subsample) {
					// downsample 4x4 to 2x2 (not the same as above because we divided
					// in the parametric space here we quads intersect directly
					
					const float urg		=	2.0f*(umax - umin) / (float) div;
					const float vrg		=	2.0f*(vmax - vmin) / (float) div;
										
					const int nb		=	div>>1;
					
					const float	*cP0	=	thisTesselation->P;
					const float	*cP1	=	cP0 + (div+1)*(div+1)*3;
					
					for (int j=0;j<nb;j++) {
						for (int i=0;i<nb;i++,cP0+=6,cP1+=6) {
							interpolatev(P00,	cP0,				cP1,			timev);
							interpolatev(P10,	cP0+6,				cP1+6,			timev);
							interpolatev(P01,	cP0+(div+1)*6,		cP1+(div+1)*6,	timev);
							interpolatev(P11,	cP0+(div+1)*6+6,	cP1+(div+1)*6+6,timev);
			
							intersectQuads();
						}
						cP0 += (div+1)*3 +3;
						cP1 += (div+1)*3 +3;
					}
				} else {
					// 2x2 or 4x4 quads intersect directly
					
					const float urg		=	(umax - umin) / (float) div;
					const float vrg		=	(vmax - vmin) / (float) div;
					
					const float	*cP0	=	thisTesselation->P;
					const float	*cP1	=	cP0 + (div+1)*(div+1)*3;
			
					for (int j=0;j<div;j++) {
						for (int i=0;i<div;i++,cP0+=3,cP1+=3) {
							interpolatev(P00,	cP0,				cP1,			timev);
							interpolatev(P10,	cP0+3,				cP1+3,			timev);
							interpolatev(P01,	cP0+(div+1)*3,		cP1+(div+1)*3,	timev);
							interpolatev(P11,	cP0+(div+1)*3+3,	cP1+(div+1)*3+3,timev);
			
							intersectQuads();
						}
						cP0 += 3;
						cP1 += 3;
					}
				}
				return;
			} else {
				if (subsample) {
					// downsample 8x8 to 4x4 or 16x16 to 8x8
					// 8x8 or 16x16 quads (or greater if 3*maxGridSize allows)
					// we bound-intersect each 2x2 subgrid before intersecting quads
					
					const float urg		=	2.0f*(umax - umin) / (float) div;
					const float vrg		=	2.0f*(vmax - vmin) / (float) div;
			
					const int nb		=	div>>2;
					
					const float	*Pt0	=	thisTesselation->P;
					const float	*Pt1	=	Pt0+(div+1)*(div+1)*3;
					const float	*cB		=	Pt1+(div+1)*(div+1)*3;
					
					for (int y=0;y<nb;y++) {
						for (int x=0;x<nb;x++,cB += 6) {
							
							float tmin = cRay->tmin;
							float tmax = cRay->t;
							if (!intersectBox(cB,cB+3,cRay->from,cRay->dir,cRay->invDir,tmin,tmax)) {	// TODO: pull out ray t etc to shadows
								continue;
							}
							
							const float	*cP0	=	Pt0 + (x*4 + y*4*(div+1))*3;
							const float	*cP1	=	Pt1 + (x*4 + y*4*(div+1))*3;

							for (int cj=0;cj<2;cj++) {
								for (int ci=0;ci<2;ci++,cP0+=6,cP1+=6) {
									interpolatev(P00,	cP0,				cP1,				timev);
									interpolatev(P10,	cP0+6,				cP1+6,				timev);
									interpolatev(P01,	cP0+(div+1)*6,		cP1+(div+1)*6,		timev);
									interpolatev(P11,	cP0+(div+1)*6 + 6,	cP1+(div+1)*6 + 6,	timev);
					
									const int i = x*2+ci;
									const int j	= y*2+cj;
									
									intersectQuads();
								}
								cP0 += (div+1)*3 + (div-4+1)*3;
								cP1 += (div+1)*3 + (div-4+1)*3;
							}
						}
					}
				} else {
					// 8x8 or 16x16 quads (or greater if 3*maxGridSize allows)
					// we bound-intersect each 4x4 subgrid before intersecting quads
					
					const float urg		=	(umax - umin) / (float) div;
					const float vrg		=	(vmax - vmin) / (float) div;
					
					const int nb		=	div>>2;
					
					const float	*Pt0	=	thisTesselation->P;
					const float	*Pt1	=	Pt0+(div+1)*(div+1)*3;
					const float	*cB		=	Pt1+(div+1)*(div+1)*3;
			
					for (int y=0;y<nb;y++) {
						for (int x=0;x<nb;x++,cB += 6) {
							
							float tmin = cRay->tmin;
							float tmax = cRay->t;
							if (!intersectBox(cB,cB+3,cRay->from,cRay->dir,cRay->invDir,tmin,tmax)) {	// TODO: pull out ray t etc to shadows
								continue;
							}
							
							const float	*cP0	=	Pt0 + (x*4 + y*4*(div+1))*3;
							const float	*cP1	=	Pt1 + (x*4 + y*4*(div+1))*3;
			
							for (int cj=0;cj<4;cj++) {
								for (int ci=0;ci<4;ci++,cP0+=3,cP1+=3) {
									interpolatev(P00,	cP0,				cP1,				timev);
									interpolatev(P10,	cP0+3,				cP1+3,				timev);
									interpolatev(P01,	cP0+(div+1)*3,		cP1+(div+1)*3,		timev);
									interpolatev(P11,	cP0+(div+1)*3 + 3,	cP1+(div+1)*3 + 3,	timev);
					
									const int i = x*4+ci;
									const int j	= y*4+cj;
									
									intersectQuads();
								}
								cP0 += (div-4+1)*3;
								cP1 += (div-4+1)*3;
							}
						}
					}
		
				}
			}
		}
	} else {
		// We do not posess a fine enough tesselation, check if we have
		// already generated a finer set by splitting
		
		if (children == NULL) {
			// We must lock the tesselateMutex so that the list of known tesselation patches
			// is maintained in a thread safe manner

			osLock(CRenderer::tesselateMutex);
			
			if (children != NULL) {
				// Another thread already did it
				osUnlock(CRenderer::tesselateMutex);
				return;
			}
	
			// Split to children to generate finer patches.  Let them deal with it
			splitToChildren(context);

			osUnlock(CRenderer::tesselateMutex);
		}
	}	
}



///////////////////////////////////////////////////////////////////////
// Function				:	measureLength
// Description			:	This function takes P and returns the sum of edge lengths
// Return Value			:
// Comments				:
static	inline	float	measureLength(const float *P,int step,int num) {
	float	length	=	0;

	for (;num>0;num--) {
		const float	*Pn		=	P + step;
		vector		D;

		subvv(D,Pn,P);
		length	+=	lengthv(D);

		P					=	Pn;
	}

	return length;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CTesselationPatch
// Method				:	initTesselation
// Description			:	Make an estimate about required tesselation sizes
// Return Value			:
// Comments				:
void CTesselationPatch::initTesselation(CShadingContext *context) {
	// We tesselate (but do not save) the finest level to get an accurate
	// r estimate for the grid to start things off.  
	// Q: Can we do this without firing the tesselation off?
	// A: perhaps, but we definitely need r accurate as subdivision will use this to
	// guess their r without tesselation
	tesselate(context,16,TRUE);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CTesselationPatch
// Method				:	sampleTesselation
// Description			:	Perform displacement and sample begin or end sample
// Return Value			:
// Comments				:
void CTesselationPatch::sampleTesselation(CShadingContext *context,int div,unsigned int sample,float *&P) {
	float	**varying	=	context->currentShadingState->varying;

	// Sample points on the patch
	const double	ustep	=	(umax-umin) / (double) div;
	const double	vstep	=	(vmax-vmin) / (double) div;

	const	float time	=	(sample == PARAMETER_BEGIN_SAMPLE) ? 0.0f : 1.0f;
	
	if ((div+1)*(div+1) <= CRenderer::maxGridSize) {
		float	*uv			=	varying[VARIABLE_U];
		float	*vv			=	varying[VARIABLE_V];
		float	*timev		=	varying[VARIABLE_TIME];
		int		up,vp;
		double	u,v;
		for (vp=div+1,v=vmin;vp>0;vp--,v+=vstep) {
			for (up=div+1,u=umin;up>0;up--,u+=ustep) {
				*uv++		=	(float) u;
				*vv++		=	(float) v;
				*timev++	=	time;
			}
		}
		
		context->displace(object,div+1,div+1,SHADING_2D_GRID,PARAMETER_P | sample | PARAMETER_RAYTRACE);
		
		P = varying[VARIABLE_P];
	} else {
		// NOTE: We are assuming here that 16x16 is the maximum size we will be asked to tesselate
		// and that all smaller grid sizes will fit within maxGridSize.  If this is not the case,
		// this code must be updated
		
		assert(div == 16);
		
		const int		hdiv	=	div/2;
		const double	vh		=	vmin + ((double) hdiv+1)*vstep;
		const double	uh		=	umin + ((double) hdiv+1)*ustep;
		
		int			up,vp;
		double		u,v;
		float		*uv			=	varying[VARIABLE_U];
		float		*vv			=	varying[VARIABLE_V];
		float		*timev		=	varying[VARIABLE_TIME];
		float		*dest,*src;
		float		*Pstorage	=	(float *) ralloc(sizeof(float)*3*(div+1)*(div+1),context->threadMemory);

		// top left 1/4			(hdiv+1 x hdiv+1)
		for (vp=hdiv+1,v=vmin;vp>0;vp--,v+=vstep) {
			for (up=hdiv+1,u=umin;up>0;up--,u+=ustep) {
				*uv++		=	(float) u;
				*vv++		=	(float) v;
				*timev++	=	time;
			}
		}
		context->displace(object,hdiv+1,hdiv+1,SHADING_2D_GRID,PARAMETER_P | sample | PARAMETER_RAYTRACE);
		
		for (vp=hdiv+1,dest=Pstorage,src=varying[VARIABLE_P];vp>0;vp--) {
			memcpy(dest,src,sizeof(float)*3*(hdiv+1));
			src		+=	(hdiv+1)*3;
			dest	+=	(div+1)*3;
		}
			
		// top right 1/4		(hdiv x hdiv+1)
		uv			=	varying[VARIABLE_U];
		vv			=	varying[VARIABLE_V];
		timev		=	varying[VARIABLE_TIME];
		for (vp=hdiv+1,v=vmin;vp>0;vp--,v+=vstep) {
			for (up=hdiv,u=uh;up>0;up--,u+=ustep) {
				*uv++		=	(float) u;
				*vv++		=	(float) v;
				*timev++	=	time;
			}
		}
		context->displace(object,hdiv,hdiv+1,SHADING_2D_GRID,PARAMETER_P | sample | PARAMETER_RAYTRACE);
		
		for (vp=hdiv+1,dest=Pstorage+(hdiv+1)*3,src=varying[VARIABLE_P];vp>0;vp--) {
			memcpy(dest,src,sizeof(float)*3*hdiv);
			src		+=	hdiv*3;
			dest	+=	(div+1)*3;
		}
		
		// bottom left 1/4		(hdiv+1 x hdiv)
		uv			=	varying[VARIABLE_U];
		vv			=	varying[VARIABLE_V];
		timev		=	varying[VARIABLE_TIME];
		for (vp=hdiv,v=vh;vp>0;vp--,v+=vstep) {
			for (up=hdiv+1,u=umin;up>0;up--,u+=ustep) {
				*uv++		=	(float) u;
				*vv++		=	(float) v;
				*timev++	=	time;
			}
		}
		context->displace(object,hdiv+1,hdiv,SHADING_2D_GRID,PARAMETER_P | sample | PARAMETER_RAYTRACE);
		
		for (vp=hdiv,dest=Pstorage+(hdiv+1)*(div+1)*3,src=varying[VARIABLE_P];vp>0;vp--) {
			memcpy(dest,src,sizeof(float)*3*(hdiv+1));
			src		+=	(hdiv+1)*3;
			dest	+=	(div+1)*3;
		}

		// bottom right 1/4		(hdiv x hdiv)
		uv			=	varying[VARIABLE_U];
		vv			=	varying[VARIABLE_V];
		timev		=	varying[VARIABLE_TIME];
		for (vp=hdiv,v=vh;vp>0;vp--,v+=vstep) {
			for (up=hdiv,u=uh;up>0;up--,u+=ustep) {
				*uv++		=	(float) u;
				*vv++		=	(float) v;
				*timev++	=	time;
			}
		}
		context->displace(object,hdiv,hdiv,SHADING_2D_GRID,PARAMETER_P | sample | PARAMETER_RAYTRACE);
		
		for (vp=hdiv,dest=Pstorage+(hdiv+1)*(div+1)*3+(hdiv+1)*3,src=varying[VARIABLE_P];vp>0;vp--) {
			memcpy(dest,src,sizeof(float)*3*hdiv);
			src		+=	hdiv*3;
			dest	+=	(div+1)*3;
		}
		
		P = Pstorage;
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CTesselationPatch
// Method				:	tesselate
// Description			:	Find the best tesselation for this object
// Return Value			:
// Comments				:
CTesselationPatch::CPurgableTesselation*		CTesselationPatch::tesselate(CShadingContext *context,char rdiv,int estimateOnly) {
	TMemCheckpoint	memCheckpoint;
	float			*Pstorage = NULL;
	
	// Get some misc variables for fast access
	
	void	*savedState = context->saveState();
	
	memSave(memCheckpoint,context->threadMemory);
	

	int div = rdiv;
	if (div == 1) div = 2;			// sample() cannot do 1x1, so we do 2x2 and drop down
	
	// Compute the sample positions and corresponding normal vectors
	
	sampleTesselation(context,div,PARAMETER_BEGIN_SAMPLE,Pstorage);
	
	// At this point, We have the tesselation. So create the grid and return it, or initialize our
	// grid size guess
	
	#if DEBUG_TESSELATIONS > 0
	if (estimateOnly || DEBUG_TESSELATIONS > 1)
	{
		CDebugView	d("/tmp/tesselate.dat",TRUE);
	
		float *Pcur = Pstorage;
		for (int i =0;i<div;i++) {
			d.line(Pcur,Pcur+3);
			d.line(Pcur+div*(div+1)*3,Pcur+div*(div+1)*3+3);
			Pcur +=3;
		}
		Pcur = Pstorage;
		for (int i =0;i<div;i++) {
			d.line(Pcur,Pcur+(div+1)*3);
			d.line(Pcur+div*3,Pcur+div*3+(div+1)*3);
			Pcur += (div+1)*3;
		}
		#if DEBUG_TESSELATIONS > 2
		Pcur = Pstorage;
		for (int i =(div+1)*(div+1);i>0;i--) {
			d.point(Pcur);
			Pcur += 3;
		}
		#endif
	}
	#endif
	
	
	// This controls how much we overestimate bounds of both the grid, and
	// sub-parts of the grid.  Setting this high hurts performance
	//const float boundExpander = attributes->rasterExpand;
	const float boundExpander = 0.1f;

	// create P if it is so required
	if (!estimateOnly) {
		CPurgableTesselation	*cTesselation	=	NULL;
		
		// Deal with moving tesselations differently, we
		// must save off both ends of the sample if we have motion
		if (!(flags & OBJECT_MOVING_TESSELATION)) {
		
			// No motion
			if (rdiv == 1) {
				// subsampling our 2x2 to 1x1, no bounds
				
				void	*mem			=	allocate_untyped(sizeof(CPurgableTesselation) + 2*2*3*sizeof(float));
						cTesselation	=	(CPurgableTesselation*) mem;
				
				cTesselation->P							=	(float*) ((char*) mem + sizeof(CPurgableTesselation));
				cTesselation->size						=	2*2*3*sizeof(float);
		
				movvv(cTesselation->P,		Pstorage);
				movvv(cTesselation->P+3,	Pstorage+6);
				movvv(cTesselation->P+6,	Pstorage+18);
				movvv(cTesselation->P+9,	Pstorage+24);
			} else if (rdiv <= 4) {
				// not saving bounds here
				void		*mem			= allocate_untyped(sizeof(CPurgableTesselation) + (div+1)*(div+1)*3*sizeof(float));
							cTesselation	= (CPurgableTesselation*) mem;
	
				cTesselation->P							=	(float*) ((char*) mem + sizeof(CPurgableTesselation));
				cTesselation->size						=	(div+1)*(div+1)*3*sizeof(float);
				
				memcpy(cTesselation->P,Pstorage,(div+1)*(div+1)*3*sizeof(float));
			} else {
				// create bounds, but only if it saves us work later
							
				int nb = div>>2;						// number of bounds in each direction
				
				// save the data
				void		*mem			= allocate_untyped(sizeof(CPurgableTesselation) + (div+1)*(div+1)*3*sizeof(float) + nb*nb*6*sizeof(float));
							cTesselation	= (CPurgableTesselation*) mem;
	
				cTesselation->P							=	(float*) ((char*) mem + sizeof(CPurgableTesselation));
				cTesselation->size						=	((div+1)*(div+1)*3 + nb*nb*6)*sizeof(float);
				
				// FIXME: bounds should be first for cache efficiency
				float *bounds							=	cTesselation->P + (div+1)*(div+1)*3;
				
				memcpy(cTesselation->P,Pstorage,(div+1)*(div+1)*3*sizeof(float));
				
				
				// Clear bounds
				float *bnds = bounds;
				for (int i=0;i<nb*nb;i++,bnds+=6) {
					initv(bnds,C_INFINITY);
					initv(bnds+3,-C_INFINITY);
				}
			
				// Sum them
				bnds = bounds;
				for (int y=0;y<nb;y++) {
					for (int x=0; x<nb;x++,bnds+=6) {
						const float *cP		=	cTesselation->P + (x*4 + y*4*(div+1))*3;
					
						for (int i=0;i<5;i++) {
							for (int j=0;j<5;j++,cP+=3) {
								addBox(bnds,bnds+3,cP);
							}
							cP += ((div+1)-5)*3;
						}
					}
				}
				
				// Expand bounds
				bnds = bounds;
				for(int i=0;i<nb*nb;i++){
					float maxBound	=	max(bnds[3+COMP_X]-bnds[COMP_X],bnds[3+COMP_Y]-bnds[COMP_Y]);
					maxBound		=	max(bnds[3+COMP_Z]-bnds[COMP_Z],maxBound);
					maxBound		*=	boundExpander;
		
					bnds[COMP_X]	-=	maxBound;
					bnds[COMP_Y]	-=	maxBound;
					bnds[COMP_Z]	-=	maxBound;
					bnds[3+COMP_X]	+=	maxBound;
					bnds[3+COMP_Y]	+=	maxBound;
					bnds[3+COMP_Z]	+=	maxBound;
					
					bnds+=6;
				}	
			}
		} else {
		
			// We're moving
			if (rdiv == 1) {
				// Subsampling our 2x2 to 1x1, no bounds
				
				void	*mem			=	allocate_untyped(sizeof(CPurgableTesselation) + 2*2*2*3*sizeof(float));
						cTesselation	=	(CPurgableTesselation*) mem;
				
				cTesselation->P							=	(float*) ((char*) mem + sizeof(CPurgableTesselation));
				cTesselation->size						=	2*2*2*3*sizeof(float);
		
				// Save first sample
				movvv(cTesselation->P,		Pstorage);
				movvv(cTesselation->P+3,	Pstorage+6);
				movvv(cTesselation->P+6,	Pstorage+18);
				movvv(cTesselation->P+9,	Pstorage+24);
				
				// Displace again
				sampleTesselation(context,div,PARAMETER_END_SAMPLE,Pstorage);
				
				// Copy the second sample
				movvv(cTesselation->P+12,	Pstorage);
				movvv(cTesselation->P+15,	Pstorage+6);
				movvv(cTesselation->P+18,	Pstorage+18);
				movvv(cTesselation->P+21,	Pstorage+24);
			} else if (rdiv <= 4) {
				// Not saving bounds here
				void		*mem			= allocate_untyped(sizeof(CPurgableTesselation) + 2*(div+1)*(div+1)*3*sizeof(float));
							cTesselation	= (CPurgableTesselation*) mem;
	
				cTesselation->P							=	(float*) ((char*) mem + sizeof(CPurgableTesselation));
				cTesselation->size						=	2*(div+1)*(div+1)*3*sizeof(float);
				
				// Save first sample
				memcpy(cTesselation->P,Pstorage,(div+1)*(div+1)*3*sizeof(float));
				
				// Displace again
				sampleTesselation(context,div,PARAMETER_END_SAMPLE,Pstorage);
				
				// Save second sample
				memcpy(cTesselation->P+(div+1)*(div+1)*3,Pstorage,(div+1)*(div+1)*3*sizeof(float));
			} else {
				// create bounds, but only if it saves us work later
							
				int nb = div>>2;						// number of bounds in each direction
				
				// save the data
				void		*mem			= allocate_untyped(sizeof(CPurgableTesselation) + 2*(div+1)*(div+1)*3*sizeof(float) + nb*nb*6*sizeof(float));
							cTesselation	= (CPurgableTesselation*) mem;
	
				cTesselation->P							=	(float*) ((char*) mem + sizeof(CPurgableTesselation));
				cTesselation->size						=	(2*(div+1)*(div+1)*3 + nb*nb*6)*sizeof(float);
				
				// FIXME: bounds should be first for cache efficiency
				float *bounds							=	cTesselation->P + 2*(div+1)*(div+1)*3;
				
				// Save the first sample
				memcpy(cTesselation->P,Pstorage,(div+1)*(div+1)*3*sizeof(float));
				
				// Clear the bounds
				float *bnds = bounds;
				for (int i=0;i<nb*nb;i++,bnds+=6) {
					initv(bnds,C_INFINITY);
					initv(bnds+3,-C_INFINITY);
				}
			
				// Sum them
				bnds = bounds;
				for (int y=0;y<nb;y++) {
					for (int x=0; x<nb;x++,bnds+=6) {
						const float *cP		=	cTesselation->P + (x*4 + y*4*(div+1))*3;
					
						for (int i=0;i<5;i++) {
							for (int j=0;j<5;j++,cP+=3) {
								addBox(bnds,bnds+3,cP);
							}
							cP += ((div+1)-5)*3;
						}
					}
				}
				
				// Displace again
				sampleTesselation(context,div,PARAMETER_END_SAMPLE,Pstorage);
				
				// Save the second sample
				memcpy(cTesselation->P+(div+1)*(div+1)*3,Pstorage,(div+1)*(div+1)*3*sizeof(float));
				
				// Sum the second sample
				bnds = bounds;
				for (int y=0;y<nb;y++) {
					for (int x=0; x<nb;x++,bnds+=6) {
						const float *cP		=	cTesselation->P + (div+1)*(div+1)*3 + (x*4 + y*4*(div+1))*3;
					
						for (int i=0;i<5;i++) {
							for (int j=0;j<5;j++,cP+=3) {
								addBox(bnds,bnds+3,cP);
							}
							cP += ((div+1)-5)*3;
						}
					}
				}

				// Expand bounds
				bnds = bounds;
				for(int i=0;i<nb*nb;i++){
					float maxBound	=	max(bnds[3+COMP_X]-bnds[COMP_X],bnds[3+COMP_Y]-bnds[COMP_Y]);
					maxBound		=	max(bnds[3+COMP_Z]-bnds[COMP_Z],maxBound);
					maxBound		*=	boundExpander;
		
					bnds[COMP_X]	-=	maxBound;
					bnds[COMP_Y]	-=	maxBound;
					bnds[COMP_Z]	-=	maxBound;
					bnds[3+COMP_X]	+=	maxBound;
					bnds[3+COMP_Y]	+=	maxBound;
					bnds[3+COMP_Z]	+=	maxBound;
					
					bnds+=6;
				}	
			}
		}
		
		memRestore(memCheckpoint,context->threadMemory);
		
		context->restoreState(savedState);

		// install tesselation last so other threads don't use bounds/P before they're ready
		return cTesselation;

	}
	
	// If we get here, we are estimating only
	
	// Evaluate the quality of this tesselation in u and v separately
	float	vMax	=	0;
	float	vMin	=	C_INFINITY;
	float	vAvg	=	0;
	for (int i=0;i<=div;i++) {
		const float	l	=	measureLength(Pstorage + i*3,(div+1)*3,div);
		vMax			=	max(vMax,l);
		vMin			=	min(vMin,l);
		vAvg			+=	l;
	}

	float	uMax	=	0;
	float	uMin	=	C_INFINITY;
	float	uAvg	=	0;
	for (int i=0;i<=div;i++) {
		const float	l	=	measureLength(Pstorage + i*(div+1)*3,3,div);
		uMax			=	max(uMax,l);
		uMin			=	min(uMin,l);
		uAvg			+=	l;
	}

	vAvg	/=	(float) (div+1)*div;
	uAvg	/=	(float) (div+1)*div;
	
	// Force overestimation on grids with large variation is quad size
	// Note: the min and max are grid-side minima and maxima, not quad
	// maxima.  This means that they are unlikely to be drastically
	// different, but we can use this to cope with undertesselation of
	// edge-pinched grids
	const float uDev = fabs(uMax-uMin)/(float)(div);
	const float vDev = fabs(vMax-vMin)/(float)(div);
	uAvg += uDev;
	vAvg += vDev;
	
	if (!(attributes->flags & ATTRIBUTES_FLAGS_DISPLACEMENTS)) {
		// When not tracing displacements, all we desire is a patch
		// which is flat enough to be a good approximation
		// if we are tracing displacements, then the quad sizes must
		// genuinely be smaller than the ray footprint
		
		// estimate flatness
		float	vFlat =	0;
		for (int i=0;i<=div;i++) {
			vector D,E,O;
			movvv(O,Pstorage + i*3);
			subvv(D,Pstorage + i*3 + (div+1)*div*3,O);
			const float lD = lengthv(D);
			if (lengthv(D) > 0) mulvf(D,1.0f/lD);
			for(int j=1;j<div;j++) {
				subvv(E,Pstorage + i*3 + (div+1)*j*3,O);
				mulvf(E,D,dotvv(D,E));
				addvv(E,O);
				subvv(E,Pstorage + i*3 + (div+1)*j*3);
				vFlat += lengthv(E);
			}
		}
	
		float	uFlat	=	0;
		for (int i=0;i<=div;i++) {
			vector D,E,O;
			movvv(O,Pstorage + (div+1)*i*3);
			subvv(D,Pstorage + (div+1)*i*3 + div*3,O);
			const float lD = lengthv(D);
			if (lengthv(D) > 0) mulvf(D,1.0f/lD);
			for(int j=1;j<div;j++) {
				subvv(E,Pstorage + (div+1)*i*3 + j*3,O);
				mulvf(E,D,dotvv(D,E));
				addvv(E,O);
				subvv(E,Pstorage + (div+1)*i*3 + j*3);
				uFlat += lengthv(E);
			}
		}
	
		vFlat	/=	(float) div*div;
		uFlat	/=	(float) div*div;

		//fprintf(stderr,"%d -- %f %f  -- %f %f\n",depth,uAvg,vAvg,uFlat,vFlat);
		if (uFlat < uAvg && vFlat < vAvg) {
			flags |= OBJECT_TERMINAL_TESSELATION;
		}
	} else {
		// prevent tesselation beyond a level we could deal with
		if ((umax-umin)/(4*div) < C_EPSILON) flags |= OBJECT_TERMINAL_TESSELATION;
		if ((vmax-vmin)/(4*div) < C_EPSILON) flags |= OBJECT_TERMINAL_TESSELATION;
	}
	
	// Simply save the coarse r estimate
	if (rdiv == 1) {
		// we sampled 2x2 because we have to, but we wanted 1x1
		rmax							=	max(rmax,(uAvg+vAvg)/4.0f);
	} else {
		rmax							=	max(rmax,div*(uAvg+vAvg)/2.0f);
	}
	
	// Calculate a tighter bound
	initv(bmin,C_INFINITY);
	initv(bmax,-C_INFINITY);

	float *Pcur = Pstorage;
	for (int i =(div+1)*(div+1);i>0;i--) {
		addBox(bmin,bmax,Pcur);
		Pcur			+=	3;
	}
	
	// If we have motion, account for it
	if (flags & OBJECT_MOVING_TESSELATION) {
		// Displace again
		sampleTesselation(context,div,PARAMETER_END_SAMPLE,Pstorage);
		
		// Bound the second sample
		Pcur = Pstorage;
		for (int i =(div+1)*(div+1);i>0;i--) {
			addBox(bmin,bmax,Pcur);
			Pcur			+=	3;
		}
		
		// We will use the r estimate from the first sample
		// Perhaps we should do better
	}
	
	// Expand the bound
	float maxBound	=	max(bmax[COMP_X]-bmin[COMP_X],bmax[COMP_Y]-bmin[COMP_Y]);
	maxBound		=	max(bmax[COMP_Z]-bmin[COMP_Z],maxBound);
	maxBound		*=	boundExpander;

	bmin[COMP_X]	-=	maxBound;
	bmin[COMP_Y]	-=	maxBound;
	bmin[COMP_Z]	-=	maxBound;
	bmax[COMP_X]	+=	maxBound;
	bmax[COMP_Y]	+=	maxBound;
	bmax[COMP_Z]	+=	maxBound;

	memRestore(memCheckpoint,context->threadMemory);
	
	context->restoreState(savedState);
	
	return NULL;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSurface
// Method				:	splitToChildren
// Description			:	generate subpatches when current tesselations are insufficient
// Return Value			:
// Comments				:
void		CTesselationPatch::splitToChildren(CShadingContext *context) {	
	const int udiv = 4;
	const int vdiv = 4;
	
	float	**varying	=	context->currentShadingState->varying;

	const double	ustep	=	(umax-umin) / (double) udiv;
	const double	vstep	=	(vmax-vmin) / (double) vdiv;

	// sanity check before dividing
	if(umin>= umax || vmin>= vmax) {
		return;
	}

	// Compute the new patch parameteric splits
	
	int		cu,cv;
	double	u,v;

	float *us = (float*) alloca(sizeof(float)*((udiv+1) + (vdiv+1)));	// don't use varyings as tesselate will smash them
	float *vs = us + (udiv+1);
	
	
	float	*vv		=	vs;
	for (cv=0,v=vmin;cv<vdiv+1;cv++,v+=vstep) {
		*vv++		=	(float) v;
	}
	float	*uv			=	us;
	for (cu=0,u=umin;cu<udiv+1;cu++,u+=ustep) {
		*uv++		=	(float) u;
	}
	
	// ensure the ends are at the ends
	us[udiv] = umax;	
	vs[vdiv] = vmax;
	
	// generate subpatches
	CTesselationPatch *subPatches = NULL;
		
	for (cv=0,vv=vs;cv<vdiv;cv++,vv++) {
		for (cu=0,uv=us;cu<udiv;cu++,uv++) {
		
			// sanity check before emitting the subpatch
			if(uv[0] >= uv[1] || vv[0] >= vv[1]) {
				continue;
			}
			
			// emit the new subpatch			
			CTesselationPatch *cPatch = new CTesselationPatch(attributes,xform,object,uv[0],uv[1],vv[0],vv[1],depth+1,minDepth,-1);
			
			cPatch->initTesselation(context);
			cPatch->sibling = subPatches;
			subPatches = cPatch;
		}
	}
	
	// attach them
	setChildren(context,subPatches);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CTesselationPatch
// Method				:	initTesselations
// Description			:	initialize the thread data for tesselations
// Return Value			:
// Comments				:
void		CTesselationPatch::initTesselations(int geoCacheMemory) {
	for (int i=0;i<TESSELATION_NUM_LEVELS;i++) {
		lastRefNumbers[i]			=	new int[CRenderer::numThreads];
		tesselationUsedMemory[i]	=	new int[CRenderer::numThreads];
		
		for (int j=0;j<CRenderer::numThreads;j++) {
			tesselationUsedMemory[i][j]	=	0;
		}
		
		// calculate the maximum tesselation cache size per thread, per level
		tesselationMaxMemory[i] = (int) ceil((float) geoCacheMemory / (float) TESSELATION_NUM_LEVELS / (float) CRenderer::numThreads);
	}
	
	// Init stats
	stats.tesselationOverhead = 0;
	
	#ifdef DEBUG_STATS
	for(int i=0;i<TESSELATION_NUM_LEVELS*DEBUG_STATS;i++)	tessPerLevel[i] = 0;
	for(int i=0;i<DEBUG_STATS;i++)							tessPerDepth[i] = 0;
	#endif
}

///////////////////////////////////////////////////////////////////////
// Class				:	CTesselationPatch
// Method				:	shutdownTesselations
// Description			:	shutdown tesselations
// Return Value			:
// Comments				:
void		CTesselationPatch::shutdownTesselations() {
	for (int i=0;i<TESSELATION_NUM_LEVELS;i++) {
		delete[] lastRefNumbers[i];
		delete[] tesselationUsedMemory[i];
	}

	assert(tesselationList == NULL);
	tesselationList = NULL;
	
	#ifdef DEBUG_STATS
	for(int d = 0; d < DEBUG_STATS; d++) {
		printf("depth %d count: %d:\n",d,tessPerDepth[d]);
		for(int l = 0; l < TESSELATION_NUM_LEVELS; l++) {
			printf("  level %d:  %d\n",l,tessPerLevel[d*TESSELATION_NUM_LEVELS+l]);
		}
	}
	#endif
}

///////////////////////////////////////////////////////////////////////
// Function				:	tesselationQuickSort
// Description			:	Sort the tesselations in the order of increasing last ref number
// Return Value			:
// Comments				:
void	CTesselationPatch::tesselationQuickSort(CTesselationEntry **activeTesselations,int start,int end,int thread) {
	int					i,last;
	CTesselationEntry	*cEntry;
	
	for (last=start,i=start+1;i<=end;i++) {
		if (activeTesselations[i]->threadTesselation[thread]->lastRefNumber < activeTesselations[start]->threadTesselation[thread]->lastRefNumber) {
			last++;
			cEntry						=	activeTesselations[last];
			activeTesselations[last]	=	activeTesselations[i];
			activeTesselations[i]		=	cEntry;
		}
	}

	cEntry						=	activeTesselations[last];
	activeTesselations[last]	=	activeTesselations[start];
	activeTesselations[start]	=	cEntry;

	// Speed is not an issue since this is not done very frequently, so recursion is OK
	if ((last-1) > start)
		tesselationQuickSort(activeTesselations,start,last-1,thread);

	if (end > (last+1))
		tesselationQuickSort(activeTesselations,last+1,end,thread);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CTesselationPatch
// Method				:	purgeTesselations
// Description			:	purge tesselations of level from thread
// Return Value			:
// Comments				:
void		CTesselationPatch::purgeTesselations(CShadingContext *context,CTesselationPatch *entry,int thread,int level,int all) {
	// Do we have stuff to free ?
	if (tesselationList == NULL)	return;

	// Ensure no other thread creates new tesselations whilst we flush
	osLock(CRenderer::tesselateMutex);
	
	
	// Figure out how many tesselations of this level we have in memory
	int				i,j;
	CTesselationEntry	**activeTesselations;
	CTesselationPatch	*cPatch;
	CTesselationEntry	*cTess;
	for (cPatch=tesselationList,i=0;cPatch!=NULL;cPatch=cPatch->next) {
		if (cPatch->levels[level].threadTesselation[thread] != NULL) {
			i++;
		}
	}
	
	// Collect those tesselations into an array
	activeTesselations	=	(CTesselationEntry **) ralloc(i*sizeof(CTesselationEntry *),context->threadMemory);
	for (cPatch=tesselationList,i=0;cPatch!=NULL;cPatch=cPatch->next) {
		if (cPatch->levels[level].threadTesselation[thread] != NULL) {
			if (cPatch != entry ) {
				activeTesselations[i++]	=	&cPatch->levels[level];
			}
		}
	}
	
	// Sort the tesselations from last used to the most recently used
	if (i > 1)	tesselationQuickSort(activeTesselations,0,i-1,thread);

	// Free the memory
	if (all)	tesselationMaxMemory[level]	=	0;
	for (j=0;(j<i) && (tesselationUsedMemory[level][thread] > (tesselationMaxMemory[level]/2));j++) {
		cTess									=	activeTesselations[j];

		tesselationUsedMemory[level][thread]	-=	cTess->threadTesselation[thread]->size;
		stats.tesselationMemory					-=	cTess->threadTesselation[thread]->size;
			
		free_untyped((unsigned char *) cTess->threadTesselation[thread]);
		cTess->threadTesselation[thread]		=	NULL;
	}
	
	osUnlock(CRenderer::tesselateMutex);
}

