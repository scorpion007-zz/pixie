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
//  File				:	scriptFunctions.h
//  Classes				:	-
//  Description			:	This file defines the built in functions that
//							can be used from the script. Note that the
//							functions defined here are totally generic and
//							don't need the presence of any external library.
//
//
//							If you have to add application specific built in
//							functions, include that file at the end of this one.
//
//
////////////////////////////////////////////////////////////////////////

#define	FUN1EXPR_PRE		float	*res;									\
							operand(0,res,float *);

#define	FUN1EXPR_UPDATE(__rs)												\
							res	+=	__rs;


#define	FUN2EXPR_PRE		float		*res;								\
							const float	*op;								\
							operand(0,res,float *);							\
							operand(1,op,const float *);

#define	FUN2OUTEXPR_PRE		float		*res,*op;							\
							operand(0,res,float *);							\
							operand(1,op,float *);



#define	FUN2EXPR_UPDATE(__rs,__op1s)										\
							res	+=	__rs;									\
							op	+=	__op1s;


#define	FUN3EXPR_PRE		float		*res;								\
							const float	*op1,*op2;							\
							operand(0,res,float *);							\
							operand(1,op1,const float *);					\
							operand(2,op2,const float *);

#define	FUN3OUTEXPR_PRE		float		*res,*op1,*op2;						\
							operand(0,res,float *);							\
							operand(1,op1,float *);							\
							operand(2,op2,float *);


#define	FUN3EXPR_UPDATE(__rs,__op1s,__op2s)									\
							res	+=	__rs;									\
							op1	+=	__op1s;									\
							op2	+=	__op2s;


#define	FUN4EXPR_PRE		float		*res;								\
							const float	*op1,*op2,*op3;						\
							operand(0,res,float *);							\
							operand(1,op1,const float *);					\
							operand(2,op2,const float *);					\
							operand(3,op3,const float *);

#define	FUN4OUTEXPR_PRE		float		*res,*op1,*op2,*op3;				\
							operand(0,res,float *);							\
							operand(1,op1,float *);							\
							operand(2,op2,float *);							\
							operand(3,op3,float *);


#define	FUN4EXPR_UPDATE(__rs,__op1s,__op2s,__op3s)							\
							res	+=	__rs;									\
							op1	+=	__op1s;									\
							op2	+=	__op2s;									\
							op3	+=	__op3s;

#define	FUN5EXPR_PRE		float		*res;								\
							const float	*op1,*op2,*op3,*op4;				\
							operand(0,res,float *);							\
							operand(1,op1,const float *);					\
							operand(2,op2,const float *);					\
							operand(3,op3,const float *);					\
							operand(4,op4,const float *);

#define	FUN5OUTEXPR_PRE		float	*res,*op1,*op2,*op3,*op4;				\
							operand(0,res,float *);							\
							operand(1,op1,float *);							\
							operand(2,op2,float *);							\
							operand(3,op3,float *);							\
							operand(4,op4,float *);


#define	FUN5EXPR_UPDATE(__rs,__op1s,__op2s,__op3s,__op4s)					\
							res	+=	__rs;									\
							op1	+=	__op1s;									\
							op2	+=	__op2s;									\
							op3	+=	__op3s;									\
							op4	+=	__op4s;

#define	SIMPLEFUNCTION		*res	=	(float) FUNCTION(*op);


#define	FUNCTION(x)	degrees(x)
DEFFUNC(Degrees		,"degrees"	,"f=f",FUN2EXPR_PRE,SIMPLEFUNCTION,FUN2EXPR_UPDATE(1,1),NULL_EXPR,0)
#undef	FUNCTION

#define	FUNCTION(x)	radians(x)
DEFFUNC(Radians		,"radians"	,"f=f",FUN2EXPR_PRE,SIMPLEFUNCTION,FUN2EXPR_UPDATE(1,1),NULL_EXPR,0)
#undef	FUNCTION

#define	FUNCTION(x)	sin(x)
DEFFUNC(Sin			,"sin"		,"f=f",FUN2EXPR_PRE,SIMPLEFUNCTION,FUN2EXPR_UPDATE(1,1),NULL_EXPR,0)
#undef	FUNCTION

#define	FUNCTION(x)	cos(x)
DEFFUNC(Cos			,"cos"		,"f=f",FUN2EXPR_PRE,SIMPLEFUNCTION,FUN2EXPR_UPDATE(1,1),NULL_EXPR,0)
#undef	FUNCTION

#define	FUNCTION(x)	tan(x)
DEFFUNC(Tan			,"tan"		,"f=f",FUN2EXPR_PRE,SIMPLEFUNCTION,FUN2EXPR_UPDATE(1,1),NULL_EXPR,0)
#undef	FUNCTION

#define	FUNCTION(x)	asin(max(min(x,1),-1))
DEFFUNC(Asin		,"asin"		,"f=f",FUN2EXPR_PRE,SIMPLEFUNCTION,FUN2EXPR_UPDATE(1,1),NULL_EXPR,0)
#undef	FUNCTION

#define	FUNCTION(x)	acos(max(min(x,1),-1))
DEFFUNC(Acos		,"acos"		,"f=f",FUN2EXPR_PRE,SIMPLEFUNCTION,FUN2EXPR_UPDATE(1,1),NULL_EXPR,0)
#undef	FUNCTION

#define	FUNCTION(x)	atan(x)
DEFFUNC(Atan		,"atan"		,"f=f",FUN2EXPR_PRE,SIMPLEFUNCTION,FUN2EXPR_UPDATE(1,1),NULL_EXPR,0)
#undef	FUNCTION

#define	FUNCTION(x)	exp(x)
DEFFUNC(Exp			,"exp"		,"f=f",FUN2EXPR_PRE,SIMPLEFUNCTION,FUN2EXPR_UPDATE(1,1),NULL_EXPR,0)
#undef	FUNCTION

#define	FUNCTION(x)	log(max(x,C_EPSILON))
DEFFUNC(Log			,"log"		,"f=f",FUN2EXPR_PRE,SIMPLEFUNCTION,FUN2EXPR_UPDATE(1,1),NULL_EXPR,0)
#undef	FUNCTION

#define	FUNCTION(x)	sqrt(max(x,0))
DEFFUNC(Sqrt		,"sqrt"		,"f=f",FUN2EXPR_PRE,SIMPLEFUNCTION,FUN2EXPR_UPDATE(1,1),NULL_EXPR,0)
#undef	FUNCTION

#define	FUNCTION(x)	isqrtf(max(x,0))
DEFFUNC(InvSqrt		,"inversesqrt"	,"f=f",FUN2EXPR_PRE,SIMPLEFUNCTION,FUN2EXPR_UPDATE(1,1),NULL_EXPR,0)
#undef	FUNCTION

