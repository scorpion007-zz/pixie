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
//  File				:	renderer.cpp
//  Classes				:	CRenderer
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include <string.h>
#include <math.h>

#include "renderer.h"
#include "ray.h"
#include "object.h"
#include "xform.h"
#include "shader.h"
#include "texture.h"
#include "raytracer.h"
#include "stochastic.h"
#include "zbuffer.h"
#include "patches.h"
#include "ri.h"
#include "rib.h"
#include "noise.h"
#include "stats.h"
#include "memory.h"
#include "photonMap.h"
#include "photon.h"
#include "polygons.h"
#include "quadrics.h"
#include "patches.h"
#include "subdivisionCreator.h"
#include "irradiance.h"
#include "random.h"
#include "points.h"
#include "curves.h"
#include "instance.h"
#include "delayed.h"
#include "dso.h"
#include "bundles.h"
#include "texmake.h"
#include "pl.h"
#include "error.h"
#include "hcshader.h"
#include "implicitSurface.h"
#include "dlobject.h"
#include "brickmap.h"
#include "show.h"
#include "remoteChannel.h"
#include "rendererContext.h"







/////////////////////////////////////////////////////////////////////
// Static members of the CRenderer
/////////////////////////////////////////////////////////////////////




// Global members (active between RiBegin() - RiEnd())
CRendererContext									*CRenderer::context						=	NULL;
CArray<CShaderInstance *>							*CRenderer::allLights					=	NULL;
CDictionary<const char *,CNamedCoordinateSystem *>	*CRenderer::definedCoordinateSystems	=	NULL;
CDictionary<const char *,CVariable *>				*CRenderer::declaredVariables			=	NULL;
CDictionary<const char *,CFileResource  *>			*CRenderer::loadedFiles					=	NULL;
CDictionary<const char *,CGlobalIdentifier *>		*CRenderer::globalIdHash				=	NULL;
CDictionary<const char *,CRenderer::CNetFileMapping *>	*CRenderer::netFileMappings			=	NULL;
int													CRenderer::numKnownGlobalIds			=	0;
CVariable											*CRenderer::variables					=	NULL;
CArray<CVariable *>									*CRenderer::globalVariables				=	NULL;
CDictionary<const char *,CDisplayChannel *>			*CRenderer::declaredChannels			=	NULL;
CArray<CDisplayChannel*>							*CRenderer::displayChannels				=	NULL;
CDSO												*CRenderer::dsos						=	NULL;
SOCKET												CRenderer::netClient					=	INVALID_SOCKET;
int													CRenderer::netNumServers				=	0;
SOCKET												*CRenderer::netServers					=	NULL;
TMutex												CRenderer::commitMutex;
int													CRenderer::numNetrenderedBuckets		=	0;





