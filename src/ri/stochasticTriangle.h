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

// This is the portion of Pixie that draws a triangle into the stochastic

#ifdef STOCHASTIC_EXTRA_SAMPLES
#define	displacement	sampleDisplacement
#else
#define	displacement	10
#endif

#ifndef	depthFilterIf
#define	depthFilterIf()
#endif

#ifndef	depthFilterElse
#define	depthFilterElse()
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

v0			=	cPrimitive->v0;
v0c			=	v0 + 3;


v1			=	(float *) cPrimitive->data[0].pointer;
v1c			=	v1 + 3;


v2			=	(float *) cPrimitive->data[1].pointer;
v2c			=	v2 + 3;


#ifdef STOCHASTIC_TRANSPARENT
v0o			=	v0c + 3;
v1o			=	v1c + 3;
v2o			=	v2c + 3;
#endif

xbound		=	cPrimitive->xbound;
ybound		=	cPrimitive->ybound;

// Define the draw pixel macro


// The following macro is used to draw extra samples for each pixels if any
#ifdef STOCHASTIC_EXTRA_SAMPLES
#ifdef STOCHASTIC_MOVING
#define	drawExtraSamples()	{																\
	int				currentSample;															\
	const	float	*s0	=	v0+10;															\
	const	float	*s1	=	v1+10;															\
	const	float	*s2	=	v2+10;															\
	float			*dest;																	\
																							\
	for (dest=pixel->extraSamples,currentSample=numExtraSamples;currentSample>0;currentSample--,s0++,s1++,s2++) {		\
		*dest++	=	(s0[0]*(1-jt)+s0[displacement]*jt)*v + (s1[0]*(1-jt) + s1[displacement]*jt)*(1-u-v) + (s2[0]*(1-jt) + s2[displacement]*jt)*u;	\
	}																						\
}

#else
#define	drawExtraSamples()	{																\
	int				currentSample;															\
	const	float	*s0	=	v0+10;															\
	const	float	*s1	=	v1+10;															\
	const	float	*s2	=	v2+10;															\
	float			*dest;																	\
																							\
	for (dest=pixel->extraSamples,currentSample=numExtraSamples;currentSample>0;currentSample--) {	\
		*dest++	=	(*s0++)*v + (*s1++)*(1-u-v) + (*s2++)*u;								\
	}																						\
}

#endif
#else
#define	drawExtraSamples()
#endif


#ifdef STOCHASTIC_MOVING
#ifdef STOCHASTIC_TRANSPARENT

// M T
#ifndef STOCHASTIC_MATTE
	#define colorOpacityUpdate()																\
		nSample->color[0]		=	(v0c[0]*(1-jt) + v0c[displacement+0]*jt)*v + (v1c[0]*(1-jt) + v1c[displacement+0]*jt)*(1-u-v) + (v2c[0]*(1-jt) + v2c[displacement+0]*jt)*u;				\
		nSample->color[1]		=	(v0c[1]*(1-jt) + v0c[displacement+1]*jt)*v + (v1c[1]*(1-jt) + v1c[displacement+1]*jt)*(1-u-v) + (v2c[1]*(1-jt) + v2c[displacement+1]*jt)*u;				\
		nSample->color[2]		=	(v0c[2]*(1-jt) + v0c[displacement+2]*jt)*v + (v1c[2]*(1-jt) + v1c[displacement+2]*jt)*(1-u-v) + (v2c[2]*(1-jt) + v2c[displacement+2]*jt)*u;				\
		nSample->opacity[0]		=	(v0o[0]*(1-jt) + v0o[displacement+0]*jt)*v + (v1o[0]*(1-jt) + v1o[displacement+0]*jt)*(1-u-v) + (v2o[0]*(1-jt) + v2o[displacement+0]*jt)*u;				\
		nSample->opacity[1]		=	(v0o[1]*(1-jt) + v0o[displacement+1]*jt)*v + (v1o[1]*(1-jt) + v1o[displacement+1]*jt)*(1-u-v) + (v2o[1]*(1-jt) + v2o[displacement+1]*jt)*u;				\
		nSample->opacity[2]		=	(v0o[2]*(1-jt) + v0o[displacement+2]*jt)*v + (v1o[2]*(1-jt) + v1o[displacement+2]*jt)*(1-u-v) + (v2o[2]*(1-jt) + v2o[displacement+2]*jt)*u;
