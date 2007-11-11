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

// This is the portion of Pixie that draws a quad into the stochastic

///////////////////////////////////////////////////////////////////////////////////////////
//
//   Here're some macros that make the rasterization job easier for us
//
///////////////////////////////////////////////////////////////////////////////////////////


// Shade _very_ early if we know we are guaranteed to have to anyway
// This also solves issues with grids viewed exactly side-on never
// being shaded when baking
// Note: we retain the pre-rasterization method for the case where RASTER_SHADE_HIDDEN
// is not set, and for the cases where 1 sidedness must be respected

#ifdef STOCHASTIC_UNSHADED
#ifdef STOCHASTIC_UNDERCULL
	const	int	_flags = grid->flags;
	if ((_flags & RASTER_SHADE_HIDDEN) &&
		(_flags & (RASTER_DRAW_FRONT | RASTER_SHADE_BACKFACE)) &&
		(_flags & (RASTER_DRAW_BACK | RASTER_SHADE_BACKFACE))) {
		
		shadeGrid(grid,FALSE);
		rasterDrawPrimitives(grid);
		return;
	}
#endif
#endif

#ifdef STOCHASTIC_EXTRA_SAMPLES
	const int displacement	=	10 + CRenderer::numExtraSamples;
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

// We have motion blur, interpolate in time as well as space
#define	drawExtraSamples()	{																\
	int				currentSample;															\
	const	float	*s0	=	v0+10;															\
	const	float	*s1	=	v1+10;															\
	const	float	*s2	=	v2+10;															\
	const	float	*s3	=	v3+10;															\
	float			*dest;																	\
																							\
	for (dest=nSample->extraSamples,currentSample=CRenderer::numExtraSamples;currentSample>0;currentSample--,s0++,s1++,s2++,s3++) {		\
		*dest++	=	((s0[0]*(1-jt)+s0[displacement]*jt)*(1-u) + (s1[0]*(1-jt)+s1[displacement]*jt)*u)*(1-v)	+	\
					((s2[0]*(1-jt)+s2[displacement]*jt)*(1-u) + (s3[0]*(1-jt)+s3[displacement]*jt)*u)*v;		\
	}																						\
}

#else

// No motion blur, interpolate in space only
#define	drawExtraSamples()	{																\
	int				currentSample;															\
	const	float	*s0	=	v0+10;															\
	const	float	*s1	=	v1+10;															\
	const	float	*s2	=	v2+10;															\
	const	float	*s3	=	v2+10;															\
	float			*dest;																	\
																							\
	for (dest=nSample->extraSamples,currentSample=CRenderer::numExtraSamples;currentSample>0;currentSample--) {	\
		*dest++	=	((*s0++)*(1-u) + (*s1++)*u)*(1-v) + ((*s2++)*(1-u) + (*s3++)*u)*v;		\
	}																						\
}

#endif

#else
#define	drawExtraSamples()
#endif






//////////////////////////////////////////////////////////////////////////////////////////
// This big ass macro is for computing the final color/opacity of a pixel
#ifdef STOCHASTIC_MOVING
#ifdef STOCHASTIC_TRANSPARENT

