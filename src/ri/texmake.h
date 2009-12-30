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
//  File				:	texmake.h
//  Classes				:	-
//  Description			:	Texture making functions
//
////////////////////////////////////////////////////////////////////////
#ifndef TEXMAKE_H
#define TEXMAKE_H

#include "common/global.h"
#include "ri_config.h"
#include "ri.h"
#include "options.h"

void	makeTexture(const char *input,const char *output,TSearchpath *path,const char *smode,const char *tmode,RtFilterFunc filt,float fwidth,float fheight,int numParams,const char **params,const void **vals);
void	makeSideEnvironment(const char *input,const char *output,TSearchpath *path,const char *smode,const char *tmode,RtFilterFunc filt,float fwidth,float fheight,int numParams,const char **params,const void **vals,int);
void	makeCubicEnvironment(const char *px,const char *py,const char *pz,const char *nx,const char *ny,const char *nz,const char *output,const char *smode,const char *tmode,TSearchpath *path,RtFilterFunc filt,float fwidth,float fheight,int numParams,const char **params,const void **vals,int);
void	makeSphericalEnvironment(const char *input,const char *output,TSearchpath *path,const char *smode,const char *tmode,RtFilterFunc filt,float fwidth,float fheight,int numParams,const char **params,const void **vals);
void	makeCylindericalEnvironment(const char *input,const char *output,TSearchpath *path,const char *smode,const char *tmode,RtFilterFunc filt,float fwidth,float fheight,int numParams,const char **params,const void **vals);


#endif

