//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright © 1999 - 2003, Okan Arikan
//
// Contact: okan@cs.utexas.edu
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
//  File				:	surface.h
//  Classes				:	CSurface
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef SURFACE_H
#define SURFACE_H

#include "common/global.h"
#include "object.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CPatch
// Description			:	Encapsulates a piece of 2D surface
// Comments				:
class	CPatch : public CObject {
public:
							CPatch(CAttributes *a,CXform *x,CSurface *o,float umin,float umax,float vmin,float vmax,int depth,int minDepth);
							~CPatch();


	void					intersect(CShadingContext *,CRay *)	{	assert(FALSE);	}
	void					dice(CShadingContext *);		// Split or render this object
	void					instantiate(CAttributes *,CXform *,CRendererContext *) const { assert(FALSE);	}

private:
	void					splitToChildren(CShadingContext *,int);

	int						depth;							// Depth of the patch
	int						minDepth;						// The minimum depth of the patch
	CSurface				*object;						// The object the surface belongs to
	float					umin,umax,vmin,vmax;			// The parametric extend of the surface
	int						udiv,vdiv;						// The split amounts
};




///////////////////////////////////////////////////////////////////////
// Class				:	CTesselationPatch
// Description			:	Encapsulates a piece of 2D surface
// Comments				:
class	CTesselationPatch : public CObject {

	struct CSubTesselation {
		float					*P;						// The P
		int						size;					// The size (in bytes) of the grid
		int						lastRefNumber;			// Last time we accessed this grid
		CSubTesselation			*next,*prev;			// To maintain the linked list	
	};
	
	
public:
							CTesselationPatch(CAttributes *a,CXform *x,CSurface *o,float umin,float umax,float vmin,float vmax,char depth,char minDepth,float r);
							~CTesselationPatch();


	void					intersect(CShadingContext *,CRay *);
	void					dice(CShadingContext *) { assert(FALSE); }
	void					instantiate(CAttributes *,CXform *,CRendererContext *) const { assert(FALSE);	}

	void					initTesselation(CShadingContext *context);
	
private:
	
	CSubTesselation*		tesselate(CShadingContext *context,char div,int estimateOnly);
	void					splitToChildren(CShadingContext *context);	
	
	char					depth;							// Depth of the patch
	char					minDepth;						// The minimum depth of the patch
	CSurface				*object;						// The object the surface belongs to
	float					umin,umax,vmin,vmax;			// The parametric extend of the surface
	
	float					rmax;
	
	CSubTesselation			*tesselations[3];
};

#endif




