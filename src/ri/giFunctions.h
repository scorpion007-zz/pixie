//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright � 1999 - 2003, Okan Arikan
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
								lookup->maxFGRadius			=	128;															\
								lookup->minFGRadius			=	2;																\
								lookup->irradianceIndex		=	-1;																\
								lookup->coverageIndex		=	-1;																\
								lookup->environmentIndex	=	-1;																\
								lookup->bias				=	attributes->shadowBias;											\
								lookup->occlusion			=	FALSE;															\
								lookup->gatherGlobal		=	1;																\
								lookup->gatherLocal			=	1;																\
								lookup->localThreshold		=	1;																\
								lookup->lengthA				=	lengthA;														\
								lookup->lengthB				=	lengthB;														\
								lookup->handle				=	(attributes->irradianceHandle		== NULL ? "temp.irr"	: attributes->irradianceHandle);			\
								lookup->filemode			=	(attributes->irradianceHandleMode	== NULL ? ""			: attributes->irradianceHandleMode);		\
								initv(lookup->backgroundColor,0);																\
								lookup->cache				=	NULL;															\
								lookup->map					=	NULL;															\
								lookup->environment			=	NULL;															\
								{																								\
									int		i;																					\
									TCode	*param,*val;																		\
																																\
									for (i=0;i<num;i++) {																		\
										operand(i*2+start,param);																\
										operand(i*2+start+1,val);																\
																																\
										if (strcmp(param->string,"estimator") == 0) {											\
											lookup->numLookupSamples	=	(int) val->real;									\
										} else if (strcmp(param->string,"maxdist") == 0) {										\
											lookup->maxDistance	=	val->real;													\
										} else if (strcmp(param->string,"maxerror") == 0) {										\
											lookup->maxError	=	val->real;													\
											if (lookup->maxError > 0)	lookup->maxError = 0.5f/lookup->maxError;				\
										} else if (strcmp(param->string,"samples") == 0) {										\
											lookup->numSamples	=	(int) val->real;											\
										} else if (strcmp(param->string,"bias") == 0) {											\
											lookup->bias		=	val->real;													\
										} else if (strcmp(param->string,"localThreshold") == 0) {								\
											lookup->localThreshold	=	val->real;												\
										} else if (strcmp(param->string,"backgroundColor") == 0) {								\
											movvv(lookup->backgroundColor,&val->real);											\
										} else if (strcmp(param->string,"maxBrightness") == 0) {								\
											lookup->maxBrightness	=	val->real;												\
										} else if (strcmp(param->string,"minR") == 0) {											\
											lookup->minFGRadius	=	val->real;													\
										} else if (strcmp(param->string,"maxR") == 0) {											\
											lookup->maxFGRadius	=	val->real;													\
										} else if (strcmp(param->string,"global") == 0) {										\
											lookup->gatherGlobal	=	(int) val->real;										\
										} else if (strcmp(param->string,"local") == 0) {										\
											lookup->gatherLocal		=	(int) val->real;										\
										} else if (strcmp(param->string,"handle") == 0) {										\
											lookup->handle			=	(const char *) val->string;								\
										} else if (strcmp(param->string,"filemode") == 0) {										\
											lookup->filemode		=	(const char *) val->string;								\
										} else if (strcmp(param->string,"environmentmap") == 0) {								\
											lookup->environment		=	getEnvironment(val->string);							\
										} else if (strcmp(param->string,"irradiance") == 0) {									\
											lookup->irradianceIndex	=	i*2+start+1;											\
										} else if (strcmp(param->string,"occlusion") == 0) {									\
											lookup->coverageIndex	=	i*2+start+1;											\
										} else if (strcmp(param->string,"environmentdir") == 0) {								\
											lookup->environmentIndex=	i*2+start+1;											\
										}																						\
									}																							\
								}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// transmission	"c=pp!"
