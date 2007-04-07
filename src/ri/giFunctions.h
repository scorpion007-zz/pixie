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
//  File				:	giFunctions.h
//  Classes				:	-
//  Description			:	Shading language Global Illumination functions
//
////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Photon map - irradiance cache macros
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This macro is used to decode the texture parameter list
#define	GLOBPARAMETERS(start,num)																								\
								lookup						=	new CGlobalIllumLookup;											\
								parameterlist				=	lookup;															\
								dirty();																						\
								lookup->numLookupSamples	=	attributes->photonEstimator;									\
								lookup->maxDistance			=	C_INFINITY;														\
								lookup->numSamples			=	200;															\
								lookup->maxError			=	attributes->irradianceMaxError;									\
								lookup->maxBrightness		=	1;																\
								lookup->maxFGRadius			=	C_INFINITY;														\
								lookup->minFGRadius			=	C_EPSILON;														\
								lookup->sampleBase			=	0;																\
								lookup->irradianceIndex		=	-1;																\
								lookup->coverageIndex		=	-1;																\
								lookup->environmentIndex	=	-1;																\
								lookup->bias				=	attributes->shadowBias;											\
								lookup->occlusion			=	FALSE;															\
								lookup->gatherGlobal		=	1;																\
								lookup->gatherLocal			=	1;																\
								lookup->pointbased			=	FALSE;															\
								lookup->localThreshold		=	1;																\
								lookup->lengthA				=	CRenderer::lengthA;												\
								lookup->lengthB				=	CRenderer::lengthB;												\
								lookup->handle				=	(attributes->irradianceHandle		== NULL ? "temp.irr"	: attributes->irradianceHandle);			\
								lookup->filemode			=	(attributes->irradianceHandleMode	== NULL ? ""			: attributes->irradianceHandleMode);		\
								lookup->coordsys			=	coordinateWorldSystem;											\
								initv(lookup->backgroundColor,0);																\
								lookup->cache				=	NULL;															\
								lookup->map					=	NULL;															\
								lookup->environment			=	NULL;															\
								lookup->pointHierarchy		=	NULL;															\
								{																								\
									int			i;																				\
									const char	**param;																		\
									const float	*valf;																			\
									const char	**vals;																			\
																																\
									for (i=0;i<num;i++) {																		\
										operand(i*2+start,param,const char **);													\
										operand(i*2+start+1,valf,const float *);												\
										operand(i*2+start+1,vals,const char **);												\
																																\
										if (strcmp(*param,"estimator") == 0) {													\
											lookup->numLookupSamples	=	(int) valf[0];										\
										} else if (strcmp(*param,"maxdist") == 0) {												\
											lookup->maxDistance	=	valf[0];													\
										} else if (strcmp(*param,"maxerror") == 0) {											\
											lookup->maxError	=	valf[0];													\
										} else if (strcmp(*param,"samples") == 0) {												\
											lookup->numSamples	=	(int) valf[0];												\
										} else if (strcmp(*param,"bias") == 0) {												\
											lookup->bias		=	valf[0];													\
										} else if (strcmp(*param,"localThreshold") == 0) {										\
											lookup->localThreshold	=	valf[0];												\
										} else if (strcmp(*param,"backgroundColor") == 0) {										\
											movvv(lookup->backgroundColor,valf);												\
										} else if (strcmp(*param,"maxBrightness") == 0) {										\
											lookup->maxBrightness	=	valf[0];												\
										} else if (strcmp(*param,"minR") == 0) {												\
											lookup->minFGRadius	=	valf[0];													\
										} else if (strcmp(*param,"maxR") == 0) {												\
											lookup->maxFGRadius	=	valf[0];													\
										} else if (strcmp(*param,"samplebase") == 0) {											\
											lookup->sampleBase	=	valf[0];													\
										} else if (strcmp(*param,"global") == 0) {												\
											lookup->gatherGlobal	=	(int) valf[0];											\
										} else if (strcmp(*param,"local") == 0) {												\
											lookup->gatherLocal		=	(int) valf[0];											\
										} else if (strcmp(*param,"handle") == 0) {												\
											lookup->handle			=	vals[0];												\
										} else if (strcmp(*param,"filemode") == 0) {											\
											lookup->filemode		=	vals[0];												\
										} else if (strcmp(*param,"coordsystem") == 0) {											\
											lookup->coordsys		=	vals[0];												\
										} else if (strcmp(*param,"environmentmap") == 0) {										\
											lookup->environment		=	CRenderer::getEnvironment(vals[0]);						\
										} else if (strcmp(*param,"irradiance") == 0) {											\
											lookup->irradianceIndex	=	i*2+start+1;											\
										} else if (strcmp(*param,"occlusion") == 0) {											\
											lookup->coverageIndex	=	i*2+start+1;											\
										} else if (strcmp(*param,"environmentdir") == 0) {										\
											lookup->environmentIndex=	i*2+start+1;											\
										} else if (strcmp(*param,"pointbased") == 0) {											\
											lookup->pointbased		=	(vals[0] > 0);											\
										} else if (strcmp(*param,"filename") == 0) {											\
											lookup->pointHierarchy	=	CRenderer::getTexture3d(vals[0],FALSE,"_area",CRenderer::fromWorld,CRenderer::toWorld,TRUE);						\
										}																						\
									}																							\
								}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// transmission	"c=pp!"
