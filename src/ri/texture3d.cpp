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
//  File				:	texture3d.cpp
//  Classes				:	CTexture3d
//  Description			:	Implementation - George
//
////////////////////////////////////////////////////////////////////////
#include "texture3d.h"
#include "error.h"
#include "renderer.h"
#include "displayChannel.h"



///////////////////////////////////////////////////////////////////////
// Class				:	CTexture3d
// Method				:	CTexture3d
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CTexture3d::CTexture3d(const char *n,const float *f,const float *t,const float *tndc,int nc,CChannel *ch) : CFileResource(n) { 
	dataSize	=	0;
	channels	=	NULL;
	numChannels	=	0;
	movmm(from,f);
	movmm(to,t);

	// will be read from file if not provided
	if (tndc != NULL)	movmm(toNDC,tndc);
	
	dPscale		=	pow(fabs(determinantm(to)),1.0f / 3.0f);

	if (nc > 0) {
		int	i;

		numChannels		=	nc;
		channels		=	new CChannel[nc];
		memcpy(channels,ch,sizeof(CChannel)*numChannels);
		for (i=0,dataSize=0;i<numChannels;i++)
			dataSize	+= channels[i].numSamples;
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CTexture3d
// Method				:	~CTexture3d
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CTexture3d::~CTexture3d() { 
	if (channels != NULL) delete [] channels;
}
	
///////////////////////////////////////////////////////////////////////
// Class				:	CTexture3d
// Method				:	defineChannels
// Description			:	Define the channels
// Return Value			:	-
// Comments				:
void CTexture3d::defineChannels(const char *channelDefinitions) {
	char				*nextComma,*sampleName,*tmp;
	CDisplayChannel		*oChannel;
	
	// This is used by remote channels
	// The channel definitions will be loaded when
	// creating the remote channel
	if (channelDefinitions == NULL) return;
	
	// determinte the channels
	numChannels		=	1;
	dataSize		=	0;
	
	const char	*sd = channelDefinitions;
	while ((sd = strchr(sd,',')) != NULL) {
		sd++;
		numChannels++;
	}
	channels		=	new CChannel[numChannels];
	
	// parse the channels / sample types
	char *sampleDefinition = strdup(channelDefinitions); // duplicate to tokenize
	nextComma = sampleName = sampleDefinition;
	numChannels = 0;
	do {
		// parse to next comma, remove spaces
		nextComma = strchr(sampleName,',');
		if (nextComma != NULL) {
			for (tmp=nextComma-1;isspace(*tmp)&&(tmp>sampleName);tmp--) *tmp = '\0';
			*nextComma++ = '\0';
			while (isspace(*nextComma)) nextComma++;
		}
		while (isspace(*sampleName)) sampleName++;
		
		// is the sample name a channel we know about?
		oChannel = CRenderer::retrieveDisplayChannel(sampleName);
		if (oChannel != NULL) {
			// it's a predefined / already seen channel
			strcpy(channels[numChannels].name,oChannel->name);
			channels[numChannels].sampleStart		= dataSize;
			channels[numChannels].numSamples		= oChannel->numSamples;
			if (oChannel->variable != NULL)
				channels[numChannels].type			= oChannel->variable->type;
			else
				channels[numChannels].type			= TYPE_FLOAT;
			channels[numChannels].fill				= oChannel->fill;
			//GSHTODO: duplicate fill
			
			dataSize								+= oChannel->numSamples;
			numChannels++;	
		} else  {
			error(CODE_BADTOKEN,"Unknown display channel \"%s\"\n",sampleName);
		}
		
		sampleName = nextComma;
	} while((sampleName != NULL) && (*sampleName != '\0'));

	free(sampleDefinition);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CTexture3d
// Method				:	defineChannels
// Description			:	Define the channels
// Return Value			:	-
// Comments				:	used by ptcapi, does not require RiBegin()
void CTexture3d::defineChannels(int n,char **channelNames,char **channelTypes) {
	// determinte the channels
	dataSize		=	0;	
	channels		=	new CChannel[n];
	
	// parse the channels / sample types
	numChannels = 0;
	for (int i=0;i<n;i++) {
		// parse to next comma, remove spaces
		
		CVariable var;
		if (parseVariable(&var,channelNames[i],channelTypes[i]) == TRUE) {

			// it's a predefined / already seen channel
			strcpy(channels[numChannels].name,channelNames[i]);
			channels[numChannels].sampleStart		= dataSize;
			channels[numChannels].numSamples		= var.numFloats;
			channels[numChannels].fill				= NULL;
			channels[numChannels].type				= var.type;
			//GSHTODO: deal with fill
			
			dataSize								+= var.numFloats;
			numChannels++;	
		} else  {
			error(CODE_BADTOKEN,"Failed to interpret display channel name \"%s\"\n",channelNames[i]);
		}		
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CTexture3d
// Method				:	writeChannels
// Description			:	Write the channels to file
// Return Value			:	-
// Comments				:
void CTexture3d::writeChannels(FILE *out) {
	// Write out the header and channels
	fwrite(toNDC,sizeof(float)*16,1,out);
	fwrite(&numChannels,sizeof(int),1,out);
	for (int i=0;i<numChannels;i++) {
		fwrite(&channels[i],sizeof(CChannel),1,out);
		//GSHTODO:  deal with fill
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CTexture3d
// Method				:	readChannels
// Description			:	Read the channels from file
// Return Value			:	-
// Comments				:
void CTexture3d::readChannels(FILE *in) {
	if (channels != NULL)	delete [] channels;

	// Write out the header and channels
	fread(toNDC,sizeof(float)*16,1,in);
	fread(&numChannels,sizeof(int),1,in);
	channels = new CChannel[numChannels];
	for (int i=0;i<numChannels;i++) {
		fread(&channels[i],sizeof(CChannel),1,in);
		dataSize += channels[i].numSamples;
		//GSHTODO:  deal with fill
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CTexture3d
// Method				:	resolve
// Description			:	Resolve the names of channels
// Return Value			:	-
// Comments				:
void	CTexture3d::resolve(int n,const char **names,int *entry,int *size) {
	int	i;
	
	// Find the channel for every name
	for (i=0;i<n;i++) {
		int	j;
		
		// Find the channel
		for (j=0;j<numChannels;j++) {
			if (strcmp(names[i],channels[j].name) == 0) {
				entry[i]	=	channels[j].sampleStart;
				size[i]		=	channels[j].numSamples;
				break;
			}
		}
		
		if (j==numChannels) {
			error(CODE_BADTOKEN,"Unknown 3d texture channel \"%s\"\n",names[i]);
			entry[i]		=	0;
			size[i]			=	0;
		}
	}
}




///////////////////////////////////////////////////////////////////////
// Class				:	CTexture3d
// Method				:	queryChannels
// Description			:	queryChannels
// Return Value			:	-
// Comments				:	FIXME and return enums, do the ptcapi conversion there
void CTexture3d::queryChannels(int *num,const char **vartypes,const char **varnames) {
	num[0] = numChannels;
	for (int i=0;i<numChannels;i++)	{
		varnames[i] = channels[i].name;
		switch(channels[i].type) {
			case TYPE_FLOAT:
				vartypes[i] = "float";
				break;
			case TYPE_COLOR:
				vartypes[i] = "color";
				break;
			case TYPE_VECTOR:
				vartypes[i] = "vector";
				break;
			case TYPE_NORMAL:
				vartypes[i] = "normal";
				break;
			case TYPE_POINT:
				vartypes[i] = "point";
				break;
			case TYPE_MATRIX:
				vartypes[i] = "matrix";
				break;
			default:
				error(CODE_BADTOKEN,"Unknown texture3d channel type\n");
		}
	}
}