#ifndef INIT_SHADING
#define	TRANSMISSIONEXPR_PRE	TCode			*res,*op1,*op2;																	\
								CTextureLookup	*lookup;																		\
								CRaySample		*samples	=	(CRaySample *) ralloc(numVertices*sizeof(CRaySample));			\
								CRaySample		*cSample	=	samples;														\
								if ((lookup = (CTextureLookup *) parameterlist) == NULL) {										\
									int			numArguments;																	\
									argumentcount(numArguments);																\
									TEXTUREPARAMETERS(3,(numArguments-3) >> 1);													\
								}																								\
								operand(0,res);																					\
								operand(1,op1);																					\
								operand(2,op2);

#define	TRANSMISSIONEXPR		cSample->res	=	&res->real;																	\
								movvv(cSample->from,&op1->real);																\
								movvv(cSample->to,&op2->real);																	\
								cSample++;


#define	TRANSMISSIONEXPR_UPDATE	res	+=	3;																						\
								op1	+=	3;																						\
								op2	+=	3;

#define	TRANSMISSIONEXPR_POST	traceTransmission(cSample-samples,samples,lookup);

#else

#define	TRANSMISSIONEXPR_PRE

#define	TRANSMISSIONEXPR

#define	TRANSMISSIONEXPR_UPDATE

#define	TRANSMISSIONEXPR_POST

#endif

DEFFUNC(TRANSMISSION			,"transmission"			,"c=pp!"		,TRANSMISSIONEXPR_PRE,TRANSMISSIONEXPR,TRANSMISSIONEXPR_UPDATE,TRANSMISSIONEXPR_POST,PARAMETER_RAYTRACE)

#undef	TRANSMISSIONEXPR_PRE

#undef	TRANSMISSIONEXPR

#undef	TRANSMISSIONEXPR_UPDATE

#undef	TRANSMISSIONEXPR_POST



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// trace	"f=pv"
#ifndef INIT_SHADING
#define	TRACEEXPR_PRE			FUN3EXPR_PRE																						\
								const float			bias			=	currentShadingState->currentObject->attributes->shadowBias;	\
								vector				D;																				\
								CRay				ray;

#define	TRACEEXPR				subvv(D,(float *) op2,(float *) op1);															\
								ray.t					=	lengthv(D);															\
								mulvf(ray.dir,D,1/ray.t);																		\
								movvv(ray.from,&op1->real);																		\
								addvv(ray.to,D,&op1->real);																		\
								ray.flags				=	ATTRIBUTES_FLAGS_TRACE_VISIBLE;										\
								ray.time				=	urand();															\
								ray.jimp				=	-1.0f;																\
								ray.tmin				=	bias;																\
								ray.t					-=	bias;																\
								ray.invDir[COMP_X]		=	1/ray.dir[COMP_X];													\
								ray.invDir[COMP_Y]		=	1/ray.dir[COMP_Y];													\
								ray.invDir[COMP_Z]		=	1/ray.dir[COMP_Z];													\
								ray.lastXform			=	NULL;																\
								ray.object				=	NULL;																\
																																\
								hierarchy->intersect(&ray);																		\
																																\
								res->real				=	ray.t


#else
#define	TRACEEXPR_PRE
#define	TRACEEXPR
#endif

DEFSHORTFUNC(Tracef			,"trace"			,"f=pv"		,TRACEEXPR_PRE,TRACEEXPR,FUN3EXPR_UPDATE(1,3,3),NULL_EXPR,PARAMETER_RAYTRACE)

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
									TCode	*param,*val;															\
																													\
									for (i=0;i<num;i++) {															\
										operand(i*2+start,param);													\
										operand(i*2+start+1,val);													\
																													\
										if (strcmp(param->string,"bias") == 0) {									\
											lookup->bias		=	val->real;										\
										} else if (strcmp(param->string,"label") == 0) {							\
											lookup->label		=	val->string;									\
										}																			\
									}																				\
								}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// trace	"c=pv!"
