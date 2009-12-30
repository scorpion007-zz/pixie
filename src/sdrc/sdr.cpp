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
//  File				:	sdr.cpp
//  Classes				:	CScriptContext
//  Description			:	The main compiler class
//
////////////////////////////////////////////////////////////////////////
#include	<string.h>
#include	<stdarg.h>
#include	<stdlib.h>


#include	"sdr.h"
#include	"opcodes.h"				// This file holds the constant strings
#include	"ri/shadeop.h"
#include	"ri/dso.h"


///////////////////////////////////////////////////////////////////////
// Class				:	symbol
// Method				:	CSymbol(char *)
// Description			:	Allocate memory ...
// Comments				:	The first parameter is the name of the variable as referenced in the code
CSymbol::CSymbol(const char *name) {
	assert(name != NULL);

	symbolName	=	strdup(name);
	defFileName	=	NULL;
	defLineNo	=	0;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CSymbol
// Method				:	~CSymbol()
// Description			:	De-allocate memory
// Comments				:
CSymbol::~CSymbol() {
	free(symbolName);
	if (defFileName != NULL) free(defFileName);
}













///////////////////////////////////////////////////////////////////////
// Class				:	CVariable
// Method				:	CVariable(char *,function *)
// Description			:	Init the structure
// Comments				:	The first parameter is the name of the variable as referenced in the code and
//							the second parameter is the function defining this variable
CVariable::CVariable(const char *name,int type,int multiplicity) : CSymbol(name) {

	// Sanity check
	if (multiplicity > 1) {
		if (!(type & SLC_ARRAY)) {
			sdr->error("Variable \"%s\" has more than one items (%d) but is not an array\n",name,multiplicity);
		}
	}

	// Make sure the array size is reasonable
	if (multiplicity <= 0) {
		sdr->error("Array size for \"%s\" is invalid (%d)\n",name,multiplicity);
		multiplicity	=	1;
	}

	// Record
	this->type		=	type;
	this->numItems	=	multiplicity;						// Note that numItems field only makes sense if the ARRAY field
	cName			=	NULL;								// of the type is set
}

///////////////////////////////////////////////////////////////////////
// Class				:	CVariable
// Method				:	~CVariable()
// Description			:	De-allocate memory
// Comments				:
CVariable::~CVariable() {
	if (cName != NULL)	free(cName);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CVariable
// Method				:	codeName
// Description			:	Get the codename for the variable
// Comments				:
char	*CVariable::codeName() {
	assert(cName != NULL);

	return cName;
}













///////////////////////////////////////////////////////////////////////
// Class				:	CParameter
// Method				:	CParameter
// Description			:	Ctor
// Comments				:	The first two parameters are directly passed to CVariable. The last parameter
//							designates the number of the parameter in the order from left to right starting
//							from 0. Thus this function replaces the actual parameter name with "$0", "$1" ...
//							so that later on, the occurance of these parameters in the code can be translated
//							to the actual parameter names in the caller's context
CParameter::CParameter(const char *name,int type,int multiplicity) : CVariable(name,type,multiplicity) {
	defaultValue	=	NULL;
	mapping			=	NULL;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CParameter
// Method				:	~CParameter()
// Description			:	De-allocate the memory
// Comments				:
CParameter::~CParameter() {
	if (defaultValue != NULL)
		free(defaultValue);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CParameter
// Method				:	codeName
// Description			:	Get the code name
// Comments				:
char	*CParameter::codeName() {
	if (mapping != NULL)	return	mapping->codeName();

	// We must be a shader parameter
	return symbolName;
}











	
///////////////////////////////////////////////////////////////////////
// Class				:	CFunction
// Method				:	CFunction
// Description			:	Ctor
// Return Value			:
// Comments				:
CFunction::CFunction(const char *name,CFunction *p) : CSymbol(name) {
	this->returnValue		=	NULL;
	this->returnValueGiven	=	FALSE;
	this->initExpression	=	NULL;
	this->code				=	NULL;
	this->parameters		=	new CList<CParameter *>;
	this->variables			=	new CList<CVariable *>;
	this->functions			=	new CList<CFunction *>;

	this->name				=	strdup(name);
	this->parent			=	p;

}

///////////////////////////////////////////////////////////////////////
// Class				:	CFunction
// Method				:	~CFunction
// Description			:	Dtor
// Return Value			:
// Comments				:
CFunction::~CFunction() {
	if (initExpression != NULL)	delete initExpression;
	if (code != NULL)			delete code;

	if (returnValue != NULL)	delete returnValue;
	parameters->destroy();
	variables->destroy();
	functions->destroy();
	free(name);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFunction
// Method				:	addParameter(char *)
// Description			:	This method creates a new parameter and adds it into the the function.
// Return Value			:	The newly added parameter
// Comments				:
CParameter	*CFunction::addParameter(const char *name,int type,int multiplicity) {
	CParameter	*cParameter;

	// Check the function parameters
	for (cParameter=parameters->first();cParameter != NULL;cParameter=parameters->next()) {
		// We already have a parameter with the same name
		if (strcmp(cParameter->symbolName,name) == 0) {
			sdr->error("Parameter \"%s\" is already defined\n",name);
			return	cParameter;
		}
	}

	cParameter	=	new CParameter(name,type,multiplicity);
					
	parameters->push(cParameter);

	return cParameter;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFunction
// Method				:	addVariable(char *)
// Description			:	This method creates a new variable and adds it into the function
// Return Value			:	The newly create variable (NULL if the variable (or parameter) already exists)
// Comments				:	This method adds a copy of the variable into the parent's list as well
//							This is done so that variables declared in the scope are propegated to the parent function
CVariable	*CFunction::addVariable(const char *name,int type,int multiplicity) {
	CVariable	*cVariable;

	// Check the function parameters
	for (cVariable=parameters->first();cVariable != NULL;cVariable=parameters->next()) {
		// We already have a parameter with the same name
		if (strcmp(cVariable->symbolName,name) == 0) {
			sdr->error("%s was defined as parameter\n",name);
			return cVariable;
		}
	}

	// Check the function variables
	for (cVariable=variables->first();cVariable != NULL;cVariable=variables->next()) {
		if (strcmp(cVariable->symbolName,name) == 0) {
			sdr->error("Variable \"%s\" is already defined\n",name);
			return	cVariable;
		}
	}

	cVariable	=	new CVariable(name,type,multiplicity);

	variables->push(cVariable);

	return cVariable;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CFunction
// Method				:	addFunction(char *name)
// Description			:	This method adds a new function to the current function
// Return Value			:	The newly added function
// Comments				:	This function does not check the existance of another function
//							with the exact same signature.
CFunction	*CFunction::addFunction(const char *name) {
	// FIXME: should I check if a function having exactly the same signature defined ?
	CFunction	*cFun	=	new CFunction(name,this);

	return cFun;
}

///////////////////////////////////////////////////////////////////////
// Class				:	function
// Method				:	getVariable(char *name,int depth)
// Description			:	This method searches for a variable. The name is the variable's name as it is in the source code
// Return Value			:	NULL if the variable not found, pointer to the variable (or parameter) othervise
// Comments				:	If the variable is not found in this function, method searches the parents as well.
//							The second parameter is used to controll the number functions above the current function.
//							e.g.: depth=0 means only this function is searched for the variable
CVariable	*CFunction::getVariable(const char *name,int probe) {
	CVariable	*cVariable;

	// Check the function parameters
	for (cVariable=parameters->first();cVariable != NULL;cVariable=parameters->next())
		if (strcmp(cVariable->symbolName,name) == 0) return cVariable;

	// Check the function variables
	for (cVariable=variables->first();cVariable != NULL;cVariable=variables->next())
		if (strcmp(cVariable->symbolName,name) == 0) return cVariable;


	if ((strcmp(this->symbolName,constantLoopName)	== 0) ||
		(strcmp(this->symbolName,constantBlockName)	== 0)) {
		if (parent != NULL) {
			return parent->getVariable(name,probe);
		}
	} else {
		if (probe == TRUE) {
			if (parent != NULL) {
				return parent->getVariable(name,probe);
			}
		}
	}

	//if (probe == FALSE)
	//	sdr->error("Variable \"%s\" is not found\n",name);

	return NULL;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFunction
// Method				:	getFunction(char *,CList<CCodeBlock *> *,int)	
// Description			:	This method searches all the defined functions for a match
// Return Value			:	NULL if no compatible function exists, a pointer to the function othervise
// Comments				:
CFunction	*CFunction::getFunction(const char *name,CList<CExpression *> *args,int returnType) {
	CFunction	*cFun;

	// Look for an exact match first
	for (cFun = functions->first(); cFun != NULL ; cFun = functions->next()) {
		CParameter	*cPar;
		CExpression	*cArg;

		// Check names first
		if (strcmp(name,cFun->symbolName) != 0) continue;

		// The number of arguments must match exactly (No default values yet)
		if (cFun->parameters->numItems != args->numItems) continue;

		// Try 1 to 1 matching first
		for (cPar = cFun->parameters->first(), cArg = args->first(); cPar != NULL; cPar = cFun->parameters->next(), cArg = args->next()) {

			// Do the types match	?
			if ((cPar->type & SLC_TYPE_MASK) & (cArg->type & SLC_TYPE_MASK)) {

				// Do the sub-types match ?
				if (cPar->type & SLC_VECTOR) {
					if ((cPar->type & SLC_SUB_TYPE_MASK) & (cArg->type & SLC_SUB_TYPE_MASK)) {

						// Do the return values match ?
						if (cFun->returnValue != NULL) {
							if ((returnType & SLC_TYPE_MASK) & (cFun->returnValue->type & SLC_TYPE_MASK)) {
								if (returnType & SLC_VECTOR) {
									if ((returnType & SLC_SUB_TYPE_MASK) & (cFun->returnValue->type & SLC_SUB_TYPE_MASK)) continue;
									else break;
								} else continue;
							}
						} else {
							if (returnType & SLC_NONE) {
							} else {
								break;
							}
						}
					} else break;
				}  else {
					// Do the return values match ?
					if (cFun->returnValue != NULL) {
						if ((returnType & SLC_TYPE_MASK) & (cFun->returnValue->type & SLC_TYPE_MASK)) {
							if (returnType & SLC_VECTOR) {
								if ((returnType & SLC_SUB_TYPE_MASK) & (cFun->returnValue->type & SLC_SUB_TYPE_MASK)) continue;
								else break;
							} else continue;
						}
					} else {
						if (returnType & SLC_NONE) {
						} else {
							break;
						}
					}
				}
			} else break;
		}

		// If exact match, return the function
		if (cPar == NULL) return cFun;
	}

	// ok ... no exact match found... choose the closest one
	for (cFun = functions->first(); cFun != NULL ; cFun = functions->next()) {
		CParameter	*cPar;
		CExpression	*cArg;

		// Function names should still match exactly
		if (strcmp(name,cFun->symbolName) != 0) continue;

		// The number of arguments should still match exactly
		if (cFun->parameters->numItems != args->numItems) continue;

		for (cPar = cFun->parameters->first(), cArg = args->first(); cPar != NULL; cPar = cFun->parameters->next(), cArg = args->next()) {
			if ((cPar->type & SLC_TYPE_MASK) & (cArg->type & SLC_TYPE_MASK)) continue;
			
			// Type coersion is possible
			if ((cPar->type & SLC_VECTOR) && (cArg->type & SLC_FLOAT)) continue;
			if ((cPar->type & SLC_MATRIX) && (cArg->type & SLC_FLOAT)) continue;
			if ((cPar->type & SLC_MATRIX) && (cArg->type & SLC_VECTOR)) continue;
			break;
		}

		if (cPar == NULL) {
			if (!(returnType & SLC_NONE)) {
				if (cFun->returnValue == NULL) continue;

				if ((returnType & SLC_TYPE_MASK) & (cFun->returnValue->type & SLC_TYPE_MASK)) return cFun;

				// Return type coersion is possible
				if ((returnType & SLC_VECTOR) & (cFun->returnValue->type & SLC_FLOAT)) return cFun;
				if ((returnType & SLC_MATRIX) & (cFun->returnValue->type & SLC_FLOAT)) return cFun;
				if ((returnType & SLC_MATRIX) & (cFun->returnValue->type & SLC_VECTOR)) return cFun;
			} else return cFun;
		}
	}

	// If we still couldn't locate the function,  try the parent
	if (this->parent != NULL) {
		return parent->getFunction(name,args,returnType);
	}

	return NULL;
}


///////////////////////////////////////////////////////////////////////
// Class				:	functionPrototype
// Method				:	functionPrototype(char *,char *)
// Description			:	Init the data structures
// Return Value			:	
// Comments				:
CFunctionPrototype::CFunctionPrototype(const char *name,const char *p,int compatible,int nonuniform)  : CSymbol(name) {
	prototype			=	strdup(p);
	compatibleShaders	=	compatible;
	this->nonuniform	=	nonuniform;
	this->dso			=	FALSE;

	switch(prototype[0]) {
	case 'f':
		functionType	=	SLC_FLOAT;
		break;
	case 'v':
		functionType	=	SLC_VECTOR | SLC_VVECTOR;
		break;
	case 'n':
		functionType	=	SLC_VECTOR | SLC_VNORMAL;
		break;
	case 'p':
		functionType	=	SLC_VECTOR | SLC_VPOINT;
		break;
	case 'c':
		functionType	=	SLC_VECTOR | SLC_VCOLOR;
		break;
	case 'm':
		functionType	=	SLC_MATRIX;
		break;
	case 's':
		functionType	=	SLC_STRING;
		break;
	default:
		functionType	=	SLC_NONE;
		break;

	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFunctionPrototype
// Method				:	~CFunctionPrototype
// Description			:	Destroy the structures
// Return Value			:
// Comments				:
CFunctionPrototype::~CFunctionPrototype() {
	free(prototype);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CFunctionPrototype
// Method				:	perfectMatch(char *,CList<CCodeBlock *> *,int)
// Description			:	This function returns TRUE if the prototype matches to the given name,argument list and return type exactly
// Return Value			:	TRUE if the prototype matches exactly
// Comments				:

//////////////////////////////////////////////////////////////////////
//
// Prototype symbols:
// o	-	void
// f	-	float
// F	-	float variable or array
// v	-	vector
// V	-	vector variable or array
// n	-	normal
// N	-	normal variable or array
// p	-	point
// P	-	point variable or array
// c	-	color
// C	-	color variable or array
// s	-	string
// S	-	string variable or array
// .	-	any type
//
// General prototype format:
// <return_type>=<parameterType>*
int			CFunctionPrototype::perfectMatch(const char *name,CList<CExpression *> *pl,int dt) {
	CExpression	*cCode;
	int			cPrototype;

	// Check if the parameter list exactly matches a built-in function prototype

	// Names should match exactly
	if (strcmp(name,symbolName) != 0) return FALSE;

	if (strcmp(name,"shadow") == 0) {
		int	y	=	1;
	}

	// Check the return values
	if (!(dt & SLC_NONE)) {
		if (prototype[0] == 'o') return FALSE;

		if ((prototype[0] == 'f') || (prototype[0] == 'F')) {
			if (!(dt & SLC_FLOAT)) return FALSE;
		} else if (	(prototype[0] == 'v') || (prototype[0] == 'V')	||
					(prototype[0] == 'p') || (prototype[0] == 'P')	||
					(prototype[0] == 'n') || (prototype[0] == 'N')	||
					(prototype[0] == 'c') || (prototype[0] == 'C')	) {
			if (!(dt & SLC_VECTOR))	return FALSE;
		} else if ((prototype[0] == 's') || (prototype[0] == 'S')) {
			if (!(dt & SLC_STRING))	return FALSE;
		} else if ((prototype[0] == 'm') || (prototype[0] == 'M')) {
			if (!(dt & SLC_MATRIX))	return FALSE;
		} else return FALSE;
	} else {
		if (prototype[0] != 'o') return FALSE;
	}

	// Invalid prototype ?
	if (prototype[1] != '=') return FALSE;

	bool parameterList	=	false;
	for (cPrototype = 2,cCode = pl->first(); (cCode != NULL) && (prototype[cPrototype] != '\0'); cCode = pl->next(),cPrototype++) {
		if (prototype[cPrototype] == '.') {
				continue;
		} else if ((prototype[cPrototype] == 'f') || (prototype[cPrototype] == 'F')) {
			if (cCode->type & SLC_FLOAT) continue;
		} else if (	(prototype[cPrototype] == 'v') || (prototype[cPrototype] == 'V') || 
					(prototype[cPrototype] == 'p') || (prototype[cPrototype] == 'P') || 
					(prototype[cPrototype] == 'n') || (prototype[cPrototype] == 'N') || 
					(prototype[cPrototype] == 'c') || (prototype[cPrototype] == 'C')) {
			if (cCode->type & SLC_VECTOR) continue;
		} else if ((prototype[cPrototype] == 's') || (prototype[cPrototype] == 'S')) {
			if (cCode->type & SLC_STRING) continue;
		} else if ((prototype[cPrototype] == 'm') || (prototype[cPrototype] == 'M')) {
			if (cCode->type & SLC_MATRIX) continue;
		} else if ((prototype[cPrototype] == '+') || (prototype[cPrototype] == '*')) {
			cPrototype-=2;
			continue;
		} else if (prototype[cPrototype] == '!') {
			// Extract the parameter list
			// NOTE: We usually expect string - value pairs, but we will not do a strict check
			if (parameterList == false) {
				parameterList	=	true;
				if ((cCode->type & SLC_STRING)	== 0)	return FALSE;
			}
			cCode	=	pl->next();
			cPrototype--;
			continue;
		} else return FALSE;

		return FALSE;
	}

	if ((cCode == NULL) && (prototype[cPrototype] == '\0'))	return TRUE;

	if (cCode == NULL) {
		if (prototype[cPrototype] == '+')	return TRUE;
		if (prototype[cPrototype] == '*')	return TRUE;
		if (prototype[cPrototype] == '!')	return TRUE;
		if (prototype[cPrototype+1] == '*') return TRUE;
		if (prototype[cPrototype+1] == '+') return TRUE;
		return FALSE;
	}
	return FALSE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFunctionPrototype
// Method				:	match(char *,CList<CCodeBlock *> *,int)
// Description			:	This function checks if the prototype is compatible to the given signature
// Return Value			:	TRUE if compatible, FALSE othervise
// Comments				:
int			CFunctionPrototype::match(const char *name,CList<CExpression *> *pl,int dt) {
	CExpression	*cCode;
	int			cPrototype;


	// Names should match exectly (still)
	if (strcmp(name,symbolName) != 0) return FALSE;

	// Screw the return type, the compiler will figure out how to convert it

	// Invalid prototype ?
	if (prototype[1] != '=') return FALSE;

	bool parameterList = false;
	for (cPrototype = 2,cCode = pl->first(); (cCode != NULL) && (prototype[cPrototype] != '\0'); cCode = pl->next(),cPrototype++) {
		if (prototype[cPrototype] == '.') {
			continue;
		} else if ((prototype[cPrototype] == 'f') || (prototype[cPrototype] == 'F')) {
			if (cCode->type & SLC_FLOAT) continue;
		} else if ((prototype[cPrototype] == 'v') || (prototype[cPrototype] == 'V')) {
			if (cCode->type & SLC_VECTOR) continue;
			if (cCode->type & SLC_FLOAT) continue;
		} else if ((prototype[cPrototype] == 'n') || (prototype[cPrototype] == 'N')) {
			if (cCode->type & SLC_VECTOR) continue;
			if (cCode->type & SLC_FLOAT) continue;
		} else if ((prototype[cPrototype] == 'p') || (prototype[cPrototype] == 'P')) {
			if (cCode->type & SLC_VECTOR) continue;
			if (cCode->type & SLC_FLOAT) continue;
		} else if ((prototype[cPrototype] == 'c') || (prototype[cPrototype] == 'C')) {
			if (cCode->type & SLC_VECTOR) continue;
			if (cCode->type & SLC_FLOAT) continue;
		} else if ((prototype[cPrototype] == 's') || (prototype[cPrototype] == 'S')) {
			if (cCode->type & SLC_STRING) continue;
		} else if ((prototype[cPrototype] == 'm') || (prototype[cPrototype] == 'M')) {
			if (cCode->type & SLC_MATRIX) continue;
			if (cCode->type & SLC_FLOAT) continue;
			if (cCode->type & SLC_VECTOR) continue;
		} else if ((prototype[cPrototype] == '+') || (prototype[cPrototype] == '*')) {
			cPrototype-=2;
			cCode = pl->prev();
			continue;
		} else if (prototype[cPrototype] == '!') {
			// Extract the parameter list
			// NOTE: We usually expect string - value pairs, but we will not do a strict check
			if (parameterList == false) {
				parameterList	=	true;
				if ((cCode->type & SLC_STRING)	== 0)	return FALSE;
			}
			cCode	=	pl->next();
			cPrototype--;
			continue;
		} else {
			return FALSE;
		}

		return FALSE;
	}

	if ((cCode == NULL) && (prototype[cPrototype] == '\0'))	return TRUE;

	if (cCode == NULL) {
		if (prototype[cPrototype] == '+')	return TRUE;
		if (prototype[cPrototype] == '*')	return TRUE;
		if (prototype[cPrototype] == '!')	return TRUE;
		if (prototype[cPrototype+1] == '*') return TRUE;
		if (prototype[cPrototype+1] == '+') return TRUE;
		return FALSE;
	}

	return FALSE;
}








///////////////////////////////////////////////////////////////////////
// Class				:	CShaderContext
// Method				:	CShaderContext(FILE *)
// Description			:	This method initializes the data structures
// Return Value			:
// Comments				:
CScriptContext::CScriptContext(int s) {
																	// Create a dummy "root" function that will contain
																	// all the global variables defined
	rootFunction			=	new CFunction("root",NULL);

	variables				=	new CList<CVariable *>;				// Pointers to all defined variables (except function parameters)
	temporaryRegisters		=	new CList<CVariable *>;				// Temporary variables used
	numTemporaryRegisters	=	0;
	numLabels				=	0;

	functionStack			=	new CList<CFunction *>;				// The function stack hierarchy
	runtimeFunctionStack	=	new CList<CFunction *>;				// The function stack hierarchy
	lastFunction			=	rootFunction;

	allocatedStrings		=	new CList<char *>;					// Pointers to the allocated strings by lex

	dsoPath					=	NULL;

	sourceFile				=	NULL;

	passNo					=	0;
	lineNo					=	1;									// The line no in the code
	statementLineNo			=	1;									// The starting line number for parsing
	compileError			=	0;									// The number of compiler CScriptContext::errors
	compileWarning			=	0;									// The number of compiler warnings
	settings				=	s;									// No settings

	shaderName				=	NULL;								// The name of the shader
	shaderType				=	0;

	builtinFunctions		=	new CList<CFunctionPrototype *>;	// List of built in functions
	globalVariables			=	new CList<CVariable *>;			// List of global variables

	desiredTypeStack		=	new CList<int>;
	desiredType				=	SLC_NONE;

	variableList			=	new CList<CVariable *>;
	actualParameterStack	=	new CList<CList<CExpression *> *>;
	actualParameters		=	new CList<CExpression *>;

	requiredShaderContext	=	SLC_GENERIC | SLC_SURFACE | SLC_LIGHT | SLC_DISPLACEMENT | SLC_TRANSFORMATION | SLC_IMAGER | SLC_VOLUME;

	// The built-in functions
	addBuiltInFunction("degrees","f=f",0);
	addBuiltInFunction("radians","f=f",0);
	addBuiltInFunction("sin","f=f",0);
	addBuiltInFunction("cos","f=f",0);
	addBuiltInFunction("tan","f=f",0);
	addBuiltInFunction("asin","f=f",0);
	addBuiltInFunction("acos","f=f",0);
	addBuiltInFunction("atan","f=f",0);
	addBuiltInFunction("atan","f=ff",0);
	addBuiltInFunction("pow","f=ff",0);
	addBuiltInFunction("exp","f=f",0);
	addBuiltInFunction("log","f=f",0);
	addBuiltInFunction("log","f=ff",0);
	addBuiltInFunction("sqrt","f=f",0);
	addBuiltInFunction("inversesqrt","f=f",0);
	addBuiltInFunction("abs","f=f",0);
	addBuiltInFunction("sign","f=f",0);
	addBuiltInFunction("floor","f=f",0);
	addBuiltInFunction("ceil","f=f",0);
	addBuiltInFunction("round","f=f",0);
	addBuiltInFunction("mod","f=ff",0);
	addBuiltInFunction("clamp","f=fff",0);
	addBuiltInFunction("clamp","v=vvv",0);
	addBuiltInFunction("clamp","n=nnn",0);
	addBuiltInFunction("clamp","p=ppp",0);
	addBuiltInFunction("clamp","c=ccc",0);
	addBuiltInFunction("mix","f=fff",0);
	addBuiltInFunction("mix","v=vvf",0);
	addBuiltInFunction("mix","n=nnf",0);
	addBuiltInFunction("mix","p=ppf",0);
	addBuiltInFunction("mix","c=ccf",0);
	addBuiltInFunction("mix","v=vvv",0);
	addBuiltInFunction("mix","n=nnn",0);
	addBuiltInFunction("mix","p=ppp",0);
	addBuiltInFunction("mix","c=ccc",0);
	addBuiltInFunction("min","f=f+",0);
	addBuiltInFunction("min","v=v+",0);
	addBuiltInFunction("max","f=f+",0);
	addBuiltInFunction("max","v=v+",0);
	addBuiltInFunction("step","f=ff",0);
	addBuiltInFunction("smoothstep","f=fff",0);
	addBuiltInFunction("filterstep","f=ff!",0);
	addBuiltInFunction("filterstep","f=fff!",0);
	addBuiltInFunction("Du","f=f",SLC_SURFACE | SLC_DISPLACEMENT | SLC_VOLUME,TRUE);
	addBuiltInFunction("Du","v=c",SLC_SURFACE | SLC_DISPLACEMENT | SLC_VOLUME,TRUE);
	addBuiltInFunction("Du","v=v",SLC_SURFACE | SLC_DISPLACEMENT | SLC_VOLUME,TRUE);
	addBuiltInFunction("Du","v=p",SLC_SURFACE | SLC_DISPLACEMENT | SLC_VOLUME,TRUE);
	addBuiltInFunction("Du","v=n",SLC_SURFACE | SLC_DISPLACEMENT | SLC_VOLUME,TRUE);
	addBuiltInFunction("Dv","f=f",SLC_SURFACE | SLC_DISPLACEMENT | SLC_VOLUME,TRUE);
	addBuiltInFunction("Dv","v=c",SLC_SURFACE | SLC_DISPLACEMENT | SLC_VOLUME,TRUE);
	addBuiltInFunction("Dv","v=v",SLC_SURFACE | SLC_DISPLACEMENT | SLC_VOLUME,TRUE);
	addBuiltInFunction("Dv","v=p",SLC_SURFACE | SLC_DISPLACEMENT | SLC_VOLUME,TRUE);
	addBuiltInFunction("Dv","v=n",SLC_SURFACE | SLC_DISPLACEMENT | SLC_VOLUME,TRUE);
	addBuiltInFunction("Deriv","f=ff",SLC_SURFACE | SLC_DISPLACEMENT | SLC_VOLUME,TRUE);
	addBuiltInFunction("Deriv","v=cf",SLC_SURFACE | SLC_DISPLACEMENT | SLC_VOLUME,TRUE);
	addBuiltInFunction("Deriv","v=vf",SLC_SURFACE | SLC_DISPLACEMENT | SLC_VOLUME,TRUE);
	addBuiltInFunction("Deriv","v=pf",SLC_SURFACE | SLC_DISPLACEMENT | SLC_VOLUME,TRUE);
	addBuiltInFunction("Deriv","v=nf",SLC_SURFACE | SLC_DISPLACEMENT | SLC_VOLUME,TRUE);
	addBuiltInFunction("random","f=",0,TRUE);
	addBuiltInFunction("random","v=",0,TRUE);
	addBuiltInFunction("random","n=",0,TRUE);
	addBuiltInFunction("random","p=",0,TRUE);
	addBuiltInFunction("random","c=",0,TRUE);
	addBuiltInFunction("urandom","f=",0);
	addBuiltInFunction("urandom","v=",0);
	addBuiltInFunction("urandom","n=",0);
	addBuiltInFunction("urandom","p=",0);
	addBuiltInFunction("urandom","c=",0);
	addBuiltInFunction("checkers","f=",0,TRUE);
	addBuiltInFunction("noise","f=f",0);
	addBuiltInFunction("noise","f=ff",0);
	addBuiltInFunction("noise","f=p",0);
	addBuiltInFunction("noise","f=pf",0);
	addBuiltInFunction("noise","c=f",0);
	addBuiltInFunction("noise","c=ff",0);
	addBuiltInFunction("noise","c=p",0);
	addBuiltInFunction("noise","c=pf",0);
	addBuiltInFunction("noise","v=f",0);
	addBuiltInFunction("noise","v=ff",0);
	addBuiltInFunction("noise","v=p",0);
	addBuiltInFunction("noise","v=pf",0);
	addBuiltInFunction("noise","n=f",0);
	addBuiltInFunction("noise","n=ff",0);
	addBuiltInFunction("noise","n=p",0);
	addBuiltInFunction("noise","n=pf",0);
	addBuiltInFunction("noise","p=f",0);
	addBuiltInFunction("noise","p=ff",0);
	addBuiltInFunction("noise","p=p",0);
	addBuiltInFunction("noise","p=pf",0);
	addBuiltInFunction("pnoise","f=ff",0);
	addBuiltInFunction("pnoise","f=ffff",0);
	addBuiltInFunction("pnoise","f=pp",0);
	addBuiltInFunction("pnoise","f=pfpf",0);
	addBuiltInFunction("pnoise","c=ff",0);
	addBuiltInFunction("pnoise","c=ffff",0);
	addBuiltInFunction("pnoise","c=pp",0);
	addBuiltInFunction("pnoise","c=pfpf",0);
	addBuiltInFunction("pnoise","v=ff",0);
	addBuiltInFunction("pnoise","v=ffff",0);
	addBuiltInFunction("pnoise","v=pp",0);
	addBuiltInFunction("pnoise","v=pfpf",0);
	addBuiltInFunction("pnoise","n=ff",0);
	addBuiltInFunction("pnoise","n=ffff",0);
	addBuiltInFunction("pnoise","n=pp",0);
	addBuiltInFunction("pnoise","n=pfpf",0);
	addBuiltInFunction("pnoise","p=ff",0);
	addBuiltInFunction("pnoise","p=ffff",0);
	addBuiltInFunction("pnoise","p=pp",0);
	addBuiltInFunction("pnoise","p=pfpf",0);
	addBuiltInFunction("cellnoise","f=f",0);
	addBuiltInFunction("cellnoise","f=ff",0);
	addBuiltInFunction("cellnoise","f=p",0);
	addBuiltInFunction("cellnoise","f=pf",0);
	addBuiltInFunction("cellnoise","c=f",0);
	addBuiltInFunction("cellnoise","c=ff",0);
	addBuiltInFunction("cellnoise","c=p",0);
	addBuiltInFunction("cellnoise","c=pf",0);
	addBuiltInFunction("cellnoise","v=f",0);
	addBuiltInFunction("cellnoise","v=ff",0);
	addBuiltInFunction("cellnoise","v=p",0);
	addBuiltInFunction("cellnoise","v=pf",0);
	addBuiltInFunction("cellnoise","n=f",0);
	addBuiltInFunction("cellnoise","n=ff",0);
	addBuiltInFunction("cellnoise","n=p",0);
	addBuiltInFunction("cellnoise","n=pf",0);
	addBuiltInFunction("cellnoise","p=f",0);
	addBuiltInFunction("cellnoise","p=ff",0);
	addBuiltInFunction("cellnoise","p=p",0);
	addBuiltInFunction("cellnoise","p=pf",0);
	addBuiltInFunction("xcomp","f=p",0);
	addBuiltInFunction("xcomp","f=v",0);
	addBuiltInFunction("xcomp","f=n",0);
	addBuiltInFunction("ycomp","f=p",0);
	addBuiltInFunction("ycomp","f=v",0);
	addBuiltInFunction("ycomp","f=n",0);
	addBuiltInFunction("zcomp","f=p",0);
	addBuiltInFunction("zcomp","f=v",0);
	addBuiltInFunction("zcomp","f=n",0);
	addBuiltInFunction("setxcomp","o=Vf",0);
	addBuiltInFunction("setxcomp","o=Pf",0);
	addBuiltInFunction("setxcomp","o=Nf",0);
	addBuiltInFunction("setycomp","o=Vf",0);
	addBuiltInFunction("setycomp","o=Pf",0);
	addBuiltInFunction("setycomp","o=Nf",0);
	addBuiltInFunction("setzcomp","o=Vf",0);
	addBuiltInFunction("setzcomp","o=Pf",0);
	addBuiltInFunction("setzcomp","o=Nf",0);
	addBuiltInFunction("comp","f=cf",0);
	addBuiltInFunction("comp","f=nf",0);
	addBuiltInFunction("comp","f=vf",0);
	addBuiltInFunction("comp","f=pf",0);
	addBuiltInFunction("comp","f=mff",0);
	addBuiltInFunction("setcomp","o=Cff",0);
	addBuiltInFunction("setcomp","o=Pff",0);
	addBuiltInFunction("setcomp","o=Nff",0);
	addBuiltInFunction("setcomp","o=Vff",0);
	addBuiltInFunction("setcomp","o=Mfff",0);
	addBuiltInFunction("length","f=v",0);
	addBuiltInFunction("normalize","v=v",0);
	addBuiltInFunction("normalize","p=p",0);
	addBuiltInFunction("normalize","c=c",0);
	addBuiltInFunction("normalize","n=n",0);
	addBuiltInFunction("distance","f=pp",0);
	addBuiltInFunction("ptlined","f=ppp",0);
	addBuiltInFunction("rotate","p=pfpp",0);
	addBuiltInFunction("area","f=p",0,TRUE);
	addBuiltInFunction("area","f=pS",0,TRUE);
	addBuiltInFunction("faceforward","v=vv",0);
	addBuiltInFunction("faceforward","v=vvv",0);
	addBuiltInFunction("reflect","v=vv",0);
	addBuiltInFunction("refract","v=vvf",0);
	addBuiltInFunction("fresnel","o=vvfFF",0);
	addBuiltInFunction("fresnel","o=vvfFFVV",0);
	addBuiltInFunction("ctransform","c=Sc",0);
	addBuiltInFunction("ctransform","c=SSc",0);
	addBuiltInFunction("transform","p=Sp",0);
	addBuiltInFunction("transform","p=SSp",0);
	addBuiltInFunction("transform","p=mp",0);
	addBuiltInFunction("transform","p=Smp",0);
	addBuiltInFunction("vtransform","v=Sv",0);
	addBuiltInFunction("vtransform","v=SSv",0);
	addBuiltInFunction("vtransform","v=mv",0);
	addBuiltInFunction("vtransform","v=Smv",0);
	addBuiltInFunction("ntransform","n=Sn",0);
	addBuiltInFunction("ntransform","n=SSn",0);
	addBuiltInFunction("ntransform","n=mn",0);
	addBuiltInFunction("ntransform","n=Smn",0);
	addBuiltInFunction("depth","f=p",0);
	addBuiltInFunction("calculatenormal","p=p",0);
	addBuiltInFunction("determinant","f=m",0);
	addBuiltInFunction("translate","m=mp",0);
	addBuiltInFunction("rotate","m=mfv",0);
	addBuiltInFunction("scale","m=mp",0);
	addBuiltInFunction("ambient","c=",SLC_SURFACE,TRUE);
	addBuiltInFunction("clearlighting","o=",SLC_SURFACE,0);
	addBuiltInFunction("diffuse","c=n",SLC_SURFACE,TRUE);
	addBuiltInFunction("diffuse","c=pnf",SLC_SURFACE,TRUE);
	addBuiltInFunction("specular","c=nvf",SLC_SURFACE,TRUE);
	addBuiltInFunction("specularbrdf","c=vnvf",SLC_SURFACE);
	addBuiltInFunction("phong","c=nvf",SLC_SURFACE,TRUE);
	addBuiltInFunction("trace","c=pv!",0,TRUE);	
	addBuiltInFunction("trace","f=pv",0,TRUE);	
	addBuiltInFunction("visibility","f=pp",0,TRUE);	
	addBuiltInFunction("transmission","c=pp!",0,TRUE);	
	addBuiltInFunction("raydepth","f=",0);	
	addBuiltInFunction("raylabel","s=",0);	
	addBuiltInFunction("rayinfo","f=s.",0);	
	addBuiltInFunction("colormap","c=sf!",0);	
	addBuiltInFunction("displacement","f=SF",0);
	addBuiltInFunction("displacement","f=SN",0);
	addBuiltInFunction("displacement","f=SP",0);
	addBuiltInFunction("displacement","f=SC",0);
	addBuiltInFunction("displacement","f=SS",0);
	addBuiltInFunction("displacement","f=SM",0);
	addBuiltInFunction("surface","f=SF",0);
	addBuiltInFunction("surface","f=SV",0);
	addBuiltInFunction("surface","f=SC",0);
	addBuiltInFunction("surface","f=SP",0);
	addBuiltInFunction("surface","f=SN",0);
	addBuiltInFunction("surface","f=SS",0);
	addBuiltInFunction("surface","f=SM",0);
	addBuiltInFunction("lightsource","f=SF",0,0);
	addBuiltInFunction("lightsource","f=SV",0,0);
	addBuiltInFunction("lightsource","f=SN",0,0);
	addBuiltInFunction("lightsource","f=SP",0,0);
	addBuiltInFunction("lightsource","f=SC",0,0);
	addBuiltInFunction("lightsource","f=SS",0,0);
	addBuiltInFunction("lightsource","f=SM",0,0);
	addBuiltInFunction("incident","f=SF",0);
	addBuiltInFunction("incident","f=SV",0);
	addBuiltInFunction("incident","f=SN",0);
	addBuiltInFunction("incident","f=SP",0);
	addBuiltInFunction("incident","f=SC",0);
	addBuiltInFunction("incident","f=SS",0);
	addBuiltInFunction("incident","f=SM",0);
	addBuiltInFunction("opposite","f=SF",0);
	addBuiltInFunction("opposite","f=SN",0);
	addBuiltInFunction("opposite","f=SV",0);
	addBuiltInFunction("opposite","f=SP",0);
	addBuiltInFunction("opposite","f=SC",0);
	addBuiltInFunction("opposite","f=SS",0);
	addBuiltInFunction("opposite","f=SM",0);
	addBuiltInFunction("attribute","f=SF",0);
	addBuiltInFunction("attribute","f=SV",0);
	addBuiltInFunction("attribute","f=SN",0);
	addBuiltInFunction("attribute","f=SP",0);
	addBuiltInFunction("attribute","f=SS",0);
	addBuiltInFunction("attribute","f=SC",0);
	addBuiltInFunction("attribute","f=SM",0);
	addBuiltInFunction("option","f=SF",0);
	addBuiltInFunction("option","f=SV",0);
	addBuiltInFunction("option","f=SC",0);
	addBuiltInFunction("option","f=SN",0);
	addBuiltInFunction("option","f=SP",0);
	addBuiltInFunction("option","f=SS",0);
	addBuiltInFunction("option","f=SM",0);
	addBuiltInFunction("rendererinfo","f=SF",0);
	addBuiltInFunction("rendererinfo","f=SC",0);
	addBuiltInFunction("rendererinfo","f=SN",0);
	addBuiltInFunction("rendererinfo","f=SP",0);
	addBuiltInFunction("rendererinfo","f=SV",0);
	addBuiltInFunction("rendererinfo","f=SS",0);
	addBuiltInFunction("rendererinfo","f=SM",0);
	addBuiltInFunction("textureinfo","f=SSF",0);
	addBuiltInFunction("textureinfo","f=SSC",0);
	addBuiltInFunction("textureinfo","f=SSN",0);
	addBuiltInFunction("textureinfo","f=SSP",0);
	addBuiltInFunction("textureinfo","f=SSV",0);
	addBuiltInFunction("textureinfo","f=SSS",0);
	addBuiltInFunction("textureinfo","f=SSM",0);
	addBuiltInFunction("shadername","s=",0);
	addBuiltInFunction("shadername","s=S",0);
	addBuiltInFunction("concat","s=ss*",0);
	addBuiltInFunction("match","f=ss",0);
	addBuiltInFunction("printf","o=s.*",0);
	addBuiltInFunction("format","s=s.*",0);
	addBuiltInFunction("texture","f=SFff!",0);
	addBuiltInFunction("texture","c=SFff!",0);
	addBuiltInFunction("texture","v=SFff!",0);
	addBuiltInFunction("texture","n=SFff!",0);
	addBuiltInFunction("texture","p=SFff!",0);
	addBuiltInFunction("texture","f=SF!",0,TRUE);
	addBuiltInFunction("texture","c=SF!",0,TRUE);
	addBuiltInFunction("texture","v=SF!",0,TRUE);
	addBuiltInFunction("texture","n=SF!",0,TRUE);
	addBuiltInFunction("texture","p=SF!",0,TRUE);
	addBuiltInFunction("texture","f=SFffffffff!",0);
	addBuiltInFunction("texture","c=SFffffffff!",0);
	addBuiltInFunction("environment","c=SFv!",0);
	addBuiltInFunction("environment","f=SFv!",0);
	addBuiltInFunction("shadow","f=SFp!",0);
	addBuiltInFunction("shadow","c=SFp!",0);
	addBuiltInFunction("photonmap","c=Spn!",0);
	addBuiltInFunction("photonmap","c=Sp!",0);
	addBuiltInFunction("indirectdiffuse","c=pnf!",0);
	addBuiltInFunction("occlusion","f=pnf!",0);
	addBuiltInFunction("bump","n=SFnvv!",0);
	addBuiltInFunction("bump","n=SFnvvff!",0);

	addBuiltInFunction("spline","f=fffff*",0);
	addBuiltInFunction("spline","c=fcccc*",0);
	addBuiltInFunction("spline","p=fpppp*",0);
	addBuiltInFunction("spline","n=fnnnn*",0);
	addBuiltInFunction("spline","v=fvvvv*",0);
	addBuiltInFunction("spline","f=Sfffff*",0);
	addBuiltInFunction("spline","c=Sfcccc*",0);
	addBuiltInFunction("spline","p=Sfpppp*",0);
	addBuiltInFunction("spline","n=Sfnnnn*",0);
	addBuiltInFunction("spline","v=Sfvvvv*",0);

	addBuiltInFunction("spline","f=fF",0);
	addBuiltInFunction("spline","c=fC",0);
	addBuiltInFunction("spline","p=fP",0);
	addBuiltInFunction("spline","n=fN",0);
	addBuiltInFunction("spline","v=fV",0);
	addBuiltInFunction("spline","f=SfF",0);
	addBuiltInFunction("spline","c=SfC",0);
	addBuiltInFunction("spline","p=SfP",0);
	addBuiltInFunction("spline","n=SfN",0);
	addBuiltInFunction("spline","v=SfV",0);

	addBuiltInFunction("bake3d","f=SSpn!",0);
	addBuiltInFunction("texture3d","f=Spn!",0);

	// The global variables
	addGlobalVariable("P",		SLC_VECTOR | SLC_VPOINT,	SLC_SURFACE | SLC_DISPLACEMENT | SLC_LIGHT | SLC_VOLUME | SLC_IMAGER);
	addGlobalVariable("Ps",		SLC_VECTOR | SLC_VPOINT,	SLC_SURFACE | SLC_LIGHT);
	addGlobalVariable("N",		SLC_VECTOR | SLC_VNORMAL,	SLC_SURFACE | SLC_DISPLACEMENT | SLC_VOLUME | SLC_LIGHT);
	addGlobalVariable("Ng",		SLC_VECTOR | SLC_VNORMAL,	SLC_SURFACE | SLC_DISPLACEMENT | SLC_VOLUME | SLC_LIGHT);
	addGlobalVariable("I",		SLC_VECTOR | SLC_VVECTOR,	SLC_SURFACE | SLC_DISPLACEMENT | SLC_VOLUME | SLC_LIGHT);
	addGlobalVariable("L",		SLC_VECTOR | SLC_VVECTOR,	SLC_SURFACE | SLC_LIGHT);
	addGlobalVariable("E",		SLC_VECTOR | SLC_VPOINT,	SLC_SURFACE | SLC_DISPLACEMENT | SLC_VOLUME | SLC_LIGHT);
	addGlobalVariable("dPdu",	SLC_VECTOR | SLC_VVECTOR,	SLC_SURFACE | SLC_DISPLACEMENT | SLC_VOLUME | SLC_LIGHT);
	addGlobalVariable("dPdv",	SLC_VECTOR | SLC_VVECTOR,	SLC_SURFACE | SLC_DISPLACEMENT | SLC_VOLUME | SLC_LIGHT);
	addGlobalVariable("Os",		SLC_VECTOR | SLC_VCOLOR,	SLC_SURFACE | SLC_DISPLACEMENT);
	addGlobalVariable("Oi",		SLC_VECTOR | SLC_VCOLOR,	SLC_SURFACE | SLC_VOLUME);
	addGlobalVariable("Cs",		SLC_VECTOR | SLC_VCOLOR,	SLC_SURFACE | SLC_DISPLACEMENT);
	addGlobalVariable("Ci",		SLC_VECTOR | SLC_VCOLOR,	SLC_SURFACE | SLC_VOLUME);
	addGlobalVariable("Cl",		SLC_VECTOR | SLC_VCOLOR,	SLC_SURFACE | SLC_LIGHT);
	addGlobalVariable("Ol",		SLC_VECTOR | SLC_VCOLOR,	SLC_SURFACE | SLC_LIGHT);
	addGlobalVariable("u",		SLC_FLOAT,					SLC_SURFACE | SLC_DISPLACEMENT | SLC_LIGHT | SLC_VOLUME);
	addGlobalVariable("v",		SLC_FLOAT,					SLC_SURFACE | SLC_DISPLACEMENT | SLC_LIGHT | SLC_VOLUME);
	addGlobalVariable("du",		SLC_FLOAT,					SLC_SURFACE | SLC_DISPLACEMENT | SLC_LIGHT | SLC_VOLUME);
	addGlobalVariable("dv",		SLC_FLOAT,					SLC_SURFACE | SLC_DISPLACEMENT | SLC_LIGHT | SLC_VOLUME);
	addGlobalVariable("s",		SLC_FLOAT,					SLC_SURFACE | SLC_DISPLACEMENT | SLC_LIGHT | SLC_VOLUME);
	addGlobalVariable("t",		SLC_FLOAT,					SLC_SURFACE | SLC_DISPLACEMENT | SLC_LIGHT | SLC_VOLUME);
	addGlobalVariable("ncomps",	SLC_FLOAT,					SLC_SURFACE | SLC_DISPLACEMENT | SLC_LIGHT | SLC_VOLUME);
	addGlobalVariable("time",	SLC_FLOAT,					SLC_SURFACE | SLC_DISPLACEMENT | SLC_LIGHT | SLC_VOLUME);	// FIXME should be uniform
	addGlobalVariable("dtime",	SLC_FLOAT | SLC_UNIFORM,	SLC_SURFACE | SLC_DISPLACEMENT | SLC_LIGHT | SLC_VOLUME);
	addGlobalVariable("dPdtime",	SLC_VECTOR | SLC_VVECTOR,	SLC_SURFACE | SLC_DISPLACEMENT | SLC_LIGHT | SLC_VOLUME);
	addGlobalVariable("alpha",	SLC_FLOAT,					SLC_SURFACE | SLC_DISPLACEMENT | SLC_LIGHT | SLC_VOLUME);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CScriptContext
// Method				:	~CScriptContext()
// Description			:	Destroy Destroy Destroy
// Return Value			:
// Comments				:		
CScriptContext::~CScriptContext() {
	char		*str;

	delete		rootFunction;

	delete		variables;							// Delete the variables
	temporaryRegisters->destroy();

	delete functionStack;							// Delete the function stack
	delete runtimeFunctionStack;					// Delete the function stack

	while((str = allocatedStrings->pop()) != NULL)	// Delete the allocated stings
		free(str);
	delete allocatedStrings;
					
	if (shaderName != NULL) free(shaderName);

	delete variableList;

	delete actualParameterStack;

	delete actualParameters;

	builtinFunctions->destroy();

	globalVariables->destroy();

	delete desiredTypeStack;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CScriptContext
// Method				:	addBuiltInFunction
// Description			:	Add a built in function
// Return Value			:
// Comments				:		
CFunctionPrototype	*CScriptContext::addBuiltInFunction(const char *name,const char *prototype,int scope,int nonuniform) {
	CFunctionPrototype	*cFun	=	new CFunctionPrototype(name,prototype,scope,nonuniform);

	builtinFunctions->push(cFun);

	return cFun;
}



///////////////////////////////////////////////////////////////////////
// Class				:	CScriptContext
// Method				:	addGlobalVariable
// Description			:	Add a built in function
// Return Value			:
// Comments				:		
void	CScriptContext::addGlobalVariable(const char *name,int type,int scope) {
	CVariable			*cVar	=	lastFunction->addVariable(name,type | SLC_GLOBAL,1);

	cVar->cName					=	strdup(name);
	
	variables->push(cVar);

	define(cVar);
}
///////////////////////////////////////////////////////////////////////
// Class				:	CScriptContext
// Method				:	getFunction(char *,CList<CCodeBlock *>)
// Description			:	Search for a function in the current context
// Return Value			:	NULL if the function is not found, pointer to the function otherwise
// Comments				:
CFunction	*CScriptContext::getFunction(const char *fn,CList<CExpression *> *params) {
	CFunction	*f	=	lastFunction->getFunction(fn,params,desiredType);

	if (f != NULL) printDefine(f);

	return f;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CScriptContext
// Method				:	getVariable(char *,int,int);
// Description			:	Search for a variable in the current context
// Return Value			:	NULL if the variable is not found, pointer to the variable otherwise
// Comments				:
CVariable	*CScriptContext::getVariable(const char *vn) {
	CVariable	*v	=	lastFunction->getVariable(vn);

	if (v == NULL) {
		int			i		=	globalVariables->numItems;
		CVariable	**vars	=	globalVariables->array;

		for (;i>0;i--,vars++) {
			CVariable	*cVar	=	*vars;

			if (strcmp(cVar->symbolName,vn) == 0) {
				v	=	cVar;
				break;
			}
		}
	}

	if (v != NULL) printDefine(v);
	else {
		v = rootFunction->getVariable(vn);
	}

	return v;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CScriptContext
// Method				:	define(CSymbol *)
// Description			:	This method fills in the information about the definition position of the variable
// Return Value			:	
// Comments				:
void		CScriptContext::define(CSymbol *s) {
	if (sourceFile != NULL) {
		if (sourceFile != NULL)
			s->defFileName	=	strdup(sourceFile);
		else
			s->defFileName	=	NULL;

		s->defLineNo	=	lineNo-1;
	} else {
		s->defFileName	=	strdup("global");
		s->defLineNo	=	0;
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CScriptContext
// Method				:	printDefine(CSymbol *)
// Description			:	This method prints the information about which variable is used to resolve this symbol
// Return Value			:
// Comments				:
void		CScriptContext::printDefine(CSymbol *s) {
	if (settings & COMPILER_SUPPRESS_DEFINITIONS) return ;

	if (s->defFileName != NULL)
		printf("%s \t(%s(%d)) \t-> %d in %s\n",s->symbolName,sourceFile,lineNo-1,s->defLineNo,s->defFileName);
	else 
		printf("%s \t(%s(%d)) \t-> ??? in ???\n",s->symbolName,sourceFile,lineNo-1);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CScriptContext
// Method				:	newParameter(char *)
// Description			:	This function creates a new parameter
// Return Value			:	NULL if the parameter already defined
// Comments				:
CParameter		*CScriptContext::newParameter(const char *name,int type,int multiplicity) {
	CParameter	*cParameter	=	lastFunction->addParameter(name,type,multiplicity);

	if (type & SLC_PARAMETER) {
		// Save the initial type of the parameter and make it a uniform
		cParameter->savedType	=	cParameter->type;
		cParameter->type		|=	SLC_UNIFORM;
	}

	return cParameter;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CScriptContext
// Method				:	newVariable(char *)
// Description			:	This function creates a new variable
// Return Value			:	NULL if the variable already exists
// Comments				:
CVariable		*CScriptContext::newVariable(const char *name,int type,int multiplicity) {
	CVariable	*cVariable	=	lastFunction->addVariable(name,type,multiplicity);

	return cVariable;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CScriptContext
// Method				:	newFunction(char *)
// Description			:	This function creates a new function :)
// Return Value			:	pointer to the new function (this method never fails)
// Comments				:
CFunction		*CScriptContext::newFunction(const char *name) {
	CFunction	*cFunction	=	new CFunction(name,lastFunction);

	if ( (strcmp(name,constantBlockName) != 0) && (strcmp(name,constantLoopName) != 0)) {
		define(cFunction);
	}

	lastFunction->functions->push(cFunction);

	functionStack->push(lastFunction);
	lastFunction	=	cFunction;

	return cFunction;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CScriptContext
// Method				:	addVariable
// Description			:	Add a new variable to the system
// Return Value			:	
// Comments				:
void	CScriptContext::addVariable(CVariable *cVariable) {
	CVariable	*tVar;
	char		tmp[512];
	int			count		=	0;
	int			collusion	=	TRUE;

	if (cVariable->type & SLC_PARAMETER) {
		variables->push(cVariable);
	} else {
		if (cVariable->cName != NULL)	return;

		sprintf(tmp,cVariable->symbolName);

		while (collusion == TRUE) {
			collusion	=	FALSE;

			for (tVar=variables->first();tVar != NULL;tVar=variables->next()) {
				if (tVar->cName != NULL) {
					if (strcmp(tmp,tVar->cName) == 0) {
						count++;
						sprintf(tmp,"%s_%d",cVariable->symbolName,count);
						collusion	=	TRUE;
						break;
					}
				} else {
					if (strcmp(tmp,tVar->symbolName) == 0) {
						count++;
						sprintf(tmp,"%s_%d",cVariable->symbolName,count);
						collusion	=	TRUE;
						break;
					}
				}

			}
		}

		cVariable->cName	=	strdup(tmp);

		if (passNo == 0)
			variables->push(cVariable);
	}
}



///////////////////////////////////////////////////////////////////////
// Class				:	CScriptContext
// Method				:	newLabel
// Description			:	This function creates a new function :)
// Return Value			:	pointer to the new function (this method never fails)
// Comments				:
void			CScriptContext::newLabel(char *dest) {
	numLabels++;

	sprintf(dest,"#!Label%d",numLabels);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CScriptContext
// Method				:	popFunction()
// Description			:	This method is used to pop a function from the function stack
// Return Value			:
// Comments				:
CFunction		*CScriptContext::popFunction() {
	CFunction	*cFunction	=	lastFunction;

	lastFunction	=	functionStack->pop();

	return cFunction;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CScriptContext
// Method				:	uniformParameters
// Description			:	Make all the parameters uniform
// Return Value			:
// Comments				:
void			CScriptContext::uniformParameters() {
	CParameter	**parameters	=	shaderFunction->parameters->array;
	int			numParameters	=	shaderFunction->parameters->numItems;
	CParameter	*cParameter;

	for (;numParameters>0;numParameters--) {
		cParameter			=	*parameters++;

		if (cParameter->type & SLC_PARAMETER) {	
			cParameter->type	|=	SLC_UNIFORM;
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CScriptContext
// Method				:	restoreParameters
// Description			:	Restore the parameters to their original type
// Return Value			:
// Comments				:
void			CScriptContext::restoreParameters() {
	CParameter	**parameters	=	shaderFunction->parameters->array;
	int			numParameters	=	shaderFunction->parameters->numItems;
	CParameter	*cParameter;

	for (;numParameters>0;numParameters--) {
		cParameter			=	*parameters++;

		if (cParameter->type & SLC_PARAMETER) {	
			cParameter->type	=	cParameter->savedType;
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CScriptContext
// Method				:	generateCode(FILE *out)
// Description			:	This method prints the code into a file
// Return Value			:
// Comments				:
void			CScriptContext::generateCode(const char *o) {
	CParameter			*cParameter;
	CVariable			*cVariable;
	FILE				*out	=	NULL;

	if (!(requiredShaderContext & shaderType)) {
		CScriptContext::error("The shader uses some functions or constructs that are not defined for its type\n");
	}

	if (compileError != 0)
		return;

	passNo	=	0;
	// Code generation
	runtimeFunctionStack->push(shaderFunction);
	if (shaderFunction->initExpression != NULL)	shaderFunction->initExpression->getCode(out,NULL);
	if (shaderFunction->code != NULL)			shaderFunction->code->getCode(out,NULL);

	if (compileError != 0)
		return;

	out		=	fopen(o,"w");

	if (out == NULL) {
		sdr->error("Failed to open \"%s\"\n",o);
		return;
	}

	fprintf(out,"#!version %d.%d.%d\n",VERSION_RELEASE,VERSION_BETA,VERSION_ALPHA);

	switch(shaderType) {
		case SLC_SURFACE:
			fprintf(out,"surface\n");
			break;
		case SLC_LIGHT:
			fprintf(out,"light\n");
			break;
		case SLC_DISPLACEMENT:
			fprintf(out,"displacement\n");
			break;
		case SLC_VOLUME:
			fprintf(out,"volume\n");
			break;
		case SLC_TRANSFORMATION:
			fprintf(out,"transformation\n");
			break;
		case SLC_IMAGER:
			fprintf(out,"imager\n");
			break;
		default:
			fprintf(out,"generic\n");
			break;
	}

	// Print the parameters
	fprintf(out,"#!parameters:\n");
	for (cVariable = variables->first(); cVariable != NULL; cVariable = variables->next()) {
		if (cVariable->type & SLC_PARAMETER) {
			cParameter = (CParameter *) cVariable;

			// Write the output status
			if (cParameter->type & SLC_OUTPUT)
				fprintf(out,"output\t");

			// Write the container class
			if (cParameter->type & SLC_UNIFORM) {
				fprintf(out,"uniform\t");
			} else {
				fprintf(out,"varying\t");
			}
			
			// Write the parameter type
			if (cParameter->type & SLC_FLOAT)
				fprintf(out,"float\t");
			else if (cParameter->type & SLC_VECTOR) {
				if (cParameter->type & SLC_VPOINT)
					fprintf(out,"point\t");	
				else if (cParameter->type & SLC_VVECTOR)
					fprintf(out,"vector\t");	
				else if (cParameter->type & SLC_VNORMAL)
					fprintf(out,"normal\t");	
				else if (cParameter->type & SLC_VCOLOR)
					fprintf(out,"color\t");	
				else fprintf(out,"vector\t");
			} else if (cParameter->type & SLC_STRING)
				fprintf(out,"string\t");
			else if (cParameter->type & SLC_MATRIX)
				fprintf(out,"matrix\t");

			fprintf(out,"%s",cParameter->symbolName);

			if (cParameter->type & SLC_ARRAY) {
				fprintf(out,"[%d]",cParameter->numItems);
			}

			if (cParameter->defaultValue != NULL) {
				fprintf(out,"\t=\t%s\n",cParameter->defaultValue);
			} else {
					fprintf(out,"\n");
			}
		}
	}


	// Print the variables
	fprintf(out,"#!variables:\n");
	for (cVariable = variables->first(); cVariable != NULL; cVariable = variables->next()) {
		if ((!(cVariable->type & SLC_PARAMETER)) && (!(cVariable->type & SLC_GLOBAL))) {

			if (cVariable->type & SLC_NONE)	continue;

			// Write the container class
			if (cVariable->type & SLC_UNIFORM) {
				fprintf(out,"uniform\t");
			} else {
				fprintf(out,"varying\t");
			}
	
			// Write the type
			if (cVariable->type & SLC_FLOAT)
				fprintf(out,"float\t");
			else if (cVariable->type & SLC_VECTOR) {
				fprintf(out,"vector\t");
			} else if (cVariable->type & SLC_STRING)
				fprintf(out,"string\t");
			else if (cVariable->type & SLC_MATRIX)
				fprintf(out,"matrix\t");

			fprintf(out,"%s",cVariable->cName);

			if (cVariable->type & SLC_ARRAY) {
				fprintf(out,"[%d]\n",cVariable->numItems);
			} else fprintf(out,"\n");
		}
	}


	passNo	=	1;

	uniformParameters();
	fprintf(out,"#!Init:\n");
	if (shaderFunction->initExpression != NULL)	shaderFunction->initExpression->getCode(out,NULL);
	fprintf(out,"%s\n",opcodeReturn);
	restoreParameters();

	fprintf(out,"#!Code:\n");
	if (shaderFunction->code != NULL)	shaderFunction->code->getCode(out,NULL);
	fprintf(out,"%s\n",opcodeReturn);

	fclose(out);
}


///////////////////////////////////////////////////////////////////////
// Function				:	dsoEnumerateCallback
// Description			:	This function will be called for each module
// Return Value			:
// Comments				:
static	int	dsoEnumerateCallback(const char *file,void *ud) {
	void	*module		=	osLoadModule(file);

	if (module != NULL) {
		int				i;
		char			*name			=	(char *) ud;
		SHADEOP_SPEC	*shadeops;

		{
			char	tmp[OS_MAX_PATH_LENGTH];

			sprintf(tmp,"%s_shadeops",name);

			shadeops	=	(SHADEOP_SPEC *)	osResolve(module,tmp);
		}

		if (shadeops != NULL) {
			for (i=0;;i++) {
				char	*dsoName,*dsoPrototype;

				if (strcmp(shadeops[i].definition,"") == 0)	break;

				if (dsoParse(shadeops[i].definition,dsoName,dsoPrototype) == TRUE) {
					CFunctionPrototype	*cFun	=	sdr->addBuiltInFunction(name,dsoPrototype,0);

					cFun->dso					=	TRUE;


					free(dsoName);
					free(dsoPrototype);
				}
			}
		}

		osUnloadModule(module);
	}

	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CScriptContext
// Method				:	enumerateDso
// Description			:	Enumerate a particular DSO
// Return Value			:
// Comments				:
void		CScriptContext::enumerateDso(const char *name) {
	char		searchPath[OS_MAX_PATH_LENGTH];
	TSearchpath	*inPath;

	// Go over the directories
	for (inPath=dsoPath;inPath!=NULL;inPath=inPath->next) {
		sprintf(searchPath,"%s/*.%s",inPath->directory,osModuleExtension);
		osEnumerate(searchPath,dsoEnumerateCallback,(void *) name);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CScriptContext
// Method				:	CScriptContext::error(char *,...)
// Description			:	Print an CScriptContext::error message and terminate
// Return Value			:
// Comments				:
void		CScriptContext::error(const char *mes,...) {
	char	tmp[1024];
	va_list	args;

	compileError++;

	if (CScriptContext::settings & COMPILER_SUPPRESS_ERRORS) return;

	sprintf(tmp,"%s(%d) Error: %s",sourceFile,lineNo,mes);

	va_start(args,mes);
	vprintf(tmp,args);
	va_end(args);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CScriptContext
// Method				:	warning(char *,...)
// Description			:	Print a warning message
// Return Value			:	
// Comments				:
void		CScriptContext::warning(const char *mes,...) {
	char	tmp[1024];
	va_list	args;

	compileWarning++;

	if (settings & COMPILER_SUPPRESS_WARNINGS) return;

	sprintf(tmp,"%s(%d) Warning: %s",sourceFile,lineNo,mes);

	va_start(args,mes);
	vprintf(tmp,args);
	va_end(args);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CScriptContext
// Method				:	fatal(char *,...)
// Description			:	Unrecoverable error
// Return Value			:	
// Comments				:
void		CScriptContext::fatal(const char *mes,...) {
	char	tmp[1024];
	va_list	args;

	sprintf(tmp,"%s(%d) Error: %s",sourceFile,lineNo,mes);

	va_start(args,mes);
	vprintf(tmp,args);
	va_end(args);

	exit(-1);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CScriptContext
// Method				:	fatalbailout()
// Description			:	Unrecoverable error
// Return Value			:	
// Comments				:
void		CScriptContext::fatalbailout() {
	fatal("Confused by earlier errors, bailing out\n");
}

///////////////////////////////////////////////////////////////////////
// Class				:	CScriptContext
// Method				:	desire
// Description			:	Expect a particular variable type
// Return Value			:	
// Comments				:
void		CScriptContext::desire(int type) {
	desiredTypeStack->push(desiredType);
	//desiredType	=	type & (~SLC_EXTERN);
	desiredType	=	type;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CScriptContext
// Method				:	undesire
// Description			:	Return to the previous desired type
// Return Value			:	
// Comments				:
int			CScriptContext::undesire() {
	if (desiredTypeStack->numItems == 0) {
		fatal("Type stack underrun\n");
	}

	desiredType	=	desiredTypeStack->pop();
	return desiredType;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CScriptContext
// Method				:	desired
// Description			:	Get the expected type
// Return Value			:	
// Comments				:
int			CScriptContext::desired() {
	return desiredType;
}



///////////////////////////////////////////////////////////////////////
// Class				:	CScriptContext
// Method				:	lockRegister
// Description			:	Allocate a temporary register
// Return Value			:	
// Comments				:
CVariable			*CScriptContext::lockRegister(int type,int numItems) {
	CVariable	*cVar;
	char		name[128];

	type	&=	(SLC_TYPE_MASK | SLC_UNIFORM);

	for (cVar=temporaryRegisters->first();cVar!=NULL;cVar=temporaryRegisters->next()) {
		if (cVar->type & SLC_LOCKED) continue;

		if ((cVar->type & type & SLC_TYPE_MASK & (~SLC_NONE)) != 0) {
			if (cVar->type & SLC_UNIFORM) {
				if (!(type & SLC_UNIFORM))	continue;
			} else {
				if (type & SLC_UNIFORM)	continue;
			}

			if (cVar->numItems != numItems)	continue;

			cVar->type |= SLC_LOCKED;
			return cVar;
		}
	}


	sprintf(name,"temporary_%d",numTemporaryRegisters++);
	cVar		=	new CVariable(name,type,numItems);
	cVar->cName	=	strdup(name);

	temporaryRegisters->push(cVar);
	variables->push(cVar);

	cVar->type	|=	SLC_LOCKED;
	return	cVar;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CScriptContext
// Method				:	releaseRegister
// Description			:	Release a previously allocated register
// Return Value			:	
// Comments				:
void				CScriptContext::releaseRegister(CVariable *cVar) {
	cVar->type	^=	SLC_LOCKED;
}

