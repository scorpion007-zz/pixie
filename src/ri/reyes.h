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
//  File				:	reyes.h
//  Classes				:	CReyes
//  Description			:	The rasterizer class
//
////////////////////////////////////////////////////////////////////////
#ifndef REYES_H
#define REYES_H

#include "common/global.h"
#include "shading.h"
#include "object.h"
#include "renderer.h"
#include "ri_config.h"

// Note:
// The low bits are spliced with the zfilter mode and used to dispatch in stochastic hider
// high bits are used in the primitive rasterization code to modify behavior

const	unsigned int	RASTER_MOVING			=	1 << 0;		// The primitive is moving
const	unsigned int	RASTER_TRANSPARENT		=	1 << 1;		// The primitive is transparent
const	unsigned int	RASTER_POINT			=	1 << 2;		// The primitive is a point
const	unsigned int	RASTER_UNSHADED			=	1 << 3;		// The primitive has not been shaded (only displaced)
const	unsigned int	RASTER_FOCALBLUR		=	1 << 4;		// The primitive has focalblur
const	unsigned int	RASTER_EXTRASAMPLES		=	1 << 5;		// The primitive has extra samples to compute
const	unsigned int	RASTER_MATTE			=	1 << 6;		// The primitive is a matte
const	unsigned int	RASTER_LOD				=	1 << 7;		// The primitive has LOD
const	unsigned int	RASTER_UNDERCULL		=	1 << 8;		// The primitive requires underculling
const	unsigned int	RASTER_XTREME			=	1 << 9;		// The primitive has extreme motion blur/depth of field
const	unsigned int	RASTER_GLOBAL_MASK		=	(1 << 10) - 1;// This mask is used to block the lower fields

const	unsigned int	RASTER_HIGHBITS_SHIFT	=	10;			// The shift needed to put bits in the higher fields
const	unsigned int	RASTER_DEPTHFILT_MASK	=	1;

const	unsigned int	RASTER_DRAW_FRONT		=	1 << 10;	// Draw the front of the primitive
const	unsigned int	RASTER_DRAW_BACK		=	1 << 11;	// Draw the back of the primitive
const	unsigned int	RASTER_SHADE_HIDDEN		=	1 << 12;	// Shade the primitive even if occluded
const	unsigned int	RASTER_SHADE_BACKFACE	=	1 << 13;	// Shade the primitive even if backfacing


///////////////////////////////////////////////////////////////////////
// Class				:	CReyes
// Description			:	This class is implementes a REYES like scan
//							line renderer
// Comments				:
class	CReyes : public CShadingContext {
protected:

	///////////////////////////////////////////////////////////////////////
	// Class				:	CRasterPatch
	// Description			:	Holds an object associated with a bucket
	// Comments				:	The same instance of this class may be associated with multiple buckets in multiple threads
	class	CRasterObject {
	public:
			CObject				*object;				// The object
			CRasterObject		**next;					// The next object (one for each thread)
			int					refCount;				// The number of threads working on this object
			int					diced;					// TRUE if this object has already been diced
			int					grid;					// TRUE if this is a grid
			int					cached;					// TRUE if this is a cached object

			int					xbound[2],ybound[2];	// The bound of the object on the screen, in samples
			float				zmin;					// The minimum z coordinate of the object (used for occlusion culling)
			TMutex				mutex;					// To secure the object
			
	};	

	///////////////////////////////////////////////////////////////////////
	// Class				:	CRasterGrid
	// Description			:	This class encapsulates a shading grid
	//							line renderer
	// Comments				:
	class	CRasterGrid : public CRasterObject {
	public:
			float				*vertices;				// Array of vertices
			int					*bounds;				// The bound of the primitive (4 numbers per primitive)
			float				*sizes;					// The size of the primitive (only makes sense for points)
			EShadingDim			dim;					// Dimensionality (0,1 or 2)
			float				umin,umax,vmin,vmax;	// The parametric range
			int					udiv,vdiv;				// The number of division
			int					numVertices;			// The number of vertices
			int					flags;					// The primitive flags
	};


