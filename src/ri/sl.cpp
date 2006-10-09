
/*  A Bison parser, made from sdr.y
    by GNU Bison version 1.28  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse slparse
#define yylex sllex
#define yyerror slerror
#define yylval sllval
#define yychar slchar
#define yydebug sldebug
#define yynerrs slnerrs
#define	SCRL_PARAMETERS	257
#define	SCRL_VARIABLES	258
#define	SCRL_OUTPUT	259
#define	SCRL_VARYING	260
#define	SCRL_UNIFORM	261
#define	SCRL_BOOLEAN	262
#define	SCRL_FLOAT	263
#define	SCRL_COLOR	264
#define	SCRL_VECTOR	265
#define	SCRL_NORMAL	266
#define	SCRL_POINT	267
#define	SCRL_MATRIX	268
#define	SCRL_STRING	269
#define	SCRL_SURFACE	270
#define	SCRL_DISPLACEMENT	271
#define	SCRL_IMAGER	272
#define	SCRL_LIGHTSOURCE	273
#define	SCRL_VOLUME	274
#define	SCRL_GENERIC	275
#define	SCRL_DSO	276
#define	SCRL_INIT	277
#define	SCRL_CODE	278
#define	SCRL_DOT	279
#define	SCRL_COLON	280
#define	SCRL_EQUAL	281
#define	SCRL_OPEN_PARANTHESIS	282
#define	SCRL_CLOSE_PARANTHESIS	283
#define	SCRL_OPEN_SQR_PARANTHESIS	284
#define	SCRL_CLOSE_SQR_PARANTHESIS	285
#define	SCRL_COMMA	286
#define	SCRL_NL	287
#define	SCRL_TEXT_VALUE	288
#define	SCRL_IDENTIFIER_VALUE	289
#define	SCRL_LABEL_VALUE	290
#define	SCRL_FLOAT_VALUE	291

#line 1 "sdr.y"

//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright � 1999 - 2003, Okan Arikan
//
// Contact: okan@cs.berkeley.edu
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
// 
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
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
#include "renderer.h"
#include "error.h"

/////////////////////////////////////////////////////////////////////////////////////
//   First some temporary data structures used during the script parsing


// Some forward definitions
		void							slerror(char *);			// Forward definition for stupid yacc
		int								sllex(void );				// Forward definition for stupid yacc

		static	char					*initLabel	=	"#!Init";	// The label for the init
		static	char					*codeLabel	=	"#!Code";	// The label for the code

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

				// Pass 1
				int						numCode;				// The number of code blocks
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
				int						currentCode;			// Current xXx
				int						currentConstant;
				int						currentVariable;
				int						currentString;
				int						currentPL;				// The current parameter list

				int						currentConstantSize;
				int						currentVaryingSize;

				TCode					*currentArray;			// Array items go here as we read them
				int						numArrayItemsRemaining;	// Number of array items we're still expecting to read
				
				char					currentOpcode[32];		// Holds the opcode being parsed
				char					currentPrototype[32];	// Holds the prototype being parsed
				int						currentArgument;		// The current argument number
				unsigned int			usedParameters;			// Used parameters by this shader
				TCode					*currentOpcodePlace;	// Points to the code that should holds the opcode

				int						codeEntryPoint;			// Indices in the code array for corresponding entry points
				int						initEntryPoint;
				
				TCode					*memory;				// The memory base for the area that's allocated
				TCode					*code;					// Code blocks
				TCode					*constants;				// Constants blocks
				int						*varyingSizes;			// Holds the size of each varying in codes
				char					**strings;				// Strings defined
				TCode					**constantEntries;

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
									// Date last edited		:	8/8/2001
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
									// Date last edited		:	8/8/2001
		static	TCode				*newVariable(char *name,EVariableType type,int numItems,int parameter) {
										const int	numComp			=	numComponents(type);

										switch(currentData.passNumber) {
										case 1:
											currentData.numVariables++;
											currentData.varyingSize		+=	numItems*numComp;
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
												currentData.currentVaryingSize	+=	numItems*numComp;
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
													newVariable->next			=	NULL;													
													cVariable->variable			=	newVariable;
													
													// Is this a global variable ?
													gVariable					=	currentRenderer->retrieveVariable(name);
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
													
													return	(TCode *) (newVariable->defaultValue);
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
									// Date last edited		:	8/8/2001
		static	void				addStringReference(char **items,int numItems) {
										int	i;
										
										switch(currentData.passNumber) {
										case 1:
											currentData.numCode			+=	1;
											currentData.numConstants	+=	1;
											currentData.numStrings		+=	numItems;
											currentData.constantSize	+=	numItems;
											break;
										case 2:
											assert(currentData.currentConstant < 65535);
											
											currentData.code[currentData.currentCode].reference.numItems	=	0;
											currentData.code[currentData.currentCode].reference.index		=	(unsigned short) currentData.currentConstant;
											currentData.code[currentData.currentCode].reference.accessor	=	SL_IMMEDIATE_OPERAND;
											currentData.constantEntries[currentData.currentConstant]		=	&currentData.constants[currentData.currentConstantSize];
											currentData.currentCode++;
											currentData.currentConstant++;

											for (i=0;i<numItems;i++)
												currentData.constants[currentData.currentConstantSize++].string		=	currentData.strings[currentData.currentString++]	=	strdup(items[i]);

											currentData.currentArgument++;
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
									// Date last edited		:	8/8/2001
		static	void				addFloatReference(float *items,int numItems) {
										int	i;
										switch(currentData.passNumber) {
											case 1:
												currentData.numCode			+=	1;
												currentData.numConstants	+=	1;
												currentData.constantSize	+=	numItems;
												break;
											case 2:
												assert(currentData.currentConstant < 65536);
												
												currentData.code[currentData.currentCode].reference.numItems	=	0;
												currentData.code[currentData.currentCode].reference.index		=	(unsigned short) currentData.currentConstant;
												currentData.code[currentData.currentCode].reference.accessor	=	SL_IMMEDIATE_OPERAND;
												currentData.constantEntries[currentData.currentConstant]		=	&currentData.constants[currentData.currentConstantSize];
												currentData.currentCode++;
												currentData.currentConstant++;

												for (i=0;i<numItems;i++)
													currentData.constants[currentData.currentConstantSize++].real	=	items[i];

												currentData.currentArgument++;
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
										// Date last edited		:	8/8/2001
		static	void					addVariableReference(char *name) {
											CVariable		*var;
											TSlVariable		*cVariable;

											switch(currentData.passNumber) {
											case 1:
												currentData.numCode	+=	1;
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
														
														currentData.code[currentData.currentCode].reference.index		=	(unsigned short) cVariable->index;
														currentData.code[currentData.currentCode].reference.numItems	=	(char) (cVariable->multiplicity*numComponents(cVariable->type));
														currentData.code[currentData.currentCode].reference.accessor	=	SL_VARYING_OPERAND;
														
														if (cVariable->uniform == FALSE)
															currentData.opcodeUniform									=	FALSE;

														currentData.currentCode++;
														return;
													}
												}

												var	=	currentRenderer->retrieveVariable(name);

												if (var != NULL) {
													currentData.usedParameters										|=	var->usageMarker;

													assert(var->entry < 65536);
													assert(var->numFloats < 256);
													
													currentData.code[currentData.currentCode].reference.index		=	(unsigned short) var->entry;
													currentData.code[currentData.currentCode].reference.numItems	=	(char) var->numFloats;
													currentData.code[currentData.currentCode].reference.accessor	=	SL_GLOBAL_OPERAND;
													
													if ((var->container != CONTAINER_UNIFORM) || (var->container != CONTAINER_CONSTANT))
															currentData.opcodeUniform								=	FALSE;
															
													currentData.currentCode++;
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
										// Date last edited		:	8/8/2001
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
														currentData.usedParameters									|=	opcodes[i].usedParameters;
														currentData.currentOpcodePlace[0].integer					=	(int) opcode;
														currentData.currentOpcodePlace[1].arguments.numCodes		=	(unsigned char) (currentData.currentArgument+2);
														currentData.currentOpcodePlace[1].arguments.numArguments	=	(unsigned char) (currentData.currentArgument);
														currentData.currentOpcodePlace[1].arguments.uniform			=	(unsigned char) (currentData.opcodeUniform);
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
														
														currentData.currentOpcodePlace[0].integer						=	(int) opcode;
														currentData.currentOpcodePlace[1].arguments.numCodes			=	(unsigned char) (currentData.currentArgument+2);
														currentData.currentOpcodePlace[1].arguments.plNumber			=	(unsigned char) (currentData.currentPL);
														currentData.currentOpcodePlace[1].arguments.numArguments		=	(unsigned char) (currentData.currentArgument);
														currentData.currentOpcodePlace[1].arguments.uniform				=	(unsigned char) (currentData.opcodeUniform);
														if (strchr(functions[i].prototype,'!') != NULL)	currentData.currentPL++;
													} else {
														// Allright, we could not find the function, check the DSO shaders
														void			*handle;
														dsoExecFunction	exec;

														if (currentRenderer->getDSO(currentData.currentOpcode,currentData.currentPrototype,handle,exec) == TRUE) {
															// We have the DSO
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
									// Date last edited		:	8/8/2001
		static	void				newLabel(char *name,int reference) {
										switch(currentData.passNumber) {
										case 1:
											if (reference)
												currentData.numCode++;
											break;
										case 2:
											{
												TSlLabel	*cLabel	=	new TSlLabel;

												strcpy(cLabel->name,name);
												cLabel->index	=	currentData.currentCode;

												if (reference) {
													cLabel->next					=	currentData.labelReferences;
													currentData.labelReferences		=	cLabel;
													currentData.currentCode++;
													currentData.currentArgument++;
												} else {
													TSlLabel	*tLabel;

													for (tLabel=currentData.labelDefinitions;tLabel!=NULL;tLabel=tLabel->next) {
														if (strcmp(tLabel->name,cLabel->name) == 0) {
															slerror("Duplicate label definition\n");
														}
													}

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

#line 659 "sdr.y"
typedef union slval {
	float	real;
	char	string[64];
	matrix	m;
	vector	v;
} YYSTYPE;
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		316
#define	YYFLAG		-32768
#define	YYNTBASE	38

#define YYTRANSLATE(x) ((unsigned)(x) <= 291 ? yytranslate[x] : 98)

static const char yytranslate[] = {     0,
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
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     3,     4,     5,     6,
     7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
    17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
    27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
    37
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     7,     8,    11,    15,    23,    26,    33,    34,    36,
    39,    42,    45,    48,    51,    56,    60,    61,    63,    65,
    68,    71,    73,    74,    77,    79,    81,    83,    85,    87,
    89,    91,    96,    99,   100,   109,   115,   119,   122,   123,
   126,   131,   132,   141,   147,   151,   154,   155,   156,   161,
   162,   171,   177,   178,   183,   184,   193,   199,   200,   205,
   206,   215,   221,   222,   227,   228,   237,   243,   246,   253,
   255,   261,   265,   268,   269,   291,   296,   299,   300,   309,
   315,   319,   339,   342,   343,   348,   352,   353,   356,   359,
   362,   365,   368,   371,   374,   377,   380,   386,   389,   395,
   398,   404,   407,   413,   416,   422,   425,   431,   434,   440,
   443,   449,   450,   455,   456,   461,   465,   469,   473,   474,
   475,   483,   485,   487,   489,   492,   493,   496,   499,   501,
   503,   505,   507,   515,   549
};

static const short yyrhs[] = {    42,
    43,    75,    86,    88,    39,     0,     0,    33,    39,     0,
    27,    34,    37,     0,    27,    34,    30,    37,    37,    37,
    31,     0,    27,    37,     0,    27,    30,    37,    37,    37,
    31,     0,     0,    40,     0,    16,    33,     0,    17,    33,
     0,    19,    33,     0,    20,    33,     0,    18,    33,     0,
     3,    26,    33,    44,     0,    44,    46,    33,     0,     0,
     7,     0,     6,     0,     5,     7,     0,     5,     6,     0,
     5,     0,     0,    45,    47,     0,    48,     0,    52,     0,
    56,     0,    59,     0,    62,     0,    65,     0,    71,     0,
     9,    35,    27,    37,     0,     9,    35,     0,     0,     9,
    35,    30,    37,    31,    27,    49,    50,     0,     9,    35,
    30,    37,    31,     0,    30,    51,    31,     0,    51,    37,
     0,     0,    15,    35,     0,    15,    35,    27,    34,     0,
     0,    15,    35,    30,    37,    31,    27,    53,    54,     0,
    15,    35,    30,    37,    31,     0,    30,    55,    31,     0,
    55,    34,     0,     0,     0,    10,    35,    57,    41,     0,
     0,    10,    35,    30,    37,    31,    27,    58,    69,     0,
    10,    35,    30,    37,    31,     0,     0,    11,    35,    60,
    41,     0,     0,    11,    35,    30,    37,    31,    27,    61,
    69,     0,    11,    35,    30,    37,    31,     0,     0,    12,
    35,    63,    41,     0,     0,    12,    35,    30,    37,    31,
    27,    64,    69,     0,    12,    35,    30,    37,    31,     0,
     0,    13,    35,    66,    41,     0,     0,    13,    35,    30,
    37,    31,    27,    67,    69,     0,    13,    35,    30,    37,
    31,     0,    34,    37,     0,    34,    30,    37,    37,    37,
    31,     0,    37,     0,    30,    37,    37,    37,    31,     0,
    30,    70,    31,     0,    70,    68,     0,     0,    14,    35,
    27,    30,    37,    37,    37,    37,    37,    37,    37,    37,
    37,    37,    37,    37,    37,    37,    37,    37,    31,     0,
    14,    35,    27,    37,     0,    14,    35,     0,     0,    14,
    35,    30,    37,    31,    27,    72,    73,     0,    14,    35,
    30,    37,    31,     0,    30,    74,    31,     0,    74,    30,
    37,    37,    37,    37,    37,    37,    37,    37,    37,    37,
    37,    37,    37,    37,    37,    37,    31,     0,    74,    37,
     0,     0,     4,    26,    33,    76,     0,    76,    77,    33,
     0,     0,    45,    78,     0,    45,    79,     0,    45,    80,
     0,    45,    82,     0,    45,    81,     0,    45,    83,     0,
    45,    84,     0,    45,    85,     0,     8,    35,     0,     8,
    35,    30,    37,    31,     0,     9,    35,     0,     9,    35,
    30,    37,    31,     0,    15,    35,     0,    15,    35,    30,
    37,    31,     0,    11,    35,     0,    11,    35,    30,    37,
    31,     0,    10,    35,     0,    10,    35,    30,    37,    31,
     0,    12,    35,     0,    12,    35,    30,    37,    31,     0,
    13,    35,     0,    13,    35,    30,    37,    31,     0,    14,
    35,     0,    14,    35,    30,    37,    31,     0,     0,    23,
    33,    87,    90,     0,     0,    24,    33,    89,    90,     0,
    90,    95,    33,     0,    90,    96,    33,     0,    90,    91,
    33,     0,     0,     0,    22,    35,    92,    28,    34,    29,
    94,     0,    35,     0,    16,     0,    17,     0,    97,    94,
     0,     0,    93,    94,     0,    36,    26,     0,    34,     0,
    36,     0,    35,     0,    37,     0,    28,    37,    32,    37,
    32,    37,    29,     0,    28,    37,    32,    37,    32,    37,
    32,    37,    32,    37,    32,    37,    32,    37,    32,    37,
    32,    37,    32,    37,    32,    37,    32,    37,    32,    37,
    32,    37,    32,    37,    32,    37,    29,     0,    28,    34,
    29,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   711,   720,   721,   726,   734,   747,   755,   767,   775,   783,
   789,   795,   801,   807,   815,   822,   826,   829,   836,   843,
   851,   859,   866,   875,   881,   883,   885,   887,   889,   891,
   893,   898,   910,   920,   942,   942,   961,   972,   986,   990,
  1009,  1030,  1061,  1061,  1078,  1089,  1104,  1108,  1115,  1127,
  1142,  1142,  1153,  1160,  1172,  1189,  1189,  1200,  1207,  1219,
  1236,  1236,  1247,  1254,  1266,  1283,  1283,  1294,  1301,  1313,
  1320,  1334,  1345,  1364,  1368,  1412,  1439,  1464,  1485,  1485,
  1504,  1515,  1563,  1594,  1598,  1605,  1609,  1612,  1615,  1618,
  1621,  1624,  1627,  1630,  1633,  1638,  1644,  1656,  1662,  1673,
  1679,  1690,  1696,  1707,  1713,  1724,  1730,  1741,  1747,  1758,
  1764,  1775,  1782,  1784,  1791,  1793,  1797,  1801,  1805,  1809,
  1829,  1865,  1884,  1903,  1924,  1929,  1934,  1942,  1950,  1957,
  1962,  1967,  1972,  1989,  2045
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","SCRL_PARAMETERS",
"SCRL_VARIABLES","SCRL_OUTPUT","SCRL_VARYING","SCRL_UNIFORM","SCRL_BOOLEAN",
"SCRL_FLOAT","SCRL_COLOR","SCRL_VECTOR","SCRL_NORMAL","SCRL_POINT","SCRL_MATRIX",
"SCRL_STRING","SCRL_SURFACE","SCRL_DISPLACEMENT","SCRL_IMAGER","SCRL_LIGHTSOURCE",
"SCRL_VOLUME","SCRL_GENERIC","SCRL_DSO","SCRL_INIT","SCRL_CODE","SCRL_DOT","SCRL_COLON",
"SCRL_EQUAL","SCRL_OPEN_PARANTHESIS","SCRL_CLOSE_PARANTHESIS","SCRL_OPEN_SQR_PARANTHESIS",
"SCRL_CLOSE_SQR_PARANTHESIS","SCRL_COMMA","SCRL_NL","SCRL_TEXT_VALUE","SCRL_IDENTIFIER_VALUE",
"SCRL_LABEL_VALUE","SCRL_FLOAT_VALUE","start","slEmptySpace","slVectorIn","slVector",
"slType","slParameterDefinitions","slParameters","slContainer","slParameter",
"slAParameter","slFloatParameter","@1","slFloatArrayInitializer","slFloatArrayInitializerItems",
"slStringParameter","@2","slStringArrayInitializer","slStringArrayInitializerItems",
"slColorParameter","@3","@4","slVectorParameter","@5","@6","slNormalParameter",
"@7","@8","slPointParameter","@9","@10","slVectorValue","slVectorArrayInitializer",
"slVectorArrayInitializerItems","slMatrixParameter","@11","slMatrixArrayInitializer",
"slMatrixArrayInitializerItems","slVariableDefinitions","slVariables","slVariable",
"slBooleanVariable","slFloatVariable","slStringVariable","slVectorVariable",
"slColorVariable","slNormalVariable","slPointVariable","slMatrixVariable","slInit",
"@12","slCode","@13","slShaderLine","slDSO","@14","slOpcode","slOperandList",
"slStatement","slLabelDefinition","slOperand", NULL
};
#endif

static const short yyr1[] = {     0,
    38,    39,    39,    40,    40,    40,    40,    40,    41,    42,
    42,    42,    42,    42,    43,    44,    44,    45,    45,    45,
    45,    45,    45,    46,    47,    47,    47,    47,    47,    47,
    47,    48,    48,    49,    48,    48,    50,    51,    51,    52,
    52,    53,    52,    52,    54,    55,    55,    57,    56,    58,
    56,    56,    60,    59,    61,    59,    59,    63,    62,    64,
    62,    62,    66,    65,    67,    65,    65,    68,    68,    68,
    68,    69,    70,    70,    71,    71,    71,    72,    71,    71,
    73,    74,    74,    74,    75,    76,    76,    77,    77,    77,
    77,    77,    77,    77,    77,    78,    78,    79,    79,    80,
    80,    81,    81,    82,    82,    83,    83,    84,    84,    85,
    85,    87,    86,    89,    88,    90,    90,    90,    90,    92,
    91,    93,    93,    93,    94,    94,    95,    96,    97,    97,
    97,    97,    97,    97,    97
};

static const short yyr2[] = {     0,
     6,     0,     2,     3,     7,     2,     6,     0,     1,     2,
     2,     2,     2,     2,     4,     3,     0,     1,     1,     2,
     2,     1,     0,     2,     1,     1,     1,     1,     1,     1,
     1,     4,     2,     0,     8,     5,     3,     2,     0,     2,
     4,     0,     8,     5,     3,     2,     0,     0,     4,     0,
     8,     5,     0,     4,     0,     8,     5,     0,     4,     0,
     8,     5,     0,     4,     0,     8,     5,     2,     6,     1,
     5,     3,     2,     0,    21,     4,     2,     0,     8,     5,
     3,    19,     2,     0,     4,     3,     0,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     5,     2,     5,     2,
     5,     2,     5,     2,     5,     2,     5,     2,     5,     2,
     5,     0,     4,     0,     4,     3,     3,     3,     0,     0,
     7,     1,     1,     1,     2,     0,     2,     2,     1,     1,
     1,     1,     7,    33,     3
};

static const short yydefact[] = {     0,
     0,     0,     0,     0,     0,     0,    10,    11,    14,    12,
    13,     0,     0,     0,     0,     0,    17,     0,     0,     0,
    23,    87,   112,     0,     2,    22,    19,    18,     0,     0,
    23,   119,   114,     2,     1,    21,    20,     0,     0,     0,
     0,     0,     0,     0,    24,    25,    26,    27,    28,    29,
    30,    31,    16,     0,     0,   113,   119,     3,    33,    48,
    53,    58,    63,    77,    40,     0,     0,     0,     0,     0,
     0,     0,     0,    88,    89,    90,    92,    91,    93,    94,
    95,    86,   123,   124,     0,   122,     0,     0,   126,     0,
     0,   115,     0,     0,     0,     8,     0,     8,     0,     8,
     0,     8,     0,     0,     0,     0,    96,    98,   104,   102,
   106,   108,   110,   100,   120,   128,   118,     0,   129,   131,
   130,   132,   127,   126,   116,   117,    32,     0,     0,     0,
     9,    49,     0,    54,     0,    59,     0,    64,     0,    76,
     0,    41,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,   125,    36,    52,     0,     0,     6,
    57,    62,    67,     0,    80,    44,     0,     0,     0,     0,
     0,     0,     0,     0,     0,   135,     0,    34,    50,     0,
     0,     4,    55,    60,    65,     0,    78,    42,    97,    99,
   105,   103,   107,   109,   111,   101,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   126,     0,
    39,    35,    74,    51,     0,     0,    56,    61,    66,     0,
    84,    79,    47,    43,   121,     0,     0,     0,     7,     0,
     0,     0,     0,   133,     0,    37,    38,     0,    72,     0,
    70,    73,     5,     0,     0,    81,    83,    45,    46,     0,
     0,     0,    68,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    71,     0,     0,     0,
     0,    69,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    75,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,    82,     0,     0,     0,     0,     0,     0,
     0,     0,   134,     0,     0,     0
};

static const short yydefgoto[] = {   314,
    35,   131,   132,     6,    13,    21,    29,    30,    45,    46,
   199,   212,   227,    47,   208,   224,   233,    48,    96,   200,
    49,    98,   203,    50,   100,   204,    51,   102,   205,   242,
   214,   228,    52,   207,   222,   232,    16,    31,    55,    74,
    75,    76,    77,    78,    79,    80,    81,    20,    32,    25,
    57,    56,    88,   152,    89,   123,    90,    91,   124
};

static const short yypact[] = {    41,
   -16,    12,    23,    46,    53,    31,-32768,-32768,-32768,-32768,
-32768,    50,    63,    54,    62,    49,-32768,    56,    57,    67,
    58,-32768,-32768,    59,    60,    77,-32768,-32768,    40,    61,
    -1,-32768,-32768,    60,-32768,-32768,-32768,    64,    65,    66,
    68,    69,    70,    71,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,    15,    74,   -15,-32768,-32768,    17,    72,
    78,    79,    80,    39,    43,    76,    81,    82,    83,    84,
    85,    86,    87,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,    88,-32768,    89,    91,   -25,    92,
    93,   -15,    75,    90,    94,   101,    95,   101,    96,   101,
    97,   101,   -22,    98,   102,   100,    99,   108,   109,   110,
   111,   112,   113,   114,-32768,-32768,-32768,    34,-32768,-32768,
-32768,-32768,-32768,   -25,-32768,-32768,-32768,   115,   116,     3,
-32768,-32768,   117,-32768,   118,-32768,   119,-32768,   120,-32768,
   121,-32768,   122,   123,   124,   125,   126,   127,   128,   129,
   130,   131,   139,   137,-32768,   103,   143,   134,     6,-32768,
   145,   146,   147,   138,   149,   150,   148,   151,   152,   153,
   154,   155,   156,   157,   144,-32768,   158,-32768,-32768,   159,
   160,-32768,-32768,-32768,-32768,   161,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,   162,   167,   163,   164,
   165,   166,   164,   164,   164,   168,   170,   171,   -25,   169,
-32768,-32768,-32768,-32768,   173,   172,-32768,-32768,-32768,   174,
-32768,-32768,-32768,-32768,-32768,    45,   -18,     1,-32768,   176,
   175,    11,    44,-32768,   177,-32768,-32768,   178,-32768,     9,
-32768,-32768,-32768,   179,   180,-32768,-32768,-32768,-32768,   181,
   182,   183,-32768,   184,   185,   186,   187,   188,   189,   190,
   196,   198,   193,   194,   195,   197,-32768,   202,   199,   200,
   203,-32768,   201,   204,   205,   206,   207,   208,   209,   210,
   211,   212,   213,   219,   215,   216,   217,   214,   218,   224,
-32768,   220,   221,   222,   228,   225,   226,   227,   229,   230,
   231,   234,   237,-32768,   233,   239,   235,   241,   238,   242,
   240,   247,-32768,   192,   266,-32768
};

static const short yypgoto[] = {-32768,
   244,-32768,   -84,-32768,-32768,-32768,   248,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -123,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,    38,-32768,-32768,-32768,  -124,-32768,-32768,-32768
};


#define	YYLAST		279


static const short yytable[] = {   155,
    83,    84,   118,    26,    27,    28,    85,   139,   119,   120,
   121,   122,   236,   134,   140,   136,     7,   138,   237,    86,
    87,   -85,    66,    67,    68,    69,    70,    71,    72,    73,
   238,   239,   158,    12,   240,   181,   159,   241,   252,   160,
   245,   246,   182,    93,     8,   253,    94,   247,    38,    39,
    40,    41,    42,    43,    44,     9,     1,     2,     3,     4,
     5,   -15,    26,    27,    28,   103,    15,   153,   104,   105,
   154,    19,   106,   234,   248,    14,   235,   249,    10,   217,
   218,   219,    36,    37,   225,    11,    17,    18,    22,    23,
    24,    33,    34,    53,    92,     0,     0,     0,    59,    60,
    61,    95,    62,    63,    64,    65,    82,    97,    99,   101,
   107,   127,     0,     0,   116,   108,   109,   110,   111,   112,
   113,   114,   115,   117,   125,   126,   128,   130,   144,   178,
   129,   133,   135,   137,   141,   142,   143,   145,   146,   147,
   148,   149,   150,   151,     0,   156,   157,   161,   162,   163,
     0,   165,   166,     0,     0,     0,   164,     0,   175,   167,
   168,   169,   170,   171,   172,   173,   174,   176,   177,   179,
   180,   183,   184,   185,   186,   187,   188,   197,   189,     0,
     0,   190,   191,   192,   193,   194,   195,   196,     0,     0,
   209,   315,   211,   213,   198,   201,   202,   206,   210,   221,
   223,   215,   216,   229,   220,   226,   243,     0,   230,     0,
   231,   244,   256,   250,   251,   254,   255,     0,   257,   258,
   259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
   269,   270,   272,   271,   275,   273,   274,   276,     0,   281,
   277,   278,   279,   280,   291,   282,   283,   284,   285,   286,
   287,   288,   289,   290,   292,   293,   294,   295,   296,   297,
   301,   298,   299,   300,   304,   316,   302,   303,   305,   306,
   307,   308,   309,   311,   310,   313,   312,    58,    54
};

static const short yycheck[] = {   124,
    16,    17,    28,     5,     6,     7,    22,    30,    34,    35,
    36,    37,    31,    98,    37,   100,    33,   102,    37,    35,
    36,    23,     8,     9,    10,    11,    12,    13,    14,    15,
    30,    31,    30,     3,    34,    30,    34,    37,    30,    37,
    30,    31,    37,    27,    33,    37,    30,    37,     9,    10,
    11,    12,    13,    14,    15,    33,    16,    17,    18,    19,
    20,     4,     5,     6,     7,    27,     4,    34,    30,    27,
    37,    23,    30,    29,    31,    26,    32,    34,    33,   203,
   204,   205,     6,     7,   209,    33,    33,    26,    33,    33,
    24,    33,    33,    33,    57,    -1,    -1,    -1,    35,    35,
    35,    30,    35,    35,    35,    35,    33,    30,    30,    30,
    35,    37,    -1,    -1,    26,    35,    35,    35,    35,    35,
    35,    35,    35,    33,    33,    33,    37,    27,    30,    27,
    37,    37,    37,    37,    37,    34,    37,    30,    30,    30,
    30,    30,    30,    30,    -1,    31,    31,    31,    31,    31,
    -1,    31,    31,    -1,    -1,    -1,    37,    -1,    28,    37,
    37,    37,    37,    37,    37,    37,    37,    29,    32,    27,
    37,    27,    27,    27,    37,    27,    27,    34,    31,    -1,
    -1,    31,    31,    31,    31,    31,    31,    31,    -1,    -1,
    29,     0,    30,    30,    37,    37,    37,    37,    32,    30,
    30,    37,    37,    31,    37,    37,    31,    -1,    37,    -1,
    37,    37,    32,    37,    37,    37,    37,    -1,    37,    37,
    37,    37,    37,    37,    37,    37,    37,    32,    31,    37,
    37,    37,    31,    37,    32,    37,    37,    37,    -1,    32,
    37,    37,    37,    37,    31,    37,    37,    37,    37,    37,
    32,    37,    37,    37,    37,    32,    37,    37,    37,    32,
    32,    37,    37,    37,    31,     0,    37,    37,    32,    37,
    32,    37,    32,    32,    37,    29,    37,    34,    31
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison.simple"
/* This file comes from bison-1.28.  */

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

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

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