#ifndef INIT_SHADING
#define	TRANSMISSIONEXPR_PRE	float			*res,*op1,*op2;																	\
								CTextureLookup	*lookup;																		\
								osLock(CRenderer::shaderMutex);																	\
								if ((lookup = (CTextureLookup *) parameterlist) == NULL) {										\
									int			numArguments;																	\
									argumentcount(numArguments);																\
									TEXTUREPARAMETERS(3,(numArguments-3) >> 1);													\
								}																								\
								osUnlock(CRenderer::shaderMutex);																\
								operand(0,res,float *);																			\
								operand(1,op1,float *);																			\
								operand(2,op2,float *);																			\
								float	*L	=	(float *) ralloc(numVertices*3*sizeof(float),threadMemory);						\
								int		t;																						\
								for (t=0;t<numVertices;t++)	subvv(L + t*3,(float *) op1 + t*3,(float *) op2 + t*3);				\
								traceTransmission((float *) res,(float *) op1,L,currentShadingState->numRealVertices,tags,lookup);


#else

#define	TRANSMISSIONEXPR_PRE


#endif

DEFFUNC(TRANSMISSION			,"transmission"			,"c=pp!"		,TRANSMISSIONEXPR_PRE,NULL_EXPR,NULL_EXPR,NULL_EXPR,PARAMETER_RAYTRACE | PARAMETER_DERIVATIVE)

#undef	TRANSMISSIONEXPR_PRE




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// trace	"f=pv"
#ifndef INIT_SHADING
#define	TRACEEXPR_PRE			FUN3EXPR_PRE																					\
								const float			bias	=	currentShadingState->currentObject->attributes->shadowBias;		\
								const float			*ab		=	rayDiff(op1,op2,NULL);											\
								vector				D;																			\
								CRay				ray;

#define	TRACEEXPR				subvv(D,op2,op1);																				\
								if (dotvv(D,D) > 0) {																			\
									ray.t					=	lengthv(D);														\
									mulvf(ray.dir,D,1/ray.t);																	\
									movvv(ray.from,op1);																		\
									ray.flags				=	ATTRIBUTES_FLAGS_TRACE_VISIBLE;									\
									ray.time				=	urand();														\
									ray.tmin				=	bias;															\
									ray.t					-=	bias;															\
									ray.da					=	ab[0];															\
									ray.db					=	ab[1];															\
																																\
									numReflectionRays++;																		\
									trace(&ray);																				\
																																\
									*res					=	ray.t;															\
								} else {																						\
									*res					=	0.0f;															\
								}


#define	TRACEEXPR_UPDATE		FUN3EXPR_UPDATE(1,3,3)																			\
								ab	+=	2;

#else
#define	TRACEEXPR_PRE
#define	TRACEEXPR
#define	TRACEEXPR_UPDATE
#endif

DEFSHORTFUNC(Tracef			,"trace"			,"f=pv"		,TRACEEXPR_PRE,TRACEEXPR,TRACEEXPR_UPDATE,NULL_EXPR,PARAMETER_RAYTRACE  | PARAMETER_DERIVATIVE)

