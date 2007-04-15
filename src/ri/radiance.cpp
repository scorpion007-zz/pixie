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
//  File				:	radiance.cpp
//  Classes				:	CRadianceCache
//  Description			:	This class holds a radiance cache
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "common/global.h"
#include "common/algebra.h"
#include "radiance.h"
#include "object.h"
#include "random.h"
#include "harmonics.h"
#include "stats.h"
#include "photonMap.h"
#include "memory.h"
#include "linsys.h"
#include "texture.h"
#include "random.h"

#define	SINTABLE_SIZE		1000		// The size of the alpha / sin(alpha) table
#define	LOCAL_LOOKUP		10			// The number of nearby local samples to look at
#define	TRIANGLE_TO_ALPHA	0.5			// triangle size / alpha
//#define DEBUG_PRINT

#ifdef DEBUG_PRINT
static	FILE	*out;					// Debugging output
#endif

// These two arrays are used to hold plusOne[i] = (i+1) % 3 and minusOne[i] = (i-1) % 3
static	int		plusOne[3]				=	{1,2,0};
static	int		plusOnes[6][5]			=	{
												{0,0,0,0,0},
												{0,0,0,0,0},
												{0,0,0,0,0},
												{1,2,0,0,0},
												{1,2,3,0,0},
												{1,2,3,4,0}	};




///////////////////////////////////////////////////////////////////////
// Class				:	CTriTon
// Description			:	This holds a triangle
// Comments				:
class	CTriTon : public CTon {
public:
	float		corners[3*3];
	vector		P,N,C;
	CAttributes	*attributes;
	int			nSides;
};










///////////////////////////////////////////////////////////////////////
// Class				:	CTriangleHash
// Description			:	A hash that holds the contribution that comes from faraway geometry
// Comments				:
class	CTriangleHash : public CMap<CTriTon> {
public:
				CTriangleHash(float a) : CMap<CTriTon>() {	
					int		i;

					// Precompute the sin table
					alpha						=	a;
					sinTable					=	new float[SINTABLE_SIZE+2];
					for (i=0;i<SINTABLE_SIZE;i++) {
						double	angle			=	acos(2*(i / (double) (SINTABLE_SIZE-1)) - 1);
						sinTable[i+1]			=	(float) (angle / sin(angle));
					}
					sinTable[0]					=	sinTable[1];
					sinTable[SINTABLE_SIZE+1]	=	1;
					sinTable[SINTABLE_SIZE]		=	1;
				}

				~CTriangleHash() {	
					delete [] sinTable;
				}

