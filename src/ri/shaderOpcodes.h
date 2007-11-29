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
//  File				:	shaderOpcodes.h
//  Classes				:	-
//  Description			:	Shading language specific opcodes.
//
////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// illumination <P> <begin> <end>  [ <category> ]
#define ILLUMINATION1RUNLIGHT_PRE	char			**lightCat;												\
									operand(3,lightCat,char **);

#define ILLUMINATION_RUNLIGHTS		runLights(P,N,costheta);

#define ILLUMINATION_RUNCATLIGHTS	runCategoryLights(P,N,costheta,lightCat);

#define	ILLUMINATION1EXPR_PRE(lightCatPreExpr,runlightsExpr)												\
									const float		*P,*N,*Lsave,*Clsave;									\
									float			*L,*Cl;													\
									float			*costheta	=	(float *) ralloc(numVertices*sizeof(float)*4,threadMemory);	\
									float			*Ntmp		=	costheta + numVertices;					\
									lightCatPreExpr;														\
									const int beginIndex		=	argument(1);							\
									const int endIndex			=	argument(2);							\
									beginConditional();														\
									lastConditional->forStart		=	beginIndex;							\
									lastConditional->forContinue	=	endIndex;							\
									lastConditional->forEnd			=	endIndex;							\
									lastConditional->forExecCount	=	1;									\
									operand(0,P,const float *);												\
									N	=	Ntmp;															\
									for (int i=0;i<numVertices;++i) {										\
										initv(Ntmp+i*3,0,0,1);												\
										costheta[i]	=	-1;													\
									}																		\
									runlightsExpr;															\
									if ((*currentLight=*lights) != NULL) {									\
										enterLightingConditional();											\
										/* copy the light's variables in */									\
										L		=	varying[VARIABLE_L];									\
										Cl		=	varying[VARIABLE_CL];									\
										Lsave	= 	(*currentLight)->savedState[0];							\
										Clsave	= 	(*currentLight)->savedState[1];							\
										for (int i=0;i<numVertices;++i,++tags) {							\
											if (*tags == 0) {												\
												movvv(L,Lsave);												\
												movvv(Cl,Clsave);											\
											}																\
											L		+=	3;													\
											Cl		+=	3;													\
											Lsave	+=	3;													\
											Clsave	+=	3;													\
										}																	\
									}
					

#define	ILLUMINATION1EXPR_POST		if ((numActive == 0) || (*currentLight == NULL))						\
										jmp(endIndex);
										


DEFOPCODE(Illumination1	,"illuminance"	,3, ILLUMINATION1EXPR_PRE(NULL_EXPR,ILLUMINATION_RUNLIGHTS), NULL_EXPR, NULL_EXPR, ILLUMINATION1EXPR_POST,0)

DEFOPCODE(IlluminationCat1 ,"illuminance",4, ILLUMINATION1EXPR_PRE(ILLUMINATION1RUNLIGHT_PRE,ILLUMINATION_RUNCATLIGHTS), NULL_EXPR, NULL_EXPR, ILLUMINATION1EXPR_POST,0)


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// illumination <P> <axis> <angle> <begin> <end>  [ <category> ]
#define ILLUMINATION2RUNLIGHT_PRE	char			**lightCat;												\
									operand(5,lightCat,char **);

#define	ILLUMINATION2EXPR_PRE(lightCatPreExpr,runlightsExpr)												\
									const float		*angle;													\
									const float		*P,*N,*Lsave,*Clsave;									\
									float			*L,*Cl;													\
									float			*costheta	=	(float *) ralloc(numVertices*sizeof(float),threadMemory);	\
									lightCatPreExpr;														\
									const int beginIndex		=	argument(3);							\
									const int endIndex			=	argument(4);							\
									beginConditional();														\
									lastConditional->forStart		=	beginIndex;							\
									lastConditional->forContinue	=	endIndex;							\
									lastConditional->forEnd			=	endIndex;							\
									lastConditional->forExecCount	=	1;									\
									operand(0,P,const float *);												\
									operand(1,N,const float *);												\
									operand(2,angle,const float *);											\
									for (int i=0;i<numVertices;++i) costheta[i]	=	(float) cos(angle[i]);	\
									runlightsExpr;															\
									if ((*currentLight=*lights) != NULL) {									\
										enterLightingConditional();											\
										/* copy the light's variables in */									\
										L		=	varying[VARIABLE_L];									\
										Cl		=	varying[VARIABLE_CL];									\
										Lsave	= 	(*currentLight)->savedState[0];							\
										Clsave	= 	(*currentLight)->savedState[1];							\
										for (int i=0;i<numVertices;++i,++tags) {							\
											if (*tags == 0) {												\
												movvv(L,Lsave);												\
												movvv(Cl,Clsave);											\
											}																\
											L		+=	3;													\
											Cl		+=	3;													\
											Lsave	+=	3;													\
											Clsave	+=	3;													\
										}																	\
									}
					

