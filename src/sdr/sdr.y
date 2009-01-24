%{
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
//  Description			:	This is the parser file for CShader
//
////////////////////////////////////////////////////////////////////////
#undef alloca
#include <math.h>
#include <string.h>

#include "common/algebra.h"
#include "common/os.h"
#include "sdr.h"

/////////////////////////////////////////////////////////////////////////////////////
//   First some temporary data structures used during the script parsing


// Some forward definitions
		void							sdrerror(const char *);		// Forward definition for stupid yacc
		int								sdrlex(void );				// Forward definition for stupid yacc




		TSdrParameter	*parameters;
		TSdrParameter	*currentParameter;
		UDefaultVal		*currentDefaultItem;
		int				numArrayItemsRemaining;
		ESdrShaderType	shaderType;

%}
%union slval {
	float			real;
	char			string[64];
	matrix			m;
	vector			v;
	TSdrParameter *parameter;
}

// Some tokens
%token	 SCRL_PARAMETERS
%token	 SCRL_VARIABLES
%token   SCRL_INIT
%token   SCRL_CODE
%token	 SCRL_OUTPUT
%token	 SCRL_VARYING
%token	 SCRL_UNIFORM
%token	 SCRL_BOOLEAN
%token	 SCRL_FLOAT
%token	 SCRL_COLOR
%token	 SCRL_VECTOR
%token	 SCRL_NORMAL
%token	 SCRL_POINT
%token	 SCRL_MATRIX
%token	 SCRL_STRING

%token	 SCRL_SURFACE
%token	 SCRL_DISPLACEMENT
%token	 SCRL_IMAGER
%token	 SCRL_LIGHTSOURCE
%token	 SCRL_VOLUME
%token	 SCRL_GENERIC

%token	 SCRL_DSO

%token	 SCRL_DOT
%token	 SCRL_COLON
%token	 SCRL_EQUAL
%token	 SCRL_OPEN_PARANTHESIS
%token	 SCRL_CLOSE_PARANTHESIS
%token	 SCRL_OPEN_SQR_PARANTHESIS
%token	 SCRL_CLOSE_SQR_PARANTHESIS
%token	 SCRL_COMMA
%token   SCRL_NL

%token<string>	SCRL_TEXT_VALUE
%token<string>	SCRL_IDENTIFIER_VALUE
%token<string>	SCRL_LABEL_VALUE
%token<real>	SCRL_FLOAT_VALUE
%type<string>	slGlobalParameterContainer
%type<v>		slVectorIn
%type<v>		slVector
%%
start:		
			slType	
			slParameterDefinitions
			slVariableDefinitions
			SCRL_INIT
			SCRL_NL
			slCode
			SCRL_CODE
			SCRL_NL
			slCode
			slEmptySpace
			;

slEmptySpace: 
			|
			SCRL_NL
			slEmptySpace
			;
			
slVectorIn:	SCRL_TEXT_VALUE
			SCRL_FLOAT_VALUE
			{
				currentParameter->space			=	strdup($1);
				currentDefaultItem->vector		=	new float[3];
				currentDefaultItem->vector[0]	=	$2;
				currentDefaultItem->vector[1]	=	$2;
				currentDefaultItem->vector[2]	=	$2;
			}
			|
			SCRL_TEXT_VALUE
			SCRL_OPEN_SQR_PARANTHESIS
			SCRL_FLOAT_VALUE
			SCRL_FLOAT_VALUE
			SCRL_FLOAT_VALUE
			SCRL_CLOSE_SQR_PARANTHESIS
			{
				currentParameter->space			=	strdup($1);
				currentDefaultItem->vector		=	new float[3];
				currentDefaultItem->vector[0]	=	$3;
				currentDefaultItem->vector[1]	=	$4;
				currentDefaultItem->vector[2]	=	$5;
			}
			|
			SCRL_FLOAT_VALUE
			{
				currentDefaultItem->vector		=	new float[3];
				currentDefaultItem->vector[0]	=	$1;
				currentDefaultItem->vector[1]	=	$1;
				currentDefaultItem->vector[2]	=	$1;
			}
			|
			SCRL_OPEN_SQR_PARANTHESIS
			SCRL_FLOAT_VALUE
			SCRL_FLOAT_VALUE
			SCRL_FLOAT_VALUE
			SCRL_CLOSE_SQR_PARANTHESIS
			{
				currentDefaultItem->vector		=	new float[3];
				currentDefaultItem->vector[0]	=	$2;
				currentDefaultItem->vector[1]	=	$3;
				currentDefaultItem->vector[2]	=	$4;
			}
			;

slVector:	slVectorIn
			{
			}
			;

slVectorInit:	SCRL_EQUAL
				slVector
			|
			{
					currentParameter->defaultValue.vector		=	new float[3];
					currentParameter->defaultValue.vector[0]	=	0;
					currentParameter->defaultValue.vector[1]	=	0;
					currentParameter->defaultValue.vector[2]	=	0;
			}
			;
			
slContainer:	SCRL_UNIFORM
				{
				}
				|
				SCRL_VARYING
				{
				}
				|
				{
				}
				;

