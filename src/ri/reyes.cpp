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
//  File				:	reyes.cpp
//  Classes				:	CReyes
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "rendererc.h"
#include "error.h"
#include "ri.h"
#include "stats.h"
#include "memory.h"
#include "points.h"
#include "reyes.h"



#define newRasterObject(__a)		__a = new CRasterObject;											\
									numObjects++;														\
									if (numObjects > stats.numPeakRasterObjects)						\
										stats.numPeakRasterObjects = numObjects;
									
#define	deleteRasterObject(__a)		if (__a->grid != NULL)	deleteGrid(__a->grid);						\
									else					__a->object->detach();						\
									delete __a;															\
									numObjects--;


// Returns the bucket numbers
#define	xbucket(__x)	(int) floor((__x - xSampleOffset) * invBucketSampleWidth);

#define	ybucket(__y)	(int) floor((__y - ySampleOffset) * invBucketSampleHeight);


// Insert an object into a bucket
#define	objectInsert(__o) {																				\
		int			bx			=	xbucket(__o->xbound[0]);											\
		int			by			=	ybucket(__o->ybound[0]);											\
		CBucket		*cBucket;																			\
																										\
		if (by <= currentYBucket) {																		\
			by	=	currentYBucket;																		\
			if (bx < currentXBucket)	bx	=	currentXBucket;											\
		} else {																						\
			if (bx < 0)			bx	=	0;																\
		}																								\
																										\
																										\
		if ((by >= yBuckets) || (bx >= xBuckets)) {														\
			deleteRasterObject(__o);																	\
		} else {																						\
			cBucket				=	buckets[by][bx];													\
			__o->next			=	cBucket->objects;													\
			cBucket->objects	=	__o;																\
		}																								\
	}

// Insert an object into a bucket
#define	objectExplicitInsert(__o,__bx,__by) {															\
		CBucket					*cBucket;																\
																										\
		cBucket				=	buckets[__by][__bx];													\
		__o->next			=	cBucket->objects;														\
		cBucket->objects	=	__o;																	\
	}


// Defer the object to the next bucket that'll need it
#define	objectDefer(__cObject)																								\
	if (		(__cObject->xbound[1] >= tbucketRight)	&&	(currentXBucket < xBucketsMinusOne)) {							\
		assert(buckets[currentYBucket][currentXBucket+1] != NULL);															\
		stats.numObjectDeferRight++;																						\
																															\
		objectExplicitInsert(__cObject,currentXBucket+1,currentYBucket);													\
	} else if (	(__cObject->ybound[1] >= tbucketBottom)	&&	(currentYBucket < yBucketsMinusOne)) {							\
		int	xb	=	xbucket(__cObject->xbound[0]);																			\
		if (xb < 0)	xb = 0;																									\
		assert(xb < (int) xBuckets);																						\
		assert(buckets[currentYBucket+1][xb] != NULL);																		\
		stats.numObjectDeferBottom++;																						\
																															\
		objectExplicitInsert(__cObject,xb,currentYBucket+1);																\
	} else {																												\
		deleteRasterObject(__cObject);																						\
	}