#define	ILLUMINATION2EXPR_POST		if ((numActive == 0) || (*currentLight == NULL))						\
										jmp(endIndex);
										


DEFOPCODE(Illumination2	,"illuminance"	,5, ILLUMINATION2EXPR_PRE(NULL_EXPR,ILLUMINATION_RUNLIGHTS), NULL_EXPR, NULL_EXPR, ILLUMINATION2EXPR_POST,0)

DEFOPCODE(IlluminationCat2	,"illuminance"	,6, ILLUMINATION2EXPR_PRE(ILLUMINATION2RUNLIGHT_PRE,ILLUMINATION_RUNLIGHTS), NULL_EXPR, NULL_EXPR, ILLUMINATION2EXPR_POST,0)


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// endillumination
#define	ENDILLUMINATIONEXPR_PRE		const float		*Lsave,*Clsave;											\
									float			*L,*Cl;													\
									lastConditional->forExecCount++;										\
									if (*currentLight != NULL) {											\
										exitLightingConditional();											\
																											\
										if ((*currentLight=(*currentLight)->next) != NULL) {				\
											enterLightingConditional();										\
											/* copy the light's variables in */								\
											L		=	varying[VARIABLE_L];								\
											Cl		=	varying[VARIABLE_CL];								\
											Lsave	= 	(*currentLight)->savedState[0];						\
											Clsave	= 	(*currentLight)->savedState[1];						\
											for (int i=0;i<numVertices;++i,++tags) {						\
												if (*tags == 0) {											\
													movvv(L,Lsave);											\
													movvv(Cl,Clsave);										\
												}															\
												L		+=	3;												\
												Cl		+=	3;												\
												Lsave	+=	3;												\
												Clsave	+=	3;												\
											}																\
										}																	\
									}																		\
									if ((numActive > 0) && (*currentLight != NULL)) {						\
										jmp(lastConditional->forStart);										\
									}																		\
									endConditional();


DEFOPCODE(EndIlluminationExpr	,"endilluminance"	,0, ENDILLUMINATIONEXPR_PRE, NULL_EXPR, NULL_EXPR, NULL_EXPR,0)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//		illuminate <P> <end>
//		illuminate <P> <N> <theta> <end>
//		endilluminate
//
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifdef INIT_SHADING
#define	ILLUMINATE1EXPR_PRE
#else
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// illuminate <P> <end>
// always execute (no shadow checking)
#define	ILLUMINATE1EXPR_PRE			const float	*Pl;													\
																										\
									operand(0,Pl,const float *);										\
																										\
									if (CRenderer::hiderFlags & HIDER_ILLUMINATIONHOOK) {				\
										illuminateBegin(Pl,NULL,NULL);									\
									} else {															\
										float		*Ps			=	varying[VARIABLE_PS];				\
										float		*L			=	varying[VARIABLE_L];				\
										const float	*Ns			=	currentShadingState->Ns;			\
										const float	*costheta	=	currentShadingState->costheta;		\
																										\
										for (int i=numVertices;i>0;--i,++tags) {						\
											if (*tags) {												\
												(*tags)++;												\
											} else {													\
												subvv(L,Ps,Pl);											\
																										\
												if (dotvv(Ns,L) > -(*costheta)*lengthv(L)) {			\
													(*tags)++;											\
													--numActive;										\
													++numPassive;										\
												}														\
											}															\
																										\
											Pl			+=	3;											\
											L			+=	3;											\
											Ps			+=	3;											\
											Ns			+=	3;											\
											++costheta;													\
										}																\
																										\
										if (numActive == 0) {											\
											jmp(argument(1));											\
										}																\
									}

#endif


DEFOPCODE(Illuminate1	,"illuminate"	,2, ILLUMINATE1EXPR_PRE, NULL_EXPR, NULL_EXPR, NULL_EXPR,PARAMETER_NONAMBIENT)

