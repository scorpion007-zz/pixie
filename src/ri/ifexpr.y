%{
//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright � 1999 - 2003, Okan Arikan
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
//  File				:	ifexpr.y
//  Classes				:	-
//  Description			:	Parser for the IF expressions
//
////////////////////////////////////////////////////////////////////////
#undef alloca
#include <string.h>

#include "common/os.h"
#include "config.h"
#include "error.h"
#include "rendererc.h"
#include "renderer.h"
#include "rendererContext.h"

int				iflex(void );					// Forward definition for stupid yacc
void			iferror(char *,...);

static	CRendererContext	*context	=	NULL;
static	int					result		=	0;	// 0 - FALSE
												// 1 - TRUE
												// 2 - error



	///////////////////////////////////////////////////////////////////////
	// Class				:	CExpr
	// Description			:	Holds an expression value
	// Comments				:
	class CExpr {
	public:
			EVariableType	type;
			void			*value;
			float			tmp;
			int				tmpInt;
			char			tmpString[128];	// HACK
	};

	///////////////////////////////////////////////////////////////////////
	// Function				:	getString
	// Description			:	Take the expression and form a string
	// Return Value			:	The string
	// Comments				:
	static	inline	const char	*getString(const CExpr &expr) {
		switch (expr.type) {
			case TYPE_FLOAT:
			case TYPE_COLOR:
			case TYPE_VECTOR:
			case TYPE_NORMAL:
			case TYPE_POINT:
			case TYPE_MATRIX:
			case TYPE_QUAD:
			case TYPE_DOUBLE:
				break;
			case TYPE_STRING:
				return (const char *) expr.value;
			case TYPE_INTEGER:
			case TYPE_BOOLEAN:
			default:
				break;
		};
		
		error(CODE_SYNTAX,"Unable to cast a string in the epxression");
		
		return "__nonsense__";
	}


	///////////////////////////////////////////////////////////////////////
	// Function				:	getFloat
	// Description			:	Take the expression and form a float
	// Return Value			:	The float
	// Comments				:
	static	inline	float		getFloat(const CExpr &expr) {
		switch (expr.type) {
			case TYPE_FLOAT:
				return *((float *) expr.value);
			case TYPE_COLOR:
			case TYPE_VECTOR:
			case TYPE_NORMAL:
			case TYPE_POINT:
			case TYPE_MATRIX:
			case TYPE_QUAD:
			case TYPE_DOUBLE:
			case TYPE_STRING:
				break;
			case TYPE_INTEGER:
			case TYPE_BOOLEAN:
				return (float) *((int *) expr.value);
			default:
				break;
		};
		
		error(CODE_SYNTAX,"Unable to cast a float in the epxression");
		
		return 0;
	}

	///////////////////////////////////////////////////////////////////////
	// Function				:	getInt
	// Description			:	Take the expression and form an int
	// Return Value			:	The int
	// Comments				:
	static	inline	int		getInt(const CExpr &expr) {
		switch (expr.type) {
			case TYPE_FLOAT:
				return (int) *((float *) expr.value);
			case TYPE_COLOR:
			case TYPE_VECTOR:
			case TYPE_NORMAL:
			case TYPE_POINT:
			case TYPE_MATRIX:
			case TYPE_QUAD:
			case TYPE_DOUBLE:
			case TYPE_STRING:
				break;
			case TYPE_INTEGER:
			case TYPE_BOOLEAN:
				return *((int *) expr.value);
			default:
				break;
		};
		
		error(CODE_SYNTAX,"Unable to cast a integer in the epxression");
		
		return 0;
	}

	///////////////////////////////////////////////////////////////////////
	// Function				:	setFloat
	// Description			:	Create a float expression
	// Return Value			:
	// Comments				:
	static	inline	void		setFloat(CExpr &expr,float val) {
		expr.type	=	TYPE_FLOAT;
		expr.value	=	&expr.tmp;
		expr.tmp	=	val;
	}

	///////////////////////////////////////////////////////////////////////
	// Function				:	setInt
	// Description			:	Create an int expression
	// Return Value			:
	// Comments				:
	static	inline	void		setInt(CExpr &expr,int val) {
		expr.type	=	TYPE_INTEGER;
		expr.value	=	&expr.tmpInt;
		expr.tmpInt	=	val;
	}

	///////////////////////////////////////////////////////////////////////
	// Function				:	findExpr
	// Description			:	Find a float expression
	// Return Value			:
	// Comments				:
	static	void				findExpr(CExpr &expr,const char *name) {
		if (strncmp(name,"Attribute:",10) == 0) {
			name	+=	10;
			
			// Lookup the attributes
		} else if (strncmp(name,"Option:",7) == 0) {
			name	+=	7;
			
			// Lookup the options
		} else {
		}
	}


%}
%union slval {
	char	string[PARSER_MAX_STRING_SIZE];
	CExpr	expr;
	float	real;
}

