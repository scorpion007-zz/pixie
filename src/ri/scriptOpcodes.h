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
#define	IF2EXPR_PRE			TCode	*op;														\
							int		i;															\
							operand(0,op);														\
							for (i=0;i<numVertices;i++,op++,tags++)	{							\
								if (*tags) {													\
									(*tags)++;													\
								} else {														\
									if (op->integer) {											\
										*tags	=	0;											\
									} else	{													\
										*tags	=	1;											\
										numActive--;											\
										numPassive++;											\
									}															\
								}																\
							}

#define	IF2EXPR_POST		if (numActive == 0) {												\
								jmp(argument(1));												\
							}

DEFOPCODE(If2	,"if"	,2,	IF2EXPR_PRE,NULL_EXPR,NULL_EXPR,IF2EXPR_POST,0)




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	elseif

#define	ELSEIFEXPR_PRE		for (int i=0;i<numVertices;i++,tags++)	{							\
								if (*tags <= 1) {												\
									if (*tags == 1) {											\
										*tags	=	0;											\
										numActive++;											\
										numPassive--;											\
									} else {													\
										*tags	=	1;											\
										numActive--;											\
										numPassive++;											\
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
#define	ENDIFEXPR_PRE		int	i;																\
							for (i=0;i<numVertices;i++,tags++)	{								\
								if (*tags) {													\
									(*tags)--;													\
																								\
									if (*tags == 0) {											\
										numActive++;											\
										numPassive--;											\
									}															\
								}																\
							}

#define	ENDIFEXPR_POST

DEFOPCODE(Endif	,"endif"	,0,	ENDIFEXPR_PRE,NULL_EXPR,NULL_EXPR,ENDIFEXPR_POST,0)


#undef	ENDIFEXPR_PRE
#undef	ENDIFEXPR_POST




















///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	forbegin <body> <continue> <end>
#define	FORBEGIN3EXPR_PRE	int		bodyIndex;													\
							int		continueIndex;												\
							int		endIndex;													\
							bodyIndex		=	argument(0);									\
							continueIndex	=	argument(1);									\
							endIndex		=	argument(2);									\
							beginConditional();													\
							lastConditional->forStart		=	bodyIndex;						\
							lastConditional->forContinue	=	continueIndex;					\
							lastConditional->forEnd			=	endIndex;						\
							lastConditional->forExecCount	=	0;
							
DEFOPCODE(Forbegin3	,"forbegin"	,3,	FORBEGIN3EXPR_PRE,NULL_EXPR,NULL_EXPR,NULL_EXPR,0)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	for <cond>
#define	FOR3EXPR_PRE		TCode	*op;														\
							operand(0,op);														\
							lastConditional->forExecCount++;									\
							for (int i=numVertices;i>0;i--,op++,tags++)	{						\
								if (*tags) {													\
									(*tags)++;													\
								} else {														\
									if (op->integer) {											\
									} else	{													\
										*tags	=	lastConditional->forExecCount;				\
										numActive--;											\
										numPassive++;											\
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
							for (int i=numVertices;i>0;i--,tags++)	{							\
								if (*tags) {													\
									*tags	-=	lastConditional->forExecCount;					\
									if (*tags	<= 0)	{										\
										*tags	=	0;											\
										numActive++;											\
										numPassive--;											\
									}															\
								}																\
							}																	\
							endConditional();
DEFOPCODE(Forend3	,"forend"	,0,	FOREND3EXPR_PRE,NULL_EXPR,NULL_EXPR,NULL_EXPR,0)

#undef FOREND3EXPR_PRE


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	break
#define	BREAK1EXPR_PRE		for (int i=0;i<numVertices;i++,tags++)	{							\
								if (*tags	== 0)	{											\
									*tags	=	lastConditional->forExecCount;					\
									numPassive++;												\
									numActive--;												\
								}																\
							}

#define	BREAK1EXPR_POST		if (numActive == 0) {												\
								jmp(lastConditional->forEnd);									\
							}

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


#define	OPERANDS3EXPR_PRE		TCode		*res;												\
								const TCode	*op1,*op2;											\
								operand(0,res);													\
								operand(1,op1);													\
								operand(2,op2);


#define	OPERANDS3EXPR_UPDATE(__rs,__op1s,__op2s)												\
								res	+=	__rs;													\
								op1	+=	__op1s;													\
								op2	+=	__op2s;



#define	OPERANDS2EXPR_PRE		TCode		*res;												\
								const TCode	*op;												\
								operand(0,res);													\
								operand(1,op);

#define	OPERANDS2EXPR_UPDATE(__rs,__ops)														\
								res	+=	__rs;													\
								op	+=	__ops;



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// fcmp

#define	FCMPEXPR			if (op1->real OPERATION op2->real)	res->integer	=	TRUE;		\
							else								res->integer	=	FALSE;



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// vcmp
#define	VCMPEXPR			if (	(op1[0].real OPERATION op2[0].real) &&								\
									(op1[1].real OPERATION op2[1].real) &&								\
									(op1[2].real OPERATION op2[2].real)	)	res->integer	=	TRUE;	\
							else	res->integer	=	FALSE;


#define	VNCMPEXPR			if (	(op1[0].real OPERATION op2[0].real) ||								\
									(op1[1].real OPERATION op2[1].real) ||								\
									(op1[2].real OPERATION op2[2].real)	)	res->integer	=	TRUE;	\
							else	res->integer	=	FALSE;



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// mcmp
#define	MCMPEXPR			int	index;																		\
							int	result	=	TRUE;															\
							for (index=0;index<16;index++)													\
								if (!(op1[index].real OPERATION op2[index].real))	result	&=	FALSE;		\
							res->integer	=	result;

#define	MNCMPEXPR			int	index;																		\
							int	result	=	TRUE;															\
							for (index=0;index<16;index++)													\
								if (!(op1[index].real OPERATION op2[index].real))	result	|=	FALSE;		\
							res->integer	=	result;


#define	SEQLEXPR			if (strcmp(op1->string,op2->string) == 0)	res->integer	=	TRUE;			\
							else										res->integer	=	FALSE;

#define	SNEQLEXPR			if (strcmp(op1->string,op2->string) != 0)	res->integer	=	TRUE;			\
							else										res->integer	=	FALSE;




#define	OPERATION			==
DEFOPCODE(Feql2		,"feql"		,3,	OPERANDS3EXPR_PRE,FCMPEXPR,OPERANDS3EXPR_UPDATE(1,1,1),		NULL_EXPR,0)
DEFOPCODE(Veql2		,"veql"		,3,	OPERANDS3EXPR_PRE,VCMPEXPR,OPERANDS3EXPR_UPDATE(1,3,3),		NULL_EXPR,0)
DEFOPCODE(Meql2		,"meql"		,3,	OPERANDS3EXPR_PRE,MCMPEXPR,OPERANDS3EXPR_UPDATE(1,16,16),	NULL_EXPR,0)
DEFOPCODE(Seql2		,"seql"		,3,	OPERANDS3EXPR_PRE,SEQLEXPR,OPERANDS3EXPR_UPDATE(1,1,1),		NULL_EXPR,0)
#undef	OPERATION

#define	OPERATION			!=
DEFOPCODE(Fneql2	,"fneql"	,3,	OPERANDS3EXPR_PRE,FCMPEXPR,OPERANDS3EXPR_UPDATE(1,1,1),		NULL_EXPR,0)
DEFOPCODE(Vneql2	,"vneql"	,3,	OPERANDS3EXPR_PRE,VNCMPEXPR,OPERANDS3EXPR_UPDATE(1,3,3),	NULL_EXPR,0)
DEFOPCODE(Mneql2	,"mneql"	,3,	OPERANDS3EXPR_PRE,MNCMPEXPR,OPERANDS3EXPR_UPDATE(1,16,16),	NULL_EXPR,0)
DEFOPCODE(Sneql2	,"sneql"	,3,	OPERANDS3EXPR_PRE,SNEQLEXPR,OPERANDS3EXPR_UPDATE(1,1,1),	NULL_EXPR,0)
#undef OPERATION

#define	OPERATION			>
DEFOPCODE(Fgt2		,"fgt"		,3,	OPERANDS3EXPR_PRE,FCMPEXPR,OPERANDS3EXPR_UPDATE(1,1,1),		NULL_EXPR,0)
DEFOPCODE(Vgt2		,"vgt"		,3,	OPERANDS3EXPR_PRE,VCMPEXPR,OPERANDS3EXPR_UPDATE(1,3,3),		NULL_EXPR,0)
#undef OPERATION

#define	OPERATION			<
DEFOPCODE(Flt2		,"flt"		,3,	OPERANDS3EXPR_PRE,FCMPEXPR,OPERANDS3EXPR_UPDATE(1,1,1),		NULL_EXPR,0)
DEFOPCODE(Vlt2		,"vlt"		,3,	OPERANDS3EXPR_PRE,VCMPEXPR,OPERANDS3EXPR_UPDATE(1,3,3),		NULL_EXPR,0)
#undef OPERATION

#define	OPERATION			>=
DEFOPCODE(Fgte2		,"fegt"		,3,	OPERANDS3EXPR_PRE,FCMPEXPR,OPERANDS3EXPR_UPDATE(1,1,1),		NULL_EXPR,0)
DEFOPCODE(Vgte2		,"vegt"		,3,	OPERANDS3EXPR_PRE,VCMPEXPR,OPERANDS3EXPR_UPDATE(1,3,3),		NULL_EXPR,0)
#undef OPERATION

#define	OPERATION			<=
DEFOPCODE(Flte2		,"felt"		,3,	OPERANDS3EXPR_PRE,FCMPEXPR,OPERANDS3EXPR_UPDATE(1,1,1),		NULL_EXPR,0)
DEFOPCODE(Vlte2		,"velt"		,3,	OPERANDS3EXPR_PRE,VCMPEXPR,OPERANDS3EXPR_UPDATE(1,3,3),		NULL_EXPR,0)
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
#define	LOGICEXPR			res->integer	=	op1->integer OPERATION op2->integer;


#define	OPERATION			&
DEFOPCODE(And0	,"and"	,3,	OPERANDS3EXPR_PRE,LOGICEXPR,OPERANDS3EXPR_UPDATE(1,1,1),NULL_EXPR,0)
#undef	OPERATION

#define	OPERATION			|
DEFOPCODE(Or0	,"or"	,3,	OPERANDS3EXPR_PRE,LOGICEXPR,OPERANDS3EXPR_UPDATE(1,1,1),NULL_EXPR,0)
#undef	OPERATION

#define	OPERATION			^
DEFOPCODE(Xor0	,"xor"	,3,	OPERANDS3EXPR_PRE,LOGICEXPR,OPERANDS3EXPR_UPDATE(1,1,1),NULL_EXPR,0)
#undef	OPERATION

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// nxor
#define	NXOREXPR			res->integer	=	~(op1->integer ^ op2->integer);

DEFOPCODE(Nxor	,"nxor"	,3, OPERANDS3EXPR_PRE,NXOREXPR,OPERANDS3EXPR_UPDATE(1,1,1),NULL_EXPR,0)


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// not
#define	NOTEXPR			res->integer	=	~op->integer;


DEFOPCODE(Not	,"not"	,2, OPERANDS2EXPR_PRE,NOTEXPR,OPERANDS2EXPR_UPDATE(1,1),NULL_EXPR,0)



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

#define	FARITMETICEXPR		res->real		=	op1->real OPERATION op2->real;

#define	VARITMETICEXPR		res[0].real		=	op1[0].real OPERATION op2[0].real;		\
							res[1].real		=	op1[1].real OPERATION op2[1].real;		\
							res[2].real		=	op1[2].real OPERATION op2[2].real;

#define	MARITMETICEXPR		res[0].real		=	op1[0].real OPERATION op2[0].real;		\
							res[1].real		=	op1[1].real OPERATION op2[1].real;		\
							res[2].real		=	op1[2].real OPERATION op2[2].real;		\
							res[3].real		=	op1[3].real OPERATION op2[3].real;		\
							res[4].real		=	op1[4].real OPERATION op2[4].real;		\
							res[5].real		=	op1[5].real OPERATION op2[5].real;		\
							res[6].real		=	op1[6].real OPERATION op2[6].real;		\
							res[7].real		=	op1[7].real OPERATION op2[7].real;		\
							res[8].real		=	op1[8].real OPERATION op2[8].real;		\
							res[9].real		=	op1[9].real OPERATION op2[9].real;		\
							res[10].real	=	op1[10].real OPERATION op2[10].real;	\
							res[11].real	=	op1[11].real OPERATION op2[11].real;	\
							res[12].real	=	op1[12].real OPERATION op2[12].real;	\
							res[13].real	=	op1[13].real OPERATION op2[13].real;	\
							res[14].real	=	op1[14].real OPERATION op2[14].real;	\
							res[15].real	=	op1[15].real OPERATION op2[15].real;

#define	OPERATION			+
DEFOPCODE(Fadd	,"addff"	,3,	OPERANDS3EXPR_PRE,FARITMETICEXPR,OPERANDS3EXPR_UPDATE(1,1,1),NULL_EXPR,0)
#undef	OPERATION
#define	OPERATION			-
DEFOPCODE(Fsub	,"subff"	,3,	OPERANDS3EXPR_PRE,FARITMETICEXPR,OPERANDS3EXPR_UPDATE(1,1,1),NULL_EXPR,0)
#undef	OPERATION
#define	OPERATION			*
DEFOPCODE(Fmul	,"mulff"	,3,	OPERANDS3EXPR_PRE,FARITMETICEXPR,OPERANDS3EXPR_UPDATE(1,1,1),NULL_EXPR,0)
#undef	OPERATION
#define	OPERATION			/
DEFOPCODE(Fdiv	,"divff"	,3,	OPERANDS3EXPR_PRE,FARITMETICEXPR,OPERANDS3EXPR_UPDATE(1,1,1),NULL_EXPR,0)
#undef	OPERATION


#define	OPERATION			+
DEFOPCODE(Vadd	,"addvv"	,3,	OPERANDS3EXPR_PRE,VARITMETICEXPR,OPERANDS3EXPR_UPDATE(3,3,3),NULL_EXPR,0)
#undef	OPERATION
#define	OPERATION			-
DEFOPCODE(Vsub	,"subvv"	,3,	OPERANDS3EXPR_PRE,VARITMETICEXPR,OPERANDS3EXPR_UPDATE(3,3,3),NULL_EXPR,0)
#undef	OPERATION
#define	OPERATION			*
DEFOPCODE(Vmul	,"mulvv"	,3,	OPERANDS3EXPR_PRE,VARITMETICEXPR,OPERANDS3EXPR_UPDATE(3,3,3),NULL_EXPR,0)
#undef	OPERATION
#define	OPERATION			/
DEFOPCODE(Vdiv	,"divvv"	,3,	OPERANDS3EXPR_PRE,VARITMETICEXPR,OPERANDS3EXPR_UPDATE(3,3,3),NULL_EXPR,0)
#undef	OPERATION

#define	OPERATION			+
DEFOPCODE(Madd	,"addmm"	,3,	OPERANDS3EXPR_PRE,MARITMETICEXPR,OPERANDS3EXPR_UPDATE(16,16,16),NULL_EXPR,0)
#undef	OPERATION
#define	OPERATION			-
DEFOPCODE(Msub	,"submm"	,3,	OPERANDS3EXPR_PRE,MARITMETICEXPR,OPERANDS3EXPR_UPDATE(16,16,16),NULL_EXPR,0)
#undef	OPERATION


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// mulmm
#define	MULMMEXPR			{																\
									matrix	mtmp;											\
									mulmm(mtmp,&op1->real,&op2->real);						\
									movmm(&res->real,mtmp);									\
							}

