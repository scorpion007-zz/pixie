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
//  File				:	error.h
//  Classes				:	-
//  Description			:	The error display functions
//
////////////////////////////////////////////////////////////////////////
#ifndef ERROR_H
#define ERROR_H

#include "common/global.h"		// The global header file

// Error codes for the error function (Used by sfError)
typedef enum {
	CODE_NOERROR,
	CODE_NOMEM,
	CODE_SYSTEM,
	CODE_NOFILE,
	CODE_BADFILE,
	CODE_VERSION,
	CODE_INCAPABLE,
	CODE_OPTIONAL,
	CODE_UNIMPLEMENT,
	CODE_LIMIT,
	CODE_BUG,
	CODE_NOTSTARTED,
	CODE_NESTING,
	CODE_NOTOPTIONS,
	CODE_NOTATTRIBS,
	CODE_NOTPRIMS,
	CODE_ILLSTATE,
	CODE_BADMOTION,
	CODE_BADSOLID,
	CODE_BADTOKEN,
	CODE_RANGE,
	CODE_CONSISTENCY,
	CODE_BADHANDLE,
	CODE_NOSHADER,
	CODE_MISSINGDATA,
	CODE_SYNTAX,
	CODE_MATH,
	CODE_LOG,
	CODE_SCRIPT,
	CODE_PRINTF,
	CODE_RESOLUTION,
	CODE_STATS,
	CODE_PROGRESS
} EErrorCode;


void	error(EErrorCode,const char *,...);
void	warning(EErrorCode,const char *,...);
void	fatal(EErrorCode,const char *,...);
void	info(EErrorCode,const char *,...);

#endif

