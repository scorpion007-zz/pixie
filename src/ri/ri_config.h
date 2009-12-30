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
//  File				:	ri_config.h
//  Classes				:
//  Description			:	This file contains the libri config settings
//
////////////////////////////////////////////////////////////////////////
#ifndef CONFIG_H
#define CONFIG_H

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
#define	DEFAULT_TSM_THRESHOLD	0.1f
#define	DEFAULT_MAX_GRIDSIZE	16*16
#define DEFAULT_NUM_THREADS		2
#define DEFAULT_MAX_TEXTURESIZE	20000000
#define DEFAULT_MAX_BRICKSIZE	10000000
#define DEFAULT_THREAD_STRIDE	3
#define	DEFAULT_GEO_CACHE_SIZE	30720*1024

// The default network port
#define	DEFAULT_SERVER_PORT		24914

// Per block or global locking for textures
// Per block is faster, but requires (fractionally) more memory
#define	TEXTURE_PERBLOCK_LOCK

// Per entry or global locking for tesselations
// Per entry is faster, but requires (fractionally) more memory
#define TESSELATION_PERENTRY_LOCK

// The number of levels before we split
#define TESSELATION_NUM_LEVELS			3

// The size of the buffer to be used during the network file transfers
#define	NETWORK_BUFFER_LENGTH			(1 << 12)

//	The maximum allowed string size that can be handled
#define	MAX_SCRIPT_STRING_SIZE			256

//	The initial zone size
#define	ZONE_INIT_SIZE					500000

//	The default page size for the zone
#define ZONE_BASE_SIZE					1000000

//	If we have threashing in the zone memory, we gradually increase the page size by this amount
#define ZONE_INCREMENT_SIZE				100000

// The maximum length of the variable name
#define VARIABLE_NAME_LENGTH			64

// The size of the hash that maps object pointers
#define	SHADING_OBJECT_CACHE_SIZE		512

// The number of items below which we allocate memory from stack
#define	ALLOCA_MAX_ITEMS				200

// The hash size for the shader parameter lists
#define	PL_HASH_SIZE					512

// The stack size for the point hierarchy lookup
#define	POINTHIERARCHY_STACK_SIZE		256

// The maximum number of channels in a 3d texture
#define	TEXTURE3D_MAX_CHANNELS			32

// The number of samples to take for filtered step
#define	FILTERSTEP_SAMPLES				100

// The initial size of the raytracing heap
#define TRACE_HEAP_SIZE					100

// The number of bins to use for filterstep function
#define	FILTERSTEP_NUMSTEPS				10

// If this flag is set, we ignore the displacement shaders for dicing
#define	IGNORE_DISPLACEMENTS_FOR_DICING

// We are compiling the renderer. This define switches the dllimport/dllexport settings on Windoze
#define RENDERER

#endif

