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
//  File				:	patchgrid.h
//  Classes				:	
//  Description			:	This implements a grid of bilinear patches
//
////////////////////////////////////////////////////////////////////////
#ifndef PATCHGRID_H
#define PATCHGRID_H

#include "common/global.h"
#include "object.h"
#include "pl.h"


///////////////////////////////////////////////////////////////////////
// Class				:	CPatchGrid
// Description			:	Implements a non-regular catmull-clark subdivision patch
// Comments				:	Regular patches are implemented as bi-cubic patches
// Date last edited		:	5/30/2003
class	CPatchGrid : public CSurface {
public:
					CPatchGrid(CAttributes *,CXform *,CVertexData *,CParameter *,int,int,int,int,int,int,double *);
					~CPatchGrid();

	void			bound(float *,float *) const;
	void			tesselate(CShadingContext *);
	int				moving() const												{	return variables->moving;			}
	void			sample(int,int,float **,unsigned int &) const;
	void			interpolate(int,float **) const;

	CVertexData		*variables;		// The variables
	CParameter		*parameters;

	float			*vertex;
	float			*Pu,*Pv;
	vector			bmin,bmax;
	int				nu,nv;			// The number of samples in u and v
};

#endif
