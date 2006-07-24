/* A Bison parser, made by GNU Bison 2.0.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse ribparse
#define yylex   riblex
#define yyerror riberror
#define yylval  riblval
#define yychar  ribchar
#define yydebug ribdebug
#define yynerrs ribnerrs


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     RIB_DECLARE = 258,
     RIB_FRAME_BEGIN = 259,
     RIB_FRAME_END = 260,
     RIB_WORLD_BEGIN = 261,
     RIB_WORLD_END = 262,
     RIB_FORMAT = 263,
     RIB_FRAME_ASPECT_RATIO = 264,
     RIB_SCREEN_WINDOW = 265,
     RIB_CROP_WINDOW = 266,
     RIB_PROJECTION = 267,
     RIB_CLIPPING = 268,
     RIB_CLIPPING_PLANE = 269,
     RIB_DEPTH_OF_FIELD = 270,
     RIB_SHUTTER = 271,
     RIB_PIXEL_VARIANCE = 272,
     RIB_PIXEL_SAMPLES = 273,
     RIB_PIXEL_FILTER = 274,
     RIB_EXPOSURE = 275,
     RIB_IMAGER = 276,
     RIB_QUANTIZE = 277,
     RIB_DISPLAY = 278,
     RIB_DISPLAYCHANNEL = 279,
     RIB_HIDER = 280,
     RIB_COLOR_SAMPLES = 281,
     RIB_RELATIVE_DETAIL = 282,
     RIB_OPTION = 283,
     RIB_ATTRIBUTE_BEGIN = 284,
     RIB_ATTRIBUTE_END = 285,
     RIB_COLOR = 286,
     RIB_OPACITY = 287,
     RIB_TEXTURE_COORDINATES = 288,
     RIB_LIGHT_SOURCE = 289,
     RIB_AREA_LIGHT_SOURCE = 290,
     RIB_ILLUMINATE = 291,
     RIB_SURFACE = 292,
     RIB_ATMOSPHERE = 293,
     RIB_INTERIOR = 294,
     RIB_EXTERIOR = 295,
     RIB_SHADING_RATE = 296,
     RIB_SHADING_INTERPOLATION = 297,
     RIB_MATTE = 298,
     RIB_BOUND = 299,
     RIB_DETAIL = 300,
     RIB_DETAIL_RANGE = 301,
     RIB_GEOMETRIC_APPROXIMATION = 302,
     RIB_GEOMETRIC_REPRESENTATION = 303,
     RIB_ORIENTATION = 304,
     RIB_REVERSE_ORIENTATION = 305,
     RIB_SIDES = 306,
     RIB_IDENTITY = 307,
     RIB_TRANSFORM = 308,
     RIB_CONCAT_TRANSFORM = 309,
     RIB_PERSPECTIVE = 310,
     RIB_TRANSLATE = 311,
     RIB_ROTATE = 312,
     RIB_SCALE = 313,
     RIB_SKEW = 314,
     RIB_DEFORMATION = 315,
     RIB_DISPLACEMENT = 316,
     RIB_COORDINATE_SYSTEM = 317,
     RIB_COORDINATE_SYS_TRANSFORM = 318,
     RIB_TRANSFORM_BEGIN = 319,
     RIB_TRANSFORM_END = 320,
     RIB_ATTRIBUTE = 321,
     RIB_POLYGON = 322,
     RIB_GENERAL_POLYGON = 323,
     RIB_POINTS_POLYGONS = 324,
     RIB_POINTS_GENERAL_POLYGONS = 325,
     RIB_BASIS = 326,
     RIB_PATCH = 327,
     RIB_PATCH_MESH = 328,
     RIB_NU_PATCH = 329,
     RIB_TRIM_CURVE = 330,
     RIB_SPHERE = 331,
     RIB_CONE = 332,
     RIB_CYLINDER = 333,
     RIB_HYPERBOLOID = 334,
     RIB_PARABOLOID = 335,
     RIB_DISK = 336,
     RIB_TORUS = 337,
     RIB_CURVES = 338,
     RIB_GEOMETRY = 339,
     RIB_POINTS = 340,
     RIB_SUBDIVISION_MESH = 341,
     RIB_BLOBBY = 342,
     RIB_PROCEDURAL = 343,
     RIB_SOLID_BEGIN = 344,
     RIB_SOLID_END = 345,
     RIB_OBJECT_BEGIN = 346,
     RIB_OBJECT_END = 347,
     RIB_OBJECT_INSTANCE = 348,
     RIB_MOTION_BEGIN = 349,
     RIB_MOTION_END = 350,
     RIB_MAKE_TEXTURE = 351,
     RIB_MAKE_TEXTURE3D = 352,
     RIB_MAKE_BUMP = 353,
     RIB_MAKE_LAT_LONG_ENVIRONMENT = 354,
     RIB_MAKE_CUBE_FACE_ENVIRONMENT = 355,
     RIB_MAKE_SHADOW = 356,
     RIB_ARCHIVE_RECORD = 357,
     RIB_ERROR_HANDLER = 358,
     RIB_VERSION = 359,
     RIB_VERSION_STRING = 360,
     RIB_ARRAY_BEGIN = 361,
     RIB_ARRAY_END = 362,
     RIB_TEXT = 363,
     RIB_IDENTIFIER = 364,
     RIB_FLOAT = 365,
     RIB_STRUCTURE_COMMENT = 366
   };
#endif
#define RIB_DECLARE 258
#define RIB_FRAME_BEGIN 259
#define RIB_FRAME_END 260
#define RIB_WORLD_BEGIN 261
#define RIB_WORLD_END 262
#define RIB_FORMAT 263
#define RIB_FRAME_ASPECT_RATIO 264
#define RIB_SCREEN_WINDOW 265
#define RIB_CROP_WINDOW 266
#define RIB_PROJECTION 267
#define RIB_CLIPPING 268
#define RIB_CLIPPING_PLANE 269
#define RIB_DEPTH_OF_FIELD 270
#define RIB_SHUTTER 271
#define RIB_PIXEL_VARIANCE 272
#define RIB_PIXEL_SAMPLES 273
#define RIB_PIXEL_FILTER 274
#define RIB_EXPOSURE 275
#define RIB_IMAGER 276
#define RIB_QUANTIZE 277
#define RIB_DISPLAY 278
#define RIB_DISPLAYCHANNEL 279
#define RIB_HIDER 280
#define RIB_COLOR_SAMPLES 281
#define RIB_RELATIVE_DETAIL 282
#define RIB_OPTION 283
#define RIB_ATTRIBUTE_BEGIN 284
#define RIB_ATTRIBUTE_END 285
#define RIB_COLOR 286
#define RIB_OPACITY 287
#define RIB_TEXTURE_COORDINATES 288
#define RIB_LIGHT_SOURCE 289
#define RIB_AREA_LIGHT_SOURCE 290
#define RIB_ILLUMINATE 291
#define RIB_SURFACE 292
#define RIB_ATMOSPHERE 293
#define RIB_INTERIOR 294
#define RIB_EXTERIOR 295
#define RIB_SHADING_RATE 296
#define RIB_SHADING_INTERPOLATION 297
#define RIB_MATTE 298
#define RIB_BOUND 299
#define RIB_DETAIL 300
#define RIB_DETAIL_RANGE 301
#define RIB_GEOMETRIC_APPROXIMATION 302
#define RIB_GEOMETRIC_REPRESENTATION 303
#define RIB_ORIENTATION 304
#define RIB_REVERSE_ORIENTATION 305
#define RIB_SIDES 306
#define RIB_IDENTITY 307
#define RIB_TRANSFORM 308
#define RIB_CONCAT_TRANSFORM 309
#define RIB_PERSPECTIVE 310
#define RIB_TRANSLATE 311
#define RIB_ROTATE 312
#define RIB_SCALE 313
#define RIB_SKEW 314
#define RIB_DEFORMATION 315
#define RIB_DISPLACEMENT 316
#define RIB_COORDINATE_SYSTEM 317
#define RIB_COORDINATE_SYS_TRANSFORM 318
#define RIB_TRANSFORM_BEGIN 319
#define RIB_TRANSFORM_END 320
#define RIB_ATTRIBUTE 321
#define RIB_POLYGON 322
#define RIB_GENERAL_POLYGON 323
#define RIB_POINTS_POLYGONS 324
#define RIB_POINTS_GENERAL_POLYGONS 325
#define RIB_BASIS 326
#define RIB_PATCH 327
#define RIB_PATCH_MESH 328
#define RIB_NU_PATCH 329
#define RIB_TRIM_CURVE 330
#define RIB_SPHERE 331
#define RIB_CONE 332
#define RIB_CYLINDER 333
#define RIB_HYPERBOLOID 334
#define RIB_PARABOLOID 335
#define RIB_DISK 336
#define RIB_TORUS 337
#define RIB_CURVES 338
#define RIB_GEOMETRY 339
#define RIB_POINTS 340
#define RIB_SUBDIVISION_MESH 341
#define RIB_BLOBBY 342
#define RIB_PROCEDURAL 343
#define RIB_SOLID_BEGIN 344
#define RIB_SOLID_END 345
#define RIB_OBJECT_BEGIN 346
#define RIB_OBJECT_END 347
#define RIB_OBJECT_INSTANCE 348
#define RIB_MOTION_BEGIN 349
#define RIB_MOTION_END 350
#define RIB_MAKE_TEXTURE 351
#define RIB_MAKE_TEXTURE3D 352
#define RIB_MAKE_BUMP 353
#define RIB_MAKE_LAT_LONG_ENVIRONMENT 354
#define RIB_MAKE_CUBE_FACE_ENVIRONMENT 355
#define RIB_MAKE_SHADOW 356
#define RIB_ARCHIVE_RECORD 357
#define RIB_ERROR_HANDLER 358
#define RIB_VERSION 359
#define RIB_VERSION_STRING 360
#define RIB_ARRAY_BEGIN 361
#define RIB_ARRAY_END 362
#define RIB_TEXT 363
#define RIB_IDENTIFIER 364
#define RIB_FLOAT 365
#define RIB_STRUCTURE_COMMENT 366




/* Copy the first part of user declarations.  */
#line 1 "rib.y"

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
//  File				:	rib.y
//  Classes				:	-
//  Description			:	RIB bindings
//
////////////////////////////////////////////////////////////////////////
#undef alloca
#define	YYMAXDEPTH	100000


#include "common/global.h"
#include "common/containers.h"
#include "common/os.h"
#include "ri.h"
#include "renderer.h"
#include "delayed.h"
#include "stats.h"
#include "rib.h"
#include "error.h"

#include <math.h>
#include <string.h>
#include <stdarg.h>


#ifdef HAVE_ZLIB
#include <zlib.h>
#endif



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 57 "rib.y"
typedef union ribval {
	float	real;
	char	string[2048];
	int		integer;
} YYSTYPE;
/* Line 190 of yacc.c.  */
#line 368 "rib.cpp"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */
#line 63 "rib.y"

// Some forward definitions
		int						riblex(ribval*);				// Forward definition for stupid yacc
		void					riberror(char *,...);

// Types for the data encountered in the rib file
// Note that there's no type for integer as they are recovered from floats
typedef enum {
	RT_FLOAT,
	RT_TEXT,
	RT_STAR,
	RT_PL,
	RT_NULL
} ERIBType;

// Every command has an argument list composed of this type
typedef union {
	ERIBType	type;
	float		real;
	int			integer;
	char		*string;
} ERIBValue;

// Holds information about a parameter
typedef struct {
	char		*name;			// Name of the parameter
	ERIBType	type;			// Type of the parameter
	int			numItems;		// Number of items of type ERIBValue
	ERIBValue	*values;		// Points to the array of values for this parameter
	int			valuesStart;	// Index in the argument list where the parameter starts
} TParameter;

static	int					ribDepth					=	0;		// The rib parsing stack depth
static	int					numConstant					=	0;		// The number of constant
static	int					numVertex					=	0;		// The number of vertices
static	int					numVarying					=	0;		// The number of varyings
static	int					numFaceVarying				=	0;		// The number of facevaryings
static	int					numUniform					=	0;		// The number of uniforms
static	CArray<RtPointer>	*lights						=	NULL;	// Number -> handle mapping for lights
static	CTrie<RtPointer>	*lightNames					=	NULL;	// Name -> handle mapping for lights
static	CArray<RtPointer>	*ribObjects					=	NULL;	// Number -> handle mapping for ribObjects
static	CArray<char *>		*allocatedStrings			=	NULL;	// Strings that have been allocated for the last command
static	CArray<char *>		*permaStrings				=	NULL;	// Strings that have been allocated for the whole rib stack
static	void				(*callback)(const char *)	=	NULL;	// The callback function for the parser
static	ERIBValue			*args						=	NULL;
static	int					numArguments				=	0;
static	int					argumentStepSize			=	100000;
static	int					maxArgument					=	0;
static	int					numParameters				=	0;
static	int					maxParameter				=	0;
static	RtToken				*tokens						=	NULL;
static	RtPointer			*vals						=	NULL;
static	TParameter			*parameters					=	NULL;

		const char			*ribFile					=	NULL;	// The RIB file that we're parsing now
		int					ribLineno					=	-1;		// The line number in the rib file (where the parser is at)
		int					ribCommandLineno			=	-1;		// The line number of the last executed command in the RIB


#define	argCheck()															\
	if (numArguments == maxArgument) {										\
		ERIBValue	*tmp	=	new ERIBValue[maxArgument+argumentStepSize];\
																			\
		memcpy(tmp,args,numArguments*sizeof(ERIBValue));					\
																			\
		maxArgument			+=	argumentStepSize;							\
		argumentStepSize	*=	2;											\
																			\
		delete [] args;														\
		args				=	tmp;										\
	}

#define	paramCheck()														\
	if (numParameters == maxParameter) {									\
		RtToken		*tmpTokens		=	new RtToken[maxParameter+10];		\
		RtPointer	*tmpVals		=	new RtPointer[maxParameter+10];		\
		TParameter	*tmpParameters	=	new TParameter[maxParameter+10];	\
																			\
		memcpy(tmpTokens,		tokens,maxParameter*sizeof(RtToken));		\
		memcpy(tmpVals,			vals,maxParameter*sizeof(RtPointer));		\
		memcpy(tmpParameters,	parameters,maxParameter*sizeof(TParameter));\
																			\
		delete [] tokens;													\
		delete [] vals;														\
		delete [] parameters;												\
																			\
		tokens						=	tmpTokens;							\
		vals						=	tmpVals;							\
		parameters					=	tmpParameters;						\
																			\
		maxParameter				+=	10;									\
	}

#define	get(__n)		(args + __n)


// Some textual descriptions for the rib-ri parser