	void		lookup(float *C,const float *P,const float *N) {
					int					numFound	=	0;
					int					maxFound	=	500;
					CTriTon				**indices	=	(CTriTon **)	alloca((maxFound+1)*sizeof(CTriTon *)); 
					float				*distances	=	(float	*)		alloca((maxFound+1)*sizeof(float)); 
					CLookup				l;
					float				totalWeight;
					vector				D;
					float				dist;
					float				formFactor,dP;
					const float			d			=	-dotvv(P,N);
					int					i;
					float				cornerDist[3];
					int					cornerStat[3];
					float				corners[6*3];
					const float			*src;
					int					numCorners;
					float				*cCorner;
					const int			*modTable;


					distances[0]	=	alpha*alpha;
					dP				=	alpha;

					l.maxFound		=	maxFound;
					l.numFound		=	0;
					movvv(l.P,P);
					initv(l.N,0);
					l.gotHeap		=	FALSE;
					l.indices		=	(const CTriTon **) indices;
					l.distances		=	distances;

					CMap<CTriTon>::lookup(&l,1);

					numFound		=	l.numFound;

					totalWeight		=	0;
					C[0]			=	0;
					C[1]			=	0;
					C[2]			=	0;
					C[3]			=	0;

					for (int ii=1;ii<=numFound;ii++) {
						CTriTon		*cTriangle		=	indices[ii];

						subvv(D,P,cTriangle->P);
						dist		=	distances[ii];
						assert(dist <= (alpha*alpha));

						//if (cTriangle->nSides == 1)
						if (dotvv(D,cTriangle->N)	<= 0.001)			continue;	// The query point is behind the triangle

						if (dotvv(cTriangle->N,N)	>= (float) 0.99)	continue;	// The triangle can not have a big form factor

						// Compute the distances of the triangle corners to the query plane
						cornerStat[0]	=	(cornerDist[0]	=	dotvv(cTriangle->corners+0,N) + d) >= 0;
						cornerStat[1]	=	(cornerDist[1]	=	dotvv(cTriangle->corners+3,N) + d) >= 0;
						cornerStat[2]	=	(cornerDist[2]	=	dotvv(cTriangle->corners+6,N) + d) >= 0;

						// If the triangle is below the horizon, skip
						if ((cornerStat[0] | cornerStat[1] | cornerStat[2]) == 0)	continue;

						// Check if we need to clip the triangle
						if (cornerStat[0] & cornerStat[1] & cornerStat[2]) {
							// No
							numCorners	=	3;
							subvv(corners+0,cTriangle->corners+0,P);	normalizev(corners+0);
							subvv(corners+3,cTriangle->corners+3,P);	normalizev(corners+3);
							subvv(corners+6,cTriangle->corners+6,P);	normalizev(corners+6);
						} else {
							// Yes							
							numCorners	=	0;
							cCorner		=	corners;
							src			=	cTriangle->corners;

							// Perform the actual clipping
							for (i=0;i<3;i++) {
								if (cornerStat[i]) {
									subvv(cCorner,src+i*3,P);
									normalizev(cCorner);
									cCorner	+=	3;
									numCorners++;

									if (cornerStat[plusOne[i]]) {
										// Nothing to output
									} else {
										const float	*in		=	src + i*3;
										const float	*out	=	src + plusOne[i]*3;
										const float	t		=	cornerDist[i] / (cornerDist[i] - cornerDist[plusOne[i]]);

										assert(t >= -0.1);
										assert(t <= 1.1);

										interpolatev(cCorner,in,out,t);
										subvv(cCorner,P);
										normalizev(cCorner);
										cCorner	+=3;
										numCorners++;
									}
								} else {
									if (cornerStat[plusOne[i]]) {
										const float	*in		=	src + plusOne[i]*3;
										const float	*out	=	src + i*3;
										const float	t		=	cornerDist[plusOne[i]] / (cornerDist[plusOne[i]] - cornerDist[i]);

										assert(t >= -0.1);
										assert(t <= 1.1);

										interpolatev(cCorner,in,out,t);
										subvv(cCorner,P);
										normalizev(cCorner);
										cCorner	+=3;
										numCorners++;
									} else {
										// Nothing to output
									}
								}
							}

							// Sanity check
							assert(cornerStat[0] | cornerStat[1] | cornerStat[2]);
						}

						// Sanity check, we're clipping a triangle against a plane, can not have more than 5 corners
						assert(numCorners <= 5);

						// Compute the form factor
						formFactor	=	0;
						modTable	=	plusOnes[numCorners];
						for (i=0;i<numCorners;i++) {
							const float	*c0		=	corners + i*3;
							const float	*c1		=	corners + modTable[i]*3;
							const float	alpha	=	dotvv(c0,c1);
							const int	index	=	(int) (SINTABLE_SIZE*(alpha + 1)*0.5);

							// Check if the function we're approximating is smooth or not
							if ((index < 10) || (index >= (SINTABLE_SIZE - 10))) {
								// The function is not smooth in this range, compute it the brute force way
								const float	alphat	=	(float) acos(max(min(alpha,1),-1));
								vector		R;

								crossvv(R,c1,c0);
								if (dotvv(R,R) > C_EPSILON)	{
									normalizev(R);
								} else {
									if (alphat > 2) {
										movvv(R,N);
									} else {
										initv(R,0,0,0);
									}
								}

								mulvf(R,alphat);
								formFactor			+=	dotvv(R,N);
							} else {
								// The function is smooth, lookup the table
								const float	alphat	=	sinTable[index];
								vector		R;

								crossvv(R,c1,c0);
								mulvf(R,alphat);
								formFactor			+=	dotvv(R,N);
							}
						}

						// This if should never evaluate to TRUE, however because of floating point errors, it might
						//if (formFactor <= 0)	continue;
						formFactor	=	absf(formFactor);
						formFactor	*=	1 / (float) (2*C_PI);				

						// Have we looked up the photonmap for this triangle before?
						if (cTriangle->attributes != NULL) {
							CPhotonMap	*globalMap;

							// No, perform a photonmap lookup
							if ((globalMap = cTriangle->attributes->globalMap) != NULL) {
								stats.numIndirectDiffusePhotonmapLookups++;

								globalMap->lookup(cTriangle->C,cTriangle->P,cTriangle->N,cTriangle->attributes->photonEstimator);
								mulvv(cTriangle->C,cTriangle->attributes->surfaceColor);
							} else {
								movvv(cTriangle->C,cTriangle->attributes->surfaceColor);
							}

							assert(dotvv(cTriangle->C,cTriangle->C) >= 0);

							// Detach the triangle from the attributes
							cTriangle->attributes	=	NULL;
						}

						C[0]		+=	formFactor*cTriangle->C[0];
						C[1]		+=	formFactor*cTriangle->C[1];
						C[2]		+=	formFactor*cTriangle->C[2];
						C[3]		+=	formFactor;
						dist		=	sqrtf(dist);
						dP			=	min(dP,dist);
					}

					C[4]		=	dP;

				}

private:
	float		*sinTable;
	float		alpha;
};



