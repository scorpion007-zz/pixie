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
//  File				:	opcode.h
//  Classes				:	-
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef OPCODE_H
#define OPCODE_H

////////////////////////////////////////////////////////////////////////
// The opcode declaration
class	COpcode {
public:
						COpcode();
		virtual			~COpcode();
		
		virtual	void	exec(int num,void **variables)	=	0;
};

// At the compile time, every statement is compiled into a dataflow
// tree. Each node of this tree is a COpcode. The compiler generates
// the code that reshuffles the variables. The interpreter executes
// the reshuffles the code and executes the commands






#endif




