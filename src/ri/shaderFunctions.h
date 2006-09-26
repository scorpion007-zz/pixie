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
								
#define	FACEFORWARDEXPR			if (dotvv(&op1->real,Ng) > 0) {						\
									if (dotvv(&op2->real,Ng) > 0)					\
										mulvf(&res->real,&op1->real,-1);			\
									else											\
										movvv(&res->real,&op1->real);				\
								} else {											\
									if (dotvv(&op2->real,Ng) > 0)					\
										movvv(&res->real,&op1->real);				\
									else											\
										mulvf(&res->real,&op1->real,-1);			\
								}


#define	FACEFORWARDEXPR_UPDATE	FUN3EXPR_UPDATE(3,3,3);								\
								Ng		+=	3;

DEFFUNC(FaceForward		,"faceforward"			,"v=vv"	,FACEFORWARDEXPR_PRE,FACEFORWARDEXPR,FACEFORWARDEXPR_UPDATE,NULL_EXPR,PARAMETER_NG)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// faceforward "v=vvv"
#define	FACEFORWARD2EXPR		if (dotvv(&op1->real,&op3->real) > 0) {				\
									if (dotvv(&op2->real,&op3->real) > 0)			\
										mulvf(&res->real,&op1->real,-1);			\
									else											\
										movvv(&res->real,&op1->real);				\
								} else {											\
									if (dotvv(&op2->real,&op3->real) > 0)			\
										movvv(&res->real,&op1->real);				\
									else											\
										mulvf(&res->real,&op1->real,-1);			\
								}


DEFFUNC(FaceForward3		,"faceforward"		,"v=vvv",FUN4EXPR_PRE,FACEFORWARD2EXPR,FUN4EXPR_UPDATE(3,3,3,3),NULL_EXPR,0)




// The following macros are used to evaluate u and v derivatives using central differencing




		


									
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// du "f=f"
#ifndef INIT_SHADING
#define	DUFEXPR_PRE				FUN2EXPR_PRE																		\
								duFloat((float *) res,(float *) op);
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
								duVector((float *) res,(float *) op);

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
								dvFloat((float *) res,(float *) op);
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
								dvVector((float *) res,(float *) op);
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
								float	*duTop		=	(float *) ralloc(numVertices*sizeof(float)*4);		\
								float	*duBottom	=	duTop + numVertices;								\
								float	*dvTop		=	duBottom + numVertices;								\
								float	*dvBottom	=	dvTop + numVertices;								\
								duFloat(duTop,		(float *) op1);											\
								duFloat(duBottom,	(float *) op2);											\
								dvFloat(dvTop,		(float *) op1);											\
								dvFloat(dvBottom,	(float *) op2);

#define	DERIVFEXPR				if (duBottom[0] != 0) {														\
									res[0].real	=	duTop[0] / duBottom[0];									\
								} else {																	\
									res[0].real	=	0;														\
								}																			\
																											\
								if (dvBottom[0] != 0) {														\
									res[0].real	+=	dvTop[0] / dvBottom[0];									\
								}



#define	DERIVFEXPR_UPDATE		res++;																		\
								duTop++;																	\
								duBottom++;																	\
								dvTop++;																	\
								dvBottom++;

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
								float	*duTop		=	(float *) ralloc(numVertices*sizeof(float)*8);		\
								float	*duBottom	=	duTop + numVertices*3;								\
								float	*dvTop		=	duBottom + numVertices;								\
								float	*dvBottom	=	dvTop + numVertices*3;								\
								duVector(duTop,		(float *) op1);											\
								duFloat(duBottom,	(float *) op2);											\
								dvVector(dvTop,		(float *) op1);											\
								dvFloat(dvBottom,	(float *) op2);

#define	DERIVVEXPR				if (duBottom[0] != 0) {														\
									res[0].real	=	duTop[0] / duBottom[0];									\
									res[1].real	=	duTop[1] / duBottom[0];									\
									res[2].real	=	duTop[2] / duBottom[0];									\
								} else {																	\
									res[0].real	=	0;														\
									res[1].real	=	0;														\
									res[2].real	=	0;														\
								}																			\
																											\
								if (dvBottom[0] != 0) {														\
									res[0].real	+=	dvTop[0] / dvBottom[0];									\
									res[1].real	+=	dvTop[1] / dvBottom[0];									\
									res[2].real	+=	dvTop[2] / dvBottom[0];									\
								}


#define	DERIVVEXPR_UPDATE		res			+=	3;															\
								duTop		+=	3;															\
								dvTop		+=	3;															\
								duBottom++;																	\
								dvBottom++;

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
								float	*dPdu	=	(float *) ralloc(numVertices*6*sizeof(float));			\
								float	*dPdv	=	dPdu + numVertices*3;									\
								vector	tmp;																\
								duVector(dPdu,(float *) op);												\
								dvVector(dPdv,(float *) op);
								

#define	AREAEXPR				mulvf(dPdu,du[0]);															\
								mulvf(dPdv,dv[0]);															\
								crossvv(tmp,dPdu,dPdv);														\
								res->real	=	lengthv(tmp);

#define	AREAEXPR_UPDATE			res++;																		\
								dPdu	+=	3;																\
								dPdv	+=	3;																\
								du++;																		\
								dv++;
#else
#define	AREAEXPR_PRE
#define	AREAEXPR
#define	AREAEXPR_UPDATE
#endif

DEFFUNC(Area		,"area"			,"f=p"	,AREAEXPR_PRE,AREAEXPR,AREAEXPR_UPDATE,NULL_EXPR,PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_DU | PARAMETER_DV | PARAMETER_DERIVATIVE)

#undef	AREAEXPR_PRE
#undef	AREAEXPR
#undef	AREAEXPR_UPDATE


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// calculatenormal "p=p"
#ifndef INIT_SHADING

#define	CALCULATENORMALEXPR_PRE		FUN2EXPR_PRE																\
									float	*dPdu	=	(float *) ralloc(numVertices*6*sizeof(float));			\
									float	*dPdv	=	dPdu + numVertices*3;									\
									float	mult	=	((currentShadingState->currentObject->attributes->flags & ATTRIBUTES_FLAGS_INSIDE) ? (float) -1 : (float) 1);	\
									duVector(dPdu,(float *) op);												\
									dvVector(dPdv,(float *) op);

#define	CALCULATENORMALEXPR			crossvv((float *) res,dPdu,dPdv);											\
									mulvf((float *) res,mult);

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
#define	NOISE1D1EXPR				res->real	=	FUNCTION(op->real);
#define	NOISE1D2EXPR				res->real	=	FUNCTION(op1->real,op2->real);
#define	NOISE1D3EXPR				res->real	=	FUNCTION(&op->real);
#define	NOISE1D4EXPR				res->real	=	FUNCTION(&op1->real,op2->real);

#define	NOISE3D1EXPR				FUNCTION(&res->real,op->real);
#define	NOISE3D2EXPR				FUNCTION(&res->real,op1->real,op2->real);
#define	NOISE3D3EXPR				FUNCTION(&res->real,&op->real);
#define	NOISE3D4EXPR				FUNCTION(&res->real,&op1->real,op2->real);

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


#define	PNOISE1D1EXPR				res->real	=	FUNCTION(op1->real,op2->real);
#define	PNOISE1D2EXPR				res->real	=	FUNCTION(op1->real,op2->real,op3->real,op4->real);
#define	PNOISE1D3EXPR				res->real	=	FUNCTION(&op1->real,&op2->real);
#define	PNOISE1D4EXPR				res->real	=	FUNCTION(&op1->real,op2->real,&op3->real,op4->real);

#define	PNOISE3D1EXPR				FUNCTION(&res->real,op1->real,op2->real);
#define	PNOISE3D2EXPR				FUNCTION(&res->real,op1->real,op2->real,op3->real,op4->real);
#define	PNOISE3D3EXPR				FUNCTION(&res->real,&op1->real,&op2->real);
#define	PNOISE3D4EXPR				FUNCTION(&res->real,&op1->real,op2->real,&op3->real,op4->real);

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
#define	CTRANSFORMEXPR_PRE	matrix				*from,*to;											\
							ECoordinateSystem	cSystem;											\
							FUN3EXPR_PRE															\
							findCoordinateSystem(op1->string,from,to,cSystem);
							
#define	CTRANSFORMEXPR		convertColorTo(&res->real,&op2->real,cSystem);

DEFFUNC(CTransform		,"ctransform"			,"c=Sc"	,CTRANSFORMEXPR_PRE,CTRANSFORMEXPR,FUN3EXPR_UPDATE(3,0,3),NULL_EXPR,0)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ctransform "c=SSc"
#define	CTRANSFORMSEXPR_PRE	matrix				*from,*to;											\
							vector				vtmp;												\
							ECoordinateSystem	cSystemFrom,cSystemTo;								\
							FUN4EXPR_PRE															\
							findCoordinateSystem(op1->string,from,to,cSystemFrom);					\
							findCoordinateSystem(op2->string,from,to,cSystemTo);

#define CTRANSFORMSEXPR		convertColorFrom(vtmp,&op3->real,cSystemFrom);							\
							convertColorTo(&res->real,vtmp,cSystemTo);


DEFFUNC(CTransforms		,"ctransform"			,"c=SSc"	,CTRANSFORMSEXPR_PRE,CTRANSFORMSEXPR,FUN4EXPR_UPDATE(3,0,0,3),NULL_EXPR,0)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// transform "p=Sp
#define	TRANSFORM1EXPR_PRE	ECoordinateSystem	cSystem;											\
							matrix				*from,*to;											\
							FUN3EXPR_PRE;															\
							findCoordinateSystem(op1->string,from,to,cSystem);


#define	TRANSFORM1EXPR		mulmp(&res->real,to[0],&op2->real);


