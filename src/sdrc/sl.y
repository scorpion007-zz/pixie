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
#include	"opcodes.h"
#include	"sdr.h"

	void				yyerror(const char *);			// Forward definition for stupid yacc
	int					yylex(void );					// Forward definition for stupid yacc
														
//////////////////////////////////////////////////////////////////////////
// Here's the only global CVariable
//////////////////////////////////////////////////////////////////////////
	CScriptContext		*sdr;
	
// This macro can be used to record the last parsed line number for accurate error reporting
#define	checkPoint()	sdr->statementLineNo	=	sdr->lineNo

//////////////////////////////////////////////////////////////////////////


%}
%union {
  const char			*string;
  CExpression			*code;
  float					real;
  int					integer;
  CList<CExpression *>	*array;
}
//////////////////////////////////////////////////////////////////////////
// Token definitions
//////////////////////////////////////////////////////////////////////////
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
%right			SL_MULTIPLY_BY SL_DIVIDE_BY

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
%start	slStart

// Rule types
%type<integer>		slTypeDecl
%type<integer>		slInheritanceClass
%type<integer>		slOutputClass
%type<integer>		slContainerClass
%type<integer>		slFloatSpecifier
%type<integer>		slVectorSpecifier
%type<integer>		slMatrixSpecifier
%type<integer>		slStringSpecifier
%type<integer>		slTypeSpecifier
%type<real>			slFloatValue
%type<code>			slFunctionParameters
%type<code>			slFunctionParameter
%type<code>			slFunctionParameterIdentifierList
%type<integer>		slShaderType
%type<code>			slShaderParameters
%type<code>			slShaderParameter
%type<code>			slShaderParameterInitializer
%type<code>			slShaderParameterIdentifierToken
%type<code>			slShaderParameterIdentifierList
%type<code>			slBlock
%type<code>			slVariableInitializer
%type<code>			slVariableDeclarations
%type<code>			slVariableIdentifierList
%type<code>			slVariableIdentifierTail
%type<code>			slStatement
%type<code>			slStatements
%type<code>			slMatchedStatement
%type<code>			slUnmatchedStatement
%type<code>			slBreakStatement
%type<code>			slContinueStatement
%type<code>			slReturnStatement
%type<code>			slWhileStartStatement
%type<code>			slWhileStatement
%type<code>			slUnmatchedWhileStatement
%type<code>			slAssignmentStatement
%type<code>			slUpdateStatement
%type<code>			slForStatement
%type<code>			slUnmatchedForStatement
%type<code>			slForInitStatement
%type<code>			slForInitStatements
%type<code>			slForCheckStatement
%type<code>			slForIncrementStatement
%type<code>			slForIncrementStatements
%type<code>			slMatchedIfStatement
%type<code>			slUnmatchedIfStatement
%type<array>		slGatherParameterList
%type<array>		slGatherHeader
%type<code>			slMatchedGatherStatement
%type<code>			slUnmatchedGatherStatement
%type<code>			slIlluminanceStatement
%type<code>			slUnmatchedIlluminanceStatement
%type<code>			slIlluminateStatement
%type<code>			slUnmatchedIlluminateStatement
%type<code>			slSolarStatement
%type<code>			slUnmatchedSolarStatement
%type<array>		slArrayItems
%type<array>		slArrayList
%type<code>			slAritmeticExpression
%type<code>			slAritmeticTerminalValue
%type<code>			slAritmeticTypeCast
%type<code>			slVectorMatrixExpression
%type<code>			slVMExpression
%type<code>			slFunctionCall
%type<code>			slFunctionCallParameters
%type<string>		slFunCallHeader
%type<code>			slFunCall
%type<string>		slTextureName
%type<string>		slTextureCall
%type<code>			slTextureNameSpecifier
%type<code>			slTextureChannelSpecifier
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

slContainerClass:
			SL_UNIFORM
			{
				$$	=	SLC_UNIFORM;
			}
			|
			SL_VARIABLE
			{
				$$	=	SLC_VARYING;
			}
			|
			{
				$$	=	0;
			}
			;


slInheritanceClass:
			SL_EXTERN
			{
				$$	=	SLC_EXTERN;
			}
			|
			{
				$$	=	0;
			}
			;

slOutputClass:
			SL_OUTPUT
			{
				$$	=	SLC_OUTPUT;
			}
			|
			{
				$$	=	0;
			}
			;

slFloatSpecifier:
			SL_FLOAT
			{
				$$	=	SLC_FLOAT;
			}
			;
			
slVectorSpecifier:
			SL_COLOR
			{
				$$	=	SLC_VECTOR | SLC_VCOLOR;
			}
			|
			SL_VECTOR
			{
				$$	=	SLC_VECTOR | SLC_VVECTOR;
			}
			|
			SL_NORMAL
			{
				$$	=	SLC_VECTOR | SLC_VNORMAL;
			}
			|
			SL_POINT
			{
				$$	=	SLC_VECTOR | SLC_VPOINT;
			}
			;
			
slMatrixSpecifier:
			SL_MATRIX
			{
				$$	=	SLC_MATRIX;
			}
			;
			
slStringSpecifier:
			SL_STRING
			{
				$$	=	SLC_STRING | SLC_UNIFORM;
			}
			;
			
			
			
slTypeSpecifier:
			slFloatSpecifier
			{
				$$	=	$1;
			}
		|
			slVectorSpecifier
			{
				$$	=	$1;
			}
		|
			slMatrixSpecifier
			{
				$$	=	$1;
			}
		|
			slStringSpecifier
			{
				$$	=	$1;
			}
			;
			
slFloatValue:	slAritmeticExpression
			{
				$$	=	0;
				
				// Is this a float type?
				if ($1->type & SLC_FLOAT) {
					char	tmp[256];
					
					// Is this a simple expression?
					if ($1->value(tmp)) {
					
						// Yes, convert it to float
						$$	=	(float) atof(tmp);
					} else
						sdr->error("Expecting a simple float argument\n");
				} else
					sdr->error("Expecting a float argument\n");
			}
			;

slTypeDecl:
			slInheritanceClass
			slOutputClass
			slContainerClass
			slTypeSpecifier
			{
				$$	=	$1 | $2 | $3 | $4;
				sdr->desire($$);
				checkPoint();
			}
			;

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
		slMainOrFunction
		| 
		slShader slMainOrFunction
		;

slMainOrFunction:
		slMain | slFunction	;

		////////////////////////////////////////////////
		//
		// A function declaration:
		// slFunctionReturnType <CFunction_name> (
		// slFunctionParameterList ) slBlock 
		// 
		//
		////////////////////////////////////////////////
slFunctionHeader:
		slTypeDecl
		SL_IDENTIFIER_VALUE									// Name of the Function
		SL_OPEN_PARANTHESIS
		{
			CFunction	*thisFunction	=	sdr->newFunction($2);
			
			if ($1 & (SLC_OUTPUT | SLC_EXTERN | SLC_RDONLY)) {
				sdr->error("Invalid return type for function %s\n",$2);
				$1	&=	~(SLC_OUTPUT | SLC_EXTERN | SLC_RDONLY);
			}

			thisFunction->returnValue	=	new CParameter($2,$1,1);

			sdr->undesire();
			checkPoint();
		}
		|
		SL_VOID
		SL_IDENTIFIER_VALUE									// Name of the CFunction
		SL_OPEN_PARANTHESIS
		{
			CFunction	*thisFunction	=	sdr->newFunction($2);
			
			thisFunction->returnValue	=	NULL;
			checkPoint();
		}
		;

slFunction:
		slFunctionHeader
		slFunctionParameters							// CFunction Parameter list
		SL_CLOSE_PARANTHESIS
		slBlock
		{
			CFunction	*cFun		=	sdr->popFunction();

			cFun->initExpression	=	$2;
			cFun->code				=	$4;

			if (cFun->returnValue != NULL)
				if (cFun->returnValueGiven == FALSE) 
					sdr->error("Return value not given for %s\n",cFun->symbolName);

			checkPoint();
		}
		;
		

		////////////////////////////////////////////////
		// CFunction Parameters
		// No default Parameters
slFunctionParameters:
		slFunctionParameter								// Semi colon seperated
		SL_SEMI_COLON 
		slFunctionParameters
		{
			$$	=	new CTwoExpressions($1,$3);
			checkPoint();
		}
	|
		slFunctionParameter
		{
			$$	=	$1;
			checkPoint();
		}
		;

		////////////////////////////////////////////////
		// A single parameter definition
