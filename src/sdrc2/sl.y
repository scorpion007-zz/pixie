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
//  File				:	sl.y
//  Classes				:	-
//  Description			:	The main parser file
//
////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//
//
//
//
// 	RenderMan Shading Language Compiler 
//	
//
//
//
//	Author  : Okan Arikan
//	Date	: 05/03/2000
//
//
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////



%{
//////////////////////////////////////////////////////////////////////////
// Misc C definitions
//////////////////////////////////////////////////////////////////////////
#undef alloca
#include	<stdlib.h>
#include	<string.h>

#include	"common/global.h"
#include	"common/os.h"

	void				yyerror(char *);				// Forward definition for stupid yacc
	int					yylex(void );					// Forward definition for stupid yacc
														
%}
%union {
  char					*string;
  float					real;
  int					integer;
}
//////////////////////////////////////////////////////////////////////////
// Token definitions
//////////////////////////////////////////////////////////////////////////
%token			SL_CLASS
%token			SL_SURFACE										// Shader types
%token			SL_DISPLACEMENT
%token			SL_LIGHT
%token			SL_VOLUME
%token			SL_TRANSFORMATION
%token			SL_IMAGER

%token			SL_FOR											// Keywords
%token			SL_WHILE
%token			SL_IF
%token			SL_GATHER
%token			SL_ELSE
%token			SL_BREAK
%token			SL_CONTINUE
%token			SL_ILLUMINANCE
%token			SL_ILLUMINATE
%token			SL_SOLAR
%token			SL_RETURN
%token			SL_VOID

%token			SL_FCN_PI										// Predefined PI constant

%token<string>	SL_IDENTIFIER_VALUE								// Identifier value	
%token<string>	SL_FLOAT_VALUE									// A floating point value

%token			SL_COMMA										// Punctuation marks
%token			SL_SEMI_COLON

%token			SL_OPEN_PARANTHESIS								// Paranthesis	(
%token			SL_CLOSE_PARANTHESIS							// )
%token			SL_OPEN_CRL_PARANTHESIS							// {
%token			SL_CLOSE_CRL_PARANTHESIS						// }
%token			SL_OPEN_SQR_PARANTHESIS							// [
%token			SL_CLOSE_SQR_PARANTHESIS						// ]

%token			SL_TEXTURE
%token			SL_SHADOW
%token			SL_ENVIRONMENT
%token			SL_BUMP

//////////////////////////////////////////////////////////////////////////
// Tokens with precedence relation
//////////////////////////////////////////////////////////////////////////
%left<string> 	SL_TEXT_VALUE

// Assignment (lowest)
%right 			SL_EQUAL
%right			SL_INCREMENT SL_DECREMENT SL_INCREMENT_BY SL_DECREMENT_BY 

// Conditional execution
%left			SL_QUESTION SL_COLON

// Type decls
%left 			SL_FLOAT SL_COLOR SL_POINT SL_VECTOR SL_NORMAL SL_MATRIX SL_STRING

// Boolean operators
%left  			SL_OR
%left  			SL_AND
%left 			SL_NOT

// Relation operators
%left  			SL_COMP_EQUAL SL_COMP_DIFFERENT
%left  			SL_COMP_GREATER SL_COMP_GREATER_EQUAL SL_COMP_LESS SL_COMP_LESS_EQUAL

// Unary oprators
%right			SL_MULTIPLY_BY SL_DIVIDE_BY

// Binary operators
%left  			SL_PLUS SL_MINUS 
%left  			SL_CROSS
%left  			SL_MULTIPLY SL_DIVIDE
%left  			SL_DOT

// Types
%left			SL_OUTPUT
%left			SL_EXTERN
%left			SL_UNIFORM
%left			SL_VARIABLE
%left			SL_PUBLIC
%left			SL_PRIVATE
%start	slStart

// Rule types
%%
slStart:		
			////////////////////////////////////////////////
			// Initilization stuff
			////////////////////////////////////////////////
			{
			}
			slShader 
			{
			}
			;
			
			// Class access
