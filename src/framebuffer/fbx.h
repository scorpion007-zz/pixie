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
//  File				:	fbx.h
//  Classes				:	CXDisplay
//  Description			:	X Windows image displaying class
//
////////////////////////////////////////////////////////////////////////
#ifndef FBX_H
#define FBX_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h> 
#include <X11/keysym.h>
#include <X11/Xatom.h>
#include <pthread.h>
#include "framebuffer.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CXDisplay
// Description			:	The windows display class
// Comments				:
class	CXDisplay : public CDisplay {
public:
							CXDisplay(const char *,const char *,int,int,int);
							~CXDisplay();

	void					main();
	int						data(int,int,int,int,float *);
	void					finish();

private:
	typedef void (CXDisplay::*dataHandlerFn)(int,int,int,int,float*);
	
	void					handleData_rgb15(int,int,int,int,float*);
	void					handleData_rgb15_rev(int,int,int,int,float*);
	void					handleData_bgr15(int,int,int,int,float*);
	void					handleData_bgr15_rev(int,int,int,int,float*);
	
	void					handleData_rgb16(int,int,int,int,float*);
	void					handleData_rgb16_rev(int,int,int,int,float*);
	void					handleData_bgr16(int,int,int,int,float*);
	void					handleData_bgr16_rev(int,int,int,int,float*);
	
	void					handleData_rgba32(int,int,int,int,float*);
	void					handleData_argb32(int,int,int,int,float*);
	void					handleData_bgra32(int,int,int,int,float*);
	void					handleData_abgr32(int,int,int,int,float*);
	
	dataHandlerFn			dataHandler;
	pthread_t				thread;
	void					*imageData;
	int						imageDepth;
	int						scanWidth;
	int						windowUp;
	int						windowDown;
	Window					xcanvas;
	Display					*display;
	int						screen;
	GC						image_gc;
	XImage					*xim;
	Atom					WM_DELETE_WINDOW;
	Atom					WM_PROTOCOLS;
	char					*displayName;
};



#endif

