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
//  File				:	options.cpp
//  Classes				:	COptions
//  Description			:	Implementation
//
////////////////////////////////////////////////////////////////////////
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "options.h"
#include "texture.h"
#include "stats.h"
#include "defaults.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifndef PIXIE_MODELS
#define PIXIE_MODELS "%PIXIEHOME%/models"
#endif

#ifndef PIXIE_PROCEDURALS
#define PIXIE_PROCEDURALS "%PIXIE_PROCEDURALS%"
#endif

#ifndef PIXIE_TEXTURES
#define PIXIE_TEXTURES "%PIXIEHOME%/textures"
#endif

#ifndef PIXIE_SHADERS
#define PIXIE_SHADERS "%PIXIEHOME%/shaders"
#endif

#ifndef PIXIE_DISPLAYS
#define PIXIE_DISPLAYS "%PIXIE_DISPLAY%"
#endif

#ifndef PIXIE_MODULES
#define PIXIE_MODULES "%PIXIE_MODULES%"
#endif

///////////////////////////////////////////////////////////////////////
// Class				:	COptions
// Method				:	optionsDeleteSearchPath
// Description			:	Delete the searchpath
// Return Value			:	-
// Comments				:
static	void		optionsDeleteSearchPath(TSearchpath *cPath) {
	TSearchpath	*nPath;

	for(;cPath!=NULL;) {
		nPath	=	cPath->next;
		free(cPath->directory);
		delete cPath;
		cPath	=	nPath;
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	COptions
// Method				:	optionsCloneSearchPath
// Description			:	Clone a search path
// Return Value			:	-
// Comments				:
static	TSearchpath	*optionsCloneSearchPath(TSearchpath *cPath) {
	TSearchpath	*nPath	=	NULL;
	TSearchpath	*lPath	=	NULL;

	for(;cPath!=NULL;cPath=cPath->next) {
		TSearchpath	*ncPath	=	new TSearchpath;

		ncPath->directory	=	strdup(cPath->directory);
		ncPath->next		=	NULL;

		if (lPath == NULL) {
			lPath			=	ncPath;
			nPath			=	ncPath;
		} else {
			lPath->next		=	ncPath;
			lPath			=	ncPath;
		}
	}

	return nPath;
}


///////////////////////////////////////////////////////////////////////
// Class				:	COptions::CDisplay
// Method				:	CDisplay
// Description			:	Ctor
// Return Value			:	-
// Comments				:
COptions::CDisplay::CDisplay() {
	outDevice		=	NULL;
	outName			=	NULL;
	outSamples		=	NULL;
	next			=	NULL;

	quantizer[0]	=	-1;	// Copy from the default

	numParameters	=	0;
	parameters		=	NULL;
}

///////////////////////////////////////////////////////////////////////
// Class				:	COptions::CDisplay
// Method				:	CDisplay
// Description			:	Ctor
// Return Value			:	-
// Comments				:
COptions::CDisplay::CDisplay(const CDisplay *other) {

	outDevice		=	strdup(other->outDevice);
	outName			=	strdup(other->outName);
	outSamples		=	strdup(other->outSamples);
	quantizer[0]	=	other->quantizer[0];
	quantizer[1]	=	other->quantizer[1];
	quantizer[2]	=	other->quantizer[2];
	quantizer[3]	=	other->quantizer[3];
	quantizer[4]	=	other->quantizer[4];

	if (other->numParameters > 0) {
		int	i;

		numParameters	=	other->numParameters;
		parameters		=	new TDisplayParameter[numParameters];

		// Duplicate the parameters
		for (i=0;i<numParameters;i++) {
			parameters[i]		=	other->parameters[i];
			parameters[i].name	=	strdup(other->parameters[i].name);
			switch(parameters[i].type) {
			case FLOAT_PARAMETER:
				parameters[i].data		=	new	float[parameters[i].numItems];
				memcpy(parameters[i].data,other->parameters[i].data,parameters[i].numItems*sizeof(float));
				break;
			case VECTOR_PARAMETER:
				parameters[i].data		=	new	float[parameters[i].numItems*3];
				memcpy(parameters[i].data,other->parameters[i].data,parameters[i].numItems*sizeof(float)*3);
				break;
			case MATRIX_PARAMETER:
				parameters[i].data		=	new	float[parameters[i].numItems*16];
				memcpy(parameters[i].data,other->parameters[i].data,parameters[i].numItems*sizeof(float)*16);
				break;
			case STRING_PARAMETER:
				char	*str;

				str						=	strdup((char *) other->parameters[i].data);
				parameters[i].data		=	str;
				break;
			case INTEGER_PARAMETER:
				parameters[i].data		=	new	int[parameters[i].numItems];
				memcpy(parameters[i].data,other->parameters[i].data,parameters[i].numItems*sizeof(int));
				break;
			default:
				break;
			}
		}
	} else {
		numParameters	=	0;
		parameters		=	NULL;
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	COptions::CDisplay
// Method				:	~CDisplay
// Description			:	Dtor
// Return Value			:	-
// Comments				:
COptions::CDisplay::~CDisplay() {
	if (outDevice	!= NULL)	free(outDevice);
	if (outName		!= NULL)	free(outName);
	if (outSamples  != NULL)	free(outSamples);

	if (parameters != NULL) {
		int	i;

		for (i=0;i<numParameters;i++) {
			switch(parameters[i].type) {
			case FLOAT_PARAMETER:
			case VECTOR_PARAMETER:
			case MATRIX_PARAMETER:
				delete [] (float *) parameters[i].data;
				break;
			case STRING_PARAMETER:
				free((char *) parameters[i].data);
				break;
			}

			free(parameters[i].name);
		}

		delete [] parameters;
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	COptions::CClipPlane
// Method				:	CCplitPlane
// Description			:	Ctor
// Return Value			:	-
// Comments				:
COptions::CClipPlane::CClipPlane() {
}


///////////////////////////////////////////////////////////////////////
// Class				:	COptions::CClipPlane
// Method				:	CCplitPlane
// Description			:	Ctor
// Return Value			:	-
// Comments				:
COptions::CClipPlane::CClipPlane(const CClipPlane *other) {
	movvv(normal,other->normal);
	d		=	other->d;
}


///////////////////////////////////////////////////////////////////////
// Class				:	COptions
// Method				:	COptions
// Description			:	All the default frame specific settings are defined here
// Return Value			:	-
// Comments				:
COptions::COptions() {
	stats.numOptions++;
	stats.optionsMemory		+=	sizeof(COptions);

	xres					=	640;
	yres					=	480;

	frame					=	-1;

	pixelAR					=	1;
	frameAR					=	4/(float) 3;

	cropLeft				=	0;
	cropRight				=	1;
	cropTop					=	0;
	cropBottom				=	1;

	screenLeft				=	-4/(float) 3;
	screenRight				=	4/(float) 3;
	screenTop				=	1;
	screenBottom			=	-1;
	
	clipMin					=	C_EPSILON;
	clipMax					=	C_INFINITY;

	pixelVariance			=	(float) 0.05;

	jitter					=	(float) 0.99;

	hider					=	strdup("stochastic");

	archivePath				=	optionsGetSearchPath(".:%RIBS%:" PIXIE_MODELS,NULL);
	proceduralPath			=	optionsGetSearchPath(".:%PROCEDURALS%:%PIXIEHOME%/procedurals:%PIXIEHOME%/bind:%PIXIE_PROCEDURALS%",NULL);
	texturePath				=	optionsGetSearchPath(".:%TEXTURES%:" PIXIE_TEXTURES,NULL);
	shaderPath				=	optionsGetSearchPath(".:%SHADERS%:" PIXIE_SHADERS,NULL);

#ifdef _DEBUG
	displayPath				=	optionsGetSearchPath(".:%DISPLAYS%:%PIXIEHOME%/bind:" PIXIE_DISPLAYS,NULL);
	modulePath				=	optionsGetSearchPath(".:%PIXIEHOME%/bind:" PIXIE_MODULES,NULL);
#else
	displayPath				=	optionsGetSearchPath(".:%DISPLAYS%:%PIXIEHOME%/displays:" PIXIE_DISPLAYS,NULL);
	modulePath				=	optionsGetSearchPath(".:%PIXIEHOME%/modules:" PIXIE_MODULES,NULL);
#endif

	// Override the official defaults for testing
	pixelXsamples			=	2;
	pixelYsamples			=	2;

	gamma					=	1;
	gain					=	1;	

	pixelFilterWidth		=	2;
	pixelFilterHeight		=	2;
	pixelFilter				=	RiCatmullRomFilter;

	colorQuantizer[0]		=	0;				// Zero
	colorQuantizer[1]		=	255;			// One
	colorQuantizer[2]		=	0;				// Min
	colorQuantizer[3]		=	255;			// Max
	colorQuantizer[4]		=	0.5;
	depthQuantizer[0]		=	0;				// Zero
	depthQuantizer[1]		=	0;				// One
	depthQuantizer[2]		=	0;				// Min
	depthQuantizer[3]		=	0;				// Max
	depthQuantizer[4]		=	0;

	// We default to sampling motion, but this can be turned off.
	// Additionally, if there's no motionblur in the scene, it will be turned off
	flags					=	OPTIONS_FLAGS_SAMPLEMOTION;

	displays				=	NULL;

	clipPlanes				=	NULL;

	relativeDetail			=	1;

	projection				=	OPTIONS_PROJECTION_ORTHOGRAPHIC;
	fov						=	90;

	nColorComps				=	3;
	fromRGB					=	NULL;
	toRGB					=	NULL;

	fstop					=	C_INFINITY;
	focallength				=	1;
	focaldistance			=	1;

	shutterOpen				=	0;
	shutterClose			=	0;

	endofframe				=	0;
	filelog					=	NULL;

	numThreads				=	DEFAULT_NUM_THREADS;

	maxTextureSize			=	DEFAULT_MAX_TEXTURESIZE;
	maxBrickSize			=	DEFAULT_MAX_BRICKSIZE;

	maxGridSize				=	DEFAULT_MAX_GRIDSIZE;

	maxRayDepth				=	5;
	maxPhotonDepth			=	10;

	bucketWidth				=	DEFAULT_TILE_WIDTH;
	bucketHeight			=	DEFAULT_TILE_HEIGHT;

	netXBuckets				=	DEFAULT_NET_XBUCKETS;
	netYBuckets				=	DEFAULT_NET_YBUCKETS;

	threadStride			=	DEFAULT_THREAD_STRIDE;
	
	geoCacheMemory			=	DEFAULT_GEO_CACHE_SIZE;

	maxEyeSplits			=	10;

	tsmThreshold			=	DEFAULT_TSM_THRESHOLD;

	causticIn				=	NULL;
	causticOut				=	NULL;

	globalIn				=	NULL;
	globalOut				=	NULL;

	volumeIn				=	NULL;
	volumeOut				=	NULL;

	numEmitPhotons			=	10000;

	shootStep				=	1000;

	depthFilter				=	DEPTH_MIN;
}


///////////////////////////////////////////////////////////////////////
// Class				:	COptions
// Method				:	COptions
// Description			:	Create an exact copy of another options block
// Return Value			:	-
// Comments				:
COptions::COptions(const COptions *o) {
	stats.numOptions++;
	stats.optionsMemory		+=	sizeof(COptions);

	this[0]					=	o[0];

	hider					=	strdup(o->hider);

	archivePath				=	optionsCloneSearchPath(o->archivePath);
	proceduralPath			=	optionsCloneSearchPath(o->proceduralPath);
	texturePath				=	optionsCloneSearchPath(o->texturePath);
	shaderPath				=	optionsCloneSearchPath(o->shaderPath);
	displayPath				=	optionsCloneSearchPath(o->displayPath);
	modulePath				=	optionsCloneSearchPath(o->modulePath);

	if (o->displays != NULL) {
		CDisplay	*cDisplay,*nDisplay;

		displays		=	NULL;
		for (cDisplay=o->displays;cDisplay!=NULL;cDisplay=cDisplay->next) {
			nDisplay		=	new CDisplay(cDisplay);
			nDisplay->next	=	displays;
			displays		=	nDisplay;
		}
	} else {
		displays		=	NULL;
	}


	if (o->clipPlanes != NULL) {
		CClipPlane		*cPlane,*nPlane;

		clipPlanes		=	NULL;
		for (cPlane=o->clipPlanes;cPlane!=NULL;cPlane=cPlane->next) {
			nPlane			=	new CClipPlane;
			*nPlane			=	*cPlane;
			nPlane->next	=	clipPlanes;
			clipPlanes		=	nPlane;
		}
	} else {
		clipPlanes		=	NULL;
	}

	
	if (o->fromRGB	!= NULL) {
		fromRGB		=	new float[3*nColorComps];
		memcpy(fromRGB,o->fromRGB,3*nColorComps*sizeof(float));
	} else {
		fromRGB		=	NULL;
	}

	if (o->toRGB	!= NULL) {
		toRGB		=	new float[3*nColorComps];
		memcpy(toRGB,o->toRGB,3*nColorComps*sizeof(float));
	} else {
		toRGB		=	NULL;
	}

	if (o->causticIn != NULL) {
		causticIn				=	strdup(o->causticIn);
	} else {
		causticIn				=	NULL;
	}

	if (o->causticOut != NULL) {
		causticOut				=	strdup(o->causticOut);
	} else {
		causticOut				=	NULL;
	}

	if (o->globalIn != NULL) {
		globalIn				=	strdup(o->globalIn);
	} else {
		globalIn				=	NULL;
	}

	if (o->globalOut != NULL) {
		globalOut				=	strdup(o->globalOut);
	} else {
		globalOut				=	NULL;
	}

	if (o->volumeIn != NULL) {
		volumeIn				=	strdup(o->volumeIn);
	} else {
		volumeIn				=	NULL;
	}

	if (o->volumeOut != NULL) {
		volumeOut				=	strdup(o->volumeOut);
	} else {
		volumeOut				=	NULL;
	}

	if (o->filelog != NULL) {
		filelog					=	strdup(o->filelog);
	} else {
		filelog					=	NULL;
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	COptions
// Method				:	~COptions
// Description			:	Destructor
// Return Value			:	-
// Comments				:
COptions::~COptions(){
	stats.numOptions--;
	stats.optionsMemory		-=	sizeof(COptions);


	if (fromRGB != NULL) 
		delete [] fromRGB;

	if (toRGB != NULL)
		delete [] toRGB;

	if (displays != NULL) {
		CDisplay	*cDisplay,*nDisplay;

		for (cDisplay=displays;cDisplay!=NULL;) {
			nDisplay	=	cDisplay->next;
			delete cDisplay;
			cDisplay	=	nDisplay;
		}
	}

	if (clipPlanes != NULL) {
		CClipPlane	*cPlane,*nPlane;

		for (cPlane=clipPlanes;cPlane!=NULL;) {
			nPlane	=	cPlane->next;
			delete cPlane;
			cPlane	=	nPlane;
		}
	}

	if (hider != NULL)
		free(hider);


	optionsDeleteSearchPath(archivePath);
	optionsDeleteSearchPath(proceduralPath);
	optionsDeleteSearchPath(texturePath);
	optionsDeleteSearchPath(shaderPath);
	optionsDeleteSearchPath(displayPath);
	optionsDeleteSearchPath(modulePath);

	if (causticIn				!= NULL)	free(causticIn);
	if (causticOut				!= NULL)	free(causticOut);
	if (globalIn				!= NULL)	free(globalIn);
	if (globalOut				!= NULL)	free(globalOut);
	if (volumeIn				!= NULL)	free(volumeIn);
	if (volumeOut				!= NULL)	free(volumeOut);
	if (filelog					!= NULL)	free(filelog);
}

///////////////////////////////////////////////////////////////////////
// Class				:	COptions
// Method				:	convertColor
// Description			:	Convert color to RGB space from whatever space entered
// Return Value			:	-
// Comments				:
void	COptions::convertColor(vector &c,const float *f)	const	{
	int	i,j;
	if (toRGB == NULL) {
		c[COMP_R] = f[0];
		c[COMP_G] = f[1];
		c[COMP_B] = f[2];
	} else {
		for (i=0;i<3;i++) {
			c[i] = 0;
			for (j=0;j<(int) nColorComps;j++)
				c[i] += f[j]*toRGB[i*nColorComps+j];
		}
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	COptions
// Method				:	pickSearchpath
// Description			:	Pick a searchpath from name
// Return Value			:	-
// Comments				:
TSearchpath		*COptions::pickSearchpath(const char *name) {

	if (strstr(name,"rib") != NULL) {
		return archivePath;

	} else if (strstr(name,"tif") != NULL) {
		return texturePath;

	} else if (strstr(name,"tiff") != NULL) {
		return texturePath;
	
	} else if (strstr(name,"tex") != NULL) {
		return texturePath;
	
	} else if (strstr(name,"tx") != NULL) {
		return texturePath;
	
	} else if (strstr(name,"ptc") != NULL) {
		return texturePath;
	
	} else if (strstr(name,"bm") != NULL) {
		return texturePath;
		
	} else if (strstr(name,"sdr") != NULL) {
		return shaderPath;

	} else if (strstr(name,osModuleExtension) != NULL) {
		return proceduralPath;
	}

	return NULL;
}


///////////////////////////////////////////////////////////////////////
// Function				:	optionsGetSearchPath
// Description			:	Get the searchpath
// Return Value			:	-
// Comments				:
TSearchpath					*optionsGetSearchPath(const char *path,TSearchpath *oldPath) {
	TSearchpath		*newPath	=	NULL;
	TSearchpath		*lastPath	=	NULL;
	TSearchpath		*cPath;
	const	char	*currentPath;
	char			tmp[OS_MAX_PATH_LENGTH];
	char			*dest;

	for (dest=tmp,currentPath=path;;) {
		if ((*currentPath == '\0') || (*currentPath == ':')) {		// End of the current path

#ifdef WIN32
			if ((dest - tmp) == 1) {
				if ((currentPath[1] == '\\') || (currentPath[1] == '/')) {
					*dest++	=	*currentPath++;
					continue;
				}
			}
#endif

			if ((dest - tmp) > 0) {		// Do we have anything to record ?
				dest--;

				if ((*dest == '/') || (*dest == '\\')) {	// The last character has to be a slash
					dest++;
				} else {
					dest++;
					*dest++	=	'/';
				}

				*dest++		=	'\0';
				osFixSlashes(tmp);

				cPath				=	new TSearchpath;
				if (strncmp(tmp,"\\\\",2) == 0) {
					tmp[1]	=	tmp[2];
					tmp[2]	=	':';
					tmp[3]	=	'\\';
					cPath->directory	=	strdup(tmp+1);
				} else {
					cPath->directory	=	strdup(tmp);
				}
				cPath->next			=	NULL;

				if (lastPath == NULL) {
					lastPath		=	cPath;
					newPath			=	cPath;
				} else {
					lastPath->next	=	cPath;
					lastPath		=	cPath;
				}
			}

			dest			=	tmp;

			if (*currentPath == '\0')	break;

			currentPath++;
		} else if (*currentPath == '%') {
			const	char	*endOfCurrentPath	=	strchr(currentPath+1,'%');
			char			environmentVariable[OS_MAX_PATH_LENGTH];

			if (endOfCurrentPath!=NULL) {
				const	int		environmentLength	=	endOfCurrentPath - currentPath - 1;
				const	char	*value;

				strncpy(environmentVariable,currentPath+1,environmentLength);
				environmentVariable[environmentLength]	=	'\0';

				value		=	osEnvironment(environmentVariable);
				if (value != NULL) {
					strcpy(dest,value);
					dest	+=	strlen(value);
				}

				currentPath	=	endOfCurrentPath+1;
			} else {
				currentPath++;
			}
		} else if ((*currentPath == '@') || (*currentPath == '&')) {
			for (cPath=oldPath;cPath!=NULL;cPath=cPath->next) {
				TSearchpath	*nPath	=	new TSearchpath;

				nPath->directory	=	strdup(cPath->directory);
				nPath->next			=	NULL;

				if (lastPath == NULL) {
					lastPath		=	nPath;
					newPath			=	nPath;
				} else {
					lastPath->next	=	nPath;
					lastPath		=	nPath;
				}
			}
			currentPath++;
		} else {
			*dest++	=	*currentPath++;
		}
	}

	optionsDeleteSearchPath(oldPath);

	return newPath;
}
