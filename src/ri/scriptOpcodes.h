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
//  File				:	scriptOpcodes.h
//  Classes				:	-
//  Description			:	Script opcodes
//
//
//
//
//
////////////////////////////////////////////////////////////////////////

#define	NULL_EXPR



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
//
//
//	CONDITIONAL EXECUTION
//
//
//	!!!	This part is quite complicated !!!
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	if <boolean> <endIf>
#define	IF2EXPR_PRE			float	*op;														\
							operand(0,op,float *);												\
							for (int i=0;i<numVertices;++i,++op,++tags)	{						\
								if (*tags) {													\
									(*tags)++;													\
								} else {														\
									if ((int) (*op)) {											\
										*tags	=	0;											\
									} else	{													\
										*tags	=	1;											\
										--numActive;											\
										++numPassive;											\
									}															\
								}																\
							}

#define	IF2EXPR_POST		if (numActive == 0) {												\
								jmp(argument(1));												\
							}

DEFOPCODE(If2	,"if"	,2,	IF2EXPR_PRE,NULL_EXPR,NULL_EXPR,IF2EXPR_POST,0)




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	elseif

#define	ELSEIFEXPR_PRE		for (int i=0;i<numVertices;++i,++tags)	{							\
								if (*tags <= 1) {												\
									if (*tags == 1) {											\
										*tags	=	0;											\
										++numActive;											\
										--numPassive;											\
									} else {													\
										*tags	=	1;											\
										--numActive;											\
										++numPassive;											\
									}															\
								}																\
							}


#define	ELSEIFEXPR_POST		if (numActive == 0) {												\
								jmp(argument(0));												\
							}

DEFOPCODE(Else	,"else"	,1,	ELSEIFEXPR_PRE,NULL_EXPR,NULL_EXPR,ELSEIFEXPR_POST,0)

#undef	ELSEIFEXPR_PRE
#undef	ELSEIFEXPR_POST

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	endif

///////////////	Single
#define	ENDIFEXPR_PRE		for (int i=0;i<numVertices;++i,++tags)	{							\
								if (*tags) {													\
									(*tags)--;													\
																								\
									if (*tags == 0) {											\
										++numActive;											\
										--numPassive;											\
									}															\
								}																\
							}

#define	ENDIFEXPR_POST

DEFOPCODE(Endif	,"endif"	,0,	ENDIFEXPR_PRE,NULL_EXPR,NULL_EXPR,ENDIFEXPR_POST,0)


#undef	ENDIFEXPR_PRE
#undef	ENDIFEXPR_POST




















///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	forbegin <body> <continue> <end>
#define	FORBEGIN3EXPR_PRE	const int bodyIndex		=	argument(0);							\
							const int continueIndex	=	argument(1);							\
							const int endIndex		=	argument(2);							\
							beginConditional();													\
							lastConditional->forStart		=	bodyIndex;						\
							lastConditional->forContinue	=	continueIndex;					\
							lastConditional->forEnd			=	endIndex;						\
							lastConditional->forExecCount	=	0;
							
DEFOPCODE(Forbegin3	,"forbegin"	,3,	FORBEGIN3EXPR_PRE,NULL_EXPR,NULL_EXPR,NULL_EXPR,0)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	for <cond>
#define	FOR3EXPR_PRE		float	*op;														\
							operand(0,op,float *);												\
							lastConditional->forExecCount++;									\
							for (int i=numVertices;i>0;--i,++op,++tags)	{						\
								if (*tags) {													\
									(*tags)++;													\
								} else {														\
									if ((int) (*op)) {											\
									} else	{													\
										*tags	=	lastConditional->forExecCount;				\
										--numActive;											\
										++numPassive;											\
									}															\
								}																\
							}


#define	FOR3EXPR_POST		if (numActive == 0) {												\
								jmp(lastConditional->forEnd);									\
							}
								


DEFOPCODE(For3	,"for"	,1,	FOR3EXPR_PRE,NULL_EXPR,NULL_EXPR,FOR3EXPR_POST,0)

