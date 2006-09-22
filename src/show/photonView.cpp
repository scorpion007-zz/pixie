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

#include "photonView.h"
#include "./ri/photonMap.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonView
// Method				:	CPhotonView
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	1/14/2002
CPhotonView::CPhotonView(FILE *in) : CInterface() {
	int		numPhotons,maxPhotons;
	vector	bmin,bmax;
	CPhoton	*photons;
	int		i;
	vector	mid;
	float	maxDim;

	fread(&numPhotons,1,sizeof(int),in);
	fread(&maxPhotons,1,sizeof(int),in);

	printf("Photons: %d\n",numPhotons);

	photons	=	new CPhoton[numPhotons];

	fread(photons,numPhotons,sizeof(CPhoton),in);
	fread(bmin,3,sizeof(float),in);
	fread(bmax,3,sizeof(float),in);

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
		float	maxChannel;

		maxChannel	=	max(max(photons[i].C[0],photons[i].C[1]),photons[i].C[2]);
		mulvf(photons[i].C,1 / maxChannel);

		//photons[i].C[0]	=	min(photons[i].C[0]);
		//photons[i].C[1]	=	min(photons[i].C[1]);
		//photons[i].C[2]	=	min(photons[i].C[2]);
		//normalizev(photons[i].C);
		glColor3fv(photons[i].C);
		glVertex3fv(photons[i].P);
	}
	glEnd();
	glEndList();
	
	drawP = 1;
	drawN = 0;
	
	// Allow us to see N also
	photonNList	=	glGenLists(1);
	glNewList(photonNList,GL_COMPILE);
	glScalef(1/maxDim,1/maxDim,1/maxDim);
	glTranslatef(-mid[0],-mid[1],-mid[2]);
	glBegin(GL_LINES);
	for (i=1;i<numPhotons;i++) {
		float	maxChannel;

		maxChannel	=	max(max(photons[i].C[0],photons[i].C[1]),photons[i].C[2]);
		mulvf(photons[i].C,1 / maxChannel);

		//photons[i].C[0]	=	min(photons[i].C[0]);
		//photons[i].C[1]	=	min(photons[i].C[1]);
		//photons[i].C[2]	=	min(photons[i].C[2]);
		//normalizev(photons[i].C);
		glColor3fv(photons[i].C);
		vector Pdash;
		glVertex3fv(photons[i].P);
		movvv(Pdash,photons[i].N);
		mulvf(Pdash,0.1f);
		addvv(Pdash,photons[i].P);
		glVertex3fv(Pdash);
	}
	glEnd();
	glEndList();

	delete [] photons;

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
CPhotonView::~CPhotonView() {
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonView
// Method				:	~CPhotonView
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	1/14/2002
void	CPhotonView::keyDown(char k) {
	CInterface::keyDown(k);
	if ((k == 'p') || (k == 'P'))	drawP ^= 1;
	if ((k == 'n') || (k == 'N'))	drawN ^= 1;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CInterface
// Method				:	draw
// Description			:	Do the actual drawing
// Return Value			:	-
// Comments				:
// Date last edited		:	1/14/2002
void		CPhotonView::drawScene()	{
	if (drawP) {
		glEnable(GL_POINT_SMOOTH);
		glCallList(photonList);
		glDisable(GL_POINT_SMOOTH);
	}
	
	if (drawN) {
		glEnable(GL_LINE_SMOOTH);
		glCallList(photonNList);
		glDisable(GL_LINE_SMOOTH);
	}

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

