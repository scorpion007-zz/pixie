//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright � 1999 - 2003, Okan Arikan
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
//  File				:	object.cpp
//  Classes				:	CGeometry
//  Description			:	Implementation
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

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
void			CObject::dice(CShadingContext *rasterizer) {
	CObject	*cObject,*nObject;
	for (cObject=children;cObject!=NULL;cObject=nObject) {
		nObject	=	cObject->sibling;

		osLock(CRenderer::refCountMutex);
		cObject->attach();
		osUnlock(CRenderer::refCountMutex);
		
		rasterizer->drawObject(cObject);
		
		osLock(CRenderer::refCountMutex);
		cObject->detach();
		osUnlock(CRenderer::refCountMutex);
	}
}


static	float	getDisp(const float *mat,float disp) {
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
CObject		*CObject::cluster(CShadingContext *context,CObject *children) {
	int		numChildren;
	CObject	*cObject;

	// Count the number of children
	for (numChildren=0,cObject=children;cObject!=NULL;cObject=cObject->sibling,numChildren++);

	// If we have too few children, continue
	if (numChildren <= 2)	return children;

	// These are the two children
	CObject	*front,*frontChildren;
	CObject	*back,*backChildren;

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

	frontChildren	=	NULL;
	backChildren	=	NULL;

	// Create the clusters
	for (numChildren=0,cObject=children;cObject!=NULL;numChildren++) {
		CObject	*nObject	=	cObject->sibling;

		if (indices[numChildren] == 0) {
			cObject->sibling	=	frontChildren;
			frontChildren		=	cObject;
			addBox(front->bmin,front->bmax,cObject->bmin);
			addBox(front->bmin,front->bmax,cObject->bmax);
		} else {
			cObject->sibling	=	backChildren;
			backChildren		=	cObject;
			addBox(back->bmin,back->bmax,cObject->bmin);
			addBox(back->bmin,back->bmax,cObject->bmax);
		}

		cObject	=	nObject;
	}

	memEnd(context->threadMemory);

	// Recurse
	front->children	=	front->cluster(context,frontChildren);
	back->children	=	back->cluster(context,backChildren);
	
	front->attach();
	back->attach();

	front->sibling	=	back;
	back->sibling	=	NULL;

	return front;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CObject
// Method				:	setChildren
// Description			:	Set the children objects
// Return Value			:
// Comments				:
void			CObject::setChildren(CShadingContext *context,CObject *allChildren) {

	// If raytraced, attach to the children
	if (raytraced()) {
		CObject	*cObject;
		for (cObject=allChildren;cObject!=NULL;cObject=cObject->sibling)	cObject->attach();
		children	=	cluster(context,allChildren);
	} else {
		children	=	allChildren;
	}

}

///////////////////////////////////////////////////////////////////////
// Class				:	CObject
// Method				:	destroy
// Description			:	Destroy the entire tree
// Return Value			:
// Comments				:
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
		const float			*from,*to;
		ECoordinateSystem	sys;

		if (CRenderer::findCoordinateSystem(attributes->maxDisplacementSpace,from,to,sys)) {
			maxDisp	=	attributes->maxDisplacement	* getDisp(from,attributes->maxDisplacement);
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
CDummyObject::CDummyObject(CAttributes *a,CXform *x) : CObject(a,x) {
	flags	|=	OBJECT_DUMMY;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDummyObject
// Method				:	~CDummyObject
// Description			:	Dtor
// Return Value			:
// Comments				:
CDummyObject::~CDummyObject() {
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDummyObject
// Method				:	intersect
// Description			:	Intersect a ray
// Return Value			:
// Comments				:
void			CDummyObject::intersect(CShadingContext *,CRay *) {
	// Should never reach this point
	//assert(FALSE);
}









///////////////////////////////////////////////////////////////////////
// Class				:	CSurface
// Method				:	intersect
// Description			:	Intersect the surface
// Return Value			:
// Comments				:
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
	if (children == NULL) {
		// We must lock the hierarchyMutex so that the list of known tesselation patches
		// is maintained in a thread safe manner
		osLock(CRenderer::hierarchyMutex);

		if (children == NULL) {

			osLock(CRenderer::refCountMutex);
			CTesselationPatch	*tesselation	=	new CTesselationPatch(attributes,xform,this,0,1,0,1,0,0,-1);
			osUnlock(CRenderer::refCountMutex);

			tesselation->initTesselation(context);
			tesselation->attach();
			children				=	tesselation;
		}

		osUnlock(CRenderer::hierarchyMutex);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSurface
// Method				:	dice
// Description			:	Dice the object into smaller ones
// Return Value			:
// Comments				:
void				CSurface::dice(CShadingContext *rasterizer) {

	osLock(CRenderer::refCountMutex);
	CPatch	*cSurface	=	new CPatch(attributes,xform,this,0,1,0,1,0,attributes->minSplits);
	osUnlock(CRenderer::refCountMutex);

	cSurface->dice(rasterizer);

	osLock(CRenderer::refCountMutex);
	cSurface->check();
	osUnlock(CRenderer::refCountMutex);
	
	// Note we tesselate for raytracing on demand - so we do not automatically emit a CTesselationPatch here
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSurface
// Method				:	moving
// Description			:	TRUE if the object is moving
// Return Value			:
// Comments				:
int					CSurface::moving() const {
	return FALSE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSurface
// Method				:	sample
// Description			:	Sample a bunch of points on the surface
// Return Value			:	TRUE if the sampling was done and shaders need to be executed
// Comments				:
void				CSurface::sample(int,int,float **,float ***,unsigned int &) const {
	error(CODE_BUG,"An object is missing the \"sample\" function\n");
	assert(FALSE);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSurface
// Method				:	interpolate
// Description			:	Interpolate the varying data and set the uniform data
// Return Value			:
// Comments				:
void				CSurface::interpolate(int,float **,float ***)	const {
	error(CODE_BUG,"An object is missing the \"interpolate\" function\n");
	assert(FALSE);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CSurface
// Method				:	split
// Description			:	Split an object
// Return Value			:
// Comments				:
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
// Class			   :   CSurface
// Method			   :   estimateShadingRate
// Description		   :   Estimate the shading rate
// Return Value			   :
// Comments				   :   P must be in pixels
float			   CSurface::estimateShadingRate(const float *P0,const float *P1) {
   return attributes->shadingRate;
}


///////////////////////////////////////////////////////////////////////
// Class			   :   CSurface
// Method			   :   estimateDicing
// Description		   :   Estimate the dicing size on the screen
// Return Value			   :
// Comments				   :   P must be in pixels
void			   CSurface::estimateDicing(const float *P,int udiv,int vdiv,int &nudiv,int &nvdiv,float motionFactor) {
   float	   uAvg,vAvg;  // The average edge length
   float	   uMin,vMin;  // The minimum edge length
   float	   uMax,vMax;  // The maximum edge length
   int		   numU,numV;
   int		   i,j;
   const float *cP,*nP,*tP;
   float	   l;
   float	   dx,dy;

   uAvg	   =   vAvg	   =   0;
   uMax	   =   vMax	   =   0;
   uMin	   =   vMin	   =   C_INFINITY;
   numU	   =   numV	   =   0;

   // U stats
   cP  =   P;
   for (j=(vdiv+1);j>0;j--) {
	   for (i=udiv;i>0;i--,cP+=3) {
		   dx	   =   cP[3 + COMP_X] - cP[COMP_X];
		   dy	   =   cP[3 + COMP_Y] - cP[COMP_Y];
		   l	   =   sqrtf(dx*dx + dy*dy);
		   uAvg	+=	l;	numU++;
		   if (l < uMin)   uMin	   =   l;
		   if (l > uMax)   uMax	   =   l;
	   }
	   cP  +=  3;
   }

   // V stats
   cP  =   P;
   for (i=(udiv+1);i>0;i--,cP+=3) {
	   nP  =   cP;
	   tP  =   nP  +   (udiv+1)*3;
	   for (j=vdiv;j>0;j--,nP=tP,tP+=(udiv+1)*3) {
		   dx	   =   tP[COMP_X] - nP[COMP_X];
		   dy	   =   tP[COMP_Y] - nP[COMP_Y];
		   l	   =   sqrtf(dx*dx + dy*dy);
		   vAvg	   +=  l;  numV++;
		   if (l < vMin)   vMin	   =   l;
		   if (l > vMax)   vMax	   =   l;
	   }
   }

   // Compute the new grid size
   nudiv   =   (int) (uAvg*udiv / (attributes->shadingRate*numU));
   nvdiv   =   (int) (vAvg*vdiv / (attributes->shadingRate*numV));
   
   nudiv   =   max(1,nudiv);
   nvdiv   =   max(1,nvdiv);
}

