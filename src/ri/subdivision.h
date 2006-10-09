//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright � 1999 - 2003, Okan Arikan
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
//  File				:	subdivision.h
//  Classes				:	CSubdivision
//  Description			:	Implements a subdivision surface
//
////////////////////////////////////////////////////////////////////////
#ifndef SUBDIVISION_H
#define SUBDIVISION_H

#include "common/global.h"
#include "object.h"
#include "pl.h"


///////////////////////////////////////////////////////////////////////
// Class				:	CSubdivision
// Description			:	Implements a non-regular catmull-clark subdivision patch
// Comments				:	Regular patches are implemented as bi-cubic patches
// Date last edited		:	10/12/2002
class	CSubdivision : public CSurface {
public:
					CSubdivision(CAttributes *,CXform *,CVertexData *,CParameter *,int,float,float,float,float,double *);
					~CSubdivision();

	void			bound(float *,float *) const;
	void			tesselate(CShadingContext *);
	int				moving() const												{	return vertexData->moving;			}
	void			sample(int,int,float **,unsigned int &) const;
	void			interpolate(int,float **) const;

	CVertexData		*vertexData;	// The variables
	CParameter		*parameters;	// The parameters
	int				N;				// The valence
	float			*vertex;		// The vertex data
	float			uOrg,vOrg,uMult,vMult;
	vector			bmin,bmax;

private:
	void			projectVertices(float *,double *,int);
};

#endif



