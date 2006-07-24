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
//  Classes				:	COpenGL
//  Description			:	The opengl hider
//
////////////////////////////////////////////////////////////////////////
#ifndef OPENGLHIDER_H
#define OPENGLHIDER_H

#include "common/global.h"		// The global header file
#include "opengl/opengl.h"
#include "shading.h"

///////////////////////////////////////////////////////////////////////
// Class				:	COpenGL
// Description			:	This is the fast open gl hider
// Comments				:
// Date last edited		:	10/15/2003
class	COpenGL	: public CShadingContext {
public:
									COpenGL(COptions *,CXform *,SOCKET);
			virtual					~COpenGL();

			// The main hider interface
			void					renderFrame();									// Right after world end to force rendering of the entire frame

			// Delayed rendering functions
			void					drawObject(CObject *,const float *,const float *);

			// Primitive creation functions
			void					drawGrid(CSurface *,int,int,float,float,float,float);
			void					drawRibbon(CSurface *,int,float,float);
			void					drawPoints(CSurface *,int);
protected:
			openglInitFun			glInit;
			openglTiniFun			glTini;
			openglDrawGridFun		glDrawGrid;
			void					*handle;
};

#endif


