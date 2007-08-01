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
//  File				:	trace.cpp
//  Classes				:	CShadingContext
//  Description			:	This file implements raytracing functionality of the shading context
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "shading.h"
#include "stats.h"
#include "memory.h"
#include "points.h"
#include "options.h"
#include "renderer.h"
































///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	trace
// Description			:	Trace/Shade bunch of rays
// Return Value			:	-
// Comments				:	Assume the following fields of CRay have been set:
//							1. from
//							2. dir (must be unit length)
//							3. t
//							4. tmin
//							5. flags
void	CShadingContext::trace(CRayBundle *bundle) {
	int								i;
	const	COptions::CClipPlane	*cPlane;
	float							t;
	float							tt;
	float							**varying;

	// Compute some of the ray junk
	CRay		**rays	=	bundle->rays;
	int			numRays	=	bundle->numRays;

	assert(numRays != 0);

	for (i=0;i<numRays;i++) {
		CRay	*ray	=	rays[i];
		
		t				=	ray->t;
		
		// Check the ray against the clipping planes
		for (cPlane=CRenderer::clipPlanes;cPlane!=NULL;cPlane=cPlane->next) {
			tt	=	-(dotvv(cPlane->normal,ray->from)+cPlane->d) / dotvv(cPlane->normal,ray->dir);

			if ((tt > 0) && (tt < t))	t	=	tt;
		}

		ray->t					=	t;
		trace(ray);
	}

	// The transparency pass loop
	while(TRUE) {

		// Check if we should shade these rays
		if (bundle->postTraceAction() == FALSE) {
			return;
		} else {
			// This struct holds a bunch of rays that can be shaded together
			typedef struct TShadingGroup {
				CSurface		*object;
				CRay			**rays;
				int				numRays;
				TShadingGroup	*next;
			} TShadingGroup;

			TObjectHash		*objects		=	NULL;	// This holds the list of objects to be shaded
			TObjectHash		*cHash;						// The current hash
			TShadingGroup	*shadingGroups	=	NULL;	// Holds a list of shading groups

			// Check we have the hash table allocated
			assert(traceObjectHash != NULL);

			// Hash the rays into the table
			for (i=0;i<numRays;i++) {
				int			key;
				CRay		*cRay	=	rays[i];

				// This is more efficient on 64 bit platforms
				union {
					CObject		*pointer;
					uintptr_t	integer;
				} object;

				// Compute the hash key (fast and easy)
				object.pointer	=	cRay->object;
				key				=	(int) (	(object.integer >> 0) ^ 
											(object.integer >> 4) ^ 
											(object.integer >> 8) ^ 
											(object.integer >> 16)) & (SHADING_OBJECT_CACHE_SIZE - 1);

				cHash			=	traceObjectHash + key;

				if (cHash->object == cRay->object) {
					// Hash hit
				} else if (cHash->object == (CObject *) this) {
					// First entry
					cHash->object		=	cRay->object;
					cHash->numRays		=	0;
					cHash->rays			=	NULL;
					cHash->next			=	NULL;
					cHash->shadeNext	=	objects;
					objects				=	cHash;
				} else {
					// Search the hash
					for (;cHash!=NULL;cHash=cHash->next) {
						if (cHash->object == cRay->object)	break;
					}

					// Did we find it ?
					if (cHash == NULL) {
						cHash						=	(TObjectHash *) ralloc(sizeof(TObjectHash),threadMemory);
						cHash->object				=	cRay->object;
						cHash->numRays				=	0;
						cHash->rays					=	NULL;
						cHash->next					=	traceObjectHash[key].next;
						traceObjectHash[key].next	=	cHash;
						cHash->shadeNext			=	objects;
						objects						=	cHash;
					}
				}

				// Insert the ray into the hash
				cRay->object	=	(CSurface *) cHash->rays;
				cHash->rays		=	cRay;
				cHash->numRays++;
			}

			// Reconstruct the shading groups
			rays				+=	numRays;
			while((cHash=objects) != NULL) {
				CRay			*cRay;
				TShadingGroup	*cGroup	=	(TShadingGroup *) ralloc(sizeof(TShadingGroup),threadMemory);

				// Put the rays in this bin into an array
				for (cRay=cHash->rays;cRay!=NULL;cRay = (CRay *) (cRay->object)) {
					*(--rays)			=	cRay;	// Save the ray
				}

				// Save the shading group
				objects					=	cHash->shadeNext;
				cGroup->object			=	cHash->object;
				cGroup->rays			=	rays;
				cGroup->numRays			=	cHash->numRays;
				cHash->object			=	(CSurface *) this;
				cGroup->next			=	shadingGroups;
				shadingGroups			=	cGroup;
			}

			// Question: Why are we storing the rays from the end to the beginning ?
			// Answer: So that se start shading from the beginning and the bundles 
			//         can use the beginning of the rays array to store continuing rays

			// Shade the shading groups
			for (varying=currentShadingState->varying;shadingGroups!=NULL;shadingGroups=shadingGroups->next) {
				int	numShading;

				while((numShading = shadingGroups->numRays) > 0) {
					if (numShading > CRenderer::maxGridSize)	numShading	=	CRenderer::maxGridSize;
					
					// Restore the object pointers in the rays for the bundle code
					for (i=0;i<numShading;i++) {
						shadingGroups->rays[i]->object = shadingGroups->object;
					}

					if (shadingGroups->object != NULL) {
						shadingGroups->object->shade(this,numShading,shadingGroups->rays);
						bundle->postShade(numShading,shadingGroups->rays,varying);
					} else {
						bundle->postShade(numShading,shadingGroups->rays);
					}

					shadingGroups->numRays	-=	numShading;
					shadingGroups->rays		+=	numShading;
				}
				
			}

			// Tell the bundle that we're done with the rays
			bundle->post();

			// Are we done ?
			if ((numRays=bundle->numRays) == 0) {
				break;
			}
			
			// Keep tracing these rays
			assert(rays == bundle->rays);
			for (i=numRays;i>0;i--) {
				CRay	*cRay	=	*rays++;

				cRay->tmin		=	cRay->t + C_EPSILON;
				cRay->t			=	C_INFINITY;
				trace(cRay);
			}

			// Increment the traced ray counter
			rays				=	bundle->rays;
		}
	}
}








