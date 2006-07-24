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
//  File				:	output.cpp
//  Classes				:	COutput
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include <string.h>
#include <math.h>

#include "output.h"
#include "renderer.h"
#include "stats.h"
#include "memory.h"
#include "error.h"

static	COutput				*currentOutput			=	NULL;
static	COptions::CDisplay	*currentDisplay			=	NULL;

///////////////////////////////////////////////////////////////////////
// Function				:	findParameter
// Description			:	This function can be used by the display server to probe for parameters
// Return Value			:	-
// Comments				:
// Date last edited		:	7/4/2001
void	*findParameter(const char *name,ParameterType type,int numItems) {
	if (currentDisplay != NULL) {
		int	i;

		for (i=0;i<currentDisplay->numParameters;i++) {
			if (strcmp(name,currentDisplay->parameters[i].name) == 0) {
				if (numItems == currentDisplay->parameters[i].numItems) {
					if (type == currentDisplay->parameters[i].type) {
						return	currentDisplay->parameters[i].data;
					}
				}
			}
		}
	}

	if (currentOutput != NULL) {
		if (strcmp(name,"quantize") == 0) {
			if ((numItems == 4) && (type == FLOAT_PARAMETER))	{
				if (currentDisplay->quantizer[0] == -1) {
					return	currentOutput->colorQuantizer;
				} else {
					return	currentDisplay->quantizer;
				}
			}
		} else if (strcmp(name,"dither") == 0) {
			if ((numItems == 1) && (type == FLOAT_PARAMETER)) {
				if (currentDisplay->quantizer[0] == -1) {
					return	currentOutput->colorQuantizer + 4;
				} else {
					return	currentDisplay->quantizer + 4;
				}
			}
		} else if (strcmp(name,"near") == 0) {
			if ((numItems == 1) && (type == FLOAT_PARAMETER))		return	&currentOutput->clipMin;
		} else if (strcmp(name,"far") == 0) {
			if ((numItems == 1) && (type == FLOAT_PARAMETER))		return	&currentOutput->clipMax;
		} else if (strcmp(name,"Nl") == 0) {
			if ((numItems == 16) && (type == FLOAT_PARAMETER))		return	&currentOutput->world->from;
		} else if (strcmp(name,"NP") == 0) {
			if ((numItems == 16) && (type == FLOAT_PARAMETER))		return	&currentOutput->worldToNDC;
		} else if (strcmp(name,"gamma") == 0) {
			if ((numItems == 1) && (type == FLOAT_PARAMETER))		return	&currentOutput->gamma;
		} else if (strcmp(name,"gain") == 0) {
			if ((numItems == 1) && (type == FLOAT_PARAMETER))		return	&currentOutput->gain;
		} else if (strcmp(name,"Software") == 0) {
			if ((numItems == 1) && (type == STRING_PARAMETER))		return	(void *) "Pixie";
		}
	}

	return	NULL;
}

