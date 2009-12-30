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
//  File				:	subdivisionCreator.cpp
//  Classes				:	CSision
//  Description			:	Implements a subdivision surface
//
////////////////////////////////////////////////////////////////////////
#include <math.h>
#include <string.h>

#include "subdivision.h"
#include "subdivisionCreator.h"
#include "memory.h"
#include "patches.h"
#include "stats.h"
#include "patchgrid.h"
#include "bsplinePatchgrid.h"
#include "shading.h"
#include "error.h"
#include "rendererContext.h"
#include "pl.h"
#include "renderer.h"
#include "ri_config.h"
#include "ri.h"

#undef new

const	unsigned	int	FACE_MOVING				=	2;			// Set if the face is moving
const	unsigned	int	FACE_INTEPOLATEBOUNDARY	=	4;			// Set if we're interpolating the boundary

const	float			bsplineBasis[16]		=	 {
	(float) (-1.0/6.0),	(float) (3.0/6.0),	(float) (-3.0/6.0),	(float)  (1.0/6.0),
	(float) (3.0/6.0),	(float) -(6.0/6.0),	(float) (3.0/6.0),	(float)  (0.0/6.0),
	(float) (-3.0/6.0),	(float) (0.0/6.0),	(float) (3.0/6.0),	(float)  (0.0/6.0),
	(float) (1.0/6.0),	(float) (4.0/6.0),	(float) (1.0/6.0),	(float)  (0.0/6.0)};

class	CSVertex;
class	CSEdge;
class	CSFace;

// This class some transient data we use during the tesselation of the subdivision surface
class CSubdivData {
public:
	int				vertexSize;					// The size of a vertex variable
	int				varyingSize;				// The size of a varying variable
	int				facevaryingSize;			// The size of a facevarying variable
	float			*vertexData;				// The array of vertices
	float			*varyingData;				// The array of varyings
	float			*facevaryingData;			// The array of facevaryings

	int				irregularDepth;				// The depth of subdivision in the case of the creases / etc.
	CSVertex		**irregularVertices;		// The array of irregular vertices
	CSVertex		**irregularRing;			// The ring of irregular vertices about the extraordinary vert
	CVertexData		*vd;
	CAttributes		*currentAttributes;
	CXform			*currentXform;
	int				currentFlags;
	CPl				*parameterList;

	CShadingContext	*context;
};




// Some misc functions for computing the vertex / varying coordinates
inline void	accumVertex(CSubdivData &data,float *dest,const float *src,float mul = 1) {
	for (int i=0;i<data.vertexSize;i++) {
		dest[i]	+=	src[i]*mul;
	}
}

inline void	scaleVertex(CSubdivData &data,float *dest,float mul = 1) {
	for (int i=0;i<data.vertexSize;i++) {
		dest[i]	*=	mul;
	}
}

inline void	initVertex(CSubdivData &data,float *dest) {
	for (int i=0;i<data.vertexSize;i++) {
		dest[i]	=	0;
	}
}

static void	gatherData(CSubdivData &data,int numVertex,CSVertex **vertices,CSVertex **varyings,int uniformNumber,float *&vertex,CParameter *&parameters);


///////////////////////////////////////////////////////////////////////
// Class				:	CSVertex
// Description			:	Encapsulates a subdivision mesh vertex
// Comments				:
class	CSVertex {

	///////////////////////////////////////////////////////////////////////
	// Class				:	CVertexFace
	// Description			:	Encapsulates a face incident on a vertex
	// Comments				:
	class	CVertexFace {
	public:
		CSFace			*face;
		CVertexFace		*next;
	};

	///////////////////////////////////////////////////////////////////////
	// Class				:	CVertexEdge
	// Description			:	Encapsulates an edge incident on a vertex
	// Comments				:
	class	CVertexEdge {
	public:
		CSEdge			*edge;
		CVertexEdge		*next;
	};
public:
					///////////////////////////////////////////////////////////////////////
					// Class				:	CSVertex
					// Method				:	CSVertex
					// Description			:	Ctor
					// Return Value			:	-
					// Comments				:
					CSVertex(CSubdivData &d) : data(d) {
						faces			=	NULL;
						edges			=	NULL;
						valence			=	0;
						fvalence		=	0;
						vertex			=	NULL;
						varying			=	NULL;
						facevarying		=	NULL;
						parentv			=	NULL;
						parente			=	NULL;
						parentf			=	NULL;
						childVertex		=	NULL;
						sharpness		=	0;
					}

	CSubdivData		&data;
	CVertexFace		*faces;							// Incident faces
	CVertexEdge		*edges;							// Incident edges
	int				valence;						// Edge valence
	int				fvalence;						// Face valence i.e., the number of faces incident on the vertex
	float			*vertex;						// The vertex coordinates
	float			*varying,*facevarying;			// The varying coordinates
	CSVertex		*parentv;						// The parent simplex
	CSEdge			*parente;
	CSFace			*parentf;
	CSVertex		*childVertex;					// Child vertex
	float			sharpness;

	void			*operator new(size_t s,CShadingContext *context) {
						return ralloc((int) s,context->threadMemory);
					}

					///////////////////////////////////////////////////////////////////////
					// Class				:	CSVertex
					// Method				:	split
					// Description			:	Split a vertex
					// Return Value			:	-
					// Comments				:
	void			split() {
						if (childVertex == NULL) {
							childVertex					=	new (data.context) CSVertex(data);
							childVertex->parentv		=	this;
							childVertex->sharpness		=	max(sharpness-1,0);
						}
					}


					///////////////////////////////////////////////////////////////////////
					// Class				:	CSVertex
					// Method				:	addFace
					// Description			:	Add an incident face into the vertex
					// Return Value			:	-
					// Comments				:
	void			addFace(CSFace *face) {
						CVertexFace	*cFace	=	(CVertexFace *) ralloc(sizeof(CVertexFace),data.context->threadMemory);

						cFace->face	=	face;
						cFace->next	=	faces;
						faces		=	cFace;

						fvalence++;
					}


					///////////////////////////////////////////////////////////////////////
					// Class				:	CSVertex
					// Method				:	addEdge
					// Description			:	Add an incident edge into the vertex
					// Return Value			:	-
					// Comments				:
	void			addEdge(CSEdge *edge) {
						CVertexEdge	*cEdge	=	(CVertexEdge *) ralloc(sizeof(CVertexEdge),data.context->threadMemory);

						cEdge->edge	=	edge;
						cEdge->next	=	edges;
						edges		=	cEdge;

						valence++;
					}

	CSEdge			*edgeExists(CSVertex *v);
	void			splitIncidentFaces();
	void			sort(CSVertex **,CSEdge *,CSFace *,int);
	void			compute(float *);
	void			computeLimit(float *);
	void			computeVarying(float *,float *);
	void			compute();
	int				funny();
	int				shouldSplit();
};

///////////////////////////////////////////////////////////////////////
// Class				:	CSEdge
// Description			:	Encapsulates an edge
// Comments				:
class	CSEdge {
public:

					///////////////////////////////////////////////////////////////////////
					// Class				:	CSEdge
					// Method				:	CSEdge
					// Description			:	Ctor
					// Return Value			:	-
					// Comments				:
					CSEdge(CSubdivData &d) : data(d) {
						vertices[0]	=	NULL;
						vertices[1]	=	NULL;
						faces[0]	=	NULL;
						faces[1]	=	NULL;
						sharpness	=	0;
						childVertex	=	NULL;
						children[0]	=	NULL;
						children[1]	=	NULL;
					}


	CSubdivData		&data;
	CSVertex		*vertices[2];					// Incident vertices
	CSFace			*faces[2];						// Incident faces
	float			sharpness;						// Edge sharpness
	CSVertex		*childVertex;					// The child vertex
	CSEdge			*children[2];					// The child edges

	void			*operator new(size_t s,CShadingContext *context) {
						return ralloc((int) s,context->threadMemory);
					}

					///////////////////////////////////////////////////////////////////////
					// Class				:	CSEdge
					// Method				:	split
					// Description			:	Split an edge
					// Return Value			:	-
					// Comments				:
	void			split() {
						if (childVertex == NULL) {
							vertices[0]->split();
							vertices[1]->split();

							children[0]					=	new (data.context) CSEdge(data);
							children[1]					=	new (data.context) CSEdge(data);
							childVertex					=	new (data.context) CSVertex(data);
							
							childVertex->parente		=	this;

							children[0]->vertices[0]	=	vertices[0]->childVertex;
							children[0]->vertices[1]	=	childVertex;
							children[0]->sharpness		=	max(sharpness-1,0);

							children[1]->vertices[0]	=	vertices[1]->childVertex;
							children[1]->vertices[1]	=	childVertex;
							children[1]->sharpness		=	max(sharpness-1,0);

							children[0]->vertices[0]->addEdge(children[0]);
							children[0]->vertices[1]->addEdge(children[0]);
							children[1]->vertices[0]->addEdge(children[1]);
							children[1]->vertices[1]->addEdge(children[1]);
						}
					}

