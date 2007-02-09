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
//  File				:	implicitSurface.h
//  Classes				:	CImplicit
//  Description			:	Defines an implicit surface
//
////////////////////////////////////////////////////////////////////////
#ifndef IMPLICITSURFACE_H
#define IMPLICITSURFACE_H

#include "common/global.h"
#include "common/os.h"
#include "implicit.h"
#include "object.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CImplicit
// Description			:	This class encapsulates an implicit surface defined by a signed distance function
// Comments				:
class	CImplicit : public CSurface {
public:
								CImplicit(CAttributes *,CXform *,int,const char *,float,float);
								~CImplicit();

								// Object interface
	void						intersect(CShadingContext *,CRay *);
	void						dice(CShadingContext *);												// Split or render this object
	void						instantiate(CAttributes *,CXform *,CRendererContext *) const;			// Instanciate this object

								// Surface functionality
	void						sample(int,int,float **,float ***,unsigned int &) const;				// Sample the surface of the object
	void						interpolate(int,float **,float ***)	const;								// Interpolate the variables
	void						shade(CShadingContext *,int,CRay **);									// Shade the object


private:
	implicitInitFunction		initFunction;			// DSO functions
	implicitEvalFunction		evalFunction;
	implicitEvalNormalFunction	evalNormalFunction;
	implicitTiniFunction		tiniFunction;

	void						*handle;				// Handle
	void						*data;					// Implicit data
	float						stepSize;				// The step size for the matching
	float						scaleFactor;			// The scale factor for the transformation
};

#endif