#undef FOR3EXPR_PRE
#undef FOR3EXPR_POST

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	forend
#define	FOREND3EXPR_PRE		if (numActive > 0)	jmp(lastConditional->forStart);					\
							numActive	=	0;													\
							numPassive	=	numVertices;										\
							for (int i=numVertices;i>0;--i,++tags)	{							\
								if (*tags) {													\
									*tags	-=	lastConditional->forExecCount;					\
									if (*tags	<= 0)	{										\
										*tags	=	0;											\
										++numActive;											\
										--numPassive;											\
									}															\
								}																\
							}																	\
							endConditional();
DEFOPCODE(Forend3	,"forend"	,0,	FOREND3EXPR_PRE,NULL_EXPR,NULL_EXPR,NULL_EXPR,0)

#undef FOREND3EXPR_PRE


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	break
#define	BREAK1EXPR_PRE		for (int i=0;i<numVertices;++i,++tags)	{							\
								if (*tags	== 0)	{											\
									*tags	=	lastConditional->forExecCount;					\
									++numPassive;												\
									--numActive;												\
								}																\
							}

#define	BREAK1EXPR_POST		

// FIXME: this optmization 'breaks' varying breaks! because they need to exit the conditional
// in which they are defined.  No easy fix
//							if (numActive == 0) {												\
//								jmp(lastConditional->forEnd);									\
//							}

DEFOPCODE(Break1	,"break"	,1,	BREAK1EXPR_PRE,NULL_EXPR,NULL_EXPR,BREAK1EXPR_POST,0)

#undef BREAK1EXPR_PRE
#undef BREAK1EXPR_POST

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	continue
//  FIXME: check this, I don't think it works inside a varying conditional

#define	CONTINUE1EXPR_POST	if (numPassive != 0) {												\
								jmp(lastConditional->forContinue);								\
							}

DEFOPCODE(Continue1	,"continue"	,1,	NULL_EXPR,NULL_EXPR,NULL_EXPR,CONTINUE1EXPR_POST,0)

#undef CONTINUE1EXPR_POST

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
//
//
//	BOOLEAN OPERATIONS
//
//
//
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define	OPERANDS3EXPR_PRE(_rt,_op1t,_op2t)						\
								_rt		res;					\
								_op1t	op1;					\
								_op2t	op2;					\
								operand(0,res,_rt);				\
								operand(1,op1,_op1t);			\
								operand(2,op2,_op2t);


#define	OPERANDS3EXPR_UPDATE(__rs,__op1s,__op2s)				\
								res	+=	__rs;					\
								op1	+=	__op1s;					\
								op2	+=	__op2s;



#define	OPERANDS2EXPR_PRE(_rt,_opt)								\
								_rt		res;					\
								_opt	op;						\
								operand(0,res,_rt);				\
								operand(1,op,_opt);

#define	OPERANDS2EXPR_UPDATE(__rs,__ops)						\
								res	+=	__rs;					\
								op	+=	__ops;



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// fcmp

#define	FCMPEXPR			if (op1[0] OPERATION op2[0])	res[0]	=	1.0f;					\
							else							res[0]	=	0;



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// vcmp
#define	VCMPEXPR			if (	(op1[0] OPERATION op2[0]) &&								\
									(op1[1] OPERATION op2[1]) &&								\
									(op1[2] OPERATION op2[2])	)	res[0]	=	1.0f;			\
							else	res[0]	=	0;


#define	VNCMPEXPR			if (	(op1[0] OPERATION op2[0]) ||								\
									(op1[1] OPERATION op2[1]) ||								\
									(op1[2] OPERATION op2[2])	)	res[0]	=	1.0f;			\
							else	res[0]	=	0;



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// mcmp
#define	MCMPEXPR			*res	=	1.0f;													\
							for (int index=0;index<16;++index)									\
								if (!(op1[index] OPERATION op2[index]))	*res	=	0;

#define	MNCMPEXPR			*res	=	0;														\
							for (int index=0;index<16;++index)									\
								if (!(op1[index] OPERATION op2[index]))	*res	=	1.0f;


