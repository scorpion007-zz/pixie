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
//  File				:	raytracer.cpp
//  Classes				:	CRaytracer
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "raytracer.h"
#include "renderer.h"
#include "shading.h"
#include "stats.h"
#include "random.h"
#include "memory.h"
#include "error.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CPrimaryBundle
// Method				:	CPrimaryBundle
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	3/20/2003
CPrimaryBundle::CPrimaryBundle(int mr,int numSamples,int nExtraChans,int *sampOrder,int numExtraSamp,float *sampDefaults) {
	int		i;
	float	*src;

	maxPrimaryRays	=	mr;
	numExtraChannels	=	0;		// These will be filled in after constuction if needed
	sampleOrder		=	NULL;
	rayBase			=	new CPrimaryRay[maxPrimaryRays];
	rays			=	new CRay*[maxPrimaryRays];
	last			=	0;
	depth			=	0;
	numRays			=	0;
	allSamples		=	new float[numSamples*maxPrimaryRays];

	src				=	allSamples;
	for (i=0;i<maxPrimaryRays;i++,src+=numSamples) {
		rayBase[i].samples	=	src;
	}
	
	numExtraChannels	=	nExtraChans;
	sampleOrder			=	sampOrder;
	numExtraSamples		=	numExtraSamp;
	sampleDefaults		=	sampDefaults;

}

