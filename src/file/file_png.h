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
//  File				:	file_png.h
//  Classes				:
//  Description			:	This file implements the PNG writer output device
//
////////////////////////////////////////////////////////////////////////

#include "common/global.h"
#include "common/algebra.h"
#include "common/os.h"
#include "ri/dsply.h"							// The display driver interface

#include "png.h"
#include "file.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CFileFramebufferPNG
// Description			:	Holds the framebuffer
// Comments				:
class	CFileFramebufferPNG: public CFileFramebuffer {
public:
	CFileFramebufferPNG(const char *name,int width,int height,int numSamples,const char *samples,TDisplayParameterFunction findParameter);
	virtual ~CFileFramebufferPNG();	
	virtual void write(int x,int y,int w,int h,float *data);
	virtual bool success() { return !!fhandle; };
	
	unsigned char	**scanlines;
	int				*scanlineUsage;
	int				width,height;
	int				pixelSize;
	int				numSamples;
	int				lastSavedLine;
	TMutex			fileMutex;
	
	float			qmin,qmax,qone,qzero,qamp;
	float			gamma,gain;
	int				bitspersample,sampleformat;

	png_structp		png_ptr;
	png_infop		info_ptr;
	FILE			*fhandle;
};

