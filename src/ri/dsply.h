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
//  File				:	dsply.h
//  Classes				:
//  Description			:	Display server interface
//
////////////////////////////////////////////////////////////////////////
#ifndef DSPLY_H
#define DSPLY_H

#ifndef LIB_EXPORT
#if defined(_WINDOWS) || defined(WIN32)
#define	LIB_EXPORT				__declspec(dllexport)
#else
#define	LIB_EXPORT				extern
#endif
#endif

typedef enum {
	FLOAT_PARAMETER,
	VECTOR_PARAMETER,
	MATRIX_PARAMETER,
	STRING_PARAMETER,
	INTEGER_PARAMETER
} ParameterType;

typedef void	*(*TDisplayParameterFunction)(const char *,ParameterType,int);
typedef	void	*(*TDisplayStartFunction)(const char *,int,int,int,const char *,TDisplayParameterFunction);
typedef int		(*TDisplayDataFunction)(void *,int,int,int,int,float *);
typedef int		(*TDisplayRawDataFunction)(void *,int,int,int,int,void *);
typedef void	(*TDisplayFinishFunction)(void *);

extern "C" {				
	LIB_EXPORT	void						*displayStart(const char *name,int width,int height,int numSamples,const char *samples,TDisplayParameterFunction);
	LIB_EXPORT	int							displayData(void *im,int x,int y,int w,int h,float *data);
	LIB_EXPORT	int							displayRawData(void *im,int x,int y,int w,int h,void *data);
	LIB_EXPORT	void						displayFinish(void *);
}

#endif