#define	SEQLEXPR			if (strcmp(op1[0],op2[0]) == 0)	res[0]	=	1.0f;					\
							else							res[0]	=	0;

#define	SNEQLEXPR			if (strcmp(op1[0],op2[0]) != 0)	res[0]	=	1.0f;					\
							else							res[0]	=	0;




#define	OPERATION			==
DEFOPCODE(Feql2		,"feql"		,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),FCMPEXPR,OPERANDS3EXPR_UPDATE(1,1,1),		NULL_EXPR,0)
DEFOPCODE(Veql2		,"veql"		,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),VCMPEXPR,OPERANDS3EXPR_UPDATE(1,3,3),		NULL_EXPR,0)
DEFOPCODE(Meql2		,"meql"		,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),MCMPEXPR,OPERANDS3EXPR_UPDATE(1,16,16),		NULL_EXPR,0)
DEFOPCODE(Seql2		,"seql"		,3,	OPERANDS3EXPR_PRE(float *,const char **,const char **),SEQLEXPR,OPERANDS3EXPR_UPDATE(1,1,1),		NULL_EXPR,0)
#undef	OPERATION

#define	OPERATION			!=
DEFOPCODE(Fneql2	,"fneql"	,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),FCMPEXPR,OPERANDS3EXPR_UPDATE(1,1,1),		NULL_EXPR,0)
DEFOPCODE(Vneql2	,"vneql"	,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),VNCMPEXPR,OPERANDS3EXPR_UPDATE(1,3,3),		NULL_EXPR,0)
DEFOPCODE(Mneql2	,"mneql"	,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),MNCMPEXPR,OPERANDS3EXPR_UPDATE(1,16,16),		NULL_EXPR,0)
DEFOPCODE(Sneql2	,"sneql"	,3,	OPERANDS3EXPR_PRE(float *,const char **,const char **),SNEQLEXPR,OPERANDS3EXPR_UPDATE(1,1,1),		NULL_EXPR,0)
#undef OPERATION

#define	OPERATION			>
DEFOPCODE(Fgt2		,"fgt"		,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),FCMPEXPR,OPERANDS3EXPR_UPDATE(1,1,1),		NULL_EXPR,0)
DEFOPCODE(Vgt2		,"vgt"		,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),VCMPEXPR,OPERANDS3EXPR_UPDATE(1,3,3),		NULL_EXPR,0)
#undef OPERATION

#define	OPERATION			<
DEFOPCODE(Flt2		,"flt"		,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),FCMPEXPR,OPERANDS3EXPR_UPDATE(1,1,1),		NULL_EXPR,0)
DEFOPCODE(Vlt2		,"vlt"		,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),VCMPEXPR,OPERANDS3EXPR_UPDATE(1,3,3),		NULL_EXPR,0)
#undef OPERATION

#define	OPERATION			>=
DEFOPCODE(Fgte2		,"fegt"		,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),FCMPEXPR,OPERANDS3EXPR_UPDATE(1,1,1),		NULL_EXPR,0)
DEFOPCODE(Vgte2		,"vegt"		,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),VCMPEXPR,OPERANDS3EXPR_UPDATE(1,3,3),		NULL_EXPR,0)
#undef OPERATION

#define	OPERATION			<=
DEFOPCODE(Flte2		,"felt"		,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),FCMPEXPR,OPERANDS3EXPR_UPDATE(1,1,1),		NULL_EXPR,0)
DEFOPCODE(Vlte2		,"velt"		,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),VCMPEXPR,OPERANDS3EXPR_UPDATE(1,3,3),		NULL_EXPR,0)
#undef OPERATION


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
//
//
//	LOGIC OPERATIONS
//
//
//
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// logic
#define	LOGICEXPR			*res	=	(float) ((int) (*op1) OPERATION (int) (*op2));


#define	OPERATION			&
DEFOPCODE(And0	,"and"	,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),LOGICEXPR,OPERANDS3EXPR_UPDATE(1,1,1),NULL_EXPR,0)
#undef	OPERATION

