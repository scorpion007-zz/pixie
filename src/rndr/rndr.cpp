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


#ifdef _WINDOWS
#include <process.h>
#else
#include <sys/select.h>
#include <netinet/tcp.h>
#include <signal.h>
#endif

#define	BUFFERSIZE			1024
#define DEFAULT_DAEMON_PORT	24666
#define	MAX_LOCALSERVERS	8

// Whether non Windows implementations should exec after fork
// Windows doesn't have / use fork anyway

#define USE_PURE_FORK		0

// Prototype for main
		int		main(int argc, char* argv[]);
static	int		gargc;
static	char	**gargv;
static	int		isDaemon;
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
void	exitFunction() {
	if (isDaemon == TRUE) {
		// Close socket before respawning
		closesocket(listenSock);

		if (noRestart == FALSE) {
			char		**argv	=	new char*[gargc+2];
			int			i;

			for (i=0;i<gargc;++i)	argv[i]	=	gargv[i];
			argv[i++]	=	(char *) "-q";
			argv[i]		=	NULL;
			
			// use execvp to search PATH, incase pixie
			// isn't on the default search path
#ifdef _WINDOWS
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
// Function				:	printVersion
// Description			:	Print the version
// Return Value			:	-
// Comments				:
void	printVersion() {
	printf("Pixie RenderMan Renderer (rndr) v%d.%d.%d\n",VERSION_RELEASE,VERSION_BETA,VERSION_ALPHA);
	printf("\nCopyright 1999-2008 Okan Arikan. http://renderpixie.com/\n");
	printf("Pixie is free software. There is NO warranty; not even for\n");
	printf("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n");
}

///////////////////////////////////////////////////////////////////////
// Function				:	printUsage
// Description			:	Print the stinking usage
// Return Value			:	-
// Comments				:
void	printUsage() {
	printf("Usage: rndr <options> file.rib [file.rib ...]\n");	
	printf("Listing several RIB files concatenates them before rendering.\n");	
	printf("\nOptions:\n");
	printf("  -f <range>      Render only a subsequence of frames\n");
	printf("                    -f 43     = Render only the 43rd frame\n");
	printf("                    -f 5:15   = Render frames 5 thru 15\n");
	printf("                    -f 5:2:15 = Render every second frame from 5 thru 15\n");
	printf("  -q              Quiet mode; errors and warnings are ignored\n");
	printf("  -d              Ignore the display drivers and use framebuffer\n");
	printf("  -t              Print renderer statistics after every frame\n");
	printf("  -p              Display rendering progress\n");
	printf("  -P:<n>          Render using <n> processes; default is using one process\n");
	printf("  -t:<n>          Render using <n> threads; default is one thread per CPU core\n");
	printf("  -r [port]       Start a network server. If given, use port <port>\n");
	printf("  -k <serverlist> Stop network servers in <serverlist>\n");
	printf("  -s <serverlist> Render on network servers in <serverlist>\n");
	printf("                  <serverlist> specified as <IP[:port],IP[:port],...>\n");
	printf("  -v              Display version information\n");
	printf("  -h              Display this help\n");
	printf("\nEnvironment variables:\n");
	printf("  PIXIEHOME       Pixie installation path\n");
	printf("  SHADERS         Shader search path\n");
}


///////////////////////////////////////////////////////////////////////
// Function				:	riThread
// Description			:	The main rendering thread
// Return Value			:
// Comments				:
void	riThread(void *w) {
	T32		*buffer	=	(T32 *) w;
	char	managerString[1024];
	T32		a;
	
	a.integer	=	0;
	send((SOCKET) buffer[0].integer,(char *) &a,sizeof(T32),0);
	
	sprintf(managerString,"#rib:%s net:client=%d",(char *) &buffer[1].character,buffer[0].integer);
	
	// I may want to do this in a seperate process
	RiBegin(managerString);
	
#ifndef _WINDOWS
	signal(SIGHUP,printStatsHandler);
#ifdef SIGINFO
	signal(SIGINFO,printStatsHandler);
#endif
#endif

	char *source	= strdup((char *) &buffer[1].character);
	char *pstart 	= source;
	char *pend;
	do {
		pend = strchr(pstart,':');
		if (pend)	*pend = '\0';
		RiReadArchive(pstart,NULL,NULL);
		pstart = pend + 1;
	} while(pend);
	free(source);
	RiEnd();
}



///////////////////////////////////////////////////////////////////////
// Function				:	rndrc
// Description			:	run as a local server and connect to client
// Return Value			:	-
// Comments				:	Servers connect back to client to avoid race
void	rndrc(char *ribFile,int port) {
	char		managerString[1024];
	SOCKET		sock;
	struct		sockaddr_in	client;
	
#ifdef _WINDOWS
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

	unsigned int	attemptAddress	=	INADDR_ANY;
	
	// Here we include robustness for Windows not allowing bind / connect to ANY
retryBind:

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
	client.sin_addr.s_addr	= htonl(attemptAddress);
	client.sin_port			= htons(port);
	
	if (connect(sock, (struct sockaddr *) &client, sizeof(client)) < 0) {
		// Retry with loopback
		if (attemptAddress != INADDR_LOOPBACK) {
			closesocket(sock);
			attemptAddress = INADDR_LOOPBACK;
			goto retryBind;
		}
		if (silent == FALSE)	fprintf(stderr,"Connection error\n");
		closesocket(sock);
		return;
	}
	
	// Run the rib
	
	sprintf(managerString,"#rib:%s net:locclient=%d",ribFile,sock);
	
	RiBegin(managerString);
	
#ifndef _WINDOWS
	signal(SIGHUP,printStatsHandler);
#ifdef SIGINFO
	signal(SIGINFO,printStatsHandler);
#endif
#endif

	char *source	= strdup(ribFile);
	char *pstart 	= source;
	char *pend;
	do {
		pend = strchr(pstart,':');
		if (pend)	*pend = '\0';
		RiReadArchive(pstart,NULL,NULL);
		pstart = pend + 1;
	} while(pend);
	free(source);
	RiEnd();
}

///////////////////////////////////////////////////////////////////////
// Function				:	runLocalServers
// Description			:	Run a set of subprocess and pre-accept connects
// Return Value			:	-
// Comments				:	the accepted sockets are handed back in managerString
int	runLocalServers(int numChildren,char *ribFile,char *managerString) {
	SOCKET		sock;
	struct		sockaddr_in	me;
	int			listenPort;
	char		*tmp = managerString + strlen(managerString);
	int			i,j;

#ifdef _WINDOWS
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
		char		portbuf[20];

		// prepare the args for child process
		sprintf(portbuf,"%d",listenPort);

		// The command line arguments
		char 		* const argv[]	=	{gargv[0],(char *) "-q",(char *) "-c",portbuf,ribFile,NULL};
		
		for(int k=0;k<numChildren;k++){
			#ifdef _WINDOWS
				// use _spawnvp to search PATH, incase pixie
				// isn't on the default search path
				intptr_t pid = _spawnvp(_P_NOWAIT,argv[0],argv);
				if (pid <= 0) {
					if (silent == FALSE)	fprintf(stderr,"Failed to launch subprocess\n");
					return FALSE;
				}
			#else
				long pid = fork();
				if (pid < 0) {
					// We failed to fork
					if (silent == FALSE)	fprintf(stderr,"Failed to launch subprocess\n");
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
		if ( select((int) sock+1,&fds,NULL,NULL,&timeout) <= 0) {
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
// Description			:	Run the network daemon
// Return Value			:	-
// Comments				:
void	rndrd(int port) {
	SOCKET		sock;
	struct		sockaddr_in	me;
	T32			buffer[BUFFERSIZE];
	int			running	=	TRUE;

#ifdef _WINDOWS
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
				if (silent == FALSE) {	printf("Active at %s:%d\n",inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list),ntohs(me.sin_port)); fflush(stdout); }
			}
		}
	}

	// We're running a daemon
	isDaemon	=	TRUE;

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
				buffer[0].integer	=	(int) peer;

				assert(sizeof(SOCKET) == sizeof(int));

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
	int				numThreads		=	-1;
	int				localChildren	=	0;
	
	// Enable memory leak detection/report
#ifdef _WINDOWS
#ifdef _DEBUG
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
#endif

	// Register the exit stuff
	sprintf(managerString,"");
	gargc				=	argc;
	gargv				=	argv;
	isDaemon			=	FALSE;
	silent				=	FALSE;
	numLocalServers		=	0;
	atexit(exitFunction);

	for (i=1;i<argc;i++) {
		if (strcmp(argv[i],"-h") == 0
			|| strcmp(argv[i],"-help") == 0
			|| strcmp(argv[i],"--help") == 0) {
			printUsage();
			if (source) free(source);
			exit(0);
		} else if (strcmp(argv[i],"-v") == 0
				   || strcmp(argv[i],"-version") == 0
				   || strcmp(argv[i],"--version") == 0) {
			printVersion();
			if (source) free(source);
			exit(0);
		} else if (strcmp(argv[i],"-r") == 0) {
			i++;

			if ((i < argc) && (sscanf(argv[i],"%d",&port) == 1)) {
			} else {
				port	=	DEFAULT_DAEMON_PORT;
				i--;
			}
		} else if (strcmp(argv[i],"-q") == 0) {
			silent		=	TRUE;
		} else if (strcmp(argv[i],"-c") == 0) {
			client		=	TRUE;

			i++;
			if (i >= argc) {
				if (silent == FALSE)	fprintf(stderr,"Was expecting client port\n");
				exit(1);
			}
			
			if(sscanf(argv[i],"%d",&clientport) != 1) {
				if (silent == FALSE)	fprintf(stderr,"Unrecognized client port\n");
				exit(1);
			}
		} else if (strcmp(argv[i],"-sizereport") == 0) {
			printf("Size Report:\n");
			printf("        sizeof(char): %d\n",sizeof(char));
			printf("       sizeof(short): %d\n",sizeof(short));
			printf("         sizeof(int): %d\n",sizeof(int));
			printf("        sizeof(long): %d\n",sizeof(long));
			printf("   sizeof(long long): %d\n",sizeof(long long));
			printf("      sizeof(void *): %d\n",sizeof(void *));
			printf("         sizeof(T32): %d\n",sizeof(T32));
			printf("         sizeof(T64): %d\n",sizeof(T64));
			printf("      sizeof(TMutex): %d\n",sizeof(TMutex));
			exit(0);
		} else if (strcmp(argv[i],"-s") == 0) {
			server	=	TRUE;

			i++;
			if (i >= argc) {
				if (silent == FALSE)	fprintf(stderr,"Was expecting list of servers\n");
				exit(1);
			}
			sprintf(managerString,"servers=%s",argv[i]);
		} else if (strcmp(argv[i],"-k") == 0) {
			server			=	TRUE;
			killservers		=	TRUE;
			
			i++;
			if (i >= argc) {
				if (silent == FALSE)	fprintf(stderr,"Was expecting list of servers\n");
				exit(1);
			}
			sprintf(managerString,"killservers=%s",argv[i]);
		} else if (strcmp(argv[i],"-f") == 0) {
			i++;
			if (i >= argc) {
				if (silent == FALSE)	fprintf(stderr,"Was expecting the frame range\n");
				exit(1);
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
		} else if (strncmp(argv[i],"-t:",3) == 0) {
			numThreads			=	atoi(argv[i]+3);
		} else if (strcmp(argv[i],"-t") == 0) {
			displayStats	=	TRUE;
		} else if (strcmp(argv[i],"-p") == 0) {
			displayProgress	=	TRUE;
		} else if (argv[i][0] == '-' && argv[i][1] != 0) {
			// Starts with '-' but not matched any option
			if (silent == FALSE)
				fprintf(stderr,"Unknown option '%s'\n", argv[i]);
		} else {
			// Create colon-separated list of source RIBs
			if (!source) {
				source = strdup(argv[i]);
			} else {
				char* tmp = (char*)malloc(strlen(source)+1+strlen(argv[i])+1);
				strcpy(tmp,source);
				strcat(tmp,":");
				strcat(tmp,argv[i]);
				free(source);
				source = tmp;
			}
		}
	}
	
	// Read from STDIN if no source given
	if (source == NULL)
		source = strdup("-");
	
	// Validate option combinations
	if ((client | server | localserver) && (client ^ server ^ localserver) == 0) {
		fprintf(stderr,"Invalid combination of client and server options\n");
		free(source);
		exit(1);
	}
	
	// FIXME: remove once multithreaded netrenders are working
	if ((client | server | localserver) && numThreads > 0) {
		fprintf(stderr,"Using threads is currently not possible for network or multiprocess renders; turning off threads.\n");
		numThreads = 0;
	}

	// Launch into daemon mode if appropriate
	if (port != 0) {
		if ((localChildren != 0) | server) {
			fprintf(stderr,"Using multiple processes is not possible for network renders\n");
			free(source);
			exit(1);
		}
		
		noRestart	=	FALSE;
		rndrd(port);
		free(source);
		exit(0);

	}
	
	// Deal with stdin renders
	if (strcmp(source,"-") == 0) {
		if ((client | server | localserver)  && (silent == FALSE) && (killservers != TRUE)) {
			fprintf(stderr,"Using STDIN pipe is not possible for network or multiprocess renders\n");
			free(source);
			exit(1);
		}
	}
	
	// Launch local servers if needed
	if (localChildren != 0) {
		noRestart	=	TRUE;
		
		// verify RIBs exists
		char *pstart = source;
		char *pend;
		do {
			pend = strchr(pstart,':');
			if (pend)	*pend = '\0';
			if (osFileExists(pstart) == FALSE) {
				if (silent == FALSE)	fprintf(stderr,"Cannot find RIB file '%s'\n",pstart);
				free(source);
				exit(1);
			}
			if (pend)	*pend = ':';
			pstart = pend + 1;
		} while(pend);
		
		// run teh servers
		if (runLocalServers(localChildren,source,managerString) == FALSE) {
			if (silent == FALSE)	fprintf(stderr,"Failed to launch subprocesses\n");
			free(source);
			exit(1);
		}
	}
	
	// Launch as spawned local server if needed
	if (clientport != 0) {
		rndrc(source,clientport);
		free(source);
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
	
#ifndef _WINDOWS
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

	if (numThreads > 0) {
		RiOption(RI_LIMITS,RI_NUMTHREADS,&numThreads,RI_NULL);
	}
	
	if (!killservers) {
		char *pstart = source;
		char *pend;
		do {
			pend = strchr(pstart,':');
			if (pend)	*pend = '\0';
			RiReadArchive(pstart,NULL,NULL);
			if (pend)	*pend = ':';
			pstart = pend + 1;
		} while(pend);
	}

	RiEnd();
	free(source);

	return (RiLastError != RIE_NOERROR) ? -1 : 0;
}

