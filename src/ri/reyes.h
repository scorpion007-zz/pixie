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
//  File				:	reyes.h
//  Classes				:	CReyes
//  Description			:	The rasterizer class
//
////////////////////////////////////////////////////////////////////////
#ifndef REYES_H
#define REYES_H

#include "common/global.h"
#include "output.h"
#include "shading.h"
#include "object.h"

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
const	unsigned int	RASTER_GLOBAL_MASK		=	(1 << 9) - 1;// This mask is used to block the lower fields

const	unsigned int	RASTER_HIGHBITS_SHIFT	=	9;			// The shift needed to put bits in the higher fields
const	unsigned int	RASTER_DEPTHFILT_MASK	=	3;			// Mask for the depth filter

const	unsigned int	RASTER_DRAW_FRONT		=	1 << 9;		// Draw the front of the primitive
const	unsigned int	RASTER_DRAW_BACK		=	1 << 10;	// Draw the back of the primitive
const	unsigned int	RASTER_SHADE_HIDDEN		=	1 << 11;	// Shade the primitive even if occluded
const	unsigned int	RASTER_SHADE_BACKFACE	=	1 << 12;	// Shade the primitive even if backfacing


///////////////////////////////////////////////////////////////////////
// Class				:	CReyes
// Description			:	This class is implementes a REYES like scan
//							line renderer
// Comments				:
// Date last edited		:	4/25/2004
class	CReyes : public CShadingContext {
protected:

	///////////////////////////////////////////////////////////////////////
	//	The misc data structures used in the scan line rendering
	///////////////////////////////////////////////////////////////////////
	typedef struct TRasterPrimitive {
			int					xbound[2],ybound[2];	// The bound on the screen, in samples
			float				*v0;					// The first vertex index (used for sorting)
			T64					data[2];				// The data field - primitive dependent data area
	} TRasterPrimitive;



	///////////////////////////////////////////////////////////////////////
	// Class				:	CRasterGrid
	// Description			:	This class encapsulates a shading grid
	//							line renderer
	// Comments				:
	// Date last edited		:	9/17/2004
	class	CRasterGrid {
	public:
		CSurface				*object;				// The object responsible for the grid
		int						dim;					// Dimensionality (0,1 or 2)
		float					umin,umax,vmin,vmax;	// The parametric range
		int						udiv,vdiv;				// The number of division
		int						numVertices;			// The number of vertices
		float					*vertices;				// Array of vertices
		int						numPrimitives;			// Number of primitives
		TRasterPrimitive		*primitives;			// Array of primitives on this grid
		int						flags;					// The primitive flags
	};



	///////////////////////////////////////////////////////////////////////
	// Class				:	CRasterPatch
	// Description			:	Holds an object
	// Comments				:
	// Date last edited		:	1/30/2002
	class	CRasterObject {
	public:
			CObject				*object;				// The object
			CRasterGrid			*grid;					// The grid
			CRasterObject		*next;					// The next object
			int					xbound[2],ybound[2];	// The bound of the object on the screen, in samples
			float				zmin;					// The minimum z coordinate of the object (used for occlusion culling)
	};	

	///////////////////////////////////////////////////////////////////////
	// Class				:	CBucket
	// Description			:	Holds a bucket
	// Comments				:
	// Date last edited		:	1/30/2002
	class	CBucket {
	public:
								CBucket();
								~CBucket();

			CRasterObject		*objects;				// The list of objects waiting to be rendered
	};


	///////////////////////////////////////////////////////////////////////
	// Class				:	CPqueue
	// Description			:	Priority queue specifically written for CRasterObject
	// Comments				:	I could have used the template in containers.h, but this one allows me to defer objects directly
	// Date last edited		:	9/20/2004
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
					
				CRasterObject	*get() {
									int				i = 1, j;
									CRasterObject	*lItem,*cItem;

									if (numItems <= 1) return NULL;
								
									cItem		=	allItems[1];
								
									numItems--;
									lItem		=	allItems[numItems];

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
									return cItem;
								}

					CRasterObject	**allItems;					// Array of the heap
					int				numItems,maxItems,stepSize;	// Misc junk
				};








public:

								CReyes(COptions *,CXform *,SOCKET,unsigned int);
								~CReyes();

								// The main hider interface
	void						renderFrame();									// Right after world end to force rendering of the entire frame

								// The following functions must be overriden by the child rasterizer
	virtual	void				rasterBegin(int,int,int,int)				=	0;
	virtual	void				rasterDrawPrimitives(CRasterGrid *)			=	0;
	virtual	void				rasterEnd(float *)							=	0;
	
	
	void						drawObject(CObject *,const float *,const float *);		// Draw an object
	void						drawGrid(CSurface *,int,int,float,float,float,float);	// Draw a grid
	void						drawRibbon(CSurface *,int,float,float);					// Draw a ribbon (RiCurves)
	void						drawPoints(CSurface *,int);								// Draw points (RiPoints)

