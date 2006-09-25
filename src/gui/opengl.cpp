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
//  File				:	opengl
//  Classes				:
//  Description			:	Hardware resterizer
//
// !!! Work under progress !!!
////////////////////////////////////////////////////////////////////////


#ifdef QT_BUILD
#include "opengl-qt.h"
#else
#include "opengl-fltk.h"
#endif

#include "common/global.h"
#include "opengl.h"
#include "interface.h"






///////////////////////////////////////////////////////////////////////
// Function				:	pglTriangleMesh
// Description			:	Draw triangles with OpenGL
// Return Value			:	-
// Comments				:
// Date last edited		:	9/21/2006
void		pglTriangleMesh(int n,const int *indices,const float *P,const float *C) {
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,P);
	glColorPointer(3,GL_FLOAT,0,C);
	glDrawElements(GL_TRIANGLES,n,GL_UNSIGNED_INT,indices);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}


///////////////////////////////////////////////////////////////////////
// Function				:	pglTriangles
// Description			:	Draw triangles with OpenGL
// Return Value			:	-
// Comments				:
// Date last edited		:	9/21/2006
void		pglTriangles(int n,const float *P,const float *C) {
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,P);
	glColorPointer(3,GL_FLOAT,0,C);
	glDrawArrays(GL_TRIANGLES,0,n);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}



///////////////////////////////////////////////////////////////////////
// Function				:	pglTriangles
// Description			:	Draw triangles with OpenGL
// Return Value			:	-
// Comments				:
// Date last edited		:	9/21/2006
void		pglPoints(int n,const float *P,const float *C) {
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,P);
	glColorPointer(3,GL_FLOAT,0,C);
	glDrawArrays(GL_POINTS,0,n);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}





