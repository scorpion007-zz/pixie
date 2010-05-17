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
//  File				:	fbw.cpp
//  Classes				:	CWinDisplay
//  Description			:	Implements a window that display the image
//
////////////////////////////////////////////////////////////////////////
#include "framebuffer.h"
#include "fbw.h"

#include <windowsx.h>
#include <math.h>
#include <tchar.h>

using namespace Gdiplus;

// Foward declarations of functions included in this code module:
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

#define	color(r,g,b,a)	((a << 24) | (r << 16) | (g << 8) | b)
#define	get_a(col)		((col) >> 24)
#define	get_r(col)		(((col) >> 16) & 255)
#define	get_g(col)		(((col) >> 8) & 255)
#define	get_b(col)		((col) & 255)

#define ARRAY_COUNT(x) sizeof(x)/sizeof((x)[0])

// Amount we zoom by each increment.
static const float ZOOM_INCREMENT = .1f;

// Valid for positive numbers.
inline double round(double x) {
  return (int)(x + .5);
}

///////////////////////////////////////////////////////////////////////
// Function				:	displayThread
// Description			:	Starts the display thread
// Return Value			:
// Comments				:
DWORD WINAPI  displayThread(void *w) {
	CWinDisplay	*cDisplay		=	(CWinDisplay *) w;

	// The thread main loop
	cDisplay->main();

	return 0;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CWinDisplay
// Method				:	CWinDisplay
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CWinDisplay::CWinDisplay(const char *name,
                         const char *samples,
                         int width,
                         int height,
                         int numSamples):
CDisplay(name, samples, width, height, numSamples),
mouseDown(false), mag_fac(1), hInst(NULL), hWnd(NULL) {
	int	i,j;
	DWORD	threadID;

  // Initialize GDI+.
  GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

  zoomOrigin.x = 0;
  zoomOrigin.y = 0;
  lastPos.x = 0;
  lastPos.y = 0;

	imageData	=	new unsigned int[width*height];

	// Create a checkerboard pattern
	for (i=0;i<height;i++) {
		for (j=0;j<width;j++) {
			unsigned char	d	=	255;
			int				t	=	0;

			if ((i & 63) < 32)	t ^=	1;
			if ((j & 63) < 32)	t ^=	1;

			if (t)			d	=	128;

			imageData[i*width+j]	=	color(d,d,d,d);
		}
	}

	active		=	TRUE;
	willRedraw	=	FALSE;

	// Create the thread
	thread		=	CreateThread(NULL,0,displayThread,this,0,&threadID);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CWinDisplay
// Method				:	~CWinDisplay
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CWinDisplay::~CWinDisplay() {
	delete [] imageData;
  GdiplusShutdown(gdiplusToken);
}

// Helper to get the base name from a path.
TCHAR *basename(TCHAR *path) {
  int len = _tcslen(path);
  int i;
  for (i = len-1; i >= 0; --i) {
    if (path[i] == _T('\\') || path[i] == _T('/')) {
      break;
    }
  }
  if (i >= 0) {
    return path+i+1;
  } else {
    return path;
  }
}

// Makes a title for the framebuffer window, containing various pieces of
// information.
// Parameters:
//  buf - buffer to write string to.
//  cch - count of characters available in buf.
//  file_name - Name of image we're displaying.
//  mag_fac - magnification factor.
void MakeWindowTitle(TCHAR *buf, size_t cch, TCHAR *file_name, float mag_fac) {
  TCHAR *szBasename = basename(file_name);
  _sntprintf(buf, cch-1, "%s [%d%%] - Pixie", szBasename,
    (int)(round(mag_fac * 100)));
  buf[cch-1] = 0;  // Null-terminate it.
}

void CWinDisplay::UpdateWinTitle() {
  MakeWindowTitle(wndTitle, ARRAY_COUNT(wndTitle), name, mag_fac);
  SetWindowText(hWnd, wndTitle);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CWinDisplay
// Method				:	main
// Description			:	The main display loop
// Return Value			:	-
// Comments				:
void	CWinDisplay::main() {
	WNDCLASSEX	wcex;
	MSG			msg;
  const char *szPixieWndClass = "PixieWinDisplay";

	hInst							= (HINSTANCE) GetModuleHandle(NULL);

	wcex.cbSize						= sizeof(WNDCLASSEX);

	wcex.style						= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc				= (WNDPROC)	WndProc;
	wcex.cbClsExtra					= 0;
	wcex.cbWndExtra					= 0;
	wcex.hInstance					= hInst;
	wcex.hIcon						= LoadIcon(NULL,IDI_APPLICATION);
	wcex.hCursor					= LoadCursor(NULL,IDC_ARROW);
	wcex.hbrBackground				= NULL;
	wcex.lpszMenuName				= NULL;
	wcex.lpszClassName				= szPixieWndClass;
	wcex.hIconSm					= LoadIcon(NULL,IDI_APPLICATION);

	RegisterClassEx(&wcex);

  // Define our window style.
  DWORD dwStyle = WS_OVERLAPPEDWINDOW;

  // Size of our desired client area.
  RECT rc = { 0, 0, width, height };

  // Compute the correct window size given our style.
  AdjustWindowRect(&rc, dwStyle, FALSE);

  // Create the initial title for the window.
  MakeWindowTitle(wndTitle, ARRAY_COUNT(wndTitle), name, mag_fac);

  // Create the window (non-resizable).
  hWnd = CreateWindow(szPixieWndClass, wndTitle,
    dwStyle, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left,
    rc.bottom - rc.top, NULL, NULL, hInst, NULL);

	if (!hWnd)	{
		active	=	FALSE;
		return;	// Nothing to do
	}

  // Associate a pointer to our instance with this window.
  SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)this);

  ActualPixels();

	// Show the window
	ShowWindow(hWnd,SW_SHOW);
	UpdateWindow(hWnd);

	// Set up the bitmap
	info.bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);
	info.bmiHeader.biWidth			= width;
	info.bmiHeader.biHeight			= height;
	info.bmiHeader.biPlanes			= 1;
	info.bmiHeader.biBitCount		= 32;
	info.bmiHeader.biCompression	= BI_RGB;
	info.bmiHeader.biSizeImage		= 0;
	info.bmiHeader.biXPelsPerMeter	= 2834;
	info.bmiHeader.biYPelsPerMeter	= 2834;
	info.bmiHeader.biClrUsed		= 0;
	info.bmiHeader.biClrImportant	= 0;

	// Display the checkerboard
	redraw();

	// Main message loop:
	while (GetMessage(&msg, NULL, 0,0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	active	=	FALSE;
}

void CWinDisplay::OnMouseDown(int x, int y) {
  mouseDown = true;
  lastPos.x = (float)x;
  lastPos.y = (float)y;

  InvalidateRect(hWnd, NULL, TRUE);
  SetCapture(hWnd);
}

void CWinDisplay::OnSize(int cx, int cy) {
  UNREFERENCED_PARAMETER(cx);
  UNREFERENCED_PARAMETER(cy);
  CenterImage();
}

void CWinDisplay::OnGetMinMaxInfo(MINMAXINFO *mmi) {
  // Restrict the minimum size of the window.
  mmi->ptMinTrackSize.x = 250;
  mmi->ptMinTrackSize.y = 150;
}

void CWinDisplay::OnMouseUp(int x, int y) {
  mouseDown = false;
  lastPos.x = (float)x;
  lastPos.y = (float)y;
  ReleaseCapture();
}

void CWinDisplay::OnMouseMove(int x, int y) {
  if (mouseDown) {
    float dx = (x - lastPos.x);
    float dy = (y - lastPos.y);

    zoomOrigin.x += dx;
    zoomOrigin.y += dy;
    InvalidateRect(hWnd, NULL, TRUE);

    lastPos.x = (float)x;
    lastPos.y = (float)y;
  }
}

template<class T>
inline T clamp(T x, T low, T high) {
  if (x < low) {
    x = low;
  } else if (x > high) {
    x = high;
  }
  return x;
}

void CWinDisplay::OnMouseWheel(int x, int y, int zDelta) {
  UNREFERENCED_PARAMETER(x);
  UNREFERENCED_PARAMETER(y);
  if (zDelta > 0) {
    ZoomIn();
  } else {
    ZoomOut();
  }
}

void CWinDisplay::ZoomDelta(float dmag) {
  ZoomImage(mag_fac + dmag);
}

void CWinDisplay::ZoomIn() {
  ZoomDelta(ZOOM_INCREMENT);
}

void CWinDisplay::ZoomOut() {
  ZoomDelta(-ZOOM_INCREMENT);
}

void CWinDisplay::CenterImage() {
  RECT rc;
  GetClientRect(hWnd, &rc);

  zoomOrigin.x = ((rc.right - rc.left) - width*mag_fac)/2;
  zoomOrigin.y = ((rc.bottom - rc.top) - height*mag_fac)/2;
}

void CWinDisplay::ActualPixels() {
  ZoomImage(1);
  CenterImage();
}

void CWinDisplay::ZoomImage(float mag) {
  const float MINZOOM = .2f;
  const float MAXZOOM = 10.f;

  mag_fac = mag;

  // Clamp zoom.
  mag_fac = clamp(mag_fac, MINZOOM, MAXZOOM);

  UpdateWinTitle();

  InvalidateRect(hWnd, NULL, TRUE);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CWinDisplay
// Method				:	redraw
// Description			:	Redraw the image
// Return Value			:	-
// Comments				:
void	CWinDisplay::redraw(HDC hdc, RECT *rcUpdate) {
  Graphics graphics(hdc);
  graphics.SetInterpolationMode(InterpolationModeNearestNeighbor);
  Bitmap bm(&info, imageData);

  float dstx = zoomOrigin.x;
  float dsty = zoomOrigin.y;

  float dstw = width*mag_fac;
  float dsth = height*mag_fac;

  // Entire surface.
  RECT rc = { 0, 0, width, height };

  ExcludeClipRect(hdc, (int)dstx, (int)dsty,
    (int)(dstx+dstw), (int)(dsty+dsth));

  FillRect(hdc, rcUpdate ? rcUpdate : &rc, GetStockBrush(GRAY_BRUSH));
  SelectClipRgn(hdc, NULL);

  RectF dest(dstx, dsty, dstw, dsth);
  graphics.DrawImage(&bm, dest);
  willRedraw = FALSE;
}

// Helper function to repaint the whole window, out of the WM_PAINT message.
void CWinDisplay::redraw() {
  HDC hdc = GetDC(hWnd);
  redraw(hdc, NULL);  // Repaint the whole window.
  ReleaseDC(hWnd, hdc);
}

void CWinDisplay::OnKeyDown(int vk) {
  switch(vk) {
    case VK_NUMPAD0:
      ActualPixels();  // Zoom to 100%.
      break;
  }
}

///////////////////////////////////////////////////////////////////////
// Class				:	CWinDisplay
// Method				:	data
// Description			:	Draw the data onto the screen
// Return Value			:	-
// Comments				:
int	CWinDisplay::data(int x,int y,int w,int h,float *d) {
	int	i,j;

	clampData(w,h,d);

	for (i=0;i<h;i++) {
		const float		*src	=	&d[i*w*numSamples];
		unsigned int	*dest	=	&imageData[((height-(i+y)-1)*width+x)];

		switch(numSamples) {
		case 0:
			break;
		case 1:
			for (j=0;j<w;j++) {
				unsigned char	d	=	(unsigned char) (src[0]*255);

				*dest++				=	color(d,d,d,d);
				src++;
			}
			break;
		case 2:
			for (j=0;j<w;j++) {
				const float		r	=	src[0]*src[1]*255	+ (1-src[1])*get_r(dest[0]);
				const float		a	=	src[1]*255			+ (1-src[1])*get_a(dest[0]);
				unsigned char	dr	=	(unsigned char) r;
				unsigned char	da	=	(unsigned char) a;

				*dest++				=	color(dr,dr,dr,da);

				src					+=	2;
			}
			break;
		case 3:
			for (j=0;j<w;j++) {
				unsigned char	dr	=	(unsigned char) (src[0]*255);
				unsigned char	dg	=	(unsigned char) (src[1]*255);
				unsigned char	db	=	(unsigned char) (src[2]*255);

				*dest++				=	color(dr,dg,db,(unsigned char) 255);

				src					+=	3;
			}
			break;
		case 4:
			for (j=0;j<w;j++) {
				const float		r	=	src[0]*src[3]*255	+ (1-src[3])*get_r(dest[0]);
				const float		g	=	src[1]*src[3]*255	+ (1-src[3])*get_g(dest[0]);
				const float		b	=	src[2]*src[3]*255	+ (1-src[3])*get_b(dest[0]);
				const float		a	=	src[3]*255			+ (1-src[3])*get_a(dest[0]);
				unsigned char	dr	=	(unsigned char) r;
				unsigned char	dg	=	(unsigned char) g;
				unsigned char	db	=	(unsigned char) b;
				unsigned char	da	=	(unsigned char) a;

				*dest++				=	color(dr,dg,db,da);

				src					+=	4;
			}
			break;
		default:
			for (j=0;j<w;j++) {
				float			r	=	src[0]*src[3]*255	+ (1-src[3])*get_r(*dest);
				float			g	=	src[1]*src[3]*255	+ (1-src[3])*get_g(*dest);
				float			b	=	src[2]*src[3]*255	+ (1-src[3])*get_b(*dest);
				float			a	=	src[3]*255			+ (1-src[3])*get_a(*dest);
				unsigned char	dr	=	(unsigned char) r;
				unsigned char	dg	=	(unsigned char) g;
				unsigned char	db	=	(unsigned char) b;
				unsigned char	da	=	(unsigned char) a;

				*dest++				=	color(dr,dg,db,da);

				src					+=	numSamples;
			}
			break;
		}
	}

	if (active) {
		if (willRedraw == FALSE) {
			// Pump messages
			willRedraw	=	TRUE;
			PostMessage(hWnd,WM_PAINT,(WPARAM) this,0);
		}
	}

	return active;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CWinDisplay
// Method				:	finish
// Description			:	Finish displaying the data
// Return Value			:	-
// Comments				:
void	CWinDisplay::finish() {
	// Pump the redraw message
	redraw();

	// Wait for the user to close the window
	WaitForSingleObject(thread,INFINITE);
}

///////////////////////////////////////////////////////////////////////
// Method				:	WndProc
// Description			:	Windows callback function
// Return Value			:	-
// Comments				:
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  CWinDisplay *dpy = (CWinDisplay *)GetWindowLongPtr(hWnd, GWLP_USERDATA);

	switch (message) {
    case WM_PAINT: {
      PAINTSTRUCT ps;
      BeginPaint(hWnd, &ps);
      dpy->redraw(ps.hdc, &ps.rcPaint);
      EndPaint(hWnd, &ps);
      break;
    }
    case WM_LBUTTONDOWN:
      dpy->OnMouseDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
      break;
    case WM_LBUTTONUP:
      dpy->OnMouseUp(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
      break;
    case WM_MOUSEMOVE:
      dpy->OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
      break;
    case WM_MOUSEWHEEL:
      dpy->OnMouseWheel(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam),
        GET_WHEEL_DELTA_WPARAM(wParam));
      break;
    case WM_KEYDOWN:
      dpy->OnKeyDown(wParam);
      break;
    case WM_SIZE:
      dpy->OnSize(LOWORD(lParam), HIWORD(lParam));
      break;
    case WM_GETMINMAXINFO:
      dpy->OnGetMinMaxInfo((MINMAXINFO*)lParam);
      break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }

   return 0;
}