slAccessClass:
			SL_PUBLIC
			{
			}
		|
			SL_PRIVATE
			{
			}
		|
			{
			}
			;

			// The container class
slContainerClass:
			SL_UNIFORM
			{
			}
		|
			SL_VARIABLE
			{
			}
		|
			{
			}
			;

			// The inheritance class
slInheritanceClass:
			SL_EXTERN
			{
			}
		|
			{
			}
			;

			// The output class
slOutputClass:
			SL_OUTPUT
			{
			}
		|
			{
			}
			;

			// The type class
slTypeClass:
			SL_VOID
			{
			}
		|
			SL_FLOAT
			{
			}
		|
			SL_COLOR
			{
			}
		|
			SL_VECTOR
			{
			}
		|
			SL_NORMAL
			{
			}
		|
			SL_POINT
			{
			}
		|
			SL_MATRIX
			{
			}
		|
			SL_STRING
			{
			}
			;
			
			// A type decleration
slTypeDecl:
			slAccessClass
			slInheritanceClass
			slOutputClass
			slContainerClass
			slTypeClass
			{
			}
			;

			// An array declaration
slArrayDecl:
			SL_OPEN_SQR_PARANTHESIS
			slAritmeticExpression
			SL_CLOSE_SQR_PARANTHESIS
			{
			}
		|
			SL_OPEN_SQR_PARANTHESIS
			slAritmeticExpression
			SL_CLOSE_SQR_PARANTHESIS
			{
			}
		|
			{
			}
			;

			// The list of identifiers
slIdentifiers:
			SL_IDENTIFIER_VALUE
			slIdentifiers
			{
			}
		|
			SL_IDENTIFIER_VALUE
			{
			}
			;

			// Variable init expression
slVariableInit:
			SL_EQUAL
			slAritmeticExpression
			{
			}
		|
			{
			}
			;
			
			// Variable declaration
slVariableDecl:
			slTypeDecl
			slIdentifiers
			slArrayDecl
			slVariableInit
			{
			}
		
		
		
		
		
			
		////////////////////////////////////////////////
		//
		// Shader file description:
		// Arbitrary number of functions followed by a 
		// shader body. I may need to change this layout if
		// I want to enable individual functions be defined
		// and used from different shader bodies
		//
		////////////////////////////////////////////////
slShader:		
		slFunction					// Normally slFunction shouldn't have any code associated with it
		slShader					// Recursion
		{
		}
	|
		slMain						// The main shader code
		{
		}
		;


		////////////////////////////////////////////////
		//
		// A function decleration
		//
		////////////////////////////////////////////////
slFunction:
		slTypeDecl											// The return type
		SL_IDENTIFIER_VALUE									// The function name
		SL_OPEN_PARANTHESIS	
		slFunctionParameters								// List of function parameters
		SL_CLOSE_PARANTHESIS
		slBlock												// The function body
		{
		}
		;
		

		////////////////////////////////////////////////
		// Function parameters
slFunctionParameters:
		slVariableDecl
		SL_SEMI_COLON 
		slFunctionParameters
		{
		}
	|
		{
		}
		;

		////////////////////////////////////////////////
		//
		// Main shader body definition
		//
slMain:	slShaderType							// Type of the shader
		SL_IDENTIFIER_VALUE						// Name of the shader
		SL_OPEN_PARANTHESIS
		slShaderParameters						// Shader Parameter list
		SL_CLOSE_PARANTHESIS
		slBlock
		{
		}
		;

		////////////////////////////////////////////////
		// Shader type
slShaderType:	
		SL_SURFACE
		{
		}
	|
		SL_DISPLACEMENT
		{
		}
	|
		SL_LIGHT
		{
		}
	|
		SL_VOLUME
		{
		}
	|
		SL_TRANSFORMATION
		{
		}
	|
		SL_IMAGER
		{
		}
		;


		////////////////////////////////////////////////
		// Shader Parameters
slShaderParameters:
		slVariableDecl 
		SL_SEMI_COLON
		slShaderParameters
		{
		}
	|
		{
		}
		;

		
		////////////////////////////////////////////////
		// A block
