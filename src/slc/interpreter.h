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
//  File				:	interpreter.h
//  Classes				:	CRegister, CNode, CShader
//  Description			:	The main interpreter class that defines necessary shader types
//
////////////////////////////////////////////////////////////////////////
#ifndef INTERPRETER_H
#define INTERPRETER_H


////////////////////////////////////////////////////////////////
// Type constants, all the types are kept in an integer
// where the specific bit positions determine the type and scope of the type
const	int		SLC_FLOAT				=	1 << 0;		// Float
const	int		SLC_VECTOR				=	1 << 1;		// A vector of 3 floats
const	int		SLC_STRING				=	1 << 2;		// String
const	int		SLC_MATRIX				=	1 << 3;		// Matrix
const	int		SLC_NONE				=	1 << 4;		// No type
const	int		SLC_BOOLEAN				=	1 << 5;		// Boolean (integer)

const	int		SLC_RDONLY				=	1 << 6;		// Read only variable

const	int		SLC_VNORMAL				=	1 << 7;		// Vector is a normal
const	int		SLC_VVECTOR				=	1 << 8;		// Vector is a vector
const	int		SLC_VPOINT				=	1 << 9;		// Vector is a point
const	int		SLC_VCOLOR				=	1 << 10;	// Vector is a color

const	int		SLC_ARRAY				=	1 << 11;	// Variable is an array
const	int		SLC_UNIFORM				=	1 << 13;	// Variable is uniform
const	int		SLC_VARYING				=	1 << 14;	// Variable is varying

class	CShadingContext;


///////////////////////////////////////////////////////////////////////
// Class				:	CRegister
// Description			:	Holds a register
// Comments				:
// Date last edited		:	9/16/2006
class	CRegister {
public:
		int					type;					// Type of the register
		void				*storage;				// Points to the storage area (always 16 bytes aligned)
		CRegister			*next;					// Points to the next register in the free registers list
};

///////////////////////////////////////////////////////////////////////
// Class				:	CNode
// Description			:	This class represents an aritmetic node
// Comments				:
// Date last edited		:	9/16/2006
class CNode {
public:
							CNode(FILE *in=NULL);
		virtual				~CNode();

		virtual	void		save(FILE *out)							=	NULL;
		virtual	CRegister	*compute(CShadingContext *context)		=	NULL;


		int					type;				// The type of the node
		char				*name;				// Name of the node (may be NULL)
		CNode				*next;				// Next node to be executed (only makes sense for root nodes)
};






///////////////////////////////////////////////////////////////////////
// Class				:	CShader
// Description			:	This class holds a shader
// Comments				:
// Date last edited		:	9/16/2006
class CShader {
public:
							CShader(FILE *in=NULL);
		virtual				~CShader();

		virtual	void		save(FILE *out)	=	NULL;

		int					type;
		CNode				*inputs;				// The list of input nodes
		CNode				*outputs;				// The list of output nodes
};


#endif
