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

#define	FUN1EXPR_PRE		TCode	*res;									\
							operand(0,res);

#define	FUN1EXPR_UPDATE(__rs)												\
							res	+=	__rs;


#define	FUN2EXPR_PRE		TCode		*res;								\
							const TCode	*op;								\
							operand(0,res);									\
							operand(1,op);

#define	FUN2OUTEXPR_PRE		TCode		*res,*op;							\
							operand(0,res);									\
							operand(1,op);



#define	FUN2EXPR_UPDATE(__rs,__op1s)										\
							res	+=	__rs;									\
							op	+=	__op1s;


#define	FUN3EXPR_PRE		TCode		*res;								\
							const TCode	*op1,*op2;							\
							operand(0,res);									\
							operand(1,op1);									\
							operand(2,op2);

#define	FUN3OUTEXPR_PRE		TCode		*res,*op1,*op2;						\
							operand(0,res);									\
							operand(1,op1);									\
							operand(2,op2);


#define	FUN3EXPR_UPDATE(__rs,__op1s,__op2s)									\
							res	+=	__rs;									\
							op1	+=	__op1s;									\
							op2	+=	__op2s;


#define	FUN4EXPR_PRE		TCode		*res;								\
							const TCode	*op1,*op2,*op3;						\
							operand(0,res);									\
							operand(1,op1);									\
							operand(2,op2);									\
							operand(3,op3);

#define	FUN4OUTEXPR_PRE		TCode		*res,*op1,*op2,*op3;				\
							operand(0,res);									\
							operand(1,op1);									\
							operand(2,op2);									\
							operand(3,op3);


#define	FUN4EXPR_UPDATE(__rs,__op1s,__op2s,__op3s)							\
							res	+=	__rs;									\
							op1	+=	__op1s;									\
							op2	+=	__op2s;									\
							op3	+=	__op3s;

#define	FUN5EXPR_PRE		TCode		*res;								\
							const TCode	*op1,*op2,*op3,*op4;				\
							operand(0,res);									\
							operand(1,op1);									\
							operand(2,op2);									\
							operand(3,op3);									\
							operand(4,op4);

#define	FUN5OUTEXPR_PRE		TCode	*res,*op1,*op2,*op3,*op4;				\
							operand(0,res);									\
							operand(1,op1);									\
							operand(2,op2);									\
							operand(3,op3);									\
							operand(4,op4);


#define	FUN5EXPR_UPDATE(__rs,__op1s,__op2s,__op3s,__op4s)					\
							res	+=	__rs;									\
							op1	+=	__op1s;									\
							op2	+=	__op2s;									\
							op3	+=	__op3s;									\
							op4	+=	__op4s;

#define	SIMPLEFUNCTION		res->real	=	(float) FUNCTION(op->real);


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

#define	FUNCTION(x)	log(max(x,0))
DEFFUNC(Log			,"log"		,"f=f",FUN2EXPR_PRE,SIMPLEFUNCTION,FUN2EXPR_UPDATE(1,1),NULL_EXPR,0)
#undef	FUNCTION

#define	FUNCTION(x)	sqrt(max(x,0))
DEFFUNC(Sqrt		,"sqrt"		,"f=f",FUN2EXPR_PRE,SIMPLEFUNCTION,FUN2EXPR_UPDATE(1,1),NULL_EXPR,0)
#undef	FUNCTION

#define	FUNCTION(x)	isqrtf(x)
DEFFUNC(InvSqrt		,"invsqrt"		,"f=f",FUN2EXPR_PRE,SIMPLEFUNCTION,FUN2EXPR_UPDATE(1,1),NULL_EXPR,0)
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

#define	ATAN2EXP	res->real	=	atan2f(op1->real,op2->real);
DEFFUNC(Atan2		,"atan"			,"f=ff",FUN3EXPR_PRE,ATAN2EXP,FUN3EXPR_UPDATE(1,1,1),NULL_EXPR,0)

#define	POW2EXP		res->real	=	powf(op1->real,op2->real); if (res->real*res->real < 0) res->real = 0;
DEFFUNC(Pow2		,"pow"			,"f=ff",FUN3EXPR_PRE,POW2EXP,FUN3EXPR_UPDATE(1,1,1),NULL_EXPR,0)

#define	LOG2EXP		res->real	=	logf(op1->real) / logf(op2->real);
DEFFUNC(Log2		,"log"			,"f=ff",FUN3EXPR_PRE,LOG2EXP,FUN3EXPR_UPDATE(1,1,1),NULL_EXPR,0)

#define	MOD2EXP		res->real	=	fmodf(op1->real,op2->real); if (res->real < 0) res->real += op2->real; assert(res->real >= 0);
DEFFUNC(Mod2		,"mod"			,"f=ff",FUN3EXPR_PRE,MOD2EXP,FUN3EXPR_UPDATE(1,1,1),NULL_EXPR,0)

