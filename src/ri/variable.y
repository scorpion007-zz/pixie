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
//  File				:	variable.y
//  Classes				:	-
//  Description			:	Parse a variable declaration
//
////////////////////////////////////////////////////////////////////////
#undef alloca
#include	<math.h>

#include	"common/global.h"
#include	"common/containers.h"
#include	"renderer.h"
#include	"error.h"
#include	"ri_config.h"

#define YYPRINT(file, type, value) print_token_value (file, type, value)

void
varerror(const char *);

int
varlex(void);

static	CVariable	*currentVariable;
static	const char	*currentName;
static	const char	*currentDecl;
%}

// Stack type.
//
%union varval {
	float	real;
}

%{
static void
print_token_value (FILE *, int, YYSTYPE);
%}

%token	VAR_GLOBAL
%token	VAR_CONSTANT
%token	VAR_UNIFORM
%token	VAR_VARYING
%token	VAR_FACEVARYING
%token	VAR_VERTEX
%token	VAR_INTEGER
%token	VAR_VECTOR
%token	VAR_COLOR
%token	VAR_NORMAL
%token	VAR_POINT
%token	VAR_HTPOINT
%token	VAR_MATRIX
%token	VAR_DOUBLE
%token	VAR_STRING
%token	VAR_POINTER
%token	VAR_OPEN
%token	VAR_CLOSE
%token <real>	VAR_FLOAT
%token	VAR_IDENTIFIER
%%
start:	varStorage
		varType
		varItems
		varName
		{
		}
		;

varGlobalMarker:	
			VAR_GLOBAL
			{
				currentVariable->storage	=	STORAGE_GLOBAL;
			}
			|
			{
				currentVariable->storage	=	STORAGE_NONE;
			}
			;

varStorage:	varGlobalMarker
			VAR_CONSTANT
			{
				currentVariable->container	=	CONTAINER_CONSTANT;
			}
			|
			varGlobalMarker
			VAR_UNIFORM
			{
				currentVariable->container	=	CONTAINER_UNIFORM;
			}
			|
			varGlobalMarker
			VAR_VARYING
			{
				currentVariable->container	=	CONTAINER_VARYING;
			}
			|
			varGlobalMarker
			VAR_FACEVARYING
			{
				currentVariable->container	=	CONTAINER_FACEVARYING;
			}
			|
			varGlobalMarker
			VAR_VERTEX
			{
				currentVariable->container	=	CONTAINER_VERTEX;
			}
			|
			varGlobalMarker
			{
                // The default storage type.
                //
				currentVariable->container	=	CONTAINER_VERTEX;
			}
			;

varType:	VAR_INTEGER
			{
				currentVariable->type			=	TYPE_INTEGER;
				currentVariable->numFloats		=	1;
			} |
			VAR_FLOAT
			{
				currentVariable->type			=	TYPE_FLOAT;
				currentVariable->numFloats		=	1;
			} |
			VAR_VECTOR
			{
				currentVariable->type			=	TYPE_VECTOR;
				currentVariable->numFloats		=	3;
			} |
			VAR_COLOR
			{
				currentVariable->type			=	TYPE_COLOR;
				currentVariable->numFloats		=	3;
			} |
			VAR_NORMAL
			{
				currentVariable->type			=	TYPE_NORMAL;
				currentVariable->numFloats		=	3;
			} |
			VAR_POINT
			{
				currentVariable->type			=	TYPE_POINT;
				currentVariable->numFloats		=	3;
			} |
			VAR_MATRIX
			{
				currentVariable->type			=	TYPE_MATRIX;
				currentVariable->numFloats		=	16;
			} |
			VAR_HTPOINT
			{
				currentVariable->type			=	TYPE_QUAD;
				currentVariable->numFloats		=	4;
			} |
			VAR_DOUBLE
			{
				currentVariable->type			=	TYPE_DOUBLE;
				currentVariable->numFloats		=	2;
			} |
			VAR_STRING
			{
				currentVariable->type			=	TYPE_STRING;
				currentVariable->numFloats		=	1;
			} |
			VAR_POINTER
			{
				currentVariable->type			=	TYPE_POINTER;
				currentVariable->numFloats		=	1;
			} ;

varName:	VAR_IDENTIFIER
			|
			{
				strcpy(currentVariable->name,"");
			}
			;

// Array types.
//
// E.g. float [ 5 ]
//
varItems:	VAR_OPEN
			VAR_FLOAT
			VAR_CLOSE
			{
				currentVariable->numItems	=	(int) $2;
				currentVariable->numFloats	*=	currentVariable->numItems;
			}
			|
			{
                // If no type [ N ] syntax is provided, default to scalar.
                //
				currentVariable->numItems	=	1;
			}
			;
%%

#include	"lex.var.cpp"

static	int	numErrors	=	0;

void
varerror(const char *str)
{
	// error(CODE_BADTOKEN,"Variable declaration error \"%s\" \"%s\"\n",
	//  (currentName == NULL ? "NULL" : currentName),currentDecl);

    printf("Variable declaration error \"%s\" \"%s\"\n",
        currentName ? currentName : "(null)",
        currentDecl);

	numErrors++;
}


///////////////////////////////////////////////////////////////////////
// Function				:	sfParseVariable
// Description			:	Parse a variable but do not commit it into the global variables
// Return Value			:
// Comments				:
int	
parseVariable(
    CVariable  *var,  // out
    const char *name, // in
    const char *decl) // in
{
#if YYDEBUG=1
	// Turn on parser debug output.
	//
    vardebug = 1;
#endif

	CVariable		*savedVariable;
	const char		*savedName;
	const char		*savedDecl;

	YY_BUFFER_STATE savedState	=	YY_CURRENT_BUFFER;
	YY_BUFFER_STATE	newState;

	numErrors		=	0;

    // Backup the current variable.
    //
	savedVariable	=	currentVariable;
	savedName		=	currentName;
	savedDecl		=	currentDecl;

    // Set the new current variable.
    //
	currentVariable	=	var;
	currentName		=	name;
	currentDecl		=	decl;

	newState	=	var_scan_string(decl);
	varparse();
	var_delete_buffer(newState);

	var_switch_to_buffer( savedState );

    // Revert to the previous variable.
    //
	currentVariable	=	savedVariable;
	currentName		=	savedName;
	currentDecl		=	savedDecl;

    // Check for parsing errors.
    //
	if (numErrors == 0)
    {
		if (name)
        {
            // TODO: address unsafe API.
            //
        	strcpy(var->name, name);
        }

		return TRUE;
	}

	return FALSE;
}

//------------------------------------------------------------------------------
// Function: print_token_value
//
// Description:
//
//  Print the value (image) of one token as encountered by the parser.
//  Most tokens don't have an image.
//
// Returns:
//
//  void.
//
void
print_token_value (FILE *file, int type, YYSTYPE value)
{
    // The goal of this routine is to visualize the value of the current variable.
    //
    // We use both the stack type (%union) and the global CVariable 'currentVariable'
    // to represent the current value being parsed.
    //
    // TODO: Consider how we can use the single stack type to encapsulate this.
    //
    if (type == VAR_FLOAT)
    {
    	fprintf(file, "%f", value.real);
    }
}