#undef	TRACEEXPR_PRE
#undef	TRACEEXPR
#undef	TRACEEXPR_UPDATE
#undef	TRACEEXPR_POST



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This macro is used to decode the trace parameter list
#define	TRACEPARAMETERS(start,num)																					\
								lookup					=	new CTraceLookup;										\
								parameterlist			=	(CShaderLookup *) lookup;								\
								dirty();																			\
								lookup->bias			=	currentShadingState->currentObject->attributes->shadowBias;	\
								lookup->label			=	rayLabelTrace;											\
								{																					\
									int		i;																		\
									const char	**param;															\
									const float	*valf;																\
									const char	**vals;																\
																													\
									for (i=0;i<num;i++) {															\
										operand(i*2+start,param,const char **);										\
										operand(i*2+start+1,valf,const float *);									\
										operand(i*2+start+1,vals,const char **);									\
																													\
										if (strcmp(*param,"bias") == 0) {											\
											lookup->bias		=	valf[0];										\
										} else if (strcmp(*param,"label") == 0) {									\
											lookup->label		=	vals[0];										\
										}																			\
									}																				\
								}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// trace	"c=pv!"
#ifndef INIT_SHADING
#define	TRACEEXPR_PRE			float				*res;																		\
								const float			*op1,*op2;																	\
								CTraceBundle		interiorBundle,exteriorBundle;												\
								CTraceRay			*rays;																		\
								CTraceRay			**interiorRays,**exteriorRays;												\
								int					cExterior		=	0;														\
								int					cInterior		=	0;														\
								const CAttributes	*cAttributes	=	currentShadingState->currentObject->attributes;			\
								float				*N;																			\
								CTraceLookup		*lookup;																	\
								osLock(CRenderer::shaderMutex);																	\
								if ((lookup = (CTraceLookup *) parameterlist) == NULL) {										\
									int			numArguments;																	\
									argumentcount(numArguments);																\
									TRACEPARAMETERS(3,(numArguments-3) >> 1);													\
								}																								\
								osUnlock(CRenderer::shaderMutex);																\
								rays			=	(CTraceRay *) ralloc(numVertices*sizeof(CTraceRay),threadMemory);			\
								interiorRays	=	(CTraceRay **) ralloc(numVertices*sizeof(CTraceRay *),threadMemory);		\
								exteriorRays	=	(CTraceRay **) ralloc(numVertices*sizeof(CTraceRay *),threadMemory);		\
								N				=	varying[VARIABLE_N];														\
								operand(0,res,float *);																			\
								operand(1,op1,const float *);																	\
								operand(2,op2,const float *);																	\
								const float *ab	=	rayDiff(op1,op2,NULL);

#define	TRACEEXPR				if (dotvv(op2,op2) > 0) {																		\
									movvv(rays->from,op1);																		\
									normalizev(rays->dir,op2);																	\
									initv(res,0);																				\
									rays->dest			=	res;																\
									rays->multiplier	=	1;																	\
									rays->t				=	C_INFINITY;															\
									rays->time			=	urand();															\
									rays->flags			=	ATTRIBUTES_FLAGS_TRACE_VISIBLE;										\
									rays->tmin			=	lookup->bias;														\
									rays->da			=	ab[0];																\
									rays->db			=	ab[1];																\
									if (dotvv(op2,N) > 0) {																		\
										exteriorRays[cExterior++]	=	rays++;													\
									} else {																					\
										interiorRays[cInterior++]	=	rays++;													\
									}																							\
								} else {																						\
									initv(res,0);																				\
								}



#define	TRACEEXPR_UPDATE		FUN3EXPR_UPDATE(3,3,3);																			\
								ab					+=	2;																		\
								N					+=	3;

