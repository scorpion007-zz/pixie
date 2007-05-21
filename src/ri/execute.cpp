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
//  File				:	execute.cpp
//  Classes				:	-
//  Description			:	This file implements the main shader execution
//
////////////////////////////////////////////////////////////////////////
#include <math.h>
#include <float.h>

#include "common/global.h"
#include "memory.h"
#include "shader.h"
#include "slcode.h"
#include "shading.h"
#include "noise.h"
#include "photonMap.h"
#include "texture3d.h"
#include "irradiance.h"
#include "bundles.h"
#include "error.h"
#include "renderer.h"
#include "surface.h"
#include "texture.h"
#include "ri_config.h"

// This function is defined in shader.cpp for debugging purposes
void							debugFunction(float *);

// These functions are defined in init.cpp
void							convertColorFrom(float *,const float *,ECoordinateSystem);
void							convertColorTo(float *,const float *,ECoordinateSystem);


// Parameter list helpers
struct CTempParamBinding {
	CShaderLookup::CParamBinding	binding;
	CTempParamBinding				*next;
};

#define initParamBindings(__lookup)												\
	CTempParamBinding *__paramBindingsStart = NULL;								\
	CTempParamBinding *__paramBindingsEnd	= NULL;
	
#define addParamBinding(__lookup,__start,__type,__dest)	{												\
	CTempParamBinding *__param = (CTempParamBinding *) ralloc(sizeof(CTempParamBinding),threadMemory);	\
	if (__paramBindingsEnd == NULL) __paramBindingsEnd = __paramBindingsStart = __param;				\
	else __paramBindingsEnd->next = __param;															\
	__param->next = NULL;																				\
	__param->binding.opIndex = i*2+__start+1;															\
	__param->binding.dest = &__lookup->__dest;															\
	__param->binding.type = 	__type;																	\
	__lookup->numParamBindings++;																		\
}

#define completeParamBindings(__lookup)	{																				\
	__lookup->paramBindings = new CShaderLookup::CParamBinding[__lookup->numParamBindings];								\
	CShaderLookup::CParamBinding 	*cBinding		= __lookup->paramBindings;											\
	CTempParamBinding				*cTempBinding	= __paramBindingsStart;												\
	while (cTempBinding != NULL) {																						\
		memcpy(cBinding,cTempBinding,sizeof(CShaderLookup::CParamBinding));												\
		cBinding++;																										\
		cTempBinding = cTempBinding->next;																				\
	}																													\
}


#define getUniformParams(__lookup) {										\
	CShaderLookup::CParamBinding *cParamBind = __lookup->paramBindings;		\
	for(int o=0;o<__lookup->numParamBindings;o++,cParamBind++){				\
		switch(cParamBind->type) {											\
			case TYPE_INTEGER:												\
				{															\
				const float *optmp;											\
				operand(cParamBind->opIndex,optmp,const float *);			\
				*((int*)cParamBind->dest) = (int) *optmp;					\
				}															\
				break;														\
			case TYPE_FLOAT:												\
				{															\
				const float *optmp;											\
				operand(cParamBind->opIndex,optmp,const float *);			\
				*((float*)cParamBind->dest) = *optmp;						\
				}															\
				break;														\
			default:														\
				break;														\
		}																	\
	}																		\
}

