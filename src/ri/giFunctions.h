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
#define	TRANSMISSIONEXPR_PRE	CTextureLookup	*lookup;										\
								osLock(CRenderer::shaderMutex);									\
								if ((lookup = (CTextureLookup *) parameterlist) == NULL) {		\
									int			numArguments;									\
									argumentcount(numArguments);								\
									TEXTUREPARAMETERS(3,(numArguments-3) >> 1);					\
								}																\
								osUnlock(CRenderer::shaderMutex);								\
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
								int				numRays	=	0;


#define	TRANSMISSIONEXPR		rays->res	=	res;			\
								movvv(rays->P,op1);				\
								mulvf(rays->dPdu,dFdu,*du);		\
								mulvf(rays->dPdv,dFdv,*dv);		\
								movvv(rays->D,op2);				\
								mulvf(rays->dDdu,dTdu,*du);		\
								mulvf(rays->dDdv,dTdv,*dv);		\
								movvv(rays->N,N);				\
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
								du++;	dv++;

// Actually compule the transmission color
#define	TRANSMISSIONEXPR_POST	if (numRays > 0) {				\
									rays	-=	numRays;		\
									traceTransmission(numRays,rays,lookup,FALSE);						\
									for (int i=numRays;i>0;i--,rays++)	movvv(rays->res,rays->C);		\
									expandVector(res);			\
								}


// Just check whether there's smtg between the end points
#define	VISIBILITYEXPR_POST		if (numRays > 0) {				\
									rays	-=	numRays;		\
									traceTransmission(numRays,rays,lookup,TRUE);									\
									for (int i=numRays;i>0;i--,rays++)	*rays->res	=	rays->t < C_INFINITY;		\
									expandFloat(res);			\
								}

#else

#define	TRANSMISSIONEXPR_PRE
#define	TRANSMISSIONEXPR
#define	TRANSMISSIONEXPR_UPDATE
#define	TRANSMISSIONEXPR_POST
#define	VISIBILITYEXPR_POST

#endif

DEFSHORTFUNC(Visibility			,"visibility"			,"f=pp!"		,TRANSMISSIONEXPR_PRE,TRANSMISSIONEXPR,TRANSMISSIONEXPR_UPDATE(1),VISIBILITYEXPR_POST,PARAMETER_RAYTRACE | PARAMETER_DERIVATIVE | PARAMETER_DU | PARAMETER_DV)
DEFSHORTFUNC(Transmission		,"transmission"			,"c=pp!"		,TRANSMISSIONEXPR_PRE,TRANSMISSIONEXPR,TRANSMISSIONEXPR_UPDATE(3),TRANSMISSIONEXPR_POST,PARAMETER_RAYTRACE | PARAMETER_DERIVATIVE | PARAMETER_DU | PARAMETER_DV)





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
									traceReflection(numRays,rays,lookup,FALSE);						\
									for (int i=numRays;i>0;i--,rays++)	movvv(rays->res,rays->C);	\
									expandVector(res);												\
								}

// Just compute the nearest intersection
#define	TRACE2EXPR_POST			if (numRays > 0) {													\
									rays	-=	numRays;											\
									traceReflection(numRays,rays,lookup,TRUE);						\
									for (int i=numRays;i>0;i--,rays++)	*rays->res	=	rays->t;	\
									expandFloat(res);												\
								}

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
#define	IDEXPR_PRE(__occlusion)	CTexture3dLookup	*lookup;																		\
								FUN4EXPR_PRE;																						\
								osLock(CRenderer::shaderMutex);																		\
								if ((lookup = (CTexture3dLookup *) parameterlist) == NULL) {										\
									int			numArguments;																		\
									argumentcount(numArguments);																	\
									TEXTURE3DPARAMETERS(4,(numArguments-4) >> 1);													\
									const float			*from,*to;																	\
									findCoordinateSystem(lookup->coordsys,from,to);													\
									lookup->numSamples	=	(int) *op3;																\
									lookup->occlusion	=	__occlusion;															\
									lookup->texture		=	CRenderer::getCache(lookup->handle,lookup->filemode,from,to);			\
									lookup->texture->resolve(lookup->numChannels,channelNames,lookup->entry,lookup->size);			\
								}																									\
								osUnlock(CRenderer::shaderMutex);																	\
								float		*dPdu	=	(float *) ralloc(numVertices*6*sizeof(float),threadMemory);					\
								float		*dPdv	=	dPdu + numVertices*3;														\
								duVector(dPdu,op1);																					\
								dvVector(dPdv,op1);																					\
								const float	*du		=	varying[VARIABLE_DU];														\
								const float	*dv		=	varying[VARIABLE_DV];														\
								CTexture3d	*cache	=	lookup->texture;															\
								assert(cache->dataSize == 7);																		\
																																	\
								float	C[7];																						\
								float	**channelValues = (float **) ralloc(lookup->numChannels*sizeof(const float *),threadMemory);	\
																																	\
								int channel;																						\
								for (channel=0;channel<lookup->numChannels;channel++) {												\
									operand(lookup->index[channel],channelValues[channel],float *);									\
								} 


#define	IDEXPR(__occlusion)		mulvf(dPdu,*du);																					\
								mulvf(dPdv,*dv);																					\
								cache->lookup(C,op1,dPdu,dPdv,op2,this,lookup);														\
								texture3Dunpack(C,lookup->numChannels,channelValues,lookup->entry,lookup->size);					\
								if (__occlusion)	*res	=	C[3];																\
								else				movvv(res,C);


