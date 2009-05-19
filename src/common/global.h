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
#define	VERSION_RELEASE	2
#define	VERSION_BETA	2
#define	VERSION_ALPHA	6

// Some constant definitions

// Math constants
#ifdef C_INFINITY
#undef C_INFINITY
#endif

#ifdef C_EPSILON
#undef C_EPSILON
#endif

#ifdef C_EPSILON_TINY
#undef C_EPSILON_TINY
#endif

#define	C_INFINITY							1e30f
#define	C_EPSILON							1e-6f
#define	C_EPSILON_TINY						1e-12f
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

// This structure encapsulates a 32 bit word
typedef union {
	int				integer;
	unsigned int	uinteger;
	float			real;
	char			character;
} T32;

// This structure encapsulates a 64 bit word
typedef union {
	long long		integer;
	void			*pointer;
	char			*string;
	double			real;
} T64;


// Some useful machinery for memory management
#ifdef		_WINDOWS
	#ifdef		_DEBUG
		#include	<assert.h>

		// Register some junk for memory leak detection
		#define		_CRTDBG_MAP_ALLOC
		#include	<stdlib.h>
		#include	<crtdbg.h>

		#define		MYDEBUG_NEW		new( _NORMAL_BLOCK, __FILE__, __LINE__)
		#define		new				MYDEBUG_NEW
	#endif
#endif

#ifdef __APPLE__
#include <assert.h>
#endif

// Useful macros for allocating/deallocating untyped memory (aligned to 8 bytes)
#define	allocate_untyped(__size)	(void*) new long long[(__size + sizeof(long long) - 1) / sizeof(long long)]
#define	free_untyped(__ptr)			delete[] ((long long *) __ptr)

#ifndef		assert
#define		assert(__cond)
#endif


// Include the global config file if available
#ifdef HAVE_CONFIG_H
	#include "../../config.h"
#else

	// Are we running under Visual Studio?
	#ifdef _WINDOWS
		#include "../../config.windows.h"
	#endif
	
	// Are we running under XCode?
	#if defined(__APPLE__) || defined(__APPLE_CC__)
		#include "../../config.xcode.h"
	#endif

#endif

#endif

