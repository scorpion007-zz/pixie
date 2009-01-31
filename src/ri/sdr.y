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

#include "common/global.h"
#include "common/containers.h"
#include "shader.h"
#include "slcode.h"
#include "error.h"
#include "renderer.h"
#include "dso.h"
#include "ri_config.h"

/////////////////////////////////////////////////////////////////////////////////////
//   First some temporary data structures used during the script parsing


// Some forward definitions
		void							slerror(const char *);		// Forward definition for stupid yacc
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
	const char		*name;
	int				nargs;
	unsigned int	usedParameters;
} TSlOpcode;

typedef struct {
	ESlCode			entryPoint;
	const char		*name;
	const char		*prototype;
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

				int						currentConstantSize;
				int						currentVaryingSize;

				float					*currentArray;			// Array items go here as we read them
				char					**currentStringArray;	// If the array is string, we this pointer instead
				int						numArrayItemsRemaining;	// Number of array items we're still expecting to read
				
				char					currentOpcode[64];		// Holds the opcode being parsed
				char					currentPrototype[64];	// Holds the prototype being parsed
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
												
												if (type == TYPE_STRING)
													currentData.varyingSizes[currentData.currentVariable]	=	numItems*numComp*sizeof(char*);
												else
													currentData.varyingSizes[currentData.currentVariable]	=	numItems*numComp*sizeof(float);
												
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
													if (type == TYPE_STRING) 	newVariable->defaultValue	=	new char*[numItems*numComp];
													else						newVariable->defaultValue	=	new float[numItems*numComp];
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
											currentData.currentArgumentPlace->varyingStep								=	0;
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
												currentData.currentArgumentPlace->varyingStep					=	0;
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
														currentData.currentArgumentPlace->varyingStep	=	(cVariable->uniform ? 0 : currentData.currentArgumentPlace->numItems);
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
													
													if ((var->container != CONTAINER_UNIFORM) || (var->container != CONTAINER_CONSTANT)) {
														currentData.opcodeUniform						=	FALSE;
														currentData.currentArgumentPlace->varyingStep	=	currentData.currentArgumentPlace->numItems;
													} else {
														currentData.currentArgumentPlace->varyingStep	=	0;
													}
															
													currentData.currentArgumentPlace++;
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
														assert(currentData.opcodeUniform < 256);
														
														currentData.currentOpcodePlace->opcode				=	(int) opcode;
														currentData.currentOpcodePlace->numArguments		=	(unsigned char) (currentData.currentArgument);
														currentData.currentOpcodePlace->uniform				=	(unsigned char) (currentData.opcodeUniform);
														currentData.currentOpcodePlace++;
													} else {
														// Allright, we could not find the function, check the DSO shaders
														CDSO	*dso;

														// See if this is a DSO function
														if ((dso = CRenderer::getDSO(currentData.currentOpcode,currentData.currentPrototype)) != NULL) {
														
															// We have the DSO
															if (currentData.currentPrototype[0] == 'o')		currentData.currentOpcodePlace->opcode	=	FUNCTION_DSO_VOID;
															else											currentData.currentOpcodePlace->opcode	=	FUNCTION_DSO;
								
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
%}
%union slval {
	float	real;
	char	*string;
	matrix	m;
	vector	v;
}

// Some tokens
%token	 SCRL_PARAMETERS
%token	 SCRL_VARIABLES
%token	 SCRL_OUTPUT
%token	 SCRL_VARYING
%token	 SCRL_UNIFORM
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
					currentData.shaderType		=	SL_SURFACE;
					currentData.accessorType 	=	ACCESSOR_SURFACE;
				}
				|
				SCRL_DISPLACEMENT
				SCRL_NL
				{
					currentData.shaderType		=	SL_DISPLACEMENT;
					currentData.accessorType	=	ACCESSOR_DISPLACEMENT;
				}
				|
				SCRL_LIGHTSOURCE
				SCRL_NL
				{
					currentData.shaderType		=	SL_LIGHTSOURCE;
					// Note: we don't set accessorType because you can't interpolate into
					// light shader parameters
				}
				|
				SCRL_VOLUME
				SCRL_NL
				{
					currentData.shaderType		=	SL_ATMOSPHERE;
					currentData.accessorType	=	ACCESSOR_ATMOSPHERE;
					// Note: we can assume the accessor is atmosphere as that's the only
					// volume shader that can be interpolated into
				}
				|
				SCRL_IMAGER
				SCRL_NL
				{
					currentData.shaderType		=	SL_IMAGER;
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
					float	*def	=	(float *) newVariable($2,TYPE_FLOAT,1,TRUE);

					if (def != NULL) {
						def[0]	=	$4;
					}
				}
				|
				SCRL_FLOAT
				SCRL_IDENTIFIER_VALUE
				{
					float	*def	=	(float *) newVariable($2,TYPE_FLOAT,1,TRUE);

					if (def != NULL) {
						def[0]		=	0;
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
					float	*def	=	(float *) newVariable($2,TYPE_FLOAT,(int) $4,TRUE);
					
					if (def != NULL) {
						int	i;

						for (i=0;i<(int) $4;i++)
							def[i]	=	0;
						
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
					float	*def	=	(float *) newVariable($2,TYPE_FLOAT,(int) $4,TRUE);

					if (def != NULL) {
						int	i;

						for (i=0;i<(int) $4;i++)
							def[i]	=	0;
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
							*currentData.currentArray++ = $2;
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
					char	**def	=	(char **) newVariable($2,TYPE_STRING,1,TRUE);

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
				}
				|
				SCRL_STRING
				SCRL_IDENTIFIER_VALUE
				SCRL_EQUAL
				SCRL_TEXT_VALUE
				{
					char	**def	=	(char **) newVariable($2,TYPE_STRING,1,TRUE);

					switch(currentData.passNumber) {
					case 1:
						currentData.numStrings++;
						break;
					case 2:
						if (def != NULL) {
							*def	=	currentData.strings[currentData.currentString++]	=	strdup($4);
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
					char	**def	=	(char **) newVariable($2,TYPE_STRING,(int) $4,TRUE);
					
					switch(currentData.passNumber) {
					case 1:
						currentData.numStrings += (int) $4;
						break;
					case 2:
						if (def != NULL) {
							int	i;

							for (i=0;i<(int) $4;i++)
								def[i]	=	NULL;
							
							currentData.currentStringArray = def;
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
					char	**def	=	(char **) newVariable($2,TYPE_STRING,(int) $4,TRUE);

					if (def != NULL) {
						int	i;

						for (i=0;i<(int) $4;i++)
							def[i]	=	NULL;
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
							*currentData.currentStringArray++	=	currentData.strings[currentData.currentString++]	=	strdup($2);
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
					float	*def	=	(float *) newVariable($2,currentData.currentParameterType,1,TRUE);

					if (def != NULL) {
						movvv(def,$4);
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
					float	*def	=	(float *) newVariable($2,TYPE_COLOR,(int) $4,TRUE);
					
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
					float	*def	=	(float *) newVariable($2,TYPE_COLOR,(int) $4,TRUE);
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
					float	*def	=	(float *) newVariable($2,currentData.currentParameterType,1,TRUE);

					if (def != NULL) {
						movvv(def,$4);
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
					float	*def	=	(float *) newVariable($2,TYPE_VECTOR,(int) $4,TRUE);
					
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
					float	*def	=	(float *) newVariable($2,TYPE_VECTOR,(int) $4,TRUE);
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
					float	*def	=	(float *) newVariable($2,currentData.currentParameterType,1,TRUE);

					if (def != NULL) {
						movvv(def,$4);
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
					float	*def	=	(float *) newVariable($2,TYPE_NORMAL,(int) $4,TRUE);
					
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
					float	*def	=	(float *) newVariable($2,TYPE_NORMAL,(int) $4,TRUE);
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
					float	*def	=	(float *)newVariable($2,currentData.currentParameterType,1,TRUE);

					if (def != NULL) {
						movvv(def,$4);
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
					float	*def	=	(float *) newVariable($2,TYPE_POINT,(int) $4,TRUE);
					
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
					float 	*def	=	(float *) newVariable($2,TYPE_POINT,(int) $4,TRUE);
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
					
					if(currentData.numArrayItemsRemaining > 0){
						if(currentData.currentArray){
							movvv(currentData.currentArray,$2);
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
					float	*def	=	(float *) newVariable($2,TYPE_MATRIX,1,TRUE);

					if (def != NULL) {
						def[0]		=	$5;
						def[1]		=	$6;
						def[2]		=	$7;
						def[3]		=	$8;
						def[4]		=	$9;
						def[5]		=	$10;
						def[6]		=	$11;
						def[7]		=	$12;
						def[8]		=	$13;
						def[9]		=	$14;
						def[10]		=	$15;
						def[11]		=	$16;
						def[12]		=	$17;
						def[13]		=	$18;
						def[14]		=	$19;
						def[15]		=	$20;
					}
				}
				|
				SCRL_MATRIX
				SCRL_IDENTIFIER_VALUE
				SCRL_EQUAL
				SCRL_FLOAT_VALUE
				{
					float	*def	=	(float *) newVariable($2,TYPE_MATRIX,1,TRUE);

					if (def != NULL) {
						def[0]		=	$4;
						def[1]		=	0;
						def[2]		=	0;
						def[3]		=	0;
						def[4]		=	0;
						def[5]		=	$4;
						def[6]		=	0;
						def[7]		=	0;
						def[8]		=	0;
						def[9]		=	0;
						def[10]		=	$4;
						def[11]		=	0;
						def[12]		=	0;
						def[13]		=	0;
						def[14]		=	0;
						def[15]		=	1;
					}
				}
				|
				SCRL_MATRIX
				SCRL_IDENTIFIER_VALUE
				{
					float	*def	=	(float *) newVariable($2,TYPE_MATRIX,1,TRUE);

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
				}
				|
				SCRL_MATRIX
				SCRL_IDENTIFIER_VALUE
				SCRL_OPEN_SQR_PARANTHESIS
				SCRL_FLOAT_VALUE
				SCRL_CLOSE_SQR_PARANTHESIS
				SCRL_EQUAL
				{
					float	*def	=	(float *) newVariable($2,TYPE_MATRIX,(int) $4,TRUE);
					
					if (def != NULL) {
						int	i;

						for (i=0;i<((int) $4)*16;i++)
							def[i]	=	0;
							
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
					float	*def	=	(float *) newVariable($2,TYPE_MATRIX,(int) $4,TRUE);

					if (def != NULL) {
						int	i;

						for (i=0;i<((int) $4)*16;i++)
							def[i]	=	0;
					}
				}
				;


slMatrixArrayInitializer:
				SCRL_OPEN_SQR_PARANTHESIS
				slMatrixArrayInitializerItems
				SCRL_CLOSE_SQR_PARANTHESIS
				{
					if(currentData.numArrayItemsRemaining){
						slerror("Wrong number of items in array initializer\n");
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
							currentData.currentArray[0] = $3;
							currentData.currentArray[1] = $4;
							currentData.currentArray[2] = $5;
							currentData.currentArray[3] = $6;
							currentData.currentArray[4] = $7;
							currentData.currentArray[5] = $8;
							currentData.currentArray[6] = $9;
							currentData.currentArray[7] = $10;
							currentData.currentArray[8] = $11;
							currentData.currentArray[9] = $12;
							currentData.currentArray[10] = $13;
							currentData.currentArray[11] = $14;
							currentData.currentArray[12] = $15;
							currentData.currentArray[13] = $16;
							currentData.currentArray[14] = $17;
							currentData.currentArray[15] = $18;
							
							currentData.currentArray += 16;
						}
						currentData.numArrayItemsRemaining--;
					}
					else{
						slerror("Wrong number of items in array initializer\n");
					}
				}	
				|
				slMatrixArrayInitializerItems
				SCRL_FLOAT_VALUE
				{
					if(currentData.numArrayItemsRemaining > 0){
						if(currentData.currentArray){
							currentData.currentArray[0] = $2;
							currentData.currentArray[1] = 0;
							currentData.currentArray[2] = 0;
							currentData.currentArray[3] = 0;
							currentData.currentArray[4] = 0;
							currentData.currentArray[5] = $2;
							currentData.currentArray[6] = 0;
							currentData.currentArray[7] = 0;
							currentData.currentArray[8] = 0;
							currentData.currentArray[9] = 0;
							currentData.currentArray[10] = $2;
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
						slerror("Wrong number of items in array initializer\n");
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
					char	*dsoName	=	$2;
					
					switch(currentData.passNumber) {
					case 1:
						currentData.numCode++;					// opcode
						break;
					case 2:
						strcpy(currentData.currentOpcode,$2);
						currentData.currentArgument					=	0;
						currentData.currentOpcodePlace->arguments	=	currentData.currentArgumentPlace;
						currentData.currentPrototype[0]				=	'~';
						currentData.opcodeUniform					=	TRUE;
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
						CDSO	*dso;

						if ((dso = CRenderer::getDSO($2,$5)) != NULL) {
							// Save the DSO opcode
							if ($5[0] == 'o')	currentData.currentOpcodePlace->opcode		=	FUNCTION_DSO_VOID;
							else				currentData.currentOpcodePlace->opcode		=	FUNCTION_DSO;

							assert(currentData.opcodeUniform < 256);
							
							currentData.currentOpcodePlace->numArguments	=	(unsigned char) (currentData.currentArgument);
							currentData.currentOpcodePlace->uniform			=	(unsigned char) (currentData.opcodeUniform);															
							currentData.currentOpcodePlace->dso				=	dso;
							currentData.currentOpcodePlace++;
						} else {
							slerror("Failed to locate DSO function\n");
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
						currentData.numCode++;		// opcode
						break;
					case 2:
						strcpy(currentData.currentOpcode,$1);
						currentData.currentArgument					=	0;
						currentData.currentOpcodePlace->arguments	=	currentData.currentArgumentPlace;
						currentData.currentPrototype[0]				=	'~';
						currentData.opcodeUniform					=	TRUE;
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
				}
				|
				SCRL_DISPLACEMENT
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
void	slerror(const char *s) {
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
	currentData.name		=	name;
	currentData.passNumber	=	1;
	
	// The first pass
	memBegin(CRenderer::globalMemory);
	slparse();
	memEnd(CRenderer::globalMemory);

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
	
	// The second pass
	memBegin(CRenderer::globalMemory);
	slparse();
	memEnd(CRenderer::globalMemory);
	
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

	// Sanity check for the shaders
	assert(currentData.numConstants		==	currentData.currentConstant);
	assert(currentData.numVariables		==	currentData.currentVariable);
	assert(currentData.numStrings		==	currentData.currentString);
	assert(currentData.constantSize		==	currentData.currentConstantSize);
	assert(currentData.varyingSize		==	currentData.currentVaryingSize);
	assert((currentData.currentOpcodePlace - currentData.code)			== currentData.numCode);
	assert((currentData.currentArgumentPlace - currentData.arguments)	== currentData.numArgument);

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
	
	cShader->analyse();
	

	currentData.memory					=	NULL;
	currentData.code					=	NULL;
	currentData.constants				=	NULL;
	currentData.varyingSizes			=	NULL;
	currentData.strings					=	NULL;
	currentData.constantEntries			=	NULL;
	

	return cShader;
}


extern	void		convertColorFrom(float *out,const float *in,ECoordinateSystem s);

