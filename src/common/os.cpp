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
//  File				:	os.cpp
//  Classes				:	-
//  Description			:	OS dependent functions
//
////////////////////////////////////////////////////////////////////////

// Needs to be first, or clashes with other definitions
#if defined(__APPLE__) || defined(__APPLE_CC__)    	// guard against __APPLE__ being undef from ftlk
#include <CoreServices/CoreServices.h>         		// For FSRef, FSRefMakePath, FSFindFolder
#endif

#include "os.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

// Needed for OSX 10.2.x fix
#if defined(__APPLE__) || defined(__APPLE_CC__)	// guard against __APPLE__ being undef from ftlk
#include <stdio.h>
#endif

// Environment seperators
#ifdef _WINDOWS
// >> Windoze
#include <io.h>
#include <direct.h>
#include <errno.h>


// << Windows
#else
// >> Unix
#include <sys/param.h>
#include <sys/sysctl.h>
#include <dlfcn.h>
#include <glob.h>

// << Unix
#endif

#ifdef HAVE_SYS_TIME_H
#ifdef TIME_WITH_SYS_TIME
#include <sys/time.h>
#endif
#endif

#ifndef HAVE_GETTIMEOFDAY
#include <sys/timeb.h>

static void gettimeofday(struct timeval *tv,void* time_zone) {
	timeb cur;

	ftime(&cur);

	tv->tv_sec	= (long) cur.time;
	tv->tv_usec = cur.millitm * 1000;
}
#endif


///////////////////////////////////////////////////////////////////////
// These two hold the operating start time
static	time_t	osStartTimeSec;
static	time_t	osStartTimeMsec;








///////////////////////////////////////////////////////////////////////
// Funvtion				:	osInit
// Description			:	Initialize the operating system
// Return Value			:	-
// Comments				:
void	osInit() {
	struct timeval	ti;

	gettimeofday(&ti, NULL);

	osStartTimeSec	=	ti.tv_sec;
	osStartTimeMsec	=	ti.tv_usec;
}

///////////////////////////////////////////////////////////////////////
// Funvtion				:	osShutdown
// Description			:	Shutdown the operating system
// Return Value			:	-
// Comments				:
void	osShutdown() {
}


///////////////////////////////////////////////////////////////////////
// Funvtion				:	osLoadModule
// Description			:	Load / attach a dll/so file
// Return Value			:	The module handle
// Comments				:
void	*osLoadModule(const char *name) {
	void	*cModule	=	NULL;

#ifdef _WINDOWS
	// Windows stuff here
	cModule	=	LoadLibrary(name);
#else
	// Unix stuff here
	cModule =	dlopen(name,RTLD_NOW);

	// Unix dlopen expects an absolute path or the shared object to be in LD_LIBRARY_PATH
	// Convert the name to an absolute file name
	if (cModule == NULL) {
		char	absoluteName[MAXPATHLEN];
		char	*absolute	=	realpath(name,absoluteName);

		if (absolute != NULL) {
			cModule =	dlopen(absolute,RTLD_NOW);
		}
	}
#endif

	return cModule;
}

///////////////////////////////////////////////////////////////////////
// Funvtion				:	osModuleError
// Description			:	Get the latest error
// Return Value			:	The error string
// Comments				:
const char *osModuleError() {
#ifdef _WINDOWS
	return NULL;
#else
	return dlerror();
#endif
}

///////////////////////////////////////////////////////////////////////
// Function				:	osUnloadModule
// Description			:	Unload / detach a dll/so file
// Return Value			:	The module handle
// Comments				:
void	osUnloadModule(void *cModule) {
#ifdef _WINDOWS
	if (cModule != NULL) FreeLibrary((HMODULE) cModule);
#else
	if (cModule != NULL) dlclose((void *) cModule);
#endif
}