// Lighting helpers
#define	saveLighting(__L)																	\
	if (numActive != 0) {																	\
		CShadedLight	*cLight		= 	NULL;												\
		const int		numGlobals	=	cInstance->parent->numGlobals;						\
		if (*freeLights != NULL) {															\
			cLight					= *freeLights;											\
			*freeLights				= (*freeLights)->next;									\
			float**		savedState	= (float**) ralloc((2+numGlobals)*sizeof(float*),threadMemory);		\
			savedState[0]			= cLight->savedState[0];								\
			savedState[1]			= cLight->savedState[1];								\
			cLight->savedState		= savedState;											\
		} else {																			\
			cLight					= (CShadedLight*) ralloc(sizeof(CShadedLight),threadMemory);		\
			cLight->lightTags		= (int*)	ralloc(sizeof(int)*numVertices,threadMemory);			\
			cLight->savedState		= (float**) ralloc((2+numGlobals)*sizeof(float*),threadMemory);		\
			cLight->savedState[0]	= (float*)	ralloc(3*sizeof(float)*numVertices,threadMemory);		\
			cLight->savedState[1]	= (float*)	ralloc(3*sizeof(float)*numVertices,threadMemory);		\
			cLight->instance		= cInstance;											\
		}																					\
		cLight->next			= *lights;													\
		*lights					= cLight;													\
		memcpy(cLight->lightTags,tagStart,sizeof(int)*numVertices);							\
		memcpy(cLight->savedState[1],varying[VARIABLE_CL],3*sizeof(float)*numVertices);		\
		__L						= cLight->savedState[0];									\
		/*save extra variables if needed*/													\
		if (numGlobals != 0) {																\
			int							globNum		=	0;									\
			CVariable					*cVariable;											\
			for (cVariable=cInstance->parameters;cVariable!=NULL;cVariable=cVariable->next) {	\
				if (cVariable->storage == STORAGE_GLOBAL) {									\
					/* globals come from the global varyings */								\
					if ((cVariable->container == CONTAINER_UNIFORM) || (cVariable->container == CONTAINER_CONSTANT)) {					\
						cLight->savedState[2+globNum]  =	(float*) ralloc(sizeof(float)*cVariable->numFloats,threadMemory);			\
						memcpy(cLight->savedState[2+globNum],varying[cVariable->entry],sizeof(float)*cVariable->numFloats);				\
					} else {																											\
						cLight->savedState[2+globNum]  =	(float*) ralloc(sizeof(float)*cVariable->numFloats*numVertices,threadMemory);	\
						memcpy(cLight->savedState[2+globNum],varying[cVariable->entry],sizeof(float)*cVariable->numFloats*numVertices);		\
					}																		\
					globNum++;																\
				} else if (cVariable->storage == STORAGE_MUTABLEPARAMETER) {				\
					/* mutable parameters come from the shader varyings */					\
					if ((cVariable->container == CONTAINER_UNIFORM) || (cVariable->container == CONTAINER_CONSTANT)) {										\
						cLight->savedState[2+globNum]  =	(float*) ralloc(sizeof(float)*cVariable->numFloats,threadMemory);								\
						memcpy(cLight->savedState[2+globNum],stuff[SL_VARYING_OPERAND][cVariable->entry],sizeof(float)*cVariable->numFloats);				\
					} else {																																\
						cLight->savedState[2+globNum]  =	(float*) ralloc(sizeof(float)*cVariable->numFloats*numVertices,threadMemory);					\
						memcpy(cLight->savedState[2+globNum],stuff[SL_VARYING_OPERAND][cVariable->entry],sizeof(float)*cVariable->numFloats*numVertices);	\
					}																		\
					globNum++;																\
				}																			\
			}																				\
		}																					\
	}

#define clearLighting() {												\
	currentShadingState->lightsExecuted = FALSE;						\
	*freeLights		=	*lights;										\
	*lights			=	NULL;											\
}

#define enterLightingConditional() {									\
	int			tmpTag;													\
	const int	*lightTags	=	(*currentLight)->lightTags;				\
	tags			=	tagStart;										\
	for (i=numVertices;i>0;i--,tags++,lightTags++) {					\
		tmpTag = (*tags == 0);											\
		*tags += *lightTags;											\
		if (tmpTag && *tags) {											\
			numActive--;												\
			numPassive++;												\
		}																\
	}																	\
	tags = tagStart;													\
}