#define	OPERATION			|
DEFOPCODE(Or0	,"or"	,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),LOGICEXPR,OPERANDS3EXPR_UPDATE(1,1,1),NULL_EXPR,0)
#undef	OPERATION

#define	OPERATION			^
DEFOPCODE(Xor0	,"xor"	,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),LOGICEXPR,OPERANDS3EXPR_UPDATE(1,1,1),NULL_EXPR,0)
#undef	OPERATION

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// nxor
#define	NXOREXPR			*res	=	(float) ~((int) (*op1) ^ (int) (*op2));

DEFOPCODE(Nxor	,"nxor"	,3, OPERANDS3EXPR_PRE(float *,const float *,const float *),NXOREXPR,OPERANDS3EXPR_UPDATE(1,1,1),NULL_EXPR,0)


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// not
#define	NOTEXPR			*res	=	(float) ~((int) (*op));


DEFOPCODE(Not	,"not"	,2, OPERANDS2EXPR_PRE(float *,const float *),NOTEXPR,OPERANDS2EXPR_UPDATE(1,1),NULL_EXPR,0)



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
//
//
//	ARITMETIC OPERATIONS
//
//
//
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define	FARITMETICEXPR		*res		=	*op1 OPERATION *op2;

#define	VARITMETICEXPR		res[0]		=	op1[0] OPERATION op2[0];		\
							res[1]		=	op1[1] OPERATION op2[1];		\
							res[2]		=	op1[2] OPERATION op2[2];

#define	MARITMETICEXPR		res[0]		=	op1[0] OPERATION op2[0];		\
							res[1]		=	op1[1] OPERATION op2[1];		\
							res[2]		=	op1[2] OPERATION op2[2];		\
							res[3]		=	op1[3] OPERATION op2[3];		\
							res[4]		=	op1[4] OPERATION op2[4];		\
							res[5]		=	op1[5] OPERATION op2[5];		\
							res[6]		=	op1[6] OPERATION op2[6];		\
							res[7]		=	op1[7] OPERATION op2[7];		\
							res[8]		=	op1[8] OPERATION op2[8];		\
							res[9]		=	op1[9] OPERATION op2[9];		\
							res[10]		=	op1[10] OPERATION op2[10];		\
							res[11]		=	op1[11] OPERATION op2[11];		\
							res[12]		=	op1[12] OPERATION op2[12];		\
							res[13]		=	op1[13] OPERATION op2[13];		\
							res[14]		=	op1[14] OPERATION op2[14];		\
							res[15]		=	op1[15] OPERATION op2[15];

#define	OPERATION			+
DEFOPCODE(Fadd	,"addff"	,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),FARITMETICEXPR,OPERANDS3EXPR_UPDATE(1,1,1),NULL_EXPR,0)
#undef	OPERATION
#define	OPERATION			-
DEFOPCODE(Fsub	,"subff"	,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),FARITMETICEXPR,OPERANDS3EXPR_UPDATE(1,1,1),NULL_EXPR,0)
#undef	OPERATION
#define	OPERATION			*
DEFOPCODE(Fmul	,"mulff"	,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),FARITMETICEXPR,OPERANDS3EXPR_UPDATE(1,1,1),NULL_EXPR,0)
#undef	OPERATION
#define	OPERATION			/
DEFOPCODE(Fdiv	,"divff"	,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),FARITMETICEXPR,OPERANDS3EXPR_UPDATE(1,1,1),NULL_EXPR,0)
#undef	OPERATION


#define	OPERATION			+
DEFOPCODE(Vadd	,"addvv"	,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),VARITMETICEXPR,OPERANDS3EXPR_UPDATE(3,3,3),NULL_EXPR,0)
#undef	OPERATION
#define	OPERATION			-
DEFOPCODE(Vsub	,"subvv"	,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),VARITMETICEXPR,OPERANDS3EXPR_UPDATE(3,3,3),NULL_EXPR,0)
#undef	OPERATION
#define	OPERATION			*
DEFOPCODE(Vmul	,"mulvv"	,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),VARITMETICEXPR,OPERANDS3EXPR_UPDATE(3,3,3),NULL_EXPR,0)
#undef	OPERATION
#define	OPERATION			/
DEFOPCODE(Vdiv	,"divvv"	,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),VARITMETICEXPR,OPERANDS3EXPR_UPDATE(3,3,3),NULL_EXPR,0)
#undef	OPERATION

