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
//  File				:	shader.cpp
//  Classes				:	CShader
//							CShaderInstance
//  Description			:	Implementation
//
////////////////////////////////////////////////////////////////////////
#include	<math.h>
#include	<stdio.h>
#include	<string.h>

#include	"error.h"
#include	"shader.h"
#include	"stats.h"
#include	"shading.h"
#include	"bundles.h"
#include	"memory.h"
#include	"renderer.h"
#include	"attributes.h"
#include	"common/align.h"


///////////////////////////////////////////////////////////////////////	
// Class				:	CShader
// Method				:	CShader
// Description			:	Constructor
// Return Value			:	-
// Comments				:
CShader::CShader(const char *name) : CFileResource(name) {
	atomicIncrement(&stats.numShaders);

	name					=	NULL;
	memory					=	NULL;
	codeArea				=	NULL;
	constantEntries			=	NULL;
	varyingSizes			=	NULL;
	strings					=	NULL;
	parameters				=	NULL;
	flags					=	0;
	data					=	NULL;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShader
// Method				:	~CShader
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CShader::~CShader() {
	int			i;
	CVariable	*cParameter;

	atomicDecrement(&stats.numShaders);

	// Ditch the parameters
	while((cParameter = parameters) != NULL) {
		parameters	=	parameters->next;

		// Delete the default values
		if (cParameter->defaultValue != NULL)	delete [] (float *) cParameter->defaultValue;

		// Delete the parameter
		delete cParameter;
	}

	// Delete the strings allocated for this shader
	for (i=0;i<numStrings;i++) {
		free(strings[i]);
	}

	// Delete additional data
	if (data != NULL)		delete data;

	// Ditch the memory baby
	if (memory != NULL)					free_untyped(memory);
}



///////////////////////////////////////////////////////////////////////
// Class				:	CShader
// Method				:	analyse
// Description			:	work out if there are special parameters
// Return Value			:	-
// Comments				:
void CShader::analyse() {
	CVariable	*cVariable;
	int			varIndex	=	numGlobals-1;

	// BEWARE that this is reversed compareed to the instance order 
	// hence the reversed counting of globalIndex
	for (cVariable=parameters;cVariable!=NULL;cVariable=cVariable->next) {
		// Check for special parameters
		if (cVariable->storage == STORAGE_MUTABLEPARAMETER || cVariable->storage == STORAGE_GLOBAL) {
			if (type == SL_LIGHTSOURCE) {
				if (!strcmp(cVariable->name,"__nondiffuse")) {
					if ((cVariable->numItems == 1) && cVariable->type == TYPE_FLOAT) {
						flags				|=	 SHADERFLAGS_NONDIFFUSE;
						
						if (data == NULL)	data = new CLightShaderData;
						CLightShaderData *lightData = (CLightShaderData*) data;
						
						lightData->nonDiffuseIndex	=	varIndex;
						lightData->nonDiffuseStep	=	((cVariable->container == CONTAINER_CONSTANT) || (cVariable->container == CONTAINER_UNIFORM)) ? 0 : 1;
					} else {
						warning(CODE_BADTOKEN,"warning type mismatch for expected definition of __nondiffuse in shader \"%s\"",name);
					}
				} else if (!strcmp(cVariable->name,"__nonspecular")) {
					if ((cVariable->numItems == 1) && cVariable->type == TYPE_FLOAT) {
						flags				|=	 SHADERFLAGS_NONSPECULAR;
						
						if (data == NULL)	data = new CLightShaderData;
						CLightShaderData *lightData = (CLightShaderData*) data;
						
						lightData->nonSpecularIndex	=	varIndex;
						lightData->nonSpecularStep	=	((cVariable->container == CONTAINER_CONSTANT) || (cVariable->container == CONTAINER_UNIFORM)) ? 0 : 1;
					} else {
						warning(CODE_BADTOKEN,"warning type mismatch for expected definition of __nonspecular in shader \"%s\"",name);
					}
				}
			}
			varIndex--;
		}
	}

	if (usedParameters & PARAMETER_NONAMBIENT)
		flags				|=	 SHADERFLAGS_NONAMBIENT;
}



///////////////////////////////////////////////////////////////////////
// Class				:	CShaderInstance
// Method				:	CShaderInstance
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CShaderInstance::CShaderInstance(CAttributes *a,CXform *x) {
	atomicIncrement(&stats.numShaderInstances);

	attach();

	xform		=	x;
	xform->attach();
	
	categories	=	NULL;
	parameters	=	NULL;	// The children class may want to clone the parent's parameters here
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShaderInstance
// Method				:	CShaderInstance
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CShaderInstance::~CShaderInstance() {
	atomicDecrement(&stats.numShaderInstances);

	xform->detach();
	
	if (categories != NULL)	delete[] categories;

	// Note: data is not owned by the instance
	
	// The children class must clear the parameter list here
}



///////////////////////////////////////////////////////////////////////
// Function				:	getToken
// Description			:	This function implements "strsep" which is non portable
// Return Value			:
// Comments				:
static char	*token(char **str,const char *tok) {
	char	*cStr	=	*str;
	char	*oStr	=	cStr;
	int		n		=	(int) strlen(tok);
	int		i;

	if (cStr == NULL)	return NULL;

	// Walk the string
	for (;;) {

		// Did we run out of string ?
		if (*cStr == '\0') {
			*str	=	NULL;
			break;
		}

		// Check for a delimiter
		for (i=0;i<n;i++) {
			if (*cStr == tok[i]) break;
		}

		if (i == n)	cStr++;
		else {
			// Delimiter found, terminate
			*cStr	=	'\0';
			*str	=	cStr+1;
			break;
		}
	}

	return oStr;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShaderInstance
// Method				:	CShaderInstance
// Description			:	Ctor
// Return Value			:	-
// Comments				:
void CShaderInstance::createCategories() {
	char	*categoryString,*cCat,*tmp;
	int		i,numCategories;

	if (getParameter("__category",&categoryString,NULL,NULL) == TRUE) {
		tmp = categoryString = strdup(categoryString);
		
		numCategories = 2;
		while (*tmp!='\0') {
			if (*tmp == ',') numCategories++;
			tmp++;
		}
		tmp = categoryString;
		
		categories = new int[numCategories];
		
		i=0;
		do {
			cCat = token(&tmp,",\t ");
			if (*cCat != '\0') categories[i++] = CRenderer::getGlobalID(cCat);
		} while (tmp != NULL);
		categories[i++] = 0;	// terminate the list
		
		free(categoryString);
	}
}










///////////////////////////////////////////////////////////////////////
// Class				:	CProgrammableShaderInstance
// Method				:	CProgrammableShaderInstance
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CProgrammableShaderInstance::CProgrammableShaderInstance(CShader *p,CAttributes *a,CXform *x) : CShaderInstance(a,x) {
	CVariable	*cVariable;

	strings				=	NULL;
	parent				=	p;
	flags				=	parent->flags;
	data				=	parent->data;

	// Clone the parent's parameter list
	// BEWARE that this reverses the order (which matters when counting the globalIndex)
	for (cVariable=parent->parameters;cVariable!=NULL;cVariable=cVariable->next) {
		CVariable	*nVariable	=	new CVariable;

		*nVariable		=	*cVariable;
		nVariable->next	=	parameters;
		parameters		=	nVariable;

		// Allocate a new default value
		if (nVariable->type == TYPE_STRING) {
			nVariable->defaultValue	=	new char *[nVariable->numFloats];
			memcpy(nVariable->defaultValue,cVariable->defaultValue,nVariable->numFloats*sizeof(char*));
		} else {
			nVariable->defaultValue	=	new float[nVariable->numFloats];
			memcpy(nVariable->defaultValue,cVariable->defaultValue,nVariable->numFloats*sizeof(float));
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CProgrammableShaderInstance
// Method				:	~CProgrammableShaderInstance
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CProgrammableShaderInstance::~CProgrammableShaderInstance() {
	CVariable			*cParameter;
	CAllocatedString	*cString;

	// Ditch the parameters
	while((cParameter = parameters) != NULL) {
		parameters	=	parameters->next;

		// Delete the default values
		if (cParameter->defaultValue != NULL) {
			if (cParameter->type == TYPE_STRING)		delete [] (char**) cParameter->defaultValue;
			else										delete [] (float*) cParameter->defaultValue;
		}

		// Delete the parameter
		delete cParameter;
	}

	// Ditch the allocated strings
	while((cString = strings) != NULL) {
		strings	=	cString->next;

		free(cString->string);
		delete cString;
	}

}


///////////////////////////////////////////////////////////////////////
// Class				:	CProgrammableShaderInstance
// Method				:	setParameters
// Description			:	Set the values of the parameters
// Return Value			:	-
// Comments				:
int	CProgrammableShaderInstance::setParameter(const char *param,const void *val) {
	CVariable	*cParameter;

	for (cParameter=parameters;cParameter!=NULL;cParameter=cParameter->next) {

		if (strcmp(param,cParameter->name) == 0) {
			switch(cParameter->type) {
			case TYPE_FLOAT:
				{
					const float	*src	=	(const float *) val;
					float		*dest	=	(float *)		cParameter->defaultValue;
					memcpy(dest,src,cParameter->numItems*sizeof(float));
				}
				break;
			case TYPE_COLOR:
				{
					int			p;
					const float	*src	=	(const float *) val;
					float		*dest	=	(float *)		cParameter->defaultValue;

					for (p=cParameter->numItems;p>0;p--,dest+=3,src+=3) {
						movvv(dest,src);
					}
				}
				break;
			case TYPE_VECTOR:
				{
					int			p;
					const float	*src	=	(const float *) val;
					float		*dest	=	(float *)		cParameter->defaultValue;

					for (p=cParameter->numItems;p>0;p--,dest+=3,src+=3) {
						mulmv(dest,xform->from,src);
					}
				}
				break;
			case TYPE_NORMAL:
				{
					int			p;
					const float	*src	=	(const float *) val;
					float		*dest	=	(float *)		cParameter->defaultValue;

					for (p=cParameter->numItems;p>0;p--,dest+=3,src+=3) {
						mulmn(dest,xform->to,src);
					}
				}
				break;
			case TYPE_POINT:
				{
					int			p;
					const float	*src	=	(const float *) val;
					float		*dest	=	(float *)		cParameter->defaultValue;

					for (p=cParameter->numItems;p>0;p--,dest+=3,src+=3) {
						mulmp(dest,xform->from,src);
					}
				}
				break;
			case TYPE_MATRIX:
				{
					const float	*src	=	(const float *) val;
					float		*dest	=	(float *)		cParameter->defaultValue;
					memcpy(dest,src,cParameter->numItems*sizeof(matrix));
				}
				break;
			case TYPE_QUAD:
				{
					const float	*src	=	(const float *) val;
					float		*dest	=	(float *)		cParameter->defaultValue;
					memcpy(dest,src,cParameter->numItems*sizeof(float)*4);
				}
				break;
			case TYPE_DOUBLE:
				{
					const float	*src	=	(const float *) val;
					float		*dest	=	(float *)		cParameter->defaultValue;
					memcpy(dest,src,cParameter->numItems*sizeof(float)*2);
				}
				break;
			case TYPE_STRING:
				{
					const char			**src	=	(const char **) val;
					char				**dest	=	(char **)		cParameter->defaultValue;
					int					t;
					CAllocatedString	*nString;

					for (t=cParameter->numItems;t>0;t--) {

						nString			=	new CAllocatedString;
						nString->string	=	strdup(*src++);
						nString->next	=	strings;
						strings			=	nString;

						*dest++			=	nString->string;
					}
				}
				break;
			case TYPE_INTEGER:
				{
					// This should not be possible
					error(CODE_BUG,"Integer shader variable in shader \"%s\"\n",parent->name);
					const int	*src	=	(const int *)	val;
					int			*dest	=	(int *)			cParameter->defaultValue;
					memcpy(dest,src,cParameter->numItems*sizeof(int));
				}
				break;
			default:
				break;
			}

			break;
		}
	}

	return cParameter != NULL;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CProgrammableShaderInstance
// Method				:	setParameters
// Description			:	Set the values of the parameters
// Return Value			:	-
// Comments				:
void	CProgrammableShaderInstance::setParameters(int np,const char **params,const void **vals) {
	int	i;


	// Set the parameter defaults
	for (i=0;i<np;i++) {
		if (setParameter(params[i],vals[i]) == FALSE) {
			CVariable	var;

			if (parseVariable(&var,NULL,params[i]) == TRUE) {
				if (setParameter(var.name,vals[i]) == FALSE) {
					error(CODE_BADTOKEN,"Parameter \"%s\" not found in the shader\n",var.name);
				}
			} else {
				error(CODE_BADTOKEN,"Parameter \"%s\" not found in the shader\n",params[i]);
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CProgrammableShaderInstance
// Method				:	getParameter
// Description			:	Get the current value of a parameter
// Return Value			:	TRUE if successful, FALSE othervise
// Comments				:	The second void * must be float *
//							if the type of the parameter is float/vector/matrix
//							and char ** if the type of the parameter is string.
//							iff var or globalIndex is NULL, we skip any parameters
//							which are mutable
int		CProgrammableShaderInstance::getParameter(const char *name,void *dest,CVariable **var,int *globalIndex) {
	int							j;
	int							globalNumber = 0;
	float						*destFloat;
	const float					*srcFloat;
	const char					**destString;
	const char					**srcString;
	int							*destInt;
	const int					*srcInt;
	CVariable					*cParameter;

	// BEWARE!
	// the instance parameters are stored in the opposite order to the
	// parent shader parameters.  The counting scheme for globals used here must
	// match that used when saving lights.  In both cases, we loop the instance
	// not the parent parameters
	
	for (cParameter=parameters;cParameter!=NULL;cParameter=cParameter->next) {

		// retrieve the storage in which the parameter lives
		const int storage = cParameter->storage;
		if (strcmp(name,cParameter->name) == 0) {

			// Note: all parameters have storage, but for lights
			// all we have to save in the light cache are the mutable ones
			// We also only return defaults for interior and exterior (var == NULL)
			if (!(storage == STORAGE_PARAMETER && parent->type == SL_LIGHTSOURCE) && (var != NULL) && (globalIndex != NULL)) {
				*var			=	cParameter;
				*globalIndex	=	globalNumber;
				return TRUE;
			}

			switch(cParameter->type) {
			case TYPE_FLOAT:
				destFloat	=	(float *)		dest;
				srcFloat	=	(const float *)	cParameter->defaultValue;
				for (j=cParameter->numItems;j>0;j--)
					*destFloat++	=	*srcFloat++;
				break;
			case TYPE_COLOR:
			case TYPE_VECTOR:
			case TYPE_NORMAL:
			case TYPE_POINT:
				destFloat	=	(float *)		dest;
				srcFloat	=	(const float *)	cParameter->defaultValue;
				for (j=cParameter->numItems;j>0;j--,destFloat+=3,srcFloat+=3)
					movvv(destFloat,srcFloat);
				break;
			case TYPE_MATRIX:
				destFloat	=	(float *)		dest;
				srcFloat	=	(const float *)	cParameter->defaultValue;
				for (j=cParameter->numItems;j>0;j--,destFloat+=16,srcFloat+=16)
					movmm(destFloat,srcFloat);
				break;
			case TYPE_QUAD:
				destFloat	=	(float *)		dest;
				srcFloat	=	(const float *)	cParameter->defaultValue;
				for (j=cParameter->numItems;j>0;j--,destFloat+=4,srcFloat+=4)
					movqq(destFloat,srcFloat);
				break;
			case TYPE_DOUBLE:
				destFloat	=	(float *)		dest;
				srcFloat	=	(const float *)	cParameter->defaultValue;
				for (j=cParameter->numItems;j>0;j--) {
					*destFloat++	=	*srcFloat++;
					*destFloat++	=	*srcFloat++;
				}
				break;
			case TYPE_STRING:
				destString	=	(const char **) dest;
				srcString	=	(const char **)	cParameter->defaultValue;
				for (j=cParameter->numItems;j>0;j--)
					*destString++	=	*srcString++;
				break;
			case TYPE_INTEGER:
				// This should not be possible
				error(CODE_BUG,"Integer shader variable in shader \"%s\"\n",name);
				destInt		=	(int *)			dest;
				srcInt		=	(const int *)	cParameter->defaultValue;
				for (j=cParameter->numItems;j>0;j--)
					*destInt++	=	*srcInt++;
				break;
			default:
				break;
			}

			return	TRUE;
		} else {
			if (!(storage == STORAGE_PARAMETER && parent->type == SL_LIGHTSOURCE))	globalNumber++;
		}
	}

	return FALSE;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CProgrammableShaderInstance
// Method				:	execute
// Description			:	Actually execute the shader
// Return Value			:	-
// Comments				:
void			CProgrammableShaderInstance::execute(CShadingContext *context,float **locals) {
	context->execute(this,locals);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CProgrammableShaderInstance
// Method				:	requiredParameters
// Description			:	Return the required parameters
// Return Value			:	-
// Comments				:
unsigned int	CProgrammableShaderInstance::requiredParameters() {
	return parent->usedParameters;
}



///////////////////////////////////////////////////////////////////////
// Class				:	CProgrammableShaderInstance
// Method				:	getName
// Description			:	Get the name of the shader
// Return Value			:	-
// Comments				:
const char		*CProgrammableShaderInstance::getName() {
	return parent->name;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CProgrammableShaderInstance
// Method				:	illuminate
// Description			:	Illuminate the shading state is a lightsource shader
// Return Value			:	-
// Comments				:
void			CProgrammableShaderInstance::illuminate(CShadingContext *context,float **locals) {

	// This function should never be called for non-light shaders
	assert(parent->type == SL_LIGHTSOURCE);
	context->execute(this,locals);
}



///////////////////////////////////////////////////////////////////////
// Class				:	CProgrammableShaderInstance
// Method				:	prepare
// Description			:	Allocate the cache and set the parameter defaults
// Return Value			:	-
// Comments				:
float			**CProgrammableShaderInstance::prepare(CMemPage *&namedMemory,float **varying,int numVertices) {
	CVariable	*cVariable;
	char		*data;
	float		**locals;
	int			totalVaryingSize;
	int			i;

	// Get const pointers for fast access
	const int	numVariables	=	parent->numVariables;
	const int	*varyingSizes	=	parent->varyingSizes;

	// Compute the total memory we will need for the shader parameters
	for (totalVaryingSize=0,i=0;i<numVariables;i++) {
		if (varyingSizes[i] < 0)	totalVaryingSize	+=	-varyingSizes[i];
		else						totalVaryingSize	+=	varyingSizes[i]*numVertices*3;
	}

	// Allocate memory for the temporary shader variables
	// Allocate some extra space for alignment
	data	=	(char *) ralloc(totalVaryingSize + numVariables*(sizeof(float *) + sizeof(float)),namedMemory);
	locals	=	(float **) data;
	data	+=	numVariables*sizeof(float*);

	// Save the memory
	for (i=0;i<numVariables;i++) {

		// Align the data to 64 bits
		data	=	(char *) align64(data);

		locals[i]	=	(float*) data;
		if (varyingSizes[i] < 0)	data	+=	-varyingSizes[i];
		else						data	+=	varyingSizes[i]*numVertices*3;
	}

	// For each parameter, copy over the default value of the parameter
	for (cVariable=parameters;cVariable!=NULL;cVariable=cVariable->next) {
		float		*destf;
		const float	*srcf;
		const char	**dests;
		const char	**srcs;
		
		// Find where we're writing
		if (cVariable->storage == STORAGE_GLOBAL)	{
			destf					=	(float *) varying[cVariable->entry];
			dests					=	(const char **) varying[cVariable->entry];
		} else {
			assert(cVariable->entry < numVariables);
			destf					=	(float *) locals[cVariable->entry];
			dests					=	(const char **) locals[cVariable->entry];
		}

		// This is the repetition amount
		if ((cVariable->container == CONTAINER_UNIFORM) || (cVariable->container == CONTAINER_CONSTANT)) {

			//assert(cVariable->numFloats == -parent->varyingSizes[cVariable->entry]);

			if (cVariable->type == TYPE_STRING) {
				if ((srcs = (const char **) cVariable->defaultValue) != NULL) {
					int	i;
					for (i=cVariable->numFloats;i>0;i--)	*dests++	=	*srcs++;
				}
			} else {
				if ((srcf = (const float *) cVariable->defaultValue) != NULL) {
					int	i;
					for (i=cVariable->numFloats;i>0;i--)	*destf++	=	*srcf++;
				}
			}
		} else {

			//assert(cVariable->numFloats == parent->varyingSizes[cVariable->entry]);
			
			if (cVariable->type == TYPE_STRING) {
				if ((srcs = (const char **) cVariable->defaultValue) != NULL) {
					int			n;
					const int	c	=	cVariable->numFloats;

					// FIXME: We may want to unroll these two loops
					for(n=numVertices*3;n>0;n--) {
						for (i=0;i<c;i++)	*dests++	=	srcs[i];
					}
				}
			} else {
				if ((srcf = (const float *) cVariable->defaultValue) != NULL) {
					int			n;
					const int	c	=	cVariable->numFloats;

					// FIXME: We may want to unroll these two loops
					for(n=numVertices*3;n>0;n--) {
						for (i=0;i<c;i++)	*destf++	=	srcf[i];
					}
				}
			}
		}
	}

	return (float **) locals;
}






///////////////////////////////////////////////////////////////////////
// Function				:	debugFunction
// Description			:	This function is used to debugging purposes
// Return Value			:	-
// Comments				:	You can trigger this function from the compiled shader
//							code by debug ("f=o")
void	debugFunction(float *op) {
	fprintf(stderr,"Debug\n");
}

