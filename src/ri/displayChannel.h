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
//  File				:	displayChannel.h
//  Classes				:	CDisplayChannel
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef DISPLAYCHANNEL_H
#define DISPLAYCHANNEL_H

#include "common/os.h"
#include "variable.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CDisplayChannel
// Description			:	Holds information on a display channel
// Comments				:	if variable is NULL and entry is -1 this is
//						:	one of the standard rgbaz channels
//						:	sampleStart is filled at render time
class  CDisplayChannel {
public:
						CDisplayChannel();
						~CDisplayChannel();
						CDisplayChannel(const char*,CVariable*,int,int,int entry = -1);
	
	char				name[64];		// Name of the channel
	CVariable			*variable;		// The variable representing channel (may be NULL)
	float				*fill;			// The sample defaults
	int					numSamples;		// The size of channel sample
	int					outType;		// The entry index of the variable
	int					sampleStart;	// The offset in the shaded vertex array (-1 is unassigned)
};


#endif

