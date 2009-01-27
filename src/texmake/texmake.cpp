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
//  File				:	texmake.cpp
//  Classes				:	-
//  Description			:	Texture making program
//
////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/global.h"
#include "common/os.h"
#include "ri/ri.h"

const	char	*tileSizeArgument			=	"-tilesize";
const	char	*resizeModeArgument			=	"-resize";
const	char	*smodeArgument				=	"-smode";
const	char	*tmodeArgument				=	"-tmode";
const	char	*filterArgument				=	"-filter";
const	char	*filterWidthArgument		=	"-filterwidth";
const	char	*sfilterWidthArgument		=	"-sfilterwidth";
const	char	*tfilterWidthArgument		=	"-tfilterwidth";
const	char	*inputPathArgument			=	"-input";
const	char	*outputPathArgument			=	"-output";
const	char	*shadowArgument				=	"-shadow";
const	char	*envlatArgument				=	"-envlatl";
const	char	*envcubeArgument			=	"-envcube";
const	char	*fovArgument				=	"-fov";
const	char	*texture3dArgument			=	"-texture3d";
const	char	*maxerrorArgument			=	"-maxerror";
const	char	*radiusscaleArgument		=	"-radiusscale";
const	char	*maxdepthArgument			=	"-maxdepth";

void	printUsage() {
	printf("Usage: texmake [-(shadow|envlatl|envcube)] [-resize <mode>] [-smode <mode>] [-tmode <mode>] [-filter <filter>] [-filterwidth <width>] [-filterheight <height>] [-sfilterwidth <width>] [-tfilterwidth <width>] <inputfile> <outputfile>\n");
	printf("       texmake -texture3d [-maxerror <number>] [-radiusscale <number>] [-maxdepth <number>] <inputfile> <outputfile>\n");
}

