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
//  File				:	align.h
//  Classes				:	-
//  Description			:	Various macros for memory alignment
//
////////////////////////////////////////////////////////////////////////
#ifndef ALIGN_H
#define ALIGN_N


// Check if a pointer is 8 byte aligned
#define	isAligned64(__data)	(const char *) __data & 0x7

// IMPORTANT: This macro only works with char* or int
// 8 byte align
#define	align64(__data)		__data	+=	__data & 0x1;	\
							__data	+=	__data & 0x2;	\
							__data	+=	__data & 0x4;	\


#endif




