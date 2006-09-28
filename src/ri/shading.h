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
//  File				:	shading.h
//  Classes				:	CShadingContext
//  Description			:	The shading context that handles sampling/shading surfaces
//
////////////////////////////////////////////////////////////////////////
#ifndef SHADING_H
#define SHADING_H

#include "common/global.h"
#include "common/algebra.h"
#include "common/containers.h"
#include "output.h"
#include "shader.h"
#include "random.h"

// Some forward definitions
class	CShaderInstance;
class	CVariable;
class	CAttributes;
class	CXform;
class	CShaderInstance;
class	CRay;
class	CObject;
class	CRemoteChannel;
class	CSurface;
class	CTracable;
class	CQuadVertex;
class	CQuadTriangle;
class	CQuad;
class	CTextureLookup;
class	CTexture3d;
class	CVertex;
class	CMovingVertex;
class	CTriangle;
class	CMovingTriangle;
class	CMemPage;
class	CHierarchy;
class	CActiveSample;
class	COutput;
class	CPoints;
class	CPointCloud;
class	CVolume;
class	CParticipatingMedium;
class	CCache;
class	CVisorCache;
class	CPl;
class	CSphereLight;
class	CRaySample;
struct	TObjectHash;

const int	SHADING_OBJECT_CACHE_SIZE	=	512;


typedef enum {
	SHADING_0D,				// Shading points
	SHADING_1D_GRID,		// Shading lines (grid)
	SHADING_1D,				// Shading lines
	SHADING_2D_GRID,		// Shading a 2D grid
	SHADING_2D,				// Shading a 2D surface that has been arbitraryly sampled
	SHADING_NODIM			// Shading arbitraryly sampled points without any neighborhood info
} EShadingDim;

// Predefined ray labels used during raytracing
extern	char	*rayLabelPrimary;
extern	char	*rayLabelTrace;
extern	char	*rayLabelTransmission;
extern	char	*rayLabelGather;


///////////////////////////////////////////////////////////////////////
// Class				:	CConditional
// Description			:	This class is used to hold info about a conditional
// Comments				:
// Date last edited		:	10/13/2001
class	CConditional {
public:
		int						forStart;							// The start IP of the conditional
		int						forContinue;						// The continue IP of the conditional
		int						forEnd;								// The end IP of the conditional
		int						forExecCount;						// The execution count of the conditional
		CConditional			*next,*prev;						// The next in the free list and the prev in the conditional stack
};


///////////////////////////////////////////////////////////////////////
// Class				:	CShadedLight
// Description			:	Hold a shaded light
// Comments				:	An instance of this class will be created for each execution of "solar" or "illuminate"
// Date last edited		:	10/13/2001
class	CShadedLight {
public:
		float					**savedState;						// the saved variables for this light
		int						*lightTags;							// the runtags indicating which points this light ran on
		CShaderInstance			*instance;							// points to the instance of light
		CShadedLight			*next;								// Points to the next shaded light
};

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingState
// Description			:	Holds a shading state at a depth
// Comments				:
// Date last edited		:	10/13/2001
class	CShadingState {
public:
																	// ---> Input fields
		CSurface				*currentObject;						// Current object
		int						numVertices;						// The number of vertices to be shaded
		int						numUvertices,numVvertices;			// The number of o/v vertices (only if rendering a regular grid)
		EShadingDim				shadingDim;							// The shading dimentionality
																	// ---> Shading variables:
		float					**varying;							// Varying variables
		float					*Ns;								// For the light source shaders: the normal of the surface
		const float				*costheta;							// For the light source shaders: the cosine of the cone of normals
																	// ---> Lighting variables
		CShadedLight			*lights;							// Lights for grid
		CShadedLight			*alights;							// Ambient lights for grid
		CShadedLight			*currentLight;						// Within an illumination statement, this points to the current light being iterated
		CShadedLight			*freeLights;						// Unused lights
		int						*lightingTags;						// The tags active when the lighting was executed
		int						lightsExecuted;						// FALSE if the lights have not been executed yet
		int						ambientLightsExecuted;				// FALSE if the ambient lights have not been executed yet
		int						lightCategory;						// The current light category
																	// ---> State and runtags
		int						*tags;								// Exec stack counter
		int						numRealVertices;					// Vertex count (internally used)
		int						numActive,numPassive;				// The number of vertices that are active and passive respectively
		CShaderInstance			*postShader;						// Shader to be executed on the surface after the atmosphere

