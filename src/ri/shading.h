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
// Class				:	TObjectHash
// Description			:	Holds an object hash root
// Comments				:
// Date last edited		:	8/16/2004
typedef struct TObjectHash {
		CSurface				*object;
		CRay					*rays;
		int						numRays;
		TObjectHash				*next;
		TObjectHash				*shadeNext;
} TObjectHash;

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Description			:	Holds thread specific stuff
// Comments				:
// Date last edited		:	10/13/2001
class	CShadingContext {
public:
								CShadingContext(int thread);
		virtual					~CShadingContext();

		// This function is called to to render
		virtual	void			renderingLoop()											=	0;

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

		void					trace(CRayBundle *);									// Trace and maybe shade bunch of rays
		void					traceEx(CRayBundle *);									// Trace and maybe shade a bundle of rays. This version increments the shading depth

								// Surface tesselation
		void					tesselate2D(CSurface *);								// Tesselate a surface

								// Variable management functions
		void					updateState();											// Add a variable into the shading state

		CShadingState			*newState();											// Allocate a new shading state
		void					freeState(CShadingState *);								// Destroy a shading state
		void					deleteState(CShadingState *);							// Delete a shading state
	
		CMemPage				*threadMemory;											// Memory from which we allocate the temp thread stuff

		// Thread safe random number generator for integers
		inline	unsigned long	irand() {
									register unsigned long y;

									if(state == next)	next_state();

									y = *( --next);

									// Tempering
									y ^= (y >> 11);
									y ^= (y << 7) & 0x9d2c5680UL;
									y ^= (y << 15) & 0xefc60000UL;
									y ^= (y >> 18);

									return y;
								}
      
		// Thread safe random number generator for floats
		inline	float			urand() {
									register unsigned long y;

									if(state == next)	next_state();

									y = *( --next);

									// Tempering
									y ^= (y >> 11);
									y ^= (y << 7) & 0x9d2c5680UL;
									y ^= (y << 15) & 0xefc60000UL;
									y ^= (y >> 18);

									y &= 0x3FFFFFFF;
									return float(y) * (float(1.0)/float(0x3FFFFFFF));
								}
protected:
		virtual	void			solarBegin(const float *,const float *) { }
		virtual	void			solarEnd() { }
		virtual	void			illuminateBegin(const float *,const float *,const float *) { }
		virtual	void			illuminateEnd() { }

		int						thread;													// The thread number for this context		
private:
		CMemPage				*shaderStateMemory;										// Memory from which we allocate shader instance variables

		CConditional			*conditionals;											// Holds nested conditionals
		int						currentRayDepth;										// Current shading depth
		const char				*currentRayLabel;										// The current ray label
		CShadingState			*freeStates;											// The list of free states
		int						inShadow;												// TRUE if we're in a shadow

		CSobol<4>				traceGenerator;											// Random number generator for "trace"
		CSobol<4>				transmissionGenerator;									// Random number generator for "transmission"
		CSobol<4>				gatherGenerator;										// Random number generator for "gather"

		TObjectHash				*traceObjectHash;										// An object hash array for raytraced objects
	
		void					execute(CProgrammableShaderInstance *,float **);		// Execute a shader

		// The following functions are used in the shaders
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

		// Some data structures for urand()
		//
		// implementation of  Takuji Nishimura and Makoto Matsumoto's
		// MT19937 (Mersenne Twister pseudorandom number generator)
		// with optimizations by Shawn Cokus, Matthe Bellew.
		// This generator is not cryptoraphically secure. 
		//
		// M. Matsumoto and T. Nishimura,
		// "Mersenne Twister: A 623-Dimensionally Equidistributed Uniform  
		// Pseudo-Random Number Generator",
		// ACM Transactions on Modeling and Computer Simulation,
		// Vol. 8, No. 1, January 1998, pp 3--30.
		//
		// C++ interface and further optimization by Mayur Patel
		//

		unsigned long			state[624];
		unsigned long			*next;

		void					next_state();
		void					randomInit(unsigned long u = 5489UL);
		void					randomShutdown();


		friend	class			CPhotonHider;
		friend	class			CProgrammableShaderInstance;
		friend	class			CSphereLight;
		friend	class			CQuadLight;
};

#endif





