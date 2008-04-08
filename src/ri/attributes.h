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
#include "userAttributes.h"		// Attribute dictionary stuff

class	CPhotonMap;

// Constant definitions for the flag field of the attributes
const	unsigned int		ATTRIBUTES_FLAGS_INSIDE						=	1;			// Flip the orientation
const	unsigned int		ATTRIBUTES_FLAGS_CUSTOM_ST					=	1 << 1;		// Explicit surface st
const	unsigned int		ATTRIBUTES_FLAGS_MATTE						=	1 << 2;		// The object is matte
const	unsigned int		ATTRIBUTES_FLAGS_CUSTOM_BOUND				=	1 << 3;		// The bound of the object is explicitly set
const	unsigned int		ATTRIBUTES_FLAGS_BINARY_DICE				=	1 << 4;		// Use binary dicing on the surface
const	unsigned int		ATTRIBUTES_FLAGS_PRIMARY_VISIBLE			=	1 << 6;		// The primitive is visible to the primary rays
const	unsigned int		ATTRIBUTES_FLAGS_PHOTON_VISIBLE				=	1 << 7;		// The primitive is visible to the photon rays
const	unsigned int		ATTRIBUTES_FLAGS_SPECULAR_VISIBLE			=	1 << 9;		// The primitive is visible to the gather/trace/environment rays
const	unsigned int		ATTRIBUTES_FLAGS_DIFFUSE_VISIBLE			=	1 << 10;	// The primitive is visible to the gather/occlusion/diffuse rays
const	unsigned int		ATTRIBUTES_FLAGS_TRANSMISSION_VISIBLE		=	1 << 11;	// The primitive is visible to the transmission/shadow rays
const	unsigned int		ATTRIBUTES_FLAGS_DISPLACEMENTS				=	1 << 14;	// The primitive is visible to the photon rays
const	unsigned int		ATTRIBUTES_FLAGS_ILLUMINATE_FRONT_ONLY		=	1 << 17;	// During the photon tracing, only photons that hit the front will be traced
const	unsigned int		ATTRIBUTES_FLAGS_LOD						=	1 << 18;	// A detail range has been specified
const	unsigned int		ATTRIBUTES_FLAGS_DISCARD_GEOMETRY			=	1 << 19;	// Discard geometry calls
const	unsigned int		ATTRIBUTES_FLAGS_DISCARD_ALL				=	1 << 20;	// Discard all calls
const	unsigned int		ATTRIBUTES_FLAGS_NONRASTERORIENT_DICE		=	1 << 21;	// Perform non raster-oriented dicing
const	unsigned int		ATTRIBUTES_FLAGS_SHADE_HIDDEN				=	1 << 22;	// Shade even if occluded
const	unsigned int		ATTRIBUTES_FLAGS_SHADE_BACKFACE				=	1 << 23;	// Shade even if backfacing
const	unsigned int		ATTRIBUTES_FLAGS_DOUBLE_SIDED				=	1 << 24;	// The surface is double sided
const	unsigned int		ATTRIBUTES_FLAGS_SAMPLEMOTION				=	1 << 25;	// Sample the time in tracing rays


// The minimum shading rate
const	float				ATTRIBUTES_MIN_SHADINGRATE					=	C_EPSILON;

///////////////////////////////////////////////////////////////////////
// Class				:	CActiveLight
// Description			:	Holds an active light source instance
// Comments				:
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
class CAttributes : public CRefCounter {
public: 
							CAttributes();
							CAttributes(const CAttributes *);
		virtual				~CAttributes();

		void				addLight(CShaderInstance *);				// Add or remove a lightsource from the environment
		void				removeLight(CShaderInstance *);
		void				checkParameters();							// Re-compute the required shader parameters
		CVariable			*findParameter(const char *);				// Find a shader parameter
		void				restore(const CAttributes *other,int shading,int geometrymodification,int geometrydefinition,int hiding);
		int					find(const char *name,const char *category,EVariableType &type,const void *&value,int &intValue,float &floatValue) const;
		
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

		unsigned int		flags;										// Attribute flags

		float				maxDisplacement;							// Maximum amount of displacement in camera system
		char				*maxDisplacementSpace;						// The current space in which the maximum displacement is given

		CActiveLight		*lightSources;								// The list of active light sources

		float				shadingRate;								// Shading rate for this primitive
		float				motionFactor;								// Amount to increase shading rate when motion blurring
						
		char				*name;										// The name of the object if any

		int					numUProbes,numVProbes;						// The samples to gather when estimating the extend of a patch
		int					minSplits;									// The minimum number of splits
		float				rasterExpand;								// The expansion coefficient during the sampling
		float				bias;										// The bias amount expressed in the camera coordinates

		char				transmissionHitMode;						// Either: 'p' = Look at the primitive   or   's' = Execute the shader
		char				specularHitMode;							// Either: 'p' = Look at the primitive   or   's' = Execute the shader
		char				diffuseHitMode;								// Either: 'p' = Look at the primitive   or   's' = Execute the shader
		char				cameraHitMode;								// Either: 'p' = Look at the primitive   or   's' = Execute the shader

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
		
		CUserAttributeDictionary		userAttributes;					// Duh.

static	char				findHitMode(const char *mode);
static	const char			*findHitMode(char mode);
static	EShadingModel		findShadingModel(const char *name);
static	const char			*findShadingModel(EShadingModel model);

};

#endif

