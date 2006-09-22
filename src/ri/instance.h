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
//  File				:	instance.h
//  Classes				:	CObjectInstance
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef INSTANCE_H
#define INSTANCE_H

#include "common/global.h"
#include "object.h"
#include "hierarchy.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CObjectInstance
// Description			:	Holds an instance of an object
// Comments				:
// Date last edited		:	10/30/2002
class	CObjectInstance : public CObject {
public:
							CObjectInstance(CAttributes *,CXform *,CArray<CObject *> *);
							~CObjectInstance();

	virtual	void			bound(float *,float *) const;
	virtual	void			copy(CAttributes *,CXform *,CRendererContext *) const;

	CArray<CObject *>		*objects;
};

#endif





