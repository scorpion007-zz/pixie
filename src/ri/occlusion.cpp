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
	for (depth=0,width=1;width < w;depth++,width=width<<1);

	// (globalMemory is checkpointed)
	nodes			=	(COcclusionNode **) ralloc(width*width*sizeof(COcclusionNode *),CRenderer::globalMemory);
	root			=	newNode(NULL,width,0,0);
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
COcclusionCuller::COcclusionNode	*COcclusionCuller::newNode(COcclusionNode *p,int w,int x,int y) {
	// (globalMemory is checkpointed)
	COcclusionNode	*cNode	=	(COcclusionNode *) ralloc(sizeof(COcclusionNode),CRenderer::globalMemory);

	cNode->parent		=	p;
	cNode->width		=	w;

	if (w > 1) {
		cNode->children[0]	=	newNode(cNode,w >> 1,(x << 1)		, (y << 1));
		cNode->children[1]	=	newNode(cNode,w >> 1,(x << 1) + 1	, (y << 1));
		cNode->children[2]	=	newNode(cNode,w >> 1,(x << 1) + 1	, (y << 1) + 1);
		cNode->children[3]	=	newNode(cNode,w >> 1,(x << 1)		, (y << 1) + 1);
	} else {
		nodes[(y << depth) + x]	=	cNode;

		cNode->children[0]		=	NULL;
		cNode->children[1]		=	NULL;
		cNode->children[2]		=	NULL;
		cNode->children[3]		=	NULL;
	}

	return cNode;
}