%token			IF_OPEN
%token			IF_CLOSE
%token			IF_PLUS
%token			IF_MINUS
%token			IF_MUL
%token			IF_DIV
%token			IF_MULMUL
%token			IF_AND
%token			IF_POW
%token			IF_OR
%token			IF_EQUAL
%token			IF_NEQUAL
%token			IF_LESSE
%token			IF_GREATERE
%token			IF_LESS
%token			IF_GREATER
%token			IF_ANDAND
%token			IF_OROR
%token			IF_NOT
%token			IF_DOLLAR
%token			IF_MATCH
%token			IF_DEFINED
%token			IF_CONCAT
%token			IF_COMMA
%token<string>	IF_TEXT_VALUE
%token<string>	IF_IDENTIFIER_VALUE
%token<real>	IF_FLOAT_VALUE
%type<expr>		ifExpr

%left  			IF_EQUAL
%left			IF_NEQUAL
%left  			IF_GREATERE
%left			IF_LESSE 
%left			IF_GREATER 
%left			IF_LESS
%left  			IF_PLUS	
%left			IF_MINUS 
%left  			IF_DIV 
%left			IF_MUL
%left  			IF_OR
%left  			IF_AND
%left  			IF_OROR
%left  			IF_ANDAND
%left  			IF_POW
%left 			IF_NOT
%left			IF_MATCH
%left			IF_DOLLAR
%%
start:			ifExpr
				{
					////////////////////////////////////////////////////////////////////
					// Compute the value of the expression
					if ($1.type == TYPE_STRING)	result	=	TRUE;
					else						result	=	getFloat($1) != 0;
				};
				