// Local members (active between RiWorldBegin() - RiWorldEnd())
CMemStack											*CRenderer::frameMemory				=	NULL;
CArray<const char*>									*CRenderer::frameTemporaryFiles		=	NULL;
CShadingContext										**CRenderer::contexts				=	NULL;
COptions											CRenderer::options;
CDictionary<const char *,CRemoteChannel *>			*CRenderer::declaredRemoteChannels	=	NULL;
CArray<CRemoteChannel *>							*CRenderer::remoteChannels			=	NULL;
CArray<CAttributes *>								*CRenderer::dirtyAttributes			=	NULL;
CArray<CProgrammableShaderInstance *>				*CRenderer::dirtyInstances			=	NULL;
unsigned int			CRenderer::raytracingFlags					=	0;
CHierarchy				*CRenderer::hierarchy						=	NULL;
CArray<CTriangle *>		*CRenderer::triangles						=	NULL;
CArray<CSurface *>		*CRenderer::raytraced						=	NULL;
CArray<CTracable *>		*CRenderer::tracables						=	NULL;
CObject					*CRenderer::offendingObject					=	NULL;
matrix					CRenderer::fromWorld,CRenderer::toWorld;
CXform					*CRenderer::world							=	NULL;
matrix					CRenderer::fromNDC,CRenderer::toNDC;
matrix					CRenderer::fromRaster,CRenderer::toRaster;
matrix					CRenderer::fromScreen,CRenderer::toScreen;
matrix					CRenderer::worldToNDC;
unsigned int			CRenderer::hiderFlags;
int						CRenderer::numSamples;
int						CRenderer::numExtraSamples;
int						CRenderer::xPixels,CRenderer::yPixels;
unsigned int			CRenderer::additionalParameters;
float					CRenderer::pixelLeft,CRenderer::pixelRight,CRenderer::pixelTop,CRenderer::pixelBottom;
float					CRenderer::dydPixel,CRenderer::dxdPixel;
float					CRenderer::dPixeldx,CRenderer::dPixeldy;
int						CRenderer::renderLeft,CRenderer::renderRight,CRenderer::renderTop,CRenderer::renderBottom;
int						CRenderer::xBuckets,CRenderer::yBuckets;
int						CRenderer::metaXBuckets,CRenderer::metaYBuckets;
float					CRenderer::aperture;
float					CRenderer::imagePlane;
float					CRenderer::invImagePlane;
float					CRenderer::cocFactorPixels;
float					CRenderer::cocFactorSamples;
float					CRenderer::cocFactorScreen;
float					CRenderer::invFocaldistance;
float					CRenderer::lengthA,CRenderer::lengthB;
float					CRenderer::marginXcoverage,CRenderer::marginYcoverage;
float					CRenderer::marginX,CRenderer::marginY;
float					CRenderer::marginalX,CRenderer::marginalY;
float					CRenderer::leftX,CRenderer::leftZ,CRenderer::leftD;
float					CRenderer::rightX,CRenderer::rightZ,CRenderer::rightD;
float					CRenderer::topY,CRenderer::topZ,CRenderer::topD;
float					CRenderer::bottomY,CRenderer::bottomZ,CRenderer::bottomD;
int						CRenderer::numActiveDisplays;
int						CRenderer::currentXBucket;
int						CRenderer::currentYBucket;
int						*CRenderer::jobAssignment;
FILE					*CRenderer::deepShadowFile			=	NULL;
int						*CRenderer::deepShadowIndex			=	NULL;
int						CRenderer::deepShadowIndexStart;
char					*CRenderer::deepShadowFileName		=	NULL;















