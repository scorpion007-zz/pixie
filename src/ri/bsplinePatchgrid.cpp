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
//  File				:	bsplinePatchgrid.cpp
//  Classes				:	
//  Description			:	Patchgrid implementation
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "bsplinePatchgrid.h"
#include "object.h"
#include "shading.h"
#include "memory.h"
#include "stats.h"
#include "patchUtils.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CBSplinePatchGrid
// Method				:	CBSplinePatchGrid
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	01/23/2006
CBSplinePatchGrid::CBSplinePatchGrid(CAttributes *a,CXform *x,CVertexData *var,CParameter *p,int nu,int nv,float uOrg,float vOrg,float uMult,float vMult,double *ve) : CSurface(a,x) {
	int				numVertices;
	const int		vertexSize	=	var->vertexSize;

	stats.numGprims++;
	stats.gprimMemory	+=	sizeof(CBSplinePatchGrid);

	variables			=	var;
	variables->attach();

	parameters			=	p;

	uVertices	=	nu;
	vVertices	=	nv;
	this->uOrg	=	uOrg;
	this->vOrg	=	vOrg;
	this->uMult	=	uMult;
	this->vMult	=	vMult;

	numVertices	=	(nu*nv);
	
	int				i,j,k;
	matrix			ut,bsplinebasis;
	double			tmp[16];

	const int 		upatches	=	uVertices - 3;
	const int	 	vpatches	=	vVertices - 3;

	initv(bmin,C_INFINITY,C_INFINITY,C_INFINITY);
	initv(bmax,-C_INFINITY,-C_INFINITY,-C_INFINITY);
	
	// Note that u basis and v basis are swapped to take the transpose into account done during the precomputation
	// Note also that we could use the B-spline basis to bound the curve, but Bezier bound is tighter
	for (i=0;i<4;i++)
		for (j=0;j<4;j++)
			bsplinebasis[element(i,j)]	=	RiBSplineBasis[j][i];
	transposem(ut,bsplinebasis);
	mulmmd(geometryV,invBezier,ut);
	mulmmd(geometryU,bsplinebasis,invBezier);
	
	// alloc off upatches*vpatches*16*vertexSize worth of data
	const int	vs			=	(variables->moving ? vertexSize*2 : vertexSize);
	vertex					=	new double[vs*16*upatches*vpatches];
	stats.gprimMemory		+=	vs*16*upatches*vpatches*sizeof(double);
	
	for (i=0;i<vpatches;i++) {
		for (j=0;j<upatches;j++) {
			int			r,c;
			double *patchData = vertex + (i*upatches + j)*16*vertexSize;

			// Fill in the geometry matrices
			for (r=0;r<4;r++) {
				int					y	=	(r + i) % vVertices;
				for (c=0;c<4;c++) {
					int				x	=	(c + j) % uVertices;
					const double	*d	=	ve + (y*uVertices+x)*vs;

					for	(k=0;k<vertexSize;k++) {
						patchData[16*k + element(r,c)]		=	*d++;
					}
				}
			}

			// add to bounds
			makeCubicBound(bmin,bmax,patchData+0*16,patchData+1*16,patchData+2*16);
			
			// precompute B*G*B' and stash it
			for	(k=0;k<vertexSize;k++) {
				mulmmd(tmp,ut,patchData);
				mulmmd(patchData,tmp,bsplinebasis);
				patchData += 16;
			}

			// do the same for moving points
			if (variables->moving) {
				patchData = vertex + (upatches*vpatches + i*upatches + j)*16*vertexSize;

				for (r=0;r<4;r++) {
					int					y	=	(r + i) % vVertices;
					for (c=0;c<4;c++) {
						int				x	=	(c + j) % uVertices;
						const double	*d	=	ve + vertexSize + (y*uVertices+x)*vs;
						
						for	(k=0;k<vertexSize;k++) {
							patchData[16*k + element(r,c)]		=	*d++;
						}
					}
				}

				// add to bounds
				makeCubicBound(bmin,bmax,patchData+0*16,patchData+1*16,patchData+2*16);

				// precompute B*G*B' and stash it
				for	(k=0;k<vertexSize;k++) {
					mulmmd(tmp,ut,patchData);
					mulmmd(patchData,tmp,bsplinebasis);
					patchData += 16;
				}
			}
		}
	}
	
	makeBound(bmin,bmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CBSplinePatchGrid
// Method				:	~CBSplinePatchGrid
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	01/23/2006
CBSplinePatchGrid::~CBSplinePatchGrid() {
	delete [] vertex;	stats.gprimMemory	-=	(variables->moving ? variables->vertexSize*2 : variables->vertexSize)*(uVertices-3)*(vVertices-3)*sizeof(double)*16;

	variables->detach();

	if (parameters != NULL)	delete parameters;

	stats.numGprims--;
	stats.gprimMemory	-=	sizeof(CBSplinePatchGrid);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CBSplinePatchGrid
// Method				:	bound
// Description			:	See object.h
// Return Value			:	-
// Comments				:
// Date last edited		:	01/23/2006
void		CBSplinePatchGrid::bound(float *bmi,float *bma) const {
	movvv(bmi,bmin);
	movvv(bma,bmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CBSplinePatchGrid
// Method				:	tesselate
// Description			:	See object.h
// Return Value			:	-
// Comments				:	-
// Date last edited		:	6/21/2001
void	CBSplinePatchGrid::tesselate(CShadingContext *context) {
	context->tesselate2D(this);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CBSplinePatchGrid
// Method				:	sample
// Description			:	See object.h
// Return Value			:	-
// Comments				:
// Date last edited		:	01/23/2006
void		CBSplinePatchGrid::sample(int start,int numVertices,float **varying,unsigned int &up) const {
	int					i,j,k;
	const float			*u						=	varying[VARIABLE_U]+start;
	const float			*v						=	varying[VARIABLE_V]+start;
	const int			vertexSize				=	variables->vertexSize;
	double				*vertexData;
	int					vertexDataStep;
	int					vertexSampleStride;
	
	const int 	upatches	=	uVertices - 3;
	const int 	vpatches	=	vVertices - 3;
	
	memBegin();

	if (variables->moving == FALSE) {
		vertexData			=	vertex;								// No need for interpolation
		vertexDataStep		=	0;
		vertexSampleStride	=	vertexSize*16;
	} else {									
		if (up & PARAMETER_BEGIN_SAMPLE) {
			vertexData			=	vertex;							// No need for interpolation
			vertexDataStep		=	0;
			vertexSampleStride	=	vertexSize*16;
		} else if (up & PARAMETER_END_SAMPLE) {
			vertexData			=	vertex + vertexSize*16*upatches*vpatches;	// No need for interpolation
			vertexDataStep		=	0;
			vertexSampleStride	=	vertexSize*16;
		} else {
														// Interpolate the vertex data in advance
														// Note: this is potentially hugely expensive
			double			*interpolate;
			const float		*time	=	varying[VARIABLE_TIME] + start;

			vertexData				=	(double *) ralloc(numVertices*vertexSize*16*sizeof(double));
			vertexDataStep			=	vertexSize*16;
			vertexSampleStride		=	0;

			interpolate				=	vertexData;

			for (i=0;i<numVertices;i++) {
				const	int		x			=	(int) floor(min(u[i]*upatches,(uVertices-4)));
				const	int		y			=	(int) floor(min(v[i]*vpatches,(vVertices-4)));
				const 	double	*vertex0	=	vertex + (y*upatches + x)*vertexSize*16;
				const 	double	*vertex1	=	vertex0 + vertexSize*16*upatches*vpatches;
				const	float	ctime		=	*time++;

				for (j=0;j<vertexDataStep;j++) {
					*interpolate++	=	vertex0[j]*(1-ctime) + vertex1[j]*ctime;
				}
			}
		}
	}
	
	{	// Do the vertices
		float	*intr		=	(float *) ralloc(numVertices*vertexSize*sizeof(float));
		float	*dPdu		=	varying[VARIABLE_DPDU] + start*3;
		float	*dPdv		=	varying[VARIABLE_DPDV] + start*3;
		float	*N			=	varying[VARIABLE_NG] + start*3;
		float	*intrStart	=	intr;
		const float um		=	(float) upatches;
		const float vm		=	(float) vpatches;
				
		// Interpolate the vertices
		for (i=0,k=0;i<numVertices;i++) {
			double			tmp1[4],tmp2[4];
			const	int		x			=	(int) floor(min(u[i]*upatches,(uVertices-4)));
			const	int		y			=	(int) floor(min(v[i]*vpatches,(vVertices-4)));
			const	double	cu			=	(u[i]*upatches - x);
			const	double	cv			=	(v[i]*vpatches - y);

			const	double	*data		=	vertexData + (y*upatches + x)*vertexSampleStride;
			const	double	usquared	=	cu*cu;
			const	double	ucubed		=	cu*usquared;
			const	double	vsquared	=	cv*cv;
			const	double	vcubed		=	cv*vsquared;
			int		j;

			for (j=0;j<3;j++) {
				for (int t=0;t<4;t++) {
					tmp2[t]	=	3*vsquared*data[element(0,t)] + 2*cv*data[element(1,t)]     + data[element(2,t)];
					tmp1[t]	=	  vcubed*  data[element(0,t)] + vsquared*data[element(1,t)] + cv*data[element(2,t)] + data[element(3,t)];
				}

				dPdv[j]			=	(float) (tmp2[0]*ucubed + tmp2[1]*usquared + tmp2[2]*cu + tmp2[3])*vm;
				dPdu[j]			=	(float) (tmp1[0]*3*usquared + tmp1[1]*2*cu + tmp1[2])*um;
				intr[k++]		=	(float) (tmp1[0]*ucubed + tmp1[1]*usquared + tmp1[2]*cu + tmp1[3]);
				data			+=	16;
			}

			for (;j<vertexSize;j++) {
				for (int t=0;t<4;t++) {
					tmp1[t]	=	  vcubed*  data[element(0,t)] + vsquared*data[element(1,t)] + cv*data[element(2,t)] + data[element(3,t)];
				}

				intr[k++]		=	(float) (tmp1[0]*ucubed + tmp1[1]*usquared + tmp1[2]*cu + tmp1[3]);
				data			+=	16;
			}

			crossvv(N,dPdu,dPdv);

			vertexData		+=	vertexDataStep;
			dPdu			+=	3;
			dPdv			+=	3;
			N				+=	3;
		}

		// Note: make the common case fast: We're computing NG,DPDU and DPDV even if it's not required.
		// Most of the time though, surface normal is required

		// Dispatch the vertex data
		variables->dispatch(intrStart,start,numVertices,varying);
	}
	
	normalFix();
	
	up	&=	~(PARAMETER_P | PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_NG | variables->parameters);

	memEnd();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CBSplinePatchGrid
// Method				:	interpolate
// Description			:	See object.h
// Return Value			:	-
// Comments				:
// Date last edited		:	01/23/2006
void		CBSplinePatchGrid::interpolate(int numVertices,float **varying) const {
	// perform u,v rescale first to interpolate from larger patch
	if ((uMult != 1) || (vMult != 1)) {
		float	*u,*v,*du,*dv,*dPdu,*dPdv;
		int		i;
	
		u		=	varying[VARIABLE_U];
		v		=	varying[VARIABLE_V];
		du		=	varying[VARIABLE_DU];
		dv		=	varying[VARIABLE_DV];
		dPdu	=	varying[VARIABLE_DPDU];
		dPdv	=	varying[VARIABLE_DPDV];
	
		for (i=numVertices;i>0;i--) {
			*u++	=	(*u) * uMult + uOrg;
			*v++	=	(*v) * vMult + vOrg;
			*du++	*=	uMult;
			*dv++	*=	vMult;
			mulvf(dPdu,uMult);	dPdu	+=	3;
			mulvf(dPdv,vMult);	dPdv	+=	3;
		}
	}
	
	if (parameters != NULL)	parameters->dispatch(numVertices,varying);
}



