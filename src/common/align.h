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
#include "global.h"

// Include the pointer types if necessary
#ifdef __APPLE_CC__
#include "inttypes.h"
#endif

// For 32 bits, we may want to turn these off


// Check if a pointer is 8 byte aligned
#define	isAligned64(__data)	(uintptr_t) __data & 0x7

// IMPORTANT: This macro only works with char *
#define	align64(__data)		__data = (char *) (((uintptr_t) __data + 7) & (~7))


#endif