DEFOPCODE(Mmul	,"mulmm"	,3,	OPERANDS3EXPR_PRE,MULMMEXPR,OPERANDS3EXPR_UPDATE(16,16,16),NULL_EXPR,0)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// divmm
#define	DIVMMEXPR			{																\
									matrix	inv;											\
									invertm(inv,&op2->real);								\
									mulmm(&res->real,&op1->real,inv);						\
							}


DEFOPCODE(Mdiv	,"divmm"	,3,	OPERANDS3EXPR_PRE,DIVMMEXPR,OPERANDS3EXPR_UPDATE(16,16,16),NULL_EXPR,0)



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// mulmp
#define	MULMPEXPR			mulmp(&res->real,&op1->real,&op2->real);
#define	MULPMEXPR			mulpm(&res->real,&op1->real,&op2->real);

DEFOPCODE(Mmulp	,"mulmp"	,3,	OPERANDS3EXPR_PRE,MULMVEXPR,OPERANDS3EXPR_UPDATE(3,16,3),NULL_EXPR,0)
DEFOPCODE(Pmulm	,"mulpm"	,3,	OPERANDS3EXPR_PRE,MULVMEXPR,OPERANDS3EXPR_UPDATE(3,3,16),NULL_EXPR,0)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// mulmv
#define	MULMVEXPR			mulmv(&res->real,&op1->real,&op2->real);
#define	MULVMEXPR			mulvm(&res->real,&op1->real,&op2->real);

