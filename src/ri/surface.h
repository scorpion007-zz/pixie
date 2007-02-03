//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright � 1999 - 2003, Okan Arikan
//
// Contact: okan@cs.utexas.edu
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
//  File				:	surface.h
//  Classes				:	CSurface
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef SURFACE_H
#define SURFACE_H

#include "common/global.h"
#include "object.h"

#define	TESSELATION_LOCK_PER_ENTRY			// Use a mutex per tesselation entry
#define TESSELATION_NUM_LEVELS			3	// The number of levels before we split

///////////////////////////////////////////////////////////////////////
// Class				:	CPatch
// Description			:	Encapsulates a piece of 2D surface
// Comments				:
class	CPatch : public CObject {
public:
							CPatch(CAttributes *a,CXform *x,CSurface *o,float umin,float umax,float vmin,float vmax,int depth,int minDepth);
							~CPatch();


	void					intersect(CShadingContext *,CRay *)	{	assert(FALSE);	}
	void					dice(CShadingContext *);		// Split or render this object
	void					instantiate(CAttributes *,CXform *,CRendererContext *) const { assert(FALSE);	}

private:
	void					splitToChildren(CShadingContext *,int);

	int						depth;							// Depth of the patch
	int						minDepth;						// The minimum depth of the patch
	CSurface				*object;						// The object the surface belongs to
	float					umin,umax,vmin,vmax;			// The parametric extend of the surface
	int						udiv,vdiv;						// The split amounts
};




///////////////////////////////////////////////////////////////////////
// Class				:	CTesselationPatch
// Description			:	Encapsulates a piece of 2D surface
// Comments				:
class	CTesselationPatch : public CObject {

	struct CPurgableTesselation {
		float					*P;						// The P
		int						size;					// The size (in bytes) of the grid
		int						*lastRefNumber;			// Last time we accessed this grid
	};
	
	struct CTesselationEntry {
		CPurgableTesselation	*tesselation;			// The global tesselation if it exists
		CPurgableTesselation	**threadTesselation;	// The entry per thread
		int						refCount;				// How many threads share this tesselation
		
		#ifdef TESSELATION_LOCK_PER_ENTRY
		TMutex					mutex;					// Mutex if we're mutexing per entry
		#endif
	};
	
	
public:
							CTesselationPatch(CAttributes *a,CXform *x,CSurface *o,float umin,float umax,float vmin,float vmax,char depth,char minDepth,float r);
							~CTesselationPatch();


	void					intersect(CShadingContext *,CRay *);
	void					dice(CShadingContext *) { assert(FALSE); }
	void					instantiate(CAttributes *,CXform *,CRendererContext *) const { assert(FALSE);	}

	void					initTesselation(CShadingContext *context);
	
	static void				initTesselations(int geoCacheMemory);
	static void				shutdownTesselations();

private:
	
	CPurgableTesselation*	tesselate(CShadingContext *context,char div,int estimateOnly);
	void					splitToChildren(CShadingContext *context);	
	
	char					depth;							// Depth of the patch
	char					minDepth;						// The minimum depth of the patch
	CSurface				*object;						// The object the surface belongs to
	float					umin,umax,vmin,vmax;			// The parametric extend of the surface
	
	float					rmax;
	
	CTesselationEntry		levels[TESSELATION_NUM_LEVELS];	// Each tesselation level
	CTesselationPatch		*next,*prev;					// To maintain the linked list


	// record keeping data
	
	static int					*lastRefNumbers[TESSELATION_NUM_LEVELS];		// Reference numbers for each thread per cache level
	static int					*tesselationUsedMemory[TESSELATION_NUM_LEVELS];	// How much each thread has used per cache level
	static int					tesselationMaxMemory[TESSELATION_NUM_LEVELS];	// The maximum memory allowed per thread per cache level
	static CTesselationPatch	*tesselationList;								// Linked list of all tesselations (all levels are listed together)
	
	static void					purgeTesselations(CShadingContext *context,int level, int thread, int all);
	static void					tesselationQuickSort(CTesselationEntry **activeTesselations,int start,int end,int thread);
};

#endif




