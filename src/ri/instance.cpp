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
//  File				:	instance.cpp
//  Classes				:	CObjectInstance
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "instance.h"
#include "renderer.h"
#include "shading.h"
#include "stats.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CObjectInstance
// Method				:	CObjectInstance
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	10/30/2002
CObjectInstance::CObjectInstance(CAttributes *a,CXform *x,CArray<CObject *> *o) : CObject(a,x) {
	stats.numGprims++;
	stats.gprimMemory	+=	sizeof(CObjectInstance);

	objects	=	o;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CObjectInstance
// Method				:	~CObjectInstance
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	10/30/2002
CObjectInstance::~CObjectInstance() {
	// I should not delete the objects array as it is a renderer resource
	stats.numGprims--;
	stats.gprimMemory	-=	sizeof(CObjectInstance);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CObjectInstance
// Method				:	bound
// Description			:	See object.h
// Return Value			:	-
// Comments				:
// Date last edited		:	10/30/2002
void			CObjectInstance::bound(float *bmin,float *bmax) const {
	CObject	**all		=	objects->array;
	int		numObjects	=	objects->numItems;
	vector	tbmin,tbmax;
	int		i;

	initv(bmin,C_INFINITY,C_INFINITY,C_INFINITY);
	initv(bmax,-C_INFINITY,-C_INFINITY,-C_INFINITY);

	for (i=0;i<numObjects;i++) {
		all[i]->bound(tbmin,tbmax);
		addBox(bmin,bmax,tbmin);
		addBox(bmin,bmax,tbmax);
	}

	xform->transformBound(bmin,bmax);
	makeBound(bmin,bmax);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CObjectInstance
// Method				:	copy
// Description			:	See object.h
// Return Value			:	-
// Comments				:
// Date last edited		:	10/30/2002
void			CObjectInstance::copy(CAttributes *a,CXform *x,CRendererContext *c) const {
	CObject	**all		=	objects->array;
	int		numObjects	=	objects->numItems;
	int		i;
	CXform	*nx			=	new CXform(x);

	nx->concat(xform);

	for (i=0;i<numObjects;i++) {
		all[i]->copy(a,nx,c);
	}

	nx->check();
}


