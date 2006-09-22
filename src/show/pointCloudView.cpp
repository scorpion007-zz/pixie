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
//  File				:	gatherview.h
//  Classes				:	CGatherView
//  Description			:	The gather cache viewer
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "pointCloudView.h"
#include "./ri/pointCloud.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonView
// Method				:	CPhotonView
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	1/14/2002
CPointCloudView::CPointCloudView(FILE *in) : CInterface() {
	int					numPhotons,maxPhotons;
	vector				bmin,bmax;
	CPointCloudPoint	*points;
	int					i;
	vector				mid;
	float				maxDim;

	int numChannels;
	int dataSize = 3;
	fread(&numChannels,1,sizeof(int),in);
	CTexture3dChannel *channels = new CTexture3dChannel[numChannels];
	for (i=0;i<numChannels;i++) {
		fread(&channels[i],1,sizeof(CTexture3dChannel),in);
		dataSize += channels[i].numSamples;
	}
	
	fread(&numPhotons,1,sizeof(int),in);
	fread(&maxPhotons,1,sizeof(int),in);

	printf("Points: %d\n",numPhotons);

	points	=	new CPointCloudPoint[numPhotons];

	fread(points,numPhotons,sizeof(CPointCloudPoint),in);
	fread(bmin,3,sizeof(float),in);
	fread(bmax,3,sizeof(float),in);
	
	float *data = new float[numPhotons*dataSize];
	fread(data,numPhotons,sizeof(float)*dataSize,in);

	addvv(mid,bmin,bmax);
	mulvf(mid,(float) 0.5);

	subvv(bmax,bmin);
	maxDim	=	max(bmax[0],bmax[1]);
	maxDim	=	max(bmax[2],maxDim);
	maxDim	*=	5;

	photonList	=	glGenLists(1);
	glNewList(photonList,GL_COMPILE);
	glScalef(1/maxDim,1/maxDim,1/maxDim);
	glTranslatef(-mid[0],-mid[1],-mid[2]);
	glBegin(GL_POINTS);
	for (i=1;i<numPhotons;i++) {
		//points[i].C[0]	=	min(points[i].C[0]);
		//points[i].C[1]	=	min(points[i].C[1]);
		//points[i].C[2]	=	min(points[i].C[2]);
		//normalizev(points[i].C);
		
		float *DD = data + i*dataSize;
		glColor3fv(DD);
		glVertex3fv(points[i].P);
	}
	glEnd();
	glEndList();
	
	delete [] points;
	delete [] data;
	delete [] channels;

	glEnable(GL_DEPTH_TEST);

	fclose(in);

}

///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonView
// Method				:	~CPhotonView
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	1/14/2002
CPointCloudView::~CPointCloudView() {
}

///////////////////////////////////////////////////////////////////////
// Class				:	CInterface
// Method				:	draw
// Description			:	Do the actual drawing
// Return Value			:	-
// Comments				:
// Date last edited		:	1/14/2002
void		CPointCloudView::drawScene()	{
	glEnable(GL_POINT_SMOOTH);
	glCallList(photonList);
	glDisable(GL_POINT_SMOOTH);

	/*
	glColor3f(1,1,1);
	glBegin(GL_LINES);
	glVertex3f(0,0,0);
	glVertex3f(10,0,0);
	glVertex3f(0,0,0);
	glVertex3f(0,10,0);
	glVertex3f(0,0,0);
	glVertex3f(0,0,10);
	glEnd();
	*/
}