#ifndef INIT_SHADING
#define	TRACEEXPR_PRE			TCode				*res;																		\
								const TCode			*op1,*op2;																	\
								CTraceBundle		interiorBundle,exteriorBundle;												\
								CTraceRay			*rays;																		\
								CTraceRay			**interiorRays,**exteriorRays;												\
								int					cExterior		=	0;														\
								int					cInterior		=	0;														\
								const CAttributes	*cAttributes	=	currentShadingState->currentObject->attributes;			\
								float				*N;																			\
								CTraceLookup		*lookup;																	\
								if ((lookup = (CTraceLookup *) parameterlist) == NULL) {										\
									int			numArguments;																	\
									argumentcount(numArguments);																\
									TRACEPARAMETERS(3,(numArguments-3) >> 1);													\
								}																								\
								rays			=	(CTraceRay *) ralloc(numVertices*sizeof(CTraceRay));						\
								interiorRays	=	(CTraceRay **) ralloc(numVertices*sizeof(CTraceRay *));						\
								exteriorRays	=	(CTraceRay **) ralloc(numVertices*sizeof(CTraceRay *));						\
								N				=	varying[VARIABLE_N];														\
								operand(0,res);																					\
								operand(1,op1);																					\
								operand(2,op2);

#define	TRACEEXPR				if (dotvv((float *) op2,(float *) op2) > 0) {													\
									movvv(rays->from,(float *) op1);															\
									normalizev(rays->dir,(float *) op2);														\
									initv((float *) res,0);																		\
									rays->dest			=	(float *) res;														\
									rays->multiplier	=	1;																	\
									rays->t				=	C_INFINITY;															\
									rays->time			=	urand();															\
									rays->flags			=	ATTRIBUTES_FLAGS_TRACE_VISIBLE;										\
									rays->tmin			=	lookup->bias;																\
									if (dotvv(&op2->real,N) > 0) {																\
										exteriorRays[cExterior++]	=	rays++;													\
									} else {																					\
										interiorRays[cInterior++]	=	rays++;													\
									}																							\
								} else {																						\
									initv((float *) res,0);																		\
								}



#define	TRACEEXPR_UPDATE		FUN3EXPR_UPDATE(3,3,3);																			\
								N					+=	3;

#define	TREACEEXPR_POST			if (inShadow == FALSE) {																		\
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

DEFSHORTFUNC(TraceV				,"trace"				,"c=pv!"		,TRACEEXPR_PRE,TRACEEXPR,TRACEEXPR_UPDATE,TREACEEXPR_POST,PARAMETER_N | PARAMETER_RAYTRACE)

#undef	TRACEEXPR_PRE
#undef	TRACEEXPR
#undef	TRACEEXPR_UPDATE
#undef	TREACEEXPR_POST



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// visibility	"f=pp"
#ifndef INIT_SHADING
#define	VISIBILITYEXPR_PRE		FUN3EXPR_PRE																						\
								const float			bias			=	currentShadingState->currentObject->attributes->shadowBias;	\
								vector				D;																				\
								CRay				ray;

#define	VISIBILITYEXPR			subvv(D,(float *) op2,(float *) op1);															\
								ray.t					=	lengthv(D);															\
								mulvf(ray.dir,D,1/ray.t);																		\
								movvv(ray.from,&op1->real);																		\
								addvv(ray.to,D,&op1->real);																		\
								ray.flags				=	ATTRIBUTES_FLAGS_TRANSMISSION_VISIBLE;								\
								ray.time				=	urand();															\
								ray.jimp				=	-1.0f;																\
								ray.tmin				=	bias;																\
								ray.t					-=	bias;																\
								ray.invDir[COMP_X]		=	1/ray.dir[COMP_X];													\
								ray.invDir[COMP_Y]		=	1/ray.dir[COMP_Y];													\
								ray.invDir[COMP_Z]		=	1/ray.dir[COMP_Z];													\
								ray.lastXform			=	NULL;																\
								ray.object				=	NULL;																\
																																\
								hierarchy->intersect(&ray);																		\
																																\
								if (ray.object != NULL)	res[0].real	=	0;														\
								else					res[0].real	=	1;


