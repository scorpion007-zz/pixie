//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright � 1999 - 2003, Okan Arikan
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
//  File				:	remoteChannel.cpp
//  Classes				:	
//  Description			:	This base class for remote deep data channels
//
////////////////////////////////////////////////////////////////////////

#include	<string.h>
#include	<math.h>

#include	"common/global.h"
#include	"common/containers.h"

#include	"renderer.h"
#include	"remoteChannel.h"
#include	"error.h"
#include	"irradiance.h"
#include	"pointCloud.h"

#define	BUFFER_LENGTH	1 << 12				// The size of the buffer to be used during the network file transfers


///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	requestRemoteChannel
// Description			:	Ask client to set up remote channel like the
//							one passed as an argument
// Return Value			:
// Comments				:	The channel will either be deleted or managed
int		CRenderer::requestRemoteChannel(CRemoteChannel *serverChannel){
	int nameLength			= strlen(serverChannel->name)+1;
	int clientInitialized	= FALSE;	
	T32 buffer[3];
	
	// Send the request
	// Note: we send a byte-order marker to ensure same-endianness
	buffer[0].integer	=	NET_CREATE_CHANNEL;
	buffer[1].integer	=	nameLength;
	buffer[2].integer	=	(serverChannel->channelType << 8) | CHANNELTYPE_BOM;
	rcSend(netClient,(char *) &buffer[0],2*sizeof(T32));
	rcSend(netClient,(char *) &buffer[2],1*sizeof(T32),FALSE);
	rcSend(netClient,(char *) serverChannel->name,nameLength,FALSE);
	
	// Does the client accept the request?
	rcRecv(netClient,(char *) buffer,2*sizeof(T32));
	if (buffer[0].integer != -1) {
		serverChannel->remoteId = buffer[0].integer;
		
		// do we need to intialize
		if (buffer[1].integer == NET_ACK) {
			
			// yes? initialize the client channel
			if (serverChannel->sendSetupData(netClient) == FALSE) {
				// Doesn't matter what the client thought, just ignore it
				rcRecv(netClient,(char *) buffer,sizeof(T32));
				
				// Notify client of failure
				buffer[0].integer	=	NET_NACK;
				rcSend(netClient,(char *) buffer,sizeof(T32));
				
				error(CODE_BUG,"Remote channel initialization failed.\n");
				delete serverChannel;
				return FALSE;
			}
			
			// Did the client initialize correctly
			rcRecv(netClient,(char *) buffer,sizeof(T32));
			clientInitialized = (buffer[0].integer == NET_ACK);
			
			// let client know we initialized
			buffer[0].integer	=	NET_ACK;
			rcSend(netClient,(char *) buffer,sizeof(T32));
			
		} else {
			clientInitialized = TRUE;
		}
	} else {
		error(CODE_BUG,"Client refused remote channel request.\n");
		delete serverChannel;
		return FALSE;
	}
	
	if (clientInitialized == TRUE) {		
		// record the channel
		remoteChannels->push(serverChannel);
		declaredRemoteChannels->insert(serverChannel->name,serverChannel);
	} else {
		error(CODE_BUG,"Remote channel initialization failed.\n");
		delete serverChannel;
		return FALSE;
	}
	
	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	processChannelRequest
// Description			:	Service request for channel, adding the
//							newly created channel to the list if successful
// Return Value			:
// Comments				:	called from CRendererContext:processServerRequest
int		CRenderer::processChannelRequest(int index,SOCKET s){
	int				channelNameLength	= 0;
	int				channelType			= 0;
	CRemoteChannel	*rChannel			= NULL;
	
	// Receive the request
	T32 buffer[2];
	buffer[0].integer	=	REMOTECHANNEL_NONE;
	buffer[1].integer	=	0;
	rcRecv(s,(char *) &buffer[0],sizeof(T32));
	rcRecv(s,(char *) &buffer[1],sizeof(T32),FALSE);
	
	// verify type
	channelNameLength	=	buffer[0].integer;
	channelType			=	buffer[1].integer;
	char *channelName	=	(char *) alloca(channelNameLength);
	rcRecv(s,(char *) channelName,channelNameLength,FALSE);
	
	// check channel byte order
	if ((channelType & CHANNELTYPE_BOM) != CHANNELTYPE_BOM) {
		// unknown type!
		buffer[0].integer	=	-1;
		buffer[1].integer	=	NET_NACK;
		rcSend(s,(char *) buffer,2*sizeof(T32));
		error(CODE_BUG,"Remote channels may not communicate over different byte orders.\n");
		return FALSE;
	}
	
	channelType &= ~CHANNELTYPE_BOM;
	channelType = channelType >> 8;
	
	// Check if we've seen the channel before
	if(declaredRemoteChannels->find(channelName,rChannel) == TRUE){
		// If so, trivially accept it
		buffer[0].integer	=	rChannel->remoteId;
		buffer[1].integer	=	NET_NACK;
		rcSend(s,(char *) buffer,2*sizeof(T32));
		return TRUE;
	} else {
		switch (channelType) {
		case CHANNELTYPE_TSM:
			// create a TSM channel
			rChannel = new CRemoteTSMChannel(channelName,deepShadowFile,deepShadowIndex,xBuckets,yBuckets);
			rChannel->remoteId = remoteChannels->numItems;
			buffer[0].integer	=	rChannel->remoteId;
			buffer[1].integer	=	NET_ACK;
			break;
		case CHANNELTYPE_ICACHE:
			{
			// create an irradiancecache channel
			CIrradianceCache * cache = (CIrradianceCache*) getCache(channelName,"w");
			rChannel = new CRemoteICacheChannel(cache);
			rChannel->remoteId = remoteChannels->numItems;
			buffer[0].integer	=	rChannel->remoteId;
			buffer[1].integer	=	NET_ACK;
			break;
			}
		case CHANNELTYPE_PTCLOUD:
			{
			// create an pointcloud channel.
			// Note: the channel definitions are duff
			CPointCloud *cloud = (CPointCloud*)  getTexture3d(channelName,TRUE,NULL,CRenderer::fromWorld,CRenderer::toWorld);			
			rChannel = new CRemotePtCloudChannel(cloud);
			rChannel->remoteId = remoteChannels->numItems;
			buffer[0].integer	=	rChannel->remoteId;
			buffer[1].integer	=	NET_ACK;
			break;
			}
		case CHANNELTYPE_INVALID:
		default:
			// unknown type!
			buffer[0].integer	=	-1;
			buffer[1].integer	=	NET_NACK;
			rcSend(s,(char *) buffer,2*sizeof(T32));
			error(CODE_BUG,"Invalid remote channel type requested.\n");
			return FALSE;
		}
		
		// Send the accept
		rcSend(s,(char *) buffer,2*sizeof(T32));
		
		// Attempt to setup the channel
		if (rChannel->setup(s) == FALSE) {
			// tell server that initialization failed
			buffer[0].integer = NET_NACK;
			rcSend(s,(char *) buffer,sizeof(T32));
			
			// Ignore the server response
			rcRecv(s,(char *) buffer,sizeof(T32));
			error(CODE_BUG,"Remote channel initialization failed.\n");
			return FALSE;
		}
		
		// Notify server that we succeeded
		buffer[0].integer = NET_ACK;
		rcSend(s,(char *) buffer,sizeof(T32));
		
		// Find out if the server succeeded...
		rcRecv(s,(char *) buffer,sizeof(T32));
		if (buffer[0].integer == NET_ACK) {
			remoteChannels->push(rChannel);
			declaredRemoteChannels->insert(rChannel->name,rChannel);
		} else {
			error(CODE_BUG,"Remote channel initialization failed.\n");
			delete rChannel;
			return FALSE;
		}
	}
	
	return TRUE;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	sendBucketDataChannels
// Description			:	Send all bucket-data channels
// Return Value			:
// Comments				:	called from render loop (reyes.cpp or raytracer.cpp)
void CRenderer::sendBucketDataChannels(int x,int y) {
	long			numChannelsToSend	= remoteChannels->numItems;
	CRemoteChannel	**channels			= remoteChannels->array;
	T32				buffer[2];
	
	
	for(int i=0;i<numChannelsToSend;i++){
		if (channels[i] == NULL) continue;					// it's an errored-out channel
		
		if (channels[i]->flags & REMOTECHANNEL_PERBUCKET) {
			// Request update and send channel index
			buffer[0].integer = NET_ACK;
			buffer[1].integer = channels[i]->remoteId;
			rcSend(netClient,(char*) buffer,2*sizeof(T32));
			rcRecv(netClient,(char*) buffer,1*sizeof(T32));	// get response back
			
			if (buffer[0].integer == NET_ACK) {
				if (channels[i]->sendRemoteBucket(netClient,x,y) == FALSE){
					error(CODE_BUG,"Remote channel communication error.\n");
					
					CRemoteChannel *val;
					declaredRemoteChannels->erase(channels[i]->name,val);
					delete channels[i];
					channels[i] = NULL;
				}
			} else {
				error(CODE_BUG,"Client refused update for remote channel.\n");

				CRemoteChannel *val;
				declaredRemoteChannels->erase(channels[i]->name,val);
				delete channels[i];
				channels[i] = NULL;
			}
		}
	}
	buffer[0].integer = NET_NACK;
	rcSend(netClient,(char*) buffer,2*sizeof(T32));
	rcRecv(netClient,(char*) buffer,1*sizeof(T32));	// get response back
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	recvBucketDataChannels
// Description			:	Recieve all bucket-data channels
// Return Value			:
// Comments				:	Each channel update is preceeded by identified
//							which was assigned when creating it
void CRenderer::recvBucketDataChannels(SOCKET s,int x,int y) {
	long			numKnownChannels	= remoteChannels->numItems;
	CRemoteChannel	**channels			= remoteChannels->array;
	T32 			buffer[2];
	int				remoteId;
	
	
	while(TRUE) {
		// receive update request - buffer[0] tells us
		// if there are any pending updates
		rcRecv(s,(char*) buffer,2*sizeof(T32));
		
		if(buffer[0].integer == NET_ACK) {
			// if we have updates then figure out what channel index
			remoteId = buffer[1].integer;
			
			if ((remoteId>=0) && (remoteId<numKnownChannels) && (channels[remoteId]!=NULL)){
				// Accept the update
				buffer[0].integer = NET_ACK;
				rcSend(s,(char*) buffer,1*sizeof(T32));
				// Perform it
				if (channels[remoteId]->recvRemoteBucket(s,x,y) == FALSE) {
					error(CODE_BUG,"Remote channel communication error.\n");
				}
			} else {
				error(CODE_BUG,"Update received for unkown remote channel.\n");
				buffer[0].integer = NET_NACK;
				rcSend(s,(char*) buffer,1*sizeof(T32));
			}
		} else {
			// No pending updates - we are done
			break;
		}
	}	
	buffer[0].integer = NET_ACK;
	rcSend(s,(char*) buffer,1*sizeof(T32));
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	sendFrameDataChannels
// Description			:	Send all frame-data channels
// Return Value			:
// Comments				:	called from render loop (reyes.cpp or raytracer.cpp)
void CRenderer::sendFrameDataChannels() {
	long			numChannelsToSend	= remoteChannels->numItems;
	CRemoteChannel	**channels			= remoteChannels->array;
	T32 			buffer[2];
	
	for(int i=0;i<numChannelsToSend;i++){
		if (channels[i] == NULL) continue;					// it's an errored-out channel
		
		if (channels[i]->flags & REMOTECHANNEL_PERFRAME) {
			// Request update and send channel index
			buffer[0].integer = NET_ACK;
			buffer[1].integer = channels[i]->remoteId;
			rcSend(netClient,(char*) buffer,2*sizeof(T32));
			rcRecv(netClient,(char*) buffer,1*sizeof(T32));	// get response back
			
			if (buffer[0].integer == NET_ACK) {
				if (channels[i]->sendRemoteFrame(netClient) == FALSE){
					error(CODE_BUG,"Remote channel communication error.\n");
					
					CRemoteChannel *val;
					declaredRemoteChannels->erase(channels[i]->name,val);
					delete channels[i];
					channels[i] = NULL;
				}
			} else {
				error(CODE_BUG,"Client refused update for remote channel.\n");
				
				CRemoteChannel *val;
				declaredRemoteChannels->erase(channels[i]->name,val);
				delete channels[i];
				channels[i] = NULL;
			}
		}
	}
	buffer[0].integer = NET_NACK;
	rcSend(netClient,(char*) buffer,2*sizeof(T32));
	rcRecv(netClient,(char*) buffer,1*sizeof(T32));	// get response back
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	recvFrameDataChannels
// Description			:	Recieve all frame-data channels
// Return Value			:
// Comments				:	Each channel update is preceeded by identified
//							which was assigned when creating it
void CRenderer::recvFrameDataChannels(SOCKET s) {
	long			numKnownChannels	= remoteChannels->numItems;
	CRemoteChannel	**channels			= remoteChannels->array;
	T32				buffer[2];
	int				remoteId;
	
	while(TRUE) {
		// receive update request - buffer[0] tells us
		// if there are any pending updates
		rcRecv(s,(char*) buffer,2*sizeof(T32));
		
		if(buffer[0].integer == NET_ACK) {
			// if we have updates then figure out what channel index
			remoteId = buffer[1].integer;
			
			if ((remoteId>=0) && (remoteId<numKnownChannels) && (channels[remoteId]!=NULL)){
				// Accept the update
				buffer[0].integer = NET_ACK;
				rcSend(s,(char*) buffer,1*sizeof(T32));
				// Perform it
				if (channels[remoteId]->recvRemoteFrame(s) == FALSE) {
					error(CODE_BUG,"Remote channel communication error.\n");
				}
			} else {
				error(CODE_BUG,"Update received for unkown remote channel.\n");
				buffer[0].integer = NET_NACK;
				rcSend(s,(char*) buffer,1*sizeof(T32));
			}
		} else {
			// No pending updates - we are done
			break;
		}
	}	
	buffer[0].integer = NET_ACK;
	rcSend(s,(char*) buffer,1*sizeof(T32));
}




///////////////////////////////////////////////////////////////////////
// Class				:	CRemoteTSMChannel
// Method				:	ctor
// Description			:	-
// Comments				:	The file is opened elsewhere and closed elsewhere
CRemoteTSMChannel::CRemoteTSMChannel(const char *name,FILE *f,int *idx,int xb,int yb) : CRemoteChannel(name,REMOTECHANNEL_PERBUCKET,CHANNELTYPE_TSM) {
	tsmFile = f;
	index = idx;
	lastPosition = ftell(f);
	xBuckets = xb;
	yBuckets = yb;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRemoteTSMChannel
// Method				:	sendRemoteBucket
// Description			:	send a buckets worth of tsm data
// Return Value			:	success or failure
// Comments				:	
int		CRemoteTSMChannel::sendRemoteBucket(SOCKET s,int x,int y) {
	// record current position, seek back to tile start
	long curPos = ftell(tsmFile);
	fseek(tsmFile,lastPosition,SEEK_SET);
	long sz = curPos - lastPosition;
	rcSend(s,(char*) &sz,sizeof(long));
	
	// send the tile data
	char buf[BUFFER_LENGTH];
	while(sz > 0){
		int nn = (sz>(BUFFER_LENGTH)) ? (BUFFER_LENGTH) : sz;
		fread(buf,nn,1,tsmFile);
		rcSend(s,buf,nn,FALSE);
		sz -= nn;
	}
	long newPos = ftell(tsmFile);
	if(newPos != curPos) {
		fseek(tsmFile,curPos,SEEK_SET);
		error(CODE_BUG,"Error reading tsm file.\n");
	}
	lastPosition = curPos;
	
	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRemoteTSMChannel
// Method				:	recvRemoteBucket
// Description			:	receive a buckets worth of tsm data
// Return Value			:	success or failure
// Comments				:	
int		CRemoteTSMChannel::recvRemoteBucket(SOCKET s,int x,int y) {
	// record where we are
	long prevPos = ftell(tsmFile);
	
	// recieve data
	long sz;
	rcRecv(s,(char*)&sz,sizeof(long));
	char buf[BUFFER_LENGTH];
	while(sz > 0){
		int nn = (sz>(BUFFER_LENGTH)) ? (BUFFER_LENGTH) : sz;
		rcRecv(s,buf,nn,FALSE);
		fwrite(buf,nn,1,tsmFile);
		sz -= nn;
	}
	
	// record the bucket start and bucket index
	long newPos = ftell(tsmFile);
	index[y*xBuckets +x] = prevPos;
	index[y*xBuckets +x + xBuckets*yBuckets] = newPos-prevPos;
	
	return TRUE;
}




///////////////////////////////////////////////////////////////////////
// Class				:	CRemoteTSMChannel
// Method				:	ctor
// Description			:	-
// Comments				:	The cache is opened elsewhere and closed elsewhere
CRemoteICacheChannel::CRemoteICacheChannel(CIrradianceCache *c) : CRemoteChannel(c->name,REMOTECHANNEL_PERFRAME,CHANNELTYPE_ICACHE) {
	cache = c;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRemoteICacheChannel
// Method				:	sendRemoteBucket
// Description			:	send all the cache's data
// Return Value			:	success or failure
// Comments				:	
int		CRemoteICacheChannel::sendRemoteFrame(SOCKET s) {
	CIrradianceCache::CCacheNode			**stackBase;
	CIrradianceCache::CCacheNode			**stack;
	CIrradianceCache::CCacheNode			*cNode;
	CIrradianceCache::CCacheSample			*cSample;
	int i,numSamples;
	
	stackBase		=	(CIrradianceCache::CCacheNode **)
							alloca(cache->maxDepth*sizeof(CIrradianceCache::CCacheNode *)*8);
	
	stack		=	stackBase;
	*stack++	=	cache->root;
	while(stack > stackBase) {
		cNode	=	*(--stack);

		// Send the values in this level (if any)
		for (numSamples=0,cSample=cNode->samples;cSample!=NULL;cSample=cSample->next)
			numSamples++;
		
		if (numSamples != 0) {
			rcSend(s,(char*) &numSamples,sizeof(int),FALSE);
			
			for (cSample=cNode->samples;cSample!=NULL;cSample=cSample->next) {
				rcSend(s,(char*) cSample,sizeof(CIrradianceCache::CCacheSample),FALSE);
			}
		}
		
		// Send the children
		for (i=0;i<8;i++) {
			CIrradianceCache::CCacheNode	*tNode;

			if ((tNode = cNode->children[i]) != NULL) {
				*stack++	=	tNode;
			}
		}
	}
	
	numSamples = 0;
	rcSend(s,(char*) &numSamples,sizeof(int),FALSE);
	
	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRemoteICacheChannel
// Method				:	recvRemoteBucket
// Description			:	receive all the server's cache data
// Return Value			:	success or failure
// Comments				:	
int		CRemoteICacheChannel::recvRemoteFrame(SOCKET s) {
	CIrradianceCache::CCacheNode			*cNode;
	CIrradianceCache::CCacheSample			*cSample;
	CIrradianceCache::CCacheSample			*sampleMem;
	int		i,j,t,numSamples,depth;
	float	rMean,P[3];

	rcRecv(s,(char*) &numSamples,sizeof(int),FALSE);
	
	while (numSamples > 0) {
		sampleMem = (CIrradianceCache::CCacheSample *)
					cache->memory->alloc(numSamples * sizeof(CIrradianceCache::CCacheSample));
		
		rcRecv(s,(char*) sampleMem,numSamples * sizeof(CIrradianceCache::CCacheSample),FALSE);
		for (t=0,cSample=sampleMem;t<numSamples;cSample++,t++) {
			cSample->next =  NULL;
		}
		
		for (t=0,cSample=sampleMem;t<numSamples;cSample++,t++) {
			rMean				=	cSample->dP;	// error adjustment!!
			movvv(P,cSample->P);
			
			cNode				=	cache->root;
			depth				=	0;
			while(cNode->side > (2*rMean)) {
				depth++;
		
				for (j=0,i=0;i<3;i++) {
					if (P[i] > cNode->center[i]) {
						j			|=	1 << i;
					}
				}
		
				if (cNode->children[j] == NULL)	{
					CIrradianceCache::CCacheNode	*nNode	=	(CIrradianceCache::CCacheNode *) 
																cache->memory->alloc(sizeof(CIrradianceCache::CCacheNode));
		
					for (i=0;i<3;i++) {
						if (P[i] > cNode->center[i]) {
							nNode->center[i]	=	cNode->center[i] + cNode->side / (float) 4;
						} else {
							nNode->center[i]	=	cNode->center[i] - cNode->side / (float) 4;
						}
					}
		
					cNode->children[j]	=	nNode;
					nNode->side			=	cNode->side*0.5f;
					nNode->samples		=	NULL;
					for (i=0;i<8;i++)	nNode->children[i]	=	NULL;
				}
		
				cNode			=	cNode->children[j];
			}
		
			// GSHTODO filter thru samples and discard this one iff within eps of another
			
			cSample->next		=	cNode->samples;
			cNode->samples		=	cSample;
			cache->maxDepth		=	max(depth,cache->maxDepth);
		}
		
		rcRecv(s,(char*) &numSamples,sizeof(int),FALSE);
	}
	
	return TRUE;
}

// Help us set up the client cache (it's worldBound will be wrong)
int	CRemoteICacheChannel::sendSetupData(SOCKET s) {
	rcSend(s,(char*) &cache->root->center,sizeof(vector),FALSE);
	rcSend(s,(char*) &cache->root->side,sizeof(float),FALSE);
	
	return TRUE;
}

int	CRemoteICacheChannel::setup(SOCKET s) {
	rcRecv(s,(char*) &cache->root->center,sizeof(vector),FALSE);
	rcRecv(s,(char*) &cache->root->side,sizeof(float),FALSE);
	
	return TRUE;
}




///////////////////////////////////////////////////////////////////////
// Class				:	CRemotePtCloudChannel
// Method				:	ctor
// Description			:	-
// Comments				:	The cache is opened elsewhere and closed elsewhere
CRemotePtCloudChannel::CRemotePtCloudChannel(CPointCloud *c) : CRemoteChannel(c->name,REMOTECHANNEL_PERFRAME,CHANNELTYPE_PTCLOUD) {
	cloud = c;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRemoteICacheChannel
// Method				:	sendRemoteBucket
// Description			:	send all the cache's data
// Return Value			:	success or failure
// Comments				:	
int		CRemotePtCloudChannel::sendRemoteFrame(SOCKET s) {
	int i,numSamples;

	// Send the points
	
	numSamples = cloud->numPhotons-1;
	rcSend(s,(char*) &numSamples,sizeof(int),FALSE);
	
	float **dataPointers = cloud->dataPointers->array;
	
	for (i=1;i<cloud->numPhotons;i++) {
		CPointCloudPoint *pt = cloud->photons + i;
		rcSend(s,(char*) pt,sizeof(CPointCloudPoint),FALSE);
		rcSend(s,(char*) dataPointers[pt->entryNumber],sizeof(float)*cloud->dataSize,FALSE);
	}
		
	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRemoteICacheChannel
// Method				:	recvRemoteBucket
// Description			:	receive all the server's cache data
// Return Value			:	success or failure
// Comments				:	
int		CRemotePtCloudChannel::recvRemoteFrame(SOCKET s) {
	int					i,numSamples;
	CPointCloudPoint	pt;
	float				*data = new float[cloud->dataSize];

	// recive the points
	
	rcRecv(s,(char*) &numSamples,sizeof(int),FALSE);
	
	for (i=0;i<numSamples;i++) {
		rcRecv(s,(char*) &pt,sizeof(CPointCloudPoint),FALSE);
		rcRecv(s,(char*) data,sizeof(float)*cloud->dataSize,FALSE);
		cloud->store(data,pt.P,pt.N,pt.dP);
	}
	
	delete[] data;
	
	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRemotePtCloudChannel
// Method				:	sendSetupData
// Description			:	sendSetupData
// Return Value			:	success or failure
// Comments				:	
int		CRemotePtCloudChannel::sendSetupData(SOCKET s) {
	char	channelDef[1024];
	char	*ptr = channelDef;
	
	// encode the channel (tidy this up)
	channelDef[0]	= '\0';
	int		i		= cloud->numChannels;
	while (i<(cloud->numChannels-1)) {
		sprintf(ptr,"%s,",cloud->channels[i].name);
		ptr += strlen(cloud->channels[i].name)-1;
	}
	sprintf(ptr,"%s",cloud->channels[cloud->numChannels-1].name);
	
	rcSend(s,channelDef,1024,FALSE);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRemotePtCloudChannel
// Method				:	setup
// Description			:	setup
// Return Value			:	success or failure
// Comments				:	
int	CRemotePtCloudChannel::setup(SOCKET s) {
	char	channelDef[1024];
	
	// get the channels
	rcRecv(s,channelDef,1024,FALSE);
	cloud->defineChannels(channelDef);
	
	identitym(cloud->to);
	identitym(cloud->from);
	
	// set the scale to 1
	
	cloud->dPscale = 1;
	
	return TRUE;
}

