//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright � 1999 - 2003, Okan Arikan
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
//  File				:	giOpcodes.h
//  Classes				:	-
//  Description			:	Shading language Global Illumination opcodes.
//
////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	gather <else>
#ifndef INIT_SHADING
#define	GATHEREXPR_PRE		const int	numRealVertices	=	currentShadingState->numRealVertices;	\
							CGatherRay		*raysBase	=	lastGather->raysBase;					\
							CGatherRay		**rays		=	(CGatherRay **) lastGather->raysStorage;\
							CGatherLookup	*lookup		=	lastGather->lookup;						\
							const float 	numSamples	=	(float) lastGather->numSamples;			\
							const float 	*coneAngle	=	lastGather->coneAngles;					\
							const float		*dPdu		=	lastGather->dPdu;						\
							const float		*dPdv		=	lastGather->dPdv;						\
							const float		*P			=	lastGather->P;							\
							const float		*D			=	lastGather->gatherDir;					\
							const float		*N				=	varying[VARIABLE_N];				\
							int			numIntRays		=	0;										\
							int			numExtRays		=	0;										\
							int			i;															\
							for (i=0;i<numRealVertices;i++) {										\
								if (tags[i]) {														\
									tags[i]++;														\
								} else {															\
									vector	tmp0,tmp1;												\
									mulvf(tmp0,dPdu,lookup->sampleBase*(urand() - 0.5f));			\
									mulvf(tmp1,dPdv,lookup->sampleBase*(urand() - 0.5f));			\
									addvv(raysBase->from,tmp0,tmp1);								\
									addvv(raysBase->from,P);										\
																									\
									if (lookup->uniformDist) {										\
										sampleHemisphere(raysBase->dir,D,*coneAngle,random4d);		\
									} else {														\
										sampleCosineHemisphere(raysBase->dir,D,*coneAngle,random4d);\
									}																\
									raysBase->index	=	i;											\
									raysBase->tmin	=	lookup->bias;								\
									raysBase->t		=	lookup->maxDist;							\
									raysBase->time	=	(urand() + lastGather->remainingSamples - 1) / numSamples;				\
									raysBase->flags	=	ATTRIBUTES_FLAGS_DIFFUSE_VISIBLE | ATTRIBUTES_FLAGS_SPECULAR_VISIBLE;	\
									raysBase->tags	=	&tags[i];									\
									if (dotvv(raysBase->dir,N) > 0) {								\
										rays[numExtRays++] = raysBase++;							\
									} else {														\
										rays[numRealVertices-1-numIntRays++] = raysBase++;			\
									}																\
								}																	\
								coneAngle++;														\
								dPdu	+=	3;														\
								dPdv	+=	3;														\
								P		+=	3;														\
								D		+=	3;														\
								N		+=	3;														\
							}																		\
							if ( (numIntRays+numExtRays) > 0 ) {									\
								const CAttributes	*cAttributes	=	currentShadingState->currentObject->attributes;		\
								if (numIntRays > 0) {												\
									lastGather->numRays		=	numIntRays;							\
									lastGather->rays		=	(CRay **) rays+numRealVertices-numIntRays;	\
									lastGather->last		=	0;									\
									lastGather->depth		=	0;									\
									lastGather->postShader	=	cAttributes->interior;				\
									lastGather->numMisses	=	0;									\
									traceEx(lastGather);											\
									numActive				-=	lastGather->numMisses;				\
									numPassive				+=	lastGather->numMisses;				\
								}																	\
								if (numExtRays > 0) {												\
									lastGather->numRays		=	numExtRays;							\
									lastGather->rays		=	(CRay **) rays;						\
									lastGather->last		=	0;									\
									lastGather->depth		=	0;									\
									lastGather->postShader	=	cAttributes->exterior;				\
									lastGather->numMisses	=	0;									\
									traceEx(lastGather);											\
									numActive				-=	lastGather->numMisses;				\
									numPassive				+=	lastGather->numMisses;				\
								}																	\
																									\
								if (numActive == 0) {												\
									jmp(argument(0));												\
								}																	\
							}
	
#else
#define GATHEREXPR_PRE
#endif

DEFOPCODE(Gather	,"gather"	,1,	GATHEREXPR_PRE,NULL_EXPR,NULL_EXPR,NULL_EXPR,PARAMETER_N | PARAMETER_RAYTRACE)

#undef GATHEREXPR_PRE

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	gatheElse <endLabel>
#ifndef INIT_SHADING
#define	GATHERELSEEXPR_PRE	int	numRealVertices = currentShadingState->numRealVertices;				\
																									\
							for (;numRealVertices>0;numRealVertices--,tags++)	{					\
								if (*tags <= 1) {													\
									if (*tags == 1) {												\
										*tags	=	0;												\
										numActive++;												\
										numPassive--;												\
									} else {														\
										*tags	=	1;												\
										numActive--;												\
										numPassive++;												\
									}																\
								}																	\
							}																		\
																									\
							if (numActive == 0) {													\
								jmp(argument(0));													\
							}

#else
#define GATHERELSEEXPR_PRE
#endif

DEFOPCODE(GatherElse	,"gatherElse"	,1,	GATHERELSEEXPR_PRE,NULL_EXPR,NULL_EXPR,NULL_EXPR,0)

#undef GATHERELSEEXPR_PRE

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	gatheEnd <gatherLabel>
#ifndef INIT_SHADING
#define	GATHERENDEXPR_PRE	int	numRealVertices = currentShadingState->numRealVertices;				\
																									\
							for (;numRealVertices>0;numRealVertices--,tags++) {						\
								if (*tags) {														\
									(*tags)--;														\
									if (*tags == 0) {												\
										numActive++;												\
										numPassive--;												\
									}																\
								}																	\
							}																		\
																									\
							lastGather->numMisses	=	0;											\
							lastGather->remainingSamples--;											\
							if (lastGather->remainingSamples > 0) {									\
								jmp(argument(0));													\
							} else {																\
								delete lastGather;													\
							}
								
#else
#define GATHERENDEXPR_PRE
#endif

DEFOPCODE(GatherEnd	,"gatherEnd"	,1,	GATHERENDEXPR_PRE,NULL_EXPR,NULL_EXPR,NULL_EXPR,0)

#undef GATHERENDEXPR_PRE

