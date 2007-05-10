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
//  File				:	stochastic.cpp
//  Classes				:	CStochastic
//  Description			:	implements the stochastic hider
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "stochastic.h"
#include "memory.h"
#include "random.h"

// This macro is used to allocate fragments
#define	newFragment(__a)	if (freeFragments == NULL)	{						\
								__a					=	new CFragment;			\
								if (CRenderer::numExtraSamples > 0) {							\
									__a->extraSamples = new float[CRenderer::numExtraSamples]; 	\
								}																\
							} else {											\
								__a					=	freeFragments;			\
								freeFragments		=	freeFragments->next;	\
							}													\
							numFragments++;

// And deallocate macro
#define	deleteFragment(__a)	__a->next				=	freeFragments;			\
							freeFragments			=	__a;					\
							numFragments--;


///////////////////////////////////////////////////////////////////////
// Class				:	CStochastic
// Method				:	CStochastic
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CStochastic::CStochastic(int thread) : CReyes(thread), COcclusionCuller(), apertureGenerator(CRenderer::frame) {
	int		i,j;
	float	*cExtraSample;
	CPixel	*cPixel;

	// The maximum width/height we should handle
	totalWidth		=	CRenderer::pixelXsamples*CRenderer::bucketWidth + 2*CRenderer::xSampleOffset;
	totalHeight		=	CRenderer::pixelYsamples*CRenderer::bucketHeight + 2*CRenderer::ySampleOffset;

	// Allocate the framebuffer for extra samples (checkpointed)
	if (CRenderer::numExtraSamples > 0)	extraSampleMemory	=	(float *) ralloc(totalWidth*totalHeight*CRenderer::numExtraSamples*sizeof(float),CRenderer::globalMemory);
	else								extraSampleMemory	=	NULL;

	// Allocate the pixels (checkpointed)
	cExtraSample	=	extraSampleMemory;
	fb				=	(CPixel **) ralloc(totalHeight*sizeof(CPixel *),CRenderer::globalMemory);
	for (i=0;i<totalHeight;i++) {
		cPixel		=	fb[i]		=	 (CPixel *) ralloc(totalWidth*sizeof(CPixel),CRenderer::globalMemory);

		for (j=totalHeight;j>0;j--,cPixel++,cExtraSample+=CRenderer::numExtraSamples) {
			cPixel->last.extraSamples	=	cExtraSample;
			cPixel->first.extraSamples	=	NULL;
		}
	}

	// Init the fragment buffer
	freeFragments	=	NULL;
	numFragments	=	0;

	// Initialize the occlusion culler
	initCuller(max(totalWidth,totalHeight), &maxDepth);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CStochastic
// Method				:	~CStochastic
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CStochastic::~CStochastic() {
	CFragment	*cFragment;

	// Ditch the extra fragments
	while((cFragment = freeFragments) != NULL) {
		freeFragments	=	cFragment->next;
		if (CRenderer::numExtraSamples > 0) {
			delete[] cFragment->extraSamples;
		}
		delete cFragment;
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CStochastic
// Method				:	rasterBegin
// Description			:	Begin drawing an image
// Return Value			:	-
// Comments				:
void		CStochastic::rasterBegin(int w,int h,int l,int t,int nullBucket) {
	int			i,j,k,pxi,pxj;
	float		zoldStart;
	CFragment	*cFragment;
	
	assert(numFragments == 0);

	switch(CRenderer::depthFilter) {
	case DEPTH_MIN:
		zoldStart	=	CRenderer::clipMax;
		break;
	case DEPTH_MAX:
		zoldStart	=	-CRenderer::clipMax;
		break;
	case DEPTH_AVG:
		zoldStart	=	0;
		break;
	case DEPTH_MID:
		zoldStart	=	CRenderer::clipMax;
		break;
	}

	// Set the digits
	width				=	w;
	height				=	h;
	left				=	l;
	top					=	t;
	sampleWidth			=	width*CRenderer::pixelXsamples + 2*CRenderer::xSampleOffset;
	sampleHeight		=	height*CRenderer::pixelYsamples + 2*CRenderer::ySampleOffset;
	right				=	left + sampleWidth;
	bottom				=	top + sampleHeight;

	// Early-out if we have no data
	if (!(CRenderer::flags & OPTIONS_FLAGS_DEEP_SHADOW_RENDERING) && nullBucket) return;

	assert(sampleWidth <= totalWidth);
	assert(sampleHeight <= totalHeight);

	// Init the occlusion culler to zero
	initToZero();
	for (i=0,pxi=CRenderer::pixelYsamples-CRenderer::ySampleOffset;i<sampleHeight;i++,pxi++) {
		CPixel	*pixel	=	fb[i];
		
		if (pxi >= CRenderer::pixelYsamples)	pxi = 0;
		
		for (j=0,pxj=CRenderer::pixelXsamples-CRenderer::xSampleOffset;j<sampleWidth;j++,pxj++,pixel++) {
			float	aperture[2];

			// The stratified sample
			pixel->jx					=	(CRenderer::jitter*(urand()-0.5f) + 0.5001011f);
			pixel->jy					=	(CRenderer::jitter*(urand()-0.5f) + 0.5001017f);

			// Time of the sample for motion blur
			if (pxj >= CRenderer::pixelXsamples)	pxj = 0;
			pixel->jt					=	( pxi*CRenderer::pixelXsamples + pxj + CRenderer::jitter*(urand()-0.5f) + 0.5001011f)/(float)(CRenderer::pixelXsamples*CRenderer::pixelYsamples);
			
			// Importance blend / jitter
			pixel->jimp					=	1.0f - ( pxj*CRenderer::pixelYsamples + pxi + CRenderer::jitter*(urand()-0.5f) + 0.5001011f)/(float)(CRenderer::pixelXsamples*CRenderer::pixelYsamples);

			if (CRenderer::flags & OPTIONS_FLAGS_FOCALBLUR) {

				// Aperture sample for depth of field
				while (TRUE) {
					apertureGenerator.get(aperture);
					aperture[0] 			= 2.0f*aperture[0] - 1.0f;
					aperture[1] 			= 2.0f*aperture[1] - 1.0f;
					if ((aperture[0]*aperture[0] + aperture[1]*aperture[1]) < 1.0f) break;
				}

				pixel->jdx					=	aperture[0];
				pixel->jdy					=	aperture[1];
			} else {
				pixel->jdx					=	0;
				pixel->jdy					=	0;
			}
			
			// Center location of the sample
			pixel->xcent				=	(j+pixel->jx) + left;
			pixel->ycent				=	(i+pixel->jy) + top;

			pixel->z					=	CRenderer::clipMax;
			pixel->zold					=	zoldStart;
			pixel->numSplats			=	0;
			pixel->node					=	getNode(j,i);
			pixel->node->zmax			=	CRenderer::clipMax;


			cFragment					=	&pixel->last;
			cFragment->z				=	CRenderer::clipMax;
			initv(cFragment->color,0);
			initv(cFragment->opacity,0);
			cFragment->next				=	NULL;
			cFragment->prev				=	&pixel->first;
			// The last sample's extra samples are genuine AOV data
			if (CRenderer::numExtraSamples > 0)
				memcpy(cFragment->extraSamples,CRenderer::sampleDefaults,sizeof(float)*CRenderer::numExtraSamples);


			cFragment					=	&pixel->first;
			cFragment->z				=	-C_INFINITY;
			initv(cFragment->color,0);
			initv(cFragment->opacity,0);
			cFragment->next				=	&pixel->last;
			cFragment->prev				=	NULL;
			// Note: The first fragment's extra samples are not used, and the pointer is NULL
			assert(cFragment->extraSamples == NULL);

			pixel->update				=	&pixel->first;
		}
	}

	resetHierarchy();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CStochastic
// Method				:	rasterDrawPrimitives
// Description			:	Draw bunch of primitives
// Return Value			:	-
// Comments				:
void		CStochastic::rasterDrawPrimitives(CRasterGrid *grid) {

// Instantiate the dispatch switch
#define DEFINE_STOCHASTIC_SWITCH
	#include "stochasticPrimitives.h"
#undef DEFINE_STOCHASTIC_SWITCH
}



// The following macros help various fragment operations
#define depthFilterIfZMin()
#define depthFilterElseZMin()

#define depthFilterIfZMax()		pixel->zold		=	max(pixel->zold,z);
#define depthFilterElseZMax()	else {	pixel->zold	=	max(pixel->zold,z);	}

#define depthFilterIfZAvg()		pixel->zold		+=	z; pixel->numSplats++;
#define depthFilterElseZAvg()	else {	pixel->zold	+=	z; pixel->numSplats++;	}

#define depthFilterIfZMid()		pixel->zold		=	pixel->z;
#define depthFilterElseZMid()	else {	pixel->zold	=	min(pixel->zold,z);	}


// This macro is used to insert a fragment into the linked list for a pixel
#define	findSample(__dest,__z) { 																	\
	CFragment *lSample	=	pixel->update;															\
	if (__z >= lSample->z)	{																		\
		CFragment		*cSample;																	\
		for (cSample=lSample->next;__z >= cSample->z;lSample=cSample,cSample=cSample->next);		\
		assert(__z >= lSample->z);																	\
		assert(__z <= cSample->z);																	\
		newFragment(__dest);																		\
		__dest->next	=	cSample;																\
		__dest->prev	=	lSample;																\
		cSample->prev	=	__dest;																	\
		lSample->next	=	__dest;																	\
	} else {																						\
		CFragment		*cSample;																	\
		for (cSample=lSample->prev;__z < cSample->z;lSample=cSample,cSample=cSample->prev);			\
		assert(__z >= cSample->z);																	\
		assert(__z <= lSample->z);																	\
		newFragment(__dest);																		\
		__dest->next	=	lSample;																\
		__dest->prev	=	cSample;																\
		cSample->next	=	__dest;																	\
		lSample->prev	=	__dest;																	\
	}																								\
	pixel->update	=	__dest;																		\
}


// This macro is called when an opaque fragment is inserted
#define updateOpaque() {																			\
	CFragment *cSample=pixel->last.prev;															\
	while(cSample->z > z) {																			\
		CFragment *nSample				=	cSample->prev;											\
		nSample->next		=	&pixel->last;														\
		pixel->last.prev	=	nSample;															\
		assert(cSample != &pixel->first);															\
		deleteFragment(cSample);																	\
		cSample				=	nSample;															\
	}																								\
	pixel->update			=	cSample;															\
}


#define DEFINE_STOCHASTIC_FUNCTIONS
#include "stochasticPrimitives.h"
#undef DEFINE_STOCHASTIC_FUNCTIONS

#undef depthFilterIfZMin
#undef depthFilterElseZMin
#undef depthFilterIfZMax
#undef depthFilterElseZMax
#undef depthFilterIfZAvg
#undef depthFilterElseZAvg
#undef depthFilterIfZMid
#undef depthFilterElseZMid
#undef findSample
#undef updateOpaque


///////////////////////////////////////////////////////////////////////
// Class				:	CStochastic
// Method				:	rasterEnd
// Description			:	Get the image from the screen
// Return Value			:	-
// Comments				:
void		CStochastic::rasterEnd(float *fb2,int noObjects) {
	int				i,y;
	int				sx,sy;
	const int		xres					=	width;
	const int		yres					=	height;
	const int		filterWidth				=	CRenderer::pixelXsamples + 2*CRenderer::xSampleOffset;
	const int		filterHeight			=	CRenderer::pixelYsamples + 2*CRenderer::ySampleOffset;
	const float		halfFilterWidth			=	(float) filterWidth*0.5f;
	const float		halfFilterHeight		=	(float) filterHeight*0.5f;
	float			*fbs;
	const int		pixelSize				=	8	+ CRenderer::numExtraSamples;	// alpha + depth + color + opacity + extra samples
	float			*tmp;
	const int		sampleLineDisplacement	=	CRenderer::pixelXsamples*pixelSize;

	// Deep shadow map computation
	if (CRenderer::flags & OPTIONS_FLAGS_DEEP_SHADOW_RENDERING)	deepShadowCompute();
	else if (noObjects) {
		// early-out if we have no data
		
		// initialize the default samples and also the extra samples using "sampleDefaults"
		for (tmp=fb2,i=xres*yres;i>0;i--) {
			*tmp++	=	0;					// r
			*tmp++	=	0;					// g
			*tmp++	=	0;					// b
			*tmp++	=	0;					// a
			*tmp++	=	C_INFINITY;			// z
			
			// default-fill extra samples
			if (CRenderer::numExtraSamples > 0) {
				memcpy(tmp,CRenderer::sampleDefaults,CRenderer::numExtraSamples*sizeof(float));
			
				tmp += CRenderer::numExtraSamples;
			}
		}

		
		return;
	}

	memBegin(threadMemory);

	// Allocate the framebuffer
	fbs				=	(float *) ralloc(totalWidth*totalHeight*pixelSize*sizeof(float),threadMemory);

	// Collapse the samples (transparency composite)
	
	const int numExtraNonCompChannels	=	CRenderer::numExtraNonCompChannels;
	const int numExtraCompChannels		=	CRenderer::numExtraCompChannels;
	
	// 0	=	alpha
	// 1	=	z;
	// 2-4	=	color
	// 5-7	=	opacity
	for (y=0;y<sampleHeight;y++) {
		CPixel	*cPixel		=	fb[y];
		float	*cFb		=	&fbs[y*totalWidth*pixelSize];
		vector	ropacity;

		for (i=sampleWidth;i>0;i--,cPixel++,cFb+=pixelSize) {
			CFragment	*cSample	=	cPixel->first.next;
			CFragment	*oSample;
			float		*C			=	&cFb[2];
			float		*O			=	&cFb[5];
			float		*ES			=	&cFb[8];
 			
			assert(cPixel->first.z == -C_INFINITY);

			// We re-use cPixel->first as a marker as to whether the pixel has any matte samples,
			// cPixel->last ise really used, but cPixel->first is not (it's always skipped in the composite),
			// so this is safe to do
			
			if (cPixel->first.opacity[0] >= 0 || cPixel->first.opacity[1] >= 0 || cPixel->first.opacity[2] >= 0) { 		// Pixel has no Matte
				// Get the base color and opacity
				movvv(C,cSample->color);
				movvv(O,cSample->opacity);
				ropacity[0]	=	1-O[0];
				ropacity[1]	=	1-O[1];
				ropacity[2]	=	1-O[2];
				
				// Copy default non-composited aovs
//FIXME: deal with the various filter mode options here
				const float *sampleExtra = cSample->extraSamples;
				for(int es = 0; es < numExtraNonCompChannels; es++) {
					const int sampleOffset	= CRenderer::nonCompChannelOrder[es*3];
					const int numSamples	= CRenderer::nonCompChannelOrder[es*3+1];
					float *ESD				= ES + sampleOffset;
					const float *ESS		= sampleExtra + sampleOffset;
					for(int ess=numSamples;ess>0;ess--) *ESD++ = *ESS++;
				}
				
				// If this sample has no valid samples, this will already be the sample defaults
				sampleExtra = cSample->extraSamples;
				for(int es = 0; es < numExtraCompChannels; es++) {
					const int sampleOffset = CRenderer::compChannelOrder[es*3];
					movvv(ES + sampleOffset,sampleExtra + sampleOffset);
				}
				
				oSample		=	cSample;
				cSample		=	cSample->next;
				for (;cSample!=NULL;) {
					deleteFragment(oSample);
					const float	*color		= cSample->color;
					const float *opacity	= cSample->opacity;
					sampleExtra				= cSample->extraSamples;

					// Composite
					C[0]		+=	ropacity[0]*color[0];
					C[1]		+=	ropacity[1]*color[1];
					C[2]		+=	ropacity[2]*color[2];
					O[0]		+=	ropacity[0]*opacity[0];
					O[1]		+=	ropacity[1]*opacity[1];
					O[2]		+=	ropacity[2]*opacity[2];
					
					for(int es = 0; es < numExtraCompChannels; es++) {
						const int sampleOffset = CRenderer::compChannelOrder[es*3];
						ES[sampleOffset + 0] += ropacity[0]*sampleExtra[sampleOffset + 0];
						ES[sampleOffset + 1] += ropacity[1]*sampleExtra[sampleOffset + 1];
						ES[sampleOffset + 2] += ropacity[2]*sampleExtra[sampleOffset + 2];
					}
					
					ropacity[0]	*=	1-opacity[0];
					ropacity[1]	*=	1-opacity[1];
					ropacity[2]	*=	1-opacity[2];
	
					oSample		=	cSample;
					cSample		=	cSample->next;
				}
			}
			else {
				// Get the base color and opacity
				if (cSample->opacity[0] < 0 || cSample->opacity[1] < 0 || cSample->opacity[2] < 0) {
					// Matte base sample
					initv(C,0);
					initv(O,0);
					ropacity[0]	=	1+cSample->opacity[0];
					ropacity[1]	=	1+cSample->opacity[1];
					ropacity[2]	=	1+cSample->opacity[2];
					
					// Copy default non-composited AOVs - default values unless ignoring matte
					const float *sampleExtra = cSample->extraSamples;
					for(int es = 0; es < numExtraNonCompChannels; es++) {
						const int sampleOffset	= CRenderer::nonCompChannelOrder[es*3];
						const int numSamples	= CRenderer::nonCompChannelOrder[es*3+1];
						const int matteMode		= CRenderer::compChannelOrder[es*3+2];
						if (matteMode) {
							float *ESD				= ES + sampleOffset;
							const float *ESS		= CRenderer::sampleDefaults + sampleOffset;
							for(int ess=numSamples;ess>0;ess--) *ESD++ = *ESS++;
						} else {
							float *ESD				= ES + sampleOffset;
							const float *ESS		= sampleExtra + sampleOffset;
							for(int ess=numSamples;ess>0;ess--) *ESD++ = *ESS++;
						}
					}

					// Composite AOVs with ignore matte flag
					sampleExtra = cSample->extraSamples;
					for(int es = 0; es < numExtraCompChannels; es++) {
						const int sampleOffset = CRenderer::compChannelOrder[es*3];
						const int matteMode = CRenderer::compChannelOrder[es*3+2];
						if (matteMode)		initv(ES + sampleOffset,0);
						else				movvv(ES + sampleOffset,sampleExtra + sampleOffset);
					}
				}
				else {
					// Non-matte base sample
					movvv(C,cSample->color);
					movvv(O,cSample->opacity);
					ropacity[0]	=	1-O[0];
					ropacity[1]	=	1-O[1];
					ropacity[2]	=	1-O[2];
					
					// Copy default non-composited AOVs
					const float *sampleExtra = cSample->extraSamples;
					for(int es = 0; es < CRenderer::numExtraNonCompChannels; es++) {
						const int sampleOffset	= CRenderer::nonCompChannelOrder[es*3];
						const int numSamples	= CRenderer::nonCompChannelOrder[es*3+1];
						float *ESD				= ES + sampleOffset;
						const float *ESS		= sampleExtra + sampleOffset;
						for(int ess=numSamples;ess>0;ess--) *ESD++ = *ESS++;
					}
					
					// Composite
					sampleExtra = cSample->extraSamples;
					for(int es = 0; es < numExtraCompChannels; es++) {
						const int sampleOffset = CRenderer::compChannelOrder[es*3];
						movvv(ES + sampleOffset,sampleExtra + sampleOffset);
					}
				}

				oSample		=	cSample;
				cSample		=	cSample->next;
				for (;cSample!=NULL;) {
					deleteFragment(oSample);
					const float	*color		= cSample->color;
					const float *opacity	= cSample->opacity;
	
					if (opacity[0] < 0 || opacity[1] < 0 || opacity[2] < 0) {
						// Composite Matte
						ropacity[0]	*=	1+opacity[0];
						ropacity[1]	*=	1+opacity[1];
						ropacity[2]	*=	1+opacity[2];
						
						// Composite AOVs with ignore matte flag
						const float *sampleExtra = cSample->extraSamples;
						for(int es = 0; es < numExtraCompChannels; es++) {
							const int sampleOffset = CRenderer::compChannelOrder[es*3];
							const int matteMode = CRenderer::compChannelOrder[es*3+2];

							if (!matteMode)		movvv(ES + sampleOffset,sampleExtra + sampleOffset);
						}
					}
					else {
						// Composite non-matte
						C[0]		+=	ropacity[0]*color[0];
						C[1]		+=	ropacity[1]*color[1];
						C[2]		+=	ropacity[2]*color[2];
						O[0]		+=	ropacity[0]*opacity[0];
						O[1]		+=	ropacity[1]*opacity[1];
						O[2]		+=	ropacity[2]*opacity[2];
						
						const float *sampleExtra = cSample->extraSamples;
						for(int es = 0; es < numExtraCompChannels; es++) {
							const int sampleOffset = CRenderer::compChannelOrder[es*3];
							const int matteMode = CRenderer::compChannelOrder[es*3+2];
							ES[sampleOffset + 0] += ropacity[0]*sampleExtra[sampleOffset + 0];
							ES[sampleOffset + 1] += ropacity[1]*sampleExtra[sampleOffset + 1];
							ES[sampleOffset + 2] += ropacity[2]*sampleExtra[sampleOffset + 2];
						}
						
						ropacity[0]	*=	1-opacity[0];
						ropacity[1]	*=	1-opacity[1];
						ropacity[2]	*=	1-opacity[2];
					}
					
					oSample		=	cSample;
					cSample		=	cSample->next;
				}
			}
			
			// Alpha is the average opacity
			// I know this is wrong but this is more useful
			cFb[0]			=	((O[0] + O[1] + O[2])*0.333333333f);
		}
	}

	// Find the depth component
	switch(CRenderer::depthFilter) {
	case DEPTH_MIN:
		for (y=0;y<sampleHeight;y++) {
			const CPixel	*cPixel		=	fb[y];
			float			*cFb		=	&fbs[y*totalWidth*pixelSize];

			for (i=sampleWidth;i>0;i--,cPixel++,cFb+=pixelSize) {
				if (cPixel->z == CRenderer::clipMax)	cFb[1]	=	C_INFINITY;
				else									cFb[1]	=	cPixel->z;
			}
		}

		break;
	case DEPTH_MAX:
		for (y=0;y<sampleHeight;y++) {
			const CPixel	*cPixel		=	fb[y];
			float			*cFb		=	&fbs[y*totalWidth*pixelSize];

			for (i=sampleWidth;i>0;i--,cPixel++,cFb+=pixelSize) {
				if (cPixel->z == CRenderer::clipMax)	cFb[1]	=	C_INFINITY;
				else									cFb[1]	=	cPixel->zold;
			}
		}

		break;
	case DEPTH_AVG:
		for (y=0;y<sampleHeight;y++) {
			const CPixel	*cPixel		=	fb[y];
			float			*cFb		=	&fbs[y*totalWidth*pixelSize];

			for (i=sampleWidth;i>0;i--,cPixel++,cFb+=pixelSize) {
				if (cPixel->z == CRenderer::clipMax)	cFb[1]	=	C_INFINITY;
				else									cFb[1]	=	cPixel->zold / (float) cPixel->numSplats;
			}
		}

		break;
	case DEPTH_MID:
		for (y=0;y<sampleHeight;y++) {
			const CPixel	*cPixel		=	fb[y];
			float			*cFb		=	&fbs[y*totalWidth*pixelSize];

			for (i=sampleWidth;i>0;i--,cPixel++,cFb+=pixelSize) {
				if (cPixel->z == CRenderer::clipMax)	cFb[1]	=	C_INFINITY;
				else {

					assert(cPixel->z < CRenderer::clipMax);
					assert(cPixel->zold <= CRenderer::clipMax);
					assert(cPixel->z <= cPixel->zold);

					if (cPixel->zold < culledDepth)	cFb[1]		=	(cPixel->z + cPixel->zold) * 0.5f;
					else							cFb[1]		=	(cPixel->z + culledDepth) * 0.5f;
				}
			}
		}

		break;
	}

	// Clear the memory first
	for (tmp=fb2,i=xres*yres*CRenderer::numSamples;i>0;i--)	*tmp++	=	0;

	// Filter the samples
	for (y=0;y<yres;y++) {
		for (sy=0;sy<filterHeight;sy++) {
			for (sx=0;sx<filterWidth;sx++) {
				const CPixel	*pixels			=	&fb[y*CRenderer::pixelYsamples+sy][sx];
				float			*pixelLine		=	&fb2[y*xres*CRenderer::numSamples];
				const float		*sampleLine		=	&fbs[((y*CRenderer::pixelYsamples+sy)*totalWidth + sx)*pixelSize];
				const float		xOffset			=	sx - halfFilterWidth;
				const float		yOffset			=	sy - halfFilterHeight;
				const float		filterResponse	=	CRenderer::pixelFilterKernel[sy*filterWidth + sx];

				for (i=0;i<xres;i++) {
					int			es;

					pixelLine[0]				+=	filterResponse*sampleLine[2];
					pixelLine[1]				+=	filterResponse*sampleLine[3];
					pixelLine[2]				+=	filterResponse*sampleLine[4];
					pixelLine[3]				+=	filterResponse*sampleLine[0];
					pixelLine[4]				+=	filterResponse*sampleLine[1];

					// Filter the extra samples here
					for (es=0;es<CRenderer::numExtraSamples;es++) {
						pixelLine[5+es]			+=	filterResponse*sampleLine[8+es];
					}

					// Advance
					pixelLine					+=	CRenderer::numSamples;
					sampleLine					+=	sampleLineDisplacement;
					pixels						+=	CRenderer::pixelXsamples;
				}
			}
		}
	}

	memEnd(threadMemory);
}


// A transient data structure to hold TSM data
class	CTSMData {
public:
	float	origin[4];
	float	lastZ;
	float	rSlopeMin;
	float	gSlopeMin;
	float	bSlopeMin;
	float	rSlopeMax;
	float	gSlopeMax;
	float	bSlopeMax;
	FILE	*deepShadowFile;
	float	tsmThreshold;
};

///////////////////////////////////////////////////////////////////////
// Function				:	outSample
// Description			:	This function is used to output a depth sample
// Return Value			:	-
// Comments				:
inline	void	startSample(FILE *outFile,float threshold,CTSMData &data) {
	data.deepShadowFile		=	outFile;
	data.tsmThreshold		=	threshold;

	data.rSlopeMax		=	C_INFINITY;
	data.gSlopeMax		=	C_INFINITY;
	data.bSlopeMax		=	C_INFINITY;
	data.rSlopeMin		=	-C_INFINITY;
	data.gSlopeMin		=	-C_INFINITY;
	data.bSlopeMin		=	-C_INFINITY;

	// Output the first sample (at z=-C_INFINITY)
	data.origin[0]		=	-C_INFINITY;
	data.origin[1]		=	1;
	data.origin[2]		=	1;
	data.origin[3]		=	1;
	fwrite(data.origin,sizeof(float),4,data.deepShadowFile);
	data.lastZ			=	-C_INFINITY;
}

///////////////////////////////////////////////////////////////////////
// Function				:	outSample
// Description			:	This function is used to output a depth sample
// Return Value			:	-
// Comments				:
inline	void	outSample(float cZ,const float *opacity,CTSMData &data) {
	// Always output the closest sample
	if (data.origin[0] == -C_INFINITY) {
		data.origin[0]	=	cZ;
		data.origin[1]	=	opacity[0];
		data.origin[2]	=	opacity[1];
		data.origin[3]	=	opacity[2];

		fwrite(data.origin,sizeof(float),4,data.deepShadowFile);
	} else if (cZ == data.origin[0]) {	// Do we have a step ?
		const float	dr	=	absf(data.origin[1] - opacity[0]);							
		const float	dg	=	absf(data.origin[2] - opacity[1]);
		const float	db	=	absf(data.origin[3] - opacity[2]);

		// Is the step small enough ?
		if ((dr >= data.tsmThreshold) || (dg >= data.tsmThreshold) || (db >= data.tsmThreshold)) {

			// No, output the step
			data.origin[1]	=	opacity[0];
			data.origin[2]	=	opacity[1];
			data.origin[3]	=	opacity[2];
			fwrite(data.origin,sizeof(float),4,data.deepShadowFile);
		}
	} else {
		// Check for the window of validity
		const float	denom		=	1 / (cZ - data.origin[0]);
		float		crSlopeMax	=	(opacity[0] - data.origin[1] + data.tsmThreshold) * denom;
		float		cgSlopeMax	=	(opacity[1] - data.origin[2] + data.tsmThreshold) * denom;
		float		cbSlopeMax	=	(opacity[2] - data.origin[3] + data.tsmThreshold) * denom;
		float		crSlopeMin	=	(opacity[0] - data.origin[1] - data.tsmThreshold) * denom;
		float		cgSlopeMin	=	(opacity[1] - data.origin[2] - data.tsmThreshold) * denom;
		float		cbSlopeMin	=	(opacity[2] - data.origin[3] - data.tsmThreshold) * denom;

		crSlopeMax				=	min(crSlopeMax,data.rSlopeMax);
		cgSlopeMax				=	min(cgSlopeMax,data.gSlopeMax);
		cbSlopeMax				=	min(cbSlopeMax,data.bSlopeMax);

		crSlopeMin				=	max(crSlopeMin,data.rSlopeMin);
		cgSlopeMin				=	max(cgSlopeMin,data.gSlopeMin);
		cbSlopeMin				=	max(cbSlopeMin,data.bSlopeMin);

		if ((crSlopeMin < crSlopeMax) && (cgSlopeMin < cgSlopeMax) && (cbSlopeMin < cbSlopeMax)) {			
			// We're in range
			data.rSlopeMax		=	crSlopeMax;
			data.gSlopeMax		=	cgSlopeMax;
			data.bSlopeMax		=	cbSlopeMax;

			data.rSlopeMin		=	crSlopeMin;
			data.gSlopeMin		=	cgSlopeMin;
			data.bSlopeMin		=	cbSlopeMin;
		} else {
			data.origin[1]		+=	(data.rSlopeMin + data.rSlopeMax)*(data.lastZ - data.origin[0])*0.5f;
			data.origin[2]		+=	(data.gSlopeMin + data.gSlopeMax)*(data.lastZ - data.origin[0])*0.5f;
			data.origin[3]		+=	(data.bSlopeMin + data.bSlopeMax)*(data.lastZ - data.origin[0])*0.5f;
			data.origin[0]		=	data.lastZ;
			fwrite(data.origin,sizeof(float),4,data.deepShadowFile);

			data.rSlopeMax		=	C_INFINITY;
			data.gSlopeMax		=	C_INFINITY;
			data.bSlopeMax		=	C_INFINITY;
			data.rSlopeMin		=	-C_INFINITY;
			data.gSlopeMin		=	-C_INFINITY;
			data.bSlopeMin		=	-C_INFINITY;

			// Do we have a step ?
			if (cZ == data.origin[0]) {
				const float	dr	=	absf(data.origin[1] - opacity[0]);							
				const float	dg	=	absf(data.origin[2] - opacity[1]);
				const float	db	=	absf(data.origin[3] - opacity[2]);

				// Is the step small enough ?
				if ((dr >= data.tsmThreshold) || (dg >= data.tsmThreshold) || (db >= data.tsmThreshold)) {

					// No, output the step
					data.origin[1]	=	opacity[0];
					data.origin[2]	=	opacity[1];
					data.origin[3]	=	opacity[2];
					fwrite(data.origin,sizeof(float),4,data.deepShadowFile);
				}
			} else {
				const float	denom		=	1 / (cZ - data.origin[0]);
				data.rSlopeMax	=	(opacity[0] - data.origin[1] + data.tsmThreshold) * denom;
				data.gSlopeMax	=	(opacity[1] - data.origin[2] + data.tsmThreshold) * denom;
				data.bSlopeMax	=	(opacity[2] - data.origin[3] + data.tsmThreshold) * denom;
				data.rSlopeMin	=	(opacity[0] - data.origin[1] - data.tsmThreshold) * denom;
				data.gSlopeMin	=	(opacity[1] - data.origin[2] - data.tsmThreshold) * denom;
				data.bSlopeMin	=	(opacity[2] - data.origin[3] - data.tsmThreshold) * denom;
			}
		}
	}

	data.lastZ	=	cZ;
}

///////////////////////////////////////////////////////////////////////
// Function				:	finishSample
// Description			:	This function is used to output the last sample
// Return Value			:	-
// Comments				:
inline	void	finishSample(float cZ,const float *opacity,CTSMData &data) {
	if (data.origin[0] < cZ) {
		data.origin[1]		+=	(data.rSlopeMin + data.rSlopeMax)*(data.lastZ - data.origin[0])*0.5f;	
		data.origin[2]		+=	(data.gSlopeMin + data.gSlopeMax)*(data.lastZ - data.origin[0])*0.5f;
		data.origin[3]		+=	(data.bSlopeMin + data.bSlopeMax)*(data.lastZ - data.origin[0])*0.5f;
		data.origin[0]		=	data.lastZ;
		fwrite(data.origin,sizeof(float),4,data.deepShadowFile);
	}

	data.origin[0]		=	cZ;
	data.origin[1]		=	opacity[0];
	data.origin[2]		=	opacity[1];
	data.origin[3]		=	opacity[2];
	fwrite(data.origin,sizeof(float),4,data.deepShadowFile);

	data.origin[0]		=	C_INFINITY;
	fwrite(data.origin,sizeof(float),4,data.deepShadowFile);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CStochastic
// Method				:	filterSamples
// Description			:	Filter / output the pixel
// Return Value			:	-
// Comments				:
void			CStochastic::filterSamples(int numSamples,CFragment **samples,float *weights) {
	int			minSample		=	0;
	int			i;
	vector		opacity;
	CTSMData	data;

	initv(opacity,1,1,1);		// The current opacity

	startSample(CRenderer::deepShadowFile,CRenderer::tsmThreshold,data);				// The beginning of a pixel

	// Find the closest sample
	for (i=1;i<numSamples;i++) {
		if (samples[i]->z < samples[minSample]->z) {
			minSample	=	i;
		}
	}

	// Filter / output pixels incrementally
	while(TRUE) {
		int				stop		=	FALSE;							// TRUE when the opacity drops below 0
		const CFragment	*cSample	=	samples[minSample];
		const float		cZ			=	cSample->z;						// The current Z coordinate
		float			*oldOpacity	=	weights + (minSample<<2);
		vector			newOpacity;

		outSample(cZ,opacity,data);

		newOpacity[0]				=	oldOpacity[1]*(1-cSample->opacity[0]);
		newOpacity[1]				=	oldOpacity[2]*(1-cSample->opacity[1]);
		newOpacity[2]				=	oldOpacity[3]*(1-cSample->opacity[2]);

		opacity[0]					+=	(newOpacity[0] - oldOpacity[1])*oldOpacity[0];
		opacity[1]					+=	(newOpacity[1] - oldOpacity[2])*oldOpacity[0];
		opacity[2]					+=	(newOpacity[2] - oldOpacity[3])*oldOpacity[0];

		oldOpacity[1]				=	newOpacity[0];
		oldOpacity[2]				=	newOpacity[1];
		oldOpacity[3]				=	newOpacity[2];

		if (opacity[0] <= 0) {
			opacity[0]	=	0;
			stop++;
		}

		if (opacity[1] <= 0) {
			opacity[1]	=	0;
			stop++;
		}

		if (opacity[2] <= 0) {
			opacity[2]	=	0;
			stop++;
		}

		// Advance the minSample
		if ((samples[minSample]		=	samples[minSample]->next) == NULL) {
			int	nindex				=	minSample << 2;
			int	oindex				=	(numSamples-1) << 2;
			samples[minSample]		=	samples[numSamples-1];
			weights[nindex + 0]		=	weights[oindex + 0];
			weights[nindex + 1]		=	weights[oindex + 1];
			weights[nindex + 2]		=	weights[oindex + 2];
			weights[nindex + 3]		=	weights[oindex + 3];
			numSamples--;
			if (numSamples == 0) {
				stop	=	3;
			}
		}

		// Decide whether we should stop or keep going
		if (stop == 3) {
			finishSample(cZ,opacity,data);
			break;
		} else {
			outSample(cZ,opacity,data);
		}

		for (minSample=0,i=1;i<numSamples;i++) {
			if (samples[i]->z < samples[minSample]->z) {
				minSample	=	i;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CStochastic
// Method				:	deepShadowCompute
// Description			:	Compute/write deep shadow map data
// Return Value			:	-
// Comments				:
void		CStochastic::deepShadowCompute() {
	int			i;
	const int	xres				=	width;
	const int	yres				=	height;
	const int	filterWidth			=	CRenderer::pixelXsamples + 2*CRenderer::xSampleOffset;
	const int	filterHeight		=	CRenderer::pixelYsamples + 2*CRenderer::ySampleOffset;
	const float	invPixelXsamples	=	1 / (float) CRenderer::pixelXsamples;
	const float	invPixelYsamples	=	1 / (float) CRenderer::pixelYsamples;
	int			prevFilePos;
	int			numSamples;
	int			x,y;
	CFragment	**samples;
	CFragment	**fSamples;
	float		*fWeights;

	osLock(CRenderer::deepShadowMutex);
	
	memBegin(threadMemory);
	
	prevFilePos		=	ftell(CRenderer::deepShadowFile);

	// Allocate the memory for misc junk
	samples			=	(CFragment **)	ralloc(totalHeight*totalWidth*sizeof(CFragment*),threadMemory);
	fSamples		=	(CFragment **)	ralloc(filterWidth*filterHeight*sizeof(CFragment*),threadMemory);
	fWeights		=	(float *)		ralloc(filterWidth*filterHeight*sizeof(float)*4,threadMemory);

	// Init the samples
	for (i=0;i<totalWidth*totalHeight;i++)	samples[i]	=	NULL;

	// Collect the samples first
	for (i=0,y=0;y<sampleHeight;y++) {
		for (x=0;x<sampleWidth;x++,i++) {
			samples[i]	=	fb[y][x].first.next;
		}
	}

	assert(CRenderer::bucketWidth	>= xres);
	assert(CRenderer::bucketHeight	>= yres);

	// Compute the visibility function for each pixel
	for (y=0;y<CRenderer::bucketHeight;y++) {
		for (x=0;x<CRenderer::bucketWidth;x++) {

			if ((x < xres) && (y < yres)) {
				// Gather the samples for this pixel and the filter response
				int		sx,sy;
				float	filterSum		=	0;

				for (i=0,sy=0;sy<filterHeight;sy++) {
					for (sx=0;sx<filterWidth;sx++,i++) {
						const int		xsample	=	x*CRenderer::pixelXsamples + sx;
						const int		ysample	=	y*CRenderer::pixelYsamples + sy;
						const CPixel	*pixels	=	&fb[ysample][xsample];
						const float		cx		=	(sx + pixels->jx - filterWidth*0.5f*invPixelXsamples);
						const float		cy		=	(sy + pixels->jy - filterHeight*0.5f*invPixelYsamples);
						fSamples[i]				=	samples[ysample*sampleWidth+xsample];
						fWeights[i<<2]			=	CRenderer::pixelFilter(cx,cy,CRenderer::pixelFilterWidth,CRenderer::pixelFilterHeight);
						filterSum				+=	fWeights[i<<2];
					}
				}

				// Normalize the pixel filter responses
				numSamples	=	i;
				for (i=0;i<numSamples;i++) {
					const int	index	=	i << 2;
					fWeights[index+0]			/=	filterSum;
					fWeights[index+1]			=	1;
					fWeights[index+2]			=	1;
					fWeights[index+3]			=	1;
				}

				// Filter/write the pixels
				filterSamples(numSamples,fSamples,fWeights);
			} else {
				// Output a dummy pixel
				float	dummy[4];

				dummy[0]	=	-C_INFINITY;
				dummy[1]	=	1;
				dummy[2]	=	1;
				dummy[3]	=	1;
				fwrite(dummy,sizeof(float),4,CRenderer::deepShadowFile);

				dummy[0]	=	C_INFINITY;
				dummy[1]	=	1;
				dummy[2]	=	1;
				dummy[3]	=	1;
				fwrite(dummy,sizeof(float),4,CRenderer::deepShadowFile);
			}
		}
	}

	// Record the index in the file
	//	we now save sizes too in order to support arbitrary bucket orders
	//	indices are now bucket starts
	const int tileIndex = currentYBucket*CRenderer::xBuckets + currentXBucket;
	CRenderer::deepShadowIndex[tileIndex]											=	prevFilePos;
	CRenderer::deepShadowIndex[tileIndex + CRenderer::xBuckets*CRenderer::yBuckets]	=	ftell(CRenderer::deepShadowFile) - prevFilePos;

	memEnd(threadMemory);
	
	osUnlock(CRenderer::deepShadowMutex);
}

