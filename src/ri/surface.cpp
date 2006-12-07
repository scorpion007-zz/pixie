//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright © 1999 - 2003, Okan Arikan
//
// Contact: okan@cs.berkeley.edu
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
// 
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
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
		vector					bmin,bmax,D;
		float					Pmov[4*3];
		float					maxBound;
		float					dx,dy;
		float					*P;
		float					rasterExpand;
		int						numUprobes;
		int						numVprobes;
		int						up,vp;
		float					**varying;
		int						k;
		float					*uv;
		float					*vv;
		float					*timev;
		int						disableCull;
		int						cullFlags	=	TRUE;
		
		// We need to split this patch, so no need to compute udiv / vdiv

		// Get some misc variables for fast access
		disableCull		=	attributes->flags & ATTRIBUTES_FLAGS_SHADE_BACKFACE;
		rasterExpand	=	attributes->rasterExpand;
		numUprobes		=	attributes->numUProbes;
		numVprobes		=	attributes->numVProbes;
		varying			=	r->currentShadingState->varying;

		// Sample points on the patch
		double	ustart	=	umin;
		double	vstart	=	vmin;
		double	ustep	=	(umax - ustart) / (double) (numUprobes-1);
		double	vstep	=	(vmax - vstart) / (double) (numVprobes-1);
		double	u,v;

		uv				=	varying[VARIABLE_U];
		vv				=	varying[VARIABLE_V];
		timev			=	varying[VARIABLE_TIME];

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
			r->displace(object,numUprobes,numVprobes,SHADING_2D_GRID,PARAMETER_P | PARAMETER_N | PARAMETER_END_SAMPLE);
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
		maxBound		*=	rasterExpand;
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
			int		i1			=	0;								// Index of the top left
			int		i2			=	numUprobes-1;					// Index of the top right
			int		i3			=	numVprobes*numUprobes-1;		// Index of the bottom right
			int		i4			=	(numVprobes-1)*numUprobes;		// Index of the bottom left
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

			umLength		=	(uLength[0]+uLength[1]) / (float) 2;// The length of the u and v extremal edges
			vmLength		=	(vLength[0]+vLength[1]) / (float) 2;

			umLength		=	min(umLength,1000);					// FIXME: This is really ugly
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
		umid			=	(umin + umax) / (float) 2;
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
		vmid			=	(vmin + vmax) / (float) 2;
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
		vmid			=	(vmin + vmax) / (float) 2;
		umid			=	(umin + umax) / (float) 2;
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








//FIXMES:
/*
make r,ru,rv guesses constructor params
remove minDepth stuff
remove udiv,vdiv
support untesselation
	mutex per patch?

*/