slFunctionParameter:
		slTypeDecl
		{
			int	type	=	sdr->desired();

			if (type & (SLC_EXTERN)) {
				sdr->error("Invalid parameter type\n");
				type	&=	~(SLC_EXTERN);
			}

			if (type & SLC_OUTPUT) {
				sdr->undesire();
				sdr->desire(type);					// Make sure we mark the desired type as READ-ONLY
			} else {
				sdr->undesire();
				sdr->desire(type | SLC_RDONLY);		// Make sure we mark the desired type as READ-ONLY
			}
		} 
		slFunctionParameterIdentifierList
		{
			$$					=	$3;
			sdr->undesire();						// We're done with the type
		}
		|
		{
			$$	=	new CNullExpression;
		}
		;

		////////////////////////////////////////////////
		// An identifier list for CFunction Parameters
slFunctionParameterIdentifierList:
		SL_IDENTIFIER_VALUE							// Default Parameter values are not supported yet
		{
			sdr->newParameter($1,sdr->desired(),1);	// Add the Parameter to the current CFunction
		}
		SL_COMMA
		slFunctionParameterIdentifierList
		{
			$$	=	$4;
		}
	|
		SL_IDENTIFIER_VALUE
		{
			sdr->newParameter($1,sdr->desired(),1);
	
			$$			=	new CNullExpression;
		}
	|
		SL_IDENTIFIER_VALUE
		SL_OPEN_SQR_PARANTHESIS
		SL_CLOSE_SQR_PARANTHESIS
		{
			sdr->newParameter($1,sdr->desired() | SLC_ARRAY,-1);
		}
		SL_COMMA
		slFunctionParameterIdentifierList
		{
			$$	=	$6;
		}
	|
		SL_IDENTIFIER_VALUE
		SL_OPEN_SQR_PARANTHESIS
		slFloatValue
		SL_CLOSE_SQR_PARANTHESIS
		{
			CParameter	*cParameter	=	sdr->newParameter($1,sdr->desired() | SLC_ARRAY, (int) $3);			
		}
		SL_COMMA
		slFunctionParameterIdentifierList
		{
			$$	=	$7;
		}
	|
		SL_IDENTIFIER_VALUE
		SL_OPEN_SQR_PARANTHESIS
		SL_CLOSE_SQR_PARANTHESIS
		{
			sdr->newParameter($1,sdr->desired() | SLC_ARRAY, 1);
			
			$$	=	new CNullExpression;
		}
	|
		SL_IDENTIFIER_VALUE
		SL_OPEN_SQR_PARANTHESIS
		slFloatValue
		SL_CLOSE_SQR_PARANTHESIS
		{
			CParameter	*cParameter	=	sdr->newParameter($1,sdr->desired() | SLC_ARRAY, (int) $3);
			
			$$	=	new CNullExpression;
		}
		;

		////////////////////////////////////////////////
		//
		// Main shader body definition
		//
slMain:	slShaderType							// Type of the shader
		SL_IDENTIFIER_VALUE						// Name of the shader
		SL_OPEN_PARANTHESIS
		{
			if (sdr->shaderType) {
				sdr->error("Shader file contains multiple shaders\n");
				sdr->lastFunction			=	sdr->shaderFunction;
			} else {
				CFunction		*mainFunction	=	sdr->newFunction(constantShaderMain);

				mainFunction->returnValue		=	NULL;

				sdr->shaderName				=	strdup($2);
				sdr->shaderType				=	$1;
				sdr->shaderFunction			=	mainFunction;
				sdr->lastFunction			=	mainFunction;
			}
		}
		slShaderParameters						// Shader Parameter list
		SL_CLOSE_PARANTHESIS
		{
			sdr->restoreParameters();
		}
		slBlock
		{
			CFunction	*cFun			=	sdr->popFunction();

			for (CParameter	*cParameter=cFun->parameters->first();cParameter!=NULL;cParameter=cFun->parameters->next()) {
				sdr->variables->push(cParameter);
			}

			cFun->initExpression	=	$5;
			cFun->code				=	$8;
		}
		;

		////////////////////////////////////////////////
		// Shader type
slShaderType:	SL_SURFACE
		{
			$$	=	SLC_SURFACE;
		}
	|
		SL_DISPLACEMENT
		{
			$$	=	SLC_DISPLACEMENT;
		}
	|
		SL_LIGHT
		{
			$$	=	SLC_LIGHT;
		}
	|
		SL_VOLUME
		{
			$$	=	SLC_VOLUME;
		}
	|
		SL_TRANSFORMATION
		{
			$$	=	SLC_TRANSFORMATION;
		}
	|
		SL_IMAGER
		{
			$$	=	SLC_IMAGER;
		}
		;


		////////////////////////////////////////////////
		// Shader Parameters
slShaderParameters:
		slShaderParameter 
		SL_SEMI_COLON
		slShaderParameters
		{
			$$	=	new CTwoExpressions($1,$3);
		}
	|
		slShaderParameter
		{
			$$	=	$1;
		}
		;

		/////////////////////////////////////////////////
		// A single shader Parameter
slShaderParameter:
		slTypeDecl
		{
			int	type	=	$1;

			// Inside the shader param declarations, params
			// are uniform by default
			if (type & SLC_VARYING) {
				// clear this marker, only used to invert the
				// default from varying to uniform
				type &= ~SLC_VARYING;
			} else {	 
				type |= SLC_UNIFORM;	 
			}
			
			sdr->undesire();
			sdr->desire(type);
		}
		slShaderParameterIdentifierList
		{
			$$	=	$3;
		
			if ($1 & (SLC_EXTERN)) {
				sdr->error("Invalid parameter type for the shader\n");
			}

			sdr->undesire();
		}
		|
		{
			$$	=	new CNullExpression;
		}
		;

		////////////////////////////////////////////////
		// Shader Parameter initializer
slShaderParameterInitializer:
		SL_EQUAL
		slAritmeticExpression
		{
			$$	=	getAssignment(sdr->variableList,$2);
		}
		|
		SL_EQUAL
		slArrayList
		{
			$$	=	getAssignment(sdr->variableList,$2);
		}
		;


slShaderParameterIdentifierToken:
		SL_IDENTIFIER_VALUE
		SL_COMMA
		{
			CParameter	*cParameter	=	sdr->newParameter($1,sdr->desired() | SLC_PARAMETER,1);

			sdr->variableList->push(cParameter);	// Save the parameter so that we can generate init code later
		}
		slShaderParameterIdentifierToken
		{
			$$	=	$4;
		}
	|
		SL_IDENTIFIER_VALUE
		{
			CParameter	*cParameter	=	sdr->newParameter($1,sdr->desired() | SLC_PARAMETER,1);

			sdr->variableList->push(cParameter);
		}
		slShaderParameterInitializer
		{
			$$	=	$3;
		}
	|
		SL_IDENTIFIER_VALUE
		SL_OPEN_SQR_PARANTHESIS
		slFloatValue
		SL_CLOSE_SQR_PARANTHESIS
		SL_COMMA
		{
			CParameter	*cParameter	=	sdr->newParameter($1,sdr->desired() | SLC_PARAMETER | SLC_ARRAY,(int) $3);

			sdr->variableList->push(cParameter);
		}
		slShaderParameterIdentifierToken
		{
			$$	=	$7;
		}
	|
		SL_IDENTIFIER_VALUE
		SL_OPEN_SQR_PARANTHESIS
		slFloatValue
		SL_CLOSE_SQR_PARANTHESIS
		{
			CParameter	*cParameter	=	sdr->newParameter($1,sdr->desired() | SLC_PARAMETER | SLC_ARRAY,(int) $3);

			sdr->variableList->push(cParameter);
		}
		slShaderParameterInitializer
		{
			$$	=	$6;
		}

	|
		{
			$$	=	new CNullExpression;
		}

		;

slShaderParameterIdentifierList:
		slShaderParameterIdentifierToken
		{
			$$	=	$1;
		}
	|
		slShaderParameterIdentifierToken
		SL_COMMA
		slShaderParameterIdentifierList
		{
			$$	=	new CTwoExpressions($1,$3);
		}
	;

		
		////////////////////////////////////////////////
		// A block
slBlock:
		SL_OPEN_CRL_PARANTHESIS
		{
			CFunction	*cFun	=	sdr->newFunction(constantBlockName);
		}
		slStatements
		SL_CLOSE_CRL_PARANTHESIS
		{
			CFunction	*cFun	=	sdr->popFunction();

			cFun->code			=	$3;

			$$					=	new	CFuncallExpression(cFun,NULL);
		}
		;

		////////////////////////////////////////////////
		// A statement
		////////////////////////////////////////////////
		// Variable declarations in a block
slVariableDeclarations:
		slTypeDecl
		slVariableIdentifierList
		{
			CVariable	*cVar;

			if ($1 & (SLC_OUTPUT | SLC_RDONLY)) {
				sdr->error("Invalid container class for local variables\n");
			}

			// Remove the uninitialized variables from the list
			while((cVar = (CVariable *) sdr->variableList->pop()) != NULL);

			sdr->undesire();

			$$	=	$2;
		}
		;

		////////////////////////////////////////////////
		// Variable identifier list
