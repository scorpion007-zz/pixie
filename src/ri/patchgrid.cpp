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
//  File				:	patchgrid.cpp
//  Classes				:	
//  Description			:	Patchgrid implementation
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "patchgrid.h"
#include "object.h"
#include "shading.h"
#include "memory.h"
#include "stats.h"
#include "renderer.h"

// Note:
//	The patgrid is instantiated with a grid of (nu+2)*(nv+2) vertices which
//	are used to calculate the derivatives symmetrically
//	at the borders these neighbor vertices are unavailable, so these are simply 
//	duplicated points from the nearest available edge.  The edge flags tell us
//	which edges these are so we can 'do the right thing' when calculating the
//	derivatives

///////////////////////////////////////////////////////////////////////
// Class				:	CPatchGrid
// Method				:	CPatchGrid
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CPatchGrid::CPatchGrid(CAttributes *a,CXform *x,CVertexData *var,CParameter *p,int nu,int nv,int bTop,int bRgt,int bBot,int bLft,float *ve) : CSurface(a,x) {
	int				numVertices,realNumVertices;
	int				i;
	float			*dest;
	const int		vertexSize	=	var->vertexSize;

	atomicIncrement(&stats.numGprims);

	variables			=	var;
	variables->attach();

	parameters			=	p;

	this->nu	=	nu;
	this->nv	=	nv;

	numVertices		=	(nu+2)*(nv+2);
	realNumVertices	=	(nu*nv);

	if (variables->moving) {
		const float	*src;

		dest		=	vertex		=	new float[numVertices*vertexSize*2];

		for (src=ve				,i=numVertices;i>0;i--) {
			int	j;

			for (j=vertexSize;j>0;j--) {
				*dest++ = *src++;
			}

			src	+=	vertexSize;
		}

		for (src=ve	+vertexSize,i=numVertices;i>0;i--) {
			int	j;

			for (j=vertexSize;j>0;j--) {
				*dest++ = *src++;
			}

			src	+=	vertexSize;
		}
	} else {
		dest		=	vertex		=	new float[numVertices*vertexSize];

		for (i=numVertices*vertexSize;i>0;i--) *dest++ = *ve++;
	}

	

	// Compute the bounding box
	{
		int		i;
		float	*P;
		initv(bmin,C_INFINITY,C_INFINITY,C_INFINITY);
		initv(bmax,-C_INFINITY,-C_INFINITY,-C_INFINITY);

		for (i=numVertices,P=vertex;i>0;i--,P+=vertexSize) {
			addBox(bmin,bmax,P);
		}

		if (variables->moving) {
			for (i=numVertices;i>0;i--,P+=vertexSize) {
				addBox(bmin,bmax,P);
			}
		}

		makeBound(bmin,bmax);
	}

	Pu	=	new float[realNumVertices*3];
	Pv	=	new float[realNumVertices*3];

	// Compute dPdu
	{
		int	x,y;
		
		const float lMul = (bLft ? 1.0f : 0.5f);
		const float rMul = (bRgt ? 1.0f : 0.5f);
		
		// Compute dPdu using central differencing
		for (y=0;y<nv;y++) {
			float	*cdPdu	=	Pu + y*nu*3;
			float	*cP		=	vertex + (y+1)*(nu+2)*vertexSize + vertexSize;
			
			subvv(cdPdu,cP+vertexSize,cP-vertexSize);
			mulvf(cdPdu,lMul);
			cdPdu	+=	3;
			cP		+=	vertexSize;
				
			for (x=1;x<(nu-1);x++) {
				subvv(cdPdu,cP+vertexSize,cP-vertexSize);
				mulvf(cdPdu,0.5);
				cdPdu	+=	3;
				cP		+=	vertexSize;
			}
			
			subvv(cdPdu,cP+vertexSize,cP-vertexSize);
			mulvf(cdPdu,rMul);
		}
	}

	// Compute dPdv
	{
		int	x,y;
		
		const float tMul = (bTop ? 1.0f : 0.5f);
		const float bMul = (bBot ? 1.0f : 0.5f);

		// Compute dPdv using central differencing
		for (x=0;x<nu;x++) {
			float	*cdPdv	=	Pv + x*3;
			float	*cP		=	vertex + (x+1)*vertexSize + (nu+2)*vertexSize;

			subvv(cdPdv,cP+vertexSize*(nu+2),cP-vertexSize*(nu+2));
			mulvf(cdPdv,tMul);
			cdPdv	+=	nu*3;
			cP		+=	(nu+2)*vertexSize;
			
			for (y=1;y<(nv-1);y++) {
				subvv(cdPdv,cP+vertexSize*(nu+2),cP-vertexSize*(nu+2));
				mulvf(cdPdv,0.5);
				cdPdv	+=	nu*3;
				cP		+=	(nu+2)*vertexSize;
			}
			
			subvv(cdPdv,cP+vertexSize*(nu+2),cP-vertexSize*(nu+2));
			mulvf(cdPdv,bMul);
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPatchGrid
// Method				:	~CPatchGrid
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CPatchGrid::~CPatchGrid() {
	int	numVertices		=	(nu+2)*(nv+2);
	int realNumVertices	=	(nu*nv);

	delete [] Pu;
	delete [] Pv;
	delete [] vertex;

	variables->detach();

	if (parameters != NULL)	delete parameters;

	atomicDecrement(&stats.numGprims);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPatchGrid
// Method				:	sample
// Description			:	See object.h
// Return Value			:	-
// Comments				:
void		CPatchGrid::sample(int start,int numVertices,float **varying,float ***locals,unsigned int &up) const {
	const float			*u						=	varying[VARIABLE_U]+start;
	const float			*v						=	varying[VARIABLE_V]+start;
	const int			vertexSize				=	variables->vertexSize;
	float				*vertexData;
	int					vertexDataStep;

	if (variables->moving == FALSE) {
		vertexData		=	vertex;									// No need for interpolation
		vertexDataStep	=	0;
	} else {									
		if (up & PARAMETER_BEGIN_SAMPLE) {
			vertexData		=	vertex;								// No need for interpolation
			vertexDataStep	=	0;
		} else if (up & PARAMETER_END_SAMPLE) {
			vertexData		=	vertex + vertexSize*(nu+2)*(nv+2);	// No need for interpolation
			vertexDataStep	=	0;
		} else {
			// GSHTODO: use uv's to interpolate only the needed vertices
												// Interpolate the vertex data in advance
			float		*interpolate;
			const float	*time		=	varying[VARIABLE_TIME] + start;
			const float	*vertex0	=	vertex;
			const float	*vertex1	=	vertex + vertexSize*(nu+2)*(nv+2);

			vertexData				=	(float *) alloca(numVertices*(nu+2)*(nv+2)*vertexSize*sizeof(float));
			vertexDataStep			=	(nu+2)*(nv+2)*vertexSize;

			interpolate				=	vertexData;

			for (int i=numVertices;i>0;--i) {
				const double ctime	=	*time++;

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
		float	*intrStart	=	intr;
		const float	um		=	(float) (nu - 1);
		const float	vm		=	(float) (nv - 1);

		// Interpolate the vertices
		for (int i=0;i<numVertices;++i) {
			const	double	cu		=	u[i] * (nu - 1.0);
			const	double	cv		=	v[i] * (nv - 1.0);
			const	int		x		=	(int) floor(min(cu,(nu-2)));
			const	int		y		=	(int) floor(min(cv,(nv-2)));
			const	float	*d0		=	vertexData + ((y+1)*(nu+2) + x+1)*vertexSize;
			const	float	*d1		=	vertexData + ((y+1)*(nu+2) + x+2)*vertexSize;
			const	float	*d2		=	vertexData + ((y+2)*(nu+2) + x+1)*vertexSize;
			const	float	*d3		=	vertexData + ((y+2)*(nu+2) + x+2)*vertexSize;
			const	double	xoff	=	cu - x;
			const	double	yoff	=	cv - y;

			//assert((xoff >= 0) && (xoff <= 1.001));
			//assert((yoff >= 0) && (yoff <= 1.001));
			//assert((x >= 0) && (x < (nu-1)));
			//assert((y >= 0) && (y < (nv-1)));

			for (int j=vertexSize;j>0;--j) {
				*intr++	=	(float) (((*d0++)*(1.0-xoff) + (*d1++)*xoff)*(1.0-yoff)  + ((*d2++)*(1.0-xoff) + (*d3++)*xoff)*yoff);
			}

			vertexData				+=	vertexDataStep;

			d0		=	Pu + (y*nu + x)*3;
			d1		=	Pu + (y*nu + x+1)*3;
			d2		=	Pu + ((y+1)*nu + x)*3;
			d3		=	Pu + ((y+1)*nu + x+1)*3;
			*dPdu++	=	(float) ((((*d0++)*(1.0-xoff) + (*d1++)*xoff)*(1.0-yoff)  + ((*d2++)*(1.0-xoff) + (*d3++)*xoff)*yoff)*um);
			*dPdu++	=	(float) ((((*d0++)*(1.0-xoff) + (*d1++)*xoff)*(1.0-yoff)  + ((*d2++)*(1.0-xoff) + (*d3++)*xoff)*yoff)*um);
			*dPdu++	=	(float) ((((*d0++)*(1.0-xoff) + (*d1++)*xoff)*(1.0-yoff)  + ((*d2++)*(1.0-xoff) + (*d3++)*xoff)*yoff)*um);

			d0		=	Pv + (y*nu + x)*3;
			d1		=	Pv + (y*nu + x+1)*3;
			d2		=	Pv + ((y+1)*nu + x)*3;
			d3		=	Pv + ((y+1)*nu + x+1)*3;
			*dPdv++	=	(float) ((((*d0++)*(1.0-xoff) + (*d1++)*xoff)*(1.0-yoff)  + ((*d2++)*(1.0-xoff) + (*d3++)*xoff)*yoff)*vm);
			*dPdv++	=	(float) ((((*d0++)*(1.0-xoff) + (*d1++)*xoff)*(1.0-yoff)  + ((*d2++)*(1.0-xoff) + (*d3++)*xoff)*yoff)*vm);
			*dPdv++	=	(float) ((((*d0++)*(1.0-xoff) + (*d1++)*xoff)*(1.0-yoff)  + ((*d2++)*(1.0-xoff) + (*d3++)*xoff)*yoff)*vm);
		}

		if (up & PARAMETER_NG) {
			float			*N		=	varying[VARIABLE_NG] + start*3;
			const	float	*dPdu	=	varying[VARIABLE_DPDU] + start*3;
			const	float	*dPdv	=	varying[VARIABLE_DPDV] + start*3;

			for (int i=numVertices;i>0;--i) {
				crossvv(N,dPdu,dPdv);
				N		+=	3;
				dPdu	+=	3;
				dPdv	+=	3;
			}
		}

		// Commit these variables
		variables->dispatch(intrStart,start,numVertices,varying,locals);
	}

	// Compute dPdtime
	if (up & PARAMETER_DPDTIME) {
		float	*dest	=	varying[VARIABLE_DPDTIME] + start*3;
		
		// Do we have motion?
		if (variables->moving) {
			assert(u == varying[VARIABLE_U] + start);
			assert(v == varying[VARIABLE_V] + start);
			const int disp	=	vertexSize*(nu+2)*(nv+2);
			
			// Interpolate the thing
			for (int i=0;i<numVertices;++i,dest+=3) {
				const	float	cu		=	u[i] * (nu - 1.0f);
				const	float	cv		=	v[i] * (nv - 1.0f);
				const	int		x		=	(int) floor(min(cu,(nu-2)));
				const	int		y		=	(int) floor(min(cv,(nv-2)));
				const	float	*d0		=	vertexData + ((y+1)*(nu+2) + x+1)*vertexSize;
				const	float	*d1		=	vertexData + ((y+1)*(nu+2) + x+2)*vertexSize;
				const	float	*d2		=	vertexData + ((y+2)*(nu+2) + x+1)*vertexSize;
				const	float	*d3		=	vertexData + ((y+2)*(nu+2) + x+2)*vertexSize;
				const	float	xoff	=	cu - x;
				const	float	yoff	=	cv - y;

				// Interpolate the thing
				for (int j=0;j<3;++j) {
					dest[j]	=	(((d0[disp+j])*(1.0f-xoff) + (d1[disp+j])*xoff)*(1.0f-yoff)  + ((d2[disp+j])*(1.0f-xoff) + (d3[disp+j])*xoff)*yoff) -
								(((d0[j])*(1.0f-xoff) + (d1[j])*xoff)*(1.0f-yoff)  + ((d2[j])*(1.0f-xoff) + (d3[j])*xoff)*yoff);
				}
				
				// Scale the dPdtime
				mulvf(dest,CRenderer::invShutterTime);
			}
		} else {
			// We have no motion, so dPdtime is {0,0,0}
			for (int i=0;i<numVertices;++i,dest+=3)	initv(dest,0,0,0);
		}
	}
	
	// Turn off the parameters we've fixed
	up	&=	~(PARAMETER_P | PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_NG | PARAMETER_DPDTIME | variables->parameters);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSubdivision
// Method				:	interpolate
// Description			:	See object.h
// Return Value			:	-
// Comments				:
void		CPatchGrid::interpolate(int numVertices,float **varying,float ***locals) const {
	if (parameters != NULL)	parameters->dispatch(numVertices,varying,locals);
}

