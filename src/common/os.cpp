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
//  File				:	os.cpp
//  Classes				:	-
//  Description			:	OS dependent functions
//
////////////////////////////////////////////////////////////////////////
#include "os.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/timeb.h>

// Needed for OSX 10.2.x fix
#if defined(__APPLE__) || defined(__APPLE_CC__)	// guard against __APPLE__ being undef from ftlk
#include <stdio.h>
#endif

// Environment seperators
#ifdef WIN32
// >> Win32
#include <io.h>
#include <direct.h>
#include <errno.h>


#define	OS_DIR_SEPERATOR					'\\'
#define OS_DIR_SEPERATOR_STRING				"\\"

///////////////////////////////////////////////////
// For WIN32 we create encapsulate the thread in the following structure
typedef struct {
	void	*userData;
	TFun	thread;
} TThreadData;

// This is the entry point for WIN32 threads
static	DWORD WINAPI  dispatcherThread(void *w) {
	TThreadData	*data		=	(TThreadData *) w;
	TFun		thread		=	data->thread;
	void		*userData	=	data->userData;

	delete data;

	thread(userData);

	return 0;
}


// << Win32
#else
// >> Unix
#include <sys/param.h>
#include <dlfcn.h>
#include <glob.h>

#define OS_DIR_SEPERATOR					'/'
#define OS_DIR_SEPERATOR_STRING				"/"
// << Unix
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
	timeb	ti;

	ftime(&ti);

	osStartTimeSec	=	ti.time;
	osStartTimeMsec	=	ti.millitm;
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

#ifdef WIN32
	// Win32 stuff here
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
#ifdef WIN32
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
#ifdef WIN32
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
#ifdef WIN32
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
#ifdef WIN32
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
// Function				:	osTempname
// Description			:	Create a temporary file
// Return Value			:	-
// Comments				:
void	osTempname(const char *directory,const char *prefix,char *result) {
	#ifdef WIN32
		// avoid some windows shortcomings by extending count when we
		// start to get clashes
		static int i = 0;
		sprintf(result,"%s\\%s-%4xXXXXXXXX",directory,prefix,i);
		osFixSlashes(result);
		while(_mktemp(result) == NULL) {
			sprintf(result,"%s\\%s-%4xXXXXXXXX",directory,prefix,i++);
			osFixSlashes(result);
		}
	#else
		sprintf(result,"%s\\%s-XXXXXXXX",directory,prefix);
		osFixSlashes(result);
		mktemp(result);
	#endif
}


///////////////////////////////////////////////////////////////////////
// Function				:	osOpen
// Description			:	Wrapper for fopen
// Return Value			:	-
// Comments				:
void			*osOpen(const char *name,const char *mode) {
	return fopen(name,mode);
}

///////////////////////////////////////////////////////////////////////
// Function				:	osClose
// Description			:	Wrapper for fclose
// Return Value			:	-
// Comments				:
void			osClose(void *handle) {
	fclose((FILE *)handle);
}

///////////////////////////////////////////////////////////////////////
// Function				:	osWrite
// Description			:	Wrapper for fwrite
// Return Value			:	-
// Comments				:
void			osWrite(void *handle,void *data,int bytes) {
	fwrite(data,1,bytes,(FILE *) handle);
}

///////////////////////////////////////////////////////////////////////
// Function				:	osWriteInt
// Description			:	Wrapper for fwrite
// Return Value			:	-
// Comments				:
void			osWriteInt(void *handle,int *data,int number) {
	fwrite(data,sizeof(int),1,(FILE *) handle);
}

///////////////////////////////////////////////////////////////////////
// Function				:	osWriteFloat
// Description			:	Wrapper for fwrite
// Return Value			:	-
// Comments				:
void			osWriteFloat(void *handle,float *data,int number) {
	fwrite(data,sizeof(float),1,(FILE *) handle);
}

///////////////////////////////////////////////////////////////////////
// Function				:	osWriteString
// Description			:	Wrapper for fwrite
// Return Value			:	-
// Comments				:
void			osWriteString(void *handle,const char *data) {
	int	i	=	strlen(data);

	osWriteInt(handle,&i);
	osWrite(handle,(void *) data,i);
}

///////////////////////////////////////////////////////////////////////
// Function				:	osRead
// Description			:	Wrapper for fread
// Return Value			:	-
// Comments				:
void			osRead(void *handle,void *data,int bytes) {
	fread(data,1,bytes,(FILE *) handle);
}

///////////////////////////////////////////////////////////////////////
// Function				:	osReadInt
// Description			:	Wrapper for fread
// Return Value			:	-
// Comments				:
int				osReadInt(void *handle,int *data,int number) {
	if (data == NULL) {
		int	i;
		fread(&i,sizeof(int),number,(FILE *) handle);
		return i;
	} else {
		fread(data,sizeof(int),number,(FILE *) handle);
		return data[0];
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	osReadFloat
// Description			:	Wrapper for fread
// Return Value			:	-
// Comments				:
float			osReadFloat(void *handle,float *data,int number) {
	if (data == NULL) {
		float	i;
		fread(&i,sizeof(float),number,(FILE *) handle);
		return i;
	} else {
		fread(data,sizeof(float),number,(FILE *) handle);
		return data[0];
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	osReadString
// Description			:	Wrapper for fread
// Return Value			:	-
// Comments				:
char			*osReadString(void *handle,char **data) {
	int	length	=	osReadInt(handle);

	if (data == NULL) {
		char	*string	=	(char *) malloc((length+1)*sizeof(char));
		osRead(handle,string,length);
		return string;
	} else {	
		osRead(handle,*data,length);
		return *data;
	}
}


///////////////////////////////////////////////////////////////////////
// Function				:	osCreateDir
// Description			:	Create a directory
// Return Value			:	-
// Comments				:
void	osCreateDir(const char *n) {
#ifdef WIN32
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
#ifdef WIN32
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
#ifdef WIN32
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
#ifdef WIN32
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
	timeb	ti;

	ftime(&ti);

	return (float) (ti.time - osStartTimeSec) + (ti.millitm - osStartTimeMsec) / 1000.0f;
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

#ifdef WIN32
	DWORD		id;
	TThreadData	*data	=	new TThreadData;

	data->thread		=	entry;
	data->userData		=	d;

	cThread				=	CreateThread(NULL,80000000,dispatcherThread,data,0,&id);
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
#ifdef WIN32
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
#ifdef WIN32
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
#ifdef WIN32
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
#ifdef WIN32
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
#ifdef WIN32
	CloseHandle(sem);
#else
	sem_destroy(&sem);
#endif
}

