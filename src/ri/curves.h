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
//  File				:	curves.h
//  Classes				:	CCurve
//  Description			:	Curve primitive
//
////////////////////////////////////////////////////////////////////////
#ifndef CURVES_H
#define CURVES_H

#include "common/global.h"
#include "object.h"
#include "shading.h"
#include "pl.h"


///////////////////////////////////////////////////////////////////////
// Class				:	CCubicCurves
// Description			:	Implements a curve primitive
// Comments				:
class	CCurve : public CSurface {
public:

					///////////////////////////////////////////////////////////////////////
					// Class				:	CBase
					// Description			:	This class holds the data about a single curve
					// Comments				:
					class	CBase : public CRefCounter  {
					public:
										CBase() {
										}

										~CBase() {
											delete [] vertex;
											variables->detach();
											if (parameters != NULL)	delete parameters;
										}

						int				sizeEntry;		// The size variable entry
						float			maxSize;		// The maximum size of the curve
						CVertexData		*variables;		// The variables for the curve
						CParameter		*parameters;	// Da parameters
						float			*vertex;		// Da vertex data
					};

public:
					CCurve(CAttributes *,CXform *,CBase *,float,float,float,float);
					~CCurve();

					// Object interface
	void			dice(CShadingContext *);
	void			instantiate(CAttributes *,CXform *,CRendererContext *) const	{	assert(FALSE);	}

					// Surface interface
	int				moving() const													{	return base->variables->moving;	}
	void			interpolate(int,float **,float ***) const;

protected:
	virtual	void	splitToChildren(CShadingContext *)	=	0;

	CBase			*base;
	float			vmin,vmax;		// The parametric range of the curves
	float			gvmin,gvmax;	// The global vmin/vmax
};

///////////////////////////////////////////////////////////////////////
// Class				:	CCubicCurves
// Description			:	Implements a curve primitive
// Comments				:
class	CCubicCurve : public CCurve {
public:
					CCubicCurve(CAttributes *,CXform *,CBase *,float,float,float,float);
					~CCubicCurve();

					// Surface interface
	void			sample(int,int,float **,float ***,unsigned int &) const;

protected:
	void			splitToChildren(CShadingContext *);
};

///////////////////////////////////////////////////////////////////////
// Class				:	CLinearCurves
// Description			:	Implements a linear primitive
// Comments				:
class	CLinearCurve : public CCurve {
public:
					CLinearCurve(CAttributes *,CXform *,CBase *,float,float,float,float);
					~CLinearCurve();

					// Surface interface
	void			sample(int,int,float **,float ***,unsigned int &) const;

protected:
	void			splitToChildren(CShadingContext *);
};



///////////////////////////////////////////////////////////////////////
// Class				:	CCurvesMesh
// Description			:	Encapsulates a curves mesh
// Comments				:
class	CCurveMesh : public CObject {
public:
							CCurveMesh(CAttributes *,CXform *,CPl *,int,int,int,int *,int);
							~CCurveMesh();

							// Object interface
		void				intersect(CShadingContext *,CRay *)	{	}
		void				dice(CShadingContext *rasterizer);
		void				instantiate(CAttributes *,CXform *,CRendererContext *) const;
		

private:
		void				create(CShadingContext *context);

		CPl					*pl;
		int					numVertices;
		int					numCurves;
		int					*nverts;
		int					degree,wrap;
		TMutex				mutex;

		const CVariable		*sizeVariable;
		float				maxSize;
};


void				curvesCreate(CAttributes *,CXform *,CPl *,int,int,int,int *,int,CRendererContext *);

#endif