#define	OPERATION			+
DEFOPCODE(Madd	,"addmm"	,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),MARITMETICEXPR,OPERANDS3EXPR_UPDATE(16,16,16),NULL_EXPR,0)
#undef	OPERATION
#define	OPERATION			-
DEFOPCODE(Msub	,"submm"	,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),MARITMETICEXPR,OPERANDS3EXPR_UPDATE(16,16,16),NULL_EXPR,0)
#undef	OPERATION


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// mulmm
#define	MULMMEXPR			{																\
									matrix	mtmp;											\
									mulmm(mtmp,op1,op2);									\
									movmm(res,mtmp);										\
							}

DEFOPCODE(Mmul	,"mulmm"	,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),MULMMEXPR,OPERANDS3EXPR_UPDATE(16,16,16),NULL_EXPR,0)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// divmm
#define	DIVMMEXPR			{																\
									matrix	inv;											\
									invertm(inv,op2);										\
									mulmm(res,op1,inv);										\
							}


DEFOPCODE(Mdiv	,"divmm"	,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),DIVMMEXPR,OPERANDS3EXPR_UPDATE(16,16,16),NULL_EXPR,0)



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// mulmp
#define	MULMPEXPR			mulmp(res,op1,op2);
#define	MULPMEXPR			mulpm(res,op1,op2);

DEFOPCODE(Mmulp	,"mulmp"	,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),MULMVEXPR,OPERANDS3EXPR_UPDATE(3,16,3),NULL_EXPR,0)
DEFOPCODE(Pmulm	,"mulpm"	,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),MULVMEXPR,OPERANDS3EXPR_UPDATE(3,3,16),NULL_EXPR,0)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// mulmv
#define	MULMVEXPR			mulmv(res,op1,op2);
#define	MULVMEXPR			mulvm(res,op1,op2);

DEFOPCODE(Mmulv	,"mulmv"	,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),MULMVEXPR,OPERANDS3EXPR_UPDATE(3,16,3),NULL_EXPR,0)
DEFOPCODE(Vmulm	,"mulvm"	,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),MULVMEXPR,OPERANDS3EXPR_UPDATE(3,3,16),NULL_EXPR,0)


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// mulmn
#define	MULMNEXPR			{												\
								matrix	mtmp;								\
								invertm(mtmp,op1);							\
								mulmn(res,mtmp,op2);						\
							}

#define	MULNMEXPR			{												\
								matrix	mtmp;								\
								invertm(mtmp,op2);							\
								mulmn(res,op1,mtmp);						\
							}


DEFOPCODE(Mmuln	,"mulmn"	,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),MULMNEXPR,OPERANDS3EXPR_UPDATE(3,16,3),NULL_EXPR,0)
DEFOPCODE(Nmulm	,"mulnm"	,3,	OPERANDS3EXPR_PRE(float *,const float *,const float *),MULNMEXPR,OPERANDS3EXPR_UPDATE(3,3,16),NULL_EXPR,0)



#define	DOTEXPR				*res	=	dotvv(op1,op2);
#define	CROSSEXPR			crossvv(res,op1,op2);

DEFOPCODE(Dot	,"dot"		,3, OPERANDS3EXPR_PRE(float *,const float *,const float *),DOTEXPR,OPERANDS3EXPR_UPDATE(1,3,3),NULL_EXPR,0)
DEFOPCODE(Cross	,"cross"	,3, OPERANDS3EXPR_PRE(float *,const float *,const float *),CROSSEXPR,OPERANDS3EXPR_UPDATE(3,3,3),NULL_EXPR,0)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
//
//
//	FORMAT CONVERSION OPERATIONS
//
//
//
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define	VFROMFEXPR		res[0]		=	op[0];		\
						res[1]		=	op[0];		\
						res[2]		=	op[0];