slBlock:
		SL_OPEN_CRL_PARANTHESIS
		slStatements
		SL_CLOSE_CRL_PARANTHESIS
		{
		}
		;

		////////////////////////////////////////////////
		// A general statement
slStatement:
		slUnmatchedStatement
		{
		}
	|
		slMatchedStatement
		{
		}
	|
		error
		{
		}
		;

slStatements:
		slStatements
		{
		}
		slStatement
		{
		}
	|
		{
		}
		;


		////////////////////////////////////////////////
		// A Matched statement
slMatchedStatement:
		slForStatement
		{
		}
	|
		slWhileStatement
		{
		}
	|
		slMatchedIfStatement
		{
		}
	|
		slMatchedGatherStatement
		{
		}
	|
		slAssignmentStatement SL_SEMI_COLON
		{
		}
	|
		slUpdateStatement SL_SEMI_COLON
		{
		}
	|
		slBreakStatement 
		{
		}
	|
		slContinueStatement 
		{
		}
	|
		slReturnStatement
		{
		}
	|	
		slIlluminanceStatement
		{
		}
	|
		slIlluminateStatement
		{
		}
	|
		slSolarStatement
		{
		}
	|
		slBlock
		{
		}
	|
		slVariableDeclerations
		{
		}
	|
		slFunction
		{
		}
	|
		slFunctionCall SL_SEMI_COLON
		{
		}
	|
		SL_SEMI_COLON
		{
		}
		;

		////////////////////////////////////////////////
		// Unmatched shatement
slUnmatchedStatement:
		slUnmatchedIfStatement
		{
		}
	|
		slUnmatchedGatherStatement
		{
		}
	|
		slUnmatchedWhileStatement
		{
		}
	|
		slUnmatchedForStatement
		{
		}
	|
		slUnmatchedIlluminanceStatement
		{
		}
	|
		slUnmatchedIlluminateStatement
		{
		}
	|
		slUnmatchedSolarStatement
		{
		}
		;

		////////////////////////////////////////////////
		// Break statement
slBreakStatement:
		SL_BREAK SL_FLOAT_VALUE SL_SEMI_COLON
		{
		}
	|
		SL_BREAK SL_SEMI_COLON
		{
		}
		;

		////////////////////////////////////////////////
		// Continue statement
slContinueStatement:
		SL_CONTINUE SL_FLOAT_VALUE SL_SEMI_COLON
		{
		}
	|
		SL_CONTINUE SL_SEMI_COLON
		{
		}
		;

		////////////////////////////////////////////////
		// Return statement
slReturnStatement:
		SL_RETURN slAritmeticExpression SL_SEMI_COLON
		{
		}
	|
		SL_RETURN SL_SEMI_COLON
		{
		}
		;
		

		////////////////////////////////////////////////
		// While statement
slWhileStartStatement:
		SL_WHILE
		SL_OPEN_PARANTHESIS
		slAritmeticExpression
		SL_CLOSE_PARANTHESIS
		{
		}
		;


slWhileStatement:
		slWhileStartStatement
		slMatchedStatement
		{
		}
		;

slUnmatchedWhileStatement:
		slWhileStartStatement
		slUnmatchedStatement
		{
		}
		;

		////////////////////////////////////////////////
		// A general assignment statement
slAssignmentStatement:
		SL_IDENTIFIER_VALUE
		SL_EQUAL
		slAritmeticExpression
		{
		}
		|
		SL_IDENTIFIER_VALUE
		SL_OPEN_SQR_PARANTHESIS
		slAritmeticExpression
		SL_CLOSE_SQR_PARANTHESIS
		SL_EQUAL
		slAritmeticExpression
		{
		}
		;

		////////////////////////////////////////////////
		// A general assignment statement
