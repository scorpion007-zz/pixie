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
//  File				:	delayed.h
//  Classes				:	CDelayed
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef DELAYED_H
#define DELAYED_H

#include "common/global.h"
#include "object.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CDelayedData
// Description			:	This is a simple container used by the rib interface for procedural dynamic objects
// Comments				:
class	CDelayedData {
public:
							CDelayedData() {
								generator	=	NULL;
								helper		=	NULL;
							}

							~CDelayedData() {
								if (generator != NULL)	free(generator);
								if (helper != NULL)		free(helper);
							}

	char					*generator;
	char					*helper;
	vector					bmin,bmax;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CDelayedObject
// Description			:	Contains a delayed object
// Comments				:
class	CDelayedObject : public CObject {
public:
							CDelayedObject(CAttributes *,CXform *,const float *,const float *,void	(*subdivisionFunction)(void *,float),void	(*freeFunction)(void *),void *,int *drc=NULL);
							~CDelayedObject();

							// Object interface
	void					intersect(CShadingContext *,CRay *);
	void					dice(CShadingContext *);
	void					instantiate(CAttributes *,CXform *,CRendererContext *) const;
	
	void					(*subdivisionFunction)(void *,float);
	void					(*freeFunction)(void *);
	void					*data;
	int						*dataRefCount;

	vector					objectBmin,objectBmax;

	int						processed;
};


///////////////////////////////////////////////////////////////////////
// Class				:	CDelayedInstance
// Description			:	Contains an instance object
// Comments				:
class	CDelayedInstance : public CObject {
public:
							CDelayedInstance(CAttributes *,CXform *,CObject *);
							~CDelayedInstance();

							// Object interface
	void					intersect(CShadingContext *,CRay *);
	void					dice(CShadingContext *);
	void					instantiate(CAttributes *,CXform *,CRendererContext *) const;
	
	CObject					*instance;
	int						processed;
};


#endif

