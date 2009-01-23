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
//							that sends the image into a file
//
////////////////////////////////////////////////////////////////////////
#include "common/global.h"
#include "common/algebra.h"
#include "common/os.h"
#include "ri/dsply.h"							// The display driver interface

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "file_tiff.h"

#ifdef HAVE_LIBPNG
#include "file_png.h"
#endif


///////////////////////////////////////////////////////////////////////
// Function				:	displayStart
// Description			:	Begin receiving an image
// Return Value			:	The handle to the image on success, NULL othervise
// Comments				:
void	*displayStart(const char *name,int width,int height,int numSamples,const char *samples,TDisplayParameterFunction findParameter) {
	CFileFramebuffer	*fb = NULL;

#ifdef HAVE_LIBPNG
	char* type	= (char *)findParameter("type",STRING_PARAMETER,1);		// Display "name" "type" "mode" ...
	int len = strlen(name);
	if ( 
		 // Name contains "png" and type is not specifically "tiff"
		 ( (len > 4 && strcmp(&name[len-4],".png")==0) && ( type && strcmp(type, "tiff") != 0 ) )
		 // or type is specifically "png"
		 || (type && strcmp(type, "png") == 0 ) ) {
		fb = new CFileFramebufferPNG(name,width,height,numSamples,samples,findParameter);
		if (!fb->success()) {
			delete fb;
			fb = NULL;
		}
	}
#endif
	if (!fb)
		fb = new CFileFramebufferTIFF(name,width,height,numSamples,samples,findParameter);
	
	if (!fb->success()) {	// If we could not create the image file, return NULL
		delete fb;
		return NULL;
	}

	return fb;
}


///////////////////////////////////////////////////////////////////////
// Function				:	displayData
// Description			:	Receive image data
// Return Value			:	TRUE on success, FALSE otherwise
// Comments				:
int		displayData(void *im,int x,int y,int w,int h,float *data) {
	CFileFramebuffer	*fb	=	(CFileFramebuffer *) im;
	
	assert(fb != NULL);

	fb->write(x,y,w,h,data);

	return TRUE;
}


///////////////////////////////////////////////////////////////////////
// Function				:	displayFinish
// Description			:	Finish receiving an image
// Return Value			:	-
// Comments				:
void	displayFinish(void *im) {
	CFileFramebuffer	*fb	=	(CFileFramebuffer *) im;

	assert(fb != NULL);

	delete fb;
}

