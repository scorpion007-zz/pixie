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
//  File				:	random.cpp
//  Classes				:	CSobol, CSphereSampler, CCosineSampler
//  Description			:	Several random generators
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "random.h"


// primitive polynomials in binary encoding
const int primitive_polynomials[SOBOL_MAX_DIMENSION] =	{
  1,     3,   7,  11,  13,  19,  25,  37,  59,  47,
  61,   55,  41,  67,  97,  91, 109, 103, 115, 131,
  193, 137, 145, 143, 241, 157, 185, 167, 229, 171,
  213, 191, 253, 203, 211, 239, 247, 285, 369, 299
};

// degrees of the primitive polynomials
const int degree_table[SOBOL_MAX_DIMENSION] = {
  0, 1, 2, 3, 3, 4, 4, 5, 5, 5,
  5, 5, 5, 6, 6, 6, 6, 6, 6, 7,
  7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 
  7, 7, 7, 7, 7, 7, 7, 8, 8, 8
};


// initial values for direction tables, following
// Bratley+Fox, taken from [Sobol+Levitan, preprint 1976]
const int v_init[8][SOBOL_MAX_DIMENSION] = {
  {
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1
  },
  {
    0, 0, 1, 3, 1, 3, 1, 3, 3, 1,
    3, 1, 3, 1, 3, 1, 1, 3, 1, 3,
    1, 3, 1, 3, 3, 1, 3, 1, 3, 1,
    3, 1, 1, 3, 1, 3, 1, 3, 1, 3
  }, 
  {
    0, 0, 0, 7, 5, 1, 3, 3, 7, 5,
    5, 7, 7, 1, 3, 3, 7, 5, 1, 1,
    5, 3, 3, 1, 7, 5, 1, 3, 3, 7,
    5, 1, 1, 5, 7, 7, 5, 1, 3, 3
  }, 
  {
    0,  0,  0,  0,  0,  1,  7,  9, 13, 11,
    1,  3,  7,  9,  5, 13, 13, 11,  3, 15,
    5,  3, 15,  7,  9, 13,  9,  1, 11,  7,
    5, 15,  1, 15, 11,  5,  3,  1,  7,  9
  }, 
  {
     0,  0,  0,  0,  0,  0,  0,  9,  3, 27,
    15, 29, 21, 23, 19, 11, 25,  7, 13, 17,
     1, 25, 29,  3, 31, 11,  5, 23, 27, 19,
    21,  5,  1, 17, 13,  7, 15,  9, 31,  9
  }, 
  {
     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
     0,  0,  0, 37, 33,  7,  5, 11, 39, 63,
    27, 17, 15, 23, 29,  3, 21, 13, 31, 25,
     9, 49, 33, 19, 29, 11, 19, 27, 15, 25
  }, 
  {
     0,   0,  0,  0,  0,  0,    0,  0,  0,   0,
     0,   0,  0,  0,  0,  0,    0,  0,  0,  13,
    33, 115, 41, 79, 17,  29, 119, 75, 73, 105,
     7,  59, 65, 21,  3, 113,  61, 89, 45, 107
  }, 
  {
    0, 0, 0, 0, 0, 0, 0, 0,  0,  0,
    0, 0, 0, 0, 0, 0, 0, 0,  0,  0,
    0, 0, 0, 0, 0, 0, 0, 0,  0,  0,
    0, 0, 0, 0, 0, 0, 0, 7, 23, 39
  }
};













///////////////////////////////////////////////////////////////////////
// Function				:	sampleHemisphere
// Description			:	Sample vectors distributed uniformly in a hemisphere
// Return Value			:
// Comments				:	Z must be unit
void	sampleHemisphere(float *R,const float *Z,const float theta,CSobol<4> &generator) {
	float	P[4];
	vector	Po;
	float	cosa;
	float	sina;

	while(TRUE) {
		generator.get(P);

		// Sample a uniformly distributed point on a sphere
		P[COMP_X]	=	2*P[COMP_X]-1;
		P[COMP_Y]	=	2*P[COMP_Y]-1;
		P[COMP_Z]	=	2*P[COMP_Z]-1;

		// did we get something inside the unit sphere and non-zero
		const float l = dotvv(P,P);
		if (l < 1 && l > C_EPSILON)	break;
	}

	cosa			=	1 - P[3]*(1 - (float) cos(theta));
	sina			=	sqrtf(1 - cosa*cosa);

	// Po is orthagonal to N
	crossvv(Po,P,Z);
	// Po is unit length
	normalizev(Po);
	// Construct the sample vector
	mulvf(R,Z,cosa);
	mulvf(Po,sina);
	addvv(R,Po);
}


///////////////////////////////////////////////////////////////////////
// Function				:	sampleHemisphere
// Description			:	Sample vectors distributed uniformly in a hemisphere
// Return Value			:
// Comments				:	Z must be unit
void		sampleCosineHemisphere(float *R,const float *Z,const float theta,CSobol<4> &generator) {
	float			P[4];
	vector			Po;
	float			cosa;
	float			sina;
	const float		cosmin	=	(float) cos(theta);

	while(TRUE) {
		generator.get(P);

		// Sample a uniformly distributed point on a sphere
		P[COMP_X]	=	2*P[COMP_X]-1;
		P[COMP_Y]	=	2*P[COMP_Y]-1;
		P[COMP_Z]	=	2*P[COMP_Z]-1;

		// did we get something inside the unit sphere and non-zero
		const float l = dotvv(P,P);
		if (l < 1 && l > C_EPSILON)	break;
	}

	cosa			=	sqrtf(P[3])*(1 - cosmin) + cosmin;
	sina			=	sqrtf(1 - cosa*cosa);

	// Po is orthagonal to N
	crossvv(Po,P,Z);
	// Po is unit length
	normalizev(Po);
	// Construct the sample vector
	mulvf(R,Z,cosa);
	mulvf(Po,sina);
	addvv(R,Po);
}


///////////////////////////////////////////////////////////////////////
// Function				:	sampleSphere
// Description			:	Sample a point in a unit sphere
// Return Value			:
// Comments				:
void	sampleSphere(float *P,CSobol<3> &generator) {
	float	r[3];

	while(TRUE) {

		generator.get(r);

		// Sample a uniformly distributed point on a sphere
		P[COMP_X]	=	2*r[0]-1;
		P[COMP_Y]	=	2*r[1]-1;
		P[COMP_Z]	=	2*r[2]-1;

		if (dotvv(P,P) < 1)	break;
	}
}

