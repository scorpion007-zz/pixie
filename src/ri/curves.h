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
// Date last edited		:	10/8/2002
class	CCurve : public CSurface {
public:

	///////////////////////////////////////////////////////////////////////
	// Class				:	CBase
	// Description			:	This class holds the data about a single curve
	// Comments				:
	// Date last edited		:	10/8/2002
	class	CBase {
	public:
						CBase() {
							refCount	=	0;
						}

						~CBase() {
							delete [] vertex;
							variables->detach();
							if (parameters != NULL)	delete parameters;
						}

		void			attach()	{	refCount++;	}

		void			detach()	{	if ((--refCount) == 0) delete this;	}

		const CVariable	*sizeVariable;	// The size variable
		float			maxSize;		// The maximum size of the curve
		CVertexData		*variables;		// The variables for the curve
		CParameter		*parameters;	// Da parameters
		float			*vertex;		// Da vertex data
		int				refCount;		// Da ref count
	};
public:
					CCurve(CAttributes *,CXform *,CBase *,float,float,float,float);
					~CCurve();

	void			tesselate(CShadingContext *)	{	}
	int				moving() const												{	return base->variables->moving;	}
	void			interpolate(int,float **) const;
	void			dice(CShadingContext *);

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
// Date last edited		:	10/8/2002
class	CCubicCurve : public CCurve {
public:
					CCubicCurve(CAttributes *,CXform *,CBase *,float,float,float,float);
					~CCubicCurve();

	void			sample(int,int,float **,unsigned int &) const;
	void			bound(float *,float *) const;

protected:
	void			splitToChildren(CShadingContext *);
};

///////////////////////////////////////////////////////////////////////
// Class				:	CLinearCurves
// Description			:	Implements a linear primitive
// Comments				:
// Date last edited		:	10/8/2002
class	CLinearCurve : public CCurve {
public:
					CLinearCurve(CAttributes *,CXform *,CBase *,float,float,float,float);
					~CLinearCurve();

	void			sample(int,int,float **,unsigned int &) const;
	void			bound(float *,float *) const;

protected:
	void			splitToChildren(CShadingContext *);
};



///////////////////////////////////////////////////////////////////////
// Class				:	CCurvesMesh
// Description			:	Encapsulates a curves mesh
// Comments				:
// Date last edited		:	6/28/2001
class	CCurveMesh : public CObject {
public:
							CCurveMesh(CAttributes *,CXform *,CPl *,int,int,int,int *,int);
							~CCurveMesh();

		void				bound(float *,float *) const;
		void				copy(CAttributes *,CXform *,CRendererContext *) const;
		void				tesselate(CShadingContext *context);
		void				dice(CShadingContext *rasterizer);

private:
		void				create();

		CPl					*pl;
		int					numVertices;
		int					numCurves;
		int					*nverts;
		int					degree,wrap;
		vector				bmin,bmax;			// The bounding box in the original object coordinate system

		const CVariable		*sizeVariable;
		float				maxSize;

		CArray<CObject *>	*children;
};


void				curvesCreate(CAttributes *,CXform *,CPl *,int,int,int,int *,int,CRendererContext *);

#endif










