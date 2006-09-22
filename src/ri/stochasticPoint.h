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

// This is the portion of Pixie that draws a point into the stochastic

#ifdef STOCHASTIC_MOVING
#define	displacement	sampleDisplacement
#else
#define	displacement	10
#endif

#ifdef STOCHASTIC_LOD
	#define lodCheck()																			\
		if (importance >= 0) {																	\
			if (pixel->jimp > importance)		continue;										\
		} else {																				\
			if ((1-pixel->jimp) >= -importance)	continue;										\
		}
#else
	#define lodCheck()
#endif

// This macro draws a sample to the pixel buffer
#ifdef STOCHASTIC_EXTRA_SAMPLES

#ifdef STOCHASTIC_MOVING
#define	drawExtraSamples()	{														\
	int				currentSample;													\
	const	float	*s0	=	v0+10;													\
	float			*dest;															\
																					\
	for (dest=pixel->extraSamples,currentSample=numExtraSamples;currentSample>0;currentSample--,s0++) {		\
		*dest++		=	(s0[0]*(1-jt)+s0[displacement]*jt);							\
	}																				\
}

#else
#define	drawExtraSamples()	{														\
	int				currentSample;													\
	const	float	*s0	=	v0+10;													\
	float			*dest;															\
																					\
	for (dest=pixel->extraSamples,currentSample=numExtraSamples;currentSample>0;currentSample--,s0++) {		\
		*dest++		=	s0[currentSample];											\
	}																				\
}
#endif

#else
#define	drawExtraSamples()
#endif

#ifndef STOCHASTIC_TRANSPARENT
// Non transparent
	#ifndef STOCHASTIC_MOVING
		// Non Moving
		#ifndef STOCHASTIC_MATTE
			// Non Matte
			#define colorOpacityUpdate()													\
				movvv(nSample->color,v0c);													\
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
				interpolatev(nSample->color,v0c,v0c+displacement,jt);						\
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
				movvv(nSample->color,v0c);													\
				movvv(nSample->opacity,v0o);
		#else
			// Matte
			#define colorOpacityUpdate()													\
				initv(nSample->color,0);													\
				initv(nSample->opacity,0);													\
				subvv(nSample->opacity,v0o);												\
				movvv(pixel->first.opacity,nSample->opacity);
		#endif
	#else
		// Moving
		#ifndef STOCHASTIC_MATTE
			// Non Matte
			#define colorOpacityUpdate()													\
				interpolatev(nSample->color,v0c,v0c+displacement,jt);						\
				interpolatev(nSample->opacity,v0o,v0o+displacement,jt);
		#else
			// Matte
			#define colorOpacityUpdate()													\
				initv(nSample->color,0);													\
				interpolatev(nSample->opacity,v0o,v0o+displacement,jt);						\
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
		nSample							=	&pixel->last;							\
		colorOpacityUpdate();														\
		drawExtraSamples()															\
		depthFilterIf();															\
		pixel->z						=	z;										\
		touchNode(pixel->node,z);													\
	} depthFilterElse();


#else
//	  Moving
#define	drawPixel() 																\
	if (z < pixel->z) {																\
		nSample							=	&pixel->last;							\
		colorOpacityUpdate();														\
		drawExtraSamples()															\
		depthFilterIf();															\
		pixel->z						=	z;										\
		touchNode(pixel->node,z);													\
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
		drawExtraSamples()															\
	}


#else
//	  Moving
#define	drawPixel() 																\
	if (z < pixel->z) {																\
		findSample(nSample,z);														\
		nSample->z						=	z;										\
		colorOpacityUpdate();														\
		drawExtraSamples()															\
	}

#endif


#endif


#ifdef STOCHASTIC_UNSHADED
// We're not shaded yet, so if we pass the depth test, we need to back and shade the grid
#ifdef STOCHASTIC_UNDERCULL
#define drawPixelCheck()															\
	if (z < pixel->z || (grid->flags & RASTER_SHADE_HIDDEN)) {						\
		shadeGrid(grid,FALSE);														\
		rasterDrawPrimitives(grid);													\
		return;																		\
	} depthFilterElse();
#else
#define drawPixelCheck()															\
	if (z < pixel->z) {																\
		shadeGrid(grid,FALSE);														\
		rasterDrawPrimitives(grid);													\
		return;																		\
	} depthFilterElse();
#endif // undercull
#else
#define drawPixelCheck()															\
	CFragment *nSample;																\
	drawPixel();
#endif

v0		=	cPrimitive->v0;
v0c		=	v0+3;

#ifdef STOCHASTIC_TRANSPARENT
v0o		=	v0c+3;
#endif

xmin	=	cPrimitive->xbound[0] - left;
ymin	=	cPrimitive->ybound[0] - top;
xmax	=	cPrimitive->xbound[1] - left;
ymax	=	cPrimitive->ybound[1] - top;

xmin	=	max(xmin,0);
ymin	=	max(ymin,0);
xmax	=	min(xmax,xres);
ymax	=	min(ymax,yres);

for (y=ymin;y<=ymax;y++) {
	for (x=xmin;x<=xmax;x++) {
		CPixel			*pixel	=	fb[y]+x;

		lodCheck();

		const float		xcent	=	pixel->xcent;
		const float		ycent	=	pixel->ycent;
		
		
#ifdef STOCHASTIC_MOVING
		const	float	jt		=	pixel->jt;
		interpolatev(v0movTmp,v0,(v0+sampleDisplacement),jt);
		dv0						=	v0movTmp;
		const	float	size	=	cPrimitive->data[0].real*(1-jt) + cPrimitive->data[1].real*jt;
#else
		dv0						=	v0;
		const	float	size	=	cPrimitive->data[0].real;
#endif

#ifdef STOCHASTIC_FOCAL_BLUR
		v0focTmp[COMP_X]		=	dv0[COMP_X] + pixel->jdx*v0[9];
		v0focTmp[COMP_Y]		=	dv0[COMP_Y] + pixel->jdy*v0[9];
		v0focTmp[COMP_Z]		=	dv0[COMP_Z];
		dv0						=	v0focTmp;
#endif

		const	float	dx		=	xcent - dv0[0];
		const	float	dy		=	ycent - dv0[1];

		if ((dx*dx + dy*dy) < (size*size)) {
			const	float	z	=	dv0[2];
			drawPixelCheck();
		}
	}
}



#undef	lodCheck
#undef	drawPixelCheck
#undef	drawPixel
#undef	drawExtraSamples
#undef	displacement
#undef	colorOpacityUpdate

