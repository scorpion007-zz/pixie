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
//  File				:	sdr.h
//  Classes				:	CScriptContext
//  Description			:
//
////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//
//
//
//
//
//
//				Script compiler header file ...
//				This file handles most of the stuff 
//
//
//				The script language is RenderMan Shading Language
//				However, I am making some modifications for a general
//				structure.
//
//
//
//				Note that the compiler is not designed for efficiency.
//				It may use a lot of memory and may do some unnecessary work.
//
//
//
//
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
#ifndef SCRIPTCOMPILER_H
#define SCRIPTCOMPILER_H
#include "common/global.h"					// The global header file
#include "common/containers.h"				// Our useful list class
#include "common/os.h"
#include "expression.h"						// Expressions


// Forward definitions
class	CSymbol;							// CSymbol class
class	CVariable;							// CVariable class
class	CParameter;							// CParameter class
class	CFunction;							// CFunction class
class	CFunctionPrototype;					// A function prototype
class	CScriptContext;						// The main shader context. Holds everything


// Bit position definitions for the settings field of the CScriptContext
const	int		COMPILER_SUPPRESS_WARNINGS		=	1;
const	int		COMPILER_SUPPRESS_ERRORS		=	2;
const	int		COMPILER_SUPPRESS_DEFINITIONS	=	4;


////////////////////////////////////////////////////////////////
// Type constants, all the types are kept in an integer
// where the specific bit positions determine the type and scope of the type
const	int		SLC_FLOAT				=	1 << 0;		// Float
const	int		SLC_VECTOR				=	1 << 1;		// A vector of 3 floats
const	int		SLC_STRING				=	1 << 2;		// String
const	int		SLC_MATRIX				=	1 << 3;		// Matrix
const	int		SLC_NONE				=	1 << 4;		// No type

const	int		SLC_RDONLY				=	1 << 6;		// Read only variable

const	int		SLC_VNORMAL				=	1 << 7;		// Vector is a normal
const	int		SLC_VVECTOR				=	1 << 8;		// Vector is a vector
const	int		SLC_VPOINT				=	1 << 9;		// Vector is a point
const	int		SLC_VCOLOR				=	1 << 10;	// Vector is a color

const	int		SLC_ARRAY				=	1 << 11;	// Variable is an array

const	int		SLC_EXTERN				=	1 << 12;	// Variable is an extern

const	int		SLC_UNIFORM				=	1 << 13;	// Variable is uniform
const	int		SLC_VARYING				=	1 << 14;	// Variable is varying (used only to differentiate non uniform params)
														// Note 1<<15 was removed

const	int		SLC_LOCKED				=	1 << 16;	// Variable is a locked temporary variable
const	int		SLC_OUTPUT				=	1 << 17;	// Variable is output

const	int		SLC_GLOBAL				=	1 << 18;	// Variable is global
const	int		SLC_PARAMETER			=	1 << 19;	// Variable is parameter

// Some masks that can be used to isolate specific postions of the type integer
const	int		SLC_TYPE_MASK			=	SLC_FLOAT | SLC_VECTOR | SLC_STRING | SLC_MATRIX | SLC_NONE;
const	int		SLC_SUB_TYPE_MASK		=	SLC_VNORMAL | SLC_VVECTOR | SLC_VPOINT | SLC_VCOLOR;

// Script types
const	int		SLC_SURFACE				=	1 << 0;		// The script is a RenderMan surface shader
const	int		SLC_LIGHT				=	1 << 1;		// The script is a RenderMan light source shader
const	int		SLC_DISPLACEMENT		=	1 << 2;		// The script is a RenderMan displacement shader
const	int		SLC_VOLUME				=	1 << 3;		// The script is a RenderMan volume shader
const	int		SLC_TRANSFORMATION		=	1 << 4;		// The script is a RenderMan transformation shader (not supported yet)
const	int		SLC_IMAGER				=	1 << 5;		// The script is a RenderMan imager shader
const	int		SLC_GENERIC				=	1 << 6;		// The script is a generic script








// This structure is used to hold a linked list of search directories
typedef struct TSearchpath {
	char		*directory;
	TSearchpath	*next;
} TSearchpath;




///////////////////////////////////////////////////////////////////////
// Class				:	CSymbol
// Description			:	This class is used as a base class for anything that has a name.
// Comments				:	The CFunction , CVariable , CParameter are derived
//							Note that the symbol name holds the name of the symbol (variable/function/...)
//							as it appears in the source code. Thus it may not be unique.
//							The defLineNo and defFileName holds the position of the definition
//							of this symbol. They can be NULL.
class	CSymbol {
public:
						CSymbol(const char *);							// The parameter is the name of the symbol
	virtual				~CSymbol();
	
	char				*symbolName;									// This is the name a variable refered in the original code
	int					defLineNo;										// The line number where the symbol is defined
	char				*defFileName;									// The source file where the symbol is defined
};



