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
//  File				:	texmake.cpp
//  Classes				:	-
//  Description			:	This file comtains texture file making routines
//
////////////////////////////////////////////////////////////////////////
#include <stddef.h>		// ensure we have NULL defined before libtiff
#include <tiffio.h>
#include <math.h>

#include "texmake.h"
#include "renderer.h"
#include "ri.h"
#include "stats.h"
#include "memory.h"
#include "error.h"

///////////////////////////////////////////////////////////////////////
// function				:	tiffErrorHandler
// Description			:	Handle errors coming from the libtiff
// Return Value			:	-
// Comments				:
// Date last edited		:	8/10/2001
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
// Date last edited		:	7/6/2001
static	void	appendLayer(TIFF *out,int dstart,int numSamples,int bitsperpixel,int tileSize,int width,int height,void *data,int last) {
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
	TIFFSetField(out, TIFFTAG_SAMPLESPERPIXEL,		(unsigned long) numSamples);
	TIFFSetField(out, TIFFTAG_TILEWIDTH,			(unsigned long) tileSize);
	TIFFSetField(out, TIFFTAG_TILELENGTH,			(unsigned long) tileSize);

	if (bitsperpixel == 8) {
		TIFFSetField(out, TIFFTAG_SAMPLEFORMAT,		SAMPLEFORMAT_UINT);
		TIFFSetField(out, TIFFTAG_BITSPERSAMPLE,		(unsigned long) (sizeof(unsigned char)*8));
		pixelSize	=	numSamples*sizeof(unsigned char);
	} else if (bitsperpixel == 16) {
		TIFFSetField(out, TIFFTAG_SAMPLEFORMAT,		SAMPLEFORMAT_UINT);
		TIFFSetField(out, TIFFTAG_BITSPERSAMPLE,		(unsigned long) (sizeof(unsigned short)*8));
		TIFFSetField(out, TIFFTAG_PHOTOMETRIC,			PHOTOMETRIC_MINISBLACK);
		pixelSize	=	numSamples*sizeof(unsigned short);
	} else {
		TIFFSetField(out, TIFFTAG_SAMPLEFORMAT,		SAMPLEFORMAT_IEEEFP);
		TIFFSetField(out, TIFFTAG_BITSPERSAMPLE,	(unsigned long) (sizeof(float)*8));
		pixelSize	=	numSamples*sizeof(float);
	}

	tileData		=	(unsigned char *) ralloc(pixelSize*tileSize*tileSize);

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

	if (last == FALSE) {
		TIFFWriteDirectory(out);
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	appendPyramid
// Description			:	Append an image pyramid into an image file
//							the reduction gives the amount of reduction in the image size at each step
// Return Value			:
// Comments				:
// Date last edited		:	7/6/2001
template <class T> static	void	appendPyramid(TIFF *out,int dstart,int numSamples,int bitsperpixel,int tileSize,int width,int height,T *data,int pyramidSize,int last) {
	T		*currentLevel;
	int		i;
	int		currentWidth,currentHeight,nextWidth,nextHeight;
	float	*fnextLevel;

	// Append the base layer
	appendLayer(out,dstart,numSamples,bitsperpixel,tileSize,width,height,data,last & (pyramidSize == 1));

	// Append the remaining layers
	currentWidth	=	width;
	currentHeight	=	height;
	currentLevel	=	data;

	fnextLevel		=	(float *)	ralloc(width*height*numSamples*sizeof(float));

	for (i=1;i<pyramidSize;i++) {
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

		appendLayer(out,dstart+i,numSamples,bitsperpixel,tileSize,currentWidth,currentHeight,currentLevel,last & (i == (pyramidSize-1)));
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	readLayer
// Description			:	Read a layer of the image into memory
// Return Value			:
// Comments				:
// Date last edited		:	7/6/2001
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

	data		=	(unsigned char *) ralloc(pixelSize*w*h);

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
// Date last edited		:	7/6/2001
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
// Date last edited		:	7/6/2001
template <class T> void	initData(T *to,int width,int height,int x,int y,int w,int h,int numSamples,T n) {
	int	i,j,s;

	for (j=0;j<h;j++)
		for (i=0;i<w;i++)
			for (s=0;s<numSamples;s++)
				to[((y+j)*width+(x+i))*numSamples+s]	=	n;
}


///////////////////////////////////////////////////////////////////////
// Function				:	adjustSize
// Description			:	Adjust the size of an image so that it's size is a power of two
// Return Value			:
// Comments				:
// Date last edited		:	7/6/2001
template <class T> void	adjustSize(T **data,int *width,int *height,int numSamples,char *smode,char *tmode) {
	int	newWidth,newHeight;

	for (newWidth=1;newWidth < width[0];newWidth = newWidth << 1);
	for (newHeight=1;newHeight < height[0];newHeight = newHeight << 1);

	if (!((width[0] == newWidth) && (height[0] == newHeight))) {
		T *newData;

		newData	=	(T *) ralloc(newWidth*newHeight*numSamples*sizeof(T));
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


		data[0]		=	newData;
		width[0]	=	newWidth;
		height[0]	=	newHeight;
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	filterImage
// Description			:	Apply a filter to the image
// Return Value			:
// Comments				:
// Date last edited		:	7/6/2001
template <class T> void	filterImage(int width,int height,int numSamples,int bitspersample,float filterWidth,float filterHeight,RtFilterFunc filter,T *data) {
	memBegin();

	float	*filteredData	=	(float *) ralloc(width*height*numSamples*sizeof(float));
	float	*normalizer		=	(float *) ralloc(width*height*sizeof(float));
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

	// Normalize the image
	float	*pixel	=	filteredData;
	T		*dest	=	data;
	float	*norm	=	normalizer;

	for (i=0;i<width*height;i++) {
		int	k;

		for (k=0;k<numSamples;k++) {
			dest[k]	=	(T) (pixel[k] / norm[0]);
		}

		dest	+=	numSamples;
		pixel	+=	numSamples;
		norm++;
	}

	memEnd();
}


///////////////////////////////////////////////////////////////////////
// Function				:	getTextureSpec
// Description			:	Generate the texture spec string for a given texture
// Return Value			:
// Comments				:
// Date last edited		:	7/6/2001
void	getTextureSpec(TIFF *in,char *spec,char *smode,char *tmode,int tileSize,int &pyramidSize) {
	uint32			w,h;
	uint32			nw,nh;

	TIFFGetFieldDefaulted(in,TIFFTAG_IMAGEWIDTH              ,&w);
	TIFFGetFieldDefaulted(in,TIFFTAG_IMAGELENGTH             ,&h);

	// Expand the size to power of two
	for (nw=1;nw<w;nw=nw<<1);
	for (nh=1;nh<h;nh=nh<<1);

	// Compute the number of pyramid levels
	if (pyramidSize != 1) {
		assert(pyramidSize == 0);
		for (;(nw > 2) && (nh > 2);nw=nw>>1,nh=nh>>1,pyramidSize++);
	}

	sprintf(spec,"#texture (%dx%d): smode: %s tmode: %s levels: %d",w,h,smode,tmode,pyramidSize);
}

///////////////////////////////////////////////////////////////////////
// Function				:	appendTexture
// Description			:	Make and append a texture to the end of the TIFF file
// Return Value			:
// Comments				:
// Date last edited		:	7/6/2001
void	appendTexture(TIFF *out,int &dstart,int width,int height,int numSamples,int bitspersample,RtFilterFunc filter,float filterWidth,float filterHeight,int tileSize,int pyramidSize,void *data,char *smode,char *tmode,int last) {
	if (bitspersample == 8) {
		if ((filterWidth > 1) || (filterHeight > 1))
			filterImage<unsigned char>(width,height,numSamples,bitspersample,filterWidth,filterHeight,filter,(unsigned char *) data);

		adjustSize<unsigned char>((unsigned char **) &data,&width,&height,numSamples,smode,tmode);

		appendPyramid<unsigned char>(out,0,numSamples,bitspersample,tileSize,width,height,(unsigned char *) data,pyramidSize,last);
	} else if (bitspersample == 16) {
		if ((filterWidth > 1) || (filterHeight > 1))
			filterImage<unsigned short>(width,height,numSamples,bitspersample,filterWidth,filterHeight,filter,(unsigned short *) data);

		adjustSize<unsigned short>((unsigned short **) &data,&width,&height,numSamples,smode,tmode);

		appendPyramid<unsigned short>(out,0,numSamples,bitspersample,tileSize,width,height,(unsigned short *) data,pyramidSize,last);
	} else if (bitspersample == 32) {
		if ((filterWidth > 1) || (filterHeight > 1))
			filterImage<float>(width,height,numSamples,bitspersample,filterWidth,filterHeight,filter,(float *) data);

		adjustSize<float>((float **) &data,&width,&height,numSamples,smode,tmode);

		appendPyramid<float>(out,0,numSamples,bitspersample,tileSize,width,height,(float *) data,pyramidSize,last);
	}

	dstart	+=	pyramidSize;
}

///////////////////////////////////////////////////////////////////////
// Function				:	makeTexture
// Description			:	Create an image pyramid from input
// Return Value			:
// Comments				:
// Date last edited		:	7/6/2001
void	makeTexture(char *input,char *output,TSearchpath *path,char *smode,char *tmode,RtFilterFunc filt,float fwidth,float fheight,int numParams,char **params,void **vals) {
	void			*data;
	int				numSamples;
	int				bitspersample;
	int				width,height;
	int				tileSize		=	32;
	char			tmp[256];
	RtFilterFunc	filter			=	filt;
	float			filterWidth		=	fwidth;
	float			filterHeight	=	fheight;
	char			*outPath		=	NULL;
	int				pyramidSize;
	char			inputFileName[OS_MAX_PATH_LENGTH];
	TIFF			*outHandle;
	TIFF			*inHandle;
	char			spec[1024];


	// Set the error handler so we don't crash
	TIFFSetErrorHandler(tiffErrorHandler);
	TIFFSetWarningHandler(tiffErrorHandler);

	if (currentRenderer->locateFile(inputFileName,input,path) == FALSE) {
		error(CODE_NOFILE,"Unable to find \"%s\"\n",input);
		return;
	}

	inHandle		=	TIFFOpen(inputFileName,"r");
	if (inHandle == NULL) {
		error(CODE_NOFILE,"Unable to open \"%s\" \n",inputFileName);
		return;
	}

	memBegin();

	pyramidSize	=	0;
	getTextureSpec(inHandle,spec,smode,tmode,tileSize,pyramidSize);
	data		=	readLayer(inHandle,&width,&height,&bitspersample,&numSamples);
	TIFFClose(inHandle);

	if (outPath != NULL) {
		if ((outPath[strlen(outPath-1)] == '/') || (outPath[strlen(outPath-1)] == '\\'))
			sprintf(tmp,"%s%s",outPath,output);
		else
			sprintf(tmp,"%s\\%s",outPath,output);
	} else {
		sprintf(tmp,"%s",output);
	}

	outHandle	=	TIFFOpen(tmp,"w");
	if (output != NULL) {
		int	dstart	=	0;
		TIFFSetField(outHandle, TIFFTAG_IMAGEDESCRIPTION,	spec);
		appendTexture(outHandle,dstart,width,height,numSamples,bitspersample,filter,filterWidth,filterHeight,tileSize,pyramidSize,data,smode,tmode,TRUE);
		TIFFClose(outHandle);
	}

	memEnd();
}


///////////////////////////////////////////////////////////////////////
// Function				:	makeSideEnvironment
// Description			:	Create a single sided environment map
// Return Value			:
// Comments				:
// Date last edited		:	7/6/2001
void	makeSideEnvironment(char *input,char *output,TSearchpath *path,char *smode,char *tmode,RtFilterFunc filt,float fwidth,float fheight,int numParams,char **params,void **vals,int shadow) {
	void			*data;
	int				numSamples;
	int				bitspersample;
	int				width,height;
	int				tileSize		=	32;
	char			tmp[256];
	RtFilterFunc	filter			=	filt;
	float			filterWidth		=	fwidth;
	float			filterHeight	=	fheight;
	char			*outPath		=	NULL;
	int				pyramidSize;
	char			inputFileName[OS_MAX_PATH_LENGTH];
	TIFF			*outHandle;
	TIFF			*inHandle;
	char			spec[1024];
	char			allSpec[1024];


	// Set the error handler so we don't crash
	TIFFSetErrorHandler(tiffErrorHandler);
	TIFFSetWarningHandler(tiffErrorHandler);

	if (currentRenderer->locateFile(inputFileName,input,path) == FALSE) {
		error(CODE_NOFILE,"Unable to find \"%s\"\n",input);
		return;
	}

	inHandle	=	TIFFOpen(inputFileName,"r");
	if (inHandle == NULL) {
		error(CODE_NOFILE,"Unable to open \"%s\" \n",inputFileName);
		return;
	}

	memBegin();

	// Read off the from world transformation from the image if possible
	{
		char	*desc;

		TIFFGetFieldDefaulted(inHandle,	TIFFTAG_IMAGEDESCRIPTION,	&desc);

		if (strncmp(desc,"WorldToNDC=",11) == 0) {
			strcpy(spec,desc+11);
		} else {
			sprintf(spec,"[1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1] ");
		}
	}

	// Set the spec
	sprintf(allSpec,"#shadow ");
	strcat(allSpec,spec);
		
	strcat(allSpec," ");
	pyramidSize	=	(shadow ? 1 : 0);
	getTextureSpec(inHandle,spec,smode,tmode,tileSize,pyramidSize);
	strcat(allSpec,spec);

	// Read the data
	data		=	readLayer(inHandle,&width,&height,&bitspersample,&numSamples);

	// Close the input
	TIFFClose(inHandle);

	if (outPath != NULL) {
		if ((outPath[strlen(outPath-1)] == '/') || (outPath[strlen(outPath-1)] == '\\'))
			sprintf(tmp,"%s%s",outPath,output);
		else
			sprintf(tmp,"%s\\%s",outPath,output);
	} else {
		sprintf(tmp,"%s",output);
	}

	outHandle	=	TIFFOpen(tmp,"w");
	if (output != NULL) {
		int			dstart	=	0;

		TIFFSetField(outHandle, TIFFTAG_IMAGEDESCRIPTION,	allSpec);

		appendTexture(outHandle,dstart,width,height,numSamples,bitspersample,filter,filterWidth,filterHeight,tileSize,1,data,smode,tmode,TRUE);

		TIFFClose(outHandle);
	} else {
		error(CODE_SYSTEM,"Unable to create %s for writing\n",tmp);
	}

	memEnd();
}

///////////////////////////////////////////////////////////////////////
// Function				:	makeCubicEnvironment
// Description			:	Create an environment map where each side is a pyramid
// Return Value			:
// Comments				:
// Date last edited		:	7/6/2001
void	makeCubicEnvironment(char *px,char *py,char *pz,char *nx,char *ny,char *nz,char *output,char *smode,char *tmode,TSearchpath *path,RtFilterFunc filt,float fwidth,float fheight,int numParams,char **params,void **vals,int shadow) {
	void			*data;
	int				numSamples;
	int				bitspersample;
	int				i;
	int				width,height;
	int				tileSize		=	32;
	char			tmp[256];
	RtFilterFunc	filter			=	filt;
	float			filterWidth		=	fwidth;
	float			filterHeight	=	fheight;
	char			*outPath		=	NULL;
	int				pyramidSize;
	char			inputFileName[OS_MAX_PATH_LENGTH];
	TIFF			*outHandle;
	char			*names[6];
	char			allSpec[1024];

	names[0]	=	px;
	names[1]	=	nx;
	names[2]	=	py;
	names[3]	=	ny;
	names[4]	=	pz;
	names[5]	=	nz;

	// Set the error handler so we don't crash
	TIFFSetErrorHandler(tiffErrorHandler);
	TIFFSetWarningHandler(tiffErrorHandler);

	if (currentRenderer->locateFile(inputFileName,names[0],path) == FALSE) {
		error(CODE_NOFILE,"Unable to find \"%s\"\n",names[0]);
		return;
	}

	if (outPath != NULL) {
		if ((outPath[strlen(outPath-1)] == '/') || (outPath[strlen(outPath-1)] == '\\'))
			sprintf(tmp,"%s%s",outPath,output);
		else
			sprintf(tmp,"%s\\%s",outPath,output);
	} else {
		sprintf(tmp,"%s",output);
	}

	outHandle	=	TIFFOpen(tmp,"w");
	if (output != NULL) {
		TIFF	*inHandles[6];
		sprintf(allSpec,"#cenvironment ");
		
		// Make one pass to create the env spec
		for (i=0;i<6;i++) {
			char		spec[1024];

			if (currentRenderer->locateFile(inputFileName,names[i],path) == FALSE) {
				error(CODE_NOFILE,"Unable to find \"%s\"\n",names[i]);
				TIFFClose(outHandle);
				return;
			}

			inHandles[i]	=	TIFFOpen(inputFileName,"r");
			if (inHandles[i] == NULL) {
				int	j;

				error(CODE_NOFILE,"Unable to open \"%s\" \n",inputFileName);

				for (j=0;j<i;j++)	TIFFClose(inHandles[j]);
				TIFFClose(outHandle);
				return;
			}

			pyramidSize	=	(shadow ? 1 : 0);
			getTextureSpec(inHandles[i],spec,smode,tmode,tileSize,pyramidSize);

			strcat(allSpec,spec);
			strcat(allSpec," ");
		}

		TIFFSetField(outHandle, TIFFTAG_IMAGEDESCRIPTION,	allSpec);

		for (i=0;i<6;i++) {
			int			dstart	=	0;

			memBegin();

			data			=	readLayer(inHandles[i],&width,&height,&bitspersample,&numSamples);
			TIFFClose(inHandles[i]);

			appendTexture(outHandle,dstart,width,height,numSamples,bitspersample,filter,filterWidth,filterHeight,tileSize,pyramidSize,data,smode,tmode,(i == 5 ? TRUE : FALSE));

			memEnd();
		}

		TIFFClose(outHandle);
	} else {
		error(CODE_SYSTEM,"Unable to create %s for writing\n",tmp);
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	makeSphericalEnvironment
// Description			:	Create an image pyramid from input
// Return Value			:
// Comments				:
// Date last edited		:	7/6/2001
void	makeSphericalEnvironment(char *input,char *output,TSearchpath *path,char *smode,char *tmode,RtFilterFunc filt,float fwidth,float fheight,int numParams,char **params,void **vals) {
	void			*data;
	int				numSamples;
	int				bitspersample;
	int				width,height;
	int				tileSize		=	32;
	char			tmp[256];
	RtFilterFunc	filter			=	filt;
	float			filterWidth		=	fwidth;
	float			filterHeight	=	fheight;
	char			*outPath		=	NULL;
	int				pyramidSize;
	char			inputFileName[OS_MAX_PATH_LENGTH];
	TIFF			*outHandle;
	TIFF			*inHandle;
	char			spec[1024];
	char			allSpec[1024];

	// Set the error handler so we don't crash
	TIFFSetErrorHandler(tiffErrorHandler);
	TIFFSetWarningHandler(tiffErrorHandler);

	if (currentRenderer->locateFile(inputFileName,input,path) == FALSE) {
		error(CODE_NOFILE,"Unable to find \"%s\"\n",input);
		return;
	}

	inHandle		=	TIFFOpen(inputFileName,"r");
	if (inHandle == NULL) {
		error(CODE_NOFILE,"Unable to open \"%s\" \n",inputFileName);
		return;
	}

	memBegin();

	pyramidSize	=	0;
	getTextureSpec(inHandle,spec,smode,tmode,tileSize,pyramidSize);
	sprintf(allSpec,"#senvironment %s",spec);

	data		=	readLayer(inHandle,&width,&height,&bitspersample,&numSamples);
	TIFFClose(inHandle);

	if (outPath != NULL) {
		if ((outPath[strlen(outPath-1)] == '/') || (outPath[strlen(outPath-1)] == '\\'))
			sprintf(tmp,"%s%s",outPath,output);
		else
			sprintf(tmp,"%s\\%s",outPath,output);
	} else {
		sprintf(tmp,"%s",output);
	}

	outHandle	=	TIFFOpen(tmp,"w");
	if (output != NULL) {
		int	dstart	=	0;
		TIFFSetField(outHandle, TIFFTAG_IMAGEDESCRIPTION,	allSpec);
		appendTexture(outHandle,dstart,width,height,numSamples,bitspersample,filter,filterWidth,filterHeight,tileSize,pyramidSize,data,smode,tmode,TRUE);
		TIFFClose(outHandle);
	}

	memEnd();
}



///////////////////////////////////////////////////////////////////////
// Function				:	makeSphericalEnvironment
// Description			:	Create an image pyramid from input
// Return Value			:
// Comments				:
// Date last edited		:	7/6/2001
void	makeCylindericalEnvironment(char *input,char *output,TSearchpath *path,char *smode,char *tmode,RtFilterFunc filt,float fwidth,float fheight,int numParams,char **params,void **vals) {
	void			*data;
	int				numSamples;
	int				bitspersample;
	int				width,height;
	int				tileSize		=	32;
	char			tmp[256];
	RtFilterFunc	filter			=	filt;
	float			filterWidth		=	fwidth;
	float			filterHeight	=	fheight;
	char			*outPath		=	NULL;
	int				pyramidSize;
	char			inputFileName[OS_MAX_PATH_LENGTH];
	TIFF			*outHandle;
	TIFF			*inHandle;
	char			spec[1024];
	char			allSpec[1024];

	// Set the error handler so we don't crash
	TIFFSetErrorHandler(tiffErrorHandler);
	TIFFSetWarningHandler(tiffErrorHandler);

	if (currentRenderer->locateFile(inputFileName,input,path) == FALSE) {
		error(CODE_NOFILE,"Unable to find \"%s\"\n",input);
		return;
	}

	inHandle		=	TIFFOpen(inputFileName,"r");
	if (inHandle == NULL) {
		error(CODE_NOFILE,"Unable to open \"%s\" \n",inputFileName);
		return;
	}

	memBegin();

	pyramidSize	=	0;
	getTextureSpec(inHandle,spec,smode,tmode,tileSize,pyramidSize);
	sprintf(allSpec,"#lenvironment %s",spec);

	data		=	readLayer(inHandle,&width,&height,&bitspersample,&numSamples);
	TIFFClose(inHandle);

	if (outPath != NULL) {
		if ((outPath[strlen(outPath-1)] == '/') || (outPath[strlen(outPath-1)] == '\\'))
			sprintf(tmp,"%s%s",outPath,output);
		else
			sprintf(tmp,"%s\\%s",outPath,output);
	} else {
		sprintf(tmp,"%s",output);
	}

	outHandle	=	TIFFOpen(tmp,"w");
	if (output != NULL) {
		int	dstart	=	0;
		TIFFSetField(outHandle, TIFFTAG_IMAGEDESCRIPTION,	allSpec);
		appendTexture(outHandle,dstart,width,height,numSamples,bitspersample,filter,filterWidth,filterHeight,tileSize,pyramidSize,data,smode,tmode,TRUE);
		TIFFClose(outHandle);
	}

	memEnd();
}

