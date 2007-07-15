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
//  File				:	pointHierarchy.h
//  Classes				:
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef POINTHIERARCHY_H
#define POINTHIERARCHY_H

#include "common/global.h"
#include "common/containers.h"
#include "map.h"
#include "texture3d.h"
#include "options.h"
#include "pointCloud.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CPointHierarchy
// Description			:	A hierarchy of points
// Comments				:
class	CPointHierarchy : public CTexture3d, public CMap<CPointCloudPoint> {

	///////////////////////////////////////////////////////////////////////
	// Class				:	CMapNode
	// Description			:	Encapsulates a node in the hierarchy
	// Comments				:
	class	CMapNode {
	public:
		vector		P,N;				// The center of the node
		vector		radiosity;			// The radiosity of the node
		float		dP,dN;				// The average radius and maximum normal deviation (cosine)
		int			child0,child1;		// The children indices (>=0 if internal nodes < if leaf)
	};


public:
							CPointHierarchy(const char *,const float *from,const float *to,FILE *);
							~CPointHierarchy();

	void					lookup(float *,const float *,const float *,const float *,const float *,CShadingContext *);
	void					store(const float *,const float *,const float *,float)	{	assert(FALSE);	}
	void					lookup(float *,const float *,const float *,float)		{	assert(FALSE);	}

protected:
	CArray<CMapNode>		nodes;					// This is where we keep the internal nodes
	CArray<float>			data;					// This is where we actually keep the data
	int						areaIndex;				// Index of the area variable
	int						radiosityIndex;			// Index of the radiosity variable

							// Functions used to construct the hierarchy
	void					computeHierarchy();
	int						average(int numItems,int *indices);
	int						cluster(int numItems,int *indices);

							// CView interface
	void					draw() { }
	void					bound(float *bmin,float *bmax) { }
};

#endif