					///////////////////////////////////////////////////////////////////////
					// Class				:	CSEdge
					// Method				:	addFace
					// Description			:	Add a face into an edge
					// Return Value			:	-
					// Comments				:
	void			addFace(CSFace *face) {
						if (faces[0] == NULL)	faces[0]	=	face;
						else {
							assert(faces[1] == NULL);
							assert(faces[0] != face);
							faces[1]	=	face;
						}
					}

	void			compute(float *);
	void			computeVarying(float *,float *);
};





///////////////////////////////////////////////////////////////////////
// Class				:	CSFace
// Description			:	Encapsulates a face
// Comments				:
class	CSFace {
public:
					///////////////////////////////////////////////////////////////////////
					// Class				:	CSFace
					// Method				:	CSFace
					// Description			:	Ctor
					// Return Value			:	-
					// Comments				:
					CSFace(CSubdivData &d,int ui) : data(d) {
						numEdges		=	0;
						edges			=	NULL;
						vertices		=	NULL;
						uniformIndex	=	ui;
						children		=	NULL;
						childVertex		=	NULL;
						hole			=	FALSE;
					}

	CSubdivData		&data;
	int				numEdges;
	CSEdge			**edges;
	CSVertex		**vertices;
	int				uniformIndex;
	int				hole;
	CSFace			**children;
	CSVertex		*childVertex;

	void			*operator new(size_t s,CShadingContext *context) {
						return ralloc((int) s,context->threadMemory);
					}

					///////////////////////////////////////////////////////////////////////
					// Class				:	CSFace
					// Method				:	split
					// Description			:	Split the face
					// Return Value			:	-
					// Comments				:
	void			split() {
						if (childVertex == NULL) {
							int			i;
							CSEdge		**newEdges	=	(CSEdge **) ralloc(numEdges*sizeof(CSEdge *),data.context->threadMemory);

							children				=	(CSFace **) ralloc(numEdges*sizeof(CSFace *),data.context->threadMemory);
							childVertex				=	new (data.context) CSVertex(data);
							childVertex->parentf	=	this;

							// Make sure the incident edges are split
							for (i=0;i<numEdges;i++) {
								edges[i]->split();
							}

							// Create the edges connected to the center
							for (i=0;i<numEdges;i++) {
								CSFace	*cFace		=	new (data.context) CSFace(data,uniformIndex);
								CSEdge	*cEdge		=	new (data.context) CSEdge(data);

								cFace->numEdges		=	4;
								cFace->edges		=	(CSEdge **)		ralloc(4*sizeof(CSEdge *),data.context->threadMemory);
								cFace->vertices		=	(CSVertex **)	ralloc(4*sizeof(CSVertex *),data.context->threadMemory);

								cEdge->vertices[0]	=	edges[i]->childVertex;
								cEdge->vertices[1]	=	childVertex;

								childVertex->addEdge(cEdge);
								edges[i]->childVertex->addEdge(cEdge);

								children[i]			=	cFace;
								newEdges[i]			=	cEdge;
							}

							// Create the children faces
							for (i=0;i<numEdges;i++) {
								int	t;

								if (	(vertices[i]->childVertex == edges[i]->children[0]->vertices[0]) || 
										(vertices[i]->childVertex == edges[i]->children[0]->vertices[1])) {
									children[i]->edges[0]	=	edges[i]->children[0];
								} else {
									assert(	(vertices[i]->childVertex == edges[i]->children[1]->vertices[0]) || 
											(vertices[i]->childVertex == edges[i]->children[1]->vertices[1]));
									children[i]->edges[0]	=	edges[i]->children[1];
								}

								t	=	(i-1+numEdges) % numEdges;

								children[i]->edges[1]		=	newEdges[i];
								children[i]->edges[2]		=	newEdges[t];

								if (	(vertices[i]->childVertex == edges[t]->children[0]->vertices[0]) || 
										(vertices[i]->childVertex == edges[t]->children[0]->vertices[1])) {
									children[i]->edges[3]	=	edges[t]->children[0];
								} else {
									assert(	(vertices[i]->childVertex == edges[t]->children[1]->vertices[0]) || 
											(vertices[i]->childVertex == edges[t]->children[1]->vertices[1]));
									children[i]->edges[3]	=	edges[t]->children[1];
								}


								children[i]->vertices[0]	=	vertices[i]->childVertex;
								children[i]->vertices[1]	=	edges[i]->childVertex;
								children[i]->vertices[2]	=	childVertex;
								children[i]->vertices[3]	=	edges[t]->childVertex;

								assert(children[i]->vertices[0] != NULL);
								assert(children[i]->vertices[1] != NULL);
								assert(children[i]->vertices[2] != NULL);
								assert(children[i]->vertices[3] != NULL);
							}

							// Manage the connectivity
							for (i=0;i<numEdges;i++) {
								children[i]->vertices[0]->addFace(children[i]);
								children[i]->vertices[1]->addFace(children[i]);
								children[i]->vertices[2]->addFace(children[i]);
								children[i]->vertices[3]->addFace(children[i]);

								children[i]->edges[0]->addFace(children[i]);
								children[i]->edges[1]->addFace(children[i]);
								children[i]->edges[2]->addFace(children[i]);
								children[i]->edges[3]->addFace(children[i]);
							}
						}
					}


