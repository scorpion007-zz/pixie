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
//  File				:	photonMap.cpp
//  Classes				:
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "photonMap.h"
#include "object.h"
#include "raytracer.h"
#include "tiffio.h"
#include "tiff.h"
#include "stats.h"
#include "memory.h"
#include "random.h"
#include "error.h"

int					inited	=	FALSE;
float				costheta[256];
float				sintheta[256];
float				cosphi[256];
float				sinphi[256];

#define	PHOTON_CAUSTICS		1
#define	PHOTON_EXPLOSION	2
#define	PHOTON_POINT		4
#define	PHOTON_DISTANT		8
#define	PHOTON_AREA			16


///////////////////////////////////////////////////////////////////////
//
//
//	Regular Photon Mapping stuff
//
//
///////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMap
// Method				:	CPhotonMap
// Description			:	Ctor
// Return Value			:
// Comments				:
// Date last edited		:	3/11/2003
CPhotonMap::CPhotonMap(const char *n,const CXform *world,FILE *in) : CMap<CPhoton>() , CFileResource(n) {
	root			=	NULL;
	maxDepth		=	1;
	refCount		=	0;
	modifying		=	FALSE;
	maxPower		=	0;

	// Try to read the photonmap
	if (in != NULL) {
		matrix	tmp;
		int		i;

		CMap<CPhoton>::read(in);

		// Read the transformation matrices
		fread(tmp,1,sizeof(matrix),in);
		mulmm(toCamera,tmp,world->to);
		fread(tmp,1,sizeof(matrix),in);
		mulmm(fromCamera,world->from,tmp);
		fread(&maxPower,1,sizeof(float),in);

		root			=	new CPhotonNode;
		addvv(root->center,bmin,bmax);
		mulvf(root->center,1 / (float) 2);
		root->side		=	max(max(bmax[0]-bmin[0],bmax[1] - bmin[1]),bmax[2] - bmin[2]);
		root->samples	=	NULL;
		for (i=0;i<8;i++) root->children[i]	=	NULL;

		fclose(in);
	} else {
		// Reset the transformation matrices
		movmm(toCamera,world->from);
		movmm(fromCamera,world->to);

		// Make sure we have a root
		balance();
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMap
// Method				:	~CPhotonMap
// Description			:	Dtor
// Return Value			:
// Comments				:
// Date last edited		:	3/11/2003
CPhotonMap::~CPhotonMap() {
	if (root != NULL) {
		CPhotonNode		**stackBase	=	(CPhotonNode **)	alloca(maxDepth*sizeof(CPhotonNode *)*8);
		CPhotonNode		**stack;
		CPhotonNode		*cNode;
		CPhotonSample	*cSample;
		int			i;

		stack		=	stackBase;
		*stack++	=	root;
		while(stack > stackBase) {
			cNode	=	*(--stack);

			while((cSample=cNode->samples) != NULL) {
				cNode->samples	=	cSample->next;
				delete cSample;
			}

			for (i=0;i<8;i++) {
				if (cNode->children[i] != NULL) *stack++	=	cNode->children[i];
			}

			delete cNode;
		}
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMap
// Method				:	reset
// Description			:	Reset the photonmap
// Return Value			:
// Comments				:
// Date last edited		:	3/11/2003
void	CPhotonMap::reset() {
	CMap<CPhoton>::reset();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMap
// Method				:	write
// Description			:	Write the photon map into a file
// Return Value			:
// Comments				:
// Date last edited		:	3/11/2003
void	CPhotonMap::write(const CXform *world) {
	// Flush the photonmap
	FILE		*out		=	ropen(name,"wb",filePhotonMap);

	if (out != NULL) {

		// Balance the map
		balance();

		// Write the map
		CMap<CPhoton>::write(out);

		// Write the matrices
		fwrite(world->from,1,sizeof(matrix),out);
		fwrite(world->to,1,sizeof(matrix),out);
		maxPower	=	sqrtf(maxPower);
		fwrite(&maxPower,1,sizeof(float),out);

		fclose(out);
	} else {
		error(CODE_BADFILE,"Unable to open %s for writing\n",name);
	}
}




///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMap
// Method				:	lookup
// Description			:	Locate the nearest maxFoundPhoton photons
// Return Value			:
// Comments				:	
int		CPhotonMap::probe(float *C,const float *P,const float *N) {
	CPhotonNode			*cNode;
	CPhotonNode			**stackBase	=	(CPhotonNode **)	alloca(maxDepth*sizeof(CPhotonNode *)*8);
	CPhotonNode			**stack;
	CPhotonSample		*cSample;
	float				totalWeight	=	0;
	int					i;

	if (root == NULL) return FALSE;

	stack			=	stackBase;
	*stack++		=	root;
	initv(C,0,0,0);
	while(stack > stackBase) {
		cNode	=	*(--stack);

		// Iterate over the samples
		for (cSample=cNode->samples;cSample!=NULL;cSample=cSample->next) {
			vector	D;
			float	d;
			
			subvv(D,cSample->P,P);

			d	=	dotvv(D,D);

			if (d < (cSample->dP*cSample->dP)) {
				d	=	sqrtf(d);
				d	+=	absf(dotvv(D,cSample->N))*16;

				if (dotvv(cSample->N,N) < 0) {
					// if N=0, this should not operate anything out.  verify
					d = C_INFINITY;
				}
			
				if (d < cSample->dP) {
					float	weight	=	1 - d / cSample->dP;

					totalWeight		+=	weight;
					C[0]			+=	cSample->C[0]*weight;
					C[1]			+=	cSample->C[1]*weight;
					C[2]			+=	cSample->C[2]*weight;
				}
			}
		}

		// Check the children
		for (i=0;i<8;i++) {
			CPhotonNode	*tNode	=	cNode->children[i];

			if (tNode != NULL) {
				const	float	tSide	=	tNode->side;

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

	if (totalWeight > 0) {
		mulvf(C,1 / totalWeight);
		return TRUE;
	}

	return FALSE;
}



///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMap
// Method				:	insert
// Description			:	Insert a sample
// Return Value			:
// Comments				:	
void	CPhotonMap::insert(const float *C,const float *P,const float *N,float dP) {
	CPhotonSample	*cSample	=	new CPhotonSample;
	CPhotonNode		*cNode		=	root;
	int				depth		=	0;
	int				i,j;

	movvv(cSample->C,C);
	movvv(cSample->P,P);
	movvv(cSample->N,N);
	cSample->dP	=	dP;

	while(cNode->side > (2*dP)) {
		depth++;

		for (j=0,i=0;i<3;i++) {
			if (P[i] > cNode->center[i]) {
				j			|=	1 << i;
			}
		}

		if (cNode->children[j] == NULL)	{
			CPhotonNode	*nNode	=	(CPhotonNode *) new CPhotonNode;

			for (i=0;i<3;i++) {
				if (P[i] > cNode->center[i]) {
					nNode->center[i]	=	cNode->center[i] + cNode->side / (float) 4;
				} else {
					nNode->center[i]	=	cNode->center[i] - cNode->side / (float) 4;
				}
			}

			cNode->children[j]	=	nNode;
			nNode->side			=	cNode->side / (float) 2;
			nNode->samples		=	NULL;
			for (i=0;i<8;i++)	nNode->children[i]	=	NULL;
		}

		cNode			=	cNode->children[j];
	}

	cSample->next	=	cNode->samples;
	cNode->samples	=	cSample;
	maxDepth		=	max(maxDepth,depth);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMap
// Method				:	lookup
// Description			:	Locate the nearest maxFoundPhoton photons
// Return Value			:
// Comments				:	Nl	must be normalized
//							Il	must be normalized
// Date last edited		:	4/1/2002
void	CPhotonMap::lookup(float *Cl,const float *Pl,const float *Nl,int maxFound) {
	int				numFound	=	0;
	const CPhoton	**indices	=	(const CPhoton **)	alloca((maxFound+1)*sizeof(CPhoton *)); 
	float			*distances	=	(float	*)			alloca((maxFound+1)*sizeof(float)); 
	CLookup			l;

	searchRadius		=	(sqrtf(maxFound*maxPower / 0.05f) / (float) C_PI)*0.5f;

	distances[0]		=	searchRadius*searchRadius;

	l.maxFound			=	maxFound;
	l.numFound			=	0;
	mulmp(l.P,toCamera,Pl);
	mulmn(l.N,fromCamera,Nl);
	l.gotHeap			=	FALSE;
	l.indices			=	indices;
	l.distances			=	distances;

	if (!probe(Cl,l.P,l.N)) {
		CMap<CPhoton>::lookupWithN(&l,1);

		initv(Cl,0,0,0);

		if (l.numFound < 2)	return;

		numFound	=	l.numFound;

		for (int i=1;i<=numFound;i++) {
			const	CPhoton	*p	=	indices[i];
			vector	I;

			assert(distances[i] <= distances[0]);

			photonToDir(I,p->theta,p->phi);

			if (dotvv(I,l.N) < 0) {
				addvv(Cl,p->C);
			}
		}

		// Normalize the result
		mulvf(Cl,(float) (1.0 / (C_PI*distances[0])));

		// Insert it into the probe 
		insert(Cl,l.P,l.N,sqrtf(distances[0])*(float) 0.2);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMap
// Method				:	lookup
// Description			:	Locate the nearest maxFoundPhoton photons
// Return Value			:
// Comments				:	Nl	must be normalized
//							Il	must be normalized
// Date last edited		:	4/1/2002
void	CPhotonMap::lookup(float *Cl,const float *Pl,int maxFound) {
	int				numFound	=	0;
	const CPhoton	**indices	=	(const CPhoton **)	alloca((maxFound+1)*sizeof(CPhoton *)); 
	float			*distances	=	(float	*)			alloca((maxFound+1)*sizeof(float)); 
	CLookup			l;

	searchRadius		=	(sqrtf(maxFound*maxPower / 0.05f) / (float) C_PI)*0.5f;

	distances[0]		=	searchRadius*searchRadius;

	l.maxFound			=	maxFound;
	l.numFound			=	0;
	mulmp(l.P,toCamera,Pl);
	initv(l.N,0,0,0);
	l.gotHeap			=	FALSE;
	l.indices			=	indices;
	l.distances			=	distances;

	if (!probe(Cl,l.P,l.N)) {
		CMap<CPhoton>::lookup(&l,1);

		initv(Cl,0,0,0);

		if (l.numFound < 2)	return;

		numFound	=	l.numFound;

		for (int i=1;i<=numFound;i++) {
			const	CPhoton	*p	=	indices[i];

			assert(distances[i] <= distances[0]);

			addvv(Cl,p->C);
		}
		
		// Normalize the result
		mulvf(Cl,(float) (1.0 / (C_PI*distances[0])));

		// Record it so we can probe it later
		insert(Cl,l.P,l.N,sqrtf(distances[0])*(float) 0.2);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMap
// Method				:	balance
// Description			:	Balance the map
// Return Value			:
// Comments				:
// Date last edited		:	9/18/2002
void	CPhotonMap::balance() {
	// If we have no photons in the map, add a dummy one to avoid an if statement during the lookup
	if (numPhotons == 0) {
		vector	P		=	{0,0,0};
		vector	I		=	{0,0,1};
		CPhoton	*photon	=	CMap<CPhoton>::store(P,I);
		initv(photon->C,0,0,0);
	}

	CMap<CPhoton>::balance();
}



///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMap
// Method				:	store
// Description			:	Store a photon
// Return Value			:
// Comments				:
// Date last edited		:	9/18/2002
void	CPhotonMap::store(const float *P,const float *N,const float *I,const float *C) {
	CPhoton	*ton	=	CMap<CPhoton>::store(P,N);
	dirToPhoton(ton->theta,ton->phi,I);
	movvv(ton->C,C);
	maxPower	=	max(maxPower,dotvv(C,C));
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMap
// Method				:	bound
// Description			:	Bound the data
// Return Value			:
// Comments				:
// Date last edited		:	9/18/2002
void	CPhotonMap::bound(float *bmin,float *bmax) {
	int	i;

	initv(bmin,C_INFINITY);
	initv(bmax,-C_INFINITY);

	for (i=1;i<numPhotons;i++)	addBox(bmin,bmax,photons[i].P);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMap
// Method				:	draw
// Description			:	Draw the photonmap
// Return Value			:
// Comments				:
// Date last edited		:	9/18/2002
void	CPhotonMap::draw() {
	float		P[chunkSize*3];
	float		C[chunkSize*3];
	int			i,j;
	float		*cP	=	P;
	float		*cC	=	C;
	CPhoton		*cT	=	photons+1;

	// Collect and dispatch the photons
	for (i=numPhotons-1,j=chunkSize;i>0;i--,cT++,cP+=3,cC+=3,j--) {
		if (j == 0)	{
			drawPoints(chunkSize,P,C);
			cP	=	P;
			cC	=	C;
			j	=	chunkSize;
		}

		float maxChannel	=	max(max(cT->C[0],cT->C[1]),cT->C[2]);
		
		movvv(cP,cT->P);
		mulvf(cC,cT->C,1 / maxChannel);
	}

	if (j != chunkSize)	drawPoints(chunkSize-j,P,C);
}