#define	FUNCTION(x)	fabs(x)
DEFFUNC(Abs			,"abs"		,"f=f",FUN2EXPR_PRE,SIMPLEFUNCTION,FUN2EXPR_UPDATE(1,1),NULL_EXPR,0)
#undef	FUNCTION

#define	FUNCTION(x)	(x < 0 ? -1 : x > 0 ? 1 : 0)
DEFFUNC(Sign		,"sign"		,"f=f",FUN2EXPR_PRE,SIMPLEFUNCTION,FUN2EXPR_UPDATE(1,1),NULL_EXPR,0)
#undef	FUNCTION

#define	FUNCTION(x)	floor(x)
DEFFUNC(Floor		,"floor"		,"f=f",FUN2EXPR_PRE,SIMPLEFUNCTION,FUN2EXPR_UPDATE(1,1),NULL_EXPR,0)
#undef	FUNCTION

#define	FUNCTION(x)	ceil(x)
DEFFUNC(Ceil		,"ceil"		,"f=f",FUN2EXPR_PRE,SIMPLEFUNCTION,FUN2EXPR_UPDATE(1,1),NULL_EXPR,0)
#undef	FUNCTION

#define	FUNCTION(x)	(int) x
DEFFUNC(Round		,"round"		,"f=f",FUN2EXPR_PRE,SIMPLEFUNCTION,FUN2EXPR_UPDATE(1,1),NULL_EXPR,0)
#undef	FUNCTION

#define	ATAN2EXP	*res		=	atan2f(*op1,*op2);
DEFFUNC(Atan2		,"atan"			,"f=ff",FUN3EXPR_PRE,ATAN2EXP,FUN3EXPR_UPDATE(1,1,1),NULL_EXPR,0)

#define	POW2EXP		*res		=	(*op1 > 0 ? (float) pow(*op1,*op2) : 0); if ((*res)*(*res) < 0) *res = 0;
DEFFUNC(Pow2		,"pow"			,"f=ff",FUN3EXPR_PRE,POW2EXP,FUN3EXPR_UPDATE(1,1,1),NULL_EXPR,0)

#define	LOG2EXP		*res		=	(float) (log((double)*op1) / log((double)*op2));
DEFFUNC(Log2		,"log"			,"f=ff",FUN3EXPR_PRE,LOG2EXP,FUN3EXPR_UPDATE(1,1,1),NULL_EXPR,0)

#define	MOD2EXP		*res		=	(float) fmod((double)*op1,(double)*op2); if (*res < 0) *res += *op2; assert(*res >= 0);
DEFFUNC(Mod2		,"mod"			,"f=ff",FUN3EXPR_PRE,MOD2EXP,FUN3EXPR_UPDATE(1,1,1),NULL_EXPR,0)

#define	CLAMPFEXP	*res		=	(*op1 < *op2 ? *op2: *op1 > *op3 ? *op3 : *op1);
DEFFUNC(Clampf		,"clamp"		,"f=fff",FUN4EXPR_PRE,CLAMPFEXP,FUN4EXPR_UPDATE(1,1,1,1),NULL_EXPR,0)

#define	CLAMPVEXP	res[0]	=	(op1[0] < op2[0] ? op2[0]: op1[0] > op3[0] ? op3[0] : op1[0]);	\
					res[1]	=	(op1[1] < op2[1] ? op2[1]: op1[1] > op3[1] ? op3[1] : op1[1]);	\
					res[2]	=	(op1[2] < op2[2] ? op2[2]: op1[2] > op3[2] ? op3[2] : op1[2]);

DEFLINKFUNC(Clampp		,"clamp"		,	"p=ppp" , 0)
DEFLINKFUNC(Clampn		,"clamp"		,	"n=nnn"	, 0)
DEFLINKFUNC(Clampc		,"clamp"		,	"c=ccc"	, 0)
DEFFUNC(Clampv			,"clamp"		,	"v=vvv"	,FUN4EXPR_PRE,CLAMPVEXP,FUN4EXPR_UPDATE(3,3,3,3),NULL_EXPR,0)









#define	MIXFEXP		res[0]	=	(float) (op1[0]*(1.0-(double)op3[0]) + op2[0]*(double)op3[0]);
DEFFUNC(Mixf		,"mix"		,"f=fff",FUN4EXPR_PRE,MIXFEXP,FUN4EXPR_UPDATE(1,1,1,1),NULL_EXPR,0)

#define	MIXVEXP		res[0]	=	(float) (op1[0]*(1.0-(double)op3[0]) + op2[0]*(double)op3[0]);	\
					res[1]	=	(float) (op1[1]*(1.0-(double)op3[0]) + op2[1]*(double)op3[0]);	\
					res[2]	=	(float) (op1[2]*(1.0-(double)op3[0]) + op2[2]*(double)op3[0]);

DEFLINKFUNC(Mixc		,"mix"			,	"c=ccf", 0)
DEFLINKFUNC(Mixp		,"mix"			,	"p=ppf", 0)
DEFLINKFUNC(Mixn		,"mix"			,	"n=nnf", 0)
DEFFUNC(Mixv			,"mix"			,	"v=vvf",FUN4EXPR_PRE,MIXVEXP,FUN4EXPR_UPDATE(3,3,3,1),NULL_EXPR,0)

#define	MIXVVEXP	res[0]	=	(float) (op1[0]*(1.0-(double)op3[0]) + op2[0]*(double)op3[0]);	\
					res[1]	=	(float) (op1[1]*(1.0-(double)op3[1]) + op2[1]*(double)op3[1]);	\
					res[2]	=	(float) (op1[2]*(1.0-(double)op3[2]) + op2[2]*(double)op3[2]);

DEFLINKFUNC(Mixcc		,"mix"			,	"c=ccc", 0)
DEFLINKFUNC(Mixpp		,"mix"			,	"p=ppp", 0)
DEFLINKFUNC(Mixnn		,"mix"			,	"n=nnn", 0)
DEFFUNC(Mixvv			,"mix"			,	"v=vvv",FUN4EXPR_PRE,MIXVVEXP,FUN4EXPR_UPDATE(3,3,3,3),NULL_EXPR,0)


#define	STEPEXP		*res	=	(*op2 < *op1 ? 0.0f : 1.0f);
DEFFUNC(Stepf		,"step"		,"f=ff",FUN3EXPR_PRE,STEPEXP,FUN3EXPR_UPDATE(1,1,1),NULL_EXPR,0)


#define	SMOOTHSTEPEXP	if (*op3 < *op1)		*res	=	0;							\
						else if (*op3 > *op2)	*res	=	1;							\
						else {															\
							float	u	=	(*op3 - *op1) / (*op2 - *op1);				\
							*res		=	-2*u*u*u + 3*u*u;							\
						}

