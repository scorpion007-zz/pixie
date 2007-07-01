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
//  File				:	shaderParameterList.h
//  Classes				:	-
//  Description			:	This file implements dynamic lookup for shader
//							parameter lists
////////////////////////////////////////////////////////////////////////

// Parameter list helpers
struct CTempParamBinding {
	CDynamicShaderLookup::TParamBinding	binding;
	CTempParamBinding					*next;
};

#define initParamBindings(__lookup)												\
	CTempParamBinding *__uniformParamBindingsStart	= NULL;						\
	CTempParamBinding *__uniformParamBindingsEnd	= NULL;						\
	CTempParamBinding *__varyingParamBindingsStart	= NULL;						\
	CTempParamBinding *__varyingParamBindingsEnd	= NULL;


#define addUniformParamBinding(__lookup,__start,__type,__mult,__varyingLookupType,__dest)	{				\
	CTempParamBinding *__param = (CTempParamBinding *) ralloc(sizeof(CTempParamBinding),threadMemory);		\
	if (__uniformParamBindingsEnd == NULL) __uniformParamBindingsEnd = __uniformParamBindingsStart = __param;	\
	else { __uniformParamBindingsEnd->next = __param;	__uniformParamBindingsEnd = __param; }				\
	__param->next = NULL;																					\
	__param->binding.opIndex	= i*2+__start+1;															\
	__param->binding.dest		= (size_t) offsetof(__varyingLookupType,__dest);							\
	__param->binding.type		= __type;																	\
	__param->binding.mult		= __mult;																	\
	__lookup->numUniformParamBindings++;																	\
}

#define addVaryingParamBinding(__lookup,__start,__type,__mult,__varyingLookupType,__dest)	{				\
	if (operandVaryingStep(i*2+__start+1) == 0) {															\
		addUniformParamBinding(__lookup,__start,__type,__mult,__varyingLookupType,__dest);					\
	} else {																								\
		CTempParamBinding *__param = (CTempParamBinding *) ralloc(sizeof(CTempParamBinding),threadMemory);	\
		if (__varyingParamBindingsEnd == NULL) __varyingParamBindingsEnd = __varyingParamBindingsStart = __param;	\
		else { __varyingParamBindingsEnd->next = __param;	__varyingParamBindingsEnd = __param; }			\
		__param->next = NULL;																				\
		__param->binding.opIndex	= i*2+__start+1;														\
		__param->binding.dest		= (size_t) offsetof(__varyingLookupType,__dest);						\
		__param->binding.type		= __type;																\
		__param->binding.mult		= __mult;																\
		__lookup->numVaryingParamBindings++;																\
	}																										\
}


#define completeParamBindings(__lookup)	{																				\
	if (__lookup->numUniformParamBindings > 0) {																		\
		__lookup->uniformParamBindings = new CDynamicShaderLookup::TParamBinding[__lookup->numUniformParamBindings];	\
		CDynamicShaderLookup::TParamBinding 	*cBinding		= __lookup->uniformParamBindings;						\
		CTempParamBinding						*cTempBinding	= __uniformParamBindingsStart;							\
		while (cTempBinding != NULL) {																					\
			memcpy(cBinding,cTempBinding,sizeof(CDynamicShaderLookup::TParamBinding));									\
			cBinding++;																									\
			cTempBinding = cTempBinding->next;																			\
		}																												\
	}																													\
	if (__lookup->numVaryingParamBindings > 0) {																		\
		__lookup->varyingParamBindings = new CDynamicShaderLookup::TParamBinding[__lookup->numVaryingParamBindings];	\
		CDynamicShaderLookup::TParamBinding 	*cBinding		= __lookup->varyingParamBindings;						\
		CTempParamBinding						*cTempBinding	= __varyingParamBindingsStart;							\
		while (cTempBinding != NULL) {																					\
			memcpy(cBinding,cTempBinding,sizeof(CDynamicShaderLookup::TParamBinding));									\
			cBinding++;																									\
			cTempBinding = cTempBinding->next;																			\
		}																												\
	}																													\
}

#define getUniformParams(__lookup,__varyingLookup) {									\
	CDynamicShaderLookup::TParamBinding *cParamBind = __lookup->uniformParamBindings;	\
	for(int o=0;o<__lookup->numUniformParamBindings;o++,cParamBind++) {					\
		if (cParamBind->type == TYPE_INTEGER) {											\
			const float *optmp;															\
			char *dtmp = (char*)&__varyingLookup;										\
			operand(cParamBind->opIndex,optmp,const float *);							\
			*((int*)(dtmp+ cParamBind->dest)) = (int) cParamBind->mult * (int) *optmp;	\
		} else {																		\
			const float *optmp;															\
			char *dtmp = (char*)&__varyingLookup;										\
			operand(cParamBind->opIndex,optmp,const float *);							\
			*((float*)(dtmp + cParamBind->dest)) = cParamBind->mult * *optmp;			\
		}																				\
	}																					\
}

#define initVaryingParams(__lookup) 													\
	const float	**__varyingParameterPtrs;												\
	 int		*__varyingParameterSizes;												\
	{																					\
		CDynamicShaderLookup::TParamBinding *cParamBind = __lookup->varyingParamBindings;	\
		if (__lookup->numVaryingParamBindings > 0) {									\
			__varyingParameterPtrs = (const float**) ralloc(sizeof(const float*)*__lookup->numVaryingParamBindings,threadMemory);	\
			__varyingParameterSizes = (int*) ralloc(sizeof(int)*__lookup->numVaryingParamBindings,threadMemory);	\
			for(int o=0;o<__lookup->numVaryingParamBindings;o++,cParamBind++) {			\
				operand(cParamBind->opIndex,__varyingParameterPtrs[o],const float *);	\
				__varyingParameterSizes[o] = operandVaryingStep(cParamBind->opIndex);	\
			}																			\
		}																				\
	}

#define getVaryingParams(__lookup,__varyingLookup) {									\
	CDynamicShaderLookup::TParamBinding *cParamBind = __lookup->varyingParamBindings;	\
	for(int o=0;o<__lookup->numVaryingParamBindings;o++,cParamBind++){					\
		if (cParamBind->type == TYPE_INTEGER) {											\
			char *dtmp = (char*)&__varyingLookup;										\
			*((int*)(dtmp+ cParamBind->dest)) = (int) cParamBind->mult * (int) *__varyingParameterPtrs[o];	\
		} else {																		\
			char *dtmp = (char*)&__varyingLookup;										\
			*((float*)(dtmp + cParamBind->dest)) = cParamBind->mult * *__varyingParameterPtrs[o];	\
		}																				\
	}																					\
}

#define stepVaryingParams(__lookup) {													\
	for(int o=0;o<__lookup->numVaryingParamBindings;o++){								\
		__varyingParameterPtrs[o] += __varyingParameterSizes[o];						\
	}																					\
}
