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
//  File				:	rndr.cpp
//  Classes				:	-
//  Description			:	rib parser
//
////////////////////////////////////////////////////////////////////////
#include <stdlib.h>

#include "common/global.h"
#include "common/os.h"
#include "common/containers.h"
#include "ri/ri.h"


#ifdef WIN32
#include <process.h>
#else
#include <sys/select.h>
#include <netinet/tcp.h>
#include <signal.h>
#endif

#define	BUFFERSIZE			1024
#define DEFAULT_PORT		24666
#define	MAX_LOCALSERVERS	8

// Whether non win32 implementations should exec after fork
// win32 doesn't have / use fork anyway

#define USE_PURE_FORK		0

// Prototype for main
		int		main(int argc, char* argv[]);
static	int		gargc;
static	char	**gargv;
static	int		deamon;
static	int		silent;
static	int		noRestart;
static	SOCKET	listenSock;
static	int		numLocalServers;
static	SOCKET	localServerSockets[MAX_LOCALSERVERS];


// Stats signal handling
extern "C" {
	void printStatsHandler(int);
}


///////////////////////////////////////////////////////////////////////
// Function				:	exitFunction
// Description			:	This function is called before exitting so that if
//							we're running a server, it can spawn another one
// Return Value			:	-
// Comments				:
// Date last edited		:	12/01/2001
void	exitFunction() {
	if (deamon == TRUE) {
		// Close socket before respawning
		closesocket(listenSock);

		if (noRestart == FALSE) {
			char	**argv	=	new char*[gargc+2];
			int		i;


			for (i=0;i<gargc;i++) {
				argv[i]	=	gargv[i];
			}
			argv[i++]	=	"-silent";
			argv[i]		=	NULL;
			
			// use execvp to search PATH, incase pixie
			// isn't on the default search path
#ifdef WIN32
			_execvp(argv[0],argv);
#else
			execvp(argv[0],argv);
#endif
			delete [] argv;
		}
	} else if (numLocalServers > 0) {
		// we have open local sockets, close them
		int i = closesocket(listenSock);
		for (int j=0;j<numLocalServers;j++) {
			i = closesocket(localServerSockets[j]);
		}
		// we may wish to kill subprocesses here
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	printUsage
// Description			:	Print the stinking usage
// Return Value			:	-
// Comments				:
// Date last edited		:	12/01/2001
void	printUsage() {
	fprintf(stdout,"PIXIE v%d.%d.%d\n",VERSION_RELEASE,VERSION_BETA,VERSION_ALPHA);

	fprintf(stdout,"Command-line options:\n");
	fprintf(stdout,"  -f <range>: Render only a subsequence of frames\n");
	fprintf(stdout,"               -f 43     = Render only 43'rd frame\n");
	fprintf(stdout,"               -f 5:15   = Render frames 5 thru 15\n");
	fprintf(stdout,"               -f 5:2:15 = Render frames 5 thru 15 skipping every other one\n");
	fprintf(stdout,"  -q        : Quiet mode (errors/warning ignored)\n");
	fprintf(stdout,"  -d        : Ignore the display drivers and use framebuffer\n");
	fprintf(stdout,"  -t        : Print renderer statistics after every frame\n");
	fprintf(stdout,"  -p        : Display the progress\n\n");


	fprintf(stdout,"To render a RIB file:\n");
	fprintf(stdout,"       rndr <rib_file>\n\n");

	fprintf(stdout,"To start a multiprocessor render:\n");
	fprintf(stdout,"       rndr -P:<n> <rib_file>\n");

	fprintf(stdout,"To start a net rendering deamon:\n");
	fprintf(stdout,"       rndr -r <port>\n");
	fprintf(stdout,"       *** WARNING: The deamon will restart itself after each frame\n\n");

	fprintf(stdout,"To kill a net rendering deamon:\n");
	fprintf(stdout,"       rndr -k <port>\n\n");

	fprintf(stdout,"To render a RIB file on network:\n");
	fprintf(stdout,"       rndr <rib_file> -s <server1:port1,server2:port2...>\n\n");


}


///////////////////////////////////////////////////////////////////////
// Function				:	riThread
// Description			:	The main rendering thread
// Return Value			:
// Comments				:
// Date last edited		:	11/28/2001
void	riThread(void *w) {
	T32		*buffer	=	(T32 *) w;
	char	managerString[1024];
	T32		a;
	
	a.integer	=	0;
	send((SOCKET) buffer[0].integer,(char *) &a,sizeof(T32),0);
	
	sprintf(managerString,"#rib:%s net:client=%d",(char *) &buffer[1].character,buffer[0].integer);
	
	// I may want to do this in a seperate process
	RiBegin(managerString);
	
#ifndef WIN32
	signal(SIGHUP,printStatsHandler);
#ifdef SIGINFO
	signal(SIGINFO,printStatsHandler);
#endif
#endif

	
	RiReadArchive((char *) &buffer[1].character,NULL,NULL);
	RiEnd();
}



///////////////////////////////////////////////////////////////////////
// Function				:	rndrc
// Description			:	run as a local server and connect to client
// Return Value			:	-
// Comments				:	Servers connect back to client to avoid race
// Date last edited		:	02/23/2006
void	rndrc(char *ribFile,int port) {
	char		managerString[1024];
	SOCKET		sock;
	struct		sockaddr_in	client;
	
#ifdef WIN32
	WSADATA wsaData;

	// Init the winsock
	if (WSAStartup(0x202,&wsaData) == SOCKET_ERROR) {
		WSACleanup();
		if (silent == FALSE)	fprintf(stderr,"Winsock init error\n");
		return;
	}
#else
	// For platforms where we can't disable sigpipe per socket, do it globally
	#ifndef SO_NOSIGPIPE
		signal(SIGPIPE,SIG_IGN);
	#endif
#endif

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		if (silent == FALSE)	fprintf(stderr,"Socket error\n");
		return;
	}
	
	// Ensure there's no delay on network transactions
	int val = 1;
	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(const char *) &val,sizeof(int));
	val = 1;
	setsockopt(sock,IPPROTO_TCP,TCP_NODELAY,(const char *) &val,sizeof(int));

	// connect to server
	
	client.sin_family		= AF_INET;
	client.sin_addr.s_addr	= htonl(INADDR_ANY);
	client.sin_port			= htons(port);
	
	if (connect(sock, (struct sockaddr *) &client, sizeof(client)) < 0) {
		if (silent == FALSE)	fprintf(stderr,"Connection error\n");
		closesocket(sock);
		return;
	}
	
	// Run the rib
	
	sprintf(managerString,"#rib:%s net:locclient=%d",ribFile,sock);
	
	RiBegin(managerString);
	
#ifndef WIN32
	signal(SIGHUP,printStatsHandler);
#ifdef SIGINFO
	signal(SIGINFO,printStatsHandler);
#endif
#endif

	RiReadArchive(ribFile,NULL,NULL);
	RiEnd();
}