#define	CLAMPFEXP	res->real	=	(op1->real < op2->real ? op2->real: op1->real > op3->real ? op3->real : op1->real);
DEFFUNC(Clampf		,"clamp"		,"f=fff",FUN4EXPR_PRE,CLAMPFEXP,FUN4EXPR_UPDATE(1,1,1,1),NULL_EXPR,0)

#define	CLAMPVEXP	res[0].real	=	(op1[0].real < op2[0].real ? op2[0].real: op1[0].real > op3[0].real ? op3[0].real : op1[0].real);	\
					res[1].real	=	(op1[1].real < op2[1].real ? op2[1].real: op1[1].real > op3[1].real ? op3[1].real : op1[1].real);	\
					res[2].real	=	(op1[2].real < op2[2].real ? op2[2].real: op1[2].real > op3[2].real ? op3[2].real : op1[2].real);

DEFLINKFUNC(Clampp		,"clamp"		,	"p=ppp" , 0)
DEFLINKFUNC(Clampn		,"clamp"		,	"n=nnn"	, 0)
DEFLINKFUNC(Clampc		,"clamp"		,	"c=ccc"	, 0)
DEFFUNC(Clampv			,"clamp"		,	"v=vvv"	,FUN4EXPR_PRE,CLAMPVEXP,FUN4EXPR_UPDATE(3,3,3,3),NULL_EXPR,0)









#define	MIXFEXP		res[0].real	=	op1[0].real*(1-op3[0].real) + op2[0].real*op3[0].real;
DEFFUNC(Mixf		,"mix"		,"f=fff",FUN4EXPR_PRE,MIXFEXP,FUN4EXPR_UPDATE(1,1,1,1),NULL_EXPR,0)

#define	MIXVEXP		res[0].real	=	op1[0].real*(1-op3[0].real) + op2[0].real*op3[0].real;	\
					res[1].real	=	op1[1].real*(1-op3[0].real) + op2[1].real*op3[0].real;	\
					res[2].real	=	op1[2].real*(1-op3[0].real) + op2[2].real*op3[0].real;

DEFLINKFUNC(Mixc		,"mix"			,	"c=ccf", 0)
DEFLINKFUNC(Mixp		,"mix"			,	"p=ppf", 0)
DEFLINKFUNC(Mixn		,"mix"			,	"n=nnf", 0)
DEFFUNC(Mixv			,"mix"			,	"v=vvf",FUN4EXPR_PRE,MIXVEXP,FUN4EXPR_UPDATE(3,3,3,1),NULL_EXPR,0)

#define	MIXVVEXP	res[0].real	=	op1[0].real*(1-op3[0].real) + op2[0].real*op3[0].real;	\
					res[1].real	=	op1[1].real*(1-op3[1].real) + op2[1].real*op3[1].real;	\
					res[2].real	=	op1[2].real*(1-op3[2].real) + op2[2].real*op3[2].real;

DEFLINKFUNC(Mixcc		,"mix"			,	"c=ccc", 0)
DEFLINKFUNC(Mixpp		,"mix"			,	"p=ppp", 0)
DEFLINKFUNC(Mixnn		,"mix"			,	"n=nnn", 0)
DEFFUNC(Mixvv			,"mix"			,	"v=vvv",FUN4EXPR_PRE,MIXVVEXP,FUN4EXPR_UPDATE(3,3,3,3),NULL_EXPR,0)


#define	STEPEXP		res->real	=	(op2->real < op1->real ? 0.0f : 1.0f);
DEFFUNC(Stepf		,"step"		,"f=ff",FUN3EXPR_PRE,STEPEXP,FUN3EXPR_UPDATE(1,1,1),NULL_EXPR,0)


#define	SMOOTHSTEPEXP	if (op3->real < op1->real)		res->real	=	0;							\
						else if (op3->real > op2->real)	res->real	=	1;							\
						else {																		\
							float	u	=	(op3->real - op1->real) / (op2->real - op1->real);		\
							res->real	=	-2*u*u*u + 3*u*u;										\
						}

DEFFUNC(SmoothStepf		,"smoothstep"		,"f=fff",FUN4EXPR_PRE,SMOOTHSTEPEXP,FUN4EXPR_UPDATE(1,1,1,1),NULL_EXPR,0)

#define	RANDOMFEXP		res->real	=	urand();

#define	RANDOMVEXP		res[0].real	=	urand();	\
						res[1].real	=	urand();	\
						res[2].real	=	urand();

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

#define	XCOMPEXP		res->real	=	op[0].real;
DEFLINKFUNC(Xcomp1		,"xcomp"		,"f=p", 0)
DEFLINKFUNC(Xcomp2		,"xcomp"		,"f=n", 0)
DEFFUNC(XComp			,"xcomp"		,"f=v",FUN2EXPR_PRE,XCOMPEXP,FUN2EXPR_UPDATE(1,3),NULL_EXPR,0)

