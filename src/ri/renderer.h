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
//  File				:	renderer.h
//  Classes				:	CRenderer
//  Description			:	This class holds global info about the renderer
//
////////////////////////////////////////////////////////////////////////
#ifndef FRAME_H
#define FRAME_H

#include "common/global.h"
#include "common/containers.h"
#include "common/os.h"
#include "options.h"
#include "shadeop.h"
#include "memory.h"

// Compute the circle of confusion as a function of the depth
#define	cocPixels(z)	absf((1 / z) - CRenderer::invFocaldistance)*CRenderer::cocFactorPixels
#define	cocSamples(z)	absf((1 / z) - CRenderer::invFocaldistance)*CRenderer::cocFactorSamples
#define	cocScreen(z)	absf((1 / z) - CRenderer::invFocaldistance)*CRenderer::cocFactorScreen

// The following bits can be used by the hiders
const	unsigned	int	HIDER_RGBAZ_ONLY			=	1;	// The hider can only produce RGBAZ channels
const	unsigned	int	HIDER_BREAK					=	2;	// The hider should stop rendering
const	unsigned	int	HIDER_NODISPLAY				=	4;	// The hider is not actually generating display output
const	unsigned	int	HIDER_DONE					=	8;	// The image has been computed, so stop
const	unsigned	int	HIDER_ILLUMINATIONHOOK		=	16;	// The hider requires the illumination hooks
const	unsigned	int	HIDER_PHOTONMAP_OVERWRITE	=	32;	// Overwrite the photon maps
const	unsigned	int	HIDER_GEOMETRYHOOK			=	64;	// The hider requires the geometry hooks

// The clipping codes used by the clipcode()
const	unsigned	int	CLIP_LEFT					=	1;
const	unsigned	int	CLIP_RIGHT					=	2;
const	unsigned	int	CLIP_TOP					=	4;
const	unsigned	int	CLIP_BOTTOM					=	8;
const	unsigned	int	CLIP_NEAR					=	16;
const	unsigned	int	CLIP_FAR					=	32;

// Textual definitions of predefined coordinate systems
extern	const char	*coordinateCameraSystem;
extern	const char	*coordinateWorldSystem;
extern	const char	*coordinateObjectSystem;
extern	const char	*coordinateShaderSystem;
extern	const char	*coordinateLightSystem;
extern	const char	*coordinateNDCSystem;
extern	const char	*coordinateRasterSystem;
extern	const char	*coordinateScreenSystem;
extern	const char	*coordinateCurrentSystem;

// Textual definitions of the predefined color systems
extern	const char	*colorRgbSystem;
extern	const char	*colorHslSystem;
extern	const char	*colorHsvSystem;
extern	const char	*colorXyzSystem;
extern	const char	*colorYiqSystem;
extern	const char	*colorXyySystem;
extern	const char	*colorCieSystem;

// Forward definitions
class	CDisplayChannel;
class	CObject;
class	CTracable;
class	CRemoteChannel;
class	CAttributes;
class	CTriangle;
class	CMovingTriangle;
class	CTexture;
class	CEnvironment;
class	CSurface;
class	CPhotonMap;
class	CNamedCoordinateSystem;
class	CGlobalIdentifier;
class	CXform;
class	CDSO;
class	CRendererContext;
class	CNetFileMapping;
class	CRay;
class	CTextureBlock;
class	CTextureInfoBase;
class	CTexture3d;


///////////////////////////////////////////////////////////////////////
//
//     The implementation for this class is split into several files:
//
//		renderer.cpp			- Init / shutdown code
//		rendererMutexes.cpp		- The portion that holds the synchronization objects
//		rendererDeclarations	- The portion that deals with declarations such as variables/coordinate systems etc.
//		rendererDisplay			- The portion that handles the output
//		rendererFiles			- The portion that manages files and loads stuff
//		rendererNetwork			- The portion that manages the network
//		rendererClipping		- The portion that handles the clipping
//		rendererJob				- The portion that dispatches the rendering jobs to threads
//
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Description			:	This class holds data about the current frame being rendered
// Comments				:	This class is invalid outside beginFrame / endFrame
class CRenderer {
public:

