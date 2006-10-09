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
//  File				:	frame.h
//  Classes				:	CFrame
//  Description			:	This class holds global info about a frame
//
////////////////////////////////////////////////////////////////////////
#ifndef FRAME_H
#define FRAME_H

#include "common/global.h"
#include "common/containers.h"
#include "options.h"
#include "ray.h"
#include "dsply.h"

// Forward definitions
class CDisplayChannel;

// Compute the circle of confusion in the camera system
#define	cocPixels(z)	absf((1 / z) - invFocaldistance)*cocFactorPixels
#define	cocSamples(z)	absf((1 / z) - invFocaldistance)*cocFactorSamples
#define	cocScreen(z)	absf((1 / z) - invFocaldistance)*cocFactorScreen

const	unsigned	int	HIDER_RGBAZ_ONLY			=	1;	// The hider can only produce RGBAZ channels
const	unsigned	int	HIDER_NEEDS_RAYTRACING		=	2;	// The hider requires raytracing
const	unsigned	int	HIDER_BREAK					=	4;	// The hider should stop rendering
const	unsigned	int	HIDER_NODISPLAY				=	8;	// The hider is not actually generating display output
const	unsigned	int	HIDER_DONE					=	16;	// The image has been computed, so stop
const	unsigned	int	HIDER_ILLUMINATIONHOOK		=	32;	// The hider requires the illumination hooks
const	unsigned	int	HIDER_PHOTONMAP_OVERWRITE	=	64;	// Overwrite the photon maps
const	unsigned	int	HIDER_GEOMETRYHOOK			=	128;// The hider requires the geometry hooks

// The clipping codes used by the clipcode()
const	unsigned	int	CLIP_LEFT					=	1;
const	unsigned	int	CLIP_RIGHT					=	2;
const	unsigned	int	CLIP_TOP					=	4;
const	unsigned	int	CLIP_BOTTOM					=	8;
const	unsigned	int	CLIP_NEAR					=	16;
const	unsigned	int	CLIP_FAR					=	32;



///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Description			:	This class handles the output
// Comments				:	It is just an extended COptions class
// Date last edited		:	7/4/2001
class CFrame : public COptions {
public:
								// Frame functions
		void					beginFrame(const COptions *options,const CXform *xform,SOCKET client);
		void					endFrame();
		void					commit(int,int,int,int,float *);
		int						advanceBucket(int,int &,int &,int &,int &);		// Find the next bucket to render for network rendering
		int						inFrustrum(const float *,const float *);		// Return TRUE if the box is in the frustrum
		int						inFrustrum(const float *);						// Return TRUE if the point is in the frustrum
		unsigned int			clipCode(const float *);						// Returns the clipping code

								// Some inline functions defined below
		void					camera2pixels(float *P);
		void					camera2pixels(float *x,float *y,const float *P);
		void					camera2pixels(int n,float *P);
		void					camera2screen(int n,float *P);
		void					distance2pixels(int n,float *dist,float *P);
		void					pixels2camera(float *P,float x,float y,float z);
		float					minCocPixels(float z1, float z2);
		void					advanceBucket();

		static	CXform			*world;											// The world transform
		static	matrix			fromNDC,toNDC;									// Some misc matrices
		static	matrix			fromRaster,toRaster;
		static	matrix			fromScreen,toScreen;
		static	matrix			worldToNDC;										// World to NDC matrix
		static	unsigned int	hiderFlags;										// The hider flags

		static	int				numSamples;										// The actual number of samples to compute
		static	int				numExtraSamples;								// The number of actual samples
		static	int				xPixels,yPixels;								// The number of pixels to compute in X and Y
		static	unsigned int	additionalParameters;							// Any user specified parameters to be computed
		static	float			pixelLeft,pixelRight,pixelTop,pixelBottom;		// The rendering window on the screen plane
		static	float			dydPixel,dxdPixel;								// Stuff
		static	float			dPixeldx,dPixeldy;
		static	int				renderLeft,renderRight,renderTop,renderBottom;	// The actual rendering window in pixels
		static	int				xBuckets,yBuckets;								// The number of buckets
		static	int				metaXBuckets,metaYBuckets;						// The number of meta buckets in X and Y
		static	float			aperture;										// Aperture radius
		static	float			imagePlane;										// The z coordinate of the image plane
		static	float			invImagePlane;									// The reciprocal of that
		static	float			cocFactorPixels;								// The circle of concusion factor for the pixels
		static	float			cocFactorSamples;								// The circle of concusion factor for the samples
		static	float			cocFactorScreen;								// The circle of concusion factor for the screen
		static	float			invFocaldistance;								// 1 / focalDistance
		static	float			lengthA,lengthB;								// The depth to length conversion

