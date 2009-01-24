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
//  File				:	shaderFunctions.h
//  Classes				:	-
//  Description			:	Shader language specific buint in functions
//
////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// debug	"o=v"
#define	DEBUGVEXPR		debugFunction((float *) res);


DEFFUNC(DebugFloat		,"debug"		,"o=f", FUN1EXPR_PRE, DEBUGVEXPR, FUN1EXPR_UPDATE(1), NULL_EXPR, 0)
DEFLINKFUNC(DebugP		,"debug"		,"o=p",	0)
DEFLINKFUNC(DebugC		,"debug"		,"o=c",	0)
DEFLINKFUNC(DebugN		,"debug"		,"o=n",	0)
DEFFUNC(DebugVector		,"debug"		,"o=v", FUN1EXPR_PRE, DEBUGVEXPR, FUN1EXPR_UPDATE(3), NULL_EXPR, 0)



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// faceforward "v=vv"
#define	FACEFORWARDEXPR_PRE		const float	*Ng	=	varying[VARIABLE_NG];			\
								FUN3EXPR_PRE
								
#define	FACEFORWARDEXPR			if (dotvv(op1,Ng) > 0) {							\
									if (dotvv(op2,Ng) > 0)							\
										mulvf(res,op1,-1);							\
									else											\
										movvv(res,op1);								\
								} else {											\
									if (dotvv(op2,Ng) > 0)							\
										movvv(res,op1);								\
									else											\
										mulvf(res,op1,-1);							\
								}


#define	FACEFORWARDEXPR_UPDATE	FUN3EXPR_UPDATE(3,3,3);								\
								Ng		+=	3;

DEFFUNC(FaceForward		,"faceforward"			,"v=vv"	,FACEFORWARDEXPR_PRE,FACEFORWARDEXPR,FACEFORWARDEXPR_UPDATE,NULL_EXPR,PARAMETER_NG)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// faceforward "v=vvv"
#define	FACEFORWARD2EXPR		if (dotvv(op1,op3) > 0) {							\
									if (dotvv(op2,op3) > 0)							\
										mulvf(res,op1,-1);							\
									else											\
										movvv(res,op1);								\
								} else {											\
									if (dotvv(op2,op3) > 0)							\
										movvv(res,op1);								\
									else											\
										mulvf(res,op1,-1);							\
								}


DEFFUNC(FaceForward3		,"faceforward"		,"v=vvv",FUN4EXPR_PRE,FACEFORWARD2EXPR,FUN4EXPR_UPDATE(3,3,3,3),NULL_EXPR,0)




// The following macros are used to evaluate u and v derivatives using central differencing




		


									
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// du "f=f"
#ifndef INIT_SHADING
#define	DUFEXPR_PRE				FUN2EXPR_PRE																		\
								duFloat(res,op);
#else
#undef	DUFEXPR_PRE
#define	DUFEXPR_PRE
#endif

DEFFUNC(Duf		,"Du"			,"f=f"	,DUFEXPR_PRE,NULL_EXPR,NULL_EXPR,NULL_EXPR,PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_DU | PARAMETER_DV | PARAMETER_DERIVATIVE)

#undef	DUVEXPR_PRE
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// du "v=v"
#ifndef INIT_SHADING
#define	DUVEXPR_PRE				FUN2EXPR_PRE																		\
								duVector(res,op);

#else
#undef	DUVEXPR_PRE
#define	DUVEXPR_PRE
#endif

DEFLINKFUNC(Duv1	,"Du"		,"v=c",	PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_DU | PARAMETER_DV | PARAMETER_DERIVATIVE)
DEFLINKFUNC(Duv2	,"Du"		,"v=p",	PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_DU | PARAMETER_DV | PARAMETER_DERIVATIVE)
DEFLINKFUNC(Duv3	,"Du"		,"v=n",	PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_DU | PARAMETER_DV | PARAMETER_DERIVATIVE)
DEFFUNC(Duv			,"Du"		,"v=v"	,DUVEXPR_PRE,NULL_EXPR,NULL_EXPR,NULL_EXPR,PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_DU | PARAMETER_DV | PARAMETER_DERIVATIVE)

#undef	DUVEXPR_PRE


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// dv "f=f"
#ifndef INIT_SHADING
#define	DVFEXPR_PRE				FUN2EXPR_PRE																	\
								dvFloat(res,op);
#else
#undef	DVFEXPR_PRE
#define	DVFEXPR_PRE
#endif

DEFFUNC(Dvf		,"Dv"			,"f=f"	,DVFEXPR_PRE,NULL_EXPR,NULL_EXPR,NULL_EXPR,PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_DU | PARAMETER_DV | PARAMETER_DERIVATIVE)

#undef	DVFEXPR_PRE

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// dv "v=v"
#ifndef INIT_SHADING
#define	DVVEXPR_PRE				FUN2EXPR_PRE																	\
								dvVector(res,op);
#else
#undef	DVVEXPR_PRE
#define	DVVEXPR_PRE	
#endif


DEFLINKFUNC(Dvv1	,"Dv"		,"v=c",	PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_DU | PARAMETER_DV | PARAMETER_DERIVATIVE)
DEFLINKFUNC(Dvv2	,"Dv"		,"v=p",	PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_DU | PARAMETER_DV | PARAMETER_DERIVATIVE)
DEFLINKFUNC(Dvv3	,"Dv"		,"v=n",	PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_DU | PARAMETER_DV | PARAMETER_DERIVATIVE)
DEFFUNC(Dvv			,"Dv"		,"v=v"	,DVVEXPR_PRE,NULL_EXPR,NULL_EXPR,NULL_EXPR,PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_DU | PARAMETER_DV | PARAMETER_DERIVATIVE)

#undef	DVVEXPR_PRE

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// deriv "f=ff"
#ifndef INIT_SHADING
#define	DERIVFEXPR_PRE			FUN3EXPR_PRE																\
								float	*duTop		=	(float *) ralloc(numVertices*sizeof(float)*4,threadMemory);		\
								float	*duBottom	=	duTop + numVertices;								\
								float	*dvTop		=	duBottom + numVertices;								\
								float	*dvBottom	=	dvTop + numVertices;								\
								duFloat(duTop,		op1);													\
								duFloat(duBottom,	op2);													\
								dvFloat(dvTop,		op1);													\
								dvFloat(dvBottom,	op2);

#define	DERIVFEXPR				if (duBottom[0] != 0) {														\
									res[0]	=	duTop[0] / duBottom[0];										\
								} else {																	\
									res[0]	=	0;															\
								}																			\
																											\
								if (dvBottom[0] != 0) {														\
									res[0]	+=	dvTop[0] / dvBottom[0];										\
								}



#define	DERIVFEXPR_UPDATE		++res;																		\
								++duTop;																	\
								++duBottom;																	\
								++dvTop;																	\
								++dvBottom;

#else

#define	DERIVFEXPR_PRE
#define	DERIVFEXPR
#define	DERIVFEXPR_UPDATE

#endif

DEFFUNC(Derivf		,"Deriv"			,"f=ff"	,DERIVFEXPR_PRE,DERIVFEXPR,DERIVFEXPR_UPDATE,NULL_EXPR,PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_DU | PARAMETER_DV | PARAMETER_DERIVATIVE)

#undef	DERIVFEXPR_PRE
#undef	DERIVFEXPR
#undef	DERIVFEXPR_UPDATE

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// deriv "v=vf"
#ifndef INIT_SHADING
#define	DERIVVEXPR_PRE			FUN3EXPR_PRE																\
								float	*duTop		=	(float *) ralloc(numVertices*sizeof(float)*8,threadMemory);		\
								float	*duBottom	=	duTop + numVertices*3;								\
								float	*dvTop		=	duBottom + numVertices;								\
								float	*dvBottom	=	dvTop + numVertices*3;								\
								duVector(duTop,		op1);													\
								duFloat(duBottom,	op2);													\
								dvVector(dvTop,		op1);													\
								dvFloat(dvBottom,	op2);

#define	DERIVVEXPR				if (duBottom[0] != 0) {														\
									res[0]	=	(float) ((double)duTop[0] / (double)duBottom[0]);			\
									res[1]	=	(float) ((double)duTop[1] / (double)duBottom[0]);			\
									res[2]	=	(float) ((double)duTop[2] / (double)duBottom[0]);			\
								} else {																	\
									res[0]	=	0;															\
									res[1]	=	0;															\
									res[2]	=	0;															\
								}																			\
																											\
								if (dvBottom[0] != 0) {														\
									res[0]	+=	(float) ((double)dvTop[0] / (double)dvBottom[0]);			\
									res[1]	+=	(float) ((double)dvTop[1] / (double)dvBottom[0]);			\
									res[2]	+=	(float) ((double)dvTop[2] / (double)dvBottom[0]);			\
								}


#define	DERIVVEXPR_UPDATE		res			+=	3;															\
								duTop		+=	3;															\
								dvTop		+=	3;															\
								++duBottom;																	\
								++dvBottom;

#else
#define	DERIVVEXPR_PRE
#define	DERIVVEXPR
#define	DERIVVEXPR_UPDATE
#endif

DEFLINKFUNC(Derivv1		,"Deriv"		,"v=cf",	PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_DU | PARAMETER_DV | PARAMETER_DERIVATIVE)
DEFLINKFUNC(Derivv2		,"Deriv"		,"v=pf",	PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_DU | PARAMETER_DV | PARAMETER_DERIVATIVE)
DEFLINKFUNC(Derivv3		,"Deriv"		,"v=nf",	PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_DU | PARAMETER_DV | PARAMETER_DERIVATIVE)
DEFFUNC(Derivv			,"Deriv"		,"v=vf"	,	DERIVVEXPR_PRE,DERIVVEXPR,DERIVVEXPR_UPDATE,NULL_EXPR,PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_DU | PARAMETER_DV | PARAMETER_DERIVATIVE)

#undef	DERIVVEXPR_PRE
#undef	DERIVVEXPR
#undef	DERIVVEXPR_UPDATE

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// area "f=p"
#ifndef INIT_SHADING
#define	AREAEXPR_PRE			FUN2EXPR_PRE																\
								float	*du		=	varying[VARIABLE_DU];									\
								float	*dv		=	varying[VARIABLE_DV];									\
								float	*dPdu	=	(float *) ralloc(numVertices*6*sizeof(float),threadMemory);			\
								float	*dPdv	=	dPdu + numVertices*3;									\
								vector	tmp;																\
								duVector(dPdu,op);															\
								dvVector(dPdv,op);
								

#define	AREAEXPR				mulvf(dPdu,du[0]);															\
								mulvf(dPdv,dv[0]);															\
								crossvv(tmp,dPdu,dPdv);														\
								*res	=	lengthv(tmp);													\
								assert(*res >= 0);

#define	AREAEXPR_UPDATE			++res;																		\
								dPdu	+=	3;																\
								dPdv	+=	3;																\
								++du;																		\
								++dv;
#else
#define	AREAEXPR_PRE
#define	AREAEXPR
#define	AREAEXPR_UPDATE
#endif

// Totally ignore the measure argument for area
DEFFUNC(Area		,"area"		,"f=p",		AREAEXPR_PRE,AREAEXPR,AREAEXPR_UPDATE,NULL_EXPR,PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_DU | PARAMETER_DV | PARAMETER_DERIVATIVE)

#undef	AREAEXPR_PRE
#undef	AREAEXPR
#undef	AREAEXPR_UPDATE




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// area "f=pS"
#ifndef INIT_SHADING
#define	AREAEXPR_PRE			FUN2EXPR_PRE																\
								float		*du;															\
								float		*dv;															\
								float		*dPdu;															\
								float		*dPdv;															\
								vector		tmp;															\
								const char	**measure;														\
								int			dicingMeasure;													\
								operand(2,measure,const char **);											\
								if (strcmp(*measure,"shading") == 0) {										\
									du		=	varying[VARIABLE_DU];										\
									dv		=	varying[VARIABLE_DV];										\
									dPdu	=	(float *) ralloc(numVertices*6*sizeof(float),threadMemory);	\
									dPdv	=	dPdu + numVertices*3;										\
									duVector(dPdu,op);														\
									dvVector(dPdv,op);														\
									dicingMeasure	=	FALSE;												\
								} else if (strcmp(*measure,"dicing") == 0) {								\
									du				=	rayDiff(op);										\
									dicingMeasure	=	TRUE;												\
								} else {																	\
									error(CODE_BADTOKEN,"Unrecognized area measure: \"%s\". Assuming \"dicing\"\n",*measure);					\
									du				=	rayDiff(op);										\
									dicingMeasure	=	TRUE;												\
								}
								

#define	AREAEXPR				if (dicingMeasure) {														\
									assert(*du >= 0);														\
									*res	=	(*du)*(*du);												\
								} else {																	\
									mulvf(dPdu,du[0]);														\
									mulvf(dPdv,dv[0]);														\
									crossvv(tmp,dPdu,dPdv);													\
									*res	=	lengthv(tmp);												\
								}

#define	AREAEXPR_UPDATE			++res;																		\
								++du;																		\
								if (dicingMeasure == FALSE) {												\
									dPdu	+=	3;															\
									dPdv	+=	3;															\
									++dv;																	\
								}
#else
#define	AREAEXPR_PRE
#define	AREAEXPR
#define	AREAEXPR_UPDATE
#endif

// Totally ignore the measure argument for area
DEFFUNC(AreaS	,"area"		,"f=pS",	AREAEXPR_PRE,AREAEXPR,AREAEXPR_UPDATE,NULL_EXPR,PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_DU | PARAMETER_DV | PARAMETER_DERIVATIVE)