#define	TREACEEXPR_POST			if (inShadow == FALSE) {																		\
									numReflectionRays	+=	cInterior + cExterior;												\
									if (cInterior > 0) {																		\
										interiorBundle.postShader	=	cAttributes->interior;									\
										interiorBundle.numRays		=	cInterior;												\
										interiorBundle.depth		=	0;														\
										interiorBundle.last			=	0;														\
										interiorBundle.rays			=	(CRay **) interiorRays;									\
										interiorBundle.label		=	lookup->label;											\
										traceEx(&interiorBundle);																\
									}																							\
									if (cExterior > 0) {																		\
										exteriorBundle.postShader	=	cAttributes->exterior;									\
										exteriorBundle.numRays		=	cExterior;												\
										exteriorBundle.depth		=	0;														\
										exteriorBundle.last			=	0;														\
										exteriorBundle.rays			=	(CRay **) exteriorRays;									\
										exteriorBundle.label		=	lookup->label;											\
										traceEx(&exteriorBundle);																\
									}																							\
								}

#else
#define	TRACEEXPR_PRE
#define	TRACEEXPR
#define	TRACEEXPR_UPDATE
#define	TREACEEXPR_POST
#endif

DEFSHORTFUNC(TraceV				,"trace"				,"c=pv!"		,TRACEEXPR_PRE,TRACEEXPR,TRACEEXPR_UPDATE,TREACEEXPR_POST,PARAMETER_N | PARAMETER_RAYTRACE  | PARAMETER_DERIVATIVE)

#undef	TRACEEXPR_PRE
#undef	TRACEEXPR
#undef	TRACEEXPR_UPDATE
#undef	TREACEEXPR_POST



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// visibility	"f=pp"
#ifndef INIT_SHADING
#define	VISIBILITYEXPR_PRE		FUN3EXPR_PRE																				\
								const float			bias	=	currentShadingState->currentObject->attributes->shadowBias;	\
								const float			*ab		=	rayDiff(op1,NULL,op2);										\
								vector				D;																		\
								CRay				ray;

#define	VISIBILITYEXPR			subvv(D,op2,op1);																			\
								if (dotvv(D,D) > 0) {																		\
									ray.t					=	lengthv(D);													\
									mulvf(ray.dir,D,1/ray.t);																\
									movvv(ray.from,op1);																	\
									ray.flags				=	ATTRIBUTES_FLAGS_TRANSMISSION_VISIBLE;						\
									ray.time				=	urand();													\
									ray.tmin				=	bias;														\
									ray.t					-=	bias;														\
									ray.da					=	ab[0];														\
									ray.db					=	ab[1];														\
																															\
									numTransmissionRays++;																	\
									trace(&ray);																			\
																															\
									if (ray.object != NULL)	res[0]	=	0;													\
									else					res[0]	=	1;													\
								} else {																					\
									res[0]	=	1;																			\
								}

#define	VISIBILITYEXPR_UPDATE	FUN3EXPR_UPDATE(1,3,3)																		\
								ab	+=	2;

#else
#define	VISIBILITYEXPR_PRE
#define	VISIBILITYEXPR
#define	VISIBILITYEXPR_UPDATE
#endif

DEFSHORTFUNC(Visibility			,"visibility"			,"f=pp"		,VISIBILITYEXPR_PRE,VISIBILITYEXPR,VISIBILITYEXPR_UPDATE,NULL_EXPR,PARAMETER_RAYTRACE  | PARAMETER_DERIVATIVE)

#undef	VISIBILITYEXPR_PRE
#undef	VISIBILITYEXPR
#undef	VISIBILITYEXPR_UPDATE

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// indirectdiffuse	"c=pnf!"
#ifndef INIT_SHADING
#define	IDEXPR_PRE				CGlobalIllumLookup	*lookup;																		\
								CCache				*cache;																			\
								float				C[7];																			\
								float				*envdir;																		\
								float				*coverage;																		\
								FUN4EXPR_PRE;																						\
								osLock(CRenderer::shaderMutex);																		\
								if ((lookup = (CGlobalIllumLookup *) parameterlist) == NULL) {										\
									CAttributes	*attributes	=	currentShadingState->currentObject->attributes;						\
									int			numArguments;																		\
									argumentcount(numArguments);																	\
									GLOBPARAMETERS(4,(numArguments-4) >> 1);														\
									lookup->cache		=	CRenderer::getCache(lookup->handle,lookup->filemode);					\
									lookup->numSamples	=	(int) *op3;																\
									lookup->occlusion	=	FALSE;																	\
								}																									\
								osUnlock(CRenderer::shaderMutex);																	\
								if (lookup->environmentIndex != -1) {	operand(lookup->environmentIndex,envdir,float *);	}		\
								else envdir = varying[VARIABLE_PW];																	\
								if (lookup->coverageIndex != -1)	{	operand(lookup->coverageIndex,coverage,float *);	}		\
								else coverage = varying[VARIABLE_PW];																\
								const float	*b	=	rayDiff(op1);																	\
								cache	=	lookup->cache;


