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
// transmission	"c=pp!"
#ifndef INIT_SHADING
#define	TRANSMISSIONEXPR_PRE	plBegin(CTraceLookup,3);										\
								CTraceLocation	*rays	=	(CTraceLocation *)	ralloc(numVertices*sizeof(CTraceLocation),threadMemory);	\
								float			*dFdu	=	(float *)			ralloc(numVertices*12*sizeof(float),threadMemory);			\
								float			*dFdv	=	dFdu + numVertices*3;				\
								float			*dTdu	=	dFdv + numVertices*3;				\
								float			*dTdv	=	dTdu + numVertices*3;				\
								float			*res;											\
								const float		*op1,*op2;										\
								operand(0,res,float *);											\
								operand(1,op1,const float *);									\
								duVector(dFdu,op1);												\
								dvVector(dFdv,op1);												\
								operand(2,op2,const float *);									\
								duVector(dTdu,op2);												\
								dvVector(dTdv,op2);												\
								const float		*du		=	varying[VARIABLE_DU];				\
								const float		*dv		=	varying[VARIABLE_DV];				\
								const float		*N		=	varying[VARIABLE_N];				\
								const float		*time	=	varying[VARIABLE_TIME];				\
								int				numRays	=	0;


#define	TRANSMISSIONEXPR		plReady();						\
								rays->res	=	res;			\
								movvv(rays->P,op1);				\
								mulvf(rays->dPdu,dFdu,*du);		\
								mulvf(rays->dPdv,dFdv,*dv);		\
								movvv(rays->D,op2);				\
								mulvf(rays->dDdu,dTdu,*du);		\
								mulvf(rays->dDdv,dTdv,*dv);		\
								movvv(rays->N,N);				\
								rays->coneAngle		=	scratch->traceParams.coneAngle;							\
								rays->numSamples	=	(int) scratch->traceParams.samples;						\
								rays->bias			=	scratch->traceParams.bias;								\
								rays->sampleBase	=	scratch->traceParams.sampleBase;						\
								rays->maxDist		=	scratch->traceParams.maxDist;							\
								rays->time			=	*time;	\
								rays++;							\
								numRays++;

#define	TRANSMISSIONEXPR_UPDATE(__n)							\
								res		+=	__n;				\
								op1		+=	3;					\
								op2		+=	3;					\
								dFdu	+=	3;					\
								dFdv	+=	3;					\
								dTdu	+=	3;					\
								dTdv	+=	3;					\
								N		+=	3;					\
								du++;	dv++;	++time;			\
								plStep();

// Actually compule the transmission color
#define	TRANSMISSIONEXPR_POST	if (numRays > 0) {				\
									rays	-=	numRays;		\
									traceTransmission(numRays,rays,FALSE);								\
									for (int i=numRays;i>0;i--,rays++)	movvv(rays->res,rays->C);		\
									expandVector(res);			\
								}								\
								plEnd();


// Just check whether there's smtg between the end points
#define	VISIBILITYEXPR_POST		if (numRays > 0) {				\
									rays	-=	numRays;		\
									traceTransmission(numRays,rays,TRUE);								\
									for (int i=numRays;i>0;i--,rays++)	*rays->res	=	rays->t < C_INFINITY;		\
									expandFloat(res);			\
								}								\
								plEnd();

#else

#define	TRANSMISSIONEXPR_PRE
#define	TRANSMISSIONEXPR
#define	TRANSMISSIONEXPR_UPDATE
#define	TRANSMISSIONEXPR_POST
#define	VISIBILITYEXPR_POST

#endif

DEFSHORTFUNC(Visibility			,"visibility"			,"f=pp!"		,TRANSMISSIONEXPR_PRE,TRANSMISSIONEXPR,TRANSMISSIONEXPR_UPDATE(1),VISIBILITYEXPR_POST,PARAMETER_RAYTRACE | PARAMETER_DERIVATIVE | PARAMETER_DU | PARAMETER_DV | PARAMETER_TIME)
DEFSHORTFUNC(Transmission		,"transmission"			,"c=pp!"		,TRANSMISSIONEXPR_PRE,TRANSMISSIONEXPR,TRANSMISSIONEXPR_UPDATE(3),TRANSMISSIONEXPR_POST,PARAMETER_RAYTRACE | PARAMETER_DERIVATIVE | PARAMETER_DU | PARAMETER_DV | PARAMETER_TIME)





