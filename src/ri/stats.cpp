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
//  Description			:	Holds statistics about the renderer
//
////////////////////////////////////////////////////////////////////////
#include <stdio.h>

#include "stats.h"
#include "common/os.h"
#include "error.h"

CStats	stats;

// Signal handler
extern "C" {
	void printStatsHandler(int){
		stats.printStats(3);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CStats
// Method				:	reset
// Description			:	Reset the renderer statistics
// Return Value			:
// Comments				:
void	CStats::reset() {
	zoneMemory							=	0;
	peakZoneMemory						=	0;
	rendererStartTime					=	osTime();
	rendererStartOverhead				=	0;
	numAttributes						=	0;
	numXforms							=	0;
	numOptions							=	0;
	numShaders							=	0;
	numShaderInstances					=	0;
	numVertexDatas						=	0;
	numParameters						=	0;
	numPls								=	0;
	numObjects							=	0;
	numGprims							=	0;
	numSurfaces							=	0;
	numPeakSurfaces						=	0;
	numDelayeds							=	0;
	numTextures							=	0;
	numEnvironments						=	0;
	textureMemory						=	0;
	sequenceNumber						=	0;
	runningSequenceNumber				=	0;
	totalNetRecv						=	0;
	totalNetSend						=	0;
	frameStartTime						=	0;
	frameTime							=	0;
	progress							=	0;
	numShade							=	0;
	numSampled							=	0;
	numShaded							=	0;
	numTracedRays						=	0;
	numReflectionRays					=	0;
	numTransmissionRays					=	0;
	numGatherRays						=	0;
	numPhotonRays						=	0;
	numRasterGrids						=	0;
	numRasterObjects					=	0;
	numRasterGridsCreated				=	0;
	numRasterVerticesCreated			=	0;
	numRasterGridsShaded				=	0;
	numRasterGridsRendered				=	0;
	numRasterQuadsRendered				=	0;
	numSplits							=	0;
	numVsplits							=	0;
	numUsplits							=	0;
	numUVsplits							=	0;
	numTextureMisses					=	0;
	transferredTextureData				=	0;
	textureSize							=	0;
	numPeakTextures						=	0;
	numPeakEnvironments					=	0;
	peakTextureSize						=	0;
	numIndirectDiffuseSamples			=	0;
	numOcclusionSamples					=	0;
	numIndirectDiffuseRays				=	0;
	numOcclusionRays					=	0;
	numIndirectDiffusePhotonmapLookups	=	0;
	numBrickmapLookups					=	0;
	numBrickmapCacheHits				=	0;
	numBrickmapCachePageouts			=	0;
	numBrickmapCachePageins				=	0;
	brickmapPeakMem						=	0;
	tesselationPeakMemory				=	0;
	tesselationMemory					=	0;
	tesselationCacheHits				=	0;
	tesselationCacheMisses				=	0;
	tesselationOverhead					=	0;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CStats
// Method				:	printStats
// Description			:	Prints the statistics
// Return Value			:
// Comments				:
void	CStats::printStats(int level) {
	info(CODE_STATS,"---> Renderer current:\n");

	info(CODE_STATS,"       Zone memory: %d/%d (Current/Peak bytes)\n",zoneMemory,peakZoneMemory);
	info(CODE_STATS,"              Time: %.2f seconds\n",osTime() - rendererStartTime);
	info(CODE_STATS,"           Network: %d KB received, %d KB sent\n",totalNetRecv >> 10,totalNetSend >> 10);

	info(CODE_STATS,"---> End of frame stats:\n");
	info(CODE_STATS,"              Time:  %.2f seconds\n",frameTime);

	info(CODE_STATS,"->Memory\n");
	info(CODE_STATS,"             Xform: %d (instances)\n",numXforms);
	info(CODE_STATS,"        Attributes: %d (instances)\n",numAttributes);
	info(CODE_STATS,"             Gprim: %d (instances)\n",numGprims);
	info(CODE_STATS,"           Options: %d (instances)\n",numOptions);
	info(CODE_STATS,"          Textures: %d(%d) (bytes(instances))\n",textureMemory,numTextures);
	info(CODE_STATS,"         Zone Peak: %d (bytes)\n",peakZoneMemory);

	if (level >= 2) {
		info(CODE_STATS,"->Rasterizer\n");

		if (numRasterGridsCreated > 0) {
			info(CODE_STATS,"      Grid Culling: %.2f (percent)\n",100*(numRasterGridsCreated-numRasterGridsShaded) / (float) numRasterGridsCreated);
			info(CODE_STATS,"       Vertex/Grid: %.2f (%d/%d)\n",numRasterVerticesCreated / (float) numRasterGridsCreated,numRasterVerticesCreated,numRasterGridsCreated);
			info(CODE_STATS,"          Overdraw: %.2f (times)\n",numRasterGridsRendered / (float) numRasterGridsCreated);
		}

		info(CODE_STATS,"          Surfaces: %d       (peak)\n",numPeakSurfaces);

		if (numSplits > 0) {
			info(CODE_STATS,"          U splits: %4.2f %%\n",100*numUsplits / (float) numSplits);
			info(CODE_STATS,"          V splits: %4.2f %%\n",100*numVsplits / (float) numSplits);
			info(CODE_STATS,"         UV splits: %4.2f %%\n",100*numUVsplits / (float) numSplits);
		}

		info(CODE_STATS,"->Raytracer\n");
		info(CODE_STATS,"      Total Traced: %d\n",numTracedRays);
		info(CODE_STATS,"        Reflection: %d\n",numReflectionRays);
		info(CODE_STATS,"      Transmission: %d\n",numTransmissionRays);
		info(CODE_STATS,"            Gather: %d\n",numGatherRays);
		info(CODE_STATS,"  Indirect Diffuse: %d\n",numIndirectDiffuseRays);
		info(CODE_STATS,"         Occlusion: %d\n",numOcclusionRays);
		info(CODE_STATS,"           Photons: %d\n",numPhotonRays);
	}

	if (level >= 3) {
		info(CODE_STATS,"->Textures\n");
		info(CODE_STATS,"              Peak: %d (texture instances) %d (environment instances)\n",numPeakTextures,numPeakEnvironments);
		info(CODE_STATS,"       Peak memory: %d (bytes)\n",peakTextureSize);
		info(CODE_STATS,"      Cache Misses: %d (times)\n",numTextureMisses);

		if (numTextureMisses > 0) {
			info(CODE_STATS,"     Avg. Transfer: %.2f (bytes per miss %d bytes total)\n",transferredTextureData / (float) numTextureMisses,transferredTextureData);
		}

		info(CODE_STATS,"->Shader\n");
		if (numSampled > 0) {
			info(CODE_STATS,"     Avg. Sampling: %.2f (points)\n",numSampled / (float) numShade);
			info(CODE_STATS,"      Avg. Shading: %.2f (points)\n",numShaded / (float) numShade);
		}

		info(CODE_STATS,"->Global Illumination\n");
		info(CODE_STATS,"       Num Samples: %d (indirectdiffuse), %d (occlusion)\n",numIndirectDiffuseSamples,numOcclusionSamples);
		info(CODE_STATS,"          Num Rays: %d (indirectdiffuse), %d (occlusion)\n",numIndirectDiffuseRays,numOcclusionRays);
		info(CODE_STATS," Photonmap Lookups: %d\n",numIndirectDiffusePhotonmapLookups);
		
		info(CODE_STATS,"->3D Textures\n");
		info(CODE_STATS,"       Peak memory: %d (bytes)\n",brickmapPeakMem);
		info(CODE_STATS,"           lookups: %d (times)\n",numBrickmapLookups);
		info(CODE_STATS,"        Cache Hits: %d (times)\n",numBrickmapCacheHits);
		info(CODE_STATS,"   Bricks paged in: %d (bricks)\n",numBrickmapCachePageins);
		info(CODE_STATS,"  Bricks paged out: %d (bricks)\n",numBrickmapCachePageouts);
		
		info(CODE_STATS,"->Tessellation Cache\n");
		info(CODE_STATS,"       Peak memory: %d (bytes)\n",tesselationPeakMemory);
		info(CODE_STATS,"            memory: %d (bytes)\n",tesselationMemory);
		info(CODE_STATS,"        Cache hits: %d (times)\n",tesselationCacheHits);
		info(CODE_STATS,"      Cache misses: %d (times)\n",tesselationCacheMisses);
		info(CODE_STATS,"    Tess. Overhead: %d (bytes)\n",tesselationOverhead);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CStats
// Method				:	check
// Description			:	Make sure everything is deallocated
// Return Value			:
// Comments				:
void	CStats::check() {

	// Sanity check
	// Make sure we deallocated everything that we allocated
	assert(numAttributes			==	0);
	assert(numXforms				==	0);
	assert(numOptions				==	0);
	assert(numShaders				==	0);
	assert(numShaderInstances		==	0);
	assert(numObjects				==	0);
	assert(numGprims				==	0);
	assert(numSurfaces				==	0);
	assert(numParameters			==	0);
	assert(numVertexDatas			==	0);
	assert(numPls					==	0);
	assert(numDelayeds				==	0);
	assert(numTextures				==	0);
	assert(numEnvironments			==	0);

	assert(textureMemory			==	0);
	assert(zoneMemory				==	0);
}

