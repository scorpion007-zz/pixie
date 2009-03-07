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
//  File				:	memory.cpp
//  Classes				:	-
//  Description			:	This file defines the misc. memory interface routines
//
////////////////////////////////////////////////////////////////////////
#include "common/os.h"
#include "common/align.h"
#include "memory.h"
#include "stats.h"
#include "ri_config.h"

// Some global variables
static	int					allocatedZoneMemory		=	0;
static	int					freedZoneMemory			=	0;
static	int					allocatedPages			=	0;
static	int					freedPages				=	0;
static	int					memoryPageSize			=	ZONE_BASE_SIZE;
static	float				lastPagingTime			=	0;


///////////////////////////////////////////////////////////////////////
// Function				:	memoryInit
// Description			:	Initialize a named memory manager
// Return Value			:
// Comments				:
void			memoryInit(CMemPage *&stack) {
	stack	=	memoryNewPage(ZONE_INIT_SIZE);
}

///////////////////////////////////////////////////////////////////////
// Function				:	memoryTini
// Description			:	Destroy a named memory manager
// Return Value			:
// Comments				:	Should be called before memTini so counts are correct
void			memoryTini(CMemPage *&stack) {
	CMemPage	*cPage;

	// We must be the first page
	assert(stack->prev == NULL);

	while(stack != NULL) {
		cPage	=	stack;
		stack	=	cPage->next;

		memoryDeletePage(cPage);
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	memoryNewPage
// Description			:	Allocate a new memory page whose size is at least "size"
// Return Value			:
// Comments				:
CMemPage		*memoryNewPage(int size) {
	float		time		=	osCPUTime();

	// Are we allocating/deallocating too often ?
	/*
	if ((time - lastPagingTime) < 1) {
		memoryPageSize		+=	ZONE_INCREMENT_SIZE;	// Increase the page size
	}
	*/
	lastPagingTime			=	time;

	size					=	max(size,memoryPageSize);
	size					=	(size + 7) & (~7);

	CMemPage	*newPage	=	new CMemPage;
	newPage->availableSize	=	size;
	newPage->totalSize		=	size;
	newPage->base			=	(char *) allocate_untyped(size);
	newPage->memory			=	newPage->base;
	newPage->next			=	NULL;
	newPage->prev			=	NULL;

	// Make sure the memory is aligned
	assert(isAligned64(newPage->base));

	// Stats update
	allocatedPages++;
	allocatedZoneMemory		+=	size;
	stats.zoneMemory		+=	size;

	if (stats.zoneMemory > stats.peakZoneMemory)
		stats.peakZoneMemory	=	stats.zoneMemory;

	return newPage;
}


///////////////////////////////////////////////////////////////////////
// Function				:	memoryDeletePage
// Description			:	Dealoocate memory page
// Return Value			:
// Comments				:
void		memoryDeletePage(CMemPage *cPage) {
	// Stats update
	freedPages++;
	freedZoneMemory			+=	cPage->totalSize;
	stats.zoneMemory		-=	cPage->totalSize;

	free_untyped(cPage->base);
	delete cPage;
}

