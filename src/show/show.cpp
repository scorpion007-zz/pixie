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
//  File				:	show.cpp
//  Classes				:	-
//  Description			:	The main show file
//
////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <tiffio.h>
#include <tiff.h>

#include "common/global.h"
#include "interface.h"
#include "photonView.h"
#include "pointCloudView.h"
#include "brickmapView.h"
#include "cacheView.h"
#include "radView.h"
#include "meshView.h"
#include "imageView.h"



const	unsigned	int	magicNumber	=	123456789;



///////////////////////////////////////////////////////////////////////
// function				:	tiffErrorHandler
// Description			:	Handle errors coming from the libtiff
// Return Value			:	-
// Comments				:
// Date last edited		:	8/10/2001
static	void	tiffErrorHandler(const char *module,const char *fmt,va_list ap) {
}






int	main(int argc,char *argv[]) {

	// Init the memory manager
	memInit();

	if (argc == 1) {
		fprintf(stdout,"Usage: show <options> <file_name>[,mode]\n");
	} else {
		CInterface	*window	=	NULL;
		FILE		*in;
		int			i;
		TIFF		*tin;

		// First, try to open this as a TIFF file
		TIFFSetErrorHandler(tiffErrorHandler);
		TIFFSetWarningHandler(tiffErrorHandler);

		tin		=	TIFFOpen(argv[argc-1],"r");

		if (tin != NULL) {
			window	=	new CImageView(tin);
		} else {
			in		=	fopen(argv[argc-1],"rb");

			if (in != NULL)	{
				unsigned int	magic	=	0;
				int				version[3];
				char			*t;

				fread(&magic,1,sizeof(int),in);

				if (magic == magicNumber) {
					fread(version,3,sizeof(int),in);

					if (!((version[0] == VERSION_RELEASE) || (version[1] == VERSION_BETA))) {
						printf("File %s is from an incompatible version\n",argv[argc-1]);
						printf("Attempting to open %s\n",argv[argc-1]);
					}

					fread(&i,1,sizeof(int),in);
					t	=	(char *) alloca((i+1)*sizeof(char));
					fread(t,i+1,sizeof(char),in);

					printf("File:    %s\n",argv[argc-1]);
					printf("Version: %d.%d.%d\n",version[0],version[1],version[2]);
					printf("Type:    %s\n",t);

					if (strcmp(t,"PhotonMap") == 0) {
						window	=	new CPhotonView(in);
					} else if (strcmp(t,"IrradianceCache") == 0) {
						window	=	new CCacheView(in);
					} else if (strcmp(t,"GatherCache") == 0) {
						window	=	new CRadView(in);
					} else if (strcmp(t,"PointCloud") == 0) {
						window	=	new CPointCloudView(in);
					} else if (strcmp(t,"BrickMap") == 0) {
						int fast = FALSE;
						int level = -1;
						
						for(int i = 1; i < argc-1; i++) {
							if(!strcmp(argv[i],"-fast")) {
								fast = true;
							} else if(!strcmp(argv[i],"-level")) {
								level = atoi(argv[i+1]);
							}
						}
						
						window	=	new CBrickMapView(in,fast,level);
					} else {
						window	=	NULL;
					}

				} else {
					printf("File %s doesn't seem to be a Pixie file\n",argv[argc-1]);
				}
			}
		}


		if (window == NULL) {
			in	=	fopen(argv[argc-1],"r");

			if (in != NULL) {
				window	=	new CMeshView(in);

				fclose(in);
			}
		}

		if (window != NULL) {
			Fl::run();

			delete window;
		}
	}

	// Shutdown the memory manager
	memShutdown();

	return	0;
}