///////////////////////////////////////////////////////////////////////
// Function				:	runLocalServers
// Description			:	Run a set of subprocess and pre-accept connects
// Return Value			:	-
// Comments				:	the accepted sockets are handed back in managerString
// Date last edited		:	02/23/2006
int	runLocalServers(int numChildren,char *ribFile,char *managerString) {
	SOCKET		sock;
	struct		sockaddr_in	me;
	int			listenPort;
	char		*tmp = managerString + strlen(managerString);
	int			i,j;

#ifdef WIN32
	WSADATA wsaData;

	// Init the winsock
	if (WSAStartup(0x202,&wsaData) == SOCKET_ERROR) {
		WSACleanup();
		if (silent == FALSE)	fprintf(stderr,"Winsock init error\n");
		return FALSE;
	}
#else
	// For platforms where we can't disable sigpipe per socket, do it globally
	#ifndef SO_NOSIGPIPE
		signal(SIGPIPE,SIG_IGN);
	#endif
#endif

	// Create the socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		if (silent == FALSE)	fprintf(stderr,"Socket error\n");
		return FALSE;
	}

	// Ensure there's no delay on network transactions
	int val = 1;
	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(const char *) &val,sizeof(int));
	val = 1;
	setsockopt(sock,IPPROTO_TCP,TCP_NODELAY,(const char *) &val,sizeof(int));

	// Bind to a port (let the os decide which)
	me.sin_family		= AF_INET;
	me.sin_addr.s_addr	= htonl(INADDR_ANY);
	me.sin_port			= htons(0);
	if (bind(sock, (struct sockaddr *) &me, sizeof(me)) < 0) {
		if (silent == FALSE)	fprintf(stderr,"Bind error\n");
		j	=	closesocket(sock);
		return FALSE;
	}

	 // work out which port we bound to
    socklen_t namelen = sizeof(me);
    if (getsockname(sock,(struct sockaddr *) &me,&namelen) < 0) {
        fprintf(stderr,"Could not determine port for bound socket\n");
        j   =   closesocket(sock);
        return FALSE;
    }
    listenPort = ntohs(me.sin_port);

	
	// Save socket so we can close it on fatal errors
	listenSock = sock;
	
	// Listen to incoming connections
	if (listen(sock,SOMAXCONN) < 0) {
		if (silent == FALSE)	fprintf(stderr,"Socket error\n");
		j	=	closesocket(sock);
		return FALSE;
	}	
	
	// fork or launch the children
	{
		char	*argv[6];
		char	portbuf[20];
		
		// prepare the args for child process
		sprintf(portbuf,"%d",listenPort);

		argv[0]	=	gargv[0];
		argv[1]	=	"-silent";
		argv[2]	=	"-c";
		argv[3]	=	portbuf;
		argv[4]	=	ribFile;
		argv[5]	=	NULL;
		
		for(int k=0;k<numChildren;k++){
			#ifdef WIN32
				// use _spawnvp to search PATH, incase pixie
				// isn't on the default search path
				long pid = _spawnvp(_P_NOWAIT,argv[0],argv);
				if (pid <= 0) {
					if (silent == FALSE)	fprintf(stderr,"Subprocess launch failed\n");
					return FALSE;
				}
			#else
				long pid = fork();
				if (pid < 0) {
					// We failed to fork
					if (silent == FALSE)	fprintf(stderr,"Subprocess launch failed\n");
					return FALSE;
				} else if (pid == 0) {
					// We are now the child server
					#if USE_PURE_FORK
						// We can actually skip the exec alltogether
						// which is useful if true local sockets were used
						rndrc(ribFile,listenPort);
						exit(0);
					#else
						// use execvp to search PATH, incase pixie
						// isn't on the default search path
						execvp(argv[0],argv);
						exit(0);
					#endif
				}
			#endif
		}
	}
		
	// pre-accept the local servers
	
	sprintf(tmp,"locservers=");
	tmp += strlen(tmp);
	
	// accept the connections
	for(i=0;i<numChildren;i++) {
		SOCKET		peer;
		socklen_t	servLen	=	sizeof(sockaddr_in);
		sockaddr_in	serv;
		fd_set		fds;
		timeval		timeout;
		
		// implement a timeout for sockets (so we don't wait for ever for subprocesses)
		FD_ZERO(&fds);
		FD_SET(sock,&fds);
		timeout.tv_sec	= 4;
		timeout.tv_usec = 0;
		if ( select(sock+1,&fds,NULL,NULL,&timeout) <= 0) {
			if (silent == FALSE)	fprintf(stderr,"Timeout waiting for socket\n");
			j	=	closesocket(sock);
			return FALSE;
		}
		
		// finally if we didn't time out, accept the connection
		peer	=	accept(sock,(sockaddr *) &serv,&servLen);
		
		#ifdef SO_NOSIGPIPE
			val = 1;
			setsockopt(peer,SOL_SOCKET,SO_NOSIGPIPE,(const char *) &val,sizeof(int));
		#endif
			
		if (peer != INVALID_SOCKET) {
			// record peer socket
			localServerSockets[numLocalServers++] = peer;
			
			if (i < numChildren-1)	sprintf(tmp,"%d,",peer);
			else					sprintf(tmp,"%d",peer);
			tmp += strlen(tmp);
		} else {
			if (silent == FALSE)	fprintf(stderr,"Socket error\n");
			j	=	closesocket(sock);
			return FALSE;
		}
	}

	// Close socket before exiting
	j	=	closesocket(sock);
		
	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// Function				:	rndrd
