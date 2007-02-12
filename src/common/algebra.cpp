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
//  File				:	algebra.cpp
//  Classes				:	-
//  Description			:	Defines math
//
////////////////////////////////////////////////////////////////////////
#include "algebra.h"

// The identity matrix
const matrix	identityMatrix	=	{	1,	0,	0,	0,
										0,	1,	0,	0,
										0,	0,	1,	0,
										0,	0,	0,	1	};

///////////////////////////////////////////////////////////////////////
// 2 by 2 determinant computation
static	inline double det2x2( const double a,const double  b,const double  c,const double  d) {
	return  a * d - b * c;
}

///////////////////////////////////////////////////////////////////////
// 3 by 3 determinant computation
static	inline double det3x3(const double  a1,const double  a2,const double  a3,const double  b1,const double  b2,const double  b3,const double  c1,const double  c2,const double  c3 ) {
    return	  a1 * det2x2( b2, b3, c2, c3 )
			- b1 * det2x2( a2, a3, c2, c3 )
			+ c1 * det2x2( a2, a3, b2, b3 );
}



#define SCALAR_TYPE	float
#define VECTOR_TYPE	vector
#define MATRIX_TYPE	matrix
#include "mathSpec.cpp"
#undef SCALAR_TYPE
#undef VECTOR_TYPE
#undef MATRIX_TYPE

#define SCALAR_TYPE	double
#define VECTOR_TYPE	dvector
#define MATRIX_TYPE	dmatrix
#include "mathSpec.cpp"
#undef SCALAR_TYPE
#undef VECTOR_TYPE
#undef MATRIX_TYPE