///////////////////////////////////////////////////////////////////////
// Class				:	variable
// Description			:	This class designates a variable (or parameter)
// Comments				:	CParameter class is derived from this. The variableType
//							field is a 32 bit integer whose individual bits designate the type
//							and the scope of the variable. The meanings of the bit positions
//							are defined at the top of this file (constants that start with SLC_...)
//							The varName field holds the name of the variable in the final code.
//							So it has to be unique. 
//							The numItems field holds the multiplicity of the variable.
//							This field is originally 1 but if the SLC_ARRAY bit of the variableType
//							is set, it should contain the number of items in the array.
//							The parent field can not be NULL. The script context will create a dummy function
//							that owns all variables (including global ones) at the beginning.
class	CVariable : public CSymbol {
public:
																		// The parameters to constructor are:
																		// The name of the variable (as it appears in the source code, must be unique)
																		// A unique name for the variable that will be used during the code generation
																		// The function owning this variable
																		// The type of the variable
																		// The multiplicity of the variable
						CVariable(const char *,int,int multiplicity=1);
						~CVariable();

	virtual	char		*codeName();

	int					type;											// Type of the variable
	int					numItems;										// The number of items in the variable if its an array
	char				*cName;											// The unique code name of the variable
};



///////////////////////////////////////////////////////////////////////
// Class				:	CParameter
// Description			:	This class designates a function or script parameter.
// Comments				:	The parameterNumber field holds the position of the parameter in the parameter
//							list. (0 being the leftmost parameter). The defaultValue field holds the default
//							value of the parameter. The parent field can not be NULL.
class	CParameter : public CVariable {
public:
																		// The constructor parameters are:
																		// The name of the parameter as it appears in the source code
																		// The function owning this parameter
																		// The type of the parameter
																		// The multiplicity of the parameter
																		// The order of the parameter from left
						CParameter(const char *,int,int);
						~CParameter();

	virtual	char		*codeName();

	CVariable			*mapping;										// The variable having the value of the parameter
	char				*defaultValue;									// The default value of the parameter. This field is used only for the script parameters for the time being
	int					savedType;										// The actual type of the parameter
};







///////////////////////////////////////////////////////////////////////
// Class				:	CFunction
// Description			:	This class holds the code and the environment belonging to a user defined function
// Comments				:	The function class holds a list of parameters to itself,
//							a list of variables defined in it, and a list of functions defined in it. Note that
//							every { } pair actually defines a function. Such blocks don't have any parameters.
//							addParameter / addVariable / addFunction functions MUST be used to insert new stuff
//							into the function and getVariable / getFunction must be used to query for a symbol.
//							(getXXX functions will also check the parent)
//							The parent function can be NULL only for the top level function (only one exists)
//							Note that functions are expanded as in-line, so they don't need unique names
//							to appear in the generated code
class	CFunction : public CSymbol {
public:
																		// The parameters to the constructor are:
																		// The name of the function as it appears in the source code
																		// The function owning this function
							CFunction(const char *,CFunction *);
							~CFunction();

	CParameter				*addParameter(const char *,int,int);		// Adds a parameter into the papameter list. Retuns NULL if a parameter with the same name exists
	CVariable				*addVariable(const char *,int,int);			// Adds a variable into the variable list. Returns NULL if a variable with the same name exists
	CFunction				*addFunction(const char *);					// Adds a function into the function list.

	CVariable				*getVariable(const char *,int probe=FALSE);		// Gets the variable record associated with the name. Returns null if the variable doesn't exist
																		// Gets the function associated with the name and the parameter list. Retuns NULL if not found
	CFunction				*getFunction(const char *,CList<CExpression *> *,int returnType = SLC_NONE);	

	CExpression				*initExpression;
	CExpression				*code;

	CParameter				*returnValue;								// The return value
	int						returnValueGiven;							// TRUE if the return value was given
	CList<CParameter *>		*parameters;								// List of parameters
	CList<CVariable *>		*variables;									// List of variables
	CList<CFunction *>		*functions;									// List of functions
	char					*name;										// Name of the function
	CFunction				*parent;									// Parent function (in static scope)
};












///////////////////////////////////////////////////////////////////////
// Class				:	CFunctionPrototype
// Description			:	This class holds the signature of a user defined function
// Comments				:	I may want to use this class to add functions exportable from other scripts etc.
//							This class encapsulates a predefined function prototype. Function prototypes
//							are used to designate built-in functions. This class provides functionality to
//							generate built-in function calls for a given parameter list.
//							The prototype string holds the actual signature of the function
//							e.g.:	f=f	means	float	my_function(float)
//									f=F	=		float	my_function(output float) or
//														my_function(float [])
//							Capitol letters mean that the parameter has be passed by reference otherwise
//							they are passed by value. Actually, screw this, all variables are passed
//							by value but since non-output variables are marked RD_ONLY, they won't be
//							changed anyway
class	CFunctionPrototype : public CSymbol {
public:
																		// The constructor parameters are:
																		// The name of the function as it appears in the source code
																		// The prototype string
																		// The script that this function can be called from
						CFunctionPrototype(const char *,const char *,int = SLC_GENERIC | SLC_SURFACE | SLC_LIGHT | SLC_DISPLACEMENT | SLC_TRANSFORMATION | SLC_IMAGER | SLC_VOLUME,int nonuniform=FALSE);
						~CFunctionPrototype();

