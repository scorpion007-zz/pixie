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
//  File				:	options.h
//  Classes				:	COptions
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef OPTIONS_H
#define OPTIONS_H

#include "common/global.h"
#include "common/containers.h"
#include "common/algebra.h"
#include "rendererc.h"
#include "xform.h"
#include "ri_config.h"
#include "ri.h"
#include "shader.h"
#include "dsply.h"
#include "userAttributes.h"

// Possible projections
typedef enum {
	OPTIONS_PROJECTION_PERSPECTIVE,			// Perspective projection
	OPTIONS_PROJECTION_ORTHOGRAPHIC			// Orthographic projection
} EProjectionType;

// The search paths are kept as a linked list of the following items
typedef struct TSearchpath {
	char		*directory;
	TSearchpath	*next;
} TSearchpath;

// This is the depth filter type
typedef enum {
	DEPTH_MIN,
	DEPTH_MAX,
	DEPTH_AVG,
	DEPTH_MID
} EDepthFilter;

// Options flags
const	unsigned int		OPTIONS_FLAGS_CUSTOM_SCREENWINDOW	=	1<<0;	// The screenwindow is fixed
const	unsigned int		OPTIONS_FLAGS_CUSTOM_FRAMEAR		=	1<<1;	// The frame aspect ratio is fixed
const	unsigned int		OPTIONS_FLAGS_CUSTOM_RESOLUTION		=	1<<2;	// The resolution is fixed
const	unsigned int		OPTIONS_FLAGS_CUSTOM_CLIPPING		=	1<<3;	// The near/far clipping planes have been set by user
const	unsigned int		OPTIONS_FLAGS_FALSECOLOR_RAYTRACES	=	1<<4;	// Create a false color image of the effort being spent on the image
const	unsigned int		OPTIONS_FLAGS_INHERIT_ATTRIBUTES	=	1<<12;	// The object instance inherit attributes from the parent
const	unsigned int		OPTIONS_FLAGS_MOTIONBLUR			=	1<<13;	// We have motion blur in the scene (shutter open != shutter close)
const	unsigned int		OPTIONS_FLAGS_FOCALBLUR				=	1<<14;	// We have depth of field in the scene
const	unsigned int		OPTIONS_FLAGS_DEEP_SHADOW_RENDERING	=	1<<16;	// We're rendering a deep shadow map
const	unsigned int		OPTIONS_FLAGS_USE_RADIANCE_CACHE	=	1<<17;	// Use the new radiance cache
const	unsigned int		OPTIONS_FLAGS_PROGRESS				=	1<<18;	// Display the progress
const	unsigned int		OPTIONS_FLAGS_SAMPLESPECTRUM		=	1<<19;	// Sample the spectrum in photon hider
const	unsigned int		OPTIONS_FLAGS_SAMPLEMOTION			=	1<<20;	// We want the hider to sample motion blur (perform motion blur)


///////////////////////////////////////////////////////////////////////
// Class				:	COptions
// Description			:	This class settings that are constant accross a frame
// Comments				:
class COptions {
public:


	///////////////////////////////////////////////////////////////////////
	// Class				:	CDisplay
	// Description			:	Holds a display setting
	// Comments				:
	class CDisplay {
	public:
									///////////////////////////////////////////////////////////////////////
									// Class				:	TDisplayParameter
									// Description			:	Holds a display parameter
									// Comments				:
									typedef struct {
										char			*name;
										ParameterType	type;
										int				numItems;
										void			*data;
									} TDisplayParameter;


									CDisplay();
									CDisplay(const CDisplay *);
									~CDisplay();

		char						*outDevice;		// The name of the out device
		char						*outName;		// The name of the image
		char						*outSamples;	// The samples to go into the display
		CDisplay					*next;
		float						quantizer[5];	// The quantization data

		RtDisplayStartFunction		startFunction;	// For custom displays
		RtDisplayDataFunction		dataFunction;
		RtDisplayFinishFunction		finishFunction;

		int							numParameters;
		TDisplayParameter			*parameters;
	};

	///////////////////////////////////////////////////////////////////////
	// Class				:	CClipPlane
	// Description			:	Holds a user defined clip plane description
	// Comments				:
	class CClipPlane {
	public:
									CClipPlane();
									CClipPlane(const CClipPlane *);