int main(int argc, char* argv[]) {
	int				tileSize		=	32;
	const char		*resizeMode		=	"up";
	const char		*smode			=	"periodic";
	const char		*tmode			=	"periodic";
	float			filterWidth		=	3;
	float			filterHeight	=	3;
	const char		*inPath			=	".";
	const char		*outPath		=	".";
	float			fov				=	90;
	RtFilterFunc	filter			=	RiCatmullRomFilter;
	float			maxerror		=	0.002f;
	float			radiusScale		=	1.0f;
	int				maxDepth		=	10;
	int				i;
	const char		*textureMode	=	"texture";
	int				processed;

	RtToken			tokens[50];
	RtPointer		vals[50];
	const char		*files[50];
	int				currentFile			=	0;
	int				currentParameter	=	0;

	if (argc == 1) {
		printUsage();
		return 0;
	}

	for (i=1;i<argc;i++) {
		if (strcmp(argv[i],"--help") == 0) {
			printUsage();
		} else if (strcmp(argv[i],shadowArgument) == 0) {
			textureMode	=	"shadow";
		} else if (strcmp(argv[i],envlatArgument) == 0) {
			textureMode	=	"envlat";
		} else if (strcmp(argv[i],envcubeArgument) == 0) {
			textureMode	=	"envcube";
		} else if (strcmp(argv[i],texture3dArgument) == 0) {
			textureMode	=	"texture3d";
		} else if (strcmp(argv[i],tileSizeArgument) == 0) {
			i++;
			tileSize	=	atoi(argv[i]);
		} else if (strcmp(argv[i],resizeModeArgument) == 0) {
			i++;
			resizeMode	=	argv[i];
		} else if (strcmp(argv[i],smodeArgument) == 0) {
			i++;
			smode		=	argv[i];
		} else if (strcmp(argv[i],tmodeArgument) == 0) {
			i++;
			tmode		=	argv[i];
		} else if (strcmp(argv[i],filterArgument) == 0) {
			i++;
			if (strcmp(argv[i],"box") == 0) {
				filter	=	RiBoxFilter;
			} else if (strcmp(argv[i],"triangle") == 0) {
				filter	=	RiTriangleFilter;
			} else if (strcmp(argv[i],"gaussian") == 0) {
				filter	=	RiGaussianFilter;
			} else if (strcmp(argv[i],"catmull-rom") == 0) {
				filter	=	RiCatmullRomFilter;
			} else if (strcmp(argv[i],"sinc") == 0) {
				filter	=	RiSincFilter;
			} else {
				fprintf(stderr,"Unknown filter: %s\n",argv[i]);
			}
		} else if (strcmp(argv[i],filterWidthArgument) == 0) {
			i++;
			filterWidth		=	(float) atof(argv[i]);
			filterHeight	=	(float) atof(argv[i]);
		} else if (strcmp(argv[i],sfilterWidthArgument) == 0) {
			i++;
			filterWidth	=	(float) atof(argv[i]);
		} else if (strcmp(argv[i],tfilterWidthArgument) == 0) {
			i++;
			filterHeight	=	(float) atof(argv[i]);
		} else if (strcmp(argv[i],fovArgument) == 0) {
			i++;
			fov	=	(float) atof(argv[i]);
		} else if (strcmp(argv[i],maxerrorArgument) == 0) {
			i++;
			maxerror		=	(float) atof(argv[i]);
		} else if (strcmp(argv[i],radiusscaleArgument) == 0) {
			i++;
			radiusScale		=	(float) atof(argv[i]);
		} else if (strcmp(argv[i],maxdepthArgument) == 0) {
			i++;
			maxDepth		=	(int) atoi(argv[i]);
		} else if (strcmp(argv[i],inputPathArgument) == 0) {
			i++;
			inPath		=	argv[i];
		} else if (strcmp(argv[i],outputPathArgument) == 0) {
			i++;
			outPath		=	argv[i];
		} else {
			files[currentFile++]	=	argv[i];
		}
	}

	processed	=	FALSE;

	if (strcmp(textureMode,"texture") == 0) {
		if (currentFile == 2) {
			RiBegin(RI_NULL);
			tokens[currentParameter]	=	"resize";
			vals[currentParameter++]	=	(RtPointer) &resizeMode;
			RiMakeTextureV(files[0],files[1],smode,tmode,filter,filterWidth,filterHeight,currentParameter,tokens,vals);
			RiEnd();

			processed	=	TRUE;
		}
	} else if (strcmp(textureMode,"shadow") == 0) {
		if (currentFile == 2) {
			RiBegin(RI_NULL);
			tokens[currentParameter]	=	"resize";
			vals[currentParameter++]	=	(RtPointer) &resizeMode;
			RiMakeShadowV(files[0],files[1],currentParameter,tokens,vals);
			RiEnd();

			processed	=	TRUE;
		}
	} else if (strcmp(textureMode,"envlat") == 0) {
		if (currentFile == 2) {
			RiBegin(RI_NULL);
			tokens[currentParameter]	=	"resize";
			vals[currentParameter++]	=	(RtPointer) &resizeMode;
			RiMakeLatLongEnvironmentV(files[0],files[1],filter,filterWidth,filterHeight,currentParameter,tokens,vals);
			RiEnd();

			processed	=	TRUE;
		}
	} else if (strcmp(textureMode,"envcube") == 0) {
		if (currentFile == 7) {
			RiBegin(RI_NULL);
			tokens[currentParameter]	=	"resize";
			vals[currentParameter++]	=	&resizeMode;
			RiMakeCubeFaceEnvironmentV(files[0],files[1],files[2],files[3],files[4],files[5],files[6],fov,filter,filterWidth,filterHeight,currentParameter,tokens,vals);
			RiEnd();

			processed	=	TRUE;
		}
	} else if (strcmp(textureMode,"texture3d") == 0) {
		if (currentFile == 2) {
			RiBegin(RI_NULL);
			tokens[currentParameter]			=	RI_MAXERROR;
			vals[currentParameter++]			= 	(RtPointer) &maxerror;
			tokens[currentParameter]			=	"radiusscale";
			vals[currentParameter++]			= 	(RtPointer) &radiusScale;
			tokens[currentParameter]			=	"maxdepth";
			vals[currentParameter++]			= 	(RtPointer) &maxDepth;
			RiMakeBrickMapV(1,&files[0],files[1],currentParameter,tokens,vals);
			RiEnd();

			processed	=	TRUE;
		}
	}

	if (processed == FALSE) {
		fprintf(stderr,"Unknown texture mode (\"%s\") or invalid number of arguments (%d)\n",textureMode,currentFile);
	}

	return 0;
}

