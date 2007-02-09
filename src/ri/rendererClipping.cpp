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
//  File				:	rendererClipping.cpp
//  Classes				:	CRenderer
//  Description			:	Functions that deal with clipping are defines here
//
////////////////////////////////////////////////////////////////////////
#include "common/global.h"
#include "renderer.h"



///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	beginClipping
// Description			:	Compute various quantities that have to do with clipping
// Return Value			:	-
// Comments				:
void		CRenderer::beginClipping() {

	const float	minX		=	min(pixelLeft,pixelRight);	// The extend of the rendering window on the image
	const float	maxX		=	max(pixelLeft,pixelRight);	// plane
	const float	minY		=	min(pixelTop,pixelBottom);
	const float	maxY		=	max(pixelTop,pixelBottom);

	// Compute the equations of the clipping planes
	// The visible points are:
	// Px*leftX		+ Pz*leftZ		+ leftD		>=	0	&&
	// Px*rightX	+ Pz*rightZ		+ rightD	>=	0	&&
	// Py*topY		+ Pz*topZ		+ topD		>=	0	&&
	// Py*bottomY	+ Pz*bottomZ	+ bottomD	>=	0	&&
	// Pz >= clipMin									&&
	// Pz <= clipMax
	if (projection == OPTIONS_PROJECTION_PERSPECTIVE) {
		leftX			=	imagePlane;
		leftZ			=	-minX;
		leftD			=	0;
		rightX			=	-imagePlane;
		rightZ			=	maxX;
		rightD			=	0;
		topY			=	imagePlane;
		topZ			=	-minY;
		topD			=	0;
		bottomY			=	-imagePlane;
		bottomZ			=	maxY;
		bottomD			=	0;
	} else {
		leftX			=	1;
		leftZ			=	0;
		leftD			=	-minX;
		rightX			=	-1;
		rightZ			=	0;
		rightD			=	maxX;

		topY			=	-1;
		topZ			=	0;
		topD			=	maxY;
		bottomY			=	1;
		bottomZ			=	0;
		bottomD			=	-minY;
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	inFrustrum
// Description			:	Check if the given box is inside the viewing frustrum
// Return Value			:	-
// Comments				:
int			CRenderer::inFrustrum(const float *bmin,const float *bmax) {
	vector	corners[8];
	int		i;

	initv(corners[0],bmin[COMP_X],bmin[COMP_Y],bmin[COMP_Z]);
	initv(corners[1],bmin[COMP_X],bmax[COMP_Y],bmin[COMP_Z]);
	initv(corners[2],bmin[COMP_X],bmax[COMP_Y],bmax[COMP_Z]);
	initv(corners[3],bmin[COMP_X],bmin[COMP_Y],bmax[COMP_Z]);
	initv(corners[4],bmax[COMP_X],bmin[COMP_Y],bmin[COMP_Z]);
	initv(corners[5],bmax[COMP_X],bmax[COMP_Y],bmin[COMP_Z]);
	initv(corners[6],bmax[COMP_X],bmax[COMP_Y],bmax[COMP_Z]);
	initv(corners[7],bmax[COMP_X],bmin[COMP_Y],bmax[COMP_Z]);

	// Check against the left bounding plane
	for (i=0;i<8;i++) {
		const float	*corner	=	corners[i];

		if ((corner[COMP_X]*leftX + corner[COMP_Z]*leftZ + leftD) > 0) {
			break;
		}
	}

	if (i == 8)	return FALSE;


	// Check against the right bounding plane
	for (i=0;i<8;i++) {
		const float	*corner	=	corners[i];

		if ((corner[COMP_X]*rightX + corner[COMP_Z]*rightZ + rightD) > 0) {
			break;
		}
	}

	if (i == 8)	return	FALSE;

	// Check against the top bounding plane
	for (i=0;i<8;i++) {
		const float	*corner	=	corners[i];

		if ((corner[COMP_Y]*topY + corner[COMP_Z]*topZ + topD) > 0) {
			break;
		}
	}

	if (i == 8)	return	FALSE;


	// Check against the bottom bounding plane
	for (i=0;i<8;i++) {
		const float	*corner	=	corners[i];

		if ((corner[COMP_Y]*bottomY + corner[COMP_Z]*bottomZ + bottomD) > 0) {
			break;
		}
	}

	if (i == 8)	return	FALSE;

	return	TRUE;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	inFrustrum
// Description			:	Check if the given box is inside the viewing frustrum
// Return Value			:	-
// Comments				:
int			CRenderer::inFrustrum(const float *P) {

	if ((P[COMP_X]*leftX + P[COMP_Z]*leftZ + leftD) < 0) {
		return FALSE;
	}

	if ((P[COMP_X]*rightX + P[COMP_Z]*rightZ + rightD) < 0) {
		return FALSE;
	}

	if ((P[COMP_Y]*topY + P[COMP_Z]*topZ + topD) < 0) {
		return FALSE;
	}

	if ((P[COMP_Y]*bottomY + P[COMP_Z]*bottomZ + bottomD) < 0) {
		return FALSE;
	}

	return	TRUE;
}




///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	clipCode
// Description			:	Compute the clipping codes for a point
// Return Value			:	-
// Comments				:
unsigned int			CRenderer::clipCode(const float *P) {
	unsigned int	code	=	0;

	if ((P[COMP_X]*leftX + P[COMP_Z]*leftZ + leftD) < 0) {
		code	|=	CLIP_LEFT;
	}

	if ((P[COMP_X]*rightX + P[COMP_Z]*rightZ + rightD) < 0) {
		code	|=	CLIP_RIGHT;
	}

	if ((P[COMP_Y]*topY + P[COMP_Z]*topZ + topD) < 0) {
		code	|=	CLIP_TOP;
	}

	if ((P[COMP_Y]*bottomY + P[COMP_Z]*bottomZ + bottomD) < 0) {
		code	|=	CLIP_BOTTOM;
	}

	if (P[COMP_Z] < clipMin)	code	|=	CLIP_NEAR;

	if (P[COMP_Z] > clipMax)	code	|=	CLIP_FAR;

	return	code;
}