// Basis functions
const	char	*RI_BEZIERBASIS				=	"bezier";
const	char	*RI_BSPLINEBASIS			=	"b-spline";
const	char	*RI_POWERBASIS				=	"power";
const	char	*RI_CATMULLROMBASIS			=	"catmull-rom";
const	char	*RI_HERMITEBASIS			=	"hermite";

// Error handlers
const	char	*RI_ERRORIGNORE				=	"ignore";
const	char	*RI_ERRORPRINT				=	"print";
const	char	*RI_ERRORABORT				=	"abort";

// Predefined procedural handlers
const	char	*RI_PROCDELAYEDREADARCHIVE	=	"DelayedReadArchive";
const	char	*RI_PROCRUNPROGRAM			=	"RunProgram";
const	char	*RI_PROCDYNAMICLOAD			=	"DynamicLoad";

// Predefined error handlers
const	char	*RI_ERROR_IGNORE			=	"ignore";
const	char	*RI_ERROR_ABORT				=	"abort";
const	char	*RI_ERROR_PRINT				=	"print";

void	test();

///////////////////////////////////////////////////////////////////////
// Function				:	toLowerCase
// Description			:	Convert the argument to lowercase
// Return Value			:	Pointer to the argument
// Comments				:
// Date last edited		:	8/10/2001
static	char			*toLowerCase(char *s) {
	int	i;
	int	l	=	strlen(s);

	for (i=0;i<l;i++) {
		if ((s[i] >= 'A') && (s[i] <= 'Z'))
			s[i]	=	'a'+s[i]-'A';
	}

	return s;
}


