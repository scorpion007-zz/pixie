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
//  File				:	file.cpp
//  Classes				:
//  Description			:	This file implements the default output device
//							that sends the image into a radiance RGBA image
//
//
////////////////////////////////////////////////////////////////////////
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/global.h"
#include "common/os.h"
#include "ri/dsply.h"							// The display functions
#include "rgbe.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CRendererbuffer
// Description			:	Holds the framebuffer
// Comments				:
class	CRgbeFramebuffer {
public:
				///////////////////////////////////////////////////////////////////////
				// Class				:	CRendererbuffer
				// Method				:	CRendererbuffer
				// Description			:	Ctor
				// Return Value			:	-
				// Comments				:
				CRgbeFramebuffer(const char *name,int width,int height,int numSamples,const char *samples,TDisplayParameterFunction findParameter) {
					char	fileName[256];

					if (strchr(name,'.') == NULL) {
						sprintf(fileName,"%s.pic",name);
					} else {
						strcpy(fileName,name);
					}

					image				=	fopen(fileName,"wb");

					RGBE_WriteHeader(image,width,height,NULL);

					this->width			=	width;
					this->height		=	height;
					this->numSamples	=	numSamples;
					this->data			=	new float[width*height*numSamples];
				}

				///////////////////////////////////////////////////////////////////////
				// Class				:	CRendererbuffer
				// Method				:	~CRendererbuffer
				// Description			:	Dtor
				// Return Value			:	-
				// Comments				:
				~CRgbeFramebuffer() {
					RGBE_WritePixels(image,data,width*height);

					if (image != NULL)	fclose(image);

					delete [] data;
				}

				///////////////////////////////////////////////////////////////////////
				// Class				:	CRendererbuffer
				// Method				:	write
				// Description			:	Swrite some data to the out file
				// Return Value			:	-
				// Comments				:
	void		write(int x,int y,int w,int h,float *data) {
					int				i,j;

					if (image == NULL)	return;

					for (i=0;i<w*h*numSamples;i++) {
						if (data[i] < 0)	data[i]	=	0;
					}

					for (i=0;i<h;i++) {
						float	*src	=	data		+ (i*w*numSamples);
						float	*dest	=	this->data	+ ((i+y)*width + x)*numSamples;

						for (j=0;j<w*numSamples;j++) {
							*dest++		=	*src++;
						}
					}
				}

	int			width,height,numSamples;
	float		*data;
	FILE		*image;
};

///////////////////////////////////////////////////////////////////////
// Function				:	displayStart
// Description			:	Begin receiving an image
// Return Value			:	The handle to the image on success, NULL othervise
// Comments				:
void	*displayStart(const char *name,int width,int height,int numSamples,const char *samples,TDisplayParameterFunction findParameter) {
	return new CRgbeFramebuffer(name,width,height,numSamples,samples,findParameter);
}

///////////////////////////////////////////////////////////////////////
// Function				:	displayData
// Description			:	Receive image data
// Return Value			:	TRUE on success, FALSE otherwise
// Comments				:
int		displayData(void *im,int x,int y,int w,int h,float *data) {
	CRgbeFramebuffer	*fb	=	(CRgbeFramebuffer *) im;
	
	assert(fb != NULL);

	fb->write(x,y,w,h,data);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// Function				:	displayFinish
// Description			:	Finish receiving an image
// Return Value			:	TRUE on success, FALSE othervise
// Comments				:
void	displayFinish(void *im) {
	CRgbeFramebuffer	*fb	=	(CRgbeFramebuffer *) im;

	assert(fb != NULL);

	delete fb;
}