#define	IDEXPR					cache->lookup(C,op1,op2,*b,this,lookup);															\
								movvv(res,C);																						\
								movvv(envdir,C+4);																					\
								*coverage = C[3];


#define	IDEXPR_UPDATE			FUN4EXPR_UPDATE(3,3,3,0)																			\
								b++;																								\
								envdir	+=	3;																						\
								coverage++;

#else
#define	IDEXPR_PRE

#define	IDEXPR
#endif

DEFSHORTFUNC(Indirectdiffuse	,"indirectdiffuse"	,"c=pnf!"	,IDEXPR_PRE,IDEXPR,IDEXPR_UPDATE,NULL_EXPR,PARAMETER_RAYTRACE | PARAMETER_DERIVATIVE)

#undef	IDEXPR_PRE

#undef	IDEXPR






///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// occlusion	"f=pnf!"
#ifndef INIT_SHADING
#define	OCCLUSIONEXPR_PRE		CGlobalIllumLookup	*lookup;																		\
								CCache				*cache;																			\
								float				C[7];																			\
								float				*envdir;																		\
								float				*irradiance;																	\
								FUN4EXPR_PRE;																						\
								osLock(CRenderer::shaderMutex);																		\
								if ((lookup = (CGlobalIllumLookup *) parameterlist) == NULL) {										\
									CAttributes	*attributes	=	currentShadingState->currentObject->attributes;						\
									int			numArguments;																		\
									argumentcount(numArguments);																	\
									GLOBPARAMETERS(4,(numArguments-4) >> 1);														\
									lookup->cache		=	CRenderer::getCache(lookup->handle,lookup->filemode);					\
									lookup->numSamples	=	(int) *op3;																\
									lookup->occlusion	=	TRUE;																	\
									if (lookup->irradianceIndex != -1) lookup->occlusion = FALSE;									\
								}																									\
								osUnlock(CRenderer::shaderMutex);																	\
								if (lookup->environmentIndex != -1) {	operand(lookup->environmentIndex,envdir,float *);	}		\
								else envdir = varying[VARIABLE_PW];																	\
								if (lookup->irradianceIndex != -1)	{	operand(lookup->irradianceIndex,irradiance,float *);	}	\
								else irradiance =  varying[VARIABLE_PW];															\
								const float	*b	=	rayDiff(op1);																	\
								cache	=	lookup->cache;

#define	OCCLUSIONEXPR			cache->lookup(C,op1,op2,*b,this,lookup);															\
								*res	=	C[3];																					\
								movvv(irradiance,C);																				\
								movvv(envdir,C+4);


#define	OCCLUSIONEXPR_UPDATE	FUN4EXPR_UPDATE(1,3,3,0)																			\
								b++;																								\
								irradiance	+=	3;																					\
								envdir		+=	3;

#else
#define	OCCLUSIONEXPR_PRE

#define	OCCLUSIONEXPR
#endif

DEFSHORTFUNC(occlusion	,"occlusion"	,"f=pnf!"	,OCCLUSIONEXPR_PRE,OCCLUSIONEXPR,OCCLUSIONEXPR_UPDATE,NULL_EXPR,PARAMETER_RAYTRACE | PARAMETER_DERIVATIVE)

#undef	OCCLUSIONEXPR_PRE

#undef	OCCLUSIONEXPR






