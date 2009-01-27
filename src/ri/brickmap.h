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
//  File				:	brickmap.h
//  Classes				:	CBrickMap
//  Description			:	The implementation of a 3D texture
//
////////////////////////////////////////////////////////////////////////
#ifndef BRICKMAP_H
#define BRICKMAP_H

#include "common/global.h"
#include "common/algebra.h"
#include "common/containers.h"
#include "options.h"
#include "stats.h"
#include "texture3d.h"

// Forward

class CBrickMapGeometry;

// Some hard coded constants to make our life easier
#define	BRICK_SHIFT				3
#define	BRICK_SIZE				8
#define	BRICK_AND				7
#define BRICK_HASHSIZE			2048	// FIXME: We may want to make this adaptive depending on the size

#define BRICK_PRESENCE_LONGS	16
#define BRICK_VOXEL_BATCH 		32

#define BRICKFLAGS_CULLED

///////////////////////////////////////////////////////////////////////
// Class				:	CBrickMap
// Description			:	Implements a 3D texture
// Comments				:
class	CBrickMap : public CTexture3d {


	///////////////////////////////////////////////////////////////////////
	// Class				:	CVoxel
	// Description			:	Holds a voxel data
	// Comments				:	The data is implicitly stored after the voxel in memory
	class CVoxel {
	public:
		CVoxel			*next;				// The next voxel in the list if incoherent
		float			weight;				// The weight of the voxel
		vector			N;					// The normal vector of the voxel
		// 5 * 4 bytes (ugly)
	};

	///////////////////////////////////////////////////////////////////////
	// Class				:	CBrick
	// Description			:	Holds a brick
	// Comments				:
	class CBrick {
	public:
		CVoxel			*voxels;			// The brick data
		CBrick			*next;				// Next brick in the list (not absolutely necessary)
		int				referenceNumber;	// The reference counter
		// 3 * 4 bytes (ugly)
	};

	///////////////////////////////////////////////////////////////////////
	// Class				:	CBrickNode
	// Description			:	Holds a hash bucket entry for a bucket
	// Comments				:	FIXME: We should make this structure 16 bytes (it is currently 20 bytes)
	class CBrickNode {
	public:
		CBrick			*brick;				// The brick (NULL if on disk)
		CBrickNode		*next;				// The next brick in the hash bucket
		short			x,y,z,d;			// The spatial index of the node
		int				fileIndex;			// The location in the master file
		// 5 * 4 bytes (ugly)
	};

public:
								CBrickMap(FILE *in,const char *name,const float *from,const float *to);
								CBrickMap(const char *name,const float *bmin,const float *bmax,const float *from,const float *to,const float *toNDC,CChannel *channels,int numChannels,int maxDepth);
			virtual				~CBrickMap();
			
								///////////////////////////////////////////////////////////////////////
								// Class				:	CBrickMap
								// Method				:	findBrick
								// Description			:	Locate a brick given it's spatial index
								// Return Value			:	The brick if found
								// Comments				:
			inline	CBrick		*findBrick(int x,int y,int z,int d,int forceCreate,CBrickNode **n) {
									int			key		=	(x + y + z + d) & (BRICK_HASHSIZE-1);	// FIXME: this is a horrible key
									CBrickNode	*cNode	=	activeBricks[key];

									// Increase the reference number
									referenceNumber++;

									// Find the brick in the hash if exists
									for (;cNode!=NULL;cNode=cNode->next) {
										if (!(	(x ^ cNode->x) |
												(y ^ cNode->y) |
												(z ^ cNode->z) |
												(d ^ cNode->d))) {

											assert(x == cNode->x);
											assert(y == cNode->y);
											assert(z == cNode->z);
											assert(d == cNode->d);

											// We found the node, make sure the brick is in memory
											if (cNode->brick == NULL) {
												assert(cNode->fileIndex != -1);
												cNode->brick = loadBrick(cNode->fileIndex);
											} else {
												atomicIncrement(&stats.numBrickmapCacheHits);
											}

											if (n != NULL) *n = cNode;
											
											// Return the brick
											cNode->brick->referenceNumber	=	referenceNumber;
											return cNode->brick;
										}
									}
							
									
									if (forceCreate) {
										// Allocate a new node and brick
										cNode				=	new CBrickNode;
										cNode->brick		=	newBrick(TRUE);
										cNode->x			=	(short) x;
										cNode->y			=	(short) y;
										cNode->z			=	(short) z;
										cNode->d			=	(short) d;
										cNode->fileIndex	=	-1;					// We're not in the file yet
										cNode->next			=	activeBricks[key];
										activeBricks[key]	=	cNode;
								
										// Return this new brick
										cNode->brick->referenceNumber	=	referenceNumber;
										return cNode->brick;
									} else {
										// No joy, the data doesn't exist
										return NULL;
									}
								}
								
