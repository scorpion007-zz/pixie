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
//  File				:	slcode.h
//  Classes				:	-
//  Description			:	This file defines the entry point for all the
//							shading language functions/opcodes
//
////////////////////////////////////////////////////////////////////////
#ifndef SLCODE_H
#define SLCODE_H

#define	DEFOPCODE(name,text,nargs,expr_pre,expr,expr_update,expr_post,params)			OPCODE_##name ,

#define	DEFSHORTOPCODE(name,text,nargs,expr_pre,expr,expr_update,expr_post,params)		OPCODE_##name ,

#define	DEFLINKOPCODE(name,text,nargs)													OPCODE_##name ,

#define	DEFLINKFUNC(name,text,prototype,par)											FUNCTION_##name ,

#define	DEFFUNC(name,text,prototype,expre_pre,expr,expr_update,expr_post,par)			FUNCTION_##name ,

#define	DEFLIGHTFUNC(name,text,prototype,expre_pre,expr,expr_update,expr_post,par)		FUNCTION_##name ,

#define	DEFSHORTFUNC(name,text,prototype,expre_pre,expr,expr_update,expr_post,par)		FUNCTION_##name ,

// Create an enumerated type of all the opcodes and functions
typedef	enum	{
#include "scriptOpcodes.h"
#include "scriptFunctions.h"
OPCODE_NOP
} ESlCode;


#undef DEFOPCODE
#undef DEFSHORTOPCODE
#undef DEFFUNC
#undef DEFLIGHTFUNC
#undef DEFSHORTFUNC
#undef DEFLINKOPCODE
#undef DEFLINKFUNC


#endif

