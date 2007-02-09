//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright © 1999 - 2003, Okan Arikan
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
//  File				:	displayChannel.cpp
//  Classes				:	CDisplayChannel
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include "displayChannel.h"
#include <string.h>


///////////////////////////////////////////////////////////////////////
// Class				:	CDisplayChannel
// Description			:	display channel info ctor
// Return Value			:
// Comments				:	var can be NULL
CDisplayChannel::CDisplayChannel() {
	strcpy(this->name,"*INVALID*");
	variable		=	NULL;
	numSamples		= 	0;
	sampleStart		=	-1;
	outType			=	-1;
	fill			=	NULL;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDisplayChannel
// Description			:	display channel info dtor
// Return Value			:
// Comments				:	var can be NULL
CDisplayChannel::~CDisplayChannel() {
	if (fill) delete [] fill;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDisplayChannel
// Description			:	display channel info ctor
// Return Value			:
// Comments				:	var can be NULL
CDisplayChannel::CDisplayChannel(const char *name,CVariable *var,int samples,int start,int entry) {
	strcpy(this->name,name);
	variable	=	var;
	numSamples	=	samples;
	sampleStart	=	start;
	outType		=	entry;
	fill		=	NULL;
}
