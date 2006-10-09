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
//  File				:	frameDeclerations.cpp
//  Classes				:	CFrame
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include <string.h>
#include <math.h>

#include "frame.h"
#include "renderer.h"
#include "error.h"







///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Method				:	defineCoordinateSystem
// Description			:	Define a coordinate system
// Return Value			:
// Comments				:
// Date last edited		:	8/25/2002
void			CFrame::defineCoordinateSystem(const char *name,matrix &from,matrix &to,ECoordinateSystem type) {
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
// Class				:	CFrame
// Method				:	declareVariable
// Description			:	Define a new variable
// Return Value			:	The new variable if successful, NULL otherwise
// Comments				:
// Date last edited		:	8/25/2002
CVariable		*CFrame::declareVariable(const char *name,const char *type,int marker) {
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
// Class				:	CFrame
// Method				:	makeGlobalVariable
// Description			:	Forcefully make a variable global
// Return Value			:
// Comments				:
// Date last edited		:	8/25/2002
void	CFrame::makeGlobalVariable(CVariable *var) {
	// Did we already start rendering ?
	var->entry		=	numGlobalVariables++;
	var->storage	=	STORAGE_GLOBAL;
	globalVariables->push(var);

	// FIXME: Flush the states for the shading contexts
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Method				:	retrieveVariable
// Description			:	Lookup a variable
// Return Value			:	The variable if found, NULL otherwise
// Comments				:
// Date last edited		:	8/25/2002
CVariable		*CFrame::retrieveVariable(const char *name) {
	CVariable					*cVariable;

	assert(declaredVariables	!=	NULL);

	if (declaredVariables->find(name,cVariable)) {
		return cVariable;
	}

	return NULL;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Method				:	getGlobalID
// Description			:	Map a string to a number globally
// Return Value			:	The ID
// Comments				:
// Date last edited		:	8/25/2002
int		CFrame::getGlobalID(const char *name) {
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
// Class				:	CFrame
// Method				:	declareDisplayChannel
// Description			:	Define a new displayChannel
// Return Value			:	The new display channel, NULL otherwise
// Comments				:
// Date last edited		:	08/02/2006
CDisplayChannel		*CFrame::declareDisplayChannel(const char *type) {
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
// Class				:	CFrame
// Method				:	declareDisplayChannel
// Description			:	Define a new displayChannel
// Return Value			:	The new display channel, NULL otherwise
// Comments				:
// Date last edited		:	08/02/2006
CDisplayChannel		*CFrame::declareDisplayChannel(CVariable *var) {
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
// Class				:	CFrame
// Method				:	retrieveDisplayChannel
// Description			:	Define a new displayChannel
// Return Value			:	The found display channel, NULL otherwise
// Comments				:
// Date last edited		:	08/02/2006
CDisplayChannel		*CFrame::retrieveDisplayChannel(const char *name) {
	CDisplayChannel *oChannel;
	if (declaredChannels->find(name,oChannel) == TRUE) {
		return oChannel;
	} else {
		return NULL;
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Method				:	resetDisplayChannelUsage
// Description			:	Mark all AOV channels as unused
// Return Value			:	
// Comments				:
// Date last edited		:	08/02/2006
void CFrame::resetDisplayChannelUsage() {
	int i,n = displayChannels->numItems;
	CDisplayChannel **dsp = displayChannels->array;
	
	for (i=0;i<n;i++,dsp++) {
		if ((*dsp)->variable != NULL) {
			(*dsp)->sampleStart = -1;
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Method				:	registerFrameTemporary
// Description			:	Register a file as a temporary
//						:	 Optionally register for deletion at frame-end
//						:	 certain files (namely those which are netrender temporaries)
//						:	 would otherwise be found in preference to the merged 
//						:	 client-side file, and must be removed before next frame.
// Return Value			:	
// Comments				:	Also removes any netFileMappings for the file
// Date last edited		:	08/02/2006
void CFrame::registerFrameTemporary(const char *name, int deleteFile) {
	char *tmp = new char[strlen(name)+2];
	tmp[0] = (deleteFile == TRUE) ? 1 : 0;
	strcpy(tmp+1,name);
	if (frameTemporaryFiles == NULL) {
		frameTemporaryFiles = new CArray<const char*>;
	}
	
	frameTemporaryFiles->push(tmp);
}