DEFFUNC(SmoothStepf		,"smoothstep"		,"f=fff",FUN4EXPR_PRE,SMOOTHSTEPEXP,FUN4EXPR_UPDATE(1,1,1,1),NULL_EXPR,0)

#define	RANDOMFEXP		*res	=	urand();

#define	RANDOMVEXP		res[0]	=	urand();	\
						res[1]	=	urand();	\
						res[2]	=	urand();

DEFFUNC(Randomf			,"random"		,"f=",FUN1EXPR_PRE,RANDOMFEXP,FUN1EXPR_UPDATE(1),NULL_EXPR,0)
DEFLINKFUNC(Random1		,"random"		,"c=", 0)
DEFLINKFUNC(Random2		,"random"		,"p=", 0)
DEFLINKFUNC(Random3		,"random"		,"n=", 0)
DEFFUNC(Randomv			,"random"		,"v=",FUN1EXPR_PRE,RANDOMVEXP,FUN1EXPR_UPDATE(3),NULL_EXPR,0)

DEFFUNC(URandomf		,"urandom"		,"f=",FUN1EXPR_PRE,RANDOMFEXP,FUN1EXPR_UPDATE(1),NULL_EXPR,0)
DEFLINKFUNC(URandom1	,"urandom"		,"c=", 0)
DEFLINKFUNC(URandom2	,"urandom"		,"p=", 0)
DEFLINKFUNC(URandom3	,"urandom"		,"n=", 0)
DEFFUNC(URandomv		,"urandom"		,"v=",FUN1EXPR_PRE,RANDOMVEXP,FUN1EXPR_UPDATE(3),NULL_EXPR,0)


#define	XCOMPEXP		*res	=	op[0];
DEFLINKFUNC(Xcomp1		,"xcomp"		,"f=p", 0)
DEFLINKFUNC(Xcomp2		,"xcomp"		,"f=n", 0)
DEFFUNC(XComp			,"xcomp"		,"f=v",FUN2EXPR_PRE,XCOMPEXP,FUN2EXPR_UPDATE(1,3),NULL_EXPR,0)

#define	YCOMPEXP		*res	=	op[1];
DEFLINKFUNC(Ycomp1		,"ycomp"		,"f=p", 0)
DEFLINKFUNC(Ycomp2		,"ycomp"		,"f=n", 0)
DEFFUNC(YComp			,"ycomp"		,"f=v",FUN2EXPR_PRE,YCOMPEXP,FUN2EXPR_UPDATE(1,3),NULL_EXPR,0)

#define	ZCOMPEXP		*res	=	op[2];
DEFLINKFUNC(Zcomp1		,"zcomp"		,"f=p", 0)
DEFLINKFUNC(Zcomp2		,"zcomp"		,"f=n", 0)
DEFFUNC(ZComp			,"zcomp"		,"f=v",FUN2EXPR_PRE,ZCOMPEXP,FUN2EXPR_UPDATE(1,3),NULL_EXPR,0)



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// setxcomp "o=Vf"
#define	SETXCOMPEXP			res[0]	=	*op;
#define	SETYCOMPEXP			res[1]	=	*op;
#define	SETZCOMPEXP			res[2]	=	*op;

DEFLINKFUNC(SetXcomp1		,"setxcomp"		,"o=Pf", 0)
DEFLINKFUNC(SetXcomp2		,"setxcomp"		,"o=Nf", 0)
DEFFUNC(SetXComp			,"setxcomp"		,"o=Vf",FUN2EXPR_PRE,SETXCOMPEXP,FUN2EXPR_UPDATE(3,1),NULL_EXPR,0)
DEFLINKFUNC(SetYcomp1		,"setycomp"		,"o=Pf", 0)
DEFLINKFUNC(SetYcomp2		,"setycomp"		,"o=Nf", 0)
DEFFUNC(SetYComp			,"setycomp"		,"o=Vf",FUN2EXPR_PRE,SETYCOMPEXP,FUN2EXPR_UPDATE(3,1),NULL_EXPR,0)
DEFLINKFUNC(SetZcomp1		,"setzcomp"		,"o=Pf", 0)
DEFLINKFUNC(SetZcomp2		,"setzcomp"		,"o=Nf", 0)
DEFFUNC(SetZComp			,"setzcomp"		,"o=Vf",FUN2EXPR_PRE,SETZCOMPEXP,FUN2EXPR_UPDATE(3,1),NULL_EXPR,0)

#define	COMPEXP				*res		=	op1[(int) *op2];
DEFLINKFUNC(Comp1		,"comp"		,"f=pf", 0)
DEFLINKFUNC(Comp2		,"comp"		,"f=nf", 0)
DEFLINKFUNC(Comp3		,"comp"		,"f=cf", 0)
DEFFUNC(Comp			,"comp"		,"f=vf"	,FUN3EXPR_PRE,COMPEXP,FUN3EXPR_UPDATE(1,3,1),NULL_EXPR,0)

#define	MCOMPEXP		*res			=	op1[((int) *op2)*4 + ((int) *op3)];
DEFFUNC(MComp			,"comp"		,"f=mff",FUN4EXPR_PRE,MCOMPEXP,FUN4EXPR_UPDATE(1,16,1,1),NULL_EXPR,0)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// setcomp "o=Vff"
#define	SETCOMPEXP			res[(int) *op1]	=	*op2;

DEFLINKFUNC(SetComp1	,"setcomp"		,"o=Pff", 0)
DEFLINKFUNC(SetComp2	,"setcomp"		,"o=Nff", 0)
DEFLINKFUNC(SetComp3	,"setcomp"		,"o=Cff", 0)
DEFFUNC(SetComp			,"setcomp"		,"o=Vff",FUN3EXPR_PRE,SETCOMPEXP,FUN3EXPR_UPDATE(3,1,1),NULL_EXPR,0)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// setcomp "o=Mfff"
#define	SETMCOMPEXP			res[element((int) *op1,(int) *op2)]	=	*op3;
DEFFUNC(SetMComp			,"setcomp"		,"o=Mfff",FUN4EXPR_PRE,SETMCOMPEXP,FUN4EXPR_UPDATE(16,1,1,1),NULL_EXPR,0)

#define	LENGTHEXP			*res	=	lengthv(op);
DEFLINKFUNC(Length3	,"length"		,"f=c", 0)
DEFLINKFUNC(Length1	,"length"		,"f=p", 0)
DEFLINKFUNC(Length2	,"length"		,"f=n", 0)
DEFFUNC(Length		,"length"		,"f=v"	,FUN2EXPR_PRE,LENGTHEXP,FUN2EXPR_UPDATE(1,3),NULL_EXPR,0)

