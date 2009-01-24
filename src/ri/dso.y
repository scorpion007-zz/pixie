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
//  File				:	dso.y
//  Classes				:	-
//  Description			:	Dso parser
//
////////////////////////////////////////////////////////////////////////
#undef alloca
#include <string.h>

#include "common/os.h"
#include "ri_config.h"

int								dsolex(void );				// Forward definition for stupid yacc
void							dsoerror(const char *,...);

static	char					nameBuffer[256];
static	char					prototypeBuffer[256];
static	char					*currentPrototype;
static	char					*funName;
static	int						numErrors;

%}
%union slval {
	char	*string;
}
%token	DSO_VOID
%token	DSO_FLOAT
%token	DSO_VECTOR
%token	DSO_NORMAL
%token	DSO_POINT
%token	DSO_COLOR
%token	DSO_MATRIX
%token	DSO_STRING
%token	DSO_OPEN
%token	DSO_CLOSE
%token<string>	DSO_TEXT
%token	DSO_COMMA
%%
start:			{
					currentPrototype	=	prototypeBuffer;
				}
				dsoType
				DSO_TEXT
				{
					*currentPrototype++	=	'=';
					funName	=	$3;		// Save the name of the function
				}
				DSO_OPEN
				dsoPL
				DSO_CLOSE
				;

dsoPL:			dsoParameters
				|
				;

dsoParameters:	dsoParameter
				|
				dsoParameter
				DSO_COMMA
				dsoParameters
				;

dsoParameter:
				dsoType
				|
				dsoType
				DSO_TEXT
				{
					// We're not using the parameter
					free($2);
				}
				;

dsoType:		DSO_VOID
				{
					*currentPrototype++	=	'o';
				}
				|
				DSO_FLOAT
				{
					*currentPrototype++	=	'f';
				}
				|
				DSO_VECTOR
				{
					*currentPrototype++	=	'v';
				}
				|
				DSO_NORMAL
				{
					*currentPrototype++	=	'n';
				}
				|
				DSO_POINT
				{
					*currentPrototype++	=	'p';
				}
				|
				DSO_COLOR
				{
					*currentPrototype++	=	'c';
				}
				|
				DSO_MATRIX
				{
					*currentPrototype++	=	'm';
				}
				|
				DSO_STRING
				{
					*currentPrototype++	=	's';
				}
				;
%%

#include "lex.dso.cpp"


///////////////////////////////////////////////////////////////////////
// Function				:	parseDSO
// Description			:	Parse a parameter list and extract the function
// Return Value			:	TRUE on success, FALSE othervise
// Comments				:
int		dsoParse(const char *decl,char *&name,char *&prototype) {
	YY_BUFFER_STATE savedState	=	YY_CURRENT_BUFFER;		// Save the old buffer
	YY_BUFFER_STATE	newState;

	numErrors		=	0;

	newState		=	dso_scan_string(decl);				// Create a new buffer
	dsoparse();												// Scan the buffer
	dso_delete_buffer(newState);							// Ditch the buffer

	dso_switch_to_buffer( savedState );						// Switch to the old buffer

	if (numErrors == 0) {
		name		=	funName;
		prototype	=	strdup(prototypeBuffer);
		return TRUE;
	}

	return FALSE;
}

///////////////////////////////////////////////////////////////////////
// Function				:	dsoerror
// Description			:	Count the parse errors
// Return Value			:
// Comments				:
void	dsoerror(const char *,...) {
	numErrors++;
}