slUpdateStatement:
		SL_IDENTIFIER_VALUE
		SL_INCREMENT_BY
		slAritmeticExpression
		{
		}
		|
		SL_IDENTIFIER_VALUE
		SL_DECREMENT_BY
		slAritmeticExpression
		{
		}
		|
		SL_IDENTIFIER_VALUE
		SL_INCREMENT
		{
		}
		|
		SL_IDENTIFIER_VALUE
		SL_DECREMENT
		{
		}
		|
		SL_IDENTIFIER_VALUE
		SL_MULTIPLY_BY
		slAritmeticExpression
		{
		}
		|
		SL_IDENTIFIER_VALUE
		SL_DIVIDE_BY
		slAritmeticExpression
		{
		}
		|
		SL_IDENTIFIER_VALUE
		SL_OPEN_SQR_PARANTHESIS
		slAritmeticExpression
		SL_CLOSE_SQR_PARANTHESIS
		SL_INCREMENT_BY
		slAritmeticExpression
		{
		}
		|
		SL_IDENTIFIER_VALUE
		SL_OPEN_SQR_PARANTHESIS
		slAritmeticExpression
		SL_CLOSE_SQR_PARANTHESIS
		SL_DECREMENT_BY
		slAritmeticExpression
		{
		}
		|
		SL_IDENTIFIER_VALUE
		SL_OPEN_SQR_PARANTHESIS
		slAritmeticExpression
		SL_CLOSE_SQR_PARANTHESIS
		SL_INCREMENT
		{
		}
		|
		SL_IDENTIFIER_VALUE
		SL_OPEN_SQR_PARANTHESIS
		slAritmeticExpression
		SL_CLOSE_SQR_PARANTHESIS
		SL_DECREMENT
		{
		}
		|
		SL_IDENTIFIER_VALUE
		SL_OPEN_SQR_PARANTHESIS
		slAritmeticExpression
		SL_CLOSE_SQR_PARANTHESIS
		SL_MULTIPLY_BY
		slAritmeticExpression
		{
		}
		|
		SL_IDENTIFIER_VALUE
		SL_OPEN_SQR_PARANTHESIS
		slAritmeticExpression
		SL_CLOSE_SQR_PARANTHESIS
		SL_DIVIDE_BY
		slAritmeticExpression
		{
		}
		;

		////////////////////////////////////////////////
		// A general for statement
slForStartStatement:
		SL_FOR
		{
		}
		;

slForStatement:
		slForStartStatement
		SL_OPEN_PARANTHESIS
		slForInitStatement
		SL_SEMI_COLON
		slForCheckStatement
		SL_SEMI_COLON
		slForIncrementStatement
		SL_CLOSE_PARANTHESIS
		slMatchedStatement
		{
		}
		;

slUnmatchedForStatement:
		slForStartStatement
		SL_OPEN_PARANTHESIS
		slForInitStatement
		SL_SEMI_COLON
		slForCheckStatement
		SL_SEMI_COLON
		slForIncrementStatement
		SL_CLOSE_PARANTHESIS
		slUnmatchedStatement
		{
		}
		;

		////////////////////////////////////////////////
		// For init statement list
slForInitStatement:
		slForInitStatements
		{
		}
	|
		{
		}
		;

		////////////////////////////////////////////////
		// For init statements
slForInitStatements:
		slAssignmentStatement
		SL_COMMA
		slForInitStatements
		{
		}
	|
		slAssignmentStatement
		{
		}
		;

		////////////////////////////////////////////////
		// For check statement
slForCheckStatement:
		slAritmeticExpression
		{
		}
	|
		{
		}
		;

		////////////////////////////////////////////////
		// For increment statement list
slForIncrementStatement:
		slForIncrementStatements
		{
		}
	|
		{
		}
		;

		////////////////////////////////////////////////
		// For increment statements
slForIncrementStatements:
		slAssignmentStatement
		SL_COMMA
		slForIncrementStatements
		{
		}
	|
		slAssignmentStatement
		{
		}
	|
		slUpdateStatement
		SL_COMMA
		slForIncrementStatements
		{
		}
	|
		slUpdateStatement
		{
		}
		;

		////////////////////////////////////////////////
		// Matched if statement