#define	NORMALIZEXP			if (dotvv(op,op) > 0) normalizev(res,op);	else initv(res,0,0,0);
DEFLINKFUNC(Normalize3	,"normalize"		,"c=c", 0)
DEFLINKFUNC(Normalize1	,"normalize"		,"p=p", 0)
DEFLINKFUNC(Normalize2	,"normalize"		,"n=n", 0)
DEFFUNC(Normalize		,"normalize"		,"v=v"	,FUN2EXPR_PRE,NORMALIZEXP,FUN2EXPR_UPDATE(3,3),NULL_EXPR,0)

#define	DISTANCEEXP_PRE		FUN3EXPR_PRE;							\
							vector	vtmp;

#define	DISTANCEEXP			subvv(vtmp,op1,op2);					\
							*res	=	lengthv(vtmp);

DEFFUNC(Distance		,"distance"			,"f=pp"	,DISTANCEEXP_PRE,DISTANCEEXP,FUN3EXPR_UPDATE(1,3,3),NULL_EXPR,0)



// Point to line distance
#define	PTLINEDEXP_PRE		FUN4EXPR_PRE											\
							vector		vtmp,vtmp2,vtmp3;							\
							float		l;

#define	PTLINEDEXP			const float *ftmp	=	op1;							\
							const float *ftmp2	=	op2;							\
							const float *ftmp3	=	op3;							\
																					\
							subvv(vtmp,ftmp3,ftmp2);								\
							subvv(vtmp2,ftmp,ftmp2);								\
							if (dotvv(vtmp,vtmp2) <= 0) {							\
								l	=	sqrtf(dotvv(vtmp,vtmp));					\
							} else {												\
								mulvf(vtmp2,-1);									\
								subvv(vtmp,ftmp3,ftmp);								\
								if (dotvv(vtmp,vtmp2) <= 0) {						\
									l = sqrtf(dotvv(vtmp,vtmp));					\
								} else {											\
									subvv(vtmp,ftmp2,ftmp);							\
									subvv(vtmp2,ftmp2,ftmp3);						\
									crossvv(vtmp3,vtmp,vtmp2);						\
									l = sqrtf(dotvv(vtmp3,vtmp3))/sqrtf(dotvv(vtmp,vtmp));	\
								}													\
							}														\
							*res	=	l;

DEFFUNC(Ptlined		,"ptlined"			,"f=ppp"	,PTLINEDEXP_PRE,PTLINEDEXP,FUN4EXPR_UPDATE(1,3,3,3),NULL_EXPR,0)


#define	ROTATEEXP_PRE	FUN5EXPR_PRE;												\
						vector	vtmp,vtmp2;											\
						matrix	mtmp;

#define	ROTATEEXP		subvv(vtmp,op4,op3);										\
						rotatem(mtmp,vtmp,*op2);									\
						subvv(vtmp2,op1,op3);										\
						mulmp(vtmp,mtmp,vtmp2);										\
						addvv(res,vtmp,op3);

DEFFUNC(Rotatep		,"rotate"			,"p=pfpp"	,ROTATEEXP_PRE,ROTATEEXP,FUN5EXPR_UPDATE(3,3,1,3,3),NULL_EXPR,0)

#define	REFLECTEXP	reflect(res,op1,op2);
					

DEFFUNC(Reflect		,"reflect"			,"v=vv"	,FUN3EXPR_PRE,REFLECTEXP,FUN3EXPR_UPDATE(3,3,3),NULL_EXPR,0)

#define	REFRACTEXP	::refract(res,op1,op2,*op3);

DEFFUNC(Refract		,"refract"			,"v=vvf"	,FUN4EXPR_PRE,REFRACTEXP,FUN4EXPR_UPDATE(3,3,3,1),NULL_EXPR,0)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// fresnel "o=vvfFF"
#define	FRESNELEXP		vector	dummy0,dummy1;															\
						fresnel(res,op1,*op2,*op3,*op4,dummy0,dummy1);




DEFFUNC(Fresnel			,"fresnel"		,"o=vvfFF",FUN5OUTEXPR_PRE,FRESNELEXP,FUN5EXPR_UPDATE(3,3,1,1,1),NULL_EXPR,0)


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// fresnel "o=vvfFFVV"
#define	FRESNEL7EXPR_PRE	float	*op[7];																\
																										\
							for (int i=0;i<7;++i) {														\
								operand(i,op[i],float *);												\
							}

#define FRESNEL7EXPR		fresnel(op[0],op[1],*op[2],*op[3],*op[4],op[5],op[6]);

#define	FRESNEL7EXPR_UPDATE		op[0]	+=	3;															\
								op[1]	+=	3;															\
								op[2]	+=	1;															\
								op[3]	+=	1;															\
								op[4]	+=	1;															\
								op[5]	+=	3;															\
								op[6]	+=	3;


DEFFUNC(Fresnel2		,"fresnel"		,"o=vvfFFVV",FRESNEL7EXPR_PRE,FRESNEL7EXPR,FRESNEL7EXPR_UPDATE,NULL_EXPR,0)

#define	DETERMINANTEXP		*res	=	determinantm(op);

DEFFUNC(Determinant		,"determinant"			,"f=m"	,FUN2EXPR_PRE,DETERMINANTEXP,FUN2EXPR_UPDATE(1,16),NULL_EXPR,0)


#define	TRANSLATEEXP_PRE	FUN3EXPR_PRE;									\
							matrix	mtmp;

#define	TRANSLATEEXP		translatem(mtmp,op2[0],op2[1],op2[2]);			\
							mulmm(res,op1,mtmp);

DEFFUNC(Translatem		,"translate"			,"m=mp"	,TRANSLATEEXP_PRE,TRANSLATEEXP,FUN3EXPR_UPDATE(16,16,3),NULL_EXPR,0)

#define	ROTATEEXPR_PRE		FUN4EXPR_PRE;									\
							matrix	mtmp;

#define	ROTATEEXPR			rotatem(mtmp,op3[0],op3[1],op3[2],*op2);		\
							mulmm(res,op1,mtmp);

DEFFUNC(Rotatem			,"rotate"				,"m=mfv"	,ROTATEEXPR_PRE,ROTATEEXPR,FUN4EXPR_UPDATE(16,16,1,3),NULL_EXPR,0)

#define	SCALEEXPR_PRE		FUN3EXPR_PRE;									\
							matrix	mtmp;

#define	SCALEEXPR			scalem(mtmp,op2[0],op2[1],op2[2]);				\
							mulmm(res,op1,mtmp);

DEFFUNC(Scalem			,"scale"				,"m=mp"		,SCALEEXPR_PRE,SCALEEXPR,FUN3EXPR_UPDATE(16,16,3),NULL_EXPR,0)


#define	MINFEXPR_PRE		float		*res;												\
							const float	**op;												\
							int			numArguments;										\
							float		min;												\
																							\
							operand(0,res,float *);											\
							argumentcount(numArguments);									\
							--numArguments;													\
							op		=	(const float **) ralloc(numArguments*sizeof(float *),threadMemory);	\
																							\
							for (int i=0;i<numArguments;++i) {								\
								operand(i+1,op[i],const float *);							\
							}

