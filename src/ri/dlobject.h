//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright � 1999 - 2003, Okan Arikan
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
//  File				:	dlobject.h
//  Classes				:	CDLObject
//  Description			:	Defines a dynamically loaded object
//
////////////////////////////////////////////////////////////////////////
#ifndef DLOBJECT_H
#define DLOBJECT_H

#include "common/global.h"
#include "common/os.h"
#include "dlo.h"
#include "object.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CDLObject
// Description			:	This class defines an object that is dynamically loaded
// Comments				:
class	CDLObject : public CSurface {
public:
								CDLObject(CAttributes *,CXform *,void *,void *,const float *,const float *,dloInitFunction,dloIntersectFunction,dloTiniFunction);
								~CDLObject();

								// Object interface
	void						intersect(CShadingContext *,CRay *);
	void						dice(CShadingContext *);												// Split or render this object
	void						instantiate(CAttributes *,CXform *,CRendererContext *) const;			// Instanciate this object

								// Surface interface
	void						sample(int,int,float **,unsigned int &) const;							// Sample the surface of the object
	void						interpolate(int,float **)	const;										// Interpolate the variables
	void						shade(CShadingContext *,int,CRay **);									// Shade the object


private:
	dloInitFunction				initFunction;
	dloIntersectFunction		intersectFunction;
	dloTiniFunction				tiniFunction;

	void						*handle;				// Handle
	void						*data;					// Implicit data
};

#endif