#else
#define	VISIBILITYEXPR_PRE
#define	VISIBILITYEXPR
#endif

DEFSHORTFUNC(Visibility			,"visibility"			,"f=pp"		,VISIBILITYEXPR_PRE,VISIBILITYEXPR,FUN3EXPR_UPDATE(1,3,3),NULL_EXPR,PARAMETER_RAYTRACE)

#undef	VISIBILITYEXPR_PRE
#undef	VISIBILITYEXPR

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// indirectdiffuse	"c=pnf!"
#ifndef INIT_SHADING
#define	IDEXPR_PRE				CGlobalIllumLookup	*lookup;																		\
								CCache				*cache;																			\
								float				C[7];																			\
								TCode				*envdir;																		\
								TCode				*coverage;																		\
								FUN4EXPR_PRE;																						\
								if ((lookup = (CGlobalIllumLookup *) parameterlist) == NULL) {										\
									CAttributes	*attributes	=	currentShadingState->currentObject->attributes;						\
									int			numArguments;																		\
									argumentcount(numArguments);																	\
									GLOBPARAMETERS(4,(numArguments-4) >> 1);														\
									lookup->cache		=	getCache(lookup->handle,lookup->filemode);								\
									lookup->numSamples	=	(int) op3->real;														\
									lookup->occlusion	=	FALSE;																	\
								}																									\
								if (lookup->environmentIndex != -1) {	operand(lookup->environmentIndex,envdir);	}				\
								else envdir = (TCode *) varying[VARIABLE_PW];														\
								if (lookup->coverageIndex != -1)	{	operand(lookup->coverageIndex,coverage);	}				\
								else coverage = (TCode *) varying[VARIABLE_PW];														\
								cache	=	lookup->cache;


#define	IDEXPR					cache->lookup(C,&op1->real,&op2->real,lookup);														\
								movvv(&res->real,C);																				\
								movvv(&envdir->real,C+4);																			\
								coverage->real = C[3];


#define	IDEXPR_UPDATE			FUN4EXPR_UPDATE(3,3,3,0)																			\
								envdir	+=	3;																						\
								coverage++;

#else
#define	IDEXPR_PRE

#define	IDEXPR
#endif

DEFSHORTFUNC(Indirectdiffuse	,"indirectdiffuse"	,"c=pnf!"	,IDEXPR_PRE,IDEXPR,IDEXPR_UPDATE,NULL_EXPR,PARAMETER_RAYTRACE)

#undef	IDEXPR_PRE

#undef	IDEXPR






///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// occlusion	"f=pnf!"
#ifndef INIT_SHADING
#define	OCCLUSIONEXPR_PRE		CGlobalIllumLookup	*lookup;																		\
								CCache				*cache;																			\
								float				C[7];																			\
								TCode				*envdir;																		\
								TCode				*irradiance;																	\
								FUN4EXPR_PRE;																						\
								if ((lookup = (CGlobalIllumLookup *) parameterlist) == NULL) {										\
									CAttributes	*attributes	=	currentShadingState->currentObject->attributes;						\
									int			numArguments;																		\
									argumentcount(numArguments);																	\
									GLOBPARAMETERS(4,(numArguments-4) >> 1);														\
									lookup->cache		=	getCache(lookup->handle,lookup->filemode);								\
									lookup->numSamples	=	(int) op3->real;														\
									lookup->occlusion	=	TRUE;																	\
									if (lookup->irradianceIndex != -1) lookup->occlusion = FALSE;									\
								}																									\
								if (lookup->environmentIndex != -1) {	operand(lookup->environmentIndex,envdir);	}				\
								else envdir = (TCode *) varying[VARIABLE_PW];														\
								if (lookup->irradianceIndex != -1)	{	operand(lookup->irradianceIndex,irradiance);	}			\
								else irradiance = (TCode *) varying[VARIABLE_PW];													\
								cache	=	lookup->cache;

