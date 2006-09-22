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
//  File				:	winOpenGL.cpp
//  Classes				:
//  Description			:	Windows opengl driver
//
////////////////////////////////////////////////////////////////////////
#include "winOpenGL.h"

#include <stdio.h>
#include <stdarg.h>


static	int			width,height;
static	HDC			hDC;
static	HGLRC		hGLRC;
static	HWND		hWnd;
static	MSG			msg;
static	int			fontListBase;

///////////////////////////////////////////////////////////////////////
// Function				:	print
// Description			:	Print a text
// Return Value			:	-
// Comments				:
// Date last edited		:	12/27/2002
static	void	print(float x,float y,char *mes,...) {
	char	tmp[256];
	va_list	args;

	va_start(args,mes);
	vsprintf(tmp,mes,args);
	va_end(args);

	GLsizei len = GLsizei(strlen(tmp));
	if (len > 0) {
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		glColor3f(1,1,1);
		glRasterPos3f(x,height - y,-1);
		// Must save/restore the list base.
		glPushAttrib(GL_LIST_BIT);{
			glListBase(fontListBase);
			glCallLists(len, GL_UNSIGNED_BYTE, (const GLvoid*) tmp);
		} glPopAttrib();
		glPopMatrix();
	}
}


///////////////////////////////////////////////////////////////////////
// Function				:	choosePixelFormatEx
// Description			:	Find a good pixel format
// Return Value			:	The index of the best pixel format
// Comments				:
// Date last edited		:	12/27/2002
static	int		choosePixelFormatEx(int *p_bpp,int *p_depth,int *p_dbl,int *p_acc)	{ 
	int wbpp;	if (p_bpp==NULL)	wbpp=-1;	else wbpp	=	*p_bpp;
	int wdepth; if (p_depth==NULL)	wdepth=16;	else wdepth	=	*p_depth;
	int wdbl;	if (p_dbl==NULL)	wdbl=-1;	else wdbl	=	*p_dbl;
	int wacc;	if (p_acc==NULL)	wacc=1;		else wacc	=	*p_acc;

	PIXELFORMATDESCRIPTOR pfd; ZeroMemory(&pfd,sizeof(pfd)); pfd.nSize=sizeof(pfd); pfd.nVersion=1;

	int num	=	DescribePixelFormat(hDC,1,sizeof(pfd),&pfd);

	if (num==0) return 0;
	unsigned int maxqual=0; int maxindex=0;
	int max_bpp=0, max_depth=0, max_dbl=0, max_acc=0;
	for (int i=1; i<=num; i++)	{ 
		ZeroMemory(&pfd,sizeof(pfd)); pfd.nSize=sizeof(pfd); pfd.nVersion=1;
		DescribePixelFormat(hDC,i,sizeof(pfd),&pfd);
		int				bpp			=	pfd.cColorBits;
		int				depth		=	pfd.cDepthBits;
		bool			pal			=	(pfd.iPixelType==PFD_TYPE_COLORINDEX);
		bool			mcd			=	((pfd.dwFlags & PFD_GENERIC_FORMAT) && (pfd.dwFlags & PFD_GENERIC_ACCELERATED));
		bool			soft		=	((pfd.dwFlags & PFD_GENERIC_FORMAT) && !(pfd.dwFlags & PFD_GENERIC_ACCELERATED));
		bool			icd			=	(!(pfd.dwFlags & PFD_GENERIC_FORMAT) && !(pfd.dwFlags & PFD_GENERIC_ACCELERATED));
		unsigned int	opengl		=	(unsigned int) (pfd.dwFlags & PFD_SUPPORT_OPENGL);
		unsigned int	window		=	(unsigned int) (pfd.dwFlags & PFD_DRAW_TO_WINDOW);
		unsigned int	bitmap		=	(unsigned int) (pfd.dwFlags & PFD_DRAW_TO_BITMAP);
		bool			dbuff		=	(pfd.dwFlags & PFD_DOUBLEBUFFER);

		unsigned int q=0;
		if (opengl && window) q=q+0x8000;
		if (wdepth==-1 || (wdepth>0 && depth>0)) q=q+0x4000;
		if (wdbl==-1 || (wdbl==0 && !dbuff) || (wdbl==1 && dbuff)) q=q+0x2000;
		if (wacc==-1 || (wacc==0 && soft) || (wacc==1 && (mcd || icd))) q=q+0x1000;
		if (mcd || icd) q=q+0x0040; if (icd) q=q+0x0002;
		if (wbpp==-1 || (wbpp==bpp)) q=q+0x0800;
		if (bpp>=16) q=q+0x0020; if (bpp==16) q=q+0x0008;
		if (wdepth==-1 || (wdepth==depth)) q=q+0x0400;
		if (depth>=16) q=q+0x0010; if (depth==16) q=q+0x0004;
		if (!pal) q=q+0x0080;
		if (bitmap) q=q+0x0001;
		if (q>maxqual) {maxqual=q; maxindex=i;max_bpp=bpp; max_depth=depth; max_dbl=dbuff?1:0; max_acc=soft?0:1;}
	}
	if (maxindex==0) return maxindex;
	if (p_bpp!=NULL)		*p_bpp		=	max_bpp;
	if (p_depth!=NULL)		*p_depth	=	max_depth;
	if (p_dbl!=NULL)		*p_dbl		=	max_dbl;
	if (p_acc!=NULL)		*p_acc		=	max_acc;
	return maxindex;
}

