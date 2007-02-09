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
//  File				:	shader.h
//  Classes				:	CShader
//							CShaderInstance
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef SHADER_H
#define SHADER_H

#include "common/global.h"
#include "common/containers.h"
#include "common/os.h"
#include "xform.h"
#include "rendererc.h"
#include "fileResource.h"
#include "ri.h"
#include "variable.h"

// For forward reference
class	CShader;
class	CShaderInstance;
class	CObject;
class	CPhotonMap;
class	CAttributes;
class	CActiveLight;
class	CTexture;
class	CTexture3d;
class	CTextureInfoBase;
class	CTexture3dChannel;
class	CEnvironment;
class	CCache;
class	CVolume;
class	CColorMap;
class	CVisorCache;
class	CShadingContext;
class	CPhotonHider;
class	CGatherRay;
class	CMemPage;

// Meanings of the accessor field of TReference
const	unsigned int	SL_IMMEDIATE_OPERAND	=	0;	// Constants
const	unsigned int	SL_GLOBAL_OPERAND		=	1;	// Global variable references
const	unsigned int	SL_VARYING_OPERAND		=	2;	// Local variable references (this includes parameters)

// This comes right after the opcode to denote the number of parameters passed to the function / opcode
typedef struct {
	unsigned	char	numArguments;			// The number of stack arguments
	unsigned	char	uniform;				// TRUE if all the arguments are uniform
	unsigned	char	numCodes;				// The number of codes after this one
	unsigned	char	plNumber;				// The parameter list number of the function
} TArguments;

// This is a variable reference
typedef struct {
	unsigned	char	numItems;				// The number of items to step for this variable (0 for constants,parameters, cardinality for variables,globals)
	unsigned	char	accessor;				// The type of the variable (SL_IMMEDIATE,SL_PARAMETER,SL_VARIABLE,SL_GLOBAL)
	unsigned	short	index;					// The index of the variable in the corresponding entry array
} TReference;

// This is the glorious TCode that holds everything
// !!!! FATAL	-	sizeof(TCode) must be 4 !!!!
// !!!! This is a major piece of code that makes Pixie 64 bit incompatible !!!!
typedef union {
	TArguments	arguments;
	TReference	reference;
	float		real;
	int			integer;
	const char	*string;
	void		*pointer;
} TCode;

// Shader types
const	unsigned int		SL_SURFACE						=	0;
const	unsigned int		SL_LIGHTSOURCE					=	1;
const	unsigned int		SL_DISPLACEMENT					=	2;
const	unsigned int		SL_ATMOSPHERE					=	3;
const	unsigned int		SL_IMAGER						=	4;

// Shader flags
const	unsigned int		SHADERFLAGS_NONAMBIENT			=	1;

///////////////////////////////////////////////////////////////////////
// Class				:	CShaderLookup
// Description			:	This class encapsulates a shader lookup
// Comments				:	Shader lookups are cached in the lifetime of a frame
//							so they're only allocated once and can store information
//							relevant to a particular shading language command
class	CShaderLookup {
public:
							CShaderLookup();
		virtual				~CShaderLookup();
};


#define	NUMFILTERSTEPS	10

///////////////////////////////////////////////////////////////////////
// Class				:	CTextureLookup
// Description			:	This class holds information about a particular texture lookup
// Comments				:
class	CFilterLookup : public CShaderLookup	{
public:
		float				width;					// The width parameter
		RtFilterFunc		filter;					// The filter function
		float				vals[NUMFILTERSTEPS];	// The partial integrals
		float				valStep;				// The step value for the value
		float				normalizer;				// The normalizer value

		void				compute();
};

///////////////////////////////////////////////////////////////////////
// Class				:	CTextureInfoLookup
// Description			:	This class holds the base of a textureinfo lookup
// Comments				:
class	CTextureInfoLookup : public CShaderLookup	{
public:
		CTextureInfoBase	*textureInfo;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CTraceLookup
// Description			:	This class holds the base of a trace lookup
// Comments				:
class	CTraceLookup : public CShaderLookup	{
public:
		float				bias;
		const char*			label;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CTextureLookup
// Description			:	This class holds information about a particular texture lookup
// Comments				:
class	CTextureLookup : public CShaderLookup	{
public:
		RtFilterFunc		filter;					// Lookup filter
		float				swidth,twidth;			// The filter width
		float				blur;					// Blur amount
		int					numSamples;				// The number of samples to take in the texture
		float				shadowBias;				// The shadow bias for the lookup
		int					channel;				// The start channel for the lookup
		float				fill;					// The fill in value for the lookup
		float				maxDist;				// The maximum intersection distance
		float				coneAngle;				// The coneangle
		const char			*label;					// The label of the ray
		int					lookupFloat;			// TRUE if we're only looking up a float
		CTexture			*texture;				// Points to the texture being looked up
		CEnvironment		*environment;			// Points to the environment being looked up
};

///////////////////////////////////////////////////////////////////////
// Class				:	CGlobalIllumLookup
// Description			:	This class encapsulates a global illumination lookup
// Comments				:
class	CGlobalIllumLookup : public CShaderLookup {
public:
							CGlobalIllumLookup();
							~CGlobalIllumLookup();

