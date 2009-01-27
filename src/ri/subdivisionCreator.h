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
class	CSubdivMesh : public CObject {
public:
							CSubdivMesh(CAttributes *a,CXform *x,CPl *c,int numFaces,int *numVerticesPerFace,int *vertexIndices,int ntags,const char **tags,int *nargs,int *intargs,float *floatargs);
							~CSubdivMesh();

	void					intersect(CShadingContext *,CRay *);
	void					dice(CShadingContext *rasterizer);
	void					instantiate(CAttributes *a,CXform *x,CRendererContext *c) const;

	int						moving() const {	return pl->data1 != NULL;	}

private:
	void					create(CShadingContext *context);

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
	TMutex					mutex;
};

#endif