#define exitLightingConditional() {										\
	int			tmpTag;													\
	const int	*lightTags	= (*currentLight)->lightTags;				\
	tags			=	tagStart;										\
	for (i=numVertices;i>0;i--,tags++,lightTags++) {					\
		tmpTag = *tags;													\
		*tags -= *lightTags;											\
		if (tmpTag && (*tags == 0)) {									\
			numActive++;												\
			numPassive--;												\
		}																\
	}																	\
	tags = tagStart;													\
}

#define enterFastLightingConditional() {								\
	const int *lightTags	=	(*currentLight)->lightTags;				\
	tags			=	tagStart;										\
	for (i=numVertices;i>0;i--) {										\
		(*tags++) += (*lightTags++);									\
	}																	\
	tags = tagStart;													\
}

#define exitFastLightingConditional() {									\
	const int *lightTags	= (*currentLight)->lightTags;				\
	tags			=	tagStart;										\
	for (i=numVertices;i>0;i--) {										\
		(*tags++) -= (*lightTags++);									\
	}																	\
	tags = tagStart;													\
}







///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	execute
// Description			:	Execute a shader
// Return Value			:	-
// Comments				:
void	CShadingContext::execute(CProgrammableShaderInstance *cInstance,float **locals) {
// At this point, the shader sends us the arrays for parameters/constants/variables/uniforms for the shader

#define		scripterror(mes)				{																	\
												CRenderer::offendingObject	=	currentShadingState->currentObject;	\
												error(CODE_SCRIPT,"\"%s\", (nullified)\n",mes);					\
												cInstance->parent->codeEntryPoint	=	-1;						\
												cInstance->parent->initEntryPoint	=	-1;						\
												goto	execEnd;												\
											}
//	Allocate temporary memory for the string and save it
#define		savestring(r,n)					{																	\
												const int	strLen	=	(int) strlen(n) + 1;					\
												const int	strSize	=	(strLen & ~3) + 4;						\
												char		*strmem	=	(char *) ralloc(strSize,threadMemory);	\
												strcpy(strmem,n);												\
												r				=	strmem;										\
											}

//	Begin a conditional block execution
#define		beginConditional()				if (conditionals == NULL) {											\
												conditionals		=	new CConditional;						\
												conditionals->next	=	NULL;									\
												conditionals->prev	=	NULL;									\
											}																	\
																												\
											conditionals->prev		=	lastConditional;						\
											lastConditional			=	conditionals;							\
											conditionals			=	lastConditional->next;
											

//	End a conditional block execution
#define		endConditional()				lastConditional->next	=	conditionals;							\
											conditionals			=	lastConditional;						\
											lastConditional			=	lastConditional->prev;

//	Retrieve a pointer to an operand and obtain it's size
#define		operand(i,n,t)					{																	\
												const TArgument	*ref	=	code->arguments + i;				\
												n	= (t) stuff[ref->accessor][ref->index];						\
											}

//	Retrieve an operand's size
#define		operandSize(i,n,s,t)			{																	\
												const TArgument	*ref	=	code->arguments + i;				\
												n	= (t) stuff[ref->accessor][ref->index];						\
												s	= ref->numItems;											\
											}

#define		operandNumItems(i)				code->arguments[i].numItems

#define		operandBytesPerItem(i)			code->arguments[i].bytesPerItem

// Retrieve the parameterlist
#define		parameterlist					cInstance->parameterLists[code->plNumber]

#define		dirty()							if (cInstance->dirty == FALSE) {										\
												osLock(CRenderer::dirtyShaderMutex);								\
												cInstance->dirty			=	TRUE;								\
												cInstance->nextDirty		=	CRenderer::dirtyInstances;			\
												cInstance->prevDirty		=	NULL;								\
												if (CRenderer::dirtyInstances != NULL)								\
													CRenderer::dirtyInstances->prevDirty	=	cInstance;			\
												CRenderer::dirtyInstances	=	cInstance;							\
												osUnlock(CRenderer::dirtyShaderMutex);								\
											}

//	Retrieve an integer operand (label references are integer)
#define		argument(i)						code->arguments[i].index

//	Retrieve the number of arguments
#define		argumentcount(n)				n = code->numArguments