slVariableInitializer:
		SL_EQUAL
		slAritmeticExpression
		{
			$$	=	getAssignment(sdr->variableList,$2);
		}
		|
		SL_EQUAL
		slArrayList
		{
			$$	=	getAssignment(sdr->variableList,$2);
		}
		;

slVariableIdentifierList:
		SL_IDENTIFIER_VALUE
		{
			CVariable	*cVar	=	sdr->newVariable($1,sdr->desired(),1);

			sdr->variableList->push(cVar);
		}
		slVariableIdentifierTail
		{
			$$	=	$3;
		}
	|
		SL_IDENTIFIER_VALUE
		{
			CVariable	*cVar	=	sdr->newVariable($1,sdr->desired(),1);

			sdr->variableList->push(cVar);
		}
		slVariableInitializer
		slVariableIdentifierTail
		{
			$$	=	new CTwoExpressions($3,$4);
		}
	|
		
		SL_IDENTIFIER_VALUE
		SL_OPEN_SQR_PARANTHESIS
		slFloatValue
		SL_CLOSE_SQR_PARANTHESIS
		{
			CVariable	*cVar	=	sdr->newVariable($1,sdr->desired() | SLC_ARRAY,(int) $3);

			sdr->variableList->push(cVar);
		}
		slVariableIdentifierTail
		{
			$$	=	$6;
		}
	|
		SL_IDENTIFIER_VALUE
		SL_OPEN_SQR_PARANTHESIS
		slFloatValue
		SL_CLOSE_SQR_PARANTHESIS
		{
			CVariable	*cVar	=	sdr->newVariable($1,sdr->desired() | SLC_ARRAY,(int) $3);

			sdr->variableList->push(cVar);
		}

		slVariableInitializer
		slVariableIdentifierTail
		{
			$$	=	new CTwoExpressions($6,$7);
		}
		;

slVariableIdentifierTail:
		SL_COMMA
		slVariableIdentifierList
		{
			$$	=	$2;
			checkPoint();
		}
	|
		SL_SEMI_COLON
		{
			$$	=	new CNullExpression;
		}
		;


		////////////////////////////////////////////////
		// A general statement
slStatement:
		slUnmatchedStatement
		{

			$$	=	$1;
			if (!(sdr->desired() & SLC_NONE))
				sdr->fatalbailout();
			checkPoint();
		}
	|
		slMatchedStatement
		{
			$$	=	$1;
			if (!(sdr->desired() & SLC_NONE))
				sdr->fatalbailout();
			checkPoint();
		}
	|
		error
		{
			// Recoverable error happened
			$$	=	new CNullExpression;
			if (!(sdr->desired() & SLC_NONE))
				sdr->fatalbailout();
			checkPoint();
		}

		;

slStatements:
		slStatements
		{
			sdr->statementLineNo	=	sdr->lineNo;
		}
		slStatement
		{
			$$	=	new CTwoExpressions($1,$3);
		}
	|
		{
			sdr->statementLineNo	=	sdr->lineNo;
			$$	=	new CNullExpression;
		}
		;


		////////////////////////////////////////////////
		// A Matched statement
slMatchedStatement:
		slForStatement
		{
			$$	=	$1;
		}
	|
		slWhileStatement
		{
			$$	=	$1;
		}
	|
		slMatchedIfStatement
		{
			$$	=	$1;
		}
	|
		slMatchedGatherStatement
		{
			$$	=	$1;
		}
	|
		slAssignmentStatement SL_SEMI_COLON
		{
			$$	=	$1;
		}
	|
		slUpdateStatement SL_SEMI_COLON
		{
			$$	=	$1;
		}
	|
		slBreakStatement 
		{
			$$	=	$1;
		}
	|
		slContinueStatement 
		{
			$$	=	$1;
		}
	|
		slReturnStatement
		{
			$$	=	$1;
		}
	|	
		slIlluminanceStatement
		{
			$$	=	$1;
		}
	|
		slIlluminateStatement
		{
			$$	=	$1;
		}
	|
		slSolarStatement
		{
			$$	=	$1;
		}
	|
		slBlock
		{
			$$	=	$1;
		}
	|
		slVariableDeclarations
		{
			$$	=	$1;
		}
	|
		slFunction
		{
			$$	=	new CNullExpression;
		}
	|
		slFunctionCall SL_SEMI_COLON
		{
			$$	=	$1;
		}
	|
		SL_SEMI_COLON
		{
			$$					=	new CNullExpression;
		}
		;

		////////////////////////////////////////////////
		// Unmatched shatement
slUnmatchedStatement:
		slUnmatchedIfStatement
		{
			$$	=	$1;
		}
	|
		slUnmatchedGatherStatement
		{
			$$	=	$1;
		}
	|
		slUnmatchedWhileStatement
		{
			$$	=	$1;
		}
	|
		slUnmatchedForStatement
		{
			$$	=	$1;
		}
	|
		slUnmatchedIlluminanceStatement
		{
			$$	=	$1;
		}
	|
		slUnmatchedIlluminateStatement
		{
			$$	=	$1;
		}
	|
		slUnmatchedSolarStatement
		{
			$$	=	$1;
		}
		;

		////////////////////////////////////////////////
		// Break statement
slBreakStatement:
		SL_BREAK SL_FLOAT_VALUE SL_SEMI_COLON
		{
			CFunction	*cFunction;
			int			bc;
			char		tmp[256];

			if (sscanf($2,"%d",&bc) != 1) sdr->error("Invalid break count: %s\n",$2);

			if (bc <= 0) sdr->error("Bad break count: %s\n",$2);

			for(cFunction = sdr->functionStack->last(); cFunction != NULL; cFunction = sdr->functionStack->prev()) {
				if (strcmp(cFunction->symbolName,constantLoopName) == 0) bc--;
				else if (strcmp(cFunction->symbolName,constantBlockName) == 0) continue;

				if (bc == 0) break;

				sdr->error("Break target not found\n");
				break;
			}

			if (cFunction == NULL) sdr->error("Break target not found\n");

			sprintf(tmp,"%s\t%s\n",opcodeBreak,$2);

			$$	=	new CFixedExpression(tmp);
		}
	|
		SL_BREAK SL_SEMI_COLON
		{
			CFunction	*cFunction;
			char		tmp[256];
			int			bc	=	(int) 1;

			sdr->functionStack->push(sdr->lastFunction);
			for(cFunction = sdr->functionStack->last(); cFunction != NULL; cFunction = sdr->functionStack->prev()) {
				if (strcmp(cFunction->symbolName,constantLoopName) == 0) bc--;
				else if (strcmp(cFunction->symbolName,constantBlockName) == 0) continue;

				if (bc == 0) break;

				sdr->error("Break target not found\n");
				break;
			}
			sdr->lastFunction	=	sdr->functionStack->pop();

			if (cFunction == NULL) sdr->error("Break target not found\n");

			sprintf(tmp,"%s\t1\n",opcodeBreak);

			$$	=	new CFixedExpression(tmp);
		}
		;

		////////////////////////////////////////////////
		// Continue statement
slContinueStatement:
		SL_CONTINUE SL_FLOAT_VALUE SL_SEMI_COLON
		{
			CFunction	*cFunction;
			char		tmp[256];
			int			bc;

			if (sscanf($2,"%d",&bc) != 1) sdr->error("Bad continue count: %s\n",$2);

			if (bc <= 0) sdr->error("Bad continue count: %s\n",$2);

			for(cFunction = sdr->functionStack->last(); cFunction != NULL; cFunction = sdr->functionStack->prev()) {
				if (strcmp(cFunction->symbolName,constantLoopName) == 0) bc--;
				else if (strcmp(cFunction->symbolName,constantBlockName) == 0) continue;

				if (bc == 0) break;

				sdr->error("Continue target not found\n");
				break;
			}

			if (cFunction == NULL) sdr->error("Continue target not found\n");

			sprintf(tmp,"%s\t%s\n",opcodeContinue,$2);

			$$	=	new CFixedExpression(tmp);
		}
	|
		SL_CONTINUE SL_SEMI_COLON
		{
			CFunction	*cFunction;
			char		tmp[256];
			int			bc	=	(int) 1;

			for(cFunction = sdr->functionStack->last(); cFunction != NULL; cFunction = sdr->functionStack->prev()) {
				if (strcmp(cFunction->symbolName,constantLoopName) == 0) bc--;
				else if (strcmp(cFunction->symbolName,constantBlockName) == 0) continue;

				if (bc == 0) break;
				
				sdr->error("Continue target not found\n");
				break;
			}

			if (cFunction == NULL) sdr->error("Continue target not found\n");

			sprintf(tmp,"%s\t1\n",opcodeContinue);

			$$	=	new CFixedExpression(tmp);
		}
		;

		////////////////////////////////////////////////
		// Return statement
