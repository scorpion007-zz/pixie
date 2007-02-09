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
#include "memory.h"
#include "stats.h"

// The default zone size
#define	INIT_ZONE_SIZE	500000				// The intial size of the memory zone

// Some global variables
static	int					allocatedZoneMemory		=	0;
static	int					freedZoneMemory			=	0;
static	int					allocatedPages			=	0;
static	int					freedPages				=	0;
static	int					memoryPageSize			=	1000000;
static	float				lastPagingTime			=	0;


///////////////////////////////////////////////////////////////////////
// Function				:	memoryInit
// Description			:	Initialize a named memory manager
// Return Value			:
// Comments				:	Should be called after memInit
void			memoryInit(CMemPage *&stack) {
	stack	=	memoryNewPage(INIT_ZONE_SIZE);
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
	CMemPage	*newPage	=	new CMemPage;
	float		time		=	osCPUTime();

	// Are we allocating/deallocating too often ?
	if ((time - lastPagingTime) < 1) {
		memoryPageSize		+=	100000;	// Increase the zone size at 100k increments
	}
	lastPagingTime			=	time;

	size					+=	memoryPageSize;

	newPage->availableSize	=	size;
	newPage->totalSize		=	size;
	newPage->base			=	new char[size];
	newPage->memory			=	newPage->base;
	newPage->next			=	NULL;
	newPage->prev			=	NULL;

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

	delete [] cPage->base;
	delete cPage;
}