///////////////////////////////////////////////////////////////////////
// Class				:	CRadianceCache
// Method				:	CRadianceCache
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CRadianceCache::CRadianceCache(const char *name,unsigned int mode,const float *bmin,const float *bmax,FILE *in,CArray<CTriangle *> *t) : CCache(name,mode) {
	int			i;

#ifdef DEBUG_PRINT
	out					=	fopen("test.txt","w");
#endif

	hash				=	new CDepository;
	memory				=	new CMemStack;
	shadingPoints		=	NULL;
	numShadingPoints	=	0;
	root				=	NULL;
	maxDepth			=	0;
	hierarchy			=	h;
	tris				=	t;
	triangleHash		=	NULL;
	osCreateMutex(mutex);

	// Figure out whether we're in read / write mode
	if (in == NULL) {
		// Create the root node for the sample hierarchy
		root						=	(CRadianceNode *) memory->alloc(sizeof(CRadianceNode));
		addvv(root->center,bmin,bmax);
		mulvf(root->center,(float) 0.5);
		root->side					=	max(max(bmax[0] - bmin[0],bmax[1] - bmin[1]),bmax[2] - bmin[2]);
		root->samples				=	NULL;
		for (i=0;i<8;i++) root->children[i]	=	NULL;
		maxDepth					=	1;
	} else {
		// Read the samples
		hash->read(in);

		// Read the harmonics
		fread(&maxDepth,1,sizeof(int),in);
		root	=	readNode(in);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRadianceCache
// Method				:	~CRadianceCache
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CRadianceCache::~CRadianceCache() {
	osDeleteMutex(mutex);

	// Are we writing into a file ?
	if (flags & CACHE_WRITE) {
		FILE	*out	=	ropen(name,"wb",fileGatherCache);

		if (out != NULL) {
			// Write the samples
			hash->balance();
			hash->write(out);

			// Write the harmonics
			fwrite(&maxDepth,1,sizeof(int),out);
			writeNode(out,root);

			fclose(out);
		}
	}

	// Ditch the memory
	delete hash;
	delete memory;
	if (triangleHash	!= NULL) delete triangleHash;

#ifdef DEBUG_PRINT
	fclose(out);
#endif
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRadianceCache
// Method				:	lookup
// Description			:	Lookup da radiance cache
// Return Value			:	-
// Comments				:
void		CRadianceCache::lookup(float *C,const float *P,const float *N,const CGlobalIllumLookup *lookup) {
	// Are we writing ?
	if (flags & CACHE_WRITE) {
		osLock(mutex);

		CShadingPoint		*cPoint			=	(CShadingPoint *) memory->alloc(sizeof(CShadingPoint));
		CDepositorySample	*cSample;
		float				Cl[5];

		// Save the shading point first for the harmonic computations
		movvv(cPoint->P,P);
		movvv(cPoint->N,N);
		cPoint->depSample	=	hash->numPhotons+1;
		cPoint->next		=	shadingPoints;
		shadingPoints		=	cPoint;
		numShadingPoints++;

		// If this is the first call, do the necessary precomputation
		if (tris != NULL) {
			alpha				=	lookup->localThreshold;
			numRaysPerCluster	=	lookup->numSamples;
			bias				=	lookup->bias;
			movvv(backgroundColor,lookup->backgroundColor);
			prepareTriangles();
			assert(tris == NULL);
		}

		// Lookup da local contribution
		triangleHash->lookup(Cl,P,N);

		// Save the result
		cSample				=	hash->store(P,N);
		cSample->C[0]		=	Cl[0];
		cSample->C[1]		=	Cl[1];
		cSample->C[2]		=	Cl[2];
		cSample->C[3]		=	Cl[3];

		// Return the local contribution
		C[0]				=	Cl[0];
		C[1]				=	Cl[1];
		C[2]				=	Cl[2];
		C[3]				=	Cl[3];

		osUnlock(mutex);
	} else {
		// Just lookup the hash
		hash->lookup(C,P,N);
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRadianceCache
// Method				:	cachesample
// Description			:	Check the existance of a sample in the cache
// Return Value			:	-
// Comments				:
void		CRadianceCache::cachesample(float *C,const float *P,const float *N,float dP) {
	CRadianceNode		*cNode;
	CRadianceNode		**stack,**stackBase;
	CRadianceHarmonic	*cHarmonic;
	int					i;
	vector				Pn;

	stack			=	stackBase	=	(CRadianceNode **) alloca(maxDepth*sizeof(CRadianceNode *)*8);
	*stack++		=	root;

	normalizev(Pn,P);
	while(stack > stackBase) {
		cNode	=	*(--stack);

		// Iterate over the samples
		for (cHarmonic=cNode->samples;cHarmonic!=NULL;cHarmonic=cHarmonic->next) {
			float	d	=	dotvv(Pn,cHarmonic->P);
			float	q	=	dotvv(cHarmonic->P,cHarmonic->P) - d*d;

			if (q < dP*dP) {
				C[0]	=	1;
				return;
			}
		}

		// Check the children
		for (i=0;i<8;i++) {
			CRadianceNode	*tNode	=	cNode->children[i];

			if (tNode != NULL) {
				const	float	tSide	=	tNode->side+dP;

				if (	((tNode->center[0] + tSide) > P[0])	&&
						((tNode->center[1] + tSide) > P[1])	&&
						((tNode->center[2] + tSide) > P[2])	&&
						((tNode->center[0] - tSide) < P[0])	&&
						((tNode->center[1] - tSide) < P[1])	&&
						((tNode->center[2] - tSide) < P[2])) {
					*stack++	=	tNode;
				}
			}
		}
	}

	C[0]	=	0;
}



///////////////////////////////////////////////////////////////////////
// Class				:	CRadianceCache
// Method				:	finalize
// Description			:	Finalize da cache
// Return Value			:	-
// Comments				:
void		CRadianceCache::finalize(const CGlobalIllumLookup *l) {
	// Do we have samples waiting to be processed ?
	if (numShadingPoints > 0) {
		// Create an array of shading points
		CShadingPoint		**samples		=	(CShadingPoint **) memory->alloc(numShadingPoints*sizeof(CShadingPoint *));
		int					i;
		CShadingPoint		*cSample;
		CTextureLookup		*texLookup = NULL;
		
		if(l->environment != NULL){
			texLookup = (CTextureLookup*) alloca(sizeof(CTextureLookup));
			texLookup->filter		= RiGaussianFilter;
			texLookup->blur			= 0;
			texLookup->swidth		= 1;
			texLookup->twidth		= 1;
			texLookup->numSamples	= 1;
			texLookup->channel		= 0;
			texLookup->fill			= 0;
			texLookup->shadowBias	= l->bias;
			texLookup->maxDist		= C_INFINITY;
			texLookup->coneAngle	= 0;
			texLookup->label		= NULL;
			texLookup->lookupFloat	= FALSE;
			texLookup->texture		= NULL;
			texLookup->environment	= l->environment;
		}

		for (i=0,cSample=shadingPoints;cSample!=NULL;cSample=cSample->next)	samples[i++]	=	cSample;

		assert(i == numShadingPoints);

		compute(numShadingPoints,samples,texLookup);

		if (l->gatherGlobal) {
			CRadianceNode		*cNode;
			CRadianceNode		**stack,**stackBase;
			CRadianceHarmonic	*cHarmonic;
			float				totalWeight;
			int					i;
			vector				global,tmp;
			float				y[9];
			CDepositorySample	*cDep;

			stackBase		=	(CRadianceNode **) alloca(maxDepth*sizeof(CRadianceNode *)*8);

			for(;numShadingPoints>0;numShadingPoints--) {
				cSample			=	*samples++;

				harmonicTransform(y,cSample->N);	// y = harmonic transform of the function max(I.N,0)
				stack			=	stackBase;
				totalWeight		=	0;
				initv(global,0);
				*stack++		=	root;
				while(stack > stackBase) {
					cNode	=	*(--stack);

					// Iterate over the samples
					for (cHarmonic=cNode->samples;cHarmonic!=NULL;cHarmonic=cHarmonic->next) {
						vector	D;
						float	t,n,w;
						float	nominator;

						subvv(D,cHarmonic->P,cSample->P);

						// Are we in the range ?
						if ((nominator = dotvv(D,D)) > (cHarmonic->dP*cHarmonic->dP)) continue;

						n			=	dotvv(cSample->N,cHarmonic->N);
						t			=	cHarmonic->dP*max(n,(float) 0.01);
						w			=	(float) exp(-nominator*3 / (t*t));
						w			=	max(w,C_EPSILON);

						assert(w <= 1);
						assert(w > 0);

						// Blend the harmonic coefficients
						//harmonicDot(tmp,cHarmonic->Y,y);
						harmonicDiffuse(tmp,cHarmonic->Y,cSample->N);
						mulvf(tmp,w);
						addvv(global,tmp);
						totalWeight					+=	w;
					}

					// Check the children
					for (i=0;i<8;i++) {
						CRadianceNode	*tNode	=	cNode->children[i];

						if (tNode != NULL) {
							const	float	tSide	=	tNode->side;

							if (	((tNode->center[0] + tSide) > cSample->P[0])	&&
									((tNode->center[1] + tSide) > cSample->P[1])	&&
									((tNode->center[2] + tSide) > cSample->P[2])	&&
									((tNode->center[0] - tSide) < cSample->P[0])	&&
									((tNode->center[1] - tSide) < cSample->P[1])	&&
									((tNode->center[2] - tSide) < cSample->P[2])) {
								*stack++	=	tNode;
							}
						}
					}
				}

				// Normalize the result
				if (totalWeight > C_EPSILON) {
					const float	invWeight		=	(float) (1 / (C_PI*totalWeight));

					mulvf(global,invWeight);
				}

				cDep			=	hash->photons + cSample->depSample;
				const float	w	=	max((1 - cDep->C[3]),0);
				cDep->C[0]		=	global[0]*w + cDep->C[0];
				cDep->C[1]		=	global[1]*w + cDep->C[1];
				cDep->C[2]		=	global[2]*w + cDep->C[2];
			}
		}

		numShadingPoints	=	0;
	}
}






















































///////////////////////////////////////////////////////////////////////
// Class				:	CRadianceCache
// Method				:	preparetriangles
// Description			:	Split the triangles as necessary
// Return Value			:	-
// Comments				:
void	CRadianceCache::prepareTriangles() {
	// Create the triangles
	int					i;
	int					numTriangles	=	tris->numItems;
	CTriangle			**triangles		=	tris->array;

	triangleHash						=	new CTriangleHash(alpha);

	for (i=numTriangles;i>0;i--) {
		const	CTriangle	*cTriangle	=	*triangles++;
		const	CVertex		*v0			=	(const CVertex *) getPointer(cTriangle->v[0]);
		const	CVertex		*v1			=	(const CVertex *) getPointer(cTriangle->v[1]);
		const	CVertex		*v2			=	(const CVertex *) getPointer(cTriangle->v[2]);
		vector				D1,D2,N;
		float				corners[3*3];

		subvv(D1,v1->P,v0->P);				// Compute the normal vector of the triangle
		subvv(D2,v2->P,v0->P);
		crossvv(N,D1,D2);
		if (dotvv(N,N) == 0) 	continue;	// Skip the degenerate triangles

		addvv(D1,v0->N,v1->N);				// Swap the vertices if necessary
		addvv(D1,v2->N);
		if (dotvv(D1,N) < 0) {
			const CVertex	*tmp	=	v1;
			v1						=	v2;
			v2						=	tmp;
			mulvf(N,-1);
		}

		// Save the triangle
		movvv(corners+0,v0->P);
		movvv(corners+3,v1->P);
		movvv(corners+6,v2->P);
		normalizev(N);

		split(corners,N,cTriangle->object->attributes);
	}

	triangleHash->balance();

	//delete tris;			//GSH
	tris	=	NULL;
}







///////////////////////////////////////////////////////////////////////
// Class				:	CRadianceCache
// Method				:	split
// Description			:	Split a triangle
// Return Value			:	-
// Comments				:
void					CRadianceCache::split(const float *corners,const float *N,CAttributes *attributes) {
	vector			D;
	float			L0,L1,L2;
	float			M0,M1,M2;
	int				i0,i1,i2;
	float			ncorners[3*3];
	float			dP,d;

	addvv(ncorners,corners+0,corners+3);
	addvv(ncorners,corners+6);
	mulvf(ncorners,1 / (float) 3);
	subvv(D,corners+0,ncorners);
	dP		=	dotvv(D,D);
	subvv(D,corners+3,ncorners);
	if ((d = dotvv(D,D)) > dP)	dP	=	d;
	subvv(D,corners+6,ncorners);
	if ((d = dotvv(D,D)) > dP)	dP	=	d;

	// Is the triangle smapp enough ?
	if (dP < (alpha*alpha*TRIANGLE_TO_ALPHA*TRIANGLE_TO_ALPHA)) {
		// Create a triangle and store it
		CTriTon				*cTon	=	triangleHash->store(ncorners,N);

		memcpy(cTon->corners,corners,3*3*sizeof(float));
		cTon->attributes			=	attributes;
		cTon->nSides				=	attributes->nSides;

		return;
	}


	// Compute the triangle edge lengths
	subvv(D,corners+3,corners+0);
	L0	=	dotvv(D,D);
	subvv(D,corners+6,corners+3);
	L1	=	dotvv(D,D);
	subvv(D,corners+0,corners+6);
	L2	=	dotvv(D,D);

	// Sort the edge lengths
	if (L0 > L1) {
		if (L2 > L0) {
			// L2 > L0 > L1
			i0	=	2;	M0	=	L2;
			i1	=	0;	M1	=	L0;
			i2	=	1;	M2	=	L1;
		} else {
			if (L2 > L1) {
				// L0 > L2 > L1
				i0	=	0;	M0	=	L0;
				i1	=	2;	M1	=	L2;
				i2	=	1;	M2	=	L1;
			} else {
				// L0 > L1 > L2
				i0	=	0;	M0	=	L0;
				i1	=	1;	M1	=	L1;
				i2	=	2;	M2	=	L2;
			}
		}
	} else {
		if (L2 > L1) {
			// L2 > L1 > L0
			i0	=	2;	M0	=	L2;
			i1	=	1;	M1	=	L1;
			i2	=	0;	M2	=	L0;
		} else {
			if (L2 > L0) {
				// L1 > L2 > L0
				i0	=	1;	M0	=	L1;
				i1	=	2;	M1	=	L2;
				i2	=	0;	M2	=	L0;
			} else {
				// L1 > L0 > L2
				i0	=	1;	M0	=	L1;
				i1	=	0;	M1	=	L0;
				i2	=	2;	M2	=	L2;
			}
		}
	}

	// Do some sanity check
	assert(M0 >= M1);
	assert(M1 >= M2);
	assert(M2 >= 0);

	// This macro is used to create a triangle
#define processTriangle(__P0,__P1,__P2)									\
	movvv(ncorners+0,__P0);												\
	movvv(ncorners+3,__P1);												\
	movvv(ncorners+6,__P2);												\
	split(ncorners,N,attributes);

	// Check the edge lengths and figure out what king of a split we'd like to make
	if (M0 > (float) (1.5*1.5)*M1) {
		// 2 Way split
		const int			c0	=	i0;
		const int			c1	=	(c0+1) % 3;
		const int			c2	=	(c1+1) % 3;
		const float			*P0	=	corners + c0*3;
		const float			*P1	=	corners + c1*3;
		const float			*P2	=	corners + c2*3;
		vector				P01;

		// Split the triangle
		interpolatev(P01,P0,P1,(float) 0.5);

		processTriangle(P0,P01,P2);
		processTriangle(P01,P1,P2);
	} else if (M2 < M1 / (float) (2*2)) {
		// 3 Way split
		const int			c0	=	i2;
		const int			c1	=	(c0+1) % 3;
		const int			c2	=	(c1+1) % 3;
		const float			*P0	=	corners + c0*3;
		const float			*P1	=	corners + c1*3;
		const float			*P2	=	corners + c2*3;
		vector				P12,P20;

		// Split the triangle
		interpolatev(P12,P1,P2,(float) 0.5);
		interpolatev(P20,P0,P2,(float) 0.5);

		processTriangle(P0,P12,P20);
		processTriangle(P0,P1,P12);
		processTriangle(P12,P2,P20);
	} else {
		// 4 Way split
		const float			*P0	=	corners + 0;
		const float			*P1	=	corners + 3;
		const float			*P2	=	corners + 6;
		vector				P01,P12,P20;

		// Split the triangle
		interpolatev(P01,P0,P1,(float) 0.5);
		interpolatev(P12,P1,P2,(float) 0.5);
		interpolatev(P20,P2,P0,(float) 0.5);

		processTriangle(P0,P01,P20);
		processTriangle(P20,P01,P12);
		processTriangle(P01,P1,P12);
		processTriangle(P20,P12,P2);
	}

#undef processTriangle
}





///////////////////////////////////////////////////////////////////////
// Class				:	CRadianceCache
// Method				:	writeNode
// Description			:	Write a cache node onto the disk
// Return Value			:	-
// Comments				:
void					CRadianceCache::writeNode(FILE *out,CRadianceNode *node) {
	int					i;
	CRadianceHarmonic	*cSample;

	fwrite(node->center,1,sizeof(vector),out);
	fwrite(&node->side,1,sizeof(float),out);

	for (i=0,cSample=node->samples;cSample!=NULL;cSample=cSample->next,i++);
	fwrite(&i,1,sizeof(int),out);
	for (cSample=node->samples;cSample!=NULL;cSample=cSample->next) {
		fwrite(cSample,1,sizeof(CRadianceHarmonic),out);
	}

	fwrite(node->children,8,sizeof(CRadianceNode *),out);

	for (i=0;i<8;i++) {
		if (node->children[i] != NULL)	writeNode(out,node->children[i]);
	}
}




///////////////////////////////////////////////////////////////////////
// Class				:	CRadianceCache
// Method				:	readNode
// Description			:	Read a cache node from disk
// Return Value			:	-
// Comments				:
CRadianceCache::CRadianceNode				*CRadianceCache::readNode(FILE *in) {
	int					i;
	CRadianceHarmonic	*cSample;
	CRadianceNode		*cNode	=	(CRadianceNode *) memory->alloc(sizeof(CRadianceNode));

	fread(cNode->center,1,sizeof(vector),in);
	fread(&cNode->side,1,sizeof(float),in);

	cNode->samples			=	NULL;

	// Read the samples
	fread(&i,1,sizeof(int),in);
	for (;i>0;i--) {
		cSample				=	(CRadianceHarmonic *) memory->alloc(sizeof(CRadianceHarmonic));
		fread(cSample,1,sizeof(CRadianceHarmonic),in);

		cSample->next		=	cNode->samples;
		cNode->samples		=	cSample;
	}

	fread(cNode->children,8,sizeof(CRadianceNode *),in);

	for (i=0;i<8;i++) {
		if (cNode->children[i] != NULL)	cNode->children[i]	=	readNode(in);
	}

	return cNode;
}






///////////////////////////////////////////////////////////////////////
// Class				:	CRadianceCache
// Method				:	compute
// Description			:	Compute the harmonic samples
// Return Value			:	-
// Comments				:
void			CRadianceCache::compute(int numSamples,CShadingPoint **points,CTextureLookup *texLookup) {
	vector				P,N;
	float				dP,dN;
	int					i;
	const CShadingPoint	*cSample;

	// If we have way too many points, forget about clustering
	if (numSamples > 10000) {
		dP		=	C_INFINITY;
		dN		=	-1;
	} else {
		// Compute the cluster center and the radius
		initv(P,0,0,0);
		initv(N,0,0,0);
		dP		=	0;
		dN		=	1;

		for (i=0;i<numSamples;i++) {
			cSample	=	points[i];

			addvv(P,cSample->P);
			addvv(N,cSample->N);
		}

		mulvf(P,1 / (float) numSamples);
		normalizev(N);

		for (i=0;i<numSamples;i++) {
			vector	D;

			cSample	=	points[i];

			subvv(D,P,cSample->P);
			dP		=	max(dP,dotvv(D,D));
			dN		=	min(dN,dotvv(N,cSample->N));
		}

		dP		=	sqrtf(dP);				// This is the radius of the cluster
	}

	// Are we too big ?
	if ((dP > alpha) && (dN < cos(radians(60)))) {
		// We're too big, split
		i	=	partition(numSamples,points);
		compute(i,points,texLookup);
		compute(numSamples-i,points+i,texLookup);
	} else {
		// Shoot bunch of rays 
		int		numRays;
		vector	C,D;
		float	X[81],Y[27];
		CRay	ray;

		// Clear the matrices
		for (i=0;i<27;i++) {
			X[i]	=	0;
			Y[i]	=	0;
		}
		for (;i<81;i++) {
			X[i]	=	0;
		}

		// Collect the samples
		for (numRays=0;numRays<numRaysPerCluster;numRays++) {

			// Pick a random shading point
			cSample					=	points[_irand() % numSamples];

			// Sample this shading point
			sampleHemisphere(D,cSample->N,(float) (C_PI/2.0),generator);

			normalizev(D);

			movvv(ray.dir,D);
			movvv(ray.from,cSample->P);
			addvv(ray.to,ray.from,ray.dir);

			ray.invDir[COMP_X]		=	1/ray.dir[COMP_X];
			ray.invDir[COMP_Y]		=	1/ray.dir[COMP_Y];
			ray.invDir[COMP_Z]		=	1/ray.dir[COMP_Z];
			ray.t					=	C_INFINITY;
			ray.time				=	_urand();
			ray.jimp				=	-1.0f;
			ray.flags				=	ATTRIBUTES_FLAGS_TRACE_VISIBLE;
			ray.tmin				=	bias;
			ray.lastXform			=	NULL;
			ray.object				=	NULL;

			// Trace the ray
			CRenderer::trace(&ray,NULL);
			stats.numIndirectDiffuseRays++;

			// Do we have an intersection that's too close ?
			if ((dP > alpha) && (ray.t < dP)) {
				break;
			}

			// Accumulate the intersection
			if (ray.object != NULL) {
				vector		P,N;
				CAttributes	*attributes	=	ray.object->attributes;
				CPhotonMap	*globalMap;

				if ((globalMap = attributes->globalMap) == NULL) {
					initv(C,1,1,1);
				} else {
					normalizev(N,ray.N);
					mulvf(P,ray.dir,ray.t);
					addvv(P,ray.from);
					
					if(dotvv(ray.dir,N) > 0)
						mulvf(N,-1);

					stats.numIndirectDiffusePhotonmapLookups++;

					globalMap->lookup(C,P,N,attributes->photonEstimator);
					mulvv(C,attributes->surfaceColor);
				}
			} else {
				if(texLookup != NULL){
					CEnvironment *tex = texLookup->environment;
					vector D0,D1,D2,D3;
					vector color;

					// GSHTODO: Add in the dCosPhi and dSinPhi
					movvv(D0,ray.dir);
					movvv(D1,ray.dir);
					movvv(D2,ray.dir);
					movvv(D3,ray.dir);
					
					tex->lookup(color,D0,D1,D2,D3,texLookup);
					movvv(C,color);
				}
				else{
					movvv(C,backgroundColor);
				}
			}

			// To be unbiased, add a dummy sample to the other end
			harmonicAccumulate(X,Y,D,C);
			initv(C,0);
			mulvf(D,-1);
			harmonicAccumulate(X,Y,D,C);
		}

		// Did we abort because there was nearby junk
		if (numRays < numRaysPerCluster) {
			// We should keep on splitting
			i	=	partition(numSamples,points);
			compute(i,points,texLookup);
			compute(numSamples-i,points+i,texLookup);
		} else {
			// Save the sample
			CRadianceHarmonic	*cHarmonic	=	(CRadianceHarmonic *) memory->alloc(sizeof(CRadianceHarmonic));
			CRadianceNode		*cNode;
			int					depth;
			int					i,j;
			float				R;

			movvv(cHarmonic->P,P);
			movvv(cHarmonic->N,N);
			cHarmonic->dP				=	dP*3;
			cHarmonic->dN				=	dN;

			linSolve(X,Y,9,3);
			memcpy(cHarmonic->Y,Y,27*sizeof(float));

			stats.numIndirectDiffuseSamples++;

			// Save the harmonic
			cNode		=	root;
			depth		=	0;
			R			=	2*cHarmonic->dP;
			while(cNode->side > R) {
				depth++;

				for (j=0,i=0;i<3;i++) {
					if (cHarmonic->P[i] > cNode->center[i]) {
						j			|=	1 << i;
					}
				}

				if (cNode->children[j] == NULL)	{
					CRadianceNode	*nNode	=	(CRadianceNode *) memory->alloc(sizeof(CRadianceNode));

					for (i=0;i<3;i++) {
						if (cHarmonic->P[i] > cNode->center[i]) {
							nNode->center[i]	=	cNode->center[i] + cNode->side * (float) 0.25;
						} else {
							nNode->center[i]	=	cNode->center[i] - cNode->side * (float) 0.25;
						}
					}

					cNode->children[j]	=	nNode;
					nNode->side			=	cNode->side / (float) 2;
					nNode->samples		=	NULL;
					for (i=0;i<8;i++)	nNode->children[i]	=	NULL;
				}

				cNode			=	cNode->children[j];
			}

			cHarmonic->next		=	cNode->samples;
			cNode->samples		=	cHarmonic;
			maxDepth			=	max(maxDepth,depth);


#ifdef DEBUG_PRINT
			if (FALSE) {
				vector	C;
				int		i;

				initv(C,_urand(),_urand(),_urand());
				normalizev(C);

				fprintf(out,"%f %f %f - %f %f %f\n",P[0],P[1],P[2],C[0],C[1],C[2]);
				fprintf(out,"%f %f %f %f %f %f\n",P[0],P[1],P[2],P[0] + N[0]*0.3,P[1] + N[1]*0.3,P[2] + N[2]*0.3);

				for (i=0;i<numSamples;i+=4) {
					cSample					=	points[i];
				
					fprintf(out,"%f %f %f\n",cSample->P[0],cSample->P[1],cSample->P[2]);

				}
			}

			if (TRUE) {
				int		i;
				vector	D,C;

				for (i=0;i<200;i++) {
					sampleSphere(D);
					normalizev(D);
					harmonicDiffuse(C,cHarmonic->Y,D);
					mulvf(D,(float) 0.2);
					addvv(D,P);
					fprintf(out,"%f %f %f - %f %f %f\n",D[0],D[1],D[2],C[0],C[1],C[2]);
				}
			}
#endif
		}
	}
}



///////////////////////////////////////////////////////////////////////
// Class				:	CRadianceCache
// Method				:	partition
// Description			:	Partition the shading points into two clusters
// Return Value			:	-
// Comments				:
int				CRadianceCache::partition(int numRays,CShadingPoint **rays) {
	int						moved;
	CShadingPoint			*s1,*s2;
	vector					P1,P2,N1,N2;
	vector					nP1,nP2,nN1,nN2;
	int						i,j,last;
	vector					D;
	int						iteration;

	// Are we too small ?
	if (numRays == 2)	return 1;

	// Are we too big ?
	if (numRays > 1000) {
		// For large number of samples, don't wory about a very accurate split
		iteration	=	1;
	} else {
		// For small number of samples, worry about an accurate split
		iteration	=	20;
	}

	// Select two random cluster centers that are not the same
	s1	=	rays[_irand() % numRays];
	do {
		s2	=	rays[_irand() % numRays];

		subvv(D,s1->P,s2->P);
	} while(dotvv(D,D) == 0);

	// Save the cluster centers
	movvv(P1,s1->P);
	movvv(P2,s2->P);
	movvv(N1,s1->N);
	movvv(N2,s2->N);

	// Init the cluster membership
	for (i=0;i<numRays;i++) {
		rays[i]->next	=	(CShadingPoint *) (-1);
	}

	// Perform 2-means clustering
	for (moved=TRUE;(iteration > 0) && (moved==TRUE);iteration--) {
		float			d1,d2;
		CShadingPoint	*cPoint;

		moved		=	FALSE;

		initv(nP1,0,0,0);
		initv(nP2,0,0,0);
		initv(nN1,0,0,0);
		initv(nN2,0,0,0);

		// Partition the points into two clusters
		for (j=0,i=0;i<numRays;i++) {
			cPoint	=	rays[i];

			subvv(D,P1,cPoint->P);
			d1	=	lengthv(D) + alpha*(1-dotvv(cPoint->N,N1));
			subvv(D,P2,cPoint->P);
			d2	=	lengthv(D) + alpha*(1-dotvv(cPoint->N,N2));

			if (d1 < d2) {
				if (cPoint->next != (CShadingPoint *) 1) {
					moved				=	TRUE;
					cPoint->next		=	(CShadingPoint *) 1;
				}

				addvv(nP1,rays[i]->P);
				addvv(nN1,rays[i]->N);
				j++;
			} else {
				if (cPoint->next != (CShadingPoint *) 2) {
					moved				=	TRUE;
					cPoint->next		=	(CShadingPoint *) 2;
				}

				addvv(nP2,rays[i]->P);
				addvv(nN2,rays[i]->N);
			}
		}

		mulvf(P1,nP1,1/(float) j);
		mulvf(P2,nP2,1/(float) (numRays-j));
		normalizev(N1,nN1);
		normalizev(N2,nN2);

	}

	// Separate the two clusters
	for (last=0,i=0;i<numRays;i++) {
		if (rays[i]->next == (CShadingPoint *) 1) {
			CShadingPoint	*t	=	rays[last];
			rays[last++]		=	rays[i];
			rays[i]				=	t;
		}
	}

	if (rays[last]->next == (CShadingPoint *) 1)	last++;

#ifdef _DEBUG
	// Sanity check here
	for (i=0;i<last;i++)	assert(rays[i]->next == (CShadingPoint *) 1);
	for (;i<numRays;i++)	assert(rays[i]->next == (CShadingPoint *) 2);
#endif

	if ((last == 0) || (numRays == last)) {
		return partition(numRays,rays);
	} else {
		return last;
	}
}



///////////////////////////////////////////////////////////////////////
// Class				:	CRadianceCache
// Method				:	draw
// Description			:	Draw the sucker
// Return Value			:	-
// Comments				:
void		CRadianceCache::draw() {
	CRadianceHarmonic	*cSample;
	CRadianceNode		*cNode;
	CRadianceNode		**stackBase		=	(CRadianceNode **)	alloca(maxDepth*sizeof(CRadianceNode *)*8);
	CRadianceNode		**stack;
	int					i,j;
	float				P[chunkSize*3];
	float				C[chunkSize*3];
	float				*cP,*cC;

	j			=	chunkSize;
	cP			=	P;
	cC			=	C;
	stack		=	stackBase;
	*stack++	=	root;
	while(stack > stackBase) {
		cNode	=	*(--stack);

		// Sum the values in this level
		for (cSample=cNode->samples;cSample!=NULL;cSample=cSample->next,j--) {
			if (j == 0)	{
				drawPoints(chunkSize,P,C);
				cP	=	P;
				cC	=	C;
				j	=	chunkSize;
			}

			// FIXME: Maybe we should draw disks instead of points here
			movvv(cP,cSample->P);
			initv(cC,1);	// The radiance samples store spherical harmonics, not color -- so just visualize their positions
		}

		// Check the children
		for (i=0;i<8;i++) {
			CRadianceNode	*tNode;

			if ((tNode = cNode->children[i]) != NULL) {
				*stack++	=	tNode;
			}
		}
	}

	if (j != chunkSize)	drawPoints(chunkSize-j,P,C);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRadianceCache
// Method				:	bound
// Description			:	Bound the structure
// Return Value			:	-
// Comments				:
void		CRadianceCache::bound(float *bmin,float *bmax) {
	assert(root != NULL);

	bmin[0]	=	root->center[0] - root->side*0.5f;
	bmin[1]	=	root->center[1] - root->side*0.5f;
	bmin[2]	=	root->center[2] - root->side*0.5f;

	bmax[0]	=	root->center[0] + root->side*0.5f;
	bmax[1]	=	root->center[1] + root->side*0.5f;
	bmax[2]	=	root->center[2] + root->side*0.5f;
}