slReturnStatement:
		SL_RETURN 
		{
			CFunction	*cFun = sdr->lastFunction;
			
			// Work out what we're returning from
			for (cFun = sdr->functionStack->last(); cFun != NULL; cFun = sdr->functionStack->prev()) {
				if (strcmp(cFun->symbolName,constantBlockName) == 0) continue;
				if (strcmp(cFun->symbolName,constantLoopName) == 0) continue;
				break;
			}

			// Figure out what the return type is and desire it
			CParameter	*retParam = cFun->returnValue;
			if (retParam) {
				int returnType = retParam->type;
				sdr->desire(returnType);
			} else {
				sdr->desire(SLC_NONE);
			}
		}
		slAritmeticExpression SL_SEMI_COLON
		{
			CFunction	*cFun	=	sdr->lastFunction;
			CExpression	*c;

			sdr->undesire();
			
			// Skip over loops
			for (cFun = sdr->functionStack->last(); cFun != NULL; cFun = sdr->functionStack->prev()) {
				if (strcmp(cFun->symbolName,constantBlockName) == 0) continue;
				if (strcmp(cFun->symbolName,constantLoopName) == 0) continue;
				break;
			}

			if (cFun ==	NULL) {
				sdr->error("Return target not found\n");
				$$	=	new CNullExpression;
			} else {
				if (cFun->returnValue == NULL) {
					if (cFun == sdr->shaderFunction)
						sdr->warning("Shader was not expecting a return statement\n");
					else
						sdr->error("Function \"%s\" was not expecting a return value\n",cFun->symbolName);
					c	=	new CNullExpression;
				} else {
					// Warn if the actual return type is different from the declared return type. Some type conversions
					// (like upconvert float to vector) can be done, but may not be intended.
					if (($3->type & (SLC_FLOAT|SLC_VECTOR|SLC_STRING|SLC_MATRIX)) 
						!= (cFun->returnValue->type & (SLC_FLOAT|SLC_VECTOR|SLC_STRING|SLC_MATRIX)))
						sdr->warning("Return value of function \"%s\" does not match function declaration\n",cFun->symbolName);
						
					// if the return type is uniform, set the return value to uniform
					if ($3->type & SLC_UNIFORM) cFun->returnValue->type |= SLC_UNIFORM;
					c	=	new CAssignmentExpression(cFun->returnValue,$3);
				}

				$$	=	c;

				cFun->returnValueGiven	=	TRUE;
			}
		}
	|
		SL_RETURN SL_SEMI_COLON
		{
			CFunction	*cFun	=	sdr->lastFunction;

			// Skip over loops
			for (cFun = sdr->functionStack->last(); cFun != NULL; cFun = sdr->functionStack->prev()) {
				if (strcmp(cFun->symbolName,constantBlockName) == 0) continue;
				if (strcmp(cFun->symbolName,constantLoopName) == 0) continue;
				break;
			}

			if (cFun ==	NULL)	sdr->error("Return target not found\n");
			else {
				if (cFun->returnValue != NULL) {
					sdr->error("Function \"%s\" was expecting a return value\n",cFun->symbolName);
				}
			}
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
			CFunction	*cFun	=	sdr->newFunction(constantLoopName);
			
			$$	=	$3;	
		}
		;


slWhileStatement:
		slWhileStartStatement
		slMatchedStatement
		{
			CFunction	*cFun	=	sdr->popFunction();

			$$	=	new CForLoop(NULL,$1,NULL,$2);
		}
		;

slUnmatchedWhileStatement:
		slWhileStartStatement
		slUnmatchedStatement
		{

			CFunction	*cFun	=	sdr->popFunction();

			$$	=	new CForLoop(NULL,$1,NULL,$2);
		}
		;

		////////////////////////////////////////////////
		// A general assignment statement
slAssignmentStatement:
		SL_IDENTIFIER_VALUE
		SL_EQUAL
		{
			CVariable	*cVar				=	sdr->getVariable($1);

			if (cVar == NULL)	sdr->error("Identifier \"%s\" is not found\n",$1);
			else				sdr->desire(cVar->type);
		}
		slAritmeticExpression
		{
			CVariable			*cVar		=	sdr->getVariable($1);

			if (cVar == NULL) {	
				$$	=	new CNullExpression;
			} else {
				$$	=	new CAssignmentExpression(cVar,$4);
				sdr->undesire();
			}
		}
		|
		SL_IDENTIFIER_VALUE
		SL_OPEN_SQR_PARANTHESIS
		slAritmeticExpression
		SL_CLOSE_SQR_PARANTHESIS
		SL_EQUAL
		{
			CVariable	*cVar				=	sdr->getVariable($1);

			if (cVar == NULL)	sdr->error("Identifier \"%s\" is not found\n",$1);
			else				sdr->desire(cVar->type);
		}
		slAritmeticExpression
		{
			CVariable			*cVar		=	sdr->getVariable($1);

			if (cVar == NULL) {
				$$	=	new CNullExpression;
			} else if (cVar->type & SLC_ARRAY) {
				$$	=	new CArrayAssignmentExpression(cVar,$3,$7);
				sdr->undesire();
			} else {
				CList<CExpression *>	*dummyParams = new CList<CExpression *>;
				CFunctionPrototype		*cFun;

				dummyParams->push(new CTerminalExpression(cVar));
				dummyParams->push($3);
				dummyParams->push($7);

				// Check the builtin functions
				for (cFun = sdr->builtinFunctions->first(); cFun != NULL; cFun = sdr->builtinFunctions->next()) {
					if (cFun->match("setcomp",dummyParams,sdr->desired())) break;
				}
				
				if (cFun == NULL) {
					// Cleanup
					CExpression	*cCode;
					while((cCode = dummyParams->pop()) != NULL) {
						delete cCode;
					}
					delete dummyParams;
					// Report error
					sdr->error("Can't assign to non array\n");
					$$	=	new CNullExpression;
				} else {
					$$	=	new CBuiltinExpression(cFun,dummyParams);
				}
				sdr->undesire();
			}
		}
		;

		////////////////////////////////////////////////
		// A general assignment statement
