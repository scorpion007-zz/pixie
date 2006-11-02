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
//  File				:	tiff.h
//  Classes				:
//  Description			:	TIFF related options
//
////////////////////////////////////////////////////////////////////////
#ifndef TIFF_H
#define TIFF_H

// Textureformat
const char	*TIFF_TEXTURE					=	"Pixie Texture";
const char	*TIFF_CYLINDER_ENVIRONMENT		=	"Pixie Environment (cylinder)";
const char	*TIFF_CUBIC_ENVIRONMENT			=	"Pixie Environment (cubic)";
const char	*TIFF_SPHERICAL_ENVIRONMENT		=	"Pixie Environment (spherical)";
const char	*TIFF_SHADOW					=	"Pixie shadow";

// Texture wrap mode
const int	TIFF_PERIODIC		=	0;		// Periodic texture
const int	TIFF_CLAMP			=	1;		// Clamp
const int	TIFF_BLACK			=	2;		// To black

#endif
