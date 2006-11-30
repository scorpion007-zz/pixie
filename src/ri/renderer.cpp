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




// Textual definitions of predefined coordinate systems
const char	*coordinateCameraSystem		=	"camera";
const char	*coordinateWorldSystem		=	"world";
const char	*coordinateObjectSystem		=	"object";
const char	*coordinateShaderSystem		=	"shader";
const char	*coordinateLightSystem		=	"light";
const char	*coordinateNDCSystem		=	"NDC";
const char	*coordinateRasterSystem		=	"raster";
const char	*coordinateScreenSystem		=	"screen";
const char	*coordinateCurrentSystem	=	"current";

// Textual definitions of the predefined color systems
const char	*colorRgbSystem				=	"rgb";
const char	*colorHslSystem				=	"hsl";
const char	*colorHsvSystem				=	"hsv";
const char	*colorXyzSystem				=	"xyz";
const char	*colorYiqSystem				=	"yiq";
const char	*colorXyySystem				=	"xyy";
const char	*colorCieSystem				=	"cie";





/////////////////////////////////////////////////////////////////////
//
// Static members of the CRenderer
//
/////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////
// Global members (active between RiBegin() - RiEnd())
////////////////////////////////////////////////////////////////////
CMemPage						*CRenderer::globalMemory				=	NULL;
CRendererContext				*CRenderer::context						=	NULL;
CArray<CShaderInstance *>		*CRenderer::allLights					=	NULL;
CTrie<CNamedCoordinateSystem *>	*CRenderer::definedCoordinateSystems	=	NULL;
CTrie<CVariable *>				*CRenderer::declaredVariables			=	NULL;
CTrie<CFileResource  *>			*CRenderer::globalFiles					=	NULL;
CTrie<CGlobalIdentifier *>		*CRenderer::globalIdHash				=	NULL;
CTrie<CNetFileMapping *>		*CRenderer::netFileMappings				=	NULL;
int								CRenderer::numKnownGlobalIds			=	0;
CVariable						*CRenderer::variables					=	NULL;
CArray<CVariable *>				*CRenderer::globalVariables				=	NULL;
CTrie<CDisplayChannel *>		*CRenderer::declaredChannels			=	NULL;
CArray<CDisplayChannel*>		*CRenderer::displayChannels				=	NULL;
CDSO							*CRenderer::dsos						=	NULL;
SOCKET							CRenderer::netClient					=	INVALID_SOCKET;
int								CRenderer::netNumServers				=	0;
SOCKET							*CRenderer::netServers					=	NULL;
int								CRenderer::numNetrenderedBuckets		=	0;
char							CRenderer::temporaryPath[OS_MAX_PATH_LENGTH];
int								CRenderer::textureRefNumber				=	0;
CTextureBlock					*CRenderer::textureUsedBlocks			=	NULL;
int								CRenderer::textureUsedMemory			=	0;
int								CRenderer::textureMaxMemory				=	0;

// Global synchronization objects
TMutex							CRenderer::commitMutex;
TMutex							CRenderer::dispatchMutex;
TMutex							CRenderer::memoryMutex;
TMutex							CRenderer::networkMutex;
TMutex							CRenderer::hierarchyMutex;
TMutex							CRenderer::tesselateMutex;
TMutex							CRenderer::textureMutex;
TMutex							CRenderer::refCountMutex;
TMutex							CRenderer::shaderMutex;
TMutex							CRenderer::delayedMutex;

