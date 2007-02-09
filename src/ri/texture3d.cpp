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
CTexture3d::CTexture3d(const char *n,const float *f,const float *t,int nc,CTexture3dChannel *ch) : CFileResource(n) { 
	dataSize	=	0;
	channels	=	NULL;
	numChannels	=	0;
	movmm(from,f);
	movmm(to,t);
	dPscale		=	pow(fabs(determinantm(to)),1.0f / 3.0f);

	if (nc > 0) {
		int	i;

		numChannels		=	nc;
		channels		=	new CTexture3dChannel[nc];
		memcpy(channels,ch,sizeof(CTexture3dChannel)*numChannels);
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
	channels		=	new CTexture3dChannel[numChannels];
	
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
// Method				:	writeChannels
// Description			:	Write the channels to file
// Return Value			:	-
// Comments				:
void CTexture3d::writeChannels(FILE *out) {
	// Write out the header and channels
	fwrite(&numChannels,1,sizeof(int),out);
	for (int i=0;i<numChannels;i++) {
		fwrite(&channels[i],1,sizeof(CTexture3dChannel),out);
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
	fread(&numChannels,1,sizeof(int),in);
	channels = new CTexture3dChannel[numChannels];
	for (int i=0;i<numChannels;i++) {
		fread(&channels[i],1,sizeof(CTexture3dChannel),in);
		dataSize += channels[i].numSamples;
		//GSHTODO:  deal with fill
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CTexture3d
// Method				:	bindChannelNamess
// Description			:	Resolve the channel names
// Return Value			:	-
// Comments				:
int CTexture3d::bindChannelNames(int &n,const char **names,CTexture3dChannel ***bindings) {
	CTexture3dChannel	**entryPointers		= new CTexture3dChannel*[numChannels];
	int					numChannelsBound	= 0;
	int					i,j;
	
	for (i=0;i<n;i++) {
		for(j=0;j<numChannels;j++) {
			if (strcmp(names[i],channels[j].name) ==0) {
				entryPointers[numChannelsBound++] = &channels[j];
				break;
			}
		}
		if (j==numChannels) {
			error(CODE_BADTOKEN,"Unknown 3d texture channel \"%s\"\n",names[i]);
			bindings[i] = NULL;
		}
	}
	// zero unbound channels
	for (i=numChannelsBound;i<numChannels;i++) {
		bindings[i] = NULL;
	}
	n			= numChannelsBound;
	*bindings	= entryPointers;

	return dataSize;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CTexture3d
// Method				:	prepareSample
// Description			:	prepareSample
// Return Value			:	-
// Comments				:
void CTexture3d::prepareSample(float *C,float **samples,CTexture3dChannel **bindings) {
	float *src,*dest;

	for (int i=0;i<numChannels;i++)	{
		CTexture3dChannel *binding = bindings[i];

		if (binding != NULL) {
			dest	= C + binding->sampleStart;
			src		= samples[i];
			for (int j=0;j<binding->numSamples;j++)
				*dest++ = *src++;
		} else {
			// GSHTODO : zero / fill the samples
		}
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CTexture3d
// Method				:	unpackSample
// Description			:	unpackSample
// Return Value			:	-
// Comments				:
void CTexture3d::unpackSample(float *C,float **samples,CTexture3dChannel **bindings) {
	float *src,*dest;

	for (int i=0;i<numChannels;i++)	{
		CTexture3dChannel *binding = bindings[i];
		if (binding != NULL) {
			src		= C + binding->sampleStart;
			dest	= samples[i];
			for (int j=0;j<binding->numSamples;j++)
				*dest++ = *src++;
		}
	}
}

