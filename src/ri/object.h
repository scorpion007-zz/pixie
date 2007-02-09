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
#include "renderer.h"

const unsigned int	GEOMETRY_FORCE_VARYING	=	1;	// Force vertex variables to be varying
const unsigned int	GEOMETRY_FORCE_VERTEX	=	2;	// Force varying variables to be vertex


class	CVariable;
class	CShadingContext;
class	CVolume;
class	CRendererContext;
class	CTesselationPatch;

// Various object flags
const unsigned int	OBJECT_DUMMY				=	1;	// Set if the object is a dummy object
const unsigned int	OBJECT_TESSELATION			=	2;	// Set if the object is an intermediate tesselation
const unsigned int	OBJECT_MOVING_TESSELATION	=	4;	// Set if the object is an intermediate tesselation which is moving

///////////////////////////////////////////////////////////////////////
// Class				:	CObject
// Description			:	This class encapsulates a general object
// Comments				:
class	CObject {
public:
							CObject(CAttributes *,CXform *);
	virtual					~CObject();

							// Instance management
	inline	void			attach()	{	refCount++;													}
	inline	void			detach()	{	refCount--;	if (refCount == 0)	delete this;				}
	inline	void			check()		{	if (refCount == 0)	delete this;							}
	inline	int				raytraced()	{	return (attributes->flags & CRenderer::raytracingFlags);	}

							///////////////////////////////////////////////////////////////
							//
							// !!! IMPORTANT !!!
							//
							// All objects must override the following functions
							//
							//	
	virtual	void			intersect(CShadingContext *,CRay *)								=	0;
	virtual	void			dice(CShadingContext *);
	virtual	void			instantiate(CAttributes *,CXform *,CRendererContext *) const	=	0;

														// Take a list of objects and cluster them
			CObject			*cluster(CShadingContext *,CObject *);	

														// Set the children objects
			void			setChildren(CShadingContext *,CObject *);

			void			destroy();					// Delete the children/siblings

	int						flags;						// Holds object flags
	CAttributes				*attributes;				// Holds the object attributes
	CXform					*xform;						// Holds the object xform to the object space
	int						refCount;					// The reference counter
	CObject					*children,*sibling;			// The hierarchy
	vector					bmin,bmax;					// The bounding box
protected:
	void					makeBound(float *,float *) const;
};


///////////////////////////////////////////////////////////////////////
// Class				:	CDummyObject
// Description			:	A dummy object
// Comments				:
class	CDummyObject : public CObject {
public:
							CDummyObject(CAttributes *,CXform *);
	virtual					~CDummyObject();

	virtual	void			intersect(CShadingContext *,CRay *);
	virtual	void			instantiate(CAttributes *,CXform *,CRendererContext *) const	{	assert(FALSE);	}
};


///////////////////////////////////////////////////////////////////////
// Class				:	CSurface
// Description			:	This class encapsulates a 2D surface
// Comments				:
class	CSurface : public CObject {
public:
							CSurface(CAttributes *a,CXform *x) : CObject(a,x) { }
							~CSurface() { }

							// CObject interface
	virtual	void			intersect(CShadingContext *,CRay *);						// Intersect a ray with the surface
	virtual	void			dice(CShadingContext *);									// Split or render this object
	
							// CSurface interface
	virtual	int				moving() const;												// TRUE if we're moving
	virtual	void			sample(int,int,float **,float ***,unsigned int &) const;	// Sample the surface of the object
	virtual	void			interpolate(int,float **,float ***)	const;					// Interpolate the variables
	virtual	void			shade(CShadingContext *,int,CRay **);						// Shade the object

protected:


			// The following two functions can be used to estimate the shading rate and the dicing amount
			float			estimateShadingRate(const float *P0,const float *P1);
			void			estimateDicing(const float *P,int udiv,int vdiv,int &nudiv,int &nvdiv,float shadingRate);
};

#endif