slUpdateStatement:
		SL_IDENTIFIER_VALUE
		SL_INCREMENT_BY
		{
			CVariable	*cVar				=	sdr->getVariable($1);

			if (cVar == NULL)	sdr->error("Identifier \"%s\" is not found\n",$1);
			else				sdr->desire(cVar->type);
		}
		slAritmeticExpression
		{
			CVariable			*cVar		=	sdr->getVariable($1);

			if (cVar == NULL) {
				$$	=	new CNullExpression;
			} else {
				$$	=	new CUpdateExpression(cVar,opcodeAddFloatFloat,opcodeAddVectorVector,FALSE,$4);
				sdr->undesire();
			}
		}
		|
		SL_IDENTIFIER_VALUE
		SL_DECREMENT_BY
		{
			CVariable	*cVar				=	sdr->getVariable($1);

			if (cVar == NULL)	sdr->error("Identifier \"%s\" is not found\n",$1);
			else				sdr->desire(cVar->type);
		}
		slAritmeticExpression
		{
			CVariable			*cVar		=	sdr->getVariable($1);

			if (cVar == NULL) {
				$$	=	new CNullExpression;
			} else {
				$$	=	new CUpdateExpression(cVar,opcodeSubFloatFloat,opcodeSubVectorVector,FALSE,$4);
				sdr->undesire();
			}
		}
		|
		SL_IDENTIFIER_VALUE
		SL_INCREMENT
		{
			CVariable	*cVar				=	sdr->getVariable($1);

			if (cVar == NULL)	sdr->error("Identifier \"%s\" is not found\n",$1);
			else {
				$$	=	new CUpdateExpression(cVar,opcodeAddFloatFloat,opcodeAddVectorVector,FALSE,new CConstantTerminalExpression(SLC_FLOAT,strdup("1")));
			}
		}
		|
		SL_IDENTIFIER_VALUE
		SL_DECREMENT
		{
			CVariable	*cVar				=	sdr->getVariable($1);

			if (cVar == NULL)	sdr->error("Identifier \"%s\" is not found\n",$1);
			else {
				$$	=	new CUpdateExpression(cVar,opcodeAddFloatFloat,opcodeAddVectorVector,FALSE,new CConstantTerminalExpression(SLC_FLOAT,strdup("-1")));
			}
		}
		|
		SL_IDENTIFIER_VALUE
		SL_MULTIPLY_BY
		{
			CVariable	*cVar				=	sdr->getVariable($1);

			if (cVar == NULL)	sdr->error("Identifier \"%s\" is not found\n",$1);
			else				sdr->desire(cVar->type);
		}
		slAritmeticExpression
		{
			CVariable			*cVar		=	sdr->getVariable($1);

			if (cVar == NULL) {
				$$	=	new CNullExpression;
			} else {
				$$	=	new CUpdateExpression(cVar,opcodeMulFloatFloat,opcodeMulVectorVector,FALSE,$4);
				sdr->undesire();
			}
		}
		|
		SL_IDENTIFIER_VALUE
		SL_DIVIDE_BY
		{
			CVariable	*cVar				=	sdr->getVariable($1);

			if (cVar == NULL)	sdr->error("Identifier \"%s\" is not found\n",$1);
			else				sdr->desire(cVar->type);
		}
		slAritmeticExpression
		{
			CVariable			*cVar		=	sdr->getVariable($1);

			if (cVar == NULL) {
				$$	=	new CNullExpression;
			} else {
				$$	=	new CUpdateExpression(cVar,opcodeDivFloatFloat,opcodeDivVectorVector,FALSE,$4);
				sdr->undesire();
			}
		}
		|
		SL_IDENTIFIER_VALUE
		SL_OPEN_SQR_PARANTHESIS
		slAritmeticExpression
		SL_CLOSE_SQR_PARANTHESIS
		SL_INCREMENT_BY
		{
			CVariable	*cVar				=	sdr->getVariable($1);

			if (cVar == NULL)	sdr->error("Identifier \"%s\" is not found\n",$1);
			else				sdr->desire(cVar->type);
		}
		slAritmeticExpression
		{
			CVariable			*cVar		=	sdr->getVariable($1);
			
			if (cVar == NULL) {
				$$	=	new CNullExpression;
			} else {
				$$	=	new CArrayUpdateExpression(cVar,$3,$7,opcodeAddFloatFloat,opcodeAddVectorVector,opcodeAddMatrixMatrix);
				sdr->undesire();
			}
		}
		|
		SL_IDENTIFIER_VALUE
		SL_OPEN_SQR_PARANTHESIS
		slAritmeticExpression
		SL_CLOSE_SQR_PARANTHESIS
		SL_DECREMENT_BY
		{
			CVariable	*cVar				=	sdr->getVariable($1);

			if (cVar == NULL)	sdr->error("Identifier \"%s\" is not found\n",$1);
			else				sdr->desire(cVar->type);
		}
		slAritmeticExpression
		{
			CVariable			*cVar		=	sdr->getVariable($1);

			if (cVar == NULL) {
				$$	=	new CNullExpression;
			} else {
				$$	=	new CArrayUpdateExpression(cVar,$3,$7,opcodeSubFloatFloat,opcodeSubVectorVector,opcodeSubMatrixMatrix);
				sdr->undesire();
			}
		}
		|
		SL_IDENTIFIER_VALUE
		SL_OPEN_SQR_PARANTHESIS
		slAritmeticExpression
		SL_CLOSE_SQR_PARANTHESIS
		SL_INCREMENT
		{
			CVariable	*cVar				=	sdr->getVariable($1);

			if (cVar == NULL)	sdr->error("Identifier \"%s\" is not found\n",$1);
			else {
				$$	=	new CArrayUpdateExpression(cVar,$3,new CConstantTerminalExpression(SLC_FLOAT,strdup("1")),opcodeAddFloatFloat,opcodeAddVectorVector,opcodeAddMatrixMatrix);
			}
		}
		|
		SL_IDENTIFIER_VALUE
		SL_OPEN_SQR_PARANTHESIS
		slAritmeticExpression
		SL_CLOSE_SQR_PARANTHESIS
		SL_DECREMENT
		{
			CVariable	*cVar				=	sdr->getVariable($1);

			if (cVar == NULL)	sdr->error("Identifier \"%s\" is not found\n",$1);
			else {
				$$	=	new CArrayUpdateExpression(cVar,$3,new CConstantTerminalExpression(SLC_FLOAT,strdup("-1")),opcodeAddFloatFloat,opcodeAddVectorVector,opcodeAddMatrixMatrix);
			}
		}
		|
		SL_IDENTIFIER_VALUE
		SL_OPEN_SQR_PARANTHESIS
		slAritmeticExpression
		SL_CLOSE_SQR_PARANTHESIS
		SL_MULTIPLY_BY
		{
			CVariable	*cVar				=	sdr->getVariable($1);

			if (cVar == NULL)	sdr->error("Identifier \"%s\" is not found\n",$1);
			else				sdr->desire(cVar->type);
		}
		slAritmeticExpression
		{
			CVariable			*cVar		=	sdr->getVariable($1);

			if (cVar == NULL) {
				$$	=	new CNullExpression;
			} else {
				$$	=	new CArrayUpdateExpression(cVar,$3,$7,opcodeMulFloatFloat,opcodeMulVectorVector,opcodeMulMatrixMatrix);
				sdr->undesire();
			}
		}
		|
		SL_IDENTIFIER_VALUE
		SL_OPEN_SQR_PARANTHESIS
		slAritmeticExpression
		SL_CLOSE_SQR_PARANTHESIS
		SL_DIVIDE_BY
		{
			CVariable	*cVar				=	sdr->getVariable($1);

			if (cVar == NULL)	sdr->error("Identifier \"%s\" is not found\n",$1);
			else				sdr->desire(cVar->type);
		}
		slAritmeticExpression
		{
			CVariable			*cVar		=	sdr->getVariable($1);

			if (cVar == NULL) {
				$$	=	new CNullExpression;
			} else {
				$$	=	new CArrayUpdateExpression(cVar,$3,$7,opcodeDivFloatFloat,opcodeDivVectorVector,opcodeDivMatrixMatrix);
				sdr->undesire();
			}
		}
		;

		////////////////////////////////////////////////
		// A general for statement
slForStartStatement:
		SL_FOR
		{
			CFunction	*cFun	=	sdr->newFunction(constantLoopName);
		}

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
			CFunction	*cFun	=	sdr->popFunction();

			$$	=	new CForLoop($3,$5,$7,$9);
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
			CFunction	*cFun	=	sdr->popFunction();

			$$	=	new CForLoop($3,$5,$7,$9);
		}
		;

		////////////////////////////////////////////////
		// For init statement list
slForInitStatement:
		slForInitStatements
		{
			$$	=	$1;
		}
	|
		{
			$$	=	new CNullExpression;
		}
		;

		////////////////////////////////////////////////
		// For init statements
slForInitStatements:
		slAssignmentStatement
		SL_COMMA
		slForInitStatements
		{
			$$	=	new CTwoExpressions($1,$3);
		}
	|
		slAssignmentStatement
		{
			$$	=	$1;
		}
		;

		////////////////////////////////////////////////
		// For check statement
slForCheckStatement:
		slAritmeticExpression
		{
			$$	=	getConversion(SLC_FLOAT,$1);
		}
	|
		{
			$$	=	new CConstantTerminalExpression(SLC_FLOAT | SLC_UNIFORM,strdup("1"));
		}
		;

		////////////////////////////////////////////////
		// For increment statement list
slForIncrementStatement:
		slForIncrementStatements
		{
			$$	=	$1;
		}
	|
		{
			$$	=	new CNullExpression;
		}
		;

		////////////////////////////////////////////////
		// For increment statements
slForIncrementStatements:
		slAssignmentStatement
		SL_COMMA
		slForIncrementStatements
		{
			$$	=	new CTwoExpressions($1,$3);
		}
	|
		slAssignmentStatement
		{
			$$	=	$1;
		}
	|
		slUpdateStatement
		SL_COMMA
		slForIncrementStatements
		{
			$$	=	new CTwoExpressions($1,$3);
		}
	|
		slUpdateStatement
		{
			$$	=	$1;
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
			$$	=	new CIfThenElse($3,$5,$7);
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
			$$	=	new CIfThenElse($3,$5,NULL);
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
			$$	=	new CIfThenElse($3,$5,$7);
		}
		;



		////////////////////////////////////////////////
		// Gather parameter list
slGatherParameterList:
		slGatherParameterList
		SL_COMMA
		slAritmeticExpression
		{
			$$->push($3);
		}
		|
		slAritmeticExpression
		{
			sdr->actualParameters->push($1);
			$$	=	sdr->actualParameters;
		}
		;

slGatherHeader:
		SL_GATHER
		SL_OPEN_PARANTHESIS
		{
			sdr->actualParameterStack->push(sdr->actualParameters);
			sdr->actualParameters	=	new CList<CExpression *>;
		}
		slGatherParameterList
		SL_CLOSE_PARANTHESIS
		{
			$$	=	$4;
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
			$$	=	new CGatherThenElse($1,$2,$4);
			sdr->actualParameters	=	sdr->actualParameterStack->pop();
		}
		;

		////////////////////////////////////////////////
		// Unmatched if statement
