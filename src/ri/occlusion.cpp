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
//  File				:	occlusion.cpp
//  Classes				:	COcclusionCuller
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include "occlusion.h"
#include "renderer.h"
#include "memory.h"

///////////////////////////////////////////////////////////////////////
// Class				:	COcclusionCuller
// Method				:	~COcclusionCuller
// Description			:	Ctor
// Return Value			:	-
// Comments				:
COcclusionCuller::COcclusionCuller() {
}

///////////////////////////////////////////////////////////////////////
// Class				:	COcclusionCuller
// Method				:	~COcclusionCuller
// Description			:	Dtor
// Return Value			:	-
// Comments				:
COcclusionCuller::~COcclusionCuller() {
}

///////////////////////////////////////////////////////////////////////
// Class				:	COcclusionCuller
// Method				:	COcclusionCuller
// Description			:	Ctor
// Return Value			:	-
// Comments				:
void	COcclusionCuller::initCuller(int w,float *ma) {
	int sizeRequirements = 0;
	for (depth=0,width=1;width < w;depth++,width=width<<1) sizeRequirements+=width*width;
	sizeRequirements += width*width;

	// (globalMemory is checkpointed)
	nodes			=	(COcclusionNode **) ralloc(sizeRequirements*sizeof(COcclusionNode *),CRenderer::globalMemory);
	root			=	newNode(NULL,width,0,sizeRequirements,0,0);
	maxOpaqueDepth	=	ma;
}


///////////////////////////////////////////////////////////////////////
// Class				:	COcclusionCuller
// Method				:	reset
// Description			:	Reset the occlusion hierarchy
// Return Value			:	-
// Comments				:
void	COcclusionCuller::resetHierarchy(COcclusionNode *cNode) {
	if (cNode==NULL)	cNode	=	root;

	if (cNode->width > 1) {
		resetHierarchy(cNode->children[0]);
		resetHierarchy(cNode->children[1]);
		resetHierarchy(cNode->children[2]);
		resetHierarchy(cNode->children[3]);

		cNode->zmax	=	max(	max(cNode->children[0]->zmax,cNode->children[1]->zmax),
								max(cNode->children[2]->zmax,cNode->children[3]->zmax));
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	COcclusionCuller
// Method				:	reset
// Description			:	Reset the occlusion hierarchy
// Return Value			:	-
// Comments				:
void	COcclusionCuller::initToZero() {
	int				i;
	COcclusionNode	*cNode;
	COcclusionNode	**tNode	=	nodes;

	for (i=width*width;i>0;i--) {
		cNode		=	*tNode++;
		cNode->zmax	=	0;
	}
}










///////////////////////////////////////////////////////////////////////
// Class				:	COcclusionCuller
// Method				:	newNode
// Description			:	Allocate a new occlusion node
// Return Value			:	-
// Comments				:
COcclusionCuller::COcclusionNode	*COcclusionCuller::newNode(COcclusionNode *p,int w,int d,int nodeOffset,int x,int y) {
	// (globalMemory is checkpointed)
	COcclusionNode	*cNode	=	(COcclusionNode *) ralloc(sizeof(COcclusionNode),CRenderer::globalMemory);

	cNode->parent		=	p;
	cNode->width		=	w;

	nodeOffset -= (1<<d)*(1<<d);

	if (w > 1) {
		nodes[nodeOffset + (y<<d) + x] = cNode;

		cNode->children[0]	=	newNode(cNode,w >> 1,d+1,nodeOffset,(x << 1)		, (y << 1));
		cNode->children[1]	=	newNode(cNode,w >> 1,d+1,nodeOffset,(x << 1) + 1	, (y << 1));
		cNode->children[2]	=	newNode(cNode,w >> 1,d+1,nodeOffset,(x << 1) + 1	, (y << 1) + 1);
		cNode->children[3]	=	newNode(cNode,w >> 1,d+1,nodeOffset,(x << 1)		, (y << 1) + 1);

	} else {
		nodes[(y << depth) + x]	=	cNode;

		cNode->children[0]		=	NULL;
		cNode->children[1]		=	NULL;
		cNode->children[2]		=	NULL;
		cNode->children[3]		=	NULL;
	}

	return cNode;
}



///////////////////////////////////////////////////////////////////////
// Class				:	COcclusionCuller
// Method				:	probeRect
// Description			:	descover whether a region would be culled
// Return Value			:	-
// Comments				:
int COcclusionCuller::probeRect(int *xbound,int *ybound, int bw, int bh, int bl, int bt, float zmin) {

	int nodeOffset=0;
	int queryDepth = depth;
	int w=bw,h=bh;

	int xmin;
	int xmax;
	int ymin;
	int ymax;
	
	// search for a small enough query area, to keep query cost down
	// this has the nice property that large objects are less accurately
	// queried than small ones (where there are chance to be many)
	for(;queryDepth>0;queryDepth--) {

		xmin	=	xbound[0] - bl;
		xmax	=	xbound[1] - bl;
		ymin	=	ybound[0] - bt;
		ymax	=	ybound[1] - bt;

		xmin	=	xmin>>(depth-queryDepth);
		xmax	=	xmax>>(depth-queryDepth);
		ymin	=	ymin>>(depth-queryDepth);
		ymax	=	ymax>>(depth-queryDepth);

		// Clamp the bound in the current bucket
		xmin					=	max(xmin,0);
		ymin					=	max(ymin,0);
		
		// Notes:
		//		This is correct but inefficient due to querying
		//			xmax		=	min(xmax,(1<<queryDepth)-1);
		//			ymax		=	min(ymax,(1<<queryDepth)-1);
		// 		This is incorrect because it doesn't account for buckets straddling bucket edge
		//			xmax		=	min(xmax,(bw>>(depth-queryDepth))-1);
		//			ymax		=	min(ymax,(bh>>(depth-queryDepth))-1);
		//		We're using a recurrance, this
		// 			(bw*2+(1<<d))>>d , d = (depth-queryDepth)
		// 		is equivalent but probably slower
		
		xmax					=	min(xmax,w-1);
		ymax					=	min(ymax,h-1);

		// Something odd occurred, abort
		if (xmin > xmax) return FALSE;
		if (ymin > ymax) return FALSE;

		// terminate search if we find a sufficiently small area
		if ((xmax-xmin) <= 4) break;
		if ((ymax-ymin) <= 4) break;
	
		// update offset
		nodeOffset				+=	(1<<queryDepth)*(1<<queryDepth);
		
		// Deal with odd sized buckets at this depth
		h = (h+(h&1))>>1;
		w = (w+(w&1))>>1;
	}

	// now that we worked out the depth, do the query
	COcclusionNode **n = nodes + nodeOffset + (ymin<<queryDepth) + xmin;
	for(int y=ymin;y<=ymax;y++) {
		COcclusionNode **ne = n;
		for(int x=xmin;x<=xmax;x++) {
			
			if (zmin <= (*ne)->zmax) return TRUE;
			
			ne++;
		}
		n += 1<<queryDepth;
	}
	return FALSE;
}