		CShaderInstance			*currentShaderInstance;				// The current shader instance that's executing
		CShaderInstance			*currentLightInstance;				// The current light instance that's executing
		
		float					**locals[NUM_ACCESSORS];			// The local variables for each shader type

		CShadingState			*next;								// The next in free state list
};

///////////////////////////////////////////////////////////////////////
// Class				:	CRayBundle
// Description			:	Encapsulates a bundle of rays
// Comments				:
// Date last edited		:	3/20/2003
class	CRayBundle {
public:
		int						numRays;									// The number of rays to trace
		CRay					**rays;										// The array of rays to trace
		const char				*label;										// The label of these rays
		int						last;										// The last transparent ray
		int						depth;										// The transparency depth of the bundle
		CShaderInstance			*postShader;								// The shader to execute after the raytrace

		virtual	int				postTraceAction()				=	0;		// The function to be called after the rays are traced
		virtual	void			postShade(int,CRay **,float **)	=	0;		// The function that's called with the shade results
		virtual	void			postShade(int,CRay **)			=	0;		// The function that's called with the rays that don't intersect anything
		virtual	void			post()							=	0;		// The function that's called after each pass
};


///////////////////////////////////////////////////////////////////////
// Class				:	CThreadContext
// Description			:	Holds thread specific stuff
// Comments				:
// Date last edited		:	10/13/2001
class	CShadingContext : public COutput {
public:
								CShadingContext(COptions *,CXform *,SOCKET,unsigned int);
								~CShadingContext();

								// The following functions must be overidden by the derived classes
		void					render(CObject *);										// Called to insert an object into the scene
		void					remove(CTracable *);									// Called to remove a delayed object from the scene

								// A block that is used by the renderer
		void					beginWorld();											// We're starting to specify geometry
		void					endWorld();												// We're done specifying geometry

		virtual	void			renderFrame()					=	0;					// Right after world end to force rendering of the entire frame

		// Delayed rendering functions
		virtual	void			drawObject(CObject *,const float *,const float *)		=	0;

		// Primitive creation functions
		virtual	void			drawGrid(CSurface *,int,int,float,float,float,float)	=	0;
		virtual	void			drawRibbon(CSurface *,int,float,float)					=	0;
		virtual	void			drawPoints(CSurface *,int)								=	0;

		// Some shading functions
		CShadingState			*currentShadingState;									// The current shading state
		void					shade(CSurface *,int,int,int,unsigned int);				// Shade points on a surface
		void					displace(CSurface *,int,int,int,unsigned int);			// Sample points on a surface

								// The raytracing functions that can be called after prepareFrame
		void					trace(CRayBundle *);									// Trace and maybe shade bunch of rays
		void					traceEx(CRayBundle *);									// Trace and maybe shade a bundle of rays. This version increments the shading depth
		void					retraceRay(CRay *);										// Trace a ray again

								// Surface tesselation
		void					tesselate2D(CSurface *);								// Tesselate a surface
		virtual void			addTracable(CTracable *,CSurface *);					// Add a raytracable object into the scene
		virtual void			addTracable(CTriangle *,CSurface *);
		virtual void			addTracable(CMovingTriangle *,CSurface *);

								// Variable management functions
		void					initState(CVariable *,int);								// Initialize the shading state
		void					updateState(CVariable *);								// Add a variable into the shading state

		CShadingState			*newState();											// Allocate a new shading state
		void					freeState(CShadingState *);								// Destroy a shading state
		void					deleteState(CShadingState *);							// Delete a shading state

		CMemStack				*frameMemory;											// The memory area for the frame
		
		// remote channels (remoteChannel.cpp)
		int						requestRemoteChannel(CRemoteChannel *);					// request a remote channel (server requests from client)
		int						processChannelRequest(int,SOCKET);						// service request for a remote channel in client
		
		void					sendBucketDataChannels(int x,int y);					// send all per-bucket remote channels
		void					recvBucketDataChannels(SOCKET s,int x,int y);			// receive one per-bucket remote channel
		void					sendFrameDataChannels();								// send all per-frame remote channels
		void					recvFrameDataChannels(SOCKET s);						// receive one per-frame remote channel
	
protected:
		virtual	void			solarBegin(const float *,const float *) { }
		virtual	void			solarEnd() { }
		virtual	void			illuminateBegin(const float *,const float *,const float *) { }
		virtual	void			illuminateEnd() { }
		vector					worldBmin,worldBmax;									// The bounding box of the entire scene
		CHierarchy				*hierarchy;												// The raytracing hierarchy

