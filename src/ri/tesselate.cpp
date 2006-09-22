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
//  File				:	tesselate.cpp
//  Classes				:	CShadingContext
//  Description			:	This file implements the tesselation functionality of the shading context
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "common/os.h"
#include "object.h"
#include "output.h"
#include "renderer.h"
#include "shading.h"
#include "stats.h"
#include "memory.h"
#include "pl.h"
#include "polygons.h"

//#define TESSELATION_PRINT

#if !defined(WIN32)
#if defined(__GNUC__) && (__GNUC__ < 4)
// Stupid gcc doesn't allow explicit constructor invocation
static void *operator new(size_t size,void *buf) {
	return  buf;
}
#else
void    *operator new(size_t size,CTriangle *buf) {
    return  buf;
}
void    *operator new(size_t size,CMovingTriangle *buf); // Declared in polygon.cpp
#endif
#endif
			
// The flags that are used to fix the patch cracks
const	int	LOCK_UMIN	=	1;
const	int	LOCK_VMIN	=	2;
const	int	LOCK_UMAX	=	4;
const	int	LOCK_VMAX	=	8;

// The size of the hash we'll use
#define	HASH_SIZE	512
#define	HASH_SHIFT	9


#ifdef TESSELATION_PRINT
static	FILE	*out	=	NULL;
#endif

///////////////////////////////////////////////////////////////////////
// Class				:	CQuad
// Description			:	Holds a vertex in the tesselation
// Comments				:
// Date last edited		:	1/22/2004
class	CQuadVertex {
public:
	float		u,v;					// The parametric coordinates of the point
	vector		P0,P1;					// The position
	vector		N0,N1;					// The normal
	int			clipCode;				// The clipping code
	void		*vertex;				// The final vertex if any
	CQuadVertex	*next;					// Next vertex in the hash
};