#else
	#define colorOpacityUpdate()																\
		initv(nSample->color,0);																\
		nSample->opacity[0]		=	-((v0o[0]*(1-jt) + v0o[displacement+0]*jt)*v + (v1o[0]*(1-jt) + v1o[displacement+0]*jt)*(1-u-v) + (v2o[0]*(1-jt) + v2o[displacement+0]*jt)*u);			\
		nSample->opacity[1]		=	-((v0o[1]*(1-jt) + v0o[displacement+1]*jt)*v + (v1o[1]*(1-jt) + v1o[displacement+1]*jt)*(1-u-v) + (v2o[1]*(1-jt) + v2o[displacement+1]*jt)*u);			\
		nSample->opacity[2]		=	-((v0o[2]*(1-jt) + v0o[displacement+2]*jt)*v + (v1o[2]*(1-jt) + v1o[displacement+2]*jt)*(1-u-v) + (v2o[2]*(1-jt) + v2o[displacement+2]*jt)*u);			\
		movvv(pixel->first.opacity,nSample->opacity);
#endif

#define	drawPixel() 																			\
	if (z < pixel->z) {																			\
		const	float	jt		=	pixel->jt;													\
		findSample(nSample,z);																	\
		nSample->z				=	z;															\
		colorOpacityUpdate();																	\
	}

#else

// M, nT
#ifndef STOCHASTIC_MATTE
	#define colorOpacityUpdate()																\
		nSample->color[0]		=	(v0c[0]*(1-jt) + v0c[displacement+0]*jt)*v + (v1c[0]*(1-jt) + v1c[displacement+0]*jt)*(1-u-v) + (v2c[0]*(1-jt) + v2c[displacement+0]*jt)*u;				\
		nSample->color[1]		=	(v0c[1]*(1-jt) + v0c[displacement+1]*jt)*v + (v1c[1]*(1-jt) + v1c[displacement+1]*jt)*(1-u-v) + (v2c[1]*(1-jt) + v2c[displacement+1]*jt)*u;				\
		nSample->color[2]		=	(v0c[2]*(1-jt) + v0c[displacement+2]*jt)*v + (v1c[2]*(1-jt) + v1c[displacement+2]*jt)*(1-u-v) + (v2c[2]*(1-jt) + v2c[displacement+2]*jt)*u;				\
		nSample->opacity[0]		=	1;															\
		nSample->opacity[1]		=	1;															\
		nSample->opacity[2]		=	1;
#else
	#define colorOpacityUpdate()																\
		initv(nSample->color,0);																\
		initv(nSample->opacity,-1);																\
		movvv(pixel->first.opacity,nSample->opacity);
#endif

#define	drawPixel() 																			\
	if (z < pixel->z) {																			\
		const	float	jt		=	pixel->jt;													\
		updateOpaque();																			\
		nSample					=	&pixel->last;												\
		nSample->z				=	z;															\
		colorOpacityUpdate();																	\
		drawExtraSamples()																		\
		depthFilterIf();																		\
		pixel->z				=	z;															\
		touchNode(pixel->node,z);																\
	} depthFilterElse();

#endif

#else

#ifdef STOCHASTIC_TRANSPARENT


// nM, T
#ifndef STOCHASTIC_MATTE
	#define colorOpacityUpdate()															\
		nSample->color[0]		=	v0c[0]*v + v1c[0]*(1-u-v) + v2c[0]*u;					\
		nSample->color[1]		=	v0c[1]*v + v1c[1]*(1-u-v) + v2c[1]*u;					\
		nSample->color[2]		=	v0c[2]*v + v1c[2]*(1-u-v) + v2c[2]*u;					\
		nSample->opacity[0]		=	v0o[0]*v + v1o[0]*(1-u-v) + v2o[0]*u;					\
		nSample->opacity[1]		=	v0o[1]*v + v1o[1]*(1-u-v) + v2o[1]*u;					\
		nSample->opacity[2]		=	v0o[2]*v + v1o[2]*(1-u-v) + v2o[2]*u;
#else
	#define colorOpacityUpdate()															\
		initv(nSample->color,0);															\
		nSample->opacity[0]		=	-(v0o[0]*v + v1o[0]*(1-u-v) + v2o[0]*u);				\
		nSample->opacity[1]		=	-(v0o[1]*v + v1o[1]*(1-u-v) + v2o[1]*u);				\
		nSample->opacity[2]		=	-(v0o[2]*v + v1o[2]*(1-u-v) + v2o[2]*u);				\
		movvv(pixel->first.opacity,nSample->opacity);
#endif

