//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright © 1999 - 2003, Okan Arikan
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
//  File				:	memory.h
//  Classes				:	-
//  Description			:	This file defines the misc. memory interface routines
//
////////////////////////////////////////////////////////////////////////
#ifndef MEMORY_H
#define MEMORY_H

#include "common/global.h"
#include "common/os.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CMemPage
// Description			:	This class coltains memory that's allocated on the fly
// Comments				:
// Date last edited		:	8/2/2001
class CMemPage {
public:
		char			*memory;					// Points to the current free memory
		char			*base;						// Points to the base memory
		int				availableSize;				// The available number of bytes
		int				totalSize;					// The total size of the block
		CMemPage		*next;						// Points to the next free memory block
		CMemPage		*prev;						// points to the previous valid memory block
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Renderer memory stack management
extern	CMemPage	*currentMemoryPage;				// The page that we're allocating from


void				memoryInit();					// Init the memory
void				memoryTini();					// Destroy the allocated memory
void				memoryInit(CMemPage *&);		// Init named memory stack
void				memoryTini(CMemPage *&);		// Destroy the named allocated memory
CMemPage			*memoryNewPage(int);			// Allocate a new memory page
void				memoryDeletePage(CMemPage *);	// Allocate a new memory page




// This macro allocates memory in the global stack
inline void *ralloc(int size) {
	void	*ptr;

	while(currentMemoryPage->availableSize < size) {
		if (currentMemoryPage->next == NULL) {
			CMemPage	*cPage				=	memoryNewPage(size);
			cPage->prev						=	currentMemoryPage;
			currentMemoryPage->next			=	cPage;
		}

		currentMemoryPage					=	currentMemoryPage->next;
		currentMemoryPage->availableSize	=	currentMemoryPage->totalSize;
		currentMemoryPage->memory			=	currentMemoryPage->base;
	}


	ptr									=	currentMemoryPage->memory;
	currentMemoryPage->memory			=	currentMemoryPage->memory+size;
	currentMemoryPage->availableSize	-=	size;
	return	ptr;
}

// This macro allocates memory in the named stack
inline void *ralloc(int size,CMemPage *&stack) {
	void	*ptr;

	while(stack->availableSize < size) {
		if (stack->next == NULL) {
			CMemPage	*cPage				=	memoryNewPage(size);
			cPage->prev						=	stack;
			stack->next						=	cPage;
		}

		currentMemoryPage					=	currentMemoryPage->next;
		currentMemoryPage->availableSize	=	currentMemoryPage->totalSize;
		currentMemoryPage->memory			=	currentMemoryPage->base;
	}


	ptr										=	stack->memory;
	stack->memory							=	stack->memory+size;
	stack->availableSize					-=	size;
	return	ptr;
}


// This macro places a checkpoint
#define	memBegin()	{														\
	char		*savedMem		=	currentMemoryPage->memory;				\
	int			savedAvailable	=	currentMemoryPage->availableSize;		\
	CMemPage	*savedPage		=	currentMemoryPage;

// This macro restores the memory to the last checkpoint
// It is important that the scope between the matching begin-end
// pairs mist not be exitted
#define	memEnd()															\
		currentMemoryPage					=	savedPage;					\
		currentMemoryPage->availableSize	=	savedAvailable;				\
		currentMemoryPage->memory			=	savedMem;					\
	}


// Mem save and mem restore does the same thing, but they explicitly store the checkpoint in T64 data[3];
#define	memSave(__data,__stack)													\
	__data[0].pointer		=	__stack->memory;								\
	__data[1].integer		=	__stack->availableSize;							\
	__data[2].pointer		=	__stack;

#define memRestore(__data,__stack)												\
	__stack					=	(CMemPage *) __data[2].pointer;					\
	__stack->availableSize	=	__data[1].integer;								\
	__stack->memory			=	(char *) __data[0].pointer;


#endif