#define	MINFEXPR			min	=	*op[0];													\
							for (int i=1;i<numArguments;++i) {								\
								if (*op[i] < min)	min = *op[i];							\
							}																\
							*res	=	min;

#define	MINFEXPR_UPDATE		++res;															\
							for (int i=0;i<numArguments;++i)								\
								++op[i];

#define	MINFEXPR_POST

DEFFUNC(Minf				,"min"						,"f=f+"		,MINFEXPR_PRE,MINFEXPR,MINFEXPR_UPDATE,MINFEXPR_POST,0)

#define	MINVEXPR_PRE		float		*res;												\
							const float	**op;												\
							int			numArguments;										\
							float		minx,miny,minz;										\
																							\
							operand(0,res,float *);											\
							argumentcount(numArguments);									\
							numArguments--;													\
							op		=	(const float **) ralloc(numArguments*sizeof(float *),threadMemory);	\
																							\
							for (int i=0;i<numArguments;++i) {								\
								operand(i+1,op[i],const float *);							\
							}

#define	MINVEXPR			minx	=	op[0][0];											\
							miny	=	op[0][1];											\
							minz	=	op[0][2];											\
							for (int i=1;i<numArguments;++i) {								\
								if (op[i][0] < minx)	minx = op[i][0];					\
								if (op[i][1] < miny)	miny = op[i][1];					\
								if (op[i][2] < minz)	minz = op[i][2];					\
							}																\
							res[0]	=	minx;												\
							res[1]	=	miny;												\
							res[2]	=	minz;

#define	MINVEXPR_UPDATE		res	+=	3;														\
							for (int i=0;i<numArguments;++i)								\
								op[i]	+=	3;

#define	MINVEXPR_POST

DEFFUNC(Minv				,"min"						,"v=v+"		,MINVEXPR_PRE,MINVEXPR,MINVEXPR_UPDATE,MINVEXPR_POST,0)

#define	MAXFEXPR_PRE		float		*res;												\
							const float	**op;												\
							int			numArguments;										\
							float		max;												\
																							\
							operand(0,res,float *);											\
							argumentcount(numArguments);									\
							numArguments--;													\
							op		=	(const float **) ralloc(numArguments*sizeof(float *),threadMemory);	\
																							\
							for (int i=0;i<numArguments;++i) {								\
								operand(i+1,op[i],const float *);							\
							}

#define	MAXFEXPR			max	=	*op[0];													\
							for (int i=1;i<numArguments;++i) {								\
								if (*op[i] > max)	max = *op[i];							\
							}																\
							*res	=	max;

#define	MAXFEXPR_UPDATE		++res;															\
							for (int i=0;i<numArguments;++i)								\
								++op[i];

#define	MAXFEXPR_POST

DEFFUNC(Maxf				,"max"						,"f=f+"		,MAXFEXPR_PRE,MAXFEXPR,MAXFEXPR_UPDATE,MAXFEXPR_POST,0)


#define	MAXVEXPR_PRE		float		*res;												\
							const float	**op;												\
							int			numArguments;										\
							float		maxx,maxy,maxz;										\
																							\
							operand(0,res,float *);											\
							argumentcount(numArguments);									\
							numArguments--;													\
							op		=	(const float **) ralloc(numArguments*sizeof(float *),threadMemory);	\
																							\
							for (int i=0;i<numArguments;++i) {								\
								operand(i+1,op[i],const float *);							\
							}

#define	MAXVEXPR			maxx	=	op[0][0];											\
							maxy	=	op[0][1];											\
							maxz	=	op[0][2];											\
							for (int i=1;i<numArguments;++i) {								\
								if (op[i][0] > maxx)	maxx = op[i][0];					\
								if (op[i][1] > maxy)	maxy = op[i][1];					\
								if (op[i][2] > maxz)	maxz = op[i][2];					\
							}																\
							res[0]	=	maxx;												\
							res[1]	=	maxy;												\
							res[2]	=	maxz;

#define	MAXVEXPR_UPDATE		res	+=	3;														\
							for (int i=0;i<numArguments;++i)								\
								op[i]	+=	3;

#define	MAXVEXPR_POST

DEFFUNC(Maxv				,"max"						,"v=v+"		,MAXVEXPR_PRE,MAXVEXPR,MAXVEXPR_UPDATE,MAXVEXPR_POST,0)



#define	CONCATEXPR_PRE		char		tmp[MAX_SCRIPT_STRING_SIZE];									\
							char		**res;															\
							const char	***op;															\
							int			numArguments;													\
							argumentcount(numArguments);												\
							numArguments--;																\
							operand(0,res,char **);														\
							op	=	(const char ***) ralloc(numArguments*sizeof(char **),threadMemory);	\
							for (int i=0;i<numArguments;++i) {												\
								operand(i+1,op[i],const char **);										\
							}

#define CONCATEXPR			strcpy(tmp,*op[0]);															\
							for (int i=1;i<numArguments;++i)	strcat(tmp,*op[i]);							\
							savestring(*res,tmp);

#define	CONCATEXPR_UPDATE	res++;																		\
							for (int i=0;i<numArguments;++i)	op[i]++;


DEFFUNC(Concat				,"concat"						,"s=ss*"		,CONCATEXPR_PRE,CONCATEXPR,CONCATEXPR_UPDATE,NULL_EXPR,0)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// match	"f=ss"
// FIXME: Subpattern matching is not implemented yet
#define FUN3SEXPR_PRE		float		*res;										\
							const char	**op1,**op2;								\
							operand(0,res,float *);									\
							operand(1,op1,const char **);							\
							operand(2,op2,const char **);

#define MATCHEXPR			if (strcmp(*op1,*op2) == 0)								\
								*res	=	1;										\
							else													\
								*res	=	0;

