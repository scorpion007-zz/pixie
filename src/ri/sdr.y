%{
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
%}
%union slval {
	float	real;
	char	string[64];
	matrix	m;
	vector	v;
}

// Some tokens
%token	 SCRL_PARAMETERS
%token	 SCRL_VARIABLES
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

%token	 SCRL_INIT
%token	 SCRL_CODE

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
%type<v>		slVectorIn
%type<v>		slVector
%type<v>		slVectorValue
%%
start:		
				slType	
				slParameterDefinitions
				slVariableDefinitions
				slInit
				slCode
				slEmptySpace
				;

slEmptySpace: 
				|
				SCRL_NL
				slEmptySpace
				;

slVectorIn:		SCRL_EQUAL
				SCRL_TEXT_VALUE
				SCRL_FLOAT_VALUE
				{
					$$[0]	=	$3;
					$$[1]	=	$3;
					$$[2]	=	$3;
				}
				|
				SCRL_EQUAL
				SCRL_TEXT_VALUE
				SCRL_OPEN_SQR_PARANTHESIS
				SCRL_FLOAT_VALUE
				SCRL_FLOAT_VALUE
				SCRL_FLOAT_VALUE
				SCRL_CLOSE_SQR_PARANTHESIS
				{
					$$[0]	=	$4;
					$$[1]	=	$5;
					$$[2]	=	$6;
				}
				|
				SCRL_EQUAL
				SCRL_FLOAT_VALUE
				{
					$$[0]	=	$2;
					$$[1]	=	$2;
					$$[2]	=	$2;
				}
				|
				SCRL_EQUAL
				SCRL_OPEN_SQR_PARANTHESIS
				SCRL_FLOAT_VALUE
				SCRL_FLOAT_VALUE
				SCRL_FLOAT_VALUE
				SCRL_CLOSE_SQR_PARANTHESIS
				{
					$$[0]	=	$3;
					$$[1]	=	$4;
					$$[2]	=	$5;
				}
				|
				{
					$$[0]	=	0;
					$$[1]	=	0;
					$$[2]	=	0;
				}
				;

slVector:		slVectorIn
				{
					$$[0]	=	$1[0];
					$$[1]	=	$1[1];
					$$[2]	=	$1[2];
				}
				;
			