#define	MFROMVEXPR		res[0]		=	op[0];		\
						res[1]		=	0;			\
						res[2]		=	0;			\
						res[3]		=	0;			\
						res[4]		=	0;			\
						res[5]		=	op[1];		\
						res[6]		=	0;			\
						res[7]		=	0;			\
						res[8]		=	0;			\
						res[9]		=	0;			\
						res[10]		=	op[2];		\
						res[11]		=	0;			\
						res[12]		=	0;			\
						res[13]		=	0;			\
						res[14]		=	0;			\
						res[15]		=	1;

#define	MFROMFEXPR		res[0]		=	op[0];		\
						res[1]		=	0;			\
						res[2]		=	0;			\
						res[3]		=	0;			\
						res[4]		=	0;			\
						res[5]		=	op[0];		\
						res[6]		=	0;			\
						res[7]		=	0;			\
						res[8]		=	0;			\
						res[9]		=	0;			\
						res[10]		=	op[0];		\
						res[11]		=	0;			\
						res[12]		=	0;			\
						res[13]		=	0;			\
						res[14]		=	0;			\
						res[15]		=	1;

DEFOPCODE(Vfromf	,"vfromf"	,2,	OPERANDS2EXPR_PRE(float *,const float *),VFROMFEXPR,OPERANDS2EXPR_UPDATE(3,1),NULL_EXPR,0)
DEFOPCODE(Mfromv	,"mfromv"	,2,	OPERANDS2EXPR_PRE(float *,const float *),MFROMVEXPR,OPERANDS2EXPR_UPDATE(16,3),NULL_EXPR,0)
DEFOPCODE(Mfromf	,"mfromf"	,2,	OPERANDS2EXPR_PRE(float *,const float *),MFROMFEXPR,OPERANDS2EXPR_UPDATE(16,1),NULL_EXPR,0)


#define	VFROMF3EXPR_PRE		float		*res;								\
							const float	*x,*y,*z;							\
							operand(0,res,float *);							\
							operand(1,x,const float *);						\
							operand(2,y,const float *);						\
							operand(3,z,const float *);	

#define	VFROMF3EXPR			res[0]	=	*x;									\
							res[1]	=	*y;									\
							res[2]	=	*z;

#define	VFROMF3EXPR_UPDATE	res	+=	3;										\
							++x;											\
							++y;											\
							++z;

#define	VFROMF3EXPR_POST

DEFOPCODE(Vfromf3	,"vfromf"	,4,	VFROMF3EXPR_PRE,VFROMF3EXPR,VFROMF3EXPR_UPDATE,VFROMF3EXPR_POST,0)

#define	MFROMF17EXPR_PRE	float		*res;								\
							const float	*e[16];								\
							operand(0,res,float *);							\
							for (int i=0;i<16;++i) {						\
								operand(i+1,e[i],const float *);			\
							}

#define	MFROMF17EXPR		for (int i=0;i<16;++i)							\
								res[i]	=	*e[i];

#define	MFROMF17EXPR_UPDATE	for (int i=0;i<16;++i)	e[i]++;					\
							res	+=	16;

#define	MFROMF17EXPR_POST

DEFOPCODE(Mfromf17	,"mfromf"	,17,	MFROMF17EXPR_PRE,MFROMF17EXPR,MFROMF17EXPR_UPDATE,MFROMF17EXPR_POST,0)



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
//
//
//	UNARY OPERATIONS
//
//
//
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// unary operate
#define	FUNARYEXPR			*res		=	OPERATION	*op;

#define	VUNARYEXPR			res[0]		=	OPERATION	op[0];		\
							res[1]		=	OPERATION	op[1];		\
							res[2]		=	OPERATION	op[2];

