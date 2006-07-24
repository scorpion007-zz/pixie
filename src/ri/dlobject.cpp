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
//  File				:	dlobject.cpp
//  Classes				:	CDLObject
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "dlobject.h"
#include "error.h"
#include "stats.h"
#include "shading.h"


///////////////////////////////////////////////////////////////////////
// Class				:	CDLObject
// Method				:	CDLObject
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	11/7/2003
CDLObject::CDLObject(CAttributes *a,CXform *x,void *handle,void *data,const float *bmi,const float *bma,dloInitFunction initFunction,dloIntersectFunction intersectFunction,dloTiniFunction tiniFunction) : CSurface(a,x) {
	stats.numGprims++;
	stats.gprimMemory		+=	sizeof(CDLObject);

	this->handle			=	handle;
	this->initFunction		=	initFunction;
	this->intersectFunction	=	intersectFunction;
	this->tiniFunction		=	tiniFunction;
	this->data				=	data;
	movvv(this->bmin,bmi);
	movvv(this->bmax,bma);

	movvv(cameraBmin,bmin);
	movvv(cameraBmax,bmax);
	xform->transformBound(cameraBmin,cameraBmax);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CDLObject
// Method				:	~CDLObject
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	11/7/2003
CDLObject::~CDLObject() {
	stats.numGprims--;
	stats.gprimMemory		-=	sizeof(CDLObject);

	tiniFunction(data);
	osUnloadModule(handle);
}
	


///////////////////////////////////////////////////////////////////////
// Class				:	CDLObject
// Method				:	intersect
// Description			:	Intersect the surface with the ray
// Return Value			:	-
// Comments				:
// Date last edited		:	11/7/2003
void					CDLObject::intersect(CRay *ray) {
	vector	oN;
	float	t;

	// Should we intersect ?
	if (! (ray->flags & attributes->flags) )	return;
	
	if (attributes->flags & ATTRIBUTES_FLAGS_LOD) {
		float importance = attributes->lodImportance;
		if (ray->jimp < 0) ray->jimp = urand();
		if (importance >= 0) {
			if (ray->jimp > importance)			return;
		} else {
			if ((1-ray->jimp) >= -importance)	return;
		}
	}
	

	// Convert the ray into the right coordinate system
	if (ray->lastXform != xform) {
		if (xform->next != NULL) {
			vector	tmp[4];
			vector	to;
			addvv(to,ray->from,ray->dir);

			mulmp(tmp[0],xform->to,ray->from);
			mulmp(tmp[1],xform->to,to);

			mulmp(tmp[2],xform->next->to,ray->from);
			mulmp(tmp[3],xform->next->to,to);

			interpolatev(ray->oFrom,tmp[0],tmp[2],ray->time);
			interpolatev(ray->oTo,tmp[1],tmp[3],ray->time);
			subvv(ray->oDir,ray->oTo,ray->oFrom);
		} else {
			vector	to;
			addvv(to,ray->from,ray->dir);

			mulmp(ray->oFrom,xform->to,ray->from);
			mulmp(ray->oTo,xform->to,to);
			subvv(ray->oDir,ray->oTo,ray->oFrom);
		}

		ray->lastXform	=	xform;
	}

	// Perform the actual intersection
	if (intersectFunction(data,ray->oFrom,ray->oDir,&t,oN)) {
		mulmn(ray->N,xform->to,oN);
		ray->t		=	t;
		ray->object	=	this;
		ray->u		=	0;
		ray->v		=	0;
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDLObject
// Method				:	intersect
// Description			:	Intersect the object with a box
// Return Value			:	-
// Comments				:
// Date last edited		:	11/7/2003
int						CDLObject::intersect(const float *bmin,const float *bmax) const {
	return intersectBox(bmin,bmax,cameraBmin,cameraBmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDLObject
// Method				:	bound
// Description			:	Bound the surface
// Return Value			:	-
// Comments				:
// Date last edited		:	11/7/2003
void					CDLObject::bound(float *bmin,float *bmax) const {
	movvv(bmin,cameraBmin);
	movvv(bmax,cameraBmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDLObject
// Method				:	sample
// Description			:	Sample the surface
// Return Value			:	-
// Comments				:
// Date last edited		:	11/7/2003
void					CDLObject::sample(int,int,float **,unsigned int &up) const {
	up	&=	~(PARAMETER_P | PARAMETER_NG);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDLObject
// Method				:	interpolate
// Description			:	Interpolate the surface
// Return Value			:	-
// Comments				:
// Date last edited		:	11/7/2003
void					CDLObject::interpolate(int,float **)	const {
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDLObject
// Method				:	tesselate
// Description			:	Tesselate the surface
// Return Value			:	-
// Comments				:
// Date last edited		:	11/7/2003
void					CDLObject::tesselate(CShadingContext *context) {
	context->addTracable(this,this);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDLObject
// Method				:	dice
// Description			:	Dice the surface for scan-line rendering
// Return Value			:	-
// Comments				:
// Date last edited		:	11/7/2003
void					CDLObject::dice(CShadingContext *) {
}


///////////////////////////////////////////////////////////////////////
// Class				:	CDLObject
// Method				:	copy
// Description			:	Create a copy
// Return Value			:	-
// Comments				:
// Date last edited		:	11/7/2003
void					CDLObject::copy(CAttributes *a,CXform *x,CRendererContext *context) const {
}


///////////////////////////////////////////////////////////////////////
// Class				:	CDLObject
// Method				:	shade
// Description			:	Shade the surface
// Return Value			:	-
// Comments				:
// Date last edited		:	11/7/2003
void					CDLObject::shade(CShadingContext *context,int numRays,CRay **rays) {
	float	**varying	=	context->currentShadingState->varying;
	float	*P			=	varying[VARIABLE_P];
	float	*N			=	varying[VARIABLE_NG];
	float	*from		=	varying[VARIABLE_I];
	int		i;

	for (i=numRays;i>0;i--) {
		const CRay	*cRay	=	*rays++;

		P[0]			=	cRay->from[0] + cRay->dir[0]*cRay->t;
		P[1]			=	cRay->from[1] + cRay->dir[1]*cRay->t;
		P[2]			=	cRay->from[2] + cRay->dir[2]*cRay->t;
		movvv(N,cRay->N);
		movvv(from,cRay->from);

		P				+=	3;
		N				+=	3;
		from			+=	3;
	}

	context->shade(this,numRays,-1,2,0);
}
