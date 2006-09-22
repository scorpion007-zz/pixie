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
//  File				:	points.h
//  Classes				:	CPoints
//  Description			:	Points primitive
//
////////////////////////////////////////////////////////////////////////
#ifndef POINTS_H
#define POINTS_H

#include "common/global.h"
#include "photonMap.h"
#include "ray.h"
#include "shading.h"
#include "pl.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CPoints
// Description			:	Implements a points primitive
// Comments				:
// Date last edited		:	10/8/2002
class	CPoints : public CSurface {

		///////////////////////////////////////////////////////////////////////
		// Class				:	CPointBase
		// Description			:	This class holds the memory for the points
		// Comments				:
		// Date last edited		:	10/8/2002
		class CPointBase {
		public:
							CPointBase()	{	refCount	=	0;							}
							~CPointBase()	{	variables->detach();	if (parameters != NULL) delete parameters;	if (vertex != NULL) delete vertex; }

			void			attach()		{	refCount++;									}
			void			detach()		{	if ((--refCount) == 0)	delete this;		}

			float			*vertex;				// The vertex data for the points
			CParameter		*parameters;			// The parameters for the points
			CVertexData		*variables;				// The vertex data
			float			maxSize;				// The maximum size of the point in camera space
			int				refCount;				// The reference count for the points
		};
public:
						CPoints(CAttributes *,CXform *,CPl *,int);
						CPoints(CAttributes *,CXform *,CPointBase *,int,const float **);
						~CPoints();

		void			bound(float *,float *) const;
		void			tesselate(CShadingContext *)	{	}
		void			dice(CShadingContext *);
		void			sample(int,int,float **,unsigned int &) const;
		int				moving() const { return (pl != NULL ? (pl->data1 !=NULL) : base->variables->moving);	}
		void			interpolate(int,float **) const;
		void			copy(CAttributes *,CXform *,CRendererContext *) const;

private:
		void			prep();

		int				numPoints;				// The number of points
		CPl				*pl;					// The parameter list
		vector			bmin,bmax;				// The bounding box

												// The variables below will only be ready after prep() is called

		const float		**points;				// Entry points to points

		CPointBase		*base;					// The point base
};

#endif