///////////////////////////////////////////////////////////////////////
// Class				:	CReyes::CBucket
// Method				:	CBucket
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	10/14/2002
CReyes::CBucket::CBucket() {
	objects			=	NULL;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CReyes::CBucket
// Method				:	~CBucket
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	10/14/2002
CReyes::CBucket::~CBucket() {
}

///////////////////////////////////////////////////////////////////////
// Class				:	CReyes
// Method				:	CReyes
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	2/1/2002
CReyes::CReyes(COptions *o,CXform *x,SOCKET s,unsigned int hf) : CShadingContext(o,x,s,hf) {
	int			cx,cy;

	// Allocate the buckets
	buckets	=	new CBucket**[yBuckets];
	for (cy=0;cy<yBuckets;cy++) {
		buckets[cy]	=	new CBucket*[xBuckets];

		for (cx=0;cx<xBuckets;cx++) {
			buckets[cy][cx]						=	new CBucket;
		}
	}

	// The sample offsets
	xSampleOffset		=	(int) ceil(max(	(pixelFilterWidth-1)*pixelXsamples  / 2.0 , 0));
	ySampleOffset		=	(int) ceil(max(	(pixelFilterHeight-1)*pixelYsamples / 2.0 , 0));

	// Compute the inv bucket width and height in samples
	invBucketSampleWidth	=	1 / (float) (bucketWidth*pixelXsamples);
	invBucketSampleHeight	=	1 / (float) (bucketHeight*pixelYsamples);

	// dSample / dx,dy
	dSampledx			=	dPixeldx*pixelXsamples;
	dSampledy			=	dPixeldy*pixelYsamples;

	// The clipping region we have
	sampleClipLeft		=	(float) (							-	xSampleOffset);
	sampleClipRight		=	(float) (xPixels*pixelXsamples		+	xSampleOffset);
	sampleClipTop		=	(float) (0							-	ySampleOffset);
	sampleClipBottom	=	(float) (yPixels*pixelYsamples		+	ySampleOffset);

	// Init the stats
	numGrids			=	0;
	numObjects			=	0;

	// The length of a raster vertex
	if (flags & OPTIONS_FLAGS_MOTIONBLUR) {
		numVertexSamples	=	(numExtraSamples + 10)*2;
		enableMotionBlur	=	TRUE;
	} else {
		numVertexSamples	=	(numExtraSamples + 10);
		enableMotionBlur	=	FALSE;
	}

	extraPrimitiveFlags	=	0;
	if (numExtraSamples > 0)	extraPrimitiveFlags	|=	RASTER_EXTRASAMPLES;
	if (aperture != 0)			extraPrimitiveFlags	|=	RASTER_FOCALBLUR;

	// Compute misc junk
	xBucketsMinusOne	=	xBuckets-1;
	yBucketsMinusOne	=	yBuckets-1;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CReyes
// Method				:	~CReyes
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	2/1/2002
CReyes::~CReyes() {
	int		x,y;
	CBucket	*cBucket;

	// Ditch the buckets
	for (y=0;y<yBuckets;y++) {
		for (x=0;x<xBuckets;x++) {
			if ((cBucket = buckets[y][x]) != NULL)	{
				CRasterObject		*cObject;

				while((cObject=cBucket->objects) != NULL) {
					cBucket->objects	=	cObject->next;
					deleteRasterObject(cObject);
				}

				delete buckets[y][x];
			}
		}
		delete [] buckets[y];
	}
	delete [] buckets;

	// Sanity check
	assert(numObjects			==	0);
	assert(numGrids				==	0);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CReyes
// Method				:	renderFrame
// Description			:	Render the entire frame
// Return Value			:	-
// Comments				:
// Date last edited		:	2/1/2002
void		CReyes::renderFrame() {
	int				numRenderedBuckets	=	0;
	const	char	*previousActivity	=	stats.activity;
	int				x,y;
	
	stats.activity	=	"Rasterizer - rendering";

	if (netClient != INVALID_SOCKET) {
		// Let the client know that we're ready to render
		T32		netBuffer;

		netBuffer.integer	=	NET_READY;
		rcSend(netClient,(char *) &netBuffer,1*sizeof(T32));
	}


	// While not done
	while(TRUE) {

		// If we have a client, ask for a bucket
		if (netClient != INVALID_SOCKET) {
			T32	netBuffer[3];

			// Receive the bucket to render from the client
			rcRecv(netClient,(char *) netBuffer,3*sizeof(T32));

			// Process the render order
			if (netBuffer[0].integer == NET_RENDER_BUCKET) {
				x	=	netBuffer[1].integer;
				y	=	netBuffer[2].integer;
			} else if (netBuffer[0].integer == NET_FINISH_FRAME) {
				// We have finished the frame, so terminate
				netBuffer[0].integer	=	NET_ACK;
				rcSend(netClient,(char *) netBuffer,1*sizeof(T32));
				
				// send end of frame channel data
				sendFrameDataChannels();
				
				break;
			} else {
				error(CODE_BUG,"Unrecognised network request\n");
			}

			assert(x < xBuckets);
			assert(y < yBuckets);

			while((currentXBucket != x) || (currentYBucket != y)) {
				// Compute the extend of the bucket
				bucketPixelLeft		=	currentXBucket*bucketWidth;
				bucketPixelTop		=	currentYBucket*bucketHeight;
				bucketPixelWidth	=	min(bucketWidth,xPixels-bucketPixelLeft);
				bucketPixelHeight	=	min(bucketHeight,yPixels-bucketPixelTop);
				tbucketLeft			=	bucketPixelLeft*pixelXsamples - xSampleOffset;
				tbucketTop			=	bucketPixelTop*pixelYsamples - ySampleOffset;
				tbucketRight		=	(bucketPixelLeft + bucketPixelWidth)*pixelXsamples - xSampleOffset;
				tbucketBottom		=	(bucketPixelTop + bucketPixelHeight)*pixelYsamples - ySampleOffset;

				numRenderedBuckets++;
				skip();
			}
		} else {
			if (hiderFlags & HIDER_BREAK)	break;
		}

		// Compute the extend of the bucket
		bucketPixelLeft		=	currentXBucket*bucketWidth;
		bucketPixelTop		=	currentYBucket*bucketHeight;
		bucketPixelWidth	=	min(bucketWidth,xPixels-bucketPixelLeft);
		bucketPixelHeight	=	min(bucketHeight,yPixels-bucketPixelTop);
		tbucketLeft			=	bucketPixelLeft*pixelXsamples - xSampleOffset;
		tbucketTop			=	bucketPixelTop*pixelYsamples - ySampleOffset;
		tbucketRight		=	(bucketPixelLeft + bucketPixelWidth)*pixelXsamples - xSampleOffset;
		tbucketBottom		=	(bucketPixelTop + bucketPixelHeight)*pixelYsamples - ySampleOffset;

		render();
		numRenderedBuckets++;
		
		if (netClient != INVALID_SOCKET) {
			// send end of bucket channel data
			sendBucketDataChannels(x,y);
		}

		stats.progress		=	(numRenderedBuckets*100) / (float) (xBuckets*yBuckets);
		if (flags & OPTIONS_FLAGS_PROGRESS)	info(CODE_PROGRESS,"Done %%%3.2f\r",stats.progress);
	}

	stats.progress	=	100;
	if (flags & OPTIONS_FLAGS_PROGRESS)	info(CODE_PROGRESS,"Done               \r");
	stats.activity	=	previousActivity;
}



///////////////////////////////////////////////////////////////////////
// Class				:	CReyes
// Method				:	render
// Description			:	Render the current bucket
// Return Value			:	-
// Comments				:
// Date last edited		:	2/1/2002
void	CReyes::render() {
	float			*pixelBuffer;
	CRasterObject	*cObject;
	CBucket			*cBucket	=	buckets[currentYBucket][currentXBucket];
	CPqueue			objectQueue;

	// Begin a new memory page
	memBegin();

	// Allocate the framebuffer area
	pixelBuffer			=	(float *) ralloc(bucketWidth*bucketHeight*numSamples*sizeof(float));

	// Initialize the opaque depths
	maxDepth			=	C_INFINITY;
	culledDepth			=	C_INFINITY;

	// Init the rasterizer
	rasterBegin(	bucketPixelWidth,
					bucketPixelHeight,
					tbucketLeft,
					tbucketTop);

	// Insert the objects into the queue
	while((cObject=cBucket->objects) != NULL)	{
		cBucket->objects	=	cObject->next;
		objectQueue.insert(cObject);
	}

	// Process the objects and patches
	while((cObject = objectQueue.get()) != NULL) {

		if(depthFilter != DEPTH_MID) culledDepth = maxDepth;

		// Is the object behind the maximum opaque depth ?
		if (cObject->zmin < culledDepth) {

			// Is this a grid ?
			if (cObject->grid != NULL) {
				// Update the stats
				stats.numRasterGridsRendered++;
				stats.numQuadsRendered	+=	cObject->grid->udiv*cObject->grid->vdiv;

				// Render the grid
				rasterDrawPrimitives(cObject->grid);
				objectDefer(cObject);

				continue;
			} else {
				// Dice the object
				cObject->object->dice(this);
				deleteRasterObject(cObject);

				// Insert the objects into the queue
				while((cObject=cBucket->objects) != NULL)	{
					cBucket->objects	=	cObject->next;
					objectQueue.insert(cObject);
				}

				// Keep going
				continue;
			}

			
		} else {
			CRasterObject	**allObjects	=	objectQueue.allItems + 1;
			int				i				=	objectQueue.numItems - 1;

			// Defer the current object
			objectDefer(cObject);

			// Defer the rest of the objects
			for (;i>0;i--) {
				cObject			=	*allObjects++;
				culledDepth		=	min(culledDepth,cObject->zmin);
				objectDefer(cObject);
			}

			break;
		}
	}

	// All objects must be deferred
	assert(cBucket->objects == NULL);

	// Get the framebuffer
	rasterEnd(pixelBuffer);

	// Flush the data to the out devices
	commit(bucketPixelLeft,bucketPixelTop,bucketPixelWidth,bucketPixelHeight,pixelBuffer);

	// Just have rendered this bucket, so deallocate it
	delete cBucket;
	buckets[currentYBucket][currentXBucket]	=	NULL;

	// Update the statistics
	const int	cnBucket			=	currentYBucket*xBuckets+currentXBucket;
	stats.avgRasterObjects			=	(stats.avgRasterObjects*cnBucket	+ numObjects) / (float) (cnBucket+1);
	stats.avgRasterGrids			=	(stats.avgRasterGrids*cnBucket		+ numGrids) / (float) (cnBucket+1);

	// Restore the memory
	memEnd();

	// Advance the bucket
	advanceBucket();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CReyes
// Method				:	skip
// Description			:	Skip the current bucket
// Return Value			:
// Comments				:
// Date last edited		:	2/1/2002
void	CReyes::skip() {
	CRasterObject		*cObject;
	CBucket				*cBucket			=	buckets[currentYBucket][currentXBucket];

	// Defer the objects
	while((cObject	=	cBucket->objects) != NULL) {
		cBucket->objects	=	cObject->next;

		objectDefer(cObject);
	}

	// Just have rendered this bucket, so deallocate it
	delete cBucket;
	buckets[currentYBucket][currentXBucket]	=	NULL;

	// Update the statistics
	const int	cnBucket			=	currentYBucket*xBuckets+currentXBucket;
	stats.avgRasterObjects			=	(stats.avgRasterObjects*cnBucket	+ numObjects) / (float) (cnBucket+1);
	stats.avgRasterGrids			=	(stats.avgRasterGrids*cnBucket		+ numGrids) / (float) (cnBucket+1);

	// Advance the bucket
	advanceBucket();
}























///////////////////////////////////////////////////////////////////////
// Class				:	CReyes
// Method				:	drawObject
// Description			:	Draw an object
// Return Value			:	-
// Comments				:
// Date last edited		:	6/5/2003
void		CReyes::drawObject(CObject *object,const float *bmin,const float *bmax) {
	float				xmin,xmax,ymin,ymax;
	float				x[4],y[4];
	int					i;
	CRasterObject		*cObject;
	float				zmin,zmax;

	// Trivial reject
	if (bmax[COMP_Z] < clipMin)	{	return;	}
	if (bmin[COMP_Z] > clipMax)	{	return;	}

	// Clamp da bounding box
	zmin	=	max(bmin[COMP_Z],clipMin);
	zmax	=	min(bmax[COMP_Z],clipMax);

	// Compute the projected extend of the bound in the pixel space
	if (projection == OPTIONS_PROJECTION_PERSPECTIVE) {
		if (zmin < C_EPSILON)	{			// Spanning the eye plane ?
			if (inFrustrum(bmin,bmax)) {	// Are we in the frustrum ?
											// If we can not make the perspective divide
											// Go ahead and process the object now
				object->dice(this);
			}

			return;
		}

		// Do the perspective divide and figure put the extend on the screen
		const double	invMin	=	imagePlane	/	(double) zmin;
		const double	invMax	=	imagePlane	/	(double) zmax;

		x[0]	=	(float) (bmin[COMP_X]*invMin);
		x[1]	=	(float) (bmin[COMP_X]*invMax);
		x[2]	=	(float) (bmax[COMP_X]*invMin);
		x[3]	=	(float) (bmax[COMP_X]*invMax);
		y[0]	=	(float) (bmin[COMP_Y]*invMin);
		y[1]	=	(float) (bmin[COMP_Y]*invMax);
		y[2]	=	(float) (bmax[COMP_Y]*invMin);
		y[3]	=	(float) (bmax[COMP_Y]*invMax);

		xmin	=	xmax	=	x[0];
		ymin	=	ymax	=	y[0];
		for (i=1;i<4;i++) {
			if			(x[i] < xmin)	xmin	=	x[i];
			else	if	(x[i] > xmax)	xmax	=	x[i];

			if			(y[i] < ymin)	ymin	=	y[i];
			else	if	(y[i] > ymax)	ymax	=	y[i];
		}
	} else {
		xmin	=	bmin[COMP_X];
		ymin	=	bmin[COMP_Y];
		xmax	=	bmax[COMP_X];
		ymax	=	bmax[COMP_Y];
	}

	xmin		-=	pixelLeft;
	xmax		-=	pixelLeft;
	ymin		-=	pixelTop;
	ymax		-=	pixelTop;

	// Account for the depth of field
	if (aperture != 0) {
		const	float	mcoc	=	max(cocScreen(zmin),cocScreen(zmax));
		xmin					=	xmin-mcoc;
		xmax					=	xmax+mcoc;
		ymin					=	ymin-mcoc;
		ymax					=	ymax+mcoc;
	}

	// Convert to samples
	xmin	*=	dSampledx;
	ymin	*=	dSampledy;
	xmax	*=	dSampledx;
	ymax	*=	dSampledy;

	if (xmax < xmin) {
		const float	t	=	xmax;
		xmax			=	xmin;
		xmin			=	t;
	}

	if (ymax < ymin) {
		const float	t	=	ymax;
		ymax			=	ymin;
		ymin			=	t;
	}

	// Trivial reject
	if (xmin > sampleClipRight)		return;
	if (ymin > sampleClipBottom)	return;
	if (xmax < sampleClipLeft)		return;
	if (ymax < sampleClipTop)		return;

	xmin							=	max(xmin,0);
	ymin							=	max(ymin,0);

	// Record the object
	newRasterObject(cObject);
	cObject->xbound[0]				=	(int) floor(xmin);	// Save the bound of the object for future reference
	cObject->xbound[1]				=	(int) floor(xmax);
	cObject->ybound[0]				=	(int) floor(ymin);
	cObject->ybound[1]				=	(int) floor(ymax);
	cObject->object					=	object;
	cObject->grid					=	NULL;
	// disable gross opacity culling for objects which need hidden surfaces shaded
	// this is only OK because cObject->zmin is not used to update the max opaque depth
	if (object->attributes->flags & ATTRIBUTES_FLAGS_SHADE_HIDDEN)
		cObject->zmin				=	-C_INFINITY;
	else
		cObject->zmin				=	zmin;
	object->attach();

	// Insert the object into the bucket its in
	objectInsert(cObject);
}





















///////////////////////////////////////////////////////////////////////
// Class				:	CReyes
// Method				:	drawGrid
// Description			:	Draw a grid
// Return Value			:	-
// Comments				:
// Date last edited		:	6/5/2003
void		CReyes::drawGrid(CSurface *object,int udiv,int vdiv,float umin,float umax,float vmin,float vmax) {
	// Create a grid on the surface
	CRasterGrid			*nGrid;

	// Initialize the grid
	nGrid			=	newGrid(object,(udiv+1)*(vdiv+1));	
	nGrid->dim		=	2;
	nGrid->umin		=	umin;
	nGrid->umax		=	umax;
	nGrid->vmin		=	vmin;
	nGrid->vmax		=	vmax;
	nGrid->udiv		=	udiv;
	nGrid->vdiv		=	vdiv;

	// Sample the grid
	shadeGrid(nGrid,TRUE);									// Just the position

	// Insert the grid into the buckets
	insertGrid(nGrid,0);
}



///////////////////////////////////////////////////////////////////////
// Class				:	CReyes
// Method				:	drawRibbon
// Description			:	Draw a ribbon
// Return Value			:	-
// Comments				:
// Date last edited		:	6/5/2003
void		CReyes::drawRibbon(CSurface *object,int numDiv,float vmin,float vmax) {
	// Create a grid on the surface
	CRasterGrid			*nGrid;

	// Initialize the grid
	nGrid			=	newGrid(object,(numDiv+1)*2);	
	nGrid->dim		=	1;
	nGrid->umin		=	0;
	nGrid->umax		=	0;
	nGrid->vmin		=	vmin;
	nGrid->vmax		=	vmax;
	nGrid->udiv		=	1;
	nGrid->vdiv		=	numDiv;

	// Sample the grid
	shadeGrid(nGrid,TRUE);									// Just the position

	// Dispatch the lines to the renderer
	insertGrid(nGrid,0);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CReyes
// Method				:	drawPoints
// Description			:	Draw bunch of points
// Return Value			:	-
// Comments				:
// Date last edited		:	6/5/2003
void		CReyes::drawPoints(CSurface *object,int numPoints) {
	// Create a grid on the surface
	CRasterGrid			*nGrid;
																// Create the grid
	nGrid			=	newGrid(object,numPoints);
	nGrid->dim		=	0;
	nGrid->umin		=	0;
	nGrid->umax		=	0;
	nGrid->vmin		=	0;
	nGrid->vmax		=	0;
	nGrid->udiv		=	1;
	nGrid->vdiv		=	numPoints;

	// Sample the grid
	shadeGrid(nGrid,TRUE);									// Just the position

	// Dispatch the lines to the renderer
	insertGrid(nGrid,RASTER_POINT);
}






































 














///////////////////////////////////////////////////////////////////////
// Class				:	CReyes
// Method				:	shadeGrid
// Description			:	Shade a grid
// Return Value			:	-
// Comments				:
// Date last edited		:	6/5/2003
void		CReyes::shadeGrid(CRasterGrid *grid,int Ponly) {
	if (grid->dim == 0) {
		// This is a 0 dimensional point cloud
		int					i;
		float				**varying		=	currentShadingState->varying;
		int					numPoints		=	grid->vdiv;
		float				*sizeArray;
		CSurface			*object			=	grid->object;
		const CAttributes	*attributes		=	object->attributes;
		float				*sizes;

		if (Ponly) {
			// Set the flags
			grid->flags	=	extraPrimitiveFlags | RASTER_POINT | RASTER_UNSHADED;
			if (enableMotionBlur && (object->moving()))					grid->flags	|= RASTER_MOVING;
			if (attributes->flags & ATTRIBUTES_FLAGS_SHADE_HIDDEN) 		grid->flags	|= RASTER_UNDERCULL | RASTER_SHADE_HIDDEN;
			if (attributes->flags & ATTRIBUTES_FLAGS_SHADE_BACKFACE)	grid->flags	|= RASTER_UNDERCULL | RASTER_SHADE_BACKFACE;
			if (attributes->flags & ATTRIBUTES_FLAGS_MATTE)				grid->flags	|= RASTER_MATTE;
			if (attributes->flags & ATTRIBUTES_FLAGS_LOD) 				grid->flags	|= RASTER_LOD;

			// Reset the size variable
			varying[VARIABLE_WIDTH][0]			=	-C_INFINITY;
			varying[VARIABLE_CONSTANTWIDTH][0]	=	-C_INFINITY;

			// Shade the points
			displace(object,numPoints,1,0,PARAMETER_BEGIN_SAMPLE | PARAMETER_P);

			// Figure out the size of the ribbon
			sizeArray	=	varying[VARIABLE_WIDTH];
			if (varying[VARIABLE_WIDTH][0] == -C_INFINITY) {
				if (varying[VARIABLE_CONSTANTWIDTH][0] == -C_INFINITY) {
					// So width is set
					for (i=0;i<numPoints;i++)	sizeArray[i]	=	1;
				} else {
					const float	tmp	=	varying[VARIABLE_CONSTANTWIDTH][0];

					for (i=0;i<numPoints;i++)	sizeArray[i]	=	tmp;
				}
			}

			// Project the points
			distance2samples(numPoints,sizeArray,varying[VARIABLE_P]);
			camera2samples(numPoints,varying[VARIABLE_P]);

			// Copy the point samples
			copyPoints(numPoints,varying,grid->vertices,0);

			// Make sure we record the point sizes
			for (sizes=grid->sizes,i=numPoints;i>0;i--,sizes+=2) {
				sizes[0]	=	*sizeArray++;
			}

		} else {
			T32				*Oi;
			T32				one;

			// Sanity check
			assert(grid->flags & RASTER_UNSHADED);
			grid->flags		&=	~(RASTER_UNSHADED | RASTER_SHADE_HIDDEN | RASTER_SHADE_BACKFACE | RASTER_UNDERCULL);
			stats.numRasterGridsShaded++;

			// Shade the points
			shade(object,numPoints,1,0,PARAMETER_BEGIN_SAMPLE | PARAMETER_P);

			// Copy the point samples
			copySamples(numPoints,varying,grid->vertices,0);

			// Check if we're opaque
			for (one.real=1,Oi=(T32 *) varying[VARIABLE_OI],i=numPoints;i>0;i--,Oi+=3) {
				if ((Oi[0].integer ^ one.integer) | (Oi[1].integer ^ one.integer) | (Oi[2].integer ^ one.integer)) {
					grid->flags	|=	RASTER_TRANSPARENT;
					break;
				}
			}
		}

		// Do we have motion ?
		if (grid->flags & RASTER_MOVING) {

			if (Ponly) {
				// Reset the size variable
				varying[VARIABLE_WIDTH][0]			=	-C_INFINITY;
				varying[VARIABLE_CONSTANTWIDTH][0]	=	-C_INFINITY;

				// Shade the points
				displace(object,numPoints,1,0,PARAMETER_END_SAMPLE | PARAMETER_P);

				// Figure out the size of the ribbon
				sizeArray	=	varying[VARIABLE_WIDTH];
				if (varying[VARIABLE_WIDTH][0] == -C_INFINITY) {
					if (varying[VARIABLE_CONSTANTWIDTH][0] == -C_INFINITY) {
						// So width is set
						for (i=0;i<numPoints;i++)	sizeArray[i]	=	1;
					} else {
						const float	tmp	=	varying[VARIABLE_CONSTANTWIDTH][0];

						for (i=0;i<numPoints;i++)	sizeArray[i]	=	tmp;
					}
				}

				// Project the points
				distance2samples(numPoints,sizeArray,varying[VARIABLE_P]);
				camera2samples(numPoints,varying[VARIABLE_P]);

				// Copy the point samples
				copyPoints(numPoints,varying,grid->vertices,1);

				// Make sure we record the point sizes
				for (sizes=grid->sizes,i=numPoints;i>0;i--,sizes+=2) {
					sizes[1]	=	*sizeArray++;
				}
			} else {
				// Shade the points
				shade(object,numPoints,1,0,PARAMETER_END_SAMPLE | PARAMETER_P);

				// Copy the point samples
				copySamples(numPoints,varying,grid->vertices,1);
			}
		}
	} else if (grid->dim == 1) {
		// This is a 1 dimensional ribbon
		const int			numVertices		=	grid->vdiv + 1;
		int					j;
		float				*size;
		int					i;
		float				**varying;
		float				*u;
		float				*v;
		float				*time;
		float				*leftVertices,*rightVertices;
		CSurface			*object			=	grid->object;
		const CAttributes	*attributes		=	object->attributes;

		varying		=	currentShadingState->varying;
		u			=	varying[VARIABLE_U];
		v			=	varying[VARIABLE_V];
		time		=	varying[VARIABLE_TIME];

		// Put the sampling coordinates
		for (j=0;j<numVertices;j++) {
			const float t	=	(float) j / (float) (numVertices - 1);
			*u++	=	0;
			*v++	=	grid->vmin*(1-t) + grid->vmax*t;
			*time++	=	0;
		}

		if (Ponly) {
			// Set the flags
			if (attributes->nSides == 2) {
				grid->flags	=	RASTER_DRAW_FRONT | RASTER_DRAW_BACK | RASTER_UNSHADED | extraPrimitiveFlags;
			} else {
				if (attributes->flags & ATTRIBUTES_FLAGS_INSIDE) {	// Flip
					grid->flags	=	RASTER_DRAW_FRONT | RASTER_UNSHADED | extraPrimitiveFlags;
				} else {
					grid->flags	=	RASTER_DRAW_BACK | RASTER_UNSHADED | extraPrimitiveFlags;
				}
			}
			if (attributes->flags & ATTRIBUTES_FLAGS_SHADE_HIDDEN) 	 grid->flags	|= RASTER_UNDERCULL | RASTER_SHADE_HIDDEN;
			if (attributes->flags & ATTRIBUTES_FLAGS_SHADE_BACKFACE) grid->flags	|= RASTER_UNDERCULL | RASTER_SHADE_BACKFACE;
			if (attributes->flags & ATTRIBUTES_FLAGS_MATTE)			 grid->flags	|= RASTER_MATTE;
			if (attributes->flags & ATTRIBUTES_FLAGS_LOD) 			 grid->flags	|= RASTER_LOD;

			// Do we have motion blur ?
			if (enableMotionBlur && (object->moving()))				grid->flags		|=	RASTER_MOVING;

			// Reset the size variable
			varying[VARIABLE_WIDTH][0]			=	-C_INFINITY;
			varying[VARIABLE_CONSTANTWIDTH][0]	=	-C_INFINITY;

			// Shade the points on the curve
			displace(object,1,numVertices,1,PARAMETER_BEGIN_SAMPLE | PARAMETER_N | PARAMETER_DPDV | PARAMETER_P);

			// Figure out the size of the ribbon
			size	=	varying[VARIABLE_WIDTH];
			if (varying[VARIABLE_WIDTH][0] == -C_INFINITY) {
				if (varying[VARIABLE_CONSTANTWIDTH][0] == -C_INFINITY) {
					// No width is set
					for (i=0;i<numVertices;i++)	size[i]	=	1;
				} else {
					const float	tmp	=	varying[VARIABLE_CONSTANTWIDTH][0];

					for (i=0;i<numVertices;i++)	size[i]	=	tmp;
				}
			}

			// Copy the vertex samples
			leftVertices	=	grid->vertices;
			rightVertices	=	leftVertices + numVertices*numVertexSamples;
			copyPoints(numVertices,varying,leftVertices,0);
			copyPoints(numVertices,varying,rightVertices,0);

			// Create the ribbon
			makeRibbon(numVertices,leftVertices,rightVertices,size,varying[VARIABLE_N],varying[VARIABLE_DPDV],0);
		} else {
			T32					one;
			int					opaque;
			T32					*Oi;

			// Sanity check
			assert(grid->flags & RASTER_UNSHADED);
			grid->flags		&=	~(RASTER_UNSHADED | RASTER_SHADE_HIDDEN | RASTER_SHADE_BACKFACE | RASTER_UNDERCULL);
			stats.numRasterGridsShaded++;

			// Shade the points on the curve
			shade(object,1,numVertices,1,PARAMETER_BEGIN_SAMPLE | PARAMETER_N | PARAMETER_DPDV | PARAMETER_P);

			// Copy the vertex samples
			leftVertices	=	grid->vertices;
			rightVertices	=	leftVertices + numVertices*numVertexSamples;
			copySamples(numVertices,varying,leftVertices,0);
			copySamples(numVertices,varying,rightVertices,0);

			// Check if we're opaque
			for (one.real=1,opaque=0,Oi=(T32 *) varying[VARIABLE_OI],i=numVertices;i>0;i--,Oi+=3) {
				if ((Oi[0].integer ^ one.integer) | (Oi[1].integer ^ one.integer) | (Oi[2].integer ^ one.integer)) {
					grid->flags	|=	RASTER_TRANSPARENT;
					break;
				}
			}
		}


		// Take care of the motion
		if (grid->flags & RASTER_MOVING) {
			// Sample points along the curve
			u				=	varying[VARIABLE_U];
			v				=	varying[VARIABLE_V];
			time			=	varying[VARIABLE_TIME];

			// Put the sampling coordinates
			for (j=0;j<numVertices;j++) {
				const float t	=	(float) j / (float) (numVertices - 1);
				*u++	=	0;
				*v++	=	grid->vmin*(1-t) + grid->vmax*t;
				*time++	=	1;
			}

			if (Ponly) {
				// Reset the size variable
				varying[VARIABLE_WIDTH][0]			=	-C_INFINITY;
				varying[VARIABLE_CONSTANTWIDTH][0]	=	-C_INFINITY;

				// Shade the points on the curve
				displace(object,1,numVertices,1,PARAMETER_END_SAMPLE | PARAMETER_N | PARAMETER_DPDV | PARAMETER_P);

				// Figure out the size of the ribbon
				size	=	varying[VARIABLE_WIDTH];
				if (varying[VARIABLE_WIDTH][0] == -C_INFINITY) {
					if (varying[VARIABLE_CONSTANTWIDTH][0] == -C_INFINITY) {
						// No width is set
						for (i=0;i<numVertices;i++)	size[i]	=	1;
					} else {
						const float	tmp	=	varying[VARIABLE_CONSTANTWIDTH][0];

						for (i=0;i<numVertices;i++)	size[i]	=	tmp;
					}
				}

				// Copy the vertex samples
				leftVertices	=	grid->vertices;
				rightVertices	=	leftVertices + numVertices*numVertexSamples;
				copyPoints(numVertices,varying,leftVertices,1);
				copyPoints(numVertices,varying,rightVertices,1);

				// Create the ribbon
				makeRibbon(numVertices,leftVertices,rightVertices,size,varying[VARIABLE_N],varying[VARIABLE_DPDV],1);
			} else {
				// Shade the points on the curve
				shade(object,1,numVertices,1,PARAMETER_END_SAMPLE | PARAMETER_N | PARAMETER_DPDV | PARAMETER_P);

				// Copy the vertex samples
				leftVertices	=	grid->vertices;
				rightVertices	=	leftVertices + numVertices*numVertexSamples;
				copySamples(numVertices,varying,leftVertices,1);
				copySamples(numVertices,varying,rightVertices,1);
			}
		}
	} else {
		assert(grid->dim == 2);
		// This is a 2 dimensional surface
		int					i,j;
		float				ustart;
		float				ustep;
		float				vstart;
		float				vstep;
		int					k;
		int					numVertices;
		float				**varying	=	currentShadingState->varying;
		T32					one;
		CSurface			*object		=	grid->object;
		const CAttributes	*attributes	=	object->attributes;
		const int			udiv		=	grid->udiv;
		const int			vdiv		=	grid->vdiv;
		float				*u;
		float				*v;
		float				*time;
		float				cu,cv;
		T32					*Oi;


		numVertices	=	(udiv+1)*(vdiv+1);			// The number of vertices to shade
		ustart		=	grid->umin;					// The minimum step sizes
		ustep		=	(grid->umax - ustart) / (float) udiv;
		vstart		=	grid->vmin;
		vstep		=	(grid->vmax - vstart) / (float) vdiv;

		assert(numVertices <= (int) maxGridSize);

		// Shade the points in the patch
		u			=	varying[VARIABLE_U];
		v			=	varying[VARIABLE_V];
		time		=	varying[VARIABLE_TIME];

		// Shade the minimum grid
		for (j=vdiv,cv=vstart;j>=0;j--,cv+=vstep) {
			for (i=udiv,cu=ustart;i>=0;i--,cu+=ustep) {
				*u++		=	cu;
				*v++		=	cv;
				*time++		=	0;
			}
		}

		if (Ponly) {
			// Set the flags
			if (attributes->nSides == 2) {
				grid->flags	=	RASTER_DRAW_FRONT | RASTER_DRAW_BACK | RASTER_UNSHADED | extraPrimitiveFlags;
			} else {
				if (attributes->flags & ATTRIBUTES_FLAGS_INSIDE) {	// Flip
					grid->flags	=	RASTER_DRAW_FRONT | RASTER_UNSHADED | extraPrimitiveFlags;
				} else {
					grid->flags	=	RASTER_DRAW_BACK | RASTER_UNSHADED | extraPrimitiveFlags;
				}
			}
			if (attributes->flags & ATTRIBUTES_FLAGS_SHADE_HIDDEN)	 grid->flags	|= RASTER_UNDERCULL | RASTER_SHADE_HIDDEN;
			if (attributes->flags & ATTRIBUTES_FLAGS_SHADE_BACKFACE) grid->flags	|= RASTER_UNDERCULL | RASTER_SHADE_BACKFACE;
			if (attributes->flags & ATTRIBUTES_FLAGS_MATTE)			 grid->flags	|= RASTER_MATTE;
			if (attributes->flags & ATTRIBUTES_FLAGS_LOD) 			 grid->flags	|= RASTER_LOD;

			// Do we have motion blur ?
			if (enableMotionBlur && (object->moving()))				grid->flags		|=	RASTER_MOVING;

			// Displace the sucker
			displace(object,udiv+1,vdiv+1,2,PARAMETER_BEGIN_SAMPLE | PARAMETER_P);

			// Project the P into samples
			camera2samples(numVertices,varying[VARIABLE_P]);
			
			// Save the vertex data
			copyPoints(numVertices,varying,grid->vertices,0);
		} else {
			// Sanity check
			assert(grid->flags & RASTER_UNSHADED);
			grid->flags		&=	~(RASTER_UNSHADED | RASTER_SHADE_HIDDEN | RASTER_SHADE_BACKFACE | RASTER_UNDERCULL);
			stats.numRasterGridsShaded++;

			// Shade the sucker
			shade(object,udiv+1,vdiv+1,2,PARAMETER_BEGIN_SAMPLE | PARAMETER_P);

			// Project the P into samples
			camera2samples(numVertices,varying[VARIABLE_P]);

			// Save the vertex data
			copySamples(numVertices,varying,grid->vertices,0);

			// Check the transparency
			Oi			=	(T32 *) varying[VARIABLE_OI];
			one.real	=	1;
			for (k=0;k<numVertices;k++,Oi+=3) {
				if ((Oi[0].integer ^ one.integer) | (Oi[1].integer ^ one.integer) | (Oi[2].integer ^ one.integer)) {
					grid->flags	|=	RASTER_TRANSPARENT;
					break;
				}
			}
		}

		// Do we have motion blur ?
		if (grid->flags & RASTER_MOVING) {
			u			=	varying[VARIABLE_U];
			v			=	varying[VARIABLE_V];
			time		=	varying[VARIABLE_TIME];

			// Shade the minimum grid
			for (j=vdiv,cv=vstart;j>=0;j--,cv+=vstep) {
				for (i=udiv,cu=ustart;i>=0;i--,cu+=ustep) {
					*u++		=	cu;
					*v++		=	cv;
					*time++		=	1;
				}
			}

			if (Ponly) {
				// Shade the sucker
				displace(object,udiv+1,vdiv+1,2,PARAMETER_END_SAMPLE | PARAMETER_P);

				// Project the P into samples
				camera2samples(numVertices,varying[VARIABLE_P]);

				// Copy the vertex data
				copyPoints(numVertices,varying,grid->vertices,1);
			} else {
				// Shade the sucker
				shade(object,udiv+1,vdiv+1,2,PARAMETER_END_SAMPLE | PARAMETER_P);

				// Project the P into samples
				camera2samples(numVertices,varying[VARIABLE_P]);

				// Copy the vertex data
				copySamples(numVertices,varying,grid->vertices,1);
			}
		}
	}
}



///////////////////////////////////////////////////////////////////////
// Class				:	CReyes
// Method				:	copyPoints
// Description			:	Copy the point data
// Return Value			:	-
// Comments				:
// Date last edited		:	6/5/2003
void			CReyes::copyPoints(int numVertices,float **varying,float *vertices,int stage) {
	const	float	*P			=	varying[VARIABLE_P];
	const	int		disp		=	(numExtraSamples + 10)*stage;
	int				i;

	// Copy the samples
	for (i=numVertices;i>0;i--,P+=3,vertices+=numVertexSamples) {
		movvv(vertices+disp,P);
	}

	// If we have depth of field, compute that
	if ((aperture != 0) && (stage == 0)) {
		vertices	-=	numVertices*numVertexSamples;

		// Compute the circle of confusion amount
		for (i=numVertices;i>0;i--,vertices+=numVertexSamples) {
			const	float	z	=	vertices[COMP_Z];

			vertices[9]			=	cocSamples(z);
		}
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CReyes
// Method				:	copySamples
// Description			:	Copy the shading data over
// Return Value			:	-
// Comments				:
// Date last edited		:	6/5/2003
void			CReyes::copySamples(int numVertices,float **varying,float *vertices,int stage) {
	const	float	*C		=	varying[VARIABLE_CI];
	const	float	*O		=	varying[VARIABLE_OI];
	int				i,j,k,l;
	const	int		disp	=	(numExtraSamples + 10)*stage;
	const	int		*cOrder	=	sampleOrder;
	const	float	*s;
	float			*d;

	// Copy the samples
	for (i=numVertices;i>0;i--,C+=3,O+=3,vertices+=numVertexSamples) {
		float	*dest	=	vertices + disp;

		movvv(dest+3,C);
		movvv(dest+6,O);
	}


	// Do the extra samples
	k	=	disp + 10;
	for (i=0;i<numExtraChannels;i++) {
		const int outType			= *cOrder++;
		const int channelSamples	= *cOrder++;

		switch(channelSamples) {
		case 0:
			break;
		case 1:
			vertices	-=	numVertices*numVertexSamples;
			s			=	varying[outType];
			for (j=0;j<numVertices;j++,vertices+=numVertexSamples) {
				d		=	vertices + k;
				*d++	=	*s++;
			}
			k++;
			break;
		case 2:
			vertices	-=	numVertices*numVertexSamples;
			s			=	varying[outType];
			for (j=0;j<numVertices;j++,vertices+=numVertexSamples) {
				d		=	vertices + k;
				*d++	=	*s++;
				*d++	=	*s++;
			}
			k	+=	2;
			break;
		case 3:
			vertices	-=	numVertices*numVertexSamples;
			s			=	varying[outType];
			for (j=0;j<numVertices;j++,vertices+=numVertexSamples) {
				d		=	vertices + k;
				*d++	=	*s++;
				*d++	=	*s++;
				*d++	=	*s++;
			}
			k	+=	3;
			break;
		case 4:
			vertices	-=	numVertices*numVertexSamples;
			s			=	varying[outType];
			for (j=0;j<numVertices;j++,vertices+=numVertexSamples) {
				d		=	vertices + k;
				*d++	=	*s++;
				*d++	=	*s++;
				*d++	=	*s++;
				*d++	=	*s++;
			}
			k	+=	4;
			break;
		default:
			vertices	-=	numVertices*numVertexSamples;
			s			=	varying[outType];
			for (j=0;j<numVertices;j++,vertices+=numVertexSamples) {
				d		=	vertices + k;
				for (l=channelSamples;l>0;l--)
					*d++	=	*s++;
			}
			k	+=	channelSamples;
		}
	}
}































///////////////////////////////////////////////////////////////////////
// Class				:	CReyes
// Method				:	makeRibbon
// Description			:	Displace the left and right vertices from each other
// Return Value			:	-
// Comments				:
// Date last edited		:	6/5/2003
void		CReyes::makeRibbon(int numVertices,float *leftVertices,float *rightVertices,const float *size,const float *N,const float *dPdv,int disp) {
	int					i;
	float				*pl;
	float				*pr;
	vector				tmp;

	disp		*=	(numExtraSamples+10);

	for (i=numVertices;i>0;i--) {
		pl		=	leftVertices	+ disp;	leftVertices	+=	numVertexSamples;
		pr		=	rightVertices	+ disp;	rightVertices	+=	numVertexSamples;
	
		crossvv(tmp,N,dPdv);		// This is the extrude direction

		normalizevf(tmp);			// Use the fast normalization as it doesn't create catastrophic error

		mulvf(tmp,(*size++) * 0.5f);

		addvv(pl,tmp);
		subvv(pr,tmp);

		camera2samples(pl);
		camera2samples(pr);

		N		+=	3;
		dPdv	+=	3;
	}
}







///////////////////////////////////////////////////////////////////////
// Class				:	CReyes
// Method				:	newGrid
// Description			:	Initialize a grid by copying the points
// Return Value			:	-
// Comments				:
// Date last edited		:	6/5/2003
CReyes::CRasterGrid		*CReyes::newGrid(CSurface *object,int numVertices) {
	CRasterGrid			*grid	=	new CRasterGrid;

	grid->object			=	object;				object->attach();
	grid->numVertices		=	numVertices;
	grid->vertices			=	new float[numVertices*numVertexSamples];
	grid->bounds			=	new int[numVertices*4];
	grid->sizes				=	new float[numVertices*2];

	numGrids++;
	if (numGrids > stats.numPeakRasterGrids)	stats.numPeakRasterGrids	=	numGrids;
	stats.numRasterGridsCreated++;

	return grid;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CReyes
// Method				:	deleteGrid
// Description			:	Delete the grid
// Return Value			:	-
// Comments				:
// Date last edited		:	6/5/2003
void			CReyes::deleteGrid(CRasterGrid *grid) {
	grid->object->detach();
	delete [] grid->vertices;
	delete [] grid->bounds;
	delete [] grid->sizes;
	delete grid;

	numGrids--;
	assert(numGrids >= 0);
}



///////////////////////////////////////////////////////////////////////
// Class				:	CReyes
// Method				:	insertGrid
// Description			:	Compute the grid bound and insert the grid into the correct bucket
// Return Value			:	-
// Comments				:
// Date last edited		:	9/17/2004
void		CReyes::insertGrid(CRasterGrid *grid,int flags) {
	// Compute the grid bound and insert it
	float				xmin,xmax,ymin,ymax;
	int					i;
	CRasterObject		*cObject;
	float				zmin,zmax;
	const float			*cVertex;

	// Compute the bound of the grid
	xmin	=	C_INFINITY;
	ymin	=	C_INFINITY;
	zmin	=	C_INFINITY;
	xmax	=	-C_INFINITY;
	ymax	=	-C_INFINITY;
	zmax	=	-C_INFINITY;
	for (cVertex=grid->vertices,i=grid->numVertices;i>0;i--,cVertex+=numVertexSamples) {
		if (cVertex[0] < xmin)	xmin	=	cVertex[0];
		if (cVertex[1] < ymin)	ymin	=	cVertex[1];
		if (cVertex[2] < zmin)	zmin	=	cVertex[2];
		if (cVertex[0] > xmax)	xmax	=	cVertex[0];
		if (cVertex[1] > ymax)	ymax	=	cVertex[1];
		if (cVertex[2] > zmax)	zmax	=	cVertex[2];
	}

	// Account for the motion if applicable
	if (grid->flags & RASTER_MOVING) {
		const float	*sVertex;

		for (sVertex=grid->vertices,i=grid->numVertices;i>0;i--,sVertex+=numVertexSamples) {
			const float	*cVertex	=	sVertex + numExtraSamples+10;
			if (cVertex[0] < xmin)	xmin	=	cVertex[0];
			if (cVertex[1] < ymin)	ymin	=	cVertex[1];
			if (cVertex[2] < zmin)	zmin	=	cVertex[2];
			if (cVertex[0] > xmax)	xmax	=	cVertex[0];
			if (cVertex[1] > ymax)	ymax	=	cVertex[1];
			if (cVertex[2] > zmax)	zmax	=	cVertex[2];
		}
	}

	if (aperture != 0) {
		// Expand the bound by the maximum focal blur amount
		const	float	coc1	=	absf(cocSamples(zmin));
		const	float	coc2	=	absf(cocSamples(zmax));
		const	float	mcoc	=	max(coc1,coc2);

		xmin	-=	mcoc;
		xmax	+=	mcoc;
		ymin	-=	mcoc;
		ymax	+=	mcoc;
	}

	// Trivial reject
	if ((xmin > sampleClipRight)	|| (ymin > sampleClipBottom) || (xmax < sampleClipLeft) || (ymax < sampleClipTop)) {
		deleteGrid(grid);
		return;
	}

	xmin							=	max(xmin,0);
	ymin							=	max(ymin,0);


	// Compute the primitive bounds
	if (flags & RASTER_POINT) {
		int					i;
		float				maxmaxSize	=	-C_INFINITY;
		const float			*sizes		=	grid->sizes;
		const float			*vertices	=	grid->vertices;
		int					*bounds		=	grid->bounds;

		// Compute the bounds for every point
		for (i=grid->numVertices;i>0;i--,vertices+=numVertexSamples,sizes+=2,bounds+=4) {
			float		xbound[2];
			float		ybound[2];
			const float	*P		=	vertices;

			xbound[0]			=	P[0];
			xbound[1]			=	P[0];
			ybound[0]			=	P[1];
			ybound[1]			=	P[1];

			if (grid->flags & RASTER_MOVING) {
				P				+=	numExtraSamples + 10;

				xbound[0]		=	min(xbound[0],P[0]);
				xbound[1]		=	max(xbound[1],P[0]);
				ybound[0]		=	min(ybound[0],P[1]);
				ybound[1]		=	max(ybound[1],P[1]);

				const float maxSize	=	max(sizes[0],sizes[1]);

				xbound[0]		-=	maxSize;
				ybound[0]		-=	maxSize;
				xbound[1]		+=	maxSize;
				ybound[1]		+=	maxSize;

				if (maxSize > maxmaxSize)	maxmaxSize	=	maxSize;
			} else {
				xbound[0]		-=	sizes[0];
				ybound[0]		-=	sizes[0];
				xbound[1]		+=	sizes[0];
				ybound[1]		+=	sizes[0];

				if (sizes[0] > maxmaxSize)	maxmaxSize	=	sizes[0];
			}

			
			bounds[0]	=	(int) floor(xbound[0]);		// xmin
			bounds[1]	=	(int) floor(xbound[1]);		// xmax
			bounds[2]	=	(int) floor(ybound[0]);		// ymin
			bounds[3]	=	(int) floor(ybound[1]);		// ymax
		}

		xmin	-=	maxmaxSize;
		ymin	-=	maxmaxSize;
		xmax	+=	maxmaxSize;
		ymax	+=	maxmaxSize;
	} else {
		int					i,j;
		const int			udiv		=	grid->udiv;
		const int			vdiv		=	grid->vdiv;
		const float			*vertices	=	grid->vertices;
		int					*bounds		=	grid->bounds;

		// Bound every quad
		for (j=0;j<vdiv;j++) {
			for (i=0;i<udiv;i++,bounds+=4) {
				float			xbound[2];
				float			ybound[2];
				const float		*cVertex	=	vertices + (j*(udiv+1) + i)*numVertexSamples; // The top left vertex
				const float		*P;

				// Compute the primitive bounds
				P			=	cVertex;
				xbound[1]	=	xbound[0]	=	P[COMP_X];
				ybound[1]	=	ybound[0]	=	P[COMP_Y];

				P			+=	numVertexSamples;
				if		(P[COMP_X] < xbound[0])	xbound[0]	=	P[COMP_X];
				else if	(P[COMP_X] > xbound[1])	xbound[1]	=	P[COMP_X];
				if		(P[COMP_Y] < ybound[0])	ybound[0]	=	P[COMP_Y];
				else if	(P[COMP_Y] > ybound[1])	ybound[1]	=	P[COMP_Y];

				P			+=	udiv*numVertexSamples;
				if		(P[COMP_X] < xbound[0])	xbound[0]	=	P[COMP_X];
				else if	(P[COMP_X] > xbound[1])	xbound[1]	=	P[COMP_X];
				if		(P[COMP_Y] < ybound[0])	ybound[0]	=	P[COMP_Y];
				else if	(P[COMP_Y] > ybound[1])	ybound[1]	=	P[COMP_Y];

				P			+=	numVertexSamples;
				if		(P[COMP_X] < xbound[0])	xbound[0]	=	P[COMP_X];
				else if	(P[COMP_X] > xbound[1])	xbound[1]	=	P[COMP_X];
				if		(P[COMP_Y] < ybound[0])	ybound[0]	=	P[COMP_Y];
				else if	(P[COMP_Y] > ybound[1])	ybound[1]	=	P[COMP_Y];

				if (grid->flags & RASTER_MOVING) {
					P	=	cVertex + numExtraSamples + 10;
					if		(P[COMP_X] < xbound[0])	xbound[0]	=	P[COMP_X];
					else if	(P[COMP_X] > xbound[1])	xbound[1]	=	P[COMP_X];
					if		(P[COMP_Y] < ybound[0])	ybound[0]	=	P[COMP_Y];
					else if	(P[COMP_Y] > ybound[1])	ybound[1]	=	P[COMP_Y];

					P	+=	numVertexSamples;
					if		(P[COMP_X] < xbound[0])	xbound[0]	=	P[COMP_X];
					else if	(P[COMP_X] > xbound[1])	xbound[1]	=	P[COMP_X];
					if		(P[COMP_Y] < ybound[0])	ybound[0]	=	P[COMP_Y];
					else if	(P[COMP_Y] > ybound[1])	ybound[1]	=	P[COMP_Y];

					P	+=	udiv*numVertexSamples;
					if		(P[COMP_X] < xbound[0])	xbound[0]	=	P[COMP_X];
					else if	(P[COMP_X] > xbound[1])	xbound[1]	=	P[COMP_X];
					if		(P[COMP_Y] < ybound[0])	ybound[0]	=	P[COMP_Y];
					else if	(P[COMP_Y] > ybound[1])	ybound[1]	=	P[COMP_Y];

					P	+=	numVertexSamples;
					if		(P[COMP_X] < xbound[0])	xbound[0]	=	P[COMP_X];
					else if	(P[COMP_X] > xbound[1])	xbound[1]	=	P[COMP_X];
					if		(P[COMP_Y] < ybound[0])	ybound[0]	=	P[COMP_Y];
					else if	(P[COMP_Y] > ybound[1])	ybound[1]	=	P[COMP_Y];
				}

				if (aperture != 0) {
					// Expand the bound by the maximum focal blur amount
					const float	c1		=	cVertex[9];
					const float	c2		=	cVertex[9 + numVertexSamples];
					const float	c3		=	cVertex[9 + numVertexSamples*(udiv+1)];
					const float	c4		=	cVertex[9 + numVertexSamples*(udiv+2)];
					const float	mcoc	=	max(max(max(c1,c2),c3),c4);

					xbound[0]			-=	mcoc;
					xbound[1]			+=	mcoc;
					ybound[0]			-=	mcoc;
					ybound[1]			+=	mcoc;
				}


				bounds[0]	=	(int) floor(xbound[0]);		// xmin
				bounds[1]	=	(int) floor(xbound[1]);		// xmax
				bounds[2]	=	(int) floor(ybound[0]);		// ymin
				bounds[3]	=	(int) floor(ybound[1]);		// ymax
			}

			bounds+=4;
		}
	}

	// Record the object
	newRasterObject(cObject);
	cObject->xbound[0]				=	(int) floor(xmin);	// Save the bound of the object for future reference
	cObject->xbound[1]				=	(int) floor(xmax);
	cObject->ybound[0]				=	(int) floor(ymin);
	cObject->ybound[1]				=	(int) floor(ymax);
	cObject->object					=	NULL;
	cObject->grid					=	grid;
	// disable gross opacity culling for objects which need hidden surfaces shaded
	// this is only OK because cObject->zmin is not used to update the max opaque depth
	if (grid->flags & RASTER_SHADE_HIDDEN)
		cObject->zmin				=	-C_INFINITY;
	else
		cObject->zmin				=	zmin;

	// Insert the object into the bucket its in
	objectInsert(cObject);

	// Update stats
	stats.numQuadsCreated	+=	grid->udiv*grid->vdiv;
	stats.numRasterGridsCreated++;
}

