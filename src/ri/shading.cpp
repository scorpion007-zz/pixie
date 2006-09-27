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
//  File				:	shading.cpp
//  Classes				:	CShadingContext
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include	<stdarg.h>
#include	<math.h>
#include	<string.h>

#include	"renderer.h"
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
#include	"radiance.h"
#include	"error.h"
#include	"remoteChannel.h"

// George's extrapolated derivative extensions
#define		USE_EXTRAPOLATED_DERIV

// In case we need identity matrix
static		matrix	identity	=	{	1,	0,	0,	0,
										0,	1,	0,	0,
										0,	0,	1,	0,
										0,	0,	0,	1	};


// Options that are defined and responded
static	char	*optionsFormat				=	"Format";
static	char	*optionsDeviceFrame			=	"Frame";
static	char	*optionsDeviceResolution	=	"DeviceResolution";
static	char	*optionsFrameAspectRatio	=	"FrameAspectRatio";
static	char	*optionsCropWindow			=	"CropWindow";
static	char	*optionsDepthOfField		=	"DepthOfField";
static	char	*optionsShutter				=	"Shutter";
static	char	*optionsClipping			=	"Clipping";
static	char	*optionsBucketSize			=	"BucketSize";
static	char	*optionsColorQuantizer		=	"ColorQuantizer";
static	char	*optionsDepthQuantizer		=	"DepthQuantizer";
static	char	*optionsPixelFilter			=	"PixelFilter";
static	char	*optionsGamma				=	"Gamma";
static	char	*optionsMaxRayDepth			=	"MaxRayDepth";
static	char	*optionsRelativeDetail		=	"RelativeDetail";
static	char	*optionsPixelSamples		=	"PixelSamples";

// Attributes that are defined and responded
static	char	*attributesShadingRate		=	"ShadingRate";
static	char	*attributesSides			=	"Sides";
static	char	*attributesMatte			=	"matte";
static	char	*attributesMotionfactor		=	"GeometricApproximation:motionfactor";
static	char	*attributesDisplacementBnd	=	"displacementbound:sphere";
static	char	*attributesDisplacementSys	=	"displacementbound:coordinatesystem";
static	char	*attributesName				=	"identifier:name";

static	char	*attributesTraceBias		=	"trace:bias";
static	char	*attributesTraceMaxDiffuse	=	"trace:maxdiffusedepth";
static	char	*attributesTraceMaxSpecular	=	"trace:maxspeculardepth";

// Rendererinfo requests
static	char	*rendererinfoRenderer		=	"renderer";
static	char	*rendererinfoVersion		=	"version";
static	char	*rendererinfoVersionStr		=	"versionstring";

// Predefined ray labels used during raytracing
		char	*rayLabelPrimary			=	"camera";
		char	*rayLabelTrace				=	"trace";
		char	*rayLabelTransmission		=	"transmission";
		char	*rayLabelGather				=	"gather";


///////////////////////////////////////////////////////////////////////
// Function				:	complete
// Description			:	This function fills in the missing data (not filled by the object) from attributes
// Return Value			:
// Comments				:
// Date last edited		:	4/18/2002
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
				const	float	ctime	=	*time++;
				const	float	cu		=	*u++;
				const	float	cv		=	*v++;

				*s++			=	((s1[0]*(1-ctime) + s2[0]*ctime)*(1-cu) + 
									 (s1[1]*(1-ctime) + s2[1]*ctime)*cu)*(1-cv) + 
									((s1[2]*(1-ctime) + s2[2]*ctime)*(1-cu) + 
									 (s1[3]*(1-ctime) + s2[3]*ctime)*cu)*cv;
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
				const	float	ctime	=	*time++;
				const	float	cu		=	*u++;
				const	float	cv		=	*v++;

				*t++			=	((t1[0]*(1-ctime) + t2[0]*ctime)*(1-cu) + 
								     (t1[1]*(1-ctime) + t2[1]*ctime)*cu)*(1-cv) + 
									((t1[2]*(1-ctime) + t2[2]*ctime)*(1-cu) + 
									 (t1[3]*(1-ctime) + t2[3]*ctime)*cu)*cv;
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
}

///////////////////////////////////////////////////////////////////////
// Function				:	complete
// Description			:	This function fills in the missing data (not filled by the object) from attributes
// Return Value			:
// Comments				:
// Date last edited		:	4/18/2002
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
				*s++		=	(sCoord[0]*(1-(*u)) + sCoord[1]*(*u))*(1-(*v)) + (sCoord[2]*(1-(*u)) + sCoord[3]*(*u))*(*v);
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
				*t++		=	(tCoord[0]*(1-(*u)) + tCoord[1]*(*u))*(1-(*v)) + (tCoord[2]*(1-(*u)) + tCoord[3]*(*u))*(*v);
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
}