#define	drawPixel() 																		\
	if (z < pixel->z) {																		\
		findSample(nSample,z);																\
		nSample->z				=	z;														\
		colorOpacityUpdate();																\
	}

#else

// nM, nT
#ifndef STOCHASTIC_MATTE
	#define colorOpacityUpdate()															\
		nSample->color[0]		=	v0c[0]*v + v1c[0]*(1-u-v) + v2c[0]*u;					\
		nSample->color[1]		=	v0c[1]*v + v1c[1]*(1-u-v) + v2c[1]*u;					\
		nSample->color[2]		=	v0c[2]*v + v1c[2]*(1-u-v) + v2c[2]*u;					\
		nSample->opacity[0]		=	1;														\
		nSample->opacity[1]		=	1;														\
		nSample->opacity[2]		=	1;
#else
	#define colorOpacityUpdate()															\
		initv(nSample->color,0);															\
		initv(nSample->opacity,-1);															\
		movvv(pixel->first.opacity,nSample->opacity);
#endif

#define	drawPixel()																			\
	if (z < pixel->z) {																		\
		updateOpaque();																		\
		nSample					=	&pixel->last;											\
		nSample->z				=	z;														\
		colorOpacityUpdate();																\
		drawExtraSamples()																	\
		depthFilterIf();																	\
		pixel->z				=	z;														\
		touchNode(pixel->node,z);															\
	} depthFilterElse();

#endif
#endif

#ifdef STOCHASTIC_UNDERCULL
#define shouldDrawFront()			(grid->flags & (RASTER_DRAW_FRONT | RASTER_SHADE_BACKFACE))
#define shouldDrawBack()			(grid->flags & (RASTER_DRAW_BACK  | RASTER_SHADE_BACKFACE))
#else
#define shouldDrawFront()			(grid->flags & RASTER_DRAW_FRONT)
#define shouldDrawBack()			(grid->flags & RASTER_DRAW_BACK)
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

xmin	=	xbound[0] - left;	// Convert the bound into the current bucket
ymin	=	ybound[0] - top;
xmax	=	xbound[1] - left;
ymax	=	ybound[1] - top;

xmin	=	max(xmin,0);		// Clamp the bound in the current bucket
ymin	=	max(ymin,0);
xmax	=	min(xmax,xres);
ymax	=	min(ymax,yres);

#ifdef STOCHASTIC_FOCAL_BLUR
#define SLOW_RASTER
#endif

#ifdef STOCHASTIC_MOVING
#ifndef SLOW_RASTER
#define SLOW_RASTER
#endif
#endif


// SLOW_RENDER means the triangle has motion blur or depth of field
// In such a case, we need to deform the triangle individually for each
// sample which makes the rasterization slower

#ifndef SLOW_RASTER

// Do the fast rasterization


// Compute the area of the triangle
a		=	area(v0[COMP_X],v0[COMP_Y],v1[COMP_X],v1[COMP_Y],v2[COMP_X],v2[COMP_Y]);

if (a > 0) {

	// Back face culling
	if (!shouldDrawBack()) {
		continue;
	}

	// For each sample
	for (y=ymin;y<=ymax;y++) {
		for (x=xmin;x<=xmax;x++) {
			CPixel			*pixel	=	fb[y] + x;

			lodCheck();

			const float		xcent	=	pixel->xcent;
			const float		ycent	=	pixel->ycent;
			float			u,v;
			
			dv0		=	v0;
			dv1		=	v1;
			dv2		=	v2;

			u	=	area(xcent,ycent,dv0[COMP_X],dv0[COMP_Y],dv1[COMP_X],dv1[COMP_Y]);
			if (u < 0)	continue;

			v	=	area(xcent,ycent,dv1[COMP_X],dv1[COMP_Y],dv2[COMP_X],dv2[COMP_Y]);
			if (v < 0)	continue;

			if ((u+v) > a) continue;
			
			u	/=	a;
			v	/=	a;

			const	float	z			=	dv0[2]*v + dv1[2]*(1-u-v) + dv2[2]*u;
			if (z < clipMin)	continue;

			drawPixelCheck();
		}
	}
} else {

	// Back face culling
	if (!shouldDrawFront()) {
		continue;
	}

	for (y=ymin;y<=ymax;y++) {
		for (x=xmin;x<=xmax;x++) {
			CPixel			*pixel	=	fb[y] + x;

			lodCheck();

			const float		xcent	=	pixel->xcent;
			const float		ycent	=	pixel->ycent;
			float			u,v;

			
			dv0		=	v0;
			dv1		=	v1;
			dv2		=	v2;

			u	=	area(xcent,ycent,dv0[COMP_X],dv0[COMP_Y],dv1[COMP_X],dv1[COMP_Y]);
			if (u > 0)	continue;

			v	=	area(xcent,ycent,dv1[COMP_X],dv1[COMP_Y],dv2[COMP_X],dv2[COMP_Y]);
			if (v > 0)	continue;

			if ((u+v) < a) continue;

			u	/=	a;
			v	/=	a;

			const	float	z			=	v0[2]*v + v1[2]*(1-u-v) + v2[2]*u;
			if (z < clipMin)	continue;

			drawPixelCheck();
		}
	}
}



