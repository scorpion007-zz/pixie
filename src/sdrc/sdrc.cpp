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

#include "common/global.h"							// The glorious global header
#include "common/os.h"								// OS dependent stuff)
#include "sdr.h"									// The CScriptContext
#include "opcodes.h"								// The opcodes/arguments


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


extern	"C" int	preprocess(char *,FILE *,int,const char **);

// The environment variables to be searched for the preprocessor and include files
#define			INCLUDE				"INCLUDE"		// The default include path for the preprocessor

// Return codes
#define ERR_NONE 0			// No error
#define ERR_FILE 1			// Cannot load file, cannot create tempfile
#define ERR_PREPROCESS 2	// Error in preprocessing
#define ERR_COMPILE 3		// Error in compilation

// If the preprocessing is not turned off, then the preprocessor will be invoked to generate
// preprocessed stuff into the argumentTemporaryFileName and then the compiler will be run on
// this file

// The symbol to be defined by the preprocessor
static	const char	*defineProgramName				=			"PIXIE";
// The name of the executable
static	const char	*compilerName					=			"sdrc";


/////////////////////////////////////////////////////////////////////
// Program command line switches
static	const char	*argumentIncludeDirectory		=			"-I";
static	const char	*argumentDefine					=			"-D";
static	const char	*argumentOutput					=			"-o";
static	const char	*argumentSuppressWarnings		=			"-nw";
static	const char	*argumentSuppressErrors			=			"-ne";
static	const char	*argumentResolutionInfo			=			"-ri";
static	const char	*argumentHelp					=			"-h";
static	const char	*argumentPrintVersionInfo		=			"-v";
static	const char	*argumentQuietInfo				=			"-q";

///////////////////////////////////////////////////////////////////////
// Function				:	printVersion
// Description			:	Print the version
// Return Value			:	-
// Comments				:
void	printVersion() {
	printf("Pixie RenderMan Shader Language Compiler (%s) v%d.%d.%d\n",compilerName,VERSION_RELEASE,VERSION_BETA,VERSION_ALPHA);
	printf("\nCopyright 1999-2008 Okan Arikan. http://renderpixie.com/\n");
	printf("Pixie is free software. There is NO warranty; not even for\n");
	printf("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n");
}