///////////////////////////////////////////////////////////////////////
// Function				:	parameterListCheck
// Description			:	Count the number of variables inb the parameter list
// Return Value			:	TRUE if OK
// Comments				:	(This version is used by the primitives)
// Date last edited		:	8/10/2001
static	int		parameterListCheck() {
	int			i;
	CVariable	tmp;

	// Set the number of variables
	numConstant		=	0;
	numVertex		=	0;
	numVarying		=	0;
	numFaceVarying	=	0;
	numUniform		=	0;

	// For each parameter encountered
	for (i=0;i<numParameters;i++) {
		TParameter		*par	=	parameters+i;
		CVariable		*var	=	currentRenderer->retrieveVariable(par->name);
		EVariableClass	container;

		// Get the variable container to check the number of items
		if (var == NULL) {
			if (parseVariable(&tmp,NULL,par->name)) {
				// We have an inline declaration, use that container
				container	=	tmp.container;
				var			=	&tmp;
			} else {
				if (FALSE) { 	// If we want to go through the shader parameters (performance hit)
					// Not global, not inline, check the shaders
					CAttributes	*attributes	=	currentRenderer->getAttributes(FALSE);
					var						=	attributes->findParameter(par->name);
					
					if (var != NULL) {
						container	=	var->container;
					} else {
						// This isn't a globally declared variable
						// Neither is it an inline delcaration
						error(CODE_BADTOKEN,"Parameter \"%s\" is not declared.\n",par->name);
						return FALSE;
					}
				} else {
					// This isn't a globally declared variable
					// Neither is it an inline delcaration
					error(CODE_BADTOKEN,"Parameter \"%s\" is not declared.\n",par->name);
					return FALSE;
				}
			}
		} else {
			// This variable is predeclared.  It may or may not be a global though
			container	=	var->container;
		}

		// Handle some irregular cases
		if (var == NULL) {
			// Special symbols
			if (strcmp(par->name,"Pz") == 0) {
				tmp.numFloats	=	1;
				tmp.numItems	=	1;
				tmp.entry		=	VARIABLE_P;
				strcpy(tmp.name,"Pz");
				tmp.type		=	TYPE_FLOAT;
				tmp.container	=	CONTAINER_VERTEX;
				tmp.usageMarker	=	PARAMETER_P;
				var				=	&tmp;
				container		=	var->container;
			} else if (strcmp(par->name,"Np") == 0) {
				tmp.numFloats	=	3;
				tmp.numItems	=	1;
				tmp.entry		=	VARIABLE_NG;
				strcpy(tmp.name,"Np");
				tmp.type		=	TYPE_NORMAL;
				tmp.container	=	CONTAINER_VERTEX;
				tmp.usageMarker	=	PARAMETER_NG;
				var				=	&tmp;
				container		=	var->container;
			} else if (strcmp(par->name,"Pw") == 0) {
				tmp.numFloats	=	4;
				tmp.numItems	=	1;
				tmp.entry		=	VARIABLE_P;
				strcpy(tmp.name,"Pw");
				tmp.type		=	TYPE_POINT;
				tmp.container	=	CONTAINER_VERTEX;
				tmp.usageMarker	=	PARAMETER_P;
				var				=	&tmp;
				container		=	var->container;
			}
		}	

		if (var == NULL)	{
			error(CODE_BADTOKEN,"Parameter \"%s\" is not declared\n",par->name);
			return FALSE;
		}

		if ((par->numItems % var->numFloats) != 0) {
			error(CODE_MISSINGDATA,"Invalid number of items for the parameter \"%s\" (expecting n*%d, found %d)\n",par->name,var->numFloats,par->numItems);
			return FALSE;
		}

		// Type checking
		if (var->type == TYPE_INTEGER) {
			if (par->type == RT_FLOAT) {
				int	j;

				for (j=0;j<par->numItems;j++) {
					par->values[j].integer	=	(int) par->values[j].real;
				}
			} else {
				error(CODE_RANGE,"Type mismatch for parameter \"%s\" (expecting integer, found string)\n",par->name);
				return	FALSE;
			}
		} else if (var->type == TYPE_STRING) {
			if (par->type != RT_TEXT) {
				error(CODE_RANGE,"Type mismatch for parameter \"%s\" (expecting string, found float)\n",par->name);
				return	FALSE;
			}
		} else {
			if (par->type != RT_FLOAT) {
				error(CODE_RANGE,"Type mismatch for parameter \"%s\" (expecting float, found string)\n",par->name);
				return	FALSE;
			}
		}

#define	SIZECHECK(dest)																		\
			if (dest == 0) {																\
				dest = (par->numItems / var->numFloats);									\
			} else {																		\
				if (dest != (par->numItems / var->numFloats)) {								\
					error(CODE_RANGE,"Invalid number of items for the parameter \"%s\" (expecting %d, found %d)\n",par->name,dest,par->numItems/var->numFloats);	\
					return FALSE;															\
				}																			\
			}

		switch(container) {
		case CONTAINER_UNIFORM:
			SIZECHECK(numUniform);
			break;
		case CONTAINER_VERTEX:
			SIZECHECK(numVertex);
			break;
		case CONTAINER_VARYING:
			SIZECHECK(numVarying);
			break;
		case CONTAINER_FACEVARYING:
			SIZECHECK(numFaceVarying);
			break;
		case CONTAINER_CONSTANT:
			SIZECHECK(numConstant);
			break;
		default:
			error(CODE_BUG,"Unknown container class in parameter list.\n");
			return FALSE;
			break;
		}

#undef SIZECHECK

	}

	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// Function				:	getBasis
// Description			:	Get the basis matrix from a given text
// Return Value			:	TRUE if OK
// Comments				:
// Date last edited		:	8/20/2003
static	int		sizeCheck(int numExpVertex,int numExpVarying,int numExpFaceVarying,int numExpUniform) {
	if (numExpVarying == 0)		numExpVarying		=	numExpVertex;
	if (numExpVertex == 0)		numExpVertex		=	numExpVarying;
	if (numExpFaceVarying == 0)	numExpFaceVarying	=	numExpVertex;

	if (numConstant != 0) {
		if (numConstant != 1) {
			error(CODE_CONSISTENCY,"Unexpected number of constants (1 expected, %d found)\n",numVarying);
			return FALSE;
		}
	}

	if (numVertex != 0) {
		if (numExpVertex != numVertex) {
			error(CODE_CONSISTENCY,"Unexpected number of vertices (%d expected, %d found)\n",numExpVertex,numVertex);
			return FALSE;
		}
	}

	if (numVarying != 0) {
		if (numExpVarying != numVarying) {
			error(CODE_CONSISTENCY,"Unexpected number of varyings (%d expected, %d found)\n",numExpVarying,numVarying);
			return FALSE;
		}
	}

	if (numFaceVarying != 0) {
		if (numExpFaceVarying != numFaceVarying) {
			error(CODE_CONSISTENCY,"Unexpected number of facevaryings (%d expected, %d found)\n",numExpFaceVarying,numFaceVarying);
			return FALSE;
		}
	}

	if (numUniform != 0) {
		if (numExpUniform != numUniform) {
			error(CODE_CONSISTENCY,"Unexpected number of uniforms (%d expected, %d found)\n",numExpUniform,numUniform);
			return FALSE;
		}
	}

	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// Function				:	getBasis
// Description			:	Get the basis matrix from a given text
// Return Value			:	TRUE if OK
// Comments				:
// Date last edited		:	8/10/2001
static	int		getBasis(RtBasis **a,char *n) {
	char	*name	=	toLowerCase(n);

	if (strcmp(name,RI_BEZIERBASIS) == 0)
		a[0]	=	&RiBezierBasis;
	else if (strcmp(name,RI_BSPLINEBASIS) == 0)
		a[0]	=	&RiBSplineBasis;
	else if (strcmp(name,RI_CATMULLROMBASIS) == 0)
		a[0]	=	&RiCatmullRomBasis;
	else if (strcmp(name,RI_HERMITEBASIS) == 0)
		a[0]	=	&RiHermiteBasis;
	else if (strcmp(name,RI_POWERBASIS) == 0)
		a[0]	=	&RiPowerBasis;
	else {
		error(CODE_BADTOKEN,"Unknown basis: \"%s\"\n",name);
		return	FALSE;
	}

	return	TRUE;
}

///////////////////////////////////////////////////////////////////////
// Function				:	getFilter
// Description			:	Get the filter from a given text
// Return Value			:	NULL if failed
// Comments				:
// Date last edited		:	8/10/2001
static	RtFilterFunc	getFilter(char *n) {
	char			*name	=	toLowerCase(n);
	RtFilterFunc	f		=	NULL;

	if (strcmp(name,RI_BOXFILTER) == 0) {
		f = RiBoxFilter;
	} else if (strcmp(name,RI_GAUSSIANFILTER) == 0) {
		f = RiGaussianFilter;
	} else if (strcmp(name,RI_TRIANGLEFILTER) == 0) {
		f = RiTriangleFilter;
	} else if (strcmp(name,RI_CATMULLROMFILTER) == 0) {
		f = RiCatmullRomFilter;
	} else if (strcmp(name,RI_SINCFILTER) == 0) {
		f = RiSincFilter;
	} else {
		error(CODE_BADTOKEN,"Filter \"%s\" not recognised\n",name);
	}

	return f;
}

///////////////////////////////////////////////////////////////////////
// Function				:	getError
// Description			:	Get the error handler from a given text
// Return Value			:	NULL if failed
// Comments				:
// Date last edited		:	8/10/2001
static	RtErrorHandler	getErrorHandler(char *n) {
	char			*name	=	toLowerCase(n);
	RtErrorHandler	f		=	NULL;

	if (strcmp(name,RI_ERRORIGNORE) == 0) {
		f = RiErrorPrint;
	} else if (strcmp(name,RI_ERRORPRINT) == 0) {
		f = RiErrorPrint;
	} else if (strcmp(name,RI_ERRORABORT) == 0) {
		f = RiErrorAbort;
	} else {
		error(CODE_BADTOKEN,"Error handler \"%s\" not recognised\n",name);
	}

	return f;
}




/* Line 213 of yacc.c.  */
#line 813 "rib.cpp"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

# ifndef YYFREE
#  define YYFREE free
# endif
# ifndef YYMALLOC
#  define YYMALLOC malloc
# endif

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   else
#    define YYSTACK_ALLOC alloca
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short int yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short int) + sizeof (YYSTYPE))			\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short int yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   676

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  112
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  16
/* YYNRULES -- Number of rules. */
#define YYNRULES  157
/* YYNRULES -- Number of states. */
#define YYNSTATES  651

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   366

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    13,    15,    18,    20,
      24,    27,    29,    31,    35,    38,    42,    44,    47,    49,
      51,    54,    55,    58,    61,    62,    66,    67,    69,    73,
      75,    78,    80,    82,    84,    89,    92,    98,   106,   112,
     120,   124,   128,   136,   141,   143,   147,   150,   154,   159,
     163,   167,   174,   180,   184,   188,   191,   195,   198,   202,
     204,   206,   211,   216,   223,   230,   240,   252,   257,   262,
     266,   271,   276,   280,   284,   288,   292,   296,   300,   303,
     306,   309,   319,   327,   337,   345,   351,   359,   363,   366,
     369,   371,   374,   376,   396,   416,   419,   424,   429,   435,
     444,   455,   459,   463,   466,   469,   471,   473,   477,   480,
     484,   489,   495,   501,   524,   547,   587,   591,   599,   612,
     623,   630,   639,   645,   653,   660,   669,   679,   691,   698,
     707,   713,   721,   729,   739,   745,   748,   758,   764,   770,
     774,   786,   789,   791,   794,   796,   799,   802,   804,   814,
     819,   829,   837,   851,   856,   859,   862,   865
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const yysigned_char yyrhs[] =
{
     113,     0,    -1,   125,    -1,   114,   110,    -1,   110,    -1,
     115,   110,    -1,   110,    -1,   116,   108,    -1,   108,    -1,
     106,   115,   107,    -1,   106,   107,    -1,   117,    -1,   115,
      -1,   106,   114,   107,    -1,   106,   107,    -1,   106,   116,
     107,    -1,   108,    -1,   106,   107,    -1,   121,    -1,   120,
      -1,   124,   123,    -1,    -1,   108,   118,    -1,   108,   120,
      -1,    -1,   125,   126,   127,    -1,    -1,   111,    -1,     3,
     108,   108,    -1,     4,    -1,     4,   110,    -1,     5,    -1,
       6,    -1,     7,    -1,     8,   110,   110,   110,    -1,     9,
     110,    -1,    10,   110,   110,   110,   110,    -1,    10,   106,
     110,   110,   110,   110,   107,    -1,    11,   110,   110,   110,
     110,    -1,    11,   106,   110,   110,   110,   110,   107,    -1,
      12,   108,   123,    -1,    13,   110,   110,    -1,    14,   110,
     110,   110,   110,   110,   110,    -1,    15,   110,   110,   110,
      -1,    15,    -1,    16,   110,   110,    -1,    17,   110,    -1,
      18,   110,   110,    -1,    19,   108,   110,   110,    -1,    20,
     110,   110,    -1,    21,   108,   123,    -1,    22,   108,   110,
     110,   110,   110,    -1,    23,   108,   108,   108,   123,    -1,
      24,   108,   123,    -1,    25,   108,   123,    -1,    26,   118,
      -1,    26,   117,   117,    -1,    27,   110,    -1,    28,   108,
     123,    -1,    29,    -1,    30,    -1,    31,   110,   110,   110,
      -1,    32,   110,   110,   110,    -1,    31,   106,   110,   110,
     110,   107,    -1,    32,   106,   110,   110,   110,   107,    -1,
      33,   110,   110,   110,   110,   110,   110,   110,   110,    -1,
      33,   106,   110,   110,   110,   110,   110,   110,   110,   110,
     107,    -1,    34,   108,   110,   123,    -1,    34,   108,   108,
     123,    -1,    34,   108,   123,    -1,    35,   108,   110,   123,
      -1,    35,   108,   108,   123,    -1,    36,   110,   110,    -1,
      36,   108,   110,    -1,    37,   108,   123,    -1,    38,   108,
     123,    -1,    39,   108,   123,    -1,    40,   108,   123,    -1,
      41,   110,    -1,    42,   108,    -1,    43,   110,    -1,    44,
     106,   110,   110,   110,   110,   110,   110,   107,    -1,    44,
     110,   110,   110,   110,   110,   110,    -1,    45,   106,   110,
     110,   110,   110,   110,   110,   107,    -1,    45,   110,   110,
     110,   110,   110,   110,    -1,    46,   110,   110,   110,   110,
      -1,    46,   106,   110,   110,   110,   110,   107,    -1,    47,
     108,   110,    -1,    48,   108,    -1,    49,   108,    -1,    50,
      -1,    51,   110,    -1,    52,    -1,    53,   106,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   107,    -1,    54,   106,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   107,    -1,    55,   110,    -1,    56,
     110,   110,   110,    -1,    58,   110,   110,   110,    -1,    57,
     110,   110,   110,   110,    -1,    59,   110,   110,   110,   110,
     110,   110,   110,    -1,    59,   106,   110,   110,   110,   110,
     110,   110,   110,   107,    -1,    60,   108,   123,    -1,    61,
     108,   123,    -1,    62,   108,    -1,    63,   108,    -1,    64,
      -1,    65,    -1,    66,   108,   123,    -1,    67,   123,    -1,
      68,   119,   123,    -1,    69,   119,   119,   123,    -1,    70,
     119,   119,   119,   123,    -1,    71,   108,   110,   108,   110,
      -1,    71,   106,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   107,
     110,   108,   110,    -1,    71,   108,   110,   106,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   107,   110,    -1,    71,   106,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   107,   110,   106,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   107,   110,    -1,    72,   108,   123,
      -1,    73,   108,   110,   108,   110,   108,   123,    -1,    74,
     110,   110,   117,   110,   110,   110,   110,   117,   110,   110,
     123,    -1,    75,   117,   117,   117,   117,   117,   117,   117,
     117,   117,    -1,    76,   110,   110,   110,   110,   123,    -1,
      76,   106,   110,   110,   110,   110,   107,   123,    -1,    77,
     110,   110,   110,   123,    -1,    77,   106,   110,   110,   110,
     107,   123,    -1,    78,   110,   110,   110,   110,   123,    -1,
      78,   106,   110,   110,   110,   110,   107,   123,    -1,    79,
     110,   110,   110,   110,   110,   110,   110,   123,    -1,    79,
     106,   110,   110,   110,   110,   110,   110,   110,   107,   123,
      -1,    80,   110,   110,   110,   110,   123,    -1,    80,   106,
     110,   110,   110,   110,   107,   123,    -1,    81,   110,   110,
     110,   123,    -1,    81,   106,   110,   110,   110,   107,   123,
      -1,    82,   110,   110,   110,   110,   110,   123,    -1,    82,
     106,   110,   110,   110,   110,   110,   107,   123,    -1,    83,
     108,   119,   108,   123,    -1,    85,   123,    -1,    86,   108,
     119,   119,   122,   119,   119,   117,   123,    -1,    86,   108,
     119,   119,   123,    -1,    87,   110,   117,   120,   123,    -1,
      84,   108,   123,    -1,    88,   108,   120,   106,   110,   110,
     110,   110,   110,   110,   107,    -1,    89,   108,    -1,    90,
      -1,    91,   110,    -1,    92,    -1,    93,   110,    -1,    94,
     118,    -1,    95,    -1,    96,   108,   108,   108,   108,   108,
     110,   110,   123,    -1,    97,   108,   108,   123,    -1,    98,
     108,   108,   108,   108,   108,   110,   110,   123,    -1,    99,
     108,   108,   108,   110,   110,   123,    -1,   100,   108,   108,
     108,   108,   108,   108,   108,   110,   108,   110,   110,   123,
      -1,   101,   108,   108,   123,    -1,   103,   108,    -1,   104,
     110,    -1,   104,   105,    -1,     1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   616,   616,   619,   627,   636,   644,   652,   662,   672,
     679,   687,   692,   698,   705,   713,   720,   731,   736,   741,
     748,   753,   772,   784,   798,   797,   811,   815,   822,   829,
     834,   840,   845,   850,   855,   863,   869,   878,   889,   898,
     909,   916,   923,   934,   942,   947,   954,   960,   967,   979,
     986,   996,  1006,  1015,  1022,  1031,  1045,  1060,  1066,  1075,
    1080,  1085,  1099,  1113,  1129,  1145,  1158,  1173,  1183,  1195,
    1202,  1212,  1224,  1233,  1245,  1252,  1259,  1266,  1273,  1279,
    1285,  1291,  1313,  1333,  1355,  1375,  1384,  1395,  1402,  1408,
    1414,  1419,  1425,  1430,  1472,  1514,  1520,  1528,  1536,  1545,
    1557,  1571,  1578,  1585,  1591,  1597,  1602,  1607,  1616,  1626,
    1639,  1675,  1719,  1732,  1781,  1830,  1909,  1935,  2011,  2044,
    2068,  2082,  2098,  2111,  2126,  2140,  2156,  2182,  2210,  2224,
    2240,  2253,  2268,  2283,  2300,  2346,  2356,  2394,  2422,  2431,
    2440,  2509,  2515,  2520,  2528,  2533,  2543,  2551,  2556,  2573,
    2581,  2598,  2613,  2634,  2642,  2652,  2657,  2662
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "RIB_DECLARE", "RIB_FRAME_BEGIN",
  "RIB_FRAME_END", "RIB_WORLD_BEGIN", "RIB_WORLD_END", "RIB_FORMAT",
  "RIB_FRAME_ASPECT_RATIO", "RIB_SCREEN_WINDOW", "RIB_CROP_WINDOW",
  "RIB_PROJECTION", "RIB_CLIPPING", "RIB_CLIPPING_PLANE",
  "RIB_DEPTH_OF_FIELD", "RIB_SHUTTER", "RIB_PIXEL_VARIANCE",
  "RIB_PIXEL_SAMPLES", "RIB_PIXEL_FILTER", "RIB_EXPOSURE", "RIB_IMAGER",
  "RIB_QUANTIZE", "RIB_DISPLAY", "RIB_DISPLAYCHANNEL", "RIB_HIDER",
  "RIB_COLOR_SAMPLES", "RIB_RELATIVE_DETAIL", "RIB_OPTION",
  "RIB_ATTRIBUTE_BEGIN", "RIB_ATTRIBUTE_END", "RIB_COLOR", "RIB_OPACITY",
  "RIB_TEXTURE_COORDINATES", "RIB_LIGHT_SOURCE", "RIB_AREA_LIGHT_SOURCE",
  "RIB_ILLUMINATE", "RIB_SURFACE", "RIB_ATMOSPHERE", "RIB_INTERIOR",
  "RIB_EXTERIOR", "RIB_SHADING_RATE", "RIB_SHADING_INTERPOLATION",
  "RIB_MATTE", "RIB_BOUND", "RIB_DETAIL", "RIB_DETAIL_RANGE",
  "RIB_GEOMETRIC_APPROXIMATION", "RIB_GEOMETRIC_REPRESENTATION",
  "RIB_ORIENTATION", "RIB_REVERSE_ORIENTATION", "RIB_SIDES",
  "RIB_IDENTITY", "RIB_TRANSFORM", "RIB_CONCAT_TRANSFORM",
  "RIB_PERSPECTIVE", "RIB_TRANSLATE", "RIB_ROTATE", "RIB_SCALE",
  "RIB_SKEW", "RIB_DEFORMATION", "RIB_DISPLACEMENT",
  "RIB_COORDINATE_SYSTEM", "RIB_COORDINATE_SYS_TRANSFORM",
  "RIB_TRANSFORM_BEGIN", "RIB_TRANSFORM_END", "RIB_ATTRIBUTE",
  "RIB_POLYGON", "RIB_GENERAL_POLYGON", "RIB_POINTS_POLYGONS",
  "RIB_POINTS_GENERAL_POLYGONS", "RIB_BASIS", "RIB_PATCH",
  "RIB_PATCH_MESH", "RIB_NU_PATCH", "RIB_TRIM_CURVE", "RIB_SPHERE",
  "RIB_CONE", "RIB_CYLINDER", "RIB_HYPERBOLOID", "RIB_PARABOLOID",
  "RIB_DISK", "RIB_TORUS", "RIB_CURVES", "RIB_GEOMETRY", "RIB_POINTS",
  "RIB_SUBDIVISION_MESH", "RIB_BLOBBY", "RIB_PROCEDURAL",
  "RIB_SOLID_BEGIN", "RIB_SOLID_END", "RIB_OBJECT_BEGIN", "RIB_OBJECT_END",
  "RIB_OBJECT_INSTANCE", "RIB_MOTION_BEGIN", "RIB_MOTION_END",
  "RIB_MAKE_TEXTURE", "RIB_MAKE_TEXTURE3D", "RIB_MAKE_BUMP",
  "RIB_MAKE_LAT_LONG_ENVIRONMENT", "RIB_MAKE_CUBE_FACE_ENVIRONMENT",
  "RIB_MAKE_SHADOW", "RIB_ARCHIVE_RECORD", "RIB_ERROR_HANDLER",
  "RIB_VERSION", "RIB_VERSION_STRING", "RIB_ARRAY_BEGIN", "RIB_ARRAY_END",
  "RIB_TEXT", "RIB_IDENTIFIER", "RIB_FLOAT", "RIB_STRUCTURE_COMMENT",
  "$accept", "start", "ribIntString", "ribFloatString", "ribTextString",
  "ribFloatArray", "ribFloats", "ribIntArray", "ribTextArray",
  "ribEmptyArray", "ribTexts", "ribPL", "ribParameter", "ribCommands",
  "@1", "ribComm", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short int yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,   112,   113,   114,   114,   115,   115,   116,   116,   117,
     117,   118,   118,   119,   119,   120,   120,   121,   122,   122,
     123,   123,   124,   124,   126,   125,   125,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     2,     1,     2,     1,     2,     1,     3,
       2,     1,     1,     3,     2,     3,     1,     2,     1,     1,
       2,     0,     2,     2,     0,     3,     0,     1,     3,     1,
       2,     1,     1,     1,     4,     2,     5,     7,     5,     7,
       3,     3,     7,     4,     1,     3,     2,     3,     4,     3,
       3,     6,     5,     3,     3,     2,     3,     2,     3,     1,
       1,     4,     4,     6,     6,     9,    11,     4,     4,     3,
       4,     4,     3,     3,     3,     3,     3,     3,     2,     2,
       2,     9,     7,     9,     7,     5,     7,     3,     2,     2,
       1,     2,     1,    19,    19,     2,     4,     4,     5,     8,
      10,     3,     3,     2,     2,     1,     1,     3,     2,     3,
       4,     5,     5,    22,    22,    39,     3,     7,    12,    10,
       6,     8,     5,     7,     6,     8,     9,    11,     6,     8,
       5,     7,     7,     9,     5,     2,     9,     5,     5,     3,
      11,     2,     1,     2,     1,     2,     2,     1,     9,     4,
       9,     7,    13,     4,     2,     2,     2,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
      26,     0,    24,     1,     0,   157,     0,    29,    31,    32,
      33,     0,     0,     0,     0,     0,     0,     0,    44,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    59,    60,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    90,     0,    92,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   105,   106,     0,
      21,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    21,     0,
       0,     0,     0,   142,     0,   144,     0,     0,   147,     0,
       0,     0,     0,     0,     0,     0,     0,    27,    25,     0,
      30,     0,    35,     0,     0,     0,     0,    21,     0,     0,
       0,     0,    46,     0,     0,     0,    21,     0,     0,    21,
      21,     0,     6,    12,    11,    55,    57,    21,     0,     0,
       0,     0,     0,     0,    21,     0,     0,     0,    21,    21,
      21,    21,    78,    79,    80,     0,     0,     0,     0,     0,
       0,     0,    88,    89,    91,     0,     0,    95,     0,     0,
       0,     0,     0,    21,    21,   103,   104,    21,     0,   108,
      21,     0,    21,     0,     0,     0,     0,    21,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    21,   135,     0,     0,
       0,   141,   143,   145,    11,   146,     0,     0,     0,     0,
       0,     0,   154,   156,   155,    28,     0,     0,     0,     0,
       0,    40,    41,     0,     0,    45,    47,     0,    49,    50,
       0,     0,    53,    54,    10,     0,     5,    56,    58,     0,
       0,     0,     0,     0,     0,    21,    21,    69,    21,    21,
      73,    72,    74,    75,    76,    77,     0,     0,     0,     0,
       0,     0,    87,     0,     0,     0,     0,     0,     0,     0,
     101,   102,   107,     0,    16,    22,    23,    20,    14,     4,
       0,   109,    21,     0,     0,     0,   116,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   139,     0,     0,     0,     0,
       0,    21,     0,     0,     0,    21,    34,     0,     0,     0,
       0,     0,    43,    48,     0,    21,     9,     0,    61,     0,
      62,     0,     0,    16,    68,    67,    71,    70,     0,     0,
       0,     0,     0,     0,     0,     0,    96,     0,    97,     0,
       0,     8,     0,    13,     3,   110,    21,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    21,     0,     0,     0,
       0,     0,     0,     0,    21,     0,     0,    21,    21,    21,
       0,     0,   149,     0,     0,     0,   153,     0,    36,     0,
      38,     0,     0,    52,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    85,     0,     0,    98,     0,     0,    15,
       7,   111,     0,     0,   112,     0,     0,     0,     0,    21,
       0,   122,     0,    21,     0,     0,     0,    21,     0,   130,
       0,     0,   134,     0,    19,    18,     0,   137,   138,     0,
       0,     0,     0,     0,     0,     0,     0,    51,    63,    64,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    21,     0,     0,     0,   120,    21,     0,
     124,     0,     0,     0,   128,    21,     0,    21,    17,     0,
       0,     0,     0,    21,     0,    37,    39,    42,     0,     0,
       0,    82,     0,    84,    86,     0,     0,     0,     0,     0,
       0,   117,     0,     0,    21,   123,    21,     0,     0,    21,
     131,     0,   132,     0,     0,     0,     0,   151,     0,     0,
       0,     0,     0,     0,     0,     0,    99,     0,     0,     0,
       0,   121,   125,     0,    21,   129,    21,    21,     0,    21,
      21,     0,     0,    65,    81,    83,     0,     0,     0,     0,
       0,     0,     0,     0,   126,   133,   136,     0,   148,   150,
       0,     0,     0,     0,   100,     0,     0,     0,   119,    21,
       0,     0,    66,     0,     0,     0,     0,    21,   127,   140,
       0,     0,     0,     0,     0,   118,    21,     0,     0,     0,
       0,   152,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    93,    94,     0,     0,     0,     0,     0,     0,
       0,     0,   113,   114,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     115
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     1,   290,   133,   362,   214,   285,   182,   286,   445,
     446,   179,   180,     2,     4,   108
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -208
static const short int yypact[] =
{
    -208,    22,    58,  -208,   531,  -208,   -17,   -32,  -208,  -208,
    -208,   -10,    -8,   -91,   -89,    -4,    -2,     1,     4,     5,
       6,     7,    10,     9,    12,    13,    15,    16,    17,   -86,
      18,    19,  -208,  -208,   -83,   -81,   -80,    21,    23,  -100,
      24,    25,    27,    28,    20,    30,    29,   -78,   -75,   -72,
      32,    33,    34,  -208,    35,  -208,     3,    37,    36,    38,
      39,    40,   -70,    43,    44,    45,    46,  -208,  -208,    47,
      48,    41,    41,    41,   -25,    50,    51,    52,    54,   -69,
     -67,   -62,   -59,   -56,   -54,   -51,    55,    56,    48,    57,
      59,    60,    62,  -208,    63,  -208,    66,   -86,  -208,    69,
      70,    71,    74,    75,    76,    77,   -98,  -208,  -208,    78,
    -208,    79,  -208,    80,    81,    82,    83,    48,    84,    85,
      86,    87,  -208,    88,    89,    90,    48,    91,    94,    48,
      48,   -37,  -208,    93,    54,  -208,  -208,    48,    95,    96,
      97,    99,   100,   101,   -26,   -22,   102,   103,    48,    48,
      48,    48,  -208,  -208,  -208,   104,   105,   106,   107,   108,
     109,   110,  -208,  -208,  -208,   111,   113,  -208,   114,   115,
     116,   117,   118,    48,    48,  -208,  -208,    48,   -97,  -208,
      48,   -35,    48,    41,    41,   119,   120,    48,   121,   122,
      54,   123,   124,   125,   126,   128,   129,   130,   132,   133,
     134,   136,   137,   138,   139,    41,    48,  -208,    41,    54,
     -21,  -208,  -208,  -208,  -208,  -208,   142,   144,   145,   146,
     147,   148,  -208,  -208,  -208,  -208,   149,   150,   151,   152,
     153,  -208,  -208,   154,   155,  -208,  -208,   156,  -208,  -208,
     157,   160,  -208,  -208,  -208,   -31,  -208,  -208,  -208,   161,
     162,   163,   164,   165,   166,   -92,    48,  -208,    48,    48,
    -208,  -208,  -208,  -208,  -208,  -208,   167,   168,   169,   170,
     171,   173,  -208,   174,   175,   176,   177,   178,   179,   180,
    -208,  -208,  -208,   -39,  -208,  -208,  -208,  -208,  -208,  -208,
     -30,  -208,    48,    41,   181,   -14,  -208,   185,    54,    54,
     184,   186,   187,   188,   189,   191,   192,   196,   197,   198,
     199,   200,   201,   202,   205,  -208,    41,   -21,   206,    61,
     207,    48,   208,   209,   210,    48,  -208,   211,   212,   213,
     214,   215,  -208,  -208,   216,    48,  -208,   217,  -208,   218,
    -208,   219,   220,   -49,  -208,  -208,  -208,  -208,   221,   222,
     223,   224,   225,   226,   227,   228,  -208,   229,  -208,   230,
     231,  -208,   -45,  -208,  -208,  -208,    48,   232,   234,   236,
     237,   238,    54,   240,   241,   242,    48,   244,   245,   246,
     247,   248,   249,   250,    48,   251,   252,    48,   -11,    48,
     253,   256,  -208,   257,   258,   259,  -208,   260,  -208,   261,
    -208,   262,   263,  -208,   267,   269,   268,   270,   271,   272,
     273,   274,   275,  -208,   276,   277,  -208,   278,   280,  -208,
    -208,  -208,   281,   282,  -208,   285,   286,    54,   287,    48,
     288,  -208,   289,    48,   290,   292,   294,    48,   298,  -208,
     296,   297,  -208,    -1,  -208,  -208,    41,  -208,  -208,   300,
     303,   304,   305,   306,   301,   309,   307,  -208,  -208,  -208,
     310,   311,   312,   313,   314,   315,   319,   317,   318,   321,
     323,   324,   326,    48,   327,    54,   322,  -208,    48,   331,
    -208,   329,   330,   334,  -208,    48,   332,    48,  -208,    41,
     333,   335,   337,    48,   336,  -208,  -208,  -208,   338,   339,
     340,  -208,   341,  -208,  -208,   342,   343,   344,   345,   346,
     347,  -208,   348,    54,    48,  -208,    48,   349,   351,    48,
    -208,   357,  -208,    54,   358,   359,   360,  -208,   363,   362,
     364,   366,   368,   367,   369,   370,  -208,   371,   372,    54,
      54,  -208,  -208,   373,    48,  -208,    48,    48,   375,    48,
      48,   376,   377,  -208,  -208,  -208,   378,   379,   383,   381,
     382,   386,    54,   390,  -208,  -208,  -208,   388,  -208,  -208,
     385,   392,   391,   394,  -208,   395,   396,   397,  -208,    48,
     393,   398,  -208,   399,   403,   404,   405,    48,  -208,  -208,
     406,   407,   408,   409,   410,  -208,    48,   411,   412,   413,
     414,  -208,   415,   416,   417,   418,   419,   420,   421,   523,
     526,   527,   528,   529,   530,   533,   534,   535,   539,   540,
     541,   542,  -208,  -208,   543,   544,    -7,   548,   546,   547,
     549,   550,  -208,  -208,   551,   552,   553,   554,   555,   556,
     557,   558,   559,   560,   561,   562,   563,   564,   568,   566,
    -208
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -208,  -208,  -208,  -126,  -208,   -29,   -23,   -71,  -207,  -208,
    -208,   -84,  -208,  -208,  -208,  -208
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const short int yytable[] =
{
     134,   183,   184,   319,   207,   245,   135,   223,   146,   283,
     147,   284,   224,   132,   283,   113,   343,   115,   132,   114,
     131,   116,     3,   138,   132,   140,   142,   139,   155,   141,
     143,   157,   156,   231,   159,   158,   171,   191,   160,   193,
     172,   192,   239,   194,   195,   242,   243,   197,   196,   190,
     199,   198,   201,   248,   200,   203,   202,   283,    -2,   204,
     257,   132,   419,   420,   262,   263,   264,   265,   244,   361,
     244,   132,   288,   132,   215,   289,   336,   363,   110,   246,
     364,   185,   255,   186,   256,   318,   258,   284,   259,   280,
     281,   109,   368,   282,   369,   443,   287,   343,   291,   628,
     111,   629,   112,   296,   117,   247,   488,   361,   118,   165,
     389,   119,   292,   293,   120,   121,   122,   123,   124,   125,
     126,   127,   315,   128,   129,   130,     0,   137,   136,   144,
     152,   145,   148,   149,   314,   150,   151,   316,   153,   154,
     161,   162,   163,   166,     0,   164,   167,   181,   168,   169,
     170,   173,   174,   175,   176,   177,   178,   245,   187,   188,
     131,   299,   189,   205,   206,   208,     0,   390,   210,   209,
     211,   344,   345,   212,   346,   347,   213,   216,   217,   218,
     317,   444,   219,   220,   221,   222,   225,     0,     0,   226,
     227,   228,   229,   230,   232,   233,   234,   235,   236,   237,
     238,   240,   241,   246,     0,   249,   250,   251,   365,   252,
     253,   254,   260,   261,   266,   267,   268,   269,   270,   271,
     272,   273,   366,   274,   275,   276,   277,   278,   279,   294,
     295,   297,   298,   300,   301,   302,   303,   392,   304,   305,
     306,   396,   307,   308,   309,   388,   310,   311,   312,   313,
     320,   403,   321,   322,   323,   324,   325,     0,     0,   326,
     327,   328,   329,   330,   331,   332,   333,   334,   335,   371,
     372,   337,   338,   339,   340,   341,   342,   348,   349,   350,
     351,   352,   421,   353,   354,   355,   356,   357,   358,   359,
     360,   367,   431,   370,   373,     0,   374,   375,   376,   377,
     439,   378,   379,   442,   447,   448,   380,   381,   382,   383,
     384,   385,   386,   387,   361,   391,   393,   394,   395,     0,
       0,   397,   398,   399,   400,   401,   402,   404,   405,   406,
     407,   408,   409,   410,   411,   412,   413,   414,   415,   416,
     417,   418,   422,   427,   423,   477,   424,   425,   426,   480,
     428,   429,   430,   484,   432,   433,   434,   435,   436,   437,
     438,   440,   441,   449,   450,   451,     0,   453,   452,     0,
     454,   455,   456,   457,   458,   489,   459,     0,   460,     0,
     461,   462,   463,   464,   465,   466,   467,   468,   469,   511,
     470,   471,   472,   473,   515,   478,   474,   476,   475,   479,
     481,   520,   482,   522,   483,   485,   486,   487,   495,   527,
     490,   491,   492,     0,   494,   493,   496,   497,   523,     0,
     498,   499,   500,   501,   502,   503,   504,   505,   506,   514,
     541,   507,   542,   508,   509,   545,   510,   512,   516,   517,
     518,   519,   521,   524,   528,   525,   513,   526,   529,   530,
     531,   532,   533,   534,   535,   536,   537,   538,   539,   543,
     564,   544,   565,   566,   546,   568,   569,     0,   548,   549,
     550,   551,   552,   554,   553,   555,     0,   556,     0,   557,
     558,   559,   560,   563,   540,   567,   570,   571,   572,   573,
     574,   575,   576,   581,   547,   588,   577,   579,   580,   582,
     589,   583,     0,   595,   584,   585,   586,   587,   590,   591,
     561,   562,   601,   592,   593,   594,   596,   597,   598,   599,
     600,   602,   603,   604,   605,   606,   607,   608,   609,   610,
     611,   612,     5,   578,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   613,   105,   106,   614,   615,   616,   617,
     618,     0,   107,   619,   620,   621,   622,   623,   624,     0,
       0,     0,   625,   626,   627,   630,   631,   632,     0,   633,
     634,   635,   636,   637,   638,   639,   640,   641,   642,   643,
     644,   645,   646,   647,   648,   649,   650
};

static const short int yycheck[] =
{
      29,    72,    73,   210,    88,   131,    29,   105,   108,   106,
     110,   108,   110,   110,   106,   106,   108,   106,   110,   110,
     106,   110,     0,   106,   110,   106,   106,   110,   106,   110,
     110,   106,   110,   117,   106,   110,   106,   106,   110,   106,
     110,   110,   126,   110,   106,   129,   130,   106,   110,    78,
     106,   110,   106,   137,   110,   106,   110,   106,     0,   110,
     144,   110,   107,   108,   148,   149,   150,   151,   107,   108,
     107,   110,   107,   110,    97,   110,   107,   107,   110,   110,
     110,   106,   108,   108,   110,   106,   108,   108,   110,   173,
     174,   108,   106,   177,   108,   106,   180,   108,   182,   106,
     110,   108,   110,   187,   108,   134,   107,   108,   110,   106,
     317,   110,   183,   184,   110,   110,   110,   110,   108,   110,
     108,   108,   206,   108,   108,   108,    -1,   108,   110,   108,
     110,   108,   108,   108,   205,   108,   108,   208,   108,   110,
     108,   108,   108,   106,    -1,   110,   110,   106,   110,   110,
     110,   108,   108,   108,   108,   108,   108,   283,   108,   108,
     106,   190,   110,   108,   108,   108,    -1,   106,   108,   110,
     108,   255,   256,   110,   258,   259,   110,   108,   108,   108,
     209,   388,   108,   108,   108,   108,   108,    -1,    -1,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   108,   110,    -1,   110,   110,   110,   292,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   293,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   321,   110,   110,
     110,   325,   110,   110,   110,   316,   110,   110,   110,   110,
     108,   335,   108,   108,   108,   108,   108,    -1,    -1,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   108,   298,
     299,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   366,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   376,   108,   110,    -1,   110,   110,   110,   110,
     384,   110,   110,   387,   388,   389,   110,   110,   110,   110,
     110,   110,   110,   108,   108,   108,   108,   108,   108,    -1,
      -1,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   372,   110,   429,   110,   110,   110,   433,
     110,   110,   110,   437,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   108,   108,    -1,   108,   110,    -1,
     110,   110,   110,   110,   107,   446,   107,    -1,   110,    -1,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   473,
     110,   110,   110,   108,   478,   107,   110,   110,   427,   110,
     110,   485,   110,   487,   110,   107,   110,   110,   107,   493,
     110,   108,   108,    -1,   108,   110,   107,   110,   489,    -1,
     110,   110,   110,   110,   110,   110,   107,   110,   110,   107,
     514,   110,   516,   110,   110,   519,   110,   110,   107,   110,
     110,   107,   110,   110,   108,   110,   475,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     544,   110,   546,   547,   107,   549,   550,    -1,   110,   110,
     110,   108,   110,   107,   110,   107,    -1,   110,    -1,   110,
     110,   110,   110,   110,   513,   110,   110,   110,   110,   110,
     107,   110,   110,   108,   523,   579,   110,   107,   110,   107,
     107,   110,    -1,   587,   110,   110,   110,   110,   110,   110,
     539,   540,   596,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,     1,   562,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   110,   103,   104,   110,   110,   110,   110,
     110,    -1,   111,   110,   110,   110,   107,   107,   107,    -1,
      -1,    -1,   110,   110,   110,   107,   110,   110,    -1,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   107,   110
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,   113,   125,     0,   126,     1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   103,   104,   111,   127,   108,
     110,   110,   110,   106,   110,   106,   110,   108,   110,   110,
     110,   110,   110,   110,   108,   110,   108,   108,   108,   108,
     108,   106,   110,   115,   117,   118,   110,   108,   106,   110,
     106,   110,   106,   110,   108,   108,   108,   110,   108,   108,
     108,   108,   110,   108,   110,   106,   110,   106,   110,   106,
     110,   108,   108,   108,   110,   106,   106,   110,   110,   110,
     110,   106,   110,   108,   108,   108,   108,   108,   108,   123,
     124,   106,   119,   119,   119,   106,   108,   108,   108,   110,
     117,   106,   110,   106,   110,   106,   110,   106,   110,   106,
     110,   106,   110,   106,   110,   108,   108,   123,   108,   110,
     108,   108,   110,   110,   117,   118,   108,   108,   108,   108,
     108,   108,   108,   105,   110,   108,   110,   110,   110,   110,
     110,   123,   110,   110,   110,   110,   110,   110,   110,   123,
     110,   108,   123,   123,   107,   115,   110,   117,   123,   110,
     110,   110,   110,   110,   110,   108,   110,   123,   108,   110,
     110,   110,   123,   123,   123,   123,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     123,   123,   123,   106,   108,   118,   120,   123,   107,   110,
     114,   123,   119,   119,   110,   110,   123,   110,   110,   117,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   119,   123,   119,   117,   106,   120,
     108,   108,   108,   108,   108,   108,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   108,   107,   110,   110,   110,
     110,   110,   110,   108,   123,   123,   123,   123,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   108,   116,   107,   110,   123,   119,   110,   106,   108,
     108,   117,   117,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   108,   119,   120,
     106,   108,   123,   108,   108,   108,   123,   110,   110,   110,
     110,   110,   110,   123,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   107,
     108,   123,   110,   110,   110,   110,   110,   117,   110,   110,
     110,   123,   110,   110,   110,   110,   110,   110,   110,   123,
     110,   110,   123,   106,   120,   121,   122,   123,   123,   110,
     108,   108,   110,   108,   110,   110,   110,   110,   107,   107,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   108,   110,   117,   110,   123,   107,   110,
     123,   110,   110,   110,   123,   107,   110,   110,   107,   119,
     110,   108,   108,   110,   108,   107,   107,   110,   110,   110,
     110,   110,   110,   110,   107,   110,   110,   110,   110,   110,
     110,   123,   110,   117,   107,   123,   107,   110,   110,   107,
     123,   110,   123,   119,   110,   110,   110,   123,   108,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     117,   123,   123,   110,   110,   123,   107,   117,   110,   110,
     110,   108,   110,   110,   107,   107,   110,   110,   110,   110,
     110,   117,   117,   110,   123,   123,   123,   110,   123,   123,
     110,   110,   110,   110,   107,   110,   110,   110,   117,   107,
     110,   108,   107,   110,   110,   110,   110,   110,   123,   107,
     110,   110,   110,   110,   110,   123,   110,   110,   110,   110,
     110,   123,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   107,   107,   107,   110,   110,   110,   106,   108,
     107,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   107,
     110
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (N)								\
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (0)
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
              (Loc).first_line, (Loc).first_column,	\
              (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Type, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short int *bottom, short int *top)
#else
static void
yy_stack_print (bottom, top)
    short int *bottom;
    short int *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);


# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */






/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  /* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short int yyssa[YYINITDEPTH];
  short int *yyss = yyssa;
  register short int *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;


  yyvsp[0] = yylval;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short int *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short int *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a look-ahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to look-ahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 621 "rib.y"
    {
					args[numArguments++].integer				=	(int) (yyvsp[0].real);
					argCheck();
					(yyval.integer)	=	(yyvsp[-1].integer)	+	1;
				;}
    break;

  case 4:
#line 628 "rib.y"
    {
					args[numArguments++].integer				=	(int) (yyvsp[0].real);
					argCheck();
					(yyval.integer)	=	1;
				;}
    break;

  case 5:
#line 638 "rib.y"
    {
					args[numArguments++].real					=	(yyvsp[0].real);
					argCheck();
					(yyval.integer)	=	(yyvsp[-1].integer)	+	1;
				;}
    break;

  case 6:
#line 645 "rib.y"
    {
					args[numArguments++].real					=	(yyvsp[0].real);
					argCheck();
					(yyval.integer)	=	1;
				;}
    break;

  case 7:
#line 654 "rib.y"
    {
					char	*theString	=	strdup((yyvsp[0].string));
					args[numArguments++].string					=	theString;
					allocatedStrings->push(theString);
					argCheck();
					(yyval.integer)	=	(yyvsp[-1].integer)	+	1;
				;}
    break;

  case 8:
#line 663 "rib.y"
    {
					char	*theString	=	strdup((yyvsp[0].string));
					args[numArguments++].string					=	theString;
					allocatedStrings->push(theString);
					argCheck();
					(yyval.integer)	=	1;
				;}
    break;

  case 9:
#line 675 "rib.y"
    {
					(yyval.integer) = (yyvsp[-1].integer);
				;}
    break;

  case 10:
#line 681 "rib.y"
    {
					(yyval.integer) = 0;
				;}
    break;

  case 11:
#line 688 "rib.y"
    {
					(yyval.integer)	=	(yyvsp[0].integer);
				;}
    break;

  case 12:
#line 693 "rib.y"
    {
					(yyval.integer)	=	(yyvsp[0].integer);
				;}
    break;

  case 13:
#line 701 "rib.y"
    {
					(yyval.integer) = (yyvsp[-1].integer);
				;}
    break;

  case 14:
#line 707 "rib.y"
    {
					(yyval.integer) = 0;
				;}
    break;

  case 15:
#line 716 "rib.y"
    {
					(yyval.integer)	=	(yyvsp[-1].integer);
				;}
    break;

  case 16:
#line 721 "rib.y"
    {
					char	*theString	=	strdup((yyvsp[0].string));
					args[numArguments++].string					=	theString;
					allocatedStrings->push(theString);
					argCheck();
					(yyval.integer)	= 1;
				;}
    break;

  case 18:
#line 737 "rib.y"
    {
					(yyval.integer)	=	0;
				;}
    break;

  case 19:
#line 742 "rib.y"
    {
					(yyval.integer)	=	(yyvsp[0].integer);
				;}
    break;

  case 20:
#line 750 "rib.y"
    {
				;}
    break;

  case 21:
#line 753 "rib.y"
    {
					int	i;

					assert(numParameters < maxParameter);

					// Fix the pointers
					for (i=0;i<numParameters;i++) {
						tokens[i]				=	parameters[i].name;

						if (parameters[i].type == RT_TEXT)
							vals[i]				=	(RtPointer) &args[parameters[i].valuesStart].string;
						else
							vals[i]				=	(RtPointer) &args[parameters[i].valuesStart];

						parameters[i].values	=	args + parameters[i].valuesStart;
					}
				;}
    break;

  case 22:
#line 774 "rib.y"
    {
					// A parameter is either a float array
					parameters[numParameters].name			=	(yyvsp[-1].string);
					parameters[numParameters].type			=	RT_FLOAT;
					parameters[numParameters].numItems		=	(yyvsp[0].integer);
					parameters[numParameters].valuesStart	=	numArguments-(yyvsp[0].integer);
					numParameters++;
					paramCheck();
				;}
    break;

  case 23:
#line 786 "rib.y"
    {	
					// Or a string array
					parameters[numParameters].name			=	(yyvsp[-1].string);
					parameters[numParameters].type			=	RT_TEXT;
					parameters[numParameters].numItems		=	(yyvsp[0].integer);
					parameters[numParameters].valuesStart	=	numArguments-(yyvsp[0].integer);
					numParameters++;
					paramCheck();
				;}
    break;

  case 24:
#line 798 "rib.y"
    {
					// Save the line number in case we have an error
					ribCommandLineno	=	ribLineno;
				;}
    break;

  case 25:
#line 803 "rib.y"
    {
					char	*currentString;
					numArguments	=	0;
					numParameters	=	0;
					while((currentString=allocatedStrings->pop()) != NULL)
						free(currentString);

				;}
    break;

  case 27:
#line 816 "rib.y"
    {
					if (callback != NULL) {
						callback((yyvsp[0].string));
					}
				;}
    break;

  case 28:
#line 825 "rib.y"
    {
					RiDeclare((yyvsp[-1].string),(yyvsp[0].string));
				;}
    break;

  case 29:
#line 830 "rib.y"
    {
					RiFrameBegin(0);
				;}
    break;

  case 30:
#line 836 "rib.y"
    {
					RiFrameBegin((int) (yyvsp[0].real));
				;}
    break;

  case 31:
#line 841 "rib.y"
    {
					RiFrameEnd();
				;}
    break;

  case 32:
#line 846 "rib.y"
    {
					RiWorldBegin();
				;}
    break;

  case 33:
#line 851 "rib.y"
    {
					RiWorldEnd();
				;}
    break;

  case 34:
#line 859 "rib.y"
    {
					RiFormat((int) (yyvsp[-2].real),(int) (yyvsp[-1].real),(yyvsp[0].real));
				;}
    break;

  case 35:
#line 865 "rib.y"
    {
					RiFrameAspectRatio((yyvsp[0].real));
				;}
    break;

  case 36:
#line 874 "rib.y"
    {
					RiScreenWindow((yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real),(yyvsp[0].real));
				;}
    break;

  case 37:
#line 885 "rib.y"
    {
					RiScreenWindow((yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real));
				;}
    break;

  case 38:
#line 894 "rib.y"
    {
					RiCropWindow((yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real),(yyvsp[0].real));
				;}
    break;

  case 39:
#line 905 "rib.y"
    {
					RiCropWindow((yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real));
				;}
    break;

  case 40:
#line 912 "rib.y"
    {
					RiProjectionV((yyvsp[-1].string),numParameters,tokens,vals);
				;}
    break;

  case 41:
#line 919 "rib.y"
    {
					RiClipping((yyvsp[-1].real),(yyvsp[0].real));
				;}
    break;

  case 42:
#line 930 "rib.y"
    {
					RiClippingPlane((yyvsp[-5].real),(yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real),(yyvsp[0].real));
				;}
    break;

  case 43:
#line 938 "rib.y"
    {
					RiDepthOfField((yyvsp[-2].real),(yyvsp[-1].real),(yyvsp[0].real));
				;}
    break;

  case 44:
#line 943 "rib.y"
    {
					RiDepthOfField(C_INFINITY,1,1);
				;}
    break;

  case 45:
#line 950 "rib.y"
    {
					RiShutter((yyvsp[-1].real),(yyvsp[0].real));
				;}
    break;

  case 46:
#line 956 "rib.y"
    {
					RiPixelVariance((yyvsp[0].real));
				;}
    break;

  case 47:
#line 963 "rib.y"
    {
					RiPixelSamples((yyvsp[-1].real),(yyvsp[0].real));
				;}
    break;

  case 48:
#line 971 "rib.y"
    {
					RtFilterFunc	f;

					if ((f = getFilter((yyvsp[-2].string))) != NULL) {
						RiPixelFilter(f,(yyvsp[-1].real),(yyvsp[0].real));
					}
				;}
    break;

  case 49:
#line 982 "rib.y"
    {
					RiExposure((yyvsp[-1].real),(yyvsp[0].real));
				;}
    break;

  case 50:
#line 989 "rib.y"
    {
					// No parameter list checking is performed for the shaders
					if (parameterListCheck()) {
						RiImagerV((yyvsp[-1].string),numParameters,tokens,vals);
					}
				;}
    break;

  case 51:
#line 1002 "rib.y"
    {
					RiQuantize((yyvsp[-4].string),(int) (yyvsp[-3].real),(int) (yyvsp[-2].real),(int) (yyvsp[-1].real),(yyvsp[0].real));
				;}
    break;

  case 52:
#line 1011 "rib.y"
    {
					RiDisplayV((yyvsp[-3].string),(yyvsp[-2].string),(yyvsp[-1].string),numParameters,tokens,vals);
				;}
    break;

  case 53:
#line 1018 "rib.y"
    {
					RiDisplayChannelV((yyvsp[-1].string),numParameters,tokens,vals);
				;}
    break;

  case 54:
#line 1025 "rib.y"
    {
					if (parameterListCheck()) {
						RiHiderV((yyvsp[-1].string),numParameters,tokens,vals);
					}
				;}
    break;

  case 55:
#line 1033 "rib.y"
    {
					if ((numArguments & 1) || ((numArguments % 6) != 0)) {
						error(CODE_MISSINGDATA,"ColorSamples: Invalid number of arguments (\"%d\") \n",numArguments);
					} else {
						int		n		=	numArguments/6;
						float	*argf1	=	(float *) get(0);
						float	*argf2	=	(float *) get(n*3);

						RiColorSamples(n,argf1,argf2);
					}
				;}
    break;

  case 56:
#line 1048 "rib.y"
    {
					if (((yyvsp[-1].integer) != (yyvsp[0].integer)) || ((numArguments % 6) != 0)) {
						error(CODE_MISSINGDATA,"ColorSamples: Invalid number of arguments (\"%d\") \n",numArguments);
					} else {
						int		n		=	numArguments/6;
						float	*argf1	=	(float *) get(0);
						float	*argf2	=	(float *) get(n*3);

						RiColorSamples(n,argf1,argf2);
					}
				;}
    break;

  case 57:
#line 1062 "rib.y"
    {
					RiRelativeDetail((yyvsp[0].real));	
				;}
    break;

  case 58:
#line 1069 "rib.y"
    {
					if (parameterListCheck()) {
						RiOptionV((yyvsp[-1].string),numParameters,tokens,vals);
					}
				;}
    break;

  case 59:
#line 1076 "rib.y"
    {
					RiAttributeBegin();
				;}
    break;

  case 60:
#line 1081 "rib.y"
    {
					RiAttributeEnd();
				;}
    break;

  case 61:
#line 1089 "rib.y"
    {
					RtColor	color;

					color[0]	=	(yyvsp[-2].real);
					color[1]	=	(yyvsp[-1].real);
					color[2]	=	(yyvsp[0].real);

					RiColor(color);
				;}
    break;

  case 62:
#line 1103 "rib.y"
    {
					RtColor	color;

					color[0]	=	(yyvsp[-2].real);
					color[1]	=	(yyvsp[-1].real);
					color[2]	=	(yyvsp[0].real);

					RiOpacity(color);
				;}
    break;

  case 63:
#line 1119 "rib.y"
    {
					RtColor	color;

					color[0]	=	(yyvsp[-3].real);
					color[1]	=	(yyvsp[-2].real);
					color[2]	=	(yyvsp[-1].real);

					RiColor(color);
				;}
    break;

  case 64:
#line 1135 "rib.y"
    {
					RtColor	color;

					color[0]	=	(yyvsp[-3].real);
					color[1]	=	(yyvsp[-2].real);
					color[2]	=	(yyvsp[-1].real);

					RiOpacity(color);
				;}
    break;

  case 65:
#line 1154 "rib.y"
    {
					RiTextureCoordinates((yyvsp[-7].real),(yyvsp[-6].real),(yyvsp[-5].real),(yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real),(yyvsp[0].real));
				;}
    break;

  case 66:
#line 1169 "rib.y"
    {
					RiTextureCoordinates((yyvsp[-8].real),(yyvsp[-7].real),(yyvsp[-6].real),(yyvsp[-5].real),(yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real));
				;}
    break;

  case 67:
#line 1177 "rib.y"
    {
					if (lights == NULL)	lights	=	new CArray<RtLightHandle>;

					(*lights)[(int) (yyvsp[-1].real)]	=	RiLightSourceV((yyvsp[-2].string),numParameters,tokens,vals);
				;}
    break;

  case 68:
#line 1187 "rib.y"
    {
					if (lightNames == NULL)	lightNames	=	new CTrie<RtLightHandle>;
					
					char *lName = strdup((yyvsp[-1].string));
					permaStrings->push(lName);
					lightNames->insert(lName,RiLightSourceV((yyvsp[-2].string),numParameters,tokens,vals));
				;}
    break;

  case 69:
#line 1198 "rib.y"
    {
					RiLightSourceV((yyvsp[-1].string),numParameters,tokens,vals);
				;}
    break;

  case 70:
#line 1206 "rib.y"
    {
					if (lights == NULL)	lights	=	new CArray<RtLightHandle>;

					(*lights)[(int) (yyvsp[-1].real)]	=	RiAreaLightSourceV((yyvsp[-2].string),numParameters,tokens,vals);
				;}
    break;

  case 71:
#line 1216 "rib.y"
    {
					if (lightNames == NULL)	lightNames	=	new CTrie<RtLightHandle>;
					
					char *lName = strdup((yyvsp[-1].string));
					permaStrings->push(lName);
					lightNames->insert(lName,RiLightSourceV((yyvsp[-2].string),numParameters,tokens,vals));
				;}
    break;

  case 72:
#line 1227 "rib.y"
    {
					if (lights == NULL)	lights	=	new CArray<RtLightHandle>;

					RiIlluminate((*lights)[(int) (yyvsp[-1].real)],(int) (yyvsp[0].real));
				;}
    break;

  case 73:
#line 1236 "rib.y"
    {
					if (lightNames == NULL)	lightNames	=	new CTrie<RtLightHandle>;
					RtLightHandle lightHandle = NULL;
					
					if(lightNames->find((yyvsp[-1].string),lightHandle)){
						RiIlluminate(lightHandle,(int) (yyvsp[0].real));
					}
				;}
    break;

  case 74:
#line 1248 "rib.y"
    {
					RiSurfaceV((yyvsp[-1].string),numParameters,tokens,vals);
				;}
    break;

  case 75:
#line 1255 "rib.y"
    {
					RiAtmosphereV((yyvsp[-1].string),numParameters,tokens,vals);
				;}
    break;

  case 76:
#line 1262 "rib.y"
    {
					RiInteriorV((yyvsp[-1].string),numParameters,tokens,vals);
				;}
    break;

  case 77:
#line 1269 "rib.y"
    {
					RiExteriorV((yyvsp[-1].string),numParameters,tokens,vals);
				;}
    break;

  case 78:
#line 1275 "rib.y"
    {
					RiShadingRate((yyvsp[0].real));
				;}
    break;

  case 79:
#line 1281 "rib.y"
    {
					RiShadingInterpolation((yyvsp[0].string));
				;}
    break;

  case 80:
#line 1287 "rib.y"
    {
					RiMatte((RtBoolean) (yyvsp[0].real));
				;}
    break;

  case 81:
#line 1300 "rib.y"
    {
					RtBound	bound;

					bound[0]	=	(yyvsp[-6].real);
					bound[1]	=	(yyvsp[-5].real);
					bound[2]	=	(yyvsp[-4].real);
					bound[3]	=	(yyvsp[-3].real);
					bound[4]	=	(yyvsp[-2].real);
					bound[5]	=	(yyvsp[-1].real);

					RiBound(bound);
				;}
    break;

  case 82:
#line 1320 "rib.y"
    {
					RtBound	bound;

					bound[0]	=	(yyvsp[-5].real);
					bound[1]	=	(yyvsp[-4].real);
					bound[2]	=	(yyvsp[-3].real);
					bound[3]	=	(yyvsp[-2].real);
					bound[4]	=	(yyvsp[-1].real);
					bound[5]	=	(yyvsp[0].real);

					RiBound(bound);
				;}
    break;

  case 83:
#line 1342 "rib.y"
    {
					RtBound	bound;

					bound[0]	=	(yyvsp[-6].real);
					bound[1]	=	(yyvsp[-5].real);
					bound[2]	=	(yyvsp[-4].real);
					bound[3]	=	(yyvsp[-3].real);
					bound[4]	=	(yyvsp[-2].real);
					bound[5]	=	(yyvsp[-1].real);

					RiDetail(bound);
				;}
    break;

  case 84:
#line 1362 "rib.y"
    {
					RtBound	bound;

					bound[0]	=	(yyvsp[-5].real);
					bound[1]	=	(yyvsp[-4].real);
					bound[2]	=	(yyvsp[-3].real);
					bound[3]	=	(yyvsp[-2].real);
					bound[4]	=	(yyvsp[-1].real);
					bound[5]	=	(yyvsp[0].real);

					RiDetail(bound);
				;}
    break;

  case 85:
#line 1380 "rib.y"
    {
					RiDetailRange((yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real),(yyvsp[0].real));
				;}
    break;

  case 86:
#line 1391 "rib.y"
    {
					RiDetailRange((yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real));
				;}
    break;

  case 87:
#line 1398 "rib.y"
    {
					RiGeometricApproximation((yyvsp[-1].string),(yyvsp[0].real));
				;}
    break;

  case 88:
#line 1404 "rib.y"
    {
					RiGeometricRepresentation((yyvsp[0].string));
				;}
    break;

  case 89:
#line 1410 "rib.y"
    {
					RiOrientation((yyvsp[0].string));
				;}
    break;

  case 90:
#line 1415 "rib.y"
    {
					RiReverseOrientation();
				;}
    break;

  case 91:
#line 1421 "rib.y"
    {
					RiSides((int) (yyvsp[0].real));
				;}
    break;

  case 92:
#line 1426 "rib.y"
    {
					RiIdentity();
				;}
    break;

  case 93:
#line 1449 "rib.y"
    {
					RtMatrix	tmp;

					tmp[0][0]	=	(yyvsp[-16].real);
					tmp[0][1]	=	(yyvsp[-15].real);
					tmp[0][2]	=	(yyvsp[-14].real);
					tmp[0][3]	=	(yyvsp[-13].real);
					tmp[1][0]	=	(yyvsp[-12].real);
					tmp[1][1]	=	(yyvsp[-11].real);
					tmp[1][2]	=	(yyvsp[-10].real);
					tmp[1][3]	=	(yyvsp[-9].real);
					tmp[2][0]	=	(yyvsp[-8].real);
					tmp[2][1]	=	(yyvsp[-7].real);
					tmp[2][2]	=	(yyvsp[-6].real);
					tmp[2][3]	=	(yyvsp[-5].real);
					tmp[3][0]	=	(yyvsp[-4].real);
					tmp[3][1]	=	(yyvsp[-3].real);
					tmp[3][2]	=	(yyvsp[-2].real);
					tmp[3][3]	=	(yyvsp[-1].real);

					RiTransform(tmp);
				;}
    break;

  case 94:
#line 1491 "rib.y"
    {
					RtMatrix	tmp;

					tmp[0][0]	=	(yyvsp[-16].real);
					tmp[0][1]	=	(yyvsp[-15].real)	;
					tmp[0][2]	=	(yyvsp[-14].real);
					tmp[0][3]	=	(yyvsp[-13].real);
					tmp[1][0]	=	(yyvsp[-12].real);
					tmp[1][1]	=	(yyvsp[-11].real);
					tmp[1][2]	=	(yyvsp[-10].real);
					tmp[1][3]	=	(yyvsp[-9].real);
					tmp[2][0]	=	(yyvsp[-8].real);
					tmp[2][1]	=	(yyvsp[-7].real);
					tmp[2][2]	=	(yyvsp[-6].real);
					tmp[2][3]	=	(yyvsp[-5].real);
					tmp[3][0]	=	(yyvsp[-4].real);
					tmp[3][1]	=	(yyvsp[-3].real);
					tmp[3][2]	=	(yyvsp[-2].real);
					tmp[3][3]	=	(yyvsp[-1].real);

					RiConcatTransform(tmp);
				;}
    break;

  case 95:
#line 1516 "rib.y"
    {
					RiPerspective((yyvsp[0].real));
				;}
    break;

  case 96:
#line 1524 "rib.y"
    {
					RiTranslate((yyvsp[-2].real),(yyvsp[-1].real),(yyvsp[0].real));
				;}
    break;

  case 97:
#line 1532 "rib.y"
    {
					RiScale((yyvsp[-2].real),(yyvsp[-1].real),(yyvsp[0].real));
				;}
    break;

  case 98:
#line 1541 "rib.y"
    {
					RiRotate((yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real),(yyvsp[0].real));
				;}
    break;

  case 99:
#line 1553 "rib.y"
    {
					RiSkew((yyvsp[-6].real),(yyvsp[-5].real),(yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real),(yyvsp[0].real));
				;}
    break;

  case 100:
#line 1567 "rib.y"
    {
					RiSkew((yyvsp[-7].real),(yyvsp[-6].real),(yyvsp[-5].real),(yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real));
				;}
    break;

  case 101:
#line 1574 "rib.y"
    {
					RiDeformationV((yyvsp[-1].string),numParameters,tokens,vals);
				;}
    break;

  case 102:
#line 1581 "rib.y"
    {
					RiDisplacementV((yyvsp[-1].string),numParameters,tokens,vals);
				;}
    break;

  case 103:
#line 1587 "rib.y"
    {
					RiCoordinateSystem((yyvsp[0].string));
				;}
    break;

  case 104:
#line 1593 "rib.y"
    {
					RiCoordSysTransform((yyvsp[0].string));
				;}
    break;

  case 105:
#line 1598 "rib.y"
    {
					RiTransformBegin();
				;}
    break;

  case 106:
#line 1603 "rib.y"
    {
					RiTransformEnd();
				;}
    break;

  case 107:
#line 1610 "rib.y"
    {
					if (parameterListCheck()) {
						RiAttributeV((yyvsp[-1].string),numParameters,tokens,vals);
					}
				;}
    break;

  case 108:
#line 1618 "rib.y"
    {
					if (parameterListCheck()) {	
						if (sizeCheck(numVertex,0,0,1)) {
							RiPolygonV(numVertex,numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 109:
#line 1629 "rib.y"
    {
					int		*argi	=	(int *) get(0);

					if (parameterListCheck()) {
						if (sizeCheck(numVertex,0,0,1)) {
							RiGeneralPolygonV((yyvsp[-1].integer),argi,numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 110:
#line 1643 "rib.y"
    {
					int	*argi1		=	(int *) get(0);
					int	*argi2		=	(int *) get((yyvsp[-2].integer));
					int	nvertices	=	0;
					int	i;
					int	maxVertex	=	0;


					// Find out how many items are in verts array
					for (i=0;i<(yyvsp[-2].integer);i++) {
						nvertices	+=	argi1[i];
					}

					if (nvertices != (yyvsp[-1].integer)) {
						error(CODE_MISSINGDATA,"Vertex count mismatch (%d != %d)\n",nvertices,(yyvsp[-1].integer));
					} else {
						// Find out the number of vertices required
						for (i=0,maxVertex=0;i<nvertices;i++) {
							if (argi2[i] > maxVertex)
								maxVertex	=	argi2[i];
						}

						maxVertex++;

						if (parameterListCheck()) {
							if (sizeCheck(maxVertex,0,nvertices,(yyvsp[-2].integer))) {
								RiPointsPolygonsV((yyvsp[-2].integer),argi1,argi2,numParameters,tokens,vals);
							}
						}
					}
				;}
    break;

  case 111:
#line 1680 "rib.y"
    {
					int	*argi1		=	(int *) get(0);
					int	*argi2		=	(int *) get((yyvsp[-3].integer));
					int	*argi3		=	(int *) get((yyvsp[-2].integer)+(yyvsp[-3].integer));
					int	numvertices	=	0;
					int	numloops	=	0;
					int	maxVertex	=	0;
					int	i;

					for (i=0;i<(yyvsp[-3].integer);i++) {
						numloops	+=	argi1[i];
					}

					if (numloops != (yyvsp[-2].integer)) {
						error(CODE_MISSINGDATA,"Loop count mismatch (%d != %d)\n",numloops,(yyvsp[-2].integer));
					} else {
						for (i=0;i<(yyvsp[-2].integer);i++) {
							numvertices	+=	argi2[i];
						}

						if (numvertices != (yyvsp[-1].integer)) {
							error(CODE_MISSINGDATA,"Vertex count mismatch (%d != %d)\n",numvertices,(yyvsp[-1].integer));
						} else {
							for (i=0;i<numvertices;i++) {
								if (argi3[i] > maxVertex)
									maxVertex	=	argi3[i];
							}

							maxVertex++;

							if (parameterListCheck()) {
								if (sizeCheck(maxVertex,0,numvertices,(yyvsp[-3].integer))) {
									RiPointsGeneralPolygonsV((yyvsp[-3].integer),argi1,argi2,argi3,numParameters,tokens,vals);
								}
							}
						}
					}
				;}
    break;

  case 112:
#line 1724 "rib.y"
    {
					RtBasis	*argf1,*argf2;

					if ((getBasis(&argf1,(yyvsp[-3].string))) && (getBasis(&argf2,(yyvsp[-1].string)))) {
						RiBasis(argf1[0],(int) (yyvsp[-2].real), argf2[0],(int) (yyvsp[0].real));
					}
				;}
    break;

  case 113:
#line 1754 "rib.y"
    {
					RtBasis	*argf2;

					if (getBasis(&argf2,(yyvsp[-1].string))) {
						RtBasis	tmp;
					
						tmp[0][0]	=	(yyvsp[-19].real);
						tmp[0][1]	=	(yyvsp[-18].real);
						tmp[0][2]	=	(yyvsp[-17].real);
						tmp[0][3]	=	(yyvsp[-16].real);
						tmp[1][0]	=	(yyvsp[-15].real);
						tmp[1][1]	=	(yyvsp[-14].real);
						tmp[1][2]	=	(yyvsp[-13].real);
						tmp[1][3]	=	(yyvsp[-12].real);
						tmp[2][0]	=	(yyvsp[-11].real);
						tmp[2][1]	=	(yyvsp[-10].real);
						tmp[2][2]	=	(yyvsp[-9].real);
						tmp[2][3]	=	(yyvsp[-8].real);
						tmp[3][0]	=	(yyvsp[-7].real);
						tmp[3][1]	=	(yyvsp[-6].real);
						tmp[3][2]	=	(yyvsp[-5].real);
						tmp[3][3]	=	(yyvsp[-4].real);
										
						RiBasis(tmp,(int) (yyvsp[-2].real),argf2[0],(int) (yyvsp[0].real));
					}
				;}
    break;

  case 114:
#line 1803 "rib.y"
    {
					RtBasis	*argf1;

					if (getBasis(&argf1,(yyvsp[-20].string))) {
						RtBasis	tmp;
					
						tmp[0][0]	=	(yyvsp[-17].real);
						tmp[0][1]	=	(yyvsp[-16].real);
						tmp[0][2]	=	(yyvsp[-15].real);
						tmp[0][3]	=	(yyvsp[-14].real);
						tmp[1][0]	=	(yyvsp[-13].real);
						tmp[1][1]	=	(yyvsp[-12].real);
						tmp[1][2]	=	(yyvsp[-11].real);
						tmp[1][3]	=	(yyvsp[-10].real);
						tmp[2][0]	=	(yyvsp[-9].real);
						tmp[2][1]	=	(yyvsp[-8].real);
						tmp[2][2]	=	(yyvsp[-7].real);
						tmp[2][3]	=	(yyvsp[-6].real);
						tmp[3][0]	=	(yyvsp[-5].real);
						tmp[3][1]	=	(yyvsp[-4].real);
						tmp[3][2]	=	(yyvsp[-3].real);
						tmp[3][3]	=	(yyvsp[-2].real);

						RiBasis(argf1[0],(int) (yyvsp[-19].real),tmp,(int) (yyvsp[0].real));
					}
				;}
    break;

  case 115:
#line 1869 "rib.y"
    {
					RtBasis	b1,b2;

					b1[0][0]	=	(yyvsp[-36].real);
					b1[0][1]	=	(yyvsp[-35].real);
					b1[0][2]	=	(yyvsp[-34].real);
					b1[0][3]	=	(yyvsp[-33].real);
					b1[1][0]	=	(yyvsp[-32].real);
					b1[1][1]	=	(yyvsp[-31].real);
					b1[1][2]	=	(yyvsp[-30].real);
					b1[1][3]	=	(yyvsp[-29].real);
					b1[2][0]	=	(yyvsp[-28].real);
					b1[2][1]	=	(yyvsp[-27].real);
					b1[2][2]	=	(yyvsp[-26].real);
					b1[2][3]	=	(yyvsp[-25].real);
					b1[3][0]	=	(yyvsp[-24].real);
					b1[3][1]	=	(yyvsp[-23].real);
					b1[3][2]	=	(yyvsp[-22].real);
					b1[3][3]	=	(yyvsp[-21].real);

					b2[0][0]	=	(yyvsp[-17].real);
					b2[0][1]	=	(yyvsp[-16].real);
					b2[0][2]	=	(yyvsp[-15].real);
					b2[0][3]	=	(yyvsp[-14].real);
					b2[1][0]	=	(yyvsp[-13].real);
					b2[1][1]	=	(yyvsp[-12].real);
					b2[1][2]	=	(yyvsp[-11].real);
					b2[1][3]	=	(yyvsp[-10].real);
					b2[2][0]	=	(yyvsp[-9].real);
					b2[2][1]	=	(yyvsp[-8].real);
					b2[2][2]	=	(yyvsp[-7].real);
					b2[2][3]	=	(yyvsp[-6].real);
					b2[3][0]	=	(yyvsp[-5].real);
					b2[3][1]	=	(yyvsp[-4].real);
					b2[3][2]	=	(yyvsp[-3].real);
					b2[3][3]	=	(yyvsp[-2].real);

					RiBasis(b1,(int) (yyvsp[-19].real),b2,(int) (yyvsp[0].real));
				;}
    break;

  case 116:
#line 1912 "rib.y"
    {
					int	numExpectedVertices;
					int	numExpectedPatches	=	1;


					if (strcmp((yyvsp[-1].string),RI_BILINEAR) == 0) {
						numExpectedVertices	=	4;
					} else if (strcmp((yyvsp[-1].string),RI_BICUBIC) == 0) {
						numExpectedVertices	=	16;
					} else {
						error(CODE_BADTOKEN,"Unknown patch type: \"%s\"\n",(yyvsp[-1].string));
						numExpectedVertices	=	0;
					}

					if (numExpectedVertices > 0) {
						if (parameterListCheck()) {
							if (sizeCheck(numExpectedVertices,4,4,1)) {
								RiPatchV((yyvsp[-1].string),numParameters,tokens,vals);
							}
						}
					}
				;}
    break;

  case 117:
#line 1942 "rib.y"
    {
					int	numExpectedVertices;
					int	numuPatches,numvPatches;
					int	nu	=	(int) (yyvsp[-4].real);
					int	nv	=	(int) (yyvsp[-2].real);
					CAttributes	*attributes	=	currentRenderer->getAttributes(FALSE);
					int	uw,vw;
					int	numVaryings;

					if (strcmp((yyvsp[-3].string),RI_PERIODIC) == 0) {
						uw	=	TRUE;
					} else {
						uw	=	FALSE;
					}

					if (strcmp((yyvsp[-1].string),RI_PERIODIC) == 0) {
						vw	=	TRUE;
					} else {
						vw	=	FALSE;
					}

					if (strcmp((yyvsp[-5].string),RI_BILINEAR) == 0) {
						numExpectedVertices	=	nu*nv;

						if (uw) {
							numuPatches	=	nu;
						} else {
							numuPatches	=	nu-1;
						}


						if (vw) {
							numvPatches	=	nv;
						} else {
							numvPatches	=	nv-1;
						}

						numVaryings		=	nu*nv;
					} else if (strcmp((yyvsp[-5].string),RI_BICUBIC) == 0) {
						numExpectedVertices	=	nu*nv;

						if (uw) {
							numuPatches	=	nu / attributes->uStep;
						} else {
							numuPatches	=	(nu - 4) / attributes->uStep + 1;
						}


						if (vw) {
							numvPatches	=	nv / attributes->vStep;
						} else {
							numvPatches	=	(nv - 4) / attributes->vStep + 1;
						}

						numVaryings		=	(numuPatches+1-uw)*(numvPatches+1-vw);
					} else {
						error(CODE_BADTOKEN,"Unknown patch type: \"%s\"\n",(yyvsp[-5].string));
						numExpectedVertices	=	0;
					}

					if (numExpectedVertices > 0) {
						if (parameterListCheck()) {
							if (sizeCheck(numExpectedVertices,numVaryings,numuPatches*numvPatches*4,numuPatches*numvPatches)) {
								RiPatchMeshV((yyvsp[-5].string),(int) (yyvsp[-4].real),(yyvsp[-3].string),(int) (yyvsp[-2].real),(yyvsp[-1].string),numParameters,tokens,vals);
							}
						}
					}
				;}
    break;

  case 118:
#line 2023 "rib.y"
    {
					float	*argf1	=	(float *) get(0);
					float	*argf2	=	(float *) get((yyvsp[-8].integer));

					int		uPoints	=	(int) (yyvsp[-10].real);
					int		uOrder	=	(int) (yyvsp[-9].real);
					int		vPoints	=	(int) (yyvsp[-5].real);
					int		vOrder	=	(int) (yyvsp[-4].real);

					int		uPatches	=	uPoints - uOrder+1;
					int		vPatches	=	vPoints - vOrder+1;

					int		numExpectedVertices	=	uPoints*vPoints;

					if (parameterListCheck()) {
						if (sizeCheck(numExpectedVertices,(uPoints-uOrder+2)*(vPoints-vOrder+2),uPatches*vPatches*4,uPatches*vPatches)) {
							RiNuPatchV((int) (yyvsp[-10].real),(int) (yyvsp[-9].real),argf1,(yyvsp[-7].real),(yyvsp[-6].real),(int) (yyvsp[-5].real),(int) (yyvsp[-4].real),argf2,(yyvsp[-2].real),(yyvsp[-1].real),numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 119:
#line 2054 "rib.y"
    {
					int		*argi1	=	(int *)		get(0);
					int		*argi2	=	(int *)		get((yyvsp[-8].integer));
					float	*argf3	=	(float *)	get((yyvsp[-7].integer)+(yyvsp[-8].integer));
					float	*argf4	=	(float *)	get((yyvsp[-6].integer)+(yyvsp[-7].integer)+(yyvsp[-7].integer));
					float	*argf5	=	(float *)	get((yyvsp[-5].integer)+(yyvsp[-6].integer)+(yyvsp[-7].integer)+(yyvsp[-8].integer));
					int		*argi6	=	(int *)		get((yyvsp[-4].integer)+(yyvsp[-5].integer)+(yyvsp[-6].integer)+(yyvsp[-7].integer)+(yyvsp[-8].integer));
					float	*argf7	=	(float *)	get((yyvsp[-3].integer)+(yyvsp[-4].integer)+(yyvsp[-5].integer)+(yyvsp[-6].integer)+(yyvsp[-7].integer)+(yyvsp[-8].integer));
					float	*argf8	=	(float *)	get((yyvsp[-2].integer)+(yyvsp[-3].integer)+(yyvsp[-4].integer)+(yyvsp[-5].integer)+(yyvsp[-6].integer)+(yyvsp[-7].integer)+(yyvsp[-8].integer));
					float	*argf9	=	(float *)	get((yyvsp[-1].integer)+(yyvsp[-2].integer)+(yyvsp[-3].integer)+(yyvsp[-4].integer)+(yyvsp[-5].integer)+(yyvsp[-6].integer)+(yyvsp[-7].integer)+(yyvsp[-8].integer));

					RiTrimCurve((yyvsp[-8].integer),argi1,argi2,argf3,argf4,argf5,argi6,argf7,argf8,argf9);
				;}
    break;

  case 120:
#line 2074 "rib.y"
    {
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiSphereV((yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real),numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 121:
#line 2090 "rib.y"
    {
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiSphereV((yyvsp[-5].real),(yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 122:
#line 2103 "rib.y"
    {
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiConeV((yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real),numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 123:
#line 2118 "rib.y"
    {
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiConeV((yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 124:
#line 2132 "rib.y"
    {
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiCylinderV((yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real),numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 125:
#line 2148 "rib.y"
    {
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiCylinderV((yyvsp[-5].real),(yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 126:
#line 2165 "rib.y"
    {
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RtPoint	p1,p2;

							p1[0]	=	(yyvsp[-7].real);
							p1[1]	=	(yyvsp[-6].real);
							p1[2]	=	(yyvsp[-5].real);
							p2[0]	=	(yyvsp[-4].real);
							p2[1]	=	(yyvsp[-3].real);
							p2[2]	=	(yyvsp[-2].real);

							RiHyperboloidV(p1,p2,(yyvsp[-1].real),numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 127:
#line 2193 "rib.y"
    {
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RtPoint	p1,p2;

							p1[0]	=	(yyvsp[-8].real);
							p1[1]	=	(yyvsp[-7].real);
							p1[2]	=	(yyvsp[-6].real);
							p2[0]	=	(yyvsp[-5].real);
							p2[1]	=	(yyvsp[-4].real);
							p2[2]	=	(yyvsp[-3].real);

							RiHyperboloidV(p1,p2,(yyvsp[-2].real),numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 128:
#line 2216 "rib.y"
    {
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiParaboloidV((yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real),numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 129:
#line 2232 "rib.y"
    {
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiParaboloidV((yyvsp[-5].real),(yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 130:
#line 2245 "rib.y"
    {
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiDiskV((yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real),numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 131:
#line 2260 "rib.y"
    {
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiDiskV((yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 132:
#line 2275 "rib.y"
    {
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiTorusV((yyvsp[-5].real),(yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real),numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 133:
#line 2292 "rib.y"
    {
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiTorusV((yyvsp[-6].real),(yyvsp[-5].real),(yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 134:
#line 2305 "rib.y"
    {
					int			*argi1		=	(int *) get(0);
					int			numVertices,numUniforms;
					CAttributes	*attributes	=	currentRenderer->getAttributes(FALSE);
					int			wrap;
					int			numVaryings,i;

					if (strcmp((yyvsp[-1].string),RI_PERIODIC) == 0) {
						wrap	=	TRUE;
					} else {
						wrap	=	FALSE;
					}

					if (strcmp((yyvsp[-3].string),RI_LINEAR) == 0) {
						for (i=0,numVertices=0;i<(yyvsp[-2].integer);i++) {
							numVertices	+=	argi1[i];
						}

						numVaryings		=	numVertices;
						numUniforms		=	(yyvsp[-2].integer);
					} else if (strcmp((yyvsp[-3].string),RI_CUBIC) == 0) {
						for (i=0,numVertices=0,numVaryings=0,numUniforms=0;i<(yyvsp[-2].integer);i++) {
							int	j		=	(argi1[i] - 4) / attributes->vStep + 1;
							numVertices	+=	argi1[i];
							numVaryings	+=	j + (1 - wrap);
						}
						numUniforms		=	(yyvsp[-2].integer);
					} else {
						error(CODE_BADTOKEN,"Unknown patch type: \"%s\"\n",(yyvsp[-3].string));
						numVertices	=	0;
					}

					if (numVertices > 0) {
						if (parameterListCheck()) {
							if (sizeCheck(numVertices,numVaryings,0,numUniforms)) {
								RiCurvesV((yyvsp[-3].string),(yyvsp[-2].integer),argi1,(yyvsp[-1].string),numParameters,tokens,vals);
							}
						}
					}
				;}
    break;

  case 135:
#line 2348 "rib.y"
    {
					if (parameterListCheck()) {
						if (sizeCheck(numVertex,0,0,1)) {
							RiPointsV(numVertex,numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 136:
#line 2365 "rib.y"
    {
					int		*argi1,*argi2,*argi3,*argi4;
					char	**args1;
					float	*argf1;
					int		numVertices,i,j;

					if (parameterListCheck()) {
						argi1	=	(int *)		get(0);
						argi2	=	(int *)		get((yyvsp[-6].integer));
						args1	=	(char **)	get((yyvsp[-6].integer)+(yyvsp[-5].integer));
						argi3	=	(int *)		get((yyvsp[-6].integer)+(yyvsp[-5].integer)+(yyvsp[-4].integer));
						argi4	=	(int *)		get((yyvsp[-6].integer)+(yyvsp[-5].integer)+(yyvsp[-4].integer)+(yyvsp[-3].integer));
						argf1	=	(float *)	get((yyvsp[-6].integer)+(yyvsp[-5].integer)+(yyvsp[-4].integer)+(yyvsp[-3].integer)+(yyvsp[-2].integer));

						// Count the number of faces / vertices
						for (i=0,j=0;i<(yyvsp[-6].integer);j+=argi1[i],i++);

						for (numVertices=-1,i=0;i<j;i++) {
							if (argi2[i] > numVertices)	numVertices	=	argi2[i];
						}
						numVertices++;


						if (sizeCheck(numVertices,numVertices,j,(yyvsp[-6].integer))) {
							RiSubdivisionMeshV((yyvsp[-7].string),(yyvsp[-6].integer),argi1,argi2,(yyvsp[-4].integer),args1,argi3,argi4,argf1,numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 137:
#line 2399 "rib.y"
    {
					int		*argi1,*argi2;
					int		numVertices,i,j;

					if (parameterListCheck()) {
						argi1	=	(int *) get(0);
						argi2	=	(int *) get((yyvsp[-2].integer));

						// Count the number of faces / vertices
						for (i=0,j=0;i<(yyvsp[-2].integer);j+=argi1[i],i++);

						for (numVertices=-1,i=0;i<j;i++) {
							if (argi2[i] > numVertices)	numVertices	=	argi2[i];
						}
						numVertices++;


						if (sizeCheck(numVertices,numVertices,j,(yyvsp[-2].integer))) {
							RiSubdivisionMeshV((yyvsp[-3].string),(yyvsp[-2].integer),argi1,argi2,0,NULL,NULL,NULL,NULL,numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 138:
#line 2427 "rib.y"
    {
					// FIXME: Not implemented
				;}
    break;

  case 139:
#line 2434 "rib.y"
    {
					if (parameterListCheck()) {
						RiGeometryV((yyvsp[-1].string),numParameters,tokens,vals);
					}
				;}
    break;

  case 140:
#line 2451 "rib.y"
    {
					RtBound			bound;
					CDelayedData	*cData	=	new CDelayedData;
					char			**arg;

					bound[0]	=	(yyvsp[-6].real);
					bound[1]	=	(yyvsp[-5].real);
					bound[2]	=	(yyvsp[-4].real);
					bound[3]	=	(yyvsp[-3].real);
					bound[4]	=	(yyvsp[-2].real);
					bound[5]	=	(yyvsp[-1].real);

					cData->bmin[COMP_X]	=	(yyvsp[-6].real);
					cData->bmin[COMP_Y]	=	(yyvsp[-5].real);
					cData->bmin[COMP_Z]	=	(yyvsp[-4].real);

					cData->bmax[COMP_X]	=	(yyvsp[-3].real);
					cData->bmax[COMP_Y]	=	(yyvsp[-2].real);
					cData->bmax[COMP_Z]	=	(yyvsp[-1].real);

					if (strcmp((yyvsp[-9].string),RI_PROCDELAYEDREADARCHIVE) == 0) {
						if ((yyvsp[-8].integer) != 1) {
							error(CODE_MISSINGDATA,"Proc delayed archive expects one argument (given %d)\n",(yyvsp[-8].integer));
						} else {
							arg		=	(char **) get(0);

							cData->generator	=	strdup(arg[0]);

							RiProcedural((RtPointer) cData,bound,RiProcDelayedReadArchive,RiProcFree);
						}
					} else if (strcmp((yyvsp[-9].string),RI_PROCRUNPROGRAM) == 0) {
						if ((yyvsp[-8].integer) != 2) {
							error(CODE_MISSINGDATA,"Proc delayed archive expects two arguments (given %d)\n",(yyvsp[-8].integer));
						} else {
							arg		=	(char **) get(0);

							cData->generator	=	strdup(arg[0]);
							cData->helper		=	strdup(arg[1]);

							RiProcedural((RtPointer) cData,bound,RiProcRunProgram,RiProcFree);
						}
					} else if (strcmp((yyvsp[-9].string),RI_PROCDYNAMICLOAD) == 0) {
						if ((yyvsp[-8].integer) != 2) {
							error(CODE_MISSINGDATA,"Proc delayed archive expects two arguments (given %d)\n",(yyvsp[-8].integer));
						} else {
							arg		=	(char **) get(0);

							cData->generator	=	strdup(arg[0]);
							cData->helper		=	strdup(arg[1]);

							RiProcedural((RtPointer) cData,bound,RiProcDynamicLoad,RiProcFree);
						}
					} else {
						error(CODE_BADTOKEN,"Unknown procedural: %s\n",(yyvsp[-9].string));
						delete cData;
					}
				;}
    break;

  case 141:
#line 2511 "rib.y"
    {
					RiSolidBegin((yyvsp[0].string));
				;}
    break;

  case 142:
#line 2516 "rib.y"
    {
					RiSolidEnd();
				;}
    break;

  case 143:
#line 2522 "rib.y"
    {
					if (ribObjects == NULL)	ribObjects	=	new CArray<RtPointer>;

					(*ribObjects)[(int) (yyvsp[0].real)]	=	RiObjectBegin();
				;}
    break;

  case 144:
#line 2529 "rib.y"
    {
					RiObjectEnd();
				;}
    break;

  case 145:
#line 2535 "rib.y"
    {
					if (ribObjects != NULL) {
						RiObjectInstance((*ribObjects)[(int) (yyvsp[0].real)]);
					} else {
						error(CODE_MISSINGDATA,"Object %d is not found\n",(int) (yyvsp[0].real));
					}
				;}
    break;

  case 146:
#line 2545 "rib.y"
    {
					float	*argf	=	(float *) get(0);

					RiMotionBeginV((yyvsp[0].integer),argf);
				;}
    break;

  case 147:
#line 2552 "rib.y"
    {
					RiMotionEnd();
				;}
    break;

  case 148:
#line 2565 "rib.y"
    {
					RtFilterFunc	f;

					if ((f		=	getFilter((yyvsp[-3].string))) != NULL)  {
						RiMakeTextureV((yyvsp[-7].string),(yyvsp[-6].string),(yyvsp[-5].string),(yyvsp[-4].string),f,(yyvsp[-2].real),(yyvsp[-1].real),numParameters,tokens,vals);
					}
				;}
    break;

  case 149:
#line 2577 "rib.y"
    {
					RiMakeTexture3DV((yyvsp[-2].string),(yyvsp[-1].string),numParameters,tokens,vals);
				;}
    break;

  case 150:
#line 2590 "rib.y"
    {
					RtFilterFunc	f;

					if ((f		=	getFilter((yyvsp[-3].string))) != NULL) {
						RiMakeBumpV((yyvsp[-7].string),(yyvsp[-6].string),(yyvsp[-5].string),(yyvsp[-4].string),f,(yyvsp[-2].real),(yyvsp[-1].real),numParameters,tokens,vals);
					}
				;}
    break;

  case 151:
#line 2605 "rib.y"
    {
					RtFilterFunc	f;

					if ((f		=	getFilter((yyvsp[-3].string))) != NULL) {
						RiMakeLatLongEnvironmentV((yyvsp[-5].string),(yyvsp[-4].string),f,(yyvsp[-2].real),(yyvsp[-1].real),numParameters,tokens,vals);
					}
				;}
    break;

  case 152:
#line 2626 "rib.y"
    {
					RtFilterFunc	f;

					if ((f =	getFilter((yyvsp[-3].string))) != NULL) {
						RiMakeCubeFaceEnvironmentV((yyvsp[-11].string),(yyvsp[-10].string),(yyvsp[-9].string),(yyvsp[-8].string),(yyvsp[-7].string),(yyvsp[-6].string),(yyvsp[-5].string),(yyvsp[-4].real),f,(yyvsp[-2].real),(yyvsp[-1].real),numParameters,tokens,vals);
					}
				;}
    break;

  case 153:
#line 2638 "rib.y"
    {
					RiMakeShadowV((yyvsp[-2].string),(yyvsp[-1].string),numParameters,tokens,vals);
				;}
    break;

  case 154:
#line 2644 "rib.y"
    {
					RtErrorHandler 	e	=	getErrorHandler((yyvsp[0].string));

					if (e != NULL) {
						RiErrorHandler(e);
					}
				;}
    break;

  case 155:
#line 2654 "rib.y"
    {
				;}
    break;

  case 156:
#line 2659 "rib.y"
    {
				;}
    break;

  case 157:
#line 2663 "rib.y"
    {
					if (YYRECOVERING() == 0) {
						error(CODE_BADFILE,"Syntax error.\n");
					}
				;}
    break;


    }

/* Line 1037 of yacc.c.  */
#line 4024 "rib.cpp"

  yyvsp -= yylen;
  yyssp -= yylen;


  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* If at end of input, pop the error token,
	     then the rest of the stack, then return failure.  */
	  if (yychar == YYEOF)
	     for (;;)
	       {

		 YYPOPSTACK;
		 if (yyssp == yyss)
		   YYABORT;
		 yydestruct ("Error: popping",
                             yystos[*yyssp], yyvsp);
	       }
        }
      else
	{
	  yydestruct ("Error: discarding", yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

#ifdef __GNUC__
  /* Pacify GCC when the user code never invokes YYERROR and the label
     yyerrorlab therefore never appears in user code.  */
  if (0)
     goto yyerrorlab;
#endif

yyvsp -= yylen;
  yyssp -= yylen;
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping", yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token. */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yydestruct ("Error: discarding lookahead",
              yytoken, &yylval);
  yychar = YYEMPTY;
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 2670 "rib.y"


#include "lex.rib.cpp"

// Our position in the rib file
static	int		ribStart	=	0;
static	int		ribStep		=	5*(1<<10);	// Parse 5 KB at a time

///////////////////////////////////////////////////////////////////////
// Function				:	riberror
// Description			:	Parser error file
// Return Value			:	-
// Comments				:
// Date last edited		:	10/8/2001
void	riberror(char *s,...) {
	warning(CODE_BADFILE,"RIB Parse error\n");
}

///////////////////////////////////////////////////////////////////////
// Function				:	ribParse
// Description			:	Parse a rib file
// Return Value			:	-
// Comments				:
// Date last edited		:	10/8/2001
void	ribParse(const char *fileName,void (*c)(const char *)) {
	if (fileName != NULL) {
		

		// Save the environment first
		CArray<RtPointer>	*savedLights					=	lights;
		CTrie<RtPointer>	*savedLightNames				=	lightNames;
		CArray<RtPointer>	*savedObjects					=	ribObjects;
		CArray<char *>		*savedAllocatedStrings			=	allocatedStrings;
		int					savedRibLineno					=	ribLineno;
		const char			*savedActivity					=	stats.activity;
		void				(*savedCallback)(const char *)	=	callback;
		ERIBValue			*savedArgs						=	args;
		int					savedNumArguments				=	numArguments;
		int					savedMaxArgument				=	maxArgument;
		int					savedArgumentStepSize			=	argumentStepSize;
		int					savedNumParameters				=	numParameters;
		int					savedMaxParameter				=	maxParameter;
		TParameter			*savedParameters				=	parameters;
		RtToken				*savedTokens					=	tokens;
		RtPointer			*savedVals						=	vals;
		int					savedRibDepth					=	ribDepth;
		YY_BUFFER_STATE		savedLexState					=	YY_CURRENT_BUFFER;
		TRibFile			*savedRibStack					=	ribStack;
		const char			*savedRibFile					=	ribFile;
		FILE				*savedRibIn						=	ribin;

		

		// Init the environment
		if (fileName[0] == '-') {
			// Read from stdin
#ifdef HAVE_ZLIB
			ribin			=	(FILE *) gzdopen(fileno(stdin),"rb");
#else
			ribin			=	stdin;
#endif
		} else if (fileName[0] == '|') {
			// Read from an arbitrary stream
#ifdef HAVE_ZLIB
			ribin			=	(FILE *) gzdopen(atoi(fileName+1),"rb");
#else
			ribin			=	fdopen(atoi(fileName+1),"r");
#endif		
		} else {
			// Read from file
#ifdef HAVE_ZLIB
			ribin			=	(FILE *) gzopen(fileName,"rb");
#else
			ribin			=	fopen(fileName,"r");
#endif
		}

		lights				=	NULL;
		lightNames			=	NULL;
		ribObjects			=	NULL;
		allocatedStrings	=	new CArray<char *>;
		stats.activity		=	"Rib parsing";
		callback			=	c;
		maxArgument			=	1000;
		argumentStepSize	=	100000;
		numArguments		=	0;
		args				=	new ERIBValue[maxArgument];
		maxParameter		=	20;
		numParameters		=	0;
		parameters			=	new TParameter[maxParameter];
		tokens				=	new RtToken[maxParameter];
		vals				=	new RtPointer[maxParameter];
		
		if ( ribDepth++ == 0) {
			// for the outermost depth only,
			// allocate storage for strings valid over the while rib
			permaStrings	=	new CArray<char *>;
		} else {
			// create a new lex buffer and switch to it
			
			// Note: there are two stacking methods here,
			//  one is explicitly handled when lexing for ReadArchive
			//	the other uses the return stack (and increments ribDepth)

			rib_switch_to_buffer(rib_create_buffer( ribin, YY_BUF_SIZE ) );	
			ribStack		=	NULL;	// prevent falling out of current ReadArchive
		}
		
		ribLineno			=	1;

		ribparse();

		if (ribin != NULL) {
#ifdef HAVE_ZLIB
			gzclose(ribin);
#else
			fclose(ribin);
#endif
		}

		if (lights != NULL)		delete lights;
		if (lightNames != NULL)	delete lightNames;
		if (ribObjects != NULL)	delete ribObjects;
		delete allocatedStrings;
		delete [] args;
		delete [] parameters;
		delete [] tokens;
		delete [] vals;
		

		ribin				=	savedRibIn;
		ribFile				=	savedRibFile;
		tokens				=	savedTokens;
		vals				=	savedVals;
		parameters			=	savedParameters;
		numParameters		=	savedNumParameters;
		maxParameter		=	savedMaxParameter;
		maxArgument			=	savedMaxArgument;
		numArguments		=	savedNumArguments;
		argumentStepSize	=	savedArgumentStepSize;
		args				=	savedArgs;
		lightNames			=	savedLightNames;
		lights				=	savedLights;
		ribObjects			=	savedObjects;
		ribLineno			=	savedRibLineno;
		allocatedStrings	=	savedAllocatedStrings;
		stats.activity		=	savedActivity;
		callback			=	savedCallback;
		
		if ((ribDepth = savedRibDepth) == 0) {
			// for the outermost depth only,
			// deallocate storage for strings valid over the while rib
			char *currentString;
			while((currentString=permaStrings->pop()) != NULL) {
				free(currentString);
			}
			
			delete permaStrings;
		} else {
			// We're done parsing an inner level, switch the lex buffer back
			
			rib_delete_buffer( YY_CURRENT_BUFFER );
			rib_switch_to_buffer( savedLexState );
			
			ribStack 		= 	savedRibStack;
		}
	}
}



///////////////////////////////////////////////////////////////////////
// Function				:	parserCleanup
// Description			:	Clean the memory allocated by the parser
// Return Value			:	-
// Comments				:
// Date last edited		:	10/8/2001
void		parserCleanup() {
	rib_delete_buffer(YY_CURRENT_BUFFER);
	yy_init				= 1;
}


