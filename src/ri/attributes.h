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
//  File				:	attributes.h
//  Classes				:	CAttributes
//  Description			:	Holds the attributes attached to an object
//
////////////////////////////////////////////////////////////////////////
#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include "common/global.h"		// The global header file
#include "common/algebra.h"		// Matrix - vector stuff
#include "common/containers.h"	// Misc data structures
#include "xform.h"				// Transformations
#include "shader.h"				// Shader stuff

class	CPhotonMap;

// Constant definitions for the flag field of the attributes
const	unsigned int		ATTRIBUTES_FLAGS_INSIDE						=	1;			// Flip the orientation
const	unsigned int		ATTRIBUTES_FLAGS_CUSTOM_ST					=	1 << 1;		// Explicit surface st
const	unsigned int		ATTRIBUTES_FLAGS_MATTE						=	1 << 2;		// The object is matte
const	unsigned int		ATTRIBUTES_FLAGS_CUSTOM_BOUND				=	1 << 3;		// The bound of the object is explicitly set
const	unsigned int		ATTRIBUTES_FLAGS_BINARY_DICE				=	1 << 4;		// Use binary dicing on the surface
const	unsigned int		ATTRIBUTES_FLAGS_SINGULARITYFIX				=	1 << 5;		// Fix the possible surface singularities
const	unsigned int		ATTRIBUTES_FLAGS_PRIMARY_VISIBLE			=	1 << 6;		// The primitive is visible to the primary rays
const	unsigned int		ATTRIBUTES_FLAGS_PHOTON_VISIBLE				=	1 << 7;		// The primitive is visible to the photon rays
const	unsigned int		ATTRIBUTES_FLAGS_TRACE_VISIBLE				=	1 << 8;		// The primitive is visible to the trace rays
const	unsigned int		ATTRIBUTES_FLAGS_TRANSMISSION_VISIBLE		=	1 << 9;		// The primitive is visible to the primary rays
const	unsigned int		ATTRIBUTES_FLAGS_DISPLACEMENTS				=	1 << 14;	// The primitive is visible to the photon rays
const	unsigned int		ATTRIBUTES_FLAGS_IMMEDIATE_RENDERING		=	1 << 16;	// We do immediate rendering
const	unsigned int		ATTRIBUTES_FLAGS_ILLUMINATE_FRONT_ONLY		=	1 << 17;	// During the photon tracing, only photons that hit the front will be traced
const	unsigned int		ATTRIBUTES_FLAGS_LOD						=	1 << 18;	// A detail range has been specified
const	unsigned int		ATTRIBUTES_FLAGS_DISCARD_GEOMETRY			=	1 << 19;	// Discard geometry calls
const	unsigned int		ATTRIBUTES_FLAGS_DISCARD_ALL				=	1 << 20;	// Discard all calls
const	unsigned int		ATTRIBUTES_FLAGS_NONRASTERORIENT_DICE		=	1 << 21;	// Perform non raster-oriented dicing
const	unsigned int		ATTRIBUTES_FLAGS_SHADE_HIDDEN				=	1 << 22;	// Shade even if occluded
const	unsigned int		ATTRIBUTES_FLAGS_SHADE_BACKFACE				=	1 << 23;	// Shade even if backfacing


// The minimum shading rate
const	float				ATTRIBUTES_MIN_SHADINGRATE					=	C_EPSILON;

///////////////////////////////////////////////////////////////////////
// Class				:	CActiveLight
// Description			:	Holds an active light source instance
// Comments				:
// Date last edited		:	2/9/2003
class	CActiveLight {
public:
	CProgrammableShaderInstance		*light;
	CActiveLight					*next;
};

// The shading model
typedef enum {
	SM_MATTE,
	SM_TRANSLUCENT,
	SM_CHROME,
	SM_GLASS,
	SM_WATER,
	SM_DIELECTRIC,
	SM_TRANSPARENT
} EShadingModel;

