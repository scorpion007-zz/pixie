//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright � 1999 - 2010, Okan Arikan
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
//  File				:	depository.h
//  Classes				:	CDepository
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef DEPOSITORY_H
#define DEPOSITORY_H

#include "common/global.h"
#include "map.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CDepositorySample
// Description			:
/// \brief					This class holds a depository sample
// Comments				:
class CDepositorySample : public CMapItem {
public:
	float	C[7];
};



///////////////////////////////////////////////////////////////////////
// Class				:	CLocalHash
// Description			:
/// \brief					A hash that holds the contribution that comes from nearby geometry
// Comments				:
class	CDepository : public CMap<CDepositorySample> {
public:
				CDepository();
				~CDepository();

	void		lookup(float *,const float *,const float *);
};



#endif