//	Control transfer
#define		jmp(n)							{																\
												code		=	currentShader->codeArea + n;				\
												goto execStart;												\
											}

//	Expand the results from primary shading points to all
#define		expandVector(__res)				if (numVertices != currentShadingState->numRealVertices) {		\
												const float	*src	=	__res - currentShadingState->numRealVertices*3;			\
												for (int i=currentShadingState->numRealVertices;i>0;i--) {						\
													movvv(__res,src);	__res	+=	3;	src	+=	3;			\
													movvv(__res,src);	__res	+=	3;	src	+=	3;			\
												}															\
											}

//	Expand the results from primary shading points to all
#define		expandFloat(__res)				if (numVertices != currentShadingState->numRealVertices) {		\
												const float	*src	=	__res - currentShadingState->numRealVertices;			\
												for (int i=currentShadingState->numRealVertices;i>0;i--) {						\
													*__res++	=	*src++;									\
													*__res++	=	*src++;									\
												}															\
											}


//	Run the ambient light source shaders for the lP
#define		runAmbientLights()				if (!currentShadingState->ambientLightsExecuted) {				\
												const CAttributes		*currentAttributes	=	currentShadingState->currentObject->attributes;	\
												float					*Clsave;							\
												int						i;									\
																											\
												assert((numActive+numPassive) == numVertices);				\
												assert(numVertices == currentShadingState->numVertices);	\
												currentShadingState->numActive				=	numActive;	\
												currentShadingState->numPassive				=	numPassive;	\
												currentShadingState->ambientLightsExecuted	=	TRUE;		\
																											\
												if (*alights == NULL) {										\
													*alights					=		(CShadedLight*)	ralloc(sizeof(CShadedLight),threadMemory);				\
													(*alights)->savedState		=		(float**)		ralloc(2*sizeof(CShadedLight),threadMemory);			\
													(*alights)->savedState[1]	=		(float*)		ralloc(3*sizeof(float)*numVertices,threadMemory);		\
													(*alights)->savedState[0]	=		NULL;			/* ambient lights do not use tags or save L */			\
													(*alights)->lightTags		=		NULL;				\
													(*alights)->instance		=		NULL;				\
													(*alights)->next			=		NULL;				\
																											\
													Clsave	= (*alights)->savedState[1];					\
													for (i=numVertices;i>0;i--,Clsave+=3) {					\
														initv(Clsave,0);									\
													}														\
												}															\
																											\
												if (inShadow == FALSE) {									\
													CActiveLight			*cLight;						\
																											\
													for (cLight=currentAttributes->lightSources;cLight!=NULL;cLight=cLight->next) {	\
														CProgrammableShaderInstance	*light	=	cLight->light;						\
														if (!(light->flags & SHADERFLAGS_NONAMBIENT)) {								\
															memBegin(shaderStateMemory);											\
															currentShadingState->currentLightInstance			=	light;			\
															currentShadingState->locals[ACCESSOR_LIGHTSOURCE]	=	light->prepare(shaderStateMemory,varying,numVertices);	\
															light->illuminate(this,currentShadingState->locals[ACCESSOR_LIGHTSOURCE]);										\
															memEnd(shaderStateMemory);						\
														}													\
													}														\
												}															\
												assert(currentShadingState->numActive	==	numActive);		\
												assert(currentShadingState->numPassive	==	numPassive);	\
																											\
												currentShadingState->currentShaderInstance	=	cInstance;	\
											}