#define	TRANSFORM1EXPR_UPDATE	FUN3EXPR_UPDATE(3,0,3);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// transform "p=SSp"
#define	TRANSFORM2EXPR_PRE	ECoordinateSystem	cSystemFrom,cSystemTo;											\
							matrix				*from1,*to1,*from2,*to2;										\
							vector				vtmp;															\
							FUN4EXPR_PRE;																		\
							findCoordinateSystem(op1->string,from1,to1,cSystemFrom);							\
							findCoordinateSystem(op2->string,from2,to2,cSystemTo);

#define	TRANSFORM2EXPR		mulmp(vtmp,from1[0],&op3->real);													\
							mulmp(&res->real,to2[0],vtmp);

#define	TRANSFORM2EXPR_UPDATE	FUN4EXPR_UPDATE(3,0,0,3);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// transform "p=mp"
#define	TRANSFORM3EXPR		mulmp(&res->real,&op1->real,&op2->real);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// transform "p=Smp"
#define	TRANSFORM4EXPR_PRE	ECoordinateSystem	cSystem;											\
							matrix				*from,*to;											\
							vector				vtmp;												\
							FUN4EXPR_PRE;															\
							findCoordinateSystem(op1->string,from,to,cSystem);

#define	TRANSFORM4EXPR		mulmp(vtmp,from[0],&op3->real);											\
							mulmp(&res->real,&op2->real,vtmp);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// vtransform "p=Sp
#define	VTRANSFORM1EXPR_PRE	ECoordinateSystem	cSystem;											\
							matrix				*from,*to;											\
							FUN3EXPR_PRE;															\
							findCoordinateSystem(op1->string,from,to,cSystem);

#define	VTRANSFORM1EXPR		mulmv(&res->real,to[0],&op2->real);


#define	VTRANSFORM1EXPR_UPDATE	FUN3EXPR_UPDATE(3,0,3);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ntransform "p=Sp
#define	NTRANSFORM1EXPR_PRE	ECoordinateSystem	cSystem;											\
							matrix				*from,*to;											\
							FUN3EXPR_PRE;															\
							findCoordinateSystem(op1->string,from,to,cSystem);						\

#define	NTRANSFORM1EXPR		mulmn(&res->real,from[0],&op2->real);

#define	NTRANSFORM1EXPR_UPDATE	FUN3EXPR_UPDATE(3,0,3);												\


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// vtransform "p=SSp"
#define VTRANSFORM2EXPR_PRE	ECoordinateSystem	cSystemFrom,cSystemTo;								\
							matrix				*from1,*to1,*from2,*to2;							\
							vector				vtmp;												\
							FUN4EXPR_PRE;															\
							findCoordinateSystem(op1->string,from1,to1,cSystemFrom);				\
							findCoordinateSystem(op2->string,from2,to2,cSystemTo);

#define	VTRANSFORM2EXPR		mulmv(vtmp,from1[0],&op3->real);										\
							mulmv(&res->real,to2[0],vtmp);

#define VTRANSFORM2EXPR_UPDATE	FUN4EXPR_UPDATE(3,0,0,3);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ntransform "p=SSp"
#define NTRANSFORM2EXPR_PRE	ECoordinateSystem	cSystemFrom,cSystemTo;								\
							matrix				*from1,*to1,*from2,*to2;							\
							vector				vtmp;												\
							FUN4EXPR_PRE;															\
							findCoordinateSystem(op1->string,from1,to1,cSystemFrom);				\
							findCoordinateSystem(op2->string,from2,to2,cSystemTo);					\

#define	NTRANSFORM2EXPR		mulmn(vtmp,to1[0],&op3->real);											\
							mulmn(&res->real,from2[0],vtmp);

#define NTRANSFORM2EXPR_UPDATE	FUN4EXPR_UPDATE(3,0,0,3);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// vtransform "p=mp"
#define	VTRANSFORM3EXPR		mulmv(&res->real,&op1->real,&op2->real);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ntransform "p=mp"
#define	NTRANSFORM3EXPR		matrix	mtmp;							\
							invertm(mtmp,&op1->real);				\
							mulmn(&res->real,mtmp,&op2->real);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// vtransform "p=Smp"
#define	VTRANSFORM4EXPR_PRE	ECoordinateSystem	cSystem;												\
							matrix				*from,*to;												\
							vector				vtmp;													\
							FUN4EXPR_PRE;																\
							findCoordinateSystem(op1->string,from,to,cSystem);

#define	VTRANSFORM4EXPR		mulmv(vtmp,from[0],&op3->real);												\
							mulmv(&res->real,&op2->real,vtmp);

#define	VTRANSFORM4EXPR_UPDATE	FUN4EXPR_UPDATE(3,0,16,3);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ntransform "p=Smp"
#define	NTRANSFORM4EXPR_PRE	ECoordinateSystem	cSystem;												\
							matrix				*from,*to;												\
							matrix				mtmp;													\
							vector				vtmp;													\
							FUN4EXPR_PRE;																\
							findCoordinateSystem(op1->string,from,to,cSystem);

#define	NTRANSFORM4EXPR		invertm(mtmp,&op2->real);													\
							mulmn(vtmp,to[0],&op3->real);												\
							mulmn(&res->real,mtmp,vtmp);

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
#define DEPTHEXPR		res->real	=	(op[2].real - clipMin) / (clipMax - clipMin);

DEFFUNC(Depth		,"depth"			,"f=p"	,FUN2EXPR_PRE,DEPTHEXPR,FUN2EXPR_UPDATE(1,3),NULL_EXPR,0)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// clearlighting	"o="
#define	CLEARLIGHTINGEXPR_PRE	clearLighting();

DEFFUNC(Clearlighting			,"clearlighting"				,"o="		,CLEARLIGHTINGEXPR_PRE,NULL_EXPR,NULL_EXPR,NULL_EXPR,0)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ambient	"c="
#define	AMBIENTEXPR_PRE		const float		*Clsave;											\
							TCode			*res;												\
							operand(0,res);														\
							runAmbientLights();													\
							Clsave = (*alights)->savedState[1];

#define AMBIENTEXPR			movvv(&res->real,Clsave);

#define	AMBIENTEXPR_UPDATE	res		+=	3;														\
							Clsave	+=	3;

DEFFUNC(Ambient			,"ambient"				,"c="		,AMBIENTEXPR_PRE,AMBIENTEXPR,AMBIENTEXPR_UPDATE,NULL_EXPR,0)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// diffuse	"c=n"
#define	DIFFUSEEXPR_PRE		const float		*P,*N,*Cl,*L;										\
							float			*R;													\
							float			*costheta	=	(float *) ralloc(numVertices*sizeof(float));	\
							const TCode		*op;												\
							TCode			*res;												\
							int				i;													\
							float			coefficient;										\
							vector			Ltmp;												\
							for (i=0;i<numVertices;i++) costheta[i]	=	0;						\
							operand(0,res);														\
							operand(1,op);														\
							P		=	varying[VARIABLE_P];									\
							N		=	&op->real;												\
							runLights(P,N,costheta);											\
							/* initialize output appropriately */								\
							R		=	&res->real;												\
							tags	=	tagStart;												\
							for (i=0;i<numVertices;i++) {										\
								if (*tags == 0) initv(R,0,0,0);									\
								R += 3;															\
								tags++;															\
							}																	\
							/* loop the lighting contributions */								\
							*currentLight = *lights;											\
							while (*currentLight) {												\
								enterFastLightingConditional();									\
								L		=	(*currentLight)->savedState[0];						\
								Cl		=	(*currentLight)->savedState[1];						\
								R		=	&res->real;											\
								N		=	&op->real;											\
								tags	=	tagStart;


#define DIFFUSEEXPR			normalizev(Ltmp,L);													\
							coefficient = dotvv(N,Ltmp);										\
							if (coefficient > 0) {												\
								R[COMP_R] += coefficient * Cl[COMP_R];							\
								R[COMP_G] += coefficient * Cl[COMP_G];							\
								R[COMP_B] += coefficient * Cl[COMP_B];							\
							}
								
#define	DIFFUSEEXPR_UPDATE	R		+=	3;														\
							N		+=	3;														\
							Cl		+=	3;														\
							L		+=	3;

#define DIFFUSEEXPR_POST		exitFastLightingConditional();									\
								*currentLight=(*currentLight)->next;							\
							}

DEFLIGHTFUNC(Diffuse				,"diffuse"				,"c=n"		,DIFFUSEEXPR_PRE, DIFFUSEEXPR, DIFFUSEEXPR_UPDATE, DIFFUSEEXPR_POST, PARAMETER_P)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// diffuse	"c=pnf"
#define	DIFFUSE2EXPR_PRE	const float		*P,*N,*Cl,*L;										\
							float			*R;													\
							float			*costheta	=	(float *) ralloc(numVertices*sizeof(float)); \
							const float		*cosangle;											\
							const TCode		*op1,*op2,*op3;										\
							TCode			*res;												\
							float			coefficient;										\
							vector			Ltmp;												\
							int				i;													\
							operand(0,res);														\
							operand(1,op1);														\
							operand(2,op2);														\
							operand(3,op3);														\
							for (i=0;i<numVertices;i++) costheta[i] = (float) cos(op3[i].real);	\
							P		=	&op1->real;												\
							N		=	&op2->real;												\
							runLights(P,N,costheta);											\
							/* initialize output appropriately */								\
							R		=	&res->real;												\
							tags 	=	tagStart;												\
							for (i=0;i<numVertices;i++) {										\
								if (*tags==0) initv(R,0,0,0);									\
								R += 3;															\
								tags++;															\
							}																	\
							/* loop the lighting contributions */								\
							*currentLight = *lights;											\
							while (*currentLight) {												\
								enterFastLightingConditional();									\
								L			=	(*currentLight)->savedState[0];					\
								Cl			=	(*currentLight)->savedState[1];					\
								R			=	&res->real;										\
								N			=	&op2->real;										\
								cosangle	=	costheta;										\
								tags		=	tagStart;

#define DIFFUSE2EXPR		normalizev(Ltmp,L);													\
							coefficient = dotvv(N,Ltmp);										\
							if (coefficient > *cosangle) {										\
								R[COMP_R] += coefficient * Cl[COMP_R];							\
								R[COMP_G] += coefficient * Cl[COMP_G];							\
								R[COMP_B] += coefficient * Cl[COMP_B];							\
							}

#define	DIFFUSE2EXPR_UPDATE	R			+=	3;													\
							N			+=	3;													\
							cosangle	+=	1;													\
							Cl			+=	3;													\
							L			+=	3;
							

#define DIFFUSE2EXPR_POST		exitFastLightingConditional();									\
								*currentLight=(*currentLight)->next;							\
							}