#undef	AREAEXPR_PRE
#undef	AREAEXPR
#undef	AREAEXPR_UPDATE



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// calculatenormal "p=p"
#ifndef INIT_SHADING

#define	CALCULATENORMALEXPR_PRE		FUN2EXPR_PRE																		\
									float		*dPdu	=	(float *) ralloc(numVertices*6*sizeof(float),threadMemory);	\
									float		*dPdv	=	dPdu + numVertices*3;										\
									const float	mult	=	((currentShadingState->currentObject->attributes->flags & ATTRIBUTES_FLAGS_INSIDE) ? (float) -1 : (float) 1);	\
									duVector(dPdu,op);																	\
									dvVector(dPdv,op);

#define	CALCULATENORMALEXPR			crossvv(res,dPdu,dPdv);														\
									mulvf(res,mult);

#define	CALCULATENORMALEXPR_UPDATE	res		+=	3;																\
									dPdu	+=	3;																\
									dPdv	+=	3;
#else
#define	CALCULATENORMALEXPR_PRE
#define	CALCULATENORMALEXPR
#define	CALCULATENORMALEXPR_UPDATE
#endif

DEFFUNC(CalculateNormal		,"calculatenormal"			,"p=p"	,CALCULATENORMALEXPR_PRE,CALCULATENORMALEXPR,CALCULATENORMALEXPR_UPDATE,NULL_EXPR,PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_DU | PARAMETER_DV | PARAMETER_DERIVATIVE)

#undef	CALCULATENORMALEXPR_PRE
#undef	CALCULATENORMALEXPR
#undef	CALCULATENORMALEXPR_UPDATE


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// noise	"f=f"
#define	NOISE1D1EXPR				*res	=	FUNCTION(*op);
#define	NOISE1D2EXPR				*res	=	FUNCTION(*op1,*op2);
#define	NOISE1D3EXPR				*res	=	FUNCTION(op);
#define	NOISE1D4EXPR				*res	=	FUNCTION(op1,*op2);

#define	NOISE3D1EXPR				FUNCTION(res,*op);
#define	NOISE3D2EXPR				FUNCTION(res,*op1,*op2);
#define	NOISE3D3EXPR				FUNCTION(res,op);
#define	NOISE3D4EXPR				FUNCTION(res,op1,*op2);

#define	FUNCTION	noiseFloat
DEFFUNC(Noise1D1			,"noise"		,"f=f"	,FUN2EXPR_PRE,NOISE1D1EXPR,FUN2EXPR_UPDATE(1,1),NULL_EXPR,0)
DEFFUNC(Noise1D2			,"noise"		,"f=ff"	,FUN3EXPR_PRE,NOISE1D2EXPR,FUN3EXPR_UPDATE(1,1,1),NULL_EXPR,0)
DEFFUNC(Noise1D3			,"noise"		,"f=p"	,FUN2EXPR_PRE,NOISE1D3EXPR,FUN2EXPR_UPDATE(1,3),NULL_EXPR,0)
DEFFUNC(Noise1D4			,"noise"		,"f=pf"	,FUN3EXPR_PRE,NOISE1D4EXPR,FUN3EXPR_UPDATE(1,3,1),NULL_EXPR,0)
#undef FUNCTION

#define	FUNCTION	noiseVector
DEFLINKFUNC(Noise1Dv1		,"noise"		,"c=f",	0)
DEFLINKFUNC(Noise1Dv2		,"noise"		,"p=f",	0)
DEFLINKFUNC(Noise1Dv3		,"noise"		,"n=f",	0)
DEFFUNC(Noise3D1			,"noise"		,"v=f"	,FUN2EXPR_PRE,NOISE3D1EXPR,FUN2EXPR_UPDATE(3,1),NULL_EXPR,0)
DEFLINKFUNC(Noise2Dv1		,"noise"		,"c=ff",	0)
DEFLINKFUNC(Noise2Dv2		,"noise"		,"p=ff",	0)
DEFLINKFUNC(Noise2Dv3		,"noise"		,"n=ff",	0)
DEFFUNC(Noise3D2			,"noise"		,"v=ff"	,FUN3EXPR_PRE,NOISE3D2EXPR,FUN3EXPR_UPDATE(3,1,1),NULL_EXPR,0)
DEFLINKFUNC(Noise3Dv1		,"noise"		,"c=p",	0)
DEFLINKFUNC(Noise3Dv2		,"noise"		,"p=p",	0)
DEFLINKFUNC(Noise3Dv3		,"noise"		,"n=p",	0)
DEFFUNC(Noise3D3			,"noise"		,"v=p"	,FUN2EXPR_PRE,NOISE3D3EXPR,FUN2EXPR_UPDATE(3,3),NULL_EXPR,0)
DEFLINKFUNC(Noise4Dv1		,"noise"		,"c=pf",	0)
DEFLINKFUNC(Noise4Dv2		,"noise"		,"p=pf",	0)
DEFLINKFUNC(Noise4Dv3		,"noise"		,"n=pf",	0)
DEFFUNC(Noise3D4			,"noise"		,"v=pf"	,FUN3EXPR_PRE,NOISE3D4EXPR,FUN3EXPR_UPDATE(3,3,1),NULL_EXPR,0)
#undef FUNCTION

#define	FUNCTION	cellNoiseFloat
DEFFUNC(CellNoise1D1			,"cellnoise"		,"f=f"	,FUN2EXPR_PRE,NOISE1D1EXPR,FUN2EXPR_UPDATE(1,1),NULL_EXPR,0)
DEFFUNC(CellNoise1D2			,"cellnoise"		,"f=ff"	,FUN3EXPR_PRE,NOISE1D2EXPR,FUN3EXPR_UPDATE(1,1,1),NULL_EXPR,0)
DEFFUNC(CellNoise1D3			,"cellnoise"		,"f=p"	,FUN2EXPR_PRE,NOISE1D3EXPR,FUN2EXPR_UPDATE(1,3),NULL_EXPR,0)
DEFFUNC(CellNoise1D4			,"cellnoise"		,"f=pf"	,FUN3EXPR_PRE,NOISE1D4EXPR,FUN3EXPR_UPDATE(1,3,1),NULL_EXPR,0)
#undef FUNCTION

#define	FUNCTION	cellNoiseVector
DEFLINKFUNC(CellNoise1Dv1		,"cellnoise"		,"c=f",	0)
DEFLINKFUNC(CellNoise1Dv2		,"cellnoise"		,"p=f",	0)
DEFLINKFUNC(CellNoise1Dv3		,"cellnoise"		,"n=f",	0)
DEFFUNC(CellNoise3D1			,"cellnoise"		,"v=f"	,FUN2EXPR_PRE,NOISE3D1EXPR,FUN2EXPR_UPDATE(3,1),NULL_EXPR,0)
DEFLINKFUNC(CellNoise2Dv1		,"cellnoise"		,"c=ff",	0)
DEFLINKFUNC(CellNoise2Dv2		,"cellnoise"		,"p=ff",	0)
DEFLINKFUNC(CellNoise2Dv3		,"cellnoise"		,"n=ff",	0)
DEFFUNC(CellNoise3D2			,"cellnoise"		,"v=ff"	,FUN3EXPR_PRE,NOISE3D2EXPR,FUN3EXPR_UPDATE(3,1,1),NULL_EXPR,0)
DEFLINKFUNC(CellNoise3Dv1		,"cellnoise"		,"c=p",	0)
DEFLINKFUNC(CellNoise3Dv2		,"cellnoise"		,"p=p",	0)
DEFLINKFUNC(CellNoise3Dv3		,"cellnoise"		,"n=p",	0)
DEFFUNC(CellNoise3D3			,"cellnoise"		,"v=p"	,FUN2EXPR_PRE,NOISE3D3EXPR,FUN2EXPR_UPDATE(3,3),NULL_EXPR,0)
DEFLINKFUNC(CellNoise4Dv1		,"cellnoise"		,"c=pf",	0)
DEFLINKFUNC(CellNoise4Dv2		,"cellnoise"		,"p=pf",	0)
DEFLINKFUNC(CellNoise4Dv3		,"cellnoise"		,"n=pf",	0)
DEFFUNC(CellNoise3D4			,"cellnoise"		,"v=pf"	,FUN3EXPR_PRE,NOISE3D4EXPR,FUN3EXPR_UPDATE(3,3,1),NULL_EXPR,0)
#undef FUNCTION


#define	PNOISE1D1EXPR				*res	=	FUNCTION(*op1,*op2);
#define	PNOISE1D2EXPR				*res	=	FUNCTION(*op1,*op2,*op3,*op4);
#define	PNOISE1D3EXPR				*res	=	FUNCTION(op1,op2);
#define	PNOISE1D4EXPR				*res	=	FUNCTION(op1,*op2,op3,*op4);

#define	PNOISE3D1EXPR				FUNCTION(res,*op1,*op2);
#define	PNOISE3D2EXPR				FUNCTION(res,*op1,*op2,*op3,*op4);
#define	PNOISE3D3EXPR				FUNCTION(res,op1,op2);
#define	PNOISE3D4EXPR				FUNCTION(res,op1,*op2,op3,*op4);

#define	FUNCTION	pnoiseFloat
DEFFUNC(PNoise1D1			,"pnoise"		,"f=ff"		,FUN3EXPR_PRE,PNOISE1D1EXPR,FUN3EXPR_UPDATE(1,1,1),NULL_EXPR,0)
DEFFUNC(PNoise1D2			,"pnoise"		,"f=ffff"	,FUN5EXPR_PRE,PNOISE1D2EXPR,FUN5EXPR_UPDATE(1,1,1,1,1),NULL_EXPR,0)
DEFFUNC(PNoise1D3			,"pnoise"		,"f=pp"		,FUN3EXPR_PRE,PNOISE1D3EXPR,FUN3EXPR_UPDATE(1,3,3),NULL_EXPR,0)
DEFFUNC(PNoise1D4			,"pnoise"		,"f=pfpf"	,FUN5EXPR_PRE,PNOISE1D4EXPR,FUN5EXPR_UPDATE(1,3,1,3,1),NULL_EXPR,0)
#undef FUNCTION

#define	FUNCTION	pnoiseVector
DEFLINKFUNC(PNoise1Dv1		,"pnoise"		,"c=ff",	0)
DEFLINKFUNC(PNoise1Dv2		,"pnoise"		,"p=ff",	0)
DEFLINKFUNC(PNoise1Dv3		,"pnoise"		,"n=ff",	0)
DEFFUNC(PNoise3D1			,"pnoise"		,"v=ff"	,	FUN3EXPR_PRE,PNOISE3D1EXPR,FUN3EXPR_UPDATE(3,1,1),NULL_EXPR,0)
DEFLINKFUNC(PNoise2Dv1		,"pnoise"		,"c=ffff",	0)
DEFLINKFUNC(PNoise2Dv2		,"pnoise"		,"p=ffff",	0)
DEFLINKFUNC(PNoise2Dv3		,"pnoise"		,"n=ffff",	0)
DEFFUNC(PNoise3D2			,"pnoise"		,"v=ffff",	FUN5EXPR_PRE,PNOISE3D2EXPR,FUN5EXPR_UPDATE(3,1,1,1,1),NULL_EXPR,0)
DEFLINKFUNC(PNoise3Dv1		,"pnoise"		,"c=pp",	0)
DEFLINKFUNC(PNoise3Dv2		,"pnoise"		,"p=pp",	0)
DEFLINKFUNC(PNoise3Dv3		,"pnoise"		,"n=pp",	0)
DEFFUNC(PNoise3D3			,"pnoise"		,"v=pp"	,	FUN3EXPR_PRE,PNOISE3D3EXPR,FUN3EXPR_UPDATE(3,3,3),NULL_EXPR,0)
DEFLINKFUNC(PNoise4Dv1		,"pnoise"		,"c=pfpf",	0)
DEFLINKFUNC(PNoise4Dv2		,"pnoise"		,"p=pfpf",	0)
DEFLINKFUNC(PNoise4Dv3		,"pnoise"		,"n=pfpf",	0)
DEFFUNC(PNoise3D4			,"pnoise"		,"v=pfpf",	FUN5EXPR_PRE,PNOISE3D4EXPR,FUN5EXPR_UPDATE(3,3,1,3,1),NULL_EXPR,0)
#undef FUNCTION

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ctransform "c=Sc"
#define	CTRANSFORMEXPR_PRE	const float			*from,*to;											\
							float				*res;												\
							const char			**op1;												\
							const float			*op2;												\
							operand(0,res,float *);													\
							operand(1,op1,const char **);											\
							operand(2,op2,const float *);											\
							ECoordinateSystem	cSystem;											\
							findCoordinateSystem(*op1,from,to,cSystem);
							
#define	CTRANSFORMEXPR		convertColorTo(res,op2,cSystem);

DEFFUNC(CTransform		,"ctransform"			,"c=Sc"	,CTRANSFORMEXPR_PRE,CTRANSFORMEXPR,FUN3EXPR_UPDATE(3,0,3),NULL_EXPR,0)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ctransform "c=SSc"
#define	CTRANSFORMSEXPR_PRE	const float			*from,*to;											\
							vector				vtmp;												\
							ECoordinateSystem	cSystemFrom,cSystemTo;								\
							float				*res;												\
							const char			**op1;												\
							const char			**op2;												\
							const float			*op3;												\
							operand(0,res,float *);													\
							operand(1,op1,const char **);											\
							operand(2,op2,const char **);											\
							operand(3,op3,const float *);											\
							findCoordinateSystem(*op1,from,to,cSystemFrom);							\
							findCoordinateSystem(*op2,from,to,cSystemTo);

