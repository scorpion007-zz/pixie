//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright © 1999 - 2010, Okan Arikan
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
//  Description			:
/// \brief					implements the stochastic hider
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "stochastic.h"
#include "memory.h"
#include "random.h"


// This function is used to allocate fragments.
// Maintains a lookaside list so we don't allocate all the time.
//
void
CStochastic::newFragment(
	__out CFragment** ppSample)
{
	if (freeFragments == NULL)
	{					
		*ppSample					=	new CFragment;			
		if (CRenderer::numExtraSamples > 0)
		{							
			(*ppSample)->extraSamples = new float[CRenderer::numExtraSamples]; 	
		}																
	}
	else
	{											
		*ppSample =	freeFragments;			
		freeFragments =	freeFragments->next;	
	}													
	numFragments++;
}

// And deallocate.
//
void
CStochastic::deleteFragment(
	__in CFragment* sample)
{
	sample->next = freeFragments;			
	freeFragments = sample;					
	numFragments--;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CStochastic
// Method				:	CStochastic
// Description			:
/// \brief					Ctor
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

		for (j=totalWidth;j>0;j--,cPixel++,cExtraSample+=CRenderer::numExtraSamples) {
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
// Description			:
/// \brief					Dtor
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
// Description			:
/// \brief					Begin drawing an image
// Return Value			:	-
// Comments				:
void		CStochastic::rasterBegin(int w,int h,int l,int t,int nullBucket) {
	int			i,j,pxi,pxj;
	float		zoldStart;
	CFragment	*cFragment;
	
	assert(numFragments == 0);

	zoldStart			=	CRenderer::clipMax;

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
	if (!(CRenderer::flags & OPTIONS_FLAGS_DEEP_SHADOW_RENDERING) && nullBucket)
	{
		return;
	}

	assert(sampleWidth <= totalWidth);
	assert(sampleHeight <= totalHeight);

	// Init the occlusion culler to zero.
	//
	initToZero();
	
	for (i = 0, pxi = CRenderer::pixelYsamples - CRenderer::ySampleOffset;
		 i < sampleHeight;
		 i++, pxi++)
	{
		CPixel	*pixel	=	fb[i];
		
		if (pxi >= CRenderer::pixelYsamples)
		{
			pxi = 0;
		}
		
		for (j = 0, pxj = CRenderer::pixelXsamples - CRenderer::xSampleOffset;
			 j < sampleWidth;
			 j++, pxj++, pixel++)
		{
			float	aperture[2];

			// The stratified sample.
			//
			pixel->jx = (CRenderer::jitter*(urand()-0.5f) + 0.5001011f);
			pixel->jy = (CRenderer::jitter*(urand()-0.5f) + 0.5001017f);

			if (pxj >= CRenderer::pixelXsamples)
			{
				pxj = 0;
			}
			
			// Time of the sample for motion blur.
			//
			pixel->jt = (pxi * CRenderer::pixelXsamples + pxj + CRenderer::jitter*(urand()-0.5f) + 0.5001011f)/
				(float)(CRenderer::pixelXsamples * CRenderer::pixelYsamples);
			
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
			initv(cFragment->accumulatedOpacity,0);


			cFragment					=	&pixel->first;
			cFragment->z				=	-C_INFINITY;
			initv(cFragment->color,0);
			initv(cFragment->opacity,0);
			cFragment->next				=	&pixel->last;
			cFragment->prev				=	NULL;
			// Note: The first fragment's extra samples are not used, and the pointer is NULL
			assert(cFragment->extraSamples == NULL);
			initv(cFragment->accumulatedOpacity,0);

			pixel->update				=	&pixel->first;
		}
	}

	resetHierarchy();
}

bool
CStochastic::lodCheck(
	__in CRasterGrid *grid,
	__in CPixel* pixel)
{
	const float importance = grid->object->attributes->lodImportance;
	
	if (importance >= 0)
	{							
		if (pixel->jimp > importance)
		{
			return false;
		}
	}
	else
	{										
		if (1 - pixel->jimp >= -importance)
		{
			return false;
		}
	}
	
	return true;
}

static bool
shouldDrawBack(unsigned flags)
{
	if (flags & RASTER_UNDERCULL)
	{
		return flags & (RASTER_DRAW_BACK | RASTER_SHADE_BACKFACE);
	}
	else
	{
		return flags & RASTER_DRAW_BACK;
	}
}

static bool
shouldDrawFront(unsigned flags)
{
	if (flags & RASTER_UNDERCULL)
	{
		return flags & (RASTER_DRAW_FRONT | RASTER_SHADE_BACKFACE);
	}
	else
	{
		return flags & RASTER_DRAW_FRONT;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
// This function is used to check whether the sample is inside the quad or not
// TODO: fix name.
//
bool
CStochastic::checkPixel(
	__in bool useLessThan,
	__in CPixel* pixel,
	__in const float* v0,
	__in const float* v1,
	__in const float* v2,
	__in const float* v3,
	__out float* pZ,
	__out float* pU,
	__out float* pV)
{
	const float		xcent	=	pixel->xcent;																
	const float		ycent	=	pixel->ycent;																
	float			aleft,atop,aright,abottom;	

	// Compute areas.
	//
	atop		= area(xcent,ycent,v0[COMP_X],v0[COMP_Y],v1[COMP_X],v1[COMP_Y]); 	
	aright		= area(xcent,ycent,v1[COMP_X],v1[COMP_Y],v3[COMP_X],v3[COMP_Y]); 	
	abottom	= area(xcent,ycent,v3[COMP_X],v3[COMP_Y],v2[COMP_X],v2[COMP_Y]); 
	aleft		= area(xcent,ycent,v2[COMP_X],v2[COMP_Y],v0[COMP_X],v0[COMP_Y]); 	

	if (useLessThan)
	{
		if (atop < 0 ||
			aright < 0 ||
			abottom < 0	||
			aleft < 0)
		{
			return false;
		}
	}
	else
	{
		if (atop > 0 ||
			aright > 0 ||
			abottom > 0	||
			aleft > 0)
		{
			return false;
		}
	}
																											
	const float u	=	aleft / (aleft + aright);															
	const float v	=	atop / (atop + abottom);															
	const float	z	=	(v0[COMP_Z]*(1-u) + v1[COMP_Z]*u)*(1-v) + (v2[COMP_Z]*(1-u) + v3[COMP_Z]*u)*v;

	// Fill caller param.
	// TODO: clean this
	//
	*pZ = z;
	*pU = u;
	*pV = v;
	
	if (z < CRenderer::clipMin)
	{
		return false;
	}

	return true;
}

// The following macros help various fragment operations
// TODO: make CPixel not a nested class!
//
void
CStochastic::depthFilterIfZMin(
	__in CPixel* pixel)
{
	// nop
}

void
CStochastic::depthFilterElseZMin(
	__in CPixel* pixel,
	__in float z)
{
	// nop
}

void
CStochastic::depthFilterTouchNodeZMin(
	__in CPixel* pixel,
	__in float z)
{
	touchNode(pixel->node, z);
}

void
CStochastic::depthFilterIfZMid(
	__in CPixel* pixel)
{
	pixel->zold		=	pixel->z;
}

void
CStochastic::depthFilterElseZMid(
	__in CPixel* pixel,
	__in float z)
{
	pixel->zold	=	min(pixel->zold, z);
}

void
CStochastic::depthFilterTouchNodeZMid(
	__in CPixel* pixel,
	__in float z)
{
	touchNode(pixel->node, pixel->zold);
}


void
CStochastic::updateTransparent(
	__in CPixel* pixel,
	__in CFragment* nSample,
	__in bool useZMid)
{															
	vector O = {0};
	vector rO = {0};											
	const float *Oc = NULL;										
	CFragment *cSample	=	nSample->prev;					
	
	movvv(O, cSample->accumulatedOpacity);					
	
	if (O[0] < CRenderer::opacityThreshold[0] &&
		O[1] < CRenderer::opacityThreshold[1] &&
		O[2] < CRenderer::opacityThreshold[2])
	{	
		/* not already opaque */																	
		cSample = nSample;																			
	}	
	
	/* adjust accumulated opacities and test against threshold */									
	initv(rO,1-O[0],1-O[1],1-O[2]);																	
	while(cSample) 
	{																				
		Oc = cSample->opacity;																		
		if (Oc[0] < 0 || Oc[1] < 0 || Oc[2] < 0) {													
			rO[0] *= 1+Oc[0];																		
			rO[1] *= 1+Oc[1];																		
			rO[2] *= 1+Oc[2];																		
		} else {																					
			O[0] += Oc[0]*rO[0];																	
			O[1] += Oc[1]*rO[1];																	
			O[2] += Oc[2]*rO[2];																	
			rO[0] *= 1-Oc[0];																		
			rO[1] *= 1-Oc[1];																		
			rO[2] *= 1-Oc[2];																		
		}																							
		movvv(cSample->accumulatedOpacity,O);														
																									
		if (O[0] > CRenderer::opacityThreshold[0] &&
			O[1] > CRenderer::opacityThreshold[1] &&
			O[2] > CRenderer::opacityThreshold[2]) 
		{	
			/* opaque after this point */															
			CFragment *dSample	=	cSample->next;													
			if (dSample && dSample != &pixel->last) {												
				while(dSample && dSample != &pixel->last) {											
					CFragment *tSample	=	dSample->next;											
					deleteFragment(dSample);														
					dSample				=	tSample;												
				}																					
				cSample->next		=	&pixel->last;												
				pixel->last.prev	=	cSample;													
				pixel->update		=	cSample;													
				/*initv(pixel->last.color,0);				*/	
				/*initv(pixel->last.opacity,0);				*/	
				/*initv(pixel->last.accumulatedOpacity,1);	*/	
				/*pixel->last.z = CRenderer::clipMax;		*/	
				/*initv(cSample->accumulatedOpacity,1);		*/	
			}																						
			const float z			=	cSample->z;													
			if (z < pixel->z) {																		
				useZMid ? depthFilterIfZMid(pixel) : depthFilterIfZMin(pixel);																				
				pixel->z			=	z;															
				useZMid ? depthFilterTouchNodeZMid(pixel, z) :
						  depthFilterTouchNodeZMin(pixel, z);																
			} 
			else
			{
				useZMid ? depthFilterElseZMid(pixel, z) :
						  depthFilterElseZMin(pixel, z);
			}
			break;																					
		}																			
		cSample = cSample->next;																	
	}																							
}


// This function is used to insert a fragment into the linked list for a pixel.
//
void
CStochastic::findSample(
	__out CFragment** dest,
	__in CPixel* pixel,
	__in float z)
{ 															
	CFragment *lSample	=	pixel->update;														
	if (z >= lSample->z)
	{																	
		CFragment		*cSample;																
		for (cSample=lSample->next;z >= cSample->z;lSample=cSample,cSample=cSample->next);	
		assert(z >= lSample->z);																
		assert(z <= cSample->z);																
		newFragment(dest);																	
		(*dest)->next	=	cSample;															
		(*dest)->prev	=	lSample;															
		cSample->prev	=	*dest;																
		lSample->next	=	*dest;																
	}
	else
	{																					
		CFragment		*cSample;																
		for (cSample=lSample->prev;
			 z < cSample->z;
			 lSample = cSample, cSample=cSample->prev);
			 
		assert(z >= cSample->z);																
		assert(z <= lSample->z);																
		newFragment(dest);																	
		(*dest)->next	=	lSample;															
		(*dest)->prev	=	cSample;															
		cSample->next	=	*dest;																
		lSample->prev	=	*dest;																
	}																							
	pixel->update	=	*dest;																	
}


void
CStochastic::colorOpacityUpdate(
	__out CFragment* nSample,
	__in CPixel* pixel,
	__in CRasterGrid* grid,
	__in float u,
	__in float v,
	__in const float* v0c,
	__in const float* v1c,
	__in const float* v2c,
	__in const float* v3c,
	__in int displacement)
{
	// Initialize the color to black and fully opaque opacity.
	//
	initv(nSample->color, 0);																
	initv(nSample->opacity, 1);

	const float jt = pixel->jt;
	
	for (int i = 0; i < 3; ++i)
	{
		const int opacityIdx = i + 3;

		if (!(grid->flags & RASTER_MATTE))
		{
			if (grid->flags & RASTER_MOVING)
			{
				nSample->color[i]		=	
					((v0c[i]*(1-jt) + v0c[displacement+i]*jt)*(1-u) +
					( v1c[i]*(1-jt) + v1c[displacement+i]*jt)*u)*(1-v) +
					((v2c[i]*(1-jt) + v2c[displacement+i]*jt)*(1-u) +
					 (v3c[i]*(1-jt) + v3c[displacement+i]*jt)*u)*v; 
			}
			else
			{
				nSample->color[i]		=	
					(v0c[i]*(1-u) + v1c[i]*u) * (1-v) +
					(v2c[i]*(1-u) + v3c[i]*u) * v; 
			}
		}

		if (grid->flags & RASTER_TRANSPARENT)
		{
			if (grid->flags & RASTER_MOVING)
			{
				nSample->opacity[i] 	=
					((v0c[opacityIdx]*(1-jt) + v0c[displacement + opacityIdx]*jt)*(1-u) +
					 (v1c[opacityIdx]*(1-jt) + v1c[displacement + opacityIdx]*jt)*u)*(1-v) +
					((v2c[opacityIdx]*(1-jt) + v2c[displacement + opacityIdx]*jt)*(1-u) +
					 (v3c[opacityIdx]*(1-jt) + v3c[displacement + opacityIdx]*jt)*u)*v;
			}
			else
			{
				nSample->opacity[i]		=	
					(v0c[opacityIdx]*(1-u) + v1c[opacityIdx]*u) * (1-v) +
					(v2c[opacityIdx]*(1-u) + v3c[opacityIdx]*u) * v; 
			}
		}

	}

	if (grid->flags & RASTER_MATTE)
	{
		// Negate it (for some reason). Figure out why.
		//
		mulvf(nSample->opacity, -1.0);
		
		movvv(pixel->first.opacity, nSample->opacity);
	}
}

void
CStochastic::drawPixel(
	__in CRasterGrid* grid,
	__in CPixel* pixel,
	__in float z,
	__in float u,
	__in float v,
	__in const float* v0,
	__in const float* v1,
	__in const float* v2,
	__in const float* v3,
	__in bool useZMid,
	__in int displacement)
{
	CFragment *nSample = NULL; 
	
	if (z < pixel->z) 
	{
		if (!(grid->flags & RASTER_TRANSPARENT))
		{
			updateOpaque(pixel, z); 	
			nSample 				=	&pixel->last;										
		}
		else
		{
			findSample(&nSample, pixel, z); 							
		}
		
		nSample->z = z;		
		
		colorOpacityUpdate(nSample, pixel, grid, u, v, v0 + 3, v1 + 3, v2 + 3, v3 + 3, displacement);	

		if (CRenderer::numExtraSamples > 0)
		{
			drawExtraSamples(nSample, pixel->jt, grid, u, v, v0, v1, v2, v3, displacement); 	
		}
		
		if (grid->flags & RASTER_TRANSPARENT)
		{
			updateTransparent(pixel, nSample, useZMid);	
		}
		else
		{
			// Opaque.
			//
			useZMid ? depthFilterIfZMid(pixel) :
					  depthFilterIfZMin(pixel);														
			
			pixel->z = z;		
			
			useZMid ? depthFilterTouchNodeZMid(pixel, z) :
					  depthFilterTouchNodeZMin(pixel, z);														
		}
	}
	else if (!(grid->flags & RASTER_TRANSPARENT))
	{
		// Failed Z-test and we're opaque:
		//
		useZMid ? depthFilterElseZMid(pixel, z) :
				  depthFilterElseZMin(pixel, z);
	}
}

void
CStochastic::drawExtraSamples(
	__out CFragment* nSample,
	__in float jt,
	__in CRasterGrid* grid,
	__in float u,
	__in float v,
	__in const float* v0,
	__in const float* v1,
	__in const float* v2,
	__in const float* v3,
	__in int displacement)
{													
	const	float	*s0	=	v0+10;													
	const	float	*s1	=	v1+10;													
	const	float	*s2	=	v2+10;													
	const	float	*s3	=	v3+10;													

	for (int i = 0; i < CRenderer::numExtraSamples; ++i)
	{
		if (grid->flags & RASTER_MOVING)
		{
			// We have motion blur, interpolate in time as well as space.
			//
			nSample->extraSamples[i] =
				((s0[i]*(1-jt)+s0[displacement]*jt)*(1-u) + (s1[i]*(1-jt)+s1[displacement]*jt)*u)*(1-v)	+
				((s2[i]*(1-jt)+s2[displacement]*jt)*(1-u) + (s3[i]*(1-jt)+s3[displacement]*jt)*u)*v;
		}
		else
		{
			// No motion blur.
			//
			nSample->extraSamples[i] =
				(s0[i]*(1-u) + s1[i]*u) * (1-v)	+
				(s2[i]*(1-u) + s3[i]*u) * v;
		}
	}
}


//////////////////////////////////////////////////////////////////////////////////////////
//This function is the entry point that checks if the pixel passes a depth test and if we need 
// to shade the grid or not.
// Returns:
//
//  true if execution should continue in caller.
//
bool
CStochastic::drawPixelCheck(
 	__in CRasterGrid* grid,
	__in CPixel* pixel,
	__in float z,
	__in float u,
	__in float v,
	__in const float* v0,
	__in const float* v1,
	__in const float* v2,
	__in const float* v3,
	__in int displacement)
{
	// Use ZMin or ZMid?
	//
	bool useZMid = false;

	// TODO: figure out what the hell this means.
	//
	if(grid->flags & (RASTER_DEPTHFILT_MASK << RASTER_HIGHBITS_SHIFT))
	{
		useZMid = true;
	}
	
	// We're not shaded yet, so if we pass the depth test, we need to go back
	// and shade the grid.
	//
	if (grid->flags & RASTER_UNSHADED)
	{
		// Assume no-shade by default.
		//
		bool shouldShade = false;

		// Do we pass the Z-test? (Are we nearer than the farthest opaque Z-value?)
		//
		if (z < pixel->z)
		{
			shouldShade = true;
		}
		else
		{
			// Didn't pass Z-test. Should we shade anyway?
			//
			if ((grid->flags & RASTER_UNDERCULL) && (grid->flags & RASTER_SHADE_HIDDEN))
			{
				shouldShade = true;
			}
		}

		if (shouldShade)
		{
			shadeGrid(grid, FALSE);										
			rasterDrawPrimitives(grid); 								
			return false; // TODO													
		}
		else
		{
			// Failed the shading test:
			//
			if (useZMid)
			{
				depthFilterElseZMid(pixel, z);
			}
			else
			{
				depthFilterElseZMin(pixel, z);
			}
			return true;
		}
	}
	else
	{
		drawPixel(grid, pixel, z, u, v,
			v0, v1, v2, v3,
			useZMid, displacement);
		return true;
	}
}

// This function is called when an opaque fragment is inserted
// Note: On the assumption that the opacity really is nearly opaque, we don't really need
// to bother messing with pixel->last though it might technicaly be more correct to do so
// so these sections are commented out in updateOpaque and updateTransparent

void
CStochastic::updateOpaque(
	__in CPixel* pixel,
	__in float z) 
{															
	CFragment *cSample=pixel->last.prev;					
	while(cSample->z > z) {									
		CFragment *nSample	=	cSample->prev;				
		nSample->next		=	&pixel->last;				
		pixel->last.prev	=	nSample;					
		assert(cSample != &pixel->first);					
		deleteFragment(cSample);							
		cSample				=	nSample;					
	}														
	/*initv(pixel->last.accumulatedOpacity,1);*/			
	pixel->update			=	cSample;					
}



///////////////////////////////////////////////////////////////////////
// Class				:	CStochastic
// Method				:	rasterDrawPrimitives
// Description			:
/// \brief					Draw bunch of primitives
// Return Value			:	-
// Comments				:
void		
CStochastic::rasterDrawPrimitives(
	__in CRasterGrid *grid)
{
	// TODO: REFACTOR to use a real function!
	//

// TODO
	// Shade _very_ early if we know we are guaranteed to have to anyway
	// This also solves issues with grids viewed exactly side-on never
	// being shaded when baking
	// Note: we retain the pre-rasterization method for the case where RASTER_SHADE_HIDDEN
	// is not set, and for the cases where 1 sidedness must be respected
	
	if (grid->flags & RASTER_UNDERCULL &&
		grid->flags & RASTER_UNSHADED)
	{
		const	int _flags = grid->flags;
		if ((_flags & RASTER_SHADE_HIDDEN) &&
			(_flags & (RASTER_DRAW_FRONT | RASTER_SHADE_BACKFACE)) &&
			(_flags & (RASTER_DRAW_BACK | RASTER_SHADE_BACKFACE))) {
			
			shadeGrid(grid,FALSE);
			rasterDrawPrimitives(grid);
			return;
		}
	}

	// Offset in vertex data to displacement part. (i.e. to the next "logical" vertex image)
	// TODO: redesign this.
	//
	int displacement = 10;
	if (grid->flags & RASTER_EXTRASAMPLES)
	{
		displacement += CRenderer::numExtraSamples;
	}

	// Extreme motion blur/DOF.
	//
	if (grid->flags & RASTER_XTREME)
	{
		const int xres = sampleWidth - 1;
		const int yres = sampleHeight - 1;
		
		int xmin =	grid->xbound[0] - left;
		int xmax =	grid->xbound[1] - left;
		int ymin =	grid->ybound[0] - top;
		int ymax =	grid->ybound[1] - top;
		
		xmin	=	max(xmin,0);		// Clamp the bound in the current bucket
		ymin	=	max(ymin,0);
		xmax	=	min(xmax,xres);
		ymax	=	min(ymax,yres);
		
		int x = 0;
		int y = 0;
		
		for (y = ymin; y <= ymax; y++) 
		{
			for (x = xmin; x <= xmax; x++) 
			{
				CPixel		*pixel		=	fb[y] + x;
				int 		i,j;
		
				const int	*bounds 	=	grid->bounds;
		
				const float *vertices	=	grid->vertices;
				const	int udiv		=	grid->udiv;
		
				const	int vdiv		=	grid->vdiv;
				const	int flags		=	grid->flags;
		
				for (j = 0; j < vdiv; j++)
				{
					for (i = 0;
						 i < udiv;
						 i++, bounds += 4, vertices += numVertexSamples)
					{
						if (x+left < bounds[0]) 	continue;
						if (x+left > bounds[1]) 	continue;
						if (y+top < bounds[2])		continue;
						if (y+top > bounds[3])		continue;

						if (grid->flags & RASTER_LOD)
						{
							// If failed the LOD check, skip this grid vertex.
							//
							if (!lodCheck(grid, pixel))
							{
								continue;
							}
						}

						// focal blur stuff (DOF)
						//
						float v0d = 0;
						float v1d = 0;
						float v2d = 0;
						float v3d = 0;

						vector	v0focTmp = {0};
						vector	v1focTmp = {0};
						vector	v2focTmp = {0};
						vector	v3focTmp = {0};

						// mo blur stuff
						vector	v0movTmp = {0};
						vector	v1movTmp = {0};
						vector	v2movTmp = {0};
						vector	v3movTmp = {0};
						// --------------
						
						const float *v0 =	vertices;
						const float *v1 =	vertices + numVertexSamples;
						const float *v2 =	v1 + udiv*numVertexSamples;
						const float *v3 =	v2 + numVertexSamples;
		
						if (grid->flags & RASTER_FOCALBLUR)
						{
							v0d =	v0[9];
							v1d =	v1[9];
							v2d =	v2[9];
							v3d =	v3[9];
						}
		
						if (grid->flags & RASTER_MOVING)
						{
							interpolatev(v0movTmp,v0,v0+displacement,pixel->jt);
							interpolatev(v1movTmp,v1,v1+displacement,pixel->jt);
							interpolatev(v2movTmp,v2,v2+displacement,pixel->jt);
							interpolatev(v3movTmp,v3,v3+displacement,pixel->jt);
							v0		=	v0movTmp;
							v1		=	v1movTmp;
							v2		=	v2movTmp;
							v3		=	v3movTmp;
						}
		
						if (grid->flags & RASTER_FOCALBLUR)
						{
							v0focTmp[COMP_X]	=	v0[COMP_X] + pixel->jdx*v0d;
							v1focTmp[COMP_X]	=	v1[COMP_X] + pixel->jdx*v1d;
							v2focTmp[COMP_X]	=	v2[COMP_X] + pixel->jdx*v2d;
							v3focTmp[COMP_X]	=	v3[COMP_X] + pixel->jdx*v3d;
			
							v0focTmp[COMP_Y]	=	v0[COMP_Y] + pixel->jdy*v0d;
							v1focTmp[COMP_Y]	=	v1[COMP_Y] + pixel->jdy*v1d;
							v2focTmp[COMP_Y]	=	v2[COMP_Y] + pixel->jdy*v2d;
							v3focTmp[COMP_Y]	=	v3[COMP_Y] + pixel->jdy*v3d;
			
							v0focTmp[COMP_Z]	=	v0[COMP_Z];
							v1focTmp[COMP_Z]	=	v1[COMP_Z];
							v2focTmp[COMP_Z]	=	v2[COMP_Z];
							v3focTmp[COMP_Z]	=	v3[COMP_Z];
			
							v0					=	v0focTmp;
							v1					=	v1focTmp;
							v2					=	v2focTmp;
							v3					=	v3focTmp;
						}

						// TODO: clean
						float z = 0;
						float u = 0;
						float v = 0;
		
						// Check the orientation of the quad.
						//
						float a = area(
							v0[COMP_X],
							v0[COMP_Y],
							v1[COMP_X],
							v1[COMP_Y],
							v2[COMP_X],
							v2[COMP_Y]);
						
						if (fabsf(a) < C_EPSILON) 
						{
							a = area(
								v1[COMP_X],
								v1[COMP_Y],
								v3[COMP_X],
								v3[COMP_Y],
								v2[COMP_X],
								v2[COMP_Y]);
						}
						
						// Back face culling.
						//
						if (!shouldDrawBack(grid->flags))
						{
							continue;
						}

						// Use less-than (<) in the comparison of checkPixel
						// if the area 'a' is positive.
						//
						if (!checkPixel(a > 0, pixel, v0, v1, v2, v3, &z, &u, &v))
						{
							continue;
						}
	
						v0	=	vertices;
						v1	=	v0 + numVertexSamples;
						v2	=	v1 + udiv*numVertexSamples;
						v3	=	v2 + numVertexSamples;
	
						if (!drawPixelCheck(grid, pixel, z, u, v, v0, v1, v2, v3, displacement))
						{
							return;
						}
					}
					vertices	+=	numVertexSamples;
				}
			}
		}
	}
	else
	{
		// Not so extreme motion blur or DOF.
		//
		assert(!"Not yet implemented");
	}

	// etc. etc.
	
#if 0
// Instantiate the dispatch switch
#define DEFINE_STOCHASTIC_SWITCH
	#include "stochasticPrimitives.h"
#undef DEFINE_STOCHASTIC_SWITCH
#endif

}



// Note: due to the way we insert samples, we may have inserted a new one behind the 
// maximum opaque depth - in which case we must flush the new sample and everything
// beind it.  Otherwise, we need to update accumulated opacity, and cull samples
// behind the point where we become opaque

#define debugTransparencyStack(cSample) {						\
	printf(">> cull opac %.6f %.6f %.6f\n",O[0],O[1],O[2]);		\
	CFragment *ds=cSample;										\
	while(ds) {													\
		printf("opac %.6f %.6f %.6f\tropac %.6f %.6f %.6f",ds->opacity[0],ds->opacity[1],ds->opacity[2],	\
			ds->accumulatedOpacity[0],ds->accumulatedOpacity[1],ds->accumulatedOpacity[2]);					\
		if(ds==nSample) {										\
			if(ds==&pixel->last) printf("*");					\
			printf("*\n");										\
		} else {												\
			printf("\n");										\
		}														\
		ds = ds->prev;											\
	}															\
	printf("\n");												\
}

#define DEFINE_STOCHASTIC_FUNCTIONS
//#include "stochasticPrimitives.h"
#undef DEFINE_STOCHASTIC_FUNCTIONS

#undef depthFilterIfZMin
#undef depthFilterElseZMin
#undef depthFilterIfZMid
#undef depthFilterElseZMid


///////////////////////////////////////////////////////////////////////
// Class				:	CStochastic
// Method				:	rasterEnd
// Description			:
/// \brief					Get the image from the screen
// Return Value			:	-
// Comments				:
void		CStochastic::rasterEnd(float *fb2,int noObjects) {
	int				i;
	const int		xres					=	width;
	const int		yres					=	height;
	float			*tmp;
	
	
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


	// Collapse the samples (transparency composite)
	const int		numExtraNonCompChannels		=	CRenderer::numExtraNonCompChannels;
	const int		numExtraCompChannels		=	CRenderer::numExtraCompChannels;

	// pull local for speed
	vector			zvisibilityThreshold;
	movvv(zvisibilityThreshold,CRenderer::zvisibilityThreshold);

	const int		filterWidth				=	CRenderer::pixelXsamples + 2*CRenderer::xSampleOffset;
	const int		filterHeight			=	CRenderer::pixelYsamples + 2*CRenderer::ySampleOffset;
	const float		halfFilterWidth			=	filterWidth*0.5f;
	const float		halfFilterHeight		=	filterHeight*0.5f;
	const int		pixelSize				=	6	+ CRenderer::numExtraSamples;	// alpha + depth + color + opacity + extra samples
	float			*fbs					=	(float *) ralloc(totalWidth*totalHeight*pixelSize*sizeof(float),threadMemory);
	const int		sampleLineDisplacement	=	CRenderer::pixelXsamples*pixelSize;
	int				sx,sy;
	
	// 0	=	alpha
	// 1	=	z;
	// 2-4	=	color
	// 5	=	z2
	for (int y=0;y<sampleHeight;y++) {
		CPixel	*cPixel		=	fb[y];
		float	*cFb		=	&fbs[y*totalWidth*pixelSize];
		vector	ropacity;

		for (i=sampleWidth;i>0;i--,cPixel++,cFb+=pixelSize) {
			CFragment	*cSample;
			CFragment	*oSample;
			float		*Z			=	&cFb[1];
			float		*C			=	&cFb[2];
			//float		*O			=	&cFb[5];
			vector		O;
			float		*Z2			=	&cFb[5];
			float		*ES			=	&cFb[6];
 			
			assert(cPixel->first.z == -C_INFINITY);

			// We re-use cPixel->first as a marker as to whether the pixel has any matte samples,
			// cPixel->last ise really used, but cPixel->first is not (it's always skipped in the composite),
			// so this is safe to do
			
			///////////////////////////////////////////////
			// Opacity thresholding for non composited aovs
			///////////////////////////////////////////////
			
			{
			// Q: Why are we recalculating z
			// A: because maintaining an accurate z for transparent samples
			//    combined with zthreshold is very awkward.
			//    We desire z to have the same evaluation properties as a zmin
			//    aov, which will account for transparent samples.  So we pass
			//    thru to grab the right value.  In fully opaque scenes this
			//    should not add significant additional workload
			
			#define NonCompositeSampleLoop() 											\
				const float *sampleExtra	= cSample->extraSamples;					\
				for(int es = 0; es < numExtraNonCompChannels; es++) {					\
					const int sampleOffset	= CRenderer::nonCompChannelOrder[es*4];		\
					const int numSamples	= CRenderer::nonCompChannelOrder[es*4+1];
			
			#define copyNonCompSamples(src)												\
				float *ESD				= ES + sampleOffset;							\
				const float *ESS		= src;											\
				for(int ess=numSamples;ess>0;ess--) *ESD++ = *ESS++;

			#define checkZThreshold()		(opacity[0] > zvisibilityThreshold[0]) || (opacity[1] > zvisibilityThreshold[1]) || (opacity[2] > zvisibilityThreshold[2])
			#define checkMatteZThreshold()	(1+opacity[0] > zvisibilityThreshold[0]) || (1+opacity[1] > zvisibilityThreshold[1]) || (1+opacity[2] > zvisibilityThreshold[2])
				
			cSample	=	cPixel->first.next;
			
			if (cPixel->first.opacity[0] >= 0 || cPixel->first.opacity[1] >= 0 || cPixel->first.opacity[2] >= 0) { 		// Pixel has no Matte
								
				for (;cSample!=NULL;) {
					const float *opacity	= cSample->opacity;

					// copy when we see sufficiently opaque sample, check against zthreshold
					if (checkZThreshold()) {
						NonCompositeSampleLoop()
							copyNonCompSamples(sampleExtra + sampleOffset);
						}
						
						Z[0] = cSample->z;
						// We've found our sample quit out
						break;
					}
					cSample		=	cSample->next;
				}
			} else {
				for (;cSample!=NULL;) {
					const float	*color		= cSample->color;
					const float *opacity	= cSample->opacity;
	
					int isMatte = (opacity[0] < 0 || opacity[1] < 0 || opacity[2] < 0);
						// Matte
					
					if (checkMatteZThreshold()) {
						// Copy default non-composited AOVs - default values unless ignoring matte
						NonCompositeSampleLoop()
							const int matteMode		= CRenderer::nonCompChannelOrder[es*4+2];
							if (isMatte && matteMode) {
								copyNonCompSamples(CRenderer::sampleDefaults + sampleOffset);
							} else {
								copyNonCompSamples(sampleExtra + sampleOffset);
							}
						}
						// FIXME: respect matte mode for main display (also reset it)
						
						//if (isMatte && matteMode)
						Z[0]	=	cSample->z;
						// We've found our sample, quit out	
						break;
					}
						
					cSample		=	cSample->next;
				}
			}
			
			// Deal with no samples, and finding a second sample for midpoint
			
			if (cSample == NULL) {
				// No samples that satisfy zthreshold, use defaults
				for(int es = 0; es < numExtraNonCompChannels; es++) {
					const int sampleOffset	= CRenderer::nonCompChannelOrder[es*4];
					const int numSamples	= CRenderer::nonCompChannelOrder[es*4+1];
					copyNonCompSamples(CRenderer::sampleDefaults + sampleOffset);
				}
				Z[0]	=	C_INFINITY;
				Z2[0]	=	C_INFINITY;
			} else if (CRenderer::depthFilter == DEPTH_MID) {
				
				// Find the second sample for midpoint, if needed
				// Q: Why not just use zold?
				// A: It doesn't take account of transparent samples
				
				for (;cSample!=NULL;cSample=cSample->next) {
					const float *opacity	= cSample->opacity;
	
					if (opacity[0] < 0 || opacity[1] < 0 || opacity[2] < 0) {
						if (checkMatteZThreshold()) {
							// FIXME: respect matteMode
							Z2[0]	=	cSample->z;
							break;
						}
					} else {
						if (checkZThreshold()) {
							// FIXME: respect matteMode
							Z2[0]	=	cSample->z;
							break;
						}
					}
				}
				if (cSample == NULL) {
					// no second sample, use the first (we have one, 
					// otherwise we'd be in the first case)
					Z2[0]	=	Z[0];
				}
				Z2[0] = max(Z2[0],cPixel->zold);
 			}
			
			#undef NonCompositeSampleLoop
			#undef copyNonCompSamples
			#undef checkZThreshold
			#undef checkMatteZThreshold

			// clip-correct the depth components
			if (Z[0] >= CRenderer::clipMax)			Z[0]	=	C_INFINITY;
			if (Z2[0] >= CRenderer::clipMax)		Z2[0]	=	C_INFINITY;	
			}
			
			///////////////////////////////////////////////
			// Composite loop for composited aovs, rgba
			// Note: we also remove the samples here
			///////////////////////////////////////////////
			
			{
			#define compositeSampleLoop()										\
				const float *sampleExtra = cSample->extraSamples;				\
				for(int es = 0; es < numExtraCompChannels; es++) {				\
					const int sampleOffset = CRenderer::compChannelOrder[es*4];
						
			cSample	=	cPixel->first.next;
			
			if (!(cPixel->first.opacity[0] < 0 || cPixel->first.opacity[1] < 0 || cPixel->first.opacity[2] < 0)) {
				// Pixel samples have no Mattes
			
				// Get the base color and opacity
				movvv(C,cSample->color);
				movvv(O,cSample->opacity);
				ropacity[0]	=	1-O[0];
				ropacity[1]	=	1-O[1];
				ropacity[2]	=	1-O[2];
				
				// If this sample has no valid samples, this will fill in the sample defaults
				// because pixel->last's AOVs get initialized to the defaults
				compositeSampleLoop()
					movvv(ES + sampleOffset,sampleExtra + sampleOffset);
				}
				
				// Transparency collapse, and delete samples
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
					
					// Composite extra samples
					compositeSampleLoop()
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
			} else {
				// We have mattes in the stack
				
				// Get the base color, opacity and extra samples
				// This will install defaults if there are no valid samples
				if (cSample->opacity[0] < 0 || cSample->opacity[1] < 0 || cSample->opacity[2] < 0) {
					// Matte base sample
					initv(C,0);
					initv(O,0);
					ropacity[0]	=	1+cSample->opacity[0];
					ropacity[1]	=	1+cSample->opacity[1];
					ropacity[2]	=	1+cSample->opacity[2];
					
					// Composite AOVs with ignore matte flag
					compositeSampleLoop()
						const int matteMode		= CRenderer::compChannelOrder[es*4+2];
						if (matteMode)		initv(ES + sampleOffset,0);
						else				movvv(ES + sampleOffset,sampleExtra + sampleOffset);
					}
				} else {
					// Non-matte base sample
					movvv(C,cSample->color);
					movvv(O,cSample->opacity);
					ropacity[0]	=	1-O[0];
					ropacity[1]	=	1-O[1];
					ropacity[2]	=	1-O[2];
										
					// Composite extra samples
					compositeSampleLoop()
						movvv(ES + sampleOffset,sampleExtra + sampleOffset);
					}
				}
				
				// Transparency collapse, and delete samples
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
						compositeSampleLoop()
							const int matteMode	=	CRenderer::compChannelOrder[es*4+2];
							if (!matteMode)		 	movvv(ES + sampleOffset,sampleExtra + sampleOffset);
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
						
						compositeSampleLoop()
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
			cFb[0]			=	((O[0] + O[1] + O[2])*0.3333333333333333f);
		}
	}
	}

	// Note: at this point, all the subpixel samples are valid
	// We could output subpixel samples here if we wish to support a subpixel hider
	
	// Clear the memory first
	for (tmp=fb2,i=xres*yres*CRenderer::numSamples;i>0;i--)	*tmp++	=	0;

	// Perform non area-filtering for depth
	// Note: technically, this should filter in the specified width/height
	// but > 1 pixel doesn't really make sense
	switch(CRenderer::depthFilter) {
	case DEPTH_MIN:	
		
		for (int y=0;y<yres;y++) {
			float			*cPixelLine		=	&fb2[y*xres*CRenderer::numSamples];
			float			*cPixel			=	cPixelLine;
			float			*cSampleLine	=	&fbs[((y*CRenderer::pixelYsamples+CRenderer::ySampleOffset)*totalWidth+CRenderer::xSampleOffset)*pixelSize];	
			float			*cSample		=	cSampleLine;

			for (i=0;i<xres;i++,cPixel+=CRenderer::numSamples,cSample+=CRenderer::pixelXsamples*pixelSize) {
				cPixel[4]		=	cSample[1];		// initialize with first sample
			}
			
			cSample		=	cSampleLine;
			for (sy=0;sy<CRenderer::pixelYsamples;sy++) {
				cPixel = cPixelLine;
				for (i=0;i<xres;i++) {			
					for (sx=0;sx<CRenderer::pixelXsamples;sx++,cSample+=pixelSize) {
						cPixel[4]		=	min(cPixel[4],cSample[1]);
					}
					cPixel += CRenderer::numSamples;
				}
				//cSample += CRenderer::xSampleOffset*pixelSize;
				cSample = cSampleLine + totalWidth*pixelSize;
				cSampleLine = cSample;
			}
		}

		break;
	case DEPTH_MAX:
		
		for (int y=0;y<yres;y++) {
			float			*cPixelLine		=	&fb2[y*xres*CRenderer::numSamples];
			float			*cPixel			=	cPixelLine;
			float			*cSampleLine	=	&fbs[((y*CRenderer::pixelYsamples+CRenderer::ySampleOffset)*totalWidth+CRenderer::xSampleOffset)*pixelSize];	
			float			*cSample		=	cSampleLine;

			for (i=0;i<xres;i++,cPixel+=CRenderer::numSamples,cSample+=CRenderer::pixelXsamples*pixelSize) {
				cPixel[4]		=	cSample[1];		// initialize with first sample
			}
			
			cSample		=	cSampleLine;
			for (sy=0;sy<CRenderer::pixelYsamples;sy++) {
				cPixel = cPixelLine;
				for (i=0;i<xres;i++) {			
					for (sx=0;sx<CRenderer::pixelXsamples;sx++,cSample+=pixelSize) {
						cPixel[4]		=	max(cPixel[4],cSample[1]);
					}
					cPixel += CRenderer::numSamples;
				}
				//cSample += CRenderer::xSampleOffset*pixelSize;
				cSample = cSampleLine + totalWidth*pixelSize;
				cSampleLine = cSample;
			}
		}

		break;
	case DEPTH_AVG:
		
		for (int y=0;y<yres;y++) {
			float			*cPixelLine		=	&fb2[y*xres*CRenderer::numSamples];
			float			*cPixel			=	cPixelLine;
			float			*cSampleLine	=	&fbs[((y*CRenderer::pixelYsamples+CRenderer::ySampleOffset)*totalWidth+CRenderer::xSampleOffset)*pixelSize];	
			float			*cSample		=	cSampleLine;

			for (i=0;i<xres;i++,cPixel+=CRenderer::numSamples,cSample+=CRenderer::pixelXsamples*pixelSize) {
				cPixel[4]		=	0;		// initialize with zero
			}
			
			cSample		=	cSampleLine;
			for (sy=0;sy<CRenderer::pixelYsamples;sy++) {
				cPixel = cPixelLine;
				for (i=0;i<xres;i++) {			
					for (sx=0;sx<CRenderer::pixelXsamples;sx++,cSample+=pixelSize) {
						cPixel[4]		+=	cSample[1];
					}
					cPixel += CRenderer::numSamples;
				}
				//cSample += CRenderer::xSampleOffset*pixelSize;
				cSample = cSampleLine + totalWidth*pixelSize;
				cSampleLine = cSample;
			}
		}
		
		{
			const float normalizer = 1.0f/((float)CRenderer::pixelXsamples*(float)CRenderer::pixelYsamples);
			for (int y=0;y<yres;y++) {
				float			*cPixel		=	&fb2[y*xres*CRenderer::numSamples];
				for (i=0;i<xres;i++,cPixel+=CRenderer::numSamples) {
					cPixel[4] 	*= normalizer;
				}
			}
		}

		break;
	
	case DEPTH_MID:
		/// FIXME: for midpoint should be working out front most 2 planes (min of front, min of 2nd)
		// and do midpoint on the - need extra working space to do this.

		for (int y=0;y<yres;y++) {
			float			*cPixelLine		=	&fb2[y*xres*CRenderer::numSamples];
			float			*cPixel			=	cPixelLine;
			float			*cSampleLine	=	&fbs[((y*CRenderer::pixelYsamples+CRenderer::ySampleOffset)*totalWidth+CRenderer::xSampleOffset)*pixelSize];	
			float			*cSample		=	cSampleLine;

			for (i=0;i<xres;i++,cPixel+=CRenderer::numSamples,cSample+=CRenderer::pixelXsamples*pixelSize) {
				cPixel[4]		=	0;		// initialize with zero
			}
			
			cSample		=	cSampleLine;
			for (sy=0;sy<CRenderer::pixelYsamples;sy++) {
				cPixel = cPixelLine;
				for (i=0;i<xres;i++) {			
					for (sx=0;sx<CRenderer::pixelXsamples;sx++,cSample+=pixelSize) {
						cPixel[4]		+=	0.5f*(cSample[1] + cSample[5]);		// FIXME: this is wrong, we're doing average on midpoint values
					}
					cPixel += CRenderer::numSamples;
				}
				//cSample += CRenderer::xSampleOffset*pixelSize;
				cSample = cSampleLine + totalWidth*pixelSize;
				cSampleLine = cSample;
			}
		}
		
		{
			const float normalizer = 1.0f/((float)CRenderer::pixelXsamples*(float)CRenderer::pixelYsamples);
			for (int y=0;y<yres;y++) {
				float			*cPixel		=	&fb2[y*xres*CRenderer::numSamples];
				for (i=0;i<xres;i++,cPixel+=CRenderer::numSamples) {
					cPixel[4] 	*= normalizer;
				}
			}
		}
	}


	// FIXME: Filter non-composited samples
	if (numExtraNonCompChannels > 0) {
	
	}

	// Filter the samples
	for (int y=0;y<yres;y++) {
		for (sy=0;sy<filterHeight;sy++) {
			for (sx=0;sx<filterWidth;sx++) {
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
					
					// Filter the extra samples here
					for (es=0;es<CRenderer::numExtraSamples;es++) {
						pixelLine[5+es]			+=	filterResponse*sampleLine[6+es];
					}

					// Advance
					pixelLine					+=	CRenderer::numSamples;
					sampleLine					+=	sampleLineDisplacement;
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
// Description			:
/// \brief					This function is used to output a depth sample
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
// Description			:
/// \brief					This function is used to output a depth sample
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
// Description			:
/// \brief					This function is used to output the last sample
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

