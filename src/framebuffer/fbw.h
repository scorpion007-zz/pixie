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
//  File				:	fbw.h
//  Classes				:	CWinDisplay
//  Description			:	Windows image displaying class
//
////////////////////////////////////////////////////////////////////////
#ifndef FBW_H
#define FBW_H

#include <windows.h>

#include "framebuffer.h"


///////////////////////////////////////////////////////////////////////
// Class				:	CWinDisplay
// Description			:	The windows display class
// Comments				:
class	CWinDisplay : public CDisplay {
public:
					CWinDisplay(const char *,const char *,int,int,int);
					~CWinDisplay();

	int				ready();
	void			main();
	void			redraw();
	int				data(int,int,int,int,float *);
	void			finish();

	HANDLE			thread;

private:
	HINSTANCE		hInst;								// current instance
	HWND			hWnd;								// current window
	BITMAPINFO		info;								// bitmap info
	RGBQUAD			*bmiColors;							// the colors
	unsigned int	*imageData;
	int				active;
	int				willRedraw;
};



#endif

