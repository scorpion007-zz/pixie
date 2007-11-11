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

// This is the portion of Pixie that draws a point into the stochastic


int			i;
const int	*bounds		=	grid->bounds;
const float	*vertices	=	grid->vertices;
const float	*sizes		=	grid->sizes;
const	int	xres		=	sampleWidth - 1;
const	int	yres		=	sampleHeight - 1;


///////////////////////////////////////////////////////////////////////////////////////////
//
//   Here're some macros that make the rasterization job easier for us
//
///////////////////////////////////////////////////////////////////////////////////////////

// Shade _very_ early if we know we are guaranteed to have to anyway
// Points are always facing the screen, so there's no point checking if
// they're visible before deciding to shade if RASTER_SHADE_HIDDEN is true

#ifdef STOCHASTIC_UNSHADED
#ifdef STOCHASTIC_UNDERCULL
	if (grid->flags & RASTER_SHADE_HIDDEN) {
		shadeGrid(grid,FALSE);
		rasterDrawPrimitives(grid);
		return;
	}
#endif
#endif


#ifdef STOCHASTIC_EXTRA_SAMPLES
#define	displacement	(10 + CRenderer::numExtraSamples)
#else
#define	displacement	10
#endif



///////////////////////////////////////////////////////////////////////////////////////////
//  This macro checks the pixel LOD against the object LOD level
#ifdef STOCHASTIC_LOD
	const float importance = grid->object->attributes->lodImportance;

	#define lodCheck()																			\
		if (importance >= 0) {																	\
			if (pixel->jimp > importance)		continue;										\
		} else {																				\
			if ((1-pixel->jimp) >= -importance)	continue;										\
		}
#else
	#define lodCheck()
#endif




//////////////////////////////////////////////////////////////////////////////////////////
// The following macro is used to draw extra samples for each pixels if any
#ifdef STOCHASTIC_EXTRA_SAMPLES

#ifdef STOCHASTIC_MOVING
#define	drawExtraSamples()	{														\
	int				currentSample;													\
	const	float	*s0	=	v0+10;													\
	float			*dest;															\
																					\
	for (dest=nSample->extraSamples,currentSample=CRenderer::numExtraSamples;currentSample>0;currentSample--,s0++) {		\
		*dest++		=	(s0[0]*(1-jt)+s0[displacement]*jt);							\
	}																				\
}

#else
#define	drawExtraSamples()	{														\
	int				currentSample;													\
	const	float	*s0	=	v0+10;													\
	float			*dest;															\
																					\
	for (dest=nSample->extraSamples,currentSample=CRenderer::numExtraSamples;currentSample>0;currentSample--,s0++) {		\
		*dest++		=	s0[currentSample];											\
	}																				\
}
#endif

#else
#define	drawExtraSamples()
#endif





//////////////////////////////////////////////////////////////////////////////////////////
// This big ass macro is for computing the final color/opacity of a pixel
#ifndef STOCHASTIC_TRANSPARENT
// Non transparent
	#ifndef STOCHASTIC_MOVING
		// Non Moving
		#ifndef STOCHASTIC_MATTE
			// Non Matte
			#define colorOpacityUpdate()													\
				movvv(nSample->color,v0 + 3);												\
				initv(nSample->opacity,1);
		#else
			// Matte
			#define colorOpacityUpdate()													\
				initv(nSample->color,0);													\
				initv(nSample->opacity,-1);													\
				initv(pixel->first.opacity,-1);
		#endif
	#else
		// Moving
		#ifndef STOCHASTIC_MATTE
			// Non Matte
			#define colorOpacityUpdate()													\
				interpolatev(nSample->color,v0+3,v0+3+displacement,jt);						\
				initv(nSample->opacity,1);
		#else
			// Matte
			#define colorOpacityUpdate()													\
				initv(nSample->color,0);													\
				initv(nSample->color,-1);													\
				initv(pixel->first.opacity,-1);
		#endif
	#endif
#else
	// Transparent
	#ifndef STOCHASTIC_MOVING
		// Non Moving
		#ifndef STOCHASTIC_MATTE
			// Non Matte
			#define colorOpacityUpdate()													\
				movvv(nSample->color,v0+3);													\
				movvv(nSample->opacity,v0+6);
		#else
			// Matte
			#define colorOpacityUpdate()													\
				initv(nSample->color,0);													\
				initv(nSample->opacity,0);													\
				subvv(nSample->opacity,v0+6);												\
				movvv(pixel->first.opacity,nSample->opacity);
		#endif
	#else
		// Moving
		#ifndef STOCHASTIC_MATTE
			// Non Matte
			#define colorOpacityUpdate()													\
				interpolatev(nSample->color,v0+3,v0+3+displacement,jt);						\
				interpolatev(nSample->opacity,v0+6,v0+6+displacement,jt);
		#else
			// Matte
			#define colorOpacityUpdate()													\
				initv(nSample->color,0);													\
				interpolatev(nSample->opacity,v0+6,v0+6+displacement,jt);					\
				nSample->opacity[0] = -nSample->opacity[0];									\
				nSample->opacity[1] = -nSample->opacity[1];									\
				nSample->opacity[2] = -nSample->opacity[2];									\
				movvv(pixel->first.opacity,nSample->opacity);
		#endif
	#endif
