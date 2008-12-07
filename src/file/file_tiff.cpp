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
//  File				:	file_tiff.cpp
//  Classes				:
//  Description			:	This file implements the TIFF writer output device
//
////////////////////////////////////////////////////////////////////////

#include "file_tiff.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

///////////////////////////////////////////////////////////////////////
// Class				:	CFileFramebufferTIFF
// Description			:	Holds the framebuffer
// Comments				:
CFileFramebufferTIFF::CFileFramebufferTIFF(const char *name,int width,int height,int numSamples,const char *samples,TDisplayParameterFunction findParameter): 
CFileFramebuffer() 
{
	int			i;
	float		*tmp;
	float		worldToNDC[16];
	float		worldToCamera[16];
	char		*software;
	const char	*compression	=	NULL;
	
	// Open the image file
	image				=	TIFFOpen(name,"w");
	
	// If we could not open the file, there's nothing to do
	if (image == NULL)	return;
	
	// Copy the quantization data
	if ((tmp = (float *) findParameter("quantize",FLOAT_PARAMETER,4))) {
		qzero			=	tmp[0];
		qone			=	tmp[1];
		qmin			=	tmp[2];
		qmax			=	tmp[3];
	} else {
		qzero			=	0;
		qone			=	0;
		qmin			=	0;
		qmax			=	0;
	}
	
	// Get the gamma correction stuff (only if we're not depth)
	if (strcmp(samples,"z") != 0) {
		
		if ((tmp = (float *) findParameter("dither",FLOAT_PARAMETER,1))) {
			qamp			=	tmp[0];
		}
		
		if ((tmp = (float *) findParameter("gamma",FLOAT_PARAMETER,1))) {
			gamma			=	tmp[0];
		}
		
		if ((tmp = (float *) findParameter("gain",FLOAT_PARAMETER,1))) {
			gain			=	tmp[0];
		}
	} else {
		// If we're saving the z channel, we must be HDR
		qamp			=	0;
		gamma			=	1;
		gain			=	1;
	}
	
	// World to screen matrix
	if ((tmp = (float *) findParameter("NP",FLOAT_PARAMETER,16))) {
		int	i;
		
		for (i=0;i<16;i++) {
			worldToNDC[i]	=	tmp[i];
		}
	}
	
	// World to Camera matrix
	if ((tmp = (float *) findParameter("Nl",FLOAT_PARAMETER,16))) {
		int	i;
		
		for (i=0;i<16;i++) {
			worldToCamera[i]	=	tmp[i];
		}
	}
	
	software	=	(char *) findParameter("Software",STRING_PARAMETER,1);
	
	compression	=	(char *) findParameter("compression",STRING_PARAMETER,1);
	
	if (qmax == 0) {
		bitspersample	=	32;
		sampleformat	=	SAMPLEFORMAT_IEEEFP;
	} else if (qmax > 65535) {
		bitspersample	=	32;
		sampleformat	=	SAMPLEFORMAT_UINT;
	} else if (qmax > 255) {
		bitspersample	=	16;
		sampleformat	=	SAMPLEFORMAT_UINT;
	} else {
		bitspersample	=	8;
		sampleformat	=	SAMPLEFORMAT_UINT;
	}
	
	// Set the tiff fields
	TIFFSetField(image, TIFFTAG_IMAGEWIDTH,			(unsigned long) width);
	TIFFSetField(image, TIFFTAG_IMAGELENGTH,		(unsigned long) height);
	TIFFSetField(image, TIFFTAG_ORIENTATION,		ORIENTATION_TOPLEFT);
	TIFFSetField(image, TIFFTAG_PLANARCONFIG,		PLANARCONFIG_CONTIG);
	TIFFSetField(image, TIFFTAG_RESOLUTIONUNIT,		RESUNIT_NONE);
	TIFFSetField(image, TIFFTAG_XRESOLUTION,		(float) 1.0);
	TIFFSetField(image, TIFFTAG_YRESOLUTION,		(float) 1.0);
	TIFFSetField(image, TIFFTAG_BITSPERSAMPLE,		(unsigned short) bitspersample);
	TIFFSetField(image, TIFFTAG_SAMPLEFORMAT,		(unsigned short) sampleformat);
	TIFFSetField(image, TIFFTAG_SAMPLESPERPIXEL,	(unsigned short) numSamples);
	TIFFSetField(image, TIFFTAG_PIXAR_MATRIX_WORLDTOSCREEN,	worldToNDC);
	TIFFSetField(image, TIFFTAG_PIXAR_MATRIX_WORLDTOCAMERA,	worldToCamera);
	
	// Compute the size of a pixel
	pixelSize	=	numSamples*bitspersample / 8;
	
	// The default compression is LZW
	ttag_t tiffcompression = COMPRESSION_LZW;
	if (compression == NULL)
		tiffcompression = COMPRESSION_LZW;
	else if (strcmp(compression,"LZW") == 0 || strcmp(compression,"lzw") == 0)
		tiffcompression = COMPRESSION_LZW;
	else if (strcmp(compression,"JPEG") == 0 || strcmp(compression,"jpeg") == 0 || strcmp(compression,"jpg") == 0)
		tiffcompression = COMPRESSION_JPEG;
	else if (strcmp(compression,"Deflate") == 0 || strcmp(compression,"deflate") == 0 || strcmp(compression,"zip") == 0)
		tiffcompression = COMPRESSION_ADOBE_DEFLATE;
	else if (strcmp(compression,"none") == 0)
		tiffcompression = COMPRESSION_NONE;
	
	// Check codec availability in libtiff
	if (tiffcompression != COMPRESSION_NONE && !TIFFIsCODECConfigured(tiffcompression)) {
		if (TIFFIsCODECConfigured(COMPRESSION_LZW))
			tiffcompression = COMPRESSION_LZW;
		else
			tiffcompression = COMPRESSION_NONE;
	}
	TIFFSetField(image, TIFFTAG_COMPRESSION, tiffcompression);
	
	if (tiffcompression == COMPRESSION_LZW || tiffcompression == COMPRESSION_DEFLATE 
		|| tiffcompression == COMPRESSION_ADOBE_DEFLATE || tiffcompression == COMPRESSION_PIXARLOG ) {
		ttag_t predictor = PREDICTOR_HORIZONTAL;
		if (sampleformat == SAMPLEFORMAT_IEEEFP)
			predictor = PREDICTOR_FLOATINGPOINT;
		TIFFSetField(image, TIFFTAG_PREDICTOR, predictor);
	}		
	
	if (numSamples == 1)
		TIFFSetField(image, TIFFTAG_PHOTOMETRIC,	PHOTOMETRIC_MINISBLACK);
	else
		TIFFSetField(image, TIFFTAG_PHOTOMETRIC,	PHOTOMETRIC_RGB);
	
	if (numSamples == 4) {
		unsigned short sampleinfo = EXTRASAMPLE_ASSOCALPHA;
		TIFFSetField(image, TIFFTAG_EXTRASAMPLES, 1, &sampleinfo);
	}
	
	if (software != NULL)	TIFFSetField(image, TIFFTAG_SOFTWARE,		software);
	
	lastSavedLine	=	0;
	scanlines		=	new unsigned char*[height];
	scanlineUsage	=	new int[height];
	
	for (i=0;i<height;i++) {
		scanlines[i]		=	NULL;
		scanlineUsage[i]	=	width;
	}
	
	this->width			=	width;
	this->height		=	height;
	this->numSamples	=	numSamples;
	
	osCreateMutex(fileMutex);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFileFramebufferTIFF
// Method				:	~CFileFramebufferTIFF
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CFileFramebufferTIFF::~CFileFramebufferTIFF() 
{
	int	i;

	if (image == NULL)
		return;

	TIFFClose(image);
	osDeleteMutex(fileMutex);
					
	for (i=0;i<height;i++) {
		if (scanlines[i] != NULL)	
			delete [] (unsigned char *) scanlines[i];
	}
					
	delete [] scanlines;
	delete [] scanlineUsage;
}
	
///////////////////////////////////////////////////////////////////////
// Class				:	CFileFramebufferTIFF
// Method				:	write
// Description			:	Write image data to the file
// Return Value			:	-
// Comments				:
void CFileFramebufferTIFF::write(int x,int y,int w,int h,float *data) 
{
	int				i,j;
	int				check		=	FALSE;
	int				numChannels	=	w*h*numSamples;
	
	if (image == NULL)	return;
	
	// Apply the gamma correction if applicable
	if ((gamma != 1) || (gain != 1)) {
		float	invGamma	=	1 / gamma;
		
		for (i=0;i<numChannels;i++) {
			data[i]	=	powf(gain*data[i],invGamma);
		}
	}
	
	// Apply the quantization if applicable
	if (qmax > 0) {
		for (i=0;i<numChannels;i++) {
			float	dither	=	qamp*(2*(rand() / (float) RAND_MAX)-1);
			data[i]			=	qzero + (qone - qzero)*data[i] + dither;
			if (data[i] < qmin)			data[i]	=	qmin;
			else if (data[i] > qmax)	data[i]	=	qmax;
		}
	}
	
	// Lock the file
	osLock(fileMutex);
	
	// Record the data
	for (i=0;i<h;i++) {
		unsigned char	*scan;
		
		if (scanlines[i+y] == NULL) {
			scanlines[i+y]	=	scan	=	new unsigned char[width*pixelSize];
		} else {
			scan			=	(unsigned char *) scanlines[i+y];
		}
		
		switch(bitspersample) {
			case 8:
			{
				const float		*src	=	&data[i*w*numSamples];
				unsigned char	*dest	=	&((unsigned char *) scan)[x*numSamples];
				
				for (j=0;j<w*numSamples;j++) {
					*dest++		=	(unsigned char) *src++;
				}
			}
				break;
			case 16:
			{
				const float		*src	=	&data[i*w*numSamples];
				unsigned short	*dest	=	&((unsigned short *) scan)[x*numSamples];
				
				for (j=0;j<w*numSamples;j++) {
					*dest++		=	(unsigned short) *src++;
				}
			}
				break;
			case 32:
				if (sampleformat == SAMPLEFORMAT_IEEEFP) {
					const float	*src	=	&data[i*w*numSamples];
					float		*dest	=	&((float *) scan)[x*numSamples];
					
					for (j=0;j<w*numSamples;j++) {
						*dest++		=	*src++;
					}
				} else {
					const float		*src	=	&data[i*w*numSamples];
					unsigned int	*dest	=	&((unsigned int *) scan)[x*numSamples];
					
					for (j=0;j<w*numSamples;j++) {
						*dest++		=	(unsigned int) *src++;
					}
				}
				break;
			default:
				break;
		}
		
		scanlineUsage[i+y]	-=	w;
		if (scanlineUsage[i+y] <= 0)	check	=	TRUE;
	}
	
	if (check) {
		for (;lastSavedLine<height;lastSavedLine++) {
			if (scanlineUsage[lastSavedLine] == 0) {
				if (scanlines[lastSavedLine] != NULL) {
					TIFFWriteScanline(image,scanlines[lastSavedLine],lastSavedLine,0);
					delete [] scanlines[lastSavedLine];
					scanlines[lastSavedLine]	=	NULL;
				}
			} else {
				break;
			}
		}
	}
	
	// Release the file
	osUnlock(fileMutex);
}	