#define CTRANSFORMSEXPR		convertColorFrom(vtmp,op3,cSystemFrom);									\
							convertColorTo(res,vtmp,cSystemTo);


DEFFUNC(CTransforms		,"ctransform"			,"c=SSc"	,CTRANSFORMSEXPR_PRE,CTRANSFORMSEXPR,FUN4EXPR_UPDATE(3,0,0,3),NULL_EXPR,0)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// transform "p=Sp
#define	TRANSFORM1EXPR_PRE	ECoordinateSystem	cSystem;											\
							const float			*from,*to;											\
							float				*res;												\
							const char			**op1;												\
							const float			*op2;												\
							operand(0,res,float *);													\
							operand(1,op1,const char **);											\
							operand(2,op2,const float *);											\
							findCoordinateSystem(*op1,from,to,cSystem);


#define	TRANSFORM1EXPR		mulmp(res,to,op2);


#define	TRANSFORM1EXPR_UPDATE	FUN3EXPR_UPDATE(3,0,3);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// transform "p=SSp"
#define	TRANSFORM2EXPR_PRE	ECoordinateSystem	cSystemFrom,cSystemTo;								\
							const float			*from1,*to1,*from2,*to2;							\
							vector				vtmp;												\
							float				*res;												\
							const char			**op1;												\
							const char			**op2;												\
							const float			*op3;												\
							operand(0,res,float *);													\
							operand(1,op1,const char **);											\
							operand(2,op2,const char **);											\
							operand(3,op3,const float *);											\
							findCoordinateSystem(*op1,from1,to1,cSystemFrom);						\
							findCoordinateSystem(*op2,from2,to2,cSystemTo);

#define	TRANSFORM2EXPR		mulmp(vtmp,from1,op3);													\
							mulmp(res,to2,vtmp);

#define	TRANSFORM2EXPR_UPDATE	FUN4EXPR_UPDATE(3,0,0,3);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// transform "p=mp"
#define	TRANSFORM3EXPR		mulmp(res,op1,op2);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// transform "p=Smp"
#define	TRANSFORM4EXPR_PRE	ECoordinateSystem	cSystem;											\
							const float			*from,*to;											\
							vector				vtmp;												\
							float				*res;												\
							const char			**op1;												\
							const float			*op2;												\
							const float			*op3;												\
							operand(0,res,float *);													\
							operand(1,op1,const char **);											\
							operand(2,op2,const float *);											\
							operand(3,op3,const float *);											\
							findCoordinateSystem(*op1,from,to,cSystem);

#define	TRANSFORM4EXPR		mulmp(vtmp,from,op3);													\
							mulmp(res,op2,vtmp);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// vtransform "p=Sp
#define	VTRANSFORM1EXPR_PRE	ECoordinateSystem	cSystem;											\
							const float			*from,*to;											\
							float				*res;												\
							const char			**op1;												\
							const float			*op2;												\
							operand(0,res,float *);													\
							operand(1,op1,const char **);											\
							operand(2,op2,const float *);											\
							findCoordinateSystem(*op1,from,to,cSystem);

#define	VTRANSFORM1EXPR		mulmv(res,to,op2);


#define	VTRANSFORM1EXPR_UPDATE	FUN3EXPR_UPDATE(3,0,3);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ntransform "p=Sp
#define	NTRANSFORM1EXPR_PRE	ECoordinateSystem	cSystem;											\
							const float			*from,*to;											\
							float				*res;												\
							const char			**op1;												\
							const float			*op2;												\
							operand(0,res,float *);													\
							operand(1,op1,const char **);											\
							operand(2,op2,const float *);											\
							findCoordinateSystem(*op1,from,to,cSystem);								\

#define	NTRANSFORM1EXPR		mulmn(res,from,op2);

#define	NTRANSFORM1EXPR_UPDATE	FUN3EXPR_UPDATE(3,0,3);												\


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// vtransform "p=SSp"
#define VTRANSFORM2EXPR_PRE	ECoordinateSystem	cSystemFrom,cSystemTo;								\
							const float			*from1,*to1,*from2,*to2;							\
							vector				vtmp;												\
							float				*res;												\
							const char			**op1;												\
							const char			**op2;												\
							const float			*op3;												\
							operand(0,res,float *);													\
							operand(1,op1,const char **);											\
							operand(2,op2,const char **);											\
							operand(3,op3,const float *);											\
							findCoordinateSystem(*op1,from1,to1,cSystemFrom);						\
							findCoordinateSystem(*op2,from2,to2,cSystemTo);

#define	VTRANSFORM2EXPR		mulmv(vtmp,from1,op3);													\
							mulmv(res,to2,vtmp);

#define VTRANSFORM2EXPR_UPDATE	FUN4EXPR_UPDATE(3,0,0,3);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ntransform "p=SSp"
#define NTRANSFORM2EXPR_PRE	ECoordinateSystem	cSystemFrom,cSystemTo;								\
							const float			*from1,*to1,*from2,*to2;							\
							vector				vtmp;												\
							float				*res;												\
							const char			**op1;												\
							const char			**op2;												\
							const float			*op3;												\
							operand(0,res,float *);													\
							operand(1,op1,const char **);											\
							operand(2,op2,const char **);											\
							operand(3,op3,const float *);											\
							findCoordinateSystem(*op1,from1,to1,cSystemFrom);						\
							findCoordinateSystem(*op2,from2,to2,cSystemTo);

#define	NTRANSFORM2EXPR		mulmn(vtmp,to1,op3);													\
							mulmn(res,from2,vtmp);

#define NTRANSFORM2EXPR_UPDATE	FUN4EXPR_UPDATE(3,0,0,3);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// vtransform "p=mp"
#define	VTRANSFORM3EXPR		mulmv(res,op1,op2);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ntransform "p=mp"
#define	NTRANSFORM3EXPR		matrix	mtmp;							\
							invertm(mtmp,op1);						\
							mulmn(res,mtmp,op2);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// vtransform "p=Smp"
#define	VTRANSFORM4EXPR_PRE	ECoordinateSystem	cSystem;											\
							const float			*from,*to;											\
							vector				vtmp;												\
							float				*res;												\
							const char			**op1;												\
							const float			*op2;												\
							const float			*op3;												\
							operand(0,res,float *);													\
							operand(1,op1,const char **);											\
							operand(2,op2,const float *);											\
							operand(3,op3,const float *);											\
							findCoordinateSystem(*op1,from,to,cSystem);

#define	VTRANSFORM4EXPR		mulmv(vtmp,from,op3);													\
							mulmv(res,op2,vtmp);

#define	VTRANSFORM4EXPR_UPDATE	FUN4EXPR_UPDATE(3,0,16,3);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ntransform "p=Smp"
#define	NTRANSFORM4EXPR_PRE	ECoordinateSystem	cSystem;											\
							const float			*from,*to;											\
							matrix				mtmp;												\
							vector				vtmp;												\
							float				*res;												\
							const char			**op1;												\
							const float			*op2;												\
							const float			*op3;												\
							operand(0,res,float *);													\
							operand(1,op1,const char **);											\
							operand(2,op2,const float *);											\
							operand(3,op3,const float *);											\
							findCoordinateSystem(*op1,from,to,cSystem);

#define	NTRANSFORM4EXPR		invertm(mtmp,op2);														\
							mulmn(vtmp,to,op3);														\
							mulmn(res,mtmp,vtmp);

#define	NTRANSFORM4EXPR_UPDATE	FUN4EXPR_UPDATE(3,0,16,3);


DEFFUNC(Transform1		,"transform"			,"p=Sp"		,TRANSFORM1EXPR_PRE,TRANSFORM1EXPR,TRANSFORM1EXPR_UPDATE,NULL_EXPR,0)
DEFFUNC(Transform2		,"transform"			,"p=SSp"	,TRANSFORM2EXPR_PRE,TRANSFORM2EXPR,TRANSFORM2EXPR_UPDATE,NULL_EXPR,0)
DEFFUNC(Transform3		,"transform"			,"p=mp"		,FUN3EXPR_PRE,TRANSFORM3EXPR,FUN3EXPR_UPDATE(3,16,3),NULL_EXPR,0)
DEFFUNC(Transform4		,"transform"			,"p=Smp"	,TRANSFORM4EXPR_PRE,TRANSFORM4EXPR,FUN4EXPR_UPDATE(3,1,16,3),NULL_EXPR,0)
DEFFUNC(VTransform1		,"vtransform"			,"v=Sv"		,VTRANSFORM1EXPR_PRE,VTRANSFORM1EXPR,VTRANSFORM1EXPR_UPDATE,NULL_EXPR,0)
DEFFUNC(VTransform2		,"vtransform"			,"v=SSv"	,VTRANSFORM2EXPR_PRE,VTRANSFORM2EXPR,VTRANSFORM2EXPR_UPDATE,NULL_EXPR,0)
DEFFUNC(VTransform3		,"vtransform"			,"v=mv"		,FUN3EXPR_PRE,VTRANSFORM3EXPR,FUN3EXPR_UPDATE(3,16,3),NULL_EXPR,0)
DEFFUNC(VTransform4		,"vtransform"			,"v=Smv"	,VTRANSFORM4EXPR_PRE,VTRANSFORM4EXPR,VTRANSFORM4EXPR_UPDATE,NULL_EXPR,0)
DEFFUNC(NTransform1		,"ntransform"			,"n=Sn"		,NTRANSFORM1EXPR_PRE,NTRANSFORM1EXPR,NTRANSFORM1EXPR_UPDATE,NULL_EXPR,0)
DEFFUNC(NTransform2		,"ntransform"			,"n=SSn"	,NTRANSFORM2EXPR_PRE,NTRANSFORM2EXPR,NTRANSFORM2EXPR_UPDATE,NULL_EXPR,0)
DEFFUNC(NTransform3		,"ntransform"			,"n=mn"		,FUN3EXPR_PRE,NTRANSFORM3EXPR,FUN3EXPR_UPDATE(3,16,3),NULL_EXPR,0)
DEFFUNC(NTransform4		,"ntransform"			,"n=Smn"	,NTRANSFORM4EXPR_PRE,NTRANSFORM4EXPR,NTRANSFORM4EXPR_UPDATE,NULL_EXPR,0)



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// depth "f=p"
#define DEPTHEXPR		*res	=	(op[2] - CRenderer::clipMin) / (CRenderer::clipMax - CRenderer::clipMin);

DEFFUNC(Depth		,"depth"			,"f=p"	,FUN2EXPR_PRE,DEPTHEXPR,FUN2EXPR_UPDATE(1,3),NULL_EXPR,0)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// clearlighting	"o="
#define	CLEARLIGHTINGEXPR_PRE	clearLighting();

DEFFUNC(Clearlighting			,"clearlighting"				,"o="		,CLEARLIGHTINGEXPR_PRE,NULL_EXPR,NULL_EXPR,NULL_EXPR,0)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ambient	"c="
#define	AMBIENTEXPR_PRE		const float		*Clsave;											\
							float			*res;												\
							operand(0,res,float *);												\
							runAmbientLights();													\
							Clsave = (*alights)->savedState[1];

#define AMBIENTEXPR			movvv(res,Clsave);

#define	AMBIENTEXPR_UPDATE	res		+=	3;														\
							Clsave	+=	3;

DEFFUNC(Ambient			,"ambient"				,"c="		,AMBIENTEXPR_PRE,AMBIENTEXPR,AMBIENTEXPR_UPDATE,NULL_EXPR,0)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// diffuse	"c=n"
#define	DIFFUSEEXPR_PRE		float			*costheta	=	(float *) ralloc(numVertices*sizeof(float),threadMemory);	\
							float			*res;												\
							const float		*op;												\
							vector			Ltmp;												\
							for (int i=0;i<numVertices;++i) costheta[i]	=	0;					\
							operand(0,res,float *);												\
							operand(1,op,const float *);										\
							const float	*P		=	varying[VARIABLE_P];						\
							const float	*N		=	op;											\
																								\
							runLights(P,N,costheta);											\
							/* initialize output appropriately */								\
							float *R			=	res;										\
							tags				=	tagStart;									\
							for (int i=0;i<numVertices;++i) {									\
								if (*tags == 0) initv(R,0,0,0);									\
								R += 3;															\
								++tags;															\
							}																	\
							/* loop the lighting contributions */								\
							*currentLight	=	*lights;										\
							while (*currentLight) {												\
								int				ndStep;											\
								float			_nd = 0;										\
								const float		*nd;											\
								enterFastLightingConditional();									\
								CShaderInstance *_inst = (*currentLight)->instance;				\
								if (_inst ->flags & SHADERFLAGS_NONDIFFUSE) {					\
									CLightShaderData *lightData = (CLightShaderData*) _inst->data;			\
									nd		=	(*currentLight)->savedState[2+lightData->nonDiffuseIndex];	\
									ndStep 	=	lightData->nonDiffuseStep;						\
								} else {														\
									nd		=	&_nd;											\
									ndStep	=	0;												\
								}																\
								const float	*L		=	(*currentLight)->savedState[0];			\
								const float	*Cl		=	(*currentLight)->savedState[1];			\
								R		=	res;												\
								N		=	op;													\
								tags	=	tagStart;


#define DIFFUSEEXPR			normalizev(Ltmp,L);													\
							const float coefficient = (1.0f-nd[0])*dotvv(N,Ltmp);				\
							if (coefficient > 0) {												\
								R[COMP_R] += coefficient * Cl[COMP_R];							\
								R[COMP_G] += coefficient * Cl[COMP_G];							\
								R[COMP_B] += coefficient * Cl[COMP_B];							\
							}
								
#define	DIFFUSEEXPR_UPDATE	R		+=	3;														\
							N		+=	3;														\
							Cl		+=	3;														\
							L		+=	3;														\
							nd		+=	ndStep;

#define DIFFUSEEXPR_POST		exitFastLightingConditional();									\
								*currentLight=(*currentLight)->next;							\
							}

