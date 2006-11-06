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
//  File				:	polygons.h
//  Classes				:	CPolygonMesh
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef POLYGONS_H
#define POLYGONS_H

#include "common/global.h"
#include "object.h"
#include "patches.h"
#include "pl.h"

// Some forward declerations
class	CPolygonTriangle;

///////////////////////////////////////////////////////////////////////
// Class				:	CPolygonMesh
// Description			:	Encapsulates a polygon mesh
// Comments				:
// Date last edited		:	6/28/2001
class	CPolygonMesh : public CObject {
public:
							CPolygonMesh(CAttributes *,CXform *,CPl *,int,int *,int *,int *);
							~CPolygonMesh();

		void				intersect(CShadingContext *,CRay *);
		void				dice(CShadingContext *);
		void				instantiate(CAttributes *,CXform *,CRendererContext *) const;

private:
		void				triangulate();

		CPl					*pl;
		int					npoly,nloops,nverts;
		int					*nholes,*nvertices,*vertices;

		unsigned int		parameters;

		friend	class		CPolygonTriangle;
		friend	class		CPolygonQuad;
};



///////////////////////////////////////////////////////////////////////
// Class				:	CPolygonTriangle
// Description			:	This class is used during the tesselation
//							Every polygon is first triangulated to obtain a 
//							meaningful parameter space. Then individual triangles
//							(this class) is tesselated into microtriangles
// Comments				:
// Date last edited		:	6/28/2001
class	CPolygonTriangle : public CSurface {
public:
							CPolygonTriangle(CAttributes *,CXform *,CPolygonMesh *);
							~CPolygonTriangle();

		void				intersect(CShadingContext *,CRay *);
		void				instantiate(CAttributes *,CXform *,CRendererContext *) const	{	assert(FALSE);	}
	

		int					moving() const												{	return mesh->pl->data1 != NULL;		}
		void				sample(int,int,float **,unsigned int &) const;
		void				interpolate(int,float **) const;


		CPolygonMesh		*mesh;
		int					v0,v1,v2;		// The vertex indices
		int					fv0,fv1,fv2;	// The facevarying indices
		int					uniform;		// The uniform index
};

///////////////////////////////////////////////////////////////////////
// Class				:	CPolygonQuad
// Description			:	Holds a bilinear polygon
// Comments				:
// Date last edited		:	6/28/2001
class	CPolygonQuad : public CSurface {
public:
							CPolygonQuad(CAttributes *,CXform *,CPolygonMesh *);
							~CPolygonQuad();

		void				intersect(CShadingContext *,CRay *);
		void				instantiate(CAttributes *,CXform *,CRendererContext *) const	{	assert(FALSE);	}

		int					moving() const												{	return mesh->pl->data1 != NULL;		}
		void				sample(int,int,float **,unsigned int &) const;
		void				interpolate(int,float **) const;


		CPolygonMesh		*mesh;
		int					v0,v1,v2,v3;		// The vertex indices
		int					fv0,fv1,fv2,fv3;	// The facevarying indices
		int					uniform;			// The uniform index
};
#endif





