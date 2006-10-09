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
//  File				:	ray.h
//  Classes				:	CRay
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef	RAY_H
#define RAY_H

#include "common/global.h"
#include "common/algebra.h"

class	CSurface;

////////////////////////////////////////////////////////////////////////////////////
// Ray class ---
// This class is the heart of the message system
// It holds data about the execution environment in the form of void pointers
// Every class that touches the ray class sets the corresponding pointers
class CRay  {
public:
						// ------------------> I N P U T
	vector				from,to;					// The ray in global space
	float				time;						// The time of the ray (shutterOpen <= time <= shutterClose)
	int					flags;						// The flags that must be on in the object's attributes
	float				t;							// The maximum intersection
	float				tmin;						// The intersection bias
	float				jimp;						// The jittered importance (-ve means not set yet)

						// ------------------> O U T P U T
	CSurface			*object;					// The intersection object
	float				u,v;						// The parametric intersection coordinates
	vector				N;							// The normal vector at the intersection

						// ------------------> I N T E R M E D I A T E
	vector				dir,invDir;					// 1 / dir
	vector				oFrom,oTo,oDir;				// The ray in object space
	void				*lastXform;					// Pointer to the xform for which oFrom,oTo,oDir are valid
	int					ID;							// Last checked object ID
	CRay				*child;						// For keeping track of the opacity
};


#endif