		////////////////////////////////////////////////////////////////////
		//
		//	beginRenderer is called in RiBegin
		//	endRenderer is called in RiEnd
		//
		//  They pretty much do what you would expect
		// 
		////////////////////////////////////////////////////////////////////
		static void								beginRenderer(CRendererContext *context,const char *ribFile,const char *riNetString);
		static void								endRenderer();

								
		////////////////////////////////////////////////////////////////////
		//
		// Some global data structures that hang around between beginRenderer and endRenderer
		//
		////////////////////////////////////////////////////////////////////
		static	CMemPage						*globalMemory;				// The global memory stack
		static	CRendererContext				*context;					// The renderer context (RenderMan Interface)
		static	CArray<CShaderInstance *>		*allLights;					// An array of all allocated lights
		static	CTrie<CNamedCoordinateSystem *>	*definedCoordinateSystems;	// This holds the named coordinate systems defined for this context
		static	CTrie<CVariable *>				*declaredVariables;			// Declared variables
		static	CTrie<CFileResource  *>			*globalFiles;				// Files that have been loaded (they stick around for the entire rendering)
		static	CTrie<CGlobalIdentifier *>		*globalIdHash;				// This holds global string to id mappings (light categories for example)
		static	CTrie<CNetFileMapping *>		*netFileMappings;			// This holds name->name mappings of files
		static	int								numKnownGlobalIds;			// The current free global ID
		static	CVariable						*variables;					// List of all defined variables
		static	CArray<CVariable *>				*globalVariables;			// Array of global variables only
		static	CTrie<CDisplayChannel *>		*declaredChannels;			// The declared display channels
		static	CArray<CDisplayChannel*>		*displayChannels;			// The list of all desclared display channels
		static	CDSO							*dsos;						// The list of DSO's that have been loaded
		static	SOCKET							netClient;					// The client that we're serving (-1 if client)
		static	int								netNumServers;				// The number of servers (0 if server)
		static	SOCKET							*netServers;				// The array of servers that are serving us		
		static	int								numRenderedBuckets;			// The number of rendered buckets
		static	char							temporaryPath[OS_MAX_PATH_LENGTH];	// Where tmp files are stored
		static	int								**textureRefNumber;			// The last reference number for each thread's textures
		static	CTextureBlock					*textureUsedBlocks;			// All texture blocks currently in use
		static	int								*textureUsedMemory;			// The amount of texture memory in use for each thread
		static	int								*textureMaxMemory;			// The maximum texture memory for each thread


		////////////////////////////////////////////////////////////////////
		//
		// Synchronization objects ...
		//
		//    Even though some of them are mainly used between WorldBegin - WorldEnd, 
		//    we're defining them as global
		//
		////////////////////////////////////////////////////////////////////
		static	TMutex							jobMutex;					// The mutex that controls job dispatch
		static	TMutex							commitMutex;				// The mutex that controls job dispatch
		static	TMutex							displayKillMutex;			// To serialize the killing of a thread
		static	TMutex							networkMutex;				// To serialize the network communication
		static	TMutex							tesselateMutex;				// To serialize the tesselation
		static	TMutex							textureMutex;				// To serialize texture fetches
		static	TMutex							shaderMutex;				// To serialize shader parameter list access
		static	TMutex							delayedMutex;				// To serialize rib parsing/delayed objects
		static	TMutex							deepShadowMutex;			// To serialize deep shadow _writes_
		static	TMutex							hierarchyMutex;				// To serialize lazy construction of bounding volume hierarchy
		static	TMutex							atomicMutex;				// To serialize atomic operations on unsupported platforms
		