		static	float			marginXcoverage,marginYcoverage;				// Coverage ratios for the pixel filter
		static	float			marginX,marginY;
		static	float			marginalX,marginalY;

		static	float			leftX,leftZ,leftD;								// The clipping plane equations
		static	float			rightX,rightZ,rightD;
		static	float			topY,topZ,topD;
		static	float			bottomY,bottomZ,bottomD;

		static	int				numActiveDisplays;								// The number of active displays

		static	int				currentXBucket;									// The bucket counters
		static	int				currentYBucket;

		static	SOCKET			netClient;										// The client socket if any

		static	int				*jobAssignment;									// The job assignment for the buckets

		static	FILE			*deepShadowFile;								// Deep shadow map stuff
		static	int				*deepShadowIndex;
		static	int				deepShadowIndexStart;							// The offset in the file for the indices
		static	char			*deepShadowFileName;

		static	void			clear(int,int,int,int);								// Clear a window
		static	void			dispatch(int,int,int,int,float *);					// Dispatch a window to out devices
		static	void			getDisplayName(char *,const char *,const char *);	// Retrieve the display name

		///////////////////////////////////////////////////////////////////////
		// Class				:	CDisplayData
		// Description			:	This class holds data about a display driver
		// Comments				:
		// Date last edited		:	7/4/2001
		class CDisplayData {
		public:
				void						*module;						// The module handle for the out device
				void						*handle;						// The handle for the out device
				int							numSamples;						// The number of samples
				CDisplayChannel				*channels;
				int							numChannels;
				
				char						*displayName;					// The computed display name
				TDisplayStartFunction		start;							// The start function for the out device
				TDisplayDataFunction		data;							// The data function
				TDisplayRawDataFunction		rawData;						// The raw data function
				TDisplayFinishFunction		finish;							// The finish function
				CDisplay					*display;
		};

		static	int				numDisplays;
		static	CDisplayData	*datas;
		static	int				*sampleOrder;		// variable entry, sample count pairs
		static	float			*sampleDefaults;	// default values for each channel
		static	int				numExtraChannels;	

		static	void			computeDisplayData();
};






