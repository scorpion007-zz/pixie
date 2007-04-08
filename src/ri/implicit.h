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
//  File				:	implicit.h
//  Classes				:	-
//  Description			:	Defines the interface to an implicit surface dso
//
////////////////////////////////////////////////////////////////////////
#ifndef IMPLICIT_H
#define IMPLICIT_H

#ifndef LIB_EXPORT
#ifdef _WINDOWS
#define	LIB_EXPORT				__declspec(dllexport)
#else
#define	LIB_EXPORT				extern
#endif
#endif


typedef	void		*(*implicitInitFunction)(int,float *,float *);
typedef	float		(*implicitEvalFunction)(float *,void *,const float *,float);
typedef	void		(*implicitEvalNormalFunction)(float *,void *,const float *,float);
typedef	void		(*implicitTiniFunction)(void *);

extern "C" {
	LIB_EXPORT	void		*implicitInit(int,float *,float *);
	LIB_EXPORT	float		implicitEval(float *,void *,const float *,float);
	LIB_EXPORT	void		implicitEvalNormal(float *,void *,const float *,float);
	LIB_EXPORT	void		implicitTini(void *);
};

#endif

