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
//  File				:	opengl.cpp
//  Classes				:	COpenGL
//  Description			:	The opengl hider
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "opengl.h"
#include "renderer.h"
#include "error.h"

///////////////////////////////////////////////////////////////////////
// Class				:	COpenGL
// Method				:	COpenGL
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	9/15/2003
COpenGL::COpenGL(COptions *o,CXform *a,SOCKET s) : CShadingContext(o,a,s,HIDER_NODISPLAY | HIDER_RGBAZ_ONLY) {
	char	modulePath[OS_MAX_PATH_LENGTH];

	if (currentRenderer->locateFileEx(modulePath,"opengl",osModuleExtension,proceduralPath) == TRUE) {
		handle	=	osLoadModule(modulePath);

		if (handle != NULL) {
			glInit		=	(openglInitFun)		osResolve(handle,"openglInit");
			glTini		=	(openglTiniFun)		osResolve(handle,"openglTini");
			glDrawGrid	=	(openglDrawGridFun)	osResolve(handle,"openglDrawGrid");

			if (	(glInit == NULL) || (glTini == NULL) || (glDrawGrid == NULL)	) {
				error(CODE_BUG,"OpenGL driver seems to be corrupt\n");
				osUnloadModule(handle);
				handle	=	NULL;
			}
		} else {
			error(CODE_BADFILE,"Unable to open OpenGL driver (%s)\n",osModuleError());
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	COpenGL
// Method				:	~COpenGL
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	9/15/2003
COpenGL::~COpenGL() {
	if (handle != NULL)	osUnloadModule(handle);
}

///////////////////////////////////////////////////////////////////////
// Class				:	COpenGL
// Method				:	renderFrame
// Description			:	RTender the frame
// Return Value			:	-
// Comments				:
// Date last edited		:	9/15/2003
void	COpenGL::renderFrame() {

	if (handle != NULL) {
		glInit(this);
	}
}



///////////////////////////////////////////////////////////////////////
// Class				:	COpenGL
// Method				:	drawObject
// Description			:	Draw an object
// Return Value			:	-
// Comments				:
// Date last edited		:	9/15/2003
void		COpenGL::drawObject(CObject *object,const float *bmin,const float *bmax) {
	if (inFrustrum(bmin,bmax)) {
		object->dice(this);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	COpenGL
// Method				:	renderFrame
// Description			:	RTender the frame
// Return Value			:	-
// Comments				:
// Date last edited		:	9/15/2003
void		COpenGL::drawGrid(CSurface *surface,int nu,int nv,float umin,float umax,float vmin,float vmax) {
}

///////////////////////////////////////////////////////////////////////
// Class				:	COpenGL
// Method				:	renderFrame
// Description			:	RTender the frame
// Return Value			:	-
// Comments				:
// Date last edited		:	9/15/2003
void		COpenGL::drawRibbon(CSurface *surface,int nv,float vmin,float vmax) {
}

///////////////////////////////////////////////////////////////////////
// Class				:	COpenGL
// Method				:	renderFrame
// Description			:	RTender the frame
// Return Value			:	-
// Comments				:
// Date last edited		:	9/15/2003
void		COpenGL::drawPoints(CSurface *surface,int np) {
}