slType:
		SCRL_SURFACE
		SCRL_NL
		{
			shaderType	=	SHADER_SURFACE;
		}
	|
		SCRL_DISPLACEMENT
		SCRL_NL
		{
			shaderType	=	SHADER_DISPLACEMENT;
		}
	|
		SCRL_LIGHTSOURCE
		SCRL_NL
		{
			shaderType	=	SHADER_LIGHT;
		}
	|
		SCRL_VOLUME
		SCRL_NL
		{
			shaderType	=	SHADER_VOLUME;
		}
	|
		SCRL_IMAGER
		SCRL_NL
		{
			shaderType	=	SHADER_IMAGER;
		}
		;

slParameterDefinitions:
		SCRL_PARAMETERS
		SCRL_COLON
		SCRL_NL
		slParameters
		;

slParameters:
		slParameters
		slParameter
		SCRL_NL
		{
		}
	|
		{
		}
		;

slParameter:
		{
			currentParameter						=	new TSdrParameter;
			currentParameter->space					=	NULL;
			currentParameter->numItems				=	1;
			currentParameter->defaultValue.string	=	NULL;
		}
		slGlobalParameterContainer
		slRegularParameter
		{
			currentParameter->next	=	parameters;
			parameters				=	currentParameter;
		}
	|
		{
			currentParameter						=	new TSdrParameter;
			currentParameter->space					=	NULL;
			currentParameter->numItems				=	1;
			currentParameter->defaultValue.string	=	NULL;
			currentParameter->container				=	CONTAINER_UNIFORM;
		}
		slRegularParameter
		{
			currentParameter->next	=	parameters;
			parameters				=	currentParameter;
		}
		;

slRegularParameter:
		slFloatParameter
	|
		slStringParameter
	|
		slColorParameter
	|
		slVectorParameter
	|
		slNormalParameter
	|
		slPointParameter
	|
		slMatrixParameter
		;

//GSHTODO: This list is missing constant and facevarying!!
slGlobalParameterContainer:
		SCRL_UNIFORM
		{
			currentParameter->container	=	CONTAINER_UNIFORM;
			currentParameter->writable	=	FALSE;
		}
		|
		SCRL_VARYING
		{
			currentParameter->container	=	CONTAINER_VARYING;
			currentParameter->writable	=	FALSE;
		}
		|
		SCRL_OUTPUT
		SCRL_UNIFORM
		{
			currentParameter->container	=	CONTAINER_UNIFORM;
			currentParameter->writable	=	TRUE;
		}
		|
		SCRL_OUTPUT
		SCRL_VARYING
		{
			currentParameter->container	=	CONTAINER_VARYING;
			currentParameter->writable	=	TRUE;
		}
		|
		SCRL_OUTPUT
		{
			currentParameter->container	=	CONTAINER_UNIFORM;
			currentParameter->writable	=	TRUE;
		}
		;

slFloatParameter:
		SCRL_FLOAT
		SCRL_IDENTIFIER_VALUE
		SCRL_EQUAL
		SCRL_FLOAT_VALUE
		{
			currentParameter->type					=	TYPE_FLOAT;
			currentParameter->name					=	strdup($2);
			currentParameter->defaultValue.scalar	=	$4;
			currentParameter->numItems				=	1;
		}
	|
		SCRL_FLOAT
		SCRL_IDENTIFIER_VALUE
		{
			currentParameter->type					=	TYPE_FLOAT;
			currentParameter->name					=	strdup($2);
			currentParameter->defaultValue.scalar	=	0;
			currentParameter->numItems				=	1;
		}
	|
		SCRL_FLOAT
		SCRL_IDENTIFIER_VALUE
		SCRL_OPEN_SQR_PARANTHESIS
		SCRL_FLOAT_VALUE
		SCRL_CLOSE_SQR_PARANTHESIS
		SCRL_EQUAL
		{
			currentParameter->type					=	TYPE_FLOAT;
			currentParameter->name					=	strdup($2);
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) $4];
			currentParameter->numItems				=	(int) $4;
			
			currentDefaultItem = currentParameter->defaultValue.array;
			numArrayItemsRemaining = currentParameter->numItems;
		}
		slFloatArrayInitializer
	|
		SCRL_FLOAT
		SCRL_IDENTIFIER_VALUE
		SCRL_OPEN_SQR_PARANTHESIS
		SCRL_FLOAT_VALUE
		SCRL_CLOSE_SQR_PARANTHESIS
		{
			currentParameter->type					=	TYPE_FLOAT;
			currentParameter->name					=	strdup($2);
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) $4];
			currentParameter->numItems				=	(int) $4;
			
			currentDefaultItem = currentParameter->defaultValue.array;
			for(int i=0;i<currentParameter->numItems;i++)
				currentDefaultItem[i].scalar = 0;
		}
		;

slFloatArrayInitializer:
		SCRL_OPEN_SQR_PARANTHESIS
		slFloatArrayInitializerItems
		SCRL_CLOSE_SQR_PARANTHESIS
		{
			if(numArrayItemsRemaining){
				sdrerror("Wrong number of items in array initializer\n");
			}
		}
		;
		
slFloatArrayInitializerItems:
		slFloatArrayInitializerItems
		SCRL_FLOAT_VALUE
		{
			if(numArrayItemsRemaining){
				currentDefaultItem->scalar = $2;
				currentDefaultItem++;
				numArrayItemsRemaining--;
			}
			else{
				sdrerror("Wrong number of items in array initializer\n");
			}
		}	
	|
		;

