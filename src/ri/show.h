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
//  File				:	show.h
//  Classes				:	-
//  Description			:	The wrapped openGL interface
//
////////////////////////////////////////////////////////////////////////
#ifndef SHOW_H
#define SHOW_H


#include "common/global.h"
#include "shading.h"
#include "xform.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CShow
// Description			:	This is just a wrapper to visualize a file
// Comments				:
class	CShow : public CShadingContext {
public:
							CShow(int thread);
			virtual			~CShow();

			static void		preDisplaySetup();

			// Right after world end to force rendering of the entire frame
			void			renderingLoop() { }

			// Delayed rendering functions
			void			drawObject(CObject *) { }

			// Primitive creation functions
			void			drawGrid(CSurface *,int,int,float,float,float,float) { }
			void			drawPoints(CSurface *,int) { }

};

#endif

