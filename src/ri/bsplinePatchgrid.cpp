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
CBSplinePatchGrid::CBSplinePatchGrid(CAttributes *a,CXform *x,CVertexData *var,CParameter *p,int nu,int nv,float uOrg,float vOrg,float uMult,float vMult,float *ve) : CSurface(a,x) {
	atomicIncrement(&stats.numGprims);

	variables			=	var;
	variables->attach();

	parameters			=	p;

	uVertices			=	nu;
	vVertices			=	nv;
	this->uOrg			=	uOrg;
	this->vOrg			=	vOrg;
	this->uMult			=	uMult;
	this->vMult			=	vMult;

	const int		numVertices		=	(nu*nv);
	int				i,j,k;
	matrix			ut;
	matrix			bsplinebasis;
	matrix			geometryU,geometryV;
	matrix			tmp;
	const int 		upatches		=	uVertices - 3;
	const int	 	vpatches		=	vVertices - 3;

	initv(bmin,C_INFINITY,C_INFINITY,C_INFINITY);
	initv(bmax,-C_INFINITY,-C_INFINITY,-C_INFINITY);
	
	// Note that u basis and v basis are swapped to take the transpose into account done during the precomputation
	// Note also that we could use the B-spline basis to bound the curve, but Bezier bound is tighter
	for (i=0;i<4;i++)
		for (j=0;j<4;j++)
			bsplinebasis[element(i,j)]	=	RiBSplineBasis[j][i];
	transposem(ut,bsplinebasis);
	mulmm(geometryV,invBezier,ut);
	mulmm(geometryU,bsplinebasis,invBezier);
	
	// alloc off upatches*vpatches*16*vertexSize worth of data
	const int	vertexSize	=	var->vertexSize;
	const int	vs			=	(variables->moving ? vertexSize*2 : vertexSize);
	vertex					=	new float[vs*16*upatches*vpatches];
	
	for (i=0;i<vpatches;i++) {
		for (j=0;j<upatches;j++) {
			int		r,c;
			float	*patchData = vertex + (i*upatches + j)*16*vertexSize;

			// Fill in the geometry matrices
			for (r=0;r<4;r++) {
				int					y	=	(r + i) % vVertices;
				for (c=0;c<4;c++) {
					int			x	=	(c + j) % uVertices;
					const float	*d	=	ve + (y*uVertices+x)*vs;

					for	(k=0;k<vertexSize;k++) {
						patchData[16*k + element(r,c)]		=	*d++;
					}
				}
			}

			// add to bounds
			makeCubicBound(bmin,bmax,patchData+0*16,patchData+1*16,patchData+2*16);
			
			// precompute B*G*B' and stash it
			for	(k=0;k<vertexSize;k++) {
				mulmm(tmp,ut,patchData);
				mulmm(patchData,tmp,bsplinebasis);
				patchData += 16;
			}

			// do the same for moving points
			if (variables->moving) {
				patchData = vertex + (upatches*vpatches + i*upatches + j)*16*vertexSize;

				for (r=0;r<4;r++) {
					int					y	=	(r + i) % vVertices;
					for (c=0;c<4;c++) {
						int			x	=	(c + j) % uVertices;
						const float	*d	=	ve + vertexSize + (y*uVertices+x)*vs;
						
						for	(k=0;k<vertexSize;k++) {
							patchData[16*k + element(r,c)]		=	*d++;
						}
					}
				}

				// add to bounds
				makeCubicBound(bmin,bmax,patchData+0*16,patchData+1*16,patchData+2*16);

				// precompute B*G*B' and stash it
				for	(k=0;k<vertexSize;k++) {
					mulmm(tmp,ut,patchData);
					mulmm(patchData,tmp,bsplinebasis);
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
CBSplinePatchGrid::~CBSplinePatchGrid() {
	delete [] vertex;

	variables->detach();

	if (parameters != NULL)	delete parameters;

	atomicDecrement(&stats.numGprims);
}



///////////////////////////////////////////////////////////////////////
// Class				:	CBSplinePatchGrid
// Method				:	sample
// Description			:	See object.h
// Return Value			:	-
// Comments				:
void		CBSplinePatchGrid::sample(int start,int numVertices,float **varying,float ***locals,unsigned int &up) const {
	const float		*u				=	varying[VARIABLE_U]+start;
	const float		*v				=	varying[VARIABLE_V]+start;
	const int		vertexSize		=	variables->vertexSize;
	float			*vertexData;
	int				vertexDataStep;
	int				vertexSampleStride;
	const int		upatches		=	uVertices - 3;
	const int		vpatches		=	vVertices - 3;
	

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
			float			*interpolate;
			const float		*time	=	varying[VARIABLE_TIME] + start;

			vertexData				=	(float *) alloca(numVertices*vertexSize*16*sizeof(float));
			vertexDataStep			=	vertexSize*16;
			vertexSampleStride		=	0;

			interpolate				=	vertexData;

			for (int i=0;i<numVertices;++i) {
				const	int		x			=	(int) floor(min(u[i]*upatches,(uVertices-4)));
				const	int		y			=	(int) floor(min(v[i]*vpatches,(vVertices-4)));
				const 	float	*vertex0	=	vertex + (y*upatches + x)*vertexSize*16;
				const 	float	*vertex1	=	vertex0 + vertexSize*16*upatches*vpatches;
				const	float	ctime		=	*time++;

				for (int j=0;j<vertexDataStep;++j) {
					*interpolate++	=	(float) (vertex0[j]*(1.0-ctime) + vertex1[j]*ctime);
				}
			}
		}
	}
	
	{	// Do the vertices
		float	*intr		=	(float *) alloca(numVertices*vertexSize*sizeof(float));
		float	*dPdu		=	varying[VARIABLE_DPDU] + start*3;
		float	*dPdv		=	varying[VARIABLE_DPDV] + start*3;
		float	*N			=	varying[VARIABLE_NG] + start*3;
		float	*intrStart	=	intr;
		const float um		=	(float) upatches;
		const float vm		=	(float) vpatches;
				
		// Interpolate the vertices
		for (int i=0;i<numVertices;++i) {
			double			tmp1[4],tmp2[4];
			const	int		x			=	(int) floor(min(u[i]*upatches,(uVertices-4)));
			const	int		y			=	(int) floor(min(v[i]*vpatches,(vVertices-4)));
			const	double	cu			=	(u[i]*upatches - x);
			const	double	cv			=	(v[i]*vpatches - y);
			const	float	*data		=	vertexData + (y*upatches + x)*vertexSampleStride;
			const	double	usquared	=	cu*cu;
			const	double	ucubed		=	cu*usquared;
			const	double	vsquared	=	cv*cv;
			const	double	vcubed		=	cv*vsquared;
			int				j;

			for (j=0;j<3;++j,data+=16) {
				for (int t=0;t<4;++t) {
					tmp2[t]	=	3*vsquared*data[element(0,t)] + 2*cv*data[element(1,t)]     + data[element(2,t)];
					tmp1[t]	=	  vcubed*  data[element(0,t)] + vsquared*data[element(1,t)] + cv*data[element(2,t)] + data[element(3,t)];
				}

				dPdv[j]			=	(float) (tmp2[0]*ucubed + tmp2[1]*usquared + tmp2[2]*cu + tmp2[3])*vm;
				dPdu[j]			=	(float) (tmp1[0]*3*usquared + tmp1[1]*2*cu + tmp1[2])*um;
				*intr++			=	(float) (tmp1[0]*ucubed + tmp1[1]*usquared + tmp1[2]*cu + tmp1[3]);
			}

			for (;j<vertexSize;++j) {
				for (int t=0;t<4;++t) {
					tmp1[t]	=	  vcubed*  data[element(0,t)] + vsquared*data[element(1,t)] + cv*data[element(2,t)] + data[element(3,t)];
				}

				*intr++			=	(float) (tmp1[0]*ucubed + tmp1[1]*usquared + tmp1[2]*cu + tmp1[3]);
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
		variables->dispatch(intrStart,start,numVertices,varying,locals);
	}
	
	// Compute dPdtime
	if (up & PARAMETER_DPDTIME) {
		float	*dest	=	varying[VARIABLE_DPDTIME] + start*3;
		
		// Do we have motion?
		if (variables->moving) {
			assert(u == varying[VARIABLE_U] + start);
			assert(v == varying[VARIABLE_V] + start);
			const int disp	=	vertexSize*16*upatches*vpatches;
			
			// Interpolate the thing
			for (int i=0;i<numVertices;++i) {
				double			tmpStart[4],tmpEnd[4];
				const	int		x			=	(int) floor(min(u[i]*upatches,(uVertices-4)));
				const	int		y			=	(int) floor(min(v[i]*vpatches,(vVertices-4)));
				const	double	cu			=	(u[i]*upatches - x);
				const	double	cv			=	(v[i]*vpatches - y);
				const	float	*data		=	vertex + (y*upatches + x)*vertexSize*16;
				const	double	usquared	=	cu*cu;
				const	double	ucubed		=	cu*usquared;
				const	double	vsquared	=	cv*cv;
				const	double	vcubed		=	cv*vsquared;

				// For x,y,z
				for (int j=0;j<3;++j,data+=16) {
				
					// The inner product
					for (int t=0;t<4;++t) {
						tmpStart[t]	=	  vcubed*  data[element(0,t)]			+ vsquared*data[element(1,t)]			+ cv*data[element(2,t)]				+ data[element(3,t)];
						tmpEnd[t]	=	  vcubed*  data[disp + element(0,t)]	+ vsquared*data[disp + element(1,t)]	+ cv*data[disp + element(2,t)]		+ data[disp + element(3,t)];
					}

					// Update the data
					*dest++			=	(float) ((tmpEnd[0]*ucubed + tmpEnd[1]*usquared + tmpEnd[2]*cu + tmpEnd[3]) - (tmpStart[0]*ucubed + tmpStart[1]*usquared + tmpStart[2]*cu + tmpStart[3]));
				}
				
				// Scale the dPdtime
				mulvf(dest-3,CRenderer::invShutterTime);
			}
		} else {
			// We have no motion, so dPdtime is {0,0,0}
			for (int i=0;i<numVertices;++i,dest+=3)	initv(dest,0,0,0);
		}
	}
	
	// Make sure we don't have any zero normals
	normalFix();
	
	// Turn off the processed parameters
	up	&=	~(PARAMETER_P | PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_NG | PARAMETER_DPDTIME | variables->parameters);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CBSplinePatchGrid
// Method				:	interpolate
// Description			:	See object.h
// Return Value			:	-
// Comments				:
void		CBSplinePatchGrid::interpolate(int numVertices,float **varying,float ***locals) const {
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
	
	if (parameters != NULL)	parameters->dispatch(numVertices,varying,locals);
}

