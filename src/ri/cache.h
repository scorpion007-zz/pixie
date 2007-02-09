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
//  File				:	cache.h
//  Classes				:	A renderer cache
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef CACHE_H
#define CACHE_H

#include "common/global.h"
#include "common/os.h"
#include "common/algebra.h"
#include "gui/opengl.h"
#include "fileResource.h"
#include "shader.h"


const	unsigned int	CACHE_SAMPLE	=	1;		// Cache needs to be sampled
const	unsigned int	CACHE_READ		=	2;		// Read the cache
const	unsigned int	CACHE_WRITE		=	4;		// Write the cache
const	unsigned int	CACHE_RDONLY	=	8;		// ONLY Read the cache

///////////////////////////////////////////////////////////////////////
// Class				:	CCache
// Description			:	Encapsulates a renderer cache
// Comments				:
class	CCache : public CFileResource, public CView {
public:
					CCache(const char *,unsigned int);
					~CCache();

	virtual	void	lookup(float *,const float *,const float *,float,CShadingContext *,const CGlobalIllumLookup *)	=	0;
	virtual	void	cachesample(float *,const float *,const float *,float)											=	0;
	virtual	void	finalize(const CGlobalIllumLookup *)	{	}

protected:
	unsigned int	flags;
};


#endif

