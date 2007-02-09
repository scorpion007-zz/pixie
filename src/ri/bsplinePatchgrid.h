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
//  File				:	bsplinePatchgrid.h
//  Classes				:	
//  Description			:	This implements a grid of bicubic b-spline patches
//
////////////////////////////////////////////////////////////////////////
#ifndef BPATCHGRID_H
#define BPATCHGRID_H

#include "common/global.h"
#include "object.h"
#include "pl.h"


///////////////////////////////////////////////////////////////////////
// Class				:	CBSplinePatchGrid
// Description			:	Implements a non-regular catmull-clark subdivision patch
// Comments				:	This is valid for irregular patches away from the border
class	CBSplinePatchGrid : public CSurface {
public:
					CBSplinePatchGrid(CAttributes *,CXform *,CVertexData *,CParameter *,int,int,float,float,float,float,float *);
					~CBSplinePatchGrid();

					// Object interface
	void			instantiate(CAttributes *,CXform *,CRendererContext *) const	{	assert(FALSE);	}

					// Surface interface
	int				moving() const													{	return variables->moving;			}
	void			sample(int,int,float **,float ***,unsigned int &) const;
	void			interpolate(int,float **,float ***) const;

	CVertexData		*variables;					// The variables
	CParameter		*parameters;				// The parameters

	float			*vertex;					// The vertex data (premultiplied Bu*G*Bu')
	float			uOrg,vOrg,uMult,vMult;		// The u,v ranges
	int				uVertices,vVertices;		// The number of samples in u and v
};

#endif