///////////////////////////////////////////////////////////////////////
// Class				:	CQuad
// Description			:	Holds a piece of the parametric surface
// Comments				:
// Date last edited		:	1/22/2004
class	CQuad {
public:
	CQuadVertex	*vertices[9];			// Set of vertices in the hash
	CQuad		*children[4];			// Pointers to children quads
	float		umin,umax,vmin,vmax;	// The parametric range of the quad
	int			flags;					// The edge flags
	int			depth;					// The depth of the quad
	CQuad		*next;					// Next quad in the front
};

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	tesselate2D
// Description			:	The main tesselation routine
// Return Value			:	-
// Comments				:
// Date last edited		:	1/24/2003
void	CShadingContext::tesselate2D(CSurface *object) {
	CQuad				*cQuad,*root;
	CQuad				*front		=	NULL;
	CQuadVertex			**vertexHash;
	CQuadVertex			**shadingList;
	CQuadVertex			**shadingListBase;
	int					numRemainingShadingPoints;
	int					i,moving;
	const CAttributes	*attributes	=	object->attributes;

#ifdef TESSELATION_PRINT
	vector	C;
	initv(C,urand(),urand(),urand());
	normalizev(C);
	if (out == NULL)	out	=	fopen("test.txt","w");
	else				out	=	fopen("test.txt","a");
#endif

	// Begin a memory page
	memBegin();

	// Allocate the memory we'll use for tesselation
	vertexHash					=	(CQuadVertex **)	ralloc(HASH_SIZE*sizeof(CQuadVertex *));
	shadingListBase				=	(CQuadVertex **)	ralloc(maxGridSize*sizeof(CQuadVertex *));
	shadingList					=	shadingListBase;
	numRemainingShadingPoints	=	maxGridSize;

	// Init the hash table
	for (i=0;i<HASH_SIZE;i++) {
		vertexHash[i]			=	NULL;
	}

	// Create the top level patch
	cQuad						=	root	=	(CQuad *) ralloc(sizeof(CQuad));
	cQuad->umin					=	0;
	cQuad->vmin					=	0;
	cQuad->umax					=	1;
	cQuad->vmax					=	1;
	cQuad->flags				=	0;
	cQuad->depth				=	0;
	cQuad->next					=	NULL;
	front						=	cQuad;
	
	// Proces the quad
	while(front != NULL) {
		CQuad	*newFront	=	NULL;

		// Compute the vertices required by the quads
		for (cQuad=front;cQuad!=NULL;cQuad=cQuad->next) {
			int			i,j,k;
			float		cu,cv;
			const float	ustep	=	(cQuad->umax - cQuad->umin) * (float) 0.5;
			const float	vstep	=	(cQuad->vmax - cQuad->vmin) * (float) 0.5;

			for (k=0,cv=cQuad->vmin,j=3;j>0;j--,cv+=vstep) {
				for (cu=cQuad->umin,i=3;i>0;i--,cu+=ustep,k++) {
					CQuadVertex	*cVertex;
					T32			ui,vi;
					int			index;
					int			index2;

					ui.real	=	cu;
					vi.real	=	cv;

					index	=	(ui.integer ^ vi.integer);
					index2	=	(index ^ (index >> HASH_SHIFT) ^ (index >> (HASH_SHIFT*2))) & (HASH_SIZE - 1);

					for (cVertex=vertexHash[index2];cVertex!=NULL;cVertex=cVertex->next) {
						if ((cVertex->u == cu) && (cVertex->v == cv))	{
							cQuad->vertices[k]	=	cVertex;
							goto nextPoint;
						}
					}

					cVertex				=	(CQuadVertex *) ralloc(sizeof(CQuadVertex));
					cVertex->u			=	cu;
					cVertex->v			=	cv;
					cVertex->vertex		=	NULL;
					cVertex->next		=	vertexHash[index2];
					vertexHash[index2]	=	cVertex;
					cQuad->vertices[k]	=	cVertex;

					*shadingList++		=	cVertex;
					if (--numRemainingShadingPoints == 0) {
						// We have exhausted the available shading list, flush it

						// Compute the vertices
						displace(object,maxGridSize,shadingListBase);

						// Reset the list
						shadingList					=	shadingListBase;
						numRemainingShadingPoints	=	maxGridSize;
					}
nextPoint:;
				}
			}
		}


		// If there are vertices waiting to be computed in our list, flush them out
		if (numRemainingShadingPoints < maxGridSize) {

			// Compute the vertices
			displace(object,maxGridSize - numRemainingShadingPoints,shadingListBase);

			// Reset the list
			shadingList					=	shadingListBase;
			numRemainingShadingPoints	=	maxGridSize;
		}

		// Refine the quads if necessary
		while((cQuad=front) != NULL) {
			front	=	cQuad->next;

			// Does the quad require refinement
			if (	 (cQuad->depth < attributes->minSubdivision) ||
					((cQuad->depth < attributes->maxSubdivision) && (refine2D(attributes,cQuad)))) {
				// Yes, split the quad into 4 and add the children into the new front
				const float	umid		=	(cQuad->umin + cQuad->umax)*(float) 0.5;
				const float	vmid		=	(cQuad->vmin + cQuad->vmax)*(float) 0.5;
				CQuad		*c0			=	cQuad->children[0]	=	(CQuad *) ralloc(sizeof(CQuad)*4);
				CQuad		*c1			=	cQuad->children[1]	=	c0 + 1;
				CQuad		*c2			=	cQuad->children[2]	=	c1 + 1;
				CQuad		*c3			=	cQuad->children[3]	=	c2 + 1;

				cQuad->children[0]		=	c0;
				cQuad->children[1]		=	c1;
				cQuad->children[2]		=	c2;
				cQuad->children[3]		=	c3;

				c0->umin				=	cQuad->umin;
				c0->vmin				=	cQuad->vmin;
				c0->umax				=	umid;
				c0->vmax				=	vmid;
				c0->flags				=	cQuad->flags & (LOCK_UMIN | LOCK_VMIN);
				c0->depth				=	cQuad->depth+1;
				c0->next				=	newFront;
				newFront				=	c0;

				c1->umin				=	umid;
				c1->vmin				=	cQuad->vmin;
				c1->umax				=	cQuad->umax;
				c1->vmax				=	vmid;
				c1->flags				=	cQuad->flags  & (LOCK_UMAX | LOCK_VMIN);
				c1->depth				=	cQuad->depth+1;
				c1->next				=	newFront;
				newFront				=	c1;

				c2->umin				=	cQuad->umin;
				c2->vmin				=	vmid;
				c2->umax				=	umid;
				c2->vmax				=	cQuad->vmax;
				c2->flags				=	cQuad->flags  & (LOCK_UMIN | LOCK_VMAX);
				c2->depth				=	cQuad->depth+1;
				c2->next				=	newFront;
				newFront				=	c2;

				c3->umin				=	umid;
				c3->vmin				=	vmid;
				c3->umax				=	cQuad->umax;
				c3->vmax				=	cQuad->vmax;
				c3->flags				=	cQuad->flags  & (LOCK_UMAX | LOCK_VMAX);
				c3->depth				=	cQuad->depth+1;
				c3->next				=	newFront;
				newFront				=	c3;
			} else {
				cQuad->children[0]		=	NULL;
			}

		}

		front	=	newFront;
	}

	// Save the object
	object->attach();
	raytraced->push(object);

	if ((flags & OPTIONS_FLAGS_MOTIONBLUR) && (object->moving())) {
		moving	=	TRUE;
	} else {
		moving	=	FALSE;
	}

	// Create the triangles
	front		=	root;
	while((cQuad=front)!=NULL) {
		front	=	cQuad->next;

		// If this is an intermediate node, push it into the stack
		if (cQuad->children[0] != NULL) {
			CQuad	*tQuad;

			// Fix the patch cracks
			if (cQuad->flags & LOCK_VMIN) {
				interpolatev(cQuad->vertices[1]->P0,cQuad->vertices[0]->P0,cQuad->vertices[2]->P0,(float) 0.5);
				interpolatev(cQuad->vertices[1]->P1,cQuad->vertices[0]->P1,cQuad->vertices[2]->P1,(float) 0.5);
			}

			if (cQuad->flags & LOCK_VMAX) {
				interpolatev(cQuad->vertices[7]->P0,cQuad->vertices[6]->P0,cQuad->vertices[8]->P0,(float) 0.5);
				interpolatev(cQuad->vertices[7]->P1,cQuad->vertices[6]->P1,cQuad->vertices[8]->P1,(float) 0.5);
			}

			if (cQuad->flags & LOCK_UMIN) {
				interpolatev(cQuad->vertices[3]->P0,cQuad->vertices[0]->P0,cQuad->vertices[6]->P0,(float) 0.5);
				interpolatev(cQuad->vertices[3]->P1,cQuad->vertices[0]->P1,cQuad->vertices[6]->P1,(float) 0.5);
			}

			if (cQuad->flags & LOCK_UMAX) {
				interpolatev(cQuad->vertices[5]->P0,cQuad->vertices[2]->P0,cQuad->vertices[8]->P0,(float) 0.5);
				interpolatev(cQuad->vertices[5]->P1,cQuad->vertices[2]->P1,cQuad->vertices[8]->P1,(float) 0.5);
			}

			tQuad		=	cQuad->children[0];
			tQuad->next	=	front;
			front		=	tQuad;

			tQuad		=	cQuad->children[1];
			tQuad->next	=	front;
			front		=	tQuad;

			tQuad		=	cQuad->children[2];
			tQuad->next	=	front;
			front		=	tQuad;

			tQuad		=	cQuad->children[3];
			tQuad->next	=	front;
			front		=	tQuad;
		} else {
			void	*v0,*v1,*v2,*v3;

			// Create the triangles for this quad
			if (moving) {
				CMovingTriangle	*t;

#define createVertex(__dest,__src)															\
				if ((__dest = __src->vertex) == NULL) {										\
					CMovingVertex	*t0	=	(CMovingVertex *) frameMemory->alloc(sizeof(CMovingVertex));	\
					CQuadVertex		*s0	=	__src;											\
																							\
					movvv(t0->P[0],s0->P0);													\
					movvv(t0->N[0],s0->N0);													\
					movvv(t0->P[1],s0->P1);													\
					movvv(t0->N[1],s0->N1);													\
					t0->u	=	s0->u;														\
					t0->v	=	s0->v;														\
					__dest	=	t0;															\
					__src->vertex	=	t0;													\
				}

				createVertex(v0,cQuad->vertices[0]);
				createVertex(v1,cQuad->vertices[2]);
				createVertex(v2,cQuad->vertices[6]);
				createVertex(v3,cQuad->vertices[8]);

#undef createVertex

				// Create the first triangle
				t				=	(CMovingTriangle *)	frameMemory->alloc(sizeof(CMovingTriangle)*2);
				t->v[0]			=	(CVertex *) v0;
				t->v[1]			=	(CVertex *) v2;
				t->v[2]			=	(CVertex *) v1;
				t->object		=	object;

#ifdef WIN32
				t->CMovingTriangle::CMovingTriangle();
#else
				t				=	new (t) CMovingTriangle();
#endif
				if ((dotvv(t->N[0],t->N[0]) > 0) && (dotvv(t->N[1],t->N[1]) > 0))
					tracables->push(t);

				t++;

				t->v[0]			=	(CVertex *) v1;
				t->v[1]			=	(CVertex *) v2;
				t->v[2]			=	(CVertex *) v3;
				t->object		=	object;

#ifdef WIN32
				t->CMovingTriangle::CMovingTriangle();
#else
				t				=	new (t) CMovingTriangle();
#endif
				if ((dotvv(t->N[0],t->N[0]) > 0) && (dotvv(t->N[1],t->N[1]) > 0))
					tracables->push(t);

				stats.numRayTriangles	+=	2;
			} else {
				CTriangle	*t;

#define createVertex(__dest,__src)															\
				if ((__dest = __src->vertex) == NULL) {										\
					CVertex		*t0	=	(CVertex *) frameMemory->alloc(sizeof(CVertex));	\
					CQuadVertex	*s0	=	__src;												\
																							\
					movvv(t0->P,s0->P0);													\
					movvv(t0->N,s0->N0);													\
					t0->u	=	s0->u;														\
					t0->v	=	s0->v;														\
					__dest	=	t0;															\
					__src->vertex	=	t0;													\
				}

				createVertex(v0,cQuad->vertices[0]);
				createVertex(v1,cQuad->vertices[2]);
				createVertex(v2,cQuad->vertices[6]);
				createVertex(v3,cQuad->vertices[8]);

#undef	createVertex


				// Create the first triangle
				t				=	(CTriangle *)	frameMemory->alloc(sizeof(CTriangle)*2);
				t->v[0]			=	(CVertex *) v0;
				t->v[1]			=	(CVertex *) v2;
				t->v[2]			=	(CVertex *) v1;
				t->object		=	object;

#ifdef WIN32
				t->CTriangle::CTriangle();
#else
				t				=	new (t) CTriangle();
#endif
				if (dotvv(t->N,t->N) > 0){
					tracables->push(t);
					if (triangles != NULL) triangles->push(t);
				}
				
				t++;

				t->v[0]			=	(CVertex *) v1;
				t->v[1]			=	(CVertex *) v2;
				t->v[2]			=	(CVertex *) v3;
				t->object		=	object;

#ifdef WIN32
				t->CTriangle::CTriangle();
#else
				t				=	new (t) CTriangle();
#endif
				if (dotvv(t->N,t->N) > 0){
					tracables->push(t);
					if (triangles != NULL) triangles->push(t);
				}

				stats.numRayTriangles	+=	2;
			}

#ifdef TESSELATION_PRINT
			fprintf(out,"%f %f %f - %f %f %f\n"
				,cQuad->vertices[4]->P0[0],cQuad->vertices[4]->P0[1],cQuad->vertices[4]->P0[2]
				,C[0],C[1],C[2]);

			fprintf(out,"%f %f %f %f %f %f %f %f %f\n"
				,cQuad->vertices[0]->P0[0],cQuad->vertices[0]->P0[1],cQuad->vertices[0]->P0[2]
				,cQuad->vertices[2]->P0[0],cQuad->vertices[2]->P0[1],cQuad->vertices[2]->P0[2]
				,cQuad->vertices[6]->P0[0],cQuad->vertices[6]->P0[1],cQuad->vertices[6]->P0[2]);

			fprintf(out,"%f %f %f %f %f %f %f %f %f\n"
				,cQuad->vertices[2]->P0[0],cQuad->vertices[2]->P0[1],cQuad->vertices[2]->P0[2]
				,cQuad->vertices[8]->P0[0],cQuad->vertices[8]->P0[1],cQuad->vertices[8]->P0[2]
				,cQuad->vertices[6]->P0[0],cQuad->vertices[6]->P0[1],cQuad->vertices[6]->P0[2]);
#endif
		}

	}

	// End a memory page
	memEnd();

#ifdef TESSELATION_PRINT
	fclose(out);
#endif
}


