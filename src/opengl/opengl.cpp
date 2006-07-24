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
#include <math.h>

#include "common/os.h"
#include "opengl.h"
#include "winOpenGL.h"
#include "ri/options.h"

// As mentioned in the customHider.h, we need to export the following functions
extern "C" {
LIB_EXPORT	void	openglInit(void *);
LIB_EXPORT	void	openglTini();
LIB_EXPORT	void	openglDrawGrid(int,int,const float *,const float *);
}

///////////////////////////////////////////////////////////////////////
// Function				:	openglInit
// Description			:	Init the rasterizer for a framebuffer
// Return Value			:
// Comments				:
// Date last edited		:	1/28/2002
void	openglInit(void *camera) {
	COptions	*options	=	(COptions *) camera;

	displayInit(options->xres,options->yres);

	if (options->projection == OPTIONS_PROJECTION_ORTHOGRAPHIC) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(options->screenLeft,options->screenRight,options->screenTop,options->screenBottom,options->clipMin,options->clipMax);
	} else {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(options->screenLeft,options->screenRight,options->screenTop,options->screenBottom,options->clipMin,options->clipMax);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(1,1,-1);

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);

	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


///////////////////////////////////////////////////////////////////////
// Function				:	openglTini
// Description			:	Shutdown the hardware
// Return Value			:
// Comments				:
// Date last edited		:	1/28/2002
void	openglTini() {
	while(TRUE) {
		displayRefresh();
		displayProcessEvents();
	}

	displayTini();
}


///////////////////////////////////////////////////////////////////////
// Function				:	openglTini
// Description			:	Shutdown the hardware
// Return Value			:
// Comments				:
// Date last edited		:	1/28/2002
void	openglDrawGrid(int nu,int nv,const float *P,const float *C) {
	int	i,j;

	if (TRUE) {
	//if (nu >= nv) {
		for (j=0;j<(nv-1);j++) {
			glBegin(GL_TRIANGLE_STRIP);

			for (i=0;i<nu;i++) {
				glColor3fv(	C + (j*nu + i)*3);
				glVertex3fv(P + (j*nu + i)*3);

				glColor3fv(	C + ((j+1)*nu + i)*3);
				glVertex3fv(P + ((j+1)*nu + i)*3);
			}

			glEnd();
		}
	} else {
		for (j=0;j<(nu-1);j++) {
			glBegin(GL_TRIANGLE_STRIP);

			for (i=0;i<nv;i++) {
				glColor3fv(	C + (i*nu + j)*3);
				glVertex3fv(P + (i*nu + j)*3);

				glColor3fv(	C + (j*nu + i+1)*3);
				glVertex3fv(P + (j*nu + i+1)*3);
			}

			glEnd();
		}
	}
}




