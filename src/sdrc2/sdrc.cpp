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
//  File				:	sdrc.cpp
//  Classes				:	-
//  Description			:	The main shader compiler source code
//
////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
//
//
//	The main shader compiler source code
//
//
//
//
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////
#include <string.h>

// Standard includes
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#ifndef		__INTEL_COMPILER
#ifdef		_WINDOWS
#ifdef		_DEBUG
#include <crtdbg.h>
#endif
#endif
#endif


#include "common/global.h"							// The glorious global header
#include "common/os.h"								// OS dependent stuff)
#include "common/containers.h"

extern	"C" int	preprocess(char *,FILE *,int,char **);
void	compile(FILE *in,char *outName);

// The environment variables to be searched for the preprocessor and include files
#define			PATH				"PATH"			// The environment variable to search for the preprocessor
#define			INCLUDE				"INCLUDE"		// The default include path for the preprocessor

// This structure is used to hold a linked list of search directories
typedef struct TSearchpath {
	char		*directory;
	TSearchpath	*next;
} TSearchpath;


// If the preprocessing is not turned off, then the preprocessor will be invoked to generate
// preprocessed stuff into the argumentTemporaryFileName and then the compiler will be run on
// this file

// The symbol to be defined by the preprocessor
static	char	*defineProgramName				=			"PIXIE";
// The name of the executable
static	char	*compilerName					=			"sdrc";


/////////////////////////////////////////////////////////////////////
// Program command line switches
static	char	*argumentIncludeDirectory		=			"-I";
static	char	*argumentDefine					=			"-D";
static	char	*argumentOutput					=			"-o";
static	char	*argumentSurpressWarnings		=			"-nw";
static	char	*argumentSurpressErrors			=			"-ne";
static	char	*argumentResolutionInfo			=			"-ri";
static	char	*argumentHelp					=			"--help";
static	char	*argumentPrintVersionInfo		=			"-v";

///////////////////////////////////////////////////////////////////////
// Function				:	printVersion
// Description			:	Print the version
// Return Value			:	-
// Comments				:
void	printVersion() {
	printf("RenderMan Shading Language Compiler (%s) v%d.%d.%d\n",compilerName,VERSION_RELEASE,VERSION_BETA,VERSION_ALPHA);
}

///////////////////////////////////////////////////////////////////////
// Function				:	printUsage
// Description			:	Print the compiler usage
// Return Value			:	-
// Comments				:
void	printUsage() {
	printVersion();
	printf("Usage:\n");
	printf("%s [options] [<in_file>]\n",compilerName);
	printf("options:\n");

	printf("%s<path>\t: Specify additional include path for the preprocessor\n",argumentIncludeDirectory);

	printf("%s<symbol>\t: Define \"symbol\" for the preprocessor\n",argumentDefine);

	printf("%s <outname>\t: Output to \"outname\" \n",argumentOutput);

	printf("%s\t\t: Surpress warnings\n",argumentSurpressWarnings);

	printf("%s\t\t: Surpress errors\n",argumentSurpressErrors);

	printf("%s\t\t: Display resolution info\n",argumentResolutionInfo);

	printf("%s\t\t: Display version info\n",argumentPrintVersionInfo);

	printf("%s\t\t: Display this message\n",argumentHelp);

	printf("The environment variable PATH will be searched for the preprocessor by default\n");

	printf("The environment variable INCLUDE will be passed to the preprocessor by default\n");

	printf("***<in_file> can have wildcards\n");
}

///////////////////////////////////////////////////////////////////////
// Function				:	initError
// Description			:	Display an error and exit
// Return Value			:	-
// Comments				:
void	initError(char *mes,...) {
	va_list	args;

	va_start(args,mes);
	vprintf(mes,args);
	va_end(args);
	exit(-1);
}

///////////////////////////////////////////////////////////////////////
// Function				:	append
// Description			:	Append a file name
// Return Value			:	-
// Comments				:
int		append(const char *file,void *ud) {
	CList<char *>	*sourceFiles	=	(CList<char *> *)	ud;

	sourceFiles->push(strdup(file));

	return TRUE;
}