DEFLIGHTFUNC(Diffuse2			,"diffuse"				,"c=pnf"	,DIFFUSE2EXPR_PRE, DIFFUSE2EXPR, DIFFUSE2EXPR_UPDATE, DIFFUSE2EXPR_POST, 0)




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// specular	"c=nvf"
#define	SPECULAREXPR_PRE		const float		*P,*N,*Cl,*L,*V;									\
								float			*R,*power;											\
								float			*costheta	=	(float *) ralloc(numVertices*sizeof(float));	\
								float			*powers		=	(float *) ralloc(numVertices*sizeof(float));	\
								const TCode		*op1,*op2,*op3;										\
								TCode			*res;												\
								int				i;													\
								float			coefficient;										\
								vector			Ltmp,halfway;										\
								operand(0,res);														\
								operand(1,op1);														\
								operand(2,op2);														\
								operand(3,op3);														\
								for (i=0;i<numVertices;i++)	costheta[i]	=	0;						\
								P		=	varying[VARIABLE_P];									\
								N		=	&op1->real;												\
								runLights(P,N,costheta);											\
								/* initialize output appropriately */								\
								R			=	&res->real;											\
								power		=	powers;												\
								tags		=	tagStart;											\
								for (i=0;i<numVertices;i++) {										\
									if (*tags==0) {													\
										initv(R,0,0,0);												\
										*power = 10.0f / op3->real;									\
									}																\
									R			+=	3;												\
									op3			+=	1;												\
									power		+=	1;												\
									tags++;															\
								}																	\
								/* loop the lighting contributions */								\
								*currentLight = *lights;											\
								while (*currentLight) {												\
									enterFastLightingConditional();									\
									L			=	(*currentLight)->savedState[0];					\
									Cl			=	(*currentLight)->savedState[1];					\
									R			=	&res->real;										\
									N			=	&op1->real;										\
									V			=	&op2->real;										\
									power		=	powers;											\
									tags		=	tagStart;

#define SPECULAREXPR			normalizev(Ltmp,L);													\
								addvv(halfway,V,Ltmp);												\
								normalizev(halfway);												\
								coefficient = dotvv(N,halfway);										\
								if (coefficient > 0) {												\
									coefficient = (float) pow(coefficient,*power);					\
									R[COMP_R] += coefficient * Cl[COMP_R];							\
									R[COMP_G] += coefficient * Cl[COMP_G];							\
									R[COMP_B] += coefficient * Cl[COMP_B];							\
								}

#define	SPECULAREXPR_UPDATE		R			+=	3;													\
								N			+=	3;													\
								V			+=	3;													\
								power		+=	1;													\
								Cl			+=	3;													\
								L			+=	3;

#define SPECULAREXPR_POST			exitFastLightingConditional();									\
									*currentLight=(*currentLight)->next;							\
								}

DEFLIGHTFUNC(Specular				,"specular"				,"c=nvf"		,SPECULAREXPR_PRE, SPECULAREXPR, SPECULAREXPR_UPDATE, SPECULAREXPR_POST, PARAMETER_P)


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// phong	"c=nvf"
#define	PHONGEXPR_PRE			const float		*P,*N,*Cl,*L,*V,*size;								\
								float			*refDir,*R;											\
								float			*costheta	=	(float *) ralloc(numVertices*sizeof(float));	\
								float			*refDirs	=	(float *) ralloc(3*numVertices*sizeof(float));	\
								const TCode		*op1,*op2,*op3;										\
								TCode			*res;												\
								float			coefficient;										\
								vector			Ltmp;												\
								int				i;													\
								operand(0,res);														\
								operand(1,op1);														\
								operand(2,op2);														\
								operand(3,op3);														\
								for (i=0;i<numVertices;i++)	costheta[i]	=	0;						\
								P		=	varying[VARIABLE_P];									\
								N		=	&op1->real;												\
								runLights(P,N,costheta);											\
								/* initialize output appropriately */								\
								R			=	&res->real;											\
								N			=	&op1->real;											\
								V			=	&op2->real;											\
								refDir		=	refDirs;											\
								tags		=	tagStart;											\
								for (i=0;i<numVertices;i++) {										\
									if (*tags==0) {													\
										initv(R,0,0,0);												\
										mulvf(refDir,N,2*dotvv(N,V));								\
										subvv(refDir,V);											\
									}																\
									R			+=	3;												\
									N			+=	3;												\
									V			+=	3;												\
									refDir		+=	3;												\
									tags++;															\
								}																	\
								/* loop the lighting contributions */								\
								*currentLight = *lights;											\
								while (*currentLight) {												\
									enterFastLightingConditional();									\
									L			=	(*currentLight)->savedState[0];					\
									Cl			=	(*currentLight)->savedState[1];					\
									R			=	&res->real;										\
									size		=	&op3->real;										\
									refDir		=	refDirs;										\
									tags		=	tagStart;

#define PHONGEXPR				normalizev(Ltmp,L);													\
								coefficient = (float) pow(max(0,dotvv(refDir,Ltmp)),*size);			\
								if (coefficient > 0) {												\
									R[COMP_R] += coefficient * Cl[COMP_R];							\
									R[COMP_G] += coefficient * Cl[COMP_G];							\
									R[COMP_B] += coefficient * Cl[COMP_B];							\
								}

#define	PHONGEXPR_UPDATE		R		+=	3;														\
								size	+=	1;														\
								refDir	+=	3;														\
								Cl		+=	3;														\
								L		+=	3;

#define PHONGEXPR_POST			exitFastLightingConditional();										\
								*currentLight=(*currentLight)->next;								\
							}

DEFLIGHTFUNC(Phong				,"phong"				,"c=nvf"		,PHONGEXPR_PRE, PHONGEXPR, PHONGEXPR_UPDATE, PHONGEXPR_POST, PARAMETER_P)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// specularBRDF	"c=vnvf"
#define	SPECULARBRDFEXPR_PRE	TCode			*res;												\
								const TCode		*op1,*op2,*op3,*op4;								\
								vector			halfway;											\
								operand(0,res);														\
								operand(1,op1);														\
								operand(2,op2);														\
								operand(3,op3);														\
								operand(4,op4);

#define SPECULARBRDFEXPR		addvv(halfway,&op3->real,&op1->real);								\
								normalizev(halfway);												\
								res[0].real	=	(float) pow(max(0,dotvv(&op2->real,halfway)),(10.0f)/op4->real);	\
								res[1].real	=	res[0].real;										\
								res[2].real	=	res[1].real;										\

#define	SPECULARBRDFEXPR_UPDATE	res		+=	3;														\
								op1		+=	3;														\
								op2		+=	3;														\
								op3		+=	3;														\
								op4		+=	1;



DEFFUNC(SpecularBRDF			,"specularbrdf"				,"c=vnvf"		,SPECULARBRDFEXPR_PRE,SPECULARBRDFEXPR,SPECULARBRDFEXPR_UPDATE,NULL_EXPR,0)





#ifndef INIT_SHADING