slStringParameter:
		SCRL_STRING
		SCRL_IDENTIFIER_VALUE
		{
			currentParameter->type					=	TYPE_STRING;
			currentParameter->name					=	strdup($2);
			currentParameter->defaultValue.array	=	NULL;
			currentParameter->numItems				=	1;
		}
	|
		SCRL_STRING
		SCRL_IDENTIFIER_VALUE
		SCRL_EQUAL
		SCRL_TEXT_VALUE
		{
			currentParameter->type					=	TYPE_STRING;
			currentParameter->name					=	strdup($2);
			currentParameter->defaultValue.string	=	strdup($4);
			currentParameter->numItems				=	1;
		}
	|
		SCRL_STRING
		SCRL_IDENTIFIER_VALUE
		SCRL_OPEN_SQR_PARANTHESIS
		SCRL_FLOAT_VALUE
		SCRL_CLOSE_SQR_PARANTHESIS
		SCRL_EQUAL
		{
			currentParameter->type					=	TYPE_STRING;
			currentParameter->name					=	strdup($2);
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) $4];
			currentParameter->numItems				=	(int) $4;
			
			currentDefaultItem = currentParameter->defaultValue.array;
			numArrayItemsRemaining = currentParameter->numItems;
		}
		slStringArrayInitializer
	|
		SCRL_STRING
		SCRL_IDENTIFIER_VALUE
		SCRL_OPEN_SQR_PARANTHESIS
		SCRL_FLOAT_VALUE
		SCRL_CLOSE_SQR_PARANTHESIS
		{
			currentParameter->type					=	TYPE_STRING;
			currentParameter->name					=	strdup($2);
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) $4];
			currentParameter->numItems				=	(int) $4;
			
			currentDefaultItem = currentParameter->defaultValue.array;
			for(int i=0;i<currentParameter->numItems;i++)
				currentDefaultItem[i].string = NULL;
		}
		;

slStringArrayInitializer:
		SCRL_OPEN_SQR_PARANTHESIS
		slStringArrayInitializerItems
		SCRL_CLOSE_SQR_PARANTHESIS
		{
			if(numArrayItemsRemaining){
				sdrerror("Wrong number of items in array initializer\n");
			}
		}
		;
		
slStringArrayInitializerItems:
		slStringArrayInitializerItems
		SCRL_TEXT_VALUE
		{
			if(numArrayItemsRemaining){
				currentDefaultItem->string = strdup($2);
				currentDefaultItem++;
				numArrayItemsRemaining--;
			}
			else{
				sdrerror("Wrong number of items in array initializer\n");
			}
		}	
	|
		;

slColorParameter:
		SCRL_COLOR
		SCRL_IDENTIFIER_VALUE
		{
			currentParameter->type					=	TYPE_COLOR;
			currentParameter->name					=	strdup($2);
			currentParameter->numItems				=	1;
			
			currentDefaultItem = &currentParameter->defaultValue;
		}
		slVectorInit
		{
		}
		|
		SCRL_COLOR
		SCRL_IDENTIFIER_VALUE
		SCRL_OPEN_SQR_PARANTHESIS
		SCRL_FLOAT_VALUE
		SCRL_CLOSE_SQR_PARANTHESIS
		SCRL_EQUAL
		{
			currentParameter->type					=	TYPE_COLOR;
			currentParameter->name					=	strdup($2);
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) $4];
			currentParameter->numItems				=	(int) $4;
			
			currentDefaultItem = currentParameter->defaultValue.array;
			numArrayItemsRemaining = currentParameter->numItems;
		}
		slVectorArrayInitializer
		|
		SCRL_COLOR
		SCRL_IDENTIFIER_VALUE
		SCRL_OPEN_SQR_PARANTHESIS
		SCRL_FLOAT_VALUE
		SCRL_CLOSE_SQR_PARANTHESIS
		{
			currentParameter->type					=	TYPE_COLOR;
			currentParameter->name					=	strdup($2);
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) $4];
			currentParameter->numItems				=	(int) $4;
			
			currentDefaultItem = currentParameter->defaultValue.array;
			for(int i=0;i<currentParameter->numItems;i++){
				currentDefaultItem[i].vector = new float[3];
				currentDefaultItem[i].vector[0] = 0;
				currentDefaultItem[i].vector[1] = 0;
				currentDefaultItem[i].vector[2] = 0;
			}
		}
		;

slVectorParameter:
		SCRL_VECTOR
		SCRL_IDENTIFIER_VALUE
		{
			currentParameter->type					=	TYPE_VECTOR;
			currentParameter->name					=	strdup($2);
			currentParameter->numItems				=	1;
			
			currentDefaultItem = &currentParameter->defaultValue;
		}
		slVectorInit
		{
		}
		|
		SCRL_VECTOR
		SCRL_IDENTIFIER_VALUE
		SCRL_OPEN_SQR_PARANTHESIS
		SCRL_FLOAT_VALUE
		SCRL_CLOSE_SQR_PARANTHESIS
		SCRL_EQUAL
		{
			currentParameter->type					=	TYPE_VECTOR;
			currentParameter->name					=	strdup($2);
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) $4];
			currentParameter->numItems				=	(int) $4;
			
			currentDefaultItem = currentParameter->defaultValue.array;
			numArrayItemsRemaining = currentParameter->numItems;
		}
		slVectorArrayInitializer
		|
		SCRL_VECTOR
		SCRL_IDENTIFIER_VALUE
		SCRL_OPEN_SQR_PARANTHESIS
		SCRL_FLOAT_VALUE
		SCRL_CLOSE_SQR_PARANTHESIS
		{
			currentParameter->type					=	TYPE_VECTOR;
			currentParameter->name					=	strdup($2);
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) $4];
			currentParameter->numItems				=	(int) $4;
			
			currentDefaultItem = currentParameter->defaultValue.array;
			for(int i=0;i<currentParameter->numItems;i++){
				currentDefaultItem[i].vector = new float[3];
				currentDefaultItem[i].vector[0] = 0;
				currentDefaultItem[i].vector[1] = 0;
				currentDefaultItem[i].vector[2] = 0;
			}
		}
		;