DEFOPCODE(Mmulv	,"mulmv"	,3,	OPERANDS3EXPR_PRE,MULMVEXPR,OPERANDS3EXPR_UPDATE(3,16,3),NULL_EXPR,0)
DEFOPCODE(Vmulm	,"mulvm"	,3,	OPERANDS3EXPR_PRE,MULVMEXPR,OPERANDS3EXPR_UPDATE(3,3,16),NULL_EXPR,0)


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// mulmn
#define	MULMNEXPR			{												\
								matrix	mtmp;								\
								invertm(mtmp,&op1->real);					\
								mulmn(&res->real,mtmp,&op2->real);			\
							}

#define	MULNMEXPR			{												\
								matrix	mtmp;								\
								invertm(mtmp,&op2->real);					\
								mulmn(&res->real,&op1->real,mtmp);			\
							}


DEFOPCODE(Mmuln	,"mulmn"	,3,	OPERANDS3EXPR_PRE,MULMNEXPR,OPERANDS3EXPR_UPDATE(3,16,3),NULL_EXPR,0)
DEFOPCODE(Nmulm	,"mulnm"	,3,	OPERANDS3EXPR_PRE,MULNMEXPR,OPERANDS3EXPR_UPDATE(3,3,16),NULL_EXPR,0)



#define	DOTEXPR				res->real	=	dotvv(&op1->real,&op2->real);
#define	CROSSEXPR			crossvv(&res->real,&op1->real,&op2->real);

