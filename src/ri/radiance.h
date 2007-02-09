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
//  File				:	radiance.h
//  Classes				:	CRadianceCache
//  Description			:	This class holds a radiance cache
//
////////////////////////////////////////////////////////////////////////
#ifndef RADIANCECACHE_H
#define RADIANCECACHE_H

#include "common/global.h"
#include "common/algebra.h"
#include "attributes.h"
#include "fileResource.h"
#include "cache.h"
#include "random.h"
#include "depository.h"

// Some misc classes we'll need
class	CTriangleHash;

///////////////////////////////////////////////////////////////////////
// Class				:	CRadianceCache
// Description			:	Radiance cache responsible for estimating stuff
// Comments				:
class	CRadianceCache : public CCache {
public:
	///////////////////////////////////////////////////////////////////////
	// Class				:	CRadianceSample
	// Description			:	Holds a radiance sample
	// Comments				:
	class	CRadianceHarmonic {
	public:
		float				Y[27];					// The spherical harmonic coefficients for this cluster
		vector				P,N;					// The position, normal
		float				dP;						// The radius of the cluster
		float				dN;						// The normal deviation
		CRadianceHarmonic	*next;					// The next pointers
	};

	///////////////////////////////////////////////////////////////////////
	// Class				:	CRadianceNode
	// Description			:	Defines a radiance node
	// Comments				:
	class	CRadianceNode {
	public:
		CRadianceNode		*children[8];			// The children nodes
		CRadianceHarmonic	*samples;				// The list of harmonics
		vector				center;					// The center of the node
		float				side;					// The side length of the node
	};

	///////////////////////////////////////////////////////////////////////
	// Class				:	CShadingPoint
	// Description			:	Holds a shading point
	// Comments				:
	class	CShadingPoint {
	public:
		vector				P,N;					// The position and normal of the shading point
		int					depSample;				// The index of the dep sample
		CShadingPoint		*next;					// Next shading point in the list
	};

public:

							CRadianceCache(const char *,unsigned int,const float *,const float *,FILE *,CArray<CTriangle *> *);
							~CRadianceCache();

							// Overloaded cache functionality
		void				lookup(float *,const float *,const float *,const CGlobalIllumLookup *);
		void				cachesample(float *,const float *,const float *,float);
		void				finalize(const CGlobalIllumLookup *);

							// The functions to visualize the structure (spelling ? ... a little drunk now (Okan) )
		void				draw();
		void				bound(float *bmin,float *bmax);
private:
							// The private functions for stuff
		void				prepareTriangles();
		void				compute(int,CShadingPoint **,CTextureLookup *);
		int					partition(int,CShadingPoint **);
		void				split(const float *,const float *,CAttributes *);
		void				writeNode(FILE *,CRadianceNode *);
		CRadianceNode		*readNode(FILE *);

		CDepository			*hash;					// This is where we keep our computed data

		CMemStack			*memory;				// The global memory area
		CShadingPoint		*shadingPoints;			// List of shading points
		int					numShadingPoints;		// The number of shading points

		CRadianceNode		*root;					// The hierarchy that is used to find nearby samples / harmonics
		int					maxDepth;				// The depth of the octree

		CSobol<4>			generator;				// Random number generator for the ray-casting

		CArray<CTriangle *> *tris;					// The triangles in the scene

		CTriangleHash		*triangleHash;			// The hash for the triangles

		float				alpha;					// The alpha amount
		int					numRaysPerCluster;		// The number of rays to shoot per cluster
		float				bias;					// The raytracing bias
		vector				backgroundColor;		// The color of the background

		TMutex				mutex;
};


#endif