slMatchedIfStatement:
		SL_IF
		SL_OPEN_PARANTHESIS
		slAritmeticExpression
		SL_CLOSE_PARANTHESIS
		slMatchedStatement
		SL_ELSE
		slMatchedStatement
		{
		}
		;

		////////////////////////////////////////////////
		// Unmatched if statement
slUnmatchedIfStatement:
		SL_IF
		SL_OPEN_PARANTHESIS
		slAritmeticExpression
		SL_CLOSE_PARANTHESIS
		slStatement
		{
		}
	|
		SL_IF
		SL_OPEN_PARANTHESIS
		slAritmeticExpression
		SL_CLOSE_PARANTHESIS
		slMatchedStatement
		SL_ELSE
		slUnmatchedStatement
		{
		}
		;



		////////////////////////////////////////////////
		// Gather parameter list
slGatherParameterList:
		slGatherParameterList
		SL_COMMA
		slAritmeticExpression
		{
		}
		|
		slAritmeticExpression
		{
		}
		;

slGatherHeader:
		SL_GATHER
		SL_OPEN_PARANTHESIS
		{
		}
		slGatherParameterList
		SL_CLOSE_PARANTHESIS
		{
		}
		;

		////////////////////////////////////////////////
		// Matched if statement
slMatchedGatherStatement:
		slGatherHeader
		slMatchedStatement
		SL_ELSE
		slMatchedStatement
		{
		}
		;

		////////////////////////////////////////////////
		// Unmatched if statement
slUnmatchedGatherStatement:
		slGatherHeader
		slStatement
		{
		}
	|
		slGatherHeader
		slMatchedStatement
		SL_ELSE
		slUnmatchedStatement
		{
		}
		;

		////////////////////////////////////////////////
		// Illuminance statement
slIlluminanceStartStatement:
		SL_ILLUMINANCE
		{
		}

slIlluminanceStatement:
		slIlluminanceStartStatement
		SL_OPEN_PARANTHESIS
		slAritmeticExpression
		SL_CLOSE_PARANTHESIS
		slMatchedStatement
		{
		}
	|
		slIlluminanceStartStatement
		SL_OPEN_PARANTHESIS
		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		SL_CLOSE_PARANTHESIS
		slMatchedStatement
		{
		}
	|
		slIlluminanceStartStatement
		SL_OPEN_PARANTHESIS
   		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		SL_CLOSE_PARANTHESIS
		slMatchedStatement
		{
		}
	|
		slIlluminanceStartStatement
		SL_OPEN_PARANTHESIS
		slAritmeticExpression
		SL_COMMA
   		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		SL_CLOSE_PARANTHESIS
		slMatchedStatement
		{
		}
		;

slUnmatchedIlluminanceStatement:
		slIlluminanceStartStatement
		SL_OPEN_PARANTHESIS
		slAritmeticExpression
		SL_CLOSE_PARANTHESIS
		slUnmatchedStatement
		{
		}
	|
		slIlluminanceStartStatement
		SL_OPEN_PARANTHESIS
		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		SL_CLOSE_PARANTHESIS
		slUnmatchedStatement
		{
		}
	|
		slIlluminanceStartStatement
		SL_OPEN_PARANTHESIS
		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		SL_CLOSE_PARANTHESIS
		slUnmatchedStatement
		{
		}
	|
		slIlluminanceStartStatement
		SL_OPEN_PARANTHESIS
		slAritmeticExpression
		SL_COMMA
   		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		SL_CLOSE_PARANTHESIS
		slUnmatchedStatement
		{
		}
		;

		////////////////////////////////////////////////
		// Illuminate statement
slIlluminateStatement:
		SL_ILLUMINATE
		SL_OPEN_PARANTHESIS
		slAritmeticExpression
		SL_CLOSE_PARANTHESIS
		slMatchedStatement
		{
		}
	|
		SL_ILLUMINATE
		SL_OPEN_PARANTHESIS
		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		SL_CLOSE_PARANTHESIS
		slMatchedStatement
		{
		}
		;

