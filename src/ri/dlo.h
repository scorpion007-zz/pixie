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
//  File				:	dlo.h
//  Classes				:	-
//  Description			:	Defines the interface to a dynamically loaded object
//
////////////////////////////////////////////////////////////////////////
#ifndef DLO_H
#define DLO_H

#ifndef LIB_EXPORT
#ifdef _WINDOWS
#define	LIB_EXPORT				__declspec(dllexport)
#else
#define	LIB_EXPORT				extern
#endif
#endif


typedef	void		*(*dloInitFunction)(int,float *,float *);
typedef	int			(*dloIntersectFunction)(void *,const float *,const float *,float *,float *);
typedef	void		(*dloTiniFunction)(void *);

extern "C" {
	LIB_EXPORT	void		*dloInit(int,float *,float *);
	LIB_EXPORT	int			dloIntersect(void *,const float *,const float *,float *,float *);
	LIB_EXPORT	void		dloTini(void *);
};

#endif

