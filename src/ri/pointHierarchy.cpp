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
//  File				:	pointHierarchy.cpp
//  Classes				:	CPointHierarchy
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include "pointHierarchy.h"


///////////////////////////////////////////////////////////////////////
// Class				:	CPointHierarchy
// Method				:	CPointHierarchy
// Description			:	Ctor
// Return Value			:
// Comments				:
CPointHierarchy::CPointHierarchy(const char *n,const float *from,const float *to,const float *toNDC,const char*,int) : CMapHierarchy<CPointCloudPoint>(), CTexture3d(n,from,to,toNDC) {
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPointHierarchy
// Method				:	CPointHierarchy
// Description			:	Ctor
// Return Value			:
// Comments				:
CPointHierarchy::CPointHierarchy(const char *n,const float *from,const float *to,const float *toNDC,int,char **,char **,int) : CMapHierarchy<CPointCloudPoint>(), CTexture3d(n,from,to,toNDC) {
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPointHierarchy
// Method				:	CPointHierarchy
// Description			:	Ctor
// Return Value			:
// Comments				:
CPointHierarchy::CPointHierarchy(const char *n,const float *from,const float *to,FILE *) : CMapHierarchy<CPointCloudPoint>(), CTexture3d(n,from,to) {
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPointHierarchy
// Method				:	~CPointHierarchy
// Description			:	Dtor
// Return Value			:
// Comments				:
CPointHierarchy::~CPointHierarchy() {
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPointHierarchy
// Method				:	store
// Description			:	Store smtg
// Return Value			:
// Comments				:
void		CPointHierarchy::store(const float *,const float *,const float *,float) {
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPointHierarchy
// Method				:	lookup
// Description			:	Lookup smtg
// Return Value			:
// Comments				:
void		CPointHierarchy::lookup(float *,const float *,const float *,float) {
}




