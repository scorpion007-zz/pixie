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
#include "hierarchy.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CImplicit
// Description			:	This class encapsulates an implicit surface defined by a signed distance function
// Comments				:
// Date last edited		:	3/11/2001
class	CImplicit : public CSurface , public CTracable {
public:
								CImplicit(CAttributes *,CXform *,int,const char *,float,float);
								~CImplicit();

								// Raytracing functionality
	int							intersect(CRay *);
	int							intersect(const float *,const float *) const;

								// Object functionality
	void						bound(float *,float *) const;											// Compute the bounding box
	void						sample(int,int,float **,unsigned int &) const;							// Sample the surface of the object
	void						interpolate(int,float **)	const;										// Interpolate the variables
	void						tesselate(CShadingContext *);											// Create a raytraceable object for this
	void						dice(CShadingContext *);												// Split or render this object
	void						copy(CAttributes *,CXform *,CRendererContext *) const;					// Instanciate this object
	void						shade(CShadingContext *,int,CRay **);									// Shade the object


private:
	implicitInitFunction		initFunction;			// DSO functions
	implicitEvalFunction		evalFunction;
	implicitEvalNormalFunction	evalNormalFunction;
	implicitTiniFunction		tiniFunction;

	vector						bmin,bmax;				// Bounding box
	vector						cameraBmin,cameraBmax;	// The camera space bounding box
	void						*handle;				// Handle
	void						*data;					// Implicit data
	float						stepSize;				// The step size for the matching
	float						scaleFactor;			// The scale factor for the transformation
};

#endif


