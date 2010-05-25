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
//  File				:	fbw.h
//  Classes				:	CWinDisplay
//  Description			:
/// \brief					Windows image displaying class
//
////////////////////////////////////////////////////////////////////////
#ifndef FBW_H
#define FBW_H

#include <windows.h>
#include <gdiplus.h>

#include "framebuffer.h"

enum CHANNEL {
  CHAN_RED,
  CHAN_GREEN,
  CHAN_BLUE,
  CHAN_ALPHA,
  MAX_CHANNELS
};

///////////////////////////////////////////////////////////////////////
// Class				:	CWinDisplay
// Description			:
/// \brief					The windows display class
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

  void      OnPaint(HDC hdc);
  BOOL      OnCreate(HWND hwnd);
  void      OnDestroy();
  void      OnLButtonDown(int x, int y);
  void      OnRButtonDown(int x, int y);
  void      OnLButtonUp(int x, int y);
  void      OnRButtonUp(int x, int y);
  void      OnMouseMove(int x, int y);
  void      OnMouseWheel(int x, int y, int zDelta);
  void      OnKeyDown(int vk);
  void      OnSize(int cx, int cy);
  BOOL      OnSetCursor();
private:
	HWND			hWnd;								// current window
	BITMAPINFO		info;								// bitmap info

	unsigned int	*imageData;  // Cached, quantized color channel for display.

  float *m_channelData[MAX_CHANNELS];  // Original float channel data

  // Tells us whether a channel is present.
  bool m_channelsPresent[MAX_CHANNELS];

	int				active;

  void QuantizeChannels(DWORD channels);
  void QuantizeAlpha();
  DWORD ComputeDisplayPixel(DWORD channels, int x, int y);

  void UpdateWinTitle();

  /// Zoom to a fixed factor.
  void ZoomImage(float new_mag, const Gdiplus::PointF &p);
  /// Zoom by some offset.
  void ZoomDelta(float dmag, const Gdiplus::PointF &p);

  void ToggleChannel(int channel);
  void ShowAlpha();
  void ShowChannel(int channel);
  void ShowRGBA();
  void SetRGBA();

  /// Sample a value from a channel.
  float SampleChannel(DWORD channel, int x, int y);
  void ComputeSamplePoint(POINT *sp, int x, int y);
  /// Sample a complete color.
  void GetColorSample(int x, int y, float rgba[4]);
  void UpdateColorInfo(int x, int y);

  // Helper functions for common cases.
  void ZoomIn(const Gdiplus::PointF &p);
  void ZoomOut(const Gdiplus::PointF &p);
  void ActualPixels();  // Zoom to 100%.
  void CenterImage();
  void CenterOfViewport(Gdiplus::PointF *p);

  ULONG_PTR gdiplusToken;
  Gdiplus::GdiplusStartupInput gdiplusStartupInput;
  TCHAR wndTitle[200];

  DWORD m_channels;
  bool m_alpha;   // Show alpha only (takes precedence over color).

  Gdiplus::PointF m_panOffset;
  Gdiplus::PointF lastPos;
  float mag_fac;
  bool m_lMouseDown;
  bool m_rMouseDown;
  Gdiplus::RectF m_dest;

  HWND hColorInfo;  // Color info dialog.
  HCURSOR curPan;  // Pan cursor.
  HCURSOR curEyedropper;  // Color picker cursor.
};



#endif

