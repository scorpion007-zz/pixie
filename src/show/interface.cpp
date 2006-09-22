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
//  File				:	interface.cpp
//  Classes				:
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>

#include "interface.h"

#include <GL/glu.h>

///////////////////////////////////////////////////////////////////////
// Class				:	CInterface
// Method				:	CInterface
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	1/14/2002
CInterface::CInterface() : Fl_Gl_Window(640,480,"View") {
	size_range(640,480);

	mode(FL_RGB | FL_DOUBLE | FL_DEPTH);

	identitym(current);
	identitym(currentInverse);
	identitym(last);
	identitym(lastInverse);

	mouseState				=	0;

	clipMin					=	0.01f;
	clipMax					=	100.0f;

	fov						=	1.5;

	width					=	640;
	height					=	480;

	active					=	TRUE;
	
	zoomAmt					=	0;

	end();
	show();

	make_current();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CInterface
// Method				:	~CInterface
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	1/14/2002
CInterface::~CInterface() {
	hide();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CInterface
// Method				:	draw
// Description			:	Draw whatever we wantto draw
// Return Value			:	-
// Comments				:
// Date last edited		:	1/14/2002
void		CInterface::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (!valid()) {
		valid(1);
		glViewport(0,0,w(),h());
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-clipMin,clipMin,-clipMin,clipMin,clipMin*fov,clipMax);
		glMatrixMode(GL_MODELVIEW);
	}

	glLoadIdentity();
	glTranslatef(0,0,-1);

	//glLoadMatrixf(current);
	glMultMatrixf(current);

	drawScene();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CInterface
// Method				:	refresh
// Description			:	Refresh the window
// Return Value			:	-
// Comments				:
// Date last edited		:	1/14/2002
void		CInterface::refresh() {
	redraw();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CInterface
// Method				:	handle
// Description			:	Handle events
// Return Value			:	-
// Comments				:
// Date last edited		:	1/14/2002
int			CInterface::handle(int event) {
	switch(event) {
	case FL_PUSH:
		leftMouseDown(Fl::event_x(),Fl::event_y());
		break;
	case FL_RELEASE:
		leftMouseUp(Fl::event_x(),Fl::event_y());
		break;
	case FL_DRAG:
		mouseMove(Fl::event_x(),Fl::event_y());
		break;
	case FL_KEYDOWN:
		keyDown(Fl::event_key());
		break;
	case FL_KEYUP:
		keyUp(Fl::event_key());
		break;
	case FL_MOUSEWHEEL:
		{
		// Left and right - Zoom
		matrix	zoom,zoomInverse;
		
		if ( zoomAmt == 0 ){
			movmm(last,current);
			movmm(lastInverse,currentInverse);
		}
		
		zoomAmt += Fl::event_dy()/40.0f;
		translatem(zoom,0,0,-zoomAmt);
		translatem(zoomInverse,0,0,zoomAmt);

		mulmm(current,zoom,last);
		mulmm(currentInverse,lastInverse,zoomInverse);
		
		redraw();
		break;
		}
	default:
		break;
	}

	return 0;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CInterface
// Method				:	resize
// Description			:	Handle the resize
// Return Value			:	-
// Comments				:
// Date last edited		:	1/14/2002
void			CInterface::resize(int x,int y,int w,int h) {
	Fl_Gl_Window::resize(x,y,w,h);
	width	=	w;
	height	=	h;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CInterface
// Method				:	draw
// Description			:	Do the actual drawing
// Return Value			:	-
// Comments				:
// Date last edited		:	1/14/2002
void		CInterface::drawScene()	{
}

///////////////////////////////////////////////////////////////////////
// Class				:	CInterface
// Method				:	leftMouseDown
// Description			:	Left mouse button has been pressed
// Return Value			:	-
// Comments				:
// Date last edited		:	1/14/2002
void		CInterface::leftMouseDown(int x,int y)	{
	// Figure out which button was pressed
	if (Fl::event_button() == 1)
		mouseState	|=	MOUSE_LEFT;
	else
		mouseState	|=	MOUSE_RIGHT;

	// Process
	vector	currentVec;

	movmm(last,current);
	movmm(lastInverse,currentInverse);
	zoomAmt = 0;

	currentVec[COMP_X]	=	(float) (x - width / 2);
	currentVec[COMP_Y]	=	(float) -(y - height / 2);
	currentVec[COMP_Z]	=	0;
	mulvf(currentVec,2 / (float) min(width,height));

	if (mouseState & MOUSE_LEFT) {
		if (mouseState & MOUSE_RIGHT || mouseState & DO_ZOOM) {
			// Left and right - Zoom
			movvv(lastVec,currentVec);
		} else {
			float	temp;

			// Left only - Rotate
			temp	=	dotvv(currentVec,currentVec);
			if (temp > 1) {
				normalizev(currentVec);
			} else {
				currentVec[COMP_Z]	=	sqrtf(1 - temp);
			}

			movvv(lastVec,currentVec);
		}
	} else if (mouseState & MOUSE_RIGHT) {
		// Right only - Pan
		movvv(lastVec,currentVec);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CInterface
// Method				:	leftMouseUp
// Description			:	Left mouse button has been released
// Return Value			:	-
// Comments				:
// Date last edited		:	1/14/2002
void		CInterface::leftMouseUp(int x,int y)	{
	if (Fl::event_button() == 1)
		mouseState	&=	~MOUSE_LEFT;
	else
		mouseState	&=	~MOUSE_RIGHT;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CInterface
// Method				:	mouseMove
// Description			:	Mouse moved
// Return Value			:	-
// Comments				:
// Date last edited		:	1/14/2002
void		CInterface::mouseMove(int x,int y)	{
	vector	currentVec;

	currentVec[COMP_X]	=	(float) (x - width / 2);
	currentVec[COMP_Y]	=	(float) -(y - height / 2);
	currentVec[COMP_Z]	=	0;
	mulvf(currentVec,2 / (float) min(width,height));

	if (mouseState & MOUSE_LEFT) {
		if (mouseState & MOUSE_RIGHT) {
			matrix	zoom,zoomInverse;

			// Left and right - Zoom
			translatem(zoom,0,0,-(lastVec[COMP_Y] - currentVec[COMP_Y]));
			translatem(zoomInverse,0,0,(lastVec[COMP_Y] - currentVec[COMP_Y]));

			mulmm(current,zoom,last);
			mulmm(currentInverse,lastInverse,zoomInverse);
		} else {
			float	temp,rdot,rtheta;
			matrix	ball,ballInverse;
			vector	axis;

			// Left only - Rotate
			temp	=	dotvv(currentVec,currentVec);
			if (temp > 1) {
				normalizev(currentVec);
			} else {
				currentVec[COMP_Z]	=	sqrtf(1 - temp);
			}

			rdot	=	max(min(dotvv(currentVec,lastVec),1),-1);
			rtheta	=	(float) acos(rdot);
			
			crossvv(axis,lastVec,currentVec);
			normalizev(axis);

			rotatem(ball,axis,rtheta);
			rotatem(ballInverse,axis,-rtheta);

			mulmm(current,ball,last);
			mulmm(currentInverse,lastInverse,ballInverse);
		}
	} else if (mouseState & MOUSE_RIGHT) {
		// Right only - Pan
		matrix	pan,panInverse;
		vector	tmp;

		// Left and right - Zoom
		subvv(tmp,currentVec,lastVec);
		translatem(pan,tmp[COMP_X],tmp[COMP_Y],tmp[COMP_Z]);
		translatem(panInverse,-tmp[COMP_X],-tmp[COMP_Y],-tmp[COMP_Z]);

		mulmm(current,pan,last);
		mulmm(currentInverse,lastInverse,panInverse);
	}

	redraw();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CInterface
// Method				:	keyDown
// Description			:	Key pressed
// Return Value			:	-
// Comments				:
// Date last edited		:	1/14/2002
void		CInterface::keyDown(char key)	{
}


///////////////////////////////////////////////////////////////////////
// Class				:	CInterface
// Method				:	keyUp
// Description			:	Key released
// Return Value			:	-
// Comments				:
// Date last edited		:	1/14/2002
void		CInterface::keyUp(char key)	{
}

///////////////////////////////////////////////////////////////////////
// Class				:	CInterface
// Method				:	print
// Description			:	Display a string
// Return Value			:
// Comments				:
// Date last edited		:	8/23/2001
void	CInterface::print(float x,float y,char *mes,...) {
	if (active == FALSE)	return;

	char	tmp[256];
	va_list	args;

	va_start(args,mes);
	vsprintf(tmp,mes,args);
	va_end(args);

	glColor3f(1,1,1);
	gl_font(FL_TIMES,12);
	

	glPushMatrix();
	glLoadIdentity();
	glRasterPos3f(2*x / (float) width - 1,1 - 2*(y+12) / (float) height, -1*fov);
	gl_draw(tmp);
	glPopMatrix();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CInterface
// Method				:	print
// Description			:	Display a string
// Return Value			:
// Comments				:
// Date last edited		:	8/23/2001
void	CInterface::print(char *mes,...) {
	if (active == FALSE)	return;

	char	tmp[256];
	va_list	args;

	va_start(args,mes);
	vsprintf(tmp,mes,args);
	va_end(args);

	gl_font(FL_TIMES,12);	
	gl_draw(tmp);
}