		////////////////////////////////////////////////////////////////////
		//
		// Here's how the rendering loop works:
		//
		//		beginFrame is called in WorldBegin
		//		renderFrame is called in WorldEnd to do the rendering
		//		endFrame is called in WorldEnd to do the cleaning up
		//
		// Between these functions, objects can be added to the scene using
		//		render
		//
		// During rendering (in renderFrame), hiders can ask for a job using
		//		getJob
		//
		////////////////////////////////////////////////////////////////////
		static	void			beginFrame(const COptions *options,CAttributes *attributes,CXform *xform);		// Called in WorldBegin
		static	void			endFrame();														// Called in WorldEnd
		static	void			renderFrame();													// Called in WorldEnd
		static	void			render(CObject *object);										// Called to insert an object into the scene

		////////////////////////////////////////////////////////////////////
		// Functions that deal with thread synthronication (defined in rendererMutexes.cpp)
		////////////////////////////////////////////////////////////////////
		static	void			initMutexes();
		static	void			shutdownMutexes();


		////////////////////////////////////////////////////////////////////
		// Functions that deal with rendering (defined in rendererJobs.cpp)
		////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////
		// Class				:	CJob
		// Description			:	This class keeps track of a job to perform
		// Comments				:
		class	CJob {
		public:
			enum {	BUCKET,					// Render a bucket
					NETWORK_BUCKET,			// Render a bucket from network
					PHOTON_BUNDLE,			// Trace a photon bundle
					NETWORK_PHOTON_BUNDLE,	// Trace a photon bundle from network
					TERMINATE				// Terminate/cleanup the shading context
				}	type;

			int			xBucket,yBucket;	// For a bucket job, the bucket to render
			int			numPhotons;			// For a photon job, the number of photons to emit
		};

		static void				(*dispatchJob)(int thread,CJob &job);				// This function is used by the hiders to ask for a job

		static void				serverThread(void *w);								// Clients run a separate thread for each server. This is the entry point for those client side threads
		static void				processServerRequest(T32 req,int index);			// This function is used to serve the client requests
		static void				dispatchReyes(int thread,CJob &job);				// This function dispatches single threaded buckets
		static void				dispatchPhoton(int thread,CJob &job);				// This function dispatches single threaded photon bundles

		////////////////////////////////////////////////////////////////////
		// Functions that deal with the clipping/projection (defined in rendererClipping.cpp)
		////////////////////////////////////////////////////////////////////
		static void				beginClipping();									// Compute the various quantities that have to do with clipping
		static int				inFrustrum(const float *,const float *);			// Return TRUE if the box is in the frustrum
		static int				inFrustrum(const float *);							// Return TRUE if the point is in the frustrum
		static unsigned int		clipCode(const float *);							// Returns the clipping code

		////////////////////////////////////////////////////////////////////
		// Functions that deal with the displays (implemented in rendererDisplay.cpp)
		////////////////////////////////////////////////////////////////////
		static void				beginDisplays();									// Init the displays
		static void				commit(int,int,int,int,float *);					// Send a chunk of computed framebuffer to the display drivers
		static int				advanceBucket(int,int &,int &);						// Find the next bucket to render for network rendering
		static void				clear(int,int,int,int);								// Clear a window
		static void				dispatch(int,int,int,int,float *);					// Dispatch a window to out devices
		static void				getDisplayName(char *,const char *,const char *);	// Retrieve the display name
		static void				endDisplays();										// Shutdown the displays
		static RtFilterFunc		getFilter(const char *);							// Get a filter
		static RtStepFilterFunc	getStepFilter(const char *);						// Get a filter

