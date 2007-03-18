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
//  File				:	debug.cpp
//  Classes				:	Various classes/functions to help debugging
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include "debug.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CDebugView
// Method				:	CDebugView
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CDebugView::CDebugView(const char *fileName,int append) {
	initv(bmin,C_INFINITY);
	initv(bmax,-C_INFINITY);

	this->writing	=	TRUE;
	this->fileName	=	fileName;

	if (append == FALSE) {
		file	=	fopen(fileName,"wb");
		fwrite(bmin,sizeof(float),3,file);
		fwrite(bmax,sizeof(float),3,file);
	} else {
		file	=	fopen(fileName,"r+b");
		if (file == NULL) file	=	fopen(fileName,"w+b");
		if (!feof(file)) {
			fread(bmin,sizeof(float),3,file);
			fread(bmax,sizeof(float),3,file);
			fseek(file,0,SEEK_END);
		} else {
			fwrite(bmin,sizeof(float),3,file);
			fwrite(bmax,sizeof(float),3,file);
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDebugView
// Method				:	CDebugView
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CDebugView::CDebugView(FILE *in,const char *fn) {
	
	file		=	in;
	writing		=	FALSE;
	fileName	=	fn;

	fread(bmin,sizeof(float),3,file);
	fread(bmax,sizeof(float),3,file);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDebugView
// Method				:	~CDebugView
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CDebugView::~CDebugView() {
	if (writing == TRUE) {
		fseek(file,0,SEEK_SET);
		fwrite(bmin,sizeof(float),3,file);
		fwrite(bmax,sizeof(float),3,file);
	}

	fclose(file);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CDebugView
// Method				:	draw
// Description			:	Draw the stuff in the file
// Return Value			:	-
// Comments				:
void		CDebugView::draw() {

	drawFile(fileName);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDebugView
// Method				:	bound
// Description			:	Bound the stuff in the file
// Return Value			:	-
// Comments				:
void		CDebugView::bound(float *bmin,float *bmax) {
	movvv(bmin,this->bmin);
	movvv(bmax,this->bmax);
}