///////////////////////////////////////////////////////////////////////
// Class				:	CPrimaryBundle
// Method				:	~CPrimaryBundle
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	3/20/2003
CPrimaryBundle::~CPrimaryBundle() {
	delete [] rayBase;
	delete [] rays;
	delete [] allSamples;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRaytracer
// Method				:	postTraceAction
// Description			:	Post trace action, force shading
// Return Value			:	-
// Comments				:
// Date last edited		:	3/20/2003
int		CPrimaryBundle::postTraceAction() {
	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRaytracer
// Method				:	postShade
// Description			:	Record the raytracing results
// Return Value			:	-
// Comments				:
// Date last edited		:	3/20/2003
void	CPrimaryBundle::postShade(int nr,CRay **r,float **varying)	{
	float		*Ci		=	varying[VARIABLE_CI];
	float		*Oi		=	varying[VARIABLE_OI];
	const int	*cOrder	=	sampleOrder;
	vector		t;
	int			i,j,l,k = 5;
	T32			one;
	T32			*opacity;

	one.real	=	(float) 1;

	if (depth == 0) {
		// First hit
		for (i=0;i<nr;i++,Ci+=3,Oi+=3) {
			CPrimaryRay	*cRay	=	(CPrimaryRay *) r[i];

			if (cRay->object->attributes->flags & ATTRIBUTES_FLAGS_MATTE) {
				initv(cRay->color,0);
				initv(cRay->opacity,0);
				cRay->ropacity[0]	=	1-Oi[0];
				cRay->ropacity[1]	=	1-Oi[1];
				cRay->ropacity[2]	=	1-Oi[2];
			}
			else {
				movvv(cRay->color,Ci);
				movvv(cRay->opacity,Oi);
				cRay->ropacity[0]	=	1-Oi[0];
				cRay->ropacity[1]	=	1-Oi[1];
				cRay->ropacity[2]	=	1-Oi[2];
			}

			opacity	=	(T32 *) Oi;
			if (	(opacity[0].integer ^ one.integer) |
					(opacity[1].integer ^ one.integer) |
					(opacity[2].integer ^ one.integer)) {
				rays[last++]	=	cRay;
			} else {
				movvv(cRay->samples,cRay->color);
			}

			cRay->samples[3]	=	(float) ((cRay->opacity[0] + cRay->opacity[1] + cRay->opacity[2])*0.333333333);
			cRay->samples[4]	=	cRay->t;
		}

		// Copy the extra samples
		for (i=0;i<numExtraChannels;i++) {
			const int 	outType			= *cOrder++;
			const int 	channelSamples	= *cOrder++;
			const float	*s				= varying[outType];
			float		*d;
					
			switch(channelSamples) {
			case 0:
				break;
			case 1:
				for (j=0;j<nr;j++) {
					d		=	((CPrimaryRay *) r[j])->samples + k;
					*d++	=	*s++;
				}
				k++;
				break;
			case 2:
				for (j=0;j<nr;j++) {
					d		=	((CPrimaryRay *) r[j])->samples + k;
					*d++	=	*s++;
					*d++	=	*s++;
				}
				k	+=	2;
				break;
			case 3:
				for (j=0;j<nr;j++) {
					d		=	((CPrimaryRay *) r[j])->samples + k;
					*d++	=	*s++;
					*d++	=	*s++;
					*d++	=	*s++;
				}
				k	+=	3;
				break;
			case 4:
				for (j=0;j<nr;j++) {
					d		=	((CPrimaryRay *) r[j])->samples + k;
					*d++	=	*s++;
					*d++	=	*s++;
					*d++	=	*s++;
					*d++	=	*s++;
				}
				k	+=	4;
				break;
			default:
				for (j=0;j<nr;j++) {
					d		=	((CPrimaryRay *) r[j])->samples + k;
					for (l=channelSamples;l>0;l--) {
						*d++	=	*s++;
					}
				}
				k	+=	channelSamples;
			}
		}
	} else {
		// Transparency hit
		for (i=0;i<nr;i++,Ci+=3,Oi+=3) {
			CPrimaryRay	*cRay		=	(CPrimaryRay *) r[i];

			opacity	=	(T32 *) Oi;

			const	int	transparent	=	(opacity[0].integer ^ one.integer) | (opacity[1].integer ^ one.integer) | (opacity[2].integer ^ one.integer);

			if (cRay->object->attributes->flags & ATTRIBUTES_FLAGS_MATTE) {
				cRay->ropacity[0]	*=	1-Oi[0];
				cRay->ropacity[1]	*=	1-Oi[1];
				cRay->ropacity[2]	*=	1-Oi[2];
			} else {
				movvv(t,Oi);
				mulvv(Ci,cRay->ropacity);
				mulvv(Oi,cRay->ropacity);
				
				addvv(cRay->color,Ci);
				addvv(cRay->opacity,Oi);
				cRay->ropacity[0]	*=	1-t[0];
				cRay->ropacity[1]	*=	1-t[1];
				cRay->ropacity[2]	*=	1-t[2];
			}

			if (transparent) {
				rays[last++]		=	cRay;
			} else {
				movvv(cRay->samples,cRay->color);
			}
			
			cRay->samples[3]	=	(float) ((cRay->opacity[0] + cRay->opacity[1] + cRay->opacity[2])*0.333333333);//1;
			
		}

		// The extra samples are copied from the closest intersection
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRaytracer
// Method				:	CRaytracer
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	8/26/2001
void	CPrimaryBundle::postShade(int nr,CRay **r) {
	int			i,j;

	if (depth == 0) {
		for (i=0;i<nr;i++) {
			CPrimaryRay	*cRay	=	(CPrimaryRay *) r[i];

			cRay->samples[0]	=	0;
			cRay->samples[1]	=	0;
			cRay->samples[2]	=	0;
			cRay->samples[3]	=	0;
			cRay->samples[4]	=	C_INFINITY;
		}
		
		// zero the extra samples
		if (numExtraSamples > 0) {
			for (j=0;j<nr;j++) {
				float		*d		=	((CPrimaryRay *) r[j])->samples + 5;
				const float *src	=	sampleDefaults;
				for (i=0;i<numExtraSamples;i++)
					*d++ = *src++;
			}
		}
	} else {
		for (i=0;i<nr;i++) {
			CPrimaryRay	*cRay	=	(CPrimaryRay *) r[i];

			movvv(cRay->samples,cRay->color);
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRaytracer
// Method				:	CRaytracer
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	8/26/2001
void	CPrimaryBundle::post() {
	numRays	=	last;
	last	=	0;
	depth++;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRaytracer
// Method				:	CRaytracer
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	8/26/2001
CRaytracer::CRaytracer(COptions *o,CXform *x,SOCKET s)	: CShadingContext(o,x,s,HIDER_NEEDS_RAYTRACING),
	primaryBundle(o->shootStep,numSamples,numExtraChannels,sampleOrder,numExtraSamples,sampleDefaults)  {
	
	const int		xoffset				=	(int) ceil((pixelFilterWidth	- 1) / (float) 2);
	const int		yoffset				=	(int) ceil((pixelFilterHeight	- 1) / (float) 2);
	const int		xpixels				=	bucketWidth + 2*xoffset;
	const int		ypixels				=	bucketHeight + 2*yoffset;
	
	fbContribution						=	new float[xpixels*ypixels];
	fbPixels							=	new float[xpixels*ypixels*numSamples];
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRaytracer
// Method				:	~CRaytracer
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	8/26/2001
CRaytracer::~CRaytracer() {
	delete [] fbContribution;
	delete [] fbPixels;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRaytracer
// Method				:	replace
// Description			:	Replace the occurance of a pointer with another
// Return Value			:	-
// Comments				:
// Date last edited		:	9/25/2001
void	CRaytracer::renderFrame() {
	int				left;
	int				top;
	int				width;
	int				height;
	int				numRenderedBuckets	=	0;
	const	char	*previousActivity	=	stats.activity;

	stats.activity	=	"Raytracer - rendering";

	memBegin();

	if (netClient != INVALID_SOCKET) {
		// Let the client know that we're starting to render
		T32		netBuffer;

		// Let the server know that we're ready
		netBuffer.integer	=	NET_READY;
		rcSend(netClient,(char *) &netBuffer,1*sizeof(T32));
	}

	// Do the job
	while(TRUE) {
		if (netClient != INVALID_SOCKET) {
			T32	netBuffer[3];

			// Receive the bucket to render from the client
			rcRecv(netClient,(char *) netBuffer,3*sizeof(T32));

			if (netBuffer[0].integer == NET_RENDER_BUCKET) {
				currentXBucket	=	netBuffer[1].integer;
				currentYBucket	=	netBuffer[2].integer;
			} else if (netBuffer[0].integer == NET_FINISH_FRAME) {
				// We have finished the frame, so terminate
				netBuffer[0].integer	=	NET_ACK;
				rcSend(netClient,(char *) netBuffer,1*sizeof(T32));
				
				// send end of frame channel data
				sendFrameDataChannels();
				
				break;
			} else {
				error(CODE_BUG,"Unrecognised network request\n");
				break;
			}
		} else {
			if (hiderFlags & HIDER_BREAK)	break;
		}

		left	=	currentXBucket*bucketWidth;
		top		=	currentYBucket*bucketHeight;
		width	=	min(bucketWidth,xPixels-left);
		height	=	min(bucketHeight,yPixels-top);

									// Sample the framebuffer
		sample(left,top,width,height);

									// Flush the data to the out devices
		commit(left,top,width,height,fbPixels);
		
		// Advance the current bucket
		if (netClient != INVALID_SOCKET) {
			// send end of bucket channel data
			sendBucketDataChannels(currentXBucket,currentYBucket);
		} else {
			// advance bucket after sending channel data
			numRenderedBuckets++;

			advanceBucket();
		}

		stats.progress	=	(numRenderedBuckets*100) / (float) (xBuckets*yBuckets);
		if (flags & OPTIONS_FLAGS_PROGRESS)	info(CODE_PROGRESS,"Done %%%3.2f\r",stats.progress);
	}

	memEnd();

	stats.progress	=	100;
	if (flags & OPTIONS_FLAGS_PROGRESS)	info(CODE_PROGRESS,"Done               \r");
	stats.activity	=	previousActivity;
}




///////////////////////////////////////////////////////////////////////
// Class				:	CRaytracer
// Method				:	sample
// Description			:	Samples a rectangular array of pixels
// Return Value			:	-
// Comments				:
// Date last edited		:	9/25/2001
void	CRaytracer::sample(int left,int top,int xpixels,int ypixels) {
	int				maxShading			=	primaryBundle.maxPrimaryRays;
	int				i,j;
	int				k;
	const int		xoffset				=	(int) ceil((pixelFilterWidth	- 1)*pixelXsamples / (float) 2);
	const int		yoffset				=	(int) ceil((pixelFilterHeight	- 1)*pixelYsamples / (float) 2);
	const int		xsamples			=	xpixels*pixelXsamples + 2*xoffset;
	const int		ysamples			=	ypixels*pixelYsamples + 2*yoffset;
	CPrimaryRay		*rays				=	primaryBundle.rayBase;
	CRay			**rayPointers		=	primaryBundle.rays;
	CPrimaryRay		*cRay;
	const float		invXsamples			=	1 / (float) pixelXsamples;
	const float		invYsamples			=	1 / (float) pixelYsamples;

	// Clear the framebuffer
	for (i=0;i<(xpixels*ypixels);i++) {
		fbContribution[i]	=	0;
		fbPixels[i]			=	0;
	}
	for (;i<(xpixels*ypixels*numSamples);i++) {
		fbPixels[i]			=	0;
	}

	// Generate the image
	{
		int		numShading	=	0;
		int		x,y;
		cRay				=	rays;
		
		for (j=0;j<ysamples;j+=8) {
			for (i=0;i<xsamples;i+=8) {
				const int	my	=	min(ysamples-j,8);
				const int	mx	=	min(xsamples-i,8);

				for (y=0;y<my;y++) {
					for (x=0;x<mx;x++) {
						cRay->x						=	(float) left + (float) (i+x-xoffset+jitter*(urand()-(float) 0.5) + (float) 0.5)*invXsamples;	// Center the sample location in the pixel
						cRay->y						=	(float) top  + (float) (j+y-yoffset+jitter*(urand()-(float) 0.5) + (float) 0.5)*invYsamples;

						rayPointers[numShading++]	=	cRay;
						cRay++;

						if (numShading >= maxShading) {
							computeSamples(rays,numShading);
							splatSamples(rays,numShading,left,top,xpixels,ypixels);
							cRay					=	rays;
							numShading				=	0;
						}
					}
				}
			}
		}

		// Shade the leftover samples
		if (numShading > 0) {
			computeSamples(rays,numShading);
			splatSamples(rays,numShading,left,top,xpixels,ypixels);
		}
	}

	// At this point, fb should contain the framebuffer, normalize the framebuffer
	for (i=0;i<xpixels*ypixels;i++) {
		const float	invContribution	=	1 / fbContribution[i];

		for (k=0;k<numSamples;k++) {
			fbPixels[i*numSamples+k]	*=	invContribution;
		}
	}
}



///////////////////////////////////////////////////////////////////////
// Class				:	CRaytracer
// Method				:	computeSamples
// Description			:	Raytrace the sample locations
// Return Value			:	-
// Comments				:
// Date last edited		:	9/25/2001
void	CRaytracer::computeSamples(CPrimaryRay *rays,int numShading) {
	int			i;
	float		x,y;
	CPrimaryRay	*cRay	=	rays;

	if (aperture == 0) {
		// No Depth of field effect

		for (i=numShading;i>0;i--,cRay++) {
			// First two numbers in the samples list are the x/y coordinates in pixels of the sample location
			const float	jtime		=	urand();
			vector		from,to;

			x					=	cRay->x;
			y					=	cRay->y;

			pixels2camera(from,x,y,0);
			pixels2camera(to,x,y,imagePlane);

			movvv(cRay->from,from);
			subvv(cRay->dir,to,from);
			normalizev(cRay->dir);

			cRay->time			=	jtime;
			cRay->jimp			=	-1.0f;
			cRay->t				=	C_INFINITY;
			cRay->flags			=	ATTRIBUTES_FLAGS_PRIMARY_VISIBLE;
			cRay->tmin			=	0;
		}
	} else {
		for (i=numShading;i>0;i--,cRay++) {
			// First two numbers in the samples list are the x/y coordinates in pixels of the sample location
			const float	jtime			=	urand();
			vector		from,to;
			const float	theta			=	(float) (urand()*2*C_PI);
			const float	r				=	urand()*aperture;

			x					=	cRay->x;
			y					=	cRay->y;

			pixels2camera(from,x,y,0);
			pixels2camera(to,x,y,focaldistance);

			from[COMP_X]	+=	cosf(theta) * r;
			from[COMP_Y]	+=	sinf(theta) * r;

			movvv(cRay->from,from);
			subvv(cRay->dir,to,from);
			normalizev(cRay->dir);

			cRay->time			=	jtime;
			cRay->jimp			=	-1.0f;
			cRay->t				=	C_INFINITY;
			cRay->flags			=	ATTRIBUTES_FLAGS_PRIMARY_VISIBLE;
			cRay->tmin			=	0;
		}
	}

	// Actually raytrace
	primaryBundle.numRays	=	numShading;
	primaryBundle.last		=	0;
	primaryBundle.depth		=	0;
	trace(&primaryBundle);

	stats.numShadingRays	+=	numShading;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRaytracer
// Method				:	splatSamples
// Description			:	Splat the samples on the image
// Return Value			:	-
// Comments				:
// Date last edited		:	9/25/2001
void	CRaytracer::splatSamples(CPrimaryRay *samples,int numShading,int left,int top,int xpixels,int ypixels) {
	int				i,j;
	const int		pw			=	(int) ceil((pixelFilterWidth-1) / (float) 2);
	const int		ph			=	(int) ceil((pixelFilterHeight-1) / (float) 2);

	for (i=0;i<numShading;i++,samples++) {
		const float	x			=	samples->x;
		const float	y			=	samples->y;
		float		*fbs		=	samples->samples;
		int			pixelX,pixelY;
		int			ix			=	(int) floor(x);
		int			iy			=	(int) floor(y);
		int			pl			=	ix - pw;
		int			pr			=	ix + pw;
		int			pt			=	iy - ph;
		int			pb			=	iy + ph;
		float		cx,cy;

		pl				=	max(pl,left);
		pt				=	max(pt,top);
		pr				=	min(pr,left + xpixels - 1);
		pb				=	min(pb,top + ypixels - 1);

		for (cy=pt + (float) 0.5 - y,pixelY=pt;pixelY<=pb;pixelY++,cy++) {
			for (cx=pl + (float) 0.5 - x,pixelX=pl;pixelX<=pr;pixelX++,cx++) {
				float	contribution					=	pixelFilter(cx,cy,pixelFilterWidth,pixelFilterHeight);

				if (fabs(cx) > marginX)	contribution	*=	marginXcoverage;
				if (fabs(cy) > marginY)	contribution	*=	marginYcoverage;

				float		*dest	=	&fbPixels[((pixelY-top)*xpixels+pixelX-left)*this->numSamples];
				const float	*src	=	fbs;

				assert((top+ypixels) > pixelY);
				assert((left+xpixels) > pixelX);

				// Save the contribution for later normalization
				fbContribution[((pixelY-top)*xpixels+pixelX-left)]	+=	contribution;

				for (j=this->numSamples;j>0;j--) {
					*dest++	+=	(*src++)*contribution;
				}
			}
		}
	}
}

