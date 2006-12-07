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
class	CBilinearPatch : public CSurface {
public:
						CBilinearPatch(CAttributes *,CXform *,CVertexData *,CParameter *,float,float,float,float,float *);
						~CBilinearPatch();

		void			intersect(CShadingContext *,CRay *);
		void			instantiate(CAttributes *,CXform *,CRendererContext *) const {	assert(FALSE);	}

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
class	CBicubicPatch : public CSurface {
public:
						CBicubicPatch(CAttributes *,CXform *,CVertexData *,CParameter *,float,float,float,float,float *,const float *uBasis=NULL,const float *vBasis=NULL);
						~CBicubicPatch();

		void			instantiate(CAttributes *,CXform *,CRendererContext *) const {	assert(FALSE);	}

		int				moving() const												{	return variables->moving;			}
		void			sample(int,int,float **,unsigned int &) const;
		void			interpolate(int,float **) const;

private:
		void			computeVertexData(float *,const float *,int,const float *,const float *);

		CVertexData		*variables;
		CParameter		*parameters;
		float			*vertex;
		float			uOrg,vOrg,uMult,vMult;				// The parametric range of the patch
};

///////////////////////////////////////////////////////////////////////
// Class				:	CNURBSPatch
// Description			:	Encapsulates a NURBS patch
// Comments				:
class	CNURBSPatch : public CSurface {
public:
						CNURBSPatch(CAttributes *,CXform *,CVertexData *,CParameter *,int,int,float *,float *,float *);
						~CNURBSPatch();

		void			instantiate(CAttributes *,CXform *,CRendererContext *) const	{	assert(FALSE);	}

		int				moving() const												{	return variables->moving;			}
		void			sample(int,int,float **,unsigned int &) const;
		void			interpolate(int,float **) const;

private:
		void			precompBasisCoefficients(double *,unsigned int,unsigned int,unsigned int,const float *);
		void			precomputeVertexData(float *,const double *,const double *,float *,int);

		CVertexData		*variables;
		CParameter		*parameters;
		float			*vertex;
		int				uOrder,vOrder;
		float			uOrg,vOrg,uMult,vMult;
};














///////////////////////////////////////////////////////////////////////
// Class				:	CPatchMesh
// Description			:	Encapsulates a patch mesh
// Comments				:
class	CPatchMesh : public CObject {
public:
							CPatchMesh(CAttributes *,CXform *,CPl *,int,int,int,int,int);
							~CPatchMesh();

		void				intersect(CShadingContext *,CRay *);
		void				dice(CShadingContext *rasterizer);
		void				instantiate(CAttributes *,CXform *,CRendererContext *) const;

private:
		void				create(CShadingContext *context);

		CPl					*pl;
		int					degree;
		int					uVertices,vVertices,uWrap,vWrap;
};



///////////////////////////////////////////////////////////////////////
// Class				:	CNURBSPatchMesh
// Description			:	Encapsulates a NURBS patch mesh
// Comments				:
class	CNURBSPatchMesh : public CObject {
public:
							CNURBSPatchMesh(CAttributes *,CXform *,CPl *,int,int,int,int,float *,float *);
							~CNURBSPatchMesh();

		void				intersect(CShadingContext *,CRay *);
		void				dice(CShadingContext *rasterizer);
		void				instantiate(CAttributes *,CXform *,CRendererContext *) const;

private:
		void				create(CShadingContext *context);

		CPl					*pl;
		int					uVertices,vVertices,uOrder,vOrder;
		float				*uKnots,*vKnots;
};

#endif