DEFLIGHTFUNC(Diffuse				,"diffuse"				,"c=n"		,DIFFUSEEXPR_PRE, DIFFUSEEXPR, DIFFUSEEXPR_UPDATE, DIFFUSEEXPR_POST, PARAMETER_P)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// diffuse	"c=pnf"
#define	DIFFUSE2EXPR_PRE	const float		*P,*N;												\
							float			*costheta	=	(float *) ralloc(numVertices*sizeof(float),threadMemory); \
							const float		*cosangle;											\
							const float		*op3;												\
							vector			Ltmp;												\
							float			*res;												\
							const float		*op2;												\
							operand(0,res,float *);												\
							operand(1,P,const float *);											\
							operand(2,op2,const float *);										\
							operand(3,op3,const float *);										\
							for (int i=0;i<numVertices;++i) costheta[i] = (float) cos(op3[i]);	\
							N		=	op2;													\
							runLights(P,N,costheta);											\
							/* initialize output appropriately */								\
							float *R		=	res;											\
							tags			=	tagStart;										\
							for (int i=0;i<numVertices;++i) {									\
								if (*tags==0) initv(R,0,0,0);									\
								R += 3;															\
								++tags;															\
							}																	\
							/* loop the lighting contributions */								\
							*currentLight = *lights;											\
							while (*currentLight) {												\
								int				ndStep;											\
								float			_nd = 0;										\
								const float		*nd;											\
								enterFastLightingConditional();									\
								CShaderInstance *_inst = (*currentLight)->instance;				\
								if (_inst ->flags & SHADERFLAGS_NONDIFFUSE) {					\
									CLightShaderData *lightData = (CLightShaderData*) _inst->data;			\
									nd		=	(*currentLight)->savedState[2+lightData->nonDiffuseIndex];	\
									ndStep 	=	lightData->nonDiffuseStep;						\
								} else {														\
									nd		=	&_nd;											\
									ndStep	=	0;												\
								}																\
								const float *L	=	(*currentLight)->savedState[0];				\
								const float *Cl	=	(*currentLight)->savedState[1];				\
								R			=	res;											\
								N			=	op2;											\
								cosangle	=	costheta;										\
								tags		=	tagStart;

#define DIFFUSE2EXPR		normalizev(Ltmp,L);													\
							const float coefficient = (1.0f-nd[0])*dotvv(N,Ltmp);				\
							if (coefficient > *cosangle) {										\
								R[COMP_R] += coefficient * Cl[COMP_R];							\
								R[COMP_G] += coefficient * Cl[COMP_G];							\
								R[COMP_B] += coefficient * Cl[COMP_B];							\
							}

#define	DIFFUSE2EXPR_UPDATE	R			+=	3;													\
							N			+=	3;													\
							cosangle	+=	1;													\
							Cl			+=	3;													\
							L			+=	3;													\
							nd			+=	ndStep;
							

#define DIFFUSE2EXPR_POST		exitFastLightingConditional();									\
								*currentLight=(*currentLight)->next;							\
							}


DEFLIGHTFUNC(Diffuse2			,"diffuse"				,"c=pnf"	,DIFFUSE2EXPR_PRE, DIFFUSE2EXPR, DIFFUSE2EXPR_UPDATE, DIFFUSE2EXPR_POST, 0)




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// specular	"c=nvf"
#define	SPECULAREXPR_PRE		float			*costheta	=	(float *) ralloc(numVertices*sizeof(float),threadMemory);	\
								float			*powers		=	(float *) ralloc(numVertices*sizeof(float),threadMemory);	\
								const float		*op1,*op2,*op3;										\
								float			*res;												\
								vector			Ltmp,halfway;										\
								operand(0,res,float *);												\
								operand(1,op1,const float *);										\
								operand(2,op2,const float *);										\
								operand(3,op3,const float *);										\
								for (int i=0;i<numVertices;++i)	costheta[i]	=	0;					\
								const float *P		=	varying[VARIABLE_P];						\
								const float *N		=	op1;										\
								runLights(P,N,costheta);											\
								/* initialize output appropriately */								\
								float *R			=	res;										\
								float *power		=	powers;										\
								tags				=	tagStart;									\
								for (int i=0;i<numVertices;++i) {									\
									if (*tags==0) {													\
										initv(R,0,0,0);												\
										*power = 10.0f / *op3;										\
									}																\
									R			+=	3;												\
									op3			+=	1;												\
									power		+=	1;												\
									++tags;															\
								}																	\
								/* loop the lighting contributions */								\
								*currentLight = *lights;											\
								while (*currentLight) {												\
									float	_ns = 0;												\
									int		nsStep;													\
									const float	*ns;												\
									enterFastLightingConditional();									\
									CShaderInstance *_inst = (*currentLight)->instance;				\
									if (_inst ->flags & SHADERFLAGS_NONSPECULAR) {					\
										CLightShaderData *lightData = (CLightShaderData*) _inst->data;			\
										ns		=	(*currentLight)->savedState[2+lightData->nonSpecularIndex];	\
										nsStep 	=	lightData->nonSpecularStep;						\
									} else {														\
										ns		=	&_ns;											\
										nsStep	=	0;												\
									}																\
									const float *L			=	(*currentLight)->savedState[0];		\
									const float *Cl			=	(*currentLight)->savedState[1];		\
									const float *V			=	op2;								\
									R			=	res;											\
									N			=	op1;											\
									power		=	powers;											\
									tags		=	tagStart;

#define SPECULAREXPR			normalizev(Ltmp,L);													\
								addvv(halfway,V,Ltmp);												\
								normalizev(halfway);												\
								const float	tmp	=	((1.0f-ns[0])*dotvv(N,halfway));				\
								if (tmp > 0) {														\
									const float coefficient = (float) pow(tmp,*power);				\
									R[COMP_R] += coefficient * Cl[COMP_R];							\
									R[COMP_G] += coefficient * Cl[COMP_G];							\
									R[COMP_B] += coefficient * Cl[COMP_B];							\
								}

#define	SPECULAREXPR_UPDATE		R			+=	3;													\
								N			+=	3;													\
								V			+=	3;													\
								power		+=	1;													\
								Cl			+=	3;													\
								L			+=	3;													\
								ns			+=	nsStep;

#define SPECULAREXPR_POST			exitFastLightingConditional();									\
									*currentLight=(*currentLight)->next;							\
								}

DEFLIGHTFUNC(Specular				,"specular"				,"c=nvf"		,SPECULAREXPR_PRE, SPECULAREXPR, SPECULAREXPR_UPDATE, SPECULAREXPR_POST, PARAMETER_P)


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// phong	"c=nvf"
#define	PHONGEXPR_PRE			float			*costheta	=	(float *) ralloc(numVertices*sizeof(float),threadMemory);	\
								float			*refDirs	=	(float *) ralloc(3*numVertices*sizeof(float),threadMemory);	\
								const float		*op1,*op2,*op3;										\
								float			*res;												\
								vector			Ltmp;												\
								operand(0,res,float *);												\
								operand(1,op1,const float *);										\
								operand(2,op2,const float *);										\
								operand(3,op3,const float *);										\
								for (int i=0;i<numVertices;++i)	costheta[i]	=	0;					\
								const float	*P		=	varying[VARIABLE_P];						\
								const float	*N		=	op1;										\
								runLights(P,N,costheta);											\
								/* initialize output appropriately */								\
								float		*R		=	res;										\
								const float	*V		=	op2;										\
								float *refDir		=	refDirs;									\
								N					=	op1;										\
								tags				=	tagStart;									\
								for (int i=0;i<numVertices;++i) {									\
									if (*tags==0) {													\
										initv(R,0,0,0);												\
										mulvf(refDir,N,2*dotvv(N,V));								\
										subvv(refDir,V);											\
									}																\
									R			+=	3;												\
									N			+=	3;												\
									V			+=	3;												\
									refDir		+=	3;												\
									++tags;															\
								}																	\
								/* loop the lighting contributions */								\
								*currentLight = *lights;											\
								while (*currentLight) {												\
									int				nsStep;											\
									const float		*ns;											\
									float			_ns = 0;										\
									enterFastLightingConditional();									\
									CShaderInstance *_inst = (*currentLight)->instance;				\
									if (_inst ->flags & SHADERFLAGS_NONSPECULAR) {					\
										CLightShaderData *lightData = (CLightShaderData*) _inst->data;			\
										ns		=	(*currentLight)->savedState[2+lightData->nonSpecularIndex];	\
										nsStep 	=	lightData->nonSpecularStep;						\
									} else {														\
										ns		=	&_ns;											\
										nsStep	=	0;												\
									}																\
									const float *L			=	(*currentLight)->savedState[0];		\
									const float *Cl			=	(*currentLight)->savedState[1];		\
									const float *size		=	op3;								\
									R			=	res;											\
									refDir		=	refDirs;										\
									tags		=	tagStart;

#define PHONGEXPR				normalizev(Ltmp,L);													\
								const float coefficient = (1.0f-ns[0]) * (float) pow(max(0,dotvv(refDir,Ltmp)),*size);			\
								if (coefficient > 0) {												\
									R[COMP_R] += coefficient * Cl[COMP_R];							\
									R[COMP_G] += coefficient * Cl[COMP_G];							\
									R[COMP_B] += coefficient * Cl[COMP_B];							\
								}

#define	PHONGEXPR_UPDATE		R		+=	3;														\
								size	+=	1;														\
								refDir	+=	3;														\
								Cl		+=	3;														\
								L		+=	3;														\
								ns		+=	nsStep;

#define PHONGEXPR_POST			exitFastLightingConditional();										\
								*currentLight=(*currentLight)->next;								\
							}

DEFLIGHTFUNC(Phong				,"phong"				,"c=nvf"		,PHONGEXPR_PRE, PHONGEXPR, PHONGEXPR_UPDATE, PHONGEXPR_POST, PARAMETER_P)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// specularBRDF	"c=vnvf"
#define	SPECULARBRDFEXPR_PRE	float			*res;												\
								const float		*op1,*op2,*op3,*op4;								\
								vector			halfway;											\
								operand(0,res,float *);												\
								operand(1,op1,const float *);										\
								operand(2,op2,const float *);										\
								operand(3,op3,const float *);										\
								operand(4,op4,const float *);

#define SPECULARBRDFEXPR		addvv(halfway,op3,op1);												\
								normalizev(halfway);												\
								res[0]	=	(float) pow(max(0,dotvv(op2,halfway)),(10.0f)/(*op4));	\
								res[1]	=	res[0];													\
								res[2]	=	res[1];													\

#define	SPECULARBRDFEXPR_UPDATE	res		+=	3;														\
								op1		+=	3;														\
								op2		+=	3;														\
								op3		+=	3;														\
								op4		+=	1;



DEFFUNC(SpecularBRDF			,"specularbrdf"				,"c=vnvf"		,SPECULARBRDFEXPR_PRE,SPECULARBRDFEXPR,SPECULARBRDFEXPR_UPDATE,NULL_EXPR,0)





#ifndef INIT_SHADING


////////////////////
// FIXME: Not 64 bit compatible
#define	PARAMETEREXPR_PRE(accessor)																			\
								float		*res;															\
								const char	**op1;															\
								float		*op2;															\
								int			op2Step;														\
								operand(0,res,float *);														\
								operand(1,op1,const char **);												\
								operand(2,op2,float *);														\
								op2Step = operandVaryingStep(2);											\
																											\
								int			globalIndex =	-1;												\
								CVariable	*cVar		=	NULL;											\
								float		found		=	(float) FUNCTION(op2,*op1,&cVar,&globalIndex);	\
								const float	*src		=	op2;											\
								int			srcStep		=	op2Step;										\
																											\
								if (found != 0) {															\
									srcStep					=	0;											\
									if (cVar != NULL) {														\
										if (cVar->storage == STORAGE_PARAMETER || cVar->storage == STORAGE_MUTABLEPARAMETER) { 				\
											src					=	currentShadingState->locals[accessor][cVar->entry];						\
										} else {																							\
											src					=	varying[cVar->entry];													\
										}																									\
										srcStep				=	cVar->numFloats;															\
										if ((cVar->container == CONTAINER_UNIFORM) || (cVar->container == CONTAINER_CONSTANT)) {			\
											srcStep	=	0;													\
										} else if (op2Step == 0) {											\
											/* guard against varying->uniform assignment : nullify copy */	\
											srcStep	=	0;													\
											src		=	op2;												\
											found	=	0;													\
										}																	\
									}																		\
								}

#define LIGHTPARAMETEREXPR_PRE	float		*res;															\
								const char	**op1;															\
								float		*op2;															\
								int			op2Step;														\
								operand(0,res,float *);														\
								operand(1,op1,const char **);												\
								operand(2,op2,float *);														\
								op2Step = operandVaryingStep(2);											\
																											\
								int			globalIndex =	-1;												\
								CVariable	*cVar		=	NULL;											\
								float		found		=	(float) (*currentLight)->instance->getParameter(*op1,op2,&cVar,&globalIndex);\
								const float	*src		=	op2;											\
								int			srcStep		=	op2Step;										\
																											\
								if (found != 0) {															\
									srcStep				=	0;												\
									if (cVar != NULL) {														\
										src					=	(*currentLight)->savedState[2+globalIndex];								\
										srcStep				=	cVar->numFloats;														\
										if ((cVar->container == CONTAINER_UNIFORM) || (cVar->container == CONTAINER_CONSTANT)) {		\
											srcStep	=	0;													\
										} else if (op2Step == 0) {											\
											/* guard against varying->uniform assignment : nullify copy */	\
											srcStep		=	0;												\
											src			=	op2;											\
											found		=	0;												\
										}																	\
									}																		\
								}

