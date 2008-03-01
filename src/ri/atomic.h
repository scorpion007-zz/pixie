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
//  File				:	atomic.h
//  Classes				:	-
//  Description			:	This file contains the atomic increment and decrement
//							to ensure consistency in multi-threaded environments
//							without kernel synchronization.
//
//							The Windoze and Apple implementations are pretty standard
//							but this file gets pretty messy for other platforms.
//
////////////////////////////////////////////////////////////////////////
#ifndef ATOMIC_H
#define ATOMIC_H


////////////////////////////////////////////////////////////////////////
// Atomic increment/decrement functions




///////////////////////////////////////////////////////////////
// Windoze
#if defined(_WINDOWS)

// Include the mighty (crappy) windoze header
#ifndef WIN32_LEAN_AND_MEAN
#define	WIN32_LEAN_AND_MEAN 
#endif
#include <windows.h>

// Ugly workaround the stuping LONG definition
// This is one of the reasons why Windoze is written by monkeys
inline int atomicIncrement(volatile int *pointer) {
	return InterlockedIncrement((volatile LONG *) pointer);
}

inline int	atomicDecrement(volatile int *pointer) {
	return InterlockedDecrement((volatile LONG *) pointer);
}

///////////////////////////////////////////////////////////////
// Apple
#elif defined(__APPLE__) || defined(__APPLE_CC__)

// Include the OSX header
#include <libkern/OSAtomic.h>

inline int atomicIncrement(int32_t *ptr) {
	return OSAtomicIncrement32Barrier(ptr);
}

inline int atomicDecrement(int32_t *ptr) {
	return OSAtomicDecrement32Barrier(ptr);
}

///////////////////////////////////////////////////////////////
// GCC (i386 or x86_64)
#elif (defined(__i386__) && defined(__GNUC__) || defined(__x86_64__)  && defined(__GNUC__))

inline int atomicIncrement(volatile int *ptr) {
    unsigned char ret;
    asm volatile("lock\n"
                 "incl %0\n"
                 "setne %1"
                 : "=m" (*ptr), "=qm" (ret)
                 : "m" (*ptr)
                 : "memory");
    return ret;
}

inline int atomicDecrement(volatile int *ptr) {
    unsigned char ret;
    asm volatile("lock\n"
                 "decl %0\n"
                 "setne %1"
                 : "=m" (*ptr), "=qm" (ret)
                 : "m" (*ptr)
                 : "memory");
    return ret;
}

///////////////////////////////////////////////////////////////
// GCC (MIPS)
#elif defined(__GNUC__) && defined( __PPC__)


inline int atomicIncrement(volatile int *ptr) {
    register int ret;
    register int one = 1;
    asm volatile("lwarx  %0, 0, %2\n"
                 "add    %0, %3, %0\n"
                 "stwcx. %0, 0, %2\n"
                 "bne-   $-12\n"
                 : "=&r" (ret), "=m" (*ptr)
                 : "r" (ptr), "r" (one)
                 : "cc", "memory");
    return ret;
}

inline int atomicDecrement(volatile int *ptr) {
    register int ret;
    register int one = -1;
    asm volatile("lwarx  %0, 0, %2\n"
                 "add    %0, %3, %0\n"
                 "stwcx. %0, 0, %2\n"
                 "bne-   $-12\n"
                 : "=&r" (ret), "=m" (*ptr)
                 : "r" (ptr), "r" (one)
                 : "cc", "memory");
    return ret;
}

///////////////////////////////////////////////////////////////
// Generic
#else


#define	ATOMIC_UNSUPPORTED
#warning Atomic Instructions are not supported on this platform, defaulting to generic implementation

// Have a cross platform solution here
inline int atomicIncrement(volatile int *ptr) {
	int	value;
	osLock(CRenderer::atomicMutex);
	value	=	++(*ptr);
	osUnlock(CRenderer::atomicMutex);
	return value;
}

inline int atomicDecrement(volatile int *ptr) {
	int	value;
	osLock(CRenderer::atomicMutex);
	value	=	--(*ptr);
	osUnlock(CRenderer::atomicMutex);
	return value;
}

#endif

#endif