DEFOPCODE(Dot	,"dot"		,3, OPERANDS3EXPR_PRE,DOTEXPR,OPERANDS3EXPR_UPDATE(1,3,3),NULL_EXPR,0)
DEFOPCODE(Cross	,"cross"	,3, OPERANDS3EXPR_PRE,CROSSEXPR,OPERANDS3EXPR_UPDATE(3,3,3),NULL_EXPR,0)

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

#define	VFROMFEXPR		res[0].real		=	op[0].real;		\
						res[1].real		=	op[0].real;		\
						res[2].real		=	op[0].real;

#define	MFROMVEXPR		res[0].real		=	op[0].real;		\
						res[1].real		=	0;				\
						res[2].real		=	0;				\
						res[3].real		=	0;				\
						res[4].real		=	0;				\
						res[5].real		=	op[1].real;		\
						res[6].real		=	0;				\
						res[7].real		=	0;				\
						res[8].real		=	0;				\
						res[9].real		=	0;				\
						res[10].real	=	op[2].real;		\
						res[11].real	=	0;				\
						res[12].real	=	0;				\
						res[13].real	=	0;				\
						res[14].real	=	0;				\
						res[15].real	=	1;

#define	MFROMFEXPR		res[0].real		=	op[0].real;		\
						res[1].real		=	0;				\
						res[2].real		=	0;				\
						res[3].real		=	0;				\
						res[4].real		=	0;				\
						res[5].real		=	op[0].real;		\
						res[6].real		=	0;				\
						res[7].real		=	0;				\
						res[8].real		=	0;				\
						res[9].real		=	0;				\
						res[10].real	=	op[0].real;		\
						res[11].real	=	0;				\
						res[12].real	=	0;				\
						res[13].real	=	0;				\
						res[14].real	=	0;				\
						res[15].real	=	1;

