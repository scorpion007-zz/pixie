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
//  File				:	memoryman.cpp
//  Classes				:
//  Description			:	Implements an efficient memory manager
//
////////////////////////////////////////////////////////////////////////
#include "global.h"
#include "os.h"

#ifdef USE_MEMORY_MANAGER

#define	NUM_CHUNKS	512

typedef union TMemoryHeader {
	unsigned int	index;
	TMemoryHeader	*next;
} TMemoryHeader;


#define	MEMORY_PAGE_SIZE	1 << 18

static	TMemoryHeader			*memoryChunks[NUM_CHUNKS];
static	unsigned char			*memoryPage					=	NULL;
static	unsigned int			memoryAvailable				=	0;
static	unsigned int			memoryUsage					=	0;
static	TMemoryHeader			*memoryAllPages				=	NULL;
static	int						memoryManagerInited			=	0;
static	int						memoryManagerInitInNew		=	0;
static	TMutex					memoryMutex;


///////////////////////////////////////////////////////////////////////
// Function				:	allocMem
// Description			:	Allocate memory from the manager
// Return Value			:
// Comments				:
inline	void	*allocMem(size_t size) {
	unsigned int	 index	=	size >> 3;	// Align at 8 byte boundary
	TMemoryHeader	*ptri;

	// Round up
	if (size & 7) index++;

	// Init the memory manager if not already have
	if (memoryManagerInited == 0) {

		// Initialize the memory manager
		memInit();

		// Set this variable so we know that we actually inited the memory inside the allocator
		memoryManagerInitInNew	=	1;
	}

	// Secure the area
	osLock(memoryMutex);

	// Is the requested size too large ?
	if (index >= NUM_CHUNKS) {

		// Yes: Use the regular memory allocator
		ptri	=	(TMemoryHeader *) malloc(size+sizeof(TMemoryHeader));
		assert(ptri != NULL);
	} else {

		// No: Use the memory manager
		if ((ptri=memoryChunks[index]) == 0) {
			size				=  (index << 3) + sizeof(TMemoryHeader);

			if (size > memoryAvailable) {
				memNewPage(size);
			}

			ptri				=	(TMemoryHeader *) memoryPage;
			memoryPage			+=	size;
			memoryAvailable		-=	size;
		} else {
			memoryChunks[index]	=	ptri->next;
		}
	}

	memoryUsage	+=	index;

	// Release the area
	osUnlock(memoryMutex);

	ptri->index	=	index;

	return ptri+1;
}

///////////////////////////////////////////////////////////////////////
// Function				:	delMem
// Description			:	Delete memory from manager
// Return Value			:
// Comments				:
inline	void	delMem(void *ptr) {
	if (ptr != 0) {
		TMemoryHeader	*ptri	=	(TMemoryHeader *) ptr;

		// Secure the area
		osLock(memoryMutex);

		ptri--;
		memoryUsage	-=	ptri->index;

		if (ptri->index >= NUM_CHUNKS) {
			free(ptri);
		} else {
			unsigned int	index	=	ptri->index;
			ptri->next				=	memoryChunks[index];
			memoryChunks[index]		=	ptri;
		}

		// Release the area
		osUnlock(memoryMutex);
	}
}


///////////////////////////////////////////////////////////////////////
// Function				:	operator new
// Description			:	Overloaded new
// Return Value			:
// Comments				:
void	*operator new(size_t size) {
	return allocMem(size);
}


///////////////////////////////////////////////////////////////////////
// Function				:	operator new
// Description			:	Overloaded new
// Return Value			:
// Comments				:
void	*operator new[](size_t size) {
	return allocMem(size);
}

///////////////////////////////////////////////////////////////////////
// Function				:	operator delete
// Description			:	Overloaded delete
// Return Value			:
// Comments				:
void	operator delete(void *ptr) {
	delMem(ptr);
}

///////////////////////////////////////////////////////////////////////
// Function				:	operator delete
// Description			:	Overloaded delete
// Return Value			:
// Comments				:
void	operator delete[](void *ptr) {
	delMem(ptr);
}

///////////////////////////////////////////////////////////////////////
// Function				:	allocate_untyped
// Description			:	malloc replacement
// Return Value			:
// Comments				:
void	*allocate_untyped(size_t size) {
	return allocMem(size);
}

///////////////////////////////////////////////////////////////////////
// Function				:	allocate_untyped
// Description			:	free replacement
// Return Value			:
// Comments				:
void	free_untyped(void *ptr) {
	delMem(ptr);
}

///////////////////////////////////////////////////////////////////////
// Function				:	memInit
// Description			:	Init the memory manager
// Return Value			:
// Comments				:
void	memInit() {

	// Did we initialize the memory manager before ?
	if (memoryManagerInited == 0) {
		int	i;

		for (i=0;i<NUM_CHUNKS;i++)	memoryChunks[i]	=	0;

		memoryAvailable		=	0;
		memoryUsage			=	0;
		memoryPage			=	0;
		memoryAllPages		=	0;
		osCreateMutex(memoryMutex);
	}

	memoryManagerInited++;
}

///////////////////////////////////////////////////////////////////////
// Function				:	memShutdown
// Description			:	Shutdown the memory manager
// Return Value			:
// Comments				:
void	memShutdown() {
	memoryManagerInited--;

	// Is this the last shutdown ?
	if (memoryManagerInited == memoryManagerInitInNew) {
		TMemoryHeader	*cPage;

		osDeleteMutex(memoryMutex);

		// Free the memory pages we allocated
		while((cPage=memoryAllPages) != NULL) {
			memoryAllPages	=	cPage->next;

			free(cPage);
		}

		// Reset the local variables
		memoryPage					=	NULL;
		memoryAvailable				=	0;
		memoryUsage					=	0;
		memoryAllPages				=	NULL;
		memoryManagerInited			=	0;
		memoryManagerInitInNew		=	0;
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	memNewPage
// Description			:	Allocate a new page of memory
// Return Value			:
// Comments				:
void	memNewPage(unsigned int size) {

	assert(memoryManagerInited > 0);

	unsigned int	asize	=	max(size,MEMORY_PAGE_SIZE);
	TMemoryHeader	*cPage	=	(TMemoryHeader *) malloc(asize+sizeof(TMemoryHeader));

	cPage->next				=	memoryAllPages;
	memoryAllPages			=	cPage;
	memoryPage				=	(unsigned char *) (cPage+1);
	memoryAvailable			=	asize;
}

#endif

