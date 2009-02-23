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

#ifdef __APPLE__
#include <sys/stat.h>
#include <CoreServices/CoreServices.h>
#ifdef check   // Apple's library defines "check"
#undef check
#endif
#endif

#include "options.h"
#include "texture.h"
#include "stats.h"
#include "ri_config.h"

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

	startFunction	=	NULL;
	dataFunction	=	NULL;
	finishFunction	=	NULL;

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

	startFunction	=	other->startFunction;
	dataFunction	=	other->dataFunction;
	finishFunction	=	other->finishFunction;

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
	atomicIncrement(&stats.numOptions);

	xres					=	640;
	yres					=	480;

	frame					=	-1;

	pixelAR					=	1;
	frameAR					=	4.0f/3.0f;

	cropLeft				=	0;
	cropRight				=	1;
	cropTop					=	0;
	cropBottom				=	1;

	screenLeft				=	-4.0f/3.0f;
	screenRight				=	4.0f/3.0f;
	screenTop				=	1;
	screenBottom			=	-1;
	
	clipMin					=	C_EPSILON;
	clipMax					=	C_INFINITY;

	pixelVariance			=	0.05f;

	jitter					=	0.99f;

	hider					=	strdup("stochastic");
	
#ifdef __APPLE__
	// Support for finding resources in Mac OS X bundles and standard Mac OS X file system locations
	
	// Find the application bundle's plug-in and Resources directory
	char path[OS_MAX_PATH_LENGTH];
	char pathtmp[OS_MAX_PATH_LENGTH];
	CFBundleRef bundle = CFBundleGetMainBundle();
	if (bundle) {
		CFURLRef url = CFBundleCopyBuiltInPlugInsURL(bundle);
		if (url) {
			Boolean validpath = CFURLGetFileSystemRepresentation(url,true,(UInt8*)path,OS_MAX_PATH_LENGTH);
			if (validpath)
				setenv("PIXIEAPPPLUGINS", (const char*)path, 1);
			CFRelease(url);
		}
		url = CFBundleCopyResourcesDirectoryURL(bundle);
		if (url) {
			Boolean validpath = CFURLGetFileSystemRepresentation(url,true,(UInt8*)path,OS_MAX_PATH_LENGTH);
			if (validpath)
				setenv("PIXIEAPPRESOURCES", (const char*)path, 1);
			CFRelease(url);
		}
		CFRelease(bundle);
	}
	
	// Find the application support directory (~/Library/Application Support/Pixie/PlugIns), and set the
	// PIXIEUSERDIR environment variable to that directory
	FSRef appsupport;
    if (FSFindFolder(kUserDomain, kApplicationSupportFolderType, kCreateFolder, &appsupport) == noErr) {
		FSRefMakePath(&appsupport, (UInt8*)path, OS_MAX_PATH_LENGTH);
		sprintf(pathtmp, "%s/" PACKAGE, path);
		mkdir(pathtmp, 0755);
		setenv("PIXIEUSERDIR", (const char*)pathtmp, 1);
	}
	
	// Find the application support directory (/Library/Application Support/Pixie/PlugIns), and set the
	// PIXIELOCALDIR environment variable to that directory
    if (FSFindFolder(kLocalDomain, kApplicationSupportFolderType, kCreateFolder, &appsupport) == noErr) {
		FSRefMakePath(&appsupport, (UInt8*)path, OS_MAX_PATH_LENGTH);
		snprintf(pathtmp, OS_MAX_PATH_LENGTH, "%s/" PACKAGE, path);
		mkdir(pathtmp, 0755);
		setenv("PIXIELOCALDIR", (const char*)pathtmp, 1);
	}
	
	// Default home, unless overridden with environment
	setenv("PIXIEHOME","/Library/Pixie",0);
	
	archivePath             =   optionsGetSearchPath(".:%RIBS%:%PIXIEHOME%/ribs" ,NULL);
	proceduralPath          =   optionsGetSearchPath(".:%PROCEDURALS%:%PIXIEUSERDIR%/procedurals:%PIXIELOCALDIR%/procedurals:%PIXIEAPPPLUGINS%:%PIXIEHOME%/procedurals",NULL);
	texturePath             =   optionsGetSearchPath(".:%TEXTURES%:%PIXIEUSERDIR%/textures:%PIXIELOCALDIR%/textures:%PIXIEAPPRESOURCES%/textures:%PIXIEHOME%/textures",NULL);
	shaderPath              =   optionsGetSearchPath(".:%SHADERS%:%PIXIEUSERDIR%/shaders:%PIXIELOCALDIR%/shaders:%PIXIEAPPRESOURCES%/shaders:%PIXIEHOME%/shaders",NULL);
	displayPath             =   optionsGetSearchPath("%DISPLAYS%:%PIXIEUSERDIR%/displays:%PIXIELOCALDIR%/displays:%PIXIEAPPPLUGINS%:%PIXIEHOME%/displays",NULL);
	modulePath              =   optionsGetSearchPath("%MODULES%:%PIXIEUSERDIR%/modules:%PIXIELOCALDIR%/modules:%PIXIEAPPPLUGINS%:%PIXIEHOME%/modules",NULL);

