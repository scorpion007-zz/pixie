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
//  File				:	zbuffer.cpp
//  Classes				:	CZbuffer
//  Description			:	The cheap simple rasterizer
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "zbuffer.h"
#include "memory.h"

///////////////////////////////////////////////////////////////////////
//	Sample	0	->	z
//	Sample	1	->	r
//	Sample	2	->	g
//	Sample	3	->	b

#define	SAMPLES_PER_PIXEL	4


///////////////////////////////////////////////////////////////////////
// Class				:	CZbuffer
// Method				:	CZbuffer
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CZbuffer::CZbuffer(int thread) : CReyes(thread) , COcclusionCuller() {
	int	i;

	totalWidth				=	CRenderer::bucketWidth*CRenderer::pixelXsamples + 2*CRenderer::xSampleOffset;
	totalHeight				=	CRenderer::bucketHeight*CRenderer::pixelYsamples + 2*CRenderer::ySampleOffset;
	

	// Allocate the framebuffer (globalMemory is checkpointed)
	fb		=	(float **) ralloc(totalHeight*sizeof(float *),CRenderer::globalMemory);
	for (i=0;i<totalHeight;i++) {
		fb[i]	=	(float *) ralloc(totalWidth*SAMPLES_PER_PIXEL*sizeof(float),CRenderer::globalMemory);
	}

	// Initialize the occlusion culler
	initCuller(max(totalWidth,totalHeight), &maxDepth);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CZbuffer
// Method				:	~CZbuffer
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CZbuffer::~CZbuffer() {
	
	// Framebuffer is allocated from the frame memory
}

///////////////////////////////////////////////////////////////////////
// Class                :   CZBuffer
// Method               :   preDisplaySetup
// Description          :   allow the hider to affect display setup
// Return Value         :   -
// Comments             :
void CZbuffer::preDisplaySetup() {
	CRenderer::hiderFlags	|=	HIDER_RGBAZ_ONLY;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CZbuffer
// Method				:	rasterBegin
// Description			:	Init the framebuffer
// Return Value			:	-
// Comments				:	Thread safe
void	CZbuffer::rasterBegin(int w,int h,int l,int t,int /*nullBucket*/) {
	int	i,j;

	// Set the digits
	width				=	w;
	height				=	h;
	left				=	l;
	top					=	t;
	sampleWidth			=	width*CRenderer::pixelXsamples + 2*CRenderer::xSampleOffset;
	sampleHeight		=	height*CRenderer::pixelYsamples + 2*CRenderer::ySampleOffset;
	right				=	left + sampleWidth;
	bottom				=	top + sampleHeight;

	assert(sampleWidth <= totalWidth);
	assert(sampleHeight <= totalHeight);

	assert(width <= CRenderer::bucketWidth);
	assert(height <= CRenderer::bucketHeight);
	assert(sampleWidth <= totalWidth);
	assert(sampleHeight <= totalHeight);

	// Clear the framebuffer
	initToZero();
	for (i=0;i<sampleHeight;i++) {
		float	*cLine	=	fb[i];

		for (j=0;j<sampleWidth;j++) {
			COcclusionNode	*cNode;

			cLine[0]	=	CRenderer::clipMax;	// z
			cLine[1]	=	0;							// r
			cLine[2]	=	0;							// g
			cLine[3]	=	0;							// b
			cLine		+=	SAMPLES_PER_PIXEL;

			// Set the occlusion cache entry
			cNode		=	getNode(j,i);
			cNode->zmax	=	CRenderer::clipMax;
		}
	}
	resetHierarchy();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CZbuffer
// Method				:	rasterDrawTriangles
// Description			:	Draw rectangles
// Return Value			:	-
// Comments				:	Thread safe
void	CZbuffer::rasterDrawPrimitives(CRasterGrid *grid) {

	// Draw the suckers one by one
	if (grid->flags & RASTER_POINT) {
		#include "zbufferPoint.h"
	} else {
		#include "zbufferQuad.h"
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CZbuffer
// Method				:	rasterEnd
// Description			:	Retrieve the image
// Return Value			:	-
// Comments				:	Thread safe
void	CZbuffer::rasterEnd(float *fb2,int /*noObjects*/) {
	int			sx,sy;
	int			i,y;
	const int	xres				=	width;
	const int	yres				=	height;
	const int	filterWidth			=	CRenderer::pixelXsamples + 2*CRenderer::xSampleOffset;
	const int	filterHeight		=	CRenderer::pixelYsamples + 2*CRenderer::ySampleOffset;
	const float	invPixelXsamples	=	1 / (float) CRenderer::pixelXsamples;
	const float	invPixelYsamples	=	1 / (float) CRenderer::pixelYsamples;
	float		*tmp;

	assert(CRenderer::numSamples == 5);

	for (tmp=fb2,i=xres*yres;i>0;i--) {
		*tmp++	=	0;
		*tmp++	=	0;
		*tmp++	=	0;
		*tmp++	=	0;
		*tmp++	=	0;
	}


	for (y=0;y<yres;y++) {
		for (sy=0;sy<filterHeight;sy++) {
			for (sx=0;sx<filterWidth;sx++) {
				const float	*sampleLine		=	&fb[y*CRenderer::pixelYsamples+sy][sx*SAMPLES_PER_PIXEL];
				float		*pixelLine		=	&fb2[y*xres*5];
				const float	filterResponse	=	CRenderer::pixelFilterKernel[sy*filterWidth + sx];

				for (i=0;i<xres;i++) {
					pixelLine[0]			+=	filterResponse*sampleLine[1];
					pixelLine[1]			+=	filterResponse*sampleLine[2];
					pixelLine[2]			+=	filterResponse*sampleLine[3];
					pixelLine[3]			+=  filterResponse*((sampleLine[0] != CRenderer::clipMax) ? 1.0f : 0.0f);
					pixelLine[4]			+=  filterResponse*sampleLine[0];
					pixelLine				+=	5;
					sampleLine				+=	CRenderer::pixelXsamples*SAMPLES_PER_PIXEL;
				}
			}
		}
	}
}

