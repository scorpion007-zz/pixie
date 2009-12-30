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
//  File				:	polygon.cpp
//  Classes				:	CPolygonMesh
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "polygons.h"
#include "object.h"
#include "stats.h"
#include "memory.h"
#include "shading.h"
#include "error.h"
#include "surface.h"
#include "renderer.h"
#include "rendererContext.h"
#include "patches.h"
#include "common/polynomial.h"

#if 0
#if !defined(_WINDOWS)
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
#endif

// For debugging only, force all trace calls to go through the tesselation patch
#define FORCE_TESSELATED_TRACE 0

///////////////////////////////////////////////////////////////////////
// Class				:	CTriVertex
// Description			:	This is a temporary vertex used during the triangulation
// Comments				:
class	CTriVertex {
public:
	const	float		*xy;
	CTriVertex			*next,*prev;
};



///////////////////////////////////////////////////////////////////////
// Class				:	CMeshData
// Description			:	This class holds transient data about the polygon mesh used during triangulation
// Comments				:
class	CMeshData {
public:
	CAttributes			*meshAttributes;		// Mesh attributes
	CXform				*meshXform;				// Mesh xform
	CPl					*meshPl;				// Parameter list
	CObject				*meshChildren;			// List of children
	const float			*meshP;					// The vertex positions
	CPlParameter		*meshNormal;			// The normal parameter
	const float			*meshNormalData0;		// The normal data at shutter open
	const float			*meshNormalData1;		// The normal data at shutter close
	int					meshTriangleType;		// The triangle type
	int					meshUniformNumber;		// The current uniform number
	int					meshFacevaryingNumber;	// The current facevarying number
	CPolygonMesh		*mesh;					// The mesh we're allocating the triangle for
	CShadingContext		*meshContext;			// The shading context
};