#endif

#ifndef STOCHASTIC_TRANSPARENT
//    Non Transparent
#ifndef STOCHASTIC_MOVING
//	  Non Moving
#define	drawPixel() 																\
	if (z < pixel->z) {																\
		updateOpaque();																\
		nSample							=	&pixel->last;							\
		nSample->z						=	z;										\
		colorOpacityUpdate();														\
		drawExtraSamples();															\
		depthFilterIf();															\
		pixel->z						=	z;										\
		depthFilterTouchNode();														\
	} depthFilterElse();


#else
//	  Moving
#define	drawPixel() 																\
	if (z < pixel->z) {																\
		updateOpaque();																\
		nSample							=	&pixel->last;							\
		nSample->z						=	z;										\
		colorOpacityUpdate();														\
		drawExtraSamples();															\
		depthFilterIf();															\
		pixel->z						=	z;										\
		depthFilterTouchNode();														\
	} depthFilterElse();

#endif


#else
//    Transparent
#ifndef STOCHASTIC_MOVING
//	  Non Moving
#define	drawPixel() 																\
	if (z < pixel->z) {																\
		findSample(nSample,z);														\
		nSample->z						=	z;										\
		colorOpacityUpdate();														\
		drawExtraSamples();															\
		updateTransparent(depthFilterIf,depthFilterElse);							\
	}


#else
//	  Moving
#define	drawPixel() 																\
	if (z < pixel->z) {																\
		findSample(nSample,z);														\
		nSample->z						=	z;										\
		colorOpacityUpdate();														\
		drawExtraSamples();															\
		updateTransparent(depthFilterIf,depthFilterElse);							\
	}

#endif


#endif


//////////////////////////////////////////////////////////////////////////////////////////
// These macros decide whether we should draw a guad or not
#ifdef STOCHASTIC_UNSHADED
// We're not shaded yet, so if we pass the depth test, we need to back and shade the grid
// Note: we dealt with RASTER_SHADE_HIDDEN very early, no need to do so here
#define drawPixelCheck()															\
	if (z < pixel->z) {																\
		shadeGrid(grid,FALSE);														\
		rasterDrawPrimitives(grid);													\
		return;																		\
	} depthFilterElse();
#else
#define drawPixelCheck()															\
	CFragment *nSample;																\
	drawPixel();
#endif


///////////////////////////////////////////////////////////////////////////////////////////
//
//   Here's the code that actually iterates over the quads and draws them
//
///////////////////////////////////////////////////////////////////////////////////////////

// Iterate over every quad
for (i=grid->numVertices;i>0;i--,vertices+=numVertexSamples,bounds+=4,sizes+=2) {

	// Trivial rejects
	if (bounds[1] < left)		continue;
	if (bounds[3] < top)		continue;
	if (bounds[0] >= right)		continue;
	if (bounds[2] >= bottom)	continue;

	int	xmin	=	bounds[0] - left;	// Convert the bound into the current bucket
	int	ymin	=	bounds[2] - top;
	int	xmax	=	bounds[1] - left;
	int	ymax	=	bounds[3] - top;

	xmin		=	max(xmin,0);		// Clamp the bound in the current bucket
	ymin		=	max(ymin,0);
	xmax		=	min(xmax,xres);
	ymax		=	min(ymax,yres);

	const float	*v0	=	vertices;
	int			x,y;
	for (y=ymin;y<=ymax;y++) {
		for (x=xmin;x<=xmax;x++) {
			CPixel			*pixel	=	fb[y]+x;

			lodCheck();
	
			const float		xcent	=	pixel->xcent;
			const float		ycent	=	pixel->ycent;
		
		
#ifdef STOCHASTIC_MOVING
			const	float	jt		=	pixel->jt;
			vector	v0movTmp;
			interpolatev(v0movTmp,v0,(v0+displacement),jt);
			v0						=	v0movTmp;
			const	float	size	=	sizes[0]*(1-jt) + sizes[1]*jt;
#else
			const	float	size	=	sizes[0];
#endif

#ifdef STOCHASTIC_FOCAL_BLUR
			vector	v0focTmp;
			v0focTmp[COMP_X]		=	v0[COMP_X] + pixel->jdx*vertices[9];
			v0focTmp[COMP_Y]		=	v0[COMP_Y] + pixel->jdy*vertices[9];
			v0focTmp[COMP_Z]		=	v0[COMP_Z];
			v0						=	v0focTmp;
#endif

			const	float	dx		=	xcent - v0[0];
			const	float	dy		=	ycent - v0[1];

			v0	=	vertices;

			if ((dx*dx + dy*dy) < (size*size)) {
				const	float	z	=	v0[2];

				drawPixelCheck();
			}
		}
	}
}



#undef	lodCheck
#undef	drawPixelCheck
#undef	drawPixel
#undef	drawExtraSamples
#undef	displacement
#undef	colorOpacityUpdate

