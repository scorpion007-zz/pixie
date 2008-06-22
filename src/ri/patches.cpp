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
//  File				:	patches.cpp
//  Classes				:	CBilinearPatchMesh
//							CBicubicPatchMesh
//							CNURBSPatch
//  Description			:	Implementation
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "patches.h"
#include "stats.h"
#include "memory.h"
#include "shading.h"
#include "surface.h"
#include "error.h"
#include "patchUtils.h"
#include "renderer.h"
#include "rendererContext.h"
#include "common/polynomial.h"

#define	checkRay(rv)											\
	if (! (rv->flags & attributes->flags) )	return;				\
																\
	if (attributes->flags & ATTRIBUTES_FLAGS_LOD) {				\
		const float importance = attributes->lodImportance;		\
		if (importance >= 0) {									\
			if (rv->jimp > importance)			return;			\
		} else {												\
			if ((1-rv->jimp) >= -importance)	return;			\
		}														\
	}															\
																\
	if ((attributes->displacement != NULL) && (attributes->flags & ATTRIBUTES_FLAGS_DISPLACEMENTS)) {						\
		/* Do we have a grid ? */								\
		if (children == NULL) {									\
			osLock(CRenderer::tesselateMutex);					\
																\
			if (children == NULL) {								\
				CTesselationPatch	*tesselation	=	new CTesselationPatch(attributes,xform,this,0,1,0,1,0,0,-1);	\
				tesselation->initTesselation(context);			\
				tesselation->attach();							\
				children				=	tesselation;		\
			}													\
			osUnlock(CRenderer::tesselateMutex);				\
		}														\
		return;													\
	}

///////////////////////////////////////////////////////////////////////
// Macro				:	gatherData
// Description			:	Get the data to create the primitive
// Return Value			:	-
// Comments				:	-
#define	gatherData(__context,__u,__v,__nu,__nv,__uv,__vv,__un,__vertex,__parameters) {	\
	int			__i,__j;																\
	float		*__dest;																\
																						\
	assert(vertexSize > 0);																\
																						\
	if (__vertex == NULL)	__vertex = (float *) ralloc(vertexSize*(__nu)*(__nv)*sizeof(float),__context->threadMemory);	\
																						\
	__dest	=	__vertex;																\
																						\
	for (__j=0;__j<(__nv);__j++) {														\
		const int __vVertex	=	((__v) + __j) % vvertices;								\
		for (__i=0;__i<(__nu);__i++) {													\
			const int		__uVertex	=	((__u) + __i) % uvertices;					\
			const int		__index		=	__vVertex * uvertices + __uVertex;			\
			const float		*__src		=	vertices + __index*vertexSize;				\
			int				__k;														\
																						\
			for (__k=vertexSize;__k>0;__k--)	*__dest++	=	*__src++;				\
		}																				\
	}																					\
																						\
	__parameters	=	parameterList->uniform(__un,NULL);								\
																						\
	const int	__v0 =	(__vv)*uvaryings+(__uv);										\
	const int	__v1 =	(__vv)*uvaryings+(((__uv)+1) % uvaryings);						\
	const int	__v2 =	(((__vv)+1) % vvaryings)*uvaryings+(__uv);						\
	const int	__v3 =	(((__vv)+1) % vvaryings)*uvaryings+(((__uv)+1) % uvaryings);	\
	__parameters	=	parameterList->varying(__v0,__v1,__v2,__v3,__parameters);		\
}