///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// trace	"c=pv!"
// NONE: Trace is derived from transmission
#ifndef INIT_SHADING
#define	TRACEEXPR_PRE			TRANSMISSIONEXPR_PRE

#define	TRACEEXPR				TRANSMISSIONEXPR

#define	TRACEEXPR_UPDATE(__n)	TRANSMISSIONEXPR_UPDATE(__n)

// Do a full raytrace
#define	TRACEEXPR_POST			if (numRays > 0) {													\
									rays	-=	numRays;											\
									traceReflection(numRays,rays,FALSE);							\
									for (int i=numRays;i>0;i--,rays++)	movvv(rays->res,rays->C);	\
									expandVector(res);												\
								}																	\
								plEnd();

// Just compute the nearest intersection
#define	TRACE2EXPR_POST			if (numRays > 0) {													\
									rays	-=	numRays;											\
									traceReflection(numRays,rays,TRUE);								\
									for (int i=numRays;i>0;i--,rays++)	*rays->res	=	rays->t;	\
									expandFloat(res);												\
								}																	\
								plEnd();

#else

#define	TRACEEXPR_PRE
#define	TRACEEXPR
#define	TRACEEXPR_UPDATE
#define	TRACEEXPR_POST
#define	TRACE2EXPR_POST	

#endif

DEFSHORTFUNC(TraceF				,"trace"				,"f=pv!"		,TRACEEXPR_PRE,TRACEEXPR,TRACEEXPR_UPDATE(1),TRACE2EXPR_POST,PARAMETER_RAYTRACE  | PARAMETER_DERIVATIVE | PARAMETER_DU | PARAMETER_DV)
DEFSHORTFUNC(TraceV				,"trace"				,"c=pv!"		,TRACEEXPR_PRE,TRACEEXPR,TRACEEXPR_UPDATE(3),TRACEEXPR_POST,PARAMETER_RAYTRACE  | PARAMETER_DERIVATIVE | PARAMETER_DU | PARAMETER_DV)


#undef	TRACEEXPR_PRE
#undef	TRACEEXPR
#undef	TRACEEXPR_UPDATE
#undef	TRACEEXPR_POST
#undef	TRACE2EXPR_POST