slVectorArrayInitializer:
		SCRL_OPEN_SQR_PARANTHESIS
		slVectorArrayInitializerItems
		SCRL_CLOSE_SQR_PARANTHESIS
		{
			if(numArrayItemsRemaining){
				sdrerror("Wrong number of items in array initializer\n");
		}
		}
		;
		
slVectorArrayInitializerItems:
		slVectorArrayInitializerItems
		{
			if(numArrayItemsRemaining){
				currentDefaultItem->vector = new float[3];
			}
			else{
				sdrerror("Wrong number of items in array initializer\n");
			}
		}
		slVector
		{
			currentDefaultItem++;
			numArrayItemsRemaining--;
		}
	|
		;

slNormalParameter:
		SCRL_NORMAL
		SCRL_IDENTIFIER_VALUE
		{
			currentParameter->type					=	TYPE_NORMAL;
			currentParameter->name					=	strdup($2);
			currentParameter->numItems				=	1;
			
			currentDefaultItem = &currentParameter->defaultValue;
		}
		slVectorInit
		{
		}
		|
		SCRL_NORMAL
		SCRL_IDENTIFIER_VALUE
		SCRL_OPEN_SQR_PARANTHESIS
		SCRL_FLOAT_VALUE
		SCRL_CLOSE_SQR_PARANTHESIS
		SCRL_EQUAL
		{
			currentParameter->type					=	TYPE_NORMAL;
			currentParameter->name					=	strdup($2);
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) $4];
			currentParameter->numItems				=	(int) $4;
			
			currentDefaultItem = currentParameter->defaultValue.array;
			numArrayItemsRemaining = currentParameter->numItems;
		}
		slVectorArrayInitializer
		|
		SCRL_NORMAL
		SCRL_IDENTIFIER_VALUE
		SCRL_OPEN_SQR_PARANTHESIS
		SCRL_FLOAT_VALUE
		SCRL_CLOSE_SQR_PARANTHESIS
		{
			currentParameter->type					=	TYPE_NORMAL;
			currentParameter->name					=	strdup($2);
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) $4];
			currentParameter->numItems				=	(int) $4;
			
			currentDefaultItem = currentParameter->defaultValue.array;
			for(int i=0;i<currentParameter->numItems;i++){
				currentDefaultItem[i].vector = new float[3];
				currentDefaultItem[i].vector[0] = 0;
				currentDefaultItem[i].vector[1] = 0;
				currentDefaultItem[i].vector[3] = 0;
			}
		}
		;

slPointParameter:
		SCRL_POINT
		SCRL_IDENTIFIER_VALUE
		{
			currentParameter->type					=	TYPE_POINT;
			currentParameter->name					=	strdup($2);
			currentParameter->numItems				=	1;
			
			currentDefaultItem = &currentParameter->defaultValue;
		}
		slVectorInit
		{
		}
		|
		SCRL_POINT
		SCRL_IDENTIFIER_VALUE
		SCRL_OPEN_SQR_PARANTHESIS
		SCRL_FLOAT_VALUE
		SCRL_CLOSE_SQR_PARANTHESIS
		SCRL_EQUAL
		{
			currentParameter->type					=	TYPE_POINT;
			currentParameter->name					=	strdup($2);
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) $4];
			currentParameter->numItems				=	(int) $4;
			
			currentDefaultItem = currentParameter->defaultValue.array;
			numArrayItemsRemaining = currentParameter->numItems;
		}
		slVectorArrayInitializer
		|
		SCRL_POINT
		SCRL_IDENTIFIER_VALUE
		SCRL_OPEN_SQR_PARANTHESIS
		SCRL_FLOAT_VALUE
		SCRL_CLOSE_SQR_PARANTHESIS
		{
			currentParameter->type					=	TYPE_POINT;
			currentParameter->name					=	strdup($2);
			currentParameter->defaultValue.array	=	new UDefaultVal[(int) $4];
			currentParameter->numItems				=	(int) $4;
			
			currentDefaultItem = currentParameter->defaultValue.array;
			for(int i=0;i<currentParameter->numItems;i++){
				currentDefaultItem[i].vector	= new float[3];
				currentDefaultItem[i].vector[0] = 0;
				currentDefaultItem[i].vector[1] = 0;
				currentDefaultItem[i].vector[2] = 0;
			}
		}
		;

