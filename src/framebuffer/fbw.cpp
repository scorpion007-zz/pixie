//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright © 1999 - 2010, Okan Arikan
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
//  Description			:
/// \brief					Implements a window that display the image
//
////////////////////////////////////////////////////////////////////////
#include "framebuffer.h"
#include "fbw.h"

#include "resource.h"

#include <windowsx.h>
#include <math.h>
#include <tchar.h>

using namespace Gdiplus;

static HINSTANCE hInst;  // Our DLL's instance.

// Foward declarations of functions included in this code module:
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
void GenCheckerboard(unsigned int *buf, int w, int h);

#define	color(r,g,b,a)	((a << 24) | (r << 16) | (g << 8) | b)
#define	get_a(col)		((col) >> 24)
#define	get_r(col)		(((col) >> 16) & 255)
#define	get_g(col)		(((col) >> 8) & 255)
#define	get_b(col)		((col) & 255)

#define ARRAY_COUNT(x) (sizeof(x)/sizeof((x)[0]))

// Channel manipulation macros.
#define TEST_CHANNEL(x, channel) ((x) & (1 << (channel)))
#define SET_CHANNEL(x, channel) ((x) |= (1 << (channel)))
#define UNSET_CHANNEL(x, channel) ((x) &= ~(1 << (channel)))
#define TOGGLE_CHANNEL(x, channel) ((x) ^= (1 << (channel)))
#define EXTRACT_CHANNEL(x, channel) (((x) >> (16 - 8 * (channel))) & 0xFF)

// Amount we zoom by each increment.
static const float ZOOM_INCREMENT = .1f;

// Valid for positive numbers.
inline double round(double x) {
  return (int)(x + .5);
}

///////////////////////////////////////////////////////////////////////
// Function				:	displayThread
// Description			:
/// \brief					Starts the display thread
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
// Description			:
/// \brief					Ctor
// Return Value			:	-
// Comments				:
CWinDisplay::CWinDisplay(const char *name,
                         const char *samples,
                         int width,
                         int height,
                         int numSamples):
