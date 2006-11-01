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
//  File				:	hierarchy.h
//  Classes				:	CTracable
//							CVertex
//							CTriangle
//							CHierarchy
//  Description			:	The raytracing hierarchy
//
////////////////////////////////////////////////////////////////////////
#ifndef HIERARCHY_H
#define HIERARCHY_H

#include "common/global.h"
#include "common/containers.h"
#include "common/algebra.h"
#include "common/os.h"
#include "attributes.h"
#include "options.h"
#include "ray.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CTracable
// Description			:	Any object that can be raytraced must overload the following functions
// Comments				:
// Date last edited		:	3/18/2002
class	CTracable {
public:
	virtual	void	bound(float *,float *) const					=	0;
	virtual	int		intersect(CRay *)								=	0;
	virtual	int		intersect(const float *,const float *) const	=	0;

	int				ID;
};


///////////////////////////////////////////////////////////////////////
// Class				:	CVertex
// Description			:	A vertex of a triangle
// Comments				:
// Date last edited		:	3/18/2002
class	CVertex {
public:
	vector			P,N;
	float			u,v;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CMovingVertex
// Description			:	A vertex of a triangle
// Comments				:
// Date last edited		:	3/18/2002
class	CMovingVertex {
public:
	vector			P[2],N[2];
	float			u,v;
};


///////////////////////////////////////////////////////////////////////
// Class				:	CTriangle
// Description			:	A triangle
// Comments				:
// Date last edited		:	3/18/2002
class	CTriangle : public CTracable {
public:
					CTriangle();

	void			bound(float *,float *) const;
	int				intersect(CRay *);
	int				intersect(const float *,const float *) const;

	void			*v[3];		// Pointers to the vertices (v[0] contains the major axis, v[1] contains the face status, v[2] contains the front back)
	vector			N;
	float			d;
	CSurface		*object;
};


///////////////////////////////////////////////////////////////////////
// Class				:	CTriangle
// Description			:	A triangle
// Comments				:
// Date last edited		:	3/18/2002
class	CPtriangle : public CTriangle {
public:
					CPtriangle() : CTriangle() {}

	int				intersect(CRay *);
};

///////////////////////////////////////////////////////////////////////
// Class				:	CMovingTriangle
// Description			:	A moving triangle
// Comments				:
// Date last edited		:	3/18/2002
class	CMovingTriangle : public CTracable {
public:
					CMovingTriangle();

	void			bound(float *,float *) const;
	int				intersect(CRay *);
	int				intersect(const float *,const float *) const;

	void			*v[3];		// Pointers to the vertices (v[0] contains the majot axis, v[1] contains the face status)
	vector			N[2];
	float			d[2];
	CSurface		*object;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CMovingTriangle
// Description			:	A moving triangle
// Comments				:
// Date last edited		:	3/18/2002
class	CPmovingTriangle : public CMovingTriangle {
public:
					CPmovingTriangle() : CMovingTriangle() {}

