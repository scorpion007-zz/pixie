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
//  File				:	nodes.h
//  Classes				:	Various aritmetic tree nodes
//  Description			:	-
//
////////////////////////////////////////////////////////////////////////
#ifndef NODES_H
#define NODES_H

#include "interpreter.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CAdd
// Description			:	This is an addition node
// Comments				:
// Date last edited		:	9/16/2006
class	CAdd : public CNode {
public:
					CAdd(CNode *input1,CNode *input2);
					~CAdd();

	void			save(FILE *out);
	CRegister		*compute(CShadingContext *context);

	CNode			*in1,*in2;
};
#endif





