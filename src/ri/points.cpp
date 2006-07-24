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
//  File				:	points.cpp
//  Classes				:	CPoints
//  Description			:	Points primitive
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "points.h"
#include "hierarchy.h"
#include "memory.h"
#include "stats.h"
#include "renderer.h"



///////////////////////////////////////////////////////////////////////
// Class				:	CPoints
// Method				:	CPoints
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	10/15/2002
CPoints::CPoints(CAttributes *a,CXform *x,CPl *pl,int np) : CSurface(a,x) {
	int				i;
	float			*vertex;
	float			expansion;
	float			maxSize;

	stats.numGprims++;
	stats.gprimMemory			+=	sizeof(CPoints);

	this->numPoints				=	np;
	this->pl					=	pl;
	this->points				=	NULL;

	// Find the maximum size we'll have
	expansion					=	(float) (pow((double) fabs(determinantm(xform->from)),1.0 / 3.0) / 2.0);
	maxSize						=	-C_INFINITY;

	for (vertex=pl->data0,i=0;i<pl->numParameters;i++) {
		const CVariable	*cVar	=	pl->parameters[i].variable;

		if (cVar->entry == VARIABLE_WIDTH) {
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
		} else if (cVar->entry == VARIABLE_CONSTANTWIDTH) {

			vertex[0]			*=	expansion;
			maxSize				=	max(maxSize,vertex[0]);

			if (pl->data1 != NULL) {
				vertex	=	pl->data1 + (vertex - pl->data0);

				vertex[0]		*=	expansion;
				maxSize	=	max(maxSize,vertex[0]);
			}

			break;
		}

		vertex	+=	pl->parameters[i].numItems*cVar->numFloats;
	}

	if (maxSize < 0)	maxSize	=	expansion;

	// Init the bounding box
	initv(bmin,C_INFINITY,C_INFINITY,C_INFINITY);
	initv(bmax,-C_INFINITY,-C_INFINITY,-C_INFINITY);
	for (vertex=pl->data0,i=0;i<numPoints;i++,vertex+=3) {
		addBox(bmin,bmax,vertex);
	}

	if (pl->data1 != NULL) {
		for (vertex=pl->data1,i=0;i<numPoints;i++,vertex+=3) {
			addBox(bmin,bmax,vertex);
		}
	}

	xform->transformBound(bmin,bmax);
	subvf(bmin,maxSize);
	addvf(bmax,maxSize);
	makeBound(bmin,bmax);

	// Init the base
	base				=	new CPointBase;
	base->attach();
	base->maxSize		=	maxSize;
	base->variables		=	pl->vertexData();
	base->variables->attach();
	base->parameters	=	pl->uniform(0,NULL);
	base->vertex		=	NULL;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPoints
// Method				:	CPoints
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	10/15/2002
CPoints::CPoints(CAttributes *a,CXform *x,CPointBase *b,int np,const float **pi) : CSurface(a,x) {
	int		i;

	stats.numGprims++;
	stats.gprimMemory		+=	sizeof(CPoints) + np*sizeof(float *);

	pl						=	NULL;
	base					=	b;
	base->attach();

	numPoints				=	np;
	points					=	new const float*[numPoints];

	initv(bmin,C_INFINITY,C_INFINITY,C_INFINITY);
	initv(bmax,-C_INFINITY,-C_INFINITY,-C_INFINITY);
	for (i=0;i<numPoints;i++) {
		points[i]			=	pi[i];
		addBox(bmin,bmax,points[i]);
	}

	subvf(bmin,base->maxSize);
	addvf(bmax,base->maxSize);
	makeBound(bmin,bmax);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPoints
// Method				:	~CPoints
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	10/15/2002
CPoints::~CPoints() {
	stats.numGprims--;
	stats.gprimMemory		-=	sizeof(CPoints);

	if (base != NULL)		base->detach();
	if (pl != NULL)			delete pl;

	if (points != NULL) {
		delete [] points;
		stats.gprimMemory	-=	numPoints*sizeof(float *);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPoints
// Method				:	bound
// Description			:	See object.h
// Return Value			:	-
// Comments				:
// Date last edited		:	10/15/2002
void	CPoints::bound(float *bmin,float *bmax) const {
	movvv(bmin,this->bmin);
	movvv(bmax,this->bmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPoints
// Method				:	dice
// Description			:	See object.h
// Return Value			:	-
// Comments				:
// Date last edited		:	10/15/2002
void	CPoints::dice(CShadingContext *rasterizer)	{
	if (pl != NULL)	prep();

	if (numPoints < rasterizer->maxGridSize) {
		// We're small enough to render directly
		rasterizer->drawPoints(this,numPoints);
	} else {

		// We're too many, split us
		memBegin();

		vector		D;
		int			numFront,numBack;
		int			i,j;
		const float	**front,**back;
		int			*membership;
		vector		P0,P1,nP0,nP1;
		int			num0,num1,moved;
		CPoints		*child;
		vector		bmin,bmax;

		front		=	(const float **)	ralloc(numPoints*sizeof(float *));
		back		=	(const float **)	ralloc(numPoints*sizeof(float *));
		membership	=	(int *)				ralloc(numPoints*sizeof(int));

		for (i=0;i<numPoints;i++)	membership[i]	=	-1;

		movvv(P0,points[0]);
		movvv(P1,points[1]);

		for (j=0;j<10;j++) {

			initv(nP0,0);
			initv(nP1,0);
			num0	=	num1	=	0;

			moved	=	FALSE;

			for (i=0;i<numPoints;i++) {
				float	d0,d1;

				subvv(D,P0,points[i]);
				d0	=	dotvv(D,D);

				subvv(D,P1,points[i]);
				d1	=	dotvv(D,D);

				if (d0 < d1) {
					if (membership[i] != 0)	{
						moved			=	TRUE;
						membership[i]	=	0;
					}

					addvv(nP0,points[i]);
					num0++;
				} else {
					if (membership[i] != 1)	{
						moved			=	TRUE;
						membership[i]	=	1;
					}

					addvv(nP1,points[i]);
					num1++;
				}
			}

			if (moved == FALSE)	break;

			if (num0 > 0)	mulvf(P0,nP0,1 / (float) num0);
			else			movvv(P0,points[irand() % numPoints]);

			if (num1 > 0)	mulvf(P1,nP1,1 / (float) num1);
			else			movvv(P1,points[irand() % numPoints]);
		}


		// Partition
		numFront	=	numBack	=	0;
		for (i=0;i<numPoints;i++) {
			if (membership[i] == 0)	front[numFront++]	=	points[i];
			else					back[numBack++]		=	points[i];
		}

		// Stupid way of partitionning
		if ((numFront == 0) || (numBack == 0)) {
			numFront	=	numBack	=	0;
			for (i=0;i<numPoints;i++) {
				if (i & 1)	front[numFront++]	=	points[i];
				else		back[numBack++]		=	points[i];
			}
		}


		// Create the children primitives

		child	=	new CPoints(attributes,xform,base,numFront,front);
		child->attach();
		child->bound(bmin,bmax);
		rasterizer->drawObject(child,bmin,bmax);
		child->detach();

		child	=	new CPoints(attributes,xform,base,numBack,back);
		child->attach();
		child->bound(bmin,bmax);
		rasterizer->drawObject(child,bmin,bmax);
		child->detach();


		memEnd();
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPoints
// Method				:	dispatch
// Description			:	Push all the defined variables into the arrays
// Return Value			:	-
// Comments				:
// Date last edited		:	10/15/2002
void	CPoints::sample(int start,int numVertices,float **varying,unsigned int &usedParameters) const {
	memBegin();
	CVertexData		*variables	=	base->variables;
	const int		vertexSize	=	variables->vertexSize;
	float			*vertexData	=	(float *) ralloc(numPoints*vertexSize*sizeof(float));
	int				i;
	float			*vertexBase	=	vertexData;

	assert(numVertices == numPoints);
	assert(start == 0);

	if ((variables->moving) && (usedParameters & PARAMETER_END_SAMPLE)) {
		for (i=0;i<numPoints;i++) {
			const float	*cP			=	points[i] + vertexSize;
			memcpy(vertexData,cP,vertexSize*sizeof(float));
			vertexData			+=	vertexSize;
		}
	} else {
		for (i=0;i<numPoints;i++) {
			const float	*cP			=	points[i];
			memcpy(vertexData,cP,vertexSize*sizeof(float));
			vertexData			+=	vertexSize;
		}
	}

	if (usedParameters & PARAMETER_NG) {
		float	*N	=	varying[VARIABLE_NG];

		for (i=numPoints;i>0;i--,N+=3) {
			initv(N,0,0,-1);
		}
	}

	variables->dispatch(vertexBase,0,numPoints,varying);

	usedParameters	&=	~(PARAMETER_N | variables->parameters);

	memEnd();
}



///////////////////////////////////////////////////////////////////////
// Class				:	CPoints
// Method				:	interpolate
// Description			:	Interpolate the varying junck and save the uniform stuff
// Return Value			:	-
// Comments				:
// Date last edited		:	10/15/2002
void	CPoints::interpolate(int numVertices,float **varying) const {
	if (base->parameters != NULL)	base->parameters->dispatch(numVertices,varying);
}



///////////////////////////////////////////////////////////////////////
// Class				:	CPoints
// Method				:	copy
// Description			:	Clone the points
// Return Value			:	-
// Comments				:
// Date last edited		:	6/11/2003
void	CPoints::copy(CAttributes *a,CXform *x,CRendererContext *c) const {
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPoints
// Method				:	prep
// Description			:	Prepare the points
// Return Value			:	-
// Comments				:
// Date last edited		:	6/11/2003
void	CPoints::prep() {
	const float			*vertex;
	int					i;
	const CVertexData	*variables;

	assert(base != NULL);
	variables					=	base->variables;

	const int	vertexSize		=	(variables->moving ? variables->vertexSize*2 : variables->vertexSize);

	pl->transform(xform);

	base->vertex				=	new float[vertexSize*numPoints];
	pl->collect(i,base->vertex,CONTAINER_VERTEX);
	assert(i == vertexSize);

	delete pl;
	pl							=	NULL;

	assert(points == NULL);

	points						=	new const float*[numPoints];
	vertex						=	base->vertex;

	stats.gprimMemory			+=	numPoints*sizeof(float *);

	for (i=0;i<numPoints;i++) {
		points[i]				=	vertex;
		vertex					+=	vertexSize;
	}
}