///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	refine2D
// Description			:	The refinement decision
// Return Value			:	-
// Comments				:
// Date last edited		:	1/24/2003
int			CShadingContext::refine2D(const CAttributes *attributes,CQuad *cQuad) {
	const CQuadVertex	*midVertex	=	cQuad->vertices[4];
	const float			d			=	dotvv(midVertex->P0,midVertex->N0);
	int					i			=	FALSE;
	int					clipCode	=	cQuad->vertices[0]->clipCode;

	//return FALSE;

	// Edge check first
	if (!(cQuad->flags & LOCK_VMIN)) {
		if (refine1D(attributes,cQuad->vertices[0],cQuad->vertices[1],cQuad->vertices[2])) {
			i				=	TRUE;
		} else {
			cQuad->flags	|=	LOCK_VMIN;
		}

	}

	if (!(cQuad->flags & LOCK_VMAX)) {
		if (refine1D(attributes,cQuad->vertices[6],cQuad->vertices[7],cQuad->vertices[8])) {
			i				=	TRUE;
		} else {
			cQuad->flags	|=	LOCK_VMAX;
		}

	}

	if (!(cQuad->flags & LOCK_UMIN)) {
		if (refine1D(attributes,cQuad->vertices[0],cQuad->vertices[3],cQuad->vertices[6])) {
			i				=	TRUE;
		} else {
			cQuad->flags	|=	LOCK_UMIN;
		}

	}

	if (!(cQuad->flags & LOCK_UMAX)) {
		if (refine1D(attributes,cQuad->vertices[2],cQuad->vertices[5],cQuad->vertices[8])) {
			i				=	TRUE;
		} else {
			cQuad->flags	|=	LOCK_UMAX;
		}

	}

	// If any of the edges require refinement, return TRUE
	if (i)	return TRUE;

	// Check if we're visible
	for (i=0;i<9;i++)	clipCode	&=	cQuad->vertices[i]->clipCode;

	// Check the patch as a surface
	for (i=0;i<9;i++) {
		const CQuadVertex	*cVertex	=	cQuad->vertices[i];
		const float			disp		=	absf(dotvv(cVertex->P0,midVertex->N0) - d);

		// Screen space flatness
		if (clipCode == 0) {
			if (disp > (lengthA*midVertex->P0[COMP_Z] + lengthB)*attributes->flatness)	return TRUE;
		}

		// Normal deviation
		if (dotvv(cVertex->N0,midVertex->N0) < attributes->normalDeviation) return TRUE;

		// Flatness
		if (disp > attributes->pointDeviation) return TRUE;
	}

	return FALSE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	refine1D
// Description			:	The refinement decision
// Return Value			:	-
// Comments				:
// Date last edited		:	1/24/2003
int		CShadingContext::refine1D(const CAttributes *attributes,const CQuadVertex *v0,const CQuadVertex *v1,const CQuadVertex *v2) {
	vector	a,b;
	float	adotb,bdotb,adota;
	float	dist;

	subvv(b,v2->P0,v0->P0);
	subvv(a,v1->P0,v0->P0);

	adota	=	dotvv(a,a);
	adotb	=	dotvv(a,b);
	bdotb	=	dotvv(b,b);
	dist	=	adota - (adotb*adotb / bdotb);
	dist	=	max(dist,0);
	dist	=	sqrtf(dist);

	// Only when visible
	if ((v0->clipCode & v1->clipCode & v2->clipCode) == 0) {
		// Screen space flatness
		if (dist > (lengthA*v1->P0[COMP_Z] + lengthB)*attributes->flatness)	return TRUE;
	}

	// Normal deviation
	if (dotvv(v1->N0,v0->N0) < attributes->normalDeviation)	return TRUE;
	if (dotvv(v2->N0,v0->N0) < attributes->normalDeviation)	return TRUE;

	// Flatness
	if (dist > attributes->pointDeviation) return TRUE;

	return FALSE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	refine2D
// Description			:	The refinement decision
// Return Value			:	-
// Comments				:
// Date last edited		:	1/24/2003
void		CShadingContext::displace(CSurface *object,int numPoints,CQuadVertex **vertices) {
	// Sample points on the quad
	float		**varying	=	currentShadingState->varying;
	float		*u			=	varying[VARIABLE_U];
	float		*v			=	varying[VARIABLE_V];
	float		*time		=	varying[VARIABLE_TIME];
	int			i;
	float		*P,*N;

	// Compute the vertices
	for (i=0;i<numPoints;i++) {
		const CQuadVertex *cVertex	=	vertices[i];
		*u++	=	cVertex->u;
		*v++	=	cVertex->v;
		*time++	=	0;
	}
	displace(object,numPoints,1,-1,PARAMETER_P | PARAMETER_N | PARAMETER_TIME | PARAMETER_BEGIN_SAMPLE | PARAMETER_RAYTRACE);

	// Save the evaluated info
	P					=	varying[VARIABLE_P];
	N					=	varying[VARIABLE_N];
	for (i=0;i<numPoints;i++,P+=3,N+=3) {
		CQuadVertex *cVertex	=	vertices[i];

		normalizev(cVertex->N0,N);
		movvv(cVertex->P0,P);
		cVertex->clipCode	=	clipCode(cVertex->P0);
	}

	// Do we have movement ?
	if ( (flags & OPTIONS_FLAGS_MOTIONBLUR) && (object->moving())) {
		u			=	varying[VARIABLE_U];
		v			=	varying[VARIABLE_V];
		time		=	varying[VARIABLE_TIME];
		
		// Compute the vertices
		for (i=0;i<numPoints;i++) {
			const CQuadVertex *cVertex	=	vertices[i];
			*u++	=	cVertex->u;
			*v++	=	cVertex->v;
			*time++	=	1;
		}
		displace(object,numPoints,1,-1,PARAMETER_P | PARAMETER_N | PARAMETER_TIME | PARAMETER_END_SAMPLE | PARAMETER_RAYTRACE);

		// Save the evaluated info
		P					=	varying[VARIABLE_P];
		N					=	varying[VARIABLE_N];
		for (i=0;i<numPoints;i++,P+=3,N+=3) {
			CQuadVertex *cVertex	=	vertices[i];

			normalizev(cVertex->N1,N);
			movvv(cVertex->P1,P);
		}
	}
}


