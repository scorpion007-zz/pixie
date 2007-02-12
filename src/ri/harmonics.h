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
//  File				:	harmonics.h
//  Classes				:	-
//  Description			:	Some misc spherical harmonic manipulation functions
//
////////////////////////////////////////////////////////////////////////
#ifndef HARMONICS_H
#define HARMONICS_H

#include "common/global.h"		// The global header file

///////////////////////////////////////////////////////////////////////
// Function				:	harmonicAccumulate
// Description			:	Accumulate a sample into the matrices
// Return Value			:	-
// Comments				:
inline	void	harmonicAccumulate(float *X,float *Y,const float *D,const float *C) {
	float	y[9];
	int		j,k;

	y[0]		=	(float) 0.282095;
	y[1]		=	(float) 0.488603*D[0];
	y[2]		=	(float) 0.488603*D[1];
	y[3]		=	(float) 0.488603*D[2];
	y[4]		=	(float) 1.092548*D[0]*D[1];
	y[5]		=	(float) 1.092548*D[1]*D[2];
	y[6]		=	(float) 1.092548*D[2]*D[0];
	y[7]		=	(float) 0.315392*(3*D[2]*D[2]-1);
	y[8]		=	(float) 0.546274*(D[0]*D[0]-D[1]*D[1]);

	for (j=0;j<9;j++) {
		for (k=0;k<9;k++) {
			X[k*9+j]	+=	y[j]*y[k];
		}


		Y[0*9+j]	+=	y[j]*C[0];
		Y[1*9+j]	+=	y[j]*C[1];
		Y[2*9+j]	+=	y[j]*C[2];
	}
}



///////////////////////////////////////////////////////////////////////
// Function				:	harmonicEvaluate
// Description			:	Evaluate spherical harmonics at a particular point
// Return Value			:	-
// Comments				:
inline	void	harmonicEvaluate(float *C,const float *Y,const float *D) {
	float	y[9];

	y[0]		=	(float) 0.282095;
	y[1]		=	(float) 0.488603*D[0];
	y[2]		=	(float) 0.488603*D[1];
	y[3]		=	(float) 0.488603*D[2];
	y[4]		=	(float) 1.092548*D[0]*D[1];
	y[5]		=	(float) 1.092548*D[1]*D[2];
	y[6]		=	(float) 1.092548*D[2]*D[0];
	y[7]		=	(float) 0.315392*(3*D[2]*D[2]-1);
	y[8]		=	(float) 0.546274*(D[0]*D[0]-D[1]*D[1]);

	C[0]		=	Y[0*9+0]*y[0] + 
					Y[0*9+1]*y[1] + 
					Y[0*9+2]*y[2] + 
					Y[0*9+3]*y[3] + 
					Y[0*9+4]*y[4] + 
					Y[0*9+5]*y[5] + 
					Y[0*9+6]*y[6] + 
					Y[0*9+7]*y[7] + 
					Y[0*9+8]*y[8];

	C[1]		=	Y[1*9+0]*y[0] + 
					Y[1*9+1]*y[1] + 
					Y[1*9+2]*y[2] + 
					Y[1*9+3]*y[3] + 
					Y[1*9+4]*y[4] + 
					Y[1*9+5]*y[5] + 
					Y[1*9+6]*y[6] + 
					Y[1*9+7]*y[7] + 
					Y[1*9+8]*y[8];

	C[2]		=	Y[2*9+0]*y[0] + 
					Y[2*9+1]*y[1] + 
					Y[2*9+2]*y[2] + 
					Y[2*9+3]*y[3] + 
					Y[2*9+4]*y[4] + 
					Y[2*9+5]*y[5] + 
					Y[2*9+6]*y[6] + 
					Y[2*9+7]*y[7] + 
					Y[2*9+8]*y[8];
}