#undef	TRANSMISSIONEXPR_PRE
#undef	TRANSMISSIONEXPR
#undef	TRANSMISSIONEXPR_UPDATE
#undef	TRANSMISSIONEXPR_POST
#undef	VISIBILITYEXPR_POST



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// indirectdiffuse	"c=pnf!"
#ifndef INIT_SHADING
#define	IDEXPR_PRE(__occlusion)	FUN4EXPR_PRE;																						\
								plBegin(COcclusionLookup,4);																		\
								CTexture3d	*cache;																					\
								if ((cache = lookup->map) == NULL) {																\
									const float		*from,*to;																		\
									findCoordinateSystem(scratch->texture3dParams.coordsys,from,to);								\
									const CAttributes		*currentAttributes	=	currentShadingState->currentObject->attributes;	\
									osLock(CRenderer::shaderMutex);																	\
									const char *mode = scratch->occlusionParams.cacheMode;											\
									if (scratch->occlusionParams.pointHierarchyName != NULL)	mode = ""; /* prevent writes */		\
									lookup->map	=	cache		=	CRenderer::getCache(scratch->occlusionParams.cacheHandle,mode,from,to);	\
									if (scratch->occlusionParams.environmentMapName != NULL && 										\
										scratch->occlusionParams.environmentMapName[0] != 0)	lookup->environment		=	CRenderer::getEnvironment(scratch->occlusionParams.environmentMapName);								\
									if (scratch->occlusionParams.pointHierarchyName != NULL &&										\
										scratch->occlusionParams.pointHierarchyName[0] != 0)	lookup->pointHierarchy	=	CRenderer::getTexture3d(scratch->occlusionParams.pointHierarchyName,FALSE,"_area",from,to,TRUE);	\
									cache->resolve(lookup->numChannels,lookup->channelName,lookup->channelEntry,lookup->channelSize);															\
									osUnlock(CRenderer::shaderMutex);																\
								}																									\
								float		*dPdu	=	(float *) ralloc(numVertices*6*sizeof(float),threadMemory);					\
								float		*dPdv	=	dPdu + numVertices*3;														\
								duVector(dPdu,op1);																					\
								dvVector(dPdv,op1);																					\
								const float	*du		=	varying[VARIABLE_DU];														\
								const float	*dv		=	varying[VARIABLE_DV];														\
								assert(cache->dataSize == 7);																		\
																																	\
								scratch->occlusionParams.environment	=	lookup->environment;									\
								scratch->occlusionParams.pointHierarchy	=	lookup->pointHierarchy;									\
																																	\
								float	C[7];																						\
								float	**channelValues = (float **) ralloc(lookup->numChannels*sizeof(const float *),threadMemory);\
																																	\
								for (int channel=0;channel<lookup->numChannels;++channel) {											\
									operand(lookup->channelIndex[channel],channelValues[channel],float *);							\
								}																									\
								const float	savedSamples	=	scratch->traceParams.samples;										\
								scratch->occlusionParams.occlusion	=	__occlusion;


#define	IDEXPR(__occlusion)		plReady();																							\
								mulvf(dPdu,*du);																					\
								mulvf(dPdv,*dv);																					\
								scratch->traceParams.samples	=	*op3;															\
								cache->lookup(C,op1,dPdu,dPdv,op2,this);															\
								texture3Dunpack(C,lookup->numChannels,channelValues,lookup->channelEntry,lookup->channelSize);		\
								if (__occlusion)	*res	=	C[3];																\
								else				movvv(res,C);


#define	IDEXPR_UPDATE(__n)		FUN4EXPR_UPDATE(__n,3,3,1)																			\
								plStep();																							\
								dPdu	+=	3;																						\
								dPdv	+=	3;																						\
								du++;	dv++;																						\
								for (int channel=0;channel<lookup->numChannels;++channel) {											\
									channelValues[channel]	+=	lookup->channelSize[channel];										\
								}

#define	IDEXPR_POST(__occlusion)													\
								if (__occlusion)	{								\
									expandFloat(res);								\
								} else {											\
									expandVector(res);								\
								}													\
								scratch->traceParams.samples	=	savedSamples;	\
								plEnd();
#else
#define	IDEXPR_PRE
#define	IDEXPR
#define	IDEXPR_UPDATE
#define	IDEXPR_POST(__occlusion)
#endif

DEFSHORTFUNC(Occlusion			,"occlusion"		,"f=pnf!"	,IDEXPR_PRE(TRUE),IDEXPR(TRUE),IDEXPR_UPDATE(1),IDEXPR_POST(TRUE),PARAMETER_RAYTRACE | PARAMETER_DERIVATIVE)
DEFSHORTFUNC(Indirectdiffuse	,"indirectdiffuse"	,"c=pnf!"	,IDEXPR_PRE(FALSE),IDEXPR(FALSE),IDEXPR_UPDATE(3),IDEXPR_POST(FALSE),PARAMETER_RAYTRACE | PARAMETER_DERIVATIVE)