		////////////////////////////////////////////////////////////////////
		// Functions that deal with declarations (implemented in rendererDeclarations.cpp)
		////////////////////////////////////////////////////////////////////
		static	void			initDeclarations();
		static	void			defineCoordinateSystem(const char *,const float *,const float *,ECoordinateSystem type = COORDINATE_CUSTOM);
		static	int				findCoordinateSystem(const char *,const float *&,const float *&,ECoordinateSystem &);
		static	CVariable		*declareVariable(const char *,const char *,int um = 0);
		static	void			makeGlobalVariable(CVariable *);
		static	CVariable		*retrieveVariable(const char *);
		static	CDisplayChannel	*declareDisplayChannel(const char *);				// Display channel management
		static	CDisplayChannel	*declareDisplayChannel(CVariable *);
		static	CDisplayChannel	*retrieveDisplayChannel(const char *);
		static	void			resetDisplayChannelUsage();
		static	void			registerFrameTemporary(const char *,int);			// Register file for end-of-frame deletion
		static	int				getGlobalID(const char *);							// Global ID management
		static	void			shutdownDeclarations();
								
		////////////////////////////////////////////////////////////////////
		// Functions that deal with files (implemented in rendererFiles.cpp)
		////////////////////////////////////////////////////////////////////
		static	void			initFiles();
		static	int				locateFileEx(char *,const char *,const char *extension=NULL,TSearchpath *search=NULL);
		static	int				locateFile(char *,const char *,TSearchpath *search=NULL);
		
		static	void			initTextures(int);										// Set the maximum texture memory and init texturing		
		static	CTexture		*textureLoad(const char *,TSearchpath *);				// Load a new texture map
		static	CEnvironment	*environmentLoad(const char *,TSearchpath *,float *);	// Load a new environment map
		static	CTexture		*getTexture(const char *);								// Load a texture
		static	CEnvironment	*getEnvironment(const char *);							// Load an environment
		static	CPhotonMap		*getPhotonMap(const char *);							// Load a photon map
		static	CTexture3d		*getCache(const char *,const char *,const float *,const float *);							// Load a cache
		static	CTextureInfoBase *getTextureInfo(const char *);							// Load a textureinfo
		static	CTexture3d		*getTexture3d(const char*,int,const char*,const float*,const float *,int hierarchy=FALSE);	// Load a point cloud or brickmap
		static	CShader			*getShader(const char *,TSearchpath *search=NULL);		// Load a shader
		static	int				getAOVFilter(const char *name);							// Get an AOV filter name
		static	const char		*getFilter(RtFilterFunc);								// The other way around
		static	CDSO			*getDSO(const char *,const char *);						// Find a DSO function
		static	void			shutdownFiles();
		static	void			shutdownTextures();										// clean up texturing


		////////////////////////////////////////////////////////////////////
		// Functions that deal with network (implemented in rendererNetwork.cpp)
		////////////////////////////////////////////////////////////////////
		static	void			initNetwork(const char *ribFile,const char *riNetString);// Initiate misc network functionality
		static	void			netSetup(const char *,const char *);					// Setup the network for rendering
		static	void			sendFile(int,char *,int,int);							// Send a particular file
		static	int				getFile(char *,const char *);							// Get a particular file from network
		static	int				getFile(FILE *,const char *,int start=0,int size=0);	// Get a particular file from network
		static	void			shutdownNetwork();										// Shutdown the network

		////////////////////////////////////////////////////////////////////
		// Remote channel stuff (in remoteChannel.cpp)
		////////////////////////////////////////////////////////////////////
		static	int				requestRemoteChannel(CRemoteChannel *);					// request a remote channel (server requests from client)
		static	int				processChannelRequest(int,SOCKET);						// service request for a remote channel in client
		static	void			sendBucketDataChannels(int x,int y);					// send all per-bucket remote channels
		static	void			recvBucketDataChannels(SOCKET s,int x,int y);			// receive one per-bucket remote channel
		static	void			sendFrameDataChannels();								// send all per-frame remote channels
		static	void			recvFrameDataChannels(SOCKET s);						// receive one per-frame remote channel

		





		////////////////////////////////////////////////////////////////////
		//
		//    Data structures only valid between WorldBegin - WorldEnd
		//
		////////////////////////////////////////////////////////////////////