slUnmatchedGatherStatement:
		slGatherHeader
		slStatement
		{
			$$	=	new CGatherThenElse($1,$2,NULL);
			sdr->actualParameters	=	sdr->actualParameterStack->pop();
		}
	|
		slGatherHeader
		slMatchedStatement
		SL_ELSE
		slUnmatchedStatement
		{
			$$	=	new CGatherThenElse($1,$2,$4);
			sdr->actualParameters	=	sdr->actualParameterStack->pop();
		}
		;

		////////////////////////////////////////////////
		// Illuminance statement
slIlluminanceStartStatement:
		SL_ILLUMINANCE
		{
			CFunction	*cCFunction	=	sdr->newFunction(constantLoopName);

			sdr->requiredShaderContext	|=	SLC_SURFACE;
		}

slIlluminanceStatement:
		slIlluminanceStartStatement
		SL_OPEN_PARANTHESIS
		slArrayItems
		SL_CLOSE_PARANTHESIS
		slMatchedStatement
		{
			CFunction	*cFun	=	sdr->popFunction();

			$$	=	new CIlluminationLoop($3,$5);
			
		}
		;

slUnmatchedIlluminanceStatement:
		slIlluminanceStartStatement
		SL_OPEN_PARANTHESIS
		slArrayItems
		SL_CLOSE_PARANTHESIS
		slUnmatchedStatement
		{
			CFunction	*cFun	=	sdr->popFunction();

			$$	=	new CIlluminationLoop($3,$5);
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
			sdr->requiredShaderContext	|=	SLC_LIGHT;

			$$	=	new CIlluminateSolar(opcodeIlluminate,opcodeEndIlluminate,$3,NULL,NULL,$5);
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
			sdr->requiredShaderContext	|=	SLC_LIGHT;

			$$	=	new CIlluminateSolar(opcodeIlluminate,opcodeEndIlluminate,$3,$5,$7,$9);
		}
		;

slUnmatchedIlluminateStatement:
		SL_ILLUMINATE
		SL_OPEN_PARANTHESIS
		slAritmeticExpression
		SL_CLOSE_PARANTHESIS
		slUnmatchedStatement
		{
			sdr->requiredShaderContext	|=	SLC_LIGHT;

			$$	=	new CIlluminateSolar(opcodeIlluminate,opcodeEndIlluminate,$3,NULL,NULL,$5);
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
			sdr->requiredShaderContext	|=	SLC_LIGHT;

			$$	=	new CIlluminateSolar(opcodeIlluminate,opcodeEndIlluminate,$3,$5,$7,$9);
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
			sdr->requiredShaderContext	|=	SLC_LIGHT;

			$$	=	new CIlluminateSolar(opcodeSolar,opcodeEndSolar,NULL,NULL,NULL,$4);
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
			sdr->requiredShaderContext	|=	SLC_LIGHT;

			$$	=	new CIlluminateSolar(opcodeSolar,opcodeEndSolar,$3,$5,NULL,$7);
		}
		;

slUnmatchedSolarStatement:
		SL_SOLAR
		SL_OPEN_PARANTHESIS
		SL_CLOSE_PARANTHESIS
		slUnmatchedStatement
		{
			sdr->requiredShaderContext	|=	SLC_LIGHT;

			$$	=	new CIlluminateSolar(opcodeSolar,opcodeEndSolar,NULL,NULL,NULL,$4);
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
			sdr->requiredShaderContext	|=	SLC_LIGHT;

			$$	=	new CIlluminateSolar(opcodeSolar,opcodeEndSolar,$3,$5,NULL,$7);
		}
		;

		////////////////////////////////////////////////
		// Aritmetic expression
slAritmeticExpression:
		slAritmeticTerminalValue
		{
			$$	=	$1;
		}
	|
		slAritmeticExpression
		SL_PLUS
		slAritmeticExpression
		{
			$$	=	getOperation($1,$3,opcodeAddFloatFloat,opcodeAddVectorVector,opcodeAddMatrixMatrix,NULL,0);
		}
	|
		slAritmeticExpression
		SL_MINUS
		slAritmeticExpression
		{
			$$	=	getOperation($1,$3,opcodeSubFloatFloat,opcodeSubVectorVector,opcodeSubMatrixMatrix,NULL,0);
		}
	|
		slAritmeticExpression
		SL_MULTIPLY
		slAritmeticExpression
		{
			$$	=	NULL;

			if ($1->type & SLC_MATRIX) {
				if ($3->type & SLC_VVECTOR) {
					$$	=	new CBinaryExpression(SLC_VECTOR | SLC_VVECTOR,opcodeMulMatrixVector,$1,getConversion(SLC_VECTOR,$3));
				} else if ($3->type & SLC_VPOINT) {
					$$	=	new CBinaryExpression(SLC_VECTOR | SLC_VPOINT,opcodeMulMatrixPoint,$1,getConversion(SLC_VECTOR,$3));
				} else if ($3->type & SLC_VNORMAL) {
					$$	=	new CBinaryExpression(SLC_VECTOR | SLC_VNORMAL,opcodeMulMatrixNormal,$1,getConversion(SLC_VECTOR,$3));
				}
			}

			if ($$ == NULL) {
				if ($3->type & SLC_MATRIX) {
					if ($1->type & SLC_VVECTOR) {
						$$	=	new CBinaryExpression(SLC_VECTOR | SLC_VVECTOR,opcodeMulVectorMatrix,$1,getConversion(SLC_VECTOR,$3));
					} else if ($1->type & SLC_VPOINT) {
						$$	=	new CBinaryExpression(SLC_VECTOR | SLC_VPOINT,opcodeMulPointMatrix,$1,getConversion(SLC_VECTOR,$3));
					} else if ($1->type & SLC_VNORMAL) {
						$$	=	new CBinaryExpression(SLC_VECTOR | SLC_VNORMAL,opcodeMulNormalMatrix,$1,getConversion(SLC_VECTOR,$3));
					}
				}
			}


			if ($$ == NULL)
				$$	=	getOperation($1,$3,opcodeMulFloatFloat,opcodeMulVectorVector,opcodeMulMatrixMatrix,NULL,0);
		}
	|
		slAritmeticExpression
		SL_DIVIDE
		slAritmeticExpression
		{
			$$	=	getOperation($1,$3,opcodeDivFloatFloat,opcodeDivVectorVector,opcodeDivMatrixMatrix,NULL,0);
		}
	|
		slAritmeticExpression
		SL_DOT
		{
			sdr->desire(SLC_VECTOR | SLC_VVECTOR);
		}
		slAritmeticExpression
		{
			sdr->undesire();
			$$	=	new CBinaryExpression(SLC_FLOAT,opcodeDotProduct,getConversion(SLC_VECTOR,$1),getConversion(SLC_VECTOR,$4));
		}
	|
		slAritmeticExpression
		SL_CROSS
		{
			sdr->desire(SLC_VECTOR | SLC_VVECTOR);
		}
		slAritmeticExpression
		{
			sdr->undesire();
			$$	=	new CBinaryExpression(SLC_VECTOR,opcodeCrossProduct,getConversion(SLC_VECTOR,$1),getConversion(SLC_VECTOR,$4));
		}
	|
		SL_PLUS
		slAritmeticExpression
		{
			$$	=	$2;	
		}
	|
		SL_MINUS
		slAritmeticExpression
		{
			$$	=	getOperation($2,opcodeNegFloat,opcodeNegVector,opcodeNegMatrix,NULL,0);
		}
	|
		slAritmeticExpression
		SL_QUESTION
		slAritmeticExpression
		SL_COLON
		slAritmeticExpression
		{
			int	ft	=	$3->type;
			int	st	=	$5->type;

			if (($3->type & SLC_TYPE_MASK) == ($5->type & SLC_TYPE_MASK)) {
				$$	=	new CConditionalExpression($3->type,$1,$3,$5);
			} else {
				sdr->error("Type mismatch in conditional execution\n");
			}
		}
	|
		slAritmeticExpression
		SL_AND
		slAritmeticExpression
		{
			$$	=	getOperation($1,$3,opcodeAnd,NULL,NULL,NULL,0);
		}
	|
		slAritmeticExpression
		SL_OR
		slAritmeticExpression
		{
			$$	=	getOperation($1,$3,opcodeOr,NULL,NULL,NULL,0);
		}
	|
		slAritmeticExpression
		SL_COMP_GREATER
		slAritmeticExpression
		{
			$$			=	getOperation($1,$3,opcodeFloatGreater,opcodeVectorGreater,NULL,NULL,SLC_FLOAT);
		}
	|
		slAritmeticExpression
		SL_COMP_LESS
		slAritmeticExpression
		{
			$$			=	getOperation($1,$3,opcodeFloatLess,opcodeVectorLess,NULL,NULL,SLC_FLOAT);
		}
	|
		slAritmeticExpression
		SL_COMP_GREATER_EQUAL
		slAritmeticExpression
		{
			$$			=	getOperation($1,$3,opcodeFloatEGreater,opcodeVectorEGreater,NULL,NULL,SLC_FLOAT);
		}
	|
		slAritmeticExpression
		SL_COMP_LESS_EQUAL
		slAritmeticExpression
		{
			$$			=	getOperation($1,$3,opcodeFloatELess,opcodeVectorELess,NULL,NULL,SLC_FLOAT);
		}
	|
		slAritmeticExpression
		SL_COMP_EQUAL
		slAritmeticExpression
		{
			$$			=	getOperation($1,$3,opcodeFloatEqual,opcodeVectorEqual,NULL,opcodeStringEqual,SLC_FLOAT);
		}
	|
		slAritmeticExpression
		SL_COMP_DIFFERENT
		slAritmeticExpression
		{
			$$			=	getOperation($1,$3,opcodeFloatNotEqual,opcodeVectorNotEqual,NULL,opcodeStringNotEqual,SLC_FLOAT);
		}
	|
		SL_NOT
		slAritmeticExpression
		{
			$$			=	new CUnaryExpression(SLC_FLOAT,opcodeNot,getConversion(SLC_FLOAT,$2));
		}
		;