DEFFUNC(Match				,"match"						,"f=ss"		,FUN3SEXPR_PRE,MATCHEXPR,FUN3EXPR_UPDATE(1,1,1),NULL_EXPR,0)



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// printf	"o=s.*"
#define	PRINTEXPR(r,s,af,as)	const char	*str;												\
								char		*tmp;												\
								int			cp	=	-1;											\
								tmp	=	r;														\
								str =   *s;														\
								while(*str != '\0')	{											\
									if (*str == '%') {											\
										str++;													\
										if (*str == '\0') break;								\
										if (*str == 'f') {										\
											cp++;												\
											sprintf(tmp,"%f",*af[cp]);							\
										} else if (*str == 'd') {								\
											cp++;												\
											sprintf(tmp,"%d",(int) *af[cp]);					\
										} else if (*str == 'c') {								\
											cp++;												\
											sprintf(tmp,"(%f,%f,%f)",af[cp][0],af[cp][1],af[cp][2]);		\
										} else if (*str == 'n') {								\
											cp++;												\
											sprintf(tmp,"(%f,%f,%f)",af[cp][0],af[cp][1],af[cp][2]);		\
										} else if (*str == 'p') {								\
											cp++;												\
											sprintf(tmp,"(%f,%f,%f)",af[cp][0],af[cp][1],af[cp][2]);		\
										} else if (*str == 's') {								\
											cp++;												\
											sprintf(tmp,"%s",*as[cp]);					\
										} else if (*str == 'm') {								\
											cp++;												\
											sprintf(tmp,"((%f,%f,%f,%f),(%f,%f,%f,%f),(%f,%f,%f,%f),(%f,%f,%f,%f))",af[cp][0],af[cp][1],af[cp][2],af[cp][3],af[cp][4],af[cp][5],af[cp][6],af[cp][7],af[cp][8],af[cp][9],af[cp][10],af[cp][11],af[cp][12],af[cp][13],af[cp][14],af[cp][15]);		\
										} else {												\
											*tmp	=	*str;									\
											tmp++;												\
										}														\
										str++;													\
										tmp	=	strchr(tmp,'\0');								\
									} else {													\
										*tmp	=	*str;										\
										tmp++;													\
										str++;													\
									}															\
								}																\
								*tmp	=	'\0';

#ifndef INIT_SHADING
#define PRINTFEXPR_PRE		char		output[MAX_SCRIPT_STRING_SIZE];							\
							char		**res;													\
							const float	**opf;													\
							const char	***ops;													\
							int			*opSteps;												\
							int			resStep;												\
							int			numArguments;											\
							int			numRealVertices = currentShadingState->numRealVertices;	\
							int			vertexN	=	0;											\
																								\
							operandSize(0,res,resStep,char **);									\
							argumentcount(numArguments);										\
							numArguments--;														\
							opf		=	(const float **)	ralloc(numArguments*sizeof(float *),threadMemory);	\
							ops		=	(const char ***)	ralloc(numArguments*sizeof(char **),threadMemory);	\
							opSteps	=	(int *)				ralloc(numArguments*sizeof(int),threadMemory);		\
																								\
							for (int i=0;i<numArguments;++i) {									\
								operandSize(i+1,ops[i],opSteps[i],const char **);				\
								operandSize(i+1,opf[i],opSteps[i],const float *);				\
							}

#define	PRINTFEXPR			if (vertexN < numRealVertices) {									\
								PRINTEXPR(output,res,opf,ops);									\
								printf(output);													\
							}

#define	PRINTF_UPDATE		res	+=	resStep;													\
							for (int i=0;i<numArguments;++i) {									\
								opf[i]	+=	opSteps[i];											\
								ops[i]	+=	opSteps[i];											\
							}																	\
							vertexN++;															\

#define	PRINTF_POST
#else
#undef	PRINTFEXPR_PRE
#undef	PRINTFEXPR
#undef	PRINTF_UPDATE
#undef	PRINTF_POST

#define PRINTFEXPR_PRE

#define	PRINTFEXPR

#define	PRINTF_UPDATE

#define	PRINTF_POST

#endif

DEFFUNC(Printf				,"printf"						,"o=s.*"		,PRINTFEXPR_PRE,PRINTFEXPR,PRINTF_UPDATE,PRINTF_POST,0)

#undef PRINTFEXPR


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// format	"s=s.*"
#define FORMATEXPR_PRE		char		output[MAX_SCRIPT_STRING_SIZE];							\
							char		**res,**strArg;											\
							const float	**opf;													\
							const char	***ops;													\
							int			*opSteps;												\
							int			resStep,strStep;										\
							int			numArguments;											\
																								\
							operandSize(0,res,resStep,char **);									\
							operandSize(1,strArg,strStep,char **);								\
							argumentcount(numArguments);										\
							numArguments--;														\
							numArguments--;														\
							opf		=	(const float **)	ralloc(numArguments*sizeof(float *),threadMemory);	\
							ops		=	(const char ***)	ralloc(numArguments*sizeof(char **),threadMemory);	\
							opSteps	=	(int *)				ralloc(numArguments*sizeof(int),threadMemory);		\
																								\
							for (int i=0;i<numArguments;++i) {									\
								operandSize(i+2,opf[i],opSteps[i],const float *);				\
								operandSize(i+2,ops[i],opSteps[i],const char **);				\
							}

#define	FORMATEXPR			PRINTEXPR(output,strArg,opf,ops);									\
							savestring(*res,output);


#define	FORMAT_UPDATE		res	+=	resStep;												\
							strArg +=	strStep;											\
							for (int i=0;i<numArguments;++i) {								\
								opf[i]	+=	opSteps[i];										\
								ops[i]	+=	opSteps[i];										\
							}

#define	FORMAT_POST

DEFFUNC(Format					,"format"						,"s=s.*"		,FORMATEXPR_PRE,FORMATEXPR,FORMAT_UPDATE,FORMAT_POST,0)


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// spline	"f=Sfffff*"
// spline	"f=fffff*"
#define SPLINEPARAMETERS()		

#ifndef INIT_SHADING

#define	SPLINEVEXPR_PRE		float		*res;													\
							const float	**op;													\
							int			numArguments;											\
							const float *val;													\
							const char	**splineType;											\
							float		ub[4],tmp[4];											\
							const float	*ubasis = (float*) RiCatmullRomBasis;					\
							int			ustep = 1;												\
							int			numPieces;												\
																								\
							operand(1,splineType,const char **);								\
							ubasis 	=	(float*) RiCatmullRomBasis;								\
							ustep	=	1;														\
							if (!strcmp(*splineType,"catmull-rom")) {							\
								/* do nothing */												\
							} else if (!strcmp(*splineType,"bezier")) {							\
								ubasis 	=	(float*) RiBezierBasis;								\
								ustep	=	3;													\
							} else if (!strcmp(*splineType,"bspline")) {						\
								ubasis 	=	(float*) RiBSplineBasis;							\
								ustep	=	1;													\
							} else if (!strcmp(*splineType,"hermite")) {						\
								ubasis 	=	(float*) RiHermiteBasis;							\
								ustep	=	2;													\
							} else if (!strcmp(*splineType,"linear")) {							\
								ubasis 	=	(float*) RiLinearBasis;								\
								ustep	=	2;													\
							} else {															\
								error(CODE_BADTOKEN,"Unknown spline basis \"%s\"\n",*splineType);	\
							}																	\
																								\
							operand(0,res,float *);												\
							operand(2,val,const float *);										\
							argumentcount(numArguments);										\
							numArguments-=3;													\
							op		=	(const float **) ralloc(numArguments*sizeof(float *),threadMemory);	\
							numPieces = (numArguments-4)/ustep+1;								\
																								\
							for (int i=0;i<numArguments;++i) {									\
								operand(i+3,op[i],float *);										\
							}