///////////////////////////////////////////////////////////////////////
// Class				:	CPatch
// Method				:	CPatch
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CTesselationPatch::CTesselationPatch(CAttributes *a,CXform *x,CSurface *o,float umin,float umax,float vmin,float vmax,char depth,char minDepth,float r) : CObject(a,x) {
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
	
	tesselations[0] =
	tesselations[1]	=
	tesselations[2]	=	NULL;
	
	this->rmax		=	r;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPatch
// Method				:	~CPatch
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CTesselationPatch::~CTesselationPatch() {
	// clean up tesselations
	for(int i=0;i<3;i++) {
		if (tesselations[i] == NULL) delete tesselations[i];
	}
}

void	CTesselationPatch::intersect(CShadingContext *context,CRay *cRay) {

	// check the ray conditions before proceeding
	
	if (! (cRay->flags & attributes->flags) )	return;

	if (attributes->flags & ATTRIBUTES_FLAGS_LOD) {
		const float importance = attributes->lodImportance;
		if (importance >= 0) {
			if (cRay->jimp > importance)			return;
		} else {
			if ((1-cRay->jimp) >= -importance)		return;
		}
	}
	
	// intersect with our bounding box
	float t = nearestBox(bmin,bmax,cRay->from,cRay->dir,cRay->tmin,cRay->t);
	
	// bail out if the hit point is already further than the ray got
	if (!(t < cRay->t)) return;
	
	float requiredR = cRay->da * t + cRay->db;
	//requiredR*=8;

	// bail very early if this ray should have been handled by a coarser (parent)
	// CTesselationPatch
	
	if (rmax*2.0f < requiredR && depth > 0) {
		// something else should have dealt with this
		return;
	}
		
	// find a tesselation level
	float	rCur	=	rmax;
	int		div		=	1;
	int		level	=	0;
	for (level=0;level<3;level++) {
		if (rCur < requiredR) {
			break;
		}
		rCur	*=	0.25;
		div		=	div<<2;
	}
	
	#if 0
		// HACK - dissallow recursive splitting
		if (level == 3)	{
			level = 2;
			rCur = rmax/16.0f;
			div = 16;
		}
	#endif
	
	#if 0
		//HACK for testing
		level = 2;
		rCur = rmax/16.2;
		div = 16;
	#endif
		
	// did we find one?
	if (level < 3) {
		// r for level is sufficient. verify we have a tesselation
		
	//	fprintf(stderr,"got level %d %f\n",level,rCur);
		
		//osLock(CRenderer::tesselateMutex);
		
		if (tesselations[level] == NULL) {
			osLock(CRenderer::tesselateMutex);
			
			if (tesselations[level] == NULL) {
				tesselations[level] = tesselate(context,div,FALSE);
			}
			
			osUnlock(CRenderer::tesselateMutex);
		}
		
		// Intersect the ray
	
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
									cRay->t			=	(float) t;				\
									movvv(cRay->N,N);							\
								}												\
							} else {											\
								cRay->object	=	object;						\
								cRay->u			=	umin + ((float) u + i)*urg;	\
								cRay->v			=	vmin + ((float) v + j)*vrg;	\
								cRay->t			=	(float) t;					\
								movvv(cRay->N,N);								\
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
		
		
		if (div == 1) {
			const float	*r		=	cRay->from;
			const float	*q		=	cRay->dir;
		
			const float	*P00	=	tesselations[level]->P;
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
				
				const float	*cP		=	tesselations[level]->P;
				
				const int nb = div>>1;
				
				for (int j=0;j<nb;j++) {
					for (int i=0;i<nb;i++,cP += 6) {
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
				
				const float	*cP		=	tesselations[level]->P;
		
				for (int j=0;j<div;j++) {
					for (int i=0;i<div;i++,cP += 3) {
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
				
				//fprintf(stderr,"%f %f %f (%d %d)\n",r,requiredR,r/requiredR,udiv,vdiv);
				
				const float	*r		=	cRay->from;
				const float	*q		=	cRay->dir;
				
				const float urg		=	2.0f*(umax - umin) / (float) div;
				const float vrg		=	2.0f*(vmax - vmin) / (float) div;
		
				const float	*P		=	tesselations[level]->P;
				const float	*cB		=	P+(div+1)*(div+1)*3;
		
				int nb				=	div>>2;
				
				for (int y=0;y<nb;y++) {
					for (int x=0;x<nb;x++,cB += 6) {
						
						float tmin = cRay->tmin;
						float tmax = cRay->t;
						if (!intersectBox(cB,cB+3,cRay->from,cRay->dir,tmin,tmax)) {	// pull out ray t etc to shadows
							continue;
						}
						
						const float	*cP	=	P + (x*4 + y*4*(div+1))*3;
		
						for (int cj=0;cj<2;cj++) {
							for (int ci=0;ci<2;ci++,cP += 6) {
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
		
				const float	*P		=	tesselations[level]->P;
				const float	*cB		=	P+(div+1)*(div+1)*3;
		
				int nb				=	div>>2;
				
				for (int y=0;y<nb;y++) {
					for (int x=0;x<nb;x++,cB += 6) {
						
						float tmin = cRay->tmin;
						float tmax = cRay->t;
						if (!intersectBox(cB,cB+3,cRay->from,cRay->dir,tmin,tmax)) {	// pull out ray t etc to shadows
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
		if (children == NULL) {
			osLock(CRenderer::hierarchyMutex);
			
			if (children != NULL) {
				osUnlock(CRenderer::hierarchyMutex);
				return;
			}
	
			// we have no sufficient level, split to children.  Let them deal with it
			splitToChildren(context);

			osUnlock(CRenderer::hierarchyMutex);
		}
	}

	
	//osUnlock(CRenderer::tesselateMutex);
	
}



///////////////////////////////////////////////////////////////////////
// Function				:	checkAngle
// Description			:	This function takes P and returns the cosine of the minimum angle deviation
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


#include "debug.h"


///////////////////////////////////////////////////////////////////////
// Class				:	CSurface
// Method				:	tesselate
// Description			:	Find the best tesselation for this object
// Return Value			:
// Comments				:
CTesselationPatch::CSubTesselation*		CTesselationPatch::tesselate(CShadingContext *context,char rdiv,int estimateOnly) {
	// Get some misc variables for fast access
	float	**varying	=	context->currentShadingState->varying;

	int div = rdiv;
	if (div == 1) div = 2;


//	This should now be guaranteed	
//	if((udiv+1)*(vdiv+1) > CRenderer::maxGridSize) {
//		udiv	=	udiv>>1;
//		vdiv	=	vdiv>>1;
//	}
	
//	if(!estimateOnly) fprintf(stderr,"tesselate %d - %d\n",depth,rdiv);

	// Sample points on the patch
	const float	ustep	=	(umax-umin) / (float) div;
	const float	vstep	=	(vmax-vmin) / (float) div;

	// Compute the sample positions and corresponding normal vectors
	float	*uv			=	varying[VARIABLE_U];
	float	*vv			=	varying[VARIABLE_V];
	float	*timev		=	varying[VARIABLE_TIME];
	int		up,vp;
	float	u,v;
	for (vp=div+1,v=vmin;vp>0;vp--,v+=vstep) {
		for (up=div+1,u=umin;up>0;up--,u+=ustep) {
			*uv++		=	u;
			*vv++		=	v;
			*timev++	=	0;
		}
	}
	context->displace(object,div+1,div+1,SHADING_2D_GRID,PARAMETER_P | PARAMETER_N | PARAMETER_BEGIN_SAMPLE);
	
	// Evaluate the quality of this tesselation in u and v separately
	int		i;
	float	vMax	=	0;
	float	vAvg	=	0;
	for (i=0;i<=div;i++) {
		const float	l	=	measureLength(varying[VARIABLE_P] + i*3,(div+1)*3,div);
		vMax			=	max(vMax,l);
		vAvg			+=	l;
	}

	float	uMax	=	0;
	float	uAvg	=	0;
	for (i=0;i<=div;i++) {
		const float	l	=	measureLength(varying[VARIABLE_P] + i*(div+1)*3,3,div);
		uMax			=	max(uMax,l);
		uAvg			+=	l;
	}

	vAvg	/=	(float) (div+1)*div;
	uAvg	/=	(float) (div+1)*div;
		
	// At this point, I should have the tesselation. So create the grid and return it
	
	
	#if 0
	{
		CDebugView	d("/tmp/tesselate.dat",TRUE);
	
		float *Pcur = varying[VARIABLE_P];
		for (int i =0;i<div;i++) {
			d.line(Pcur,Pcur+3);
			d.line(Pcur+(div+1)*3,Pcur+(div+1)*3+3);
			Pcur +=3;
		}
		Pcur = varying[VARIABLE_P];
		for (int i =0;i<div;i++) {
			d.line(Pcur,Pcur+(div+1)*3);
			d.line(Pcur+div*3,Pcur+div*3+(div+1)*3);
			Pcur += (div+1)*3;
		}
		Pcur = varying[VARIABLE_P];
		for (int i =(div+1)*(div+1);i>0;i--) {
			d.point(Pcur);
		}
	}
	#endif
	
	
	// This controls how much we overestimate bounds of both the grid, and
	// sub-parts of the grid.  Setting this high hurts performance
	//const float boundExpander = attributes->rasterExpand;
	const float boundExpander = 0.1f;

	// create P if it is so required
	if (!estimateOnly) {
		
		if (rdiv == 1) {
			// subsampling our 2x2 to 1x1, no bounds
			
			void			*mem			=	malloc(sizeof(CSubTesselation) + 2*2*3*sizeof(float));
			CSubTesselation	*cTesselation	=	(CSubTesselation*) mem;
			
			cTesselation->P					=	(float*) ((char*) mem + sizeof(CSubTesselation));
			cTesselation->size				=	2*2*3*sizeof(float);			
			cTesselation->lastRefNumber		=	-1;
			//rmax							=	max(rmax,(uAvg+vAvg)/4.0f);	// we're subsampling
	
			movvv(cTesselation->P,		varying[VARIABLE_P]);
			movvv(cTesselation->P+3,	varying[VARIABLE_P]+6);
			movvv(cTesselation->P+6,	varying[VARIABLE_P]+18);
			movvv(cTesselation->P+9,	varying[VARIABLE_P]+24);
			
			// install tesselation last so other threads don't use bounds/P before they're ready
			return cTesselation;
			
		} else if (rdiv <= 4) {
			// not saving bounds here
			void				*mem			= malloc(sizeof(CSubTesselation) + (div+1)*(div+1)*3*sizeof(float));
			CSubTesselation		*cTesselation	= (CSubTesselation*) mem;

			cTesselation->P						=	(float*) ((char*) mem + sizeof(CSubTesselation));
			cTesselation->size					=	(div+1)*(div+1)*3*sizeof(float);
			cTesselation->lastRefNumber			=	-1;
			//rmax								=	max(rmax,div*(uAvg+vAvg)/2.0f);
			
			memcpy(cTesselation->P,varying[VARIABLE_P],(div+1)*(div+1)*3*sizeof(float));
			
			// install tesselation last so other threads don't use bounds/P before they're ready
			return cTesselation;
		} else {
			// create bounds, but only if it saves us work later
						
			int nb = div>>2;		// number of bounds in each direction
			
			// save off the data
			
			void				*mem			= malloc(sizeof(CSubTesselation) + (div+1)*(div+1)*3*sizeof(float) + nb*nb*6*sizeof(float));
			CSubTesselation		*cTesselation	= (CSubTesselation*) mem;

			cTesselation->P						=	(float*) ((char*) mem + sizeof(CSubTesselation));
			cTesselation->size					=	((div+1)*(div+1)*3 + nb*nb*6)*sizeof(float);
			cTesselation->lastRefNumber			=	-1;
			//rmax								=	max(rmax,div*(uAvg+vAvg)/2.0f);
			
			float *bounds						=	cTesselation->P + (div+1)*(div+1)*3;
			
			memcpy(cTesselation->P,varying[VARIABLE_P],(div+1)*(div+1)*3*sizeof(float));
			
			
			// clear them
			float *bnds = bounds;
			for (i=0;i<nb*nb;i++,bnds+=6) {
				initv(bnds,C_INFINITY);
				initv(bnds+3,-C_INFINITY);
			}
			
			// sum them
			bnds = bounds;
			for (int y=0;y<nb;y++) {
				for (int x=0; x<nb;x++,bnds+=6) {
					const float *cP		=	cTesselation->P + (x*4 + y*4*(div+1))*3;
				
					for (i=0;i<5;i++) {
						for (int j=0;j<5;j++,cP+=3) {
							addBox(bnds,bnds+3,cP);
						}
						cP += ((div+1)-5)*3;
					}
				}
			}
			
			// expand them
			bnds = bounds;
			for(i=0;i<nb*nb;i++){
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
			
			// install tesselation last so other threads don't use bounds/P before they're ready
			return cTesselation;
		}
	}
	
	// simply save the coarse r estimate
	if (rdiv == 1) {
		rmax							=	max(rmax,(uAvg+vAvg)/4.0f);	// we're subsampling
	} else {
		rmax							=	max(rmax,div*(uAvg+vAvg)/2.0f);
	}
	
	// save a tighter bound
	initv(bmin,C_INFINITY);
	initv(bmax,-C_INFINITY);

	float *Pcur = varying[VARIABLE_P];
	for (int i =(div+1)*(div+1);i>0;i--) {
		addBox(bmin,bmax,Pcur);
		Pcur			+=	3;
	}
	
	float maxBound	=	max(bmax[COMP_X]-bmin[COMP_X],bmax[COMP_Y]-bmin[COMP_Y]);
	maxBound		=	max(bmax[COMP_Z]-bmin[COMP_Z],maxBound);
	maxBound		*=	boundExpander;

	bmin[COMP_X]	-=	maxBound;
	bmin[COMP_Y]	-=	maxBound;
	bmin[COMP_Z]	-=	maxBound;
	bmax[COMP_X]	+=	maxBound;
	bmax[COMP_Y]	+=	maxBound;
	bmax[COMP_Z]	+=	maxBound;
	
	return NULL;
}

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
			CTesselationPatch *cPatch = new CTesselationPatch(attributes,xform,object,uv[0],uv[1],vv[0],vv[1],depth+1,minDepth,-1);
			cPatch->tesselate(context,16,TRUE);
			cPatch->sibling = subPatches;
			subPatches = cPatch;
		}
	}
	
	// attach them
	setChildren(context,subPatches);
}