// M T
#ifndef STOCHASTIC_MATTE

	#define colorOpacityUpdate()																\
		const float	*v0c		=	v0+3;														\
		const float	*v1c		=	v1+3;														\
		const float	*v2c		=	v2+3;														\
		const float	*v3c		=	v3+3;														\
		nSample->color[0]		=	((v0c[0]*(1-jt) + v0c[displacement+0]*jt)*(1-u) + (v1c[0]*(1-jt) + v1c[displacement+0]*jt)*u)*(1-v) + ((v2c[0]*(1-jt) + v2c[displacement+0]*jt)*(1-u) + (v3c[0]*(1-jt) + v3c[displacement+0]*jt)*u)*v;	\
		v0c++;	v1c++;	v2c++;	v3c++;															\
		nSample->color[1]		=	((v0c[0]*(1-jt) + v0c[displacement+0]*jt)*(1-u) + (v1c[0]*(1-jt) + v1c[displacement+0]*jt)*u)*(1-v) + ((v2c[0]*(1-jt) + v2c[displacement+0]*jt)*(1-u) + (v3c[0]*(1-jt) + v3c[displacement+0]*jt)*u)*v;	\
		v0c++;	v1c++;	v2c++;	v3c++;															\
		nSample->color[2]		=	((v0c[0]*(1-jt) + v0c[displacement+0]*jt)*(1-u) + (v1c[0]*(1-jt) + v1c[displacement+0]*jt)*u)*(1-v) + ((v2c[0]*(1-jt) + v2c[displacement+0]*jt)*(1-u) + (v3c[0]*(1-jt) + v3c[displacement+0]*jt)*u)*v;	\
		v0c++;	v1c++;	v2c++;	v3c++;															\
		nSample->opacity[0]		=	((v0c[0]*(1-jt) + v0c[displacement+0]*jt)*(1-u) + (v1c[0]*(1-jt) + v1c[displacement+0]*jt)*u)*(1-v) + ((v2c[0]*(1-jt) + v2c[displacement+0]*jt)*(1-u) + (v3c[0]*(1-jt) + v3c[displacement+0]*jt)*u)*v;	\
		v0c++;	v1c++;	v2c++;	v3c++;															\
		nSample->opacity[1]		=	((v0c[0]*(1-jt) + v0c[displacement+0]*jt)*(1-u) + (v1c[0]*(1-jt) + v1c[displacement+0]*jt)*u)*(1-v) + ((v2c[0]*(1-jt) + v2c[displacement+0]*jt)*(1-u) + (v3c[0]*(1-jt) + v3c[displacement+0]*jt)*u)*v;	\
		v0c++;	v1c++;	v2c++;	v3c++;															\
		nSample->opacity[2]		=	((v0c[0]*(1-jt) + v0c[displacement+0]*jt)*(1-u) + (v1c[0]*(1-jt) + v1c[displacement+0]*jt)*u)*(1-v) + ((v2c[0]*(1-jt) + v2c[displacement+0]*jt)*(1-u) + (v3c[0]*(1-jt) + v3c[displacement+0]*jt)*u)*v;
		
#else

	#define colorOpacityUpdate()																\
		initv(nSample->color,0);																\
		const float	*v0c		=	v0+6;														\
		const float	*v1c		=	v1+6;														\
		const float	*v2c		=	v2+6;														\
		const float	*v3c		=	v3+6;														\
		nSample->opacity[0]		=	-(((v0c[0]*(1-jt) + v0c[displacement+0]*jt)*(1-u) + (v1c[0]*(1-jt) + v1c[displacement+0]*jt)*u)*(1-v) + ((v2c[0]*(1-jt) + v2c[displacement+0]*jt)*(1-u) + (v3c[0]*(1-jt) + v3c[displacement+0]*jt)*u)*v);	\
		v0c++;	v1c++;	v2c++;	v3c++;															\
		nSample->opacity[1]		=	-(((v0c[0]*(1-jt) + v0c[displacement+0]*jt)*(1-u) + (v1c[0]*(1-jt) + v1c[displacement+0]*jt)*u)*(1-v) + ((v2c[0]*(1-jt) + v2c[displacement+0]*jt)*(1-u) + (v3c[0]*(1-jt) + v3c[displacement+0]*jt)*u)*v);	\
		v0c++;	v1c++;	v2c++;	v3c++;															\
		nSample->opacity[2]		=	-(((v0c[0]*(1-jt) + v0c[displacement+0]*jt)*(1-u) + (v1c[0]*(1-jt) + v1c[displacement+0]*jt)*u)*(1-v) + ((v2c[0]*(1-jt) + v2c[displacement+0]*jt)*(1-u) + (v3c[0]*(1-jt) + v3c[displacement+0]*jt)*u)*v);	\
		movvv(pixel->first.opacity,nSample->opacity);

#endif

#define	drawPixel() 																			\
	if (z < pixel->z) {																			\
		const	float	jt		=	pixel->jt;													\
		findSample(nSample,z);																	\
		nSample->z				=	z;															\
		colorOpacityUpdate();																	\
		drawExtraSamples();																		\
		updateTransparent(depthFilterIf,depthFilterElse);										\
	}

#else