///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	traceEx
// Description			:	Trace/Shade bunch of rays
// Return Value			:	-
// Comments				:
void	CShadingContext::traceEx(CRayBundle *bundle) {
	if (currentRayDepth < CRenderer::maxRayDepth) {
		CShadingState	*savedState		=	currentShadingState;
		const char		*savedLabel		=	currentRayLabel;

		currentRayDepth++;
		currentRayLabel					=	bundle->label;

		if (freeStates == NULL)			freeStates	=	newState();

		currentShadingState				=	freeStates;
		freeStates						=	currentShadingState->next;
		currentShadingState->postShader	=	bundle->postShader;

		trace(bundle);

		currentRayDepth--;
		currentShadingState->next		=	freeStates;
		freeStates						=	currentShadingState;

		currentRayLabel					=	savedLabel;
		currentShadingState				=	savedState;

	} else {
		//GSHTODO: what about postTrace(), post() here??
		//Okan: postShade function (in this form) must take care of the rays that don't hit anything
		bundle->postShade(bundle->numRays,bundle->rays);
	}
}


// This is a temp class to hold the heap
class	CTraceObject {
public:
		float		tmin;
		CObject		*object;
};




///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	trace
// Description			:	Trace a single ray
// Return Value			:	-
// Comments				:	Assume the following fields of CRay have been set:
//							1. from
//							2. dir (must be unit length)
//							3. t
//							4. tmin
//							5. flags
void	CShadingContext::trace(CRay *ray) {

	
	CTraceObject		heapBase[TRACE_HEAP_SIZE + 1];
	CTraceObject		*heap		=	heapBase;
	int					numObjects	=	1;
	int					maxObjects	=	TRACE_HEAP_SIZE;
	
	// Compute the inverse of the ray direction first
	ray->invDir[0]	= 1.0 / (double) ray->dir[0];
	ray->invDir[1]	= 1.0 / (double) ray->dir[1];
	ray->invDir[2]	= 1.0 / (double) ray->dir[2];
	
	// Compute the first entry in the heap
	heap[1].tmin		=	nearestBox(CRenderer::root->bmin,CRenderer::root->bmax,ray->from,ray->invDir,ray->tmin,ray->t);
	heap[1].object		=	CRenderer::root;
	ray->jimp			=	urand();
	ray->object			=	NULL;

	numTracedRays++;

	// While we have objects in the heap, pop the object and process it
	while((numObjects > 0) && (heap[1].tmin < ray->t)) {
		CObject	*object		=	heap[1].object;

		// Remove the topmost item from da heap
		int			parent	=	1;
		int			child	=	2;
		const float	tmin	=	heap[numObjects].tmin;
		while(child < numObjects) {
			if (((child+1) < numObjects) && (heap[child].tmin > heap[child+1].tmin))	child++;

			if (tmin < heap[child].tmin)	break;

			heap[parent]	=	heap[child];
			parent			=	child;
			child			=	child+child;
		}
		heap[parent]	=	heap[numObjects];
		numObjects--;

		// If this is a real object, intersect it with the ray
		if ((object->flags & OBJECT_DUMMY) == 0) {
			object->intersect(this,ray);
		}

		// Is the object hierarchy ready ?
		if ((object->flags & OBJECT_HIERARCHY_READY) == 0) {
		
			// Lock the thing
			// IDEA: This mutex can be per object, but it would increase the dummy object overhead
			osLock(CRenderer::hierarchyMutex);
			if ((object->flags & OBJECT_HIERARCHY_READY) == 0) {
			
				// Do the clustering
				object->cluster(this);
				
				// Mark the object as ready
				object->flags		|=	OBJECT_HIERARCHY_READY;
			}
			osUnlock(CRenderer::hierarchyMutex);
		}
		
		// Insert the children objects into the queue
		CObject	*cChild;
		for (cChild=object->children;cChild!=NULL;cChild=cChild->sibling) {

			// Allocate more heap space if we need it (very unlikely)
			if (numObjects == maxObjects) {
				maxObjects					*=	2;
				CTraceObject	*newHeap	=	(CTraceObject *) ralloc((maxObjects+1)*sizeof(CTraceObject),threadMemory);
				memcpy(newHeap,heap,(numObjects+1)*sizeof(CTraceObject));
				heap						=	newHeap;
			}

			// Insert the child into the heap
			const float	tmin	=	nearestBox(cChild->bmin,cChild->bmax,ray->from,ray->invDir,ray->tmin,ray->t);
			
			if (tmin < ray->t) {
				// Maintain the heap
				int	child	=	++numObjects;
				int	parent	=	child >> 1;
				while ((child > 1) && (tmin < heap[parent].tmin)) {
					heap[child]			=	heap[parent];
					child				=	parent;
					parent				=	parent >> 1;
				}
				heap[child].tmin	=	tmin;
				heap[child].object	=	cChild;
			}
		}
	}
}

