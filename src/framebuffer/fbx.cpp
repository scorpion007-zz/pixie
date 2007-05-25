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
//  File				:	fbx.cpp
//  Classes				:	CXDisplay
//  Description			:	X Windows image displaying class
//
////////////////////////////////////////////////////////////////////////
#include "common/global.h"
#include "framebuffer.h"
#include "fbx.h"

#define	color_15_bgr(r,g,b,a)		((r >> 3) << 10) | ((g >> 3) << 5) | (b >> 3)
#define	color_15_bgr_rev(r,g,b,a)	((g >> 3) << 13) | ((b >> 3) << 8) | ((r >> 3) << 3) | (g >> 5)
#define	color_15_rgb(r,g,b,a)		((b >> 3) << 10) | ((g >> 3) << 5) | (r >> 3)
#define	color_15_rgb_rev(r,g,b,a)	((g >> 3) << 13) | ((r >> 3) << 8) | ((b >> 3) << 3) | (g >> 5)

#define	color_16_bgr(r,g,b,a)		((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3)
#define	color_16_bgr_rev(r,g,b,a)	((g >> 2) << 13) | ((b >> 3) << 8) | ((r >> 3) << 3) | (g >> 5)
#define	color_16_rgb(r,g,b,a)		((b >> 3) << 11) | ((g >> 2) << 5) | (r >> 3)
#define	color_16_rgb_rev(r,g,b,a)	((g >> 2) << 13) | ((r >> 3) << 8) | ((b >> 3) << 3) | (g >> 5)

#define	color_bgra(r,g,b,a)		((a << 24) | (r << 16) | (g << 8) | b)
#define	color_abgr(r,g,b,a)		((r << 24) | (g << 16) | (b << 8) | a)
#define	color_argb(r,g,b,a)		((b << 24) | (g << 16) | (r << 8) | a)
#define	color_rgba(r,g,b,a)		((a << 24) | (b << 16) | (g << 8) | r)

#define get_pix_rgba(col)	float old_r = ((col) & 0xFF);			\
							float old_g = (((col) >> 8) & 0xFF);	\
							float old_b = (((col) >> 16) & 0xFF);	\
							float old_a = (((col) >> 24) & 0xFF);

#define get_pix_argb(col)	float old_a = ((col) & 0xFF);			\
							float old_r = (((col) >> 8) & 0xFF);	\
							float old_g = (((col) >> 16) & 0xFF);	\
							float old_b = (((col) >> 24) & 0xFF);

#define get_pix_bgra(col)	float old_b = ((col) & 0xFF);			\
							float old_g = (((col) >> 8) & 0xFF);	\
							float old_r = (((col) >> 16) & 0xFF);	\
							float old_a = (((col) >> 24) & 0xFF);
							
#define get_pix_abgr(col)	float old_a = ((col) & 0xFF);			\
							float old_b = (((col) >> 8) & 0xFF);	\
							float old_g = (((col) >> 16) & 0xFF);	\
							float old_r = (((col) >> 24) & 0xFF);