#define	YCOMPEXP		res->real	=	op[1].real;
DEFLINKFUNC(Ycomp1		,"ycomp"		,"f=p", 0)
DEFLINKFUNC(Ycomp2		,"ycomp"		,"f=n", 0)
DEFFUNC(YComp			,"ycomp"		,"f=v",FUN2EXPR_PRE,YCOMPEXP,FUN2EXPR_UPDATE(1,3),NULL_EXPR,0)

#define	ZCOMPEXP		res->real	=	op[2].real;
DEFLINKFUNC(Zcomp1		,"zcomp"		,"f=p", 0)
DEFLINKFUNC(Zcomp2		,"zcomp"		,"f=n", 0)
DEFFUNC(ZComp			,"zcomp"		,"f=v",FUN2EXPR_PRE,ZCOMPEXP,FUN2EXPR_UPDATE(1,3),NULL_EXPR,0)



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// setxcomp "o=Vf"
#define	SETXCOMPEXP			res[0].real	=	op->real;
#define	SETYCOMPEXP			res[1].real	=	op->real;
#define	SETZCOMPEXP			res[2].real	=	op->real;

DEFLINKFUNC(SetXcomp1		,"setxcomp"		,"o=Pf", 0)
DEFLINKFUNC(SetXcomp2		,"setxcomp"		,"o=Nf", 0)
DEFFUNC(SetXComp			,"setxcomp"		,"o=Vf",FUN2EXPR_PRE,SETXCOMPEXP,FUN2EXPR_UPDATE(3,1),NULL_EXPR,0)
DEFLINKFUNC(SetYcomp1		,"setycomp"		,"o=Pf", 0)
DEFLINKFUNC(SetYcomp2		,"setycomp"		,"o=Nf", 0)
DEFFUNC(SetYComp			,"setycomp"		,"o=Vf",FUN2EXPR_PRE,SETYCOMPEXP,FUN2EXPR_UPDATE(3,1),NULL_EXPR,0)
DEFLINKFUNC(SetZcomp1		,"setzcomp"		,"o=Pf", 0)
DEFLINKFUNC(SetZcomp2		,"setzcomp"		,"o=Nf", 0)
DEFFUNC(SetZComp			,"setzcomp"		,"o=Vf",FUN2EXPR_PRE,SETZCOMPEXP,FUN2EXPR_UPDATE(3,1),NULL_EXPR,0)

#define	COMPEXP				res->real		=	op1[(int) op2->real].real;
DEFLINKFUNC(Comp1		,"comp"		,"f=pf", 0)
DEFLINKFUNC(Comp2		,"comp"		,"f=nf", 0)
DEFLINKFUNC(Comp3		,"comp"		,"f=cf", 0)
DEFFUNC(Comp			,"comp"		,"f=vf"	,FUN3EXPR_PRE,COMPEXP,FUN3EXPR_UPDATE(1,3,1),NULL_EXPR,0)

#define	MCOMPEXP		res->real		=	op1[((int) op2->real)*4 + ((int) op3->real)].real;
DEFFUNC(MComp			,"comp"		,"f=mff",FUN4EXPR_PRE,MCOMPEXP,FUN4EXPR_UPDATE(1,16,1,1),NULL_EXPR,0)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// setcomp "o=Vff"
#define	SETCOMPEXP			res[(int) op1->real].real	=	op2->real;

DEFLINKFUNC(SetComp1	,"setcomp"		,"o=Pff", 0)
DEFLINKFUNC(SetComp2	,"setcomp"		,"o=Nff", 0)
DEFLINKFUNC(SetComp3	,"setcomp"		,"o=Cff", 0)
DEFFUNC(SetComp			,"setcomp"		,"o=Vff",FUN3EXPR_PRE,SETCOMPEXP,FUN3EXPR_UPDATE(3,1,1),NULL_EXPR,0)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// setcomp "o=Mfff"
#define	SETMCOMPEXP			res[element((int) op1->real,(int) op2->real)].real	=	op3->real;
DEFFUNC(SetMComp			,"setcomp"		,"o=Mfff",FUN4EXPR_PRE,SETMCOMPEXP,FUN4EXPR_UPDATE(16,1,1,1),NULL_EXPR,0)

#define	LENGTHEXP			res->real	=	lengthv(&op->real);
DEFLINKFUNC(Length3	,"length"		,"f=c", 0)
DEFLINKFUNC(Length1	,"length"		,"f=p", 0)
DEFLINKFUNC(Length2	,"length"		,"f=n", 0)
DEFFUNC(Length		,"length"		,"f=v"	,FUN2EXPR_PRE,LENGTHEXP,FUN2EXPR_UPDATE(1,3),NULL_EXPR,0)

