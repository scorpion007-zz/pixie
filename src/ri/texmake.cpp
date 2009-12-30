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
//  File				:	texmake.cpp
//  Classes				:	-
//  Description			:	This file comtains texture file making routines
//
////////////////////////////////////////////////////////////////////////
#include "texmake.h"
#include "ri_config.h"
#include "ri.h"
#include "memory.h"
#include "error.h"
#include "renderer.h"
#include "tiff.h"

#include <stddef.h>		// ensure we have NULL defined before libtiff
#include <tiffio.h>
#include <math.h>

const char	*TIFF_TEXTURE					=	"Pixie Texture";
const char	*TIFF_CYLINDER_ENVIRONMENT		=	"Pixie Environment (cylinder)";
const char	*TIFF_CUBIC_ENVIRONMENT			=	"Pixie Environment (cubic)";
const char	*TIFF_SPHERICAL_ENVIRONMENT		=	"Pixie Environment (spherical)";
const char	*TIFF_SHADOW					=	"Pixie shadow";

const char	*resizeUpMode					=	"up";
const char	*resizeDownMode					=	"down";
const char	*resizeRoundMode				=	"round";
const char	*resizeNoneMode					=	"none";


///////////////////////////////////////////////////////////////////////
// function				:	tiffErrorHandler
// Description			:	Handle errors coming from the libtiff
// Return Value			:	-
// Comments				:
static	void	tiffErrorHandler(const char *module,const char *fmt,va_list ap) {
	char tmp[1024];

	vsprintf(tmp,fmt,ap);

	error(CODE_SYSTEM,"TIFF: %s\n",tmp);
}


///////////////////////////////////////////////////////////////////////
// Function				:	appendLayer
// Description			:	Append a layer of image into an image file
// Return Value			:	-
// Comments				:
static	void	appendLayer(TIFF *out,int dstart,int numSamples,int bitsperpixel,int tileSize,int width,int height,void *data) {
	int				x,y;
	unsigned char	*tileData;
	int				pixelSize;

	TIFFSetField(out, TIFFTAG_IMAGEWIDTH,			(unsigned long) width);
	TIFFSetField(out, TIFFTAG_IMAGELENGTH,			(unsigned long) height);
	TIFFSetField(out, TIFFTAG_ORIENTATION,			ORIENTATION_TOPLEFT);
	TIFFSetField(out, TIFFTAG_PLANARCONFIG,			PLANARCONFIG_CONTIG);
	TIFFSetField(out, TIFFTAG_RESOLUTIONUNIT,		RESUNIT_NONE);
	TIFFSetField(out, TIFFTAG_XRESOLUTION,			1.0f);
	TIFFSetField(out, TIFFTAG_YRESOLUTION,			1.0f);
	TIFFSetField(out, TIFFTAG_COMPRESSION,			COMPRESSION_LZW);
	//TIFFSetField(out, TIFFTAG_COMPRESSION,			COMPRESSION_ADOBE_DEFLATE);
	//TIFFSetField(out, TIFFTAG_COMPRESSION,			COMPRESSION_JPEG);
	//TIFFSetField(out, TIFFTAG_COMPRESSION,			COMPRESSION_PACKBITS);
	//TIFFSetField(out, TIFFTAG_COMPRESSION,			COMPRESSION_THUNDERSCAN);
	//TIFFSetField(out, TIFFTAG_COMPRESSION,			COMPRESSION_PIXARFILM);
	//TIFFSetField(out, TIFFTAG_COMPRESSION,			COMPRESSION_PIXARLOG);
	//TIFFSetField(out, TIFFTAG_COMPRESSION,			COMPRESSION_DEFLATE);

	
	TIFFSetField(out, TIFFTAG_SAMPLESPERPIXEL,		(unsigned long) numSamples);
	TIFFSetField(out, TIFFTAG_TILEWIDTH,			(unsigned long) tileSize);
	TIFFSetField(out, TIFFTAG_TILELENGTH,			(unsigned long) tileSize);

	if (bitsperpixel == 8) {
		TIFFSetField(out, TIFFTAG_SAMPLEFORMAT,		SAMPLEFORMAT_UINT);
		TIFFSetField(out, TIFFTAG_BITSPERSAMPLE,	(unsigned long) (sizeof(unsigned char)*8));
		pixelSize	=	numSamples*sizeof(unsigned char);
	} else if (bitsperpixel == 16) {
		TIFFSetField(out, TIFFTAG_SAMPLEFORMAT,		SAMPLEFORMAT_UINT);
		TIFFSetField(out, TIFFTAG_BITSPERSAMPLE,	(unsigned long) (sizeof(unsigned short)*8));
		TIFFSetField(out, TIFFTAG_PHOTOMETRIC,		PHOTOMETRIC_MINISBLACK);
		pixelSize	=	numSamples*sizeof(unsigned short);
	} else {
		TIFFSetField(out, TIFFTAG_SAMPLEFORMAT,		SAMPLEFORMAT_IEEEFP);
		TIFFSetField(out, TIFFTAG_BITSPERSAMPLE,	(unsigned long) (sizeof(float)*8));
		pixelSize	=	numSamples*sizeof(float);
	}

	memBegin(CRenderer::globalMemory);

	tileData		=	(unsigned char *) ralloc(pixelSize*tileSize*tileSize,CRenderer::globalMemory);

	assert(TIFFTileSize(out) == (tileSize*tileSize*pixelSize));

	for (y=0;y<height;y+=tileSize) {
		for (x=0;x<width;x+=tileSize) {
			int	ty;

			for (ty=0;ty<tileSize;ty++) {
				memcpy(&tileData[ty*tileSize*pixelSize],&((unsigned char *) data)[((y+ty)*width+x)*pixelSize],tileSize*pixelSize);
			}

			TIFFWriteTile(out,tileData,x,y,0,0);
		}
	}

	TIFFWriteDirectory(out);

	memEnd(CRenderer::globalMemory);
}

