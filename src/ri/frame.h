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
//  File				:	frame.h
//  Classes				:	CFrame
//  Description			:	This class holds global info about a frame
//
////////////////////////////////////////////////////////////////////////
#ifndef FRAME_H
#define FRAME_H

#include "common/global.h"
#include "common/containers.h"
#include "common/os.h"
#include "options.h"
#include "shadeop.h"

// Compute the circle of confusion in the camera system
#define	cocPixels(z)	absf((1 / z) - invFocaldistance)*cocFactorPixels
#define	cocSamples(z)	absf((1 / z) - invFocaldistance)*cocFactorSamples
#define	cocScreen(z)	absf((1 / z) - invFocaldistance)*cocFactorScreen

const	unsigned	int	HIDER_RGBAZ_ONLY			=	1;	// The hider can only produce RGBAZ channels
const	unsigned	int	HIDER_NEEDS_RAYTRACING		=	2;	// The hider requires raytracing
const	unsigned	int	HIDER_BREAK					=	4;	// The hider should stop rendering
const	unsigned	int	HIDER_NODISPLAY				=	8;	// The hider is not actually generating display output
const	unsigned	int	HIDER_DONE					=	16;	// The image has been computed, so stop
const	unsigned	int	HIDER_ILLUMINATIONHOOK		=	32;	// The hider requires the illumination hooks
const	unsigned	int	HIDER_PHOTONMAP_OVERWRITE	=	64;	// Overwrite the photon maps
const	unsigned	int	HIDER_GEOMETRYHOOK			=	128;// The hider requires the geometry hooks

// The clipping codes used by the clipcode()
const	unsigned	int	CLIP_LEFT					=	1;
const	unsigned	int	CLIP_RIGHT					=	2;
const	unsigned	int	CLIP_TOP					=	4;
const	unsigned	int	CLIP_BOTTOM					=	8;
const	unsigned	int	CLIP_NEAR					=	16;
const	unsigned	int	CLIP_FAR					=	32;

// Forward definitions
class	CDisplayChannel;
class	CHierarchy;
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
class	CCache;
class	CNamedCoordinateSystem;
class	CGlobalIdentifier;
class	CXform;
class	CDSO;


///////////////////////////////////////////////////////////////////////
//
//     The implementation for this class is split into several files:
//
//		frame.cpp			- Init / shutdown code
//		frameDeclerations	- The portion that deals with declerations such as variables/coordinate systems etc.
//		frameDisplay		- The portion that handles the output
//		frameFiles			- The portion that manages files and loads stuff
//
///////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Description			:	This class holds data about the current frame being rendered
// Comments				:	This class is invalid outside beginFrame / endFrame
// Date last edited		:	10/10/2006
class CFrame : public COptions {

		///////////////////////////////////////////////////////////////////////
		// Class				:	CNetFileMapping
		// Description			:	maps files to alternate pats
		// Return Value			:
		// Comments				:
		// Date last edited		:	02/25/2006
		class CNetFileMapping{
		public:
			CNetFileMapping(const char *from,const char *to) {
				this->from	= strdup(from);
				this->to	= strdup(to);
			}
			~CNetFileMapping() {
				free(from);
				free(to);
			}
			
			char *from,*to;
		};

public:
		



		////////////////////////////////////////////////////////////////////
		//
		//   Globally active data / functions
		//
		////////////////////////////////////////////////////////////////////
		static void				beginRenderer(char *ribFile,char *riNetString);
		static void				endRenderer();

								
								////////////////////////////////////////////////////////////////////
								// Some global data structures
								////////////////////////////////////////////////////////////////////
		static	CArray<CShaderInstance *>							*allLights;					// An array of all allocated lights in the options context
		static	CDictionary<const char *,CNamedCoordinateSystem *>	*definedCoordinateSystems;	// This holds the named coordinate systems defined for this context
		static	CDictionary<const char *,CVariable *>				*declaredVariables;			// Declared variables
		static	CDictionary<const char *,CFileResource  *>			*loadedFiles;				// Files that have been loaded
		static	CDictionary<const char *,CGlobalIdentifier *>		*globalIdHash;				// This holds global string to id mappings (light categories for example)
		static	CDictionary<const char *,CNetFileMapping *>			*netFileMappings;			// This holds name->name mappings of files
		static	int													numKnownGlobalIds;
		static	CVariable											*variables;					// List of all defined variables
		static	CArray<CVariable *>									*globalVariables;			// Array of global variables only
		static	CDictionary<const char *,CDisplayChannel *>			*declaredChannels;			// The declared display channels
		static	CArray<CDisplayChannel*>							*displayChannels;			// The list of all desclared display channels
		static	CArray<CArray<CObject *> *>							*allocatedInstances;		// The list of allocated object instances
		static	CDSO												*dsos;						// The list of DSO's that have been loaded
		static	SOCKET												netClient;					// The client that we're serving (-1 if client)
		static	int													netNumServers;				// The number of servers (0 if server)
		static	SOCKET												*netServers;				// The array of servers that are serving us
		static	TMutex												commitMutex;				// The mutex that controls job dispatch
		static	int													userRaytracing;				// TRUE if we're raytracing for the user
		static	int													numNetrenderedBuckets;		// The number of netrendered buckets






