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

class CRWLock {
    HANDLE  readerEvent;
    HANDLE  mutex;
    HANDLE  writerMutex;
	LONG	readCount;
	
    friend void osCreateRWLock(CRWLock &);
    friend void osDeleteRWLock(CRWLock &);
    friend void osReadLock(CRWLock &);
    friend void osReadUnlock(CRWLock &);
    friend void osWriteLock(CRWLock &);
    friend void osWriteUnlock(CRWLock &);
};

#define	socklen_t		int
#define	LIB_EXPORT		__declspec(dllexport)
#define LIB_IMPORT		__declspec(dllimport)
#define	popen			_popen
#define	pclose			_pclose
#define	TThread			HANDLE
#define	TMutex			CRITICAL_SECTION 
#define	TSemaphore		HANDLE
#define TRWLock         CRWLock
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

//#if defined(__APPLE__) || defined(__APPLE_CC__)	// guard against __APPLE__ being undef from ftlk
#include <semaphore.h>
//#endif


#define	LIB_EXPORT		extern
#define LIB_IMPORT		extern
#define SOCKET			int
#define	closesocket		close
#define	INVALID_SOCKET	-1
#define	TThread			pthread_t
#define	TMutex			pthread_mutex_t
#define TSemaphore		sem_t
#define TRWLock			pthread_rwlock_t
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
void			osCreateSemaphore(TMutex &,int);
void			osDeleteSemaphore(TMutex &);

///////////////////////////////////////////////////////////////////////
// Function				:	osLock
// Description			:	Lock a mutex
// Return Value			:
// Comments				:
inline	void	osLock(TMutex &mutex) {
#ifdef WIN32
	EnterCriticalSection(&mutex);
#else
	pthread_mutex_lock(&mutex);
#endif
}

///////////////////////////////////////////////////////////////////////
// Function				:	osUnlock
// Description			:	Unlock a mutex
// Return Value			:
// Comments				:
inline	void	osUnlock(TMutex &mutex) {
#ifdef WIN32
	LeaveCriticalSection(&mutex);
#else
	pthread_mutex_unlock(&mutex);
#endif
}


///////////////////////////////////////////////////////////////////////
// Function				:	osUp
// Description			:	Increment a semaphore
// Return Value			:
// Comments				:
inline	void	osUp(TSemaphore &sem) {
#ifdef WIN32
	ReleaseSemaphore(sem,1,NULL);
#else
	sem_post(&sem);
#endif
}

///////////////////////////////////////////////////////////////////////
// Function				:	osDown
// Description			:	Decrement a semaphore
// Return Value			:
// Comments				:
inline	void	osDown(TSemaphore &sem) {
#ifdef WIN32
	WaitForSingleObject(sem,INFINITE);
#else
	sem_wait(&sem);
#endif
}

///////////////////////////////////////////////////////////////////////
// Function				:	osCreateRWLock
// Description			:	create a read-write lock
// Return Value			:
// Comments				:
inline	void osCreateRWLock(TRWLock &l) {
#ifdef WIN32
	l.readerEvent	=	CreateEvent(NULL,TRUE,FALSE,NULL);
	l.mutex			=	CreateEvent(NULL,FALSE,TRUE,NULL);
	l.writerMutex	=	CreateMutex(NULL,FALSE,NULL);
	l.readCount		=	-1;
#else
	pthread_rwlock_init(&l,NULL);
#endif
}

///////////////////////////////////////////////////////////////////////
// Function				:	osDeleteRWLock
// Description			:	destroy a read-write lock
// Return Value			:
// Comments				:
inline	void osDeleteRWLock(TRWLock &l) {
#ifdef WIN32
	CloseHandle(l.readerEvent);
	CloseHandle(l.mutex);
	CloseHandle(l.writerMutex);
#else
	pthread_rwlock_destroy(&l);
#endif
}

///////////////////////////////////////////////////////////////////////
// Function				:	osReadLock
// Description			:	lock for reading
// Return Value			:
// Comments				:
inline	void osReadLock(TRWLock &l) {
#ifdef WIN32
	// If we're first reader, claim mutex for all readers
	if (InterlockedIncrement(&l.readCount) == 0) {
		WaitForSingleObject(l.mutex, INFINITE);
	}
	// Signal that there are readers
	WaitForSingleObject(l.readerEvent, INFINITE);
#else	
	pthread_rwlock_rdlock(&l);
#endif
}

///////////////////////////////////////////////////////////////////////
// Function				:	osReadUnlock
// Description			:	unlock after reading
// Return Value			:
// Comments				:
inline	void osReadUnlock(TRWLock &l) {
#ifdef WIN32
	// If we're last reader, signal that there are no more
	if (InterlockedDecrement(&l.readCount) < 0) {
		ResetEvent(l.readerEvent);
		// And release global mutex for a writer
		ReleaseMutex(l.mutex);
	}
#else
	pthread_rwlock_unlock(&l);
#endif
}

///////////////////////////////////////////////////////////////////////
// Function				:	osWriteLock
// Description			:	lock for writing
// Return Value			:
// Comments				:
inline	void osWriteLock(TRWLock &l) {
#ifdef WIN32
	// Ensure we are the only writr
	WaitForSingleObject(l.writerMutex, INFINITE);
	// Claim the global mutex
	WaitForSingleObject(l.mutex, INFINITE);
#else
	pthread_rwlock_wrlock(&l);
#endif
}

///////////////////////////////////////////////////////////////////////
// Function				:	osWriteUnlock
// Description			:	unlock after writing
// Return Value			:
// Comments				:
inline	void osWriteUnlock(TRWLock &l) {
#ifdef WIN32
	// Signal that that there are no more writers
	SetEvent(l.mutex);
	// And release writer mutex for a reader
	ReleaseMutex(l.writerMutex);
#else
	pthread_rwlock_unlock(&l);
#endif
}


// Misc. file extensions
#ifdef WIN32
const	char	osModuleExtension[]		=	"dll";
#else		// Win32
#ifdef __APPLE_CC__
//const	char	osModuleExtension[]		=	"dylib";

// loadable libs on darwin are supposed to be .bundle
// but automake/libtool chooses .so and it can't be 
// changed.  Xcode can be
const	char	osModuleExtension[]		=	"so";
#else		// OSX
const	char	osModuleExtension[]		=	"so";
#endif		// OSX
#endif		// Win32

#endif

