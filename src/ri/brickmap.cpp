//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright � 1999 - 2003, Okan Arikan
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
//  File				:	brickmap.cpp
//  Classes				:	CBrickMap
//  Description			:	Da implementation
//
////////////////////////////////////////////////////////////////////////

#include "common/os.h"
#include "brickmap.h"
#include "random.h"
#include "renderer.h"
#include "error.h"
#include "pointCloud.h"
#include "memory.h"




// The static members of the CBrickMap class
CBrickMap	*CBrickMap::brickMaps		=	NULL;			// List of brickmaps in memory
int			CBrickMap::referenceNumber	=	0;				// The last reference number
int			CBrickMap::currentMemory	=	0;				// The currently used memory abount
int			CBrickMap::maxMemory		=	0;				// The maximum memory for brickmaps


////////////////////////////////////////////////////////////////////////
// This number controls the density of the points in the finest level of the tree
// Larger it is, the smaller the leaf level voxels will be (compared to the point size)
#define	LEAF_FACTOR 0.4f

///////////////////////////////////////////////////////////////////////
// Function				:	intersect
// Description			:	Compute the volume of the intersection of the cube centered at P with side dP, with the cube centered at x,y,z with side d
// Return Value			:	the volume of the intersection
// Comments				:
// Date last edited		:	7/16/2006
static	inline	float	intersect(const float *P,float dP,float x,float y,float z,float d) {
	float	tmin1,tmin2,tmax1,tmax2,tmin,tmax;
	float	w;

	// X coordinate overlap
	tmin1	=	P[0] - dP;
	tmax1	=	P[0] + dP;
	tmin2	=	x - d;
	tmax2	=	x + d;
	tmin	=	max(tmin1,tmin2);
	tmax	=	min(tmax1,tmax2);
	if (tmax <= tmin)	return 0;
	w		=	tmax - tmin;

	// Y coordinate overlap
	tmin1	=	P[1] - dP;
	tmax1	=	P[1] + dP;
	tmin2	=	y - d;
	tmax2	=	y + d;
	tmin	=	max(tmin1,tmin2);
	tmax	=	min(tmax1,tmax2);
	if (tmax <= tmin)	return 0;
	w		*=	tmax - tmin;

	// Z coordinate overlap
	tmin1	=	P[2] - dP;
	tmax1	=	P[2] + dP;
	tmin2	=	z - d;
	tmax2	=	z + d;
	tmin	=	max(tmin1,tmin2);
	tmax	=	min(tmax1,tmax2);
	if (tmax <= tmin)	return 0;
	w		*=	tmax - tmin;

	return w;
}











