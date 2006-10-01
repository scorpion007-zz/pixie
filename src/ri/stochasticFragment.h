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

// This is the portion of Pixie that rasterizes a grid into the framebuffer












////////////////////////////////////////////////////////////////////////////////////////////
//
//		This is where we dice the microquads into nanoquads
//
////////////////////////////////////////////////////////////////////////////////////////////
const int	left				=	this->left;			// Left of the bucket window
const int	top					=	this->top;			// Top
const int	right				=	left + width;		// Right
const int	bottom				=	top + height;		// Bottom
const int	udiv				=	grid->udiv;			// For fast access
const int	vdiv				=	grid->vdiv;
const float	*vertices			=	grid->vertices;
const int	*bound				=	grid->bound;


if (fragments == NULL) if (grid->dim > 0) {
	////////////////////////////////////////////////////////////////////////////////////////////
	// Dice quads (either a curve or a surface)
	////////////////////////////////////////////////////////////////////////////////////////////
	int				i,j;

	// For each quad
	for (j=0;j<vdiv;j++) {
		for (i=0;i<udiv;i++,bound+=4) {


			numQuadsConsidered++;

			// Trivial reject
			if (bound[0] > right)	continue;	// xmin
			if (bound[1] > bottom)	continue;	// ymin
			if (bound[2] < left)	continue;	// xmax
			if (bound[3] < top)		continue;	// ymax


			const int	index		=	j*(udiv+1) + i;						// Index is the top left vertex
			const float	*vertex0	=	vertices + index*numVertexSamples;	// Top left
			const float	*vertex1	=	vertex0 + numVertexSamples;			// Top right
			const float	*vertex2	=	vertex1 + udiv*numVertexSamples;	// Bottom left
			const float	*vertex3	=	vertex2 + numVertexSamples;			// Bottom right
			vector		tmp;
			int			mudiv,mvdiv,k;	// Micro division amount


			numQuadsPassed++;

			/////////////////////////////////////////////////////////////
			// Compute the micro subdivision amount so that the max edge 
			// length for a nanoquad is one sample long
			/////////////////////////////////////////////////////////////
			subvv(tmp,vertex1,vertex0);
			mudiv	=	(int) ceil(lengthv(tmp));
			subvv(tmp,vertex3,vertex2);
			k	=	(int) ceil(lengthv(tmp));
			if (k > mudiv)	mudiv	=	k;
			subvv(tmp,vertex2,vertex0);
			mvdiv	=	(int) ceil(lengthv(tmp));
			subvv(tmp,vertex3,vertex1);
			k	=	(int) ceil(lengthv(tmp));
			if (k > mvdiv)	mvdiv	=	k;

			assert(mudiv >= 1);
			assert(mvdiv >= 1);

			/*

			/////////////////////////////////////////////////////////////
			// Compute the nanoquads
			/////////////////////////////////////////////////////////////
			const float	du	=	1 / (float) mudiv;
			const float	dv	=	1 / (float) mvdiv;
			float		cu,cv;
			int			ii,jj;
			for (cv=0,jj=0;jj<udiv;jj++,cv+=dv) {
				for (cu=0,ii=0;ii<udiv;ii++,cu+=du) {
					vector		v0,v1,v2,v3;
					TFragment	*cFragment;

					numNanoQuadsConsidered++;

					// Compute the corners of the microquads
#define corner(__c,__u,__v)	__c[0]	=	((vertex1[0] - vertex0[0])*(__u) + vertex0[0])*(1 - (__v)) + 	((vertex3[0] - vertex2[0])*(__u) + vertex2[0])*(__v);	\
							__c[1]	=	((vertex1[1] - vertex0[1])*(__u) + vertex0[1])*(1 - (__v)) + 	((vertex3[1] - vertex2[1])*(__u) + vertex2[1])*(__v);	\
							__c[2]	=	((vertex1[2] - vertex0[2])*(__u) + vertex0[2])*(1 - (__v)) + 	((vertex3[2] - vertex2[2])*(__u) + vertex2[2])*(__v);

					corner(v0,cu,cv);
					corner(v1,cu+du,cv);
					corner(v2,cu,cv+dv);
					corner(v3,cu+du,cv+dv);

#undef corner

					// v0,v1,v2,v3 are the corners of the nanoquad (topleft,topright,bottomleft,bottomright resp.)

					// Compute the centeroid of the nanoquad
					addvv(tmp,v0,v1);
					addvv(tmp,v2);
					addvv(tmp,v3);
					mulvf(tmp,0.25f);

					// Convert to integer sample coordinates
					const int	x	=	(int) floor(tmp[0]);
					const int	y	=	(int) floor(tmp[1]);

					// Is it in the bucket?
					if (x < left)		continue;					
					if (y < top)		continue;
					if (x >= right)		continue;
					if (y >= bottom)	continue;
					
					numNanoQuadsPassed++;

					// Check if the fragment is inside the quad
					const float	xSample		=	(float) x + 0.5f;
					const float	ySample		=	(float) y + 0.5f;
					float		atop,abottom,aleft,aright;

					if (area(v0[0],v0[1],v1[0],v2[1],v3[0],v3[1]) > 0) {
						
						#ifndef STOCHASTIC_DRAWFRONT
						continue;
						#endif

						if ((atop		= area(xSample,ySample,v0[0],v0[1],v1[0],v1[1])) < 0) continue;
						if ((aright		= area(xSample,ySample,v1[0],v1[1],v3[0],v3[1])) < 0) continue;
						if ((abottom	= area(xSample,ySample,v3[0],v3[1],v2[0],v2[1])) < 0) continue;
						if ((aleft		= area(xSample,ySample,v2[0],v2[1],v0[0],v0[1])) < 0) continue;

					} else {

						#ifndef STOCHASTIC_DRAWBACK
						continue;
						#endif

						if ((atop		= area(xSample,ySample,v0[0],v0[1],v1[0],v1[1])) > 0) continue;
						if ((aright		= area(xSample,ySample,v1[0],v1[1],v3[0],v3[1])) > 0) continue;
						if ((abottom	= area(xSample,ySample,v3[0],v3[1],v2[0],v2[1])) > 0) continue;
						if ((aleft		= area(xSample,ySample,v2[0],v2[1],v0[0],v0[1])) > 0) continue;

					}

					// Record the fragment
					cFragment				=	newFragment();		// Allocate the fragment
					cFragment->xSample		=	x;					// The coordinate of the fragment in the current bucket
					cFragment->ySample		=	y;
					cFragment->z			=	tmp[2];				// The depth of the fragment
					cFragment->index		=	index;
					cFragment->u			=	(aright / (aright + aleft))*udiv + cu;
					cFragment->v			=	(atop / (atop + abottom))*vdiv + cv;
					cFragment->next			=	fragments;
					fragments				=	cFragment;

					// FIXME: This fragment can be deferred to the correct bucket now
				}
			}
			*/
		}

		bound	+=	4;
	}

} else {
	////////////////////////////////////////////////////////////////////////////////////////////
	// Dice points
	////////////////////////////////////////////////////////////////////////////////////////////
}