DEFOPCODE(Vfromf	,"vfromf"	,2,	OPERANDS2EXPR_PRE,VFROMFEXPR,OPERANDS2EXPR_UPDATE(3,1),NULL_EXPR,0)
DEFOPCODE(Mfromv	,"mfromv"	,2,	OPERANDS2EXPR_PRE,MFROMVEXPR,OPERANDS2EXPR_UPDATE(16,3),NULL_EXPR,0)
DEFOPCODE(Mfromf	,"mfromf"	,2,	OPERANDS2EXPR_PRE,MFROMFEXPR,OPERANDS2EXPR_UPDATE(16,1),NULL_EXPR,0)


#define	VFROMF3EXPR_PRE		TCode		*res;								\
							const TCode	*x,*y,*z;							\
							operand(0,res);									\
							operand(1,x);									\
							operand(2,y);									\
							operand(3,z);	

#define	VFROMF3EXPR			res[0].real	=	x[0].real;						\
							res[1].real	=	y[0].real;						\
							res[2].real	=	z[0].real;

#define	VFROMF3EXPR_UPDATE	res	+=	3;										\
							x	++;											\
							y	++;											\
							z	++;

#define	VFROMF3EXPR_POST

DEFOPCODE(Vfromf3	,"vfromf"	,4,	VFROMF3EXPR_PRE,VFROMF3EXPR,VFROMF3EXPR_UPDATE,VFROMF3EXPR_POST,0)

