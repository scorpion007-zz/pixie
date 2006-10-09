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
//  File				:	raytracer.h
//  Classes				:	CRaytracer
//							and helper classes
//  Description			:	The raytracer hider
//
////////////////////////////////////////////////////////////////////////
#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "common/global.h"
#include "object.h"
#include "options.h"
#include "output.h"
#include "hierarchy.h"
#include "shading.h"



///////////////////////////////////////////////////////////////////////
// Class				:	CRaytracer
// Description			:	Encapsulates a primary camera ray
// Comments				:
// Date last edited		:	3/20/2003
class	CPrimaryRay : public CRay {
public:
	vector	color;					// Color of the ray
	vector	opacity;				// Opacity of the ray
	vector	ropacity;				// Residual opacity
	float	*samples;				// The extra samples that need to be saved
	float	x,y;					// The x,y location of the ray on the screen
};


///////////////////////////////////////////////////////////////////////
// Class				:	CRaytracer
// Description			:	Defines a raytracer
// Comments				:
// Date last edited		:	3/20/2003
class	CPrimaryBundle : public CRayBundle {
public:
				CPrimaryBundle(int,int,int,int*,int,float*);
				~CPrimaryBundle();

	int			postTraceAction();
	void		postShade(int nr,CRay **r,float **varyings);
	void		postShade(int nr,CRay **r);
	void		post();

	CPrimaryRay	*rayBase;			// The ray memory
	int			maxPrimaryRays;		// The maximum number of primary rays
	int			numExtraChannels;	// The number of extra channels
	int			numExtraSamples;	// The number of extra samples
	int			*sampleOrder;		// The order of the extra samples
	float		*sampleDefaults;	// The defaults for the extra samples
	float		*allSamples;		// The memory area for all the samples
};


///////////////////////////////////////////////////////////////////////
// Class				:	CRaytracer
// Description			:	Defines a raytracer
// Comments				:
// Date last edited		:	8/26/2001
class	CRaytracer : public CShadingContext {
public:
									CRaytracer(COptions *,CXform *,SOCKET);
			virtual					~CRaytracer();

			// The main hider interface
			// The following functions are commented out for we want the CShadingContext to handle those
			void					renderFrame();									// Right after world end to force rendering of the entire frame

			// Since we're not doing any rasterization, the following functions are simple stubs

			// Delayed rendering functions
			void					drawObject(CObject *,const float *,const float *) { }

			// Primitive creation functions
			void					drawGrid(CSurface *,int,int,float,float,float,float) { }
			void					drawRibbon(CSurface *,int,float,float) { }
			void					drawPoints(CSurface *,int) { }
protected:
			// Sampling functions
			void					sample(int,int,int,int);
			void					computeSamples(CPrimaryRay *,int);
			void					splatSamples(CPrimaryRay *,int,int,int,int,int);

			CPrimaryBundle			primaryBundle;

			float					*fbContribution;
			float					*fbPixels;
};

#endif





