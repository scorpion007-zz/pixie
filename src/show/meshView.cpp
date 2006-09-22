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
//  File				:	meshview.cpp
//  Classes				:	CMeshView
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "meshView.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CMeshView
// Method				:	CMeshView
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	1/14/2002
CMeshView::CMeshView(FILE *in) : CInterface() {
	float	maxDim;

	// The initial polygon mode
	polygonMode		=	POLYGON_WIREFRAME | POLYGON_SOLID;

	make_current();

	if (in != NULL) {
		initv(bmin,C_INFINITY,C_INFINITY,C_INFINITY);
		initv(bmax,-C_INFINITY,-C_INFINITY,-C_INFINITY);

		solidBase	=	glGenLists(1);

		// First read and display the solid polygons
		glNewList(solidBase,GL_COMPILE);

		while(!feof(in)) {
			vector	p1,p2,p3;
			char	tmp[512];

			fgets(tmp,512,in);

			if (sscanf(tmp,"%f %f %f %f %f %f %f %f %f \n"	,&p1[COMP_X],&p1[COMP_Y],&p1[COMP_Z]
															,&p2[COMP_X],&p2[COMP_Y],&p2[COMP_Z]
															,&p3[COMP_X],&p3[COMP_Y],&p3[COMP_Z]) == 9) {
				
				addBox(bmin,bmax,p1);
				addBox(bmin,bmax,p2);
				addBox(bmin,bmax,p3);

				glBegin(GL_TRIANGLES);
				//glBegin(GL_LINE_LOOP);
				glVertex3fv(p1);
				glVertex3fv(p2);
				glVertex3fv(p3);
				glEnd();
			} else if (sscanf(tmp,"%f %f %f %f %f %f \n"	,&p1[COMP_X],&p1[COMP_Y],&p1[COMP_Z]
														,&p2[COMP_X],&p2[COMP_Y],&p2[COMP_Z]) == 6) {
														

				addBox(bmin,bmax,p1);
				addBox(bmin,bmax,p2);

				glBegin(GL_LINES);
				glVertex3fv(p2);
				glVertex3fv(p1);
				glEnd();
			} else if (sscanf(tmp,"%f %f %f - %f %f %f \n"	,&p1[COMP_X],&p1[COMP_Y],&p1[COMP_Z]
														,&p2[COMP_X],&p2[COMP_Y],&p2[COMP_Z]) == 6) {
														
				addBox(bmin,bmax,p1);

				glBegin(GL_POINTS);
				glColor3fv(p2);
				glVertex3fv(p1);
				glEnd();
			} else if (sscanf(tmp,"%f %f %f \n"	,&p1[COMP_X],&p1[COMP_Y],&p1[COMP_Z]) == 3) {
				addBox(bmin,bmax,p1);

				glBegin(GL_POINTS);
				//glColor3f(1,1,1);
				glVertex3fv(p1);
				glEnd();
			}

		}

		glEndList();

		fclose(in);
	}

	maxDim	=	max(max(bmax[0]-bmin[0],bmax[1] - bmin[1]),bmax[2] - bmin[2]);

	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glPointSize(3);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CMeshView
// Method				:	~CMeshView
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	1/14/2002
CMeshView::~CMeshView() {
	glDeleteLists(solidBase,1);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CMeshView
// Method				:	draw
// Description			:	Draw the mesh
// Return Value			:	-
// Comments				:
// Date last edited		:	1/14/2002
void	CMeshView::drawScene() {
	vector	mid,mid2;
	float	maxScale;

	glPushMatrix();

	addvv(mid,bmin,bmax);
	mulvf(mid,0.5);

	subvv(mid2,bmax,bmin);

	maxScale	=	max(mid2[COMP_X],mid2[COMP_Y]);
	maxScale	=	max(maxScale,mid2[COMP_Z]);
	maxScale	=	1 / maxScale;

	//glTranslatef(0,0,-2);

	glScalef(maxScale,maxScale,maxScale);

	glTranslatef(-mid[COMP_X],-mid[COMP_Y],-mid[COMP_Z]);

	if (polygonMode & POLYGON_CULLFACE) {
		glEnable(GL_CULL_FACE);
	} else {
		glDisable(GL_CULL_FACE);
	}

	// Draw the solid portion first
	glColor3f(1,1,1);
	glCallList(solidBase);

	glPopMatrix();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CMeshView
// Method				:	keyDown
// Description			:	Key press
// Return Value			:	-
// Comments				:
// Date last edited		:	1/14/2002
void	CMeshView::keyDown(char key) {
	if		(key == 'm') {
		polygonMode	^=	POLYGON_SOLID;
		refresh();
	} else if (key == 'w')	{
		polygonMode ^=	POLYGON_WIREFRAME;
		refresh();
	} else if (key == 'o')	{
		polygonMode ^=	POLYGON_CULLFACE;
		refresh();
	}

	else CInterface::keyDown(key);
}


/*
///////////////////////////////////////////////////////////////////////
// Class				:	CRawMotion
// Method				:	draw
// Description			:	Draw the raw data
// Return Value			:	-
// Comments				:
// Date last edited		:	10/3/2002
unsigned int	loadTexture(const char *name,const char *dir) {
	char			*type	=	"trilinear";
	char			tmp[256];
	char			fn[OS_MAX_PATH_LENGTH];
	unsigned int	id	=	0;

	if (schr(name,'.') == NULL) {
		sprintf(tmp,"%s.tif",name);
	} else {
		sprintf(tmp,"%s",name);
	}

	if (COs::locateFile(fn,tmp,dir) == FALSE) {
	} else {
		// Set the error handler so we don't crash
		//TIFFSetErrorHandler(errorHandler);
		//TIFFSetWarningHandler(errorHandler);
		TIFF			*in		=	TIFFOpen(fn,"r");
		unsigned char	*udata;
		int				i;
		uint32			w,h;
		uint16			ns,bp,organization;

		if (in == NULL)	return 0;

		// Set the necessary stuff
		TIFFGetFieldDefaulted(in, TIFFTAG_IMAGEWIDTH,			&w);
		TIFFGetFieldDefaulted(in, TIFFTAG_IMAGELENGTH,			&h);
		TIFFGetFieldDefaulted(in, TIFFTAG_SAMPLESPERPIXEL,		&ns);
		TIFFGetFieldDefaulted(in, TIFFTAG_BITSPERSAMPLE,		&bp);
		TIFFGetFieldDefaulted(in, TIFFTAG_SAMPLEFORMAT,			&organization);

		udata	=	new unsigned char[w*h*ns];

		for (i=0;i<(int) h;i++) {
			TIFFReadScanline(in,&udata[i*w*ns],i,0);
		}

		TIFFClose(in);


		glGenTextures(1,&id);
		glBindTexture(GL_TEXTURE_2D,id);
		glPixelStorei (GL_UNPACK_ALIGNMENT, 1);  
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		GLenum	channelTypeGL;
		GLenum	sampleTypeGL;

		switch(ns) {
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
		}

		sampleTypeGL		=	GL_UNSIGNED_BYTE;

		if (scmp(type,"bilinear") == 0) {
			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D,0,ns,w,h,0,channelTypeGL,sampleTypeGL,udata);	
		} else if (scmp(type,"trilinear") == 0) {
			gluBuild2DMipmaps(GL_TEXTURE_2D,3, w,h,channelTypeGL,sampleTypeGL,udata);
			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
       		glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		} else {
			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexImage2D(GL_TEXTURE_2D,0,ns,w,h,0,channelTypeGL,sampleTypeGL,udata);	
		}

		delete [] udata;
	}
	
	
	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 

	return id;
}
*/