///////////////////////////////////////////////////////////////////////
// Function				:	initOpenGL
// Description			:	Initialize opengl
// Return Value			:	TRUE on success
// Comments				:
// Date last edited		:	12/27/2002
static	void	initOpenGL() {
	int						bpp		=	32;
	int						depth	=	24;
	//int						dbl		=	TRUE;
	int						dbl		=	FALSE;
	int						acc		=	-1;
	int						pf		=	choosePixelFormatEx(&bpp,&depth,&dbl,&acc);
	PIXELFORMATDESCRIPTOR	pfd; ZeroMemory(&pfd,sizeof(pfd)); pfd.nSize=sizeof(pfd); pfd.nVersion=1;

	if (SetPixelFormat(hDC,pf,&pfd) == FALSE) 
		hGLRC	=	NULL;
	else
		hGLRC	=	wglCreateContext(hDC);	
}


///////////////////////////////////////////////////////////////////////
// Function				:	WndProc
// Description			:	Event proc.
// Return Value			:	-
// Comments				:
// Date last edited		:	12/27/2002
LRESULT APIENTRY	WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)	{
    switch (message) {
    case WM_CREATE:
        return 0;
    case WM_DESTROY:
        if (hGLRC) {
            wglMakeCurrent(NULL, NULL);
            wglDeleteContext(hGLRC);
        }
        ReleaseDC(hWnd, hDC);
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            BeginPaint(hWnd, &ps);
            if (hGLRC) {
				SwapBuffers(hDC);
				SwapBuffers(hDC);
            }
            EndPaint(hWnd, &ps);
            return 0;
        }
        break;
    default:
        break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}



