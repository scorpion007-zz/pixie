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
//  File				:	pointCloud.cpp
//  Classes				:	CPointCloud
//  Description			:	Implementation - George
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "pointCloud.h"
#include "object.h"
#include "raytracer.h"
#include "memory.h"
#include "random.h"
#include "error.h"


///////////////////////////////////////////////////////////////////////
// globals
///////////////////////////////////////////////////////////////////////

int			CPointCloud::drawDiscs		=	TRUE;
int			CPointCloud::drawChannel	=	0;


///////////////////////////////////////////////////////////////////////
// Class				:	CPointCloud
// Method				:	CPointCloud
// Description			:	Ctor
// Return Value			:
// Comments				:	for a write-mode map, ch and nc must be provided
CPointCloud::CPointCloud(const char *n,const float *from,const float *to,const float *toNDC,const char *channelDefs,int write) : CMap<CPointCloudPoint>(), CTexture3d(n,from,to,toNDC) {
	// Create our data areas
	flush				=	write;
	maxdP				=	0;

	osCreateMutex(mutex);

	// Assign the channels
	defineChannels(channelDefs);

	// Make sure we have a root
	// (but only if we're looking up, otherwise we'd add duff data)
	if (!write) balance();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPointCloud
// Method				:	CPointCloud
// Description			:	Ctor
// Return Value			:
// Comments				:	for a write-mode map via ptcapi, ch and nc must be provided
CPointCloud::CPointCloud(const char *n,const float *from,const float *to,const float *toNDC,int numChannels,char **channelNames,char **channelTypes,int write) : CMap<CPointCloudPoint>(), CTexture3d(n,from,to,toNDC) {
	// Create our data areas
	flush				=	write;
	maxdP				=	0;

	osCreateMutex(mutex);

	// Assign the channels
	defineChannels(numChannels,channelNames,channelTypes);

	// Make sure we have a root
	// (but only if we're looking up, otherwise we'd add duff data)
	if (!write) balance();
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPointCloud
// Method				:	CPointCloud
// Description			:	Ctor
// Return Value			:
// Comments				:	for a write-mode map, ch and nc must be provided
CPointCloud::CPointCloud(const char *n,const float *from,const float *to,FILE *in) : CMap<CPointCloudPoint>(), CTexture3d(n,from,to) {

	// Create our data areas
	flush	=	FALSE;
	maxdP	=	0;
	
	osCreateMutex(mutex);

	
	// Try to read the point cloud

	// Read the header
	readChannels(in);
	
	// Read the points
	CMap<CPointCloudPoint>::read(in);

	// Reserve the actual space
	data.reserve(numItems*dataSize);
	
	// Read the data
	fread(data.array,sizeof(float),numItems*dataSize,in);
	data.numItems	=	numItems*dataSize;

	// Read the maximum radius
	fread(&maxdP,sizeof(float),1,in);
	
	// Close the file
	fclose(in);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPointCloud
// Method				:	~CPointCloud
// Description			:	Dtor
// Return Value			:
// Comments				:
CPointCloud::~CPointCloud() {
	osDeleteMutex(mutex);

	if (flush) write();
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPointCloud
// Method				:	reset
// Description			:	Reset the photonmap
// Return Value			:
// Comments				:
void	CPointCloud::reset() {
	osLock(mutex);
	CMap<CPointCloudPoint>::reset();
	osUnlock(mutex);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPointCloud
// Method				:	write
// Description			:	Write the photon map into a file
// Return Value			:
// Comments				:
void	CPointCloud::write() {
	// Flush the photonmap
	FILE		*out		=	ropen(name,"wb",filePointCloud);

	if (out != NULL) {

		// Balance the map
		balance();

		// Write out the header and channels
		writeChannels(out);
		
		// Write the map
		CMap<CPointCloudPoint>::write(out);
	
		// Write the data
		fwrite(data.array,sizeof(float),numItems*dataSize,out);

		// Read the maximum radius
		fwrite(&maxdP,sizeof(float),1,out);
	
		// Close the file
		fclose(out);
	} else {
		error(CODE_BADFILE,"Failed to open \"%s\" for writing\n",name);
	}
}



///////////////////////////////////////////////////////////////////////
// Class				:	CPointCloud
// Method				:	lookup
// Description			:	Locate the nearest points
// Return Value			:
// Comments				:	Nl	must be normalized
//							Il	must be normalized
void	CPointCloud::lookup(float *Cl,const float *Pl,const float *Nl,float radius) {
	const int 				maxFound	=	16;
	const CPointCloudPoint	**indices	=	(const CPointCloudPoint **)	alloca((maxFound+1)*sizeof(CPointCloudPoint *)); 
	float					*distances	=	(float	*)					alloca((maxFound+1)*sizeof(float)); 
	CPointLookup			l;
	int						i,j;
	const float				scale		=	2.5f;	// By controlling this, we 

	distances[0]		=	maxdP*maxdP*scale*scale;
	l.maxFound			=	maxFound;
	l.numFound			=	0;
	l.ignoreNormal		=	dotvv(Nl,Nl) < C_EPSILON;

	// Perform lookup in the world coordinate system
	mulmp(l.P,to,Pl);
	mulmn(l.N,from,Nl);
	mulvf(l.N,-1);				// Photonmaps have N reversed, we must reverse
								// N when looking up it it
	if (dotvv(Nl,Nl) > C_EPSILON) normalizevf(l.N);
	
	l.gotHeap			=	FALSE;
	l.indices			=	indices;
	l.distances			=	distances;

	// No need to lock the mutex here, CMap::lookup is thread safe
	lookup(&l,1,scale);

	for (i=0;i<dataSize;i++) Cl[i] = 0.0f;	//GSHTODO: channel fill values

	if (l.numFound < 2)	return;

	int		numFound		=	l.numFound;
	float	totalWeight		=	0;
	
	for (i=1;i<=numFound;i++) {
		const	CPointCloudPoint	*p	=	indices[i];

		assert(distances[i] <= distances[0]);

		const float	t		=	sqrtf(distances[i]) / (p->dP*scale);
		const float	weight	=	l.ignoreNormal ? (1-t) : (1-t)*(-dotvv(l.N,p->N));
		
		float		*dest	=	Cl;
		const float	*src	=	data.array + p->entryNumber;
		for (j=0;j<dataSize;j++) {
			*dest++			+=	(*src++)*weight;
		}
		totalWeight += weight;
	}
	
	if (totalWeight > 0) {
		// Divide the contribution
		const float weight	= 1.0f/totalWeight;
		for (i=0;i<dataSize;i++) Cl[i]	*=	weight;
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPointCloud
// Method				:	balance
// Description			:	Balance the map
// Return Value			:
// Comments				:
void	CPointCloud::balance() {
	// If we have no points in the map, add a dummy one to avoid an if statement during the lookup
	if (numItems == 0) {
		vector	P		=	{0,0,0};
		vector	N		=	{0,0,0};
		float	*data	=	(float*) alloca(dataSize*sizeof(float));

		for (int i=0;i<dataSize;i++)	data[i] = 0;

		// Store the fake data
		store(data,P,N,0);
	}

	// Balance the data
	CMap<CPointCloudPoint>::balance();
}



///////////////////////////////////////////////////////////////////////
// Class				:	CPointCloud
// Method				:	store
// Description			:	Store a photon
// Return Value			:
// Comments				:
void	CPointCloud::store(const float *C,const float *cP,const float *cN,float dP) {
	vector				P,N;
	CPointCloudPoint	*point;

	// Store in the world coordinate system
	mulmp(P,to,cP);
	mulmn(N,from,cN);
	dP					*=	dPscale;
	
	osLock(mutex);	// FIXME: use rwlock to allow multiple readers
	point				=	CMap<CPointCloudPoint>::store(P,N);
	point->entryNumber	=	data.numItems;
	point->dP			=	dP;

	for (int i=0;i<dataSize;i++)	data.push(C[i]);

	maxdP				=	max(maxdP,dP);
	
	osUnlock(mutex);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPointCloud
// Method				:	getPoint
// Description			:	Retrieve an indexed point
// Return Value			:
// Comments				:
void	CPointCloud::getPoint(int i,float *C,float *P,float *N,float *dP) {
	const	CPointCloudPoint	*p		=	items + i;
	const float 				*src	=	data.array + p->entryNumber;
	float						*dest	=	C;
	
	for (int j=0;j<dataSize;j++) {
		*dest++		=	*src++;
	}
	
	movvv(P,p->P);
	movvv(N,p->N);
	dP[0] = p->dP;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPointCloud
// Method				:	draw
// Description			:	Gui interface
// Return Value			:
// Comments				:
void	CPointCloud::draw() {
	float		P[chunkSize*3];
	float		C[chunkSize*3];
	float		N[chunkSize*3];
	float		dP[chunkSize];
	int			i,j;
	int			sampleStart		=	channels[drawChannel].sampleStart;
	int			numSamples		=	channels[drawChannel].numSamples;
	float		*cP				=	P;
	float		*cC				=	C;
	float		*cN				=	N;
	float		*cdP			=	dP;
	CPointCloudPoint	*cT		=	items+1;

	// Collect and dispatch the photons
	for (i=numItems,j=chunkSize;i>0;i--,cT++,cP+=3,cdP++,cN+=3,cC+=3,j--) {
		if (j == 0)	{
			if (drawDiscs)		drawDisks(chunkSize,P,dP,N,C);
			else			 	drawPoints(chunkSize,P,C);
			cP	=	P;
			cC	=	C;
			cN	=	N;
			cdP	=	dP;
			j	=	chunkSize;
		}
		
		movvv(cP,cT->P);
		movvv(cN,cT->N);
		*cdP	=	cT->dP;		// was /dPscale;	but should already be in world
		
		float *DDs = data.array + cT->entryNumber + sampleStart;
		if (numSamples == 1) {
			initv(cC,DDs[0]);
		} else if (numSamples == 2) {
			initv(cC,DDs[0],DDs[1],0);
		} else {
			movvv(cC,DDs);
		}
	}

	if (j != chunkSize) {
		if (drawDiscs)		drawDisks(chunkSize-j,P,dP,N,C);
		else			 	drawPoints(chunkSize-j,P,C);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPointCloud
// Method				:	keyDown
// Description			:	handle keypresses
// Return Value			:	-
// Comments				:
int			CPointCloud::keyDown(int key) {
	if ((key == 'd') || (key == 'D')) {
		drawDiscs = TRUE;
		return TRUE;
	} else if ((key == 'p') || (key == 'P')) {
		drawDiscs = FALSE;
		return TRUE;
	} else if ((key == 'q') || (key == 'Q')) {
		drawChannel--;
		if (drawChannel < 0) drawChannel = 0;
		printf("channel : %s\n",channels[drawChannel].name);
		return TRUE;
	} else if ((key == 'w') || (key == 'W')) {
		drawChannel++;
		if (drawChannel >= numChannels) drawChannel = numChannels-1;
		printf("channel : %s\n",channels[drawChannel].name);
		return TRUE;
	}

	return FALSE;
}

//////////////////////////////////////////////////////////////////////
// Class				:	CPointCloud
// Method				:	draw
// Description			:	Gui interface
// Return Value			:
// Comments				:
void	CPointCloud::bound(float *bmin,float *bmax) {
	movvv(bmin,this->bmin);
	movvv(bmax,this->bmax);
}

