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
//  File				:	shader.cpp
//  Classes				:	CShader
//							CShaderInstance
//  Description			:	Implementation
//
////////////////////////////////////////////////////////////////////////
#include	<math.h>
#include	<stdio.h>
#include	<string.h>

#include	"renderer.h"
#include	"error.h"
#include	"shader.h"
#include	"stats.h"
#include	"shading.h"
#include	"cache.h"
#include	"bundles.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CShaderLookup
// Method				:	CShaderLookup
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	3/10/2001
CShaderLookup::CShaderLookup() {
}


///////////////////////////////////////////////////////////////////////
// Class				:	CShaderLookup
// Method				:	~CShaderLookup
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	3/10/2001
CShaderLookup::~CShaderLookup() {
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFilterLookup
// Method				:	compute
// Description			:	Lookup filter values at discrete intelvals
// Return Value			:	-
// Comments				:
// Date last edited		:	3/10/2001
void	CFilterLookup::compute() {
	int		i;
	float	val;

	valStep		=	2*width / (NUMFILTERSTEPS-1);
	val			=	width;
	normalizer	=	0;

	for (i=0;i<NUMFILTERSTEPS;i++,val-=valStep) {
		vals[i]		=	filter(val,0,width,1);
		normalizer	+=	vals[i]*valStep;
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShaderVectorVariable
// Method				:	record
// Description			:
// Return Value			:	-
// Comments				:
// Date last edited		:	3/23/2003
void	CShaderVectorVariable::record(int nr,CGatherRay **r,float **varying) {
	int		i;
	float	*src	=	varying[entry];

	for (i=nr;i>0;i--,src+=3) {
		CGatherRay	*ray	=	(CGatherRay *) (*r++);

		movvv((float *) dest + ray->index*3,src);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShaderVectorVariable
// Method				:	record
// Description			:
// Return Value			:	-
// Comments				:
// Date last edited		:	3/23/2003
void	CShaderFloatVariable::record(int nr,CGatherRay **r,float **varying) {
	int		i;
	float	*src	=	varying[entry];

	for (i=nr;i>0;i--) {
		CGatherRay	*ray	=	(CGatherRay *) (*r++);

		dest[ray->index].real	=	*src++;
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CShaderVectorVariable
// Method				:	record
// Description			:
// Return Value			:	-
// Comments				:
// Date last edited		:	3/23/2003
void	CRayOriginVariable::record(int nr,CGatherRay **r,float **varying) {
	int		i;

	for (i=nr;i>0;i--) {
		CGatherRay	*ray	=	(CGatherRay *) (*r++);

		movvv((float *) dest + ray->index*3,ray->from);
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CShaderVectorVariable
// Method				:	record
// Description			:
// Return Value			:	-
// Comments				:
// Date last edited		:	3/23/2003
void	CRayDirVariable::record(int nr,CGatherRay **r,float **varying) {
	int		i;

	for (i=nr;i>0;i--) {
		CGatherRay	*ray	=	(CGatherRay *) (*r++);

		movvv((float *) dest + ray->index*3,ray->dir);
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CShaderVectorVariable
// Method				:	record
// Description			:
// Return Value			:	-
// Comments				:
// Date last edited		:	3/23/2003
void	CRayLengthVariable::record(int nr,CGatherRay **r,float **varying) {
	int		i;

	for (i=nr;i>0;i--) {
		CGatherRay	*ray	=	(CGatherRay *) (*r++);

		dest[ray->index].real	=	ray->t;
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CGatherLookup
// Method				:	CGatherLookup
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	3/23/2003
CGatherLookup::CGatherLookup() {
	outputs			=	NULL;
	nonShadeOutputs	=	NULL;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CGatherLookup
// Method				:	~CGatherLookup
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	3/23/2003
CGatherLookup::~CGatherLookup() {
	CGatherVariable	*cVar;

	while((cVar=outputs) != NULL) {
		outputs	=	cVar->next;
		if (cVar->destForEachLevel != NULL) delete [] cVar->destForEachLevel;
		delete cVar;
	}

	while((cVar=nonShadeOutputs) != NULL) {
		nonShadeOutputs	=	cVar->next;
		if (cVar->destForEachLevel != NULL) delete [] cVar->destForEachLevel;
		delete cVar;
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CGatherLookup
// Method				:	addOutput
// Description			:	Adds an output
// Return Value			:	-
// Comments				:
// Date last edited		:	3/23/2003
void	CGatherLookup::addOutput(const char *output,int destIndex) {
	CGatherVariable	*nVar	=	NULL;

	if (strncmp(output,"surface:",8) == 0) {
		CVariable				*var	=	currentRenderer->retrieveVariable(output+8);
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
				nVar				=	outVar;
			} else if (var->type == TYPE_FLOAT) {
				CShaderFloatVariable	*outVar	=	new CShaderFloatVariable;
				outVar->shade		=	TRUE;
				outVar->entry		=	var->entry;
				outVar->destIndex	=	destIndex;
				outVar->next		=	outputs;
				outputs				=	outVar;
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
		nVar				=	outVar;
	} else if (strcmp(output,"ray:direction") == 0) {
		CRayDirVariable	*outVar	=	new CRayDirVariable;
		outVar->destIndex	=	destIndex;
		outVar->next		=	nonShadeOutputs;
		nonShadeOutputs		=	outVar;
		nVar				=	outVar;
	} else if (strcmp(output,"ray:length") == 0) {
		CRayLengthVariable	*outVar	=	new CRayLengthVariable;
		outVar->destIndex	=	destIndex;
		outVar->next		=	nonShadeOutputs;
		nonShadeOutputs		=	outVar;
		nVar				=	outVar;
	} else {
		error(CODE_BADTOKEN,"Unknown output variable for gather\n");
	}

	if (nVar != NULL) {
		nVar->destForEachLevel	=	new TCode*[maxRayDepth+1];
		nVar->cDepth			=	nVar->destForEachLevel;
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CGlobalIllumLookup
// Method				:	CGlobalIllumLookup
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	3/10/2001
CGlobalIllumLookup::CGlobalIllumLookup() {
}

///////////////////////////////////////////////////////////////////////
// Class				:	CGlobalIllumLookup
// Method				:	~CGlobalIllumLookup
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	3/10/2001
CGlobalIllumLookup::~CGlobalIllumLookup() {
	if (cache != NULL) cache->finalize(this);
}

///////////////////////////////////////////////////////////////////////	
// Class				:	CShader
// Method				:	CShader
// Description			:	Constructor
// Return Value			:	-
// Comments				:
// Date last edited		:	3/10/2001
CShader::CShader(const char *name) : CFileResource(name) {
	stats.numShaders++;

	name					=	NULL;
	memory					=	NULL;
	codeArea				=	NULL;
	constantsArea			=	NULL;
	constantEntries			=	NULL;
	varyingSizes			=	NULL;
	strings					=	NULL;
	parameters				=	NULL;
	cache					=	NULL;
	dirty					=	FALSE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShader
// Method				:	~CShader
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	3/10/2001
CShader::~CShader() {
	int			i;
	CVariable	*cParameter;

	stats.numShaders--;

	// Ditch the parameters
	while((cParameter = parameters) != NULL) {
		parameters	=	parameters->next;

		// Delete the default values
		if (cParameter->defaultValue != NULL)	delete [] (TCode *) cParameter->defaultValue;

		// Delete the parameter
		delete cParameter;
	}

	// Delete the strings allocated for this shader
	for (i=0;i<numStrings;i++) {
		free(strings[i]);
	}

	// Ditch the memory baby
	if (memory != NULL)					delete [] memory;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShader
// Method				:	nullify
// Description			:	This function must make sure the shader can never execute again
// Return Value			:
// Comments				:	
// Date last edited		:	3/10/2001
void	CShader::nullify() {
	codeEntryPoint	=	-1;
	initEntryPoint	=	-1;
}



///////////////////////////////////////////////////////////////////////
// Class				:	CShaderInstance
// Method				:	CShaderInstance
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	3/10/2001
CShaderInstance::CShaderInstance(CAttributes *a,CXform *x) {
	stats.numShaderInstances++;

	refCount	=	1;
	xform		=	x;
	xform->attach();
	
	categories	=	NULL;
	parameters	=	NULL;	// FIXME: Clone the parent's parameters here
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShaderInstance
// Method				:	CShaderInstance
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	3/10/2001
CShaderInstance::~CShaderInstance() {
	stats.numShaderInstances--;

	xform->detach();
	
	if (categories != NULL)	delete[] categories;

	// FIXME: Delete the parameters here
}



///////////////////////////////////////////////////////////////////////
// Function				:	getToken
// Description			:	This function implements "strsep" which is non portable
// Return Value			:
// Comments				:
// Date last edited		:	10/1/2005
static char	*token(char **str,char *tok) {
	char	*cStr	=	*str;
	char	*oStr	=	cStr;
	int		n		=	strlen(tok);
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
// Date last edited		:	3/10/2001
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
			if (*cCat != '\0') categories[i++] = currentRenderer->getGlobalID(cCat);
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
// Date last edited		:	3/10/2001
CProgrammableShaderInstance::CProgrammableShaderInstance(CShader *p,CAttributes *a,CXform *x) : CShaderInstance(a,x) {
	int			i;
	CVariable	*cVariable;

	strings				=	NULL;
	parent				=	p;
	
	if (parent->numPLs > 0) {
		parameterLists	=	new CShaderLookup*[parent->numPLs];

		for (i=0;i<parent->numPLs;i++)
			parameterLists[i]	=	NULL;
	} else {
		parameterLists	=	NULL;
	}

	// Clone the parent's parameter list
	for (cVariable=parent->parameters;cVariable!=NULL;cVariable=cVariable->next) {
		CVariable	*nVariable	=	new CVariable;

		*nVariable		=	*cVariable;
		nVariable->next	=	parameters;
		parameters		=	nVariable;

		// Allocate a new default value
		nVariable->defaultValue	=	new TCode[nVariable->numFloats];
		memcpy(nVariable->defaultValue,cVariable->defaultValue,nVariable->numFloats*sizeof(TCode));
	}

	flags				=	(parent->usedParameters & PARAMETER_NONAMBIENT) ? SHADERFLAGS_NONAMBIENT : 0;
	dirty				=	FALSE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CProgrammableShaderInstance
// Method				:	~CProgrammableShaderInstance
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	3/10/2001
CProgrammableShaderInstance::~CProgrammableShaderInstance() {
	CVariable			*cParameter;
	CAllocatedString	*cString;

	// Ditch the parameters
	while((cParameter = parameters) != NULL) {
		parameters	=	parameters->next;

		// Delete the default values
		if (cParameter->defaultValue != NULL)	delete [] (TCode *) cParameter->defaultValue;

		// Delete the parameter
		delete cParameter;
	}

	// Ditch the allocated strings
	while((cString = strings) != NULL) {
		strings	=	cString->next;

		free(cString->string);
		delete cString;
	}

	if (parameterLists != NULL) {
#ifdef _DEBUG
		int	i;

		for (i=0;i<parent->numPLs;i++) {
			assert(parameterLists[i] == NULL);
		}

		assert(dirty == FALSE);
#endif

		delete [] parameterLists;
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CProgrammableShaderInstance
// Method				:	setParameters
// Description			:	Set the values of the parameters
// Return Value			:	-
// Comments				:
// Date last edited		:	3/10/2001
int	CProgrammableShaderInstance::setParameter(char *param,void *val) {
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

					for (p=0;p<cParameter->numItems;p++) {
						movvv(dest,src);
						dest	+=	3;
						src		+=	3;
					}
				}
				break;
			case TYPE_VECTOR:
				{
					int			p;
					const float	*src	=	(const float *) val;
					float		*dest	=	(float *)		cParameter->defaultValue;

					for (p=0;p<cParameter->numItems;p++) {
						mulmv(dest,xform->from,src);
						dest	+=	3;
						src		+=	3;
					}
				}
				break;
			case TYPE_NORMAL:
				{
					int			p;
					const float	*src	=	(const float *) val;
					float		*dest	=	(float *)		cParameter->defaultValue;

					for (p=0;p<cParameter->numItems;p++) {
						mulmn(dest,xform->to,src);
						dest	+=	3;
						src		+=	3;
					}
				}
				break;
			case TYPE_POINT:
				{
					int			p;
					const float	*src	=	(const float *) val;
					float		*dest	=	(float *)		cParameter->defaultValue;

					for (p=0;p<cParameter->numItems;p++) {
						mulmp(dest,xform->from,src);
						dest	+=	3;
						src		+=	3;
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

					for (t=0;t<cParameter->numItems;t++) {

						nString			=	new CAllocatedString;
						nString->string	=	strdup(*src++);
						nString->next	=	strings;
						strings			=	nString;

						*dest++			=	nString->string;
					}
				}
				break;
			case TYPE_INTEGER:
			case TYPE_BOOLEAN:
				{
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
// Date last edited		:	3/10/2001
void	CProgrammableShaderInstance::setParameters(int np,char **params,void **vals) {
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
// Date last edited		:	3/10/2001
int		CProgrammableShaderInstance::getParameter(const char *name,void *dest,CVariable **var,int *globalIndex) {
	int							j,storage,globalNumber = 0;
	float						*destFloat;
	float						*srcFloat;
	const char					**destString;
	const char					**srcString;
	int							*destInt;
	int							*srcInt;
	CVariable					*cParameter;

	for (cParameter=parameters;cParameter!=NULL;cParameter=cParameter->next) {
		// retrieve the storage in which the parameter lives
		storage = cParameter->storage;
		if (strcmp(name,cParameter->name) == 0) {

			// Note: ll parameters have storage, but for lights
			// all we have to save in the light cache are the mutable ones
			// We also only return defaults for interior and exterior (var == NULL)
			if (!(storage == STORAGE_PARAMETER && parent->type == SL_LIGHTSOURCE) && (var != NULL) && (globalIndex != NULL)) {
				*var			=	cParameter;
				*globalIndex	=	globalNumber;
				return TRUE;
			}

			switch(cParameter->type) {
			case TYPE_FLOAT:
				destFloat	=	(float *)	dest;
				srcFloat	=	(float *)	cParameter->defaultValue;
				for (j=0;j<cParameter->numItems;j++)
					*destFloat++	=	*srcFloat++;
				break;
			case TYPE_COLOR:
			case TYPE_VECTOR:
			case TYPE_NORMAL:
			case TYPE_POINT:
				destFloat	=	(float *)	dest;
				srcFloat	=	(float *)	cParameter->defaultValue;
				for (j=0;j<cParameter->numItems*3;j++)
					*destFloat++	=	*srcFloat++;
				break;
			case TYPE_MATRIX:
				destFloat	=	(float *)	dest;
				srcFloat	=	(float *)	cParameter->defaultValue;
				for (j=0;j<cParameter->numItems*16;j++)
					*destFloat++	=	*srcFloat++;
				break;
			case TYPE_QUAD:
				destFloat	=	(float *)	dest;
				srcFloat	=	(float *)	cParameter->defaultValue;
				for (j=0;j<cParameter->numItems*4;j++)
					*destFloat++	=	*srcFloat++;
				break;
			case TYPE_DOUBLE:
				destFloat	=	(float *)	dest;
				srcFloat	=	(float *)	cParameter->defaultValue;
				for (j=0;j<cParameter->numItems*2;j++)
					*destFloat++	=	*srcFloat++;
				break;
			case TYPE_STRING:
				destString	=	(const char **) dest;
				srcString	=	(const char **)	cParameter->defaultValue;
				for (j=0;j<cParameter->numItems;j++)
					*destString++	=	*srcString++;
				break;
			case TYPE_INTEGER:
			case TYPE_BOOLEAN:
				destInt		=	(int *)		dest;
				srcInt		=	(int *)		cParameter->defaultValue;
				for (j=0;j<cParameter->numItems;j++)
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
// Date last edited		:	3/10/2001
void			CProgrammableShaderInstance::execute(CShadingContext *context) {
	context->execute(this);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CProgrammableShaderInstance
// Method				:	requiredParameters
// Description			:	Return the required parameters
// Return Value			:	-
// Comments				:
// Date last edited		:	3/10/2001
unsigned int	CProgrammableShaderInstance::requiredParameters() {
	return parent->usedParameters;
}



///////////////////////////////////////////////////////////////////////
// Class				:	CProgrammableShaderInstance
// Method				:	getName
// Description			:	Get the name of the shader
// Return Value			:	-
// Comments				:
// Date last edited		:	3/10/2001
const char		*CProgrammableShaderInstance::getName() {
	return parent->name;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CProgrammableShaderInstance
// Method				:	illuminate
// Description			:	Illuminate the shading state is a lightsource shader
// Return Value			:	-
// Comments				:
// Date last edited		:	3/10/2001
void			CProgrammableShaderInstance::illuminate(CShadingContext *context) {
	// This function should never be called for non-light shaders
	context->execute(this);
}



///////////////////////////////////////////////////////////////////////
// Class				:	CProgrammableShaderInstance
// Method				:	prepareCache
// Description			:	Allocate the cache and set the parameter defaults
// Return Value			:	-
// Comments				:
// Date last edited		:	5/24/2006
void			CProgrammableShaderInstance::prepareCache(CShadingContext *context,int numVertices,float ***accessor) {
	CVariable		*cVariable;
	const TCode		*src;
	TCode			*dest;
	int				i,n,c;
	CShaderCache	*cache;
	TCode			**varying	=	(TCode**) context->currentShadingState->varying;

	// Make sure the parent has a shader cache
	if (parent->cache == NULL)	parent->cache	=	context->newCache(parent);
	cache	=	parent->cache;

	// For each parameter, copy over the default value of the parameter
	for (cVariable=parameters;cVariable!=NULL;cVariable=cVariable->next) {
	
		// This is the repetition amount
		if ((cVariable->container == CONTAINER_UNIFORM) || (cVariable->container == CONTAINER_CONSTANT)) {
			n				=	1;
		} else {
			n				=	numVertices*3;
		}
		
		if (cVariable->storage == STORAGE_GLOBAL) {
			dest			=	varying[cVariable->entry];
		} else {
			dest			=	cache->varyings[cVariable->entry];
		}
		
		cVariable->value	=	(float *) dest;
		src					=	(const TCode *) cVariable->defaultValue;
		c					=	cVariable->numFloats;

		// Copy the parameters
		for(;n>0;n--) {
			for (i=0;i<c;i++)	*dest++	=	src[i];
		}
	}
	// Install the accessor for the message passing
	*accessor = (float**) cache->varyings;
}






///////////////////////////////////////////////////////////////////////
// Function				:	debugFunction
// Description			:	This function is used to debugging purposes
// Return Value			:	-
// Comments				:
// Date last edited		:	2/4/2003
void	debugFunction(float *op) {
	fprintf(stderr,"Debug\n");
}
