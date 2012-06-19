//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright © 1999 - 2010, Okan Arikan
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
//  File				:	stochastic.h
//  Classes				:	CStochastic
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef STOCHASTIC_H
#define STOCHASTIC_H

#include "common/global.h"
#include "reyes.h"
#include "occlusion.h"
#include "random.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CStochastic
// Description			:	This is the stochastic hider (a scanline renderer)
// Comments				:
class	CStochastic : public CReyes, public COcclusionCuller {
public:
				CStochastic(int thread);
				~CStochastic();

	static void	preDisplaySetup() { }

				// The functions inherited from the CReyes
	void		rasterBegin(int,int,int,int,int);
	void		rasterDrawPrimitives(CRasterGrid *);
	void		rasterEnd(float *,int);

protected:
	int			probeArea(int *xbound,int *ybound, int bw, int bh, int bl, int bt, float zmin) {
					return probeRect(xbound,ybound,bw,bh,bl,bt,zmin);
				}
	
private:

	///////////////////////////////////////////////////////////////////////
	// Class				:	CFragment
	// Description			:
/// \brief					This class holds a sample
	// Comments				:
	class	CFragment {
	public:
		vector			color;					// Color of the sample
		vector			opacity;				// Opacity of the sample
		vector			accumulatedOpacity;		// The accumulated opacity at this sample
		float			z;						// Depth of the sample
		CFragment		*next;					// The next fragment wrt. depth
		CFragment		*prev;					// The previous fragment wrt. depth
		float			*extraSamples;			// Extra sample space
	};

	///////////////////////////////////////////////////////////////////////
	// Class				:	CPixel
	// Description			:
/// \brief					This class holds a pixel
	// Comments				:
	class	CPixel {
	public:
		float			jx,jy;					// The sampling jitter
		float			jt;						// The time jitter
		float			jdx,jdy;				// The aperture jitter	(Gaussian)
		float			jimp;					// The relative importance // GSHHACK
		float			z;						// The farthest opaque z value
		float			zold;					// This is the old Z value (for depth filtering)
		int				numSplats;				// The number of splats to this pixel (used by the avg. depth filter);
		float			xcent,ycent;			// The center of the sampling window
		CFragment		first,last;				// The first and last fragments always exist
		CFragment		*update;				// The last fragment to be saved
		COcclusionNode	*node;					// The occlusion sample
	};

	void		filterSamples(int,CFragment **,float *);
	void		deepShadowCompute();
	
	void
	newFragment(
		__out CFragment** ppSample);
	
	void
	deleteFragment(
		__in CFragment* sample);
	
	void
	drawExtraSamples(
		__out CFragment* nSample,
		__in float jt,
		__in CRasterGrid* grid,
		__in float u,
		__in float v,
		__in const float* v0,
		__in const float* v1,
		__in const float* v2,
		__in const float* v3,
		__in int displacement);
	
	void
	findSample(
		__out CFragment** dest,
		__in CPixel* pixel,
		__in float z);
	
	bool
	lodCheck(
		__in CRasterGrid *grid,
		__in CPixel* pixel);
	
	void
	updateOpaque(
		__in CPixel* pixel,
		__in float z);
	
	bool
	checkPixel(
		__in bool useLessThan,
		__in CPixel* pixel,
		__in const float* v0,
		__in const float* v1,
		__in const float* v2,
		__in const float* v3,
		__out float* pZ,
		__out float* pU,
		__out float* pV);
	
	void
	depthFilterIfZMin(
		__in CPixel* pixel);
	
	void
	depthFilterElseZMin(
		__in CPixel* pixel,
		__in float z);
	
	void
	depthFilterTouchNodeZMin(
		__in CPixel* pixel,
		__in float z);
	
	void
	depthFilterIfZMid(
		__in CPixel* pixel);
	
	void
	depthFilterElseZMid(
		__in CPixel* pixel,
		__in float z);
	
	void
	depthFilterTouchNodeZMid(
		__in CPixel* pixel,
		__in float z);

	void
	updateTransparent(
		__in CPixel* pixel,
		__in CFragment* nSample,
		__in bool useZMid);
	
	void
	colorOpacityUpdate(
		__out CFragment* nSample,
		__in CPixel* pixel,
		__in CRasterGrid* grid,
		__in float u,
		__in float v,
		__in const float* v0c,
		__in const float* v1c,
		__in const float* v2c,
		__in const float* v3c,
		__in int displacement);
	
	void
	drawPixel(
		__in CRasterGrid* grid,
		__in CPixel* pixel,
		__in float z,
		__in float u,
		__in float v,
		__in const float* v0,
		__in const float* v1,
		__in const float* v2,
		__in const float* v3,
		__in bool useZMid,
		__in int displacement);
	
	bool
	drawPixelCheck(
		__in CRasterGrid* grid,
		__in CPixel* pixel,
		__in float z,
		__in float u,
		__in float v,
		__in const float* v0,
		__in const float* v1,
		__in const float* v2,
		__in const float* v3,
		__in int displacement);

	int			totalWidth,totalHeight;
	CPixel		**fb;

	CFragment	*freeFragments;
	int			numFragments;
	float		*extraSampleMemory;
	
	int			width,height;
	int			top,left,right,bottom;
	int			sampleWidth,sampleHeight;
	
	CSobol<2>	apertureGenerator;
	
	// Define prototypes for the rasterization functions
	
	#define DEFINE_STOCHASTIC_FUNPROTOS
	#include "stochasticPrimitives.h"
	#undef DEFINE_STOCHASTIC_FUNPROTOS
};

#endif

