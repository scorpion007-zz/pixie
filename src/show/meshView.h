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
//  File				:	meshview.h
//  Classes				:	CMeshView
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef MESHVIEW_H
#define MESHVIEW_H

#include <stdio.h>

#include "interface.h"

const unsigned int	POLYGON_WIREFRAME	=	1;	// Draw the wireframe
const unsigned int	POLYGON_SOLID		=	2;	// Draw the solid polygons
const unsigned int	POLYGON_CULLFACE	=	4;	// Enable back face culling

///////////////////////////////////////////////////////////////////////
// Class				:	CMeshView
// Description			:	Display triangle meshes
// Comments				:
// Date last edited		:
class	CMeshView : public CInterface {
public:
			CMeshView(FILE *);
			~CMeshView();

	void	drawScene();
	void	keyDown(char);
private:
	int		solidBase;
	vector	bmin,bmax;

	int		polygonMode;
};

#endif