		////////////////////////////////////////////////////////////////////
		//
		//   The following data / functions is only valid when rendering a frame
		//
		////////////////////////////////////////////////////////////////////
		static	void			beginFrame(const COptions *options,CXform *xform,SOCKET client,unsigned int hiderFlags);	// Called in WorldBegin
		static	void			render(CShadingContext *context,CObject *object,const float *bmin,const float *bmax);	// Called to insert an object into the scene
		static	void			removeTracable(CTracable *);																	// Called to remove a delayed object from the scene
		static	void			addTracable(CTracable *,CSurface *);				// Add a raytracable object into the scene
		static	void			addTracable(CTriangle *,CSurface *);
		static	void			addTracable(CMovingTriangle *,CSurface *);
		static	void			prepareFrame();																				// Called in WorldEnd
		static	int				getJob(int &xBucket,int &yBucket,int thread);
		static	void			endFrame();																					// Called in WorldEnd

								////////////////////////////////////////////////////////////////////
								//
								// Here's how the rendering loop works:
								//
								//		beginFrame is called in WorldBegin
								//		endFrame is called in WorldEnd and renders the frame
								//
								// Between these functions, objects can be added to the scene using
								//		render
								//
								// If raytracing is on, objects may need to be tesselated. In this case
								//		tesselate
								// function of CObject will be called in
								//		render
								// which may subsequently call
								//		addTracable or removeTracable
								// When the tesselation is done,
								//		prepareFrame
								// must be called to incorporate tesselated objects into the raytracing hierarchy
								//
								// During rendering (initiated in endFrame), hiders can ask for a job using
								//		getJob
								//
								////////////////////////////////////////////////////////////////////


								

								////////////////////////////////////////////////////////////////////
								// Functions that deal with the clipping/projection
								////////////////////////////////////////////////////////////////////
		static int				inFrustrum(const float *,const float *);			// Return TRUE if the box is in the frustrum
		static int				inFrustrum(const float *);							// Return TRUE if the point is in the frustrum
		static unsigned int		clipCode(const float *);							// Returns the clipping code

								// Some inline functions defined below
		static void				camera2pixels(float *P);
		static void				camera2pixels(float *x,float *y,const float *P);
		static void				camera2pixels(int n,float *P);
		static void				camera2screen(int n,float *P);
		static void				distance2pixels(int n,float *dist,float *P);
		static void				pixels2camera(float *P,float x,float y,float z);
		static float			minCocPixels(float z1, float z2);
		static void				advanceBucket();


								////////////////////////////////////////////////////////////////////
								// Functions that deal with the displays (implemented in frameDisplay.cpp)
								////////////////////////////////////////////////////////////////////
		static void				commit(int,int,int,int,float *);
		static int				advanceBucket(int,int &,int &,int &,int &);			// Find the next bucket to render for network rendering
		static void				clear(int,int,int,int);								// Clear a window
		static void				dispatch(int,int,int,int,float *);					// Dispatch a window to out devices
		static void				getDisplayName(char *,const char *,const char *);	// Retrieve the display name