#define	IDEXPR_UPDATE(__n)		FUN4EXPR_UPDATE(__n,3,3,0)																			\
								dPdu	+=	3;																						\
								dPdv	+=	3;																						\
								du++;	dv++;																						\
								for (channel=0;channel<lookup->numChannels;channel++) {												\
									channelValues[channel]	+=	lookup->size[channel];												\
								}

#define	IDEXPR_POST(__occlusion)								\
								if (__occlusion)	{			\
									expandFloat(res);			\
								} else {						\
									expandVector(res);			\
								}
#else
#define	IDEXPR_PRE
#define	IDEXPR
#define	IDEXPR_UPDATE
#define	IDEXPR_POST(__occlusion)
#endif

DEFSHORTFUNC(Occlusion			,"occlusion"		,"f=pnf!"	,IDEXPR_PRE(TRUE),IDEXPR(TRUE),IDEXPR_UPDATE(1),IDEXPR_POST(TRUE),PARAMETER_RAYTRACE | PARAMETER_DERIVATIVE)
DEFSHORTFUNC(Indirectdiffuse	,"indirectdiffuse"	,"c=pnf!"	,IDEXPR_PRE(FALSE),IDEXPR(FALSE),IDEXPR_UPDATE(3),IDEXPR_POST(TRUE),PARAMETER_RAYTRACE | PARAMETER_DERIVATIVE)

#undef	IDEXPR_PRE
#undef	IDEXPR
#undef	IDEXPR_UPDATE
#undef	IDEXPR_POST



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// photonmap	"c=spn!"
#ifndef INIT_SHADING
#define	PHOTONMAPEXPR_PRE		CTexture3dLookup	*lookup;													\
								osLock(CRenderer::shaderMutex);													\
								if ((lookup = (CTexture3dLookup *) parameterlist) == NULL) {					\
									int			numArguments;													\
									const char	**op1;															\
									argumentcount(numArguments);												\
									TEXTURE3DPARAMETERS(4,(numArguments-4) >> 1);								\
									operand(1,op1,const char **);												\
									lookup->map			=	CRenderer::getPhotonMap(*op1);						\
								}																				\
								osUnlock(CRenderer::shaderMutex);												\
								float				*res;														\
								const float			*op2,*op3;													\
								operand(0,res,float *);															\
								operand(2,op2,const float *);													\
								operand(3,op3,const float *);													\
								CPhotonMap	*map	=	lookup->map;


#define	PHOTONMAPEXPR			map->lookup(res,op2,op3,lookup->numLookupSamples);

#define	PHOTONMAPEXPR_UPDATE	res	+=	3;																		\
								op2	+=	3;																		\
								op3	+=	3;

#define	PHOTONMAPEXPR_POST		expandVector(res);

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
#define	PHOTONMAP2EXPR_PRE		CTexture3dLookup	*lookup;													\
								osLock(CRenderer::shaderMutex);													\
								if ((lookup = (CTexture3dLookup *) parameterlist) == NULL) {					\
									int			numArguments;													\
									const char	**op1;															\
									argumentcount(numArguments);												\
									TEXTURE3DPARAMETERS(3,(numArguments-3) >> 1);								\
									operand(1,op1,const char **);												\
									lookup->map			=	CRenderer::getPhotonMap(*op1);						\
								}																				\
								osUnlock(CRenderer::shaderMutex);												\
								float				*res;														\
								const float			*op2;														\
								operand(0,res,float *);															\
								operand(2,op2,const float *);													\
								CPhotonMap	*map	=	lookup->map;

#define	PHOTONMAP2EXPR			map->lookup(res,op2,lookup->numLookupSamples);

#define	PHOTONMAP2EXPR_UPDATE	res	+=	3;																		\
								op2	+=	3;

#define	PHOTONMAP2EXPR_POST		expandVector(res);

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
								lookup->sampleBase		=	1.0f;													\
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
										} else if (strcmp(*param,"samplebase")  == 0) {								\
											lookup->sampleBase	=	valf[0];										\
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
									lookup->coneAngle				=	min(tanf(*sampleCone),1.0f);				\
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
								float	*dPdu	=	(float *) ralloc(numVertices*6*sizeof(float),threadMemory);		\
								float	*dPdv	=	dPdu + numVertices*3;											\
								duVector(dPdu,P);																	\
								dvVector(dPdv,P);																	\
								const float	*du	=	varying[VARIABLE_DU];											\
								const float	*dv	=	varying[VARIABLE_DV];											\
																													\
								CGatherRay		*rays;																\
								lastGather->rays					=	(CRay **) ralloc(numVertices*sizeof(CGatherRay *),threadMemory);		\
								lastGather->raysStorage				=	lastGather->rays;							\
								lastGather->raysBase	=	rays	=	(CGatherRay *) ralloc(numVertices*sizeof(CGatherRay),threadMemory);
								


#define GATHERHEADEREXPR		movvv(rays->P,P);																	\
								mulvf(rays->dPdu,dPdu,*du);															\
								mulvf(rays->dPdv,dPdv,*dv);															\
								movvv(rays->gatherDir,N);															\
								rays->da	=	lookup->da;															\
								rays->db	=	(lengthv(rays->dPdu) + lengthv(rays->dPdv))*0.5f;

#define GATHERHEADEREXPR_UPDATE	P		+=	3;																		\
								N		+=	3;																		\
								dPdu	+=	3;																		\
								dPdv	+=	3;																		\
								du++; dv++;																			\
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

