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
//  File				:	imageView.h
//  Classes				:	CImageView
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include "interface.h"

#define	IMAGE_MOUSE_DOWN	1
#define	IMAGE_ZOOM			2
#define	FMOUSE_LEFT			4
#define	FMOUSE_RIGHT		8

///////////////////////////////////////////////////////////////////////
// Class				:	CImageView
// Description			:	Display an image rendered with Pixie
// Comments				:
// Date last edited		:	10/4/2005
class CImageView : public CInterface {
public:
					CImageView(void *);
					~CImageView();

	void			drawScene();
	void			leftMouseDown(int,int);
	void			leftMouseUp(int,int);
	void			mouseMove(int,int);
	void			keyDown(char);
	void			keyUp(char);
private:
	void			copy(float *,float *,int,int,int,int,int);
	void			readTexture(TIFF *in);

	int				texWidth,texHeight;		// The texture dimensions (powers of two)
	int				width,height;			// The image dimensions
	GLuint			textureIndex;			// The texture index
	
	float			length;
	float			xoffset,yoffset;
	int				lastX,lastY;
	float			lastXoffset,lastYoffset,lastLength;
	int				flags;
};


#endif
