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
			return	absf(-dotvv(nD,oN)*dotvv(nD,rN)*dP*dP / (dotvv(D,D) + C_EPSILON));

		} else {
			// Full occlusion
			vector	nD,D;

			subvv(D,oP,rP);

			// Are we seeing the occluder from behind?
			if (dotvv(D,oN) >= 0)	return 0;

			normalizevf(nD,D);

			// Notice that we're computing the disk area without PI because it cancels the one in the denominator
			return	absf(-dotvv(nD,oN)*dotvv(nD,rN)*dP*dP / (dotvv(D,D) + C_EPSILON));
		}
	}
}


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
void		CPointHierarchy::store(const float *Cl,const float *Pl,const float *Nl,float dP) {
	vector	P,N;

	mulmp(P,to,Pl);
	mulmn(N,from,Nl);
	dP	*=	dPscale;

	// Should never be called
	assert(FALSE);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPointHierarchy
// Method				:	lookup
// Description			:	Lookup smtg
// Return Value			:
// Comments				:
void		CPointHierarchy::lookup(float *Cl,const float *Pl,const float *Nl,float dP,CShadingContext *context,const CTexture3dLookup *l) {
	const float maxsolidangle	=	l->maxsolidangle;
	int			*stack			=	(int *) alloca(100*sizeof(int));
	int			*stackBase		=	stack;
	int			i;
	vector		P,N;

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
			
			// Sum this item
			Cl[0]	+=	ff(P,N,item->P,item->N,item->dP);
		} else {
			const CMapNode			*node	=	nodes.array + currentNode;

			// Decide whether we want to split this node
			vector	D;
			subvv(D,node->P,P);

			// Compare the code angle to maximum solid angle
			const float distSq	= dotvv(D,D) + C_EPSILON;
			const float dParea	= (float) C_PI*node->dP*node->dP;

			// The split decision
			if (	(lengthv(D) > node->dP) && ((dParea / distSq) < maxsolidangle)	) {
				Cl[0]	+=	ff(P,N,node->P,node->N,node->dP);
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