#undef	IDEXPR_PRE
#undef	IDEXPR
#undef	IDEXPR_UPDATE
#undef	IDEXPR_POST



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// photonmap	"c=spn!"
#ifndef INIT_SHADING
#define	PHOTONMAPEXPR_PRE		plBegin(CPhotonMapLookup,4);													\
								CPhotonMap	*map;																\
								if ((map = lookup->map) == NULL) {												\
									const char	**op1;															\
									operand(1,op1,const char **);												\
									osLock(CRenderer::shaderMutex);												\
									lookup->map = map	=	CRenderer::getPhotonMap(*op1);						\
									osUnlock(CRenderer::shaderMutex);											\
								}																				\
								float		*res;																\
								const float	*op2,*op3;															\
								const int	estimator	=	(scratch->photonmapParams.estimator == 0 ? currentShadingState->currentObject->attributes->photonEstimator : (int) scratch->photonmapParams.estimator);	\
								operand(0,res,float *);															\
								operand(2,op2,const float *);													\
								operand(3,op3,const float *);


#define	PHOTONMAPEXPR			plReady();																		\
								map->lookup(res,op2,estimator);

#define	PHOTONMAPEXPR_UPDATE	res	+=	3;																		\
								op2	+=	3;																		\
								op3	+=	3;																		\
								plStep();

#define	PHOTONMAPEXPR_POST		expandVector(res);	plEnd();

#else
#define	PHOTONMAPEXPR_PRE
#define	PHOTONMAPEXPR
#define	PHOTONMAPEXPR_UPDATE
#define	PHOTONMAPEXPR_POST
#endif

DEFSHORTFUNC(Photonmap			,"photonmap"	,"c=Spn!"	,PHOTONMAPEXPR_PRE,PHOTONMAPEXPR,PHOTONMAPEXPR_UPDATE,PHOTONMAPEXPR_POST,0)

#undef	PHOTONMAPEXPR_PRE
#undef	PHOTONMAPEXPR
#undef	PHOTONMAPEXPR_UPDATE
#undef	PHOTONMAPEXPR_POST



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// photonmap	"c=sp!"
#ifndef INIT_SHADING
#define	PHOTONMAP2EXPR_PRE		plBegin(CPhotonMapLookup,3);													\
								CPhotonMap	*map;																\
								if ((map = lookup->map) == NULL) {												\
									const char	**op1;															\
									operand(1,op1,const char **);												\
									osLock(CRenderer::shaderMutex);												\
									lookup->map = map	=	CRenderer::getPhotonMap(*op1);						\
									osUnlock(CRenderer::shaderMutex);											\
								}																				\
								float		*res;																\
								const float	*op2;																\
								const int	estimator	=	(scratch->photonmapParams.estimator == 0 ? currentShadingState->currentObject->attributes->photonEstimator : (int) scratch->photonmapParams.estimator);	\
								operand(0,res,float *);															\
								operand(2,op2,const float *);

#define	PHOTONMAP2EXPR			plReady();																		\
								map->lookup(res,op2,estimator);

#define	PHOTONMAP2EXPR_UPDATE	res	+=	3;																		\
								op2	+=	3;																		\
								plStep();

#define	PHOTONMAP2EXPR_POST		expandVector(res);	plEnd();

#else
#define	PHOTONMAP2EXPR_PRE

#define	PHOTONMAP2EXPR

#define	PHOTONMAP2EXPR_UPDATE

#define	PHOTONMAP2EXPR_POST
#endif

DEFSHORTFUNC(Photonmap2			,"photonmap"	,"c=Sp!"	,PHOTONMAP2EXPR_PRE,PHOTONMAP2EXPR,PHOTONMAP2EXPR_UPDATE,PHOTONMAP2EXPR_POST,0)

#undef	PHOTONMAP2EXPR_PRE

#undef	PHOTONMAP2EXPR

#undef	PHOTONMAP2EXPR_UPDATE

