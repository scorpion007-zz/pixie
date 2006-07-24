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
#include "random.h"

// Texture wrapping mode
typedef enum {
	TEXTURE_PERIODIC,
	TEXTURE_BLACK,
	TEXTURE_CLAMP
} TTextureMode;


///////////////////////////////////////////////////////////////////////
// Class				:	CTextureInfoBase
// Description			:	This class allows textureinfo to get data
// Comments				:
// Date last edited		:	02/22/2006
class	CTextureInfoBase : public CFileResource {
public:
						CTextureInfoBase(const char *n) : CFileResource(n) { }
	virtual				~CTextureInfoBase() { }
	
	virtual void		getResolution(float*)		= 0;
	virtual char* 		getTextureType()			= 0;
	virtual int 		getNumChannels()			= 0;
	virtual int 		getViewMatrix(float*)		= 0;
	virtual int 		getProjectionMatrix(float*)	= 0;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CTexture
// Description			:	This class the the base of all texture types
// Comments				:
// Date last edited		:	9/24/2002
class	CTexture : public CTextureInfoBase {
public:

						CTexture(const char *,int,int,TTextureMode,TTextureMode);
	virtual				~CTexture();

	virtual float		lookupz(float,float,float,const CTextureLookup *);						// Depth access
	virtual	void		lookup(float *,float,float,const CTextureLookup *);						// Point access
	virtual	void		lookup4(float *,const float *,const	float *,const CTextureLookup *);	// Area access
	
	// textureinfo support
	void				getResolution(float *r) 	{ r[0] = (float) width; r[1] = (float) height; }
	char* 				getTextureType()			{ return "texture"; }
	int 				getNumChannels()			{ return 0; }
	int 				getViewMatrix(float*)		{ return FALSE; }
	int 				getProjectionMatrix(float*)	{ return FALSE; }

	int					width,height;											// The dimensions of the texture (just ised to figure out the blur amount)
	TTextureMode		sMode,tMode;											// The texture wrapping mode

	static void			textureInit(int);										// This function MUST be called before any texture is loaded
	static void			textureShutdown();										// This function MUST be called before termination
};



///////////////////////////////////////////////////////////////////////
// Class				:	CEnvironment
// Description			:	An environment map (also encapsulates shadow maps)
// Comments				:
// Date last edited		:	9/24/2002
class	CEnvironment : public CTextureInfoBase {
public:

						CEnvironment(const char *);
	virtual				~CEnvironment();

	virtual	void		lookup(float *,const float *,const float *,const float *,const float *,const CTextureLookup *);
	
	// textureinfo support
	void				getResolution(float *r) 	{ r[0] = 0; r[1] = 0; }
	char* 				getTextureType()			{ return "environment"; }
	int 				getNumChannels()			{ return 0; }
	int 				getViewMatrix(float*)		{ return FALSE; }
	int 				getProjectionMatrix(float*)	{ return FALSE; }
};


///////////////////////////////////////////////////////////////////////
// Class				:	CDeepShadowHeader
// Description			:	The deep shadow map header
// Comments				:
// Date last edited		:	2/28/2002
class	CDeepShadowHeader {
public:
	int					xres,yres;				// The resolution of the file
	int					xTiles,yTiles;			// The number of tiles
	int					tileSize;				// The tile dimensions
	int					tileShift;				// The tile shift
	matrix				toNDC;
};


#endif

