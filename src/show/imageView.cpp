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
//  File				:	imageView.cpp
//  Classes				:	CImageView
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include <math.h>
#include <string.h>
#include <tiff.h>
#include <tiffio.h>
#include "imageView.h"

///////////////////////////////////////////////////////////////////////
// Function				:	convert
// Description			:	Convert the input texture to float per sample
// Return Value			:	-
// Comments				:
// Date last edited		:	10/5/2005
static	void	convert(float *dest,void *src,int n,int bpp) {
	int				i;
	unsigned char	*src8;
	unsigned short	*src16;
	float			*src32f;

	switch(bpp) {
		case 8:
			src8	=	(unsigned char *) src;
			for (i=0;i<n;i++) {
				dest[i]	=	src8[i]/255.0f;
			}
			break;
		case 16:
			src16	=	(unsigned short *) src;
			for (i=0;i<n;i++) {
				dest[i]	=	src16[i]/65535.0f;
			}
			break;
		case 32:
			src32f	=	(float *) src;
			for (i=0;i<n;i++) {
				dest[i]	=	src32f[i];
			}
			break;
		default:
			break;
	}
}




///////////////////////////////////////////////////////////////////////
// Class				:	CImageView
// Method				:	CImageView
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	10/5/2005
CImageView::CImageView(void *tin) {
	TIFF	*in		=	(TIFF *) tin;

	// Init the memory
	textureIndex	=	0;
	xoffset			=	0;
	yoffset			=	0;
	length			=	1;

	// Read the texture from memory
	readTexture(in);

	// Print usage
	fprintf(stdout,"LMB     = pan\n");
	fprintf(stdout,"LMB+RMB = zoom\n");
	fprintf(stdout,"'z'+LMB = zoom\n");
	fprintf(stdout,"'r'     = reset\n");
}

///////////////////////////////////////////////////////////////////////
// Class				:	CImageView
// Method				:	~CImageView
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	10/5/2005
CImageView::~CImageView() {
	glDeleteTextures(1,&textureIndex);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CImageView
// Method				:	readTexture
// Description			:	Read the texture from file
// Return Value			:	-
// Comments				:
// Date last edited		:	10/5/2005
void	CImageView::readTexture(TIFF *in) {
	uint32			fileWidth,fileHeight;
	uint16			numSamples;
	uint16			bitspersample;
	unsigned char	*tmp1;
	float			*tmp2;
	float			*texture;
	int				i,j;
	GLenum			channelTypeGL;

	// Read the tiff info
	TIFFGetFieldDefaulted(in,TIFFTAG_IMAGEWIDTH              ,&fileWidth);
	TIFFGetFieldDefaulted(in,TIFFTAG_IMAGELENGTH             ,&fileHeight);
	TIFFGetFieldDefaulted(in,TIFFTAG_SAMPLESPERPIXEL         ,&numSamples);
	TIFFGetFieldDefaulted(in,TIFFTAG_BITSPERSAMPLE           ,&bitspersample);

	// Set the required fields
	width					=	fileWidth;
	height					=	fileHeight;
	for (texWidth=1;texWidth<width;texWidth=texWidth<<1);
	for (texHeight=1;texHeight<height;texHeight=texHeight<<1);
	texture					=	new float[texWidth*texHeight*numSamples];

	fprintf(stdout,"->%dx%d[%d samples,%d bits / pixel]\n",width,height,numSamples,bitspersample*numSamples);

	// Is this a tiled image ?
	if (TIFFIsTiled(in)) {
		uint32	tileWidth,tileHeight;

		TIFFGetFieldDefaulted(in,TIFFTAG_TILEWIDTH				 ,&tileWidth);
		TIFFGetFieldDefaulted(in,TIFFTAG_TILELENGTH		         ,&tileHeight);

		fprintf(stdout,"->Tilesize: %dx%d\n",tileWidth,tileHeight);

		// Allocate temp memory
		tmp1	=	new unsigned char[tileWidth*tileHeight*numSamples*4];
		tmp2	=	new float[tileWidth*tileHeight*numSamples];

		// Read the texture
		for (j=0;j<height;j+=tileHeight) {
			for (i=0;i<width;i+=tileWidth) {
				TIFFReadTile(in,tmp1,i,j,0,0);
				convert(tmp2,tmp1,tileWidth*tileHeight*numSamples,bitspersample);
				copy(texture,tmp2,i,j,tileWidth,tileHeight,numSamples);
			}
		}
	} else {

		// Allocate temp memory
		tmp1	=	new unsigned char[width*numSamples*4];
		tmp2	=	new float[width*numSamples];

		// Read the texture
		for (i=0;i<height;i++) {
			TIFFReadScanline(in,tmp1,i,0);
			convert(tmp2,tmp1,width*numSamples,bitspersample);
			copy(texture,tmp2,0,i,width,1,numSamples);
		}
	}

	// If this seems like a depth file, normalize
	if ((bitspersample == 32) && (numSamples == 1)) {
		float	minDepth	=	C_INFINITY;
		float	maxDepth	=	-C_INFINITY;

		fprintf(stdout,"->This seems like a depth file. Normalizing...\n");

		// Find the range
		for (j=0;j<height;j++) {
			for (i=0;i<width;i++) {
				if (texture[j*texWidth+i] >= 1e20) continue;
				if (texture[j*texWidth+i] < minDepth)	minDepth	=	texture[j*texWidth+i];
				if (texture[j*texWidth+i] > maxDepth)	maxDepth	=	texture[j*texWidth+i];
			}
		}

		// No the normalization
		if (maxDepth > minDepth) {
			const double tmp	=	1 / (maxDepth - minDepth);

			for (j=0;j<height;j++) {
				for (i=0;i<width;i++) {
					texture[j*texWidth+i]	=	(float) ((texture[j*texWidth+i] - minDepth)*tmp);
				}
			}
		}
	}

	
	
	// Load & bind the texture
	glGenTextures(1,&textureIndex);
	glBindTexture(GL_TEXTURE_2D,textureIndex);
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);  
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 

	switch(numSamples) {
	case 1:
		channelTypeGL	=	GL_LUMINANCE;
		break;
	case 2:
		channelTypeGL	=	GL_LUMINANCE_ALPHA;
		break;
	case 3:
		channelTypeGL	=	GL_RGB;
		break;
	case 4:
		channelTypeGL	=	GL_RGBA;
		break;
	default:
		channelTypeGL	=	GL_RGBA;
		break;
	}

	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,0,numSamples,texWidth,texHeight,0,channelTypeGL,GL_FLOAT,texture);	

	// Delete the temp memory
	delete [] tmp1;
	delete [] tmp2;
	delete [] texture;

	// Close the file
	TIFFClose(in);

	// Resize the image
	size(width,height);
	size_range(width,height);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CImageView
