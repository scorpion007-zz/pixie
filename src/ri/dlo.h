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
//  File				:	dlo.h
//  Classes				:	-
//  Description			:	Defines the interface to a dynamically loaded object
//
////////////////////////////////////////////////////////////////////////
#ifndef DLO_H
#define DLO_H

#ifndef LIB_EXPORT
#ifdef WIN32
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


