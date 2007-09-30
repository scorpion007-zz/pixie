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
//  File				:	delayed.cpp
//  Classes				:	CDelayedObject
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "delayed.h"
#include "stats.h"
#include "renderer.h"
#include "rendererContext.h"


///////////////////////////////////////////////////////////////////////
// Class				:	CDelayedObject
// Method				:	CDelayedObject
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CDelayedObject::CDelayedObject(CAttributes *a,CXform *x,const float *bmin,const float *bmax,void	(*subdivisionFunction)(void *,float),void	(*freeFunction)(void *),void *data,int *drc) : CObject(a,x) {
	atomicIncrement(&stats.numDelayeds);

	movvv(this->bmin,bmin);
	movvv(this->bmax,bmax);
	this->subdivisionFunction	=	subdivisionFunction;
	this->freeFunction			=	freeFunction;
	this->data					=	data;

	processed					=	FALSE;

	// Save the object space bounding box
	movvv(objectBmin,bmin);
	movvv(objectBmax,bmax);

	if (drc == NULL) {
		dataRefCount			=	new int;
		dataRefCount[0]			=	0;
	} else {
		dataRefCount			=	drc;
	}

	dataRefCount[0]++;

	xform->transformBound(this->bmin,this->bmax);
	makeBound(this->bmin,this->bmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDelayedObject
// Method				:	~CDelayedObject
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CDelayedObject::~CDelayedObject() {
	atomicDecrement(&stats.numDelayeds);

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
void	CDelayedObject::intersect(CShadingContext *context,CRay *cRay) {
		
	// Process the object
	if (processed == FALSE) {
		osLock(CRenderer::delayedMutex);
		if (processed == FALSE) {
			CRenderer::context->processDelayedObject(context,this,subdivisionFunction,data,bmin,bmax);
			processed	=	TRUE;
		}
		osUnlock(CRenderer::delayedMutex);
	}
}



///////////////////////////////////////////////////////////////////////
// Class				:	CDelayedObject
// Method				:	dice
// Description			:	See object.h
// Return Value			:	-
// Comments				:
void	CDelayedObject::dice(CShadingContext *r) {
	
	// Process the object
	if (processed == FALSE) {
		osLock(CRenderer::delayedMutex);
		if (processed == FALSE) {
			CRenderer::context->processDelayedObject(r,this,subdivisionFunction,data,bmin,bmax);
			processed	=	TRUE;
		}
		osUnlock(CRenderer::delayedMutex);
	}

	// Let the parent dice it
	CObject::dice(r);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDelayedObject
// Method				:	instantiate
// Description			:	See object.h
// Return Value			:	-
// Comments				:
void	CDelayedObject::instantiate(CAttributes *a,CXform *x,CRendererContext *c) const {
	CXform			*nx					=	new CXform(x);

	nx->concat(xform);

	if (a == NULL)	a	=	attributes;

	c->addObject(new CDelayedObject(a,nx,objectBmin,objectBmax,subdivisionFunction,freeFunction,data,dataRefCount));
}












///////////////////////////////////////////////////////////////////////
// Class				:	CDelayedInstance
// Method				:	CDelayedInstance
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CDelayedInstance::CDelayedInstance(CAttributes *a,CXform *x,CObject *in) : CObject(a,x) {
	atomicIncrement(&stats.numDelayeds);

	instance		=	in;
	processed		=	FALSE;

	initv(bmin,C_INFINITY);
	initv(bmax,-C_INFINITY);

	CObject	*cObject;
	for (cObject=instance;cObject!=NULL;cObject=cObject->sibling) {
		addBox(bmin,bmax,cObject->bmin);
		addBox(bmin,bmax,cObject->bmax);
	}

	xform->transformBound(this->bmin,this->bmax);
	makeBound(this->bmin,this->bmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDelayedInstance
// Method				:	~CDelayedInstance
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CDelayedInstance::~CDelayedInstance() {
	atomicDecrement(&stats.numDelayeds);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CDelayedInstance
// Method				:	intersect
// Description			:	See object.h
// Return Value			:	-
// Comments				:
void	CDelayedInstance::intersect(CShadingContext *context,CRay *cRay) {
	
	// Process the instance
	if (processed == FALSE) {
		osLock(CRenderer::delayedMutex);
		if (processed == FALSE) {
			CRenderer::context->processDelayedInstance(context,this);
			processed	=	TRUE;
		}
		osUnlock(CRenderer::delayedMutex);
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CDelayedInstance
// Method				:	dice
// Description			:	See object.h
// Return Value			:	-
// Comments				:
void	CDelayedInstance::dice(CShadingContext *r) {
	
	// Process the instance
	if (processed == FALSE) {
		osLock(CRenderer::delayedMutex);
		if (processed == FALSE) {
			CRenderer::context->processDelayedInstance(r,this);
			processed	=	TRUE;
		}
		osUnlock(CRenderer::delayedMutex);
	}

	// Let the parent take care of the instance
	CObject::dice(r);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDelayedInstance
// Method				:	instantiate
// Description			:	See object.h
// Return Value			:	-
// Comments				:
void	CDelayedInstance::instantiate(CAttributes *a,CXform *x,CRendererContext *c) const {
	CXform			*nx					=	new CXform(x);

	nx->concat(xform);

	if (a == NULL)	a	=	attributes;

	c->addObject(new CDelayedInstance(a,nx,instance));
}