								////////////////////////////////////////////////////////////////////
								// Functions that deal with declerations (implemented in frameDeclerations.cpp)
								////////////////////////////////////////////////////////////////////
		static	void			defineCoordinateSystem(const char *,matrix &,matrix &,ECoordinateSystem type = COORDINATE_CUSTOM);
		static	CVariable		*declareVariable(const char *,const char *,int um = 0);
		static	void			makeGlobalVariable(CVariable *);
		static	CVariable		*retrieveVariable(const char *);
		static	CDisplayChannel	*declareDisplayChannel(const char *);					// Display channel management
		static	CDisplayChannel	*declareDisplayChannel(CVariable *);
		static	CDisplayChannel	*retrieveDisplayChannel(const char *);
		static	void			resetDisplayChannelUsage();
		static	void			registerFrameTemporary(const char *,int);				// Register file for end-of-frame deletion
		static	int				getGlobalID(const char *);								// Global ID management

								
								////////////////////////////////////////////////////////////////////
								// Functions that deal with files (implemented in frameFiles.cpp)
								////////////////////////////////////////////////////////////////////
		static	int				locateFileEx(char *,const char *,const char *extension=NULL,TSearchpath *search=NULL);
		static	int				locateFile(char *,const char *,TSearchpath *search=NULL);
		static	CTexture		*textureLoad(const char *,TSearchpath *);				// Load a new texture map
		static	CEnvironment	*environmentLoad(const char *,TSearchpath *,float *);	// Load a new environment map
		static	CTexture		*getTexture(const char *);								// Load a texture
		static	CEnvironment	*getEnvironment(const char *);							// Load an environment
		static	CPhotonMap		*getPhotonMap(const char *);							// Load a photon map
		static	CCache			*getCache(const char *,const char *);					// Load a photon map
		static	CTextureInfoBase *getTextureInfo(const char *);							// Load a textureinfo
		static	CTexture3d		*getTexture3d(const char*,int,const char*,const float*,const float *);	// Load a point cloud or brickmap
		static	RtFilterFunc	getFilter(const char *);								// Get a filter
		static	char			*getFilter(RtFilterFunc);								// The other way around
		static	int				loadDSO(char *,char *,TSearchpath *,dsoInitFunction *,dsoExecFunction *,dsoCleanupFunction *);	// Find/load a DSO shader


								////////////////////////////////////////////////////////////////////
								// Functions that deal with network (implemented in frameNetwork.cpp)
								////////////////////////////////////////////////////////////////////
		static	void			netSetup(char *,char *);								// Setup the network for rendering
		static	void			sendFile(int,char *,int,int);							// Send a particular file
		static	int				getFile(char *,const char *);							// Get a particular file from network
		static	int				getFile(FILE *,const char *,int start=0,int size=0);	// Get a particular file from network
		static	void			clientRenderFrame();									// Isn't that obvious
		static	void			processServerRequest(T32,int);							// Process a request from the server


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
								// The memory we use for the frame
								////////////////////////////////////////////////////////////////////
		static CMemStack		*frameMemory;
		static	CArray<const char*>	*frameTemporaryFiles;		// This hold the name of temporary files

								////////////////////////////////////////////////////////////////////
								// The options
								////////////////////////////////////////////////////////////////////
		static	COptions		options;		

								////////////////////////////////////////////////////////////////////
								// Remote channels
								////////////////////////////////////////////////////////////////////
		static	CDictionary<const char *,CRemoteChannel *>		*declaredRemoteChannels;	// Known remote channel lookup
		static	CArray<CRemoteChannel *>						*remoteChannels;			// all known channels

								////////////////////////////////////////////////////////////////////
								// Misc stuff that we touched while rendering that needs cleaning
								////////////////////////////////////////////////////////////////////
		static	CArray<CAttributes *>							*dirtyAttributes;		// The list of attributes that need to be cleaned after the rendering
		static	CArray<CProgrammableShaderInstance *>			*dirtyInstances;		// The list of shader instances that need cleanup


		
								////////////////////////////////////////////////////////////////////
								// Raytracing related functions
								////////////////////////////////////////////////////////////////////
		static	unsigned int			raytracingFlags;								// The raytracing flags that hold the combination that needs to be raytraced
		static	CHierarchy				*hierarchy;										// The raytracing hierarchy
		static	CArray<CTriangle *>		*triangles;										// The array of triangles
		static	CArray<CSurface *>		*raytraced;										// The list of raytraced objects
		static	CArray<CTracable *>		*tracables;										// The array of raytracable objects


								////////////////////////////////////////////////////////////////////
								// Some interesting precomputed quantities
								////////////////////////////////////////////////////////////////////
		static	vector			worldBmin,worldBmax;							// The bounding box of the world
		static	CXform			*world;											// The world xform
		static	matrix			fromWorld,toWorld;								// Some misc matrices
		static	matrix			fromNDC,toNDC;
		static	matrix			fromRaster,toRaster;
		static	matrix			fromScreen,toScreen;
		static	matrix			worldToNDC;										// World to NDC matrix
		static	unsigned int	hiderFlags;										// The hider flags

