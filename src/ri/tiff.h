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
//  File				:	tiff.h
//  Classes				:
//  Description			:	TIFF related options
//
////////////////////////////////////////////////////////////////////////
#ifndef TIFF_H
#define TIFF_H

// Textureformat
extern const char	*TIFF_TEXTURE;
extern const char	*TIFF_CYLINDER_ENVIRONMENT;
extern const char	*TIFF_CUBIC_ENVIRONMENT;
extern const char	*TIFF_SPHERICAL_ENVIRONMENT;
extern const char	*TIFF_SHADOW;

// Texture wrap mode
const int	TIFF_PERIODIC		=	0;		// Periodic texture
const int	TIFF_CLAMP			=	1;		// Clamp
const int	TIFF_BLACK			=	2;		// To black

// This function computes the number of levels for a particular image
inline int	tiffNumLevels(int w,int h) {
	int	i;

	for (i=0;(w > 2) && (h > 2);i++,w=w>>1,h=h>>1);

	return i+1;
}

#endif

