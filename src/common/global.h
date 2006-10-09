//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright � 1999 - 2003, Okan Arikan
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
//  File				:	global.h
//  Classes				:	-
//  Description			:	Some global definitions
//
////////////////////////////////////////////////////////////////////////


//
//
//
//
//
//
//		This header has to be included from every file
//
//
//
//
//
//
//
#ifndef GLOBAL_H
#define	GLOBAL_H

// The Pixie version
#define	VERSION_RELEASE	1
#define	VERSION_BETA	7
#define	VERSION_ALPHA	5

// Some constant definitions

// Math constants
#ifdef C_INFINITY
#undef C_INFINITY
#endif

#ifdef C_EPSILON
#undef C_EPSILON
#endif

#define	C_INFINITY							1e30f
#define	C_EPSILON							1e-6f
#define C_PI                                3.141592653589793238462643383279502884197169399375105820974944592308

// Logic constants
#ifndef TRUE
#define	TRUE								1
#endif

#ifndef FALSE
#define	FALSE								0
#endif


// Misc Options and Attributes constants
#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#ifdef radians
#undef radians
#endif

#ifdef degrees
#undef degrees
#endif

#define			min(a,b)					((a) < (b) ? (a) : (b))
#define			max(a,b)					((a) > (b) ? (a) : (b))
#define			radians(a)					((a)*C_PI/180.)
#define			degrees(a)					((a)*180./ C_PI)

#define			getPointer(a)				(((unsigned long) a) & (~3))
#define			getData(a)					(((unsigned long) a) & 3)
#define			getToken(a,b)				(((unsigned long) a) | b)


// This structure encapsulates a 32 bit word
typedef union {
	int				integer;
	unsigned int	uinteger;
	float			real;
	char			character;
} T32;

// This structure encapsulates a 64 bit word
typedef union {
	long int		integer;
	void			*pointer;
	char			*string;
	float			real;
	double			dreal;
} T64;


#ifndef __APPLE_CC__
	// Enable the memory manager
	#define USE_MEMORY_MANAGER
	// But under OSX, this seems to cause some issues
	// We use __APPLE_CC_ because fltk insists on __APPLE__
	// being undefined
#endif

// For Windows/debug build, turn off the memory manager so we can check the memory leaks
#ifdef		WIN32
#ifdef		_DEBUG
#undef		USE_MEMORY_MANAGER
#include	<assert.h>
#endif
#endif

#include "memoryman.h"

#ifndef		assert
#define		assert(__cond)
#endif


#include "../../config.h"


#endif