#else
	archivePath				=	optionsGetSearchPath(".:%RIBS%:" PIXIE_RIBS,NULL);
	proceduralPath			=	optionsGetSearchPath(".:%PROCEDURALS%:" PIXIE_PROCEDURALS,NULL);
	texturePath				=	optionsGetSearchPath(".:%TEXTURES%:" PIXIE_TEXTURES,NULL);
	shaderPath				=	optionsGetSearchPath(".:%SHADERS%:" PIXIE_SHADERS,NULL);
	displayPath				=	optionsGetSearchPath(".:%DISPLAYS%:" PIXIE_DISPLAYS,NULL);
	modulePath				=	optionsGetSearchPath(".:%MODULES%:" PIXIE_MODULES,NULL);
#endif

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

	initv(opacityThreshold,0.996f);
	initv(zvisibilityThreshold,0.996f);
	
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
	shutterOffset			=	0;

	endofframe				=	0;
	filelog					=	NULL;

	numThreads              =   osAvailableCPUs();
	if (numThreads < 1)
		numThreads          =   DEFAULT_NUM_THREADS;

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
	atomicIncrement(&stats.numOptions);

	this[0]					=	o[0];

	// Note: The assignment here also invokes the assignment operator of userOptions
	//      so there's no need for a separate copy for that

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

	causticIn				=	(o->causticIn != NULL ? strdup(o->causticIn) : NULL);
	causticOut				=	(o->causticOut != NULL ? strdup(o->causticOut) : NULL);
	globalIn				=	(o->globalIn != NULL ? strdup(o->globalIn) : NULL);
	globalOut				=	(o->globalOut != NULL ? strdup(o->globalOut) : NULL);
	filelog					=	(o->filelog != NULL ? strdup(o->filelog) : NULL);
}


