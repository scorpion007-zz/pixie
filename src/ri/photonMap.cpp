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
CPhotonMap::CPhotonMap(const char *n,FILE *in) : CMap<CPhoton>() , CFileResource(n) {
	refCount		=	0;
	modifying		=	FALSE;
	maxPower		=	0;
	osCreateMutex(mutex);

	identitym(from);
	identitym(to);

	// Try to read the photonmap
	if (in != NULL) {
		matrix	fromWorld,toWorld;

		CMap<CPhoton>::read(in);

		// Read the transformation matrices
		fread(fromWorld,1,sizeof(matrix),in);
		fread(toWorld,1,sizeof(matrix),in);
		fread(&maxPower,1,sizeof(float),in);

		mulmm(to,fromWorld,CRenderer::toWorld);
		mulmm(from,CRenderer::fromWorld,toWorld);
	} else {
	
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
CPhotonMap::~CPhotonMap() {
	osDeleteMutex(mutex);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMap
// Method				:	reset
// Description			:	Reset the photonmap
// Return Value			:
// Comments				:
void	CPhotonMap::reset() {
	CMap<CPhoton>::reset();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMap
// Method				:	write
// Description			:	Write the photon map into a file
// Return Value			:
// Comments				:
void	CPhotonMap::write(const CXform *world) {
	// Flush the photonmap
	FILE		*out		=	ropen(name,"wb",filePhotonMap);

	if (out != NULL) {

		// Balance the map
		balance();

		// Write the map
		CMap<CPhoton>::write(out);

		// Write the matrices
		fwrite(CRenderer::fromWorld,1,sizeof(matrix),out);
		fwrite(CRenderer::toWorld,1,sizeof(matrix),out);
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
// Comments				:	Nl	must be normalized
//							Il	must be normalized
void	CPhotonMap::lookup(float *Cl,const float *Pl,const float *Nl,int maxFound) {
	int				numFound;
	const CPhoton	**indices	=	(const CPhoton **)	alloca((maxFound+1)*sizeof(CPhoton *)); 
	float			*distances	=	(float	*)			alloca((maxFound+1)*sizeof(float)); 
	CLookup			l;

	searchRadius		=	(sqrtf(maxFound*maxPower / 0.05f) / (float) C_PI)*0.5f;

	// Lookup the photonmap at the location of the photon
	distances[0]		=	searchRadius*searchRadius;
	l.maxFound			=	maxFound;
	l.numFound			=	0;
	mulmp(l.P,to,Pl);
	mulmn(l.N,from,Nl);
	l.gotHeap			=	FALSE;
	l.indices			=	indices;
	l.distances			=	distances;


	CMap<CPhoton>::lookupWithN(&l,1);

	initv(Cl,0);

	if ((numFound = l.numFound) < 2)	return;

	// Accumulate the irradiance
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
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMap
// Method				:	lookup
// Description			:	Locate the nearest maxFoundPhoton photons
// Return Value			:
// Comments				:	Nl	must be normalized
//							Il	must be normalized
void	CPhotonMap::lookup(float *Cl,const float *Pl,int maxFound) {
	int				numFound	=	0;
	const CPhoton	**indices	=	(const CPhoton **)	alloca((maxFound+1)*sizeof(CPhoton *)); 
	float			*distances	=	(float	*)			alloca((maxFound+1)*sizeof(float)); 
	CLookup			l;

	searchRadius		=	(sqrtf(maxFound*maxPower / 0.05f) / (float) C_PI)*0.5f;

	distances[0]		=	searchRadius*searchRadius;

	l.maxFound			=	maxFound;
	l.numFound			=	0;
	mulmp(l.P,to,Pl);
	initv(l.N,0,0,0);
	l.gotHeap			=	FALSE;
	l.indices			=	indices;
	l.distances			=	distances;

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
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMap
// Method				:	balance
// Description			:	Balance the map
// Return Value			:
// Comments				:
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
void	CPhotonMap::store(const float *P,const float *N,const float *I,const float *C) {

	osLock(mutex);
	CPhoton	*ton	=	CMap<CPhoton>::store(P,N);
	dirToPhoton(ton->theta,ton->phi,I);
	movvv(ton->C,C);
	maxPower	=	max(maxPower,dotvv(C,C));
	osUnlock(mutex);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMap
// Method				:	bound
// Description			:	Bound the data
// Return Value			:
// Comments				:
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
