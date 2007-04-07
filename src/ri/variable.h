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
//  File				:	variable.h
//  Classes				:	CVariable
//  Description			:	This class holds variable information
//
////////////////////////////////////////////////////////////////////////
#ifndef VARIABLE_H
#define VARIABLE_H

#include "common/global.h"		// The global header file
#include "ri_config.h"
#include "rendererc.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CVariable
// Description			:	This class holds information about a variable
// Comments				:	FIXME: Maximum length of a variable's name is 63 characters
class CVariable {
public:
	char				name[VARIABLE_NAME_LENGTH];	// Name as it is referenced
	
	int					numItems;					// Number of items if this is an array
	int					numFloats;					// Number of floats per variable (1 for float, 3 for color, 16 for matrix)
	int					entry;						// The global variable number as it's referenced from a grid (-1 if not global)
	int					usageMarker;				// The usage or flag
	
	void				*defaultValue;				// Points to the memory area that holds the default value for the variable
	CVariable			*next;						// Linked list next (used to maintain shader parameter lists)

	int					accessor;					// Which entry in the locals array are we?
	
	EVariableType		type;						// Type
	EVariableClass		container;					// Container type
	EVariableStorage	storage;					// If the variable is global, parameter or mutable parameter
};


int	parseVariable(CVariable *,const char *,const char *);

#endif

