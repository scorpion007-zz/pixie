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
// Date last edited		:	7/31/2002
CZbuffer::CZbuffer(COptions *o,CXform *x,SOCKET s) : CReyes(o,x,s,HIDER_RGBAZ_ONLY) , COcclusionCuller() {
	int	i;

	totalWidth		=	bucketWidth*pixelXsamples + 2*xSampleOffset;
	totalHeight		=	bucketHeight*pixelYsamples + 2*ySampleOffset;
	

	// Allocate the framebuffer
	fb					=	new float*[totalHeight];
	for (i=0;i<totalHeight;i++) {
		fb[i]			=	new float[totalWidth*SAMPLES_PER_PIXEL];
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
// Date last edited		:	7/31/2002
CZbuffer::~CZbuffer() {
	int	i;

	for (i=0;i<totalHeight;i++) {
		delete [] fb[i];
	}

	delete [] fb;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CZbuffer
// Method				:	rasterBegin
// Description			:	Init the framebuffer
// Return Value			:	-
// Comments				:
// Date last edited		:	7/31/2002
void	CZbuffer::rasterBegin(int w,int h,int l,int t,int /*nullBucket*/) {
	int	i,j;

	// Set the digits
	width				=	w;
	height				=	h;
	left				=	l;
	top					=	t;
	sampleWidth			=	width*pixelXsamples + 2*xSampleOffset;
	sampleHeight		=	height*pixelYsamples + 2*ySampleOffset;
	right				=	left + sampleWidth;
	bottom				=	top + sampleHeight;

	assert(sampleWidth <= totalWidth);
	assert(sampleHeight <= totalHeight);


	assert(width <= bucketWidth);
	assert(height <= bucketHeight);
	assert(sampleWidth <= totalWidth);
	assert(sampleHeight <= totalHeight);

	// Clear the framebuffer
	initToZero();
	for (i=0;i<sampleHeight;i++) {
		float	*cLine	=	fb[i];

		for (j=0;j<sampleWidth;j++) {
			COcclusionNode	*cNode;

			cLine[0]	=	clipMax;			// z
			cLine[1]	=	0;					// r
			cLine[2]	=	0;					// g
			cLine[3]	=	0;					// b
			cLine		+=	SAMPLES_PER_PIXEL;

			// Set the occlusion cache entry
			cNode		=	getNode(j,i);
			cNode->zmax	=	clipMax;
		}
	}
	resetHierarchy();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CZbuffer
// Method				:	rasterDrawTriangles
// Description			:	Draw rectangles
// Return Value			:	-
// Comments				:
// Date last edited		:	7/31/2002
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
// Comments				:
// Date last edited		:	7/31/2002
void	CZbuffer::rasterEnd(float *fb2,int /*noObjects*/) {
	int			sx,sy;
	int			i,y;
	const int	xres				=	width;
	const int	yres				=	height;
	const int	filterWidth			=	pixelXsamples + 2*xSampleOffset;
	const int	filterHeight		=	pixelYsamples + 2*ySampleOffset;
	const float	invPixelXsamples	=	1 / (float) pixelXsamples;
	const float	invPixelYsamples	=	1 / (float) pixelYsamples;
	float		*tmp;
	float		*pixelFilterWeights;

	memBegin();

	assert(numSamples == 5);

	for (tmp=fb2,i=xres*yres;i>0;i--) {
		*tmp++	=	0;
		*tmp++	=	0;
		*tmp++	=	0;
		*tmp++	=	0;
		*tmp++	=	0;
	}

	// Allocate the memory for the pixel filter
	pixelFilterWeights	=	(float *) alloca(filterHeight*filterHeight*sizeof(float));

	// Evaluate the pixel filter, ignoring the jitter as it is apperently what other renderers do as well
	{
		float		totalWeight			=	0;
		double		invWeight;
		const float	halfFilterWidth		=	filterWidth / 2.0f;
		const float	halfFilterHeight	=	filterHeight / 2.0f;


		for (sy=0;sy<filterHeight;sy++) {
			for (sx=0;sx<filterWidth;sx++) {
				const float	cx								=	(sx - halfFilterWidth + 0.5f)*invPixelXsamples;
				const float	cy								=	(sy - halfFilterHeight + 0.5f)*invPixelYsamples;
				float		filterResponse					=	pixelFilter(cx,cy,pixelFilterWidth,pixelFilterHeight);

				// Account for the partial area out of the bounds
				//if (fabs(cx) > marginX)	filterResponse		*=	marginXcoverage;
				//if (fabs(cy) > marginY)	filterResponse		*=	marginYcoverage;

				// Record
				pixelFilterWeights[sy*filterWidth + sx]		=	filterResponse;
				totalWeight									+=	filterResponse;
			}
		}

		// Normalize the filter kernel
		invWeight	=	1 / (double) totalWeight;
		for (i=0;i<filterWidth*filterHeight;i++) {
			pixelFilterWeights[i]							=	(float) (pixelFilterWeights[i] * invWeight);
		}
	}

	for (y=0;y<yres;y++) {
		for (sy=0;sy<filterHeight;sy++) {
			for (sx=0;sx<filterWidth;sx++) {
				const float	*sampleLine		=	&fb[y*pixelYsamples+sy][sx*SAMPLES_PER_PIXEL];
				float		*pixelLine		=	&fb2[y*xres*5];
				const float	filterResponse	=	pixelFilterWeights[sy*filterWidth + sx];

				for (i=0;i<xres;i++) {
					pixelLine[0]			+=	filterResponse*sampleLine[1];
					pixelLine[1]			+=	filterResponse*sampleLine[2];
					pixelLine[2]			+=	filterResponse*sampleLine[3];
					pixelLine[3]			+=  filterResponse*((sampleLine[0] != clipMax) ? 1.0f : 0.0f);
					pixelLine[4]			+=  filterResponse*sampleLine[0];
					pixelLine				+=	5;
					sampleLine				+=	pixelXsamples*SAMPLES_PER_PIXEL;
				}
			}
		}
	}

	memEnd();
}



