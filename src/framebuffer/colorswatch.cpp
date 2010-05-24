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
//  File				:	colorswatch.cpp
//  Classes				:
//  Description			:
/// \brief					Implements a color swatch control.
//
////////////////////////////////////////////////////////////////////////

#include "colorswatch.h"

#include <windowsx.h>
#include <tchar.h>

extern HINSTANCE hInst;  // Our DLL's instance.

static const TCHAR g_ColorSwatchCls[] = _T("ColorSwatchCls");

static LRESULT CALLBACK ColorSwatchWndProc(HWND hwnd, UINT uMsg,
                                           WPARAM wParam, LPARAM lParam);

BOOL InitColorSwatch() {
  WNDCLASS wc = {0};
  wc.hInstance = hInst;
  wc.lpszClassName = g_ColorSwatchCls;
  wc.lpfnWndProc = (WNDPROC)ColorSwatchWndProc;

  if (RegisterClass(&wc)) {
    return TRUE;
  }
  return FALSE;
}

void UninitColorSwatch() {
  UnregisterClass(g_ColorSwatchCls, hInst);
}

void OnPaint(HWND hwnd) {
  PAINTSTRUCT ps;
  BeginPaint(hwnd, &ps);
  RECT rc;
  GetClientRect(hwnd, &rc);
  COLORREF bg = (COLORREF)GetWindowLongPtr(hwnd, GWLP_USERDATA);
  SetDCBrushColor(ps.hdc, bg);
  FillRect(ps.hdc, &rc, GetStockBrush(DC_BRUSH));
  EndPaint(hwnd, &ps);
}

LRESULT CALLBACK ColorSwatchWndProc(HWND hwnd, UINT uMsg,
                                    WPARAM wParam, LPARAM lParam)
{
  switch(uMsg) {
    case WM_PAINT:
      OnPaint(hwnd);
      return 0;
    case CSM_SETBKCOLOR:
      // Store our background color.
      SetWindowLongPtr(hwnd, GWLP_USERDATA, wParam);
      return 0;
  }
  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