	///////////////////////////////////////////////////////////////////////
	// Class				:	CPqueue
	// Description			:	Priority queue specifically written for CRasterObject
	// Comments				:	I could have used the template in containers.h, but this one allows me to defer objects directly
	class CPqueue  {
	public:
								CPqueue(int ss=100)	{
									stepSize	=	ss;
									maxItems	=	stepSize;
									numItems	=	1;
									allItems	=	new CRasterObject*[maxItems];
								}

								~CPqueue()	{
									delete [] allItems;
								}

					void		insert(CRasterObject *cObject) {
									int i,j;

									// Expand the buffer
									if (numItems >= maxItems) {
										CRasterObject	**newItems;
										maxItems		+=	stepSize;
										newItems		=	new CRasterObject*[maxItems+1];
										memcpy(newItems,allItems,numItems*sizeof(CRasterObject*));
										delete [] allItems;
										allItems		=	newItems;
										stepSize		*=	2;
									}
					
									// Insert the item
									i	= numItems++;
									j	= i >> 1;
									while ((i > 1) && (cObject->zmin < allItems[j]->zmin)) {
										allItems[i]	=	allItems[j];
										i			=	j;
										j			=	i >> 1;

									}

									allItems[i]		=	cObject;
								}
					
				CRasterObject	*get(TMutex &mutex) {
									int				i = 1, j;
									CRasterObject	*lItem,*cItem;
								
									osLock(mutex);

									if (numItems <= 1) {
										cItem	=	NULL;
									} else {
										cItem	=	allItems[1];
									
										numItems--;
										lItem	=	allItems[numItems];

										while (i <= numItems / 2) {
											j = 2 * i;
											if (j >= numItems) break;

											if ((j < (numItems-1)) && (allItems[j]->zmin > allItems[j+1]->zmin))
												j++;

											if (allItems[j]->zmin > lItem->zmin)
												break;

											allItems[i]	=	allItems[j];
											i			=	j;
										}
										allItems[i]				=	lItem;
									}

									if (cItem != NULL) osUnlock(mutex);

									return cItem;
								}

		CRasterObject			**allItems;					// Array of the heap
		int						numItems,maxItems,stepSize;	// Misc junk
	};


	///////////////////////////////////////////////////////////////////////
	// Class				:	CBucket
	// Description			:	Holds a bucket
	// Comments				:
	class	CBucket {
	public:
								CBucket();
								~CBucket();

			CRasterObject		*objects;				// The list of objects waiting to be rendered
			CPqueue				*queue;					// If this is not null, we're currently rendering this bucket
	};


public:

								CReyes(int thread);
								~CReyes();

								// This function is called to to render
	void						renderingLoop();

								// The following functions must be overriden by the child rasterizer
	virtual	void				rasterBegin(int,int,int,int,int)			=	0;
	virtual	void				rasterDrawPrimitives(CRasterGrid *)			=	0;
	virtual	void				rasterEnd(float *,int)						=	0;
	
								// The following can be called from the "dice" function to insert an object into the scene
	void						drawObject(CObject *);									// Draw an object
	void						drawGrid(CSurface *,int,int,float,float,float,float);	// Draw a grid
	void						drawPoints(CSurface *,int);								// Draw points (RiPoints)

								// Some stats
	int							numGridsRendered;
	int							numQuadsRendered;
	int							numGridsShaded;
	int							numGridsCreated;
	int							numVerticesCreated;
protected:
	float						maxDepth;										// The maximum opaque depth in the current bucket

	static	int					extraPrimitiveFlags;							// These are the extra primitive flags
	static	int					numVertexSamples;								// The number of samples per pixel	

	void						shadeGrid(CRasterGrid *,int);					// Called by the child to force the shading of a grid

