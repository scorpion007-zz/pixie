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
//  File				:	texmake.h
//  Classes				:	-
//  Description			:	Texture making functions
//
////////////////////////////////////////////////////////////////////////
#ifndef TEXMAKE_H
#define TEXMAKE_H

#include "common/global.h"
#include "ri.h"
#include "options.h"

void	makeTexture(char *input,char *output,TSearchpath *path,char *smode,char *tmode,RtFilterFunc filt,float fwidth,float fheight,int numParams,char **params,void **vals);
void	makeSideEnvironment(char *input,char *output,TSearchpath *path,char *smode,char *tmode,RtFilterFunc filt,float fwidth,float fheight,int numParams,char **params,void **vals,int);
void	makeCubicEnvironment(char *px,char *py,char *pz,char *nx,char *ny,char *nz,char *output,char *smode,char *tmode,TSearchpath *path,RtFilterFunc filt,float fwidth,float fheight,int numParams,char **params,void **vals,int);
void	makeSphericalEnvironment(char *input,char *output,TSearchpath *path,char *smode,char *tmode,RtFilterFunc filt,float fwidth,float fheight,int numParams,char **params,void **vals);
void	makeCylindericalEnvironment(char *input,char *output,TSearchpath *path,char *smode,char *tmode,RtFilterFunc filt,float fwidth,float fheight,int numParams,char **params,void **vals);


#endif




