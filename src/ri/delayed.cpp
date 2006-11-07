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
CDelayedObject::CDelayedObject(CAttributes *a,CXform *x,const float *bmin,const float *bmax,void	(*subdivisionFunction)(void *,float),void	(*freeFunction)(void *),void *data,int *drc) : CObject(a,x) {
	stats.numDelayeds++;

	movvv(this->bmin,bmin);
	movvv(this->bmax,bmax);
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

	xform->transformBound(this->bmin,this->bmax);
	makeBound(this->bmin,this->bmax);
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
void	CDelayedObject::intersect(CShadingContext *context,CRay *cRay) {
		

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
// Date last edited		:	8/10/2001
void	CDelayedObject::dice(CShadingContext *r) {
	

	if (processed == FALSE) {
		osLock(CRenderer::delayedMutex);
		if (processed == FALSE) {
			CRenderer::context->processDelayedObject(r,this,subdivisionFunction,data,bmin,bmax);
			processed	=	TRUE;
		}
		osUnlock(CRenderer::delayedMutex);
	}
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
CDelayedInstance::CDelayedInstance(CAttributes *a,CXform *x,CObject *in) : CObject(a,x) {
	stats.numDelayeds++;

	instance		=	in;
	processed		=	FALSE;

	initv(bmin,C_INFINITY);
	initv(bmax,-C_INFINITY);

	CObject	*cObject;
	for (cObject=instance;cObject!=NULL;cObject=cObject->sibling) {
		addBox(bmin,bmax,cObject->bmin);
		addBox(bmin,bmax,cObject->bmax);
	}
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
void	CDelayedInstance::intersect(CShadingContext *context,CRay *cRay) {
	
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
// Date last edited		:	8/10/2001
void	CDelayedInstance::dice(CShadingContext *r) {
	

	if (processed == FALSE) {
		osLock(CRenderer::delayedMutex);
		if (processed == FALSE) {
			CRenderer::context->processDelayedInstance(r,this);
			processed	=	TRUE;
		}
		osUnlock(CRenderer::delayedMutex);
	}
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