		// First a copy of the options we're using for the frame
		static	int						xres,yres;										// Output resolution
		static	int						frame;											// The frame number given by frameBegin
		static	float					pixelAR;										// Pixel aspect ratio
		static	float					frameAR;										// Frame aspect ratio
		static	float					cropLeft,cropRight,cropTop,cropBottom;			// The crop window
		static	float					screenLeft,screenRight,screenTop,screenBottom;	// The screen window
		static	float					clipMin,clipMax;								// Clipping bounds
		static	float					pixelVariance;									// The maximum tolerable pixel color variation
		static	float					jitter;											// Amount of jitter in samples
		static	char					*hider;											// Hider name
		static	TSearchpath				*archivePath;									// RIB search path
		static	TSearchpath				*proceduralPath;								// Procedural primitive search path
		static	TSearchpath				*texturePath;									// Texture search path
		static	TSearchpath				*shaderPath;									// Shader search path
		static	TSearchpath				*displayPath;									// Display search path
		static	TSearchpath				*modulePath;									// Search path for Pixie modules
		static	int						pixelXsamples,pixelYsamples;					// Number of samples to take in X and Y
		static	float					gamma,gain;										// Gamma correction stuff
		static	float					pixelFilterWidth,pixelFilterHeight;				// Pixel filter data
		static	RtFilterFunc			pixelFilter;
		static	float					colorQuantizer[5];								// The quantization data
		static	float					depthQuantizer[5];
		static	vector					opacityThreshold;								// The opacity threshold
		static	vector					zvisibilityThreshold;							// The point at which samples are visible in z and noncomp aovs
		static	COptions::CDisplay		*displays;										// List of displays to send the output
		static	COptions::CClipPlane	*clipPlanes;									// List of used defined clipping planes
		static	float					relativeDetail;									// The relative detail multiplier
		static	EProjectionType			projection;										// Projection type
		static	float					fov;											// Field of view for perspective projection
		static	int						nColorComps;									// Custom color space stuff
		static	float					*fromRGB,*toRGB;
		static	float					fstop,focallength,focaldistance;				// Depth of field stuff
		static	float					shutterOpen,shutterClose;						// Motion blur stuff
		static	float					shutterTime,invShutterTime;						// More motion stuff
		static	unsigned int			flags;											// Flags	
		static	int						endofframe;										// The end of frame statstics number
		static	char					*filelog;										// The name of the log file
		static	int						numThreads;										// The number of threads working
		static	int						maxTextureSize;									// Maximum amount of texture data to keep in memory (in bytes)
		static	int						maxBrickSize;									// Maximum amount of brick data to keep in memory (in bytes)
		static	int						maxGridSize;									// Maximum number of points to shade at a time
		static	int						maxRayDepth;									// Maximum raytracing recursion depth
		static	int						maxPhotonDepth;									// The maximum number of photon bounces
		static	int						bucketWidth,bucketHeight;						// Bucket dimentions in samples
		static	int						netXBuckets,netYBuckets;						// The meta bucket size
		static	int						threadStride;									// The number of buckets per thread at a time
		static	int						geoCacheSize;									// The ammount of memory to dedicate to tesselation caches
		static	int						maxEyeSplits;									// Maximum number of eye splits
		static	float					tsmThreshold;									// Transparency shadow map threshold
		static	char					*causticIn,*causticOut;							// The caustics in/out file name
		static	char					*globalIn,*globalOut;							// The global photon map 
		static	char					*volumeIn,*volumeOut;							// The volume photon map 
		static	int						numEmitPhotons;									// The number of photons to emit for the scene
		static	int						shootStep;										// The number of rays to shoot at a time
		static	EDepthFilter			depthFilter;									// Holds the depth filter type


