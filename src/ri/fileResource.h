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

const	unsigned	int	magicNumber	=	123456789;

///////////////////////////////////////////////////////////////////////
// Class				:	CFileResource
// Description			:	Any class that is read or written to a file must derive from this class
// Comments				:
// Date last edited		:	7/4/2001
class	CFileResource {
public:
					CFileResource(const char *);
	virtual			~CFileResource();

	const	char	*name;
};


FILE	*ropen(const char *,const char *,const char *,int probe=0);
FILE	*ropen(const char *,char *);

#endif