#undef	PHOTONMAP2EXPR_POST



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// gather	"o=spnff!"
#ifndef INIT_SHADING
#define	GATHERHEADEREXPR_PRE	plBegin(CGatherLookup,5);															\
								const float		*samples,*sampleCone;												\
								const float		*P,*D;																\
								operand(1,P,const float *);															\
								operand(2,D,const float *);															\
								operand(3,sampleCone,float *);														\
								operand(4,samples,float *);															\
																													\
								lastGather							=	new CGatherBundle;							\
								lastGather->numOutputs				=	lookup->numOutputs;							\
								lastGather->numNonShadeOutputs		=	lookup->numNonShadeOutputs;					\
								lastGather->outputs					=	(float **) ralloc((lookup->numOutputs + lookup->numNonShadeOutputs)*sizeof(float *),threadMemory);	\
								lastGather->nonShadeOutputs			=	lastGather->outputs + lookup->numOutputs;	\
								lastGather->outputVars				=	lookup->outputs;							\
								lastGather->nonShadeOutputVars		=	lookup->nonShadeOutputs;					\
								lastGather->remainingSamples		=	(int) *samples;								\
								lastGather->numMisses				=	0;											\
								lastGather->label					=	scratch->traceParams.label;					\
								lastGather->numSamples				=	(int) *samples;								\
								assert(lastGather->label != NULL);													\
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
								const float	*du		=	varying[VARIABLE_DU];										\
								const float	*dv		=	varying[VARIABLE_DV];										\
								float		*dPdu	=	(float *) ralloc(numVertices*6*sizeof(float),threadMemory);	\
								float		*dPdv	=	dPdu + numVertices*3;										\
								duVector(dPdu,P);																	\
								dvVector(dPdv,P);																	\
																													\
								/* Figure out the ray distribution */												\
								lastGather->uniformDist				=	FALSE;										\
								if (scratch->gatherParams.distribution != NULL) {									\
									if (strcmp(scratch->gatherParams.distribution,"uniform") == 0)		lastGather->uniformDist	=	TRUE;	\
									else if (strcmp(scratch->gatherParams.distribution,"cosine") == 0)	lastGather->uniformDist	=	FALSE;	\
								}																					\
																													\
								CGatherRay		*rays;																\
								lastGather->rays					=	(CRay **) ralloc(numVertices*sizeof(CGatherRay *),threadMemory);		\
								lastGather->raysStorage				=	lastGather->rays;							\
								lastGather->raysBase	=	rays	=	(CGatherRay *) ralloc(numVertices*sizeof(CGatherRay),threadMemory);
								


#define GATHERHEADEREXPR		plReady();																			\
								mulvf(dPdu,*du);																	\
								mulvf(dPdv,*dv);																	\
								rays->da			=	min(max(tanf(*sampleCone),0.0f),1.0f);						\
								rays->db			=	(lengthv(dPdu) + lengthv(dPdv))*0.5f;						\
								rays->sampleCone	=	*sampleCone;												\
								rays->sampleBase	=	scratch->traceParams.sampleBase;							\
								rays->bias			=	scratch->traceParams.bias;									\
								rays->maxDist		=	scratch->traceParams.maxDist;								\
								movvv(rays->gatherDir,D);															\
								movvv(rays->gatherP,P);																\
								movvv(rays->dPdu,dPdu);																\
								movvv(rays->dPdv,dPdv);

#define GATHERHEADEREXPR_UPDATE	dPdu	+=	3;																		\
								dPdv	+=	3;																		\
								D		+=	3;																		\
								P		+=	3;																		\
								du++; dv++;																			\
								sampleCone++;																		\
								rays++;																				\
								plStep();

#define GATHERHEADEREXPR_POST	plEnd();

#else
#define	GATHERHEADEREXPR_PRE
#define	GATHERHEADEREXPR
#define GATHERHEADEREXPR_UPDATE
#define GATHERHEADEREXPR_POST
#endif

DEFSHORTFUNC(GatherHeader		,"gatherHeader"	,"o=spnff!"	,GATHERHEADEREXPR_PRE,GATHERHEADEREXPR,GATHERHEADEREXPR_UPDATE,GATHERHEADEREXPR_POST,PARAMETER_DERIVATIVE)

#undef	GATHERHEADEREXPR_PRE
#undef	GATHERHEADEREXPR
#undef  GATHERHEADEREXPR_UPDATE
#undef	GATHERHEADEREXPR_POST




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

