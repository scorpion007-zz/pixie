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
//  File				:	output.h
//  Classes				:	COutput
//  Description			:	The class that manages display drivers
//
////////////////////////////////////////////////////////////////////////
#ifndef OUTPUT_H
#define OUTPUT_H

#include "common/global.h"
#include "common/containers.h"
#include "options.h"
#include "ray.h"
#include "dsply.h"

// Forward definitions

class CDisplayChannel;

// Indices of several things in the vertex array

#define	RASTER_VERTEX_REFCOUNT	0
#define	RASTER_VERTEX_COC		1

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
// Class				:	COutput
// Description			:	This class handles the output
// Comments				:	It is just an extended COptions class
// Date last edited		:	7/4/2001
class COutput : public COptions {
public:
							COutput(COptions *,CXform *,SOCKET,unsigned int);
			virtual			~COutput();

			void			commit(int,int,int,int,float *);

			///////////////////////////////////////////////////////////////////////
			// Class				:	COutput
			// Method				:	camera2pixels
			// Description			:	Project from camera space into the pixel space
			// Return Value			:
			// Comments				:	(inline for speed)
			// Date last edited		:	7/4/2001
			inline void		camera2pixels(float *P) {
								if(projection == OPTIONS_PROJECTION_PERSPECTIVE) {
									P[COMP_X]	=	imagePlane*P[COMP_X]/P[COMP_Z];
									P[COMP_Y]	=	imagePlane*P[COMP_Y]/P[COMP_Z];
								}

								P[COMP_X]	=	(P[COMP_X] - pixelLeft)*dPixeldx;
								P[COMP_Y]	=	(P[COMP_Y] - pixelTop)*dPixeldy;
							}

			///////////////////////////////////////////////////////////////////////
			// Class				:	COutput
			// Method				:	camera2pixels
			// Description			:	Project from camera space into the pixel space
			// Return Value			:
			// Comments				:	(inline for speed)
			// Date last edited		:	7/4/2001
			inline void		camera2pixels(float *x,float *y,const float *P) {
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
			// Class				:	COutput
			// Method				:	camera2pixels
			// Description			:	Project from camera space into the pixel space
			// Return Value			:
			// Comments				:	(inline for speed)
			// Date last edited		:	7/4/2001
			inline void		camera2pixels(int n,float *P) {
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
			// Class				:	COutput
			// Method				:	camera2screen
			// Description			:	Project from camera space into the screen space
			// Return Value			:
			// Comments				:	(inline for speed)
			// Date last edited		:	7/4/2001
			inline void		camera2screen(int n,float *P) {
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
			// Class				:	COutput
			// Method				:	distance2pixels
			// Description			:	Project a distance in camera space into a distance in the pixel space
			// Return Value			:
			// Comments				:	(inline for speed)
			// Date last edited		:	7/4/2001
			inline void		distance2pixels(int n,float *dist,float *P) {
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
			// Class				:	COutput
			// Method				:	pixels2distance
			// Description			:	Convert from pixel distance to camera space distance
			// Return Value			:	-
			// Comments				:
			// Date last edited		:	7/4/2001
			void			pixels2distance(float &a,float &b,float d) {
								a	=	lengthA*d;
								b	=	lengthB*d;
							}

			///////////////////////////////////////////////////////////////////////
			// Class				:	COutput
			// Method				:	samples2camera
			// Description			:	Back project from sample space into the camera space
			// Return Value			:
			// Comments				:	(inline for speed)
			// Date last edited		:	7/4/2001
			inline void		pixels2camera(float *P,float x,float y,float z) {
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
			// Class				:	COutput
			// Method				:	minCocPixels
			// Description			:	return the minimum circle of confusion
			// Return Value			:
			// Comments				:	(inline for speed, needed for CSurface::dice() )
			// Date last edited		:	4/7/2006
			inline float	minCocPixels(float z1, float z2) {
								return min(cocPixels(z1),cocPixels(z2));
							}


			///////////////////////////////////////////////////////////////////////
			// Class				:	COutput
			// Method				:	advanceBucket
			// Description			:	Advance the bucket
			// Return Value			:	TRUE if we're still rendering, FALSE otherwise
			// Comments				:
			// Date last edited		:	7/4/2001
			void			advanceBucket() {
								currentXBucket++;
								if (currentXBucket == xBuckets) {		
									currentXBucket	=	0;
									currentYBucket++;
								}

								if ((currentXBucket == 0) && (currentYBucket == yBuckets)) {
									hiderFlags |=	HIDER_DONE | HIDER_BREAK;
								}
							}

			

			CXform			*world;											// The world transform
			matrix			fromNDC,toNDC;									// Some misc matrices
			matrix			fromRaster,toRaster;
			matrix			fromScreen,toScreen;
			matrix			worldToNDC;										// World to NDC matrix
			unsigned int	hiderFlags;										// The hider flags

			int				advanceBucket(int,int &,int &,int &,int &);		// Find the next bucket to render for network rendering
			int				inFrustrum(const float *,const float *);		// Return TRUE if the box is in the frustrum
			int				inFrustrum(const float *);						// Return TRUE if the point is in the frustrum
			unsigned int	clipCode(const float *);						// Returns the clipping code
protected:
			int				numSamples;										// The actual number of samples to compute
			int				numExtraSamples;								// The number of actual samples
			int				xPixels,yPixels;								// The number of pixels to compute in X and Y
			unsigned int	additionalParameters;							// Any user specified parameters to be computed
			float			pixelLeft,pixelRight,pixelTop,pixelBottom;		// The rendering window on the screen plane
			float			dydPixel,dxdPixel;								// Stuff
			float			dPixeldx,dPixeldy;
			int				renderLeft,renderRight,renderTop,renderBottom;	// The actual rendering window in pixels
			int				xBuckets,yBuckets;								// The number of buckets
			int				metaXBuckets,metaYBuckets;						// The number of meta buckets in X and Y
			float			aperture;										// Aperture radius
			float			imagePlane;										// The z coordinate of the image plane
			float			invImagePlane;									// The reciprocal of that
			float			cocFactorPixels;								// The circle of concusion factor for the pixels
			float			cocFactorSamples;								// The circle of concusion factor for the samples
			float			cocFactorScreen;								// The circle of concusion factor for the screen
			float			invFocaldistance;								// 1 / focalDistance
			float			lengthA,lengthB;								// The depth to length conversion

			float			marginXcoverage,marginYcoverage;				// Coverage ratios for the pixel filter
			float			marginX,marginY;
			float			marginalX,marginalY;

			float			leftX,leftZ,leftD;								// The clipping plane equations
			float			rightX,rightZ,rightD;
			float			topY,topZ,topD;
			float			bottomY,bottomZ,bottomD;

			int				numActiveDisplays;								// The number of active displays

			int				currentXBucket;									// The bucket counters
			int				currentYBucket;

			SOCKET			netClient;										// The client socket if any

			int				*jobAssignment;									// The job assignment for the buckets

			FILE			*deepShadowFile;								// Deep shadow map stuff
			int				*deepShadowIndex;
			int				deepShadowIndexStart;							// The offset in the file for the indices
			char			*deepShadowFileName;

			void			clear(int,int,int,int);								// Clear a window
			void			dispatch(int,int,int,int,float *);					// Dispatch a window to out devices
			void			getDisplayName(char *,const char *,const char *);	// Retrieve the display name

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

			int				numDisplays;
			CDisplayData	*datas;
			int				*sampleOrder;		// variable entry, sample count pairs
			float			*sampleDefaults;	// default values for each channel
			int				numExtraChannels;	

			void			computeDisplayData();
};

#endif





