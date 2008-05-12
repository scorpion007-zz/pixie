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
//  File				:	patcheUtils.cpp
//  Classes				:	
//  Description			:	Utilities for bicubic patches
//
////////////////////////////////////////////////////////////////////////

// The inverse of the Bezier basis
static	matrix	invBezier		=	{	0,		0,			0,			1.0f,
										0,		0,			1.0f/3.0f,	1.0f,
										0,		1.0f/3.0f,	2.0f/3.0f,	1.0f,
										1.0f,	1.0f,		1.0f,		1.0f};

static	dmatrix	dinvBezier		=	{	0,		0,			0,			1.0,
										0,		0,			1.0/3.0,	1.0,
										0,		1.0/3.0,	2.0/3.0,	1.0,
										1.0,	1.0,		1.0,		1.0};

// This macro is used to fix the degenerate normal vectors
#define	normalFix()	{																				\
	float		*Ng	=	varying[VARIABLE_NG];														\
																									\
	for (int i=numVertices;i>0;i--,Ng+=3) {															\
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
#define	makeCubicBound(__bmin,__bmax,__gx,__gy,__gz) {							\
	matrix	tmp1;																\
	matrix	tmp2;																\
	int		i;																	\
																				\
	mulmm(tmp1,geometryV,__gx);													\
	mulmm(tmp2,tmp1,geometryU);													\
																				\
	for (i=0;i<16;i++) {														\
		if (tmp2[i] < __bmin[COMP_X])	__bmin[COMP_X]	=	(float) tmp2[i];	\
		if (tmp2[i] > __bmax[COMP_X])	__bmax[COMP_X]	=	(float) tmp2[i];	\
	}																			\
																				\
	mulmm(tmp1,geometryV,__gy);													\
	mulmm(tmp2,tmp1,geometryU);													\
																				\
	for (i=0;i<16;i++) {														\
		if (tmp2[i] < __bmin[COMP_Y])	__bmin[COMP_Y]	=	(float) tmp2[i];	\
		if (tmp2[i] > __bmax[COMP_Y])	__bmax[COMP_Y]	=	(float) tmp2[i];	\
	}																			\
																				\
	mulmm(tmp1,geometryV,__gz);													\
	mulmm(tmp2,tmp1,geometryU);													\
																				\
	for (i=0;i<16;i++) {														\
		if (tmp2[i] < __bmin[COMP_Z])	__bmin[COMP_Z]	=	(float) tmp2[i];	\
		if (tmp2[i] > __bmax[COMP_Z])	__bmax[COMP_Z]	=	(float) tmp2[i];	\
	}																			\
}



///////////////////////////////////////////////////////////////////////
// Function				:	makeCubicBound
// Description			:	Converts the control vertices to Bezier control vertices
// Return Value			:	-
// Comments				:
#define	makeCubicBoundX(__bmin,__bmax,__gx,__gy,__gz,__xform) {					\
	dmatrix	tmp1;																\
	dmatrix	tmpX;																\
	dmatrix	tmpY;																\
	dmatrix	tmpZ;																\
	int		i;																	\
																				\
	mulmm(tmp1,geometryV,__gx);													\
	mulmm(tmpX,tmp1,geometryU);													\
																				\
	mulmm(tmp1,geometryV,__gy);													\
	mulmm(tmpY,tmp1,geometryU);													\
																				\
	mulmm(tmp1,geometryV,__gz);													\
	mulmm(tmpZ,tmp1,geometryU);													\
																				\
	for (i=0;i<16;i++) {														\
		vector	D,Dw;															\
		initv(D,(float) tmpX[i],(float) tmpY[i],(float) tmpZ[i]);				\
		mulmp(Dw,__xform->from,D);												\
		addBox(__bmin,__bmax,Dw);												\
	}																			\
}

