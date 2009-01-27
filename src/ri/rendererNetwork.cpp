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
//  File				:	rendererNetwork.cpp
//  Classes				:	CRenderer
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include <string.h>
#include <math.h>

#include "renderer.h"
#include "error.h"
#include "stats.h"
#include "memory.h"
#include "netFileMapping.h"
#include "ri_config.h"

///////////////////////////////////////////////////////////////////////
// Function				:	rcRecv
// Description			:	Receive data from network
// Return Value			:
// Comments				:
void			CRenderer::initNetwork(const char *ribFile,const char *riNetString) {

	// Clear some data
	netClient						=	INVALID_SOCKET;
	netNumServers					=	0;
	netServers						=	NULL;
	netFileMappings					=	NULL;

	// Network init
	netSetup(ribFile,riNetString);
	
	if (netClient != INVALID_SOCKET) {
		netFileMappings = new CTrie<CNetFileMapping*>;
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	rcRecv
// Description			:	Receive data from network
// Return Value			:
// Comments				:
void			CRenderer::shutdownNetwork() {
	if (netClient != INVALID_SOCKET) {

		assert(netFileMappings != NULL);

		netFileMappings->destroy();
		closesocket(netClient);
	}

	if (netNumServers != 0) {
		int	i;

		for (i=0;i<netNumServers;i++) {
			closesocket(netServers[i]);
		}

		delete [] netServers;
	}
}


///////////////////////////////////////////////////////////////////////
// Function				:	rcSend
// Description			:	Send data on the network
// Return Value			:
// Comments				:
void		rcSend(SOCKET s,const void *dataToSend,int n,int toNetwork) {
	int	i,j;

	if (toNetwork) {
		T32	*buf	=	(T32 *) dataToSend;

		for (i=n>>2;i>0;i--,buf++) {
			buf->integer	=	htonl(buf->integer);
		}
	}

	const char	*data	=	(const char *) dataToSend;

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
void		rcRecv(SOCKET s,void *dataToReceive,int n,int toNetwork) {
	int		i,j;
	char	*data	=	(char *) dataToReceive;

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
		T32		*buf	=	 (T32 *) dataToReceive;

		for (i=n>>2;i>0;i--,buf++) {
			buf->integer	=	ntohl(buf->integer);
		}
	}

	stats.totalNetRecv	+=	n;
}






///////////////////////////////////////////////////////////////////////
// Function				:	netName
// Description			:	Lookup the name of a socket and return it's address
// Return Value			:	TRUE on success, FALSE otherwise
// Comments				:
static	int		netName(sockaddr_in *address,const char *orgName) {
	int					port;
	struct	hostent		*hp			=	NULL;
	char				*portMarker;
	char				name[256];

	// Make a local copy of the name
	if (orgName == NULL)	gethostname(name,256);
	else					strcpy(name,orgName);

	portMarker						=	strchr(name,':');

	// Try to read off the port
	if (portMarker == NULL)	port	=	DEFAULT_SERVER_PORT;
	else {
		if (sscanf(portMarker,":%d",&port) != 1) {
			port	=	DEFAULT_SERVER_PORT;
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

#ifdef _WINDOWS
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
#define	netError() error(CODE_SYSTEM,"NET ERROR: %s\n",strerror(errno));
#endif

///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	sendFile
// Description			:	Send a file over the network to the server
// Return Value			:
// Comments				:
void				CRenderer::sendFile(int index,char *fileToSend,int start,int size) {
	FILE	*in	=	fopen(fileToSend,"rb");

	if (in != NULL) {
		char	buffer[NETWORK_BUFFER_LENGTH];
		int		csize;
		T32		netBuffer[1];

		// Tell the server that we found the file
		netBuffer[0].integer	=	NET_ACK;
		rcSend(netServers[index],netBuffer,sizeof(T32));

		// Get the size of the file to send
		if (size == 0) {
			int	totalSize;
			
			fseek(in,0,SEEK_END);
			totalSize	=	ftell(in);

			size		=	totalSize - start;
		}

		// Tell the server the length of the file
		netBuffer[0].integer	=	size;
		rcSend(netServers[index],netBuffer,sizeof(T32));

		// Transfer the file
		fseek(in,start,SEEK_SET);
		for (csize=size;csize>0;csize-=NETWORK_BUFFER_LENGTH) {
			fread(buffer,min(csize,NETWORK_BUFFER_LENGTH),sizeof(char),in);
			rcSend(netServers[index],buffer,min(csize,NETWORK_BUFFER_LENGTH),FALSE);
		}

		fclose(in);
	} else {
		T32		netBuffer[1];

		// File could not be found
		netBuffer[0].integer	=	NET_NACK;
		rcSend(netServers[index],netBuffer,sizeof(T32));
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	sfGetFile
// Description			:	Get a portion of a file
// Return Value			:	The size received
// Comments				:
int			CRenderer::getFile(FILE *file,const char *inName,int start,int size) {
	T32		*buffer;
	int		i			=	(int) strlen(inName);
	int		r;

	// Compute the file name length
	i					=	(i / sizeof(T32))+2;

	// Allocate tmp space
	buffer				=	(T32 *) alloca((i+4)*sizeof(T32));

	buffer[0].integer	=	NET_SEND_FILE;
	buffer[1].integer	=	start;
	buffer[2].integer	=	size;
	buffer[3].integer	=	i*sizeof(T32);

	// Send the file request
	rcSend(netClient,buffer,4*sizeof(T32));

	// Send the file name
	strcpy(&buffer[0].character,inName);
	rcSend(netClient,buffer,i*sizeof(T32),FALSE);

	rcRecv(netClient,buffer,1*sizeof(T32));
	if (buffer->integer == NET_NACK) {
		r	=	0;
	} else {
		int		tsize,csize;
		char	buf[NETWORK_BUFFER_LENGTH];

		// Get the size of the file first
		rcRecv(netClient,&tsize,sizeof(int));

		// Write down the file
		for (csize=tsize;csize>0;csize-=NETWORK_BUFFER_LENGTH) {
			rcRecv(netClient,buf,min(NETWORK_BUFFER_LENGTH,csize),FALSE);
			fwrite(buf,min(NETWORK_BUFFER_LENGTH,csize),sizeof(char),file);
		}

		r	=	tsize;
	}

	return r;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	getFile
// Description			:	Receive a file over the network from the client
// Return Value			:
// Comments				:
int			CRenderer::getFile(char *outName,const char *inName) {
	FILE	*out;
	int		result	=	FALSE;

	if (!osFileExists(temporaryPath)) {
		osCreateDir(temporaryPath);
	}

	osTempname(temporaryPath,"rndr",outName);
	CNetFileMapping *mapping = new CNetFileMapping(inName,outName);
	netFileMappings->insert(mapping->from,mapping);

	out	=	fopen(outName,"wb");

	if (out != NULL) {
		if (getFile(out,inName) > 0) {
			result	=	TRUE;
		} else {
			error(CODE_SYSTEM,"Failed to download file %s\n",inName);
		}

		fclose(out);
	} else {
		error(CODE_SYSTEM,"Failed to create file %s\n",outName);
	}

	return result;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	netSetup
// Description			:	Setup the network connections
// Return Value			:
// Comments				:
void		CRenderer::netSetup(const char *ribFile,const char *riNetString) {
	sockaddr_in	me;
	SOCKET		control;

	netClient			=	INVALID_SOCKET;
	netNumServers		=	0;
	netServers			=	NULL;

	if (riNetString == NULL)	return;

	char	*tmp		=	(char *) alloca(strlen(riNetString)+1);
	strcpy(tmp,riNetString);

#ifdef _WINDOWS
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
		rcRecv(netClient,netBuffer,4*sizeof(T32));

		// Check the message
		if (netBuffer[0].integer != NET_CONNECT) {
			fatal(CODE_SYSTEM,"Unrecognized startup sequence from the client\n");
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
		rcSend(netClient,netBuffer,sizeof(T32));
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
		char		*tmpStart	=	tmp;

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
		tmp					=	tmpStart+tmpOffset;
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
					send(control,ribFile,(int) strlen(ribFile)+1,0);	// Send the name of the rib file
					recv(control,(char *) netBuffer,sizeof(T32),0);		// Expect an ACK

					// Try to establist the connection
					netBuffer[0].integer	=	NET_CONNECT;
					netBuffer[1].integer	=	VERSION_RELEASE;
					netBuffer[2].integer	=	VERSION_BETA;
					netBuffer[3].integer	=	VERSION_ALPHA;
					rcSend(control,netBuffer,4*sizeof(T32));	// Send the client version
					rcRecv(control,netBuffer,1*sizeof(T32));	// Expect an ACK

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
					error(CODE_SYSTEM,"Failed to connect to %s\n",tmp);
				}
			} else {
				netError();
				error(CODE_SYSTEM,"Failed to resolve %s\n",tmp);
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
				send(control,ribFile,(int) strlen(ribFile)+1,0);	// Send the name of the rib file
				recv(control,(char *) netBuffer,sizeof(T32),0);		// Expect an ACK

				// Try to establist the connection
				netBuffer[0].integer	=	NET_CONNECT;
				netBuffer[1].integer	=	VERSION_RELEASE;
				netBuffer[2].integer	=	VERSION_BETA;
				netBuffer[3].integer	=	VERSION_ALPHA;
				rcSend(control,netBuffer,4*sizeof(T32));	// Send the client version
				rcRecv(control,netBuffer,1*sizeof(T32));	// Expect an ACK

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
				error(CODE_SYSTEM,"Failed to connect to %s\n",tmp);
			}
		} else {
			netError();
			error(CODE_SYSTEM,"Failed to resolve %s\n",tmp);
		}
	} else if (strncmp(tmp,"locclient=",10) == 0) {
		tmp += 10;
		
		// Note that we do not check the client version (it's the same binary)
		
		// Just read the client port number
		sscanf(tmp,"%d",&netClient);
	} else if (strncmp(tmp,"locservers=",11) == 0) {
		char		*marker;
		char		*tmpStarts	=	tmp;
		
		tmp += 11;
		
		// Note that we do not check the server versions
		
		// Count up the servers
		while((marker = strchr(tmp,',')) != NULL) {
			netNumServers++;
			tmp	=	marker+1;
		}
		netNumServers++;
		tmp		=	tmpStarts+11;
		
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

