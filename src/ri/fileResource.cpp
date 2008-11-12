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
//  File				:	fileResource.cpp
//  Classes				:	CFileResource
//  Description			:	Implementation
//
////////////////////////////////////////////////////////////////////////
#include <string.h>

#include "common/global.h"
#include "common/os.h"
#include "fileResource.h"
#include "error.h"


const	char	*filePhotonMap			=	"PhotonMap";
const	char	*fileIrradianceCache	=	"IrradianceCache";
const	char	*fileGatherCache		=	"GatherCache";
const	char	*fileTransparencyShadow	=	"TransparencyShadow";
const	char	*filePointCloud			=	"PointCloud";
const	char	*fileBrickMap			=	"BrickMap";


///////////////////////////////////////////////////////////////////////
// Class				:	CFileResource
// Method				:	CFileResource
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CFileResource::CFileResource(const char *n) {
	name	=	strdup(n);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFileResource
// Method				:	~CFileResource
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CFileResource::~CFileResource() {
	free((void *) name);
}


///////////////////////////////////////////////////////////////////////
// Function				:	ropen
// Description			:	Open a binary file
// Return Value			:	File handle is successful
// Comments				:	-
FILE	*ropen(const char *name,const char *mode,const char *type,int probe) {
	FILE	*f	=	fopen(name,mode);
	int		i;

	if (f == NULL)	{
		if (probe == FALSE)	error(CODE_BADFILE,"Failed to open %s\n",name);
		return NULL;
	}

	if ((mode[0] == 'w') || (mode[1] == 'w')) {
		unsigned int	magic	=	magicNumber;
		int				version[4];

		fwrite(&magic,sizeof(int),1,f);

		version[0]	=	VERSION_RELEASE;
		version[1]	=	VERSION_BETA;
		version[2]	=	VERSION_ALPHA;
		version[3]	=	sizeof(int*);

		fwrite(version,sizeof(int),4,f);

		i	=	(int) strlen(type);
		fwrite(&i,sizeof(int),1,f);
		fwrite(type,sizeof(char),i+1,f);
	} else {
		unsigned int	magic	=	0;
		int				version[4];
		char			*t;

		fread(&magic,1,sizeof(int),f);

		if (magic != magicNumber) {
			if (magic == magicNumberReversed) {
				// This is a pixie file, but wrong endian
				// Always report file wordsize errors
				error(CODE_BADFILE,"File \"%s\" is binary incompatible (generated on a different endian machine)\n",name);
			} else if (probe == FALSE) {
				error(CODE_BADFILE,"File \"%s\" is binary incompatible\n",name);
			}
			fclose(f);
			return NULL;
		}

		fread(version,3,sizeof(int),f);

		if ((version[0] != VERSION_RELEASE) || (version[1] != VERSION_BETA)) {
			// Always report file version errors
			error(CODE_BADFILE,"File \"%s\" is of incompatible version\n",name);
			fclose(f);
			return NULL;
		}
		
		// intentionally read separately for backward compatibility
		fread(version+3,1,sizeof(int),f);
		
		if (version[3] != sizeof(int*)) {
			// Always report file wordsize errors
			error(CODE_BADFILE,"File \"%s\" is binary incompatible (generated on a machine with different word size)\n",name);
			fclose(f);
			return NULL;
		}

		fread(&i,1,sizeof(int),f);
		t	=	(char *) alloca((i+1)*sizeof(char));
		fread(t,i+1,sizeof(char),f);

		if (strcmp(t,type) != 0) {
			if (probe == FALSE)		error(CODE_BADFILE,"File \"%s\" is of unexpected type\n",name);
			fclose(f);
			return NULL;
		}
	}

	return f;
}


///////////////////////////////////////////////////////////////////////
// Function				:	ropen
// Description			:	Open a binary file
// Return Value			:	File handle is successful
// Comments				:	-
FILE	*ropen(const char *name,char *type) {
	FILE			*f	=	fopen(name,"rb");
	int				i;
	unsigned int	magic	=	0;
	int				version[4];

	if (f == NULL)	{
		error(CODE_BADFILE,"Failed to open %s\n",name);
		return NULL;
	}

	fread(&magic,1,sizeof(int),f);

	if (magic != magicNumber) {
		if (magic == magicNumberReversed) {
			error(CODE_BADFILE,"File \"%s\" is binary incompatible (generated on a different endian machine)\n",name);
		} else {
			error(CODE_BADFILE,"File \"%s\" is binary incompatible\n",name);
		}
		fclose(f);
		return NULL;
	}

	fread(version,3,sizeof(int),f);

	if ((version[0] != VERSION_RELEASE) || (version[1] != VERSION_BETA)) {
		error(CODE_BADFILE,"File \"%s\" is of incompatible version\n",name);
		fclose(f);
		return NULL;
	}
	
	// intentionally read separately for backward compatibility
	fread(version+3,1,sizeof(int),f);
	
	if (version[3] != sizeof(int*)) {
		error(CODE_BADFILE,"File \"%s\" is binary incompatible (generated on a machine with different word size)\n",name);
		fclose(f);
		return NULL;
	}

	fread(&i,1,sizeof(int),f);
	fread(type,i+1,sizeof(char),f);

	return f;
}

