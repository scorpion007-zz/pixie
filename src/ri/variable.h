//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright © 1999 - 2003, Okan Arikan
//
// Contact: okan@cs.utexas.edu
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
//  File				:	variable.h
//  Classes				:	CVariable
//  Description			:	This class holds variable information
//
////////////////////////////////////////////////////////////////////////
#ifndef VARIABLE_H
#define VARIABLE_H

#include "common/global.h"		// The global header file
#include "rendererc.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CVariable
// Description			:	This class holds information about a variable
// Comments				:	FIXME: Maximum length of a variable's name is 63 characters
class CVariable {
public:
	char				name[64];		// Name as it is referenced
	EVariableType		type;			// Type
	EVariableClass		container;		// Container type
	int					numItems;		// Number of items if this is an array
	int					numFloats;		// Number of floats per variable (1 for float, 3 for color, 16 for matrix)
	int					entry;			// The global variable number as it's referenced from a grid (-1 if not global)
	int					usageMarker;	// The usage or flag
	EVariableStorage	storage;		// If the variable is global, parameter or mutable parameter
	void				*defaultValue;	// Points to the memory area that holds the default value for the variable
	int					accessor;		// Which entry in the locals array are we?
	CVariable			*next;			// Linked list next (used to maintain shader parameter lists)
};


int	parseVariable(CVariable *,const char *,const char *);

#endif