///////////////////////////////////////////////////////////////////////
// Function				:	pglInit
// Description			:	Initialise openGL
// Return Value			:
// Comments				:
// Date last edited		:	11/28/2001
int	pglInit(int w,int h) {
	WNDCLASS	wndClass;
	HINSTANCE	hInstance	=	(HINSTANCE)GetModuleHandle(NULL);
	char		*fontname	=	"Font:Arial";
	HFONT		font;
	char		*tmp;

	width					=	max(w,320);
	height					=	max(h,200);

    // Create the window
    wndClass.style			= CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc	= WndProc;
    wndClass.cbClsExtra		= 0;
    wndClass.cbWndExtra		= 0;
    wndClass.hInstance		= hInstance;
    wndClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
    wndClass.lpszMenuName	= NULL;
    wndClass.lpszClassName	= "HardwareFB";
    RegisterClass(&wndClass);

    hWnd = CreateWindow("HardwareFB", "Rendering, please do not close",
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
        0, 0, width, height,
        NULL, NULL, hInstance, NULL);

	// Map the window
    ShowWindow(hWnd,SW_SHOW);
    UpdateWindow(hWnd);

	{
		RECT	clientRect,windowRect;
		int		nw,nh;

		GetWindowRect(hWnd,&windowRect);
		GetClientRect(hWnd,&clientRect);

		nw	=	width	+	(windowRect.right - windowRect.left) - (clientRect.right - clientRect.left);
		nh	=	height	+	(windowRect.bottom - windowRect.top) - (clientRect.bottom - clientRect.top);

		SetWindowPos(hWnd,HWND_TOPMOST,0,0,nw,nh,SWP_SHOWWINDOW);
	}

    hDC = GetDC(hWnd);
    initOpenGL();
    wglMakeCurrent(hDC, hGLRC);

	// Create the font
    fontListBase = glGenLists(256);

    LOGFONT logfont;
    logfont.lfHeight = -12;
    logfont.lfWidth = 0;
    logfont.lfEscapement = 0;
    logfont.lfOrientation = logfont.lfEscapement;
    logfont.lfWeight = FW_NORMAL;
    logfont.lfItalic = FALSE;
    logfont.lfUnderline = FALSE;
    logfont.lfStrikeOut = FALSE;
    logfont.lfCharSet = ANSI_CHARSET;
    logfont.lfOutPrecision = OUT_DEFAULT_PRECIS;
    logfont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
    logfont.lfQuality = DEFAULT_QUALITY;
    logfont.lfPitchAndFamily = FF_DONTCARE|DEFAULT_PITCH;
    lstrcpy(logfont.lfFaceName, fontname);

	font			= CreateFontIndirect(&logfont);
    SelectObject(hDC,&font);
    if (FALSE == wglUseFontBitmaps(hDC, 0, 256, fontListBase)) {
        glDeleteLists(fontListBase, 256);
        fontListBase = 0;
    }


	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,width,0,height,0,100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glViewport(0,0,width,height);

	tmp	=	(char *) glGetString(GL_VENDOR);
	print(20,30,"Vendor: %s",tmp);
	tmp	=	(char *) glGetString(GL_RENDERER);
	print(20,45,"Renderer: %s",tmp);
	tmp	=	(char *) glGetString(GL_VERSION );
	print(20,60,"Version: %s",tmp);

	print(20,80,"Pixie Rendering ... DO NOT CLOSE");

	SwapBuffers(hDC);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// Function				:	pglRun
// Description			:	Enter into the event loop
// Return Value			:
// Comments				:
// Date last edited		:	9/21/2006
void		pglRun() {
}

///////////////////////////////////////////////////////////////////////
// Function				:	displayRefresh
// Description			:	Refresh the display of the window
// Return Value			:
// Comments				:
// Date last edited		:	11/28/2001
void	displayRefresh() {
	PostMessage(hWnd,WM_PAINT,(WPARAM) 0,0);
}

///////////////////////////////////////////////////////////////////////
// Function				:	displayProcessEvents
// Description			:	Process the window events until none is left
// Return Value			:
// Comments				:
// Date last edited		:	11/28/2001
void	displayProcessEvents() {
	// Into the event loop
	while(PeekMessage(&msg,hWnd,0,0,PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

///////////////////////////////////////////////////////////////////////
// Function				:	pglFinish
// Description			:	Terminate the display
// Return Value			:
// Comments				:
// Date last edited		:	11/28/2001
void	pglFinish() {
	width			=	0;
	height			=	0;

	DestroyWindow(hWnd);
}






