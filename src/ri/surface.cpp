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
	stats.numGprims++;
	stats.gprimMemory	+=	sizeof(CPatch);
	stats.numSurfaces++;
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
	stats.numGprims--;
	stats.gprimMemory	-=	sizeof(CPatch);
	stats.numSurfaces--;

	object->detach();
}


static	inline int	cull(float *bmin,float *bmax,const float *P,const float *N,int k,int nsides,int disable) {
	int	i;

	// Update the bounding box
	for (i=k;i>0;i--) {
		addBox(bmin,bmax,P);
		P			+=	3;
	}

	// Check the back face culling
	if (nsides == 1  && !disable) {
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
		// No, probe the surface and find the bounding box
		vector		D;
		float		Pmov[4*3];
		float		maxBound;
		float		dx,dy;
		float		*P;
		int			up,vp;
		int			k;
		int			cullFlags	=	TRUE;
		
		// We need to split this patch, so no need to compute udiv / vdiv

		// Get some misc variables for fast access
		const int	disableCull		=	attributes->flags & ATTRIBUTES_FLAGS_SHADE_BACKFACE;
		const int	numUprobes		=	attributes->numUProbes;
		const int	numVprobes		=	attributes->numVProbes;
		float		**varying		=	r->currentShadingState->varying;

		// Sample points on the patch
		const double	ustart		=	umin;
		const double	vstart		=	vmin;
		const double	ustep		=	(umax - ustart) / (double) (numUprobes-1);
		const double	vstep		=	(vmax - vstart) / (double) (numVprobes-1);
		double			u,v;

		// The current u/v/time vectors
		float			*uv			=	varying[VARIABLE_U];
		float			*vv			=	varying[VARIABLE_V];
		float			*timev		=	varying[VARIABLE_TIME];

		// Init the bounding box to zero
		initv(bmin,C_INFINITY);
		initv(bmax,-C_INFINITY);

		// Take care of the motion first
		if ((CRenderer::flags & OPTIONS_FLAGS_MOTIONBLUR) && (object->moving())) {

			// Compute the sample positions and corresponding normal vectors
			for (vp=0,v=vstart,k=0;vp<numVprobes;vp++,v+=vstep) {
				for (up=0,u=ustart;up<numUprobes;up++,u+=ustep,k++) {
					uv[k]		=	(float) u;
					vv[k]		=	(float) v;
					timev[k]	=	1;
				}
			}
			
			assert(k <= (int) CRenderer::maxGridSize);
			r->displace(object,numUprobes,numVprobes,SHADING_2D_GRID,PARAMETER_P | PARAMETER_N | PARAMETER_END_SAMPLE | PARAMETER_RAYTRACE);
			cullFlags			&=	cull(bmin,bmax,varying[VARIABLE_P],varying[VARIABLE_N],k,attributes->nSides,disableCull);
			
			movvv(Pmov,varying[VARIABLE_P]);
			movvv(Pmov+3,varying[VARIABLE_P]+(numUprobes-1)*3);
			movvv(Pmov+6,varying[VARIABLE_P]+(numVprobes*numUprobes-1)*3);
			movvv(Pmov+9,varying[VARIABLE_P]+((numVprobes-1)*numUprobes)*3);
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
		r->displace(object,numUprobes,numVprobes,SHADING_2D_GRID,PARAMETER_P | PARAMETER_N | PARAMETER_BEGIN_SAMPLE);
		cullFlags			&=	cull(bmin,bmax,varying[VARIABLE_P],varying[VARIABLE_N],k,attributes->nSides,disableCull);

		// Are we culled
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
			int		i1		=	0;								// Index of the top left
			int		i2		=	numUprobes-1;					// Index of the top right
			int		i3		=	numVprobes*numUprobes-1;		// Index of the bottom right
			int		i4		=	(numVprobes-1)*numUprobes;		// Index of the bottom left
			float	uLength[2],vLength[2];
			float	umLength,vmLength;
			float	shadingRate	=	attributes->shadingRate;

			// Project all the shaded vertices
			i1				*=	3;
			i2				*=	3;
			i3				*=	3;
			i4				*=	3;
			P				=	varying[VARIABLE_P];
			camera2pixels(numUprobes*numVprobes,P);
			
			// Correct shading rate with dof factor
			if (CRenderer::flags & OPTIONS_FLAGS_FOCALBLUR) {
				const float coc = minCocPixels(bmin[COMP_Z],bmax[COMP_Z]);
				shadingRate *= max(1,0.5f*coc);
			}
			
			// Optionally correct shading rate with motionfactor
			if ((CRenderer::flags & OPTIONS_FLAGS_MOTIONBLUR) && (object->moving())) {

				camera2pixels(4,(float*)Pmov);

				subvv(Pmov,P + i1);		Pmov[2] = 0;
				subvv(Pmov+3,P + i2);	Pmov[5] = 0;
				subvv(Pmov+6,P + i3);	Pmov[8] = 0;
				subvv(Pmov+9,P + i4);	Pmov[11] = 0;

				const float blurDistance = 0.25f*(sqrtf(dotvv(Pmov,Pmov)) + sqrtf(dotvv(Pmov+3,Pmov+3)) + sqrtf(dotvv(Pmov+6,Pmov+6)) + sqrtf(dotvv(Pmov+9,Pmov+9)));

				shadingRate += attributes->motionFactor*shadingRate*blurDistance;
			}
			
			if (attributes->flags & ATTRIBUTES_FLAGS_NONRASTERORIENT_DICE) {
				subvv(D,P+i1,P+i2);	uLength[0] = lengthv(D);			// Length of the top
				subvv(D,P+i3,P+i4);	uLength[1] = lengthv(D);			// Length of the bottom
				subvv(D,P+i1,P+i4);	vLength[0] = lengthv(D);			// Length of the left
				subvv(D,P+i2,P+i3);	vLength[1] = lengthv(D);			// Length of the right
			} else {
				dx				=	P[i1+0] - P[i2+0];					// Length of the top
				dy				=	P[i1+1] - P[i2+1];
				uLength[0]		=	sqrtf(dx*dx + dy*dy);
				dx				=	P[i3+0] - P[i4+0];					// Length of the bottom
				dy				=	P[i3+1] - P[i4+1];
				uLength[1]		=	sqrtf(dx*dx + dy*dy);
				dx				=	P[i1+0] - P[i4+0];					// Length of the left
				dy				=	P[i1+1] - P[i4+1];
				vLength[0]		=	sqrtf(dx*dx + dy*dy);
				dx				=	P[i2+0] - P[i3+0];					// Length of the right
				dy				=	P[i2+1] - P[i3+1];
				vLength[1]		=	sqrtf(dx*dx + dy*dy);
			}

			umLength		=	(uLength[0]+uLength[1]) *0.5f;// The length of the u and v extremal edges
			vmLength		=	(vLength[0]+vLength[1]) *0.5f;

			umLength		=	min(umLength,1000);						// FIXME: This is really ugly
			vmLength		=	min(vmLength,1000);

			// Do some regularization on the shading rate
			if (umLength > vmLength) {
				vmLength	=	(float) max(umLength * 0.5,vmLength);
			} else {
				umLength	=	(float) max(vmLength * 0.5,umLength);
			}

			if (attributes->flags & ATTRIBUTES_FLAGS_BINARY_DICE) {
				const double	log2		=	log(2.0);
				const float		udivf		=	max(1,(float) (C_EPSILON + umLength / shadingRate));
				const float		vdivf		=	max(1,(float) (C_EPSILON + vmLength / shadingRate));

				udiv	=	1 << (unsigned int) (ceil(log(udivf) / log2));
				vdiv	=	1 << (unsigned int) (ceil(log(vdivf) / log2));
			} else {
				udiv	=	(unsigned int) (ceil(C_EPSILON + umLength / shadingRate));
				vdiv	=	(unsigned int) (ceil(C_EPSILON + vmLength / shadingRate));
			}

		} else {
			// Are we making too many splits ?
			if (depth >= CRenderer::maxEyeSplits) {
				warning(CODE_SYSTEM,"Too many eye splits for primitive \"%s\"\n",attributes->name);
				return;
			}

			// We can not make the perspective divide, so make sure we split into 4 next time
			udiv	=	0;
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
		osLock(CRenderer::refCountMutex);
		p1				=	new CPatch(attributes,xform,object,umin,umid,vmin,vmax,depth+1,minDepth);
		p2				=	new CPatch(attributes,xform,object,umid,umax,vmin,vmax,depth+1,minDepth);
		osUnlock(CRenderer::refCountMutex);

		p1->dice(r);
		p2->dice(r);

		osLock(CRenderer::refCountMutex);
		p1->check();
		p2->check();
		stats.numSplits++;
		stats.numUsplits++;
		osUnlock(CRenderer::refCountMutex);
		break;
	case 1:
		if (vmax <= vmin)	break;

		// Split along one direction
		vmid			=	(vmin + vmax)*0.5f;
		osLock(CRenderer::refCountMutex);
		p1				=	new CPatch(attributes,xform,object,umin,umax,vmin,vmid,depth+1,minDepth);	
		p2				=	new CPatch(attributes,xform,object,umin,umax,vmid,vmax,depth+1,minDepth);	
		osUnlock(CRenderer::refCountMutex);

		p1->dice(r);
		p2->dice(r);

		osLock(CRenderer::refCountMutex);
		p1->check();
		p2->check();
		stats.numSplits++;
		stats.numVsplits++;
		osUnlock(CRenderer::refCountMutex);
		break;
	case 2:
		if (vmax <= vmin)	break;
		if (umax <= umin)	break;

		// Split along one direction
		vmid			=	(vmin + vmax)*0.5f;
		umid			=	(umin + umax)*0.5f;
		osLock(CRenderer::refCountMutex);
		p1				=	new CPatch(attributes,xform,object,umin,umid,vmin,vmid,depth+1,minDepth);
		p2				=	new CPatch(attributes,xform,object,umid,umax,vmin,vmid,depth+1,minDepth);
		p3				=	new CPatch(attributes,xform,object,umin,umid,vmid,vmax,depth+1,minDepth);
		p4				=	new CPatch(attributes,xform,object,umid,umax,vmid,vmax,depth+1,minDepth);
		osUnlock(CRenderer::refCountMutex);

		p1->dice(r);
		p2->dice(r);
		p3->dice(r);
		p4->dice(r);

		osLock(CRenderer::refCountMutex);
		p1->check();
		p2->check();
		p3->check();
		p4->check();
		stats.numSplits++;
		stats.numUVsplits++;
		osUnlock(CRenderer::refCountMutex);

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

//#define DEBUG_HITS
#define DEBUG_TESSELATIONS 0


int					*CTesselationPatch::lastRefNumbers[TESSELATION_NUM_LEVELS];
int					*CTesselationPatch::tesselationUsedMemory[TESSELATION_NUM_LEVELS];
int					CTesselationPatch::tesselationMaxMemory[TESSELATION_NUM_LEVELS];
CTesselationPatch	*CTesselationPatch::tesselationList;


///////////////////////////////////////////////////////////////////////
// Class				:	CPatch
// Method				:	CPatch
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CTesselationPatch::CTesselationPatch(CAttributes *a,CXform *x,CSurface *o,float umin,float umax,float vmin,float vmax,char depth,char minDepth,float r) : CObject(a,x) {
	// Work out whether we're moving and mark us as a tesselation
	this->flags		|=	OBJECT_TESSELATION;
	if (o->moving()) 
		this->flags |= OBJECT_MOVING_TESSELATION;
	
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
		
		levels[i].tesselation		=	NULL;
		levels[i].threadTesselation	=	cTess;
		levels[i].refCount			=	0;
		
		#ifdef TESSELATION_LOCK_PER_ENTRY
			osCreateMutex(levels[i].mutex);
		#endif
	}
	
	// Maintain the linked list
	prev						=	NULL;
	next						=	tesselationList;
	if (tesselationList != NULL)
		tesselationList->prev	=	this;
	tesselationList				=	this;
	
	// Set the initial guess for the grid size
	this->rmax		=	r;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPatch
// Method				:	~CPatch
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
		if (levels[i].tesselation != NULL) free(levels[i].tesselation);
		delete[] levels[i].threadTesselation;
		#ifdef TESSELATION_LOCK_PER_ENTRY
			osDeleteMutex(levels[i].mutex);
		#endif
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPatch
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
	
	float requiredR = cRay->da * t + cRay->db;

	// Bail very early if this ray should have been handled by a coarser tesselation
	if (rmax*2.0f < requiredR && depth > 0) {
		// do not proceed further
		return;
	}
		
	// We must find the appropriate tesselation level
	float	rCur	=	rmax;
	int		div		=	1;
	int		level	=	0;
	for (level=0;level<TESSELATION_NUM_LEVELS;level++) {
		if (rCur < requiredR) {
			break;
		}
		rCur	*=	0.25;
		div		=	div<<2;
	}
		
	// Did we find a tesselation in this tesselationPatch?
	if (level < TESSELATION_NUM_LEVELS) {
		// Yes, our r is sufficient
		
		const int thread = context->thread;
		
		
		// Verify we have a tesselation
		if (levels[level].threadTesselation[thread] == NULL) {
			// No, we must get one, lock first
			
			#ifdef TESSELATION_LOCK_PER_ENTRY
				osLock(levels[level].mutex);
			#else
				osLock(CRenderer::tesselateMutex);
			#endif
			
			if (levels[level].tesselation == NULL) {
				// Create the tesselation
				levels[level].tesselation		=	tesselate(context,div,FALSE);
				levels[level].refCount			=	1;
				
				// Restore the refCount
				levels[level].tesselation->lastRefNumber[thread]	=	lastRefNumbers[level][thread];
				
				/// FIXME make these context stats
				// Update stats
				stats.tesselationMemory								+=	levels[level].tesselation->size;
				if (stats.tesselationPeakMemory < stats.tesselationMemory) {
					stats.tesselationPeakMemory = stats.tesselationMemory;
				}
				// Update stats
				stats.tesselationCacheMisses++;
				
				// Purge if we exceeded the max memory for this thread
				if (tesselationUsedMemory[level][thread] > tesselationMaxMemory[level]) {
					purgeTesselations(context,thread,level,FALSE);
				}
			} else {
				// We already have this tesselation in another thread
				levels[level].refCount++;
			}
			
			tesselationUsedMemory[level][thread] += levels[level].tesselation->size;
			levels[level].threadTesselation[thread] = levels[level].tesselation;
			
			#ifdef TESSELATION_LOCK_PER_ENTRY
				osUnlock(levels[level].mutex);
			#else
				osUnlock(CRenderer::tesselateMutex);
			#endif
		} else {
			/// FIXME make these context stats
			// Update stats
			stats.tesselationCacheHits++;
		}
		
		// Bump the tesselation refCount
		lastRefNumbers[level][thread]++;
		levels[level].tesselation->lastRefNumber[thread]	=	lastRefNumbers[level][thread];
		
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
							t	=	(P[COMP_X] - r[COMP_X]) / q[COMP_X];		\
						else if (q[COMP_Y]*q[COMP_Y] >= q[COMP_Z]*q[COMP_Z])	\
							t	=	(P[COMP_Y] - r[COMP_Y]) / q[COMP_Y];		\
						else													\
							t	=	(P[COMP_Z] - r[COMP_Z]) / q[COMP_Z];		\
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
							if (attributes->nSides == 1) {						\
								if (dotvv(q,N) < 0) {							\
									cRay->object	=	object;					\
									cRay->u			=	umin + ((float) u + i)*urg;	\
									cRay->v			=	vmin + ((float) v + j)*vrg;	\
									cRay->t			=	(float) t;					\
									movvv(cRay->N,N);								\
									debugHit();										\
								}												\
							} else {											\
								cRay->object	=	object;						\
								cRay->u			=	umin + ((float) u + i)*urg;	\
								cRay->v			=	vmin + ((float) v + j)*vrg;	\
								cRay->t			=	(float) t;					\
								movvv(cRay->N,N);								\
								debugHit();										\
							}													\
						}														\
					}															\
				}
	
				
		#define intersectQuads()												\
																				\
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
		
		// We treat moving patches differently
		if (!(flags & OBJECT_MOVING_TESSELATION)) {
		
			// No motion
			if (div == 1) {
				// 1x1
				const float	*r		=	cRay->from;
				const float	*q		=	cRay->dir;
			
				const float	*P00	=	levels[level].tesselation->P;
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
				if (rCur*0.5 < requiredR) {
					// downsample 4x4 to 2x2 (not the same as above because we divided
					// in the parametric space here we quads intersect directly
					
					const float	*r		=	cRay->from;
					const float	*q		=	cRay->dir;
					
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
					
					const float	*r		=	cRay->from;
					const float	*q		=	cRay->dir;
					
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
				if (rCur*0.5 < requiredR) {
					// downsample 8x8 to 4x4 or 16x16 to 8x8
					// 8x8 or 16x16 quads (or greater if 3*maxGridSize allows)
					// we bound-intersect each 2x2 subgrid before intersecting quads
									
					const float	*r		=	cRay->from;
					const float	*q		=	cRay->dir;
					
					const float urg		=	2.0f*(umax - umin) / (float) div;
					const float vrg		=	2.0f*(vmax - vmin) / (float) div;
			
					int nb				=	div>>2;
					
					const float	*P		=	thisTesselation->P;
					const float	*cB		=	P+(div+1)*(div+1)*3;
					
					for (int y=0;y<nb;y++) {
						for (int x=0;x<nb;x++,cB+=6) {
							
							float tmin = cRay->tmin;
							float tmax = cRay->t;
							if (!intersectBox(cB,cB+3,cRay->from,cRay->dir,tmin,tmax)) {	// TODO: pull out ray t etc to shadows
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
					
					const float	*r		=	cRay->from;
					const float	*q		=	cRay->dir;
					
					const float urg		=	(umax - umin) / (float) div;
					const float vrg		=	(vmax - vmin) / (float) div;
			
					int nb				=	div>>2;
								
					const float	*P		=	thisTesselation->P;
					const float	*cB		=	P+(div+1)*(div+1)*3;
					
					for (int y=0;y<nb;y++) {
						for (int x=0;x<nb;x++,cB+=6) {
							
							float tmin = cRay->tmin;
							float tmax = cRay->t;
							if (!intersectBox(cB,cB+3,cRay->from,cRay->dir,tmin,tmax)) {	// TODO: pull out ray t etc to shadows
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
				const float	*r		=	cRay->from;
				const float	*q		=	cRay->dir;
				
				const float	*Pt0	=	levels[level].tesselation->P;
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
				if (rCur*0.5 < requiredR) {
					// downsample 4x4 to 2x2 (not the same as above because we divided
					// in the parametric space here we quads intersect directly
					
					const float	*r		=	cRay->from;
					const float	*q		=	cRay->dir;
					
					const float urg		=	2.0f*(umax - umin) / (float) div;
					const float vrg		=	2.0f*(vmax - vmin) / (float) div;
										
					const int nb = div>>1;
					
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
					
					const float	*r		=	cRay->from;
					const float	*q		=	cRay->dir;
					
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
				if (rCur*0.5 < requiredR) {
					// downsample 8x8 to 4x4 or 16x16 to 8x8
					// 8x8 or 16x16 quads (or greater if 3*maxGridSize allows)
					// we bound-intersect each 2x2 subgrid before intersecting quads
									
					const float	*r		=	cRay->from;
					const float	*q		=	cRay->dir;
					
					const float urg		=	2.0f*(umax - umin) / (float) div;
					const float vrg		=	2.0f*(vmax - vmin) / (float) div;
			
					int nb				=	div>>2;
					
					const float	*Pt0	=	thisTesselation->P;
					const float	*Pt1	=	Pt0+(div+1)*(div+1)*3;
					const float	*cB		=	Pt1+(div+1)*(div+1)*3;
					
					for (int y=0;y<nb;y++) {
						for (int x=0;x<nb;x++,cB += 6) {
							
							float tmin = cRay->tmin;
							float tmax = cRay->t;
							if (!intersectBox(cB,cB+3,cRay->from,cRay->dir,tmin,tmax)) {	// TODO: pull out ray t etc to shadows
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
					
					const float	*r		=	cRay->from;
					const float	*q		=	cRay->dir;
					
					const float urg		=	(umax - umin) / (float) div;
					const float vrg		=	(vmax - vmin) / (float) div;
					
					int nb				=	div>>2;
					
					const float	*Pt0	=	thisTesselation->P;
					const float	*Pt1	=	Pt0+(div+1)*(div+1)*3;
					const float	*cB		=	Pt1+(div+1)*(div+1)*3;
			
					for (int y=0;y<nb;y++) {
						for (int x=0;x<nb;x++,cB += 6) {
							
							float tmin = cRay->tmin;
							float tmax = cRay->t;
							if (!intersectBox(cB,cB+3,cRay->from,cRay->dir,tmin,tmax)) {	// TODO: pull out ray t etc to shadows
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
// Class				:	CSurface
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
// Class				:	CSurface
// Method				:	tesselate
// Description			:	Find the best tesselation for this object
// Return Value			:
// Comments				:
///////////////////////////////////////////////////////////////////////
// Class				:	CSurface
// Method				:	tesselate
// Description			:	Find the best tesselation for this object
// Return Value			:
// Comments				:
CTesselationPatch::CPurgableTesselation*		CTesselationPatch::tesselate(CShadingContext *context,char rdiv,int estimateOnly) {
	// Get some misc variables for fast access
	
	void	*savedState = context->saveState();
	
	float	**varying	=	context->currentShadingState->varying;

	int div = rdiv;
	if (div == 1) div = 2;			// sample() cannot do 1x1, so we do 2x2 and drop down
	
	// Sample points on the patch
	const float	ustep	=	(umax-umin) / (float) div;
	const float	vstep	=	(vmax-vmin) / (float) div;

	// Compute the sample positions and corresponding normal vectors
#define sampleTesselation(sample,time)											\
	{																			\
		float	*uv			=	varying[VARIABLE_U];							\
		float	*vv			=	varying[VARIABLE_V];							\
		float	*timev		=	varying[VARIABLE_TIME];							\
		int		up,vp;															\
		float	u,v;															\
		for (vp=div+1,v=vmin;vp>0;vp--,v+=vstep) {								\
			for (up=div+1,u=umin;up>0;up--,u+=ustep) {							\
				*uv++		=	u;												\
				*vv++		=	v;												\
				*timev++	=	time;											\
			}																	\
		}																		\
		context->displace(object,div+1,div+1,SHADING_2D_GRID,PARAMETER_P | sample | PARAMETER_RAYTRACE);	\
	}
	
	sampleTesselation(PARAMETER_BEGIN_SAMPLE,0);
	
	// At this point, We have the tesselation. So create the grid and return it, or initialize our
	// grid size guess
	
	#if DEBUG_TESSELATIONS > 0
	{
		CDebugView	d("/tmp/tesselate.dat",TRUE);
	
		float *Pcur = varying[VARIABLE_P];
		for (int i =0;i<div;i++) {
			d.line(Pcur,Pcur+3);
			d.line(Pcur+div*(div+1)*3,Pcur+div*(div+1)*3+3);
			Pcur +=3;
		}
		Pcur = varying[VARIABLE_P];
		for (int i =0;i<div;i++) {
			d.line(Pcur,Pcur+(div+1)*3);
			d.line(Pcur+div*3,Pcur+div*3+(div+1)*3);
			Pcur += (div+1)*3;
		}
		#if DEBUG_TESSELATIONS > 2
		Pcur = varying[VARIABLE_P];
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
				
				void	*mem			=	malloc(sizeof(CPurgableTesselation) + sizeof(int)*CRenderer::numThreads + 2*2*3*sizeof(float));
						cTesselation	=	(CPurgableTesselation*) mem;
				
				cTesselation->P							=	(float*) ((char*) mem + sizeof(CPurgableTesselation)+ sizeof(int)*CRenderer::numThreads);
				cTesselation->lastRefNumber				=	(int*)   ((char*) mem + sizeof(CPurgableTesselation));
				cTesselation->size						=	2*2*3*sizeof(float);			
		
				movvv(cTesselation->P,		varying[VARIABLE_P]);
				movvv(cTesselation->P+3,	varying[VARIABLE_P]+6);
				movvv(cTesselation->P+6,	varying[VARIABLE_P]+18);
				movvv(cTesselation->P+9,	varying[VARIABLE_P]+24);
			} else if (rdiv <= 4) {
				// not saving bounds here
				void		*mem			= malloc(sizeof(CPurgableTesselation) + sizeof(int)*CRenderer::numThreads + (div+1)*(div+1)*3*sizeof(float));
							cTesselation	= (CPurgableTesselation*) mem;
	
				cTesselation->P							=	(float*) ((char*) mem + sizeof(CPurgableTesselation) + sizeof(int)*CRenderer::numThreads);
				cTesselation->lastRefNumber				=	(int*)   ((char*) mem + sizeof(CPurgableTesselation));
				cTesselation->size						=	(div+1)*(div+1)*3*sizeof(float);
				
				memcpy(cTesselation->P,varying[VARIABLE_P],(div+1)*(div+1)*3*sizeof(float));
			} else {
				// create bounds, but only if it saves us work later
							
				int nb = div>>2;						// number of bounds in each direction
				
				// save the data
				void		*mem			= malloc(sizeof(CPurgableTesselation) + sizeof(int)*CRenderer::numThreads + (div+1)*(div+1)*3*sizeof(float) + nb*nb*6*sizeof(float));
							cTesselation	= (CPurgableTesselation*) mem;
	
				cTesselation->P							=	(float*) ((char*) mem + sizeof(CPurgableTesselation) + sizeof(int)*CRenderer::numThreads);
				cTesselation->lastRefNumber				=	(int*)   ((char*) mem + sizeof(CPurgableTesselation));
				cTesselation->size						=	((div+1)*(div+1)*3 + nb*nb*6)*sizeof(float);
				
				// FIXME: bounds should be first for cache efficiency
				float *bounds							=	cTesselation->P + (div+1)*(div+1)*3;
				
				memcpy(cTesselation->P,varying[VARIABLE_P],(div+1)*(div+1)*3*sizeof(float));
				
				
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
				
				void	*mem			=	malloc(sizeof(CPurgableTesselation) + sizeof(int)*CRenderer::numThreads + 2*2*2*3*sizeof(float));
						cTesselation	=	(CPurgableTesselation*) mem;
				
				cTesselation->P							=	(float*) ((char*) mem + sizeof(CPurgableTesselation)+ sizeof(int)*CRenderer::numThreads);
				cTesselation->lastRefNumber				=	(int*)   ((char*) mem + sizeof(CPurgableTesselation));
				cTesselation->size						=	2*2*2*3*sizeof(float);
		
				// Save first sample
				movvv(cTesselation->P,		varying[VARIABLE_P]);
				movvv(cTesselation->P+3,	varying[VARIABLE_P]+6);
				movvv(cTesselation->P+6,	varying[VARIABLE_P]+18);
				movvv(cTesselation->P+9,	varying[VARIABLE_P]+24);
				
				// Displace again
				sampleTesselation(PARAMETER_END_SAMPLE,1);
				
				// Copy the second sample
				movvv(cTesselation->P+12,	varying[VARIABLE_P]);
				movvv(cTesselation->P+15,	varying[VARIABLE_P]+6);
				movvv(cTesselation->P+18,	varying[VARIABLE_P]+18);
				movvv(cTesselation->P+21,	varying[VARIABLE_P]+24);
			} else if (rdiv <= 4) {
				// Not saving bounds here
				void		*mem			= malloc(sizeof(CPurgableTesselation) + sizeof(int)*CRenderer::numThreads + 2*(div+1)*(div+1)*3*sizeof(float));
							cTesselation	= (CPurgableTesselation*) mem;
	
				cTesselation->P							=	(float*) ((char*) mem + sizeof(CPurgableTesselation) + sizeof(int)*CRenderer::numThreads);
				cTesselation->lastRefNumber				=	(int*)   ((char*) mem + sizeof(CPurgableTesselation));
				cTesselation->size						=	2*(div+1)*(div+1)*3*sizeof(float);
				
				// Save first sample
				memcpy(cTesselation->P,varying[VARIABLE_P],(div+1)*(div+1)*3*sizeof(float));
				
				// Displace again
				sampleTesselation(PARAMETER_END_SAMPLE,1);
				
				// Save second sample
				memcpy(cTesselation->P+(div+1)*(div+1)*3,varying[VARIABLE_P],(div+1)*(div+1)*3*sizeof(float));
			} else {
				// create bounds, but only if it saves us work later
							
				int nb = div>>2;						// number of bounds in each direction
				
				// save the data
				void		*mem			= malloc(sizeof(CPurgableTesselation) + sizeof(int)*CRenderer::numThreads + 2*(div+1)*(div+1)*3*sizeof(float) + nb*nb*6*sizeof(float));
							cTesselation	= (CPurgableTesselation*) mem;
	
				cTesselation->P							=	(float*) ((char*) mem + sizeof(CPurgableTesselation) + sizeof(int)*CRenderer::numThreads);
				cTesselation->lastRefNumber				=	(int*)   ((char*) mem + sizeof(CPurgableTesselation));
				cTesselation->size						=	(2*(div+1)*(div+1)*3 + nb*nb*6)*sizeof(float);
				
				// FIXME: bounds should be first for cache efficiency
				float *bounds							=	cTesselation->P + 2*(div+1)*(div+1)*3;
				
				// Save the first sample
				memcpy(cTesselation->P,varying[VARIABLE_P],(div+1)*(div+1)*3*sizeof(float));
				
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
				sampleTesselation(PARAMETER_END_SAMPLE,1);
				
				// Save the second sample
				memcpy(cTesselation->P+(div+1)*(div+1)*3,varying[VARIABLE_P],(div+1)*(div+1)*3*sizeof(float));
				
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
		
		context->restoreState(savedState);
		
		// install tesselation last so other threads don't use bounds/P before they're ready
		return cTesselation;

	}
	
	// If we get here, we are estimating only
	
	// Evaluate the quality of this tesselation in u and v separately
	float	vMax	=	0;
	float	vAvg	=	0;
	for (int i=0;i<=div;i++) {
		const float	l	=	measureLength(varying[VARIABLE_P] + i*3,(div+1)*3,div);
		vMax			=	max(vMax,l);
		vAvg			+=	l;
	}

	float	uMax	=	0;
	float	uAvg	=	0;
	for (int i=0;i<=div;i++) {
		const float	l	=	measureLength(varying[VARIABLE_P] + i*(div+1)*3,3,div);
		uMax			=	max(uMax,l);
		uAvg			+=	l;
	}

	vAvg	/=	(float) (div+1)*div;
	uAvg	/=	(float) (div+1)*div;
	
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

	float *Pcur = varying[VARIABLE_P];
	for (int i =(div+1)*(div+1);i>0;i--) {
		addBox(bmin,bmax,Pcur);
		Pcur			+=	3;
	}
	
	// If we have motion, account for it
	if (flags & OBJECT_MOVING_TESSELATION) {
		// Displace again
		sampleTesselation(PARAMETER_END_SAMPLE,1);
		
		// Bound the second sample
		Pcur = varying[VARIABLE_P];
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
	const int udiv = 16;
	const int vdiv = 16;
	
	float	**varying	=	context->currentShadingState->varying;

	const float	ustep	=	(umax-umin) / (float) udiv;
	const float	vstep	=	(vmax-vmin) / (float) vdiv;

	// sanity check before dividing
	if(umin>= umax || vmin>= vmax) {
		return;
	}

	// Compute the new patch parameteric splits
	
	int		cu,cv;
	float	u,v;

	float *us = (float*) alloca(sizeof(float)*((udiv+1) + (vdiv+1)));	// don't use varyings as tesselate will smash them
	float *vs = us + (udiv+1);
	
	
	float	*vv			=	vs;
	for (cv=0,v=vmin;cv<vdiv+1;cv++,v+=vstep) {
		*vv++		=	v;
	}
	float	*uv			=	us;
	for (cu=0,u=umin;cu<udiv+1;cu++,u+=ustep) {
		*uv++		=	u;
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
			osLock(CRenderer::refCountMutex);
			CTesselationPatch *cPatch = new CTesselationPatch(attributes,xform,object,uv[0],uv[1],vv[0],vv[1],depth+1,minDepth,-1);
			osUnlock(CRenderer::refCountMutex);
			
			cPatch->tesselate(context,16,TRUE);
			cPatch->sibling = subPatches;
			subPatches = cPatch;
		}
	}
	
	// attach them
	setChildren(context,subPatches);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CSurface
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
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSurface
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
}

///////////////////////////////////////////////////////////////////////
// Function				:	tesselationQuickSort
// Description			:	Sort the tesselations in the order of increasing last ref number
// Return Value			:
// Comments				:
void	CTesselationPatch::tesselationQuickSort(CTesselationEntry **activeTesselations,int start,int end,int thread) {
	int					i,last;
	CTesselationEntry	*cTess;

	for (last=start,i=start+1;i<=end;i++) {
		if (activeTesselations[i]->tesselation->lastRefNumber[thread] < activeTesselations[start]->tesselation->lastRefNumber[thread]) {
			last++;
			cTess						=	activeTesselations[last];
			activeTesselations[last]	=	activeTesselations[i];
			activeTesselations[i]		=	cTess;
		}
	}

	cTess						=	activeTesselations[last];
	activeTesselations[last]	=	activeTesselations[start];
	activeTesselations[start]	=	cTess;

	// Speed is not an issue since this is not done very frequently, so recursion is OK
	if ((last-1) > start)
		tesselationQuickSort(activeTesselations,start,last-1,thread);

	if (end > (last+1))
		tesselationQuickSort(activeTesselations,last+1,end,thread);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CSurface
// Method				:	purgeTesselations
// Description			:	purge tesselations of level from thread
// Return Value			:
// Comments				:
void		CTesselationPatch::purgeTesselations(CShadingContext *context,int thread,int level,int all) {
	// Do we have stuff to free ?
	if (tesselationList == NULL)	return;

	// Ensure no other thread creates new tesselations whilst we flush
	#ifdef TESSELATION_LOCK_PER_ENTRY
		osLock(CRenderer::tesselateMutex);
	#endif
	
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
			activeTesselations[i++]	=	&cPatch->levels[level];
		}
	}
	
	// Sort the tesselations from last used to the most recently used
	if (i > 1)	tesselationQuickSort(activeTesselations,0,i-1,thread);

	// Free the memory
	if (all)	tesselationMaxMemory[level]	=	0;
	for (j=0;(j<i) && (tesselationUsedMemory[level][thread] > (tesselationMaxMemory[level]/2));j++) {
		cTess									=	activeTesselations[j];

		tesselationUsedMemory[level][thread]	-=	cTess->tesselation->size;
		cTess->threadTesselation[thread]		=	NULL;
		
		#ifdef TESSELATION_LOCK_PER_ENTRY
			osLock(cTess->mutex);
		#endif
		
		if (--cTess->refCount == 0) {
			stats.tesselationMemory				-=	cTess->tesselation->size;
			
			free((unsigned char *) cTess->tesselation);
			cTess->tesselation						=	NULL;
		}
		
		#ifdef TESSELATION_LOCK_PER_ENTRY
			osUnlock(cTess->mutex);
		#endif

	}
	
	#ifdef TESSELATION_LOCK_PER_ENTRY
		osUnlock(CRenderer::tesselateMutex);
	#endif
}

