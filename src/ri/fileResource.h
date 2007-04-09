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
//  File				:	fileResource.h
//  Classes				:	CFileResource
//  Description			:	Any class that reads from a file must be derived from this class
//
////////////////////////////////////////////////////////////////////////
#ifndef FILERESOURCE_H
#define FILERESOURCE_H

#include <stdio.h>

#include "common/global.h"		// The global header file

// Come textual definitions for various binary files
extern	const	char	*filePhotonMap;
extern	const	char	*fileIrradianceCache;
extern	const	char	*fileGatherCache;
extern	const	char	*fileTransparencyShadow;
extern	const	char	*filePointCloud;
extern	const	char	*fileBrickMap;

const	unsigned	int	magicNumber			=	123456789;
const	unsigned	int	magicNumberReversed	=	((magicNumber & 0xFF000000) >> 24) |
												((magicNumber & 0xFF0000) >> 8) |
												((magicNumber & 0xFF00) << 8) |
												((magicNumber & 0xFF) << 24);

///////////////////////////////////////////////////////////////////////
// Class				:	CFileResource
// Description			:	Any class that is read or written to a file must derive from this class
// Comments				:
class	CFileResource {
public:
					CFileResource(const char *);
	virtual			~CFileResource();

	const	char	*name;
};


FILE	*ropen(const char *,const char *,const char *,int probe=FALSE);
FILE	*ropen(const char *,char *);

#endif

