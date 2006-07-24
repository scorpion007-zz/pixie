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
//  File				:	patches.cpp
//  Classes				:	CBilinearPatchMesh
//							CBicubicPatchMesh
//							CNURBSPatch
//  Description			:	Implementation
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "patches.h"
#include "renderer.h"
#include "stats.h"
#include "memory.h"
#include "shading.h"
#include "error.h"
#include "patchUtils.h"



////////////////////////////////////////////////////////////////////////
//
//	Some static variables used while creating primitives
//
////////////////////////////////////////////////////////////////////////
static	int				uvaryings,vvaryings;
static	int				uvertices,vvertices;
static	CPl				*parameterList;
static	CVertexData		*vertexData;
static	float			*vertices;
static	int				vertexSize;

///////////////////////////////////////////////////////////////////////
// Function				:	gatherData
// Description			:	Get the data
// Return Value			:	-
// Comments				:	-
// Date last edited		:	6/21/2001
static	inline	void	gatherData(int u,int v,int nu,int nv,int uv,int vv,int un,double *&vertex,CParameter *&parameters) {
	int			i,j,k;
	double		*dest;
	const int	v0		=	vv*uvaryings+uv;
	const int	v1		=	vv*uvaryings+((uv+1) % uvaryings);
	const int	v2		=	((vv+1) % vvaryings)*uvaryings+uv;
	const int	v3		=	((vv+1) % vvaryings)*uvaryings+((uv+1) % uvaryings);

	vertex		=	NULL;

	assert(vertexSize > 0);

	dest	=	vertex	=	(double *) ralloc(vertexSize*nu*nv*sizeof(double));

	// Copy the vertex variables over
	for (j=0;j<nv;j++) {
		const int		vVertex	=	(v + j) % vvertices;
		for (i=0;i<nu;i++) {
			const int		uVertex	=	(u + i) % uvertices;
		
			const int		index	=	vVertex * uvertices + uVertex;
			const float		*src	=	vertices + index*vertexSize;

			for (k=vertexSize;k>0;k--)	*dest++	=	*src++;
		}
	}

	parameters	=	parameterList->uniform(un,NULL);
	parameters	=	parameterList->varying(v0,v1,v2,v3,parameters);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CBilinearPatch
// Method				:	CBilinearPatch
// Description			:	Ctor
// Return Value			:	-
// Comments				:	-
// Date last edited		:	6/21/2001
CBilinearPatch::CBilinearPatch(CAttributes *a,CXform *x,CVertexData *v,CParameter *p,float uOrg,float vOrg,float uMult,float vMult,double *vertex0) : CSurface(a,x) {
	int			i;
	float		*dest;
	const	int	vertexSize	=	v->vertexSize;

	stats.gprimMemory	+=	sizeof(CBilinearPatch);
	stats.numGprims++;

	this->variables		=	v;
	this->variables->attach();
	this->parameters	=	p;
	this->uOrg			=	uOrg;
	this->vOrg			=	vOrg;
	this->uMult			=	uMult;
	this->vMult			=	vMult;

	// Copy the data
	if (variables->moving) {
		const double *src;
		int			j;

		dest	=	vertex	=	new float[vertexSize*8];

		src		=	vertex0;
		for (i=4;i>0;i--,src+=vertexSize) {
			for (j=vertexSize;j>0;j--)	*dest++ = (float) *src++;
		}

		src		=	vertex0 + vertexSize;
		for (i=4;i>0;i--,src+=vertexSize) {
			for (j=vertexSize;j>0;j--)	*dest++ = (float) *src++;
		}

		stats.gprimMemory	+=	vertexSize*8*sizeof(float);
	} else {
		dest	=	vertex	=	new float[vertexSize*4];

		for (i=vertexSize*4;i>0;i--) *dest++ = (float) *vertex0++;

		stats.gprimMemory	+=	vertexSize*4*sizeof(float);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CBilinearPatch
// Method				:	~CBilinearPatch
// Description			:	Dtor
// Return Value			:	-
// Comments				:	-
// Date last edited		:	6/21/2001
CBilinearPatch::~CBilinearPatch() {
	const	int	vertexSize	=	(variables->moving ? variables->vertexSize*2 : variables->vertexSize);

	stats.gprimMemory	-=	sizeof(CBilinearPatch) + 4*vertexSize*sizeof(float);
	stats.numGprims--;

	if (parameters	!= NULL)	delete parameters;
	delete [] vertex;

	variables->detach();
}


///////////////////////////////////////////////////////////////////////
// Class				:	CBilinearPatch
// Method				:	bound
// Description			:	See object.h
// Return Value			:	-
// Comments				:	-
// Date last edited		:	6/21/2001
void	CBilinearPatch::bound(float *bmin,float *bmax) const {
	float	*ver0,*ver1,*ver2,*ver3;
	int		vertexSize	=	variables->vertexSize;

	ver0				=	vertex;
	ver1				=	ver0	+	vertexSize;
	ver2				=	ver1	+	vertexSize;
	ver3				=	ver2	+	vertexSize;

	movvv(bmin,ver0);
	movvv(bmax,ver0);

	addBox(bmin,bmax,ver1);
	addBox(bmin,bmax,ver2);
	addBox(bmin,bmax,ver3);

	if (variables->moving) {
		ver0				=	vertex + vertexSize*4;
		ver1				=	ver0	+	vertexSize;
		ver2				=	ver1	+	vertexSize;
		ver3				=	ver2	+	vertexSize;

		addBox(bmin,bmax,ver0);
		addBox(bmin,bmax,ver1);
		addBox(bmin,bmax,ver2);
		addBox(bmin,bmax,ver3);
	}

	makeBound(bmin,bmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CBilinearPatch
// Method				:	tesselate
// Description			:	See object.h
// Return Value			:	-
// Comments				:	-
// Date last edited		:	6/21/2001
void	CBilinearPatch::tesselate(CShadingContext *context) {
	context->tesselate2D(this);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CBilinearPatch
// Method				:	sample
// Description			:	See object.h
// Return Value			:	-
// Comments				:	-
// Date last edited		:	6/21/2001
void	CBilinearPatch::sample(int start,int numVertices,float **varying,unsigned int &up) const {
	int				i,j;
	const float		*u						=	varying[VARIABLE_U]+start;
	const float		*v						=	varying[VARIABLE_V]+start;
	int				vertexSize				=	variables->vertexSize;
	float			*vertexData;
	int				vertexDataStep;

	memBegin();

	if (variables->moving == FALSE) {
		vertexData		=	vertex;							// No need for interpolation
		vertexDataStep	=	0;
	} else {
		if (up & PARAMETER_BEGIN_SAMPLE) {
			vertexData		=	vertex;						// No need for interpolation
			vertexDataStep	=	0;
		} else if (up & PARAMETER_END_SAMPLE) {
			vertexData		=	vertex + vertexSize*4;		// No need for interpolation
			vertexDataStep	=	0;
		} else {
			float		*interpolate;
			const float	*time	=	varying[VARIABLE_TIME] + start;
			int			j,k;
			const float	*vertex0	=	vertex;
			const float	*vertex1	=	vertex + vertexSize*4;

			vertexData		=	(float *) ralloc(numVertices*vertexSize*4*sizeof(float));
			vertexDataStep	=	vertexSize*4;
			interpolate		=	vertexData;
			k				=	vertexSize*4;

			for (i=numVertices;i>0;i--) {
				const float	ctime	=	*time++;
				for (j=0;j<k;j++) {
					*interpolate++	=	vertex0[j]*(1-ctime) + vertex1[j]*ctime;
				}
			}
		}
	}

	{	// Do the vertices
		// Interpolate the vertices
		float		*intr	=	(float *) ralloc(numVertices*vertexSize*sizeof(float));
		const float	*v0		=	vertexData;
		const float	*v1		=	v0 + vertexSize;
		const float	*v2		=	v1 + vertexSize;
		const float	*v3		=	v2 + vertexSize;
		float		*tmp	=	intr;

		for (i=0;i<numVertices;i++) {
			const float cu	=	*u++;
			const float cv	=	*v++;

			for (j=0;j<vertexSize;j++) {
				*tmp++	=	(v0[j]*(1 - cu) + v1[j]*cu)*(1-cv)	+
							(v2[j]*(1 - cu) + v3[j]*cu)*cv;
			}

			v0			+=	vertexDataStep;
			v1			+=	vertexDataStep;
			v2			+=	vertexDataStep;
			v3			+=	vertexDataStep;
		}

		variables->dispatch(intr,start,numVertices,varying);

		// Compute surface derivatives and normal if required
		if (up & (PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_NG)) {
			float	*destdu	=	varying[VARIABLE_DPDU] + start*3;
			float	*destdv	=	varying[VARIABLE_DPDV] + start*3;
			float	*destn	=	varying[VARIABLE_NG] + start*3;
			vector	du1,du2;
			vector	dv1,dv2;

			u				=	varying[VARIABLE_U]+start;
			v				=	varying[VARIABLE_V]+start;

			if (vertexDataStep == 0) {
				subvv(du1,v1,v0);
				subvv(du2,v3,v2);
				subvv(dv1,v2,v0);
				subvv(dv2,v3,v1);

				for (i=0;i<numVertices;i++) {
					interpolatev(destdu,du1,du2,v[i]);
					interpolatev(destdv,dv1,dv2,u[i]);
					crossvv(destn,destdu,destdv);
					destdu	+=	3;
					destdv	+=	3;
					destn	+=	3;
				}
			} else {
				v0		=	vertexData;
				v1		=	v0 + vertexSize;
				v2		=	v1 + vertexSize;
				v3		=	v2 + vertexSize;

				for (i=0;i<numVertices;i++) {
					subvv(du1,v1,v0);
					subvv(du2,v3,v2);
					subvv(dv1,v2,v0);
					subvv(dv2,v3,v1);
					interpolatev(destdu,du1,du2,v[i]);
					interpolatev(destdv,dv1,dv2,u[i]);
					crossvv(destn,destdu,destdv);
					destdu	+=	3;
					destdv	+=	3;
					destn	+=	3;
					v0		+=	vertexDataStep;
					v1		+=	vertexDataStep;
					v2		+=	vertexDataStep;
					v3		+=	vertexDataStep;

				}
			}
		}
	}

	// Fix the degenerate normals
	normalFix();

	up	&=	~(PARAMETER_P | PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_NG | variables->parameters);

	memEnd();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CBilinearPatch
// Method				:	interpolate
// Description			:	See object.h
// Return Value			:	-
// Comments				:	-
// Date last edited		:	6/21/2001
void	CBilinearPatch::interpolate(int numVertices,float **varying) const {
	if (parameters != NULL)	parameters->dispatch(numVertices,varying);

	// Correct the parametric range of the primitive
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
}








///////////////////////////////////////////////////////////////////////
// Class				:	CBicubicPatch
// Method				:	CBicubicPatch
// Description			:	Ctor
// Return Value			:	-
// Comments				:	-
// Date last edited		:	6/21/2001
CBicubicPatch::CBicubicPatch(CAttributes *a,CXform *x,CVertexData *v,CParameter *p,float uOrg,float vOrg,float uMult,float vMult,double *vertexData) : CSurface(a,x) {
	const unsigned int vertexSize	=	v->vertexSize;

	stats.numGprims++;
	stats.gprimMemory	+=	sizeof(CBicubicPatch);

	variables	=	v;
	variables->attach();
	parameters	=	p;

	this->uOrg	=	uOrg;
	this->vOrg	=	vOrg;
	this->uMult	=	uMult;
	this->vMult	=	vMult;

	initv(bmin,C_INFINITY,C_INFINITY,C_INFINITY);
	initv(bmax,-C_INFINITY,-C_INFINITY,-C_INFINITY);

	if (variables->moving) {
		vertex	=	new double[vertexSize*32];

		computeVertexData(vertex					,vertexData,0);
		computeVertexData(vertex + vertexSize*16	,vertexData,vertexSize);

		stats.gprimMemory	+=	vertexSize*32*sizeof(double);
	} else {
		vertex	=	new double[vertexSize*16];

		computeVertexData(vertex,vertexData,0);

		stats.gprimMemory	+=	vertexSize*16*sizeof(double);
	}

	makeBound(bmin,bmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CBicubicPatch
// Method				:	~CBicubicPatch
// Description			:	Dtor
// Return Value			:	-
// Comments				:	-
// Date last edited		:	6/21/2001
CBicubicPatch::~CBicubicPatch() {
	const int	vertexSize	=	(variables->moving ? variables->vertexSize*2 : variables->vertexSize);

	stats.gprimMemory	-=	sizeof(CBicubicPatch) + sizeof(double)*vertexSize*16;
	stats.numGprims--;

	if (parameters	!= NULL)	delete parameters;

	assert(vertex != NULL);
	delete [] vertex;

	variables->detach();
}


///////////////////////////////////////////////////////////////////////
// Class				:	CBicubicPatch
// Method				:	computeVertexData
// Description			:	Compute the Bu*G*Bv' matrix as the matrix data so that we don't need to do this multiplication at runtime
// Return Value			:	The new vertex data
// Comments				:	-
// Date last edited		:	6/21/2001
void	CBicubicPatch::computeVertexData(double *vertex,const double *vertexData,int disp) {
	int					k,l;
	const float			*vb			=	attributes->uBasis;
	const float			*ub			=	attributes->vBasis;
	const int			vertexSize	=	variables->vertexSize;
	const int			vs			=	(variables->moving ? vertexSize*2 : vertexSize);
	double				data[16];
	matrix				ut;

	transposem(ut,ub);

	// Compute the premultiplied geometry matrix
	for	(k=0;k<vertexSize;k++) {
		double			tmp[16],tmp2[16];
		unsigned int	x,y;

		for (y=0;y<4;y++)
			for (x=0;x<4;x++)
				data[element(y,x)]	=	vertexData[(y*4+x)*vs+k+disp];

		mulmmd(tmp2,ut,data);
		mulmmd(tmp,tmp2,vb);

		for (l=0;l<16;l++)
			vertex[16*k+l]	=	tmp[l];
	}

	// Computhe the bound
	{
		double	tmp1[16],tmp2[16];
		double	*cVertex	=	vertex;

		mulmmd(tmp1,invBezier,cVertex);
		mulmmd(tmp2,tmp1,invBezier);
		for (k=0;k<16;k++) {
			if (tmp2[k] < bmin[COMP_X])	bmin[COMP_X]	=	(float) tmp2[k];
			if (tmp2[k] > bmax[COMP_X])	bmax[COMP_X]	=	(float) tmp2[k];
		}

		cVertex	+=	16;
		mulmmd(tmp1,invBezier,cVertex);
		mulmmd(tmp2,tmp1,invBezier);
		for (k=0;k<16;k++) {
			if (tmp2[k] < bmin[COMP_Y])	bmin[COMP_Y]	=	(float) tmp2[k];
			if (tmp2[k] > bmax[COMP_Y])	bmax[COMP_Y]	=	(float) tmp2[k];
		}

		cVertex	+=	16;
		mulmmd(tmp1,invBezier,cVertex);
		mulmmd(tmp2,tmp1,invBezier);
		for (k=0;k<16;k++) {
			if (tmp2[k] < bmin[COMP_Z])	bmin[COMP_Z]	=	(float) tmp2[k];
			if (tmp2[k] > bmax[COMP_Z])	bmax[COMP_Z]	=	(float) tmp2[k];
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CBicubicPatch
// Method				:	bound
// Description			:	See object.h
// Return Value			:	-
// Comments				:	-
// Date last edited		:	6/21/2001
void	CBicubicPatch::bound(float *bmin,float *bmax) const {
	movvv(bmin,this->bmin);
	movvv(bmax,this->bmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CBicubicPatch
// Method				:	tesselate
// Description			:	See object.h
// Return Value			:	-
// Comments				:	-
// Date last edited		:	6/21/2001
void	CBicubicPatch::tesselate(CShadingContext *context) {
	context->tesselate2D(this);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CBicubicPatch
// Method				:	sample
// Description			:	See object.h
// Return Value			:	-
// Comments				:	-
// Date last edited		:	6/21/2001
void	CBicubicPatch::sample(int start,int numVertices,float **varying,unsigned int &up) const {
	int					i,k;
	const float			*u					=	varying[VARIABLE_U]+start;
	const float			*v					=	varying[VARIABLE_V]+start;
	int					vertexSize			=	variables->vertexSize;
	double				*vertexData;
	int					vertexDataStep;

	memBegin();

	if (variables->moving == FALSE) {
		vertexData		=	vertex;
		vertexDataStep	=	0;
	} else {
		if (up & PARAMETER_BEGIN_SAMPLE) {
			vertexData		=	vertex;						// No need for interpolation
			vertexDataStep	=	0;
		} else if (up & PARAMETER_END_SAMPLE) {
			vertexData		=	vertex + vertexSize*16;		// No need for interpolation
			vertexDataStep	=	0;
		} else {
			double			*interpolate;
			const float		*time	=	varying[VARIABLE_TIME] + start;
			int				j;
			const double	*vertex0	=	vertex;
			const double	*vertex1	=	vertex + vertexSize*16;

			vertexData		=	(double *) ralloc(numVertices*vertexSize*16*sizeof(double));
			vertexDataStep	=	vertexSize*16;
			interpolate		=	vertexData;

			for (i=numVertices;i>0;i--) {
				const float	ctime	=	*time++;

				for (j=0;j<vertexDataStep;j++) {
					*interpolate++	=	vertex0[j]*(1-ctime) + vertex1[j]*ctime;
				}
			}
		}
	}

	{	// Do the vertices
		float	*intr		=	(float *) ralloc(vertexSize*numVertices*sizeof(float));
		double	*data;
		float	*intrStart	=	intr;
		float	*dPdu		=	varying[VARIABLE_DPDU] + start*3;
		float	*dPdv		=	varying[VARIABLE_DPDV] + start*3;
		float	*N			=	varying[VARIABLE_NG] + start*3;

		// Interpolate the vertices
		for (i=0,k=0;i<numVertices;i++) {
			int				j;
			double			tmp1[4],tmp2[4];
			const double	cu			=	u[i];
			const double 	cv			=	v[i];
			const double	usquared	=	cu*cu;
			const double	ucubed		=	cu*usquared;
			const double	vsquared	=	cv*cv;
			const double	vcubed		=	cv*vsquared;

			for (data=vertexData,j=0;j<3;j++) {
				for (int t=0;t<4;t++) {
					tmp2[t]	=	3*vsquared*data[element(0,t)] + 2*cv*data[element(1,t)]     + data[element(2,t)];
					tmp1[t]	=	  vcubed*  data[element(0,t)] + vsquared*data[element(1,t)] + cv*data[element(2,t)] + data[element(3,t)];
				}

				dPdv[j]			=	(float) (tmp2[0]*ucubed + tmp2[1]*usquared + tmp2[2]*cu + tmp2[3]);
				dPdu[j]			=	(float) (tmp1[0]*3*usquared + tmp1[1]*2*cu + tmp1[2]);
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

	// Fix the degenerate normals
	normalFix();

	up	&=	~(PARAMETER_P | PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_NG | variables->parameters);

	memEnd();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CBicubicPatch
// Method				:	interpolate
// Description			:	See object.h
// Return Value			:	-
// Comments				:	-
// Date last edited		:	6/21/2001
void	CBicubicPatch::interpolate(int numVertices,float **varying) const {
	if (parameters != NULL)	parameters->dispatch(numVertices,varying);

	// Correct the parametric range of the primitive
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
}





///////////////////////////////////////////////////////////////////////
// Class				:	CNURBSPatch
// Method				:	CNURBSPatch
// Description			:	Ctor
// Return Value			:	-
// Comments				:	-
// Date last edited		:	6/21/2001
CNURBSPatch::CNURBSPatch(CAttributes *a,CXform *x,CVertexData *v,CParameter *p,int uOrder,int vOrder,float *uKnots,float *vKnots,double *vertex0) : CSurface(a,x) {
	int			j;
	double		*uCoefficients,*vCoefficients;
	const int	vertexSize	=	v->vertexSize;

	stats.gprimMemory	+=	sizeof(CNURBSPatch);
	stats.numGprims++;

	this->variables		=	v;
	this->variables->attach();
	this->parameters	=	p;
	this->uOrder		=	uOrder;
	this->vOrder		=	vOrder;

	uOrg				=	uKnots[uOrder-1];
	const float	umax	=	uKnots[uOrder];
	vOrg				=	vKnots[vOrder-1];
	const float	vmax	=	vKnots[vOrder];
	uMult				=	umax	-	uOrg;
	vMult				=	vmax	-	vOrg;

	memBegin();

	uCoefficients		=	(double *) ralloc(uOrder*uOrder*sizeof(double));
	vCoefficients		=	(double *) ralloc(vOrder*vOrder*sizeof(double));

	// For each basis function
	// Compute the coefficients
	for (j=0;j<uOrder;j++) {			
		precompBasisCoefficients(uCoefficients + uOrder*j,uOrder,j,uOrder-1,uKnots);
	}

	for (j=0;j<vOrder;j++) {
		precompBasisCoefficients(vCoefficients + vOrder*j,vOrder,j,vOrder-1,vKnots);
	}

	initv(bmin,C_INFINITY,C_INFINITY,C_INFINITY);
	initv(bmax,-C_INFINITY,-C_INFINITY,-C_INFINITY);

	if (variables->moving) {
		vertex	=	new double[uOrder*vOrder*vertexSize*2];

		precomputeVertexData(vertex								,uCoefficients,vCoefficients,vertex0,0);
		precomputeVertexData(vertex + uOrder*vOrder*vertexSize	,uCoefficients,vCoefficients,vertex0,vertexSize);

		stats.gprimMemory	+=	vertexSize*uOrder*vOrder*2*sizeof(double);
	} else {
		vertex	=	new double[uOrder*vOrder*vertexSize];

		precomputeVertexData(vertex								,uCoefficients,vCoefficients,vertex0,0);

		stats.gprimMemory	+=	vertexSize*uOrder*vOrder*sizeof(double);
	}

	memEnd();

	makeBound(bmin,bmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CNURBSPatch
// Method				:	~CNURBSPatch
// Description			:	Dtor
// Return Value			:	-
// Comments				:	-
// Date last edited		:	6/21/2001
CNURBSPatch::~CNURBSPatch() {
	const int			vertexSize	=	(variables->moving ? variables->vertexSize*2 : variables->vertexSize);

	stats.gprimMemory	-=	sizeof(CNURBSPatch) + sizeof(double)*vertexSize*uOrder*vOrder;
	stats.numGprims--;

	if (parameters	!= NULL)	delete parameters;
	delete [] vertex;

	variables->detach();
}


///////////////////////////////////////////////////////////////////////
// Class				:	CNURBSPatch
// Method				:	precomputeVertexData
// Description			:	Precompute uBasis*G*vBasis'
// Return Value			:	-
// Comments				:	-
// Date last edited		:	6/21/2001
void	CNURBSPatch::precomputeVertexData(double *vertex,const double *uCoefficients,const double *vCoefficients,double *vertexData,int disp) {
	const int	vertexSize	=	variables->vertexSize;
	const int	vs			=	(variables->moving ? vertexSize*2 : vertexSize);
	int			i,j,k;
	double		*cVertex;

	for (cVertex=vertex,i=0;i<vertexSize;i++,cVertex+=uOrder*vOrder) {
		int		u,v;

		for (j=0;j<uOrder*vOrder;j++) {
			cVertex[j]	=	0;
		}

		for (v=0;v<vOrder;v++) {
			const double *vRow	=	&vCoefficients[v*vOrder];
			for (u=0;u<uOrder;u++) {
				double		data	=	vertexData[i+(v*uOrder+u)*vs+disp];
				const double *uRow	=	&uCoefficients[u*uOrder];

				for (j=0;j<uOrder;j++) {
					for (k=0;k<vOrder;k++) {
						cVertex[j*vOrder+k]	+=	data*uRow[j]*vRow[k];
					}
				}
			}
		}
	}

	for (vertexData+=disp,i=0;i<uOrder*vOrder;i++,vertexData+=vs) {
		vector	P;

		P[0]	=	(float) (vertexData[0] / vertexData[3]);
		P[1]	=	(float) (vertexData[1] / vertexData[3]);
		P[2]	=	(float) (vertexData[2] / vertexData[3]);

		addBox(bmin,bmax,P);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CNURBSPatch
// Method				:	bound
// Description			:	See object.h
// Return Value			:	-
// Comments				:	-
// Date last edited		:	6/21/2001
void	CNURBSPatch::bound(float *bmin,float *bmax) const {
	movvv(bmin,this->bmin);
	movvv(bmax,this->bmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CNURBSPatch
// Method				:	tesselate
// Description			:	See object.h
// Return Value			:	-
// Comments				:	-
// Date last edited		:	6/21/2001
void	CNURBSPatch::tesselate(CShadingContext *context) {
	context->tesselate2D(this);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CNURBSPatch
// Method				:	sample
// Description			:	See object.h
// Return Value			:	-
// Comments				:	-
// Date last edited		:	6/21/2001
void	CNURBSPatch::sample(int start,int numVertices,float **varying,unsigned int &up) const {
	int					i,k;
	const float			*u					=	varying[VARIABLE_U]+start;
	const float			*v					=	varying[VARIABLE_V]+start;
	int					vertexSize			=	variables->vertexSize;
	double				*vertexData;
	int					vertexDataStep;

	memBegin();

	if (variables->moving == FALSE) {
		vertexData		=	vertex;
		vertexDataStep	=	0;
	} else {
		if (up & PARAMETER_BEGIN_SAMPLE) {
			vertexData		=	vertex;		// No need for interpolation
			vertexDataStep	=	0;
		} else if (up & PARAMETER_END_SAMPLE) {
			vertexData		=	vertex + vertexSize*uOrder*vOrder;		// No need for interpolation
			vertexDataStep	=	0;
		} else {
			double			*interpolate;
			const float		*time		=	varying[VARIABLE_TIME] + start;
			int				j;
			const double	*vertex0	=	vertex;
			const double	*vertex1	=	vertex + vertexSize*uOrder*vOrder;

			vertexData		=	(double *) ralloc(numVertices*vertexSize*uOrder*vOrder*sizeof(double));
			vertexDataStep	=	vertexSize*uOrder*vOrder;
			interpolate		=	vertexData;

			for (i=numVertices;i>0;i--) {
				const float ctime	=	*time++;
				for (j=0;j<vertexDataStep;j++) {
					*interpolate++	=	vertex0[j]*(1-ctime) + vertex1[j]*ctime;
				}
			}
		}
	}

	{	// Do the vertices
		float	*intr			=	(float *) ralloc(vertexSize*numVertices*sizeof(float));
		float	*intrStart		=	intr;
		float	*dPdu			=	varying[VARIABLE_DPDU] + start*3;
		float	*dPdv			=	varying[VARIABLE_DPDV] + start*3;
		float	*N				=	varying[VARIABLE_NG] + start*3;
		float	*vertexStart;
		double	pdu[4];
		double	pdv[4];

#define computeNURBS(UORDER,VORDER) {																\
		double	*memBase		=	(double *) ralloc((UORDER*3 + VORDER*3)*sizeof(double));		\
		double	*uPowers		=	memBase;														\
		double	*vPowers		=	uPowers + UORDER;												\
		double	*duPowers		=	vPowers + VORDER;												\
		double	*dvPowers		=	duPowers + UORDER;												\
																									\
		for (i=0,k=0;i<numVertices;i++) {															\
			int				j,t,var;																\
			double			*cVertex;																\
			double			denominator;															\
			const double	cu				=	u[i]*uMult + uOrg;									\
			const double	cv				=	v[i]*vMult + vOrg;									\
																									\
			uPowers[0]		=	1;																	\
			duPowers[0]		=	0;																	\
			for (j=1;j<UORDER;j++) {																\
				uPowers[j]	=	cu*uPowers[j-1];													\
				duPowers[j]	=	j*uPowers[j-1];														\
			}																						\
																									\
			vPowers[0]		=	1;																	\
			dvPowers[0]		=	0;																	\
			for (j=1;j<VORDER;j++) {																\
				vPowers[j]	=	cv*vPowers[j-1];													\
				dvPowers[j]	=	j*vPowers[j-1];														\
			}																						\
																									\
			cVertex			=	vertexData;															\
			vertexStart		=	intr;																\
			for (var=0;var<4;var++) {																\
				denominator		=	0;																\
				pdu[var]		=	0;																\
				pdv[var]		=	0;																\
				for (j=0;j<UORDER;j++) {															\
					double	tmp		=	0;															\
					double	tmpdv	=	0;															\
																									\
					for (t=0;t<VORDER;t++,cVertex++) {												\
						tmp		+=	(*cVertex)*vPowers[t];											\
						tmpdv	+=	(*cVertex)*dvPowers[t];											\
					}																				\
																									\
					denominator	+=	tmp*uPowers[j];													\
					pdu[var]	+=	tmp*duPowers[j];												\
					pdv[var]	+=	tmpdv*uPowers[j];												\
				}																					\
				*intr++	=	(float) denominator;													\
			}																						\
																									\
			for (;var<vertexSize;var++) {															\
				double	res	=	0;																	\
				for (j=0;j<UORDER;j++) {															\
					double	tmp	=	0;																\
																									\
					for (t=0;t<VORDER;t++) {														\
						tmp		+=	(*cVertex++)*vPowers[t];										\
					}																				\
																									\
					res		+=	tmp*uPowers[j];														\
				}																					\
				*intr++	=	(float) res;															\
			}																						\
																									\
																									\
			const double	invDD	=	1 / (denominator*denominator);								\
			dPdu[0]		=	(float) ((pdu[0]*denominator - vertexStart[0]*pdu[3])*invDD);			\
			dPdu[1]		=	(float) ((pdu[1]*denominator - vertexStart[1]*pdu[3])*invDD);			\
			dPdu[2]		=	(float) ((pdu[2]*denominator - vertexStart[2]*pdu[3])*invDD);			\
																									\
			dPdv[0]		=	(float) ((pdv[0]*denominator - vertexStart[0]*pdv[3])*invDD);			\
			dPdv[1]		=	(float) ((pdv[1]*denominator - vertexStart[1]*pdv[3])*invDD);			\
			dPdv[2]		=	(float) ((pdv[2]*denominator - vertexStart[2]*pdv[3])*invDD);			\
																									\
			crossvv(N,dPdu,dPdv);																	\
																									\
			const double	invD	=	1 / (denominator);											\
			for (var=0;var<vertexSize;var++) {														\
				vertexStart[var]	=	(float) (vertexStart[var]*invD);							\
			}																						\
																									\
			vertexData		+=	vertexDataStep;														\
			dPdu			+=	3;																	\
			dPdv			+=	3;																	\
			N				+=	3;																	\
		}																							\
		}

		switch(uOrder) {
		case 0:
			assert(FALSE);
			break;
		case 1:
			assert(FALSE);
			break;
		case 2:
			switch(vOrder) {
			case 0:
				assert(FALSE);
				break;
			case 1:
				assert(FALSE);
				break;
			case 2:
				computeNURBS(2,2);
				break;
			case 3:
				computeNURBS(2,3);
				break;
			case 4:
				computeNURBS(2,4);
				break;
			case 5:
				computeNURBS(2,5);
				break;
			default:
				computeNURBS(uOrder,vOrder);
				break;
			}
			break;
		case 3:
			switch(vOrder) {
			case 0:
				assert(FALSE);
				break;
			case 1:
				assert(FALSE);
				break;
			case 2:
				computeNURBS(3,2);
				break;
			case 3:
				computeNURBS(3,3);
				break;
			case 4:
				computeNURBS(3,4);
				break;
			case 5:
				computeNURBS(3,5);
				break;
			default:
				computeNURBS(uOrder,vOrder);
				break;
			}
			break;
		case 4:
			switch(vOrder) {
			case 0:
				assert(FALSE);
				break;
			case 1:
				assert(FALSE);
				break;
			case 2:
				computeNURBS(4,2);
				break;
			case 3:
				computeNURBS(4,3);
				break;
			case 4:
				computeNURBS(4,4);
				break;
			case 5:
				computeNURBS(4,5);
				break;
			default:
				computeNURBS(uOrder,vOrder);
				break;
			}
			break;
		case 5:
			switch(vOrder) {
			case 0:
				assert(FALSE);
				break;
			case 1:
				assert(FALSE);
				break;
			case 2:
				computeNURBS(5,2);
				break;
			case 3:
				computeNURBS(5,3);
				break;
			case 4:
				computeNURBS(5,4);
				break;
			case 5:
				computeNURBS(5,5);
				break;
			default:
				computeNURBS(uOrder,vOrder);
				break;
			}
			break;
		default:
			computeNURBS(uOrder,vOrder);
			break;
		}

		// Note: make the common case fast: We're computing NG,DPDU and DPDV even if it's not required.
		// Most of the time though, surface normal is required

		// Dispatch the vertex data
		variables->dispatch(intrStart,start,numVertices,varying);

		// Convert to P
		{
			float		*P	=	varying[VARIABLE_P]		+	start*3;
			const float	*Pw	=	varying[VARIABLE_PW]	+	start*4;

			for (i=numVertices;i>=0;i--) {
				*P++	=	*Pw++;
				*P++	=	*Pw++;
				*P++	=	*Pw++;
				Pw++;
			}
		}

#undef computeNURBS
	}


	// Fix the degenerate normals
	normalFix();

	up	&=	~(PARAMETER_P | PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_NG | variables->parameters);

	memEnd();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CNURBSPatch
// Method				:	interpolate
// Description			:	See object.h
// Return Value			:	-
// Comments				:	-
// Date last edited		:	6/21/2001
void			CNURBSPatch::interpolate(int numVertices,float **varying) const {
	if (parameters != NULL)	parameters->dispatch(numVertices,varying);

	// Correct the parametric range of the primitive
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
}

///////////////////////////////////////////////////////////////////////
// Class				:	CNURBSMesh
// Method				:	precompBasisCoefficients
// Description			:	Compute the coefficients of a basis
// Return Value			:	-
// Comments				:
// Date last edited		:	6/22/2001
void		CNURBSPatch::precompBasisCoefficients(double *coefficients,unsigned int order,unsigned int start,unsigned int interval,const float *knots) {
	if (order == 1) {
		if (start == interval)
			coefficients[0]	=	1;
		else
			coefficients[0]	=	0;
	} else {

		memBegin();

		double	*lowerCoefficients1	=	(double *) ralloc((order-1)*sizeof(double));
		double	*lowerCoefficients2	=	(double *) ralloc((order-1)*sizeof(double));
		unsigned int		i;

		precompBasisCoefficients(lowerCoefficients1,order-1,start,interval,knots);
		precompBasisCoefficients(lowerCoefficients2,order-1,start+1,interval,knots);

		for (i=0;i<order;i++)	coefficients[i]	=	0;

		for (i=0;i<(order-1);i++)	{
			if (knots[start+order-1] != knots[start])
				coefficients[i+1]	+=	lowerCoefficients1[i]*(1/(knots[start+order-1] - knots[start]));
			
			if (knots[start+order] != knots[start+1])
				coefficients[i+1]	+= -lowerCoefficients2[i]*(1/(knots[start+order]-knots[start+1]));
		}

		for (i=0;i<(order-1);i++)	{
			if (knots[start+order-1] != knots[start])
				coefficients[i]		+=	-lowerCoefficients1[i]*(knots[start]/ (knots[start+order-1] - knots[start]));
			
			if (knots[start+order] != knots[start+1])
				coefficients[i]		+=	 lowerCoefficients2[i]*(knots[start+order]/(knots[start+order]-knots[start+1]));
		}

		memEnd();
	}
}























///////////////////////////////////////////////////////////////////////
// Function				:	CPatchMesh
// Description			:	CPatchMesh
// Return Value			:	Ctor
// Comments				:	-
// Date last edited		:	6/10/2003
CPatchMesh::CPatchMesh(CAttributes *a,CXform *x,CPl *c,int d,int nu,int nv,int uw,int vw) : CObject(a,x) {
	int			i;
	const float	*P;

	stats.numGprims++;
	stats.gprimMemory	+=	sizeof(CPatchMesh);

	pl			=	c;

	degree		=	d;
	uVertices	=	nu;
	vVertices	=	nv;
	uWrap		=	uw;
	vWrap		=	vw;

	// Compute the bounding box in the local object coordinate system
	initv(bmin,C_INFINITY,C_INFINITY,C_INFINITY);
	initv(bmax,-C_INFINITY,-C_INFINITY,-C_INFINITY);

	if (degree == 1) {
		for (P=pl->data0,i=0;i<(uVertices*vVertices);i++,P+=3) {
			addBox(bmin,bmax,P);
		}

		if (pl->data1 != NULL) {
			for (P=pl->data1,i=0;i<(uVertices*vVertices);i++,P+=3) {
				addBox(bmin,bmax,P);
			}
		}
	} else {
		int				i,j;
		float			uMult;
		float			vMult;
		int				upatches,vpatches;
		const int		us		=	attributes->uStep;
		const int		vs		=	attributes->vStep;
		double			xg[16],yg[16],zg[16];
		matrix			ut;

		assert(degree == 3);

		if (uWrap)	upatches	=	(uVertices ) / us;
		else		upatches	=	((uVertices - 4) / us)+1;

		if (vWrap)	vpatches	=	(vVertices) / vs;
		else		vpatches	=	((vVertices - 4) / vs)+1;

		uMult					=	1 / (float) upatches;
		vMult					=	1 / (float) vpatches;

		// Note that u basis and v basis are swapped to take the transpose into account done during the precomputation
		transposem(ut,attributes->uBasis);
		mulmmd(geometryV,invBezier,ut);
		mulmmd(geometryU,attributes->vBasis,invBezier);

		for (i=0;i<vpatches;i++) {
			for (j=0;j<upatches;j++) {
				const int	up	=	j*us;
				const int	vp	=	i*vs;
				int			r,c;

				// Fill in the geometry matrices
				for (r=0;r<4;r++) {
					for (c=0;c<4;c++) {
						int			y	=	(r + vp) % vVertices;
						int			x	=	(c + up) % uVertices;
						const float	*P	=	pl->data0 + (y*uVertices+x)*3;

						xg[element(r,c)]	=	P[COMP_X];
						yg[element(r,c)]	=	P[COMP_Y];
						zg[element(r,c)]	=	P[COMP_Z];
					}
				}

				makeCubicBound(bmin,bmax,xg,yg,zg);

				if (pl->data1 != NULL) {
					for (r=0;r<4;r++) {
						for (c=0;c<4;c++) {
							int			y	=	(r + vp) % vVertices;
							int			x	=	(c + up) % uVertices;
							const float	*P	=	pl->data1 + (y*uVertices+x)*3;

							xg[element(r,c)]	=	P[COMP_X];
							yg[element(r,c)]	=	P[COMP_Y];
							zg[element(r,c)]	=	P[COMP_Z];
						}
					}

					makeCubicBound(bmin,bmax,xg,yg,zg);
				}

			}
		}
	}

	children	=	NULL;
}

///////////////////////////////////////////////////////////////////////
// Function				:	CPatchMesh
// Description			:	~CPatchMesh
// Return Value			:	Dtor
// Comments				:	-
// Date last edited		:	6/10/2003
CPatchMesh::~CPatchMesh() {
	stats.numGprims--;
	stats.gprimMemory	-=	sizeof(CPatchMesh);

	delete pl;

	if (children != NULL) {
		CObject	**objects	=	children->array;
		int		numObjects	=	children->numItems;
		int		i;

		for (i=0;i<numObjects;i++)	objects[i]->detach();

		delete children;
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	CPatchMesh
// Description			:	bound
// Return Value			:	Bound the mesh
// Comments				:	-
// Date last edited		:	6/10/2003
void	CPatchMesh::bound(float *bmi,float *bma) const {
	movvv(bmi,bmin);
	movvv(bma,bmax);
	xform->transformBound(bmi,bma);
	makeBound(bmi,bma);
}

///////////////////////////////////////////////////////////////////////
// Function				:	CPatchMesh
// Description			:	copy
// Return Value			:	Clone the object
// Comments				:	-
// Date last edited		:	6/10/2003
void	CPatchMesh::copy(CAttributes *a,CXform *x,CRendererContext *c) const {
	CXform	*nx	=	new CXform(x);

	nx->concat(xform);	// Concetenate the local xform

	if (a == NULL)	a	=	attributes;

	c->addObject(new CPatchMesh(a,nx,pl->clone(a),degree,uVertices,vVertices,uWrap,vWrap));
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPatchMesh
// Method				:	tesselate
// Description			:	Tesselate the primitive if possible
// Return Value			:	-
// Comments				:
// Date last edited		:	5/28/2003
void	CPatchMesh::tesselate(CShadingContext *context)	{
	int		i;
	int		numChildren;
	CObject	**c;

	if (children == NULL)	create();

	numChildren	=	children->numItems;
	c			=	children->array;

	for (i=0;i<numChildren;i++) {
		c[i]->tesselate(context);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPatchMesh
// Method				:	dice
// Description			:	Dice the primitive
// Return Value			:	-
// Comments				:
// Date last edited		:	5/28/2003
void	CPatchMesh::dice(CShadingContext *rasterizer) {
	int		i;
	int		numChildren;
	CObject	**c;

	if (children == NULL)	create();

	numChildren	=	children->numItems;
	c			=	children->array;

	for (i=0;i<numChildren;i++) {
		vector	bmin,bmax;

		c[i]->bound(bmin,bmax);
		rasterizer->drawObject(c[i],bmin,bmax);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPatchMesh
// Method				:	split
// Description			:	Create the children
// Return Value			:	-
// Comments				:
// Date last edited		:	5/28/2003
void	CPatchMesh::create() {
	int				i,j,k;

	children			=	new CArray<CObject *>;

	memBegin();

	uvertices			=	uVertices;
	vvertices			=	vVertices;

	vertices			=	NULL;
	pl->transform(xform);
	pl->collect(vertexSize,vertices,CONTAINER_VERTEX);
	parameterList		=	pl;
	vertexData			=	pl->vertexData();
	vertexData->attach();

	if (degree == 1) {
		float			uMult;
		float			vMult;
		double			*vertex;
		CParameter		*parameters;
		int				upatches,vpatches;

		if (uWrap)	upatches	=	uvertices;
		else		upatches	=	uvertices-1;

		if (vWrap)	vpatches	=	vvertices;
		else		vpatches	=	vvertices-1;

		uMult					=	1 / (float) upatches;
		vMult					=	1 / (float) vpatches;

		uvaryings				=	uvertices;
		vvaryings				=	vvertices;

		for (k=0,i=0;i<vpatches;i++) {
			for (j=0;j<upatches;j++,k++) {
				float			uOrg		=	j * uMult;
				float			vOrg		=	i * vMult;
				CObject			*nObject;
				
				gatherData(j,i,2,2,j,i,k,vertex,parameters);

				nObject	=	new CBilinearPatch(attributes,xform,vertexData,parameters,uOrg,vOrg,uMult,vMult,vertex);

				nObject->attach();

				children->push(nObject);
			}
		}
	} else {
		int				i,j,k;
		float			uMult;
		float			vMult;
		double			*vertex;
		int				upatches,vpatches;
		CParameter		*parameters;
		const int		us		=	attributes->uStep;
		const int		vs		=	attributes->vStep;

		assert(degree == 3);

		if (uWrap)	upatches	=	(uvertices ) / us;
		else		upatches	=	((uvertices - 4) / us)+1;

		if (vWrap)	vpatches	=	(vvertices) / vs;
		else		vpatches	=	((vvertices - 4) / vs)+1;

		uMult					=	1 / (float) upatches;
		vMult					=	1 / (float) vpatches;

		uvaryings				=	(upatches+1-uWrap);
		vvaryings				=	(vpatches+1-vWrap);

		for (k=0,i=0;i<vpatches;i++) {
			for (j=0;j<upatches;j++,k++) {
				float			uOrg	=	j * uMult;
				float			vOrg	=	i * vMult;
				CObject			*nObject;

				gatherData(j*us,i*vs,4,4,j,i,k,vertex,parameters);

				nObject	=	new CBicubicPatch(attributes,xform,vertexData,parameters,uOrg,vOrg,uMult,vMult,vertex);

				nObject->attach();

				children->push(nObject);
			}
		}
	}

	vertexData->detach();

	memEnd();
}




















///////////////////////////////////////////////////////////////////////
// Function				:	CNURBSPatchMesh
// Description			:	CNURBSPatchMesh
// Return Value			:	Ctor
// Comments				:	-
// Date last edited		:	6/10/2003
CNURBSPatchMesh::CNURBSPatchMesh(CAttributes *a,CXform *x,CPl *c,int nu,int nv,int uo,int vo,float *uk,float *vk) : CObject(a,x) {
	int			i;
	const float	*P;

	stats.numGprims++;
	stats.gprimMemory	+=	sizeof(CNURBSPatchMesh) + (nu+uo)*sizeof(float) + (nv+vo)*sizeof(float);

	pl			=	c;

	uVertices	=	nu;
	vVertices	=	nv;
	uOrder		=	uo;
	vOrder		=	vo;
	uKnots		=	new float[uVertices+uOrder];	memcpy(uKnots,uk,(uVertices+uOrder)*sizeof(float));
	vKnots		=	new float[vVertices+vOrder];	memcpy(vKnots,vk,(vVertices+vOrder)*sizeof(float));

	initv(bmin,C_INFINITY,C_INFINITY,C_INFINITY);
	initv(bmax,-C_INFINITY,-C_INFINITY,-C_INFINITY);

	for (P=pl->data0,i=0;i<(uVertices*vVertices);i++,P+=4) {
		vector	tmp;

		tmp[0]	=	P[0] / P[3];
		tmp[1]	=	P[1] / P[3];
		tmp[2]	=	P[2] / P[3];
		addBox(bmin,bmax,tmp);
	}

	if (pl->data1 != NULL) {
		for (P=pl->data1,i=0;i<(uVertices*vVertices);i++,P+=4) {
			vector	tmp;

			tmp[0]	=	P[0] / P[3];
			tmp[1]	=	P[1] / P[3];
			tmp[2]	=	P[2] / P[3];
			addBox(bmin,bmax,tmp);
		}
	}

	children	=	NULL;
}

///////////////////////////////////////////////////////////////////////
// Function				:	CNURBSPatchMesh
// Description			:	~CNURBSPatchMesh
// Return Value			:	Dtor
// Comments				:	-
// Date last edited		:	6/10/2003
CNURBSPatchMesh::~CNURBSPatchMesh() {
	stats.numGprims--;
	stats.gprimMemory	-=	sizeof(CNURBSPatchMesh) + (uVertices+uOrder)*sizeof(float) + (vVertices+vOrder)*sizeof(float);

	delete [] uKnots;
	delete [] vKnots;
	delete pl;

	if (children != NULL) {
		CObject	**objects	=	children->array;
		int		numObjects	=	children->numItems;
		int		i;

		for (i=0;i<numObjects;i++)	objects[i]->detach();

		delete children;
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	CNURBSPatchMesh
// Description			:	bound
// Return Value			:	Bound the mesh
// Comments				:	-
// Date last edited		:	6/10/2003
void	CNURBSPatchMesh::bound(float *bmi,float *bma) const {
	movvv(bmi,bmin);
	movvv(bma,bmax);
	xform->transformBound(bmi,bma);
	makeBound(bmi,bma);
}

///////////////////////////////////////////////////////////////////////
// Function				:	CNURBSPatchMesh
// Description			:	clone
// Return Value			:	Clone the object
// Comments				:	-
// Date last edited		:	6/10/2003
void	CNURBSPatchMesh::copy(CAttributes *a,CXform *x,CRendererContext *c) const {
	CXform	*nx	=	new CXform(x);

	nx->concat(xform);	// Concetenate the local xform

	if (a == NULL)	a	=	attributes;

	c->addObject(new CNURBSPatchMesh(a,nx,pl->clone(a),uVertices,vVertices,uOrder,vOrder,uKnots,vKnots));
}

///////////////////////////////////////////////////////////////////////
// Class				:	CNURBSPatchMesh
// Method				:	tesselate
// Description			:	Tesselate the primitive if possible
// Return Value			:	-
// Comments				:
// Date last edited		:	5/28/2003
void	CNURBSPatchMesh::tesselate(CShadingContext *context)	{
	int		i;
	int		numChildren;
	CObject	**c;

	if (children == NULL)	create();

	numChildren	=	children->numItems;
	c			=	children->array;

	for (i=0;i<numChildren;i++) {
		c[i]->tesselate(context);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CNURBSPatchMesh
// Method				:	dice
// Description			:	Dice the primitive
// Return Value			:	-
// Comments				:
// Date last edited		:	5/28/2003
void	CNURBSPatchMesh::dice(CShadingContext *rasterizer) {
	int		i;
	int		numChildren;
	CObject	**c;

	if (children == NULL)	create();

	numChildren	=	children->numItems;
	c			=	children->array;

	for (i=0;i<numChildren;i++) {
		vector	bmin,bmax;

		c[i]->bound(bmin,bmax);
		rasterizer->drawObject(c[i],bmin,bmax);
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	CNURBSPatchMesh
// Description			:	split
// Return Value			:	Split the mesh
// Comments				:	-
// Date last edited		:	6/10/2003
void	CNURBSPatchMesh::create() {
	int				uPatches	=	uVertices - uOrder+1;
	int				vPatches	=	vVertices - vOrder+1;
	int				i,j,k;
	double			*vertex;
	int				upatches,vpatches;
	CParameter		*parameters;

	children		=	new CArray<CObject *>;

	uvertices		=	uVertices;
	vvertices		=	vVertices;
	upatches		=	uPatches;
	vpatches		=	vPatches;
	uvaryings		=	uVertices-uOrder+2;
	vvaryings		=	vVertices-vOrder+2;

	// Transform the core into the camera coordinate system
	vertices		=	NULL;
	pl->transform(xform);
	pl->collect(vertexSize,vertices,CONTAINER_VERTEX);
	parameterList	=	pl;
	vertexData		=	pl->vertexData();
	vertexData->attach();

	memBegin();

	// Create the NURBS patches
	for (k=0,j=0;j<vPatches;j++) {
		for (i=0;i<uPatches;i++,k++) {
			float	umin	=	uKnots[i+uOrder-1];
			float	umax	=	uKnots[i+uOrder];
			float	vmin	=	vKnots[j+vOrder-1];
			float	vmax	=	vKnots[j+vOrder];
			float	uint	=	umax	-	umin;
			float	vint	=	vmax	-	vmin;

			if ((uint == 0) || (vint == 0)) {
				// The patch does not have a valid parametric space, so just skip it
			} else {
				CObject	*nObject;

				gatherData(i,j,uOrder,vOrder,i,j,k,vertex,parameters);

				nObject	=	new CNURBSPatch(attributes,xform,vertexData,parameters,uOrder,vOrder,uKnots+i,vKnots+j,vertex);

				nObject->attach();

				children->push(nObject);
			}
		}
	}

	memEnd();

	vertexData->detach();
}