// M, nT
#ifndef STOCHASTIC_MATTE

	#define colorOpacityUpdate()																\
		const float	*v0c		=	v0+3;														\
		const float	*v1c		=	v1+3;														\
		const float	*v2c		=	v2+3;														\
		const float	*v3c		=	v3+3;														\
		nSample->color[0]		=	((v0c[0]*(1-jt) + v0c[displacement+0]*jt)*(1-u) + (v1c[0]*(1-jt) + v1c[displacement+0]*jt)*u)*(1-v) + ((v2c[0]*(1-jt) + v2c[displacement+0]*jt)*(1-u) + (v3c[0]*(1-jt) + v3c[displacement+0]*jt)*u)*v;	\
		v0c++;	v1c++;	v2c++;	v3c++;															\
		nSample->color[1]		=	((v0c[0]*(1-jt) + v0c[displacement+0]*jt)*(1-u) + (v1c[0]*(1-jt) + v1c[displacement+0]*jt)*u)*(1-v) + ((v2c[0]*(1-jt) + v2c[displacement+0]*jt)*(1-u) + (v3c[0]*(1-jt) + v3c[displacement+0]*jt)*u)*v;	\
		v0c++;	v1c++;	v2c++;	v3c++;															\
		nSample->color[2]		=	((v0c[0]*(1-jt) + v0c[displacement+0]*jt)*(1-u) + (v1c[0]*(1-jt) + v1c[displacement+0]*jt)*u)*(1-v) + ((v2c[0]*(1-jt) + v2c[displacement+0]*jt)*(1-u) + (v3c[0]*(1-jt) + v3c[displacement+0]*jt)*u)*v;	\
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
		drawExtraSamples();																		\
		depthFilterIf();																		\
		pixel->z				=	z;															\
		depthFilterTouchNode();																	\
	} depthFilterElse();

#endif

#else

#ifdef STOCHASTIC_TRANSPARENT


// nM, T
#ifndef STOCHASTIC_MATTE

	#define colorOpacityUpdate()															\
		const float	*v0c		=	v0+3;													\
		const float	*v1c		=	v1+3;													\
		const float	*v2c		=	v2+3;													\
		const float	*v3c		=	v3+3;													\
		nSample->color[0]		=	(v0c[0]*(1-u) + v1c[0]*u)*(1-v) + (v2c[0]*(1-u) + v3c[0]*u)*v;	\
		nSample->color[1]		=	(v0c[1]*(1-u) + v1c[1]*u)*(1-v) + (v2c[1]*(1-u) + v3c[1]*u)*v;	\
		nSample->color[2]		=	(v0c[2]*(1-u) + v1c[2]*u)*(1-v) + (v2c[2]*(1-u) + v3c[2]*u)*v;	\
		nSample->opacity[0]		=	(v0c[3]*(1-u) + v1c[3]*u)*(1-v) + (v2c[3]*(1-u) + v3c[3]*u)*v;	\
		nSample->opacity[1]		=	(v0c[4]*(1-u) + v1c[4]*u)*(1-v) + (v2c[4]*(1-u) + v3c[4]*u)*v;	\
		nSample->opacity[2]		=	(v0c[5]*(1-u) + v1c[5]*u)*(1-v) + (v2c[5]*(1-u) + v3c[5]*u)*v;

#else

	#define colorOpacityUpdate()															\
		initv(nSample->color,0);															\
		const float	*v0c		=	v0+6;													\
		const float	*v1c		=	v1+6;													\
		const float	*v2c		=	v2+6;													\
		const float	*v3c		=	v3+6;													\
		nSample->opacity[0]		=	-((v0c[0]*(1-u) + v1c[0]*u)*(1-v) + (v2c[0]*(1-u) + v3c[0]*u)*v);	\
		nSample->opacity[1]		=	-((v0c[1]*(1-u) + v1c[1]*u)*(1-v) + (v2c[1]*(1-u) + v3c[1]*u)*v);	\
		nSample->opacity[2]		=	-((v0c[2]*(1-u) + v1c[2]*u)*(1-v) + (v2c[2]*(1-u) + v3c[2]*u)*v);	\
		movvv(pixel->first.opacity,nSample->opacity);

#endif

#define	drawPixel() 																		\
	if (z < pixel->z) {																		\
		findSample(nSample,z);																\
		nSample->z				=	z;														\
		colorOpacityUpdate();																\
		drawExtraSamples();																	\
		updateTransparent(depthFilterIf,depthFilterElse);									\
	}

#else