slMatrixParameter:
		SCRL_MATRIX
		SCRL_IDENTIFIER_VALUE
		SCRL_EQUAL
		SCRL_OPEN_SQR_PARANTHESIS
		SCRL_FLOAT_VALUE
		SCRL_FLOAT_VALUE
		SCRL_FLOAT_VALUE
		SCRL_FLOAT_VALUE
		SCRL_FLOAT_VALUE
		SCRL_FLOAT_VALUE
		SCRL_FLOAT_VALUE
		SCRL_FLOAT_VALUE
		SCRL_FLOAT_VALUE
		SCRL_FLOAT_VALUE
		SCRL_FLOAT_VALUE
		SCRL_FLOAT_VALUE
		SCRL_FLOAT_VALUE
		SCRL_FLOAT_VALUE
		SCRL_FLOAT_VALUE
		SCRL_FLOAT_VALUE
		SCRL_CLOSE_SQR_PARANTHESIS
		{
			currentParameter->container					=	CONTAINER_UNIFORM;
			currentParameter->type						=	TYPE_MATRIX;
			currentParameter->name						=	strdup($2);
			currentParameter->defaultValue.matrix		=	new float[16];
			currentParameter->defaultValue.matrix[0]	=	$5;
			currentParameter->defaultValue.matrix[1]	=	$6;
			currentParameter->defaultValue.matrix[2]	=	$7;
			currentParameter->defaultValue.matrix[3]	=	$8;
			currentParameter->defaultValue.matrix[4]	=	$9;
			currentParameter->defaultValue.matrix[5]	=	$10;
			currentParameter->defaultValue.matrix[6]	=	$11;
			currentParameter->defaultValue.matrix[7]	=	$12;
			currentParameter->defaultValue.matrix[8]	=	$13;
			currentParameter->defaultValue.matrix[9]	=	$14;
			currentParameter->defaultValue.matrix[10]	=	$15;
			currentParameter->defaultValue.matrix[11]	=	$16;
			currentParameter->defaultValue.matrix[12]	=	$17;
			currentParameter->defaultValue.matrix[13]	=	$18;
			currentParameter->defaultValue.matrix[14]	=	$19;
			currentParameter->defaultValue.matrix[15]	=	$20;
			currentParameter->numItems					=	1;
		}
	|
		SCRL_MATRIX
		SCRL_IDENTIFIER_VALUE
		SCRL_EQUAL
		SCRL_FLOAT_VALUE
		{
			currentParameter->container					=	CONTAINER_UNIFORM;
			currentParameter->type						=	TYPE_MATRIX;
			currentParameter->name						=	strdup($2);
			currentParameter->defaultValue.matrix		=	new float[16];
			currentParameter->defaultValue.matrix[0]	=	$4;
			currentParameter->defaultValue.matrix[1]	=	0;
			currentParameter->defaultValue.matrix[2]	=	0;
			currentParameter->defaultValue.matrix[3]	=	0;
			currentParameter->defaultValue.matrix[4]	=	0;
			currentParameter->defaultValue.matrix[5]	=	$4;
			currentParameter->defaultValue.matrix[6]	=	0;
			currentParameter->defaultValue.matrix[7]	=	0;
			currentParameter->defaultValue.matrix[8]	=	0;
			currentParameter->defaultValue.matrix[9]	=	0;
			currentParameter->defaultValue.matrix[10]	=	$4;
			currentParameter->defaultValue.matrix[11]	=	0;
			currentParameter->defaultValue.matrix[12]	=	0;
			currentParameter->defaultValue.matrix[13]	=	0;
			currentParameter->defaultValue.matrix[14]	=	0;
			currentParameter->defaultValue.matrix[15]	=	$4;
			currentParameter->numItems					=	1;
		}
	|
		SCRL_MATRIX
		SCRL_IDENTIFIER_VALUE
		{
			currentParameter->container					=	CONTAINER_UNIFORM;
			currentParameter->type						=	TYPE_MATRIX;
			currentParameter->name						=	strdup($2);
			currentParameter->defaultValue.matrix		=	new float[16];
			currentParameter->defaultValue.matrix[0]	=	1;
			currentParameter->defaultValue.matrix[1]	=	0;
			currentParameter->defaultValue.matrix[2]	=	0;
			currentParameter->defaultValue.matrix[3]	=	0;
			currentParameter->defaultValue.matrix[4]	=	0;
			currentParameter->defaultValue.matrix[5]	=	1;
			currentParameter->defaultValue.matrix[6]	=	0;
			currentParameter->defaultValue.matrix[7]	=	0;
			currentParameter->defaultValue.matrix[8]	=	0;
			currentParameter->defaultValue.matrix[9]	=	0;
			currentParameter->defaultValue.matrix[10]	=	1;
			currentParameter->defaultValue.matrix[11]	=	0;
			currentParameter->defaultValue.matrix[12]	=	0;
			currentParameter->defaultValue.matrix[13]	=	0;
			currentParameter->defaultValue.matrix[14]	=	0;
			currentParameter->defaultValue.matrix[15]	=	1;
			currentParameter->numItems					=	1;
		}
	|
		SCRL_MATRIX
		SCRL_IDENTIFIER_VALUE
		SCRL_OPEN_SQR_PARANTHESIS
		SCRL_FLOAT_VALUE
		SCRL_CLOSE_SQR_PARANTHESIS
		SCRL_EQUAL
		{
			currentParameter->container					=	CONTAINER_UNIFORM;
			currentParameter->type						=	TYPE_MATRIX;
			currentParameter->name						=	strdup($2);
			currentParameter->defaultValue.array		=	new UDefaultVal[(int) $4];
			currentParameter->numItems					=	(int) $4;
			
			currentDefaultItem = currentParameter->defaultValue.array;
			numArrayItemsRemaining = currentParameter->numItems;
		}
		slMatrixArrayInitializer
	|
		SCRL_MATRIX
		SCRL_IDENTIFIER_VALUE
		SCRL_OPEN_SQR_PARANTHESIS
		SCRL_FLOAT_VALUE
		SCRL_CLOSE_SQR_PARANTHESIS
		{
			currentParameter->container					=	CONTAINER_UNIFORM;
			currentParameter->type						=	TYPE_MATRIX;
			currentParameter->name						=	strdup($2);
			currentParameter->defaultValue.array		=	new UDefaultVal[(int) $4];
			currentParameter->numItems					=	(int) $4;
			
			currentDefaultItem = currentParameter->defaultValue.array;
			for(int i=0;i<currentParameter->numItems;i++){
				currentDefaultItem[i].matrix = new float[16];
				currentDefaultItem[i].matrix[0] = 1;
				currentDefaultItem[i].matrix[1] = 0;
				currentDefaultItem[i].matrix[2] = 0;
				currentDefaultItem[i].matrix[3] = 0;
				currentDefaultItem[i].matrix[4] = 0;
				currentDefaultItem[i].matrix[5] = 1;
				currentDefaultItem[i].matrix[6] = 0;
				currentDefaultItem[i].matrix[7] = 0;
				currentDefaultItem[i].matrix[8] = 0;
				currentDefaultItem[i].matrix[9] = 0;
				currentDefaultItem[i].matrix[10] = 1;
				currentDefaultItem[i].matrix[11] = 0;
				currentDefaultItem[i].matrix[12] = 0;
				currentDefaultItem[i].matrix[13] = 0;
				currentDefaultItem[i].matrix[14] = 0;
				currentDefaultItem[i].matrix[15] = 1;
			}
		}
		;