slType:
				SCRL_SURFACE
				SCRL_NL
				{
					currentData.shaderType	=	SL_SURFACE;
				}
				|
				SCRL_DISPLACEMENT
				SCRL_NL
				{
					currentData.shaderType	=	SL_DISPLACEMENT;
				}
				|
				SCRL_LIGHTSOURCE
				SCRL_NL
				{
					currentData.shaderType	=	SL_LIGHTSOURCE;
				}
				|
				SCRL_VOLUME
				SCRL_NL
				{
					currentData.shaderType	=	SL_ATMOSPHERE;
				}
				|
				SCRL_IMAGER
				SCRL_NL
				{
					currentData.shaderType	=	SL_IMAGER;
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
				|
				;

slContainer:
				SCRL_UNIFORM
				{
					currentData.currentParameterClass	=	CONTAINER_UNIFORM;
					currentData.currentParameterMutable	=	FALSE;
					currentData.uniform					=	TRUE;
				}
				|
				SCRL_VARYING
				{
					currentData.currentParameterClass	=	CONTAINER_VARYING;
					currentData.currentParameterMutable	=	FALSE;
					currentData.uniform					=	FALSE;
				}
				|
				SCRL_OUTPUT
				SCRL_UNIFORM
				{
					currentData.currentParameterClass	=	CONTAINER_UNIFORM;
					currentData.currentParameterMutable	=	TRUE;
					currentData.uniform					=	TRUE;
				}
				|
				SCRL_OUTPUT
				SCRL_VARYING
				{
					currentData.currentParameterClass	=	CONTAINER_VARYING;
					currentData.currentParameterMutable	=	TRUE;
					currentData.uniform					=	FALSE;
				}
				|
				SCRL_OUTPUT
				{
					currentData.currentParameterClass	=	CONTAINER_UNIFORM;
					currentData.currentParameterMutable	=	TRUE;
					currentData.uniform					=	TRUE;
				}
				|
				{
					currentData.currentParameterClass	=	CONTAINER_UNIFORM;
					currentData.currentParameterMutable	=	FALSE;
					currentData.uniform					=	TRUE;
				}
				;


slParameter:
				slContainer
				slAParameter
				;


slAParameter:
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


slFloatParameter:
				SCRL_FLOAT
				SCRL_IDENTIFIER_VALUE
				SCRL_EQUAL
				SCRL_FLOAT_VALUE
				{
					TCode	*def	=	newVariable($2,TYPE_FLOAT,1,TRUE);

					if (def != NULL) {
						def->real	=	$4;
					}
				}
				|
				SCRL_FLOAT
				SCRL_IDENTIFIER_VALUE
				{
					TCode	*def	=	newVariable($2,TYPE_FLOAT,1,TRUE);

					if (def != NULL) {
						def->real	=	0;
					}
				}
				|
				SCRL_FLOAT
				SCRL_IDENTIFIER_VALUE
				SCRL_OPEN_SQR_PARANTHESIS
				SCRL_FLOAT_VALUE
				SCRL_CLOSE_SQR_PARANTHESIS
				SCRL_EQUAL
				{
					TCode	*def	=	newVariable($2,TYPE_FLOAT,(int) $4,TRUE);
					
					if (def != NULL) {
						int	i;

						for (i=0;i<(int) $4;i++)
							def[i].real	=	0;
						
						currentData.currentArray = def;
					}
					
					currentData.numArrayItemsRemaining = (int) $4;
				}
				slFloatArrayInitializer
				|
				SCRL_FLOAT
				SCRL_IDENTIFIER_VALUE
				SCRL_OPEN_SQR_PARANTHESIS
				SCRL_FLOAT_VALUE
				SCRL_CLOSE_SQR_PARANTHESIS
				{
					TCode	*def	=	newVariable($2,TYPE_FLOAT,(int) $4,TRUE);

					if (def != NULL) {
						int	i;

						for (i=0;i<(int) $4;i++)
							def[i].real	=	0;
					}
				}
				;


slFloatArrayInitializer:
				SCRL_OPEN_SQR_PARANTHESIS
				slFloatArrayInitializerItems
				SCRL_CLOSE_SQR_PARANTHESIS
				{
					if(currentData.numArrayItemsRemaining){
						slerror("Wrong number of items in array initializer\n");
					}
				}
				;
				
slFloatArrayInitializerItems:
				slFloatArrayInitializerItems
				SCRL_FLOAT_VALUE
				{
					if(currentData.numArrayItemsRemaining > 0){
						if(currentData.currentArray){
							currentData.currentArray->real = $2;
							currentData.currentArray++;
						}
						currentData.numArrayItemsRemaining--;
					} else{
						slerror("Wrong number of items in array initializer\n");
					}
				}	
				|
				;


slStringParameter:
				SCRL_STRING
				SCRL_IDENTIFIER_VALUE
				{
					TCode	*def	=	newVariable($2,TYPE_STRING,1,TRUE);

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
				}
				|
				SCRL_STRING
				SCRL_IDENTIFIER_VALUE
				SCRL_EQUAL
				SCRL_TEXT_VALUE
				{
					TCode	*def	=	newVariable($2,TYPE_STRING,1,TRUE);

					switch(currentData.passNumber) {
					case 1:
						currentData.numStrings++;
						break;
					case 2:
						if (def != NULL) {
							def->string	=	currentData.strings[currentData.currentString++]	=	strdup($4);
						}
						break;
					default:
						break;
					}
				}
				|
				SCRL_STRING
				SCRL_IDENTIFIER_VALUE
				SCRL_OPEN_SQR_PARANTHESIS
				SCRL_FLOAT_VALUE
				SCRL_CLOSE_SQR_PARANTHESIS
				SCRL_EQUAL
				{
					TCode	*def	=	newVariable($2,TYPE_STRING,(int) $4,TRUE);
					
					switch(currentData.passNumber) {
					case 1:
						currentData.numStrings += (int) $4;
						break;
					case 2:
						if (def != NULL) {
							int	i;

							for (i=0;i<(int) $4;i++)
								def[i].string	=	NULL;
							
							currentData.currentArray = def;
						}
						break;
					default:
						break;
					}
					
					currentData.numArrayItemsRemaining = (int) $4;
				}
				slStringArrayInitializer
				|
				SCRL_STRING
				SCRL_IDENTIFIER_VALUE
				SCRL_OPEN_SQR_PARANTHESIS
				SCRL_FLOAT_VALUE
				SCRL_CLOSE_SQR_PARANTHESIS
				{
					TCode	*def	=	newVariable($2,TYPE_STRING,(int) $4,TRUE);

					if (def != NULL) {
						int	i;

						for (i=0;i<(int) $4;i++)
							def[i].string	=	NULL;
					}
				}

slStringArrayInitializer:
				SCRL_OPEN_SQR_PARANTHESIS
				slStringArrayInitializerItems
				SCRL_CLOSE_SQR_PARANTHESIS
				{
					if(currentData.numArrayItemsRemaining){
						slerror("Wrong number of items in array initializer\n");
					}
				}
				;
		
slStringArrayInitializerItems:
				slStringArrayInitializerItems
				SCRL_TEXT_VALUE
				{
					if(currentData.numArrayItemsRemaining > 0){
						if(currentData.currentArray){
							currentData.currentArray->string	=	currentData.strings[currentData.currentString++]	=	strdup($2);
							currentData.currentArray++;
						}
						currentData.numArrayItemsRemaining--;
					}
					else{
						slerror("Wrong number of items in array initializer\n");
					}
				}	
				|
				;


slColorParameter:
				SCRL_COLOR
				SCRL_IDENTIFIER_VALUE
				{
					currentData.currentParameterType	=	TYPE_COLOR;
				}
				slVector
				{
					TCode	*def	=	newVariable($2,currentData.currentParameterType,1,TRUE);
					float	*v;

					if (def != NULL) {
						v	=	$4;

						def[0].real	=	v[0];
						def[1].real	=	v[1];
						def[2].real	=	v[2];
					}
				}
				|
				SCRL_COLOR
				SCRL_IDENTIFIER_VALUE
				SCRL_OPEN_SQR_PARANTHESIS
				SCRL_FLOAT_VALUE
				SCRL_CLOSE_SQR_PARANTHESIS
				SCRL_EQUAL
				{
					TCode	*def	=	newVariable($2,TYPE_COLOR,(int) $4,TRUE);
					
					if(def != NULL)
						currentData.currentArray = def;
					currentData.numArrayItemsRemaining = (int) $4;
				}
				slVectorArrayInitializer
				|
				SCRL_COLOR
				SCRL_IDENTIFIER_VALUE
				SCRL_OPEN_SQR_PARANTHESIS
				SCRL_FLOAT_VALUE
				SCRL_CLOSE_SQR_PARANTHESIS
				{
					TCode	*def	=	newVariable($2,TYPE_COLOR,(int) $4,TRUE);
				}
				;

slVectorParameter:
				SCRL_VECTOR
				SCRL_IDENTIFIER_VALUE
				{
					currentData.currentParameterType	=	TYPE_VECTOR;
				}
				slVector
				{
					TCode	*def	=	newVariable($2,currentData.currentParameterType,1,TRUE);
					float	*v;

					if (def != NULL) {
						v	=	$4;

						def[0].real	=	v[0];
						def[1].real	=	v[1];
						def[2].real	=	v[2];
					}
				}
				|
				SCRL_VECTOR
				SCRL_IDENTIFIER_VALUE
				SCRL_OPEN_SQR_PARANTHESIS
				SCRL_FLOAT_VALUE
				SCRL_CLOSE_SQR_PARANTHESIS
				SCRL_EQUAL
				{
					TCode	*def	=	newVariable($2,TYPE_VECTOR,(int) $4,TRUE);
					
					if(def != NULL) {
						currentData.currentArray = def;
					}
					
					currentData.numArrayItemsRemaining = (int) $4;
				}
				slVectorArrayInitializer
				|
				SCRL_VECTOR
				SCRL_IDENTIFIER_VALUE
				SCRL_OPEN_SQR_PARANTHESIS
				SCRL_FLOAT_VALUE
				SCRL_CLOSE_SQR_PARANTHESIS
				{
					TCode	*def	=	newVariable($2,TYPE_VECTOR,(int) $4,TRUE);
				}
				;

slNormalParameter:
				SCRL_NORMAL
				SCRL_IDENTIFIER_VALUE
				{
					currentData.currentParameterType	=	TYPE_NORMAL;
				}
				slVector
				{
					TCode	*def	=	newVariable($2,currentData.currentParameterType,1,TRUE);
					float	*v;

					if (def != NULL) {
						v	=	$4;

						def[0].real	=	v[0];
						def[1].real	=	v[1];
						def[2].real	=	v[2];
					}
				}
				|
				SCRL_NORMAL
				SCRL_IDENTIFIER_VALUE
				SCRL_OPEN_SQR_PARANTHESIS
				SCRL_FLOAT_VALUE
				SCRL_CLOSE_SQR_PARANTHESIS
				SCRL_EQUAL
				{
					TCode	*def	=	newVariable($2,TYPE_NORMAL,(int) $4,TRUE);
					
					if(def != NULL) {
						currentData.currentArray = def;
					}
					
					currentData.numArrayItemsRemaining = (int) $4;
				}
				slVectorArrayInitializer
				|
				SCRL_NORMAL
				SCRL_IDENTIFIER_VALUE
				SCRL_OPEN_SQR_PARANTHESIS
				SCRL_FLOAT_VALUE
				SCRL_CLOSE_SQR_PARANTHESIS
				{
					TCode	*def	=	newVariable($2,TYPE_NORMAL,(int) $4,TRUE);
				}
				;

slPointParameter:
				SCRL_POINT
				SCRL_IDENTIFIER_VALUE
				{
					currentData.currentParameterType	=	TYPE_POINT;
				}
				slVector
				{
					TCode	*def	=	newVariable($2,currentData.currentParameterType,1,TRUE);
					float	*v;

					if (def != NULL) {
						v	=	$4;

						def[0].real	=	v[0];
						def[1].real	=	v[1];
						def[2].real	=	v[2];
					}
				}
				|
				SCRL_POINT
				SCRL_IDENTIFIER_VALUE
				SCRL_OPEN_SQR_PARANTHESIS
				SCRL_FLOAT_VALUE
				SCRL_CLOSE_SQR_PARANTHESIS
				SCRL_EQUAL
				{
					TCode	*def	=	newVariable($2,TYPE_POINT,(int) $4,TRUE);
					
					if(def != NULL) {
						currentData.currentArray = def;
					}
					
					currentData.numArrayItemsRemaining = (int) $4;
				}
				slVectorArrayInitializer
				|
				SCRL_POINT
				SCRL_IDENTIFIER_VALUE
				SCRL_OPEN_SQR_PARANTHESIS
				SCRL_FLOAT_VALUE
				SCRL_CLOSE_SQR_PARANTHESIS
				{
					TCode	*def	=	newVariable($2,TYPE_POINT,(int) $4,TRUE);
				}
				;

slVectorValue:	SCRL_TEXT_VALUE
				SCRL_FLOAT_VALUE
				{
					$$[0]	=	$2;
					$$[1]	=	$2;
					$$[2]	=	$2;
				}
				|
				SCRL_TEXT_VALUE
				SCRL_OPEN_SQR_PARANTHESIS
				SCRL_FLOAT_VALUE
				SCRL_FLOAT_VALUE
				SCRL_FLOAT_VALUE
				SCRL_CLOSE_SQR_PARANTHESIS
				{
					$$[0]	=	$3;
					$$[1]	=	$4;
					$$[2]	=	$5;
				}
				|
				SCRL_FLOAT_VALUE
				{
					$$[0]	=	$1;
					$$[1]	=	$1;
					$$[2]	=	$1;
				}
				|
				SCRL_OPEN_SQR_PARANTHESIS
				SCRL_FLOAT_VALUE
				SCRL_FLOAT_VALUE
				SCRL_FLOAT_VALUE
				SCRL_CLOSE_SQR_PARANTHESIS
				{
					$$[0]	=	$2;
					$$[1]	=	$3;
					$$[2]	=	$4;
				}
				;


slVectorArrayInitializer:
				SCRL_OPEN_SQR_PARANTHESIS
				slVectorArrayInitializerItems
				SCRL_CLOSE_SQR_PARANTHESIS
				{
					if(currentData.numArrayItemsRemaining){
						slerror("Wrong number of items in array initializer\n");
					}
				}
				;
		
slVectorArrayInitializerItems:
				slVectorArrayInitializerItems
				slVectorValue
				{
					float *v;
					
					if(currentData.numArrayItemsRemaining > 0){
						if(currentData.currentArray){
							v = $2;
							currentData.currentArray[0].real = v[0];
							currentData.currentArray[1].real = v[1];
							currentData.currentArray[2].real = v[2];
							currentData.currentArray += 3;
						}
						currentData.numArrayItemsRemaining--;
					} else{
						slerror("Wrong number of items in array initializer\n");
					}
				}	
				|
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
					TCode	*def	=	newVariable($2,TYPE_MATRIX,1,TRUE);

					if (def != NULL) {
						def[0].real		=	$5;
						def[1].real		=	$6;
						def[2].real		=	$7;
						def[3].real		=	$8;
						def[4].real		=	$9;
						def[5].real		=	$10;
						def[6].real		=	$11;
						def[7].real		=	$12;
						def[8].real		=	$13;
						def[9].real		=	$14;
						def[10].real	=	$15;
						def[11].real	=	$16;
						def[12].real	=	$17;
						def[13].real	=	$18;
						def[14].real	=	$19;
						def[15].real	=	$20;
					}
				}
				|
				SCRL_MATRIX
				SCRL_IDENTIFIER_VALUE
				SCRL_EQUAL
				SCRL_FLOAT_VALUE
				{
					TCode	*def	=	newVariable($2,TYPE_MATRIX,1,TRUE);

					if (def != NULL) {
						def[0].real		=	$4;
						def[1].real		=	0;
						def[2].real		=	0;
						def[3].real		=	0;
						def[4].real		=	0;
						def[5].real		=	$4;
						def[6].real		=	0;
						def[7].real		=	0;
						def[8].real		=	0;
						def[9].real		=	0;
						def[10].real	=	$4;
						def[11].real	=	0;
						def[12].real	=	0;
						def[13].real	=	0;
						def[14].real	=	0;
						def[15].real	=	1;
					}
				}
				|
				SCRL_MATRIX
				SCRL_IDENTIFIER_VALUE
				{
					TCode	*def	=	newVariable($2,TYPE_MATRIX,1,TRUE);

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
				}
				|
				SCRL_MATRIX
				SCRL_IDENTIFIER_VALUE
				SCRL_OPEN_SQR_PARANTHESIS
				SCRL_FLOAT_VALUE
				SCRL_CLOSE_SQR_PARANTHESIS
				SCRL_EQUAL
				{
					TCode	*def	=	newVariable($2,TYPE_MATRIX,(int) $4,TRUE);
					
					if (def != NULL) {
						int	i;

						for (i=0;i<((int) $4)*16;i++)
							def[i].real	=	0;
						currentData.currentArray = def;
					}
					
					currentData.numArrayItemsRemaining = (int) $4;
				}
				slMatrixArrayInitializer
				|
				SCRL_MATRIX
				SCRL_IDENTIFIER_VALUE
				SCRL_OPEN_SQR_PARANTHESIS
				SCRL_FLOAT_VALUE
				SCRL_CLOSE_SQR_PARANTHESIS
				{
					TCode	*def	=	newVariable($2,TYPE_MATRIX,(int) $4,TRUE);

					if (def != NULL) {
						int	i;

						for (i=0;i<((int) $4)*16;i++)
							def[i].real	=	0;
					}
				}
				;