#undef ILLUMINATE1EXPR_PRE

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// illuminate <P> <N> <theta> <end>
#ifdef INIT_SHADING
#define	ILLUMINATE3EXPR_PRE
#else
#define	ILLUMINATE3EXPR_PRE			const float	*Pf,*Nf,*thetaf;										\
																										\
									operand(0,Pf,const float *);										\
									operand(1,Nf,const float *);										\
									operand(2,thetaf,const float *);									\
																										\
									if (CRenderer::hiderFlags & HIDER_ILLUMINATIONHOOK) {				\
										illuminateBegin(Pf,Nf,thetaf);									\
									} else {															\
										float		*Ps			=	varying[VARIABLE_PS];				\
										float		*L			=	varying[VARIABLE_L];				\
										const float	*Ns			=	currentShadingState->Ns;			\
										const float	*costheta	=	currentShadingState->costheta;		\
																										\
										for (int i=numVertices;i>0;--i,++tags) {						\
											if (*tags) {												\
												(*tags)++;												\
											} else {													\
												subvv(L,Ps,Pf);											\
												const float	Lm		=	lengthv(L);						\
												if ((dotvv(Nf,L) < cos(*thetaf)*Lm) || (dotvv(Ns,L) > -(*costheta)*Lm)) {	\
													(*tags)++;											\
													--numActive;										\
													++numPassive;										\
												}														\
											}															\
																										\
											Pf			+=	3;											\
											Nf			+=	3;											\
											++thetaf;													\
											L			+=	3;											\
											Ps			+=	3;											\
											Ns			+=	3;											\
											++costheta;													\
										}																\
																										\
																										\
										if (numActive == 0) {											\
											jmp(argument(3));											\
										}																\
									}

#endif

DEFOPCODE(Illuminate3	,"illuminate"	,4, ILLUMINATE3EXPR_PRE, NULL_EXPR, NULL_EXPR, NULL_EXPR,PARAMETER_NONAMBIENT)

#undef ILLUMINATE3EXPR_PRE

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// illuminateend
// Create a new shaded light
// Save L,Cl,Ol 
#ifdef INIT_SHADING
#define	ILLUMINATEEND_PRE
#else
#define	ILLUMINATEEND_PRE			if (CRenderer::hiderFlags & HIDER_ILLUMINATIONHOOK) {		\
										illuminateEnd();										\
									} else {													\
										const float		*L =	varying[VARIABLE_L];			\
										float 			*Lsave;									\
																								\
										saveLighting(Lsave);									\
										for (int i=0;i<numVertices;++i,++tags) {				\
											if (*tags) {										\
												(*tags)--;										\
												if (*tags == 0) {								\
													++numActive;								\
													--numPassive;								\
												}												\
											} else {											\
												mulvf(Lsave,L,-1);								\
											}													\
											L		+=	3;										\
											Lsave	+=	3;										\
										}														\
									}

#endif

DEFOPCODE(EndIlluminate	,"endilluminate"	,0, ILLUMINATEEND_PRE, NULL_EXPR, NULL_EXPR, NULL_EXPR,PARAMETER_NONAMBIENT)

#undef ILLUMINATEEND_PRE





///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//		solar <end>
//		solar <N> <theta> <end>
//		endsolar
//
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// solar <end>
// always execute (no shadow checking)
// FIXME: Shadows are not correct
#ifdef INIT_SHADING
#define SOLAR1EXPR_PRE
#else
#define	SOLAR1EXPR_PRE				if (CRenderer::hiderFlags & HIDER_ILLUMINATIONHOOK) {		\
										solarBegin(NULL,NULL);									\
									} else {													\
										const float	*Ps		=	varying[VARIABLE_PS];			\
										float		*L		=	varying[VARIABLE_L];			\
																								\
										for (int i=numVertices;i>0;--i,++tags) {				\
											if (*tags) {										\
												(*tags)++;										\
											} else {											\
												movvv(L,Ps);									\
											}													\
																								\
											L			+=	3;									\
											Ps			+=	3;									\
										}														\
									}

#endif

DEFOPCODE(Solar1	,"solar"	,1, SOLAR1EXPR_PRE, NULL_EXPR, NULL_EXPR, NULL_EXPR,PARAMETER_NONAMBIENT)