#define	PARAMETEREXPRF			*res		=	found;												\
								*op2		=	*src;

#define	PARAMETEREXPRS			*res		=	found;												\
								*op2		=	*src;

#define	PARAMETEREXPRV			*res		=	found;												\
								op2[0]		=	src[0];												\
								op2[1]		=	src[1];												\
								op2[2]		=	src[2];

#define	PARAMETEREXPRM			*res		=	found;												\
								op2[0]		=	src[0];												\
								op2[1]		=	src[1];												\
								op2[2]		=	src[2];												\
								op2[3]		=	src[3];												\
								op2[4]		=	src[4];												\
								op2[5]		=	src[5];												\
								op2[6]		=	src[6];												\
								op2[7]		=	src[7];												\
								op2[8]		=	src[8];												\
								op2[9]		=	src[9];												\
								op2[10]		=	src[10];											\
								op2[11]		=	src[11];											\
								op2[12]		=	src[12];											\
								op2[13]		=	src[13];											\
								op2[14]		=	src[14];											\
								op2[15]		=	src[15];


#define	PARAMETEREXPR_UPDATE(__r,__o2)																\
								res			+=	__r;												\
								op2			+=	__o2;												\
								src			+=	srcStep;

#else
#undef PARAMETEREXPR_PRE
#undef LIGHTPARAMETEREXPR_PRE
#undef PARAMETEREXPRF
#undef PARAMETEREXPRS
#undef PARAMETEREXPRV
#undef PARAMETEREXPRM
#undef PARAMETEREXPR_UPDATE
#define PARAMETEREXPR_PRE(a)
#define LIGHTPARAMETEREXPR_PRE
#define PARAMETEREXPRF
#define PARAMETEREXPRS
#define PARAMETEREXPRV
#define PARAMETEREXPRM
#define PARAMETEREXPR_UPDATE
#endif

#define	FUNCTION	displacementParameter
DEFLINKFUNC(Displacement2			,"displacement"				,"f=SC",	PARAMETER_MESSAGEPASSING)
DEFLINKFUNC(Displacement3			,"displacement"				,"f=SN",	PARAMETER_MESSAGEPASSING)
DEFLINKFUNC(Displacement4			,"displacement"				,"f=SP",	PARAMETER_MESSAGEPASSING)
DEFFUNC(DisplacementV				,"displacement"				,"f=SV"		,PARAMETEREXPR_PRE(ACCESSOR_DISPLACEMENT),PARAMETEREXPRV,PARAMETEREXPR_UPDATE(1,3),NULL_EXPR,PARAMETER_MESSAGEPASSING)
DEFFUNC(Displacement				,"displacement"				,"f=SF"		,PARAMETEREXPR_PRE(ACCESSOR_DISPLACEMENT),PARAMETEREXPRF,PARAMETEREXPR_UPDATE(1,1),NULL_EXPR,PARAMETER_MESSAGEPASSING)
DEFFUNC(DisplacementS				,"displacement"				,"f=SS"		,PARAMETEREXPR_PRE(ACCESSOR_DISPLACEMENT),PARAMETEREXPRS,PARAMETEREXPR_UPDATE(1,1),NULL_EXPR,PARAMETER_MESSAGEPASSING)
DEFFUNC(DisplacementM				,"displacement"				,"f=SM"		,PARAMETEREXPR_PRE(ACCESSOR_DISPLACEMENT),PARAMETEREXPRM,PARAMETEREXPR_UPDATE(1,16),NULL_EXPR,PARAMETER_MESSAGEPASSING)
#undef FUNCTION

#define	FUNCTION	surfaceParameter
DEFLINKFUNC(Surface2			,"surface"				,"f=SC",	PARAMETER_MESSAGEPASSING)
DEFLINKFUNC(Surface3			,"surface"				,"f=SN",	PARAMETER_MESSAGEPASSING)
DEFLINKFUNC(Surface4			,"surface"				,"f=SP",	PARAMETER_MESSAGEPASSING)
DEFFUNC(SurfaceV				,"surface"				,"f=SV"		,PARAMETEREXPR_PRE(ACCESSOR_SURFACE),PARAMETEREXPRV,PARAMETEREXPR_UPDATE(1,3),NULL_EXPR,PARAMETER_MESSAGEPASSING)
DEFFUNC(Surface					,"surface"				,"f=SF"		,PARAMETEREXPR_PRE(ACCESSOR_SURFACE),PARAMETEREXPRF,PARAMETEREXPR_UPDATE(1,1),NULL_EXPR,PARAMETER_MESSAGEPASSING)
DEFFUNC(SurfaceS				,"surface"				,"f=SS"		,PARAMETEREXPR_PRE(ACCESSOR_SURFACE),PARAMETEREXPRS,PARAMETEREXPR_UPDATE(1,1),NULL_EXPR,PARAMETER_MESSAGEPASSING)
DEFFUNC(SurfaceM				,"surface"				,"f=SM"		,PARAMETEREXPR_PRE(ACCESSOR_SURFACE),PARAMETEREXPRM,PARAMETEREXPR_UPDATE(1,16),NULL_EXPR,PARAMETER_MESSAGEPASSING)
#undef FUNCTION

DEFLINKFUNC(Lightsource2			,"lightsource"				,"f=SC",	PARAMETER_MESSAGEPASSING)
DEFLINKFUNC(Lightsource3			,"lightsource"				,"f=SN",	PARAMETER_MESSAGEPASSING)
DEFLINKFUNC(Lightsource4			,"lightsource"				,"f=SP",	PARAMETER_MESSAGEPASSING)
DEFFUNC(LightsourceV				,"lightsource"				,"f=SV"		,LIGHTPARAMETEREXPR_PRE,PARAMETEREXPRV,PARAMETEREXPR_UPDATE(1,3),NULL_EXPR,PARAMETER_MESSAGEPASSING)
DEFFUNC(Lightsource					,"lightsource"				,"f=SF"		,LIGHTPARAMETEREXPR_PRE,PARAMETEREXPRF,PARAMETEREXPR_UPDATE(1,1),NULL_EXPR,PARAMETER_MESSAGEPASSING)
DEFFUNC(LightsourceS				,"lightsource"				,"f=SS"		,LIGHTPARAMETEREXPR_PRE,PARAMETEREXPRS,PARAMETEREXPR_UPDATE(1,1),NULL_EXPR,PARAMETER_MESSAGEPASSING)
DEFFUNC(LightsourceM				,"lightsource"				,"f=SM"		,LIGHTPARAMETEREXPR_PRE,PARAMETEREXPRM,PARAMETEREXPR_UPDATE(1,16),NULL_EXPR,PARAMETER_MESSAGEPASSING)

#define	FUNCTION	atmosphereParameter
DEFLINKFUNC(Atmosphere2			,"atmosphere"				,"f=SC",	PARAMETER_MESSAGEPASSING)
DEFLINKFUNC(Atmosphere3			,"atmosphere"				,"f=SN",	PARAMETER_MESSAGEPASSING)
DEFLINKFUNC(Atmosphere4			,"atmosphere"				,"f=SP",	PARAMETER_MESSAGEPASSING)
DEFFUNC(AtmosphereV				,"atmosphere"				,"f=SV"		,PARAMETEREXPR_PRE(ACCESSOR_ATMOSPHERE),PARAMETEREXPRV,PARAMETEREXPR_UPDATE(1,3),NULL_EXPR,PARAMETER_MESSAGEPASSING)
DEFFUNC(Atmosphere				,"atmosphere"				,"f=SF"		,PARAMETEREXPR_PRE(ACCESSOR_ATMOSPHERE),PARAMETEREXPRF,PARAMETEREXPR_UPDATE(1,1),NULL_EXPR,PARAMETER_MESSAGEPASSING)
DEFFUNC(AtmosphereS				,"atmosphere"				,"f=SS"		,PARAMETEREXPR_PRE(ACCESSOR_ATMOSPHERE),PARAMETEREXPRS,PARAMETEREXPR_UPDATE(1,1),NULL_EXPR,PARAMETER_MESSAGEPASSING)
DEFFUNC(AtmosphereM				,"atmosphere"				,"f=SM"		,PARAMETEREXPR_PRE(ACCESSOR_ATMOSPHERE),PARAMETEREXPRM,PARAMETEREXPR_UPDATE(1,16),NULL_EXPR,PARAMETER_MESSAGEPASSING)
#undef FUNCTION

/* note that whilst we provide accessors for incident and opposite, they will never be used */

#define	FUNCTION	incidentParameter
DEFLINKFUNC(Incident2			,"incident"				,"f=SC",	PARAMETER_MESSAGEPASSING)
DEFLINKFUNC(Incident3			,"incident"				,"f=SN",	PARAMETER_MESSAGEPASSING)
DEFLINKFUNC(Incident4			,"incident"				,"f=SP",	PARAMETER_MESSAGEPASSING)
DEFFUNC(IncidentV				,"incident"				,"f=SV"		,PARAMETEREXPR_PRE(ACCESSOR_EXTERIOR),PARAMETEREXPRV,PARAMETEREXPR_UPDATE(1,3),NULL_EXPR,PARAMETER_MESSAGEPASSING)
DEFFUNC(Incident				,"incident"				,"f=SF"		,PARAMETEREXPR_PRE(ACCESSOR_EXTERIOR),PARAMETEREXPRF,PARAMETEREXPR_UPDATE(1,1),NULL_EXPR,PARAMETER_MESSAGEPASSING)
DEFFUNC(IncidentS				,"incident"				,"f=SS"		,PARAMETEREXPR_PRE(ACCESSOR_EXTERIOR),PARAMETEREXPRS,PARAMETEREXPR_UPDATE(1,1),NULL_EXPR,PARAMETER_MESSAGEPASSING)
DEFFUNC(IncidentM				,"incident"				,"f=SM"		,PARAMETEREXPR_PRE(ACCESSOR_EXTERIOR),PARAMETEREXPRM,PARAMETEREXPR_UPDATE(1,16),NULL_EXPR,PARAMETER_MESSAGEPASSING)
#undef FUNCTION

#define	FUNCTION	oppositeParameter
DEFLINKFUNC(Opposite2			,"opposite"				,"f=SC",	PARAMETER_MESSAGEPASSING)
DEFLINKFUNC(Opposite3			,"opposite"				,"f=SN",	PARAMETER_MESSAGEPASSING)
DEFLINKFUNC(Opposite4			,"opposite"				,"f=SP",	PARAMETER_MESSAGEPASSING)
DEFFUNC(OppositeV				,"opposite"				,"f=SV"		,PARAMETEREXPR_PRE(ACCESSOR_INTERIOR),PARAMETEREXPRV(ACCESSOR_INTERIOR),PARAMETEREXPR_UPDATE(1,3),NULL_EXPR,PARAMETER_MESSAGEPASSING)
DEFFUNC(Opposite				,"opposite"				,"f=SF"		,PARAMETEREXPR_PRE(ACCESSOR_INTERIOR),PARAMETEREXPRF(ACCESSOR_INTERIOR),PARAMETEREXPR_UPDATE(1,1),NULL_EXPR,PARAMETER_MESSAGEPASSING)
DEFFUNC(OppositeS				,"opposite"				,"f=SS"		,PARAMETEREXPR_PRE(ACCESSOR_INTERIOR),PARAMETEREXPRS(ACCESSOR_INTERIOR),PARAMETEREXPR_UPDATE(1,1),NULL_EXPR,PARAMETER_MESSAGEPASSING)
DEFFUNC(OppositeM				,"opposite"				,"f=SM"		,PARAMETEREXPR_PRE(ACCESSOR_INTERIOR),PARAMETEREXPRM(ACCESSOR_INTERIOR),PARAMETEREXPR_UPDATE(1,16),NULL_EXPR,PARAMETER_MESSAGEPASSING)
#undef FUNCTION

/* note the accessor for the remaining functions is not used */

#define	FUNCTION	attributes
DEFLINKFUNC(Attributes2			,"attribute"				,"f=SC",	0)
DEFLINKFUNC(Attributes3			,"attribute"				,"f=SN",	0)
DEFLINKFUNC(Attributes4			,"attribute"				,"f=SP",	0)
DEFFUNC(AttributesV				,"attribute"				,"f=SV"		,PARAMETEREXPR_PRE(0),PARAMETEREXPRV,PARAMETEREXPR_UPDATE(1,3),NULL_EXPR,0)
DEFFUNC(Attributes				,"attribute"				,"f=SF"		,PARAMETEREXPR_PRE(0),PARAMETEREXPRF,PARAMETEREXPR_UPDATE(1,1),NULL_EXPR,0)
DEFFUNC(AttributesS				,"attribute"				,"f=SS"		,PARAMETEREXPR_PRE(0),PARAMETEREXPRS,PARAMETEREXPR_UPDATE(1,1),NULL_EXPR,0)
DEFFUNC(AttributesM				,"attribute"				,"f=SM"		,PARAMETEREXPR_PRE(0),PARAMETEREXPRM,PARAMETEREXPR_UPDATE(1,16),NULL_EXPR,0)
#undef FUNCTION