///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// photonmap	"c=spn!"
#ifndef INIT_SHADING
#define	PHOTONMAPEXPR_PRE		CGlobalIllumLookup	*lookup;													\
								CPhotonMap			*map;														\
								float				*res;														\
								const float			*op2,*op3;													\
								osLock(CRenderer::shaderMutex);													\
								if ((lookup = (CGlobalIllumLookup *) parameterlist) == NULL) {					\
									CAttributes	*attributes	=	currentShadingState->currentObject->attributes;	\
									int			numArguments;													\
									const char	**op1;															\
									argumentcount(numArguments);												\
									GLOBPARAMETERS(4,(numArguments-4) >> 1);									\
									operand(1,op1,const char **);												\
									lookup->map			=	CRenderer::getPhotonMap(*op1);						\
								}																				\
								osUnlock(CRenderer::shaderMutex);												\
								operand(0,res,float *);															\
								operand(2,op2,const float *);													\
								operand(3,op3,const float *);													\
								map						=	lookup->map;


#define	PHOTONMAPEXPR			map->lookup(res,op2,op3,lookup->numLookupSamples);

#define	PHOTONMAPEXPR_UPDATE	res	+=	3;																		\
								op2	+=	3;																		\
								op3	+=	3;

#else
#define	PHOTONMAPEXPR_PRE

#define	PHOTONMAPEXPR

#define	PHOTONMAPEXPR_UPDATE
#endif

DEFSHORTFUNC(Photonmap			,"photonmap"	,"c=Spn!"	,PHOTONMAPEXPR_PRE,PHOTONMAPEXPR,PHOTONMAPEXPR_UPDATE,NULL_EXPR,0)

#undef	PHOTONMAPEXPR_PRE

#undef	PHOTONMAPEXPR

#undef	PHOTONMAPEXPR_UPDATE



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// photonmap	"c=sp!"
#ifndef INIT_SHADING
#define	PHOTONMAP2EXPR_PRE		CGlobalIllumLookup	*lookup;													\
								CPhotonMap			*map;														\
								float				*res;														\
								const float			*op2;														\
								osLock(CRenderer::shaderMutex);													\
								if ((lookup = (CGlobalIllumLookup *) parameterlist) == NULL) {					\
									CAttributes	*attributes	=	currentShadingState->currentObject->attributes;	\
									int			numArguments;													\
									const char	**op1;															\
									argumentcount(numArguments);												\
									GLOBPARAMETERS(3,(numArguments-3) >> 1);									\
									operand(1,op1,const char **);												\
									lookup->map			=	CRenderer::getPhotonMap(*op1);						\
								}																				\
								osUnlock(CRenderer::shaderMutex);												\
								operand(0,res,float *);															\
								operand(2,op2,const float *);													\
								map						=	lookup->map;

#define	PHOTONMAP2EXPR			map->lookup(res,op2,lookup->numLookupSamples);

#define	PHOTONMAP2EXPR_UPDATE	res	+=	3;																		\
								op2	+=	3;

#else
#define	PHOTONMAP2EXPR_PRE

#define	PHOTONMAP2EXPR

#define	PHOTONMAP2EXPR_UPDATE
#endif

DEFSHORTFUNC(Photonmap2			,"photonmap"	,"c=Sp!"	,PHOTONMAP2EXPR_PRE,PHOTONMAP2EXPR,PHOTONMAP2EXPR_UPDATE,NULL_EXPR,0)

#undef	PHOTONMAP2EXPR_PRE

#undef	PHOTONMAP2EXPR

#undef	PHOTONMAP2EXPR_UPDATE







