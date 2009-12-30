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
//  File				:	reyes.cpp
//  Classes				:	CReyes
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "rendererc.h"
#include "error.h"
#include "ri_config.h"
#include "ri.h"
#include "stats.h"
#include "memory.h"
#include "points.h"
#include "reyes.h"

/////////////////////////////////////////////////////////////////////////////////////////
// Some misc macros
/////////////////////////////////////////////////////////////////////////////////////////

#if 0
	#define __logPushRight(__object,__x,__y)				fprintf(stderr,"\t->object %x pushed right to %d,%d in thread %d\n",__object,__x,__y,thread);
	#define __logPushDown(__object,__x,__y)					fprintf(stderr,"\t->object %x pushed down to %d,%d in thread %d\n",__object,__x,__y,thread);
	#define __logPushDiscard(__object,__x,__y)				fprintf(stderr,"\t->object %x discarded on push at %d,%d in thread %d\n",__object,__x,__y,thread);
	#define	__logObjectDequeue(__object,__x,__y)			fprintf(stderr,"\t->object %x dequeued at %d,%d in thread %d\n",__object,__x,__y,thread);
	#define __logObjectRasterizeDice(_object,__x,__y)		fprintf(stderr,"->object %x rasterized / diced at %d,%d in thread %d\n",__object,__x,__y,thread);
	#define __logObjectOpacityCull(__object,__x,__y)		fprintf(stderr,"\t->object %x gross opacity culled at %d %d in thread %d\n",cObject,currentXBucket,currentYBucket,thread);
	#define __logBucketStart(__x,__Y)						fprintf(stderr,"START bucket %d,%d in thread %d\n",__x,_y,thread);
	#define __logBucketTerminate(__x,__y)					fprintf(stderr,"DONE bucket %d,%d in thread %d\n",__x,_y,thread);
	#define __logBucketSkip(__x,__y)						fprintf(stderr,"SKIP bucket %d,%d in thread %d\n",__x,_y,thread);
	#define __logObjectSkip(__object,__x,__y)				fprintf(stderr,"->object %x skipped at %d,%d in thread %d\n",__object,__x,__y,thread);
	#define __logObjectDelete(__object,__x,__y)				fprintf(stderr,"->object %x deleted at %d,%d in thread %d\n",__object,__x,__y,thread);
	#define __logObjectInsert(__object,__x,__y,__thread,__queue)
		fprintf(stderr,"->object %x inserted at %d,%d in thread %d (queue was %d)\n",__object,__x,__y,__thread,__queue);
#else
	#define __logPushRight(__object,__x,__y)
	#define __logPushDown(__object,__x,__y)
	#define __logPushDiscard(__object,__x,__y)
	#define	__logObjectDequeue(__object,__x,__y)
	#define __logObjectRasterizeDice(_object,__x,__y)
	#define __logObjectOpacityCull(__object,__x,__y)
	#define __logBucketStart(__x,__Y)
	#define __logBucketTerminate(__x,__y)
	#define __logBucketSkip(__x,__y)
	#define __logObjectSkip(__object,__x,__y)
	#define __logObjectDelete(__object,__x,__y)
	#define __logObjectInsert(__object,__x,__y,__thread,__queue)
#endif

#if 0
	TMutex debugMutex = PTHREAD_MUTEX_INITIALIZER;
	#include <map>
	using namespace std;
	map<void*,int> allocMap;

	void allocateMapCheck() {
		printf("%d undisposed objects\n",allocMap.size());
		for(map<void*,int>::iterator it = allocMap.begin(); it != allocMap.end(); it++) {
			printf("\t%x inserted to %d buckets\n",it->first,it->second);
		}
	}

	#define __recordObjectInsert(__object,__ref)	\
		osLock(debugMutex);							\
		allocMap[object] = refCount;				\
		osUnlock(debugMutex);						\

	#define __recordObjectDelete(__object)			\
		osLock(debugMutex);							\
		map<void*,int>::iterator it = allocMap.find(grid);	\
		if(it == allocMap.end())	printf("ERROR deleting nonexistent raster object\n");	\
		else						allocMap.erase(it);		\
		osUnlock(debugMutex);
#else
	#define __recordObjectInsert(__object,__ref)
	#define __recordObjectDelete(__object)
#endif

// Returns the bucket numbers
#define	xbucket(__x)	(int) floor((__x - CRenderer::xSampleOffset) * CRenderer::invBucketSampleWidth);
#define	ybucket(__y)	(int) floor((__y - CRenderer::ySampleOffset) * CRenderer::invBucketSampleHeight);

#define	xbucketNext(__x)	(int) ceil((__x - CRenderer::xSampleOffset) * CRenderer::invBucketSampleWidth);
#define	ybucketNext(__y)	(int) ceil((__y - CRenderer::ySampleOffset) * CRenderer::invBucketSampleHeight);


// Insert an object into a bucket (buckets must be locked)
#define	objectExplicitInsert(__o,__bx,__by) {			\
		CBucket					*cBucket;				\
														\
		cBucket				=	buckets[__by][__bx];	\
		__o->next[thread]	=	cBucket->objects;		\
		cBucket->objects	=	__o;					\
	}


// Defer the object to the next bucket that'll need it (buckets must be locked)
#define	objectDefer(__cObject)																					\
	if (		(__cObject->xbound[1] >= tbucketRight)	&&	(currentXBucket < CRenderer::xBucketsMinusOne)) {	\
		assert(buckets[currentYBucket][currentXBucket+1] != NULL);												\
																												\
		objectExplicitInsert(__cObject,currentXBucket+1,currentYBucket);										\
		__logPushRight(__cObject,currentXBucket+1,currentYBucket);												\
	} else if (	(__cObject->ybound[1] >= tbucketBottom)	&&	(currentYBucket < CRenderer::yBucketsMinusOne)) {	\
		int	xb	=	xbucket(__cObject->xbound[0]);																\
		if (xb < 0)	xb = 0;																						\
		assert(xb < (int) CRenderer::xBuckets);																	\
		assert(buckets[currentYBucket+1][xb] != NULL);															\
																												\
		objectExplicitInsert(__cObject,xb,currentYBucket+1);													\
		__logPushDown(__cObject,xb,currentYBucket+1);															\
	} else {																									\
		__logPushDiscard(__cObject,currentXBucket,currentYBucket);												\
		__cObject->next[thread]	=	objectsToDelete;															\
		objectsToDelete			=	__cObject;																	\
	}