#define	MUNARYEXPR			res[0]		=	OPERATION	op[0];		\
							res[1]		=	OPERATION	op[1];		\
							res[2]		=	OPERATION	op[2];		\
							res[3]		=	OPERATION	op[3];		\
							res[4]		=	OPERATION	op[4];		\
							res[5]		=	OPERATION	op[5];		\
							res[6]		=	OPERATION	op[6];		\
							res[7]		=	OPERATION	op[7];		\
							res[8]		=	OPERATION	op[8];		\
							res[9]		=	OPERATION	op[9];		\
							res[10]		=	OPERATION	op[10];		\
							res[11]		=	OPERATION	op[11];		\
							res[12]		=	OPERATION	op[12];		\
							res[13]		=	OPERATION	op[13];		\
							res[14]		=	OPERATION	op[14];		\
							res[15]		=	OPERATION	op[15];

#define	SUNARYEXPR			*res		=	OPERATION	*op;

#define	OPERATION			-
DEFOPCODE(Negf	,"negf"	,2,	OPERANDS2EXPR_PRE(float *,const float *),FUNARYEXPR,OPERANDS2EXPR_UPDATE(1,1),NULL_EXPR,0)
#undef	OPERATION

#define	OPERATION			-
DEFOPCODE(Negv	,"negv"	,2,	OPERANDS2EXPR_PRE(float *,const float *),VUNARYEXPR,OPERANDS2EXPR_UPDATE(3,3),NULL_EXPR,0)
#undef	OPERATION

#define	OPERATION			-
DEFOPCODE(Negm	,"negm"	,2,	OPERANDS2EXPR_PRE(float *,const float *),MUNARYEXPR,OPERANDS2EXPR_UPDATE(16,16),NULL_EXPR,0)
#undef	OPERATION


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
//
//
//	DATA MOVEMENT OPERATIONS
//
//
//
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define OPERATION
DEFOPCODE(Moveff	,"moveff"	,2,	OPERANDS2EXPR_PRE(float *,const float *),FUNARYEXPR,OPERANDS2EXPR_UPDATE(1,1),		NULL_EXPR,0)
DEFOPCODE(Movevv	,"movevv"	,2,	OPERANDS2EXPR_PRE(float *,const float *),VUNARYEXPR,OPERANDS2EXPR_UPDATE(3,3),		NULL_EXPR,0)
DEFOPCODE(Movemm	,"movemm"	,2,	OPERANDS2EXPR_PRE(float *,const float *),MUNARYEXPR,OPERANDS2EXPR_UPDATE(16,16),	NULL_EXPR,0)
DEFOPCODE(Movess	,"movess"	,2,	OPERANDS2EXPR_PRE(float *,const float *),SUNARYEXPR,OPERANDS2EXPR_UPDATE(1,1),		NULL_EXPR,0)
DEFOPCODE(VUFloat	,"vufloat"	,2,	OPERANDS2EXPR_PRE(float *,const float *),FUNARYEXPR,OPERANDS2EXPR_UPDATE(1,0),		NULL_EXPR,0)
DEFOPCODE(VUVector	,"vuvector"	,2,	OPERANDS2EXPR_PRE(float *,const float *),VUNARYEXPR,OPERANDS2EXPR_UPDATE(3,0),		NULL_EXPR,0)
DEFOPCODE(VUMatrix	,"vumatrix"	,2,	OPERANDS2EXPR_PRE(float *,const float *),MUNARYEXPR,OPERANDS2EXPR_UPDATE(16,0),		NULL_EXPR,0)
DEFOPCODE(VUString	,"vustring"	,2,	OPERANDS2EXPR_PRE(float *,const float *),SUNARYEXPR,OPERANDS2EXPR_UPDATE(1,0),		NULL_EXPR,0)
#undef OPERATION




/////////////////////////////////////////////////////////////////
//
//	Array opcodes
//
/////////////////////////////////////////////////////////////////
#define	ARRAY_PRE(_t)	_t			res;							\
						_t			op1;							\
						const float	*op2;							\
						int			op1Step;						\
						operand(0,res,_t);							\
						operandSize(1,op1,op1Step,_t);				\
						operand(2,op2,const float *);

