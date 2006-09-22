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
//  File				:	opengl.h
//  Classes				:	-
//  Description			:	The wrapped openGL interface
//
////////////////////////////////////////////////////////////////////////
#ifndef OPENGLWRAP_H
#define OPENGLWRAP_H


#include "common/global.h"
#include "shading.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CShow
// Description			:	This is just a wrapper to visualize a file
// Comments				:
// Date last edited		:	8/26/2001
class	CShow : public CShadingContext {
public:
							CShow(COptions *,CXform *,SOCKET);
			virtual			~CShow();

			// Right after world end to force rendering of the entire frame
			void			renderFrame() { }

			// Delayed rendering functions
			void			drawObject(CObject *,const float *,const float *) { }

			// Primitive creation functions
			void			drawGrid(CSurface *,int,int,float,float,float,float) { }
			void			drawRibbon(CSurface *,int,float,float) { }
			void			drawPoints(CSurface *,int) { }

};

#endif