#define	NORMALIZEXP			if (dotvv(&op->real,&op->real) > 0) normalizev(&res->real,&op->real);	else initv(&res->real,0,0,0);
DEFLINKFUNC(Normalize3	,"normalize"		,"c=c", 0)
DEFLINKFUNC(Normalize1	,"normalize"		,"p=p", 0)
DEFLINKFUNC(Normalize2	,"normalize"		,"n=n", 0)
DEFFUNC(Normalize		,"normalize"		,"v=v"	,FUN2EXPR_PRE,NORMALIZEXP,FUN2EXPR_UPDATE(3,3),NULL_EXPR,0)

#define	DISTANCEEXP_PRE		FUN3EXPR_PRE;										\
							vector	vtmp;

#define	DISTANCEEXP			subvv(vtmp,&op1->real,&op2->real);					\
							res->real	=	lengthv(vtmp);

DEFFUNC(Distance		,"distance"			,"f=pp"	,DISTANCEEXP_PRE,DISTANCEEXP,FUN3EXPR_UPDATE(1,3,3),NULL_EXPR,0)



// Point to line distance
#define	PTLINEDEXP_PRE		FUN4EXPR_PRE											\
							const float	*ftmp,*ftmp2,*ftmp3;						\
							vector		vtmp,vtmp2,vtmp3;							\
							float		l;

#define	PTLINEDEXP			ftmp	=	&op1->real;									\
							ftmp2	=	&op2->real;									\
							ftmp3	=	&op3->real;									\
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
							res->real	=	l;

DEFFUNC(Ptlined		,"ptlined"			,"f=ppp"	,PTLINEDEXP_PRE,PTLINEDEXP,FUN4EXPR_UPDATE(1,3,3,3),NULL_EXPR,0)


#define	ROTATEEXP_PRE	FUN5EXPR_PRE;												\
						vector	vtmp,vtmp2;											\
						matrix	mtmp;

#define	ROTATEEXP		subvv(vtmp,&op3->real,&op4->real);							\
						rotatem(mtmp,vtmp,op2->real);								\
						subvv(vtmp2,&op1->real,&op4->real);							\
						mulmp(vtmp,mtmp,vtmp2);										\
						addvv(&res->real,vtmp,&op4->real);

DEFFUNC(Rotatep		,"rotate"			,"p=pfpp"	,ROTATEEXP_PRE,ROTATEEXP,FUN5EXPR_UPDATE(3,3,1,3,3),NULL_EXPR,0)

#define	REFLECTEXP	reflect(&res->real,&op1->real,&op2->real);
					

DEFFUNC(Reflect		,"reflect"			,"v=vv"	,FUN3EXPR_PRE,REFLECTEXP,FUN3EXPR_UPDATE(3,3,3),NULL_EXPR,0)

#define	REFRACTEXP	::refract(&res->real,&op1->real,&op2->real,op3->real);

DEFFUNC(Refract		,"refract"			,"v=vvf"	,FUN4EXPR_PRE,REFRACTEXP,FUN4EXPR_UPDATE(3,3,3,1),NULL_EXPR,0)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// fresnel "o=vvfFF"
#define	FRESNELEXP		vector	dummy0,dummy1;															\
						fresnel(&res->real,&op1->real,op2->real,op3->real,op4->real,dummy0,dummy1);




DEFFUNC(Fresnel			,"fresnel"		,"o=vvfFF",FUN5OUTEXPR_PRE,FRESNELEXP,FUN5EXPR_UPDATE(3,3,1,1,1),NULL_EXPR,0)


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// fresnel "o=vvfFFVV"
#define	FRESNEL7EXPR_PRE	TCode	*op[7];																\
							int		i;																	\
																										\
							for (i=0;i<7;i++) {															\
								operand(i,op[i]);														\
							}

#define FRESNEL7EXPR		fresnel(&op[0]->real,&op[1]->real,op[2]->real,op[3]->real,op[4]->real,&op[5]->real,&op[6]->real);

#define	FRESNEL7EXPR_UPDATE		op[0]	+=	3;															\
								op[1]	+=	3;															\
								op[2]	+=	1;															\
								op[3]	+=	1;															\
								op[4]	+=	1;															\
								op[5]	+=	3;															\
								op[6]	+=	3;


DEFFUNC(Fresnel2		,"fresnel"		,"o=vvfFFVV",FRESNEL7EXPR_PRE,FRESNEL7EXPR,FRESNEL7EXPR_UPDATE,NULL_EXPR,0)

#define	DETERMINANTEXP		res->real	=	determinantm(&op->real);