slArrayList:
		SL_OPEN_CRL_PARANTHESIS
		slArrayItems
		SL_CLOSE_CRL_PARANTHESIS
		{
			$$	=	$2;
		}
		;

slArrayItems:
		slAritmeticExpression
		SL_COMMA
		slArrayItems
		{
			$$	=	$3;
			$$->push($1);
		}
		|
		slAritmeticExpression
		{
			$$	=	new CList<CExpression *>;
			$$->push($1);
		}
		;

slAritmeticTerminalValue:
		SL_FCN_PI
		{
			$$	=	new CConstantTerminalExpression(SLC_FLOAT | SLC_UNIFORM,strdup("3.141592654"));
		}
	|
		slAssignmentStatement
		{
			$$	=	$1;
		}
	|
		slUpdateStatement
		{
			$$	=	$1;
		}
	|
		slAritmeticTypeCast
		{
			$$	=	$1;
		}
	|
		slFunctionCall
		{
			$$	=	$1;
		}
	|
		slTypeDecl
		slFunctionCall
		{
			$$	=	getConversion($1,$2);
			sdr->undesire();
		}
	|
		slTypeDecl
		SL_TEXT_VALUE
		slFunctionCall
		{
			$$	=	getConversion($1,$2,$3);
			sdr->undesire();
		}
	|
		SL_IDENTIFIER_VALUE
		{
	
			CVariable	*cVar	=	sdr->getVariable($1);

			if (cVar == NULL) {
				sdr->error("Identifier \"%s\" is not found\n",$1);
				$$	=	new CNullExpression;
			} else { 
				$$	=	new CTerminalExpression(cVar);
			}
		}
	|
		slTypeDecl
		SL_IDENTIFIER_VALUE
		{
	
			CVariable	*cVar	=	sdr->getVariable($2);

			if (cVar == NULL) {
				sdr->error("Identifier \"%s\" is not found\n",$2);
				$$	=	new CNullExpression;
			} else { 
				$$	=	getConversion($1,new CTerminalExpression(cVar));
			}
			
			sdr->undesire();
		}
	|
		SL_IDENTIFIER_VALUE
		SL_OPEN_SQR_PARANTHESIS
		slAritmeticExpression
		SL_CLOSE_SQR_PARANTHESIS
		{
			CVariable *cVar	=	sdr->getVariable($1);

			if (cVar == NULL) {
				sdr->error("Identifier \"%s\" is not found\n",$1);
				$$	=	new CNullExpression;
			} else if (cVar->type & SLC_ARRAY) { 
				$$	=	new CArrayExpression(cVar,$3);
			} else {
				CList<CExpression *>	*dummyParams = new CList<CExpression *>;
				CFunctionPrototype		*cFun;

				dummyParams->push(new CTerminalExpression(cVar));
				dummyParams->push($3);

				// Check the builtin functions
				for (cFun = sdr->builtinFunctions->first(); cFun != NULL; cFun = sdr->builtinFunctions->next()) {
					if (cFun->match("comp",dummyParams,SLC_FLOAT)) break;
				}
				
				if (cFun == NULL) {
					// Cleanup
					CExpression	*cCode;
					while((cCode = dummyParams->pop()) != NULL) {
						delete cCode;
					}
					delete dummyParams;
					// Report error
					sdr->error("Can't index non array\n");
					$$	=	new CNullExpression;
				} else {
					$$	=	new CBuiltinExpression(cFun,dummyParams);
				}
			}
		}
	|
		SL_FLOAT_VALUE
		{
			$$	=	new CConstantTerminalExpression(SLC_FLOAT,strdup($1));
		}
	|
		SL_TEXT_VALUE
		{
			$$	=	new CConstantTerminalExpression(SLC_STRING,strdup($1));
		}
	|
		SL_OPEN_PARANTHESIS
		slAritmeticExpression
		SL_CLOSE_PARANTHESIS
		{	
			$$	=	$2;
		}
		;
	


slAritmeticTypeCast:
		slTypeDecl
		SL_TEXT_VALUE
		{
			// Change the expected type to float
			sdr->undesire();
			sdr->desire(SLC_FLOAT | ($1 & (~(SLC_TYPE_MASK | SLC_SUB_TYPE_MASK))));
		}
		slVectorMatrixExpression
		{
			$$	=	getConversion($1,$2,$4);

			sdr->undesire();
		}
	|
		slTypeDecl
		{
			// Change the expected type to float
			sdr->undesire();
			sdr->desire(SLC_FLOAT | ($1 & (~(SLC_TYPE_MASK | SLC_SUB_TYPE_MASK))));
		}
		slVectorMatrixExpression
		{
			$$	=	getConversion($1,$3);

			sdr->undesire();
		}
	|
		slTypeDecl
		{
			// Change the expected type to float
			sdr->undesire();
			sdr->desire(SLC_FLOAT | ($1 & (~(SLC_TYPE_MASK | SLC_SUB_TYPE_MASK))));
		}
		SL_FLOAT_VALUE
		{
			$$	=	getConversion($1,new CConstantTerminalExpression(SLC_FLOAT,strdup($3)));

			sdr->undesire();
		}
	|
		slVectorMatrixExpression
		{
			$$	=	$1;
		}
		;
		
slVectorMatrixExpression:
		SL_OPEN_PARANTHESIS
		slVMExpression
		SL_CLOSE_PARANTHESIS
		{
			$$	=	$2;
		}
		;
	
		
slVMExpression:
		slAritmeticExpression
		{
			$$	=	$1;
		}
	|
		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		SL_COMMA
		slAritmeticExpression
		{
			$$	=	new CVectorExpression($1,$3,$5);
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
			CExpression	*elements[16];

			elements[0]		=	$1;
			elements[1]		=	$3;
			elements[2]		=	$5;
			elements[3]		=	$7;
			elements[4]		=	$9;
			elements[5]		=	$11;
			elements[6]		=	$13;
			elements[7]		=	$15;
			elements[8]		=	$17;
			elements[9]		=	$19;
			elements[10]	=	$21;
			elements[11]	=	$23;
			elements[12]	=	$25;
			elements[13]	=	$27;
			elements[14]	=	$29;
			elements[15]	=	$31;

			$$				=	new CMatrixExpression(elements);
		}
		
		////////////////////////////////////////////////
		// A CFunction call


		
slFunctionCall:
		slTextureCall
		{
			CFunctionPrototype		*cFun;
			CList<CExpression *>	*parameters	=	sdr->actualParameters;	// This is the list of parameters to the function
			const char				*funName	=	$1;

			// Clear the desired type flags
			sdr->undesire();

			// Restore the old parameters
			sdr->actualParameters		=	sdr->actualParameterStack->pop();

			// Check the builtin functions
			for (cFun = sdr->builtinFunctions->first(); cFun != NULL; cFun = sdr->builtinFunctions->next()) {
				if (cFun->perfectMatch($1,parameters,sdr->desired())) break;
			}

			if (cFun == NULL) {
				for (cFun = sdr->builtinFunctions->first(); cFun != NULL; cFun = sdr->builtinFunctions->next()) {
					if (cFun->match($1,parameters,sdr->desired())) break;
				}
			}

			if (cFun != NULL) {
				$$	=	new CBuiltinExpression(cFun,parameters);
			} else {
				sdr->error("Function \"%s\" is not found\n",$1);
				if (parameters->numItems != 0) {
					CExpression	*cCode;
					while((cCode = parameters->pop()) != NULL) {
						delete cCode;
					}
				}
				delete parameters;
				$$	=	new CNullExpression;
			}
		}
		|
		slFunCall
		{
			$$	=	$1;
		}
		;

	

