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
#define ALIGN_H
#include "global.h"

// Include the pointer types if necessary
#ifdef __APPLE_CC__	// >>OSX
#include "inttypes.h"
#else				// <<OSX

#ifndef _WINDOWS	// >>Not Windoze

#ifdef HAVE_STDINT_H
	#include <stdint.h>
#endif

#else				// >>Windoze

#ifndef uint32_t 
#define uint32_t unsigned int
#endif

#ifndef uint64_t 
#define uint64_t unsigned long long
#endif

#endif				// <<Windoze

#endif

// For 32 bits, we may want to turn these off


// Check if a pointer is 8 byte aligned
#define	isAligned64(__data)	(((size_t) (__data) & 0x7) == 0)

// Alignment macro (returns a 64 bit aligned data)
#define	align64(__data)		(((size_t) (__data) + 7) & (~7))


#endif