DEFFUNC(Determinant		,"determinant"			,"f=m"	,FUN2EXPR_PRE,DETERMINANTEXP,FUN2EXPR_UPDATE(1,16),NULL_EXPR,0)


#define	TRANSLATEEXP_PRE	FUN3EXPR_PRE;													\
							matrix	mtmp;

#define	TRANSLATEEXP		translatem(mtmp,op2[0].real,op2[1].real,op2[2].real);			\
							mulmm(&res->real,&op1->real,mtmp);

DEFFUNC(Translatem		,"translate"			,"m=mp"	,TRANSLATEEXP_PRE,TRANSLATEEXP,FUN3EXPR_UPDATE(16,16,3),NULL_EXPR,0)

#define	ROTATEEXPR_PRE		FUN4EXPR_PRE;													\
							matrix	mtmp;

#define	ROTATEEXPR			rotatem(mtmp,op3[0].real,op3[1].real,op3[2].real,op2->real);	\
							mulmm(&res->real,&op1->real,mtmp);

DEFFUNC(Rotatem			,"rotate"				,"m=mfv"	,ROTATEEXPR_PRE,ROTATEEXPR,FUN4EXPR_UPDATE(16,16,1,3),NULL_EXPR,0)

#define	SCALEEXPR_PRE		FUN3EXPR_PRE;													\
							matrix	mtmp;

#define	SCALEEXPR			scalem(mtmp,op2[0].real,op2[1].real,op2[2].real);				\
							mulmm(&res->real,&op1->real,mtmp);

DEFFUNC(Scalem			,"scale"				,"m=mp"		,SCALEEXPR_PRE,SCALEEXPR,FUN3EXPR_UPDATE(16,16,3),NULL_EXPR,0)


#define	MINFEXPR_PRE		TCode		*res;												\
							const TCode	**op;												\
							int			numArguments;										\
							int			i;													\
							float		min;												\
																							\
							operand(0,res);													\
							argumentcount(numArguments);									\
							numArguments--;													\
							op		=	(const TCode **) ralloc(numArguments*sizeof(TCode *),threadMemory);	\
																							\
							for (i=0;i<numArguments;i++) {									\
								operand(i+1,op[i]);											\
							}

#define	MINFEXPR			min	=	op[0]->real;											\
							for (i=1;i<numArguments;i++) {									\
								if (op[i]->real < min)	min = op[i]->real;					\
							}																\
							res->real	=	min;

#define	MINFEXPR_UPDATE		res	++;															\
							for (i=0;i<numArguments;i++)									\
								op[i]++;

#define	MINFEXPR_POST

DEFFUNC(Minf				,"min"						,"f=f+"		,MINFEXPR_PRE,MINFEXPR,MINFEXPR_UPDATE,MINFEXPR_POST,0)

#define	MINVEXPR_PRE		TCode		*res;												\
							const TCode	**op;												\
							int			numArguments;										\
							int			i;													\
							float		minx,miny,minz;										\
																							\
							operand(0,res);													\
							argumentcount(numArguments);									\
							numArguments--;													\
							op		=	(const TCode **) ralloc(numArguments*sizeof(TCode *),threadMemory);	\
																							\
							for (i=0;i<numArguments;i++) {									\
								operand(i+1,op[i]);											\
							}

#define	MINVEXPR			minx	=	op[0][0].real;										\
							miny	=	op[0][1].real;										\
							minz	=	op[0][2].real;										\
							for (i=1;i<numArguments;i++) {									\
								if (op[i][0].real < minx)	minx = op[i][0].real;			\
								if (op[i][1].real < miny)	miny = op[i][1].real;			\
								if (op[i][2].real < minz)	minz = op[i][2].real;			\
							}																\
							res[0].real	=	minx;											\
							res[1].real	=	miny;											\
							res[2].real	=	minz;

#define	MINVEXPR_UPDATE		res	+=	3;														\
							for (i=0;i<numArguments;i++)									\
								op[i]	+=	3;

#define	MINVEXPR_POST

DEFFUNC(Minv				,"min"						,"v=v+"		,MINVEXPR_PRE,MINVEXPR,MINVEXPR_UPDATE,MINVEXPR_POST,0)

#define	MAXFEXPR_PRE		TCode		*res;												\
							const TCode	**op;												\
							int			numArguments;										\
							int			i;													\
							float		max;												\
																							\
							operand(0,res);													\
							argumentcount(numArguments);									\
							numArguments--;													\
							op		=	(const TCode **) ralloc(numArguments*sizeof(TCode *),threadMemory);	\
																							\
							for (i=0;i<numArguments;i++) {									\
								operand(i+1,op[i]);											\
							}

#define	MAXFEXPR			max	=	op[0]->real;											\
							for (i=1;i<numArguments;i++) {									\
								if (op[i]->real > max)	max = op[i]->real;					\
							}																\
							res->real	=	max;