#define	FUNCTION	options
DEFLINKFUNC(Options2			,"option"				,"f=SC",	0)
DEFLINKFUNC(Options3			,"option"				,"f=SN",	0)
DEFLINKFUNC(Options4			,"option"				,"f=SP",	0)
DEFFUNC(OptionsV				,"option"				,"f=SV"		,PARAMETEREXPR_PRE(0),PARAMETEREXPRV,PARAMETEREXPR_UPDATE(1,3),NULL_EXPR,0)
DEFFUNC(Options					,"option"				,"f=SF"		,PARAMETEREXPR_PRE(0),PARAMETEREXPRF,PARAMETEREXPR_UPDATE(1,1),NULL_EXPR,0)
DEFFUNC(OptionsS				,"option"				,"f=SS"		,PARAMETEREXPR_PRE(0),PARAMETEREXPRS,PARAMETEREXPR_UPDATE(1,1),NULL_EXPR,0)
DEFFUNC(OptionsM				,"option"				,"f=SM"		,PARAMETEREXPR_PRE(0),PARAMETEREXPRM,PARAMETEREXPR_UPDATE(1,16),NULL_EXPR,0)
#undef FUNCTION

#define	FUNCTION	rendererInfo
DEFLINKFUNC(Rendererinfo2			,"rendererinfo"				,"f=SC",	0)
DEFLINKFUNC(Rendererinfo3			,"rendererinfo"				,"f=SN",	0)
DEFLINKFUNC(Rendererinfo4			,"rendererinfo"				,"f=SP",	0)
DEFFUNC(RendererinfoV				,"rendererinfo"				,"f=SV"		,PARAMETEREXPR_PRE(0),PARAMETEREXPRV,PARAMETEREXPR_UPDATE(1,3),NULL_EXPR,0)
DEFFUNC(Rendererinfo				,"rendererinfo"				,"f=SF"		,PARAMETEREXPR_PRE(0),PARAMETEREXPRF,PARAMETEREXPR_UPDATE(1,1),NULL_EXPR,0)
DEFFUNC(RendererinfoS				,"rendererinfo"				,"f=SS"		,PARAMETEREXPR_PRE(0),PARAMETEREXPRS,PARAMETEREXPR_UPDATE(1,1),NULL_EXPR,0)
DEFFUNC(RendererinfoM				,"rendererinfo"				,"f=SM"		,PARAMETEREXPR_PRE(0),PARAMETEREXPRM,PARAMETEREXPR_UPDATE(1,16),NULL_EXPR,0)
#undef FUNCTION




#ifndef INIT_SHADING

#define	TEXTUREINFO_PRE(_t)		plBegin(CMapInfoLookup,4);											\
								float				*res;											\
								const char			**op1;											\
								const char			**op2;											\
								_t					op3;											\
								float				found;											\
								float				out[16*2];										\
								const char			*outS;											\
								_t					src = (_t) out;									\
								int					op3sz;											\
																									\
								operand(0,res,float *);												\
								operand(1,op1,const char **);										\
								operand(2,op2,const char **);										\
								operandSize(3,op3,op3sz,_t);										\
																									\
								CTextureInfoBase	*textureInfo;									\
								if ((textureInfo = lookup->map) == NULL) {							\
									osLock(CRenderer::shaderMutex);									\
									lookup->map = textureInfo	=	CRenderer::getTextureInfo(*op1);\
									osUnlock(CRenderer::shaderMutex);								\
								}																	\
																									\
								if (textureInfo == NULL) {											\
									found		=	0;												\
									src			=	op3;	/* prevent writing result */			\
								} else {															\
																									\
									for (int i=0;i<16*2;++i) out[i] = 0;							\
																									\
									found				=	1;										\
																									\
									if (strcmp(*op2,"resolution") == 0) {							\
										textureInfo->getResolution(out);							\
									} else if (strcmp(*op2,"type") == 0) {							\
										outS		=	textureInfo->getTextureType();				\
										src			=	(_t) &outS;									\
									} else if (strcmp(*op2,"channels") == 0) {						\
										out[0]		=	(float) textureInfo->getNumChannels();		\
									} else if (strcmp(*op2,"viewingmatrix") == 0) {					\
										found		= (float) textureInfo->getViewMatrix(out);		\
									} else if (strcmp(*op2,"projectionmatrix") == 0) {				\
										found		= (float) textureInfo->getProjectionMatrix(out);\
									} else if (strcmp(*op2,"exists") == 0) {						\
										src			=	op3;	/* prevent writing result */		\
									} else {														\
										found	=	0;												\
										src		=	op3;	/* prevent writing result */			\
									}																\
								}

#define	TEXTUREINFOF			*res		=	found;												\
								*op3		=	src[0];												\
								if (op3sz > 1) op3[1]		=	src[1];

#define	TEXTUREINFOS			*res		=	found;												\
								*op3		=	src[0];

#define	TEXTUREINFOV			*res		=	found;												\
								op3[0]		=	src[0];												\
								op3[1]		=	src[1];												\
								op3[2]		=	src[2];

#define	TEXTUREINFOM			*res		=	found;												\
								op3[0]		=	src[0];												\
								op3[1]		=	src[1];												\
								op3[2]		=	src[2];												\
								op3[3]		=	src[3];												\
								op3[4]		=	src[4];												\
								op3[5]		=	src[5];												\
								op3[6]		=	src[6];												\
								op3[7]		=	src[7];												\
								op3[8]		=	src[8];												\
								op3[9]		=	src[9];												\
								op3[10]		=	src[10];											\
								op3[11]		=	src[11];											\
								op3[12]		=	src[12];											\
								op3[13]		=	src[13];											\
								op3[14]		=	src[14];											\
								op3[15]		=	src[15];


#define	TEXTUREINFO_UPDATE(__r,__o2)	FUN4EXPR_UPDATE(__r,0,0,__o2)

#define	TEXTUREINFO_POST		plEnd();


#else

#undef	TEXTUREINFO_PRE
#undef	TEXTUREINFOF
#undef	TEXTUREINFOS
#undef	TEXTUREINFOV
#undef	TEXTUREINFOM
#undef	TEXTUREINFO_UPDATE
#undef	TEXTUREINFO_POST

#define	TEXTUREINFO_PRE(__t)
#define	TEXTUREINFOF
#define	TEXTUREINFOS
#define	TEXTUREINFOV
#define	TEXTUREINFOM
#define	TEXTUREINFO_UPDATE
#define	TEXTUREINFO_POST
#endif

DEFLINKFUNC(Textureinfo2			,"textureinfo"				,"f=SSC!",	0)
DEFLINKFUNC(Textureinfo3			,"textureinfo"				,"f=SSN!",	0)
DEFLINKFUNC(Textureinfo4			,"textureinfo"				,"f=SSP!",	0)
DEFFUNC(TextureinfoV				,"textureinfo"				,"f=SSV!"	,TEXTUREINFO_PRE(float *),TEXTUREINFOV,TEXTUREINFO_UPDATE(1,3),TEXTUREINFO_POST,0)
DEFFUNC(Textureinfo					,"textureinfo"				,"f=SSF!"	,TEXTUREINFO_PRE(float *),TEXTUREINFOF,TEXTUREINFO_UPDATE(1,op3sz),TEXTUREINFO_POST,0)
DEFFUNC(TextureinfoS				,"textureinfo"				,"f=SSS!"	,TEXTUREINFO_PRE(char **),TEXTUREINFOS,TEXTUREINFO_UPDATE(1,1),TEXTUREINFO_POST,0)
DEFFUNC(TextureinfoM				,"textureinfo"				,"f=SSM!"	,TEXTUREINFO_PRE(float *),TEXTUREINFOM,TEXTUREINFO_UPDATE(1,16),TEXTUREINFO_POST,0)


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// shadername	"s="
#define SHADERNAMEEXPR_PRE	char	**res;								\
							operand(0,res,char **);

#define SHADERNAMEEXPR		*res	=	(char *) currentShader->name;

DEFFUNC(ShaderName				,"shadername"					,"s="		,SHADERNAMEEXPR_PRE,SHADERNAMEEXPR,FUN1EXPR_UPDATE(1),NULL_EXPR,0)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// shadername	"s=s"
#ifndef INIT_SHADING
#define SHADERNAMESEXPR_PRE	char	**res,**op;								\
							operand(0,res,char **);							\
							operand(1,op,char **);

#define SHADERNAMESEXPR		*res	=	(char *) shaderName(*op);
#else
#undef SHADERNAMESEXPR_PRE
#undef SHADERNAMESEXPR
#define SHADERNAMESEXPR_PRE
#define SHADERNAMESEXPR
#endif

DEFFUNC(ShaderNames				,"shadername"					,"s=s"		,SHADERNAMESEXPR_PRE,SHADERNAMESEXPR,FUN2EXPR_UPDATE(1,1),NULL_EXPR,0)




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Texture - Environment - Shadow mapping macros
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// texture	"f=SFff"
#ifndef INIT_SHADING
#define	TEXTUREFEXPR_PRE		float			*res;															\
								const float		*s,*t;															\
								const float		*op2;															\
								/* Begin the parameter list */													\
								plBegin(CTextureLookup,5);														\
								/* Fetch the parameters as usual */												\
								operand(0,res,float *);															\
								operand(2,op2,const float *);													\
								operand(3,s,const float *);														\
								operand(4,t,const float *);														\
								/* Get the texture */															\
								CTexture	*tex;																\
								if ((tex = lookup->map) == NULL) {												\
									const char		**op1;														\
									operand(1,op1,const char **);												\
									osLock(CRenderer::shaderMutex);												\
									lookup->map = tex	=	CRenderer::getTexture(*op1);						\
									osUnlock(CRenderer::shaderMutex);											\
								}																				\
								int				i;																\
								float			*dsdu		=	(float *) ralloc(numVertices*4*sizeof(float),threadMemory);	\
								float			*dsdv		=	dsdu + numVertices;								\
								float			*dtdu		=	dsdv + numVertices;								\
								float			*dtdv		=	dtdu + numVertices;								\
								float			cs[4],ct[4];													\
								const float		swidth		=	(scratch->textureParams.width == 0 ? scratch->textureParams.swidth : scratch->textureParams.width);	\
								const float		twidth		=	(scratch->textureParams.width == 0 ? scratch->textureParams.twidth : scratch->textureParams.width);	\
								const float		*du			=	varying[VARIABLE_DU];							\
								const float		*dv			=	varying[VARIABLE_DV];							\
																												\
								scratch->textureParams.filter	=	lookup->filter;								\
																												\
								duFloat(dsdu,s);																\
								duFloat(dtdu,t);																\
								dvFloat(dsdv,s);																\
								dvFloat(dtdv,t);																\
																												\
								i	=	0;

#define	TEXTUREFEXPR			plReady();																		\
								cs[0]		=	s[i];															\
								cs[1]		=	s[i] + dsdu[i]*du[i]*swidth;									\
								cs[2]		=	s[i] + dsdv[i]*dv[i]*swidth;									\
								cs[3]		=	s[i] + (dsdu[i]*du[i] + dsdv[i]*dv[i])*swidth;					\
								ct[0]		=	t[i];															\
								ct[1]		=	t[i] + dtdu[i]*du[i]*twidth;									\
								ct[2]		=	t[i] + dtdv[i]*dv[i]*twidth;									\
								ct[3]		=	t[i] + (dtdu[i]*du[i] + dtdv[i]*dv[i])*twidth;					\
								vector	tmp;																	\
								tex->lookup4(tmp,cs,ct,this);													\
								res[i]		=	tmp[int(*op2)&3];

#define	TEXTUREFEXPR_UPDATE		++i;	plStep();

#define	TEXTUREFEXPR_POST		plEnd();
#else
#define	TEXTUREFEXPR_PRE
#define	TEXTUREFEXPR
#define	TEXTUREFEXPR_UPDATE
#define	TEXTUREFEXPR_POST
#endif

DEFFUNC(TextureFloat			,"texture"					,"f=SFff!"		,TEXTUREFEXPR_PRE,TEXTUREFEXPR,TEXTUREFEXPR_UPDATE,TEXTUREFEXPR_POST,PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_DU | PARAMETER_DV | PARAMETER_DERIVATIVE)





///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// texture	"c=SFff"
#ifndef INIT_SHADING

#define	TEXTURECEXPR			plReady();																		\
								cs[0]		=	s[i];															\
								cs[1]		=	s[i] + dsdu[i]*du[i]*swidth;											\
								cs[2]		=	s[i] + dsdv[i]*dv[i]*swidth;											\
								cs[3]		=	s[i] + (dsdu[i]*du[i] + dsdv[i]*dv[i])*swidth;								\
								ct[0]		=	t[i];															\
								ct[1]		=	t[i] + dtdu[i]*du[i]*twidth;											\
								ct[2]		=	t[i] + dtdv[i]*dv[i]*twidth;											\
								ct[3]		=	t[i] + (dtdu[i]*du[i] + dtdv[i]*dv[i])*twidth;								\
								tex->lookup4(res,cs,ct,this);

#define	TEXTURECEXPR_UPDATE		++i;	res	+=	3;	plStep();

#define	TEXTURECEXPR_POST		plEnd();

#else
#define	TEXTURECEXPR_PRE
#define	TEXTURECEXPR
#define	TEXTURECEXPR_UPDATE
#define	TEXTURECEXPR_POST
#endif

DEFFUNC(TextureColor			,"texture"					,"c=SFff!"		,TEXTUREFEXPR_PRE,TEXTURECEXPR,TEXTURECEXPR_UPDATE,TEXTURECEXPR_POST,PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_DU | PARAMETER_DV | PARAMETER_DERIVATIVE)

#undef	TEXTURECEXPR_PRE
#undef	TEXTURECEXPR
#undef	TEXTURECEXPR_UPDATE
#undef	TEXTURECEXPR_POST
#undef	TEXTUREFEXPR_PRE
#undef	TEXTUREFEXPR
#undef	TEXTUREFEXPR_UPDATE
#undef	TEXTUREFEXPR_POST


