slMatrixArrayInitializer:
		SCRL_OPEN_SQR_PARANTHESIS
		slMatrixArrayInitializerItems
		SCRL_CLOSE_SQR_PARANTHESIS
		{
			if(numArrayItemsRemaining){
				sdrerror("Wrong number of items in array initializer\n");
			}
		}
		;
		
slMatrixArrayInitializerItems:
		slMatrixArrayInitializerItems
		SCRL_OPEN_SQR_PARANTHESIS
		SCRL_FLOAT_VALUE
		SCRL_FLOAT_VALUE
		SCRL_FLOAT_VALUE
		SCRL_FLOAT_VALUE
		SCRL_FLOAT_VALUE
		SCRL_FLOAT_VALUE
		SCRL_FLOAT_VALUE
		SCRL_FLOAT_VALUE
		SCRL_FLOAT_VALUE
		SCRL_FLOAT_VALUE
		SCRL_FLOAT_VALUE
		SCRL_FLOAT_VALUE
		SCRL_FLOAT_VALUE
		SCRL_FLOAT_VALUE
		SCRL_FLOAT_VALUE
		SCRL_FLOAT_VALUE
		SCRL_CLOSE_SQR_PARANTHESIS
		{
			if(numArrayItemsRemaining){
				currentDefaultItem->matrix = new float[16];
				currentDefaultItem->matrix[0] = $3;
				currentDefaultItem->matrix[1] = $4;
				currentDefaultItem->matrix[2] = $5;
				currentDefaultItem->matrix[3] = $6;
				currentDefaultItem->matrix[4] = $7;
				currentDefaultItem->matrix[5] = $8;
				currentDefaultItem->matrix[6] = $9;
				currentDefaultItem->matrix[7] = $10;
				currentDefaultItem->matrix[8] = $11;
				currentDefaultItem->matrix[9] = $12;
				currentDefaultItem->matrix[10] = $13;
				currentDefaultItem->matrix[11] = $14;
				currentDefaultItem->matrix[12] = $15;
				currentDefaultItem->matrix[13] = $16;
				currentDefaultItem->matrix[14] = $17;
				currentDefaultItem->matrix[15] = $18;
				
				currentDefaultItem++;
				numArrayItemsRemaining--;
			}
			else{
				sdrerror("Wrong number of items in array initializer\n");
			}
		}	
	|
		slMatrixArrayInitializerItems
		SCRL_FLOAT_VALUE
		{
			if(numArrayItemsRemaining){
				currentDefaultItem->matrix = new float[16];
				currentDefaultItem->matrix[0] = $2;
				currentDefaultItem->matrix[1] = 0;
				currentDefaultItem->matrix[2] = 0;
				currentDefaultItem->matrix[3] = 0;
				currentDefaultItem->matrix[4] = 0;
				currentDefaultItem->matrix[5] = $2;
				currentDefaultItem->matrix[6] = 0;
				currentDefaultItem->matrix[7] = 0;
				currentDefaultItem->matrix[8] = 0;
				currentDefaultItem->matrix[9] = 0;
				currentDefaultItem->matrix[10] = $2;
				currentDefaultItem->matrix[11] = 0;
				currentDefaultItem->matrix[12] = 0;
				currentDefaultItem->matrix[13] = 0;
				currentDefaultItem->matrix[14] = 0;
				currentDefaultItem->matrix[15] = 1;
				
				currentDefaultItem++;
				numArrayItemsRemaining--;
			}
		}
	|
		;

slVariableDefinitions:
		SCRL_VARIABLES
		SCRL_COLON
		SCRL_NL
		slVariables
		;

slVariables:
		slVariables
		slVariable
	|
		;

