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
//  File				:	opengl.cpp
//  Classes				:	-
//  Description			:	The opengl hider
//
////////////////////////////////////////////////////////////////////////
#include "opengl.h"
#include "renderer.h"
#include "error.h"
#include "fileResource.h"
#include "photonMap.h"



///////////////////////////////////////////////////////////////////////
// Class				:	CShow
// Method				:	CShow
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	9/21/2006
CShow::CShow(COptions *o,CXform *x,SOCKET s) : CShadingContext(o,x,s,HIDER_NODISPLAY) {
	const char	*fileName = hider + 5;

#ifdef WIN32
	void	*handle	=	osLoadModule("opengl.dll");
#else
	void	*handle	=	osLoadModule("opengl.so");
#endif

	if (handle != NULL) {
		TGlVisualizeFunction	visualize	=	(TGlVisualizeFunction) osResolve(handle,"pglVisualize");
		CView					*view		=	NULL;

		if (visualize != NULL) {
			FILE *in		=	fopen(fileName,"rb");

			if (in != NULL)	{
				unsigned int	magic	=	0;
				int				version[3],i;
				char			*t;

				fread(&magic,1,sizeof(int),in);

				if (magic == magicNumber) {
					fread(version,3,sizeof(int),in);

					if (!((version[0] == VERSION_RELEASE) || (version[1] == VERSION_BETA))) {
						printf("File %s is from an incompatible version\n",fileName);
						printf("Attempting to open %s\n",fileName);
					}

					fread(&i,1,sizeof(int),in);
					t	=	(char *) alloca((i+1)*sizeof(char));
					fread(t,i+1,sizeof(char),in);

					printf("File:    %s\n",fileName);
					printf("Version: %d.%d.%d\n",version[0],version[1],version[2]);
					printf("Type:    %s\n",t);
					fclose(in);

					if (strcmp(t,"PhotonMap") == 0) {
						view	=	getPhotonMap(fileName);
					} else if (strcmp(t,"IrradianceCache") == 0) {

					} else if (strcmp(t,"GatherCache") == 0) {

					} else if (strcmp(t,"PointCloud") == 0) {
						
					} else if (strcmp(t,"BrickMap") == 0) {
						
					}

					if (view != NULL)	visualize(view);

				} else {
					printf("File %s doesn't seem to be a Pixie file\n",fileName);
				}
			}
		}
	} else {
		error(CODE_BADFILE,"Opengl wrapper not found...");
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CShow
// Method				:	~CShow
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	9/21/2006
CShow::~CShow() {
}