// Description			:	Run the network deamon
// Return Value			:	-
// Comments				:
// Date last edited		:	12/01/2001
void	rndrd(int port) {
	SOCKET		sock;
	struct		sockaddr_in	me;
	T32			buffer[BUFFERSIZE];
	int			running	=	TRUE;

#ifdef WIN32
	WSADATA wsaData;

	// Init the winsock
	if (WSAStartup(0x202,&wsaData) == SOCKET_ERROR) {
		WSACleanup();
		if (silent == FALSE)	fprintf(stderr,"Winsock init error\n");
	}
#else
	// For platforms where we can't disable sigpipe per socket, do it globally
	#ifndef SO_NOSIGPIPE
		signal(SIGPIPE,SIG_IGN);
	#endif
#endif

	// Create the socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		if (silent == FALSE)	fprintf(stderr,"Socket error\n");
		return;
	}

	// Ensure there's no delay on network transactions
	int val = 1;
	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(const char *) &val,sizeof(int));
	val = 1;
	setsockopt(sock,IPPROTO_TCP,TCP_NODELAY,(const char *) &val,sizeof(int));

	// Bind to the port
	me.sin_family		= AF_INET;
	me.sin_addr.s_addr	= htonl(INADDR_ANY);
	me.sin_port			= htons(port);
	if (bind(sock, (struct sockaddr *) &me, sizeof(me)) < 0) {
		if (silent == FALSE)	fprintf(stderr,"Bind error\n");
		return;
	}

	// Display the information
	{
		char	hostName[128];
		hostent *hostinfo;

		if(gethostname(hostName,sizeof(hostName)) == 0) {
			if((hostinfo = gethostbyname(hostName)) != NULL) {
				if (silent == FALSE)	fprintf(stdout,"Active at %s:%d\n",inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list),ntohs(me.sin_port));
			}
		}
	}

	// We're running a deamon
	deamon	=	TRUE;

	// Save socket so we can close it on fatal errors
	listenSock = sock;
	
	// Listen to incoming connections
	listen(sock,SOMAXCONN);
	while(running == TRUE) {
		SOCKET		peer;
		socklen_t	servLen	=	sizeof(sockaddr_in);
		sockaddr_in	serv;
		
		peer	=	accept(sock,(sockaddr *) &serv,&servLen);
		
		if (peer != INVALID_SOCKET) {
	
			// If supported / needed, disable sigpipe (needs to be an connected socket)
			#ifdef SO_NOSIGPIPE
				val = 1;
				setsockopt(peer,SOL_SOCKET,SO_NOSIGPIPE,(const char *) &val,sizeof(int));
			#endif

			// Handle the message
			recv(peer,(char *) &buffer[1].character,(BUFFERSIZE-1)*sizeof(T32),0);
			if (strncmp((char *) &buffer[1].character," quit",5) == 0) {
				noRestart	=	TRUE;
				running		=	FALSE;
			} else {
				buffer[0].integer	=	peer;

				riThread((void *) buffer);
				
				running = TRUE;
			}
	
			// Close peer socket
			closesocket(peer);
		}
	}

	// Close socket before exiting
	closesocket(sock);
}



