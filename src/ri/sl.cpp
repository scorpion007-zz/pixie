/* A Bison parser, made by GNU Bison 1.875c.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0

/* If NAME_PREFIX is specified substitute the variables and functions
   names.  */
#define yyparse slparse
#define yylex   sllex
#define yyerror slerror
#define yylval  sllval
#define yychar  slchar
#define yydebug sldebug
#define yynerrs slnerrs


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     SCRL_PARAMETERS = 258,
     SCRL_VARIABLES = 259,
     SCRL_OUTPUT = 260,
     SCRL_VARYING = 261,
     SCRL_UNIFORM = 262,
     SCRL_BOOLEAN = 263,
     SCRL_FLOAT = 264,
     SCRL_COLOR = 265,
     SCRL_VECTOR = 266,
     SCRL_NORMAL = 267,
     SCRL_POINT = 268,
     SCRL_MATRIX = 269,
     SCRL_STRING = 270,
     SCRL_SURFACE = 271,
     SCRL_DISPLACEMENT = 272,
     SCRL_IMAGER = 273,
     SCRL_LIGHTSOURCE = 274,
     SCRL_VOLUME = 275,
     SCRL_GENERIC = 276,
     SCRL_DSO = 277,
     SCRL_INIT = 278,
     SCRL_CODE = 279,
     SCRL_DOT = 280,
     SCRL_COLON = 281,
     SCRL_EQUAL = 282,
     SCRL_OPEN_PARANTHESIS = 283,
     SCRL_CLOSE_PARANTHESIS = 284,
     SCRL_OPEN_SQR_PARANTHESIS = 285,
     SCRL_CLOSE_SQR_PARANTHESIS = 286,
     SCRL_COMMA = 287,
     SCRL_NL = 288,
     SCRL_TEXT_VALUE = 289,
     SCRL_IDENTIFIER_VALUE = 290,
     SCRL_LABEL_VALUE = 291,
     SCRL_FLOAT_VALUE = 292
   };
#endif
#define SCRL_PARAMETERS 258
#define SCRL_VARIABLES 259
#define SCRL_OUTPUT 260
#define SCRL_VARYING 261
#define SCRL_UNIFORM 262
#define SCRL_BOOLEAN 263
#define SCRL_FLOAT 264
#define SCRL_COLOR 265
#define SCRL_VECTOR 266
#define SCRL_NORMAL 267
#define SCRL_POINT 268
#define SCRL_MATRIX 269
#define SCRL_STRING 270
#define SCRL_SURFACE 271
#define SCRL_DISPLACEMENT 272
#define SCRL_IMAGER 273
#define SCRL_LIGHTSOURCE 274
#define SCRL_VOLUME 275
#define SCRL_GENERIC 276
#define SCRL_DSO 277
#define SCRL_INIT 278
#define SCRL_CODE 279
#define SCRL_DOT 280
#define SCRL_COLON 281
#define SCRL_EQUAL 282
#define SCRL_OPEN_PARANTHESIS 283
#define SCRL_CLOSE_PARANTHESIS 284
#define SCRL_OPEN_SQR_PARANTHESIS 285
#define SCRL_CLOSE_SQR_PARANTHESIS 286
#define SCRL_COMMA 287
#define SCRL_NL 288
#define SCRL_TEXT_VALUE 289
#define SCRL_IDENTIFIER_VALUE 290
#define SCRL_LABEL_VALUE 291
#define SCRL_FLOAT_VALUE 292




/* Copy the first part of user declarations.  */
#line 1 "sdr.y"

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

#include "common/global.h"
#include "common/containers.h"
#include "shader.h"
#include "slcode.h"
#include "error.h"
#include "renderer.h"
#include "dso.h"

/////////////////////////////////////////////////////////////////////////////////////
//   First some temporary data structures used during the script parsing


// Some forward definitions
		void							slerror(char *);			// Forward definition for stupid yacc
		int								sllex(void );				// Forward definition for stupid yacc

		const	char					*initLabel	=	"#!Init";	// The label for the init
		const	char					*codeLabel	=	"#!Code";	// The label for the code

typedef struct TSlVariable {
	char			name[64];
	int				index;
	int				multiplicity;
	EVariableType	type;
	EVariableClass	container;
	int				uniform;
	CVariable		*variable;
	TSlVariable		*next;
} TSlVariable;

typedef struct TSlLabel {
	char			name[64];
	int				index;
	TArgument		*argument;
	TSlLabel		*next;
} TSlLabel;

typedef struct {
	ESlCode			entryPoint;
	char			*name;
	int				nargs;
	unsigned int	usedParameters;
} TSlOpcode;

typedef struct {
	ESlCode			entryPoint;
	char			*name;
	char			*prototype;
	unsigned int	usedParameters;
} TSlFunction;

#define	DEFOPCODE(name,text,nargs,expr_pre,expr,expr_update,expr_post,params)			{OPCODE_##name,text,nargs,params},
#define	DEFSHORTOPCODE(name,text,nargs,expr_pre,expr,expr_update,expr_post,params)		{OPCODE_##name,text,nargs,params},
#define	DEFLINKOPCODE(name,text,nargs)													{OPCODE_##name,text,nargs,0},
#define	DEFFUNC(name,text,prototype,expr_pre,expr,expr_update,expr_post,par)
#define	DEFLIGHTFUNC(name,text,prototype,expr_pre,expr,expr_update,expr_post,par)
#define	DESHORTFFUNC(name,text,prototype,expr_pre,expr,expr_update,expr_post,par)
#define	DEFLINKFUNC(name,text,prototype,par)

static	TSlOpcode	opcodes[]	=	{
#include "scriptOpcodes.h"
{	OPCODE_NOP	,	NULL	,	0	}
};

#undef DEFOPCODE
#undef DEFSHORTOPCODE
#undef DEFLINKOPCODE
#undef DEFFUNC
#undef DEFLIGHTFUNC
#undef DEFSHORTFUNC
#undef DEFLINKFUNC

#define	DEFOPCODE(name,text,nargs,expr_pre,expr,expr_update,expr_post)
#define	DEFSHORTOPCODE(name,text,nargs,expr_pre,expr,expr_update,expr_post)
#define DEFLINKOPCODE(name,text,nargs)
#define	DEFFUNC(name,text,prototype,expr_pre,expr,expr_update,expr_post,par)			{FUNCTION_##name,text,prototype,par},
#define	DEFLIGHTFUNC(name,text,prototype,expr_pre,expr,expr_update,expr_post,par)		{FUNCTION_##name,text,prototype,par},
#define	DEFSHORTFUNC(name,text,prototype,expr_pre,expr,expr_update,expr_post,par)		{FUNCTION_##name,text,prototype,par},
#define	DEFLINKFUNC(name,text,prototype,par)											{FUNCTION_##name,text,prototype,par},
static	TSlFunction		functions[]	=	{
#include "scriptFunctions.h"
{	OPCODE_NOP	,	NULL	,	NULL	}
};


