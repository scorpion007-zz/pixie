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
#include <gdiplus.h>

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
	int				data(int,int,int,int,float *);
	void			finish();
	HANDLE			thread;

  void      redraw();
  void      redraw(HDC hdc, RECT *rcUpdate);
  void      OnMouseDown(int x, int y);
  void      OnMouseUp(int x, int y);
  void      OnMouseMove(int x, int y);
  void      OnMouseWheel(int x, int y, int zDelta);
  void      OnKeyDown(int vk);
  void      OnSize(int cx, int cy);
  void      OnGetMinMaxInfo(MINMAXINFO *mmi);
private:
	HINSTANCE		hInst;								// current instance
	HWND			hWnd;								// current window
	BITMAPINFO		info;								// bitmap info
	RGBQUAD			*bmiColors;							// the colors
	unsigned int	*imageData;
	int				active;
	int				willRedraw;

  void UpdateWinTitle();
  void ZoomImage(float mag);   // Zoom to a fixed factor.
  void ZoomDelta(float dmag);  // Zoom by some offset

  // Helper functions for common cases.
  void ZoomIn();
  void ZoomOut();
  void ActualPixels();  // Zoom to 100%.
  void CenterImage();

  ULONG_PTR gdiplusToken;
  Gdiplus::GdiplusStartupInput gdiplusStartupInput;
  TCHAR wndTitle[200];

  // Zoom origin
  POINTFLOAT zoomOrigin;
  POINTFLOAT lastPos;
  float mag_fac;
  POINT vpOrigin;  // viewport origin.
  bool mouseDown;
};



#endif

