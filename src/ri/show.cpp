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
//  File				:	show.cpp
//  Classes				:	-
//  Description			:	The hardware visualizer
//
////////////////////////////////////////////////////////////////////////
#include "show.h"
#include "error.h"
#include "fileResource.h"
#include "photonMap.h"
#include "texture3d.h"
#include "gui/opengl.h"
#include "renderer.h"
#include "debug.h"


// The static members of the CView class that visualizable classes derive from
void					*CView::handle			=	NULL;
TGlTrianglesFunction	CView::drawTriangles	=	NULL;
TGlLinesFunction		CView::drawLines		=	NULL;
TGlPointsFunction		CView::drawPoints		=	NULL;
TGlDisksFunction		CView::drawDisks		=	NULL;
TGlFileFunction			CView::drawFile			=	NULL;

///////////////////////////////////////////////////////////////////////
// Class				:	CShow
// Method				:	CShow
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CShow::CShow(int thread) : CShadingContext(thread) {

	if (thread == 0) {
		char		moduleFile[OS_MAX_PATH_LENGTH];

		// First, try to load the dynamic library
		CView::handle	=	NULL;
		if(CRenderer::locateFileEx(moduleFile,"gui",osModuleExtension,CRenderer::modulePath)) {
			CView::handle		=	osLoadModule(moduleFile);
		}

		if (CView::handle != NULL) {

			// Is this the library we were expecting ?
			TGlVisualizeFunction	visualize	=	(TGlVisualizeFunction) osResolve(CView::handle,"pglVisualize");
			CView					*view		=	NULL;

			if (visualize != NULL) {

				// Try to load the file
				const char	*fileName	=	CRenderer::hider + 5;
				FILE		*in			=	fopen(fileName,"rb");

				CView::drawTriangles	=	(TGlTrianglesFunction)	osResolve(CView::handle,"pglTriangles");
				CView::drawLines		=	(TGlLinesFunction)		osResolve(CView::handle,"pglLines");
				CView::drawPoints		=	(TGlPointsFunction)		osResolve(CView::handle,"pglPoints");
				CView::drawDisks		=	(TGlDisksFunction)		osResolve(CView::handle,"pglDisks");
				CView::drawFile			=	(TGlFileFunction)		osResolve(CView::handle,"pglFile");

				assert(CView::drawTriangles != NULL);
				assert(CView::drawPoints != NULL);

				if (in != NULL)	{
					unsigned int	magic	=	0;
					int				version[4],i;
					char			*t;

					fread(&magic,sizeof(int),1,in);

					if (magic == magicNumber) {
						fread(version,sizeof(int),4,in);

						if (!((version[0] == VERSION_RELEASE) || (version[1] == VERSION_BETA))) {
							error(CODE_VERSION,"File \"%s\" is from an incompatible version\n",fileName);
						} else {
							if (version[3] != sizeof(int*) ) {
								error(CODE_VERSION,"File \"%s\" is binary an incompatible (generated on a machine with different word size)\n",fileName);
							} else {
								
								fread(&i,sizeof(int),1,in);
								t	=	(char *) alloca((i+1)*sizeof(char));
								fread(t,sizeof(char),i+1,in);
	
								info(CODE_PRINTF,"File:    %s\n",fileName);
								info(CODE_PRINTF,"Version: %d.%d.%d\n",version[0],version[1],version[2]);
								info(CODE_PRINTF,"Type:    %s\n",t);
								fclose(in);

								matrix	from,to;

								identitym(from);
								identitym(to);
	
								if (strcmp(t,filePhotonMap) == 0) {
									view	=	CRenderer::getPhotonMap(fileName);
								} else if (strcmp(t,fileIrradianceCache) == 0) {
									view	=	CRenderer::getCache(fileName,"R",from,to);
								} else if (strcmp(t,fileGatherCache) == 0) {
									view	=	CRenderer::getCache(fileName,"R",from,to);
								} else if (strcmp(t,filePointCloud) == 0) {
									view	=	CRenderer::getTexture3d(fileName,FALSE,NULL,from,to);
								} else if (strcmp(t,fileBrickMap) == 0) {
									view	=	CRenderer::getTexture3d(fileName,FALSE,NULL,from,to);
								}
	
								// Create / display the window
								if (view != NULL)	visualize(view);
							}
						}
					} else {
						fseek(in,0,SEEK_SET);
						view	=	new CDebugView(in,fileName);

						visualize(view);

						delete view;
					}
				}
			}
		} else {
			error(CODE_SYSTEM,"Opengl wrapper not found...");
		}
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CShow
// Method				:	~CShow
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CShow::~CShow() {
}

///////////////////////////////////////////////////////////////////////
// Class                :   CShow
// Method               :   preDisplaySetup
// Description          :   allow the hider to affect display setup
// Return Value         :   -
// Comments             :
void CShow::preDisplaySetup() {
	CRenderer::hiderFlags	|=	HIDER_NODISPLAY;
}

