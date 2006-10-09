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

class CBrickMapView;

// Some hard coded constants to make our life easier
#define	BRICK_SHIFT				3
#define	BRICK_SIZE				8
#define	BRICK_AND				7
#define BRICK_HASHSIZE			2048	// FIXME: We may want to make this adaptive depending on the size

#define BRICK_PRESENCE_LONGS	16
#define BRICK_VOXEL_BATCH 		32


///////////////////////////////////////////////////////////////////////
// Class				:	CBrickMap
// Description			:	Implements a 3D texture
// Comments				:
// Date last edited		:	7/15/2006
class	CBrickMap : public CTexture3d {


	///////////////////////////////////////////////////////////////////////
	// Class				:	CVoxel
	// Description			:	Holds a voxel data
	// Comments				:	The data is implicitly stored after the voxel in memory
	// Date last edited		:	7/15/2006
	class CVoxel {
	public:
		float			weight;				// The weight of the voxel
		vector			N;					// The normal vector of the voxel
		CVoxel			*next;				// The next voxel in the list if incoherent
		// 5 * 4 bytes (ugly)
	};

	///////////////////////////////////////////////////////////////////////
	// Class				:	CBrick
	// Description			:	Holds a brick
	// Comments				:
	// Date last edited		:	7/15/2006
	class CBrick {
	public:
		CVoxel			*voxels;			// The brick data
		int				referenceNumber;	// The reference counter
		CBrick			*next;				// Next brick in the list (not absolutely necessary)
		// 3 * 4 bytes (ugly)
	};

	///////////////////////////////////////////////////////////////////////
	// Class				:	CBrickNode
	// Description			:	Holds a hash bucket entry for a bucket
	// Comments				:	FIXME: We should make this structure 16 bytes (it is currently 20 bytes)
	// Date last edited		:	7/15/2006
	class CBrickNode {
	public:
		CBrick			*brick;				// The brick (NULL if on disk)
		short			x,y,z,d;			// The spatial index of the node
		int				fileIndex;			// The location in the master file
		CBrickNode		*next;				// The next brick in the hash bucket
		// 5 * 4 bytes (ugly)
	};

public:
								CBrickMap(FILE *in,const char *name,CXform *world);
								CBrickMap(const char *name,const float *bmin,const float *bmax,CXform *world,CTexture3dChannel*,int);
			virtual				~CBrickMap();
			
								///////////////////////////////////////////////////////////////////////
								// Class				:	CBrickMap
								// Method				:	findBrick
								// Description			:	Locate a brick given it's spatial index
								// Return Value			:	The brick if found
								// Comments				:
								// Date last edited		:	7/15/2006
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
												stats.numBrickmapCacheHits++;
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

			void				lookup(float *data,const float *P,const float *N,float dP);
			void				store(const float *data,const float *P,const float *N,float dP);
			void				finalize();
			void				compact(const char*,float);

			void				draw();
			void				bound(float *bmin,float *bmax);
			int					keyDown(int key);

			// Some global static functions for the renderer interface
	static	void				brickMapInit(int maxMemory = 10000000);
	static	void				brickMapFlush(int all=FALSE);
	static	void				brickMapShutdown();
protected:
			void				lookup(const float *P,const float *N,float dP,float *data,int depth);
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


																// Some static variables

	static	CBrickMap			*brickMaps;						// The list of brick maps
	static	int					referenceNumber;				// The last access number
	static	int					currentMemory;					// The amount of used memory
	static	int					maxMemory;						// The maximum amount of memory to allocate
	static	int					detailLevel;					// The brickmap detail level for visualization

	static	void				brickQuickSort(CBrickNode **nodes,int start,int end);
	
	friend class CBrickMapView;
};



void	makeTexture3D(const char *src,const char *dest,TSearchpath *searchPath,int n,char **tokens,void **params);


#endif