// nM, nT
#ifndef STOCHASTIC_MATTE

	#define colorOpacityUpdate()															\
		const float	*v0c		=	v0+3;													\
		const float	*v1c		=	v1+3;													\
		const float	*v2c		=	v2+3;													\
		const float	*v3c		=	v3+3;													\
		nSample->color[0]		=	(v0c[0]*(1-u) + v1c[0]*u)*(1-v) + (v2c[0]*(1-u) + v3c[0]*u)*v;	\
		nSample->color[1]		=	(v0c[1]*(1-u) + v1c[1]*u)*(1-v) + (v2c[1]*(1-u) + v3c[1]*u)*v;	\
		nSample->color[2]		=	(v0c[2]*(1-u) + v1c[2]*u)*(1-v) + (v2c[2]*(1-u) + v3c[2]*u)*v;	\
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
		drawExtraSamples();																	\
		depthFilterIf();																	\
		pixel->z				=	z;														\
		depthFilterTouchNode();																\
	} depthFilterElse();

#endif
#endif





//////////////////////////////////////////////////////////////////////////////////////////
// These macros decide whether we should draw a quad or not
#ifdef STOCHASTIC_UNDERCULL
#define shouldDrawFront()			(flags & (RASTER_DRAW_FRONT | RASTER_SHADE_BACKFACE))
#define shouldDrawBack()			(flags & (RASTER_DRAW_BACK  | RASTER_SHADE_BACKFACE))
#else
#define shouldDrawFront()			(flags & RASTER_DRAW_FRONT)
#define shouldDrawBack()			(flags & RASTER_DRAW_BACK)
#endif



