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
//  File				:	debug.h
//  Classes				:	Various classes/functions to help debugging
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef DEBUGFILE_H
#define DEBUGFILE_H

#include "common/global.h"
#include "common/algebra.h"
#include "common/os.h"
#include "gui/opengl.h"


///////////////////////////////////////////////////////////////////////
// Class				:	CDebugView
// Description			:	This class is used to draw various things
// Comments				:
class	CDebugView : public CView {
public:
								CDebugView(const char *fileName,int append=FALSE);
								CDebugView(FILE *in,const char *fileName);
								~CDebugView();

				void			point(const float *P)	{
									addBox(bmin,bmax,P);
									int	i	=	0;
									fwrite(&i,sizeof(int),1,file);
									fwrite(P,sizeof(float),3,file);
								}

				void			line(const float *P1,const float *P2) {
									addBox(bmin,bmax,P1);
									addBox(bmin,bmax,P2);
									int	i	=	1;
									fwrite(&i,sizeof(int),1,file);
									fwrite(P1,sizeof(float),3,file);
									fwrite(P2,sizeof(float),3,file);
								}

				void			triangle(const float *P1,const float *P2,const float *P3) {
									addBox(bmin,bmax,P1);
									addBox(bmin,bmax,P2);
									addBox(bmin,bmax,P3);
									int	i	=	2;
									fwrite(&i,sizeof(int),1,file);
									fwrite(P1,sizeof(float),3,file);
									fwrite(P2,sizeof(float),3,file);
									fwrite(P3,sizeof(float),3,file);
								}

				void			quad(const float *P1,const float *P2,const float *P3,const float *P4) {
									addBox(bmin,bmax,P1);
									addBox(bmin,bmax,P2);
									addBox(bmin,bmax,P3);
									int	i	=	3;
									fwrite(&i,sizeof(int),1,file);
									fwrite(P1,sizeof(float),3,file);
									fwrite(P2,sizeof(float),3,file);
									fwrite(P3,sizeof(float),3,file);
									fwrite(P4,sizeof(float),3,file);
								}

				// Stuff inherited from CView
				void			draw();
				void			bound(float *bmin,float *bmax);
				int				keyDown(int key) { return FALSE;	}
private:
				vector			bmin,bmax;
				int				writing;
				FILE			*file;
				const char		*fileName;
};

#endif

