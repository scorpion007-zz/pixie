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
//  File				:	points.h
//  Classes				:	CPoints
//  Description			:	Points primitive
//
////////////////////////////////////////////////////////////////////////
#ifndef POINTS_H
#define POINTS_H

#include "common/global.h"
#include "ray.h"
#include "shading.h"
#include "surface.h"
#include "pl.h"
#include "refCounter.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CPoints
// Description			:	Implements a points primitive
// Comments				:
class	CPoints : public CSurface {

		///////////////////////////////////////////////////////////////////////
		// Class				:	CPointBase
		// Description			:	This class holds the memory for the points
		// Comments				:
		class CPointBase : public CRefCounter {
		public:
							CPointBase()	{	osCreateMutex(mutex);			}
							~CPointBase()	{	variables->detach();	if (parameters != NULL) delete parameters;	if (vertex != NULL) delete vertex; osDeleteMutex(mutex);	}

			float			*vertex;				// The vertex data for the points
			CParameter		*parameters;			// The parameters for the points
			CVertexData		*variables;				// The vertex data
			float			maxSize;				// The maximum size of the point in camera space
			TMutex			mutex;					// Holds the synchronization object
		};
public:
						CPoints(CAttributes *,CXform *,CPl *,int);
						CPoints(CAttributes *,CXform *,CPointBase *,int,const float **);
						~CPoints();

						// Object interface
		void			intersect(CShadingContext *,CRay *)	{	}
		void			dice(CShadingContext *);
		void			instantiate(CAttributes *,CXform *,CRendererContext *) const;

						// Surface interface
		void			sample(int,int,float **,float ***,unsigned int &) const;
		int				moving() const { return (pl != NULL ? (pl->data1 !=NULL) : base->variables->moving);	}
		void			interpolate(int,float **,float ***) const;
		

private:
		void			prep();

		int				numPoints;				// The number of points
		CPl				*pl;					// The parameter list

												// The variables below will only be ready after prep() is called

		const float		**points;				// Entry points to points

		CPointBase		*base;					// The point base
};

#endif

