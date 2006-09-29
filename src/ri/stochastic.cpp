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
//  File				:	stochastic.cpp
//  Classes				:	CStochastic
//  Description			:	implements the stochastic hider
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "stochastic.h"
#include "renderer.h"
#include "memory.h"
#include "random.h"

static	int	numFragments	=	0;

// This macro is used to allocate fragments
#define	newFragment(__a)	if (freeFragments == NULL)	{						\
								__a					=	new CFragment;			\
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
// Date last edited		:	7/31/2002
CStochastic::CStochastic(COptions *o,CXform *x,SOCKET s) : CReyes(o,x,s,0), COcclusionCuller() {
	int		i,j,sx,sy;
	float	*cExtraSample;
	CPixel	*cPixel;

	// The maximum width/height we should handle
	totalWidth		=	pixelXsamples*bucketWidth + 2*xSampleOffset;
	totalHeight		=	pixelYsamples*bucketHeight + 2*ySampleOffset;

	// Allocate the framebuffer
	if (numExtraSamples > 0)	extraSampleMemory	=	new float[totalWidth*totalHeight*numExtraSamples];
	else						extraSampleMemory	=	NULL;

	cExtraSample	=	extraSampleMemory;
	fb				=	new CPixel*[totalHeight];
	for (i=0;i<totalHeight;i++) {
		cPixel		=	fb[i]		=	new CPixel[totalWidth];

		for (j=totalHeight;j>0;j--,cPixel++,cExtraSample+=numExtraSamples)	cPixel->extraSamples	=	cExtraSample;
	}

	// Init the fragment buffer
	freeFragments	=	NULL;

	// Initialize the occlusion culler
	initCuller(max(totalWidth,totalHeight), &maxDepth);
	
	// Set up the pixel filter
	const int		filterWidth				=	pixelXsamples + 2*xSampleOffset;
	const int		filterHeight			=	pixelYsamples + 2*ySampleOffset;
	const float		halfFilterWidth			=	(float) filterWidth / (float) 2;
	const float		halfFilterHeight		=	(float) filterHeight / (float) 2;
	const float		invPixelXsamples		=	1 / (float) pixelXsamples;
	const float		invPixelYsamples		=	1 / (float) pixelYsamples;

	
	pixelFilterWeights	=	new float[filterWidth*filterHeight];
	
	// Evaluate the pixel filter, ignoring the jitter as it is apperently what other renderers do as well
	{
		float	totalWeight	=	0;
		double	invWeight;

		for (sy=0;sy<filterHeight;sy++) {
			for (sx=0;sx<filterWidth;sx++) {
				const float	cx								=	(sx - halfFilterWidth + 0.5f)*invPixelXsamples;
				const float	cy								=	(sy - halfFilterHeight + 0.5f)*invPixelYsamples;
				float		filterResponse					=	pixelFilter(cx,cy,pixelFilterWidth,pixelFilterHeight);

				// Account for the partial area out of the bounds
				//if (fabs(cx) > marginX)	filterResponse		*=	marginXcoverage;
				//if (fabs(cy) > marginY)	filterResponse		*=	marginYcoverage;

				// Record
				pixelFilterWeights[sy*filterWidth + sx]		=	filterResponse;
				totalWeight									+=	filterResponse;
			}
		}

		// Normalize the filter kernel
		invWeight	=	1 / (double) totalWeight;
		for (i=0;i<filterWidth*filterHeight;i++) {
			pixelFilterWeights[i]							=	(float) (pixelFilterWeights[i] * invWeight);
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CStochastic
// Method				:	~CStochastic
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	7/31/2002
CStochastic::~CStochastic() {
	int			i;
	CFragment	*cFragment;
	
	// Ditch the pixel filter
	delete[] pixelFilterWeights;

	// Ditch the memory we allocated for extra samples
	if (extraSampleMemory != NULL) delete [] extraSampleMemory;

	// Ditch the pixels
	for (i=0;i<totalHeight;i++) {
		delete [] fb[i];
	}
	delete [] fb;

	// Ditch the extra fragments
	while((cFragment = freeFragments) != NULL) {
		freeFragments	=	cFragment->next;
		delete cFragment;
	}
}

// static sampling - no patterning over buckets or frames
CSobol<2>	apertureGenerator;

///////////////////////////////////////////////////////////////////////
// Class				:	CStochastic
// Method				:	rasterBegin
// Description			:	Begin drawing an image
// Return Value			:	-
// Comments				:
// Date last edited		:	7/31/2002
void		CStochastic::rasterBegin(int w,int h,int l,int t) {
	int			i,j,k,pxi,pxj;
	float		zoldStart;
	CFragment	*cFragment;
	//CSobol<2>	apertureGenerator;


	assert(numFragments == 0);


	switch(depthFilter) {
	case DEPTH_MIN:
		zoldStart	=	clipMax;
		break;
	case DEPTH_MAX:
		zoldStart	=	-clipMax;
		break;
	case DEPTH_AVG:
		zoldStart	=	0;
		break;
	case DEPTH_MID:
		zoldStart	=	clipMax;
		break;
	}

	// Set the digits
	width				=	w;
	height				=	h;
	left				=	l;
	top					=	t;
	sampleWidth			=	width*pixelXsamples + 2*xSampleOffset;
	sampleHeight		=	height*pixelYsamples + 2*ySampleOffset;
	right				=	left + sampleWidth;
	bottom				=	top + sampleHeight;

	assert(sampleWidth <= totalWidth);
	assert(sampleHeight <= totalHeight);

	// Init the occlusion culler to zero
	initToZero();
	for (i=0,pxi=pixelYsamples-ySampleOffset;i<sampleHeight;i++,pxi++) {
		CPixel	*pixel	=	fb[i];
		
		if (pxi >= pixelYsamples)	pxi = 0;
		
		for (j=0,pxj=pixelXsamples-xSampleOffset;j<sampleWidth;j++,pxj++,pixel++) {
			float	aperture[2];

			// The stratified sample
			pixel->jx					=	(jitter*(urand()-0.5f) + 0.5001011f);
			pixel->jy					=	(jitter*(urand()-0.5f) + 0.5001017f);

			// Time of the sample for motion blur
			if (pxj >= pixelXsamples)	pxj = 0;
			pixel->jt					=	( pxi*pixelXsamples + pxj + jitter*(urand()-0.5f) + 0.5001011f)/(float)(pixelXsamples*pixelYsamples);
			
			// Importance blend / jitter
			pixel->jimp					=	1.0f - ( pxj*pixelYsamples + pxi + jitter*(urand()-0.5f) + 0.5001011f)/(float)(pixelXsamples*pixelYsamples);	//urand();

			if (flags & OPTIONS_FLAGS_FOCALBLUR) {
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

			pixel->z					=	clipMax;
			pixel->zold					=	zoldStart;
			pixel->numSplats			=	0;
			pixel->node					=	getNode(j,i);
			pixel->node->zmax			=	clipMax;


			cFragment					=	&pixel->last;
			cFragment->z				=	clipMax;
			initv(cFragment->color,0);
			initv(cFragment->opacity,0);
			cFragment->next				=	NULL;
			cFragment->prev				=	&pixel->first;

			cFragment					=	&pixel->first;
			cFragment->z				=	-C_INFINITY;
			initv(cFragment->color,0);
			initv(cFragment->opacity,0);
			cFragment->next				=	&pixel->last;
			cFragment->prev				=	NULL;
			
			for (k=0;k<numExtraSamples;k++) {
				pixel->extraSamples[k]	=	sampleDefaults[k];
			}

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
// Date last edited		:	7/31/2002
void		CStochastic::rasterDrawPrimitives(CRasterGrid *grid) {
// Instantiate the dispatch switch
#define DEFINE_STOCHASTIC_SWITCH
	#include "stochasticPrimitives.h"
#undef DEFINE_STOCHASTIC_SWITCH
}

// Instantiate the rasterization functions


#define depthFilterIfZMin()
#define depthFilterElseZMin()

#define depthFilterIfZMax()		pixel->zold		=	max(pixel->zold,z);
#define depthFilterElseZMax()	else {	pixel->zold	=	max(pixel->zold,z);	}

#define depthFilterIfZAvg()		pixel->zold		+=	z; pixel->numSplats++;
#define depthFilterElseZAvg()	else {	pixel->zold	+=	z; pixel->numSplats++;	}

#define depthFilterIfZMid()		pixel->zold		=	pixel->z;
#define depthFilterElseZMid()	else {	pixel->zold	=	min(pixel->zold,z);	}

#define lodExtraVariables()		const float importance = grid->object->attributes->lodImportance;


//////////////////////////////////////////////////////////////////////////////////////////////////
//
//   There are two sets of parameters, for triangles and for points
//      Within each set, some parameters are only required when there is motion blur, depth of field etc.
//      The macros below define local variables for each set, so that we do not end up with a huge amount
//      of unused variables. This not only makes the compiler happy, but also produces leaner code
//
//////////////////////////////////////////////////////////////////////////////////////////////////


// Triangle drawing local variables
#define triExtraVariables()			const	int					*xbound;							\
									const	int					*ybound;							\
									const	float				*v0,*v0c;							\
									const	float				*v1,*v1c;							\
									const	float				*v2,*v2c;							\
									const	float				*dv0,*dv1,*dv2;						\
									float						a;

#define movTriExtraVariables()		vector						v0movTmp,v1movTmp,v2movTmp;
#define focTriExtraVariables()		vector						v0focTmp,v1focTmp,v2focTmp;
#define transTriExtraVariables()	const float					*v0o,*v1o,*v2o;

// Point drawing local variables
#define ptExtraVariables()			const	float				*v0,*v0c;							\
									const	float				*dv0;

#define movPtExtraVariables()		vector						v0movTmp;
#define focPtExtraVariables()		vector						v0focTmp;
#define transPtExtraVariables()		const float					*v0o;

// Common local variables
#define drawGridHeader() 																			\
	const	int					xres				=	sampleWidth - 1;							\
	const	int					yres				=	sampleHeight - 1;							\
	const	TRasterPrimitive	*cPrimitive;														\
	const	int					sampleDisplacement	=	numExtraSamples + 10;						\
	int							xmin,xmax,ymin,ymax,x,y;											\
	int							numPrimitives;

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
#undef lodExtraVariables
#undef drawGridHeader
#undef findSample
#undef updateOpaque


///////////////////////////////////////////////////////////////////////
// Class				:	CStochastic
// Method				:	rasterEnd
// Description			:	Get the image from the screen
// Return Value			:	-
// Comments				:
// Date last edited		:	7/31/2002
void		CStochastic::rasterEnd(float *fb2) {
	int				i,y;
	int				sx,sy;
	const int		xres					=	width;
	const int		yres					=	height;
	const int		filterWidth				=	pixelXsamples + 2*xSampleOffset;
	const int		filterHeight			=	pixelYsamples + 2*ySampleOffset;
	const float		halfFilterWidth			=	(float) filterWidth / (float) 2;
	const float		halfFilterHeight		=	(float) filterHeight / (float) 2;
	float			*fbs;
	const int		pixelSize				=	8	+ numExtraSamples;	// alpha + depth + color + opacity + extra samples
	float			*tmp;
	const int		sampleLineDisplacement	=	pixelXsamples*pixelSize;

	// Deep shadow map computation
	if (flags & OPTIONS_FLAGS_DEEP_SHADOW_RENDERING)	deepShadowCompute();

	memBegin();

	// Allocate the framebuffer
	fbs				=	(float *) ralloc(totalWidth*totalHeight*pixelSize*sizeof(float));

	// Collapse the samples (transparency composite)

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
 
			assert(cPixel->first.z == -C_INFINITY);

			if (numExtraSamples > 0)
				memcpy(cFb+8,cPixel->extraSamples,numExtraSamples*sizeof(float));

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

				oSample		=	cSample;
				cSample		=	cSample->next;
				for (;cSample!=NULL;) {
					deleteFragment(oSample);
					const float	*color		= cSample->color;
					const float *opacity	= cSample->opacity;
	
					// Composite
					C[0]		+=	ropacity[0]*color[0];
					C[1]		+=	ropacity[1]*color[1];
					C[2]		+=	ropacity[2]*color[2];
					O[0]		+=	ropacity[0]*opacity[0];
					O[1]		+=	ropacity[1]*opacity[1];
					O[2]		+=	ropacity[2]*opacity[2];
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
				}
				else {
					// Non-matte base sample
					movvv(C,cSample->color);
					movvv(O,cSample->opacity);
					ropacity[0]	=	1-O[0];
					ropacity[1]	=	1-O[1];
					ropacity[2]	=	1-O[2];

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
					}
					else {
						// Composite non-matte
						C[0]		+=	ropacity[0]*color[0];
						C[1]		+=	ropacity[1]*color[1];
						C[2]		+=	ropacity[2]*color[2];
						O[0]		+=	ropacity[0]*opacity[0];
						O[1]		+=	ropacity[1]*opacity[1];
						O[2]		+=	ropacity[2]*opacity[2];
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
	switch(depthFilter) {
	case DEPTH_MIN:
		for (y=0;y<sampleHeight;y++) {
			CPixel	*cPixel		=	fb[y];
			float	*cFb		=	&fbs[y*totalWidth*pixelSize];

			for (i=sampleWidth;i>0;i--,cPixel++,cFb+=pixelSize) {
				if (cPixel->z == clipMax)	cFb[1]	=	C_INFINITY;
				else						cFb[1]	=	cPixel->z;
			}
		}

		break;
	case DEPTH_MAX:
		for (y=0;y<sampleHeight;y++) {
			CPixel	*cPixel		=	fb[y];
			float	*cFb		=	&fbs[y*totalWidth*pixelSize];

			for (i=sampleWidth;i>0;i--,cPixel++,cFb+=pixelSize) {
				if (cPixel->z == clipMax)	cFb[1]	=	C_INFINITY;
				else						cFb[1]	=	cPixel->zold;
			}
		}

		break;
	case DEPTH_AVG:
		for (y=0;y<sampleHeight;y++) {
			CPixel	*cPixel		=	fb[y];
			float	*cFb		=	&fbs[y*totalWidth*pixelSize];

			for (i=sampleWidth;i>0;i--,cPixel++,cFb+=pixelSize) {
				if (cPixel->z == clipMax)	cFb[1]	=	C_INFINITY;
				else						cFb[1]	=	cPixel->zold / (float) cPixel->numSplats;
			}
		}

		break;
	case DEPTH_MID:
		for (y=0;y<sampleHeight;y++) {
			CPixel	*cPixel		=	fb[y];
			float	*cFb		=	&fbs[y*totalWidth*pixelSize];

			for (i=sampleWidth;i>0;i--,cPixel++,cFb+=pixelSize) {
				if (cPixel->z == clipMax)	cFb[1]	=	C_INFINITY;
				else {

					assert(cPixel->z < clipMax);
					assert(cPixel->zold <= clipMax);
					assert(cPixel->z <= cPixel->zold);

					if (cPixel->zold < culledDepth)	cFb[1]		=	(cPixel->z + cPixel->zold) * 0.5f;
					else							cFb[1]		=	(cPixel->z + culledDepth) * 0.5f;
				}
			}
		}

		break;
	}

	// Clear the memory first
	for (tmp=fb2,i=xres*yres*numSamples;i>0;i--)	*tmp++	=	0;

	// Filter the samples
	for (y=0;y<yres;y++) {
		for (sy=0;sy<filterHeight;sy++) {
			for (sx=0;sx<filterWidth;sx++) {
				const CPixel	*pixels			=	&fb[y*pixelYsamples+sy][sx];
				float			*pixelLine		=	&fb2[y*xres*numSamples];
				const float		*sampleLine		=	&fbs[((y*pixelYsamples+sy)*totalWidth + sx)*pixelSize];
				const float		xOffset			=	sx - halfFilterWidth;
				const float		yOffset			=	sy - halfFilterHeight;
				const float		filterResponse	=	pixelFilterWeights[sy*filterWidth + sx];

				for (i=0;i<xres;i++) {
					int			es;

					pixelLine[0]				+=	filterResponse*sampleLine[2];
					pixelLine[1]				+=	filterResponse*sampleLine[3];
					pixelLine[2]				+=	filterResponse*sampleLine[4];
					pixelLine[3]				+=	filterResponse*sampleLine[0];
					pixelLine[4]				+=	filterResponse*sampleLine[1];

					// Filter the extra samples here
					for (es=0;es<numExtraSamples;es++) {
						pixelLine[5+es]			+=	filterResponse*sampleLine[8+es];
					}

					// Advance
					pixelLine					+=	numSamples;
					sampleLine					+=	sampleLineDisplacement;
					pixels						+=	pixelXsamples;
				}
			}
		}
	}

	memEnd();
}


// The origin, the last depth sample we output
static	float	origin[4];
static	float	lastZ;
static	float	rSlopeMin;
static	float	gSlopeMin;
static	float	bSlopeMin;
static	float	rSlopeMax;
static	float	gSlopeMax;
static	float	bSlopeMax;
static	FILE	*deepShadowFile;
static	float	tsmThreshold;

///////////////////////////////////////////////////////////////////////
// Function				:	outSample
// Description			:	This function is used to output a depth sample
// Return Value			:	-
// Comments				:
// Date last edited		:	12/26/2003
inline	void	startSample(FILE *outFile,float threshold) {
	deepShadowFile	=	outFile;
	tsmThreshold	=	threshold;

	rSlopeMax		=	C_INFINITY;
	gSlopeMax		=	C_INFINITY;
	bSlopeMax		=	C_INFINITY;
	rSlopeMin		=	-C_INFINITY;
	gSlopeMin		=	-C_INFINITY;
	bSlopeMin		=	-C_INFINITY;

	// Output the first sample (at z=-C_INFINITY)
	origin[0]		=	-C_INFINITY;
	origin[1]		=	1;
	origin[2]		=	1;
	origin[3]		=	1;
	fwrite(origin,sizeof(float),4,deepShadowFile);
	lastZ			=	-C_INFINITY;
}

///////////////////////////////////////////////////////////////////////
// Function				:	outSample
// Description			:	This function is used to output a depth sample
// Return Value			:	-
// Comments				:
// Date last edited		:	12/26/2003
inline	void	outSample(float cZ,const float *opacity) {
	// Always output the closest sample
	if (origin[0] == -C_INFINITY) {
		origin[0]	=	cZ;
		origin[1]	=	opacity[0];
		origin[2]	=	opacity[1];
		origin[3]	=	opacity[2];

		fwrite(origin,sizeof(float),4,deepShadowFile);
	} else if (cZ == origin[0]) {	// Do we have a step ?
		const float	dr	=	absf(origin[1] - opacity[0]);							
		const float	dg	=	absf(origin[2] - opacity[1]);
		const float	db	=	absf(origin[3] - opacity[2]);

		// Is the step small enough ?
		if ((dr >= tsmThreshold) || (dg >= tsmThreshold) || (db >= tsmThreshold)) {

			// No, output the step
			origin[1]	=	opacity[0];
			origin[2]	=	opacity[1];
			origin[3]	=	opacity[2];
			fwrite(origin,sizeof(float),4,deepShadowFile);
		}
	} else {
		// Check for the window of validity
		const float	denom		=	1 / (cZ - origin[0]);
		float		crSlopeMax	=	(opacity[0] - origin[1] + tsmThreshold) * denom;
		float		cgSlopeMax	=	(opacity[1] - origin[2] + tsmThreshold) * denom;
		float		cbSlopeMax	=	(opacity[2] - origin[3] + tsmThreshold) * denom;
		float		crSlopeMin	=	(opacity[0] - origin[1] - tsmThreshold) * denom;
		float		cgSlopeMin	=	(opacity[1] - origin[2] - tsmThreshold) * denom;
		float		cbSlopeMin	=	(opacity[2] - origin[3] - tsmThreshold) * denom;

		crSlopeMax				=	min(crSlopeMax,rSlopeMax);
		cgSlopeMax				=	min(cgSlopeMax,gSlopeMax);
		cbSlopeMax				=	min(cbSlopeMax,bSlopeMax);

		crSlopeMin				=	max(crSlopeMin,rSlopeMin);
		cgSlopeMin				=	max(cgSlopeMin,gSlopeMin);
		cbSlopeMin				=	max(cbSlopeMin,bSlopeMin);

		if ((crSlopeMin < crSlopeMax) && (cgSlopeMin < cgSlopeMax) && (cbSlopeMin < cbSlopeMax)) {			
			// We're in range
			rSlopeMax		=	crSlopeMax;
			gSlopeMax		=	cgSlopeMax;
			bSlopeMax		=	cbSlopeMax;

			rSlopeMin		=	crSlopeMin;
			gSlopeMin		=	cgSlopeMin;
			bSlopeMin		=	cbSlopeMin;
		} else {
			origin[1]		+=	(rSlopeMin + rSlopeMax)*(lastZ - origin[0])*0.5f;
			origin[2]		+=	(gSlopeMin + gSlopeMax)*(lastZ - origin[0])*0.5f;
			origin[3]		+=	(bSlopeMin + bSlopeMax)*(lastZ - origin[0])*0.5f;
			origin[0]		=	lastZ;
			fwrite(origin,sizeof(float),4,deepShadowFile);

			rSlopeMax		=	C_INFINITY;
			gSlopeMax		=	C_INFINITY;
			bSlopeMax		=	C_INFINITY;
			rSlopeMin		=	-C_INFINITY;
			gSlopeMin		=	-C_INFINITY;
			bSlopeMin		=	-C_INFINITY;

			// Do we have a step ?
			if (cZ == origin[0]) {
				const float	dr	=	absf(origin[1] - opacity[0]);							
				const float	dg	=	absf(origin[2] - opacity[1]);
				const float	db	=	absf(origin[3] - opacity[2]);

				// Is the step small enough ?
				if ((dr >= tsmThreshold) || (dg >= tsmThreshold) || (db >= tsmThreshold)) {

					// No, output the step
					origin[1]	=	opacity[0];
					origin[2]	=	opacity[1];
					origin[3]	=	opacity[2];
					fwrite(origin,sizeof(float),4,deepShadowFile);
				}
			} else {
				const float	denom		=	1 / (cZ - origin[0]);
				rSlopeMax	=	(opacity[0] - origin[1] + tsmThreshold) * denom;
				gSlopeMax	=	(opacity[1] - origin[2] + tsmThreshold) * denom;
				bSlopeMax	=	(opacity[2] - origin[3] + tsmThreshold) * denom;
				rSlopeMin	=	(opacity[0] - origin[1] - tsmThreshold) * denom;
				gSlopeMin	=	(opacity[1] - origin[2] - tsmThreshold) * denom;
				bSlopeMin	=	(opacity[2] - origin[3] - tsmThreshold) * denom;
			}
		}
	}

	lastZ	=	cZ;
}

///////////////////////////////////////////////////////////////////////
// Function				:	finishSample
// Description			:	This function is used to output the last sample
// Return Value			:	-
// Comments				:
// Date last edited		:	12/26/2003
inline	void	finishSample(float cZ,const float *opacity) {
	if (origin[0] < cZ) {
		origin[1]		+=	(rSlopeMin + rSlopeMax)*(lastZ - origin[0])*0.5f;	
		origin[2]		+=	(gSlopeMin + gSlopeMax)*(lastZ - origin[0])*0.5f;
		origin[3]		+=	(bSlopeMin + bSlopeMax)*(lastZ - origin[0])*0.5f;
		origin[0]		=	lastZ;
		fwrite(origin,sizeof(float),4,deepShadowFile);
	}

	origin[0]		=	cZ;
	origin[1]		=	opacity[0];
	origin[2]		=	opacity[1];
	origin[3]		=	opacity[2];
	fwrite(origin,sizeof(float),4,deepShadowFile);

	origin[0]		=	C_INFINITY;
	fwrite(origin,sizeof(float),4,deepShadowFile);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CStochastic
// Method				:	filterSamples
// Description			:	Filter / output the pixel
// Return Value			:	-
// Comments				:
// Date last edited		:	3/1/2003
void			CStochastic::filterSamples(int numSamples,CFragment **samples,float *weights) {
	int		minSample		=	0;
	int		i;
	vector	opacity;

	initv(opacity,1,1,1);		// The current opacity

	startSample(deepShadowFile,tsmThreshold);				// The beginning of a pixel

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

		outSample(cZ,opacity);

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
			finishSample(cZ,opacity);
			break;
		} else {
			outSample(cZ,opacity);
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
// Date last edited		:	7/31/2002
void		CStochastic::deepShadowCompute() {
	int			i;
	const int	xres				=	width;
	const int	yres				=	height;
	const int	filterWidth			=	pixelXsamples + 2*xSampleOffset;
	const int	filterHeight		=	pixelYsamples + 2*ySampleOffset;
	const float	invPixelXsamples	=	1 / (float) pixelXsamples;
	const float	invPixelYsamples	=	1 / (float) pixelYsamples;
	int			prevFilePos;
	int			numSamples;
	int			x,y;
	CFragment	**samples;
	CFragment	**fSamples;
	float		*fWeights;

	memBegin();
	
	prevFilePos		=	ftell(deepShadowFile);

	// Allocate the memory for misc junk
	samples			=	(CFragment **)	ralloc(totalHeight*totalWidth*sizeof(CFragment*));
	fSamples		=	(CFragment **)	ralloc(filterWidth*filterHeight*sizeof(CFragment*));
	fWeights		=	(float *)		ralloc(filterWidth*filterHeight*sizeof(float)*4);

	// Init the samples
	for (i=0;i<totalWidth*totalHeight;i++)	samples[i]	=	NULL;

	// Collect the samples first
	for (i=0,y=0;y<sampleHeight;y++) {
		for (x=0;x<sampleWidth;x++,i++) {
			samples[i]	=	fb[y][x].first.next;
		}
	}

	assert(bucketWidth	>= xres);
	assert(bucketHeight	>= yres);

	// Compute the visibility function for each pixel
	for (y=0;y<bucketHeight;y++) {
		for (x=0;x<bucketWidth;x++) {

			if ((x < xres) && (y < yres)) {
				// Gather the samples for this pixel and the filter response
				int		sx,sy;
				float	filterSum		=	0;

				for (i=0,sy=0;sy<filterHeight;sy++) {
					for (sx=0;sx<filterWidth;sx++,i++) {
						const int		xsample	=	x*pixelXsamples + sx;
						const int		ysample	=	y*pixelYsamples + sy;
						const CPixel	*pixels	=	&fb[ysample][xsample];
						const float		cx		=	(sx + pixels->jx - filterWidth*0.5f*invPixelXsamples);
						const float		cy		=	(sy + pixels->jy - filterHeight*0.5f*invPixelYsamples);
						fSamples[i]				=	samples[ysample*sampleWidth+xsample];
						fWeights[i<<2]			=	pixelFilter(cx,cy,pixelFilterWidth,pixelFilterHeight);
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
				fwrite(dummy,sizeof(float),4,deepShadowFile);

				dummy[0]	=	C_INFINITY;
				dummy[1]	=	1;
				dummy[2]	=	1;
				dummy[3]	=	1;
				fwrite(dummy,sizeof(float),4,deepShadowFile);
			}
		}
	}

	// Record the index in the file
	//	we now save sizes too in order to support arbitrary bucket orders
	//	indices are now bucket starts
	const int tileIndex = currentYBucket*xBuckets + currentXBucket;
	deepShadowIndex[tileIndex]						=	prevFilePos;
	deepShadowIndex[tileIndex + xBuckets*yBuckets]	=	ftell(deepShadowFile) - prevFilePos;

	memEnd();
}
