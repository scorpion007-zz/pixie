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
//  File				:	defaults.h
//  Classes				:
//  Description			:	This file contains compile time specific defaults
//
////////////////////////////////////////////////////////////////////////
#ifndef DEFAULTS_H
#define DEFAULTS_H

// The default tile size for textures
#define	DEFAULT_TILE_SIZE		32

// The default ray differential for photon/irradiance cache
#define DEFAULT_RAY_DA			0.5f
#define	DEFAULT_RAY_DB			0

// Some default options
#define	DEFAULT_TILE_WIDTH		32
#define	DEFAULT_TILE_HEIGHT		32
#define	DEFAULT_NET_XBUCKETS	5
#define	DEFAULT_NET_YBUCKETS	5
#define	DEFAULT_TSM_THRESHOLD	(float ) 0.1
#define	DEFAULT_MAX_GRIDSIZE	16*16
#define DEFAULT_NUM_THREADS		2
#define DEFAULT_MAX_TEXTURESIZE	20000000
#define DEFAULT_MAX_BRICKSIZE	10000000
#define DEFAULT_THREAD_STRIDE	3
#define	DEFAULT_GEO_CACHE_SIZE	30720*1024

#endif