///////////////////////////////////////////////////////////////////////
// Function				:	main
// Description			:	The god
// Return Value			:	-
// Comments				:
// Date last edited		:	12/01/2001
int main(int argc, char* argv[]) {
	int				i;
	char			managerString[1024];
	char			managerString2[1024];
	int				server			=	FALSE;
	int				client			=	FALSE;
	int				localserver		=	FALSE;
	int				killservers		=	FALSE;
	char			*source			=	NULL;
	int				port			=	0;
	int				clientport		=	0;
	const	char	*frameRange		=	NULL;
	int				frameBufferOnly	=	FALSE;
	int				displayStats	=	FALSE;
	int				displayProgress	=	FALSE;
	int				localChildren	=	0;

	// Init the memory manager
	memInit();

	// Register the exit stuff
	sprintf(managerString,"");
	gargc				=	argc;
	gargv				=	argv;
	deamon				=	FALSE;
	silent				=	FALSE;
	numLocalServers		=	0;
	atexit(exitFunction);

	for (i=1;i<argc;i++) {
		if ((strcmp(argv[i],"-h") == 0) || (strcmp(argv[i],"--help") == 0) || (strcmp(argv[i],"-v") == 0)) {
			printUsage();
			exit(0);
		} else if (strcmp(argv[i],"-r") == 0) {
			i++;

			if ((i < argc) && (sscanf(argv[i],"%d",&port) == 1)) {
			} else {
				port	=	DEFAULT_PORT;
				i--;
			}
		} else if (strcmp(argv[i],"-q") == 0) {
			silent		=	TRUE;
		} else if (strcmp(argv[i],"-c") == 0) {
			client		=	TRUE;

			i++;
			if (i >= argc) {
				if (silent == FALSE)	fprintf(stderr,"Was expecting client port\n");
				exit(0);
			}
			
			if(sscanf(argv[i],"%d",&clientport) != 1) {
				if (silent == FALSE)	fprintf(stderr,"Unrecognized client port\n");
				exit(0);
			}
		} else if (strcmp(argv[i],"-s") == 0) {
			server	=	TRUE;

			i++;
			if (i >= argc) {
				if (silent == FALSE)	fprintf(stderr,"Was expecting list of servers\n");
				exit(0);
			}
			sprintf(managerString,"servers=%s",argv[i]);
		} else if (strcmp(argv[i],"-k") == 0) {
			server			=	TRUE;
			killservers		=	TRUE;
			
			i++;
			if (i >= argc) {
				if (silent == FALSE)	fprintf(stderr,"Was expecting list of servers\n");
				exit(0);
			}
			sprintf(managerString,"killservers=%s",argv[i]);
		} else if (strcmp(argv[i],"-f") == 0) {
			i++;
			if (i >= argc) {
				if (silent == FALSE)	fprintf(stderr,"Was expecting the frame range\n");
				exit(0);
			}

			frameRange	=	argv[i];
		} else if (strncmp(argv[i],"-P:",3) == 0) {
			localChildren	=	atoi(argv[i]+3);
			localserver		=	TRUE;

			if (localChildren > MAX_LOCALSERVERS) {
			
				if (silent == FALSE)	fprintf(stderr,"Cannot run more than %d local processes\n",MAX_LOCALSERVERS);
				localChildren = MAX_LOCALSERVERS;
			}
		} else if (strcmp(argv[i],"-d") == 0) {
			frameBufferOnly	=	TRUE;
		} else if (strcmp(argv[i],"-t") == 0) {
			displayStats	=	TRUE;
		} else if (strcmp(argv[i],"-p") == 0) {
			displayProgress	=	TRUE;
		} else {
			source	=	argv[i];
		}
	}
	
	// Validate option combinations
	if (client | server | localserver) {
		if ((client ^ server ^ localserver) == 0) {
			fprintf(stderr,"Invalid combination of client and server options\n");
			exit(0);
		}
	}

	// Launch into daemon mode if appropriate
	if (port != 0) {
		if ((localChildren != 0) | server) {
			fprintf(stderr,"You cannot launch a deamon with multiprocessor options\n");
			exit(0);
		}
		
		noRestart	=	FALSE;
		rndrd(port);
		exit(0);

	}
	
	// If no source, get the input from stdin
	if (source == NULL)	source	=	"-";

	// Deal with stdin renders
	if (strcmp(source,"-") == 0) {
		if ((client | server | localserver)  && (silent == FALSE) && (killservers != TRUE)) {
			fprintf(stderr,"You cannot use stdin for network / multiprocessor renders\n");
			exit(0);
		}
	}
	
	// Launch local servers if needed
	if (localChildren != 0) {
		noRestart	=	TRUE;
		
		// verify rib exists
		if (osFileExists(source) == FALSE) {
			if (silent == FALSE)	fprintf(stderr,"Cannot find rib file for subprocesses\n");
			exit(0);
		}
		
		// run teh servers
		if (runLocalServers(localChildren,source,managerString) == FALSE) {
			if (silent == FALSE)	fprintf(stderr,"Cannot launch multiprocessor subprocesses\n");
			exit(0);
		}
	}
	
	// Launch as spawned local server if needed
	if (clientport != 0) {
		rndrc(source,clientport);
		exit(0);
	}
	
	// Create the command line for the ri
	if (client | server | localserver) {
		sprintf(managerString2,"#rib:%s net:%s",source,managerString);
	} else {
		sprintf(managerString2,"#");
	}

	if (frameRange != NULL) {
		strcat(managerString2," frames:");
		strcat(managerString2,frameRange);
	}

	if (frameBufferOnly) {
		strcat(managerString2," fbonly:");
	}
	
	RiBegin(managerString2);
	
#ifndef WIN32
	signal(SIGHUP,printStatsHandler);
#ifdef SIGINFO
	signal(SIGINFO,printStatsHandler);
#endif
#endif
	
	if (silent			==	TRUE)	RiErrorHandler(RiErrorIgnore);
	if (displayStats	==	TRUE)	{
		RtInt	level		=	3;
		RiOption(RI_STATISTICS,RI_ENDOFFRAME,&level,RI_NULL);
	}

	if (displayProgress	==	TRUE)	{
		RtInt	progress	=	1;
		RiOption(RI_STATISTICS,RI_PROGRESS,&progress,RI_NULL);
	}

	if (!killservers) RiReadArchive(source,NULL,NULL);

	RiEnd();

	memShutdown();

	return (RiLastError != RIE_NOERROR) ? -1 : 0;
}