																		// Returns TRUE if the given function matches perfectly to this
	int					perfectMatch(const char *,CList<CExpression *> *,int dt = SLC_NONE);	
																		// Returns TRUE if these two functions are compatible
	int					match(const char *,CList<CExpression *> *,int dt = SLC_NONE);	
																		// Returns the function call code
	
	char				*prototype;										// The prototype of the function (e.g.: "f=f" for sin)
	int					compatibleShaders;								// A list of compatible shader types
	int					functionType;									// Type of the function
	int					nonuniform;										// TRUE if want to force non-uniformity
	int					dso;											// TRUE if the function is defined in a DSO
};













///////////////////////////////////////////////////////////////////////
// Class				:	CScriptContext
// Description			:	This class is used to hold information about the file being compiled
// Comments				:	The main compiler manager class.
class	CScriptContext {
	typedef	void	(*dsoCallbackFunction)(char *name,char *prototype);
public:
						CScriptContext(int s = 0);
						~CScriptContext();


																		// Add global junk
	CFunctionPrototype	*addBuiltInFunction(const char *,const char *,int,int nonuniform=FALSE);
	void				addGlobalVariable(const char *,int,int);
	int					compile(FILE *,char *outName = NULL);			// All mighty compile function


																		// The following two functions are
																		// used to search the context for a function
																		// or a variable
	CFunction			*getFunction(const char *,CList<CExpression *> *);
	CVariable			*getVariable(const char *);

	void				define(CSymbol *);								// Define a symbol here
	void				printDefine(CSymbol *);							// Print the definition of a symbol

	CVariable			*lockRegister(int,int numItems=1);				// Allocate a temporary register
	void				releaseRegister(CVariable *);					// Deallocate a temporary register

	CParameter			*newParameter(const char *,int,int);			// Create a new parameter to the topmost function
	CVariable			*newVariable(const char *,int,int);				// Create a new variable to the topmost function
	CFunction			*newFunction(const char *);						// Create a function to the topmost function																		
	void				newLabel(char *);								// Create a unique label
	void				addVariable(CVariable *);						// Create a unique name for the variable

	CFunction			*popFunction();									// Pop the topmost function in the function stack

	void				uniformParameters();							// Make all the parameters uniform
	void				restoreParameters();							// Restore all the parameters to their original types
	void				generateCode(const char *);						// Prints the generated code into a stream

	void				enumerateDso(const char *);						// Find a DSO and add it into the library

	void				error(const char *,...);						// Compiler error
	void				warning(const char *,...);						// Compiler warning
	void				fatal(const char *,...);						// Fatal compiler error
	void				fatalbailout();									// Fatal compiler error, standard error message

	void				desire(int);									// Desire a particular type
	int					undesire();										// Return back to the previous desired type
	int					desired();										// Return the desired type







int						compileError;									// The number of compiler errors
int						compileWarning;									// The number of compiler warnings
int						settings;										// The compiler settings

CFunction				*rootFunction;									// The topmost function
CFunction				*shaderFunction;								// The shader function
CList<CVariable *>		*variables;										// List of all the variables
CList<CVariable *>		*temporaryRegisters;							// List of temporary registers
int						numTemporaryRegisters;							// Number of temporary registers
int						numLabels;										// Number of labels

CList<CFunction *>		*functionStack;									// The current function stack
CList<CFunction *>		*runtimeFunctionStack;							// The runtime function stack
CFunction				*lastFunction;									// The stack top in the function stack

CList<char *>			*allocatedStrings;								// A list of all the allocated strings
																		// (So that we can deallocated them later at once)
																		// FIXME: This structure can also be used to prune the allocated strings in
																		// the middle of compilation if the allocated strings are not needed anymore.
																		// I may want to add this functionality later.
TSearchpath				*dsoPath;										// Points to the DSO path

int						passNo;											// 0 - error check, 1 - code generation
int						lineNo;											// The current line no
int						statementLineNo;								// The line number we started parsing
char					*sourceFile;									// The current source file


char					*shaderName;									// The name of the shader
int						shaderType;										// The type of the shader

CList<CFunctionPrototype *>		*builtinFunctions;					// List of all the built-in functions
CList<CVariable *>				*globalVariables;					// List of all global variables

																		// The stuff below is used to keep track of the type context information so that
																		// We can figure out what variable type we want to have for "texture" or "noise" like calls
																		// The management routines are extremely ugly
int						desiredType;									// The desired type in the current context
CList<int>				*desiredTypeStack;

																		// The following stuff is used to manage the 
																		// parameter lists that are passed to functions
																		// (somewhat ugly)
CList<CVariable *>				*variableList;							// Internal stuff
CList<CList<CExpression *> *>	*actualParameterStack;
CList<CExpression *>			*actualParameters;

int								requiredShaderContext;					// This holds the shader types that the code expects
																		// For example, is the code has an illuminate statement, the
																		// SLC_LIGHT_SOURCE field will be on
																		// Compilation flags
};


extern	CScriptContext		*sdr;
extern	void				addDSO(char *,char *);

#endif

