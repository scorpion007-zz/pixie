//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright © 1999 - 2003, Okan Arikan
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
//  File				:	sdr.h
//  Classes				:	
//  Description			:	Global functions for shader parsing
//
////////////////////////////////////////////////////////////////////////
#ifndef SDR_H
#define SDR_H

#include "interpreter.h"


///////////////////////////////////////////////////////////////////////
// Class				:	CVariable
// Description			:	Holds a variable
// Comments				:
// Date last edited		:	9/16/2006
class	CVariable {
public:
				int			type;			// Type of the variable
				char		name[512];		// Name of the variable
				CVariable	*next;			// Next variable in the same scope
				CNode		*node;			// The node corresponding to this variable
};

///////////////////////////////////////////////////////////////////////
// Class				:	CFunction
// Description			:	Holds a function
// Comments				:
// Date last edited		:	9/16/2006
class	CScope {
public:
				CVariable	*variables;		// The list of variables defined in this scope
				CScope		*parent;		// The parent scope
				CNode		*nodes;			// List of nodes for this scope (the code)
};

///////////////////////////////////////////////////////////////////////
// Class				:	CFunction
// Description			:	Holds a function
// Comments				:
// Date last edited		:	9/16/2006
class	CFunction : public CScope {
public:
				int			type;			// Type of the function
				char		name[512];		// Name of the function
				CVariable	*inputs;		// List of input variables
};







////////////////////////////////////////////////////////////////////////////
// Some global functions for the shader compiler
extern	int		type;
extern	int		lineNo;
extern	char	fileName[512];
extern	CScope	*scope;
extern	CShader	*shader;






////////////////////////////////////////////////////////////////////////////
// Some functions for the shader compiler
void		beginFunction(const char *name,int type);		// Begin a function
void		endFunction();									// End a function
void		beginScope();									// Begin a scope
void		endScope();										// End a scope
CVariable	*addVariable(const char *name,int type,int numItems=1);		// Add a variable to the current scope
CVariable	*findVariable(const char *name);				// Find a variable
void		addNode(CNode *node);							// Add a node to the current scope







#endif