///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// texture	"f=SFffffffff"
#ifndef INIT_SHADING
#define	TEXTUREFFULLEXPR_PRE	/* Begin the parameter list */													\
								plBegin(CTextureLookup,11);														\
								/* Fetch the parameters as usual */												\
								float			*res;															\
								const float		*op2,*op3,*op4,*op5,*op6,*op7,*op8,*op9,*op10;					\
								float			cs[4],ct[4];													\
								operand(0,res,float *);															\
								operand(2,op2,const float *);													\
								operand(3,op3,const float *);													\
								operand(4,op4,const float *);													\
								operand(5,op5,const float *);													\
								operand(6,op6,const float *);													\
								operand(7,op7,const float *);													\
								operand(8,op8,const float *);													\
								operand(9,op9,const float *);													\
								operand(10,op10,const float *);													\
								/* Get the texture */															\
								CTexture	*tex;																\
								if ((tex = lookup->map) == NULL) {												\
									const char		**op1;														\
									operand(1,op1,const char **);												\
									osLock(CRenderer::shaderMutex);												\
									lookup->map = tex	=	CRenderer::getTexture(*op1);						\
									osUnlock(CRenderer::shaderMutex);											\
								}																				\
								scratch->textureParams.filter	=	lookup->filter;
								

#define	TEXTUREFFULLEXPR		plReady();																		\
								cs[0]		=	*op3;															\
								cs[1]		=	*op5;															\
								cs[2]		=	*op7;															\
								cs[3]		=	*op9;															\
								ct[0]		=	*op4;															\
								ct[1]		=	*op6;															\
								ct[2]		=	*op8;															\
								ct[3]		=	*op10;															\
								vector	tmp;																	\
								tex->lookup4(tmp,cs,ct,this);													\
								*res		=	tmp[0];

#define	TEXTUREFFULLEXPR_UPDATE	++res;																			\
								++op3;																			\
								++op4;																			\
								++op5;																			\
								++op6;																			\
								++op7;																			\
								++op8;																			\
								++op9;																			\
								++op10;																			\
								plStep();


#define	TEXTUREFFULLEXPR_POST	plEnd();

#else
#define	TEXTUREFFULLEXPR_PRE
#define	TEXTUREFFULLEXPR
#define	TEXTUREFFULLEXPR_UPDATE
#define	TEXTUREFFULLEXPR_POST
#endif

DEFFUNC(TextureFloatFull			,"texture"				,"f=SFffffffff!"		,TEXTUREFFULLEXPR_PRE,TEXTUREFFULLEXPR,TEXTUREFFULLEXPR_UPDATE,TEXTUREFFULLEXPR_POST,0)







///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// texture	"c=SFffffffff"
#ifndef INIT_SHADING
#define	TEXTURECFULLEXPR		plReady();																		\
								cs[0]		=	*op3;															\
								cs[1]		=	*op5;															\
								cs[2]		=	*op7;															\
								cs[3]		=	*op9;															\
								ct[0]		=	*op4;															\
								ct[1]		=	*op6;															\
								ct[2]		=	*op8;															\
								ct[3]		=	*op10;															\
								tex->lookup4(res,cs,ct,this);

#define	TEXTURECFULLEXPR_UPDATE	res	+=	3;																		\
								++op3;																			\
								++op4;																			\
								++op5;																			\
								++op6;																			\
								++op7;																			\
								++op8;																			\
								++op9;																			\
								++op10;																			\
								plStep();


#define	TEXTURECFULLEXPR_POST	plEnd();

#else
#define	TEXTURECFULLEXPR_PRE
#define	TEXTURECFULLEXPR
#define	TEXTURECFULLEXPR_UPDATE
#define	TEXTURECFULLEXPR_POST
#endif

DEFFUNC(TextureColorFull			,"texture"				,"c=SFffffffff!"		,TEXTUREFFULLEXPR_PRE,TEXTURECFULLEXPR,TEXTURECFULLEXPR_UPDATE,TEXTURECFULLEXPR_POST,0)

#undef	TEXTURECFULLEXPR_PRE
#undef	TEXTURECFULLEXPR
#undef	TEXTURECFULLEXPR_UPDATE
#undef	TEXTURECFULLEXPR_POST
#undef	TEXTUREFFULLEXPR_PRE
#undef	TEXTUREFFULLEXPR
#undef	TEXTUREFFULLEXPR_UPDATE
#undef	TEXTUREFFULLEXPR_POST
















///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Environment / Shadow mapping macros
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// environment	"f=SFv"
#ifndef INIT_SHADING
#define	ENVIRONMENTEXPR_PRE(__name)																					\
								/* Begin the parameter list */														\
								plBegin(CEnvironmentLookup,4);														\
								float			*res;																\
								const char		**op1;																\
								const float		*op2;																\
								/* Fetch the parameters as usual */													\
								operand(0,res,float *);																\
								operand(1,op1,const char **);														\
								operand(2,op2,const float *);														\
								/* Get the texture */																\
								CEnvironment	*tex = NULL;														\
								if ((strcmp(*op1,"raytrace") != 0) && (strcmp(*op1,__name) != 0)) {					\
									if ((tex = lookup->map) == NULL) {												\
										osLock(CRenderer::shaderMutex);												\
										lookup->map = tex	=	CRenderer::getEnvironment(*op1);					\
										osUnlock(CRenderer::shaderMutex);											\
									}																				\
								}																					\
								CTraceLocation	*rays;																\
								int				numRays;															\
								const float		*P,*N;																\
								float			*dPdu,*dPdv;														\
								if (tex == NULL) {																	\
									rays	=	(CTraceLocation *) ralloc(currentShadingState->numVertices*sizeof(CTraceLocation),threadMemory);	\
									P		=	varying[VARIABLE_P];												\
									N		=	varying[VARIABLE_N];												\
									dPdu	=	varying[VARIABLE_DPDU];												\
									dPdv	=	varying[VARIABLE_DPDV];												\
									numRays	=	0;																	\
								}																					\
																													\
								const float		*D;																	\
								float			*dDdu		=	(float *) ralloc(numVertices*6*sizeof(float),threadMemory);	\
								float			*dDdv		=	dDdu + numVertices*3;								\
								const float		*du			=	varying[VARIABLE_DU];								\
								const float		*dv			=	varying[VARIABLE_DV];								\
								const float		*time		=	varying[VARIABLE_TIME];								\
								const float		swidth		=	(scratch->textureParams.width == 0 ? scratch->textureParams.swidth : scratch->textureParams.width);	\
								const float		twidth		=	(scratch->textureParams.width == 0 ? scratch->textureParams.twidth : scratch->textureParams.width);	\
								operand(3,D,const float *);															\
																													\
								scratch->textureParams.filter				=	lookup->filter;						\
																													\
								duVector(dDdu,D);																	\
								dvVector(dDdv,D);

#define	ENVIRONMENTEXPR(__float)																					\
								plReady();																			\
								if (tex == NULL) {																	\
									rays->res	=	res;															\
									movvv(rays->D,D);																\
									mulvf(rays->dDdu,dDdu,(*du)*swidth);											\
									mulvf(rays->dDdv,dDdv,(*dv)*twidth);											\
									movvv(rays->P,P);																\
									mulvf(rays->dPdu,dPdu,(*du)*swidth);											\
									mulvf(rays->dPdv,dPdv,(*dv)*twidth);											\
									rays->coneAngle		=	max(scratch->traceParams.coneAngle,scratch->textureParams.blur);	\
									rays->numSamples	=	(int) scratch->traceParams.samples;						\
									rays->bias			=	scratch->traceParams.bias;								\
									rays->sampleBase	=	scratch->traceParams.sampleBase;						\
									rays->maxDist		=	scratch->traceParams.maxDist;							\
									rays->time			=	*time;													\
									++rays;																			\
									++numRays;																		\
								} else {																			\
									vector	D0,D1,D2,D3;															\
									mulvf(dDdu,(*du)*swidth*0.5f);													\
									mulvf(dDdv,(*dv)*twidth*0.5f);													\
									subvv(D0,D,dDdu); subvv(D0,dDdv);												\
									addvv(D1,D,dDdu); subvv(D1,dDdv);												\
									subvv(D2,D,dDdu); addvv(D2,dDdv);												\
									addvv(D3,D,dDdu); addvv(D3,dDdv);												\
									if (__float) {																	\
										vector	color;																\
										tex->lookup(color,D0,D1,D2,D3,this);										\
										*res	=	color[0];														\
									} else {																		\
										tex->lookup(res,D0,D1,D2,D3,this);											\
									}																				\
								}

#define ENVIRONMENTEXPR_UPDATE(__n)																					\
								res			+=	__n;																\
								D			+=	3;																	\
								dDdu		+=	3;																	\
								dDdv		+=	3;																	\
								++du;																				\
								++dv;																				\
								++time;																				\
								if (tex == NULL) {																	\
									P		+=	3;																	\
									N		+=	3;																	\
									dPdu	+=	3;																	\
									dPdv	+=	3;																	\
								}																					\
								plStep();



#define ENVIRONMENTEXPR_POST(__float)																				\
								if ((tex == NULL) && (numRays > 0))	{												\
									rays	-=	numRays;															\
									traceReflection(numRays,rays,FALSE);											\
									if (__float) {																	\
										for (int i=numRays;i>0;--i,++rays) {										\
											*(rays->res)	=	(rays->C[0] + rays->C[1] + rays->C[2]) / 3.0f;		\
										}																			\
									} else {																		\
										for (int i=numRays;i>0;--i,++rays) movvv(rays->res,rays->C);				\
									}																				\
								}																					\
								plEnd();
								
#else
#define	ENVIRONMENTEXPR_PRE
#define	ENVIRONMENTEXPR
#define	ENVIRONMENTEXPR_UPDATE
#define	ENVIRONMENTEXPR_POST(__float)
#endif

DEFSHORTFUNC(EnvironmentFloat			,"environment"				,"f=SFv!"		,ENVIRONMENTEXPR_PRE("reflection"),ENVIRONMENTEXPR(TRUE),ENVIRONMENTEXPR_UPDATE(1),ENVIRONMENTEXPR_POST(TRUE),PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_DU | PARAMETER_DV | PARAMETER_TIME | PARAMETER_DERIVATIVE)
DEFSHORTFUNC(EnvironmentColor			,"environment"				,"c=SFv!"		,ENVIRONMENTEXPR_PRE("reflection"),ENVIRONMENTEXPR(FALSE),ENVIRONMENTEXPR_UPDATE(3),ENVIRONMENTEXPR_POST(FALSE),PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_DU | PARAMETER_DV | PARAMETER_TIME | PARAMETER_DERIVATIVE)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// shadow	"f=Sfv"
#ifndef INIT_SHADING


// Note: we are swapping dDdu and dDdv with dPdu and dPdv here, because
// the ENVIRONMENT_PRE macro always calculates the dD differentials.
// It is also very impartant that we supply dPdu and dPdv so the ray differentials
// are correct or otherwise we waste time overtesselating

#define	SHADOWEXPR_PRE			ENVIRONMENTEXPR_PRE("shadow");														\
								const float	*L	=	varying[VARIABLE_L];											\
								if (tex == NULL) {																	\
									float *tmp	= 	(float*) ralloc(currentShadingState->numVertices*sizeof(float)*9,threadMemory);	\
									dPdu		=	tmp		+ currentShadingState->numVertices*3;					\
									dPdv		=	dPdu	+ currentShadingState->numVertices*3;					\
									for(int v=0;v<currentShadingState->numVertices*3;v+=3) {						\
										subvv(tmp+v,D+v,L+v);														\
									}																				\
									duVector(dPdu,tmp);																\
									dvVector(dPdv,tmp);																\
								}


#define	SHADOWEXPR(__float)		plReady();																			\
								if (tex == NULL) {																	\
									rays->res	=	res;															\
									movvv(rays->P,D);																\
									mulvf(rays->dPdu,dDdu,(*du)*swidth);											\
									mulvf(rays->dPdv,dDdv,(*dv)*twidth);											\
									subvv(rays->D,D,L);																\
									mulvf(rays->dDdu,dPdu,(*du)*swidth);											\
									mulvf(rays->dDdv,dPdv,(*dv)*twidth);											\
									rays->coneAngle		=	max(scratch->traceParams.coneAngle,scratch->textureParams.blur);	\
									rays->sampleBase	=	scratch->traceParams.sampleBase;						\
									rays->numSamples	=	(int) scratch->traceParams.samples;						\
									rays->bias			=	scratch->traceParams.bias;								\
									rays->maxDist		=	scratch->traceParams.maxDist;							\
									rays->time			=	*time;													\
									++rays;																			\
									++numRays;																		\
								} else {																			\
									vector	D0,D1,D2,D3;															\
									mulvf(dDdu,(*du)*swidth*0.5f);													\
									mulvf(dDdv,(*dv)*twidth*0.5f);													\
									subvv(D0,D,dDdu); subvv(D0,dDdv);												\
									addvv(D1,D,dDdu); subvv(D1,dDdv);												\
									subvv(D2,D,dDdu); addvv(D2,dDdv);												\
									addvv(D3,D,dDdu); addvv(D3,dDdv);												\
									if (__float) {																	\
										vector	color;																\
										tex->lookup(color,D0,D1,D2,D3,this);										\
										*res	=	(color[0] + color[1] + color[2])/3.0f;							\
									} else {																		\
										tex->lookup(res,D0,D1,D2,D3,this);											\
									}																				\
								}