///////////////////////////////////////////////////////////////////////
// Function				:	printUsage
// Description			:	Print the compiler usage
// Return Value			:	-
// Comments				:
void	printUsage() {
	printf("Usage: %s <options> filename.sl [filename.sl ...]\n",compilerName);
	printf("The filenames are wildcard-expanded\n\n");
	printf("Options:\n");
	printf("  %s<path>           Additional include path for the preprocessor\n",argumentIncludeDirectory);
	printf("  %s<symbol>         Define <symbol> for the preprocessor\n",argumentDefine);
	printf("  %s<symbol>=<value> Define <symbol> to be <value>\n",argumentDefine);
	printf("  %s <filename>      Output to <filename> \n",argumentOutput);
	printf("  %s                Suppress warnings\n",argumentSuppressWarnings);
	printf("  %s                Suppress errors\n",argumentSuppressErrors);
	printf("  %s                 Quiet, suppress progress display\n",argumentQuietInfo);
	printf("  %s                Display resolution information\n",argumentResolutionInfo);
	printf("  %s                 Display version information\n",argumentPrintVersionInfo);
	printf("  %s                 Display this help\n",argumentHelp);
	printf("\nEnvironment variables:\n");
	printf("  INCLUDE            Additional include paths for the preprocessor\n");
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
	CScriptContext	*currentCompiler;
	int				i;
	int				settings	=	COMPILER_SUPPRESS_DEFINITIONS;
	TSearchpath		*dsoPath;
	CList<char *>	*sourceFiles;
	char			*sourceFile;
	const char		*ppargv[100];
	int				ppargc;
	char			*outName	=	NULL;
	char 			*includeEnv = osEnvironment(INCLUDE);
	int				error = ERR_NONE;
	int				quiet = FALSE;
	
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

	// Require some parameters, or else print help and exit
	if (argc<2) {
		printUsage();
		exit(1);
	}
	
	// Process the arguments
	for (i=1;i<argc;i++) {
		if (strcmp(argv[i],argumentSuppressWarnings) == 0) {
			settings	|=	COMPILER_SUPPRESS_WARNINGS;
		} else if (strcmp(argv[i],argumentSuppressErrors) == 0) {
			settings	|=	COMPILER_SUPPRESS_ERRORS;
		} else if (strcmp(argv[i],argumentResolutionInfo) == 0) {
			settings	&=	~COMPILER_SUPPRESS_DEFINITIONS;
		} else if (strcmp(argv[i],argumentQuietInfo) == 0) {
			quiet = TRUE;
		} else if (strcmp(argv[i],argumentPrintVersionInfo) == 0
				   ||strcmp(argv[i],"-version") == 0
				   ||strcmp(argv[i],"--version") == 0) {
			printVersion();
			exit(0);
		} else if (strcmp(argv[i],argumentHelp) == 0
				   || strcmp(argv[i],"-help")==0
				   || strcmp(argv[i],"--help")==0) {
			printUsage();
			exit(0);
		} else if (strcmp(argv[i],argumentOutput) == 0) {
			if (i < (argc-1)) {
				outName				=	argv[i+1];
				i++;
			} else
				fprintf(stderr,"Output filename expected\n");
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
		} else if (argv[i][0] == '-' && argv[i][1] != 0) {
			// Starts with '-' but not matched any option
			if (!(settings & (COMPILER_SUPPRESS_WARNINGS|COMPILER_SUPPRESS_ERRORS)))
				fprintf(stderr,"Unknown option '%s'\n", argv[i]);			
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

	// Require input file
	if (sourceFiles->numItems == 0)	{
		fprintf(stderr,"no input files\n");
		exit(0);
	};
	
	// If using -o only one file can be processed
	if (outName != NULL && sourceFiles->numItems > 1) {
		fprintf(stderr,"Named output file requires single input file\n");
		exit(1);
	};
		
		// Get a temp file
	char tempfile[OS_MAX_PATH_LENGTH];
	char tempdir[OS_MAX_PATH_LENGTH];
	osTempdir(tempdir,sizeof(tempdir));
	osCreateDir(tempdir);
	osTempname(tempdir,"sdrc",tempfile);
	
	for (sourceFile=sourceFiles->first();error==ERR_NONE,sourceFile!=NULL;sourceFile=sourceFiles->next()) {

		if (!quiet)	fprintf(stderr,"Compiling %s\n",sourceFile);

		FILE	*in	=	fopen(tempfile,"w+");		
		if (in == NULL) {
			fprintf(stderr,"Failed to create a temporary file\n");
			error = ERR_FILE;
			break;
		}

			// Preprocess the file
		if (!preprocess(sourceFile,in,ppargc,ppargv)) {
			error = ERR_PREPROCESS;
			fclose(in);
			break;
		}

				// Rewind in the file
				fseek(in,0,SEEK_SET);

				// Create the compiler
				currentCompiler				=	new CScriptContext(settings);
				currentCompiler->dsoPath	=	dsoPath;

				// Compile the file
				currentCompiler->sourceFile	=	sourceFile;
				currentCompiler->compile(in,outName);

				// Ditch the compiler
		if (currentCompiler->compileError)
			error = ERR_COMPILE;

		delete currentCompiler;
			fclose(in);
			}

	// Ditch the temp file
	osDeleteFile(tempfile);
	osDeleteDir(tempdir);
			free(sourceFile);
	delete sourceFiles;
	
	TSearchpath	*cPath,*nPath;
	for (cPath=dsoPath;cPath!=NULL;) {
		nPath	=	cPath->next;
		free(cPath->directory);
		delete cPath;
		cPath	=	nPath;
	}

	return error;
}