#define	PARAMETEREXPR_PRE(accessor)																			\
								TCode		*res,*op1,*op2;													\
								const TCode	*src;															\
								int			srcStep,op2Step;												\
								float		found;															\
								CVariable	*cVar = NULL;													\
								int			globalIndex = -1;												\
								operand(0,res);																\
								operand(1,op1);																\
								operandSize(2,op2,op2Step);													\
								src		= op2;																\
								srcStep = op2Step;															\
																											\
								found		=	(float) FUNCTION(op2,op1->string,&cVar,&globalIndex);		\
																											\
								if (found != 0) {															\
									srcStep					=	0;											\
									if (cVar != NULL) {														\
										if (cVar->storage == STORAGE_PARAMETER || cVar->storage == STORAGE_MUTABLEPARAMETER) { 				\
											src					=	(TCode *) currentShadingState->locals[accessor][cVar->entry];			\
										} else {																							\
											src					=	(TCode *) varying[cVar->entry];											\
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

#define LIGHTPARAMETEREXPR_PRE	TCode		*res,*op1,*op2;													\
								const TCode	*src;															\
								int			srcStep,op2Step;												\
								float		found;															\
								CVariable	*cVar = NULL;													\
								int			globalIndex = -1;												\
								operand(0,res);																\
								operand(1,op1);																\
								operandSize(2,op2,op2Step);													\
								src		= op2;																\
								srcStep = op2Step;															\
																											\
								found		=	(float) (*currentLight)->instance->getParameter(op1->string,op2,&cVar,&globalIndex);\
																											\
								if (found != 0) {															\
									srcStep				=	0;												\
									if (cVar != NULL) {														\
										src					=	(TCode *) (*currentLight)->savedState[2+globalIndex];					\
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

#define	PARAMETEREXPRF			res->real	=	found;												\
								*op2		=	*src;

#define	PARAMETEREXPRS			res->real	=	found;												\
								*op2		=	*src;

#define	PARAMETEREXPRV			res->real	=	found;												\
								op2[0]		=	src[0];												\
								op2[1]		=	src[1];												\
								op2[2]		=	src[2];

#define	PARAMETEREXPRM			res->real	=	found;												\
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

#define	TEXTUREINFO_PRE			FUN4OUTEXPR_PRE														\
								float				found;											\
								CTextureInfoBase	*textureInfo;									\
								TCode				out[16*2];										\
								TCode				*src = &out[0];									\
								CTextureInfoLookup	*lookup;										\
								if ((lookup = (CTextureInfoLookup *) parameterlist) == NULL) {		\
									/* cache the texture lookup */									\
									lookup					=	new CTextureInfoLookup;				\
									parameterlist			=	lookup;								\
									dirty();														\
									lookup->textureInfo		=	getTextureInfo(op1->string);		\
								}																	\
																									\
								textureInfo = lookup->textureInfo;									\
								if (textureInfo == NULL) {											\
									found		=	0;												\
									src			=	op3;	/* prevent writing result */			\
								} else {															\
									int	i;															\
																									\
									for (i=0;i<16*2;i++) out[i].real = 0;							\
																									\
									found				=	1;										\
																									\
									if (strcmp(op2->string,"resolution") == 0) {					\
										textureInfo->getResolution(&out[0].real);					\
									} else if (strcmp(op2->string,"type") == 0) {					\
										out[0].string	=	textureInfo->getTextureType();			\
									} else if (strcmp(op2->string,"channels") == 0) {				\
										out[0].real		=	(float) textureInfo->getNumChannels();	\
									} else if (strcmp(op2->string,"viewingmatrix") == 0) {			\
										found = (float) textureInfo->getViewMatrix(&out[0].real);	\
									} else if (strcmp(op2->string,"projectionmatrix") == 0) {		\
										found = (float) textureInfo->getProjectionMatrix(&out[0].real);		\
									} else if (strcmp(op2->string,"exists") == 0) {					\
										src		=	op3;	/* prevent writing result */			\
									} else {														\
										found	=	0;												\
										src		=	op3;	/* prevent writing result */			\
									}																\
								}

#define	TEXTUREINFOF			res->real	=	found;												\
								*op3		=	src[0];

#define	TEXTUREINFOS			res->real	=	found;												\
								*op3		=	src[0];

#define	TEXTUREINFOV			res->real	=	found;												\
								op3[0]		=	src[0];												\
								op3[1]		=	src[1];												\
								op3[2]		=	src[2];

#define	TEXTUREINFOM			res->real	=	found;												\
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


#else

#undef	TEXTUREINFO_PRE
#undef	TEXTUREINFOF
#undef	TEXTUREINFOS
#undef	TEXTUREINFOV
#undef	TEXTUREINFOM
#undef	TEXTUREINFO_UPDATE

#define	TEXTUREINFO_PRE
#define	TEXTUREINFOF
#define	TEXTUREINFOS
#define	TEXTUREINFOV
#define	TEXTUREINFOM
#define	TEXTUREINFO_UPDATE
#endif

DEFLINKFUNC(Textureinfo2			,"textureinfo"				,"f=SSC!",	0)
DEFLINKFUNC(Textureinfo3			,"textureinfo"				,"f=SSN!",	0)
DEFLINKFUNC(Textureinfo4			,"textureinfo"				,"f=SSP!",	0)
DEFFUNC(TextureinfoV				,"textureinfo"				,"f=SSV!"	,TEXTUREINFO_PRE,TEXTUREINFOV,TEXTUREINFO_UPDATE(1,3),NULL_EXPR,0)
DEFFUNC(Textureinfo					,"textureinfo"				,"f=SSF!"	,TEXTUREINFO_PRE,TEXTUREINFOF,TEXTUREINFO_UPDATE(1,1),NULL_EXPR,0)
DEFFUNC(TextureinfoS				,"textureinfo"				,"f=SSS!"	,TEXTUREINFO_PRE,TEXTUREINFOS,TEXTUREINFO_UPDATE(1,1),NULL_EXPR,0)
DEFFUNC(TextureinfoM				,"textureinfo"				,"f=SSM!"	,TEXTUREINFO_PRE,TEXTUREINFOM,TEXTUREINFO_UPDATE(1,16),NULL_EXPR,0)


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// shadername	"s="
#define SHADERNAMEEXPR		res->string	=	(char *) currentShader->name;

DEFFUNC(ShaderName				,"shadername"					,"s="		,FUN1EXPR_PRE,SHADERNAMEEXPR,FUN1EXPR_UPDATE(1),NULL_EXPR,0)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// shadername	"s=s"
#ifndef INIT_SHADING
#define SHADERNAMESEXPR		res->string	=	(char *) shaderName(op->string);
#else
#undef SHADERNAMESEXPR
#define SHADERNAMESEXPR
#endif

DEFFUNC(ShaderNames				,"shadername"					,"s=s"		,FUN2EXPR_PRE,SHADERNAMESEXPR,FUN2EXPR_UPDATE(1,1),NULL_EXPR,0)











///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Texture - Environment - Shadow mapping macros
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This macro is used to decode the texture parameter list
#define	TEXTUREPARAMETERS(start,num)																			\
								lookup					=	new CTextureLookup;									\
								parameterlist			=	lookup;												\
								dirty();																		\
								lookup->filter			=	RiGaussianFilter;									\
								lookup->blur			=	0;													\
								lookup->swidth			=	1;													\
								lookup->twidth			=	1;													\
								lookup->numSamples		=	1;													\
								lookup->channel			=	0;													\
								lookup->fill			=	0;													\
								lookup->shadowBias		=	currentShadingState->currentObject->attributes->shadowBias;	\
								lookup->maxDist			=	C_INFINITY;											\
								lookup->coneAngle		=	0;													\
								lookup->label			=	NULL;												\
								lookup->lookupFloat		=	TRUE;												\
								lookup->texture			=	NULL;												\
								lookup->environment		=	NULL;												\
								{																				\
									int		i;																	\
									TCode	*param,*val;														\
																												\
									for (i=0;i<num;i++) {														\
										operand(i*2+start,param);												\
										operand(i*2+start+1,val);												\
																												\
										if (strcmp(param->string,"filter") == 0) {								\
											lookup->filter	=	currentRenderer->getFilter(val->string);		\
										} else if (strcmp(param->string,"blur") == 0) {							\
											lookup->blur		=	val->real;									\
											lookup->coneAngle	=	(float) (C_PI*val->real);					\
										} else if (strcmp(param->string,"swidth") == 0) {						\
											lookup->swidth		=	val->real;									\
										} else if (strcmp(param->string,"fill") == 0) {							\
											lookup->fill			=	val->real;								\
										} else if (strcmp(param->string,"twidth") == 0) {						\
											lookup->twidth		=	val->real;									\
										} else if (strcmp(param->string,"samples") == 0) {						\
											lookup->numSamples	=	(int) val->real;							\
										} else if (strcmp(param->string,"bias") == 0) {							\
											lookup->shadowBias	=	val->real;									\
										} else if (strcmp(param->string,"maxdist") == 0) {						\
											lookup->maxDist		=	val->real;									\
										} else if (strcmp(param->string,"samplecone") == 0) {					\
											lookup->coneAngle	=	val->real;									\
										} else if (strcmp(param->string,"label") == 0) {						\
											lookup->label		=	val->string;								\
										}																		\
									}																			\
								}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// texture	"f=SFff"
#ifndef INIT_SHADING
#define	TEXTUREFEXPR_PRE		TCode			*res;															\
								const TCode		*op3,*op4;														\
								CTextureLookup	*lookup;														\
								if ((lookup = (CTextureLookup *) parameterlist) == NULL) {						\
									int			numArguments;													\
									TCode		*op1,*op2;														\
									argumentcount(numArguments);												\
									TEXTUREPARAMETERS(5,(numArguments-5) >> 1);									\
									operand(1,op1);																\
									operand(2,op2);																\
									lookup->texture				=	getTexture(op1->string);					\
									lookup->channel				=	(int) op2->real;							\
									lookup->lookupFloat			=	TRUE;										\
								}																				\
								operand(0,res);																	\
								operand(3,op3);																	\
								operand(4,op4);																	\
								int				i;																\
								float			*dsdu		=	(float *) ralloc(numVertices*4*sizeof(float));	\
								float			*dsdv		=	dsdu + numVertices;								\
								float			*dtdu		=	dsdv + numVertices;								\
								float			*dtdv		=	dtdu + numVertices;								\
								const float		*s			=	(const float *) op3;							\
								const float		*t			=	(const float *) op4;							\
								float			cs[4],ct[4];													\
								vector			color;															\
								const	float	swidth		=	lookup->swidth;									\
								const	float	twidth		=	lookup->twidth;									\
								CTexture		*tex		=	lookup->texture;								\
								const float		*du			=	varying[VARIABLE_DU];							\
								const float		*dv			=	varying[VARIABLE_DV];							\
																												\
								duFloat(dsdu,s);																\
								duFloat(dtdu,t);																\
								dvFloat(dsdv,s);																\
								dvFloat(dtdv,t);																\
																												\
								for (i=0;i<numVertices;i++) {													\
									dsdu[i]		*=	swidth*du[i];												\
									dsdv[i]		*=	swidth*dv[i];												\
									dtdu[i]		*=	twidth*du[i];												\
									dtdv[i]		*=	twidth*dv[i];												\
								}																				\
																												\
								i	=	0;

#define	TEXTUREFEXPR			cs[0]		=	s[i];															\
								cs[1]		=	s[i] + dsdu[i];													\
								cs[2]		=	s[i] + dsdv[i];													\
								cs[3]		=	s[i] + dsdu[i] + dsdv[i];										\
								ct[0]		=	t[i];															\
								ct[1]		=	t[i] + dtdu[i];													\
								ct[2]		=	t[i] + dtdv[i];													\
								ct[3]		=	t[i] + dtdu[i] + dtdv[i];										\
								tex->lookup4(color,cs,ct,lookup);												\
								res[i].real	=	color[0];

#define	TEXTUREFEXPR_UPDATE		i++;
#else
#define	TEXTUREFEXPR_PRE
#define	TEXTUREFEXPR
#define	TEXTUREFEXPR_UPDATE
#endif

DEFFUNC(TextureFloat			,"texture"					,"f=SFff!"		,TEXTUREFEXPR_PRE,TEXTUREFEXPR,TEXTUREFEXPR_UPDATE,NULL_EXPR,PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_DU | PARAMETER_DV | PARAMETER_DERIVATIVE)

#undef	TEXTUREFEXPR_PRE
#undef	TEXTUREFEXPR
#undef	TEXTUREFEXPR_UPDATE





///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// texture	"c=SFff"
#ifndef INIT_SHADING
#define	TEXTURECEXPR_PRE		TCode			*res;															\
								const TCode		*op3,*op4;														\
								CTextureLookup	*lookup;														\
								if ((lookup = (CTextureLookup *) parameterlist) == NULL) {						\
									int			numArguments;													\
									TCode		*op1,*op2;														\
									argumentcount(numArguments);												\
									TEXTUREPARAMETERS(5,(numArguments-5) >> 1);									\
									operand(1,op1);																\
									operand(2,op2);																\
									lookup->texture				=	getTexture(op1->string);					\
									lookup->channel				=	(int) op2->real;							\
									lookup->lookupFloat			=	FALSE;										\
								}																				\
								operand(0,res);																	\
								operand(3,op3);																	\
								operand(4,op4);																	\
								int				i;																\
								float			*dsdu		=	(float *) ralloc(numVertices*4*sizeof(float));	\
								float			*dsdv		=	dsdu + numVertices;								\
								float			*dtdu		=	dsdv + numVertices;								\
								float			*dtdv		=	dtdu + numVertices;								\
								const float		*s			=	(const float *) op3;							\
								const float		*t			=	(const float *) op4;							\
								float			cs[4],ct[4];													\
								const	float	swidth		=	lookup->swidth;									\
								const	float	twidth		=	lookup->twidth;									\
								CTexture		*tex		=	lookup->texture;								\
								const float		*du			=	varying[VARIABLE_DU];							\
								const float		*dv			=	varying[VARIABLE_DV];							\
																												\
								duFloat(dsdu,s);																\
								duFloat(dtdu,t);																\
								dvFloat(dsdv,s);																\
								dvFloat(dtdv,t);																\
																												\
								for (i=0;i<numVertices;i++) {													\
									dsdu[i]		*=	swidth*du[i];												\
									dsdv[i]		*=	swidth*dv[i];												\
									dtdu[i]		*=	twidth*du[i];												\
									dtdv[i]		*=	twidth*dv[i];												\
								}																				\
																												\
								i	=	0;

#define	TEXTURECEXPR			cs[0]		=	s[i];															\
								cs[1]		=	s[i] + dsdu[i];													\
								cs[2]		=	s[i] + dsdv[i];													\
								cs[3]		=	s[i] + dsdu[i] + dsdv[i];										\
								ct[0]		=	t[i];															\
								ct[1]		=	t[i] + dtdu[i];													\
								ct[2]		=	t[i] + dtdv[i];													\
								ct[3]		=	t[i] + dtdu[i] + dtdv[i];										\
								tex->lookup4((float *) res,cs,ct,lookup);

#define	TEXTURECEXPR_UPDATE		i++;	res	+=	3;
#else
#define	TEXTURECEXPR_PRE
#define	TEXTURECEXPR
#define	TEXTURECEXPR_UPDATE
#endif

DEFFUNC(TextureColor			,"texture"					,"c=SFff!"		,TEXTURECEXPR_PRE,TEXTURECEXPR,TEXTURECEXPR_UPDATE,NULL_EXPR,PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_DU | PARAMETER_DV | PARAMETER_DERIVATIVE)

#undef	TEXTURECEXPR_PRE
#undef	TEXTURECEXPR
#undef	TEXTURECEXPR_UPDATE


















///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// texture	"f=SFffffffff"
#ifndef INIT_SHADING
#define	TEXTUREFFULLEXPR_PRE	TCode			*res;															\
								const TCode		*op3,*op4,*op5,*op6,*op7,*op8,*op9,*op10;						\
								CTextureLookup	*lookup;														\
								float			cs[4],ct[4];													\
								vector			tmp;															\
								if ((lookup = (CTextureLookup *) parameterlist) == NULL) {						\
									int			numArguments;													\
									TCode		*op1,*op2;														\
									argumentcount(numArguments);												\
									TEXTUREPARAMETERS(11,(numArguments-11) >> 1);								\
									operand(1,op1);																\
									operand(2,op2);																\
									lookup->texture				=	getTexture(op1->string);					\
									lookup->channel				=	(int) op2->real;							\
									lookup->lookupFloat			=	TRUE;										\
								}																				\
								CTexture		*tex		=	lookup->texture;								\
								operand(0,res);																	\
								operand(3,op3);																	\
								operand(4,op4);																	\
								operand(5,op5);																	\
								operand(6,op6);																	\
								operand(7,op7);																	\
								operand(8,op8);																	\
								operand(9,op9);																	\
								operand(10,op10);

#define	TEXTUREFFULLEXPR		cs[0]		=	op3->real;														\
								cs[1]		=	op5->real;														\
								cs[2]		=	op7->real;														\
								cs[3]		=	op9->real;														\
								ct[0]		=	op4->real;														\
								ct[1]		=	op6->real;														\
								ct[2]		=	op8->real;														\
								ct[3]		=	op10->real;														\
								tex->lookup4(tmp,cs,ct,lookup);													\
								res->real	=	tmp[0];

#define	TEXTUREFFULLEXPR_UPDATE	res++;																			\
								op3++;																			\
								op4++;																			\
								op5++;																			\
								op6++;																			\
								op7++;																			\
								op8++;																			\
								op9++;																			\
								op10++;																			\


#else
#define	TEXTUREFFULLEXPR_PRE
#define	TEXTUREFFULLEXPR
#define	TEXTUREFFULLEXPR_UPDATE
#endif

DEFFUNC(TextureFloatFull			,"texture"				,"f=SFffffffff!"		,TEXTUREFFULLEXPR_PRE,TEXTUREFFULLEXPR,TEXTUREFFULLEXPR_UPDATE,NULL_EXPR,0)

#undef	TEXTUREFFULLEXPR_PRE
#undef	TEXTUREFFULLEXPR
#undef	TEXTUREFFULLEXPR_UPDATE






///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// texture	"c=SFffffffff"
#ifndef INIT_SHADING
#define	TEXTURECFULLEXPR_PRE	TCode			*res;															\
								const TCode		*op3,*op4,*op5,*op6,*op7,*op8,*op9,*op10;						\
								CTextureLookup	*lookup;														\
								float			cs[4],ct[4];													\
								if ((lookup = (CTextureLookup *) parameterlist) == NULL) {						\
									int			numArguments;													\
									TCode		*op1,*op2;														\
									argumentcount(numArguments);												\
									TEXTUREPARAMETERS(11,(numArguments-11) >> 1);								\
									operand(1,op1);																\
									operand(2,op2);																\
									lookup->texture				=	getTexture(op1->string);					\
									lookup->channel				=	(int) op2->real;							\
									lookup->lookupFloat			=	FALSE;										\
								}																				\
								CTexture		*tex		=	lookup->texture;								\
								operand(0,res);																	\
								operand(3,op3);																	\
								operand(4,op4);																	\
								operand(5,op5);																	\
								operand(6,op6);																	\
								operand(7,op7);																	\
								operand(8,op8);																	\
								operand(9,op9);																	\
								operand(10,op10);

#define	TEXTURECFULLEXPR		cs[0]		=	op3->real;														\
								cs[1]		=	op5->real;														\
								cs[2]		=	op7->real;														\
								cs[3]		=	op9->real;														\
								ct[0]		=	op4->real;														\
								ct[1]		=	op6->real;														\
								ct[2]		=	op8->real;														\
								ct[3]		=	op10->real;														\
								tex->lookup4((float *) res,cs,ct,lookup);

#define	TEXTURECFULLEXPR_UPDATE	res	+=	3;																		\
								op3++;																			\
								op4++;																			\
								op5++;																			\
								op6++;																			\
								op7++;																			\
								op8++;																			\
								op9++;																			\
								op10++;																			\


#else
#define	TEXTURECFULLEXPR_PRE
#define	TEXTURECFULLEXPR
#define	TEXTURECFULLEXPR_UPDATE
#endif

DEFFUNC(TextureColorFull			,"texture"				,"c=SFffffffff!"		,TEXTURECFULLEXPR_PRE,TEXTURECFULLEXPR,TEXTURECFULLEXPR_UPDATE,NULL_EXPR,0)

#undef	TEXTURECFULLEXPR_PRE
#undef	TEXTURECFULLEXPR
#undef	TEXTURECFULLEXPR_UPDATE
















///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Environment / Shadow mapping macros
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// environment	"f=SFv"
#ifndef INIT_SHADING
#define	ENVIRONMENTFEXPR_PRE	CTextureLookup	*lookup;															\
								TCode			*res;																\
								const TCode		*op3;																\
								int				i;																	\
								if ((lookup = (CTextureLookup *) parameterlist) == NULL) {							\
									TCode			*op2,*op1;														\
									int				numArguments;													\
									argumentcount(numArguments);													\
									TEXTUREPARAMETERS(4,(numArguments-4) >> 1);										\
									operand(1,op1);																	\
									operand(2,op2);																	\
									lookup->channel				=	(int) op2->real;								\
									lookup->lookupFloat			=	TRUE;											\
									if ((strcmp(op1->string,"raytrace")==0) || (strcmp(op1->string,"reflection") == 0)) {		\
										lookup->environment		=	NULL;											\
									} else {																		\
										lookup->environment		=	getEnvironment(op1->string);					\
									}																				\
								}																					\
								if (lookup->environment == NULL) {													\
									float			*color;															\
									const int		numRealVertices = currentShadingState->numRealVertices;			\
																													\
									operand(0,res);																	\
									operand(3,op3);																	\
																													\
									color						=	(float *) ralloc(numRealVertices*3*sizeof(float));	\
									traceReflection(color,varying[VARIABLE_P],(float *) op3,numRealVertices,tags,lookup);	\
																													\
									for (i=numRealVertices;i>0;i--,tags++,res++,color+=3) {							\
										if (*tags == 0) {															\
											res->real	=	(color[0] + color[1] + color[2]) / (float) 3;			\
										}																			\
									}																				\
								} else {																			\
									const float		*D;																\
									vector			color;															\
									CEnvironment	*tex;															\
									float			*dDdu		=	(float *) ralloc(numVertices*6*sizeof(float));	\
									float			*dDdv		=	dDdu + numVertices*3;							\
									const float		*du			=	varying[VARIABLE_DU];							\
									const float		*dv			=	varying[VARIABLE_DV];							\
									operand(0,res);																	\
									operand(3,op3);																	\
									D		=	(const float *) op3;												\
									tex		=	lookup->environment;												\
																													\
									duVector(dDdu,D);																\
									dvVector(dDdv,D);																\
																													\
									for (i=currentShadingState->numRealVertices;i>0;i--,tags++) {					\
										if (*tags == 0) {															\
											vector	D0,D1,D2,D3;													\
																													\
											D0[0]	=	D[0];														\
											D0[1]	=	D[1];														\
											D0[2]	=	D[2];														\
											D1[0]	=	D[0] + dDdu[0]*du[0];										\
											D1[1]	=	D[1] + dDdu[1]*du[0];										\
											D1[2]	=	D[2] + dDdu[2]*du[0];										\
											D2[0]	=	D[0] + dDdv[0]*dv[0];										\
											D2[1]	=	D[1] + dDdv[1]*dv[0];										\
											D2[2]	=	D[2] + dDdv[2]*dv[0];										\
											D3[0]	=	D[0] + dDdv[0]*dv[0] + dDdu[0]*du[0];						\
											D3[1]	=	D[1] + dDdv[1]*dv[0] + dDdu[1]*du[0];						\
											D3[2]	=	D[2] + dDdv[2]*dv[0] + dDdu[2]*du[0];						\
																													\
											tex->lookup(color,D0,D1,D2,D3,lookup);									\
											res->real	=	color[0];												\
										}																			\
										res			++;																\
										D			+=	3;															\
										dDdu		+=	3;															\
										dDdv		+=	3;															\
										du++;																		\
										dv++;																		\
									}																				\
								}


#else
#define	ENVIRONMENTFEXPR_PRE
#endif

DEFFUNC(EnvironmentFloat			,"environment"				,"f=SFv!"		,ENVIRONMENTFEXPR_PRE,NULL_EXPR,NULL_EXPR,NULL_EXPR,PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_DU | PARAMETER_DV | PARAMETER_DERIVATIVE)

#undef	ENVIRONMENTFEXPR_PRE


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// shadow	"f=Sfv"
#ifndef INIT_SHADING
#define	SHADOWFEXPR_PRE			CTextureLookup	*lookup;															\
								TCode			*res;																\
								const TCode		*op3;																\
								int				i;																	\
								if ((lookup = (CTextureLookup *) parameterlist) == NULL) {							\
									TCode			*op2,*op1;														\
									int				numArguments;													\
									argumentcount(numArguments);													\
									TEXTUREPARAMETERS(4,(numArguments-4) >> 1);										\
									operand(1,op1);																	\
									operand(2,op2);																	\
									lookup->channel				=	(int) op2->real;								\
									lookup->lookupFloat			=	TRUE;											\
									if ((strcmp(op1->string,"raytrace")==0) || (strcmp(op1->string,"shadow") == 0)) {\
										lookup->environment		=	NULL;											\
									} else {																		\
										lookup->environment		=	getEnvironment(op1->string);					\
									}																				\
								}																					\
								if (lookup->environment == NULL) {													\
									float			*color;															\
									const int		numRealVertices = currentShadingState->numRealVertices;			\
																													\
									operand(0,res);																	\
									operand(3,op3);																	\
																													\
									color						=	(float *) ralloc(numRealVertices*3*sizeof(float));	\
																													\
									traceTransmission(color,(float *) op3,varying[VARIABLE_L],numRealVertices,tags,lookup);	\
																													\
									for (i=numRealVertices;i>0;i--,tags++,res++,color+=3) {							\
										if (*tags == 0) {															\
											res->real	=	1 - ((color[0] + color[1] + color[2]) / (float) 3);		\
										}																			\
									}																				\
								} else {																			\
									const float		*D;																\
									vector			color;															\
									CEnvironment	*tex;															\
									float			*dDdu		=	(float *) ralloc(numVertices*6*sizeof(float));	\
									float			*dDdv		=	dDdu + numVertices*3;							\
									const float		*du			=	varying[VARIABLE_DU];							\
									const float		*dv			=	varying[VARIABLE_DV];							\
									operand(0,res);																	\
									operand(3,op3);																	\
									D		=	(const float *) op3;												\
									tex		=	lookup->environment;												\
																													\
									duVector(dDdu,D);																\
									dvVector(dDdv,D);																\
																													\
									for (i=currentShadingState->numRealVertices;i>0;i--,tags++) {					\
										if (*tags == 0) {															\
											vector	D0,D1,D2,D3;													\
																													\
											D0[0]	=	D[0];														\
											D0[1]	=	D[1];														\
											D0[2]	=	D[2];														\
											D1[0]	=	D[0] + dDdu[0]*du[0];										\
											D1[1]	=	D[1] + dDdu[1]*du[0];										\
											D1[2]	=	D[2] + dDdu[2]*du[0];										\
											D2[0]	=	D[0] + dDdv[0]*dv[0];										\
											D2[1]	=	D[1] + dDdv[1]*dv[0];										\
											D2[2]	=	D[2] + dDdv[2]*dv[0];										\
											D3[0]	=	D[0] + dDdv[0]*dv[0] + dDdu[0]*du[0];						\
											D3[1]	=	D[1] + dDdv[1]*dv[0] + dDdu[1]*du[0];						\
											D3[2]	=	D[2] + dDdv[2]*dv[0] + dDdu[2]*du[0];						\
																													\
											tex->lookup(color,D0,D1,D2,D3,lookup);									\
											res->real	=	color[0];												\
										}																			\
										res			++;																\
										D			+=	3;															\
										dDdu		+=	3;															\
										dDdv		+=	3;															\
										du++;																		\
										dv++;																		\
									}																				\
								}


#else
#define	SHADOWFEXPR_PRE
#endif

DEFFUNC(ShadowFloat			,"shadow"				,"f=SFp!"		,SHADOWFEXPR_PRE,NULL_EXPR,NULL_EXPR,NULL_EXPR,PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_DU | PARAMETER_DV | PARAMETER_DERIVATIVE)

#undef	SHADOWFEXPR_PRE


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// environment	"c=SFv"
#ifndef INIT_SHADING
#define	ENVIRONMENTCEXPR_PRE	CTextureLookup	*lookup;															\
								TCode			*res;																\
								const TCode		*op3;																\
								int				i;																	\
								if ((lookup = (CTextureLookup *) parameterlist) == NULL) {							\
									TCode			*op2,*op1;														\
									int				numArguments;													\
									argumentcount(numArguments);													\
									TEXTUREPARAMETERS(4,(numArguments-4) >> 1);										\
									operand(1,op1);																	\
									operand(2,op2);																	\
									lookup->channel				=	(int) op2->real;								\
									lookup->lookupFloat			=	FALSE;											\
									if ((strcmp(op1->string,"raytrace")==0) || (strcmp(op1->string,"reflection") == 0)) {		\
										lookup->environment		=	NULL;											\
									} else {																		\
										lookup->environment		=	getEnvironment(op1->string);					\
									}																				\
								}																					\
								if (lookup->environment == NULL) {													\
									const int		numRealVertices = currentShadingState->numRealVertices;			\
																													\
									operand(0,res);																	\
									operand(3,op3);																	\
																													\
									traceReflection((float *) res,varying[VARIABLE_P],(float *) op3,numRealVertices,tags,lookup);	\
								} else {																			\
									const float		*D;																\
									CEnvironment	*tex;															\
									float			*dDdu		=	(float *) ralloc(numVertices*6*sizeof(float));	\
									float			*dDdv		=	dDdu + numVertices*3;							\
									const float		*du			=	varying[VARIABLE_DU];							\
									const float		*dv			=	varying[VARIABLE_DV];							\
									operand(0,res);																	\
									operand(3,op3);																	\
									D		=	(const float *) op3;												\
									tex		=	lookup->environment;												\
																													\
									duVector(dDdu,D);																\
									dvVector(dDdv,D);																\
																													\
									for (i=currentShadingState->numRealVertices;i>0;i--,tags++) {					\
										if (*tags == 0) {															\
											vector	D0,D1,D2,D3;													\
																													\
											D0[0]	=	D[0];														\
											D0[1]	=	D[1];														\
											D0[2]	=	D[2];														\
											D1[0]	=	D[0] + dDdu[0]*du[0];										\
											D1[1]	=	D[1] + dDdu[1]*du[0];										\
											D1[2]	=	D[2] + dDdu[2]*du[0];										\
											D2[0]	=	D[0] + dDdv[0]*dv[0];										\
											D2[1]	=	D[1] + dDdv[1]*dv[0];										\
											D2[2]	=	D[2] + dDdv[2]*dv[0];										\
											D3[0]	=	D[0] + dDdv[0]*dv[0] + dDdu[0]*du[0];						\
											D3[1]	=	D[1] + dDdv[1]*dv[0] + dDdu[1]*du[0];						\
											D3[2]	=	D[2] + dDdv[2]*dv[0] + dDdu[2]*du[0];						\
																													\
											tex->lookup(&res->real,D0,D1,D2,D3,lookup);								\
										}																			\
										res			+=	3;															\
										D			+=	3;															\
										dDdu		+=	3;															\
										dDdv		+=	3;															\
										du++;																		\
										dv++;																		\
									}																				\
								}


#else
#define	ENVIRONMENTCEXPR_PRE
#endif

DEFFUNC(EnvironmentColor			,"environment"				,"c=SFv!"		,ENVIRONMENTCEXPR_PRE,NULL_EXPR,NULL_EXPR,NULL_EXPR,PARAMETER_P | PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_DU | PARAMETER_DV | PARAMETER_DERIVATIVE)

#undef	ENVIRONMENTCEXPR_PRE


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// shadow	"c=SFv"
#ifndef INIT_SHADING
#define	SHADOWCEXPR_PRE			CTextureLookup	*lookup;															\
								TCode			*res;																\
								const TCode		*op3;																\
								int				i;																	\
								if ((lookup = (CTextureLookup *) parameterlist) == NULL) {							\
									TCode			*op2,*op1;														\
									int				numArguments;													\
									argumentcount(numArguments);													\
									TEXTUREPARAMETERS(4,(numArguments-4) >> 1);										\
									operand(1,op1);																	\
									operand(2,op2);																	\
									lookup->channel				=	(int) op2->real;								\
									lookup->lookupFloat			=	TRUE;											\
									if ((strcmp(op1->string,"raytrace")==0) || (strcmp(op1->string,"shadow") == 0)) {		\
										lookup->environment		=	NULL;											\
									} else {																		\
										lookup->environment		=	getEnvironment(op1->string);					\
									}																				\
								}																					\
								if (lookup->environment == NULL) {													\
									const int		numRealVertices = currentShadingState->numRealVertices;			\
																													\
									operand(0,res);																	\
									operand(3,op3);																	\
																													\
									traceTransmission((float *) res,(float *) op3,varying[VARIABLE_L],numRealVertices,tags,lookup);	\
																													\
									for (i=numRealVertices;i>0;i--,res+=3) {										\
										res[0].real	=	1 - res[0].real;											\
										res[1].real	=	1 - res[1].real;											\
										res[2].real	=	1 - res[2].real;											\
									}																				\
								} else {																			\
									const float		*D;																\
									CEnvironment	*tex;															\
									float			*dDdu		=	(float *) ralloc(numVertices*6*sizeof(float));	\
									float			*dDdv		=	dDdu + numVertices*3;							\
									const float		*du			=	varying[VARIABLE_DU];							\
									const float		*dv			=	varying[VARIABLE_DV];							\
									operand(0,res);																	\
									operand(3,op3);																	\
									D		=	(const float *) op3;												\
									tex		=	lookup->environment;												\
																													\
									duVector(dDdu,D);																\
									dvVector(dDdv,D);																\
																													\
									for (i=currentShadingState->numRealVertices;i>0;i--,tags++) {					\
										if (*tags == 0) {															\
											vector	D0,D1,D2,D3;													\
																													\
											D0[0]	=	D[0];														\
											D0[1]	=	D[1];														\
											D0[2]	=	D[2];														\
											D1[0]	=	D[0] + dDdu[0]*du[0];										\
											D1[1]	=	D[1] + dDdu[1]*du[0];										\
											D1[2]	=	D[2] + dDdu[2]*du[0];										\
											D2[0]	=	D[0] + dDdv[0]*dv[0];										\
											D2[1]	=	D[1] + dDdv[1]*dv[0];										\
											D2[2]	=	D[2] + dDdv[2]*dv[0];										\
											D3[0]	=	D[0] + dDdv[0]*dv[0] + dDdu[0]*du[0];						\
											D3[1]	=	D[1] + dDdv[1]*dv[0] + dDdu[1]*du[0];						\
											D3[2]	=	D[2] + dDdv[2]*dv[0] + dDdu[2]*du[0];						\
																													\
											tex->lookup(&res->real,D0,D1,D2,D3,lookup);								\
										}																			\
										res			+=	3;															\
										D			+=	3;															\
										dDdu		+=	3;															\
										dDdv		+=	3;															\
										du++;																		\
										dv++;																		\
									}																				\
								}


#else
#define	SHADOWCEXPR_PRE
#endif

DEFFUNC(ShadowColor			,"shadow"				,"c=SFp!"		,SHADOWCEXPR_PRE,NULL_EXPR,NULL_EXPR,NULL_EXPR,PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_DU | PARAMETER_DV | PARAMETER_DERIVATIVE)

#undef	SHADOWCEXPR_PRE




// This macro is used to decode the filter parameter list
#define	FILTERPARAMETERS(start,num)																				\
								lookup				=	new CFilterLookup;										\
								parameterlist		=	lookup;													\
								dirty();																		\
								lookup->filter		=	RiCatmullRomFilter;										\
								lookup->width		=	1;														\
								{																				\
									int		i;																	\
									TCode	*param,*val;														\
																												\
									for (i=0;i<num;i++) {														\
										operand(i*2+start,param);												\
										operand(i*2+start+1,val);												\
																												\
										if (strcmp(param->string,"filter") == 0) {								\
											lookup->filter		=	currentRenderer->getFilter(val->string);	\
										} else if (strcmp(param->string,"width") == 0) {						\
											lookup->width		=	val->real;									\
										}																		\
									}																			\
								}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// filterstep "f=ff!"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef INIT_SHADING
#define	FILTERSTEP2EXPR_PRE	FUN3EXPR_PRE																		\
							CFilterLookup	*lookup;															\
							float			tmp;																\
							float			val;																\
							int				i;																	\
							float			step,vstep;															\
							if ((lookup = (CFilterLookup *) parameterlist) == NULL) {							\
								int				numArguments;													\
								argumentcount(numArguments);													\
								FILTERPARAMETERS(3,(numArguments-3) >> 1);										\
								lookup->compute();																\
							}																					\
							const	float			width	=	lookup->width;									\
							float	*dsdu					=	(float *) ralloc(numVertices*2*sizeof(float));	\
							float	*dsdv					=	dsdu + numVertices;								\
							float	*fwidth					=	dsdu;											\
							const float		*du				=	varying[VARIABLE_DU];							\
							const float		*dv				=	varying[VARIABLE_DV];							\
							const float		*s				=	(const float *) &op2->real;						\
																												\
							duFloat(dsdu,s);																	\
							dvFloat(dsdv,s);																	\
							for (i=0;i<numVertices;i++) {														\
								dsdu[i]		=	fabs(dsdu[i]*du[i]);											\
								dsdv[i]		=	fabs(dsdv[i]*dv[i]);											\
								fwidth[i]	=	max(dsdv[i] + dsdv[i],C_EPSILON);								\
							}

#define	FILTERSTEP2EXPR		tmp		=	0;																		\
							val		=	op2->real+width*fwidth[0];												\
							vstep	=	lookup->valStep*fwidth[0];												\
							i		=	NUMFILTERSTEPS-1;														\
							while(i>=0) {																		\
								if (op1->real > val)	break;													\
								step	=	min(vstep,val-op1->real);											\
								tmp		+=	lookup->vals[i]*step;												\
								val		-=	vstep;																\
								i--;																			\
							}																					\
							res->real	=	tmp / (lookup->normalizer * fwidth[0]);


#define	FILTERSTEP2EXPR_UPDATE	FUN3EXPR_UPDATE(1,1,1)															\
								fwidth++;

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
							CFilterLookup	*lookup;															\
							float			tmp;																\
							float			val;																\
							int				i;																	\
							float			step,vstep,fwidth;													\
							if ((lookup = (CFilterLookup *) parameterlist) == NULL) {							\
								int				numArguments;													\
								argumentcount(numArguments);													\
								FILTERPARAMETERS(4,(numArguments-4) >> 1);										\
								lookup->compute();																\
							}																					\
							const	float			width	=	lookup->width;

#define	FILTERSTEP3EXPR		tmp		=	0;																		\
							fwidth	=	max(fabs(op2->real-op3->real),C_EPSILON);								\
							val		=	op2->real+width*fwidth;													\
							vstep	=	lookup->valStep*fwidth;													\
							i		=	NUMFILTERSTEPS-1;														\
							while(i>=0) {																		\
								if (op1->real > val)	break;													\
								step	=	min(vstep,val-op1->real);											\
								tmp		+=	lookup->vals[i]*step;												\
								val		-=	vstep;																\
								i--;																			\
							}																					\
							res->real	=	tmp / (lookup->normalizer * fwidth);


#define	FILTERSTEP3EXPR_UPDATE	FUN4EXPR_UPDATE(1,1,1,1)
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
// This macro is used to decode the bake3d parameter list
#define	TEXTURE3DPARAMETERS(start,num)																			\
								lookup						=	new CTexture3dLookup;							\
								const char **channelNames	=	(const char **) ralloc(num*sizeof(char*));		\
								parameterlist				=	lookup;											\
								dirty();																		\
								lookup->radius			=	-1.0f;												\
								lookup->radiusScale		=	1.0f;												\
								lookup->coordsys		=	NULL;												\
								lookup->numChannels		=	0;													\
								lookup->dataStart		=	start;												\
								{																				\
									/* we assume here that channels and parameters are not mixed */ 			\
									int		i;																	\
									TCode	*param,*val;														\
																												\
									for (i=0;i<num;i++) {														\
										operand(i*2+start,param);												\
										operand(i*2+start+1,val);												\
																												\
										if (strcmp(param->string,"radiusscale") == 0) {							\
											lookup->radiusScale	=	val->real;									\
											lookup->dataStart += 2;												\
										} else if (strcmp(param->string,"radius") == 0) {						\
											lookup->radius		=	val->real;									\
											lookup->dataStart += 2;												\
										} else if (strcmp(param->string,"coordsystem") == 0) {					\
											lookup->coordsys	=	strdup(val->string);								\
											lookup->dataStart += 2;												\
										} else {																\
											channelNames[lookup->numChannels++]	= param->string;				\
										}																		\
									}																			\
								}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// bake3d	"f=SSpn!"
#ifndef INIT_SHADING
#define	BAKE3DEXPR_PRE			TCode			*res;															\
								const TCode		*op3,*op4;														\
								CTexture3dLookup*lookup;														\
								int				numArguments;													\
								argumentcount(numArguments);													\
								const TCode		**channelValues = (const TCode **) ralloc(numArguments*sizeof(TCode*));	\
								if ((lookup = (CTexture3dLookup *) parameterlist) == NULL) {					\
									TCode		*op1,*op2;														\
									TEXTURE3DPARAMETERS(5,(numArguments-5) >> 1);								\
									operand(1,op1);																\
									operand(2,op2);																\
									lookup->texture		=	getTexture3d(op1->string,TRUE,op2->string,lookup->coordsys);							\
									lookup->sampleSize	=	lookup->texture->bindChannelNames(lookup->numChannels,channelNames,&lookup->bindings);	\
									lookup->valueSpace	=	new float[lookup->sampleSize];						\
								}																				\
								operand(0,res);																	\
								operand(3,op3);																	\
								operand(4,op4);																	\
								int				i;																\
								float			*dPdu		=	(float *) ralloc(numVertices*7*sizeof(float));	\
								float			*dPdv		=	dPdu + numVertices*3;							\
								float			*radius		=	dPdv + numVertices*3;							\
								const	float	radiiscale	=	lookup->radiusScale;							\
								float			*r			=	radius;											\
								CTexture3d		*tex		=	lookup->texture;								\
								const float		*D			=	(const float *) op3;							\
								const float		*du			=	varying[VARIABLE_DU];							\
								const float		*dv			=	varying[VARIABLE_DV];							\
																												\
								duVector(dPdu,D);																\
								dvVector(dPdv,D);																\
																												\
								if ( lookup->radius < 0 ) {														\
									/* unless one was specified, calculate the radius */						\
									for (i=0;i<numVertices;i++) {												\
										vector	D0,D1,D2,D3;													\
										vector	l0,l1,l2,l3;													\
																												\
										D0[0]	=	D[0];														\
										D0[1]	=	D[1];														\
										D0[2]	=	D[2];														\
										D1[0]	=	D[0] + dPdu[0]*du[0];										\
										D1[1]	=	D[1] + dPdu[1]*du[0];										\
										D1[2]	=	D[2] + dPdu[2]*du[0];										\
										D2[0]	=	D[0] + dPdv[0]*dv[0];										\
										D2[1]	=	D[1] + dPdv[1]*dv[0];										\
										D2[2]	=	D[2] + dPdv[2]*dv[0];										\
										D3[0]	=	D[0] + dPdv[0]*dv[0] + dPdu[0]*du[0];						\
										D3[1]	=	D[1] + dPdv[1]*dv[0] + dPdu[1]*du[0];						\
										D3[2]	=	D[2] + dPdv[2]*dv[0] + dPdu[2]*du[0];						\
																												\
										subvv(l0,D0,D1);														\
										subvv(l1,D1,D3);														\
										subvv(l2,D3,D2);														\
										subvv(l3,D2,D0);														\
																												\
										float rm = max(dotvv(l0,l0),dotvv(l1,l1));								\
										rm = max(rm,dotvv(l2,l2));												\
										rm = max(rm,dotvv(l3,l3));												\
																												\
										*r++ = radiiscale*0.5f*sqrtf(rm);										\
									}																			\
								} else {																		\
									/* explicit radius given */													\
									for (i=0;i<numVertices;i++) {												\
										*r++ = radiiscale*lookup->radius;														\
									}																			\
								}																				\
																												\
								for (i=0;i<lookup->numChannels;i++) {											\
									operand(lookup->dataStart+i*2+1,channelValues[i]);							\
								} 

#define	BAKE3DEXPR				tex->prepareSample(lookup->valueSpace,(float**)channelValues,lookup->bindings);	\
								tex->store(lookup->valueSpace,&op3->real,&op4->real,*radius);					\
								res->real		=	1;

#define	BAKE3DEXPR_UPDATE		res++;																			\
								op3+=3;																			\
								op4+=3;																			\
								radius++;																		\
								for (int j=0;j<lookup->numChannels;j++) {										\
									channelValues[j]	+=	lookup->bindings[j]->numSamples;					\
								}
#else
#define	BAKE3DEXPR_PRE
#define	BAKE3DEXPR
#define	BAKE3DEXPR_UPDATE
#endif

DEFFUNC(Bake3d			,"bake3d"					,"f=SSpn!"		,BAKE3DEXPR_PRE,BAKE3DEXPR,BAKE3DEXPR_UPDATE,NULL_EXPR,PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_DU | PARAMETER_DV | PARAMETER_DERIVATIVE)

#undef	BAKE3DEXPR_PRE
#undef	BAKE3DEXPR
#undef	BAKE3DEXPR_UPDATE



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// texture3d	"f=Spn!"
#ifndef INIT_SHADING
#define	TEXTURE3DEXPR_PRE		TCode			*res;															\
								const TCode		*op2,*op3;														\
								CTexture3dLookup	*lookup;													\
								int				numArguments;													\
								argumentcount(numArguments);													\
								const TCode		**channelValues = (const TCode **) ralloc(numArguments*sizeof(TCode*));	\
								if ((lookup = (CTexture3dLookup *) parameterlist) == NULL) {					\
									TCode		*op1;															\
									TEXTURE3DPARAMETERS(4,(numArguments-4) >> 1);								\
									operand(1,op1);																\
									lookup->texture		=	getTexture3d(op1->string,FALSE,NULL,lookup->coordsys);									\
									lookup->sampleSize	=	lookup->texture->bindChannelNames(lookup->numChannels,channelNames,&lookup->bindings);	\
									lookup->valueSpace	=	new float[lookup->sampleSize];						\
								}																				\
								operand(0,res);																	\
								operand(2,op2);																	\
								operand(3,op3);																	\
								int				i;																\
								float			*dPdu		=	(float *) ralloc(numVertices*7*sizeof(float));	\
								float			*dPdv		=	dPdu + numVertices*3;							\
								float			*radius		=	dPdv + numVertices*3;							\
								const	float	radiiscale	=	lookup->radiusScale;							\
								float			*r			=	radius;											\
								CTexture3d		*tex		=	lookup->texture;								\
								const float		*D			=	(const float *) op2;							\
								const float		*du			=	varying[VARIABLE_DU];							\
								const float		*dv			=	varying[VARIABLE_DV];							\
																												\
								duVector(dPdu,D);																\
								dvVector(dPdv,D);																\
																												\
								if ( lookup->radius < 0 ) {														\
									/* unless one was specified, calculate the radius */						\
									for (i=0;i<numVertices;i++) {												\
										vector	D0,D1,D2,D3;													\
										vector	l0,l1,l2,l3;													\
																												\
										D0[0]	=	D[0];														\
										D0[1]	=	D[1];														\
										D0[2]	=	D[2];														\
										D1[0]	=	D[0] + dPdu[0]*du[0];										\
										D1[1]	=	D[1] + dPdu[1]*du[0];										\
										D1[2]	=	D[2] + dPdu[2]*du[0];										\
										D2[0]	=	D[0] + dPdv[0]*dv[0];										\
										D2[1]	=	D[1] + dPdv[1]*dv[0];										\
										D2[2]	=	D[2] + dPdv[2]*dv[0];										\
										D3[0]	=	D[0] + dPdv[0]*dv[0] + dPdu[0]*du[0];						\
										D3[1]	=	D[1] + dPdv[1]*dv[0] + dPdu[1]*du[0];						\
										D3[2]	=	D[2] + dPdv[2]*dv[0] + dPdu[2]*du[0];						\
																												\
										subvv(l0,D0,D1);														\
										subvv(l1,D1,D3);														\
										subvv(l2,D3,D2);														\
										subvv(l3,D2,D0);														\
																												\
										float rm = max(dotvv(l0,l0),dotvv(l1,l1));								\
										rm = max(rm,dotvv(l2,l2));												\
										rm = max(rm,dotvv(l3,l3));												\
																												\
										*r++ = radiiscale*0.5f*sqrtf(rm);										\
									}																			\
								} else {																		\
									/* explicit radius given */													\
									for (i=0;i<numVertices;i++) {												\
										*r++ = radiiscale*lookup->radius;														\
									}																			\
								}																				\
																												\
								for (i=0;i<lookup->numChannels;i++) {											\
									operand(lookup->dataStart+i*2+1,channelValues[i]);							\
								}

#define	TEXTURE3DEXPR			tex->lookup(lookup->valueSpace,&op2->real,&op3->real,*radius);							\
								tex->unpackSample(lookup->valueSpace,(float**)channelValues,lookup->bindings);			\
								res->real		=	1;

#define	TEXTURE3DEXPR_UPDATE	res++;																			\
								op2+=3;																			\
								op3+=3;																			\
								radius++;																		\
								for (int j=0;j<lookup->numChannels;j++) {										\
									channelValues[j]	+=	lookup->bindings[j]->numSamples;					\
								}
#else
#define	TEXTURE3DEXPR_PRE
#define	TEXTURE3DEXPR
#define	TEXTURE3DEXPR_UPDATE
#endif

DEFFUNC(Texture3d			,"texture3d"					,"f=Spn!"		,TEXTURE3DEXPR_PRE,TEXTURE3DEXPR,TEXTURE3DEXPR_UPDATE,NULL_EXPR,PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_DU | PARAMETER_DV | PARAMETER_DERIVATIVE)

#undef	TEXTURE3DEXPR_PRE
#undef	TEXTURE3DEXPR
#undef	TEXTURE3DEXPR_UPDATE


///////////////////////////////////////////////////
//
//	FIXME : missing functions :
//	bump


#include "giFunctions.h"