	virtual int					probeArea(int *xbound,int *ybound, int bw, int bh, int bl, int bt, float zmin) {
									return TRUE;
								}

private:
	void						copyPoints(int,float **,float *,int);			// Data movement (copy P only)
	void						copySamples(int,float **,float *,int);			// Data movement (copy the color + opacity + extra samples)

	void						insertObject(CRasterObject *object);			// Add an object into the system
	void						insertGrid(CRasterGrid *,int);					// Insert a grid into the correct bucket

	CRasterObject				*newObject(CObject *);							// Create a new object
	CRasterGrid					*newGrid(CSurface *,int,int,int);				// Create a new grid
	void						deleteObject(CRasterObject *);					// Delete an object (the object can also be a grid)
	
	void						render();										// Render the current bucket
	void						skip();											// Skip the current bucket

	CBucket						***buckets;										// All buckets
	TMutex						bucketMutex;									// Controls the accesses to the buckets

	int							bucketPixelLeft;								// Left of the current bucket in pixels
	int							bucketPixelTop;									// Top of the current bucket in pixels
	int							bucketPixelWidth;								// Width of the current bucket in pixels
	int							bucketPixelHeight;								// Height of the current bucket in pixels
	int							tbucketLeft;									// Left of the current bucket in samples
	int							tbucketTop;										// Right of the current bucket in samples
	int							tbucketRight;
	int							tbucketBottom;
	

				///////////////////////////////////////////////////////////////////////
				// Class				:	CReyes
				// Method				:	distance2samples
				// Description			:	Project distances into the sample space
				// Return Value			:
				// Comments				:	(inline for speed)
				inline void		distance2samples(int n,float *dist,float *P) {
									if(CRenderer::projection == OPTIONS_PROJECTION_PERSPECTIVE) {
										for (;n>0;n--,P+=3,dist++) {
											*dist		=	CRenderer::dSampledx*CRenderer::imagePlane*dist[0]/P[COMP_Z];
										}
									} else {
										for (;n>0;n--,P+=3,dist++) {
											*dist		=	CRenderer::dSampledx*dist[0];
										}
									}
								}

				///////////////////////////////////////////////////////////////////////
				// Class				:	CReyes
				// Method				:	camera2samples
				// Description			:	Project from camera space into the sample space
				// Return Value			:
				// Comments				:	(inline for speed)
				inline void		camera2samples(int n,float *P) {
									if(CRenderer::projection == OPTIONS_PROJECTION_PERSPECTIVE) {
										for (;n>0;n--,P+=3) {
											P[COMP_X]	=	(CRenderer::imagePlane*P[COMP_X]/P[COMP_Z] - CRenderer::pixelLeft)*CRenderer::dSampledx;
											P[COMP_Y]	=	(CRenderer::imagePlane*P[COMP_Y]/P[COMP_Z] - CRenderer::pixelTop)*CRenderer::dSampledy;
										}
									} else {
										for (;n>0;n--,P+=3) {
											P[COMP_X]	=	(P[COMP_X] - CRenderer::pixelLeft)*CRenderer::dSampledx;
											P[COMP_Y]	=	(P[COMP_Y] - CRenderer::pixelTop)*CRenderer::dSampledy;
										}
									}
								}

				///////////////////////////////////////////////////////////////////////
				// Class				:	CReyes
				// Method				:	camera2samples
				// Description			:	Project from camera space into the sample space
				// Return Value			:
				// Comments				:	(inline for speed)
				inline void		camera2samples(float *P) {
									if(CRenderer::projection == OPTIONS_PROJECTION_PERSPECTIVE) {
										P[COMP_X]	=	CRenderer::imagePlane*P[COMP_X]/P[COMP_Z];
										P[COMP_Y]	=	CRenderer::imagePlane*P[COMP_Y]/P[COMP_Z];
									}

									P[COMP_X]	=	(P[COMP_X] - CRenderer::pixelLeft)*CRenderer::dSampledx;
									P[COMP_Y]	=	(P[COMP_Y] - CRenderer::pixelTop)*CRenderer::dSampledy;
								}

};

#endif

