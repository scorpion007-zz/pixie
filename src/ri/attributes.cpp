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
//  File				:	attributes.cpp
//  Classes				:	CAttributes
//  Description			:	Implementation
//
////////////////////////////////////////////////////////////////////////
#include <math.h>
#include <string.h>

#include "attributes.h"
#include "ri.h"
#include "renderer.h"
#include "stats.h"
#include "photonMap.h"
#include "irradiance.h"
#include "error.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CAttributes
// Method				:	CAttributes
// Description			:	The constructor, the default values for
//							attributes are given here
// Return Value			:	-
// Comments				:
// Date last edited		:	3/11/2003
CAttributes::CAttributes() {
	next					=	NULL;
	refCount				=	0;

	stats.numAttributes++;
	stats.attributesMemory	+=	sizeof(CAttributes);

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

	nSides						=	2;

	flags						=	0;
	flags						|=	ATTRIBUTES_FLAGS_PRIMARY_VISIBLE;
	flags						|=	ATTRIBUTES_FLAGS_SINGULARITYFIX;

	minSubdivision				=	2;
	maxSubdivision				=	5;

	flatness					=	0.5f;
	pointDeviation				=	C_INFINITY;
	normalDeviation				=	cosf(radians(45));

	maxDisplacement				=	0;
	maxDisplacementSpace		=	NULL;

	lightSources				=	NULL;

	shadingRate					=	1.0f;
	motionFactor				=	0.0f;

	name						=	NULL;

	numUProbes					=	4;
	numVProbes					=	4;
	minSplits					=	2;
	rasterExpand				=	0.5f;
	shadowBias					=	0.01f;

	transmission				=	'o';

	emit						=	-1;
	relativeEmit				=	1;

	shadingModel				=	SM_MATTE;
	
	globalMapName				=	NULL;
	causticMapName				=	NULL;
	globalMap					=	NULL;
	causticMap					=	NULL;
	irradianceHandle			=	NULL;
	irradianceHandleMode		=	NULL;
	irradianceMaxError			=	1.0f;
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
}

///////////////////////////////////////////////////////////////////////
// Class				:	CAttributes
// Method				:	CAttributes
// Description			:	This functions creates an exact replica of 
//							another attribute set
// Return Value			:	-
// Comments				:
// Date last edited		:	3/13/2003
CAttributes::CAttributes(const CAttributes *a) {
	CActiveLight	*cLight,*nLight;

	stats.numAttributes++;
	stats.attributesMemory	+=	sizeof(CAttributes);

	this[0]						=	a[0];
	
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
		nLight			=	new CActiveLight;

		nLight->light		=	cLight->light;
		nLight->next		=	lightSources;
		lightSources		=	nLight;
	}

	name						=	(a->name != NULL ? strdup(a->name) : NULL);

	if (a->next != NULL) next	=	new CAttributes(a->next);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CAttributes
// Method				:	~CAttributes
// Description			:	Deallocate everything
// Return Value			:	-
// Comments				:
// Date last edited		:	3/3/2001
CAttributes::~CAttributes(){
	CActiveLight	*cLight;

	stats.numAttributes--;
	stats.attributesMemory	-=	sizeof(CAttributes);

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
// Date last edited		:	3/3/2001
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
}

///////////////////////////////////////////////////////////////////////
// Class				:	CAttributes
// Method				:	removeLight
// Description			:	This method must be used to remove a light
//							source from the active light source list
// Return Value			:	-
// Comments				:
// Date last edited		:	3/3/2001
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
}

///////////////////////////////////////////////////////////////////////
// Class				:	CAttributes
// Method				:	lightParameterCheck
// Description			:	Check the light parameters
// Return Value			:	-
// Comments				:
// Date last edited		:	3/3/2001
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
// Date last edited		:	5/28/2006
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