		static	int				numSamples;										// The actual number of samples to compute
		static	int				numExtraSamples;								// The number of actual samples
		static	int				xPixels,yPixels;								// The number of pixels to compute in X and Y
		static	unsigned int	additionalParameters;							// Any user specified parameters to be computed
		static	float			pixelLeft,pixelRight,pixelTop,pixelBottom;		// The rendering window on the screen plane
		static	float			dydPixel,dxdPixel;								// Stuff
		static	float			dPixeldx,dPixeldy;
		static	int				renderLeft,renderRight,renderTop,renderBottom;	// The actual rendering window in pixels
		static	int				xBuckets,yBuckets;								// The number of buckets
		static	int				metaXBuckets,metaYBuckets;						// The number of meta buckets in X and Y
		static	float			aperture;										// Aperture radius
		static	float			imagePlane;										// The z coordinate of the image plane
		static	float			invImagePlane;									// The reciprocal of that
		static	float			cocFactorPixels;								// The circle of concusion factor for the pixels
		static	float			cocFactorSamples;								// The circle of concusion factor for the samples
		static	float			cocFactorScreen;								// The circle of concusion factor for the screen
		static	float			invFocaldistance;								// 1 / focalDistance
		static	float			lengthA,lengthB;								// The depth to length conversion

		static	float			marginXcoverage,marginYcoverage;				// Coverage ratios for the pixel filter
		static	float			marginX,marginY;
		static	float			marginalX,marginalY;

		static	float			leftX,leftZ,leftD;								// The clipping plane equations
		static	float			rightX,rightZ,rightD;
		static	float			topY,topZ,topD;
		static	float			bottomY,bottomZ,bottomD;

		static	int				numActiveDisplays;								// The number of active displays

		static	int				currentXBucket;									// The bucket counters
		static	int				currentYBucket;

		static	int				*jobAssignment;									// The job assignment for the buckets

		static	FILE			*deepShadowFile;								// Deep shadow map stuff
		static	int				*deepShadowIndex;
		static	int				deepShadowIndexStart;							// The offset in the file for the indices
		static	char			*deepShadowFileName;



		///////////////////////////////////////////////////////////////////////
		// Class				:	CDisplayData
		// Description			:	This class holds data about a display driver
		// Comments				:
		// Date last edited		:	7/4/2001
		class CDisplayData {
		public:
				void						*module;						// The module handle for the out device
				void						*handle;						// The handle for the out device
				int							numSamples;						// The number of samples
				CDisplayChannel				*channels;
				int							numChannels;
				
				char						*displayName;					// The computed display name
				TDisplayStartFunction		start;							// The start function for the out device
				TDisplayDataFunction		data;							// The data function
				TDisplayRawDataFunction		rawData;						// The raw data function
				TDisplayFinishFunction		finish;							// The finish function
				CDisplay					*display;
		};

		static	int				numDisplays;
		static	CDisplayData	*datas;
		static	int				*sampleOrder;		// variable entry, sample count pairs
		static	float			*sampleDefaults;	// default values for each channel
		static	int				numExtraChannels;	


protected:
		static	void			computeDisplayData();
};


// These two are defined in frameNetwork.cpp
void			rcSend(SOCKET,char *,int,int net = TRUE);				// Send data
void			rcRecv(SOCKET,char *,int,int net = TRUE);				// Recv data



