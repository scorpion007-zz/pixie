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
//  File				:	opengl.h
//  Classes				:	COpenGL
//  Description			:	The opengl hider
//
////////////////////////////////////////////////////////////////////////
#ifndef OPENGL_H
#define OPENGL_H

#include "common/global.h"
#include "common/os.h"

typedef	void	(*openglInitFun)(void *);
typedef void	(*openglTiniFun)();
typedef void	(*openglDrawGridFun)(int,int,const float *,const float *);

///////////////////////////////////////////////////////////////////////
// Class				:	CGraphics
// Description			:	This class encapsulates graphics hardware operations
// Comments				:
// Date last edited		:	10/2/2004;
class	CGraphics {
public:
						CGraphics(void *);
						~CGraphics();

		unsigned int	shader(void *,char *);								// Set a shader
		void			draw(void *,int,int,const float *,const float *);
};

#endif