//	Run the light source shaders for the lP
#define		runLightsTemplate(lP,lN,lT,lightCategoryPre,lightCategoryCheck)									\
											int curLightingValid = currentShadingState->lightsExecuted;		\
											lightCategoryPre;												\
											if (curLightingValid) {											\
												const int	*aTag	=	tagStart;							\
												const int	*lTag	=	currentShadingState->lightingTags;	\
												int			i;												\
												curLightingValid = curLightingValid && 						\
													(currentShadingState->lightCategory == saveCat);		\
												/* memcmp is faster than a T32/xor/compare loop here */		\
												/* note: we should really only need to compare active */	\
												/*  shading points, but it's faster to compare all */		\
												curLightingValid = curLightingValid &&						\
													!memcmp(lN,currentShadingState->Ns,sizeof(float)*3*numVertices) &&		\
													!memcmp(lP,varying[VARIABLE_PS],sizeof(float)*3*numVertices) &&			\
													!memcmp(lT,currentShadingState->costheta,sizeof(float)*numVertices);	\
												/* we must still compare active tags, note this isn't */					\
												/* the same as tags being numerically equal */								\
												for (i=numVertices; curLightingValid && (i>0); i--) {						\
													curLightingValid = curLightingValid && (!*aTag++ & !*lTag++);			\
												}																			\
											}																\
											if (!curLightingValid) { 										\
												const CAttributes	*currentAttributes	=	currentShadingState->currentObject->attributes;	\
												assert((numActive+numPassive) == numVertices);				\
												assert(numVertices == currentShadingState->numVertices);	\
												currentShadingState->numActive		=	numActive;			\
												currentShadingState->numPassive		=	numPassive;			\
												currentShadingState->lightsExecuted	=	TRUE;				\
												currentShadingState->costheta		=	lT;					\
												currentShadingState->lightCategory	=	saveCat;			\
												/* memcpy is faster than a loop here */						\
												memcpy(varying[VARIABLE_PS],lP,numVertices*3*sizeof(float));					\
												memcpy(currentShadingState->Ns,lN,numVertices*3*sizeof(float));					\
												memcpy(currentShadingState->lightingTags,tagStart,numVertices*sizeof(int));		\
																											\
												/* clear all lights */										\
												*freeLights 	=	*lights;								\
												*lights			=	NULL;									\
																											\
												if (inShadow == FALSE) {									\
													CActiveLight			*cLight;						\
																											\
													for (cLight=currentAttributes->lightSources;cLight!=NULL;cLight=cLight->next) {		\
														CProgrammableShaderInstance	*light	=	cLight->light;							\
														lightCategoryCheck;																\
														if (light->flags & SHADERFLAGS_NONAMBIENT) {									\
															memBegin(shaderStateMemory);												\
															currentShadingState->currentLightInstance			=	light;				\
															currentShadingState->locals[ACCESSOR_LIGHTSOURCE]	=	light->prepare(shaderStateMemory,varying,numVertices);	\
															light->illuminate(this,currentShadingState->locals[ACCESSOR_LIGHTSOURCE]);										\
															memEnd(shaderStateMemory);						\
														}													\
													}														\
												}															\
												assert(currentShadingState->numActive	==	numActive);		\
												assert(currentShadingState->numPassive	==	numPassive);	\
																											\
												currentShadingState->currentShaderInstance	=	cInstance;	\
											}

#define		CATEGORYLIGHT_PRE(lC)			int	runCat = 0,saveCat = 0;										\
											int	invertCatMatch = FALSE;										\
											if (*(*lC) != '\0') {											\
												if (*(*lC) == '-') {										\
													saveCat = -(runCat = CRenderer::getGlobalID(*lC+1));	\
													invertCatMatch = TRUE;									\
												} else {													\
													saveCat = runCat = CRenderer::getGlobalID(*lC);			\
												}															\
											}

#define		CATEGORYLIGHT_CHECK				if (light->categories != NULL) {								\
												int			validLight = FALSE;								\
												const int	*cCat;											\
												for (cCat=light->categories;(*cCat!=0);cCat++) {			\
													if (*cCat == runCat) {									\
														validLight = TRUE;									\
														break;												\
													}														\
												}															\
												if (invertCatMatch) {										\
													if (validLight)		continue;							\
												} else {													\
													if (!validLight)	continue;							\
												}															\
											} else if (!invertCatMatch) {									\
												continue;													\
											}

