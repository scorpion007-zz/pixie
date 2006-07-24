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
//  File				:	subdivisionCreator.h
//  Classes				:	
//  Description			:	The code that does the subdivision and generates the bicubic patches
//
////////////////////////////////////////////////////////////////////////
#ifndef SUBDIVCREATOR_H
#define SUBDIVCREATOR_H

#include "common/global.h"		// The global header file
#include "attributes.h"
#include "xform.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CSubdivMesh
// Description			:	Holds a subdivision surface mesh
// Comments				:
// Date last edited		:	5/30/2003
class	CSubdivMesh : public CObject {
public:
							CSubdivMesh(CAttributes *a,CXform *x,CPl *c,int numFaces,int *numVerticesPerFace,int *vertexIndices,int ntags,char **tags,int *nargs,int *intargs,float *floatargs);
							~CSubdivMesh();

	void					bound(float *bmi,float *bma) const;
	void					tesselate(CShadingContext *context);
	void					dice(CShadingContext *rasterizer);
	int						moving() const {	return pl->data1 != NULL;	}
	void					copy(CAttributes *a,CXform *x,CRendererContext *c) const;

private:
	void					create();

	CPl						*pl;
	int						numFaces;
	int						numVertices;
	int						*numVerticesPerFace;
	int						*vertexIndices;
	int						ntags;
	char					**tags;
	int						*nargs;
	int						*intargs;
	float					*floatargs;
	vector					bmin,bmax;
	CArray<CObject *>		*objects;
};

#endif
