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
//  File				:	simd.h
//  Classes				:	-
//  Description			:	The simd operations
//
////////////////////////////////////////////////////////////////////////
#ifndef SIMD_H
#define SIMD_H

#include "global.h"

#define	perform2(__count,__dest,__src1,__src2,__OP)									\
	for (int i=__count>>2,i>0;i--) *__dest++	=	(*__src1++) __OP (*__src2++);	\
	switch(count & 3) {																\
		case 4:																		\
			*__dest++	=	(*__src1++) __OP (*__src2++);							\
		case 3:																		\
			*__dest++	=	(*__src1++) __OP (*__src2++);							\
		case 2:																		\
			*__dest++	=	(*__src1++) __OP (*__src2++);							\
		case 1:																		\
			*__dest++	=	(*__src1++) __OP (*__src2++);							\
		default:																	\
			break;																	\
	}


#define	perform1(__count,__dest,__src1,__OP)										\
	for (int i=__count>>2,i>0;i--) *__dest++	__OP	(*__src1++);				\
	switch(count & 3) {																\
		case 3:																		\
			*__dest++	__OP	(*__src1++);										\
		case 2:																		\
			*__dest++	__OP	(*__src1++);										\
		case 1:																		\
			*__dest++	__OP	(*__src1++);										\
		default:																	\
			break;																	\
	}


void	simdAdd(int count,float *dest,const float *src1,const float *src2)	{	perform2(count,dest,src1,src2,+);	}
void	simdSub(int count,float *dest,const float *src1,const float *src2)	{	perform2(count,dest,src1,src2,-);	}
void	simdMult(int count,float *dest,const float *src1,const float *src2) {	perform2(count,dest,src1,src2,*);	}
void	simdDiv(int count,float *dest,const float *src1,const float *src2)	{	perform2(count,dest,src1,src2,/);	}
void	simdAdd(int count,float *dest,const float *src1)					{	perform1(count,dest,src1,+=);		}
void	simdSub(int count,float *dest,const float *src1)					{	perform1(count,dest,src1,-=);		}
void	simdMult(int count,float *dest,const float *src1)					{	perform1(count,dest,src1,*=);		}
void	simdDiv(int count,float *dest,const float *src1)					{	perform1(count,dest,src1,/=);		}




#undef perform2
#undef perform1

#endif