slMatrixArrayInitializer:
				SCRL_OPEN_SQR_PARANTHESIS
				slMatrixArrayInitializerItems
				SCRL_CLOSE_SQR_PARANTHESIS
				{
					if(currentData.numArrayItemsRemaining){
						slerror("wrong number of items in array initializer\n");
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
					if(currentData.numArrayItemsRemaining > 0){
						if(currentData.currentArray){
							currentData.currentArray[0].real = $3;
							currentData.currentArray[1].real = $4;
							currentData.currentArray[2].real = $5;
							currentData.currentArray[3].real = $6;
							currentData.currentArray[4].real = $7;
							currentData.currentArray[5].real = $8;
							currentData.currentArray[6].real = $9;
							currentData.currentArray[7].real = $10;
							currentData.currentArray[8].real = $11;
							currentData.currentArray[9].real = $12;
							currentData.currentArray[10].real = $13;
							currentData.currentArray[11].real = $14;
							currentData.currentArray[12].real = $15;
							currentData.currentArray[13].real = $16;
							currentData.currentArray[14].real = $17;
							currentData.currentArray[15].real = $18;
							
							currentData.currentArray += 16;
						}
						currentData.numArrayItemsRemaining--;
					}
					else{
						slerror("wrong number of items in array initializer\n");
					}
				}	
				|
				slMatrixArrayInitializerItems
				SCRL_FLOAT_VALUE
				{
					if(currentData.numArrayItemsRemaining > 0){
						if(currentData.currentArray){
							currentData.currentArray[0].real = $2;
							currentData.currentArray[1].real = 0;
							currentData.currentArray[2].real = 0;
							currentData.currentArray[3].real = 0;
							currentData.currentArray[4].real = 0;
							currentData.currentArray[5].real = $2;
							currentData.currentArray[6].real = 0;
							currentData.currentArray[7].real = 0;
							currentData.currentArray[8].real = 0;
							currentData.currentArray[9].real = 0;
							currentData.currentArray[10].real = $2;
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
				SCRL_NL
				|
				;

slVariable:
				slContainer
				slBooleanVariable
				|
				slContainer
				slFloatVariable
				|
				slContainer
				slStringVariable
				|
				slContainer
				slColorVariable
				|
				slContainer
				slVectorVariable
				|
				slContainer
				slNormalVariable
				|
				slContainer
				slPointVariable
				|
				slContainer
				slMatrixVariable
				;

slBooleanVariable:
				SCRL_BOOLEAN
				SCRL_IDENTIFIER_VALUE
				{
					newVariable($2,TYPE_BOOLEAN,1,FALSE);
				}
				|
				SCRL_BOOLEAN
				SCRL_IDENTIFIER_VALUE
				SCRL_OPEN_SQR_PARANTHESIS
				SCRL_FLOAT_VALUE
				SCRL_CLOSE_SQR_PARANTHESIS
				{
					newVariable($2,TYPE_BOOLEAN,(int) $4,FALSE);
				}
				;


slFloatVariable:
				SCRL_FLOAT
				SCRL_IDENTIFIER_VALUE
				{
					newVariable($2,TYPE_FLOAT,1,FALSE);
				}
				|
				SCRL_FLOAT
				SCRL_IDENTIFIER_VALUE
				SCRL_OPEN_SQR_PARANTHESIS
				SCRL_FLOAT_VALUE
				SCRL_CLOSE_SQR_PARANTHESIS
				{
					newVariable($2,TYPE_FLOAT,(int) $4,FALSE);
				}
				;

slStringVariable:
				SCRL_STRING
				SCRL_IDENTIFIER_VALUE
				{
					newVariable($2,TYPE_STRING,1,FALSE);
				}
				|
				SCRL_STRING
				SCRL_IDENTIFIER_VALUE
				SCRL_OPEN_SQR_PARANTHESIS
				SCRL_FLOAT_VALUE
				SCRL_CLOSE_SQR_PARANTHESIS
				{
					newVariable($2,TYPE_STRING,(int) $4,FALSE);
				}
				;

slVectorVariable:
				SCRL_VECTOR
				SCRL_IDENTIFIER_VALUE
				{
					newVariable($2,TYPE_VECTOR,1,FALSE);
				}
				|
				SCRL_VECTOR
				SCRL_IDENTIFIER_VALUE
				SCRL_OPEN_SQR_PARANTHESIS
				SCRL_FLOAT_VALUE
				SCRL_CLOSE_SQR_PARANTHESIS
				{
					newVariable($2,TYPE_VECTOR,(int) $4,FALSE);
				}
				;

slColorVariable:
				SCRL_COLOR
				SCRL_IDENTIFIER_VALUE
				{
					newVariable($2,TYPE_COLOR,1,FALSE);
				}
				|
				SCRL_COLOR
				SCRL_IDENTIFIER_VALUE
				SCRL_OPEN_SQR_PARANTHESIS
				SCRL_FLOAT_VALUE
				SCRL_CLOSE_SQR_PARANTHESIS
				{
					newVariable($2,TYPE_COLOR,(int) $4,FALSE);
				}
				;

slNormalVariable:
				SCRL_NORMAL
				SCRL_IDENTIFIER_VALUE
				{
					newVariable($2,TYPE_NORMAL,1,FALSE);
				}
				|
				SCRL_NORMAL
				SCRL_IDENTIFIER_VALUE
				SCRL_OPEN_SQR_PARANTHESIS
				SCRL_FLOAT_VALUE
				SCRL_CLOSE_SQR_PARANTHESIS
				{
					newVariable($2,TYPE_NORMAL,(int) $4,FALSE);
				}
				;

slPointVariable:
				SCRL_POINT
				SCRL_IDENTIFIER_VALUE
				{
					newVariable($2,TYPE_POINT,1,FALSE);
				}
				|
				SCRL_POINT
				SCRL_IDENTIFIER_VALUE
				SCRL_OPEN_SQR_PARANTHESIS
				SCRL_FLOAT_VALUE
				SCRL_CLOSE_SQR_PARANTHESIS
				{
					newVariable($2,TYPE_POINT,(int) $4,FALSE);
				}
				;

slMatrixVariable:
				SCRL_MATRIX
				SCRL_IDENTIFIER_VALUE
				{
					newVariable($2,TYPE_MATRIX,1,FALSE);
				}
				|
				SCRL_MATRIX
				SCRL_IDENTIFIER_VALUE
				SCRL_OPEN_SQR_PARANTHESIS
				SCRL_FLOAT_VALUE
				SCRL_CLOSE_SQR_PARANTHESIS
				{
					newVariable($2,TYPE_MATRIX,(int) $4,FALSE);
				}
				;

slInit:			SCRL_INIT
				SCRL_NL
				{
					currentData.parsingInit	=	TRUE;
					newLabel(initLabel,FALSE);
				}
				slShaderLine
				;

slCode:			SCRL_CODE
				SCRL_NL
				{
					currentData.parsingInit	=	FALSE;
					newLabel(codeLabel,FALSE);
				}
				slShaderLine
				;

slShaderLine:	
				slShaderLine
				slStatement
				SCRL_NL
				|
				slShaderLine
				slLabelDefinition
				SCRL_NL
				|
				slShaderLine
				slDSO
				SCRL_NL	
				|
				;


slDSO:			SCRL_DSO
				SCRL_IDENTIFIER_VALUE
				{
					switch(currentData.passNumber) {
					case 1:
						currentData.numCode					+=	4;		// opcode
						break;
					case 2:
						strcpy(currentData.currentOpcode,$2);
						currentData.currentArgument			=	0;
						currentData.currentOpcodePlace		=	&currentData.code[currentData.currentCode];
						currentData.currentCode				+=	4;
						currentData.currentPrototype[0]		=	'~';
						currentData.opcodeUniform			=	TRUE;
						break;
					default:
						break;
					}
				}
				SCRL_OPEN_PARANTHESIS
				SCRL_TEXT_VALUE
				SCRL_CLOSE_PARANTHESIS
				slOperandList
				{
					switch(currentData.passNumber) {
					case 1:
						break;
					case 2:
						// Set the opcode here
						void			*handle;
						dsoExecFunction	exec;

						if (currentRenderer->getDSO($2,$5,handle,exec) == TRUE) {
							if ($5[0] == 'o')
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
				}
				;

slOpcode:
				SCRL_IDENTIFIER_VALUE
				{
					switch(currentData.passNumber) {
					case 1:
						currentData.numCode					+=	2;		// opcode
						break;
					case 2:
						strcpy(currentData.currentOpcode,$1);
						currentData.currentArgument			=	0;
						currentData.currentOpcodePlace		=	&currentData.code[currentData.currentCode];
						currentData.currentCode				+=	2;
						currentData.currentPrototype[0]		=	'~';
						currentData.opcodeUniform			=	TRUE;
						break;
					default:
						break;
					}
				}
				|
				SCRL_SURFACE
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
				}
				|
				SCRL_DISPLACEMENT
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
					setOpcode();
				}
				;

slLabelDefinition:
				SCRL_LABEL_VALUE
				SCRL_COLON
				{
					newLabel($1,FALSE);
				}
				;

slOperand:
				SCRL_TEXT_VALUE
				{
					char	*str	=	$1;

					addStringReference(&str,1);
				}
				|
				SCRL_LABEL_VALUE
				{
					newLabel($1,TRUE);
				}
				|
				SCRL_IDENTIFIER_VALUE
				{
					addVariableReference($1);
				}
				|
				SCRL_FLOAT_VALUE
				{
					addFloatReference(&$1,1);
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
					vector	tmp;

					tmp[0]	=	$2;
					tmp[1]	=	$4;
					tmp[2]	=	$6;

					addFloatReference(tmp,3);
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
					matrix	tmp;

					tmp[element(0,0)]	=	$2;
					tmp[element(0,1)]	=	$4;
					tmp[element(0,2)]	=	$6;
					tmp[element(0,3)]	=	$8;
					tmp[element(1,0)]	=	$10;
					tmp[element(1,1)]	=	$12;
					tmp[element(1,2)]	=	$14;
					tmp[element(1,3)]	=	$16;
					tmp[element(2,0)]	=	$18;
					tmp[element(2,1)]	=	$20;
					tmp[element(2,2)]	=	$22;
					tmp[element(2,3)]	=	$24;
					tmp[element(3,0)]	=	$26;
					tmp[element(3,1)]	=	$28;
					tmp[element(3,2)]	=	$30;
					tmp[element(3,3)]	=	$32;

					addFloatReference(tmp,16);
				}
				|
				SCRL_OPEN_PARANTHESIS
				SCRL_TEXT_VALUE
				SCRL_CLOSE_PARANTHESIS
				{
					strcpy(currentData.currentPrototype,$2);
				}
				;

%%
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