#ifndef YYSTACK_USE_ALLOCA
#ifdef alloca
#define YYSTACK_USE_ALLOCA
#else /* alloca not defined */
#ifdef __GNUC__
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi) || (defined (__sun) && defined (__i386))
#define YYSTACK_USE_ALLOCA
#include <alloca.h>
#else /* not sparc */
/* We think this test detects Watcom and Microsoft C.  */
/* This used to test MSDOS, but that is a bad idea
   since that symbol is in the user namespace.  */
#if (defined (_MSDOS) || defined (_MSDOS_)) && !defined (__TURBOC__)
#if 0 /* No need for malloc.h, which pollutes the namespace;
	 instead, just don't use alloca.  */
#include <malloc.h>
#endif
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
/* I don't know what this was needed for, but it pollutes the namespace.
   So I turned it off.   rms, 2 May 1997.  */
/* #include <malloc.h>  */
 #pragma alloca
#define YYSTACK_USE_ALLOCA
#else /* not MSDOS, or __TURBOC__, or _AIX */
#if 0
#ifdef __hpux /* haible@ilog.fr says this works for HPUX 9.05 and up,
		 and on HPUX 10.  Eventually we can turn this on.  */
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#endif /* __hpux */
#endif
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc */
#endif /* not GNU C */
#endif /* alloca not defined */
#endif /* YYSTACK_USE_ALLOCA not defined */

