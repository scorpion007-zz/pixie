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
//  File				:	framebuffer.h
//  Classes				:	CDisplay
//  Description			:	Defines a generic display class that holds
//							the display data to be passed to the display thread
//
////////////////////////////////////////////////////////////////////////
#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "common/global.h"
#include "common/os.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CDisplay
// Description			:	Holds image data to be passed to the window thread
// Comments				:
class	CDisplay {
public:
					CDisplay(const char *,const char *,int,int,int);
	virtual			~CDisplay();

	int				failure;								// Set to TRUE in the case of an init error
	int				width,height,numSamples;				// The display properties
	char			*name;									// Name of the display
	char			*samples;								// Samples for the display

	virtual	int		data(int,int,int,int,float *)	= 0;	// Store data
	virtual	void	finish()						= 0;	// Finish displaying the data

			void	clampData(int,int,float *);				// Clamp the data so that everything is between 0 and 1
};


#endif







