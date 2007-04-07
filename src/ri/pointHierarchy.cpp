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
//  File				:	pointHierarchy.cpp
//  Classes				:	CPointHierarchy
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include "pointHierarchy.h"
#include "error.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CPointHierarchy
// Method				:	CPointHierarchy
// Description			:	Ctor
// Return Value			:
// Comments				:
CPointHierarchy::CPointHierarchy(const char *n,const float *from,const float *to,FILE *in) : CMapHierarchy<CPointCloudPoint>(), CTexture3d(n,from,to) {
	
	// Try to read the point cloud

	// Read the header
	readChannels(in);
	
	// Read the points
	CMap<CPointCloudPoint>::read(in);

	// Reserve the actual space
	data.reserve(numItems*dataSize);
	
	// Read the data
	fread(data.array,sizeof(float),numItems*dataSize,in);
	data.numItems	=	numItems*dataSize;

	// Close the file
	fclose(in);

	// Compute the point hierarchy so that we can perform lookups
	computeHierarchy();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPointHierarchy
// Method				:	~CPointHierarchy
// Description			:	Dtor
// Return Value			:
// Comments				:
CPointHierarchy::~CPointHierarchy() {
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPointHierarchy
// Method				:	store
// Description			:	Store smtg
// Return Value			:
// Comments				:
void		CPointHierarchy::store(const float *,const float *,const float *,float) {
	// Should never be called
	assert(FALSE);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPointHierarchy
// Method				:	lookup
// Description			:	Lookup smtg
// Return Value			:
// Comments				:
void		CPointHierarchy::lookup(float *Cl,const float *Pl,const float *Nl,float radius) {
	int		*stack		=	(int *) alloca(100*sizeof(int));
	int		*stackBase	=	stack;
	int		i;

	// Clear the data
	for (i=0;i<dataSize;i++)	Cl[i]	=	0;

	*stack++			=	root;
	while(stack > stackBase) {
		const int	currentNode	=	*(--stack);

		// Is this a leaf ?
		if (currentNode < 0) {
			CPointCloudPoint	*item		=	CMap<CPointCloudPoint>::items - currentNode;
			
			// Sum this item
		} else {
			CMapNode			*node		=	nodes.array + currentNode;
			CPointCloudPoint	*average	=	CMap<CPointCloudPoint>::items + node->average;

			// Decide whether we want to split this node
			vector	D;
			subvv(D,average->P,Pl);

			// Are we pointing towards each other?
			if (	(dotvv(D,Nl) > 0) && (dotvv(D,average->N) < 0)		) {

				// Compare the code angle to some random angle
				if (	(average->dP / lengthv(D)) < cosf((float) radians(5))	) {
					// Use the average
				} else {

					// Sanity check
					assert((stack-stackBase) < 98);

					// Split
					*stack++	=	node->child0;
					*stack++	=	node->child1;
				}
			}
		}
	}
}