/*


///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Method				:	camera2pixels
// Description			:	Project from camera space into the pixel space
// Return Value			:
// Comments				:	(inline for speed)
// Date last edited		:	7/4/2001
inline void		CFrame::camera2pixels(float *P) {
	if(projection == OPTIONS_PROJECTION_PERSPECTIVE) {
		P[COMP_X]	=	imagePlane*P[COMP_X]/P[COMP_Z];
		P[COMP_Y]	=	imagePlane*P[COMP_Y]/P[COMP_Z];
	}

	P[COMP_X]	=	(P[COMP_X] - pixelLeft)*dPixeldx;
	P[COMP_Y]	=	(P[COMP_Y] - pixelTop)*dPixeldy;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Method				:	camera2pixels
// Description			:	Project from camera space into the pixel space
// Return Value			:
// Comments				:	(inline for speed)
// Date last edited		:	7/4/2001
inline void		CFrame::camera2pixels(float *x,float *y,const float *P) {
	if(projection == OPTIONS_PROJECTION_PERSPECTIVE) {
		x[0]	=	imagePlane*P[COMP_X]/P[COMP_Z];
		y[0]	=	imagePlane*P[COMP_Y]/P[COMP_Z];
	} else {
		x[0]	=	P[COMP_X];
		y[0]	=	P[COMP_Y];
	}

	x[0]	=	(x[0] - pixelLeft)*dPixeldx;
	y[0]	=	(y[0] - pixelTop)*dPixeldy;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Method				:	camera2pixels
// Description			:	Project from camera space into the pixel space
// Return Value			:
// Comments				:	(inline for speed)
// Date last edited		:	7/4/2001
inline void		CFrame::camera2pixels(int n,float *P) {
	if(projection == OPTIONS_PROJECTION_PERSPECTIVE) {
		for (;n>0;n--,P+=3) {
			P[COMP_X]	=	(imagePlane*P[COMP_X]/P[COMP_Z] - pixelLeft)*dPixeldx;
			P[COMP_Y]	=	(imagePlane*P[COMP_Y]/P[COMP_Z] - pixelTop)*dPixeldy;
		}
	} else {
		for (;n>0;n--,P+=3) {
			P[COMP_X]	=	(P[COMP_X] - pixelLeft)*dPixeldx;
			P[COMP_Y]	=	(P[COMP_Y] - pixelTop)*dPixeldy;
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Method				:	camera2screen
// Description			:	Project from camera space into the screen space
// Return Value			:
// Comments				:	(inline for speed)
// Date last edited		:	7/4/2001
inline void		CFrame::camera2screen(int n,float *P) {
	if(projection == OPTIONS_PROJECTION_PERSPECTIVE) {
		for (;n>0;n--,P+=3) {
			P[COMP_X]	=	(imagePlane*P[COMP_X]/P[COMP_Z] - pixelLeft);
			P[COMP_Y]	=	(imagePlane*P[COMP_Y]/P[COMP_Z] - pixelTop);
		}
	} else {
		for (;n>0;n--,P+=3) {
			P[COMP_X]	=	(P[COMP_X] - pixelLeft);
			P[COMP_Y]	=	(P[COMP_Y] - pixelTop);
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Method				:	distance2pixels
// Description			:	Project a distance in camera space into a distance in the pixel space
// Return Value			:
// Comments				:	(inline for speed)
// Date last edited		:	7/4/2001
inline void		CFrame::distance2pixels(int n,float *dist,float *P) {
	if(projection == OPTIONS_PROJECTION_PERSPECTIVE) {
		for (;n>0;n--,P+=3) {
			*dist++		=	dPixeldx*imagePlane*dist[0]/P[COMP_Z];
		}
	} else {
		for (;n>0;n--,P+=3) {
			*dist++		=	dPixeldx*dist[0];
		}
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Method				:	pixels2distance
// Description			:	Convert from pixel distance to camera space distance
// Return Value			:	-
// Comments				:
// Date last edited		:	7/4/2001
void			CFrame::pixels2distance(float &a,float &b,float d) {
	a	=	lengthA*d;
	b	=	lengthB*d;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Method				:	samples2camera
// Description			:	Back project from sample space into the camera space
// Return Value			:
// Comments				:	(inline for speed)
// Date last edited		:	7/4/2001
inline void		CFrame::pixels2camera(float *P,float x,float y,float z) {
	x	=	x*dxdPixel + pixelLeft;
	y	=	y*dydPixel + pixelTop;

	if(projection == OPTIONS_PROJECTION_PERSPECTIVE) {
		P[COMP_X]	=	x*z*invImagePlane;
		P[COMP_Y]	=	y*z*invImagePlane;
		P[COMP_Z]	=	z;
	} else {
		P[COMP_X]	=	x;
		P[COMP_Y]	=	y;
		P[COMP_Z]	=	z;
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Method				:	minCocPixels
// Description			:	return the minimum circle of confusion
// Return Value			:
// Comments				:	(inline for speed, needed for CSurface::dice() )
// Date last edited		:	4/7/2006
inline float	CFrame::minCocPixels(float z1, float z2) {
	return min(cocPixels(z1),cocPixels(z2));
}


///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Method				:	advanceBucket
// Description			:	Advance the bucket
// Return Value			:	TRUE if we're still rendering, FALSE otherwise
// Comments				:
// Date last edited		:	7/4/2001
void			CFrame::advanceBucket() {
	currentXBucket++;
	if (currentXBucket == xBuckets) {		
		currentXBucket	=	0;
		currentYBucket++;
	}

	if ((currentXBucket == 0) && (currentYBucket == yBuckets)) {
		hiderFlags |=	HIDER_DONE | HIDER_BREAK;
	}
}



*/

#endif