slVariable:
		slContainer
		slBooleanVariable
		SCRL_NL
	|
		slContainer
		slFloatVariable
		SCRL_NL
	|
		slContainer
		slStringVariable
		SCRL_NL
	|
		slContainer
		slColorVariable
		SCRL_NL
	|
		slContainer
		slVectorVariable
		SCRL_NL
	|
		slContainer
		slNormalVariable
		SCRL_NL
	|
		slContainer
		slPointVariable
		SCRL_NL
	|
		slContainer
		slMatrixVariable
		SCRL_NL
		;

slBooleanVariable:
		SCRL_BOOLEAN
		SCRL_IDENTIFIER_VALUE
		{
		}
	|
		SCRL_BOOLEAN
		SCRL_IDENTIFIER_VALUE
		SCRL_OPEN_SQR_PARANTHESIS
		SCRL_FLOAT_VALUE
		SCRL_CLOSE_SQR_PARANTHESIS
		{
		}
		;


slFloatVariable:
		SCRL_FLOAT
		SCRL_IDENTIFIER_VALUE
		{
		}
	|
		SCRL_FLOAT
		SCRL_IDENTIFIER_VALUE
		SCRL_OPEN_SQR_PARANTHESIS
		SCRL_FLOAT_VALUE
		SCRL_CLOSE_SQR_PARANTHESIS
		{
		}
		;

slStringVariable:
		SCRL_STRING
		SCRL_IDENTIFIER_VALUE
		{
		}
	|
		SCRL_STRING
		SCRL_IDENTIFIER_VALUE
		SCRL_OPEN_SQR_PARANTHESIS
		SCRL_FLOAT_VALUE
		SCRL_CLOSE_SQR_PARANTHESIS
		{
		}
		;

slVectorVariable:
		SCRL_VECTOR
		SCRL_IDENTIFIER_VALUE
		{
		}
	|
		SCRL_VECTOR
		SCRL_IDENTIFIER_VALUE
		SCRL_OPEN_SQR_PARANTHESIS
		SCRL_FLOAT_VALUE
		SCRL_CLOSE_SQR_PARANTHESIS
		{
		}
		;

slColorVariable:
		SCRL_COLOR
		SCRL_IDENTIFIER_VALUE
		{
		}
	|
		SCRL_COLOR
		SCRL_IDENTIFIER_VALUE
		SCRL_OPEN_SQR_PARANTHESIS
		SCRL_FLOAT_VALUE
		SCRL_CLOSE_SQR_PARANTHESIS
		{
		}
		;

slNormalVariable:
		SCRL_NORMAL
		SCRL_IDENTIFIER_VALUE
		{
		}
	|
		SCRL_NORMAL
		SCRL_IDENTIFIER_VALUE
		SCRL_OPEN_SQR_PARANTHESIS
		SCRL_FLOAT_VALUE
		SCRL_CLOSE_SQR_PARANTHESIS
		{
		}
		;

slPointVariable:
		SCRL_POINT
		SCRL_IDENTIFIER_VALUE
		{
		}
	|
		SCRL_POINT
		SCRL_IDENTIFIER_VALUE
		SCRL_OPEN_SQR_PARANTHESIS
		SCRL_FLOAT_VALUE
		SCRL_CLOSE_SQR_PARANTHESIS
		{
		}
		;

slMatrixVariable:
		SCRL_MATRIX
		SCRL_IDENTIFIER_VALUE
		{
		}
	|
		SCRL_MATRIX
		SCRL_IDENTIFIER_VALUE
		SCRL_OPEN_SQR_PARANTHESIS
		SCRL_FLOAT_VALUE
		SCRL_CLOSE_SQR_PARANTHESIS
		{
		}
		;

slCode:
		slCode
		slStatement
		SCRL_NL
	|
		slCode
		slLabelDefinition
		SCRL_NL
	|
		slCode
		slDSO
		SCRL_NL
	|
		;


slDSO:	SCRL_DSO
		SCRL_IDENTIFIER_VALUE
		{
		}
		SCRL_OPEN_PARANTHESIS
		SCRL_TEXT_VALUE
		SCRL_CLOSE_PARANTHESIS
		slOperandList
		{
		}
		;

slOpcode:
		SCRL_IDENTIFIER_VALUE
		{
		}
		|
		SCRL_DISPLACEMENT
		{
		}
		|
		SCRL_SURFACE
		{
		}
		;

slOperandList:
		slOperand
		slOperandList
		{
		}
		|
		{
		}
		;

slStatement:
		slOpcode
		slOperandList
		{
		}
		;

slLabelDefinition:
		SCRL_LABEL_VALUE
		SCRL_COLON
		{
		}
		;

