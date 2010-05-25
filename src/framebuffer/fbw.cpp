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
#include "colorswatch.h"

#include "resource.h"

#include <windowsx.h>
#include <math.h>
#include <tchar.h>
#include <stdarg.h>

using namespace Gdiplus;

HINSTANCE hInst;  // Our DLL's instance.

// Foward declarations of functions included in this code module:
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
// Dialog proc for color info window.
INT_PTR CALLBACK ColorInfoProc(HWND hWnd, UINT uMsg,
                               WPARAM wParam, LPARAM lParam);
void GenCheckerboard(unsigned int *buf, int w, int h);
void ScaleRectAboutPoint(RectF *rc, const PointF &p, float scale);
void safe_stprintf(TCHAR *buf, size_t cch, const TCHAR *format, ...);

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

// Amount we pan by for keyboard controls.
static const float PAN_INCREMENT = 10.f;

// Valid for positive numbers.
inline int round(double x) {
  return (int)(x + .5);
}

// Clamp a value to a range.
template<class T>
inline T clamp(T x, T low, T high) {
  if (x < low) {
    x = low;
  } else if (x > high) {
    x = high;
  }
  return x;
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
m_lMouseDown(false), m_rMouseDown(false), mag_fac(1), hWnd(NULL),
m_channels(0), m_alpha(false), m_dest(0, 0, width, height), hColorInfo(NULL) {
	DWORD	threadID;

  memset(m_channelsPresent, 0, sizeof(m_channelsPresent));

  // Initialize GDI+.
  GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

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

// Safe, truncating version of stprintf
void safe_stprintf(TCHAR *buf, size_t cch, const TCHAR *format, ...) {
  va_list args;
  va_start(args, format);
  _vsntprintf(buf, cch-1, format, args);
  va_end(args);
  buf[cch-1] = 0;  // Guarantee NULL-termination.
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

void ScaleRectAboutPoint(RectF *rc, const PointF &p, float scale) {
  assert(rc);
  // Translate rc by -p.
  rc->Offset(-p.X, -p.Y);

  // Scale the components.
  rc->X *= scale;
  rc->Y *= scale;
  rc->Width *= scale;
  rc->Height *= scale;

  // Translate it back.
  rc->Offset(p);
}

BOOL CWinDisplay::OnCreate(HWND hwnd) {
  if (!InitColorSwatch()) {
    return FALSE;
  }
  hColorInfo = CreateDialog(hInst, MAKEINTRESOURCE(IDD_COLORINFO),
    hwnd, ColorInfoProc);
  if (!hColorInfo) {
    return FALSE;
  }
  return TRUE;
}

void CWinDisplay::OnDestroy() {
  DestroyWindow(hColorInfo);
  UninitColorSwatch();
  PostQuitMessage(0);
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
  curEyedropper = LoadCursor(hInst, MAKEINTRESOURCE(IDC_EYEDROPPER));

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
    rc.bottom - rc.top, NULL, NULL, hInst, (LPVOID)this);

	if (!hWnd)	{
		active	=	FALSE;
		return;	// Nothing to do
	}

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

void CWinDisplay::OnLButtonDown(int x, int y) {
  m_lMouseDown = true;
  lastPos.X = (float)x;
  lastPos.Y = (float)y;

  InvalidateRect(hWnd, NULL, TRUE);
  SetCapture(hWnd);
  SetCursor(curPan);
}

float CWinDisplay::SampleChannel(DWORD channel, int x, int y) {
  assert(channel < MAX_CHANNELS);
  assert(m_channelsPresent[channel]);
  assert(x >= 0 && x < width);
  assert(y >= 0 && y < height);
  return m_channelData[channel][x + y * width];
}

// Given mouse client coords (x,y), compute where we should sample from in the
// image, taking into account zoom/pan state.
void CWinDisplay::ComputeSamplePoint(POINT *sp, int x, int y) {
  float vx = clamp<float>((x - m_dest.X - m_panOffset.X)/mag_fac, 0, width-1);
  float vy = clamp<float>((y - m_dest.Y - m_panOffset.Y)/mag_fac, 0, height-1);
  sp->x = round(vx);
  sp->y = height-1-round(vy);  // We're upside down.
}

void CWinDisplay::GetColorSample(int x, int y, float rgba[4]) {
  POINT sp;
  ComputeSamplePoint(&sp, x, y);
  for (int i = 0; i < MAX_CHANNELS; ++i) {
    rgba[i] = 0;
    if (m_channelsPresent[i]) {
      rgba[i] = SampleChannel(i, sp.x, sp.y);
    }
  }
}

COLORREF ClampPixel(float rgba[]) {
  BYTE clamped[3] = {0};
  for (int i = 0; i < 3; ++i) {
    clamped[i] = (BYTE)(clamp(rgba[i], 0.f, 1.f) * 255);
  }
  return RGB(clamped[0], clamped[1], clamped[2]);
}

void CWinDisplay::UpdateColorInfo(int x, int y) {
  int sx = clamp(x, 0, width-1);
  int sy = clamp(y, 0, height-1);

  float rgba[4] = {0};
  GetColorSample(sx, sy, rgba);

  // Update swatch's color.
  SendMessage(GetDlgItem(hColorInfo, IDC_COLOR_SWATCH),
    CSM_SETBKCOLOR, ClampPixel(rgba), 0);

  InvalidateRect(GetDlgItem(hColorInfo, IDC_COLOR_SWATCH), NULL, FALSE);

  TCHAR buf[100] = {0};

  // Set up RGBA static controls.
  safe_stprintf(buf, ARRAY_COUNT(buf), _T("%f"), rgba[0]);
  SetDlgItemText(hColorInfo, IDC_CHAN_R, buf);
  safe_stprintf(buf, ARRAY_COUNT(buf), _T("%f"), rgba[1]);
  SetDlgItemText(hColorInfo, IDC_CHAN_G, buf);
  safe_stprintf(buf, ARRAY_COUNT(buf), _T("%f"), rgba[2]);
  SetDlgItemText(hColorInfo, IDC_CHAN_B, buf);
  safe_stprintf(buf, ARRAY_COUNT(buf), _T("%f"), rgba[3]);
  SetDlgItemText(hColorInfo, IDC_CHAN_A, buf);

  RECT rc;
  GetClientRect(hWnd, &rc);
  POINT pt = {x + 25, y};
  pt.x = clamp<int>(pt.x, 0, rc.right-rc.left);
  pt.y = clamp<int>(pt.y, 0, rc.bottom-rc.top);
  ClientToScreen(hWnd, &pt);
  SetWindowPos(hColorInfo, NULL, pt.x, pt.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void CWinDisplay::OnRButtonDown(int x, int y) {
  m_rMouseDown = true;
  UpdateColorInfo(x, y);
  ShowWindow(hColorInfo, SW_SHOW);
  SetCursor(curEyedropper);
  SetCapture(hWnd);
}

void CWinDisplay::OnSize(int cx, int cy) {
  UNREFERENCED_PARAMETER(cx);
  UNREFERENCED_PARAMETER(cy);
  CenterImage();
}

void OnGetMinMaxInfo(MINMAXINFO *mmi) {
  // Restrict the minimum size of the window.
  mmi->ptMinTrackSize.x = 250;
  mmi->ptMinTrackSize.y = 150;
}

void CWinDisplay::OnLButtonUp(int x, int y) {
  m_lMouseDown = false;
  lastPos.X = (float)x;
  lastPos.Y = (float)y;
  ReleaseCapture();
}

void CWinDisplay::OnRButtonUp(int x, int y) {
  m_rMouseDown = false;
  ShowWindow(hColorInfo, SW_HIDE);
  ReleaseCapture();
}

void CWinDisplay::OnMouseMove(int x, int y) {
  if (m_lMouseDown) {
    float dx = (x - lastPos.X);
    float dy = (y - lastPos.Y);

    m_panOffset.X += dx;
    m_panOffset.Y += dy;

    InvalidateRect(hWnd, NULL, TRUE);

    lastPos.X = (float)x;
    lastPos.Y = (float)y;
  } else if (m_rMouseDown) {
    UpdateColorInfo(x, y);
  }
}

void CWinDisplay::CenterOfViewport(PointF *p) {
  RECT rc;
  GetClientRect(hWnd, &rc);
  p->X = (rc.right - rc.left)/2 - m_panOffset.X;
  p->Y = (rc.bottom - rc.top)/2 - m_panOffset.Y;
}

// (x, y) - point in client coordinates.
void CWinDisplay::OnMouseWheel(int x, int y, int zDelta) {
  PointF p(x - m_panOffset.X, y - m_panOffset.Y);
  if (zDelta > 0) {
    ZoomIn(p);
  } else {
    ZoomOut(p);
  }
}

void CWinDisplay::ZoomDelta(float dmag, const PointF &p) {
  ZoomImage(mag_fac + dmag, p);
}

void CWinDisplay::ZoomIn(const PointF &p) {
  ZoomDelta(ZOOM_INCREMENT*mag_fac, p);
}

void CWinDisplay::ZoomOut(const PointF &p) {
  ZoomDelta(-ZOOM_INCREMENT*mag_fac, p);
}

void CWinDisplay::CenterImage() {
  RECT rc;
  GetClientRect(hWnd, &rc);

  m_panOffset.X = ((rc.right - rc.left) - width*mag_fac)/2 - m_dest.X;
  m_panOffset.Y = ((rc.bottom - rc.top) - height*mag_fac)/2 - m_dest.Y;

  InvalidateRect(hWnd, NULL, FALSE);
}

void CWinDisplay::ActualPixels() {
  ZoomImage(1, PointF(0,0));
  CenterImage();
}

void CWinDisplay::ZoomImage(float new_mag, const PointF &p) {
  const float MINZOOM = .2f;
  const float MAXZOOM = 10.f;

  // Clamp zoom.
  new_mag = clamp(new_mag, MINZOOM, MAXZOOM);

  RectF rc(m_dest);
  ScaleRectAboutPoint(&rc, p, 1.0f/mag_fac);
  ScaleRectAboutPoint(&rc, p, new_mag);
  m_dest = rc;

  mag_fac = new_mag;

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
  // Entire surface.
  RECT rcEntire;
  GetClientRect(hWnd, &rcEntire);

  RectF rc(m_dest);
  rc.Offset(m_panOffset);

  Graphics graphics(hWnd);

  // Set device parameters.
  graphics.SetInterpolationMode(InterpolationModeNearestNeighbor);
  graphics.SetPixelOffsetMode(PixelOffsetModeHalf);

  Bitmap bm(&info, imageData);

  // Fill in viewport background.
  graphics.ExcludeClip(rc);
  SolidBrush bgBrush(Color(127, 127, 127));
  graphics.FillRectangle(&bgBrush,
    rcEntire.left, rcEntire.top,
    rcEntire.right-rcEntire.left,
    rcEntire.bottom-rcEntire.top);
  graphics.ResetClip();

  // Draw bitmap contents.
  graphics.DrawImage(&bm, rc);
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

    // Keyboard panning controls.
    case VK_LEFT:
      m_panOffset.X += PAN_INCREMENT;
      InvalidateRect(hWnd, NULL, FALSE);
      break;
    case VK_RIGHT:
      m_panOffset.X -= PAN_INCREMENT;
      InvalidateRect(hWnd, NULL, FALSE);
      break;
    case VK_UP:
      m_panOffset.Y += PAN_INCREMENT;
      InvalidateRect(hWnd, NULL, FALSE);
      break;
    case VK_DOWN:
      m_panOffset.Y -= PAN_INCREMENT;
      InvalidateRect(hWnd, NULL, FALSE);
      break;

    // Numpad +
    case VK_ADD: {
      PointF p;
      CenterOfViewport(&p);
      // Zoom about the center of viewport.
      ZoomIn(p);
      break;
    }
    // Numpad -
    case VK_SUBTRACT: {
      PointF p;
      CenterOfViewport(&p);
      // Zoom about the center of viewport.
      ZoomOut(p);
      break;
    }
  }
}

BOOL CWinDisplay::OnSetCursor() {
  if (m_lMouseDown) {
    SetCursor(curPan);
    return TRUE;
  } else if (m_rMouseDown) {
    SetCursor(curEyedropper);
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
      float dstx = m_panOffset.X + x;
      float dsty = m_panOffset.Y + y;
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
    case WM_CREATE: {
      CREATESTRUCT *cs = (CREATESTRUCT*)lParam;
      // Associate a pointer to our instance with this window.
      SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)cs->lpCreateParams);
      dpy = (CWinDisplay *)cs->lpCreateParams;
      if (dpy->OnCreate(hWnd)) {
        return 0;
      } else {
        return -1;  // Failed to create window.
      }
    }
    case WM_PAINT: {
      dpy->redraw();
      return 0;
    }
    case WM_LBUTTONDOWN:
      dpy->OnLButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
      break;
    case WM_RBUTTONDOWN:
      dpy->OnRButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
      break;
    case WM_LBUTTONUP:
      dpy->OnLButtonUp(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
      break;
    case WM_RBUTTONUP:
      dpy->OnRButtonUp(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
      break;
    case WM_MOUSEMOVE:
      dpy->OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
      break;
    case WM_MOUSEWHEEL: {
      // NOTE: MOUSEWHEEL gets (x,y) in screen coords! Not client coords!
      POINT p = {GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
      ScreenToClient(hWnd, &p);  // Convert them to client coords.
      dpy->OnMouseWheel(p.x, p.y, GET_WHEEL_DELTA_WPARAM(wParam));
      break;
    }
    case WM_KEYDOWN:
      dpy->OnKeyDown((int)wParam);
      break;
    case WM_SIZE:
      dpy->OnSize(LOWORD(lParam), HIWORD(lParam));
      break;
    case WM_GETMINMAXINFO:
      // NOTE: Can't be a member function, since it arrives before WM_CREATE
      // when we establish the 'this' pointer.
      OnGetMinMaxInfo((MINMAXINFO*)lParam);
      break;
    case WM_CLOSE:
      DestroyWindow(hWnd);
      break;
    case WM_DESTROY:
      dpy->OnDestroy();
      break;
    case WM_SETCURSOR:
      if (dpy->OnSetCursor()) {
        break;
      }
  }

  return DefWindowProc(hWnd, message, wParam, lParam);
}

INT_PTR CALLBACK ColorInfoProc(HWND hWnd, UINT uMsg,
                               WPARAM wParam, LPARAM lParam)
{
  return FALSE;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
  switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
      hInst = hinstDLL;  // Save our module handle.
      break;
  }
  return TRUE;
}
