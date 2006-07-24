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
// Date last edited		:	8/30/2002
void	CStats::reset() {
	zoneMemory						=	0;
	peakZoneMemory					=	0;
	vertexMemory					=	0;
	peakVertexMemory				=	0;
	rendererStartTime				=	osCPUTime();
	rendererStartOverhead			=	0;
	rendererTime					=	osCPUTime();
	numAttributes					=	0;
	numXforms						=	0;
	numOptions						=	0;
	numShaders						=	0;
	numShaderInstances				=	0;
	numOutDevices					=	0;
	numGprimCores					=	0;
	numObjects						=	0;
	numGprims						=	0;
	numSurfaces						=	0;
	numPeakSurfaces					=	0;
	numVariableDatas				=	0;
	numVertexDatas					=	0;
	numParameters					=	0;
	numParameterLists				=	0;
	numPls							=	0;
	numComposites					=	0;
	numDelayeds						=	0;
	numInstances					=	0;
	numTextures						=	0;
	numEnvironments					=	0;
	optionsMemory					=	0;
	attributesMemory				=	0;
	xformMemory						=	0;
	gprimCoreMemory					=	0;
	gprimMemory						=	0;
	variableDataMemory				=	0;
	textureMemory					=	0;
	sequenceNumber					=	0;
	runningSequenceNumber			=	0;
	totalNetRecv					=	0;
	totalNetSend					=	0;
	frameStartTime					=	0;
	frameTime						=	0;
	frameStartOverhead				=	0;
	frameEndOverhead				=	0;
	frameRaytracerOverhead			=	0;
	activity						=	"idle";
	progress						=	0;
	sprintf(frameName,"");
	frameNumber						=	0;
	numShaded						=	0;
	numSampled						=	0;
	numRasterGridsCreated			=	0;
	numRasterGridsShaded			=	0;
	numRasterGridsRendered			=	0;
	numPeakRasterGrids				=	0;
	numPeakRasterObjects			=	0;
	avgRasterGrids					=	0;
	avgRasterObjects				=	0;
	numObjectDeferRight				=	0;
	numObjectDeferBottom			=	0;
	numObjectOccluded				=	0;
	numSplits						=	0;
	numVsplits						=	0;
	numUsplits						=	0;
	numUVsplits						=	0;
	numTrianglesCreated				=	0;
	numTrianglesRendered			=	0;
	numTracedRays					=	0;
	numShadingRays					=	0;
	numShadowRays					=	0;
	numRayTriangles					=	0;
	numHierarchyLeaves				=	0;
	numHierarchyInternals			=	0;
	numHierarchyUncomputeds			=	0;
	numLeafItems					=	0;
	numTextureMisses				=	0;
	transferredTextureData			=	0;
	textureSize						=	0;
	numPeakTextures					=	0;
	numPeakEnvironments				=	0;
	peakTextureSize					=	0;
	numIndirectDiffuseSamples		=	0;
	numOcclusionSamples				=	0;
	numIndirectDiffuseRays			=	0;
	numOcclusionRays				=	0;
	numIndirectDiffusePhotonmapLookups	=	0;
	numBrickmapLookups				=	0;
	numBrickmapCacheHits			=	0;
	numBrickmapCachePageouts		=	0;
	numBrickmapCachePageins			=	0;
	brickmapPeakMem					=	0;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CStats
// Method				:	printStats
// Description			:	Prints the statistics
// Return Value			:
// Comments				:
// Date last edited		:	8/30/2002
void	CStats::printStats(int level) {
	info(CODE_STATS,"---> Renderer current:\n");

	info(CODE_STATS,"       Zone memory: %d/%d (Current/Peak bytes)\n",zoneMemory,peakZoneMemory);
	info(CODE_STATS,"              Time: %.2f seconds \n",rendererTime);
	info(CODE_STATS,"           Network: %d KB received, %d KB sent \n",totalNetRecv >> 10,totalNetSend >> 10);

	info(CODE_STATS,"---> End of frame stats:\n");
	info(CODE_STATS,"Frame \"%s\", number %d:\n",frameName,frameNumber);
	info(CODE_STATS,"              Time:  %.2f seconds\n",frameTime);
	info(CODE_STATS,"Start/End Overhead:  %.2f/%.2f seconds (%.2f Raytracer init overhead)\n",frameStartOverhead,frameEndOverhead,frameRaytracerOverhead);

	info(CODE_STATS,"->Memory\n");
	info(CODE_STATS,"             Xform: %d(%d) (bytes(instances))\n",xformMemory,numXforms);
	info(CODE_STATS,"        Attributes: %d(%d) (bytes(instances))\n",attributesMemory,numAttributes);
	info(CODE_STATS,"             Gprim: %d(%d) (bytes(instances))\n",gprimCoreMemory+gprimMemory,numGprims);
	info(CODE_STATS,"           Options: %d(%d) (bytes(instances))\n",optionsMemory,numOptions);
	info(CODE_STATS,"          Textures: %d(%d) (bytes(instances))\n",textureMemory,numTextures);
	info(CODE_STATS,"         Zone Peak: %d (bytes)\n",peakZoneMemory);

	if (level >= 2) {
		info(CODE_STATS,"->Rasterizer\n");
		info(CODE_STATS,"             Grids: %d(%.2f) (peak number(avg))\n",numPeakRasterGrids,avgRasterGrids);

		if (numRasterGridsCreated > 0) {
			info(CODE_STATS,"      Grid Culling: %.2f     (percent) \n",100*(numRasterGridsCreated-numRasterGridsShaded) / (float) numRasterGridsCreated);
			info(CODE_STATS,"          Tri/Grid: %.2f (%d/%d)\n",numTrianglesCreated / (float) numRasterGridsCreated,numTrianglesCreated,numRasterGridsCreated);
			info(CODE_STATS,"          Overdraw: %.2f (times)\n",numTrianglesRendered / (float) numTrianglesCreated);
		}

		info(CODE_STATS,"           Objects: %d(%.2f) (peak number(avg))\n",numPeakRasterObjects,avgRasterObjects);
		info(CODE_STATS,"          Surfaces: %d       (peak number(avg))\n",numPeakSurfaces);

		if (numSplits > 0) {
			info(CODE_STATS,"          U splits: %4.2f %%\n",100*numUsplits / (float) numSplits);
			info(CODE_STATS,"          V splits: %4.2f %%\n",100*numVsplits / (float) numSplits);
			info(CODE_STATS,"         UV splits: %4.2f %%\n",100*numUVsplits / (float) numSplits);
		}

		info(CODE_STATS,"->Raytracer\n");
		info(CODE_STATS,"            Traced: %d (%d shading, %d shadow)\n",numTracedRays,numShadingRays,numShadowRays);
		info(CODE_STATS,"         Hierarchy: %d leaf, %d intermediate, %d uncomputed\n",numHierarchyLeaves,numHierarchyInternals,numHierarchyUncomputeds);
		info(CODE_STATS,"       Tesselation: %d triangles\n",numRayTriangles);
		info(CODE_STATS,"        Leaf items: %d\n",numLeafItems);
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
			info(CODE_STATS,"      Avg. Shading: %.2f (points)\n",numShaded / (float) numSampled);
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
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CStats
// Method				:	check
// Description			:	Make sure everything is deallocated
// Return Value			:
// Comments				:
// Date last edited		:	8/30/2002
void	CStats::check() {
	// Sanity check
	// Make sure we deallocated everything that we allocated
	assert(numAttributes			==	0);
	assert(numXforms				==	0);
	assert(numOptions				==	0);
	assert(numShaders				==	0);
	assert(numShaderInstances		==	0);
	assert(numOutDevices			==	0);
	assert(numGprimCores			==	0);
	assert(numObjects				==	0);
	assert(numGprims				==	0);
	assert(numSurfaces				==	0);
	assert(numVariableDatas			==	0);
	assert(numParameters			==	0);
	assert(numParameterLists		==	0);
	assert(numVertexDatas			==	0);
	assert(numPls					==	0);
	assert(numComposites			==	0);
	assert(numDelayeds				==	0);
	assert(numInstances				==	0);
	assert(numTextures				==	0);
	assert(numEnvironments			==	0);

	assert(numHierarchyInternals	==	0);
	assert(numHierarchyLeaves		==	0);
	assert(numHierarchyUncomputeds	==	0);

	assert(attributesMemory			==	0);
	assert(xformMemory				==	0);
	assert(attributesMemory			==	0);
	assert(gprimCoreMemory			==	0);
	assert(gprimMemory				==	0);
	assert(variableDataMemory		==	0);
	assert(textureMemory			==	0);
	assert(zoneMemory				==	0);
}



