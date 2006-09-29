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

// This is the portion of Pixie that inserts a fragment into the framebuffer

#ifdef STOCHASTIC_LOD
	#define lodCheck()																				\
		if (importance >= 0) {																		\
			if (pixel->jimp > importance)		continue;											\
		} else {																					\
			if ((1-pixel->jimp) >= -importance)	continue;											\
		}
#else
	#define lodCheck()
#endif


// This macro does the actual interpolation of the color from the grid
#define	computeFragment()																			\
	const float	*v0			=	grid->vertices + cFragment->index*vertexSize;						\
	const float	*v1			=	v0 + vertexSize;													\
	const float	*v2			=	v0 + (grid->udiv+1)*vertexSize;										\
	const float	*v3			=	v2 + vertexSize;													\
	const float	u			=	cFragment->u;														\
	const float	v			=	cFragment->v;														\
	cFragment->color[0]		=	((v1[3] - v0[3])*u + v0[3])*(1-v) + ((v3[3] - v2[3])*u + v2[3])*v;	\
	cFragment->color[1]		=	((v1[4] - v0[4])*u + v0[4])*(1-v) + ((v3[4] - v2[4])*u + v2[4])*v;	\
	cFragment->color[2]		=	((v1[5] - v0[5])*u + v0[5])*(1-v) + ((v3[5] - v2[5])*u + v2[5])*v;	\
	cFragment->opacity[0]	=	((v1[6] - v0[6])*u + v0[6])*(1-v) + ((v3[6] - v2[6])*u + v2[6])*v;	\
	cFragment->opacity[1]	=	((v1[7] - v0[7])*u + v0[7])*(1-v) + ((v3[7] - v2[7])*u + v2[7])*v;	\
	cFragment->opacity[2]	=	((v1[8] - v0[8])*u + v0[8])*(1-v) + ((v3[8] - v2[8])*u + v2[8])*v;	\


#ifndef STOCHASTIC_TRANSPARENT

// Opaque fragment insertion
#define	drawPixel() 																				\
	computeFragment();																				\
	TFragment *cSample=pixel->last;																	\
	while(cSample->z > z) {																			\
		TFragment *nSample	=	cSample->prev;														\
		assert(cSample != pixel->first);															\
		deleteFragment(cSample);																	\
		cSample				=	nSample;															\
	}																								\
	cSample->next			=	cFragment;															\
	cFragment->prev			=	cSample;															\
	cFragment->next			=	NULL;																\
	pixel->last				=	cFragment;															\
	pixel->update			=	cSample;															\
	depthFilterIf();																				\
	touchNode(pixel->node,z);																		\


#else

// Transparent fragment insertion
#define	drawPixel() 																				\
	computeFragment();																				\
	TFragment *lSample	=	pixel->update;															\
	if (z >= lSample->z)	{																		\
		TFragment		*cSample;																	\
		for (cSample=lSample->next;z >= cSample->z;lSample=cSample,cSample=cSample->next);			\
		assert(z >= lSample->z);																	\
		assert(z <= cSample->z);																	\
		cFragment->next	=	cSample;																\
		cFragment->prev	=	lSample;																\
		cSample->prev	=	cFragment;																\
		lSample->next	=	cFragment;																\
	} else {																						\
		TFragment		*cSample;																	\
		for (cSample=lSample->prev;z < cSample->z;lSample=cSample,cSample=cSample->prev);			\
		assert(z >= cSample->z);																	\
		assert(z <= lSample->z);																	\
		cFragment->next	=	lSample;																\
		cFragment->prev	=	cSample;																\
		cSample->next	=	cFragment;																\
		lSample->prev	=	cFragment;																\
	}																								\
	pixel->update	=	cFragment;																	\


#endif









#ifdef STOCHASTIC_UNSHADED
// We're not shaded yet, so if we pass the depth test, we need to back and shade the grid
#ifdef STOCHASTIC_UNDERCULL
#define drawPixelCheck()															\
	if (z < pixel->z || (grid->flags & RASTER_SHADE_HIDDEN)) {						\
		shadeGrid(grid,FALSE);														\
		rasterDrawFragments(frid,cFragment);										\
		return;																		\
	} depthFilterElse();
#else
#define drawPixelCheck()															\
	if (z < pixel->z) {																\
		shadeGrid(grid,FALSE);														\
		rasterDrawFragments(frid,cFragment);										\
		return;																		\
	} depthFilterElse();
#endif // undercull
#else
#define drawPixelCheck()															\
	if (z < pixel->z) {																\
		drawPixel();																\
	} depthFilterElse();
#endif





		// The only macro that expands depending on the running conditions
		CPixel		*pixel	=	fb[cFragment->ySample] + cFragment->xSample;
		const float	z		=	cFragment->z;

		// Check the LOD first
		lodCheck();

		// This macro kicks off the code gen
		drawPixelCheck();





#undef	lodCheck
#undef	drawPixelCheck
#undef	drawPixel

