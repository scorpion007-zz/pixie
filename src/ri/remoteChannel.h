//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright � 1999 - 2003, Okan Arikan
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
//  File				:	remoteChannel.h
//  Classes				:	
//  Description			:	This base class for remote deep data channels
//
////////////////////////////////////////////////////////////////////////
#ifndef REMOTECHANNEL_H
#define REMOTECHANNEL_H

#include "common/global.h"
#include "common/os.h"


// Forward declarations:
class CIrradianceCache;
class CPointCloud;

// Types and flags

typedef enum {
	REMOTECHANNEL_NONE,
	REMOTECHANNEL_PERFRAME,
	REMOTECHANNEL_PERBUCKET
} ERemoteChannelFlag;

typedef enum {
	CHANNELTYPE_INVALID	= -1,
	CHANNELTYPE_TSM		= 0,
	CHANNELTYPE_ICACHE	= 1,
	CHANNELTYPE_PTCLOUD	= 2,
	CHANNELTYPE_BOM		= 0x55000000			// byte-order marker
} ERemoteChannelType;

///////////////////////////////////////////////////////////////////////
// Class				:	CRemoteChannel
// Description			:	base class for remote channels
// Comments				:	
// Date last edited		:	03/13/06
class CRemoteChannel {
public:
					CRemoteChannel(const char *n,int f,int d) : name(strdup(n)), flags(f), channelType(d), remoteId(-1) { }
		virtual 	~CRemoteChannel() { free(name); };
		
		virtual		int		sendSetupData(SOCKET s)					{ return TRUE; }
		virtual		int		setup(SOCKET s)							{ return TRUE; }
		virtual		int		sendRemoteBucket(SOCKET s,int,int)		{ return TRUE; }
		virtual		int		recvRemoteBucket(SOCKET s,int,int)		{ return TRUE; }
		virtual		int		sendRemoteFrame(SOCKET s)				{ return TRUE; }
		virtual		int		recvRemoteFrame(SOCKET s)				{ return TRUE; }		

public:
	char	*name;
	int		flags;				// when should we be run?
	int		channelType;		// identify the derived type
	int		remoteId;			// the Id of the channel on the client
};

///////////////////////////////////////////////////////////////////////
// Class				:	CRemoteTSMChannel
// Description			:	remote channel for tsm
// Comments				:	
// Date last edited		:	03/13/06
class	CRemoteTSMChannel : public CRemoteChannel {
public:
	CRemoteTSMChannel(const char*,FILE*,int*,int,int);
	~CRemoteTSMChannel() { }
	
	int sendRemoteBucket(SOCKET s,int x,int y);
	int recvRemoteBucket(SOCKET s,int x,int y);

private:
	FILE	*tsmFile;
	int		*index;
	long	lastPosition;
	int		xBuckets,yBuckets;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CRemoteICacheChannel
// Description			:	remote channel for irradiance caches
// Comments				:	
// Date last edited		:	03/13/06
class	CRemoteICacheChannel : public CRemoteChannel {
public:
	CRemoteICacheChannel(CIrradianceCache *);
	~CRemoteICacheChannel() { }
	
	int	sendSetupData(SOCKET s);
	int	setup(SOCKET s);
	int sendRemoteFrame(SOCKET s);
	int recvRemoteFrame(SOCKET s);

private:
	CIrradianceCache	*cache;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CRemotePtCloudChannel
// Description			:	remote channel for point clouds
// Comments				:	
// Date last edited		:	03/13/06
class	CRemotePtCloudChannel : public CRemoteChannel {
public:
	CRemotePtCloudChannel(CPointCloud *);
	~CRemotePtCloudChannel() { }
	
	int	sendSetupData(SOCKET s);
	int	setup(SOCKET s);
	int sendRemoteFrame(SOCKET s);
	int recvRemoteFrame(SOCKET s);

private:
	CPointCloud	*cloud;
};

#endif