#define	SPLINEEXPR_PRE		float		*res;													\
							const float	**op;													\
							int			numArguments;											\
							const float	*val;													\
							float		ub[4],tmp[4];											\
							const float	*ubasis = (float*) RiCatmullRomBasis;					\
							int			ustep = 1;												\
							int			numPieces;												\
																								\
							operand(0,res,float *);												\
							operand(1,val,const float *);										\
							argumentcount(numArguments);										\
							numArguments--;														\
							numArguments--;														\
							op		=	(const float **) ralloc(numArguments*sizeof(float *),threadMemory);	\
							numPieces = (numArguments-3);										\
																								\
							for (int i=0;i<numArguments;++i) {									\
								operand(i+2,op[i],const float *);								\
							}

#define	SPLINEFEXPR			if (*val <= 0)		*res	=	*op[1];										\
							else if (*val >= 1)	*res	=	*op[numArguments-2];						\
							else {																		\
								int		piece	=	(int) floor(*val * (float) numPieces);				\
								int		pieceid	=	piece*ustep;										\
								float	u		=	(*val)*((float) numPieces) - (float) piece;			\
								ub[3] = 1;																\
								ub[2] =	u;																\
								ub[1] =	u*u;															\
								ub[0] =	u*ub[2];														\
																										\
								tmp[0]	=	ub[0]*ubasis[element(0,0)] + ub[1]*ubasis[element(0,1)] + ub[2]*ubasis[element(0,2)] + ub[3]*ubasis[element(0,3)];	\
								tmp[1]	=	ub[0]*ubasis[element(1,0)] + ub[1]*ubasis[element(1,1)] + ub[2]*ubasis[element(1,2)] + ub[3]*ubasis[element(1,3)];	\
								tmp[2]	=	ub[0]*ubasis[element(2,0)] + ub[1]*ubasis[element(2,1)] + ub[2]*ubasis[element(2,2)] + ub[3]*ubasis[element(2,3)];	\
								tmp[3]	=	ub[0]*ubasis[element(3,0)] + ub[1]*ubasis[element(3,1)] + ub[2]*ubasis[element(3,2)] + ub[3]*ubasis[element(3,3)];	\
																										\
								*res	=	tmp[0]*op[pieceid+0][0] +									\
											tmp[1]*op[pieceid+1][0] +									\
											tmp[2]*op[pieceid+2][0] +									\
											tmp[3]*op[pieceid+3][0];									\
							}																			\


#define	SPLINEFEXPR_UPDATE	++res;																		\
							++val;																		\
							for (int i=0;i<numArguments;++i)											\
								++op[i];

#define	SPLINEFEXPR_POST

#else

#undef	SPLINEVEXPR_PRE
#undef	SPLINEEXPR_PRE
#undef	SPLINEFEXPR
#undef	SPLINEFEXPR_UPDATE
#undef	SPLINEFEXPR_POST

#define	SPLINEVEXPR_PRE
#define	SPLINEEXPR_PRE
#define	SPLINEFEXPR
#define	SPLINEFEXPR_UPDATE
#define	SPLINEFEXPR_POST

#endif

DEFFUNC(Splinef					,"spline"						,"f=fffff*"		,SPLINEEXPR_PRE,SPLINEFEXPR,SPLINEFEXPR_UPDATE,SPLINEFEXPR_POST,0)
DEFFUNC(Splinesf				,"spline"						,"f=Sfffff*"	,SPLINEVEXPR_PRE,SPLINEFEXPR,SPLINEFEXPR_UPDATE,SPLINEFEXPR_POST,0)


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// spline	"p=fpppp*"
// spline	"p=Sfpppp*"

#ifndef INIT_SHADING

#define	SPLINEPEXPR			if (*val <= 0)			movvv(res,op[1]);									\
							else if (*val >= 1)		movvv(res,op[numArguments-2]);						\
							else {																		\
								const int	piece	=	(int) floor((*val) * (float) numPieces);		\
								const int	pieceid	=	piece*ustep;									\
								const float	u		=	(*val)*((float) numPieces) - (float) piece;		\
								ub[3] = 1;																\
								ub[2] =	u;																\
								ub[1] =	u*u;															\
								ub[0] =	u*ub[2];														\
																										\
								tmp[0]	=	ub[0]*ubasis[element(0,0)] + ub[1]*ubasis[element(0,1)] + ub[2]*ubasis[element(0,2)] + ub[3]*ubasis[element(0,3)];	\
								tmp[1]	=	ub[0]*ubasis[element(1,0)] + ub[1]*ubasis[element(1,1)] + ub[2]*ubasis[element(1,2)] + ub[3]*ubasis[element(1,3)];	\
								tmp[2]	=	ub[0]*ubasis[element(2,0)] + ub[1]*ubasis[element(2,1)] + ub[2]*ubasis[element(2,2)] + ub[3]*ubasis[element(2,3)];	\
								tmp[3]	=	ub[0]*ubasis[element(3,0)] + ub[1]*ubasis[element(3,1)] + ub[2]*ubasis[element(3,2)] + ub[3]*ubasis[element(3,3)];	\
																										\
								res[0]		=	tmp[0]*op[pieceid+0][0] +								\
												tmp[1]*op[pieceid+1][0] +								\
												tmp[2]*op[pieceid+2][0] +								\
												tmp[3]*op[pieceid+3][0];								\
																										\
								res[1]		=	tmp[0]*op[pieceid+0][1] +								\
												tmp[1]*op[pieceid+1][1] +								\
												tmp[2]*op[pieceid+2][1] +								\
												tmp[3]*op[pieceid+3][1];								\
																										\
								res[2]		=	tmp[0]*op[pieceid+0][2] +								\
												tmp[1]*op[pieceid+1][2] +								\
												tmp[2]*op[pieceid+2][2] +								\
												tmp[3]*op[pieceid+3][2];								\
							}																			\


#define	SPLINEPEXPR_UPDATE	res	+=	3;																	\
							val +=	1;																	\
							for (int i=0;i<numArguments;++i)											\
								op[i]	+=	3;

#define	SPLINEPEXPR_POST

#else

#undef	SPLINEPEXPR
#undef	SPLINEPEXPR_UPDATE
#undef	SPLINEPEXPR_POST


#define	SPLINEPEXPR
#define	SPLINEPEXPR_UPDATE
#define	SPLINEPEXPR_POST

#endif

DEFLINKFUNC(Splinec		,"spline"		,"c=fcccc*", 0)
DEFLINKFUNC(Splinev		,"spline"		,"v=fvvvv*", 0)
DEFLINKFUNC(Splinen		,"spline"		,"n=fnnnn*", 0)
DEFFUNC(Splinep			,"spline"		,"p=fpppp*"		,SPLINEEXPR_PRE,SPLINEPEXPR,SPLINEPEXPR_UPDATE,SPLINEPEXPR_POST,0)