///////////////////////////////////////////////////////////////////////
// Function				:	main
// Description			:	Shading compiler main
// Return Value			:	-
// Comments				:
int main(int argc, char* argv[]) {
	int				i;
	TSearchpath		*dsoPath;
	CList<char *>	*sourceFiles;
	char			*sourceFile;
	char			*ppargv[100];
	int				ppargc;
	char			*outName	=	NULL;
	char 			*includeEnv =	osEnvironment(INCLUDE);
	
	sourceFiles					=	new CList<char *>;

	dsoPath						=	new TSearchpath;
	dsoPath->directory			=	strdup(".");
	dsoPath->next				=	NULL;

	ppargc						=	1;
	ppargv[ppargc++]			=	"-c";
	ppargv[ppargc++]			=	"6";
	ppargv[ppargc++]			=	"-d";
	ppargv[ppargc++]			=	defineProgramName;
	
	if (includeEnv != NULL) {
		ppargv[ppargc++]		=	"-i";
		ppargv[ppargc++]		=	includeEnv;
	}

	// Process the arguments
	for (i=1;i<argc;i++) {
		if (strcmp(argv[i],argumentPrintVersionInfo) == 0) {
			printVersion();
			exit(1);
		} else if (strcmp(argv[i],argumentHelp) == 0) {
			printUsage();
			exit(1);
		} else if (strcmp(argv[i],argumentOutput) == 0) {
			if (i < (argc-1)) {
				outName				=	argv[i+1];
				i++;
			} else
				fprintf(stderr,"Output name expected\n");
		} else if (strncmp(argv[i],argumentDefine,strlen(argumentDefine)) == 0) {
			ppargv[ppargc++]	=	"-d";
			ppargv[ppargc++]	=	&argv[i][2];
		} else if (strncmp(argv[i],argumentIncludeDirectory,strlen(argumentIncludeDirectory)) == 0) {
			TSearchpath *nPath	=	new TSearchpath;

			ppargv[ppargc++]	=	"-i";
			ppargv[ppargc++]	=	&argv[i][2];

			nPath->directory	=	strdup(&argv[i][2]);
			nPath->next			=	dsoPath;
			dsoPath				=	nPath;
		} else {
			// Save the files
			sourceFiles->push(strdup(argv[i]));
			argv[i]	=	NULL;
		}
	}

	ppargv[ppargc++]	=	"-v";

	// Go over the arguments and replace the wildcards
	{
		char			*file;
		CList<char *>	*newSources	=	new CList<char *>;

		for (file=sourceFiles->first();file != NULL;file = sourceFiles->next()) {
			if ((strchr(file,'*') != NULL) || (strchr(file,'?') != NULL)) {
				osEnumerate(file,append,newSources);
				free(file);
			} else {
				newSources->push(file);
			}
		}

		delete sourceFiles;
		sourceFiles	=	newSources;
	}

	if (sourceFiles->numItems == 1) {
		// Get a temp file
		FILE	*in	=	fopen("sdrc.temp","w+");

		// Do we have a go ?
		if (in != NULL) {

			// Get the source file
			sourceFile	=	sourceFiles->pop();

			// Preprocess the file
			if (preprocess(sourceFile,in,ppargc,ppargv) == TRUE) {

				// Rewind in the file
				fseek(in,0,SEEK_SET);

				/*
				// Create the compiler
				currentCompiler				=	new CScriptContext(settings);
				currentCompiler->dsoPath	=	dsoPath;

				// Set the file name
				if (currentCompiler->sourceFile != NULL)	free(currentCompiler->sourceFile);

				// Compile the file
				currentCompiler->sourceFile	=	strdup(sourceFile);
				currentCompiler->compile(in,outName);

				// Ditch the compiler
				delete currentCompiler;
				*/
			}

			// Ditch the temp file
			fclose(in);
			osDeleteFile("sdrc.temp");
		} else {
			fprintf(stderr,"Unable to create temporary file\n");
		}

		// Ditch the filename
		free(sourceFile);
	} else {
		char	tmp[OS_MAX_PATH_LENGTH];
		char	*fp;

		// Recreate the argument list
		strcpy(tmp,"");
		for (i=0;i<argc;i++) {
			if (argv[i] != NULL) {
				strcat(tmp,argv[i]);
				strcat(tmp," ");
			}
		}

		fp	=	tmp	+ strlen(tmp);

		for (sourceFile=sourceFiles->first();sourceFile!=NULL;sourceFile=sourceFiles->next()) {
			sprintf(fp,sourceFile);

			fprintf(stdout,"Compiling %s\n",sourceFile);

			system(tmp);

			free(sourceFile);
		}
	}


	delete sourceFiles;

	return 0;
}