///////////////////////////////////////////////////////////////////////
// Class				:	CAttributes
// Description			:	This class encapsulates the attributes attached
//							to a surface. Surfaces that have the same set of 
//							attributes share a common clone to avoid unnecessary
//							memory allocation.
// Comments				:
// Date last edited		:	2/9/2003
class CAttributes {
public: 
							CAttributes();
							CAttributes(const CAttributes *);
		virtual				~CAttributes();

		void				attach()	{	refCount++;	}
		void				detach()	{	refCount--; if (refCount == 0) delete this; }
		void				check()		{	if (refCount == 0)	delete this;			}

		void				addLight(CShaderInstance *);				// Add or remove a lightsource from the environment
		void				removeLight(CShaderInstance *);
		void				checkParameters();							// Re-compute the required shader parameters
		CVariable			*findParameter(const char *);				// Find a shader parameter

		int					refCount;									// Refcount used by the objects and the general graphics state
		
		CAttributes			*next;										// points to the next attribute if there's motion blur

		CShaderInstance		*surface;									// Shaders attached to the primitive
		CShaderInstance		*displacement;
		CShaderInstance		*atmosphere;
		CShaderInstance		*interior;
		CShaderInstance		*exterior;
		unsigned int		usedParameters;								// The set of used parameters that the shaders need

		vector				surfaceColor;								// Default surface color and opacity
		vector				surfaceOpacity;

		float				s[4],t[4];									// The texture coordinates

		vector				bmin,bmax;									// The custom bounding box if given
		float				bexpand;									// Bounding box expansion percentage

		matrix				uBasis,vBasis;								// The basis for bicubic patches
		int					uStep,vStep;								// The step sizes for bicubic patches

		unsigned int		nSides;										// Number of sides

		unsigned int		flags;										// Attribute flags

		int					minSubdivision,maxSubdivision;				// Min - Max depths of the refinement tree

																		// Tesselation attributes
		float				flatness;									// The pixel space flatness
		float				pointDeviation;								// The maximum flatness amount
		float				normalDeviation;							// The normal deviation

		float				maxDisplacement;							// Maximum amount of displacement in camera system
		char				*maxDisplacementSpace;						// The current space in which the maximum displacement is given

		CActiveLight		*lightSources;								// The list of active light sources

		float				shadingRate;								// Shading rate for this primitive
		float				motionFactor;								// Amount to increase shading rate when motion blurring
						
		char				*name;										// The name of the object if any

		int					numUProbes,numVProbes;						// The samples to gather when estimating the extend of a patch
		int					minSplits;									// The minimum number of splits
		float				rasterExpand;								// The expansion coefficient during the sampling
		float				shadowBias;									// The bias amount expressed in the camera coordinates

		char				transmission;								// Either:
																		// 'o'	=	opaque
																		// 'i'	=	Os
																		// 's'	=	execute

		int					emit;										// The number of photons to emit from this light source
		float				relativeEmit;								// The relative emittance

		EShadingModel		shadingModel;								// The surface shading model

		char				*globalMapName;								// The name of the global photon map
		char				*causticMapName;							// The name of the caustic photon map
		CPhotonMap			*globalMap;									// The global photon map
		CPhotonMap			*causticMap;								// The caustic photon map
		char				*irradianceHandle;							// The irradiance cache
		char				*irradianceHandleMode;						// The irradiance cache mode
		float				irradianceMaxError;							// The error threshold for the irradiance cache
		float				irradianceMaxPixelDistance;					// The maximum pixel distance between the samples for trradiance caching
		int					photonEstimator;							// The total number of photons to use to estimate irradiance
		float				photonIor[2];								// Index of refraction range used for the dielectic shading model
		int					maxDiffuseDepth;							// The maximum number of diffuse bounces before going to the photon map
		int					maxSpecularDepth;							// The maximum number of specular bounces before giving up
		int					shootStep;									// The step size for shooting rays for the attached object
		
		float				lodRange[4];								// LOD variables
		float				lodSize;
		float				lodImportance;
};

#endif