CDisplay(name, samples, width, height, numSamples),
mouseDown(false), mag_fac(1), hWnd(NULL), m_channels(0),
m_alpha(false) {
	DWORD	threadID;

  memset(m_channelsPresent, 0, sizeof(m_channelsPresent));

  // Initialize GDI+.
  GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

  zoomOrigin.x = 0;
  zoomOrigin.y = 0;
  lastPos.x = 0;
  lastPos.y = 0;

  // Default to RGB
  SetRGBA();

  imageData	=	new unsigned int[width*height];

  int nchannels = min(numSamples, MAX_CHANNELS);

  // Allocate storage for channel data.
  for (int i = 0; i < nchannels; ++i) {
    m_channelData[i] = new float[width*height];
    memset(m_channelData[i], 0, width*height*sizeof(float));
    m_channelsPresent[i] = true;
  }

  if (m_channelsPresent[CHAN_ALPHA]) {
    // Create a checkerboard pattern
    GenCheckerboard(imageData, width, height);
  } else {
    // Fill with black.
    memset(imageData, 0, width*height * sizeof(*imageData));
  }

	active		=	TRUE;
	willRedraw	=	FALSE;

	// Create the thread
	thread		=	CreateThread(NULL,0,displayThread,this,0,&threadID);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CWinDisplay
// Method				:	~CWinDisplay
// Description			:
/// \brief					Dtor
// Return Value			:	-
// Comments				:
CWinDisplay::~CWinDisplay() {
	delete [] imageData;
  for (int i = 0; i < MAX_CHANNELS; ++i) {
    if (m_channelsPresent[i]) {
      delete [] m_channelData[i];
    }
  }
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
void MakeWindowTitle(TCHAR *buf, size_t cch, TCHAR *file_name, float mag_fac,
                     DWORD channels, bool alphaOnly) {
  TCHAR *szBasename = basename(file_name);
  _sntprintf(buf, cch-1, "%s [%d%%] [%c%c%c%c] - Pixie", szBasename,
    (int)(round(mag_fac * 100)),
    TEST_CHANNEL(channels, CHAN_RED) && !alphaOnly ? 'R' : '-',
    TEST_CHANNEL(channels, CHAN_GREEN) && !alphaOnly ? 'G' : '-',
    TEST_CHANNEL(channels, CHAN_BLUE) && !alphaOnly ? 'B' : '-',
    TEST_CHANNEL(channels, CHAN_ALPHA) || alphaOnly ? 'A' : '-'
    );
  buf[cch-1] = 0;  // Null-terminate it.
}

void CWinDisplay::UpdateWinTitle() {
  DWORD channels = m_channels;
  if (m_channelsPresent[CHAN_ALPHA]) {
    SET_CHANNEL(channels, CHAN_ALPHA);
  }
  MakeWindowTitle(wndTitle, ARRAY_COUNT(wndTitle), name, mag_fac, channels,
    m_alpha);
  SetWindowText(hWnd, wndTitle);
}

// Generates a checkerboard pattern.
void GenCheckerboard(unsigned int *buf, int w, int h) {
  for (int i=0; i<h; i++) {
    for (int j=0; j<w; j++) {
      unsigned char d = 255;
      int t = 0;

      if ((i & 63) < 32) t ^= 1;
      if ((j & 63) < 32) t ^= 1;

      if (t)   d = 128;

      buf[i*w+j] = color(d,d,d,d);
    }
  }
}

// The alpha channel is special and requires different processing.
void CWinDisplay::QuantizeAlpha() {
  assert(m_alpha);
  if (!m_channelsPresent[CHAN_ALPHA]) {
    // Fill with black
    memset(imageData, 0, width*height*sizeof(*imageData));
  } else {
    for (int i = 0; i < height; ++i) {
      for (int j = 0; j < width; ++j) {
        int idx = j + i*width;
        imageData[idx] = ComputeDisplayPixel(0, j, i);
      }
    }
  }
}

void CWinDisplay::ShowAlpha() {
  m_alpha = true;
  QuantizeAlpha();
  UpdateWinTitle();
  InvalidateRect(hWnd, NULL, FALSE);
}

DWORD CWinDisplay::ComputeDisplayPixel(DWORD channels, int x, int y) {
  int idx = x + y*width;

  if (m_alpha || (!channels && m_channelsPresent[CHAN_ALPHA])) {
    BYTE alpha = m_channelsPresent[CHAN_ALPHA] ?
      m_channelData[CHAN_ALPHA][idx] * 255 : 0;
    return color(alpha, alpha, alpha, 0);
  } else {
    float alpha = m_channelsPresent[CHAN_ALPHA] ?
      m_channelData[CHAN_ALPHA][idx] : 1;

    BYTE rgb[3] = {0};

    // Blend the sample with the background to achieve transparency
    // (for display).
    for (int ch = 0; ch < 3; ++ch) {
      if (TEST_CHANNEL(channels, ch) && m_channelsPresent[ch]) {
        rgb[ch] = alpha * m_channelData[ch][idx] * 255 + (1-alpha) *
          EXTRACT_CHANNEL(imageData[idx], ch);
      }
    }

    return color(rgb[0], rgb[1], rgb[2], 0);
  }
}

// Quantize several color channels for display and cache the results.
// channels - bitfield of channels to display
void CWinDisplay::QuantizeChannels(DWORD channels) {
  // Make the background (in case it's transparent).
  GenCheckerboard(imageData, width, height);

  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      int idx = j + i*width;
      imageData[idx] = ComputeDisplayPixel(channels, j, i);
    }
  }
}

