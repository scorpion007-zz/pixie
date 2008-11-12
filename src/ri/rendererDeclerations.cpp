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
//  File				:	rendererDeclarations.cpp
//  Classes				:	CRenderer
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include <string.h>
#include <math.h>

#include "renderer.h"
#include "rendererContext.h"
#include "error.h"
#include "shading.h"
#include "displayChannel.h"


///////////////////////////////////////////////////////////////////////
// Class				:	CGlobalIdentifier
// Description			:	Holds a global identifier
// Comments				:
class  CGlobalIdentifier {
public:
	char				name[64];		// Name of the identifier
	int					id;
};




///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	initDeclarations
// Description			:	Init the declarations
// Return Value			:
// Comments				:
void			CRenderer::initDeclarations() {


	////////////////////////////////////////////////////////////////////////////////////////////
	//
	//
	//			A L L O C A T E    M E M O R Y
	//
	//
	////////////////////////////////////////////////////////////////////////////////////////////
	// Init the coordinate systems
	definedCoordinateSystems			=	new CTrie<CNamedCoordinateSystem *>;

	// Init the declared variables
	declaredVariables					=	new CTrie<CVariable *>;
	// Allocate the global variables array
	globalVariables						=	new CArray<CVariable *>;
	// This is the list of all variables
	variables							=	NULL;

	// Allocate the space for default display channels
	declaredChannels					=	new CTrie<CDisplayChannel*>;
	displayChannels						=	new	CArray<CDisplayChannel*>;

	// Zero is reserved as an invalid value
	numKnownGlobalIds					=	1;
	// Global Ids
	globalIdHash						=	new CTrie<CGlobalIdentifier *>;


	////////////////////////////////////////////////////////////////////////////////////////////
	//
	//
	//			R E G I S T E R    O P T I O N S / A T T R I B U T E S
	//
	//
	////////////////////////////////////////////////////////////////////////////////////////////
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
	declareVariable(RI_EYESPLITS,			"int");
	declareVariable(RI_TEXTUREMEMORY,		"int");
	declareVariable(RI_BRICKMEMORY,			"int");
	declareVariable(RI_NUMTHREADS,			"int");
	declareVariable(RI_THREADSTRIDE,		"int");
	declareVariable(RI_GEOCACHEMEMORY,		"int");
	declareVariable(RI_OTHRESHOLD,			"color");
	declareVariable(RI_ZTHRESHOLD,			"color");

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
	declareVariable(RI_SAMPLEMOTION,		"int");

	declareVariable(RI_HANDLE,				"string");
	declareVariable(RI_FILEMODE,			"string");
	declareVariable(RI_MAXERROR,			"float");
	declareVariable(RI_MAXPIXELDIST,		"float");

	declareVariable(RI_GLOBALMAP,			"string");
	declareVariable(RI_CAUSTICMAP,			"string");
	declareVariable(RI_SHADINGMODEL,		"string");
	declareVariable(RI_ESTIMATOR,			"int");
	declareVariable(RI_ILLUMINATEFRONT,		"int");

	declareVariable(RI_TRANSMISSION,		"int");
	declareVariable(RI_CAMERA,				"int");
	declareVariable(RI_SPECULAR,			"int");
	declareVariable(RI_DIFFUSE,				"int");
	declareVariable(RI_PHOTON,				"int");

	declareVariable(RI_DIFFUSEHITMODE,		"string");
	declareVariable(RI_SPECULARHITMODE,		"string");
	declareVariable(RI_TRANSMISSIONHITMODE,	"string");
	declareVariable(RI_CAMERAHITMODE,		"string");

	declareVariable(RI_NAME,				"string");

	declareVariable(RI_HIDDEN,				"int");
	declareVariable(RI_BACKFACING,			"int");

	////////////////////////////////////////////////////////////////////////////////////////////
	//
	//
	//			R E G I S T E R    D E F A U L T    V A R I A B L E S
	//
	//
	////////////////////////////////////////////////////////////////////////////////////////////
	CVariable		*tmp;
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
	tmp	=	declareVariable("Pz",	"vertex float",PARAMETER_P);				tmp->entry			=	VARIABLE_P;
	tmp	=	declareVariable("ncomps","global uniform float",PARAMETER_NCOMPS);	assert(tmp->entry	==	VARIABLE_NCOMPS);
	tmp	=	declareVariable("dtime","global uniform float",PARAMETER_DTIME);	assert(tmp->entry	==	VARIABLE_DTIME);
	tmp	=	declareVariable("dPdtime","global varying vector",PARAMETER_DPDTIME);assert(tmp->entry	==	VARIABLE_DPDTIME);

	tmp	=	declareVariable("width","global varying float",0);					assert(tmp->entry	==	VARIABLE_WIDTH);
	tmp	=	declareVariable("constantwidth","global constant float",0);			assert(tmp->entry	==	VARIABLE_CONSTANTWIDTH);
	tmp	=	declareVariable("Np","uniform normal",PARAMETER_NG);


	////////////////////////////////////////////////////////////////////////////////////////////
	//
	//
	//			R E G I S T E R    D E F A U L T   D I S P L A Y    C H A N N E L S
	//
	//
	////////////////////////////////////////////////////////////////////////////////////////////
	CDisplayChannel	*tmp2;

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
	

	////////////////////////////////////////////////////////////////////////////////////////////
	//
	//
	//			R E G I S T E R    D E F A U L T   C O O R D I N A T E    S Y S T E M S
	//
	//
	////////////////////////////////////////////////////////////////////////////////////////////


	defineCoordinateSystem(coordinateCameraSystem,identityMatrix,identityMatrix,COORDINATE_CAMERA);
	defineCoordinateSystem(coordinateWorldSystem,identityMatrix,identityMatrix,COORDINATE_WORLD);
	defineCoordinateSystem(coordinateObjectSystem,identityMatrix,identityMatrix,COORDINATE_OBJECT);
	defineCoordinateSystem(coordinateShaderSystem,identityMatrix,identityMatrix,COORDINATE_SHADER);
	defineCoordinateSystem(coordinateLightSystem,identityMatrix,identityMatrix,COORDINATE_LIGHT);
	defineCoordinateSystem(coordinateNDCSystem,identityMatrix,identityMatrix,COORDINATE_NDC);
	defineCoordinateSystem(coordinateRasterSystem,identityMatrix,identityMatrix,COORDINATE_RASTER);
	defineCoordinateSystem(coordinateScreenSystem,identityMatrix,identityMatrix,COORDINATE_SCREEN);
	defineCoordinateSystem(coordinateCurrentSystem,identityMatrix,identityMatrix,COORDINATE_CURRENT);

	// Define the default color systems
	defineCoordinateSystem(colorRgbSystem,identityMatrix,identityMatrix,COLOR_RGB);
	defineCoordinateSystem(colorHslSystem,identityMatrix,identityMatrix,COLOR_HSL);
	defineCoordinateSystem(colorHsvSystem,identityMatrix,identityMatrix,COLOR_HSV);
	defineCoordinateSystem(colorXyzSystem,identityMatrix,identityMatrix,COLOR_XYZ);
	defineCoordinateSystem(colorCieSystem,identityMatrix,identityMatrix,COLOR_CIE);
	defineCoordinateSystem(colorYiqSystem,identityMatrix,identityMatrix,COLOR_YIQ);
	defineCoordinateSystem(colorXyySystem,identityMatrix,identityMatrix,COLOR_XYY);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	shutdownDeclarations
// Description			:	Clear the declarations
// Return Value			:
// Comments				:
void			CRenderer::shutdownDeclarations() {
	// Ditch the global IDs
	assert(globalIdHash != NULL);
	globalIdHash->destroy();

	// Ditch the display channels
	assert(declaredChannels != NULL);
	assert(displayChannels != NULL);
	declaredChannels->destroy();
	delete displayChannels;

	// First the variables
	assert(declaredVariables != NULL);
	declaredVariables->destroy();
	delete globalVariables;

	// Ditch the coordinate stsrems
	assert(definedCoordinateSystems	!=	NULL);
	definedCoordinateSystems->destroy();
}



///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	defineCoordinateSystem
// Description			:	Define a coordinate system
// Return Value			:
// Comments				:
void			CRenderer::defineCoordinateSystem(const char *name,const float *from,const float *to,ECoordinateSystem type) {
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
int			CRenderer::findCoordinateSystem(const char *name,const float *&from,const float *&to,ECoordinateSystem &cSystem) {
	CNamedCoordinateSystem	*currentSystem;

	assert(CRenderer::definedCoordinateSystems	!=	NULL);

	if(CRenderer::definedCoordinateSystems->find(name,currentSystem)) {
		from		=	currentSystem->from;
		to			=	currentSystem->to;
		cSystem		=	currentSystem->systemType;

		switch(cSystem) {
			case COORDINATE_OBJECT:
				break;
			case COORDINATE_CAMERA:
				from	=	identityMatrix;
				to		=	identityMatrix;
				break;
			case COORDINATE_WORLD:
				from	=	CRenderer::fromWorld;
				to		=	CRenderer::toWorld;
				break;
			case COORDINATE_SHADER:
				{
					CXform	*currentXform	=	context->getXform(FALSE);
					from	=	currentXform->from;
					to		=	currentXform->to;
					break;
				}
			case COORDINATE_LIGHT:
			case COORDINATE_NDC:
			case COORDINATE_RASTER:
			case COORDINATE_SCREEN:
				break;
			case COORDINATE_CURRENT:
				{
					CXform	*currentXform	=	context->getXform(FALSE);
					from	=	currentXform->from;
					to		=	currentXform->to;
					break;
				}
		}

		return	TRUE;
	}

	return	FALSE;
}



///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	declareVariable
// Description			:	Define a new variable
// Return Value			:	The new variable if successful, NULL otherwise
// Comments				:
CVariable		*CRenderer::declareVariable(const char *name,const char *type,int marker) {
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
		nVariable->accessor					=	-1;
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
// Class				:	CRenderer
// Method				:	makeGlobalVariable
// Description			:	Forcefully make a variable global
// Return Value			:
// Comments				:
void	CRenderer::makeGlobalVariable(CVariable *var) {

	// Did we already start rendering ?
	var->entry		=	globalVariables->numItems;
	var->storage	=	STORAGE_GLOBAL;
	globalVariables->push(var);

	// Flush the states for the shading contexts
	if (contexts != NULL) {
		int	i;

		for (i=0;i<numThreads;i++) {
			contexts[i]->updateState();
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	retrieveVariable
// Description			:	Lookup a variable
// Return Value			:	The variable if found, NULL otherwise
// Comments				:
CVariable		*CRenderer::retrieveVariable(const char *name) {
	CVariable					*cVariable;

	assert(declaredVariables	!=	NULL);

	if (declaredVariables->find(name,cVariable)) {
		return cVariable;
	}

	return NULL;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	getGlobalID
// Description			:	Map a string to a number globally
// Return Value			:	The ID
// Comments				:
int		CRenderer::getGlobalID(const char *name) {
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
// Class				:	CRenderer
// Method				:	declareDisplayChannel
// Description			:	Define a new displayChannel
// Return Value			:	The new display channel, NULL otherwise
// Comments				:
CDisplayChannel		*CRenderer::declareDisplayChannel(const char *type) {
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
// Class				:	CRenderer
// Method				:	declareDisplayChannel
// Description			:	Define a new displayChannel
// Return Value			:	The new display channel, NULL otherwise
// Comments				:
CDisplayChannel		*CRenderer::declareDisplayChannel(CVariable *var) {
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
// Class				:	CRenderer
// Method				:	retrieveDisplayChannel
// Description			:	Define a new displayChannel
// Return Value			:	The found display channel, NULL otherwise
// Comments				:
CDisplayChannel		*CRenderer::retrieveDisplayChannel(const char *name) {
	CDisplayChannel *oChannel;
	if (declaredChannels->find(name,oChannel) == TRUE) {
		return oChannel;
	} else {
		return NULL;
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	resetDisplayChannelUsage
// Description			:	Mark all AOV channels as unused
// Return Value			:	
// Comments				:
void CRenderer::resetDisplayChannelUsage() {
	int i,n = displayChannels->numItems;
	CDisplayChannel **dsp = displayChannels->array;
	
	for (i=0;i<n;i++,dsp++) {
		if ((*dsp)->variable != NULL) {
			(*dsp)->sampleStart = -1;
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	registerFrameTemporary
// Description			:	Register a file as a temporary
//						:	 Optionally register for deletion at frame-end
//						:	 certain files (namely those which are netrender temporaries)
//						:	 would otherwise be found in preference to the merged 
//						:	 client-side file, and must be removed before next frame.
// Return Value			:	
// Comments				:	Also removes any netFileMappings for the file
void CRenderer::registerFrameTemporary(const char *name, int deleteFile) {
	char *tmp = new char[strlen(name)+2];
	tmp[0] = (deleteFile == TRUE) ? 1 : 0;
	strcpy(tmp+1,name);
	if (frameTemporaryFiles == NULL) {
		frameTemporaryFiles = new CArray<const char*>;
	}
	
	frameTemporaryFiles->push(tmp);
}

