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
//  File				:	refCounter.h
//  Classes				:	CRefCounter
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef REFCOUNTER_H
#define REFCOUNTER_H

#include "common/global.h"
#include "atomic.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CRefCounter
// Description			:	Reference counter
// Comments				:
class	CRefCounter {
public:
						CRefCounter();
			virtual		~CRefCounter();

			void		attach()	{	atomicIncrement(&refCount);	}
			void		detach()	{	if (atomicDecrement(&refCount) == 0) delete this; }

			int			refCount;
};

#endif