///////////////////////////////////////////////////////////////////////
// Class				:	CWinDisplay
// Method				:	main
// Description			:
/// \brief					The main display loop
// Return Value			:	-
// Comments				:
void	CWinDisplay::main() {
	WNDCLASSEX	wcex;
	MSG			msg;
  const char *szPixieWndClass = "PixieWinDisplay";

  curPan = LoadCursor(hInst, MAKEINTRESOURCE(IDC_PAN));

	wcex.cbSize						= sizeof(WNDCLASSEX);

	wcex.style						= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc				= (WNDPROC)	WndProc;
	wcex.cbClsExtra					= 0;
	wcex.cbWndExtra					= 0;
	wcex.hInstance					= hInst;
	wcex.hIcon						= LoadIcon(NULL,IDI_APPLICATION);
	wcex.hCursor					= LoadCursor(NULL, IDC_ARROW);
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
  MakeWindowTitle(wndTitle, ARRAY_COUNT(wndTitle), name, mag_fac, m_channels,
    m_alpha);

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
  InvalidateRect(hWnd, NULL, FALSE);

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
  SetCursor(curPan);
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

  InvalidateRect(hWnd, NULL, FALSE);
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
// Description			:
/// \brief					Redraw the image
// Return Value			:	-
// Comments				:
void	CWinDisplay::redraw() {
  float dstx = zoomOrigin.x;
  float dsty = zoomOrigin.y;

  float dstw = width*mag_fac;
  float dsth = height*mag_fac;

  // Entire surface.
  RECT rcEntire;
  GetClientRect(hWnd, &rcEntire);

  Graphics graphics(hWnd);
  graphics.SetInterpolationMode(InterpolationModeNearestNeighbor);
  graphics.SetPixelOffsetMode(PixelOffsetModeHalf);
  Bitmap bm(&info, imageData);

  RectF dest(dstx, dsty, dstw, dsth);
  graphics.ExcludeClip(dest);
  SolidBrush bgBrush(Color(127, 127, 127));
  graphics.FillRectangle(&bgBrush,
    rcEntire.left, rcEntire.top,
    rcEntire.right-rcEntire.left,
    rcEntire.bottom-rcEntire.top);
  graphics.ResetClip();

  graphics.DrawImage(&bm, dest);
  willRedraw = FALSE;
}

void CWinDisplay::ToggleChannel(int channel) {
  TOGGLE_CHANNEL(m_channels, channel);
  QuantizeChannels(m_channels);
  UpdateWinTitle();
  InvalidateRect(hWnd, NULL, FALSE);
}

void CWinDisplay::ShowChannel(int channel) {
  m_alpha = false;
  m_channels = 0;
  SET_CHANNEL(m_channels, channel);
  UpdateWinTitle();
  QuantizeChannels(m_channels);
  InvalidateRect(hWnd, NULL, FALSE);
}

void CWinDisplay::SetRGBA() {
  m_channels = 0;
  SET_CHANNEL(m_channels, CHAN_RED);
  SET_CHANNEL(m_channels, CHAN_GREEN);
  SET_CHANNEL(m_channels, CHAN_BLUE);
}

void CWinDisplay::ShowRGBA() {
  m_alpha = false;
  SetRGBA();
  UpdateWinTitle();
  QuantizeChannels(m_channels);
  InvalidateRect(hWnd, NULL, FALSE);
}

// Use during keyboard message only!
BOOL IsKeyDown(int nVirtKey) {
  // Return the high bit.
  return GetKeyState(nVirtKey) & 0x8000;
}

void CWinDisplay::OnKeyDown(int vk) {
  switch(vk) {
    case VK_NUMPAD0:
      ActualPixels();  // Zoom to 100%.
      break;
    case 'C':  // Show RGBA color
      ShowRGBA();
      break;
    case 'R':
      if (IsKeyDown(VK_CONTROL)) {
        ToggleChannel(CHAN_RED);
      } else {
        ShowChannel(CHAN_RED);
      }
      break;
    case 'G':
      if (IsKeyDown(VK_CONTROL)) {
        ToggleChannel(CHAN_GREEN);
      } else {
        ShowChannel(CHAN_GREEN);
      }
      break;
    case 'B':
      if (IsKeyDown(VK_CONTROL)) {
        ToggleChannel(CHAN_BLUE);
      } else {
        ShowChannel(CHAN_BLUE);
      }
      break;
    case 'A':
      ShowAlpha();
      break;
    case VK_HOME:
      CenterImage();
      break;
  }
}

BOOL CWinDisplay::OnSetCursor() {
  if (mouseDown) {
    SetCursor(curPan);
    return TRUE;
  } else {
    return FALSE;
  }
}


///////////////////////////////////////////////////////////////////////
// Class        : CWinDisplay
// Method				: data
// Description			:
/// \brief					Draw the data onto the screen
// Return Value :
// Comments     : Must be thread safe! Called from multiple threads
// concurrently.
int	CWinDisplay::data(int x,int y,int w,int h,float *d) {
	int	i,j;

	clampData(w,h,d);

	for (i=0;i<h;i++) {
		const float		*src	=	&d[i*w*numSamples];
		unsigned int	*dest	=	&imageData[((height-(i+y)-1)*width+x)];
    int offset = (height-1-(i+y))*width + x;

		switch(numSamples) {
		case 0:
			break;
		case 1:
			for (j=0;j<w;j++) {
        for (int c = 0; c < numSamples; ++c) {
          m_channelData[c][offset + j] = src[c];
        }

				*dest++				=	ComputeDisplayPixel(m_channels, x+j, height-1-(y+i));
				src++;
			}
			break;
		case 2:
			for (j=0;j<w;j++) {
        for (int c = 0; c < numSamples; ++c) {
          m_channelData[c][offset + j] = src[c];
        }
				*dest++				=	ComputeDisplayPixel(m_channels, x+j, height-1-(y+i));
				src					+=	2;
			}
			break;
		case 3:
			for (j=0;j<w;j++) {
        for (int c = 0; c < numSamples; ++c) {
          m_channelData[c][offset + j] = src[c];
        }
				*dest++				=	ComputeDisplayPixel(m_channels, x+j, height-1-(y+i));
				src					+=	3;
			}
			break;
		case 4:
			for (j=0;j<w;j++) {
        for (int c = 0; c < numSamples; ++c) {
          m_channelData[c][offset + j] = src[c];
        }
				*dest++				=	ComputeDisplayPixel(m_channels, x+j, height-1-(y+i));
				src					+=	4;
			}
			break;
		default:
			for (j=0;j<w;j++) {
        // We only support storing up to 4 channels for now (RGBA)
        for (int c = 0; c < 4; ++c) {
          m_channelData[c][offset + j] = src[c];
        }
				*dest++				=	ComputeDisplayPixel(m_channels, x+j, height-1-(y+i));
				src					+=	numSamples;
			}
			break;
		}
	}

	if (active) {
    float dstx = zoomOrigin.x + x;
    float dsty = zoomOrigin.y + y;
    RECT rc = { dstx, dsty, dstx + w*mag_fac , dsty + h*mag_fac };
    InvalidateRect(hWnd, &rc, FALSE);
	}

	return active;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CWinDisplay
// Method				:	finish
// Description			:
/// \brief					Finish displaying the data
// Return Value			:	-
// Comments				:
void	CWinDisplay::finish() {
	// Wait for the user to close the window
	WaitForSingleObject(thread,INFINITE);
}

///////////////////////////////////////////////////////////////////////
// Method				:	WndProc
// Description			:
/// \brief					Windows callback function
// Return Value			:	-
// Comments				:
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
  CWinDisplay *dpy = (CWinDisplay *)GetWindowLongPtr(hWnd, GWLP_USERDATA);

  switch (message) {
    case WM_PAINT: {
      dpy->redraw();
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
    case WM_SETCURSOR:
      if (dpy->OnSetCursor()) {
        break;
      }
  }

  return DefWindowProc(hWnd, message, wParam, lParam);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
  switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
      hInst = hinstDLL;  // Save our module handle.
      break;
  }
  return TRUE;
}