					///////////////////////////////////////////////////////////////////////
					// Class				:	CSFace
					// Method				:	Create
					// Description			:	Split / create children objects
					// Return Value			:	-
					// Comments				:
	void			create(CObject *&children) {
						int	split				=	FALSE;
						int	funny				=	FALSE;
						int funnyBorder			=	FALSE;
						int	i,j;
						int	numExtraordinary	=	0;
						int	extraordinary		=	0;

						if (hole == TRUE)	return;							// If we're a hole, don't create

						if (numEdges != 4) {
							split	=	TRUE;								// If we're not a quad, we must split (vanilla, no funny patch treatment)
						} else {
							// Count the extraordinary vertices
							for (i=0;i<numEdges;i++) {
	
								// was: if (vertices[i]->valence != 4 ) {
								// The following is better as it forces borders to split such that there is
								// one extraordinart vertex which isn't a natural border point
								if ( ((vertices[i]->valence != 4) || (vertices[i]->fvalence != 4)) && (!((vertices[i]->valence == 3) && (vertices[i]->fvalence == 2))) ) {
									numExtraordinary++;
									extraordinary	=	i;
								}
	
								if (vertices[i]->valence != vertices[i]->fvalence) {
									if (!(data.currentFlags & FACE_INTEPOLATEBOUNDARY)) {
										// We're a face adjacent to a boundary and the interpolate boundary flag is not set
										return;
									} else {
										funny		=	TRUE;
										funnyBorder	=	TRUE;
									}
								}
	
								if (vertices[i]->shouldSplit()) split	=	TRUE;
							}
	
	
							// was: if (numExtraordinary > 1) {
							// prefer to split if possible to enforce above 
							// constraint on extraordinary border vertices								
							if (numExtraordinary > 1) {				// If we have more than one ordinary, we must split
								split = TRUE;
								funny = FALSE;
							}
							
							if (numExtraordinary == 1) {
								if (vertices[extraordinary]->valence < 3) funny = TRUE;
							}
						}
						
						if ((split == FALSE) || (funny == TRUE)) {
							// Check if we're a "funny" quad. i.e., have crease edges
							for (i=0;i<numEdges;i++) {
								if (vertices[i]->funny() == TRUE) {
									funny	=	TRUE;
									break;
								}
							}

							if (funny == FALSE) {

								// We're not a funny patch
								// We are either:
								//		1 - A regular patch - Create a bi-cubic patch
								//		2 - An extraordinary patch - Create an extraordinary patch
								if (numExtraordinary == 1) {
									// This is an extraordinary patch
									CSVertex	**v,*va[4];
									int			N		=	vertices[extraordinary]->valence;
									int			K		=	2*N + 8;
									CSVertex	**ring	=	(CSVertex **) alloca(2*N*sizeof(CSVertex *));	// Holds the ring around the extraordinary vertex (transient)
									CSVertex	*ringt[8];
									float		*vertex;
									CParameter	*parameters;

									v		=	(CSVertex **) alloca((K+1)*sizeof(CSVertex *));				// Holds the vertices that effect the current patch (transient)

									// First, deal with the vertices around the extraordinary vertex
									vertices[(extraordinary + 0) & 3]->sort(ring,edges[(extraordinary + 0) & 3],this,2*N);
									for (i=0;i<(2*N);i++) {
										v[i + 2]	=	ring[(i + 2*N - 2) % (2*N)];
									}

									vertices[(extraordinary + 1) & 3]->sort(ringt,edges[(extraordinary + 1) & 3],this,8);
									v[2*N+8]	=	ringt[5];
									v[2*N+7]	=	ringt[6];
									v[2*N+6]	=	ringt[7];

									vertices[(extraordinary + 2) & 3]->sort(ringt,edges[(extraordinary + 2) & 3],this,8);
									v[2*N+2]	=	ringt[5];

									vertices[(extraordinary + 3) & 3]->sort(ringt,edges[(extraordinary + 3) & 3],this,8);
									v[2*N+5]	=	ringt[5];
									v[2*N+4]	=	ringt[4];
									v[2*N+3]	=	ringt[3];

									v[1]		=	vertices[(extraordinary + 0) & 3];
									assert(v[4]	==	vertices[(extraordinary + 1) & 3]);
									assert(v[5]	==	vertices[(extraordinary + 2) & 3]);
									assert(v[6]	==	vertices[(extraordinary + 3) & 3]);

									va[0]		=	v[1];
									va[1]		=	v[4];
									va[2]		=	v[6];
									va[3]		=	v[5];

									// Gather the data
									gatherData(data,K,v+1,va,uniformIndex,vertex,parameters);

									// Create the primitive
									CObject	*nObject	=	new CSubdivision(data.currentAttributes,data.currentXform,data.vd,parameters,N,0.0f,0.0f,1.0f,1.0f,vertex);
									nObject->sibling	=	children;
									children			=	nObject;
								} else {
									// This is an ordinary patch
									CSVertex	*v[16],*va[4];
									CSVertex	*ring[8];
									float		*vertex;
									CParameter	*parameters;

									// Gather the regular neighborhood
									vertices[0]->sort(ring,edges[0],this,8);
									v[0*4+0]	=	ring[5];
									v[0*4+1]	=	ring[6];
									v[0*4+2]	=	ring[7];
									v[1*4+0]	=	ring[4];
									v[2*4+0]	=	ring[3];

									vertices[1]->sort(ring,edges[1],this,8);
									v[0*4+3]	=	ring[5];
									v[1*4+3]	=	ring[6];
									v[2*4+3]	=	ring[7];

									vertices[2]->sort(ring,edges[2],this,8);
									v[3*4+1]	=	ring[7];
									v[3*4+2]	=	ring[6];
									v[3*4+3]	=	ring[5];

									vertices[3]->sort(ring,edges[3],this,8);
									v[3*4+0]	=	ring[5];

									v[1*4+1]	=	vertices[(extraordinary+0)&3];
									v[1*4+2]	=	vertices[(extraordinary+1)&3];
									v[2*4+2]	=	vertices[(extraordinary+2)&3];
									v[2*4+1]	=	vertices[(extraordinary+3)&3];

									va[0]		=	v[1*4+1];
									va[1]		=	v[1*4+2];
									va[2]		=	v[2*4+1];
									va[3]		=	v[2*4+2];

									// Gather the data
									gatherData(data,16,v,va,uniformIndex,vertex,parameters);

									// Create the primitive
									CObject	*nObject	=	new CBicubicPatch(data.currentAttributes,data.currentXform,data.vd,parameters,0,0,1,1,vertex,bsplineBasis,bsplineBasis);
									nObject->sibling	=	children;
									children			=	nObject;
								}
							} else {
								// Damn, we're a funny patch, deal with it
								int			nv		=	(1 << data.irregularDepth) + 1;
								float		*vertex;
								CSVertex	*va[4];
								CParameter	*parameters;

								data.irregularVertices	=	(CSVertex **) ralloc(sizeof(CSVertex *)*(nv+2)*(nv+2),data.context->threadMemory);
								for (i=0;i<(nv+2)*(nv+2);i++) {
									data.irregularVertices[i] = NULL;
								}
								
								if ( (numExtraordinary > 0) && (vertices[(extraordinary+0)&3]->valence >= 3)) {
									data.irregularRing	=	(CSVertex **) ralloc(sizeof(CSVertex *)*(vertices[(extraordinary+0)&3]->valence*2),data.context->threadMemory);
								}
								
								// Create irregular patch
								unconditionalSplit(data.irregularDepth,0,0,vertices[extraordinary]);
								
								va[0]	=	vertices[(extraordinary+0)&3];
								va[1]	=	vertices[(extraordinary+1)&3];
								va[2]	=	vertices[(extraordinary+3)&3];
								va[3]	=	vertices[(extraordinary+2)&3];
								
								if ( funnyBorder == TRUE ) {
									// We're at the border so it'll have to be a bilinear patch
									
									
									// Note: At the border, we may not have found all the corner vertices - this is particularly true
									// if only the corner is at the border.  Set these to the nearest point to ensure
									// gather will succeed (we don't use these points anyway)
									
									if (data.irregularVertices[0*(nv+2)+0] == NULL)				data.irregularVertices[0*(nv+2)+0]				= data.irregularVertices[1*(nv+2)+1];
									if (data.irregularVertices[0*(nv+2)+(nv+1)] == NULL)		data.irregularVertices[0*(nv+2)+(nv+1)]			= data.irregularVertices[1*(nv+2)+(nv)];
									if (data.irregularVertices[(nv+1)*(nv+2)+(nv+1)] == NULL)	data.irregularVertices[(nv+1)*(nv+2)+(nv+1)]	= data.irregularVertices[(nv)*(nv+2)+(nv)];
									if (data.irregularVertices[(nv+1)*(nv+2)+0] == NULL)		data.irregularVertices[(nv+1)*(nv+2)+0]			= data.irregularVertices[(nv)*(nv+2)+1];
																		
									// now we gather the grid from neighbors on patches where it exists
									// pass all available data to the patch grid and flags to indicate which
									// edges are valid.  This is used to create symmetric normals
									int bTop = (edges[(extraordinary+0)&3]->faces[0] == NULL) || (edges[(extraordinary+0)&3]->faces[1] == NULL);
									int bRgt = (edges[(extraordinary+1)&3]->faces[0] == NULL) || (edges[(extraordinary+1)&3]->faces[1] == NULL);
									int bBot = (edges[(extraordinary+2)&3]->faces[0] == NULL) || (edges[(extraordinary+2)&3]->faces[1] == NULL);
									int bLft = (edges[(extraordinary+3)&3]->faces[0] == NULL) || (edges[(extraordinary+3)&3]->faces[1] == NULL);
									
									gatherData(data,(nv+2)*(nv+2),data.irregularVertices,va,uniformIndex,vertex,parameters);
										
									// Create the primitive
									CObject	*nObject	=	new CPatchGrid(data.currentAttributes,data.currentXform,data.vd,parameters,nv,nv,bTop,bRgt,bBot,bLft,vertex);
									nObject->sibling	=	children;
									children			=	nObject;
								} else {
									if ( (numExtraordinary > 0) && (vertices[(extraordinary+0)&3]->valence >= 3)) {
										// We're have an extraordinary patch
										// divide main patch into two side strips which are adjacent
										// to the extraordinary pathc and a smaller grid
										
										int			N				=	vertices[extraordinary]->valence;
										int			K				=	2*N + 8;
										CSVertex	**v				=	(CSVertex **) ralloc((K+1)*sizeof(CSVertex *),data.context->threadMemory);	
										CSVertex** strip1Vertices	=	(CSVertex**) ralloc(sizeof(CSVertex*)*4*(nv+1),data.context->threadMemory);
										CSVertex** strip2Vertices	=	(CSVertex**) ralloc(sizeof(CSVertex*)*4*(nv+1),data.context->threadMemory);
										CSVertex** patchVertices	=	(CSVertex**) ralloc(sizeof(CSVertex*)*(nv+1)*(nv+1),data.context->threadMemory);
										const float mult			=	1.0f/(nv-1);
										
										for (i=0;i<(nv+1);i++) {
											strip1Vertices[4*i+0] = data.irregularVertices[(i+1)*(nv+2)+0];
											strip1Vertices[4*i+1] = data.irregularVertices[(i+1)*(nv+2)+1];
											strip1Vertices[4*i+2] = data.irregularVertices[(i+1)*(nv+2)+2];
											strip1Vertices[4*i+3] = data.irregularVertices[(i+1)*(nv+2)+3];
																						
											strip2Vertices[0*(nv+1)+i] = data.irregularVertices[0*(nv+2)+1+i];
											strip2Vertices[1*(nv+1)+i] = data.irregularVertices[1*(nv+2)+1+i];
											strip2Vertices[2*(nv+1)+i] = data.irregularVertices[2*(nv+2)+1+i];
											strip2Vertices[3*(nv+1)+i] = data.irregularVertices[3*(nv+2)+1+i];
											
											for (j=0;j<(nv+1);j++) {
												patchVertices[i*(nv+1)+j] = data.irregularVertices[(i+1)*(nv+2)+j+1];
											}
										}
										
										CObject	*nObject;

										// 'left' strip
										gatherData(data,(nv+1)*(4),strip1Vertices,va,uniformIndex,vertex,parameters);
										nObject				=	new CBSplinePatchGrid(data.currentAttributes,data.currentXform,data.vd,parameters,4,nv+1,0.0f,mult,mult,(nv-2)*mult,vertex);
										nObject->sibling	=	children;
										children			=	nObject;
										
										// 'top' strip
										gatherData(data,(4)*(nv+1),strip2Vertices,va,uniformIndex,vertex,parameters);
										nObject				=	new CBSplinePatchGrid(data.currentAttributes,data.currentXform,data.vd,parameters,nv+1,4,mult,0.0f,(nv-2)*mult,mult,vertex);
										nObject->sibling	=	children;
										children			=	nObject;
										
										// main grid
										gatherData(data,(nv+1)*(nv+1),patchVertices,va,uniformIndex,vertex,parameters);
										nObject				=	new CBSplinePatchGrid(data.currentAttributes,data.currentXform,data.vd,parameters,nv+1,nv+1,mult,mult,(nv-2)*mult,(nv-2)*mult,vertex);
										nObject->sibling	=	children;
										children			=	nObject;
										
										// extraordinary patch
										for (i=0;i<(2*N);i++) {
											v[i + 2]	=	data.irregularRing[(i + 2*N - 2) % (2*N)];
										}
										
										v[1]		= data.irregularVertices[1*(nv+2)+1];
										
										v[2*N+6]	= data.irregularVertices[2*(nv+2)+3];
										v[2*N+7]	= data.irregularVertices[1*(nv+2)+3];
										v[2*N+8]	= data.irregularVertices[0*(nv+2)+3];
										
										v[2*N+5]	= data.irregularVertices[3*(nv+2)+0];
										v[2*N+4]	= data.irregularVertices[3*(nv+2)+1];
										v[2*N+3]	= data.irregularVertices[3*(nv+2)+2];
										v[2*N+2]	= data.irregularVertices[3*(nv+2)+3];
																				
										// Gather the data
										gatherData(data,K,v+1,va,uniformIndex,vertex,parameters);
																		
										// Create the primitive
										nObject				=	new CSubdivision(data.currentAttributes,data.currentXform,data.vd,parameters,N,0.0f,0.0f,mult,mult,vertex);
										nObject->sibling	=	children;
										children			=	nObject;
									} else {
										// No extraordinary patch, use the a bicubic b-spline patch
										
										// Gather the data
										gatherData(data,(nv+2)*(nv+2),data.irregularVertices,va,uniformIndex,vertex,parameters);
										
										// Create the primitive
										CObject	*nObject	=	new CBSplinePatchGrid(data.currentAttributes,data.currentXform,data.vd,parameters,nv+2,nv+2,0.0f,0.0f,1.0f,1.0f,vertex);
										nObject->sibling	=	children;
										children			=	nObject;
									}
								}
							}
						} else {
							for (i=0;i<numEdges;i++) {
								vertices[i]->splitIncidentFaces();
							}

							for (i=0;i<numEdges;i++) {
								this->children[i]->create(children);
							}
						}
					}

