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
//  File				:	os.h
//  Classes				:	-
//  Description			:	OS dependent functions
//
////////////////////////////////////////////////////////////////////////
#ifndef OS_H
#define OS_H

#include "global.h"

#ifdef WIN32		// >>>>>>>>>>>>>>>>>>>   Win32
#define	WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <winsock.h>
#include <malloc.h>
#include <process.h>

#define	socklen_t		int
#define	LIB_EXPORT		__declspec(dllexport)
#define LIB_IMPORT		__declspec(dllimport)
#define	popen			_popen
#define	pclose			_pclose
#define	TThread			HANDLE
#define	TMutex			LPCRITICAL_SECTION 
typedef void			*(*TFun)(void *);

#else				// >>>>>>>>>>>>>>>>>>>   Unix
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <ctype.h>
#include <signal.h>
#include <errno.h>


#define	LIB_EXPORT		extern
#define LIB_IMPORT		extern
#define SOCKET			int
#define	closesocket		close
#define	INVALID_SOCKET	-1
#define	TThread			pthread_t
#define	TMutex			pthread_mutex_t
typedef void			*(*TFun)(void *);

#endif

// Some common headers
#include <stdio.h>
#include <stdlib.h>


// Because Microzort developers are monkeys, we need these
// for compatibility with the .NET 2005
#ifdef WIN32			// >>>>>>>>>>>>>>>>>>>   Win32

#ifndef strdup
#define		strdup	_strdup
#endif


#ifndef fileno
#define		fileno	_fileno
#endif

#endif					// >>>>>>>>>>>>>>>>>>>   Win32


// Maximum length of a path
const	int		OS_MAX_PATH_LENGTH	=	512;

// Init/shutdown
void			osInit();
void			osShutdown();

// Module I/O
void			*osLoadModule(const char *);
const char		*osModuleError();
void			osUnloadModule(void *);
void			*osResolve(void *,const char *);

// Get an environment variable (return NULL if non existent)
char			*osEnvironment(const char *);

// File io
int				osFileExists(const char *);
void			osFixSlashes(char *);
void			osTempname(const char *,const char *,char*);
void			*osOpen(const char *name,const char *mode);
void			osClose(void *handle);
void			osWrite(void *handle,void *data,int bytes);
void			osWriteInt(void *handle,int *data,int number=1);
void			osWriteFloat(void *handle,float *data,int number=1);
void			osWriteString(void *handle,const char *data);
void			osRead(void *handle,void *data,int bytes);
int				osReadInt(void *handle,int *data=NULL,int number=1);
float			osReadFloat(void *handle,float *data=NULL,int number=1);
char			*osReadString(void *handle,char **data=NULL);


// Directory IO
void			osCreateDir(const char *);
void			osDeleteDir(const char *);
void			osDeleteFile(const char *);

// Iterate thru files in a directory
void			osEnumerate(const char *,int (*callback)(const char *,void *),void *);

// Time functions
float			osTime();
float			osCPUTime();

// Sync. functions
TThread			osCreateThread(TFun,void *);
int				osWaitThread(TThread);
void			osCreateMutex(TMutex &);
void			osDeleteMutex(TMutex &);
void			osDownMutex(TMutex &);
void			osUpMutex(TMutex &);


// Misc. file extensions
#ifdef WIN32
const	char	osModuleExtension[]		=	"dll";
#else		// Win32
#ifdef OSX
const	char	osModuleExtension[]		=	"dylib";
#else		// OSX
const	char	osModuleExtension[]		=	"so";
#endif		// OSX
#endif		// Win32

#endif