///////////////////////////////////////////////////////////////////////
// Class				:	COptions
// Method				:	~COptions
// Description			:	Destructor
// Return Value			:	-
// Comments				:
COptions::~COptions(){
	atomicDecrement(&stats.numOptions);

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

#ifdef _WINDOWS
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
				const	int		environmentLength	=	(int) (endOfCurrentPath - currentPath) - 1;
				const	char	*value;

				strncpy(environmentVariable,currentPath+1,environmentLength);
				environmentVariable[environmentLength]	=	'\0';

				value		=	osEnvironment(environmentVariable);
				if (value != NULL) {
					strcpy(dest,value);
					dest	+=	strlen(value);
					currentPath =   endOfCurrentPath+1;
				} else {
					// If this environment variable was not defined, scrap the entire
					// path in progress b/c it will not be correct without this env variable
					dest = tmp;
					*dest = '\0';   // Truncate dest path
					currentPath = strchr(endOfCurrentPath,':');         // Skip to next path
					if (!currentPath)
						currentPath = strchr(endOfCurrentPath,'\0');    // ...or end if last path
				}

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

///////////////////////////////////////////////////////////////////////
// Class				:	COptions
// Method				:	find
// Description			:	Find the value of a particular option
// Return Value			:	-
// Comments				:
int			COptions::find(const char *name,const char *category,EVariableType &type,const void *&value,int &intValue,float &floatValue) const {

	// Check the common case first
	if ((category == NULL) || (strcmp(category,RI_USER) == 0)) {
		CVariable *var;
        if (userOptions.lookup(name,var) == TRUE) {
			type = var->type;
			value = var->defaultValue;
			if (value != NULL)	return TRUE;
		}
	}

	if ((category == NULL) || (strcmp(category,RI_LIMITS) == 0)) {
		if (strcmp(name,RI_BUCKETSIZE) == 0)				{	type	=	TYPE_INTEGER;	value	=	&bucketWidth;			return TRUE;}
		else if (strcmp(name,RI_METABUCKETS) == 0)			{	type	=	TYPE_INTEGER;	value	=	&netXBuckets;			return TRUE;}
		else if (strcmp(name,RI_GRIDSIZE) == 0)				{	type	=	TYPE_INTEGER;	value	=	&maxGridSize;			return TRUE;}
		else if (strcmp(name,RI_EYESPLITS) == 0)			{	type	=	TYPE_INTEGER;	value	=	&maxEyeSplits;			return TRUE;}
		else if (strcmp(name,RI_TEXTUREMEMORY) == 0)		{	type	=	TYPE_INTEGER;	value	=	NULL;	intValue = maxTextureSize / 1000;	return TRUE;}
		else if (strcmp(name,RI_BRICKMEMORY) == 0)			{	type	=	TYPE_INTEGER;	value	=	NULL;	intValue = maxBrickSize / 1000;		return TRUE;}
		else if (strcmp(name,RI_NUMTHREADS) == 0)			{	type	=	TYPE_INTEGER;	value	=	&numThreads;			return TRUE;}
		else if (strcmp(name,RI_THREADSTRIDE) == 0)			{	type	=	TYPE_INTEGER;	value	=	&threadStride;			return TRUE;}
		else if (strcmp(name,RI_GEOCACHEMEMORY) == 0)		{	type	=	TYPE_INTEGER;	value	=	NULL;	intValue = geoCacheMemory / 1000;	return TRUE;}
		else if (strcmp(name,RI_INHERITATTRIBUTES) == 0)	{	type	=	TYPE_INTEGER;	value	=	NULL;	intValue = (flags & OPTIONS_FLAGS_INHERIT_ATTRIBUTES) != 0;				return TRUE;}
		else if (strcmp(name,"frame") == 0)					{	type	=	TYPE_INTEGER;	value	=	&frame;					return TRUE;}
	}
	
	if ((category == NULL) || (strcmp(category,RI_HIDER) == 0)) {
		if (strcmp(name,RI_JITTER) == 0)					{	type	=	TYPE_FLOAT;		value	=	&jitter;				return TRUE;}
		else if (strcmp(name,RI_EMIT) == 0)					{	type	=	TYPE_INTEGER;	value	=	&numEmitPhotons;		return TRUE;}
		else if (strcmp(name,RI_SAMPLESPECTRUM) == 0)		{	type	=	TYPE_INTEGER;	value	=	NULL;	intValue = (flags & OPTIONS_FLAGS_SAMPLESPECTRUM) != 0;				return TRUE;}
		else if (strcmp(name,RI_SAMPLEMOTION) == 0)			{	type	=	TYPE_INTEGER;	value	=	NULL;	intValue = (flags & OPTIONS_FLAGS_SAMPLEMOTION) != 0;				return TRUE;}
	}
	
	if ((category == NULL) || (strcmp(category,RI_TRACE) == 0)) {
		if (strcmp(name,RI_MAXDEPTH) == 0)					{	type	=	TYPE_INTEGER;	value	=	&maxRayDepth;			return TRUE;}
	}

	if ((category == NULL) || (strcmp(category,RI_STATISTICS) == 0)) {
		if (strcmp(name,RI_ENDOFFRAME) == 0)				{	type	=	TYPE_INTEGER;	value	=	&endofframe;			return TRUE;}
		else if (strcmp(name,RI_FILELOG) == 0)				{	type	=	TYPE_STRING;	value	=	filelog;				return TRUE;}
		else if (strcmp(name,RI_PROGRESS) == 0)				{	type	=	TYPE_INTEGER;	value	=	NULL;	intValue = (flags & OPTIONS_FLAGS_PROGRESS) != 0;				return TRUE;}

	}
	
	if ((category == NULL) || (strcmp(category,RI_SHUTTER) == 0)) {
		if (strcmp(name,RI_OFFSET) == 0)					{	type	=	TYPE_FLOAT;		value	=	&shutterOffset;			return TRUE;}
	}

	
	return FALSE;
}
