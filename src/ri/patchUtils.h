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
//  File				:	patcheUtils.cpp
//  Classes				:	
//  Description			:	Utilities for bicubic patches
//
////////////////////////////////////////////////////////////////////////

// The inverse of the Bezier basis
static	double	invBezier[16]	=	{	0,		0,			0,			1.0,
										0,		0,			1.0/3.0,	1.0,
										0,		1.0/3.0,	2.0/3.0,	1.0,
										1.0,	1.0,		1.0,		1.0};


static	double	geometryU[16],geometryV[16];

#define	mulmmd(__result,__s1,__s2) {												\
	int i,j,k;																		\
																					\
	for (i=0;i<4;i++)																\
		for (j=0;j<4;j++) {															\
				double &dest	=	__result[element(i,j)];							\
																					\
				dest		=	0;													\
				for (k=0;k<4;k++) dest	+=	__s1[element(i,k)]*__s2[element(k,j)];	\
		}																			\
}

// This macro is used to fix the degenerate normal vectors
#define	normalFix()	{																				\
	float		*Ng	=	varying[VARIABLE_NG];														\
	int			i;																					\
																									\
	for (i=numVertices;i>0;i--,Ng+=3) {																\
		if (dotvv(Ng,Ng) == 0) {																	\
			const float	*u		=	varying[VARIABLE_U];											\
			const float	*v		=	varying[VARIABLE_V];											\
			const float	*cNg	=	varying[VARIABLE_NG];											\
			const float	cu		=	u[numVertices-i];												\
			const float	cv		=	v[numVertices-i];												\
			float		cd		=	C_INFINITY;														\
			const float	*closest=	Ng;																\
			int			j;																			\
																									\
			for (j=numVertices;j>0;j--,cNg+=3,u++,v++) {											\
				if (dotvv(cNg,cNg) > 0) {															\
					const float	du	=	cu - u[0];													\
					const float	dv	=	cv - v[0];													\
					float		d;																	\
																									\
					d	=	du*du + dv*dv;															\
					if (d < cd) {																	\
						cd		=	d;																\
						closest	=	cNg;															\
					}																				\
				}																					\
			}																						\
																									\
			movvv(Ng,closest);																		\
		}																							\
	}																								\
}


///////////////////////////////////////////////////////////////////////
// Function				:	makeCubicBound
// Description			:	Converts the control vertices to Bezier control vertices
// Return Value			:	-
// Comments				:
// Date last edited		:	5/25/2004
static	inline	void	makeCubicBound(float *bmin,float *bmax,double *gx,double *gy,double *gz) {
	double	tmp1[16];
	double	tmp2[16];
	int		i;

	mulmmd(tmp1,geometryV,gx);
	mulmmd(tmp2,tmp1,geometryU);

	for (i=0;i<16;i++) {
		if (tmp2[i] < bmin[COMP_X])	bmin[COMP_X]	=	(float) tmp2[i];
		if (tmp2[i] > bmax[COMP_X])	bmax[COMP_X]	=	(float) tmp2[i];
	}

	mulmmd(tmp1,geometryV,gy);
	mulmmd(tmp2,tmp1,geometryU);

	for (i=0;i<16;i++) {
		if (tmp2[i] < bmin[COMP_Y])	bmin[COMP_Y]	=	(float) tmp2[i];
		if (tmp2[i] > bmax[COMP_Y])	bmax[COMP_Y]	=	(float) tmp2[i];
	}

	mulmmd(tmp1,geometryV,gz);
	mulmmd(tmp2,tmp1,geometryU);

	for (i=0;i<16;i++) {
		if (tmp2[i] < bmin[COMP_Z])	bmin[COMP_Z]	=	(float) tmp2[i];
		if (tmp2[i] > bmax[COMP_Z])	bmax[COMP_Z]	=	(float) tmp2[i];
	}
}