///////////////////////////////////////////////////////////////////////
// Function				:	harmonicDiffuse
// Description			:	Evaluate the diffuse illumination at a point
// Return Value			:	-
// Comments				:
inline	void	harmonicDiffuse(float *C,const float *Y,const float *D) {
#define	c1	0.429043
#define	c2	0.511664
#define	c3	0.743125
#define	c4	0.886227
#define	c5	0.247708

	C[0]	=	(float) (c1*Y[0*9 + 8]*(D[0]*D[0] - D[1]*D[1])	+
				c3*Y[0*9 + 7]*D[2]*D[2] +
				c4*Y[0*9 + 0] -
				c5*Y[0*9 + 7] +
				c1*2*(Y[0*9 + 4]*D[0]*D[1]	+ Y[0*9 + 5]*D[1]*D[2]	+ Y[0*9 + 6]*D[2]*D[0]) +
				c2*2*(Y[0*9 + 1]*D[0]		+ Y[0*9 + 2]*D[1]		+ Y[0*9 + 3]*D[2]));

	C[1]	=	(float) (c1*Y[1*9 + 8]*(D[0]*D[0] - D[1]*D[1])	+
				c3*Y[1*9 + 7]*D[2]*D[2] +
				c4*Y[1*9 + 0] -
				c5*Y[1*9 + 7] +
				c1*2*(Y[1*9 + 4]*D[0]*D[1]	+ Y[1*9 + 5]*D[1]*D[2]	+ Y[1*9 + 6]*D[2]*D[0]) +
				c2*2*(Y[1*9 + 1]*D[0]		+ Y[1*9 + 2]*D[1]		+ Y[1*9 + 3]*D[2]));

	C[2]	=	(float) (c1*Y[2*9 + 8]*(D[0]*D[0] - D[1]*D[1])	+
				c3*Y[2*9 + 7]*D[2]*D[2] +
				c4*Y[2*9 + 0] -
				c5*Y[2*9 + 7] +
				c1*2*(Y[2*9 + 4]*D[0]*D[1]	+ Y[2*9 + 5]*D[1]*D[2]	+ Y[2*9 + 6]*D[2]*D[0]) +
				c2*2*(Y[2*9 + 1]*D[0]		+ Y[2*9 + 2]*D[1]		+ Y[2*9 + 3]*D[2]));


#undef c1
#undef c2
#undef c3
#undef c4
#undef c5
}


///////////////////////////////////////////////////////////////////////
// Function				:	harmonicMultiply
// Description			:	Multiply the harmonics with a normal vector
// Return Value			:	-
// Comments				:
inline	void	harmonicTransform(float *y,const float *D) {
#define	c1	0.429043
#define	c2	0.511664
#define	c3	0.743125
#define	c4	0.886227
#define	c5	0.247708


	y[0]		=	(float) (c4);
	y[1]		=	(float) (c2*2*D[0]);
	y[2]		=	(float) (c2*2*D[1]);
	y[3]		=	(float) (c2*2*D[2]);
	y[4]		=	(float) (c1*2*D[0]*D[1]);
	y[5]		=	(float) (c1*2*D[1]*D[2]);
	y[6]		=	(float) (c1*2*D[2]*D[0]);
	y[7]		=	(float) (c3*D[2]*D[2] - c5);
	y[8]		=	(float) (c1*(D[0]*D[0] - D[1]*D[1]));

#undef c1
#undef c2
#undef c3
#undef c4
#undef c5

}


///////////////////////////////////////////////////////////////////////
// Function				:	harmonicDot
// Description			:	Multiply the harmonics with a normal vector
// Return Value			:	-
// Comments				:
inline	void	harmonicDot(float *C,const float *Y,const float *y) {
	C[0]		=	Y[0*9+0]*y[0] + 
					Y[0*9+1]*y[1] + 
					Y[0*9+2]*y[2] + 
					Y[0*9+3]*y[3] + 
					Y[0*9+4]*y[4] + 
					Y[0*9+5]*y[5] + 
					Y[0*9+6]*y[6] + 
					Y[0*9+7]*y[7] + 
					Y[0*9+8]*y[8];

	C[1]		=	Y[1*9+0]*y[0] + 
					Y[1*9+1]*y[1] + 
					Y[1*9+2]*y[2] + 
					Y[1*9+3]*y[3] + 
					Y[1*9+4]*y[4] + 
					Y[1*9+5]*y[5] + 
					Y[1*9+6]*y[6] + 
					Y[1*9+7]*y[7] + 
					Y[1*9+8]*y[8];

	C[2]		=	Y[2*9+0]*y[0] + 
					Y[2*9+1]*y[1] + 
					Y[2*9+2]*y[2] + 
					Y[2*9+3]*y[3] + 
					Y[2*9+4]*y[4] + 
					Y[2*9+5]*y[5] + 
					Y[2*9+6]*y[6] + 
					Y[2*9+7]*y[7] + 
					Y[2*9+8]*y[8];
}




#endif