		// Second, some other data structures
		static	TMemCheckpoint			frameCheckpoint;			// A checkpoint in the global memory
		static	CTrie<CFileResource  *>	*frameFiles;				// Files that have been loaded (they stick around only during the frame)
		static	CArray<const char*>		*frameTemporaryFiles;		// This hold the name of temporary files
		static	CShadingContext			**contexts;					// The array of shading contexts
		static	int						numActiveThreads;			// The number of threads currently active
		static	CTrie<CRemoteChannel *>	*declaredRemoteChannels;	// Known remote channel lookup
		static	CArray<CRemoteChannel *>	*remoteChannels;		// all known channels
		static	unsigned int			raytracingFlags;			// The raytracing flags that hold the combination that needs to be raytraced
		static	CObject					*root;						// The root bounding volume object
		static	CObject					*offendingObject;			// This points to the object creating an error
		static	vector					worldBmin,worldBmax;		// The bounding box of the world
		static	CXform					*world;						// The world xform
		static	matrix					fromWorld,toWorld;			// Some misc matrices
		static	matrix					fromNDC,toNDC;
		static	matrix					fromRaster,toRaster;
		static	matrix					fromScreen,toScreen;
		static	matrix					worldToNDC;					// World to NDC matrix
		static	unsigned int			hiderFlags;					// The hider flags
		static	int						numSamples;					// The actual number of samples to compute
		static	int						numExtraSamples;			// The number of actual samples
		static	int						xPixels,yPixels;			// The number of pixels to compute in X and Y
		static	unsigned int			additionalParameters;		// Any user specified parameters to be computed
		static	float					pixelLeft,pixelRight,pixelTop,pixelBottom;		// The rendering window on the screen plane
		static	float					dydPixel,dxdPixel;			// Stuff
		static	float					dPixeldx,dPixeldy;			// dPixel / dx, dPixel / dy
		static	float					dSampledx,dSampledy;		// dSample / dx, dSample / dy
		static	int						renderLeft,renderRight,renderTop,renderBottom;					// The actual rendering window in pixels
		static	int						xBuckets,yBuckets;			// The number of buckets
		static	int						xBucketsMinusOne;			// Obvious ?
		static	int						yBucketsMinusOne;
		static	float					invBucketSampleWidth,invBucketSampleHeight;		// The 1 / sample
		static	int						metaXBuckets,metaYBuckets;						// The number of meta buckets in X and Y
		static	float					aperture;					// Aperture radius
		static	float					imagePlane;					// The z coordinate of the image plane
		static	float					invImagePlane;				// The reciprocal of that
		static	float					cocFactorPixels;			// The circle of concusion factor for the pixels
		static	float					cocFactorSamples;			// The circle of concusion factor for the samples
		static	float					cocFactorScreen;			// The circle of concusion factor for the screen
		static	float					invFocaldistance;			// 1 / focalDistance
		static	float					lengthA,lengthB;			// The depth to length conversion

		static	int						xSampleOffset,ySampleOffset;// The amount of offset around each bucket in samples
		static	float					sampleClipRight,sampleClipLeft,sampleClipTop,sampleClipBottom;	// The actual rendering window in samples
		static	float					*pixelFilterKernel;			// The precomputed pixel filter kernel

		static	float					leftX,leftZ,leftD;			// The clipping plane equations
		static	float					rightX,rightZ,rightD;
		static	float					topY,topZ,topD;
		static	float					bottomY,bottomZ,bottomD;
		static	int						numActiveDisplays;			// The number of active displays
		static	int						currentXBucket;				// The bucket counters
		static	int						currentYBucket;
		static	int						currentPhoton;				// The current photon counter for the photon mapping
		static	int						*jobAssignment;				// The job assignment for the buckets
		static	FILE					*deepShadowFile;			// Deep shadow map stuff
		static	int						*deepShadowIndex;
		static	int						deepShadowIndexStart;		// The offset in the file for the indices
		static	char					*deepShadowFileName;
		
		static	const CUserAttributeDictionary	*userOptions;