					///////////////////////////////////////////////////////////////////////
					// Class				:	CSFace
					// Method				:	unconditionalSplit
					// Description			:	Unconditionally split this quad until a predefined depth for table computation
					// Return Value			:	-
					// Comments				:
	void			unconditionalSplit(int depth,int x,int y,CSVertex *org) {
						if (depth > 0) {
							int	i;

							for (i=0;i<numEdges;i++) {
								vertices[i]->splitIncidentFaces();
							}

							for (i=0;i<4;i++) {
								if (vertices[i] == org) {
									children[(i+0) & 3]->unconditionalSplit(depth-1,(x << 1),(y << 1),				vertices[(i+0) & 3]->childVertex);
									children[(i+1) & 3]->unconditionalSplit(depth-1,(x << 1) + 1,(y << 1),			edges[(i+0) & 3]->childVertex);
									children[(i+2) & 3]->unconditionalSplit(depth-1,(x << 1) + 1,(y << 1) + 1,		childVertex);
									children[(i+3) & 3]->unconditionalSplit(depth-1,(x << 1),(y << 1) + 1,			edges[(i+3) & 3]->childVertex);
									break;
								}
							}

							assert(i != 4);
						} else {
							int	i;

							for (i=0;i<4;i++) {
								if (vertices[i] == org) {
									char l = (x==0);
									char r = (x==(1 << data.irregularDepth)-1);
									char t = (y==0);
									char b = (y==(1 << data.irregularDepth)-1);
									char ml=0,mr=0,mt=0,mb=0;
									
									data.irregularVertices[(y+1) * ((1 << data.irregularDepth) + 3) + x + 1]		=	vertices[(i + 0) & 3];
									data.irregularVertices[(y+1) * ((1 << data.irregularDepth) + 3) + x + 2]		=	vertices[(i + 1) & 3];
									data.irregularVertices[(y+2) * ((1 << data.irregularDepth) + 3) + x + 2]		=	vertices[(i + 2) & 3];
									data.irregularVertices[(y+2) * ((1 << data.irregularDepth) + 3) + x + 1]		=	vertices[(i + 3) & 3];
									
									// If we're not at an edge, the rest is not relevant
									if (!(l||r||t||b)) break;
									
									// Deal with the edges
									//  either we fetch vertices from a neighboring face or duplicate the edge
									if (l) {
										CSVertex *v1	=	data.irregularVertices[(y+1) * ((1 << data.irregularDepth) + 3) + x + 1];
										CSVertex *v2	= 	data.irregularVertices[(y+2) * ((1 << data.irregularDepth) + 3) + x + 1];
										ml = findEdgeVertices((i+3)&3,(i+3)&3,v1,v2);
										data.irregularVertices[(y+1) * ((1 << data.irregularDepth) + 3) + x] = v1;
										data.irregularVertices[(y+2) * ((1 << data.irregularDepth) + 3) + x] = v2;
									}
									if (r) {
										CSVertex *v1	=	data.irregularVertices[(y+1) * ((1 << data.irregularDepth) + 3) + x + 2];
										CSVertex *v2	=	data.irregularVertices[(y+2) * ((1 << data.irregularDepth) + 3) + x + 2];
										mr = findEdgeVertices((i+1)&3,(i+2)&3,v1,v2);
										data.irregularVertices[(y+1) * ((1 << data.irregularDepth) + 3) + x + 3] = v1;
										data.irregularVertices[(y+2) * ((1 << data.irregularDepth) + 3) + x + 3] = v2;
									}
									if (t) {
										CSVertex *v1	=	data.irregularVertices[(y+1) * ((1 << data.irregularDepth) + 3) + x + 1];
										CSVertex *v2	=	data.irregularVertices[(y+1) * ((1 << data.irregularDepth) + 3) + x + 2];
										mt = findEdgeVertices((i+0)&3,(i+1)&3,v1,v2);
										data.irregularVertices[(y) * ((1 << data.irregularDepth) + 3) + x + 1] = v1;
										data.irregularVertices[(y) * ((1 << data.irregularDepth) + 3) + x + 2] = v2;
									}
									if (b) {
										CSVertex *v1	=	data.irregularVertices[(y+2) * ((1 << data.irregularDepth) + 3) + x + 1];
										CSVertex *v2	=	data.irregularVertices[(y+2) * ((1 << data.irregularDepth) + 3) + x + 2];
										mb = findEdgeVertices((i+2)&3,(i+2)&3,v1,v2);
										data.irregularVertices[(y+3) * ((1 << data.irregularDepth) + 3) + x + 1] = v1;
										data.irregularVertices[(y+3) * ((1 << data.irregularDepth) + 3) + x + 2] = v2;
									}
									
									// Deal with the corners
									//  find the corner from an corner-adjacent face if possible, or 
									//  duplicate a neighboring point
									// Note: there's no more than 1 extraordinary vertex here, and its
									//  at vertices[(i+0)&3] in (0,0) if there is such a point
									
									if (l&&t) {
										if (((vertices[(i+0)&3]->valence != 4) && (vertices[(i+0)&3]->valence >= 3) && (vertices[(i+0)&3]->valence==vertices[(i+0)&3]->fvalence))) {
											// We're an extraordinary point and not at the border
											vertices[(i+0)&3]->sort(data.irregularRing,edges[(i+0)&3],this,2*vertices[(i+0)&3]->valence);
										} else {
											CSVertex *v = data.irregularVertices[(y+mt) * ((1 << data.irregularDepth) + 3) + x + ml];
											if(!findCornerVertex((i+0)&3,(i+0)&3,v))
												findCornerVertex((i+3)&3,(i+0)&3,v);
											data.irregularVertices[(y) * ((1 << data.irregularDepth) + 3) + x] = v;
										}
									}
									if (r&&t) {
										CSVertex *v = data.irregularVertices[(y+mt) * ((1 << data.irregularDepth) + 3) + x + 3 - mr];
										if(!findCornerVertex((i+1)&3,(i+1)&3,v))
											findCornerVertex((i+0)&3,(i+1)&3,v);
										data.irregularVertices[(y) * ((1 << data.irregularDepth) + 3) + x + 3] = v;
									}
									if (r&&b) {
										CSVertex *v = data.irregularVertices[(y+3-mb) * ((1 << data.irregularDepth) + 3) + x + 3 - mr];
										if(!findCornerVertex((i+2)&3,(i+2)&3,v))
											findCornerVertex((i+1)&3,(i+2)&3,v);
										data.irregularVertices[(y+3) * ((1 << data.irregularDepth) + 3) + x + 3] = v;
									}
									if (l&&b) {
										CSVertex *v = data.irregularVertices[(y+3-mb) * ((1 << data.irregularDepth) + 3) + x + ml];
										if(!findCornerVertex((i+3)&3,(i+3)&3,v))
											findCornerVertex((i+2)&3,(i+3)&3,v);
										data.irregularVertices[(y+3) * ((1 << data.irregularDepth) + 3) + x] = v;
									}
									
									break;
								}
							}

							assert(i != 4);
						}
					}

