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
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef ATOMIC_H
#define ATOMIC_H


////////////////////////////////////////////////////////////////////////
// Atomic increment/decrement functions



// Windows (32 bit)
#if defined(_WIN32)

inline int atomicIncrement(volatile int *pointer) {
    unsigned char retVal;
    __asm {
        mov ECX,pointer
        lock inc DWORD ptr[ECX]
        setne retVal
    }
    return retVal;
}

inline int atomicDecrement(volatile int *pointer) {
    unsigned char retVal;
    __asm {
        mov ECX,pointer
        lock dec DWORD ptr[ECX]
        setne retVal
    }
    return retVal;
}

// Windows 64 bits
#elif defined(__WIN64)

inline int atomicIncrement(volatile int *ptr) {
    unsigned char ret;
    asm volatile("lock\n"
                 "incl %0\n"
                 "setne %1"
                 : "=m" (*ptr), "=qm" (ret)
                 : "m" (*ptr)
                 : "memory");
    return static_cast<int>(ret);
}

inline int atomicDecrement(volatile int *ptr)
{
    unsigned char ret;
    asm volatile("lock\n"
                 "decl %0\n"
                 "setne %1"
                 : "=m" (*ptr), "=qm" (ret)
                 : "m" (*ptr)
                 : "memory");
    return static_cast<int>(ret);
}



// GCC (32 bit)
#elif defined(__i386__) && defined(__GNUC__)

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

#else
#error Unsupported platform
#endif

#endif





