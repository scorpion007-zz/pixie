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
//  File				:	object.cpp
//  Classes				:	CGeometry
//  Description			:	Implementation
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "object.h"
#include "error.h"
#include "renderer.h"
#include "ri.h"
#include "shading.h"
#include "stats.h"
#include "memory.h"
#include "surface.h"










///////////////////////////////////////////////////////////////////////
// Class				:	CObject
// Method				:	CObject
// Description			:	Ctor
// Return Value			:	-
// Comments				:	
// Date last edited		:	3/11/2001
CObject::CObject(CAttributes *a,CXform *x) {
	stats.numObjects++;

	attributes	=	a;
	xform		=	x;

	attributes->attach();
	xform->attach();

	refCount	=	0;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CObject
// Method				:	~CObject
// Description			:	Dtor
// Return Value			:	-
// Comments				:	
// Date last edited		:	3/11/2001
CObject::~CObject() {
	stats.numObjects--;

	attributes->detach();
	xform->detach();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CObject
// Method				:	bound
// Description			:	Compute the bounding box of the object
// Return Value			:
// Comments				:
// Date last edited		:	10/16/2001
void				CObject::bound(float *bmin,float *bmax) const {
	error(CODE_BUG,"An object is missing the \"bound\" function\n");
	assert(FALSE);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CObject
// Method				:	tesselate
// Description			:	Tesselate the object into raytracable primitives
// Return Value			:
// Comments				:
// Date last edited		:	10/16/2001
void				CObject::tesselate(CShadingContext *context) {
}

///////////////////////////////////////////////////////////////////////
// Class				:	CObject
// Method				:	dice
// Description			:	Dice the object into smaller ones
// Return Value			:
// Comments				:
// Date last edited		:	10/16/2001
void				CObject::dice(CShadingContext *rasterizer) {
}


///////////////////////////////////////////////////////////////////////
// Class				:	CObject
// Method				:	copy
// Description			:	Create a clone object
// Return Value			:
// Comments				:
// Date last edited		:	10/16/2001
void				CObject::copy(CAttributes *,CXform *,CRendererContext *) const {
	error(CODE_BUG,"An object is missing the \"copy\" function\n");
	assert(FALSE);
}


static	float	getDisp(float *mat,float disp) {
	float	tmp[4],tmp2[4];
	int		i;
	float	alpha;

	tmp[0]	=	urand();
	tmp[1]	=	urand();
	tmp[2]	=	urand();
	tmp[3]	=	urand();

	for (i=0;i<10;i++) {
		mulmp4(tmp2,mat,tmp);

		alpha	=	max(absf(tmp2[0]),absf(tmp2[1]));
		alpha	=	max(alpha,absf(tmp2[2]));
		alpha	=	max(alpha,absf(tmp2[3]));

		tmp[0]	=	tmp2[0]	/	alpha;
		tmp[1]	=	tmp2[1]	/	alpha;
		tmp[2]	=	tmp2[2]	/	alpha;
		tmp[3]	=	tmp2[3]	/	alpha;
	}
	
	return	alpha;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CObject
// Method				:	makeBound
// Description			:	Make sure we do not have empty bounding box
// Return Value			:
// Comments				:
// Date last edited		:	10/16/2001
void		CObject::makeBound(float *bmin,float *bmax) const {
	vector	D;
	float	maxD;
	float	maxDisp = attributes->maxDisplacement;

	subvv(D,bmax,bmin);
	maxD	=	D[0];
	maxD	=	max(D[1],maxD);
	maxD	=	max(D[2],maxD);
	maxD	*=	attributes->bexpand;

	// Add the displacement amount of the surface
	if (attributes->maxDisplacementSpace != NULL) {
		matrix				*from;
		matrix				*to;
		ECoordinateSystem	sys;

		if (currentRenderer->findCoordinateSystem(attributes->maxDisplacementSpace,from,to,sys)) {
			maxDisp	=	attributes->maxDisplacement	* getDisp(*from,attributes->maxDisplacement);
		}

		free(attributes->maxDisplacementSpace);
		attributes->maxDisplacementSpace	=	NULL;
	}

	maxD	+=	maxDisp;

	// Expand the bound accordingly
	subvf(bmin,maxD);
	addvf(bmax,maxD);
}








///////////////////////////////////////////////////////////////////////
// Class				:	CSurface
// Method				:	CSurface
// Description			:	Ctor
// Return Value			:
// Comments				:
// Date last edited		:	10/16/2001
CSurface::CSurface(CAttributes *a,CXform *x) : CObject(a,x) {
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSurface
// Method				:	~CSurface
// Description			:	Dtor
// Return Value			:
// Comments				:
// Date last edited		:	10/16/2001
CSurface::~CSurface() {
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSurface
// Method				:	dice
// Description			:	Dice the object into smaller ones
// Return Value			:
// Comments				:
// Date last edited		:	10/16/2001
void				CSurface::dice(CShadingContext *rasterizer) {
	CPatch	*cSurface	=	new CPatch(attributes,xform,this,0,1,0,1,0,attributes->minSplits);

	cSurface->dice(rasterizer);

	cSurface->check();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSurface
// Method				:	moving
// Description			:	TRUE if the object is moving
// Return Value			:
// Comments				:
// Date last edited		:	10/16/2001
int					CSurface::moving() const {
	return FALSE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSurface
// Method				:	sample
// Description			:	Sample a bunch of points on the surface
// Return Value			:	TRUE if the sampling was done and shaders need to be executed
// Comments				:
// Date last edited		:	10/16/2001
void				CSurface::sample(int,int,float **,unsigned int &) const {
	error(CODE_BUG,"An object is missing the \"sample\" function\n");
	assert(FALSE);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSurface
// Method				:	interpolate
// Description			:	Interpolate the varying data and set the uniform data
// Return Value			:
// Comments				:
// Date last edited		:	10/16/2001
void				CSurface::interpolate(int,float **)	const {
	error(CODE_BUG,"An object is missing the \"interpolate\" function\n");
	assert(FALSE);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CSurface
// Method				:	split
// Description			:	Split an object
// Return Value			:
// Comments				:
// Date last edited		:	10/16/2001
void				CSurface::shade(CShadingContext *context,int numRays,CRay **rays) {
	float	**varying	=	context->currentShadingState->varying;
	float	*u			=	varying[VARIABLE_U];
	float	*v			=	varying[VARIABLE_V];
	float	*time		=	varying[VARIABLE_TIME];
	float	*from		=	varying[VARIABLE_I];
	int		i;

	for (i=numRays;i>0;i--) {
		const CRay	*cRay	=	*rays++;

		*u++	=	cRay->u;
		*v++	=	cRay->v;
		*time++	=	cRay->time;
		movvv(from,cRay->from);	from	+=	3;
	}

	context->shade(this,numRays,1,-1,0);
}