////////////////////////////////////////////////////////////////////
// Local members (active between RiWorldBegin() - RiWorldEnd())
////////////////////////////////////////////////////////////////////
// Frame options
int								CRenderer::xres,CRenderer::yres;
int								CRenderer::frame;
float							CRenderer::pixelAR;
float							CRenderer::frameAR;
float							CRenderer::cropLeft,CRenderer::cropRight,CRenderer::cropTop,CRenderer::cropBottom;
float							CRenderer::screenLeft,CRenderer::screenRight,CRenderer::screenTop,CRenderer::screenBottom;
float							CRenderer::clipMin,CRenderer::clipMax;
float							CRenderer::pixelVariance;
float							CRenderer::jitter;
char							*CRenderer::hider;
TSearchpath						*CRenderer::archivePath;
TSearchpath						*CRenderer::proceduralPath;
TSearchpath						*CRenderer::texturePath;
TSearchpath						*CRenderer::shaderPath;
TSearchpath						*CRenderer::displayPath;
TSearchpath						*CRenderer::modulePath;
int								CRenderer::pixelXsamples,CRenderer::pixelYsamples;
float							CRenderer::gamma,CRenderer::gain;
float							CRenderer::pixelFilterWidth,CRenderer::pixelFilterHeight;
RtFilterFunc					CRenderer::pixelFilter;
float							CRenderer::colorQuantizer[5];
float							CRenderer::depthQuantizer[5];
COptions::CDisplay				*CRenderer::displays;
COptions::CClipPlane			*CRenderer::clipPlanes;
float							CRenderer::relativeDetail;
EProjectionType					CRenderer::projection;
float							CRenderer::fov;
int								CRenderer::nColorComps;
float							*CRenderer::fromRGB,*CRenderer::toRGB;
float							CRenderer::fstop,CRenderer::focallength,CRenderer::focaldistance;
float							CRenderer::shutterOpen,CRenderer::shutterClose;
unsigned int					CRenderer::flags;

// Pixie dependent options
int								CRenderer::endofframe;
char							*CRenderer::filelog;
int								CRenderer::numThreads;
int								CRenderer::maxTextureSize;
int								CRenderer::maxBrickSize;
int								CRenderer::maxGridSize;
int								CRenderer::maxRayDepth;
int								CRenderer::maxPhotonDepth;
int								CRenderer::bucketWidth,CRenderer::bucketHeight;
int								CRenderer::netXBuckets,CRenderer::netYBuckets;
int								CRenderer::threadStride;
int								CRenderer::maxEyeSplits;
float							CRenderer::tsmThreshold;
char							*CRenderer::causticIn,*CRenderer::causticOut;
char							*CRenderer::globalIn,*CRenderer::globalOut;
char							*CRenderer::volumeIn,*CRenderer::volumeOut;
int								CRenderer::numEmitPhotons;
int								CRenderer::shootStep;
EDepthFilter					CRenderer::depthFilter;

// Frame data
CMemStack						*CRenderer::frameMemory				=	NULL;
CTrie<CFileResource  *>			*CRenderer::frameFiles				=	NULL;
CArray<const char*>				*CRenderer::frameTemporaryFiles		=	NULL;
CShadingContext					**CRenderer::contexts				=	NULL;
int								CRenderer::numActiveThreads			=	0;
CTrie<CRemoteChannel *>			*CRenderer::declaredRemoteChannels	=	NULL;
CArray<CRemoteChannel *>		*CRenderer::remoteChannels			=	NULL;
CArray<CProgrammableShaderInstance*>		*CRenderer::dirtyInstances			=	NULL;
unsigned int					CRenderer::raytracingFlags			=	0;
CObject							*CRenderer::root					=	NULL;
CObject							*CRenderer::offendingObject			=	NULL;
matrix							CRenderer::fromWorld,CRenderer::toWorld;
vector							CRenderer::worldBmin,CRenderer::worldBmax;
CXform							*CRenderer::world					=	NULL;
matrix							CRenderer::fromNDC,CRenderer::toNDC;
matrix							CRenderer::fromRaster,CRenderer::toRaster;
matrix							CRenderer::fromScreen,CRenderer::toScreen;
matrix							CRenderer::worldToNDC;
unsigned int					CRenderer::hiderFlags;
int								CRenderer::numSamples;
int								CRenderer::numExtraSamples;
int								CRenderer::xPixels,CRenderer::yPixels;
unsigned int					CRenderer::additionalParameters;
float							CRenderer::pixelLeft,CRenderer::pixelRight,CRenderer::pixelTop,CRenderer::pixelBottom;
float							CRenderer::dydPixel,CRenderer::dxdPixel;
float							CRenderer::dPixeldx,CRenderer::dPixeldy;
float							CRenderer::dSampledx,CRenderer::dSampledy;
int								CRenderer::renderLeft,CRenderer::renderRight,CRenderer::renderTop,CRenderer::renderBottom;
int								CRenderer::xBuckets,CRenderer::yBuckets;
int								CRenderer::xBucketsMinusOne;
int								CRenderer::yBucketsMinusOne;
float							CRenderer::invBucketSampleWidth,CRenderer::invBucketSampleHeight;
int								CRenderer::metaXBuckets,CRenderer::metaYBuckets;
float							CRenderer::aperture;
float							CRenderer::imagePlane;
float							CRenderer::invImagePlane;
float							CRenderer::cocFactorPixels;
float							CRenderer::cocFactorSamples;
float							CRenderer::cocFactorScreen;
float							CRenderer::invFocaldistance;
float							CRenderer::lengthA,CRenderer::lengthB;

