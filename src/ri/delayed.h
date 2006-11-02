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
// Date last edited		:	8/10/2001
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

	char			*generator;
	char			*helper;
	vector			bmin,bmax;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CDelayedObject
// Description			:	Contains a delayed object
// Comments				:
// Date last edited		:	8/10/2001
class	CDelayedObject : public CSurface , public CTracable {
public:
							CDelayedObject(CAttributes *,CXform *,const float *,const float *,void	(*subdivisionFunction)(void *,float),void	(*freeFunction)(void *),void *,int *drc=NULL);
							~CDelayedObject();

	void					tesselate(CShadingContext *);
	void					dice(CShadingContext *);
	int						intersect(const float *,const float *) const;
	void					intersect(CRay *,int &);
	void					bound(float *,float *) const;
	int						moving() const													{	return FALSE;		}
	void					copy(CAttributes *,CXform *,CRendererContext *) const;

	void					(*subdivisionFunction)(void *,float);
	void					(*freeFunction)(void *);
	void					*data;
	int						*dataRefCount;

	int						processed;

	vector					bmin,bmax;					// Bound in the object space
	vector					cbmin,cbmax;				// Bound in the camera space

};

///////////////////////////////////////////////////////////////////////
// Class				:	CDelayedInstance
// Description			:	Contains an instance object
// Comments				:
// Date last edited		:	8/10/2001
class	CDelayedInstance : public CSurface , public CTracable {
public:
							CDelayedInstance(CAttributes *,CXform *,CArray<CObject *> *);
							~CDelayedInstance();

	void					tesselate(CShadingContext *);
	void					dice(CShadingContext *);
	int						intersect(const float *,const float *) const;
	void					intersect(CRay *,int &);
	void					bound(float *,float *) const;
	int						moving() const													{	return FALSE;		}
	void					copy(CAttributes *,CXform *,CRendererContext *) const;

	CArray<CObject *>		*instance;
	int						processed;

	vector					bmin,bmax;					// Bound in the object space
	vector					cbmin,cbmax;				// Bound in the camera space

};
#endif