slFunCallHeader:
		SL_IDENTIFIER_VALUE
		SL_OPEN_PARANTHESIS
		{
			// Save the old parameters
			sdr->actualParameterStack->push(sdr->actualParameters);
			// Start a new parameter list
			sdr->actualParameters	=	new CList<CExpression *>;

			// Make sure we do not do something stupid with the parameters
			sdr->desire(SLC_NONE);

			// Set the name
			$$	=	$1;
		}
		|
		SL_SURFACE
		SL_OPEN_PARANTHESIS
		{
			// Save the old parameters
			sdr->actualParameterStack->push(sdr->actualParameters);
			// Start a new parameter list
			sdr->actualParameters	=	new CList<CExpression *>;

			// Make sure we do not do something stupid with the parameters
			sdr->desire(SLC_NONE);

			// Set the name
			$$	=	"surface";
		}
		|
		SL_DISPLACEMENT
		SL_OPEN_PARANTHESIS
		{
			// Save the old parameters
			sdr->actualParameterStack->push(sdr->actualParameters);
			// Start a new parameter list
			sdr->actualParameters	=	new CList<CExpression *>;

			// Make sure we do not do something stupid with the parameters
			sdr->desire(SLC_NONE);

			// Set the name
			$$	=	"displacement";
		}
		;

slFunCall:
		slFunCallHeader
		slFunctionCallParameterList
		SL_CLOSE_PARANTHESIS
		{
			CFunction				*cFun;
			CList<CExpression *>	*parameters	=	sdr->actualParameters;	// This is the list of parameters to the function
			const char				*funName	=	$1;

			// Clear the desired type flags
			sdr->undesire();

			// Restore the old parameters
			sdr->actualParameters		=	sdr->actualParameterStack->pop();

			// Search for the CFunction here....
			cFun	=	sdr->getFunction($1,parameters);

			if (cFun != NULL) {													// Cool, the function exists
				// A function with the same name is defined ... 
				// Try to match the parameters;
				if (cFun->parameters->numItems == parameters->numItems) {	// The number of parameters match
					// A function with the same name is defined and the number of Parameters match
					$$	=	new CFuncallExpression(cFun,parameters);					
				}
			}

			// If not found, check the predefined CFunctions
			if (cFun == NULL) {
				CFunctionPrototype	*cFun;
				const char			*fName	=	$1;
				// Check the builtin CFunctions

				for (cFun = sdr->builtinFunctions->first(); cFun != NULL; cFun = sdr->builtinFunctions->next()) {
					if (cFun->perfectMatch($1,parameters,sdr->desired())) break;
				}

				if (cFun == NULL) {
					for (cFun = sdr->builtinFunctions->first(); cFun != NULL; cFun = sdr->builtinFunctions->next()) {
						if (cFun->match($1,parameters,sdr->desired())) break;
					}
				}

				// Check if there is a DSO implementing this function
				if (cFun == NULL) {
					sdr->enumerateDso($1);

					for (cFun = sdr->builtinFunctions->first(); cFun != NULL; cFun = sdr->builtinFunctions->next()) {
						if (cFun->perfectMatch($1,parameters,sdr->desired())) break;
					}

					if (cFun == NULL) {
						for (cFun = sdr->builtinFunctions->first(); cFun != NULL; cFun = sdr->builtinFunctions->next()) {
							if (cFun->match($1,parameters,sdr->desired())) break;
						}
					}
				}

				if (cFun != NULL) {
					$$	=	new CBuiltinExpression(cFun,parameters);
				} else {
					sdr->error("Function \"%s\" is not found\n",$1);
					if (parameters->numItems != 0) {
						CExpression	*cCode;
						while((cCode = parameters->pop()) != NULL) {
							delete cCode;
						}
					}
					delete parameters;
					$$	=	new CNullExpression;
				}

			}
		}
		;


		// Either text of value
slTextureNameSpecifier:
		SL_TEXT_VALUE
		{
			$$	=	new CConstantTerminalExpression(SLC_STRING | SLC_UNIFORM,strdup($1));
		}
		|
		SL_IDENTIFIER_VALUE
		{
			CVariable	*cVar	=	sdr->getVariable($1);

			if (cVar != NULL)	$$	=	new CTerminalExpression(cVar);
			else				$$	=	new CNullExpression;
		}
		;


slTextureChannelSpecifier:
		SL_OPEN_SQR_PARANTHESIS
		slAritmeticExpression
		SL_CLOSE_SQR_PARANTHESIS
		{
			$$	=	getConversion(SLC_FLOAT | ($2->type & SLC_UNIFORM),$2);
		}
		|
		{
			$$	=	new CConstantTerminalExpression(SLC_FLOAT | SLC_UNIFORM,strdup("0"));
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
			// Fake the parameters
			CList<CExpression *>	*parameters	=	sdr->actualParameters;	// This is the list of parameters to the function
			CList<CExpression *>	*pl			=	new CList<CExpression *>;
			CExpression				*cExpression;

			pl->push($3);
			pl->push($4);
			for (cExpression=parameters->first();cExpression!=NULL;cExpression=parameters->next())
				pl->push(cExpression);

			delete parameters;
			sdr->actualParameters	=	pl;

			$$						=	$1;
		}
		|
		slTextureName
		SL_OPEN_PARANTHESIS
		slTextureNameSpecifier
		slTextureChannelSpecifier
		SL_CLOSE_PARANTHESIS
		{
			// Fake the parameters
			CList<CExpression *>	*parameters	=	sdr->actualParameters;	// This is the list of parameters to the function
			CList<CExpression *>	*pl			=	new CList<CExpression *>;
			CExpression				*cExpression;

			pl->push($3);
			pl->push($4);
			for (cExpression=parameters->first();cExpression!=NULL;cExpression=parameters->next())
				pl->push(cExpression);

			delete parameters;
			sdr->actualParameters	=	pl;

			$$						=	$1;
		}
		;

slTextureName:
		SL_TEXTURE
		{
			$$	=	"texture";

			// Save the old parameters
			sdr->actualParameterStack->push(sdr->actualParameters);
			// Start a new parameter list
			sdr->actualParameters	=	new CList<CExpression *>;

			// Make sure we do not do something stupid with the parameters
			sdr->desire(SLC_NONE);
		}
		|
		SL_SHADOW
		{
			$$	=	"shadow";

			// Save the old parameters
			sdr->actualParameterStack->push(sdr->actualParameters);
			// Start a new parameter list
			sdr->actualParameters	=	new CList<CExpression *>;

			// Make sure we do not do something stupid with the parameters
			sdr->desire(SLC_NONE);
		}
		|
		SL_ENVIRONMENT
		{
			$$	=	"environment";

			// Save the old parameters
			sdr->actualParameterStack->push(sdr->actualParameters);
			// Start a new parameter list
			sdr->actualParameters	=	new CList<CExpression *>;

			// Make sure we do not do something stupid with the parameters
			sdr->desire(SLC_NONE);
		}
		|
		SL_BUMP
		{
			$$	=	"bump";

			// Save the old parameters
			sdr->actualParameterStack->push(sdr->actualParameters);
			// Start a new parameter list
			sdr->actualParameters	=	new CList<CExpression *>;

			// Make sure we do not do something stupid with the parameters
			sdr->desire(SLC_NONE);
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
			sdr->actualParameters->push($1);
		}
		slFunctionCallParameters
		{
		}
	|
		slAritmeticExpression
		{
			sdr->actualParameters->push($1);
		}
		;

%%


#include	"lex.sl.cpp"



int	CScriptContext::compile(FILE *in,char *outName) {
	
	sdr		=	this;

	slin	=	in;

	slparse();

	// Must have exactly one main shader function
	if (!sdr->shaderType)
		sdr->error("Shader file missing main shader body\n");

	if (compileError == 0) {
		char		*tmp;

		if (outName == NULL) {
			// If there's no compile error, dump the compiled code
			tmp	=	new char[strlen(sdr->shaderName)+5];

			strcpy(tmp,sdr->shaderName);
			strcat(tmp,".sdr");
		} else {
			tmp	=	outName;
		}

		sdr->generateCode(tmp);

		if (tmp != outName) delete [] tmp;

		return TRUE;
	}
	return FALSE;
}


void	yyerror(const char *mes) {
	if (yytext && yytext[0])
		sdr->error("Parse error before '%s'\n",yytext);
	else
		sdr->error("Parse error\n");
}