int								CRenderer::xSampleOffset,CRenderer::ySampleOffset;
float							CRenderer::sampleClipRight,CRenderer::sampleClipLeft,CRenderer::sampleClipTop,CRenderer::sampleClipBottom;
float							*CRenderer::pixelFilterKernel;

float							CRenderer::leftX,CRenderer::leftZ,CRenderer::leftD;
float							CRenderer::rightX,CRenderer::rightZ,CRenderer::rightD;
float							CRenderer::topY,CRenderer::topZ,CRenderer::topD;
float							CRenderer::bottomY,CRenderer::bottomZ,CRenderer::bottomD;
int								CRenderer::numActiveDisplays;
int								CRenderer::currentXBucket;
int								CRenderer::currentYBucket;
int								CRenderer::currentPhoton;
int								*CRenderer::jobAssignment;
FILE							*CRenderer::deepShadowFile			=	NULL;
int								*CRenderer::deepShadowIndex			=	NULL;
int								CRenderer::deepShadowIndexStart;
char							*CRenderer::deepShadowFileName		=	NULL;
int								CRenderer::numDisplays;
CRenderer::CDisplayData			*CRenderer::datas;
int								*CRenderer::sampleOrder;
float							*CRenderer::sampleDefaults;
int								CRenderer::numExtraChannels;	














///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	beginRenderer
// Description			:	Begin the renderer
// Return Value			:	-
// Comments				:
void		CRenderer::beginRenderer(CRendererContext *c,char *ribFile,char *riNetString) {
	float			startTime	=	osCPUTime();

	// Save the context
	context		=	c;

	// Reset the stats
	stats.reset();

	// Create the commit mutex (globally active)
	osCreateMutex(commitMutex);
	osCreateMutex(dispatchMutex);
	osCreateMutex(memoryMutex);
	osCreateMutex(networkMutex);
	osCreateMutex(hierarchyMutex);
	osCreateMutex(tesselateMutex);
	osCreateMutex(textureMutex);
	osCreateMutex(refCountMutex);
	osCreateMutex(shaderMutex);
	osCreateMutex(delayedMutex);

	// Init the memory
	memoryInit(globalMemory);

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

	// Create a temporary directory for the lifetime of the renderer

		
	// Make the temporary directory pid-unique in case we have more than one on a given host
#ifdef WIN32
	sprintf(temporaryPath,"PixieTemp_%d",GetCurrentProcessId());
#else
	sprintf(temporaryPath,"PixieTemp-%d",getpid());
#endif
	osFixSlashes(temporaryPath);

	// Good to rock and roll
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	endRenderer
// Description			:	End the renderer
// Return Value			:	-
// Comments				:
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

	// Delete the commit mutex (globally active)
	osDeleteMutex(commitMutex);
	osDeleteMutex(dispatchMutex);
	osDeleteMutex(memoryMutex);
	osDeleteMutex(networkMutex);
	osDeleteMutex(hierarchyMutex);
	osDeleteMutex(tesselateMutex);
	osDeleteMutex(textureMutex);
	osDeleteMutex(refCountMutex);
	osDeleteMutex(shaderMutex);
	osDeleteMutex(delayedMutex);

	// Turn off the memory manager
	memoryTini(globalMemory);

	// Check the stats for memory leaks
	stats.check();
}















