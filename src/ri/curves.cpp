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
//  File				:	curves.cpp
//  Classes				:	CCurve
//  Description			:	Curve primitive
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "curves.h"
#include "renderer.h"
#include "memory.h"
#include "stats.h"

// The inverse of the Bezier basis
static	matrix	invBezier	=	{	0,	0,				0,				1,
									0,	0,				1/(float) 3,	1,
									0,	1/(float) 3,	2/(float) 3,	1,
									1,	1,				1,				1};

// Temp variable
static	matrix	geometryMatrix;


///////////////////////////////////////////////////////////////////////
// Function				:	makeCubicBound
// Description			:	Converts the control vertices to Bezier control vertices
// Return Value			:	-
// Comments				:
// Date last edited		:	5/25/2004
static	inline	void	makeCubicBound(float *bmin,float *bmax,const float *v0,const float *v1,const float *v2,const float *v3) {
	htpoint	tmp,tmp2;
	vector	vtmp0,vtmp1,vtmp2,vtmp3;

	tmp[0]			=	v0[COMP_X];
	tmp[1]			=	v1[COMP_X];
	tmp[2]			=	v2[COMP_X];
	tmp[3]			=	v3[COMP_X];
	mulpm4(tmp2,tmp,geometryMatrix);
	vtmp0[COMP_X]	=	tmp2[0];
	vtmp1[COMP_X]	=	tmp2[1];
	vtmp2[COMP_X]	=	tmp2[2];
	vtmp3[COMP_X]	=	tmp2[3];

	tmp[0]			=	v0[COMP_Y];
	tmp[1]			=	v1[COMP_Y];
	tmp[2]			=	v2[COMP_Y];
	tmp[3]			=	v3[COMP_Y];
	mulpm4(tmp2,tmp,geometryMatrix);
	vtmp0[COMP_Y]	=	tmp2[0];
	vtmp1[COMP_Y]	=	tmp2[1];
	vtmp2[COMP_Y]	=	tmp2[2];
	vtmp3[COMP_Y]	=	tmp2[3];

	tmp[0]			=	v0[COMP_Z];
	tmp[1]			=	v1[COMP_Z];
	tmp[2]			=	v2[COMP_Z];
	tmp[3]			=	v3[COMP_Z];
	mulpm4(tmp2,tmp,geometryMatrix);
	vtmp0[COMP_Z]	=	tmp2[0];
	vtmp1[COMP_Z]	=	tmp2[1];
	vtmp2[COMP_Z]	=	tmp2[2];
	vtmp3[COMP_Z]	=	tmp2[3];

	addBox(bmin,bmax,vtmp0);
	addBox(bmin,bmax,vtmp1);
	addBox(bmin,bmax,vtmp2);
	addBox(bmin,bmax,vtmp3);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CCurve
// Method				:	CCurve
// Description			:	Ctor
// Return Value			:	-
// Comments				:	
// Date last edited		:	6/2/2003
CCurve::CCurve(CAttributes *a,CXform *x,CBase *b,float vmi,float vma,float gvmi,float gvma) : CSurface(a,x) {
	stats.numGprims++;
	stats.gprimCoreMemory	+=	sizeof(CCurve);

	vmin				=	vmi;
	vmax				=	vma;
	gvmin				=	gvmi;
	gvmax				=	gvma;
	base				=	b;
	base->attach();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CCurve
// Method				:	~CCurve
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	6/2/2003
CCurve::~CCurve() {
	stats.numGprims--;
	stats.gprimCoreMemory	-=	sizeof(CCurve);

	base->detach();
}


///////////////////////////////////////////////////////////////////////
// Class				:	CCubicCurve
// Method				:	interpolate
// Description			:	Interpolate the junk
// Return Value			:	-
// Comments				:
// Date last edited		:	6/2/2003
void			CCurve::interpolate(int numVertices,float **varying) const {
	float	*v	=	varying[VARIABLE_V];
	int		i;

	if (base->parameters != NULL)	base->parameters->dispatch(numVertices,varying);

	for (i=numVertices;i>0;i--) {
		*v++	=	(gvmax - gvmin)*v[0] + gvmin;
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CCubicCurve
// Method				:	CCurve
// Description			:	Dice the curve group into smaller ones
// Return Value			:	-
// Comments				:
// Date last edited		:	6/2/2003
void			CCurve::dice(CShadingContext *rasterizer) {
	memBegin();

	// We can sample the object, so do so
	float	**varying		=	rasterizer->currentShadingState->varying;
	float	*u				=	varying[VARIABLE_U];
	float	*v				=	varying[VARIABLE_V];
	float	*time			=	varying[VARIABLE_TIME];
	float	*P;
	int		shouldSplit;
	int		numPoints;
	vector	bmin,bmax;

	// Sample 3 points on the curve
	*v++			=	vmin;
	*v++			=	(vmin + vmax) * 0.5f;
	*v++			=	vmax;
	*u++			=	0;
	*u++			=	0;
	*u++			=	0;
	*time++			=	0;
	*time++			=	0;
	*time++			=	0;

	// Sample the curves
	rasterizer->displace(this,1,3,1,PARAMETER_P | PARAMETER_BEGIN_SAMPLE);

	// Compute the curve bounding box
	P				=	varying[VARIABLE_P];
	initv(bmin,C_INFINITY,C_INFINITY,C_INFINITY);
	initv(bmax,-C_INFINITY,-C_INFINITY,-C_INFINITY);
	addBox(bmin,bmax,P);
	addBox(bmin,bmax,P+3);
	addBox(bmin,bmax,P+6);

	shouldSplit		=	FALSE;
	if (bmin[COMP_Z] < C_EPSILON) {
		if (bmax[COMP_Z] < rasterizer->clipMin) {
			numPoints		=	-1;
		} else if (rasterizer->inFrustrum(bmin,bmax) == FALSE) {
			// The curve is out of the viewing frustrum
			numPoints		=	-1;
		} else {
			// Split the curve into two pieces
			numPoints		=	0;
			shouldSplit		=	TRUE;
		}
	} else {
		float	dx,dy;
		int		j;

		// we can do the perspective division
		rasterizer->camera2pixels(3,P);

		dx				=	P[6+0] - P[0];
		dy				=	P[6+1] - P[1];
		j				=	(int) ceil(C_EPSILON + sqrt(dx*dx + dy*dy) / attributes->shadingRate);

		if ((j + 1) < rasterizer->maxGridSize) {
			// We can shade this curve
			numPoints	=	j;
		} else {
			// We can not shade this curve - so split into two
			numPoints	=	0;
			shouldSplit	=	TRUE;
		}
	}

	if (shouldSplit) {
		splitToChildren(rasterizer);
	} else {
		if (numPoints > 0) {
			rasterizer->drawRibbon(this,numPoints,vmin,vmax);
		}
	}

	memEnd();
}




























///////////////////////////////////////////////////////////////////////
// Class				:	CCubicCurve
// Method				:	CCubicCurve
// Description			:	Ctor
// Return Value			:	-
// Comments				:	
// Date last edited		:	6/2/2003
CCubicCurve::CCubicCurve(CAttributes *a,CXform *x,CBase *b,float vmi,float vma,float gvmi,float gvma) : CCurve(a,x,b,vmi,vma,gvmi,gvma) {
}

///////////////////////////////////////////////////////////////////////
// Class				:	CCubicCurve
// Method				:	~CCubicCurve
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	6/2/2003
CCubicCurve::~CCubicCurve() {
}

///////////////////////////////////////////////////////////////////////
// Class				:	CCubicCurve
// Method				:	sample
// Description			:	Sample the curves
// Return Value			:	-
// Comments				:
// Date last edited		:	6/2/2003
void			CCubicCurve::sample(int start,int numVertices,float **varying,unsigned int &up) const {
	int				i,k;
	float			*intr,*intrStart;
	const	float	*v					=	varying[VARIABLE_V] + start;
	const	float	*vBasis				=	attributes->vBasis;
	CVertexData		*variables			=	base->variables;
	const	int		vertexSize			=	variables->vertexSize;
	const	int		vs					=	(variables->moving ? vertexSize*2 : vertexSize);
	const	float	*v0;
	const	float	*v1;
	const	float	*v2;
	const	float	*v3;
	float			*N;


	memBegin();

	intr	=	intrStart	=	(float *) ralloc(numVertices*vertexSize*sizeof(float));

	if ((variables->moving == FALSE) || (up & PARAMETER_BEGIN_SAMPLE)) {
		v0		=	base->vertex;
		v1		=	v0 + vs;
		v2		=	v1 + vs;
		v3		=	v2 + vs;
	} else {
		v0		=	base->vertex + vertexSize;
		v1		=	v0 + vs;
		v2		=	v1 + vs;
		v3		=	v2 + vs;
	}

	N		=	varying[VARIABLE_NG] + start*3;

	for (i=0;i<numVertices;i++) {
		const	float	cv				=	*v++;
		float			vb[4];
		float			tmp[4];

		vb[3]	=	1;
		vb[2]	=	cv;
		vb[1]	=	cv*cv;
		vb[0]	=	cv*vb[1];

		tmp[0]	=	vb[0]*vBasis[element(0,0)] + vb[1]*vBasis[element(0,1)] + vb[2]*vBasis[element(0,2)] + vb[3]*vBasis[element(0,3)];
		tmp[1]	=	vb[0]*vBasis[element(1,0)] + vb[1]*vBasis[element(1,1)] + vb[2]*vBasis[element(1,2)] + vb[3]*vBasis[element(1,3)];
		tmp[2]	=	vb[0]*vBasis[element(2,0)] + vb[1]*vBasis[element(2,1)] + vb[2]*vBasis[element(2,2)] + vb[3]*vBasis[element(2,3)];
		tmp[3]	=	vb[0]*vBasis[element(3,0)] + vb[1]*vBasis[element(3,1)] + vb[2]*vBasis[element(3,2)] + vb[3]*vBasis[element(3,3)];

		*intr++	=	*N++	=	tmp[0]*v0[0] + tmp[1]*v1[0] + tmp[2]*v2[0] + tmp[3]*v3[0];
		*intr++	=	*N++	=	tmp[0]*v0[1] + tmp[1]*v1[1] + tmp[2]*v2[1] + tmp[3]*v3[1];
		*intr++	=	*N++	=	tmp[0]*v0[2] + tmp[1]*v1[2] + tmp[2]*v2[2] + tmp[3]*v3[2];

		for (k=3;k<vertexSize;k++) {
			*intr++	=	tmp[0]*v0[k] + tmp[1]*v1[k] + tmp[2]*v2[k] + tmp[3]*v3[k];
		}
	}

	if (up & (PARAMETER_DPDU | PARAMETER_DPDV)) {
		float	*dPdv	=	varying[VARIABLE_DPDV] + start*3;
		float	*dPdu	=	varying[VARIABLE_DPDU] + start*3;

		v	=	varying[VARIABLE_V] + start*3;

		for (i=0;i<numVertices;i++) {
			const	float	cv				=	*v++;
			float			vb[4];
			float			tmp[4];

			vb[3]	=	0;
			vb[2]	=	1;
			vb[1]	=	2*cv;
			vb[0]	=	3*cv*cv;

			tmp[0]	=	vb[0]*vBasis[element(0,0)] + vb[1]*vBasis[element(0,1)] + vb[2]*vBasis[element(0,2)];
			tmp[1]	=	vb[0]*vBasis[element(1,0)] + vb[1]*vBasis[element(1,1)] + vb[2]*vBasis[element(1,2)];
			tmp[2]	=	vb[0]*vBasis[element(2,0)] + vb[1]*vBasis[element(2,1)] + vb[2]*vBasis[element(2,2)];
			tmp[3]	=	vb[0]*vBasis[element(3,0)] + vb[1]*vBasis[element(3,1)] + vb[2]*vBasis[element(3,2)];

			*dPdv++	=	tmp[0]*v0[0] + tmp[1]*v1[0] + tmp[2]*v2[0] + tmp[3]*v3[0];
			*dPdv++	=	tmp[0]*v0[1] + tmp[1]*v1[1] + tmp[2]*v2[1] + tmp[3]*v3[1];
			*dPdv++	=	tmp[0]*v0[2] + tmp[1]*v1[2] + tmp[2]*v2[2] + tmp[3]*v3[2];

			*dPdu++	=	0;
			*dPdu++	=	0;
			*dPdu++	=	0;
		}
	}

	variables->dispatch(intrStart,0,numVertices,varying);

	up	&=	~(PARAMETER_P | PARAMETER_NG | PARAMETER_DPDU | PARAMETER_DPDV | variables->parameters);

	memEnd();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CCubicCurve
// Method				:	dice
// Description			:	Dice the curve group into smaller ones
// Return Value			:	-
// Comments				:
// Date last edited		:	6/2/2003
void			CCubicCurve::bound(float *bmin,float *bmax) const {
	const CVertexData	*variables	=	base->variables;
	const int			vertexSize	=	variables->vertexSize;
	const int			vs			=	(variables->moving ? vertexSize*2 : vertexSize);
	const float			*vertex		=	base->vertex;
	const float			*v0			=	vertex;
	const float			*v1			=	v0 + vs;
	const float			*v2			=	v1 + vs;
	const float			*v3			=	v2 + vs;

	initv(bmin,C_INFINITY,C_INFINITY,C_INFINITY);
	initv(bmax,-C_INFINITY,-C_INFINITY,-C_INFINITY);

	mulmm(geometryMatrix,attributes->vBasis,invBezier);

	makeCubicBound(bmin,bmax,v0,v1,v2,v3);
	
	if (variables->moving) {
		v0	+=	vertexSize;
		v1	+=	vertexSize;
		v2	+=	vertexSize;
		v3	+=	vertexSize;

		makeCubicBound(bmin,bmax,v0,v1,v2,v3);
	}

	subvf(bmin,base->maxSize);
	addvf(bmax,base->maxSize);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CCubicCurve
// Method				:	dice
// Description			:	Dice the curve group into smaller ones
// Return Value			:	-
// Comments				:
// Date last edited		:	6/2/2003
void			CCubicCurve::splitToChildren(CShadingContext *rasterizer) {
	CCubicCurve		*cGroup;
	float			vmid		=	(vmin + vmax) * 0.5f;
	vector			bmin,bmax;

	// Create vmin - vmid group
	cGroup	=	new CCubicCurve(attributes,xform,base,vmin,vmid,gvmin,gvmax);
	cGroup->bound(bmin,bmax);
	rasterizer->drawObject(cGroup,bmin,bmax);

	// Create vmid - vmax group
	cGroup	=	new CCubicCurve(attributes,xform,base,vmid,vmax,gvmin,gvmax);
	cGroup->bound(bmin,bmax);
	rasterizer->drawObject(cGroup,bmin,bmax);
}


















///////////////////////////////////////////////////////////////////////
// Class				:	CLinearCurve
// Method				:	CLinearCurve
// Description			:	Ctor
// Return Value			:	-
// Comments				:	
// Date last edited		:	6/2/2003
CLinearCurve::CLinearCurve(CAttributes *a,CXform *x,CBase *b,float vmi,float vma,float gvmi,float gvma) : CCurve(a,x,b,vmi,vma,gvmi,gvma) {
}

///////////////////////////////////////////////////////////////////////
// Class				:	CLinearCurve
// Method				:	~CLinearCurve
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	6/2/2003
CLinearCurve::~CLinearCurve() {
}

///////////////////////////////////////////////////////////////////////
// Class				:	CLinearCurve
// Method				:	sample
// Description			:	Sample the curves
// Return Value			:	-
// Comments				:
// Date last edited		:	6/2/2003
void			CLinearCurve::sample(int start,int numVertices,float **varying,unsigned int &up) const {
	int				j,k;
	float			*intr,*intrStart;
	const	float	*v					=	varying[VARIABLE_V];
	CVertexData		*variables			=	base->variables;
	const	int		vertexSize			=	variables->vertexSize;
	const	int		vs					=	(variables->moving ? vertexSize*2 : vertexSize);
	const	int		numSavedVertices	=	numVertices;
	const	float	*v0;
	const	float	*v1;
	float			*N;

	memBegin();

	intr	=	intrStart	=	(float *) ralloc(numVertices*vertexSize*sizeof(float));

	if ((variables->moving == FALSE) || (up & PARAMETER_BEGIN_SAMPLE)) {
		v0					=	base->vertex;
		v1					=	v0 + vs;
	} else {
		v0					=	base->vertex + vertexSize;
		v1					=	v0 + vs;
	}

	N						=	varying[VARIABLE_NG] + start*3;

	for (j=numVertices;j>0;j--) {
		const	float	cv	=	*v++;

		*intr++	=	*N++	=	v0[0]*(1-cv) + v1[0]*cv;
		*intr++	=	*N++	=	v0[1]*(1-cv) + v1[1]*cv;
		*intr++	=	*N++	=	v0[2]*(1-cv) + v1[2]*cv;

		for (k=3;k<vertexSize;k++) {
			*intr++			=	v0[k]*(1-cv) + v1[k]*cv;
		}
	}

	if (up & (PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_N)) {
		float	*dPdv	=	varying[VARIABLE_DPDV] + start*3;
		float	*dPdu	=	varying[VARIABLE_DPDU] + start*3;

		for (j=numVertices;j>0;j--) {
			*dPdv++	=	v1[0] - v0[0];
			*dPdv++	=	v1[1] - v0[1];
			*dPdv++	=	v1[2] - v0[2];
			*dPdu++	=	0;
			*dPdu++	=	0;
			*dPdu++	=	0;
		}
	}

	variables->dispatch(intrStart,0,numSavedVertices,varying);

	up	&=	~(PARAMETER_P | PARAMETER_NG | PARAMETER_DPDU | PARAMETER_DPDV | variables->parameters);

	memEnd();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CLinearCurve
// Method				:	dice
// Description			:	Dice the curve group into smaller ones
// Return Value			:	-
// Comments				:
// Date last edited		:	6/2/2003
void			CLinearCurve::bound(float *bmin,float *bmax) const {
	const CVertexData	*variables	=	base->variables;
	const int			vertexSize	=	variables->vertexSize;
	const float			*vertex		=	base->vertex;
	int					i;

	if (variables->moving)	i	=	4;
	else					i	=	2;

	initv(bmin,C_INFINITY,C_INFINITY,C_INFINITY);
	initv(bmax,-C_INFINITY,-C_INFINITY,-C_INFINITY);

	for (;i>0;i--,vertex+=vertexSize)	addBox(bmin,bmax,vertex);

	subvf(bmin,base->maxSize);
	addvf(bmax,base->maxSize);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CLinearCurve
// Method				:	split
// Description			:	Dice the curve group into smaller ones
// Return Value			:	-
// Comments				:
// Date last edited		:	6/2/2003
void			CLinearCurve::splitToChildren(CShadingContext *rasterizer) {
	CLinearCurve	*cGroup;
	const float		vmid				=	(vmin + vmax) * 0.5f;
	vector			bmin,bmax;

	// Create vmin - vmid group
	cGroup	=	new CLinearCurve(attributes,xform,base,vmin,vmid,gvmin,gvmax);
	cGroup->bound(bmin,bmax);
	rasterizer->drawObject(cGroup,bmin,bmax);

	// Create vmid - vmax group
	cGroup	=	new CLinearCurve(attributes,xform,base,vmid,vmax,gvmin,gvmax);
	cGroup->bound(bmin,bmax);
	rasterizer->drawObject(cGroup,bmin,bmax);
}














///////////////////////////////////////////////////////////////////////
// Function				:	CCurveMesh
// Description			:	CCurveMesh
// Return Value			:	Ctor
// Comments				:	-
// Date last edited		:	6/10/2003
CCurveMesh::CCurveMesh(CAttributes *a,CXform *x,CPl *c,int d,int nv,int nc,int *nve,int w) : CObject(a,x) {
	int			i;
	const float	*P;
	const float	expansion	=	powf(fabsf(determinantm(xform->from)), 1.0f / 3.0f);
	float		*vertex;

	stats.numGprims++;
	stats.gprimMemory		+=	sizeof(CCurveMesh) + sizeof(int)*nc;

	pl			=	c;

	numVertices	=	nv;
	numCurves	=	nc;
	degree		=	d;
	nverts		=	new int[numCurves];				memcpy(nverts,nve,sizeof(int)*numCurves);
	wrap		=	w;

	// Extract the size parameter
	sizeVariable				=	NULL;
	maxSize						=	0;
	for (vertex=pl->data0,i=0;i<pl->numParameters;i++) {
		const CVariable	*cVar	=	pl->parameters[i].variable;

		if ((strcmp(cVar->name,"width") == 0) || (strcmp(cVar->name,"constantwidth") == 0)) {
			const	int	np	=	pl->parameters[i].numItems;

			sizeVariable		=	cVar;

			for (i=0;i<np;i++) {
				vertex[i]		*=	expansion;
				maxSize			=	max(maxSize,vertex[i]);
			}

			if (pl->data1 != NULL) {
				vertex	=	pl->data1 + (vertex - pl->data0) - np;

				for (i=0;i<np;i++) {
					vertex[i]		*=	expansion;
					maxSize			=	max(maxSize,vertex[i]);
				}
			}

			break;
		}

		vertex	+=	pl->parameters[i].numItems*cVar->numFloats;
	}

	if (sizeVariable == NULL)	maxSize	=	1;
	maxSize		*=	0.5f;

	// Compute the bound

	initv(bmin,C_INFINITY,C_INFINITY,C_INFINITY);
	initv(bmax,-C_INFINITY,-C_INFINITY,-C_INFINITY);

	if (degree == 1) {
		for (P=pl->data0,i=numVertices;i>0;i--,P+=3) {
			addBox(bmin,bmax,P);
		}

		if (pl->data1 != NULL) {
			for (P=pl->data1,i=numVertices;i>0;i--,P+=3) {
				addBox(bmin,bmax,P);
			}
		}
	} else {
		int				k			=	0;
		int				cVertex		=	0;

		mulmm(geometryMatrix,attributes->vBasis,invBezier);

		for (i=0;i<numCurves;i++) {
			const	int	ncsegs	=	(wrap == FALSE ? (nverts[i] - 4) / attributes->vStep + 1 : nverts[i] / attributes->vStep);
			int			j;

			for (j=0;j<ncsegs;j++,k++) {
				float	*v0		=	pl->data0 + (cVertex+(j*attributes->vStep + 0) % nverts[i])*3;
				float	*v1		=	pl->data0 + (cVertex+(j*attributes->vStep + 1) % nverts[i])*3;
				float	*v2		=	pl->data0 + (cVertex+(j*attributes->vStep + 2) % nverts[i])*3;
				float	*v3		=	pl->data0 + (cVertex+(j*attributes->vStep + 3) % nverts[i])*3;

				makeCubicBound(bmin,bmax,v0,v1,v2,v3);

				if (pl->data1 != NULL) {
					v0			=	pl->data1 + (cVertex+(j*attributes->vStep + 0) % nverts[i])*3;
					v1			=	pl->data1 + (cVertex+(j*attributes->vStep + 1) % nverts[i])*3;
					v2			=	pl->data1 + (cVertex+(j*attributes->vStep + 2) % nverts[i])*3;
					v3			=	pl->data1 + (cVertex+(j*attributes->vStep + 3) % nverts[i])*3;

					makeCubicBound(bmin,bmax,v0,v1,v2,v3);
				}
			}

			cVertex				+=	nverts[i];
		}
	}

	addvf(bmax,maxSize);
	subvf(bmin,maxSize);

	children	=	NULL;
}

///////////////////////////////////////////////////////////////////////
// Function				:	CCurveMesh
// Description			:	~CCurveMesh
// Return Value			:	Dtor
// Comments				:	-
// Date last edited		:	6/10/2003
CCurveMesh::~CCurveMesh() {
	stats.numGprims--;
	stats.gprimMemory	-=	sizeof(CCurveMesh) + sizeof(int)*numCurves;

	delete pl;
	delete [] nverts;

	if (children != NULL) {
		CObject	**c	=	children->array;
		int		i	=	children->numItems;

		for (;i>0;i--)	(*c++)->detach();

		delete children;
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	CCurveMesh
// Description			:	bound
// Return Value			:	Bound the mesh
// Comments				:	-
// Date last edited		:	6/10/2003
void	CCurveMesh::bound(float *bmi,float *bma) const {
	movvv(bmi,bmin);
	movvv(bma,bmax);
	xform->transformBound(bmi,bma);
	makeBound(bmi,bma);
}

///////////////////////////////////////////////////////////////////////
// Function				:	CCurveMesh
// Description			:	clone
// Return Value			:	Clone the object
// Comments				:	-
// Date last edited		:	6/10/2003
void	CCurveMesh::copy(CAttributes *a,CXform *x,CRendererContext *c) const {
	CXform	*nx	=	new CXform(x);

	nx->concat(xform);	// Concetenate the local xform

	if (a == NULL)	a	=	attributes;

	c->addObject(new CCurveMesh(a,nx,pl->clone(a),degree,numVertices,numCurves,nverts,wrap));
}

///////////////////////////////////////////////////////////////////////
// Class				:	CCurveMesh
// Method				:	tesselate
// Description			:	Tesselate the primitive if possible
// Return Value			:	-
// Comments				:
// Date last edited		:	5/28/2003
void	CCurveMesh::tesselate(CShadingContext *context)	{
	// We can not be raytraced
}

///////////////////////////////////////////////////////////////////////
// Class				:	CCurveMesh
// Method				:	dice
// Description			:	Dice the primitive
// Return Value			:	-
// Comments				:
// Date last edited		:	5/28/2003
void	CCurveMesh::dice(CShadingContext *rasterizer) {
	int		i;
	CObject	**c;

	if (children == NULL)	create();

	c	=	children->array;
	i	=	children->numItems;

	for (;i>0;i--) {
		(*c++)->dice(rasterizer);
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CCurveMesh
// Method				:	dice
// Description			:	Dice the primitive
// Return Value			:	-
// Comments				:
// Date last edited		:	5/28/2003
void	CCurveMesh::create() {
	int					i;
	CVertexData			*variables;
	int					vertexSize;
	float				*vertex;

	children			=	new CArray<CObject *>;

	vertex	=	NULL;
	pl->transform(xform);								// Transform the core
	pl->collect(vertexSize,vertex,CONTAINER_VERTEX);	// Obtain the vertex data

	// Allocate the variables
	variables		=	pl->vertexData();

	memBegin();

	// Instanciate
	if (degree == 3) {
		float			*baseVertex;
		int				t			=	0;
		int				k			=	0;
		int				cVertex		=	0;

		for (baseVertex=vertex,i=0;i<numCurves;i++) {
			const	int	ncsegs	=	(wrap == FALSE ? (nverts[i] - 4) / attributes->vStep + 1 : nverts[i] / attributes->vStep);
			int			j;
			const	int	nvars	=	ncsegs + 1 - wrap;

			for (j=0;j<ncsegs;j++,k++) {
				float			*v0		=	baseVertex + (cVertex+(j*attributes->vStep + 0) % nverts[i])*vertexSize;
				float			*v1		=	baseVertex + (cVertex+(j*attributes->vStep + 1) % nverts[i])*vertexSize;
				float			*v2		=	baseVertex + (cVertex+(j*attributes->vStep + 2) % nverts[i])*vertexSize;
				float			*v3		=	baseVertex + (cVertex+(j*attributes->vStep + 3) % nverts[i])*vertexSize;
				CParameter		*parameters;
				CCurve			*cCurve;
				CCurve::CBase	*base	=	new CCurve::CBase;
				const float		vmin	=	j / (float) ncsegs;
				const float		vmax	=	(j+1) / (float) ncsegs;

				parameters			=	pl->uniform(i,NULL);
				parameters			=	pl->varying(t+j,t+(j+1)%nvars,parameters);

				variables->attach();
				base->maxSize		=	maxSize;
				base->variables		=	variables;
				base->sizeVariable	=	sizeVariable;
				base->parameters	=	parameters;
				base->vertex		=	new float[vertexSize*4];
				memcpy(base->vertex + 0*vertexSize,v0,vertexSize*sizeof(float));
				memcpy(base->vertex + 1*vertexSize,v1,vertexSize*sizeof(float));
				memcpy(base->vertex + 2*vertexSize,v2,vertexSize*sizeof(float));
				memcpy(base->vertex + 3*vertexSize,v3,vertexSize*sizeof(float));

				cCurve				=	new CCubicCurve(attributes,xform,base,0,1,vmin,vmax);
				cCurve->attach();
				children->push(cCurve);
				
			}

			cVertex					+=	nverts[i];
			t						+=	nvars;
		}
	} if (degree == 1) {
		float			*baseVertex;
		int				k			=	0;
		int				t			=	0;
		int				cVertex		=	0;

		for (baseVertex=vertex,i=0;i<numCurves;i++) {
			const	int	ncsegs	=	(wrap == FALSE ? nverts[i] - 1: nverts[i]);
			int			j;
			const	int	nvars	=	nverts[i];

			for (j=0;j<ncsegs;j++,k++) {
				float			*v0		=	baseVertex + (cVertex+(j + 0) % nverts[i])*vertexSize;
				float			*v1		=	baseVertex + (cVertex+(j + 1) % nverts[i])*vertexSize;
				CParameter		*parameters;
				CCurve			*cCurve;
				CCurve::CBase	*base	=	new CCurve::CBase;
				const float		vmin	=	j / (float) ncsegs;
				const float		vmax	=	(j+1) / (float) ncsegs;
				
				parameters			=	pl->uniform(i,NULL);
				parameters			=	pl->varying(t+j,t+(j+1)%nvars,parameters);

				variables->attach();
				base->maxSize		=	maxSize;
				base->variables		=	variables;
				base->sizeVariable	=	sizeVariable;
				base->refCount		=	0;
				base->parameters	=	parameters;
				base->vertex		=	new float[vertexSize*2];
				memcpy(base->vertex + 0*vertexSize,v0,vertexSize*sizeof(float));
				memcpy(base->vertex + 1*vertexSize,v1,vertexSize*sizeof(float));

				cCurve				=	new CLinearCurve(attributes,xform,base,0,1,vmin,vmax);
				cCurve->attach();
				children->push(cCurve);
			}

			cVertex					+=	nverts[i];
			t						+=	nvars;
		}
	}

	memEnd();
}