/*


///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Method				:	camera2pixels
// Description			:	Project from camera space into the pixel space
// Return Value			:
// Comments				:	(inline for speed)
// Date last edited		:	7/4/2001
inline void		CFrame::camera2pixels(float *P) {
	if(projection == OPTIONS_PROJECTION_PERSPECTIVE) {
		P[COMP_X]	=	imagePlane*P[COMP_X]/P[COMP_Z];
		P[COMP_Y]	=	imagePlane*P[COMP_Y]/P[COMP_Z];
	}

	P[COMP_X]	=	(P[COMP_X] - pixelLeft)*dPixeldx;
	P[COMP_Y]	=	(P[COMP_Y] - pixelTop)*dPixeldy;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Method				:	camera2pixels
// Description			:	Project from camera space into the pixel space
// Return Value			:
// Comments				:	(inline for speed)
// Date last edited		:	7/4/2001
inline void		CFrame::camera2pixels(float *x,float *y,const float *P) {
	if(projection == OPTIONS_PROJECTION_PERSPECTIVE) {
		x[0]	=	imagePlane*P[COMP_X]/P[COMP_Z];
		y[0]	=	imagePlane*P[COMP_Y]/P[COMP_Z];
	} else {
		x[0]	=	P[COMP_X];
		y[0]	=	P[COMP_Y];
	}

	x[0]	=	(x[0] - pixelLeft)*dPixeldx;
	y[0]	=	(y[0] - pixelTop)*dPixeldy;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Method				:	camera2pixels
// Description			:	Project from camera space into the pixel space
// Return Value			:
// Comments				:	(inline for speed)
// Date last edited		:	7/4/2001
inline void		CFrame::camera2pixels(int n,float *P) {
	if(projection == OPTIONS_PROJECTION_PERSPECTIVE) {
		for (;n>0;n--,P+=3) {
			P[COMP_X]	=	(imagePlane*P[COMP_X]/P[COMP_Z] - pixelLeft)*dPixeldx;
			P[COMP_Y]	=	(imagePlane*P[COMP_Y]/P[COMP_Z] - pixelTop)*dPixeldy;
		}
	} else {
		for (;n>0;n--,P+=3) {
			P[COMP_X]	=	(P[COMP_X] - pixelLeft)*dPixeldx;
			P[COMP_Y]	=	(P[COMP_Y] - pixelTop)*dPixeldy;
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Method				:	camera2screen
// Description			:	Project from camera space into the screen space
// Return Value			:
// Comments				:	(inline for speed)
// Date last edited		:	7/4/2001
inline void		CFrame::camera2screen(int n,float *P) {
	if(projection == OPTIONS_PROJECTION_PERSPECTIVE) {
		for (;n>0;n--,P+=3) {
			P[COMP_X]	=	(imagePlane*P[COMP_X]/P[COMP_Z] - pixelLeft);
			P[COMP_Y]	=	(imagePlane*P[COMP_Y]/P[COMP_Z] - pixelTop);
		}
	} else {
		for (;n>0;n--,P+=3) {
			P[COMP_X]	=	(P[COMP_X] - pixelLeft);
			P[COMP_Y]	=	(P[COMP_Y] - pixelTop);
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Method				:	distance2pixels
// Description			:	Project a distance in camera space into a distance in the pixel space
// Return Value			:
// Comments				:	(inline for speed)
// Date last edited		:	7/4/2001
inline void		CFrame::distance2pixels(int n,float *dist,float *P) {
	if(projection == OPTIONS_PROJECTION_PERSPECTIVE) {
		for (;n>0;n--,P+=3) {
			*dist++		=	dPixeldx*imagePlane*dist[0]/P[COMP_Z];
		}
	} else {
		for (;n>0;n--,P+=3) {
			*dist++		=	dPixeldx*dist[0];
		}
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Method				:	pixels2distance
// Description			:	Convert from pixel distance to camera space distance
// Return Value			:	-
// Comments				:
// Date last edited		:	7/4/2001
void			CFrame::pixels2distance(float &a,float &b,float d) {
	a	=	lengthA*d;
	b	=	lengthB*d;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Method				:	samples2camera
// Description			:	Back project from sample space into the camera space
// Return Value			:
// Comments				:	(inline for speed)
// Date last edited		:	7/4/2001
inline void		CFrame::pixels2camera(float *P,float x,float y,float z) {
	x	=	x*dxdPixel + pixelLeft;
	y	=	y*dydPixel + pixelTop;

	if(projection == OPTIONS_PROJECTION_PERSPECTIVE) {
		P[COMP_X]	=	x*z*invImagePlane;
		P[COMP_Y]	=	y*z*invImagePlane;
		P[COMP_Z]	=	z;
	} else {
		P[COMP_X]	=	x;
		P[COMP_Y]	=	y;
		P[COMP_Z]	=	z;
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Method				:	minCocPixels
// Description			:	return the minimum circle of confusion
// Return Value			:
// Comments				:	(inline for speed, needed for CSurface::dice() )
// Date last edited		:	4/7/2006
inline float	CFrame::minCocPixels(float z1, float z2) {
	return min(cocPixels(z1),cocPixels(z2));
}


///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Method				:	advanceBucket
// Description			:	Advance the bucket
// Return Value			:	TRUE if we're still rendering, FALSE otherwise
// Comments				:
// Date last edited		:	7/4/2001
void			CFrame::advanceBucket() {
	currentXBucket++;
	if (currentXBucket == xBuckets) {		
		currentXBucket	=	0;
		currentYBucket++;
	}

	if ((currentXBucket == 0) && (currentYBucket == yBuckets)) {
		hiderFlags |=	HIDER_DONE | HIDER_BREAK;
	}
}



*/

#endif