		int					numLookupSamples;		// The number of nearest samples to use during the map access
		float				maxDistance;			// The maximum ray intersection distance
		int					numSamples;				// The number of samples to gather for each sample
		float				maxError;				// The error knob for the sampling
		float				maxBrightness;			// The maximum brightness amount
		float				minFGRadius;			// The minimum final gather spacing
		float				maxFGRadius;			// The maximum final gather spacing
		float				sampleBase;				// The relative ammount to jitter ray origins
		int					irradianceIndex;		// The index of the irradiance
		int					coverageIndex;			// The index of the coverage
		int					environmentIndex;		// The index of the environment direction
		float				bias;					// The shadow bias
		int					occlusion;				// TRUE if this is an occlusion lookup
		int					gatherLocal,gatherGlobal;	// The gathering behaivor
		float				localThreshold;			// The local threshold for the radiance cache
		float				lengthA,lengthB;		// The depth to length conversion
		vector				backgroundColor;		// The color of the background for rays that don't hit anything
		const char			*handle;				// The irradiance handle
		const char			*filemode;				// The irradiance filemode
		CCache				*cache;					// The cache to lookup
		CPhotonMap			*map;					// The photon map to lookup
		CEnvironment		*environment;			// The environment map to use if no intersection
};


///////////////////////////////////////////////////////////////////////
// Class				:	CTexture3dLookup
// Description			:	This class holds information about a 3d texture bake
// Comments				:
class	CTexture3dLookup : public CShaderLookup	{
public:
							~CTexture3dLookup()	{
								delete[] bindings;
								for (int t = 0; t<nv; t++)
									delete[] valueSpace[t];
								delete[] valueSpace;
							}
		float				radius;					// The sample radius
		float				radiusScale;			// Blur amount
		char				**channels;				// The channels this bake3d provides
		int					numChannels;			// The number of channels bake3d provides
		int					dataStart;				// The argument at which data starts
		const char			*coordsys;				// The coordinate system to bake to
		
		int					sampleSize;				// The cloud's native sample size
		CTexture3dChannel	**bindings;				// Points to the environment being looked up
		int					nv;
		float				**valueSpace;			// Space for one sample
		
		CTexture3d			*texture;
};















///////////////////////////////////////////////////////////////////////
// Class				:	CGatherVariable
// Description			:	Encapsulates a variable to be saved
// Comments				:
class	CGatherVariable {
public:
	virtual			~CGatherVariable() { }
	virtual	void	record(TCode *,int,CGatherRay **,float **varying)	=	0;

	CGatherVariable	*next;		// The next item in the linked list
	int				shade;		// TRUE if this variable requires shading
	int				destIndex;	// The destination index
};

///////////////////////////////////////////////////////////////////////
// Class				:	CShaderVectorVariable
// Description			:	Encapsulates a shader variable
// Comments				:
class	CShaderVectorVariable : public CGatherVariable {
public:

			void	record(TCode *,int nr,CGatherRay **r,float **varying);

			int		entry;		// Variable index
};

///////////////////////////////////////////////////////////////////////
// Class				:	CShaderFloatVariable
// Description			:	Encapsulates a shader variable
// Comments				:
class	CShaderFloatVariable : public CGatherVariable {
public:

			void	record(TCode *,int nr,CGatherRay **r,float **varying);

			int		entry;		// Variable index
};

///////////////////////////////////////////////////////////////////////
// Class				:	CRayOriginVariable
// Description			:	Ray origin variable
// Comments				:
class	CRayOriginVariable : public CGatherVariable {
public:

			void	record(TCode *,int nr,CGatherRay **r,float **varying);
};

///////////////////////////////////////////////////////////////////////
// Class				:	CRayDirVariable
// Description			:	Ray direction variable
// Comments				:
class	CRayDirVariable : public CGatherVariable {
public:

			void	record(TCode *,int nr,CGatherRay **r,float **varying);
};

///////////////////////////////////////////////////////////////////////
// Class				:	CRayLengthVariable
// Description			:	Ray direction variable
// Comments				:
class	CRayLengthVariable : public CGatherVariable {
public:

