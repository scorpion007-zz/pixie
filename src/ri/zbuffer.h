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
//  File				:	zbuffer.h
//  Classes				:	CZbuffer
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef ZBUFFER_H
#define ZBUFFER_H

#include "common/global.h"
#include "reyes.h"
#include "occlusion.h"



///////////////////////////////////////////////////////////////////////
// Class				:	CZbuffer
// Description			:	This is the zbuffer hider (a scanline renderer)
// Comments				:
class	CZbuffer : public CReyes , public COcclusionCuller {
public:
				CZbuffer(int thread);
				~CZbuffer();

	static void	preDisplaySetup();

				// The functions inherited from the CReyes
	void		rasterBegin(int,int,int,int,int);
	void		rasterDrawPrimitives(CRasterGrid *);
	void		rasterEnd(float *,int);
private:
	// The local variables
	int			totalWidth,totalHeight;
	float		**fb;												// The sample buffer
	int			top,left,bottom,right;
	int			width,height;
	int			sampleWidth,sampleHeight;
};

#endif