///////////////////////////////////////////////////////////////////////
// Class				:	COutput
// Method				:	COutput
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	7/4/2001
COutput::COutput(COptions *options,CXform *x,SOCKET s,unsigned int hf) : COptions(options) {
	matrix	mtmp;

	currentOutput			=	this;

	hiderFlags				=	hf;
	netClient				=	s;

	assert(pixelXsamples > 0);
	assert(pixelYsamples > 0);

	// Compute some stuff
	if (flags & OPTIONS_FLAGS_CUSTOM_FRAMEAR) {
		const float	ar	=	xres*pixelAR / (float) yres;

		// Update the resolution as necessary
		if (frameAR > ar) {
			yres	=	(int) (xres*pixelAR / frameAR);
		} else {
			xres	=	(int) (frameAR * yres / pixelAR);
		}
	} else {
		frameAR = xres*pixelAR / (float) yres;
	}

	if (flags & OPTIONS_FLAGS_CUSTOM_SCREENWINDOW) {
		// The user explicitly entered the screen window, so we don't have to make sure it matches the frame aspect ratio
	} else {
		if (frameAR > (float) 1.0) {
			screenTop			=	(float) 1.0;
			screenBottom		=	(float) -1.0;
			screenLeft			=	-frameAR;
			screenRight			=	frameAR;
		} else {
			screenTop			=	1/frameAR;
			screenBottom		=	-1/frameAR;
			screenLeft			=	(float) -1.0;
			screenRight			=	(float) 1.0;
		}
	}

	imagePlane		=	1;
	if (projection == OPTIONS_PROJECTION_PERSPECTIVE) {
		imagePlane	=	(float) (1/tan(radians(fov/(float) 2)));
	} else {
		imagePlane	=	1;
	}

	invImagePlane	=	1/imagePlane;

	assert(cropLeft < cropRight);
	assert(cropTop < cropBottom);

	// Rendering window in pixels
	renderLeft			=	(int) ceil(xres*cropLeft);
	renderRight			=	(int) ceil(xres*cropRight);
	renderTop			=	(int) ceil(yres*cropTop);
	renderBottom		=	(int) ceil(yres*cropBottom);

	assert(renderRight > renderLeft);
	assert(renderBottom > renderTop);

	// The resolution of the actual render window
	xPixels				=	renderRight		-	renderLeft;
	yPixels				=	renderBottom	-	renderTop;

	assert(xPixels >= 0);
	assert(yPixels >= 0);

	dxdPixel			=	(screenRight	- screenLeft) / (float) (xres);
	dydPixel			=	(screenBottom	- screenTop) / (float) (yres);
	dPixeldx			=	1	/	dxdPixel;
	dPixeldy			=	1	/	dydPixel;
	pixelLeft			=	(float) (screenLeft	+ renderLeft*dxdPixel);
	pixelTop			=	(float) (screenTop	+ renderTop*dydPixel);
	pixelRight			=	pixelLeft	+ dxdPixel*xPixels;
	pixelBottom			=	pixelTop	+ dydPixel*yPixels;

	xBuckets			=	(int) ceil(xPixels / (float) bucketWidth);
	yBuckets			=	(int) ceil(yPixels / (float) bucketHeight);

	metaXBuckets		=	(int) ceil(xBuckets / (float) netXBuckets);
	metaYBuckets		=	(int) ceil(yBuckets / (float) netYBuckets);

	jobAssignment		=	NULL;

	aperture			=	focallength / (2*fstop);
	if ((aperture <= C_EPSILON) || (projection == OPTIONS_PROJECTION_ORTHOGRAPHIC)) {
		aperture			=	0;
		cocFactorScreen		=	0;
		cocFactorSamples	=	0;
		cocFactorPixels		=	0;
		invFocaldistance	=	0;
	} else {
		cocFactorScreen		=	(float) (imagePlane*aperture*focaldistance /  (focaldistance + aperture));
		cocFactorSamples	=	cocFactorScreen*sqrtf(dPixeldx*dPixeldx*pixelXsamples*pixelXsamples + dPixeldy*dPixeldy*pixelYsamples*pixelYsamples);
		cocFactorPixels		=	cocFactorScreen*sqrtf(dPixeldx*dPixeldx + dPixeldy*dPixeldy);
		invFocaldistance	=	1 / focaldistance;
	}

	if (projection == OPTIONS_PROJECTION_ORTHOGRAPHIC) {
		lengthA			=	0;
		lengthB			=	sqrtf(dxdPixel*dxdPixel + dydPixel*dydPixel);
	} else {
		lengthA			=	sqrtf(dxdPixel*dxdPixel + dydPixel*dydPixel) / imagePlane;
		lengthB			=	0;
	}

	if (aperture		!= 0)			flags	|=	OPTIONS_FLAGS_FOCALBLUR;
	if (shutterClose	!= shutterOpen)	flags	|=	OPTIONS_FLAGS_MOTIONBLUR;

	// Init the world matrix
	world				=	x;
	world->attach();

	// Compute the matrices related to the camera transformation
	if (projection == OPTIONS_PROJECTION_PERSPECTIVE) {
		toNDC[element(0,0)]		=	imagePlane / (screenRight - screenLeft);
		toNDC[element(0,1)]		=	0;
		toNDC[element(0,2)]		=	-screenLeft / (screenRight - screenLeft);
		toNDC[element(0,3)]		=	0;

		toNDC[element(1,0)]		=	0;
		toNDC[element(1,1)]		=	imagePlane / (screenBottom - screenTop);
		toNDC[element(1,2)]		=	-screenTop / (screenBottom - screenTop);
		toNDC[element(1,3)]		=	0;

		toNDC[element(2,0)]		=	0;
		toNDC[element(2,1)]		=	0;
		toNDC[element(2,2)]		=	1;
		toNDC[element(2,3)]		=	0;

		toNDC[element(3,0)]		=	0;
		toNDC[element(3,1)]		=	0;
		toNDC[element(3,2)]		=	1;
		toNDC[element(3,3)]		=	0;
	} else {
		toNDC[element(0,0)]		=	1 / (screenRight - screenLeft);
		toNDC[element(0,1)]		=	0;
		toNDC[element(0,2)]		=	0;
		toNDC[element(0,3)]		=	-screenLeft / (screenRight - screenLeft);

		toNDC[element(1,0)]		=	0;
		toNDC[element(1,1)]		=	1 / (screenBottom - screenTop);
		toNDC[element(1,2)]		=	0;
		toNDC[element(1,3)]		=	-screenTop / (screenBottom - screenTop);

		toNDC[element(2,0)]		=	0;
		toNDC[element(2,1)]		=	0;
		toNDC[element(2,2)]		=	1;
		toNDC[element(2,3)]		=	0;

		toNDC[element(3,0)]		=	0;
		toNDC[element(3,1)]		=	0;
		toNDC[element(3,2)]		=	0;
		toNDC[element(3,3)]		=	1;
	}

	// The inverse fromNDC is the same for both perspective and orthographic projections
	fromNDC[element(0,0)]	=	(screenRight - screenLeft);
	fromNDC[element(0,1)]	=	0;
	fromNDC[element(0,2)]	=	0;
	fromNDC[element(0,3)]	=	screenLeft;

	fromNDC[element(1,0)]	=	0;
	fromNDC[element(1,1)]	=	(screenBottom - screenTop);
	fromNDC[element(1,2)]	=	0;
	fromNDC[element(1,3)]	=	screenTop;

	fromNDC[element(1,0)]	=	0;
	fromNDC[element(1,1)]	=	0;
	fromNDC[element(1,2)]	=	0;
	fromNDC[element(1,3)]	=	imagePlane;

	fromNDC[element(3,0)]	=	0;
	fromNDC[element(3,1)]	=	0;
	fromNDC[element(3,2)]	=	0;
	fromNDC[element(3,3)]	=	1;


	// Compute the fromRaster / toRaster
	identitym(mtmp);
	mtmp[element(0,0)]		=	(float) xres;
	mtmp[element(1,1)]		=	(float) yres;
	mulmm(toRaster,mtmp,toNDC);

	identitym(mtmp);
	mtmp[element(0,0)]		=	1 / (float) xres;
	mtmp[element(1,1)]		=	1 / (float) yres;
	mulmm(fromRaster,fromNDC,mtmp);

	// Compute the world to NDC transform required by the shadow maps
	mulmm(worldToNDC,toNDC,world->from);

	const float	minX		=	min(pixelLeft,pixelRight);	// The extend of the rendering window on the image
	const float	maxX		=	max(pixelLeft,pixelRight);	// plane
	const float	minY		=	min(pixelTop,pixelBottom);
	const float	maxY		=	max(pixelTop,pixelBottom);

	// Compute the equations of the clipping planes
	// The visible points are:
	// Px*leftX		+ Pz*leftZ		+ leftD		>=	0	&&
	// Px*rightX	+ Pz*rightZ		+ rightD	>=	0	&&
	// Py*topY		+ Pz*topZ		+ topD		>=	0	&&
	// Py*bottomY	+ Pz*bottomZ	+ bottomD	>=	0	&&
	// Pz >= clipMin									&&
	// Pz <= clipMax
	if (projection == OPTIONS_PROJECTION_PERSPECTIVE) {
		leftX			=	imagePlane;
		leftZ			=	-minX;
		leftD			=	0;
		rightX			=	-imagePlane;
		rightZ			=	maxX;
		rightD			=	0;
		topY			=	imagePlane;
		topZ			=	-minY;
		topD			=	0;
		bottomY			=	-imagePlane;
		bottomZ			=	maxY;
		bottomD			=	0;
	} else {
		leftX			=	1;
		leftZ			=	0;
		leftD			=	-minX;
		rightX			=	-1;
		rightZ			=	0;
		rightD			=	maxX;

		topY			=	-1;
		topZ			=	0;
		topD			=	maxY;
		bottomY			=	1;
		bottomZ			=	0;
		bottomD			=	-minY;
	}

	if (displays == NULL) {
		displays				=	new CDisplay;
		displays->next			=	NULL;
		displays->outDevice		=	strdup(RI_FILE);
		displays->outName		=	strdup("ri.tif");
		displays->outSamples	=	strdup(RI_RGBA);
	}

	marginalX			=	pixelFilterWidth / 2;
	marginalY			=	pixelFilterHeight / 2;
	marginX				=	(float) floor(marginalX);
	marginY				=	(float) floor(marginalY);
	marginXcoverage		=	max(marginalX - marginX,0);
	marginYcoverage		=	max(marginalY -	marginY,0);

	currentXBucket		=	0;
	currentYBucket		=	0;

	numDisplays			=	0;
	numActiveDisplays	=	0;
	datas				=	NULL;

	deepShadowFile		=	NULL;
	deepShadowIndex		=	NULL;
	deepShadowIndexStart=	0;
	
	sampleOrder			=	NULL;
	sampleDefaults		=	NULL;

	if (netClient != INVALID_SOCKET) {
		numActiveDisplays		=	1;
	}

	if (!(hiderFlags & HIDER_NODISPLAY))
		computeDisplayData();
	else {
		numSamples		=	0;
		numExtraSamples	=	0;
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	COutput
// Method				:	~COutput
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	7/4/2001
COutput::~COutput() {
	int			i;

	// Delete the job queue
	if (jobAssignment	!= NULL)	delete [] jobAssignment;

	// Detach from the world transform
	world->detach();

	// Finish the out images
	for (i=0;i<numDisplays;i++) {
		if (datas[i].module != NULL) {
			datas[i].finish(datas[i].handle);
			if (strcmp(datas[i].display->outDevice,RI_SHADOW) == 0) {
				currentRenderer->RiMakeShadowV(datas[i].displayName,datas[i].displayName,0,NULL,NULL);
			}
		}
		if (datas[i].displayName != NULL) free(datas[i].displayName);
		delete[] datas[i].channels;
	}

	if (datas != NULL)			delete[] datas;
	if (sampleOrder != NULL)	delete[] sampleOrder;
	if (sampleDefaults != NULL)	delete[] sampleDefaults;
	
	if (deepShadowFile != NULL) {
		fseek(deepShadowFile,deepShadowIndexStart,SEEK_SET);
		fwrite(deepShadowIndex,sizeof(int),xBuckets*yBuckets*2,deepShadowFile);	// Override the deep shadow map index
		fclose(deepShadowFile);
	}

	if (deepShadowIndex != NULL) {
		delete [] deepShadowIndex;
		free(deepShadowFileName);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	COutput
// Method				:	advanceBucket
// Description			:	Advance the bucket for network parallel rendering
// Return Value			:	TRUE if we're still rendering, FALSE otherwise
// Comments				:
// Date last edited		:	7/4/2001
int				COutput::advanceBucket(int index,int &x,int &y,int &nx,int &ny) {

	nx = xBuckets;
	ny = yBuckets;
	
// Advance bucket indices
#define	advance(__x,__y)									\
		__x++;												\
		if (__x == xBuckets) {								\
			__x	=	0;										\
			__y++;											\
			if (__y == yBuckets)	{						\
				return FALSE;								\
			}												\
		}

// Find the server index assigned to this job
#define	bucket(__x,__y)		jobAssignment[__y*xBuckets + __x]

	if (jobAssignment == FALSE) {
		int	i;

		jobAssignment	=	new int[xBuckets*yBuckets];

		// Create the job assignment
		for (i=0;i<xBuckets*yBuckets;i++)	jobAssignment[i]	=	-1;

	}

	// Are we just starting ?
	if ((x == -1) || (y == -1)) {
		x	=	0;			// Begin from the start
		y	=	0;
	} else {
		advance(x,y);		// Advance the bucket by one
	}
	
	// Scan forward from (cx,cy) to find the first bucket to render
	while(TRUE) {

		// Has the bucket been assigned before ?
		if (bucket(x,y) == -1) {
			int	left	=	(x / netXBuckets)*netXBuckets;
			int	right	=	min((left + netXBuckets),xBuckets);
			int	top		=	(y / netYBuckets)*netYBuckets;
			int	bottom	=	min((top + netYBuckets),yBuckets);
			int	i,j;

			// The bucket is not assigned ...
			// Assign the meta block to this processor
			for (i=left;i<right;i++) {
				for (j=top;j<bottom;j++) {
					bucket(i,j)	=	index;
				}
			}

			assert(bucket(x,y) == index);

			// We found the job !!!
			return TRUE;
		} else if (bucket(x,y) != index) {

			// This bucket has been pre-allocated to another server, skip over
			advance(x,y);
		} else {

			// This bucket has been pre-allocated to us, proceed
			return TRUE;
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	COutput
// Method				:	dispatch
// Description			:	Dispatch a rendered window to the out devices
// Return Value			:	-
// Comments				:
// Date last edited		:	8/26/2001
void	COutput::dispatch(int left,int top,int width,int height,float *pixels) {
	float	*dest,*dispatch;
	int		i,j,k,l;
	int		srcStep,dstStep,disp;

	// Send the pixels to the output servers
	for (i=0;i<numDisplays;i++) {
		if (datas[i].module != NULL) {
			int				imageSamples	=	datas[i].numSamples;
			
			memBegin();
	
			dispatch	= (float *) ralloc(width*height*imageSamples*sizeof(float));
			
			for (j=0,disp=0;j<datas[i].numChannels;j++){
				const float		*tmp			=	&pixels[datas[i].channels[j].sampleStart];
				const int		channelSamples	=	datas[i].channels[j].numSamples;
				
				dest		=	dispatch + disp;
				srcStep		=	numSamples - channelSamples;
				dstStep		=	imageSamples - channelSamples;
				disp		+=	channelSamples;
	
				for (k=width*height;k>0;k--) {
					for (l=channelSamples;l>0;l--) {
						*dest++	=	*tmp++;				// GSHTODO: quantize here, not in driver
					}
					tmp		+=	srcStep;
					dest	+=	dstStep;
				}
			}

			if (datas[i].data(datas[i].handle,left,top,width,height,dispatch) == FALSE) {
				datas[i].handle	=	NULL;
				numActiveDisplays--;
				if (numActiveDisplays == 0)	hiderFlags	|=	HIDER_BREAK;
				osUnloadModule(datas[i].module);
				datas[i].module	=	NULL;
			}

			memEnd();
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	COutput
// Method				:	clear
// Description			:	Send a clear window to the out devices
// Return Value			:	-
// Comments				:
// Date last edited		:	8/26/2001
void	COutput::clear(int left,int top,int width,int height) {
	memBegin();

	float	* pixels	=	(float *) ralloc(width*height*numSamples*sizeof(float));
	int		i;

	for (i=0;i<width*height*numSamples;i++) {
		pixels[i]	=	0;
	}

	dispatch(left,top,width,height,pixels);

	memEnd();
}

///////////////////////////////////////////////////////////////////////
// Class				:	COutput
// Method				:	commit
// Description			:	Send a window of samples
// Return Value			:	-
// Comments				:
// Date last edited		:	8/26/2001
void	COutput::commit(int left,int top,int xpixels,int ypixels,float *pixels) {
	if (netClient != INVALID_SOCKET) {
		// We are rendering for a client, so just send the result to the waiting client
		T32	header[5];
		T32	a;

		header[0].integer	=	NET_READY;
		rcSend(netClient,(char *) header,	1*sizeof(T32));

		header[0].integer	=	left;
		header[1].integer	=	top;
		header[2].integer	=	xpixels;
		header[3].integer	=	ypixels;
		header[4].integer	=	xpixels*ypixels*numSamples;

		rcSend(netClient,(char *) header,	5*sizeof(T32));
		rcRecv(netClient,(char *) &a,		1*sizeof(T32));
		rcSend(netClient,(char *) pixels,xpixels*ypixels*numSamples*sizeof(T32));
		return;
	}

	if ((top == 0) && (left == 0)) {
		if (renderTop > 0)		clear(0,0,xres,renderTop);
	}

	if (left == 0) {
		if (renderLeft > 0)		clear(0,top+renderTop,renderLeft,ypixels);
	}

	if ((left+xpixels) == xPixels) {
		if (renderRight < xres)	clear(renderRight,top+renderTop,xres-renderRight,ypixels);
	}

	if (((top+ypixels) == yPixels) && ((left+xpixels) == xPixels)) {
		if (renderBottom < yres)	clear(0,renderBottom,xres,yres-renderBottom);
	}


	dispatch(left+renderLeft,top+renderTop,xpixels,ypixels,pixels);
}



///////////////////////////////////////////////////////////////////////
// Class				:	COutput
// Method				:	getDisplayName
// Description			:	Create the display name
// Return Value			:
// Comments				:
// Date last edited		:	7/4/2001
void	COutput::getDisplayName(char *out,const char *in,const char *displayType) {
	char		*cOut	=	out;
	const char	*cIn	=	in;

	while(*cIn != '\0') {
		if (*cIn == '#') {
			int		width		=	0;
			char	widthString[256];

			cIn++;

			while((*cIn >= '0') && (*cIn <= '9')) {
				widthString[width++]	=	*cIn++;
			}

			if (width > 0) {
				widthString[width]	=	'\0';
				sscanf(widthString,"%d",&width);
				sprintf(widthString,"%%0%dd",width);
			} else {
				sprintf(widthString,"%%d");
			}

			switch(*cIn++) {
			case 'f':
				sprintf(cOut,widthString,(int) frame);
				while(*cOut != '\0')	cOut++;
				break;
			case 's':
				sprintf(cOut,widthString,stats.sequenceNumber);
				while(*cOut != '\0')	cOut++;
				break;
			case 'n':
				sprintf(cOut,widthString,stats.runningSequenceNumber);
				while(*cOut != '\0')	cOut++;
				break;
			case 'h':
				char	hostName[1024];
				gethostname(hostName,1024);
				sprintf(cOut,hostName);
				while(*cOut != '\0')	cOut++;
				break;
			case 'd':
				strcpy(cOut,displayType);
				while(*cOut != '\0')	cOut++;
				break;
			case 'p':
				sprintf(cOut,"0");
				while(*cOut != '\0')	cOut++;
				break;
			case 'P':
				sprintf(cOut,"0");
				while(*cOut != '\0')	cOut++;
				break;
			case '#':
				sprintf(cOut,"#");
				while(*cOut != '\0')	cOut++;
				break;
			default:
				error(CODE_BADTOKEN,"Unknown display stub %c\n",*cIn);
				break;
			}
		} else {
			*cOut++	=	*cIn++;
		}
	}

	*cOut	=	'\0';
}




///////////////////////////////////////////////////////////////////////
// Class				:	COutput
// Method				:	computeDisplayData
// Description			:	Compute the display data
// Return Value			:
// Comments				:
// Date last edited		:	7/4/2001
void	COutput::computeDisplayData() {
	CDisplay		*cDisplay;
	CDisplayChannel *oChannel;
	char			displayName[OS_MAX_PATH_LENGTH];
	char			deviceFile[OS_MAX_PATH_LENGTH];
	char			*sampleDefinition,*sampleName,*nextComma,*tmp;
	int				i,j,k,s,t,isNewChannel;

	// mark all channels as unallocated
	currentRenderer->resetDisplayChannelUsage();
	
	for (i=0,cDisplay=displays;cDisplay!=NULL;i++,cDisplay=cDisplay->next);

	datas					=	new CDisplayData[i];
	j						=	0;
	numSamples				=	5;	// rgbaz
	numExtraSamples			=	0;
	numDisplays				=	0;
	numExtraChannels		=	0;
	additionalParameters	=	0;
	numActiveDisplays		=	0;
	deepShadowFile			=	NULL;
	deepShadowIndex			=	NULL;

	for (cDisplay=displays;cDisplay!=NULL;cDisplay=cDisplay->next) {
		datas[numDisplays].display		=	cDisplay;
		datas[numDisplays].displayName	=	NULL;
		datas[numDisplays].numChannels	=	0;
		datas[numDisplays].channels		=	NULL;
		datas[numDisplays].numSamples	=	0;
		
		int dspError					=	FALSE;
		int dspNumExtraChannels			=	0;
		int dspNumSamples				=	0;
		int dspNumExtraSamples			=	0;
		
		// work out how many channels to expect (at least one)
		int dspNumChannels = 1;
		sampleDefinition = cDisplay->outSamples;
		while ((sampleDefinition = strchr(sampleDefinition,',')) != NULL) {
			sampleDefinition++;
			dspNumChannels++;
		}
		datas[numDisplays].channels = new CDisplayChannel[dspNumChannels];
		
		// parse the channels / sample types
		sampleDefinition = strdup(cDisplay->outSamples); // duplicate to tokenize
		nextComma = sampleName = sampleDefinition;
		dspNumChannels = 0;
		do {
			// parse to next comma, remove spaces
			nextComma = strchr(sampleName,',');
			if (nextComma != NULL) {
				for (tmp=nextComma-1;isspace(*tmp)&&(tmp>sampleName);tmp--) *tmp = '\0';
				*nextComma++ = '\0';
				while (isspace(*nextComma)) nextComma++;
			}
			while (isspace(*sampleName)) sampleName++;
			
			// is the sample name a channel we know about?
			oChannel = currentRenderer->retrieveDisplayChannel(sampleName);
			if (oChannel != NULL) {
				// it's a predefined / already seen channel
			
				if (oChannel->variable != NULL) {
					// variable is NULL only for RGBAZ channels
					if (hiderFlags & HIDER_RGBAZ_ONLY) {
						error(CODE_BADTOKEN,"Hider %s can not handle display channels\n",hider);
						dspError = TRUE;
						break;
					}	
					
					// Make sure the variable is global
					if (oChannel->outType == -1) {
						currentRenderer->makeGlobalVariable(oChannel->variable);
						oChannel->outType = oChannel->variable->entry;
					}
				}
			} else {
				// it's an old-style AOV
				
				if (hiderFlags & HIDER_RGBAZ_ONLY) {
					error(CODE_BADTOKEN,"Hider %s can not handle arbitrary output variables\n",hider);
					dspError = TRUE;
					break;
				} else {				
					CVariable	*cVar		=	currentRenderer->retrieveVariable(sampleName);
					
					// if it's an inline declaration but it's not defined yet, declare it
					if (cVar == NULL) {
						cVar = currentRenderer->declareVariable(NULL,sampleName);
					}
	
					if (cVar != NULL) {
						// Make sure the variable is global
						if (cVar->storage != STORAGE_GLOBAL) {
							currentRenderer->makeGlobalVariable(cVar);
						} else if (cVar->storage == STORAGE_PARAMETER || cVar->storage == STORAGE_MUTABLEPARAMETER) {
							error(CODE_BADTOKEN,"Unable to find output variable or display channel \"%s\" (seems to be a parameter?)\n",sampleName);
							dspError = TRUE;
							break;
						}
					} else {
						error(CODE_BADTOKEN,"Unable to find output variable or display channel \"%s\"\n",sampleName);
						dspError = TRUE;
						break;
					}
										
					// now create a channel for the variable
					oChannel = currentRenderer->declareDisplayChannel(cVar);
					
					if (oChannel == NULL) {
						error(CODE_BADTOKEN,"variable \"%s\" clashes with a display channel\n",cVar->name);
						dspError = TRUE;
						break;
					}
				}
			}
			
			// record channel if it's new
			isNewChannel = FALSE;
			if (oChannel->sampleStart == -1) {
				// sampleStart is -1 only for channels not yet allocated
				oChannel->sampleStart		=	numSamples + dspNumSamples;
				dspNumSamples				+=	oChannel->numSamples;
				dspNumExtraSamples			+=	oChannel->numSamples;
				additionalParameters		|=	oChannel->variable->usageMarker;
				dspNumExtraChannels++;
				isNewChannel = TRUE;
			}
			memcpy(datas[numDisplays].channels + dspNumChannels,oChannel,sizeof(CDisplayChannel));
			if (oChannel->fill) {
				// ensure a deep copy
				datas[numDisplays].channels[dspNumChannels].fill = (float*) malloc(sizeof(float)*oChannel->numSamples);
				for(s=0;s<datas[numDisplays].channels[dspNumChannels].numSamples;s++)
					datas[numDisplays].channels[dspNumChannels].fill[s] = oChannel->fill[s];
			}
			if (isNewChannel == FALSE) {
				// mark this channel as a duplicate
				datas[numDisplays].channels[dspNumChannels].variable = NULL;
			}
			
			datas[numDisplays].numSamples		+= oChannel->numSamples;
			dspNumChannels++;
			
			sampleName = nextComma;
		} while((sampleName != NULL) && (*sampleName != '\0'));
		
		free(sampleDefinition);
		
		if (dspError) {
			error(CODE_BADTOKEN,"display \"%s\" disabled\n",cDisplay->outName);
			delete [] datas[numDisplays].channels;
			continue;
		}
		
		// Sum up if we successfully allocated display
		datas[numDisplays].numChannels	=	dspNumChannels;
		numSamples						+=	dspNumSamples;
		numExtraSamples					+=	dspNumExtraSamples;
		numExtraChannels				+=	dspNumExtraChannels;

		// finally deal with the display initialization
		getDisplayName(displayName,cDisplay->outName,cDisplay->outSamples);
		
		// save the computed display name
		datas[numDisplays].displayName = strdup(displayName);
		
		char * outDevice = cDisplay->outDevice;
		if (strcmp(outDevice,"shadow") == 0)	outDevice	= 	RI_FILE;
		if (strcmp(outDevice,"zfile") == 0)		outDevice	=	RI_FILE;
		if (strcmp(outDevice,"tiff") == 0)		outDevice	=	RI_FILE;
			
		if (strcmp(outDevice,"tsm") == 0) {
			int					j;
			CDeepShadowHeader	header;

			// The TSM is hardcoded
			datas[numDisplays].module	=	NULL;
			datas[numDisplays].handle	=	NULL;

			// Set up the file header
			header.xres		=	xres;
			header.yres		=	yres;
			header.xTiles	=	xBuckets;
			header.yTiles	=	yBuckets;
			header.tileSize	=	bucketWidth;
			for (header.tileShift=1;(1 << header.tileShift) < bucketWidth;header.tileShift++);
			movmm(header.toNDC,worldToNDC);

			// The sanity check
			if ((1 << header.tileShift) != bucketWidth) {
				error(CODE_LIMIT,"Bucket width must be a power of 2 for tsm (%d).\n",bucketWidth);
			} else {
				if (bucketWidth != bucketHeight) {
					error(CODE_LIMIT,"Bucket width and height must be same for tsm (%d,%d).\n",bucketWidth,bucketHeight);
				} else {
					if (strcmp(hider,"stochastic") != 0) {
						error(CODE_LIMIT,"Hider must be stochastic / hidden for tsm.\n");
					} else {
						if (deepShadowFile != NULL) {
							error(CODE_LIMIT,"There can only be one tsm output.\n");
						} else {
							if (netClient != INVALID_SOCKET) {
								char tempTsmName[OS_MAX_PATH_LENGTH];
								
								if (!osFileExists(temporaryPath)) {
									osCreateDir(temporaryPath);
								}
								
								// need read and write
								osTempname(temporaryPath,"rndr",tempTsmName);
								deepShadowFile		=	ropen(tempTsmName,"w+b",fileTransparencyShadow);
								
								// register temporary for deletion
								currentRenderer->registerFrameTemporary(tempTsmName,TRUE);
							} else {
								deepShadowFile		=	ropen(displayName,"wb",fileTransparencyShadow);
							}
	
							if (deepShadowFile != NULL) {
								numActiveDisplays++;
								flags						|=	OPTIONS_FLAGS_DEEP_SHADOW_RENDERING;
	
								deepShadowIndex				=	new int[xBuckets*yBuckets*2];
								deepShadowFileName			=	strdup(displayName);
								
								// Write the header
								fwrite(&header,sizeof(CDeepShadowHeader),1,deepShadowFile);
	
								// Save the index start
								deepShadowIndexStart	=	ftell(deepShadowFile);
	
								// Write the dummy index
								fwrite(deepShadowIndex,sizeof(int),xBuckets*yBuckets*2,deepShadowFile);
	
								// Parse the tsm parameters
								for (j=0;j<cDisplay->numParameters;j++) {
									if (strcmp(cDisplay->parameters[j].name,"threshold") == 0) {
										float	*val	=	(float *) cDisplay->parameters[j].data;
	
										tsmThreshold	=	val[0];
									}
								}
							}
						}
					}
				}
			}
		} else if (netClient == INVALID_SOCKET) {
			if (currentRenderer->locateFileEx(deviceFile,outDevice,osModuleExtension,displayPath)) {
				datas[numDisplays].module		=	osLoadModule(deviceFile);
				if (datas[numDisplays].module != NULL) {
					datas[numDisplays].start		=	(TDisplayStartFunction)		osResolve(datas[numDisplays].module,"displayStart");
					datas[numDisplays].data			=	(TDisplayDataFunction)		osResolve(datas[numDisplays].module,"displayData");
					datas[numDisplays].rawData		=	(TDisplayRawDataFunction)	osResolve(datas[numDisplays].module,"displayRawData");
					datas[numDisplays].finish		=	(TDisplayFinishFunction)	osResolve(datas[numDisplays].module,"displayFinish");

					if ((datas[numDisplays].start == NULL) || (datas[numDisplays].data == NULL) || (datas[numDisplays].finish == NULL)) {
						error(CODE_SYSTEM,"The module %s has missing implementation\n",deviceFile);
						osUnloadModule(datas[numDisplays].module);
						datas[numDisplays].module	=	NULL;
					} else {
						currentDisplay				=	cDisplay;
						datas[numDisplays].handle	=	datas[numDisplays].start(displayName,xres,yres,datas[numDisplays].numSamples,cDisplay->outSamples,findParameter);
							//GSHTODO: above sample names are now quite incorrect
						if (datas[numDisplays].handle != NULL) {
							numActiveDisplays++;
						} else {
							osUnloadModule(datas[numDisplays].module);
							datas[numDisplays].module	=	NULL;
						}
					}
				} else {
					datas[numDisplays].module		=	NULL;
					error(CODE_SYSTEM,"Unable to open out device \"%s\" (error: %s)\n",cDisplay->outDevice,osModuleError());
				}
			} else {
				datas[numDisplays].module		=	NULL;
				error(CODE_SYSTEM,"Unable to find out device \"%s\"\n",cDisplay->outDevice);
			}
		} else {
			datas[numDisplays].module	=	NULL;
			datas[numDisplays].handle	=	NULL;
		}

		numDisplays++;
	}
	
	// copy the sample and sampled defaults order for fast access
	sampleOrder		=	new int[numExtraChannels*2];
	sampleDefaults	=	new float[numExtraSamples];
	for (i=0,k=0,t=0;i<numDisplays;i++) {
		for (j=0;j<datas[i].numChannels;j++) {
			// skip standard channels
			if (datas[i].channels[j].outType == -1) continue;
			// skip duplicate channels
			if (datas[i].channels[j].variable == NULL) continue;
			
			if (datas[i].channels[j].fill) {
				for(s=0;s<datas[i].channels[j].numSamples;s++)
					sampleDefaults[t+s] = datas[i].channels[j].fill[s];
			} else {
				for(s=0;s<datas[i].channels[j].numSamples;s++) sampleDefaults[t+s] = 0;
			}
			t += datas[i].channels[j].numSamples;
			
			sampleOrder[k++] = datas[i].channels[j].outType;
			sampleOrder[k++] = datas[i].channels[j].numSamples;
		}
	}
	assert(k == 2*numExtraChannels);

	if (numActiveDisplays == 0) hiderFlags	|=	HIDER_BREAK;
}





///////////////////////////////////////////////////////////////////////
// Class				:	COutput
// Method				:	inFrustrum
// Description			:	Check if the given box is inside the viewing frustrum
// Return Value			:	-
// Comments				:
// Date last edited		:	5/10/2002
int			COutput::inFrustrum(const float *bmin,const float *bmax) {
	vector	corners[8];
	int		i;

	initv(corners[0],bmin[COMP_X],bmin[COMP_Y],bmin[COMP_Z]);
	initv(corners[1],bmin[COMP_X],bmax[COMP_Y],bmin[COMP_Z]);
	initv(corners[2],bmin[COMP_X],bmax[COMP_Y],bmax[COMP_Z]);
	initv(corners[3],bmin[COMP_X],bmin[COMP_Y],bmax[COMP_Z]);
	initv(corners[4],bmax[COMP_X],bmin[COMP_Y],bmin[COMP_Z]);
	initv(corners[5],bmax[COMP_X],bmax[COMP_Y],bmin[COMP_Z]);
	initv(corners[6],bmax[COMP_X],bmax[COMP_Y],bmax[COMP_Z]);
	initv(corners[7],bmax[COMP_X],bmin[COMP_Y],bmax[COMP_Z]);

	// Check against the left bounding plane
	for (i=0;i<8;i++) {
		const float	*corner	=	corners[i];

		if ((corner[COMP_X]*leftX + corner[COMP_Z]*leftZ + leftD) > 0) {
			break;
		}
	}

	if (i == 8)	return FALSE;


	// Check against the right bounding plane
	for (i=0;i<8;i++) {
		const float	*corner	=	corners[i];

		if ((corner[COMP_X]*rightX + corner[COMP_Z]*rightZ + rightD) > 0) {
			break;
		}
	}

	if (i == 8)	return	FALSE;

	// Check against the top bounding plane
	for (i=0;i<8;i++) {
		const float	*corner	=	corners[i];

		if ((corner[COMP_Y]*topY + corner[COMP_Z]*topZ + topD) > 0) {
			break;
		}
	}

	if (i == 8)	return	FALSE;


	// Check against the bottom bounding plane
	for (i=0;i<8;i++) {
		const float	*corner	=	corners[i];

		if ((corner[COMP_Y]*bottomY + corner[COMP_Z]*bottomZ + bottomD) > 0) {
			break;
		}
	}

	if (i == 8)	return	FALSE;

	return	TRUE;
}


///////////////////////////////////////////////////////////////////////
// Class				:	COutput
// Method				:	inFrustrum
// Description			:	Check if the given box is inside the viewing frustrum
// Return Value			:	-
// Comments				:
// Date last edited		:	5/10/2002
int			COutput::inFrustrum(const float *P) {

	if ((P[COMP_X]*leftX + P[COMP_Z]*leftZ + leftD) < 0) {
		return FALSE;
	}

	if ((P[COMP_X]*rightX + P[COMP_Z]*rightZ + rightD) < 0) {
		return FALSE;
	}

	if ((P[COMP_Y]*topY + P[COMP_Z]*topZ + topD) < 0) {
		return FALSE;
	}

	if ((P[COMP_Y]*bottomY + P[COMP_Z]*bottomZ + bottomD) < 0) {
		return FALSE;
	}

	return	TRUE;
}




///////////////////////////////////////////////////////////////////////
// Class				:	COutput
// Method				:	clipCode
// Description			:	Compute the clipping codes for a point
// Return Value			:	-
// Comments				:
// Date last edited		:	5/10/2002
unsigned int			COutput::clipCode(const float *P) {
	unsigned int	code	=	0;

	if ((P[COMP_X]*leftX + P[COMP_Z]*leftZ + leftD) < 0) {
		code	|=	CLIP_LEFT;
	}

	if ((P[COMP_X]*rightX + P[COMP_Z]*rightZ + rightD) < 0) {
		code	|=	CLIP_RIGHT;
	}

	if ((P[COMP_Y]*topY + P[COMP_Z]*topZ + topD) < 0) {
		code	|=	CLIP_TOP;
	}

	if ((P[COMP_Y]*bottomY + P[COMP_Z]*bottomZ + bottomD) < 0) {
		code	|=	CLIP_BOTTOM;
	}

	if (P[COMP_Z] < clipMin)	code	|=	CLIP_NEAR;

	if (P[COMP_Z] > clipMax)	code	|=	CLIP_FAR;

	return	code;
}