///////////////////////////////////////////////////////////////////////
// Function				:	osResolve
// Description			:	Resolve a symbol in a dll/so file
// Return Value			:	The module handle
// Comments				:
void	*osResolve(void *cModule,const char *name) {
	void	*result	=	NULL;

	if (cModule != NULL) {
#ifdef _WINDOWS
		result	=	GetProcAddress((HMODULE) cModule,name);
#else
		result	=	dlsym((void *) cModule,name);
		
// OSX 10.2.x fix
#if defined(__APPLE__) || defined(__APPLE_CC__)	// guard against __APPLE__ being undef from ftlk
		if(result == NULL){
			char new_name[strlen(name)+2];
			sprintf(new_name,"_%s",name);
			result	=	dlsym((void *) cModule,new_name);
		}
#endif

#endif
	}

	return result;
}

///////////////////////////////////////////////////////////////////////
// Function				:	osEnvironment
// Description			:	Get an environment variable
// Return Value			:	The variable value if found
// Comments				:
char			*osEnvironment(const char *name) {	
	return getenv(name);
}

///////////////////////////////////////////////////////////////////////
// Function				:	osFileExists
// Description			:	Check if a file exists
// Return Value			:	TRUE if it does
// Comments				:
int		osFileExists(const char *name) {
#ifdef _WINDOWS
	if (_access(name,0) == 0) return TRUE;
#else
	if (access(name,0) == 0) return TRUE;
#endif
	return FALSE;
}



///////////////////////////////////////////////////////////////////////
// Function				:	osFixSlashes
// Description			:	Make sure the slashes are right
// Return Value			:	-
// Comments				:
void	osFixSlashes(char *st) {
	for (;*st!='\0';st++) {
		if ((*st == '\\') || (*st == '/')) *st	=	OS_DIR_SEPERATOR;
	}
}


///////////////////////////////////////////////////////////////////////
// Function            :   osTempdir
// Description         :   Create a path to a directory suitable
//                     :   for storing temporary files.
// Return Value        :   -
// Comments            :   The directory will end with / or \
//                     :   Does not create the directory.
//                     :   Path is only unique within this process.
void   osTempdir(char *result, size_t resultsize) {    
   
#ifdef _WINDOWS
	sprintf(result,"PixieTemp_%d\\",GetCurrentProcessId());
#elif defined(__APPLE__) || defined(__APPLE_CC__)  // guard against __APPLE__ being undef from ftlk
	FSRef tempRef;
	char tempDirPath[OS_MAX_PATH_LENGTH];
	OSErr err = FSFindFolder(kLocalDomain,kTemporaryFolderType,true,&tempRef);
	if (!err)
		err = FSRefMakePath(&tempRef,(UInt8*)tempDirPath,sizeof(tempDirPath));
	if (!err)
		snprintf(result,resultsize,"%s/PixieTemp_%d/",tempDirPath,getpid());
	else
		snprintf(result,resultsize,"/tmp/PixieTemp_%d/",getpid());
	
#else
	// Unix-y
	const char *tempDirEnv = osEnvironment("TMPDIR");
	if (!tempDirEnv)
		tempDirEnv = osEnvironment("TMP");
	if (tempDirEnv != NULL)
		snprintf(result,resultsize,"%s/PixieTemp_%d/",tempDirEnv,getpid());
	else
		snprintf(result,resultsize,"PixieTemp_%d/",getpid());
#endif
	
	osFixSlashes(result);   
}


///////////////////////////////////////////////////////////////////////
// Function				:	osTempname
// Description			:	Create a temporary file
// Return Value			:	-
// Comments				:	The directory must end with / (or \)
void	osTempname(const char *directory,const char *prefix,char *result) {
	#ifdef _WINDOWS
		// avoid some windows shortcomings by extending count when we
		// start to get clashes
		static int i = 0;
		sprintf(result,"%s%s-%4xXXXXXXXX",directory,prefix,i);
		while(_mktemp(result) == NULL) {
			sprintf(result,"%s%s-%4xXXXXXXXX",directory,prefix,i++);
		}
	#else
		sprintf(result,"%s%s-XXXXXXXX",directory,prefix);
		mktemp(result);
	#endif
}




