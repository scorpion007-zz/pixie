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

class	CView;
class	CStatistics;

typedef void	(*TGlVisualizeFunction)(CView *view);
typedef void	(*TGlTriMeshFunction)(int n,const int *indices,const float *P,const float *C);
typedef void	(*TGlTrianglesFunction)(int n,const float *P,const float *C);
typedef void	(*TGlPointsFunction)(int n,const float *P,const float *C);


///////////////////////////////////////////////////////////////////////
// Class				:	CView
// Description			:	Encapsulates a data view
// Comments				:	The classes that "show" can visualize must be derived
// Date last edited		:	9/21/2006
class	CView {
public:
								CView()		{	}
		virtual					~CView()	{	}

		virtual	void			draw()							=	0;		// The draw the data
		virtual	void			bound(float *bmin,float *bmax)	=	0;		// Bound the data
		virtual	int				keyDown(int key) { return FALSE;	}		// Called when the user presses a key
																			// return TRUE if the data needs to be updated

		

								// The classes can use the following functions for drawing primitives
static	TGlTrianglesFunction	drawTriangles;		// The function to draw bunch of triangles
static	TGlTriMeshFunction		drawTriangleMesh;	// The function to draw bunch of triangles (organized into a mesh)
static	TGlPointsFunction		drawPoints;			// The function to draw bunch of points
static	void					*handle;			// The handle for the opengl.[dll/so/dylib] (only valid after show hider is constructed)
static	const int				chunkSize =	128*3;	// The number of primitives to draw at a time (must be a multiple of 3)
};



#ifndef LIB_EXPORT
#ifdef WIN32
#define	LIB_EXPORT				__declspec(dllexport)
#else
#define	LIB_EXPORT				extern
#endif
#endif



extern "C" {				
	LIB_EXPORT	void		pglVisualize(CView *view);
	LIB_EXPORT	void		pglTriangleMesh(int n,const int *indices,const float *P,const float *C);
	LIB_EXPORT	void		pglTriangles(int n,const float *P,const float *C);
	LIB_EXPORT	void		pglPoints(int n,const float *P,const float *C);

	LIB_EXPORT	void		pViewStats(CStatistics *statistics);
}


#endif
