//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright � 1999 - 2003, Okan Arikan
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
//  File				:	texture.h
//  Classes				:	CTexture , CEnvironment
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef TEXTURE_H
#define TEXTURE_H

#include "common/global.h"
#include "common/algebra.h"
#include "common/containers.h"
#include "attributes.h"
#include "fileResource.h"
#include "stats.h"


class	CShadingContext;

///////////////////////////////////////////////////////////////////////
// Class				:	CTextureInfoBase
// Description			:	This class allows textureinfo to get data
// Comments				:
class	CTextureInfoBase : public CFileResource {
public:
						CTextureInfoBase(const char *name) : CFileResource(name) { }
	virtual				~CTextureInfoBase() { }
	
	virtual void		getResolution(float *dest)			= 0;
	virtual char* 		getTextureType()					= 0;
	virtual int 		getNumChannels()					= 0;
	virtual int 		getViewMatrix(float *dest)			= 0;
	virtual int 		getProjectionMatrix(float *dest)	= 0;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CTexture
// Description			:	This class the the base of all texture types
// Comments				:
class	CTexture : public CTextureInfoBase {
public:
						CTexture(const char *name) : CTextureInfoBase(name) {
							stats.numTextures++;
							if (stats.numTextures > stats.numPeakTextures)	stats.numPeakTextures	=	stats.numTextures;
						}

	virtual				~CTexture() {
							stats.numTextures--;
						}

	virtual float		lookupz(float u,float v,float z,const CTextureLookup *lookup,CShadingContext *context)						=	0;
	virtual	void		lookup(float *dest,float u,float v,const CTextureLookup *lookup,CShadingContext *context)					=	0;
	virtual	void		lookup4(float *dest,const float *u,const float *v,const CTextureLookup *lookup,CShadingContext *context)	=	0;
	
	// textureinfo support
	void				getResolution(float *r)		{ r[0] = 0; r[1] = 0; }
	char* 				getTextureType()			{ return "texture"; }
	int 				getNumChannels()			{ return 0; }
	int 				getViewMatrix(float*)		{ return FALSE; }
	int 				getProjectionMatrix(float*)	{ return FALSE; }
};



///////////////////////////////////////////////////////////////////////
// Class				:	CEnvironment
// Description			:	An environment map (also encapsulates shadow maps)
// Comments				:
class	CEnvironment : public CTextureInfoBase {
public:
						CEnvironment(const char *name) : CTextureInfoBase(name) {
							stats.numEnvironments++;
							if (stats.numEnvironments > stats.numPeakEnvironments)	stats.numPeakEnvironments	=	stats.numEnvironments;
						}

	virtual				~CEnvironment() {
							stats.numEnvironments--;
						}

	virtual	void		lookup(float *dest,const float *D0,const float *D1,const float *D2,const float *D3,const CTextureLookup *lookup,CShadingContext *context)	=	0;
	
	// textureinfo support
	void				getResolution(float *r) 	{ r[0] = 0; r[1] = 0; }
	char* 				getTextureType()			{ return "environment"; }
	int 				getNumChannels()			{ return 0; }
	int 				getViewMatrix(float*)		{ return FALSE; }
	int 				getProjectionMatrix(float*)	{ return FALSE; }
};


///////////////////////////////////////////////////////////////////////
// Class				:	CDeepShadowHeader
// Description			:	The deep shadow map header (used internally)
// Comments				:
class	CDeepShadowHeader {
public:
	int					xres,yres;				// The resolution of the file
	int					xTiles,yTiles;			// The number of tiles
	int					tileSize;				// The tile dimensions
	int					tileShift;				// The tile shift
	matrix				toNDC;					// Xform to the normalized device coordinates
};



#endif