#define SHADOWEXPR_UPDATE(__n)	res			+=__n;																	\
								D			+=	3;																	\
								dDdu		+=	3;																	\
								dDdv		+=	3;																	\
								++du;																				\
								++dv;																				\
								++time;																				\
								L			+=	3;																	\
								if (tex == NULL) {																	\
									dPdu	+=	3;																	\
									dPdv	+=	3;																	\
								}																					\
								plStep();


#define SHADOWEXPR_POST(__float)																					\
							if ((tex == NULL) && (numRays > 0))	{													\
								rays	-=	numRays;																\
								traceTransmission(numRays,rays,FALSE);												\
								if (__float) {																		\
									for (int i=numRays;i>0;--i,++rays) {											\
										*(rays->res)	=	1 - (rays->C[0] + rays->C[1] + rays->C[2]) / 3.0f;		\
									}																				\
								} else {																			\
									for (int i=numRays;i>0;--i,++rays) {											\
										res		=	rays->res;														\
										res[0]	=	1 - rays->C[0];													\
										res[1]	=	1 - rays->C[1];													\
										res[2]	=	1 - rays->C[2];													\
									}																				\
								}																					\
							}																						\
							plEnd();

#else
#define	SHADOWEXPR_PRE
#define	SHADOWEXPR
#define	SHADOWEXPR_UPDATE
#define	SHADOWEXPR_POST(__float)
#endif

DEFSHORTFUNC(ShadowFloat			,"shadow"				,"f=SFp!"		,SHADOWEXPR_PRE,SHADOWEXPR(TRUE),SHADOWEXPR_UPDATE(1),SHADOWEXPR_POST(TRUE),PARAMETER_DU | PARAMETER_DV | PARAMETER_TIME | PARAMETER_DERIVATIVE)
DEFSHORTFUNC(ShadowColor			,"shadow"				,"c=SFp!"		,SHADOWEXPR_PRE,SHADOWEXPR(FALSE),SHADOWEXPR_UPDATE(3),SHADOWEXPR_POST(FALSE),PARAMETER_DU | PARAMETER_DV | PARAMETER_TIME | PARAMETER_DERIVATIVE)

#undef	ENVIRONMENTEXPR_PRE
#undef	ENVIRONMENTEXPR
#undef	ENVIRONMENTEXPR_UPDATE
#undef	ENVIRONMENTEXPR_POST

#undef	SHADOWEXPR_PRE
#undef	SHADOWEXPR
#undef	SHADOWEXPR_UPDATE
#undef	SHADOWEXPR_POST


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// filterstep "f=ff!"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef INIT_SHADING
#define	FILTERSTEP2EXPR_PRE		FUN3EXPR_PRE																		\
								plBegin(CFilterLookup,3);															\
								float			*dsdu	=	(float *) ralloc(numVertices*2*sizeof(float),threadMemory);	\
								float			*dsdv	=	dsdu + numVertices;										\
								float			*fwidth	=	dsdu;													\
								const float		*du		=	varying[VARIABLE_DU];									\
								const float		*dv		=	varying[VARIABLE_DV];									\
								const float		*s		=	op2;													\
																													\
								duFloat(dsdu,s);																	\
								dvFloat(dsdv,s);																	\
								for (int i=0;i<numVertices;++i) {													\
									dsdu[i]		=	fabs(dsdu[i]*du[i]);											\
									dsdv[i]		=	fabs(dsdv[i]*dv[i]);											\
									fwidth[i]	=	scratch->textureParams.width*max(dsdu[i] + dsdv[i],C_EPSILON);	\
								}

#define	FILTERSTEP2EXPR			plReady();																			\
								*res	=	lookup->filter(*op2,*op1,fwidth[0]);


#define	FILTERSTEP2EXPR_UPDATE	plStep();																			\
								FUN3EXPR_UPDATE(1,1,1)																\
								++fwidth;

#else
#define	FILTERSTEP2EXPR_PRE
#define	FILTERSTEP2EXPR
#define	FILTERSTEP2EXPR_UPDATE
#endif

DEFFUNC(FilterStep2			,"filterstep"				,"f=ff!"		,FILTERSTEP2EXPR_PRE,FILTERSTEP2EXPR,FUN3EXPR_UPDATE(1,1,1),NULL_EXPR,PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_DU | PARAMETER_DV | PARAMETER_DERIVATIVE)


#undef	FILTERSTEP2EXPR_PRE
#undef	FILTERSTEP2EXPR
#undef	FILTERSTEP2EXPR_UPDATE

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// filterstep "f=fff!"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef INIT_SHADING
#define	FILTERSTEP3EXPR_PRE	FUN4EXPR_PRE																		\
							plBegin(CFilterLookup,4);

#define	FILTERSTEP3EXPR		plReady();																			\
							*res	=	lookup->filter(0.5f*(*op2+*op3),*op1,*op3-*op2);


#define	FILTERSTEP3EXPR_UPDATE	plStep();	FUN4EXPR_UPDATE(1,1,1,1)
#else
#define	FILTERSTEP3EXPR_PRE
#define	FILTERSTEP3EXPR
#define	FILTERSTEP3EXPR_UPDATE
#endif

DEFFUNC(FilterStep3			,"filterstep"				,"f=fff!"		,FILTERSTEP3EXPR_PRE,FILTERSTEP3EXPR,FUN4EXPR_UPDATE(1,1,1,1),NULL_EXPR,0)


#undef	FILTERSTEP3EXPR_PRE
#undef	FILTERSTEP3EXPR
#undef	FILTERSTEP3EXPR_UPDATE


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// bake3d	"f=SSpn!"
#ifndef INIT_SHADING
#define	BAKE3DEXPR_PRE			plBegin(CTexture3dLookup,5);													\
								CTexture3d	*tex;																\
								if ((tex = lookup->map) == NULL) {												\
									const float		*from,*to;													\
									findCoordinateSystem(scratch->texture3dParams.coordsys,from,to);			\
									const char		**op1,**op2;												\
									operand(1,op1,const char **);												\
									operand(2,op2,const char **);												\
									osLock(CRenderer::shaderMutex);												\
									lookup->map = tex	=	CRenderer::getTexture3d(*op1,TRUE,*op2,from,to);	\
									osUnlock(CRenderer::shaderMutex);											\
									tex->resolve(lookup->numChannels,lookup->channelName,lookup->channelEntry,lookup->channelSize);	\
								}																				\
								float			*res;															\
								const float		*op3,*op4;														\
								operand(0,res,float *);															\
								operand(3,op3,const float *);													\
								operand(4,op4,const float *);													\
								int				curU=0,curV=0;													\
								const int		uVerts		=	currentShadingState->numUvertices;				\
								const int		vVerts		=	currentShadingState->numVvertices;				\
								const int		doInterp	=	((scratch->texture3dParams.interpolate == 1.0f) && currentShadingState->numVertices == currentShadingState->numRealVertices);	\
								float			*dest		=	(float *) ralloc(tex->dataSize*sizeof(float),threadMemory);	\
								const float		**channelValues = (const float **) ralloc(lookup->numChannels*sizeof(const float *),threadMemory);	\
								float			*dPdu		=	(float *) ralloc(numVertices*6*sizeof(float),threadMemory);	\
								float			*dPdv		=	dPdu + numVertices*3;							\
								duVector(dPdu,op3);																\
								dvVector(dPdv,op3);																\
								const float		*du			=	varying[VARIABLE_DU];							\
								const float		*dv			=	varying[VARIABLE_DV];							\
																												\
								for (int channel=0;channel<lookup->numChannels;++channel) {						\
									operand(lookup->channelIndex[channel],channelValues[channel],const float *);\
								}																				\
																												\
								vector	P;																		\
								float	radius;

#define	BAKE3DEXPR				plReady();																		\
								mulvf(dPdu,*du);																\
								mulvf(dPdv,*dv);																\
								if (scratch->texture3dParams.radius > 0) {										\
									radius	=	scratch->texture3dParams.radius*scratch->texture3dParams.radiusScale;							\
								} else {																		\
									radius	=	(lengthv(dPdu) + lengthv(dPdv))*0.5f*scratch->texture3dParams.radiusScale;		\
								}																				\
																												\
								texture3Dflatten(dest,lookup->numChannels,channelValues,lookup->channelEntry,lookup->channelSize);	\
								if (doInterp == FALSE) {														\
									movvv(P,op3);																\
									tex->store(dest,P,op4,radius);												\
								} else if ((curU < uVerts-1) && (curV < vVerts-1)) {							\
									/* skip the end - do not double-bake seams */								\
									P[0]	=	(dPdu[0] + dPdv[0])*0.5f + op3[0];								\
									P[1]	=	(dPdu[1] + dPdv[1])*0.5f + op3[1];								\
									P[2]	=	(dPdu[2] + dPdv[2])*0.5f + op3[2];								\
									tex->store(dest,P,op4,radius);												\
								}																				\
								*res		=	1;

#define	BAKE3DEXPR_UPDATE		++res;																			\
								op3		+=	3;																	\
								op4		+=	3;																	\
								dPdu	+=	3;																	\
								dPdv	+=	3;																	\
								++du;	++dv;																	\
								++curU;																			\
								plStep();																		\
								if (curU == uVerts) { curV++; curU = 0; }										\
								for (int channel=0;channel<lookup->numChannels;++channel) {						\
									channelValues[channel]	+=	lookup->channelSize[channel];					\
								}

#define	BAKE3DEXPR_POST			plEnd();

#else
#define	BAKE3DEXPR_PRE
#define	BAKE3DEXPR
#define	BAKE3DEXPR_UPDATE
#define	BAKE3DEXPR_POST
#endif

DEFSHORTFUNC(Bake3d			,"bake3d"					,"f=SSpn!"		,BAKE3DEXPR_PRE,BAKE3DEXPR,BAKE3DEXPR_UPDATE,BAKE3DEXPR_POST,PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_DU | PARAMETER_DV | PARAMETER_DERIVATIVE)

#undef	BAKE3DEXPR_PRE
#undef	BAKE3DEXPR
#undef	BAKE3DEXPR_UPDATE
#undef	BAKE3DEXPR_POST



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// texture3d	"f=Spn!"
#ifndef INIT_SHADING
#define	TEXTURE3DEXPR_PRE		plBegin(CTexture3dLookup,4);													\
								CTexture3d	*tex;																\
								if ((tex = lookup->map) == NULL) {												\
									const float			*from,*to;												\
									findCoordinateSystem(scratch->texture3dParams.coordsys,from,to);			\
									const char			**op1;													\
									operand(1,op1,const char **);												\
									osLock(CRenderer::shaderMutex);												\
									lookup->map	=	tex	=	CRenderer::getTexture3d(*op1,FALSE,NULL,from,to);	\
									osUnlock(CRenderer::shaderMutex);											\
									tex->resolve(lookup->numChannels,lookup->channelName,lookup->channelEntry,lookup->channelSize);	\
								}																				\
								float				*res;														\
								const float			*op2,*op3;													\
								operand(0,res,float *);															\
								operand(2,op2,const float *);													\
								operand(3,op3,const float *);													\
								float			*dest		=	(float *) ralloc(tex->dataSize*sizeof(float),threadMemory);	\
								float			**channelValues = (float **) ralloc(lookup->numChannels*sizeof(float*),threadMemory);	\
								float			*dPdu		=	(float *) ralloc(numVertices*6*sizeof(float),threadMemory);	\
								float			*dPdv		=	dPdu + numVertices*3;							\
								duVector(dPdu,op2);																\
								dvVector(dPdv,op2);																\
								const float		*du			=	varying[VARIABLE_DU];							\
								const float		*dv			=	varying[VARIABLE_DV];							\
																												\
								for (int channel=0;channel<lookup->numChannels;++channel) {						\
									operand(lookup->channelIndex[channel],channelValues[channel],float *);		\
								} 

#define	TEXTURE3DEXPR			plReady();																		\
								float radius;																	\
								mulvf(dPdu,*du);																\
								mulvf(dPdv,*dv);																\
								if (scratch->texture3dParams.radius > 0) {										\
									radius	=	scratch->texture3dParams.radius*scratch->texture3dParams.radiusScale;				\
								} else {																		\
									radius	=	(lengthv(dPdu) + lengthv(dPdv))*0.5f*scratch->texture3dParams.radiusScale;			\
								}																				\
								tex->lookup(dest,op2,op3,radius);												\
								texture3Dunpack(dest,lookup->numChannels,channelValues,lookup->channelEntry,lookup->channelSize);	\
								*res		=	1;

#define	TEXTURE3DEXPR_UPDATE	++res;																			\
								op2		+=	3;																	\
								op3		+=	3;																	\
								dPdu	+=	3;																	\
								dPdv	+=	3;																	\
								++du;	++dv;																	\
								plStep();																		\
								for (int channel=0;channel<lookup->numChannels;++channel) {						\
									channelValues[channel]	+=	lookup->channelSize[channel];					\
								}

#define	TEXTURE3DEXPR_POST		plEnd();
#else
#define	TEXTURE3DEXPR_PRE
#define	TEXTURE3DEXPR
#define	TEXTURE3DEXPR_UPDATE
#define	TEXTURE3DEXPR_POST
#endif

DEFFUNC(Texture3d			,"texture3d"					,"f=Spn!"		,TEXTURE3DEXPR_PRE,TEXTURE3DEXPR,TEXTURE3DEXPR_UPDATE,TEXTURE3DEXPR_POST,PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_DU | PARAMETER_DV | PARAMETER_DERIVATIVE)

#undef	TEXTURE3DEXPR_PRE
#undef	TEXTURE3DEXPR
#undef	TEXTURE3DEXPR_UPDATE
#undef	TEXTURE3DEXPR_POST


///////////////////////////////////////////////////
//
//	FIXME : missing functions :
//	bump


#include "giFunctions.h"