#define	MFROMF17EXPR_PRE	TCode		*res;								\
							const TCode	*e[16];								\
							int			i;									\
							operand(0,res);									\
							for (i=0;i<16;i++) {							\
								operand(i+1,e[i]);							\
							}

#define	MFROMF17EXPR		for (i=0;i<16;i++)								\
								res[i].real	=	e[i]->real;

#define	MFROMF17EXPR_UPDATE	for (i=0;i<16;i++)	e[i]++;						\
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
#define	FUNARYEXPR			res->real		=	OPERATION	op->real;

#define	VUNARYEXPR			res[0].real		=	OPERATION	op[0].real;		\
							res[1].real		=	OPERATION	op[1].real;		\
							res[2].real		=	OPERATION	op[2].real;

#define	MUNARYEXPR			res[0].real		=	OPERATION	op[0].real;		\
							res[1].real		=	OPERATION	op[1].real;		\
							res[2].real		=	OPERATION	op[2].real;		\
							res[3].real		=	OPERATION	op[3].real;		\
							res[4].real		=	OPERATION	op[4].real;		\
							res[5].real		=	OPERATION	op[5].real;		\
							res[6].real		=	OPERATION	op[6].real;		\
							res[7].real		=	OPERATION	op[7].real;		\
							res[8].real		=	OPERATION	op[8].real;		\
							res[9].real		=	OPERATION	op[9].real;		\
							res[10].real	=	OPERATION	op[10].real;	\
							res[11].real	=	OPERATION	op[11].real;	\
							res[12].real	=	OPERATION	op[12].real;	\
							res[13].real	=	OPERATION	op[13].real;	\
							res[14].real	=	OPERATION	op[14].real;	\
							res[15].real	=	OPERATION	op[15].real;