#define		runCategoryLights(lP,lN,lT,lC)	runLightsTemplate(lP,lN,lT,CATEGORYLIGHT_PRE(lC),CATEGORYLIGHT_CHECK)

#define		NORMALLIGHT_PRE					int saveCat = 0;

#define		runLights(lP,lN,lT)				runLightsTemplate(lP,lN,lT,NORMALLIGHT_PRE,NULL_EXPR)

// The misc macros
#define		DEFLINKOPCODE(name,text,nargs)				case OPCODE_##name:		
#define		DEFLINKFUNC(name,text,prototype,par)		case FUNCTION_##name:

// Break the shader execution
#define		BREAK							goto execEnd;



	//	The	shading variables and junk
	void						**stuff[3];			// Where we keep pointers to the variables
	CConditional				*lastConditional;	// The last conditional
	int							numActive;			// The number of active points being shaded
	int							numPassive;			// The number of passive points being not shaded (numPassive+numActive = numVertices)
	int							*tags;				// Execution tags
	int							*tagStart;
	int							currentVertex;		// The current vertex being executed
	CShader						*currentShader			=	cInstance->parent;
	const TCode					*code;
	int							numVertices;
	float						**varying;
	CShadedLight				**lights;
	CShadedLight				**alights;
	CShadedLight				**currentLight;
	CShadedLight				**freeLights;
	CGatherBundle				*lastGather;		// Pointer to the last gather bundle
	

	assert((currentShadingState->numActive+currentShadingState->numPassive) == currentShadingState->numVertices);

	currentShadingState->currentShaderInstance	=	cInstance;
	code										=	currentShader->codeArea + currentShader->codeEntryPoint;
	tagStart									=	currentShadingState->tags;

	// Save this stuff for fast access
	numVertices							=	currentShadingState->numVertices;
	varying								=	currentShadingState->varying;
	lights								=	&currentShadingState->lights;
	alights								=	&currentShadingState->alights;
	currentLight						=	&currentShadingState->currentLight;
	freeLights							=	&currentShadingState->freeLights;

	// Set the access arrays
	stuff[SL_IMMEDIATE_OPERAND]			=	currentShader->constantEntries;				// Immediate operands
	stuff[SL_GLOBAL_OPERAND]			=	(void **) varying;							// Global variables
	stuff[SL_VARYING_OPERAND]			=	(void **) locals;							// Local variables

	numActive							=	currentShadingState->numActive;
	numPassive							=	currentShadingState->numPassive;
	lastConditional						=	NULL;										// The last conditional block

	// Execute
