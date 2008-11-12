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
//  File				:	shaderPl.cpp
//  Classes				:	CPLLookup
//  Description			:	Implementation
//
////////////////////////////////////////////////////////////////////////
#include <stddef.h>
#include "common/algebra.h"
#include "common/os.h"
#include "attributes.h"
#include "shaderPl.h"
#include "rendererc.h"
#include "bundles.h"
#include "error.h"
#include "variable.h"
#include "renderer.h"
#include "shading.h"


///////////////////////////////////////////////////////////////////////
// Class				:	CPLLookup
// Method				:	CPLLookup
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CPLLookup::CPLLookup() {
	numUniforms		=	0;
	numVaryings		=	0;
	uniforms		=	NULL;
	varyings		=	NULL;
	instance		=	0;
	code			=	0;
	next			=	NULL;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPLLookup
// Method				:	~CPLLookup
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CPLLookup::~CPLLookup() {
	if (uniforms != NULL)	delete [] uniforms;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPLLookup
// Method				:	bind
// Description			:	The default action simply prints an error
// Return Value			:	-
// Comments				:
void	CPLLookup::bind(const char *name,int &opIndex,int step,void *data,CShaderInstance *shader) {
	error(CODE_BADTOKEN,"Unknown parameter: \"%s\" in shader %s\n",name,shader->getName());
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPLLookup
// Method				:	add
// Description			:	Add a parameter
// Return Value			:	-
// Comments				:
void	CPLLookup::add(const char *name,int opIndex,int step,void *data,size_t dest) {
	TParamBinding	*cBinding;
	
	if (data != NULL)	cBinding	=	uniforms + numUniforms++;
	else				cBinding	=	varyings + numVaryings++;

	cBinding->name		=	name;
	cBinding->opIndex	=	opIndex;
	cBinding->step		=	step;
	cBinding->dest		=	dest;
}




#define	expectUniform(__name)	if (data == NULL)	warning(CODE_CONSISTENCY,"\"%s\" parameter was expected to be uniform\n",__name)







///////////////////////////////////////////////////////////////////////
// Class				:	CTextureLookup
// Method				:	CTextureLookup
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CTextureLookup::CTextureLookup() {
	map		=	NULL;
	filter	=	RiBoxFilter;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CTextureLookup
// Method				:	~CTextureLookup
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CTextureLookup::~CTextureLookup() {
}


///////////////////////////////////////////////////////////////////////
// Class				:	CTextureLookup
// Method				:	bind
// Description			:	Bind a texture lookup parameter
// Return Value			:	-
// Comments				:
void		CTextureLookup::bind(const char *name,int &opIndex,int step,void *data,CShaderInstance *shader) {

	// Find the parameter and bind it
	if (strcmp(name,"filter") == 0) {
		expectUniform(name);
		else				filter		=	CRenderer::getFilter(((const char **) data)[0]);
	} else if (strcmp(name,"blur") == 0) {
		add(name,opIndex,step,data,offsetof(CShadingScratch,textureParams.blur));
	} else if (strcmp(name,"width") == 0) {
		expectUniform(name);
		add(name,opIndex,step,data,offsetof(CShadingScratch,textureParams.width));
	} else if (strcmp(name,"swidth") == 0) {
		expectUniform(name);
		add(name,opIndex,step,data,offsetof(CShadingScratch,textureParams.swidth));
	} else if (strcmp(name,"twidth") == 0) {
		expectUniform(name);
		add(name,opIndex,step,data,offsetof(CShadingScratch,textureParams.twidth));
	} else if (strcmp(name,"fill") == 0) {
		add(name,opIndex,step,data,offsetof(CShadingScratch,textureParams.fill));
	} else if (strcmp(name,"samples") == 0) {
		add(name,opIndex,step,data,offsetof(CShadingScratch,textureParams.samples));
	} else	CPLLookup::bind(name,opIndex,step,data,shader);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CTextureLookup
// Method				:	init
// Description			:	Initialize the scratch for this lookup
// Return Value			:	-
// Comments				:
void		CTextureLookup::init(CShadingScratch *scratch,const CAttributes *attributes) {
	scratch->textureParams.filter	=	filter;
	scratch->textureParams.blur		=	0;
	scratch->textureParams.width	=	1;
	scratch->textureParams.swidth	=	1;
	scratch->textureParams.twidth	=	1;
	scratch->textureParams.fill		=	0;
	scratch->textureParams.samples	=	1;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CTextureLookup
// Method				:	init
// Description			:	Initialize texture lookup scratch for null lookup
// Return Value			:	-
// Comments				:	used by irradiance cache
void CTextureLookup::staticInit(CShadingScratch *scratch) {
	scratch->textureParams.filter	=	RiBoxFilter;
	scratch->textureParams.blur		=	0;
	scratch->textureParams.width	=	1;
	scratch->textureParams.swidth	=	1;
	scratch->textureParams.twidth	=	1;
	scratch->textureParams.fill		=	0;
	scratch->textureParams.samples	=	1;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CTraceLookup
// Method				:	CTraceLookup
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CTraceLookup::CTraceLookup() {
}

///////////////////////////////////////////////////////////////////////
// Class				:	CTraceLookup
// Method				:	~CTraceLookup
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CTraceLookup::~CTraceLookup() {
}


///////////////////////////////////////////////////////////////////////
// Class				:	CTransmissionLookup
// Method				:	bind
// Description			:	Bind an environment lookup parameter
// Return Value			:	-
// Comments				:
void		CTraceLookup::bind(const char *name,int &opIndex,int step,void *data,CShaderInstance *shader) {

	// Find the parameter and bind it
	if (strcmp(name,"samples") == 0) {
		add(name,opIndex,step,data,offsetof(CShadingScratch,traceParams.samples));
	} else if (strcmp(name,"bias") == 0) {
		add(name,opIndex,step,data,offsetof(CShadingScratch,traceParams.bias));
	} else if (strcmp(name,"samplecone") == 0) {
		add(name,opIndex,step,data,offsetof(CShadingScratch,traceParams.coneAngle));
	} else if (strcmp(name,"sampleBase") == 0) {
		add(name,opIndex,step,data,offsetof(CShadingScratch,traceParams.sampleBase));
	} else if (strcmp(name,"maxdist") == 0) {
		add(name,opIndex,step,data,offsetof(CShadingScratch,traceParams.maxDist));
	} else if (strcmp(name,"label") == 0) {
		expectUniform(name);
		add(name,opIndex,step,data,offsetof(CShadingScratch,traceParams.label));
	} else	CPLLookup::bind(name,opIndex,step,data,shader);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CTransmissionLookup
// Method				:	init
// Description			:	Initialize the scratch for this lookup
// Return Value			:	-
// Comments				:
void		CTraceLookup::init(CShadingScratch *scratch,const CAttributes *attributes) {

	scratch->traceParams.samples	=	1;
	scratch->traceParams.bias		=	attributes->bias;
	scratch->traceParams.coneAngle	=	0;
	scratch->traceParams.sampleBase =	1;
	scratch->traceParams.maxDist	=	C_INFINITY;
	scratch->traceParams.label		=	"";
}






///////////////////////////////////////////////////////////////////////
// Class				:	CEnvironmentLookup
// Method				:	CEnvironmentLookup
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CEnvironmentLookup::CEnvironmentLookup() {
	filter	=	RiBoxFilter;
	map		=	NULL;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CEnvironmentLookup
// Method				:	~CEnvironmentLookup
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CEnvironmentLookup::~CEnvironmentLookup() {
}


///////////////////////////////////////////////////////////////////////
// Class				:	CEnvironmentLookup
// Method				:	bind
// Description			:	Bind an environment lookup parameter
// Return Value			:	-
// Comments				:
void		CEnvironmentLookup::bind(const char *name,int &opIndex,int step,void *data,CShaderInstance *shader) {

	// Find the parameter and bind it
	if (strcmp(name,"filter") == 0) {
		expectUniform(name);
		else	filter		=	CRenderer::getFilter(((const char **) data)[0]);
	} else if (strcmp(name,"blur") == 0) {
		add(name,opIndex,step,data,offsetof(CShadingScratch,textureParams.blur));
	} else if (strcmp(name,"width") == 0) {
		expectUniform(name);
		add(name,opIndex,step,data,offsetof(CShadingScratch,textureParams.width));
	} else if (strcmp(name,"swidth") == 0) {
		expectUniform(name);
		add(name,opIndex,step,data,offsetof(CShadingScratch,textureParams.swidth));
	} else if (strcmp(name,"twidth") == 0) {
		expectUniform(name);
		add(name,opIndex,step,data,offsetof(CShadingScratch,textureParams.twidth));
	} else if (strcmp(name,"fill") == 0) {
		add(name,opIndex,step,data,offsetof(CShadingScratch,textureParams.fill));
	} else CTraceLookup::bind(name,opIndex,step,data,shader);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CEnvironmentLookup
// Method				:	init
// Description			:	Initialize the scratch for this lookup
// Return Value			:	-
// Comments				:
void		CEnvironmentLookup::init(CShadingScratch *scratch,const CAttributes *attributes) {
	scratch->textureParams.filter	=	filter;
	scratch->textureParams.samples	=	1;	// also filled in where it's used
	scratch->textureParams.blur		=	0;
	scratch->textureParams.width	=	1;
	scratch->textureParams.swidth	=	1;
	scratch->textureParams.twidth	=	1;
	scratch->textureParams.fill		=	0;
	CTraceLookup::init(scratch,attributes);
}











///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMapLookup
// Method				:	CPhotonMapLookup
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CPhotonMapLookup::CPhotonMapLookup() {
	map	=	NULL;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMapLookup
// Method				:	~CPhotonMapLookup
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CPhotonMapLookup::~CPhotonMapLookup() {
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMapLookup
// Method				:	bind
// Description			:	Bind an environment lookup parameter
// Return Value			:	-
// Comments				:
void		CPhotonMapLookup::bind(const char *name,int &opIndex,int step,void *data,CShaderInstance *shader) {

	// Find the parameter and bind it
	if (strcmp(name,"lookuptype") == 0) {
		const char	*type	=	((const char **) data)[0];
		if (strcmp(type,"irradiance") != 0) {
			error(CODE_BADTOKEN,"Photonmap lookup type \"%s\" is not supported in shader %s\n",type,shader->getName());
		}
	} else if (strcmp(name,"estimator") == 0) {
		expectUniform(name);
		add(name,opIndex,step,data,offsetof(CShadingScratch,photonmapParams.estimator));
	} else	CPLLookup::bind(name,opIndex,step,data,shader);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMapLookup
// Method				:	init
// Description			:	Initialize the scratch for this lookup
// Return Value			:	-
// Comments				:
void		CPhotonMapLookup::init(CShadingScratch *scratch,const CAttributes *attributes) {
	scratch->photonmapParams.estimator		= 0;
}




///////////////////////////////////////////////////////////////////////
// Class				:	CMapInfoLookup
// Method				:	CMapInfoLookup
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CMapInfoLookup::CMapInfoLookup() {
	map	=	NULL;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CMapInfoLookup
// Method				:	~CMapInfoLookup
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CMapInfoLookup::~CMapInfoLookup() {
}





///////////////////////////////////////////////////////////////////////
// Class				:	CTexture3dLookup
// Method				:	CTexture3dLookup
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CTexture3dLookup::CTexture3dLookup() {
	map				=	NULL;
	numChannels		=	0;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CTexture3dLookup
// Method				:	~CTexture3dLookup
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CTexture3dLookup::~CTexture3dLookup() {
}


///////////////////////////////////////////////////////////////////////
// Class				:	CTexture3dLookup
// Method				:	bind
// Description			:	Bind the texture3d/bake3d parameters
// Return Value			:	-
// Comments				:
void		CTexture3dLookup::bind(const char *name,int &opIndex,int step,void *data,CShaderInstance *shader) {

	// Find the parameter and bind it
	if (strcmp(name,"coordsystem") == 0) {
		expectUniform(name);
		add(name,opIndex,step,data,offsetof(CShadingScratch,texture3dParams.coordsys));
	} else if (strcmp(name,"interpolate") == 0) {
		expectUniform(name);
		add(name,opIndex,step,data,offsetof(CShadingScratch,texture3dParams.interpolate));
	} else if (strcmp(name,"radius") == 0) {
		add(name,opIndex,step,data,offsetof(CShadingScratch,texture3dParams.radius));
	} else if (strcmp(name,"radiusscale") == 0) {
		add(name,opIndex,step,data,offsetof(CShadingScratch,texture3dParams.radiusScale));
	} else {
		if (data == NULL) {
			// The data has to be varying

			channelIndex[numChannels]	= opIndex;
			channelSize[numChannels]	= step;
			channelName[numChannels]	= name;
			numChannels++;
		} else {
			warning(CODE_BADTOKEN,"warning, uniform texture3d parameter \"%s\" ignored\n",name);
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CTexture3dLookup
// Method				:	init
// Description			:	Initialize the scratch for this lookup
// Return Value			:	-
// Comments				:
void		CTexture3dLookup::init(CShadingScratch *scratch,const CAttributes *attributes) {
	scratch->texture3dParams.coordsys		=	"";
	scratch->texture3dParams.interpolate	=	0;
	scratch->texture3dParams.radius			=	0;
	scratch->texture3dParams.radiusScale	=	1;
}

///////////////////////////////////////////////////////////////////////
// Class				:	COcclusionLookup
// Method				:	init
// Description			:	Initialize the scratch for this lookup
// Return Value			:	-
// Comments				:
void		CTexture3dLookup::postBind(CShadingScratch *scratch) {
	if (scratch->texture3dParams.coordsys[0] == '\0') {
		scratch->texture3dParams.coordsys = "world";
	}
}




///////////////////////////////////////////////////////////////////////
// Class				:	COcclusionLookup
// Method				:	COcclusionLookup
// Description			:	Ctor
// Return Value			:	-
// Comments				:
COcclusionLookup::COcclusionLookup() {
	environment		=	NULL;
	pointHierarchy	=	NULL;
}

///////////////////////////////////////////////////////////////////////
// Class				:	COcclusionLookup
// Method				:	~COcclusionLookup
// Description			:	Dtor
// Return Value			:	-
// Comments				:
COcclusionLookup::~COcclusionLookup() {
}


///////////////////////////////////////////////////////////////////////
// Class				:	COcclusionLookup
// Method				:	bind
// Description			:	Bind the indirectdiffuse/occlusion parameters
// Return Value			:	-
// Comments				:
void		COcclusionLookup::bind(const char *name,int &opIndex,int step,void *data,CShaderInstance *shader) {

	// Find the parameter and bind it
	if (strcmp(name,"coordsystem") == 0) {
		expectUniform(name);
		add(name,opIndex,step,data,offsetof(CShadingScratch,texture3dParams.coordsys));
	} else if (strcmp(name,"maxdist") == 0) {
		add(name,opIndex,step,data,offsetof(CShadingScratch,traceParams.maxDist));
	} else if (strcmp(name,"coneangle") == 0) {
		add(name,opIndex,step,data,offsetof(CShadingScratch,traceParams.coneAngle));
	} else if (strcmp(name,"samplebase") == 0) {
		add(name,opIndex,step,data,offsetof(CShadingScratch,traceParams.sampleBase));
	} else if (strcmp(name,"label") == 0) {
		add(name,opIndex,step,data,offsetof(CShadingScratch,traceParams.label));
	} else if (strcmp(name,"bias") == 0) {
		add(name,opIndex,step,data,offsetof(CShadingScratch,traceParams.bias));
	} else if (strcmp(name,"maxerror") == 0) {
		add(name,opIndex,step,data,offsetof(CShadingScratch,occlusionParams.maxError));
	} else if (strcmp(name,"pointbased") == 0) {
		expectUniform(name);
		add(name,opIndex,step,data,offsetof(CShadingScratch,occlusionParams.pointbased));
	} else if (strcmp(name,"environmentmap") == 0) {
		expectUniform(name);
		// This is a uniform parameter
		add(name,opIndex,step,data,offsetof(CShadingScratch,occlusionParams.environmentMapName));
	} else if (strcmp(name,"filename") == 0) {
		expectUniform(name);
		add(name,opIndex,step,data,offsetof(CShadingScratch,occlusionParams.pointHierarchyName));
	} else if (strcmp(name,"maxpixeldist") == 0) {
		add(name,opIndex,step,data,offsetof(CShadingScratch,occlusionParams.maxPixelDist));
	} else if (strcmp(name,"maxsolidangle") == 0) {
		add(name,opIndex,step,data,offsetof(CShadingScratch,occlusionParams.maxSolidAngle));
	} else if (strcmp(name,"environmentcolor") == 0) {
		add(name,opIndex,step,data,offsetof(CShadingScratch,occlusionParams.environmentColor));
	} else if (strcmp(name,"maxBrightness") == 0) {
		add(name,opIndex,step,data,offsetof(CShadingScratch,occlusionParams.maxBrightness));
	} else if (strcmp(name,"handle") == 0) {
		expectUniform(name);
		// This is a uniform parameter
		add(name,opIndex,step,data,offsetof(CShadingScratch,occlusionParams.cacheHandle));
	} else if (strcmp(name,"filemode") == 0) {
		expectUniform(name);
		// This is a uniform parameter
		add(name,opIndex,step,data,offsetof(CShadingScratch,occlusionParams.cacheMode));
	} else {
		if (data == NULL) {
			// The data has to be varying

			channelIndex[numChannels]	= opIndex;
			channelSize[numChannels]	= step;
			channelName[numChannels]	= name;
			numChannels++;
		} else {
			warning(CODE_BADTOKEN,"Warning, uniform occlusion / indirectdiffuse parameter \"%s\" ignored\n",name);
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	COcclusionLookup
// Method				:	init
// Description			:	Initialize the scratch for this lookup
// Return Value			:	-
// Comments				:
void		COcclusionLookup::init(CShadingScratch *scratch,const CAttributes *attributes) {
	scratch->occlusionParams.environmentMapName	=	NULL;					// None by default
	scratch->texture3dParams.coordsys			=	"";
	scratch->occlusionParams.maxError			=	attributes->irradianceMaxError;
	scratch->occlusionParams.pointbased			=	0;						// This is not a point based lookup
	scratch->occlusionParams.maxBrightness		=	1.0f;					// Upper limit on the maximum brightness
	scratch->occlusionParams.environmentMapName	=	NULL;					// No environment map by default
	scratch->occlusionParams.pointHierarchyName	=	NULL;					// No point hierarchy
	scratch->occlusionParams.maxPixelDist		=	attributes->irradianceMaxPixelDistance;		// The maximum distance between samples
	scratch->occlusionParams.maxSolidAngle		=	0.05f;					// The maximum solid angle
	scratch->occlusionParams.occlusion			=	FALSE;					// Overwritten on the fly
	initv(scratch->occlusionParams.environmentColor,0);						// The background color for irradiance
	scratch->occlusionParams.pointHierarchy		=	NULL;					// Overwritten on the fly
	scratch->occlusionParams.environment		=	NULL;					// Overwritten on the fly
	scratch->occlusionParams.cacheHandle		=	attributes->irradianceHandle;				// Use the attribute by default
	scratch->occlusionParams.cacheMode			=	attributes->irradianceHandleMode;			// Use the attribute by default
	
	scratch->traceParams.samples				=	1;
	scratch->traceParams.maxDist				=	C_INFINITY;
	scratch->traceParams.coneAngle				=	0;
	scratch->traceParams.sampleBase				=	1;
	scratch->traceParams.label					=	"";
	scratch->traceParams.bias					=	attributes->bias;

}

///////////////////////////////////////////////////////////////////////
// Class				:	COcclusionLookup
// Method				:	init
// Description			:	Initialize the scratch for this lookup
// Return Value			:	-
// Comments				:
void		COcclusionLookup::postBind(CShadingScratch *scratch) {
	if (scratch->texture3dParams.coordsys[0] == '\0') {
		scratch->texture3dParams.coordsys = "world";
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CFilterLookup
// Method				:	CFilterLookup
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CFilterLookup::CFilterLookup() {
	filter		=	RiCatmullRomStepFilter;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFilterLookup
// Method				:	~CFilterLookup
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CFilterLookup::~CFilterLookup() {
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFilterLookup
// Method				:	bind
// Description			:	Bind the filterstep parameters
// Return Value			:	-
// Comments				:
void		CFilterLookup::bind(const char *name,int &opIndex,int step,void *data,CShaderInstance *shader) {

	// Find the parameter and bind it
	if (strcmp(name,"filter") == 0) {
		expectUniform(name);
		else				filter		=	CRenderer::getStepFilter(((const char **) data)[0]);
	} else if (strcmp(name,"width") == 0) {
		expectUniform(name);
		add(name,opIndex,step,data,offsetof(CShadingScratch,textureParams.width));
	} else	CPLLookup::bind(name,opIndex,step,data,shader);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFilterLookup
// Method				:	init
// Description			:	Initialize the scratch for this lookup
// Return Value			:	-
// Comments				:
void		CFilterLookup::init(CShadingScratch *scratch,const CAttributes *attributes) {
	scratch->textureParams.width		=	1.0f;
}










///////////////////////////////////////////////////////////////////////
// Class				:	CShaderVectorVariable
// Description			:	Encapsulates a shader variable
// Comments				:
class	CShaderVectorVariable : public CGatherVariable {
public:

			void	record(float *dest,int nr,CGatherRay **r,float **varying) {
						const float	*src	=	varying[entry];

						for (int i=nr;i>0;--i,src+=3) {
							const CGatherRay	*ray	=	(CGatherRay *) (*r++);
							movvv(dest + ray->index*3,src);
						}
					}

			int		entry;		// Variable index
};

///////////////////////////////////////////////////////////////////////
// Class				:	CShaderFloatVariable
// Description			:	Encapsulates a shader variable
// Comments				:
class	CShaderFloatVariable : public CGatherVariable {
public:

			void	record(float *dest,int nr,CGatherRay **r,float **varying) {
						const float	*src	=	varying[entry];

						for (int i=nr;i>0;--i) {
							const CGatherRay	*ray	=	(CGatherRay *) (*r++);

							dest[ray->index]	=	*src++;
						}
					}

			int		entry;		// Variable index
};

///////////////////////////////////////////////////////////////////////
// Class				:	CRayOriginVariable
// Description			:	Ray origin variable
// Comments				:
class	CRayOriginVariable : public CGatherVariable {
public:

			void	record(float *dest,int nr,CGatherRay **r,float **varying) {

						for (int i=nr;i>0;--i) {
							const CGatherRay	*ray	=	(CGatherRay *) (*r++);

							movvv(dest + ray->index*3,ray->from);
						}
					}
};

///////////////////////////////////////////////////////////////////////
// Class				:	CRayDirVariable
// Description			:	Ray direction variable
// Comments				:
class	CRayDirVariable : public CGatherVariable {
public:

			void	record(float *dest,int nr,CGatherRay **r,float **varying) {

						for (int i=nr;i>0;--i) {
							const CGatherRay	*ray	=	(CGatherRay *) (*r++);

							movvv(dest + ray->index*3,ray->dir);
						}
					}
};

///////////////////////////////////////////////////////////////////////
// Class				:	CRayLengthVariable
// Description			:	Ray length variable
// Comments				:
class	CRayLengthVariable : public CGatherVariable {
public:

			void	record(float *dest,int nr,CGatherRay **r,float **varying) {

						for (int i=nr;i>0;--i) {
							const CGatherRay	*ray	=	(CGatherRay *) (*r++);

							dest[ray->index]	=	ray->t;
						}
					}
};


///////////////////////////////////////////////////////////////////////
// Class				:	CGatherLookup
// Method				:	CGatherLookup
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CGatherLookup::CGatherLookup() {
	outputs				=	NULL;
	numOutputs			=	0;
	nonShadeOutputs		=	NULL;
	numNonShadeOutputs	=	0;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CGatherLookup
// Method				:	~CGatherLookup
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CGatherLookup::~CGatherLookup() {
	CGatherVariable	*cVar;

	while((cVar=outputs) != NULL) {
		outputs	=	cVar->next;
		delete cVar;
	}

	while((cVar=nonShadeOutputs) != NULL) {
		nonShadeOutputs	=	cVar->next;
		delete cVar;
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CGatherLookup
// Method				:	addOutput
// Description			:	Adds an output
// Return Value			:	-
// Comments				:
void	CGatherLookup::addOutput(const char *output,int destIndex,CShaderInstance *shader) {
	CGatherVariable	*nVar	=	NULL;

	if (strncmp(output,"surface:",8) == 0) {
		CVariable				*var	=	CRenderer::retrieveVariable(output+8);
		if (var == NULL)							error(CODE_BADTOKEN,"Variable \"%s\" is not found in shader %s\n",output,shader->getName());
		else if (var->storage != STORAGE_GLOBAL)	error(CODE_BADTOKEN,"Variable \"%s\" is not found in shader %s\n",output,shader->getName());
		else {
			if (	(var->type == TYPE_VECTOR)	||
					(var->type == TYPE_POINT)	||
					(var->type == TYPE_COLOR)	||
					(var->type == TYPE_NORMAL)) {
				CShaderVectorVariable	*outVar	=	new CShaderVectorVariable;
				outVar->shade		=	TRUE;
				outVar->entry		=	var->entry;
				outVar->destIndex	=	destIndex;
				outVar->next		=	outputs;
				outputs				=	outVar;
				numOutputs++;
				nVar				=	outVar;
			} else if (var->type == TYPE_FLOAT) {
				CShaderFloatVariable	*outVar	=	new CShaderFloatVariable;
				outVar->shade		=	TRUE;
				outVar->entry		=	var->entry;
				outVar->destIndex	=	destIndex;
				outVar->next		=	outputs;
				outputs				=	outVar;
				numOutputs++;
				nVar				=	outVar;
			} else {
				error(CODE_BADTOKEN,"Unknown output variable type for gather in shader %s\n",shader->getName());
			}
		}
	} else if (strcmp(output,"ray:origin") == 0) {
		CRayOriginVariable	*outVar	=	new CRayOriginVariable;
		outVar->destIndex	=	destIndex;
		outVar->next		=	nonShadeOutputs;
		nonShadeOutputs		=	outVar;
		numNonShadeOutputs++;
		nVar				=	outVar;
	} else if (strcmp(output,"ray:direction") == 0) {
		CRayDirVariable	*outVar	=	new CRayDirVariable;
		outVar->destIndex	=	destIndex;
		outVar->next		=	nonShadeOutputs;
		nonShadeOutputs		=	outVar;
		numNonShadeOutputs++;
		nVar				=	outVar;
	} else if (strcmp(output,"ray:length") == 0) {
		CRayLengthVariable	*outVar	=	new CRayLengthVariable;
		outVar->destIndex	=	destIndex;
		outVar->next		=	nonShadeOutputs;
		nonShadeOutputs		=	outVar;
		numNonShadeOutputs++;
		nVar				=	outVar;
	} else {
		error(CODE_BADTOKEN,"Unknown output variable for gather in shader %s\n",shader->getName());
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CGatherLookup
// Method				:	bind
// Description			:	Bind variables
// Return Value			:	-
// Comments				:
void	CGatherLookup::bind(const char *name,int &opIndex,int step,void *data,CShaderInstance *shader) {
	// Find the parameter and bind it
	if (strcmp(name,"bias") == 0) {
		add(name,opIndex,step,data,offsetof(CShadingScratch,traceParams.bias));
	} else if (strcmp(name,"maxdist") == 0) {
		add(name,opIndex,step,data,offsetof(CShadingScratch,traceParams.maxDist));
	} else if (strcmp(name,"samplebase") == 0) {
		add(name,opIndex,step,data,offsetof(CShadingScratch,traceParams.sampleBase));
	} else if (strcmp(name,"distribution") == 0) {
		expectUniform(name);
		add(name,opIndex,step,data,offsetof(CShadingScratch,gatherParams.distribution));
	} else if (strcmp(name,"label") == 0) {
		expectUniform(name);
		add(name,opIndex,step,data,offsetof(CShadingScratch,traceParams.label));
	} else {
		addOutput(name,opIndex,shader);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CGatherLookup
// Method				:	init
// Description			:	Init the gather parameters
// Return Value			:	-
// Comments				:
void	CGatherLookup::init(CShadingScratch *scratch,const CAttributes *attributes) {
	scratch->traceParams.samples		=	1;
	scratch->traceParams.bias			=	attributes->bias;
	scratch->gatherParams.distribution	=	NULL;
	scratch->traceParams.sampleBase		=	1;
	scratch->traceParams.maxDist		=	C_INFINITY;
	scratch->traceParams.label			=	rayLabelGather;
}
