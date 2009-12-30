//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright � 1999 - 2003, Okan Arikan
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
//  File				:	openexr.cpp
//  Classes				:
//  Description			:	This file implements the output device
//							that sends the image into an openEXR file
//
////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <ImfOutputFile.h> 
#include <ImfChannelList.h>
#include <ImfStringAttribute.h>
#include <ImfChromaticitiesAttribute.h>
#include <ImfStandardAttributes.h>
#include <ImfCompressionAttribute.h>

#include "common/global.h"
#include "common/algebra.h"
#include "common/os.h"
#include "ri/dsply.h"							// The display driver interface

using namespace Imf;
using namespace Imath;

///////////////////////////////////////////////////////////////////////
// Class				:	CRendererbuffer
// Description			:	Holds the framebuffer
// Comments				:
class	CExrFramebuffer {
public:
				///////////////////////////////////////////////////////////////////////
				// Class				:	CRendererbuffer
				// Method				:	CRendererbuffer
				// Description			:	Ctor
				// Return Value			:	-
				// Comments				:
				CExrFramebuffer(const char *name,int width,int height,int numSamples,const char *samples,TDisplayParameterFunction findParameter) {
					int			i;
					float		*tmp;
					char		*software;
					const char	*compression	=	NULL;

					Header header(width,height);
					
					// set the compression (must be before opening the file)
					compression	=	(char *) findParameter("compression",STRING_PARAMETER,1);
					
					// The default compression is none
					if (compression != NULL) {
						if (strcmp(compression,"RLE") == 0) {
							header.compression() = RLE_COMPRESSION;
						} else if (strcmp(compression,"ZIPS") == 0) {
							header.compression() = ZIPS_COMPRESSION;
						} else if (strcmp(compression,"ZIP") == 0) {
							header.compression() = ZIP_COMPRESSION;
						} else if (strcmp(compression,"PIZ") == 0) {
							header.compression() = PIZ_COMPRESSION;
						} else if (strcmp(compression,"PXR24") == 0) {
							header.compression() = PXR24_COMPRESSION;
						}
					}
					
					// Get the gamma params and quantization
					if ((tmp = (float *) findParameter("quantize",FLOAT_PARAMETER,4))) {
						// Needed to range-shift data even when writing as float/half
						qzero			=	tmp[0];
						qone			=	tmp[1];
						qmin			=	tmp[2];
						qmax			=	tmp[3];
					}
					
					if ((tmp = (float *) findParameter("dither",FLOAT_PARAMETER,1))) {
						qamp			=	tmp[0];
					}
					
					if ((tmp = (float *) findParameter("gamma",FLOAT_PARAMETER,1))) {
						gamma			=	tmp[0];
					}

					if ((tmp = (float *) findParameter("gain",FLOAT_PARAMETER,1))) {
						gain			=	tmp[0];
					}
					
					// Software attribute
					software	=	(char *) findParameter("Software",STRING_PARAMETER,1);
					if (software != NULL)	header.insert("Software",StringAttribute(software));

					// Add the channels
					const char *channelName = "R\0G\0B\0A\0Z\0";
					for (int curSample=0;curSample<numSamples;curSample++){
						header.channels().insert(channelName,Channel(HALF));
						channelName += 2;
					}
					
					addChromaticities(header,Chromaticities());
									
					// Open the image file
					file				=	new OutputFile(name,header);

					// If we could not open the file, there's nothing to do
					if (file == NULL)	return;
					
					// Create a framebuffer to save off our samples
					framebuffer			=	new FrameBuffer;

					// Compute the size of a pixel
					pixelSize			=	numSamples*sizeof(half);
					lastSavedLine		=	0;
					scanlines			=	new half*[height];
					scanlineUsage		=	new int[height];

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
				// Class				:	CExrFramebuffer
				// Method				:	~CExrFramebuffer
				// Description			:	Dtor
				// Return Value			:	-
				// Comments				:
				~CExrFramebuffer() {
					int	i;
					
					if (file != NULL){
						delete framebuffer;
						delete file;
						file = NULL;
					} else {
						return;
					}

					for (i=0;i<height;i++) {
						if (scanlines[i] != NULL)	delete [] scanlines[i];
					}


					delete [] scanlines;
					delete [] scanlineUsage;

					osDeleteMutex(fileMutex);					
				}

				///////////////////////////////////////////////////////////////////////
				// Class				:	CRendererbuffer
				// Method				:	write
				// Description			:	Swrite some data to the out file
				// Return Value			:	-
				// Comments				:
	void		write(int x,int y,int w,int h,float *data) {
					int				i,j;
					int				check		=	FALSE;
					int				numChannels	=	w*h*numSamples;

					if (file == NULL)	return;


					// Apply the gamma correction if applicable
					if ((gamma != 1) || (gain != 1)) {
						float	invGamma	=	1 / gamma;

						for (i=0;i<numChannels;i++) {
							data[i]	=	powf(gain*data[i],invGamma);
						}
					}

					// gold-standard quantizes unless you disable, is it really needed?
					// Apply the quantization if applicable
					if (qmax > 0) {
						for (i=0;i<numChannels;i++) {
							float	dither	=	qamp*(2*(rand() / (float) RAND_MAX)-1);
							data[i]			=	qzero + (qone - qzero)*data[i] + dither;
							if (data[i] < qmin)			data[i]	=	qmin;
							else if (data[i] > qmax)	data[i]	=	qmax;
						}
					}

					osLock(fileMutex);
					
					for (i=0;i<h;i++) {
						half	*scan;
						
						if (scanlines[i+y] == NULL) {
							scanlines[i+y]	=	scan	=	new half[width*numSamples];
						} else {
							scan			=	scanlines[i+y];
						}
						
						const float		*src	=	&data[i*w*numSamples];
						half			*dest	=	&scan[x*numSamples];
						for (j=0;j<w*numSamples;j++) {
							*dest++		=	half( *src++ );
						}
						
						scanlineUsage[i+y]	-=	w;
						if (scanlineUsage[i+y] <= 0)	check	=	TRUE;
					}
					
					if (check) {
						for (;lastSavedLine<height;lastSavedLine++) {
							if (scanlineUsage[lastSavedLine] == 0) {
								if (scanlines[lastSavedLine] != NULL) {
									const char *channelName = "R\0G\0B\0A\0Z\0";
									
									for (int curSample=0;curSample<numSamples;curSample++){
										framebuffer->insert (channelName,							// channel name
												Slice (HALF,                        				// channel type
												  (char *) (scanlines[lastSavedLine] + curSample),	// basePtr
												  pixelSize,										// xStride
												  0));												// yStride (0 as we're scan at a time)
										channelName += 2;
									}
									file->setFrameBuffer(*framebuffer);
									file->writePixels(1);
									
									delete [] scanlines[lastSavedLine];
									scanlines[lastSavedLine]	=	NULL;
								}
							} else {
								break;
							}
						}
					}

					osUnlock(fileMutex);					
				}

	half			**scanlines;
	int				*scanlineUsage;
	int				width,height;

	OutputFile		*file;
	FrameBuffer		*framebuffer;
	int				pixelSize;
	int				numSamples;
	int				lastSavedLine;
	TMutex			fileMutex;	
	
	float			gamma,gain;
	float			qmin,qmax,qone,qzero,qamp;
	int				bitspersample,sampleformat;
};

///////////////////////////////////////////////////////////////////////
// Function				:	displayStart
// Description			:	Begin receiving an image
// Return Value			:	The handle to the image on success, NULL othervise
// Comments				:
void	*displayStart(const char *name,int width,int height,int numSamples,const char *samples,TDisplayParameterFunction findParameter) {
	CExrFramebuffer	*fb	=	new CExrFramebuffer(name,width,height,numSamples,samples,findParameter);
	
	if (fb->file == NULL) {	// If we could not open the image, return NULL
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
	CExrFramebuffer	*fb	=	(CExrFramebuffer *) im;
	
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
	CExrFramebuffer	*fb	=	(CExrFramebuffer *) im;

	assert(fb != NULL);

	delete fb;
}

