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
#include "random.h"
#include "shading.h"

// The predefined names for the area and the radiosity channels
const	char	*areaName		=	"_area";
const	char	*radiosityName	=	"_radiosity";

///////////////////////////////////////////////////////////////////////
// Function				:	ff
// Description			:	Compute the form factor from an occluding disk
// Return Value			:	The form factor
// Comments				:
static	inline	float	ff(const float *rP,const float *rN,const float *oP,const float *oN,float dP) {
	float	t	=	dotvv(oP,rN) - dotvv(rP,rN);

	// If the occluding sphere is completely behind the tangent plane, return
	if (t < - dP)	return 0;
	else {

		// Do we have partial occlusion?
		if (t < dP) {
			vector	cP,P0,P1;

			// Recompute a sphere that fits above the horizon of the receiver
			mulvf(P0,rN,dP);	addvv(P0,oP);
			mulvf(P1,rN,-t);	addvv(P1,oP);

			// The center of the sphere
			addvv(cP,P0,P1);	mulvf(cP,0.5f);

			vector	D,nD;
			subvv(D,P0,cP);
			dP		=	lengthv(D);

			subvv(D,cP,rP);

			// Are we seeing the occluder from behind?
			if (dotvv(D,oN) >= 0)	return 0;

			normalizevf(nD,D);

			// Notice that we're computing the disk area without PI because it cancels the one in the denominator
			return	-dotvv(nD,oN)*dotvv(nD,rN)*dP*dP / (dotvv(D,D) + C_EPSILON);

		} else {
			// Full occlusion
			vector	nD,D;

			subvv(D,oP,rP);

			// Are we seeing the occluder from behind?
			if (dotvv(D,oN) >= 0)	return 0;

			normalizevf(nD,D);
			assert(dotvv(nD,rN) >= 0);

			// Notice that we're computing the disk area without PI because it cancels the one in the denominator
			return	-dotvv(nD,oN)*dotvv(nD,rN)*dP*dP / (dotvv(D,D) + C_EPSILON);
		}
	}
}