#define	OCCLUSIONEXPR			cache->lookup(C,&op1->real,&op2->real,lookup);														\
								res->real	=	C[3];																				\
								movvv(&irradiance->real,C);																			\
								movvv(&envdir->real,C+4);


#define	OCCLUSIONEXPR_UPDATE	FUN4EXPR_UPDATE(1,3,3,0)																			\
								irradiance	+=	3;																					\
								envdir		+=	3;

#else
#define	OCCLUSIONEXPR_PRE

#define	OCCLUSIONEXPR
#endif

DEFSHORTFUNC(occlusion	,"occlusion"	,"f=pnf!"	,OCCLUSIONEXPR_PRE,OCCLUSIONEXPR,OCCLUSIONEXPR_UPDATE,NULL_EXPR,PARAMETER_RAYTRACE)

#undef	OCCLUSIONEXPR_PRE

#undef	OCCLUSIONEXPR




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// cachesample	"f=pnf!"
#ifndef INIT_SHADING
#define	CACSAMPLEEXPR_PRE		CGlobalIllumLookup	*lookup;																		\
								CCache				*cache;																			\
								FUN4EXPR_PRE;																						\
								if ((lookup = (CGlobalIllumLookup *) parameterlist) == NULL) {										\
									CAttributes	*attributes	=	currentShadingState->currentObject->attributes;						\
									int			numArguments;																		\
									argumentcount(numArguments);																	\
									GLOBPARAMETERS(4,(numArguments-4) >> 1);														\
									lookup->cache		=	getCache(lookup->handle,lookup->filemode);								\
									lookup->numSamples	=	(int) op3->real;														\
									lookup->occlusion	=	FALSE;																	\
								}																									\
								cache	=	lookup->cache;


#define	CACSAMPLEEXPR			cache->cachesample(&res->real,&op1->real,&op2->real,(lengthA*op1[COMP_Z].real + lengthB)*op3->real);

#else
#define	CACSAMPLEEXPR_PRE

#define	CACSAMPLEEXPR
#endif

DEFSHORTFUNC(Cachesample	,"cachesample"	,"f=pnf!"	,CACSAMPLEEXPR_PRE,CACSAMPLEEXPR,FUN4EXPR_UPDATE(1,3,3,1),NULL_EXPR,0)

#undef	CACSAMPLEEXPR_PRE

#undef	CACSAMPLEEXPR



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// photonmap	"c=spn!"
#ifndef INIT_SHADING
#define	PHOTONMAPEXPR_PRE		CGlobalIllumLookup	*lookup;													\
								CPhotonMap			*map;														\
								TCode				*res;														\
								const TCode			*op2,*op3;													\
								if ((lookup = (CGlobalIllumLookup *) parameterlist) == NULL) {					\
									CAttributes	*attributes	=	currentShadingState->currentObject->attributes;	\
									int			numArguments;													\
									const TCode	*op1;															\
									argumentcount(numArguments);												\
									GLOBPARAMETERS(4,(numArguments-4) >> 1);									\
									operand(1,op1);																\
									lookup->map			=	getPhotonMap(op1->string);							\
								}																				\
								operand(0,res);																	\
								operand(2,op2);																	\
								operand(3,op3);																	\
								map						=	lookup->map;


#define	PHOTONMAPEXPR			map->lookup(&res->real,&op2->real,&op3->real,lookup->numLookupSamples);

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
								TCode				*res;														\
								const TCode			*op2;														\
								if ((lookup = (CGlobalIllumLookup *) parameterlist) == NULL) {					\
									CAttributes	*attributes	=	currentShadingState->currentObject->attributes;	\
									int			numArguments;													\
									const TCode	*op1;															\
									argumentcount(numArguments);												\
									GLOBPARAMETERS(3,(numArguments-3) >> 1);									\
									operand(1,op1);																\
									lookup->map			=	getPhotonMap(op1->string);							\
								}																				\
								operand(0,res);																	\
								operand(2,op2);																	\
								map						=	lookup->map;

