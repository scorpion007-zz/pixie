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
//  File				:	polygon.cpp
//  Classes				:	CPolygonMesh
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "polygons.h"
#include "renderer.h"
#include "object.h"
#include "stats.h"
#include "memory.h"
#include "shading.h"
#include "error.h"
#include "surface.h"


#if !defined(WIN32)
#if defined(__GNUC__) && (__GNUC__ < 4)
// Stupid gcc doesn't allow explicit constructor invocation
static void	*operator new(size_t size,void *buf) {
	return	buf;
}
#else
void	*operator new(size_t size,CPtriangle *buf) {
	return	buf;
}
void	*operator new(size_t size,CMovingTriangle *buf) {
	return	buf;
}
#endif
#endif


///////////////////////////////////////////////////////////////////////
// Class				:	CTriVertex
// Description			:	This is a temporary vertex used during the triangulation
// Comments				:
// Date last edited		:	1/20/2002
class	CTriVertex {
public:
	const	float		*xy;
	CTriVertex			*next,*prev;
};



static	CAttributes			*meshAttributes;		// Mesh attributes
static	CXform				*meshXform;				// Mesh xform
static	CPl					*meshPl;				// Parameter list
static	CArray<CObject *>	*meshChildren;			// List of children
static	const float			*meshP;					// The vertex positions
static	CPlParameter		*meshNormal;			// The normal parameter
static	const float			*meshNormalData0;		// The normal data
static	const float			*meshNormalData1;
static	int					meshTriangleType;		// The triangle type
static	int					meshUniformNumber;		// The current uniform number
static	int					meshFacevaryingNumber;	// The current facevarying number
static	CPolygonMesh		*mesh;					// The mesh we're allocating the triangle for
static	CShadingContext		*meshContext;			// The shading context






