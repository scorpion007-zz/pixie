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
class	CPatchGrid : public CSurface {
public:
					CPatchGrid(CAttributes *,CXform *,CVertexData *,CParameter *,int,int,int,int,int,int,float *);
					~CPatchGrid();

					// Object interface
	void			instantiate(CAttributes *,CXform *,CRendererContext *) const	{	assert(FALSE);	}

					// Surface interface
	int				moving() const												{	return variables->moving;			}
	void			sample(int,int,float **,float ***,unsigned int &) const;
	void			interpolate(int,float **,float ***) const;

	CVertexData		*variables;		// The variables
	CParameter		*parameters;

	float			*vertex;
	float			*Pu,*Pv;
	int				nu,nv;			// The number of samples in u and v
};

#endif