slOperand:
		SCRL_TEXT_VALUE
		{
		}
	|
		SCRL_LABEL_VALUE
		{
		}
	|
		SCRL_IDENTIFIER_VALUE
		{
		}
	|
		SCRL_FLOAT_VALUE
		{
		}
	|
		SCRL_OPEN_PARANTHESIS
		SCRL_FLOAT_VALUE
		SCRL_COMMA
		SCRL_FLOAT_VALUE
		SCRL_COMMA
		SCRL_FLOAT_VALUE
		SCRL_CLOSE_PARANTHESIS
		{
		}
	|
		SCRL_OPEN_PARANTHESIS
		SCRL_FLOAT_VALUE
		SCRL_COMMA
		SCRL_FLOAT_VALUE
		SCRL_COMMA
		SCRL_FLOAT_VALUE
		SCRL_COMMA
		SCRL_FLOAT_VALUE
		SCRL_COMMA
		SCRL_FLOAT_VALUE
		SCRL_COMMA
		SCRL_FLOAT_VALUE
		SCRL_COMMA
		SCRL_FLOAT_VALUE
		SCRL_COMMA
		SCRL_FLOAT_VALUE
		SCRL_COMMA
		SCRL_FLOAT_VALUE
		SCRL_COMMA
		SCRL_FLOAT_VALUE
		SCRL_COMMA
		SCRL_FLOAT_VALUE
		SCRL_COMMA
		SCRL_FLOAT_VALUE
		SCRL_COMMA
		SCRL_FLOAT_VALUE
		SCRL_COMMA
		SCRL_FLOAT_VALUE
		SCRL_COMMA
		SCRL_FLOAT_VALUE
		SCRL_COMMA
		SCRL_FLOAT_VALUE
		SCRL_CLOSE_PARANTHESIS
		{
		}
		|
		SCRL_OPEN_PARANTHESIS
		SCRL_TEXT_VALUE
		SCRL_CLOSE_PARANTHESIS
		{
		}
		;

%%
#include "lex.sdr.cpp"

int	slLineno	=	0;

///////////////////////////////////////////////////////////////////////
// Function				:	sdrerror
// Description			:	Parser error function
// Return Value			:
// Comments				:
void			sdrerror(const char *s) {
	fprintf(stdout,"%s\n",s);
}


///////////////////////////////////////////////////////////////////////
// Function				:	sdrGet
// Description			:	Parse a shader
// Return Value			:
// Comments				:
TSdrShader		*sdrGet(const char *in,const char *searchpath) {
	TSdrShader		*cShader;
	char			tmp[512];
	const	char	*currentPath;
	char			*dest;

	sdrin	=	fopen(in,"r");

	if (sdrin == NULL) {
		if (searchpath != NULL) {
			for (dest=tmp,currentPath=searchpath;;) {
				if ((*currentPath == '\0') || (*currentPath == ':')) {		// End of the current path

					if ((dest - tmp) > 0) {		// Do we have anything to record ?
						dest--;

						if ((*dest == '/') || (*dest == '\\')) {	// The last character has to be a slash
							dest++;
						} else {
							dest++;
							*dest++	=	'/';
						}

						sprintf(dest,in);
						if (strstr(dest,".sdr") == NULL) {
							strcat(dest,".sdr");
						}

						osFixSlashes(tmp);

						if (strncmp(tmp,"\\\\",2) == 0) {
							tmp[1]	=	tmp[2];
							tmp[2]	=	':';
							tmp[3]	=	'\\';

							sdrin	=	fopen(tmp+1,"r");
						} else {
							sdrin	=	fopen(tmp,"r");
						}

						if (sdrin != NULL)	break;
					}

					dest			=	tmp;

					if (*currentPath == '\0')	break;

					currentPath++;
				} else if (*currentPath == '%') {
					const	char	*endOfCurrentPath	=	strchr(currentPath+1,'%');
					char			environmentVariable[OS_MAX_PATH_LENGTH];

					if (endOfCurrentPath!=NULL) {
						const	int		environmentLength	=	(int) (endOfCurrentPath - currentPath) - 1;
						const	char	*value;

						strncpy(environmentVariable,currentPath+1,environmentLength);
						environmentVariable[environmentLength]	=	'\0';

						value		=	osEnvironment(environmentVariable);
						if (value != NULL) {
							strcpy(dest,value);
							dest	+=	strlen(value);
						}

						currentPath	=	endOfCurrentPath+1;
					} else {
						currentPath++;
					}
				} else if ((*currentPath == '@') || (*currentPath == '&')) {
					currentPath++;
				} else {
					*dest++	=	*currentPath++;
				}
			}
		}
	}

	if (sdrin == NULL)	return NULL;

	parameters	=	NULL;

	sdrparse();

	fclose(sdrin);

	cShader	=	new TSdrShader;

	cShader->name		=	strdup(in);
	cShader->type		=	shaderType;
	cShader->parameters	=	parameters;

	return cShader;
}

///////////////////////////////////////////////////////////////////////
// Function				:	sdrDelete
// Description			:	Delete a shader
// Return Value			:
// Comments				:
void			sdrDelete(TSdrShader *cShader) {
	TSdrParameter	*cParameter;

	while((cParameter = cShader->parameters) != NULL) {
		cShader->parameters	=	cParameter->next;

		free(cParameter->name);
		if (cParameter->space != NULL) {
			free(cParameter->space);
		}

		if (cParameter->numItems == 1) {
			switch(cParameter->type) {
			case TYPE_FLOAT:
				break;
			case TYPE_VECTOR:
			case TYPE_NORMAL:
			case TYPE_POINT:
			case TYPE_COLOR:
				if (cParameter->defaultValue.vector != NULL) {
					delete [] cParameter->defaultValue.vector;
				}
				break;
			case TYPE_MATRIX:
				if (cParameter->defaultValue.matrix != NULL) {
					delete [] cParameter->defaultValue.matrix;
				}
				break;
			case TYPE_STRING:
				if (cParameter->defaultValue.string != NULL) {
					free(cParameter->defaultValue.string);
				}
				break;
			}
		}

		delete cParameter;
	}

	free(cShader->name);
	delete cShader;
}

