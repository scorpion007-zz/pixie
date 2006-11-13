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
//  File				:	object.cpp
//  Classes				:	CGeometry
//  Description			:	Implementation
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "common/global.h"
#include "common/polynomial.h"
#include "object.h"
#include "error.h"
#include "ri.h"
#include "shading.h"
#include "stats.h"
#include "memory.h"
#include "surface.h"
#include "rendererContext.h"
#include "renderer.h"











///////////////////////////////////////////////////////////////////////
// Class				:	CObject
// Method				:	CObject
// Description			:	Ctor
// Return Value			:	-
// Comments				:	
// Date last edited		:	3/11/2001
CObject::CObject(CAttributes *a,CXform *x) {
	stats.numObjects++;

	flags		=	0;
	attributes	=	a;
	xform		=	x;

	refCount	=	0;

	attributes->attach();
	xform->attach();

	children	=	NULL;
	sibling		=	NULL;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CObject
// Method				:	~CObject
// Description			:	Dtor
// Return Value			:	-
// Comments				:	
// Date last edited		:	3/11/2001
CObject::~CObject() {
	stats.numObjects--;

	attributes->detach();
	xform->detach();
}


///////////////////////////////////////////////////////////////////////
// Class				:	CObject
// Method				:	dice
// Description			:	Dice the children objects
// Return Value			:	-
// Comments				:	
// Date last edited		:	3/11/2001
void			CObject::dice(CShadingContext *rasterizer) {
	CObject	*cObject,*nObject;
	for (cObject=children;cObject!=NULL;cObject=nObject) {
		nObject	=	cObject->sibling;
		cObject->attach();
		rasterizer->drawObject(cObject);
		cObject->detach();
	}
}


static	float	getDisp(float *mat,float disp) {
	float	tmp[4],tmp2[4];
	int		i;
	float	alpha;

#define urand()	rand() / (float) RAND_MAX

	tmp[0]	=	urand();
	tmp[1]	=	urand();
	tmp[2]	=	urand();
	tmp[3]	=	urand();

	for (i=0;i<10;i++) {
		mulmp4(tmp2,mat,tmp);

		alpha	=	max(absf(tmp2[0]),absf(tmp2[1]));
		alpha	=	max(alpha,absf(tmp2[2]));
		alpha	=	max(alpha,absf(tmp2[3]));

		tmp[0]	=	tmp2[0]	/	alpha;
		tmp[1]	=	tmp2[1]	/	alpha;
		tmp[2]	=	tmp2[2]	/	alpha;
		tmp[3]	=	tmp2[3]	/	alpha;
	}
	
	return	alpha;

#undef urand
}


///////////////////////////////////////////////////////////////////////
// Class				:	CObject
// Method				:	cluster
// Description			:	Cluster the objects
// Return Value			:
// Comments				:
// Date last edited		:	10/16/2001
void		CObject::cluster(CShadingContext *context) {
	int		numChildren;
	CObject	*cObject;

	// Count the number of children
	for (numChildren=0,cObject=children;cObject!=NULL;cObject=cObject->sibling,numChildren++);

	// If we have too few children, continue
	if (numChildren <= 2)	return;

	CObject	*front;
	CObject	*back;

	// Begin a memory page
	memBegin(context->threadMemory);

	// Cluster the midpoints of the objects
	float	*P			=	(float *)	ralloc(numChildren*3*sizeof(float),context->threadMemory);
	int		*indices	=	(int *)		ralloc(numChildren*sizeof(int),context->threadMemory);


	// For 5 iterations
	int	iteration;
	for (iteration=0;iteration<5;iteration++) {

		// Compute a slightly jittered center position for the object
		for (numChildren=0,cObject=children;cObject!=NULL;cObject=cObject->sibling,numChildren++) {
			initv(P + numChildren*3	,	(cObject->bmax[0] - cObject->bmin[0])*(context->urand()*0.2f + 0.4f) +  cObject->bmin[0]
									,	(cObject->bmax[1] - cObject->bmin[1])*(context->urand()*0.2f + 0.4f) +  cObject->bmin[1]
									,	(cObject->bmax[2] - cObject->bmin[2])*(context->urand()*0.2f + 0.4f) +  cObject->bmin[2]);
			indices[numChildren]	=	-1;
		}

		// The random cluster centers
		vector	P1,P2;
		initv(P1,	(bmax[0] - bmin[0])*context->urand() + bmin[0]
				,	(bmax[1] - bmin[1])*context->urand() + bmin[1]
				,	(bmax[2] - bmin[2])*context->urand() + bmin[2]);
		initv(P2,	(bmax[0] - bmin[0])*context->urand() + bmin[0]
				,	(bmax[1] - bmin[1])*context->urand() + bmin[1]
				,	(bmax[2] - bmin[2])*context->urand() + bmin[2]);

		// The main clustering loop
		int	done;
		for (done=FALSE;done==FALSE;) {
			int		i;
			vector	nP1,nP2;
			int		num1,num2;

			done	=	TRUE;

			initv(nP1,0);
			initv(nP2,0);
			num1	=	0;
			num2	=	0;
			for (i=0;i<numChildren;i++) {
				vector	D1,D2;

				subvv(D1,P + i*3,P1);
				subvv(D2,P + i*3,P2);
				if (dotvv(D1,D1) < dotvv(D2,D2)) {
					if (indices[i] != 0) {
						done		=	FALSE;
						indices[i]	=	0;
					}

					addvv(nP1,P+i*3);
					num1++;
				} else {
					if (indices[i] != 1) {
						done		=	FALSE;
						indices[i]	=	1;
					}

					addvv(nP2,P+i*3);
					num2++;
				}
			}

			if ((num1 == 0) || (num2 == 0))	break;

			mulvf(P1,nP1,1/(float) num1);
			mulvf(P2,nP2,1/(float) num2);
		}

		if (done == TRUE)	break;
	}






	// Cluster the rest of the objects
	front	=	new CDummyObject(attributes,xform);
	back	=	new CDummyObject(attributes,xform);
	initv(front->bmin,C_INFINITY);
	initv(front->bmax,-C_INFINITY);
	initv(back->bmin,C_INFINITY);
	initv(back->bmax,-C_INFINITY);

	// Create the clusters
	for (numChildren=0,cObject=children;cObject!=NULL;numChildren++) {
		CObject	*nObject	=	cObject->sibling;

		if (indices[numChildren] == 0) {
			cObject->sibling	=	front->children;
			front->children		=	cObject;
			addBox(front->bmin,front->bmax,cObject->bmin);
			addBox(front->bmin,front->bmax,cObject->bmax);
		} else {
			cObject->sibling	=	back->children;
			back->children		=	cObject;
			addBox(back->bmin,back->bmax,cObject->bmin);
			addBox(back->bmin,back->bmax,cObject->bmax);
		}

		cObject	=	nObject;
	}
	children		=	front;
	front->sibling	=	back;
	back->sibling	=	NULL;

	memEnd(context->threadMemory);

	// Recurse
	front->cluster(context);
	back->cluster(context);
	
	front->attach();
	back->attach();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CObject
// Method				:	destroy
// Description			:	Destroy the entire tree
// Return Value			:
// Comments				:
// Date last edited		:	10/16/2001
void		CObject::destroy() {
	if (sibling != NULL)	sibling->destroy();
	if (children != NULL)	children->destroy();

	delete this;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CObject
// Method				:	makeBound
// Description			:	Make sure we do not have empty bounding box
// Return Value			:
// Comments				:
// Date last edited		:	10/16/2001
void		CObject::makeBound(float *bmin,float *bmax) const {
	vector	D;
	float	maxD;
	float	maxDisp = attributes->maxDisplacement;

	subvv(D,bmax,bmin);
	maxD	=	D[0];
	maxD	=	max(D[1],maxD);
	maxD	=	max(D[2],maxD);
	maxD	*=	attributes->bexpand;

	// Add the displacement amount of the surface
	if (attributes->maxDisplacementSpace != NULL) {
		matrix				*from;
		matrix				*to;
		ECoordinateSystem	sys;

		if (CRenderer::findCoordinateSystem(attributes->maxDisplacementSpace,from,to,sys)) {
			maxDisp	=	attributes->maxDisplacement	* getDisp(*from,attributes->maxDisplacement);
		}

		free(attributes->maxDisplacementSpace);
		attributes->maxDisplacementSpace	=	NULL;
	}

	maxD	+=	maxDisp;

	// Expand the bound accordingly
	subvf(bmin,maxD);
	addvf(bmax,maxD);
}








///////////////////////////////////////////////////////////////////////
// Class				:	CDummyObject
// Method				:	CDummyObject
// Description			:	Ctor
// Return Value			:
// Comments				:
// Date last edited		:	10/16/2001
CDummyObject::CDummyObject(CAttributes *a,CXform *x) : CObject(a,x) {
	flags	|=	OBJECT_DUMMY;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDummyObject
// Method				:	~CDummyObject
// Description			:	Dtor
// Return Value			:
// Comments				:
// Date last edited		:	10/16/2001
CDummyObject::~CDummyObject() {
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDummyObject
// Method				:	intersect
// Description			:	Intersect a ray
// Return Value			:
// Comments				:
// Date last edited		:	10/16/2001
void			CDummyObject::intersect(CShadingContext *,CRay *) {
	// Should never reach this point
	//assert(FALSE);
}








///////////////////////////////////////////////////////////////////////
// Class				:	CSurface
// Method				:	CSurface
// Description			:	Ctor
// Return Value			:
// Comments				:
// Date last edited		:	10/16/2001
CSurface::CSurface(CAttributes *a,CXform *x) : CObject(a,x) {
	tesselationCache	=	NULL;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSurface
// Method				:	~CSurface
// Description			:	Dtor
// Return Value			:
// Comments				:
// Date last edited		:	10/16/2001
CSurface::~CSurface() {
	while (tesselationCache != NULL) {
		CSurface::CSurfaceTesselation *cTesselation = tesselationCache;
		tesselationCache = tesselationCache->otherTesselations;
		delete cTesselation;
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSurface
// Method				:	intersect
// Description			:	Intersect the surface
// Return Value			:
// Comments				:
// Date last edited		:	10/16/2001
void				CSurface::intersect(CShadingContext *context,CRay *cRay) {

	if (! (cRay->flags & attributes->flags) )	return;

	if (attributes->flags & ATTRIBUTES_FLAGS_LOD) {
		const float importance = attributes->lodImportance;
		if (importance >= 0) {
			if (cRay->jimp > importance)			return;
		} else {
			if ((1-cRay->jimp) >= -importance)		return;
		}
	}



	// Do we have a grid ?
	if (tesselationCache == NULL) {
		osLock(CRenderer::tesselateMutex);

		if (tesselationCache == NULL) {
			tesselationCache	=	tesselate(context,0,0.0f,1.0f,0.0f,1.0f,0.01f);
		}

		osUnlock(CRenderer::tesselateMutex);
	}

	// Intersect the ray
	CSurface::CSurfaceTesselation *cTesselation = tesselationCache;
	
	while (cTesselation != NULL) {
		int			i,j;
		const float	*cP		=	cTesselation->P;
		const float	*r		=	cRay->from;
		const float	*q		=	cRay->dir;
		const int	udiv	=	cTesselation->udiv;
		const int	vdiv	=	cTesselation->vdiv;
		
		const float umin = cTesselation->umin;
		const float vmin = cTesselation->vmin;
		const float urg = (cTesselation->umax-cTesselation->umin);
		const float vrg = (cTesselation->vmax-cTesselation->vmin);

		for (j=0;j<vdiv;j++) {
			for (i=0;i<udiv;i++,cP += 3) {
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
									cRay->object	=	this;					\
									cRay->u			=	(float) umin + ((float) u + i)*urg / (float) udiv;	\
									cRay->v			=	(float) vmin + ((float) v + j)*vrg / (float) vdiv;	\
									cRay->t			=	(float) t;				\
									movvv(cRay->N,N);							\
								}												\
							} else {											\
								cRay->object	=	this;						\
								cRay->u			=	(float) umin + ((float) u + i)*urg / (float) udiv;		\
								cRay->v			=	(float) vmin + ((float) v + j)*vrg / (float) vdiv;		\
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
		
		cTesselation = cTesselation->otherTesselations;
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSurface
// Method				:	dice
// Description			:	Dice the object into smaller ones
// Return Value			:
// Comments				:
// Date last edited		:	10/16/2001
void				CSurface::dice(CShadingContext *rasterizer) {

	osLock(CRenderer::refCountMutex);
	CPatch	*cSurface	=	new CPatch(attributes,xform,this,0,1,0,1,0,attributes->minSplits);
	osUnlock(CRenderer::refCountMutex);

	cSurface->dice(rasterizer);

	osLock(CRenderer::refCountMutex);
	cSurface->check();
	osUnlock(CRenderer::refCountMutex);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSurface
// Method				:	moving
// Description			:	TRUE if the object is moving
// Return Value			:
// Comments				:
// Date last edited		:	10/16/2001
int					CSurface::moving() const {
	return FALSE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSurface
// Method				:	sample
// Description			:	Sample a bunch of points on the surface
// Return Value			:	TRUE if the sampling was done and shaders need to be executed
// Comments				:
// Date last edited		:	10/16/2001
void				CSurface::sample(int,int,float **,unsigned int &) const {
	error(CODE_BUG,"An object is missing the \"sample\" function\n");
	assert(FALSE);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSurface
// Method				:	interpolate
// Description			:	Interpolate the varying data and set the uniform data
// Return Value			:
// Comments				:
// Date last edited		:	10/16/2001
void				CSurface::interpolate(int,float **)	const {
	error(CODE_BUG,"An object is missing the \"interpolate\" function\n");
	assert(FALSE);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CSurface
// Method				:	split
// Description			:	Split an object
// Return Value			:
// Comments				:
// Date last edited		:	10/16/2001
void				CSurface::shade(CShadingContext *context,int numRays,CRay **rays) {
	float	**varying	=	context->currentShadingState->varying;
	float	*u			=	varying[VARIABLE_U];
	float	*v			=	varying[VARIABLE_V];
	float	*time		=	varying[VARIABLE_TIME];
	float	*I			=	varying[VARIABLE_I];
	float	*du			=	varying[VARIABLE_DU];
	int		i;

	for (i=numRays;i>0;i--) {
		const CRay	*cRay	=	*rays++;

		*u++	=	cRay->u;						// The intersection u
		*v++	=	cRay->v;						// The intersection v
		*time++	=	cRay->time;						// The intersection time
		*du++	=	cRay->da*cRay->t + cRay->db;	// The ray differential
		mulvf(I,cRay->dir,cRay->t);					// Compute the I vector
		I		+=	3;
	}

	context->shade(this,numRays,1,SHADING_2D,0);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CSurface
// Method				:	estimateShadingRate
// Description			:	Estimate the shading rate
// Return Value			:
// Comments				:	P must be in pixels
// Date last edited		:	10/16/2001
float				CSurface::estimateShadingRate(const float *P0,const float *P1) {
	return attributes->shadingRate;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSurface
// Method				:	estimateDicing
// Description			:	Estimate the dicing size on the screen
// Return Value			:
// Comments				:	P must be in pixels
// Date last edited		:	10/16/2001
void				CSurface::estimateDicing(const float *P,int udiv,int vdiv,int &nudiv,int &nvdiv,float motionFactor) {
	float		uAvg,vAvg;	// The average edge length
	float		uMin,vMin;	// The minimum edge length
	float		uMax,vMax;	// The maximum edge length
	int			numU,numV;
	int			i,j;
	const float	*cP,*nP,*tP;
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


//#include "debug.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CSurface
// Method				:	tesselate
// Description			:	Find the best tesselation for this object
// Return Value			:
// Comments				:
// Date last edited		:	10/16/2001
CSurface::CSurfaceTesselation			*CSurface::tesselate(CShadingContext *context,int depth,float umin,float umax,float vmin,float vmax,float r) {
	// Get some misc variables for fast access
	float	**varying	=	context->currentShadingState->varying;

	// Start with a 3x3 sampling grid
	int		udiv		=	2;
	int		vdiv		=	2;
	
	int		maxTesselationReached	=	(depth >= attributes->maxSubdivision);

	while(TRUE) {
		// Sample points on the patch
		float	ustep		=	(umax-umin) / (float) (udiv);
		float	vstep		=	(vmax-vmin) / (float) (vdiv);

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
		context->displace(this,udiv+1,vdiv+1,SHADING_2D_GRID,PARAMETER_P | PARAMETER_N | PARAMETER_BEGIN_SAMPLE);

		if (maxTesselationReached) break;
		
		// Evaluate the quality of this tesselation in u and v separately
		int		i;
		float	vMax	=	0;
		float	vAvg	=	0;
		for (i=0;i<=udiv;i++) {
			const float	l	=	measureLength(varying[VARIABLE_P] + i*3,(udiv+1)*3,vdiv-1);
			vMax			=	max(vMax,l);
			vAvg			+=	l;
		}

		float	uMax	=	0;
		float	uAvg	=	0;
		for (i=0;i<=vdiv;i++) {
			const float	l	=	measureLength(varying[VARIABLE_P] + i*(udiv+1)*3,3,udiv-1);
			uMax			=	max(uMax,l);
			uAvg			+=	l;
		}

		uAvg	/=	(float) (vdiv+1);
		vAvg	/=	(float) (udiv+1);

		int	nudiv	=	max((int) (uAvg / r),2);
		int	nvdiv	=	max((int) (vAvg / r),2);

		if ((nudiv == udiv) && (nvdiv == vdiv))	break;

		// Scale back if we exceeded the max shading size
		if ((nudiv+1)*(nvdiv+1) > CRenderer::maxGridSize) {
			#if 0
			float	aspect	=	uAvg / vAvg;
			nvdiv	=	(int) floor(sqrtf(CRenderer::maxGridSize / aspect))-1;
			nudiv	=	(int) floor(nvdiv*aspect)-1;
						
			assert ((nudiv+1)*(nvdiv+1) <= CRenderer::maxGridSize);
			maxTesselationReached = TRUE;
			
			#else
			// TODO: allow multiple shades in multiple patches, and reconstruct.
			// TODO: begin-end time samples
			//break;
			if (nvdiv == nudiv) {
				float 		umid			=	(umin + umax) / (float) 2;
				float 		vmid			=	(vmin + vmax) / (float) 2;
				
				CSurface::CSurfaceTesselation *a = tesselate(context,depth+1,umin,umid,vmin,vmid,r);
				CSurface::CSurfaceTesselation *b = tesselate(context,depth+1,umid,umax,vmin,vmid,r);
				CSurface::CSurfaceTesselation *c = tesselate(context,depth+1,umid,umax,vmid,vmax,r);
				CSurface::CSurfaceTesselation *d = tesselate(context,depth+1,umin,umid,vmid,vmax,r);
				
				CSurface::CSurfaceTesselation *ct = a;
				while(ct->otherTesselations != NULL) ct = ct->otherTesselations;
				ct->otherTesselations = b;
				
				ct = b;
				while(ct->otherTesselations != NULL) ct = ct->otherTesselations;
				ct->otherTesselations = c;
				
				ct = c;
				while(ct->otherTesselations != NULL) ct = ct->otherTesselations;
				ct->otherTesselations = d;
				
				return a;
				
			} else if (nudiv > nvdiv) {
				float 		umid			=	(umin + umax) / (float) 2;
				
				CSurface::CSurfaceTesselation *a = tesselate(context,depth+1,umin,umid,vmin,vmax,r);
				CSurface::CSurfaceTesselation *b = tesselate(context,depth+1,umid,umax,vmin,vmax,r);
				
				CSurface::CSurfaceTesselation *ct = a;
				while(ct->otherTesselations != NULL) ct = ct->otherTesselations;
				ct->otherTesselations = b;
								
				return a;
			} else {
				float 		vmid			=	(vmin + vmax) / (float) 2;
				
				CSurface::CSurfaceTesselation *a = tesselate(context,depth+1,umin,umax,vmin,vmid,r);
				CSurface::CSurfaceTesselation *b = tesselate(context,depth+1,umin,umax,vmid,vmax,r);
				
				CSurface::CSurfaceTesselation *ct = a;
				while(ct->otherTesselations != NULL) ct = ct->otherTesselations;
				ct->otherTesselations = b;
								
				return a;
			}
			#endif
		}

		// Do another iteration
		udiv	=	nudiv;
		vdiv	=	nvdiv;
	}

	// At this point, I should have the tesselation. So create the grid and return it
	CSurfaceTesselation	*newTesselationCache	=	new CSurfaceTesselation;
	newTesselationCache->udiv					=	udiv;
	newTesselationCache->vdiv					=	vdiv;
	
	newTesselationCache->umin					=	umin;
	newTesselationCache->umax					=	umax;
	newTesselationCache->vmin					=	vmin;
	newTesselationCache->vmax					=	vmax;
	
	newTesselationCache->lastRefNumber			=	-1;
	newTesselationCache->P						=	new float[(udiv+1)*(vdiv+1)*3];
	newTesselationCache->size					=	(udiv+1)*(vdiv+1)*3*sizeof(float);
	newTesselationCache->otherTesselations		=	NULL;
	
	memcpy(newTesselationCache->P,varying[VARIABLE_P],(udiv+1)*(vdiv+1)*3*sizeof(float));

	return newTesselationCache;
}