	int				intersect(CRay *);
};

const	int		HIERARCHY_LEAF_NODE			=	0;		// The node is leaf
const	int		HIERARCHY_INTERNAL_NODE		=	1;		// The node is internal
const	int		HIERARCHY_UNCOMPUTED_NODE	=	2;		// The node is uncomputed
const	int		HIERARCHY_EMPTY_NODE		=	3;		// The node is empty (used with NULL)

///////////////////////////////////////////////////////////////////////
// Function				:	hierarchyIntersectBox
// Description			:	Return TRUE if a given non axis aligned box whose
//							corners are given in the boundingVertices array
//							intersects the given axis aligned box.
// Return Value			:	TRUE if it intersects, FALSE othervise
// Comments				:	Note that the corner indices are defined in object.h
// Date last edited		:	3/11/2001
inline	unsigned int		hierarchyIntersectBox(const float *bmin,const float *bmax,const float *normal) {
	vector	corner;


	initv(corner,bmin[COMP_X],bmin[COMP_Y],bmin[COMP_Z]);
	if ((dotvv(corner,normal)+normal[3]) < 0)
		return	FALSE;

	initv(corner,bmin[COMP_X],bmin[COMP_Y],bmax[COMP_Z]);
	if ((dotvv(corner,normal)+normal[3]) < 0)
		return	FALSE;

	initv(corner,bmin[COMP_X],bmax[COMP_Y],bmax[COMP_Z]);
	if ((dotvv(corner,normal)+normal[3]) < 0) 
		return	FALSE;

	initv(corner,bmin[COMP_X],bmax[COMP_Y],bmin[COMP_Z]);
	if ((dotvv(corner,normal)+normal[3]) < 0)
		return	FALSE;


	initv(corner,bmax[COMP_X],bmin[COMP_Y],bmin[COMP_Z]);
	if ((dotvv(corner,normal)+normal[3]) < 0)
		return	FALSE;

	initv(corner,bmax[COMP_X],bmin[COMP_Y],bmax[COMP_Z]);
	if ((dotvv(corner,normal)+normal[3]) < 0)
		return	FALSE;

	initv(corner,bmax[COMP_X],bmax[COMP_Y],bmax[COMP_Z]);
	if ((dotvv(corner,normal)+normal[3]) < 0)
		return	FALSE;

	initv(corner,bmax[COMP_X],bmax[COMP_Y],bmin[COMP_Z]);
	if ((dotvv(corner,normal)+normal[3]) < 0)
		return	FALSE;

	return	TRUE;
}

inline	unsigned int		hierarchyIntersectBox(const float *bmin,const float *bmax,const float *obmin,const float *obmax,const float *boundingPlanes) {
	unsigned int		i;

	// Do trivial rejection first
	if (intersectBox(obmin,obmax,bmin,bmax)) {

		// Try to find a seperating plane on the non-axis aligned box
		for (i=0;i<6;i++) {
			if (hierarchyIntersectBox(bmin,bmax,&boundingPlanes[i*4]))	return FALSE;
		}

		// We're in
		return	TRUE;
	}

	return FALSE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	COctreeNode
// Method				:	intersectBox
// Description			:	Does the vector from F to T intersect box (bmin,bmax)?
// Return Value			:	TRUE if it does, FALSE othervise
// Comments				:
// Date last edited		:	3/11/2001
inline	unsigned int		hierarchyIntersectBox(const float *bmin,const float *bmax,const float *F,const float *T,float &tmin,float &tmax) {
	float			tnear,tfar;
	float			t1,t2;
	unsigned int	i;

	tnear	=	tmin;
	tfar	=	tmax;

	for (i=0;i<3;i++) {
		if (F[i] == T[i]) {
			if ((F[i] > bmax[i]) || (F[i] < bmin[i])) return FALSE;
		} else {
			float	tmp	=	1 / (T[i] - F[i]);

			t1		=	(bmin[i] - F[i]) * tmp;
			t2		=	(bmax[i] - F[i]) * tmp;

			if (t1 < t2) {
				if (t1 > tnear)	tnear = t1;
				if (t2 < tfar)	tfar = t2;
			} else {
				if (t2 > tnear)	tnear = t2;
				if (t1 < tfar)	tfar = t1;
			}

			if (tnear > tfar) return FALSE;
		}
	}

	tmin	=	tnear;
	tmax	=	tfar;

	return TRUE;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CHierarchy
// Description			:	Encapsulates a hierarchy
// Comments				:
// Date last edited		:	3/18/2002
class	CHierarchy {
	///////////////////////////////////////////////////////////////////////
	// Class				:	CHLeaf
	// Description			:	Holds a hierarchy leaf
	// Comments				:
	// Date last edited		:	12/23/2001
	class	CHLeaf {		// 8 bytes
	public:
		int						numItems;				// Number of items in the leaf
		CTracable				**items;				// Items in the leaf
	};

	///////////////////////////////////////////////////////////////////////
	// Class				:	CHInternal
	// Description			:	Holds a hierarchy internal node
	// Comments				:
	// Date last edited		:	12/23/2001
	class	CHInternal {	// 16 bytes
	public:
		void					*front,*back;			// The front/back pointers
		float					splitCoordinate;		// The coordinate of the split
		int						splitAxis;				// 0,1,2
	};

	///////////////////////////////////////////////////////////////////////
	// Class				:	CHUncomputed
	// Description			:	Holds a hierarchy uncomputed node
	// Comments				:
	// Date last edited		:	12/23/2001
	class	CHUncomputed {	// 32 bytes
	public:
		int						numItems;				// The number of items intersecting the node
		CTracable				**items;				// List of items
		vector					bmin,bmax;				// The bounds of the node
		CHInternal				*parent;				// Parent of the node
		int						depth;					// Depth of the node
	};


	///////////////////////////////////////////////////////////////////////
	// Class				:	CHSingleStack
	// Description			:	Stack entry
	// Comments				:
	// Date last edited		:	12/23/2001
	class	CHStack {
	public:
		void					*node;
		float					tmin,tmax;
	};

public:
						CHierarchy(int,CTracable **,const float *,const float *,COptions *,CMemStack *mem);
						~CHierarchy();

	void				remove(const CTracable *,float *,float *);
	void				add(int,CTracable **);
	void				intersect(CRay *ray);
	int					collect(CTracable **,const float *,float);

private:
	void				deleteNode(void *cNode);
	void				*compute(CHUncomputed *cUncomputed);
	void				intersect(void *r,CRay *ray,float tmin,float tmax);
	void				add(void *node,CHInternal *parent,int depth,int numItems,CTracable **items,float *bmin,float *bmax);
	void				remove(void *node,const CTracable *item,float *bmin,float *bmax,float *ibmin,float *ibmax);

	CMemStack			*memory;					// The memory area we allocate the hierarchy from
	void				*root;						// Root node of the hierarchy
	vector				bmin,bmax;					// The bound of all the objects in the tree
	int					maxObjects;					// Maximum number of objects per leaf
	int					maxDepth;					// Maximum leaf depth
	CHStack				*singleStack;				// Traversal stack
	int					currentRayID;				// The global ray counter used for mailboxing
};


#endif


