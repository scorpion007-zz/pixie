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
//  File				:	file_tiff.h
//  Classes				:
//  Description			:	This file implements the TIFF writer output device
//
////////////////////////////////////////////////////////////////////////

#include "common/global.h"
#include "common/algebra.h"
#include "common/os.h"
#include "ri/dsply.h"							// The display driver interface

#include <stdlib.h>								// Ensure we have NULL defined before libtiff
#include <tiffio.h>								// Libtiff is required

#include "file.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CFileFramebufferTIFF
// Description			:	Holds the framebuffer
// Comments				:
class	CFileFramebufferTIFF: public CFileFramebuffer {
public:
	CFileFramebufferTIFF(const char *name,int width,int height,int numSamples,const char *samples,TDisplayParameterFunction findParameter);
	virtual ~CFileFramebufferTIFF();	
	virtual void write(int x,int y,int w,int h,float *data);
	virtual bool success() { return !!image; };
	
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
	
	TIFF			*image;
};

