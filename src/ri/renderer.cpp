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
//  File				:	renderer.cpp
//  Classes				:	-
//  Description			:	Renderer implementation
//
////////////////////////////////////////////////////////////////////////
#include <math.h>
#include <string.h>
#include <stdarg.h>


#include "common/algebra.h"
#include "common/containers.h"
#include "common/os.h"
#include "ray.h"
#include "object.h"
#include "xform.h"
#include "shader.h"
#include "texture.h"
#include "raytracer.h"
#include "stochastic.h"
#include "zbuffer.h"
#include "renderer.h"
#include "patches.h"
#include "ri.h"
#include "rib.h"
#include "shadeop.h"
#include "noise.h"
#include "stats.h"
#include "memory.h"
#include "photonMap.h"
#include "photon.h"
#include "polygons.h"
#include "quadrics.h"
#include "patches.h"
#include "subdivisionCreator.h"
#include "irradiance.h"
#include "random.h"
#include "points.h"
#include "curves.h"
#include "instance.h"
#include "delayed.h"
#include "dso.h"
#include "bundles.h"
#include "texmake.h"
#include "pl.h"
#include "error.h"
#include "hcshader.h"
#include "implicitSurface.h"
#include "dlobject.h"
#include "brickmap.h"
#include "show.h"

// The default network port
#define	DEFAULT_PORT	24914

// Identity matrix for unknown transformations
static		matrix	identity	=	{	1,	0,	0,	0,
										0,	1,	0,	0,
										0,	0,	1,	0,
										0,	0,	0,	1	};




// Textual definitions of predefined coordinate systems
const char	*coordinateCameraSystem		=	"camera";
const char	*coordinateWorldSystem		=	"world";
const char	*coordinateObjectSystem		=	"object";
const char	*coordinateShaderSystem		=	"shader";
const char	*coordinateLightSystem		=	"light";
const char	*coordinateNDCSystem		=	"NDC";
const char	*coordinateRasterSystem		=	"raster";
const char	*coordinateScreenSystem		=	"screen";
const char	*coordinateCurrentSystem	=	"current";

// Textual definitions of the predefined color systems
const char	*colorRgbSystem				=	"rgb";
const char	*colorHslSystem				=	"hsl";
const char	*colorHsvSystem				=	"hsv";
const char	*colorXyzSystem				=	"xyz";
const char	*colorYiqSystem				=	"yiq";
const char	*colorXyySystem				=	"xyy";
const char	*colorCieSystem				=	"cie";

// The default zone size
#define	BUFFER_LENGTH	1 << 12				// The size of the buffer to be used during the network file transfers

////////////////////////////////////////////////////////////////////////////////////////////////
// The global variables are defined here
CRendererContext	*currentRenderer		=	NULL;
extern	int			ribCommandLineno;					// These two are defined in rib.y
extern	const char	*ribFile;


///////////////////////////////////////////////////////////////////////
// Class				:	CNetFileMapping
// Description			:	maps files to alternate pats
// Return Value			:
// Comments				:
// Date last edited		:	02/25/2006
class CNetFileMapping{
public:
	CNetFileMapping(const char *from,const char *to) {
		this->from	= strdup(from);
		this->to	= strdup(to);
	}
	~CNetFileMapping() {
		free(from);
		free(to);
	}
	