ifExpr:			//////////////////////////////////////////////////////////////////////////
				// The terminals
				IF_DOLLAR
				IF_IDENTIFIER_VALUE
				{
					// Find the variable here
					findExpr($$,$2);
				}
				|
				IF_DOLLAR
				IF_OPEN
				ifExpr
				IF_CLOSE
				{
					// FIXME: This is wrong. What are we supposed to do here ?
					
					// Find the variable here
					findExpr($$,getString($3));
				}
				|
				IF_FLOAT_VALUE
				{
					setFloat($$,$1);
				}
				|
				IF_TEXT_VALUE
				{
					$$.type		=	TYPE_STRING;
					$$.value	=	$$.tmpString;
					strcpy($$.tmpString,$1);
				}
				|
				//////////////////////////////////////////////////////////////////////////
				// The arithmetic operations
				ifExpr
				IF_PLUS
				ifExpr
				{
					setFloat($$,getFloat($1) + getFloat($3));
				}
				|
				ifExpr
				IF_MINUS
				ifExpr
				{
					setFloat($$,getFloat($1) - getFloat($3));
				}
				|
				ifExpr
				IF_MUL
				ifExpr
				{
					setFloat($$,getFloat($1) * getFloat($3));
				}
				|
				ifExpr
				IF_DIV
				ifExpr
				{
					setFloat($$,getFloat($1) / getFloat($3));
				}
				|
				//////////////////////////////////////////////////////////////////////////
				// The bitwise operations (run on integers)
				ifExpr
				IF_AND
				ifExpr
				{
					setInt($$,getInt($1) & getInt($3));
				}
				|
				ifExpr
				IF_OR
				ifExpr
				{
					setInt($$,getInt($1) | getInt($3));
				}
				|
				ifExpr
				IF_POW
				ifExpr
				{
					setInt($$,getInt($1) ^ getInt($3));
				}
				|
				//////////////////////////////////////////////////////////////////////////
				// Relational operations
				ifExpr
				IF_EQUAL
				ifExpr
				{
					if ($1.type == TYPE_STRING || $3.type == TYPE_STRING) {
						setInt($$,strcmp(getString($1),getString($3)) == 0);
					} else {
						setInt($$,getFloat($1) == getFloat($3));
					}
				}
				|
				ifExpr
				IF_NEQUAL
				ifExpr
				{
					if ($1.type == TYPE_STRING || $3.type == TYPE_STRING) {
						setInt($$,strcmp(getString($1),getString($3)) != 0);
					} else {
						setInt($$,getFloat($1) != getFloat($3));
					}
				}
				|
				ifExpr
				IF_GREATER
				ifExpr
				{
					if ($1.type == TYPE_STRING || $3.type == TYPE_STRING) {
						setInt($$,strcmp(getString($1),getString($3)) > 0);
					} else {
						setInt($$,getFloat($1) > getFloat($3));
					}
				}
				|
				ifExpr
				IF_LESS
				ifExpr
				{
					if ($1.type == TYPE_STRING || $3.type == TYPE_STRING) {
						setInt($$,strcmp(getString($1),getString($3)) < 0);
					} else {
						setInt($$,getFloat($1) < getFloat($3));
					}
				}
				|
				ifExpr
				IF_GREATERE
				ifExpr
				{
					if ($1.type == TYPE_STRING || $3.type == TYPE_STRING) {
						setInt($$,strcmp(getString($1),getString($3)) >= 0);
					} else {
						setInt($$,getFloat($1) >= getFloat($3));
					}
				}
				|
				ifExpr
				IF_LESSE
				ifExpr
				{
					if ($1.type == TYPE_STRING || $3.type == TYPE_STRING) {
						setInt($$,strcmp(getString($1),getString($3)) <= 0);
					} else {
						setInt($$,getFloat($1) <= getFloat($3));
					}
				}				
				|
				//////////////////////////////////////////////////////////////////////////
				// String matching
				ifExpr
				IF_MATCH
				ifExpr
				{
					// FIXME: Implement pattern matching
					setInt($$,strcmp(getString($1),getString($3)) == 0);
				}
				|
				//////////////////////////////////////////////////////////////////////////
				// Logical operations
				ifExpr
				IF_ANDAND
				ifExpr
				{
					setInt($$,getInt($1) && getInt($3));
				}
				|
				ifExpr
				IF_OROR
				ifExpr
				{
					setInt($$,getInt($1) || getInt($3));
				}
				|
				IF_NOT
				ifExpr
				{
					setInt($$,! getInt($2));
				}
				|
				//////////////////////////////////////////////////////////////////////////
				// Grouping
				IF_OPEN
				ifExpr
				IF_CLOSE
				{
					$$	=	$2;
				}
				|
				//////////////////////////////////////////////////////////////////////////
				// Defined
				IF_DEFINED
				IF_OPEN
				ifExpr
				IF_CLOSE
				{
					setInt($$,CRenderer::retrieveVariable(getString($3)) != NULL);
				}
				|
				//////////////////////////////////////////////////////////////////////////
				// Concat
				IF_CONCAT
				IF_OPEN
				ifExpr
				IF_COMMA
				ifExpr
				IF_CLOSE
				{
					$$.type		=	TYPE_STRING;
					$$.value	=	$$.tmpString;
					strcpy($$.tmpString,getString($3));
					strcat($$.tmpString,getString($5));
				}
				;
				
%%

#include "lex.if.cpp"


///////////////////////////////////////////////////////////////////////
// Function				:	ifParse
// Description			:	Parse an if statement
// Return Value			:	TRUE/FALSE
// Comments				:
int		CRendererContext::ifParse(const char *expr) {
	YY_BUFFER_STATE savedState	=	YY_CURRENT_BUFFER;		// Save the old buffer
	YY_BUFFER_STATE	newState;

	// Save the necessary info
	context			=	this;
	result			=	0;

	newState		=	if_scan_string(expr);				// Create a new buffer
	ifparse();												// Scan the buffer
	if_delete_buffer(newState);								// Ditch the buffer

	if_switch_to_buffer( savedState );						// Switch to the old buffer

	return result;
}

///////////////////////////////////////////////////////////////////////
// Function				:	dsoerror
// Description			:	Count the parse errors
// Return Value			:
// Comments				:
void	iferror(char *,...) {
	// What do we do in the case of an error ?
	warning(CODE_BADTOKEN,"Condition parse error\n");
}





