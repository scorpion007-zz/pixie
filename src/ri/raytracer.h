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
#include "shading.h"



///////////////////////////////////////////////////////////////////////
// Class				:	CRaytracer
// Description			:	Encapsulates a primary camera ray
// Comments				:
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
class	CRaytracer : public CShadingContext {
public:
									CRaytracer(int thread);
			virtual					~CRaytracer();

			static void				preDisplaySetup() { }

			// The main hider interface
			// The following functions are commented out for we want the CShadingContext to handle those
			void					renderingLoop();

			// Since we're not doing any rasterization, the following functions are simple stubs

			// Delayed rendering functions
			void					drawObject(CObject *) { }

			// Primitive creation functions
			void					drawGrid(CSurface *,int,int,float,float,float,float) { }
			void					drawPoints(CSurface *,int) { }
protected:
			// Sampling functions
			void					sample(int,int,int,int);
			void					computeSamples(CPrimaryRay *,int);
			void					splatSamples(CPrimaryRay *,int,int,int,int,int);

			CPrimaryBundle			primaryBundle;

			float					*fbContribution;
			float					*fbPixels;

			// Some stats
			int						numRaytraceRays;
};

#endif

