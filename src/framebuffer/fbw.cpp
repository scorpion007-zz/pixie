//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright � 1999 - 2003, Okan Arikan
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

// Foward declarations of functions included in this code module:
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

#define	color(r,g,b,a)	((a << 24) | (r << 16) | (g << 8) | b)
#define	get_a(col)		((col) >> 24)
#define	get_r(col)		(((col) >> 16) & 255)
#define	get_g(col)		(((col) >> 8) & 255)
#define	get_b(col)		((col) & 255)



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
CWinDisplay::CWinDisplay(const char *name,const char *samples,int width,int height,int numSamples)
: CDisplay(name,samples,width,height,numSamples) {
	int	i,j;
	DWORD	threadID;

	hInst		=	NULL;
	hWnd		=	NULL;
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

  // Make a non-resizable window style.
  DWORD dwStyle = WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX);

  // Size of our desired client area.
  RECT rc = { 0, 0, width, height };

  // Compute the correct window size given our style.
  AdjustWindowRect(&rc, dwStyle, FALSE);

  // Create the window (non-resizable).
  hWnd = CreateWindow(szPixieWndClass, name,
    dwStyle, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left,
    rc.bottom - rc.top, NULL, NULL, hInst, NULL);

	if (!hWnd)	{
		active	=	FALSE;
		return;	// Nothing to do
	}

  // Associate a pointer to our instance with this window.
  SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)this);

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


///////////////////////////////////////////////////////////////////////
// Class				:	CWinDisplay
// Method				:	redraw
// Description			:	Redraw the image
// Return Value			:	-
// Comments				:
void	CWinDisplay::redraw(HDC hdc, RECT *rcUpdate) {
  int x, y, w, h;

  if (rcUpdate) {
    // Repaint just the dirty rect.
    x = rcUpdate->left;
    y = rcUpdate->top;
    w = min(rcUpdate->right - rcUpdate->left, width);
    h = min(rcUpdate->bottom - rcUpdate->top, height);
  } else {
    // Repaint the whole thing.
    x = 0;
    y = 0;
    w = width;
    h = height;
  }

  // NOTE: Refer to Petzold's "Programming Windows" for an explanation of
  // the strange coordinate system bitmaps and the following function use.
  SetDIBitsToDevice(hdc, x, y, w, h, x, height - y - h, 0, height,
    imageData, &info, DIB_RGB_COLORS);

  willRedraw = FALSE;
}

// Helper function to repaint the whole window, out of the WM_PAINT message.
void CWinDisplay::redraw() {
  HDC hdc = GetDC(hWnd);
  redraw(hdc, NULL);  // Repaint the whole window.
  ReleaseDC(hWnd, hdc);
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
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }

   return 0;
}