		///////////////////////////////////////////////////////////////////////
		// Class				:	CDisplayData
		// Description			:	This class holds data about a display driver
		// Comments				:
		class CDisplayData {
		public:
				void						*module;				// The module handle for the out device
				void						*handle;				// The handle for the out device
				int							numSamples;				// The number of samples
				CDisplayChannel				*channels;
				int							numChannels;
				char						*displayName;			// The computed display name
				TDisplayStartFunction		start;					// The start function for the out device
				TDisplayDataFunction		data;					// The data function
				TDisplayRawDataFunction		rawData;				// The raw data function
				TDisplayFinishFunction		finish;					// The finish function
				COptions::CDisplay			*display;				// The display corresponding to this display
		};

		static	int							numDisplays;
		static	CDisplayData				*datas;
		static	int							*sampleOrder;			// variable entry, sample count pairs
		static	float						*sampleDefaults;		// default values for each channel
		static	int							*compChannelOrder;		// channels which need compositing
		static	int							numExtraCompChannels;	// number of channels which need compositing
		static	int							*nonCompChannelOrder;	// channels which do not need compositing
		static	int							numExtraNonCompChannels;// number of channels which do not need compositing

		static	int							numExtraChannels;	


		static	void						computeDisplayData();
};


// These two are defined in frameNetwork.cpp and can be used to send/receive data over network
void			rcSend(SOCKET,const void *,int,int net = TRUE);		// Send data
void			rcRecv(SOCKET,void *,int,int net = TRUE);			// Recv data




////////////////////////////////////////////////////////////////////
// Some inline functions defined below for efficiency
////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////
// Function				:	camera2pixels
// Description			:	Project from camera space into the pixel space
// Return Value			:
// Comments				:	(inline for speed)
inline void		camera2pixels(float *P) {
	if(CRenderer::projection == OPTIONS_PROJECTION_PERSPECTIVE) {
		P[COMP_X]	=	CRenderer::imagePlane*P[COMP_X]/P[COMP_Z];
		P[COMP_Y]	=	CRenderer::imagePlane*P[COMP_Y]/P[COMP_Z];
	}

	P[COMP_X]	=	(P[COMP_X] - CRenderer::pixelLeft)*CRenderer::dPixeldx;
	P[COMP_Y]	=	(P[COMP_Y] - CRenderer::pixelTop)*CRenderer::dPixeldy;
}

///////////////////////////////////////////////////////////////////////
// Function				:	camera2pixels
// Description			:	Project from camera space into the pixel space
// Return Value			:
// Comments				:	(inline for speed)
inline void		camera2pixels(float *x,float *y,const float *P) {
	if(CRenderer::projection == OPTIONS_PROJECTION_PERSPECTIVE) {
		x[0]	=	CRenderer::imagePlane*P[COMP_X]/P[COMP_Z];
		y[0]	=	CRenderer::imagePlane*P[COMP_Y]/P[COMP_Z];
	} else {
		x[0]	=	P[COMP_X];
		y[0]	=	P[COMP_Y];
	}

	x[0]	=	(x[0] - CRenderer::pixelLeft)*CRenderer::dPixeldx;
	y[0]	=	(y[0] - CRenderer::pixelTop)*CRenderer::dPixeldy;
}

