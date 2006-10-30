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
//  File				:	delayed.cpp
//  Classes				:	CDelayedObject
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "delayed.h"
#include "hierarchy.h"
#include "stats.h"
#include "renderer.h"
#include "rendererContext.h"


///////////////////////////////////////////////////////////////////////
// Class				:	CDelayedObject
// Method				:	CDelayedObject
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	8/10/2001
CDelayedObject::CDelayedObject(CAttributes *a,CXform *x,const float *bmin,const float *bmax,void	(*subdivisionFunction)(void *,float),void	(*freeFunction)(void *),void *data,int *drc) : CSurface(a,x) {
	stats.numDelayeds++;

	movvv(this->bmin,bmin);
	movvv(this->bmax,bmax);
	movvv(this->cbmin,bmin);
	movvv(this->cbmax,bmax);
	this->subdivisionFunction	=	subdivisionFunction;
	this->freeFunction			=	freeFunction;
	this->data					=	data;

	processed					=	FALSE;

	if (drc == NULL) {
		dataRefCount			=	new int;
		dataRefCount[0]			=	0;
	} else {
		dataRefCount			=	drc;
	}

	dataRefCount[0]++;

	xform->transformBound(this->cbmin,this->cbmax);
	makeBound(this->cbmin,this->cbmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDelayedObject
// Method				:	~CDelayedObject
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	8/10/2001
CDelayedObject::~CDelayedObject() {
	stats.numDelayeds--;

	dataRefCount[0]--;

	if (dataRefCount[0] == 0) {
		if (freeFunction != NULL)	freeFunction(data);
		delete dataRefCount;
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDelayedObject
// Method				:	intersect
// Description			:	See object.h
// Return Value			:	-
// Comments				:
// Date last edited		:	8/10/2001
int		CDelayedObject::intersect(const float *bmin,const float *bmax) const {
	return intersectBox(bmin,bmax,this->cbmin,this->cbmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDelayedObject
// Method				:	intersect
// Description			:	See object.h
// Return Value			:	-
// Comments				:
// Date last edited		:	8/10/2001
void	CDelayedObject::intersect(CRay *cRay) {
	float	tmin	=	cRay->tmin;
	float	tmax	=	cRay->t;

	if (hierarchyIntersectBox(this->cbmin,this->cbmax,cRay->from,cRay->to,tmin,tmax)) {
		osLock(CRenderer::delayedMutex);

		if (processed == FALSE) {
			CRenderer::context->processDelayedObject(this,subdivisionFunction,data,bmin,bmax,cRay);
			processed	=	TRUE;
		}

		osUnlock(CRenderer::delayedMutex);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDelayedObject
// Method				:	bound
// Description			:	See object.h
// Return Value			:	-
// Comments				:
// Date last edited		:	8/10/2001
void	CDelayedObject::bound(float *bmin,float *bmax) const {
	movvv(bmin,this->cbmin);
	movvv(bmax,this->cbmax);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CDelayedObject
// Method				:	split
// Description			:	See object.h
// Return Value			:	-
// Comments				:
// Date last edited		:	8/10/2001
void	CDelayedObject::tesselate(CShadingContext *context) {
	CRenderer::addTracable(this,this);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDelayedObject
// Method				:	dice
// Description			:	See object.h
// Return Value			:	-
// Comments				:
// Date last edited		:	8/10/2001
void	CDelayedObject::dice(CShadingContext *r) {
	osLock(CRenderer::delayedMutex);

	if (processed == FALSE) {
		CRenderer::context->processDelayedObject(this,subdivisionFunction,data,bmin,bmax);
		processed	=	TRUE;
	}

	osUnlock(CRenderer::delayedMutex);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDelayedObject
// Method				:	instantiate
// Description			:	See object.h
// Return Value			:	-
// Comments				:
// Date last edited		:	8/10/2001
void	CDelayedObject::instantiate(CAttributes *a,CXform *x,CRendererContext *c) const {
	CXform			*nx					=	new CXform(x);

	nx->concat(xform);

	if (a == NULL)	a	=	attributes;

	c->addObject(new CDelayedObject(a,nx,bmin,bmax,subdivisionFunction,freeFunction,data,dataRefCount));
}












///////////////////////////////////////////////////////////////////////
// Class				:	CDelayedInstance
// Method				:	CDelayedInstance
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	8/10/2001
CDelayedInstance::CDelayedInstance(CAttributes *a,CXform *x,CArray<CObject *> *in) : CSurface(a,x) {
	stats.numDelayeds++;

	instance		=	in;
	processed		=	FALSE;

	xform->transformBound(this->cbmin,this->cbmax);
	makeBound(this->cbmin,this->cbmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDelayedInstance
// Method				:	~CDelayedInstance
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	8/10/2001
CDelayedInstance::~CDelayedInstance() {
	stats.numDelayeds--;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDelayedInstance
// Method				:	intersect
// Description			:	See object.h
// Return Value			:	-
// Comments				:
// Date last edited		:	8/10/2001
int		CDelayedInstance::intersect(const float *bmin,const float *bmax) const {
	return intersectBox(bmin,bmax,this->cbmin,this->cbmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDelayedInstance
// Method				:	intersect
// Description			:	See object.h
// Return Value			:	-
// Comments				:
// Date last edited		:	8/10/2001
void	CDelayedInstance::intersect(CRay *cRay) {
	float	tmin	=	cRay->tmin;
	float	tmax	=	cRay->t;

	if (hierarchyIntersectBox(this->cbmin,this->cbmax,cRay->from,cRay->to,tmin,tmax)) {
		osLock(CRenderer::delayedMutex);

		if (processed == FALSE) {
			CRenderer::context->processDelayedInstance(this,cRay);
			processed	=	TRUE;
		}

		osUnlock(CRenderer::delayedMutex);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDelayedInstance
// Method				:	bound
// Description			:	See object.h
// Return Value			:	-
// Comments				:
// Date last edited		:	8/10/2001
void	CDelayedInstance::bound(float *bmin,float *bmax) const {
	movvv(bmin,this->cbmin);
	movvv(bmax,this->cbmax);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CDelayedInstance
// Method				:	split
// Description			:	See object.h
// Return Value			:	-
// Comments				:
// Date last edited		:	8/10/2001
void	CDelayedInstance::tesselate(CShadingContext *context) {
	CRenderer::addTracable(this,this);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDelayedInstance
// Method				:	dice
// Description			:	See object.h
// Return Value			:	-
// Comments				:
// Date last edited		:	8/10/2001
void	CDelayedInstance::dice(CShadingContext *r) {
	osLock(CRenderer::delayedMutex);

	if (processed == FALSE) {
		CRenderer::context->processDelayedInstance(this);
		processed	=	TRUE;
	}

	osUnlock(CRenderer::delayedMutex);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDelayedInstance
// Method				:	instantiate
// Description			:	See object.h
// Return Value			:	-
// Comments				:
// Date last edited		:	8/10/2001
void	CDelayedInstance::instantiate(CAttributes *a,CXform *x,CRendererContext *c) const {
	CXform			*nx					=	new CXform(x);

	nx->concat(xform);

	if (a == NULL)	a	=	attributes;

	c->addObject(new CDelayedInstance(a,nx,instance));
}