#define	MAXFEXPR_UPDATE		res++;															\
							for (i=0;i<numArguments;i++)									\
								op[i]++;

#define	MAXFEXPR_POST

DEFFUNC(Maxf				,"max"						,"f=f+"		,MAXFEXPR_PRE,MAXFEXPR,MAXFEXPR_UPDATE,MAXFEXPR_POST,0)


#define	MAXVEXPR_PRE		TCode		*res;												\
							const TCode	**op;												\
							int			numArguments;										\
							int			i;													\
							float		maxx,maxy,maxz;										\
																							\
							operand(0,res);													\
							argumentcount(numArguments);									\
							numArguments--;													\
							op		=	(const TCode **) ralloc(numArguments*sizeof(TCode *),threadMemory);	\
																							\
							for (i=0;i<numArguments;i++) {									\
								operand(i+1,op[i]);											\
							}

#define	MAXVEXPR			maxx	=	op[0][0].real;										\
							maxy	=	op[0][1].real;										\
							maxz	=	op[0][2].real;										\
							for (i=1;i<numArguments;i++) {									\
								if (op[i][0].real > maxx)	maxx = op[i][0].real;			\
								if (op[i][1].real > maxy)	maxy = op[i][1].real;			\
								if (op[i][2].real > maxz)	maxz = op[i][2].real;			\
							}																\
							res[0].real	=	maxx;											\
							res[1].real	=	maxy;											\
							res[2].real	=	maxz;

#define	MAXVEXPR_UPDATE		res	+=	3;														\
							for (i=0;i<numArguments;i++)									\
								op[i]	+=	3;

#define	MAXVEXPR_POST

DEFFUNC(Maxv					,"max"						,"v=v+"		,MAXVEXPR_PRE,MAXVEXPR,MAXVEXPR_UPDATE,MAXVEXPR_POST,0)



#define	CONCATEXPR_PRE		char		tmp[MAX_SCRIPT_STRING_SIZE];				\
							TCode		*res;										\
							const TCode	*op1,*op2;									\
							operand(0,res);											\
							operand(1,op1);											\
							operand(2,op2);

#define CONCATEXPR			strcpy(tmp,op1->string);								\
							strcat(tmp,op2->string);								\
							savestring(res->string,tmp);

#define	CONCATEXPR_UPDATE	res++;													\
							op1++;													\
							op2++;


DEFFUNC(Concat					,"concat"						,"s=ss"		,CONCATEXPR_PRE,CONCATEXPR,CONCATEXPR_UPDATE,NULL_EXPR,0)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// match	"f=ss"
// FIXME: Subpattern matching is not implemented yet
#define MATCHEXPR		if (strcmp(op1->string,op2->string) == 0)					\
							res->real	=	1;										\
						else														\
							res->real	=	0;