#undef DEFOPCODE
#undef DEFSHORTOPCODE
#undef DEFLINKOPCODE
#undef DEFFUNC
#undef DEFSHORTFUNC
#undef DEFLINKFUNC


		////////////////////////////////////////////////////////////////////////////////////////////////////
		//
		//	This structure holds the compiling context
		//
		//
		typedef struct {
				const char				*name;					// Name of the file being parsed
				int						passNumber;				// Current pass number (we make 2 passes)
				int						parsingInit;			// TRUE if we're parsing the init code
				int						numErrors;				// Number of errors encountered during parse
				int						accessorType;			// Accessor type for _interpolatable_ parameters

				// Pass 1
				int						numCode;				// The number of code blocks
				int						numArgument;			// The number of argument blocks
				int						numConstants;			// The number of constants
				int						numVariables;			// The number of variables (local + parameters)
				int						numStrings;				// The number of strings

				int						constantSize;			// Total size required by the constants
				int						varyingSize;			// Total size required by the variables

				int						shaderType;				// Type of the shader

				int						uniform;				// TRUE if the current expression is uniform
				int						opcodeUniform;			// TRUE if the opcode/function is uniform

				// Pass 2
				EVariableType			currentParameterType;	// The type of the current parameter
				int						currentParameterMutable;// TRUE if the current parameter is global or writable
				EVariableClass			currentParameterClass;	// The container class of the current parameter
				int						currentConstant;
				int						currentVariable;
				int						currentString;
				int						currentPL;				// The current parameter list

				int						currentConstantSize;
				int						currentVaryingSize;

				float					*currentArray;			// Array items go here as we read them
				char					**currentStringArray;	// If the array is string, we this pointer instead
				int						numArrayItemsRemaining;	// Number of array items we're still expecting to read
				
				char					currentOpcode[32];		// Holds the opcode being parsed
				char					currentPrototype[32];	// Holds the prototype being parsed
				int						currentArgument;		// The current argument number
				unsigned int			usedParameters;			// Used parameters by this shader
				TCode					*currentOpcodePlace;	// Points to the code that should holds the opcode
				TArgument				*currentArgumentPlace;	// Points to the current argument that should hold the argument

				int						codeEntryPoint;			// Indices in the code array for corresponding entry points
				int						initEntryPoint;
				
				char					*memory;				// The memory base for the area that's allocated
				TCode					*code;					// Code blocks
				TArgument				*arguments;				// Argument blocks
				char					*constants;				// Constants blocks
				int						*varyingSizes;			// Holds the size of each varying in codes
				char					**strings;				// Strings defined
				void					**constantEntries;		// Where the constant entries are stored

				TSlVariable				*definedVariables;		// List of defined variables
				TSlLabel				*labelReferences;		// List of label references
				TSlLabel				*labelDefinitions;		// List of label definitions
		} TShaderData;

		TShaderData						currentData;

									///////////////////////////////////////////////////////////////////////
									// Function				:	numComponents
									// Description			:	Returns the number of codes that a particular type takes
									// Return Value			:	Size in codes
									// Comments				:
		static	int					numComponents(EVariableType type) {
										switch(type) {
										case TYPE_FLOAT:
											return	1;
											break;
										case TYPE_COLOR:
											return	3;
											break;
										case TYPE_VECTOR:
											return	3;
											break;
										case TYPE_NORMAL:
											return	3;
											break;
										case TYPE_POINT:
											return	3;
											break;
										case TYPE_MATRIX:
											return	16;
											break;
										case TYPE_QUAD:
											return	4;
											break;
										case TYPE_DOUBLE:
											return	2;
											break;
										case TYPE_STRING:
											return	1;
											break;
										case TYPE_INTEGER:
										case TYPE_BOOLEAN:
											return	1;
											break;
										default:
											slerror("Unknown type (bug)");
											break;
										}

										return 0;
									}


									///////////////////////////////////////////////////////////////////////
									// Function				:	newVariable
									// Description			:	Add a new variable/parameter
									// Return Value			:	The default area if available
									// Comments				:
		static	void				*newVariable(char *name,EVariableType type,int numItems,int parameter) {
										const int	numComp			=	numComponents(type);

										switch(currentData.passNumber) {
										case 1:
											currentData.numVariables++;
											if (type == TYPE_STRING)
												currentData.varyingSize		+=	numItems*numComp*sizeof(char*);
											else
												currentData.varyingSize		+=	numItems*numComp*sizeof(float);
											break;
										case 2:
											{
												// Create a new variable
												TSlVariable	*cVariable	=	new TSlVariable;

												strcpy(cVariable->name,name);
												cVariable->multiplicity	=	numItems;
												cVariable->type			=	type;
												cVariable->container	=	currentData.currentParameterClass;
												cVariable->uniform		=	currentData.uniform;
												cVariable->variable		=	NULL;
												cVariable->index		=	currentData.currentVariable;
												
												currentData.varyingSizes[currentData.currentVariable]	=	numItems*numComp;
												if (cVariable->uniform)	currentData.varyingSizes[currentData.currentVariable]	=	-currentData.varyingSizes[currentData.currentVariable];
												
												currentData.currentVariable++;
												if (type == TYPE_STRING)
													currentData.currentVaryingSize	+=	numItems*numComp*sizeof(char*);
												else
													currentData.currentVaryingSize	+=	numItems*numComp*sizeof(float);

													
												cVariable->next					=	currentData.definedVariables;
												currentData.definedVariables	=	cVariable;
												
												// Here's the trick part ...
												// If this is a parameter, allocate a parameter entry and make sure it points to the right location
												if (parameter) {
													CVariable	*newVariable;
													CVariable	*gVariable;
													
													newVariable					=	new CVariable;
													strcpy(newVariable->name,name);
													newVariable->type			=	type;
													newVariable->container		=	currentData.currentParameterClass;
													newVariable->numItems		=	numItems;
													newVariable->numFloats		=	numItems*numComp;
													newVariable->entry			=	cVariable->index;
													newVariable->usageMarker	=	0;
													newVariable->storage		=	currentData.currentParameterMutable	? STORAGE_MUTABLEPARAMETER : STORAGE_PARAMETER;
													newVariable->defaultValue	=	new TCode[numItems*numComp];
													newVariable->accessor		=	currentData.accessorType;
													newVariable->next			=	NULL;													
													cVariable->variable			=	newVariable;
													
													// Is this a global variable ?
													gVariable					=	CRenderer::retrieveVariable(name);
													if (gVariable != NULL)	{
														if (gVariable->storage == STORAGE_GLOBAL) {
															// If the variable is actually defined
															
															if (newVariable->type == gVariable->type &&
																newVariable->numItems == gVariable->numItems &&
																newVariable->numFloats == gVariable->numFloats &&
																!(cVariable->uniform ^ ((gVariable->container == CONTAINER_UNIFORM) || (gVariable->container == CONTAINER_CONSTANT)))
																) {
																
																// And it matchces the current definition
																
																newVariable->storage						=	STORAGE_GLOBAL;
																currentData.varyingSizes[cVariable->index]	=	0;		// It takes up no space in the cache
																
																// Note: the variable index will be re-pointed at the global when init is run
															}
															/*else {
																// This mismatches the predeclared variable.  Issue warning, and continue
																warning(CODE_CONSISTENCY,"Parameter \"%s\" in shader \"%s\" mismatches predeclared variable\n",gVariable->name,currentData.name);
															}*/
														}
													} //If so, then lets ensure we don't delete it by taking a copy
													
													return	newVariable->defaultValue;
												}
											}
											break;
										default:
											break;
										}

										return NULL;
									}

									///////////////////////////////////////////////////////////////////////
									// Function				:	addStringReference
									// Description			:	Add a reference to a string
									// Return Value			:	-
									// Comments				:
		static	void				addStringReference(char **items,int numItems) {
										int	i;
										
										switch(currentData.passNumber) {
										case 1:
											currentData.numArgument		+=	1;							// Add one argument
											currentData.numConstants	+=	1;							// We have one more constant
											currentData.numStrings		+=	numItems;					// Reserve numItems strings
											currentData.constantSize	+=	numItems*sizeof(char *);	// This is the final constant size we consume
											break;
										case 2:
											assert(currentData.currentConstant < 65535);
											
											char	**dest;
											
											currentData.currentArgumentPlace->numItems									=	numItems;
											currentData.currentArgumentPlace->bytesPerItem								=	sizeof(char *);
											currentData.currentArgumentPlace->index										=	(unsigned short) currentData.currentConstant;
											currentData.currentArgumentPlace->accessor									=	SL_IMMEDIATE_OPERAND;
											currentData.constantEntries[currentData.currentConstant]					=	currentData.constants + currentData.currentConstantSize;
											dest																		=	(char **) currentData.constantEntries[currentData.currentConstant];
											currentData.currentConstant++;
											currentData.currentArgumentPlace++;
											currentData.currentArgument++;
											currentData.currentConstantSize	+=	numItems*sizeof(char *);

											// Acturally record the strings
											for (i=0;i<numItems;i++)
												dest[i]	=	currentData.strings[currentData.currentString++]	=	strdup(items[i]);
											
											break;
										default:
											break;
										}
									}


									///////////////////////////////////////////////////////////////////////
									// Function				:	addFloatReference
									// Description			:	Add a reference to a float
									// Return Value			:	-
									// Comments				:
		static	void				addFloatReference(float *items,int numItems) {
										int	i;
										switch(currentData.passNumber) {
											case 1:
												currentData.numArgument		+=	1;
												currentData.numConstants	+=	1;
												currentData.constantSize	+=	numItems*sizeof(float);
												break;
											case 2:
												assert(currentData.currentConstant < 65536);
												
												float	*dest;
												
												currentData.currentArgumentPlace->numItems						=	numItems;
												currentData.currentArgumentPlace->bytesPerItem					=	sizeof(float);
												currentData.currentArgumentPlace->index							=	(unsigned short) currentData.currentConstant;
												currentData.currentArgumentPlace->accessor						=	SL_IMMEDIATE_OPERAND;
												currentData.constantEntries[currentData.currentConstant]		=	currentData.constants + currentData.currentConstantSize;
												dest															=	(float *) currentData.constantEntries[currentData.currentConstant];
												currentData.currentConstant++;
												currentData.currentArgumentPlace++;
												currentData.currentArgument++;
												currentData.currentConstantSize	+=	numItems*sizeof(float);

												for (i=0;i<numItems;i++) dest[i]	=	items[i];

												break;
											default:
												break;
											}
										}

										///////////////////////////////////////////////////////////////////////
										// Function				:	addVariableReference
										// Description			:	Add a reference to a variable/parameter
										// Return Value			:	-
										// Comments				:
		static	void					addVariableReference(char *name) {
											CVariable		*var;
											TSlVariable		*cVariable;

											switch(currentData.passNumber) {
											case 1:
												currentData.numArgument	+=	1;
												break;
											case 2:
												currentData.currentArgument++;

												// Search the variables
												for (cVariable=currentData.definedVariables;cVariable!=NULL;cVariable=cVariable->next) {
													if (strcmp(cVariable->name,name) == 0) {
														
														// If this is a global parameter, let the next section deal with it
														if (cVariable->variable) {
															// in init, we treat the global as a parameter, but in the init phase, it's a local varying
															if ((cVariable->variable->storage == STORAGE_GLOBAL) && !currentData.parsingInit) continue;
														} 
														
														assert(cVariable->index < 65536);
														assert((cVariable->multiplicity*numComponents(cVariable->type)) < 256);
														
														currentData.currentArgumentPlace->index			=	(unsigned short) cVariable->index;
														currentData.currentArgumentPlace->numItems		=	(char) (cVariable->multiplicity*numComponents(cVariable->type));
														currentData.currentArgumentPlace->bytesPerItem	=	(cVariable->type == TYPE_STRING ? sizeof(char *) : sizeof(float));
														currentData.currentArgumentPlace->accessor		=	SL_VARYING_OPERAND;
														currentData.currentArgumentPlace++;
														
														if (cVariable->uniform == FALSE)
															currentData.opcodeUniform									=	FALSE;
														
														return;
													}
												}

												var	=	CRenderer::retrieveVariable(name);

												if (var != NULL) {
													currentData.usedParameters										|=	var->usageMarker;

													assert(var->entry < 65536);
													assert(var->numFloats < 256);
													
													currentData.currentArgumentPlace->index			=	(unsigned short) var->entry;
													currentData.currentArgumentPlace->numItems		=	(char) var->numFloats;
													currentData.currentArgumentPlace->bytesPerItem	=	(var->type == TYPE_STRING ? sizeof(char *) : sizeof(float));
													currentData.currentArgumentPlace->accessor		=	SL_GLOBAL_OPERAND;
													currentData.currentArgumentPlace++;
													
													if ((var->container != CONTAINER_UNIFORM) || (var->container != CONTAINER_CONSTANT))
															currentData.opcodeUniform								=	FALSE;
															
												} else {
													slerror("Unknown variable");
												}

												break;
											default:
												break;
											}
										}

										///////////////////////////////////////////////////////////////////////
										// Function				:	setOpcode
										// Description			:	Find/Set an opcode/function
										// Return Value			:	-
										// Comments				:
		static	void					setOpcode() {
											switch(currentData.passNumber) {
											case 1:
												break;
											case 2:
												// Is this an opcode or function
												if (currentData.currentPrototype[0] == '~') {
													ESlCode	opcode;
													int		i;

													for(i=0;opcodes[i].name != NULL;i++) {
														if (strcmp(opcodes[i].name,currentData.currentOpcode) == 0) 
															if (opcodes[i].nargs == currentData.currentArgument) {
																opcode	=	opcodes[i].entryPoint;
																break;
															}
													}

													if (opcodes[i].name == NULL)
														slerror("Unknown opcode");
													else {
														assert((currentData.currentArgument+2) < 256);
														assert((currentData.opcodeUniform) < 256);
														
														// Save the opcode
														currentData.usedParameters						|=	opcodes[i].usedParameters;
														currentData.currentOpcodePlace->opcode			=	(int) opcode;
														currentData.currentOpcodePlace->plNumber		=	0;
														currentData.currentOpcodePlace->numArguments	=	(unsigned char) (currentData.currentArgument);
														currentData.currentOpcodePlace->uniform			=	(unsigned char) (currentData.opcodeUniform);
														currentData.currentOpcodePlace++;
													}
												} else {
													int			i;
													ESlCode		opcode;

													for(i=0;functions[i].name != NULL;i++) {
														if (strcmp(functions[i].name,currentData.currentOpcode) == 0) {
															if (strcmp(functions[i].prototype,currentData.currentPrototype) == 0) {
																currentData.usedParameters	|=	functions[i].usedParameters;
																opcode						=	functions[i].entryPoint;
																break;
															} else {
																// Do a pattern match
				

																// The return types must match exactly
																if (functions[i].prototype[0] != currentData.currentPrototype[0]) continue;

																{
																	int		j,k,t;

																	t	=	FALSE;

																	for (j=2,k=2;(currentData.currentPrototype[j] != '\0') && (functions[i].prototype[k] != '\0');j++,k++) {
																		// Do the current parameters match
																		if (currentData.currentPrototype[j] == functions[i].prototype[k]) continue;
																		// Does the function match any parameter ?
																		else if (functions[i].prototype[k] == '.') continue;
																		// Is the current parameter a * or + ?
																		else if ((functions[i].prototype[k] == '+') || (functions[i].prototype[k] == '*')) {
																			k-=2;
																			j--;
																			continue;
																		// Is the current parameter a parameter list ?
																		} else if (functions[i].prototype[k] == '!') {
																			if ((currentData.currentPrototype[j] == 's') || (currentData.currentPrototype[j] == 'S')) {
																				j++;
																				k--;
																			} else {
																				t	=	TRUE;
																				break;
																			}
																		} else {
																			t	=	TRUE;
																			break;
																		}
																	}


																	if (t == FALSE) {
																		if (
																				((functions[i].prototype[k] == '\0') && (currentData.currentPrototype[j] == '\0')) ||
																				((functions[i].prototype[k] == '+') || (functions[i].prototype[k] == '*')) || 
																				(functions[i].prototype[k] == '!') ||
																				(functions[i].prototype[k+1] == '*')) {
																			// We found our function/opcode
																			currentData.usedParameters	|=	functions[i].usedParameters;
																			opcode	=	functions[i].entryPoint;
																			break;
																		} else {
																			continue;
																		}
																	}
																}
															}
														}
													}	

													// Save the opcode
													if (functions[i].name != NULL) {
														assert((currentData.currentArgument+2) < 256);
														assert(currentData.currentPL < 256);
														assert(currentData.opcodeUniform < 256);
														
														currentData.currentOpcodePlace->opcode				=	(int) opcode;
														currentData.currentOpcodePlace->plNumber			=	(unsigned char) (currentData.currentPL);
														currentData.currentOpcodePlace->numArguments		=	(unsigned char) (currentData.currentArgument);
														currentData.currentOpcodePlace->uniform				=	(unsigned char) (currentData.opcodeUniform);
														if (strchr(functions[i].prototype,'!') != NULL)	currentData.currentPL++;
														currentData.currentOpcodePlace++;
													} else {
														// Allright, we could not find the function, check the DSO shaders
														CDSO	*dso;

														// See if this is a DSO function
														if ((dso = CRenderer::getDSO(currentData.currentOpcode,currentData.currentPrototype)) != NULL) {
														
															// We have the DSO
															if (currentData.currentPrototype[0] == 'o')		currentData.currentOpcodePlace->opcode	=	FUNCTION_DSO_VOID;
															else											currentData.currentOpcodePlace->opcode	=	FUNCTION_DSO;
								
															currentData.currentOpcodePlace->plNumber		=	(unsigned char) (currentData.currentPL);
															currentData.currentOpcodePlace->numArguments	=	(unsigned char) (currentData.currentArgument);
															currentData.currentOpcodePlace->uniform			=	(unsigned char) (currentData.opcodeUniform);
															currentData.currentOpcodePlace->dso				=	dso;
															currentData.currentOpcodePlace++;
														} else {
															slerror("Unknown function");
														}
													}
												}
												break;
											default:
												break;
											}
										}


									///////////////////////////////////////////////////////////////////////
									// Function				:	newLabel
									// Description			:	Create a new label definition/reference
									// Return Value			:	-
									// Comments				:
		static	void				newLabel(const char *name,int reference) {
										switch(currentData.passNumber) {
										case 1:
											if (reference)
												currentData.numArgument++;
											break;
										case 2:
											{
												TSlLabel	*cLabel	=	new TSlLabel;

												strcpy(cLabel->name,name);
												cLabel->index	=	(int) (currentData.currentOpcodePlace - currentData.code);

												if (reference) {
													cLabel->next					=	currentData.labelReferences;
													currentData.labelReferences		=	cLabel;
													cLabel->argument				=	currentData.currentArgumentPlace++;
													currentData.currentArgument++;
												} else {
													TSlLabel	*tLabel;

													for (tLabel=currentData.labelDefinitions;tLabel!=NULL;tLabel=tLabel->next) {
														if (strcmp(tLabel->name,cLabel->name) == 0) {
															slerror("Duplicate label definition\n");
														}
													}

													cLabel->argument				=	NULL;
													cLabel->next					=	currentData.labelDefinitions;
													currentData.labelDefinitions	=	cLabel;
												}
											}
											break;
										default:
											break;
										}
									}

									// Some forward references
		void						reset();
		void						alloc();
		CShader						*shaderCreate(const char *);
		int							getVariable(char *);
		int							getOpcode(char *,int);
		int							getFunction(char *,char *,int *ps = NULL);
		void						*newVariable(char *,int,int,int,int m=1);
		TSlLabel					*newLabelDef(char *,int);
		TSlLabel					*newLabelRef(char *,int);
		void						processEscapes(char *);


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 690 "sdr.y"
typedef union slval {
	float	real;
	char	string[64];
	matrix	m;
	vector	v;
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 856 "sl.cpp"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 868 "sl.cpp"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

# ifndef YYFREE
#  define YYFREE free
# endif
# ifndef YYMALLOC
#  define YYMALLOC malloc
# endif

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   define YYSTACK_ALLOC alloca
#  endif
# else
#  if defined (alloca) || defined (_ALLOCA_H)
#   define YYSTACK_ALLOC alloca
#  else
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   281

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  61
/* YYNRULES -- Number of rules. */
#define YYNRULES  136
/* YYNRULES -- Number of states. */
#define YYNSTATES  316

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short yyprhs[] =
{
       0,     0,     3,    10,    11,    14,    18,    26,    29,    36,
      37,    39,    42,    45,    48,    51,    54,    59,    63,    64,
      66,    68,    71,    74,    76,    77,    80,    82,    84,    86,
      88,    90,    92,    94,    99,   102,   103,   112,   118,   122,
     125,   126,   129,   134,   135,   144,   150,   154,   157,   158,
     159,   164,   165,   174,   180,   181,   186,   187,   196,   202,
     203,   208,   209,   218,   224,   225,   230,   231,   240,   246,
     249,   256,   258,   264,   268,   271,   272,   294,   299,   302,
     303,   312,   318,   322,   342,   345,   346,   351,   355,   356,
     359,   362,   365,   368,   371,   374,   377,   380,   383,   389,
     392,   398,   401,   407,   410,   416,   419,   425,   428,   434,
     437,   443,   446,   452,   453,   458,   459,   464,   468,   472,
     476,   477,   478,   486,   488,   490,   492,   495,   496,   499,
     502,   504,   506,   508,   510,   518,   552
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
      39,     0,    -1,    43,    44,    76,    87,    89,    40,    -1,
      -1,    33,    40,    -1,    27,    34,    37,    -1,    27,    34,
      30,    37,    37,    37,    31,    -1,    27,    37,    -1,    27,
      30,    37,    37,    37,    31,    -1,    -1,    41,    -1,    16,
      33,    -1,    17,    33,    -1,    19,    33,    -1,    20,    33,
      -1,    18,    33,    -1,     3,    26,    33,    45,    -1,    45,
      47,    33,    -1,    -1,     7,    -1,     6,    -1,     5,     7,
      -1,     5,     6,    -1,     5,    -1,    -1,    46,    48,    -1,
      49,    -1,    53,    -1,    57,    -1,    60,    -1,    63,    -1,
      66,    -1,    72,    -1,     9,    35,    27,    37,    -1,     9,
      35,    -1,    -1,     9,    35,    30,    37,    31,    27,    50,
      51,    -1,     9,    35,    30,    37,    31,    -1,    30,    52,
      31,    -1,    52,    37,    -1,    -1,    15,    35,    -1,    15,
      35,    27,    34,    -1,    -1,    15,    35,    30,    37,    31,
      27,    54,    55,    -1,    15,    35,    30,    37,    31,    -1,
      30,    56,    31,    -1,    56,    34,    -1,    -1,    -1,    10,
      35,    58,    42,    -1,    -1,    10,    35,    30,    37,    31,
      27,    59,    70,    -1,    10,    35,    30,    37,    31,    -1,
      -1,    11,    35,    61,    42,    -1,    -1,    11,    35,    30,
      37,    31,    27,    62,    70,    -1,    11,    35,    30,    37,
      31,    -1,    -1,    12,    35,    64,    42,    -1,    -1,    12,
      35,    30,    37,    31,    27,    65,    70,    -1,    12,    35,
      30,    37,    31,    -1,    -1,    13,    35,    67,    42,    -1,
      -1,    13,    35,    30,    37,    31,    27,    68,    70,    -1,
      13,    35,    30,    37,    31,    -1,    34,    37,    -1,    34,
      30,    37,    37,    37,    31,    -1,    37,    -1,    30,    37,
      37,    37,    31,    -1,    30,    71,    31,    -1,    71,    69,
      -1,    -1,    14,    35,    27,    30,    37,    37,    37,    37,
      37,    37,    37,    37,    37,    37,    37,    37,    37,    37,
      37,    37,    31,    -1,    14,    35,    27,    37,    -1,    14,
      35,    -1,    -1,    14,    35,    30,    37,    31,    27,    73,
      74,    -1,    14,    35,    30,    37,    31,    -1,    30,    75,
      31,    -1,    75,    30,    37,    37,    37,    37,    37,    37,
      37,    37,    37,    37,    37,    37,    37,    37,    37,    37,
      31,    -1,    75,    37,    -1,    -1,     4,    26,    33,    77,
      -1,    77,    78,    33,    -1,    -1,    46,    79,    -1,    46,
      80,    -1,    46,    81,    -1,    46,    83,    -1,    46,    82,
      -1,    46,    84,    -1,    46,    85,    -1,    46,    86,    -1,
       8,    35,    -1,     8,    35,    30,    37,    31,    -1,     9,
      35,    -1,     9,    35,    30,    37,    31,    -1,    15,    35,
      -1,    15,    35,    30,    37,    31,    -1,    11,    35,    -1,
      11,    35,    30,    37,    31,    -1,    10,    35,    -1,    10,
      35,    30,    37,    31,    -1,    12,    35,    -1,    12,    35,
      30,    37,    31,    -1,    13,    35,    -1,    13,    35,    30,
      37,    31,    -1,    14,    35,    -1,    14,    35,    30,    37,
      31,    -1,    -1,    23,    33,    88,    91,    -1,    -1,    24,
      33,    90,    91,    -1,    91,    96,    33,    -1,    91,    97,
      33,    -1,    91,    92,    33,    -1,    -1,    -1,    22,    35,
      93,    28,    34,    29,    95,    -1,    35,    -1,    16,    -1,
      17,    -1,    98,    95,    -1,    -1,    94,    95,    -1,    36,
      26,    -1,    34,    -1,    36,    -1,    35,    -1,    37,    -1,
      28,    37,    32,    37,    32,    37,    29,    -1,    28,    37,
      32,    37,    32,    37,    32,    37,    32,    37,    32,    37,
      32,    37,    32,    37,    32,    37,    32,    37,    32,    37,
      32,    37,    32,    37,    32,    37,    32,    37,    32,    37,
      29,    -1,    28,    34,    29,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   743,   743,   751,   753,   757,   766,   779,   787,   799,
     806,   815,   822,   829,   837,   846,   854,   861,   864,   868,
     875,   882,   890,   898,   905,   914,   920,   922,   924,   926,
     928,   930,   932,   937,   949,   965,   959,   981,  1000,  1011,
    1023,  1028,  1047,  1074,  1068,  1099,  1116,  1127,  1140,  1147,
    1145,  1165,  1159,  1174,  1187,  1185,  1205,  1199,  1216,  1229,
    1227,  1247,  1241,  1258,  1271,  1269,  1289,  1283,  1300,  1310,
    1318,  1330,  1337,  1351,  1362,  1376,  1381,  1425,  1452,  1483,
    1477,  1499,  1518,  1529,  1577,  1607,  1612,  1619,  1622,  1626,
    1629,  1632,  1635,  1638,  1641,  1644,  1647,  1652,  1658,  1670,
    1676,  1687,  1693,  1704,  1710,  1721,  1727,  1738,  1744,  1755,
    1761,  1772,  1778,  1790,  1788,  1799,  1797,  1807,  1811,  1815,
    1818,  1824,  1822,  1877,  1895,  1913,  1933,  1938,  1943,  1951,
    1959,  1966,  1971,  1976,  1981,  1998,  2054
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SCRL_PARAMETERS", "SCRL_VARIABLES",
  "SCRL_OUTPUT", "SCRL_VARYING", "SCRL_UNIFORM", "SCRL_BOOLEAN",
  "SCRL_FLOAT", "SCRL_COLOR", "SCRL_VECTOR", "SCRL_NORMAL", "SCRL_POINT",
  "SCRL_MATRIX", "SCRL_STRING", "SCRL_SURFACE", "SCRL_DISPLACEMENT",
  "SCRL_IMAGER", "SCRL_LIGHTSOURCE", "SCRL_VOLUME", "SCRL_GENERIC",
  "SCRL_DSO", "SCRL_INIT", "SCRL_CODE", "SCRL_DOT", "SCRL_COLON",
  "SCRL_EQUAL", "SCRL_OPEN_PARANTHESIS", "SCRL_CLOSE_PARANTHESIS",
  "SCRL_OPEN_SQR_PARANTHESIS", "SCRL_CLOSE_SQR_PARANTHESIS", "SCRL_COMMA",
  "SCRL_NL", "SCRL_TEXT_VALUE", "SCRL_IDENTIFIER_VALUE",
  "SCRL_LABEL_VALUE", "SCRL_FLOAT_VALUE", "$accept", "start",
  "slEmptySpace", "slVectorIn", "slVector", "slType",
  "slParameterDefinitions", "slParameters", "slContainer", "slParameter",
  "slAParameter", "slFloatParameter", "@1", "slFloatArrayInitializer",
  "slFloatArrayInitializerItems", "slStringParameter", "@2",
  "slStringArrayInitializer", "slStringArrayInitializerItems",
  "slColorParameter", "@3", "@4", "slVectorParameter", "@5", "@6",
  "slNormalParameter", "@7", "@8", "slPointParameter", "@9", "@10",
  "slVectorValue", "slVectorArrayInitializer",
  "slVectorArrayInitializerItems", "slMatrixParameter", "@11",
  "slMatrixArrayInitializer", "slMatrixArrayInitializerItems",
  "slVariableDefinitions", "slVariables", "slVariable",
  "slBooleanVariable", "slFloatVariable", "slStringVariable",
  "slVectorVariable", "slColorVariable", "slNormalVariable",
  "slPointVariable", "slMatrixVariable", "slInit", "@12", "slCode", "@13",
  "slShaderLine", "slDSO", "@14", "slOpcode", "slOperandList",
  "slStatement", "slLabelDefinition", "slOperand", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,    38,    39,    40,    40,    41,    41,    41,    41,    41,
      42,    43,    43,    43,    43,    43,    44,    45,    45,    46,
      46,    46,    46,    46,    46,    47,    48,    48,    48,    48,
      48,    48,    48,    49,    49,    50,    49,    49,    51,    52,
      52,    53,    53,    54,    53,    53,    55,    56,    56,    58,
      57,    59,    57,    57,    61,    60,    62,    60,    60,    64,
      63,    65,    63,    63,    67,    66,    68,    66,    66,    69,
      69,    69,    69,    70,    71,    71,    72,    72,    72,    73,
      72,    72,    74,    75,    75,    75,    76,    77,    77,    78,
      78,    78,    78,    78,    78,    78,    78,    79,    79,    80,
      80,    81,    81,    82,    82,    83,    83,    84,    84,    85,
      85,    86,    86,    88,    87,    90,    89,    91,    91,    91,
      91,    93,    92,    94,    94,    94,    95,    95,    96,    97,
      98,    98,    98,    98,    98,    98,    98
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     6,     0,     2,     3,     7,     2,     6,     0,
       1,     2,     2,     2,     2,     2,     4,     3,     0,     1,
       1,     2,     2,     1,     0,     2,     1,     1,     1,     1,
       1,     1,     1,     4,     2,     0,     8,     5,     3,     2,
       0,     2,     4,     0,     8,     5,     3,     2,     0,     0,
       4,     0,     8,     5,     0,     4,     0,     8,     5,     0,
       4,     0,     8,     5,     0,     4,     0,     8,     5,     2,
       6,     1,     5,     3,     2,     0,    21,     4,     2,     0,
       8,     5,     3,    19,     2,     0,     4,     3,     0,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     5,     2,
       5,     2,     5,     2,     5,     2,     5,     2,     5,     2,
       5,     2,     5,     0,     4,     0,     4,     3,     3,     3,
       0,     0,     7,     1,     1,     1,     2,     0,     2,     2,
       1,     1,     1,     1,     7,    33,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,    11,    12,
      15,    13,    14,     1,     0,     0,     0,     0,     0,    18,
       0,     0,     0,    24,    88,   113,     0,     3,    23,    20,
      19,     0,     0,    24,   120,   115,     3,     2,    22,    21,
       0,     0,     0,     0,     0,     0,     0,    25,    26,    27,
      28,    29,    30,    31,    32,    17,     0,     0,   114,   120,
       4,    34,    49,    54,    59,    64,    78,    41,     0,     0,
       0,     0,     0,     0,     0,     0,    89,    90,    91,    93,
      92,    94,    95,    96,    87,   124,   125,     0,   123,     0,
       0,   127,     0,     0,   116,     0,     0,     0,     9,     0,
       9,     0,     9,     0,     9,     0,     0,     0,     0,    97,
      99,   105,   103,   107,   109,   111,   101,   121,   129,   119,
       0,   130,   132,   131,   133,   128,   127,   117,   118,    33,
       0,     0,     0,    10,    50,     0,    55,     0,    60,     0,
      65,     0,    77,     0,    42,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   126,    37,    53,
       0,     0,     7,    58,    63,    68,     0,    81,    45,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   136,     0,
      35,    51,     0,     0,     5,    56,    61,    66,     0,    79,
      43,    98,   100,   106,   104,   108,   110,   112,   102,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   127,     0,    40,    36,    75,    52,     0,     0,    57,
      62,    67,     0,    85,    80,    48,    44,   122,     0,     0,
       0,     8,     0,     0,     0,     0,   134,     0,    38,    39,
       0,    73,     0,    71,    74,     6,     0,     0,    82,    84,
      46,    47,     0,     0,     0,    69,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    72,
       0,     0,     0,     0,    70,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    76,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    83,     0,     0,     0,
       0,     0,     0,     0,     0,   135
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short yydefgoto[] =
{
      -1,     6,    37,   133,   134,     7,    15,    23,    31,    32,
      47,    48,   201,   214,   229,    49,   210,   226,   235,    50,
      98,   202,    51,   100,   205,    52,   102,   206,    53,   104,
     207,   244,   216,   230,    54,   209,   224,   234,    18,    33,
      57,    76,    77,    78,    79,    80,    81,    82,    83,    22,
      34,    27,    59,    58,    90,   154,    91,   125,    92,    93,
     126
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -127
static const short yypact[] =
{
      41,   -16,    12,    23,    46,    53,    67,    31,  -127,  -127,
    -127,  -127,  -127,  -127,    50,    68,    54,    62,    66,  -127,
      57,    59,    69,    58,  -127,  -127,    61,    63,    77,  -127,
    -127,    40,    64,    -1,  -127,  -127,    63,  -127,  -127,  -127,
      56,    60,    65,    70,    71,    72,    73,  -127,  -127,  -127,
    -127,  -127,  -127,  -127,  -127,  -127,    15,    76,   -15,  -127,
    -127,    17,    74,    80,    81,    82,    39,    43,    78,    79,
      83,    84,    85,    86,    87,    88,  -127,  -127,  -127,  -127,
    -127,  -127,  -127,  -127,  -127,  -127,  -127,    89,  -127,    75,
      92,   -25,    93,    94,   -15,    91,    95,    96,    90,    97,
      90,    98,    90,    99,    90,   -22,   100,   104,   102,   101,
     110,   111,   112,   113,   114,   115,   116,  -127,  -127,  -127,
      34,  -127,  -127,  -127,  -127,  -127,   -25,  -127,  -127,  -127,
     117,   118,     3,  -127,  -127,   119,  -127,   120,  -127,   121,
    -127,   122,  -127,   123,  -127,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   141,   139,  -127,   103,   145,
     136,     6,  -127,   147,   148,   149,   140,   151,   152,   150,
     153,   154,   155,   156,   157,   158,   159,   146,  -127,   160,
    -127,  -127,   161,   162,  -127,  -127,  -127,  -127,   163,  -127,
    -127,  -127,  -127,  -127,  -127,  -127,  -127,  -127,  -127,   164,
     169,   165,   166,   167,   168,   166,   166,   166,   170,   172,
     173,   -25,   171,  -127,  -127,  -127,  -127,   175,   174,  -127,
    -127,  -127,   176,  -127,  -127,  -127,  -127,  -127,    45,   -18,
       1,  -127,   178,   177,    11,    44,  -127,   179,  -127,  -127,
     180,  -127,     9,  -127,  -127,  -127,   181,   182,  -127,  -127,
    -127,  -127,   183,   184,   185,  -127,   186,   187,   188,   189,
     190,   191,   192,   198,   200,   195,   196,   197,   199,  -127,
     204,   201,   202,   205,  -127,   203,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   221,   217,   218,   219,
     216,   220,   226,  -127,   222,   223,   224,   230,   227,   228,
     229,   231,   232,   233,   236,   239,  -127,   235,   241,   237,
     243,   240,   244,   242,   249,  -127
};

/* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -127,  -127,   245,  -127,   -86,  -127,  -127,  -127,   247,  -127,
    -127,  -127,  -127,  -127,  -127,  -127,  -127,  -127,  -127,  -127,
    -127,  -127,  -127,  -127,  -127,  -127,  -127,  -127,  -127,  -127,
    -127,  -127,  -125,  -127,  -127,  -127,  -127,  -127,  -127,  -127,
    -127,  -127,  -127,  -127,  -127,  -127,  -127,  -127,  -127,  -127,
    -127,  -127,  -127,   135,  -127,  -127,  -127,  -126,  -127,  -127,
    -127
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -87
static const short yytable[] =
{
     157,    85,    86,   120,    28,    29,    30,    87,   141,   121,
     122,   123,   124,   238,   136,   142,   138,     8,   140,   239,
      88,    89,   -86,    68,    69,    70,    71,    72,    73,    74,
      75,   240,   241,   160,    14,   242,   183,   161,   243,   254,
     162,   247,   248,   184,    95,     9,   255,    96,   249,    40,
      41,    42,    43,    44,    45,    46,    10,     1,     2,     3,
       4,     5,   -16,    28,    29,    30,   105,    13,   155,   106,
     107,   156,    17,   108,   236,   250,    16,   237,   251,    11,
     219,   220,   221,    38,    39,   227,    12,    19,    20,    21,
      24,    61,    25,    26,    35,    62,    36,    55,     0,     0,
      63,   118,     0,     0,    97,    64,    65,    66,    67,    84,
      99,   101,   103,   109,   110,     0,     0,   132,   111,   112,
     113,   114,   115,   116,   117,   119,   127,   128,   129,     0,
     180,   146,   130,   131,   135,   137,   139,   143,   144,   145,
     147,   148,   149,   150,   151,   152,   153,     0,   158,   159,
     163,   164,   165,     0,   167,   168,     0,     0,     0,   166,
       0,   177,   169,   170,   171,   172,   173,   174,   175,   176,
     178,   179,   181,   182,   185,   186,   187,   188,   189,   190,
     199,   191,     0,     0,   192,   193,   194,   195,   196,   197,
     198,     0,     0,   211,    94,   213,   215,   200,   203,   204,
     208,   212,   223,   225,   217,   218,   231,   222,   228,   245,
       0,   232,     0,   233,   246,   258,   252,   253,   256,   257,
       0,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   274,   273,   277,   275,   276,
     278,     0,   283,   279,   280,   281,   282,   293,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   294,   295,   296,
     297,   298,   299,   303,   300,   301,   302,   306,     0,   304,
     305,   307,   308,   309,   310,   311,   313,   312,   315,   314,
      56,    60
};

static const short yycheck[] =
{
     126,    16,    17,    28,     5,     6,     7,    22,    30,    34,
      35,    36,    37,    31,   100,    37,   102,    33,   104,    37,
      35,    36,    23,     8,     9,    10,    11,    12,    13,    14,
      15,    30,    31,    30,     3,    34,    30,    34,    37,    30,
      37,    30,    31,    37,    27,    33,    37,    30,    37,     9,
      10,    11,    12,    13,    14,    15,    33,    16,    17,    18,
      19,    20,     4,     5,     6,     7,    27,     0,    34,    30,
      27,    37,     4,    30,    29,    31,    26,    32,    34,    33,
     205,   206,   207,     6,     7,   211,    33,    33,    26,    23,
      33,    35,    33,    24,    33,    35,    33,    33,    -1,    -1,
      35,    26,    -1,    -1,    30,    35,    35,    35,    35,    33,
      30,    30,    30,    35,    35,    -1,    -1,    27,    35,    35,
      35,    35,    35,    35,    35,    33,    33,    33,    37,    -1,
      27,    30,    37,    37,    37,    37,    37,    37,    34,    37,
      30,    30,    30,    30,    30,    30,    30,    -1,    31,    31,
      31,    31,    31,    -1,    31,    31,    -1,    -1,    -1,    37,
      -1,    28,    37,    37,    37,    37,    37,    37,    37,    37,
      29,    32,    27,    37,    27,    27,    27,    37,    27,    27,
      34,    31,    -1,    -1,    31,    31,    31,    31,    31,    31,
      31,    -1,    -1,    29,    59,    30,    30,    37,    37,    37,
      37,    32,    30,    30,    37,    37,    31,    37,    37,    31,
      -1,    37,    -1,    37,    37,    32,    37,    37,    37,    37,
      -1,    37,    37,    37,    37,    37,    37,    37,    37,    37,
      32,    31,    37,    37,    37,    31,    37,    32,    37,    37,
      37,    -1,    32,    37,    37,    37,    37,    31,    37,    37,
      37,    37,    37,    32,    37,    37,    37,    37,    32,    37,
      37,    37,    32,    32,    37,    37,    37,    31,    -1,    37,
      37,    32,    37,    32,    37,    32,    32,    37,    29,    37,
      33,    36
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    16,    17,    18,    19,    20,    39,    43,    33,    33,
      33,    33,    33,     0,     3,    44,    26,     4,    76,    33,
      26,    23,    87,    45,    33,    33,    24,    89,     5,     6,
       7,    46,    47,    77,    88,    33,    33,    40,     6,     7,
       9,    10,    11,    12,    13,    14,    15,    48,    49,    53,
      57,    60,    63,    66,    72,    33,    46,    78,    91,    90,
      40,    35,    35,    35,    35,    35,    35,    35,     8,     9,
      10,    11,    12,    13,    14,    15,    79,    80,    81,    82,
      83,    84,    85,    86,    33,    16,    17,    22,    35,    36,
      92,    94,    96,    97,    91,    27,    30,    30,    58,    30,
      61,    30,    64,    30,    67,    27,    30,    27,    30,    35,
      35,    35,    35,    35,    35,    35,    35,    35,    26,    33,
      28,    34,    35,    36,    37,    95,    98,    33,    33,    37,
      37,    37,    27,    41,    42,    37,    42,    37,    42,    37,
      42,    30,    37,    37,    34,    37,    30,    30,    30,    30,
      30,    30,    30,    30,    93,    34,    37,    95,    31,    31,
      30,    34,    37,    31,    31,    31,    37,    31,    31,    37,
      37,    37,    37,    37,    37,    37,    37,    28,    29,    32,
      27,    27,    37,    30,    37,    27,    27,    27,    37,    27,
      27,    31,    31,    31,    31,    31,    31,    31,    31,    34,
      37,    50,    59,    37,    37,    62,    65,    68,    37,    73,
      54,    29,    32,    30,    51,    30,    70,    37,    37,    70,
      70,    70,    37,    30,    74,    30,    55,    95,    37,    52,
      71,    31,    37,    37,    75,    56,    29,    32,    31,    37,
      30,    31,    34,    37,    69,    31,    37,    30,    31,    37,
      31,    34,    37,    37,    30,    37,    37,    37,    32,    37,
      37,    37,    37,    37,    37,    37,    37,    37,    32,    31,
      37,    37,    37,    37,    31,    37,    37,    32,    37,    37,
      37,    37,    37,    32,    37,    37,    37,    37,    37,    32,
      37,    37,    37,    31,    37,    32,    37,    37,    37,    32,
      37,    37,    37,    32,    37,    37,    31,    32,    37,    32,
      37,    32,    37,    32,    37,    29
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)		\
   ((Current).first_line   = (Rhs)[1].first_line,	\
    (Current).first_column = (Rhs)[1].first_column,	\
    (Current).last_line    = (Rhs)[N].last_line,	\
    (Current).last_column  = (Rhs)[N].last_column)
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short *bottom, short *top)
#else
static void
yy_stack_print (bottom, top)
    short *bottom;
    short *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if defined (YYMAXDEPTH) && YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 5:
#line 760 "sdr.y"
    {
					yyval.v[0]	=	yyvsp[0].real;
					yyval.v[1]	=	yyvsp[0].real;
					yyval.v[2]	=	yyvsp[0].real;
				;}
    break;

  case 6:
#line 773 "sdr.y"
    {
					yyval.v[0]	=	yyvsp[-3].real;
					yyval.v[1]	=	yyvsp[-2].real;
					yyval.v[2]	=	yyvsp[-1].real;
				;}
    break;

  case 7:
#line 781 "sdr.y"
    {
					yyval.v[0]	=	yyvsp[0].real;
					yyval.v[1]	=	yyvsp[0].real;
					yyval.v[2]	=	yyvsp[0].real;
				;}
    break;

  case 8:
#line 793 "sdr.y"
    {
					yyval.v[0]	=	yyvsp[-3].real;
					yyval.v[1]	=	yyvsp[-2].real;
					yyval.v[2]	=	yyvsp[-1].real;
				;}
    break;

  case 9:
#line 799 "sdr.y"
    {
					yyval.v[0]	=	0;
					yyval.v[1]	=	0;
					yyval.v[2]	=	0;
				;}
    break;

  case 10:
#line 807 "sdr.y"
    {
					yyval.v[0]	=	yyvsp[0].v[0];
					yyval.v[1]	=	yyvsp[0].v[1];
					yyval.v[2]	=	yyvsp[0].v[2];
				;}
    break;

  case 11:
#line 817 "sdr.y"
    {
					currentData.shaderType		=	SL_SURFACE;
					currentData.accessorType 	=	ACCESSOR_SURFACE;
				;}
    break;

  case 12:
#line 824 "sdr.y"
    {
					currentData.shaderType		=	SL_DISPLACEMENT;
					currentData.accessorType	=	ACCESSOR_DISPLACEMENT;
				;}
    break;

  case 13:
#line 831 "sdr.y"
    {
					currentData.shaderType		=	SL_LIGHTSOURCE;
					// Note: we don't set accessorType because you can't interpolate into
					// light shader parameters
				;}
    break;

  case 14:
#line 839 "sdr.y"
    {
					currentData.shaderType		=	SL_ATMOSPHERE;
					currentData.accessorType	=	ACCESSOR_ATMOSPHERE;
					// Note: we can assume the accessor is atmosphere as that's the only
					// volume shader that can be interpolated into
				;}
    break;

  case 15:
#line 848 "sdr.y"
    {
					currentData.shaderType		=	SL_IMAGER;
				;}
    break;

  case 19:
#line 869 "sdr.y"
    {
					currentData.currentParameterClass	=	CONTAINER_UNIFORM;
					currentData.currentParameterMutable	=	FALSE;
					currentData.uniform					=	TRUE;
				;}
    break;

  case 20:
#line 876 "sdr.y"
    {
					currentData.currentParameterClass	=	CONTAINER_VARYING;
					currentData.currentParameterMutable	=	FALSE;
					currentData.uniform					=	FALSE;
				;}
    break;

  case 21:
#line 884 "sdr.y"
    {
					currentData.currentParameterClass	=	CONTAINER_UNIFORM;
					currentData.currentParameterMutable	=	TRUE;
					currentData.uniform					=	TRUE;
				;}
    break;

  case 22:
#line 892 "sdr.y"
    {
					currentData.currentParameterClass	=	CONTAINER_VARYING;
					currentData.currentParameterMutable	=	TRUE;
					currentData.uniform					=	FALSE;
				;}
    break;

  case 23:
#line 899 "sdr.y"
    {
					currentData.currentParameterClass	=	CONTAINER_UNIFORM;
					currentData.currentParameterMutable	=	TRUE;
					currentData.uniform					=	TRUE;
				;}
    break;

  case 24:
#line 905 "sdr.y"
    {
					currentData.currentParameterClass	=	CONTAINER_UNIFORM;
					currentData.currentParameterMutable	=	FALSE;
					currentData.uniform					=	TRUE;
				;}
    break;

  case 33:
#line 941 "sdr.y"
    {
					float	*def	=	(float *) newVariable(yyvsp[-2].string,TYPE_FLOAT,1,TRUE);

					if (def != NULL) {
						def[0]	=	yyvsp[0].real;
					}
				;}
    break;

  case 34:
#line 951 "sdr.y"
    {
					float	*def	=	(float *) newVariable(yyvsp[0].string,TYPE_FLOAT,1,TRUE);

					if (def != NULL) {
						def[0]		=	0;
					}
				;}
    break;

  case 35:
#line 965 "sdr.y"
    {
					float	*def	=	(float *) newVariable(yyvsp[-4].string,TYPE_FLOAT,(int) yyvsp[-2].real,TRUE);
					
					if (def != NULL) {
						int	i;

						for (i=0;i<(int) yyvsp[-2].real;i++)
							def[i]	=	0;
						
						currentData.currentArray = def;
					}
					
					currentData.numArrayItemsRemaining = (int) yyvsp[-2].real;
				;}
    break;

  case 37:
#line 986 "sdr.y"
    {
					float	*def	=	(float *) newVariable(yyvsp[-3].string,TYPE_FLOAT,(int) yyvsp[-1].real,TRUE);

					if (def != NULL) {
						int	i;

						for (i=0;i<(int) yyvsp[-1].real;i++)
							def[i]	=	0;
					}
				;}
    break;

  case 38:
#line 1003 "sdr.y"
    {
					if(currentData.numArrayItemsRemaining){
						slerror("Wrong number of items in array initializer\n");
					}
				;}
    break;

  case 39:
#line 1013 "sdr.y"
    {
					if(currentData.numArrayItemsRemaining > 0){
						if(currentData.currentArray){
							*currentData.currentArray++ = yyvsp[0].real;
						}
						currentData.numArrayItemsRemaining--;
					} else{
						slerror("Wrong number of items in array initializer\n");
					}
				;}
    break;

  case 41:
#line 1030 "sdr.y"
    {
					char	**def	=	(char **) newVariable(yyvsp[0].string,TYPE_STRING,1,TRUE);

					switch(currentData.passNumber) {
					case 1:
						currentData.numStrings++;
						break;
					case 2:
						if (def != NULL) {
							*def	=	currentData.strings[currentData.currentString++]	=	strdup("*");
						}
						break;
					default:
						break;
					}
				;}
    break;

  case 42:
#line 1051 "sdr.y"
    {
					char	**def	=	(char **) newVariable(yyvsp[-2].string,TYPE_STRING,1,TRUE);

					switch(currentData.passNumber) {
					case 1:
						currentData.numStrings++;
						break;
					case 2:
						if (def != NULL) {
							*def	=	currentData.strings[currentData.currentString++]	=	strdup(yyvsp[0].string);
						}
						break;
					default:
						break;
					}
				;}
    break;

  case 43:
#line 1074 "sdr.y"
    {
					char	**def	=	(char **) newVariable(yyvsp[-4].string,TYPE_STRING,(int) yyvsp[-2].real,TRUE);
					
					switch(currentData.passNumber) {
					case 1:
						currentData.numStrings += (int) yyvsp[-2].real;
						break;
					case 2:
						if (def != NULL) {
							int	i;

							for (i=0;i<(int) yyvsp[-2].real;i++)
								def[i]	=	NULL;
							
							currentData.currentStringArray = def;
						}
						break;
					default:
						break;
					}
					
					currentData.numArrayItemsRemaining = (int) yyvsp[-2].real;
				;}
    break;

  case 45:
#line 1104 "sdr.y"
    {
					char	**def	=	(char **) newVariable(yyvsp[-3].string,TYPE_STRING,(int) yyvsp[-1].real,TRUE);

					if (def != NULL) {
						int	i;

						for (i=0;i<(int) yyvsp[-1].real;i++)
							def[i]	=	NULL;
					}
				;}
    break;

  case 46:
#line 1119 "sdr.y"
    {
					if(currentData.numArrayItemsRemaining){
						slerror("Wrong number of items in array initializer\n");
					}
				;}
    break;

  case 47:
#line 1129 "sdr.y"
    {
					if(currentData.numArrayItemsRemaining > 0){
						if(currentData.currentArray){
							*currentData.currentStringArray++	=	currentData.strings[currentData.currentString++]	=	strdup(yyvsp[0].string);
						}
						currentData.numArrayItemsRemaining--;
					}
					else{
						slerror("Wrong number of items in array initializer\n");
					}
				;}
    break;

  case 49:
#line 1147 "sdr.y"
    {
					currentData.currentParameterType	=	TYPE_COLOR;
				;}
    break;

  case 50:
#line 1151 "sdr.y"
    {
					float	*def	=	(float *) newVariable(yyvsp[-2].string,currentData.currentParameterType,1,TRUE);

					if (def != NULL) {
						movvv(def,yyvsp[0].v);
					}
				;}
    break;

  case 51:
#line 1165 "sdr.y"
    {
					float	*def	=	(float *) newVariable(yyvsp[-4].string,TYPE_COLOR,(int) yyvsp[-2].real,TRUE);
					
					if(def != NULL)
						currentData.currentArray = def;
					currentData.numArrayItemsRemaining = (int) yyvsp[-2].real;
				;}
    break;

  case 53:
#line 1179 "sdr.y"
    {
					float	*def	=	(float *) newVariable(yyvsp[-3].string,TYPE_COLOR,(int) yyvsp[-1].real,TRUE);
				;}
    break;

  case 54:
#line 1187 "sdr.y"
    {
					currentData.currentParameterType	=	TYPE_VECTOR;
				;}
    break;

  case 55:
#line 1191 "sdr.y"
    {
					float	*def	=	(float *) newVariable(yyvsp[-2].string,currentData.currentParameterType,1,TRUE);

					if (def != NULL) {
						movvv(def,yyvsp[0].v);
					}
				;}
    break;

  case 56:
#line 1205 "sdr.y"
    {
					float	*def	=	(float *) newVariable(yyvsp[-4].string,TYPE_VECTOR,(int) yyvsp[-2].real,TRUE);
					
					if(def != NULL) {
						currentData.currentArray = def;
					}
					
					currentData.numArrayItemsRemaining = (int) yyvsp[-2].real;
				;}
    break;

  case 58:
#line 1221 "sdr.y"
    {
					float	*def	=	(float *) newVariable(yyvsp[-3].string,TYPE_VECTOR,(int) yyvsp[-1].real,TRUE);
				;}
    break;

  case 59:
#line 1229 "sdr.y"
    {
					currentData.currentParameterType	=	TYPE_NORMAL;
				;}
    break;

  case 60:
#line 1233 "sdr.y"
    {
					float	*def	=	(float *) newVariable(yyvsp[-2].string,currentData.currentParameterType,1,TRUE);

					if (def != NULL) {
						movvv(def,yyvsp[0].v);
					}
				;}
    break;

  case 61:
#line 1247 "sdr.y"
    {
					float	*def	=	(float *) newVariable(yyvsp[-4].string,TYPE_NORMAL,(int) yyvsp[-2].real,TRUE);
					
					if(def != NULL) {
						currentData.currentArray = def;
					}
					
					currentData.numArrayItemsRemaining = (int) yyvsp[-2].real;
				;}
    break;

  case 63:
#line 1263 "sdr.y"
    {
					float	*def	=	(float *) newVariable(yyvsp[-3].string,TYPE_NORMAL,(int) yyvsp[-1].real,TRUE);
				;}
    break;

  case 64:
#line 1271 "sdr.y"
    {
					currentData.currentParameterType	=	TYPE_POINT;
				;}
    break;

  case 65:
#line 1275 "sdr.y"
    {
					float	*def	=	(float *)newVariable(yyvsp[-2].string,currentData.currentParameterType,1,TRUE);

					if (def != NULL) {
						movvv(def,yyvsp[0].v);
					}
				;}
    break;

  case 66:
#line 1289 "sdr.y"
    {
					float	*def	=	(float *) newVariable(yyvsp[-4].string,TYPE_POINT,(int) yyvsp[-2].real,TRUE);
					
					if(def != NULL) {
						currentData.currentArray = def;
					}
					
					currentData.numArrayItemsRemaining = (int) yyvsp[-2].real;
				;}
    break;

  case 68:
#line 1305 "sdr.y"
    {
					float 	*def	=	(float *) newVariable(yyvsp[-3].string,TYPE_POINT,(int) yyvsp[-1].real,TRUE);
				;}
    break;

  case 69:
#line 1312 "sdr.y"
    {
					yyval.v[0]	=	yyvsp[0].real;
					yyval.v[1]	=	yyvsp[0].real;
					yyval.v[2]	=	yyvsp[0].real;
				;}
    break;

  case 70:
#line 1324 "sdr.y"
    {
					yyval.v[0]	=	yyvsp[-3].real;
					yyval.v[1]	=	yyvsp[-2].real;
					yyval.v[2]	=	yyvsp[-1].real;
				;}
    break;

  case 71:
#line 1331 "sdr.y"
    {
					yyval.v[0]	=	yyvsp[0].real;
					yyval.v[1]	=	yyvsp[0].real;
					yyval.v[2]	=	yyvsp[0].real;
				;}
    break;

  case 72:
#line 1342 "sdr.y"
    {
					yyval.v[0]	=	yyvsp[-3].real;
					yyval.v[1]	=	yyvsp[-2].real;
					yyval.v[2]	=	yyvsp[-1].real;
				;}
    break;

  case 73:
#line 1354 "sdr.y"
    {
					if(currentData.numArrayItemsRemaining){
						slerror("Wrong number of items in array initializer\n");
					}
				;}
    break;

  case 74:
#line 1364 "sdr.y"
    {
					
					if(currentData.numArrayItemsRemaining > 0){
						if(currentData.currentArray){
							movvv(currentData.currentArray,yyvsp[0].v);
							currentData.currentArray += 3;
						}
						currentData.numArrayItemsRemaining--;
					} else{
						slerror("Wrong number of items in array initializer\n");
					}
				;}
    break;

  case 76:
#line 1402 "sdr.y"
    {
					float	*def	=	(float *) newVariable(yyvsp[-19].string,TYPE_MATRIX,1,TRUE);

					if (def != NULL) {
						def[0]		=	yyvsp[-16].real;
						def[1]		=	yyvsp[-15].real;
						def[2]		=	yyvsp[-14].real;
						def[3]		=	yyvsp[-13].real;
						def[4]		=	yyvsp[-12].real;
						def[5]		=	yyvsp[-11].real;
						def[6]		=	yyvsp[-10].real;
						def[7]		=	yyvsp[-9].real;
						def[8]		=	yyvsp[-8].real;
						def[9]		=	yyvsp[-7].real;
						def[10]		=	yyvsp[-6].real;
						def[11]		=	yyvsp[-5].real;
						def[12]		=	yyvsp[-4].real;
						def[13]		=	yyvsp[-3].real;
						def[14]		=	yyvsp[-2].real;
						def[15]		=	yyvsp[-1].real;
					}
				;}
    break;

  case 77:
#line 1429 "sdr.y"
    {
					float	*def	=	(float *) newVariable(yyvsp[-2].string,TYPE_MATRIX,1,TRUE);

					if (def != NULL) {
						def[0]		=	yyvsp[0].real;
						def[1]		=	0;
						def[2]		=	0;
						def[3]		=	0;
						def[4]		=	0;
						def[5]		=	yyvsp[0].real;
						def[6]		=	0;
						def[7]		=	0;
						def[8]		=	0;
						def[9]		=	0;
						def[10]		=	yyvsp[0].real;
						def[11]		=	0;
						def[12]		=	0;
						def[13]		=	0;
						def[14]		=	0;
						def[15]		=	1;
					}
				;}
    break;

  case 78:
#line 1454 "sdr.y"
    {
					float	*def	=	(float *) newVariable(yyvsp[0].string,TYPE_MATRIX,1,TRUE);

					if (def != NULL) {
						def[0]		=	1;
						def[1]		=	0;
						def[2]		=	0;
						def[3]		=	0;
						def[4]		=	0;
						def[5]		=	1;
						def[6]		=	0;
						def[7]		=	0;
						def[8]		=	0;
						def[9]		=	0;
						def[10]		=	1;
						def[11]		=	0;
						def[12]		=	0;
						def[13]		=	0;
						def[14]		=	0;
						def[15]		=	1;
					}
				;}
    break;

  case 79:
#line 1483 "sdr.y"
    {
					float	*def	=	(float *) newVariable(yyvsp[-4].string,TYPE_MATRIX,(int) yyvsp[-2].real,TRUE);
					
					if (def != NULL) {
						int	i;

						for (i=0;i<((int) yyvsp[-2].real)*16;i++)
							def[i]	=	0;
							
						currentData.currentArray = def;
					}
					
					currentData.numArrayItemsRemaining = (int) yyvsp[-2].real;
				;}
    break;

  case 81:
#line 1504 "sdr.y"
    {
					float	*def	=	(float *) newVariable(yyvsp[-3].string,TYPE_MATRIX,(int) yyvsp[-1].real,TRUE);

					if (def != NULL) {
						int	i;

						for (i=0;i<((int) yyvsp[-1].real)*16;i++)
							def[i]	=	0;
					}
				;}
    break;

  case 82:
#line 1521 "sdr.y"
    {
					if(currentData.numArrayItemsRemaining){
						slerror("wrong number of items in array initializer\n");
					}
				;}
    break;

  case 83:
#line 1548 "sdr.y"
    {
					if(currentData.numArrayItemsRemaining > 0){
						if(currentData.currentArray){
							currentData.currentArray[0] = yyvsp[-16].real;
							currentData.currentArray[1] = yyvsp[-15].real;
							currentData.currentArray[2] = yyvsp[-14].real;
							currentData.currentArray[3] = yyvsp[-13].real;
							currentData.currentArray[4] = yyvsp[-12].real;
							currentData.currentArray[5] = yyvsp[-11].real;
							currentData.currentArray[6] = yyvsp[-10].real;
							currentData.currentArray[7] = yyvsp[-9].real;
							currentData.currentArray[8] = yyvsp[-8].real;
							currentData.currentArray[9] = yyvsp[-7].real;
							currentData.currentArray[10] = yyvsp[-6].real;
							currentData.currentArray[11] = yyvsp[-5].real;
							currentData.currentArray[12] = yyvsp[-4].real;
							currentData.currentArray[13] = yyvsp[-3].real;
							currentData.currentArray[14] = yyvsp[-2].real;
							currentData.currentArray[15] = yyvsp[-1].real;
							
							currentData.currentArray += 16;
						}
						currentData.numArrayItemsRemaining--;
					}
					else{
						slerror("wrong number of items in array initializer\n");
					}
				;}
    break;

  case 84:
#line 1579 "sdr.y"
    {
					if(currentData.numArrayItemsRemaining > 0){
						if(currentData.currentArray){
							currentData.currentArray[0] = yyvsp[0].real;
							currentData.currentArray[1] = 0;
							currentData.currentArray[2] = 0;
							currentData.currentArray[3] = 0;
							currentData.currentArray[4] = 0;
							currentData.currentArray[5] = yyvsp[0].real;
							currentData.currentArray[6] = 0;
							currentData.currentArray[7] = 0;
							currentData.currentArray[8] = 0;
							currentData.currentArray[9] = 0;
							currentData.currentArray[10] = yyvsp[0].real;
							currentData.currentArray[11] = 0;
							currentData.currentArray[12] = 0;
							currentData.currentArray[13] = 0;
							currentData.currentArray[14] = 0;
							currentData.currentArray[15] = 1;
							
							currentData.currentArray += 16;
						}
						currentData.numArrayItemsRemaining--;
					}
					else{
						slerror("wrong number of items in array initializer\n");
					}
				;}
    break;

  case 97:
#line 1654 "sdr.y"
    {
					newVariable(yyvsp[0].string,TYPE_BOOLEAN,1,FALSE);
				;}
    break;

  case 98:
#line 1663 "sdr.y"
    {
					newVariable(yyvsp[-3].string,TYPE_BOOLEAN,(int) yyvsp[-1].real,FALSE);
				;}
    break;

  case 99:
#line 1672 "sdr.y"
    {
					newVariable(yyvsp[0].string,TYPE_FLOAT,1,FALSE);
				;}
    break;

  case 100:
#line 1681 "sdr.y"
    {
					newVariable(yyvsp[-3].string,TYPE_FLOAT,(int) yyvsp[-1].real,FALSE);
				;}
    break;

  case 101:
#line 1689 "sdr.y"
    {
					newVariable(yyvsp[0].string,TYPE_STRING,1,FALSE);
				;}
    break;

  case 102:
#line 1698 "sdr.y"
    {
					newVariable(yyvsp[-3].string,TYPE_STRING,(int) yyvsp[-1].real,FALSE);
				;}
    break;

  case 103:
#line 1706 "sdr.y"
    {
					newVariable(yyvsp[0].string,TYPE_VECTOR,1,FALSE);
				;}
    break;

  case 104:
#line 1715 "sdr.y"
    {
					newVariable(yyvsp[-3].string,TYPE_VECTOR,(int) yyvsp[-1].real,FALSE);
				;}
    break;

  case 105:
#line 1723 "sdr.y"
    {
					newVariable(yyvsp[0].string,TYPE_COLOR,1,FALSE);
				;}
    break;

  case 106:
#line 1732 "sdr.y"
    {
					newVariable(yyvsp[-3].string,TYPE_COLOR,(int) yyvsp[-1].real,FALSE);
				;}
    break;

  case 107:
#line 1740 "sdr.y"
    {
					newVariable(yyvsp[0].string,TYPE_NORMAL,1,FALSE);
				;}
    break;

  case 108:
#line 1749 "sdr.y"
    {
					newVariable(yyvsp[-3].string,TYPE_NORMAL,(int) yyvsp[-1].real,FALSE);
				;}
    break;

  case 109:
#line 1757 "sdr.y"
    {
					newVariable(yyvsp[0].string,TYPE_POINT,1,FALSE);
				;}
    break;

  case 110:
#line 1766 "sdr.y"
    {
					newVariable(yyvsp[-3].string,TYPE_POINT,(int) yyvsp[-1].real,FALSE);
				;}
    break;

  case 111:
#line 1774 "sdr.y"
    {
					newVariable(yyvsp[0].string,TYPE_MATRIX,1,FALSE);
				;}
    break;

  case 112:
#line 1783 "sdr.y"
    {
					newVariable(yyvsp[-3].string,TYPE_MATRIX,(int) yyvsp[-1].real,FALSE);
				;}
    break;

  case 113:
#line 1790 "sdr.y"
    {
					currentData.parsingInit	=	TRUE;
					newLabel(initLabel,FALSE);
				;}
    break;

  case 115:
#line 1799 "sdr.y"
    {
					currentData.parsingInit	=	FALSE;
					newLabel(codeLabel,FALSE);
				;}
    break;

  case 121:
#line 1824 "sdr.y"
    {
					char	*dsoName	=	yyvsp[0].string;
					
					switch(currentData.passNumber) {
					case 1:
						currentData.numCode++;					// opcode
						break;
					case 2:
						strcpy(currentData.currentOpcode,yyvsp[0].string);
						currentData.currentArgument					=	0;
						currentData.currentOpcodePlace->arguments	=	currentData.currentArgumentPlace;
						currentData.currentPrototype[0]				=	'~';
						currentData.opcodeUniform					=	TRUE;
						break;
					default:
						break;
					}
				;}
    break;

  case 122:
#line 1846 "sdr.y"
    {
					switch(currentData.passNumber) {
					case 1:
						break;
					case 2:
						// Set the opcode here
						CDSO	*dso;

						if ((dso = CRenderer::getDSO(yyvsp[-5].string,yyvsp[-2].string)) != NULL) {
							// Save the DSO opcode
							if (yyvsp[-2].string[0] == 'o')	currentData.currentOpcodePlace->opcode		=	FUNCTION_DSO_VOID;
							else				currentData.currentOpcodePlace->opcode		=	FUNCTION_DSO;

							assert(currentData.opcodeUniform < 256);
							
							currentData.currentOpcodePlace->plNumber		=	(unsigned char) (currentData.currentPL);
							currentData.currentOpcodePlace->numArguments	=	(unsigned char) (currentData.currentArgument);
							currentData.currentOpcodePlace->uniform			=	(unsigned char) (currentData.opcodeUniform);															
							currentData.currentOpcodePlace->dso				=	dso;
							currentData.currentOpcodePlace++;
						} else {
							slerror("Unable to locate DSO function\n");
						}
						break;
					default:
						break;
					}
				;}
    break;

  case 123:
#line 1878 "sdr.y"
    {
					switch(currentData.passNumber) {
					case 1:
						currentData.numCode++;		// opcode
						break;
					case 2:
						strcpy(currentData.currentOpcode,yyvsp[0].string);
						currentData.currentArgument					=	0;
						currentData.currentOpcodePlace->arguments	=	currentData.currentArgumentPlace;
						currentData.currentPrototype[0]				=	'~';
						currentData.opcodeUniform					=	TRUE;
						break;
					default:
						break;
					}
				;}
    break;

  case 124:
#line 1896 "sdr.y"
    {
					switch(currentData.passNumber) {
					case 1:
						currentData.numCode++;		// opcode
						break;
					case 2:
						strcpy(currentData.currentOpcode,"surface");
						currentData.currentArgument					=	0;
						currentData.currentOpcodePlace->arguments	=	currentData.currentArgumentPlace;
						currentData.currentPrototype[0]				=	'~';
						currentData.opcodeUniform					=	TRUE;
						break;
					default:
						break;
					}
				;}
    break;

  case 125:
#line 1914 "sdr.y"
    {
					switch(currentData.passNumber) {
					case 1:
						currentData.numCode++;		// opcode
						break;
					case 2:
						strcpy(currentData.currentOpcode,"displacement");
						currentData.currentArgument					=	0;
						currentData.currentOpcodePlace->arguments	=	currentData.currentArgumentPlace;
						currentData.currentPrototype[0]				=	'~';
						currentData.opcodeUniform					=	TRUE;
						break;
					default:
						break;
					}
				;}
    break;

  case 126:
#line 1935 "sdr.y"
    {
				;}
    break;

  case 127:
#line 1938 "sdr.y"
    {
				;}
    break;

  case 128:
#line 1945 "sdr.y"
    {
					setOpcode();
				;}
    break;

  case 129:
#line 1953 "sdr.y"
    {
					newLabel(yyvsp[-1].string,FALSE);
				;}
    break;

  case 130:
#line 1960 "sdr.y"
    {
					char	*str	=	yyvsp[0].string;

					addStringReference(&str,1);
				;}
    break;

  case 131:
#line 1967 "sdr.y"
    {
					newLabel(yyvsp[0].string,TRUE);
				;}
    break;

  case 132:
#line 1972 "sdr.y"
    {
					addVariableReference(yyvsp[0].string);
				;}
    break;

  case 133:
#line 1977 "sdr.y"
    {
					addFloatReference(&yyvsp[0].real,1);
				;}
    break;

  case 134:
#line 1988 "sdr.y"
    {
					vector	tmp;

					tmp[0]	=	yyvsp[-5].real;
					tmp[1]	=	yyvsp[-3].real;
					tmp[2]	=	yyvsp[-1].real;

					addFloatReference(tmp,3);
				;}
    break;

  case 135:
#line 2031 "sdr.y"
    {
					matrix	tmp;

					tmp[element(0,0)]	=	yyvsp[-31].real;
					tmp[element(0,1)]	=	yyvsp[-29].real;
					tmp[element(0,2)]	=	yyvsp[-27].real;
					tmp[element(0,3)]	=	yyvsp[-25].real;
					tmp[element(1,0)]	=	yyvsp[-23].real;
					tmp[element(1,1)]	=	yyvsp[-21].real;
					tmp[element(1,2)]	=	yyvsp[-19].real;
					tmp[element(1,3)]	=	yyvsp[-17].real;
					tmp[element(2,0)]	=	yyvsp[-15].real;
					tmp[element(2,1)]	=	yyvsp[-13].real;
					tmp[element(2,2)]	=	yyvsp[-11].real;
					tmp[element(2,3)]	=	yyvsp[-9].real;
					tmp[element(3,0)]	=	yyvsp[-7].real;
					tmp[element(3,1)]	=	yyvsp[-5].real;
					tmp[element(3,2)]	=	yyvsp[-3].real;
					tmp[element(3,3)]	=	yyvsp[-1].real;

					addFloatReference(tmp,16);
				;}
    break;

  case 136:
#line 2057 "sdr.y"
    {
					strcpy(currentData.currentPrototype,yyvsp[-1].string);
				;}
    break;


    }

/* Line 1000 of yacc.c.  */
#line 3105 "sl.cpp"

  yyvsp -= yylen;
  yyssp -= yylen;


  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* If at end of input, pop the error token,
	     then the rest of the stack, then return failure.  */
	  if (yychar == YYEOF)
	     for (;;)
	       {
		 YYPOPSTACK;
		 if (yyssp == yyss)
		   YYABORT;
		 YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
		 yydestruct (yystos[*yyssp], yyvsp);
	       }
        }
      else
	{
	  YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
	  yydestruct (yytoken, &yylval);
	  yychar = YYEMPTY;

	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

#ifdef __GNUC__
  /* Pacify GCC when the user code never invokes YYERROR and the label
     yyerrorlab therefore never appears in user code.  */
  if (0)
     goto yyerrorlab;
#endif

  yyvsp -= yylen;
  yyssp -= yylen;
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 2062 "sdr.y"

#include "lex.sl.cpp"

int	slLineno	=	0;

///////////////////////////////////////////////////////////////////////
// Function				:	slerror
// Description			:	Parser error function
// Return Value			:
// Comments				:
void	slerror(char *s) {
	warning(CODE_BADFILE,"Error in shader \"%s\" (%d) (\"%s\") (v%d.%d.%d)\n",currentData.name,slLineno,s,VERSION_RELEASE,VERSION_BETA,VERSION_ALPHA);
	currentData.numErrors++;
}


///////////////////////////////////////////////////////////////////////
// Function				:	parseShader
// Description			:	Parse a shader
// Return Value			:	Parsed shader if successful
// Comments				:
CShader	*parseShader(const char *shaderName,const char *name) {
	YY_BUFFER_STATE	oldState;

	FILE	*fin;

	fin						=	fopen(name,"r");
	
	if (fin == NULL) return NULL;

	oldState				=	YY_CURRENT_BUFFER;
	sl_switch_to_buffer(sl_create_buffer( fin, YY_BUF_SIZE ) );

	slLineno				=	0;

	slin					=	fin;

	reset();
	currentData.name					=	name;
	currentData.passNumber				=	1;
	slparse();

	if (currentData.numErrors != 0) {
		sl_delete_buffer( YY_CURRENT_BUFFER );
		fclose(fin);
		sl_switch_to_buffer( oldState );
		return NULL;
	}

	slLineno				=	0;

	fseek(fin,0,SEEK_SET);
	alloc();
	currentData.passNumber				=	2;
	
	slparse();
	if (currentData.numErrors != 0) {
		reset();
		sl_delete_buffer( YY_CURRENT_BUFFER );
		fclose(fin);
		sl_switch_to_buffer( oldState );
		return NULL;
	} else {
		CShader	*cShader	=	shaderCreate(shaderName);
		reset();
		sl_delete_buffer( YY_CURRENT_BUFFER );
		fclose(fin);
		sl_switch_to_buffer( oldState );
		return cShader;
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	reset
// Description			:	Deallocate any previously allocated memory for the shader
// Return Value			:	-
// Comments				:
void	reset() {
	if (currentData.strings != NULL) {
		int	i;

		for (i=0;i<currentData.numStrings;i++)
			if (currentData.strings[i] != NULL)
				free(currentData.strings[i]);
	}


	if (currentData.definedVariables != NULL) {
		TSlVariable	*cVar,*nVar;

		for (cVar=currentData.definedVariables;cVar != NULL;) {
			nVar	=	cVar->next;
			delete cVar;
			cVar	=	nVar;
			
			// FIXME: Clear the parameter if not NULL
		}
	}


	if (currentData.labelDefinitions != NULL) {
		TSlLabel	*cLabel,*nLabel;

		for (cLabel=currentData.labelDefinitions;cLabel != NULL;) {
			nLabel	=	cLabel->next;
			delete cLabel;
			cLabel	=	nLabel;
		}
	}

	if (currentData.labelReferences != NULL) {
		TSlLabel	*cLabel,*nLabel;

		for (cLabel=currentData.labelReferences;cLabel != NULL;) {
			nLabel	=	cLabel->next;
			delete cLabel;
			cLabel	=	nLabel;
		}
	}

	if (currentData.memory != NULL)		delete [] currentData.memory;

	// Clear currentData
	memset(&currentData,0,sizeof(TShaderData));
}

///////////////////////////////////////////////////////////////////////
// Function				:	alloc
// Description			:	Allocate required space for the shader
// Return Value			:
// Comments				:
void	alloc() {
	char	*mem;

	currentData.memory	=	(char *) allocate_untyped(	currentData.numCode*sizeof(TCode)	+
														currentData.numArgument*sizeof(TArgument)	+
														currentData.constantSize +
														currentData.numConstants*sizeof(void *) + 
														currentData.numVariables*sizeof(int) + 
														currentData.numStrings*sizeof(char *));

	mem		=	currentData.memory;

	if (currentData.numCode != 0) {
		currentData.code						=	(TCode *) mem;
		currentData.currentOpcodePlace			=	currentData.code;
		mem										+=	currentData.numCode*sizeof(TCode);
	}
	
	if (currentData.numArgument != 0) {
		currentData.arguments					=	(TArgument *) mem;
		currentData.currentArgumentPlace		=	currentData.arguments;
		mem										+=	currentData.numArgument*sizeof(TArgument);
	}

	if (currentData.constantSize != 0) {
		currentData.constants					=	mem;
		mem										+=	currentData.constantSize;
	}

	if (currentData.numConstants != 0) {
		currentData.constantEntries				=	(void **) mem;
		mem										+=	currentData.numConstants*sizeof(void *);
	}

	if (currentData.numVariables != 0) {
		currentData.varyingSizes				=	(int *) mem;
		mem										+=	currentData.numVariables*sizeof(int);
	}

	if (currentData.numStrings != 0) {
		int	i;

		currentData.strings						=	(char **) mem;
		mem										+=	currentData.numStrings*sizeof(char *);

		for (i=0;i<currentData.numStrings;i++) {
			currentData.strings[i]				=	NULL;
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	shaderCreate
// Description			:	Parse successful, allocate the shader
// Return Value			:
// Comments				:
CShader	*shaderCreate(const char *shaderName) {
	CShader	*cShader;


	assert(currentData.numConstants		==	currentData.currentConstant);
	assert(currentData.numVariables		==	currentData.currentVariable);
	assert(currentData.numStrings		==	currentData.currentString);
	assert(currentData.constantSize		==	currentData.currentConstantSize);
	assert(currentData.varyingSize		==	currentData.currentVaryingSize);


	// Fix the labels
	{
		TSlLabel	*cLabel,*nLabel;

		for (cLabel = currentData.labelReferences;cLabel != NULL;cLabel = cLabel->next) {
			for (nLabel = currentData.labelDefinitions;nLabel != NULL;nLabel = nLabel->next) {
				if (strcmp(cLabel->name,nLabel->name) == 0) {
					cLabel->argument->index	=	nLabel->index;
					break;
				}
			}

			if (nLabel == NULL) {
				slerror("Label not found");
				return NULL;
			}
		}

		for (cLabel = currentData.labelDefinitions;cLabel != NULL;cLabel = cLabel->next) {
			if (strcmp(cLabel->name,codeLabel) == 0) {
				currentData.codeEntryPoint	=	cLabel->index;
			}

			if (strcmp(cLabel->name,initLabel) == 0) {
				currentData.initEntryPoint	=	cLabel->index;
			}
		}
	}

	cShader								=	new CShader(shaderName);

	cShader->memory						=	currentData.memory;

	cShader->codeArea					=	currentData.code;

	cShader->constantEntries			=	currentData.constantEntries;
	cShader->varyingSizes				=	currentData.varyingSizes;

	cShader->strings					=	currentData.strings;

	cShader->numStrings					=	currentData.numStrings;
	cShader->numVariables				=	currentData.numVariables;
	cShader->numPLs						=	currentData.currentPL;

	cShader->codeEntryPoint				=	currentData.codeEntryPoint;
	cShader->initEntryPoint				=	currentData.initEntryPoint;

	cShader->usedParameters				=	currentData.usedParameters;

	cShader->type						=	currentData.shaderType;

	{
		TSlVariable	*cVar;
		int			i,numGlobals=0;

		cShader->parameters				=	NULL;
		i								=	0;
		while(currentData.definedVariables != NULL) {
			cVar							=	currentData.definedVariables;
			currentData.definedVariables	=	cVar->next;
		
			// Is this a parameter ? 
			if (cVar->variable != NULL) {
				cVar->variable->next	=	cShader->parameters;
				cShader->parameters		=	cVar->variable;
				if (cVar->variable->storage == STORAGE_GLOBAL ||
					cVar->variable->storage == STORAGE_MUTABLEPARAMETER)
						numGlobals++;
			} 
			
			// Delete the variable
			delete cVar;
			i++;
		}
		
		cShader->numGlobals	=	numGlobals;
	}
	
	

	currentData.memory					=	NULL;
	currentData.code					=	NULL;
	currentData.constants				=	NULL;
	currentData.varyingSizes			=	NULL;
	currentData.strings					=	NULL;
	currentData.constantEntries			=	NULL;


	return cShader;
}

///////////////////////////////////////////////////////////////////////
// Function				:
// Description			:
// Return Value			:
// Comments				:
void	processEscapes(char *str) {
	int		i,n,j;

	n	=	(int) strlen(str);
	for (i=0;i<n;i++) {
		if (str[i] == '\\') {
			switch(str[i+1]) {
			case 'n':
				str[i]	=	'\n';
				break;
			case 't':
				str[i]	=	'\t';
				break;
			case 'r':
				str[i]	=	'\r';
				break;
			case '\\':
				str[i]	=	'\\';
				break;
			default:
				break;
			}

			j	=	i+2;
			do {
				str[j-1]	=	str[j];
				j++;
			} while(str[j] != '\0');
			n--;
			i++;
		}
	}
	str[i]	=	'\0';
}

extern	void		convertColorFrom(float *out,const float *in,ECoordinateSystem s);