#undef SOLAR1EXPR_PRE

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// solar <N> <theta> <end>
#ifdef INIT_SHADING
#define	SOLAR2EXPR_PRE
#else
#define	SOLAR2EXPR_PRE				const float	*Nf,*thetaf;									\
																								\
									operand(0,Nf,const float *);								\
									operand(1,thetaf,const float *);							\
																								\
									if (CRenderer::hiderFlags & HIDER_ILLUMINATIONHOOK) {		\
										solarBegin(Nf,thetaf);									\
									} else {													\
										vector		R;											\
										float		worldRadius;								\
										float		*L			=	varying[VARIABLE_L];		\
										const float	*Ns			=	currentShadingState->Ns;	\
										const float	*costheta	=	currentShadingState->costheta;		\
																								\
										subvv(R,CRenderer::worldBmax,CRenderer::worldBmin);		\
										worldRadius				=	dotvv(R,R);					\
																								\
										for (int i=numVertices;i>0;--i,++tags) {				\
											if (*tags) {										\
												(*tags)++;										\
											} else {											\
												movvv(L,Nf);									\
												mulvf(L,worldRadius);							\
												if (dotvv(Ns,L) > -(*costheta)*lengthv(L)) {	\
													(*tags)++;									\
													--numActive;								\
													++numPassive;								\
												}												\
											}													\
											Nf			+=	3;									\
											L			+=	3;									\
											Ns			+=	3;									\
											++costheta;											\
										}														\
									}

#endif

#define	SOLAR2EXPR_POST				if (numActive == 0)	jmp(argument(2));

DEFOPCODE(Solar2	,"solar"	,3, SOLAR2EXPR_PRE, NULL_EXPR, NULL_EXPR, SOLAR2EXPR_POST,PARAMETER_NONAMBIENT)

#undef SOLAR2EXPR_PRE

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// solarend
// Create a new shaded light
// Save L,Cl,Ol 
#ifdef INIT_SHADING
#define SOLAREND_PRE
#else
#define	SOLAREND_PRE				if (CRenderer::hiderFlags & HIDER_ILLUMINATIONHOOK) {	\
										solarEnd();											\
									} else {												\
										const float		*L	=	varying[VARIABLE_L];		\
										float 			*Lsave;								\
																							\
										saveLighting(Lsave);								\
										for (int i=0;i<numVertices;++i,++tags) {			\
											if (*tags) {									\
												(*tags)--;									\
												if (*tags == 0) {							\
													++numActive;							\
													--numPassive;							\
												}											\
											} else {										\
												mulvf(Lsave,L,-1);							\
												normalizev(Lsave);							\
											}												\
											L		+=	3;									\
											Lsave	+=	3;									\
										}													\
									}

#endif

DEFOPCODE(EndSolar	,"endsolar"	,0, SOLAREND_PRE, NULL_EXPR, NULL_EXPR, NULL_EXPR,PARAMETER_NONAMBIENT)

#undef SOLAREND_PRE










#define	PFROMEXPR_PRE		float				*res;								\
							const float			*op;								\
							const char			**sys;								\
							const float			*from,*to;							\
							ECoordinateSystem	cSystem;							\
							operand(0,res,float *);									\
							operand(1,sys,const char **);							\
							operand(2,op,const float *);							\
							findCoordinateSystem(*sys,from,to,cSystem);

#define	PFROMEXPR			mulmp(res,from,op);

#define	PFROMEXPR_UPDATE	res	+=	3;												\
							op	+=	3;

#define	PFROMEXPR_POST

#define	CFROMEXPR			convertColorFrom(res,op,cSystem);

#define	CFROMEXPR_UPDATE	res	+=	3;												\
							op	+=	3;

#define	CFROMEXPR_POST

#define	MFROMEXPR			mulmm(res,from,op);

#define	MFROMEXPR_UPDATE	res	+=	16;												\
							op	+=	16;

#define	MFROMEXPR_POST

#define	VFROMEXPR			mulmv(res,from,op);

#define	VFROMEXPR_UPDATE	res	+=	3;												\
							op	+=	3;

#define	VFROMEXPR_POST


DEFOPCODE(CFrom		,"cfrom"	,3, PFROMEXPR_PRE,CFROMEXPR,CFROMEXPR_UPDATE,CFROMEXPR_POST,0)
DEFOPCODE(VFrom		,"vfrom"	,3, PFROMEXPR_PRE,VFROMEXPR,VFROMEXPR_UPDATE,VFROMEXPR_POST,0)
DEFOPCODE(PFrom		,"pfrom"	,3, PFROMEXPR_PRE,PFROMEXPR,PFROMEXPR_UPDATE,PFROMEXPR_POST,0)
DEFOPCODE(MFrom		,"mfrom"	,3, PFROMEXPR_PRE,MFROMEXPR,MFROMEXPR_UPDATE,MFROMEXPR_POST,0)

#include "giOpcodes.h"