execStart:
	const ESlCode	opcode	=	(ESlCode)	code->opcode;	// Get the opcode

	tags	=	tagStart;						// Set the tags to the start

	if (code->uniform) {			// If the opcode is uniform , execute once
#define		DEFOPCODE(name,text,nargs,expr_pre,expr,expr_update,expr_post,params)					\
			case OPCODE_##name:																		\
			{																						\
				expr_pre;																			\
				expr;																				\
				expr_post;																			\
				code++;																				\
				goto execStart;																		\
			}

#define		DEFSHORTOPCODE(name,text,nargs,expr_pre,expr,expr_update,expr_post,params)				\
			case OPCODE_##name:																		\
			{																						\
				expr_pre;																			\
				expr;																				\
				expr_post;																			\
				code++;																				\
				goto execStart;																		\
			}


#define		DEFFUNC(name,text,prototype,expr_pre,expr,expr_update,expr_post,par)					\
			case FUNCTION_##name:																	\
			{																						\
				expr_pre;																			\
				expr;																				\
				expr_post;																			\
				code++;																				\
				goto execStart;																		\
			}

#define		DEFLIGHTFUNC(name,text,prototype,expr_pre,expr,expr_update,expr_post,par)				\
			case FUNCTION_##name:																	\
			{																						\
				scripterror("invalid uniform lighting call");										\
				code++;																				\
				goto execStart;																		\
			}

#define		DEFSHORTFUNC(name,text,prototype,expr_pre,expr,expr_update,expr_post,par)				\
			case FUNCTION_##name:																	\
			{																						\
				expr_pre;																			\
				expr;																				\
				expr_post;																			\
				code++;																				\
				goto execStart;																		\
			}

		switch(opcode) {

#include "scriptOpcodes.h"

#include "scriptFunctions.h"

		default:
			error(CODE_BUG,"Opcode conflict");
			goto execEnd;
		}

		// Resume executing instructions
		code++;
		goto execStart;

#undef DEFOPCODE
#undef DEFSHORTOPCODE
#undef DEFFUNC
#undef DEFLIGHTFUNC
#undef DEFSHORTFUNC


	} else {
		if (numPassive != 0) {					// If we have some vertices that are passive, be more careful
#define		DEFOPCODE(name,text,nargs,expr_pre,expr,expr_update,expr_post,params)					\
			case OPCODE_##name:																		\
			{																						\
				expr_pre;																			\
				for (currentVertex=numVertices;currentVertex>0;currentVertex--,tags++) {			\
					if (*tags == 0) {																\
						expr;																		\
					}																				\
					expr_update;																	\
				}																					\
				expr_post																			\
				code++;																				\
				goto execStart;																		\
			}


#define		DEFSHORTOPCODE(name,text,nargs,expr_pre,expr,expr_update,expr_post,params)				\
			case OPCODE_##name:																		\
			{																						\
				expr_pre;																			\
				for (currentVertex=currentShadingState->numRealVertices;currentVertex>0;currentVertex--,tags++) {			\
					if (*tags == 0) {																\
						expr;																		\
					}																				\
					expr_update;																	\
				}																					\
				expr_post																			\
				code++;																				\
				goto execStart;																		\
			}


#define		DEFFUNC(name,text,prototype,expr_pre,expr,expr_update,expr_post,par)					\
			case FUNCTION_##name:																	\
			{																						\
				expr_pre;																			\
				for (currentVertex=numVertices;currentVertex>0;currentVertex--,tags++) {			\
					if (*tags == 0) {																\
						expr;																		\
					}																				\
					expr_update;																	\
				}																					\
				expr_post																			\
				code++;																				\
				goto execStart;																		\
			}

#define		DEFLIGHTFUNC(name,text,prototype,expr_pre,expr,expr_update,expr_post,par)				\
			case FUNCTION_##name:																	\
			{																						\
				expr_pre;																			\
				for (currentVertex=numVertices;currentVertex>0;currentVertex--,tags++) {			\
					if (*tags == 0) {																\
						expr;																		\
					}																				\
					expr_update;																	\
				}																					\
				expr_post																			\
				code++;																				\
				goto execStart;																		\
			}
			
#define		DEFSHORTFUNC(name,text,prototype,expr_pre,expr,expr_update,expr_post,par)				\
			case FUNCTION_##name:																	\
			{																						\
				expr_pre;																			\
				for (currentVertex=currentShadingState->numRealVertices;currentVertex>0;currentVertex--,tags++) {			\
					if (*tags == 0) {																\
						expr;																		\
					}																				\
					expr_update;																	\
				}																					\
				expr_post																			\
				code++;																				\
				goto execStart;																		\
			}


			switch(opcode) {

#include "scriptOpcodes.h"

#include "scriptFunctions.h"

			default:
				error(CODE_BUG,"Opcode conflict");
				goto execEnd;
			}

			code++;
			goto execStart;
		} else {

#undef DEFOPCODE
#undef DEFSHORTOPCODE
#undef DEFFUNC
#undef DEFLIGHTFUNC
#undef DEFSHORTFUNC

#define		DEFOPCODE(name,text,nargs,expr_pre,expr,expr_update,expr_post,params)					\
			case OPCODE_##name:																		\
			{																						\
				expr_pre;																			\
				for (currentVertex=numVertices;currentVertex>0;currentVertex--) {					\
					expr;																			\
					expr_update;																	\
				}																					\
				expr_post																			\
				code++;																				\
				goto execStart;																		\
			}

#define		DEFSHORTOPCODE(name,text,nargs,expr_pre,expr,expr_update,expr_post,params)				\
			case OPCODE_##name:																		\
			{																						\
				expr_pre;																			\
				for (currentVertex=currentShadingState->numRealVertices;currentVertex>0;currentVertex--) {					\
					expr;																			\
					expr_update;																	\
				}																					\
				expr_post																			\
				code++;																				\
				goto execStart;																		\
			}


#define		DEFFUNC(name,text,prototype,expr_pre,expr,expr_update,expr_post,par)					\
			case FUNCTION_##name:																	\
			{																						\
				expr_pre;																			\
				for (currentVertex=numVertices;currentVertex>0;currentVertex--) {					\
					expr;																			\
					expr_update;																	\
				}																					\
				expr_post																			\
				code++;																				\
				goto execStart;																		\
			}

#define		DEFLIGHTFUNC(name,text,prototype,expr_pre,expr,expr_update,expr_post,par)				\
			case FUNCTION_##name:																	\
			{																						\
				expr_pre;																			\
				for (currentVertex=numVertices;currentVertex>0;currentVertex--,tags++) {			\
					if (*tags == 0) {																\
						expr;																		\
					}																				\
					expr_update;																	\
				}																					\
				expr_post																			\
				code++;																				\
				goto execStart;																		\
			}


#define		DEFSHORTFUNC(name,text,prototype,expr_pre,expr,expr_update,expr_post,par)				\
			case FUNCTION_##name:																	\
			{																						\
				expr_pre;																			\
				for (currentVertex=currentShadingState->numRealVertices;currentVertex>0;currentVertex--) {					\
					expr;																			\
					expr_update;																	\
				}																					\
				expr_post																			\
				code++;																				\
				goto execStart;																		\
			}

			switch(opcode) {

#include "scriptOpcodes.h"

#include "scriptFunctions.h"

			default:
				error(CODE_BUG,"Opcode conflict");
				goto execEnd;
			}

			code++;
			goto execStart;
		}

#undef DEFOPCODE
#undef DEFSHORTOPCODE
#undef DEFFUNC
#undef DEFLIGHTFUNC
#undef DEFSHORTFUNC

	}


	goto execStart;
