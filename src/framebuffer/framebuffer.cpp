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
//  File				:	framebuffer.cpp
//  Classes				:	CDisplay
//  Description			:	Implementation of the framebuffer display driver
//
////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>

#include "common/global.h"
#include "framebuffer.h"
#include "ri/dsply.h"


#define TRUE	1
#define	FALSE	0

#ifdef _WINDOWS
#include "fbw.h"	// Windoze framebuffer
#else
#include "fbx.h"	// X-Windoze framebuffer
#endif

///////////////////////////////////////////////////////////////////////
// Class				:	CDisplay
// Method				:	CDisplay
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CDisplay::CDisplay(const char *name,const char *samples,int width,int height,int numSamples) {
	this->failure		=	FALSE;
	this->name			=	strdup(name);
	this->samples		=	strdup(samples);
	this->width			=	width;
	this->height		=	height;
	this->numSamples	=	numSamples;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDisplay
// Method				:	~CDisplay
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CDisplay::~CDisplay() {
	free(name);
	free(samples);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CDisplay
// Method				:	clampData
// Description			:	The main display loop
// Return Value			:	-
// Comments				:
void	CDisplay::clampData(int w,int h,float *d) {
	float	*cData	=	d;
	int		c		=	w*h*numSamples;

	for (;c>0;c--,cData++) {
		if (*cData < 0)			*cData	=	0;
		else if (*cData > 1)	*cData	=	1;
	}
}


///////////////////////////////////////////////////////////////////////
// Function				:	displayStart
// Description			:	Begin receiving an image
// Return Value			:	The handle to the image on success, NULL othervise
// Comments				:
void	*displayStart(const char *name,int width,int height,int numSamples,const char *samples,TDisplayParameterFunction findParameter) {

#ifdef _WINDOWS
	CWinDisplay		*cWindow	=	new CWinDisplay(name,samples,width,height,numSamples);
#else
	CXDisplay		*cWindow	=	new CXDisplay(name,samples,width,height,numSamples);
#endif

	if (cWindow->failure == TRUE) {
		delete cWindow;
		return NULL;
	} else {
		return cWindow;
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	displayData
// Description			:	Receive image data
// Return Value			:	TRUE on success, FALSE otherwise
// Comments				:
int		displayData(void *im,int x,int y,int w,int h,float *data) {
	CDisplay	*cWindow	=	(CDisplay *) im;

	assert(cWindow != NULL);

	if (cWindow->data(x,y,w,h,data) == FALSE) {
		delete cWindow;
		return FALSE;
	}

	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// Function				:	displayFinish
// Description			:	Finish receiving an image
// Return Value			:	TRUE on success, FALSE othervise
// Comments				:
void	displayFinish(void *im) {
	CDisplay	*cWindow		=	(CDisplay *) im;

	assert(cWindow != NULL);

	cWindow->finish();

	delete cWindow;

}