#define	flushObjects(__objects)	{						\
		CRasterObject	*cObject;						\
		while((cObject = __objects) != NULL) {			\
			__objects	=	__objects->next[thread];	\
			osLock(cObject->mutex);						\
			cObject->refCount--;						\
			if (cObject->refCount == 0) {				\
				deleteObject(cObject);					\
			} else {									\
				osUnlock(cObject->mutex);				\
			}											\
		}												\
	}


//////////////////////////////////////////////////////////////
// Some static variables for the CReyes class
int				CReyes::extraPrimitiveFlags;
int				CReyes::numVertexSamples;



///////////////////////////////////////////////////////////////////////
// Class				:	CReyes::CBucket
// Method				:	CBucket
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CReyes::CBucket::CBucket() {
	objects			=	NULL;
	queue			=	NULL;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CReyes::CBucket
// Method				:	~CBucket
// Description			:	Dtor
// Return Value			:	-
// Comments				:6
CReyes::CBucket::~CBucket() {
}

///////////////////////////////////////////////////////////////////////
// Class				:	CReyes
// Method				:	CReyes
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CReyes::CReyes(int thread) : CShadingContext(thread) {
	int			cx,cy;

	// Allocate the buckets
	osCreateMutex(bucketMutex);
	buckets	=	new CBucket**[CRenderer::yBuckets];
	for (cy=0;cy<CRenderer::yBuckets;cy++) {
		buckets[cy]	=	new CBucket*[CRenderer::xBuckets];

		for (cx=0;cx<CRenderer::xBuckets;cx++) {
			buckets[cy][cx]						=	new CBucket;
		}
	}

	// The length of a raster vertex
	if (CRenderer::flags & OPTIONS_FLAGS_SAMPLEMOTION)	numVertexSamples	=	(CRenderer::numExtraSamples + 10)*2;
	else												numVertexSamples	=	(CRenderer::numExtraSamples + 10);

	extraPrimitiveFlags	=	0;
	if (CRenderer::numExtraSamples > 0)	extraPrimitiveFlags	|=	RASTER_EXTRASAMPLES;
	if (CRenderer::aperture != 0)		extraPrimitiveFlags	|=	RASTER_FOCALBLUR;

	// Init the stats
	numGridsRendered	=	0;
	numQuadsRendered	=	0;
	numGridsShaded		=	0;
	numGridsCreated		=	0;
	numVerticesCreated	=	0;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CReyes
// Method				:	~CReyes
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CReyes::~CReyes() {
	int		x,y;
	CBucket	*cBucket;

	osLock(bucketMutex);

	// Ditch the buckets
	for (y=0;y<CRenderer::yBuckets;y++) {
		for (x=0;x<CRenderer::xBuckets;x++) {
			if ((cBucket = buckets[y][x]) != NULL)	{
				CRasterObject		*allObjects	=	cBucket->objects;

				flushObjects(allObjects);

				delete buckets[y][x];
			}
		}
		delete [] buckets[y];
	}
	delete [] buckets;

	// Get rid of the bucket mutex
	osUnlock(bucketMutex);		// Unlock the mutex
	osDeleteMutex(bucketMutex);	// Destroy the _unlocked_ mutex

	// Update the global stats
	stats.numRasterGridsCreated		+=	numGridsCreated;
	stats.numRasterVerticesCreated	+=	numVerticesCreated;
	stats.numRasterGridsShaded		+=	numGridsShaded;
	stats.numRasterGridsRendered	+=	numGridsRendered;
	stats.numRasterQuadsRendered	+=	numQuadsRendered;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CReyes
// Method				:	renderingLoop
// Description			:	This is the rendering loop for the thread
// Return Value			:	-
// Comments				:
void		CReyes::renderingLoop() {
	CRenderer::CJob	job;

#define computeExtends																									\
	bucketPixelLeft		=	currentXBucket*CRenderer::bucketWidth;														\
	bucketPixelTop		=	currentYBucket*CRenderer::bucketHeight;														\
	bucketPixelWidth	=	min(CRenderer::bucketWidth,		CRenderer::xPixels-bucketPixelLeft);						\
	bucketPixelHeight	=	min(CRenderer::bucketHeight,	CRenderer::yPixels-bucketPixelTop);							\
	tbucketLeft			=	bucketPixelLeft*CRenderer::pixelXsamples - CRenderer::xSampleOffset;						\
	tbucketTop			=	bucketPixelTop*CRenderer::pixelYsamples - CRenderer::ySampleOffset;							\
	tbucketRight		=	(bucketPixelLeft + bucketPixelWidth)*CRenderer::pixelXsamples - CRenderer::xSampleOffset;	\
	tbucketBottom		=	(bucketPixelTop + bucketPixelHeight)*CRenderer::pixelYsamples - CRenderer::ySampleOffset;

	// This is da loop
	while(TRUE) {

		// Get the job from the renderer
		CRenderer::dispatchJob(thread,job);

		// Process the job
		if (job.type == CRenderer::CJob::TERMINATE) {
			
			// End the context, cleanup of incomplete buckets
			// is in the destructor
			break;
		} else if (job.type == CRenderer::CJob::BUCKET) {
			const int	x	=	job.xBucket;
			const int	y	=	job.yBucket;

			assert(x < CRenderer::xBuckets);
			assert(y < CRenderer::yBuckets);

			// Skip the buckets reach the bucket we want
			while((currentXBucket != x) || (currentYBucket != y)) {
				computeExtends;
				skip();
			}


			// Render the bucket
			computeExtends;
			render();
		} else {
			error(CODE_BUG,"Invalid job for the hider\n");
			break;
		}
	}

#undef computeExtends

}



///////////////////////////////////////////////////////////////////////
// Class				:	CReyes
// Method				:	render
// Description			:	Render the current bucket
// Return Value			:	-
// Comments				:
void	CReyes::render() {
	CRasterObject	*cObject;
	CPqueue			objectQueue;

	__logBucketStart(currentXBucket,currentYBucket);

	// Initialize the opaque depths
	maxDepth					=	C_INFINITY;

	// Insert the objects into the queue
	osLock(bucketMutex);
	CBucket			*cBucket	=	buckets[currentYBucket][currentXBucket];
	int				nullBucket	=	(cBucket->objects == NULL);
	int				noObjects	=	TRUE;
	cBucket->queue				=	&objectQueue;
	while((cObject=cBucket->objects) != NULL)	{
		__logObjectDequeue(cObject,currentXBucket,currentYBucket);
		cBucket->objects		=	cObject->next[thread];
		objectQueue.insert(cObject);
	}
	osUnlock(bucketMutex);

	// Init the rasterizer
	rasterBegin(	bucketPixelWidth,
					bucketPixelHeight,
					tbucketLeft,
					tbucketTop,
					nullBucket);

	// Process the objects and patches
	while((cObject = objectQueue.get(bucketMutex)) != NULL) {

		// Is the object behind the maximum opaque depth ?
		if (cObject->zmin < maxDepth) {
			
			__logObjectRasterizeDice(cObject,currentXBucket,currentYBucket);

			// Is this a grid ?
			if (cObject->grid) {
				CRasterGrid	*grid	=	(CRasterGrid *) cObject;
				
				// Update the stats
				numGridsRendered++;
				numQuadsRendered	+=	grid->udiv*grid->vdiv;

				// Render the grid
				rasterDrawPrimitives(grid);

				// Defer the object
				CRasterObject		*objectsToDelete	=	NULL;
				osLock(bucketMutex);
				objectDefer(cObject);
				osUnlock(bucketMutex);

				// Delete the objects we do not need
				flushObjects(objectsToDelete);

				// We rendered objects
				noObjects	=	FALSE;
				
				continue;
			} else {
				// Dice the object
				osLock(cObject->mutex);

				// Did we dice this object before ?
				if (cObject->diced == FALSE) {
					if(probeArea(cObject->xbound,cObject->ybound,
						tbucketRight - tbucketLeft + 2*CRenderer::xSampleOffset,
						tbucketBottom - tbucketTop + 2*CRenderer::ySampleOffset,
						tbucketLeft,
						tbucketTop,
						cObject->zmin)) {

						cObject->object->dice(this);
						cObject->diced	=	TRUE;
					} else {
						// We have discovered that the object is occluded
						// defer it
						CRasterObject		*objectsToDelete	=	NULL;
						osUnlock(cObject->mutex);
						osLock(bucketMutex);				
						objectDefer(cObject);
						osUnlock(bucketMutex);
						flushObjects(objectsToDelete);
						continue;
					}
				}

				cObject->refCount--;
				if (cObject->refCount == 0) {
					// Get rid of the object
					deleteObject(cObject);
				} else {
					// Unlock the object
					osUnlock(cObject->mutex);
				}

				// Keep going
				continue;
			}

			
		} else {
			osLock(bucketMutex);

			CRasterObject	**allObjects		=	objectQueue.allItems + 1;
			int				i					=	objectQueue.numItems - 1;
			CRasterObject	*objectsToDelete	=	NULL;
			
			// We killed this bucket
			buckets[currentYBucket][currentXBucket]	=	NULL;

			// Defer the current object
			__logObjectOpacityCull(cObject,currentXBucket,currentYBucket);
			objectDefer(cObject);

			// Defer the rest of the objects
			for (;i>0;i--) {
				cObject			=	*allObjects++;
				__logObjectOpacityCull(cObject,currentXBucket,currentYBucket);
				objectDefer(cObject);
			}

			objectQueue.numItems					=	1;
			buckets[currentYBucket][currentXBucket]	=	NULL;

			osUnlock(bucketMutex);

			// Delete the objects we do not need
			flushObjects(objectsToDelete);

			osLock(bucketMutex);

			break;
		}
	}

	__logBucketTerminate(currentXBucket,currentYBucket);

	// All objects must be processed
	buckets[currentYBucket][currentXBucket]	=	NULL;
	assert(cBucket->objects == NULL);
	assert(cBucket->queue->numItems == 1);

	osUnlock(bucketMutex);

	// Begin a new memory page
	memBegin(threadMemory);

		// Allocate the framebuffer area (from the thread memory)
		float			*pixelBuffer		=	(float *) ralloc(CRenderer::bucketWidth*CRenderer::bucketHeight*CRenderer::numSamples*sizeof(float),threadMemory);

		// Get the framebuffer
		rasterEnd(pixelBuffer,noObjects);
	
		// Mark the first thread
		#if 0
		if (thread == 1) {
			pixelBuffer[5]	=	1;
		} else if (thread == 0) {
			pixelBuffer[6]	=	1;
		}
		#endif
		
		// Flush the data to the out devices
		CRenderer::commit(bucketPixelLeft,bucketPixelTop,bucketPixelWidth,bucketPixelHeight,pixelBuffer);
		
		// Send bucket data if we're a netrender
		if (CRenderer::netClient != INVALID_SOCKET) {
			CRenderer::sendBucketDataChannels(currentXBucket,currentYBucket);
		}

	// Restore the memory
	memEnd(threadMemory);

	// Lock the bucket one more time
	osLock(bucketMutex);

	// Just have rendered this bucket, so deallocate it
	assert(cBucket->objects == NULL);
	delete cBucket;

	// Advance the bucket
	currentXBucket++;
	if (currentXBucket == CRenderer::xBuckets) {		
		currentXBucket	=	0;
		currentYBucket++;
	}

	// Unlock the bucket
	osUnlock(bucketMutex);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CReyes
// Method				:	skip
// Description			:	Skip the current bucket
// Return Value			:
// Comments				:
void	CReyes::skip() {
	CRasterObject		*cObject;
	CBucket				*cBucket;
	CRasterObject		*objectsToDelete	=	NULL;

	// Defer the objects
	osLock(bucketMutex);
	cBucket	= buckets[currentYBucket][currentXBucket];

	__logBucketSkip(currentXBucket,currentBucket);

	while((cObject = cBucket->objects) != NULL) {
		cBucket->objects	=	cObject->next[thread];
		__logObjectSkip(cObject,currentXBucket,currentBucket);
		objectDefer(cObject);
	}

	// Just have rendered this bucket, so deallocate it
	delete cBucket;
	buckets[currentYBucket][currentXBucket]	=	NULL;

	// Advance the bucket
	currentXBucket++;
	if (currentXBucket == CRenderer::xBuckets) {		
		currentXBucket	=	0;
		currentYBucket++;
	}
	osUnlock(bucketMutex);

	// Delete the objects we do not need
	flushObjects(objectsToDelete);
}























///////////////////////////////////////////////////////////////////////
// Class				:	CReyes
// Method				:	drawObject
// Description			:	Draw an object
// Return Value			:	-
// Comments				:	Thread safe
void		CReyes::drawObject(CObject *object) {
	float				xmin,xmax,ymin,ymax;
	float				x[4],y[4];
	int					i;
	const float			*bmin	=	object->bmin;
	const float			*bmax	=	object->bmax;

	// Trivial reject
	if (bmax[COMP_Z] < CRenderer::clipMin)	{	return;	}
	if (bmin[COMP_Z] > CRenderer::clipMax)	{	return;	}

	// Clamp da bounding box
	const float	zmin	=	max(bmin[COMP_Z],CRenderer::clipMin);
	const float	zmax	=	min(bmax[COMP_Z],CRenderer::clipMax);

	assert(zmin <= zmax);
	
	// Compute the projected extend of the bound in the pixel space
	if (CRenderer::projection == OPTIONS_PROJECTION_PERSPECTIVE) {
		if (zmin < C_EPSILON)	{					// Spanning the eye plane ?
			if (CRenderer::inFrustrum(bmin,bmax)) {	// Are we in the frustrum ?
													// If we can not make the perspective divide
													// Go ahead and process the object now
				object->dice(this);
			}

			return;
		}

		// Do the perspective divide and figure put the extend on the screen
		const double	invMin	=	CRenderer::imagePlane	/	(double) zmin;
		const double	invMax	=	CRenderer::imagePlane	/	(double) zmax;

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

	xmin		-=	CRenderer::pixelLeft;
	xmax		-=	CRenderer::pixelLeft;
	ymin		-=	CRenderer::pixelTop;
	ymax		-=	CRenderer::pixelTop;

	// Account for the depth of field
	if (CRenderer::aperture != 0) {
		const	float	mcoc	=	max(cocScreen(zmin),cocScreen(zmax));
		xmin					=	xmin-mcoc;
		xmax					=	xmax+mcoc;
		ymin					=	ymin-mcoc;
		ymax					=	ymax+mcoc;
	}

	// Convert to samples
	xmin	*=	CRenderer::dSampledx;
	ymin	*=	CRenderer::dSampledy;
	xmax	*=	CRenderer::dSampledx;
	ymax	*=	CRenderer::dSampledy;

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
	if (xmin > CRenderer::sampleClipRight)		return;
	if (ymin > CRenderer::sampleClipBottom)		return;
	if (xmax < CRenderer::sampleClipLeft)		return;
	if (ymax < CRenderer::sampleClipTop)		return;

	xmin							=	max(xmin,0);
	ymin							=	max(ymin,0);
	xmax							=	min(xmax,CRenderer::sampleClipRight);
	ymax							=	min(ymax,CRenderer::sampleClipBottom);

	// Record the object
	CRasterObject	*cObject		=	newObject(object);
	cObject->xbound[0]				=	(int) floor(xmin);	// Save the bound of the object for future reference
	cObject->xbound[1]				=	(int) floor(xmax);
	cObject->ybound[0]				=	(int) floor(ymin);
	cObject->ybound[1]				=	(int) floor(ymax);

	// disable gross opacity culling for objects which need hidden surfaces shaded
	// this is only OK because cObject->zmin is not used to update the max opaque depth
	if (object->attributes->flags & ATTRIBUTES_FLAGS_SHADE_HIDDEN)
		cObject->zmin				=	-C_INFINITY;
	else
		cObject->zmin				=	zmin;

	// Insert the object into the bucket its in
	insertObject(cObject);
}

























///////////////////////////////////////////////////////////////////////
// Class				:	CReyes
// Method				:	drawGrid
// Description			:	Draw a grid
// Return Value			:	-
// Comments				:	Thread safe
void		CReyes::drawGrid(CSurface *object,int udiv,int vdiv,float umin,float umax,float vmin,float vmax) {
	// Create a grid on the surface
	CRasterGrid			*nGrid;

	// Initialize the grid
	nGrid			=	newGrid(object,FALSE,(udiv+1),(vdiv+1));	
	nGrid->dim		=	SHADING_2D_GRID;
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
// Method				:	drawPoints
// Description			:	Draw bunch of points
// Return Value			:	-
// Comments				:	Thread safe
void		CReyes::drawPoints(CSurface *object,int numPoints) {
	// Create a grid on the surface
	CRasterGrid			*nGrid;
															// Create the grid
	nGrid			=	newGrid(object,TRUE,numPoints,1);
	nGrid->dim		=	SHADING_0D;
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
void		CReyes::shadeGrid(CRasterGrid *grid,int Ponly) {

	// Make sure we shade a grid only once
	if (Ponly == FALSE) {
		osLock(grid->mutex);

		if (!(grid->flags & RASTER_UNSHADED)) {
			osUnlock(grid->mutex);
			return;
		}
	}

	if (grid->dim == SHADING_0D) {
		// This is a 0 dimensional point cloud
		int					i;
		float				**varying		=	currentShadingState->varying;
		int					numPoints		=	grid->vdiv;
		float				*sizeArray;
		CSurface			*object			=	(CSurface *) (grid->object);
		const CAttributes	*attributes		=	object->attributes;
		float				*sizes;

		if (Ponly) {
			// Set the flags
			grid->flags	=	extraPrimitiveFlags | RASTER_POINT | RASTER_UNSHADED;
			if (attributes->flags & ATTRIBUTES_FLAGS_SHADE_HIDDEN) 		grid->flags	|= RASTER_UNDERCULL | RASTER_SHADE_HIDDEN;
			if (attributes->flags & ATTRIBUTES_FLAGS_SHADE_BACKFACE)	grid->flags	|= RASTER_UNDERCULL | RASTER_SHADE_BACKFACE;

			// Do we have motion blur?
			if ((CRenderer::flags & OPTIONS_FLAGS_SAMPLEMOTION) && (object->moving())) grid->flags	|= RASTER_MOVING;

			// Reset the size variable
			varying[VARIABLE_WIDTH][0]			=	-C_INFINITY;
			varying[VARIABLE_CONSTANTWIDTH][0]	=	-C_INFINITY;

			// Shade the points
			displace(object,numPoints,1,SHADING_0D,PARAMETER_BEGIN_SAMPLE | PARAMETER_P);

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
				sizes[0]	=	(*sizeArray++*0.5f);
			}

		} else {
			float			*Oi;

			// Sanity check
			numGridsShaded++;

			// Shade the points
			shade(object,numPoints,1,SHADING_0D,PARAMETER_BEGIN_SAMPLE | PARAMETER_P);

			// Copy the point samples
			copySamples(numPoints,varying,grid->vertices,0);

			// Check if we're opaque
			for (Oi=varying[VARIABLE_OI],i=numPoints;i>0;i--,Oi+=3) {
				if ((Oi[0] < CRenderer::opacityThreshold[0]) | (Oi[1] < CRenderer::opacityThreshold[1]) | (Oi[2] < CRenderer::opacityThreshold[2])) {
					grid->flags	|=	RASTER_TRANSPARENT;
					break;
				}
			}
			
			// We require matte and LOD flagged grids to have been shaded / displaced
			if (attributes->flags & ATTRIBUTES_FLAGS_MATTE)				grid->flags	|= RASTER_MATTE;
			if (attributes->flags & ATTRIBUTES_FLAGS_LOD) 				grid->flags	|= RASTER_LOD;
		}

		// Do we have motion ?
		if (grid->flags & RASTER_MOVING) {

			if (Ponly) {
				// Reset the size variable
				varying[VARIABLE_WIDTH][0]			=	-C_INFINITY;
				varying[VARIABLE_CONSTANTWIDTH][0]	=	-C_INFINITY;

				// Shade the points
				displace(object,numPoints,1,SHADING_0D,PARAMETER_END_SAMPLE | PARAMETER_P);

				// Figure out the size of the points
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
					sizes[1]	=	(*sizeArray++)*0.5f;
				}
			} else {
				// Shade the points
				shade(object,numPoints,1,SHADING_0D,PARAMETER_END_SAMPLE | PARAMETER_P);

				// Copy the point samples
				copySamples(numPoints,varying,grid->vertices,1);
			}
		}
	} else {
		assert(grid->dim == SHADING_2D_GRID);

		// This is a 2 dimensional surface
		int					i,j;
		int					k;
		float				**varying	=	currentShadingState->varying;
		CSurface			*object		=	(CSurface *) (grid->object);
		const CAttributes	*attributes	=	object->attributes;
		const int			udiv		=	grid->udiv;
		const int			vdiv		=	grid->vdiv;
		float				*u;
		float				*v;
		float				*time;
		double				cu,cv;
		float				*Oi;


		const int			numVertices	=	(udiv+1)*(vdiv+1);			// The number of vertices to shade
		const double		ustart		=	grid->umin;					// The minimum step sizes
		const double		ustep		=	(grid->umax - ustart) / (double) udiv;
		const double		vstart		=	grid->vmin;
		const double		vstep		=	(grid->vmax - vstart) / (double) vdiv;

		assert(numVertices <= (int) CRenderer::maxGridSize);

		// Shade the points in the patch
		u			=	varying[VARIABLE_U];
		v			=	varying[VARIABLE_V];
		time		=	varying[VARIABLE_TIME];

		// Shade the minimum grid
		for (j=vdiv,cv=vstart;j>=0;j--,cv+=vstep) {
			for (i=udiv,cu=ustart;i>=0;i--,cu+=ustep) {
				*u++		=	(float) cu;
				*v++		=	(float) cv;
				*time++		=	0;
			}
		}

		if (Ponly) {
		
			// Set the flags
			if (attributes->flags & ATTRIBUTES_FLAGS_DOUBLE_SIDED) {
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

			// Do we have motion blur ?
			if ((CRenderer::flags & OPTIONS_FLAGS_SAMPLEMOTION) && (object->moving())) grid->flags		|=	RASTER_MOVING;

			// Displace the sucker
			displace(object,udiv+1,vdiv+1,SHADING_2D_GRID,PARAMETER_BEGIN_SAMPLE | PARAMETER_P);

			// Project the P into samples
			camera2samples(numVertices,varying[VARIABLE_P]);
			
			// Save the vertex data
			copyPoints(numVertices,varying,grid->vertices,0);
		} else {
			// Sanity check
			numGridsShaded++;

			// Shade the sucker
			shade(object,udiv+1,vdiv+1,SHADING_2D_GRID,PARAMETER_BEGIN_SAMPLE | PARAMETER_P);

			// Project the P into samples
			camera2samples(numVertices,varying[VARIABLE_P]);

			// Save the vertex data
			copySamples(numVertices,varying,grid->vertices,0);

			// Check the transparency
			Oi			=	varying[VARIABLE_OI];
			for (k=numVertices;k>0;k--,Oi+=3) {
				if ((Oi[0] < CRenderer::opacityThreshold[0]) | (Oi[1] < CRenderer::opacityThreshold[1]) | (Oi[2] < CRenderer::opacityThreshold[2])) {
					grid->flags	|=	RASTER_TRANSPARENT;
					break;
				}
			}
			
			// We require matte and LOD flagged grids to have been shaded / displaced
			if (attributes->flags & ATTRIBUTES_FLAGS_MATTE)			 grid->flags	|= RASTER_MATTE;
			if (attributes->flags & ATTRIBUTES_FLAGS_LOD) 			 grid->flags	|= RASTER_LOD;
		}

		// Do we have motion blur ?
		if (grid->flags & RASTER_MOVING) {
			u			=	varying[VARIABLE_U];
			v			=	varying[VARIABLE_V];
			time		=	varying[VARIABLE_TIME];

			// Shade the minimum grid
			for (j=vdiv,cv=vstart;j>=0;j--,cv+=vstep) {
				for (i=udiv,cu=ustart;i>=0;i--,cu+=ustep) {
					*u++		=	(float) cu;
					*v++		=	(float) cv;
					*time++		=	1;
				}
			}

			if (Ponly) {
				// Shade the sucker
				displace(object,udiv+1,vdiv+1,SHADING_2D_GRID,PARAMETER_END_SAMPLE | PARAMETER_P);

				// Project the P into samples
				camera2samples(numVertices,varying[VARIABLE_P]);

				// Copy the vertex data
				copyPoints(numVertices,varying,grid->vertices,1);
			} else {
				// Shade the sucker
				shade(object,udiv+1,vdiv+1,SHADING_2D_GRID,PARAMETER_END_SAMPLE | PARAMETER_P);

				// Project the P into samples
				camera2samples(numVertices,varying[VARIABLE_P]);

				// Copy the vertex data
				copySamples(numVertices,varying,grid->vertices,1);
			}
		}
	}

	// If we've been shading, reset the flags and unlock the mutex
	if (Ponly == FALSE)	{
		assert(grid->flags & RASTER_UNSHADED);
		grid->flags		&=	~(RASTER_UNSHADED | RASTER_SHADE_HIDDEN | RASTER_SHADE_BACKFACE | RASTER_UNDERCULL);

		osUnlock(grid->mutex);
	}
}



///////////////////////////////////////////////////////////////////////
// Class				:	CReyes
// Method				:	copyPoints
// Description			:	Copy the point data
// Return Value			:	-
// Comments				:
void			CReyes::copyPoints(int numVertices,float **varying,float *vertices,int stage) {
	const	float	*P		=	varying[VARIABLE_P];
	const	int		disp	=	(CRenderer::numExtraSamples + 10)*stage;
	int				i;

	// Copy the samples
	vertices	+=	disp;
	for (i=numVertices;i>0;i--,P+=3,vertices+=numVertexSamples) {
		movvv(vertices,P);
	}

	// If we have depth of field, compute that
	if ((CRenderer::aperture != 0) && (stage == 0)) {
	
		assert(disp == 0);
		
		// Roll back to the beginning
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
// Comments				:	Thread safe
void			CReyes::copySamples(int numVertices,float **varying,float *vertices,int stage) {
	const	float	*C		=	varying[VARIABLE_CI];
	const	float	*O		=	varying[VARIABLE_OI];
	int				i,j,k,l;
	const	int		disp	=	(CRenderer::numExtraSamples + 10)*stage;
	const	int		*cOrder	=	CRenderer::sampleOrder;
	const	float	*s;
	float			*d;

	// Copy the color and opacity
	for (d=vertices+disp,i=numVertices;i>0;i--,C+=3,O+=3,d+=numVertexSamples) {
		movvv(d+3,C);
		movvv(d+6,O);
	}

	// Do the extra samples
	k	=	disp + 10;
	for (i=0;i<CRenderer::numExtraChannels;i++) {
		const int outType			= *cOrder++;
		const int channelSamples	= *cOrder++;

		// This is the source
		s			=	varying[outType];
		
		// This is where we want to save it
		d			=	vertices + k;
			
		switch(channelSamples) {
		case 0:
			break;
		case 1:
			for (j=0;j<numVertices;j++,d+=numVertexSamples) {
				d[0]	=	*s++;
			}
			k++;
			break;
		case 2:
			for (j=0;j<numVertices;j++,d+=numVertexSamples) {
				d[0]	=	*s++;
				d[1]	=	*s++;
			}
			k	+=	2;
			break;
		case 3:
			for (j=0;j<numVertices;j++,d+=numVertexSamples) {
				d[0]	=	*s++;
				d[1]	=	*s++;
				d[2]	=	*s++;
			}
			k	+=	3;
			break;
		case 4:
			for (j=0;j<numVertices;j++,d+=numVertexSamples) {
				d[0]	=	*s++;
				d[1]	=	*s++;
				d[2]	=	*s++;
				d[3]	=	*s++;
			}
			k	+=	4;
			break;
		default:
			for (j=0;j<numVertices;j++,d+=numVertexSamples) {
				for (l=0;l<channelSamples;l++) d[l]	=	*s++;
			}
			k	+=	channelSamples;
		}
	}
}








































///////////////////////////////////////////////////////////////////////
// Class				:	CReyes
// Method				:	newObject
// Description			:	Allocate a new raster object
// Return Value			:	-
// Comments				:	Thread safe
CReyes::CRasterObject		*CReyes::newObject(CObject *cObject) {
	CRasterObject	*nObject;

	nObject				=	new CRasterObject;
	nObject->next		=	new CRasterObject*[CRenderer::numThreads];
	nObject->object		=	cObject;	
	nObject->diced		=	FALSE;	// FIXME: Can combine diced and grid into one integer
	nObject->grid		=	FALSE;
	nObject->refCount	=	0;
	osCreateMutex(nObject->mutex);

	cObject->attach();

	atomicIncrement(&stats.numRasterObjects);

	return nObject;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CReyes
// Method				:	newGrid
// Description			:	Initialize a grid by copying the points
// Return Value			:	-
// Comments				:	Thread safe
CReyes::CRasterGrid		*CReyes::newGrid(CSurface *object,int points,int numVerticesU,int numVerticesV) {
	CRasterGrid		*grid;

	const int numVertices = numVerticesU*numVerticesV;

	grid				=	new CRasterGrid;
	grid->next			=	new CRasterObject*[CRenderer::numThreads];
	grid->object		=	object;
	grid->diced			=	TRUE;
	grid->grid			=	TRUE;
	grid->refCount		=	0;
	osCreateMutex(grid->mutex);

	// Allocate grid specific fields
	grid->numVertices	=	numVertices;
	grid->vertices		=	new float[numVertices*numVertexSamples];
	if (points) {
		grid->bounds	=	new int[numVertices*4];
		grid->sizes		=	new float[numVertices*2];
	} else {
		grid->bounds	=	new int[(numVerticesU-1)*(numVerticesV-1)*4];
		grid->sizes		=	NULL;
	}

	object->attach();

	atomicIncrement(&stats.numRasterGrids);
	numGridsCreated++;
	numVerticesCreated	+=	numVertices;

	return grid;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CReyes
// Method				:	deleteObject
// Description			:	Delete a raster object
// Return Value			:	-
// Comments				:	detach is not thread safe. dObject->mutex must be locked
void				CReyes::deleteObject(CRasterObject *dObject) {

	assert(dObject->refCount == 0);

	// Detach from the object
	dObject->object->detach();
	
	__logObjectDelete(dObject,currentXBucket,currentYBucket);
	__recordObjectDelete(dObject);

	if (dObject->grid)	{
		CRasterGrid *grid	=	(CRasterGrid *) dObject;

		// Decrement the active grid counter
		atomicDecrement(&stats.numRasterGrids);

		// Delete the grid data
		osUnlock(dObject->mutex);		// Unlock the mutex
		osDeleteMutex(dObject->mutex);	// Destroy the _unlocked_ mutex
		delete [] dObject->next;
		delete [] grid->vertices;
		delete [] grid->bounds;
		if (grid->sizes != NULL) delete [] grid->sizes;
		delete grid;
	} else {

		// Decrement the active object counter
		atomicDecrement(&stats.numRasterObjects);

		// Delete the object data
		osUnlock(dObject->mutex);		// Unlock the mutex
		osDeleteMutex(dObject->mutex);	// Destroy the _unlocked_ mutex
		delete [] dObject->next;
		delete dObject;
	}
}








///////////////////////////////////////////////////////////////////////
// Class				:	CReyes
// Method				:	insertGrid
// Description			:	Compute the grid bound and insert the grid into the correct bucket
// Return Value			:	-
// Comments				:	Thread safe
void		CReyes::insertGrid(CRasterGrid *grid,int flags) {
	// Compute the grid bound and insert it
	int				i;
	const float		*cVertex;

	// Compute the bound of the grid
	float xmin	=	C_INFINITY;
	float ymin	=	C_INFINITY;
	float zmin	=	C_INFINITY;
	float xmax	=	-C_INFINITY;
	float ymax	=	-C_INFINITY;
	float zmax	=	-C_INFINITY;
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

		for (cVertex=grid->vertices+CRenderer::numExtraSamples+10,i=grid->numVertices;i>0;i--,cVertex+=numVertexSamples) {
			if (cVertex[0] < xmin)	xmin	=	cVertex[0];
			if (cVertex[1] < ymin)	ymin	=	cVertex[1];
			if (cVertex[2] < zmin)	zmin	=	cVertex[2];
			if (cVertex[0] > xmax)	xmax	=	cVertex[0];
			if (cVertex[1] > ymax)	ymax	=	cVertex[1];
			if (cVertex[2] > zmax)	zmax	=	cVertex[2];
		}
	}

	if (CRenderer::aperture != 0) {
		// Expand the bound by the maximum focal blur amount
		const	float	coc1	=	cocSamples(zmin);
		const	float	coc2	=	cocSamples(zmax);
		const	float	mcoc	=	max(coc1,coc2);

		xmin	-=	mcoc;
		xmax	+=	mcoc;
		ymin	-=	mcoc;
		ymax	+=	mcoc;
	}


	// Trivial reject
	if ((xmin > CRenderer::sampleClipRight)	|| (ymin > CRenderer::sampleClipBottom) || (xmax < CRenderer::sampleClipLeft) || (ymax < CRenderer::sampleClipTop)) {
		deleteObject(grid);
		return;
	}

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
				P				+=	CRenderer::numExtraSamples + 10;

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

			// Expand the bound by the focal blur amount
			if (CRenderer::aperture != 0) {
				const float coc = vertices[9];
				
				xbound[0] -= coc;
				xbound[1] += coc;
				ybound[0] -= coc;
				ybound[1] += coc;
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
		const int			udiv			=	grid->udiv;
		const int			vdiv			=	grid->vdiv;
		const float			*vertices		=	grid->vertices;
		int					*bounds			=	grid->bounds;
		float				originalArea	=	0;	// This is the total area of the grid without mb/dof
		float				expandedArea	=	0;	// This is the total area of the grid with mb/dof

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

				originalArea	+=	(xbound[1] - xbound[0])*(ybound[1] - ybound[0]);

				if (grid->flags & RASTER_MOVING) {
					P	=	cVertex + CRenderer::numExtraSamples + 10;
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

				if (CRenderer::aperture != 0) {
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

				expandedArea	+=	(xbound[1] - xbound[0])*(ybound[1] - ybound[0]);

				bounds[0]	=	(int) floor(xbound[0]);		// xmin
				bounds[1]	=	(int) floor(xbound[1]);		// xmax
				bounds[2]	=	(int) floor(ybound[0]);		// ymin
				bounds[3]	=	(int) floor(ybound[1]);		// ymax
			}
		}

		// Check if we have xtreme mb/dof
		if ((expandedArea / originalArea) > 10.0f) {
			grid->flags	|=	RASTER_XTREME;
		}
	}


	xmin							=	max(xmin,0);
	ymin							=	max(ymin,0);

	// Save the bound of the grid
	grid->xbound[0]					=	(int) floor(xmin);
	grid->xbound[1]					=	(int) floor(xmax);
	grid->ybound[0]					=	(int) floor(ymin);
	grid->ybound[1]					=	(int) floor(ymax);

	// disable gross opacity culling for objects which need hidden surfaces shaded
	// this is only OK because cObject->zmin is not used to update the max opaque depth
	if (grid->flags & RASTER_SHADE_HIDDEN)
		grid->zmin					=	-C_INFINITY;
	else
		grid->zmin					=	zmin;

	// Insert the object into the bucket its in
	insertObject(grid);
}



///////////////////////////////////////////////////////////////////////
// Class				:	CReyes
// Method				:	insertObject
// Description			:	Insert an object into all hiders
// Return Value			:
// Comments				:	* Called from parse thread *
void	CReyes::insertObject(CRasterObject *object) {
	
	// For every thread
	int			sx = xbucket(object->xbound[0]);
	int			sy = ybucket(object->ybound[0]);
	const int	ex = xbucketNext(object->xbound[1]);
	const int	ey = ybucketNext(object->ybound[1]);

	// Trivial reject check
	if (	(sx >= CRenderer::xBuckets) || 
			(sy >= CRenderer::yBuckets) ||
			(ex < 0) ||
			(ey < 0)) {

		// Delete and return
		deleteObject(object);
		return;
	}

	// Guard
	sx			=	max(0,sx);
	sy			=	max(0,sy);

	int			i;
	int			refCount	=	0;

	// A fake refcount to prevent other threads from deallocating this object
	object->refCount	=	CRenderer::numThreads + 1;

	// Insert the the object into every thread
	for (i=0;i<CRenderer::numThreads;i++) {
		CReyes		*hider	=	(CReyes *) CRenderer::contexts[i];
		int			bx		=	sx;
		int			by		=	sy;
		int			killObj	=	FALSE;
		CBucket		*cBucket;

		// Secure the area
		osLock(hider->bucketMutex);

		// Determine the bucket
		if (by <= hider->currentYBucket) {
			by	=	hider->currentYBucket;
			if (ey < hider->currentYBucket) {
				// This must have been caused by dicing an
				// object which was previously occluded, resulting
				// in objects in previous buckets, so we will
				// cause a deletion
				killObj = TRUE;
			}
			if (bx < hider->currentXBucket)	{
				bx	=	hider->currentXBucket;
				if (ey == hider->currentYBucket && ex < hider->currentXBucket) {
					// This must have been caused by dicing an
					// object which was previously occluded, resulting
					// in objects in previous buckets, so we will
					// cause a deletion
					killObj = TRUE;
				}
			}
		} else {
			if (bx < 0)	bx	=	0;
		}

		// We must be in bounds
		if (!killObj && (bx < CRenderer::xBuckets) && (by < CRenderer::yBuckets)) {

			// Normally, this bucket must almost exist
			// But because there is a mutex release between the time we set the bucket to NULL
			// and increment the bucket index, buckets[currentYBucket][currentXBucket] may be NULL
			// ---We can actually eliminate this while loop pretty easily---
			int cx = bx,cy = by;
			while((cBucket = hider->buckets[cy][cx]) == NULL) {
				cx++;
				if (cx == CRenderer::xBuckets || cx > ex) {
					// push down _only_
					cx	=	sx;
					if (cx < 0) cx = 0;
					cy++;
					if (cy == CRenderer::yBuckets || cy > ey) {
						break;
					}
				}
			}


			if (cBucket != NULL) {
				// Insert the object	
				refCount++;
				
				__logObjectInsert(cObject,cx,cy,i,cBucket->queue != NULL);
				
				if (cBucket->queue == NULL) {
					// The thread has not processed this bucket yet
					object->next[i]		=	cBucket->objects;
					cBucket->objects	=	object;
				} else {
					// The thread is processing this bucket
					cBucket->queue->insert(object);
				}
			}
		}

		// Release the mutex
		osUnlock(hider->bucketMutex);
	}

	// Check if we need to delete this object
	osLock(object->mutex);

	__recordObjectInsert(object,refCount);
	
	// Compute the reference count
	refCount	=	refCount + object->refCount - (CRenderer::numThreads + 1);
	assert(refCount >= 0);
	assert(refCount <= CRenderer::numThreads);

	// Did we kill the object ?
	if (refCount == 0) {
		object->refCount	=	0;	// restore a null reference count before deletion
		deleteObject(object);
	} else {
		object->refCount	=	refCount;
		osUnlock(object->mutex);
	}
}
