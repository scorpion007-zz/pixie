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
//  File				:	attributes.cpp
//  Classes				:	CAttributes
//  Description			:	Implementation
//
////////////////////////////////////////////////////////////////////////
#include <math.h>
#include <string.h>

#include "attributes.h"
#include "ri.h"
#include "stats.h"
#include "photonMap.h"
#include "irradiance.h"
#include "error.h"
#include "atomic.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CAttributes
// Method				:	CAttributes
// Description			:	The constructor, the default values for
//							attributes are given here
// Return Value			:	-
// Comments				:
CAttributes::CAttributes() {
	next					=	NULL;

	atomicIncrement(&stats.numAttributes);

	surface					=	NULL;
	displacement			=	NULL;
	atmosphere				=	NULL;
	interior				=	NULL;
	exterior				=	NULL;
	usedParameters			=	0;

	initv(surfaceColor,1,1,1);
	initv(surfaceOpacity,1,1,1);

	s[0]					=	0.0;
	s[1]					=	1.0;
	s[2]					=	0.0;
	s[3]					=	1.0;
	t[0]					=	0.0;
	t[1]					=	0.0;
	t[2]					=	1.0;
	t[3]					=	1.0;	

	initv(bmin,C_INFINITY,C_INFINITY,C_INFINITY);
	initv(bmax,-C_INFINITY,-C_INFINITY,-C_INFINITY);
	bexpand					=	0.00001f;	// Epsilon

	{
		int	i,j;

		for (i=0;i<4;i++)
			for (j=0;j<4;j++) {
				uBasis[element(i,j)]	=	RiBezierBasis[i][j];
				vBasis[element(i,j)]	=	RiBezierBasis[i][j];
			}
	}

	uStep						=	3;
	vStep						=	3;

	flags						=	0;
	flags						|=	ATTRIBUTES_FLAGS_PRIMARY_VISIBLE;
	flags						|=	ATTRIBUTES_FLAGS_DOUBLE_SIDED;

	maxDisplacement				=	0;
	maxDisplacementSpace		=	NULL;

	lightSources				=	NULL;

	shadingRate					=	1.0f;
	motionFactor				=	0.0f;

	name						=	NULL;

	numUProbes					=	4;
	numVProbes					=	4;
	minSplits					=	0;		// This should no longer be needed with convergent dicing
	rasterExpand				=	0.5f;	// This could be significantly lowered for many primitives
	bias						=	0.01f;

	transmissionHitMode			=	'p';
	diffuseHitMode				=	'p';
	cameraHitMode				=	's';
	specularHitMode				=	's';


	emit						=	-1;
	relativeEmit				=	1;

	shadingModel				=	SM_MATTE;
	
	globalMapName				=	NULL;
	causticMapName				=	NULL;
	globalMap					=	NULL;
	causticMap					=	NULL;
	irradianceHandle			=	strdup("");
	irradianceHandleMode		=	strdup("w");
	irradianceMaxError			=	0.6f;
	irradianceMaxPixelDistance	=	20.0f;
	photonEstimator				=	100;
	photonIor[0]				=	1.5;
	photonIor[1]				=	1.5;
	maxDiffuseDepth				=	1;
	maxSpecularDepth			=	2;

	shootStep					=	1000;		// Shoot 1000 rays at a time
	
	lodRange[0]					=	-C_INFINITY;
	lodRange[1]					=	-C_INFINITY;
	lodRange[2]					=	C_INFINITY;
	lodRange[3]					=	C_INFINITY;
	lodSize						=	0;
	lodImportance				=	1;
	
	checkParameters();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CAttributes
// Method				:	CAttributes
// Description			:	This functions creates an exact replica of 
//							another attribute set
// Return Value			:	-
// Comments				:
CAttributes::CAttributes(const CAttributes *a) {
	CActiveLight	*cLight,*nLight;

	atomicIncrement(&stats.numAttributes);

	this[0]						=	a[0];

	// Note: The assignment here also invokes the assignment operator of userAttributes
	//      so there's no need for a separate copy for that
	
	refCount					=	0;

	if (surface != NULL)			surface->attach();
	if (displacement != NULL)		displacement->attach();
	if (atmosphere != NULL)			atmosphere->attach();
	if (interior != NULL)			interior->attach();
	if (exterior != NULL)			exterior->attach();

	if (globalMapName != NULL)		globalMapName	=	strdup(a->globalMapName);
	if (causticMapName != NULL)		causticMapName	=	strdup(a->causticMapName);
	if (globalMap != NULL)			globalMap->attach();
	if (causticMap != NULL)			causticMap->attach();

	irradianceHandle			=	(a->irradianceHandle == NULL ?		NULL : strdup(a->irradianceHandle));
	irradianceHandleMode		=	(a->irradianceHandleMode == NULL ?	NULL : strdup(a->irradianceHandleMode));

	if (a->maxDisplacementSpace != NULL)	maxDisplacementSpace	=	strdup(a->maxDisplacementSpace);

	lightSources				=	NULL;

	for (cLight=a->lightSources;cLight!=NULL;cLight=cLight->next) {
		nLight				=	new CActiveLight;
		nLight->light		=	cLight->light;
		nLight->next		=	lightSources;
		lightSources		=	nLight;
	}

	name					=	(a->name != NULL ? strdup(a->name) : NULL);

	if (a->next != NULL) next	=	new CAttributes(a->next);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CAttributes
// Method				:	~CAttributes
// Description			:	Deallocate everything
// Return Value			:	-
// Comments				:
CAttributes::~CAttributes(){
	CActiveLight	*cLight;

	atomicDecrement(&stats.numAttributes);

	if (surface != NULL)				surface->detach();
	if (displacement != NULL)			displacement->detach();
	if (atmosphere != NULL)				atmosphere->detach();
	if (interior != NULL)				interior->detach();
	if (exterior != NULL)				exterior->detach();

	if (globalMapName != NULL)			free(globalMapName);
	if (causticMapName != NULL)			free(causticMapName);
	if (globalMap != NULL)				globalMap->detach();
	if (causticMap != NULL)				causticMap->detach();
	if (irradianceHandle != NULL)		free(irradianceHandle);
	if (irradianceHandleMode != NULL)	free(irradianceHandleMode);

	if (name != NULL)					free(name);

	if (maxDisplacementSpace != NULL)	free(maxDisplacementSpace);

	while((cLight=lightSources) != NULL) {
		lightSources	=	cLight->next;
		delete cLight;
	}

	if (next != NULL)			delete next;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CAttributes
// Method				:	addLight
// Description			:	Obvious !
// Return Value			:	-
// Comments				:
void	CAttributes::addLight(CShaderInstance *cLight) {
	CActiveLight	*nLight,*pLight;

	// Make sure we're not duplicating the light source
	for (nLight=lightSources,pLight=NULL;nLight!=NULL;nLight=nLight->next) {
		if (nLight->light == cLight)	return;
		pLight = nLight;
	}
	
	// Make sure lighting order matches RIB order
	if (pLight == NULL) {
		nLight			=	lightSources	=	new CActiveLight;
	} else {
		nLight			=	pLight->next	=	new CActiveLight;
	}
	
	nLight->light		=	(CProgrammableShaderInstance*) cLight;
	nLight->next		=	NULL;
	checkParameters();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CAttributes
// Method				:	removeLight
// Description			:	This method must be used to remove a light
//							source from the active light source list
// Return Value			:	-
// Comments				:
void	CAttributes::removeLight(CShaderInstance *light) {
	CActiveLight	*cLight,*pLight;

	for (pLight=NULL,cLight=lightSources;cLight!=NULL;pLight=cLight,cLight=cLight->next) {
		if (cLight->light == light) {
			if (pLight == NULL)	lightSources	=	cLight->next;
			else				pLight->next	=	cLight->next;

			delete cLight;

			break;
		}
	}
	checkParameters();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CAttributes
// Method				:	lightParameterCheck
// Description			:	Check the light parameters
// Return Value			:	-
// Comments				:
void	CAttributes::checkParameters() {
	CActiveLight	*cLight;

	usedParameters	=	0;

	if (displacement != NULL)	usedParameters	|=	displacement->requiredParameters();
	if (surface != NULL)		usedParameters	|=	surface->requiredParameters();
	if (atmosphere != NULL)		usedParameters	|=	atmosphere->requiredParameters();
	if (interior != NULL)		usedParameters	|=	interior->requiredParameters();
	if (exterior != NULL)		usedParameters	|=	exterior->requiredParameters();

	if (surface == NULL)		usedParameters	|=	PARAMETER_N;

	for (cLight=lightSources;cLight!=NULL;cLight=cLight->next) {
		usedParameters	|=	cLight->light->requiredParameters();
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CAttributes
// Method				:	findParameter
// Description			:	Find a particular parameter
// Return Value			:	-
// Comments				:
CVariable	*CAttributes::findParameter(const char *name) {
	CVariable	*cParameter;

	if (displacement) {
		for (cParameter=displacement->parameters;cParameter!=NULL;cParameter=cParameter->next) {
			if (strcmp(cParameter->name,name) == 0)	return	cParameter;
		}
	}

	if (surface) {
		for (cParameter=surface->parameters;cParameter!=NULL;cParameter=cParameter->next) {
			if (strcmp(cParameter->name,name) == 0)	return	cParameter;
		}
	}

	if (atmosphere) {
		for (cParameter=atmosphere->parameters;cParameter!=NULL;cParameter=cParameter->next) {
			if (strcmp(cParameter->name,name) == 0)	return	cParameter;
		}
	}

	return NULL;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CAttributes
// Method				:	restore
// Description			:	Restore some portion of the shading state from another attribute block
// Return Value			:	-
// Comments				:
void		CAttributes::restore(const CAttributes *other,int shading,int geometrymodification,int geometrydefinition,int hiding) {
	if (shading) {
		if (surface != NULL)		surface->detach();
		if (displacement != NULL)	displacement->detach();
		if (atmosphere != NULL)		atmosphere->detach();
		if (interior != NULL)		interior->detach();
		if (exterior != NULL)		exterior->detach();
		
		surface			=	other->surface;			if (surface != NULL)		surface->attach();
		displacement	=	other->displacement;	if (displacement != NULL)	displacement->attach();
		atmosphere		=	other->atmosphere;		if (atmosphere != NULL)		atmosphere->attach();
		interior		=	other->interior;		if (interior != NULL)		interior->attach();
		exterior		=	other->exterior;		if (exterior != NULL)		exterior->attach();

		movvv(surfaceColor,other->surfaceColor);
		movvv(surfaceColor,other->surfaceColor);

		// Delete the light sources
		CActiveLight	*cLight;
		while((cLight=lightSources) != NULL) {
			lightSources	=	lightSources->next;
			delete cLight;
		}

		// Copy the light sources
		for (cLight=other->lightSources;cLight!=NULL;cLight=cLight->next) {
			CActiveLight	*nLight	=	new CActiveLight;
			nLight->light			=	cLight->light;
			nLight->next			=	lightSources;
			lightSources			=	nLight;
		}
		
		checkParameters();

		shadingRate	=	other->shadingRate;
		memcpy(s,other->s,4*sizeof(float));
		memcpy(t,other->t,4*sizeof(float));

		// Do the irradiance stuff
		if (irradianceHandle		!= NULL)	free(irradianceHandle);
		if (irradianceHandleMode	!= NULL)	free(irradianceHandleMode);
		irradianceHandle		=	(other->irradianceHandle == NULL ? NULL : strdup(other->irradianceHandle));
		irradianceHandleMode	=	(other->irradianceHandleMode == NULL ? NULL : strdup(other->irradianceHandleMode));

		// Do the photon map stuff
		if (globalMapName	!= NULL)	free(globalMapName);
		if (causticMapName	!= NULL)	free(causticMapName);
		globalMapName			=	(other->globalMapName == NULL ? NULL : strdup(other->globalMapName));
		causticMapName			=	(other->causticMapName == NULL ? NULL : strdup(other->causticMapName));

		// Copy the user attributes
		userAttributes			=	other->userAttributes;

		// Copy the flags
		flags					=	other->flags;

	}

	if (geometrymodification) {
		memcpy(lodRange,other->lodRange,4*sizeof(float));
		lodSize			=	other->lodSize;
		lodImportance	=	other->lodImportance;

		flags			|=	other->flags & ATTRIBUTES_FLAGS_DOUBLE_SIDED;
	}

	if (geometrydefinition) {
		movmm(uBasis,other->uBasis);
		movmm(vBasis,other->vBasis);
		uStep	=	other->uStep;
		vStep	=	other->vStep;

		if (name != NULL)	free(name);
		name	=	(other->name == NULL ? NULL : strdup(other->name));
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CAttributes
// Method				:	find
// Description			:	Find a particular attribute
// Return Value			:	-
// Comments				:
int		CAttributes::find(const char *name,const char *category,EVariableType &type,const void *&value,int &intValue,float &floatValue) const {

	// Make the common case fast
	if ((category == NULL) || (strcmp(category,RI_USER) == 0)) {
		CVariable	*cVariable;

		// Lookup the attribute
		if (userAttributes.lookup(name,cVariable)) {
			type	=	cVariable->type;
			value	=	cVariable->defaultValue;

			if (value != NULL)	return TRUE;
		}
	}
	
	if ((category == NULL) || (strcmp(category,RI_DICE) == 0)) {
		if (strcmp(name,RI_NUMPROBES) == 0)				{	type	=	TYPE_INTEGER;	value	=	&numUProbes;			return TRUE;}
		else if (strcmp(name,RI_MINSPLITS) == 0)		{	type	=	TYPE_INTEGER;	value	=	&minSplits;				return TRUE;}
		else if (strcmp(name,RI_BOUNDEXPAND) == 0)		{	type	=	TYPE_FLOAT;		value	=	&rasterExpand;			return TRUE;}
		else if (strcmp(name,RI_BINARY) == 0)			{	type	=	TYPE_INTEGER;	value	=	NULL;	intValue = (flags & ATTRIBUTES_FLAGS_BINARY_DICE) != 0;				return TRUE;}
		else if (strcmp(name,RI_RASTERORIENT) == 0)		{	type	=	TYPE_INTEGER;	value	=	NULL;	intValue = (flags & ATTRIBUTES_FLAGS_NONRASTERORIENT_DICE) != 0;	return TRUE;}
	}

	if ((category == NULL) || (strcmp(category,RI_DISPLACEMENTBOUND) == 0)) {
		if (strcmp(name,RI_SPHERE) == 0)				{	type	=	TYPE_FLOAT;		value	=	&maxDisplacement;		return TRUE;}
		else if (strcmp(name,RI_COORDINATESYSYTEM) == 0){	type	=	TYPE_STRING;	value	=	maxDisplacementSpace;	return TRUE;}
	}

	if ((category == NULL) || (strcmp(category,RI_TRACE) == 0)) {
		if (strcmp(name,RI_BIAS) == 0)					{	type	=	TYPE_FLOAT;		value	=	&bias;					return TRUE;}
		else if (strcmp(name,RI_MAXDIFFUSEDEPTH) == 0)	{	type	=	TYPE_INTEGER;	value	=	&maxDiffuseDepth;		return TRUE;}
		else if (strcmp(name,RI_MAXSPECULARDEPTH) == 0)	{	type	=	TYPE_INTEGER;	value	=	&maxSpecularDepth;		return TRUE;}
		else if (strcmp(name,RI_DISPLACEMENTS) == 0)	{	type	=	TYPE_INTEGER;	value	=	NULL;	intValue = (flags & ATTRIBUTES_FLAGS_DISPLACEMENTS) != 0;			return TRUE;}
	}

	if ((category == NULL) || (strcmp(category,RI_IRRADIANCE) == 0)) {
		if (strcmp(name,RI_HANDLE) == 0)				{	type	=	TYPE_STRING;	value	=	irradianceHandle;		return TRUE;}
		else if (strcmp(name,RI_FILEMODE) == 0)			{	type	=	TYPE_STRING;	value	=	irradianceHandleMode;	return TRUE;}
		else if (strcmp(name,RI_MAXERROR) == 0)			{	type	=	TYPE_FLOAT;		value	=	&irradianceMaxError;	return TRUE;}
	}

	if ((category == NULL) || (strcmp(category,RI_PHOTON) == 0)) {
		if (strcmp(name,RI_GLOBALMAP) == 0)				{	type	=	TYPE_STRING;	value	=	globalMapName;			return TRUE;}
		else if (strcmp(name,RI_CAUSTICMAP) == 0)		{	type	=	TYPE_STRING;	value	=	causticMapName;			return TRUE;}
		else if (strcmp(name,RI_IOR) == 0)				{	type	=	TYPE_FLOAT;		value	=	photonIor;				return TRUE;}
		else if (strcmp(name,RI_IORRANGE) == 0)			{	type	=	TYPE_FLOAT;		value	=	photonIor;				return TRUE;}
		else if (strcmp(name,RI_ESTIMATOR) == 0)		{	type	=	TYPE_INTEGER;	value	=	&photonEstimator;		return TRUE;}
		else if (strcmp(name,RI_SHADINGMODEL) == 0)		{	type	=	TYPE_STRING;	value	=	findShadingModel(shadingModel);		return TRUE;}
	}

	if ((category == NULL) || (strcmp(category,RI_VISIBILITY) == 0)) {
		if (strcmp(name,RI_CAMERA) == 0)				{	type	=	TYPE_INTEGER;	value	=	NULL;	intValue = (flags & ATTRIBUTES_FLAGS_PRIMARY_VISIBLE) != 0;			return TRUE;}
		else if (strcmp(name,RI_DIFFUSE) == 0)			{	type	=	TYPE_INTEGER;	value	=	NULL;	intValue = (flags & ATTRIBUTES_FLAGS_DIFFUSE_VISIBLE) != 0;			return TRUE;}
		else if (strcmp(name,RI_SPECULAR) == 0)			{	type	=	TYPE_INTEGER;	value	=	NULL;	intValue = (flags & ATTRIBUTES_FLAGS_SPECULAR_VISIBLE) != 0;		return TRUE;}
		else if (strcmp(name,RI_PHOTON) == 0)			{	type	=	TYPE_INTEGER;	value	=	NULL;	intValue = (flags & ATTRIBUTES_FLAGS_PHOTON_VISIBLE) != 0;			return TRUE;}
		else if (strcmp(name,RI_TRANSMISSION) == 0)		{	type	=	TYPE_INTEGER;	value	=	NULL;	intValue = (flags & ATTRIBUTES_FLAGS_TRANSMISSION_VISIBLE) != 0;	return TRUE;}
	}
	
	if ((category == NULL) || (strcmp(category,RI_IDENTIFIER) == 0)) {
		if (strcmp(name,RI_NAME) == 0)					{	type	=	TYPE_STRING;	value	=	this->name;				return TRUE;}
	}

	if ((category == NULL) || (strcmp(category,RI_CULL) == 0)) {
		if (strcmp(name,RI_HIDDEN) == 0)				{	type	=	TYPE_INTEGER;	value	=	NULL;	intValue = (flags & ATTRIBUTES_FLAGS_SHADE_HIDDEN) != 0;			return TRUE;}
		else if (strcmp(name,RI_BACKFACING) == 0)		{	type	=	TYPE_INTEGER;	value	=	NULL;	intValue = (flags & ATTRIBUTES_FLAGS_SHADE_BACKFACE) != 0;			return TRUE;}
	}

	// Unable to find it
	return FALSE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CAttributes
// Method				:	findShadingModel
// Description			:	Find the shading model from text
// Return Value			:	-
// Comments				:
EShadingModel		CAttributes::findShadingModel(const char *val) {
	if (strcmp(val,"matte") == 0) {
		return SM_MATTE;
	} else if (strcmp(val,"translucent") == 0) {
		return SM_TRANSLUCENT;
	} else if (strcmp(val,"chrome") == 0) {
		return SM_CHROME;
	} else if (strcmp(val,"glass") == 0) {
		return SM_GLASS;
	} else if (strcmp(val,"water") == 0) {
		return SM_WATER;
	} else if (strcmp(val,"dielectric") == 0) {
		return SM_DIELECTRIC;
	} else if (strcmp(val,"transparent") == 0) {
		return SM_TRANSPARENT;
	} else {
		error(CODE_BADTOKEN,"Unknown shading model: \"%s\"\n",val);
		return SM_MATTE;
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CAttributes
// Method				:	findShadingModel
// Description			:	The other way around
// Return Value			:	-
// Comments				:
const char			*CAttributes::findShadingModel(EShadingModel model) {
	switch(model) {
	case SM_MATTE:
		return "matte";
		break;
	case SM_TRANSLUCENT:
		return "translucent";
		break;
	case SM_CHROME:
		return "chrome";
		break;
	case SM_GLASS:
		return "glass";
		break;
	case SM_WATER:
		return "water";
		break;
	case SM_DIELECTRIC:
		return "dielectric";
		break;
	case SM_TRANSPARENT:
		return "transparent";
		break;
	}

	return "matte";
}

///////////////////////////////////////////////////////////////////////
// Class				:	findHitMode
// Method				:	setHitmode
// Description			:	Translate hitmode from string
// Return Value			:	-
// Comments				:
char		CAttributes::findHitMode(const char *mode) {

	// Figure out the hit mode
	if (strcmp(mode,"primitive") == 0) {
		return 'p';
	} else if (strcmp(mode,"shader") == 0) {
		return 's';
	} else {
		error(CODE_BADTOKEN,"Unrecognized hit mode \"%s\"\n",mode);
		return 'p';
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CAttributes
// Method				:	findHitMode
// Description			:	The other way around
// Return Value			:	-
// Comments				:
const char		*CAttributes::findHitMode(char mode) {
	if (mode == 'p')		return "primitive";
	else if (mode == 's')	return "shader";
	else error(CODE_BUG,"Invalid hit mode encountered: \'%c\'\n",mode);

	return "primitive";
}