///////////////////////////////////////////////////////////////////////
// Function				:	camera2pixels
// Description			:	Project from camera space into the pixel space
// Return Value			:
// Comments				:	(inline for speed)
inline void		camera2pixels(int n,float *P) {
	if(CRenderer::projection == OPTIONS_PROJECTION_PERSPECTIVE) {
		for (;n>0;n--,P+=3) {
			P[COMP_X]	=	(CRenderer::imagePlane*P[COMP_X]/P[COMP_Z] - CRenderer::pixelLeft)*CRenderer::dPixeldx;
			P[COMP_Y]	=	(CRenderer::imagePlane*P[COMP_Y]/P[COMP_Z] - CRenderer::pixelTop)*CRenderer::dPixeldy;
		}
	} else {
		for (;n>0;n--,P+=3) {
			P[COMP_X]	=	(P[COMP_X] - CRenderer::pixelLeft)*CRenderer::dPixeldx;
			P[COMP_Y]	=	(P[COMP_Y] - CRenderer::pixelTop)*CRenderer::dPixeldy;
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	camera2screen
// Description			:	Project from camera space into the screen space
// Return Value			:
// Comments				:	(inline for speed)
inline void		camera2screen(int n,float *P) {
	if(CRenderer::projection == OPTIONS_PROJECTION_PERSPECTIVE) {
		for (;n>0;n--,P+=3) {
			P[COMP_X]	=	(CRenderer::imagePlane*P[COMP_X]/P[COMP_Z] - CRenderer::pixelLeft);
			P[COMP_Y]	=	(CRenderer::imagePlane*P[COMP_Y]/P[COMP_Z] - CRenderer::pixelTop);
		}
	} else {
		for (;n>0;n--,P+=3) {
			P[COMP_X]	=	(P[COMP_X] - CRenderer::pixelLeft);
			P[COMP_Y]	=	(P[COMP_Y] - CRenderer::pixelTop);
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	distance2pixels
// Description			:	Project a distance in camera space into a distance in the pixel space
// Return Value			:
// Comments				:	(inline for speed)
inline void		distance2pixels(int n,float *dist,float *P) {
	if(CRenderer::projection == OPTIONS_PROJECTION_PERSPECTIVE) {
		for (;n>0;n--,P+=3) {
			*dist++		=	CRenderer::dPixeldx*CRenderer::imagePlane*dist[0]/P[COMP_Z];
		}
	} else {
		for (;n>0;n--,P+=3) {
			*dist++		=	CRenderer::dPixeldx*dist[0];
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	pixels2distance
// Description			:	Convert from pixel distance to camera space distance
// Return Value			:	-
// Comments				:
inline void			pixels2distance(float &a,float &b,float d) {
	a	=	CRenderer::lengthA*d;
	b	=	CRenderer::lengthB*d;
}

///////////////////////////////////////////////////////////////////////
// Function				:	samples2camera
// Description			:	Back project from sample space into the camera space
// Return Value			:
// Comments				:	(inline for speed)
inline void		pixels2camera(float *P,float x,float y,float z) {
	x	=	x*CRenderer::dxdPixel + CRenderer::pixelLeft;
	y	=	y*CRenderer::dydPixel + CRenderer::pixelTop;

	if(CRenderer::projection == OPTIONS_PROJECTION_PERSPECTIVE) {
		P[COMP_X]	=	x*z*CRenderer::invImagePlane;
		P[COMP_Y]	=	y*z*CRenderer::invImagePlane;
		P[COMP_Z]	=	z;
	} else {
		P[COMP_X]	=	x;
		P[COMP_Y]	=	y;
		P[COMP_Z]	=	z;
	}
}



////////////////////////////////////////////////////////////////////
// Some misc data structures
////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////
// Class				:	CNamedCoordinateSystem
// Description			:	Holds a coordinate system
// Comments				:
class  CNamedCoordinateSystem {
public:
	char				name[64];		// Name of the coordinate system
	ECoordinateSystem	systemType;		// If the system is one of the standard ones
	matrix				from;			// The transformation
	matrix				to;
};


///////////////////////////////////////////////////////////////////////
// Class				:	CDSO
// Description			:	Holds a DSO shader info
// Comments				:
class	CDSO {
public:
	void				*handle;		// The handle to the module that implements the DSO shader
	dsoInitFunction		init;			// Init function
	dsoExecFunction		exec;			// Execute function
	dsoCleanupFunction	cleanup;		// Cleanup function
	char				*name;			// Name of the DSO shader
	char				*prototype;		// Prototype of the DSO shader
	CDSO				*next;
};



#endif

