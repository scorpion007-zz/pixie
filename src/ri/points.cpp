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
//  File				:	points.cpp
//  Classes				:	CPoints
//  Description			:	Points primitive
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "points.h"
#include "memory.h"
#include "stats.h"
#include "renderer.h"
#include "rendererContext.h"


///////////////////////////////////////////////////////////////////////
// Class				:	CPoints
// Method				:	CPoints
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CPoints::CPoints(CAttributes *a,CXform *x,CPl *pl,int np) : CSurface(a,x) {
	int				i,j;

	atomicIncrement(&stats.numGprims);

	this->numPoints				=	np;
	this->pl					=	pl;
	this->points				=	NULL;

	// Find the maximum size we'll have
	const float	expansion		=	(float) pow((double) fabs(determinantm(xform->from)),1.0 / 3.0);
	float		maxSize			=	0;

	// Compute the maximum point size (for bounding volume computation)
	for (i=0;i<pl->numParameters;i++) {
		const CVariable	*cVar	=	pl->parameters[i].variable;
		
		if (cVar->entry == VARIABLE_WIDTH) {
			const float		*vertex	=	pl->data0 + pl->parameters[i].index;

			for (j=0;j<np;j++) {
				maxSize			=	max(maxSize,vertex[j]);
			}

			if (pl->data1 != NULL) {
				vertex	=	pl->data1 + pl->parameters[i].index;

				for (j=0;j<np;j++) {
					maxSize			=	max(maxSize,vertex[j]);
				}
			}

			break;
		} else if (cVar->entry == VARIABLE_CONSTANTWIDTH) {
			const float		*vertex	=	pl->data0 + pl->parameters[i].index;

			maxSize				=	max(maxSize,vertex[0]);

			if (pl->data1 != NULL) {
				vertex	=	pl->data1 + pl->parameters[i].index;

				maxSize	=	max(maxSize,vertex[0]);
			}

			break;
		}
	}

	// Init the bounding box
	vector		tmp;
	const float	*vertex;
	initv(bmin,C_INFINITY,C_INFINITY,C_INFINITY);
	initv(bmax,-C_INFINITY,-C_INFINITY,-C_INFINITY);
	for (vertex=pl->data0,i=0;i<numPoints;i++,vertex+=3) {
		mulmp(tmp,xform->from,vertex);
		addBox(bmin,bmax,tmp);
	}

	if (pl->data1 != NULL) {
		const float *from = (xform->next != NULL) ? xform->next->from : xform->from;
		for (vertex=pl->data1,i=0;i<numPoints;i++,vertex+=3) {
			mulmp(tmp,from,vertex);
			addBox(bmin,bmax,tmp);
		}
	} else if (xform->next != NULL) {
		const float *from = xform->next->from;
		for (vertex=pl->data0,i=0;i<numPoints;i++,vertex+=3) {
			mulmp(tmp,from,vertex);
			addBox(bmin,bmax,tmp);
		}
	}

	if (maxSize < 0)	maxSize	=	1;
	maxSize	*=	expansion*0.5f;
	subvf(bmin,maxSize);
	addvf(bmax,maxSize);
	makeBound(bmin,bmax);

	// Init the base
	base				=	new CPointBase;
	base->attach();
	base->maxSize		=	maxSize;
	base->variables		=	pl->vertexData();
	base->variables->attach();

	// defferred to prep()
	base->parameters	=	NULL;
	base->vertex		=	NULL;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPoints
// Method				:	CPoints
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CPoints::CPoints(CAttributes *a,CXform *x,CPointBase *b,int np,const float **pi) : CSurface(a,x) {
	int		i;

	atomicIncrement(&stats.numGprims);

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
CPoints::~CPoints() {
	atomicDecrement(&stats.numGprims);

	if (base != NULL)		base->detach();
	if (pl != NULL)			delete pl;

	if (points != NULL) {
		delete [] points;
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPoints
// Method				:	dice
// Description			:	See object.h
// Return Value			:	-
// Comments				:
void	CPoints::dice(CShadingContext *rasterizer)	{
	if (pl != NULL)	prep();

	if (numPoints < CRenderer::maxGridSize) {
		// We're small enough to render directly
		rasterizer->drawPoints(this,numPoints);
	} else {

		// We're too many, split us
		memBegin(rasterizer->threadMemory);

		vector		D;
		int			numFront,numBack;
		int			i,j;
		const float	**front,**back;
		int			*membership;
		vector		P0,P1,nP0,nP1;
		int			num0,num1,moved;
		CPoints		*child;

		front		=	(const float **)	ralloc(numPoints*sizeof(float *),rasterizer->threadMemory);
		back		=	(const float **)	ralloc(numPoints*sizeof(float *),rasterizer->threadMemory);
		membership	=	(int *)				ralloc(numPoints*sizeof(int),rasterizer->threadMemory);

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
			else			movvv(P0,points[rasterizer->irand() % numPoints]);

			if (num1 > 0)	mulvf(P1,nP1,1 / (float) num1);
			else			movvv(P1,points[rasterizer->irand() % numPoints]);
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
		
		rasterizer->drawObject(child);
		
		child->detach();
		
		child	=	new CPoints(attributes,xform,base,numBack,back);
		
		child->attach();
		
		rasterizer->drawObject(child);
		
		child->detach();

		memEnd(rasterizer->threadMemory);
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPoints
// Method				:	dispatch
// Description			:	Push all the defined variables into the arrays
// Return Value			:	-
// Comments				:
void	CPoints::sample(int start,int numVertices,float **varying,float ***locals,unsigned int &usedParameters) const {
	CVertexData		*variables	=	base->variables;
	const int		vertexSize	=	variables->vertexSize;
	float			*vertexData	=	(float *) alloca(numPoints*vertexSize*sizeof(float));
	float			*vertexBase	=	vertexData;

	assert(numVertices == numPoints);
	assert(start == 0);

	if ((variables->moving) && (usedParameters & PARAMETER_END_SAMPLE)) {
		for (int i=0;i<numPoints;++i) {
			const float	*cP		=	points[i] + vertexSize;
			memcpy(vertexData,cP,vertexSize*sizeof(float));
			vertexData			+=	vertexSize;
		}
	} else {
		for (int i=0;i<numPoints;++i) {
			const float	*cP		=	points[i];
			memcpy(vertexData,cP,vertexSize*sizeof(float));
			vertexData			+=	vertexSize;
		}
	}

	// Compute the normal vector
	if (usedParameters & PARAMETER_NG) {
		float	*N	=	varying[VARIABLE_NG];

		for (int i=numPoints;i>0;--i,N+=3)	initv(N,0,0,-1);
	}
	
	// Compute dPdtime
	if (usedParameters & PARAMETER_DPDTIME) {
		float	*dest	=	varying[VARIABLE_DPDTIME];
		
		// Do we have motion?
		if (variables->moving) {
			for (int i=0;i<numPoints;++i) {
				subvv(dest,points[i]+vertexSize,points[i]);
				mulvf(dest,CRenderer::invShutterTime);
			}
		} else {
			// We have no motion, so dPdtime is {0,0,0}
			for (int i=0;i<numPoints;++i)	initv(dest,0,0,0);
		}
	}

	variables->dispatch(vertexBase,0,numPoints,varying,locals);

	usedParameters	&=	~(PARAMETER_NG | PARAMETER_DPDTIME | variables->parameters);
}



///////////////////////////////////////////////////////////////////////
// Class				:	CPoints
// Method				:	interpolate
// Description			:	Interpolate the varying junck and save the uniform stuff
// Return Value			:	-
// Comments				:
void	CPoints::interpolate(int numVertices,float **varying,float ***locals) const {
	if (base->parameters != NULL)	base->parameters->dispatch(numVertices,varying,locals);
}



///////////////////////////////////////////////////////////////////////
// Class				:	CPoints
// Method				:	instantiate
// Description			:	Clone the points
// Return Value			:	-
// Comments				:
void	CPoints::instantiate(CAttributes *a,CXform *x,CRendererContext *c) const {
	CXform	*nx	=	new CXform(x);

	nx->concat(xform);	// Concetenate the local xform

	if (a == NULL)	a	=	attributes;

	assert(pl != NULL);

	c->addObject(new CPoints(a,nx,pl->clone(a),numPoints));
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPoints
// Method				:	prep
// Description			:	Prepare the points
// Return Value			:	-
// Comments				:
void	CPoints::prep() {

	assert(base != NULL);

	osLock(base->mutex);
	if (children != NULL) {
		osUnlock(base->mutex);
		return;
	}

	int					i;
	const CVertexData	*variables;
	variables					=	base->variables;

	const int	vertexSize		=	(variables->moving ? variables->vertexSize*2 : variables->vertexSize);

	pl->transform(xform);

	// Transform the size variable
	const float	expansion		=	(float) pow((double) fabs(determinantm(xform->from)),1.0 / 3.0);
	for (i=0;i<pl->numParameters;i++) {
		const CVariable	*cVar	=	pl->parameters[i].variable;

		if (cVar->entry == VARIABLE_WIDTH) {
			float		*vertex	=	pl->data0 + pl->parameters[i].index;
			
			for (i=0;i<numPoints;i++) {
				vertex[i]		*=	expansion;
			}

			if (pl->data1 != NULL) {
				vertex	=	pl->data1 + pl->parameters[i].index;

				for (i=0;i<numPoints;i++) {
					vertex[i]		*=	expansion;
				}
			}

			break;
		} else if (cVar->entry == VARIABLE_CONSTANTWIDTH) {
			float		*vertex	=	pl->data0 + pl->parameters[i].index;
			
			vertex[0]			*=	expansion;

			if (pl->data1 != NULL) {
				vertex	=	pl->data1 + pl->parameters[i].index;
				
				vertex[0]		*=	expansion;
			}

			break;
		}
	}

	base->vertex				=	new float[vertexSize*numPoints];
	pl->collect(i,base->vertex,CONTAINER_VERTEX,NULL);
	assert(i == vertexSize);	

	assert(points == NULL);

	points						=	new const float*[numPoints];
	const float *vertex			=	base->vertex;

	for (i=0;i<numPoints;i++) {
		points[i]				=	vertex;
		vertex					+=	vertexSize;
	}

	// select out the uniforms
	base->parameters	=	pl->uniform(0,NULL);

	// trash the pl, it's now in the vertex and parameters
	delete pl;
	pl							=	NULL;

	osUnlock(base->mutex);
}