///////////////////////////////////////////////////////////////////////
// Class				:	CPointHierarchy
// Method				:	CPointHierarchy
// Description			:	Ctor
// Return Value			:
// Comments				:
CPointHierarchy::CPointHierarchy(const char *n,const float *from,const float *to,FILE *in) : CMap<CPointCloudPoint>(), CTexture3d(n,from,to) {
	
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

	// Find the indices for area and radiosity
	areaIndex		=	-1;
	radiosityIndex	=	-1;
	int	i;
	for (i=0;i<numChannels;i++) {
		if		((strcmp(channels[i].name,areaName) == 0)		&& (channels[i].numSamples == 1))	areaIndex		=	channels[i].sampleStart;
		else if ((strcmp(channels[i].name,radiosityName) == 0)	&& (channels[i].numSamples == 3))	radiosityIndex	=	channels[i].sampleStart;
	}

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
// Method				:	computeHierarchy
// Description			:	Constructs a hierarchy of the stored items
// Return Value			:	-
// Comments				:
void		CPointHierarchy::computeHierarchy() {

	// Get the item pointers into a temporary array
	int	i;
	int	*tmp	=	new int[CMap<CPointCloudPoint>::numItems];
	
	for (i=1;i<=CMap<CPointCloudPoint>::numItems;i++)	tmp[i-1]	=	i;

	// Compute the map hierarchy
	const int	root	=	cluster(CMap<CPointCloudPoint>::numItems,tmp);

	// Root is always the first item in the array
	assert(root == 0);

	// Ditch the temp memory
	delete [] tmp;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPointHierarchy
// Method				:	average
// Description			:	Create an internal node by averaging the point data
// Return Value			:	-
// Comments				:
int			CPointHierarchy::average(int numItems,int *indices) {
	CMapNode	node;

	// PASS 1:	Average the position/normal
	initv(node.P,0);
	initv(node.N,0);
	for (int i=numItems;i>0;i--) {
		const CPointCloudPoint	*item	=	CMap<CPointCloudPoint>::items + (*indices++);
		addvv(node.P,item->P);
		addvv(node.N,item->N);
	}
	indices	-=	numItems;

	// Normalize the thing
	assert(numItems > 0);
	mulvf(node.P,1/(float) numItems);
	normalizev(node.N);

	// PASS 2:	Compute the maximum deviation
	initv(node.radiosity,0);
	node.dP		=	0;
	node.dN		=	1;
	for (int i=numItems;i>0;i--) {
		vector					D;
		const CPointCloudPoint	*item	=	CMap<CPointCloudPoint>::items + (*indices++);
		const float				*src	=	data.array + item->entryNumber;
		float					area;

		subvv(D,node.P,item->P);
		if (areaIndex == -1)		area	=	max(((float) C_PI*item->dP*item->dP*dotvv(node.N,item->N)),0);
		else						area	=	max((src[areaIndex]*dotvv(node.N,item->N)),0);
		
		node.dP		+=	area;

		if (radiosityIndex != -1) {
			vector	tmp;
			mulvf(tmp,src + radiosityIndex,area);
			addvv(node.radiosity,tmp);
		}

		node.dN		=	min(node.dN,dotvv(node.N,item->N));
	}
	indices		-=	numItems;

	// Normalize the radiosity and the area
	mulvf(node.radiosity,1 / node.dP);				// Normalize the radiosity
	node.dP		=	sqrtf(node.dP / (float) C_PI);	// Convert to effective radius

	// Create the node
	nodes.push(node);
	return nodes.numItems - 1;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPointHierarchy
// Method				:	cluster
// Description			:	Cluster the items
// Return Value			:	-
// Comments				:
int			CPointHierarchy::cluster(int numItems,int *indices) {

	// Sanity check
	assert(numItems > 0);

	if (numItems == 1) {
		// Create a leaf
		return -indices[0];

	} else if (numItems == 2) {
		// Easy case
		int			nodeIndex	=	average(numItems,indices);
		CMapNode	*node		=	nodes.array + nodeIndex;
		node->child0			=	-indices[0];
		node->child1			=	-indices[1];
		return nodeIndex;

	} else {
		// Allocate temp memory
		int	*membership,*subItems;
		
		// Use alloca if the allocation size is low enough
		if (numItems >= ALLOCA_MAX_ITEMS)	membership	=	new int[numItems*2];
		else								membership	=	(int *) alloca(numItems*2*sizeof(int));

		subItems	=	membership	+	numItems;

		vector	bmin,bmax;

		initv(bmin,C_INFINITY);
		initv(bmax,-C_INFINITY);
		
		// The membership is dummy ... Also compute the bounding box of the point set
		for (int i=0;i<numItems;i++) {
			membership[i]	=	-1;
			addBox(bmin,bmax,CMap<CPointCloudPoint>::items[indices[i]].P);
		}
		
		vector	C0,C1;		// The cluster centers
		vector	N0,N1;		// The cluster normals

		// Create random cluster centers
		initv(C0,	_urand()*(bmax[0]-bmin[0]) + bmin[0],
					_urand()*(bmax[1]-bmin[1]) + bmin[1],
					_urand()*(bmax[2]-bmin[2]) + bmin[2]);
		initv(C1,	_urand()*(bmax[0]-bmin[0]) + bmin[0],
					_urand()*(bmax[1]-bmin[1]) + bmin[1],
					_urand()*(bmax[2]-bmin[2]) + bmin[2]);

		// Create random cluster normals
		initv(N0,	_urand()*2-1,	_urand()*2-1,	_urand()*2-1);
		initv(N1,	_urand()*2-1,	_urand()*2-1,	_urand()*2-1);
		normalizevf(N0);
		normalizevf(N1);

		// Perform the clustering iterations
		int		num0,num1;
		for (int iterations=0;iterations<5;iterations++) {	// Try 5 times ... Not until convergence
			int		changed	=	FALSE;
			vector	nC0,nC1;
			vector	nN0,nN1;

			// Clear the data
			initv(nC0,0);
			initv(nC1,0);
			initv(nN0,0);
			initv(nN1,0);
			num0	=	0;
			num1	=	0;
			
			// iterate over items
			for (int i=0;i<numItems;i++) {
				vector						D;
				const	CPointCloudPoint	*cItem	=	CMap<CPointCloudPoint>::items + indices[i];
				
				// Compute the distance to the first cluster
				subvv(D,cItem->P,C0);
				const float d0	=	dotvv(D,D) / max(dotvv(N0,cItem->N),C_EPSILON);
				
				// Compute the distance to the second cluster
				subvv(D,cItem->P,C1);
				const float d1	=	dotvv(D,D) / max(dotvv(N1,cItem->N),C_EPSILON);
				
				// Change the membership if necessary
				if (d0 < d1) {
					if (membership[i] != 0) {
						changed			=	TRUE;
						membership[i]	=	0;
					}

					addvv(nC0,cItem->P);
					addvv(nN0,cItem->N);
					num0++;
				} else {
					if (membership[i] != 1) {
						changed			=	TRUE;
						membership[i]	=	1;
					}

					addvv(nC1,cItem->P);
					addvv(nN1,cItem->N);
					num1++;
				}
			}
			
			// Check for degenerate cases
			if ((num0 == 0) || (num1 == 0)) {
				initv(C0,	_urand()*(bmax[0]-bmin[0]) + bmin[0],
							_urand()*(bmax[1]-bmin[1]) + bmin[1],
							_urand()*(bmax[2]-bmin[2]) + bmin[2]);
				initv(C1,	_urand()*(bmax[0]-bmin[0]) + bmin[0],
							_urand()*(bmax[1]-bmin[1]) + bmin[1],
							_urand()*(bmax[2]-bmin[2]) + bmin[2]);

				initv(N0,	_urand()*2-1,	_urand()*2-1,	_urand()*2-1);
				initv(N1,	_urand()*2-1,	_urand()*2-1,	_urand()*2-1);
				normalizevf(N0);
				normalizevf(N1);
			} else {
				if (changed == FALSE)	break;

				mulvf(C0,nC0,1 / (float) num0);
				mulvf(C1,nC1,1 / (float) num1);

				// Normalize the normal vectors
				normalizevf(N0,nN0);
				normalizevf(N1,nN1);
			}	
		}
		
		// Do we have a bad clustering?
		while (num0 == 0 || num1 == 0) {

			// Clustering failed - probably coincident points, make an arbitrary split
			num0 = num1 = 0;
			for (int i=0;i<numItems;i++) {
				const int which = i & 1;
				if (which)	num1++;
				else		num0++;
				membership[i] = which;
			}

			// FIXME: A smarter thing to do would be to sort the items in one dimension and split it in half
		}
		
		assert((num0 + num1) == numItems);

		// Average the items and create an internal node
		const int	nodeIndex	=	average(numItems,indices);
		
		// OK, split the items into two
		int	i,j;
		
		// Collect the items in the first child
		for (i=0,j=0;i<numItems;i++)	if (membership[i] == 0)	subItems[j++]	=	indices[i];
		assert(j == num0);
		const int	child0	=	cluster(num0,subItems);
		
		// Collect the items in the second child
		for (i=0,j=0;i<numItems;i++)	if (membership[i] == 1)	subItems[j++]	=	indices[i];
		assert(j == num1);
		const int	child1	=	cluster(num1,subItems);
		
		// NOTE: There's an important subtlety here...
		// We can not access cNode before the child nodes are created because the creation of children
		// may change the nodes.array field
		CMapNode *cNode	=	nodes.array + nodeIndex;
		cNode->child0	=	child0;
		cNode->child1	=	child1;

		// Reclaim the memory if applicable
		if (numItems >= ALLOCA_MAX_ITEMS)	delete [] membership;

		// Return the index of the node
		return nodeIndex;
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPointHierarchy
// Method				:	lookup
// Description			:	Lookup smtg
// Return Value			:
// Comments				:
void		CPointHierarchy::lookup(float *Cl,const float *Pl,const float *dPdul,const float *dPdvl,const float *Nl,CShadingContext *context) {
	const CShadingScratch	*scratch		=	&(context->currentShadingState->scratch);
	const float				maxsolidangle	=	scratch->occlusionParams.maxSolidAngle;
	int						*stack			=	(int *) alloca(POINTHIERARCHY_STACK_SIZE*sizeof(int));
	int						*stackBase		=	stack;
	int						i;
	vector					P,N;

	// Transform the lookup point to the correct coordinate system
	mulmp(P,to,Pl);
	mulmn(N,from,Nl);

	// Clear the data
	for (i=0;i<dataSize;i++)	Cl[i]	=	0;

	// Do the recursive stuff
	*stack++	=	0;
	while(stack > stackBase) {
		const int	currentNode	=	*(--stack);

		// Is this a leaf ?
		if (currentNode < 0) {
			const CPointCloudPoint	*item	=	CMap<CPointCloudPoint>::items - currentNode;

			// Are we behind the item?
			if (dotvv(P,item->N) <= dotvv(item->P,item->N))	continue;
			
			// Compute the form factor
			float		form;
			const float	*src	=	data.array + item->entryNumber;
			if (areaIndex == -1)	form	=	ff(P,N,item->P,item->N,item->dP);
			else					form	=	ff(P,N,item->P,item->N,sqrtf(src[areaIndex] / (float) C_PI));
			assert(form >= 0);

			// Sum the data
			if (radiosityIndex > 0) {
				Cl[0] += form*src[radiosityIndex+0];
				Cl[1] += form*src[radiosityIndex+1];
				Cl[2] += form*src[radiosityIndex+2];
			}
			Cl[3]	+=	form;

		} else {
			const CMapNode			*node	=	nodes.array + currentNode;
			
			// Are we behind the node?
			//if ((node->dN > 0.999999) && (dotvv(P,node->N) <= dotvv(node->P,node->N))) {
			
			// FIXME: A more general behind test would be nice

			// Decide whether we want to split this node
			vector	D;
			subvv(D,node->P,P);

			// Compare the code angle to maximum solid angle
			const float distSq	= dotvv(D,D) + C_EPSILON;
			const float dParea	= (float) C_PI*node->dP*node->dP;

			// The split decision
			if (	(lengthv(D) > node->dP) && ((dParea / distSq) < maxsolidangle)	) {
				const float form = ff(P,N,node->P,node->N,node->dP);

				if (radiosityIndex > 0) {
					Cl[0] += form*node->radiosity[0];
					Cl[1] += form*node->radiosity[1];
					Cl[2] += form*node->radiosity[2];
				}
				Cl[3]	+=	form;
			} else {
				// Sanity check
				assert((stack-stackBase) < (POINTHIERARCHY_STACK_SIZE-2));
		
				// Split
				*stack++	=	node->child0;
				*stack++	=	node->child1;
			}
		}
	}
}


void RiPtFilter() {

}



