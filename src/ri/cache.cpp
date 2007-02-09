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
#include <math.h>

#include "cache.h"


///////////////////////////////////////////////////////////////////////
// Class				:	CCache
// Method				:	CCache
// Description			:	Ctor
// Return Value			:
// Comments				:
CCache::CCache(const char *name,unsigned int f) : CFileResource(name) {
	flags	=	f;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CCache
// Method				:	~CCache
// Description			:	Dtor
// Return Value			:
// Comments				:
CCache::~CCache() {
}

