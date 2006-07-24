//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright � 1999 - 2003, Okan Arikan
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
//  File				:	xform.cpp
//  Classes				:	CXform
//  Description			:	Implementation
//
////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <math.h>

#include "xform.h"
#include "error.h"
#include "stats.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CXform
// Method				:	CXform
// Description			:	Constructor
// Return Value			:	-
// Comments				:	Identity at the beginning
// Date last edited		:	3/3/2001
CXform::CXform() {
	stats.numXforms++;
	stats.xformMemory	+=	sizeof(CXform);

	next				=	NULL;
	refCount			=	0;

	identitym(from);
	identitym(to);
	flip				=	0;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CXform
// Method				:	CXform
// Description			:	Create an exact copy of another xform
// Return Value			:	-
// Comments				:	
// Date last edited		:	3/3/2001
CXform::CXform(CXform *a) {
	stats.numXforms++;
	stats.xformMemory	+=	sizeof(CXform);

	if (a->next != NULL)
		next	=	new CXform(a->next);
	else
		next	=	NULL;

	refCount	=	0;

	movmm(from,a->from);
	movmm(to,a->to);
	flip	=	a->flip;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CXform
// Method				:	~CXform
// Description			:	Destructor
// Return Value			:	-
// Comments				:	
// Date last edited		:	3/3/2001
CXform::~CXform() {
	stats.numXforms--;
	stats.xformMemory	-=	sizeof(CXform);

	if (next != NULL)	delete next;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CXform
// Method				:	identity
// Description			:	Initialize the transformation to identity
// Return Value			:	-
// Comments				:
// Date last edited		:	3/3/2001
void	CXform::identity() {
	identitym(from);
	identitym(to);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CXform
// Method				:	translate
// Description			:	Append a translation. Note that the last
//							specified transformation is applied first
// Return Value			:	-
// Comments				:
// Date last edited		:	3/3/2001
void	CXform::translate(float dx,float dy,float dz) {
	matrix	tmp,tmp2;

	translatem(tmp,-dx,-dy,-dz);
	mulmm(tmp2,tmp,to);
	movmm(to,tmp2);

	translatem(tmp,dx,dy,dz);
	mulmm(tmp2,from,tmp);
	movmm(from,tmp2);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CXform
// Method				:	rotate
// Description			:	Append a rotation
// Return Value			:	-
// Comments				:
// Date last edited		:	3/3/2001
void	CXform::rotate(float angle,float x,float y,float z) {
	matrix		tmp,tmp2;
	const float	r	=	(float) radians(angle);

	rotatem(tmp,-x,-y,-z,r);
	mulmm(tmp2,tmp,to);
	movmm(to,tmp2);

	rotatem(tmp,x,y,z,r);
	mulmm(tmp2,from,tmp);
	movmm(from,tmp2);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CXform
// Method				:	scale
// Description			:	Append a scale
// Return Value			:	-
// Comments				:
// Date last edited		:	3/3/2001
void	CXform::scale(float sx,float sy,float sz) {
	matrix	tmp,tmp2;

	if ((sx == 0) || (sy == 0) || (sz == 0)) error(CODE_MATH,"Singular scale (%f %f %f) (ignored)\n",sx,sy,sz);
	else {
		scalem(tmp,1/sx,1/sy,1/sz);
		mulmm(tmp2,tmp,to);
		movmm(to,tmp2);

		scalem(tmp,sx,sy,sz);
		mulmm(tmp2,from,tmp);
		movmm(from,tmp2);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CXform
// Method				:	skew
// Description			:	Append a skew
// Return Value			:	-
// Comments				:
// Date last edited		:	3/3/2001
void	CXform::skew(float angle,float dx1,float dy1,float dz1,float dx2,float dy2,float dz2) {
	matrix	tmp,tmp2;
	const	float	r	=	(float) radians(angle);

	skewm(tmp,-r,dx1,dy1,dz1,dx2,dy2,dz2);
	mulmm(tmp2,tmp,to);
	movmm(to,tmp2);

	skewm(tmp,r,dx1,dy1,dz1,dx2,dy2,dz2);
	mulmm(tmp2,from,tmp);
	movmm(from,tmp2);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CXform
// Method				:	concat
// Description			:	Concetenate another transformation (This
//							transformation will be applied first)
// Return Value			:	-
// Comments				:
// Date last edited		:	3/3/2001
void	CXform::concat(CXform *x) {
	matrix	tmp;

	if (x->next != NULL) {
		if (next == NULL)	next = new CXform(this);
		next->concat(x->next);
	}

	mulmm(tmp,x->to,to);
	movmm(to,tmp);

	mulmm(tmp,from,x->from);
	movmm(from,tmp);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CXform
// Method				:	invert
// Description			:	Invert the transformation
// Return Value			:	-
// Comments				:
// Date last edited		:	3/3/2001
void	CXform::invert() {
	matrix	tmp;
	movmm(tmp,from);
	movmm(from,to);
	movmm(to,tmp);
}



///////////////////////////////////////////////////////////////////////
// Class				:	CXform
// Method				:	transformBound
// Description			:	Transfer the bounding box from one system to another
// Return Value			:	-
// Comments				:
// Date last edited		:	3/3/2001
void	CXform::transformBound(float *bmin,float *bmax) const {
	vector		corners[8];
	int			i;
	const float	*from;
	vector		vtmp;
	vector		lbmin,lbmax;


	from	=	this->from;

	// Compute & transfer the corners to the dest space
	initv(vtmp,bmin[COMP_X],bmin[COMP_Y],bmin[COMP_Z]);
	mulmp(corners[0],from,vtmp);

	initv(vtmp,bmin[COMP_X],bmin[COMP_Y],bmax[COMP_Z]);
	mulmp(corners[1],from,vtmp);

	initv(vtmp,bmin[COMP_X],bmax[COMP_Y],bmax[COMP_Z]);
	mulmp(corners[2],from,vtmp);

	initv(vtmp,bmin[COMP_X],bmax[COMP_Y],bmin[COMP_Z]);
	mulmp(corners[3],from,vtmp);

	initv(vtmp,bmax[COMP_X],bmin[COMP_Y],bmin[COMP_Z]);
	mulmp(corners[4],from,vtmp);

	initv(vtmp,bmax[COMP_X],bmin[COMP_Y],bmax[COMP_Z]);
	mulmp(corners[5],from,vtmp);

	initv(vtmp,bmax[COMP_X],bmax[COMP_Y],bmax[COMP_Z]);
	mulmp(corners[6],from,vtmp);

	initv(vtmp,bmax[COMP_X],bmax[COMP_Y],bmin[COMP_Z]);
	mulmp(corners[7],from,vtmp);

	movvv(lbmin,corners[0]);
	movvv(lbmax,corners[0]);

	for (i=1;i<8;i++) {
		addBox(lbmin,lbmax,corners[i]);
	}

	if (next != NULL) {
		from	=	next->from;

		// Compute & transfer the corners to the dest space
		initv(vtmp,bmin[COMP_X],bmin[COMP_Y],bmin[COMP_Z]);
		mulmp(corners[0],from,vtmp);

		initv(vtmp,bmin[COMP_X],bmin[COMP_Y],bmax[COMP_Z]);
		mulmp(corners[1],from,vtmp);

		initv(vtmp,bmin[COMP_X],bmax[COMP_Y],bmax[COMP_Z]);
		mulmp(corners[2],from,vtmp);

		initv(vtmp,bmin[COMP_X],bmax[COMP_Y],bmin[COMP_Z]);
		mulmp(corners[3],from,vtmp);

		initv(vtmp,bmax[COMP_X],bmin[COMP_Y],bmin[COMP_Z]);
		mulmp(corners[4],from,vtmp);

		initv(vtmp,bmax[COMP_X],bmin[COMP_Y],bmax[COMP_Z]);
		mulmp(corners[5],from,vtmp);

		initv(vtmp,bmax[COMP_X],bmax[COMP_Y],bmax[COMP_Z]);
		mulmp(corners[6],from,vtmp);

		initv(vtmp,bmax[COMP_X],bmax[COMP_Y],bmin[COMP_Z]);
		mulmp(corners[7],from,vtmp);

		for (i=0;i<8;i++) {
			addBox(lbmin,lbmax,corners[i]);
		}
	}
	movvv(bmin,lbmin);
	movvv(bmax,lbmax);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CXform
// Method				:	invTransformBound
// Description			:	Transfer the bounding box from one system to another
// Return Value			:	-
// Comments				:
// Date last edited		:	3/3/2001
void	CXform::invTransformBound(float *bmin,float *bmax) const {
	vector		corners[8];
	int			i;
	const float	*from;
	vector		vtmp;
	vector		lbmin,lbmax;


	from	=	this->to;

	// Compute & transfer the corners to the dest space
	initv(vtmp,bmin[COMP_X],bmin[COMP_Y],bmin[COMP_Z]);
	mulmp(corners[0],from,vtmp);

	initv(vtmp,bmin[COMP_X],bmin[COMP_Y],bmax[COMP_Z]);
	mulmp(corners[1],from,vtmp);

	initv(vtmp,bmin[COMP_X],bmax[COMP_Y],bmax[COMP_Z]);
	mulmp(corners[2],from,vtmp);

	initv(vtmp,bmin[COMP_X],bmax[COMP_Y],bmin[COMP_Z]);
	mulmp(corners[3],from,vtmp);

	initv(vtmp,bmax[COMP_X],bmin[COMP_Y],bmin[COMP_Z]);
	mulmp(corners[4],from,vtmp);

	initv(vtmp,bmax[COMP_X],bmin[COMP_Y],bmax[COMP_Z]);
	mulmp(corners[5],from,vtmp);

	initv(vtmp,bmax[COMP_X],bmax[COMP_Y],bmax[COMP_Z]);
	mulmp(corners[6],from,vtmp);

	initv(vtmp,bmax[COMP_X],bmax[COMP_Y],bmin[COMP_Z]);
	mulmp(corners[7],from,vtmp);

	movvv(lbmin,corners[0]);
	movvv(lbmax,corners[0]);

	for (i=1;i<8;i++) {
		addBox(lbmin,lbmax,corners[i]);
	}

	if (next != NULL) {
		from	=	next->from;

		// Compute & transfer the corners to the dest space
		initv(vtmp,bmin[COMP_X],bmin[COMP_Y],bmin[COMP_Z]);
		mulmp(corners[0],from,vtmp);

		initv(vtmp,bmin[COMP_X],bmin[COMP_Y],bmax[COMP_Z]);
		mulmp(corners[1],from,vtmp);

		initv(vtmp,bmin[COMP_X],bmax[COMP_Y],bmax[COMP_Z]);
		mulmp(corners[2],from,vtmp);

		initv(vtmp,bmin[COMP_X],bmax[COMP_Y],bmin[COMP_Z]);
		mulmp(corners[3],from,vtmp);

		initv(vtmp,bmax[COMP_X],bmin[COMP_Y],bmin[COMP_Z]);
		mulmp(corners[4],from,vtmp);

		initv(vtmp,bmax[COMP_X],bmin[COMP_Y],bmax[COMP_Z]);
		mulmp(corners[5],from,vtmp);

		initv(vtmp,bmax[COMP_X],bmax[COMP_Y],bmax[COMP_Z]);
		mulmp(corners[6],from,vtmp);

		initv(vtmp,bmax[COMP_X],bmax[COMP_Y],bmin[COMP_Z]);
		mulmp(corners[7],from,vtmp);

		for (i=0;i<8;i++) {
			addBox(lbmin,lbmax,corners[i]);
		}
	}
	movvv(bmin,lbmin);
	movvv(bmax,lbmax);
}

