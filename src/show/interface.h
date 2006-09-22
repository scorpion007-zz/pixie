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
//  File				:	interface.h
//  Classes				:	CInterface
//  Description			:	Displays the user interface
//
////////////////////////////////////////////////////////////////////////
#ifndef INTERFACE_H
#define INTERFACE_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>

#include "common/os.h"
#include "common/algebra.h"

const	int	MOUSE_LEFT			=	1;
const	int	MOUSE_RIGHT			=	2;
const	int	DO_ZOOM				=	4;

///////////////////////////////////////////////////////////////////////
// Class				:	CInterface
// Description			:	Handles 3D user interface
// Comments				:
// Date last edited		:	8/23/2001
class	CInterface : public Fl_Gl_Window {
public:
							CInterface();
	virtual					~CInterface();

							// Fl functions:
			void			draw();
			int				handle(int);
			void			resize(int,int,int,int);
			void			refresh();

	virtual	void			drawScene();
	virtual	void			leftMouseDown(int,int);
	virtual	void			leftMouseUp(int,int);
	virtual	void			mouseMove(int,int);
	virtual	void			keyDown(char);
	virtual	void			keyUp(char);
	virtual	void			print(float,float,char *,...);
	virtual	void			print(char *,...);

			int				mouseState;

			vector			lastVec;
			matrix			last,lastInverse;
			matrix			current,currentInverse;
			int				width,height;		// Of the interface region

			float			fov;
			float			clipMin,clipMax;
			int				active;
			float			zoomAmt;
};

#endif