	void			compute(float *);
	void			computeVarying(float *,float *);
	char			findEdgeVertices(int,int,CSVertex*&,CSVertex*&);
	int				findCornerVertex(int,int,CSVertex*&);
};










/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Misc functions related to subdivision surface vertices
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////
// Class				:	CSVertex
// Method				:	splitIncidentFaces
// Description			:	Split all the incident faces
// Return Value			:	-
// Comments				:
void		CSVertex::splitIncidentFaces() {
	CVertexFace	*cFace;

	for (cFace=faces;cFace!=NULL;cFace=cFace->next) {
		cFace->face->split();
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSVertex
// Method				:	edgeExists
// Description			:	Figure out if an edge has already been inserted
// Return Value			:	-
// Comments				:
CSEdge		*CSVertex::edgeExists(CSVertex *v) {
	CVertexEdge	*cEdge;
	
	for (cEdge=edges;cEdge!=NULL;cEdge=cEdge->next) {
		if (	(cEdge->edge->vertices[0] == v) ||
				(cEdge->edge->vertices[1] == v))	return cEdge->edge;
	}

	return NULL;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CSVertex
// Method				:	sort
// Description			:	Sort 1 ring neighborhood
// Return Value			:	-
// Comments				:
void		CSVertex::sort(CSVertex **v,CSEdge *cEdge,CSFace *cFace,int exp) {
	CSEdge	*estart	=	cEdge;
	int		i;

	do {
		if (cEdge->vertices[0] == this)	*v++	=	cEdge->vertices[1];
		else							*v++	=	cEdge->vertices[0];

		exp--;

		assert(cFace->numEdges == 4);

		for (i=0;i<4;i++) {
			if (cFace->vertices[i] == this)	{
				*v++	=	cFace->vertices[(i+2) & 3];
				break;
			}
		}

		exp--;

		assert(i != 4);

		cEdge	=	cFace->edges[(i+1) & 3];
		if (!((cEdge->vertices[0] == this) || (cEdge->vertices[1] == this)))	cEdge	=	cFace->edges[(i+3) & 3];

		if (cEdge->faces[0] == cFace)	cFace	=	cEdge->faces[1];
		else							cFace	=	cEdge->faces[0];
		
	} while(cEdge != estart && exp);

	assert(exp == 0);
}



///////////////////////////////////////////////////////////////////////
// Class				:	CSVertex
// Method				:	funny
// Description			:	Figure out if there's something funny in the neighborhood of the vertex
// Return Value			:	TRUE if funny
// Comments				:
int		CSVertex::funny() {
	CVertexEdge	*cEdge;

	if (fvalence != valence) {
		assert(data.currentFlags & FACE_INTEPOLATEBOUNDARY);
		return TRUE;
	}

	for (cEdge=edges;cEdge!=NULL;cEdge=cEdge->next) {
		if (cEdge->edge->sharpness > 0)	return TRUE;
		if (sharpness > 0) return TRUE;

		if (cEdge->edge->faces[1] == NULL) {

			return TRUE;
		}
	}

	return FALSE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSVertex
// Method				:	shouldSplit
// Description			:	TRUE if there is a non-quad incident face
// Return Value			:
// Comments				:
int		CSVertex::shouldSplit() {
	CVertexFace	*cFace;

	for (cFace=faces;cFace!=NULL;cFace=cFace->next) {
		if (cFace->face->numEdges != 4) return TRUE;
	}

	return FALSE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSFace
// Method				:	findEdgeVertices
// Description			:	get the vertex pair bordering an edge
// Return Value			:	-
// Comments				:
char	CSFace::findEdgeVertices(int eOrg,int vOrg,CSVertex* &v1,CSVertex* &v2) {
	CSEdge		*cEdge = edges[eOrg];
	CSVertex	*cVert = vertices[vOrg];
	CSFace		*cFace = NULL;
	int			i;
	
	if (cEdge->faces[0] == this)	cFace = cEdge->faces[1];
	else							cFace = cEdge->faces[0];
	
	if (cFace != NULL){
		for (i=0;i<4;i++) {
			if (cFace->edges[i] == cEdge) {
				if (cFace->vertices[i] == cVert) {
					v1 = cFace->vertices[(i + 2) & 3];
					v2 = cFace->vertices[(i + 3) & 3];
				} else {
					v1 = cFace->vertices[(i + 3) & 3];
					v2 = cFace->vertices[(i + 2) & 3];
					//assert(cFace->vertices[(i+1)&3] != cVert);
				}
				break;
			}
		}
		assert(i!=4);
	} else {
		return 1;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSFace
// Method				:	findCornerVertex
// Description			:	find the vertex corner-opposite by edge walking
// Return Value			:	-
// Comments				:
int		CSFace::findCornerVertex(int eOrg,int vOrg,CSVertex *&v) {
	CSEdge		*cEdge = edges[eOrg];
	CSVertex	*cVert = vertices[vOrg];
	CSFace		*cFace = this;
	int i,j;
	
	for (j=1;j>=0;j--){
		if (cEdge->faces[0] == cFace)	cFace = cEdge->faces[1];
		else							cFace = cEdge->faces[0];
		
		if (cFace == NULL) break;
		
		for (i=0;i<4;i++){
			if (cFace->edges[i] == cEdge) {
				if (cFace->vertices[(i+0)&3] == cVert) {
					cEdge = cFace->edges[(i+3)&3];
					if (!j && (cEdge->faces[0] != this) && (cEdge->faces[1] != this) ) {
						v = cFace->vertices[(i+2)&3];
						return TRUE;
					}
				} else {
					cEdge = cFace->edges[(i+1)&3];
					assert(cFace->vertices[(i+1)&3] == cVert);
					if (!j && (cEdge->faces[0] != this) && (cEdge->faces[1] != this) ) {
						v = cFace->vertices[(i+3)&3];
						return TRUE;
					}
				}
				break;
			}
		}
		assert(i!=4);
	}
	return FALSE;
}















/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Subdivision rules implementation
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////












///////////////////////////////////////////////////////////////////////
// Class				:	CSVertex
// Method				:	compute
// Description			:	Compute the vertex / varying
// Return Value			:	-
// Comments				:
void	CSVertex::compute() {
	assert(vertex == NULL);

	vertex	=	(float *) ralloc(data.vertexSize*sizeof(float),data.context->threadMemory);

	if (parentv != NULL)		parentv->compute(vertex);
	else if (parente != NULL)	parente->compute(vertex);
	else if (parentf != NULL)	parentf->compute(vertex);
	else {
		assert(FALSE);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSVertex
// Method				:	compute
// Description			:	Compute the vertex / varying
// Return Value			:	-
// Comments				:
void	CSVertex::compute(float *vertex) {
	CVertexEdge	*cEdge;
	CVertexFace	*cFace;
	float		*tvertex;
	float		sharpness;
	int			numSharp;

	if (this->vertex == NULL)	compute();

	tvertex			=	(float *) ralloc(data.vertexSize*sizeof(float),data.context->threadMemory);
	
	for (numSharp=0,sharpness=0,cEdge=edges;cEdge!=NULL;cEdge=cEdge->next) {
		if (cEdge->edge->sharpness > 0) {
			sharpness	+=	cEdge->edge->sharpness;
			numSharp++;
		}
	}
	
	if ((numSharp > 2) || (valence == 2)) {	// We're a corner vertex
		memcpy(vertex,this->vertex,data.vertexSize*sizeof(float));
	} else {											// We're not a corner vertex
		float	*sharpVertex	=	(float *) ralloc(data.vertexSize*sizeof(float),data.context->threadMemory);
		float	*smoothVertex	=	(float *) ralloc(data.vertexSize*sizeof(float),data.context->threadMemory);

		sharpness	/=	(float) numSharp;

		// Compute the smooth rule
		initVertex(data,smoothVertex);
		initVertex(data,sharpVertex);

		for (cEdge=edges;cEdge!=NULL;cEdge=cEdge->next) {
			CSVertex	*oVertex;

			if (cEdge->edge->vertices[0] == this) oVertex	=	cEdge->edge->vertices[1];
			else {
				assert(cEdge->edge->vertices[1] == this);
				oVertex	=	cEdge->edge->vertices[0];
			}

			if (oVertex->vertex == NULL)	oVertex->compute();

			accumVertex(data,smoothVertex,oVertex->vertex);

			if (cEdge->edge->sharpness > 0) {
				accumVertex(data,sharpVertex,oVertex->vertex);
			}
		}

		for (cFace=faces;cFace!=NULL;cFace=cFace->next) {
			cFace->face->compute(tvertex);
			accumVertex(data,smoothVertex,tvertex);
		}

		scaleVertex(data,smoothVertex, 1 / (float) (valence*valence));
		accumVertex(data,smoothVertex,this->vertex,(valence - 2) / (float) valence);

		scaleVertex(data,sharpVertex, 1.0 / 8.0);
		accumVertex(data,sharpVertex,this->vertex,6.0 / 8.0);

		if (numSharp == 2) {
			// We're a crease vertex
			if (sharpness >= 1) {
				memcpy(vertex,sharpVertex,data.vertexSize*sizeof(float));
			} else if (sharpness <= 0) {
				memcpy(vertex,smoothVertex,data.vertexSize*sizeof(float));
			} else {
				initVertex(data,vertex);
				accumVertex(data,vertex,smoothVertex,1-sharpness);
				accumVertex(data,vertex,sharpVertex,sharpness);
			}
		} else {
			// We're a dart or a non-crease vertex
			memcpy(vertex,smoothVertex,data.vertexSize*sizeof(float));
		}
	}
	
	if (this->sharpness >= 1) {			// sharp corner rule
		memcpy(vertex,this->vertex,data.vertexSize*sizeof(float));
	}
	else if (this->sharpness > 0) {		// smooth corner rule
		scaleVertex(data,vertex,1 - this->sharpness);
		accumVertex(data,vertex,this->vertex,this->sharpness);
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CSVertex
// Method				:	compute
// Description			:	Compute the vertex / varying
// Return Value			:	-
// Comments				:
void	CSVertex::computeVarying(float *varying,float *facevarying) {
	if		(parentv != NULL)	parentv->computeVarying(varying,facevarying);
	else if (parente != NULL)	parente->computeVarying(varying,facevarying);
	else if (parentf != NULL)	parentf->computeVarying(varying,facevarying);
	else {
		if (this->varying != NULL) {
			memcpy(varying,this->varying,sizeof(float)*data.varyingSize);
		}

		if (this->facevarying != NULL) {
			memcpy(facevarying,this->facevarying,sizeof(float)*data.facevaryingSize);
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSVertex
// Method				:	computeLimit
// Description			:	Compute the vertex / varying
// Return Value			:	-
// Comments				:
void	CSVertex::computeLimit(float *vertex) {
	CVertexEdge	*cEdge;
	CVertexFace	*cFace;
	float		*tvertex;
	float		sharpness;
	int			numSharp;

	if (this->vertex == NULL)	compute();

	tvertex			=	(float *) ralloc(data.vertexSize*sizeof(float),data.context->threadMemory);

	for (numSharp=0,sharpness=0,cEdge=edges;cEdge!=NULL;cEdge=cEdge->next) {
		if (cEdge->edge->sharpness > 0) {
			sharpness	+=	cEdge->edge->sharpness;
			numSharp++;
		}
	}

	if ((numSharp > 2) || (valence == 2)) {	// We're a corner vertex
		memcpy(vertex,this->vertex,data.vertexSize*sizeof(float));
	} else {											// We're not a corner vertex
		float	*sharpVertex	=	(float *) ralloc(data.vertexSize*sizeof(float),data.context->threadMemory);
		float	*smoothVertex	=	(float *) ralloc(data.vertexSize*sizeof(float),data.context->threadMemory);

		sharpness	/=	(float) numSharp;

		// Compute the smooth rule
		initVertex(data,smoothVertex);
		initVertex(data,sharpVertex);

		for (cEdge=edges;cEdge!=NULL;cEdge=cEdge->next) {
			accumVertex(data,smoothVertex,tvertex,4);

			if (cEdge->edge->sharpness > 0) {
				accumVertex(data,sharpVertex,tvertex);
			}
		}

		for (cFace=faces;cFace!=NULL;cFace=cFace->next) {
			accumVertex(data,smoothVertex,tvertex);
		}

		accumVertex(data,smoothVertex,this->vertex,(float) (valence*valence));
		scaleVertex(data,smoothVertex, 1 / (float) (valence*(valence+5)));

		scaleVertex(data,sharpVertex, 1.0 / 4.0);
		accumVertex(data,sharpVertex,this->vertex,1.0 / 2.0);

		if (numSharp == 2) {
			// We're a crease vertex
			if (sharpness >= 1) {
				memcpy(vertex,sharpVertex,data.vertexSize*sizeof(float));
			} else if (sharpness <= 0) {
				memcpy(vertex,smoothVertex,data.vertexSize*sizeof(float));
			} else {
				initVertex(data,vertex);
				accumVertex(data,vertex,smoothVertex,1-sharpness);
				accumVertex(data,vertex,sharpVertex,sharpness);
			}
		} else {
			// We're a dart or a non-crease vertex
			memcpy(vertex,smoothVertex,data.vertexSize*sizeof(float));
		}
	}
	
	if (this->sharpness >= 1) {			// sharp corner rule
		memcpy(vertex,this->vertex,data.vertexSize*sizeof(float));
	}
	else if (this->sharpness > 0) {		// smooth corner rule
		scaleVertex(data,vertex,1 - this->sharpness);
		accumVertex(data,vertex,this->vertex,this->sharpness);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSEdge
// Method				:	compute
// Description			:	Edge subdivision rule
// Return Value			:	-
// Comments				:
void	CSEdge::compute(float *vertex) {
	float	*tvertex;
	float	*smoothVertex,*sharpVertex;

	smoothVertex	=	(float *) ralloc(data.vertexSize*sizeof(float),data.context->threadMemory);
	sharpVertex		=	(float *) ralloc(data.vertexSize*sizeof(float),data.context->threadMemory);
	tvertex			=	(float *) ralloc(data.vertexSize*sizeof(float),data.context->threadMemory);

	if (vertices[0]->vertex == NULL)	vertices[0]->compute();
	if (vertices[1]->vertex == NULL)	vertices[1]->compute();

	if ((sharpness > 0) || (faces[1] == NULL)) {	// Have to compute the sharp vertex
		initVertex(data,sharpVertex);
		accumVertex(data,sharpVertex,vertices[0]->vertex);
		accumVertex(data,sharpVertex,vertices[1]->vertex);
		scaleVertex(data,sharpVertex,0.5f);
	}

	if ((sharpness < 1) && (faces[1] != NULL)) {	// Have to compute the smooth vertex
		faces[0]->compute(smoothVertex);
		faces[1]->compute(tvertex);
		accumVertex(data,smoothVertex,tvertex);
		accumVertex(data,smoothVertex,vertices[0]->vertex);
		accumVertex(data,smoothVertex,vertices[1]->vertex);
		scaleVertex(data,smoothVertex,1 / (float) 4);
	}

	if ((sharpness >= 1) || (faces[1] == NULL))			memcpy(vertex,sharpVertex,data.vertexSize*sizeof(float));
	else if (sharpness <= 0)							memcpy(vertex,smoothVertex,data.vertexSize*sizeof(float));
	else {
		initVertex(data,vertex);
		accumVertex(data,vertex,smoothVertex,(1-sharpness));
		accumVertex(data,vertex,sharpVertex,sharpness);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSEdge
// Method				:	computeVarying
// Description			:	Edge subdivision rule
// Return Value			:	-
// Comments				:
void	CSEdge::computeVarying(float *varying,float *facevarying) {
	float	*varying1,*facevarying1;
	int		i;

	varying1		=	(float *) ralloc(sizeof(float)*data.varyingSize,data.context->threadMemory);
	facevarying1	=	(float *) ralloc(sizeof(float)*data.facevaryingSize,data.context->threadMemory);

	vertices[0]->computeVarying(varying,facevarying);
	vertices[1]->computeVarying(varying1,facevarying1);

	for (i=0;i<data.varyingSize;i++) {
		varying[i]	=	(varying[i] + varying1[i])*0.5f;
	}

	for (i=0;i<data.facevaryingSize;i++) {
		facevarying[i]	=	(facevarying[i] + facevarying1[i])*0.5f;
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSFace
// Method				:	compute
// Description			:	Face subdivision rule
// Return Value			:	-
// Comments				:
void	CSFace::compute(float *vertex) {
	int	i;

	initVertex(data,vertex);

	for (i=0;i<numEdges;i++) {
		if (vertices[i]->vertex == NULL)	vertices[i]->compute();

		accumVertex(data,vertex,vertices[i]->vertex);
	}

	scaleVertex(data,vertex,1 / (float) numEdges);
}



///////////////////////////////////////////////////////////////////////
// Class				:	CSFace
// Method				:	computeVarying
// Description			:	Face subdivision rule
// Return Value			:	-
// Comments				:
void	CSFace::computeVarying(float *varying,float *facevarying) {
	float		*varying1,*facevarying1;
	int			i,j;
	const float	scale	=	1 / (float) numEdges;

	varying1		=	(float *) ralloc(sizeof(float)*data.varyingSize,data.context->threadMemory);
	facevarying1	=	(float *) ralloc(sizeof(float)*data.facevaryingSize,data.context->threadMemory);

	for (i=0;i<data.varyingSize;i++) {
		varying[i]	=	0;
	}

	for (i=0;i<data.facevaryingSize;i++) {
		facevarying[i]	=	0;
	}

	for (j=0;j<numEdges;j++) {
		vertices[j]->computeVarying(varying1,facevarying1);

		for (i=0;i<data.varyingSize;i++) {
			varying[i]	+=	varying1[i];
		}

		for (i=0;i<data.facevaryingSize;i++) {
			facevarying[i]	+=	facevarying1[i];
		}
	}

	for (i=0;i<data.varyingSize;i++) {
		varying[i]	*=	scale;
	}

	for (i=0;i<data.facevaryingSize;i++) {
		facevarying[i]	*=	scale;
	}
}

















































static void	gatherData(CSubdivData &data,int numVertex,CSVertex **vertices,CSVertex **varyings,int uniformNumber,float *&vertex,CParameter *&parameters) {
	int			i;
	float		*varyingsT,*facevaryingsT;

	assert(data.vertexSize > 0);

	vertex		=	(float *) ralloc(data.vertexSize*numVertex*sizeof(float),data.context->threadMemory);

	for (i=0;i<numVertex;i++) {
		if (vertices[i]->vertex == NULL)	vertices[i]->compute();
		
		memcpy(vertex+i*data.vertexSize,vertices[i]->vertex,sizeof(float)*data.vertexSize);
	}


	varyingsT		=	(float *) ralloc(data.varyingSize*4*sizeof(float),data.context->threadMemory);
	facevaryingsT	=	(float *) ralloc(data.facevaryingSize*4*sizeof(float),data.context->threadMemory);

	for (i=0;i<4;i++) {
		varyings[i]->computeVarying(varyingsT + i*data.varyingSize,facevaryingsT + i*data.facevaryingSize);
	}

	parameters		=	data.parameterList->uniform(uniformNumber,NULL);
	parameters		=	data.parameterList->varying(	varyingsT+0*data.varyingSize,
														varyingsT+1*data.varyingSize,
														varyingsT+2*data.varyingSize,
														varyingsT+3*data.varyingSize,parameters);
	parameters		=	data.parameterList->facevarying(	facevaryingsT+0*data.facevaryingSize,
															facevaryingsT+1*data.facevaryingSize,
															facevaryingsT+2*data.facevaryingSize,
															facevaryingsT+3*data.facevaryingSize,parameters);
}















///////////////////////////////////////////////////////////////////////
// Class				:	CSubdivMesh
// Method				:	CSubdivMesh
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CSubdivMesh::CSubdivMesh(CAttributes *a,CXform *x,CPl *c,int numFaces,int *numVerticesPerFace,int *vertexIndices,int ntags,const char **tags,int *nargs,int *intargs,float *floatargs) : CObject(a,x) {
	int			i,j,ias,fas;
	const float	*P;

	atomicIncrement(&stats.numGprims);

	this->pl					=	c;
	this->numFaces				=	numFaces;

	// Count the number of faces / vertices
	for (i=0,j=0;i<numFaces;j+=numVerticesPerFace[i],i++);

	for (numVertices=-1,i=0;i<j;i++) {
		if (vertexIndices[i] > numVertices)	numVertices	=	vertexIndices[i];
	}
	numVertices++;

	// Create a fresh copy of the parameters
	this->numVerticesPerFace	=	new int[numFaces];		memcpy(this->numVerticesPerFace,numVerticesPerFace,sizeof(int)*numFaces);
	this->vertexIndices			=	new int[j];				memcpy(this->vertexIndices,vertexIndices,sizeof(int)*j);
	this->ntags					=	ntags;
	this->tags					=	NULL;
	this->nargs					=	NULL;
	this->intargs				=	NULL;
	this->floatargs				=	NULL;

	if (ntags > 0) {
		this->tags				=	new char*[ntags];
		this->nargs				=	new int[ntags*2];		memcpy(this->nargs,nargs,sizeof(int)*ntags*2);

		for (ias=0,fas=0,i=0;i<ntags;i++) {
			this->tags[i]		=	strdup(tags[i]);
			ias					+=	nargs[i*2];
			fas					+=	nargs[i*2+1];
		}

		if (ias > 0)	this->intargs			=	new int[ias];			memcpy(this->intargs,intargs,ias*sizeof(int));
		if (fas > 0)	this->floatargs			=	new float[fas];			memcpy(this->floatargs,floatargs,fas*sizeof(float));
	}

	// Compute the bounding box
	initv(bmin,C_INFINITY);
	initv(bmax,-C_INFINITY);
	for (P=pl->data0,i=0;i<numVertices;i++,P+=3) {
		addBox(bmin,bmax,P);
	}

	if (pl->data1 != NULL) {
		for (P=pl->data1,i=0;i<numVertices;i++,P+=3) {
			addBox(bmin,bmax,P);
		}
	}

	xform->transformBound(bmin,bmax);
	makeBound(bmin,bmax);
	
	// Create the synch. object
	osCreateMutex(mutex);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSubdivMesh
// Method				:	~CSubdivMesh
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CSubdivMesh::~CSubdivMesh() {
	int	i;

	atomicDecrement(&stats.numGprims);

	delete pl;
	delete [] numVerticesPerFace;
	delete [] vertexIndices;
	
	if (ntags > 0) {
		for (i=0;i<ntags;i++) {
			free(tags[i]);
		}
		delete [] tags;
		delete [] nargs;
		if (intargs != NULL)	delete [] intargs;
		if (floatargs != NULL)	delete [] floatargs;
	}
	
	// Delete the synch. object
	osDeleteMutex(mutex);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CSubdivMesh
// Method				:	intersect
// Description			:	Intersect the thing
// Return Value			:	-
// Comments				:
void		CSubdivMesh::intersect(CShadingContext *rasterizer,CRay *cRay) {

	if (children == NULL)	create(rasterizer);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CSubdivMesh
// Method				:	dice
// Description			:	Dice the primitive
// Return Value			:	-
// Comments				:
void		CSubdivMesh::dice(CShadingContext *rasterizer) {

	if (children == NULL)	create(rasterizer);

	CObject	*cObject,*nObject;
	for (cObject=children;cObject!=NULL;cObject=nObject) {
		nObject	=	cObject->sibling;
		
		cObject->attach();
		
		rasterizer->drawObject(cObject);
		
		cObject->detach();
	}
}
							
///////////////////////////////////////////////////////////////////////
// Class				:	CSubdivMesh
// Method				:	instantiate
// Description			:	Clone the primitive
// Return Value			:	-
// Comments				:
void		CSubdivMesh::instantiate(CAttributes *a,CXform *x,CRendererContext *c) const {
	CXform	*nx		=	new CXform(x);

	nx->concat(xform);	// Concetenate the local xform

	if (a == NULL)	a	=	attributes;

	c->addObject(new CSubdivMesh(a,nx,pl->clone(a),numFaces,numVerticesPerFace,vertexIndices,ntags,(const char **) tags,nargs,intargs,floatargs));
}


///////////////////////////////////////////////////////////////////////
// Class				:	CSubdivMesh
// Method				:	split
// Description			:	Split this into smaller primitives
// Return Value			:	-
// Comments				:
void		CSubdivMesh::create(CShadingContext *context) {
	int			i;
	int			j,k;
	CSFace		**faces;
	CSVertex	**vertices;
	int			*cnargs;
	int			*cintargs;
	float		*cfloatargs;
	int			*cvertexIndex;
	CSubdivData	data;
	CObject		*allChildren;

	osLock(mutex);
	if (children != NULL) {
		osUnlock(mutex);
		return;
	}

	memBegin(context->threadMemory);

	// Transform the core
	pl->transform(xform);

	data.vertexSize			=	0;
	data.varyingSize		=	0;
	data.facevaryingSize	=	0;
	data.vertexData			=	NULL;
	data.varyingData		=	NULL;
	data.facevaryingData	=	NULL;

	data.irregularDepth		=	5;
	data.irregularVertices	=	NULL;
	data.irregularRing		=	NULL;
	data.vd					=	NULL;
	data.currentAttributes	=	NULL;
	data.currentXform		=	NULL;
	data.currentFlags		=	0;
	data.parameterList		=	NULL;

	data.context			=	context;

	data.vd					=	pl->vertexData();
	data.currentFlags		=	0;
	data.currentAttributes	=	this->attributes;
	data.currentXform		=	this->xform;
	data.parameterList		=	this->pl;

	// Collect the misc data
	data.vertexData			=	NULL;			pl->collect(data.vertexSize,data.vertexData,CONTAINER_VERTEX,context->threadMemory);
	data.varyingData		=	NULL;			pl->collect(data.varyingSize,data.varyingData,CONTAINER_VARYING,context->threadMemory);
	data.facevaryingData	=	NULL;			pl->collect(data.facevaryingSize,data.facevaryingData,CONTAINER_FACEVARYING,context->threadMemory);

	faces					=	(CSFace **)		ralloc(numFaces*sizeof(CSFace *),data.context->threadMemory);
	vertices				=	(CSVertex **)	ralloc(numVertices*sizeof(CSVertex *),data.context->threadMemory);

	// Create the vertices and copy the vertex / varying data over
	for (i=0;i<numVertices;i++)	{
		const float	*src			=	data.vertexData + i*data.vertexSize;
		float		*dest;
		int			k;

		vertices[i]					=	new (data.context) CSVertex(data);
		dest = vertices[i]->vertex	=	(float *) ralloc(data.vertexSize*sizeof(float),data.context->threadMemory);

		for (k=0;k<data.vertexSize;k++)	*dest++	=	*src++;
	}

	if (data.varyingData != NULL) {
		for (i=0;i<numVertices;i++) {
			vertices[i]->varying	=	data.varyingData + i*data.varyingSize;
		}
	}

	// Create the faces
	for (i=0;i<numFaces;i++) {
		faces[i]				=	new (data.context) CSFace(data,i);
	}
	
	// Manage the connectivity
	for (i=0,cvertexIndex=vertexIndices;i<numFaces;i++) {
		CSFace	*cFace			=	faces[i];
		int		numEdges		=	numVerticesPerFace[i];
		cFace->numEdges			=	numEdges;
		cFace->vertices			=	(CSVertex **)	ralloc(numEdges*sizeof(CSVertex *),data.context->threadMemory);
		cFace->edges			=	(CSEdge **)		ralloc(numEdges*sizeof(CSEdge *),data.context->threadMemory);

		// Set the vertices belonging to a face
		for (j=0;j<numEdges;j++) {
			cFace->vertices[j]	=	vertices[*cvertexIndex++];
		}

		// Figure out the edges
		for (j=0;j<numEdges;j++) {
			CSEdge	*cEdge;

			if ((cEdge = cFace->vertices[j]->edgeExists(cFace->vertices[(j+1) % numEdges])) == NULL) {
				cEdge				=	new (data.context) CSEdge(data);
				cEdge->vertices[0]	=	cFace->vertices[j];
				cEdge->vertices[1]	=	cFace->vertices[(j+1) % numEdges];
				cEdge->vertices[0]->addEdge(cEdge);
				cEdge->vertices[1]->addEdge(cEdge);
			}

			cFace->edges[j]	=	cEdge;
		}

		for (j=0;j<cFace->numEdges;j++) {
			cFace->vertices[j]->addFace(cFace);
			cFace->edges[j]->addFace(cFace);
		}
	}
	
	// Process the tags
	for (i=0,cnargs=nargs,cintargs=intargs,cfloatargs=floatargs;i<ntags;i++) {
		if (strcmp(tags[i],RI_HOLE) == 0) {
			if (cnargs[1] != 0)	error(CODE_RANGE,"Hole takes no floating point arguments\n");
			for (j=0;j<cnargs[0];j++) {
				faces[cintargs[j]]->hole	=	TRUE;
			}
		} else if (strcmp(tags[i],RI_CREASE) == 0) {
			for (j=0;j<cnargs[0]-1;j++) {
				CSVertex	*v0	=	vertices[cintargs[j]];
				CSVertex	*v1	=	vertices[cintargs[j+1]];
				CSEdge		*cEdge;

				cEdge			=	v0->edgeExists(v1);

				if (cEdge != NULL) {
					cEdge->sharpness	=	min(cfloatargs[0],10);
				} else {
					error(CODE_RANGE,"The edge between vertices %d-%d not found\n",cintargs[j],cintargs[j+1]);
				}
			}
			if (cnargs[1] != 1) {
				error(CODE_RANGE,"Creases expect exactly 1 float argument\n");
			}
		} else if (strcmp(tags[i],RI_INTERPOLATEBOUNDARY) == 0) {
			data.currentFlags	|=	FACE_INTEPOLATEBOUNDARY;
		} else if (strcmp(tags[i],RI_CORNER) == 0) {
			if (cnargs[1] == cnargs[0]) {
				for (j=0;j<cnargs[0];j++) {
					vertices[cintargs[j]]->sharpness = cfloatargs[j];
				}
			} else if (cnargs[1] == 1) {
				for (j=0;j<cnargs[0];j++) {
					vertices[cintargs[j]]->sharpness = cfloatargs[0];
				}
			} else {
				error(CODE_RANGE,"Corner has 1 or n float arguments\n");
			}
		} else {
			error(CODE_BADTOKEN,"Unknown subdivision tag: \"%s\"\n",tags[i]);
		}

		cintargs	+=	cnargs[0];
		cfloatargs	+=	cnargs[1];
		cnargs		+=	2;
	}
	
	// Add sharp creases when we've got an interpolateboundary tag
	// Note: corner in the literature refers to v.valence == 2,
	// whereas the spec overloads corners as tags to mean sharp vertices
	if (data.currentFlags & FACE_INTEPOLATEBOUNDARY) {
		for (i=0;i<numFaces;i++) {
			CSFace	*cFace			=	faces[i];
			int		numEdges		=	numVerticesPerFace[i];
	
			// Figure out the edges
			for (j=0;j<numEdges;j++) {
				CSEdge	*cEdge = cFace->edges[j];
	
				if (cEdge->faces[1] == NULL) {
					cEdge->sharpness = 10;
				}
			}
		}
	}
		
	// Finalize the faces
	allChildren	=	NULL;
	for (k=0,i=0;i<numFaces;i++) {

		// Set the facevarying parameters
		for (j=0;j<faces[i]->numEdges;j++) {
			faces[i]->vertices[j]->facevarying	=	data.facevaryingData + (k+j)*data.facevaryingSize;
			
			// Check for degenerate faces
			const int val	= faces[i]->vertices[j]->valence;
			const int fval	= faces[i]->vertices[j]->fvalence;
			if((val == 1))					{ warning(CODE_CONSISTENCY,"Subdivision mesh has hanging vertex");			k    +=    faces[i]->numEdges;	goto skipFace; }
			if((val == 2) && (fval != 1)) 	{ warning(CODE_CONSISTENCY,"Subdivision mesh is degenerate (face %d)\n",i); k    +=    faces[i]->numEdges;	goto skipFace; }
			if((val >= 3) && (fval > val)) 	{ warning(CODE_CONSISTENCY,"Subdivision mesh is degenerate (face %d)\n",i); k    +=    faces[i]->numEdges;	goto skipFace; }
		}

		k	+=	j;

		// Finally, create the face
		faces[i]->create(allChildren);
		
		skipFace:
			;		// intentionally empty
	}

	// Re-claim the memory
	memEnd(context->threadMemory);

	// Set the children objects
	setChildren(context,allChildren);

	if (i==0) warning(CODE_CONSISTENCY,"Subdivision mesh is trivial (skipped)\n");
	
	osUnlock(mutex);
}