///////////////////////////////////////////////////////////////////////
// Class				:	CBrickMap
// Method				:	CBrickMap
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	7/15/2006
CBrickMap::CBrickMap(FILE *in,const char *name,CXform *world) : CTexture3d(name,world) {
	int		offset,i;

	// Init the data
	nextMap			=	brickMaps;
	brickMaps		=	this;
	normalThreshold	=	0.7f;
	file			=	in;
	modifying		=	FALSE;

	// Read the header offset
	fseek(file,-4,SEEK_END);
	fread(&offset,1,sizeof(int),file);
	fseek(file,offset,SEEK_SET);

	// Read the class data
	readChannels(file);
	
	fread(bmin,1,sizeof(vector),file);
	fread(bmax,1,sizeof(vector),file);
	fread(center,1,sizeof(vector),file);
	fread(&side,1,sizeof(float),file);
	invSide	=	1 / side;
	fread(&maxDepth,1,sizeof(int),file);
	fread(activeBricks,BRICK_HASHSIZE,sizeof(CBrickNode *),file);

	// Read the permanent bricks nodes
	for (i=0;i<BRICK_HASHSIZE;i++) {
		if (activeBricks[i] != NULL) {
			activeBricks[i]	=	NULL;

			while(TRUE) {
				CBrickNode	*cNode	=	new CBrickNode;

				fread(cNode,1,sizeof(CBrickNode),file);

				assert(cNode->brick == NULL);
				assert(cNode->fileIndex != -1);

				if (cNode->next != NULL) {
					cNode->next		=	activeBricks[i];
					activeBricks[i]	=	cNode;
				} else {
					cNode->next		=	activeBricks[i];
					activeBricks[i]	=	cNode;
					break;
				}
			}
		}
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CBrickMap
// Method				:	CBrickMap
// Description			:	Ctor
// Return Value			:	-
// Comments				:	Use this contructor to compute from sctratch
// Date last edited		:	7/15/2006
CBrickMap::CBrickMap(const char *name,const float *bmi,const float *bma,CXform *world,CTexture3dChannel *ch,int nc) : CTexture3d(name,world,nc,ch) {
	int	i;
	
	// Init the data
	nextMap			=	brickMaps;
	brickMaps		=	this;
	normalThreshold	=	0.7f;
	file			=	NULL;
	modifying		=	TRUE;


	// Compute the bounding cube
	movvv(bmin,bmi);
	movvv(bmax,bma);
	subvv(bmax,bmin);
	side			=	bmax[0];
	side			=	max(side,bmax[1]);
	side			=	max(side,bmax[2]);
	invSide			=	1 / side;
	addvf(bmax,bmin,side);
	addvv(center,bmin,bmax);
	mulvf(center,0.5f);

	maxDepth		=	10;
	file			=	ropen(name,"wb+",fileBrickMap);		// This is the file we will be writing to

	// Initialize the hash table
	for (i=0;i<BRICK_HASHSIZE;i++)	activeBricks[i]	=	NULL;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CBrickMap
// Method				:	~CBrickMap
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	7/15/2006
CBrickMap::~CBrickMap() {
	int			i;
	CBrickNode	*cNode;
	CBrickMap	*cMap,*pMap;

	// Flush the memory
	brickMapFlush(TRUE);

	// Remove us from the list of bricks in memory
	for (pMap=NULL,cMap=brickMaps;cMap!=NULL;pMap=cMap,cMap=cMap->nextMap) {
		if (cMap == this) {
			if (pMap == NULL)	brickMaps		=	nextMap;
			else				pMap->nextMap	=	nextMap;
			break;
		}
	}
	
	// Free the hash table
	for (i=0;i<BRICK_HASHSIZE;i++) {
		while((cNode=activeBricks[i]) != NULL) {
			activeBricks[i]	=	cNode->next;
			assert(cNode->brick == NULL);
			delete cNode;
		}
	}

	// Close the file if not already have done so
	if (file != NULL)	fclose(file);
}


















//////////////////////////////////////////////////////////////////
//
//   Here are some convenient macros for locating bricks/voxels








///////////////////////////////////////////////////////////
// This macro iterates over the bricks that intersect the normalized point P
// ---> Preconditions:
// P			= normalized point
// dP			= lookup radius
// ---> Within the loop:
// x,y,z		= the brick coordinates
#define	forEachBrick(__depth) 															\
	const float	tmp	=	invSide*(float) (1 << __depth);									\
	int			xs	=	(int) floor((P[0]-dP)*tmp);										\
	int			ys	=	(int) floor((P[1]-dP)*tmp);										\
	int			zs	=	(int) floor((P[2]-dP)*tmp);										\
	int			xe	=	(int) floor((P[0]+dP)*tmp);										\
	int			ye	=	(int) floor((P[1]+dP)*tmp);										\
	int			ze	=	(int) floor((P[2]+dP)*tmp);										\
	int			x,y,z;																	\
	if (xs < 0)	xs	=	0;																\
	if (ys < 0)	ys	=	0;																\
	if (zs < 0)	zs	=	0;																\
	if (xe >= (1 << depth))	xe	=	(1 << depth) - 1;									\
	if (ye >= (1 << depth))	ye	=	(1 << depth) - 1;									\
	if (ze >= (1 << depth))	ze	=	(1 << depth) - 1;									\
	for (x=xs;x<=xe;x++) for (y=ys;y<=ye;y++) for (z=zs;z<=ze;z++) {

///////////////////////////////////////////////////////////
// This macro iterates over the voxels that intersects the normalized point P
// ---> Preconditions:
// P			= normalized point
// dP			= lookup radius
// cBrick		= the current brick
// ---> Within the loop:
// cWeight		= the weight of the voxel
// cVoxel		= the voxel
// cX,cY,cZ		= the center of the voxel
#define forEachVoxel(__x,__y,__z,__depth)												\
	const	float	cSide		=	side / (float) (1 << __depth);						\
	const	float	xS			=	cSide*__x;											\
	const	float	yS			=	cSide*__y;											\
	const	float	zS			=	cSide*__z;											\
	const	float	dVoxel		=	cSide / (float) BRICK_SIZE;							\
	const	float	invDvoxel	=	1 / dVoxel;											\
	char			*cData		=	(char *) cBrick->voxels;							\
	int				xvs			=	(int) floor(((P[0] - dP) - xS) * invDvoxel);		\
	int				yvs			=	(int) floor(((P[1] - dP) - yS) * invDvoxel);		\
	int				zvs			=	(int) floor(((P[2] - dP) - zS) * invDvoxel);		\
	int				xve			=	(int) floor(((P[0] + dP) - xS) * invDvoxel);		\
	int				yve			=	(int) floor(((P[1] + dP) - yS) * invDvoxel);		\
	int				zve			=	(int) floor(((P[2] + dP) - zS) * invDvoxel);		\
	int				xv,yv,zv;															\
	if (xvs < 0)			xvs = 0;													\
	if (yvs < 0)			yvs = 0;													\
	if (zvs < 0)			zvs = 0;													\
	if (xve >= BRICK_SIZE)	xve = BRICK_SIZE-1;											\
	if (yve >= BRICK_SIZE)	yve = BRICK_SIZE-1;											\
	if (zve >= BRICK_SIZE)	zve = BRICK_SIZE-1;											\
	for (xv=xvs;xv<=xve;xv++) for (yv=yvs;yv<=yve;yv++) for (zv=zvs;zv<=zve;zv++) {		\
		CVoxel		*cVoxel	=	(CVoxel *) (cData + (zv*BRICK_SIZE*BRICK_SIZE + yv*BRICK_SIZE + xv)*(sizeof(CVoxel) + dataSize*sizeof(float)));	\
		const float	cX		=	(xS + (xv + 0.5f)*dVoxel);								\
		const float	cY		=	(yS + (yv + 0.5f)*dVoxel);								\
		const float	cZ		=	(zS + (zv + 0.5f)*dVoxel);								\
		const float	cWeight	=	intersect(P,dP,cX,cY,cZ,dVoxel*0.5f);					\
		if (cWeight == 0) continue;










///////////////////////////////////////////////////////////////////////
// Class				:	CBrickMap
// Method				:	store
// Description			:	Add a point into the structure
// Return Value			:	-
// Comments				:
// Date last edited		:	7/15/2006
void	CBrickMap::store(const float *data,const float *cP,const float *cN,float dP) {
	dP	*=	dPscale;

	int			depth	=	(int) ceil(log(side*LEAF_FACTOR/dP));	// This is the depth we want to add
	CBrick		*cBrick;
	CBrickNode	*cNode;
	vector		P,N;

	if (depth > maxDepth)	depth	=	maxDepth;

	// First, transform the point to world coordinate system
	mulmp(P,world->to,cP);
	assert(inBox(bmin,bmax,P));
	subvv(P,bmin);
	mulmn(N,world->from,cN);
	if (dotvv(N,N) > 0) normalizev(N);
	
	// Iterate over the bricks we want
	forEachBrick(depth)
		int		cDepth,cx,cy,cz;

		// Forcefully create the bricks higher up in the hierarchy and add this point to the voxel data
		for (cx=x,cy=y,cz=z,cDepth=depth;cDepth>=0;cx=cx>>1,cy=cy>>1,cz=cz>>1,cDepth--) {

			// Create the brick
			cBrick	=	findBrick(cx,cy,cz,cDepth,TRUE,&cNode);
			assert(cBrick != NULL);

			// Iterate over the voxels that intersect this one
			forEachVoxel(cx,cy,cz,cDepth)

				// Find the voxel we want to record
				while(TRUE) {
					const float	tmp	=	dotvv(N,cVoxel->N);
					if (((tmp*tmp) >= (normalThreshold*normalThreshold*dotvv(cVoxel->N,cVoxel->N))) && (tmp >= 0)) {
						break;
					} else {
						if (cVoxel->next == NULL) {
							float	*data;
							int		i;

							cVoxel->next	=	(CVoxel *) new char[sizeof(CVoxel) + dataSize*sizeof(float)];
							cVoxel			=	cVoxel->next;
							data			=	(float *) (cVoxel+1);
							initv(cVoxel->N,0);
							cVoxel->weight	=	0;
							cVoxel->next	=	NULL;
							for (i=0;i<dataSize;i++)	data[i]	=	0;
							
							currentMemory	+=	sizeof(CVoxel) + dataSize*sizeof(float);
							
							// Mark the brick as needing new storage
							// Note: we will need to compact the map afterwards
							cNode->fileIndex = -1;
							break;
						} else {
							cVoxel			=	cVoxel->next;
						}
					}
				}

				float	*dest	=	(float *) (cVoxel+1);
				cVoxel->N[0]	+=	N[0]*cWeight;
				cVoxel->N[1]	+=	N[1]*cWeight;
				cVoxel->N[2]	+=	N[2]*cWeight;
				for (int j=0;j<dataSize;j++)	dest[j]	+=	data[j]*cWeight;
				cVoxel->weight	+=	cWeight;
			}
		}
	}
}



///////////////////////////////////////////////////////////////////////
// Class				:	CBrickMap
// Method				:	lookup
// Description			:	Lookup data
// Return Value			:	-
// Comments				:
// Date last edited		:	7/15/2006
void		CBrickMap::lookup(float *data,const float *cP,const float *cN,float dP) {
	dP	*=	dPscale;

	float	depthf		=	log(side*LEAF_FACTOR/dP);
	int		depth		=	(int) floor(depthf);
	float	t			=	depthf - depth;
	float	*data0		=	(float *) alloca(dataSize*2*sizeof(float));
	float	*data1		=	data0 + dataSize;
	vector	P,N;
	int		i;

	// First, transform the point to world coordinate system
	mulmp(P,world->to,cP);
	assert(inBox(bmin,bmax,P));
	subvv(P,bmin);
	mulmn(N,world->from,cN);
	if (dotvv(N,N) > 0) normalizev(N);

	stats.numBrickmapLookups	+=	2;
	
	lookup(P,N,dP,data0,depth);
	lookup(P,N,dP,data1,depth+1);
	for (i=0;i<dataSize;i++)	data[i]	=	data0[i]*(1-t) + data1[i]*t;
}



///////////////////////////////////////////////////////////////////////
// Class				:	CBrickMap
// Method				:	lookup
// Description			:	Lookup a particular depth
// Return Value			:	-
// Comments				:
// Date last edited		:	7/15/2006
void		CBrickMap::lookup(const float *P,const float *N,float dP,float *data,int depth) {
	CBrick	*cBrick;
	float	totalWeight	=	0;
	int		i;

	// Clear the data
	for (i=0;i<dataSize;i++)	data[i]	=	0;

	// Find the brick we want to look at
	forEachBrick(depth)
		int		cDepth,cx,cy,cz;
		
		// iterate all levels until we hit a valid sample
		for (cx=x,cy=y,cz=z,cDepth=depth;cDepth>=0;cx=cx>>1,cy=cy>>1,cz=cz>>1,cDepth--) {
		
			// Get the current brick
			if ((cBrick	=	findBrick(cx,cy,cz,cDepth,FALSE,NULL)) != NULL) {
				forEachVoxel(cx,cy,cz,cDepth)
					
					// Find the voxel with the closest normal
					for (;cVoxel!=NULL;cVoxel=cVoxel->next) {
						const float Ncorrect	=	dotvv(cVoxel->N,cVoxel->N);
						const float	weight		=	cWeight*(Ncorrect*dotvv(cVoxel->N,N) + cVoxel->weight*(1.0f-Ncorrect));

						if (weight > 0) {
							int			j;
							const float	*src	=	(float *) (cVoxel+1);
		
							for (j=0;j<dataSize;j++)	data[j]	+=	src[j]*weight;
							totalWeight	+=	weight;
						}
					}
				}
			}
			
			// If we hit anything, we're done
			if(totalWeight > 0) break;
		}
	}
		
	// Normalize the data
	if (totalWeight > 0) {
		totalWeight	=	1/totalWeight;
		for (i=0;i<dataSize;i++)	data[i]	*=	totalWeight;
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CBrickMap
// Method				:	finalize
// Description			:	Finalize the creation of the brickmap
// Return Value			:	-
// Comments				:
// Date last edited		:	7/15/2006
void				CBrickMap::finalize() {
	int			*stack		=	(int *) alloca(maxDepth*8*5*sizeof(int));
	int			*stackBase	=	stack;
	int			headerOffset;
	CBrickNode	*cNode;
	int			i;

	*stack++	=	0;
	*stack++	=	0;
	*stack++	=	0;
	*stack++	=	0;
	while(stack > stackBase) {
		int		x,y,z,depth;
		CBrick	*cBrick;

		depth	=	*(--stack);
		z		=	*(--stack);
		y		=	*(--stack);
		x		=	*(--stack);

		if ((cBrick=findBrick(x,y,z,depth,FALSE,NULL)) != NULL) {
			CVoxel	*cVoxel;
			int		i;

			// Make sure we iterate over the children
#define	push(__x,__y,__z,__depth)	*stack++	=	__x;	*stack++	=	__y;	*stack++	=	__z;	*stack++	=	__depth;		
			push(2*x,	2*y,	2*z,	depth+1);
			push(2*x+1,	2*y,	2*z,	depth+1);
			push(2*x,	2*y+1,	2*z,	depth+1);
			push(2*x+1,	2*y+1,	2*z,	depth+1);
			push(2*x,	2*y,	2*z+1,	depth+1);
			push(2*x+1,	2*y,	2*z+1,	depth+1);
			push(2*x,	2*y+1,	2*z+1,	depth+1);
			push(2*x+1,	2*y+1,	2*z+1,	depth+1);
#undef push

			// Normalize the voxel data
			for (cVoxel=cBrick->voxels,i=BRICK_SIZE*BRICK_SIZE*BRICK_SIZE;i>0;i--) {
				float			*vdata		=	(float*) (cVoxel+1);
				
				// Deal with normalizing incoherent normals data
				while(TRUE) {
					float		*data		=	(float *) (cVoxel+1);
					if (cVoxel->weight > 0) {
						const float	invWeight	=	1 / cVoxel->weight;
						int			j;
						
						if (dotvv(cVoxel->N,cVoxel->N) > 0) normalizev(cVoxel->N);
						for (j=0;j<dataSize;j++)	data[j]	*=	invWeight;
						cVoxel->weight	=	1;
					}
					
					if (cVoxel->next != NULL) {
						cVoxel = cVoxel->next;
					} else {
						break;
					}
				}
			
				cVoxel			=	(CVoxel*) (vdata + dataSize);
			}
		}
	}
	
	// Flush all the bricks to disk
	brickMapFlush(TRUE);

	// Save the current file position. This is the file index
	fseek(file,0,SEEK_END);
	headerOffset	=	ftell(file);

	// Write the class data here
	writeChannels(file);
	
	// Write the class data
	fwrite(bmin,1,sizeof(vector),file);
	fwrite(bmax,1,sizeof(vector),file);
	fwrite(center,1,sizeof(vector),file);
	fwrite(&side,1,sizeof(float),file);
	fwrite(&maxDepth,1,sizeof(int),file);
	fwrite(activeBricks,BRICK_HASHSIZE,sizeof(CBrickNode *),file);
	for (i=0;i<BRICK_HASHSIZE;i++) {
		for (cNode=activeBricks[i];cNode!=NULL;cNode=cNode->next) {

			// Make sure the node is written to disk
			assert(cNode->brick == NULL);
			assert(cNode->fileIndex != -1);

			fwrite(cNode,1,sizeof(CBrickNode),file);
		}
	}

	// Write the file header at the beginning
	fwrite(&headerOffset,1,sizeof(int),file);

	// Mark the map as non-modifying, meaning
	// we will no longer page out nodes
	// this provides a big speed increase when
	// compressing
	modifying		=	FALSE;
}













///////////////////////////////////////////////////////////////////////
// Class				:	CBrickMap
// Method				:	newBrick
// Description			:	Create a new brick
// Return Value			:	-
// Comments				:
// Date last edited		:	7/15/2006
CBrickMap::CBrick	*CBrickMap::newBrick(int clear) {
	CBrick	*cBrick;

	// If we're using too much memory, swap some bricks out
	if (currentMemory > maxMemory)	brickMapFlush(FALSE);

	// Allocate the brick
	cBrick			=	(CBrick *) new char[sizeof(CBrick) + (sizeof(CVoxel) + dataSize*sizeof(float))*(BRICK_SIZE*BRICK_SIZE*BRICK_SIZE)];
	cBrick->voxels	=	(CVoxel *) (cBrick + 1);

	// Update the used memory
	currentMemory	+=	sizeof(CBrick) + (sizeof(CVoxel) + dataSize*sizeof(float))*(BRICK_SIZE*BRICK_SIZE*BRICK_SIZE);


	if (clear) {
		CVoxel	*cVoxel;
		int		i,j;

		// Clear the voxels
		for (cVoxel=cBrick->voxels,i=0;i<(BRICK_SIZE*BRICK_SIZE*BRICK_SIZE);i++) {
			float	*data;
			initv(cVoxel->N,0);
			cVoxel->weight	=	0;
			cVoxel->next	=	NULL;
			data			=	(float *) (cVoxel+1);
			for (j=0;j<dataSize;j++)	data[j]	=	0;
			cVoxel			=	(CVoxel *) ((char *) cVoxel + sizeof(CVoxel) + dataSize*sizeof(float));
		}
	}

	return cBrick;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CBrickMap
// Method				:	loadBrick
// Description			:	Load a brick
// Return Value			:	-
// Comments				:
// Date last edited		:	7/15/2006
CBrickMap::CBrick	*CBrickMap::loadBrick(int fileIndex) {	
	CBrick	*cBrick	=	newBrick(FALSE);
	CVoxel	*cVoxel,*tVoxel;
	int		i,j;

	stats.numBrickmapCachePageins++;
	
	// Seek to the right position in file
	if (file == NULL)	file	=	ropen(name,"w+",fileBrickMap);
	fseek(file,fileIndex,SEEK_SET);

	unsigned long bs[BRICK_PRESENCE_LONGS];
	unsigned long b;
	
	// work out which top-level voxels are present
	fread(bs,sizeof(unsigned long)*BRICK_PRESENCE_LONGS,1,file);
	
	// read those that are
	for(i=0,cVoxel=cBrick->voxels;i<BRICK_PRESENCE_LONGS;i++){
		b = bs[i];
		
		for(j=BRICK_VOXEL_BATCH;j>0;j--) {
			float *vdata = (float*) (cVoxel + 1);
	
			if (b & 0x80000000L) {
				fread(cVoxel,sizeof(CVoxel) + sizeof(float)*dataSize,1,file);
	
				if (cVoxel->next != NULL) {
					cVoxel->next	=	NULL;
					
					while (TRUE) {
						tVoxel		 = (CVoxel*) new char[sizeof(CVoxel) + dataSize*sizeof(float)];
						currentMemory	+=	sizeof(CVoxel) + dataSize*sizeof(float);
						
						fread(tVoxel,sizeof(CVoxel) + sizeof(float)*dataSize,1,file);
						
						if (tVoxel->next != NULL) {
							tVoxel->next	=	cVoxel->next;
							cVoxel->next	=	tVoxel;
						} else {
							tVoxel->next	=	cVoxel->next;
							cVoxel->next	=	tVoxel;
							break;
						}
					}
				}
			} else {
				// initialize to null any that are not
				cVoxel->weight	=	0;
				cVoxel->next	=	NULL;
				initv(cVoxel->N,0);
			}
			
			b = b<<1;
			
			cVoxel = (CVoxel*) (vdata + dataSize);
		}
	}
	
	if (currentMemory > stats.brickmapPeakMem) 	stats.brickmapPeakMem = currentMemory;

	// Return the brick
	return cBrick;	
}















///////////////////////////////////////////////////////////////////////
// Class				:	CBrickMap
// Method				:	brickMapCompact
// Description			:	This function is called to re-claim some of the memory from the brickmap
// Return Value			:	-
// Comments				:
// Date last edited		:	7/15/2006
void				CBrickMap::compact(const char *outFileName,float maxVariation) {
	int			numNodes;
	CBrickNode	*cNode;
	CVoxel		*cVoxel,*tVoxel;
	CBrick		*cBrick;
	int			i,j,k,vCnt,nullCnt,numCulled;

	FILE		*outfile 	=	ropen(outFileName,"wb+",fileBrickMap);
		
	
	memBegin();
	
	CVoxel		*tempVoxel	=	(CVoxel*)		ralloc(sizeof(CVoxel) + dataSize*sizeof(float));
	CBrickNode	**newHash	=	(CBrickNode**)	ralloc(BRICK_HASHSIZE*sizeof(CBrickNode*));
	float 		*dataMean	=	(float*)		ralloc(2*dataSize*sizeof(float));
	float 		*dataVar	=	dataMean + dataSize;
	
	// Initialize the hash
	for (i=0;i<BRICK_HASHSIZE;i++)  newHash[i] = NULL;
	
	// Collect the loaded bricks into an array
	numCulled	=	0;
	numNodes	=	0;
	nullCnt		=	0;
	for (i=0;i<BRICK_HASHSIZE;i++) {
		
		for (cNode=activeBricks[i];cNode!=NULL;cNode=cNode->next) {
		
			// Make sure we have the data
			if (cNode->brick == NULL) {
				// Get the thing resident
				cNode->brick					=	loadBrick(cNode->fileIndex);
				cNode->brick->referenceNumber	=	referenceNumber;
			}
			cBrick = cNode->brick;
			
			// Calculate variance
			
			for (j=0;j<dataSize;j++) dataMean[j] = dataVar[j] = 0;
			
			vCnt = 0;
			
			for (cVoxel=cBrick->voxels,k=BRICK_SIZE*BRICK_SIZE*BRICK_SIZE;k>0;k--) {
				float			*vdata		=	(float*) (cVoxel+1);
				
				// Deal with normalizing incoherent normals data
				while(TRUE) {
					float		*data		=	(float *) (cVoxel+1);
					
					if(cVoxel->weight >0) {
						for (j=0;j<dataSize;j++)	dataMean[j]	+=	data[j];
						vCnt++;
					}else nullCnt++;

					if (cVoxel->next != NULL) {
						cVoxel = cVoxel->next;
					} else {
						break;
					}
				}
			
				cVoxel			=	(CVoxel*) (vdata + dataSize);
			}
			
			// Skip if we have no data in this brick
			if (vCnt == 0) {
				numCulled++;
				continue;
			}
			
			float invCnt = 1.0f/(float)vCnt;
			for (j=0;j<dataSize;j++)	dataMean[j] *= invCnt;
			
			for (cVoxel=cBrick->voxels,k=BRICK_SIZE*BRICK_SIZE*BRICK_SIZE;k>0;k--) {
				float			*vdata		=	(float*) (cVoxel+1);
				
				// Deal with normalizing incoherent normals data
				while(TRUE) {
					float		*data		=	(float *) (cVoxel+1);
					
					if(cVoxel->weight >0) {
						for (j=0;j<dataSize;j++) {
							float d = (data[j]-dataMean[j]);
							dataVar[j]	+=	d*d;
						}
					}
					
					if (cVoxel->next != NULL) {
						cVoxel = cVoxel->next;
					} else {
						break;
					}
				}
			
				cVoxel			=	(CVoxel*) (vdata + dataSize);
			}
			
			float maxVar = 0;
			for (j=0;j<dataSize;j++) {
				dataVar[j] *=	invCnt;
				dataVar[j] =	sqrtf(dataVar[j]);
				dataVar[j] /=	dataMean[j];
				if (dataVar[j] > maxVar) maxVar = dataVar[j];
			}

			// Do not write this brick if variation too low
			if (maxVar < maxVariation) {
				numCulled++;
				continue;
			}
			
			
			CBrickNode *tNode	=	(CBrickNode*) ralloc(sizeof(CBrickNode));
			
			// Initialize temporary node data over
			*tNode				=	*cNode;
			tNode->next			=	newHash[i];
			newHash[i]			= 	tNode;
			tNode->brick		=	NULL;
			numNodes++;
			
			
			// write it out to a new location
			fseek(outfile,0,SEEK_END);
			tNode->fileIndex	=	ftell(outfile);
			
			unsigned long bs[BRICK_PRESENCE_LONGS];
			unsigned long b;
			
			// Work out for each voxel if there is anything at all
			for (k=0,cVoxel=cBrick->voxels;k<BRICK_PRESENCE_LONGS;k++) {
				b = 0;
				
				for (j=BRICK_VOXEL_BATCH;j>0;j--) {
					float *vdata = (float*) (cVoxel + 1);
					
					b = b<<1;
					
					while (cVoxel != NULL) {
						if (cVoxel->weight > 0){
							b |= 1;
						}
						cVoxel = cVoxel->next;
					}
					
					cVoxel = (CVoxel*) (vdata + dataSize);
				}
				
				bs[k] = b;
			}
			
			// Write the voxel-presence bits
			fwrite(bs,sizeof(unsigned long)*BRICK_PRESENCE_LONGS,1,outfile);
			
			// Write each voxel which exists
			for(j=BRICK_SIZE*BRICK_SIZE*BRICK_SIZE,cVoxel=cBrick->voxels;j>0;j--) {
				float *vdata = (float*) (cVoxel + 1);
				
				int skippedLast = FALSE;
				tVoxel			= NULL;
				
				while (cVoxel != NULL) {
				
					skippedLast = FALSE;
					
					if (cVoxel->weight > 0) {
						fwrite(cVoxel,sizeof(CVoxel)+sizeof(float)*dataSize,1,outfile);
						tVoxel = cVoxel;
					} else {
						skippedLast = TRUE;
					}
					
					cVoxel = cVoxel->next;
				}
				
				if ((skippedLast == TRUE) && (tVoxel != NULL)) {
					// That last voxel we wrote had a bad next value...
					fseek(outfile,-(long)(sizeof(CVoxel)+dataSize*sizeof(float)),SEEK_CUR);
					memcpy(tempVoxel,tVoxel,sizeof(CVoxel)+sizeof(float)*dataSize);
					tempVoxel->next = NULL;
					fwrite(tempVoxel,sizeof(CVoxel)+sizeof(float)*dataSize,1,outfile);
				}
				
				cVoxel = (CVoxel*) (vdata + dataSize);
			}
		}
	}
	//fprintf(stderr,"%d bricks culled.  %d null voxels not written\n",numCulled,nullCnt);
	
	// Write out temporary node hash
	// Save the current file position. This is the file index
	fseek(outfile,0,SEEK_END);
	int headerOffset	=	ftell(outfile);

	// Write the class data here
	writeChannels(outfile);
	
	fwrite(bmin,1,sizeof(vector),outfile);
	fwrite(bmax,1,sizeof(vector),outfile);
	fwrite(center,1,sizeof(vector),outfile);
	fwrite(&side,1,sizeof(float),outfile);
	fwrite(&maxDepth,1,sizeof(int),outfile);
	fwrite(newHash,BRICK_HASHSIZE,sizeof(CBrickNode *),outfile);
	for (i=0;i<BRICK_HASHSIZE;i++) {
		for (cNode=newHash[i];cNode!=NULL;cNode=cNode->next) {

			// Make sure the node is written to disk
			assert(cNode->brick == NULL);
			assert(cNode->fileIndex != -1);

			fwrite(cNode,1,sizeof(CBrickNode),outfile);
		}
	}

	// Write the file header at the beginning
	fwrite(&headerOffset,1,sizeof(int),outfile);
	
	fclose(outfile);

	memEnd();
}



///////////////////////////////////////////////////////////////////////
// Class				:	CBrickMap
// Method				:	brickMapInit
// Description			:	Initialize the brickmaps at the beginning of a frame
// Return Value			:	-
// Comments				:
// Date last edited		:	7/15/2006
void				CBrickMap::brickMapInit(int m) {
	// This function is guaranteed to be called once and only once for each frame
	brickMaps		=	NULL;
	referenceNumber	=	0;
	currentMemory	=	0;
	maxMemory		=	m;
}




///////////////////////////////////////////////////////////////////////
// Class				:	CBrickMap
// Method				:	brickMapFlush
// Description			:	This function is called to re-claim some of the memory from the brickmap
// Return Value			:	-
// Comments				:
// Date last edited		:	7/15/2006
void				CBrickMap::brickMapFlush(int allBricks) {
	int			numNodes;
	CBrickNode	**nodes;
	CBrickNode	*cNode;
	CBrickMap	*cMap;
	int			i;

	memBegin();

	// Collect the loaded bricks into an array
	numNodes	=	0;
	for (cMap=brickMaps;cMap!=NULL;cMap=cMap->nextMap) {
		for (i=0;i<BRICK_HASHSIZE;i++) {
			for (cNode=cMap->activeBricks[i];cNode!=NULL;cNode=cNode->next) {
				if (cNode->brick != NULL)	numNodes++;
			}
		}
	}
	nodes		=	(CBrickNode **) ralloc(numNodes*2*sizeof(CBrickNode *));
	numNodes	=	0;
	for (cMap=brickMaps;cMap!=NULL;cMap=cMap->nextMap) {
		for (i=0;i<BRICK_HASHSIZE;i++) {
			for (cNode=cMap->activeBricks[i];cNode!=NULL;cNode=cNode->next) {
				if (cNode->brick != NULL)	{
					nodes[numNodes*2]	=	cNode;
					nodes[numNodes*2+1]	=	(CBrickNode *) cMap;
					numNodes++;
				}
			}
		}
	}

	// Sort the bricks wrt. to the last reference
	brickQuickSort(nodes,0,numNodes-1);

	// Swap out the bricks
	if (allBricks == FALSE) {
		numNodes						=	numNodes >> 1;
		stats.numBrickmapCachePageouts	+=	numNodes;
	}
	

	// Eliminate nodes
	for (i=0;i<numNodes;i++) {
		CBrickNode	*cNode	=	nodes[i*2];
		CBrickMap	*cMap	=	(CBrickMap *) nodes[i*2+1];
		CVoxel		*cVoxel,*tVoxel;
		int			j;
	
		// Strategy - if we are modifying, save the contents to backing store
		// otherwise, just forget the voxel altogether
		if (cMap->modifying == TRUE) {
			// Write and free the brick
			
			if (cNode->fileIndex == -1)	{
				// If this is the first time we're writing, append it to the end
				fseek(cMap->file,0,SEEK_END);
				cNode->fileIndex	=	ftell(cMap->file);
			} else {
				// Go to the correct position
				fseek(cMap->file,cNode->fileIndex,SEEK_SET);
			}
			
			unsigned long bs[BRICK_PRESENCE_LONGS];
			
			// Write all voxels, do not spend time compressing
			for(j=0;j<BRICK_PRESENCE_LONGS;j++) bs[j] = 0xFFFFFFFFL;
			
			fwrite(bs,sizeof(unsigned long)*BRICK_PRESENCE_LONGS,1,cMap->file);
		
			for(j=BRICK_SIZE*BRICK_SIZE*BRICK_SIZE,cVoxel=cNode->brick->voxels;j>0;j--) {
				float *vdata = (float*) (cVoxel + 1);
			
				fwrite(cVoxel,sizeof(CVoxel) + cMap->dataSize*sizeof(float),1,cMap->file);
		
				while((tVoxel=cVoxel->next) != NULL) {
					cVoxel->next	=	tVoxel->next;
					fwrite(tVoxel,1,sizeof(CVoxel) + cMap->dataSize*sizeof(float),cMap->file);
					delete [] (char *) tVoxel;
				
					currentMemory	-=	sizeof(CVoxel) + cMap->dataSize*sizeof(float);
				}
				
				cVoxel = (CVoxel*) (vdata + cMap->dataSize);
			}
			
			// Free the brick
			delete[] (char*) cNode->brick;
			cNode->brick		=	NULL;

			// Update the used memory
			currentMemory		-=	sizeof(CBrick) + (sizeof(CVoxel) + cMap->dataSize*sizeof(float))*(BRICK_SIZE*BRICK_SIZE*BRICK_SIZE);
		} else {
			// Just free the brick
			
			for(j=BRICK_SIZE*BRICK_SIZE*BRICK_SIZE,cVoxel=cNode->brick->voxels;j>0;j--) {
				float *vdata = (float*) (cVoxel + 1);
			
				while((tVoxel=cVoxel->next) != NULL) {
					cVoxel->next	=	tVoxel->next;
					delete [] (char *) tVoxel;
				
					currentMemory	-=	sizeof(CVoxel) + cMap->dataSize*sizeof(float);
				}
				
				cVoxel = (CVoxel*) (vdata + cMap->dataSize);
			}
			
			// Free the brick
			delete[] (char*) cNode->brick;
			cNode->brick		=	NULL;

			// Update the used memory
			currentMemory		-=	sizeof(CBrick) + (sizeof(CVoxel) + cMap->dataSize*sizeof(float))*(BRICK_SIZE*BRICK_SIZE*BRICK_SIZE);
		}
	}

	memEnd();
}


///////////////////////////////////////////////////////////////////////
// Class				:	CBrickMap
// Method				:	brickMapShutdown
// Description			:	Clear the memory used by the brickmaps
// Return Value			:	-
// Comments				:
// Date last edited		:	7/15/2006
void				CBrickMap::brickMapShutdown() {
	// This function is guaranteed to be called once and only once for each frame
	assert(currentMemory == 0);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CBrickMap
// Method				:	brickQuickSort
// Description			:	Quick sort the bricks wrt. to the referenceNumbers
// Return Value			:	-
// Comments				:
// Date last edited		:	7/15/2006
void			CBrickMap::brickQuickSort(CBrickNode **nodes,int start,int end) {
	int			i,last;
	CBrickNode	*cNode;

	for (last=start,i=start+1;i<=end;i++) {
		if (nodes[i*2]->brick->referenceNumber < nodes[start*2]->brick->referenceNumber) {
			last++;
			cNode			=	nodes[last*2];
			nodes[last*2]	=	nodes[i*2];
			nodes[i*2]		=	cNode;

			cNode			=	nodes[last*2+1];
			nodes[last*2+1]	=	nodes[i*2+1];
			nodes[i*2+1]	=	cNode;
		}
	}

	cNode				=	nodes[last*2];
	nodes[last*2]		=	nodes[start*2];
	nodes[start*2]		=	cNode;

	cNode				=	nodes[last*2+1];
	nodes[last*2+1]		=	nodes[start*2+1];
	nodes[start*2+1]	=	cNode;



	// Speed is not an issue since this is not done very frequently, so recursion is OK
	if ((last-1) > start)
		brickQuickSort(nodes,start,last-1);

	if (end > (last+1))
		brickQuickSort(nodes,last+1,end);
}













///////////////////////////////////////////////////////////////////////
// Function				:	makeTexture3D
// Description			:	This function creates the 3D baed texture from point cloud representation
// Return Value			:	-
// Comments				:
// Date last edited		:	7/16/2006
void	makeTexture3D(const char *src,const char *dest,TSearchpath *searchPath,int n,char **tokens,void **params) {
	char	tempName[OS_MAX_PATH_LENGTH];
	char	fileName[OS_MAX_PATH_LENGTH];
	int		i;
	
	float maxVariation = 0.002f;
	for(i =0;i<n;i++){
		if(!strcmp(tokens[i],"maxerror")){
			maxVariation = ((float*)params[i])[0];
		}
	}
	
	// If not initialized already, init the brick memory manager
	// Use a large memory limit when creating brickmaps
	// Note: needed as RiMakeXYZ can only be called outside a frame, and then
	// the shading context is gone
	CBrickMap::brickMapInit(100000000);
	
	if (currentRenderer->locateFile(fileName,src,searchPath)) {
		FILE *in;
		if ((in	=	ropen(fileName,"rb",filePointCloud,TRUE)) != NULL) {
			// create backing store in a temp file
			// FIXME: make osTempname not always prefix dir
			sprintf(tempName,"%s.tmp",dest);
		
			CXform		*dummyXform	=	new CXform;	dummyXform->attach();
			CPointCloud *cPtCloud	=	new CPointCloud(filePointCloud,dummyXform,in);
			CBrickMap	*cBMap		=	new CBrickMap(tempName,cPtCloud->bmin,cPtCloud->bmax,dummyXform,cPtCloud->channels,cPtCloud->numChannels);
			
			float **dataPointers =	cPtCloud->dataPointers->array;
			for (i=1;i<cPtCloud->numPhotons;i++) {
				CPointCloudPoint	*p = cPtCloud->photons + i;
				float			 	*C = dataPointers[p->entryNumber];
				cBMap->store(C,p->P,p->N,p->dP);
			}
			
			cBMap->finalize();
			
			// compact to the final file
			cBMap->compact(dest,maxVariation);
			
			delete cBMap;
			delete cPtCloud;
			dummyXform->detach();
			// clean up
			osDeleteFile(tempName);
		} else {
			error(CODE_BADTOKEN,"Point cloud file \"%s\" could not be opened\n");
		}
	} else {
		error(CODE_BADTOKEN,"Point cloud file \"%s\" not found\n");
	}
	
	CBrickMap::brickMapShutdown();
}
