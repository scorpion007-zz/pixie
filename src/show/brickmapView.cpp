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

#include "brickmapView.h"
#include "./ri/brickMap.h"
#include "./ri/memory.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonView
// Method				:	CPhotonView
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	1/14/2002
CBrickMapView::CBrickMapView(FILE *in,int fast,int level) : CInterface() {
	vector				bmin,bmax,center;
	int					i,maxDepth;
	float				side,invSide;

	
	// set up memory and brickmap managers
	memoryInit();
	CBrickMap::brickMapInit(150000L);
	
	// do our load
	int curPos = ftell(in);
	
	// dummy read 'seek to end'
	fseek(in,-4,SEEK_END);
	fread(&i,1,sizeof(int),in);
	fseek(in,i,SEEK_SET);

	// read channels
	int numChannels;
	int dataSize = 0;
	fread(&numChannels,1,sizeof(int),in);
	CTexture3dChannel *channels = new CTexture3dChannel[numChannels];
	for (i=0;i<numChannels;i++) {
		fread(&channels[i],1,sizeof(CTexture3dChannel),in);
		dataSize += channels[i].numSamples;
	}
	
	// the rest of the header
	fread(bmin,1,sizeof(vector),in);
	fread(bmax,1,sizeof(vector),in);
	fread(center,1,sizeof(vector),in);
	fread(&side,1,sizeof(float),in);
	invSide	=	1.0f / side;
	fread(&maxDepth,1,sizeof(int),in);
	
	addvf(bmax,bmin,side);
	addvv(center,bmin,bmax);
	mulvf(center,0.5f);

	// fseek back
	fseek(in,curPos,SEEK_SET);
	
	// now read the map
	CXform *dummy = new CXform();
	CBrickMap *bm = new CBrickMap(in,"brickmap",dummy);
	
	float cubePoints[] = {	0, 0, 0,
							1, 0, 0,
							1, 0, 1,
							0, 0, 1,
							
							0, 1, 0,
							1, 1, 0,
							1, 1, 1,
							0, 1, 1,
							
							0, 0, 0,
							1, 0, 0,
							1, 1, 0,
							0, 1, 0,
							
							0, 0, 1,
							1, 0, 1,
							1, 1, 1,
							0, 1, 1,
							
							0, 0, 0,
							0, 1, 0,
							0, 1, 1,
							0, 0, 1,
							
							1, 0, 0,
							1, 1, 0,
							1, 1, 1,
							1, 0, 1
							};
		
	brickLists = new unsigned int[4];
	brickLists[0] =	glGenLists(1);
	glNewList(brickLists[0],GL_COMPILE);
	glScalef(1/(5.0f*side),1/(5.0f*side),1/(5.0f*side));
	glTranslatef(-center[0],-center[1],-center[2]);
		
	if (level < 0 || level > maxDepth) {
		level = maxDepth / 2;
	}
	
	fprintf(stderr,"levels : %d\n",maxDepth);	
	fprintf(stderr,"loading level %d... \n",level);


	int nb = (1<<level);
	
	if (fast)	glBegin(GL_POINTS);
	else		glBegin(GL_TRIANGLES);
	
	for (int xe = 0;xe<nb-1;xe++) {
	for (int ye = 0;ye<nb-1;ye++) {
	for (int ze = 0;ze<nb-1;ze++) {
		int nlevel = level;
		float sz = side/(float)nb;
		int x =xe,y=ye,z=ze;
		
		CBrickMap::CBrick *bk = bm->findBrick(x,y,z,level,false,NULL);
		
/*		while (bk == NULL && nlevel>level-1) { 
			nlevel = nlevel-1;
			sz *= 2;
			x = x >>1;
			y = y >>1;
			z = z >>1;
			bk = bm->findBrick(x,y,z,nlevel,false,NULL);
		}
*/		
		if (bk == NULL) continue;
		
		CBrickMap::CVoxel *vx = bk->voxels;
		
		float *DD = (float*)((char*)vx + sizeof(CBrickMap::CVoxel));
		
		for(int zi =0; zi<8; zi++) {
		for(int yi =0; yi<8; yi++) {
		for(int xi =0; xi<8; xi++) {
			float *pts = cubePoints;
			
			glColor3fv(DD);
			vector cent;
			initv(cent,x*sz + xi*(sz/8.0f),y*sz + yi*(sz/8.0f),z*sz + zi*(sz/8.0f));
	
			float wt = vx->weight;
			
			vx = (CBrickMap::CVoxel*)((char*)vx + sizeof(float)*dataSize + sizeof(CBrickMap::CVoxel));
			DD = (float*)((char*) DD + sizeof(float)*dataSize + sizeof(CBrickMap::CVoxel));
			
			if (wt < C_EPSILON) continue;			

			if (!fast) {
				for(int j =0; j<6; j++) {
					vector tmp;
					
					#define emitPt(i)					\
						mulvf(tmp,pts+ i*3,sz/8.0f);	\
						addvv(tmp,cent);				\
						glVertex3fv(tmp);
					
						emitPt(0);
						emitPt(1);
						emitPt(2);
						emitPt(2);
						emitPt(3);
						emitPt(0);
					
					pts += 12;
				}
			} else {
				glVertex3fv(cent);
			}
			
		}}}
	}}}
	
	glEnd();
	glEndList();
	
	delete [] channels;
	delete bm;

	CBrickMap::brickMapShutdown();
	memoryTini();
	
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glClearColor(0.5,0.5,0.5,0);
	
	#ifndef GL_POINT_SPRITE_ARB
	#define GL_POINT_SPRITE_ARB	0x8861
	#endif
	glEnable(GL_POINT_SPRITE_ARB);
	glPointSize(5);

	fclose(in);
	
	fprintf(stderr,"done...\n");

}

///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonView
// Method				:	~CPhotonView
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	1/14/2002
CBrickMapView::~CBrickMapView() {
}

///////////////////////////////////////////////////////////////////////
// Class				:	CInterface
// Method				:	draw
// Description			:	Do the actual drawing
// Return Value			:	-
// Comments				:
// Date last edited		:	1/14/2002
void		CBrickMapView::drawScene() {

	glEnable(GL_POINT_SMOOTH);
	glCallList(brickLists[0]);
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


