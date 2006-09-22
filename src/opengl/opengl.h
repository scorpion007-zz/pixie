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
//  Classes				:	-
//  Description			:	This is a wrapper for openGL so that Pixie 
//							can interact with OpenGL without linkinking to it
//
////////////////////////////////////////////////////////////////////////
#ifndef OPENGL_H
#define OPENGL_H




///////////////////////////////////////////////////////////////////////
// Class				:	CView
// Description			:	Encapsulates a data view
// Comments				:	The classes that "show" can visualize must be derived
// Date last edited		:	9/21/2006
class	CView {
public:
						CView()		{	}
		virtual			~CView()	{	}

		virtual	void	draw()							=	NULL;		// The draw the data
		virtual	void	bound(float *bmin,float *bmax)	=	NULL;		// Bound the data


						// The classes can use the following functions for drawing primitives
		virtual	void	drawTriangles(int n,const int *indices,const float *P,const float *C)	{	}
		virtual	void	drawPoints(int n,const float *P,const float *C)							{	}
};



#ifdef WIN32
#define	LIB_EXPORT				__declspec(dllexport)
#else
#define	LIB_EXPORT				extern
#endif






typedef void	(*TGlVisualizeFunction)(CView *view);

extern "C" {				
	LIB_EXPORT	void		pglVisualize(CView *view);
}


#endif
