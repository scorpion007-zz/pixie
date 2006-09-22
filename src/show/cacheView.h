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
//  File				:	cacheview.h
//  Classes				:	CCacheView
//  Description			:	The irradiance cache viewer
//
////////////////////////////////////////////////////////////////////////
#ifndef CACHEVIEW_H
#define CACHEVIEW_H

#include <stdio.h>

#include "interface.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CCacheView
// Description			:	The irradiance cache viewer
// Comments				:
// Date last edited		:	11/29/2003
class	CCacheView : public CInterface {
public:
					CCacheView(FILE *);
					~CCacheView();

	virtual	void	drawScene();
	virtual	void	keyDown(char);
private:
	void			reparse(int);
	void			readNode(FILE *);

	unsigned int	depList;
	unsigned int	cacheList;
	FILE			*in;
	int				offset;
	float			pointSize;
	int				drawSamples;
	int				drawDep;

	vector			bmin,bmax;
};

#endif