//////////////////////////////////////////////////////////////////////////////////////////
//This macro is the entry point that checks if the pixel passes a depth test and if we need 
// to shade the grid or not
#ifdef STOCHASTIC_UNSHADED
// We're not shaded yet, so if we pass the depth test, we need to back and shade the grid
#ifdef STOCHASTIC_UNDERCULL
#define drawPixelCheck()															\
	if (z < pixel->z || (flags & RASTER_SHADE_HIDDEN)) {							\
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




//////////////////////////////////////////////////////////////////////////////////////////
// This macro is used to check whether the sample is inside the quad or not
#define	checkPixel(__op)																					\
	const float		xcent	=	pixel->xcent;																\
	const float		ycent	=	pixel->ycent;																\
	float			aleft,atop,aright,abottom;																\
																											\
	if ((atop		= area(xcent,ycent,v0[COMP_X],v0[COMP_Y],v1[COMP_X],v1[COMP_Y])) __op 0)	continue;	\
	if ((aright		= area(xcent,ycent,v1[COMP_X],v1[COMP_Y],v3[COMP_X],v3[COMP_Y])) __op 0)	continue;	\
	if ((abottom	= area(xcent,ycent,v3[COMP_X],v3[COMP_Y],v2[COMP_X],v2[COMP_Y])) __op 0)	continue;	\
	if ((aleft		= area(xcent,ycent,v2[COMP_X],v2[COMP_Y],v0[COMP_X],v0[COMP_Y])) __op 0)	continue;	\
																											\
	const float u	=	aleft / (aleft + aright);															\
	const float v	=	atop / (atop + abottom);															\
	const float	z	=	(v0[COMP_Z]*(1-u) + v1[COMP_Z]*u)*(1-v) + (v2[COMP_Z]*(1-u) + v3[COMP_Z]*u)*v;		\
	if (z < CRenderer::clipMin)	continue;



///////////////////////////////////////////////////////////////////////////////////////////
//
//   Here's the code that actually iterates over the quads and draws them
//
///////////////////////////////////////////////////////////////////////////////////////////

#ifdef STOCHASTIC_XTREME

// Iterate over pixels, discarding quads
// --- Extreme motion blur/depth of field case


const int	xres		=	sampleWidth - 1;
const int	yres		=	sampleHeight - 1;

int xmin				=	grid->xbound[0] - left;
int xmax				=	grid->xbound[1] - left;
int ymin				=	grid->ybound[0] - top;
int ymax				=	grid->ybound[1] - top;

xmin					=	max(xmin,0);		// Clamp the bound in the current bucket
ymin					=	max(ymin,0);
xmax					=	min(xmax,xres);
ymax					=	min(ymax,yres);

int	x,y;
for (y=ymin;y<=ymax;y++) for (x=xmin;x<=xmax;x++) {
	CPixel		*pixel		=	fb[y] + x;
	int			i,j;

	const int	*bounds		=	grid->bounds;

	const float	*vertices	=	grid->vertices;
	const	int	udiv		=	grid->udiv;

	const	int	vdiv		=	grid->vdiv;
	const	int	flags		=	grid->flags;

	for (j=0;j<vdiv;j++) {
		for (i=0;i<udiv;i++,bounds+=4,vertices+=numVertexSamples) {

			if (x+left < bounds[0])		continue;
			if (x+left > bounds[1])		continue;
			if (y+top < bounds[2])		continue;
			if (y+top > bounds[3])		continue;

			lodCheck();

			const float	*v0	=	vertices;
			const float	*v1	=	vertices + numVertexSamples;
			const float	*v2	=	v1 + udiv*numVertexSamples;
			const float	*v3	=	v2 + numVertexSamples;

#ifdef STOCHASTIC_FOCAL_BLUR
				const float v0d =	v0[9];
				const float v1d =	v1[9];
				const float v2d =	v2[9];
				const float v3d =	v3[9];
#endif

#ifdef STOCHASTIC_MOVING
			vector	v0movTmp;
			vector	v1movTmp;
			vector	v2movTmp;
			vector	v3movTmp;
			interpolatev(v0movTmp,v0,v0+displacement,pixel->jt);
			interpolatev(v1movTmp,v1,v1+displacement,pixel->jt);
			interpolatev(v2movTmp,v2,v2+displacement,pixel->jt);
			interpolatev(v3movTmp,v3,v3+displacement,pixel->jt);
			v0		=	v0movTmp;
			v1		=	v1movTmp;
			v2		=	v2movTmp;
			v3		=	v3movTmp;
#endif


#ifdef STOCHASTIC_FOCAL_BLUR
			vector	v0focTmp;
			vector	v1focTmp;
			vector	v2focTmp;
			vector	v3focTmp;
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
#endif

			// Check the orientation of the quad
			float a	= area(v0[COMP_X],v0[COMP_Y],v1[COMP_X],v1[COMP_Y],v2[COMP_X],v2[COMP_Y]);
			if (fabsf(a) < C_EPSILON)  a = area(v1[COMP_X],v1[COMP_Y],v3[COMP_X],v3[COMP_Y],v2[COMP_X],v2[COMP_Y]);
			if (a > 0) {

				// Back face culling
				if (!shouldDrawBack()) {
					continue;
				}

				checkPixel(<);

				v0	=	vertices;
				v1	=	v0 + numVertexSamples;
				v2	=	v1 + udiv*numVertexSamples;
				v3	=	v2 + numVertexSamples;

				drawPixelCheck();
			} else {

				// Back face culling
				if (!shouldDrawFront()) {
					continue;
				}

				checkPixel(>);

				v0	=	vertices;
				v1	=	v0 + numVertexSamples;
				v2	=	v1 + udiv*numVertexSamples;
				v3	=	v2 + numVertexSamples;

				drawPixelCheck();
			}
		}
		vertices	+=	numVertexSamples;
	}
}

#else

// Iterate over quads, discarding pixels
// --- No (significant) motion blur/depth of field

int			i,j;
const int	*bounds		=	grid->bounds;
const float	*vertices	=	grid->vertices;
const	int	xres		=	sampleWidth - 1;
const	int	yres		=	sampleHeight - 1;
const	int	udiv		=	grid->udiv;
const	int	vdiv		=	grid->vdiv;
const	int	flags		=	grid->flags;

for (j=0;j<vdiv;j++) {
	for (i=0;i<udiv;i++,bounds+=4,vertices+=numVertexSamples) {

		// Trivial rejects
		if (bounds[1] < left)		continue;
		if (bounds[3] < top)		continue;
		if (bounds[0] >= right)		continue;
		if (bounds[2] >= bottom)	continue;

		// Extract the quad corners
		const float	*v0	=	vertices;
		const float	*v1	=	vertices + numVertexSamples;
		const float	*v2	=	v1 + udiv*numVertexSamples;
		const float	*v3	=	v2 + numVertexSamples;


		int	xmin	=	bounds[0] - left;	// Convert the bound into the current bucket
		int	ymin	=	bounds[2] - top;
		int	xmax	=	bounds[1] - left;
		int	ymax	=	bounds[3] - top;

		xmin		=	max(xmin,0);		// Clamp the bound in the current bucket
		ymin		=	max(ymin,0);
		xmax		=	min(xmax,xres);
		ymax		=	min(ymax,yres);


		// Figure our if we have to do the slow rasterization	
#ifdef STOCHASTIC_FOCAL_BLUR
	#define SLOW_RASTER
#endif

#ifdef STOCHASTIC_MOVING
	#ifndef SLOW_RASTER
		#define SLOW_RASTER
	#endif
#endif




// SLOW_RENDER means the quad has motion blur or depth of field
// In such a case, we need to deform the quad individually for each
// sample which makes the rasterization slower
#ifndef SLOW_RASTER


		// Do the fast rasterization

		// Check the orientation of the quad
		float a	= area(v0[COMP_X],v0[COMP_Y],v1[COMP_X],v1[COMP_Y],v2[COMP_X],v2[COMP_Y]);
		if (fabsf(a) < C_EPSILON)  a = area(v1[COMP_X],v1[COMP_Y],v3[COMP_X],v3[COMP_Y],v2[COMP_X],v2[COMP_Y]);
		if (a > 0) {

			// Back face culling
			if (!shouldDrawBack()) {
				continue;
			}

			// For each sample
			int		x,y;
			for (y=ymin;y<=ymax;y++) {
				CPixel	*pixel;

				for (pixel=fb[y]+xmin,x=xmin;x<=xmax;x++,pixel++) {

					lodCheck();

					checkPixel(<);

					drawPixelCheck();
				}
			}
		} else {

			// Back face culling
			if (!shouldDrawFront()) {
				continue;
			}

			int	x,y;
			for (y=ymin;y<=ymax;y++) {
				CPixel	*pixel;

				for (pixel=fb[y]+xmin,x=xmin;x<=xmax;x++,pixel++) {

					lodCheck();

					checkPixel(>);

					drawPixelCheck();
				}
			}
		}

#else

		// Do the slow rasterization

		int	x,y;
		for (y=ymin;y<=ymax;y++) {
			CPixel		*pixel;

			for (pixel=fb[y]+xmin,x=xmin;x<=xmax;x++,pixel++) {
	
				lodCheck();

				const float	*v0	=	vertices;
				const float	*v1	=	vertices + numVertexSamples;
				const float	*v2	=	v1 + udiv*numVertexSamples;
				const float	*v3	=	v2 + numVertexSamples;

#ifdef STOCHASTIC_FOCAL_BLUR
				const float v0d =	v0[9];
				const float v1d =	v1[9];
				const float v2d =	v2[9];
				const float v3d =	v3[9];
#endif

#ifdef STOCHASTIC_MOVING
				vector	v0movTmp;
				vector	v1movTmp;
				vector	v2movTmp;
				vector	v3movTmp;
				interpolatev(v0movTmp,v0,v0+displacement,pixel->jt);
				interpolatev(v1movTmp,v1,v1+displacement,pixel->jt);
				interpolatev(v2movTmp,v2,v2+displacement,pixel->jt);
				interpolatev(v3movTmp,v3,v3+displacement,pixel->jt);
				v0		=	v0movTmp;
				v1		=	v1movTmp;
				v2		=	v2movTmp;
				v3		=	v3movTmp;
#endif


#ifdef STOCHASTIC_FOCAL_BLUR
				vector	v0focTmp;
				vector	v1focTmp;
				vector	v2focTmp;
				vector	v3focTmp;
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
#endif

				// Check the orientation of the quad
				float a	= area(v0[COMP_X],v0[COMP_Y],v1[COMP_X],v1[COMP_Y],v2[COMP_X],v2[COMP_Y]);
				if (fabsf(a) < C_EPSILON)  a = area(v1[COMP_X],v1[COMP_Y],v3[COMP_X],v3[COMP_Y],v2[COMP_X],v2[COMP_Y]);
				if (a > 0) {


					// Back face culling
					if (!shouldDrawBack()) {
						continue;
					}

					checkPixel(<);

					v0	=	vertices;
					v1	=	v0 + numVertexSamples;
					v2	=	v1 + udiv*numVertexSamples;
					v3	=	v2 + numVertexSamples;

					drawPixelCheck();
				} else {

					// Back face culling
					if (!shouldDrawFront()) {
						continue;
					}

					checkPixel(>);

					v0	=	vertices;
					v1	=	v0 + numVertexSamples;
					v2	=	v1 + udiv*numVertexSamples;
					v3	=	v2 + numVertexSamples;

					drawPixelCheck();
				}
			}
		}

#endif
	}

	vertices	+=	numVertexSamples;
}

#endif


#undef SLOW_RASTER
#undef lodCheck
#undef drawPixelCheck
#undef drawPixel
#undef drawExtraSamples
#undef displacement
#undef colorOpacityUpdate
#undef shouldDrawFront
#undef shouldDrawBack
#undef checkPixel




	