///////////////////////////////////////////////////////////////////////
// Function				:	appendPyramid
// Description			:	Append an image pyramid into an image file
//							the reduction gives the amount of reduction in the image size at each step
// Return Value			:
// Comments				:
template <class T> static	void	appendPyramid(TIFF *out,int &dstart,int numSamples,int bitsperpixel,int tileSize,int width,int height,T *data) {
	T		*currentLevel;
	int		currentWidth,currentHeight,nextWidth,nextHeight;
	float	*fnextLevel;

	// Append the base layer
	appendLayer(out,dstart++,numSamples,bitsperpixel,tileSize,width,height,data);

	// Append the remaining layers
	currentWidth	=	width;
	currentHeight	=	height;
	currentLevel	=	data;

	fnextLevel		=	(float *)	ralloc(width*height*numSamples*sizeof(float),CRenderer::globalMemory);

	int numLevels	=	tiffNumLevels(width,height);
	int	i;

	for (i=1;i<numLevels;i++) {
		int			x,y,yo;
		int			s;

		nextWidth	=	currentWidth >> 1;
		nextHeight	=	currentHeight >> 1;

		for (y=0,yo=0;y<nextHeight;y++,yo+=2) {
			T		*src	=	&currentLevel[yo*currentWidth*numSamples];
			float	*dest	=	&fnextLevel[y*nextWidth*numSamples];
			int		n;

			for (x=0;x<nextWidth;x++) {
				for (n=0;n<numSamples;n++) {
					dest[n]		=	src[n];
					dest[n]		+=	src[numSamples+n];
				}
				dest	+=	numSamples;
				src		+=	2*numSamples;
			}

			src		=	&currentLevel[(yo+1)*currentWidth*numSamples];
			dest	=	&fnextLevel[y*nextWidth*numSamples];

			for (x=0;x<nextWidth;x++) {
				for (n=0;n<numSamples;n++) {
					dest[n]		+=	src[n];
					dest[n]		+=	src[numSamples+n];
				}
				dest	+=	numSamples;
				src		+=	2*numSamples;
			}

			dest	=	&fnextLevel[y*nextWidth*numSamples];

			for (x=0;x<nextWidth*numSamples;x++) {
				*dest++	*=	1/(float) 4;
			}
		}
			
		for (s=0;s<nextWidth*nextHeight*numSamples;s++) {
			currentLevel[s]	=	(T) fnextLevel[s];
		}

		currentWidth	=	nextWidth;
		currentHeight	=	nextHeight;

		appendLayer(out,dstart++,numSamples,bitsperpixel,tileSize,currentWidth,currentHeight,currentLevel);
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	readLayer
// Description			:	Read a layer of the image into memory
// Return Value			:
// Comments				:
void	*readLayer(TIFF *in,int *width,int *height,int *bitsperpixel,int *numSamples) {
	unsigned char	*data;
	int				i;
	uint32			w,h;
	uint16			ns,bp;
	int				pixelSize;

	TIFFGetFieldDefaulted(in,TIFFTAG_IMAGEWIDTH              ,&w);
	TIFFGetFieldDefaulted(in,TIFFTAG_IMAGELENGTH             ,&h);
	TIFFGetFieldDefaulted(in,TIFFTAG_SAMPLESPERPIXEL         ,&ns);
	TIFFGetFieldDefaulted(in,TIFFTAG_BITSPERSAMPLE			 ,&bp);

	width[0]		=	w;
	height[0]		=	h;
	numSamples[0]	=	ns;
	bitsperpixel[0]	=	bp;

	if (bp == 8) {
		pixelSize	=	ns*sizeof(unsigned char);
	} else if (bp == 16) {
		pixelSize	=	ns*sizeof(unsigned short);
	} else if (bp == 32) {
		pixelSize	=	ns*sizeof(float);
	} else {
		error(CODE_BUG,"Unknown bits per pixel in readLayer (%d)\n",bp);
		pixelSize	=	0;
	}

	data =	(unsigned char *) ralloc(pixelSize*w*h,CRenderer::globalMemory);

	for (i=0;i<(int) h;i++) {
		TIFFReadScanline(in,&data[i*pixelSize*w],i,0);
	}

	return data;
}

///////////////////////////////////////////////////////////////////////
// Function				:	copyData
// Description			:	Copy a rectangular portion between images
// Return Value			:
// Comments				:
template <class T> void copyData(T *from,int fw,int fh,int x,int y,int w,int h,
								 T *to,int tw,int th,int tx,int ty,int numSamples) {
	int	i,j;

	for (j=0;j<h;j++)
		for (i=0;i<w;i++) {
			int s;

			for (s=0;s<numSamples;s++) {
				to[((ty+j)*tw+(tx+i))*numSamples+s]	=	from[((y+j)*fw + (x+i))*numSamples+s];
			}
		}

}

///////////////////////////////////////////////////////////////////////
// Function				:	initData
// Description			:	Paint
// Return Value			:
// Comments				:
template <class T> void	initData(T *to,int width,int height,int x,int y,int w,int h,int numSamples,T n) {
	int	i,j,s;

	for (j=0;j<h;j++)
		for (i=0;i<w;i++)
			for (s=0;s<numSamples;s++)
				to[((y+j)*width+(x+i))*numSamples+s]	=	n;
}

///////////////////////////////////////////////////////////////////////
// Function				:	initDataValues
// Description			:	Paint
// Return Value			:
// Comments				:
template <class T> void	initDataValues(T *to,int width,int height,int x,int y,int w,int h,int numSamples,T* v) {
	int	i,j,s;

	for (j=0;j<h;j++)
		for (i=0;i<w;i++)
			for (s=0;s<numSamples;s++)
				to[((y+j)*width+(x+i))*numSamples+s]	=	v[s];
}

///////////////////////////////////////////////////////////////////////
// Function				:	filterImage
// Description			:	Apply a filter to the image
// Return Value			:
// Comments				:
template <class T> void	filterImage(int width,int height,int numSamples,int bitspersample,float filterWidth,float filterHeight,RtFilterFunc filter,T *data) {

	memBegin(CRenderer::globalMemory);

	float	*filteredData	=	(float *) ralloc(width*height*numSamples*sizeof(float),CRenderer::globalMemory);
	float	*normalizer		=	(float *) ralloc(width*height*sizeof(float),CRenderer::globalMemory);
	int		x,y,i;
	int		fw				=	(int) ceil((filterWidth-1)/2);
	int		fh				=	(int) ceil((filterHeight-1)/2);
	float	filterXmarginal	=	filterWidth/2;
	float	filterYmarginal	=	filterHeight/2;
	float	filterXmargin	=	(float) floor(filterXmarginal);
	float	filterYmargin	=	(float) floor(filterYmarginal);
	float	dx				=	filterXmarginal - filterXmargin;
	float	dy				=	filterYmarginal - filterYmargin;

	// Clear the filtered image
	for (i=0;i<width*height;i++) {
		normalizer[i]	=	0;
		filteredData[i]	=	0;
	}

	for (;i<width*height*numSamples;i++) {
		filteredData[i]	=	0;
	}

	// Filter the image
	for (y=0;y<height;y++) {
		for (x=0;x<width;x++) {
			int		i,j;
			float	*pixel	=	&filteredData[(y*width+x)*numSamples];
			float	*norm	=	&normalizer[y*width+x];

			for (j=y-fh;j<=y+fh;j++) {
				for (i=x-fw;i<=x+fw;i++) {
					if ((i >= 0) && (i < width) && (j >= 0) && (j < height)) {
						float	cx				=	(float) (i-x);
						float	cy				=	(float) (j-y);
						float	filterResponse	=	filter(cx,cy,filterWidth,filterHeight);
						int		k;
						T		*cPixel			=	&data[(j*width+i)*numSamples];

						if (fabs(cx) > filterXmargin)	filterResponse	*=	dx;
						if (fabs(cy) > filterYmargin)	filterResponse	*=	dy;

						norm[0]	+=	filterResponse;

						for (k=0;k<numSamples;k++) {
							pixel[k]	+=	filterResponse*cPixel[k];
						}
					}
				}
			}
		}
	}

	float minVal = -C_INFINITY;
	float maxVal = C_INFINITY;
	
	if (bitspersample == 8) {
		minVal = 0;
		maxVal = 255;
	} else if (bitspersample == 16) {
		minVal = 0;
		maxVal = 65535;
	}
	
	// Normalize the image
	float	*pixel	=	filteredData;
	T		*dest	=	data;
	float	*norm	=	normalizer;

	for (i=0;i<width*height;i++) {
		int	k;

		for (k=0;k<numSamples;k++) {
			float t = (pixel[k] / norm[0]);		// avoid precision / quanitze issues
			t = min(max(minVal,t),maxVal);
			dest[k]	=	(T) (t);
			
			//dest[k]	=	(T) (pixel[k] / norm[0]);
		}

		dest	+=	numSamples;
		pixel	+=	numSamples;
		norm++;
	}

	memEnd(CRenderer::globalMemory);
}

///////////////////////////////////////////////////////////////////////
// Function				:	filterScaleImage
// Description			:	Apply a filter to the image and scale it
// Return Value			:
// Comments				:
template <class T> void	filterScaleImage(int width,int height,int targetWidth,int targetHeight,int newWidth,int newHeight,
	int numSamples,int bitspersample,float filterWidth,float filterHeight,RtFilterFunc filter,T *dataIn,T *dataOut) {

	memBegin(CRenderer::globalMemory);

	float	*filteredData	=	(float *) ralloc(newWidth*newHeight*numSamples*sizeof(float),CRenderer::globalMemory);
	float	*normalizer		=	(float *) ralloc(newWidth*newHeight*sizeof(float),CRenderer::globalMemory);
	float	widthRatio		=	(float)width/(float)targetWidth;
	float	heightRatio		=	(float)height/(float)targetHeight;
	int		x,y,i;
	int		fw				=	(int) ceil((filterWidth-1)/2);
	int		fh				=	(int) ceil((filterHeight-1)/2);
	float	filterXmarginal	=	filterWidth/2;
	float	filterYmarginal	=	filterHeight/2;
	float	filterXmargin	=	(float) floor(filterXmarginal);
	float	filterYmargin	=	(float) floor(filterYmarginal);
	float	dx				=	filterXmarginal - filterXmargin;
	float	dy				=	filterYmarginal - filterYmargin;

	// Clear the filtered image
	for (i=0;i<newHeight*newHeight;i++) {
		normalizer[i]	=	0;
		filteredData[i]	=	0;
	}

	for (;i<newHeight*newHeight*numSamples;i++) {
		filteredData[i]	=	0;
	}

	// Filter the image
	for (y=0;y<newHeight;y++) {
		for (x=0;x<newWidth;x++) {
			int		i,j;
			float	*pixel	=	&filteredData[(y*newWidth+x)*numSamples];
			float	*norm	=	&normalizer[y*newWidth+x];
			
			float	xo		=	x*widthRatio;
			float	yo		=	y*heightRatio;
			int		xoi		=	(int) floor(xo);
			int		yoi		=	(int) floor(yo);
//			float	xof		=	xo-xoi;
//			float	yof		=	yo-yoi;

// FIXME: should periodic textures filter from the other side?

			for (j=(int) (yo-fh);j<=yo+fh;j++) {
				for (i=(int) (xo-fw);i<=xo+fw;i++) {
					if ((i >= 0) && (i < width) && (j >= 0) && (j < height)) {
						float	cx				=	(float) (i-xo);
						float	cy				=	(float) (j-yo);
						float	filterResponse	=	filter(cx,cy,filterWidth,filterHeight);
						int		k;
						T		*cPixel			=	&dataIn[(j*width+i)*numSamples];

						if (fabs(cx) > filterXmargin)	filterResponse	*=	dx;
						if (fabs(cy) > filterYmargin)	filterResponse	*=	dy;

						norm[0]	+=	filterResponse;

						for (k=0;k<numSamples;k++) {
							pixel[k]	+=	filterResponse*cPixel[k];
						}
					}
				}
			}
		}
	}

	float minVal = -C_INFINITY;
	float maxVal = C_INFINITY;
	
	if (bitspersample == 8) {
		minVal = 0;
		maxVal = 255;
	} else if (bitspersample == 16) {
		minVal = 0;
		maxVal = 65535;
	}
	
	// Normalize the image
	float	*pixel	=	filteredData;
	T		*dest	=	dataOut;
	float	*norm	=	normalizer;

	for (i=0;i<newWidth*newHeight;i++) {
		int	k;

		float nrm = norm[0];
		if (nrm > 0) {
			for (k=0;k<numSamples;k++) {
				float t = (pixel[k] / nrm);		// avoid precision / quanitze issues
				t = min(max(minVal,t),maxVal);
				dest[k]	=	(T) (t);
			}
		} else {
			// In the rescale case we may well have no value for portions of the image - zero fill them
			for (k=0;k<numSamples;k++) {
				dest[k]	=	(T) (minVal);
			}
		}

		dest	+=	numSamples;
		pixel	+=	numSamples;
		norm++;
	}

	memEnd(CRenderer::globalMemory);
}


///////////////////////////////////////////////////////////////////////
// Function				:	adjustSize
// Description			:	Adjust the size of an image so that it's size is a power of two
// Return Value			:
// Comments				:	resize modes to match prman
template <class T> void	adjustSize(T **data,int *width,int *height,int *validWidth,int *validHeight,int numSamples,int bitspersample,float filterWidth,float filterHeight,RtFilterFunc filter,const char *smode,const char *tmode,const char *resizemode) {
	int	newWidth,newHeight,targetWidth,targetHeight;
	int preserveRatio = TRUE;

	// default to rounding up
	for (newWidth=1;newWidth < width[0];newWidth = newWidth << 1);
	for (newHeight=1;newHeight < height[0];newHeight = newHeight << 1);
	
	// check if we're supposed to preserve ratios
	int resizeModeLen = (int) strlen(resizemode);
	if (resizeModeLen > 2) {
		if (resizemode[resizeModeLen-1] == '-') {
			preserveRatio = FALSE;
			resizeModeLen--;
		}
	}
	
	// make adjustments according to resize mode
	if (strncmp(resizemode,resizeDownMode,resizeModeLen) == 0) {
		if (newWidth != width[0]) 		newWidth	=	newWidth >> 1;
		if (newHeight != height[0]) 	newHeight	=	newHeight >> 1;
	} else if (strncmp(resizemode,resizeRoundMode,resizeModeLen) == 0) {
		if (newWidth != width[0]) {
			int lowerWidth	=	newWidth >> 1;
			if (abs(width[0]-newWidth) > abs(lowerWidth-width[0])) {
				newWidth = lowerWidth;
			}
		}
		if (newHeight != height[0]) {
			int	lowerHeight	=	newHeight >> 1;
			if (abs(height[0]-newHeight) > abs(lowerHeight-height[0])) {
				newHeight = lowerHeight;
			}
		}
	}
	
	// adjust the target width / height
	targetWidth		= newWidth;
	targetHeight 	= newHeight;
	if (preserveRatio) {
		if (width[0] > height[0]) {
			// find new targetHeight
			float nh		=	(float) newWidth*height[0] / (float) width[0];
			targetHeight	=	(int) ceil(nh);
			// We may have produced an overly small side
			// In order to preserve ratios, it might have to be larger
			while (targetHeight > newHeight) newHeight = newHeight << 1;
		} else {
			// find new targetWidth
			float nw		=	(float) newHeight*width[0] / (float) height[0];
			targetWidth		=	(int) ceil(nw);
			// We may have produced an overly small side
			// In order to preserve ratios, it might have to be larger
			while (targetWidth > newWidth) newWidth = newWidth << 1;
		}
	}

	// resize if apporpriate
	if (strcmp(resizemode,resizeNoneMode) != 0) {
		if (!((width[0] == newWidth) && (height[0] == newHeight))) {
			T *newData;
		
			newData	=	(T *) ralloc(newWidth*newHeight*numSamples*sizeof(T),CRenderer::globalMemory);
			memset(newData,0,newWidth*newHeight*numSamples*sizeof(T));
	
			filterScaleImage<T>(width[0],height[0],targetWidth,targetHeight,newWidth,newHeight,numSamples,bitspersample,filterWidth,filterHeight,filter,data[0],newData);
			
			data[0]			=	newData;
			width[0]		=	newWidth;
			height[0]		=	newHeight;
		}
	} else {
		// filter the image before rescaling
		if ((filterWidth > 1.0) || (filterHeight > 1.0))
			filterImage<T>(width[0],height[0],numSamples,bitspersample,filterWidth,filterHeight,filter,data[0]);

		// rescale otherwise
		if (!((width[0] == newWidth) && (height[0] == newHeight))) {
			T *newData;
	
			newData	=	(T *) ralloc(newWidth*newHeight*numSamples*sizeof(T),CRenderer::globalMemory);
			memset(newData,0,newWidth*newHeight*numSamples*sizeof(T));
	
			copyData<T>(data[0],width[0],height[0],0,0,width[0],height[0],newData,newWidth,newHeight,0,0,numSamples);
			
			if (strcmp(smode,RI_PERIODIC) == 0) {
				copyData<T>(data[0],width[0],height[0],0,0,newWidth-width[0],height[0],newData,newWidth,newHeight,width[0],0,numSamples);
			} else if (strcmp(smode,RI_CLAMP) == 0) {
				int	i;
	
				for (i=0;i<newWidth-width[0];i++)
					copyData<T>(data[0],width[0],height[0],width[0]-1,0,1,height[0],newData,newWidth,newHeight,width[0]+i,0,numSamples);
			} else if (strcmp(smode,RI_BLACK) == 0) {
				initData<T>(newData,newWidth,newHeight,width[0],0,newWidth-width[0],height[0],numSamples,0);
			}
	
	
			if (strcmp(tmode,RI_PERIODIC) == 0) {
				copyData<T>(data[0],width[0],height[0],0,0,width[0],newHeight-height[0],newData,newWidth,newHeight,0,height[0],numSamples);
			} else if (strcmp(tmode,RI_CLAMP) == 0) {
				int	i;
	
				for (i=0;i<newHeight-height[0];i++)
					copyData<T>(data[0],width[0],height[0],0,height[0]-1,width[0],1,newData,newWidth,newHeight,0,height[0]+i,numSamples);
			} else if (strcmp(tmode,RI_BLACK) == 0) {
				initData<T>(newData,newWidth,newHeight,0,height[0],width[0],newHeight-height[0],numSamples,0);
			}
			
			// when resizing both dimentions, there's an extra corner to worry about
			if ((newWidth != width[0]) && (newHeight != height[0])) {
				if ((strcmp(smode,RI_PERIODIC) == 0) && (strcmp(tmode,RI_PERIODIC) == 0)) {
					copyData<T>(data[0],width[0],height[0],0,0,newWidth-width[0],newHeight-height[0],newData,newWidth,newHeight,width[0],height[0],numSamples);
				} else if ((strcmp(smode,RI_BLACK) == 0) || (strcmp(tmode,RI_BLACK) == 0)) {
					initData<T>(newData,newWidth,newHeight,width[0],height[0],newWidth-width[0],newHeight-height[0],numSamples,0);
				} else if (strcmp(smode,RI_CLAMP) == 0) {
					// FIXME: This case is a little ambiguous
					T *initValues = data[0] + width[0]*numSamples*(height[0]-1) + (width[0]-1)*numSamples;
					initDataValues<T>(newData,newWidth,newHeight,width[0],height[0],newWidth-width[0],newHeight-height[0],numSamples,initValues);
				}
			}
	
			data[0]		=	newData;
			width[0]	=	newWidth;
			height[0]	=	newHeight;
		}
	}
	
	validWidth[0]	=	targetWidth;
	validHeight[0]	=	targetHeight;
}

///////////////////////////////////////////////////////////////////////
// Function				:	appendTexture
// Description			:	Make and append a texture to the end of the TIFF file
// Return Value			:
// Comments				:	FIXME: filter only when adjusting size
void	appendTexture(TIFF *out,int &dstart,int width,int height,int numSamples,int bitspersample,RtFilterFunc filter,float filterWidth,float filterHeight,int tileSize,void *data,const char *smode,const char *tmode,const char *resizemode) {
	int validHeight,validWidth;
	
	if (bitspersample == 8) {
		adjustSize<unsigned char>((unsigned char **) &data,&width,&height,&validWidth,&validHeight,numSamples,bitspersample,filterWidth,filterHeight,filter,smode,tmode,resizemode);
		
		// write adjusted sizes
		TIFFSetField(out, TIFFTAG_PIXAR_IMAGEFULLWIDTH,		validWidth);
		TIFFSetField(out, TIFFTAG_PIXAR_IMAGEFULLLENGTH,	validHeight);

		appendPyramid<unsigned char>(out,dstart,numSamples,bitspersample,tileSize,width,height,(unsigned char *) data);
	} else if (bitspersample == 16) {
		adjustSize<unsigned short>((unsigned short **) &data,&width,&height,&validWidth,&validHeight,numSamples,bitspersample,filterWidth,filterHeight,filter,smode,tmode,resizemode);

		// write adjusted sizes
		TIFFSetField(out, TIFFTAG_PIXAR_IMAGEFULLWIDTH,		validWidth);
		TIFFSetField(out, TIFFTAG_PIXAR_IMAGEFULLLENGTH,	validHeight);

		appendPyramid<unsigned short>(out,dstart,numSamples,bitspersample,tileSize,width,height,(unsigned short *) data);
	} else if (bitspersample == 32) {
		adjustSize<float>((float **) &data,&width,&height,&validWidth,&validHeight,numSamples,bitspersample,filterWidth,filterHeight,filter,smode,tmode,resizemode);

		// write adjusted sizes
		TIFFSetField(out, TIFFTAG_PIXAR_IMAGEFULLWIDTH,		validWidth);
		TIFFSetField(out, TIFFTAG_PIXAR_IMAGEFULLLENGTH,	validHeight);

		appendPyramid<float>(out,dstart,numSamples,bitspersample,tileSize,width,height,(float *) data);
	}
}


#define getResizeMode(numParams,params,vals) 	\
	const char *resizeMode = resizeUpMode;		\
	for(int p=0;p<numParams;p++) {				\
		if (strcmp(params[p],"resize") == 0) {	\
			resizeMode = * ((char**) vals[p]);	\
			break;								\
		}										\
	}

///////////////////////////////////////////////////////////////////////
// Function				:	makeTexture
// Description			:	Create an image pyramid from input
// Return Value			:
// Comments				:
void	makeTexture(const char *input,const char *output,TSearchpath *path,const char *smode,const char *tmode,RtFilterFunc filt,float fwidth,float fheight,int numParams,const char **params,const void **vals) {
	char	inputFileName[OS_MAX_PATH_LENGTH];
	
	getResizeMode(numParams,params,vals);

	if (CRenderer::locateFile(inputFileName,input,path) == FALSE) {
		error(CODE_NOFILE,"Failed to find \"%s\"\n",input);
	} else {
		// Set the error handler so we don't crash
		TIFFSetErrorHandler(tiffErrorHandler);
		TIFFSetWarningHandler(tiffErrorHandler);

		TIFF	*inHandle = TIFFOpen(inputFileName,"r");
		if (inHandle == NULL) {
			error(CODE_NOFILE,"Failed to open \"%s\"\n",inputFileName);
		} else {
			void			*data;
			int				numSamples;
			int				bitspersample;
			int				width,height;
			int				tileSize		=	DEFAULT_TILE_SIZE;
			RtFilterFunc	filter			=	filt;
			float			filterWidth		=	fwidth;
			float			filterHeight	=	fheight;
			char			modes[128];

			memBegin(CRenderer::globalMemory);

			// Read the texture
			data		=	readLayer(inHandle,&width,&height,&bitspersample,&numSamples);
			TIFFClose(inHandle);

			// Write the made texture
			TIFF	*outHandle	=	TIFFOpen(output,"w");
			if (output != NULL) {
				int	dstart	=	0;

				sprintf(modes,"%s,%s",smode,tmode);

				TIFFSetField(outHandle, TIFFTAG_PIXAR_TEXTUREFORMAT,	TIFF_TEXTURE);
				TIFFSetField(outHandle, TIFFTAG_PIXAR_WRAPMODES,		modes);

				appendTexture(outHandle,dstart,width,height,numSamples,bitspersample,filter,filterWidth,filterHeight,tileSize,data,smode,tmode,resizeMode);

				TIFFClose(outHandle);
			}

			memEnd(CRenderer::globalMemory);
		}
	}
}


///////////////////////////////////////////////////////////////////////
// Function				:	makeSideEnvironment
// Description			:	Create a single sided environment map
// Return Value			:
// Comments				:
void	makeSideEnvironment(const char *input,const char *output,TSearchpath *path,const char *smode,const char *tmode,RtFilterFunc filt,float fwidth,float fheight,int numParams,const char **params,const void **vals,int shadow) {
	char	inputFileName[OS_MAX_PATH_LENGTH];

	getResizeMode(numParams,params,vals);
	
	if (CRenderer::locateFile(inputFileName,input,path) == FALSE) {
		error(CODE_NOFILE,"Failed to find \"%s\"\n",input);
	} else {
		// Set the error handler so we don't crash
		TIFFSetErrorHandler(tiffErrorHandler);
		TIFFSetWarningHandler(tiffErrorHandler);

		TIFF	*inHandle = TIFFOpen(inputFileName,"r");
		if (inHandle == NULL) {
			error(CODE_NOFILE,"Failed to open \"%s\"\n",inputFileName);
		} else {
			void			*data;
			int				numSamples;
			int				bitspersample;
			int				width,height;
			int				tileSize		=	DEFAULT_TILE_SIZE;
			RtFilterFunc	filter			=	filt;
			float			filterWidth		=	fwidth;
			float			filterHeight	=	fheight;
			matrix			worldToCamera,worldToScreen;
			float			*tmp;

			memBegin(CRenderer::globalMemory);

			// Read off the from world transformation from the image if possible
			if (TIFFGetField(inHandle,TIFFTAG_PIXAR_MATRIX_WORLDTOCAMERA,	&tmp) == FALSE) {
				error(CODE_BUG,"Failed to read the world to camera matrix\n");
				identitym(worldToCamera);
			} else {
				movmm(worldToCamera,tmp);
			}

			if (TIFFGetField(inHandle,TIFFTAG_PIXAR_MATRIX_WORLDTOSCREEN,	&tmp) == FALSE) {
				error(CODE_BUG,"Failed to read the world to screen matrix\n");
				identitym(worldToScreen);
			} else {
				movmm(worldToScreen,tmp);
			}


			// Read the data
			data		=	readLayer(inHandle,&width,&height,&bitspersample,&numSamples);

			// Close the input
			TIFFClose(inHandle);

			TIFF	*outHandle = TIFFOpen(output,"w");
			if (output != NULL) {
				int			dstart	=	0;

				// Write the texture data
				TIFFSetField(outHandle, TIFFTAG_PIXAR_TEXTUREFORMAT,		TIFF_SHADOW);
				TIFFSetField(outHandle, TIFFTAG_PIXAR_MATRIX_WORLDTOCAMERA,	worldToCamera);
				TIFFSetField(outHandle, TIFFTAG_PIXAR_MATRIX_WORLDTOSCREEN,	worldToScreen);

				appendTexture(outHandle,dstart,width,height,numSamples,bitspersample,filter,filterWidth,filterHeight,tileSize,data,smode,tmode,resizeMode);

				TIFFClose(outHandle);
			} else {
				error(CODE_SYSTEM,"Failed to create \"%s\" for writing\n",output);
			}

			memEnd(CRenderer::globalMemory);
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	makeCubicEnvironment
// Description			:	Create an environment map where each side is a pyramid
// Return Value			:
// Comments				:
void	makeCubicEnvironment(const char *px,const char *py,const char *pz,const char *nx,const char *ny,const char *nz,const char *output,const char *smode,const char *tmode,TSearchpath *path,RtFilterFunc filt,float fwidth,float fheight,int numParams,const char **params,const void **vals,int shadow) {
	char		inputFileName[OS_MAX_PATH_LENGTH];
	const char	*names[6];

	getResizeMode(numParams,params,vals);
	
	names[0]	=	px;
	names[1]	=	nx;
	names[2]	=	py;
	names[3]	=	ny;
	names[4]	=	pz;
	names[5]	=	nz;

	if (CRenderer::locateFile(inputFileName,names[0],path) == FALSE) {
		error(CODE_NOFILE,"Failed to find \"%s\"\n",names[0]);
	} else {

		// Set the error handler so we don't crash
		TIFFSetErrorHandler(tiffErrorHandler);
		TIFFSetWarningHandler(tiffErrorHandler);

		TIFF	*outHandle = TIFFOpen(output,"w");
		if (output != NULL) {
			void			*data;
			int				numSamples;
			int				bitspersample;
			int				i;
			int				tileSize		=	DEFAULT_TILE_SIZE;
			RtFilterFunc	filter			=	filt;
			float			filterWidth		=	fwidth;
			float			filterHeight	=	fheight;

			if (outHandle != NULL) {
				int			dstart	=	0;

				TIFFSetField(outHandle, TIFFTAG_PIXAR_TEXTUREFORMAT,		TIFF_CUBIC_ENVIRONMENT);

				for (i=0;i<6;i++) {	
					int		width,height;
					TIFF	*inHandle;

					// Open the file
					if (CRenderer::locateFile(inputFileName,names[i],path) == FALSE) {
						error(CODE_NOFILE,"Failed to find \"%s\"\n",names[i]);
						break;
					} else {
						inHandle	=	TIFFOpen(inputFileName,"r");
						if (inHandle == NULL)	break;
					}

					memBegin(CRenderer::globalMemory);

					// Read the data
					data			=	readLayer(inHandle,&width,&height,&bitspersample,&numSamples);
					TIFFClose(inHandle);

					// Write the data
					appendTexture(outHandle,dstart,width,height,numSamples,bitspersample,filter,filterWidth,filterHeight,tileSize,data,smode,tmode,resizeMode);

					memEnd(CRenderer::globalMemory);
				}

				TIFFClose(outHandle);
			}
		} else {
			error(CODE_SYSTEM,"Failed to create \"%s\" for writing\n",output);
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	makeSphericalEnvironment
// Description			:	Create an image pyramid from input
// Return Value			:
// Comments				:
void	makeSphericalEnvironment(const char *input,const char *output,TSearchpath *path,const char *smode,const char *tmode,RtFilterFunc filt,float fwidth,float fheight,int numParams,const char **params,const void **vals) {
	char	inputFileName[OS_MAX_PATH_LENGTH];

	getResizeMode(numParams,params,vals);
	
	if (CRenderer::locateFile(inputFileName,input,path) == FALSE) {
		error(CODE_NOFILE,"Failed to find \"%s\"\n",input);
	} else {
		// Set the error handler so we don't crash
		TIFFSetErrorHandler(tiffErrorHandler);
		TIFFSetWarningHandler(tiffErrorHandler);

		TIFF	*inHandle	=	TIFFOpen(inputFileName,"r");

		if (inHandle == NULL) {
			error(CODE_NOFILE,"Failed to open \"%s\"\n",inputFileName);
		} else {
			void			*data;
			int				numSamples;
			int				bitspersample;
			int				width,height;
			int				tileSize		=	DEFAULT_TILE_SIZE;
			RtFilterFunc	filter			=	filt;
			float			filterWidth		=	fwidth;
			float			filterHeight	=	fheight;
			char			modes[128];

			memBegin(CRenderer::globalMemory);

			// Read the texture
			data		=	readLayer(inHandle,&width,&height,&bitspersample,&numSamples);
			TIFFClose(inHandle);

			TIFF	*outHandle	=	TIFFOpen(output,"w");
			if (output != NULL) {
				int	dstart	=	0;

				sprintf(modes,"%s,%s",smode,tmode);	
				
				// Write out the data
				TIFFSetField(outHandle, TIFFTAG_PIXAR_TEXTUREFORMAT,	TIFF_SPHERICAL_ENVIRONMENT);
				TIFFSetField(outHandle, TIFFTAG_PIXAR_WRAPMODES,		modes);

				appendTexture(outHandle,dstart,width,height,numSamples,bitspersample,filter,filterWidth,filterHeight,tileSize,data,smode,tmode,resizeMode);
				TIFFClose(outHandle);
			}

			memEnd(CRenderer::globalMemory);
		}
	}
}



///////////////////////////////////////////////////////////////////////
// Function				:	makeSphericalEnvironment
// Description			:	Create an image pyramid from input
// Return Value			:
// Comments				:
void	makeCylindericalEnvironment(const char *input,const char *output,TSearchpath *path,const char *smode,const char *tmode,RtFilterFunc filt,float fwidth,float fheight,int numParams,const char **params,const void **vals) {
	char	inputFileName[OS_MAX_PATH_LENGTH];
	
	getResizeMode(numParams,params,vals);
	
	if (CRenderer::locateFile(inputFileName,input,path) == FALSE) {
		error(CODE_NOFILE,"Failed to find \"%s\"\n",input);
	} else {
		// Set the error handler so we don't crash
		TIFFSetErrorHandler(tiffErrorHandler);
		TIFFSetWarningHandler(tiffErrorHandler);

		TIFF	*inHandle		=	TIFFOpen(inputFileName,"r");

		if (inHandle == NULL) {
			error(CODE_NOFILE,"Failed to open \"%s\"\n",inputFileName);
		} else {
			void			*data;
			int				numSamples;
			int				bitspersample;
			int				width,height;
			int				tileSize		=	DEFAULT_TILE_SIZE;
			RtFilterFunc	filter			=	filt;
			float			filterWidth		=	fwidth;
			float			filterHeight	=	fheight;
			char			modes[128];

			memBegin(CRenderer::globalMemory);

			data		=	readLayer(inHandle,&width,&height,&bitspersample,&numSamples);
			TIFFClose(inHandle);


			TIFF	*outHandle	=	TIFFOpen(output,"w");
			if (output != NULL) {
				int	dstart	=	0;

				sprintf(modes,"%s,%s",smode,tmode);
				
				TIFFSetField(outHandle, TIFFTAG_PIXAR_TEXTUREFORMAT,	TIFF_CYLINDER_ENVIRONMENT);
				TIFFSetField(outHandle, TIFFTAG_PIXAR_WRAPMODES,		modes);
				
				appendTexture(outHandle,dstart,width,height,numSamples,bitspersample,filter,filterWidth,filterHeight,tileSize,data,smode,tmode,resizeMode);
				TIFFClose(outHandle);
			}

			memEnd(CRenderer::globalMemory);
		}
	}
}