	char *from,*to;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CDisplayChannel
// Description			:	display channel info ctor
// Return Value			:
// Comments				:	var can be NULL
// Date last edited		:	02/25/2006
CDisplayChannel::CDisplayChannel() {
	strcpy(this->name,"*INVALID*");
	variable		=	NULL;
	numSamples		= 	0;
	sampleStart		=	-1;
	outType			=	-1;
	fill			=	NULL;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDisplayChannel
// Description			:	display channel info dtor
// Return Value			:
// Comments				:	var can be NULL
// Date last edited		:	02/25/2006
CDisplayChannel::~CDisplayChannel() {
	if (fill) free(fill);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDisplayChannel
// Description			:	display channel info ctor
// Return Value			:
// Comments				:	var can be NULL
// Date last edited		:	02/25/2006
CDisplayChannel::CDisplayChannel(const char *name,CVariable *var,int samples,int start,int entry) {
	strcpy(this->name,name);
	variable	=	var;
	numSamples	=	samples;
	sampleStart	=	start;
	outType		=	entry;
	fill		=	NULL;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	CRendererContext
// Description			:	Ctor
// Return Value			:
// Comments				:
// Date last edited		:	8/25/2002
CRendererContext::CRendererContext(char *ribFile,char *riNetString) {
	// Declare the global variables
	CVariable		*tmp;
	CDisplayChannel	*tmp2;
	float			startTime	=	osCPUTime();

	////////////////////////////////////////////////////////////////////////////////////////////
	//
	//
	//			R E N D E R E R 		I N I T
	//
	//
	////////////////////////////////////////////////////////////////////////////////////////////
	currentRenderer					=	this;

	definedCoordinateSystems		=	NULL;
	declaredVariables				=	NULL;
	variables						=	NULL;
	numGlobalVariables				=	0;
	savedXforms						=	NULL;
	savedAttributes					=	NULL;
	savedOptions					=	NULL;
	objects							=	NULL;
	objectsStack					=	NULL;
	allocatedInstances				=	NULL;
	currentXform					=	NULL;
	currentAttributes				=	NULL;
	currentOptions					=	NULL;
	dsos							=	NULL;
	netClient						=	INVALID_SOCKET;
	netNumServers					=	0;
	netServers						=	NULL;
	renderer						=	NULL;
	userRaytracing					=	FALSE;
	numNetrenderedBuckets			=	0;


	////////////////////////////////////////////////////////////////////////////////////////////
	//
	//
	//			I N T E R F A C E			I N I T
	//
	//
	////////////////////////////////////////////////////////////////////////////////////////////
	numExpectedMotions				=	1;
	numMotions						=	0;
	keyTimes						=	NULL;
	motionParameters				=	NULL;
	maxMotionParameters				=	0;
	lastCommand						=	NULL;


	////////////////////////////////////////////////////////////////////////////////////////////
	//
	//
	//			S T A T S			I N I T
	//
	//
	////////////////////////////////////////////////////////////////////////////////////////////
	// Init the stats
	stats.reset();
	memoryInit();

	////////////////////////////////////////////////////////////////////////////////////////////
	//
	//
	//			G R A P H I C S		S T A T E		I N I T
	//
	//
	////////////////////////////////////////////////////////////////////////////////////////////

	// Init the coordinate systems
	definedCoordinateSystems			=	new CTrie<CNamedCoordinateSystem *>;
	// Init the declared variables
	declaredVariables					=	new CTrie<CVariable *>;
	// The loaded shaders
	loadedFiles							=	new CTrie<CFileResource *>;
	// Global Ids
	globalIdHash						=	new CTrie<CGlobalIdentifier *>;
	numKnownGlobalIds					=	1;		// Zero is reserved as an invalid value
	// net file mappings
	netFileMappings						=	NULL;
	frameTemporaryFiles					=	NULL;

	// Make sure there are no defined variables
	numGlobalVariables					=	0;
	variables							=	NULL;

	// Define the options
	declareVariable(RI_ARCHIVE,				"string");
	declareVariable(RI_PROCEDURAL,			"string");
	declareVariable(RI_TEXTURE,				"string");
	declareVariable(RI_SHADER,				"string");
	declareVariable(RI_DISPLAY,				"string");
	declareVariable(RI_RESOURCE,			"string");

	declareVariable(RI_BUCKETSIZE,			"int[2]");
	declareVariable(RI_METABUCKETS,			"int[2]");
	declareVariable(RI_INHERITATTRIBUTES,	"int");
	declareVariable(RI_GRIDSIZE,			"int");
	declareVariable(RI_HIERARCHYDEPTH,		"int");
	declareVariable(RI_HIERARCHYOBJECTS,	"int");
	declareVariable(RI_EYESPLITS,			"int");
	declareVariable(RI_TEXTUREMEMORY,		"int");
	declareVariable(RI_BRICKMEMORY,			"int");
	declareVariable(RI_SHADERCACHE,			"int");

	declareVariable(RI_RADIANCECACHE,		"int");
	declareVariable(RI_JITTER,				"float");
	declareVariable(RI_FALSECOLOR,			"int");
	declareVariable(RI_EMIT,				"int");
	declareVariable(RI_SAMPLESPECTRUM,		"int");
	declareVariable(RI_DEPTHFILTER,			"string");

	declareVariable(RI_MAXDEPTH,			"int");

	declareVariable(RI_ENDOFFRAME,			"int");
	declareVariable(RI_FILELOG,				"string");
	declareVariable(RI_PROGRESS,			"int");

	// File display variables
	
	declareVariable("quantize",				"float[4]");
	declareVariable("dither",				"float");
	declareVariable("gamma",				"float");
	declareVariable("gain",					"float");
	declareVariable("near",					"float");
	declareVariable("far",					"float");
	declareVariable("Software",				"string");
	declareVariable("compression",			"string");
	declareVariable("NP",					"float[16]");
	declareVariable("Nl",					"float[16]");

	// Define the attributes
	declareVariable(RI_NUMPROBES,			"int[2]");
	declareVariable(RI_MINSUBDIVISION,		"int");
	declareVariable(RI_MAXSUBDIVISION,		"int");
	declareVariable(RI_MINSPLITS,			"int");
	declareVariable(RI_BOUNDEXPAND,			"float");
	declareVariable(RI_BINARY,				"int");
	declareVariable(RI_RASTERORIENT,		"int");

	declareVariable(RI_SPHERE,				"float");
	declareVariable(RI_COORDINATESYSYTEM,	"string");

	declareVariable(RI_DISPLACEMENTS,		"int");
	declareVariable(RI_BIAS,				"float");
	declareVariable(RI_MAXDIFFUSEDEPTH,		"int");
	declareVariable(RI_MAXSPECULARDEPTH,	"int");

	declareVariable(RI_HANDLE,				"string");
	declareVariable(RI_FILEMODE,			"string");
	declareVariable(RI_MAXERROR,			"float");

	declareVariable(RI_GLOBALMAP,			"string");
	declareVariable(RI_CAUSTICMAP,			"string");
	declareVariable(RI_SHADINGMODEL,		"string");
	declareVariable(RI_ESTIMATOR,			"int");
	declareVariable(RI_ILLUMINATEFRONT,		"int");

	declareVariable(RI_TRANSMISSION,		"string");
	declareVariable(RI_CAMERA,				"int");
	declareVariable(RI_TRACE,				"int");
	declareVariable(RI_PHOTON,				"int");

	declareVariable(RI_NAME,				"string");

	declareVariable(RI_HIDDEN,				"int");
	declareVariable(RI_BACKFACING,			"int");

	// Define varying variables
	tmp	=	declareVariable("P",	"global vertex point",PARAMETER_P);			assert(tmp->entry	==	VARIABLE_P);
	tmp	=	declareVariable("Ps",	"global vertex point",PARAMETER_PS);		assert(tmp->entry	==	VARIABLE_PS);
	tmp	=	declareVariable("N",	"global varying normal",PARAMETER_N);		assert(tmp->entry	==	VARIABLE_N);
	tmp	=	declareVariable("Ng",	"global varying normal",PARAMETER_NG);		assert(tmp->entry	==	VARIABLE_NG);
	tmp	=	declareVariable("dPdu",	"global vertex vector",PARAMETER_DPDU);		assert(tmp->entry	==	VARIABLE_DPDU);
	tmp	=	declareVariable("dPdv",	"global vertex vector",PARAMETER_DPDV);		assert(tmp->entry	==	VARIABLE_DPDV);
	tmp	=	declareVariable("L",	"global varying vector",PARAMETER_L);		assert(tmp->entry	==	VARIABLE_L);
	tmp	=	declareVariable("Cs",	"global varying color",PARAMETER_CS);		assert(tmp->entry	==	VARIABLE_CS);
	tmp	=	declareVariable("Os",	"global varying color",PARAMETER_OS);		assert(tmp->entry	==	VARIABLE_OS);
	tmp	=	declareVariable("Cl",	"global varying color",PARAMETER_CL);		assert(tmp->entry	==	VARIABLE_CL);
	tmp	=	declareVariable("Ol",	"global varying color",PARAMETER_OL);		assert(tmp->entry	==	VARIABLE_OL);
	tmp	=	declareVariable("Ci",	"global varying color",PARAMETER_CI);		assert(tmp->entry	==	VARIABLE_CI);
	tmp	=	declareVariable("Oi",	"global varying color",PARAMETER_OI);		assert(tmp->entry	==	VARIABLE_OI);
	tmp	=	declareVariable("s",	"global varying float",PARAMETER_S);		assert(tmp->entry	==	VARIABLE_S);
	tmp	=	declareVariable("t",	"global varying float",PARAMETER_T);		assert(tmp->entry	==	VARIABLE_T);
	tmp	=	declareVariable("st",	"varying float[2]",PARAMETER_S | PARAMETER_T);
	tmp	=	declareVariable("du",	"global varying float",PARAMETER_DU | PARAMETER_DERIVATIVE);	assert(tmp->entry	==	VARIABLE_DU);
	tmp	=	declareVariable("dv",	"global varying float",PARAMETER_DV | PARAMETER_DERIVATIVE);	assert(tmp->entry	==	VARIABLE_DV);
	tmp	=	declareVariable("u",	"global varying float",PARAMETER_U);		assert(tmp->entry	==	VARIABLE_U);
	tmp	=	declareVariable("v",	"global varying float",PARAMETER_V);		assert(tmp->entry	==	VARIABLE_V);
	tmp	=	declareVariable("I",	"global varying vector",PARAMETER_I);		assert(tmp->entry	==	VARIABLE_I);
	tmp	=	declareVariable("E",	"global varying point",PARAMETER_E);		assert(tmp->entry	==	VARIABLE_E);
	tmp	=	declareVariable("alpha","global varying float",PARAMETER_ALPHA);	assert(tmp->entry	==	VARIABLE_ALPHA);
	tmp	=	declareVariable("time",	"global varying float",PARAMETER_TIME);		assert(tmp->entry	==	VARIABLE_TIME);
	tmp	=	declareVariable("Pw",	"global vertex htpoint",PARAMETER_P);		tmp->entry			=	VARIABLE_PW;
	tmp	=	declareVariable("__sru","global varying float",0);					assert(tmp->entry	==	VARIABLE_SRU);
	tmp	=	declareVariable("__srv","global varying float",0);					assert(tmp->entry	==	VARIABLE_SRV);
	tmp	=	declareVariable("Pz",	"vertex float",PARAMETER_P);				tmp->entry			=	VARIABLE_P;
	tmp	=	declareVariable("ncomps","global uniform float",PARAMETER_NCOMPS);	assert(tmp->entry	==	VARIABLE_NCOMPS);
	tmp	=	declareVariable("dtime","global uniform float",PARAMETER_DTIME);	assert(tmp->entry	==	VARIABLE_DTIME);

	tmp	=	declareVariable("width","global varying float",0);					assert(tmp->entry	==	VARIABLE_WIDTH);
	tmp	=	declareVariable("constantwidth","global constant float",0);			assert(tmp->entry	==	VARIABLE_CONSTANTWIDTH);
	tmp	=	declareVariable("Np","uniform normal",PARAMETER_NG);

	// Define the default display channels
	declaredChannels				=	new CTrie<CDisplayChannel*>;
	displayChannels					=	new	CArray<CDisplayChannel*>;
		
	tmp2 = new CDisplayChannel("rgb",NULL,3,0);
	displayChannels->push(tmp2);
	declaredChannels->insert(tmp2->name,tmp2);
	
	tmp2 = new CDisplayChannel("rgba",NULL,4,0);
	displayChannels->push(tmp2);
	declaredChannels->insert(tmp2->name,tmp2);
	
	tmp2 = new CDisplayChannel("a",NULL,1,3);
	displayChannels->push(tmp2);
	declaredChannels->insert(tmp2->name,tmp2);
	
	tmp2 = new CDisplayChannel("z",NULL,1,4);
	displayChannels->push(tmp2);
	declaredChannels->insert(tmp2->name,tmp2);
	
	tmp2 = new CDisplayChannel("rgbaz",NULL,5,0);
	displayChannels->push(tmp2);
	declaredChannels->insert(tmp2->name,tmp2);
	
	// Define default coordinate systems
	defineCoordinateSystem(coordinateCameraSystem,identity,identity,COORDINATE_CAMERA);
	defineCoordinateSystem(coordinateWorldSystem,identity,identity,COORDINATE_WORLD);
	defineCoordinateSystem(coordinateObjectSystem,identity,identity,COORDINATE_OBJECT);
	defineCoordinateSystem(coordinateShaderSystem,identity,identity,COORDINATE_SHADER);
	defineCoordinateSystem(coordinateLightSystem,identity,identity,COORDINATE_LIGHT);
	defineCoordinateSystem(coordinateNDCSystem,identity,identity,COORDINATE_NDC);
	defineCoordinateSystem(coordinateRasterSystem,identity,identity,COORDINATE_RASTER);
	defineCoordinateSystem(coordinateScreenSystem,identity,identity,COORDINATE_SCREEN);
	defineCoordinateSystem(coordinateCurrentSystem,identity,identity,COORDINATE_CURRENT);

	// Define the default color systems
	defineCoordinateSystem(colorRgbSystem,identity,identity,COLOR_RGB);
	defineCoordinateSystem(colorHslSystem,identity,identity,COLOR_HSL);
	defineCoordinateSystem(colorHsvSystem,identity,identity,COLOR_HSV);
	defineCoordinateSystem(colorXyzSystem,identity,identity,COLOR_XYZ);
	defineCoordinateSystem(colorCieSystem,identity,identity,COLOR_CIE);
	defineCoordinateSystem(colorYiqSystem,identity,identity,COLOR_YIQ);
	defineCoordinateSystem(colorXyySystem,identity,identity,COLOR_XYY);

	// Init the graphics state
	savedXforms						=	new CArray<CXform *>;
	savedAttributes					=	new CArray<CAttributes *>;
	savedOptions					=	new CArray<COptions *>;

	// Init the object stack
	objects							=	NULL;
	objectsStack					=	new CArray<CArray<CObject *> *>;

	// Init the object instance junk
	allocatedInstances				=	new CArray<CArray<CObject *> *>;

	// Allocate the initial graphics state
	currentOptions					=	new COptions;
	currentXform					=	new CXform;
	currentAttributes				=	new CAttributes;
	currentXform->attach();
	currentAttributes->attach();

	// DSO init
	dsos							=	NULL;

	// Network init
	netSetup(ribFile,riNetString);
	
	// Netfile dictionary if we're a netrender daemon
	if (netClient != INVALID_SOCKET) {
		netFileMappings = new CTrie<CNetFileMapping*>;
		
		// make the temporary directory pid-unique in case we have more than
		// one on a given host
		char	*newTemporaryPath = (char*) malloc(OS_MAX_PATH_LENGTH);
		char	hostName[1024];
		gethostname(hostName,1024);
		#ifdef WIN32
		sprintf(newTemporaryPath,"%s-%s-%d",currentOptions->temporaryPath,hostName,GetCurrentProcessId());
		#else
		sprintf(newTemporaryPath,"%s-%s-%d",currentOptions->temporaryPath,hostName,getpid());
		#endif
		osFixSlashes(newTemporaryPath);
		free(currentOptions->temporaryPath);
		currentOptions->temporaryPath = newTemporaryPath;
	}

	// Record the start overhead
	stats.rendererStartOverhead		=	osCPUTime() - startTime;
}

///////////////////////////////////////////////////////////////////////
// Function				:	sfClearTemp
// Description			:	This callback function is used to remove the temporary files
// Return Value			:
// Comments				:
// Date last edited		:	7/4/2001
static int	rcClearTemp(const char *fileName,void *userData) {
	osDeleteFile(fileName);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	~CRendererContext
// Description			:	Dtor
// Return Value			:
// Comments				:
// Date last edited		:	8/25/2002
CRendererContext::~CRendererContext() {

	assert(renderer		== NULL);

	// In the case of an abnormal termination, clear the memory
	if (renderer != NULL) {
		delete renderer;
	}	

	////////////////////////////////////////////////////////////////////////////////////////////
	//
	//
	//			I N T E R F A C E			S H U T D O W N
	//
	//
	////////////////////////////////////////////////////////////////////////////////////////////
	if (keyTimes != NULL)			delete [] keyTimes;
	if (motionParameters != NULL)	delete [] motionParameters;


	////////////////////////////////////////////////////////////////////////////////////////////
	//
	//
	//			S T A T S			S H U T D O W N
	//
	//
	////////////////////////////////////////////////////////////////////////////////////////////
	stats.rendererTime	=	osCPUTime()	-	stats.rendererStartTime;

	////////////////////////////////////////////////////////////////////////////////////////////
	//
	//
	//			G R A P H I C S		S T A T E		S H U T D O W N
	//
	//
	////////////////////////////////////////////////////////////////////////////////////////////

	// Ditch the defined objects
	CArray<CObject *>	*CArray;
	CDSO				*cDso;

	// Ditch the DSO shaders that have been loaded
	for (cDso=dsos;cDso!=NULL;) {
		CDSO	*nDso	=	cDso->next;
		// Call DSO's cleanup
		if(cDso->cleanup != NULL) cDso->cleanup(cDso->handle);
		free(cDso->name);
		free(cDso->prototype);
		delete cDso;
		cDso	=	nDso;
	}

	// Ditch the temporary files created
	if (osFileExists(currentOptions->temporaryPath)) {
		char	tmp[OS_MAX_PATH_LENGTH];

		sprintf(tmp,"%s\\*",currentOptions->temporaryPath);
		osFixSlashes(tmp);
		osEnumerate(tmp,rcClearTemp,NULL);
		osDeleteDir(currentOptions->temporaryPath);
	}

	// Ditch the instance objects created
	for (CArray=allocatedInstances->pop();CArray!=NULL;CArray=allocatedInstances->pop()) {
		CObject	*cObject;

		for (cObject=CArray->first();cObject!=NULL;cObject=CArray->next()) {
			cObject->detach();
		}

		delete CArray;
	}
	delete allocatedInstances;

	// Delete the object stack
	assert(objectsStack				!=	NULL);
	assert(objectsStack->numItems	==	0);
	for (CArray=objectsStack->pop();CArray!= NULL;CArray=objectsStack->pop()) {
		CObject	*cObject;

		// Abnormal termination, force explicit object delete
		for (cObject=CArray->first();cObject!=NULL;cObject=CArray->next()) {
			delete cObject;
		}

		delete CArray;
	}
	delete objectsStack;
	
	// Ditch the current graphics state
	assert(currentOptions				!=	NULL);
	assert(currentXform					!=	NULL);
	assert(currentAttributes			!=	NULL);
	delete currentOptions;
	currentXform->detach();
	currentAttributes->detach();

	assert(savedXforms					!=	NULL);	
	assert(savedAttributes				!=	NULL);	
	assert(savedOptions					!=	NULL);	
	assert(savedXforms->numItems		==	0);
	assert(savedAttributes->numItems	==	0);
	assert(savedOptions->numItems		==	0);
	savedXforms->destroy();
	savedAttributes->destroy();
	savedOptions->destroy();

	assert(loadedFiles != NULL);
	loadedFiles->destroy();

	assert(declaredVariables != NULL);
	declaredVariables->destroy();
	
	// Delete the display channels
	assert(declaredChannels != NULL);
	assert(displayChannels != NULL);
	declaredChannels->destroy();
	delete displayChannels;

	assert(definedCoordinateSystems	!=	NULL);
	definedCoordinateSystems->destroy();
	
	assert(globalIdHash != NULL);
	globalIdHash->destroy();
	
	// Ditch temporary file and net file mappings
	
	if (frameTemporaryFiles != NULL) {
		frameTemporaryFiles->destroy();
	}
	
	if (netFileMappings != NULL) {
		netFileMappings->destroy();
	}

	// Cleanup the parser
	parserCleanup();

	// Network shutdown
	if (netClient != INVALID_SOCKET) {
		closesocket(netClient);
	}

	if (netNumServers != 0) {
		int	i;

		for (i=0;i<netNumServers;i++) {
			closesocket(netServers[i]);
		}

		delete [] netServers;
	}

	memoryTini();

	// Check the stats for memory leaks
	stats.check();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	getXform
// Description			:	Return the active Xform
// Return Value			:
// Comments				:
// Date last edited		:	8/25/2002
CXform		*CRendererContext::getXform(int modify) {
	assert(currentXform	!=	NULL);

	if ((modify) && (currentXform->refCount > 1)) {
		CXform	*nXform	=	new CXform(currentXform);

		currentXform->detach();
		currentXform	=	nXform;

		nXform->attach();
	}

	return currentXform;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	getAttributes
// Description			:	Return the active attributes
// Return Value			:
// Comments				:
// Date last edited		:	8/25/2002
CAttributes	*CRendererContext::getAttributes(int modify) {
	assert(currentAttributes	!=	NULL);

	if ((modify) && (currentAttributes->refCount > 1)) {
		CAttributes	*nAttributes	=	new CAttributes(currentAttributes);

		currentAttributes->detach();
		currentAttributes	=	nAttributes;

		nAttributes->attach();
	}

	return currentAttributes;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	getOptions
// Description			:	Return the active options
// Return Value			:
// Comments				:
// Date last edited		:	8/25/2002
COptions	*CRendererContext::getOptions() {
	assert(currentOptions	!=	NULL);

	return currentOptions;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	getShader
// Description			:	Create an instance of a shader
// Return Value			:
// Comments				:
// Date last edited		:	8/25/2002
CShaderInstance		*CRendererContext::getShader(const char *name,int type,int np,char **params,void **vals) {
	CShader			*cShader;
	CShaderInstance	*cInstance;
	CFileResource	*file;

	if (strcmp(name,"null") == 0)				return	NULL;

	if (strcmp(name,RI_DEFAULTSURFACE) == 0)	name	=	RI_MATTE;

	// Check if we already loaded this shader before ...
	cShader		=	NULL;
	cInstance	=	NULL;
	if (loadedFiles->find(name,file)) {
		cShader		=	(CShader *) file;
	}

	// If not found, search scripts
	if (cShader == NULL) {
		char	shaderLocation[OS_MAX_PATH_LENGTH];
		if (locateFileEx(shaderLocation,name,"sdr",currentOptions->shaderPath) == TRUE) {
			cShader	=	parseShader(name,shaderLocation);

			if (cShader != NULL) {
				loadedFiles->insert(cShader->name,cShader);
			}
		}
	}

	if (cShader != NULL) {
		CProgrammableShaderInstance	*instance;

		if (cShader->type != type) {
			error(CODE_NOSHADER,"Shader \"%s\" is not of the expected type\n",name);
			return NULL;
		}

		instance	= new CProgrammableShaderInstance(cShader,currentAttributes,currentXform);
		
		if (type == SL_LIGHTSOURCE) {
			// fill in lighting category
			instance->createCategories();
			
			// Add the new light into the active lights list for the frame
			if (renderer != NULL)	renderer->allLights->push(instance);
			else					currentOptions->allLights->push(instance);

		}

		assert(instance != NULL);

		// Execute the init code of the shader
		memBegin();
		init(instance);
		memEnd();

		cInstance	=	instance;
	}

	if (cInstance == NULL) {
		// Look into the hardcoded shaders
		if (strcmp(name,"spherelight") == 0) {
			cInstance	=	new CSphereLight(currentAttributes,currentXform);

			// Add the new light into the active lights list for the frame
			if (renderer != NULL)	renderer->allLights->push(cInstance);
			else					currentOptions->allLights->push(cInstance);
		} else if (strcmp(name,"quadlight") == 0) {
			cInstance	=	new CQuadLight(currentAttributes,currentXform);

			// Add the new light into the active lights list for the frame
			if (renderer != NULL)	renderer->allLights->push(cInstance);
			else					currentOptions->allLights->push(cInstance);
		}
	}

	// If not found, error out
	if (cInstance == NULL) {
		error(CODE_NOSHADER,"Unable to find shader \"%s\"\n",name);
		return NULL;
	}

	// Set the shader parameters
	cInstance->setParameters(np,params,vals);

	return	cInstance;
}



///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	getFilter
// Description			:	Return the filter matching the name
// Return Value			:
// Comments				:
// Date last edited		:	8/25/2002
RtFilterFunc			CRendererContext::getFilter(const char *name) {
	if (strcmp(name,RI_GAUSSIANFILTER) == 0) {
		return	RiGaussianFilter;
	} else if (strcmp(name,RI_BOXFILTER) == 0) {
		return	RiBoxFilter;
	} else if (strcmp(name,RI_TRIANGLEFILTER) == 0) {
		return	RiTriangleFilter;
	} else if (strcmp(name,RI_SINCFILTER) == 0) {
		return	RiSincFilter;
	} else if (strcmp(name,RI_CATMULLROMFILTER) == 0) {
		return	RiCatmullRomFilter;
	}

	return	RiGaussianFilter;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	getFilter
// Description			:	Return the name matching the filter
// Return Value			:
// Comments				:
// Date last edited		:	8/25/2002
char					*CRendererContext::getFilter(RtFilterFunc func) {
	if (func == RiGaussianFilter) {
		return	RI_GAUSSIANFILTER;
	} else if (func == RiBoxFilter) {
		return	RI_BOXFILTER;
	} else if (func == RiTriangleFilter) {
		return	RI_TRIANGLEFILTER;
	} else if (func == RiSincFilter) {
		return	RI_SINCFILTER;
	} else if (func == RiCatmullRomFilter) {
		return	RI_CATMULLROMFILTER;
	}

	return	RI_GAUSSIANFILTER;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	getDSO
// Description			:	Load a DSO matching the prototyoe
// Return Value			:
// Comments				:
// Date last edited		:	8/25/2002
int						CRendererContext::getDSO(char *name,char *prototype,void *&handle,dsoExecFunction &exec) {
	dsoInitFunction		init;
	dsoCleanupFunction	cleanup;
	CDSO				*cDso;

	// Check if the DSO had been loaded before
	for (cDso=dsos;cDso!=NULL;cDso=cDso->next) {
		if (strcmp(cDso->name,name) == 0) {
			if (strcmp(cDso->prototype,prototype) == 0) {
				handle	=	cDso->handle;
				exec	=	cDso->exec;
				return	TRUE;
			}
		}
	}

	// Load a DSO shader
	if (loadDSO(name,prototype,currentOptions->proceduralPath,&init,&exec,&cleanup) == TRUE) {
		// OK, we found the shader
		if (init !=	NULL)	handle	=	init(0,NULL);
		else				handle	=	NULL;

		// Save the DSO
		cDso			=	new CDSO;
		cDso->init		=	init;
		cDso->exec		=	exec;
		cDso->cleanup	=	cleanup;
		cDso->handle	=	handle;
		cDso->name		=	strdup(name);
		cDso->prototype	=	strdup(prototype);
		cDso->next		=	dsos;
		dsos			=	cDso;

		return TRUE;
	}

	return FALSE;
}



///////////////////////////////////////////////////////////////////////
// Function				:	screenArea
// Description			:	Compute the screen space area of a box
// Return Value			:	The area
// Comments				:
// Date last edited		:	10/11/2004
static	float	screenArea(COutput *output,CXform *x,const float *bmin,const float *bmax) {
	float	P[8*3];
	float	t,a;

	// Transform the points
	initv(P	+	0*3,bmin[0],bmin[1],bmin[2]);	mulmp(P + 0*3,x->from,P + 0*3);
	initv(P	+	1*3,bmin[0],bmax[1],bmin[2]);	mulmp(P + 1*3,x->from,P + 1*3);
	initv(P	+	2*3,bmax[0],bmax[1],bmin[2]);	mulmp(P + 2*3,x->from,P + 2*3);
	initv(P	+	3*3,bmax[0],bmin[1],bmin[2]);	mulmp(P + 3*3,x->from,P + 3*3);
	initv(P	+	4*3,bmin[0],bmin[1],bmax[2]);	mulmp(P + 4*3,x->from,P + 4*3);
	initv(P	+	5*3,bmin[0],bmax[1],bmax[2]);	mulmp(P + 5*3,x->from,P + 5*3);
	initv(P	+	6*3,bmax[0],bmax[1],bmax[2]);	mulmp(P + 6*3,x->from,P + 6*3);
	initv(P	+	7*3,bmax[0],bmin[1],bmax[2]);	mulmp(P + 7*3,x->from,P + 7*3);
	
	// Do the projection
	//output->camera2screen(8,P);
	output->camera2pixels(8,P);
	
	a		=	0;

#define	sumArea(__i1,__i2,__i3)																				\
	if ((P[__i1*3 + 2] > 0) && (P[__i2*3 + 2] > 0) && (P[__i3*3 + 2] > 0)) {								\
		if ((t = area(P[__i1*3+0],P[__i1*3+1],P[__i2*3+0],P[__i2*3+1],P[__i3*3+0],P[__i3*3+1])) > 0) {		\
			a	+=	t;																						\
		}																									\
	} else return C_INFINITY;

	sumArea(0,3,2);
	sumArea(0,2,1);
	sumArea(4,7,3);
	sumArea(4,3,0);
	sumArea(7,6,2);
	sumArea(7,2,3);
	sumArea(5,4,0);	
	sumArea(5,0,1);
	sumArea(6,5,1);
	sumArea(6,1,2);
	sumArea(5,6,7);
	sumArea(5,7,4);

#undef sumArea

	return (float) (a * 0.5);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	processDelayedObject
// Description			:	Process a delayed primitive
//							i.e. : Raytrace it or add it to the graphics state
// Return Value			:
// Comments				:
// Date last edited		:	8/25/2002
void		CRendererContext::processDelayedObject(CDelayedObject *cDelayed,void	(*subdivisionFunction)(void *,float),void *data,const float *bmin,const float *bmax,CRay *cRay) {
	CAttributes	*savedAttributes;
	CXform		*savedXform;
	float		area;

	assert(renderer		!=	NULL);


	// Restore the graphics state to the one at the delayed object instanciation
	savedAttributes		=	currentAttributes;
	savedXform			=	currentXform;
	currentAttributes	=	new CAttributes(cDelayed->attributes);	// Duplicate the graphics state of the delayed object
	currentXform		=	new CXform(cDelayed->xform);
	currentAttributes->attach();
	currentXform->attach();

	// Re-start the world
	renderer->beginWorld();

	// Execute the subdivision
	area				=	screenArea(renderer,cDelayed->xform,bmin,bmax);
	subdivisionFunction(data,area);

	// Restore the graphics state back
	currentAttributes->detach();									// Restore the graphics state of the delayed object
	currentXform->detach();
	currentAttributes	=	savedAttributes;
	currentXform		=	savedXform;

	// Remove the delayed primitive from the scene
	renderer->remove(cDelayed);

	// Update the raytracer
	renderer->endWorld();

	// If we're raytracing, check the ray against the children objects
	if (cRay != NULL) {
		renderer->retraceRay(cRay);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	addObject
// Description			:	Add an object into the scene
// Return Value			:
// Comments				:
// Date last edited		:	8/25/2002
void	CRendererContext::addObject(CObject *o) {
	assert(currentAttributes	!= NULL);
	assert(o					!= NULL);

	if (objects != NULL) {
		objects->push(o);
		return;
	}

	// Make sure we don't delete the object
	o->attach();

	if (renderer != NULL) {
		// Try to render the object
		assert(renderer != NULL);

		renderer->render(o);
	}

	// Processing is done
	o->detach();
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	addInstance
// Description			:	Add an instance of a compound object
// Return Value			:
// Comments				:
// Date last edited		:	8/25/2002
void	CRendererContext::addInstance(void *d) {
	CArray<CObject *>	*cInstance		=	(CArray<CObject *> *) d;
	CXform				*cXform			=	getXform(FALSE);
	CAttributes			*cAttributes	=	getAttributes(FALSE);
	int					i;
	int					numObjects		=	cInstance->numItems;
	CObject				**all			=	cInstance->array;

	if (currentOptions->flags & OPTIONS_FLAGS_INHERIT_ATTRIBUTES) {
		cAttributes	=	NULL;
	}

	// Instanciate the instance
	if (objects == NULL) {
		for (i=0;i<numObjects;i++) {
			all[i]->copy(cAttributes,cXform,this);
		}
	} else {
		CArray<CObject *>	*nInstance		=	new CArray<CObject *>;

		for (i=0;i<numObjects;i++) {
			all[i]->attach();
			nInstance->push(all[i]);
		}

		objects->push(new CObjectInstance(cAttributes,cXform,nInstance));
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	defineCoordinateSystem
// Description			:	Define a coordinate system
// Return Value			:
// Comments				:
// Date last edited		:	8/25/2002
void			CRendererContext::defineCoordinateSystem(const char *name,matrix &from,matrix &to,ECoordinateSystem type) {
	CNamedCoordinateSystem	*newEntry;
	
	assert(definedCoordinateSystems	!=	NULL);

	// Check if this system has been defined already
	if (definedCoordinateSystems->find(name,newEntry)) {
		// If the coordinate system existed before, just override
		movmm(newEntry->from,	from);
		movmm(newEntry->to,		to);
		newEntry->systemType	=	type;
	} else {
		newEntry				=	new CNamedCoordinateSystem;
		strcpy(newEntry->name,name);
		movmm(newEntry->from,	from);
		movmm(newEntry->to,		to);
		newEntry->systemType	=	type;
		definedCoordinateSystems->insert(newEntry->name,newEntry);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	findCoordinateSystem
// Description			:	Find a coordinate system
// Return Value			:	TRUE on success
// Comments				:
// Date last edited		:	8/25/2002
int		CRendererContext::findCoordinateSystem(const char *name,matrix *&from,matrix *&to,ECoordinateSystem &cSystem) {
	CNamedCoordinateSystem	*currentSystem;

	assert(definedCoordinateSystems	!=	NULL);

	if(definedCoordinateSystems->find(name,currentSystem)) {
		from		=	&currentSystem->from;
		to			=	&currentSystem->to;
		cSystem		=	currentSystem->systemType;

		switch(cSystem) {
			case COORDINATE_OBJECT:
				break;
			case COORDINATE_CAMERA:
				from	=	&identity;
				to		=	&identity;
				break;
			case COORDINATE_WORLD:
				if (renderer != NULL) {
					from	=	&renderer->world->from;
					to		=	&renderer->world->to;
					break;
				}
				
			case COORDINATE_SHADER:
				from	=	&currentXform->from;
				to		=	&currentXform->to;
				break;
			case COORDINATE_LIGHT:
			case COORDINATE_NDC:
			case COORDINATE_RASTER:
			case COORDINATE_SCREEN:
				break;
			case COORDINATE_CURRENT:
				from	=	&currentXform->from;
				to		=	&currentXform->to;
				break;
		}

		return	TRUE;
	}

	return	FALSE;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	declareVariable
// Description			:	Define a new variable
// Return Value			:	The new variable if successful, NULL otherwise
// Comments				:
// Date last edited		:	8/25/2002
CVariable		*CRendererContext::declareVariable(const char *name,const char *type,int marker) {
	CVariable	cVariable,*nVariable;

	assert(declaredVariables	!=	NULL);
	
	if (parseVariable(&cVariable,name,type)) {
		// Parse successful, insert the variable into the dictionary
		CVariable	*oVariable;

		if (declaredVariables->find(cVariable.name,oVariable)) {
			if (	(cVariable.numFloats	!=	oVariable->numFloats)	||
					(cVariable.numItems		!=	oVariable->numItems)) {
				error(CODE_SYSTEM,"Variable \"%s\" was previously defined differently\n",cVariable.name);
			} else {
				if (cVariable.type			!= oVariable->type) {
					if ((cVariable.type == TYPE_STRING) || (oVariable->type == TYPE_STRING)) {
						error(CODE_SYSTEM,"Variable \"%s\" was previously defined differently\n",cVariable.name);
					}
				}
			}

			// Overwrite the container
			oVariable->container			=	cVariable.container;

			// If we're overwriting "st" make sure to overwrite the s and t too
			if (oVariable->usageMarker == (PARAMETER_S | PARAMETER_T)) {
				if (declaredVariables->find("s",nVariable)) {
					nVariable->container	=	cVariable.container;
				} else	assert(FALSE);

				if (declaredVariables->find("t",nVariable)) {
					nVariable->container	=	cVariable.container;
				}  else	assert(FALSE);
			}

			return oVariable;
		}

		// Add the new variable into the variables list
		nVariable							=	new CVariable;
		nVariable[0]						=	cVariable;
		nVariable->next						=	variables;
		nVariable->usageMarker				=	marker;
		nVariable->defaultValue				=	NULL;
		nVariable->value					=	NULL;
		variables							=	nVariable;
		
		// Insert the variable into the variables trie
		declaredVariables->insert(nVariable->name,nVariable);

		// Make the variable global if it needs to be global
		if (nVariable->storage == STORAGE_GLOBAL) {
			makeGlobalVariable(nVariable);			
		}
		
		return nVariable;
	} else {
		return NULL;
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	makeGlobalVariable
// Description			:	Forcefully make a variable global
// Return Value			:
// Comments				:
// Date last edited		:	8/25/2002
void	CRendererContext::makeGlobalVariable(CVariable *var) {
	// Did we already start rendering ?
	var->entry		=	numGlobalVariables++;
	var->storage	=	STORAGE_GLOBAL;

	if (renderer != NULL) {
		renderer->updateState(var);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	retrieveVariable
// Description			:	Lookup a variable
// Return Value			:	The variable if found, NULL otherwise
// Comments				:
// Date last edited		:	8/25/2002
CVariable		*CRendererContext::retrieveVariable(const char *name) {
	CVariable					*cVariable;

	assert(declaredVariables	!=	NULL);

	if (declaredVariables->find(name,cVariable)) {
		return cVariable;
	}

	return NULL;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	getGlobalID
// Description			:	Map a string to a number globally
// Return Value			:	The ID
// Comments				:
// Date last edited		:	8/25/2002
int		CRendererContext::getGlobalID(const char *name) {
	CGlobalIdentifier	*cId;

	assert(globalIdHash	!=	NULL);

	if (!globalIdHash->find(name,cId)) {
		cId = new CGlobalIdentifier;
		cId->id = numKnownGlobalIds++;
		strcpy(cId->name,name);
		globalIdHash->insert(cId->name,cId);
	}

	return cId->id;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	declareDisplayChannel
// Description			:	Define a new displayChannel
// Return Value			:	The new display channel, NULL otherwise
// Comments				:
// Date last edited		:	08/02/2006
CDisplayChannel		*CRendererContext::declareDisplayChannel(const char *type) {
	CDisplayChannel *oChannel;
	CVariable		cVariable,*oVariable;
	
	assert(declaredChannels	!=	NULL);
	
	if (parseVariable(&cVariable,NULL,type) == FALSE) {
		return NULL;
	}
	
	if (declaredChannels->find(cVariable.name,oChannel) == TRUE) {
		if ((oChannel->numSamples == cVariable.numFloats) &&
			((cVariable.storage != STORAGE_GLOBAL) || oChannel->outType == cVariable.entry)) {
			return oChannel;
		} else {
			error(CODE_SYSTEM,"Channel \"%s\" was previously defined differently\n",cVariable.name);
			return NULL;
		}
	} else {
		oVariable = declareVariable(NULL,type);
		
		if (oVariable == NULL) {
			error(CODE_SYSTEM,"Channel definition \"%s\" is ill formed\n",type);
		} else {
			const int samples = oVariable->numFloats;
			const int outType = (oVariable->storage == STORAGE_GLOBAL) ? oVariable->entry : -1;
			oChannel = new CDisplayChannel(oVariable->name,oVariable,samples,-1,outType);
			declaredChannels->insert(oChannel->name,oChannel);
			displayChannels->push(oChannel);
			
			return oChannel;
		}
	}
	return NULL;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	declareDisplayChannel
// Description			:	Define a new displayChannel
// Return Value			:	The new display channel, NULL otherwise
// Comments				:
// Date last edited		:	08/02/2006
CDisplayChannel		*CRendererContext::declareDisplayChannel(CVariable *var) {
	CDisplayChannel *oChannel;
	
	assert(declaredChannels	!=	NULL);
	
	if (declaredChannels->find(var->name,oChannel) == TRUE) {
		if (oChannel->variable == var) {
			return oChannel;
		} else {
			return NULL;
		}
	} else {
		oChannel = new CDisplayChannel(var->name,var,var->numFloats,-1,var->entry);
		declaredChannels->insert(oChannel->name,oChannel);
		displayChannels->push(oChannel);
		
		return oChannel;
	}

	return NULL;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	retrieveDisplayChannel
// Description			:	Define a new displayChannel
// Return Value			:	The found display channel, NULL otherwise
// Comments				:
// Date last edited		:	08/02/2006
CDisplayChannel		*CRendererContext::retrieveDisplayChannel(const char *name) {
	CDisplayChannel *oChannel;
	if (declaredChannels->find(name,oChannel) == TRUE) {
		return oChannel;
	} else {
		return NULL;
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	resetDisplayChannelUsage
// Description			:	Mark all AOV channels as unused
// Return Value			:	
// Comments				:
// Date last edited		:	08/02/2006
void CRendererContext::resetDisplayChannelUsage() {
	int i,n = displayChannels->numItems;
	CDisplayChannel **dsp = displayChannels->array;
	
	for (i=0;i<n;i++,dsp++) {
		if ((*dsp)->variable != NULL) {
			(*dsp)->sampleStart = -1;
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	registerFrameTemporary
// Description			:	Register a file as a temporary
//						:	 Optionally register for deletion at frame-end
//						:	 certain files (namely those which are netrender temporaries)
//						:	 would otherwise be found in preference to the merged 
//						:	 client-side file, and must be removed before next frame.
// Return Value			:	
// Comments				:	Also removes any netFileMappings for the file
// Date last edited		:	08/02/2006
void CRendererContext::registerFrameTemporary(const char *name, int deleteFile) {
	char *tmp = new char[strlen(name)+2];
	tmp[0] = (deleteFile == TRUE) ? 1 : 0;
	strcpy(tmp+1,name);
	if (frameTemporaryFiles == NULL) {
		frameTemporaryFiles = new CArray<const char*>;
	}
	
	frameTemporaryFiles->push(tmp);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	locateFileEx
// Description			:	Locate a file on disk
// Return Value			:	TRUE if found
// Comments				:
// Date last edited		:	8/25/2002
int	CRendererContext::locateFileEx(char *result,const char *name,const char *extension,TSearchpath *searchpath) {
	if (strchr(name,'.') == NULL) {
		char	tmp[OS_MAX_PATH_LENGTH];

		sprintf(tmp,"%s.%s",name,extension);

		return locateFile(result,tmp,searchpath);
	} else {
		return locateFile(result,name,searchpath);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	locateFile
// Description			:	Locate a file on disk
// Return Value			:	TRUE if found
// Comments				:
// Date last edited		:	8/25/2002
int	CRendererContext::locateFile(char *result,const char *name,TSearchpath *searchpath) {

	if (netClient != INVALID_SOCKET) {
		// check netfile mappings
		CNetFileMapping* mapping;
		if (netFileMappings->find(name,mapping)) {
			name = mapping->to;
		}
	}
	
	// Check if the file exists
	if (osFileExists(name)) {
		strcpy(result,name);
		info(CODE_RESOLUTION,"\"%s\" -> \"%s\"\n",name,name);
		return TRUE;
	}

	// Search the directories
	if (searchpath == NULL) {

		if (strstr(name,"rib") != NULL) {
			searchpath	=	currentOptions->archivePath;

		} else if (strstr(name,"tif") != NULL) {
			searchpath	=	currentOptions->texturePath;

		} else if (strstr(name,"tiff") != NULL) {
			searchpath	=	currentOptions->texturePath;
		
		} else if (strstr(name,"tex") != NULL) {
			searchpath	=	currentOptions->texturePath;
		
		} else if (strstr(name,"tx") != NULL) {
			searchpath	=	currentOptions->texturePath;
		
		} else if (strstr(name,"ptc") != NULL) {
			searchpath	=	currentOptions->texturePath;
		
		} else if (strstr(name,"bm") != NULL) {
			searchpath	=	currentOptions->texturePath;
			
		} else if (strstr(name,"sdr") != NULL) {
			searchpath	=	currentOptions->shaderPath;

		} else if (strstr(name,osModuleExtension) != NULL) {
			searchpath	=	currentOptions->proceduralPath;
		}
	}

	for (;searchpath!=NULL;searchpath=searchpath->next) {
		sprintf(result,"%s%s",searchpath->directory,name);
		osFixSlashes(result);
		if (osFileExists(result)) {
			info(CODE_RESOLUTION,"\"%s\" -> \"%s\"\n",name,result);
			return TRUE;
		}
	}

	// Unable to find the file, check the network
	// Check the net if we can find the file
	if (netClient != INVALID_SOCKET) {
		if (getFile(result,name) == TRUE) {
			if (osFileExists(result)) {
				info(CODE_RESOLUTION,"\"%s\" -> \"%s\"\n",name,result);
				return TRUE;
			}
		}
	}

	info(CODE_RESOLUTION,"\"%s\" -> ???\n",name);

	return FALSE;
}



///////////////////////////////////////////////////////////////////////
// Function				:	netName
// Description			:	Lookup the name of a socket and return it's address
// Return Value			:	TRUE on success, FALSE otherwise
// Comments				:
// Date last edited		:	6/24/2002
static	int		netName(sockaddr_in *address,char *name) {
	int					port;
	struct	hostent		*hp			=	NULL;
	char				*portMarker;
	char				tmp[256];

	if (name == NULL) {
		gethostname(tmp,256);
		name	=	tmp;
	} else {
		// Make a local copy of the address
		strcpy(tmp,name);
		name	=	tmp;
	}

	portMarker						=	strchr(name,':');

	// Try to read off the port
	if (portMarker == NULL)	port	=	DEFAULT_PORT;
	else {
		if (sscanf(portMarker,":%d",&port) != 1) {
			port	=	DEFAULT_PORT;
		}

		*portMarker	=	'\0';
	}

	if (isalpha(name[0])) {
		hp = gethostbyname(name);
	} else  {
		unsigned int addr = inet_addr(name);
		hp = gethostbyaddr((char *)&addr,4,AF_INET);
	}

	if (hp == NULL)	return	TRUE;

	address->sin_family		= hp->h_addrtype;
	memcpy((char *) &address->sin_addr.s_addr, hp->h_addr_list[0], hp->h_length);
	address->sin_port = htons((short) port);

	return	FALSE;
}

#ifdef WIN32
#define netError() {									\
		int		lastErrorNumber;						\
		char	*lastError;								\
														\
		lastErrorNumber	=	WSAGetLastError();			\
		switch(lastErrorNumber) {						\
		case WSANOTINITIALISED:							\
			lastError	=	"WSANOTINITIALISED";		\
			break;										\
		case WSAENETDOWN:								\
			lastError	=	"WSAENETDOWN";				\
			break;										\
		case WSAEFAULT:									\
			lastError	=	"WSAEFAULT";				\
			break;										\
		case WSAEINTR:									\
			lastError	=	"WSAEINTR";					\
			break;										\
		case WSAEINPROGRESS:							\
			lastError	=	"WSAEINPROGRESS";			\
			break;										\
		case WSAEINVAL:									\
			lastError	=	"WSAEINVAL";				\
			break;										\
		case WSAEMFILE:									\
			lastError	=	"WSAEMFILE";				\
			break;										\
		case WSAENOBUFS:								\
			lastError	=	"WSAENOBUFS";				\
			break;										\
		case WSAENOTSOCK:								\
			lastError	=	"WSAENOTSOCK";				\
			break;										\
		case WSAEOPNOTSUPP:								\
			lastError	=	"WSAEOPNOTSUPP";			\
			break;										\
		case WSAEWOULDBLOCK:							\
			lastError	=	"WSAEWOULDBLOCK";			\
			break;										\
		case WSAENOTCONN:								\
			lastError	=	"WSAENOTCONN";				\
			break;										\
		case WSAENETRESET:								\
			lastError	=	"WSAENETRESET";				\
			break;										\
		case WSAESHUTDOWN:								\
			lastError	=	"WSAESHUTDOWN";				\
			break;										\
		case WSAEMSGSIZE:								\
			lastError	=	"WSAEMSGSIZE";				\
			break;										\
		case WSAECONNABORTED:							\
			lastError	=	"WSAECONNABORTED";			\
			break;										\
		case WSAETIMEDOUT:								\
			lastError	=	"WSAETIMEDOUT";				\
			break;										\
		case WSAECONNRESET:								\
			lastError	=	"WSAECONNRESET";			\
			break;										\
		case WSAEADDRINUSE:								\
			lastError	=	"WSAEADDRINUSE";			\
			break;										\
		case WSAEALREADY:								\
			lastError	=	"WSAEALREADY";				\
			break;										\
		case WSAEADDRNOTAVAIL:							\
			lastError	=	"WSAEADDRNOTAVAIL";			\
			break;										\
		case WSAEAFNOSUPPORT:							\
			lastError	=	"WSAEAFNOSUPPORT";			\
			break;										\
		case WSAECONNREFUSED:							\
			lastError	=	"WSAECONNREFUSED";			\
			break;										\
		case WSAEISCONN:								\
			lastError	=	"WSAEISCONN";				\
			break;										\
		case WSAENETUNREACH:							\
			lastError	=	"WSAENETUNREACH";			\
			break;										\
		case WSAEACCES:									\
			lastError	=	"WSAEACCES";				\
			break;										\
		default:										\
			lastError	=	"Unknown";					\
			break;										\
		}												\
														\
		error(CODE_SYSTEM,"NET ERROR: %s\n",lastError);	\
}
#else
#define	netError() error(CODE_SYSTEM,"NET ERROR : %s\n",strerror(errno));
#endif

///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	sendFile
// Description			:	Send a file over the network to the server
// Return Value			:
// Comments				:
// Date last edited		:	8/25/2002
void				CRendererContext::sendFile(int index,char *fileToSend,int start,int size) {
	FILE	*in	=	fopen(fileToSend,"rb");

	if (in != NULL) {
		char	buffer[BUFFER_LENGTH];
		int		csize;
		T32		netBuffer[1];

		// Tell the server that we found the file
		netBuffer[0].integer	=	NET_ACK;
		rcSend(netServers[index],(char *) netBuffer,sizeof(T32));

		// Get the size of the file to send
		if (size == 0) {
			int	totalSize;
			
			fseek(in,0,SEEK_END);
			totalSize	=	ftell(in);

			size		=	totalSize - start;
		}

		// Tell the server the length of the file
		netBuffer[0].integer	=	size;
		rcSend(netServers[index],(char *) netBuffer,sizeof(T32));

		// Transfer the file
		fseek(in,start,SEEK_SET);
		for (csize=size;csize>0;csize-=BUFFER_LENGTH) {
			fread(buffer,min(csize,BUFFER_LENGTH),sizeof(char),in);
			rcSend(netServers[index],buffer,min(csize,BUFFER_LENGTH),FALSE);
		}

		fclose(in);
	} else {
		T32		netBuffer[1];

		// File could not be found
		netBuffer[0].integer	=	NET_NACK;
		rcSend(netServers[index],(char *) netBuffer,sizeof(T32));
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	sfGetFile
// Description			:	Get a portion of a file
// Return Value			:	The size received
// Comments				:
// Date last edited		:	7/4/2001
int			CRendererContext::getFile(FILE *file,const char *inName,int start,int size) {
	T32		*buffer;
	int		i			=	strlen(inName);
	int		r;

	// Compute the file name length
	i					=	(i / sizeof(T32))+2;

	// Allocate tmp space
	memBegin();

	buffer				=	(T32 *) ralloc((i+4)*sizeof(T32));

	buffer[0].integer	=	NET_SEND_FILE;
	buffer[1].integer	=	start;
	buffer[2].integer	=	size;
	buffer[3].integer	=	i*sizeof(T32);

	// Send the file request
	rcSend(netClient,(char *) buffer,4*sizeof(T32));

	// Send the file name
	strcpy(&buffer[0].character,inName);
	rcSend(netClient,(char *) buffer,i*sizeof(T32),FALSE);

	rcRecv(netClient,(char *) buffer,1*sizeof(T32));
	if (buffer->integer == NET_NACK) {
		r	=	0;
	} else {
		int		tsize,csize;
		char	buf[BUFFER_LENGTH];

		// Get the size of the file first
		rcRecv(netClient,(char *) &tsize,sizeof(int));

		// Write down the file
		for (csize=tsize;csize>0;csize-=BUFFER_LENGTH) {
			rcRecv(netClient,buf,min(BUFFER_LENGTH,csize),FALSE);
			fwrite(buf,min(BUFFER_LENGTH,csize),sizeof(char),file);
		}

		r	=	tsize;
	}

	memEnd();

	return r;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	getFile
// Description			:	Receive a file over the network from the client
// Return Value			:
// Comments				:
// Date last edited		:	8/25/2002
int			CRendererContext::getFile(char *outName,const char *inName) {
	FILE	*out;
	int		result	=	FALSE;

	if (!osFileExists(currentOptions->temporaryPath)) {
		osCreateDir(currentOptions->temporaryPath);
	}

	osTempname(currentOptions->temporaryPath,"rndr",outName);
	CNetFileMapping *mapping = new CNetFileMapping(inName,outName);
	netFileMappings->insert(mapping->from,mapping);

	out	=	fopen(outName,"wb");

	if (out != NULL) {
		if (getFile(out,inName) > 0) {
			result	=	TRUE;
		} else {
			error(CODE_SYSTEM,"Unable to download file %s\n",inName);
		}

		fclose(out);
	} else {
		error(CODE_SYSTEM,"Unable to create file %s\n",outName);
	}

	return result;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	netSetup
// Description			:	Setup the network connections
// Return Value			:
// Comments				:
// Date last edited		:	8/25/2002
void		CRendererContext::netSetup(char *ribFile,char *riNetString) {
	char		*tmp		=	riNetString;
	sockaddr_in	me;
	SOCKET		control;

	netClient			=	INVALID_SOCKET;
	netNumServers		=	0;
	netServers			=	NULL;

	if (tmp == NULL)	return;

#ifdef WIN32
	WSADATA wsaData;

	// Init the winsock
	if (WSAStartup(0x202,&wsaData) == SOCKET_ERROR) {
		WSACleanup();
		fatal(CODE_SYSTEM,"Winsock init error\n");
	}
#endif


	// Decide what we are e.g., server/client
	if (strncmp(tmp,"client=",7) == 0) {
		T32	netBuffer[4];

		tmp	+=	7;

		// Just read the client port number
		sscanf(tmp,"%d",&netClient);

		// Figure out the version junk
		rcRecv(netClient,(char *) netBuffer,4*sizeof(T32));

		// Check the message
		if (netBuffer[0].integer != NET_CONNECT) {
			fatal(CODE_SYSTEM,"Unrecognised startup sequence from the client\n");
		}

		// Check the version
		if (	(	netBuffer[1].integer	!=	VERSION_RELEASE)	||
				(	netBuffer[2].integer	!=	VERSION_BETA)) {
			netBuffer[0].integer	=	NET_NACK;
			fatal(CODE_SYSTEM,"Version mismatch with the client\n");
		} else {
			netBuffer[0].integer	=	NET_ACK;
			info(CODE_LOG,"Accepted incoming connection\n");
		}

		// Accept or decline the connection
		rcSend(netClient,(char *) netBuffer,sizeof(T32));
	} else if ((strncmp(tmp,"servers=",8) == 0) || (strncmp(tmp,"killservers=",12) == 0)) {
		socklen_t	servLen		=	sizeof(sockaddr_in);
		sockaddr_in	serv;
		char		*marker;
		char		hostName[1024];
		char		temporary[32];
		hostent 	*hostinfo;
		socklen_t	myLength	=	sizeof(me);
		int			port;
		T32			netBuffer[4];
		int			killservers = FALSE,tmpOffset;

		if (*tmp == 'k') {
			tmp			+=	(tmpOffset=12);
			killservers =	TRUE;
		} else {
			tmp 		+=	(tmpOffset=8);
		}

		// Create the socket
		control = socket(AF_INET, SOCK_STREAM, 0);
		if (control == INVALID_SOCKET) {
			fatal(CODE_SYSTEM,"Socket error\n");
		}

		// Bind to the port
		me.sin_family		= AF_INET;
		me.sin_addr.s_addr	= htonl(INADDR_ANY);
		me.sin_port			= htons(0);
		if (bind(control, (struct sockaddr *) &me, sizeof(me)) < 0) {
			fatal(CODE_SYSTEM,"Bind error\n");
		}


		// Resolve the name of the host
		getsockname(control,(sockaddr *) &me,&myLength);
		port				=	me.sin_port;

		if(gethostname(hostName,sizeof(hostName)) == 0) {
			if((hostinfo = gethostbyname(hostName)) != NULL) {
				strcpy(hostName,inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list));
			}
		}

		// Save the name of the host
		sprintf(temporary,":%d",port);
		strcat(hostName,temporary);

		// Count the number of servers
		netNumServers		=	0;
		while((marker = strchr(tmp,',')) != NULL) {
			netNumServers++;
			tmp	=	marker+1;
		}
		tmp					=	riNetString+tmpOffset;
		netNumServers++;

		netServers			=	new SOCKET[netNumServers];
		netNumServers		=	0;

		// Try to connect to the servers
		while((marker = strchr(tmp,',')) != NULL) {
			*marker++	=	'\0';

			if (killservers) {
				// We are killing other servers
				if (netName(&serv,tmp) == FALSE) {
					if (connect(control,(sockaddr *) &serv,servLen) == 0) {
						send(control," quit",6,0);	// send a quit message
						
						// Create a new control socket
						closesocket(control);
						control = socket(AF_INET, SOCK_STREAM, 0);
						if (control == INVALID_SOCKET) {
							fatal(CODE_SYSTEM,"Socket error\n");
						}
					}
				}
			} else if (netName(&serv,tmp) == FALSE) {
				if (connect(control,(sockaddr *) &serv,servLen) == 0) {
					// Ensure there's no delay on network transactions
					int val = 1;
					setsockopt(control,IPPROTO_TCP,TCP_NODELAY,(const char *) &val,sizeof(int));
					
					// The following sequence will be processed by RNDR
					send(control,ribFile,strlen(ribFile)+1,0);		// Send the name of the rib file
					recv(control,(char *) netBuffer,sizeof(T32),0);		// Expect an ACK

					// Try to establist the connection
					netBuffer[0].integer	=	NET_CONNECT;
					netBuffer[1].integer	=	VERSION_RELEASE;
					netBuffer[2].integer	=	VERSION_BETA;
					netBuffer[3].integer	=	VERSION_ALPHA;
					rcSend(control,(char *) netBuffer,4*sizeof(T32));	// Send the client version
					rcRecv(control,(char *) netBuffer,1*sizeof(T32));	// Expect an ACK

					if (netBuffer[0].integer == NET_ACK) {
						// Connection is successful
						netServers[netNumServers++]	=	control;

						info(CODE_LOG,"Connected to %s\n",tmp);
					} else {
						info(CODE_SYSTEM,"Version mismatch with server %s\n",tmp);
						closesocket(control);
					}

					// Create a new control socket
					control = socket(AF_INET, SOCK_STREAM, 0);
					if (control == INVALID_SOCKET) {
						fatal(CODE_SYSTEM,"Socket error\n");
					}

					// Bind to the port
					me.sin_family		= AF_INET;
					me.sin_addr.s_addr	= htonl(INADDR_ANY);
					me.sin_port			= htons(0);
					if (bind(control, (struct sockaddr *) &me, sizeof(me)) < 0) {
						fatal(CODE_SYSTEM,"Bind error\n");
					}
				} else {
					netError();
					error(CODE_SYSTEM,"Unable to connect to %s\n",tmp);
				}
			} else {
				netError();
				error(CODE_SYSTEM,"Unable to resolve %s\n",tmp);
			}

			tmp	=	marker;
		}

		if (killservers) {
			// We are killing other servers
			if (netName(&serv,tmp) == FALSE) {
				if (connect(control,(sockaddr *) &serv,servLen) == 0) {
					send(control," quit",6,0);	// send a quit message
					
					control	=	INVALID_SOCKET;
				}
			}
		} else if (netName(&serv,tmp) == FALSE) {
			if (connect(control,(sockaddr *) &serv,servLen) == 0) {
				// Ensure there's no delay on network transactions
				int val = 1;
				setsockopt(control,IPPROTO_TCP,TCP_NODELAY,(const char *) &val,sizeof(int));
			
				// The following sequence will be processed by RNDR
				send(control,ribFile,strlen(ribFile)+1,0);		// Send the name of the rib file
				recv(control,(char *) netBuffer,sizeof(T32),0);		// Expect an ACK

				// Try to establist the connection
				netBuffer[0].integer	=	NET_CONNECT;
				netBuffer[1].integer	=	VERSION_RELEASE;
				netBuffer[2].integer	=	VERSION_BETA;
				netBuffer[3].integer	=	VERSION_ALPHA;
				rcSend(control,(char *) netBuffer,4*sizeof(T32));	// Send the client version
				rcRecv(control,(char *) netBuffer,1*sizeof(T32));	// Expect an ACK

				if (netBuffer[0].integer == NET_ACK) {
					// Connection is successful
					netServers[netNumServers++]	=	control;

					info(CODE_LOG,"Connected to %s\n",tmp);
				} else {
					error(CODE_SYSTEM,"Version mismatch with server %s\n",tmp);
					closesocket(control);
				}

				control	=	INVALID_SOCKET;
			} else {
				netError();
				error(CODE_SYSTEM,"Unable to connect to %s\n",tmp);
			}
		} else {
			netError();
			error(CODE_SYSTEM,"Unable to resolve %s\n",tmp);
		}
	} else if (strncmp(tmp,"locclient=",10) == 0) {
		tmp += 10;
		
		// Note that we do not check the client version (it's the same binary)
		
		// Just read the client port number
		sscanf(tmp,"%d",&netClient);
	} else if (strncmp(tmp,"locservers=",11) == 0) {
		char		*marker;
		
		tmp += 11;
		
		// Note that we do not check the server versions
		
		// Count up the servers
		while((marker = strchr(tmp,',')) != NULL) {
			netNumServers++;
			tmp	=	marker+1;
		}
		netNumServers++;
		tmp		=	riNetString+11;
		
		// Allocate our arrays
		netServers			=	new SOCKET[netNumServers];
		netNumServers		=	0;
		
		// Now actually parse them
		while((marker = strchr(tmp,',')) != NULL) {
			sscanf(tmp,"%d",&netServers[netNumServers]);
			netNumServers++;
			
			tmp	=	marker+1;
		}
		sscanf(tmp,"%d",&netServers[netNumServers]);
		netNumServers++;
	} else {
		error(CODE_BUG,"Unknown net string %s\n",tmp);
	}
}




///////////////////////////////////////////////////////////////////////
// Function				:	dispatcherThread
// Description			:	This thread is responsible for dispatching needed buckets
//							the servers
// Return Value			:
// Comments				:
// Date last edited		:	11/28/2001
static	void		*dispatcherThread(void *w) {
	currentRenderer->rendererThread(w);

	return NULL;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	rendererThread
// Description			:	This function actually manages the servers
// Return Value			:
// Comments				:
// Date last edited		:	8/25/2002
void		CRendererContext::rendererThread(void *w) {
	int		index			=	(int) w;	// This is the server index, 1 thread for every server
	int		done			=	FALSE;
	T32		netBuffer[3];
	int		x,y,nx,ny;

	// Make sure the server needs all the files it needs
	while(TRUE) {

		// Expect the ready message
		rcRecv(netServers[index],(char *) netBuffer,1*sizeof(T32));

		if (netBuffer[0].integer == NET_READY)	break;

		// Server needs something, process the request
		processServerRequest(netBuffer[0],index);
	}

	// At this point, the server should be ready to render...

	// Dispatch buckets
	x	=	-1;
	y	=	-1;
	while(done==FALSE){
		T32		header[5];
		float	*buffer;

		// Find the needed bucket
		osDownMutex(commitMutex);

		// Get the current bucket and advance the bucket
		if (renderer->advanceBucket(index,x,y,nx,ny) == FALSE) {
			done	=	TRUE;
		}

		// Release the bucket
		osUpMutex(commitMutex);

		if (done == FALSE) {

			// Dispatch the job
			netBuffer[0].integer	=	NET_RENDER_BUCKET;
			netBuffer[1].integer	=	x;
			netBuffer[2].integer	=	y;
			rcSend(netServers[index],(char *) netBuffer,3*sizeof(T32));

			while(TRUE) {
				// Expect the ready message
				rcRecv(netServers[index],(char *) netBuffer,1*sizeof(T32));

				if (netBuffer[0].integer == NET_READY)	break;

				// Server needs something, process the request
				processServerRequest(netBuffer[0],index);
			}

			// Receive the result
			rcRecv(netServers[index],(char *) &header,5*sizeof(T32));		// Receive the response header
			rcSend(netServers[index],(char *) &netBuffer,1*sizeof(T32));	// Echo the message back

			buffer					=	new float[header[4].integer];
																			// Receive the framebuffer
			rcRecv(netServers[index],(char *) buffer,header[4].integer*sizeof(T32));

			// Commit the bucket
			osDownMutex(commitMutex);
			
			renderer->commit(header[0].integer,header[1].integer,header[2].integer,header[3].integer,buffer);
			renderer->recvBucketDataChannels(netServers[index],x,y);
	
			numNetrenderedBuckets++;
			stats.progress		=	(numNetrenderedBuckets*100) / (float) (nx*ny);
			if (renderer->flags & OPTIONS_FLAGS_PROGRESS)	info(CODE_PROGRESS,"Done %%%3.2f\r",stats.progress);
			
			osUpMutex(commitMutex);

			delete[] buffer;
		}

		if(done == TRUE){
			// We finished rendering this frame
			// Advance the server to the next frame
			netBuffer[0].integer	=	NET_FINISH_FRAME;
			netBuffer[1].integer	=	0;
			netBuffer[2].integer	=	0;
			rcSend(netServers[index],(char *) netBuffer,3*sizeof(T32));
			rcRecv(netServers[index],(char *) netBuffer,1*sizeof(T32));	// Expect ACK
			
			osDownMutex(commitMutex);
			
			renderer->recvFrameDataChannels(netServers[index]);
	
			stats.progress	=	100;
			if (renderer->flags & OPTIONS_FLAGS_PROGRESS)	info(CODE_PROGRESS,"Done               \r");

			osUpMutex(commitMutex);
		}
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	clientRenderFrame
// Description			:	We're a client, so spawn a thread to guide each server
// Return Value			:
// Comments				:
// Date last edited		:	8/25/2002
void		CRendererContext::clientRenderFrame() {
	int			i;
	TThread		*threads;

	// Create the mutexes
	osCreateMutex(commitMutex);

	threads	=	(TThread *) alloca(netNumServers*sizeof(TThread));

	// Spawn the threads
	for (i=0;i<netNumServers;i++) {
		threads[i]	=	osCreateThread(dispatcherThread,(void *) i);
	}

	// Go to sleep until we're done
	for (i=0;i<netNumServers;i++) {
		osWaitThread(threads[i]);
	}

	// Ditch the mutexes
	osDeleteMutex(commitMutex);

	// If restart if necessary
	numNetrenderedBuckets = 0;
	for (i=0;i<netNumServers;i++) {
		T32	netBuffer;
		netBuffer.integer	=	NET_READY;
		rcSend(netServers[i],(char *) &netBuffer,sizeof(T32));
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	processServerRequest
// Description			:	Process a server request
// Return Value			:	-
// Comments				:
// Date last edited		:	8/25/2002
void			CRendererContext::processServerRequest(T32 req,int index) {
	if (req.integer == NET_SEND_FILE) {
		// The server is missing a file, so send it over
		char		*fileName;
		char		fileLocation[OS_MAX_PATH_LENGTH];
		int			start,size;
		int			nameLength;
		T32			buffer[3];
		TSearchpath	*search;

		// Receive the length of the fileName
		rcRecv(netServers[index],(char *) buffer,3*sizeof(T32));
		start		=	buffer[0].integer;
		size		=	buffer[1].integer;
		nameLength	=	buffer[2].integer;

		fileName	=	(char *) alloca(nameLength);
		rcRecv(netServers[index],(char *) fileName,nameLength,FALSE);
		
		// Figure out what type of file it is
		if (strstr(fileName,".sdr") != NULL)		search	=	currentOptions->shaderPath;
		else if (strstr(fileName,".dll") != NULL)	search	=	currentOptions->proceduralPath;
		else if (strstr(fileName,".so") != NULL)	search	=	currentOptions->proceduralPath;
		else if (strstr(fileName,".rib") != NULL)	search	=	currentOptions->archivePath;
		else if (strstr(fileName,".tif") != NULL)	search	=	currentOptions->texturePath;
		else if (strstr(fileName,".tiff") != NULL)	search	=	currentOptions->texturePath;
		else if (strstr(fileName,".tex") != NULL)	search	=	currentOptions->texturePath;
		else if (strstr(fileName,".tx") != NULL)	search	=	currentOptions->texturePath;
		else if (strstr(fileName,".ptc") != NULL)	search	=	currentOptions->texturePath;
		else if (strstr(fileName,".bm") != NULL)	search	=	currentOptions->texturePath;
		else										search	=	NULL;

		if (locateFile(fileLocation,fileName,search)) {
			sendFile(index,fileLocation,start,size);
		} else {
			// Unable to find file
			T32	response;

			response.integer	=	NET_NACK;
			rcSend(netServers[index],(char *) &response,sizeof(T32));
		}
	} else if (req.integer == NET_CREATE_CHANNEL) {
		// This must be atomic
		osDownMutex(commitMutex);
		renderer->processChannelRequest(index,netServers[index]);
		osUpMutex(commitMutex);
	} else {
		error(CODE_BUG,"Unknown server request\n");
	}
}


///////////////////////////////////////////////////////////////////////
// Function				:	dsoLoadCallback
// Description			:	This function will be called for each module
// Return Value			:
// Comments				:
// Date last edited		:	7/30/2002
static	int	dsoLoadCallback(const char *file,void *ud) {
	void	*module		=	osLoadModule(file);

	if (module != NULL) {
		int				i;
		void			**userData	=	(void **) ud;
		char			*name		=	(char *) userData[0];
		char			*prototype	=	(char *) userData[1];
		SHADEOP_SPEC	*shadeops;

		{
			char	tmp[OS_MAX_PATH_LENGTH];

			sprintf(tmp,"%s_shadeops",name);

			shadeops	=	(SHADEOP_SPEC *)	osResolve(module,tmp);
		}

		if (shadeops != NULL) {
			for (i=0;;i++) {
				char	*dsoName,*dsoPrototype;

				if (strcmp(shadeops[i].definition,"") == 0)	break;

				if (dsoParse(shadeops[i].definition,dsoName,dsoPrototype) == TRUE) {
					if (strcmp(dsoPrototype,prototype) == 0) {
						dsoInitFunction		*init		=	(dsoInitFunction *) userData[2];
						dsoExecFunction		*exec		=	(dsoExecFunction *) userData[3];
						dsoCleanupFunction	*cleanup	=	(dsoCleanupFunction *) userData[4];

						// Bingo
						init[0]		=	(dsoInitFunction)		osResolve(module,shadeops[i].init);
						exec[0]		=	(dsoExecFunction)		osResolve(module,dsoName);
						cleanup[0]	=	(dsoCleanupFunction)	osResolve(module,shadeops[i].cleanup);

						if (exec != NULL) {
							free(dsoName);
							free(dsoPrototype);

							// We have found the DSO
							return FALSE;
						}
					}

					free(dsoName);
					free(dsoPrototype);
				}
			}
		}

		osUnloadModule(module);
	} else {
		error(CODE_SYSTEM,"Unable to load dso %s (error %s)\n",file,osModuleError());
	}

	// Continue iterating
	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	loadDSO
// Description			:	Find and load a DSO shader
// Return Value			:	-
// Comments				:
// Date last edited		:	8/25/2002
int			CRendererContext::loadDSO(char *name,char *prototype,TSearchpath *inPath,dsoInitFunction *init,dsoExecFunction *exec,dsoCleanupFunction *cleanup) {
	void	*userData[5];
	char	searchPath[OS_MAX_PATH_LENGTH];

	*init		=	NULL;
	*exec		=	NULL;
	*cleanup	=	NULL;

	userData[0]	=	name;
	userData[1]	=	prototype;
	userData[2]	=	init;
	userData[3]	=	exec;
	userData[4]	=	cleanup;

	// Go over the directories
	for (;inPath!=NULL;inPath=inPath->next) {
		sprintf(searchPath,"%s*.%s",inPath->directory,osModuleExtension);
		osEnumerate(searchPath,dsoLoadCallback,userData);
	}

	if (exec[0] == NULL)	return FALSE;

	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// Function				:	rcSend
// Description			:	Send data on the network
// Return Value			:
// Comments				:
// Date last edited		:	7/4/2001
void			rcSend(SOCKET s,char *data,int n,int toNetwork) {
	int	i,j;

	if (toNetwork) {
		T32	*buf	=	(T32 *) data;

		for (i=n>>2;i>0;i--,buf++) {
			buf->integer	=	htonl(buf->integer);
		}
	}

	j	= n;
	i	= send(s,data,j,0);

	if (i <= 0) {
		fatal(CODE_SYSTEM,"Connection broken\n");
	}

	// If we could not send the entire data, send the rest
	while(i < j) {
		data	+=	i;
		j		-=	i;

		i		= send(s,data,j,0);
		
		if (i <= 0) {
			fatal(CODE_SYSTEM,"Connection broken\n");
			break;
		}
	}


	stats.totalNetSend	+=	n;
}

///////////////////////////////////////////////////////////////////////
// Function				:	rcRecv
// Description			:	Receive data from network
// Return Value			:
// Comments				:
// Date last edited		:	7/4/2001
void			rcRecv(SOCKET s,char *data,int n,int toNetwork) {
	int	i,j;
	T32	*buf = (T32 *) data;

	j	= n;
	i	= recv(s,data,j,0);

	if (i <= 0) {
		fatal(CODE_SYSTEM,"Connection broken\n");
	}

	while(i < j) {
		data	+=	i;
		j		-=	i;

		i		=	recv(s,data,j,0);
	
		if (i <= 0) {
			fatal(CODE_SYSTEM,"Connection broken\n");
			break;
		}
	}

	if (toNetwork) {
		for (i=n>>2;i>0;i--,buf++) {
			buf->integer	=	ntohl(buf->integer);
		}
	}

	stats.totalNetRecv	+=	n;
}














///////////////////////////////////////////////////////////////////////
// Function				:	addMotion
// Description			:	Make sure the command is good to go
// Return Value			:	The processing type (see below)
// Comments				:
// Date last edited		:	8/7/2001
//	0	-	skip
//	1	-	process single
//	2	-	process double
int		CRendererContext::addMotion(float *parameters,int parameterSize,char *name,float *&p0,float *&p1) {
	if (numExpectedMotions == 1)	{
		p0	=	parameters;
		return	1;
	}

	// Make sure we have enough memory to hold motion parameters
	if ((parameterSize*numExpectedMotions) > maxMotionParameters) {
		if (motionParameters != NULL) delete [] motionParameters;

		maxMotionParameters	=	parameterSize*numExpectedMotions;
		motionParameters	=	new float[maxMotionParameters];
	}

	// Sanity check
	if (numMotions == 0) {
		lastCommand			=	name;
	} else {
		if (numMotions >= numExpectedMotions) {
			error(CODE_NESTING,"%s: Too many motions in motion block.\n",name);
			return 0;
		}

		if (lastCommand != name) {
			error(CODE_NESTING,"%s: Different commands in motion block.\n",name);
			return 0;
		}
	}

	memcpy(motionParameters+parameterSize*numMotions,parameters,parameterSize*sizeof(float));
	numMotions++;

	if (numExpectedMotions == numMotions) {
		int			i;

		p0						=	motionParameters;
		p1						=	&motionParameters[parameterSize*(numMotions-1)];

		// Interpolate the motion parameters between the shutter open and shutter close
		for (i=0;i<parameterSize;i++) {
			float	s,e,d;

			d		=	(p1[i] - p0[i]) / (keyTimes[numMotions-1] - keyTimes[0]);
			s		=	p0[i] + (currentOptions->shutterOpen - keyTimes[0])*d;
			e		=	p1[i] + (currentOptions->shutterClose - keyTimes[numMotions-1])*d;
			p0[i]	=	s;
			p1[i]	=	e;
		}

		return	2;
	}

	return 0;
}





////////////////////////////////////////////////////////////////////////////////
// Some misc macros used to manage the graphics state
////////////////////////////////////////////////////////////////////////////////
#define	xformBegin()												\
	savedXforms->push(currentXform);								\
	currentXform	=	new CXform(currentXform);					\
	currentXform->attach();


#define	xformEnd()													\
	{																\
		int oflip			=	currentXform->flip;					\
		currentXform->detach();										\
		currentXform		=	savedXforms->pop();					\
		if (oflip != currentXform->flip) {							\
			CAttributes	*attributes	=	getAttributes(TRUE);		\
			attributes->flags	^=	ATTRIBUTES_FLAGS_INSIDE;		\
		}															\
	}

#define	attributeBegin()											\
	savedAttributes->push(currentAttributes);						\
	currentAttributes = new CAttributes(currentAttributes);			\
	currentAttributes->attach();

#define	attributeEnd()												\
	currentAttributes->detach();									\
	currentAttributes			=	savedAttributes->pop();

#define	optionBegin()												\
	savedOptions->push(currentOptions);								\
	currentOptions	=	new COptions(currentOptions);

#define	optionEnd()													\
	delete currentOptions;											\
	currentOptions			=	savedOptions->pop();


#define	getOptions(a)	currentOptions

#define	checkGeometryOrDiscard()									\
	if (attributes->flags & ATTRIBUTES_FLAGS_DISCARD_GEOMETRY)		\
		return;



////////////////////////////////////////////////////////////////////////////////
//	Renderer Interface
////////////////////////////////////////////////////////////////////////////////
void	CRendererContext::RiDeclare(char *name,char *declaration) {
	declareVariable(name,declaration);
}
   
// FrameBegin - End stuff
void	CRendererContext::RiFrameBegin(int number) {
	COptions	*options;

	optionBegin();
	attributeBegin();
	xformBegin();

	options			=	getOptions(TRUE);
	options->frame	=	number;

	stats.sequenceNumber++;
}

void	CRendererContext::RiFrameEnd(void) {

	xformEnd();
	attributeEnd();
	optionEnd();
}

// WorldBegin - End stuff
void	CRendererContext::RiWorldBegin(void) {
	optionBegin();
	attributeBegin();
	xformBegin();

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//		The frame initialization		
	assert(currentOptions	!=	NULL);

	// Init the stats
	stats.frameStartTime				=	osCPUTime();
	stats.progress						=	0;

	defineCoordinateSystem(coordinateWorldSystem,currentXform->from,currentXform->to,COORDINATE_WORLD);

	// Create the renderer
	if (strcmp(currentOptions->hider,"raytrace") == 0)
		renderer						=	new CRaytracer(currentOptions,currentXform,netClient);
	else if (strcmp(currentOptions->hider,"stochastic") == 0)
		renderer						=	new CStochastic(currentOptions,currentXform,netClient);
	else if (strcmp(currentOptions->hider,"zbuffer") == 0)
		renderer						=	new CZbuffer(currentOptions,currentXform,netClient);
	else if (strncmp(currentOptions->hider,"show:",5) == 0)
		renderer						=	new CShow(currentOptions,currentXform,netClient);
	else if (strcmp(currentOptions->hider,"photon") == 0)
		if ((netClient != INVALID_SOCKET) || (netNumServers > 0)) {
			error(CODE_LIMIT,"Hider \"%s\" does not support paralell / network rendering\n",currentOptions->hider);
			renderer					=	new CStochastic(currentOptions,currentXform,netClient);
		} else {
			renderer					=	new CPhotonHider(currentOptions,currentXform,netClient,currentAttributes);
		}
	else {
		error(CODE_BADTOKEN,"Hider \"%s\" unavailable\n",currentOptions->hider);
		renderer						=	new CStochastic(currentOptions,currentXform,netClient);
	}

	renderer->initState(variables,numGlobalVariables);
	renderer->beginWorld();

	userRaytracing						=	FALSE;


	stats.runningSequenceNumber++;
}

void	CRendererContext::RiWorldEnd(void) {
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//
	//
	//
	//
	//
	//
	//	This call causes the rendering to happen
	//
	//
	//
	//
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Do the thing baby

	// If the user is raytracing, then do not render the scene
	if (userRaytracing == FALSE) {
		// Prepare the raytracer
		renderer->endWorld();

		// Render the frame
		if (netNumServers != 0) {
			// Dispatch the rendering job to the servers
			clientRenderFrame();
		} else {
			// Just render
			renderer->renderFrame();
		}
	}

	delete renderer;
	renderer		=	NULL;
	
	// remove end-of-frame temporary files
	if (frameTemporaryFiles != NULL) {
		int			i,numTemps	=	frameTemporaryFiles->numItems;
		const char	**tempFiles	=	frameTemporaryFiles->array;
		for (i=0;i<numTemps;i++) {
			int			removeFile	= (*tempFiles)[0];
			const char	*fileName 	= &(*tempFiles)[1];
			
			// Remove file if needed
			if (removeFile) {
				if (osFileExists(fileName) == TRUE) {
					osDeleteFile(fileName);
				}
			}
			
			// Remove temp file mapping if it exists
			if (netFileMappings != NULL) {
				CNetFileMapping* mapping;
				if (netFileMappings->erase(fileName,mapping) == TRUE) {
					delete mapping;
				}
			}
			
			tempFiles++;
		}
		frameTemporaryFiles->destroy();
		frameTemporaryFiles = NULL;
	}

	if (netClient != INVALID_SOCKET) {	// End of frame confirmation
		T32		netBuffer;

		// Expect the ready message
		rcRecv(netClient,(char *) &netBuffer,1*sizeof(T32));

		if (netBuffer.integer == NET_READY) {
			// We're proceeding to the next frame
		} else {
			fatal(CODE_BADTOKEN,"Invalid net command\n");
		}
	}

	xformEnd();
	attributeEnd();
	optionEnd();
}

void	CRendererContext::RiFormat(int xres,int yres,float aspect) {
	COptions	*options;

	if ((xres <= 0) || (yres <= 0)) {
		error(CODE_RANGE,"Resolution too small (%dx%d).\n",xres,yres);
		return;
	}

	options				= getOptions(TRUE);
	options->xres		= xres;
	options->yres		= yres;
	if (aspect > 0) {
		options->pixelAR	= aspect;
	}
	options->flags		|= OPTIONS_FLAGS_CUSTOM_RESOLUTION;
}

void	CRendererContext::RiFrameAspectRatio(float aspect) {
	COptions	*options;

	if (aspect == 0) {
		error(CODE_RANGE,"Invalid frame aspectratio (%f).\n",aspect);
		return;
	}

	options						= getOptions(TRUE);
	options->frameAR			= aspect;
	options->flags				|= OPTIONS_FLAGS_CUSTOM_FRAMEAR;
}

void	CRendererContext::RiScreenWindow(float left,float right,float bot,float top) {
	COptions	*options;

	options						=	getOptions(TRUE);
	options->screenLeft			=	left;
	options->screenRight		=	right;
	options->screenTop			=	top;
	options->screenBottom		=	bot;
	options->flags				|=	OPTIONS_FLAGS_CUSTOM_SCREENWINDOW;
}

void	CRendererContext::RiCropWindow(float xmin,float xmax,float ymin,float ymax) {
	COptions	*options;

	if ((xmin < 0) || (xmin > 1) || (ymin < 0) || (ymax > 1) || (xmax < xmin) || (ymax < ymin)) {
		error(CODE_RANGE,"Invalid crop window boundaries (%.3f,%.3f,%.3f,%.3f).\n",xmin,xmax,ymin,ymax);
		return;
	}

	options						=	getOptions(TRUE);
	options->cropLeft			=	xmin;
	options->cropRight			=	xmax;
	options->cropTop			=	ymin;
	options->cropBottom			=	ymax;
}

void	CRendererContext::RiProjectionV(char *name,int n,char *tokens[],void *params[]) {
	COptions	*options;

	options	=	getOptions(TRUE);

	if (strcmp(name,RI_PERSPECTIVE) == 0) {
		int	i;
		options->projection = OPTIONS_PROJECTION_PERSPECTIVE;
		for (i=0;i<n;i++) {
			if (strcmp(tokens[i],RI_FOV) == 0) 
				options->fov	=	((float **) params)[i][0];
			else 
				error(CODE_BADTOKEN,"Invalid perspective projection parameter (%s).\n",tokens[i]);
		}
	} else if (strcmp(name,RI_ORTHOGRAPHIC) == 0) {
		int	i;
		options->projection = OPTIONS_PROJECTION_ORTHOGRAPHIC;
		for (i=0;i<n;i++) {
			error(CODE_BADTOKEN,"Invalid orthographic projection parameter (%s).\n",tokens[i]);
		}
	} else {
		error(CODE_BADTOKEN,"Invalid projection type (%s).\n",name);
	}
}

void	CRendererContext::RiClipping(float hither,float yon) {
	COptions	*options;

	if ((yon < hither)  || (hither < 0) || (yon < 0)) {
		error(CODE_RANGE,"Invalid clipping boundaries (%f,%f).\n",hither,yon);
		return;
	}

	options				=	getOptions(TRUE);
	options->clipMin	=	max(hither,C_EPSILON);
	options->clipMax	=	yon;
	options->flags		|=	OPTIONS_FLAGS_CUSTOM_CLIPPING;
}

void	CRendererContext::RiClippingPlane(float x,float y,float z,float nx,float ny,float nz) {
	COptions				*options;
	CXform					*xform;
	COptions::CClipPlane	*newPlane;
	vector					p,n,tmp;

	options		=	getOptions(TRUE);
	xform		=	getXform(FALSE);
	newPlane	=	new COptions::CClipPlane;

	initv(tmp,x,y,z);
	mulmp(p,xform->from,tmp);

	initv(tmp,nx,ny,nz);
	mulmn(n,xform->to,tmp);

	movvv(newPlane->normal,n);
	newPlane->d			=	-dotvv(n,p);

	newPlane->next		=	options->clipPlanes;
	options->clipPlanes	=	newPlane;
}

void	CRendererContext::RiDepthOfField(float fstop,float focallength,float focaldistance) {
	COptions	*options;

	if (fstop < 0) {
		error(CODE_RANGE,"Invalid fstop: %f\n",fstop);
		return;
	}

	if (focallength < 0) {
		error(CODE_RANGE,"Invalid focallength: %f\n",focallength);
		return;
	}

	if (focaldistance < 0) {
		error(CODE_RANGE,"Invalid focaldistance: %f\n",focaldistance);
		return;
	}

	options					=	getOptions(TRUE);
	options->fstop			=	fstop;
	options->focallength	=	focallength;
	options->focaldistance	=	focaldistance;
}

void	CRendererContext::RiShutter(float smin,float smax) {
	COptions	*options;

	if (smax < smin) {
		error(CODE_RANGE,"Invalid shutter interval [%f %f]\n",smin,smax);
		return;
	}

	options					=	getOptions(TRUE);
	options->shutterOpen	=	smin;
	options->shutterClose	=	smax;
}


void	CRendererContext::RiPixelVariance(float variation) {
	COptions	*options;

	options					=	getOptions(TRUE);
	options->pixelVariance	=	variation;
}

void	CRendererContext::RiPixelSamples(float xsamples,float ysamples) {
	COptions	*options;

	if ((xsamples < 1) || (ysamples < 1)) {
		error(CODE_RANGE,"Invalid pixel samples (%f,%f).\n",xsamples,ysamples);
		return;
	}

	options					=	getOptions(TRUE);
	options->pixelXsamples	=	(int) xsamples;
	options->pixelYsamples	=	(int) ysamples;
}

void	CRendererContext::RiPixelFilter(float (*function)(float,float,float,float),float xwidth,float ywidth) {
	COptions	*options;

	if ((xwidth < 0) || (ywidth < 0)) {
		warning(CODE_RANGE,"Invalid filter dimentions (%f,%f).\n",xwidth,ywidth);
		return;
	}

	if ((xwidth < 1) || (ywidth < 1)) {
		warning(CODE_RANGE,"Filter support is less than a pixel (%f,%f).\n",xwidth,ywidth);
	}

	options							=	getOptions(TRUE);
	options->pixelFilter			=	function;
	options->pixelFilterWidth		=	xwidth;
	options->pixelFilterHeight		=	ywidth;
}

void	CRendererContext::RiExposure(float gain,float gamma) {
	COptions	*options;

	if (gamma <= C_EPSILON) {
		error(CODE_RANGE,"Invalid gamma (%f).\n",gamma);
		return;
	}

	if (gain <= C_EPSILON) {
		error(CODE_RANGE,"Invalid gain (%f).\n",gain);
		return;
	}

	options			=	getOptions(TRUE);
	options->gamma	=	gamma;
	options->gain	=	gain; 
}

void	CRendererContext::RiImagerV (char *name,int n,char *tokens[],void *params[]) {
	error(CODE_INCAPABLE,"Imager shaders are not supported (yet).\n");
}

void	CRendererContext::RiQuantize(char *type,int one,int qmin,int qmax,float ampl) {
	COptions	*options;

	options	=	getOptions(TRUE);

	if (strcmp(type,RI_RGBA) == 0) {
		options->colorQuantizer[0]	=	0;
		options->colorQuantizer[1]	=	(float) one;
		options->colorQuantizer[2]	=	(float) qmin;
		options->colorQuantizer[3]	=	(float) qmax;
		options->colorQuantizer[4]	=	(float) ampl;
	} else if (strcmp(type,RI_Z) == 0) {
		options->depthQuantizer[0]	=	0;
		options->depthQuantizer[1]	=	(float) one;
		options->depthQuantizer[2]	=	(float) qmin;
		options->depthQuantizer[3]	=	(float) qmax;
		options->depthQuantizer[4]	=	(float) ampl;
	} else if (strcmp(type,RI_CUSTOM) == 0) {
		COptions::CDisplay	*cDisplay	=	options->displays;
		if (cDisplay != NULL) {
			cDisplay->quantizer[0]	=	0;
			cDisplay->quantizer[1]	=	(float) one;
			cDisplay->quantizer[2]	=	(float) qmin;
			cDisplay->quantizer[3]	=	(float) qmax;
			cDisplay->quantizer[4]	=	(float) ampl;
		}
	} else {
		error(CODE_BADTOKEN,"Unknown quantizer type (%s).\n",type);
	}
}


void	CRendererContext::RiDisplayV(char *name,char *type,char *mode,int n,char *tokens[],void *params[]) {
	COptions	*options;

	if (strcmp(mode,RI_RGBZ) == 0) {
		char	tmp[OS_MAX_PATH_LENGTH];
		char	*extensionPos;

		strcpy(tmp,name);
		if ((extensionPos = strchr(tmp,'.')) != NULL) {
			sprintf(extensionPos,"_z");
			strcat(tmp,strchr(name,'.'));
		} else {
			strcat(tmp,"_z");
		}

		RiDisplayV(name,type,RI_RGB,n,tokens,params);
		RiDisplayV(tmp,type,RI_Z,n,tokens,params);
		return;
	} else if (strcmp(mode,RI_RGBAZ) == 0) {
		char	tmp[OS_MAX_PATH_LENGTH];
		char	*extensionPos;

		strcpy(tmp,name);
		if ((extensionPos = strchr(tmp,'.')) != NULL) {
			sprintf(extensionPos,"_z");
			strcat(tmp,strchr(name,'.'));
		} else {
			strcat(tmp,"_z");
		}

		RiDisplayV(name,type,RI_RGBA,n,tokens,params);
		RiDisplayV(tmp,type,RI_Z,n,tokens,params);
		return;
	}

	options	=	getOptions(TRUE);
	if (name[0] == '+') {
		name++;
	} else {
		// Ditch the previously assigned junk
		if (options->displays != NULL) {
			COptions::CDisplay	*cDisplay,*nDisplay;

			for (cDisplay=options->displays;cDisplay!=NULL;) {
				nDisplay	=	cDisplay->next;
				delete cDisplay;
				cDisplay	=	nDisplay;
			}
			options->displays	=	NULL;
		}
	}

	COptions::CDisplay	*cDisplay	=	new COptions::CDisplay;
	cDisplay->outDevice				=	strdup(type);
	cDisplay->outName				=	strdup(name);
	cDisplay->outSamples			=	strdup(mode);
	cDisplay->next					=	options->displays;
	options->displays				=	cDisplay;

	if (n > 0) {
		int i,j;

		cDisplay->numParameters			=	n;
		cDisplay->parameters			=	new COptions::CDisplay::TDisplayParameter[n];

		for (j=0,i=0;i<n;i++) {
			CVariable	*cVar;
			CVariable	tVar;

			cVar						=	retrieveVariable(tokens[i]);
			if (cVar == NULL)
				if (parseVariable(&tVar,NULL,tokens[i]) == TRUE) {
					cVar	=	&tVar;
				}

			if (cVar != NULL) {
				cDisplay->parameters[j].name		=	strdup(cVar->name);
				cDisplay->parameters[j].numItems	=	cVar->numItems;
				switch(cVar->type) {
				case TYPE_FLOAT:
					cDisplay->parameters[j].type	=	FLOAT_PARAMETER;
					cDisplay->parameters[j].data	=	new float[cVar->numItems];
					memcpy(cDisplay->parameters[j].data,params[i],cVar->numItems*sizeof(float));
					break;
				case TYPE_COLOR:
				case TYPE_VECTOR:
				case TYPE_NORMAL:
				case TYPE_POINT:
					cDisplay->parameters[j].type	=	VECTOR_PARAMETER;
					cDisplay->parameters[j].data	=	new float[cVar->numItems*3];
					memcpy(cDisplay->parameters[j].data,params[i],cVar->numItems*sizeof(float)*3);
					break;
				case TYPE_MATRIX:
					cDisplay->parameters[j].type	=	MATRIX_PARAMETER;
					cDisplay->parameters[j].data	=	new float[cVar->numItems*16];
					memcpy(cDisplay->parameters[j].data,params[i],cVar->numItems*sizeof(float)*16);
					break;
				case TYPE_QUAD:
				case TYPE_DOUBLE:
					break;
				case TYPE_STRING:
					cDisplay->parameters[j].type	=	STRING_PARAMETER;
					cDisplay->parameters[j].data	=	strdup(((char **) params[i])[0]);
					break;
				case TYPE_INTEGER:
					{
						int		k;
						float	*src;
						int		*dst;
						cDisplay->parameters[j].type	=	INTEGER_PARAMETER;
						cDisplay->parameters[j].data	=	new int[cVar->numItems];
						dst = (int*)	cDisplay->parameters[j].data;
						src	= (float*)	params[i];
						for(k=0;k<cVar->numItems;k++)	*dst++ = (int) *src++;
					}
					break;
				case TYPE_BOOLEAN:
					break;
				}
				j++;
			} else {
				error(CODE_BADTOKEN,"Display parameter %s not defined\n",tokens[i]);
			}
		}
		cDisplay->numParameters	=	j;
	}
}

void	CRendererContext::RiDisplayChannelV(char *channel,int n,char *tokens[],void *params[]) {
	int i,j;
	
	CDisplayChannel *nChannel = declareDisplayChannel(channel);
	
	if (nChannel != NULL) {
		for (j=0,i=0;i<n;i++) {
			CVariable	*cVar;
			CVariable	tVar;

			cVar						=	retrieveVariable(tokens[i]);
			if (cVar == NULL)
				if (parseVariable(&tVar,NULL,tokens[i]) == TRUE) {
					cVar	=	&tVar;
				}

			if (cVar != NULL) {
				if (strcmp(cVar->name,"fill") == 0) {
					if ((cVar->numFloats == nChannel->numSamples) &&
						(cVar->type == nChannel->variable->type)) {
						nChannel->fill = (float*) malloc(sizeof(float)*nChannel->numSamples);
						memcpy(nChannel->fill,params[i],nChannel->numSamples*sizeof(float));
					} else {
						error(CODE_BADTOKEN,"Invalid number of items for fill\n");
					}
				} else if (strcmp(cVar->name,"quantize") == 0) {
					// intentionally empty for compatibility
					warning(CODE_UNIMPLEMENT,"Display channel parameter \"%s\" is not implemented (yet)\n",cVar->name);
				} else if (strcmp(cVar->name,"dither") == 0) {
					// intentionally empty for compatibility
					warning(CODE_UNIMPLEMENT,"Display channel parameter \"%s\" is not implemented (yet)\n",cVar->name);
				} else if (strcmp(cVar->name,"filter") == 0) {
					// intentionally empty for compatibility
					warning(CODE_UNIMPLEMENT,"Display channel parameter \"%s\" is not implemented (yet)\n",cVar->name);
				} else {
					error(CODE_BADTOKEN,"Invalid display channel parameter %s\n",tokens[i]);
				}
				j++;
			} else {
				error(CODE_BADTOKEN,"Display channel parameter %s not defined\n",tokens[i]);
			}
		}
	}
}

void	CRendererContext::RiHiderV(char *type,int n,char *tokens[],void *params[]) {
	COptions	*options;

	options	=	getOptions(TRUE);

	if (options->hider != NULL)	free(options->hider);

	if (strcmp(type,RI_HIDDEN) == 0)	options->hider	=	strdup("stochastic");
	else								options->hider	=	strdup(type);

	if (n > 0) {
		CRendererContext::RiOptionV(RI_HIDER,n,tokens,params);
	}
}

void	CRendererContext::RiColorSamples(int N,float *nRGB,float *RGBn) {
	COptions	*options;

	if (N < 1) {
		error(CODE_RANGE,"Invalid number of color samples (%d).\n",N);
		return;
	}

	options					=	getOptions(TRUE);
	options->nColorComps	=	N;
	
	if (options->fromRGB != NULL) 
		delete [] options->fromRGB;
	if (options->toRGB != NULL) 
		delete [] options->toRGB;

	options->fromRGB	=	new float[N*3];
	options->toRGB		=	new float[N*3];

	memcpy(options->fromRGB,RGBn,N*3*sizeof(float));
	memcpy(options->toRGB,nRGB,N*3*sizeof(float));
}

void	CRendererContext::RiRelativeDetail(float relativedetail) {
	COptions	*options;

	if (relativedetail < 0) {
		error(CODE_RANGE,"Invalid relative detail (%4.2).\n",relativedetail);
		return;
	}

	options					=	getOptions(TRUE);
	options->relativeDetail	=	relativedetail;
}


#define	optionCheck(__name,__dest,__min,__max,__type)														\
	} else if (strcmp(tokens[i],__name) == 0) {																\
		__type	*val	=	(__type *) params[i];															\
		if ((val[0] < __min) || (val[0] > __max)) {															\
			error(CODE_RANGE,"Invalid value for \"%s\"\n",__name);											\
		} else {																							\
			__dest	=	val[0];																				\
		}

#define	optionCheckFlag(__name,__dest,__flag)																\
	} else if (strcmp(tokens[i],__name) == 0) {																\
		int	*val	=	(int *) params[i];																	\
		if (val[0] != 0)	__dest	|=	__flag;																\
		else				__dest	&=	~(__flag);															\

#define	optionCheckString(__name,__dest)																	\
	} else if (strcmp(tokens[i],__name) == 0) {																\
		char	*val	=	((char **) params[i])[0];														\
		if (__dest != NULL) free(__dest);																	\
		if (val[0] == '\0') __dest	=	NULL;																\
		else				__dest	=	strdup(val);

#define	optionEndCheck																						\
	} else {																								\
		CVariable	var;																					\
		if (parseVariable(&var,NULL,tokens[i]) == TRUE) {													\
			RiOption(name,var.name,params[i],RI_NULL);														\
		} else {																							\
			error(CODE_BADTOKEN,"Unknown %s option: \"%s\"\n",name,tokens[i]);								\
		}																									\
	}


void	CRendererContext::RiOptionV(char *name,int n,char *tokens[],void *params[]) {
	int			i;
	COptions	*options;

	options	=	getOptions(TRUE);

	// Check the searchpath options
	if (strcmp(name,RI_SEARCHPATH) == 0) {
		for (i=0;i<n;i++) {
			char	*paths	=	((char **) params[i])[0];

			if (strcmp(tokens[i],RI_ARCHIVE) == 0) {
				options->archivePath	=	optionsGetSearchPath(paths,options->archivePath);
			} else if (strcmp(tokens[i],RI_PROCEDURAL) == 0) {
				options->proceduralPath	=	optionsGetSearchPath(paths,options->proceduralPath);
			} else if (strcmp(tokens[i],RI_TEXTURE) == 0) {
				options->texturePath	=	optionsGetSearchPath(paths,options->texturePath);
			} else if (strcmp(tokens[i],RI_SHADER) == 0) {
				options->shaderPath		=	optionsGetSearchPath(paths,options->shaderPath);
			} else if (strcmp(tokens[i],RI_DISPLAY) == 0) {
				options->displayPath	=	optionsGetSearchPath(paths,options->displayPath);
			} else if (strcmp(tokens[i],RI_RESOURCE) == 0) {
				options->shaderPath		=	optionsGetSearchPath(paths,options->shaderPath);
				options->texturePath	=	optionsGetSearchPath(paths,options->texturePath);
			optionEndCheck
		}
	// Check the limit options
	} else if (strcmp(name,RI_LIMITS) == 0) {
		for (i=0;i<n;i++) {

			if (strcmp(tokens[i],RI_BUCKETSIZE) == 0) {
				int	*val	=	(int *) params[i];
				if ((val[0] < 0) || (val[1] < 0)) {
					error(CODE_RANGE,"Invalid bucket size (%dx%d)\n",val[0],val[1]);
				} else {
					options->bucketWidth	=	val[0];
					options->bucketHeight	=	val[1];
				}
			} else if (strcmp(tokens[i],RI_METABUCKETS) == 0) {
				int	*val	=	(int *) params[i];
				if ((val[0] < 0) || (val[1] < 0)) {
					error(CODE_RANGE,"Invalid meta bucket size (%dx%d)\n",val[0],val[1]);
				} else {
					options->netXBuckets	=	val[0];
					options->netYBuckets	=	val[1];
				}
			optionCheckFlag(RI_INHERITATTRIBUTES,options->flags,					OPTIONS_FLAGS_INHERIT_ATTRIBUTES)
			optionCheck(RI_GRIDSIZE,			options->maxGridSize,				0,100000,int)
			optionCheck(RI_HIERARCHYDEPTH,		options->maxHierarchyDepth,			1,100000,int)
			optionCheck(RI_HIERARCHYOBJECTS,	options->maxHierarchyLeafObjects,	1,100000,int)
			optionCheck(RI_EYESPLITS,			options->maxEyeSplits,				1,100000,int)
			optionCheck(RI_TEXTUREMEMORY,		options->maxTextureSize,			0,100000,int)
				options->maxTextureSize	*=	1000;								// Convert into bytes
			optionCheck(RI_BRICKMEMORY,			options->maxBrickSize,				0,100000,int)
				options->maxBrickSize	*=	1000;								// Convert into bytes
			optionCheck(RI_SHADERCACHE,			options->maxShaderCache,			0,100000,int)
				options->maxShaderCache	*=	1000;								// Convert into bytes
			optionEndCheck
		}
	// Check the hider options
	} else if (strcmp(name,RI_HIDER) == 0) {
		for (i=0;i<n;i++) {
			if (FALSE) {
			optionCheck(RI_JITTER,				options->jitter,					0,1,float)
				if (options->jitter > (float) 0.99)	options->jitter	=	(float) 0.99;
			optionCheckFlag(RI_FALSECOLOR,		options->flags,						OPTIONS_FLAGS_FALSECOLOR_RAYTRACES)
			optionCheckFlag(RI_RADIANCECACHE,	options->flags,						OPTIONS_FLAGS_USE_RADIANCE_CACHE)
			optionCheck(RI_EMIT,				options->numEmitPhotons,			0,100000000,int)
			optionCheckFlag(RI_SAMPLESPECTRUM,	options->flags,						OPTIONS_FLAGS_SAMPLESPECTRUM)
			} else if (strcmp(tokens[i],RI_DEPTHFILTER) == 0) {
				char	*val	=	((char **) params[i])[0];
				if		(strcmp(val,"min") == 0)		options->depthFilter	=	DEPTH_MIN;
				else if (strcmp(val,"max") == 0)		options->depthFilter	=	DEPTH_MAX;
				else if (strcmp(val,"average") == 0)	options->depthFilter	=	DEPTH_AVG;
				else if (strcmp(val,"midpoint") == 0)	options->depthFilter	=	DEPTH_MID;
				else error(CODE_BADTOKEN,"Unknown depth filter: \"%s\" \n",val);
			optionEndCheck
		}

	// Check the trace options
	} else if (strcmp(name,RI_TRACE) == 0) {
		for (i=0;i<n;i++) {
			if (FALSE) {
			optionCheck(RI_MAXDEPTH,			options->maxRayDepth,				0,100000,int)
			optionEndCheck
		}

	// Check the io options
	} else if (strcmp(name,RI_STATISTICS) == 0) {
		for (i=0;i<n;i++) {
			if (FALSE) {
			optionCheck(RI_ENDOFFRAME,			options->endofframe,				0,3,int)
			optionCheckString(RI_FILELOG,		options->filelog)
			optionCheckFlag(RI_PROGRESS,		options->flags,						OPTIONS_FLAGS_PROGRESS)
			optionEndCheck
		}
	} else {
		error(CODE_BADTOKEN,"Unknown option: \"%s\"\n",name);
	}
}

#undef optionCheck
#undef optionCheckFlag
#undef optionCheckString
#undef optionEnd

void	CRendererContext::RiAttributeBegin (void) {
	attributeBegin();
	xformBegin();
}

void	CRendererContext::RiAttributeEnd (void) {
	xformEnd();
	attributeEnd();
}

void	CRendererContext::RiColor(float * Cs) {
	COptions		*options;
	CAttributes		*attributes;
	vector			color;
	float			*p0,*p1;

	if (netNumServers > 0)	return;

	attributes	=	getAttributes(TRUE);
	options		=	getOptions(TRUE);

	options->convertColor(color,Cs);

	switch(addMotion(color,3,"CRendererContext::RiColor",p0,p1)) {
	case 0:
		break;
	case 1:
		movvv(attributes->surfaceColor,p0);
		if (attributes->next != NULL)	movvv(attributes->next->surfaceColor,p0);
		break;
	case 2:
		movvv(attributes->surfaceColor,p0);
		if (attributes->next == NULL)	attributes->next	=	new CAttributes(attributes);
		movvv(attributes->next->surfaceColor,p1);
		break;
	default:
		break;
	}
}

void	CRendererContext::RiOpacity (float * Cs) {
	COptions		*options;
	CAttributes		*attributes;
	vector			color;
	float			*p0,*p1;

	if (netNumServers > 0)	return;

	attributes	=	getAttributes(TRUE);
	options		=	getOptions(TRUE);

	options->convertColor(color,Cs);

	switch(addMotion(color,3,"CRendererContext::RiOpacity",p0,p1)) {
	case 0:
		break;
	case 1:
		movvv(attributes->surfaceOpacity,p0);
		if (attributes->next != NULL)	movvv(attributes->next->surfaceOpacity,p0);
		break;
	case 2:
		movvv(attributes->surfaceOpacity,p0);
		if (attributes->next == NULL)	attributes->next	=	new CAttributes(attributes);
		movvv(attributes->next->surfaceOpacity,p1);
		break;
	default:
		break;
	}
}

void	CRendererContext::RiTextureCoordinates(float s1,float t1,float s2,float t2,float s3,float t3,float s4,float t4) {
	CAttributes	*attributes;
	float		*p0,*p1;
	float		data[8];

	if (netNumServers > 0)	return;

	attributes	=	getAttributes(TRUE);

	data[0]	=	s1;
	data[1]	=	s2;
	data[2]	=	s3;
	data[3]	=	s4;
	data[4]	=	t1;
	data[5]	=	t2;
	data[6]	=	t3;
	data[7]	=	t4;

	switch(addMotion(data,8,"CRendererContext::RiTextureCoordinates",p0,p1)) {
	case 0:
		break;
	case 1:
		attributes->s[0] = p0[0];
		attributes->s[1] = p0[1];
		attributes->s[2] = p0[2];
		attributes->s[3] = p0[3];
		attributes->t[0] = p0[4];
		attributes->t[1] = p0[5];
		attributes->t[2] = p0[6];
		attributes->t[3] = p0[7];
		attributes->flags |= ATTRIBUTES_FLAGS_CUSTOM_ST;

		if (attributes->next != NULL) {
			attributes->next->s[0] = p0[0];
			attributes->next->s[1] = p0[1];
			attributes->next->s[2] = p0[2];
			attributes->next->s[3] = p0[3];
			attributes->next->t[0] = p0[4];
			attributes->next->t[1] = p0[5];
			attributes->next->t[2] = p0[6];
			attributes->next->t[3] = p0[7];
		}
		
		break;
	case 2:
		attributes->s[0] = p0[0];
		attributes->s[1] = p0[1];
		attributes->s[2] = p0[2];
		attributes->s[3] = p0[3];
		attributes->t[0] = p0[4];
		attributes->t[1] = p0[5];
		attributes->t[2] = p0[6];
		attributes->t[3] = p0[7];
		attributes->flags |= ATTRIBUTES_FLAGS_CUSTOM_ST;

		if (attributes->next == NULL)	attributes->next	=	new CAttributes(attributes);
		
		attributes->next->s[0] = p1[0];
		attributes->next->s[1] = p1[1];
		attributes->next->s[2] = p1[2];
		attributes->next->s[3] = p1[3];
		attributes->next->t[0] = p1[4];
		attributes->next->t[1] = p1[5];
		attributes->next->t[2] = p1[6];
		attributes->next->t[3] = p1[7];
		break;
	default:
		break;
	}
}



void	*CRendererContext::RiLightSourceV(char *name,int n,char *tokens[],void *params[]) {
	CAttributes			*attributes;
	CShaderInstance		*cShader;

	if (netNumServers > 0)	return NULL;

	attributes	=	getAttributes(TRUE);
	cShader		=	getShader(name,SL_LIGHTSOURCE,n,tokens,(void **) params);

	if (cShader != NULL) {
		attributes->addLight(cShader);

		return (RtLightHandle) cShader;
	}

	return NULL;
}

void	*CRendererContext::RiAreaLightSourceV(char *name,int n,char *tokens[],void *params[]) {
	CAttributes			*attributes;
	CShaderInstance		*cShader;

	if (netNumServers > 0)	return NULL;

	attributes	=	getAttributes(TRUE);
	cShader		=	getShader(name,SL_LIGHTSOURCE,n,tokens,(void **) params);

	if (cShader != NULL) {
		attributes->addLight(cShader);

		return (RtLightHandle) cShader;
	}

	return NULL;
}


void	CRendererContext::RiIlluminate (void *light,int onoff) {
	CShaderInstance	*cInstance	=	(CShaderInstance *) light;
	CAttributes		*attributes;

	if (netNumServers > 0)				return;
	if (cInstance == NULL)	return;

	attributes	=	getAttributes(TRUE);
	if (onoff)
		attributes->addLight(cInstance);
	else
		attributes->removeLight(cInstance);
}

void	CRendererContext::RiSurfaceV(char *name,int n,char *tokens[],void *params[]) {
	CAttributes		*attributes;
	CShaderInstance	*cShader;

	if (netNumServers > 0)	return;

	attributes	=	getAttributes(TRUE);
	cShader		=	getShader(name,SL_SURFACE,n,tokens,(void **) params);

	if (attributes->surface != NULL)
		attributes->surface->detach();

	attributes->surface = cShader;
}

void	CRendererContext::RiAtmosphereV(char *name,int n,char *tokens[],void *params[]) {
	CAttributes		*attributes;
	CShaderInstance	*cShader;

	if (netNumServers > 0)	return;

	attributes	=	getAttributes(TRUE);
	cShader		=	getShader(name,SL_ATMOSPHERE,n,tokens,(void **) params);

	if (attributes->atmosphere != NULL)
		attributes->atmosphere->detach();

	attributes->atmosphere = cShader;
}

void	CRendererContext::RiInteriorV(char *name,int n,char *tokens[],void *params[]) {
	CAttributes		*attributes;
	CShaderInstance	*cShader;

	if (netNumServers > 0)	return;

	attributes	=	getAttributes(TRUE);
	cShader		=	getShader(name,SL_ATMOSPHERE,n,tokens,(void **) params);

	if (attributes->interior != NULL)
		attributes->interior->detach();

	attributes->interior = cShader;
}

void	CRendererContext::RiExteriorV (char *name,int n,char *tokens[],void *params[]) {
	CAttributes		*attributes;
	CShaderInstance	*cShader;

	if (netNumServers > 0)	return;

	attributes	=	getAttributes(TRUE);
	cShader		=	getShader(name,SL_ATMOSPHERE,n,tokens,(void **) params);

	if (attributes->exterior != NULL)
		attributes->exterior->detach();

	attributes->exterior = cShader;
}

void	CRendererContext::RiShadingRate(float size) {
	CAttributes			*attributes;

	if (netNumServers > 0)	return;

	if (size < C_EPSILON) {
		error(CODE_RANGE,"Invalid shading rate (%f)\n",size);
		return;
	}

	attributes				=	getAttributes(TRUE);
	attributes->shadingRate	=	size;
}

void	CRendererContext::RiShadingInterpolation(char *type) {
}

void	CRendererContext::RiMatte(int onoff) {
	CAttributes	*attributes;

	if (netNumServers > 0)	return;

	attributes	=	getAttributes(TRUE);
	if (onoff) 
		attributes->flags	|=	ATTRIBUTES_FLAGS_MATTE;
	else {
		attributes->flags	&=	~ATTRIBUTES_FLAGS_MATTE;
	}
}


void	CRendererContext::RiBound(float *bound) {
	CAttributes	*attributes;
	CXform		*xform;

	if (netNumServers > 0)	return;

	xform							=	getXform(FALSE);
	attributes						=	getAttributes(TRUE);
	attributes->flags				|=	ATTRIBUTES_FLAGS_CUSTOM_BOUND;
	attributes->bmin[COMP_X]		=	bound[0];
	attributes->bmax[COMP_X]		=	bound[1];
	attributes->bmin[COMP_Y]		=	bound[2];
	attributes->bmax[COMP_Y]		=	bound[3];
	attributes->bmin[COMP_Z]		=	bound[4];
	attributes->bmax[COMP_Z]		=	bound[5];
	xform->transformBound(attributes->bmin,attributes->bmax);
}

void	CRendererContext::RiDetail(float *bound) {
	CAttributes	*attributes;
	CXform		*xform;
	vector		bmin,bmax;
	
	if (netNumServers > 0)	return;

	xform				=	getXform(FALSE);
	attributes			=	getAttributes(TRUE);
	
	bmin[COMP_X]		=	bound[0];
	bmax[COMP_X]		=	bound[1];
	bmin[COMP_Y]		=	bound[2];
	bmax[COMP_Y]		=	bound[3];
	bmin[COMP_Z]		=	bound[4];
	bmax[COMP_Z]		=	bound[5];
	
	// project the bound to screen space and calculate size	
	
	attributes->lodSize = screenArea(renderer,xform,bmin,bmax);
}

void	CRendererContext::RiDetailRange(float minvis,float lowtran,float uptran,float maxvis) {
	CAttributes	*attributes;
	
	if (netNumServers > 0)	return;

	attributes				=	getAttributes(TRUE);
	
	attributes->lodRange[0] =	minvis;
	attributes->lodRange[1] =	lowtran;
	attributes->lodRange[2] =	uptran;
	attributes->lodRange[3] =	maxvis;
	
	if ((attributes->lodSize < minvis)	|| (attributes->lodSize > maxvis)) {
		// out of rance, discard all geometry
		attributes->flags		|=	ATTRIBUTES_FLAGS_DISCARD_GEOMETRY;
	} else {
		// Ensure we're no longer discarding geometry
		
		attributes->flags		&=	~(ATTRIBUTES_FLAGS_DISCARD_GEOMETRY | ATTRIBUTES_FLAGS_LOD);
		
		if (attributes->lodSize <= lowtran) {
			// fade in
			attributes->lodImportance = (attributes->lodSize-minvis)/(lowtran-minvis);
			
			attributes->flags		|=	ATTRIBUTES_FLAGS_LOD;
		}
		
		if (attributes->lodSize > uptran) {
			// fade out
			attributes->lodImportance = -(1.0f-(attributes->lodSize-uptran)/(maxvis-uptran));
			attributes->flags		|=	ATTRIBUTES_FLAGS_LOD;
		}
	}
}

void	CRendererContext::RiGeometricApproximation(char *type,float value) {
	CAttributes	*attributes;

	if (netNumServers > 0)	return;

	attributes	=	getAttributes(TRUE);

	if (strcmp(type,RI_NORMALDEVIATION) == 0) {
		attributes->normalDeviation		=	(float) cos(radians(value));
	} else if (strcmp(type,RI_POINTDEVIATION) == 0) {
		attributes->pointDeviation		=	value;
	} else if (strcmp(type,RI_FLATNESS) == 0) {
		attributes->flatness			=	value;
	} else if (strcmp(type,RI_MOTIONFACTOR) == 0) {
		attributes->motionFactor		=	value;
	} else {
		error(CODE_BADTOKEN,"Unknown geometric approximation: %s\n",type);
	}
}

void	CRendererContext::RiGeometricRepresentation(char *type) {
	if (netNumServers > 0)	return;

	error(CODE_INCAPABLE,"Arbitrary geometric representation is not implemented (yet).\n");

	return;
}

void	CRendererContext::RiOrientation(char *orientation) {
	CAttributes	*attributes;

	if (netNumServers > 0)	return;

	attributes	=	getAttributes(TRUE);

	if ((strcmp(orientation,RI_OUTSIDE) == 0) || (strcmp(orientation,RI_LH) == 0)) {
		attributes->flags	&=	~ATTRIBUTES_FLAGS_INSIDE;
	} else if ((strcmp(orientation,RI_INSIDE) == 0) || (strcmp(orientation,RI_RH) == 0)) {
		attributes->flags	|=	ATTRIBUTES_FLAGS_INSIDE;
	} else
		error(CODE_BADTOKEN,"Invalid orientation (%s).\n",orientation);
}

void	CRendererContext::RiReverseOrientation(void) {
	CAttributes	*attributes;

	if (netNumServers > 0)	return;

	attributes			=	getAttributes(TRUE);
	attributes->flags	^= ATTRIBUTES_FLAGS_INSIDE;
}

void	CRendererContext::RiSides(int nsides) {
	CAttributes	*attributes;

	if (netNumServers > 0)	return;

	if (!((nsides == 1) || (nsides == 2)))
		error(CODE_RANGE,"Invalid number of sides (%d).\n",nsides);
	else {

		attributes			=	getAttributes(TRUE);
		attributes->nSides	=	nsides;
	}
}


void	CRendererContext::RiIdentity(void) {
	CXform	*xform;
	float	*p0,*p1;
	int		nflip;

	switch(addMotion(NULL,0,"CRendererContext::RiIdentity",p0,p1)) {
	case 0:
		break;
	case 1:
		xform	=	getXform(TRUE);

		if (renderer == NULL) {
			xform->identity();

			if (xform->next != NULL)	{
				delete xform->next;
				xform->next	=	NULL;
			}
		} else {
			CXform	*world	=	renderer->world;

			movmm(xform->from,renderer->world->from);
			movmm(xform->to,renderer->world->to);

			if (world->next == NULL) {
				if (xform->next != NULL)	{
					delete xform->next;
					xform->next	=	NULL;
				}
			} else {
				if (xform->next == NULL)
					xform->next	=	new CXform(xform);

				movmm(xform->next->from,world->next->from);
				movmm(xform->next->to,world->next->to);
			}
		}

		// Orientation check
		if (determinantm(xform->from) < 0)	nflip	=	1;
		else								nflip	=	0;

		if (nflip != xform->flip) {
			CAttributes	*attributes	=	getAttributes(TRUE);

			attributes->flags	^=	ATTRIBUTES_FLAGS_INSIDE;

			xform->flip	=	nflip;
		}

		break;
	case 2:
		xform	=	getXform(TRUE);

		if (renderer == NULL) {
			xform->identity();
			if (xform->next != NULL)	{
				delete xform->next;
				xform->next	=	NULL;
			}
		} else {
			CXform	*world	=	renderer->world;

			movmm(xform->from,world->from);
			movmm(xform->to,world->to);

			if (world->next == NULL) {
				movmm(xform->next->from,world->from);
				movmm(xform->next->to,world->to);

				if (xform->next != NULL)	{
					delete xform->next;
					xform->next	=	NULL;
				}
			} else {
				if (xform->next == NULL)
					xform->next	=	new CXform(xform);
				movmm(xform->next->from,world->next->from);
				movmm(xform->next->to,world->next->to);
			}
		}

		// Orientation check
		if (determinantm(xform->from) < 0)	nflip	=	1;
		else								nflip	=	0;

		if (nflip != xform->flip) {
			CAttributes	*attributes	=	getAttributes(TRUE);

			attributes->flags	^=	ATTRIBUTES_FLAGS_INSIDE;

			xform->flip	=	nflip;
		}
	default:
		break;
	}
}

void	CRendererContext::RiTransform(float transform[][4]) {
	CXform		*xform;
	matrix		to0,to1,from;
	float		*p0,*p1;
	int			nflip;

	// Save the elements
	from[element(0,0)]	=	transform[0][0];
	from[element(1,0)]	=	transform[0][1];
	from[element(2,0)]	=	transform[0][2];
	from[element(3,0)]	=	transform[0][3];
	from[element(0,1)]	=	transform[1][0];
	from[element(1,1)]	=	transform[1][1];
	from[element(2,1)]	=	transform[1][2];
	from[element(3,1)]	=	transform[1][3];
	from[element(0,2)]	=	transform[2][0];
	from[element(1,2)]	=	transform[2][1];
	from[element(2,2)]	=	transform[2][2];
	from[element(3,2)]	=	transform[2][3];
	from[element(0,3)]	=	transform[3][0];
	from[element(1,3)]	=	transform[3][1];
	from[element(2,3)]	=	transform[3][2];
	from[element(3,3)]	=	transform[3][3];

	switch(addMotion(from,16,"CRendererContext::RiTransform",p0,p1)) {
	case 0:
		break;
	case 1:
		if (invertm(to0,p0) == TRUE) {
			error(CODE_MATH,"Singular transformation matrix detected.\n");
		} else {
			xform			=	getXform(TRUE);

			if (renderer == NULL) {
				movmm(xform->from,p0);
				movmm(xform->to,to0);

				if (xform->next != NULL)	{
					delete xform->next;
					xform->next	=	NULL;
				}
			} else {
				CXform	*world	=	renderer->world;

				mulmm(xform->from,renderer->world->from,p0);
				mulmm(xform->to,to0,renderer->world->to);

				if (world->next == NULL) {
					if (xform->next != NULL)	{
						delete xform->next;
						xform->next	=	NULL;
					}
				} else {
					if (xform->next == NULL)	{
						xform->next	=	new CXform(xform);
					}

					mulmm(xform->next->from,world->next->from,p0);
					mulmm(xform->next->to,to0,world->next->to);
				}
			}
		}

		// Orientation check
		if (determinantm(xform->from) < 0)	nflip	=	1;
		else								nflip	=	0;

		if (nflip != xform->flip) {
			CAttributes	*attributes	=	getAttributes(TRUE);

			attributes->flags	^=	ATTRIBUTES_FLAGS_INSIDE;

			xform->flip	=	nflip;
		}
		break;
	case 2:
		if ((invertm(to0,p0) == TRUE) || (invertm(to1,p1) == TRUE)) {
			error(CODE_MATH,"Singular transformation matrix detected.\n");
		} else {
			xform			=	getXform(TRUE);

			if (renderer == NULL) {
				movmm(xform->from,p0);
				movmm(xform->to,to0);
				if (xform->next == NULL)	{
					xform->next	=	new CXform(xform);
				}
				movmm(xform->next->from,p1);
				movmm(xform->next->to,to1);
			} else {
				CXform	*world	=	renderer->world;

				mulmm(xform->from,renderer->world->from,p0);
				mulmm(xform->to,to0,renderer->world->to);
				if (xform->next == NULL)	{
					xform->next	=	new CXform(xform);
				}

				if (world->next == NULL) {
					mulmm(xform->next->from,world->from,p1);
					mulmm(xform->next->to,to1,world->to);
				} else {
					mulmm(xform->next->from,world->next->from,p1);
					mulmm(xform->next->to,to1,world->next->to);
				}
			}
		}

		// Orientation check
		if (determinantm(xform->from) < 0)	nflip	=	1;
		else								nflip	=	0;

		if (nflip != xform->flip) {
			CAttributes	*attributes	=	getAttributes(TRUE);

			attributes->flags	^=	ATTRIBUTES_FLAGS_INSIDE;

			xform->flip	=	nflip;
		}
		break;
	default:
		break;
	}
}

void	CRendererContext::RiConcatTransform(float transform[][4]) {
	CXform	*xform;
	matrix	tmp;
	matrix	to0,to1,from;
	float	*p0,*p1;
	int		nflip;

	// Save the elements
	from[element(0,0)]	=	transform[0][0];
	from[element(1,0)]	=	transform[0][1];
	from[element(2,0)]	=	transform[0][2];
	from[element(3,0)]	=	transform[0][3];
	from[element(0,1)]	=	transform[1][0];
	from[element(1,1)]	=	transform[1][1];
	from[element(2,1)]	=	transform[1][2];
	from[element(3,1)]	=	transform[1][3];
	from[element(0,2)]	=	transform[2][0];
	from[element(1,2)]	=	transform[2][1];
	from[element(2,2)]	=	transform[2][2];
	from[element(3,2)]	=	transform[2][3];
	from[element(0,3)]	=	transform[3][0];
	from[element(1,3)]	=	transform[3][1];
	from[element(2,3)]	=	transform[3][2];
	from[element(3,3)]	=	transform[3][3];

	switch(addMotion(from,16,"CRendererContext::RiConcatTransform",p0,p1)) {
	case 0:
		break;
	case 1:
		if (invertm(to0,p0) == TRUE) {
			error(CODE_MATH,"Singular transformation matrix detected.\n");
		} else {
			xform	=	getXform(TRUE);
			mulmm(tmp,xform->from,p0);
			movmm(xform->from,tmp);

			mulmm(tmp,to0,xform->to);
			movmm(xform->to,tmp);

			if (xform->next != NULL)	{
				mulmm(tmp,xform->next->from,p0);
				movmm(xform->next->from,tmp);

				mulmm(tmp,to0,xform->next->to);
				movmm(xform->next->to,tmp);
			}
		}

		// Orientation check
		if (determinantm(xform->from) < 0)	nflip	=	1;
		else								nflip	=	0;

		if (nflip != xform->flip) {
			CAttributes	*attributes	=	getAttributes(TRUE);

			attributes->flags	^=	ATTRIBUTES_FLAGS_INSIDE;

			xform->flip	=	nflip;
		}
		break;
	case 2:
		if ((invertm(to0,p0) == TRUE) || (invertm(to1,p1) == TRUE)) {
			error(CODE_MATH,"Singular transformation matrix detected.\n");
		} else {
			xform	=	getXform(TRUE);

			if (xform->next == NULL)	{
				xform->next	=	new CXform(xform);
			}


			mulmm(tmp,xform->from,p0);
			movmm(xform->from,tmp);

			mulmm(tmp,to0,xform->to);
			movmm(xform->to,tmp);

			mulmm(tmp,xform->next->from,p1);
			movmm(xform->next->from,tmp);

			mulmm(tmp,to1,xform->next->to);
			movmm(xform->next->to,tmp);
		}

		// Orientation check
		if (determinantm(xform->from) < 0)	nflip	=	1;
		else								nflip	=	0;

		if (nflip != xform->flip) {
			CAttributes	*attributes	=	getAttributes(TRUE);

			attributes->flags	^=	ATTRIBUTES_FLAGS_INSIDE;

			xform->flip	=	nflip;
		}
		break;
	default:
		break;
	}
}

void	CRendererContext::RiPerspective(float fov) {
	CXform	*xform;
	matrix	to,from,tmp;
	double	d;
	float	p;
	float	*p0,*p1;

	p	=	fov;

	switch(addMotion(&p,1,"CRendererContext::RiPerspective",p0,p1)) {
	case 0:
		break;
	case 1:
		xform				=	getXform(TRUE);

		d					=	1 / tan(p0[0]*C_PI/(double) 360);

		from[element(0,0)]	=	(float) d;
		from[element(0,1)]	=	(float) 0;
		from[element(0,2)]	=	(float) 0;
		from[element(0,3)]	=	(float) 0;

		from[element(1,0)]	=	(float) 0;
		from[element(1,1)]	=	(float) d;
		from[element(1,2)]	=	(float) 0;
		from[element(1,3)]	=	(float) 0;

		from[element(2,0)]	=	(float) 0;
		from[element(2,1)]	=	(float) 0;
		from[element(2,2)]	=	(float) 1;
		from[element(2,3)]	=	(float) 0;

		from[element(3,0)]	=	(float) 0;
		from[element(3,1)]	=	(float) 0;
		from[element(3,2)]	=	(float) 1;
		from[element(3,3)]	=	(float) 0;

		identitym(to);
		
		mulmm(tmp,xform->from,from);
		movmm(xform->from,from);

		mulmm(tmp,to,xform->to);
		movmm(xform->to,tmp);

		if (xform->next != NULL)	{
			mulmm(tmp,xform->next->from,from);
			movmm(xform->next->from,from);

			mulmm(tmp,to,xform->next->to);
			movmm(xform->next->to,tmp);
		}

		break;
	case 2:
		xform				=	getXform(TRUE);
		if (xform->next == NULL)	xform->next	=	new CXform(xform);

		d					=	1 / tan(p0[0]*C_PI/(double) 360);

		from[element(0,0)]	=	(float) d;
		from[element(0,1)]	=	(float) 0;
		from[element(0,2)]	=	(float) 0;
		from[element(0,3)]	=	(float) 0;
		from[element(1,0)]	=	(float) 0;
		from[element(1,1)]	=	(float) d;
		from[element(1,2)]	=	(float) 0;
		from[element(1,3)]	=	(float) 0;
		from[element(2,0)]	=	(float) 0;
		from[element(2,1)]	=	(float) 0;
		from[element(2,2)]	=	(float) 1;
		from[element(2,3)]	=	(float) 0;
		from[element(3,0)]	=	(float) 0;
		from[element(3,1)]	=	(float) 0;
		from[element(3,2)]	=	(float) 1;
		from[element(3,3)]	=	(float) 0;

		invertm(to,from);

		mulmm(tmp,xform->from,from);
		movmm(xform->from,from);

		mulmm(tmp,to,xform->to);
		movmm(xform->to,tmp);

		d					=	1 / tan(p1[0]*C_PI/(double) 360);

		from[element(0,0)]	=	(float) d;
		from[element(0,1)]	=	(float) 0;
		from[element(0,2)]	=	(float) 0;
		from[element(0,3)]	=	(float) 0;
		from[element(1,0)]	=	(float) 0;
		from[element(1,1)]	=	(float) d;
		from[element(1,2)]	=	(float) 0;
		from[element(1,3)]	=	(float) 0;
		from[element(2,0)]	=	(float) 0;
		from[element(2,1)]	=	(float) 0;
		from[element(2,2)]	=	(float) 1;
		from[element(2,3)]	=	(float) 0;
		from[element(3,0)]	=	(float) 0;
		from[element(3,1)]	=	(float) 0;
		from[element(3,2)]	=	(float) 1;
		from[element(3,3)]	=	(float) 0;

		invertm(to,from);

		mulmm(tmp,xform->next->from,from);
		movmm(xform->next->from,from);

		mulmm(tmp,to,xform->next->to);
		movmm(xform->next->to,tmp);
		break;
	default:
		break;
	}
}

void	CRendererContext::RiTranslate(float dx,float dy,float dz) {
	CXform	*xform;
	vector	par;
	float	*p0,*p1;

	par[COMP_X]	=	dx;
	par[COMP_Y]	=	dy;
	par[COMP_Z]	=	dz;

	switch(addMotion(par,3,"CRendererContext::RiTranslate",p0,p1)) {
	case 0:
		break;
	case 1:
		xform	=	getXform(TRUE);
		xform->translate(p0[COMP_X],p0[COMP_Y],p0[COMP_Z]);
		if (xform->next != NULL)	xform->next->translate(p0[COMP_X],p0[COMP_Y],p0[COMP_Z]);
		break;
	case 2:
		xform	=	getXform(TRUE);
		if (xform->next == NULL) xform->next	=	new CXform(xform);

		xform->translate(p0[COMP_X],p0[COMP_Y],p0[COMP_Z]);
		xform->next->translate(p1[COMP_X],p1[COMP_Y],p1[COMP_Z]);
		break;
	default:
		break;
	}

	// Note that there's no orientation check as translation can not change the determinant
}

void	CRendererContext::RiRotate(float angle,float dx,float dy,float dz) {
	CXform	*xform;
	float	tmp[4];
	float	*p0,*p1;

	tmp[0]	=	dx;
	tmp[1]	=	dy;
	tmp[2]	=	dz;
	tmp[3]	=	angle;

	switch(addMotion(tmp,4,"CRendererContext::RiRotate",p0,p1)) {
	case 0:
		break;
	case 1:
		xform	=	getXform(TRUE);
		xform->rotate(p0[3],p0[0],p0[1],p0[2]);
		if (xform->next != NULL)	xform->next->rotate(p0[3],p0[0],p0[1],p0[2]);
		break;
	case 2:
		xform	=	getXform(TRUE);
		if (xform->next == NULL)	xform->next	=	new CXform(xform);
		xform->rotate(p0[3],p0[0],p0[1],p0[2]);
		xform->next->rotate(p1[3],p1[0],p1[1],p1[2]);
		break;
	default:
		break;
	}

	// Rotation does not change determinant's sign
}

void	CRendererContext::RiScale(float dx,float dy,float dz) {
	CXform		*xform;
	vector		tmp;
	float		*p0,*p1;
	int			nflip;

	if ((dx == 0) || (dy == 0) || (dz == 0)) {
		error(CODE_MATH,"The matrix is uninvertible (scale(%f,%f,%f)).\n",dx,dy,dz);
		return;
	}

	tmp[COMP_X]	=	dx;
	tmp[COMP_Y]	=	dy;
	tmp[COMP_Z]	=	dz;

	switch(addMotion(tmp,3,"CRendererContext::RiScale",p0,p1)) {
	case 0:
		break;
	case 1:
		if ((p0[0] == 0) || (p0[1] == 0) || (p0[2] == 0)) {
			error(CODE_MATH,"The matrix is uninvertible (scale(%f,%f,%f)).\n",p0[0],p0[1],p0[2]);
			return;
		}

		xform	=	getXform(TRUE);
		xform->scale(p0[0],p0[1],p0[2]);
		if (xform->next != NULL)	xform->next->scale(p0[0],p0[1],p0[2]);

		// Orientation check
		if (determinantm(xform->from) < 0)	nflip	=	1;
		else								nflip	=	0;

		if (nflip != xform->flip) {
			CAttributes	*attributes	=	getAttributes(TRUE);

			attributes->flags	^=	ATTRIBUTES_FLAGS_INSIDE;

			xform->flip	=	nflip;
		}
		break;
	case 2:
		if ((p0[0] == 0) || (p0[1] == 0) || (p0[2] == 0)) {
			error(CODE_MATH,"The matrix is uninvertible (scale(%f,%f,%f)).\n",p0[0],p0[1],p0[2]);
			return;
		}

		if ((p0[0] == 0) || (p0[1] == 0) || (p0[2] == 0)) {
			error(CODE_MATH,"The matrix is uninvertible (scale(%f,%f,%f)).\n",p1[0],p1[1],p1[2]);
			return;
		}

		xform	=	getXform(TRUE);
		if (xform->next == NULL)	xform->next	=	new CXform(xform);
		xform->scale(p0[0],p0[1],p0[2]);
		xform->next->scale(p1[0],p1[1],p1[2]);

		// Orientation check
		if (determinantm(xform->from) < 0)	nflip	=	1;
		else								nflip	=	0;

		if (nflip != xform->flip) {
			CAttributes	*attributes	=	getAttributes(TRUE);

			attributes->flags	^=	ATTRIBUTES_FLAGS_INSIDE;

			xform->flip	=	nflip;
		}
		break;
	default:
		break;
	}
}

void	CRendererContext::RiSkew(float angle,float dx1,float dy1,float dz1,float dx2,float dy2,float dz2) {
	CXform	*xform;
	float	tmp[7];
	float	*p0,*p1;
	int		nflip;

	tmp[0]	=	angle;
	tmp[1]	=	dx1;
	tmp[2]	=	dy1;
	tmp[3]	=	dz1;
	tmp[4]	=	dx2;
	tmp[5]	=	dy2;
	tmp[6]	=	dz2;

	switch(addMotion(tmp,7,"CRendererContext::RiSkew",p0,p1)) {
	case 0:
		break;
	case 1:
		xform	=	getXform(TRUE);
		xform->skew(p0[0],p0[1],p0[2],p0[3],p0[4],p0[5],p0[6]);
		if (xform->next != NULL)	xform->next->skew(p0[0],p0[1],p0[2],p0[3],p0[4],p0[5],p0[6]);

		// Orientation check
		if (determinantm(xform->from) < 0)	nflip	=	1;
		else								nflip	=	0;

		if (nflip != xform->flip) {
			CAttributes	*attributes	=	getAttributes(TRUE);

			attributes->flags	^=	ATTRIBUTES_FLAGS_INSIDE;

			xform->flip	=	nflip;
		}
		break;
	case 2:
		xform	=	getXform(TRUE);
		if (xform->next == NULL)	xform->next	=	new CXform(xform);

		xform->skew(p0[0],p0[1],p0[2],p0[3],p0[4],p0[5],p0[6]);
		xform->next->skew(p1[0],p1[1],p1[2],p1[3],p1[4],p1[5],p1[6]);

		// Orientation check
		if (determinantm(xform->from) < 0)	nflip	=	1;
		else								nflip	=	0;

		if (nflip != xform->flip) {
			CAttributes	*attributes	=	getAttributes(TRUE);

			attributes->flags	^=	ATTRIBUTES_FLAGS_INSIDE;

			xform->flip	=	nflip;
		}
		break;
	default:
		break;
	}
}

void	CRendererContext::RiDeformationV(char *name,int n,char *tokens[],void *params[]) {
	if (netNumServers > 0)	return;

	error(CODE_INCAPABLE,"Atbitrary deformations are not implemented (yet).\n");

	return;
}


void	CRendererContext::RiDisplacementV(char *name,int n,char *tokens[],void *params[]) {
	CAttributes		*attributes;
	CShaderInstance	*cShader;

	if (netNumServers > 0)	return;

	attributes	=	getAttributes(TRUE);
	cShader		=	getShader(name,SL_DISPLACEMENT,n,tokens,(void **) params);

	if (attributes->displacement != NULL)
		attributes->displacement->detach();

	attributes->displacement = cShader;
}

void	CRendererContext::RiCoordinateSystem(char *space) {
	CXform	*xform;

	xform	=	getXform(FALSE);

	defineCoordinateSystem(space,xform->from,xform->to);
}

void	CRendererContext::RiCoordSysTransform(char *space) {
	matrix				*from,*to;
	ECoordinateSystem	cSystem;
	CXform				*xform;

	xform	=	getXform(FALSE);

	if (xform != NULL) {
		findCoordinateSystem(space,from,to,cSystem);

		movmm(xform->from,from[0]);
		movmm(xform->to,to[0]);
	}
}

void	CRendererContext::RiTransformPoints(char *fromspace,char *tospace,int npoints,float points[][3]) {
	matrix				*from1,*to1;
	matrix				*from2,*to2;
	ECoordinateSystem	cSystem1,cSystem2;
	int					i;
	vector				tmp;

	findCoordinateSystem(fromspace,from1,to1,cSystem1);
	findCoordinateSystem(tospace,from2,to2,cSystem2);

	for (i=0;i<npoints;i++) {
		mulmp(tmp,from1[0],points[i]);
		mulmp(points[i],to2[0],tmp);
	}
}

void	CRendererContext::RiTransformBegin (void) {
	xformBegin();
}

void	CRendererContext::RiTransformEnd (void) {
	xformEnd();
}

#define	attributeCheck(__name,__dest,__min,__max,__type)													\
	} else if (strcmp(tokens[i],__name) == 0) {																\
		__type	*val	=	(__type *) params[i];															\
		if ((val[0] < __min) || (val[0] > __max)) {															\
			error(CODE_RANGE,"Invalid value for \"%s\"\n",__name);											\
		} else {																							\
			__dest	=	val[0];																				\
		}

#define	attributeCheckFlag(__name,__dest,__flag)															\
	} else if (strcmp(tokens[i],__name) == 0) {																\
		int	*val	=	(int *) params[i];																	\
		if (val[0] != 0)	__dest	|=	__flag;																\
		else				__dest	&=	~(__flag);															\

#define	attributeCheckInvertFlag(__name,__dest,__flag)														\
	} else if (strcmp(tokens[i],__name) == 0) {																\
		int	*val	=	(int *) params[i];																	\
		if (val[0] != 0)	__dest	&=	~(__flag);															\
		else				__dest	|=	__flag;																\

#define	attributeCheckString(__name,__dest)																	\
	} else if (strcmp(tokens[i],__name) == 0) {																\
		char	*val	=	((char **) params[i])[0];														\
		if (__dest != NULL) free(__dest);																	\
		if (val[0] == '\0') __dest	=	NULL;																\
		else				__dest	=	strdup(val);

#define	attributeEndCheck																					\
	} else {																								\
		CVariable	var;																					\
		if (parseVariable(&var,NULL,tokens[i]) == TRUE) {													\
			RiAttribute(name,var.name,params[i],RI_NULL);													\
		} else {																							\
			error(CODE_BADTOKEN,"Unknown %s attribute: \"%s\"\n",name,tokens[i]);							\
		}																									\
	}



void	CRendererContext::RiAttributeV(char *name,int n,char *tokens[],void *params[]) {
	int			i;
	CAttributes	*attributes;

	if (netNumServers > 0)	return;

	attributes	=	getAttributes(TRUE);

	if (attributes != NULL) {
		if (strcmp(name,RI_DICE) == 0) {
			for (i=0;i<n;i++) {
				if (strcmp(tokens[i],RI_NUMPROBES) == 0) {
					int		*val	=	(int *) params[i];

					if ((val[0] < 0) || (val[1] < 0)) error(CODE_RANGE,"Invalid number of probes (%dx%d)\n",val[0],val[1]);
					else {
						attributes->numUProbes	=	val[0];
						attributes->numVProbes	=	val[1];
					}
				attributeCheck(RI_MINSUBDIVISION,			attributes->minSubdivision,				1, 100000,int)
				attributeCheck(RI_MAXSUBDIVISION,			attributes->maxSubdivision,				1, 100000,int)				
				attributeCheck(RI_MINSPLITS,				attributes->minSplits,					1, 100000,int)				
				attributeCheck(RI_BOUNDEXPAND,				attributes->rasterExpand,				-C_INFINITY, C_INFINITY,float)				
				attributeCheckFlag(RI_BINARY,				attributes->flags,						ATTRIBUTES_FLAGS_BINARY_DICE)
				attributeCheckInvertFlag(RI_RASTERORIENT,	attributes->flags,						ATTRIBUTES_FLAGS_NONRASTERORIENT_DICE)
				attributeEndCheck
			}
		} else if (strcmp(name,RI_DISPLACEMENTBOUND) == 0) {
			for (i=0;i<n;i++) {
				if (strcmp(tokens[i],RI_SPHERE) == 0) {
					float	*val	=	(float *) params[i];

					attributes->maxDisplacement	=	val[0];
				} else if (strcmp(tokens[i],RI_COORDINATESYSYTEM) == 0) {
					char	*val	=	((char **) params[i])[0];

					if (attributes->maxDisplacementSpace != NULL)	free(attributes->maxDisplacementSpace);

					attributes->maxDisplacementSpace	=	strdup(val);
				attributeEndCheck
			}

		} else if (strcmp(name,RI_TRACE) == 0) {
			for (i=0;i<n;i++) {
				if (FALSE) {
				attributeCheckFlag(RI_DISPLACEMENTS,	attributes->flags,									ATTRIBUTES_FLAGS_DISPLACEMENTS)
				attributeCheck(RI_BIAS,					attributes->shadowBias,								-C_INFINITY,C_INFINITY,float)
				attributeCheck(RI_MAXDIFFUSEDEPTH,		attributes->maxDiffuseDepth,						0,C_INFINITY,int)
				attributeCheck(RI_MAXSPECULARDEPTH,		attributes->maxSpecularDepth,						0,C_INFINITY,int)
				attributeEndCheck
			}
		// Check the irradiance cache options
		} else if (strcmp(name,RI_IRRADIANCE) == 0) {
			for (i=0;i<n;i++) {
				if (FALSE) {
				attributeCheckString(RI_HANDLE,			attributes->irradianceHandle)
				attributeCheckString(RI_FILEMODE,		attributes->irradianceHandleMode)
				attributeCheck(RI_MAXERROR,				attributes->irradianceMaxError,		0,C_INFINITY,float)

				if (attributes->irradianceMaxError > 0)	attributes->irradianceMaxError = 0.5f/attributes->irradianceMaxError;

				attributeEndCheck
			}
		} else if (strcmp(name,RI_PHOTON) == 0) {
			for (i=0;i<n;i++) {
				if (strcmp(tokens[i],RI_GLOBALMAP) == 0) {
					if (attributes->globalMapName != NULL) free(attributes->globalMapName);
					attributes->globalMapName	=	strdup(((char **) params[i])[0]);
				} else if (strcmp(tokens[i],RI_CAUSTICMAP) == 0) {
					if (attributes->causticMapName != NULL) free(attributes->causticMapName);
					attributes->causticMapName	=	strdup(((char **) params[i])[0]);
				} else if (strcmp(tokens[i],RI_SHADINGMODEL) == 0) {
					const char *val	=	((const char **) params[i])[0];

					if (strcmp(val,"matte") == 0) {
						attributes->shadingModel	=	SM_MATTE;
					} else if (strcmp(val,"translucent") == 0) {
						attributes->shadingModel	=	SM_TRANSLUCENT;
					} else if (strcmp(val,"chrome") == 0) {
						attributes->shadingModel	=	SM_CHROME;
					} else if (strcmp(val,"glass") == 0) {
						attributes->shadingModel	=	SM_GLASS;
					} else if (strcmp(val,"water") == 0) {
						attributes->shadingModel	=	SM_WATER;
					} else if (strcmp(val,"dielectric") == 0) {
						attributes->shadingModel	=	SM_DIELECTRIC;
					} else if (strcmp(val,"transparent") == 0) {
						attributes->shadingModel	=	SM_TRANSPARENT;
					} else {
						error(CODE_BADTOKEN,"Unknown shading model: \"%s\"\n",val);
					}
				} else if (strcmp(tokens[i],RI_IOR) == 0) {
					float	*val	=	(float *) params[i];
					if (val[0] < 0) {
						error(CODE_RANGE,"Invalid value for \"%s\"\n",RI_IOR);
					} else {
						attributes->photonIor[0] = attributes->photonIor[1]	= val[0];
					}
				}  else if (strcmp(tokens[i],RI_IORRANGE) == 0) {
					float	*val	=	(float *) params[i];
					if ((val[0] < 0) || (val[1] < 0)) {
						error(CODE_RANGE,"Invalid value for \"%s\"\n",RI_IORRANGE);
					} else {
						attributes->photonIor[0] 	=	val[0];
						attributes->photonIor[1]	=	val[1];
					}
				attributeCheck(RI_ESTIMATOR,			attributes->photonEstimator,						1,C_INFINITY,int)
				attributeCheckFlag(RI_ILLUMINATEFRONT,	attributes->flags,									ATTRIBUTES_FLAGS_ILLUMINATE_FRONT_ONLY)
				attributeEndCheck
			}
		} else if (strcmp(name,RI_VISIBILITY) == 0) {
			for (i=0;i<n;i++) {
				if (strcmp(tokens[i],RI_TRANSMISSION) == 0) {
					char	*val	=	((char **) params[i])[0];

					attributes->flags	|=	ATTRIBUTES_FLAGS_TRANSMISSION_VISIBLE;
					if (strcmp(val,"opaque") == 0)		attributes->transmission	=	'o';
					else if (strcmp(val,"Os") == 0)		attributes->transmission	=	'i';
					else if (strcmp(val,"shader") == 0)	attributes->transmission	=	's';
					else if (strcmp(val,"transparent") == 0)	{
						attributes->flags	&=	~ATTRIBUTES_FLAGS_TRANSMISSION_VISIBLE;
					} else {
						error(CODE_BADTOKEN,"Unknown transmission value: %s\n",val);
					}
				attributeCheckFlag(RI_CAMERA,			attributes->flags,	ATTRIBUTES_FLAGS_PRIMARY_VISIBLE)
				attributeCheckFlag(RI_TRACE,			attributes->flags,	ATTRIBUTES_FLAGS_TRACE_VISIBLE)
				attributeCheckFlag(RI_PHOTON,			attributes->flags,	ATTRIBUTES_FLAGS_PHOTON_VISIBLE)
				attributeEndCheck
			}
		} else if (strcmp(name,RI_IDENTIFIER) == 0) {
			for (i=0;i<n;i++) {
				if (FALSE) {
				attributeCheckString(RI_NAME,			attributes->name)
				attributeEndCheck
			}
		 } else if (strcmp(name,RI_CULL) == 0) {
			for (i=0;i<n;i++) {
				if (FALSE) {
				attributeCheckInvertFlag(RI_HIDDEN,		attributes->flags,	ATTRIBUTES_FLAGS_SHADE_HIDDEN)
				attributeCheckInvertFlag(RI_BACKFACING,	attributes->flags,	ATTRIBUTES_FLAGS_SHADE_BACKFACE)
				attributeEndCheck
			}
		} else {
			error(CODE_BADTOKEN,"Unknown attribute: \"%s\"\n",name);
		}
	}
}

#undef	attributeCheck
#undef	attributeCheckFlag
#undef	attributeCheckString
#undef	attributeEndCheck

void	CRendererContext::RiPolygonV(int nvertices,int n,char *tokens[],void *params[]) {
	CXform			*xform;
	CAttributes		*attributes;
	float			*p0,*p1;
	CPl				*pl;
	
	if (netNumServers > 0)	return;

	xform			=	getXform(FALSE);
	attributes		=	getAttributes(FALSE);
	
	checkGeometryOrDiscard();
	
	pl				=	parseParameterList(1,nvertices,0,nvertices,n,tokens,(void **) params,RI_P,PL_VARYING_TO_VERTEX,attributes);
	if (pl == NULL)	return;

	// We have the core
	switch(addMotion(pl->data0,pl->dataSize,"RiPolygon",p0,p1)) {
	case 0:
		delete pl;
		return;
		break;
	case 1:
		// Restore the parameters
		if (pl->data0 != p0)
			memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);			
		break;
	case 2:
		// Restore the parameters
		memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);
		pl->append(p1);
		break;
	}

	int	*vertices		=	(int *) alloca(nvertices*sizeof(int));
	int	i;

	for (i=0;i<nvertices;i++) {
		vertices[i]	=	i;
	}

	i	=	1;

	addObject(new CPolygonMesh(attributes,xform,pl,1,&i,&nvertices,vertices));
}


void	CRendererContext::RiGeneralPolygonV(int nloops,int *nverts,int n,char *tokens[],void *params[]) {
	CXform			*xform;
	CAttributes		*attributes;
	float			*p0,*p1;
	CPl				*pl;
	int				i,nvertices;

	if (netNumServers > 0)	return;

	xform			=	getXform(FALSE);
	attributes		=	getAttributes(FALSE);
	
	checkGeometryOrDiscard();

	nvertices=0;
	for (i=0;i<nloops;i++) {
		nvertices	+=	nverts[i];
	}
	
	pl				=	parseParameterList(1,nvertices,0,nvertices,n,tokens,(void **) params,RI_P,PL_VARYING_TO_VERTEX,attributes);
	if (pl == NULL)	return;

	// We have the core
	switch(addMotion(pl->data0,pl->dataSize,"RiGeneralPolygon",p0,p1)) {
	case 0:
		delete pl;
		return;
		break;
	case 1:
		if (pl->data0 != p0)
			memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);
		break;
	case 2:
		memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);
		pl->append(p1);
		break;
	}

	// Get the core and allocate the polygon
	int	*vertices		=	(int *) alloca(nvertices*sizeof(int));

	for (i=0;i<nvertices;i++) {
		vertices[i]	=	i;
	}


	addObject(new CPolygonMesh(attributes,xform,pl,1,&nloops,nverts,vertices));
}

void	CRendererContext::RiPointsPolygonsV(int npolys,int *nverts,int *verts,int n,char *tokens[],void *params[]) {
	CXform			*xform;
	CAttributes		*attributes;
	float			*p0,*p1;
	CPl				*pl;
	int				i,nvertices,mvertex;

	if (netNumServers > 0)	return;

	xform			=	getXform(FALSE);
	attributes		=	getAttributes(FALSE);
	
	checkGeometryOrDiscard();

	nvertices	=	0;
	mvertex		=	0;

	for (i=0;i<npolys;i++) {
		nvertices	+=	nverts[i];
	}

	for (i=0;i<nvertices;i++) {
		mvertex		=	max(mvertex,verts[i]);
	}

	pl				=	parseParameterList(npolys,mvertex+1,0,nvertices,n,tokens,(void **) params,RI_P,PL_VARYING_TO_VERTEX,attributes);
	if (pl == NULL)	return;

	// We have the core
	switch(addMotion(pl->data0,pl->dataSize,"RiPointsPolygons",p0,p1)) {
	case 0:
		delete pl;
		return;
		break;
	case 1:
		// Restore the parameters
		if (pl->data0 != p0)
			memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);

		break;
	case 2:
		// Restore the parameters
		memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);
		pl->append(p1);

		break;
	default:
		break;
	}	

	// Get the core and allocate the polygon
	memBegin();

	int	*nloops		=	(int *) ralloc(npolys*sizeof(int));
	int	i;

	for (i=0;i<npolys;i++) {
		nloops[i]	=	1;
	}

	addObject(new CPolygonMesh(attributes,xform,pl,npolys,nloops,nverts,verts));

	memEnd();
}

void	CRendererContext::RiPointsGeneralPolygonsV(int npolys,int *nloops,int *nverts,int *verts,int n,char *tokens[],void *params[]) {
	CXform			*xform;
	CAttributes		*attributes;
	float			*p0,*p1;
	CPl				*pl;
	int				i,j,k;

	int				sloops;				// The size of the loops array
	int				snverts;			// The size of the nverts array
	int				sverts;				// The size of the verts array
	int				numVertices;		// The number of vertices

	if (netNumServers > 0)	return;

	xform			=	getXform(FALSE);
	attributes		=	getAttributes(FALSE);
	
	checkGeometryOrDiscard();

	sloops		=	npolys;
	snverts		=	0;
	sverts		=	0;
	numVertices	=	0;
	k			=	0;

	for (i=0;i<sloops;i++) {
		snverts	+=	nloops[i];
		for (j=0;j<nloops[i];j++,k++) {
			sverts	+=	nverts[k];
		}
	}

	for (i=0;i<sverts;i++) {
		numVertices	=	max(numVertices,verts[i]);
	}
	
	pl				=	parseParameterList(npolys,numVertices+1,0,sverts,n,tokens,(void **) params,RI_P,PL_VARYING_TO_VERTEX,attributes);
	if (pl == NULL)	return;

	// We have the core
	switch(addMotion(pl->data0,pl->dataSize,"RiPointsGeneralPolygons",p0,p1)) {
	case 0:
		delete pl;
		return;
		break;
	case 1:
		// Restore the parameters
		if (pl->data0 != p0)
			memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);

		break;
	case 2:
		// Restore the parameters
		memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);
		pl->append(p1);

		break;
	default:
		break;
	}

	addObject(new CPolygonMesh(attributes,xform,pl,npolys,nloops,nverts,verts));
}

void	CRendererContext::RiBasis(float ubasis[][4],int ustep,float vbasis[][4],int vstep) {
	CAttributes *attributes;
	matrix		mtmp;
	int			i,j;

	// This is used in the client to parse the rib so we
	//  must not bail out when neterendering...

	attributes	=	getAttributes(TRUE);

	attributes->uStep	=	ustep;
	attributes->vStep	=	vstep;

	for (i=0;i<4;i++)
		for (j=0;j<4;j++)
			mtmp[element(i,j)]	=	ubasis[j][i];
	movmm(attributes->uBasis,mtmp);

	for (i=0;i<4;i++)
		for (j=0;j<4;j++)
			mtmp[element(i,j)]	=	vbasis[j][i];
	movmm(attributes->vBasis,mtmp);
}

#define	correct3begin(xv,yv)													\
{																				\
	int		i;																	\
	char	**newTokens	=	(char **) ralloc(n*sizeof(char *));					\
	memcpy(newTokens,tokens,n*sizeof(char *));									\
	tokens				=	newTokens;											\
	for (i=0;i<n;i++) {															\
		if (strcmp(tokens[i],RI_PZ) == 0)	{									\
			float	*newData	=	(float *) ralloc(xv*yv*3*sizeof(float));	\
			float	*oldData	=	(float *) params[i];						\
			int		x,y;														\
			params[i]			=	(char *) newData;							\
			tokens[i]			=	(char *) RI_P;								\
																				\
			for (y=0;y<yv;y++) {												\
				for (x=0;x<xv;x++) {											\
					*newData++		=	x / (float) (xv-1);						\
					*newData++		=	y / (float) (yv-1);						\
					*newData++		=	*oldData++;								\
				}																\
			}																	\
		} else if (strcmp(tokens[i],RI_PW) == 0)	{							\
			float	*newData	=	(float *) ralloc(xv*yv*3*sizeof(float));	\
			float	*oldData	=	(float *) params[i];						\
			int		x,y;														\
			params[i]			=	(char *) newData;							\
			tokens[i]			=	(char *) RI_P;								\
																				\
			for (y=0;y<yv;y++) {												\
				for (x=0;x<xv;x++) {											\
					*newData++		=	oldData[0] / oldData[3];				\
					*newData++		=	oldData[1] / oldData[3];				\
					*newData++		=	oldData[2] / oldData[3];				\
					oldData			+=	4;										\
				}																\
			}																	\
		}																		\
	}																			\
}

#define correct3cbegin(xv)														\
{																				\
	int		i;																	\
	char	**newTokens	=	(char **) ralloc(n*sizeof(char *));					\
	memcpy(newTokens,tokens,n*sizeof(char *));									\
	tokens				=	newTokens;											\
	for (i=0;i<n;i++) {															\
		if (strcmp(tokens[i],RI_PW) == 0)	{									\
			float	*newData	=	(float *) ralloc(xv*3*sizeof(float));		\
			float	*oldData	=	(float *) params[i];						\
			int		x;															\
			params[i]			=	(char *) newData;							\
			tokens[i]			=	(char *) RI_P;								\
																				\
			for (x=0;x<xv;x++) {												\
				*newData++		=	oldData[0] / oldData[3];					\
				*newData++		=	oldData[1] / oldData[3];					\
				*newData++		=	oldData[2] / oldData[3];					\
				oldData			+=	4;											\
			}																	\
		}																		\
	}																			\
}

#define	correct4begin(xv,yv)													\
{																				\
	int		i;																	\
	char	**newTokens	=	(char **) ralloc(n*sizeof(char *));					\
	memcpy(newTokens,tokens,n*sizeof(char *));									\
	tokens				=	newTokens;											\
	for (i=0;i<n;i++) {															\
		if (strcmp(tokens[i],RI_PZ) == 0)	{									\
			float	*newData	=	(float *) ralloc(xv*yv*4*sizeof(float));	\
			float	*oldData	=	(float *) params[i];						\
			int		x,y;														\
			params[i]			=	(char *) newData;							\
			tokens[i]			=	(char *) RI_PW;								\
																				\
			for (y=0;y<yv;y++) {												\
				for (x=0;x<xv;x++) {											\
					*newData++		=	x / (float) (xv-1);						\
					*newData++		=	y / (float) (yv-1);						\
					*newData++		=	*oldData++;								\
					*newData++		=	1;										\
				}																\
			}																	\
																				\
		} else if (strcmp(tokens[i],RI_P) == 0) {								\
			float	*newData	=	(float *) ralloc(xv*yv*4*sizeof(float));	\
			float	*oldData	=	(float *) params[i];						\
			int		x,y;														\
			params[i]			=	(char *) newData;							\
			tokens[i]			=	(char *) RI_PW;								\
																				\
			for (y=0;y<yv;y++) {												\
				for (x=0;x<xv;x++) {											\
					*newData++		=	*oldData++;								\
					*newData++		=	*oldData++;								\
					*newData++		=	*oldData++;								\
					*newData++		=	1;										\
				}																\
			}																	\
		}																		\
	}																			\
}


void	CRendererContext::RiPatchV (char * type,int n,char *tokens[],void *params[]) {
	CXform			*xform;
	CAttributes		*attributes;
	float			*p0,*p1;
	int				uver,vver;
	int				degree;
	CPl				*pl;

	if (netNumServers > 0)	return;

	xform			=	getXform(FALSE);
	attributes		=	getAttributes(FALSE);
	
	checkGeometryOrDiscard();

	if (strcmp(type,RI_BILINEAR) == 0)			{
		degree	=	1;
		uver	=	2;
		vver	=	2;
	} else if (strcmp(type,RI_BICUBIC) == 0)	{
		degree	=	3;
		uver	=	4;	
		vver	=	4;
	} else {
		error(CODE_BADTOKEN,"Unknown patch type: %s\n",type);
		return;
	}

	memBegin();

	correct3begin(uver,vver);
	
	pl				=	parseParameterList(1,uver*vver,4,0,n,tokens,(void **) params,RI_P,0,attributes);

	if (pl != NULL) {
		// We have the core
		switch(addMotion(pl->data0,pl->dataSize,"RiPatch",p0,p1)) {
		case 0:
			delete pl;
			break;
		case 1:
			// Restore the parameters
			if (pl->data0 != p0)
				memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);

			addObject(new CPatchMesh(attributes,xform,pl,degree,uver,vver,FALSE,FALSE));

			break;
		case 2:
			// Restore the parameters
			memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);
			pl->append(p1);

			addObject(new CPatchMesh(attributes,xform,pl,degree,uver,vver,FALSE,FALSE));
			break;
		default:
			break;
		}	
	}

	memEnd();
}


void	CRendererContext::RiPatchMeshV(char *type,int nu,char * uwrap,int nv,char *vwrap,int n,char *tokens[],void *params[]) {
	CXform			*xform;
	CAttributes		*attributes;
	float			*p0,*p1;
	int				uw,vw;
	int				upatches,vpatches;
	CPl				*pl;
	int				numVertex,numVarying,numUniform;
	int				degree;

	if (netNumServers > 0)	return;

	attributes		=	getAttributes(FALSE);
	
	checkGeometryOrDiscard();

	if (strcmp(uwrap,RI_PERIODIC) == 0) {
		uw	=	TRUE;
	} else if ((strcmp(uwrap,RI_NONPERIODIC) == 0) || (strcmp(uwrap,RI_NOWRAP) == 0)) {
		uw	=	FALSE;
	} else {
		error(CODE_BADTOKEN,"Wrapping mode unrecognised: \"%s\"\n",uwrap);
		return;
	}

	if (strcmp(vwrap,RI_PERIODIC) == 0) {
		vw	=	TRUE;
	} else if ((strcmp(vwrap,RI_NONPERIODIC) == 0) || (strcmp(vwrap,RI_NOWRAP) == 0)) {
		vw	=	FALSE;
	} else {
		error(CODE_BADTOKEN,"Wrapping mode unrecognised: \"%s\"\n",vwrap);
		return;
	}

	if (strcmp(type,RI_BICUBIC) == 0) {
		degree	=	3;

		if (uw)		{
			if ((nu % attributes->uStep) != 0) {
				error(CODE_MISSINGDATA,"Unexpected number of u vertices \n");
				return;
			}

			upatches	=	(nu) / attributes->uStep;
		} else {
			if (((nu - 4) % attributes->uStep) != 0) {
				error(CODE_MISSINGDATA,"Unexpected number of u vertices \n");
				return;
			}

			upatches	=	((nu - 4) / attributes->uStep)+1;
		}

		if (vw)		{
			if ((nv % attributes->vStep) != 0) {
				error(CODE_MISSINGDATA,"Unexpected number of v vertices \n");
				return;
			}

			vpatches	=	(nv) / attributes->vStep;
		} else {
			if (((nv - 4) % attributes->vStep) != 0) {
				error(CODE_MISSINGDATA,"Unexpected number of v vertices \n");
				return;
			}

			vpatches	=	((nv - 4) / attributes->vStep)+1;
		}

		numVertex		=	nu*nv;
		numVarying		=	(upatches+1-uw)*(vpatches+1-vw);
		numUniform		=	upatches*vpatches;
	} else if (strcmp(type,RI_BILINEAR) == 0) {
		degree	=	1;
		if (uw)
			upatches	=	nu;
		else
			upatches	=	nu-1;

		if (vw)
			vpatches	=	nv;
		else
			vpatches	=	nv-1;

		numVertex		=	nu*nv;
		numVarying		=	nu*nv;
		numUniform		=	upatches*vpatches;
	} else {
		error(CODE_BADTOKEN,"Unknown patch type: %s\n",type);
		return;
	}

	memBegin();

	correct3begin(nu,nv);

	xform			=	getXform(FALSE);
	pl				=	parseParameterList(numUniform,numVertex,numVarying,0,n,tokens,(void **) params,RI_P,0,attributes);

	if (pl != NULL) {
		// We have the core
		switch(addMotion(pl->data0,pl->dataSize,"RiPatchMesh",p0,p1)) {
		case 0:
			delete pl;
			break;
		case 1:
			// Restore the parameters
			if (pl->data0 != p0)
				memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);

 			addObject(new CPatchMesh(attributes,xform,pl,degree,nu,nv,uw,vw));

			break;
		case 2:
			memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);
			pl->append(p1);

			addObject(new CPatchMesh(attributes,xform,pl,degree,nu,nv,uw,vw));

			break;
		}	
	}

	memEnd();
}

void	CRendererContext::RiNuPatchV(int nu,int uorder,float *uknot,float umin,float umax,int nv,int vorder,float *vknot,float vmin,float vmax,int n,char *tokens[],void *params[]) {
	CXform			*xform;
	CAttributes		*attributes;
	float			*p0,*p1;
	int				upatches,vpatches;
	CPl				*pl;

	if (netNumServers > 0)	return;

	xform			=	getXform(FALSE);
	attributes		=	getAttributes(FALSE);
	
	checkGeometryOrDiscard();

	memBegin();

	correct4begin(nu,nv);

	upatches		=	nu - uorder + 1;
	vpatches		=	nv - vorder + 1;
	
	pl				=	parseParameterList(upatches*vpatches,nu*nv,(upatches+1)*(vpatches+1),0,n,tokens,(void **) params,RI_PW,0,attributes);

	if (pl != NULL) {
		// We have the core
		switch(addMotion(pl->data0,pl->dataSize,"RiNuPatch",p0,p1)) {
		case 0:
			delete pl;
			break;
		case 1:
			// Restore the parameters
			if (pl->data0 != p0)
				memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);

			addObject(new CNURBSPatchMesh(attributes,xform,pl,nu,nv,uorder,vorder,uknot,vknot));

			break;
		case 2:
			memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);
			pl->append(p1);

			addObject(new CNURBSPatchMesh(attributes,xform,pl,nu,nv,uorder,vorder,uknot,vknot));

			break;
		default:
			break;
		}	
	}

	memEnd();
}

void	CRendererContext::RiTrimCurve (int nloops,int *ncurves,int *order,float *knot,float *amin,float *amax,int *n,float *u,float *v,float *w) {
	if (netNumServers > 0)	return;

	error(CODE_INCAPABLE,"Trim curves are not implemented yet (yet).\n");
}

void	CRendererContext::RiCurvesV(char *d,int ncurves,int nverts[], char *w,int n,char *tokens[],void *params[]) {
	CAttributes	*attributes;
	CXform		*xform;
	float		*p0,*p1;
	int			numVertices,numSegments,numVaryings;
	int			i;
	int			degree,wrap;
	CPl			*pl;

	if (netNumServers > 0)	return;

	attributes		=	getAttributes(FALSE);
	
	checkGeometryOrDiscard();
	
	xform			=	getXform(FALSE);

	if (strcmp(d,RI_LINEAR) == 0) {
		degree	=	1;

		if (strcmp(w,RI_PERIODIC) == 0) {
			for (numVertices=0,numSegments=0,numVaryings=0,i=0;i<ncurves;i++) {
				numVertices	+=	nverts[i];
				numSegments	+=	nverts[i];
				numVaryings	+=	nverts[i];
			}

			wrap		=	TRUE;
		} else {
			for (numVertices=0,numSegments=0,numVaryings=0,i=0;i<ncurves;i++) {
				numVertices	+=	nverts[i];
				numSegments	+=	nverts[i] - 1;
				numVaryings	+=	nverts[i];
			}

			wrap		=	FALSE;
		}
	} else if (strcmp(d,RI_CUBIC) == 0) {
		degree	=	3;

		if (strcmp(w,RI_PERIODIC) == 0) {
			for (numVertices=0,numSegments=0,numVaryings=0,i=0;i<ncurves;i++) {
				numVertices	+=	nverts[i];
				numSegments	+=	(nverts[i] - 4) / attributes->vStep + 1;
				numVaryings	+=	(nverts[i] - 4) / attributes->vStep + 1;
			}

			wrap		=	TRUE;
		} else {
			for (numVertices=0,numSegments=0,numVaryings=0,i=0;i<ncurves;i++) {
				numVertices	+=	nverts[i];
				numSegments	+=	nverts[i] / attributes->vStep;
				numVaryings	+=	(nverts[i] - 4) / attributes->vStep + 2;
			}

			wrap		=	FALSE;
		}
	} else {
		error(CODE_BADTOKEN,"Unknown curve degree: \"%s\"\n",d);
		return;
	}

	memBegin();
	
	correct3cbegin(numVertices);
	
	pl				=	parseParameterList(ncurves,numVertices,numVaryings,0,n,tokens,(void **) params,RI_P,0,attributes);
	if (pl == NULL)	return;
	

	// We have the core
	switch(addMotion(pl->data0,pl->dataSize,"CRendererContext::RiCurves",p0,p1)) {
	case 0:
		if (pl != NULL)	delete pl;
		break;
	case 1:
		if (p0 != pl->data0)
			memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);

		addObject(new CCurveMesh(attributes,xform,pl,degree,numVertices,ncurves,nverts,wrap));

		break;
	case 2:
		// Restore the parameters
		memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);
		pl->append(p1);

		addObject(new CCurveMesh(attributes,xform,pl,degree,numVertices,ncurves,nverts,wrap));

		break;
	default:
		break;
	}	

	memEnd();

}

#undef correct3begin
#undef correct4begin
#undef correct3cbegin

void	CRendererContext::RiSphereV(float radius,float zmin,float zmax,float thetamax,int n,char *tokens[],void *params[]) {
	CXform			*xform;
	CAttributes		*attributes;
	float			*p0,*p1;
	float			*data;
	int				dataSize;
	CPl				*pl;
	CParameter		*parameters;
	unsigned int	parametersF;
	float			tmp;

	if (netNumServers > 0)	return;

	attributes		=	getAttributes(FALSE);
	xform			=	getXform(FALSE);
	
	checkGeometryOrDiscard();
	
	pl				=	parseParameterList(1,0,4,0,n,tokens,(void **) params,NULL,PL_VERTEX_TO_VARYING,attributes);

	memBegin();

	if (pl == NULL) {
		data		=	(float *) ralloc(4*sizeof(float));
		dataSize	=	4;
		parametersF	=	0;
	} else {
		data		=	(float *) ralloc((pl->dataSize+4)*sizeof(float));
		dataSize	=	4+pl->dataSize;
		memcpy(&data[4],pl->data0,pl->dataSize*sizeof(float));
		parametersF	=	pl->parameterUsage();
	}

	data[0]			=	radius;
	data[1]			=	zmin;
	data[2]			=	zmax;
	data[3]			=	thetamax;

	// We have the core
	switch(addMotion(data,dataSize,"CRendererContext::RiSphere",p0,p1)) {
	case 0:
		break;
	case 1:
		if (pl != NULL)	memcpy(pl->data0,&p0[4],sizeof(float)*pl->dataSize);

		parameters	=	pl->uniform(0,NULL);
		parameters	=	pl->varying(0,1,2,3,parameters);;

		tmp			=	absf(p0[0]);
		p0[1]		=	min(max(p0[1],-tmp),tmp);
		p0[2]		=	min(max(p0[2],-tmp),tmp);
		p0[1]		=	(float) asin(p0[1] / p0[0]);
		p0[2]		=	(float) asin(p0[2] / p0[0]);

		addObject(new CSphere(attributes,xform,parameters,parametersF,p0[0],p0[1],p0[2],(float) radians(p0[3])));
		break;
	case 2:
		// Restore the parameters
		if (pl != NULL)	{
			memcpy(pl->data0,&p0[4],sizeof(float)*pl->dataSize);
			pl->append(p1+4);
		}

		parameters	=	pl->uniform(0,NULL);
		parameters	=	pl->varying(0,1,2,3,parameters);;

		tmp			=	absf(p0[0]);
		p0[1]		=	min(max(p0[1],-tmp),tmp);
		p0[2]		=	min(max(p0[2],-tmp),tmp);
		p0[1]		=	(float) asin(p0[1] / p0[0]);
		p0[2]		=	(float) asin(p0[2] / p0[0]);

		tmp			=	absf(p0[1]);
		p1[1]		=	min(max(p1[1],-tmp),tmp);
		p1[2]		=	min(max(p1[2],-tmp),tmp);
		p1[1]		=	(float) asin(p1[1] / p1[0]);
		p1[2]		=	(float) asin(p1[2] / p1[0]);

		addObject(new CSphere(attributes,xform,parameters,parametersF,p0[0],p0[1],p0[2],(float) radians(p0[3]),p1[0],p1[1],p1[2],(float) radians(p1[3])));
		break;
	default:
		break;
	}	

	if (pl != NULL)	delete pl;

	memEnd();
}

void	CRendererContext::RiConeV (float height,float radius,float thetamax,int n,char *tokens[],void *params[]) {
	CXform			*xform;
	CAttributes		*attributes;
	float			*p0,*p1;
	float			*data;
	int				dataSize;
	CPl				*pl;
	CParameter		*parameters;
	unsigned int	parametersF;

	if (netNumServers > 0)	return;

	attributes		=	getAttributes(FALSE);
	
	checkGeometryOrDiscard();
	
	xform			=	getXform(FALSE);
	pl				=	parseParameterList(1,0,4,0,n,tokens,(void **) params,NULL,PL_VERTEX_TO_VARYING,attributes);

	memBegin();

	if (pl == NULL) {
		data		=	(float *) ralloc(3*sizeof(float));
		dataSize	=	3;
		parametersF	=	0;
	} else {
		data		=	(float *) ralloc((pl->dataSize+3)*sizeof(float));
		dataSize	=	3+pl->dataSize;
		memcpy(&data[3],pl->data0,pl->dataSize*sizeof(float));
		parametersF	=	pl->parameterUsage();
	}

	data[0]			=	radius;
	data[1]			=	height;
	data[2]			=	thetamax;

	// We have the core
	switch(addMotion(data,dataSize,"CRendererContext::RiCone",p0,p1)) {
	case 0:
		break;
	case 1:
		if (pl != NULL)	memcpy(pl->data0,&p0[3],sizeof(float)*pl->dataSize);

		parameters	=	pl->uniform(0,NULL);
		parameters	=	pl->varying(0,1,2,3,parameters);;

		addObject(new CCone(attributes,xform,parameters,parametersF,p0[0],p0[1],(float) radians(p0[2])));
		break;
	case 2:
		// Restore the parameters
		if (pl != NULL)	{
			memcpy(pl->data0,&p0[3],sizeof(float)*pl->dataSize);
			pl->append(p1+3);
		}

		parameters	=	pl->uniform(0,NULL);
		parameters	=	pl->varying(0,1,2,3,parameters);;

		addObject(new CCone(attributes,xform,parameters,parametersF,p0[0],p0[1],(float) radians(p0[2]),p1[0],p1[1],(float) radians(p1[2])));
		break;
	default:
		break;
	}	

	if (pl != NULL)	delete pl;

	memEnd();
}

void	CRendererContext::RiCylinderV (float radius,float zmin,float zmax,float thetamax,int n,char *tokens[],void *params[]) {
	CXform			*xform;
	CAttributes		*attributes;
	float			*p0,*p1;
	float			*data;
	int				dataSize;
	CPl				*pl;
	CParameter		*parameters;
	unsigned int	parametersF;

	if (netNumServers > 0)	return;

	attributes		=	getAttributes(FALSE);
	
	checkGeometryOrDiscard();
	
	xform			=	getXform(FALSE);
	pl				=	parseParameterList(1,0,4,0,n,tokens,(void **) params,NULL,PL_VERTEX_TO_VARYING,attributes);

	memBegin();

	if (pl == NULL) {
		data		=	(float *) ralloc(4*sizeof(float));
		dataSize	=	4;
		parametersF	=	0;
	} else {
		data		=	(float *) ralloc((pl->dataSize+4)*sizeof(float));
		dataSize	=	4+pl->dataSize;
		memcpy(&data[4],pl->data0,pl->dataSize*sizeof(float));
		parametersF	=	pl->parameterUsage();
	}

	data[0]			=	radius;
	data[1]			=	zmin;
	data[2]			=	zmax;
	data[3]			=	thetamax;

	// We have the core
	switch(addMotion(data,dataSize,"CRendererContext::RiCylinder",p0,p1)) {
	case 0:
		break;
	case 1:
		if (pl != NULL)	memcpy(pl->data0,&p0[4],sizeof(float)*pl->dataSize);

		parameters	=	pl->uniform(0,NULL);
		parameters	=	pl->varying(0,1,2,3,parameters);;

		addObject(new CCylinder(attributes,xform,parameters,parametersF,p0[0],p0[1],p0[2],(float) radians(p0[3])));
		break;
	case 2:
		// Restore the parameters
		if (pl != NULL)	{
			memcpy(pl->data0,&p0[4],sizeof(float)*pl->dataSize);
			pl->append(p1+4);
		}

		parameters	=	pl->uniform(0,NULL);
		parameters	=	pl->varying(0,1,2,3,parameters);;

		addObject(new CCylinder(attributes,xform,parameters,parametersF,p0[0],p0[1],p0[2],(float) radians(p0[3]),p1[0],p1[1],p1[2],(float) radians(p1[3])));
		break;
	default:
		break;
	}	

	if (pl != NULL)	delete pl;

	memEnd();
}

void	CRendererContext::RiHyperboloidV (float *point1,float *point2,float thetamax,int n,char *tokens[],void *params[]) {
	CXform			*xform;
	CAttributes		*attributes;
	float			*p0,*p1;
	float			*data;
	int				dataSize;
	CPl				*pl;
	CParameter		*parameters;
	unsigned int	parametersF;

	if (netNumServers > 0)	return;

	attributes		=	getAttributes(FALSE);
	
	checkGeometryOrDiscard();
	
	xform			=	getXform(FALSE);
	pl				=	parseParameterList(1,0,4,0,n,tokens,(void **) params,NULL,PL_VERTEX_TO_VARYING,attributes);

	memBegin();

	if (pl == NULL) {
		data		=	(float *) ralloc(7*sizeof(float));
		dataSize	=	7;
		parametersF	=	0;
	} else {
		data		=	(float *) ralloc((pl->dataSize+7)*sizeof(float));
		dataSize	=	7+pl->dataSize;
		memcpy(&data[7],pl->data0,pl->dataSize*sizeof(float));
		parametersF	=	pl->parameterUsage();
	}

	data[0]			=	point1[0];
	data[1]			=	point1[1];
	data[2]			=	point1[2];
	data[3]			=	point2[0];
	data[4]			=	point2[1];
	data[5]			=	point2[2];
	data[6]			=	thetamax;

	// We have the core
	switch(addMotion(data,dataSize,"CRendererContext::RiHyperboloid",p0,p1)) {
	case 0:
		break;
	case 1:
		if (pl != NULL)	memcpy(pl->data0,&p0[7],sizeof(float)*pl->dataSize);

		parameters	=	pl->uniform(0,NULL);
		parameters	=	pl->varying(0,1,2,3,parameters);;

		addObject(new CHyperboloid(attributes,xform,parameters,parametersF,&p0[0],&p0[3],(float) radians(p0[6])));
		break;
	case 2:
		// Restore the parameters
		if (pl != NULL)	{
			memcpy(pl->data0,&p0[7],sizeof(float)*pl->dataSize);
			pl->append(p1+7);
		}

		parameters	=	pl->uniform(0,NULL);
		parameters	=	pl->varying(0,1,2,3,parameters);;

		addObject(new CHyperboloid(attributes,xform,parameters,parametersF,&p0[0],&p0[3],(float) radians(p0[6]),&p1[0],&p1[3],(float) radians(p1[6])));
		break;
	default:
		break;
	}	

	if (pl != NULL) delete pl;

	memEnd();
}

void	CRendererContext::RiParaboloidV(float radius,float zmin,float zmax,float thetamax,int n,char *tokens[],void *params[]) {
	CXform			*xform;
	CAttributes		*attributes;
	float			*p0,*p1;
	float			*data;
	int				dataSize;
	CPl				*pl;
	CParameter		*parameters;
	unsigned int	parametersF;

	if (netNumServers > 0)	return;

	attributes		=	getAttributes(FALSE);
	
	checkGeometryOrDiscard();
	
	xform			=	getXform(FALSE);
	pl				=	parseParameterList(1,0,4,0,n,tokens,(void **) params,NULL,PL_VERTEX_TO_VARYING,attributes);

	memBegin();

	if (pl == NULL) {
		data		=	(float *) ralloc(4*sizeof(float));
		dataSize	=	4;
		parametersF	=	0;
	} else {
		data		=	(float *) ralloc((pl->dataSize+4)*sizeof(float));
		dataSize	=	4+pl->dataSize;
		memcpy(&data[4],pl->data0,pl->dataSize*sizeof(float));
		parametersF	=	pl->parameterUsage();
	}

	data[0]			=	radius;
	data[1]			=	zmin;
	data[2]			=	zmax;
	data[3]			=	thetamax;

	// We have the core
	switch(addMotion(data,dataSize,"CRendererContext::RiParaboloid",p0,p1)) {
	case 0:
		break;
	case 1:
		if (pl != NULL)	memcpy(pl->data0,&p0[4],sizeof(float)*pl->dataSize);

		parameters	=	pl->uniform(0,NULL);
		parameters	=	pl->varying(0,1,2,3,parameters);;

		if (p0[1] != p0[2])
			addObject(new CParaboloid(attributes,xform,parameters,parametersF,p0[0],p0[1],p0[2],(float) radians(p0[3])));
		break;
	case 2:
		// Restore the parameters
		if (pl != NULL)	{
			memcpy(pl->data0,&p0[4],sizeof(float)*pl->dataSize);
			pl->append(p1+4);
		}

		parameters	=	pl->uniform(0,NULL);
		parameters	=	pl->varying(0,1,2,3,parameters);;

		if ((p0[1] != p0[2]) || (p1[1] != p1[2]))
			addObject(new CParaboloid(attributes,xform,parameters,parametersF,p0[0],p0[1],p0[2],(float) radians(p0[3]),p1[0],p1[1],p1[2],(float) radians(p1[3])));
		break;
	default:
		break;
	}	

	if (pl != NULL)	delete pl;

	memEnd();
}

void	CRendererContext::RiDiskV (float height,float radius,float thetamax,int n,char *tokens[],void *params[]) {
	CXform			*xform;
	CAttributes		*attributes;
	float			*p0,*p1;
	float			*data;
	int				dataSize;
	CPl				*pl;
	CParameter		*parameters;
	unsigned int	parametersF;

	if (netNumServers > 0)			return;

	attributes		=	getAttributes(FALSE);
	
	checkGeometryOrDiscard();
	
	xform			=	getXform(FALSE);
	pl				=	parseParameterList(1,0,4,0,n,tokens,(void **) params,NULL,PL_VERTEX_TO_VARYING,attributes);

	memBegin();

	if (pl == NULL) {
		data		=	(float *) ralloc(3*sizeof(float));
		dataSize	=	3;
		parametersF	=	0;
	} else {
		data		=	(float *) ralloc((pl->dataSize+3)*sizeof(float));
		dataSize	=	3+pl->dataSize;
		memcpy(&data[3],pl->data0,pl->dataSize*sizeof(float));
		parametersF	=	pl->parameterUsage();
	}


	data[0]			=	radius;
	data[1]			=	height;
	data[2]			=	thetamax;

	// We have the core
	switch(addMotion(data,dataSize,"CRendererContext::RiDisk",p0,p1)) {
	case 0:
		break;
	case 1:
		if (pl != NULL)	memcpy(pl->data0,&p0[3],sizeof(float)*pl->dataSize);

		parameters	=	pl->uniform(0,NULL);
		parameters	=	pl->varying(0,1,2,3,parameters);;

		addObject(new CDisk(attributes,xform,parameters,parametersF,p0[0],p0[1],(float) radians(p0[2])));
		break;
	case 2:
		// Restore the parameters
		if (pl != NULL)	{
			memcpy(pl->data0,&p0[3],sizeof(float)*pl->dataSize);
			pl->append(p1+3);
		}

		parameters	=	pl->uniform(0,NULL);
		parameters	=	pl->varying(0,1,2,3,parameters);;

		addObject(new CDisk(attributes,xform,parameters,parametersF,p0[0],p0[1],(float) radians(p0[2]),p1[0],p1[1],(float) radians(p1[2])));
		break;
	default:
		break;
	}	

	if (pl != NULL)	delete pl;

	memEnd();
}

void	CRendererContext::RiTorusV (float majorrad,float minorrad,float phimin,float phimax,float thetamax,int n,char *tokens[],void *params[]) {
	CXform			*xform;
	CAttributes		*attributes;
	float			*p0,*p1;
	float			*data;
	int				dataSize;
	CPl				*pl;
	CParameter		*parameters;
	unsigned int	parametersF;

	if (netNumServers > 0)	return;

	attributes		=	getAttributes(FALSE);
	
	checkGeometryOrDiscard();
	
	xform			=	getXform(FALSE);
	pl				=	parseParameterList(1,0,4,0,n,tokens,(void **) params,NULL,PL_VERTEX_TO_VARYING,attributes);

	memBegin();

	if (pl == NULL) {
		data		=	(float *) ralloc(5*sizeof(float));
		dataSize	=	5;
		parametersF	=	0;
	} else {
		data		=	(float *) ralloc((pl->dataSize+5)*sizeof(float));
		dataSize	=	5+pl->dataSize;
		memcpy(&data[5],pl->data0,pl->dataSize*sizeof(float));
		parametersF	=	pl->parameterUsage();
	}

	data[0]			=	minorrad;
	data[1]			=	majorrad;
	data[2]			=	phimin;
	data[3]			=	phimax;
	data[4]			=	thetamax;

	// We have the core
	switch(addMotion(data,dataSize,"CRendererContext::RiTorus",p0,p1)) {
	case 0:
		break;
	case 1:
		if (pl != NULL)	memcpy(pl->data0,&p0[5],sizeof(float)*pl->dataSize);

		parameters	=	pl->uniform(0,NULL);
		parameters	=	pl->varying(0,1,2,3,parameters);;

		addObject(new CToroid(attributes,xform,parameters,parametersF,p0[0],p0[1],(float) radians(p0[2]),(float) radians(p0[3]),(float) radians(p0[4])));
		break;
	case 2:
		// Restore the parameters
		if (pl != NULL)	{
			memcpy(pl->data0,&p0[5],sizeof(float)*pl->dataSize);
			pl->append(p1+5);
		}

		parameters	=	pl->uniform(0,NULL);
		parameters	=	pl->varying(0,1,2,3,parameters);;

		addObject(new CToroid(attributes,xform,parameters,parametersF,p0[0],p0[1],(float) radians(p0[2]),(float) radians(p0[3]),(float) radians(p0[4]),p1[0],p1[1],(float) radians(p1[2]),(float) radians(p1[3]),(float) radians(p1[4])));
		break;
	default:
		break;
	}	

	if (pl != NULL)	delete pl;

	memEnd();
}


void	CRendererContext::RiProcedural(void *data,float *bound,void (*subdivfunc) (void *,float),void (*freefunc) (void *)) {
	CDelayedObject	*cObject;
	CXform			*xform;
	CAttributes		*attributes;
	vector			bmin,bmax;

	if (netNumServers > 0)	return;

	xform		=	getXform(FALSE);
	attributes	=	getAttributes(FALSE);
	
	checkGeometryOrDiscard();

	if ((xform != NULL) && (attributes != NULL)) {
		bmin[COMP_X]	=	bound[0];
		bmax[COMP_X]	=	bound[1];
		bmin[COMP_Y]	=	bound[2];
		bmax[COMP_Y]	=	bound[3];
		bmin[COMP_Z]	=	bound[4];
		bmax[COMP_Z]	=	bound[5];

		cObject	=	new CDelayedObject(attributes,xform,bmin,bmax,subdivfunc,freefunc,data);

		addObject(cObject);
	}
}


void	CRendererContext::RiGeometryV(char *type,int n,char *tokens[],void *params[]) {
	if (netNumServers > 0)	return;
		
	if (strcmp(type,"implicit") == 0) {
		int				i;
		const char		*name				=	NULL;
		int				frame				=	currentOptions->frame;
		float			stepSize			=	(float) 0.1;
		float			scaleFactor			=	(float) 0.5;
		CAttributes		*attributes			=	getAttributes(FALSE);
		
		checkGeometryOrDiscard();

		for (i=0;i<n;i++) {
			if (strcmp(tokens[i],"file") == 0) {
				name				=	((const char **) params[i])[0];
			} else if (strcmp(tokens[i],"frame") == 0) {
				frame				=	(int) ((float *) params[i])[0];
			} else if (strcmp(tokens[i],"stepSize") == 0) {
				stepSize			=	((float *) params[i])[0];
			} else if (strcmp(tokens[i],"scaleFactor") == 0) {
				scaleFactor	=	((float *) params[i])[0];
			} else {
				CVariable	var;

				if (parseVariable(&var,NULL,tokens[i])) {
					tokens[i]	=	var.name;
					i--;
				} else {
					error(CODE_BADTOKEN,"Unrecognised implicit parameter: %s\n",tokens[i]);
				}
			}
		}

		if (name == NULL)	{
			error(CODE_BADTOKEN,"Implicit geometry requires a dso name\n");
		} else {
			char	location[OS_MAX_PATH_LENGTH];

			if (locateFileEx(location,name,osModuleExtension,currentOptions->proceduralPath)) {
				CObject	*cObject	=	new CImplicit(getAttributes(FALSE),getXform(FALSE),frame,location,stepSize,scaleFactor);

				addObject(cObject);
			} else {
				error(CODE_NOFILE,"Unable to find %s. Make sure it's in your procedural path\n",name);
			}
		}
	} else if (strcmp(type,"dlo") == 0) {
		int				i;
		const char		*name				=	NULL;
		int				frame				=	currentOptions->frame;
		CAttributes		*attributes			=	getAttributes(FALSE);
		
		checkGeometryOrDiscard();
		
		for (i=0;i<n;i++) {
			if (strcmp(tokens[i],"file") == 0) {
				name				=	(const char *) params[i];
			} else {
				CVariable	var;

				if (parseVariable(&var,NULL,tokens[i])) {
					tokens[i]	=	var.name;
					i--;
				} else {
					error(CODE_BADTOKEN,"Unrecognised implicit parameter: %s\n",tokens[i]);
				}
			}
		}

		if (name == NULL)	{
			error(CODE_BADTOKEN,"Dynamic object requires a dso name\n");
		} else {
			char	location[OS_MAX_PATH_LENGTH];

			if (locateFileEx(location,name,osModuleExtension,currentOptions->proceduralPath)) {
				void	*handle,*data;
				vector	bmin,bmax;

				handle		=	osLoadModule(name);

				if (handle != NULL) {
					dloInitFunction				initFunction		=	(dloInitFunction)		osResolve(handle,"dloInit");
					dloIntersectFunction		intersectFunction	=	(dloIntersectFunction)	osResolve(handle,"dloIntersect");
					dloTiniFunction				tiniFunction		=	(dloTiniFunction)		osResolve(handle,"dloTini");

					if (initFunction != NULL) {
						if (intersectFunction != NULL) {
							if (tiniFunction != NULL) {
								data	=	initFunction(frame,bmin,bmax);

								if (data != NULL) {
									addObject(new CDLObject(getAttributes(FALSE),getXform(FALSE),handle,data,bmin,bmax,initFunction,intersectFunction,tiniFunction));
								} else {
									error(CODE_BADFILE,"dlo %s failed to initialize\n",name);
								}
							} else {
								error(CODE_BADFILE,"Missing \"dloTini\" in dlo %s\n",name);
							}
						} else {
							error(CODE_BADFILE,"Missing \"dloIntersect\" in dlo %s\n",name);
						}
					} else {
						error(CODE_BADFILE,"Missing \"dloInit\" in dlo %s\n",name);
					}
				} else {
					error(CODE_BADFILE,"Unable to load dlo %s\n",name);
				}
			} else {
				error(CODE_NOFILE,"Unable to load %s (error %s)\n",name,osModuleError());
			}
		}
	} else {
		error(CODE_BADTOKEN,"Unknown geometry: \"%s\"\n",type);
	}
}


void	CRendererContext::RiPointsV(int npts,int n,char *tokens[],void *params[]) {
	CAttributes	*attributes;
	CXform		*xform;
	float		*p0,*p1;
	CPl			*pl;

	if (netNumServers > 0)	return;

	attributes		=	getAttributes(FALSE);
	
	checkGeometryOrDiscard();
	
	xform			=	getXform(FALSE);
	pl				=	parseParameterList(1,npts,0,0,n,tokens,(void **) params,RI_P,PL_VARYING_TO_VERTEX,attributes);
	if (pl == NULL)	return;

	memBegin();

	// We have the core
	switch(addMotion(pl->data0,pl->dataSize,"CRendererContext::RiPoints",p0,p1)) {
	case 0:
		if (pl != NULL)	delete pl;
		break;
	case 1:
		if (p0 != pl->data0)
			memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);

		addObject(new CPoints(attributes,xform,pl,npts));
		break;
	case 2:
		// Restore the parameters
		memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);
		pl->append(p1);

		addObject(new CPoints(attributes,xform,pl,npts));
		break;
	default:
		break;
	}	

	memEnd();
}

void	CRendererContext::RiSubdivisionMeshV(char * scheme,int nfaces,int nvertices[],int vertices[],int ntags, char * tags[],int nargs[],int intargs[],float floatargs[],int n,char *tokens[],void *params[]) {
	int			i,j;
	int			numVertices;
	CPl			*pl;
	CAttributes	*attributes;
	CXform		*xform;
	float		*p0,*p1;

	if (netNumServers > 0)	return;

	xform		=	getXform(FALSE);
	attributes	=	getAttributes(FALSE);

	checkGeometryOrDiscard();

	// Only catmull clark is supported for the time being
	if (strcmp(scheme,RI_CATMULLCLARK) != 0) {
		error(CODE_INCAPABLE,"Unknown subdivision scheme (%s).\n",scheme);
		return;
	}
	
	// save previous attributes so we don't mess with the basis for other primitives
	attributeBegin();
	attributes	=	getAttributes(FALSE);
	
	RiBasis(RiBSplineBasis,1,RiBSplineBasis,1);
		
	// Count the number of faces / vertices
	for (i=0,j=0;i<nfaces;j+=nvertices[i],i++);

	for (numVertices=-1,i=0;i<j;i++) {
		if (vertices[i] > numVertices)	numVertices	=	vertices[i];
	}
	numVertices++;

	// Create the core
	pl		=	parseParameterList(nfaces,numVertices,numVertices,j,n,tokens,(void **) params,RI_P,PL_VARYING_TO_VERTEX,attributes);
	if (pl == NULL)	return;

	switch(addMotion(pl->data0,pl->dataSize,"RiSubdivisionMesh",p0,p1)) {
	case 0:
		// Restore those attributes
		attributeEnd();
		// Clean up the unneeded pl
		delete pl;
		// Get out of here
		return;
		break;
	case 1:
		if (p0 != pl->data0)
			memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);
		break;
	case 2:
		// Restore the parameters
		memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);
		pl->append(p1);
		break;
	default:
		break;
	}

	// Create the object
	addObject(new CSubdivMesh(attributes,xform,pl,nfaces,nvertices,vertices,ntags,tags,nargs,intargs,floatargs));
	
	// Restore those attributes
	attributeEnd();
}

void	CRendererContext::RiBlobbyV(int nleaf,int ncode,int code[],int nflt,float flt[],int nstr,char *str[],int n,char *tokens[],void *params[]) {

	if (netNumServers > 0)	return;

	error(CODE_INCAPABLE,"Blobby primitive is not implemented yet (yet).\n");
}


void	CRendererContext::RiSolidBegin(char *type) {
	if (netNumServers > 0)	return;

	error(CODE_OPTIONAL,"CSG is not implemented.\n");
}

void	CRendererContext::RiSolidEnd(void) {
	if (netNumServers > 0)	return;
}

void	*CRendererContext::RiObjectBegin (void) {
	CXform	*xForm;

	if (netNumServers > 0)	return NULL;

	// Reset the xform so that all the objects defined relative to the beginning of the block
	xformBegin();
	
	xForm	=	getXform(TRUE);
	xForm->identity();
	if (xForm->next != NULL)	xForm->next->identity();

	// Create a new object
	objectsStack->push(objects);
	objects			=	new CArray<CObject *>;
	return	objects;
}


void	CRendererContext::RiObjectEnd(void) {
	if (netNumServers > 0)	return;

	CObject	*cObject;

	// Attach to the instanciated objects so that we don't loose them later
	for (cObject=objects->first();cObject!=NULL;cObject=objects->next()) {
		cObject->attach();
	}

	allocatedInstances->push(objects);
	objects			=	objectsStack->pop();
	xformEnd();
}


void	CRendererContext::RiObjectInstance(void *handle) {
	if (netNumServers > 0)	return;

	addInstance(handle);
}

void	CRendererContext::RiMotionBeginV(int N,float times[]) {
	int	i;
	
	numExpectedMotions	=	N;
	numMotions			=	0;
	keyTimes			=	new float[numExpectedMotions];
	for (i=0;i<numExpectedMotions;i++) {
		keyTimes[i]	=	times[i];
	}
}

void	CRendererContext::RiMotionEnd(void) {
	numExpectedMotions	=	1;
	delete [] keyTimes;
	keyTimes			=	NULL;
}

void	CRendererContext::RiMakeTextureV(char *pic,char *tex,char *swrap,char *twrap,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,char *tokens[],void *params[]) {
	COptions	*options;

	if (netClient != INVALID_SOCKET)	return;

	options	=	getOptions(FALSE);
	makeTexture(pic,tex,options->texturePath,swrap,twrap,filterfunc,swidth,twidth,n,tokens,(void **) params);
}

void	CRendererContext::RiMakeBumpV(char *pic,char *tex,char *swrap,char *twrap,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,char *tokens[],void *params[]) {
	COptions	*options;

	if (netClient != INVALID_SOCKET)	return;

	options	=	getOptions(FALSE);
	makeTexture(pic,tex,options->texturePath,swrap,twrap,filterfunc,swidth,twidth,n,tokens,(void **) params);
}

void	CRendererContext::RiMakeLatLongEnvironmentV(char *pic,char *tex,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,char *tokens[],void *params[]) {
	COptions	*options;

	if (netClient != INVALID_SOCKET)	return;

	options	=	getOptions(FALSE);
	makeCylindericalEnvironment(pic,tex,options->texturePath,RI_PERIODIC,RI_CLAMP,filterfunc,swidth,twidth,n,tokens,(void **) params);
}

void	CRendererContext::RiMakeCubeFaceEnvironmentV(char *px,char *nx,char *py,char *ny, char *pz,char *nz,char *tex,float fov,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,char *tokens[],void *params[]) {
	COptions	*options;

	if (netClient != INVALID_SOCKET)	return;

	options	=	getOptions(FALSE);
	makeCubicEnvironment(px,py,pz,nx,ny,nz,tex,RI_CLAMP,RI_CLAMP,options->texturePath,filterfunc,swidth,twidth,n,tokens,(void **) params,FALSE);
}


void	CRendererContext::RiMakeShadowV(char *pic,char *tex,int n,char *tokens[],void *params[]) {
	COptions	*options;

	if (netClient != INVALID_SOCKET)	return;

	options	=	getOptions(FALSE);
	makeSideEnvironment(pic,tex,options->texturePath,RI_CLAMP,RI_CLAMP,RiBoxFilter,1,1,n,tokens,(void **) params,TRUE);
}

void	CRendererContext::RiMakeTexture3DV(char *src,char *dest,int n,char *tokens[],void *params[]) {
	COptions	*options;

	if (netClient != INVALID_SOCKET)	return;

	options	=	getOptions(FALSE);
	makeTexture3D(src,dest,options->texturePath,n,tokens,(void **) params);
}

void	CRendererContext::RiArchiveRecord(char * type,char *format,va_list args) {
	// We're not archiving
}

void	CRendererContext::RiReadArchiveV(char *filename,void (*callback)(const char *),int n,char *tokens[],void *params[]) {
	char	tmp[OS_MAX_PATH_LENGTH];

	if ((filename[0] != '-') && (filename[0] != '|')) {
		COptions	*options	=	getOptions(FALSE);

		// Try locating the file
		if (locateFile(tmp,filename,options->archivePath)) {

			// Success, parse the file
			ribParse(tmp,callback);
		}
	} else {
		ribParse(filename,callback);
	}
}

void	CRendererContext::RiTrace(int n,float from[][3],float to[][3],float Ci[][3]) {
	memBegin();

	if (userRaytracing == FALSE) {
		// Prepare the rendering environment
		renderer->endWorld();

		// Make sure we mark ourself as raytracing so that sfEnd will not render
		userRaytracing					=	TRUE;
	}

	CTraceBundle	bundle;
	CTraceRay		*rays			=	(CTraceRay *) ralloc(n*sizeof(CTraceRay));
	CTraceRay		**allRays		=	(CTraceRay **) ralloc(n*sizeof(CTraceRay *));
	int				i;
	const float		bias			=	currentAttributes->shadowBias;

	for (i=0;i<n;i++) {
		CTraceRay	*cRay	=	allRays[i]	=	&rays[i];
		movvv(cRay->from,from[i]);
		subvv(cRay->dir,to[i],from[i]);
		normalizev(cRay->dir);
		cRay->time			=	urand();
		cRay->dest			=	Ci[i];
		cRay->flags			=	ATTRIBUTES_FLAGS_TRACE_VISIBLE;
		cRay->tmin			=	bias;
		cRay->t				=	C_INFINITY;
		cRay->multiplier	=	1;
	}

	bundle.rays			=	(CRay **) allRays;
	bundle.numRays		=	n;
	bundle.postShader	=	NULL;
	bundle.last			=	0;
	bundle.depth		=	0;
	renderer->trace(&bundle);

	memEnd();

}

void	CRendererContext::RiTrace(int n,float from[][3],float to[][3],float Ci[][3],float t[]) {
	memBegin();

	if (userRaytracing == FALSE) {
		// Prepare the rendering environment
		renderer->endWorld();

		// Make sure we mark ourself as raytracing so that sfEnd will not render
		userRaytracing					=	TRUE;
	}

	CTraceExBundle	bundle;
	CTraceExRay		*rays			=	(CTraceExRay *) ralloc(n*sizeof(CTraceExRay));
	CTraceExRay		**allRays		=	(CTraceExRay **) ralloc(n*sizeof(CTraceExRay *));
	int				i;
	const float		bias			=	currentAttributes->shadowBias;

	for (i=0;i<n;i++) {
		CTraceExRay	*cRay	=	allRays[i]	=	&rays[i];
		movvv(cRay->from,from[i]);
		subvv(cRay->dir,to[i],from[i]);
		normalizev(cRay->dir);
		cRay->time			=	urand();
		cRay->dest			=	Ci[i];
		cRay->destT			=	&t[i];
		cRay->flags			=	ATTRIBUTES_FLAGS_TRACE_VISIBLE;
		cRay->tmin			=	bias;
		cRay->t				=	C_INFINITY;
		cRay->multiplier	=	1;
	}

	bundle.rays			=	(CRay **) allRays;
	bundle.numRays		=	n;
	bundle.postShader	=	NULL;
	bundle.last			=	0;
	bundle.depth		=	0;
	renderer->trace(&bundle);


	memEnd();

}


void	CRendererContext::RiVisibility(int n,float from[][3],float to[][3],float Oi[][3]) {
	memBegin();

	if (userRaytracing == FALSE) {
		// Prepare the rendering environment
		renderer->endWorld();

		// Make sure we mark ourself as raytracing so that sfEnd will not render
		userRaytracing					=	TRUE;
	}

	CTransmissionBundle	bundle;
	CTransmissionRay	*rays			=	(CTransmissionRay *) ralloc(n*sizeof(CTransmissionRay));
	CTransmissionRay	**allRays		=	(CTransmissionRay **) ralloc(n*sizeof(CTransmissionRay *));
	int					i;
	const float			bias			=	currentAttributes->shadowBias;

	for (i=0;i<n;i++) {
		CTransmissionRay	*cRay	=	allRays[i]	=	&rays[i];
		movvv(cRay->from,from[i]);
		subvv(cRay->dir,to[i],from[i]);
		cRay->t				=	lengthv(cRay->dir);
		mulvf(cRay->dir,1/cRay->t);
		cRay->time			=	urand();
		cRay->dest			=	Oi[i];
		cRay->flags			=	ATTRIBUTES_FLAGS_TRANSMISSION_VISIBLE;
		cRay->tmin			=	bias;
		cRay->multiplier	=	1;
	}

	bundle.rays			=	(CRay **) allRays;
	bundle.numRays		=	n;
	bundle.postShader	=	NULL;
	bundle.last			=	0;
	bundle.depth		=	0;
	renderer->trace(&bundle);


	memEnd();
}

void	CRendererContext::RiError(int code,int severity,char *mes) {
	char		tmp[OS_MAX_PATH_LENGTH];
	CAttributes	*attributes	=	NULL;

	if (renderer != NULL) {
		if (renderer->currentShadingState != NULL) {
			if (renderer->currentShadingState->currentObject != NULL) {
				attributes	=	renderer->currentShadingState->currentObject->attributes;
			}
		}
	}

	if (attributes == NULL)	attributes	=	currentAttributes;

	if (severity != RIE_INFO) {
		if (ribFile != NULL) {
			sprintf(tmp,"%s (%d): ",ribFile,ribCommandLineno);
		} else {
			sprintf(tmp,"");
		}
	} else {
		sprintf(tmp,"");
	}

	if (attributes != NULL)	{
		if (attributes->name != NULL) {
			strcat(tmp,"(");
			strcat(tmp,attributes->name);
			strcat(tmp,") ");
		}
	}

	strcat(tmp,mes);

	// Log the file
	if (code == RIE_LOG) {
		if (currentOptions->filelog != NULL) {
			FILE	*out	=	fopen(currentOptions->filelog,"a");

			if (out != NULL) {
				fprintf(out,tmp);

				fclose(out);
			}
		}
	} else {
		if (errorHandler != NULL) {
			errorHandler(code,severity,tmp);
		}
	}
}
