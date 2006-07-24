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
//  File				:	cacheview.cpp
//  Classes				:	CCacheView
//  Description			:	The irradiance cache viewer
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "cacheView.h"
#include "../ri/irradiance.h"
#include "../ri/depository.h"

static	int		rootNode;



///////////////////////////////////////////////////////////////////////
// Class				:	CCacheView
// Method				:	CCacheView
// Description			:	Ctor
// Return Value			:
// Comments				:
// Date last edited		:	11/29/2003
CCacheView::CCacheView(FILE *i) : CInterface() {
	in			=	i;
	offset		=	ftell(in);
	pointSize	=	1;
	drawSamples	=	1;
	drawDep		=	1;

	initv(bmax,-C_INFINITY);
	initv(bmin,C_INFINITY);

	reparse(0);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CCacheView
// Method				:	~CCacheView
// Description			:	Dtor
// Return Value			:
// Comments				:
// Date last edited		:	11/29/2003
CCacheView::~CCacheView() {
	glDeleteLists(depList,1);
	glDeleteLists(cacheList,1);

	fclose(in);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CCacheView
// Method				:	draw
// Description			:	Do the actual drawing
// Return Value			:	-
// Comments				:
// Date last edited		:	1/14/2002
void		CCacheView::drawScene()	{
	float	maxDim;
	vector	mid,tmp;

	addvv(mid,bmin,bmax);
	mulvf(mid,0.5f);

	subvv(tmp,bmax,bmin);
	maxDim	=	max(tmp[0],tmp[1]);
	maxDim	=	max(tmp[2],maxDim);
	maxDim	*=	5;

	glPointSize(pointSize);
	glEnable(GL_POINT_SMOOTH);
	glPushMatrix();

	// Center the view
	glScalef(1/maxDim,1/maxDim,1/maxDim);
	glTranslatef(-mid[0],-mid[1],-mid[2]);

	if (drawDep)		glCallList(depList);

	if (drawSamples)	glCallList(cacheList);

	glPopMatrix();
}


///////////////////////////////////////////////////////////////////////
// Class				:	CCacheView
// Method				:	keyDown
// Description			:	Key press event
// Return Value			:	-
// Comments				:
// Date last edited		:	1/14/2002
void		CCacheView::keyDown(char k)	{
	CInterface::keyDown(k);
	if ((k == 'c') || (k == 'C'))	reparse(0);
	if ((k == 'o') || (k == 'O'))	reparse(1);
	if ((k == 'e') || (k == 'E'))	reparse(2);
	if ((k == 's') || (k == 'S'))	drawSamples	^=	1;
	if ((k == 'd') || (k == 'D'))	drawDep		^=	1;
	if (k == ']')	pointSize++;
	if (k == '[')	pointSize--;

	redraw();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CCacheView
// Method				:	reparse
// Description			:	Re-parse the scene
// Return Value			:	-
// Comments				:
// Date last edited		:	1/14/2002
void		CCacheView::reparse(int mode) {
	int		maxDepth;
	matrix	tmp;

	fseek(in,offset,SEEK_SET);

	// Read the to world and from world matrices
	fread(tmp,			sizeof(matrix),1,in);
	fread(tmp,			sizeof(matrix),1,in);

	// Parse the depository
	if (FALSE) {
		int					numPhotons,maxPhotons;
		CDepositorySample	*photons;
		int					i;

		fread(&numPhotons,1,sizeof(int),in);
		fread(&maxPhotons,1,sizeof(int),in);

		photons	=	new CDepositorySample[numPhotons+1];

		fread(photons,numPhotons+1,sizeof(CDepositorySample),in);
		fread(bmin,3,sizeof(float),in);
		fread(bmax,3,sizeof(float),in);

		

		depList	=	glGenLists(1);
		glNewList(depList,GL_COMPILE);
		glBegin(GL_POINTS);
		for (i=1;i<=numPhotons;i++) {
			if (mode == 0) {
				glColor3fv(photons[i].C);
			} else if (mode == 1) {
				glColor3f(1 - photons[i].C[3],1 - photons[i].C[3],1 - photons[i].C[3]);
			} else if (mode == 2) {
				glColor3fv(photons[i].C+4);
			}

			glVertex3fv(photons[i].P);
		}
		glEnd();
		glEndList();

		delete [] photons;
	}

	// Parse the samples
	if (TRUE) {
		rootNode	=	TRUE;
		cacheList	=	glGenLists(1);
		glNewList(cacheList,GL_COMPILE);

		fread(&maxDepth,	sizeof(int),1,in);
		readNode(in);

		glEnd();
		glEndList();
	}

	glEnable(GL_DEPTH_TEST);
}




///////////////////////////////////////////////////////////////////////
// Function				:	readNode
// Description			:	Read an irradiance cache node
// Return Value			:	-
// Comments				:
// Date last edited		:	11/29/3003
void	CCacheView::readNode(FILE *in) {
	vector							center;
	float							side;
	int								numSamples;
	CIrradianceCache::CCacheSample	cSample;
	CIrradianceCache::CCacheNode	*c[8];

	assert(glGetError() == GL_NO_ERROR);

	fread(center,		sizeof(vector),1,in);
	fread(&side,		sizeof(float),1,in);
	fread(&numSamples,	sizeof(int),1,in);

	if (rootNode) {
		rootNode	=	FALSE;
		
		//glScalef(1 / side,1 / side,1 / side);
		//glTranslatef(-center[COMP_X],-center[COMP_Y],-center[COMP_Z]);
		
		glColor3f(0,1,0);
		glBegin(GL_POINTS);
	}

	for(;numSamples>0;numSamples--) {
		fread(&cSample,sizeof(CIrradianceCache::CCacheSample),1,in);

		addBox(bmin,bmax,cSample.P);
		glVertex3fv(cSample.P);
	}

	fread(c,8,sizeof(CIrradianceCache::CCacheNode *),in);
	if (c[0] != NULL)	{	readNode(in);	}
	if (c[1] != NULL)	{	readNode(in);	}
	if (c[2] != NULL)	{	readNode(in);	}
	if (c[3] != NULL)	{	readNode(in);	}
	if (c[4] != NULL)	{	readNode(in);	}
	if (c[5] != NULL)	{	readNode(in);	}
	if (c[6] != NULL)	{	readNode(in);	}
	if (c[7] != NULL)	{	readNode(in);	}
}