///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	CShadingContext
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	8/25/2002
CShadingContext::CShadingContext(COptions *o,CXform *x,SOCKET s,unsigned int hf) : COutput(o,x,s,hf) {

	// Initialize the extend of the world
	initv(worldBmin,C_INFINITY,C_INFINITY,C_INFINITY);
	initv(worldBmax,-C_INFINITY,-C_INFINITY,-C_INFINITY);

	// Initialize the shading state
	currentShadingState		=	NULL;

	// This is the memory we allocate our junk from
	frameMemory				=	new CMemStack(1 << 20);
	
	// Initialize the shader state memory stack
	memoryInit(shaderStateMemory);

	// This is the set of raytraced objects
	raytraced				=	new CArray<CSurface *>;

	// Init the loaded files
	loadedFiles				=	new CTrie<CFileResource *>;
	dirtyInstances			=	NULL;
	dirtyAttributes			=	NULL;

	conditionals			=	NULL;
	currentRayDepth			=	0;
	currentRayLabel			=	rayLabelPrimary;
	freeStates				=	NULL;
	inShadow				=	FALSE;
	
	raytracingFlags			=	ATTRIBUTES_FLAGS_PHOTON_VISIBLE			|
								ATTRIBUTES_FLAGS_TRACE_VISIBLE			|
								ATTRIBUTES_FLAGS_TRANSMISSION_VISIBLE;

	if (hiderFlags & HIDER_NEEDS_RAYTRACING) {
		raytracingFlags		|=	ATTRIBUTES_FLAGS_PRIMARY_VISIBLE;
	}

	globalVariables			=	NULL;
	numGlobalVariables		=	0;
	maxGlobalVariables		=	0;

	traceObjectHash			=	NULL;

	hierarchy				=	NULL;
	tracables				=	NULL;
	triangles				=	NULL;

	// Initialize remote channels
	remoteChannels			=	new CArray<CRemoteChannel*>;
	declaredRemoteChannels	=	new CTrie<CRemoteChannel*>;
	
	// Initialize the texturing
	CTexture::textureInit(maxTextureSize);	// Make sure we convert the size to bytes (from KB)
	CBrickMap::brickMapInit(maxBrickSize);
	randomInit();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	~CShadingContext
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	8/25/2002
CShadingContext::~CShadingContext() {
	CShadingState	*cState;
	
	// Print the stats (before we discard the memory)
	stats.frameTime		=	osCPUTime()		-	stats.frameStartTime;

	// Display the stats if applicable
	if (endofframe > 0) {
		stats.printStats(endofframe);
	}

	// Reset the dirty shader instances
	if (dirtyInstances != NULL) {
		int							numShaderInstances	=	dirtyInstances->numItems;
		CProgrammableShaderInstance	**instances			=	dirtyInstances->array;

		for (;numShaderInstances>0;numShaderInstances--) {
			CProgrammableShaderInstance	*dirtyInstance	=	*instances++;
			int							i;

			for (i=0;i<dirtyInstance->parent->numPLs;i++) {
				if (dirtyInstance->parameterLists[i] != NULL)	{
					delete dirtyInstance->parameterLists[i];
					dirtyInstance->parameterLists[i]	=	NULL;
				}
			}

			// The shader is no longer dirty
			dirtyInstance->dirty	=	FALSE;
			dirtyInstance->detach();
		}

		delete dirtyInstances;
	}

	// Ditch the remote channels
	for (int i=0;i<remoteChannels->numItems;i++) {
		if (remoteChannels->array[i] != NULL) delete remoteChannels->array[i];
	}
	delete remoteChannels;
	delete declaredRemoteChannels;

	// Ditch the loaded files
	assert(loadedFiles != NULL);
	loadedFiles->destroy();

	// Ditch the shading states that have been allocated
	assert(currentShadingState != NULL);
	freeState(currentShadingState);
	while ((cState=freeStates) != NULL) {
		freeStates	=	cState->next;

		freeState(cState);
	}
	currentShadingState	=	NULL;

	// Ditch the raytraced objects
	if (raytraced != NULL) {
		int			i;
		CSurface	**surfaces	=	raytraced->array;

		for (i=raytraced->numItems;i>0;i--) {
			(*surfaces++)->detach();
		}

		delete raytraced;
	}

	assert(tracables == NULL);

	// Ditch the triangle list if it's still around
	if (triangles != NULL) delete triangles;

	// Ditch the global variables
	if (globalVariables != NULL) {
		delete [] globalVariables;
	}

	// Ditch the raytracing hierarchy
	if (hierarchy != NULL) {
		delete hierarchy;
	}
	
	// Ditch the frame memory
	delete frameMemory;
	
	// Ditch the shader state memory stack
	memoryTini(shaderStateMemory);


	// Reset the dirty attributes
	if (dirtyAttributes != NULL) {
		int			numAttributes	=	dirtyAttributes->numItems;
		CAttributes	**dirty			=	dirtyAttributes->array;
		CAttributes	*cAttribute;

		for (;numAttributes>0;numAttributes--) {
			cAttribute				=	*dirty++;
			cAttribute->globalMap	=	NULL;
			cAttribute->causticMap	=	NULL;
			cAttribute->detach();
		}

		delete dirtyAttributes;
	}

	// Close the texturing system
	CBrickMap::brickMapShutdown();
	CTexture::textureShutdown();
	randomShutdown();
}





///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	render
// Description			:	Add an object into the scene
// Return Value			:
// Comments				:
// Date last edited		:	2/15/2003
void	CShadingContext::render(CObject *cObject) {
	vector		bmin,bmax;
	CAttributes	*cAttributes	=	cObject->attributes;

	// Assign the photon map is necessary
	if (cAttributes->globalMapName != NULL) {
		cAttributes->globalMap	=	getPhotonMap(cAttributes->globalMapName);
		cAttributes->globalMap->attach();
	}

	if (cAttributes->causticMapName != NULL) {
		cAttributes->causticMap	=	getPhotonMap(cAttributes->causticMapName);
		cAttributes->causticMap->attach();
	}

	if ((cAttributes->globalMap != NULL) || (cAttributes->causticMap != NULL)) {
		if (dirtyAttributes == NULL) dirtyAttributes	=	new CArray<CAttributes *>;

		cAttributes->attach();
		dirtyAttributes->push(cAttributes);
	}

	// Bound the object
	cObject->bound(bmin,bmax);

	// Update the world bounding box
	addBox(worldBmin,worldBmax,bmin);
	addBox(worldBmin,worldBmax,bmax);

	// Tesselate the object if applicable
	if (cObject->attributes->flags & raytracingFlags) {
		cObject->tesselate(this);
	}

	if (cObject->attributes->flags & ATTRIBUTES_FLAGS_PRIMARY_VISIBLE) {
		// Dispatch the object to the hider
		drawObject(cObject,bmin,bmax);
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	remove
// Description			:	Remove an object from the scene
// Return Value			:
// Comments				:
// Date last edited		:	2/15/2003
void	CShadingContext::addTracable(CTracable *tracable,CSurface *object) {
	object->attach();

	tracables->push(tracable);
	raytraced->push(object);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	remove
// Description			:	Remove an object from the scene
// Return Value			:
// Comments				:
// Date last edited		:	2/15/2003
void	CShadingContext::addTracable(CTriangle *tracable,CSurface *object) {
	object->attach();

	tracables->push(tracable);
	raytraced->push(object);

	if (triangles != NULL) triangles->push(tracable);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	remove
// Description			:	Remove an object from the scene
// Return Value			:
// Comments				:
// Date last edited		:	2/15/2003
void	CShadingContext::addTracable(CMovingTriangle *tracable,CSurface *object) {
	object->attach();

	tracables->push(tracable);
	raytraced->push(object);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	remove
// Description			:	Remove an object from the scene
// Return Value			:
// Comments				:
// Date last edited		:	2/15/2003
void	CShadingContext::remove(CTracable *cObject) {
	if (hierarchy != NULL) {
		vector	bmin,bmax;

		// Bound the object
		cObject->bound(bmin,bmax);

		hierarchy->remove(cObject,bmin,bmax);
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	renderPrimitive
// Description			:	Add an object into the scene
// Return Value			:
// Comments				:
// Date last edited		:	2/15/2003
void	CShadingContext::drawObject(CObject *cObject,const float *,const float *) {
	// This function must be overriden
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	retraceRay
// Description			:	Retrace a ray
// Return Value			:
// Comments				:
// Date last edited		:	11/9/2002
void	CShadingContext::retraceRay(CRay *cRay) {
	hierarchy->intersect(cRay);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	beginWorld
// Description			:	Start a world block
// Return Value			:
// Comments				:
// Date last edited		:	11/9/2002
void	CShadingContext::beginWorld() {
	assert(tracables == NULL);
	tracables	=	new CArray<CTracable *>;

	if (flags & OPTIONS_FLAGS_USE_RADIANCE_CACHE) {
		triangles	=	new CArray<CTriangle *>;
	}
	
	// Start a TSM channel if needed
	if ((netClient != INVALID_SOCKET) && (flags & OPTIONS_FLAGS_DEEP_SHADOW_RENDERING)) {
		requestRemoteChannel(new CRemoteTSMChannel(deepShadowFileName,deepShadowFile,deepShadowIndex,xBuckets,yBuckets));
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	endWorld
// Description			:	End a world block
// Return Value			:
// Comments				:
// Date last edited		:	11/9/2002
void	CShadingContext::endWorld() {
	if (hierarchy == NULL) {
		// Init the hierarchy
		hierarchy	=	new CHierarchy(tracables->numItems,tracables->array,worldBmin,worldBmax,this,frameMemory);
	} else {
		hierarchy->add(tracables->numItems,tracables->array);
	}

	delete tracables;
	tracables	=	NULL;
}



///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	shade2D
// Description			:	Sample/Shade bunch of points
// Return Value			:	-
// Comments				:
// Date last edited		:	8/30/2002
//
//
//
//	Preconditions:
//	!!!	->	u,v,time,I		fields of varying must be set
void	CShadingContext::shade(CSurface *object,int uVertices,int vVertices,int dim,unsigned int usedParameters) {
	CAttributes			*currentAttributes	=	object->attributes;
	float				**varying;
	CShaderInstance		*displacement;
	CShaderInstance		*surface;
	CShaderInstance		*atmosphere;
	int					i;
	int					numVertices;
	CSurface			*savedObject;
	T64					shaderVarCheckpoint[3];

	assert(uVertices > 0);
	assert(vVertices > 0);

	numVertices	=	uVertices*vVertices;

	stats.numSampled++;
	stats.numShaded							+=	numVertices;

	assert(numVertices <= maxGridSize);

	// Are we a shadow ray ?
	if (inShadow == TRUE) {

		// Yes, are we supposed to shade the objects in the shadow ?
		if (currentAttributes->transmission == 'o') {
			// No, just copy the color/opacity from the attributes field
			float			*opacity	=	currentShadingState->varying[VARIABLE_OI];
			int				i;

			for (i=numVertices;i>0;i--) {
				initv(opacity,1,1,1);
				opacity	+=	3;
			}

			return;
		} else if (currentAttributes->transmission == 'i') {
			// No, just copy the color/opacity from the attributes field
			float			*opacity	=	currentShadingState->varying[VARIABLE_OI];
			int				i;
			const	float	*so			=	currentAttributes->surfaceOpacity;


			for (i=numVertices;i>0;i--) {
				movvv(opacity,so);
				opacity	+=	3;
			}

			return;
		}
		// We need to execute the shaders
		displacement	=	NULL;	//currentAttributes->displacement;	// We probably don't need to execute the displacement shader
		surface			=	currentAttributes->surface;
		atmosphere		=	NULL;

	} else {
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

	if (currentAttributes->usedParameters == 0)	currentAttributes->checkParameters();

	usedParameters						|=	currentAttributes->usedParameters | additionalParameters;

	// Prepare the shading state
	varying								=	currentShadingState->varying;

	// We're shading
	savedObject							=	currentShadingState->currentObject;
	currentShadingState->currentObject	=	object;
	currentShadingState->numUvertices	=	uVertices;
	currentShadingState->numVvertices	=	vVertices;
	currentShadingState->numVertices	=	numVertices;

	// Checkpoint the shader state stack
	memSave(shaderVarCheckpoint,shaderStateMemory);
	
	// Allocate the caches for the shaders being executed
	if (surface != NULL)							currentShadingState->locals[ACCESSOR_SURFACE]		=	surface->prepare(shaderStateMemory,varying,numVertices);
	if (displacement != NULL)						currentShadingState->locals[ACCESSOR_DISPLACEMENT]	=	displacement->prepare(shaderStateMemory,varying,numVertices);
	if (atmosphere != NULL)							currentShadingState->locals[ACCESSOR_ATMOSPHERE]	=	atmosphere->prepare(shaderStateMemory,varying,numVertices);
	// We do not prepare interior or exterior as these are limited to passing default values (no outputs, they don't recieve pl variables)
	
	// If we need derivative information, treat differently
	if ((usedParameters & PARAMETER_DERIVATIVE) && (dim != 0)) {	// Notice: we can not differentiate a 0 dimentional point set
		if (dim == -1) {											// We're raytracing, so the derivative computation is different
			float				*P;									// Notice: we can not differentiate a 1 dimentional point set along this dimention
			float				*dPdu;
			float				*dPdv;
			int					numRealVertices;
			float				dud,dvd;
			float				*u,*v,*du,*dv,*time,*I;
			unsigned int		shadingParameters;
			int					j;

			numRealVertices							=	numVertices;
			numVertices								*=	3;	// For the extra derivative vertices
			currentShadingState->numVertices		=	numVertices;
			currentShadingState->numRealVertices	=	numRealVertices;
			currentShadingState->shadingDim			=	SHADING_2D;
			currentShadingState->numActive			=	numVertices;
			currentShadingState->numPassive			=	0;

			// Sample the object
			usedParameters							|=	PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_P;
			shadingParameters						=	usedParameters;
			object->sample(0,numRealVertices,varying,usedParameters);
			usedParameters							=	shadingParameters;		// Restore the required parameters for the second round of shading

			P				=	varying[VARIABLE_P];
			dPdu			=	varying[VARIABLE_DPDU];
			dPdv			=	varying[VARIABLE_DPDV];
			du				=	varying[VARIABLE_DU];
			dv				=	varying[VARIABLE_DV];
			u				=	varying[VARIABLE_U];
			v				=	varying[VARIABLE_V];
			time			=	varying[VARIABLE_TIME];
			I				=	varying[VARIABLE_I];

			// Compute the derivative evaluation u/v
			if (projection == OPTIONS_PROJECTION_PERSPECTIVE) {
				const float	d	=	dxdPixel / imagePlane;

				for (i=0,j=numRealVertices;i<numRealVertices;i++,P+=3,dPdu+=3,dPdv+=3) {
					float		ku,kv;
					const float	lengthu	=	dotvv(dPdu,dPdu);
					const float	lengthv	=	dotvv(dPdv,dPdv);
					const float	lengthi	=	dotvv(P,P);

					ku			=	dotvv(P,dPdu);	ku	=	isqrtf((lengthu*lengthi - (ku*ku)) / (lengthu*lengthi + C_EPSILON));
					kv			=	dotvv(P,dPdv);	kv	=	isqrtf((lengthv*lengthi - (kv*kv)) / (lengthv*lengthi + C_EPSILON));

					dud			=	ku * d * isqrtf(lengthu/(lengthi+C_EPSILON)) + C_EPSILON;
					dvd			=	kv * d * isqrtf(lengthv/(lengthi+C_EPSILON)) + C_EPSILON;

					u[j]		=	u[i] + dud;
					v[j]		=	v[i];
					time[j]		=	time[i];
					movvv(I + j*3,I + i*3);
					du[i]		=	dud;
					du[j]		=	dud;
					dv[j]		=	dvd;
					j++;

					u[j]		=	u[i];
					v[j]		=	v[i] + dvd;
					time[j]		=	time[i];
					movvv(I + j*3,I + i*3);
					dv[i]		=	dvd;
					du[j]		=	dud;
					dv[j]		=	dvd;
					j++;
				}
			} else {
				const float	d	=	dxdPixel;

				for (i=0,j=numRealVertices;i<numRealVertices;i++,P+=3,dPdu+=3,dPdv+=3) {
					float		ku,kv;
					const float	lengthu	=	dotvv(dPdu,dPdu);
					const float	lengthv	=	dotvv(dPdv,dPdv);

					ku			=	isqrtf((lengthu - (dPdu[COMP_Z]*dPdu[COMP_Z])) / (lengthu + C_EPSILON));
					kv			=	isqrtf((lengthv - (dPdv[COMP_Z]*dPdv[COMP_Z])) / (lengthv + C_EPSILON));

					dud			=	ku * d * isqrtf(lengthu) + C_EPSILON;
					dvd			=	kv * d * isqrtf(lengthv) + C_EPSILON;

					u[j]		=	u[i] + dud;
					v[j]		=	v[i];
					time[j]		=	time[i];
					movvv(I + j*3,I + i*3);
					du[i]		=	dud;
					du[j]		=	dud;
					dv[j]		=	dvd;
					j++;

					u[j]		=	u[i];
					v[j]		=	v[i] + dvd;
					time[j]		=	time[i];
					movvv(I + j*3,I + i*3);
					dv[i]		=	dvd;
					du[j]		=	dud;
					dv[j]		=	dvd;
					j++;
				}
			}

			object->sample(numRealVertices,2*numRealVertices,varying,usedParameters);
		} else {
			// We're shading a regular grid, so take the shortcut while computing the surface derivatives
			float			*P;
			float			*du;
			float			*dv;
			float			*u,*v;
			float			*xy;
			int				i,j;
			const float		shadingRate				=	currentAttributes->shadingRate;
			float			*sru,*srv;

			currentShadingState->numRealVertices	=	numVertices;
			currentShadingState->shadingDim			=	(dim == 2 ? SHADING_2D_GRID : SHADING_1D_GRID);
			currentShadingState->numActive			=	numVertices;
			currentShadingState->numPassive			=	0;

			// First sample the object at the grid vertices
			usedParameters	|=	PARAMETER_P;

			// Sample the object
			object->sample(0,numVertices,varying,usedParameters);

			// We're rasterizing, so the derivative information is already available
			memBegin();

			xy					=	(float *) ralloc(numVertices*2*sizeof(float));

			P					=	varying[VARIABLE_P];
			du					=	varying[VARIABLE_DU];
			dv					=	varying[VARIABLE_DV];
			u					=	varying[VARIABLE_U];
			v					=	varying[VARIABLE_V];
			sru					=	varying[VARIABLE_SRU];
			srv					=	varying[VARIABLE_SRV];

			// Project the grid vertices first
			// PS: The offset is not important, so do not compute it
			if (projection == OPTIONS_PROJECTION_PERSPECTIVE) {
				float	*cXy	=	xy;

				for (i=numVertices;i>0;i--) {
					cXy[0]		=	(P[COMP_X] * imagePlane / P[COMP_Z])*dPixeldx;
					cXy[1]		=	(P[COMP_Y] * imagePlane / P[COMP_Z])*dPixeldy;
					cXy			+=	2;
					P			+=	3;
				}
			} else {
				float	*cXy	=	xy;

				for (i=numVertices;i>0;i--) {
					cXy[0]		=	P[COMP_X]*dPixeldx;
					cXy[1]		=	P[COMP_Y]*dPixeldy;
					cXy			+=	2;
					P			+=	3;
				}
			}

			// Compute the du
			for (i=0;i<vVertices;i++) {
				int		tmp		=	i*uVertices;
				float	*cDU	=	du	+ tmp;
				float	*cU		=	u	+ tmp;
				float	*cSr	=	sru	+ tmp;
				float	*cXy	=	xy	+ tmp*2;
				float	dx,dy,d;

				P				=	varying[VARIABLE_P]		+	tmp*3;
				for (j=uVertices-1;j>0;j--) {
					dx		=	cXy[2] - cXy[0];
					dy		=	cXy[3] - cXy[1];
					cSr[0]	=	shadingRate*isqrtf(dx*dx + dy*dy);
					d		=	cSr[0]*(cU[1] - cU[0]);
					d		=	min(d,1);
					assert(d > 0);
					assert(d <= 1);
					cDU[0]	=	d;
					cDU		+=	1;
					cU		+=	1;
					cSr		+=	1;
					cXy		+=	2;
					P		+=	3;
				}

#ifdef USE_EXTRAPOLATED_DERIV
				if (uVertices > 3) {
					const float A =	(cDU[-3] - cDU[-2])/((cU[-3]-cU[-2])*(cU[-3]-cU[-1])) -
									(cDU[-1] - cDU[-2])/((cU[-1]-cU[-2])*(cU[-3]-cU[-1]));
					const float B =	(cDU[-1] - cDU[-2] + A*(cU[-2]*cU[-2] - cU[-1]*cU[-1])) /
									(cU[-1] - cU[-2]);
					const float C = (cDU[-1] - A*cU[-1]*cU[-1] - B*cU[-1]);

					d		= A*cU[0]*cU[0] + B*cU[0] + C;
				}
#endif
				
				cSr[0]		=	cSr[-1];
				cDU[0]		=	d;
			}

			// Compute the dv,dPdv
			for (i=0;i<uVertices;i++) {
				float	*cDV	=	dv	+	i;
				float	*cV		=	v	+	i;
				float	*cSr	=	srv	+	i;
				float	*cXy	=	xy	+	i*2;
				float	dx,dy,d;

				P				=	varying[VARIABLE_P]		+	i*3;
				for (j=0;j<vVertices-1;j++) {
					dx		=	cXy[uVertices*2]	- cXy[0];
					dy		=	cXy[uVertices*2+1]	- cXy[1];
					cSr[0]	=	shadingRate*isqrtf(dx*dx + dy*dy);
					d		=	cSr[0]*(cV[uVertices] - cV[0]);
					d		=	min(d,1);
					assert(d > 0);
					assert(d <= 1);
					cDV[0]	=	d;
					cDV		+=	uVertices;
					cV		+=	uVertices;
					cSr		+=	uVertices;
					cXy		+=	uVertices*2;
					P		+=	uVertices*3;
				}
				
#ifdef USE_EXTRAPOLATED_DERIV
				if (vVertices > 3) {
					const float A =	(cDV[-uVertices*3] - cDV[-uVertices*2])/((cV[-uVertices*3]-cV[-uVertices*2])*(cV[-uVertices*3]-cV[-uVertices*1])) -
									(cDV[-uVertices*1] - cDV[-uVertices*2])/((cV[-uVertices*1]-cV[-uVertices*2])*(cV[-uVertices*3]-cV[-uVertices*1]));
					const float B =	(cDV[-uVertices*1] - cDV[-uVertices*2] + A*(cV[-uVertices*2]*cV[-uVertices*2] - cV[-uVertices*1]*cV[-uVertices*1])) /
									(cV[-uVertices*1] - cV[-uVertices*2]);
					const float C = (cDV[-uVertices*1] - A*cV[-uVertices*1]*cV[-uVertices*1] - B*cV[-uVertices*1]);
					
					d		= A*cV[0]*cV[0] + B*cV[0] + C;
				}
#endif
				
				cSr[0]		=	cSr[-uVertices];
				cDV[0]		=	d;
			}

			// Done and done
			memEnd();
		}
	} else {
		// No derivative information is needed
		currentShadingState->shadingDim			=	SHADING_0D;
		currentShadingState->numRealVertices	=	numVertices;
		currentShadingState->numActive			=	numVertices;
		currentShadingState->numPassive			=	0;

		// Sample the object
		object->sample(0,numVertices,varying,usedParameters);
	}


	// Compute the "I"
	if (currentRayDepth == 0) {
		float			*I				=	varying[VARIABLE_I];

		if (projection == OPTIONS_PROJECTION_PERSPECTIVE) {
			memcpy(I,varying[VARIABLE_P],numVertices*3*sizeof(float));
		} else {
			for (i=numVertices;i>0;i--) {
				initv(I,0,0,1);
				I	+=	3;
			}
		}
	} else {
		float			*I				=	varying[VARIABLE_I];
		const float		*P				=	varying[VARIABLE_P];

		for (i=numVertices;i>0;i--) {
			I[0]	=	P[0] - I[0];
			I[1]	=	P[1] - I[1];
			I[2]	=	P[2] - I[2];
			I		+=	3;
			P		+=	3;
		}
	}

	{
		CShadedLight	**lights					=	&currentShadingState->lights;
		CShadedLight	**alights					=	&currentShadingState->alights;
		CShadedLight	**currentLight				=	&currentShadingState->currentLight;
		CShadedLight	**freeLights				=	&currentShadingState->freeLights;
		int				*tags						=	currentShadingState->tags;

		currentShadingState->lightsExecuted			=	FALSE;
		currentShadingState->ambientLightsExecuted	=	FALSE;
		currentShadingState->lightCategory			=	0;

		// Clear out previous lights etc
		*lights			=	NULL;
		*currentLight	=	NULL;
		*freeLights		=	NULL;
		*alights		=	NULL;
		for (i=0;i<numVertices;i++) {
			tags[i]		=	0;
		}

		object->interpolate(numVertices,varying);

		if (currentAttributes->next != NULL) {
			complete(numVertices,varying,usedParameters,currentAttributes,currentAttributes->next);
		} else {
			complete(numVertices,varying,usedParameters,currentAttributes);
		}

		memBegin();

		if (displacement != NULL) {
			displacement->execute(this,currentShadingState->locals[ACCESSOR_DISPLACEMENT]);
		}

		if (surface != NULL) {
			surface->execute(this,currentShadingState->locals[ACCESSOR_SURFACE]);
		} else {
			float			*color		=	varying[VARIABLE_CI];
			float			*opacity	=	varying[VARIABLE_OI];
			float			*normal		=	varying[VARIABLE_N];
			float			*point		=	varying[VARIABLE_P];
			const float		*Cs			=	currentAttributes->surfaceColor;
			const float		*Os			=	currentAttributes->surfaceOpacity;

			for (i=numVertices;i>0;i--) {
				normalizevf(normal);
				normalizevf(point);
				mulvf(color,Cs,absf(dotvv(point,normal)));
				movvv(opacity,Os);
				color	+=	3;
				opacity	+=	3;
				normal	+=	3;
				point	+=	3;
			}
		}

		if (currentRayDepth == 0) {  // do not execute atmosphere for non-camera rays
			if (atmosphere != NULL) {
				atmosphere->execute(this,currentShadingState->locals[ACCESSOR_ATMOSPHERE]);
			}
		}

		if (currentShadingState->postShader != NULL) {
			currentShadingState->locals[ACCESSOR_POSTSHADER]	=	currentShadingState->postShader->prepare(shaderStateMemory,varying,numVertices);
			currentShadingState->postShader->execute(this,currentShadingState->locals[ACCESSOR_POSTSHADER]);
		}

		memEnd();
	}
	
	// Unwind the stack of shader states
	memRestore(shaderVarCheckpoint,shaderStateMemory);

	currentShadingState->currentObject	=	savedObject;
}





///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	displace
// Description			:	Sample/Shade bunch of points
// Return Value			:	-
// Comments				:
// Date last edited		:	8/30/2002
//
//
//
//	Preconditions:
//	!!!	->	u,v,time,I		fields of varying must be set
void	CShadingContext::displace(CSurface *object,int uVertices,int vVertices,int dim,unsigned int usedParameters) {
	CAttributes			*currentAttributes	=	object->attributes;
	float				**varying;
	CShaderInstance		*displacement;
	CShaderInstance		*surface;
	CShaderInstance		*atmosphere;
	int					i;
	int					numVertices;
	CSurface			*savedObject;
	T64					shaderVarCheckpoint[3];

	assert(uVertices > 0);
	assert(vVertices > 0);

	numVertices	=	uVertices*vVertices;

	stats.numSampled++;
	stats.numShaded							+=	numVertices;

	assert(numVertices <= maxGridSize);

	// Yes, is there a displacement shader on the surface ?
	if (	(currentAttributes->displacement == NULL) || 
			(	(usedParameters & PARAMETER_RAYTRACE) && (!(currentAttributes->flags & ATTRIBUTES_FLAGS_DISPLACEMENTS)))) {
		const int	savedParameters	=	usedParameters;

		// No, just sample the geometry
		object->sample(0,numVertices,currentShadingState->varying,usedParameters);
		object->interpolate(numVertices,currentShadingState->varying);

		// We're not shading just sampling
		if (usedParameters & PARAMETER_N) {
			assert(savedParameters & PARAMETER_NG);

			varying								=	currentShadingState->varying;

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

	// We need to execute the displacement shader, so get ready
	displacement	=	currentAttributes->displacement;
	surface			=	NULL;
	atmosphere		=	NULL;

	if (currentAttributes->usedParameters == 0)	currentAttributes->checkParameters();

	usedParameters						|=	currentAttributes->usedParameters | additionalParameters;

	// Prepare the shading state
	varying								=	currentShadingState->varying;

	// We're shading
	savedObject							=	currentShadingState->currentObject;
	currentShadingState->currentObject	=	object;
	currentShadingState->numUvertices	=	uVertices;
	currentShadingState->numVvertices	=	vVertices;
	currentShadingState->numVertices	=	numVertices;

	// Checkpoint the shader state stack
	memSave(shaderVarCheckpoint,shaderStateMemory);

	// Set the parameters of the displacement shader
	if (displacement != NULL)	currentShadingState->locals[ACCESSOR_DISPLACEMENT]	=	displacement->prepare(shaderStateMemory,varying,numVertices);
	
	if (usedParameters & PARAMETER_MESSAGEPASSING) {
		// Iff. we require message passing in the displacement shader, set up the caches
		if (surface != NULL)	currentShadingState->locals[ACCESSOR_SURFACE]		=	surface->prepare(shaderStateMemory,varying,numVertices);
		if (atmosphere != NULL)	currentShadingState->locals[ACCESSOR_ATMOSPHERE]	=	atmosphere->prepare(shaderStateMemory,varying,numVertices);
		// We do not prepare interior or exterior as these are limited to passing default values (no outputs, they don't recieve pl variables)
	}

	// If we need derivative information, treat differently
	if ((usedParameters & PARAMETER_DERIVATIVE) && (dim != 0)) {	// Notice: we can not differentiate a 0 dimentional point set
		if (dim == -1) {											// We're raytracing, so the derivative computation is different
			float				*P;									// Notice: we can not differentiate a 1 dimentional point set along this dimention
			float				*dPdu;
			float				*dPdv;
			int					numRealVertices;
			float				dud,dvd;
			float				*u,*v,*du,*dv,*time,*I;
			unsigned int		shadingParameters;
			int					j;

			numRealVertices							=	numVertices;
			numVertices								*=	3;	// For the extra derivative vertices
			currentShadingState->numVertices		=	numVertices;
			currentShadingState->numRealVertices	=	numRealVertices;
			currentShadingState->shadingDim			=	SHADING_2D;
			currentShadingState->numActive			=	numVertices;
			currentShadingState->numPassive			=	0;

			// Sample the object
			usedParameters							|=	PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_P;
			shadingParameters						=	usedParameters;
			object->sample(0,numRealVertices,varying,usedParameters);
			usedParameters							=	shadingParameters;		// Restore the required parameters for the second round of shading

			P				=	varying[VARIABLE_P];
			dPdu			=	varying[VARIABLE_DPDU];
			dPdv			=	varying[VARIABLE_DPDV];
			du				=	varying[VARIABLE_DU];
			dv				=	varying[VARIABLE_DV];
			u				=	varying[VARIABLE_U];
			v				=	varying[VARIABLE_V];
			time			=	varying[VARIABLE_TIME];
			I				=	varying[VARIABLE_I];

			// Compute the derivative evaluation u/v
			if (projection == OPTIONS_PROJECTION_PERSPECTIVE) {
				const float	d	=	dxdPixel / imagePlane;

				for (i=0,j=numRealVertices;i<numRealVertices;i++,P+=3,dPdu+=3,dPdv+=3) {
					float		ku,kv;
					const float	lengthu	=	dotvv(dPdu,dPdu);
					const float	lengthv	=	dotvv(dPdv,dPdv);
					const float	lengthi	=	dotvv(P,P);

					ku			=	dotvv(P,dPdu);	ku	=	isqrtf((lengthu*lengthi - (ku*ku)) / (lengthu*lengthi + C_EPSILON));
					kv			=	dotvv(P,dPdv);	kv	=	isqrtf((lengthv*lengthi - (kv*kv)) / (lengthv*lengthi + C_EPSILON));

					dud			=	ku * d * isqrtf(lengthu/(lengthi+C_EPSILON)) + C_EPSILON;
					dvd			=	kv * d * isqrtf(lengthv/(lengthi+C_EPSILON)) + C_EPSILON;

					u[j]		=	u[i] + dud;
					v[j]		=	v[i];
					time[j]		=	time[i];
					movvv(I + j*3,I + i*3);
					du[i]		=	dud;
					du[j]		=	dud;
					dv[j]		=	dvd;
					j++;

					u[j]		=	u[i];
					v[j]		=	v[i] + dvd;
					time[j]		=	time[i];
					movvv(I + j*3,I + i*3);
					dv[i]		=	dvd;
					du[j]		=	dud;
					dv[j]		=	dvd;
					j++;
				}
			} else {
				const float	d	=	dxdPixel;

				for (i=0,j=numRealVertices;i<numRealVertices;i++,P+=3,dPdu+=3,dPdv+=3) {
					float		ku,kv;
					const float	lengthu	=	dotvv(dPdu,dPdu);
					const float	lengthv	=	dotvv(dPdv,dPdv);

					ku			=	isqrtf((lengthu - (dPdu[COMP_Z]*dPdu[COMP_Z])) / (lengthu + C_EPSILON));
					kv			=	isqrtf((lengthv - (dPdv[COMP_Z]*dPdv[COMP_Z])) / (lengthv + C_EPSILON));

					dud			=	ku * d * isqrtf(lengthu) + C_EPSILON;
					dvd			=	kv * d * isqrtf(lengthv) + C_EPSILON;

					u[j]		=	u[i] + dud;
					v[j]		=	v[i];
					time[j]		=	time[i];
					movvv(I + j*3,I + i*3);
					du[i]		=	dud;
					du[j]		=	dud;
					dv[j]		=	dvd;
					j++;

					u[j]		=	u[i];
					v[j]		=	v[i] + dvd;
					time[j]		=	time[i];
					movvv(I + j*3,I + i*3);
					dv[i]		=	dvd;
					du[j]		=	dud;
					dv[j]		=	dvd;
					j++;
				}
			}

			object->sample(numRealVertices,2*numRealVertices,varying,usedParameters);
		} else {
			// We're shading a regular grid, so take the shortcut while computing the surface derivatives
			float			*P;
			float			*dPdu,*dPdv;
			float			*du;
			float			*dv;
			float			*u,*v;
			float			*xy;
			int				i,j;
			const float		shadingRate				=	currentAttributes->shadingRate;
			float			*sru,*srv;

			currentShadingState->numRealVertices	=	numVertices;
			currentShadingState->shadingDim			=	(dim == 2 ? SHADING_2D_GRID : SHADING_1D_GRID);
			currentShadingState->numActive			=	numVertices;
			currentShadingState->numPassive			=	0;

			// First sample the object at the grid vertices
			usedParameters	|=	PARAMETER_P;
			usedParameters	&=	~(PARAMETER_DPDU | PARAMETER_DPDV);

			// Sample the object
			object->sample(0,numVertices,varying,usedParameters);

			// We're rasterizing, so the derivative information is already available
			memBegin();

			xy					=	(float *) ralloc(numVertices*2*sizeof(float));

			P					=	varying[VARIABLE_P];
			du					=	varying[VARIABLE_DU];
			dv					=	varying[VARIABLE_DV];
			u					=	varying[VARIABLE_U];
			v					=	varying[VARIABLE_V];
			sru					=	varying[VARIABLE_SRU];
			srv					=	varying[VARIABLE_SRV];

			// Project the grid vertices first
			// PS: The offset is not important, so do not compute it
			if (projection == OPTIONS_PROJECTION_PERSPECTIVE) {
				float	*cXy	=	xy;

				for (i=numVertices;i>0;i--) {
					cXy[0]		=	(P[COMP_X] * imagePlane / P[COMP_Z])*dPixeldx;
					cXy[1]		=	(P[COMP_Y] * imagePlane / P[COMP_Z])*dPixeldy;
					cXy			+=	2;
					P			+=	3;
				}
			} else {
				float	*cXy	=	xy;

				for (i=numVertices;i>0;i--) {
					cXy[0]		=	P[COMP_X]*dPixeldx;
					cXy[1]		=	P[COMP_Y]*dPixeldy;
					cXy			+=	2;
					P			+=	3;
				}
			}

			// Compute the du,dPdu
			for (i=0;i<vVertices;i++) {
				int		tmp		=	i*uVertices;
				float	*cDU	=	du	+ tmp;
				float	*cU		=	u	+ tmp;
				float	*cSr	=	sru	+ tmp;
				float	*cXy	=	xy	+ tmp*2;
				float	dx,dy,d;

				dPdu			=	varying[VARIABLE_DPDU]	+	tmp*3;
				P				=	varying[VARIABLE_P]		+	tmp*3;
				for (j=uVertices-1;j>0;j--) {
					dx		=	cXy[2] - cXy[0];
					dy		=	cXy[3] - cXy[1];
					cSr[0]	=	shadingRate*isqrtf(dx*dx + dy*dy);
					d		=	cSr[0]*(cU[1] - cU[0]);
					d		=	min(d,1);
					assert(d > 0);
					assert(d <= 1);
					cDU[0]	=	d;
					dPdu[0]	=	P[3] - P[0];
					dPdu[1]	=	P[4] - P[1];
					dPdu[2]	=	P[5] - P[2];
					mulvf(dPdu,1 / (cU[1] - cU[0]));
					cDU		+=	1;
					cU		+=	1;
					cSr		+=	1;
					cXy		+=	2;
					dPdu	+=	3;
					P		+=	3;
				}
				
#ifdef USE_EXTRAPOLATED_DERIV
				if (uVertices > 3) {
					const float A =	(cDU[-3] - cDU[-2])/((cU[-3]-cU[-2])*(cU[-3]-cU[-1])) -
									(cDU[-1] - cDU[-2])/((cU[-1]-cU[-2])*(cU[-3]-cU[-1]));
					const float B =	(cDU[-1] - cDU[-2] + A*(cU[-2]*cU[-2] - cU[-1]*cU[-1])) /
									(cU[-1] - cU[-2]);
					const float C = (cDU[-1] - A*cU[-1]*cU[-1] - B*cU[-1]);
					
					d		= A*cU[0]*cU[0] + B*cU[0] + C;
				}
#endif
				
				cSr[0]		=	cSr[-1];
				cDU[0]		=	d;
				dPdu[0]		=	dPdu[-3];
				dPdu[1]		=	dPdu[-2];
				dPdu[2]		=	dPdu[-1];
			}

			// Compute the dv,dPdv
			for (i=0;i<uVertices;i++) {
				float	*cDV	=	dv	+	i;
				float	*cV		=	v	+	i;
				float	*cSr	=	srv	+	i;
				float	*cXy	=	xy	+	i*2;
				float	dx,dy,d;

				dPdv			=	varying[VARIABLE_DPDV]	+	i*3;
				P				=	varying[VARIABLE_P]		+	i*3;
				for (j=0;j<vVertices-1;j++) {
					dx		=	cXy[uVertices*2]	- cXy[0];
					dy		=	cXy[uVertices*2+1]	- cXy[1];
					cSr[0]	=	shadingRate*isqrtf(dx*dx + dy*dy);
					d		=	cSr[0]*(cV[uVertices] - cV[0]);
					d		=	min(d,1);
					assert(d > 0);
					assert(d <= 1);
					cDV[0]	=	d;
					dPdv[0]	=	P[uVertices*3+0] - P[0];
					dPdv[1]	=	P[uVertices*3+1] - P[1];
					dPdv[2]	=	P[uVertices*3+2] - P[2];
					mulvf(dPdv,1 / (cV[uVertices] - cV[0]));
					cDV		+=	uVertices;
					cV		+=	uVertices;
					cSr		+=	uVertices;
					cXy		+=	uVertices*2;
					dPdv	+=	uVertices*3;
					P		+=	uVertices*3;
				}
				
#ifdef USE_EXTRAPOLATED_DERIV
				if (vVertices > 3) {
					const float A =	(cDV[-uVertices*3] - cDV[-uVertices*2])/((cV[-uVertices*3]-cV[-uVertices*2])*(cV[-uVertices*3]-cV[-uVertices*1])) -
									(cDV[-uVertices*1] - cDV[-uVertices*2])/((cV[-uVertices*1]-cV[-uVertices*2])*(cV[-uVertices*3]-cV[-uVertices*1]));
					const float B =	(cDV[-uVertices*1] - cDV[-uVertices*2] + A*(cV[-uVertices*2]*cV[-uVertices*2] - cV[-uVertices*1]*cV[-uVertices*1])) /
									(cV[-uVertices*1] - cV[-uVertices*2]);
					const float C = (cDV[-uVertices*1] - A*cV[-uVertices*1]*cV[-uVertices*1] - B*cV[-uVertices*1]);
					
					d		= A*cV[0]*cV[0] + B*cV[0] + C;
				}
#endif
				
				cSr[0]		=	cSr[-uVertices];
				cDV[0]		=	d;
				dPdv[0]		=	dPdv[-uVertices*3+0];
				dPdv[1]		=	dPdv[-uVertices*3+1];
				dPdv[2]		=	dPdv[-uVertices*3+2];
			}

			// Done and done
			memEnd();
		}
	} else {
		// No derivative information is needed
		currentShadingState->shadingDim			=	SHADING_0D;
		currentShadingState->numRealVertices	=	numVertices;
		currentShadingState->numActive			=	numVertices;
		currentShadingState->numPassive			=	0;

		// Sample the object
		object->sample(0,numVertices,varying,usedParameters);
	}


	if (currentRayDepth == 0) {
		float			*I				=	varying[VARIABLE_I];

		if (projection == OPTIONS_PROJECTION_PERSPECTIVE) {
			memcpy(I,varying[VARIABLE_P],numVertices*3*sizeof(float));
		} else {
			for (i=numVertices;i>0;i--) {
				initv(I,0,0,1);
				I	+=	3;
			}
		}
	} else {
		float			*I				=	varying[VARIABLE_I];
		const float		*P				=	varying[VARIABLE_P];

		for (i=numVertices;i>0;i--) {
			I[0]	=	P[0] - I[0];
			I[1]	=	P[1] - I[1];
			I[2]	=	P[2] - I[2];
			I		+=	3;
			P		+=	3;
		}
	}

	{
		int				*tags				=	currentShadingState->tags;

		for (i=0;i<numVertices;i++) {
			tags[i]						=	0;
		}

		object->interpolate(numVertices,varying);

		if (currentAttributes->next != NULL) {
			complete(numVertices,varying,usedParameters,currentAttributes,currentAttributes->next);
		} else {
			complete(numVertices,varying,usedParameters,currentAttributes);
		}

		memBegin();

		if (displacement != NULL) {
			displacement->execute(this,currentShadingState->locals[ACCESSOR_DISPLACEMENT]);
		}

		memEnd();
	}
	
	// Unwind the stack of shader states
	memRestore(shaderVarCheckpoint,shaderStateMemory);

	currentShadingState->currentObject	=	savedObject;
}








///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	newState
// Description			:	Allocate a new shading state
// Return Value			:	-
// Comments				:
// Date last edited		:	8/25/2002
CShadingState	*CShadingContext::newState() {
	if (freeStates == NULL) {
		CShadingState	*newState		=	new CShadingState;
		int				j;
		float			*E;

		newState->varying				=	new float*[maxGlobalVariables];				stats.vertexMemory	+=	maxGlobalVariables*sizeof(float *);
		newState->tags					=	new int[maxGridSize*3];						stats.vertexMemory	+=	maxGridSize*3*sizeof(int);
		newState->lightingTags			=	new int[maxGridSize*3];						stats.vertexMemory	+=	maxGridSize*3*sizeof(int);
		newState->Ns					=	new float[maxGridSize*9];					stats.vertexMemory	+=	maxGridSize*3*sizeof(float);
		newState->alights				=	NULL;
		newState->freeLights			=	NULL;
		newState->postShader			=	NULL;
		newState->currentObject			=	NULL;

		for (j=0;j<maxGlobalVariables;j++) {
			newState->varying[j]	=	NULL;
		}

		for (j=0;j<numGlobalVariables;j++) {
			const	CVariable	*var	=	globalVariables[j];

			assert(var != NULL);

			if (	(var->container == CONTAINER_UNIFORM) || (var->container == CONTAINER_CONSTANT)	) {
				newState->varying[j]	=	new float[var->numFloats];
				stats.vertexMemory		+=	var->numFloats*sizeof(float);
			} else {
				newState->varying[j]	=	new float[var->numFloats*maxGridSize*3];
				stats.vertexMemory		+=	var->numFloats*maxGridSize*3*sizeof(float);
			}
		}

		// E is always (0,0,0)
		E	=	newState->varying[VARIABLE_E];
		for (j=maxGridSize*3;j>0;j--) {
			initv(E,0,0,0);
			E	+=	3;
		}

		if (stats.vertexMemory > stats.peakVertexMemory)	stats.peakVertexMemory=	stats.vertexMemory;

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
// Date last edited		:	8/25/2002
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
// Date last edited		:	8/25/2002
void			CShadingContext::freeState(CShadingState *cState) {
	int	j;

	for (j=0;j<numGlobalVariables;j++) {
		if (globalVariables[j] != NULL) {
			const CVariable	*var	=	globalVariables[j];

			if (	(var->container == CONTAINER_UNIFORM) || (var->container == CONTAINER_CONSTANT)	) {
				delete [] cState->varying[j];
				stats.vertexMemory		-=	var->numFloats*sizeof(float);
			} else {
				delete [] cState->varying[j];
				stats.vertexMemory		-=	var->numFloats*maxGridSize*3*sizeof(float);
			}
		}
	}

	delete [] cState->varying;					stats.vertexMemory	-=	maxGlobalVariables*sizeof(float *);
	delete [] cState->tags;						stats.vertexMemory	-=	maxGridSize*3*sizeof(int);
	delete [] cState->lightingTags;				stats.vertexMemory	-=	maxGridSize*3*sizeof(int);
	delete [] cState->Ns;						stats.vertexMemory	-=	maxGridSize*9*sizeof(float);
	
	delete cState;
}






///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	variableUpdate
// Description			:	This function is called to signal that there has been
//							a modification on the set of active variables
// Return Value			:	-
// Comments				:
// Date last edited		:	8/25/2002
void		CShadingContext::initState(CVariable *var,int numGlobal) {
	numGlobalVariables	=	numGlobal;
	maxGlobalVariables	=	numGlobal + 50;
	globalVariables		=	new CVariable*[maxGlobalVariables];

	for (;var!=NULL;var=var->next) {
		if (var->storage == STORAGE_GLOBAL) {
			assert(var->entry <= numGlobal);
			globalVariables[var->entry]		=	var;
		}
	}

	assert(freeStates == NULL);
	assert(currentShadingState == NULL);

	currentShadingState	=	newState();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	variableUpdate
// Description			:	This function is called to signal that there has been
//							a modification on the set of active variables
// Return Value			:	-
// Comments				:
// Date last edited		:	8/25/2002
void		CShadingContext::updateState(CVariable *var) {
	CShadingState	*cState;

	assert(var->storage == STORAGE_GLOBAL);
	assert(var->entry == numGlobalVariables);

	// Ditch the shading states that have been allocated
	while ((cState=freeStates) != NULL) {
		freeStates	=	cState->next;
		freeState(cState);
	}

	if (numGlobalVariables == maxGlobalVariables) {
		CVariable	**nvariables;

		freeState(currentShadingState);
		currentShadingState	=	NULL;

		nvariables			=	new CVariable*[maxGlobalVariables + 50];
		memcpy(nvariables,globalVariables,numGlobalVariables*sizeof(CVariable *));
		delete [] globalVariables;
		globalVariables		=	nvariables;
		maxGlobalVariables	+=	50;
	}

	globalVariables[numGlobalVariables++]	=	var;

	if (currentShadingState == NULL)	currentShadingState	=	newState();
	else {
		if (	(var->container == CONTAINER_UNIFORM) || (var->container == CONTAINER_CONSTANT)	) {
			currentShadingState->varying[var->entry]	=	new float[var->numFloats];
			stats.vertexMemory							+=	var->numFloats*sizeof(float);
		} else {
			currentShadingState->varying[var->entry]	=	new float[var->numFloats*maxGridSize*3];
			stats.vertexMemory							+=	var->numFloats*maxGridSize*3*sizeof(float);
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	getTexture
// Description			:	Load a texture from file
// Return Value			:
// Comments				:
// Date last edited		:	8/25/2002
CTexture	*CShadingContext::getTexture(const char *name) {
	CFileResource	*tex;

	if (loadedFiles->find(name,tex) == FALSE){
		// Load the texture
		tex	=	currentRenderer->textureLoad(name,texturePath);

		if (tex == NULL)	{
			// Not found, substitude with a dummy one
			error(CODE_NOFILE,"Unable open texture \"%s\"\n",name);
			tex					=	new CTexture(name,128,128,TEXTURE_PERIODIC,TEXTURE_PERIODIC);
		}

		loadedFiles->insert(tex->name,tex);
	}

	return (CTexture *) tex;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	getEnvironment
// Description			:	Load an environment map (which can also be a shadow map)
// Return Value			:
// Comments				:
// Date last edited		:	8/25/2002
CEnvironment	*CShadingContext::getEnvironment(const char *name) {
	CFileResource	*tex;

	if (loadedFiles->find(name,tex) == FALSE){
		tex	=	currentRenderer->environmentLoad(name,texturePath,world->to);

		if (tex == NULL)	{
			// Not found, substitude with a dummy one
			error(CODE_NOFILE,"Unable open environment \"%s\"\n",name);
			tex					=	new CEnvironment(name);
		}

		loadedFiles->insert(tex->name,tex);
	}

	return (CEnvironment *) tex;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	getPhotonMap
// Description			:	Load a photon map
// Return Value			:
// Comments				:
// Date last edited		:	3/11/2003
CPhotonMap		*CShadingContext::getPhotonMap(const char *name) {
	CFileResource	*map;
	char			fileName[OS_MAX_PATH_LENGTH];
	FILE			*in;

	// Check the cache to see if the file is in the memory
	if (loadedFiles->find(name,map) == FALSE){

		// Locate the file
		if (currentRenderer->locateFile(fileName,name,texturePath)) {
			// Try to open the file
			in		=	ropen(fileName,"rb",filePhotonMap,TRUE);
		} else {
			in		=	NULL;
		}

		// Read it
		map		=	new CPhotonMap(name,world,in);
		loadedFiles->insert(map->name,map);
	}

	return (CPhotonMap *) map;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	getCache
// Description			:	Load a cache
// Return Value			:
// Comments				:
// Date last edited		:	3/11/2003
CCache		*CShadingContext::getCache(const char *name,const char *mode) {
	CFileResource	*cache;
	
	// Check the memory first
	if (loadedFiles->find(name,cache) == FALSE){
		char				fileName[OS_MAX_PATH_LENGTH];
		int					flags;
		char				type[128];
		int					createChannel = FALSE;
		CIrradianceCache	*icache = NULL;
		CRadianceCache		*rcache = NULL;

		// Process the file mode
		if (strcmp(mode,"r") == 0) {
			flags	=	CACHE_READ| CACHE_SAMPLE;
		} else if (strcmp(mode,"w") == 0) {
			flags	=	CACHE_WRITE | CACHE_SAMPLE;
		} else if (strcmp(mode,"R") == 0) {
			flags	=	CACHE_READ | CACHE_RDONLY;
		} else if (strcmp(mode,"rw") == 0) {
			flags	=	CACHE_READ | CACHE_WRITE | CACHE_SAMPLE;
		} else {
			flags	=	CACHE_SAMPLE;
		}
		
		// Try to read the file
		cache		=	NULL;
		if (flags & CACHE_READ) {

			// Locate the file
			if (currentRenderer->locateFile(fileName,name,texturePath)) {
				FILE	*in	=	ropen(fileName,type);

				if (in != NULL) {
					// If we're netrendering and writing, treat specially
					if ((netClient != INVALID_SOCKET) && (flags & CACHE_WRITE)) {
						flags			&=	~CACHE_WRITE;		// don't flush cache to disk
						createChannel	=	TRUE;
						if (strncmp(fileName,temporaryPath,strlen(temporaryPath)) == 0) {
							// it's a temp file, delete it after we're done
							currentRenderer->registerFrameTemporary(fileName,TRUE);
						}
						// always remove the file mapping when writing
						currentRenderer->registerFrameTemporary(name,FALSE);
					}
					
					// Create the cache
					if (strcmp(type,fileIrradianceCache) == 0) {
						cache	=	icache	=	new CIrradianceCache(name,flags,worldBmin,worldBmax,world,hierarchy,in);
					} else if (strcmp(type,fileGatherCache) == 0) {
						cache	=	rcache	=	new CRadianceCache(name,flags,worldBmin,worldBmax,hierarchy,in,triangles);
					} else {
						error(CODE_BUG,"This seems to be a Pixie file of unrecognised type (%s)\n",name);
						fclose(in);
					}
				}
			}
		}

		// If there is no cache, create it
		if (cache == NULL) {
			// If we're netrendering and writing, treat specially
			if ((netClient != INVALID_SOCKET) && (flags & CACHE_WRITE)) {
				flags			&=	~CACHE_WRITE;		// don't flush cache to 
				createChannel	=	TRUE;
				// always remove the file mapping when writing
				currentRenderer->registerFrameTemporary(name,FALSE);
			}
			
			// go ahead and create the cache
			if (this->flags & OPTIONS_FLAGS_USE_RADIANCE_CACHE) {
				cache	=	rcache	=	new CRadianceCache(name,flags,worldBmin,worldBmax,hierarchy,NULL,triangles);
			} else {
				cache	=	icache	=	new CIrradianceCache(name,flags,worldBmin,worldBmax,world,hierarchy,NULL);
			}
		}
		
		// Create channels if possible
		if (createChannel == TRUE) {
			if (icache != NULL) {
				requestRemoteChannel(new CRemoteICacheChannel(icache));
			} else if (rcache != NULL) {
				error(CODE_LIMIT,"Radiancecache file \"%s\" cannot be written to in paralell / network renders\n",name);

				// Prevent crashes caused by unwritable empty cache
				delete cache;
				flags |= CACHE_WRITE;
				osTempname(temporaryPath,"rndr",fileName);
				cache = new CRadianceCache(fileName,flags,worldBmin,worldBmax,hierarchy,NULL,triangles);
			}
		}

		loadedFiles->insert(cache->name,cache);
	}

	return (CCache *) cache;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	getTextureInfo
// Description			:	Load a texture from file
// Return Value			:
// Comments				:
// Date last edited		:	02/22/2006
CTextureInfoBase	*CShadingContext::getTextureInfo(const char *name) {
	CFileResource	*tex;

	if (loadedFiles->find(name,tex) == FALSE){
		// try environments first
		tex	=	currentRenderer->environmentLoad(name,texturePath,world->to);

		if (tex == NULL)	{
			// else try as textures
			tex	=	currentRenderer->textureLoad(name,texturePath);
		}

		if (tex != NULL) {
			// only store the result if found
			loadedFiles->insert(tex->name,tex);
		}
	}

	return (CTextureInfoBase *) tex;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	getTexture3d
// Description			:	Get a point cloud or brickmap
// Return Value			:
// Comments				:
// Date last edited		:	02/22/2006
CTexture3d			*CShadingContext::getTexture3d(const char *name,int write,const char* channels,const char *coordsys) {
	CFileResource	*texture3d;
	char			fileName[OS_MAX_PATH_LENGTH];
	FILE			*in;

	if (loadedFiles->find(name,texture3d) == FALSE){
	
		CXform *xform = world;
		if (coordsys != NULL) {
			ECoordinateSystem	esys;
			matrix				*from,*to;
			
			// non worldspace texture
			xform = new CXform();
			findCoordinateSystem(coordsys,from,to,esys);
	
			movmm(xform->from,from[0]);	// construct the transform to put us in the desired system
			movmm(xform->to,to[0]);
		}
		
		// If we are writing, it must be a point cloud
		if (write == TRUE) {
			
			if (netClient != INVALID_SOCKET) {
				CPointCloud	*cloud	=	new CPointCloud(name,xform,channels,FALSE);
				texture3d			=	cloud;
			
				// Ensure we unmap the file when done.  Do not delete it
				// as we mark the file to never be written in the server
				currentRenderer->registerFrameTemporary(name,FALSE);
				requestRemoteChannel(new CRemotePtCloudChannel(cloud));
			} else {
				// alloate a point cloud which will be written to disk
				CXform *dummy = new CXform;
				texture3d	=	new CPointCloud(name,xform,channels,TRUE);
			}
			
		} else {
			// Locate the file
			if (currentRenderer->locateFile(fileName,name,texturePath)) {
				// Try to open the file
				if ((in	=	ropen(fileName,"rb",filePointCloud,TRUE)) != NULL) {
					CXform *dummy = new CXform;
					texture3d	=	new CPointCloud(name,xform,in);
				} else {
					if ((in	=	ropen(fileName,"rb",fileBrickMap,TRUE)) != NULL) {
						texture3d	=	new CBrickMap(in,name,xform);
					}
				}
			} else {
				in		=	NULL;
			}
			
			if (in == NULL) {
				// allocate a dummy blank-channel point cloud
				error(CODE_BADTOKEN,"Cannot find or open Texture3d file \"%s\"\n",name);
				texture3d	=	new CPointCloud(name,xform,NULL,FALSE);
				// remove the dummy mapping once the frame ends
				currentRenderer->registerFrameTemporary(name,FALSE);
			}
		}
		
		// tidy up in case something went wrong
		xform->check();
		
		loadedFiles->insert(texture3d->name,texture3d);
	}

	return (CPointCloud *) texture3d;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	surfaceParameter
// Description			:	Execute light sources
// Return Value			:	-
// Comments				:
// Date last edited		:	8/25/2002
int		CShadingContext::surfaceParameter(void *dest,const char *name,CVariable **var,int *globalIndex) {
	CAttributes	*currentAttributes	=	currentShadingState->currentObject->attributes;

	if (currentAttributes->surface != NULL)
		return currentAttributes->surface->getParameter(name,dest,var,globalIndex);
	return FALSE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	surfaceParameter
// Description			:	Execute light sources
// Return Value			:	-
// Comments				:
// Date last edited		:	8/25/2002
int		CShadingContext::displacementParameter(void *dest,const char *name,CVariable **var,int *globalIndex) {
	CAttributes	*currentAttributes	=	currentShadingState->currentObject->attributes;

	if (currentAttributes->displacement != NULL)
		return currentAttributes->displacement->getParameter(name,dest,var,globalIndex);
	return FALSE;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	surfaceParameter
// Description			:	Execute light sources
// Return Value			:	-
// Comments				:
// Date last edited		:	8/25/2002
int		CShadingContext::atmosphereParameter(void *dest,const char *name,CVariable **var,int *globalIndex) {
	CAttributes	*currentAttributes	=	currentShadingState->currentObject->attributes;

	if (currentAttributes->atmosphere != NULL)
		return currentAttributes->atmosphere->getParameter(name,dest,var,globalIndex);
	return FALSE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	surfaceParameter
// Description			:	Execute light sources
// Return Value			:	-
// Comments				:
// Date last edited		:	8/25/2002
int		CShadingContext::incidentParameter(void *dest,const char *name,CVariable **var,int *globalIndex) {
	CAttributes	*currentAttributes	=	currentShadingState->currentObject->attributes;

	if (currentAttributes->interior != NULL)
		return currentAttributes->interior->getParameter(name,dest,NULL,NULL);	// skip mutable parameters
	return FALSE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	surfaceParameter
// Description			:	Execute light sources
// Return Value			:	-
// Comments				:
// Date last edited		:	8/25/2002
int		CShadingContext::oppositeParameter(void *dest,const char *name,CVariable **var,int *globalIndex) {
	CAttributes	*currentAttributes	=	currentShadingState->currentObject->attributes;

	if (currentAttributes->exterior != NULL)
		return currentAttributes->exterior->getParameter(name,dest,NULL,NULL);	// skip mutable parameters
	return FALSE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	surfaceParameter
// Description			:	Execute light sources
// Return Value			:	-
// Comments				:
// Date last edited		:	8/25/2002
int		CShadingContext::options(void *dest,const char *name,CVariable **,int *) {
	if (strcmp(name,optionsFormat) == 0) {
		float	*d	=	(float *) dest;
		d[0]		=	(float) xres;
		d[1]		=	(float) yres;
		d[2]		=	(float) 1;
		return TRUE;
	} else if (strcmp(name,optionsDeviceFrame) == 0) { 
		float	*d	=	(float *) dest;
		d[0]		=	(float) frame;
		return TRUE;
	} else if (strcmp(name,optionsDeviceResolution) == 0) { 
		float	*d	=	(float *) dest;
		d[0]		=	(float) xres;
		d[1]		=	(float) yres;
		d[2]		=	(float) 1;
		return TRUE;
	} else if (strcmp(name,optionsFrameAspectRatio) == 0) { 
		float	*d	=	(float *) dest;
		d[0]		=	(float) frameAR;
		return TRUE;
	} else if (strcmp(name,optionsCropWindow) == 0) { 
		float	*d	=	(float *) dest;
		d[0]		=	(float) cropLeft;
		d[1]		=	(float) cropTop;
		d[2]		=	(float) cropRight;
		d[3]		=	(float) cropBottom;
		return TRUE;
	} else if (strcmp(name,optionsDepthOfField) == 0) { 
		float	*d	=	(float *) dest;
		d[0]		=	(float) fstop;
		d[1]		=	(float) focallength;
		d[2]		=	(float) focaldistance;
		return TRUE;
	} else if (strcmp(name,optionsShutter) == 0) { 
		float	*d	=	(float *) dest;
		d[0]		=	(float) shutterOpen;
		d[1]		=	(float) shutterClose;
		return TRUE;
	} else if (strcmp(name,optionsClipping) == 0) { 
		float	*d	=	(float *) dest;
		d[0]		=	(float) clipMin;
		d[1]		=	(float) clipMax;
		return TRUE;
	} else if (strcmp(name,optionsBucketSize) == 0) { 
		float	*d	=	(float *) dest;
		d[0]		=	(float) bucketWidth;
		d[1]		=	(float) bucketHeight;
		return TRUE;
	} else if (strcmp(name,optionsColorQuantizer) == 0) { 
		float	*d	=	(float *) dest;
		d[0]		=	(float) colorQuantizer[0];
		d[1]		=	(float) colorQuantizer[1];
		d[2]		=	(float) colorQuantizer[2];
		d[3]		=	(float) colorQuantizer[3];
		return TRUE;
	} else if (strcmp(name,optionsDepthQuantizer) == 0) { 
		float	*d	=	(float *) dest;
		d[0]		=	(float) depthQuantizer[0];
		d[1]		=	(float) depthQuantizer[1];
		d[2]		=	(float) depthQuantizer[2];
		d[3]		=	(float) depthQuantizer[3];
		return TRUE;
	} else if (strcmp(name,optionsPixelFilter) == 0) { 
		float	*d	=	(float *) dest;
		d[0]		=	(float) pixelFilterWidth;
		d[1]		=	(float) pixelFilterHeight;
		return TRUE;
	} else if (strcmp(name,optionsGamma) == 0) { 
		float	*d	=	(float *) dest;
		d[0]		=	(float) gamma;
		d[1]		=	(float) gain;
		return TRUE;
	} else if (strcmp(name,optionsMaxRayDepth) == 0) { 
		float	*d	=	(float *) dest;
		d[0]		=	(float) maxRayDepth;
		return TRUE;
	} else if (strcmp(name,optionsRelativeDetail) == 0) { 
		float	*d	=	(float *) dest;
		d[0]		=	(float) relativeDetail;
		return TRUE;
	} else if (strcmp(name,optionsPixelSamples) == 0) { 
		float	*d	=	(float *) dest;
		d[0]		=	(float) pixelXsamples;
		d[1]		=	(float) pixelYsamples;
		return TRUE;
	}
	return FALSE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	surfaceParameter
// Description			:	Execute light sources
// Return Value			:	-
// Comments				:
// Date last edited		:	8/25/2002
int		CShadingContext::attributes(void *dest,const char *name,CVariable **,int *) {
	CAttributes	*currentAttributes	=	currentShadingState->currentObject->attributes;

	if (strcmp(name,attributesShadingRate) == 0) {
		float	*d	=	(float *) dest;
		d[0]		=	(float) currentAttributes->shadingRate;
		return TRUE;
	} else if (strcmp(name,attributesSides) == 0) {
		float	*d	=	(float *) dest;
		d[0]		=	(float) currentAttributes->nSides;
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
		d[0]		=	(float) currentAttributes->shadowBias;
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
	
	return FALSE;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	surfaceParameter
// Description			:	Execute light sources
// Return Value			:	-
// Comments				:
// Date last edited		:	8/25/2002
int		CShadingContext::rendererInfo(void *dest,const char *name,CVariable **,int *) {
	
	if (strcmp(name,rendererinfoRenderer) == 0) {
		char	**d	=	(char **) dest;
		d[0]		=	"Pixie";
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
// Method				:	surfaceParameter
// Description			:	Execute light sources
// Return Value			:	-
// Comments				:
// Date last edited		:	8/25/2002
const char	*CShadingContext::shaderName() {
	assert(currentShadingState->currentShaderInstance != NULL);

	return currentShadingState->currentShaderInstance->getName();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	surfaceParameter
// Description			:	Execute light sources
// Return Value			:	-
// Comments				:
// Date last edited		:	8/25/2002
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
// Comments				:
// Date last edited		:	8/25/2002
void		CShadingContext::findCoordinateSystem(const char *name,matrix *&from,matrix *&to,ECoordinateSystem &cSystem) {
	if (currentRenderer->findCoordinateSystem(name,from,to,cSystem)) {
		// The coordinate systems that don't have ant implementation will be pushed into the
		// CDictionary as a custom coordinate system for they are constant accross a frame
		
		switch(cSystem) {
		case COORDINATE_OBJECT:
			if (currentShadingState->currentObject == NULL) {
				error(CODE_SYSTEM,"Object system reference without an object\n");
				from		=	&identity;
				to			=	&identity;
			} else {
				from		=	&(currentShadingState->currentObject->xform->from);
				to			=	&(currentShadingState->currentObject->xform->to);
			}
			break;
		case COORDINATE_CAMERA:
			from		=	&identity;
			to			=	&identity;
			break;
		case COORDINATE_WORLD:
			from		=	&world->from;
			to			=	&world->to;
			break;
		case COORDINATE_SHADER:
			assert(currentShadingState->currentShaderInstance != NULL);

			from		=	&(currentShadingState->currentShaderInstance->xform->from);
			to			=	&(currentShadingState->currentShaderInstance->xform->to);
			break;
		case COORDINATE_LIGHT:
			assert(currentShadingState->currentLightInstance != NULL);

			from		=	&(currentShadingState->currentLightInstance->xform->from);
			to			=	&(currentShadingState->currentLightInstance->xform->to);
			break;
		case COORDINATE_NDC:
			from		=	&fromNDC;
			to			=	&toNDC;
			break;
		case COORDINATE_RASTER:
			from		=	&fromRaster;
			to			=	&toRaster;
			break;
		case COORDINATE_SCREEN:
			from		=	&fromScreen;
			to			=	&toScreen;
			break;
		case COORDINATE_CURRENT:
			from		=	&identity;
			to			=	&identity;
			break;
		case COLOR_RGB:
		case COLOR_HSL:
		case COLOR_HSV:
		case COLOR_XYZ:
		case COLOR_CIE:
		case COLOR_YIQ:
		case COLOR_XYY:
		case COORDINATE_CUSTOM:
			// Don't handle color, the custom must have been handled
			break;
		default:
			warning(CODE_BUG,"Unknown coordinate system: %s\n",name);
			from	=	&identity;
			to		=	&identity;
		}	
	} else {
		warning(CODE_BUG,"Unknown coordinate system: %s\n",name);
		from	=	&identity;
		to		=	&identity;
	}
}