			void	record(TCode *,int nr,CGatherRay **r,float **varying);
};


///////////////////////////////////////////////////////////////////////
// Class				:	CGatherLookup
// Description			:	Lookup parameters for the gather
// Comments				:
class	CGatherLookup : public CShaderLookup {
public:

							CGatherLookup();
							~CGatherLookup();

	void					addOutput(const char *,int);

	CGatherVariable			*outputs;				// These are the outputs that require shading
	int						numOutputs;				// The number of outputs
	CGatherVariable			*nonShadeOutputs;		// These are the outputs that do not require shading
	int						numNonShadeOutputs;		// The number of outputs that don't need shading

	const char				*category;				// The gather category
	const char				*label;					// The ray label
	float					coneAngle;				// The distribution angle
	float					da;						// The ray differential
	int						numSamples;				// The number of samples to gather
	float					bias;					// The shadow bias
	float					maxDist;				// The maximum intersection distance
	int						maxRayDepth;			// The maximum ray depth
	int						uniformDist;			// TRUE if we should sample uniformly
};











///////////////////////////////////////////////////////////////////////
// Class				:	CShader
// Description			:	This class encapsulates a shader
// Comments				:
class	CShader	: public CFileResource {
public:
								CShader(const char *);
								~CShader();

		int						type;							// Type of the shader

		CVariable				*parameters;					// List of parameters

		TCode					*memory;						// The memory base allocated for this shader
		TCode					*codeArea;						// The code array
		TCode					*constantsArea;					// The constant values
		TCode					**constantEntries;				// The constant entries

		int						*varyingSizes;					// The size of a variable (if negative, it is uniform)

		char					**strings;						// Strings used by the shader

		int						numGlobals;						// Number of global parameters
		int						numStrings;						// Number of strings
		int						numVariables;					// Number of variables
		int						numPLs;							// Number of parameter lists

		int						codeEntryPoint;					// Index into code array where the actual code starts
		int						initEntryPoint;					// Index into code array where the init code starts

		int						usedParameters;

		friend	CShader			*parseShader(const char *,const char *);
};


///////////////////////////////////////////////////////////////////////
// Class				:	CShaderInstance
// Description			:	This class encapsulates an instance of a shader
// Comments				:
class	CShaderInstance {
public:
								CShaderInstance(CAttributes *,CXform *);
		virtual					~CShaderInstance();

		void					attach()	{	refCount++;	}
		void					detach()	{	refCount--; if (refCount == 0) delete this; }
		void					check()		{	if (refCount == 0)	delete this;			}

		virtual	void			illuminate(CShadingContext *,float **)					=	0;
		virtual	void			setParameters(int,char **,void **)						=	0;
		virtual int				getParameter(const char *,void *,CVariable**,int*)		=	0;
		virtual	void			execute(CShadingContext *,float **)						=	0;
		virtual	unsigned int	requiredParameters()									=	0;
		virtual	const char		*getName()												=	0;
		virtual	float			**prepare(CMemPage*&,float **,int)						=	0;
		
		void					createCategories();

		CVariable				*parameters;				// The list of parameter (cloned from the parent)
		int						refCount;					// The refcount to manage the clones
		CXform					*xform;
		int						*categories;				// Categories for light shaders
		unsigned int			flags;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CProgrammableShaderInstance
// Description			:	This class encapsulates an instance of a programmable shader
// Comments				:
class	CProgrammableShaderInstance : public CShaderInstance {

	///////////////////////////////////////////////////////////////////////
	// Class				:	CAllocatedString
	// Description			:	We use this class to keep track of the allocated strings for parameters
	// Comments				:
	class	CAllocatedString {
	public:
			char				*string;
			CAllocatedString	*next;
	};
public:
									CProgrammableShaderInstance(CShader *,CAttributes *,CXform *);
		virtual						~CProgrammableShaderInstance();

		void						illuminate(CShadingContext *,float **);
		void						setParameters(int,char **,void **);
		int							getParameter(const char *,void *,CVariable**,int*);	// Get the value of a parameter
		void						execute(CShadingContext *,float **);				// Execute the shader
		unsigned int				requiredParameters();
		const char					*getName();
		float						**prepare(CMemPage*&,float **,int);


		CAllocatedString			*strings;					// The strings we allocated for parameters
		CShader						*parent;					// The parent shader
		CProgrammableShaderInstance	*nextDirty;					// The next dirty shader instance
		CProgrammableShaderInstance	*prevDirty;					// The previous dirty shader instance
		CShaderLookup				**parameterLists;			// The parameter lists
		int							dirty;						// TRUE if the shader is dirty
private:
		int						setParameter(char *,void *);
};

#endif