slUnmatchedIlluminateStatement:
		SL_ILLUMINATE
		SL_OPEN_PARANTHESIS
		slAritmeticExpression
		SL_CLOSE_PARANTHESIS
		slUnmatchedStatement
		{
		}
	|
		SL_ILLUMINATE
		SL_OPEN_PARANTHESIS
		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		SL_CLOSE_PARANTHESIS
		slUnmatchedStatement
		{
		}
		;

		////////////////////////////////////////////////
		// Solar statement
slSolarStatement:
		SL_SOLAR
		SL_OPEN_PARANTHESIS
		SL_CLOSE_PARANTHESIS
		slMatchedStatement
		{
		}
	|
		SL_SOLAR
		SL_OPEN_PARANTHESIS
		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		SL_CLOSE_PARANTHESIS
		slMatchedStatement
		{
		}
		;

slUnmatchedSolarStatement:
		SL_SOLAR
		SL_OPEN_PARANTHESIS
		SL_CLOSE_PARANTHESIS
		slUnmatchedStatement
		{
		}
	|
		SL_SOLAR
		SL_OPEN_PARANTHESIS
		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		SL_CLOSE_PARANTHESIS
		slUnmatchedStatement
		{
		}
		;

		////////////////////////////////////////////////
		// Aritmetic expression
slAritmeticExpression:
		slAritmeticTerminalValue
		{
		}
	|
		slAritmeticExpression
		SL_PLUS
		slAritmeticExpression
		{
		}
	|
		slAritmeticExpression
		SL_MINUS
		slAritmeticExpression
		{
		}
	|
		slAritmeticExpression
		SL_MULTIPLY
		slAritmeticExpression
		{
		}
	|
		slAritmeticExpression
		SL_DIVIDE
		slAritmeticExpression
		{
		}
	|
		slAritmeticExpression
		SL_DOT
		{
		}
		slAritmeticExpression
		{
		}
	|
		slAritmeticExpression
		SL_CROSS
		{
		}
		slAritmeticExpression
		{
		}
	|
		SL_PLUS
		slAritmeticExpression
		{
		}
	|
		SL_MINUS
		slAritmeticExpression
		{
		}
	|
		slAritmeticExpression
		SL_QUESTION
		slAritmeticExpression
		SL_COLON
		slAritmeticExpression
		{
		}
	|
		slAritmeticExpression
		SL_AND
		slAritmeticExpression
		{
		}
	|
		slAritmeticExpression
		SL_OR
		slAritmeticExpression
		{
		}
	|
		slAritmeticExpression
		SL_COMP_GREATER
		slAritmeticExpression
		{
		}
	|
		slAritmeticExpression
		SL_COMP_LESS
		slAritmeticExpression
		{
		}
	|
		slAritmeticExpression
		SL_COMP_GREATER_EQUAL
		slAritmeticExpression
		{
		}
	|
		slAritmeticExpression
		SL_COMP_LESS_EQUAL
		slAritmeticExpression
		{
		}
	|
		slAritmeticExpression
		SL_COMP_EQUAL
		slAritmeticExpression
		{
		}
	|
		slAritmeticExpression
		SL_COMP_DIFFERENT
		slAritmeticExpression
		{
		}
	|
		SL_NOT
		slAritmeticExpression
		{
		}
		;

slArrayList:
		SL_OPEN_CRL_PARANTHESIS
		slArrayItems
		SL_CLOSE_CRL_PARANTHESIS
		{
		}
		;

slArrayItems:
		slAritmeticExpression
		SL_COMMA
		slArrayItems
		{
		}
		|
		slAritmeticExpression
		{
		}
		;