///////////////////////////////////////////////////////////////////////
// Class				:	CBilinearPatch
// Method				:	CBilinearPatch
// Description			:	Ctor
// Return Value			:	-
// Comments				:	-
CBilinearPatch::CBilinearPatch(CAttributes *a,CXform *x,CVertexData *v,CParameter *p,float uOrg,float vOrg,float uMult,float vMult,float *vertex0) : CSurface(a,x) {

	atomicIncrement(&stats.numGprims);

	this->variables		=	v;
	this->variables->attach();
	this->parameters	=	p;
	this->uOrg			=	uOrg;
	this->vOrg			=	vOrg;
	this->uMult			=	uMult;
	this->vMult			=	vMult;

	// Copy the data
	const	int	vertexSize	=	v->vertexSize;
	if (variables->moving) {
		const float *src;
		int			i,j;
		float		*dest;

		dest	=	vertex	=	new float[vertexSize*8];

		src		=	vertex0;
		for (i=4;i>0;i--,src+=vertexSize) {
			for (j=vertexSize;j>0;j--)	*dest++ = (float) *src++;
		}

		src		=	vertex0 + vertexSize;
		for (i=4;i>0;i--,src+=vertexSize) {
			for (j=vertexSize;j>0;j--)	*dest++ = (float) *src++;
		}

	} else {
		int			i;
		float		*dest;

		dest	=	vertex	=	new float[vertexSize*4];

		for (i=vertexSize*4;i>0;i--) *dest++ = (float) *vertex0++;
	}

	// Compute the bounding box of the patch
	{
		float	*ver0,*ver1,*ver2,*ver3;
		int		vertexSize	=	variables->vertexSize;

		ver0	=	vertex;
		ver1	=	ver0	+	vertexSize;
		ver2	=	ver1	+	vertexSize;
		ver3	=	ver2	+	vertexSize;

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
	}

	makeBound(bmin,bmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CBilinearPatch
// Method				:	~CBilinearPatch
// Description			:	Dtor
// Return Value			:	-
// Comments				:	-
CBilinearPatch::~CBilinearPatch() {
	const	int	vertexSize	=	(variables->moving ? variables->vertexSize*2 : variables->vertexSize);

	atomicDecrement(&stats.numGprims);

	if (parameters	!= NULL)	delete parameters;
	delete [] vertex;

	variables->detach();
}



///////////////////////////////////////////////////////////////////////
// Class				:	CBilinearPatch
// Method				:	intersect
// Description			:	See object.h
// Return Value			:	-
// Comments				:	-
void	CBilinearPatch::intersect(CShadingContext *context,CRay *cRay) {

	checkRay(cRay);

	const int	vertexSize	=	variables->vertexSize;
	const float	*P00		=	vertex;
	const float	*P10		=	P00 + vertexSize;
	const float	*P01		=	P10 + vertexSize;
	const float	*P11		=	P01 + vertexSize;
	vector	t0,t1,t2,t3;

	if (variables->moving) {
		interpolatev(t0,P00,P00 + vertexSize*4,cRay->time);	P00	=	t0;
		interpolatev(t1,P10,P10 + vertexSize*4,cRay->time);	P10	=	t1;
		interpolatev(t2,P01,P01 + vertexSize*4,cRay->time);	P01	=	t2;
		interpolatev(t3,P11,P11 + vertexSize*4,cRay->time);	P11	=	t3;
	} 


	const float	*r			=	cRay->from;
	const float	*q			=	cRay->dir;
	vector		a,b,c,d;

	subvv(a,P11,P10);
	subvv(a,P01);
	addvv(a,P00);
	subvv(b,P10,P00);
	subvv(c,P01,P00);
	movvv(d,P00);

	const double	A1	=	a[COMP_X]*q[COMP_Z] - a[COMP_Z]*q[COMP_X];
	const double	B1	=	b[COMP_X]*q[COMP_Z] - b[COMP_Z]*q[COMP_X];
	const double	C1	=	c[COMP_X]*q[COMP_Z] - c[COMP_Z]*q[COMP_X];
	const double	D1	=	(d[COMP_X] - r[COMP_X])*q[COMP_Z] - (d[COMP_Z] - r[COMP_Z])*q[COMP_X];
	const double	A2	=	a[COMP_Y]*q[COMP_Z] - a[COMP_Z]*q[COMP_Y];
	const double	B2	=	b[COMP_Y]*q[COMP_Z] - b[COMP_Z]*q[COMP_Y];
	const double	C2	=	c[COMP_Y]*q[COMP_Z] - c[COMP_Z]*q[COMP_Y];
	const double	D2	=	(d[COMP_Y] - r[COMP_Y])*q[COMP_Z] - (d[COMP_Z] - r[COMP_Z])*q[COMP_Y];
	

#define solve()														\
	if ((v > 0) && (v < 1)) {										\
		{															\
			const double	a	=	v*A2 + B2;						\
			const double	b	=	v*(A2 - A1) + B2 - B1;			\
			if (b*b >= a*a)	u	=	(v*(C1 - C2) + D1 - D2) / b;	\
			else			u	=	(-v*C2 - D2) / a;				\
		}															\
																	\
		if ((u > 0) && (u < 1)) {									\
			double	P[3];											\
																	\
			P[0]	=	a[0]*u*v + b[0]*u + c[0]*v + d[0];			\
			P[1]	=	a[1]*u*v + b[1]*u + c[1]*v + d[1];			\
			P[2]	=	a[2]*u*v + b[2]*u + c[2]*v + d[2];			\
																	\
			if ((q[COMP_X]*q[COMP_X] >= q[COMP_Y]*q[COMP_Y]) && (q[COMP_X]*q[COMP_X] >= q[COMP_Z]*q[COMP_Z]))	\
				t	=	(P[COMP_X] - r[COMP_X]) / q[COMP_X];		\
			else if (q[COMP_Y]*q[COMP_Y] >= q[COMP_Z]*q[COMP_Z])	\
				t	=	(P[COMP_Y] - r[COMP_Y]) / q[COMP_Y];		\
			else													\
				t	=	(P[COMP_Z] - r[COMP_Z]) / q[COMP_Z];		\
																	\
			if ((t > cRay->tmin) && (t < cRay->t)) {				\
				vector	dPdu,dPdv,N;								\
				vector	tmp1,tmp2;									\
				subvv(tmp1,P10,P00);								\
				subvv(tmp2,P11,P01);								\
				interpolatev(dPdu,tmp1,tmp2,(float) v);				\
				subvv(tmp1,P01,P00);								\
				subvv(tmp2,P11,P10);								\
				interpolatev(dPdv,tmp1,tmp2,(float) u);				\
				crossvv(N,dPdu,dPdv);								\
				if ((attributes->flags & ATTRIBUTES_FLAGS_INSIDE) ^ xform->flip) mulvf(N,-1);	\
				if (attributes->flags & ATTRIBUTES_FLAGS_DOUBLE_SIDED) {						\
					cRay->object	=	this;						\
					cRay->u			=	(float) (u*uMult + uOrg);	\
					cRay->v			=	(float) (v*vMult + vOrg);	\
					cRay->t			=	(float) t;					\
					movvv(cRay->N,N);								\
				} else {											\
					if (dotvv(q,N) < 0) {							\
						cRay->object	=	this;					\
						cRay->u			=	(float) (u*uMult + uOrg);	\
						cRay->v			=	(float) (v*vMult + vOrg);	\
						cRay->t			=	(float) t;				\
						movvv(cRay->N,N);							\
					}												\
				}													\
			}														\
		}															\
	}
	


	double			roots[2];
	const int		i	=	solveQuadric<double>(A2*C1 - A1*C2,A2*D1 - A1*D2 + B2*C1 - B1*C2,B2*D1 - B1*D2,roots);
	double			u,v,t;

	switch (i) {
		case 0:
			break;
		case 1:
			v	=	roots[0];
			solve();
			break;
		case 2:
			v	=	roots[0];
			solve();
			v	=	roots[1];
			solve();
			break;
	}


}

///////////////////////////////////////////////////////////////////////
// Class				:	CBilinearPatch
// Method				:	sample
// Description			:	See object.h
// Return Value			:	-
// Comments				:	-
void	CBilinearPatch::sample(int start,int numVertices,float **varying,float ***locals,unsigned int &up) const {
	const float		*u				=	varying[VARIABLE_U]+start;
	const float		*v				=	varying[VARIABLE_V]+start;
	const int		vertexSize		=	variables->vertexSize;
	float			*vertexData;
	int				vertexDataStep;

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
			const float	*time		=	varying[VARIABLE_TIME] + start;
			const float	*vertex0	=	vertex;
			const float	*vertex1	=	vertex + vertexSize*4;

			vertexData		=	(float *) alloca(numVertices*vertexSize*4*sizeof(float));
			vertexDataStep	=	vertexSize*4;
			interpolate		=	vertexData;

			for (int i=numVertices;i>0;--i) {
				const double ctime	=	*time++;
				for (int j=0;j<vertexSize*4;++j) {
					*interpolate++	=	(float) (vertex0[j]*(1.0-ctime) + vertex1[j]*ctime);
				}
			}
		}
	}

	{	// Do the vertices
		// Interpolate the vertices
		float		*intr	=	(float *) alloca(numVertices*vertexSize*sizeof(float));
		const float	*v0		=	vertexData;
		const float	*v1		=	v0 + vertexSize;
		const float	*v2		=	v1 + vertexSize;
		const float	*v3		=	v2 + vertexSize;
		float		*tmp	=	intr;

		for (int i=0;i<numVertices;++i) {
			const double cu	=	*u++;
			const double cv	=	*v++;

			for (int j=0;j<vertexSize;++j) {
				*tmp++	=	(float) ((v0[j]*(1.0 - cu) + v1[j]*cu)*(1.0 - cv)	+
									 (v2[j]*(1.0 - cu) + v3[j]*cu)*cv);
			}

			v0			+=	vertexDataStep;
			v1			+=	vertexDataStep;
			v2			+=	vertexDataStep;
			v3			+=	vertexDataStep;
		}

		variables->dispatch(intr,start,numVertices,varying,locals);

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

				for (int i=0;i<numVertices;++i) {
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

				for (int i=0;i<numVertices;++i) {
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
	
	// Compute dPdtime
	if (up & PARAMETER_DPDTIME) {
		float	*dest	=	varying[VARIABLE_DPDTIME] + start*3;
		
		// Do we have motion?
		if (variables->moving) {
			const float	*u		=	varying[VARIABLE_U] + start;
			const float	*v		=	varying[VARIABLE_V] + start;
			const float	*v0		=	vertex;
			const float	*v1		=	v0 + vertexSize;
			const float	*v2		=	v1 + vertexSize;
			const float	*v3		=	v2 + vertexSize;
			for (int i=0;i<numVertices;++i,dest+=3) {
				const double cu	=	*u++;
				const double cv	=	*v++;

				// Sum over the components
				for (int j=0;j<3;++j) {
					const int	k	=	4*vertexSize + j;
					dest[j]			=	(float) ((((v0[k]*(1.0 - cu) + v1[k]*cu)*(1.0 - cv)	+ (v2[k]*(1.0 - cu) + v3[k]*cu)*cv - (v0[j]*(1.0 - cu) + v1[j]*cu)*(1.0 - cv)	+ (v2[j]*(1.0 - cu) + v3[j]*cu)*cv)));
				}
				
				// Scale the dPdtime
				mulvf(dest,CRenderer::invShutterTime);
			}
		} else {
			// We have no motion, so dPdtime is {0,0,0}
			for (int i=0;i<numVertices;++i,dest+=3)	initv(dest,0,0,0);
		}
	}

	// Fix the degenerate normals
	normalFix();

	// Turn off the parameters we computed
	up	&=	~(PARAMETER_P | PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_NG | PARAMETER_DPDTIME | variables->parameters);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CBilinearPatch
// Method				:	interpolate
// Description			:	See object.h
// Return Value			:	-
// Comments				:	-
void	CBilinearPatch::interpolate(int numVertices,float **varying,float ***locals) const {

	// Dispatch the parameters first
	if (parameters != NULL)	parameters->dispatch(numVertices,varying,locals);

	// Correct the parametric range of the primitive
	if ((uMult != 1) || (vMult != 1)) {
		float	*u		=	varying[VARIABLE_U];
		float	*v		=	varying[VARIABLE_V];
		float	*du		=	varying[VARIABLE_DU];
		float	*dv		=	varying[VARIABLE_DV];
		float	*dPdu	=	varying[VARIABLE_DPDU];
		float	*dPdv	=	varying[VARIABLE_DPDV];
		int		i;

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
CBicubicPatch::CBicubicPatch(CAttributes *a,CXform *x,CVertexData *v,CParameter *p,float uOrg,float vOrg,float uMult,float vMult,float *vertexData,const float *uBasis,const float *vBasis) : CSurface(a,x) {
	const unsigned int vertexSize	=	v->vertexSize;

	atomicIncrement(&stats.numGprims);

	variables	=	v;
	variables->attach();
	parameters	=	p;

	this->uOrg	=	uOrg;
	this->vOrg	=	vOrg;
	this->uMult	=	uMult;
	this->vMult	=	vMult;

	if (uBasis == NULL)	uBasis	=	attributes->uBasis;
	if (vBasis == NULL)	vBasis	=	attributes->vBasis;

	initv(bmin,C_INFINITY,C_INFINITY,C_INFINITY);
	initv(bmax,-C_INFINITY,-C_INFINITY,-C_INFINITY);

	if (variables->moving) {
		vertex	=	new float[vertexSize*32];

		computeVertexData(vertex					,vertexData,0,uBasis,vBasis);
		computeVertexData(vertex + vertexSize*16	,vertexData,vertexSize,uBasis,vBasis);
	} else {
		vertex	=	new float[vertexSize*16];

		computeVertexData(vertex,vertexData,0,uBasis,vBasis);
	}

	makeBound(bmin,bmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CBicubicPatch
// Method				:	~CBicubicPatch
// Description			:	Dtor
// Return Value			:	-
// Comments				:	-
CBicubicPatch::~CBicubicPatch() {
	const int	vertexSize	=	(variables->moving ? variables->vertexSize*2 : variables->vertexSize);

	atomicDecrement(&stats.numGprims);

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
void	CBicubicPatch::computeVertexData(float *vertex,const float *vertexData,int disp,const float *uBasis,const float *vBasis) {
	int					k,l;
	const int			vertexSize	=	variables->vertexSize;
	const int			vs			=	(variables->moving ? vertexSize*2 : vertexSize);
	dmatrix				data;
	dmatrix				ut,uB,vB;

	// Promote the basis to double
	for (k=0;k<16;k++) {
		uB[k]	=	uBasis[k];
		vB[k]	=	vBasis[k];
	}

	// Compute the utranspose
	transposem(ut,uB);

	// Compute the premultiplied geometry matrix
	for	(k=0;k<vertexSize;k++) {
		dmatrix			tmp,tmp2;
		unsigned int	x,y;

		for (y=0;y<4;y++)
			for (x=0;x<4;x++)
				data[element(y,x)]	=	vertexData[(y*4+x)*vs+k+disp];

		mulmm(tmp2,ut,data);
		mulmm(tmp,tmp2,vB);

		// Demote to float
		for (l=0;l<16;l++)	vertex[16*k+l]	=	(float) tmp[l];

		// Update the bounding box
		if (k < 3) {

			// Convert to the bezier control vertices
			mulmm(tmp2,dinvBezier,tmp);
			mulmm(tmp,tmp2,dinvBezier);

			// Expand the bound appropriately
			int	i;
			for (i=0;i<16;i++) {
				if (tmp[i] < bmin[k])	bmin[k]	=	(float) tmp[i];
				if (tmp[i] > bmax[k])	bmax[k]	=	(float) tmp[i];
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CBicubicPatch
// Method				:	sample
// Description			:	See object.h
// Return Value			:	-
// Comments				:	-
void	CBicubicPatch::sample(int start,int numVertices,float **varying,float ***locals,unsigned int &up) const {
	const float			*u					=	varying[VARIABLE_U]+start;
	const float			*v					=	varying[VARIABLE_V]+start;
	const int			vertexSize			=	variables->vertexSize;
	float				*vertexData;
	int					vertexDataStep;

	assert(vertexSize > 0);

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
			float			*interpolate;
			const float		*time		=	varying[VARIABLE_TIME] + start;
			const float		*vertex0	=	vertex;
			const float		*vertex1	=	vertex + vertexSize*16;

			vertexData		=	(float *) alloca(numVertices*vertexSize*16*sizeof(float));
			vertexDataStep	=	vertexSize*16;
			interpolate		=	vertexData;

			for (int i=numVertices;i>0;--i) {
				const double	ctime	=	*time++;

				for (int j=0;j<vertexDataStep;++j) {
					*interpolate++	=	(float) (vertex0[j]*(1.0-ctime) + vertex1[j]*ctime);
				}
			}
		}
	}

	{	// Do the vertices
		float	*intr		=	(float *) alloca(vertexSize*numVertices*sizeof(float));
		float	*data;
		float	*intrStart	=	intr;
		float	*dPdu		=	varying[VARIABLE_DPDU] + start*3;
		float	*dPdv		=	varying[VARIABLE_DPDV] + start*3;
		float	*N			=	varying[VARIABLE_NG] + start*3;

		// Interpolate the vertices
		for (int i=0;i<numVertices;++i) {
			double			tmp1[4],tmp2[4];
			const double	cu			=	u[i];
			const double 	cv			=	v[i];
			const double	usquared	=	cu*cu;
			const double	ucubed		=	cu*usquared;
			const double	vsquared	=	cv*cv;
			const double	vcubed		=	cv*vsquared;
			int				j;

			for (data=vertexData,j=0;j<3;++j) {
				for (int t=0;t<4;++t) {
					tmp2[t]	=	3*vsquared*data[element(0,t)] + 2*cv*data[element(1,t)]     + data[element(2,t)];
					tmp1[t]	=	  vcubed*  data[element(0,t)] + vsquared*data[element(1,t)] + cv*data[element(2,t)] + data[element(3,t)];
				}

				dPdv[j]			=	(float) (tmp2[0]*ucubed + tmp2[1]*usquared + tmp2[2]*cu + tmp2[3]);
				dPdu[j]			=	(float) (tmp1[0]*3*usquared + tmp1[1]*2*cu + tmp1[2]);
				*intr++			=	(float) (tmp1[0]*ucubed + tmp1[1]*usquared + tmp1[2]*cu + tmp1[3]);
				data			+=	16;
			}

			for (;j<vertexSize;++j) {
				for (int t=0;t<4;t++) {
					tmp1[t]		=	  vcubed*  data[element(0,t)] + vsquared*data[element(1,t)] + cv*data[element(2,t)] + data[element(3,t)];
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
		
		// Sanity check
		assert(intr == intrStart + numVertices*vertexSize);

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
			assert(u == (varying[VARIABLE_U] + start));
			assert(v == (varying[VARIABLE_V] + start));
			const int	disp	=	vertexSize*16;
			for (int i=0;i<numVertices;++i,dest+=3) {
				int				j;
				double			tmpStart[4],tmpEnd[4];
				const double	cu			=	u[i];
				const double 	cv			=	v[i];
				const double	usquared	=	cu*cu;
				const double	ucubed		=	cu*usquared;
				const double	vsquared	=	cv*cv;
				const double	vcubed		=	cv*vsquared;
				float			*data;

				// For each component
				for (data=vertex,j=0;j<3;j++,data+=16) {
				
					// Do the partial computation
					for (int t=0;t<4;t++) {
						tmpStart[t]	=	  vcubed*  data[element(0,t)]			+ vsquared*data[element(1,t)]			+ cv*data[element(2,t)]			+ data[element(3,t)];
						tmpEnd[t]	=	  vcubed*  data[disp + element(0,t)]	+ vsquared*data[disp + element(1,t)]	+ cv*data[disp + element(2,t)]	+ data[disp + element(3,t)];
					}

					// Compute the result
					dest[j]			=	(float) ((tmpEnd[0]*ucubed + tmpEnd[1]*usquared + tmpEnd[2]*cu + tmpEnd[3]) - (tmpStart[0]*ucubed + tmpStart[1]*usquared + tmpStart[2]*cu + tmpStart[3]));
				}
				
				// Scale the dPdtime
				mulvf(dest,CRenderer::invShutterTime);
			}
		} else {
			// We have no motion, so dPdtime is {0,0,0}
			for (int i=0;i<numVertices;++i,dest+=3)	initv(dest,0,0,0);
		}
	}
	
	// Fix the degenerate normals
	normalFix();

	up	&=	~(PARAMETER_P | PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_NG | PARAMETER_DPDTIME | variables->parameters);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CBicubicPatch
// Method				:	interpolate
// Description			:	See object.h// Return Value			:	-
// Comments				:	-
void	CBicubicPatch::interpolate(int numVertices,float **varying,float ***locals) const {

	// Dispatch the parameters first
	if (parameters != NULL)	parameters->dispatch(numVertices,varying,locals);

	// Correct the parametric range of the primitive
	if ((uMult != 1) || (vMult != 1)) {
		float	*u		=	varying[VARIABLE_U];
		float	*v		=	varying[VARIABLE_V];
		float	*du		=	varying[VARIABLE_DU];
		float	*dv		=	varying[VARIABLE_DV];
		float	*dPdu	=	varying[VARIABLE_DPDU];
		float	*dPdv	=	varying[VARIABLE_DPDV];
		int		i;

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
CNURBSPatch::CNURBSPatch(CAttributes *a,CXform *x,CVertexData *v,CParameter *p,int uOrder,int vOrder,float *uKnots,float *vKnots,float *vertex0) : CSurface(a,x) {
	int			j;
	const int	vertexSize	=	v->vertexSize;

	atomicIncrement(&stats.numGprims);

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

	double	*uCoefficients		=	(double *) alloca(uOrder*uOrder*sizeof(double));
	double	*vCoefficients		=	(double *) alloca(vOrder*vOrder*sizeof(double));

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
	} else {
		vertex	=	new double[uOrder*vOrder*vertexSize];

		precomputeVertexData(vertex								,uCoefficients,vCoefficients,vertex0,0);
	}

	makeBound(bmin,bmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CNURBSPatch
// Method				:	~CNURBSPatch
// Description			:	Dtor
// Return Value			:	-
// Comments				:	-
CNURBSPatch::~CNURBSPatch() {
	const int vertexSize	=	(variables->moving ? variables->vertexSize*2 : variables->vertexSize);

	atomicDecrement(&stats.numGprims);

	if (parameters	!= NULL) delete parameters;
	delete [] vertex;

	variables->detach();
}


///////////////////////////////////////////////////////////////////////
// Class				:	CNURBSPatch
// Method				:	precomputeVertexData
// Description			:	Precompute uBasis*G*vBasis'
// Return Value			:	-
// Comments				:	-
void	CNURBSPatch::precomputeVertexData(double *vertex,const double *uCoefficients,const double *vCoefficients,float *vertexData,int disp) {
	const int	vertexSize	=	variables->vertexSize;
	const int	vs			=	(variables->moving ? vertexSize*2 : vertexSize);
	int			i,j,k;
	double		*cVertex;
	double		*tmp		=	(double *) alloca(uOrder*vOrder*sizeof(double));

	for (cVertex=vertex,i=0;i<vertexSize;i++,cVertex+=uOrder*vOrder) {
		int		u,v;

		for (j=0;j<uOrder*vOrder;j++)	cVertex[j]	=	0;

		for (v=0;v<vOrder;v++) {
			const double *vRow	=	&vCoefficients[v*vOrder];
			for (u=0;u<uOrder;u++) {
				const double	data	=	vertexData[i+(v*uOrder+u)*vs+disp];
				const double	*uRow	=	&uCoefficients[u*uOrder];

				for (j=0;j<uOrder;j++) {
					for (k=0;k<vOrder;k++) {
						cVertex[j*vOrder+k]	+=	data*uRow[j]*vRow[k];
					}
				}
			}
		}
	}

	// Update the bounding box
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
// Method				:	sample
// Description			:	See object.h
// Return Value			:	-
// Comments				:	-
void	CNURBSPatch::sample(int start,int numVertices,float **varying,float ***locals,unsigned int &up) const {
	const float			*u			=	varying[VARIABLE_U]+start;
	const float			*v			=	varying[VARIABLE_V]+start;
	int					vertexSize	=	variables->vertexSize;
	double				*vertexData;
	int					vertexDataStep;

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
			const double	*vertex0	=	vertex;
			const double	*vertex1	=	vertex + vertexSize*uOrder*vOrder;

			vertexData		=	(double *) alloca(numVertices*vertexSize*uOrder*vOrder*sizeof(double));
			vertexDataStep	=	vertexSize*uOrder*vOrder;
			interpolate		=	vertexData;

			for (int i=numVertices;i>0;--i) {
				const double ctime	=	*time++;
				for (int j=0;j<vertexDataStep;++j) {
					*interpolate++	=	(float) (vertex0[j]*(1.0-ctime) + vertex1[j]*ctime);
				}
			}
		}
	}

	{	// Do the vertices
		float	*intr			=	(float *) alloca(vertexSize*numVertices*sizeof(float));
		float	*intrStart		=	intr;
		float	*dPdu			=	varying[VARIABLE_DPDU] + start*3;
		float	*dPdv			=	varying[VARIABLE_DPDV] + start*3;
		float	*N				=	varying[VARIABLE_NG] + start*3;
		float	*vertexStart;
		double	pdu[4];
		double	pdv[4];
		
#define computeNURBS(UORDER,VORDER) {																\
		double	*memBase		=	(double *) alloca((UORDER*3 + VORDER*3)*sizeof(double));		\
		double	*uPowers		=	memBase;														\
		double	*vPowers		=	uPowers + UORDER;												\
		double	*duPowers		=	vPowers + VORDER;												\
		double	*dvPowers		=	duPowers + UORDER;												\
																									\
		for (int i=0;i<numVertices;++i) {															\
			double			denominator;															\
			const double	cu	=	u[i]*uMult + uOrg;												\
			const double	cv	=	v[i]*vMult + vOrg;												\
																									\
			uPowers[0]		=	1;																	\
			duPowers[0]		=	0;																	\
			for (int j=1;j<UORDER;++j) {															\
				uPowers[j]	=	cu*uPowers[j-1];													\
				duPowers[j]	=	j*uPowers[j-1];														\
			}																						\
																									\
			vPowers[0]		=	1;																	\
			dvPowers[0]		=	0;																	\
			for (int j=1;j<VORDER;++j) {															\
				vPowers[j]	=	cv*vPowers[j-1];													\
				dvPowers[j]	=	j*vPowers[j-1];														\
			}																						\
																									\
			const double *cVertex	=	vertexData;													\
			vertexStart		=	intr;																\
			int	var;																				\
			for (var=0;var<4;++var) {																\
				denominator		=	0;																\
				pdu[var]		=	0;																\
				pdv[var]		=	0;																\
				for (int j=0;j<UORDER;++j) {														\
					double	tmp		=	0;															\
					double	tmpdv	=	0;															\
																									\
					for (int t=0;t<VORDER;++t,++cVertex) {											\
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
			for (;var<vertexSize;++var) {															\
				double	res	=	0;																	\
				for (int j=0;j<UORDER;++j) {														\
					double	tmp	=	0;																\
																									\
					for (int t=0;t<VORDER;++t) {													\
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
			for (var=0;var<vertexSize;++var) {														\
				vertexStart[var]	=	(float) (vertexStart[var]*invD);							\
			}																						\
																									\
			vertexData		+=	vertexDataStep;														\
			dPdu			+=	3;																	\
			dPdv			+=	3;																	\
			N				+=	3;																	\
		}																							\
		}

#define compute()																					\
		switch(uOrder) {																			\
		case 0:	assert(FALSE);	break;																\
		case 1:	assert(FALSE);	break;																\
		case 2:																						\
			switch(vOrder) {																		\
			case 0:		assert(FALSE);					break;										\
			case 1:		assert(FALSE);					break;										\
			case 2:		computeNURBS(2,2);				break;										\
			case 3:		computeNURBS(2,3);				break;										\
			case 4:		computeNURBS(2,4);				break;										\
			case 5:		computeNURBS(2,5);				break;										\
			default:	computeNURBS(uOrder,vOrder);	break;										\
			}																						\
			break;																					\
		case 3:																						\
			switch(vOrder) {																		\
			case 0:		assert(FALSE);					break;										\
			case 1:		assert(FALSE);					break;										\
			case 2:		computeNURBS(3,2);				break;										\
			case 3:		computeNURBS(3,3);				break;										\
			case 4:		computeNURBS(3,4);				break;										\
			case 5:		computeNURBS(3,5);				break;										\
			default:	computeNURBS(uOrder,vOrder);	break;										\
			}																						\
			break;																					\
		case 4:																						\
			switch(vOrder) {																		\
			case 0:		assert(FALSE);					break;										\
			case 1:		assert(FALSE);					break;										\
			case 2:		computeNURBS(4,2);				break;										\
			case 3:		computeNURBS(4,3);				break;										\
			case 4:		computeNURBS(4,4);				break;										\
			case 5:		computeNURBS(4,5);				break;										\
			default:	computeNURBS(uOrder,vOrder);	break;										\
			}																						\
			break;																					\
		case 5:																						\
			switch(vOrder) {																		\
			case 0:		assert(FALSE);					break;										\
			case 1:		assert(FALSE);					break;										\
			case 2:		computeNURBS(5,2);				break;										\
			case 3:		computeNURBS(5,3);				break;										\
			case 4:		computeNURBS(5,4);				break;										\
			case 5:		computeNURBS(5,5);				break;										\
			default:	computeNURBS(uOrder,vOrder);	break;										\
			}																						\
			break;																					\
		default:	computeNURBS(uOrder,vOrder);	break;											\
		}
		
		// Do the computation
		compute();

		// Note: make the common case fast: We're computing NG,DPDU and DPDV even if it's not required.
		// Most of the time though, surface normal is required
		
		// Dispatch the vertex data
		variables->dispatch(intrStart,start,numVertices,varying,locals);

		// Convert to P
		{
			float		*P	=	varying[VARIABLE_P]		+	start*3;
			const float	*Pw	=	varying[VARIABLE_PW]	+	start*4;

			for (int i=numVertices;i>0;i--,P+=3,Pw+=4)	movvv(P,Pw);
		}
	}

		
	// Compute dPdtime
	if (up & PARAMETER_DPDTIME) {
		float	*dest	=	varying[VARIABLE_DPDTIME] + start*3;
		
		// Do we have motion?
		if (variables->moving) {
			// OK, here's the tricky point, 
			const int	disp	=	vertexSize*uOrder*vOrder;
#undef computeNURBS
#define computeNURBS(UORDER,VORDER) {															\
	double	*memBase		=	(double *) alloca((UORDER*3 + VORDER*3)*sizeof(double));		\
	double	*uPowers		=	memBase;														\
	double	*vPowers		=	uPowers + UORDER;												\
																								\
	for (int i=0;i<numVertices;++i,dest+=3) {													\
		double			Pstart[4],Pend[4];														\
		const double	cu	=	u[i]*uMult + uOrg;												\
		const double	cv	=	v[i]*vMult + vOrg;												\
																								\
		uPowers[0]		=	1;																	\
		for (int j=1;j<UORDER;++j) {															\
			uPowers[j]	=	cu*uPowers[j-1];													\
		}																						\
																								\
		vPowers[0]		=	1;																	\
		for (int j=1;j<VORDER;++j) {															\
			vPowers[j]	=	cv*vPowers[j-1];													\
		}																						\
																								\
		const double *cVertex	=	vertex;														\
		for (int var=0;var<4;++var) {															\
			Pstart[var]	=	Pend[var]	=	0;													\
			for (int j=0;j<UORDER;++j) {														\
				double	tmpStart	=	0;														\
				double	tmpEnd		=	0;														\
																								\
				for (int t=0;t<VORDER;++t,++cVertex) {											\
					tmpStart	+=	cVertex[0]*vPowers[t];										\
					tmpEnd		+=	cVertex[disp]*vPowers[t];									\
				}																				\
																								\
				Pstart[var]	+=	tmpStart*uPowers[j];											\
				Pend[var]	+=	tmpEnd*uPowers[j];												\
			}																					\
		}																						\
																								\
																								\
		mulvf(Pstart,1/Pstart[3]);																\
		mulvf(Pend,1/Pend[3]);																	\
		dest[0]		=	(float) (Pend[0] - Pstart[0]);											\
		dest[1]		=	(float) (Pend[1] - Pstart[1]);											\
		dest[2]		=	(float) (Pend[2] - Pstart[2]);											\
		mulvf(dest,CRenderer::invShutterTime);													\
	}																							\
	}
	
		compute();

		} else {
			// We have no motion, so dPdtime is {0,0,0}
			for (int i=0;i<numVertices;++i,dest+=3)	initv(dest,0,0,0);
		}
	}
	
#undef computeNURBS
#undef compute


	// Fix the degenerate normals
	normalFix();

	// Turn off the computed parameters
	up	&=	~(PARAMETER_P | PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_NG | PARAMETER_DPDTIME | variables->parameters);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CNURBSPatch
// Method				:	interpolate
// Description			:	See object.h
// Return Value			:	-
// Comments				:	-
void			CNURBSPatch::interpolate(int numVertices,float **varying,float ***locals) const {

	// Dispatch the parameters first
	if (parameters != NULL)	parameters->dispatch(numVertices,varying,locals);

	// Correct the parametric range of the primitive
	if ((uMult != 1) || (vMult != 1)) {
		float *u	=	varying[VARIABLE_U];
		float *v	=	varying[VARIABLE_V];
		float *du	=	varying[VARIABLE_DU];
		float *dv	=	varying[VARIABLE_DV];
		float *dPdu	=	varying[VARIABLE_DPDU];
		float *dPdv	=	varying[VARIABLE_DPDV];
		int	  i;

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
void		CNURBSPatch::precompBasisCoefficients(double *coefficients,unsigned int order,unsigned int start,unsigned int interval,const float *knots) {
	if (order == 1) {
		if (start == interval)
			coefficients[0]	=	1;
		else
			coefficients[0]	=	0;
	} else {

		double			*lowerCoefficients1	=	(double *) alloca((order-1)*sizeof(double));
		double			*lowerCoefficients2	=	(double *) alloca((order-1)*sizeof(double));
		unsigned int	i;

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
	}
}























///////////////////////////////////////////////////////////////////////
// Function				:	CPatchMesh
// Description			:	CPatchMesh
// Return Value			:	Ctor
// Comments				:	-
CPatchMesh::CPatchMesh(CAttributes *a,CXform *x,CPl *c,int d,int nu,int nv,int uw,int vw) : CObject(a,x) {
	int			i;
	const float	*P;

	atomicIncrement(&stats.numGprims);

	pl			=	c;
	degree		=	d;
	uVertices	=	nu;
	vVertices	=	nv;
	uWrap		=	uw;
	vWrap		=	vw;

	// Compute the bounding box in the camera system
	initv(bmin,C_INFINITY,C_INFINITY,C_INFINITY);
	initv(bmax,-C_INFINITY,-C_INFINITY,-C_INFINITY);

	if (degree == 1) {
		vector	tmp;

		for (P=pl->data0,i=0;i<(uVertices*vVertices);i++,P+=3) {
			mulmp(tmp,xform->from,P);
			addBox(bmin,bmax,tmp);
		}

		if (pl->data1 != NULL) {
			const float *from = (xform->next != NULL) ? xform->next->from : xform->from;
			for (P=pl->data1,i=0;i<(uVertices*vVertices);i++,P+=3) {
				mulmp(tmp,from,P);
				addBox(bmin,bmax,tmp);
			}
		} else if (xform->next != NULL) {
			const float *from = xform->next->from;
			for (P=pl->data0,i=0;i<(uVertices*vVertices);i++,P+=3) {
				mulmp(tmp,from,P);
				addBox(bmin,bmax,tmp);
			}
		}
	} else {
		int				i,j;
		float			uMult;
		float			vMult;
		int				upatches,vpatches;
		const int		us		=	attributes->uStep;
		const int		vs		=	attributes->vStep;
		dmatrix			xg,yg,zg;
		matrix			ub;
		dmatrix			ut,vb;
		dmatrix			geometryU,geometryV;

		assert(degree == 3);

		if (uWrap)	upatches	=	(uVertices ) / us;
		else		upatches	=	((uVertices - 4) / us)+1;

		if (vWrap)	vpatches	=	(vVertices) / vs;
		else		vpatches	=	((vVertices - 4) / vs)+1;

		uMult					=	1 / (float) upatches;
		vMult					=	1 / (float) vpatches;

		// Note that u basis and v basis are swapped to take the transpose into account done during the precomputation
		transposem(ub,attributes->uBasis);

		// Promote the precision
		for (i=0;i<16;i++)	{
			ut[i]	=	ub[i];
			vb[i]	=	attributes->vBasis[i];
		}

		mulmm(geometryV,dinvBezier,ut);
		mulmm(geometryU,vb,dinvBezier);

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
				
				makeCubicBoundX(bmin,bmax,xg,yg,zg,xform);

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
					
					if (xform->next != NULL) {
						makeCubicBoundX(bmin,bmax,xg,yg,zg,xform->next);
					} else {
						makeCubicBoundX(bmin,bmax,xg,yg,zg,xform);
					}
				} else if (xform->next != NULL) {
					makeCubicBoundX(bmin,bmax,xg,yg,zg,xform->next);
				}
			}
		}
	}
	
	makeBound(bmin,bmax);

	// Create the synchronization object
	osCreateMutex(mutex);
}

///////////////////////////////////////////////////////////////////////
// Function				:	CPatchMesh
// Description			:	~CPatchMesh
// Return Value			:	Dtor
// Comments				:	-
CPatchMesh::~CPatchMesh() {
	atomicDecrement(&stats.numGprims);

	if (pl != NULL)	delete pl;

	// Delete the synchronization object
	osDeleteMutex(mutex);
}


///////////////////////////////////////////////////////////////////////
// Function				:	CPatchMesh
// Description			:	instantiate
// Return Value			:	Clone the object
// Comments				:	-
void	CPatchMesh::instantiate(CAttributes *a,CXform *x,CRendererContext *c) const {
	CXform	*nx	=	new CXform(x);

	nx->concat(xform);	// Concetenate the local xform

	if (a == NULL)	a	=	attributes;

	assert(pl != NULL);

	c->addObject(new CPatchMesh(a,nx,pl->clone(a),degree,uVertices,vVertices,uWrap,vWrap));
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPatchMesh
// Method				:	intersect
// Description			:	Intersect a ray with this pritimive
// Return Value			:	-
// Comments				:
void	CPatchMesh::intersect(CShadingContext *rasterizer,CRay *ray) {

	if (children == NULL)	create(rasterizer);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPatchMesh
// Method				:	dice
// Description			:	Dice the primitive
// Return Value			:	-
// Comments				:
void	CPatchMesh::dice(CShadingContext *rasterizer) {

	if (children == NULL)	create(rasterizer);

	CObject::dice(rasterizer);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPatchMesh
// Method				:	split
// Description			:	Create the children
// Return Value			:	-
// Comments				:
void	CPatchMesh::create(CShadingContext *context) {

	osLock(mutex);
	if (children != NULL) {
		osUnlock(mutex);
		return;
	}

	int				i,j,k;
	int				uvaryings,vvaryings;
	int				uvertices,vvertices;
	CPl				*parameterList;
	CVertexData		*vertexData;
	float			*vertices;
	int				vertexSize;
	CObject			*allChildren	=	NULL;

	memBegin(context->threadMemory);

	uvertices			=	uVertices;
	vvertices			=	vVertices;

	vertices			=	NULL;
	pl->transform(xform);
	pl->collect(vertexSize,vertices,CONTAINER_VERTEX,context->threadMemory);
	parameterList		=	pl;
	vertexData			=	pl->vertexData();
	vertexData->attach();

	if (degree == 1) {
		float			uMult;
		float			vMult;
		float			*vertex	=	NULL;
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
				
				gatherData(context,j,i,2,2,j,i,k,vertex,parameters);

				nObject				=	new CBilinearPatch(attributes,xform,vertexData,parameters,uOrg,vOrg,uMult,vMult,vertex);

				nObject->sibling	=	allChildren;
				allChildren			=	nObject;
			}
		}
	} else {
		int				i,j,k;
		float			uMult;
		float			vMult;
		float			*vertex	=	NULL;
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

				gatherData(context,j*us,i*vs,4,4,j,i,k,vertex,parameters);

				nObject				=	new CBicubicPatch(attributes,xform,vertexData,parameters,uOrg,vOrg,uMult,vMult,vertex);

				nObject->sibling	=	allChildren;
				allChildren			=	nObject;
			}
		}
	}

	vertexData->detach();

	memEnd(context->threadMemory);

	// We're done with the parameter list
	delete pl;
	pl	=	NULL;

	// Set the children pointer
	setChildren(context,allChildren);
	
	// Release the lock
	osUnlock(mutex);
}




















///////////////////////////////////////////////////////////////////////
// Function				:	CNURBSPatchMesh
// Description			:	CNURBSPatchMesh
// Return Value			:	Ctor
// Comments				:	-
CNURBSPatchMesh::CNURBSPatchMesh(CAttributes *a,CXform *x,CPl *c,int nu,int nv,int uo,int vo,float *uk,float *vk) : CObject(a,x) {
	int			i;
	const float	*P;

	atomicIncrement(&stats.numGprims);

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
		htpoint	tmp;

		mulmp4(tmp,xform->from,P);
		mulvf(tmp,1/tmp[3]);
		addBox(bmin,bmax,tmp);
	}

	if (pl->data1 != NULL) {
		const float *from = (xform->next != NULL) ? xform->next->from : xform->from;
		for (P=pl->data1,i=0;i<(uVertices*vVertices);i++,P+=4) {
			htpoint	tmp;

			mulmp4(tmp,from,P);
			mulvf(tmp,1/tmp[3]);
			addBox(bmin,bmax,tmp);
		}
	} else if (xform->next != NULL) {
		const float *from = xform->next->from;
		for (P=pl->data0,i=0;i<(uVertices*vVertices);i++,P+=4) {
			htpoint	tmp;
	
			mulmp4(tmp,from,P);
			mulvf(tmp,1/tmp[3]);
			addBox(bmin,bmax,tmp);
		}
	}

	makeBound(bmin,bmax);

	// Create the synch. object
	osCreateMutex(mutex);
}

///////////////////////////////////////////////////////////////////////
// Function				:	CNURBSPatchMesh
// Description			:	~CNURBSPatchMesh
// Return Value			:	Dtor
// Comments				:	-
CNURBSPatchMesh::~CNURBSPatchMesh() {
	atomicDecrement(&stats.numGprims);

	delete [] uKnots;
	delete [] vKnots;
	delete pl;

	// We're done with the synch. object
	osDeleteMutex(mutex);
}


///////////////////////////////////////////////////////////////////////
// Function				:	CNURBSPatchMesh
// Description			:	instantiate
// Return Value			:	Clone the object
// Comments				:	-
void	CNURBSPatchMesh::instantiate(CAttributes *a,CXform *x,CRendererContext *c) const {
	CXform	*nx	=	new CXform(x);

	nx->concat(xform);	// Concetenate the local xform

	if (a == NULL)	a	=	attributes;

	c->addObject(new CNURBSPatchMesh(a,nx,pl->clone(a),uVertices,vVertices,uOrder,vOrder,uKnots,vKnots));
}

///////////////////////////////////////////////////////////////////////
// Class				:	CNURBSPatchMesh
// Method				:	dice
// Description			:	Dice the primitive
// Return Value			:	-
// Comments				:
void	CNURBSPatchMesh::intersect(CShadingContext *rasterizer,CRay *ray) {

	if (children == NULL)	create(rasterizer);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CNURBSPatchMesh
// Method				:	dice
// Description			:	Dice the primitive
// Return Value			:	-
// Comments				:
void	CNURBSPatchMesh::dice(CShadingContext *rasterizer) {

	if (children == NULL)	create(rasterizer);

	CObject::dice(rasterizer);
}

///////////////////////////////////////////////////////////////////////
// Function				:	CNURBSPatchMesh
// Description			:	split
// Return Value			:	Split the mesh
// Comments				:	-
void	CNURBSPatchMesh::create(CShadingContext *context) {

	osLock(mutex);
	if (children != NULL) {
		osUnlock(mutex);
		return;
	}

	const int		uPatches		=	uVertices - uOrder+1;
	const int		vPatches		=	vVertices - vOrder+1;
	int				i,j,k;
	float			*vertex			=	NULL;
	CParameter		*parameters;
	CPl				*parameterList;
	CVertexData		*vertexData;
	float			*vertices;
	int				vertexSize;
	CObject			*allChildren	=	NULL;


	const int	uvertices		=	uVertices;
	const int	vvertices		=	vVertices;
	const int	upatches		=	uPatches;
	const int	vpatches		=	vPatches;
	const int	uvaryings		=	uVertices-uOrder+2;
	const int	vvaryings		=	vVertices-vOrder+2;

	// Transform the core into the camera coordinate system
	vertices		=	NULL;
	pl->transform(xform);
	pl->collect(vertexSize,vertices,CONTAINER_VERTEX,context->threadMemory);
	parameterList	=	pl;
	vertexData		=	pl->vertexData();
	vertexData->attach();

	memBegin(context->threadMemory);

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

				gatherData(context,i,j,uOrder,vOrder,i,j,k,vertex,parameters);

				nObject				=	new CNURBSPatch(attributes,xform,vertexData,parameters,uOrder,vOrder,uKnots+i,vKnots+j,vertex);

				nObject->sibling	=	allChildren;
				allChildren			=	nObject;
			}
		}
	}

	memEnd(context->threadMemory);

	vertexData->detach();

	// Set the children 
	setChildren(context,allChildren);

	// Release the lock
	osUnlock(mutex);
}

