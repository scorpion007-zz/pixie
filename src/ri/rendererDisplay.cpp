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
//  File				:	rendererDisplay.cpp
//  Classes				:	CRenderer
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include <string.h>
#include <math.h>

#include "renderer.h"
#include "rendererContext.h"
#include "error.h"
#include "memory.h"
#include "stats.h"
#include "options.h"
#include "remoteChannel.h"
#include "displayChannel.h"




static COptions::CDisplay	*currentDisplay	=	NULL;

///////////////////////////////////////////////////////////////////////
// Function				:	findParameter
// Description			:	This function can be used by the display server to probe for parameters
// Return Value			:	-
// Comments				:
void	*findParameter(const char *name,ParameterType type,int numItems) {
	if (currentDisplay != NULL) {
		int	i;

		// parameters provided on the display line override everything else
		for (i=0;i<currentDisplay->numParameters;i++) {
			if (strcmp(name,currentDisplay->parameters[i].name) == 0) {
				if (numItems == currentDisplay->parameters[i].numItems) {
					if (type == currentDisplay->parameters[i].type) {
						return	currentDisplay->parameters[i].data;
					}
				}
			}
		}
	}
// FIXME: lookup the channel's quantizer
// FIXME: depth quantizer for z
	// Otherwise, we respect Quantize applied to the current display,
	// falling back on the default color / depth quantizer
	if (strcmp(name,"quantize") == 0) {
		if ((numItems == 4) && (type == FLOAT_PARAMETER))	{
			if (currentDisplay->quantizer[0] == -1) {
				if (!strcmp(currentDisplay->outSamples,"z")) {
					return	CRenderer::depthQuantizer;
				} else {
					return	CRenderer::colorQuantizer;
				}
			} else {
				return	currentDisplay->quantizer;
			}
		}
	} else if (strcmp(name,"dither") == 0) {
		if ((numItems == 1) && (type == FLOAT_PARAMETER)) {
			if (currentDisplay->quantizer[0] == -1) {
				if (!strcmp(currentDisplay->outSamples,"z")) {
					return	CRenderer::depthQuantizer + 4;
				} else {
					return	CRenderer::colorQuantizer + 4;
				}
			} else {
				return	currentDisplay->quantizer + 4;
			}
		}
	} else if (strcmp(name,"near") == 0) {
		if ((numItems == 1) && (type == FLOAT_PARAMETER))		return	&CRenderer::clipMin;
	} else if (strcmp(name,"far") == 0) {
		if ((numItems == 1) && (type == FLOAT_PARAMETER))		return	&CRenderer::clipMax;
	} else if (strcmp(name,"Nl") == 0) {
		if ((numItems == 16) && (type == FLOAT_PARAMETER))		return	&CRenderer::fromWorld;
	} else if (strcmp(name,"NP") == 0) {
		if ((numItems == 16) && (type == FLOAT_PARAMETER))		return	&CRenderer::worldToNDC;
	} else if (strcmp(name,"screen") == 0) {
		if ((numItems == 16) && (type == FLOAT_PARAMETER))		return	&CRenderer::toScreen;
	} else if (strcmp(name,"gamma") == 0) {
		if ((numItems == 1) && (type == FLOAT_PARAMETER))		return	&CRenderer::gamma;
	} else if (strcmp(name,"gain") == 0) {
		if ((numItems == 1) && (type == FLOAT_PARAMETER))		return	&CRenderer::gain;
	} else if (strcmp(name,"Software") == 0) {
		if ((numItems == 1) && (type == STRING_PARAMETER))		return	(void *) "Pixie";
	} else if (strcmp(name,"type") == 0 && currentDisplay) {
		if ((numItems == 1) && (type == STRING_PARAMETER))		return	(void *) currentDisplay->outDevice;
	}

	return	NULL;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	getAOVFilter
// Description			:	Return the name matching the filter
// Return Value			:
// Comments				:
int	CRenderer::getAOVFilter(const char *name) {
	if (strcmp(name,RI_ZMIN) == 0) {
		return	AOV_FILTER_ZMIN;
	} else if (strcmp(name,RI_ZMAX) == 0) {
		return AOV_FILTER_ZMAX;
	} else if (strcmp(name,RI_MIN) == 0) {
		return	AOV_FILTER_MIN;
	} else if (strcmp(name,RI_MAX) == 0) {
		return AOV_FILTER_MAX;
	} else if (strcmp(name,RI_AVERAGE) == 0) {
		return AOV_FILTER_AVERAGE;
	} else if (strcmp(name,RI_GAUSSIANFILTER) == 0) {
		return	AOV_FILTER_GAUSSIAN;
	} else if (strcmp(name,RI_BOXFILTER) == 0) {
		return	AOV_FILTER_BOX;
	} else if (strcmp(name,RI_TRIANGLEFILTER) == 0) {
		return	AOV_FILTER_TRIANGLE;
	} else if (strcmp(name,RI_SINCFILTER) == 0) {
		return	AOV_FILTER_SINC;
	} else if (strcmp(name,RI_CATMULLROMFILTER) == 0) {
		return	AOV_FILTER_CATMULLROM;
	} else if (strcmp(name,RI_BLACKMANHARRISFILTER) == 0) {
		return	AOV_FILTER_BLACKMANHARRIS;
	} else if (strcmp(name,RI_MITCHELLFILTER) == 0) {
		return	AOV_FILTER_MITCHELL;
	}

	error(CODE_BADTOKEN,"Unknown AOV filter type: \"%s\"\n",name);
	return	AOV_FILTER_DEFAULT;
}







///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	beginDisplays
// Description			:	Initiate the displays
// Return Value			:	-
// Comments				:
void	CRenderer::beginDisplays() {
	
	// Clear the data first
	numDisplays			=	0;
	numActiveDisplays	=	0;
	datas				=	NULL;

	deepShadowFile		=	NULL;
	deepShadowIndex		=	NULL;
	deepShadowIndexStart=	0;
	
	sampleOrder			=	NULL;
	sampleDefaults		=	NULL;
	compChannelOrder	=	NULL;
	nonCompChannelOrder	=	NULL;

	// Initiate the displays
	if (!(hiderFlags & HIDER_NODISPLAY))
		computeDisplayData();
	else {
		numSamples			=	0;
		numExtraSamples		=	0;
	}

	// If we have a client, do not create a display
	if (netClient != INVALID_SOCKET) {
		numActiveDisplays	=	1;
	}

	// Start a TSM channel if needed
	if ((netClient != INVALID_SOCKET) && (flags & OPTIONS_FLAGS_DEEP_SHADOW_RENDERING)) {
		requestRemoteChannel(new CRemoteTSMChannel(deepShadowFileName,deepShadowFile,deepShadowIndex,xBuckets,yBuckets));
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	endDisplays
// Description			:	Terminate the displays
// Return Value			:	-
// Comments				:
void	CRenderer::endDisplays() {
	int	i;

	// Finish the out images
	for (i=0;i<numDisplays;i++) {
	
		// Is the module up ?
		if (datas[i].module != NULL) {
			datas[i].finish(datas[i].handle);
			if (strcmp(datas[i].display->outDevice,RI_SHADOW) == 0) {
				CRenderer::context->RiMakeShadowV(datas[i].displayName,datas[i].displayName,0,NULL,NULL);
			}
		}
		if (datas[i].displayName != NULL) free(datas[i].displayName);
		
		// Delete the fill array if set
		int	j;
		for (j=0;j<datas[i].numChannels;j++) {
			if (datas[i].channels[j].fill != NULL) delete [] datas[i].channels[j].fill;
		}
		
		// Delete the channels
		delete[] datas[i].channels;
	}

	if (datas != NULL)					delete[] datas;
	if (sampleOrder != NULL)			delete[] sampleOrder;
	if (sampleDefaults != NULL)			delete[] sampleDefaults;
	if (compChannelOrder != NULL)		delete[] compChannelOrder;
	if (nonCompChannelOrder != NULL)	delete[] nonCompChannelOrder;
	
	if (deepShadowFile != NULL) {
		fseek(deepShadowFile,deepShadowIndexStart,SEEK_SET);
		fwrite(deepShadowIndex,sizeof(int),xBuckets*yBuckets*2,deepShadowFile);	// Override the deep shadow map index
		fclose(deepShadowFile);
	}

	if (deepShadowIndex != NULL) {
		delete [] deepShadowIndex;
		free(deepShadowFileName);
	}
}

// The maximum memory we should try to allocate on the stack in dispatch / clear
#define MAX_DISPATCH_SIZE 100000

///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	dispatch
// Description			:	Dispatch a rendered window to the out devices
// Return Value			:	-
// Comments				:	Thread safe
void	CRenderer::dispatch(int left,int top,int width,int height,float *pixels) {
	float	*dest;
	int		i,j,k,l;
	int		srcStep,dstStep,disp;

	// Send the pixels to the output servers
	for (i=0;i<numDisplays;i++) {
		if (datas[i].module != NULL) {
			float	*dispatchData;
			int		imageSamples							=	datas[i].numSamples;
			int		size									=	width*height*imageSamples*sizeof(float);
			
			if (size < MAX_DISPATCH_SIZE) 	dispatchData	=	(float *) alloca(size);
			else							dispatchData	=	new float[width*height*imageSamples];
			
			for (j=0,disp=0;j<datas[i].numChannels;j++){
				const float		*tmp			=	&pixels[datas[i].channels[j].sampleStart];
				const int		channelSamples	=	datas[i].channels[j].numSamples;
				
				dest		=	dispatchData + disp;
				srcStep		=	numSamples - channelSamples;
				dstStep		=	imageSamples - channelSamples;
				disp		+=	channelSamples;
	
				for (k=width*height;k>0;k--) {
					for (l=channelSamples;l>0;l--) {
						*dest++	=	*tmp++;
					}
					tmp		+=	srcStep;
					dest	+=	dstStep;
				}
			}

			if (datas[i].data(datas[i].handle,left,top,width,height,dispatchData) == FALSE) {
				// Lock this piece of code
				osLock(displayKillMutex);
				datas[i].handle	=	NULL;
				numActiveDisplays--;
				if (numActiveDisplays == 0)	hiderFlags	|=	HIDER_BREAK;
				osUnloadModule(datas[i].module);
				datas[i].module	=	NULL;
				osUnlock(displayKillMutex);
			}

			if (size >= MAX_DISPATCH_SIZE)	delete [] dispatchData;
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	clear
// Description			:	Send a clear window to the out devices
// Return Value			:	-
// Comments				:	Thread safe
void	CRenderer::clear(int left,int top,int width,int height) {
	float	*pixels;
	int		size								=	width*height*numSamples*sizeof(float);
	if (size < MAX_DISPATCH_SIZE)	pixels	=	(float *) alloca(size);
	else							pixels	=	new float[width*height*numSamples];

	for (int i=0;i<width*height*numSamples;i++)	pixels[i]	=	0;

	dispatch(left,top,width,height,pixels);
	
	if (size >= MAX_DISPATCH_SIZE)	delete [] pixels;
}



///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	commit
// Description			:	Send a window of samples
// Return Value			:	-
// Comments				:	Thread safe
void	CRenderer::commit(int left,int top,int xpixels,int ypixels,float *pixels) {
	// Progress stats
	if (flags & OPTIONS_FLAGS_PROGRESS)	{
		// FIXME: This is not thread safe !!!
		// But it's just for reporting progress, so who cares
		numRenderedBuckets++;
		stats.progress		=	(numRenderedBuckets*100) / (float) (xBuckets * yBuckets);
		if (numRenderedBuckets == xBuckets*yBuckets)	info(CODE_PROGRESS,"Done                    \r\n");
		else											info(CODE_PROGRESS,"Done %%%3.2f\r",stats.progress);		
	}
	
	if (netClient != INVALID_SOCKET) {
		// We are rendering for a client, so just send the result to the waiting client
		T32	header[5];
		T32	a;

		// Lock network
		osLock(networkMutex);

		header[0].integer	=	NET_READY;
		rcSend(netClient,header,	1*sizeof(T32));

		header[0].integer	=	left;
		header[1].integer	=	top;
		header[2].integer	=	xpixels;
		header[3].integer	=	ypixels;
		header[4].integer	=	xpixels*ypixels*numSamples;

		rcSend(netClient,header,	5*sizeof(T32));
		rcRecv(netClient,&a,		1*sizeof(T32));
		rcSend(netClient,pixels,xpixels*ypixels*numSamples*sizeof(T32));

		// Unlock network
		osUnlock(networkMutex);

		return;
	}

	if ((top == 0) && (left == 0)) {
		if (renderTop > 0)			clear(0,0,xres,renderTop);
	}

	if (left == 0) {
		if (renderLeft > 0)			clear(0,top+renderTop,renderLeft,ypixels);
	}

	if ((left+xpixels) == xPixels) {
		if (renderRight < xres)		clear(renderRight,top+renderTop,xres-renderRight,ypixels);
	}

	if (((top+ypixels) == yPixels) && ((left+xpixels) == xPixels)) {
		if (renderBottom < yres)	clear(0,renderBottom,xres,yres-renderBottom);
	}


	dispatch(left+renderLeft,top+renderTop,xpixels,ypixels,pixels);
}



///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	getDisplayName
// Description			:	Create the display name
// Return Value			:
// Comments				:
void	CRenderer::getDisplayName(char *out,const char *in,const char *displayType) {
	char		*cOut	=	out;
	const char	*cIn	=	in;

	while(*cIn != '\0') {
		if (*cIn == '#') {
			int		width		=	0;
			char	widthString[256];

			cIn++;

			while((*cIn >= '0') && (*cIn <= '9')) {
				widthString[width++]	=	*cIn++;
			}

			if (width > 0) {
				widthString[width]	=	'\0';
				sscanf(widthString,"%d",&width);
				sprintf(widthString,"%%0%dd",width);
			} else {
				sprintf(widthString,"%%d");
			}

			switch(*cIn++) {
			case 'f':
				sprintf(cOut,widthString,(int) frame);
				while(*cOut != '\0')	cOut++;
				break;
			case 's':
				sprintf(cOut,widthString,stats.sequenceNumber);
				while(*cOut != '\0')	cOut++;
				break;
			case 'n':
				sprintf(cOut,widthString,stats.runningSequenceNumber);
				while(*cOut != '\0')	cOut++;
				break;
			case 'h':
				char	hostName[1024];
				gethostname(hostName,1024);
				sprintf(cOut,hostName);
				while(*cOut != '\0')	cOut++;
				break;
			case 'd':
				strcpy(cOut,displayType);
				while(*cOut != '\0')	cOut++;
				break;
			case 'p':
				sprintf(cOut,"0");
				while(*cOut != '\0')	cOut++;
				break;
			case 'P':
				sprintf(cOut,"0");
				while(*cOut != '\0')	cOut++;
				break;
			case '#':
				sprintf(cOut,"#");
				while(*cOut != '\0')	cOut++;
				break;
			default:
				error(CODE_BADTOKEN,"Unknown display stub %c\n",*cIn);
				break;
			}
		} else {
			*cOut++	=	*cIn++;
		}
	}

	*cOut	=	'\0';
}




///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	computeDisplayData
// Description			:	Compute the display data
// Return Value			:
// Comments				:
void	CRenderer::computeDisplayData() {
	COptions::CDisplay	*cDisplay;
	CDisplayChannel		*oChannel;
	char				displayName[OS_MAX_PATH_LENGTH];
	char				deviceFile[OS_MAX_PATH_LENGTH];
	char				*sampleDefinition,*sampleName,*nextComma,*tmp;
	int					i,j,k,s,isNewChannel;
	int					hasZOutput = FALSE;

	// mark all channels as unallocated
	resetDisplayChannelUsage();
	
	for (i=0,cDisplay=displays;cDisplay!=NULL;i++,cDisplay=cDisplay->next);

	datas					=	new CDisplayData[i];
	j						=	0;
	numSamples				=	5;	// rgbaz
	numExtraSamples			=	0;
	numDisplays				=	0;
	numExtraChannels		=	0;
	additionalParameters	=	0;
	numActiveDisplays		=	0;
	deepShadowFile			=	NULL;
	deepShadowIndex			=	NULL;

	for (cDisplay=displays;cDisplay!=NULL;cDisplay=cDisplay->next) {
		datas[numDisplays].display		=	cDisplay;
		datas[numDisplays].displayName	=	NULL;
		datas[numDisplays].numChannels	=	0;
		datas[numDisplays].channels		=	NULL;
		datas[numDisplays].numSamples	=	0;
		
		int dspError					=	FALSE;
		int dspNumExtraChannels			=	0;
		int dspNumSamples				=	0;
		int dspNumExtraSamples			=	0;
		
		// work out how many channels to expect (at least one)
		int dspNumChannels = 1;
		sampleDefinition = cDisplay->outSamples;
		while ((sampleDefinition = strchr(sampleDefinition,',')) != NULL) {
			sampleDefinition++;
			dspNumChannels++;
		}
		datas[numDisplays].channels = new CDisplayChannel[dspNumChannels];
		
		// parse the channels / sample types
		sampleDefinition = strdup(cDisplay->outSamples); // duplicate to tokenize
		nextComma = sampleName = sampleDefinition;
		dspNumChannels = 0;
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
			oChannel = retrieveDisplayChannel(sampleName);
			if (oChannel != NULL) {
				// it's a predefined / already seen channel
			
				if (oChannel->variable != NULL) {
					// variable is NULL only for RGBAZ channels
					if (hiderFlags & HIDER_RGBAZ_ONLY) {
						error(CODE_BADTOKEN,"Hider \"%s\" cannot handle display channels\n",hider);
						dspError = TRUE;
						break;
					}	
					
					// Make sure the variable is global
					if (oChannel->outType == -1) {
						makeGlobalVariable(oChannel->variable);
						oChannel->outType = oChannel->variable->entry;
					}
				}
			} else {
				// it's an old-style AOV
				
				if (hiderFlags & HIDER_RGBAZ_ONLY) {
					error(CODE_BADTOKEN,"Hider \"%s\" cannot handle arbitrary output variables\n",hider);
					dspError = TRUE;
					break;
				} else {				
					CVariable	*cVar		=	retrieveVariable(sampleName);
					
					// if it's an inline declaration but it's not defined yet, declare it
					if (cVar == NULL) {
						cVar = declareVariable(NULL,sampleName);
					}
	
					if (cVar != NULL) {
						// Make sure the variable is global
						if (cVar->storage != STORAGE_GLOBAL) {
							makeGlobalVariable(cVar);
						} else if (cVar->storage == STORAGE_PARAMETER || cVar->storage == STORAGE_MUTABLEPARAMETER) {
							error(CODE_BADTOKEN,"Failed to find output variable or display channel \"%s\"\n",sampleName);
							dspError = TRUE;
							break;
						}
					} else {
						error(CODE_BADTOKEN,"Failed to find output variable or display channel \"%s\"\n",sampleName);
						dspError = TRUE;
						break;
					}
										
					// now create a channel for the variable
					oChannel = declareDisplayChannel(cVar);
					
					if (oChannel == NULL) {
						error(CODE_BADTOKEN,"Variable \"%s\" clashes with a display channel\n",cVar->name);
						dspError = TRUE;
						break;
					}
				}
			}
			
			// record channel if it's new
			isNewChannel = FALSE;
			if (oChannel->sampleStart == -1) {
				// sampleStart is -1 only for channels not yet allocated
				oChannel->sampleStart		=	numSamples + dspNumSamples;
				dspNumSamples				+=	oChannel->numSamples;
				dspNumExtraSamples			+=	oChannel->numSamples;
				additionalParameters		|=	oChannel->variable->usageMarker;
				dspNumExtraChannels++;
				isNewChannel = TRUE;
			}
			memcpy(datas[numDisplays].channels + dspNumChannels,oChannel,sizeof(CDisplayChannel));
			if (oChannel->fill) {
				// ensure a deep copy
				datas[numDisplays].channels[dspNumChannels].fill = new float[oChannel->numSamples];
				for(s=0;s<datas[numDisplays].channels[dspNumChannels].numSamples;s++)
					datas[numDisplays].channels[dspNumChannels].fill[s] = oChannel->fill[s];
			}
			if (isNewChannel == FALSE) {
				// mark this channel as a duplicate
				datas[numDisplays].channels[dspNumChannels].variable = NULL;
			}
			
			datas[numDisplays].numSamples		+= oChannel->numSamples;
			dspNumChannels++;
			
			// do we cover z?
			if (oChannel->sampleStart < 5 && (oChannel->sampleStart + oChannel->numSamples >= 5)) {
				hasZOutput = TRUE;
			}

			// advance the channel definition
			sampleName = nextComma;
		} while((sampleName != NULL) && (*sampleName != '\0'));
		
		free(sampleDefinition);
		
		if (dspError) {
			error(CODE_BADTOKEN,"Display \"%s\" disabled\n",cDisplay->outName);
			delete [] datas[numDisplays].channels;
			continue;
		}
		
		// Sum up if we successfully allocated display
		datas[numDisplays].numChannels	=	dspNumChannels;
		numSamples						+=	dspNumSamples;
		numExtraSamples					+=	dspNumExtraSamples;
		numExtraChannels				+=	dspNumExtraChannels;

		// finally deal with the display initialization
		getDisplayName(displayName,cDisplay->outName,cDisplay->outSamples);
		
		// save the computed display name
		datas[numDisplays].displayName = strdup(displayName);
		
		const char * outDevice = cDisplay->outDevice;
		if (strcmp(outDevice,"shadow") == 0
			|| strcmp(outDevice,"zfile") == 0
			|| strcmp(outDevice,"tiff") == 0
			|| strcmp(outDevice,"png") == 0)
			outDevice	=	RI_FILE;
			
		if (strcmp(outDevice,"tsm") == 0) {
			int					j;
			CDeepShadowHeader	header;

			// The TSM is hardcoded
			datas[numDisplays].module	=	NULL;
			datas[numDisplays].handle	=	NULL;

			// Set up the file header
			header.xres		=	xres;
			header.yres		=	yres;
			header.xTiles	=	xBuckets;
			header.yTiles	=	yBuckets;
			header.tileSize	=	bucketWidth;
			for (header.tileShift=1;(1 << header.tileShift) < bucketWidth;header.tileShift++);
			movmm(header.toNDC,worldToNDC);
			movmm(header.toCamera,fromWorld);

			// The sanity check
			if ((1 << header.tileShift) != bucketWidth) {
				error(CODE_LIMIT,"Bucket width must be a power of 2 for TSM: %d\n",bucketWidth);
			} else {
				if (bucketWidth != bucketHeight) {
					error(CODE_LIMIT,"Bucket width and height must be same for TSM: (%d,%d)\n",bucketWidth,bucketHeight);
				} else {
					if (strcmp(hider,"stochastic") != 0) {
						error(CODE_LIMIT,"Hider must be stochastic or hidden for TSM\n");
					} else {
						if (deepShadowFile != NULL) {
							error(CODE_LIMIT,"There can only be one TSM output\n");
						} else {
							if (netClient != INVALID_SOCKET) {
								char tempTsmName[OS_MAX_PATH_LENGTH];
								
								if (!osFileExists(temporaryPath)) {
									osCreateDir(temporaryPath);
								}
								
								// need read and write
								osTempname(temporaryPath,"rndr",tempTsmName);
								deepShadowFile		=	ropen(tempTsmName,"w+b",fileTransparencyShadow);
								
								// register temporary for deletion
								registerFrameTemporary(tempTsmName,TRUE);
							} else {
								deepShadowFile		=	ropen(displayName,"wb",fileTransparencyShadow);
							}
	
							if (deepShadowFile != NULL) {
								numActiveDisplays++;
								flags						|=	OPTIONS_FLAGS_DEEP_SHADOW_RENDERING;
	
								deepShadowIndex				=	new int[xBuckets*yBuckets*2];
								deepShadowFileName			=	strdup(displayName);
								
								// Write the header
								fwrite(&header,sizeof(CDeepShadowHeader),1,deepShadowFile);
	
								// Save the index start
								deepShadowIndexStart	=	ftell(deepShadowFile);
	
								// Write the dummy index
								fwrite(deepShadowIndex,sizeof(int),xBuckets*yBuckets*2,deepShadowFile);
	
								// Parse the tsm parameters
								for (j=0;j<cDisplay->numParameters;j++) {
									if (strcmp(cDisplay->parameters[j].name,"threshold") == 0) {
										float	*val	=	(float *) cDisplay->parameters[j].data;
	
										tsmThreshold	=	val[0];
									}
								}
							}
						}
					}
				}
			}
		} else if (netClient == INVALID_SOCKET) {
			
			// Is this a custom display driver?
			if (strcmp(outDevice,"custom") == 0) {
				datas[numDisplays].module		=	(void *) outDevice;
				datas[numDisplays].start		=	(TDisplayStartFunction) cDisplay->startFunction;
				datas[numDisplays].data			=	(TDisplayDataFunction) cDisplay->dataFunction;
				datas[numDisplays].rawData		=	NULL;
				datas[numDisplays].finish		=	(TDisplayFinishFunction) cDisplay->finishFunction;
			} else {

				// Load the display driver
				if (locateFileEx(deviceFile,outDevice,osModuleExtension,displayPath)) {
					datas[numDisplays].module		=	osLoadModule(deviceFile);
					datas[numDisplays].start		=	(TDisplayStartFunction)		osResolve(datas[numDisplays].module,"displayStart");
					datas[numDisplays].data			=	(TDisplayDataFunction)		osResolve(datas[numDisplays].module,"displayData");
					datas[numDisplays].rawData		=	(TDisplayRawDataFunction)	osResolve(datas[numDisplays].module,"displayRawData");
					datas[numDisplays].finish		=	(TDisplayFinishFunction)	osResolve(datas[numDisplays].module,"displayFinish");
				} else {
					datas[numDisplays].module		=	NULL;
					error(CODE_SYSTEM,"Failed to open out device \"%s\" (error: %s)\n",cDisplay->outDevice,osModuleError());
				}
			}

			// Check the stuff
			if ((datas[numDisplays].start == NULL) || (datas[numDisplays].data == NULL) || (datas[numDisplays].finish == NULL)) {
				error(CODE_SYSTEM,"The module \"%s\" has missing implementation\n",deviceFile);
				if (datas[numDisplays].module != outDevice)
					osUnloadModule(datas[numDisplays].module);
				datas[numDisplays].module	=	NULL;
			} else {
				currentDisplay				=	cDisplay;
				datas[numDisplays].handle	=	datas[numDisplays].start(displayName,xres,yres,datas[numDisplays].numSamples,cDisplay->outSamples,findParameter);
					//GSHTODO: above sample names are now quite incorrect
				if (datas[numDisplays].handle != NULL) {
					numActiveDisplays++;
				} else {
					if (datas[numDisplays].module != outDevice)
						osUnloadModule(datas[numDisplays].module);
					datas[numDisplays].module	=	NULL;
				}
			}
		} else {
			datas[numDisplays].module	=	NULL;
			datas[numDisplays].handle	=	NULL;
		}

		numDisplays++;
	}
	
	// copy the sample and sampled defaults order for fast access
	
	// Note: sampleOrder is used to unpack variables from the varying state into
	// the extraSamples buffer for each fragment
	
	// Note: compChannelOrder and nonCompChannelOrder are used during the composite
	// loops to alter the way we composite AOV channels
	
	sampleOrder				=	new int[numExtraChannels*2];	// variableEntry,numSamples
	sampleDefaults			=	new float[numExtraSamples];
	compChannelOrder		=	new int[numExtraChannels*4];	// offset,numSamples,matteMode,variableEntry
	nonCompChannelOrder		=	new int[numExtraChannels*4];
	numExtraCompChannels	=	0;
	numExtraNonCompChannels	=	0;
	
	int sampleOffset = 0;	// rgbaz
	for (i=0,k=0;i<numDisplays;i++) {
		for (j=0;j<datas[i].numChannels;j++) {
			// skip standard channels
			if (datas[i].channels[j].outType == -1) continue;
			// skip duplicate channels
			if (datas[i].channels[j].variable == NULL) continue;
			
			if (datas[i].channels[j].fill) {
				for(s=0;s<datas[i].channels[j].numSamples;s++)
					sampleDefaults[sampleOffset+s] = datas[i].channels[j].fill[s];
			} else {
				for(s=0;s<datas[i].channels[j].numSamples;s++) sampleDefaults[sampleOffset+s] = 0;
			}
			
			sampleOrder[k++] = datas[i].channels[j].outType;
			sampleOrder[k++] = datas[i].channels[j].numSamples;

			if (datas[i].channels[j].filterType > AOV_FILTER_SPECIALFILTERS) {
				// verify it matches the main pixel filter
				
			}
			
			// _only_ color can be composited
			if ((datas[i].channels[j].variable->type == TYPE_COLOR) && (datas[i].channels[j].filterType == AOV_FILTER_DEFAULT)) {
// FIXME: this logic should cope with user filter choice					
				compChannelOrder[numExtraCompChannels*4+0]			= sampleOffset;
				compChannelOrder[numExtraCompChannels*4+1]			= datas[i].channels[j].numSamples;
				compChannelOrder[numExtraCompChannels*4+2]			= datas[i].channels[j].matteMode;
				compChannelOrder[numExtraCompChannels*4+3]			= datas[i].channels[j].outType;
				numExtraCompChannels++;
			} else {
				nonCompChannelOrder[numExtraNonCompChannels*4+0]	= sampleOffset;
				nonCompChannelOrder[numExtraNonCompChannels*4+1] 	= datas[i].channels[j].numSamples;
				nonCompChannelOrder[numExtraNonCompChannels*4+2] 	= datas[i].channels[j].matteMode;
				nonCompChannelOrder[numExtraNonCompChannels*4+3]	= datas[i].channels[j].outType;
				numExtraNonCompChannels++;
			}
			
			sampleOffset += datas[i].channels[j].numSamples;
		}
	}
	assert(numExtraCompChannels + numExtraNonCompChannels == numExtraChannels);
	assert(k == 2*numExtraChannels);

	// If we are not outputting Z, do not perform midpoint calculations
	// it is slower and we're not outputting the data
	if (!hasZOutput && (depthFilter == DEPTH_MID)) {
		depthFilter = DEPTH_MIN;
	}

	// No active displays? Abort rendering
	if (numActiveDisplays == 0) hiderFlags	|=	HIDER_BREAK;
}

