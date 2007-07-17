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
#include "common/algebra.h"
#include "common/os.h"
#include "shaderPl.h"
#include "rendererc.h"
#include "bundles.h"
#include "error.h"
#include "variable.h"
#include "renderer.h"

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
	size			=	0;
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
void	CPLLookup::bind(const char *name,int &opIndex,int step) {
	error(CODE_BADTOKEN,"Unknown parameter: \"%s\"\n",name);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPLLookup
// Method				:	add
// Description			:	Add a parameter
// Return Value			:	-
// Comments				:
void	CPLLookup::add(const char *name,int &opIndex,int step,size_t dest) {
	TParamBinding	*cBinding;

	if (step == 0)	cBinding	=	uniforms + numUniforms++;
	else			cBinding	=	varyings + numVaryings++;

	cBinding->name		=	name;
	cBinding->opIndex	=	opIndex++;
	cBinding->step		=	step;
	cBinding->dest		=	dest;
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
void	CGatherLookup::addOutput(const char *output,int destIndex) {
	CGatherVariable	*nVar	=	NULL;

	if (strncmp(output,"surface:",8) == 0) {
		CVariable				*var	=	CRenderer::retrieveVariable(output+8);
		if (var == NULL)							error(CODE_BADTOKEN,"Variable %s not found\n",output);
		else if (var->storage != STORAGE_GLOBAL)	error(CODE_BADTOKEN,"Variable %s not found\n",output);
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
				error(CODE_BADTOKEN,"Unknown output variable type for gather\n");
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
		error(CODE_BADTOKEN,"Unknown output variable for gather\n");
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CTexture3dLookup
// Method				:	CTexture3dLookup
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CTexture3dLookup::CTexture3dLookup() {
	numChannels			=	0;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CGlobalIllumLookup
// Method				:	~CGlobalIllumLookup
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CTexture3dLookup::~CTexture3dLookup() {
}