#define	PHOTONMAP2EXPR			map->lookup(&res->real,&op2->real,lookup->numLookupSamples);

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
								lookup->maxDist			=	C_INFINITY;												\
								lookup->maxRayDepth		=	maxRayDepth;											\
								lookup->label			=	rayLabelGather;											\
								lookup->uniformDist		=	FALSE;													\
								{																					\
									int		i;																		\
									TCode	*param,*val;															\
																													\
									for (i=0;i<num;i++) {															\
										operand(i*2+start,param);													\
										operand(i*2+start+1,val);													\
																													\
										if (strcmp(param->string,"bias") == 0) {									\
											lookup->bias		=	val->real;										\
										} else if (strcmp(param->string,"blur") == 0) {								\
											lookup->coneAngle	=	(float) (C_PI*val->real/2.0);					\
										} else if (strcmp(param->string,"maxdist") == 0) {							\
											lookup->maxDist		=	val->real;										\
										} else if (strcmp(param->string,"samplecone") == 0) {						\
											lookup->coneAngle	=	val->real;										\
										} else if (strcmp(param->string,"label") == 0) {							\
											lookup->label		=	val->string;									\
										} else if (strcmp(param->string,"distribution") == 0) {						\
											if (strcmp(val->string,"uniform") == 0) {								\
												lookup->uniformDist	=	TRUE;										\
											} else if (strcmp(val->string,"cosine") == 0) {							\
												lookup->uniformDist	=	FALSE;										\
											} else {																\
												error(CODE_BADTOKEN,"Unknown gather distribution: \"%s\"\n",val->string);	\
											}																		\
										} else { 																	\
											lookup->addOutput(param->string,i*2+start+1);							\
										}																			\
									}																				\
								}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// gather	"o=spnff!"
#ifndef INIT_SHADING
#define	GATHERHEADEREXPR_PRE	CGatherLookup	*lookup;															\
								CGatherRay		*rays;																\
								TCode			*P,*N;																\
								CGatherVariable	*var;																\
								if ((lookup = (CGatherLookup *) parameterlist) == NULL) {							\
									TCode			*samples,*sampleCone;											\
									int				numArguments;													\
									TCode			*category;														\
									argumentcount(numArguments);													\
									GATHERPARAMETERS(5,(numArguments-5) >> 1);										\
									operand(0,category);															\
									operand(3,sampleCone);															\
									operand(4,samples);																\
									lookup->numSamples				=	(int) samples->real;						\
									lookup->coneAngle				=	sampleCone->real;							\
								}																					\
																													\
								for (var=lookup->outputs;var!=NULL;var=var->next) {									\
									*(var->cDepth++)	=	var->dest;												\
									operand(var->destIndex,var->dest);												\
									assert((var->cDepth-var->destForEachLevel) <= (maxRayDepth+1));					\
								}																					\
								for (var=lookup->nonShadeOutputs;var!=NULL;var=var->next) {							\
									*(var->cDepth++)	=	var->dest;												\
									operand(var->destIndex,var->dest);												\
									assert((var->cDepth-var->destForEachLevel) <= (maxRayDepth+1));					\
								}																					\
																													\
								lastGather							=	new CGatherBundle;							\
								lastGather->lookup					=	lookup;										\
								lastGather->remainingSamples		=	lookup->numSamples;							\
								lastGather->numMisses				=	0;											\
								lastGather->label					=	lookup->label;								\
								operand(1,P);																		\
								operand(2,N);																		\
																													\
								lastGather->rays					=	(CRay **) ralloc(numVertices*sizeof(CGatherRay *));		\
								lastGather->raysStorage				=	lastGather->rays;							\
								lastGather->raysBase	=	rays	=	(CGatherRay *) ralloc(numVertices*sizeof(CGatherRay));
								


#define GATHERHEADEREXPR		movvv(rays->from,(float *) P);														\
								movvv(rays->gatherDir,(float *) N);

#define GATHERHEADEREXPR_UPDATE	P	+=	3;																			\
								N	+=	3;																			\
								rays++;