///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This macro is used to decode the gather parameter list
#define	GATHERPARAMETERS(start,num)																					\
								lookup					=	new CGatherLookup;										\
								parameterlist			=	(CShaderLookup *) lookup;								\
								dirty();																			\
								lookup->outputs			=	NULL;													\
								lookup->nonShadeOutputs	=	NULL;													\
								lookup->category		=	"irradiance";											\
								lookup->numSamples		=	1;														\
								lookup->bias			=	currentShadingState->currentObject->attributes->shadowBias;	\
								lookup->coneAngle		=	(float) (C_PI/2.0);										\
								lookup->da				=	min(tanf(lookup->coneAngle),DEFAULT_RAY_DA);			\
								lookup->maxDist			=	C_INFINITY;												\
								lookup->maxRayDepth		=	CRenderer::maxRayDepth;									\
								lookup->label			=	rayLabelGather;											\
								lookup->uniformDist		=	FALSE;													\
								{																					\
									int		i;																		\
									const char	**param;															\
									const float	*valf;																\
									const char	**vals;																\
																													\
									for (i=0;i<num;i++) {															\
										operand(i*2+start,param,const char **);										\
										operand(i*2+start+1,valf,const float *);									\
										operand(i*2+start+1,vals,const char **);									\
																													\
										if (strcmp(*param,"bias") == 0) {											\
											lookup->bias		=	valf[0];										\
										} else if (strcmp(*param,"blur") == 0) {									\
											lookup->coneAngle	=	(float) (C_PI*valf[0]/2.0);						\
										} else if (strcmp(*param,"maxdist") == 0) {									\
											lookup->maxDist		=	valf[0];										\
										} else if (strcmp(*param,"samplecone") == 0) {								\
											lookup->coneAngle	=	valf[0];										\
											lookup->da			=	min(tanf(lookup->coneAngle),DEFAULT_RAY_DA);	\
										} else if (strcmp(*param,"label") == 0) {									\
											lookup->label		=	*vals;											\
										} else if (strcmp(*param,"distribution") == 0) {							\
											if (strcmp(*vals,"uniform") == 0) {										\
												lookup->uniformDist	=	TRUE;										\
											} else if (strcmp(*vals,"cosine") == 0) {								\
												lookup->uniformDist	=	FALSE;										\
											} else {																\
												error(CODE_BADTOKEN,"Unknown gather distribution: \"%s\"\n",vals[0]);	\
											}																		\
										} else { 																	\
											lookup->addOutput(*param,i*2+start+1);									\
										}																			\
									}																				\
								}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// gather	"o=spnff!"
#ifndef INIT_SHADING
#define	GATHERHEADEREXPR_PRE	CGatherLookup	*lookup;															\
								osLock(CRenderer::shaderMutex);														\
								if ((lookup = (CGatherLookup *) parameterlist) == NULL) {							\
									const float		*samples,*sampleCone;											\
									int				numArguments;													\
									const char		**category;														\
									argumentcount(numArguments);													\
									GATHERPARAMETERS(5,(numArguments-5) >> 1);										\
									operand(0,category,const char **);												\
									operand(3,sampleCone,float *);													\
									operand(4,samples,float *);														\
									lookup->numSamples				=	(int) *samples;								\
									lookup->coneAngle				=	*sampleCone;								\
								}																					\
								osUnlock(CRenderer::shaderMutex);													\
																													\
																													\
								lastGather							=	new CGatherBundle;							\
								lastGather->outputs					=	(float **) ralloc((lookup->numOutputs + lookup->numNonShadeOutputs)*sizeof(float *),threadMemory);	\
								lastGather->nonShadeOutputs			=	lastGather->outputs + lookup->numOutputs;	\
								lastGather->lookup					=	lookup;										\
								lastGather->remainingSamples		=	lookup->numSamples;							\
								lastGather->numMisses				=	0;											\
								lastGather->label					=	lookup->label;								\
																													\
								CGatherVariable	*var;																\
								int				cOutput;															\
								for (cOutput=0,var=lookup->outputs;var!=NULL;var=var->next,cOutput++) {				\
									operand(var->destIndex,lastGather->outputs[cOutput],float *);					\
								}																					\
								assert(cOutput == lookup->numOutputs);												\
																													\
								for (cOutput=0,var=lookup->nonShadeOutputs;var!=NULL;var=var->next,cOutput++) {		\
									operand(var->destIndex,lastGather->nonShadeOutputs[cOutput],float *);			\
								}																					\
																													\
								const float *P,*N;																	\
								operand(1,P,const float *);															\
								operand(2,N,const float *);															\
																													\
								CGatherRay		*rays;																\
								lastGather->ab						=	rayDiff(P,N,NULL);							\
								lastGather->rays					=	(CRay **) ralloc(numVertices*sizeof(CGatherRay *),threadMemory);		\
								lastGather->raysStorage				=	lastGather->rays;							\
								lastGather->raysBase	=	rays	=	(CGatherRay *) ralloc(numVertices*sizeof(CGatherRay),threadMemory);
								


#define GATHERHEADEREXPR		movvv(rays->from,P);																\
								movvv(rays->gatherDir,N);