///////////////////////////////////////////////////////////////////////
// Class				:	CPolygonTriangle
// Method				:	CPolygonTriangle
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	3/7/2002
CPolygonTriangle::CPolygonTriangle(CAttributes *a,CXform *x,CPolygonMesh *mesh) : CSurface(a,x) {
	stats.numGprims++;

	// Save the parameters
	this->mesh			=	mesh;
	mesh->attach();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPolygonTriangle
// Method				:	~CPolygonTriangle
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	3/7/2002
CPolygonTriangle::~CPolygonTriangle() {
	stats.numGprims--;
	mesh->detach();
}




///////////////////////////////////////////////////////////////////////
// Class				:	CPolygonTriangle
// Method				:	tesselate
// Description			:	See object.h
// Return Value			:	-
// Comments				:
// Date last edited		:	3/17/2001
void			CPolygonTriangle::tesselate(CShadingContext *context) {
	assert(FALSE);	// Should never be called
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPolygonTriangle
// Method				:	bound
// Description			:	Compute the bounding box of the polygon
// Return Value			:	-
// Comments				:
// Date last edited		:	3/7/2002
void			CPolygonTriangle::bound(float *bmin,float *bmax) const {
	const CPl	*pl			=	mesh->pl;
	const float	*vertices	=	pl->data0;
	const float	*v0			=	vertices + this->v0*3;
	const float	*v1			=	vertices + this->v1*3;
	const float	*v2			=	vertices + this->v2*3;

	// Bound the primitive in the camera space
	movvv(bmin,v0);
	movvv(bmax,v0);

	addBox(bmin,bmax,v1);
	addBox(bmin,bmax,v2);

	if ((vertices=pl->data1) != NULL) {
		vertices	=	pl->data1;
		v0			=	vertices + this->v0*3;
		v1			=	vertices + this->v1*3;
		v2			=	vertices + this->v2*3;

		addBox(bmin,bmax,v0);
		addBox(bmin,bmax,v1);
		addBox(bmin,bmax,v2);
	}

	makeBound(bmin,bmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPolygonTriangle
// Method				:	sample
// Description			:	Sample bunch of points on the triangle
// Return Value			:	-
// Comments				:
// Date last edited		:	3/7/2002
void		CPolygonTriangle::sample(int start,int numVertices,float **varying,unsigned int &up) const {
	int			i,j,k;
	const float	*u				=	varying[VARIABLE_U] + start;
	const float	*v				=	varying[VARIABLE_V] + start;
	const CPl	*pl				=	mesh->pl;

	memBegin();


	if ((pl->data1 != NULL) && (!(up & (PARAMETER_BEGIN_SAMPLE | PARAMETER_END_SAMPLE)))) {
		const float		*v00;
		const float		*v01;
		const float		*v02;
		const float		*v10;
		const float		*v11;
		const float		*v12;
		const float		*data0	=	pl->data0;
		const float		*data1	=	pl->data1;
		const float		*time	=	varying[VARIABLE_TIME] + start*3;

		// Interpolate the vertex variables accross the triangle
		for (j=0;j<pl->numParameters;j++) {
			const CVariable	*variable	=	pl->parameters[j].variable;
			const int		numFloats	=	variable->numFloats;

			if (pl->parameters[j].container == CONTAINER_VERTEX) {
				float		*dest	=	pl->parameters[j].resolve(varying) + start*numFloats;

				if (dest != NULL) {
					const float	*sv00	=	data0 + this->v0*variable->numFloats;
					const float	*sv01	=	data0 + this->v1*variable->numFloats;
					const float	*sv02	=	data0 + this->v2*variable->numFloats;
					const float	*sv10	=	data1 + this->v0*variable->numFloats;
					const float	*sv11	=	data1 + this->v1*variable->numFloats;
					const float	*sv12	=	data1 + this->v2*variable->numFloats;

					for (i=0;i<numVertices;i++) {
						const	float	cu		=	u[i];
						const	float	cv		=	v[i];
						const	float	ctime	=	time[i];

						for (k=0;k<numFloats;k++) {
							*dest++	=	(sv00[k]*(1-cu) + sv01[k]*cu*cv + sv02[k]*cu*(1-cv))*(1-ctime) + 
										(sv10[k]*(1-cu) + sv11[k]*cu*cv + sv12[k]*cu*(1-cv))*ctime;
						}
					}
				}
			}

			data0	+=	numFloats*pl->parameters[j].numItems;
			data1	+=	numFloats*pl->parameters[j].numItems;
		}

		v00	=	data0 + this->v0*3;
		v01	=	data0 + this->v1*3;
		v02	=	data0 + this->v2*3;
		v10	=	data1 + this->v0*3;
		v11	=	data1 + this->v1*3;
		v12	=	data1 + this->v2*3;

		// Compute surface derivatives and normal if required
		if (up & PARAMETER_DPDU) {
			float	*dest	=	&varying[VARIABLE_DPDU][start*3];

			for (i=0;i<numVertices;i++) {
				const float	cv		=	v[i];
				const float	ctime	=	time[i];

				dest[0]			=	(v01[0]*cv + v02[0]*(1-cv) - v00[0])*(1-ctime) + (v01[0]*cv + v02[0]*(1-cv) - v00[0])*ctime;
				dest[1]			=	(v01[1]*cv + v02[1]*(1-cv) - v00[1])*(1-ctime) + (v01[1]*cv + v02[1]*(1-cv) - v00[1])*ctime;
				dest[2]			=	(v01[2]*cv + v02[2]*(1-cv) - v00[2])*(1-ctime) + (v01[2]*cv + v02[2]*(1-cv) - v00[2])*ctime;
				dest			+=	3;
			}
		}

		if (up & PARAMETER_DPDV) {
			float	*dest	=	&varying[VARIABLE_DPDV][start*3];

			for (i=0;i<numVertices;i++) {
				const float	cu		=	u[i];
				const float	ctime	=	time[i];

				dest[0]			=	(v01[0] - v02[0])*cu*(1-ctime) + (v11[0] - v12[0])*cu*ctime;
				dest[1]			=	(v01[1] - v02[1])*cu*(1-ctime) + (v11[1] - v12[1])*cu*ctime;
				dest[2]			=	(v01[2] - v02[2])*cu*(1-ctime) + (v11[2] - v12[2])*cu*ctime;
				dest			+=	3;
			}
		}

		if (up & PARAMETER_NG) {
			float	*dest	=	&varying[VARIABLE_NG][start*3];
			vector	normal0,normal1;
			vector	D0,D1;

			subvv(D0,v01,v00);
			subvv(D1,v02,v00);
			crossvv(normal0,D1,D0);

			subvv(D0,v11,v10);
			subvv(D1,v12,v10);
			crossvv(normal1,D1,D0);

			for (i=0;i<numVertices;i++) {
				interpolatev(dest,normal0,normal1,time[i]);

				dest			+=	3;
			}
		}
	} else {
		const float		*v0;
		const float		*v1;
		const float		*v2;
		const float		*data;

		if (up & PARAMETER_END_SAMPLE) {
			data		=	pl->data1;
		} else {
			data		=	pl->data0;
		}

		v0	=	data + this->v0*3;
		v1	=	data + this->v1*3;
		v2	=	data + this->v2*3;

		// Interpolate the vertex variables accross the triangle
		for (j=0;j<pl->numParameters;j++) {
			const CVariable	*variable	=	pl->parameters[j].variable;
			const int		numFloats	=	variable->numFloats;

			if (pl->parameters[j].container == CONTAINER_VERTEX) {
				float		*dest	=	pl->parameters[j].resolve(varying) + start*numFloats;

				if (dest != NULL) {
					const float	*sv0	=	data + this->v0*variable->numFloats;
					const float	*sv1	=	data + this->v1*variable->numFloats;
					const float	*sv2	=	data + this->v2*variable->numFloats;

					for (i=0;i<numVertices;i++) {
						const	float	cu	=	u[i];
						const	float	cv	=	v[i];

						for (k=0;k<numFloats;k++) {
							*dest++	=	sv0[k]*(1-cu) + sv1[k]*cu*cv + sv2[k]*cu*(1-cv);
						}
					}
				}
			}

			data	+=	numFloats*pl->parameters[j].numItems;
		}

		// Compute surface derivatives and normal if required
		if (up & PARAMETER_DPDU) {
			float	*dest	=	&varying[VARIABLE_DPDU][start*3];

			for (i=0;i<numVertices;i++) {
				const float	cv	=	v[i];

				dest[0]			=	v1[0]*cv + v2[0]*(1-cv) - v0[0];
				dest[1]			=	v1[1]*cv + v2[1]*(1-cv) - v0[1];
				dest[2]			=	v1[2]*cv + v2[2]*(1-cv) - v0[2];
				dest			+=	3;
			}
		}

		if (up & PARAMETER_DPDV) {
			float	*dest	=	&varying[VARIABLE_DPDV][start*3];

			for (i=0;i<numVertices;i++) {
				const float	cu	=	u[i];

				dest[0]			=	(v1[0] - v2[0])*cu;
				dest[1]			=	(v1[1] - v2[1])*cu;
				dest[2]			=	(v1[2] - v2[2])*cu;
				dest			+=	3;
			}
		}

		if (up & PARAMETER_NG) {
			float	*dest	=	&varying[VARIABLE_NG][start*3];
			vector	normal;
			vector	D0,D1;

			subvv(D0,v1,v0);
			subvv(D1,v2,v0);
			crossvv(normal,D1,D0);

			for (i=0;i<numVertices;i++) {
				movvv(dest,normal);

				dest			+=	3;
			}
		}
	}

	up	&=	~(PARAMETER_P | PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_NG | mesh->parameters);

	memEnd();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPolygonTriangle
// Method				:	interpolate
// Description			:	Core interpolation
// Return Value			:	-
// Comments				:
// Date last edited		:	3/7/2002
void			CPolygonTriangle::interpolate(int numVertices,float **varying) const {
	int			i,j,k;
	const float	*u				=	varying[VARIABLE_U];
	const float	*v				=	varying[VARIABLE_V];
	const CPl	*pl				=	mesh->pl;
	const float	*data			=	pl->data0;

	for (i=0;i<pl->numParameters;i++) {
		const CPlParameter	*cParameter	=	pl->parameters+i;
		const CVariable		*cVariable	=	cParameter->variable;
		const int			numFloats	=	cVariable->numFloats;
		float				*dest		=	cParameter->resolve(varying);
		const float			*src;
		const float			*v0,*v1,*v2;

		if (dest != NULL) {
			switch(cParameter->container) {
			case CONTAINER_UNIFORM:
				if ((cVariable->container == CONTAINER_UNIFORM) || (cVariable->container == CONTAINER_CONSTANT)) {
					src	=	data + this->uniform*numFloats;
					for (j=numFloats;j>0;j--) {
						*dest++	=	*src++;
					}
				} else {
					// premote
					for(j=0;j<numVertices;j++) {
						src	=	data + this->uniform*numFloats;
						for (k=numFloats;k>0;k--) {
							*dest++	=	*src++;
						}
					}
				}
				break;
			case CONTAINER_VERTEX:
				// Ignore
				break;
			case CONTAINER_VARYING:
				v0	=	data + this->v0*numFloats;
				v1	=	data + this->v1*numFloats;
				v2	=	data + this->v2*numFloats;
				for (j=0;j<numVertices;j++) {
					const	float	cu	=	u[j];
					const	float	cv	=	v[j];

					for (k=0;k<numFloats;k++) {
						*dest++	=	v0[k]*(1-cu) + v1[k]*cu*cv + v2[k]*cu*(1-cv);
					}
				}

				break;
			case CONTAINER_FACEVARYING:
				v0	=	data + this->fv0*numFloats;
				v1	=	data + this->fv1*numFloats;
				v2	=	data + this->fv2*numFloats;
				for (j=0;j<numVertices;j++) {
					const	float	cu	=	u[j];
					const	float	cv	=	v[j];

					for (k=0;k<numFloats;k++) {
						*dest++	=	v0[k]*(1-cu) + v1[k]*cu*cv + v2[k]*cu*(1-cv);
					}
				}
				break;
			case CONTAINER_CONSTANT:
				if ((cVariable->container == CONTAINER_UNIFORM) || (cVariable->container == CONTAINER_CONSTANT)) {
					src	=	data;
					for (j=numFloats;j>0;j--) {
						*dest++	=	*src++;
					}
				} else {
					// premote
					for(j=0;j<numVertices;j++) {
						src	=	data;
						for (k=numFloats;k>0;k--) {
							*dest++	=	*src++;
						}
					}
				}
				break;
			}
		}

		data	+=	cParameter->numItems*numFloats;
	}
}

































///////////////////////////////////////////////////////////////////////
// Class				:	CPolygonMesh
// Method				:	CPolygonMesh
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	6/11/2003
CPolygonMesh::CPolygonMesh(CAttributes *a,CXform *x,CPl *pl,int npoly,int *nholes,int *nvertices,int *vertices) : CObject(a,x) {
	int		i,mVertex;
	float	*P;

	stats.numGprims++;
	stats.gprimMemory	+=	sizeof(CPolygonMesh);

	this->pl			=	pl;
	this->npoly			=	npoly;

	for (i=0,nloops=0;i<npoly;i++) {
		nloops	+=	nholes[i];
	}

	for (i=0,nverts=0;i<nloops;i++) {
		nverts	+=	nvertices[i];
	}

	this->nholes		=	new int[npoly];		memcpy(this->nholes,nholes,npoly*sizeof(int));
	this->nvertices		=	new int[nloops];	memcpy(this->nvertices,nvertices,nloops*sizeof(int));
	this->vertices		=	new int[nverts];	memcpy(this->vertices,vertices,nverts*sizeof(int));	

	stats.gprimMemory	+=	(npoly + nloops + nverts)*sizeof(int);

	for (i=0,mVertex=-1;i<nverts;i++) {
		mVertex	=	max(mVertex,vertices[i]);
	}
	mVertex++;

	// Compute the object space bounding box
	initv(bmin,C_INFINITY,C_INFINITY,C_INFINITY);
	initv(bmax,-C_INFINITY,-C_INFINITY,-C_INFINITY);
	P					=	pl->data0;
	for (i=mVertex;i>0;i--,P+=3) {
		addBox(bmin,bmax,P);
	}

	if (pl->data1 != NULL) {
		P					=	pl->data1;
		for (i=mVertex;i>0;i--,P+=3) {
			addBox(bmin,bmax,P);
		}
	}

	children			=	NULL;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPolygonMesh
// Method				:	~CPolygonMesh
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	6/11/2003
CPolygonMesh::~CPolygonMesh() {
	stats.numGprims--;
	stats.gprimMemory	-=	sizeof(CPolygonMesh);
	stats.gprimMemory	-=	(npoly + nloops + nverts)*sizeof(int);

	delete pl;
	delete [] nholes;
	delete [] nvertices;
	delete [] vertices;

	if (children != NULL)	delete children;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPolygonMesh
// Method				:	bound
// Description			:	Compute the bounding box
// Return Value			:	-
// Comments				:
// Date last edited		:	6/11/2003
void		CPolygonMesh::bound(float *bmi,float *bma) const {
	movvv(bmi,bmin);
	movvv(bma,bmax);
	xform->transformBound(bmi,bma);
	makeBound(bmi,bma);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPolygonMesh
// Method				:	copy
// Description			:	Instanciate the mesh
// Return Value			:	-
// Comments				:
// Date last edited		:	6/11/2003
void		CPolygonMesh::copy(CAttributes *a,CXform *x,CRendererContext *c) const {
	CXform	*nx		=	new CXform(x);

	nx->concat(xform);	// Concetenate the local xform

	if (a == NULL)	a	=	attributes;

	c->addObject(new CPolygonMesh(a,nx,pl->clone(a),npoly,nholes,nvertices,vertices));
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPolygonMesh
// Method				:	tesselate
// Description			:	Tesselate the mesh
// Return Value			:	-
// Comments				:
// Date last edited		:	6/11/2003
void		CPolygonMesh::tesselate(CShadingContext *c) {
	if (children == NULL) {
		triangulate(c);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPolygonMesh
// Method				:	dice
// Description			:	Split the mesh
// Return Value			:	-
// Comments				:
// Date last edited		:	6/11/2003
void		CPolygonMesh::dice(CShadingContext *r) {
	int		i;
	CObject	**objects;

	if (children == NULL) {
		triangulate(NULL);
	}

	objects	=	children->array;

	for (i=children->numItems;i>0;i--,objects++) {
		(*objects)->dice(r);
	}
}



























///////////////////////////////////////////////////////////////////////
// Function				:	createTriangle
// Description			:	Actually create the triangle
// Return Value			:	-
// Comments				:
// Date last edited		:	10/29/2003
inline	void	createTriangle(const int *vindices,const int vi0,const int vi1,const int vi2) {
	CPolygonTriangle	*cTriangle;
	const float			*P				=	meshP;
	const float			*vs0			=	P+vindices[vi0]*3;
	const float			*vs1			=	P+vindices[vi1]*3;
	const float			*vs2			=	P+vindices[vi2]*3;
	vector				D,D0,D1;

	// Skip if this is a degenerate triangle
	subvv(D0,vs1,vs0);
	subvv(D1,vs2,vs0);
	crossvv(D,D0,D1);
	if (dotvv(D,D) == 0) {
		return;
	}

	// Create the triangle
	cTriangle				=	new CPolygonTriangle(meshAttributes,meshXform,mesh);

	// Set the variables
	cTriangle->v0			=	vindices[vi0];
	cTriangle->v1			=	vindices[vi1];
	cTriangle->v2			=	vindices[vi2];
	cTriangle->fv0			=	meshFacevaryingNumber+vi0;
	cTriangle->fv1			=	meshFacevaryingNumber+vi1;
	cTriangle->fv2			=	meshFacevaryingNumber+vi2;
	cTriangle->uniform		=	meshUniformNumber;

	// Add the children into the pool
	meshChildren->push(cTriangle);

	// Do we need to create a tracable object for this triangle ?
	if (meshContext != NULL) {

		// Do we have displacements ?
		if ((meshAttributes->flags & ATTRIBUTES_FLAGS_DISPLACEMENTS) && (meshAttributes->displacement != NULL)) {
			// Yes, tesselate the triangle
			meshContext->tesselate2D(cTriangle);
		} else {
			// No, create raytracing triangles
			CMemStack	*memory	=	meshContext->frameMemory;

			if (meshPl->data1 == NULL) {
				CVertex		*v0	=	(CVertex *)		memory->alloc(3*sizeof(CVertex) + sizeof(CPtriangle));
				CVertex		*v1	=	v0+1;
				CVertex		*v2	=	v1+1;
				CPtriangle	*t	=	(CPtriangle *)	(v2 + 1);

				movvv(v0->P,vs0);	v0->u = 0;	v0->v = 1;
				movvv(v1->P,vs1);	v1->u = 1;	v1->v = 1;
				movvv(v2->P,vs2);	v2->u = 1;	v2->v = 0;

				t->v[0]		=	v0;
				t->v[1]		=	v1;
				t->v[2]		=	v2;
				t->object	=	cTriangle;

#ifdef WIN32
				t->CPtriangle::CPtriangle();
#else
				t	=	new (t) CPtriangle;
#endif


				// Create the vertices
				switch(meshTriangleType) {
				case 0:
					// Flat triangle
					movvv(v0->N,t->N);
					movvv(v1->N,t->N);
					movvv(v2->N,t->N);
					break;
				case 1:
					// Smooth triangle
					movvv(v0->N,meshNormalData0+vindices[vi0]*3);
					movvv(v1->N,meshNormalData0+vindices[vi1]*3);
					movvv(v2->N,meshNormalData0+vindices[vi2]*3);
					break;
				case 2:
					// Smooth facevarying triangle
					movvv(v0->N,meshNormalData0+(meshFacevaryingNumber+vi0)*3);
					movvv(v1->N,meshNormalData0+(meshFacevaryingNumber+vi1)*3);
					movvv(v2->N,meshNormalData0+(meshFacevaryingNumber+vi2)*3);
					break;
				}


				// Insert the triangle into the list
				meshContext->addTracable(t,cTriangle);
				stats.numRayTriangles++;
			} else {
				CMovingVertex		*v0		=	(CMovingVertex *)		memory->alloc(3*sizeof(CMovingVertex) + sizeof(CPmovingTriangle));
				CMovingVertex		*v1		=	v0+1;
				CMovingVertex		*v2		=	v1+1;
				CPmovingTriangle	*t		=	(CPmovingTriangle *)	(v2 + 1);
				const float			*P1		=	meshPl->data1;
				const float			*ve0	=	P1+vindices[vi0]*3;
				const float			*ve1	=	P1+vindices[vi1]*3;
				const float			*ve2	=	P1+vindices[vi2]*3;


				movvv(v0->P[0],vs0);	movvv(v0->P[1],ve0);	v0->u = 0;	v0->v = 1;
				movvv(v1->P[0],vs1);	movvv(v1->P[1],ve1);	v1->u = 1;	v1->v = 1;
				movvv(v2->P[0],vs2);	movvv(v2->P[1],ve2);	v2->u = 1;	v2->v = 0;

				t->v[0]		=	v0;
				t->v[1]		=	v1;
				t->v[2]		=	v2;
				t->object	=	cTriangle;

#ifdef WIN32
				t->CPmovingTriangle::CPmovingTriangle();
#else
				t	=	new (t) CPmovingTriangle;
#endif


				// Create the vertices
				switch(meshTriangleType) {
				case 0:
					// Flat triangle
					movvv(v0->N[0],t->N[0]);
					movvv(v1->N[0],t->N[0]);
					movvv(v2->N[0],t->N[0]);
					movvv(v0->N[1],t->N[1]);
					movvv(v1->N[1],t->N[1]);
					movvv(v2->N[1],t->N[1]);
					break;
				case 1:
					// Smooth triangle
					movvv(v0->N[0],meshNormalData0+vindices[vi0]*3);
					movvv(v1->N[0],meshNormalData0+vindices[vi1]*3);
					movvv(v2->N[0],meshNormalData0+vindices[vi2]*3);
					movvv(v0->N[1],meshNormalData1+vindices[vi0]*3);
					movvv(v1->N[1],meshNormalData1+vindices[vi1]*3);
					movvv(v2->N[1],meshNormalData1+vindices[vi2]*3);
					break;
				case 2:
					// Smooth facevarying triangle
					movvv(v0->N[0],meshNormalData0+(meshFacevaryingNumber+vi0)*3);
					movvv(v1->N[0],meshNormalData0+(meshFacevaryingNumber+vi1)*3);
					movvv(v2->N[0],meshNormalData0+(meshFacevaryingNumber+vi2)*3);
					movvv(v0->N[1],meshNormalData1+(meshFacevaryingNumber+vi0)*3);
					movvv(v1->N[1],meshNormalData1+(meshFacevaryingNumber+vi1)*3);
					movvv(v2->N[1],meshNormalData1+(meshFacevaryingNumber+vi2)*3);
					break;
				}

				// Insert the triangle into the list
				meshContext->addTracable(t,cTriangle);
				stats.numRayTriangles++;
			}
		}
	}
}





///////////////////////////////////////////////////////////////////////
// Function				:	valid
// Description			:	Check if the edge between from and to is inside the polygon
// Return Value			:	TRUE if this is a valid edge
// Comments				:
// Date last edited		:	10/29/2003
static	inline	int		valid(const CTriVertex *loop,const CTriVertex *from,const CTriVertex *to) {
	const CTriVertex	*sVertex	=	loop;
	const float			*a			=	loop->xy;
	const float			*b			=	from->xy;
	const float			*c			=	to->xy;

	sVertex = sVertex->next;

	do{
		if(sVertex == to) 	{ sVertex = sVertex->next; continue; }
		if(sVertex == from) { sVertex = sVertex->next; continue; }

		const float	*s1	=	sVertex->xy;
				
		if(	(area(c[0],c[1],s1[0],s1[1],b[0],b[1])*area(c[0],c[1],a[0],a[1],b[0],b[1]) > 0) &&
			(area(c[0],c[1],s1[0],s1[1],a[0],a[1])*area(c[0],c[1],b[0],b[1],a[0],a[1]) > 0) &&
			(area(b[0],b[1],s1[0],s1[1],a[0],a[1])*area(b[0],b[1],c[0],c[1],a[0],a[1]) > 0)) return FALSE;
		
		sVertex = sVertex->next;
	}while(sVertex != loop);
	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// Function				:	orientationCheck
// Description			:	Check the orientation of a loop to make sure it is CW or CCW
// Return Value			:	-
// Comments				:
// Date last edited		:	5/26/2004
static	inline	int			orientationCheck(CTriVertex *loop,int cw) {
	CTriVertex	*minVertex;
	CTriVertex	*cVertex,*pVertex,*nVertex;
	int			reverse;
	int			numVertices;

	// Correct the orientation of the polygon if necessary
	minVertex	=	loop;
	numVertices	=	1;
	for (cVertex=minVertex->next;cVertex!=loop;cVertex=cVertex->next,numVertices++) {
		// Find the topmost vertex
		if (cVertex->xy[1] > minVertex->xy[1])	minVertex	=	cVertex;
	}

	pVertex		=	minVertex->prev;
	nVertex		=	minVertex->next;
	reverse		=	FALSE;

	if (cw == TRUE) {
		if (area(pVertex->xy[0],pVertex->xy[1],minVertex->xy[0],minVertex->xy[1],nVertex->xy[0],nVertex->xy[1]) < 0) {
			reverse	=	TRUE;
		}
	} else {
		if (area(pVertex->xy[0],pVertex->xy[1],minVertex->xy[0],minVertex->xy[1],nVertex->xy[0],nVertex->xy[1]) > 0) {
			reverse	=	TRUE;
		}
	}

	// Do we need to reverse the loop
	if (reverse == TRUE) {
		CTriVertex	**vertices	=	(CTriVertex **) alloca(numVertices*sizeof(CTriVertex *));
		int			i;

		vertices[0]	=	loop;
		cVertex		=	loop->next;
		i			=	1;
		for (;cVertex!=loop;cVertex=cVertex->next,i++) {
			vertices[i]			=	cVertex;
		}

		assert(i == numVertices);

		for (i=0;i<numVertices;i++) {
			cVertex	=	vertices[i];
			cVertex->prev	=	vertices[(i+1) % numVertices];
			cVertex->next	=	vertices[(i-1+numVertices) % numVertices];
		}
	}

	return reverse;
}




///////////////////////////////////////////////////////////////////////
// Function				:	triangulate
// Description			:	Triangulate a general polygon
// Return Value			:	-
// Comments				:
// Date last edited		:	10/29/2003
inline	void	triangulatePolygon(int nloops,int *nverts,int *vindices) {
	int			i,j,k;
	int			numVertices;
	CTriVertex	**loops;
	CTriVertex	*vertices;
	CTriVertex	*cVertex,*pVertex,*nVertex;
	float		*xy;
	int			majorAxis,minorAxis;
	vector		normal;
	const float	*P;
	int			reverse;

//#define OLDSTYLE
#ifdef OLDSTYLE
	// Are we just creating a triangle ?
	if ((nloops == 1) && (nverts[0] == 3)) {

		// Create the triangle
		createTriangle(vindices,0,1,2);

		meshUniformNumber++;
		meshFacevaryingNumber	+=	3;

		return;
	}
#endif

	// Count the number of vertices
	for (numVertices=0,i=0;i<nloops;numVertices+=nverts[i],i++);

	// Compute the polygon normal
	for (P=meshP,i=0;i<nverts[0];i++) {
		const int	vi0		=	vindices[i];
		const int	vi1		=	vindices[(i+1) % nverts[0]];
		const int	vi2		=	vindices[(i+2) % nverts[0]];
		const float	*v0		=	P + vi0*3;
		const float	*v1		=	P + vi1*3;
		const float	*v2		=	P + vi2*3;
		vector		D0,D1;

		subvv(D0,v1,v0);
		subvv(D1,v2,v0);

		crossvv(normal,D0,D1);

		// Do we have a good normal ?
		if (dotvv(normal,normal) > 0) {

			// Normalize the normal vector
			normalizev(normal);

			// Find the minor and major axices of the normal ?
			if (fabs(normal[COMP_X]) >= max(fabs(normal[COMP_Y]),fabs(normal[COMP_Z]))) {
				majorAxis	=	COMP_Y;
				minorAxis	=	COMP_Z;
			} else if (fabs(normal[COMP_Y]) >= max(fabs(normal[COMP_X]),fabs(normal[COMP_Z]))) {
				majorAxis	=	COMP_X;
				minorAxis	=	COMP_Z;
			} else {
				majorAxis	=	COMP_X;
				minorAxis	=	COMP_Y;
			}

		

			break;
		}
	}

	// Check if we have a degenerate polygon
	if (i == nverts[0]) {
		meshUniformNumber++;
		meshFacevaryingNumber	+=	numVertices;

		return;
	}

	// Allocate the intial memory
	xy			=	(float *)			alloca(numVertices*2*sizeof(float));
	loops		=	(CTriVertex **)		alloca(nloops*sizeof(CTriVertex *));
	vertices	=	(CTriVertex *)		alloca(numVertices*sizeof(CTriVertex));

	// Collect the vertex data
	for (i=0;i<numVertices;i++) {
		const float	*cP	=	P + vindices[i]*3;
		xy[i*2+0]		=	cP[majorAxis];
		xy[i*2+1]		=	cP[minorAxis];
	}

	// Create / link the vertices
	for (k=0,i=0;i<nloops;i++) {
		int	nv		=	nverts[i];

		loops[i]	=	vertices + k;
		for (j=0;j<nv;j++) {
			cVertex				=	vertices + k + j;

			cVertex->xy			=	xy + (k + j)*2;
			cVertex->next		=	vertices + k + (j + 1) % nv;
			cVertex->prev		=	vertices + k + (j - 1 + nv) % nv;
		}

		k			+=	nv;
	}
	

	// Correct the orientation
	reverse	=	orientationCheck(loops[0],TRUE);
	for (i=1;i<nloops;i++) {
		orientationCheck(loops[i],FALSE);
	}

#ifndef OLDSTYLE
	// Are we just creating a triangle ?
	if ((nloops == 1) && (nverts[0] == 3)) {
		cVertex = loops[0];
		pVertex = cVertex->prev;
		nVertex = cVertex->next;
		const int	vi0	=	(nVertex->xy - xy) >> 1;
		const int	vi1	=	(cVertex->xy - xy) >> 1;
		const int	vi2	=	(pVertex->xy - xy) >> 1;

		if (reverse == FALSE) {
			createTriangle(vindices,vi0,vi1,vi2);
		} else {
			createTriangle(vindices,vi0,vi2,vi1);
		}
		meshUniformNumber++;
		meshFacevaryingNumber	+=	3;

		return;
	}
#endif

	// Eliminate holes by connecting them to the outher hull
	for (i=1;i<nloops;i++) {
		CTriVertex	*sVertex,*dVertex;

		// Iterate over the hole vertices
		sVertex	=	loops[i];
		do {

			// Iterate over the polygon vertices
			dVertex	=	loops[0];
			do {

				// Check if can be connected to the outer hull
				if (valid(loops[0],sVertex,dVertex)) {

					// Check if we're intersecting any other holes
					for (k=1,j=i+1;j<nloops;j++) {
						if (!valid(loops[j],sVertex,dVertex)) {
							k	=	0;
							break;
						}
					}

					if (k) {
						// Connect these two vertices
						CTriVertex	*snVertex	=	(CTriVertex *) alloca(2*sizeof(CTriVertex));
						CTriVertex	*dnVertex	=	snVertex+1;

						snVertex->xy			=	sVertex->xy;
						dnVertex->xy			=	dVertex->xy;

						snVertex->prev			=	sVertex->prev;
						snVertex->next			=	dnVertex;
						dnVertex->next			=	dVertex->next;
						dnVertex->prev			=	snVertex;

						dVertex->next->prev		=	dnVertex;
						sVertex->prev->next		=	snVertex;

						dVertex->next			=	sVertex;
						sVertex->prev			=	dVertex;

						goto nextLoop;
					}
				}

				dVertex	=	dVertex->next;
			} while(dVertex != loops[0]);

			if (dVertex != loops[0]) break;

			sVertex	=	sVertex->next;
		} while(sVertex != loops[i]);

		// We have an error: could not connect the hole to the outher hull, ignore the hole
		int	temp;

		temp	=	1;

nextLoop:;

	}

	// Triangulate the outer polygon
	{
		CTriVertex	*sVertex;
		int			numVertices;

		// Count the number of vertices on the polygon
		sVertex		=	loops[0];
		cVertex		=	sVertex;
		numVertices	=	0;
		do {
			numVertices++;
			cVertex	=	cVertex->next;
		} while(sVertex != cVertex);

		// Do ear clipping
		sVertex		=	loops[0];
		while(numVertices >= 3) {
			cVertex		=	sVertex;
			do {
				pVertex			=	cVertex->prev;
				nVertex			=	cVertex->next;
				const float	a	=	area(pVertex->xy[0],pVertex->xy[1],cVertex->xy[0],cVertex->xy[1],nVertex->xy[0],nVertex->xy[1]);

				if (a >= 0) {
					if (valid(sVertex,nVertex,pVertex)) {
						const int	vi0	=	(nVertex->xy - xy) >> 1;
						const int	vi1	=	(cVertex->xy - xy) >> 1;
						const int	vi2	=	(pVertex->xy - xy) >> 1;

						if (reverse == FALSE) {
							createTriangle(vindices,vi0,vi1,vi2);
						} else {
							createTriangle(vindices,vi0,vi2,vi1);
						}

						if (sVertex == cVertex)	sVertex	=	nVertex;

						pVertex->next	=	nVertex;
						nVertex->prev	=	pVertex;

						numVertices--;
						break;
					}
				}

				cVertex	=	cVertex->next;
			} while(sVertex != cVertex);

			if (sVertex == cVertex) {
				// We have detected a self intersecting polygon,
				break;
			}
		}
	}

	// Update the data
	meshUniformNumber++;
	meshFacevaryingNumber	+=	numVertices;
}




///////////////////////////////////////////////////////////////////////
// Class				:	CPolygonMesh
// Method				:	triangulate
// Description			:	Triangulate the mesh
// Return Value			:	-
// Comments				:
// Date last edited		:	5/28/2003
void				CPolygonMesh::triangulate(CShadingContext *context) {
	int					i,j,k,numVertices;
	int					*cnholes,*cvertices,*cnvertices;
	CPlParameter		*normal;
	const float			*normalData0;
	const float			*normalData1;
	int					triangleType;

	// Transform the parameter list
	pl->transform(xform);

	// Find the type of the polygon mesh
	//	0	-	Flat polygons
	//	1	-	Smooth polygons
	//	2	-	Facevarying normal polygons
	normal		=	pl->find(VARIABLE_N,normalData0,normalData1);
	if (normal == NULL) {
		// No normal data is present
		triangleType	=	0;
		normalData0		=	NULL;
		normalData1		=	NULL;
	} else {
		switch(normal->container) {
		case CONTAINER_UNIFORM:
			triangleType	=	0;
			break;
		case CONTAINER_VERTEX:
			triangleType	=	1;
			break;
		case CONTAINER_VARYING:
			triangleType	=	1;
			break;
		case CONTAINER_FACEVARYING:
			triangleType	=	2;
			break;
		case CONTAINER_CONSTANT:
			triangleType	=	0;
			break;
		default:
			error(CODE_BUG,"Unknown container type in polygon mesh.\n");
			triangleType	=	0;
			break;
		}
	}

	// Allocate the space for the children triangles
	children	=	new CArray<CObject *>;

	// Count the number of vertices there is in the mesh
	for (j=0,i=0;i<npoly;i++)	j+=nholes[i];
	for (k=0,i=0;i<j;i++)		k+=nvertices[i];

	for (numVertices=0,i=0;i<k;i++) {
		if (vertices[i] > numVertices)	numVertices	=	vertices[i];
	}
	numVertices++;

	parameters				=	pl->parameterUsage();

	// Fill in the data structure
	meshAttributes			=	attributes;
	meshXform				=	xform;
	meshPl					=	pl;
	meshChildren			=	children;
	meshP					=	pl->data0;
	meshNormal				=	normal;
	meshNormalData0			=	normalData0;
	meshNormalData1			=	normalData1;
	meshTriangleType		=	triangleType;
	meshUniformNumber		=	0;
	meshFacevaryingNumber	=	0;
	mesh					=	this;
	meshContext				=	context;

	// Triangulate the individual polygons
	for (cnholes=nholes,cvertices=vertices,cnvertices=nvertices,i=0;i<npoly;i++) {
		// Triangulate the current polygon
		triangulatePolygon(cnholes[0],cnvertices,cvertices);

		// Advance the holes
		for (j=0;j<cnholes[0];j++) {
			cvertices	+=	cnvertices[j];
		}
		cnvertices	+=	cnholes[0];
		cnholes++;
	}
}