// Method				:	copy
// Description			:	Copy some portion of the image
// Return Value			:	-
// Comments				:
// Date last edited		:	10/5/2005
void	CImageView::copy(float *dest,float *src,int x,int y,int w,int h,int numSamples) {
	int	i;

	for (i=0;i<h;i++)
		memcpy(dest + (y+i)*texWidth*numSamples + x*numSamples,src + i*w*numSamples,w*numSamples*sizeof(float));
}


///////////////////////////////////////////////////////////////////////
// Class				:	CImageView
// Method				:	drawScene
// Description			:	Draw the image
// Return Value			:	-
// Comments				:
// Date last edited		:	10/5/2005
void			CImageView::drawScene() {

	// Clear the transformation
	glViewport(0,0,w(),h());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,width,texHeight-height,texHeight,0,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0,0,-0.5f);


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,textureIndex);

	glTranslatef(xoffset*this->width/CInterface::width,yoffset*this->height/CInterface::height,0);

	glTranslatef((float) (texWidth >> 1), (float) (texHeight >> 1),0);
	glScalef(length,length,1);
	glTranslatef((float) (-texWidth >> 1),(float) (-texHeight >> 1),0);

	glColor3f(1,1,1);
	glBegin(GL_QUADS);
	glTexCoord2f(0,1);	glVertex2i(0,0);
	glTexCoord2f(1,1);	glVertex2i(texWidth,0);
	glTexCoord2f(1,0);	glVertex2i(texWidth,texHeight);
	glTexCoord2f(0,0);	glVertex2i(0,texHeight);
	glEnd();
}


///////////////////////////////////////////////////////////////////////
// Class				:	CImageView
// Method				:	mouseDown
// Description			:	Mouse down handle
// Return Value			:	-
// Comments				:
// Date last edited		:	10/5/2005
void			CImageView::leftMouseDown(int x,int y) {
	lastXoffset	=	xoffset;
	lastYoffset	=	yoffset;
	lastLength	=	length;
	lastX		=	x;
	lastY		=	y;

	flags		|=	IMAGE_MOUSE_DOWN;
	
	if (Fl::event_button() == 1)
		flags	|=	FMOUSE_LEFT;
	else
		flags	|=	FMOUSE_RIGHT;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CImageView
// Method				:	leftMouseUp
// Description			:	Mouse down handle
// Return Value			:	-
// Comments				:
// Date last edited		:	10/5/2005
void			CImageView::leftMouseUp(int x,int y) {
	flags		&=	~IMAGE_MOUSE_DOWN;
	
	if (Fl::event_button() == 1)
		flags	&=	~FMOUSE_LEFT;
	else
		flags	&=	~FMOUSE_RIGHT;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CImageView
// Method				:	mouseMove
// Description			:	Mouse move handle
// Return Value			:	-
// Comments				:
// Date last edited		:	10/5/2005
void			CImageView::mouseMove(int x,int y) {

	if (flags & IMAGE_MOUSE_DOWN) {
		int	dx	=	x - lastX;
		int	dy	=	y - lastY;


		if ((flags & IMAGE_ZOOM) || ((flags & FMOUSE_LEFT) && (flags & FMOUSE_RIGHT))) {
			length	=	lastLength + dx / 500.0f;
		} else {
			xoffset	=	lastXoffset	+ dx;
			yoffset	=	lastYoffset - dy;
		}
	}

	redraw();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CImageView
// Method				:	keyDown
// Description			:	Key down handler
// Return Value			:	-
// Comments				:
// Date last edited		:	10/5/2005
void			CImageView::keyDown(char key) {
	if (key == 'z') {
		if ((flags & IMAGE_MOUSE_DOWN)) {
			flags	|=	IMAGE_ZOOM;
		}
	} else if (key == 'r') {
		xoffset			=	0;
		yoffset			=	0;
		length			=	1;

		size_range(width,height);

		redraw();
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CImageView
// Method				:	keyUp
// Description			:	Key up handler
// Return Value			:	-
// Comments				:
// Date last edited		:	10/5/2005
void			CImageView::keyUp(char key) {
	if (key == 'z') {
		flags	&=	~IMAGE_ZOOM;
	} else {
	}
}




