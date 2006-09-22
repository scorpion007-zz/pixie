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
//  File				:	trace.cpp
//  Classes				:	CShadingContext
//  Description			:	This file implements raytracing functionality of the shading context
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "hierarchy.h"
#include "renderer.h"
#include "shading.h"
#include "stats.h"
#include "memory.h"
#include "output.h"
#include "points.h"












///////////////////////////////////////////////////////////////////////
// Class				:	TObjectHash
// Description			:	Holds an object hash root
// Comments				:
// Date last edited		:	8/16/2004
typedef struct TObjectHash {
	CSurface		*object;
	CRay			*rays;
	int				numRays;
	TObjectHash		*next;
	TObjectHash		*shadeNext;
} TObjectHash;




















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
// Date last edited		:	8/30/2002
void	CShadingContext::trace(CRayBundle *bundle) {
	int								i;
	const	COptions::CClipPlane	*cPlane;
	float							t;
	float							tt;
	CRay							**rays;
	int								numRays;
	float							**varying;

	// Compute some of the ray junk
	rays			=	bundle->rays;
	numRays			=	bundle->numRays;

	assert(numRays != 0);

	for (i=0;i<numRays;i++) {
		CRay	*ray	=	rays[i];
		
		t				=	ray->t;

		addvv(ray->to,ray->from,ray->dir);
		
		// Check the ray against the clipping planes
		for (cPlane=clipPlanes;cPlane!=NULL;cPlane=cPlane->next) {
			tt	=	-(dotvv(cPlane->normal,ray->from)+cPlane->d) / dotvv(cPlane->normal,ray->dir);

			if ((tt > 0) && (tt < t))	t	=	tt;
		}

		ray->invDir[COMP_X]		=	1/ray->dir[COMP_X];
		ray->invDir[COMP_Y]		=	1/ray->dir[COMP_Y];
		ray->invDir[COMP_Z]		=	1/ray->dir[COMP_Z];
		ray->t					=	t;
		ray->jimp				=	-1.0f;
		ray->lastXform			=	NULL;
		ray->object				=	NULL;
		hierarchy->intersect(ray);
	}

	// Increment the traced ray counter
	stats.numTracedRays	+=	numRays;

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
			if (traceObjectHash == NULL) {
				traceObjectHash	=	(TObjectHash *) frameMemory->alloc(sizeof(TObjectHash)*SHADING_OBJECT_CACHE_SIZE);

				// Fill the object pointers with impossible data
				for (i=0;i<SHADING_OBJECT_CACHE_SIZE;i++)	traceObjectHash[i].object	=	(CSurface *) this;
			}

			// Hash the rays into the table
			for (i=0;i<numRays;i++) {
				T64			object;
				int			key;
				CRay		*cRay	=	rays[i];

				// Compute the hash key (fast and easy)
				object.pointer	=	cRay->object;
				key				=	(	(object.integer >> 0) ^ 
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
						cHash				=	(TObjectHash *) frameMemory->alloc(sizeof(TObjectHash));//GSHHACK //ralloc(sizeof(TObjectHash));
						cHash->object		=	cRay->object;
						cHash->numRays		=	0;
						cHash->rays			=	NULL;
						cHash->next			=	traceObjectHash[key].next;
						traceObjectHash[key].next	=	cHash;
						cHash->shadeNext	=	objects;
						objects				=	cHash;
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
				TShadingGroup	*cGroup	=	(TShadingGroup *) ralloc(sizeof(TShadingGroup));

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
					if (numShading > maxGridSize)	numShading	=	maxGridSize;
					
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
				cRay->object	=	NULL;
				cRay->t			=	C_INFINITY;
				hierarchy->intersect(cRay);
			}

			// Increment the traced ray counter
			stats.numTracedRays	+=	numRays;
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
// Date last edited		:	8/30/2002
void	CShadingContext::traceEx(CRayBundle *bundle) {
	if (currentRayDepth < maxRayDepth) {
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
		bundle->postShade(bundle->numRays,bundle->rays);
	}
}




