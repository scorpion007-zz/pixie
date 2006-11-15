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
// Date last edited		:	4/7/2006
static inline float	minCocPixels(float z1, float z2) {
	return min(cocPixels(z1),cocPixels(z2));
}



///////////////////////////////////////////////////////////////////////
// Class				:	CPatch
// Method				:	CPatch
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	6/4/2003
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
// Date last edited		:	6/4/2003
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
// Date last edited		:	6/4/2003
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
		float					u,v;
		float					ustep,vstep;
		float					ustart,vstart;
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
		ustart			=	umin;
		vstart			=	vmin;
		ustep			=	(umax - ustart) / (float) (numUprobes-1);
		vstep			=	(vmax - vstart) / (float) (numVprobes-1);

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
					uv[k]		=	u;
					vv[k]		=	v;
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
				uv[k]		=	u;
				vv[k]		=	v;
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
// Date last edited		:	6/4/2003
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
// Date last edited		:	6/4/2003
CTesselationPatch::CTesselationPatch(CAttributes *a,CXform *x,CSurface *o,float umin,float umax,float vmin,float vmax,int depth,int minDepth) : CObject(a,x) {
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
	movvv(this->bmin,o->bmin);
	movvv(this->bmax,o->bmax);
	
	this->ru		=
		this->rv	=
		this->r 	=	C_INFINITY;
	
	this->P = NULL;
	this->subTesselations[0]	= 
		this->subTesselations[1] = 
		this->subTesselations[2] = 
		this->subTesselations[3] = NULL;
	numTesselations = 0;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPatch
// Method				:	~CPatch
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	6/4/2003
CTesselationPatch::~CTesselationPatch() {
	// clean up tesselations
	delete[] P;
	for (int i=0;i<numTesselations;i++)	{
		delete subTesselations[i]; 
	}
}

void	CTesselationPatch::intersect(CShadingContext *context,CRay *cRay,float requiredR) {

#if 0		
	// trivially reject using bounds	
	if(P != NULL && depth > 1) {	// FIXME: convert P!=NULL to check if we've been tesselated ever
		// Only do so for tesselations > 2 deep, others will be too coarse
		// FIXME: we should do better here
		float tmin = cRay->tmin;
		float tmax = cRay->t;
		if (!intersectBox(bmin,bmax,cRay->from,cRay->dir,tmin,tmax)) return;
	}
#endif

	// recurse if r is insufficient
	if (r > 2*requiredR && depth < 10) {	// FIXME: make this a user controllable parameter
		// Make subtesselations if they don't exist
		
		if (numTesselations == 0) {
			osLock(CRenderer::tesselateMutex);

			if (numTesselations == 0) {
				if (ru > 2*rv) {
					// dice u 1st
					float umid				=	(umin + umax) / (float) 2;
					subTesselations[0]		=	new CTesselationPatch(attributes,xform,object,umin,umid,vmin,vmax,depth+1,minDepth);
					subTesselations[1]		=	new CTesselationPatch(attributes,xform,object,umid,umax,vmin,vmax,depth+1,minDepth);
					subTesselations[0]->ru	=	ru/2.0f;	// we'll calculate this again on tesselation
					subTesselations[0]->rv	=	rv;
					subTesselations[0]->r	=	r/2.0f;
					subTesselations[1]->ru	=	ru/2.0f;
					subTesselations[1]->rv	=	rv;
					subTesselations[1]->r	=	r/2.0f;
					numTesselations			=	2;
					//fprintf(stderr," US %f %f %f\n",ru/2.0f,rv,r/2.0f);
				} else if (rv > 2*ru) {
					// dice v 1st
					float vmid				=	(vmin + vmax) / (float) 2;
					subTesselations[0]		=	new CTesselationPatch(attributes,xform,object,umin,umax,vmin,vmid,depth+1,minDepth);
					subTesselations[1]		=	new CTesselationPatch(attributes,xform,object,umin,umax,vmid,vmax,depth+1,minDepth);
					subTesselations[0]->ru	=	ru;			// we'll calculate this again on tesselation
					subTesselations[0]->rv	=	rv/2.0f;
					subTesselations[0]->r	=	r/2.0f;
					subTesselations[1]->ru	=	ru;
					subTesselations[1]->rv	=	rv/2.0f;
					subTesselations[1]->r	=	r/2.0f;
					numTesselations			=	2;
					//fprintf(stderr," VS %f %f %f\n",ru,rv/2.0f,r/2.0f);
				} else {
					// dice both
					float umid				=	(umin + umax) / (float) 2;
					float vmid				=	(vmin + vmax) / (float) 2;
					subTesselations[0]		=	new CTesselationPatch(attributes,xform,object,umin,umid,vmin,vmid,depth+1,minDepth);
					subTesselations[1]		=	new CTesselationPatch(attributes,xform,object,umid,umax,vmin,vmid,depth+1,minDepth);
					subTesselations[2]		=	new CTesselationPatch(attributes,xform,object,umid,umax,vmid,vmax,depth+1,minDepth);
					subTesselations[3]		=	new CTesselationPatch(attributes,xform,object,umin,umid,vmid,vmax,depth+1,minDepth);
					subTesselations[0]->ru	=	ru/2.0f;		// we'll calculate this again on tesselation
					subTesselations[0]->rv	=	rv/2.0f;
					subTesselations[0]->r	=	r/2.0f;
					subTesselations[1]->ru	=	ru/2.0f;
					subTesselations[1]->rv	=	rv/2.0f;
					subTesselations[1]->r	=	r/2.0f;
					subTesselations[2]->ru	=	ru/2.0f;
					subTesselations[2]->rv	=	rv/2.0f;
					subTesselations[2]->r	=	r/2.0f;
					subTesselations[3]->ru	=	ru/2.0f;
					subTesselations[3]->rv	=	rv/2.0f;
					subTesselations[3]->r	=	r/2.0f;
					numTesselations			=	4;
					//fprintf(stderr," BS %f %f %f\n",ru/2.0f,rv/2.0f,r/2.0f);
				}
			}
			
			osUnlock(CRenderer::tesselateMutex);
		}
		
		// test the subtesselations
		
		for(int i=0;i<numTesselations;i++) {
			subTesselations[i]->intersect(context,cRay,r);
		}
		return;
	}
	
	// Our r is sufficient. verify we have P
	
	//osLock(CRenderer::tesselateMutex);
	
	if (P == NULL) {
		osLock(CRenderer::tesselateMutex);
		
		if (P == NULL) {
			tesselate(context,TRUE);
		}
		
		osUnlock(CRenderer::tesselateMutex);
	}
	
	// Intersect the ray
	
	int			i,j;
	const float	*cP		=	P;
	const float *cB		=	bounds;
	const float	*r		=	cRay->from;
	const float	*q		=	cRay->dir;
	
	float urg = (umax - umin) / (float) udiv;
	float vrg = (vmax - vmin) / (float) vdiv;

	// FIXME: pull udiv and vdiv out to constants so we can really get this unrolled
	for (j=0;j<vdiv;j++) {
		for (i=0;i<udiv;i++,cP += 3,cB += 6) {
		
			// quick-reject bounds
			float tmin = cRay->tmin;
			float tmax = cRay->t;
			if (!intersectBox(cB,cB+3,cRay->from,cRay->dir,tmin,tmax)) {
				continue;
			}

			const float	*P00	=	cP;
			const float	*P10	=	cP + 3;
			const float	*P01	=	cP + (udiv+1)*3;
			const float	*P11	=	P01 + 3;
			
			vector		a,b,c,d;

			subvv(a,P11,P10);
			subvv(a,P01);
			addvv(a,P00);
			subvv(b,P10,P00);
			subvv(c,P01,P00);
			movvv(d,P00);

			const double	A1	=	a[COMP_X]*q[COMP_Z] - a[COMP_Z]*q[COMP_X];
			const double	B1	=	b[COMP_X]*q[COMP_Z] - b[COMP_Z]*q[COMP_X];
			const double	C1	=	c[COMP_X]*q[COMP_Z] - c[COMP_Z]*q[COMP_X];
			const double	D1	=	(d[COMP_X] - r[COMP_X])*q[COMP_Z] - (d[COMP_Z] - r[COMP_Z])*q[COMP_X];
			const double	A2	=	a[COMP_Y]*q[COMP_Z] - a[COMP_Z]*q[COMP_Y];
			const double	B2	=	b[COMP_Y]*q[COMP_Z] - b[COMP_Z]*q[COMP_Y];
			const double	C2	=	c[COMP_Y]*q[COMP_Z] - c[COMP_Z]*q[COMP_Y];
			const double	D2	=	(d[COMP_Y] - r[COMP_Y])*q[COMP_Z] - (d[COMP_Z] - r[COMP_Z])*q[COMP_Y];
			


		#define solve()														\
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
			


			double			roots[2];
			double			u,v,t;
			switch (solveQuadric<double>(A2*C1 - A1*C2,A2*D1 - A1*D2 + B2*C1 - B1*C2,B2*D1 - B1*D2,roots)) {
				case 0:
					break;
				case 1:
					v	=	roots[0];
					solve();
					break;
				case 2:
					v	=	roots[0];
					solve();
					v	=	roots[1];
					solve();
					break;
			}

		}

		cP += 3;
	}
	
	//osUnlock(CRenderer::tesselateMutex);
}



///////////////////////////////////////////////////////////////////////
// Function				:	checkAngle
// Description			:	This function takes P and returns the cosine of the minimum angle deviation
// Return Value			:
// Comments				:
// Date last edited		:	10/16/2001
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
// Date last edited		:	10/16/2001
void			CTesselationPatch::tesselate(CShadingContext *context,int saveP) {
	// Get some misc variables for fast access
	float	**varying	=	context->currentShadingState->varying;

	// Start with a 3x3 sampling grid
	udiv		=	4;
	vdiv		=	4;
	
if(depth>1) fprintf(stderr,"%d\n",depth);

	// Sample points on the patch
	const float	ustep	=	(umax-umin) / (float) (udiv);
	const float	vstep	=	(vmax-vmin) / (float) (vdiv);

	// Compute the sample positions and corresponding normal vectors
	float	*uv			=	varying[VARIABLE_U];
	float	*vv			=	varying[VARIABLE_V];
	float	*timev		=	varying[VARIABLE_TIME];
	int		up,vp;
	float	u,v;
	for (vp=vdiv+1,v=vmin;vp>0;vp--,v+=vstep) {
		for (up=udiv+1,u=umin;up>0;up--,u+=ustep) {
			*uv++		=	u;
			*vv++		=	v;
			*timev++	=	0;
		}
	}
	context->displace(object,udiv+1,vdiv+1,SHADING_2D_GRID,PARAMETER_P | PARAMETER_N | PARAMETER_BEGIN_SAMPLE);
	
	// Evaluate the quality of this tesselation in u and v separately
	int		i;
	float	vMax	=	0;
	float	vAvg	=	0;
	for (i=0;i<=udiv;i++) {
		const float	l	=	measureLength(varying[VARIABLE_P] + i*3,(udiv+1)*3,vdiv);
		vMax			=	max(vMax,l);
		vAvg			+=	l;
	}

	float	uMax	=	0;
	float	uAvg	=	0;
	for (i=0;i<=vdiv;i++) {
		const float	l	=	measureLength(varying[VARIABLE_P] + i*(udiv+1)*3,3,udiv);
		uMax			=	max(uMax,l);
		uAvg			+=	l;
	}

	vAvg	/=	(float) (udiv+1)*vdiv;
	uAvg	/=	(float) (vdiv+1)*udiv;
		
	// At this point, I should have the tesselation. So create the grid and return it
	
	//if((uAvg+vAvg)/2.0 > 2*this->r && depth > 0) fprintf(stderr,"tesselationm underreduction %f %f %d\n",(uAvg+vAvg)/2.0f,this->r,depth);
	
	lastRefNumber			=	-1;
	this->ru				=	uAvg;
	this->rv				=	vAvg;
	this->r					=	(ru+rv)/2;
	//fprintf(stderr,"%f %f %f\n",ru,rv,r);
	
	#if 0
	{
		CDebugView	d("/tmp/tesselate.dat",TRUE);
	
		float *Pcur = varying[VARIABLE_P];
		for (int i =0;i<vdiv;i++) {
			d.line(Pcur,Pcur+3);
			d.line(Pcur+(udiv+1)*3,Pcur+(udiv+1)*3+3);
			Pcur +=3;
		}
		Pcur = varying[VARIABLE_P];
		for (int i =0;i<udiv;i++) {
			d.line(Pcur,Pcur+(vdiv+1)*3);
			d.line(Pcur+udiv*3,Pcur+udiv*3+(vdiv+1)*3);
			Pcur += (vdiv+1)*3;
		}
		Pcur = varying[VARIABLE_P];
		for (int i =(vdiv+1)*(udiv+1);i>0;i--) {
			d.point(Pcur);
		}
	}
	#endif
	
	// save a tighter bound
	initv(bmin,C_INFINITY);
	initv(bmax,-C_INFINITY);

	float *Pcur = varying[VARIABLE_P];
	for (int i =(vdiv+1)*(udiv+1);i>0;i--) {
		addBox(bmin,bmax,Pcur);
		Pcur			+=	3;
	}
	
	float maxBound	=	max(bmax[COMP_X]-bmin[COMP_X],bmax[COMP_Y]-bmin[COMP_Y]);
	maxBound		=	max(bmax[COMP_Z]-bmin[COMP_Z],maxBound);
	maxBound		*=	attributes->rasterExpand;

	bmin[COMP_X]	-=	maxBound;
	bmin[COMP_Y]	-=	maxBound;
	bmin[COMP_Z]	-=	maxBound;
	bmax[COMP_X]	+=	maxBound;
	bmax[COMP_Y]	+=	maxBound;
	bmax[COMP_Z]	+=	maxBound;

	// create P if it is so required
	if (saveP) {
		P						=	new float[(udiv+1)*(vdiv+1)*3 + udiv*vdiv*6];
		bounds					=	P + (udiv+1)*(vdiv+1)*3;
		size					=	(udiv+1)*(vdiv+1)*3*sizeof(float) + udiv*vdiv*6*sizeof(float);
		
		memcpy(P,varying[VARIABLE_P],(udiv+1)*(vdiv+1)*3*sizeof(float));
		
		float *Pcur = P;
		float *bnds = bounds;
		
		for (i=0;i<vdiv;i++) {
			for (int j=0;j<udiv;j++) {
				initv(bnds,C_INFINITY);
				initv(bnds+3,-C_INFINITY);
				
				addBox(bnds,bnds+3,Pcur);
				addBox(bnds,bnds+3,Pcur+3);
				addBox(bnds,bnds+3,Pcur+(udiv+1)*3);
				addBox(bnds,bnds+3,Pcur+(udiv+1)*3+3);
				
				maxBound		=	max(bnds[3+COMP_X]-bnds[COMP_X],bnds[3+COMP_Y]-bnds[COMP_Y]);
				maxBound		=	max(bnds[3+COMP_Z]-bnds[COMP_Z],maxBound);
				maxBound		*=	attributes->rasterExpand;

				bnds[COMP_X]	-=	maxBound;
				bnds[COMP_Y]	-=	maxBound;
				bnds[COMP_Z]	-=	maxBound;
				bnds[3+COMP_X]	+=	maxBound;
				bnds[3+COMP_Y]	+=	maxBound;
				bnds[3+COMP_Z]	+=	maxBound;
				
				bnds += 6;
				Pcur += 3;
			}
			Pcur += 3;
		}
		
	} else {
		P						=	NULL;
		size					=	0;
	}
}