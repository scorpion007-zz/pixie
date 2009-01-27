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
//  File				:	file_png.cpp
//  Classes				:
//  Description			:	This file implements the PNG writer output device
//							PNG only does 8 and 16 bit pixel depths, so 32bits or floats give error
//							Gamma is stored in the metadata and does not change pixel values
//
////////////////////////////////////////////////////////////////////////
#include "common/global.h"

#ifdef HAVE_LIBPNG

#include "file_png.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

///////////////////////////////////////////////////////////////////////
// Class				:	CFileFramebufferPNG
// Description			:	Holds the framebuffer
// Comments				:
CFileFramebufferPNG::CFileFramebufferPNG(const char *name,int width,int height,int numSamples,const char *samples,TDisplayParameterFunction findParameter): 
CFileFramebuffer() 
{
	int			i;
	float		*tmp;
	char		*software;

	fhandle = NULL;

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
	
	if (width < 1 || height < 1 || numSamples < 1 || numSamples > 4 || qmax == 0 || qmax > 65535 || !name || !samples)
		return;	// Parameter error
	
	// Open PNG library
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL)
		return;

	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		png_destroy_write_struct(&png_ptr, NULL);
		return;
	}

	software	=	(char *) findParameter("Software",STRING_PARAMETER,1);
	if (software) {
		png_text comment;
		comment.compression = -1;
		comment.key = (png_charp) "Software";
		comment.text = software;
		comment.text_length = strlen(software);
		png_set_text(png_ptr, info_ptr, &comment, 1);
	}

	// Create the image file
	fhandle = fopen(name,"w+");
	if (fhandle == NULL) {
		png_destroy_write_struct(&png_ptr, &info_ptr);
		return;
	}
	png_init_io(png_ptr, fhandle);
	
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
	
	if (gamma != 1.0)
		png_set_gAMA(png_ptr, info_ptr, gamma);
	
	if (qmax > 255) {
		bitspersample	=	16;
	} else {
		bitspersample	=	8;
	}
	
	int color_type;
	switch(numSamples) {
		case 1:
			color_type = PNG_COLOR_TYPE_GRAY;
			break;
		case 2:
			color_type = PNG_COLOR_TYPE_GRAY_ALPHA;
			break;
		case 3:
			color_type = PNG_COLOR_TYPE_RGB;
			break;
		case 4:
			color_type = PNG_COLOR_TYPE_RGB_ALPHA;
			break;
		default:
			break;
	}
	
	// Set the PNG fields
	png_set_IHDR(png_ptr,
				 info_ptr,
				 width,
				 height,
				 bitspersample,
				 color_type,
				 PNG_INTERLACE_NONE,
				 PNG_COMPRESSION_TYPE_DEFAULT,
				 PNG_FILTER_TYPE_DEFAULT);
	
	// Compute the size of a pixel
	pixelSize	=	numSamples*bitspersample / 8;
					
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
	
	png_write_info(png_ptr, info_ptr);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CFileFramebufferPNG
// Method				:	~CFileFramebufferPNG
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CFileFramebufferPNG::~CFileFramebufferPNG() {
	int	i;
	
	if (fhandle == NULL)
		return;

	png_write_end(png_ptr, info_ptr);
	fclose(fhandle);
	osDeleteMutex(fileMutex);
	
	png_destroy_write_struct(&png_ptr, &info_ptr);
					
	for (i=0;i<height;i++) {
		if (scanlines[i] != NULL)	
			delete [] (unsigned char *) scanlines[i];
	}
					
	delete [] scanlines;
	delete [] scanlineUsage;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CFileFramebufferPNG
// Method				:	write
// Description			:	Write image data to the file
// Return Value			:	-
// Comments				:
void CFileFramebufferPNG::write(int x,int y,int w,int h,float *data) 
{
	int				i,j;
	int				check		=	FALSE;
	int				numChannels	=	w*h*numSamples;
	
	if (fhandle == NULL)
		return;
	
	// Apply the pixel correction if applicable
	if (gain != 1) {
		for (i=0;i<numChannels;i++) {
			data[i]	*= gain;
		}
	}
		
	// Apply the quantization if applicable
	if (qmax > 0) {
		for (i=0;i<numChannels;i++) {
			float	dither	=	qamp*(2*(rand() / (float) RAND_MAX)-1);
			data[i]			=	qzero + (qone - qzero)*data[i] + dither;
			if (data[i] < qmin)
				data[i]	= qmin;
			else if (data[i] > qmax)
				data[i]	= qmax;
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
					png_write_row(png_ptr,scanlines[lastSavedLine]);
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

#endif // HAVE_LIBPNG