DEFFUNC(Match					,"match"						,"f=ss"		,FUN3EXPR_PRE,MATCHEXPR,FUN3EXPR_UPDATE(1,1,1),NULL_EXPR,0)



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// printf	"o=s.*"
#define	PRINTEXPR(r,s,a)	const char	*str;												\
							char		*tmp;												\
							int			cp	=	-1;											\
							tmp	=	r;														\
							str =   s->string;												\
							while(*str != '\0')	{											\
								if (*str == '%') {											\
									str++;													\
									if (*str == '\0') break;								\
									if (*str == 'f') {										\
										cp++;												\
										sprintf(tmp,"%f",a[cp]->real);						\
									} else if (*str == 'c') {								\
										cp++;												\
										sprintf(tmp,"(%f,%f,%f)",a[cp][0].real,a[cp][1].real,a[cp][2].real);		\
									} else if (*str == 'n') {								\
										cp++;												\
										sprintf(tmp,"(%f,%f,%f)",a[cp][0].real,a[cp][1].real,a[cp][2].real);		\
									} else if (*str == 'p') {								\
										cp++;												\
										sprintf(tmp,"(%f,%f,%f)",a[cp][0].real,a[cp][1].real,a[cp][2].real);		\
									} else if (*str == 's') {								\
										cp++;												\
										sprintf(tmp,"%s",a[cp]->string);					\
									} else if (*str == 'm') {								\
										cp++;												\
										sprintf(tmp,"((%f,%f,%f,%f),(%f,%f,%f,%f),(%f,%f,%f,%f),(%f,%f,%f,%f))",a[cp][0].real,a[cp][1].real,a[cp][2].real,a[cp][3].real,a[cp][4].real,a[cp][5].real,a[cp][6].real,a[cp][7].real,a[cp][8].real,a[cp][9].real,a[cp][10].real,a[cp][11].real,a[cp][12].real,a[cp][13].real,a[cp][14].real,a[cp][15].real);		\
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
							TCode		*res;													\
							const TCode	**op;													\
							int			*opSteps;												\
							int			resStep;												\
							int			numArguments;											\
							int			i;														\
							int			numRealVertices = currentShadingState->numRealVertices;	\
							int			vertexN	=	0;											\
																								\
							operandSize(0,res,resStep);											\
							argumentcount(numArguments);										\
							numArguments--;														\
							op		=	(const TCode **) ralloc(numArguments*sizeof(TCode *),threadMemory);	\
							opSteps	=	(int *)	   ralloc(numArguments*sizeof(int),threadMemory);			\
																								\
							for (i=0;i<numArguments;i++) {										\
								operandSize(i+1,op[i],opSteps[i]);								\
							}

#define	PRINTFEXPR			if (vertexN < numRealVertices) {									\
								PRINTEXPR(output,res,op);										\
								printf(output);													\
							}

#define	PRINTF_UPDATE		res	+=	resStep;													\
							for (i=0;i<numArguments;i++)										\
								op[i]	+=	opSteps[i];											\
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
							TCode		*res,*strArg;											\
							const TCode	**op;													\
							int			*opSteps;												\
							int			resStep,strStep;										\
							int			numArguments;											\
							int			i;														\
																								\
							operandSize(0,res,resStep);											\
							operandSize(1,strArg,strStep);										\
							argumentcount(numArguments);										\
							numArguments--;														\
							numArguments--;														\
							op		=	(const TCode **) ralloc(numArguments*sizeof(TCode *),threadMemory);	\
							opSteps	=	(int *)			ralloc(numArguments*sizeof(int),threadMemory);		\
																								\
							for (i=0;i<numArguments;i++) {										\
								operandSize(i+2,op[i],opSteps[i]);								\
							}

#define	FORMATEXPR			PRINTEXPR(output,strArg,op);										\
							savestring(res->string,output);


#define	FORMAT_UPDATE		res	+=	resStep;												\
							strArg +=	strStep;											\
							for (i=0;i<numArguments;i++)									\
								op[i]	+=	opSteps[i];

#define	FORMAT_POST

DEFFUNC(Format					,"format"						,"s=s.*"		,FORMATEXPR_PRE,FORMATEXPR,FORMAT_UPDATE,FORMAT_POST,0)


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// spline	"f=Sfffff*"
// spline	"f=fffff*"
#define SPLINEPARAMETERS()		

#ifndef INIT_SHADING

#define	SPLINEVEXPR_PRE		TCode		*res;													\
							const TCode	**op;													\
							int			numArguments;											\
							int			i;														\
							TCode		*val,*splineType;										\
							float		ub[4],tmp[4];											\
							const float	*ubasis = (float*) RiCatmullRomBasis;					\
							int			ustep = 1;												\
							int			numPieces;												\
																								\
							operand(1,splineType);												\
							ubasis 	=	(float*) RiCatmullRomBasis;								\
							ustep	=	1;														\
							if (!strcmp(splineType->string,"catmull-rom")) {					\
								/* do nothing */												\
							} else if (!strcmp(splineType->string,"bezier")) {					\
								ubasis 	=	(float*) RiBezierBasis;								\
								ustep	=	3;													\
							} else if (!strcmp(splineType->string,"bspline")) {					\
								ubasis 	=	(float*) RiBSplineBasis;							\
								ustep	=	1;													\
							} else if (!strcmp(splineType->string,"hermite")) {					\
								ubasis 	=	(float*) RiHermiteBasis;							\
								ustep	=	2;													\
							} else {															\
								error(CODE_BADTOKEN,"Unknown spline basis \"%s\"\n",splineType->string);	\
							}																	\
																								\
							operand(0,res);														\
							operand(2,val);														\
							argumentcount(numArguments);										\
							numArguments-=3;													\
							op		=	(const TCode **) ralloc(numArguments*sizeof(TCode *),threadMemory);	\
							numPieces = (numArguments-4)/ustep+1;								\
																								\
							for (i=0;i<numArguments;i++) {										\
								operand(i+3,op[i]);												\
							}


#define	SPLINEEXPR_PRE		TCode		*res;													\
							const TCode	**op;													\
							int			numArguments;											\
							int			i;														\
							TCode		*val;													\
							float		ub[4],tmp[4];											\
							const float	*ubasis = (float*) RiCatmullRomBasis;					\
							int			ustep = 1;												\
							int			numPieces;												\
																								\
							operand(0,res);														\
							operand(1,val);														\
							argumentcount(numArguments);										\
							numArguments--;														\
							numArguments--;														\
							op		=	(const TCode **) ralloc(numArguments*sizeof(TCode *),threadMemory);	\
							numPieces = (numArguments-3);										\
																								\
							for (i=0;i<numArguments;i++) {										\
								operand(i+2,op[i]);												\
							}

#define	SPLINEFEXPR			if (val->real <= 0)			res->real	=	op[1]->real;					\
							else if (val->real >= 1)	res->real	=	op[numArguments-2]->real;		\
							else {																		\
								int		piece	=	(int) floor(val->real * (float) numPieces);			\
								int		pieceid	=	piece*ustep;										\
								float	u		=	val->real*((float) numPieces) - (float) piece;		\
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
								res->real		=	tmp[0]*op[pieceid+0]->real +						\
													tmp[1]*op[pieceid+1]->real +						\
													tmp[2]*op[pieceid+2]->real +						\
													tmp[3]*op[pieceid+3]->real;							\
							}																			\


#define	SPLINEFEXPR_UPDATE	res++;																\
							val++;																\
							for (i=0;i<numArguments;i++)										\
								op[i]++;

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

#define	SPLINEPEXPR			if (val->real <= 0)			movvv(&res->real,&op[1]->real);					\
							else if (val->real >= 1)	movvv(&res->real,&op[numArguments-2]->real);	\
							else {																		\
								int		piece	=	(int) floor(val->real * (float) numPieces);			\
								int		pieceid	=	piece*ustep;										\
								float	u		=	val->real*((float) numPieces) - (float) piece;		\
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
								res[0].real		=	tmp[0]*op[pieceid+0][0].real +						\
													tmp[1]*op[pieceid+1][0].real +						\
													tmp[2]*op[pieceid+2][0].real +						\
													tmp[3]*op[pieceid+3][0].real;						\
																										\
								res[1].real		=	tmp[0]*op[pieceid+0][1].real +						\
													tmp[1]*op[pieceid+1][1].real +						\
													tmp[2]*op[pieceid+2][1].real +						\
													tmp[3]*op[pieceid+3][1].real;						\
																										\
								res[2].real		=	tmp[0]*op[pieceid+0][2].real +						\
													tmp[1]*op[pieceid+1][2].real +						\
													tmp[2]*op[pieceid+2][2].real +						\
													tmp[3]*op[pieceid+3][2].real;						\
							}																			\


#define	SPLINEPEXPR_UPDATE	res	+=	3;																	\
							val +=	1;																	\
							for (i=0;i<numArguments;i++)												\
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
// DSO dispatcher
#define	DSOEXEC_PRE			int					numArguments;								\
							void				*handle;									\
							dsoExecFunction		exec;										\
							TCode				**op;										\
							int					*opSteps;									\
							int					i;											\
																							\
							argumentcount(numArguments);									\
							op		=	(TCode **) ralloc(numArguments*sizeof(TCode *),threadMemory);	\
							opSteps	=	(int *)	   ralloc(numArguments*sizeof(int),threadMemory);		\
																							\
							for (i=0;i<numArguments;i++) {									\
								operandSize(i+2,op[i],opSteps[i]);							\
							}																\
																							\
							handle	=	(void *) argument(0);								\
							exec	=	(dsoExecFunction) argument(1);
						

#define	DSOEXEC				exec(handle,numArguments,(void **) op);

#define	DSOEXEC_UPDATE		for (i=0;i<numArguments;i++) {									\
								op[i]	+=	opSteps[i];										\
							}

#define	DSOEXEC_POST

DEFFUNC(DSO				,"XXX",			"XXX",	DSOEXEC_PRE,DSOEXEC,DSOEXEC_UPDATE,DSOEXEC_POST,0)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VOID DSO dispatcher
#define	DSOVOIDEXEC_PRE		int					numArguments;								\
							void				*handle;									\
							dsoExecFunction		exec;										\
							TCode				**op;										\
							int					*opSteps;									\
							int					i;											\
																							\
							argumentcount(numArguments);									\
							numArguments++;													\
							op		=	(TCode **) ralloc(numArguments*sizeof(TCode *),threadMemory);	\
							opSteps	=	(int *)	   ralloc(numArguments*sizeof(int),threadMemory);		\
																							\
							for (i=1;i<numArguments;i++) {									\
								operandSize(i+1,op[i],opSteps[i]);							\
							}																\
																							\
							handle	=	(void *) argument(0);								\
							exec	=	(dsoExecFunction) argument(1);

#define	DSOVOIDEXEC			exec(handle,numArguments,(void **) op);

#define	DSOVOIDEXEC_UPDATE	for (i=1;i<numArguments;i++) {									\
								op[i]	+=	opSteps[i];										\
							}

#define	DSOVOIDEXEC_POST

DEFFUNC(DSO_VOID				,"XXX",			"XXX",	DSOVOIDEXEC_PRE,DSOVOIDEXEC,DSOVOIDEXEC_UPDATE,DSOVOIDEXEC_POST,0)

// Include the RenderMan Shading Language specific built - in functions
#include "shaderFunctions.h"