#else
#define	GATHERHEADEREXPR_PRE
#define	GATHERHEADEREXPR
#define GATHERHEADEREXPR_UPDATE
#endif

DEFSHORTFUNC(GatherHeader		,"gatherHeader"	,"o=spnff!"	,GATHERHEADEREXPR_PRE,GATHERHEADEREXPR,GATHERHEADEREXPR_UPDATE,NULL_EXPR,0)

#undef	GATHERHEADEREXPR_PRE
#undef	GATHERHEADEREXPR
#undef  GATHERHEADEREXPR_UPDATE




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// rayinfo	"f=s."
#ifndef INIT_SHADING
#define	RAYINFOEXPR_PRE		FUN3OUTEXPR_PRE;													\
							const	float	*P	=	varying[VARIABLE_P];						\
							const	float	*I	=	varying[VARIABLE_I];						\
							int				stepSize;

#define	RAYINFOEXPR			if (strcmp(op1->string,"label") == 0) {								\
								op2->string	=	currentRayLabel;								\
								res->real	=	1;												\
								stepSize	=	1;												\
							} else if (strcmp(op1->string,"depth") == 0) {						\
								op2->real	=	(float) currentRayDepth;						\
								res->real	=	(float ) 1;										\
								stepSize	=	1;												\
							} else if (strcmp(op1->string,"origin") == 0) {						\
								op2[0].real	=	P[0] - I[0];									\
								op2[1].real	=	P[1] - I[1];									\
								op2[2].real	=	P[2] - I[2];									\
								res->real	=	(float) 1;										\
								stepSize	=	3;												\
							} else if (strcmp(op1->string,"direction") == 0) {					\
								normalizev((float *) op2,I);									\
								res->real	=	(float) 1;										\
								stepSize	=	3;												\
							} else if (strcmp(op1->string,"length") == 0) {						\
								op2[0].real	=	lengthv(I);										\
								res->real	=	(float) 1;										\
								stepSize	=	1;												\
							} else {															\
								res->real	=	(float) 0;										\
								stepSize	=	1;												\
							}


#define	RAYINFOEXPR_UPDATE	FUN3EXPR_UPDATE(1,1,stepSize);										\
							P				+=	3;												\
							I				+=	3;

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
#define	RAYLABELEXPR	res->string	=	currentRayLabel;

#else
#define	RAYLABELEXPR
#endif

DEFSHORTFUNC(RayLabel		,"raylabel"	,"s="	,FUN1EXPR_PRE,RAYLABELEXPR,FUN1EXPR_UPDATE(1),NULL_EXPR,0)

#undef	RAYLABELEXPR


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// raydepth	"f="
#ifndef INIT_SHADING
#define	RAYDEPTHEXPR	res->real	=	(float) currentRayDepth;

#else
#define	RAYDEPTHEXPR
#endif

DEFSHORTFUNC(RayDepth		,"raydepth"	,"f="	,FUN1EXPR_PRE,RAYDEPTHEXPR,FUN1EXPR_UPDATE(1),NULL_EXPR,0)

#undef	RAYDEPTHEXPR














///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This macro is used to decode the explosion parameter list
#define	EXPPARAMETERS(start,num)																					\
								lookup							=	new CExplosionLookup;							\
								parameterlist					=	lookup;											\
								dirty();																			\
								lookup->scatteringCoefficient	=	0;												\
								lookup->explosionSpace			=	"explosion";									\
								{																					\
									int		i;																		\
									TCode	*param,*val;															\
																													\
									for (i=0;i<num;i++) {															\
										operand(i*2+start,param);													\
										operand(i*2+start+1,val);													\
																													\
										if (strcmp(param->string,"scatter") == 0) {									\
											lookup->scatteringCoefficient	=	val->real;							\
										} else if (strcmp(param->string,"space") == 0) {							\
											lookup->explosionSpace			=	val->string;						\
										}																			\
																													\
									}																				\
								}