#else	// SLOW_RENDER

	a	=	0;

	for (y=ymin;y<=ymax;y++) {
		for (x=xmin;x<=xmax;x++) {
			CPixel			*pixel	=	fb[y] + x;

			lodCheck();

			const float		xcent	=	pixel->xcent;
			const float		ycent	=	pixel->ycent;
			float			u,v;
			
#ifdef STOCHASTIC_MOVING
			interpolatev(v0movTmp,v0,v0+displacement,pixel->jt);
			interpolatev(v1movTmp,v1,v1+displacement,pixel->jt);
			interpolatev(v2movTmp,v2,v2+displacement,pixel->jt);
			dv0		=	v0movTmp;
			dv1		=	v1movTmp;
			dv2		=	v2movTmp;

			// Compute the deformed triangle area
			if((a = area(dv0[COMP_X],dv0[COMP_Y],dv1[COMP_X],dv1[COMP_Y],dv2[COMP_X],dv2[COMP_Y])) < 0) {
				const float	*tmp;

				if (!shouldDrawFront()) {
					continue;
				}

				tmp		=	dv0;
				dv0		=	dv1;
				dv1		=	tmp;
				a		=	-a;

				
			} else {
				if (!shouldDrawBack()) {
					continue;
				}
			}
#else
			dv0		=	v0;
			dv1		=	v1;
			dv2		=	v2;
#endif


#ifdef STOCHASTIC_FOCAL_BLUR
			v0focTmp[COMP_X]	= dv0[COMP_X] + pixel->jdx*v0[9];
			v1focTmp[COMP_X]	= dv1[COMP_X] + pixel->jdx*v1[9];
			v2focTmp[COMP_X]	= dv2[COMP_X] + pixel->jdx*v2[9];
			v0focTmp[COMP_Y]	= dv0[COMP_Y] + pixel->jdy*v0[9];
			v1focTmp[COMP_Y]	= dv1[COMP_Y] + pixel->jdy*v1[9];
			v2focTmp[COMP_Y]	= dv2[COMP_Y] + pixel->jdy*v2[9];
			v0focTmp[COMP_Z]	= dv0[COMP_Z];
			v1focTmp[COMP_Z]	= dv1[COMP_Z];
			v2focTmp[COMP_Z]	= dv2[COMP_Z];
			dv0					= v0focTmp;
			dv1					= v1focTmp;
			dv2					= v2focTmp;

			if((a = area(dv0[COMP_X],dv0[COMP_Y],dv1[COMP_X],dv1[COMP_Y],dv2[COMP_X],dv2[COMP_Y])) < 0) {
				const float	*tmp;
				
				if (!shouldDrawFront()) {
					continue;
				}

				tmp		=	dv0;
				dv0		=	dv1;
				dv1		=	tmp;
				a		=	-a;
			} else {
				if (!shouldDrawBack()) {
					continue;
				}
			}

#endif

			u	=	area(xcent,ycent,dv0[COMP_X],dv0[COMP_Y],dv1[COMP_X],dv1[COMP_Y]);
			if (u < 0)	continue;

			v	=	area(xcent,ycent,dv1[COMP_X],dv1[COMP_Y],dv2[COMP_X],dv2[COMP_Y]);
			if (v < 0)	continue;

			if ((u+v) > a) continue;

			u	/=	a;
			v	/=	a;

			const	float	z			=	dv0[2]*v + dv1[2]*(1-u-v) + dv2[2]*u;
			if (z < clipMin)	continue;

			drawPixelCheck();
		}
	}

#endif	// SLOW_RENDER




#ifdef SLOW_RASTER
#undef SLOW_RASTER
#endif

#undef t
#undef lodCheck
#undef drawPixelCheck
#undef drawPixel
#undef drawExtraSamples
#undef displacement
#undef colorOpacityUpdate
#undef shouldDrawFront
#undef shouldDrawBack

