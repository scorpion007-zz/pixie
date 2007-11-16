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

						// CObject interface
		void			intersect(CShadingContext *,CRay *);
		void			instantiate(CAttributes *,CXform *,CRendererContext *) const {	assert(FALSE);	}

						// CSurface interface
		int				moving() const {	return variables->moving;			}
		void			sample(int,int,float **,float ***,unsigned int &) const;
		void			interpolate(int,float **,float ***) const;

private:
		CVertexData		*variables;						// The variables for the patch
		CParameter		*parameters;					// The parameters for the patch
		float			*vertex;						// The vertex data
		float			uMult,vMult,uOrg,vOrg;			// The parametric range of the patch
};


///////////////////////////////////////////////////////////////////////
// Class				:	CBicubicPatch
// Description			:	Encapsulates a bicubic patch
// Comments				:
class	CBicubicPatch : public CSurface {
public:
						CBicubicPatch(CAttributes *,CXform *,CVertexData *,CParameter *,float,float,float,float,float *,const float *uBasis=NULL,const float *vBasis=NULL);
						~CBicubicPatch();

						// CObject interface
		void			instantiate(CAttributes *,CXform *,CRendererContext *) const {	assert(FALSE);	}

						// CSurface interface
		int				moving() const	{	return variables->moving;			}
		void			sample(int,int,float **,float ***,unsigned int &) const;
		void			interpolate(int,float **,float ***) const;

private:
		void			computeVertexData(float *,const float *,int,const float *,const float *);

		CVertexData		*variables;						// Variables for the patch
		CParameter		*parameters;					// Parameters for the patch
		float			*vertex;						// The vertex data
		float			uOrg,vOrg,uMult,vMult;			// The parametric range of the patch
};

///////////////////////////////////////////////////////////////////////
// Class				:	CNURBSPatch
// Description			:	Encapsulates a NURBS patch
// Comments				:
class	CNURBSPatch : public CSurface {
public:
						CNURBSPatch(CAttributes *,CXform *,CVertexData *,CParameter *,int,int,float *,float *,float *);
						~CNURBSPatch();

						// CObject interface
		void			instantiate(CAttributes *,CXform *,CRendererContext *) const	{	assert(FALSE);	}

						// CSurface interface
		int				moving() const	{	return variables->moving;			}
		void			sample(int,int,float **,float ***,unsigned int &) const;
		void			interpolate(int,float **,float ***) const;

		int				getDicingStats(int depth, int &minDivU,int &minDivV) const { minDivU = max(uOrder-1-depth,1); minDivV = max(vOrder-1-depth,1); return 0; }

private:
		void			precompBasisCoefficients(double *,unsigned int,unsigned int,unsigned int,const float *);
		void			precomputeVertexData(double *,const double *,const double *,float *,int);

		CVertexData		*variables;						// The variable data
		CParameter		*parameters;					// The parameters for this patch
		double			*vertex;						// The vertex data
		int				uOrder,vOrder;					// The order of the patch
		float			uOrg,vOrg,uMult,vMult;			// The parametric range of the patch
};














///////////////////////////////////////////////////////////////////////
// Class				:	CPatchMesh
// Description			:	Encapsulates a patch mesh
// Comments				:
class	CPatchMesh : public CObject {
public:
							CPatchMesh(CAttributes *,CXform *,CPl *,int,int,int,int,int);
							~CPatchMesh();

							// CObject interface
		void				intersect(CShadingContext *,CRay *);
		void				dice(CShadingContext *rasterizer);
		void				instantiate(CAttributes *,CXform *,CRendererContext *) const;

private:
		void				create(CShadingContext *context);

		CPl					*pl;
		int					degree;
		int					uVertices,vVertices,uWrap,vWrap;
		TMutex				mutex;
};



///////////////////////////////////////////////////////////////////////
// Class				:	CNURBSPatchMesh
// Description			:	Encapsulates a NURBS patch mesh
// Comments				:
class	CNURBSPatchMesh : public CObject {
public:
							CNURBSPatchMesh(CAttributes *,CXform *,CPl *,int,int,int,int,float *,float *);
							~CNURBSPatchMesh();

							// CObject interface
		void				intersect(CShadingContext *,CRay *);
		void				dice(CShadingContext *rasterizer);
		void				instantiate(CAttributes *,CXform *,CRendererContext *) const;

private:
		void				create(CShadingContext *context);

		CPl					*pl;
		int					uVertices,vVertices,uOrder,vOrder;
		float				*uKnots,*vKnots;
		TMutex				mutex;
};

#endif