		CTexture				*getTexture(const char *);								// Load a texture
		CEnvironment			*getEnvironment(const char *);							// Load an environment
		CPhotonMap				*getPhotonMap(const char *);							// Load a photon map
		CCache					*getCache(const char *,const char *);					// Load a photon map
		CTextureInfoBase		*getTextureInfo(const char *);							// Load a textureinfo
		CTexture3d				*getTexture3d(const char*,int,const char*,const char*);	// Load a point cloud or brickmap

		CDictionary<const char *,CFileResource *>			*loadedFiles;				// This holds the files loaded so far

		CArray<CAttributes *>	*dirtyAttributes;										// The list of attributes that need to be cleaned after the rendering
		CArray<CTriangle *>		*triangles;												// The array of triangles
		CArray<CSurface *>		*raytraced;												// The list of raytraced objects
		CArray<CTracable *>		*tracables;												// The array of raytracable objects
private:

		CMemPage				*shaderStateMemory;										// Memory from which we allocate shader instance variables
								
		CArray<CProgrammableShaderInstance *>	*dirtyInstances;						// The list of shader instances that need cleanup

		CConditional			*conditionals;											// Holds nested conditionals
		int						currentRayDepth;										// Current shading depth
		const char				*currentRayLabel;										// The current ray label
		CShadingState			*freeStates;											// The list of free states
		int						inShadow;												// TRUE if we're in a shadow
		unsigned int			raytracingFlags;										// The raytracing flags that hold the combination that needs to be raytraced

		CVariable				**globalVariables;										// The array of global variables
		int						numGlobalVariables;										// The current number of global variables
		int						maxGlobalVariables;										// Maximum number of variables allocated

		CSobol<4>				traceGenerator;											// Random number generator for "trace"
		CSobol<4>				transmissionGenerator;									// Random number generator for "transmission"
		CSobol<4>				gatherGenerator;										// Random number generator for "gather"

		TObjectHash				*traceObjectHash;										// An object hash array for raytraced objects
		
		CDictionary<const char *,CRemoteChannel *>			*declaredRemoteChannels;	// Known remote channel lookup
		CArray<CRemoteChannel *>							*remoteChannels;			// all known channels

		void					execute(CProgrammableShaderInstance *,float **);		// Execute a shader

		void					duFloat(float *,const float *);
		void					dvFloat(float *,const float *);
		void					duVector(float *,const float *);
		void					dvVector(float *,const float *);

		void					traceTransmission(float *,const float *,const float *,int,int *,CTextureLookup *);
		void					traceReflection(float *,const float *,const float *,int,int *,CTextureLookup *);
		void					traceTransmission(int,CRaySample *,CTextureLookup *);
		void					traceReflection(int,CRaySample *,CTextureLookup *);

		void					indirectSample(CGlobalIllumLookup *,const float *,const float *);
		void					occlusionSample(CGlobalIllumLookup *,const float *,const float *);

																						// The following functions are used in the shaders
		int						surfaceParameter(void *dest,const char *name,CVariable**,int*);
		int						displacementParameter(void *dest,const char *name,CVariable**,int*);
		int						atmosphereParameter(void *dest,const char *name,CVariable**,int*);
		int						incidentParameter(void *dest,const char *name,CVariable**,int*);
		int						oppositeParameter(void *dest,const char *name,CVariable**,int*);
		int						options(void *dest,const char *name,CVariable**,int*);
		int						attributes(void *dest,const char *name,CVariable**,int*);
		int						rendererInfo(void *,const char *,CVariable**,int*);
		const char				*shaderName();
		const char				*shaderName(const char *type);

		// Some misc tesselation functions (tesselate.cpp)
		int						refine2D(const CAttributes *,CQuad *);
		int						refine1D(const CAttributes *,const CQuadVertex *,const CQuadVertex *,const CQuadVertex *);
		void					displace(CSurface *,int,CQuadVertex **);

		// Some misc shading functions
		void					findCoordinateSystem(const char *,matrix *&,matrix *&,ECoordinateSystem &);

		friend	class			CPhotonHider;
		friend	class			CProgrammableShaderInstance;
		friend	class			CSphereLight;
		friend	class			CQuadLight;
};

#endif