#ifdef YYSTACK_USE_ALLOCA
#define YYSTACK_ALLOC alloca
#else
#define YYSTACK_ALLOC malloc
#endif

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Define __yy_memcpy.  Note that the size argument
   should be passed with type unsigned int, because that is what the non-GCC
   definitions require.  With GCC, __builtin_memcpy takes an arg
   of type size_t, but it can handle unsigned int.  */

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     unsigned int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, unsigned int count)
{
  register char *t = to;
  register char *f = from;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 217 "/usr/share/bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
#ifdef YYPARSE_PARAM
int yyparse (void *);
#else
int yyparse (void);
#endif
#endif

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;
  int yyfree_stacks = 0;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  if (yyfree_stacks)
	    {
	      free (yyss);
	      free (yyvs);
#ifdef YYLSP_NEEDED
	      free (yyls);
#endif
	    }
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
#ifndef YYSTACK_USE_ALLOCA
      yyfree_stacks = 1;
#endif
      yyss = (short *) YYSTACK_ALLOC (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1,
		   size * (unsigned int) sizeof (*yyssp));
      yyvs = (YYSTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1,
		   size * (unsigned int) sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1,
		   size * (unsigned int) sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 4:
#line 729 "sdr.y"
{
					yyval.v[0]	=	yyvsp[0].real;
					yyval.v[1]	=	yyvsp[0].real;
					yyval.v[2]	=	yyvsp[0].real;
				;
    break;}
case 5:
#line 742 "sdr.y"
{
					yyval.v[0]	=	yyvsp[-3].real;
					yyval.v[1]	=	yyvsp[-2].real;
					yyval.v[2]	=	yyvsp[-1].real;
				;
    break;}
case 6:
#line 750 "sdr.y"
{
					yyval.v[0]	=	yyvsp[0].real;
					yyval.v[1]	=	yyvsp[0].real;
					yyval.v[2]	=	yyvsp[0].real;
				;
    break;}
case 7:
#line 762 "sdr.y"
{
					yyval.v[0]	=	yyvsp[-3].real;
					yyval.v[1]	=	yyvsp[-2].real;
					yyval.v[2]	=	yyvsp[-1].real;
				;
    break;}
case 8:
#line 768 "sdr.y"
{
					yyval.v[0]	=	0;
					yyval.v[1]	=	0;
					yyval.v[2]	=	0;
				;
    break;}
case 9:
#line 776 "sdr.y"
{
					yyval.v[0]	=	yyvsp[0].v[0];
					yyval.v[1]	=	yyvsp[0].v[1];
					yyval.v[2]	=	yyvsp[0].v[2];
				;
    break;}
case 10:
#line 786 "sdr.y"
{
					currentData.shaderType	=	SL_SURFACE;
				;
    break;}
case 11:
#line 792 "sdr.y"
{
					currentData.shaderType	=	SL_DISPLACEMENT;
				;
    break;}
case 12:
#line 798 "sdr.y"
{
					currentData.shaderType	=	SL_LIGHTSOURCE;
				;
    break;}
case 13:
#line 804 "sdr.y"
{
					currentData.shaderType	=	SL_ATMOSPHERE;
				;
    break;}
case 14:
#line 810 "sdr.y"
{
					currentData.shaderType	=	SL_IMAGER;
				;
    break;}
case 18:
#line 831 "sdr.y"
{
					currentData.currentParameterClass	=	CONTAINER_UNIFORM;
					currentData.currentParameterMutable	=	FALSE;
					currentData.uniform					=	TRUE;
				;
    break;}
case 19:
#line 838 "sdr.y"
{
					currentData.currentParameterClass	=	CONTAINER_VARYING;
					currentData.currentParameterMutable	=	FALSE;
					currentData.uniform					=	FALSE;
				;
    break;}
case 20:
#line 846 "sdr.y"
{
					currentData.currentParameterClass	=	CONTAINER_UNIFORM;
					currentData.currentParameterMutable	=	TRUE;
					currentData.uniform					=	TRUE;
				;
    break;}
case 21:
#line 854 "sdr.y"
{
					currentData.currentParameterClass	=	CONTAINER_VARYING;
					currentData.currentParameterMutable	=	TRUE;
					currentData.uniform					=	FALSE;
				;
    break;}
case 22:
#line 861 "sdr.y"
{
					currentData.currentParameterClass	=	CONTAINER_UNIFORM;
					currentData.currentParameterMutable	=	TRUE;
					currentData.uniform					=	TRUE;
				;
    break;}
case 23:
#line 867 "sdr.y"
{
					currentData.currentParameterClass	=	CONTAINER_UNIFORM;
					currentData.currentParameterMutable	=	FALSE;
					currentData.uniform					=	TRUE;
				;
    break;}
case 32:
#line 903 "sdr.y"
{
					TCode	*def	=	newVariable(yyvsp[-2].string,TYPE_FLOAT,1,TRUE);

					if (def != NULL) {
						def->real	=	yyvsp[0].real;
					}
				;
    break;}
case 33:
#line 913 "sdr.y"
{
					TCode	*def	=	newVariable(yyvsp[0].string,TYPE_FLOAT,1,TRUE);

					if (def != NULL) {
						def->real	=	0;
					}
				;
    break;}
case 34:
#line 927 "sdr.y"
{
					TCode	*def	=	newVariable(yyvsp[-4].string,TYPE_FLOAT,(int) yyvsp[-2].real,TRUE);
					
					if (def != NULL) {
						int	i;

						for (i=0;i<(int) yyvsp[-2].real;i++)
							def[i].real	=	0;
						
						currentData.currentArray = def;
					}
					
					currentData.numArrayItemsRemaining = (int) yyvsp[-2].real;
				;
    break;}
case 36:
#line 948 "sdr.y"
{
					TCode	*def	=	newVariable(yyvsp[-3].string,TYPE_FLOAT,(int) yyvsp[-1].real,TRUE);

					if (def != NULL) {
						int	i;

						for (i=0;i<(int) yyvsp[-1].real;i++)
							def[i].real	=	0;
					}
				;
    break;}
case 37:
#line 965 "sdr.y"
{
					if(currentData.numArrayItemsRemaining){
						slerror("Wrong number of items in array initializer\n");
					}
				;
    break;}
case 38:
#line 975 "sdr.y"
{
					if(currentData.numArrayItemsRemaining > 0){
						if(currentData.currentArray){
							currentData.currentArray->real = yyvsp[0].real;
							currentData.currentArray++;
						}
						currentData.numArrayItemsRemaining--;
					} else{
						slerror("Wrong number of items in array initializer\n");
					}
				;
    break;}
case 40:
#line 993 "sdr.y"
{
					TCode	*def	=	newVariable(yyvsp[0].string,TYPE_STRING,1,TRUE);

					switch(currentData.passNumber) {
					case 1:
						currentData.numStrings++;
						break;
					case 2:
						if (def != NULL) {
							def->string	=	currentData.strings[currentData.currentString++]	=	strdup("*");
						}
						break;
					default:
						break;
					}
				;
    break;}
case 41:
#line 1014 "sdr.y"
{
					TCode	*def	=	newVariable(yyvsp[-2].string,TYPE_STRING,1,TRUE);

					switch(currentData.passNumber) {
					case 1:
						currentData.numStrings++;
						break;
					case 2:
						if (def != NULL) {
							def->string	=	currentData.strings[currentData.currentString++]	=	strdup(yyvsp[0].string);
						}
						break;
					default:
						break;
					}
				;
    break;}
case 42:
#line 1037 "sdr.y"
{
					TCode	*def	=	newVariable(yyvsp[-4].string,TYPE_STRING,(int) yyvsp[-2].real,TRUE);
					
					switch(currentData.passNumber) {
					case 1:
						currentData.numStrings += (int) yyvsp[-2].real;
						break;
					case 2:
						if (def != NULL) {
							int	i;

							for (i=0;i<(int) yyvsp[-2].real;i++)
								def[i].string	=	NULL;
							
							currentData.currentArray = def;
						}
						break;
					default:
						break;
					}
					
					currentData.numArrayItemsRemaining = (int) yyvsp[-2].real;
				;
    break;}
case 44:
#line 1067 "sdr.y"
{
					TCode	*def	=	newVariable(yyvsp[-3].string,TYPE_STRING,(int) yyvsp[-1].real,TRUE);

					if (def != NULL) {
						int	i;

						for (i=0;i<(int) yyvsp[-1].real;i++)
							def[i].string	=	NULL;
					}
				;
    break;}
case 45:
#line 1082 "sdr.y"
{
					if(currentData.numArrayItemsRemaining){
						slerror("Wrong number of items in array initializer\n");
					}
				;
    break;}
case 46:
#line 1092 "sdr.y"
{
					if(currentData.numArrayItemsRemaining > 0){
						if(currentData.currentArray){
							currentData.currentArray->string	=	currentData.strings[currentData.currentString++]	=	strdup(yyvsp[0].string);
							currentData.currentArray++;
						}
						currentData.numArrayItemsRemaining--;
					}
					else{
						slerror("Wrong number of items in array initializer\n");
					}
				;
    break;}
case 48:
#line 1111 "sdr.y"
{
					currentData.currentParameterType	=	TYPE_COLOR;
				;
    break;}
case 49:
#line 1115 "sdr.y"
{
					TCode	*def	=	newVariable(yyvsp[-2].string,currentData.currentParameterType,1,TRUE);
					float	*v;

					if (def != NULL) {
						v	=	yyvsp[0].v;

						def[0].real	=	v[0];
						def[1].real	=	v[1];
						def[2].real	=	v[2];
					}
				;
    break;}
case 50:
#line 1134 "sdr.y"
{
					TCode	*def	=	newVariable(yyvsp[-4].string,TYPE_COLOR,(int) yyvsp[-2].real,TRUE);
					
					if(def != NULL)
						currentData.currentArray = def;
					currentData.numArrayItemsRemaining = (int) yyvsp[-2].real;
				;
    break;}
case 52:
#line 1148 "sdr.y"
{
					TCode	*def	=	newVariable(yyvsp[-3].string,TYPE_COLOR,(int) yyvsp[-1].real,TRUE);
				;
    break;}
case 53:
#line 1156 "sdr.y"
{
					currentData.currentParameterType	=	TYPE_VECTOR;
				;
    break;}
case 54:
#line 1160 "sdr.y"
{
					TCode	*def	=	newVariable(yyvsp[-2].string,currentData.currentParameterType,1,TRUE);
					float	*v;

					if (def != NULL) {
						v	=	yyvsp[0].v;

						def[0].real	=	v[0];
						def[1].real	=	v[1];
						def[2].real	=	v[2];
					}
				;
    break;}
case 55:
#line 1179 "sdr.y"
{
					TCode	*def	=	newVariable(yyvsp[-4].string,TYPE_VECTOR,(int) yyvsp[-2].real,TRUE);
					
					if(def != NULL) {
						currentData.currentArray = def;
					}
					
					currentData.numArrayItemsRemaining = (int) yyvsp[-2].real;
				;
    break;}
case 57:
#line 1195 "sdr.y"
{
					TCode	*def	=	newVariable(yyvsp[-3].string,TYPE_VECTOR,(int) yyvsp[-1].real,TRUE);
				;
    break;}
case 58:
#line 1203 "sdr.y"
{
					currentData.currentParameterType	=	TYPE_NORMAL;
				;
    break;}
case 59:
#line 1207 "sdr.y"
{
					TCode	*def	=	newVariable(yyvsp[-2].string,currentData.currentParameterType,1,TRUE);
					float	*v;

					if (def != NULL) {
						v	=	yyvsp[0].v;

						def[0].real	=	v[0];
						def[1].real	=	v[1];
						def[2].real	=	v[2];
					}
				;
    break;}
case 60:
#line 1226 "sdr.y"
{
					TCode	*def	=	newVariable(yyvsp[-4].string,TYPE_NORMAL,(int) yyvsp[-2].real,TRUE);
					
					if(def != NULL) {
						currentData.currentArray = def;
					}
					
					currentData.numArrayItemsRemaining = (int) yyvsp[-2].real;
				;
    break;}
case 62:
#line 1242 "sdr.y"
{
					TCode	*def	=	newVariable(yyvsp[-3].string,TYPE_NORMAL,(int) yyvsp[-1].real,TRUE);
				;
    break;}
case 63:
#line 1250 "sdr.y"
{
					currentData.currentParameterType	=	TYPE_POINT;
				;
    break;}
case 64:
#line 1254 "sdr.y"
{
					TCode	*def	=	newVariable(yyvsp[-2].string,currentData.currentParameterType,1,TRUE);
					float	*v;

					if (def != NULL) {
						v	=	yyvsp[0].v;

						def[0].real	=	v[0];
						def[1].real	=	v[1];
						def[2].real	=	v[2];
					}
				;
    break;}
case 65:
#line 1273 "sdr.y"
{
					TCode	*def	=	newVariable(yyvsp[-4].string,TYPE_POINT,(int) yyvsp[-2].real,TRUE);
					
					if(def != NULL) {
						currentData.currentArray = def;
					}
					
					currentData.numArrayItemsRemaining = (int) yyvsp[-2].real;
				;
    break;}
case 67:
#line 1289 "sdr.y"
{
					TCode	*def	=	newVariable(yyvsp[-3].string,TYPE_POINT,(int) yyvsp[-1].real,TRUE);
				;
    break;}
case 68:
#line 1296 "sdr.y"
{
					yyval.v[0]	=	yyvsp[0].real;
					yyval.v[1]	=	yyvsp[0].real;
					yyval.v[2]	=	yyvsp[0].real;
				;
    break;}
case 69:
#line 1308 "sdr.y"
{
					yyval.v[0]	=	yyvsp[-3].real;
					yyval.v[1]	=	yyvsp[-2].real;
					yyval.v[2]	=	yyvsp[-1].real;
				;
    break;}
case 70:
#line 1315 "sdr.y"
{
					yyval.v[0]	=	yyvsp[0].real;
					yyval.v[1]	=	yyvsp[0].real;
					yyval.v[2]	=	yyvsp[0].real;
				;
    break;}
case 71:
#line 1326 "sdr.y"
{
					yyval.v[0]	=	yyvsp[-3].real;
					yyval.v[1]	=	yyvsp[-2].real;
					yyval.v[2]	=	yyvsp[-1].real;
				;
    break;}
case 72:
#line 1338 "sdr.y"
{
					if(currentData.numArrayItemsRemaining){
						slerror("Wrong number of items in array initializer\n");
					}
				;
    break;}
case 73:
#line 1348 "sdr.y"
{
					float *v;
					
					if(currentData.numArrayItemsRemaining > 0){
						if(currentData.currentArray){
							v = yyvsp[0].v;
							currentData.currentArray[0].real = v[0];
							currentData.currentArray[1].real = v[1];
							currentData.currentArray[2].real = v[2];
							currentData.currentArray += 3;
						}
						currentData.numArrayItemsRemaining--;
					} else{
						slerror("Wrong number of items in array initializer\n");
					}
				;
    break;}
case 75:
#line 1390 "sdr.y"
{
					TCode	*def	=	newVariable(yyvsp[-19].string,TYPE_MATRIX,1,TRUE);

					if (def != NULL) {
						def[0].real		=	yyvsp[-16].real;
						def[1].real		=	yyvsp[-15].real;
						def[2].real		=	yyvsp[-14].real;
						def[3].real		=	yyvsp[-13].real;
						def[4].real		=	yyvsp[-12].real;
						def[5].real		=	yyvsp[-11].real;
						def[6].real		=	yyvsp[-10].real;
						def[7].real		=	yyvsp[-9].real;
						def[8].real		=	yyvsp[-8].real;
						def[9].real		=	yyvsp[-7].real;
						def[10].real	=	yyvsp[-6].real;
						def[11].real	=	yyvsp[-5].real;
						def[12].real	=	yyvsp[-4].real;
						def[13].real	=	yyvsp[-3].real;
						def[14].real	=	yyvsp[-2].real;
						def[15].real	=	yyvsp[-1].real;
					}
				;
    break;}
case 76:
#line 1417 "sdr.y"
{
					TCode	*def	=	newVariable(yyvsp[-2].string,TYPE_MATRIX,1,TRUE);

					if (def != NULL) {
						def[0].real		=	yyvsp[0].real;
						def[1].real		=	0;
						def[2].real		=	0;
						def[3].real		=	0;
						def[4].real		=	0;
						def[5].real		=	yyvsp[0].real;
						def[6].real		=	0;
						def[7].real		=	0;
						def[8].real		=	0;
						def[9].real		=	0;
						def[10].real	=	yyvsp[0].real;
						def[11].real	=	0;
						def[12].real	=	0;
						def[13].real	=	0;
						def[14].real	=	0;
						def[15].real	=	1;
					}
				;
    break;}
case 77:
#line 1442 "sdr.y"
{
					TCode	*def	=	newVariable(yyvsp[0].string,TYPE_MATRIX,1,TRUE);

					if (def != NULL) {
						def[0].real		=	1;
						def[1].real		=	0;
						def[2].real		=	0;
						def[3].real		=	0;
						def[4].real		=	0;
						def[5].real		=	1;
						def[6].real		=	0;
						def[7].real		=	0;
						def[8].real		=	0;
						def[9].real		=	0;
						def[10].real	=	1;
						def[11].real	=	0;
						def[12].real	=	0;
						def[13].real	=	0;
						def[14].real	=	0;
						def[15].real	=	1;
					}
				;
    break;}
case 78:
#line 1471 "sdr.y"
{
					TCode	*def	=	newVariable(yyvsp[-4].string,TYPE_MATRIX,(int) yyvsp[-2].real,TRUE);
					
					if (def != NULL) {
						int	i;

						for (i=0;i<((int) yyvsp[-2].real)*16;i++)
							def[i].real	=	0;
						currentData.currentArray = def;
					}
					
					currentData.numArrayItemsRemaining = (int) yyvsp[-2].real;
				;
    break;}
case 80:
#line 1491 "sdr.y"
{
					TCode	*def	=	newVariable(yyvsp[-3].string,TYPE_MATRIX,(int) yyvsp[-1].real,TRUE);

					if (def != NULL) {
						int	i;

						for (i=0;i<((int) yyvsp[-1].real)*16;i++)
							def[i].real	=	0;
					}
				;
    break;}
case 81:
#line 1508 "sdr.y"
{
					if(currentData.numArrayItemsRemaining){
						slerror("wrong number of items in array initializer\n");
					}
				;
    break;}
case 82:
#line 1535 "sdr.y"
{
					if(currentData.numArrayItemsRemaining > 0){
						if(currentData.currentArray){
							currentData.currentArray[0].real = yyvsp[-16].real;
							currentData.currentArray[1].real = yyvsp[-15].real;
							currentData.currentArray[2].real = yyvsp[-14].real;
							currentData.currentArray[3].real = yyvsp[-13].real;
							currentData.currentArray[4].real = yyvsp[-12].real;
							currentData.currentArray[5].real = yyvsp[-11].real;
							currentData.currentArray[6].real = yyvsp[-10].real;
							currentData.currentArray[7].real = yyvsp[-9].real;
							currentData.currentArray[8].real = yyvsp[-8].real;
							currentData.currentArray[9].real = yyvsp[-7].real;
							currentData.currentArray[10].real = yyvsp[-6].real;
							currentData.currentArray[11].real = yyvsp[-5].real;
							currentData.currentArray[12].real = yyvsp[-4].real;
							currentData.currentArray[13].real = yyvsp[-3].real;
							currentData.currentArray[14].real = yyvsp[-2].real;
							currentData.currentArray[15].real = yyvsp[-1].real;
							
							currentData.currentArray += 16;
						}
						currentData.numArrayItemsRemaining--;
					}
					else{
						slerror("wrong number of items in array initializer\n");
					}
				;
    break;}
case 83:
#line 1566 "sdr.y"
{
					if(currentData.numArrayItemsRemaining > 0){
						if(currentData.currentArray){
							currentData.currentArray[0].real = yyvsp[0].real;
							currentData.currentArray[1].real = 0;
							currentData.currentArray[2].real = 0;
							currentData.currentArray[3].real = 0;
							currentData.currentArray[4].real = 0;
							currentData.currentArray[5].real = yyvsp[0].real;
							currentData.currentArray[6].real = 0;
							currentData.currentArray[7].real = 0;
							currentData.currentArray[8].real = 0;
							currentData.currentArray[9].real = 0;
							currentData.currentArray[10].real = yyvsp[0].real;
							currentData.currentArray[11].real = 0;
							currentData.currentArray[12].real = 0;
							currentData.currentArray[13].real = 0;
							currentData.currentArray[14].real = 0;
							currentData.currentArray[15].real = 1;
							
							currentData.currentArray += 16;
						}
						currentData.numArrayItemsRemaining--;
					}
					else{
						slerror("wrong number of items in array initializer\n");
					}
				;
    break;}
case 96:
#line 1641 "sdr.y"
{
					newVariable(yyvsp[0].string,TYPE_BOOLEAN,1,FALSE);
				;
    break;}
case 97:
#line 1650 "sdr.y"
{
					newVariable(yyvsp[-3].string,TYPE_BOOLEAN,(int) yyvsp[-1].real,FALSE);
				;
    break;}
case 98:
#line 1659 "sdr.y"
{
					newVariable(yyvsp[0].string,TYPE_FLOAT,1,FALSE);
				;
    break;}
case 99:
#line 1668 "sdr.y"
{
					newVariable(yyvsp[-3].string,TYPE_FLOAT,(int) yyvsp[-1].real,FALSE);
				;
    break;}
case 100:
#line 1676 "sdr.y"
{
					newVariable(yyvsp[0].string,TYPE_STRING,1,FALSE);
				;
    break;}
case 101:
#line 1685 "sdr.y"
{
					newVariable(yyvsp[-3].string,TYPE_STRING,(int) yyvsp[-1].real,FALSE);
				;
    break;}
case 102:
#line 1693 "sdr.y"
{
					newVariable(yyvsp[0].string,TYPE_VECTOR,1,FALSE);
				;
    break;}
case 103:
#line 1702 "sdr.y"
{
					newVariable(yyvsp[-3].string,TYPE_VECTOR,(int) yyvsp[-1].real,FALSE);
				;
    break;}
case 104:
#line 1710 "sdr.y"
{
					newVariable(yyvsp[0].string,TYPE_COLOR,1,FALSE);
				;
    break;}
case 105:
#line 1719 "sdr.y"
{
					newVariable(yyvsp[-3].string,TYPE_COLOR,(int) yyvsp[-1].real,FALSE);
				;
    break;}
case 106:
#line 1727 "sdr.y"
{
					newVariable(yyvsp[0].string,TYPE_NORMAL,1,FALSE);
				;
    break;}
case 107:
#line 1736 "sdr.y"
{
					newVariable(yyvsp[-3].string,TYPE_NORMAL,(int) yyvsp[-1].real,FALSE);
				;
    break;}
case 108:
#line 1744 "sdr.y"
{
					newVariable(yyvsp[0].string,TYPE_POINT,1,FALSE);
				;
    break;}
case 109:
#line 1753 "sdr.y"
{
					newVariable(yyvsp[-3].string,TYPE_POINT,(int) yyvsp[-1].real,FALSE);
				;
    break;}
case 110:
#line 1761 "sdr.y"
{
					newVariable(yyvsp[0].string,TYPE_MATRIX,1,FALSE);
				;
    break;}
case 111:
#line 1770 "sdr.y"
{
					newVariable(yyvsp[-3].string,TYPE_MATRIX,(int) yyvsp[-1].real,FALSE);
				;
    break;}
case 112:
#line 1777 "sdr.y"
{
					currentData.parsingInit	=	TRUE;
					newLabel(initLabel,FALSE);
				;
    break;}
case 114:
#line 1786 "sdr.y"
{
					currentData.parsingInit	=	FALSE;
					newLabel(codeLabel,FALSE);
				;
    break;}
case 120:
#line 1811 "sdr.y"
{
					switch(currentData.passNumber) {
					case 1:
						currentData.numCode					+=	4;		// opcode
						break;
					case 2:
						strcpy(currentData.currentOpcode,yyvsp[0].string);
						currentData.currentArgument			=	0;
						currentData.currentOpcodePlace		=	&currentData.code[currentData.currentCode];
						currentData.currentCode				+=	4;
						currentData.currentPrototype[0]		=	'~';
						currentData.opcodeUniform			=	TRUE;
						break;
					default:
						break;
					}
				;
    break;}
case 121:
#line 1832 "sdr.y"
{
					switch(currentData.passNumber) {
					case 1:
						break;
					case 2:
						// Set the opcode here
						void			*handle;
						dsoExecFunction	exec;

						if (currentRenderer->getDSO(yyvsp[-5].string,yyvsp[-2].string,handle,exec) == TRUE) {
							if (yyvsp[-2].string[0] == 'o')
								currentData.currentOpcodePlace[0].integer	=	FUNCTION_DSO_VOID;
							else
								currentData.currentOpcodePlace[0].integer	=	FUNCTION_DSO;

							assert((currentData.currentArgument+4) < 256);
							assert(currentData.opcodeUniform < 256);
							
							currentData.currentOpcodePlace[1].arguments.numCodes			=	(unsigned char) (currentData.currentArgument+4);
							currentData.currentOpcodePlace[1].arguments.numArguments		=	(unsigned char) (currentData.currentArgument);
							currentData.currentOpcodePlace[1].arguments.uniform				=	(unsigned char) (currentData.opcodeUniform);
							currentData.currentOpcodePlace[2].integer						=	(int) handle;
							currentData.currentOpcodePlace[3].integer						=	(int) exec;
						} else {
							slerror("Unable to locate DSO function\n");
						}
						break;
					default:
						break;
					}
				;
    break;}
case 122:
#line 1867 "sdr.y"
{
					switch(currentData.passNumber) {
					case 1:
						currentData.numCode					+=	2;		// opcode
						break;
					case 2:
						strcpy(currentData.currentOpcode,yyvsp[0].string);
						currentData.currentArgument			=	0;
						currentData.currentOpcodePlace		=	&currentData.code[currentData.currentCode];
						currentData.currentCode				+=	2;
						currentData.currentPrototype[0]		=	'~';
						currentData.opcodeUniform			=	TRUE;
						break;
					default:
						break;
					}
				;
    break;}
case 123:
#line 1886 "sdr.y"
{
					switch(currentData.passNumber) {
					case 1:
						currentData.numCode					+=	2;		// opcode
						break;
					case 2:
						strcpy(currentData.currentOpcode,"surface");
						currentData.currentArgument			=	0;
						currentData.currentOpcodePlace		=	&currentData.code[currentData.currentCode];
						currentData.currentCode				+=	2;
						currentData.currentPrototype[0]		=	'~';
						currentData.opcodeUniform			=	TRUE;
						break;
					default:
						break;
					}
				;
    break;}
case 124:
#line 1905 "sdr.y"
{
					switch(currentData.passNumber) {
					case 1:
						currentData.numCode					+=	2;		// opcode
						break;
					case 2:
						strcpy(currentData.currentOpcode,"displacement");
						currentData.currentArgument			=	0;
						currentData.currentOpcodePlace		=	&currentData.code[currentData.currentCode];
						currentData.currentCode				+=	2;
						currentData.currentPrototype[0]		=	'~';
						currentData.opcodeUniform			=	TRUE;
						break;
					default:
						break;
					}
				;
    break;}
case 125:
#line 1927 "sdr.y"
{
				;
    break;}
case 126:
#line 1930 "sdr.y"
{
				;
    break;}
case 127:
#line 1937 "sdr.y"
{
					setOpcode();
				;
    break;}
case 128:
#line 1945 "sdr.y"
{
					newLabel(yyvsp[-1].string,FALSE);
				;
    break;}
case 129:
#line 1952 "sdr.y"
{
					char	*str	=	yyvsp[0].string;

					addStringReference(&str,1);
				;
    break;}
case 130:
#line 1959 "sdr.y"
{
					newLabel(yyvsp[0].string,TRUE);
				;
    break;}
case 131:
#line 1964 "sdr.y"
{
					addVariableReference(yyvsp[0].string);
				;
    break;}
case 132:
#line 1969 "sdr.y"
{
					addFloatReference(&yyvsp[0].real,1);
				;
    break;}
case 133:
#line 1980 "sdr.y"
{
					vector	tmp;

					tmp[0]	=	yyvsp[-5].real;
					tmp[1]	=	yyvsp[-3].real;
					tmp[2]	=	yyvsp[-1].real;

					addFloatReference(tmp,3);
				;
    break;}
case 134:
#line 2023 "sdr.y"
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
				;
    break;}
case 135:
#line 2049 "sdr.y"
{
					strcpy(currentData.currentPrototype,yyvsp[-1].string);
				;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 543 "/usr/share/bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;

 yyacceptlab:
  /* YYACCEPT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 0;

 yyabortlab:
  /* YYABORT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 1;
}
#line 2054 "sdr.y"

#include "lex.sl.cpp"

int	slLineno	=	0;

///////////////////////////////////////////////////////////////////////
// Function				:	slerror
// Description			:	Parser error function
// Return Value			:
// Comments				:
// Date last edited		:	8/8/2001
void	slerror(char *s) {
	warning(CODE_BADFILE,"Error in shader \"%s\" (%d) (\"%s\") (v%d.%d.%d)\n",currentData.name,slLineno,s,VERSION_RELEASE,VERSION_BETA,VERSION_ALPHA);
	currentData.numErrors++;
}


///////////////////////////////////////////////////////////////////////
// Function				:	parseShader
// Description			:	Parse a shader
// Return Value			:	Parsed shader if successful
// Comments				:
// Date last edited		:	8/8/2001
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
		fclose(fin);
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
// Date last edited		:	8/8/2001
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


	currentData.name					=	NULL;
	currentData.passNumber				=	0;
	currentData.parsingInit				=	FALSE;
	currentData.numErrors				=	0;

				// Pass 1
	currentData.numCode					=	0;
	currentData.numConstants			=	0;
	currentData.numVariables			=	0;
	currentData.numStrings				=	0;
	currentData.constantSize			=	0;
	currentData.varyingSize				=	0;
	currentData.shaderType				=	SL_SURFACE;
	currentData.uniform					=	FALSE;
	currentData.opcodeUniform			=	FALSE;

				// Pass 2
	currentData.currentCode				=	0;
	currentData.currentConstant			=	0;
	currentData.currentVariable			=	0;
	currentData.currentString			=	0;
	currentData.currentPL				=	0;
	currentData.currentConstantSize		=	0;
	currentData.currentVaryingSize		=	0;
	strcpy(currentData.currentOpcode,"");
	strcpy(currentData.currentPrototype,"");
	currentData.currentArgument			=	0;
	currentData.usedParameters			=	0;
	currentData.currentOpcodePlace		=	NULL;
	currentData.codeEntryPoint			=	-1;
	currentData.initEntryPoint			=	-1;
				
	currentData.memory					=	NULL;
	currentData.code					=	NULL;
	currentData.constants				=	NULL;
	currentData.varyingSizes			=	NULL;
	currentData.strings					=	NULL;
	currentData.constantEntries			=	NULL;
	currentData.definedVariables		=	NULL;
	currentData.labelReferences			=	NULL;
	currentData.labelDefinitions		=	NULL;
}

///////////////////////////////////////////////////////////////////////
// Function				:	alloc
// Description			:	Allocate required space for the shader
// Return Value			:
// Comments				:
// Date last edited		:	8/8/2001
void	alloc() {
	TCode	*mem;

	currentData.memory	=	new TCode[	currentData.numCode	+
										currentData.constantSize +
										currentData.numConstants + 
										currentData.numVariables + 
										currentData.numStrings];

	mem		=	currentData.memory;

	if (currentData.numCode != 0) {
		currentData.code						=	mem;
		mem										+=	currentData.numCode;
	}

	if (currentData.constantSize != 0) {
		currentData.constants					=	mem;
		mem										+=	currentData.constantSize;
	}

	if (currentData.numConstants != 0) {
		currentData.constantEntries				=	(TCode **) mem;
		mem										+=	currentData.numConstants;
	}

	if (currentData.numVariables != 0) {
		currentData.varyingSizes				=	(int *) mem;
		mem										+=	currentData.numVariables;
	}

	if (currentData.numStrings != 0) {
		int	i;

		currentData.strings						=	(char **) mem;
		mem										+=	currentData.numStrings;

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
// Date last edited		:	8/8/2001
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
					currentData.code[cLabel->index].integer	=	nLabel->index;
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
	cShader->constantsArea				=	currentData.constants;

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
// Date last edited		:
void	processEscapes(char *str) {
	int		i,n,j;

	n	=	strlen(str);
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


