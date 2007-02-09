//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright © 1999 - 2003, Okan Arikan
//
// Contact: okan@cs.utexas.edu
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
//  File				:	xform.h
//  Classes				:	CXform
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef XFORM_H
#define XFORM_H

#include "common/global.h"
#include "common/algebra.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CXform
// Description			:	This class encapsulates the transformation.
//							"from" is the transformation matrix from the
//							local system to the global system and "to"
//							is the transformation from global to local system
// Comments				:
class CXform {
public:
				CXform();
				CXform(CXform *);
	virtual		~CXform();

	CXform		*next;		// points to the next xform in case of motion blur
	int			refCount;

	void		attach()	{	refCount++;	}
	void		detach()	{	refCount--; if (refCount == 0) delete this; }
	void		check()		{	if (refCount == 0)	delete this;			}

	void		identity();							// Transformations
	void		translate(float,float,float);		// Concetenate from right
	void		rotate(float,float,float,float);
	void		scale(float,float,float);
	void		skew(float,float,float,float,float,float,float);
	void		concat(CXform *);
	void		invert();
	void		transformBound(float *,float *) const;
	void		invTransformBound(float *,float *) const;
	void		updateBound(float *,float *,int,const float *);

	int			normalFlip()		{
					if (flip == -1) {
						if (determinantm(from) < 0)	flip	=	TRUE;
						else						flip	=	FALSE;
					}

					return flip;
				}

	matrix		from,to;							// The actual transformation matrices
	int			flip;								// TRUE if the determinant is < 0
};

void	transformBound(float *bmax,float *bmin,const float *to,const float *obmin,const float *obmax);
#endif

