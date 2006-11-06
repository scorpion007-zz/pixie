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
//  File				:	object.h
//  Classes				:	CObject
//  Description			:	(All the computation is in camera system)
//
////////////////////////////////////////////////////////////////////////
#ifndef OBJECT_H
#define OBJECT_H

#include "common/global.h"
#include "attributes.h"
#include "xform.h"
#include "ray.h"
#include "rendererc.h"

const unsigned int	GEOMETRY_FORCE_VARYING	=	1;	// Force vertex variables to be varying
const unsigned int	GEOMETRY_FORCE_VERTEX	=	2;	// Force varying variables to be vertex


class	CVariable;
class	CShadingContext;
class	CVolume;
class	CRendererContext;


///////////////////////////////////////////////////////////////////////
// Class				:	CObject
// Description			:	This class encapsulates a general object
// Comments				:
// Date last edited		:	3/11/2001
class	CObject {
public:
							CObject(CAttributes *,CXform *);
	virtual					~CObject();



							// Instance management
	inline	void			attach()	{	refCount++;		}

							// Instance management
	inline	void			detach()	{	refCount--;	if (refCount == 0)	delete this;	}

							// Instance management						
	inline	void			check()		{	if (refCount == 0)	delete this;				}


							///////////////////////////////////////////////////////////////
							//
							// !!! IMPORTANT !!!
							//
							// All objects must override the following functions
							//
							//	
	virtual	void			intersect(CShadingContext *,CRay *)								=	NULL;
	virtual	void			dice(CShadingContext *)											=	NULL;
	virtual	void			instantiate(CAttributes *,CXform *,CRendererContext *) const	=	NULL;

							// This function is used to create a bounding volume hierarchy from the children
			void			cluster();

	CAttributes				*attributes;			// Holds the object attributes
	CXform					*xform;					// Holds the object xform to the object space
	int						refCount;				// The reference counter
	CObject					*children,*sibling;		// The hierarchy
	vector					bmin,bmax;				// The bounding box
protected:
	void					makeBound(float *,float *) const;
};


///////////////////////////////////////////////////////////////////////
// Class				:	CDummyObject
// Description			:	A dummy object
// Comments				:
// Date last edited		:	3/11/2001
class	CDummyObject : public CObject {
public:
							CDummyObject(CAttributes *,CXform *);
	virtual					~CDummyObject();

	virtual	void			intersect(CShadingContext *,CRay *);
	virtual	void			dice(CShadingContext *);
	virtual	void			instantiate(CAttributes *,CXform *,CRendererContext *) const	{	assert(FALSE);	}
};


///////////////////////////////////////////////////////////////////////
// Class				:	CSurface
// Description			:	This class encapsulates a general object
// Comments				:
// Date last edited		:	3/11/2001
class	CSurface : public CObject {
public:
							CSurface(CAttributes *,CXform *);
							~CSurface();

							// CObject interface
	virtual	void			intersect(CShadingContext *,CRay *);									// Intersect a ray with the surface
	virtual	void			dice(CShadingContext *);												// Split or render this object
	virtual	void			instantiate(CAttributes *,CXform *,CRendererContext *) const	{	assert(FALSE);	}
	
							// CSurface interface
	virtual	int				moving() const;															// TRUE if we're moving
	virtual	void			sample(int,int,float **,unsigned int &) const;							// Sample the surface of the object
	virtual	void			interpolate(int,float **)	const;										// Interpolate the variables
	virtual	void			shade(CShadingContext *,int,CRay **);									// Shade the object

protected:
			float			*P;		// The grid if sampled
};

#endif