TFragment	*cFragment;
while((cFragment = fragments) != NULL) {

	// Advance the fragment
	fragments	=	fragments->next;

	deleteFragment(cFragment);
}

/*
////////////////////////////////////////////////////////////////////////////////////////////
//
//		This is where the fragment insertion happens
//
////////////////////////////////////////////////////////////////////////////////////////////
TFragment	*cFragment;
while((cFragment = fragments) != NULL) {

	// Advance the fragment
	fragments	=	fragments->next;

// This macro does the actual interpolation of the color from the grid
#define	computeFragment()																			\
	const float	*v0			=	vertices + cFragment->index*numVertexSamples;						\
	const float	*v1			=	v0 + numVertexSamples;												\
	const float	*v2			=	v1 + udiv*numVertexSamples;											\
	const float	*v3			=	v2 + numVertexSamples;												\
	const float	u			=	cFragment->u;														\
	const float	v			=	cFragment->v;														\
	cFragment->color[0]		=	((v1[3] - v0[3])*u + v0[3])*(1-v) + ((v3[3] - v2[3])*u + v2[3])*v;	\
	cFragment->color[1]		=	((v1[4] - v0[4])*u + v0[4])*(1-v) + ((v3[4] - v2[4])*u + v2[4])*v;	\
	cFragment->color[2]		=	((v1[5] - v0[5])*u + v0[5])*(1-v) + ((v3[5] - v2[5])*u + v2[5])*v;	\
	cFragment->opacity[0]	=	((v1[6] - v0[6])*u + v0[6])*(1-v) + ((v3[6] - v2[6])*u + v2[6])*v;	\
	cFragment->opacity[1]	=	((v1[7] - v0[7])*u + v0[7])*(1-v) + ((v3[7] - v2[7])*u + v2[7])*v;	\
	cFragment->opacity[2]	=	((v1[8] - v0[8])*u + v0[8])*(1-v) + ((v3[8] - v2[8])*u + v2[8])*v;	\









#ifdef STOCHASTIC_TRANSPARENT

//////////////////////////////////////////////////////////
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
	pixel->update	=	cFragment;

//
//////////////////////////////////////////////////////////


#else


//////////////////////////////////////////////////////////
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
	touchNode(pixel->node,z);
//
//////////////////////////////////////////////////////////

#endif









#ifdef STOCHASTIC_UNSHADED
// We're not shaded yet, so if we pass the depth test, we need to back and shade the grid
#ifdef STOCHASTIC_UNDERCULL
#define drawPixelCheck()															\
	if (z < pixel->z || (grid->flags & RASTER_SHADE_HIDDEN)) {						\
		shadeGrid(grid,FALSE);														\
		rasterDrawGrid(grid,cFragment);												\
		return;																		\
	} depthFilterElse();
#else
#define drawPixelCheck()															\
	if (z < pixel->z) {																\
		shadeGrid(grid,FALSE);														\
		rasterDrawGrid(grid,cFragment);												\
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

		// This macro kicks off the code gen
		drawPixelCheck();





#undef	lodCheck
#undef	drawPixelCheck
#undef	drawPixel
}
*/