#define	SUNARYEXPR			res->string		=	OPERATION	op->string;

#define	OPERATION			-
DEFOPCODE(Negf	,"negf"	,2,	OPERANDS2EXPR_PRE,FUNARYEXPR,OPERANDS2EXPR_UPDATE(1,1),NULL_EXPR,0)
#undef	OPERATION

#define	OPERATION			-
DEFOPCODE(Negv	,"negv"	,2,	OPERANDS2EXPR_PRE,VUNARYEXPR,OPERANDS2EXPR_UPDATE(3,3),NULL_EXPR,0)
#undef	OPERATION

#define	OPERATION			-
DEFOPCODE(Negm	,"negm"	,2,	OPERANDS2EXPR_PRE,MUNARYEXPR,OPERANDS2EXPR_UPDATE(16,16),NULL_EXPR,0)
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
DEFOPCODE(Moveff	,"moveff"	,2,	OPERANDS2EXPR_PRE,FUNARYEXPR,OPERANDS2EXPR_UPDATE(1,1),		NULL_EXPR,0)
DEFOPCODE(Movevv	,"movevv"	,2,	OPERANDS2EXPR_PRE,VUNARYEXPR,OPERANDS2EXPR_UPDATE(3,3),		NULL_EXPR,0)
DEFOPCODE(Movemm	,"movemm"	,2,	OPERANDS2EXPR_PRE,MUNARYEXPR,OPERANDS2EXPR_UPDATE(16,16),	NULL_EXPR,0)
DEFOPCODE(Movess	,"movess"	,2,	OPERANDS2EXPR_PRE,SUNARYEXPR,OPERANDS2EXPR_UPDATE(1,1),		NULL_EXPR,0)
DEFOPCODE(VUFloat	,"vufloat"	,2,	OPERANDS2EXPR_PRE,FUNARYEXPR,OPERANDS2EXPR_UPDATE(1,0),		NULL_EXPR,0)
DEFOPCODE(VUVector	,"vuvector"	,2,	OPERANDS2EXPR_PRE,VUNARYEXPR,OPERANDS2EXPR_UPDATE(3,0),		NULL_EXPR,0)
DEFOPCODE(VUMatrix	,"vumatrix"	,2,	OPERANDS2EXPR_PRE,MUNARYEXPR,OPERANDS2EXPR_UPDATE(16,0),	NULL_EXPR,0)
DEFOPCODE(VUString	,"vustring"	,2,	OPERANDS2EXPR_PRE,SUNARYEXPR,OPERANDS2EXPR_UPDATE(1,0),		NULL_EXPR,0)
DEFOPCODE(VUBoolean	,"vuboolean",2,	OPERANDS2EXPR_PRE,FUNARYEXPR,OPERANDS2EXPR_UPDATE(1,0),		NULL_EXPR,0)
#undef OPERATION




/////////////////////////////////////////////////////////////////
//
//	FIXME : Array opcodes
//
// IMPORTANT: The array index is assumed to be uniform
/////////////////////////////////////////////////////////////////
#define	ARRAY_PRE		TCode		*res;							\
						const TCode	*op1,*op2;						\
						int			op1Step;						\
						operand(0,res);								\
						operandSize(1,op1,op1Step);					\
						operand(2,op2);

