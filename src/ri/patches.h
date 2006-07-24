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
//  File				:	patches.h
//  Classes				:	CPointDB
//							CBilinearPatchMesh
//							CBicubicPatchMesh
//  Description			:	Some geometry classes
//
////////////////////////////////////////////////////////////////////////
#ifndef PATCHES_H
#define PATCHES_H

#include "common/global.h"
#include "object.h"
#include "memory.h"
#include "pl.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CBilinearPatch
// Description			:	Encapsulates a bilinear patch
// Comments				:
// Date last edited		:	6/28/2001
class	CBilinearPatch : public CSurface {
public:
						CBilinearPatch(CAttributes *,CXform *,CVertexData *,CParameter *,float,float,float,float,double *);
						~CBilinearPatch();

		void			bound(float *,float *) const;
		void			tesselate(CShadingContext *);
		int				moving() const												{	return variables->moving;			}
		void			sample(int,int,float **,unsigned int &) const;
		void			interpolate(int,float **) const;

private:
		CVertexData		*variables;
		CParameter		*parameters;
		float			*vertex;
		float			uMult,vMult,uOrg,vOrg;				// The parametric range of the patch
};


///////////////////////////////////////////////////////////////////////
// Class				:	CBicubicPatch
// Description			:	Encapsulates a bicubic patch
// Comments				:
// Date last edited		:	6/28/2001
class	CBicubicPatch : public CSurface {
public:
						CBicubicPatch(CAttributes *,CXform *,CVertexData *,CParameter *,float,float,float,float,double *);
						~CBicubicPatch();

		void			bound(float *,float *) const;
		void			tesselate(CShadingContext *);
		int				moving() const												{	return variables->moving;			}
		void			sample(int,int,float **,unsigned int &) const;
		void			interpolate(int,float **) const;

private:
		void			computeVertexData(double *,const double *,int);

		CVertexData		*variables;
		CParameter		*parameters;
		double			*vertex;
		vector			bmin,bmax;							// The original bounding box
		float			uOrg,vOrg,uMult,vMult;				// The parametric range of the patch
};

///////////////////////////////////////////////////////////////////////
// Class				:	CNURBSPatch
// Description			:	Encapsulates a NURBS patch
// Comments				:
// Date last edited		:	6/28/2001
class	CNURBSPatch : public CSurface {
public:
						CNURBSPatch(CAttributes *,CXform *,CVertexData *,CParameter *,int,int,float *,float *,double *);
						~CNURBSPatch();

		void			bound(float *,float *) const;
		void			tesselate(CShadingContext *);
		int				moving() const												{	return variables->moving;			}
		void			sample(int,int,float **,unsigned int &) const;
		void			interpolate(int,float **) const;

private:
		void			precompBasisCoefficients(double *,unsigned int,unsigned int,unsigned int,const float *);
		void			precomputeVertexData(double *,const double *,const double *,double *,int);

		CVertexData		*variables;
		CParameter		*parameters;
		double			*vertex;							// These are double precision to reduce roundoff errors
		vector			bmin,bmax;
		int				uOrder,vOrder;
		float			uOrg,vOrg,uMult,vMult;
};














///////////////////////////////////////////////////////////////////////
// Class				:	CPatchMesh
// Description			:	Encapsulates a patch mesh
// Comments				:
// Date last edited		:	6/28/2001
class	CPatchMesh : public CObject {
public:
							CPatchMesh(CAttributes *,CXform *,CPl *,int,int,int,int,int);
							~CPatchMesh();

		void				bound(float *,float *) const;
		void				copy(CAttributes *,CXform *,CRendererContext *) const;
		void				tesselate(CShadingContext *context);
		void				dice(CShadingContext *rasterizer);

private:
		void				create();

		CPl					*pl;
		int					degree;
		int					uVertices,vVertices,uWrap,vWrap;
		vector				bmin,bmax;			// The bounding box in the original object coordinate system
		CArray<CObject *>	*children;
};



///////////////////////////////////////////////////////////////////////
// Class				:	CNURBSPatchMesh
// Description			:	Encapsulates a NURBS patch mesh
// Comments				:
// Date last edited		:	6/28/2001
class	CNURBSPatchMesh : public CObject {
public:
							CNURBSPatchMesh(CAttributes *,CXform *,CPl *,int,int,int,int,float *,float *);
							~CNURBSPatchMesh();

		void				bound(float *,float *) const;
		void				copy(CAttributes *,CXform *,CRendererContext *) const;
		void				tesselate(CShadingContext *context);
		void				dice(CShadingContext *rasterizer);

private:
		void				create();

		CPl					*pl;
		int					uVertices,vVertices,uOrder,vOrder;
		float				*uKnots,*vKnots;
		vector				bmin,bmax;			// The bounding box in the original object coordinate system
		CArray<CObject *>	*children;
};

#endif






