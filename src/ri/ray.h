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
	vector				from,dir;					// The ray in camera coordinate system
	float				time;						// The time of the ray (0 <= time <= 1)
	int					flags;						// The intersection flags
	float				t;							// The maximum intersection (if intersection, this is overwritten)
	float				tmin;						// The intersection bias
	float				da,db;						// The linear ray differential (r = da*t + db)

						// ------------------> O U T P U T
	CSurface			*object;					// The intersection object (NULL if no intersection)
	float				u,v;						// The parametric intersection coordinates on the object
	vector				N;							// The normal vector at the intersection

						// ------------------> I N T E R M E D I A T E
	float				jimp;						// The jittered importance (sampled automatically before tracing)
	dvector				invDir;						// 1/dir
	CRay				*child;						// For keeping track of the opacity
};


#endif