#define GATHERHEADEREXPR_UPDATE	P	+=	3;																			\
								N	+=	3;																			\
								rays++;

#else
#define	GATHERHEADEREXPR_PRE
#define	GATHERHEADEREXPR
#define GATHERHEADEREXPR_UPDATE
#endif

DEFSHORTFUNC(GatherHeader		,"gatherHeader"	,"o=spnff!"	,GATHERHEADEREXPR_PRE,GATHERHEADEREXPR,GATHERHEADEREXPR_UPDATE,NULL_EXPR,PARAMETER_DERIVATIVE)

#undef	GATHERHEADEREXPR_PRE
#undef	GATHERHEADEREXPR
#undef  GATHERHEADEREXPR_UPDATE




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// rayinfo	"f=s."
#ifndef INIT_SHADING
#define	RAYINFOEXPR_PRE		float		*res;													\
							const char	**op1;													\
							const char	**op2s;													\
							float		*op2f;													\
							const float	*P	=	varying[VARIABLE_P];							\
							const float	*I	=	varying[VARIABLE_I];							\
							int			stepSize;												\
							operand(0,res,float *);												\
							operand(1,op1,const char **);										\
							operand(2,op2f,float *);											\
							operand(2,op2s,const char **);

#define	RAYINFOEXPR			if (strcmp(*op1,"label") == 0) {									\
								*op2s		=	currentRayLabel;								\
								*res		=	1;												\
								stepSize	=	1;												\
							} else if (strcmp(*op1,"depth") == 0) {								\
								*op2f		=	(float) currentRayDepth;						\
								*res		=	1;												\
								stepSize	=	1;												\
							} else if (strcmp(*op1,"origin") == 0) {							\
								op2f[0]		=	P[0] - I[0];									\
								op2f[1]		=	P[1] - I[1];									\
								op2f[2]		=	P[2] - I[2];									\
								*res		=	1;												\
								stepSize	=	3;												\
							} else if (strcmp(*op1,"direction") == 0) {							\
								normalizev(op2f,I);												\
								*res		=	1;												\
								stepSize	=	3;												\
							} else if (strcmp(*op1,"length") == 0) {							\
								*op2f		=	lengthv(I);										\
								*res		=	1;												\
								stepSize	=	1;												\
							} else {															\
								*res		=	(float) 0;										\
								stepSize	=	1;												\
							}


#define	RAYINFOEXPR_UPDATE	res++;																\
							op1++;																\
							op2s	+=	stepSize;												\
							op2f	+=	stepSize;												\
							P		+=	3;														\
							I		+=	3;

#else
#define	RAYINFOEXPR_PRE
#define	RAYINFOEXPR
#define	RAYINFOEXPR_UPDATE
#endif

DEFSHORTFUNC(RayInfo		,"rayinfo"	,"f=s."	,RAYINFOEXPR_PRE,RAYINFOEXPR,RAYINFOEXPR_UPDATE,NULL_EXPR,0)

#undef	RAYINFOEXPR_PRE
#undef	RAYINFOEXPR
#undef	RAYINFOEXPR_UPDATE




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// raylabel	"s="
#ifndef INIT_SHADING
#define	RAYLABELEXPR_PRE	const char	**res;					\
							operand(0,res,const char **);

#define	RAYLABELEXPR		*res	=	currentRayLabel;

#else
#define	RAYLABELEXPR_PRE
#define	RAYLABELEXPR
#endif

DEFSHORTFUNC(RayLabel		,"raylabel"	,"s="	,RAYLABELEXPR_PRE,RAYLABELEXPR,FUN1EXPR_UPDATE(1),NULL_EXPR,0)

#undef	RAYLABELEXPR_PRE
#undef	RAYLABELEXPR


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// raydepth	"f="
#ifndef INIT_SHADING
#define	RAYDEPTHEXPR	*res	=	(float) currentRayDepth;

#else
#define	RAYDEPTHEXPR
#endif

DEFSHORTFUNC(RayDepth		,"raydepth"	,"f="	,FUN1EXPR_PRE,RAYDEPTHEXPR,FUN1EXPR_UPDATE(1),NULL_EXPR,0)

#undef	RAYDEPTHEXPR