protected:
	float						maxDepth;										// The maximum opaque depth in the current bucket
	float						culledDepth;									// The depth of the closest culled object
	int							xSampleOffset,ySampleOffset;					// The amount of offset around each bucket in samples

	void						shadeGrid(CRasterGrid *,int);					// Called by the child to force the shading of a grid
private:
	void						copyPoints(int,float **,float *,int);			// Data movement
	void						copySamples(int,float **,float *,int);

	void						makeRibbon(int,float *,float *,const float *,const float *,const float *,int);

	CRasterGrid					*newGrid(CSurface *,int,int);					// Create a new grid
	void						deleteGrid(CRasterGrid *);						// Delete a grid
	void						insertGrid(CRasterGrid *,int);					// Insert a grid into the correct bucket

	void						render();										// Render the current bucket
	void						skip();											// Skip the current bucket
	
	int							numGrids;										// The number of grids allocated
	int							numObjects;										// The number of objects allocated

	CBucket						***buckets;										// All buckets

	int							numVertexSamples;								// The number of samples per pixel
	int							enableMotionBlur;								// TRUE if the motion blur has to be enabled
	int							extraPrimitiveFlags;							// These are the extra primitive flags
	int							xBucketsMinusOne;								// xBuckets-1
	int							yBucketsMinusOne;								// yBuckets-1

	float						dSampledx,dSampledy;							// dSample / dx, dSample / dy
																				// The clipping region in samples
	float						sampleClipRight,sampleClipLeft,sampleClipTop,sampleClipBottom;

	float						invBucketSampleWidth,invBucketSampleHeight;		// The 1 / sample

	int							bucketPixelLeft;								// Left of the current bucket in pixels
	int							bucketPixelTop;									// Top of the current bucket in pixels
	int							bucketPixelWidth;								// Width of the current bucket in pixels
	int							bucketPixelHeight;								// Height of the current bucket in pixels
	int							tbucketLeft;									// Left of the current bucket in samples
	int							tbucketTop;										// Right of the current bucket in samples
	int							tbucketRight;
	int							tbucketBottom;

				///////////////////////////////////////////////////////////////////////
				// Class				:	COutput
				// Method				:	distance2samples
				// Description			:	Project distances into the sample space
				// Return Value			:
				// Comments				:	(inline for speed)
				// Date last edited		:	7/4/2001
				inline void		distance2samples(int n,float *dist,float *P) {
									if(projection == OPTIONS_PROJECTION_PERSPECTIVE) {
										for (;n>0;n--,P+=3) {
											*dist++		=	dSampledx*imagePlane*dist[0]/P[COMP_Z];
										}
									} else {
										for (;n>0;n--,P+=3) {
											*dist++		=	dSampledx*dist[0];
										}
									}
								}

				///////////////////////////////////////////////////////////////////////
				// Class				:	COutput
				// Method				:	camera2samples
				// Description			:	Project from camera space into the sample space
				// Return Value			:
				// Comments				:	(inline for speed)
				// Date last edited		:	7/4/2001
				inline void		camera2samples(int n,float *P) {
									if(projection == OPTIONS_PROJECTION_PERSPECTIVE) {
										for (;n>0;n--,P+=3) {
											P[COMP_X]	=	(imagePlane*P[COMP_X]/P[COMP_Z] - pixelLeft)*dSampledx;
											P[COMP_Y]	=	(imagePlane*P[COMP_Y]/P[COMP_Z] - pixelTop)*dSampledy;
										}
									} else {
										for (;n>0;n--,P+=3) {
											P[COMP_X]	=	(P[COMP_X] - pixelLeft)*dSampledx;
											P[COMP_Y]	=	(P[COMP_Y] - pixelTop)*dSampledy;
										}
									}
								}

				///////////////////////////////////////////////////////////////////////
				// Class				:	COutput
				// Method				:	camera2samples
				// Description			:	Project from camera space into the sample space
				// Return Value			:
				// Comments				:	(inline for speed)
				// Date last edited		:	7/4/2001
				inline void		camera2samples(float *P) {
									if(projection == OPTIONS_PROJECTION_PERSPECTIVE) {
										P[COMP_X]	=	imagePlane*P[COMP_X]/P[COMP_Z];
										P[COMP_Y]	=	imagePlane*P[COMP_Y]/P[COMP_Z];
									}

									P[COMP_X]	=	(P[COMP_X] - pixelLeft)*dSampledx;
									P[COMP_Y]	=	(P[COMP_Y] - pixelTop)*dSampledy;
								}
};

#endif