#define	ARRAY_UPDATE(__rs)											\
						res		+=	__rs;							\
						op1		+=	op1Step;						\
						op2++;

#define	UARRAY_UPDATE(__rs)											\
						res		+=	__rs;



#define	FFROMAEXPR	*res	=	op1[(int) (*op2)];
#define	VFROMAEXPR	movvv(res,&op1[((int) (*op2))*3]);
#define	MFROMAEXPR	movmm(res,&op1[((int) (*op2))*16]);
#define	SFROMAEXPR	*res	=	op1[(int) (*op2)];

DEFOPCODE(FFromA	,"ffroma"	,3,	ARRAY_PRE(float *),FFROMAEXPR,ARRAY_UPDATE(1),	NULL_EXPR,0)
DEFOPCODE(VFromA	,"vfroma"	,3,	ARRAY_PRE(float *),VFROMAEXPR,ARRAY_UPDATE(3),	NULL_EXPR,0)
DEFOPCODE(MFromA	,"mfroma"	,3,	ARRAY_PRE(float *),MFROMAEXPR,ARRAY_UPDATE(16),	NULL_EXPR,0)
DEFOPCODE(SFromA	,"sfroma"	,3,	ARRAY_PRE(char **),SFROMAEXPR,ARRAY_UPDATE(1),	NULL_EXPR,0)

DEFOPCODE(UFFromA	,"uffroma"	,3,	ARRAY_PRE(float *),FFROMAEXPR,UARRAY_UPDATE(1),		NULL_EXPR,0)
DEFOPCODE(UVFromA	,"uvfroma"	,3,	ARRAY_PRE(float *),VFROMAEXPR,UARRAY_UPDATE(3),		NULL_EXPR,0)
DEFOPCODE(UMFromA	,"umfroma"	,3,	ARRAY_PRE(float *),MFROMAEXPR,UARRAY_UPDATE(16),	NULL_EXPR,0)
DEFOPCODE(USFromA	,"usfroma"	,3,	ARRAY_PRE(char **),SFROMAEXPR,UARRAY_UPDATE(1),		NULL_EXPR,0)


#undef ARRAY_PRE
#undef ARRAY_UPDATE



#define	ARRAY_PRE(_t)	_t			res;							\
						const float	*op1;							\
						_t			op2;							\
						int			resStep;						\
						operandSize(0,res,resStep,_t);				\
						operand(1,op1,const float *);				\
						operand(2,op2,_t);

#define	ARRAY_UPDATE(__os)											\
						res		+=	resStep;						\
						++op1;										\
						op2		+=	__os;


#define	FTOAEXPR	res[(int) (*op1)]	=	*op2;
#define	VTOAEXPR	movvv(res + ((int) (*op1))*3,op2);
#define	MTOAEXPR	movmm(res + ((int) (*op1))*16,op2);
#define	STOAEXPR	res[(int) (*op1)]	=	*op2;


DEFOPCODE(FToA		,"ftoa"		,3,	ARRAY_PRE(float *),FTOAEXPR,ARRAY_UPDATE(1),NULL_EXPR,0)
DEFOPCODE(VToA		,"vtoa"		,3,	ARRAY_PRE(float *),VTOAEXPR,ARRAY_UPDATE(3),NULL_EXPR,0)
DEFOPCODE(MToA		,"mtoa"		,3,	ARRAY_PRE(float *),MTOAEXPR,ARRAY_UPDATE(16),NULL_EXPR,0)
DEFOPCODE(SToA		,"stoa"		,3,	ARRAY_PRE(char **),STOAEXPR,ARRAY_UPDATE(1),NULL_EXPR,0)

#undef ARRAY_PRE
#undef ARRAY_UPDATE


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// return
#define	RETURN_PRE		BREAK;


DEFOPCODE(Return	,"return"	,0,RETURN_PRE,NULL_EXPR,NULL_EXPR,NULL_EXPR,0)


// Include RenderMan Shading Language specific opcodes here
#include "shaderOpcodes.h"