#define	ARRAY_UPDATE(__rs)											\
						res		+=	__rs;							\
						op1		+=	op1Step;

#define	UARRAY_UPDATE(__rs)											\
						res		+=	__rs;



#define	FFROMAEXPR	res->real	=	op1[(int) op2->real].real;
#define	VFROMAEXPR	movvv(&res->real,&op1[((int) op2->real)*3].real);
#define	MFROMAEXPR	movmm(&res->real,&op1[((int) op2->real)*16].real);
#define	SFROMAEXPR	res->string	=	op1[(int) op2->real].string;

DEFOPCODE(FFromA	,"ffroma"	,3,	ARRAY_PRE,FFROMAEXPR,ARRAY_UPDATE(1),	NULL_EXPR,0)
DEFOPCODE(VFromA	,"vfroma"	,3,	ARRAY_PRE,VFROMAEXPR,ARRAY_UPDATE(3),	NULL_EXPR,0)
DEFOPCODE(MFromA	,"mfroma"	,3,	ARRAY_PRE,MFROMAEXPR,ARRAY_UPDATE(16),	NULL_EXPR,0)
DEFOPCODE(SFromA	,"sfroma"	,3,	ARRAY_PRE,SFROMAEXPR,ARRAY_UPDATE(1),	NULL_EXPR,0)

DEFOPCODE(UFFromA	,"uffroma"	,3,	ARRAY_PRE,FFROMAEXPR,UARRAY_UPDATE(1),	NULL_EXPR,0)
DEFOPCODE(UVFromA	,"uvfroma"	,3,	ARRAY_PRE,VFROMAEXPR,UARRAY_UPDATE(3),	NULL_EXPR,0)
DEFOPCODE(UMFromA	,"umfroma"	,3,	ARRAY_PRE,MFROMAEXPR,UARRAY_UPDATE(16),	NULL_EXPR,0)
DEFOPCODE(USFromA	,"usfroma"	,3,	ARRAY_PRE,SFROMAEXPR,UARRAY_UPDATE(1),	NULL_EXPR,0)


#undef ARRAY_PRE
#undef ARRAY_UPDATE



#define	ARRAY_PRE		TCode		*res;							\
						const TCode	*op1,*op2;						\
						int			resStep;						\
						operandSize(0,res,resStep);					\
						operand(1,op1);								\
						operand(2,op2);

// IMPORTANT: The array index is assumed to be uniform !!!

#define	ARRAY_UPDATE(__os)											\
						res		+=	resStep;						\
						op2		+=	__os;


#define	FTOAEXPR	res[(int) op1->real].real	=	op2->real;
#define	VTOAEXPR	movvv(&res[((int) op1->real)*3].real,&op2->real);
#define	MTOAEXPR	movmm(&res[((int) op1->real)*16].real,&op2->real);
#define	STOAEXPR	res[(int) op1->real].string	=	op2->string;


DEFOPCODE(FToA		,"ftoa"		,3,	ARRAY_PRE,FTOAEXPR,ARRAY_UPDATE(1),NULL_EXPR,0)
DEFOPCODE(VToA		,"vtoa"		,3,	ARRAY_PRE,VTOAEXPR,ARRAY_UPDATE(3),NULL_EXPR,0)
DEFOPCODE(MToA		,"mtoa"		,3,	ARRAY_PRE,MTOAEXPR,ARRAY_UPDATE(16),NULL_EXPR,0)
DEFOPCODE(SToA		,"stoa"		,3,	ARRAY_PRE,STOAEXPR,ARRAY_UPDATE(1),NULL_EXPR,0)

#undef ARRAY_PRE
#undef ARRAY_UPDATE


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// return
#define	RETURN_PRE		BREAK;


DEFOPCODE(Return	,"return"	,0,RETURN_PRE,NULL_EXPR,NULL_EXPR,NULL_EXPR,0)


// Include RenderMan Shading Language specific opcodes here
#include "shaderOpcodes.h"