///////////////////////////////////////////////////////////////////////
// Function				:	osCreateDir
// Description			:	Create a directory
// Return Value			:	-
// Comments				:
void	osCreateDir(const char *n) {
#ifdef _WINDOWS
		_mkdir(n);
#else
		mkdir(n,S_IRWXU);
#endif
}

///////////////////////////////////////////////////////////////////////
// Function				:	osDeleteDir
// Description			:	Remove a directory
// Return Value			:	-
// Comments				:
void	osDeleteDir(const char *n)	{
#ifdef _WINDOWS
	_rmdir(n);	
#else
	rmdir(n);
#endif
}

///////////////////////////////////////////////////////////////////////
// Function				:	osDeleteFile
// Description			:	Delete a file
// Return Value			:	-
// Comments				:
void	osDeleteFile(const char *n)	{
#ifdef _WINDOWS
	_unlink(n);	
#else
	unlink(n);	
#endif
}


///////////////////////////////////////////////////////////////////////
// Function				:	enumerate
// Description			:	Enumerate the files matching a criteria
// Return Value			:
// Comments				:
void	osEnumerate(const char *name,int (*callback)(const char *,void *),void *userData) {
#ifdef _WINDOWS
	_finddata_t	c_file;
	intptr_t	hFile;
	char		tmp[OS_MAX_PATH_LENGTH];
	char		*tmpp;

	strcpy(tmp,name);
	osFixSlashes(tmp);

	tmpp	=	strrchr(tmp,OS_DIR_SEPERATOR);
	if (tmpp == NULL) {
		tmpp	=	tmp;
	} else {
		tmpp++;
	}

	if( (hFile = _findfirst(name, &c_file )) == -1L ) {
	} else {
		strcpy(tmpp,c_file.name);
		if (callback(tmp,userData) == TRUE) {
			while( _findnext( hFile, &c_file ) == 0 ) {
				strcpy(tmpp,c_file.name);
				if (callback(tmp,userData) == FALSE)	break;
			}
		}

		_findclose( hFile );
	}
#else
	glob_t	globbuf;
	int		i;

	globbuf.gl_offs =       0;
	glob(name,GLOB_DOOFFS,NULL,&globbuf);


	for (i=0;i<globbuf.gl_pathc;i++) {
		if (callback(globbuf.gl_pathv[i],userData) == FALSE)	break;
	}

	globfree(&globbuf);
#endif
}

///////////////////////////////////////////////////////////////////////
// Function				:	osTime
// Description			:	Get the time
// Return Value			:
// Comments				:
float	osTime() {
	struct timeval	ti;

	gettimeofday(&ti, NULL);

	return (float) (ti.tv_sec - osStartTimeSec) + (ti.tv_usec - osStartTimeMsec) / 1000000.0f;
}

///////////////////////////////////////////////////////////////////////
// Function				:	osTime
// Description			:	Get the time
// Return Value			:
// Comments				:
float	osCPUTime() {
	return	clock() / (float) CLOCKS_PER_SEC;
}

///////////////////////////////////////////////////////////////////////
// Function				:	osCreateThread
// Description			:	Start a thread
// Return Value			:
// Comments				:
TThread	osCreateThread(TFun entry,void *d) {
	TThread	cThread;

#ifdef _WINDOWS
	DWORD		id;

	cThread				=	CreateThread(NULL,80000000,entry,d,0,&id);
#else
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setstacksize(&attr,1024*1024*8);//8MB stack
	pthread_create(&cThread,&attr,entry,d);
	pthread_attr_destroy(&attr);
	//pthread_create(&cThread,NULL,entry,d);
#endif

	return	cThread;
}

///////////////////////////////////////////////////////////////////////
// Function				:	osWaitThread
// Description			:	Wait for the termination of a thread
// Return Value			:
// Comments				:
int		osWaitThread(TThread	thread) {
#ifdef _WINDOWS
	WaitForSingleObject(thread,INFINITE);
#else
	return pthread_join(thread,NULL);
#endif

	return 0;
}