		vector						normal;			// Normal vector in camera space
		float						d;				// normal.P+d=0;
		CClipPlane					*next;			// Next clipping plane
	};

	
								COptions();
								COptions(const COptions *);
	virtual						~COptions();

								// The following method is used to convert from a custom color space to RGB if- entered
	void						convertColor(vector &c,const float *f)	const;

								// Guess where to search by looking into the extension
	TSearchpath					*pickSearchpath(const char *name);

								// Find a particular option
	int							find(const char *name,const char *category,EVariableType &type,const void *&value,int &intValue,float &floatValue) const;









								////////////////////////////////////////////////////////////////////
								// options start here
								////////////////////////////////////////////////////////////////////
	int							xres,yres;										// Output resolution

	int							frame;											// The frame number given by frameBegin

	float						pixelAR;										// Pixel aspect ratio
	float						frameAR;										// Frame aspect ratio

	float						cropLeft,cropRight,cropTop,cropBottom;			// The crop window
	float						screenLeft,screenRight,screenTop,screenBottom;	// The screen window

	float						clipMin,clipMax;								// Clipping bounds

	float						pixelVariance;									// The maximum tolerable pixel color variation

	float						jitter;											// Amount of jitter in samples

	char						*hider;											// Hider name

	TSearchpath					*archivePath;									// RIB search path
	TSearchpath					*proceduralPath;								// Procedural primitive search path
	TSearchpath					*texturePath;									// Texture search path
	TSearchpath					*shaderPath;									// Shader search path
	TSearchpath					*displayPath;									// Display search path
	TSearchpath					*modulePath;									// Search path for Pixie modules

	int							pixelXsamples,pixelYsamples;					// Number of samples to take in X and Y

	float						gamma,gain;										// Gamma correction stuff

	float						pixelFilterWidth,pixelFilterHeight;				// Pixel filter data
	RtFilterFunc				pixelFilter;

	float						colorQuantizer[5];								// The quantization data
	float						depthQuantizer[5];

	vector						opacityThreshold;								// The opacity threshold
	vector						zvisibilityThreshold;							// The visibility threshold for z files and noncomp aovs
	
	CDisplay					*displays;										// List of displays to send the output

	CClipPlane					*clipPlanes;									// List of used defined clipping planes

	float						relativeDetail;									// The relative detail multiplier

	EProjectionType				projection;										// Projection type
	float						fov;											// Field of view for perspective projection

	int							nColorComps;									// Custom color space stuff
	float						*fromRGB,*toRGB;

	float						fstop,focallength,focaldistance;				// Depth of field stuff

	float						shutterOpen,shutterClose;						// Motion blur stuff
	float						shutterOffset;									// Shutter offset

	unsigned int				flags;											// Flags	

								////////////////////////////////////////////////////////////////////
								// Pixie dependent options
								////////////////////////////////////////////////////////////////////

	int							endofframe;										// The end of frame statstics number
	char						*filelog;										// The name of the log file

	int							numThreads;										// The number of threads working

	int							maxTextureSize;									// Maximum amount of texture data to keep in memory (in bytes)

	int							maxBrickSize;									// Maximum amount of brick data to keep in memory (in bytes)

	int							maxGridSize;									// Maximum number of points to shade at a time

	int							maxRayDepth;									// Maximum raytracing recursion depth

	int							maxPhotonDepth;									// The maximum number of photon bounces

	int							bucketWidth,bucketHeight;						// Bucket dimentions in samples

	int							netXBuckets,netYBuckets;						// The meta bucket size

	int							threadStride;									// The number of buckets to distribute to threads at a time
	
	int							geoCacheMemory;									// The ammount of memory to dedicate to tesselation caches

	int							maxEyeSplits;									// Maximum number of eye splits
																				// The number of times the bucket will be rendered

	float						tsmThreshold;									// Transparency shadow map threshold

	char						*causticIn,*causticOut;							// The caustics in/out file name
	char						*globalIn,*globalOut;							// The global photon map 

	int							numEmitPhotons;									// The number of photons to emit for the scene

	int							shootStep;										// The number of rays to shoot at a time

	EDepthFilter				depthFilter;									// Holds the depth filter type
	
	CUserAttributeDictionary	userOptions;									// User options
};


TSearchpath					*optionsGetSearchPath(const char *,TSearchpath *);				// Compute the search path

#endif

