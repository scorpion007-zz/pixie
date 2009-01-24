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
//  File				:	expressions.h
//  Classes				:	CExpression
//							CNullExpression
//							CVectorExpression
//							CMatrixExpression
//							CTerminalExpression
//							CConstantTerminalExpression
//							CBinaryExpression
//							CUnaryExpression
//							CSysConversionExpression
//							CFuncallExpression
//							CBuiltinExpression
//							CConditionalExpression
//							CAssignmentExpression
//							CUpdateExpression
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef EXPRESSION_H
#define	EXPRESSION_H

#include "common/containers.h"
#include "common/os.h"

// Forward definitions used
class	CSymbol;							// CSymbol class
class	CVariable;							// CVariable class
class	CParameter;							// CParameter class
class	CFunction;							// CFunction class
class	CFunctionPrototype;					// A function prototype
class	CScriptContext;						// The main shader context. Holds everything

/////////////////////
//
//
//	The mighty expression class
//
//
/////////////////////

///////////////////////////////////////////////////////////////////////
// Class				:	CExpression
// Description			:	This class holds an expression (multiplication , function call, etc)
// Comments				:	
class	CExpression {
public:
						CExpression(int);
	virtual				~CExpression();

	virtual	void		getCode(FILE *,CVariable *);
	virtual	CVariable	*getVariable();
	virtual	int			value(char *);

	int					type;
};



///////////////////////////////////////////////////////////////////////
// Class				:	CTwoExpressions
// Description			:	This expression is used to encapsulate multiple expressions
// Comments				:	
class	CTwoExpressions : public CExpression {
public:
						CTwoExpressions(CExpression *,CExpression *);
						~CTwoExpressions();

			void		getCode(FILE *,CVariable *);


			CExpression	*first,*second;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CNullExpression
// Description			:	This class is instanciated if there has been an error
// Comments				:
class	CNullExpression : public CExpression {
public:
						CNullExpression();
};



///////////////////////////////////////////////////////////////////////
// Class				:	CVectorExpression
// Description			:	Cast a vector from a collection of floats
// Comments				:
class	CVectorExpression : public CExpression {
public:
						CVectorExpression(CExpression *,CExpression *,CExpression *);
						~CVectorExpression();

			void		getCode(FILE *,CVariable *);
			int			value(char *);

			CExpression	*x,*y,*z;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CMatrixExpression
// Description			:	Cast a matrix from a collection of 16 floats
// Comments				:
class	CMatrixExpression : public CExpression {
public:
						CMatrixExpression(CExpression **);
						~CMatrixExpression();

			void		getCode(FILE *,CVariable *);
			int			value(char *);

			CExpression	*elements[16];
};

///////////////////////////////////////////////////////////////////////
// Class				:	CTerminalExpression
// Description			:	This encapsulates a variable reference
// Comments				:
class	CTerminalExpression : public CExpression {
public:
						CTerminalExpression(CVariable *);
						~CTerminalExpression();

			void		getCode(FILE *,CVariable *);
			CVariable	*getVariable()	{	 return variable;	}

			CVariable	*variable;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CArrayExpression
// Description			:	Extract a particular item from an array
// Comments				:
class	CArrayExpression : public CExpression {
public:
						CArrayExpression(CVariable *,CExpression *);
						~CArrayExpression();

			void		getCode(FILE *,CVariable *);

			CVariable	*array;
			CExpression	*item;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CConstantExpression
// Description			:	This encapsulates a constant expression
// Comments				:
class	CConstantTerminalExpression : public CExpression {
public:
						CConstantTerminalExpression(int,char *);
						~CConstantTerminalExpression();

			void		getCode(FILE *,CVariable *);
			CVariable	*getVariable()	{	return dummy;	}
			int			value(char *);

			char		*constant;
			CVariable	*dummy;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CBinaryExpression
// Description			:	A binary expression
// Comments				:
class	CBinaryExpression : public CExpression {
public:
						CBinaryExpression(int,const char *,CExpression *,CExpression *);
						~CBinaryExpression();

			void		getCode(FILE *,CVariable *);

			CExpression	*first,*second;
			const char	*opcode;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CUnaryExpression
// Description			:	A unary expression
// Comments				:
class	CUnaryExpression : public CExpression {
public:
						CUnaryExpression(int,const char *,CExpression *);
						~CUnaryExpression();

			void		getCode(FILE *,CVariable *);

			CExpression	*first;
			const char	*opcode;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CSysConversionExpression
// Description			:	System conversion
// Comments				:
class	CSysConversionExpression : public CExpression {
public:
						CSysConversionExpression(int,const char *,const char *,CExpression *);
						~CSysConversionExpression();

			void		getCode(FILE *,CVariable *);
			int			value(char *);

			CExpression	*first;
			const char	*opcode;
			char		*system;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CFuncallExpression
// Description			:	Function call
// Comments				:
class	CFuncallExpression : public CExpression {
public:
						CFuncallExpression(CFunction *,CList<CExpression *> *);
						~CFuncallExpression();

			void		getCode(FILE *,CVariable *);

			CList<CExpression *>	*arguments;
			CFunction				*function;
			int			error;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CBuiltinExpression
// Description			:	A built in function call
// Comments				:
class	CBuiltinExpression : public CExpression {
public:
						CBuiltinExpression(CFunctionPrototype *,CList<CExpression *> *);
						~CBuiltinExpression();

			void		getCode(FILE *,CVariable *);

			CList<CExpression *>	*arguments;
			CFunctionPrototype		*function;
			const char				*replacementPrototype;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CConditionalExpression
// Description			:	A conditional statement (?:)
// Comments				:
class	CConditionalExpression : public CExpression {
public:
						CConditionalExpression(int,CExpression *,CExpression *,CExpression *);
						~CConditionalExpression();

