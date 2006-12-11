//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright � 1999 - 2003, Okan Arikan
//
// Contact: okan@cs.utexas.edu
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
		fwrite(bmin,3,sizeof(float),file);
		fwrite(bmax,3,sizeof(float),file);
	} else {
		file	=	fopen(fileName,"ab");
		if (!feof(file)) {
			fread(bmin,3,sizeof(float),file);
			fread(bmax,3,sizeof(float),file);
			fseek(file,0,SEEK_END);
		} else {
			fwrite(bmin,3,sizeof(float),file);
			fwrite(bmax,3,sizeof(float),file);
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

	fread(bmin,3,sizeof(float),file);
	fread(bmax,3,sizeof(float),file);
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
		fwrite(bmin,3,sizeof(float),file);
		fwrite(bmax,3,sizeof(float),file);
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