execEnd:

	// Make sure we save the ambient contribution if there has been no illuminate/solar executed
	if (currentShader->type == SL_LIGHTSOURCE) {
		if (!(currentShader->usedParameters & PARAMETER_NONAMBIENT)) {
			float	*Cl		=	varying[VARIABLE_CL];
			float	*Ol		=	varying[VARIABLE_OL];
			float	*Clsave;
			
			// Save the ambient junk
			Clsave	= (*alights)->savedState[1];
			tags	= tagStart;
			for (int i=numVertices;i>0;i--,Cl+=3,Ol+=3,Clsave+=3) {
				if (*tags==0) {
					addvv(Clsave,Cl);
				}
				tags++;
			}
		}
	}

// Undefine junk
#undef		savestring
#undef		allocbuffer
#undef		freebuffer
#undef		beginConditional
#undef		endConditional
#undef		operand
#undef		dirty
#undef		parameterlist
#undef		argument
#undef		argumentcount
#undef		jmp
#undef		runAmbientLights
#undef		runLightsTemplate
#undef		CATEGORYLIGHT_PRE
#undef		CATEGORYLIGHT_CHECK
#undef		runCategoryLights
#undef		NORMALLIGHT_PRE
#undef		runLights
#undef		firstLight
#undef		nextLight
#undef		allLights
#undef		currentLight
#undef		saveLight	
#undef		uniformGlobal
#undef		varyingGlobal
#undef		DEFOPCODE
#undef		DEFFUNC
#undef		DEFLINKOPCODE
#undef		DEFLINKFUNC
#undef		BREAK
}