			void		getCode(FILE *,CVariable *);

			CExpression	*condition;
			CExpression	*trueExpression;
			CExpression	*falseExpression;
};


///////////////////////////////////////////////////////////////////////
// Class				:	CAssignmentExpression
// Description			:	Assignment expression
// Comments				:
class	CAssignmentExpression : public CExpression {
public:
						CAssignmentExpression(CVariable *,CExpression *);
						~CAssignmentExpression();

			void		getCode(FILE *,CVariable *);

			CVariable	*first;
			CExpression	*second;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CArrayAssignmentExpression
// Description			:	Assignment expression
// Comments				:
class	CArrayAssignmentExpression : public CExpression {
public:
						CArrayAssignmentExpression(CVariable *,CExpression *,CExpression *);
						~CArrayAssignmentExpression();

			void		getCode(FILE *,CVariable *);

			CVariable	*first;
			CExpression	*index;
			CExpression	*second;
};


///////////////////////////////////////////////////////////////////////
// Class				:	CArrayAssignmentExpression
// Description			:	Assignment expression
// Comments				:
class	CArrayUpdateExpression : public CExpression {
public:
						CArrayUpdateExpression(CVariable *,CExpression *,CExpression *,const char *,const char *,const char *);
						~CArrayUpdateExpression();

			void		getCode(FILE *,CVariable *);

			CVariable	*first;
			CVariable	*indexVar;
			CExpression	*index;
			CExpression *arrayAssigner;
};


///////////////////////////////////////////////////////////////////////
// Class				:	CArray
// Description			:	Assignment expression
// Comments				:
class	CArrayMove : public CExpression {
public:
						CArrayMove(CVariable *,CList<CExpression *> *);
						~CArrayMove();

			void		getCode(FILE *,CVariable *);

			CVariable				*first;
			CList<CExpression *>	*items;
};



///////////////////////////////////////////////////////////////////////
// Class				:	CUpdateExpression
// Description			:	Update expression
// Comments				:
class	CUpdateExpression : public CExpression {
public:
						CUpdateExpression(CVariable *,const char *,const char *,int,CExpression *);
						~CUpdateExpression();

			void		getCode(FILE *,CVariable *);

			CVariable	*first;
			CExpression	*second;
			const char	*opcodeFloat,*opcodeVector;
			int			pre;
};


///////////////////////////////////////////////////////////////////////
// Class				:	CIfThenElse
// Description			:	If - Then - Else expression
// Comments				:
class	CIfThenElse : public CExpression {
public:
						CIfThenElse(CExpression *,CExpression *,CExpression *);
						~CIfThenElse();

			void		getCode(FILE *,CVariable *);

			CExpression	*cond;
			CExpression	*first;
			CExpression	*second;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CGatherThenElse
// Description			:	Gather - Then - Else expression
// Comments				:
class	CGatherThenElse : public CExpression {
public:
						CGatherThenElse(CList<CExpression *> *,CExpression *,CExpression *);
						~CGatherThenElse();

			void		getCode(FILE *,CVariable *);

			CList<CExpression *>	*parameterList;
			CExpression				*first;
			CExpression				*second;
};



///////////////////////////////////////////////////////////////////////
// Class				:	CForLoop
// Description			:	For loop
// Comments				:
class	CForLoop : public CExpression {
public:
						CForLoop(CExpression *,CExpression *,CExpression *,CExpression *);
						~CForLoop();

			void		getCode(FILE *,CVariable *);

			CExpression	*start,*cond,*update;
			CExpression	*body;
};



///////////////////////////////////////////////////////////////////////
// Class				:	CIlluminationLoop
// Description			:	Illumination loop
// Comments				:
class	CIlluminationLoop : public CExpression {
public:
						CIlluminationLoop(CList<CExpression *> *,CExpression *);
						~CIlluminationLoop();

			void		getCode(FILE *,CVariable *);

			CExpression	*category,*P,*N,*angle;
			CExpression	*body;
};


///////////////////////////////////////////////////////////////////////
// Class				:	CIlluminateSolar
// Description			:	Illuminate/solar loop
// Comments				:
class	CIlluminateSolar : public CExpression {
public:
						CIlluminateSolar(const char *,const char *,CExpression *,CExpression *,CExpression *,CExpression *);
						~CIlluminateSolar();

			void		getCode(FILE *,CVariable *);

			CExpression	*P,*N,*angle;
			CExpression	*body;
			const char	*beginOpcode,*endOpcode;
};



///////////////////////////////////////////////////////////////////////
// Class				:	CFixedExpression
// Description			:	A fixed string expression
// Comments				:
class	CFixedExpression : public CExpression {
public:
						CFixedExpression(const char *);
						~CFixedExpression();

			void		getCode(FILE *,CVariable *);

			char		*fixed;
};






////////////////////////////////////////////////////////////////////////
//
//	The following functions are used to generate operations and stuff
//
//	All the gunctions below ditch the arguments
//
////////////////////////////////////////////////////////////////////////

CExpression	*getOperation(CExpression *first,CExpression *second,const char *opcodeFloat,const char *opcodeVector,const char *opcodeMatrix,const char *opcodeString,int typeOverwrite);
CExpression *getOperation(CExpression *first,const char *opcodeFloat,const char *opcodeVector,const char *opcodeMatrix,const char *opcodeString,int typeOverwrite);
CExpression	*getConversion(int type,CExpression *first);
CExpression	*getConversion(int type,const char *system,CExpression *first);
void		getConversion(FILE *,CVariable *,CExpression *);
CExpression	*getAssignment(CList<CVariable *> *,CExpression *);
CExpression	*getAssignment(CList<CVariable *> *,CList<CExpression *> *);

//CCodeBlock	*getAssignment(char *,CExpression *);
#endif

