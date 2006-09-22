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

#include "surface.h"
#include "memory.h"
#include "stats.h"
#include "shading.h"
#include "error.h"


const	int		SPLIT_NONE	=	0;
const	int		SPLIT_U		=	1;
const	int		SPLIT_V		=	2;
const	int		SPLIT_UV	=	3;







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


static	int	cull(float *bmin,float *bmax,const float *P,const float *N,int k,int nsides,int disable,EProjectionType projection) {
	int	i;

	// Update the bounding box
	for (i=k;i>0;i--) {
		addBox(bmin,bmax,P);
		P			+=	3;
	}

	// Check the back face culling
	if (nsides == 1  && !disable) {
		P	-=	k*3;

		if (projection == OPTIONS_PROJECTION_PERSPECTIVE) {
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
		if ((r->flags & OPTIONS_FLAGS_MOTIONBLUR) && (object->moving())) {
			// Compute the sample positions and corresponding normal vectors
			for (vp=0,v=vstart,k=0;vp<numVprobes;vp++,v+=vstep) {
				for (up=0,u=ustart;up<numUprobes;up++,u+=ustep,k++) {
					uv[k]		=	u;
					vv[k]		=	v;
					timev[k]	=	1;
				}
			}
			assert(k <= (int) r->maxGridSize);
			r->displace(object,numUprobes,numVprobes,2,PARAMETER_P | PARAMETER_N | PARAMETER_END_SAMPLE);
			cullFlags			&=	cull(bmin,bmax,varying[VARIABLE_P],varying[VARIABLE_N],k,attributes->nSides,disableCull,r->projection);
			
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
		assert(k <= (int) r->maxGridSize);
		r->displace(object,numUprobes,numVprobes,2,PARAMETER_P | PARAMETER_N | PARAMETER_BEGIN_SAMPLE);
		cullFlags			&=	cull(bmin,bmax,varying[VARIABLE_P],varying[VARIABLE_N],k,attributes->nSides,disableCull,r->projection);

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
		if (r->inFrustrum(bmin,bmax) == FALSE)	return;

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
			r->camera2pixels(numUprobes*numVprobes,P);
			
			// Correct shading rate with dof factor
			if (r->flags & OPTIONS_FLAGS_FOCALBLUR) {
				float coc = r->minCocPixels(bmin[COMP_Z],bmax[COMP_Z]);
				shadingRate *= max(1,0.5f*coc);
			}
			
			// Optionally correct shading rate with motionfactor
			if ((r->flags & OPTIONS_FLAGS_MOTIONBLUR) && (object->moving())) {

				r->camera2pixels(4,(float*)Pmov);

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
			if (depth >= r->maxEyeSplits) {
				warning(CODE_SYSTEM,"Too many eye splits for primitive \"%s\"\n",attributes->name);
				return;
			}

			// We can not make the perspective divide, so make sure we split into 4 next time
			udiv	=	0;
		}

		// Finally record the surface with the rasterizer
		r->drawObject(this,bmin,bmax);
	} else {
		if (udiv == 0) {
			// We're spanning the eye plane
			splitToChildren(r,2);
		} else if (((udiv+1)*(vdiv+1)) > r->maxGridSize) {
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
	float		umid,vmid;

	stats.numSplits++;

	switch(dir) {
	case 0:
		if (umax <= umin)	break;

		// Split along one direction
		umid			=	(umin + umax) / (float) 2;
		p1				=	new CPatch(attributes,xform,object,umin,umid,vmin,vmax,depth+1,minDepth);	p1->dice(r);
		p2				=	new CPatch(attributes,xform,object,umid,umax,vmin,vmax,depth+1,minDepth);	p2->dice(r);
		p1->check();
		p2->check();
		stats.numUsplits++;
		break;
	case 1:
		if (vmax <= vmin)	break;

		// Split along one direction
		vmid			=	(vmin + vmax) / (float) 2;
		p1				=	new CPatch(attributes,xform,object,umin,umax,vmin,vmid,depth+1,minDepth);	p1->dice(r);
		p2				=	new CPatch(attributes,xform,object,umin,umax,vmid,vmax,depth+1,minDepth);	p2->dice(r);
		p1->check();
		p2->check();
		stats.numVsplits++;
		break;
	case 2:
		if (vmax <= vmin)	break;
		if (umax <= umin)	break;

		// Split along one direction
		vmid			=	(vmin + vmax) / (float) 2;
		umid			=	(umin + umax) / (float) 2;
		p1				=	new CPatch(attributes,xform,object,umin,umid,vmin,vmid,depth+1,minDepth);	p1->dice(r);
		p2				=	new CPatch(attributes,xform,object,umid,umax,vmin,vmid,depth+1,minDepth);	p2->dice(r);
		p3				=	new CPatch(attributes,xform,object,umin,umid,vmid,vmax,depth+1,minDepth);	p3->dice(r);
		p4				=	new CPatch(attributes,xform,object,umid,umax,vmid,vmax,depth+1,minDepth);	p4->dice(r);
		p1->check();
		p2->check();
		p3->check();
		p4->check();
		stats.numUVsplits++;
		break;
	}
}



///////////////////////////////////////////////////////////////////////
// Class				:	CPatch
// Method				:	diceNew
// Description			:	The new version of dice
// Return Value			:	-
// Comments				:
// Date last edited		:	6/4/2003
void		CPatch::diceNew(CShadingContext *r) {
	vector					bmin,bmax;
	int						up,vp;
	float					u,v;
	float					ustep,vstep;
	float					ustart,vstart;
	float					**varying;
	float					*uv;
	float					*vv;
	float					*timev;
	int						cullFlags;
	int						disableCull;
	int						nudiv,nvdiv,splitDecision;

	// Get some misc variables for fast access
	disableCull			=	attributes->flags & ATTRIBUTES_FLAGS_SHADE_BACKFACE;
	varying				=	r->currentShadingState->varying;

	// Start with a 3x3 sampling grid
	udiv				=	2;
	vdiv				=	2;
	while(TRUE) {
		cullFlags		=	TRUE;

		// Sample points on the patch
		ustart			=	umin;
		vstart			=	vmin;
		ustep			=	(umax - ustart) / (float) (udiv);
		vstep			=	(vmax - vstart) / (float) (vdiv);

		initv(bmin,C_INFINITY);
		initv(bmax,-C_INFINITY);

		// Take care of the motion
		if ((r->flags & OPTIONS_FLAGS_MOTIONBLUR) && (object->moving())) {
			// Compute the sample positions and corresponding normal vectors
			uv			=	varying[VARIABLE_U];
			vv			=	varying[VARIABLE_V];
			timev		=	varying[VARIABLE_TIME];
			for (vp=vdiv+1,v=vstart;vp>0;vp--,v+=vstep) {
				for (up=udiv+1,u=ustart;up>0;up--,u+=ustep) {
					*uv++		=	u;
					*vv++		=	v;
					*timev++	=	1;
				}
			}

			r->displace(object,udiv+1,vdiv+1,2,PARAMETER_P | PARAMETER_N | PARAMETER_END_SAMPLE);
			cullFlags			&=	cull(bmin,bmax,varying[VARIABLE_P],varying[VARIABLE_N],(udiv+1)*(vdiv+1),attributes->nSides,disableCull,r->projection);
		}


		// Compute the sample positions and corresponding normal vectors
		uv			=	varying[VARIABLE_U];
		vv			=	varying[VARIABLE_V];
		timev		=	varying[VARIABLE_TIME];
		for (vp=vdiv+1,v=vstart;vp>0;vp--,v+=vstep) {
				for (up=udiv+1,u=ustart;up>0;up--,u+=ustep) {
				*uv++		=	u;
				*vv++		=	v;
				*timev++	=	0;
			}
		}
		r->displace(object,udiv+1,vdiv+1,2,PARAMETER_P | PARAMETER_N | PARAMETER_BEGIN_SAMPLE);
		cullFlags			&=	cull(bmin,bmax,varying[VARIABLE_P],varying[VARIABLE_N],(udiv+1)*(vdiv+1),attributes->nSides,disableCull,r->projection);

		// Are we culled ?
		if (cullFlags)	return;

		// Can we make the perspective divide ?
		if (bmin[COMP_Z] > C_EPSILON) {
			// Do the projection
			r->camera2pixels((udiv+1)*(vdiv+1),varying[VARIABLE_P]);

			// Decide on the split
			splitDecision	=	diceStats(r,varying[VARIABLE_P],varying[VARIABLE_N],udiv,vdiv,nudiv,nvdiv);
			if (splitDecision == SPLIT_NONE) {

				// Do we have a good enough estimate ?
				//if ((udiv == nudiv) && (vdiv == nvdiv))	return splitDecision;

				// Keep going
				udiv	=	nudiv;
				vdiv	=	nvdiv;
			} else {
				return;
			}
		} else {
			// Decide on the split
			//return	diceStats(r,varying[VARIABLE_P],varying[VARIABLE_N],udiv,vdiv);
		}
	}

	assert(FALSE);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPatch
// Method				:	diceStats
// Description			:	Estimate the dicing stats
// Return Value			:	-
// Comments				:
// Date last edited		:	6/4/2003
int		CPatch::diceStats(CShadingContext *r,float *P,float *N,int udiv,int vdiv,int &nudiv,int &nvdiv) {
	float		uAvg,vAvg;	// The average edge length
	float		uMin,vMin;	// The minimum edge length
	float		uMax,vMax;	// The maximum edge length
	int			numU,numV;
	int			i,j;
	float		*cP,*nP,*tP;
	float		l;
	float		dx,dy;

	uAvg	=	vAvg	=	0;
	uMax	=	vMax	=	0;
	uMin	=	vMin	=	C_INFINITY;
	numU	=	numV	=	0;

	// U stats
	cP	=	P;
	for (j=(vdiv+1);j>0;j--) {
		for (i=udiv;i>0;i--,cP+=3) {
			dx		=	cP[3 + COMP_X] - cP[COMP_X];
			dy		=	cP[3 + COMP_Y] - cP[COMP_Y];
			l		=	sqrtf(dx*dx + dy*dy);
			uAvg	+=	l;	numU++;
			if (l < uMin)	uMin	=	l;
			if (l > uMax)	uMax	=	l;
		}
		cP	+=	3;
	}

	// V stats
	cP	=	P;
	for (i=(udiv+1);i>0;i--,cP+=3) {
		nP	=	cP;
		tP	=	nP	+	(udiv+1)*3;
		for (j=vdiv;j>0;j--,nP=tP,tP+=(udiv+1)*3) {
			dx		=	tP[COMP_X] - nP[COMP_X];
			dy		=	tP[COMP_Y] - nP[COMP_Y];
			l		=	sqrtf(dx*dx + dy*dy);
			vAvg	+=	l;	numV++;
			if (l < vMin)	vMin	=	l;
			if (l > vMax)	vMax	=	l;
		}
	}

	// Compute the new grid size
	nudiv	=	(int) (uAvg*udiv / (attributes->shadingRate*numU));
	nvdiv	=	(int) (vAvg*vdiv / (attributes->shadingRate*numV));

	// Are we too big ?
	if ((nudiv+1)*(nvdiv+1) > r->maxGridSize) {
		// We're too big, decide on the split
		if (nudiv > nvdiv)	return SPLIT_U;
		else				return SPLIT_V;
	} else {

		// Is there a big stretch ?
		if (uMax > attributes->shadingRate) {
			if (vMax > attributes->shadingRate) {
				if (uMax > vMax) {
					return SPLIT_U;
				} else {
					return SPLIT_V;
				}
			} else {
				return SPLIT_U;
			}
		} else if (vMax > attributes->shadingRate) {
			return SPLIT_V;
		} else {
			// We're good to go
			return	SPLIT_NONE;
		}
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPatch
// Method				:	diceStats
// Description			:	Figure out the maximum parametric direction
// Return Value			:	-
// Comments				:
// Date last edited		:	6/4/2003
int		CPatch::diceStats(CShadingContext *r,float *P,float *N,int udiv,int vdiv) {
	float		uMax,vMax;	// The maximum side length
	int			i,j;
	float		*cP,*nP,*tP;
	float		l;
	vector		D;

	uMax	=	vMax	=	0;

	// U stats
	cP	=	P;
	for (j=(vdiv+1);j>0;j--) {
		l	=	0;

		for (i=udiv;i>0;i--,cP+=3) {
			subvv(D,cP+3,cP);
			l		+=	sqrtf(dotvv(D,D));
		}
		cP	+=	3;

		if (l > uMax)	uMax	=	l;
	}

	// V stats
	cP	=	P;
	for (i=(udiv+1);i>0;i--,cP+=3) {
		l	=	0;
		nP	=	cP;
		tP	=	nP	+	(udiv+1)*3;
		for (j=vdiv;j>0;j--,nP=tP,tP+=(udiv+1)*3) {
			subvv(nP,tP);
			l		+=	sqrtf(dotvv(D,D));
		}

		if (l > vMax)	vMax	=	l;
	}

	// Split along the longest direction
	if (uMax > vMax)	return SPLIT_U;
	else				return SPLIT_V;
}























































///////////////////////////////////////////////////////////////////////
// Class				:	CSurfaceGrid
// Method				:	CSurfaceGrid
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	2/9/2005
CSurfaceGrid::CSurfaceGrid(CAttributes *a,CXform *x,CSurface *s,float umin,float umax,float vmin,float vmax,int depth,int minDepth) : CObject(a,x) {
	this->umin		=	umin;
	this->umax		=	umax;
	this->vmin		=	vmin;
	this->vmax		=	vmax;
	this->object	=	s;

	object->attach();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSurfaceGrid
// Method				:	~CSurfaceGrid
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	2/9/2005
CSurfaceGrid::~CSurfaceGrid() {
	object->detach();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSurfaceGrid
// Method				:	dice
// Description			:	Dispatch the grid
// Return Value			:	-
// Comments				:
// Date last edited		:	2/9/2005
void			CSurfaceGrid::dice(CShadingContext *context) {
}