///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	beginRenderer
// Description			:	Begin the renderer
// Return Value			:	-
// Comments				:
// Date last edited		:	10/9/2006
void		CRenderer::beginRenderer(CRendererContext *c,char *ribFile,char *riNetString) {
	float			startTime	=	osCPUTime();

	// Save the context
	context		=	c;

	// Reset the stats
	stats.reset();

	// Init the memory
	memoryInit();

	// Init the files
	initFiles();

	// Init the declerations
	initDeclerations();

	// Init the network
	initNetwork(ribFile,riNetString);
	
	// Init the light sources we use
	allLights						=	new CArray<CShaderInstance *>;
	
	// Record the start overhead
	stats.rendererStartOverhead		=	osCPUTime() - startTime;

	// Good to rock and roll
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	endRenderer
// Description			:	End the renderer
// Return Value			:	-
// Comments				:
// Date last edited		:	10/9/2006
void		CRenderer::endRenderer() {
	// Ditch the allocated lights
	CShaderInstance	**array	=	allLights->array;
	int				size	=	allLights->numItems;
	int				i;

	for (i=0;i<size;i++)	array[i]->detach();
	delete allLights;

	// Init the network
	shutdownNetwork();

	// Init the declerations
	shutdownDeclerations();

	// Init the files
	shutdownFiles();

	// Cleanup the parser
	parserCleanup();

	// Turn off the memory manager
	memoryTini();

	// Check the stats for memory leaks
	stats.check();
}

















///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	beginFrame
// Description			:	Begin a frame / compute misc data
// Return Value			:	-
// Comments				:
// Date last edited		:	10/9/2006
void		CRenderer::beginFrame(CRendererContext *c,const COptions *o,CXform *x) {

	// Record the frame start time
	stats.frameStartTime	=	osCPUTime();

	// This is the memory we allocate our junk from (only permenant stuff for the entire frame)
	frameMemory				=	new CMemStack(1 << 20);

	// Save the options
	options					=	*o;

	// Save the world xform
	world					=	x;
	world->attach();
	movmm(fromWorld,x->from);
	movmm(toWorld,x->to);

	// Save / precompute some interesting stuff
	hiderFlags				=	hf;

	assert(options.pixelXsamples > 0);
	assert(options.pixelYsamples > 0);

	// Compute some stuff
	if (options.flags & OPTIONS_FLAGS_CUSTOM_FRAMEAR) {
		const float	ar	=	options.xres*options.pixelAR / (float) options.yres;

		// Update the resolution as necessary
		if (options.frameAR > ar) {
			options.yres	=	(int) (options.xres*options.pixelAR / options.frameAR);
		} else {
			options.xres	=	(int) (options.frameAR * options.yres / options.pixelAR);
		}
	} else {
		options.frameAR = options.xres*options.pixelAR / (float) options.yres;
	}


	if (options.flags & OPTIONS_FLAGS_CUSTOM_SCREENWINDOW) {
		// The user explicitly entered the screen window, so we don't have to make sure it matches the frame aspect ratio
	} else {
		if (options.frameAR > (float) 1.0) {
			options.screenTop			=	(float) 1.0;
			options.screenBottom		=	(float) -1.0;
			options.screenLeft			=	-options.frameAR;
			options.screenRight			=	options.frameAR;
		} else {
			options.screenTop			=	1/options.frameAR;
			options.screenBottom		=	-1/options.frameAR;
			options.screenLeft			=	(float) -1.0;
			options.screenRight			=	(float) 1.0;
		}
	}

	imagePlane		=	1;
	if (options.projection == OPTIONS_PROJECTION_PERSPECTIVE) {
		imagePlane	=	(float) (1/tan(radians(options.fov/(float) 2)));
	} else {
		imagePlane	=	1;
	}

	invImagePlane	=	1/imagePlane;

	assert(options.cropLeft < options.cropRight);
	assert(options.cropTop < options.cropBottom);

	// Rendering window in pixels
	renderLeft			=	(int) ceil(options.xres*options.cropLeft);
	renderRight			=	(int) ceil(options.xres*options.cropRight);
	renderTop			=	(int) ceil(options.yres*options.cropTop);
	renderBottom		=	(int) ceil(options.yres*options.cropBottom);

	assert(renderRight > renderLeft);
	assert(renderBottom > renderTop);

	// The resolution of the actual render window
	xPixels				=	renderRight		-	renderLeft;
	yPixels				=	renderBottom	-	renderTop;

	assert(xPixels >= 0);
	assert(yPixels >= 0);

	dxdPixel			=	(options.screenRight	- options.screenLeft) / (float) (options.xres);
	dydPixel			=	(options.screenBottom	- options.screenTop) / (float) (options.yres);
	dPixeldx			=	1	/	dxdPixel;
	dPixeldy			=	1	/	dydPixel;
	pixelLeft			=	(float) (options.screenLeft	+ renderLeft*dxdPixel);
	pixelTop			=	(float) (options.screenTop	+ renderTop*dydPixel);
	pixelRight			=	pixelLeft	+ dxdPixel*xPixels;
	pixelBottom			=	pixelTop	+ dydPixel*yPixels;

	xBuckets			=	(int) ceil(xPixels / (float) options.bucketWidth);
	yBuckets			=	(int) ceil(yPixels / (float) options.bucketHeight);

	metaXBuckets		=	(int) ceil(xBuckets / (float) options.netXBuckets);
	metaYBuckets		=	(int) ceil(yBuckets / (float) options.netYBuckets);

	jobAssignment		=	NULL;

	aperture			=	options.focallength / (2*options.fstop);
	if ((aperture <= C_EPSILON) || (options.projection == OPTIONS_PROJECTION_ORTHOGRAPHIC)) {
		aperture			=	0;
		cocFactorScreen		=	0;
		cocFactorSamples	=	0;
		cocFactorPixels		=	0;
		invFocaldistance	=	0;
	} else {
		cocFactorScreen		=	(float) (imagePlane*aperture*options.focaldistance /  (options.focaldistance + aperture));
		cocFactorSamples	=	cocFactorScreen*sqrtf(dPixeldx*dPixeldx*options.pixelXsamples*options.pixelXsamples + dPixeldy*dPixeldy*options.pixelYsamples*options.pixelYsamples);
		cocFactorPixels		=	cocFactorScreen*sqrtf(dPixeldx*dPixeldx + dPixeldy*dPixeldy);
		invFocaldistance	=	1 / options.focaldistance;
	}

	if (options.projection == OPTIONS_PROJECTION_ORTHOGRAPHIC) {
		lengthA			=	0;
		lengthB			=	sqrtf(dxdPixel*dxdPixel + dydPixel*dydPixel);
	} else {
		lengthA			=	sqrtf(dxdPixel*dxdPixel + dydPixel*dydPixel) / imagePlane;
		lengthB			=	0;
	}

	if (aperture				!= 0)					options.flags	|=	OPTIONS_FLAGS_FOCALBLUR;
	if (options.shutterClose	!= options.shutterOpen)	options.flags	|=	OPTIONS_FLAGS_MOTIONBLUR;

	// Compute the matrices related to the camera transformation
	if (options.projection == OPTIONS_PROJECTION_PERSPECTIVE) {
		toNDC[element(0,0)]		=	imagePlane / (options.screenRight - options.screenLeft);
		toNDC[element(0,1)]		=	0;
		toNDC[element(0,2)]		=	-options.screenLeft / (options.screenRight - options.screenLeft);
		toNDC[element(0,3)]		=	0;

		toNDC[element(1,0)]		=	0;
		toNDC[element(1,1)]		=	imagePlane / (options.screenBottom - options.screenTop);
		toNDC[element(1,2)]		=	-options.screenTop / (options.screenBottom - options.screenTop);
		toNDC[element(1,3)]		=	0;

		toNDC[element(2,0)]		=	0;
		toNDC[element(2,1)]		=	0;
		toNDC[element(2,2)]		=	1;
		toNDC[element(2,3)]		=	0;

		toNDC[element(3,0)]		=	0;
		toNDC[element(3,1)]		=	0;
		toNDC[element(3,2)]		=	1;
		toNDC[element(3,3)]		=	0;
	} else {
		toNDC[element(0,0)]		=	1 / (options.screenRight - options.screenLeft);
		toNDC[element(0,1)]		=	0;
		toNDC[element(0,2)]		=	0;
		toNDC[element(0,3)]		=	-options.screenLeft / (options.screenRight - options.screenLeft);

		toNDC[element(1,0)]		=	0;
		toNDC[element(1,1)]		=	1 / (options.screenBottom - options.screenTop);
		toNDC[element(1,2)]		=	0;
		toNDC[element(1,3)]		=	-options.screenTop / (options.screenBottom - options.screenTop);

		toNDC[element(2,0)]		=	0;
		toNDC[element(2,1)]		=	0;
		toNDC[element(2,2)]		=	1;
		toNDC[element(2,3)]		=	0;

		toNDC[element(3,0)]		=	0;
		toNDC[element(3,1)]		=	0;
		toNDC[element(3,2)]		=	0;
		toNDC[element(3,3)]		=	1;
	}

	// The inverse fromNDC is the same for both perspective and orthographic projections
	fromNDC[element(0,0)]	=	(options.screenRight - options.screenLeft);
	fromNDC[element(0,1)]	=	0;
	fromNDC[element(0,2)]	=	0;
	fromNDC[element(0,3)]	=	options.screenLeft;

	fromNDC[element(1,0)]	=	0;
	fromNDC[element(1,1)]	=	(options.screenBottom - options.screenTop);
	fromNDC[element(1,2)]	=	0;
	fromNDC[element(1,3)]	=	options.screenTop;

	fromNDC[element(1,0)]	=	0;
	fromNDC[element(1,1)]	=	0;
	fromNDC[element(1,2)]	=	0;
	fromNDC[element(1,3)]	=	imagePlane;

	fromNDC[element(3,0)]	=	0;
	fromNDC[element(3,1)]	=	0;
	fromNDC[element(3,2)]	=	0;
	fromNDC[element(3,3)]	=	1;


	// Compute the fromRaster / toRaster
	matrix	mtmp;

	identitym(mtmp);
	mtmp[element(0,0)]		=	(float) options.xres;
	mtmp[element(1,1)]		=	(float) options.yres;
	mulmm(toRaster,mtmp,toNDC);

	identitym(mtmp);
	mtmp[element(0,0)]		=	1 / (float) options.xres;
	mtmp[element(1,1)]		=	1 / (float) options.yres;
	mulmm(fromRaster,fromNDC,mtmp);

	// Compute the world to NDC transform required by the shadow maps
	mulmm(worldToNDC,toNDC,fromWorld);


	if (options.displays == NULL) {
		options.displays				=	new CDisplay;
		options.displays->next			=	NULL;
		options.displays->outDevice		=	strdup(RI_FILE);
		options.displays->outName		=	strdup("ri.tif");
		options.displays->outSamples	=	strdup(RI_RGBA);
	}

	marginalX			=	options.pixelFilterWidth / 2;
	marginalY			=	options.pixelFilterHeight / 2;
	marginX				=	(float) floor(marginalX);
	marginY				=	(float) floor(marginalY);
	marginXcoverage		=	max(marginalX - marginX,0);
	marginYcoverage		=	max(marginalY -	marginY,0);

	currentXBucket		=	0;
	currentYBucket		=	0;



	
	// Initialize the extend of the world
	initv(worldBmin,C_INFINITY,C_INFINITY,C_INFINITY);
	initv(worldBmax,-C_INFINITY,-C_INFINITY,-C_INFINITY);


	// This is the set of raytraced objects
	raytraced				=	NULL;
	hierarchy				=	NULL;
	tracables				=	NULL;
	triangles				=	NULL;

	// Init the loaded files
	loadedFiles				=	new CTrie<CFileResource *>;
	dirtyInstances			=	NULL;
	dirtyAttributes			=	NULL;
	
	raytracingFlags			=	ATTRIBUTES_FLAGS_PHOTON_VISIBLE			|
								ATTRIBUTES_FLAGS_TRACE_VISIBLE			|
								ATTRIBUTES_FLAGS_TRANSMISSION_VISIBLE;

	if (hiderFlags & HIDER_NEEDS_RAYTRACING) {
		raytracingFlags		|=	ATTRIBUTES_FLAGS_PRIMARY_VISIBLE;
	}

	// Initialize remote channels
	remoteChannels			=	new CArray<CRemoteChannel*>;
	declaredRemoteChannels	=	new CTrie<CRemoteChannel*>;


	// Compute the clipping data
	beginClipping();

	// Start the displays
	beginDisplays();

	// Initialize the texturing
	CTexture::textureInit(options.maxTextureSize);

	// Initialize the brickmaps
	CBrickMap::brickMapInit(options.maxBrickSize);

	// Initialize the random number generator for the frame
	randomInit();

	// Start the contexts
	int	i;
	contexts		=	new CShadingContext*[options.numThreads];
	for (i=0;i<options.numThreads;i++) {

		// Start the hiders here
		contexts[i]	=	NULL;

		if (strcmp(options.hider,"raytrace") == 0) {
			contexts[i]						=	new CRaytracer();
			dispatchJob						=	singleThreadedReyes;
		} else if (strcmp(options.hider,"stochastic") == 0) {
			contexts[i]						=	new CStochastic();
			dispatchJob						=	singleThreadedReyes;
		} else if (strcmp(options.hider,"zbuffer") == 0) {
			contexts[i]						=	new CZbuffer();
			dispatchJob						=	singleThreadedReyes;
		} else if (strncmp(options.hider,"show:",5) == 0) {
			contexts[i]						=	new CShow();
			dispatchJob						=	singleThreadedReyes;
		} else if (strcmp(options.hider,"photon") == 0) {
			if ((netClient != INVALID_SOCKET) || (netNumServers > 0)) {
				error(CODE_LIMIT,"Hider \"%s\" does not support paralell / network rendering\n",options.hider);
				contexts[i]					=	new CStochastic();
				dispatchJob					=	singleThreadedReyes;
			} else {
				contexts[i]					=	new CPhotonHider(context->getAttributes(TRUE));
				dispatchJob					=	singleThreadedPhoton;
			}
		} else {
			error(CODE_BADTOKEN,"Hider \"%s\" unavailable\n",options.hider);
			contexts[i]						=	new CStochastic();
			dispatchJob						=	singleThreadedReyes;
		}

		assert(contexts[i] != NULL);

		contexts[i]->updateState();
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	endFrame
// Description			:	Finish the frame
// Return Value			:	-
// Comments				:
// Date last edited		:	10/9/2006
void		CRenderer::endFrame() {
	
	// Shutdown the texturing system
	CBrickMap::brickMapShutdown();

	// Shutdown the brickmaps
	CTexture::textureShutdown();

	// Shutdown the random number generator
	randomShutdown();

	// Terminate the displays
	endDisplays();

	// Delete the job queue
	if (jobAssignment	!= NULL) {
		delete [] jobAssignment;
		jobAssignment	=	NULL;
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
		dirtyInstances	=	NULL;
	}

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

	// Ditch the remote channels
	for (int i=0;i<remoteChannels->numItems;i++) {
		if (remoteChannels->array[i] != NULL) delete remoteChannels->array[i];
	}
	delete remoteChannels;
	delete declaredRemoteChannels;
	remoteChannels			=	NULL;
	declaredRemoteChannels	=	NULL;


	// Detach from the raytraced objects
	if (raytraced != NULL) {
		int			i;
		CSurface	**surfaces	=	raytraced->array;

		for (i=raytraced->numItems;i>0;i--)	(*surfaces++)->detach();

		delete raytraced;
		raytraced	=	NULL;
	}

	// We should not have any dangling raytraced objects
	assert(tracables == NULL);

	// Ditch the triangle list if it's still around
	if (triangles != NULL) {
		delete triangles;
		triangles	=	NULL;
	}

	// Ditch the raytracing hierarchy
	if (hierarchy != NULL) {
		delete hierarchy;
		hierarchy	=	NULL;
	}

	// Release the world
	world->detach();
	world		=	NULL;

	// Ditch the frame memory
	delete frameMemory;
	frameMemory	=	NULL;

	// Remove end-of-frame temporary files
	if (frameTemporaryFiles != NULL) {
		int			i,numTemps	=	frameTemporaryFiles->numItems;
		const char	**tempFiles	=	frameTemporaryFiles->array;
		for (i=0;i<numTemps;i++) {
			int			removeFile	= (*tempFiles)[0];
			const char	*fileName 	= &(*tempFiles)[1];
			
			// Remove file if needed
			if (removeFile) {
				if (osFileExists(fileName) == TRUE) {
					osDeleteFile(fileName);
				}
			}
			
			// Remove temp file mapping if it exists
			if (netFileMappings != NULL) {
				CNetFileMapping* mapping;
				if (netFileMappings->erase(fileName,mapping) == TRUE) {
					delete mapping;
				}
			}
			
			tempFiles++;
		}
		frameTemporaryFiles->destroy();
		frameTemporaryFiles = NULL;
	}

	// Receive an end of frame confirmation to the server
	if (netClient != INVALID_SOCKET) {
		T32		netBuffer;

		// Expect the ready message
		rcRecv(netClient,(char *) &netBuffer,1*sizeof(T32));

		if (netBuffer.integer == NET_READY) {
			// We're proceeding to the next frame
		} else {
			fatal(CODE_BADTOKEN,"Invalid net command\n");
		}
	}

	// Print the stats (before we discard the memory)
	stats.frameTime		=	osCPUTime()		-	stats.frameStartTime;

	// Display the stats if applicable
	if (options.endofframe > 0)	stats.printStats(options.endofframe);
}






///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	render
// Description			:	Add an object into the scene
// Return Value			:
// Comments				:
// Date last edited		:	10/9/2006
void			CRenderer::render(CObject *cObject,const float *bmin,const float *bmax) {
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

	// Update the world bounding box
	addBox(worldBmin,worldBmax,bmin);
	addBox(worldBmin,worldBmax,bmax);

	// Tesselate the object if applicable
	if (cObject->attributes->flags & raytracingFlags) {

		// Tesselate the object
		cObject->tesselate(contexts[0]);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	removeTracable
// Description			:	Remove a delayed object
// Return Value			:
// Comments				:
// Date last edited		:	10/9/2006
void			CRenderer::removeTracable(CTracable *cObject) {
	if (hierarchy != NULL) {
		vector	bmin,bmax;

		// Bound the object
		cObject->bound(bmin,bmax);

		hierarchy->remove(cObject,bmin,bmax);
	}
}




///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	addTracable
// Description			:	Add a raytracable object into the frame
// Return Value			:	-
// Comments				:
// Date last edited		:	10/9/2006
void		CRenderer::addTracable(CTracable *tracable,CSurface *object) {

	if (tracables == NULL)	tracables	=	new CArray<CTracable *>;
	if (raytraced == NULL)	raytraced	=	new CArray<CSurface *>;

	object->attach();

	tracables->push(tracable);
	raytraced->push(object);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	addTracable
// Description			:	Add a raytracable object into the frame
// Return Value			:	-
// Comments				:
// Date last edited		:	10/9/2006
void		CRenderer::addTracable(CTriangle *tracable,CSurface *object) {
	if (tracables == NULL)	tracables	=	new CArray<CTracable *>;
	if (raytraced == NULL)	raytraced	=	new CArray<CSurface *>;

	object->attach();

	tracables->push(tracable);
	raytraced->push(object);

	if (triangles != NULL) triangles->push(tracable);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	addTracable
// Description			:	Add a raytracable object into the frame
// Return Value			:	-
// Comments				:
// Date last edited		:	10/9/2006
void		CRenderer::addTracable(CMovingTriangle *tracable,CSurface *object) {
	if (tracables == NULL)	tracables	=	new CArray<CTracable *>;
	if (raytraced == NULL)	raytraced	=	new CArray<CSurface *>;

	object->attach();

	tracables->push(tracable);
	raytraced->push(object);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	prepareFrame
// Description			:	Prepare to render a frame
// Return Value			:	-
// Comments				:
// Date last edited		:	10/9/2006
void		CRenderer::prepareFrame() {

	if (hierarchy == NULL) {
		// Init the hierarchy
		hierarchy	=	new CHierarchy(tracables->numItems,tracables->array,worldBmin,worldBmax,frameMemory);
	} else {
		hierarchy->add(tracables->numItems,tracables->array);
	}

	delete tracables;
	tracables	=	NULL;
}




///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	renderFrame
// Description			:	Render the frame
// Return Value			:	-
// Comments				:
// Date last edited		:	10/9/2006
void		CRenderer::renderFrame() {
	// Render the frame
	if (netNumServers != 0) {

		// Dispatch the rendering job to the servers
		clientRenderFrame();

	} else {
		const	char	*previousActivity	=	stats.activity;
	
		stats.activity	=	"Rendering";

		// Let the client know that we're ready to render
		if (netClient != INVALID_SOCKET) {
			T32		netBuffer;

			netBuffer.integer	=	NET_READY;
			rcSend(netClient,(char *) &netBuffer,1*sizeof(T32));
		}

		// Enter the rendering loop
		contexts[0]->renderingLoop();

		stats.activity	=	previousActivity;
	}
}











