///////////////////////////////////////////////////////////////////////
// Function				:	osCreateMutex
// Description			:	Create a mutex
// Return Value			:
// Comments				:
void	osCreateMutex(TMutex &mutex) {
#ifdef _WINDOWS
	InitializeCriticalSection(&mutex);
#else
	pthread_mutex_init(&mutex,NULL);
#endif
}

///////////////////////////////////////////////////////////////////////
// Function				:	osDeleteMutex
// Description			:	Delete a mutex
// Return Value			:
// Comments				:
void	osDeleteMutex(TMutex &mutex) {
#ifdef _WINDOWS
	DeleteCriticalSection(&mutex);
#else
	pthread_mutex_destroy(&mutex);
#endif
}

///////////////////////////////////////////////////////////////////////
// Function				:	osCreateSemaphore
// Description			:	Create a semaphere
// Return Value			:
// Comments				:
void	osCreateSemaphore(TSemaphore &sem,int count) {
#ifdef _WINDOWS
	sem	=	CreateSemaphore(NULL,0,count,NULL);
#else
	sem_init(&sem,PTHREAD_PROCESS_PRIVATE,count);
#endif
}

///////////////////////////////////////////////////////////////////////
// Function				:	osDeleteMutex
// Description			:	Delete a mutex
// Return Value			:
// Comments				:
void	osDeleteSemaphore(TSemaphore &sem) {
#ifdef _WINDOWS
	CloseHandle(sem);
#else
	sem_destroy(&sem);
#endif
}


///////////////////////////////////////////////////////////////////////
// Function				:	osProcessEscapes
// Description			:	Process the escape characters in a string
// Return Value			:
// Comments				:
void	osProcessEscapes(char *str) {
	int		i,n,j;

	n	=	(int) strlen(str);
	for (i=0;i<n;i++) {
		if (str[i] == '\\') {
			switch(str[i+1]) {
			case 'n':
				str[i]	=	'\n';
				break;
			case 't':
				str[i]	=	'\t';
				break;
			case 'r':
				str[i]	=	'\r';
				break;
			case '\\':
				str[i]	=	'\\';
				break;
			default:
				break;
			}

			j	=	i+2;
			do {
				str[j-1]	=	str[j];
				j++;
			} while(str[j] != '\0');
			n--;
			i++;
		}
	}
	str[i]	=	'\0';
}

///////////////////////////////////////////////////////////////////////
// Function            :   osAvailableCPUs
// Description         :   Get number of CPUs available
// Return Value        :   Number of available CPUs or -1 if unknown
// Comments            :   See <http://stackoverflow.com/questions/150355/programmatically-find-the-number-of-cores-on-a-machine>
int    osAvailableCPUs() {

#if defined(WIN32)
	SYSTEM_INFO sys_info;
    GetSystemInfo(&sys_info);
    return sys_info.dwNumberOfProcessors;
	
#elif defined(CTL_HW)
	// BSD, Mac OS X
	int ncpu = 0;
	int mib[2];
	size_t sz = sizeof(ncpu);
	mib[0] = CTL_HW;
#ifdef HW_AVAILCPU
	mib[1] = HW_AVAILCPU;
#else
	mib[1] = HW_NCPU;
#endif
	if(sysctl(mib, 2, &ncpu, &sz, NULL, 0) == -1)
		return ncpu;
	   
#elif defined(_SC_NPROCESSORS_ONLN)
	// Linux, AIX, Solaris
	return sysconf( _SC_NPROCESSORS_ONLN );
	
#elif defined(MPC_GETNUMSPUS)
	// HP-UX
	return mpctl(MPC_GETNUMSPUS, NULL, NULL);
   
#elif defined(_SC_NPROC_ONLN)
	// IRIX
	return sysconf( _SC_NPROC_ONLN );
#endif 
	
	return -1;
}


