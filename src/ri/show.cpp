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
//  Description			:	The hardware visualizer
//
////////////////////////////////////////////////////////////////////////
#include "show.h"
#include "cache.h"
#include "renderer.h"
#include "error.h"
#include "fileResource.h"
#include "photonMap.h"
#include "texture3d.h"
#include "gui/opengl.h"


// The static members of the CView class that visualizable classes derive from
void					*CView::handle			=	NULL;
TGlTrianglesFunction	CView::drawTriangles	=	NULL;
TGlPointsFunction		CView::drawPoints		=	NULL;
int						CView::detailLevel		=	2;

///////////////////////////////////////////////////////////////////////
// Class				:	CShow
// Method				:	CShow
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	9/21/2006
CShow::CShow(COptions *o,CXform *x,SOCKET s) : CShadingContext(o,x,s,HIDER_NODISPLAY) {
	char		moduleFile[OS_MAX_PATH_LENGTH];

	// First, try to load the dynamic library
	CView::handle	=	NULL;
	if(currentRenderer->locateFileEx(moduleFile,"gui",osModuleExtension,modulePath)) {
		CView::handle		=	osLoadModule(moduleFile);
	}

	if (CView::handle != NULL) {

		// Is this the library we were expecting ?
		TGlVisualizeFunction	visualize	=	(TGlVisualizeFunction) osResolve(CView::handle,"pglVisualize");
		CView					*view		=	NULL;

		if (visualize != NULL) {

			// Try to load the file
			const char	*fileName	=	hider + 5;
			FILE		*in			=	fopen(fileName,"rb");

			CView::drawTriangles	=	(TGlTrianglesFunction)	osResolve(CView::handle,"pglTriangles");
			CView::drawPoints		=	(TGlPointsFunction)		osResolve(CView::handle,"pglPoints");

			assert(CView::drawTriangles != NULL);
			assert(CView::drawPoints != NULL);

			if (in != NULL)	{
				unsigned int	magic	=	0;
				int				version[3],i;
				char			*t;

				fread(&magic,1,sizeof(int),in);

				if (magic == magicNumber) {
					fread(version,3,sizeof(int),in);

					if (!((version[0] == VERSION_RELEASE) || (version[1] == VERSION_BETA))) {
						error(CODE_VERSION,"File %s is from an incompatible version\n",fileName);
					} else {
						fread(&i,1,sizeof(int),in);
						t	=	(char *) alloca((i+1)*sizeof(char));
						fread(t,i+1,sizeof(char),in);

						info(CODE_PRINTF,"File:    %s\n",fileName);
						info(CODE_PRINTF,"Version: %d.%d.%d\n",version[0],version[1],version[2]);
						info(CODE_PRINTF,"Type:    %s\n",t);
						fclose(in);

						if (strcmp(t,filePhotonMap) == 0) {
							view	=	getPhotonMap(fileName);
						} else if (strcmp(t,fileIrradianceCache) == 0) {
							view	=	getCache(fileName,"R");
						} else if (strcmp(t,fileGatherCache) == 0) {
							view	=	getCache(fileName,"R");
						} else if (strcmp(t,filePointCloud) == 0) {
							view	=	getTexture3d(fileName,FALSE,NULL,NULL);
						} else if (strcmp(t,fileBrickMap) == 0) {
							view	=	getTexture3d(fileName,FALSE,NULL,NULL);
						}

						// Create / display the window
						if (view != NULL)	visualize(view);
					}
				} else {
					error(CODE_BADFILE,"File %s doesn't seem to be a Pixie file\n",fileName);
				}
			}
		}
	} else {
		error(CODE_SYSTEM,"Opengl wrapper not found...");
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