								///////////////////////////////////////////////////////////////////////
								// Class				:	CBrickMap
								// Method				:	checkBrick
								// Description			:	Locate a brick given it's spatial index
								// Return Value			:	TRUE if found
								// Comments				:
			inline	int			checkBrick(int x,int y,int z,int d,CBrickNode **n) {
									int			key		=	(x + y + z + d) & (BRICK_HASHSIZE-1);	// FIXME: this is a horrible key
									CBrickNode	*cNode	=	activeBricks[key];

									// Find the brick in the hash if exists
									for (;cNode!=NULL;cNode=cNode->next) {
										if (!(	(x ^ cNode->x) |
												(y ^ cNode->y) |
												(z ^ cNode->z) |
												(d ^ cNode->d))) {

											assert(x == cNode->x);
											assert(y == cNode->y);
											assert(z == cNode->z);
											assert(d == cNode->d);

											// We found the node, make sure the brick is in memory
											if (cNode->brick == NULL) {
												assert(cNode->fileIndex != -1);
												cNode->brick = loadBrick(cNode->fileIndex);
											} else {
												atomicIncrement(&stats.numBrickmapCacheHits);
											}

											if (n != NULL) *n = cNode;
											
											return TRUE;
										}
									}
									return FALSE;
								}

			void				lookup(float *data,const float *P,const float *N,float dP);
			void				lookup(float *,const float *,const float *,const float *,const float *,CShadingContext *) {	assert(FALSE);	}
			void				store(const float *data,const float *P,const float *N,float dP);
				
			void				finalize();
			void				compact(const char*,float);

			void				draw();
			void				bound(float *bmin,float *bmax);
			int					keyDown(int key);

			// Some global static functions for the renderer interface
	static	void				initBrickMap(int maxMemory = 10000000);
	static	void				flushBrickMap(int all=FALSE);
	static	void				shutdownBrickMap();
protected:
			void				lookup(const float *P,const float *N,float dP,float *data,int depth,float normalFactor);
			void				flushBricks(int allBricks);		// Free memory by flushing bricks
			CBrick				*newBrick(int clear);			// Allocate a brick
			CBrick				*loadBrick(int fileIndex);		// Load a brick
			
			float				normalThreshold;				// The normal threshold for incoherent normals
			FILE				*file;							// The file where we keep the hierarchy (may be NULL)
			vector				bmin,bmax;						// The bounding box of the scene (has to be a cube)
			vector				center;							// The center of the cube
			float				side,invSide;					// The size of one side
			CBrickNode			*activeBricks[BRICK_HASHSIZE];	// x,y,z,d -> brick hash array
			int					maxDepth;						// The maximum depth of the structure
			CBrickMap			*nextMap;						// Maintain a linked list of brickmaps
			int					modifying;
			TMutex				mutex;


																// Some static variables

	static	CBrickMap			*brickMaps;						// The list of brick maps
	static	int					referenceNumber;				// The last access number
	static	int					currentMemory;					// The amount of used memory
	static	int					maxMemory;						// The maximum amount of memory to allocate
	static	int					detailLevel;					// The brickmap detail level for visualization
	static	int					drawType;						// Which type to draw
	static	int					drawChannel;					// Which channel to draw;


	static	void				brickQuickSort(CBrickNode **nodes,int start,int end);
	
	friend class CBrickMapGeometry;
};



void	makeBrickMap(int n,const char **src,const char *dest,TSearchpath *searchPath,int numTokens,const char **tokens,const void **params);


#endif

