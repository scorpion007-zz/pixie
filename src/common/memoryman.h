//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright � 1999 - 2003, Okan Arikan
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
//  File				:	memoryman.h
//  Classes				:
//  Description			:	Implements an efficient memory manager
//
////////////////////////////////////////////////////////////////////////
#ifndef MEMORY_MAN
#define MEMORY_MAN


#ifndef WIN32
// >> Win32
#ifdef HAVE_MALLOC_H
#include <malloc.h>
#else
#include <stdlib.h>
#endif

// For systems that don't have built in alloca
#ifdef HAVE_ALLOCA_H
#include <alloca.h>
#endif

// << Win32
#endif

extern	void	*allocate_untyped(size_t size);
extern	void	free_untyped(void *);


#ifdef USE_MEMORY_MANAGER

extern	void	memInit();
extern	void	memShutdown();
extern	void	memNewPage(unsigned int);

extern	void	*operator new(size_t size);
extern	void	operator delete(void *ptr);
extern	void	*operator new[](size_t size);
extern	void	operator delete[](void *ptr);

#else		// USE_MEMORY_MANAGER

#ifdef WIN32
#ifdef _DEBUG

// Register some junk for memory leak detection
#define _CRTDBG_MAP_ALLOC
#include <malloc.h>
#include <stdlib.h>
#include <crtdbg.h>





#define	memInit()	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);



#ifdef new
#undef new
#endif


#define MYDEBUG_NEW   new( _NORMAL_BLOCK, __FILE__, __LINE__)

#define new MYDEBUG_NEW


#else
#ifdef new
#undef new
#endif

#endif	// _DEBUG
#endif // WIN32



#ifndef memInit
#define	memInit()
#endif


#ifndef memShutdown
#define	memShutdown()
#endif


#endif		// USE_MEMORY_MANAGER




#endif

