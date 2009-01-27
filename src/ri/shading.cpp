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
//  File				:	shading.cpp
//  Classes				:	CShadingContext
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include	<stdarg.h>
#include	<math.h>
#include	<string.h>

#include	"shading.h"
#include	"object.h"
#include	"raytracer.h"
#include	"brickmap.h"
#include	"photonMap.h"
#include	"pointCloud.h"
#include	"texture3d.h"
#include	"irradiance.h"
#include	"stats.h"
#include	"memory.h"
#include	"random.h"
#include	"points.h"
#include	"error.h"
#include	"remoteChannel.h"
#include	"renderer.h"
#include	"shaderPl.h"
#include	"ri_config.h"

// George's extrapolated derivative extensions
#define		USE_EXTRAPOLATED_DERIV

// Options that are defined and responded
const	char	*optionsFormat				=	"Format";
const	char	*optionsDeviceFrame			=	"Frame";
const	char	*optionsDeviceResolution	=	"DeviceResolution";
const	char	*optionsFrameAspectRatio	=	"FrameAspectRatio";
const	char	*optionsCropWindow			=	"CropWindow";
const	char	*optionsDepthOfField		=	"DepthOfField";
const	char	*optionsShutter				=	"Shutter";
const	char	*optionsClipping			=	"Clipping";
const	char	*optionsBucketSize			=	"BucketSize";
const	char	*optionsColorQuantizer		=	"ColorQuantizer";
const	char	*optionsDepthQuantizer		=	"DepthQuantizer";
const	char	*optionsPixelFilter			=	"PixelFilter";
const	char	*optionsGamma				=	"Gamma";
const	char	*optionsMaxRayDepth			=	"MaxRayDepth";
const	char	*optionsRelativeDetail		=	"RelativeDetail";
const	char	*optionsPixelSamples		=	"PixelSamples";

// Attributes that are defined and responded
const	char	*attributesShadingRate		=	"ShadingRate";
const	char	*attributesSides			=	"Sides";
const	char	*attributesMatte			=	"matte";
const	char	*attributesMotionfactor		=	"GeometricApproximation:motionfactor";
const	char	*attributesDisplacementBnd	=	"displacementbound:sphere";
const	char	*attributesDisplacementSys	=	"displacementbound:coordinatesystem";
const	char	*attributesName				=	"identifier:name";

const	char	*attributesTraceBias		=	"trace:bias";
const	char	*attributesTraceMaxDiffuse	=	"trace:maxdiffusedepth";
const	char	*attributesTraceMaxSpecular	=	"trace:maxspeculardepth";

const	char	*attributesUser				=	"user:";

// Rendererinfo requests
const	char	*rendererinfoRenderer		=	"renderer";
const	char	*rendererinfoVersion		=	"version";
const	char	*rendererinfoVersionStr		=	"versionstring";

// Predefined ray labels used during raytracing
const	char	*rayLabelPrimary			=	"camera";
const	char	*rayLabelTrace				=	"trace";
const	char	*rayLabelTransmission		=	"transmission";
const	char	*rayLabelGather				=	"gather";


///////////////////////////////////////////////////////////////////////
// Function				:	complete
// Description			:	This function fills in the missing data (not filled by the object) from attributes
// Return Value			:
// Comments				:	Thread safe
inline void	complete(int num,float **varying,unsigned int usedParameters,const CAttributes *attributes1,const CAttributes *attributes2) {
	int		i;

	if (usedParameters & PARAMETER_ALPHA) {
		float	*dest	=	varying[VARIABLE_ALPHA];

		for (i=num;i>0;i--)
			*dest++	=	1;
	}

	if (usedParameters & PARAMETER_S) {
		const float	*u		=	varying[VARIABLE_U];
		float		*s		=	varying[VARIABLE_S];

		if (attributes1->flags & ATTRIBUTES_FLAGS_CUSTOM_ST) {
			const	float	*v		=	varying[VARIABLE_V];
			const	float	*time	=	varying[VARIABLE_TIME];
			const	float	*s1		=	attributes1->s;
			const	float	*s2		=	attributes2->s;

			for (i=num;i>0;i--) {
				const	double	ctime	=	*time++;
				const	double	cu		=	*u++;
				const	double	cv		=	*v++;

				*s++			=	(float) (((s1[0]*(1.0-ctime) + s2[0]*ctime)*(1.0-cu) + 
											 (s1[1]*(1.0-ctime) + s2[1]*ctime)*cu)*(1.0-cv) + 
											((s1[2]*(1.0-ctime) + s2[2]*ctime)*(1.0-cu) + 
											 (s1[3]*(1.0-ctime) + s2[3]*ctime)*cu)*cv);
			}
		} else {
			memcpy(s,u,num*sizeof(float));
		}
	}

	if (usedParameters & PARAMETER_T) {
		const float	*v		=	varying[VARIABLE_V];
		float		*t		=	varying[VARIABLE_T];

		if (attributes1->flags & ATTRIBUTES_FLAGS_CUSTOM_ST) {
			const	float	*u		=	varying[VARIABLE_U];
			const	float	*time	=	varying[VARIABLE_TIME];
			const	float	*t1		=	attributes1->t;
			const	float	*t2		=	attributes2->t;

			for (i=num;i>0;i--) {
				const	double	ctime	=	*time++;
				const	double	cu		=	*u++;
				const	double	cv		=	*v++;

				*t++			=	(float) (((t1[0]*(1.0-ctime) + t2[0]*ctime)*(1.0-cu) + 
										     (t1[1]*(1.0-ctime) + t2[1]*ctime)*cu)*(1.0-cv) + 
											((t1[2]*(1.0-ctime) + t2[2]*ctime)*(1.0-cu) + 
											 (t1[3]*(1.0-ctime) + t2[3]*ctime)*cu)*cv);
				u++;
				v++;
				time++;
			}
		} else {
			memcpy(t,v,num*sizeof(float));
		}
	}

	if (usedParameters & PARAMETER_CS) {
		float			*dest	=	varying[VARIABLE_CS];
		const	float	*time	=	varying[VARIABLE_TIME];
		const	float	*c1		=	attributes1->surfaceColor;
		const	float	*c2		=	attributes2->surfaceColor;


		for (i=num;i>0;i--) {
			interpolatev(dest,c1,c2,*time++);
			dest	+=	3;
		}
	}

	if (usedParameters & PARAMETER_OS) {
		float			*dest	=	varying[VARIABLE_OS];
		const	float	*time	=	varying[VARIABLE_TIME];
		const	float	*c1		=	attributes1->surfaceOpacity;
		const	float	*c2		=	attributes2->surfaceOpacity;

		for (i=num;i>0;i--) {
			interpolatev(dest,c1,c2,*time++);
			dest	+=	3;
		}
	}

	// If the coordinate system is right handed, flip the normal vector
	if (attributes1->flags & ATTRIBUTES_FLAGS_INSIDE)  {
		float	*src	=	varying[VARIABLE_NG];
		float	*src2	=	varying[VARIABLE_N];

		for (i=num;i>0;i--) {
			mulvf(src,-1);
			mulvf(src2,-1);
			src		+=	3;
			src2	+=	3;
		}
	}

	// Copy the normal vector
	if (usedParameters & PARAMETER_N) {
		memcpy(varying[VARIABLE_N],varying[VARIABLE_NG],3*num*sizeof(float));
	}

	// ensure Oi and Ci are always filled in
	if (!(usedParameters & PARAMETER_CI)) {
		float			*dest	=	varying[VARIABLE_CI];
		const	float	*time	=	varying[VARIABLE_TIME];
		const	float	*c1		=	attributes1->surfaceColor;
		const	float	*c2		=	attributes2->surfaceColor;


		for (i=num;i>0;i--) {
			interpolatev(dest,c1,c2,*time);
			dest	+=	3;
			time	++;
		}
	}

	if (!(usedParameters & PARAMETER_OI)) {
		float			*dest	=	varying[VARIABLE_OI];
		const	float	*time	=	varying[VARIABLE_TIME];
		const	float	*c1		=	attributes1->surfaceOpacity;
		const	float	*c2		=	attributes2->surfaceOpacity;

		for (i=num;i>0;i--) {
			interpolatev(dest,c1,c2,*time);
			dest	+=	3;
			time	++;
		}
	}
	
	// Finally, range-correct time
	// Note: It is important this is last, as before this we assume a 0-1
	// range for time.  After this we must never use time assuing 0-1 range
	if (usedParameters & (PARAMETER_TIME | PARAMETER_DTIME)) {
	
		varying[VARIABLE_DTIME][0]	=	CRenderer::shutterClose - CRenderer::shutterOpen;
		
		float		*time			=	varying[VARIABLE_TIME];
		const float idtime			= 	CRenderer::invShutterTime;
		const float t0				=	CRenderer::shutterOpen;
		
		for (i=num;i>0;i--) {
			time[0] = (time[0]*idtime + t0);
			time++;
		}
	}
	
}

