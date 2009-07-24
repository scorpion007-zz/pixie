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
//  File				:	expression.cpp
//  Classes				:	Expression classes
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include <string.h>

#include "common/os.h"
#include "expression.h"
#include "opcodes.h"
#include "sdr.h"

extern	CScriptContext	*sdr;

#define	fprintf		if (out != NULL)	fprintf

///////////////////////////////////////////////////////////////////////
// Function				:	getContainer
// Description			:	Generate uniform 2 varying conversion
// Return Value			:	-
// Comments				:
inline	void	getContainer(FILE *out,int type,CVariable *&dest,CExpression *src) {
	if (type & SLC_UNIFORM) {
		if (src->type & SLC_UNIFORM) {
			// No action required
			if (dest == NULL) {
				dest	=	sdr->lockRegister(src->type);
				src->getCode(out,dest);
			}
		} else {
			// Varying to uniform assignment
			sdr->fatal("Varying to uniform assignment\n");
		}
	} else {
		if (src->type & SLC_UNIFORM) {
			// Uniform to varying assignment
			CVariable	*nDest	=	sdr->lockRegister(src->type ^ SLC_UNIFORM);
			const char	*opcode;

			if (dest == NULL) {
				dest	=	sdr->lockRegister(src->type);
				src->getCode(out,dest);
			}

			// Uniform to varying assignment
			if (src->type & SLC_FLOAT) {
				opcode	=	opcodeVUFloat;
			} else if (src->type & SLC_VECTOR) {
				opcode	=	opcodeVUVector;
			} else if (src->type & SLC_MATRIX) {
				opcode	=	opcodeVUMatrix;
			} else if (src->type & SLC_STRING) {
				opcode	=	opcodeVUString;
			} else {
				sdr->fatal(constantBug);
			}

			fprintf(out,"%s %s %s\n",opcode,nDest->codeName(),dest->codeName());

			if (dest != NULL) {
				sdr->releaseRegister(dest);
			}

			dest	=	nDest;
		} else {
			// No action required
			if (dest == NULL) {
				dest	=	sdr->lockRegister(src->type);
				src->getCode(out,dest);
			}
		}
	}
}


///////////////////////////////////////////////////////////////////////
// Function				:	getContainer
// Description			:	Generate uniform 2 varying conversion
// Return Value			:	-
// Comments				:
inline	void	getContainer(FILE *out,CVariable *dest,CVariable *src) {
	if (dest->type & SLC_UNIFORM) {
		if (src->type & SLC_UNIFORM) {
			sdr->fatal(constantBug);
		} else {
			// Varying to uniform assignment
			sdr->fatal("Varying to uniform assignment\n");
		}
	} else {
		if (src->type & SLC_UNIFORM) {
			// Uniform to varying assignment
			const char		*opcode;

			// Uniform to varying assignment
			if (src->type & SLC_FLOAT) {
				opcode	=	opcodeVUFloat;
			} else if (src->type & SLC_VECTOR) {
				opcode	=	opcodeVUVector;
			} else if (src->type & SLC_MATRIX) {
				opcode	=	opcodeVUMatrix;
			} else if (src->type & SLC_STRING) {
				opcode	=	opcodeVUString;
			} else {
			}

			fprintf(out,"%s %s %s\n",opcode,dest->codeName(),src->codeName());
		} else {
			sdr->fatal(constantBug);
		}
	}
}


///////////////////////////////////////////////////////////////////////
// Function				:	getContainer
// Description			:	Generate uniform 2 varying conversion
// Return Value			:	-
// Comments				:
inline	void	getContainer(FILE *out,CVariable *dest,CExpression *src) {
	if (dest->type & SLC_UNIFORM) {
		if (src->type & SLC_UNIFORM) {
			getConversion(out,dest,src);
		} else {
			// Varying to uniform assignment
			sdr->fatal("Varying to uniform assignment\n");
		}
	} else {
		if (src->type & SLC_UNIFORM) {
			// Uniform to varying assignment
			const char	*opcode;
			CVariable	*cVar;
			CExpression	*exp		=	getConversion(dest->type,src);
			int			allocated	=	FALSE;

			cVar	=	exp->getVariable();
			if (cVar == NULL) {
				cVar		=	sdr->lockRegister(exp->type);
				exp->getCode(out,cVar);
				allocated	=	TRUE;
			}

			// Uniform to varying assignment
			if (exp->type & SLC_FLOAT) {
				opcode	=	opcodeVUFloat;
			} else if (exp->type & SLC_VECTOR) {
				opcode	=	opcodeVUVector;
			} else if (exp->type & SLC_MATRIX) {
				opcode	=	opcodeVUMatrix;
			} else if (exp->type & SLC_STRING) {
				opcode	=	opcodeVUString;
			} else {
				sdr->fatalbailout();
			}

			fprintf(out,"%s %s %s\n",opcode,dest->codeName(),cVar->codeName());

			if (allocated) {
				sdr->releaseRegister(cVar);
			}
		} else {
			getConversion(out,dest,src);
		}
	}
}


///////////////////////////////////////////////////////////////////////
// Function				:	getContainer
// Description			:	Generate uniform 2 varying conversion
// Return Value			:	-
// Comments				:
inline	CVariable	*getContainer(FILE *out,int type,CExpression *src) {
	CVariable	*dest;

	if (type & SLC_UNIFORM) {
		if (src->type & SLC_UNIFORM) {
			dest	=	src->getVariable();
			if (dest == NULL) {
				dest	=	sdr->lockRegister(src->type);
				src->getCode(out,dest);
			}
		} else {
			// Varying to uniform assignment
			sdr->fatal("Varying to uniform assignment\n");
		}
	} else {
		if (src->type & SLC_UNIFORM) {
			// Uniform to varying assignment
			const char	*opcode;
			CVariable	*cVar;
			int			allocated	=	FALSE;

			dest	=	sdr->lockRegister(src->type & (~SLC_UNIFORM));
			cVar	=	src->getVariable();
			if (cVar == NULL) {
				cVar		=	sdr->lockRegister(src->type);
				src->getCode(out,cVar);
				allocated	=	TRUE;
			}

			// Uniform to varying assignment
			if (src->type & SLC_FLOAT) {
				opcode	=	opcodeVUFloat;
			} else if (src->type & SLC_VECTOR) {
				opcode	=	opcodeVUVector;
			} else if (src->type & SLC_MATRIX) {
				opcode	=	opcodeVUMatrix;
			} else if (src->type & SLC_STRING) {
				opcode	=	opcodeVUString;
			} else {
				assert(FALSE);
			}

			fprintf(out,"%s %s %s\n",opcode,dest->codeName(),cVar->codeName());

			if (allocated) {
				sdr->releaseRegister(cVar);
			}
		} else {
			dest	=	src->getVariable();
			if (dest == NULL) {
				sdr->lockRegister(src->type);
				src->getCode(out,dest);
			}
		}
	}

	return dest;
}