///////////////////////////////////////////////////////////////////////
// Class				:	CPolygonTriangle
// Method				:	CPolygonTriangle
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CPolygonTriangle::CPolygonTriangle(CAttributes *a,CXform *x,CPolygonMesh *mesh,int iv0,int iv1,int iv2,int ifv0,int ifv1,int ifv2,int iuniform) : CSurface(a,x) {
	atomicIncrement(&stats.numGprims);

	// Save the parameters
	this->mesh				=	mesh;
	mesh->attach();

	this->v0				=	iv0;
	this->v1				=	iv1;
	this->v2				=	iv2;
	this->fv0				=	ifv0;
	this->fv1				=	ifv1;
	this->fv2				=	ifv2;
	this->uniform			=	iuniform;

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
// Method				:	~CPolygonTriangle
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CPolygonTriangle::~CPolygonTriangle() {
	atomicDecrement(&stats.numGprims);
	mesh->detach();
}



///////////////////////////////////////////////////////////////////////
// Class				:	CPolygonTriangle
// Method				:	intersect
// Description			:	Intersect the polygon with the ray
// Return Value			:	-
// Comments				:
void		CPolygonTriangle::intersect(CShadingContext *context,CRay *cRay) {
	if (! (cRay->flags & attributes->flags) )	return;

	if (attributes->flags & ATTRIBUTES_FLAGS_LOD) {
		const float importance = attributes->lodImportance;
		if (importance >= 0) {
			if (cRay->jimp > importance)			return;
		} else {
			if ((1-cRay->jimp) >= -importance)		return;
		}
	}

	// smash to grids if we've got displacement
	if ((attributes->displacement != NULL) && (attributes->flags & ATTRIBUTES_FLAGS_DISPLACEMENTS) || FORCE_TESSELATED_TRACE) {
		// Do we have a grid ?
		if (children == NULL) {
			osLock(CRenderer::tesselateMutex);
	
			if (children == NULL) {
				CTesselationPatch	*tesselation	=	new CTesselationPatch(attributes,xform,this,0,1,0,1,0,0,-1);

				tesselation->initTesselation(context);
				tesselation->attach();
				children				=	tesselation;
			}
	
			osUnlock(CRenderer::tesselateMutex);
		}
		return;
	}

	// Get the polygon corners
	const CPl	*pl			=	mesh->pl;
	const float	*vertices	=	pl->data0;
	const float	*vert0		=	vertices + this->v0*3;
	const float	*vert1		=	vertices + this->v1*3;
	const float	*vert2		=	vertices + this->v2*3;
	vector		t0,t1,t2;

	if ((vertices = pl->data1) != NULL) {
		interpolatev(t0,vert0,vertices + this->v0*3,cRay->time);	vert0	=	t0;
		interpolatev(t1,vert1,vertices + this->v1*3,cRay->time);	vert1	=	t1;
		interpolatev(t2,vert2,vertices + this->v2*3,cRay->time);	vert2	=	t2;
	} 

	// The ray triangle intersection code
	// Hacked away from the article titled "Fast, Minimum Storage Ray-Triangle Intersection"
	//	http://jgt.akpeters.com/papers/MollerTrumbore97/

	vector	edge1,edge2,tvec,pvec,qvec;

	subvv(edge1,vert1,vert0);
	subvv(edge2,vert2,vert0);
	crossvv(pvec,cRay->dir,edge2);

	const float det = dotvv(edge1, pvec);

	if (attributes->flags & ATTRIBUTES_FLAGS_DOUBLE_SIDED) {
		const float	inv_det = 1.0f / det;

		subvv(tvec, cRay->from, vert0);

		const float	u = dotvv(tvec, pvec) * inv_det;
		if (u < 0.0 || u > 1.0)	return;

		crossvv(qvec, tvec, edge1);

		const float	v = dotvv(cRay->dir, qvec) * inv_det;
		if (v < 0.0 || u + v > 1.0)	return;

		const float t = dotvv(edge2, qvec) * inv_det;

		if ((t > cRay->tmin) && (t < cRay->t)) {
			cRay->object	=	this;
			cRay->t			=	t;
			cRay->u			=	u + v;
			cRay->v			=	u / (u + v);
			if	((attributes->flags & ATTRIBUTES_FLAGS_INSIDE) ^ xform->flip)	crossvv(cRay->N,edge2,edge1);
			else																crossvv(cRay->N,edge1,edge2);
		}
	} else {

		if ((attributes->flags & ATTRIBUTES_FLAGS_INSIDE) ^ xform->flip) {
			if (det < 0)	return;
		} else {
			if (det > 0)	return;
		}

		subvv(tvec, cRay->from, vert0);

		const float	u = dotvv(tvec, pvec);
		if (u < 0.0 || u > det)	return;

		crossvv(qvec, tvec, edge1);

		const float	v = dotvv(cRay->dir, qvec);
		if (v < 0.0 || u + v > det)	return;

		const float t = dotvv(edge2, qvec);
		const float	inv_det = 1.0f / det;
		if ((t > cRay->tmin) && (t < cRay->t)) {
			cRay->object	=	this;
			cRay->t			=	t*inv_det;
			cRay->u			=	(u + v)*inv_det;
			cRay->v			=	u / (u + v);
			if	((attributes->flags & ATTRIBUTES_FLAGS_INSIDE) ^ xform->flip)	crossvv(cRay->N,edge2,edge1);
			else																crossvv(cRay->N,edge1,edge2);
		}
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPolygonTriangle
// Method				:	sample
// Description			:	Sample bunch of points on the triangle
// Return Value			:	-
// Comments				:
void		CPolygonTriangle::sample(int start,int numVertices,float **varying,float ***locals,unsigned int &up) const {
	const float	*u				=	varying[VARIABLE_U] + start;
	const float	*v				=	varying[VARIABLE_V] + start;
	const CPl	*pl				=	mesh->pl;


	if ((pl->data1 != NULL) && (!(up & (PARAMETER_BEGIN_SAMPLE | PARAMETER_END_SAMPLE)))) {
		const float		*time	=	varying[VARIABLE_TIME] + start;

		// Interpolate the vertex variables accross the triangle
		for (int j=0;j<pl->numParameters;++j) {
			const CVariable	*variable	=	pl->parameters[j].variable;
			const int		numFloats	=	variable->numFloats;

			// Is this a vertex parameter?
			if (pl->parameters[j].container == CONTAINER_VERTEX) {
				float		*dest	=	pl->parameters[j].resolve(varying,locals) + start*numFloats;

				if (dest != NULL) {
					const float	*data0	=	pl->data0 + pl->parameters[j].index;
					const float	*data1	=	pl->data1 + pl->parameters[j].index;
					
					assert(isAligned64(data0));
					assert(isAligned64(data1));
					
					const float	*sv00	=	data0 + this->v0*variable->numFloats;
					const float	*sv01	=	data0 + this->v1*variable->numFloats;
					const float	*sv02	=	data0 + this->v2*variable->numFloats;
					const float	*sv10	=	data1 + this->v0*variable->numFloats;
					const float	*sv11	=	data1 + this->v1*variable->numFloats;
					const float	*sv12	=	data1 + this->v2*variable->numFloats;

					for (int i=0;i<numVertices;++i) {
						const	double	cu		=	u[i];
						const	double	cv		=	v[i];
						const	double	ctime	=	time[i];

						for (int k=0;k<numFloats;++k) {
							*dest++	=	(float) ((sv00[k]*(1.0-cu) + sv01[k]*cu*cv + sv02[k]*cu*(1.0-cv))*(1.0-ctime) + 
												 (sv10[k]*(1.0-cu) + sv11[k]*cu*cv + sv12[k]*cu*(1.0-cv))*ctime);
						}
					}
				}
			}
		}

		// Get the corners
		const float *v00	=	pl->data0 + this->v0*3;
		const float *v01	=	pl->data0 + this->v1*3;
		const float *v02	=	pl->data0 + this->v2*3;
		const float *v10	=	pl->data1 + this->v0*3;
		const float *v11	=	pl->data1 + this->v1*3;
		const float *v12	=	pl->data1 + this->v2*3;

		// Compute surface derivatives and normal if required
		if (up & PARAMETER_DPDU) {
			float	*dest	=	varying[VARIABLE_DPDU] + start*3;

			for (int i=0;i<numVertices;++i,dest+=3) {
				const double cv		=	v[i];
				const double ctime	=	time[i];

				dest[0]			=	(float) ((v01[0]*cv + v02[0]*(1.0-cv) - v00[0])*(1.0-ctime) + (v11[0]*cv + v12[0]*(1-cv) - v10[0])*ctime);
				dest[1]			=	(float) ((v01[1]*cv + v02[1]*(1.0-cv) - v00[1])*(1.0-ctime) + (v11[1]*cv + v12[1]*(1-cv) - v10[1])*ctime);
				dest[2]			=	(float) ((v01[2]*cv + v02[2]*(1.0-cv) - v00[2])*(1.0-ctime) + (v11[2]*cv + v12[2]*(1-cv) - v10[2])*ctime);
			}
		}

		if (up & PARAMETER_DPDV) {
			float	*dest	=	varying[VARIABLE_DPDV] + start*3;

			for (int i=0;i<numVertices;++i,dest+=3) {
				const double cu		=	u[i];
				const double ctime	=	time[i];

				dest[0]			=	(float) ((v01[0] - v02[0])*cu*(1.0-ctime) + (v11[0] - v12[0])*cu*ctime);
				dest[1]			=	(float) ((v01[1] - v02[1])*cu*(1.0-ctime) + (v11[1] - v12[1])*cu*ctime);
				dest[2]			=	(float) ((v01[2] - v02[2])*cu*(1.0-ctime) + (v11[2] - v12[2])*cu*ctime);
			}
		}

		if (up & PARAMETER_NG) {
			float	*dest	=	varying[VARIABLE_NG] + start*3;
			vector	normal0,normal1;
			vector	D0,D1;

			// Compute the normal at the beginning
			subvv(D0,v01,v00);
			subvv(D1,v02,v00);
			crossvv(normal0,D1,D0);

			// And at the end
			subvv(D0,v11,v10);
			subvv(D1,v12,v10);
			crossvv(normal1,D1,D0);

			// Interpolate the normal vector
			for (int i=0;i<numVertices;i++,dest+=3)	interpolatev(dest,normal0,normal1,time[i]);
		}
	} else {
		const float		*data;

		if (up & PARAMETER_END_SAMPLE)	data		=	pl->data1;
		else							data		=	pl->data0;

		// Interpolate the vertex variables accross the triangle
		for (int j=0;j<pl->numParameters;++j) {
			const CVariable	*variable	=	pl->parameters[j].variable;
			const int		numFloats	=	variable->numFloats;

			// Should we interpolate this parameter?
			if (pl->parameters[j].container == CONTAINER_VERTEX) {
				float		*dest	=	pl->parameters[j].resolve(varying,locals);

				if (dest != NULL) {
					dest += start*numFloats;
					assert(isAligned64(data + pl->parameters[j].index));
					
					const float	*sv0	=	data + pl->parameters[j].index + this->v0*variable->numFloats;
					const float	*sv1	=	data + pl->parameters[j].index + this->v1*variable->numFloats;
					const float	*sv2	=	data + pl->parameters[j].index + this->v2*variable->numFloats;

					for (int i=0;i<numVertices;++i) {
						const	double	cu	=	u[i];
						const	double	cv	=	v[i];

						for (int k=0;k<numFloats;++k) {
							*dest++	=	(float) (sv0[k]*(1.0-cu) + sv1[k]*cu*cv + sv2[k]*cu*(1.0-cv));
						}
					}
				}
			}
		}
		
		// Get the vertex corners
		const float	*v0	=	data + this->v0*3;
		const float	*v1	=	data + this->v1*3;
		const float	*v2	=	data + this->v2*3;

		// Compute surface derivatives and normal if required
		if (up & PARAMETER_DPDU) {
			float	*dest	=	varying[VARIABLE_DPDU] + start*3;

			for (int i=0;i<numVertices;++i,dest+=3) {
				const double cv	=	v[i];

				dest[0]			=	(float) (v1[0]*cv + v2[0]*(1.0-cv) - v0[0]);
				dest[1]			=	(float) (v1[1]*cv + v2[1]*(1.0-cv) - v0[1]);
				dest[2]			=	(float) (v1[2]*cv + v2[2]*(1.0-cv) - v0[2]);
			}
		}

		if (up & PARAMETER_DPDV) {
			float	*dest	=	varying[VARIABLE_DPDV] + start*3;

			for (int i=0;i<numVertices;++i,dest+=3) {
				const double cu	=	u[i];

				dest[0]			=	(float) ((v1[0] - v2[0])*cu);
				dest[1]			=	(float) ((v1[1] - v2[1])*cu);
				dest[2]			=	(float) ((v1[2] - v2[2])*cu);
			}
		}

		if (up & PARAMETER_NG) {
			float	*dest	=	varying[VARIABLE_NG] + start*3;
			vector	normal;
			vector	D0,D1;

			// Compute the normal vector
			subvv(D0,v1,v0);
			subvv(D1,v2,v0);
			crossvv(normal,D1,D0);

			// Just duplicate the normal vector
			for (int i=0;i<numVertices;++i,dest+=3)		movvv(dest,normal);
		}
	}
	
	// Compute dPdtime
	if (up & PARAMETER_DPDTIME) {
		float	*dest	=	varying[VARIABLE_DPDTIME] + start*3;
		
		// Do we have motion?
		if (pl->data1 != NULL) {
			const float *v00	=	pl->data0 + this->v0*3;
			const float *v01	=	pl->data0 + this->v1*3;
			const float *v02	=	pl->data0 + this->v2*3;
			const float *v10	=	pl->data1 + this->v0*3;
			const float *v11	=	pl->data1 + this->v1*3;
			const float *v12	=	pl->data1 + this->v2*3;
			assert(u == (varying[VARIABLE_U] + start));
			assert(v == (varying[VARIABLE_V] + start));
			for (int i=0;i<numVertices;++i) {
				const	double	cu	=	u[i];
				const	double	cv	=	v[i];

				// Do the interpolation
				for (int k=0;k<3;k++) {
					*dest++	=	(float) ((v10[k]*(1.0-cu) + v11[k]*cu*cv + v12[k]*cu*(1.0-cv)) - (v00[k]*(1.0-cu) + v01[k]*cu*cv + v02[k]*cu*(1.0-cv)));					
				}
				
				// Scale the dPdtime
				mulvf(dest-3,CRenderer::invShutterTime);
			}
		} else {
			// We have no motion, so dPdtime is {0,0,0}
			for (int i=0;i<numVertices;++i,dest+=3)	initv(dest,0,0,0);
		}
	}

	// Turn off the interpolated variables
	up	&=	~(PARAMETER_P | PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_NG | PARAMETER_DPDTIME | mesh->parameters);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPolygonTriangle
// Method				:	interpolate
// Description			:	Core interpolation
// Return Value			:	-
// Comments				:
void			CPolygonTriangle::interpolate(int numVertices,float **varying,float ***locals) const {
	int			i,j,k;
	const float	*u				=	varying[VARIABLE_U];
	const float	*v				=	varying[VARIABLE_V];
	const CPl	*pl				=	mesh->pl;
	
	for (i=0;i<pl->numParameters;i++) {
		const CPlParameter	*cParameter	=	pl->parameters+i;
		const CVariable		*cVariable	=	cParameter->variable;
		const int			numFloats	=	cVariable->numFloats;
		float				*dest		=	cParameter->resolve(varying,locals);
		const float			*src;
		const float			*v0,*v1,*v2;

		if (dest != NULL) {
			const float	*data			=	pl->data0 + cParameter->index;

			switch(cParameter->container) {
			case CONTAINER_UNIFORM:

				if (cVariable->type != TYPE_STRING) {

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
				} else {

					if ((cVariable->container == CONTAINER_UNIFORM) || (cVariable->container == CONTAINER_CONSTANT)) {
						const char ** srcs		=	((const char **) data) + this->uniform*numFloats;
						const char ** dests		=	(const char **) dest;
						
						assert(isAligned64(srcs));
						assert(isAligned64(dests));

						for (j=numFloats;j>0;j--) {
							*dests++	=	*srcs++;
						}
					} else {
						const char ** srcs		=	((const char **) data) + this->uniform*numFloats;
						const char ** dests		=	(const char **) dest;
						
						assert(isAligned64(srcs));
						assert(isAligned64(dests));
						
						// premote
						for(j=0;j<numVertices;j++) {
							const char **csrcs	=	srcs;
							for (k=numFloats;k>0;k--) {
								*dests++	=	*csrcs++;
							}
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
					const	double	cu	=	u[j];
					const	double	cv	=	v[j];

					for (k=0;k<numFloats;k++) {
						*dest++	=	(float) (v0[k]*(1-cu) + v1[k]*cu*cv + v2[k]*cu*(1-cv));
					}
				}

				break;
			case CONTAINER_FACEVARYING:
				v0	=	data + this->fv0*numFloats;
				v1	=	data + this->fv1*numFloats;
				v2	=	data + this->fv2*numFloats;
				for (j=0;j<numVertices;j++) {
					const	double	cu	=	u[j];
					const	double	cv	=	v[j];

					for (k=0;k<numFloats;k++) {
						*dest++	=	(float) (v0[k]*(1-cu) + v1[k]*cu*cv + v2[k]*cu*(1-cv));
					}
				}
				break;
			case CONTAINER_CONSTANT:
				if (cVariable->type == TYPE_STRING) {

					if ((cVariable->container == CONTAINER_UNIFORM) || (cVariable->container == CONTAINER_CONSTANT)) {
						const char **srcs	=	(const char**) data;
						const char **dests	=	(const char**) dest;

						assert(isAligned64(srcs));
						assert(isAligned64(dests));
						
						for (j=numFloats;j>0;j--) {
							*dests++	=	*srcs++;
						}
					} else {
						const char **srcs	=	(const char**) data;
						const char **dests	=	(const char**) dest;

						assert(isAligned64(srcs));
						assert(isAligned64(dests));
						
						// premote
						for(j=0;j<numVertices;j++) {
							const char **csrcs	=	srcs;
							for (k=numFloats;k>0;k--) {
								*dests++	=	*csrcs++;
							}
						}
					}
				} else {
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
				}
				break;
			}
		}
	}
}
























///////////////////////////////////////////////////////////////////////
// Class				:	CPolygonQuad
// Method				:	CPolygonQuad
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CPolygonQuad::CPolygonQuad(CAttributes *a,CXform *x,CPolygonMesh *mesh,int iv0,int iv1,int iv2,int iv3,int ifv0,int ifv1,int ifv2,int ifv3,int iuniform) : CSurface(a,x) {
	atomicIncrement(&stats.numGprims);

	// Save the parameters
	this->mesh				=	mesh;
	mesh->attach();

	this->v0				=	iv0;
	this->v1				=	iv1;
	this->v2				=	iv2;
	this->v3				=	iv3;
	this->fv0				=	ifv0;
	this->fv1				=	ifv1;
	this->fv2				=	ifv2;
	this->fv3				=	ifv3;
	this->uniform			=	iuniform;

	const CPl	*pl			=	mesh->pl;
	const float	*vertices	=	pl->data0;
	const float	*v0			=	vertices + this->v0*3;

	// Bound the primitive in the camera space
	movvv(bmin,v0);
	movvv(bmax,v0);

	addBox(bmin,bmax,vertices + this->v1*3);
	addBox(bmin,bmax,vertices + this->v2*3);
	addBox(bmin,bmax,vertices + this->v3*3);

	if ((vertices=pl->data1) != NULL) {
		vertices	=	pl->data1;

		addBox(bmin,bmax,vertices + this->v0*3);
		addBox(bmin,bmax,vertices + this->v1*3);
		addBox(bmin,bmax,vertices + this->v2*3);
		addBox(bmin,bmax,vertices + this->v3*3);
	}

	makeBound(bmin,bmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPolygonQuad
// Method				:	~CPolygonQuad
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CPolygonQuad::~CPolygonQuad() {
	atomicDecrement(&stats.numGprims);
	mesh->detach();
}



///////////////////////////////////////////////////////////////////////
// Class				:	CPolygonQuad
// Method				:	intersect
// Description			:	Intersect the quad with a ray
// Return Value			:	-
// Comments				:
void		CPolygonQuad::intersect(CShadingContext *context,CRay *cRay) {
	if (! (cRay->flags & attributes->flags) )	return;

	if (attributes->flags & ATTRIBUTES_FLAGS_LOD) {
		const float importance = attributes->lodImportance;
		if (importance >= 0) {
			if (cRay->jimp > importance)			return;
		} else {
			if ((1-cRay->jimp) >= -importance)		return;
		}
	}

	// smash to grids if we've got displacement
	if ((attributes->displacement != NULL) && (attributes->flags & ATTRIBUTES_FLAGS_DISPLACEMENTS) || FORCE_TESSELATED_TRACE) {
		// Do we have a grid ?
		if (children == NULL) {
			osLock(CRenderer::tesselateMutex);
	
			if (children == NULL) {
				CTesselationPatch	*tesselation	=	new CTesselationPatch(attributes,xform,this,0,1,0,1,0,0,-1);

				tesselation->initTesselation(context);
				tesselation->attach();
				children				=	tesselation;
			}
	
			osUnlock(CRenderer::tesselateMutex);
		}
		return;
	}

	const CPl	*pl			=	mesh->pl;
	const float	*vertices	=	pl->data0;
	const float	*P00		=	vertices + this->v0*3;
	const float	*P10		=	vertices + this->v1*3;
	const float	*P01		=	vertices + this->v2*3;
	const float	*P11		=	vertices + this->v3*3;
	vector	t0,t1,t2,t3;

	if ((vertices = pl->data1) != NULL) {
		interpolatev(t0,P00,vertices + this->v0*3,cRay->time);	P00	=	t0;
		interpolatev(t1,P10,vertices + this->v1*3,cRay->time);	P10	=	t1;
		interpolatev(t2,P01,vertices + this->v2*3,cRay->time);	P01	=	t2;
		interpolatev(t3,P11,vertices + this->v3*3,cRay->time);	P11	=	t3;
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
					cRay->u			=	(float) u;					\
					cRay->v			=	(float) v;					\
					cRay->t			=	(float) t;					\
					movvv(cRay->N,N);								\
				} else {											\
					if (dotvv(q,N) < 0) {							\
						cRay->object	=	this;					\
						cRay->u			=	(float) u;				\
						cRay->v			=	(float) v;				\
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
// Class				:	CPolygonQuad
// Method				:	sample
// Description			:	Sample bunch of points on the quad
// Return Value			:	-
// Comments				:
void		CPolygonQuad::sample(int start,int numVertices,float **varying,float ***locals,unsigned int &up) const {
	const float	*u				=	varying[VARIABLE_U] + start;
	const float	*v				=	varying[VARIABLE_V] + start;
	const CPl	*pl				=	mesh->pl;


	if ((pl->data1 != NULL) && (!(up & (PARAMETER_BEGIN_SAMPLE | PARAMETER_END_SAMPLE)))) {
		const float		*time	=	varying[VARIABLE_TIME] + start;

		// Interpolate the vertex variables accross the triangle
		for (int j=0;j<pl->numParameters;j++) {
			
			// Is this a vertex variable that needs to be interpolated?
			if (pl->parameters[j].container == CONTAINER_VERTEX) {
				const CVariable	*variable	=	pl->parameters[j].variable;
				const int		numFloats	=	variable->numFloats;
				float			*dest		=	pl->parameters[j].resolve(varying,locals) + start*numFloats;

				if (dest != NULL) {
					const float	*data0	=	pl->data0 + pl->parameters[j].index;
					const float	*data1	=	pl->data1 + pl->parameters[j].index;
					
					assert(isAligned64(data0));
					assert(isAligned64(data1));

					const float	*sv00	=	data0 + this->v0*variable->numFloats;
					const float	*sv01	=	data0 + this->v1*variable->numFloats;
					const float	*sv02	=	data0 + this->v2*variable->numFloats;
					const float	*sv03	=	data0 + this->v3*variable->numFloats;
					const float	*sv10	=	data1 + this->v0*variable->numFloats;
					const float	*sv11	=	data1 + this->v1*variable->numFloats;
					const float	*sv12	=	data1 + this->v2*variable->numFloats;
					const float	*sv13	=	data1 + this->v3*variable->numFloats;

					for (int i=0;i<numVertices;i++) {
						const	double	cu		=	u[i];
						const	double	cv		=	v[i];
						const	double	ctime	=	time[i];

						for (int k=0;k<numFloats;k++) {
							*dest++	=	(float) (((sv00[k]*(1.0-cu) + sv01[k]*cu)*(1.0-cv) + (sv02[k]*(1.0-cu) + sv03[k]*cu)*cv)*(1.0-ctime) + 
												 ((sv10[k]*(1.0-cu) + sv11[k]*cu)*(1.0-cv) + (sv12[k]*(1.0-cu) + sv13[k]*cu)*cv)*ctime);
						}
					}
				}
			}
		}

		const float	*v00	=	pl->data0 + this->v0*3;
		const float	*v01	=	pl->data0 + this->v1*3;
		const float	*v02	=	pl->data0 + this->v2*3;
		const float	*v03	=	pl->data0 + this->v3*3;
		const float	*v10	=	pl->data1 + this->v0*3;
		const float	*v11	=	pl->data1 + this->v1*3;
		const float	*v12	=	pl->data1 + this->v2*3;
		const float	*v13	=	pl->data1 + this->v3*3;

		// Compute surface derivatives and normal if required
		if (up & (PARAMETER_DPDU | PARAMETER_NG)) {
			float	*dest	=	varying[VARIABLE_DPDU]+start*3;

			for (int i=0;i<numVertices;++i,dest+=3) {
				const double cv		=	v[i];
				const double ctime	=	time[i];

				dest[0]			=	(float) (((-v00[0] + v01[0])*(1.0-cv) + (-v02[0] + v03[0])*cv)*(1.0-ctime) + ((-v10[0] + v11[0])*(1.0-cv) + (-v12[0] + v13[0])*cv)*ctime);
				dest[1]			=	(float) (((-v00[1] + v01[1])*(1.0-cv) + (-v02[1] + v03[1])*cv)*(1.0-ctime) + ((-v10[1] + v11[1])*(1.0-cv) + (-v12[1] + v13[1])*cv)*ctime);
				dest[2]			=	(float) (((-v00[2] + v01[2])*(1.0-cv) + (-v02[2] + v03[2])*cv)*(1.0-ctime) + ((-v10[2] + v11[2])*(1.0-cv) + (-v12[2] + v13[2])*cv)*ctime);
			}
		}

		if (up & (PARAMETER_DPDV | PARAMETER_NG)) {
			float	*dest	=	varying[VARIABLE_DPDV]+start*3;

			for (int i=0;i<numVertices;++i,dest+=3) {
				const double cu		=	u[i];
				const double ctime	=	time[i];

				dest[0]			=	(float) ((-(v00[0]*(1.0-cu) + (v01[0]*cu)) + (v02[0]*(1.0-cu) + (v03[0]*cu)))*(1.0-ctime) + (-(v10[0]*(1.0-cu) + (v11[0]*cu)) + (v12[0]*(1.0-cu) + (v13[0]*cu)))*ctime);
				dest[1]			=	(float) ((-(v00[1]*(1.0-cu) + (v01[1]*cu)) + (v02[1]*(1.0-cu) + (v03[1]*cu)))*(1.0-ctime) + (-(v10[1]*(1.0-cu) + (v11[1]*cu)) + (v12[1]*(1.0-cu) + (v13[1]*cu)))*ctime);
				dest[2]			=	(float) ((-(v00[2]*(1.0-cu) + (v01[2]*cu)) + (v02[2]*(1.0-cu) + (v03[2]*cu)))*(1.0-ctime) + (-(v10[2]*(1.0-cu) + (v11[2]*cu)) + (v12[2]*(1.0-cu) + (v13[2]*cu)))*ctime);
			}
		}

		if (up & PARAMETER_NG) {
			float	*dest	=	varying[VARIABLE_NG] + start*3;
			float	*dPdu	=	varying[VARIABLE_DPDU] + start*3;
			float	*dPdv	=	varying[VARIABLE_DPDV] + start*3;

			for (int i=0;i<numVertices;++i) {
				crossvv(dest,dPdu,dPdv);

				dest			+=	3;
				dPdu			+=	3;
				dPdv			+=	3;
			}
		}
	} else {
		const float		*data;

		if (up & PARAMETER_END_SAMPLE)	data		=	pl->data1;
		else							data		=	pl->data0;

		// Interpolate the vertex variables accross the triangle
		for (int j=0;j<pl->numParameters;j++) {
			const CVariable	*variable	=	pl->parameters[j].variable;
			const int		numFloats	=	variable->numFloats;

			if (pl->parameters[j].container == CONTAINER_VERTEX) {
				float		*dest	=	pl->parameters[j].resolve(varying,locals) + start*numFloats;

				if (dest != NULL) {
					const float	*sv0	=	data + pl->parameters[j].index + this->v0*variable->numFloats;
					const float	*sv1	=	data + pl->parameters[j].index + this->v1*variable->numFloats;
					const float	*sv2	=	data + pl->parameters[j].index + this->v2*variable->numFloats;
					const float	*sv3	=	data + pl->parameters[j].index + this->v3*variable->numFloats;

					for (int i=0;i<numVertices;++i) {
						const	double cu	=	u[i];
						const	double cv	=	v[i];

						for (int k=0;k<numFloats;k++) {
							*dest++	=	(float) ((sv0[k]*(1.0-cu) + sv1[k]*cu)*(1.0-cv) + (sv2[k]*(1.0-cu) + sv3[k]*cu)*cv);
						}
					}
				}
			}
		}
		
		// Get the quad corners
		const float *v0	=	data + this->v0*3;
		const float *v1	=	data + this->v1*3;
		const float *v2	=	data + this->v2*3;
		const float *v3	=	data + this->v3*3;
		
		// Compute surface derivatives and normal if required
		if (up & (PARAMETER_DPDU | PARAMETER_NG)) {
			float	*dest	=	varying[VARIABLE_DPDU]+start*3;

			for (int i=0;i<numVertices;++i,dest+=3) {
				const double cv	=	v[i];

				dest[0]			=	(float) ((v1[0] - v0[0])*(1.0-cv) + (v3[0] - v2[0])*cv);
				dest[1]			=	(float) ((v1[1] - v0[1])*(1.0-cv) + (v3[1] - v2[1])*cv);
				dest[2]			=	(float) ((v1[2] - v0[2])*(1.0-cv) + (v3[2] - v2[2])*cv);
			}
		}

		if (up & (PARAMETER_DPDV | PARAMETER_NG)) {
			float	*dest	=	varying[VARIABLE_DPDV]+start*3;

			for (int i=0;i<numVertices;i++,dest+=3) {
				const double cu	=	u[i];

				dest[0]			=	(float) ((v2[0]*(1.0-cu) + v3[0]*cu) - (v0[0]*(1.0-cu) + v1[0]*cu));
				dest[1]			=	(float) ((v2[1]*(1.0-cu) + v3[1]*cu) - (v0[1]*(1.0-cu) + v1[1]*cu));
				dest[2]			=	(float) ((v2[2]*(1.0-cu) + v3[2]*cu) - (v0[2]*(1.0-cu) + v1[2]*cu));
			}
		}

		if (up & PARAMETER_NG) {
			float	*dest	=	varying[VARIABLE_NG]+start*3;
			float	*dPdu	=	varying[VARIABLE_DPDU]+start*3;
			float	*dPdv	=	varying[VARIABLE_DPDV]+start*3;

			for (int i=0;i<numVertices;++i) {
				crossvv(dest,dPdu,dPdv);

				dest			+=	3;
				dPdu			+=	3;
				dPdv			+=	3;
			}
		}
	}
	
	// Compute dPdtime
	if (up & PARAMETER_DPDTIME) {
		float	*dest	=	varying[VARIABLE_DPDTIME] + start*3;
		
		// Do we have motion?
		if (pl->data1 != NULL) {
			const float *v00	=	pl->data0 + this->v0*3;
			const float *v01	=	pl->data0 + this->v1*3;
			const float *v02	=	pl->data0 + this->v2*3;
			const float *v03	=	pl->data0 + this->v3*3;
			const float *v10	=	pl->data1 + this->v0*3;
			const float *v11	=	pl->data1 + this->v1*3;
			const float *v12	=	pl->data1 + this->v2*3;
			const float *v13	=	pl->data1 + this->v3*3;
			assert(u == (varying[VARIABLE_U] + start));
			assert(v == (varying[VARIABLE_V] + start));
			for (int i=0;i<numVertices;++i,dest+=3) {
				const	double	cu	=	u[i];
				const	double	cv	=	v[i];

				// Do the interpolation
				for (int k=0;k<3;k++) {
					dest[k]	=	(float) (((v10[k]*(1.0-cu) + v11[k]*cu)*(1.0-cv) + (v12[k]*(1.0-cu) + v13[k]*cu)*cv) - ((v00[k]*(1.0-cu) + v01[k]*cu)*(1.0-cv) + (v02[k]*(1.0-cu) + v03[k]*cu)*cv));
				}
				
				// Scale the dPdtime
				mulvf(dest,CRenderer::invShutterTime);
			}
		} else {
			// We have no motion, so dPdtime is {0,0,0}
			for (int i=0;i<numVertices;++i,dest+=3)	initv(dest,0,0,0);
		}
	}

	// Turn off the interpolated variables
	up	&=	~(PARAMETER_P | PARAMETER_DPDU | PARAMETER_DPDV | PARAMETER_NG | PARAMETER_DPDTIME | mesh->parameters);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPolygonQuad
// Method				:	interpolate
// Description			:	Core interpolation
// Return Value			:	-
// Comments				:
void			CPolygonQuad::interpolate(int numVertices,float **varying,float ***locals) const {
	int			i,j,k;
	const float	*u				=	varying[VARIABLE_U];
	const float	*v				=	varying[VARIABLE_V];
	const CPl	*pl				=	mesh->pl;
	
	for (i=0;i<pl->numParameters;i++) {
		const CPlParameter	*cParameter	=	pl->parameters+i;
		const CVariable		*cVariable	=	cParameter->variable;
		const int			numFloats	=	cVariable->numFloats;
		float				*dest		=	cParameter->resolve(varying,locals);
		const float			*src;
		const float			*v0,*v1,*v2,*v3;

		if (dest != NULL) {
			const float	*data			=	pl->data0 + cParameter->index;

			switch(cParameter->container) {
			case CONTAINER_UNIFORM:
				if (cVariable->type != TYPE_STRING) {
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
				} else {
					if ((cVariable->container == CONTAINER_UNIFORM) || (cVariable->container == CONTAINER_CONSTANT)) {
						const char ** srcs		=	((const char **) data) + this->uniform*numFloats;
						const char ** dests		=	(const char **) dest;
						
						assert(isAligned64(srcs));
						assert(isAligned64(dests));

						for (j=numFloats;j>0;j--) {
							*dests++	=	*srcs++;
						}
					} else {
						const char ** srcs		=	((const char **) data) + this->uniform*numFloats;
						const char ** dests		=	(const char **) dest;
						
						assert(isAligned64(srcs));
						assert(isAligned64(dests));
						
						// premote
						for(j=0;j<numVertices;j++) {
							const char **csrcs	=	srcs;
							for (k=numFloats;k>0;k--) {
								*dests++	=	*csrcs++;
							}
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
				v3	=	data + this->v3*numFloats;
				for (j=0;j<numVertices;j++) {
					const	double	cu	=	u[j];
					const	double	cv	=	v[j];

					for (k=0;k<numFloats;k++) {
						*dest++	=	(float) ((v0[k]*(1.0-cu) + v1[k]*cu)*(1.0-cv) + (v2[k]*(1.0-cu) + v3[k]*cu)*cv);
					}
				}

				break;
			case CONTAINER_FACEVARYING:
				v0	=	data + this->fv0*numFloats;
				v1	=	data + this->fv1*numFloats;
				v2	=	data + this->fv2*numFloats;
				v3	=	data + this->fv3*numFloats;
				for (j=0;j<numVertices;j++) {
					const	double	cu	=	u[j];
					const	double	cv	=	v[j];

					for (k=0;k<numFloats;k++) {
						*dest++	=	(float) ((v0[k]*(1.0-cu) + v1[k]*cu)*(1.0-cv) + (v2[k]*(1.0-cu) + v3[k]*cu)*cv);
					}
				}
				break;
			case CONTAINER_CONSTANT:
				if (cVariable->type == TYPE_STRING) {
					if ((cVariable->container == CONTAINER_UNIFORM) || (cVariable->container == CONTAINER_CONSTANT)) {
						const char **srcs	=	(const char**) data;
						const char **dests	=	(const char**) dest;

						assert(isAligned64(srcs));
						assert(isAligned64(dests));
						
						for (j=numFloats;j>0;j--) {
							*dests++	=	*srcs++;
						}
					} else {
						const char **srcs	=	(const char**) data;
						const char **dests	=	(const char**) dest;

						assert(isAligned64(srcs));
						assert(isAligned64(dests));
						
						// premote
						for(j=0;j<numVertices;j++) {
							const char **csrcs	=	srcs;
							for (k=numFloats;k>0;k--) {
								*dests++	=	*csrcs++;
							}
						}
					}
				} else {
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
				}
				break;
			}
		}
	}
}































///////////////////////////////////////////////////////////////////////
// Class				:	CPolygonMesh
// Method				:	CPolygonMesh
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CPolygonMesh::CPolygonMesh(CAttributes *a,CXform *x,CPl *pl,int npoly,int *nholes,int *nvertices,int *vertices) : CObject(a,x) {
	int		i,mVertex;
	float	*P;

	atomicIncrement(&stats.numGprims);

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

	xform->transformBound(bmin,bmax);
	makeBound(bmin,bmax);

	children			=	NULL;

	// Create the synch. object
	osCreateMutex(mutex);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPolygonMesh
// Method				:	~CPolygonMesh
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CPolygonMesh::~CPolygonMesh() {
	atomicDecrement(&stats.numGprims);

	delete pl;
	delete [] nholes;
	delete [] nvertices;
	delete [] vertices;

	// We're done with this object
	osDeleteMutex(mutex);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPolygonMesh
// Method				:	intersect
// Description			:	Intersect with a ray
// Return Value			:	-
// Comments				:
void		CPolygonMesh::intersect(CShadingContext *r,CRay *ray) {

	if (children == NULL)	create(r);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPolygonMesh
// Method				:	dice
// Description			:	Split the mesh
// Return Value			:	-
// Comments				:
void		CPolygonMesh::dice(CShadingContext *r) {

	if (children == NULL)	create(r);

	CObject::dice(r);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPolygonMesh
// Method				:	instantiate
// Description			:	Instanciate the mesh
// Return Value			:	-
// Comments				:
void		CPolygonMesh::instantiate(CAttributes *a,CXform *x,CRendererContext *c) const {
	CXform	*nx		=	new CXform(x);

	nx->concat(xform);	// Concetenate the local xform

	if (a == NULL)	a	=	attributes;

	c->addObject(new CPolygonMesh(a,nx,pl->clone(a),npoly,nholes,nvertices,vertices));
}





























///////////////////////////////////////////////////////////////////////
// Function				:	createTriangle
// Description			:	Actually create the triangle
// Return Value			:	-
// Comments				:
inline	void	createQuad(const int *vindices,const int vi0,const int vi1,const int vi2,const int vi3,CMeshData &data) {
	CPolygonQuad		*cQuad;
	const float			*P				=	data.meshP;
	const float			*vs0			=	P+vindices[vi0]*3;
	const float			*vs1			=	P+vindices[vi1]*3;
	const float			*vs2			=	P+vindices[vi2]*3;
	const float			*vs3			=	P+vindices[vi3]*3;

	// Create the triangle
	cQuad				=	new CPolygonQuad(data.meshAttributes,data.meshXform,data.mesh
		,vindices[vi0]
		,vindices[vi1]
		,vindices[vi3]
		,vindices[vi2]
		,data.meshFacevaryingNumber+vi0
		,data.meshFacevaryingNumber+vi1
		,data.meshFacevaryingNumber+vi3
		,data.meshFacevaryingNumber+vi2
		,data.meshUniformNumber);


	// Add the children into the pool
	cQuad->sibling		=	data.meshChildren;
	data.meshChildren	=	cQuad;
}

///////////////////////////////////////////////////////////////////////
// Function				:	createTriangle
// Description			:	Actually create the triangle
// Return Value			:	-
// Comments				:
inline	void	createTriangle(const int *vindices,const int vi0,const int vi1,const int vi2,CMeshData &data) {
	CPolygonTriangle	*cTriangle;
	const float			*P				=	data.meshP;
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
	cTriangle				=	new CPolygonTriangle(data.meshAttributes,data.meshXform,data.mesh
		,vindices[vi0]
		,vindices[vi1]
		,vindices[vi2]
		,data.meshFacevaryingNumber+vi0
		,data.meshFacevaryingNumber+vi1
		,data.meshFacevaryingNumber+vi2
		,data.meshUniformNumber);


	// Add the children into the pool
	cTriangle->sibling		=	data.meshChildren;
	data.meshChildren		=	cTriangle;
}



#define CLOCKWISE -1
#define COUNTER_CLOCKWISE 1
#define LINE 0


int check_tri_clock_dir(const float *pt1, const float *pt2, const float *pt3) {
  const double test = (((pt2[0] - pt1[0])*(pt3[1] - pt1[1])) - ((pt3[0] - pt1[0])*(pt2[1] - pt1[1]))); 
  if (test > 0) return COUNTER_CLOCKWISE;
  else if(test < 0) return CLOCKWISE;
  else return LINE;
}

bool check_intersect(const float *l1p1, const float *l1p2, const float *l2p1, const float *l2p2) {
   int test1_a, test1_b, test2_a, test2_b;

   test1_a = check_tri_clock_dir(l1p1, l1p2, l2p1);
   test1_b = check_tri_clock_dir(l1p1, l1p2, l2p2);
   if (test1_a != test1_b)
   {
      test2_a = check_tri_clock_dir(l2p1, l2p2, l1p1);
      test2_b = check_tri_clock_dir(l2p1, l2p2, l1p2);
      if (test2_a != test2_b)
      {
         return true;
      }
   }
   return false;
}





///////////////////////////////////////////////////////////////////////
// Function				:	valid
// Description			:	Check if the edge between from and to is inside the polygon
// Return Value			:	TRUE if this is a valid edge
// Comments				:
static	inline	int		valid(const CTriVertex *loop,const CTriVertex *from,const CTriVertex *to) {
	const CTriVertex	*sVertex	=	loop;
	const float			*a			=	loop->xy;
	const float			*b			=	from->xy;
	const float			*c			=	to->xy;
	assert((b[0] != c[0]) || (b[1] != c[1]));

	do{

		// If we are sharing a vertex, keep going
		if (	(sVertex->xy != to->xy) && 
				(sVertex->xy != from->xy) && 
				(sVertex->next->xy != to->xy) && 
				(sVertex->next->xy != from->xy)) {

			const float	*s1	=	sVertex->xy;
			const float	*s2	=	sVertex->next->xy;

			assert((s1[0] != s2[0]) || (s1[1] != s2[1]));
			assert((s1[0] != b[0]) || (s1[1] != b[1]));
			assert((s1[0] != c[0]) || (s1[1] != c[1]));
			assert((s2[0] != b[0]) || (s2[1] != b[1]));
			assert((s2[0] != c[0]) || (s2[1] != c[1]));

			if (	area(b[0],b[1],c[0],c[1],s1[0],s1[1]) *
					area(b[0],b[1],c[0],c[1],s2[0],s2[1]) <= 0) {

				if (	area(s1[0],s1[1],s2[0],s2[1],b[0],b[1]) *
						area(s1[0],s1[1],s2[0],s2[1],c[0],c[1]) <= 0) {

					return FALSE;
				}
			}

			if(	(area(a[0],a[1],s1[0],s1[1],b[0],b[1]) > 0) &&
				(area(b[0],b[1],s1[0],s1[1],c[0],c[1]) > 0) &&
				(area(c[0],c[1],s1[0],s1[1],a[0],a[1]) > 0)	)	return FALSE;

			if(	(area(a[0],a[1],s2[0],s2[1],b[0],b[1]) > 0) &&
				(area(b[0],b[1],s2[0],s2[1],c[0],c[1]) > 0) &&
				(area(c[0],c[1],s2[0],s2[1],a[0],a[1]) > 0)	)	return FALSE;
		}
		
		/*
		const double a1 = area(c[0],c[1],s1[0],s1[1],b[0],b[1]);
		const double a2 = area(c[0],c[1],s1[0],s1[1],a[0],a[1]);
		const double a3 = area(b[0],b[1],s1[0],s1[1],a[0],a[1]);

		// is a point colinear with the suggested cut edge
		if (fabs(a1) < 0) {
			// area is zero, verify if we're within the endpoints of the line
			const double dp = (b[0] -c[0])*(s1[0]-c[0]) + (b[1] -c[1])*(s1[1]-c[1]);
			const double l1 = (b[0] -c[0])*(b[0] -c[0]) + (b[1] -c[1])*(b[1] -c[1]);
			const double l2 = (s1[0]-c[0])*(s1[0]-c[0]) + (s1[1]-c[1])*(s1[1]-c[1]);
			const double l = l1*l2 + C_EPSILON_TINY;

			if (dp > -0 && dp < l) {
				// within the endpoints is invalid
				return FALSE;
			}
		}

		if(	(a1*area(c[0],c[1],a[0],a[1],b[0],b[1]) > 0) &&
			(a2*area(c[0],c[1],b[0],b[1],a[0],a[1]) > 0) &&
			(a3*area(b[0],b[1],c[0],c[1],a[0],a[1]) > 0)) return FALSE;	

			*/
		sVertex = sVertex->next;
	} while(sVertex != loop);
	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// Function				:	orientationCheck
// Description			:	Check the orientation of a loop to make sure it is CW or CCW
// Return Value			:	-
// Comments				:
static	inline	int			orientationCheck(CTriVertex *loop,int cw,CMeshData &data) {
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
		CTriVertex	**vertices	=	(CTriVertex **) ralloc(numVertices*sizeof(CTriVertex *),data.meshContext->threadMemory);
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
inline	void	triangulatePolygon(int nloops,int *nverts,int *vindices,CMeshData &data) {
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
		createTriangle(vindices,0,1,2,data);

		data.meshUniformNumber++;
		data.meshFacevaryingNumber	+=	3;

		return;
	} else if ((nloops == 1) && (nverts[0] == 4)) {

		// Create the quad
		createQuad(vindices,0,1,2,3,data);

		data.meshUniformNumber++;
		data.meshFacevaryingNumber	+=	4;

		return;
	}
#endif

	// Count the number of vertices
	for (numVertices=0,i=0;i<nloops;numVertices+=nverts[i],i++);

	// Compute the polygon normal
	for (P=data.meshP,i=0;i<nverts[0];i++) {
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
		data.meshUniformNumber++;
		data.meshFacevaryingNumber	+=	numVertices;

		return;
	}

	// Allocate the intial memory
	xy			=	(float *)			ralloc(numVertices*2*sizeof(float),data.meshContext->threadMemory);
	loops		=	(CTriVertex **)		ralloc(nloops*sizeof(CTriVertex *),data.meshContext->threadMemory);
	vertices	=	(CTriVertex *)		ralloc(numVertices*sizeof(CTriVertex),data.meshContext->threadMemory);

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
	reverse	=	orientationCheck(loops[0],TRUE,data);
	for (i=1;i<nloops;i++) {
		orientationCheck(loops[i],FALSE,data);
	}

#ifndef OLDSTYLE
	// Are we just creating a triangle ?
	if ((nloops == 1) && (nverts[0] == 3)) {
		cVertex = loops[0];
		pVertex = cVertex->prev;
		nVertex = cVertex->next;
		const int	vi0	=	(int) (nVertex->xy - xy) >> 1;
		const int	vi1	=	(int) (cVertex->xy - xy) >> 1;
		const int	vi2	=	(int) (pVertex->xy - xy) >> 1;

		if (reverse == FALSE) {
			createTriangle(vindices,vi0,vi1,vi2,data);
		} else {
			createTriangle(vindices,vi0,vi2,vi1,data);
		}
		data.meshUniformNumber++;
		data.meshFacevaryingNumber	+=	3;

		return;
	} else if ((nloops == 1) && (nverts[0] == 4)) {
		CTriVertex	*nnVertex;
		cVertex		= loops[0];
		pVertex		= cVertex->prev;
		nnVertex	= pVertex->prev;
		nVertex		= cVertex->next;
		const int	vi0	=	(int) (nVertex->xy - xy) >> 1;
		const int	vi1	=	(int) (cVertex->xy - xy) >> 1;
		const int	vi2	=	(int) (pVertex->xy - xy) >> 1;
		const int	vi3	=	(int) (nnVertex->xy - xy) >> 1;

		if (reverse == FALSE) {
			createQuad(vindices,vi3,vi2,vi1,vi0,data);
		} else {
			createQuad(vindices,vi0,vi1,vi2,vi3,data);
		}
		data.meshUniformNumber++;
		data.meshFacevaryingNumber	+=	4;

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
						CTriVertex	*snVertex	=	(CTriVertex *) ralloc(2*sizeof(CTriVertex),data.meshContext->threadMemory);
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

				// Is the polygon orientation correct?
				if (area(pVertex->xy[0],pVertex->xy[1],cVertex->xy[0],cVertex->xy[1],nVertex->xy[0],nVertex->xy[1]) >= 0) {

					// If we clip this edge, do we intersect another?
					if (valid(cVertex,nVertex,pVertex)) {
						const int	vi0	=	(int) (nVertex->xy - xy) >> 1;
						const int	vi1	=	(int) (cVertex->xy - xy) >> 1;
						const int	vi2	=	(int) (pVertex->xy - xy) >> 1;

						if (reverse == FALSE) {
							createTriangle(vindices,vi0,vi1,vi2,data);
						} else {
							createTriangle(vindices,vi0,vi2,vi1,data);
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
	data.meshUniformNumber++;
	data.meshFacevaryingNumber	+=	numVertices;
}




///////////////////////////////////////////////////////////////////////
// Class				:	CPolygonMesh
// Method				:	triangulate
// Description			:	Triangulate the mesh
// Return Value			:	-
// Comments				:
void				CPolygonMesh::create(CShadingContext *context) {
	osLock(mutex);
	if (children != NULL) {
		osUnlock(mutex);
		return;
	}

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
			error(CODE_BUG,"Unknown container type in polygon mesh\n");
			triangleType	=	0;
			break;
		}
	}


	// Count the number of vertices there is in the mesh
	for (j=0,i=0;i<npoly;i++)	j+=nholes[i];
	for (k=0,i=0;i<j;i++)		k+=nvertices[i];

	for (numVertices=0,i=0;i<k;i++) {
		if (vertices[i] > numVertices)	numVertices	=	vertices[i];
	}
	numVertices++;

	parameters					=	pl->parameterUsage();

	// Fill in the data structure
	CMeshData	data;
	data.meshAttributes			=	attributes;
	data.meshXform				=	xform;
	data.meshPl					=	pl;
	data.meshChildren			=	NULL;
	data.meshP					=	pl->data0;
	data.meshNormal				=	normal;
	data.meshNormalData0		=	normalData0;
	data.meshNormalData1		=	normalData1;
	data.meshTriangleType		=	triangleType;
	data.meshUniformNumber		=	0;
	data.meshFacevaryingNumber	=	0;
	data.mesh					=	this;
	data.meshContext			=	context;

	memBegin(context->threadMemory);
	
	// Triangulate the individual polygons
	for (cnholes=nholes,cvertices=vertices,cnvertices=nvertices,i=0;i<npoly;i++) {
		// Triangulate the current polygon
		triangulatePolygon(cnholes[0],cnvertices,cvertices,data);

		// Advance the holes
		for (j=0;j<cnholes[0];j++) {
			cvertices	+=	cnvertices[j];
		}
		cnvertices	+=	cnholes[0];
		cnholes++;
	}
	
	memEnd(context->threadMemory);

	// Set the children
	setChildren(context,data.meshChildren);
	
	osUnlock(mutex);
}


