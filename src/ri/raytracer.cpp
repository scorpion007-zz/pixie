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
//  File				:	raytracer.cpp
//  Classes				:	CRaytracer
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "raytracer.h"
#include "shading.h"
#include "random.h"
#include "memory.h"
#include "error.h"
#include "renderer.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CPrimaryBundle
// Method				:	CPrimaryBundle
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CPrimaryBundle::CPrimaryBundle(int mr,int numSamples,int nExtraChans,int *sampOrder,int numExtraSamp,float *sampDefaults) {
	maxPrimaryRays		=	mr;
	numExtraChannels	=	0;		// These will be filled in after constuction if needed
	sampleOrder			=	NULL;
	rayBase				=	new CPrimaryRay[maxPrimaryRays];
	rays				=	new CRay*[maxPrimaryRays];
	last				=	0;
	depth				=	0;
	numRays				=	0;
	allSamples			=	new float[numSamples*maxPrimaryRays];

	float	*src		=	allSamples;
	for (int i=0;i<maxPrimaryRays;i++,src+=numSamples) {
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
int		CPrimaryBundle::postTraceAction() {
	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRaytracer
// Method				:	postShade
// Description			:	Record the raytracing results
// Return Value			:	-
// Comments				:
void	CPrimaryBundle::postShade(int nr,CRay **r,float **varying)	{
	float		*Ci		=	varying[VARIABLE_CI];
	float		*Oi		=	varying[VARIABLE_OI];
	const int	*cOrder	=	sampleOrder;

	// FIXME: make this deal with comp and non comp channels properly
	if (depth == 0) {

		// First hit
		for (int i=0;i<nr;i++,Ci+=3,Oi+=3) {
			CPrimaryRay	*cRay	=	(CPrimaryRay *) r[i];

			// Is this a matte surface
			if (cRay->object->attributes->flags & ATTRIBUTES_FLAGS_MATTE) {
				initv(cRay->color,0);
				initv(cRay->opacity,0);
				cRay->ropacity[0]	=	1-Oi[0];
				cRay->ropacity[1]	=	1-Oi[1];
				cRay->ropacity[2]	=	1-Oi[2];
			} else {
				movvv(cRay->color,Ci);
				movvv(cRay->opacity,Oi);
				cRay->ropacity[0]	=	1-Oi[0];
				cRay->ropacity[1]	=	1-Oi[1];
				cRay->ropacity[2]	=	1-Oi[2];
			}

			 if ((Oi[0] < CRenderer::opacityThreshold[0]) ||
			 	 (Oi[1] < CRenderer::opacityThreshold[1]) ||
			 	 (Oi[2] < CRenderer::opacityThreshold[2])) {
				rays[last++]	=	cRay;
			} else {
				movvv(cRay->samples,cRay->color);
			}

			cRay->samples[3]	=	(float) ((cRay->opacity[0] + cRay->opacity[1] + cRay->opacity[2])*0.333333333);
			cRay->samples[4]	=	cRay->t;
		}

		// Copy the extra samples
		int	k = 5;
		for (int i=0;i<numExtraChannels;i++) {
			const int 	outType			= *cOrder++;
			const int 	channelSamples	= *cOrder++;
			const float	*s				= varying[outType];
			float		*d;
					
			switch(channelSamples) {
			case 0:
				break;
			case 1:
				for (int j=0;j<nr;j++) {
					d		=	((CPrimaryRay *) r[j])->samples + k;
					*d++	=	*s++;
				}
				k++;
				break;
			case 2:
				for (int j=0;j<nr;j++) {
					d		=	((CPrimaryRay *) r[j])->samples + k;
					*d++	=	*s++;
					*d++	=	*s++;
				}
				k	+=	2;
				break;
			case 3:
				for (int j=0;j<nr;j++) {
					d		=	((CPrimaryRay *) r[j])->samples + k;
					*d++	=	*s++;
					*d++	=	*s++;
					*d++	=	*s++;
				}
				k	+=	3;
				break;
			case 4:
				for (int j=0;j<nr;j++) {
					d		=	((CPrimaryRay *) r[j])->samples + k;
					*d++	=	*s++;
					*d++	=	*s++;
					*d++	=	*s++;
					*d++	=	*s++;
				}
				k	+=	4;
				break;
			default:
				for (int j=0;j<nr;j++) {
					d		=	((CPrimaryRay *) r[j])->samples + k;
					for (int l=channelSamples;l>0;l--) {
						*d++	=	*s++;
					}
				}
				k	+=	channelSamples;
			}
		}
	} else {
		// Transparency hit
		for (int i=0;i<nr;i++,Ci+=3,Oi+=3) {
			CPrimaryRay	*cRay		=	(CPrimaryRay *) r[i];

			const	int	transparent	= ( (Oi[0] < CRenderer::opacityThreshold[0]) ||
								 		(Oi[1] < CRenderer::opacityThreshold[1]) ||
								 		(Oi[2] < CRenderer::opacityThreshold[2]));

			if (cRay->object->attributes->flags & ATTRIBUTES_FLAGS_MATTE) {
				cRay->ropacity[0]	*=	1-Oi[0];
				cRay->ropacity[1]	*=	1-Oi[1];
				cRay->ropacity[2]	*=	1-Oi[2];
			} else {
				vector	t;
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
void	CPrimaryBundle::postShade(int nr,CRay **r) {
	if (depth == 0) {
		for (int i=0;i<nr;i++) {
			CPrimaryRay	*cRay	=	(CPrimaryRay *) r[i];

			cRay->samples[0]	=	0;
			cRay->samples[1]	=	0;
			cRay->samples[2]	=	0;
			cRay->samples[3]	=	0;
			cRay->samples[4]	=	C_INFINITY;
		}
		
		// zero the extra samples
		if (numExtraSamples > 0) {
			for (int j=0;j<nr;j++) {
				float		*d		=	((CPrimaryRay *) r[j])->samples + 5;
				const float *src	=	sampleDefaults;
				for (int i=0;i<numExtraSamples;i++)
					*d++ = *src++;
			}
		}
	} else {
		for (int i=0;i<nr;i++) {
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
CRaytracer::CRaytracer(int thread) : CShadingContext(thread), primaryBundle(CRenderer::shootStep,CRenderer::numSamples,CRenderer::numExtraChannels,CRenderer::sampleOrder,CRenderer::numExtraSamples,CRenderer::sampleDefaults)  {
	CRenderer::raytracingFlags	|=	ATTRIBUTES_FLAGS_PRIMARY_VISIBLE;

	const int		xoffset		=	(int) ceil((CRenderer::pixelFilterWidth		- 1)*0.5f);
	const int		yoffset		=	(int) ceil((CRenderer::pixelFilterHeight	- 1)*0.5f);
	const int		xpixels		=	CRenderer::bucketWidth + 2*xoffset;
	const int		ypixels		=	CRenderer::bucketHeight + 2*yoffset;
	
	fbContribution				=	new float[xpixels*ypixels];
	fbPixels					=	new float[xpixels*ypixels*CRenderer::numSamples];
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRaytracer
// Method				:	~CRaytracer
// Description			:	Dtor
// Return Value			:	-
// Comments				:
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
void	CRaytracer::renderingLoop() {
	int				left;
	int				top;
	int				width;
	int				height;
	CRenderer::CJob	job;

	memBegin(threadMemory);

	// While not done
	while(TRUE) {

		// Get the job from the renderer
		CRenderer::dispatchJob(thread,job);

		// Process the job
		if (job.type == CRenderer::CJob::TERMINATE) {

			// End the context
			break;
		} else if (job.type == CRenderer::CJob::BUCKET) {
			const int	x	=	job.xBucket;
			const int	y	=	job.yBucket;

			assert(x < CRenderer::xBuckets);
			assert(y < CRenderer::yBuckets);

			currentXBucket	=	x;
			currentYBucket	=	y;

			left			=	x*CRenderer::bucketWidth;
			top				=	y*CRenderer::bucketHeight;
			width			=	min(CRenderer::bucketWidth,CRenderer::xPixels-left);
			height			=	min(CRenderer::bucketHeight,CRenderer::yPixels-top);

			// Sample the framebuffer
			sample(left,top,width,height);

			// Flush the data to the out devices
			CRenderer::commit(left,top,width,height,fbPixels);
			
			// Send bucket data if we're a netrender
			if (CRenderer::netClient != INVALID_SOCKET) {
				CRenderer::sendBucketDataChannels(currentXBucket,currentYBucket);
			}

			currentXBucket++;
			if (currentXBucket == CRenderer::xBuckets) {
				currentXBucket	=	0;
				currentYBucket++;
			}

		} else {
			error(CODE_BUG,"Invalid job for the hider\n");
		}
	}

	memEnd(threadMemory);
}




///////////////////////////////////////////////////////////////////////
// Class				:	CRaytracer
// Method				:	sampleFi
// Description			:	Samples a rectangular array of pixels
// Return Value			:	-
// Comments				:
void	CRaytracer::sample(int left,int top,int xpixels,int ypixels) {
	int				maxShading			=	primaryBundle.maxPrimaryRays;
	int				i,j;
	const int		xsamples			=	xpixels*CRenderer::pixelXsamples + 2*CRenderer::xSampleOffset;
	const int		ysamples			=	ypixels*CRenderer::pixelYsamples + 2*CRenderer::ySampleOffset;
	CPrimaryRay		*rays				=	primaryBundle.rayBase;
	CRay			**rayPointers		=	primaryBundle.rays;
	CPrimaryRay		*cRay;
	const float		invXsamples			=	1 / (float) CRenderer::pixelXsamples;
	const float		invYsamples			=	1 / (float) CRenderer::pixelYsamples;

	// Clear the framebuffer
	for (i=0;i<(xpixels*ypixels);i++) {
		fbContribution[i]	=	0;
		fbPixels[i]			=	0;
	}
	for (;i<(xpixels*ypixels*CRenderer::numSamples);i++) {
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
						cRay->x						=	(float) left + (float) (i+x-CRenderer::xSampleOffset+CRenderer::jitter*(urand()-(float) 0.5) + (float) 0.5)*invXsamples;	// Center the sample location in the pixel
						cRay->y						=	(float) top  + (float) (j+y-CRenderer::ySampleOffset+CRenderer::jitter*(urand()-(float) 0.5) + (float) 0.5)*invYsamples;

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

		for (int k=0;k<CRenderer::numSamples;k++) {
			fbPixels[i*CRenderer::numSamples+k]	*=	invContribution;
		}
	}
}



///////////////////////////////////////////////////////////////////////
// Class				:	CRaytracer
// Method				:	computeSamples
// Description			:	Raytrace the sample locations
// Return Value			:	-
// Comments				:
void	CRaytracer::computeSamples(CPrimaryRay *rays,int numShading) {
	int			i;
	float		x,y;
	CPrimaryRay	*cRay	=	rays;

	if (CRenderer::aperture == 0) {
		// No Depth of field effect

		for (i=numShading;i>0;i--,cRay++) {
			// First two numbers in the samples list are the x/y coordinates in pixels of the sample location
			x					=	cRay->x;
			y					=	cRay->y;

			vector		from,to;
			pixels2camera(from,x,y,0);
			pixels2camera(to,x,y,CRenderer::imagePlane);

			movvv(cRay->from,from);
			subvv(cRay->dir,to,from);
			normalizev(cRay->dir);

			cRay->time			=	((CRenderer::flags & OPTIONS_FLAGS_SAMPLEMOTION) ? urand() : 0);
			cRay->t				=	C_INFINITY;
			cRay->flags			=	ATTRIBUTES_FLAGS_PRIMARY_VISIBLE;
			cRay->tmin			=	0;
		}
	} else {
		for (i=numShading;i>0;i--,cRay++) {
			// First two numbers in the samples list are the x/y coordinates in pixels of the sample location
			x					=	cRay->x;
			y					=	cRay->y;

			vector		from,to;
			pixels2camera(from,x,y,0);
			pixels2camera(to,x,y,CRenderer::focaldistance);

			const float	theta	=	(float) (urand()*2*C_PI);
			const float	r		=	urand()*CRenderer::aperture;
			from[COMP_X]		+=	cosf(theta) * r;
			from[COMP_Y]		+=	sinf(theta) * r;

			movvv(cRay->from,from);
			subvv(cRay->dir,to,from);
			normalizev(cRay->dir);

			cRay->time			=	((CRenderer::flags & OPTIONS_FLAGS_SAMPLEMOTION) ? urand() : 0);
			cRay->t				=	C_INFINITY;
			cRay->flags			=	ATTRIBUTES_FLAGS_PRIMARY_VISIBLE;
			cRay->tmin			=	0;
		}
	}

	// Setup the ray differentials
	if (CRenderer::projection == OPTIONS_PROJECTION_PERSPECTIVE) {
		const float	a	=	CRenderer::dxdPixel/CRenderer::imagePlane;

		cRay	=	rays;
		for (i=numShading;i>0;i--,cRay++) {
			cRay->db			=	0;
			cRay->da			=	a;
		}
	} else{
		const float	b	=	CRenderer::dxdPixel;

		cRay	=	rays;
		for (i=numShading;i>0;i--,cRay++) {
			cRay->da			=	0;
			cRay->db			=	b;
		}
	}

	// Actually raytrace
	primaryBundle.numRays	=	numShading;
	primaryBundle.last		=	0;
	primaryBundle.depth		=	0;
	trace(&primaryBundle);

	numRaytraceRays	+=	numShading;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRaytracer
// Method				:	splatSamples
// Description			:	Splat the samples on the image
// Return Value			:	-
// Comments				:
void	CRaytracer::splatSamples(CPrimaryRay *samples,int numShading,int left,int top,int xpixels,int ypixels) {
	const int		pw				=	(int) ceil((CRenderer::pixelFilterWidth-1)*0.5f);
	const int		ph				=	(int) ceil((CRenderer::pixelFilterHeight-1)*0.5f);
	const int		filterWidth		=	CRenderer::pixelXsamples + 2*CRenderer::xSampleOffset;
	const int		filterHeight	=	CRenderer::pixelYsamples + 2*CRenderer::ySampleOffset;

	// Process each sample
	for (int i=0;i<numShading;i++,samples++) {
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

		pl				=	max(pl,left);
		pt				=	max(pt,top);
		pr				=	min(pr,left + xpixels - 1);
		pb				=	min(pb,top + ypixels - 1);

		/*
		for (pixelY=pt;pixelY<=pb;pixelY++) {
			for (pixelX=pl;pixelX<=pr;pixelX++) {
				const int	px				=	(int) floor((x - (pixelX + 0.5f))*filterWidth) + filterWidth>>1;
				const int	py				=	(int) floor((y - (pixelY + 0.5f))*filterWidth) + filterHeight>>1;
				const float	contribution	=	CRenderer::pixelFilterKernel[py*filterWidth+px];
				float		*dest			=	&fbPixels[((pixelY-top)*xpixels+pixelX-left)*CRenderer::numSamples];
				const float	*src			=	fbs;

				assert((top+ypixels) > pixelY);
				assert((left+xpixels) > pixelX);

				for (int j=CRenderer::numSamples;j>0;j--) {
					*dest++	+=	(*src++)*contribution;
				}
			}
		}
		*/

		float	cx,cy;
		for (cy=pt + 0.5f - y,pixelY=pt;pixelY<=pb;pixelY++,cy++) {
			for (cx=pl + 0.5f - x,pixelX=pl;pixelX<=pr;pixelX++,cx++) {
				const float	contribution	=	CRenderer::pixelFilter(cx,cy,CRenderer::pixelFilterWidth,CRenderer::pixelFilterHeight);
				float		*dest			=	&fbPixels[((pixelY-top)*xpixels+pixelX-left)*CRenderer::numSamples];
				const float	*src			=	fbs;

				assert((top+ypixels) > pixelY);
				assert((left+xpixels) > pixelX);

				// Save the contribution for later normalization
				fbContribution[((pixelY-top)*xpixels+pixelX-left)]	+=	contribution;

				// Accumulate the pixel filter results
				for (int j=CRenderer::numSamples;j>0;j--) {
					*dest++	+=	(*src++)*contribution;
				}
			}
		}
	}
}