// Lock a value into a character
#define	lock(IIIdest,IIIexpression)	{																						\
														char		*IIIdest		=	NULL;								\
														CVariable	*IIIdest##Var	=	NULL;								\
														if (IIIexpression != NULL) {										\
															IIIdest##Var				=	IIIexpression->getVariable();	\
															if (IIIdest##Var == NULL) {										\
																getContainer(out,type,IIIdest##Var,IIIexpression);			\
																IIIdest					=	IIIdest##Var->codeName();		\
															} else {														\
																if ((IIIdest##Var->type & SLC_UNIFORM) ^ (type & SLC_UNIFORM)) {\
																	getContainer(out,type,IIIdest##Var,IIIexpression);		\
																	IIIdest			=	IIIdest##Var->codeName();			\
																} else {													\
																	IIIdest			=	IIIdest##Var->codeName();			\
																	IIIdest##Var	=	NULL;								\
																}															\
															}																\
														}


#define	release(IIIdest)								if (IIIdest##Var != NULL)	sdr->releaseRegister(IIIdest##Var);	}


// FIXME:	foolproof error checking

///////////////////////////////////////////////////////////////////////
// Class				:	CExpression
// Method				:	CExpression
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CExpression::CExpression(int t)	{	
	type	=	t;

}

///////////////////////////////////////////////////////////////////////
// Class				:	CExpression
// Method				:	~CExpression
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CExpression::~CExpression()	{	
}

///////////////////////////////////////////////////////////////////////
// Class				:	CExpression
// Method				:	getCode
// Description			:	Generate code that stores the result in "dest"
// Return Value			:	-
// Comments				:
void		CExpression::getCode(FILE *out,CVariable *dest)	{	
}


///////////////////////////////////////////////////////////////////////
// Class				:	CExpression
// Method				:	getVariable
// Description			:	If this is a variable, return the variable
// Return Value			:	-
// Comments				:
CVariable	*CExpression::getVariable()	{	
	return	NULL;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CExpression
// Method				:	value
// Description			:	This is another form of the get variable
// Return Value			:	-
// Comments				:
int			CExpression::value(char *) {
	return	FALSE;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CNullExpression
// Method				:	CNullExpression
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CNullExpression::CNullExpression() : CExpression(SLC_NONE) {
}

















///////////////////////////////////////////////////////////////////////////////////////////////////////////




























///////////////////////////////////////////////////////////////////////////////////////////////////////////







///////////////////////////////////////////////////////////////////////
// Class				:	CTwoExpressions
// Method				:	CTwoExpressions
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CTwoExpressions::CTwoExpressions(CExpression *f,CExpression *s) : CExpression(SLC_NONE) {
	first	=	f;
	second	=	s;
	
	// work out if the expression pair is varying
	if ((f->type & SLC_UNIFORM) && (s->type & SLC_UNIFORM)) {
		type |= SLC_UNIFORM;
	}
}



///////////////////////////////////////////////////////////////////////
// Class				:	CTwoExpressions
// Method				:	~CTwoExpressions
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CTwoExpressions::~CTwoExpressions() {
	delete first;
	delete second;
}




///////////////////////////////////////////////////////////////////////
// Class				:	CTwoExpressions
// Method				:	getCode
// Description			:	If this is a variable, return the variable
// Return Value			:	-
// Comments				:
void		CTwoExpressions::getCode(FILE *out,CVariable *dest) {
	if (dest != NULL) {
		sdr->error("Can not assign to a variable\n");
		return;
	}


	first->getCode(out,NULL);
	second->getCode(out,NULL);
}





///////////////////////////////////////////////////////////////////////////////////////////////////////////

















///////////////////////////////////////////////////////////////////////
// Class				:	CVectorExpression
// Method				:	CVectorExpression
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CVectorExpression::CVectorExpression(CExpression *x,CExpression *y,CExpression *z) : CExpression(SLC_VECTOR | (x->type & y->type & z->type & SLC_UNIFORM)) {
	this->x	=	getConversion(SLC_FLOAT,x);
	this->y	=	getConversion(SLC_FLOAT,y);
	this->z	=	getConversion(SLC_FLOAT,z);
}



///////////////////////////////////////////////////////////////////////
// Class				:	CVectorExpression
// Method				:	~CVextorExpression
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CVectorExpression::~CVectorExpression() {
	if (x != NULL)	delete x;
	if (y != NULL)	delete y;
	if (z != NULL)	delete z;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CVectorExpression
// Method				:	getCode
// Description			:	(see CExpression)
// Return Value			:	-
// Comments				:
void		CVectorExpression::getCode(FILE *out,CVariable *dest) {
	if (dest == NULL) {
		sdr->warning("Useless vector expression\n");
		return;
	}

	assert(	((dest->type & SLC_UNIFORM) ^ (type & SLC_UNIFORM))	== 0);

	assert(x->type & SLC_FLOAT);
	assert(y->type & SLC_FLOAT);
	assert(z->type & SLC_FLOAT);

	lock(op1,x);
	lock(op2,y);
	lock(op3,z);

	fprintf(out,"%s\t%s %s %s %s\n",opcodeVectorFromFloat,dest->codeName(),op1,op2,op3);

	release(op3);
	release(op2);
	release(op1);
}



///////////////////////////////////////////////////////////////////////
// Class				:	CVectorExpression
// Method				:	value
// Description			:	(see CExpression)
// Return Value			:	-
// Comments				:
int			CVectorExpression::value(char *dest) {
	char	tmp1[128];
	char	tmp2[128];
	char	tmp3[128];

	if (x->value(tmp1) & y->value(tmp2) & z->value(tmp3)) {
		sprintf(dest," [ %s %s %s ]",tmp1,tmp2,tmp3);

		return TRUE;
	}

	return FALSE;
}







///////////////////////////////////////////////////////////////////////////////////////////////////////////












///////////////////////////////////////////////////////////////////////
// Class				:	CMatrixExpression
// Method				:	CMatrixExpression
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CMatrixExpression::CMatrixExpression(CExpression **e) : CExpression(SLC_MATRIX) {
	int	i;
	int	f	=	SLC_UNIFORM;

	for (i=0;i<16;i++) {
		this->elements[i]	=	getConversion(SLC_FLOAT,e[i]);
		f	&=	this->elements[i]->type & SLC_UNIFORM;
	}

	type	|=	f;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CMatrixExpression
// Method				:	~CMatrixExpression
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CMatrixExpression::~CMatrixExpression() {
	int	i;

	for (i=0;i<16;i++) {
		if (elements[i] != NULL)
			delete elements[i];
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CMatrixExpression
// Method				:	getCode
// Description			:	(see CExpression)
// Return Value			:	-
// Comments				:
void		CMatrixExpression::getCode(FILE *out,CVariable *dest) {
	if (dest == NULL) {
		sdr->warning("Useless matrix expression\n");
		return;
	}

	assert(	((dest->type & SLC_UNIFORM) ^ (type & SLC_UNIFORM))	== 0);

	lock(op0,	elements[0]);	assert(elements[0]->type & SLC_FLOAT);
	lock(op1,	elements[1]);	assert(elements[1]->type & SLC_FLOAT);
	lock(op2,	elements[2]);	assert(elements[2]->type & SLC_FLOAT);
	lock(op3,	elements[3]);	assert(elements[3]->type & SLC_FLOAT);
	lock(op4,	elements[4]);	assert(elements[4]->type & SLC_FLOAT);
	lock(op5,	elements[5]);	assert(elements[5]->type & SLC_FLOAT);
	lock(op6,	elements[6]);	assert(elements[6]->type & SLC_FLOAT);
	lock(op7,	elements[7]);	assert(elements[7]->type & SLC_FLOAT);
	lock(op8,	elements[8]);	assert(elements[8]->type & SLC_FLOAT);
	lock(op9,	elements[9]);	assert(elements[9]->type & SLC_FLOAT);
	lock(op10,	elements[10]);	assert(elements[10]->type & SLC_FLOAT);
	lock(op11,	elements[11]);	assert(elements[11]->type & SLC_FLOAT);
	lock(op12,	elements[12]);	assert(elements[12]->type & SLC_FLOAT);
	lock(op13,	elements[13]);	assert(elements[13]->type & SLC_FLOAT);
	lock(op14,	elements[14]);	assert(elements[14]->type & SLC_FLOAT);
	lock(op15,	elements[15]);	assert(elements[15]->type & SLC_FLOAT);


	fprintf(out,"%s\t%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s\n",
			opcodeMatrixFromFloat,
			dest->codeName(),
			op0,op1,op2,op3,
			op4,op5,op6,op7,
			op8,op9,op10,op11,
			op12,op13,op14,op15);

	release(op15);
	release(op14);
	release(op13);
	release(op12);
	release(op11);
	release(op10);
	release(op9);
	release(op8);
	release(op7);
	release(op6);
	release(op5);
	release(op4);
	release(op3);
	release(op2);
	release(op1);
	release(op0);

}





///////////////////////////////////////////////////////////////////////
// Class				:	CMatrixExpression
// Method				:	value
// Description			:	(see CExpression)
// Return Value			:	-
// Comments				:
int			CMatrixExpression::value(char *dest) {
	char	tmp[128];
	int		i;

	sprintf(dest,"[ ");
	for (i=0;i<16;i++) {
		if (elements[i]->value(tmp)) {
			strcat(dest,tmp);
			strcat(dest," ");
		} else {
			return FALSE;
		}
	}
	strcat(dest," ]");

	return TRUE;
}






///////////////////////////////////////////////////////////////////////////////////////////////////////////












///////////////////////////////////////////////////////////////////////
// Class				:	CArrayExpression
// Method				:	CArrayExpression
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CArrayExpression::CArrayExpression(CVariable *v,CExpression *i) : CExpression((v->type & (SLC_TYPE_MASK | SLC_SUB_TYPE_MASK)) | (v->type & i->type & SLC_UNIFORM)) {
	array	=	v;
	item	=	getConversion(SLC_FLOAT | (type & SLC_UNIFORM),i);
	
	if (v->type & SLC_ARRAY) {
	} else {
		sdr->fatal("%s needs to be array\n",v->symbolName);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CArrayExpression
// Method				:	~CArrayExpression
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CArrayExpression::~CArrayExpression() {
	delete item;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CArrayExpression
// Method				:	getCode
// Description			:	Code generation
// Return Value			:	-
// Comments				:
void		CArrayExpression::getCode(FILE *out,CVariable *dest) {
	const char	*opcode;

	if (dest == NULL) {
		// We have to be assigned to something
		sdr->warning("Useles array expression\n");
		return;
	}

	assert(	((dest->type & SLC_UNIFORM) ^ (type & SLC_UNIFORM))	== 0);

	lock(op1,item);	
	assert(item->type & SLC_FLOAT);

	if ((array->type & SLC_UNIFORM) ^ (type & SLC_UNIFORM)) {
		if		(array->type & SLC_FLOAT)	opcode	=	opcodeUFFromArray;
		else if (array->type & SLC_VECTOR)	opcode	=	opcodeUVFromArray;
		else if (array->type & SLC_MATRIX)	opcode	=	opcodeUMFromArray;
		else if (array->type & SLC_STRING)	opcode	=	opcodeUSFromArray;
		else {
			assert(FALSE);
		}
	} else {
		if		(array->type & SLC_FLOAT)	opcode	=	opcodeFFromArray;
		else if (array->type & SLC_VECTOR)	opcode	=	opcodeVFromArray;
		else if (array->type & SLC_MATRIX)	opcode	=	opcodeMFromArray;
		else if (array->type & SLC_STRING)	opcode	=	opcodeSFromArray;
		else {
			assert(FALSE);
		}
	}


	fprintf(out,"%s\t%s %s %s\n",opcode,dest->codeName(),array->codeName(),op1);
	
	release(op1);
}






///////////////////////////////////////////////////////////////////////////////////////////////////////////












///////////////////////////////////////////////////////////////////////
// Class				:	CTerminalExpression
// Method				:	CTerminalExpression
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CTerminalExpression::CTerminalExpression(CVariable *v) : CExpression(v->type & (SLC_TYPE_MASK | SLC_SUB_TYPE_MASK | SLC_UNIFORM))	{	
	variable	=	v;
}



///////////////////////////////////////////////////////////////////////
// Class				:	CTerminalExpression
// Method				:	~CTerminalExpression
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CTerminalExpression::~CTerminalExpression()	{	
}

///////////////////////////////////////////////////////////////////////
// Class				:	CTerminalExpression
// Method				:	getCode
// Description			:	(see CExpression)
// Return Value			:	-
// Comments				:
void		CTerminalExpression::getCode(FILE *out,CVariable *dest) {
	const char	*opcode;

	if (dest == NULL) {
		sdr->warning("Useless assignment\n");
		return;
	}

	assert(	((dest->type & SLC_UNIFORM) ^ (type & SLC_UNIFORM))	== 0);

	if		(type & SLC_FLOAT)	opcode	=	opcodeMoveFloatFloat;
	else if (type & SLC_VECTOR)	opcode	=	opcodeMoveVectorVector;
	else if (type & SLC_MATRIX)	opcode	=	opcodeMoveMatrixMatrix;
	else if (type & SLC_STRING)	opcode	=	opcodeMoveStringString;
	else {
		assert(FALSE);
	}

	fprintf(out,"%s\t%s %s\n",opcode,dest->codeName(),variable->codeName());
}







///////////////////////////////////////////////////////////////////////////////////////////////////////////











///////////////////////////////////////////////////////////////////////
// Class				:	CConstantTerminalExpression
// Method				:	CConstantTerminalExpression
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CConstantTerminalExpression::CConstantTerminalExpression(int t,char *c)	: CExpression(t | SLC_UNIFORM) {	
	constant		=	c;
	dummy			=	new CVariable(c,t | SLC_UNIFORM,1);
	dummy->cName	=	strdup(constant);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CConstantTerminalExpression
// Method				:	~CConstantTerminalExpression
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CConstantTerminalExpression::~CConstantTerminalExpression()	{	
	free(constant);	
	delete dummy;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CConstantTerminalExpression
// Method				:	getCode
// Description			:	(see CExpression)
// Return Value			:	-
// Comments				:
void		CConstantTerminalExpression::getCode(FILE *out,CVariable *dest) {
	const char	*opcode;

	if (dest == NULL) {
		sdr->warning("Useless constant expression\n");
		return;
	}

	assert(	((dest->type & SLC_UNIFORM) ^ (type & SLC_UNIFORM))	== 0);

	if		(type & SLC_FLOAT)	opcode	=	opcodeMoveFloatFloat;
	else if (type & SLC_VECTOR)	opcode	=	opcodeMoveVectorVector;
	else if (type & SLC_MATRIX)	opcode	=	opcodeMoveMatrixMatrix;
	else if (type & SLC_STRING)	opcode	=	opcodeMoveStringString;
	else {
		assert(FALSE);
	}

	fprintf(out,"%s\t%s %s\n",opcode,dest->codeName(),constant);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CConstantTerminalExpression
// Method				:	value
// Description			:	(see CExpression)
// Return Value			:	-
// Comments				:
int			CConstantTerminalExpression::value(char *dest) {
	strcpy(dest,constant);
	return TRUE;
}















///////////////////////////////////////////////////////////////////////////////////////////////////////////














///////////////////////////////////////////////////////////////////////
// Class				:	CBinaryExpression
// Method				:	CBinaryExpression
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CBinaryExpression::CBinaryExpression(int t,const char *o,CExpression *f,CExpression *s) : CExpression(t | (f->type & s->type & SLC_UNIFORM))	{ 
	first	=	f;
	second	=	s;
	opcode	=	o;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CBinaryExpression
// Method				:	~CBinaryExpression
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CBinaryExpression::~CBinaryExpression() {
	if (first	!= NULL)	delete first;
	if (second	!= NULL)	delete second;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CBinaryExpression
// Method				:	getVariable
// Description			:	(see CExpression)
// Return Value			:	-
// Comments				:
void	CBinaryExpression::getCode(FILE *out,CVariable *dest) {

	if (dest == NULL) {
		sdr->warning("Useless binary expression\n");
		return;
	}

	assert(	((dest->type & SLC_UNIFORM) ^ (type & SLC_UNIFORM))	== 0);

	lock(op1,first);
	lock(op2,second);

	fprintf(out,"%s\t%s %s %s\n",opcode,dest->codeName(),op1,op2);

	release(op2);
	release(op1);
}















///////////////////////////////////////////////////////////////////////////////////////////////////////////












///////////////////////////////////////////////////////////////////////
// Class				:	CUnaryExpression
// Method				:	CUnaryExpression
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CUnaryExpression::CUnaryExpression(int t,const char *o,CExpression *f) : CExpression(t | (f->type & SLC_UNIFORM) ) { 
	first	= f; 
	opcode	= o; 
}


///////////////////////////////////////////////////////////////////////
// Class				:	CUnaryExpression
// Method				:	~CUnaryExpression
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CUnaryExpression::~CUnaryExpression() {
	if (first != NULL)	delete first;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CUnaryExpression
// Method				:	getCode
// Description			:	(see CExpression)
// Return Value			:	-
// Comments				:
void	CUnaryExpression::getCode(FILE *out,CVariable *dest) {
	if (dest == NULL) {
		sdr->warning("Useless unary expression\n");
		return;
	}

	assert(	((dest->type & SLC_UNIFORM) ^ (type & SLC_UNIFORM))	== 0);

	lock(op1,first);

	fprintf(out,"%s\t%s %s\n",opcode,dest->codeName(),op1);

	release(op1);
}
















///////////////////////////////////////////////////////////////////////////////////////////////////////////













///////////////////////////////////////////////////////////////////////
// Class				:	CSysConversionExpression
// Method				:	CSysConversionExpression
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CSysConversionExpression::CSysConversionExpression(int t,const char *opcode,const char *system,CExpression *ft) : CExpression(t | (ft->type & SLC_UNIFORM) ) {
	this->opcode	=	opcode;
	this->system	=	strdup(system);
	this->first		=	ft;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSysConversionExpression
// Method				:	~CSysConversionExpression
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CSysConversionExpression::~CSysConversionExpression() {
	if (first != NULL)	delete first;
	free(system);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSysConversionExpression
// Method				:	getCode
// Description			:	(see CExpression)
// Return Value			:	-
// Comments				:
void		CSysConversionExpression::getCode(FILE *out,CVariable *dest) {
	if (dest == NULL) {
		sdr->warning("Useless system conversion\n");
		return;
	}

	assert(	((dest->type & SLC_UNIFORM) ^ (type & SLC_UNIFORM))	== 0);

	lock(op1,first);

	fprintf(out,"%s\t%s %s %s\n",opcode,dest->codeName(),system,op1);

	release(op1);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CSysConversionExpression
// Method				:	value
// Description			:	(see CExpression)
// Return Value			:	-
// Comments				:
int			CSysConversionExpression::value(char *dest) {
	char	tmp[128];

	if (first->value(tmp)) {
		sprintf(dest,"%s %s",system,tmp);
		return TRUE;
	}

	return FALSE;
}















///////////////////////////////////////////////////////////////////////////////////////////////////////////














///////////////////////////////////////////////////////////////////////
// Class				:	CFuncallExpression
// Method				:	CFuncallExpression
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CFuncallExpression::CFuncallExpression(CFunction *f,CList<CExpression *> *p) : CExpression(SLC_NONE) {
	if (f->returnValue != NULL)	type	=	f->returnValue->type;
	function	=	f;
	error		=	FALSE;
	
	// take the container from subexpressions
	if (function->code)
		type		|=	function->code->type & SLC_UNIFORM;
	
	// handle the parameters
	if (p == NULL) {
		// No arguments
		arguments	=	NULL;

		if (function->parameters->numItems != 0) {
			sdr->error("Argument count mismatch for %s\n",function->symbolName);
			error	=	TRUE;
		}
	} else {
		// Make sure the parameters match
		CExpression				*argument;
		CParameter				*parameter;
		CList<CExpression *>	*newArguments	=	new CList<CExpression *>;

		if (p->numItems != function->parameters->numItems) {
			sdr->fatal("Argument count mismatch for %s\n",function->symbolName);
			error	=	TRUE;
		} else {
			for (argument=p->first(),parameter=function->parameters->first();(argument!=NULL) && (parameter!=NULL);argument=p->next(),parameter=function->parameters->next()) {
				newArguments->push(getConversion(parameter->type & SLC_TYPE_MASK,argument));
				if (!(argument->type & SLC_UNIFORM)) {
					type	&=	~SLC_UNIFORM;
				}	
			}
		}

		delete p;
		arguments				=	newArguments;
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFuncallExpression
// Method				:	~CFuncallExpression
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CFuncallExpression::~CFuncallExpression() {
	CExpression	*cExpression;

	if (arguments != NULL) {
		while((cExpression = arguments->pop()) != NULL)	delete cExpression;
		delete arguments;
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFuncallExpression
// Method				:	getCode
// Description			:	(see CExpression)
// Return Value			:	-
// Comments				:
void		CFuncallExpression::getCode(FILE *out,CVariable *dest) {
	CVariable		**c	=	NULL;
	int				i,j;
	CExpression		*cParameter;
	CParameter		*cP;
	CVariable		*cVariable;
	CVariable		*temp	=	NULL;

	if (error == TRUE)	return;

	// Check the return value
	if (dest == NULL) {
		if (function->returnValue != NULL) {
			temp	=	sdr->lockRegister(type);
			dest	=	temp;
		}
	} else {
		if (function->returnValue == NULL) {
			sdr->error("Function %s does not have a return value\n",function->name);
			return;
		}

		assert(	((dest->type & SLC_UNIFORM) ^ (type & SLC_UNIFORM))	== 0);
	}

	// Set the return value to dest
	if (function->returnValue != NULL)
		function->returnValue->mapping	=	dest;


	// Figure out which variables the extern variables refer to
	for (cVariable=function->variables->first();cVariable!=NULL;cVariable=function->variables->next()) {
		if (cVariable->type & SLC_EXTERN) {
			CFunction	*lFunction;

			for (lFunction=sdr->runtimeFunctionStack->last();lFunction!=NULL;lFunction=sdr->runtimeFunctionStack->prev()) {
				CVariable	*tVariable	=	lFunction->getVariable(cVariable->symbolName,TRUE);

				if (tVariable != NULL) {
					if (cVariable->cName != NULL)	free(cVariable->cName);
					cVariable->cName		=	strdup(tVariable->codeName());
					break;
				}
			}

			if (lFunction == NULL) {
				sdr->error("Extern variable \"%s\" is not found\n",cVariable->symbolName);
			}
		} else {
			sdr->addVariable(cVariable);
		}
	}

	// Save the current function on the stack
	sdr->runtimeFunctionStack->push(function);

	i	=	0;
	if (arguments != NULL) {
		c	=	new CVariable*[arguments->numItems];

		// Go over the parameters and convert them as necessary
		for (cP = function->parameters->first(),cParameter = arguments->first();cParameter != NULL;cParameter = arguments->next(),cP = function->parameters->next()) {
			CVariable	*cVar	=	cParameter->getVariable();

			if (cVar == NULL) {
				getContainer(out,cP->type,cVar,cParameter);
				c[i++]	=	cVar;
			} else if ((cVar->type & SLC_UNIFORM) ^ (cP->type & SLC_UNIFORM)) {
				getContainer(out,cP->type,cVar,cParameter);
				c[i++]	=	cVar;
			}

			assert(cVar != NULL);
			cP->mapping	=	cVar;
		}
	} else	{
		c	=	NULL;
	}

	// Go over the init code 
	if (function->initExpression != NULL) function->initExpression->getCode(out,NULL);

	// Go over the code 
	if (function->code != NULL) function->code->getCode(out,NULL);

	// Release the locked registers
	for (j=0;j<i;j++) {
		if (c[j]->type & SLC_LOCKED) {
			sdr->releaseRegister(c[j]);
		}
	}

	if (c != NULL)	delete [] c;

	if (temp != NULL)
		sdr->releaseRegister(temp);

	// Restore the runtime function stack
	sdr->runtimeFunctionStack->pop();
}

















///////////////////////////////////////////////////////////////////////////////////////////////////////////













///////////////////////////////////////////////////////////////////////
// Class				:	CBuiltinExpression
// Method				:	CBuiltinExpression
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CBuiltinExpression::CBuiltinExpression(CFunctionPrototype *f,CList<CExpression *> *p) : CExpression(f->functionType) {
	int			fa	=	SLC_UNIFORM;
	int			i;
	CExpression	*cEx;

	replacementPrototype	=	NULL;

	if (f->nonuniform == TRUE) {
		fa	=	0;
	} else {
		for (cEx = p->first();cEx != NULL;cEx = p->next()) {
			fa	&=	cEx->type & SLC_UNIFORM;
		}
	}

	if (strcmp(f->symbolName,"texture") == 0) {
		arguments	=	NULL;

		if (strcmp(f->prototype,"c=SF!") == 0) {
			arguments	=	new CList<CExpression *>;
			arguments->push((*p)[0]);
			arguments->push((*p)[1]);
			arguments->push(new CTerminalExpression(sdr->getVariable("s")));
			arguments->push(new CTerminalExpression(sdr->getVariable("t")));
			for (i=2;i<p->numItems;i++) {
				arguments->push((*p)[i]);
			}

			replacementPrototype	=	"c=SFff!";
		} else if (strcmp(f->prototype,"f=SF!") == 0) {
			arguments	=	new CList<CExpression *>;
			arguments->push((*p)[0]);
			arguments->push((*p)[1]);
			arguments->push(new CTerminalExpression(sdr->getVariable("s")));
			arguments->push(new CTerminalExpression(sdr->getVariable("t")));
			for (i=2;i<p->numItems;i++) {
				arguments->push((*p)[i]);
			}

			replacementPrototype	=	"f=SFff!";
		} else if (strcmp(f->prototype,"f=SFfffffff!") == 0) {
			arguments	=	new CList<CExpression *>;
			arguments->push((*p)[0]);
			arguments->push(new CConstantTerminalExpression(SLC_FLOAT | SLC_UNIFORM,strdup("0")));
			arguments->push((*p)[1]);
			arguments->push((*p)[2]);
			arguments->push((*p)[3]);
			arguments->push((*p)[4]);
			arguments->push((*p)[5]);
			arguments->push((*p)[6]);
			arguments->push((*p)[7]);
			arguments->push((*p)[8]);
			for (i=9;i<p->numItems;i++) {
				arguments->push((*p)[i]);
			}

			replacementPrototype	=	"f=SFffffffff!";
		} else if (strcmp(f->prototype,"c=SFfffffff!") == 0) {
			arguments	=	new CList<CExpression *>;
			arguments->push((*p)[0]);
			arguments->push(new CConstantTerminalExpression(SLC_FLOAT | SLC_UNIFORM,strdup("0")));
			arguments->push((*p)[1]);
			arguments->push((*p)[2]);
			arguments->push((*p)[3]);
			arguments->push((*p)[4]);
			arguments->push((*p)[5]);
			arguments->push((*p)[6]);
			arguments->push((*p)[7]);
			arguments->push((*p)[8]);
			for (i=9;i<p->numItems;i++) {
				arguments->push((*p)[i]);
			}

			replacementPrototype	=	"c=SFffffffff!";
		} 

		if (arguments != NULL) {
			p	=	arguments;
		}

	} else if (strcmp(f->symbolName,"bump") == 0) {
		if (strcmp(f->prototype,"n=SFnvv!") == 0) {
			p->push(new CTerminalExpression(sdr->getVariable("s")));
			p->push(new CTerminalExpression(sdr->getVariable("t")));
			replacementPrototype	=	"n=SFvvff!";
		}
	}


	function	=	f;
	arguments	=	p;
	type		|=	fa;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CBuiltinExpression
// Method				:	~CBuiltinExpression
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CBuiltinExpression::~CBuiltinExpression() {
	CExpression	*cExpression;

	if (arguments != NULL) {
		while((cExpression = arguments->pop()) != NULL)	delete cExpression;
		delete arguments;
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CBuiltinExpression
// Method				:	getVariable
// Description			:	(see CExpression)
// Return Value			:	-
// Comments				:
static	char	getExpressionType(CExpression *e) {
	if		(e->type & SLC_FLOAT)	return	'f';
	else if (e->type & SLC_VECTOR) {
		if	(e->type & SLC_VVECTOR)	return 'v';
		if	(e->type & SLC_VNORMAL)	return 'n';
		if	(e->type & SLC_VPOINT)	return 'p';
		if	(e->type & SLC_VCOLOR)	return 'c';
		else	return 'v';
	} else if	(e->type & SLC_MATRIX)	return 'm';
	else if		(e->type & SLC_STRING)		return 's';
	else	return 'o';
}

void		CBuiltinExpression::getCode(FILE *out,CVariable *dest) {
	char		**op;
	CVariable	**c;
	int			nParameters;
	int			i;
	CExpression	*cParameter;
	CExpression	**expressions;
	int			cPrototype;
	char		usedPrototype[512];
	int			uPrototype;
	CVariable	*d;
	CVariable	*temp	=	NULL;
	const char	*fprototype;
	int			plStart	=	-1;

	if (replacementPrototype == NULL) {
		fprototype	=	function->prototype;
	} else {
		fprototype	=	replacementPrototype;
	}

	if (dest == NULL) {
		if (fprototype[0] == 'o') {
			d		=	NULL;
		} else {
			temp	=	sdr->lockRegister(type);
			d		=	temp;
		}
	} else {
		if (fprototype[0] == 'o') {
			sdr->error("Function %s does not return anything\n",function->symbolName);
			return;
		}

		d	=	dest;
	}

	nParameters	=	arguments->numItems;

	op			=	new char*[nParameters];
	c			=	new CVariable*[nParameters];
	expressions	=	new CExpression*[nParameters];


	uPrototype	=	2;
	cPrototype	=	2;

	usedPrototype[0]	=	fprototype[0];
	usedPrototype[1]	=	'=';

	bool	parameterList	=	false;
	for (i=0,cParameter = arguments->first();cParameter != NULL;) {
		if (fprototype[cPrototype]	==	'f')	{
			expressions[i]	=	getConversion(SLC_FLOAT,cParameter);
			usedPrototype[uPrototype++]	=	'f';
			cPrototype++;
			i++;
			cParameter = arguments->next();
		} else if (fprototype[cPrototype]	==	'v')	{
			expressions[i]	=	getConversion(SLC_VECTOR | SLC_VVECTOR,cParameter);
			usedPrototype[uPrototype++]	=	'v';
			cPrototype++;
			i++;
			cParameter = arguments->next();
		} else if (fprototype[cPrototype]	==	'n')	{
			expressions[i]	=	getConversion(SLC_VECTOR | SLC_VNORMAL,cParameter);
			usedPrototype[uPrototype++]	=	'n';
			cPrototype++;
			i++;
			cParameter = arguments->next();
		} else if (fprototype[cPrototype]	==	'p')	{
			expressions[i]	=	getConversion(SLC_VECTOR | SLC_VPOINT,cParameter);
			usedPrototype[uPrototype++]	=	'p';
			cPrototype++;
			i++;
			cParameter = arguments->next();
		} else if (fprototype[cPrototype]	==	'c')	{
			expressions[i]	=	getConversion(SLC_VECTOR | SLC_VCOLOR,cParameter);
			usedPrototype[uPrototype++]	=	'c';
			cPrototype++;
			i++;
			cParameter = arguments->next();
		} else if (fprototype[cPrototype]	==	'm')	{
			expressions[i]	=	getConversion(SLC_MATRIX,cParameter);
			usedPrototype[uPrototype++]	=	'm';
			cPrototype++;
			i++;
			cParameter = arguments->next();
		} else if (fprototype[cPrototype]	==	's')	{
			expressions[i]	=	getConversion(SLC_STRING,cParameter);
			usedPrototype[uPrototype++]	=	's';
			cPrototype++;
			i++;
			cParameter = arguments->next();
		} else if (fprototype[cPrototype]	==	'F')	{
			expressions[i]	=	getConversion(SLC_FLOAT,cParameter);
			if (expressions[i]->getVariable() == NULL)	sdr->warning("Identifier expected as return value\n");
			usedPrototype[uPrototype++]	=	'F';
			cPrototype++;
			i++;
			cParameter = arguments->next();
		} else if (fprototype[cPrototype]	==	'V')	{
			expressions[i]	=	getConversion(SLC_VECTOR | SLC_VVECTOR,cParameter);
			if (expressions[i]->getVariable() == NULL)	sdr->warning("Identifier expected as return value\n");
			usedPrototype[uPrototype++]	=	'V';
			cPrototype++;
			i++;
			cParameter = arguments->next();
		} else if (fprototype[cPrototype]	==	'N')	{
			expressions[i]	=	getConversion(SLC_VECTOR | SLC_VNORMAL,cParameter);
			if (expressions[i]->getVariable() == NULL)	sdr->warning("Identifier expected as return value\n");
			usedPrototype[uPrototype++]	=	'N';
			cPrototype++;
			i++;
			cParameter = arguments->next();
		} else if (fprototype[cPrototype]	==	'P')	{
			expressions[i]	=	getConversion(SLC_VECTOR | SLC_VPOINT,cParameter);
			if (expressions[i]->getVariable() == NULL)	sdr->warning("Identifier expected as return value\n");
			usedPrototype[uPrototype++]	=	'P';
			cPrototype++;
			i++;
			cParameter = arguments->next();
		} else if (fprototype[cPrototype]	==	'C')	{
			expressions[i]	=	getConversion(SLC_VECTOR | SLC_VCOLOR,cParameter);
			if (expressions[i]->getVariable() == NULL)	sdr->warning("Identifier expected as return value\n");
			usedPrototype[uPrototype++]	=	'C';
			cPrototype++;
			i++;
			cParameter = arguments->next();
		} else if (fprototype[cPrototype]	==	'M')	{
			expressions[i]	=	getConversion(SLC_MATRIX,cParameter);
			if (expressions[i]->getVariable() == NULL)	sdr->warning("Identifier expected as return value\n");
			usedPrototype[uPrototype++]	=	'M';
			cPrototype++;
			i++;
			cParameter = arguments->next();
		} else if (fprototype[cPrototype]	==	'S')	{
			expressions[i]	=	getConversion(SLC_STRING,cParameter);
			if (expressions[i]->getVariable() == NULL)	sdr->warning("Identifier expected as return value\n");
			usedPrototype[uPrototype++]	=	'S';
			cPrototype++;
			i++;
			cParameter = arguments->next();
		} else if ((fprototype[cPrototype]	==	'+') || (fprototype[cPrototype]	==	'*')) {
			cPrototype--;
		} else if (fprototype[cPrototype]	==	'.') {
			expressions[i]	=	cParameter;
			usedPrototype[uPrototype++]	=	getExpressionType(cParameter);
			cPrototype++;
			i++;
			cParameter = arguments->next();

			if (usedPrototype[uPrototype-1]	==	'o') {
				assert(FALSE);
			}
		} else if (fprototype[cPrototype]	==	'!') {
			if (plStart == -1)	plStart			=	i;

			if (parameterList == false) {
				parameterList	=	true;
				expressions[i]	=	getConversion(SLC_STRING,cParameter);
				usedPrototype[uPrototype++]	=	'S';
			} else {
				expressions[i]	=	cParameter;
				usedPrototype[uPrototype++]	=	getExpressionType(cParameter);
			}

			i++;
			cParameter = arguments->next();
		}
	}

	usedPrototype[uPrototype]	=	'\0';

	if (plStart == -1)	plStart	=	nParameters;

	for (i = 0;i < nParameters;i++) {
		int		dt	=	type;

		c[i]	=	expressions[i]->getVariable();
		op[i]	=	NULL;

		if ((i >= plStart) || ((usedPrototype[i+2] >= 'A') && (usedPrototype[i+2] <= 'Z'))) {
			dt	&=	~SLC_VARYING;
			dt	|=	SLC_UNIFORM;
		}

		if (c[i] == NULL) {
			getContainer(out,dt,c[i],expressions[i]);
			op[i]	=	c[i]->codeName();
		} else if ((c[i]->type & SLC_UNIFORM) ^ (dt & SLC_UNIFORM)) {
			getContainer(out,type,c[i],expressions[i]);
			op[i]	=	c[i]->codeName();
		} else {
			op[i]	=	c[i]->codeName();
			c[i]	=	NULL;
		}
	}

	if (function->dso == FALSE) {
		fprintf(out,"\t%s\t(\"%s\") ",function->symbolName,usedPrototype);
	} else {
		fprintf(out,"\tDSO %s\t(\"%s\") ",function->symbolName,usedPrototype);
	}

	if (d != NULL) {
		fprintf(out," %s ",d->codeName());
	}

	for (i = 0;i < nParameters;i++) {
		fprintf(out," %s ",op[i]);
	}

	fprintf(out,"\n");


	// Release the locked registers
	for (i=0;i<arguments->numItems;i++) {
		if (c[i] != NULL) {
			sdr->releaseRegister(c[i]);
		} else {
		}
	}

	if (d != dest) {
		sdr->releaseRegister(temp);
	}

	delete [] expressions;
	delete [] op;
	delete [] c;
}




























///////////////////////////////////////////////////////////////////////////////////////////////////////////



















///////////////////////////////////////////////////////////////////////
// Class				:	CConditionalExpression
// Method				:	CConditionalExpression
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CConditionalExpression::CConditionalExpression(int type,CExpression *condition,CExpression *first,CExpression *second) : CExpression(type) {
	this->condition			=	getConversion(SLC_FLOAT,condition);
	this->trueExpression	=	getConversion(type,first);
	this->falseExpression	=	getConversion(type,second);

	if (!(condition->type & SLC_UNIFORM))		this->type	&=	~SLC_UNIFORM;
	if (!(trueExpression->type & SLC_UNIFORM))	this->type	&=	~SLC_UNIFORM;
	if (!(falseExpression->type & SLC_UNIFORM))	this->type	&=	~SLC_UNIFORM;

}


///////////////////////////////////////////////////////////////////////
// Class				:	CConditionalExpression
// Method				:	~CConditionalExpression
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CConditionalExpression::~CConditionalExpression() {
	delete condition;
	delete trueExpression;
	delete falseExpression;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CConditionalExpression
// Method				:	getCode
// Description			:	(see expression)
// Return Value			:	-
// Comments				:
void		CConditionalExpression::getCode(FILE *out,CVariable *dest) {
	char	elseLabel[32];
	char	endLabel[32];

	sdr->newLabel(elseLabel);
	sdr->newLabel(endLabel);

	// Note condition variables must always be varying
	// so we use a HACK to force varying conditions (or else behaves badly, acting as ifever)
	int typeSave = type;	type &= ~SLC_UNIFORM;
	lock(cond,condition);
	type = typeSave;

	fprintf(out,"%s\t%s %s\n",opcodeIf,cond,elseLabel);

	release(cond);

	getContainer(out,dest,trueExpression);

	fprintf(out,"%s:\n",elseLabel);
	fprintf(out,"%s\t%s\n",opcodeElse,endLabel);

	getContainer(out,dest,falseExpression);
	
	fprintf(out,"%s:\n",endLabel);
	fprintf(out,"%s\n",opcodeEndif);
}







///////////////////////////////////////////////////////////////////////////////////////////////////////////












///////////////////////////////////////////////////////////////////////
// Class				:	CAssignmentExpression
// Method				:	CAssignmentExpression
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CAssignmentExpression::CAssignmentExpression(CVariable *f,CExpression *s) : CExpression(f->type) {
	if (f->type & SLC_RDONLY) {
		sdr->error("Can not assign to rdonly %s\n",f->symbolName);
	}

	if (f->type & SLC_UNIFORM) {
		if (!(s->type & SLC_UNIFORM)) {
			sdr->error("Can not assign varying to uniform %s\n",f->symbolName);
		}
	}

	first	=	f;
	second	=	s;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CAssignmentExpression
// Method				:	~CAssignmentExpression
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CAssignmentExpression::~CAssignmentExpression() {
	if (second != NULL)	delete second;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CAssignmentExpression
// Method				:	getCode
// Description			:	(see CExpression)
// Return Value			:	-
// Comments				:
void		CAssignmentExpression::getCode(FILE *out,CVariable *dest) {
	getContainer(out,first,second);

	if (dest != NULL) {
		CExpression	*t	=	new CTerminalExpression(first);

		getContainer(out,dest,t);

		delete t;
	}
}








///////////////////////////////////////////////////////////////////////////////////////////////////////////












///////////////////////////////////////////////////////////////////////
// Class				:	CArrayAssignmentExpression
// Method				:	CArrayAssignmentExpression
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CArrayAssignmentExpression::CArrayAssignmentExpression(CVariable *f,CExpression *i,CExpression *s) : CExpression(f->type) {
	if (f->type & SLC_RDONLY) {
		sdr->error("Can not assign to rdonly %s\n",f->symbolName);
	}

	if (f->type & SLC_UNIFORM) {
		if (!(s->type & SLC_UNIFORM)) {
			sdr->error("Can not assign varying to uniform %s\n",f->symbolName);
		}
	}
	
	first	=	f;
	index	=	getConversion(SLC_FLOAT | (type & SLC_UNIFORM),i);
	second	=	getConversion((first->type & SLC_TYPE_MASK) | (type & SLC_UNIFORM),s);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CAssignmentExpression
// Method				:	~CAssignmentExpression
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CArrayAssignmentExpression::~CArrayAssignmentExpression() {
	if (second != NULL)	delete second;
	if (index != NULL)	delete index;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CArrayAssignmentExpression
// Method				:	getCode
// Description			:	(see CExpression)
// Return Value			:	-
// Comments				:
void		CArrayAssignmentExpression::getCode(FILE *out,CVariable *dest) {
	const char	*opcode;
	const char	*opcodeN;

	lock(opi,index);	// Get float index
	lock(op,second);	// Get the second code
	
	if (first->type & SLC_FLOAT) {
		opcode	=	opcodeFToArray;
		opcodeN	=	opcodeMoveFloatFloat;
	} else if (first->type & SLC_VECTOR) {
		opcode	=	opcodeVToArray;
		opcodeN	=	opcodeMoveVectorVector;
	} else if (first->type & SLC_MATRIX) {
		opcode	=	opcodeMToArray;
		opcodeN	=	opcodeMoveMatrixMatrix;
	} else if (first->type & SLC_STRING) {
		opcode	=	opcodeSToArray;
		opcodeN	=	opcodeMoveStringString;
	} else {
		assert(FALSE);
	}

	fprintf(out,"%s\t%s %s %s\n",opcode,first->codeName(),opi,op);

	if (dest != NULL) {
		assert((dest->type & SLC_ARRAY) == 0);
		getConversion(out,dest,second);
	}

	release(op);
	release(opi);
}












///////////////////////////////////////////////////////////////////////////////////////////////////////////












///////////////////////////////////////////////////////////////////////
// Class				:	CArrayUpdateExpression
// Method				:	CArrayUpdateExpression
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CArrayUpdateExpression::CArrayUpdateExpression(CVariable *f,CExpression *i,CExpression *s,const char *opcodeFloat,const char *opcodeVector,const char *opcodeMatrix) : CExpression(f->type) {
	first = f;
	arrayAssigner = NULL;
	
	// Ensure index is float
	index = getConversion(SLC_FLOAT | (type & SLC_UNIFORM),i);

	// pre-reseve the register (needs 1 register for index for both load and store)
	indexVar = sdr->lockRegister(SLC_FLOAT | (type & SLC_UNIFORM));
	
	// Create Accessor
	if(CExpression *arrayAccessor = new CArrayExpression(first,new CTerminalExpression(indexVar))){
		// Create update expression
		if(CExpression	*second = getOperation(arrayAccessor,s,opcodeFloat,opcodeVector,opcodeMatrix,NULL,0)){
			// Create expression to store it again
			arrayAssigner = new CArrayAssignmentExpression(first,new CTerminalExpression(indexVar),second);
		}
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CAssignmentExpression
// Method				:	~CAssignmentExpression
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CArrayUpdateExpression::~CArrayUpdateExpression() {
	if (index != NULL)			delete index;
	if (arrayAssigner != NULL)	delete arrayAssigner;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CArrayAssignmentExpression
// Method				:	getCode
// Description			:	(see CExpression)
// Return Value			:	-
// Comments				:
void		CArrayUpdateExpression::getCode(FILE *out,CVariable *dest) {
	// generate the u->v conversion if needed of index
	getContainer(out,indexVar,index);
	// previous getContainer() unlocks indexVar, relock it
	indexVar->type |= SLC_LOCKED;
	// generate the load, arithmetic and final store
	arrayAssigner->getCode(out,dest);
	// release indexVar
	sdr->releaseRegister(indexVar);
}












///////////////////////////////////////////////////////////////////////////////////////////////////////////




















///////////////////////////////////////////////////////////////////////
// Class				:	CArrayMove
// Method				:	CArrayMove
// Description			:	Ctor
// Return Value			:	-
// Comments				:	Note that e array holds the last item first
CArrayMove::CArrayMove(CVariable *f,CList<CExpression *> *e) : CExpression(f->type & (~SLC_ARRAY)) {
	CExpression	*cExpression;
	int			numItems	=	0;

	first	=	f;
	items	=	new CList<CExpression *>;

	while((cExpression=e->pop()) != NULL) {

		items->push(getConversion(f->type & (SLC_TYPE_MASK | SLC_UNIFORM),cExpression));

		numItems++;
	}

	if (f->type & SLC_ARRAY) {
		if (f->numItems == numItems) {
		} else {
			sdr->error("Number of items mismatch for %s\n",f->symbolName);
		}
	} else {
		sdr->error("Array expected in assignment to %s\n",f->symbolName);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CArrayMove
// Method				:	~CArrayMove
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CArrayMove::~CArrayMove() {
	CExpression	*cExpression;

	while((cExpression=items->pop()) != NULL) {
		delete cExpression;
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CArrayMove
// Method				:	CArrayMove
// Description			:	Ctor
// Return Value			:	-
// Comments				:
void		CArrayMove::getCode(FILE *out,CVariable *dest) {
	int			i;
	CExpression	*cExpression;
	char		tmp[32];
	const char	*opcode;

	if (dest != NULL) {
		sdr->error("Nested array assignments are not supported yet\n");
		return;
	}

	if (first->type & SLC_FLOAT) {
		opcode	=	opcodeFToArray;
	} else if (first->type & SLC_VECTOR) {
		opcode	=	opcodeVToArray;
	} else if (first->type & SLC_MATRIX) {
		opcode	=	opcodeMToArray;
	} else if (first->type & SLC_STRING) {
		opcode	=	opcodeSToArray;
	} else {
		assert(FALSE);
	}


	for (i=0,cExpression=items->first();cExpression!=NULL;cExpression=items->next(),i++) {
		CVariable	*cVariable	=	getContainer(out,first->type & (SLC_TYPE_MASK | SLC_UNIFORM),cExpression);

		sprintf(tmp,"%d",i);

		CExpression	*iVariable	=	new CConstantTerminalExpression(SLC_UNIFORM | SLC_FLOAT,tmp);

		lock(iname,iVariable);

		fprintf(out,"%s %s %s %s\n",opcode,first->codeName(),iname,cVariable->codeName());

		release(iname);

		if (cVariable->type & SLC_LOCKED) {
			sdr->releaseRegister(cVariable);
		}
	}
}













///////////////////////////////////////////////////////////////////////////////////////////////////////////












///////////////////////////////////////////////////////////////////////
// Class				:	CUpdateExpression
// Method				:	CUpdateExpression
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CUpdateExpression::CUpdateExpression(CVariable *f,const char *opcodeFloat,const char *opcodeVector,int pre,CExpression *s) : CExpression(f->type) {
	first	=	f;
	second	=	getConversion(f->type & SLC_TYPE_MASK,s);

	if (f->type & SLC_RDONLY) {
		sdr->error("Can not assign to rdonly %s\n",f->symbolName);
	}

	if (f->type & SLC_UNIFORM) {
		if (!(s->type & SLC_UNIFORM)) {
			sdr->error("Can not assign varying to uniform %s\n",f->symbolName);
		}
	}

	this->opcodeFloat		=	opcodeFloat;
	this->opcodeVector		=	opcodeVector;
	this->pre				=	pre;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CUpdateExpression
// Method				:	~CUpdateExpression
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CUpdateExpression::~CUpdateExpression() {
	if (second != NULL)	delete second;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CUpdateExpression
// Method				:	getCode
// Description			:	(see CExpression)
// Return Value			:	-
// Comments				:
void		CUpdateExpression::getCode(FILE *out,CVariable *dest) {
	const char	*opcode,*opcodeM;

	lock(op,second);

	if (first->type & SLC_FLOAT) {
		opcode	=	opcodeFloat;
		opcodeM	=	opcodeMoveFloatFloat;
	} else if (first->type & SLC_VECTOR) {
		opcode	=	opcodeVector;
		opcodeM	=	opcodeMoveVectorVector;
	} else if (first->type & SLC_MATRIX) {
		sdr->error("Bad matrix operator\n");
		opcode	=	"";
		opcodeM	=	"";
	} else if (first->type & SLC_STRING) {
		sdr->error("Bad string operator");
		opcode	=	"";
		opcodeM	=	"";
	} else {
		assert(FALSE);
	}


	if (pre) {
		fprintf(out,"%s\t%s %s %s\n",opcode,first->codeName(),first->codeName(),op);

		if (dest != NULL) {
			assert((dest->type & SLC_ARRAY) == 0);
			fprintf(out,"%s\t%s %s\n",opcodeM,dest->codeName(),first->codeName());
		}
	} else {
		fprintf(out,"%s\t%s %s %s\n",opcode,first->codeName(),first->codeName(),op);

		if (dest != NULL) {
			assert((dest->type & SLC_ARRAY) == 0);
			fprintf(out,"%s\t%s %s\n",opcodeM,dest->codeName(),op);
		}
	}


	release(op);
}













///////////////////////////////////////////////////////////////////////////////////////////////////////////











///////////////////////////////////////////////////////////////////////
// Class				:	CIfThenElse
// Method				:	CIfThenElse
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CIfThenElse::CIfThenElse(CExpression *c,CExpression *f,CExpression *s) : CExpression(SLC_NONE) {
	cond	=	getConversion(SLC_FLOAT,c);
	first	=	f;
	second	=	s;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CIfThenElse
// Method				:	~CIfThenElse
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CIfThenElse::~CIfThenElse() {
	delete cond;
	delete first;
	if (second != NULL)	delete second;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CIfThenElse
// Method				:	getCode
// Description			:	-
// Return Value			:	-
// Comments				:
void		CIfThenElse::getCode(FILE *out,CVariable *dest) {
	char		elseLabel[32];
	char		endLabel[32];

	if (dest != NULL) {
		sdr->error("Conditional assignment to a variable\n");
		return;
	}

	// Allocate end label
	sdr->newLabel(endLabel);
	sdr->newLabel(elseLabel);

	lock(condition,cond);

	fprintf(out,"%s\t%s ",opcodeIf,condition);
	if (second != NULL)	{	fprintf(out,"%s\n",elseLabel);	}
	else				{	fprintf(out,"%s\n",endLabel);	}


	first->getCode(out,NULL);

	if (second != NULL) {
		fprintf(out,"%s:\n",elseLabel);
		fprintf(out,"%s\t%s\n",opcodeElse,endLabel);

		second->getCode(out,NULL);
	}

	fprintf(out,"%s:\n",endLabel);
	fprintf(out,"%s\n",opcodeEndif);

	release(condition);
}



















///////////////////////////////////////////////////////////////////////////////////////////////////////////











///////////////////////////////////////////////////////////////////////
// Class				:	CGatherThenElse
// Method				:	CGatherThenElse
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CGatherThenElse::CGatherThenElse(CList<CExpression *> *pl,CExpression *f,CExpression *s) : CExpression(0) {
	parameterList	=	pl;
	first			=	f;
	second			=	s;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CGatherThenElse
// Method				:	~CGatherThenElse
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CGatherThenElse::~CGatherThenElse() {
	delete first;
	if (second)	delete second;
	parameterList->destroy();
}


///////////////////////////////////////////////////////////////////////
// Class				:	CGatherThenElse
// Method				:	getCode
// Description			:	-
// Return Value			:	-
// Comments				:
void		CGatherThenElse::getCode(FILE *out,CVariable *dest) {
	char		beginLabel[32];
	char		elseLabel[32];
	char		endLabel[32];
	CExpression	**parameters;
	int			numParameters;
	char		str[256];
	char		*cstr = str;
	int			i;
	CVariable	**vars;
	char		**varNames;

	if (dest != NULL) {
		sdr->error("Gather assignment to a variable\n");
		return;
	}

	// Get the parameters
	parameters		=	parameterList->array;
	numParameters	=	parameterList->numItems;

	vars			=	new CVariable*[numParameters];
	varNames		=	new char*[numParameters];

	lock(category,		getConversion(SLC_STRING,parameters[0]));
	lock(P,				getConversion(SLC_VECTOR | SLC_VPOINT,parameters[1]));
	lock(N,				getConversion(SLC_VECTOR | SLC_VECTOR,parameters[2]));
	lock(sampleCone,	getConversion(SLC_FLOAT,parameters[3]));
	lock(samples,		getConversion(SLC_FLOAT,parameters[4]));

	*cstr++	=	's';
	*cstr++	=	'p';
	*cstr++	=	'n';
	*cstr++	=	'f';
	*cstr++	=	'f';

	for (i=5;i<numParameters;i+=2) {
		parameters[i]	=	getConversion(SLC_STRING | SLC_UNIFORM,parameters[i]);
		vars[i]			=	parameters[i]->getVariable();
		if (vars[i] == NULL) {
			varNames[i]	=	new char[32];
			if (parameters[i]->value(varNames[i]) == FALSE) {
				sdr->error("Gather was expecting a variable in the parameter list\n");
			}
			return;
		}
		*cstr++			=	's';

		parameters[i+1]	=	parameters[i+1];
		vars[i+1]		=	parameters[i+1]->getVariable();
		if (vars[i+1] == NULL) {
			varNames[i+1]	=	new char[32];
			if (parameters[i+1]->value(varNames[i+1]) == FALSE) {
				sdr->error("Gather was expecting a variable in the parameter list\n");
			}
			return;
		}
		if (parameters[i+1]->type & SLC_FLOAT) {
			*cstr++			=	'f';
		} else if (parameters[i+1]->type & SLC_VECTOR) {
			if (parameters[i+1]->type & SLC_VVECTOR) {
				*cstr++			=	'v';
			} else if (parameters[i+1]->type & SLC_VNORMAL) {
				*cstr++			=	'n';
			} else if (parameters[i+1]->type & SLC_VPOINT) {
				*cstr++			=	'p';
			} else if (parameters[i+1]->type & SLC_VCOLOR) {
				*cstr++			=	'c';
			} else {
				*cstr++			=	'v';
			}
		} else if (parameters[i+1]->type & SLC_MATRIX) {
			*cstr++			=	'm';
		} else if (parameters[i+1]->type & SLC_STRING) {
			*cstr++			=	's';
		} else {
			sdr->error("Unexpected parameter type in gather statement\n");
			return;
		}
	}
	*cstr			=	'\0';

	// Allocate end label
	sdr->newLabel(beginLabel);
	sdr->newLabel(endLabel);
	sdr->newLabel(elseLabel);

	fprintf(out,"%s (\"o=%s\") %s %s %s %s %s ",opcodeGatherHeader,str,category,P,N,sampleCone,samples);
	for (i=5;i<numParameters;i++) {
		if (vars[i] == NULL) {
			fprintf(out,"%s ",varNames[i]);
		} else {
			fprintf(out,"%s ",vars[i]->codeName());
		}
	}
	fprintf(out,"\n");

	fprintf(out,"%s:\n",beginLabel);

	if (second != NULL)	{	fprintf(out,"%s %s\n",opcodeGather,elseLabel);	}
	else				{	fprintf(out,"%s %s\n",opcodeGather,endLabel);	}

	first->getCode(out,NULL);

	if (second != NULL) {
		fprintf(out,"%s:\n",elseLabel);
		fprintf(out,"%s\t%s\n",opcodeGatherElse,endLabel);

		second->getCode(out,NULL);

	}

	fprintf(out,"%s:\n",endLabel);
	fprintf(out,"%s %s\n",opcodeGatherEnd,beginLabel);

	delete [] varNames;
	delete [] vars;

	release(samples);
	release(sampleCone);
	release(N);
	release(P);
	release(category);
}



















//////////////////////////////////////////////////////////////////////////////////////////////////////////















///////////////////////////////////////////////////////////////////////
// Class				:	CForLoop
// Method				:	CForLoop
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CForLoop::CForLoop(CExpression *s,CExpression *c,CExpression *u,CExpression *b) : CExpression(0) {
	start	=	s;
	cond	=	getConversion(SLC_FLOAT,c);
	update	=	u;
	body	=	b;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CForLoop
// Method				:	~CForLoop
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CForLoop::~CForLoop() {
	if (start != NULL)	delete start;
	if (cond != NULL)	delete cond;
	if (update != NULL)	delete update;
	if (body != NULL)	delete body;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CForLoop
// Method				:	getCode
// Description			:	-
// Return Value			:	-
// Comments				:
void		CForLoop::getCode(FILE *out,CVariable *dest) {
	char	bodyLabel[32];
	char	contLabel[32];
	char	endLabel[32];

	sdr->newLabel(bodyLabel);
	sdr->newLabel(contLabel);
	sdr->newLabel(endLabel);

	if (start != NULL) {
		start->getCode(out,NULL);
	}

	fprintf(out,"%s\t%s %s %s\n",opcodeBeginfor,bodyLabel,contLabel,endLabel);

	fprintf(out,"%s:\n",bodyLabel);

	lock(condition,cond);

	fprintf(out,"%s\t%s\n",opcodeFor,condition);

	release(condition);

	if (body != NULL)	body->getCode(out,NULL);

	
	fprintf(out,"%s:\n",contLabel);

	if (update != NULL) {
		update->getCode(out,NULL);
	}

	fprintf(out,"%s:\n",endLabel);

	fprintf(out,"%s\n",opcodeEndfor);
}














//////////////////////////////////////////////////////////////////////////////////////////////////////////















///////////////////////////////////////////////////////////////////////
// Class				:	CIlluminationLoop
// Method				:	CIlluminationLoop
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CIlluminationLoop::CIlluminationLoop(CList<CExpression *> *p,CExpression *b) : CExpression(0), category(NULL), P(NULL), N(NULL), angle(NULL), body(b) {
	// Note that p is reverse

	// Figure out the number of core items
	int	numCore;
	for (numCore=1;numCore<p->numItems;++numCore) {
		if (p->array[p->numItems-numCore-1]->type & SLC_STRING) break;
	}

	// Get the parameters
	switch(numCore) {
	case 1:		
		this->P			=	getConversion(SLC_VECTOR,p->array[p->numItems-1-0]);
		break;
	case 2:		
		this->category	=	getConversion(SLC_STRING,p->array[p->numItems-1-0]);
		this->P			=	getConversion(SLC_VECTOR,p->array[p->numItems-1-1]);
		break;
	case 3:		
		this->P			=	getConversion(SLC_VECTOR,p->array[p->numItems-1-0]);
		this->N			=	getConversion(SLC_VECTOR,p->array[p->numItems-1-1]);
		this->angle		=	getConversion(SLC_FLOAT,p->array[p->numItems-1-2]);
		break;
	case 4:		
		this->category	=	getConversion(SLC_STRING,p->array[p->numItems-1-0]);
		this->P			=	getConversion(SLC_VECTOR,p->array[p->numItems-1-1]);
		this->N			=	getConversion(SLC_VECTOR,p->array[p->numItems-1-2]);
		this->angle		=	getConversion(SLC_FLOAT,p->array[p->numItems-1-3]);
		break;
	default:
		sdr->error("Invalid number of parameters to the illumination loop");
		break;
	}

	// We're done with the list
	delete p;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CIlluminationLoop
// Method				:	~CIlluminationLoop
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CIlluminationLoop::~CIlluminationLoop() {
	if (category != NULL)	delete category;
	if (P != NULL)			delete P;
	if (N != NULL)			delete N;
	if (angle != NULL)		delete angle;
	if (body != NULL)		delete body;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CIlluminationLoop
// Method				:	getCode
// Description			:	-
// Return Value			:	-
// Comments				:
void		CIlluminationLoop::getCode(FILE *out,CVariable *dest) {
	char	beginLabel[32];
	char	endLabel[32];

	sdr->newLabel(beginLabel);
	sdr->newLabel(endLabel);

	lock(op1,P);
	lock(op2,N);
	lock(op3,angle);
	lock(op4,category);


	fprintf(out,"%s\t",opcodeIlluminance);

	if (op1 != NULL) {
		fprintf(out," %s ",op1);
	}

	if (op2 != NULL) {
		fprintf(out," %s ",op2);
	}

	if (op3 != NULL) {
		fprintf(out," %s ",op3);
	}

//	fprintf(out," %s %s\n",beginLabel,endLabel);
	fprintf(out," %s %s",beginLabel,endLabel);
	if (op4 != NULL) {
		fprintf(out," %s ",op4);
	}
	fprintf(out,"\n");
	
	fprintf(out,"%s:\n",beginLabel);

	if (body != NULL)	body->getCode(out,NULL);

	fprintf(out,"%s:\n",endLabel);

	fprintf(out,"%s\n",opcodeEndIlluminance);

	if (op4 != NULL)	release(op4);
	if (op3 != NULL)	release(op3);
	if (op2 != NULL)	release(op2);
	if (op1 != NULL)	release(op1);
}












///////////////////////////////////////////////////////////////////////
// Class				:	CIlluminateSolar
// Method				:	CIlluminateSolar
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CIlluminateSolar::CIlluminateSolar(const char *op1,const char *op2,CExpression *p,CExpression *n,CExpression *a,CExpression *b) : CExpression(0) {
	beginOpcode	=	strdup(op1);
	endOpcode	=	strdup(op2);
	this->P		=	(p != NULL ? getConversion(SLC_VECTOR,p) : NULL);
	this->N		=	(n != NULL ? getConversion(SLC_VECTOR,n) : NULL);
	this->angle	=	(a != NULL ? getConversion(SLC_FLOAT,a) : NULL);
	this->body	=	b;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CIlluminateSolar
// Method				:	~CIlluminateSolar
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CIlluminateSolar::~CIlluminateSolar() {
	if (P != NULL)		delete P;
	if (N != NULL)		delete N;
	if (angle != NULL)	delete angle;
	if (body != NULL)	delete body;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CIlluminateSolar
// Method				:	getCode
// Description			:	-
// Return Value			:	-
// Comments				:
void		CIlluminateSolar::getCode(FILE *out,CVariable *dest) {
	char		endLabel[32];

	// Allocate end label
	sdr->newLabel(endLabel);

	lock(op1,P);
	lock(op2,N);
	lock(op3,angle);

	fprintf(out,"%s\t",beginOpcode);

	if (op1 != NULL)	{
		fprintf(out," %s ",op1);
	}

	if (op2 != NULL)	{
		fprintf(out," %s ",op2);
	}

	if (op3 != NULL)	{
		fprintf(out," %s ",op3);
	}

	fprintf(out," %s\n",endLabel);

	if (body != NULL)	body->getCode(out,NULL);

	fprintf(out,"%s:\n",endLabel);

	fprintf(out,"%s\n",endOpcode);

	if (op3 != NULL)	release(op3);
	if (op2 != NULL)	release(op2);
	if (op1 != NULL)	release(op1);
}













///////////////////////////////////////////////////////////////////////
// Class				:	CFixedExpression
// Method				:	CFixedExpression
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CFixedExpression::CFixedExpression(const char *f) : CExpression(SLC_NONE)  {
	fixed	=	strdup(f);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFixedExpression
// Method				:	~CFixedExpression
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CFixedExpression::~CFixedExpression() {
	free(fixed);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CFixedExpression
// Method				:	getCode
// Description			:	-
// Return Value			:	-
// Comments				:
void			CFixedExpression::getCode(FILE *out,CVariable *dest) {
	if (dest != NULL) {
		sdr->error("Destination variable \"%s\" was not expected\n",dest->symbolName);
		return;
	}


	fprintf(out,fixed);
}


























///////////////////////////////////////////////////////////////////////
// Function				:	getOperation
// Description			:	Generate code for a binary operation
// Return Value			:	The generated expression
// Comments				:
CExpression	*getOperation(CExpression *first,CExpression *second,const char *opcodeFloat,const char *opcodeVector,const char *opcodeMatrix,const char *opcodeString,int typeOverwrite) {
	if ((first->type | second->type) & SLC_ARRAY) {
		delete first;
		delete second;
		sdr->error("Direct operations on arrays is not possible\n");
		return	new CNullExpression;
	}
	
	// Do the types match
	if ((first->type & SLC_TYPE_MASK) == (second->type & SLC_TYPE_MASK)) {
		// Yesss

		if (first->type & SLC_FLOAT)	{
			if (opcodeFloat == NULL) {
				sdr->error("This operation is not defined on floats\n");
			} else {
				return	new CBinaryExpression((typeOverwrite ? typeOverwrite : SLC_FLOAT),opcodeFloat,first,second);
			}
		} else if (first->type & SLC_VECTOR) {	
			if (opcodeVector == NULL) {
				sdr->error("This operation is not defined on vectors\n");
			} else {
				int subtype = (first->type | second->type) & SLC_SUB_TYPE_MASK;
				return	new CBinaryExpression((typeOverwrite ? typeOverwrite : (SLC_VECTOR|subtype)),opcodeVector,first,second);
			}
		} else if (first->type & SLC_MATRIX) {	
			if (opcodeMatrix == NULL) {
				sdr->error("This operation is not defined on matrices\n");
			} else {
				return	new CBinaryExpression((typeOverwrite ? typeOverwrite : SLC_MATRIX),opcodeMatrix,first,second);
			}
		} else if (first->type & SLC_STRING) {	
			if (opcodeString == NULL) {
				sdr->error("This operation is not defined on strings\n");
			} else {
				return	new CBinaryExpression((typeOverwrite ? typeOverwrite : SLC_STRING),opcodeString,first,second);
			}
		} else {
			sdr->fatalbailout();
		}
	} else {
		// Nop, try converting to the most general type
		if ((first->type | second->type) & SLC_STRING) {			
			if (opcodeString == NULL) {
				sdr->error("This operation is not defined on strings\n");
			} else {
				return	new CBinaryExpression((typeOverwrite ? typeOverwrite : SLC_STRING),opcodeString,getConversion(SLC_STRING,first),getConversion(SLC_STRING,second));
			}
		} else if ((first->type | second->type) & SLC_MATRIX) {		
			if (opcodeMatrix == NULL) {
				sdr->error("This operation is not defined on matrices\n");
			} else {
				return	new CBinaryExpression((typeOverwrite ? typeOverwrite : SLC_MATRIX),opcodeMatrix,getConversion(SLC_MATRIX,first),getConversion(SLC_MATRIX,second));
			}
		} else if ((first->type | second->type) & SLC_VECTOR)	{	
			if (opcodeVector == NULL) {
				sdr->error("This operation is not defined on vectors\n");
			} else {
				int subtype = (first->type | second->type) & SLC_SUB_TYPE_MASK;
				return	new CBinaryExpression((typeOverwrite ? typeOverwrite : (SLC_VECTOR|subtype)),opcodeVector,getConversion(SLC_VECTOR,first),getConversion(SLC_VECTOR,second));
			}
		} else if ((first->type | second->type) & SLC_FLOAT) {		
			if (opcodeFloat == NULL) {
				sdr->error("This operation is not defined on floats\n");
			} else {
				return	new CBinaryExpression(SLC_FLOAT,opcodeFloat,getConversion((typeOverwrite ? typeOverwrite : SLC_FLOAT),first),getConversion(SLC_FLOAT,second));
			}
		} else {
			sdr->fatalbailout();
		}
	}

	delete first;
	delete second;
	assert(FALSE);
	return	new CNullExpression();
}

///////////////////////////////////////////////////////////////////////
// Function				:	getOperation
// Description			:	Generate a unary operation
// Return Value			:	The generated expression
// Comments				:
CExpression *getOperation(CExpression *first,const char *opcodeFloat,const char *opcodeVector,const char *opcodeMatrix,const char *opcodeString,int typeOverwrite) {
	if (first->type & SLC_ARRAY) {
		delete first;
		sdr->error("Direct operations on arrays is not possible\n");
		return	new CNullExpression();
	}
		
	if (first->type & SLC_FLOAT)		return	new CUnaryExpression((typeOverwrite ? typeOverwrite : SLC_FLOAT),opcodeFloat,first);
	else if (first->type & SLC_VECTOR)	return	new CUnaryExpression((typeOverwrite ? typeOverwrite : (SLC_VECTOR | (first->type & SLC_SUB_TYPE_MASK))),opcodeVector,first);
	else if (first->type & SLC_MATRIX)	return	new CUnaryExpression((typeOverwrite ? typeOverwrite : SLC_MATRIX),opcodeMatrix,first);
	else if (first->type & SLC_STRING)	return	new CUnaryExpression((typeOverwrite ? typeOverwrite : SLC_STRING),opcodeString,first);
	else {
		assert(FALSE);
	}

	return	new CNullExpression;
}

///////////////////////////////////////////////////////////////////////
// Function				:	getConversion
// Description			:	Convert an expression to a desired type
// Return Value			:	The converted expression
// Comments				:
CExpression	*getConversion(int type,CExpression *first) {
	
	const char* firsttype = "none";
	if (first->type & SLC_STRING)
		firsttype = "string";
	else if (first->type & SLC_FLOAT)
		firsttype = "float";
	else if (first->type & SLC_VECTOR)
		firsttype = "vector";
	else if (first->type & SLC_MATRIX)
		firsttype = "matrix";

	const char* desttype = "none";
	if (type & SLC_STRING)
		desttype = "string";
	else if (type & SLC_FLOAT)
		desttype = "float";
	else if (type & SLC_VECTOR)
		desttype = "vector";
	else if (type & SLC_MATRIX)
		desttype = "matrix";
	
	const char* unabletocast = "Unable to cast %s to %s\n";
	if (type & SLC_STRING) {
		if (first->type & SLC_STRING)	return first;
		else {
			sdr->error(unabletocast, firsttype, desttype);
			delete first;
		}
	} else if (type & SLC_FLOAT) {
		if (first->type & SLC_FLOAT)	return first;
		else {
			sdr->error(unabletocast, firsttype, desttype);
			delete first;
		}
	} else if (type & SLC_VECTOR) {
		if (first->type & SLC_VECTOR)		{ first->type |= (type & SLC_SUB_TYPE_MASK);	return first; }
		else if (first->type & SLC_FLOAT)	return new CUnaryExpression(SLC_VECTOR | (first->type & SLC_UNIFORM) | (type & SLC_SUB_TYPE_MASK), opcodeVectorFromFloat,first);
		else {
			sdr->error(unabletocast, firsttype, desttype);
			delete first;
		}
	} else if (type & SLC_MATRIX) {
		if (first->type & SLC_MATRIX)		return first;
		else if (first->type & SLC_FLOAT)	return new CUnaryExpression(SLC_MATRIX | (first->type & SLC_UNIFORM),opcodeMatrixFromFloat,first);
		else if (first->type & SLC_VECTOR)	return new CUnaryExpression(SLC_MATRIX | (first->type & SLC_UNIFORM),opcodeMatrixFromVector,first);
		else {
			sdr->error(unabletocast, firsttype, desttype);
			delete first;
		}
	}

	return	new CNullExpression();
}


///////////////////////////////////////////////////////////////////////
// Function				:	getConversion
// Description			:	Convert an expression to a desired type
// Return Value			:	The converted expression
// Comments				:
void	getConversion(FILE *out,CVariable *dest,CExpression *first) {
	CVariable	*cVar;

	if ((dest->type & SLC_UNIFORM) ^ (first->type & SLC_UNIFORM)) {
		getContainer(out,dest,first);
		return;
	}

	const char* firsttype = "none";
	if (first->type & SLC_STRING)
		firsttype = "string";
	else if (first->type & SLC_FLOAT)
		firsttype = "float";
	else if (first->type & SLC_VECTOR)
		firsttype = "vector";
	else if (first->type & SLC_MATRIX)
		firsttype = "matrix";

	const char* desttype = "none";
	if (dest->type & SLC_STRING)
		desttype = "string";
	else if (dest->type & SLC_FLOAT)
		desttype = "float";
	else if (dest->type & SLC_VECTOR)
		desttype = "vector";
	else if (dest->type & SLC_MATRIX)
		desttype = "matrix";
	
	const char* unabletocast = "Unable to cast %s to %s\n";
	
	cVar	=	first->getVariable();

	if (cVar == NULL) {
		if ((first->type & dest->type & SLC_TYPE_MASK & (~SLC_NONE)) == 0) {
			// We need one more intermediate variable
			CVariable	*tVar	=	sdr->lockRegister(first->type);

			first->getCode(out,tVar);

			if (dest->type & SLC_STRING) {
				sdr->error(unabletocast, firsttype, desttype);
			} else if (dest->type & SLC_FLOAT) {
				sdr->error(unabletocast, firsttype, desttype);
			} else if (dest->type & SLC_VECTOR) {
				if (first->type & SLC_FLOAT)	{
					fprintf(out,"%s\t%s %s\n",opcodeVectorFromFloat,dest->codeName(),tVar->codeName());
				} else {
					sdr->error(unabletocast, firsttype, desttype);
				}
			} else if (dest->type & SLC_MATRIX) {
				if (first->type & SLC_FLOAT) {
					fprintf(out,"%s\t%s %s\n",opcodeMatrixFromFloat,dest->codeName(),tVar->codeName());
				} else if (first->type & SLC_VECTOR) {
					fprintf(out,"%s\t%s %s\n",opcodeMatrixFromVector,dest->codeName(),tVar->codeName());
				} else {
					sdr->error(unabletocast, firsttype, desttype);
				}
			}


			sdr->releaseRegister(tVar);
		} else {
			// Types agree, no intermediate conversion is necessary
			first->getCode(out,dest);
		}
	} else {
		if (dest->type & SLC_STRING) {
			if (first->type & SLC_STRING)	{
				fprintf(out,"%s\t%s %s\n",opcodeMoveStringString,dest->codeName(),cVar->codeName());
			} else {
				sdr->error(unabletocast, firsttype, desttype);
			}
		} else if (dest->type & SLC_FLOAT)	{
			if (first->type & SLC_FLOAT)	{
				fprintf(out,"%s\t%s %s\n",opcodeMoveFloatFloat,dest->codeName(),cVar->codeName());
			} else {
				sdr->error(unabletocast, firsttype, desttype);
			}
		} else if (dest->type & SLC_VECTOR) {
			if (first->type & SLC_VECTOR)	{
				fprintf(out,"%s\t%s %s\n",opcodeMoveVectorVector,dest->codeName(),cVar->codeName());
			} else if (first->type & SLC_FLOAT)	{
				fprintf(out,"%s\t%s %s\n",opcodeVectorFromFloat,dest->codeName(),cVar->codeName());
			} else {
				sdr->error(unabletocast, firsttype, desttype);
			}
		} else if (dest->type & SLC_MATRIX) {
			if (first->type & SLC_MATRIX)	{
				fprintf(out,"%s\t%s %s\n",opcodeMoveMatrixMatrix,dest->codeName(),cVar->codeName());
			} else if (first->type & SLC_FLOAT) {
				fprintf(out,"%s\t%s %s\n",opcodeMatrixFromFloat,dest->codeName(),cVar->codeName());
			} else if (first->type & SLC_VECTOR) {
				fprintf(out,"%s\t%s %s\n",opcodeMatrixFromVector,dest->codeName(),cVar->codeName());
			} else {
				sdr->error(unabletocast, firsttype, desttype);
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	getConversion
// Description			:	Generates a coordinate system conversion code
// Return Value			:	The generated expression
// Comments				:
CExpression	*getConversion(int type,const char *system,CExpression *first) {
	if (type & SLC_VECTOR) {
		if (type & (SLC_VVECTOR | SLC_VNORMAL))
			return new CSysConversionExpression(type,opcodeVectorFrom,system,getConversion(SLC_VECTOR | (type & SLC_SUB_TYPE_MASK) | (first->type & SLC_UNIFORM) ,first));
		else if (type & SLC_VPOINT)
			return new CSysConversionExpression(type,opcodePointFrom,system,getConversion(SLC_VECTOR | (type & SLC_SUB_TYPE_MASK) | (first->type & SLC_UNIFORM) ,first));
		else if (type & SLC_VCOLOR)
			return new CSysConversionExpression(type,opcodeColorFrom,system,getConversion(SLC_VECTOR | (type & SLC_SUB_TYPE_MASK) | (first->type & SLC_UNIFORM) ,first));
		else {
			delete first;
			sdr->error("Invalid type for system conversion\n");
		}
	} else if (type & SLC_MATRIX) {
		return new CSysConversionExpression(type,opcodeMatrixFrom,system,getConversion(SLC_MATRIX | (first->type & SLC_UNIFORM) ,first));
	} else {
		delete first;
		sdr->error("Invalid type for system conversion\n");
	}

	return	new CNullExpression();
}

///////////////////////////////////////////////////////////////////////
// Function				:	getAssignment
// Description			:	Generates an assignment code
// Return Value			:	The generated expression
// Comments				:
CExpression		*getAssignment(CList<CVariable *> *variables,CExpression *expression) {
	CVariable	*cVar;
	CExpression	*cExpression	=	expression;
	char		tmp[256];

	for (cVar=variables->pop();cVar != NULL;cVar=variables->pop()) {

		if (cVar->type & SLC_ARRAY) {
			sdr->error("Can not assign to whole array %s\n",cVar->symbolName);
			continue;
		}
		
		if (cVar->type & SLC_UNIFORM) 
			if (!(expression->type & SLC_UNIFORM)) {
				sdr->error("Can not assign to uniform variable %s\n",cVar->symbolName);
				continue;
			}

		if ((cVar->type & SLC_PARAMETER) && (expression->value(tmp))) {
			CParameter	*cPar	=	(CParameter *) cVar;

			if (	(cVar->type & expression->type & SLC_TYPE_MASK) ||
					((cVar->type & SLC_VECTOR) && (expression->type & SLC_FLOAT)) ||
					((cVar->type & SLC_MATRIX) && (expression->type & SLC_FLOAT)) ||
					((cVar->type & SLC_MATRIX) && (expression->type & SLC_VECTOR))) {

				cPar->defaultValue	=	strdup(tmp);

				if (cVar->type & SLC_STRING)	continue;
				if (tmp[0] != '"')				continue;

			} else {
				sdr->error("Parameter initializer for \"%s\" is incompatible\n",cVar->symbolName);
			}
		}

		cExpression	=	new CAssignmentExpression(cVar,cExpression);
	}

	if (cExpression == expression) {
		delete expression;
		return new CNullExpression;
	}

	return	cExpression;
}


///////////////////////////////////////////////////////////////////////
// Function				:	getAssignment
// Description			:	Generates an assignment code
// Return Value			:	The generated expression
// Comments				:
CExpression		*getAssignment(CList<CVariable *> *variables,CList<CExpression *> *expressions) {
	CVariable	*cVar;
	CExpression	*pExpression	=	NULL;
	int i,hasNamedSpace,hasComplexRef;
	char tmp[128],*tmp2;

#define NEWARRAYPARSE
#ifdef NEWARRAYPARSE

	while((cVar=variables->pop()) != NULL) {
		hasNamedSpace = FALSE;
		hasComplexRef = FALSE;
		
		if (cVar->type & SLC_PARAMETER){
			CParameter	*cPar	=	(CParameter *) cVar;
			
			// Do we have the right number of arguments
			if(expressions->numItems == cPar->numItems) {

				for(i=0;i<expressions->numItems;i++) {

					if(!	((cVar->type & (*expressions)[i]->type & SLC_TYPE_MASK) ||
							((cVar->type & SLC_VECTOR) && ((*expressions)[i]->type & SLC_FLOAT)) ||
							((cVar->type & SLC_MATRIX) && ((*expressions)[i]->type & SLC_FLOAT)) ||
							((cVar->type & SLC_MATRIX) && ((*expressions)[i]->type & SLC_VECTOR)))) {
						sdr->error("Parameter initializer for \"%s\" is incompatible\n",cVar->symbolName);
						break;
					}
				}
				
				tmp2 = (char*)malloc(expressions->numItems * 128);
				sprintf(tmp2,"[ ");
				for(i=expressions->numItems-1;i>=0;i--){
					if((*expressions)[i]->value(tmp)){
						strcat(tmp2,tmp);
						strcat(tmp2," ");
						// Don't emit defaults for items with space specifier
						if((tmp[0] == '"') && !(cVar->type & SLC_STRING)) {
							hasNamedSpace = TRUE;
							break;
						}
					} else {
						hasComplexRef = TRUE;
						break;
					}
				}
				strcat(tmp2," ]");

				if(!hasNamedSpace && !hasComplexRef){
					cPar->defaultValue	=	strdup(tmp2);
				}
				free(tmp2);
			}
			else{	// item count mismatch
				sdr->error("Parameter initializer for \"%s\" has wrong number of items\n",cVar->symbolName);
			}
		}
	
		CExpression	*cExpression	=	new CArrayMove(cVar,expressions);

		if (pExpression == NULL)	pExpression	=	cExpression;
		else						pExpression	=	new CTwoExpressions(cExpression,pExpression);
	}

	if(pExpression == NULL){
		delete expressions;
		return new CNullExpression;
	}
	
	return	pExpression;
	
#else
	while((cVar=variables->pop()) != NULL) {
		
		CExpression	*cExpression	=	new CArrayMove(cVar,expressions);

		if (pExpression == NULL)	pExpression	=	cExpression;
		else						pExpression	=	new CTwoExpressions(cExpression,pExpression);
	}

	return	pExpression;
#endif
}