///////////////////////////////////////////////////////////////////////
// Function				:	copyOptions
// Description			:	Make a local copy of the options
// Return Value			:	-
// Comments				:
static void	copyOptions(const COptions *o) {
	CRenderer::xres						=	o->xres;
	CRenderer::yres						=	o->yres;
	CRenderer::frame					=	o->frame;
	CRenderer::pixelAR					=	o->pixelAR;
	CRenderer::frameAR					=	o->frameAR;
	CRenderer::cropLeft					=	o->cropLeft;
	CRenderer::cropRight				=	o->cropRight;
	CRenderer::cropTop					=	o->cropTop;
	CRenderer::cropBottom				=	o->cropBottom;
	CRenderer::screenLeft				=	o->screenLeft;
	CRenderer::screenRight				=	o->screenRight;
	CRenderer::screenTop				=	o->screenTop;
	CRenderer::screenBottom				=	o->screenBottom;
	CRenderer::clipMin					=	o->clipMin;
	CRenderer::clipMax					=	o->clipMax;
	CRenderer::pixelVariance			=	o->pixelVariance;
	CRenderer::jitter					=	o->jitter;
	CRenderer::hider					=	o->hider;
	CRenderer::archivePath				=	o->archivePath;
	CRenderer::proceduralPath			=	o->proceduralPath;
	CRenderer::texturePath				=	o->texturePath;
	CRenderer::shaderPath				=	o->shaderPath;
	CRenderer::displayPath				=	o->displayPath;
	CRenderer::modulePath				=	o->modulePath;
	CRenderer::pixelXsamples			=	o->pixelXsamples;
	CRenderer::pixelYsamples			=	o->pixelYsamples;
	CRenderer::gamma					=	o->gamma;
	CRenderer::gain						=	o->gain;
	CRenderer::pixelFilterWidth			=	o->pixelFilterWidth;
	CRenderer::pixelFilterHeight		=	o->pixelFilterHeight;
	CRenderer::pixelFilter				=	o->pixelFilter;
	memcpy(CRenderer::colorQuantizer,o->colorQuantizer,5*sizeof(float));
	memcpy(CRenderer::depthQuantizer,o->depthQuantizer,5*sizeof(float));
	CRenderer::displays					=	o->displays;
	CRenderer::clipPlanes				=	o->clipPlanes;
	CRenderer::relativeDetail			=	o->relativeDetail;
	CRenderer::projection				=	o->projection;
	CRenderer::fov						=	o->fov;
	CRenderer::nColorComps				=	o->nColorComps;
	CRenderer::fromRGB					=	o->fromRGB;
	CRenderer::toRGB					=	o->toRGB;
	CRenderer::fstop					=	o->fstop;
	CRenderer::focallength				=	o->focallength;
	CRenderer::focaldistance			=	o->focaldistance;
	CRenderer::shutterOpen				=	o->shutterOpen;
	CRenderer::shutterClose				=	o->shutterClose;
	CRenderer::flags					=	o->flags;

	CRenderer::endofframe				=	o->endofframe;
	CRenderer::filelog					=	o->filelog;
	CRenderer::numThreads				=	o->numThreads;
	CRenderer::maxTextureSize			=	o->maxTextureSize;
	CRenderer::maxBrickSize				=	o->maxBrickSize;
	CRenderer::maxGridSize				=	o->maxGridSize;
	CRenderer::maxRayDepth				=	o->maxRayDepth;
	CRenderer::maxPhotonDepth			=	o->maxPhotonDepth;
	CRenderer::bucketWidth				=	o->bucketWidth;
	CRenderer::bucketHeight				=	o->bucketHeight;
	CRenderer::netXBuckets				=	o->netXBuckets;
	CRenderer::netYBuckets				=	o->netYBuckets;
	CRenderer::threadStride				=	o->threadStride;
	CRenderer::maxEyeSplits				=	o->maxEyeSplits;
	CRenderer::tsmThreshold				=	o->tsmThreshold;
	CRenderer::causticIn				=	o->causticIn;
	CRenderer::causticOut				=	o->causticOut;
	CRenderer::globalIn					=	o->globalIn;
	CRenderer::globalOut				=	o->globalOut;
	CRenderer::volumeIn					=	o->volumeIn;
	CRenderer::volumeOut				=	o->volumeOut;
	CRenderer::numEmitPhotons			=	o->numEmitPhotons;
	CRenderer::shootStep				=	o->shootStep;
	CRenderer::depthFilter				=	o->depthFilter;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	beginFrame
// Description			:	Begin a frame / compute misc data
// Return Value			:	-
// Comments				:
void		CRenderer::beginFrame(const COptions *o,CAttributes *a,CXform *x) {
	int		i;

	// Record the frame start time
	stats.frameStartTime	=	osCPUTime();

	// Allocate the frame zone
	frameMemory				=	new CMemStack(1000000);

	// Make a local copy of the options
	copyOptions(o);

	// This is the memory we allocate our junk from (only permenant stuff for the entire frame)
	frameFiles				=	new CTrie<CFileResource  *>;

	// Save the world xform
	world					=	x;
	world->attach();
	movmm(fromWorld,x->from);
	movmm(toWorld,x->to);

	assert(pixelXsamples > 0);
	assert(pixelYsamples > 0);

	// Compute some stuff
	if (flags & OPTIONS_FLAGS_CUSTOM_FRAMEAR) {
		const float	ar	=	xres*pixelAR / (float) yres;

		// Update the resolution as necessary
		if (frameAR > ar) {
			yres	=	(int) (xres*pixelAR / frameAR);
		} else {
			xres	=	(int) (frameAR * yres / pixelAR);
		}
	} else {
		frameAR = xres*pixelAR / (float) yres;
	}


	if (flags & OPTIONS_FLAGS_CUSTOM_SCREENWINDOW) {
		// The user explicitly entered the screen window, so we don't have to make sure it matches the frame aspect ratio
	} else {
		if (frameAR > (float) 1.0) {
			screenTop			=	(float) 1.0;
			screenBottom		=	(float) -1.0;
			screenLeft			=	-frameAR;
			screenRight			=	frameAR;
		} else {
			screenTop			=	1/frameAR;
			screenBottom		=	-1/frameAR;
			screenLeft			=	(float) -1.0;
			screenRight			=	(float) 1.0;
		}
	}

	// Compute the image plane depth
	imagePlane		=	1;
	if (projection == OPTIONS_PROJECTION_PERSPECTIVE) {
		imagePlane	=	(float) (1/tan(radians(fov/(float) 2)));
	} else {
		imagePlane	=	1;
	}
	invImagePlane	=	1/imagePlane;

	assert(cropLeft < cropRight);
	assert(cropTop < cropBottom);

	// Rendering window in pixels
	renderLeft			=	(int) ceil(xres*cropLeft);
	renderRight			=	(int) ceil(xres*cropRight);
	renderTop			=	(int) ceil(yres*cropTop);
	renderBottom		=	(int) ceil(yres*cropBottom);

	assert(renderRight > renderLeft);
	assert(renderBottom > renderTop);

	// The resolution of the actual render window
	xPixels				=	renderRight		-	renderLeft;
	yPixels				=	renderBottom	-	renderTop;

	assert(xPixels >= 0);
	assert(yPixels >= 0);

	// Compute various quantities about the rendering window
	dxdPixel			=	(screenRight	- screenLeft) / (float) (xres);
	dydPixel			=	(screenBottom	- screenTop) / (float) (yres);
	dPixeldx			=	1	/	dxdPixel;
	dPixeldy			=	1	/	dydPixel;
	dSampledx			=	dPixeldx*pixelXsamples;
	dSampledy			=	dPixeldy*pixelYsamples;
	pixelLeft			=	(float) (screenLeft	+ renderLeft*dxdPixel);
	pixelTop			=	(float) (screenTop	+ renderTop*dydPixel);
	pixelRight			=	pixelLeft	+ dxdPixel*xPixels;
	pixelBottom			=	pixelTop	+ dydPixel*yPixels;

	// Compute the inv bucket width and height in samples
	invBucketSampleWidth	=	1 / (float) (bucketWidth*pixelXsamples);
	invBucketSampleHeight	=	1 / (float) (bucketHeight*pixelYsamples);

	// Number of buckets to render
	xBuckets			=	(int) ceil(xPixels / (float) bucketWidth);
	yBuckets			=	(int) ceil(yPixels / (float) bucketHeight);
	xBucketsMinusOne	=	xBuckets-1;
	yBucketsMinusOne	=	yBuckets-1;

	// Number of meta buckets for net rendering
	metaXBuckets		=	(int) ceil(xBuckets / (float) netXBuckets);
	metaYBuckets		=	(int) ceil(yBuckets / (float) netYBuckets);

	// If we have servers, this array will hold the server assignment for each bucket
	jobAssignment		=	(int *) frameMemory->alloc(xBuckets*yBuckets*sizeof(int));

	// Create the job assignment
	for (i=0;i<xBuckets*yBuckets;i++)	jobAssignment[i]	=	-1;

	// Compute depth of field related stuff
	aperture			=	focallength / (2*fstop);
	if ((aperture <= C_EPSILON) || (projection == OPTIONS_PROJECTION_ORTHOGRAPHIC)) {
		aperture			=	0;
		cocFactorScreen		=	0;
		cocFactorSamples	=	0;
		cocFactorPixels		=	0;
		invFocaldistance	=	0;
	} else {
		cocFactorScreen		=	(float) (imagePlane*aperture*focaldistance /  (focaldistance + aperture));
		cocFactorSamples	=	cocFactorScreen*sqrtf(dPixeldx*dPixeldx*pixelXsamples*pixelXsamples + dPixeldy*dPixeldy*pixelYsamples*pixelYsamples);
		cocFactorPixels		=	cocFactorScreen*sqrtf(dPixeldx*dPixeldx + dPixeldy*dPixeldy);
		invFocaldistance	=	1 / focaldistance;
	}

	// Update the flags if we have depth of field / motion blur
	if (aperture		!= 0)			flags	|=	OPTIONS_FLAGS_FOCALBLUR;
	if (shutterClose	!= shutterOpen)	flags	|=	OPTIONS_FLAGS_MOTIONBLUR;

	// lengthA * z + lengthB gives the screen space radius of a unit sphere at depth = z
	if (projection == OPTIONS_PROJECTION_ORTHOGRAPHIC) {
		lengthA			=	0;
		lengthB			=	sqrtf(dxdPixel*dxdPixel + dydPixel*dydPixel);
	} else {
		lengthA			=	sqrtf(dxdPixel*dxdPixel + dydPixel*dydPixel) / imagePlane;
		lengthB			=	0;
	}	

	// Compute the matrices related to the camera transformation
	if (projection == OPTIONS_PROJECTION_PERSPECTIVE) {
		toNDC[element(0,0)]		=	imagePlane / (screenRight - screenLeft);
		toNDC[element(0,1)]		=	0;
		toNDC[element(0,2)]		=	-screenLeft / (screenRight - screenLeft);
		toNDC[element(0,3)]		=	0;

		toNDC[element(1,0)]		=	0;
		toNDC[element(1,1)]		=	imagePlane / (screenBottom - screenTop);
		toNDC[element(1,2)]		=	-screenTop / (screenBottom - screenTop);
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
		toNDC[element(0,0)]		=	1 / (screenRight - screenLeft);
		toNDC[element(0,1)]		=	0;
		toNDC[element(0,2)]		=	0;
		toNDC[element(0,3)]		=	-screenLeft / (screenRight - screenLeft);

		toNDC[element(1,0)]		=	0;
		toNDC[element(1,1)]		=	1 / (screenBottom - screenTop);
		toNDC[element(1,2)]		=	0;
		toNDC[element(1,3)]		=	-screenTop / (screenBottom - screenTop);

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
	fromNDC[element(0,0)]	=	(screenRight - screenLeft);
	fromNDC[element(0,1)]	=	0;
	fromNDC[element(0,2)]	=	0;
	fromNDC[element(0,3)]	=	screenLeft;

	fromNDC[element(1,0)]	=	0;
	fromNDC[element(1,1)]	=	(screenBottom - screenTop);
	fromNDC[element(1,2)]	=	0;
	fromNDC[element(1,3)]	=	screenTop;

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
	mtmp[element(0,0)]		=	(float) xres;
	mtmp[element(1,1)]		=	(float) yres;
	mulmm(toRaster,mtmp,toNDC);

	identitym(mtmp);
	mtmp[element(0,0)]		=	1 / (float) xres;
	mtmp[element(1,1)]		=	1 / (float) yres;
	mulmm(fromRaster,fromNDC,mtmp);

	// Compute the world to NDC transform required by the shadow maps
	mulmm(worldToNDC,toNDC,fromWorld);

	// Create a default display if not there
	if (displays == NULL) {
		displays				=	(COptions::CDisplay *) frameMemory->alloc(sizeof(COptions::CDisplay));
		displays->next			=	NULL;
		displays->outDevice		=	RI_FILE;
		displays->outName		=	"ri.tif";
		displays->outSamples	=	RI_RGBA;
	}

	// The sample offsets
	xSampleOffset		=	(int) ceil(max(	(CRenderer::pixelFilterWidth-1)*CRenderer::pixelXsamples  / 2.0 , 0));
	ySampleOffset		=	(int) ceil(max(	(CRenderer::pixelFilterHeight-1)*CRenderer::pixelYsamples / 2.0 , 0));

	// The clipping region we have
	sampleClipLeft		=	(float) (						-	xSampleOffset);
	sampleClipRight		=	(float) (xPixels*pixelXsamples	+	xSampleOffset);
	sampleClipTop		=	(float) (						-	ySampleOffset);
	sampleClipBottom	=	(float) (yPixels*pixelYsamples	+	ySampleOffset);

	// Set up the pixel filter kernel
	{
		const int		filterWidth				=	pixelXsamples + 2*xSampleOffset;
		const int		filterHeight			=	pixelYsamples + 2*ySampleOffset;
		const float		halfFilterWidth			=	(float) filterWidth / (float) 2;
		const float		halfFilterHeight		=	(float) filterHeight / (float) 2;

		// Allocate the pixel filter
		pixelFilterKernel = (float *) frameMemory->alloc(filterWidth*filterHeight*sizeof(float));
	
		// Evaluate the pixel filter, ignoring the jitter as it is apperently what other renderers do as well
		float	totalWeight	=	0;
		double	invWeight;
		int		sx,sy;

		// Evaluate the filter
		for (sy=0;sy<filterHeight;sy++) {
			for (sx=0;sx<filterWidth;sx++) {
				const float	cx				=	(sx - halfFilterWidth + 0.5f) / (float) pixelXsamples;
				const float	cy				=	(sy - halfFilterHeight + 0.5f) / (float) pixelYsamples;
				const float	filterResponse	=	pixelFilter(cx,cy,pixelFilterWidth,pixelFilterHeight);

				// Record
				pixelFilterKernel[sy*filterWidth + sx]		=	filterResponse;
				totalWeight									+=	filterResponse;
			}
		}

		// Normalize the filter kernel
		invWeight	=	1 / (double) totalWeight;
		for (i=0;i<filterWidth*filterHeight;i++) {
			pixelFilterKernel[i]			=	(float) (pixelFilterKernel[i] * invWeight);
		}
	}

	// The bucket we're rendering
	currentXBucket			=	0;
	currentYBucket			=	0;
	currentPhoton			=	0;
	
	// Initialize the extend of the world
	initv(worldBmin,C_INFINITY,C_INFINITY,C_INFINITY);
	initv(worldBmax,-C_INFINITY,-C_INFINITY,-C_INFINITY);

	// No dirty shader instances yet
	dirtyInstances			=	NULL;
	
	// These are the flags that objects need to have to be visible to raytracer
	raytracingFlags			=	ATTRIBUTES_FLAGS_PHOTON_VISIBLE			|
								ATTRIBUTES_FLAGS_TRACE_VISIBLE			|
								ATTRIBUTES_FLAGS_TRANSMISSION_VISIBLE;

	// Set the root object
	root					=	new CDummyObject(a,x);

	// Initialize remote channels
	remoteChannels			=	new CArray<CRemoteChannel*>;
	declaredRemoteChannels	=	new CTrie<CRemoteChannel*>;

	// Compute the clipping data
	beginClipping();

	// Start the displays
	beginDisplays();

	// Initialize the texturing
	textureSetMaxMemory(maxTextureSize);

	// Initialize the brickmaps
	CBrickMap::brickMapInit(maxBrickSize);

	if (netClient != INVALID_SOCKET) {
		// for now to keep things working, one thread only in each server
		// FIXME: remove this once the client server networking is threadable
		numThreads = 1;
	}
			
	// Start the contexts
	numActiveThreads	=	2;
	contexts			=	new CShadingContext*[numThreads];
	for (i=0;i<numThreads;i++) {

		// Start the hiders here
		contexts[i]	=	NULL;

		if (strcmp(hider,"raytrace") == 0) {
			contexts[i]						=	new CRaytracer(i);
			dispatchJob						=	dispatchReyes;
		} else if (strcmp(hider,"stochastic") == 0) {
			contexts[i]						=	new CStochastic(i);
			dispatchJob						=	dispatchReyes;
		} else if (strcmp(hider,"zbuffer") == 0) {
			contexts[i]						=	new CZbuffer(i);
			dispatchJob						=	dispatchReyes;
		} else if (strncmp(hider,"show:",5) == 0) {
			contexts[i]						=	new CShow(i);
			dispatchJob						=	dispatchReyes;
		} else if (strcmp(hider,"photon") == 0) {
			contexts[i]						=	new CPhotonHider(i,context->getAttributes(TRUE));
			dispatchJob						=	dispatchPhoton;
		} else {
			error(CODE_BADTOKEN,"Hider \"%s\" unavailable\n",hider);
			contexts[i]						=	new CStochastic(i);
			dispatchJob						=	dispatchReyes;
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
void		CRenderer::endFrame() {
	int	i;

	// Delete the contexts
	for (i=0;i<numThreads;i++)	{
		delete contexts[i];
	}
	delete [] contexts;

	assert(stats.numRasterGrids		== 0);
	assert(stats.numRasterObjects	== 0);

	// Delete the root object and it's children
	root->destroy();

	// Terminate the displays
	endDisplays();

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

	// Ditch the remote channels
	for (int i=0;i<remoteChannels->numItems;i++) {
		if (remoteChannels->array[i] != NULL) delete remoteChannels->array[i];
	}
	delete remoteChannels;
	delete declaredRemoteChannels;
	remoteChannels			=	NULL;
	declaredRemoteChannels	=	NULL;

	// Unload the files
	frameFiles->destroy();

	// Shutdown the texturing system
	CBrickMap::brickMapShutdown();

	// Release the world
	world->detach();
	world		=	NULL;

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

	// Ditch the frame memory
	delete frameMemory;
	frameMemory	=	NULL;

	// Print the stats (before we discard the memory)
	stats.frameTime		=	osCPUTime()		-	stats.frameStartTime;

	// Display the stats if applicable
	if (endofframe > 0)	stats.printStats(endofframe);
}






///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	render
// Description			:	Add an object into the scene
// Return Value			:
// Comments				:
void			CRenderer::render(CObject *cObject) {
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

	// Update the world bounding box
	addBox(worldBmin,worldBmax,cObject->bmin);
	addBox(worldBmin,worldBmax,cObject->bmax);

	// If the object is raytraced, add it into our hierarchy
	if (cObject->raytraced()) {
		cObject->attach();
		cObject->sibling	=	root->children;
		root->children		=	cObject;
	}

	// Only add to this first context, it will do the culling and add it to the rest of the threads
	contexts[0]->drawObject(cObject);
}
















///////////////////////////////////////////////////////////////////////
// Function				:	dispatcherThread
// Description			:	This thread is responsible for dispatching needed buckets
//							the servers
// Return Value			:
// Comments				:
static	void		*serverDispatchThread(void *w) {
	CRenderer::serverThread(w);

	return NULL;
}

///////////////////////////////////////////////////////////////////////
// Function				:	rendererThread
// Description			:	This thread is responsible for rendering
// Return Value			:
// Comments				:
static	void		*rendererDispatchThread(void *w) {
	CRenderer::contexts[(int) w]->renderingLoop();

	return NULL;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	renderFrame
// Description			:	Render the frame
// Return Value			:	-
// Comments				:
void		CRenderer::renderFrame() {

	// Make sure we have a bounding hierarchy
	movvv(root->bmin,worldBmin);
	movvv(root->bmax,worldBmax);
	root->setChildren(contexts[0],root->children);

	// Render the frame
	if (netNumServers != 0) {
		int				i;
		TThread			*threads;


		// Spawn the threads
		threads	=	(TThread *) alloca(netNumServers*sizeof(TThread));
		for (i=0;i<netNumServers;i++) {
			threads[i]	=	osCreateThread(serverDispatchThread,(void *) i);
		}

		// Go to sleep until we're done
		for (i=0;i<netNumServers;i++) {
			osWaitThread(threads[i]);
		}

		// Send the ready to the servers to prepare them for the next frame
		numNetrenderedBuckets = 0;
		for (i=0;i<netNumServers;i++) {
			T32	netBuffer;
			netBuffer.integer	=	NET_READY;
			rcSend(netServers[i],(char *) &netBuffer,sizeof(T32));
		}

	} else {
		int				i;
		TThread			*threads;

		// Let the client know that we're ready to render
		if (netClient != INVALID_SOCKET) {
			T32		netBuffer;

			netBuffer.integer	=	NET_READY;
			rcSend(netClient,(char *) &netBuffer,1*sizeof(T32));
		}
		
		// Spawn the threads
		threads	=	(TThread *) alloca(numThreads*sizeof(TThread));
		for (i=0;i<numThreads;i++) {
			threads[i]	=	osCreateThread(rendererDispatchThread,(void *) i);
		}

		// Go to sleep until we're done
		for (i=0;i<numThreads;i++) {
			osWaitThread(threads[i]);
		}
	}
}











