///////////////////////////////////////////////////////////////////////
// Function				:	complete
// Description			:	This function fills in the missing data (not filled by the object) from attributes
// Return Value			:
// Comments				:	Thread safe
inline	void	complete(int num,float **varying,unsigned int usedParameters,const CAttributes *attributes) {
	int		i;

	if (usedParameters & PARAMETER_ALPHA) {
		float	*dest	=	varying[VARIABLE_ALPHA];

		for (i=num;i>0;i--)
			*dest++	=	1;
	}

	if (usedParameters & PARAMETER_S) {
		const	float	*u		=	varying[VARIABLE_U];
		float			*s		=	varying[VARIABLE_S];

		if (attributes->flags & ATTRIBUTES_FLAGS_CUSTOM_ST) {
			const	float	*v		=	varying[VARIABLE_V];
			const	float	*sCoord	=	attributes->s;

			for (i=num;i>0;i--) {
				const double uu = *u;
				const double vv = *v;
				*s++		=	(float) ((sCoord[0]*(1.0-uu) + sCoord[1]*uu)*(1.0-vv) + (sCoord[2]*(1.0-uu) + sCoord[3]*uu)*vv);
				u++;
				v++;
			}
		} else {
			memcpy(s,u,num*sizeof(float));
		}
	}

	if (usedParameters & PARAMETER_T) {
		const float	*v		=	varying[VARIABLE_V];
		float		*t		=	varying[VARIABLE_T];

		if (attributes->flags & ATTRIBUTES_FLAGS_CUSTOM_ST) {
			const	float	*u		=	varying[VARIABLE_U];
			const	float	*tCoord	=	attributes->t;

			for (i=num;i>0;i--) {
				const double uu = *u;
				const double vv = *v;
				*t++		=	(float) ((tCoord[0]*(1.0-uu) + tCoord[1]*uu)*(1.0-vv) + (tCoord[2]*(1.0-uu) + tCoord[3]*uu)*vv);
				u++;
				v++;
			}
		} else {
			memcpy(t,v,num*sizeof(float));
		}
	}

	if (usedParameters & PARAMETER_CS) {
		float			*dest	=	varying[VARIABLE_CS];
		const	float	*src	=	attributes->surfaceColor;

		for (i=num;i>0;i--) {
			movvv(dest,src);
			dest	+=	3;
		}
	}

	if (usedParameters & PARAMETER_OS) {
		float			*dest	=	varying[VARIABLE_OS];
		const	float	*src	=	attributes->surfaceOpacity;

		for (i=num;i>0;i--) {
			movvv(dest,src);
			dest	+=	3;
		}
	}

	if (attributes->flags & ATTRIBUTES_FLAGS_INSIDE) {
		float	*src	=	varying[VARIABLE_NG];

		for (i=num;i>0;i--) {
			mulvf(src,-1);
			src		+=	3;
		}
	}

	if (usedParameters & PARAMETER_N) {
		memcpy(varying[VARIABLE_N],varying[VARIABLE_NG],3*num*sizeof(float));
	}
	
	// ensure Oi and Ci are always filled in
	if (!(usedParameters & PARAMETER_CI)) {
		float			*dest	=	varying[VARIABLE_CI];
		const	float	*src	=	attributes->surfaceColor;

		for (i=num;i>0;i--) {
			movvv(dest,src);
			dest	+=	3;
		}
	}

	if (!(usedParameters & PARAMETER_OI)) {
		float			*dest	=	varying[VARIABLE_OI];
		const	float	*src	=	attributes->surfaceOpacity;

		for (i=num;i>0;i--) {
			movvv(dest,src);
			dest	+=	3;
		}
	}
	
	// Finally, range-correct time
	// Note: It is important this is last, as before this we assume a 0-1
	// range for time.  After this we must never use time assuing 0-1 range
	if (usedParameters & (PARAMETER_TIME | PARAMETER_DTIME)) {
		
		varying[VARIABLE_DTIME][0]	=	CRenderer::shutterClose - CRenderer::shutterOpen;
		
		float		*time		=	varying[VARIABLE_TIME];
		const float idtime		= 	CRenderer::invShutterTime;
		const float t0			=	CRenderer::shutterOpen;
		
		for (i=num;i>0;i--) {
			time[0] = (time[0]*idtime + t0);
			time++;
		}
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	CShadingContext
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CShadingContext::CShadingContext(int t) : thread(t) {
	// Initialize the shading state
	currentShadingState		=	NULL;
	
	// Initialize the shader state memory stack
	memoryInit(shaderStateMemory);

	// Initialize the thread memory stack
	memoryInit(threadMemory);

	// Init the bucket we're rendering
	currentXBucket			=	0;
	currentYBucket			=	0;

	// Init the conditionals
	conditionals			=	NULL;
	currentRayDepth			=	0;
	currentRayLabel			=	rayLabelPrimary;
	freeStates				=	NULL;
	inShadow				=	FALSE;

	// (globalMemory is checkpointed)
	traceObjectHash			=	(TObjectHash *) ralloc(sizeof(TObjectHash)*SHADING_OBJECT_CACHE_SIZE,CRenderer::globalMemory);

	// Fill the object pointers with impossible data
	for (int i=0;i<SHADING_OBJECT_CACHE_SIZE;i++)	traceObjectHash[i].object	=	(CSurface *) this;

	// Init the PL hash
	for (int i=0;i<PL_HASH_SIZE;i++) plHash[i]	=	NULL;

	// Init the random number generator
	randomInit(5489*(thread+1));

	// Init the stats
	numIndirectDiffuseRays				=	0;
	numIndirectDiffuseSamples			=	0;
	numOcclusionRays					=	0;
	numOcclusionSamples					=	0;
	numIndirectDiffusePhotonmapLookups	=	0;
	numShade							=	0;
	numSampled							=	0;
	numShaded							=	0;
	vertexMemory						=	0;
	peakVertexMemory					=	0;
	numTracedRays						=	0;
	numReflectionRays					=	0;
	numTransmissionRays					=	0;
	numGatherRays						=	0;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	~CShadingContext
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CShadingContext::~CShadingContext() {

	// Delete the conditionals we allocated
	CConditional	*cConditional;
	while((cConditional = conditionals) != NULL) {
		conditionals	=	conditionals->next;
		delete cConditional;
	}
	
	// Shutdown the random number generator
	randomShutdown();

	// Ditch the PL hash
	for (int i=0;i<PL_HASH_SIZE;i++) {
		CPLLookup	*cLookup;
		while((cLookup=plHash[i]) != NULL) {
			plHash[i]	=	cLookup->next;
			delete cLookup;
		}
	}

	// Ditch the shading states that have been allocated
	assert(currentShadingState != NULL);
	freeState(currentShadingState);
	CShadingState	*cState;
	while ((cState=freeStates) != NULL) {
		freeStates	=	cState->next;

		freeState(cState);
	}
	currentShadingState	=	NULL;
	
	// Ditch the thread memory stack
	memoryTini(threadMemory);

	// Ditch the shader state memory stack
	memoryTini(shaderStateMemory);

	// The frame assertions
	assert(vertexMemory == 0);

	// Update the global statistics
	stats.numIndirectDiffuseRays				+=	numIndirectDiffuseRays;
	stats.numIndirectDiffuseSamples				+=	numIndirectDiffuseSamples;
	stats.numOcclusionRays						+=	numOcclusionRays;
	stats.numOcclusionSamples					+=	numOcclusionSamples;
	stats.numIndirectDiffusePhotonmapLookups	+=	numIndirectDiffusePhotonmapLookups;
	stats.numShade								+=	numShade;
	stats.numSampled							+=	numSampled;
	stats.numShaded								+=	numShaded;
	stats.numTracedRays							+=	numTracedRays;
	stats.numReflectionRays						+=	numReflectionRays;
	stats.numTransmissionRays					+=	numTransmissionRays;
	stats.numGatherRays							+=	numGatherRays;
}




///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	renderPrimitive
// Description			:	Add an object into the scene
// Return Value			:
// Comments				:
void	CShadingContext::drawObject(CObject *cObject) {
	// This function must be overriden
}






///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	shade2D
// Description			:	Sample/Shade bunch of points
// Return Value			:	-
// Comments				:	Thread safe
//
//
//
//	Preconditions:
//	!!!	->	u,v,time,I		fields of varying must be set
void	CShadingContext::shade(CSurface *object,int uVertices,int vVertices,EShadingDim dim,unsigned int usedParameters,int displaceOnly) {
	const CAttributes	*currentAttributes	=	object->attributes;
	float				**varying			=	currentShadingState->varying;
	float				***locals			= 	currentShadingState->locals;
	CShaderInstance		*displacement;
	CShaderInstance		*surface;
	CShaderInstance		*atmosphere;
	int					i;
	CSurface			*savedObject;

	assert(uVertices > 0);
	assert(vVertices > 0);

	// This is the number of vertices we will be sampling/shading
	int	numVertices		=	uVertices*vVertices;
	assert(numVertices <= CRenderer::maxGridSize);
	assert(numVertices > 0);

	// Update the stats
	numShade++;
	numSampled			+=	numVertices;

	// Are we just displacing the surface ?
	if (displaceOnly == FALSE) {

		// Are we in a shadow ray ?
		if (inShadow == TRUE) {

			// Yes, are we supposed to shade the objects in the shadow ?
			if (currentAttributes->transmissionHitMode == 'p') {

				// No, just copy the color/opacity from the attributes field
				float			*opacity	=	varying[VARIABLE_OI];
				int				i;
				const	float	*so			=	currentAttributes->surfaceOpacity;

				for (i=numVertices;i>0;i--,opacity+=3)	movvv(opacity,so);

				// Nothing more to do here, just return
				return;
			}

			// The transmission must be shade at this point
			assert(currentAttributes->transmissionHitMode == 's');
			
			// We need to execute the shaders
			displacement	=	NULL;	//currentAttributes->displacement;	// We probably don't need to execute the displacement shader
			surface			=	currentAttributes->surface;
			atmosphere		=	NULL;

		} else {
			// check the hit mode

			// If we're raytracing, are we supposed to shade hit rays?
			if ((dim == SHADING_2D) && (currentAttributes->specularHitMode == 'p')) {
				// No, just copy the color/opacity from the attributes field
				float			*opacity	=	varying[VARIABLE_OI];
				float			*color		=	varying[VARIABLE_CI];
				int				i;
				const	float	*so			=	currentAttributes->surfaceOpacity;
				const	float	*sc			=	currentAttributes->surfaceColor;

				for (i=numVertices;i>0;i--,opacity+=3,color+=3) {
					movvv(opacity,so);
					movvv(color,sc);
				}

				// Nothing more to do here, just return
				return;
			}

			// We need to execute the shaders
			if (currentAttributes->flags & ATTRIBUTES_FLAGS_MATTE) {
				displacement	=	currentAttributes->displacement;
				surface			=	currentAttributes->surface;				// execute the surface shader for the output opacity
				atmosphere		=	NULL;
			} else {
				displacement	=	currentAttributes->displacement;
				surface			=	currentAttributes->surface;
				atmosphere		=	currentAttributes->atmosphere;
			}
		}

		// Prepare the used parameters by the shaders 
		usedParameters			|=	currentAttributes->usedParameters | CRenderer::additionalParameters;
		
		// Prepare the locals
		for (int a=0;a<NUM_ACCESSORS;a++) locals[a] = NULL;
	} else {

		// We are only interested in the surface position, not the color
#ifdef IGNORE_DISPLACEMENTS_FOR_DICING
		if (	(currentAttributes->displacement == NULL) || 
			(	(usedParameters & PARAMETER_RAYTRACE) && (!(currentAttributes->flags & ATTRIBUTES_FLAGS_DISPLACEMENTS))) ||
				(displaceOnly & 2)
			) {
#else
		if (	(currentAttributes->displacement == NULL) || 
			(	(usedParameters & PARAMETER_RAYTRACE) && (!(currentAttributes->flags & ATTRIBUTES_FLAGS_DISPLACEMENTS)))) {
#endif
			const int	savedParameters	=	usedParameters;

			// No, just sample the geometry
			// Note: we pass NULL for each of the locals here because we do not wish
			// to expand them (we're not running shaders) yet.  This causes the
			// interpolation to local shader vars from the pl not to occur
			for (int a=0;a<NUM_ACCESSORS;a++) locals[a] = NULL;
			
			object->sample(0,numVertices,varying,locals,usedParameters);
			object->interpolate(numVertices,varying,locals);

			// We're not shading just sampling
			if (usedParameters & PARAMETER_N) {
				assert(savedParameters & PARAMETER_NG);

				// Flip the normal vector ?
				if (currentAttributes->flags & ATTRIBUTES_FLAGS_INSIDE) {
					int		i	=	numVertices;
					float	*N	=	varying[VARIABLE_NG];

					for (;i>0;i--) {
						*N++	*=	-1;
						*N++	*=	-1;
						*N++	*=	-1;
					}
				}

				memcpy(varying[VARIABLE_N],varying[VARIABLE_NG],numVertices*3*sizeof(float));
			}

			// We're done here
			return;
		}
		
		// Prepare the locals
		for (int a=0;a<NUM_ACCESSORS;a++) locals[a] = NULL;

		// We need to execute the displacement shader, so get ready
		displacement	=	currentAttributes->displacement;
		surface			=	NULL;
		atmosphere		=	NULL;

		// Note: we check for message passing with displacement and prepare appopriately below
	}

	
	// We're shading
	savedObject							=	currentShadingState->currentObject;
	currentShadingState->currentObject	=	object;
	currentShadingState->numUvertices	=	uVertices;
	currentShadingState->numVvertices	=	vVertices;
	currentShadingState->numVertices	=	numVertices;

	// Checkpoint the shader state stack
	memBegin(shaderStateMemory);
	
	// Allocate the caches for the shaders being executed
	if (surface != NULL)							locals[ACCESSOR_SURFACE]		=	surface->prepare(shaderStateMemory,varying,numVertices);
	if (displacement != NULL)						locals[ACCESSOR_DISPLACEMENT]	=	displacement->prepare(shaderStateMemory,varying,numVertices);
	if (atmosphere != NULL)							locals[ACCESSOR_ATMOSPHERE]		=	atmosphere->prepare(shaderStateMemory,varying,numVertices);

	if (displaceOnly == TRUE) {
		// Verify if we have to prepare other shaders, even though displacing
		// due to message passing this _has_ to be after the shaderStateMemory checkPoint
		usedParameters	=	displacement->requiredParameters() | PARAMETER_P | PARAMETER_N;
		
		if (usedParameters & PARAMETER_MESSAGEPASSING) {
			// displacement shader uses messsage passing, must prepare but not execute
			// the surface and atmosphere shaders
			if (currentAttributes->surface != NULL)			locals[ACCESSOR_SURFACE]		=	currentAttributes->surface->prepare(shaderStateMemory,varying,numVertices);
			if (currentAttributes->atmosphere != NULL)		locals[ACCESSOR_ATMOSPHERE]		=	currentAttributes->atmosphere->prepare(shaderStateMemory,varying,numVertices);
		}
	}

	
	// We do not prepare interior or exterior as these are limited to passing default values (no outputs, they don't recieve pl variables)

	// If we need derivative information, treat differently
	if ((usedParameters & PARAMETER_DERIVATIVE) && (dim != SHADING_0D)) {	// Notice: we can not differentiate a 0 dimentional point set
	
		if (dim == SHADING_2D) {											// We're raytracing, so the derivative computation is different
			const int numRealVertices				=	numVertices;
			numVertices								*=	3;					// For the extra derivative vertices
			currentShadingState->numVertices		=	numVertices;
			currentShadingState->numRealVertices	=	numRealVertices;
			currentShadingState->shadingDim			=	SHADING_2D;
			currentShadingState->numActive			=	numVertices;
			currentShadingState->numPassive			=	0;

			// Sample the object at the main intersection points
			usedParameters							|=	PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_P;
			const unsigned int shadingParameters	=	usedParameters;
			object->sample(0,numRealVertices,varying,locals,usedParameters);
			usedParameters							=	shadingParameters;		// Restore the required parameters for the second round of shading
			
			float	*dPdu			=	varying[VARIABLE_DPDU];
			float	*dPdv			=	varying[VARIABLE_DPDV];
			float	*du				=	varying[VARIABLE_DU];
			float	*dv				=	varying[VARIABLE_DV];
			float	*u				=	varying[VARIABLE_U];
			float	*v				=	varying[VARIABLE_V];
			float	*time			=	varying[VARIABLE_TIME];
			float	*I				=	varying[VARIABLE_I];
			int		j;

			// Compute du/dv
			for (i=0,j=numRealVertices;i<numRealVertices;i++,I+=3,dPdu+=3,dPdv+=3) {
				const float	lengthu	=	dotvv(dPdu,dPdu);
				const float	lengthv	=	dotvv(dPdv,dPdv);
				const float	lengthi	=	dotvv(I,I);

				float	ku			=	dotvv(I,dPdu);	ku	=	isqrtf((lengthu*lengthi - (ku*ku)) / (lengthu*lengthi + C_EPSILON));
				float	kv			=	dotvv(I,dPdv);	kv	=	isqrtf((lengthv*lengthi - (kv*kv)) / (lengthv*lengthi + C_EPSILON));

				const float	dest	=	du[i];				// The ray crosssection at the intersection
				// Note: we are clamping the maximal du dv because otherwise the surface
				// sampling becomes grossly inaccurate, and in recursive raytracing, db
				// grows unboundedly, causing inf and nan, and messing up filtering
				// These are the 0-1 patch uvs, not the expanded range uvs, so this is OK.
				const float	dud		=	min(ku * dest * isqrtf(lengthu) + C_EPSILON,1.0f);
				const float	dvd		=	min(kv * dest * isqrtf(lengthv) + C_EPSILON,1.0f);
				
				// Create one more shading point at (u + du,v)
				u[j]		=	u[i] + dud;
				v[j]		=	v[i];
				time[j]		=	time[i];
				movvv(varying[VARIABLE_I] + j*3,I);
				du[i]		=	dud;
				du[j]		=	dud;
				dv[j]		=	dvd;
				j++;

				// Create one more shading point at (u,v + dv)
				u[j]		=	u[i];
				v[j]		=	v[i] + dvd;
				time[j]		=	time[i];
				movvv(varying[VARIABLE_I] + j*3,I);
				dv[i]		=	dvd;
				du[j]		=	dud;
				dv[j]		=	dvd;
				j++;
			}

			// Sample the object again, this time at the extra shading points
			object->sample(numRealVertices,2*numRealVertices,varying,locals,usedParameters);

			// Interpolate the various variables defined on the object
			object->interpolate(numVertices,varying,locals);

		} else {
			// We're shading a regular grid, so take the shortcut while computing the surface derivatives
			int				i,j;
			const float		shadingRate				=	currentAttributes->shadingRate;

			assert(dim == SHADING_2D_GRID);

			currentShadingState->numRealVertices	=	numVertices;
			currentShadingState->shadingDim			=	SHADING_2D_GRID;
			currentShadingState->numActive			=	numVertices;
			currentShadingState->numPassive			=	0;

			// First sample the object at the grid vertices
			usedParameters	|=	PARAMETER_P;

			// Sample the object
			object->sample(0,numVertices,varying,locals,usedParameters);

			// Interpolate the various variables defined on the object
			object->interpolate(numVertices,varying,locals);

			// We're rasterizing, so the derivative information is already available
			memBegin(threadMemory);

			// This array holds the projected xy pixel positions for the vertices
			float		*xy		=	(float *) ralloc(numVertices*2*sizeof(float),threadMemory);
			const float	*P		=	varying[VARIABLE_P];
			
			// Project the grid vertices first
			// PS: The offset is not important, so do not compute it
			const float maxdPixeldxy = max(CRenderer::dPixeldx,CRenderer::dPixeldy);
			const float dPixeldx = (currentAttributes->flags & ATTRIBUTES_FLAGS_NONRASTERORIENT_DICE) ? 1.0f : CRenderer::dPixeldx;
			const float dPixeldy = (currentAttributes->flags & ATTRIBUTES_FLAGS_NONRASTERORIENT_DICE) ? 1.0f : CRenderer::dPixeldy;
			if (CRenderer::projection == OPTIONS_PROJECTION_PERSPECTIVE) {
				float	*cXy	=	xy;

				for (i=numVertices;i>0;i--) {
					cXy[0]		=	(P[COMP_X] * CRenderer::imagePlane / P[COMP_Z])*dPixeldx;
					cXy[1]		=	(P[COMP_Y] * CRenderer::imagePlane / P[COMP_Z])*dPixeldy;
					cXy			+=	2;
					P			+=	3;
				}

				// Compute the I
				memcpy(varying[VARIABLE_I],varying[VARIABLE_P],numVertices*3*sizeof(float));
			} else {
				float	*cXy	=	xy;

				for (i=numVertices;i>0;i--) {
					cXy[0]		=	P[COMP_X]*dPixeldx;
					cXy[1]		=	P[COMP_Y]*dPixeldy;
					cXy			+=	2;
					P			+=	3;
				}

				// Compute the I
				float		*I	=	varying[VARIABLE_I];
				P	=	varying[VARIABLE_P];
				for (i=numVertices;i>0;i--,I+=3,P+=3)	initv(I,0,0,P[COMP_Z]);
			}

			float		*du			=	varying[VARIABLE_DU];
			float		*dv			=	varying[VARIABLE_DV];
			const float *u			=	varying[VARIABLE_U];
			const float	*v			=	varying[VARIABLE_V];

			#ifdef USE_EXTRAPOLATED_DERIV
				#define extrapolateDerivU()																\
					if (uVertices > 3) {																\
						const float A =	(cDU[-3] - cDU[-2])/((cU[-3]-cU[-2])*(cU[-3]-cU[-1])) -			\
										(cDU[-1] - cDU[-2])/((cU[-1]-cU[-2])*(cU[-3]-cU[-1]));			\
						const float B =	(cDU[-1] - cDU[-2] + A*(cU[-2]*cU[-2] - cU[-1]*cU[-1])) /		\
										(cU[-1] - cU[-2]);												\
						const float C = (cDU[-1] - A*cU[-1]*cU[-1] - B*cU[-1]);							\
						d		= A*cU[0]*cU[0] + B*cU[0] + C;											\
					}
				
				#define extrapolateDerivV()																														\
					if (vVertices > 3) {																														\
						const float A =	(cDV[-uVertices*3] - cDV[-uVertices*2])/((cV[-uVertices*3]-cV[-uVertices*2])*(cV[-uVertices*3]-cV[-uVertices*1])) -		\
										(cDV[-uVertices*1] - cDV[-uVertices*2])/((cV[-uVertices*1]-cV[-uVertices*2])*(cV[-uVertices*3]-cV[-uVertices*1]));		\
						const float B =	(cDV[-uVertices*1] - cDV[-uVertices*2] + A*(cV[-uVertices*2]*cV[-uVertices*2] - cV[-uVertices*1]*cV[-uVertices*1])) /	\
										(cV[-uVertices*1] - cV[-uVertices*2]);																					\
						const float C = (cDV[-uVertices*1] - A*cV[-uVertices*1]*cV[-uVertices*1] - B*cV[-uVertices*1]);											\
						d		= A*cV[0]*cV[0] + B*cV[0] + C;																									\
					}

			#else
				#define extrapolateDerivU()
				#define extrapolateDerivV()
			#endif

#define	MAX_DIFFERENTIAL_DISCREPANCY	4*shadingRate

			if (!(currentAttributes->flags & ATTRIBUTES_FLAGS_NONRASTERORIENT_DICE)) {
				// Compute the du
				for (i=0;i<vVertices;i++) {
					const int	tmp		=	i*uVertices;
					float		*cDU	=	du	+ tmp;
					const float	*cU		=	u	+ tmp;
					float		*cXy	=	xy	+ tmp*2;
					float		d		=	0;

					for (j=uVertices-1;j>0;j--) {
						const float	dx	=	cXy[2] - cXy[0];
						const float	dy	=	cXy[3] - cXy[1];
						float		cSr	=	shadingRate*isqrtf(dx*dx + dy*dy);
						if (cSr > MAX_DIFFERENTIAL_DISCREPANCY)	cSr	=	MAX_DIFFERENTIAL_DISCREPANCY;
						d		=	cSr*(cU[1] - cU[0]);
						d		=	min(d,1);
						d		=	max(d,C_EPSILON);
						assert(d > 0);
						assert(d <= 1);
						cDU[0]	=	d;
						cDU		+=	1;
						cU		+=	1;
						cXy		+=	2;
					}
	
					extrapolateDerivU();
					
					cDU[0]		=	d;
				}
	
				// Compute the dv,dPdv
				for (i=0;i<uVertices;i++) {
					float		*cDV	=	dv	+	i;
					const float	*cV		=	v	+	i;
					float		*cXy	=	xy	+	i*2;
					float		d		=	0;
	
					for (j=0;j<vVertices-1;j++) {
						const float	dx		=	cXy[uVertices*2]	- cXy[0];
						const float	dy		=	cXy[uVertices*2+1]	- cXy[1];
						float		cSr		=	shadingRate*isqrtf(dx*dx + dy*dy);
						if (cSr > MAX_DIFFERENTIAL_DISCREPANCY)	cSr	=	MAX_DIFFERENTIAL_DISCREPANCY;
						d		=	cSr*(cV[uVertices] - cV[0]);
						d		=	max(d,C_EPSILON);
						d		=	min(d,1);
						assert(d > 0);
						assert(d <= 1);
						cDV[0]	=	d;
						cDV		+=	uVertices;
						cV		+=	uVertices;
						cXy		+=	uVertices*2;
					}
					
					extrapolateDerivV();
					
					cDV[0]		=	d;
				}
				
			} else {
				// Non raster orient
				vector tmp1,tmp2;
			
				// Compute the du
				for (i=0;i<vVertices;i++) {
					const int	tmp		=	i*uVertices;
					float		*cDU	=	du	+ tmp;
					const float	*cU		=	u	+ tmp;
					float		*cXy	=	xy	+ tmp*2;
					float		d		=	0;
	
					P				=	varying[VARIABLE_P]		+	tmp*3;
					for (j=uVertices-1;j>0;j--) {
						initv(tmp1,cXy[2]-P[3],cXy[3]-P[4],P[5]-1);
						initv(tmp2,cXy[0]-P[0],cXy[1]-P[1],P[2]-1);
						const float	dx		=	maxdPixeldxy*(cXy[2] - cXy[0]);
						const float	dy		=	maxdPixeldxy*(cXy[3] - cXy[1]);
						const float	dz		=	maxdPixeldxy*(lengthv(tmp1) - lengthv(tmp2));
	
						float		cSr		=	shadingRate*isqrtf(dx*dx + dy*dy + dz*dz);
						if (cSr > MAX_DIFFERENTIAL_DISCREPANCY)	cSr	=	MAX_DIFFERENTIAL_DISCREPANCY;
						d		=	cSr*(cU[1] - cU[0]);
						d		=	min(d,1);
						d		=	max(d,C_EPSILON);
						assert(d > 0);
						assert(d <= 1);
						cDU[0]	=	d;
						cDU		+=	1;
						cU		+=	1;
						P		+=	3;
						cXy		+=	2;
					}
	
					extrapolateDerivU();
					
					cDU[0]		=	d;
				}
	
				// Compute the dv,dPdv
				for (i=0;i<uVertices;i++) {
					float		*cDV	=	dv	+	i;
					const float	*cV		=	v	+	i;
					float		*cXy	=	xy	+	i*2;
					float		d		=	0;
	
					P				=	varying[VARIABLE_P]		+	i*3;
					for (j=0;j<vVertices-1;j++) {
						initv(tmp1,cXy[uVertices*2]-P[uVertices*3+0],cXy[uVertices*2+1]-P[uVertices*3+1],P[uVertices*3+2]-1);
						initv(tmp2,cXy[0]-P[0],cXy[1]-P[1],P[2]-1);

						const float	dx		=	maxdPixeldxy*(cXy[uVertices*2]		- cXy[0]);
						const float	dy		=	maxdPixeldxy*(cXy[uVertices*2+1]	- cXy[1]);
						const float	dz		=	maxdPixeldxy*(lengthv(tmp1) - lengthv(tmp2));

						float		cSr		=	shadingRate*isqrtf(dx*dx + dy*dy + dz*dz);
						if (cSr > MAX_DIFFERENTIAL_DISCREPANCY)	cSr	=	MAX_DIFFERENTIAL_DISCREPANCY;
						d		=	cSr*(cV[uVertices] - cV[0]);
						d		=	max(d,C_EPSILON);
						d		=	min(d,1);
						assert(d > 0);
						assert(d <= 1);
						cDV[0]	=	d;
						cDV		+=	uVertices;
						cV		+=	uVertices;
						P		+=	uVertices*3;
						cXy		+=	uVertices*2;
					}
					
					extrapolateDerivV();
					
					cDV[0]		=	d;
				}
			}

			#undef MAX_DIFFERENTIAL_DISCREPANCY
			#undef extrapolateDerivU
			#undef extrapolateDerivV

			// Done and done
			memEnd(threadMemory);
		}
	} else {
		// No derivative information is needed
		currentShadingState->shadingDim			=	dim;
		currentShadingState->numRealVertices	=	numVertices;
		currentShadingState->numActive			=	numVertices;
		currentShadingState->numPassive			=	0;

		// Sample the object
		object->sample(0,numVertices,varying,locals,usedParameters);

		// Interpolate the various variables defined on the object
		object->interpolate(numVertices,varying,locals);

		// Compute the I
		if (currentRayDepth == 0) {
			if (CRenderer::projection == OPTIONS_PROJECTION_PERSPECTIVE) {
				memcpy(varying[VARIABLE_I],varying[VARIABLE_P],numVertices*3*sizeof(float));
			} else {
				float		*I	=	varying[VARIABLE_I];
				const float	*P	=	varying[VARIABLE_P];
				for (i=numVertices;i>0;i--,I+=3,P+=3)	initv(I,0,0,P[COMP_Z]);
			}
		}
	}

	// Clear the tags for shader execution
	memset(currentShadingState->tags,0,numVertices*sizeof(int));

	// Fill in the uninitialized variables from the attributes
	if (currentAttributes->next != NULL) {
		complete(numVertices,varying,usedParameters,currentAttributes,currentAttributes->next);
	} else {
		complete(numVertices,varying,usedParameters,currentAttributes);
	}

	// Save the memory here
	memBegin(threadMemory);
	
	// Set up lighting here incase displacement shader uses lighting
	
	// No lights are executed yet
	currentShadingState->lightsExecuted			=	FALSE;
	currentShadingState->ambientLightsExecuted	=	FALSE;
	currentShadingState->lightCategory			=	0;
	
	// Clear out previous lights etc
	currentShadingState->lights					=	NULL;
	currentShadingState->alights				=	NULL;
	currentShadingState->currentLight			=	NULL;
	currentShadingState->freeLights				=	NULL;
		
	// Run the displacement shader here
	if (displacement != NULL) {
		displacement->execute(this,locals[ACCESSOR_DISPLACEMENT]);
	}

	// Do we need to run the surface shader?
	if (displaceOnly == FALSE) {

		// Is there a surface shader ?
		if (surface != NULL) {
			numShaded				+=	numVertices;
			surface->execute(this,locals[ACCESSOR_SURFACE]);
		} else {
			// No surface shader eh, make up a color
			

			// Overwrite the colors if not specified by the primitives
			if (usedParameters & PARAMETER_CS)	{
				const float		*Cs		=	currentAttributes->surfaceColor;
				float			*C		=	varying[VARIABLE_CI];
				for (i=numVertices;i>0;i--,C+=3)	movvv(C,Cs);
			}

			// Overwrite the opacity if not specified by the primitive
			if (usedParameters & PARAMETER_OS)	{
				const float		*Os		=	currentAttributes->surfaceOpacity;
				float			*O		=	varying[VARIABLE_OI];
				for (i=numVertices;i>0;i--,O+=3)	movvv(O,Os);
			}

			// Get the variables
			float			*C		=	varying[VARIABLE_CI];
			float			*N		=	varying[VARIABLE_N];
			float			*I		=	varying[VARIABLE_I];

			// Do a simple dot product shading here
			for (i=numVertices;i>0;i--) {
				normalizevf(N);
				normalizevf(I);

				mulvf(C,absf(dotvv(I,N)));
				C	+=	3;
				N	+=	3;
				I	+=	3;
			}
		}

		// Is there an atmosphere shader ?
		if (atmosphere != NULL) {
		
			// Do not execute atmosphere for non-camera rays
			if (currentRayDepth == 0) {  
				atmosphere->execute(this,locals[ACCESSOR_ATMOSPHERE]);
			}
		}

		// Is there an interior/exterior shader waiting to be executed?
		if (currentShadingState->postShader != NULL) {
			locals[ACCESSOR_POSTSHADER]		=	currentShadingState->postShader->prepare(shaderStateMemory,varying,numVertices);
			currentShadingState->postShader->execute(this,locals[ACCESSOR_POSTSHADER]);
		}
	}


	// Check if we should are a camera ray, and have primitive hit mode
	if ((dim == SHADING_2D_GRID) && (currentAttributes->cameraHitMode == 'p')) {
		// Yes, force opacity 1
		float			*opacity	=	varying[VARIABLE_OI];
		const	float	*so			=	currentAttributes->surfaceOpacity;
		int				i;

		for (i=numVertices;i>0;i--,opacity+=3) movvv(opacity,so);
	}

	// Restore the thread memory
	memEnd(threadMemory);
	
	// Unwind the stack of shader states
	memEnd(shaderStateMemory);

	// Restore the shaded object
	currentShadingState->currentObject	=	savedObject;
}











///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	newState
// Description			:	Allocate a new shading state
// Return Value			:	-
// Comments				:
CShadingState	*CShadingContext::newState() {

	if (freeStates == NULL) {
		CShadingState	*newState			=	new CShadingState;
		int				j;
		float			*E;
		const int		numGlobalVariables	=	CRenderer::globalVariables->numItems;
		CVariable		**globalVariables	=	CRenderer::globalVariables->array;

		newState->varying				=	new float*[numGlobalVariables];					vertexMemory	+=	numGlobalVariables*sizeof(float *);
		newState->tags					=	new int[CRenderer::maxGridSize*3];				vertexMemory	+=	CRenderer::maxGridSize*3*sizeof(int);
		newState->lightingTags			=	new int[CRenderer::maxGridSize*3];				vertexMemory	+=	CRenderer::maxGridSize*3*sizeof(int);
		newState->Ns					=	new float[CRenderer::maxGridSize*9];			vertexMemory	+=	CRenderer::maxGridSize*9*sizeof(float);
		newState->alights				=	NULL;
		newState->freeLights			=	NULL;
		newState->postShader			=	NULL;
		newState->currentObject			=	NULL;

		for (j=0;j<numGlobalVariables;j++) {
			const	CVariable	*var	=	globalVariables[j];

			assert(var != NULL);

			if (	(var->container == CONTAINER_UNIFORM) || (var->container == CONTAINER_CONSTANT)	) {
				if (var->type == TYPE_STRING) {
					newState->varying[j]	=	(float*) new char*[var->numFloats];
					vertexMemory			+=	var->numFloats*sizeof(char*);
				} else {
					newState->varying[j]	=	new float[var->numFloats];
					vertexMemory			+=	var->numFloats*sizeof(float);
				}
			} else {
				if (var->type == TYPE_STRING) {
					newState->varying[j]	=	(float*) new char*[var->numFloats*CRenderer::maxGridSize*3];
					vertexMemory			+=	var->numFloats*CRenderer::maxGridSize*3*sizeof(char*);
				} else {
					newState->varying[j]	=	new float[var->numFloats*CRenderer::maxGridSize*3];
					vertexMemory			+=	var->numFloats*CRenderer::maxGridSize*3*sizeof(float);
				}
			}
		}

		// E is always (0,0,0)
		E	=	newState->varying[VARIABLE_E];
		for (j=CRenderer::maxGridSize*3;j>0;j--,E+=3)	initv(E,0,0,0);

		if (vertexMemory > peakVertexMemory)	peakVertexMemory=	vertexMemory;

		newState->next				=	NULL;
		return	newState;
	} else {
		CShadingState	*newState	=	freeStates;
		freeStates					=	newState->next;

		return newState;
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	newState
// Description			:	Allocate a new shading state
// Return Value			:	-
// Comments				:
void				CShadingContext::deleteState(CShadingState *cState) {
	cState->next	=	freeStates;
	freeStates		=	cState;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	freeState
// Description			:	Ditch a shading state
// Return Value			:	-
// Comments				:
void			CShadingContext::freeState(CShadingState *cState) {
	int			j;
	const int	numGlobalVariables	=	CRenderer::globalVariables->numItems;
	CVariable	**globalVariables	=	CRenderer::globalVariables->array;

	for (j=0;j<numGlobalVariables;j++) {
		const CVariable	*var	=	globalVariables[j];

		if (	(var->container == CONTAINER_UNIFORM) || (var->container == CONTAINER_CONSTANT)	) {
			delete [] cState->varying[j];
			vertexMemory		-=	var->numFloats*sizeof(float);
		} else {
			delete [] cState->varying[j];
			vertexMemory		-=	var->numFloats*CRenderer::maxGridSize*3*sizeof(float);
		}
	}

	delete [] cState->varying;					vertexMemory	-=	numGlobalVariables*sizeof(float *);
	delete [] cState->tags;						vertexMemory	-=	CRenderer::maxGridSize*3*sizeof(int);
	delete [] cState->lightingTags;				vertexMemory	-=	CRenderer::maxGridSize*3*sizeof(int);
	delete [] cState->Ns;						vertexMemory	-=	CRenderer::maxGridSize*9*sizeof(float);
	
	delete cState;
}







///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	variableUpdate
// Description			:	This function is called to signal that there has been
//							a modification on the set of active variables
// Return Value			:	-
// Comments				:
void		CShadingContext::updateState() {
	CShadingState	*cState;

	// Ditch the shading states that have been allocated
	while ((cState=freeStates) != NULL) {
		freeStates	=	cState->next;
		freeState(cState);
	}

	// Recreate
	if (currentShadingState != NULL)	freeState(currentShadingState);

	currentShadingState	=	NULL;
	currentShadingState	=	newState();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	saveState
// Description			:	Save the shading state so a nested tesselation
//							doesn't trash our variables
// Return Value			:	an opaque shading state reference
// Comments				:
void	*CShadingContext::saveState() {
	CShadingState	*savedState		=	currentShadingState;
	if (freeStates == NULL)			freeStates	=	newState();

	currentShadingState				=	freeStates;
	freeStates						=	currentShadingState->next;
	
	return (void*) savedState;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	restoreState
// Description			:	Restore the shading state from a previous save
// Return Value			:	-
// Comments				:
void	CShadingContext::restoreState(void *state) {
	CShadingState	*savedState		=	(CShadingState*) state;
	
	currentShadingState->next		=	freeStates;
	freeStates						=	currentShadingState;

	currentShadingState				=	savedState;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	surfaceParameter
// Description			:	Execute light sources
// Return Value			:	-
// Comments				:
int		CShadingContext::surfaceParameter(void *dest,const char *name,CVariable **var,int *globalIndex) {
	const CAttributes	*currentAttributes	=	currentShadingState->currentObject->attributes;

	if (currentAttributes->surface != NULL)
		return currentAttributes->surface->getParameter(name,dest,var,globalIndex);
	return FALSE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	displacementParameter
// Description			:	Execute light sources
// Return Value			:	-
// Comments				:
int		CShadingContext::displacementParameter(void *dest,const char *name,CVariable **var,int *globalIndex) {
	const CAttributes	*currentAttributes	=	currentShadingState->currentObject->attributes;

	if (currentAttributes->displacement != NULL)
		return currentAttributes->displacement->getParameter(name,dest,var,globalIndex);
	return FALSE;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	atmosphereParameter
// Description			:	Execute light sources
// Return Value			:	-
// Comments				:
int		CShadingContext::atmosphereParameter(void *dest,const char *name,CVariable **var,int *globalIndex) {
	const CAttributes	*currentAttributes	=	currentShadingState->currentObject->attributes;

	if (currentAttributes->atmosphere != NULL)
		return currentAttributes->atmosphere->getParameter(name,dest,var,globalIndex);
	return FALSE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	incidentParameter
// Description			:	Execute light sources
// Return Value			:	-
// Comments				:
int		CShadingContext::incidentParameter(void *dest,const char *name,CVariable **var,int *globalIndex) {
	const CAttributes	*currentAttributes	=	currentShadingState->currentObject->attributes;

	if (currentAttributes->interior != NULL)
		return currentAttributes->interior->getParameter(name,dest,NULL,NULL);	// skip mutable parameters
	return FALSE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	oppositeParameter
// Description			:	Execute light sources
// Return Value			:	-
// Comments				:
int		CShadingContext::oppositeParameter(void *dest,const char *name,CVariable **var,int *globalIndex) {
	const CAttributes	*currentAttributes	=	currentShadingState->currentObject->attributes;

	if (currentAttributes->exterior != NULL)
		return currentAttributes->exterior->getParameter(name,dest,NULL,NULL);	// skip mutable parameters
	return FALSE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	options
// Description			:	Execute light sources
// Return Value			:	-
// Comments				:
int		CShadingContext::options(void *dest,const char *name,CVariable **,int *) {
	if (strcmp(name,optionsFormat) == 0) {
		float	*d	=	(float *) dest;
		d[0]		=	(float) CRenderer::xres;
		d[1]		=	(float) CRenderer::yres;
		d[2]		=	(float) 1;
		return TRUE;
	} else if (strcmp(name,optionsDeviceFrame) == 0) { 
		float	*d	=	(float *) dest;
		d[0]		=	(float) CRenderer::frame;
		return TRUE;
	} else if (strcmp(name,optionsDeviceResolution) == 0) { 
		float	*d	=	(float *) dest;
		d[0]		=	(float) CRenderer::xres;
		d[1]		=	(float) CRenderer::yres;
		d[2]		=	(float) 1;
		return TRUE;
	} else if (strcmp(name,optionsFrameAspectRatio) == 0) { 
		float	*d	=	(float *) dest;
		d[0]		=	(float) CRenderer::frameAR;
		return TRUE;
	} else if (strcmp(name,optionsCropWindow) == 0) { 
		float	*d	=	(float *) dest;
		d[0]		=	(float) CRenderer::cropLeft;
		d[1]		=	(float) CRenderer::cropTop;
		d[2]		=	(float) CRenderer::cropRight;
		d[3]		=	(float) CRenderer::cropBottom;
		return TRUE;
	} else if (strcmp(name,optionsDepthOfField) == 0) { 
		float	*d	=	(float *) dest;
		d[0]		=	(float) CRenderer::fstop;
		d[1]		=	(float) CRenderer::focallength;
		d[2]		=	(float) CRenderer::focaldistance;
		return TRUE;
	} else if (strcmp(name,optionsShutter) == 0) { 
		float	*d	=	(float *) dest;
		d[0]		=	(float) CRenderer::shutterOpen;
		d[1]		=	(float) CRenderer::shutterClose;
		return TRUE;
	} else if (strcmp(name,optionsClipping) == 0) { 
		float	*d	=	(float *) dest;
		d[0]		=	(float) CRenderer::clipMin;
		d[1]		=	(float) CRenderer::clipMax;
		return TRUE;
	} else if (strcmp(name,optionsBucketSize) == 0) { 
		float	*d	=	(float *) dest;
		d[0]		=	(float) CRenderer::bucketWidth;
		d[1]		=	(float) CRenderer::bucketHeight;
		return TRUE;
	} else if (strcmp(name,optionsColorQuantizer) == 0) { 
		float	*d	=	(float *) dest;
		d[0]		=	(float) CRenderer::colorQuantizer[0];
		d[1]		=	(float) CRenderer::colorQuantizer[1];
		d[2]		=	(float) CRenderer::colorQuantizer[2];
		d[3]		=	(float) CRenderer::colorQuantizer[3];
		return TRUE;
	} else if (strcmp(name,optionsDepthQuantizer) == 0) { 
		float	*d	=	(float *) dest;
		d[0]		=	(float) CRenderer::depthQuantizer[0];
		d[1]		=	(float) CRenderer::depthQuantizer[1];
		d[2]		=	(float) CRenderer::depthQuantizer[2];
		d[3]		=	(float) CRenderer::depthQuantizer[3];
		return TRUE;
	} else if (strcmp(name,optionsPixelFilter) == 0) { 
		float	*d	=	(float *) dest;
		d[0]		=	(float) CRenderer::pixelFilterWidth;
		d[1]		=	(float) CRenderer::pixelFilterHeight;
		return TRUE;
	} else if (strcmp(name,optionsGamma) == 0) { 
		float	*d	=	(float *) dest;
		d[0]		=	(float) CRenderer::gamma;
		d[1]		=	(float) CRenderer::gain;
		return TRUE;
	} else if (strcmp(name,optionsMaxRayDepth) == 0) { 
		float	*d	=	(float *) dest;
		d[0]		=	(float) CRenderer::maxRayDepth;
		return TRUE;
	} else if (strcmp(name,optionsRelativeDetail) == 0) { 
		float	*d	=	(float *) dest;
		d[0]		=	(float) CRenderer::relativeDetail;
		return TRUE;
	} else if (strcmp(name,optionsPixelSamples) == 0) { 
		float	*d	=	(float *) dest;
		d[0]		=	(float) CRenderer::pixelXsamples;
		d[1]		=	(float) CRenderer::pixelYsamples;
		return TRUE;
	}
	// User options
	else if (strncmp(name,attributesUser,strlen(attributesUser)) == 0) {
		CVariable *var;
		
		if (CRenderer::userOptions->lookup(name+strlen(attributesUser),var) == TRUE) {
			if (var->type == TYPE_STRING) {
				char **d	=	(char **) dest;
				char **s	=	(char **) var->defaultValue;
				for (int i=0;i<var->numFloats;i++) {
					d[i] = s[i];
				}
			} else {
				float	*d	=	(float *) dest;
				memcpy(d,var->defaultValue,sizeof(float)*var->numFloats);
			}
			return TRUE;
		}
	}
	
	return FALSE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	attributes
// Description			:	Execute light sources
// Return Value			:	-
// Comments				:
int		CShadingContext::attributes(void *dest,const char *name,CVariable **,int *) {
	const CAttributes	*currentAttributes	=	currentShadingState->currentObject->attributes;

	if (strcmp(name,attributesShadingRate) == 0) {
		float	*d	=	(float *) dest;
		d[0]		=	(float) currentAttributes->shadingRate;
		return TRUE;
	} else if (strcmp(name,attributesSides) == 0) {
		float	*d	=	(float *) dest;
		d[0]		=	(float) (currentAttributes->flags & ATTRIBUTES_FLAGS_DOUBLE_SIDED ? 2 : 1);
		return TRUE;
	} else if (strcmp(name,attributesMatte) == 0) {
		float	*d	=	(float *) dest;
		d[0]		=	(float) ((currentAttributes->flags & ATTRIBUTES_FLAGS_MATTE) != 0);
		return TRUE;
	} else if (strcmp(name,attributesMotionfactor) == 0) {
		float	*d	=	(float *) dest;
		d[0]		=	(float) currentAttributes->motionFactor;
		return TRUE;
	} else if (strcmp(name,attributesDisplacementBnd) == 0) {
		float	*d	=	(float *) dest;
		d[0]		=	(float) currentAttributes->maxDisplacement;
		return TRUE;
	} else if (strcmp(name,attributesDisplacementSys) == 0) {
		char	**d	=	(char **) dest;
		d[0]		=	currentAttributes->maxDisplacementSpace;
		return TRUE;
	} else if (strcmp(name,attributesName) == 0) {
		char	**d	=	(char **) dest;
		d[0]		=	currentAttributes->name;
		return TRUE;
	}
	// Additional attributes
	else if (strcmp(name,attributesTraceBias) == 0) {
		float	*d	=	(float *) dest;
		d[0]		=	(float) currentAttributes->bias;
		return TRUE;
	} else if (strcmp(name,attributesTraceMaxDiffuse) == 0) {
		float	*d	=	(float *) dest;
		d[0]		=	(float) currentAttributes->maxDiffuseDepth;
		return TRUE;
	} else if (strcmp(name,attributesTraceMaxSpecular) == 0) {
		float	*d	=	(float *) dest;
		d[0]		=	(float) currentAttributes->maxSpecularDepth;
		return TRUE;
	}
	// User attributes
	else if (strncmp(name,attributesUser,strlen(attributesUser)) == 0) {
		CVariable *var;
		
		if (currentAttributes->userAttributes.lookup(name+strlen(attributesUser),var) == TRUE) {
			if (var->type == TYPE_STRING) {
				char **d	=	(char **) dest;
				char **s	=	(char **) var->defaultValue;
				for (int i=0;i<var->numFloats;i++) {
					d[i] = s[i];
				}
			} else {
				float	*d	=	(float *) dest;
				memcpy(d,var->defaultValue,sizeof(float)*var->numFloats);
			}
			return TRUE;
		}
	}
	
	return FALSE;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	rendererInfo
// Description			:	Execute light sources
// Return Value			:	-
// Comments				:
int		CShadingContext::rendererInfo(void *dest,const char *name,CVariable **,int *) {
	
	if (strcmp(name,rendererinfoRenderer) == 0) {
		char	**d	=	(char **) dest;
		d[0]		=	(char *) "Pixie";
		return TRUE;
	} else if (strcmp(name,rendererinfoVersion) == 0) {
		float	*d	=	(float *) dest;
		d[0]		=	(float) VERSION_RELEASE;
		d[1]		=	(float) VERSION_BETA;
		d[2]		=	(float) VERSION_ALPHA;
		d[3]		=	(float) 0;
		return TRUE;
	}
	
	return FALSE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	shaderName
// Description			:	Get the name of the shader
// Return Value			:	-
// Comments				:
const char	*CShadingContext::shaderName() {
	assert(currentShadingState->currentShaderInstance != NULL);

	return currentShadingState->currentShaderInstance->getName();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	shaderName
// Description			:	Get the name of a particular shader
// Return Value			:	-
// Comments				:
const char	*CShadingContext::shaderName(const char *type) {
	CAttributes	*currentAttributes	=	currentShadingState->currentObject->attributes;

	if (strcmp(type,"surface") == 0) {
		if (currentAttributes->surface != NULL)
			return currentAttributes->surface->getName();
	} else if (strcmp(type,"displacement") == 0) {
		if (currentAttributes->displacement != NULL)
			return currentAttributes->displacement->getName();
	} else if (strcmp(type,"atmosphere") == 0) {
		if (currentAttributes->atmosphere != NULL)
			return currentAttributes->atmosphere->getName();
	} else if (strcmp(type,"interior") == 0) {
		if (currentAttributes->interior != NULL)
			return currentAttributes->interior->getName();
	} else if (strcmp(type,"exterior") == 0) {
		if (currentAttributes->exterior != NULL)
			return currentAttributes->exterior->getName();
	} else if (strcmp(type,"lightsource") == 0) {
		if (currentShadingState->currentLight != NULL)
			return currentShadingState->currentLight->instance->getName();
	}
	return "";
}


///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	findCoordinateSystem
// Description			:	Locate a coordinate system
// Return Value			:	-
// Comments				:	Sometimes we just don't care about what system it is
void		CShadingContext::findCoordinateSystem(const char *name,const float *&from,const float *&to) {
	ECoordinateSystem	dummy;
	
	findCoordinateSystem(name,from,to,dummy);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	findCoordinateSystem
// Description			:	Locate a coordinate system
// Return Value			:	-
// Comments				:
void		CShadingContext::findCoordinateSystem(const char *name,const float *&from,const float *&to,ECoordinateSystem &cSystem) {
	CNamedCoordinateSystem	*currentSystem;

	if(CRenderer::definedCoordinateSystems->find(name,currentSystem)) {
		from		=	currentSystem->from;
		to			=	currentSystem->to;
		cSystem		=	currentSystem->systemType;

		switch(currentSystem->systemType) {
		case COORDINATE_OBJECT:
			if (currentShadingState->currentObject == NULL) {
				error(CODE_SYSTEM,"Object system reference without an object\n");
				from		=	identityMatrix;
				to			=	identityMatrix;
			} else {
				from		=	currentShadingState->currentObject->xform->from;
				to			=	currentShadingState->currentObject->xform->to;
			}
			break;
		case COORDINATE_CAMERA:
			from		=	identityMatrix;
			to			=	identityMatrix;
			break;
		case COORDINATE_WORLD:
			from		=	CRenderer::fromWorld;
			to			=	CRenderer::toWorld;
			break;
		case COORDINATE_SHADER:
			assert(currentShadingState->currentShaderInstance != NULL);

			from		=	currentShadingState->currentShaderInstance->xform->from;
			to			=	currentShadingState->currentShaderInstance->xform->to;
			break;
		case COORDINATE_LIGHT:
			assert(currentShadingState->currentLightInstance != NULL);

			from		=	currentShadingState->currentLightInstance->xform->from;
			to			=	currentShadingState->currentLightInstance->xform->to;
			break;
		case COORDINATE_NDC:
			from		=	CRenderer::fromNDC;
			to			=	CRenderer::toNDC;
			break;
		case COORDINATE_RASTER:
			from		=	CRenderer::fromRaster;
			to			=	CRenderer::toRaster;
			break;
		case COORDINATE_SCREEN:
			from		=	CRenderer::fromScreen;
			to			=	CRenderer::toScreen;
			break;
		case COORDINATE_CURRENT:
			from		=	identityMatrix;
			to			=	identityMatrix;
			break;
		case COLOR_RGB:
		case COLOR_HSL:
		case COLOR_HSV:
		case COLOR_XYZ:
		case COLOR_CIE:
		case COLOR_YIQ:
		case COLOR_XYY:
			// Don't handle color, the custom must have been handled
			break;
		case COORDINATE_CUSTOM:
			// Don't handle color, the custom must have been handled
			from		=	currentSystem->from;
			to			=	currentSystem->to;
			break;
		default:
			warning(CODE_BUG,"Unknown coordinate system: %s\n",name);
			from		=	identityMatrix;
			to			=	identityMatrix;
			break;
		}	
	} else {
		warning(CODE_BUG,"Unknown coordinate system: %s\n",name);
		from	=	identityMatrix;
		to		=	identityMatrix;
	}
}










//Period parameters
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL	//constant vector a
#define UMASK 0x80000000UL		//most significant w-r bits
#define LMASK 0x7fffffffUL		//least significant r bits
#define MIXBITS(u,v) ( ((u) & UMASK) | ((v) & LMASK) )
#define TWIST(u,v) ((MIXBITS(u,v) >> 1) ^ (_uTable[v & 1UL] ))


///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	randomInit
// Description			:	Init the random number generator
// Return Value			:	-
// Comments				:
void			CShadingContext::randomInit(uint32_t s) {
    int j;
    state[0]= s & 0xffffffffUL;
    for (j=1; j<N; j++) {
        state[j] = (1812433253UL * (state[j-1] ^ (state[j-1] >> 30)) + j); 
        state[j] &= 0xffffffffUL;  /* for >32 bit machines */
    }
    next = state;
    return;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	randomShutdown
// Description			:	Shutdown the random number generator
// Return Value			:	-
// Comments				:
void			CShadingContext::randomShutdown() {
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	next_state
// Description			:	Get the next stage for the random number generator
// Return Value			:	-
// Comments				:
void			CShadingContext::next_state() {
    static const uint32_t _uTable[2] = { 0UL, MATRIX_A };
    register signed int j;
    
    register uint32_t *p0;
    register uint32_t *p1;

    j = ( N-M ) >> 1;
    p0 = state;
    p1 = p0 + 1;
    while(j) {
       --j;
        *p0 = TWIST( *p0, *p1 );
		*p0 ^= p0[M];
		++p1;
		++p0;

		*p0 = TWIST( *p0, *p1 );
		*p0 ^= p0[M];
		++p1; 
		++p0;
    }

    *p0 = TWIST( *p0, *p1);
    *p0 ^= p0[M];
    ++p1; 
    ++p0;

    j = (M-1) >> 1;
    while( j ) {
       --j;
       *p0 = TWIST( *p0, *p1 );
       *p0 ^= p0[M-N];
       ++p1;
       ++p0;

       *p0 = TWIST( *p0, *p1 );
       *p0 ^= p0[M-N];
       ++p1;
       ++p0;
    }
    *p0 = TWIST( *p0, *state );
    *p0 ^= p0[M-N];

    next = state + N;
    return;
}

