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
// Date last edited		:	6/4/2003
class	CPatch : public CObject {
public:
							CPatch(CAttributes *,CXform *,CSurface *,float,float,float,float,int,int);
							~CPatch();

	void					dice(CShadingContext *);		// Split or render this object

private:
	void					splitToChildren(CShadingContext *,int);
	void					diceNew(CShadingContext *);
	int						diceStats(CShadingContext *,float *,float *,int,int,int &,int &);
	int						diceStats(CShadingContext *,float *,float *,int,int);

	int						depth;							// Depth of the patch
	int						minDepth;						// The minimum depth of the patch
	CSurface				*object;						// The object the surface belongs to
	float					umin,umax,vmin,vmax;			// The parametric extend of the surface
	int						udiv,vdiv;						// The split amounts
};


///////////////////////////////////////////////////////////////////////
// Class				:	CSurfaceGrid
// Description			:	Holds a piece of surface to be rendered
// Comments				:
// Date last edited		:	6/4/2003
class	CSurfaceGrid : public CObject {
public:
							CSurfaceGrid(CAttributes *,CXform *,CSurface *,float,float,float,float,int,int);
							~CSurfaceGrid();

	void					dice(CShadingContext *);		// Split or render this object

private:
	CSurface				*object;						// The object the surface belongs to
	float					umin,umax,vmin,vmax;			// The parametric extend of the surface
	int						udiv,vdiv;						// The split amounts
};

#endif




