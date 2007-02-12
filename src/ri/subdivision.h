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
class	CSubdivision : public CSurface {
public:
					CSubdivision(CAttributes *,CXform *,CVertexData *,CParameter *,int,float,float,float,float,float *);
					~CSubdivision();

	void			instantiate(CAttributes *,CXform *,CRendererContext *) const	{	assert(FALSE);	}

	int				moving() const												{	return vertexData->moving;			}
	void			sample(int,int,float **,float ***,unsigned int &) const;
	void			interpolate(int,float **,float ***) const;

	CVertexData		*vertexData;	// The variables
	CParameter		*parameters;	// The parameters
	int				N;				// The valence
	float			*vertex;		// The vertex data
	float			uOrg,vOrg,uMult,vMult;

private:
	void			projectVertices(float *,float *,int);
};

#endif