///////////////////////////////////////////////////////////////////////
// Function				:	displayThread
// Description			:	Starts the display thread
// Return Value			:
// Comments				:
void		*displayThread(void *w) {
	CXDisplay	*cDisplay		=	(CXDisplay *) w;

	// The thread main loop
	cDisplay->main();

	return NULL;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CXDisplay
// Method				:	CXDisplay
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CXDisplay::CXDisplay(const char *name,const char *samples,int width,int height,int numSamples)
: CDisplay(name,samples,width,height,numSamples) {
	int				x,y;
	unsigned int	*dest;
	unsigned short	*dests;
	unsigned short	byteOrder = 0x0100;
	int				flipByteOrder;
	Visual			*vis;
	
	XInitThreads();
	display				=	XOpenDisplay (NULL);

	if (display == NULL) failure	=	TRUE;
	else {
		WM_DELETE_WINDOW	=	XInternAtom(display, "WM_DELETE_WINDOW",	0);
		WM_PROTOCOLS		=	XInternAtom(display, "WM_PROTOCOLS",		0);

		screen				=	DefaultScreen (display);
		imageDepth			=	DefaultDepth (display, screen);
		flipByteOrder		=	ImageByteOrder(display);
		vis					=	DefaultVisual (display,screen);

		flipByteOrder = (*((unsigned char*)&byteOrder) != flipByteOrder);
		
		// Allocate memory and create a checkerboard pattern
		switch(imageDepth){
			case 15:
				if(vis->red_mask == 0x001F){
					if(flipByteOrder)	dataHandler = &CXDisplay::handleData_rgb15_rev;
					else				dataHandler = &CXDisplay::handleData_rgb15;
				}
				else{
					if(flipByteOrder)	dataHandler = &CXDisplay::handleData_bgr15_rev;
					else				dataHandler = &CXDisplay::handleData_bgr15;
				}
				imageData			=	malloc(width*height*sizeof(unsigned short));
				dests				=	(unsigned short *) imageData;

				for (y=0;y<height;y++) {
					for (x=0;x<width;x++) {
						int	t	=	0;

						if ((x & 63) < 32)	t ^=	1;
						if ((y & 63) < 32)	t ^=	1;

						if (t) {
							*dests++	=	color_15_rgb(128,128,128,128);	// all chanels identical, so format irrelevant
						} else {
							*dests++	=	color_15_rgb(255,255,255,255);
						}

					}
				}
				break;
			
			case 16:
				if(vis->red_mask == 0x001F){
					if(flipByteOrder)	dataHandler = &CXDisplay::handleData_rgb16_rev;
					else				dataHandler = &CXDisplay::handleData_rgb16;
				}
				else{
					if(flipByteOrder)	dataHandler = &CXDisplay::handleData_bgr16_rev;
					else				dataHandler = &CXDisplay::handleData_bgr16;
				}
				imageData			=	malloc(width*height*sizeof(unsigned short));
				dests				=	(unsigned short *) imageData;

				for (y=0;y<height;y++) {
					for (x=0;x<width;x++) {
						int	t	=	0;

						if ((x & 63) < 32)	t ^=	1;
						if ((y & 63) < 32)	t ^=	1;

						if (t) {
							*dests++	=	color_16_rgb(128,128,128,128);	// all chanels identical, so format irrelevant
						} else {
							*dests++	=	color_16_rgb(255,255,255,255);
						}

					}
				}
				break;
				
			case 24:
			case 32:
				if(vis->red_mask == 0x000000FF){
					if(flipByteOrder)	dataHandler = &CXDisplay::handleData_abgr32;
					else				dataHandler = &CXDisplay::handleData_rgba32;
				}
				else if(vis->red_mask == 0x0000FF00){
					if(flipByteOrder)	dataHandler = &CXDisplay::handleData_bgra32;
					else				dataHandler	= &CXDisplay::handleData_argb32;
				}
				else if(vis->red_mask == 0x00FF0000){
					if(flipByteOrder)	dataHandler = &CXDisplay::handleData_argb32;
					else				dataHandler = &CXDisplay::handleData_bgra32;
				}
				else{
					if(flipByteOrder)	dataHandler = &CXDisplay::handleData_rgba32;
					else				dataHandler = &CXDisplay::handleData_abgr32;
				}
				imageData			=	malloc(width*height*sizeof(unsigned int));
				dest				=	(unsigned int *) imageData;

				for (y=0;y<height;y++) {
					for (x=0;x<width;x++) {
						int	t	=	0;

						if ((x & 63) < 32)	t ^=	1;
						if ((y & 63) < 32)	t ^=	1;

						if (t) {
							*dest++	=	color_argb(128,128,128,128);	// all chanels identical, so format irrelevant
						} else {
							*dest++	=	color_argb(255,255,255,255);
						}

					}
				}
				break;

			default:
				fprintf(stderr,"Unsupported sample format for framebuffer display\n");
				imageData = NULL;
				failure = true;
		}
		

		if (imageData != NULL) {
			displayName = strdup(name);
			pthread_create(&thread, NULL , displayThread, this);
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CXDisplay
// Method				:	~CXDisplay
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CXDisplay::~CXDisplay() {
	free(displayName);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CXDisplay
// Method				:	main
// Description			:	The main display loop
// Return Value			:	-
// Comments				:
void	CXDisplay::main() {
	int			i,j;

	assert(display != NULL);
	assert(failure == FALSE);

	windowUp	=	FALSE;
	windowDown	=	FALSE;

	XSetWindowAttributes	window_attributes;
	unsigned long			window_mask;
	XSizeHints				window_hints;
	int						running	=	TRUE;

	window_attributes.border_pixel		= BlackPixel (display, screen);
	window_attributes.background_pixel	= BlackPixel (display, screen);
	window_attributes.override_redirect = 0;
	window_mask							= CWBackPixel | CWBorderPixel;
	xcanvas								= XCreateWindow (display,
														DefaultRootWindow (display),
														0,
														0,
														width,height,
														0,
														imageDepth,
														InputOutput,
														CopyFromParent,
														window_mask,
														&window_attributes);


	int	scanSize;

	switch(imageDepth) {
	case 15:
	case 16:
		xim = XCreateImage (
			display,
			CopyFromParent,
			imageDepth,
			ZPixmap,
			0,
			(char *) imageData,
			width,
			height,
			16,
			width*2);
		break;
	case 24:
	case 32:
		xim = XCreateImage (
			display,
			CopyFromParent,
			imageDepth,
			ZPixmap,
			0,
			(char *) imageData,
			width,
			height,
			32,
			width*4);
		break;
	}

	image_gc = XCreateGC (display, xcanvas, 0, 0);

	XMapWindow (display, xcanvas);

	XChangeProperty(display, xcanvas, WM_PROTOCOLS,XA_ATOM, 32, 0, (unsigned char *)&WM_DELETE_WINDOW, 1);
	
	XStoreName(display, xcanvas, displayName);

	XSelectInput(display, xcanvas, ExposureMask | StructureNotifyMask | KeyPressMask);

	// Initial Image

	XPutImage (display, xcanvas, image_gc, xim, 0, 0, 0, 0, width, height);
	XFlush(display);
	
	windowUp	=	TRUE;

	while (running)	{
		XEvent x_event;
		XExposeEvent exp_event;
		
		XNextEvent(display, &x_event);
		switch  (x_event.type) {
   		case Expose:
			exp_event = x_event.xexpose;
			XPutImage (display, xcanvas, image_gc, xim, exp_event.x, exp_event.y,
				exp_event.x, exp_event.y, exp_event.width, exp_event.height);
			XFlush(display);
		break;            
 		case KeyPress:
 			{
 				KeySym key = XLookupKeysym(&x_event.xkey, 0);
				if(key == XK_Escape || key == XK_q)	{
					running	= FALSE;
				}
			}
		break;
		case DestroyNotify:
			running	=	FALSE;
		break;
		case ClientMessage:
			{
				const long* data = x_event.xclient.data.l;
				if ((Atom)(data[0]) == WM_DELETE_WINDOW) {
					running	=FALSE;
 	  			}
			}
		break;
		}
 	}

	windowDown	=	TRUE;

	XUnmapWindow(display,xcanvas);
	XFreeGC(display,image_gc);
	XDestroyImage(xim);
	XDestroyWindow(display,xcanvas);
	XCloseDisplay(display);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CXDisplay
// Method				:	finish
// Description			:	Finish displaying data
// Return Value			:	-
// Comments				:
void		CXDisplay::finish() {
	if(!windowDown){
		XPutImage (display, xcanvas, image_gc, xim, 0, 0, 0, 0, width, height);
		XFlush(display);
	}

	pthread_join(thread,NULL);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CXDisplay
// Method				:	handleData_xxx
// Description			:	Stuff data into pixmap
// Return Value			:	-
// Comments				:

#define STUFF_MONO_ROW(colorPacker,v)										\
	for (j=0;j<w;j++) {														\
		unsigned char	dv	=	(unsigned char) ((v)*255);					\
		*dest++				=	colorPacker(dv,dv,dv,dv);					\
		src++;																\
	}

#define STUFF_ROW(colorPacker,r,g,b,inc)									\
	for (j=0;j<w;j++) {														\
		unsigned char	dr	=	(unsigned char) ((r)*255);					\
		unsigned char	dg	=	(unsigned char) ((g)*255);					\
		unsigned char	db	=	(unsigned char) ((b)*255);					\
		*dest++				=	colorPacker(dr,dg,db,(unsigned char) 0);	\
		src					+=	inc;										\
	}

#define STUFF_ALPHA_ROW(colorPacker,colorUnpacker,r,g,b,a,inc)				\
	for (j=0;j<w;j++) {														\
		colorUnpacker(dest[0])												\
		float			nr	=	(r)*(a)*255	+ (1-(a))*old_r;				\
		float			ng	=	(g)*(a)*255	+ (1-(a))*old_g;				\
		float			nb	=	(b)*(a)*255	+ (1-(a))*old_b;				\
		float			na	=	(a)*255		+ (1-(a))*old_a;				\
		unsigned char	dr	=	(unsigned char) nr;							\
		unsigned char	dg	=	(unsigned char) ng;							\
		unsigned char	db	=	(unsigned char) nb;							\
		unsigned char	da	=	(unsigned char) na;							\
		*dest++				=	colorPacker(dr,dg,db,da);					\
		src					+=	inc;										\
	}

#define STUFF_ALPHA_ROW_16(colorPacker,r,g,b,a,inc)							\
	for (j=0;j<w;j++) {														\
		float			nr	=	(r)*(a)*255;								\
		float			ng	=	(g)*(a)*255;								\
		float			nb	=	(b)*(a)*255;								\
		float			na	=	(a)*255;									\
		unsigned char	dr	=	(unsigned char) nr;							\
		unsigned char	dg	=	(unsigned char) ng;							\
		unsigned char	db	=	(unsigned char) nb;							\
		unsigned char	da	=	(unsigned char) na;							\
		*dest++				=	colorPacker(dr,dg,db,da);					\
		src					+=	inc;										\
	}

#define DEFINE_DATA_HANDLER_16(fn_name,colorPacker)												\
	void CXDisplay::handleData_##fn_name(int x, int y, int w, int h, float *d){					\
		int i,j;																				\
		switch(numSamples){																		\
		case 0:																					\
			break;																				\
		case 1:																					\
			for (i=0;i<h;i++) {																	\
				const float		*src	=	&d[i*w*numSamples];									\
				unsigned short	*dest	=	&((unsigned short *) imageData)[((i+y)*width+x)];	\
				STUFF_MONO_ROW(colorPacker,src[0])												\
			}																					\
			break;																				\
		case 2:																					\
			for (i=0;i<h;i++) {																	\
				const float		*src	=	&d[i*w*numSamples];									\
				unsigned short	*dest	=	&((unsigned short *) imageData)[((i+y)*width+x)];	\
				STUFF_ALPHA_ROW_16(colorPacker,src[0],src[0],src[0],src[1],2)					\
			}																					\
			break;																				\
		case 3:																					\
			for (i=0;i<h;i++) {																	\
				const float		*src	=	&d[i*w*numSamples];									\
				unsigned short	*dest	=	&((unsigned short *) imageData)[((i+y)*width+x)];	\
				STUFF_ROW(colorPacker,src[0],src[1],src[2],3)									\
			}																					\
			break;																				\
		case 4:																					\
			for (i=0;i<h;i++) {																	\
				const float		*src	=	&d[i*w*numSamples];									\
				unsigned short	*dest	=	&((unsigned short *) imageData)[((i+y)*width+x)];	\
				STUFF_ALPHA_ROW_16(colorPacker,src[0],src[1],src[2],src[3],4)					\
			}																					\
		default:																				\
			for (i=0;i<h;i++) {																	\
				const float		*src	=	&d[i*w*numSamples];									\
				unsigned short	*dest	=	&((unsigned short *) imageData)[((i+y)*width+x)];	\
				STUFF_ALPHA_ROW_16(colorPacker,src[0],src[1],src[2],src[3],numSamples)			\
			}																					\
		}																						\
	}

#define DEFINE_DATA_HANDLER(fn_name,colorPacker,colorUnpacker)										\
	void CXDisplay::handleData_##fn_name(int x, int y, int w, int h, float *d){						\
		int i,j;																					\
		switch(numSamples){																			\
		case 0:																						\
			break;																					\
		case 1:																						\
			for (i=0;i<h;i++) {																		\
				const float		*src	=	&d[i*w*numSamples];										\
				unsigned int	*dest	=	&((unsigned int *) imageData)[((i+y)*width+x)];			\
				STUFF_MONO_ROW(colorPacker,src[0])													\
			}																						\
			break;																					\
		case 2:																						\
			for (i=0;i<h;i++) {																		\
				const float		*src	=	&d[i*w*numSamples];										\
				unsigned int	*dest	=	&((unsigned int *) imageData)[((i+y)*width+x)];			\
				STUFF_ALPHA_ROW(colorPacker,colorUnpacker,src[0],src[0],src[0],src[1],2)			\
			}																						\
			break;																					\
		case 3:																						\
			for (i=0;i<h;i++) {																		\
				const float		*src	=	&d[i*w*numSamples];										\
				unsigned int	*dest	=	&((unsigned int *) imageData)[((i+y)*width+x)];			\
				STUFF_ROW(colorPacker,src[0],src[1],src[2],3)										\
			}																						\
			break;																					\
		case 4:																						\
			for (i=0;i<h;i++) {																		\
				const float		*src	=	&d[i*w*numSamples];										\
				unsigned int	*dest	=	&((unsigned int *) imageData)[((i+y)*width+x)];			\
				STUFF_ALPHA_ROW(colorPacker,colorUnpacker,src[0],src[1],src[2],src[3],4)			\
			}																						\
		default:																					\
			for (i=0;i<h;i++) {																		\
				const float		*src	=	&d[i*w*numSamples];										\
				unsigned int	*dest	=	&((unsigned int *) imageData)[((i+y)*width+x)];			\
				STUFF_ALPHA_ROW(colorPacker,colorUnpacker,src[0],src[1],src[2],src[3],numSamples)	\
			}																						\
		}																							\
	}

DEFINE_DATA_HANDLER_16(rgb16,color_16_rgb)
DEFINE_DATA_HANDLER_16(rgb16_rev,color_16_rgb_rev)
DEFINE_DATA_HANDLER_16(bgr16,color_16_bgr)
DEFINE_DATA_HANDLER_16(bgr16_rev,color_16_bgr_rev)

DEFINE_DATA_HANDLER_16(rgb15,color_15_rgb)
DEFINE_DATA_HANDLER_16(rgb15_rev,color_15_rgb_rev)
DEFINE_DATA_HANDLER_16(bgr15,color_15_bgr)
DEFINE_DATA_HANDLER_16(bgr15_rev,color_15_bgr_rev)

DEFINE_DATA_HANDLER(rgba32,color_rgba,get_pix_rgba)
DEFINE_DATA_HANDLER(argb32,color_argb,get_pix_argb)
DEFINE_DATA_HANDLER(bgra32,color_bgra,get_pix_bgra)
DEFINE_DATA_HANDLER(abgr32,color_abgr,get_pix_abgr)

///////////////////////////////////////////////////////////////////////
// Class				:	CXDisplay
// Method				:	data
// Description			:	Commit the image data
// Return Value			:	-
// Comments				:
int		CXDisplay::data(int x,int y,int w,int h,float *d) {
	int	i,j;

	if (windowDown)	return FALSE;

	clampData(w,h,d);
	
	(this->*dataHandler)(x,y,w,h,d);	// call the appropriate pixel writer
	
	if (windowUp) {
		XPutImage (display, xcanvas, image_gc, xim, x, y, x, y, w, h);
		XFlush(display);
	}

	return TRUE;
}