slAritmeticTerminalValue:
		SL_FCN_PI
		{
		}
	|
		slAssignmentStatement
		{
		}
	|
		slUpdateStatement
		{
		}
	|
		slAritmeticTypeCast
		{
		}
	|
		slFunctionCall
		{
		}
	|
		slTypeDecl
		slFunctionCall
		{
		}
	|
		slTypeDecl
		SL_TEXT_VALUE
		slFunctionCall
		{
		}
	|
		SL_IDENTIFIER_VALUE
		{
		}
	|
		slTypeDecl
		SL_IDENTIFIER_VALUE
		{
		}
	|
		SL_IDENTIFIER_VALUE
		SL_OPEN_SQR_PARANTHESIS
		slAritmeticExpression
		SL_CLOSE_SQR_PARANTHESIS
		{
		}
	|
		SL_FLOAT_VALUE
		{
		}
	|
		SL_TEXT_VALUE
		{
		}
	|
		SL_OPEN_PARANTHESIS
		slAritmeticExpression
		SL_CLOSE_PARANTHESIS
		{	
		}
		;
	


slAritmeticTypeCast:
		slTypeDecl
		SL_TEXT_VALUE
		{
		}
		slVectorMatrixExpression
		{
		}
	|
		slTypeDecl
		{
		}
		slVectorMatrixExpression
		{
		}
	|
		slTypeDecl
		{
		}
		SL_FLOAT_VALUE
		{
		}
	|
		slVectorMatrixExpression
		{
		}
		;
		
slVectorMatrixExpression:
		SL_OPEN_PARANTHESIS
		slVMExpression
		SL_CLOSE_PARANTHESIS
		{
		}
		;
	
		
slVMExpression:
		slAritmeticExpression
		{
		}
	|
		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		{
		}
	|
		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		{
		}
		
		////////////////////////////////////////////////
		// A CFunction call


		
slFunctionCall:
		slTextureCall
		{
		}
		|
		slFunCall
		{
		}
		;

	

slFunCallHeader:
		SL_IDENTIFIER_VALUE
		SL_OPEN_PARANTHESIS
		{
		}
		|
		SL_SURFACE
		SL_OPEN_PARANTHESIS
		{
		}
		|
		SL_DISPLACEMENT
		SL_OPEN_PARANTHESIS
		{
		}
		;

slFunCall:
		slFunCallHeader
		slFunctionCallParameterList
		SL_CLOSE_PARANTHESIS
		{
		}
		;


		// Either text of value
slTextureNameSpecifier:
		SL_TEXT_VALUE
		{
		}
		|
		SL_IDENTIFIER_VALUE
		{
		}
		;


slTextureChannelSpecifier:
		SL_OPEN_SQR_PARANTHESIS
		slAritmeticExpression
		SL_CLOSE_SQR_PARANTHESIS
		{
		}
		|
		{
		}
		;

		// There are 4 cases
		//	texture(textureIdentifier,...)
		//	texture("textureName",...)
		//	texture(textureIdentifier[channelIdentifier],...)
		//	texture("textureName"[channelIdentifier],...)
slTextureCall:
		slTextureName
		SL_OPEN_PARANTHESIS
		slTextureNameSpecifier
		slTextureChannelSpecifier
		SL_COMMA
		slFunctionCallParameterList
		SL_CLOSE_PARANTHESIS
		{
		}
		|
		slTextureName
		SL_OPEN_PARANTHESIS
		slTextureNameSpecifier
		slTextureChannelSpecifier
		SL_CLOSE_PARANTHESIS
		{
		}
		;

slTextureName:
		SL_TEXTURE
		{
		}
		|
		SL_SHADOW
		{
		}
		|
		SL_ENVIRONMENT
		{
		}
		|
		SL_BUMP
		{
		}
		;

		////////////////////////////////////////////////
		// CFunction Parameters
slFunctionCallParameterList:
		slFunctionCallParameters
		{
		}
	|
		{
		}
		;

slFunctionCallParameters:
		slAritmeticExpression
		SL_COMMA
		{
		}
		slFunctionCallParameters
		{
		}
	|
		slAritmeticExpression
		{
		}
		;

%%

static	int		lineNo		=	0;
static	char	*sourceFile	=	NULL;

#include	"lex.sl.cpp"



void	compile(FILE *in,char *outName) {

	slin	=	in;

	slparse();
}


void	yyerror(char *mes) {
}