DEFLINKFUNC(VSplinec	,"spline"		,"c=Sfcccc*", 0)
DEFLINKFUNC(VSplinev	,"spline"		,"v=Sfvvvv*", 0)
DEFLINKFUNC(VSplinen	,"spline"		,"n=Sfnnnn*", 0)
DEFFUNC(VSplinep		,"spline"		,"p=Sfpppp*"	,SPLINEVEXPR_PRE,SPLINEPEXPR,SPLINEPEXPR_UPDATE,SPLINEPEXPR_POST,0)






///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// spline	"p=fP"
#define	SPLINEAPEXPR_PRE	float		*res;													\
							const float	*op;													\
							int			numArguments;											\
							const float	*val;													\
							float		ub[4],tmp[4];											\
							const float	*ubasis = (float*) RiCatmullRomBasis;					\
							int			ustep = 1;												\
							int			numPieces;												\
																								\
							operand(0,res,float *);												\
							operand(1,val,const float *);										\
							operandSize(2,op,numArguments,const float *);						\
							numArguments	/=	3;												\
							numPieces		=	(numArguments-3);


#define	SPLINEAPEXPR		if (*val <= 0)				movvv(res,&op[3]);						\
							else if (*val >= 1)			movvv(res,&op[(numArguments-2)*3]);		\
							else {																		\
								const int	piece	=	(int) floor((*val) * (float) numPieces);		\
								const int	pieceid	=	piece*ustep;									\
								const float	u		=	(*val)*((float) numPieces) - (float) piece;		\
								ub[3] = 1;																\
								ub[2] =	u;																\
								ub[1] =	u*u;															\
								ub[0] =	u*ub[2];														\
																										\
								tmp[0]	=	ub[0]*ubasis[element(0,0)] + ub[1]*ubasis[element(0,1)] + ub[2]*ubasis[element(0,2)] + ub[3]*ubasis[element(0,3)];	\
								tmp[1]	=	ub[0]*ubasis[element(1,0)] + ub[1]*ubasis[element(1,1)] + ub[2]*ubasis[element(1,2)] + ub[3]*ubasis[element(1,3)];	\
								tmp[2]	=	ub[0]*ubasis[element(2,0)] + ub[1]*ubasis[element(2,1)] + ub[2]*ubasis[element(2,2)] + ub[3]*ubasis[element(2,3)];	\
								tmp[3]	=	ub[0]*ubasis[element(3,0)] + ub[1]*ubasis[element(3,1)] + ub[2]*ubasis[element(3,2)] + ub[3]*ubasis[element(3,3)];	\
																										\
								res[0]		=	tmp[0]*op[(pieceid+0)*3+0] +							\
												tmp[1]*op[(pieceid+1)*3+0] +							\
												tmp[2]*op[(pieceid+2)*3+0] +							\
												tmp[3]*op[(pieceid+3)*3+0];								\
																										\
								res[1]		=	tmp[0]*op[(pieceid+0)*3+1] +							\
												tmp[1]*op[(pieceid+1)*3+1] +							\
												tmp[2]*op[(pieceid+2)*3+1] +							\
												tmp[3]*op[(pieceid+3)*3+1];								\
																										\
								res[2]		=	tmp[0]*op[(pieceid+0)*3+2] +							\
												tmp[1]*op[(pieceid+1)*3+2] +							\
												tmp[2]*op[(pieceid+2)*3+2] +							\
												tmp[3]*op[(pieceid+3)*3+2];								\
																										\
							}																			\

#define	SPLINEAPEXPR_UPDATE	res	+=	3;																	\
							val +=	1;																	\
							op	+=	numArguments*3;



DEFLINKFUNC(Splineac		,"spline"		,"c=fC", 0)
DEFLINKFUNC(Splineav		,"spline"		,"v=fV", 0)
DEFLINKFUNC(Splinean		,"spline"		,"n=fN", 0)
DEFFUNC(Splineap			,"spline"		,"p=fP"		,SPLINEAPEXPR_PRE,SPLINEAPEXPR,SPLINEAPEXPR_UPDATE,NULL_EXPR,0)


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DSO dispatcher
#define	DSOEXEC_PRE			int					numArguments;								\
							char				**op;										\
							int					*opSteps;									\
																							\
							argumentcount(numArguments);									\
																							\
							op		=	(char **)	ralloc(numArguments*sizeof(char *),threadMemory);	\
							opSteps	=	(int *)		ralloc(numArguments*sizeof(int),threadMemory);		\
																							\
							for (int i=0;i<numArguments;++i) {								\
								operandSize(i,op[i],opSteps[i],char *);						\
								opSteps[i]	*=	operandBytesPerItem(i);						\
							}																\
																							\
							void			*handle	=	code->dso->handle;					\
							dsoExecFunction exec	=	code->dso->exec;
						

#define	DSOEXEC				exec(handle,numArguments-1,(void **) op);

#define	DSOEXEC_UPDATE		for (int i=0;i<numArguments;++i) {								\
								op[i]	+=	opSteps[i];										\
							}

#define	DSOEXEC_POST

DEFFUNC(DSO				,"XXX",			"XXX",	DSOEXEC_PRE,DSOEXEC,DSOEXEC_UPDATE,DSOEXEC_POST,0)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VOID DSO dispatcher
#define	DSOVOIDEXEC_PRE		int					numArguments;								\
							float				**op;										\
							int					*opSteps;									\
																							\
							argumentcount(numArguments);									\
																							\
							op		=	(float **) ralloc((numArguments+1)*sizeof(float *),threadMemory);	\
							opSteps	=	(int *)	   ralloc((numArguments+1)*sizeof(int),threadMemory);		\
																							\
							for (int i=0;i<numArguments;++i) {								\
								operandSize(i,op[i+1],opSteps[i+1],float *);				\
								opSteps[i+1]	*=	operandBytesPerItem(i);					\
							}																\
																							\
							void			*handle	=	code->dso->handle;					\
							dsoExecFunction exec	=	code->dso->exec;

#define	DSOVOIDEXEC			exec(handle,numArguments,(void **) op);

#define	DSOVOIDEXEC_UPDATE	for (int i=0;i<numArguments;++i) {								\
								op[i+1]	+=	opSteps[i+1];									\
							}

#define	DSOVOIDEXEC_POST

DEFFUNC(DSO_VOID				,"XXX",			"XXX",	DSOVOIDEXEC_PRE,DSOVOIDEXEC,DSOVOIDEXEC_UPDATE,DSOVOIDEXEC_POST,0)

// Include the RenderMan Shading Language specific built - in functions
#include "shaderFunctions.h"

