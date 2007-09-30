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
//  File				:	stats.h
//  Classes				:	CStats
//  Description			:	Holds renderer statistics
//
////////////////////////////////////////////////////////////////////////
#ifndef STATS_H
#define STATS_H

#include "common/global.h"		// The global header file

///////////////////////////////////////////////////////////////////////
// Class				:	CStats
// Description			:	Holds statistics
// Comments				:
class CStats {
public:


	void			reset();						// Reset all the stats
	void			printStats(int);				// Print the frame statistics
	void			check();						// Check we have clean shutdown


	///////////////////////////////////////////////////////////////////////////////
	//
	//	Global stats
	//
	///////////////////////////////////////////////////////////////////////////////
	int				zoneMemory;						// The current zone memory size
	int				peakZoneMemory;					// The peak zone memeory size
	float			rendererStartTime;				// The time when the renderer was started
	float			rendererStartOverhead;			// The time it took to initialize the renderer
	int				numAttributes;					// The number of objects allocated of each type
	int				numXforms;
	int				numOptions;
	int				numShaders;
	int				numShaderInstances;
	int				numVertexDatas;
	int				numParameters;
	int				numPls;
	int				numObjects;
	int				numGprims;
	int				numSurfaces;
	int				numPeakSurfaces;
	int				numDelayeds;
	int				numTextures;
	int				numEnvironments;
	int				textureMemory;
	int				sequenceNumber;					// The sequence number
	int				runningSequenceNumber;			// The running sequence number
	int				totalNetRecv;					// The total number of bytes received over the net
	int				totalNetSend;					// The total number of bytes send over the net


	///////////////////////////////////////////////////////////////////////////////
	//
	//	Frame stats
	//
	///////////////////////////////////////////////////////////////////////////////
	float			frameStartTime;					// The time when we started rendering
	float			frameTime;						// The current frame time
	float			progress;						// The progress in the current frame

	int				numShade;						// Number of times shade is called
	int				numSampled;						// The number of vertices that passed thru shade
	int				numShaded;						// The number of vertices that ended up being shaded
	int				numTracedRays;
	int				numReflectionRays;
	int				numTransmissionRays;
	int				numGatherRays;
	int				numPhotonRays;

	int				numRasterGrids;					// The following stats come from the CReyes
	int				numRasterObjects;
	int				numRasterGridsCreated;
	int				numRasterVerticesCreated;
	int				numRasterGridsShaded;
	int				numRasterGridsRendered;
	int				numRasterQuadsRendered;

	int				numSplits;						// The stats that come from CPatch
	int				numVsplits,numUsplits,numUVsplits;

	

	int				numTextureMisses;				// The number of texture misses
	int				transferredTextureData;			// The amount the texture data transmitted
	int				textureSize;					// The current amount of textures in the memory
	int				numPeakTextures;				// The peak number of textures
	int				numPeakEnvironments;			// The peak number of environments
	int				peakTextureSize;				// The amount of memory at the peak denoted to textures
	int				numIndirectDiffuseSamples;		// The number of final gather samples taken
	int				numOcclusionSamples;			// The number of final gather samples taken
	int				numIndirectDiffuseRays;			// The number of final gather samples taken
	int				numOcclusionRays;				// The number of final gather samples taken
	int				numIndirectDiffusePhotonmapLookups;			// The number of final gather photonmap lookups
	int				numBrickmapLookups;				// The number of brickmap lookups
	int				numBrickmapCacheHits;			// The number of brickmap cache hits
	int				numBrickmapCachePageouts;		// The number of bricks paged out
	int				numBrickmapCachePageins;		// The number of bricks paged in
	int				brickmapPeakMem;				// The peak memory usage for brickmaps
	int				tesselationMemory;				// The total memory usage for tesselations
	int				tesselationPeakMemory;			// The peak total memory usage for tesselations
	int				tesselationCacheMisses;			// The number of tesselation cache misses
	int				tesselationCacheHits;			// The number of tesselation cache hits
	int				tesselationOverhead;			// The memory overhead of tesselation patches
};


extern	CStats	stats;


#endif

