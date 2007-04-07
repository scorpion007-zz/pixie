/* A Bison parser, made by GNU Bison 2.1.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005 Free Software Foundation, Inc.

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
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Bison version.  */
#define YYBISON_VERSION "2.1"

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
     RIB_ARCHIVE_BEGIN = 358,
     RIB_ARCHIVE_END = 359,
     RIB_RESOURCE = 360,
     RIB_RESOURCE_BEGIN = 361,
     RIB_RESOURCE_END = 362,
     RIB_IFBEGIN = 363,
     RIB_IFEND = 364,
     RIB_ELSEIF = 365,
     RIB_ELSE = 366,
     RIB_ERROR_HANDLER = 367,
     RIB_VERSION = 368,
     RIB_VERSION_STRING = 369,
     RIB_ARRAY_BEGIN = 370,
     RIB_ARRAY_END = 371,
     RIB_TEXT = 372,
     RIB_FLOAT = 373,
     RIB_STRUCTURE_COMMENT = 374
   };
#endif
/* Tokens.  */
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
#define RIB_ARCHIVE_BEGIN 358
#define RIB_ARCHIVE_END 359
#define RIB_RESOURCE 360
#define RIB_RESOURCE_BEGIN 361
#define RIB_RESOURCE_END 362
#define RIB_IFBEGIN 363
#define RIB_IFEND 364
#define RIB_ELSEIF 365
#define RIB_ELSE 366
#define RIB_ERROR_HANDLER 367
#define RIB_VERSION 368
#define RIB_VERSION_STRING 369
#define RIB_ARRAY_BEGIN 370
#define RIB_ARRAY_END 371
#define RIB_TEXT 372
#define RIB_FLOAT 373
#define RIB_STRUCTURE_COMMENT 374




/* Copy the first part of user declarations.  */
#line 1 "rib.y"

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
#include "delayed.h"
#include "rib.h"
#include "rendererContext.h"
#include "renderer.h"
#include "error.h"
#include "ri_config.h"

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

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 58 "rib.y"
typedef union ribval {
	float	real;
	char	*string;
	int		integer;
} YYSTYPE;
/* Line 196 of yacc.c.  */
#line 394 "rib.cpp"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */
#line 64 "rib.y"

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

// Holds information about a parameter
typedef struct {
	char			*name;			// Name of the parameter
	ERIBType		type;			// Type of the parameter
	int				numItems;		// Number of items of type ERIBValue
	int				valuesStart;	// Index in the argument list where the parameter starts
} TParameter;

typedef struct TLight {
	char			*name;			// The name of the light (if any)
	RtLightHandle	handle;			// The returned handle
	TLight			*next;			// The next light in the list
	int				index;			// The index of the light
} TLight;

typedef struct TObject {
	RtObjectHandle	handle;			// The handle of the object
	TObject			*next;			// The next in the list
	int				index;			// The index of the object
} TObject;

static	int					ribDepth					=	0;		// The rib parsing stack depth
static	int					numConstant					=	0;		// The number of constant
static	int					numVertex					=	0;		// The number of vertices
static	int					numVarying					=	0;		// The number of varyings
static	int					numFaceVarying				=	0;		// The number of facevaryings
static	int					numUniform					=	0;		// The number of uniforms
static	TLight				*lights						=	NULL;	// The linked list of light handles
static	TObject				*objects					=	NULL;	// The linked list of object handles
static	void				(*callback)(const char *)	=	NULL;	// The callback function for the parser

static	TMemCheckpoint		worldCheckpoint;
static	TMemCheckpoint		memoryCheckpoint;						// We use this to put a checkpoint to the memory
static	CArray<float>		floatArgs;								// The array of float arguments
static	CArray<int>			intArgs;								// The array of integer arguments
static	CArray<char *>		stringArgs;								// The array of string arguments

static	int					numParameters				=	0;
static	int					maxParameter				=	0;
static	RtToken				*tokens						=	NULL;
static	RtPointer			*vals						=	NULL;
static	TParameter			*parameters					=	NULL;

		const char			*ribFile					=	NULL;	// The RIB file that we're parsing now
		int					ribLineno					=	-1;		// The line number in the rib file (where the parser is at)
		int					ribCommandLineno			=	-1;		// The line number of the last executed command in the RIB


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

#define	getFloat(__n)		(floatArgs.array + __n)
#define	getInt(__n)			(intArgs.array + __n)
#define	getString(__n)		(stringArgs.array + __n)

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
static	char			*toLowerCase(char *s) {
	int	i;
	int	l	=	(int) strlen(s);

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
		CVariable		*var	=	CRenderer::retrieveVariable(par->name);
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
					CAttributes	*attributes	=	CRenderer::context->getAttributes(FALSE);
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
				// We need to convert the float argument list to int
				int	j;
				T32	*dest	=	(T32 *) vals[i];

				// FIXME: We're doing an ugly conversion here
				// These assertions must be valid even on 64 bit platforms
				assert(sizeof(T32) == 4);
				assert(sizeof(float) == sizeof(int));
				
				for (j=par->numItems;j>0;j--,dest++) {
					dest->integer	=	(int) dest->real;
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
	} else if (strcmp(name,RI_BLACKMANHARRISFILTER) == 0) {
		f = RiBlackmanHarrisFilter;
	} else if (strcmp(name,RI_MITCHELLFILTER) == 0) {
		f = RiMitchellFilter;
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




/* Line 219 of yacc.c.  */
#line 836 "rib.cpp"

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T) && (defined (__STDC__) || defined (__cplusplus))
# include <stddef.h> /* INFRINGES ON USER NAME SPACE */
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#if ! defined (yyoverflow) || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if defined (__STDC__) || defined (__cplusplus)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     define YYINCLUDED_STDLIB_H
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2005 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM ((YYSIZE_T) -1)
#  endif
#  ifdef __cplusplus
extern "C" {
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if (! defined (malloc) && ! defined (YYINCLUDED_STDLIB_H) \
	&& (defined (__STDC__) || defined (__cplusplus)))
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if (! defined (free) && ! defined (YYINCLUDED_STDLIB_H) \
	&& (defined (__STDC__) || defined (__cplusplus)))
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifdef __cplusplus
}
#  endif
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
	  YYSIZE_T yyi;				\
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
#define YYLAST   683

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  120
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  14
/* YYNRULES -- Number of rules. */
#define YYNRULES  163
/* YYNRULES -- Number of states. */
#define YYNSTATES  665

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   374

#define YYTRANSLATE(YYX)						\
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
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    13,    15,    18,    20,
      24,    27,    29,    31,    35,    38,    42,    44,    47,    48,
      51,    54,    55,    59,    60,    62,    66,    68,    71,    73,
      75,    77,    82,    85,    91,    99,   105,   113,   117,   121,
     129,   134,   136,   140,   143,   147,   152,   156,   160,   167,
     173,   177,   181,   184,   188,   191,   195,   197,   199,   204,
     209,   216,   223,   233,   245,   250,   255,   259,   264,   269,
     273,   277,   281,   285,   289,   293,   296,   299,   302,   312,
     320,   330,   338,   344,   352,   356,   359,   362,   364,   367,
     369,   389,   409,   412,   417,   422,   428,   437,   448,   452,
     456,   459,   462,   464,   466,   470,   473,   477,   482,   488,
     494,   517,   540,   580,   584,   592,   605,   616,   623,   632,
     638,   646,   653,   662,   672,   684,   691,   700,   706,   714,
     722,   732,   738,   741,   751,   757,   763,   767,   779,   782,
     784,   787,   789,   792,   795,   797,   807,   812,   822,   830,
     844,   849,   853,   855,   857,   859,   864,   868,   870,   874,
     876,   879,   882,   885
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short int yyrhs[] =
{
     121,     0,    -1,   131,    -1,   122,   118,    -1,   118,    -1,
     123,   118,    -1,   118,    -1,   124,   117,    -1,   117,    -1,
     115,   123,   116,    -1,   115,   116,    -1,   125,    -1,   123,
      -1,   115,   122,   116,    -1,   115,   116,    -1,   115,   124,
     116,    -1,   117,    -1,   130,   129,    -1,    -1,   117,   126,
      -1,   117,   128,    -1,    -1,   131,   132,   133,    -1,    -1,
     119,    -1,     3,   117,   117,    -1,     4,    -1,     4,   118,
      -1,     5,    -1,     6,    -1,     7,    -1,     8,   118,   118,
     118,    -1,     9,   118,    -1,    10,   118,   118,   118,   118,
      -1,    10,   115,   118,   118,   118,   118,   116,    -1,    11,
     118,   118,   118,   118,    -1,    11,   115,   118,   118,   118,
     118,   116,    -1,    12,   117,   129,    -1,    13,   118,   118,
      -1,    14,   118,   118,   118,   118,   118,   118,    -1,    15,
     118,   118,   118,    -1,    15,    -1,    16,   118,   118,    -1,
      17,   118,    -1,    18,   118,   118,    -1,    19,   117,   118,
     118,    -1,    20,   118,   118,    -1,    21,   117,   129,    -1,
      22,   117,   118,   118,   118,   118,    -1,    23,   117,   117,
     117,   129,    -1,    24,   117,   129,    -1,    25,   117,   129,
      -1,    26,   126,    -1,    26,   125,   125,    -1,    27,   118,
      -1,    28,   117,   129,    -1,    29,    -1,    30,    -1,    31,
     118,   118,   118,    -1,    32,   118,   118,   118,    -1,    31,
     115,   118,   118,   118,   116,    -1,    32,   115,   118,   118,
     118,   116,    -1,    33,   118,   118,   118,   118,   118,   118,
     118,   118,    -1,    33,   115,   118,   118,   118,   118,   118,
     118,   118,   118,   116,    -1,    34,   117,   118,   129,    -1,
      34,   117,   117,   129,    -1,    34,   117,   129,    -1,    35,
     117,   118,   129,    -1,    35,   117,   117,   129,    -1,    36,
     118,   118,    -1,    36,   117,   118,    -1,    37,   117,   129,
      -1,    38,   117,   129,    -1,    39,   117,   129,    -1,    40,
     117,   129,    -1,    41,   118,    -1,    42,   117,    -1,    43,
     118,    -1,    44,   115,   118,   118,   118,   118,   118,   118,
     116,    -1,    44,   118,   118,   118,   118,   118,   118,    -1,
      45,   115,   118,   118,   118,   118,   118,   118,   116,    -1,
      45,   118,   118,   118,   118,   118,   118,    -1,    46,   118,
     118,   118,   118,    -1,    46,   115,   118,   118,   118,   118,
     116,    -1,    47,   117,   118,    -1,    48,   117,    -1,    49,
     117,    -1,    50,    -1,    51,   118,    -1,    52,    -1,    53,
     115,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   116,    -1,    54,
     115,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   116,    -1,    55,
     118,    -1,    56,   118,   118,   118,    -1,    58,   118,   118,
     118,    -1,    57,   118,   118,   118,   118,    -1,    59,   118,
     118,   118,   118,   118,   118,   118,    -1,    59,   115,   118,
     118,   118,   118,   118,   118,   118,   116,    -1,    60,   117,
     129,    -1,    61,   117,   129,    -1,    62,   117,    -1,    63,
     117,    -1,    64,    -1,    65,    -1,    66,   117,   129,    -1,
      67,   129,    -1,    68,   127,   129,    -1,    69,   127,   127,
     129,    -1,    70,   127,   127,   127,   129,    -1,    71,   117,
     118,   117,   118,    -1,    71,   115,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   116,   118,   117,   118,    -1,    71,   117,   118,
     115,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   116,   118,    -1,
      71,   115,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   116,   118,
     115,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   116,   118,    -1,
      72,   117,   129,    -1,    73,   117,   118,   117,   118,   117,
     129,    -1,    74,   118,   118,   125,   118,   118,   118,   118,
     125,   118,   118,   129,    -1,    75,   127,   127,   125,   125,
     125,   127,   125,   125,   125,    -1,    76,   118,   118,   118,
     118,   129,    -1,    76,   115,   118,   118,   118,   118,   116,
     129,    -1,    77,   118,   118,   118,   129,    -1,    77,   115,
     118,   118,   118,   116,   129,    -1,    78,   118,   118,   118,
     118,   129,    -1,    78,   115,   118,   118,   118,   118,   116,
     129,    -1,    79,   118,   118,   118,   118,   118,   118,   118,
     129,    -1,    79,   115,   118,   118,   118,   118,   118,   118,
     118,   116,   129,    -1,    80,   118,   118,   118,   118,   129,
      -1,    80,   115,   118,   118,   118,   118,   116,   129,    -1,
      81,   118,   118,   118,   129,    -1,    81,   115,   118,   118,
     118,   116,   129,    -1,    82,   118,   118,   118,   118,   118,
     129,    -1,    82,   115,   118,   118,   118,   118,   118,   116,
     129,    -1,    83,   117,   127,   117,   129,    -1,    85,   129,
      -1,    86,   117,   127,   127,   128,   127,   127,   125,   129,
      -1,    86,   117,   127,   127,   129,    -1,    87,   118,   125,
     128,   129,    -1,    84,   117,   129,    -1,    88,   117,   128,
     115,   118,   118,   118,   118,   118,   118,   116,    -1,    89,
     117,    -1,    90,    -1,    91,   118,    -1,    92,    -1,    93,
     118,    -1,    94,   126,    -1,    95,    -1,    96,   117,   117,
     117,   117,   117,   118,   118,   129,    -1,    97,   117,   117,
     129,    -1,    98,   117,   117,   117,   117,   117,   118,   118,
     129,    -1,    99,   117,   117,   117,   118,   118,   129,    -1,
     100,   117,   117,   117,   117,   117,   117,   117,   118,   117,
     118,   118,   129,    -1,   101,   117,   117,   129,    -1,   103,
     117,   129,    -1,   104,    -1,   106,    -1,   107,    -1,   105,
     117,   117,   129,    -1,   108,   117,   129,    -1,   109,    -1,
     110,   117,   129,    -1,   111,    -1,   112,   117,    -1,   113,
     118,    -1,   113,   114,    -1,     1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   621,   621,   624,   631,   639,   646,   653,   660,   667,
     674,   682,   687,   693,   700,   708,   715,   724,   729,   747,
     759,   773,   772,   789,   793,   800,   807,   812,   818,   823,
     836,   844,   852,   858,   867,   878,   887,   898,   905,   912,
     923,   931,   936,   943,   949,   956,   968,   975,   985,   995,
    1004,  1011,  1020,  1034,  1049,  1055,  1064,  1069,  1074,  1088,
    1102,  1118,  1134,  1147,  1162,  1175,  1188,  1195,  1208,  1221,
    1237,  1255,  1262,  1269,  1276,  1283,  1289,  1295,  1301,  1323,
    1343,  1365,  1385,  1394,  1405,  1412,  1418,  1424,  1429,  1435,
    1440,  1482,  1524,  1530,  1538,  1546,  1555,  1567,  1581,  1588,
    1595,  1601,  1607,  1612,  1617,  1626,  1636,  1649,  1685,  1729,
    1742,  1791,  1840,  1919,  1945,  2021,  2054,  2078,  2092,  2108,
    2121,  2136,  2150,  2166,  2192,  2220,  2234,  2250,  2263,  2278,
    2293,  2310,  2356,  2366,  2404,  2432,  2441,  2450,  2519,  2525,
    2530,  2541,  2546,  2562,  2570,  2575,  2592,  2600,  2617,  2632,
    2653,  2661,  2668,  2673,  2678,  2683,  2691,  2698,  2703,  2710,
    2715,  2725,  2730,  2735
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
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
  "RIB_MAKE_SHADOW", "RIB_ARCHIVE_RECORD", "RIB_ARCHIVE_BEGIN",
  "RIB_ARCHIVE_END", "RIB_RESOURCE", "RIB_RESOURCE_BEGIN",
  "RIB_RESOURCE_END", "RIB_IFBEGIN", "RIB_IFEND", "RIB_ELSEIF", "RIB_ELSE",
  "RIB_ERROR_HANDLER", "RIB_VERSION", "RIB_VERSION_STRING",
  "RIB_ARRAY_BEGIN", "RIB_ARRAY_END", "RIB_TEXT", "RIB_FLOAT",
  "RIB_STRUCTURE_COMMENT", "$accept", "start", "ribIntString",
  "ribFloatString", "ribTextString", "ribFloatArray", "ribFloats",
  "ribIntArray", "ribTextArray", "ribPL", "ribParameter", "ribCommands",
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
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,   120,   121,   122,   122,   123,   123,   124,   124,   125,
     125,   126,   126,   127,   127,   128,   128,   129,   129,   130,
     130,   132,   131,   131,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     2,     1,     2,     1,     2,     1,     3,
       2,     1,     1,     3,     2,     3,     1,     2,     0,     2,
       2,     0,     3,     0,     1,     3,     1,     2,     1,     1,
       1,     4,     2,     5,     7,     5,     7,     3,     3,     7,
       4,     1,     3,     2,     3,     4,     3,     3,     6,     5,
       3,     3,     2,     3,     2,     3,     1,     1,     4,     4,
       6,     6,     9,    11,     4,     4,     3,     4,     4,     3,
       3,     3,     3,     3,     3,     2,     2,     2,     9,     7,
       9,     7,     5,     7,     3,     2,     2,     1,     2,     1,
      19,    19,     2,     4,     4,     5,     8,    10,     3,     3,
       2,     2,     1,     1,     3,     2,     3,     4,     5,     5,
      22,    22,    39,     3,     7,    12,    10,     6,     8,     5,
       7,     6,     8,     9,    11,     6,     8,     5,     7,     7,
       9,     5,     2,     9,     5,     5,     3,    11,     2,     1,
       2,     1,     2,     2,     1,     9,     4,     9,     7,    13,
       4,     3,     1,     1,     1,     4,     3,     1,     3,     1,
       2,     2,     2,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
      23,     0,    21,     1,     0,   163,     0,    26,    28,    29,
      30,     0,     0,     0,     0,     0,     0,     0,    41,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    56,    57,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    87,     0,    89,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   102,   103,     0,
      18,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    18,     0,
       0,     0,     0,   139,     0,   141,     0,     0,   144,     0,
       0,     0,     0,     0,     0,     0,   152,     0,   153,   154,
       0,   157,     0,   159,     0,     0,    24,    22,     0,    27,
       0,    32,     0,     0,     0,     0,    18,     0,     0,     0,
       0,    43,     0,     0,     0,    18,     0,     0,    18,    18,
       0,     6,    12,    11,    52,    54,    18,     0,     0,     0,
       0,     0,     0,    18,     0,     0,     0,    18,    18,    18,
      18,    75,    76,    77,     0,     0,     0,     0,     0,     0,
       0,    85,    86,    88,     0,     0,    92,     0,     0,     0,
       0,     0,    18,    18,   100,   101,    18,     0,   105,    18,
       0,    18,     0,     0,     0,     0,    18,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    18,   132,     0,     0,     0,
     138,   140,   142,    11,   143,     0,     0,     0,     0,     0,
       0,    18,     0,    18,    18,   160,   162,   161,    25,     0,
       0,     0,     0,     0,    37,    38,     0,     0,    42,    44,
       0,    46,    47,     0,     0,    50,    51,    10,     0,     5,
      53,    55,     0,     0,     0,     0,     0,     0,    18,    18,
      66,    18,    18,    70,    69,    71,    72,    73,    74,     0,
       0,     0,     0,     0,     0,    84,     0,     0,     0,     0,
       0,     0,     0,    98,    99,   104,     0,    16,    19,    20,
      17,    14,     4,     0,   106,    18,     0,     0,     0,   113,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   136,     0,
       0,     0,     0,     0,    18,     0,     0,     0,    18,   151,
      18,   156,   158,    31,     0,     0,     0,     0,     0,    40,
      45,     0,    18,     9,     0,    58,     0,    59,     0,     0,
      16,    65,    64,    68,    67,     0,     0,     0,     0,     0,
       0,     0,     0,    93,     0,    94,     0,     0,     8,     0,
      13,     3,   107,    18,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    18,     0,     0,     0,     0,     0,     0,
       0,    18,     0,     0,    18,    18,    18,     0,     0,   146,
       0,     0,     0,   150,   155,     0,    33,     0,    35,     0,
       0,    49,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    82,     0,     0,    95,     0,     0,    15,     7,   108,
       0,     0,   109,     0,     0,     0,     0,    18,     0,   119,
       0,    18,     0,     0,     0,    18,     0,   127,     0,     0,
     131,     0,   134,   135,     0,     0,     0,     0,     0,     0,
       0,     0,    48,    60,    61,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    18,     0,
       0,     0,   117,    18,     0,   121,     0,     0,     0,   125,
      18,     0,    18,     0,     0,     0,     0,    18,     0,    34,
      36,    39,     0,     0,     0,    79,     0,    81,    83,     0,
       0,     0,     0,     0,     0,   114,     0,     0,    18,   120,
      18,     0,     0,    18,   128,     0,   129,     0,     0,     0,
       0,   148,     0,     0,     0,     0,     0,     0,     0,     0,
      96,     0,     0,     0,     0,   118,   122,     0,    18,   126,
      18,    18,     0,    18,    18,     0,     0,    62,    78,    80,
       0,     0,     0,     0,     0,     0,     0,     0,   123,   130,
     133,     0,   145,   147,     0,     0,     0,     0,    97,     0,
       0,     0,   116,    18,     0,     0,    63,     0,     0,     0,
       0,    18,   124,   137,     0,     0,     0,     0,     0,   115,
      18,     0,     0,     0,     0,   149,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    90,    91,     0,     0,
       0,     0,     0,     0,     0,     0,   110,   111,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   112
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     1,   303,   142,   379,   223,   298,   191,   299,   188,
     189,     2,     4,   117
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -214
static const short int yypact[] =
{
    -214,     3,     9,  -214,   545,  -214,   -62,   -84,  -214,  -214,
    -214,   -55,   -50,   -99,   -95,   -36,   -30,   -15,   -14,   -12,
     -11,    -9,   -17,    -7,    -5,    -4,    -1,     1,     2,   -94,
       4,     6,  -214,  -214,   -93,   -89,   -88,    10,    11,   -43,
      12,    13,    15,    16,     8,    18,    19,   -87,   -83,   -82,
      21,    22,    23,  -214,    24,  -214,     5,    26,    25,    27,
      29,    30,   -78,    34,    37,    38,    39,  -214,  -214,    41,
      42,    45,    45,    45,   -51,    44,    46,    47,    45,   -77,
     -76,   -72,   -71,   -67,   -66,   -65,    49,    50,    42,    51,
      52,    54,    55,  -214,    56,  -214,    57,   -94,  -214,    59,
      60,    61,    62,    63,    64,    65,  -214,    66,  -214,  -214,
      67,  -214,    68,  -214,    69,  -106,  -214,  -214,    76,  -214,
      77,  -214,    78,    79,    80,    81,    42,    82,    83,    84,
      85,  -214,    86,    87,    88,    42,    89,    91,    42,    42,
     -49,  -214,    92,    58,  -214,  -214,    42,    93,    94,    95,
      96,    97,    98,   -23,   -21,    99,   100,    42,    42,    42,
      42,  -214,  -214,  -214,   101,   102,   103,   104,   105,   107,
     108,  -214,  -214,  -214,   109,   110,  -214,   111,   112,   113,
     114,   115,    42,    42,  -214,  -214,    42,  -104,  -214,    42,
     -45,    42,    45,    45,   116,   117,    42,   118,   119,    45,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,    45,    42,  -214,    45,    58,   -35,
    -214,  -214,  -214,  -214,  -214,   137,   138,   139,   141,   143,
     145,    42,   146,    42,    42,  -214,  -214,  -214,  -214,   147,
     148,   149,   150,   151,  -214,  -214,   152,   154,  -214,  -214,
     155,  -214,  -214,   156,   158,  -214,  -214,  -214,   -33,  -214,
    -214,  -214,   159,   160,   161,   162,   163,   166,  -100,    42,
    -214,    42,    42,  -214,  -214,  -214,  -214,  -214,  -214,   167,
     168,   169,   170,   171,   172,  -214,   173,   174,   175,   176,
     177,   178,   179,  -214,  -214,  -214,   -56,  -214,  -214,  -214,
    -214,  -214,  -214,   -32,  -214,    42,    45,   180,   -28,  -214,
     182,    58,    58,   183,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   195,   196,   197,   198,   200,  -214,    45,
     -35,   201,   204,   205,    42,   209,   210,   211,    42,  -214,
      42,  -214,  -214,  -214,   203,   212,   213,   214,   215,  -214,
    -214,   216,    42,  -214,   217,  -214,   218,  -214,   219,   220,
     -59,  -214,  -214,  -214,  -214,   221,   222,   223,   224,   225,
     226,   227,   228,  -214,   229,  -214,   230,   231,  -214,   -18,
    -214,  -214,  -214,    42,   232,   233,   234,   235,   236,    58,
     237,   238,   239,    42,   240,   241,   243,   244,   245,   246,
     247,    42,   249,   250,    42,   -25,    42,   251,   254,  -214,
     255,   257,   256,  -214,  -214,   258,  -214,   259,  -214,   260,
     261,  -214,    20,    28,   262,   263,   264,   265,   266,   267,
     268,  -214,   269,   270,  -214,   271,   272,  -214,  -214,  -214,
     273,   274,  -214,   277,   278,    58,   279,    42,    48,  -214,
     280,    42,   281,   282,   283,    42,    53,  -214,   284,   285,
    -214,    45,  -214,  -214,   286,   288,   289,   290,   292,   184,
     294,   293,  -214,  -214,  -214,   295,   296,   297,   299,   300,
     302,   307,   306,   309,   310,   311,   312,   313,    42,   314,
      45,   317,  -214,    42,   318,  -214,   319,   320,   323,  -214,
      42,   322,    42,    45,   324,   325,   326,    42,   308,  -214,
    -214,  -214,   327,   328,   330,  -214,   332,  -214,  -214,   333,
     335,   336,   337,   338,   339,  -214,   340,    58,    42,  -214,
      42,   341,   342,    42,  -214,   345,  -214,    58,   344,   346,
     347,  -214,   349,   350,   351,   354,   355,   356,   357,   358,
    -214,   360,   363,    58,    58,  -214,  -214,   366,    42,  -214,
      42,    42,   367,    42,    42,   368,   369,  -214,  -214,  -214,
     370,   371,   374,   373,   375,   376,    58,   379,  -214,  -214,
    -214,   378,  -214,  -214,   380,   383,   382,   384,  -214,   385,
     386,   387,  -214,    42,   390,   389,  -214,   391,   392,   393,
     395,    42,  -214,  -214,   396,   397,   398,   399,   400,  -214,
      42,   401,   403,   404,   405,  -214,   408,   409,   410,   412,
     413,   414,   415,   416,   417,   418,   419,   420,   421,   422,
     423,   424,   427,   428,   429,   529,  -214,  -214,   541,   542,
     -24,   546,   543,   547,   548,   549,  -214,  -214,   550,   551,
     552,   553,   554,   555,   556,   557,   558,   559,   560,   561,
     562,   563,   566,   565,  -214
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -214,  -214,  -214,  -139,  -214,   -29,   -27,   -68,  -213,   -81,
    -214,  -214,  -214,  -214
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const short int yytable[] =
{
     143,   258,   144,     3,   192,   193,   332,   216,   236,    -2,
     199,   296,   237,   297,   141,   296,   122,   360,   141,   123,
     124,   140,   147,   125,   141,   148,   149,   151,   164,   150,
     152,   165,   166,   168,   119,   167,   169,   180,   200,   202,
     181,   201,   203,   204,   206,   244,   205,   207,   208,   210,
     212,   209,   211,   213,   252,   118,   296,   255,   256,   141,
     257,   378,   141,   120,   194,   261,   195,   257,   121,   141,
     224,   301,   270,   302,   155,   156,   275,   276,   277,   278,
     331,   126,   297,   353,   380,   259,   381,   385,   127,   386,
     331,   642,   360,   643,   268,   269,   271,   272,   437,   438,
     133,   293,   294,   128,   129,   295,   130,   131,   300,   132,
     304,   134,   135,   136,   260,   309,   137,   406,   138,   139,
     174,     0,   145,   146,   305,   306,   161,   153,   154,   157,
     158,   312,   159,   160,   328,   162,   473,   163,   170,   171,
     172,   175,   173,   176,   474,   177,   327,   178,   179,   329,
     339,   182,   341,   342,   183,   184,   185,   258,   186,   187,
     190,   196,     0,   197,   493,   198,   214,   215,   217,   500,
     218,   219,   220,   140,   221,   222,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   361,   362,   330,
     363,   364,   461,   238,     0,   239,   240,   241,   242,   243,
     245,   246,   247,   248,   249,   250,   251,   253,   254,     0,
     259,   262,   263,   264,   265,   266,   267,   273,   274,   279,
     280,   281,   282,   283,   382,   284,   285,   286,   287,   288,
     289,   290,   291,   292,   307,   308,   310,   311,   383,   313,
     314,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,   326,   409,   333,   334,   335,   413,   336,   414,
     337,   405,   338,   340,     0,   343,   344,   345,   346,   347,
     348,   421,   349,   350,   351,   352,     0,   354,   355,   356,
     357,   358,   388,   389,   359,   365,   366,   367,   368,   369,
     370,   371,   372,   373,   374,   375,   376,   377,   384,   387,
     509,   390,   439,   391,   392,   393,   394,   395,   396,   397,
     398,   399,   449,   400,   401,   402,   403,   404,   378,   407,
     457,   415,   408,   460,   462,   463,   410,   411,   412,     0,
     416,   417,   418,   419,   420,   422,   423,   424,   425,   426,
     427,   428,   429,   430,   431,   432,   433,   434,   435,   436,
     440,   441,   442,   443,   444,   446,   447,   448,   450,   451,
     445,   452,   453,   454,   455,   456,   492,   458,   459,   464,
     495,   465,   466,   468,   499,   467,   469,   470,   471,   472,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   503,   488,     0,   489,   491,   494,   496,
     497,   498,   501,   502,   504,   505,   506,   525,   507,   508,
     510,   511,   529,   512,   513,   514,   490,   515,   516,   534,
     517,   536,   527,   518,   519,   542,   541,   520,   521,   522,
     523,   524,   526,   528,   530,   537,     0,   531,   532,   533,
     535,     0,   538,   539,   540,   543,   544,   555,   545,   556,
     546,   547,   559,   548,   549,   550,   551,   552,   553,   557,
     558,   560,   562,     0,   563,   564,   565,     0,   566,   567,
     568,   569,     0,     0,   570,   571,   572,   578,   573,   579,
     580,   574,   582,   583,   577,   581,   584,   585,   586,   587,
     588,   589,     0,   590,   591,   593,   594,   595,   554,   596,
     597,     0,   598,   599,   600,   601,   603,   604,   561,   605,
     606,   607,   602,   608,   610,   611,   612,   613,   614,   616,
     609,   617,   618,   619,   575,   576,   620,   621,   622,   615,
     623,   624,   625,   626,   627,   628,   629,   630,   631,   632,
     633,   634,   635,   636,   637,   638,     5,   592,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   639,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   640,
     641,   645,   644,     0,   116,   646,   647,   648,   649,   650,
     651,   652,   653,   654,   655,   656,   657,   658,   659,   660,
     661,   662,   663,   664
};

static const short int yycheck[] =
{
      29,   140,    29,     0,    72,    73,   219,    88,   114,     0,
      78,   115,   118,   117,   118,   115,   115,   117,   118,   118,
     115,   115,   115,   118,   118,   118,   115,   115,   115,   118,
     118,   118,   115,   115,   118,   118,   118,   115,   115,   115,
     118,   118,   118,   115,   115,   126,   118,   118,   115,   115,
     115,   118,   118,   118,   135,   117,   115,   138,   139,   118,
     116,   117,   118,   118,   115,   146,   117,   116,   118,   118,
      97,   116,   153,   118,   117,   118,   157,   158,   159,   160,
     115,   117,   117,   116,   116,   118,   118,   115,   118,   117,
     115,   115,   117,   117,   117,   118,   117,   118,   116,   117,
     117,   182,   183,   118,   118,   186,   118,   118,   189,   118,
     191,   118,   117,   117,   143,   196,   117,   330,   117,   117,
     115,    -1,   118,   117,   192,   193,   118,   117,   117,   117,
     117,   199,   117,   117,   215,   117,   116,   118,   117,   117,
     117,   115,   118,   118,   116,   118,   214,   118,   118,   217,
     231,   117,   233,   234,   117,   117,   117,   296,   117,   117,
     115,   117,    -1,   117,   116,   118,   117,   117,   117,   116,
     118,   117,   117,   115,   118,   118,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   268,   269,   218,
     271,   272,   405,   117,    -1,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   117,    -1,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   305,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   306,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   334,   117,   117,   117,   338,   117,   340,
     117,   329,   117,   117,    -1,   118,   118,   118,   118,   118,
     118,   352,   118,   118,   118,   117,    -1,   118,   118,   118,
     118,   118,   311,   312,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   117,
     116,   118,   383,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   393,   118,   118,   118,   118,   117,   117,   115,
     401,   118,   117,   404,   405,   406,   117,   117,   117,    -1,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     389,   118,   118,   118,   118,   118,   447,   118,   118,   118,
     451,   117,   117,   117,   455,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   461,   117,    -1,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   117,   117,   488,   118,   117,
     116,   118,   493,   118,   118,   118,   445,   118,   118,   500,
     118,   502,   490,   116,   118,   117,   507,   118,   118,   118,
     118,   118,   118,   116,   116,   503,    -1,   118,   118,   116,
     118,    -1,   118,   118,   118,   118,   118,   528,   118,   530,
     118,   118,   533,   118,   118,   118,   118,   118,   118,   118,
     118,   116,   118,    -1,   118,   118,   117,    -1,   118,   118,
     116,   116,    -1,    -1,   118,   118,   118,   558,   118,   560,
     561,   118,   563,   564,   118,   118,   118,   118,   118,   118,
     116,   118,    -1,   118,   118,   116,   118,   117,   527,   116,
     118,    -1,   118,   118,   118,   118,   116,   118,   537,   118,
     118,   118,   593,   118,   118,   118,   118,   118,   118,   118,
     601,   118,   118,   118,   553,   554,   118,   118,   118,   610,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   116,   116,   116,     1,   576,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   118,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   118,
     118,   118,   116,    -1,   119,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   116,   118
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,   121,   131,     0,   132,     1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   119,   133,   117,   118,
     118,   118,   115,   118,   115,   118,   117,   118,   118,   118,
     118,   118,   118,   117,   118,   117,   117,   117,   117,   117,
     115,   118,   123,   125,   126,   118,   117,   115,   118,   115,
     118,   115,   118,   117,   117,   117,   118,   117,   117,   117,
     117,   118,   117,   118,   115,   118,   115,   118,   115,   118,
     117,   117,   117,   118,   115,   115,   118,   118,   118,   118,
     115,   118,   117,   117,   117,   117,   117,   117,   129,   130,
     115,   127,   127,   127,   115,   117,   117,   117,   118,   127,
     115,   118,   115,   118,   115,   118,   115,   118,   115,   118,
     115,   118,   115,   118,   117,   117,   129,   117,   118,   117,
     117,   118,   118,   125,   126,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   114,   118,   117,   118,
     118,   118,   118,   118,   129,   118,   118,   118,   118,   118,
     118,   118,   129,   118,   117,   129,   129,   116,   123,   118,
     125,   129,   118,   118,   118,   118,   118,   118,   117,   118,
     129,   117,   118,   118,   118,   129,   129,   129,   129,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   129,   129,   129,   115,   117,   126,   128,
     129,   116,   118,   122,   129,   127,   127,   118,   118,   129,
     118,   118,   127,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   127,   129,   127,
     125,   115,   128,   117,   117,   117,   117,   117,   117,   129,
     117,   129,   129,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   117,   116,   118,   118,   118,   118,   118,   118,
     117,   129,   129,   129,   129,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   117,   124,
     116,   118,   129,   127,   118,   115,   117,   117,   125,   125,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   117,   127,   128,   115,   117,   129,
     117,   117,   117,   129,   129,   118,   118,   118,   118,   118,
     118,   129,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   116,   117,   129,
     118,   118,   118,   118,   118,   125,   118,   118,   118,   129,
     118,   118,   118,   118,   118,   118,   118,   129,   118,   118,
     129,   128,   129,   129,   118,   117,   117,   118,   117,   118,
     118,   118,   118,   116,   116,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   117,   118,
     125,   118,   129,   116,   118,   129,   118,   118,   118,   129,
     116,   118,   118,   127,   118,   117,   117,   118,   117,   116,
     116,   118,   118,   118,   118,   118,   118,   118,   116,   118,
     118,   118,   118,   118,   118,   129,   118,   127,   116,   129,
     116,   118,   118,   116,   129,   118,   129,   127,   118,   118,
     118,   129,   117,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   125,   129,   129,   118,   118,   129,
     116,   125,   118,   118,   118,   117,   118,   118,   116,   116,
     118,   118,   118,   118,   118,   125,   125,   118,   129,   129,
     129,   118,   129,   129,   118,   118,   118,   118,   116,   118,
     118,   118,   125,   116,   118,   117,   116,   118,   118,   118,
     118,   118,   129,   116,   118,   118,   118,   118,   118,   129,
     118,   118,   118,   118,   118,   129,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   116,   116,   116,   118,
     118,   118,   115,   117,   116,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   116,   118
};

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
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
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
      yysymprint (stderr,					\
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
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname[yyr1[yyrule]]);
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
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
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
  const char *yys = yystr;

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
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      size_t yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

#endif /* YYERROR_VERBOSE */



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
    ;
#endif
#endif
{
  /* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;

  int yystate;
  int yyn;
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
  short int *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



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
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short int *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
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
#line 626 "rib.y"
    {
					intArgs.push((int) (yyvsp[0].real));
					(yyval.integer)	=	(yyvsp[-1].integer)	+	1;
				;}
    break;

  case 4:
#line 632 "rib.y"
    {
					intArgs.push((int) (yyvsp[0].real));
					(yyval.integer)	=	1;
				;}
    break;

  case 5:
#line 641 "rib.y"
    {
					floatArgs.push((yyvsp[0].real));
					(yyval.integer)	=	(yyvsp[-1].integer)	+	1;
				;}
    break;

  case 6:
#line 647 "rib.y"
    {
					floatArgs.push((yyvsp[0].real));
					(yyval.integer)	=	1;
				;}
    break;

  case 7:
#line 655 "rib.y"
    {
					stringArgs.push((yyvsp[0].string));
					(yyval.integer)	=	(yyvsp[-1].integer)	+	1;
				;}
    break;

  case 8:
#line 661 "rib.y"
    {
					stringArgs.push((yyvsp[0].string));
					(yyval.integer)	=	1;
				;}
    break;

  case 9:
#line 670 "rib.y"
    {
					(yyval.integer) = (yyvsp[-1].integer);
				;}
    break;

  case 10:
#line 676 "rib.y"
    {
					(yyval.integer) = 0;
				;}
    break;

  case 11:
#line 683 "rib.y"
    {
					(yyval.integer)	=	(yyvsp[0].integer);
				;}
    break;

  case 12:
#line 688 "rib.y"
    {
					(yyval.integer)	=	(yyvsp[0].integer);
				;}
    break;

  case 13:
#line 696 "rib.y"
    {
					(yyval.integer) = (yyvsp[-1].integer);
				;}
    break;

  case 14:
#line 702 "rib.y"
    {
					(yyval.integer) = 0;
				;}
    break;

  case 15:
#line 711 "rib.y"
    {
					(yyval.integer)	=	(yyvsp[-1].integer);
				;}
    break;

  case 16:
#line 716 "rib.y"
    {
					stringArgs.push((yyvsp[0].string));
					(yyval.integer)	= 1;
				;}
    break;

  case 17:
#line 726 "rib.y"
    {
				;}
    break;

  case 18:
#line 729 "rib.y"
    {
					int	i;

					assert(numParameters < maxParameter);

					// Fix the pointers
					for (i=0;i<numParameters;i++) {
						tokens[i]				=	parameters[i].name;

						if (parameters[i].type == RT_TEXT)
							vals[i]				=	(RtPointer) (stringArgs.array + parameters[i].valuesStart);
						else
							vals[i]				=	(RtPointer) (floatArgs.array + parameters[i].valuesStart);

					}
				;}
    break;

  case 19:
#line 749 "rib.y"
    {
					// A parameter is either a float array
					parameters[numParameters].name			=	(yyvsp[-1].string);
					parameters[numParameters].type			=	RT_FLOAT;
					parameters[numParameters].numItems		=	(yyvsp[0].integer);
					parameters[numParameters].valuesStart	=	floatArgs.numItems-(yyvsp[0].integer);
					numParameters++;
					paramCheck();
				;}
    break;

  case 20:
#line 761 "rib.y"
    {	
					// Or a string array
					parameters[numParameters].name			=	(yyvsp[-1].string);
					parameters[numParameters].type			=	RT_TEXT;
					parameters[numParameters].numItems		=	(yyvsp[0].integer);
					parameters[numParameters].valuesStart	=	stringArgs.numItems-(yyvsp[0].integer);
					numParameters++;
					paramCheck();
				;}
    break;

  case 21:
#line 773 "rib.y"
    {
					// Save the line number in case we have an error
					ribCommandLineno		=	ribLineno;
					
					// Reset the number of parameters
					floatArgs.numItems		=	0;
					intArgs.numItems		=	0;
					stringArgs.numItems		=	0;
					numParameters			=	0;
					
					// Restore the memory
					memRestore(memoryCheckpoint,CRenderer::globalMemory);
				;}
    break;

  case 22:
#line 787 "rib.y"
    {	
				;}
    break;

  case 24:
#line 794 "rib.y"
    {
					if (callback != NULL) {
						callback((yyvsp[0].string));
					}
				;}
    break;

  case 25:
#line 803 "rib.y"
    {
					RiDeclare((yyvsp[-1].string),(yyvsp[0].string));
				;}
    break;

  case 26:
#line 808 "rib.y"
    {
					RiFrameBegin(0);
				;}
    break;

  case 27:
#line 814 "rib.y"
    {
					RiFrameBegin((int) (yyvsp[0].real));
				;}
    break;

  case 28:
#line 819 "rib.y"
    {
					RiFrameEnd();
				;}
    break;

  case 29:
#line 824 "rib.y"
    {
					// Save the checkpoint
					worldCheckpoint		=	memoryCheckpoint;
					
					// Call the worldbegin
					RiWorldBegin();
					
					// Create a new checkpoint because we allocate some stuff in RiWorldBegin
					memSave(memoryCheckpoint,CRenderer::globalMemory);
					
				;}
    break;

  case 30:
#line 837 "rib.y"
    {
					RiWorldEnd();
					
					// Restore the checkpoint to that before the world begin
					memoryCheckpoint	=	worldCheckpoint;
				;}
    break;

  case 31:
#line 848 "rib.y"
    {
					RiFormat((int) (yyvsp[-2].real),(int) (yyvsp[-1].real),(yyvsp[0].real));
				;}
    break;

  case 32:
#line 854 "rib.y"
    {
					RiFrameAspectRatio((yyvsp[0].real));
				;}
    break;

  case 33:
#line 863 "rib.y"
    {
					RiScreenWindow((yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real),(yyvsp[0].real));
				;}
    break;

  case 34:
#line 874 "rib.y"
    {
					RiScreenWindow((yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real));
				;}
    break;

  case 35:
#line 883 "rib.y"
    {
					RiCropWindow((yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real),(yyvsp[0].real));
				;}
    break;

  case 36:
#line 894 "rib.y"
    {
					RiCropWindow((yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real));
				;}
    break;

  case 37:
#line 901 "rib.y"
    {
					RiProjectionV((yyvsp[-1].string),numParameters,tokens,vals);
				;}
    break;

  case 38:
#line 908 "rib.y"
    {
					RiClipping((yyvsp[-1].real),(yyvsp[0].real));
				;}
    break;

  case 39:
#line 919 "rib.y"
    {
					RiClippingPlane((yyvsp[-5].real),(yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real),(yyvsp[0].real));
				;}
    break;

  case 40:
#line 927 "rib.y"
    {
					RiDepthOfField((yyvsp[-2].real),(yyvsp[-1].real),(yyvsp[0].real));
				;}
    break;

  case 41:
#line 932 "rib.y"
    {
					RiDepthOfField(C_INFINITY,1,1);
				;}
    break;

  case 42:
#line 939 "rib.y"
    {
					RiShutter((yyvsp[-1].real),(yyvsp[0].real));
				;}
    break;

  case 43:
#line 945 "rib.y"
    {
					RiPixelVariance((yyvsp[0].real));
				;}
    break;

  case 44:
#line 952 "rib.y"
    {
					RiPixelSamples((yyvsp[-1].real),(yyvsp[0].real));
				;}
    break;

  case 45:
#line 960 "rib.y"
    {
					RtFilterFunc	f;

					if ((f = getFilter((yyvsp[-2].string))) != NULL) {
						RiPixelFilter(f,(yyvsp[-1].real),(yyvsp[0].real));
					}
				;}
    break;

  case 46:
#line 971 "rib.y"
    {
					RiExposure((yyvsp[-1].real),(yyvsp[0].real));
				;}
    break;

  case 47:
#line 978 "rib.y"
    {
					// No parameter list checking is performed for the shaders
					if (parameterListCheck()) {
						RiImagerV((yyvsp[-1].string),numParameters,tokens,vals);
					}
				;}
    break;

  case 48:
#line 991 "rib.y"
    {
					RiQuantize((yyvsp[-4].string),(int) (yyvsp[-3].real),(int) (yyvsp[-2].real),(int) (yyvsp[-1].real),(yyvsp[0].real));
				;}
    break;

  case 49:
#line 1000 "rib.y"
    {
					RiDisplayV((yyvsp[-3].string),(yyvsp[-2].string),(yyvsp[-1].string),numParameters,tokens,vals);
				;}
    break;

  case 50:
#line 1007 "rib.y"
    {
					RiDisplayChannelV((yyvsp[-1].string),numParameters,tokens,vals);
				;}
    break;

  case 51:
#line 1014 "rib.y"
    {
					if (parameterListCheck()) {
						RiHiderV((yyvsp[-1].string),numParameters,tokens,vals);
					}
				;}
    break;

  case 52:
#line 1022 "rib.y"
    {
					if ((floatArgs.numItems & 1) || ((floatArgs.numItems % 6) != 0)) {
						error(CODE_MISSINGDATA,"ColorSamples: Invalid number of arguments (\"%d\") \n",floatArgs.numItems);
					} else {
						int		n		=	floatArgs.numItems/6;
						float	*argf1	=	getFloat(0);
						float	*argf2	=	getFloat(n*3);

						RiColorSamples(n,argf1,argf2);
					}
				;}
    break;

  case 53:
#line 1037 "rib.y"
    {
					if (((yyvsp[-1].integer) != (yyvsp[0].integer)) || ((floatArgs.numItems % 6) != 0)) {
						error(CODE_MISSINGDATA,"ColorSamples: Invalid number of arguments (\"%d\") \n",floatArgs.numItems);
					} else {
						int		n		=	floatArgs.numItems/6;
						float	*argf1	=	getFloat(0);
						float	*argf2	=	getFloat(n*3);

						RiColorSamples(n,argf1,argf2);
					}
				;}
    break;

  case 54:
#line 1051 "rib.y"
    {
					RiRelativeDetail((yyvsp[0].real));	
				;}
    break;

  case 55:
#line 1058 "rib.y"
    {
					if (parameterListCheck()) {
						RiOptionV((yyvsp[-1].string),numParameters,tokens,vals);
					}
				;}
    break;

  case 56:
#line 1065 "rib.y"
    {
					RiAttributeBegin();
				;}
    break;

  case 57:
#line 1070 "rib.y"
    {
					RiAttributeEnd();
				;}
    break;

  case 58:
#line 1078 "rib.y"
    {
					RtColor	color;

					color[0]	=	(yyvsp[-2].real);
					color[1]	=	(yyvsp[-1].real);
					color[2]	=	(yyvsp[0].real);

					RiColor(color);
				;}
    break;

  case 59:
#line 1092 "rib.y"
    {
					RtColor	color;

					color[0]	=	(yyvsp[-2].real);
					color[1]	=	(yyvsp[-1].real);
					color[2]	=	(yyvsp[0].real);

					RiOpacity(color);
				;}
    break;

  case 60:
#line 1108 "rib.y"
    {
					RtColor	color;

					color[0]	=	(yyvsp[-3].real);
					color[1]	=	(yyvsp[-2].real);
					color[2]	=	(yyvsp[-1].real);

					RiColor(color);
				;}
    break;

  case 61:
#line 1124 "rib.y"
    {
					RtColor	color;

					color[0]	=	(yyvsp[-3].real);
					color[1]	=	(yyvsp[-2].real);
					color[2]	=	(yyvsp[-1].real);

					RiOpacity(color);
				;}
    break;

  case 62:
#line 1143 "rib.y"
    {
					RiTextureCoordinates((yyvsp[-7].real),(yyvsp[-6].real),(yyvsp[-5].real),(yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real),(yyvsp[0].real));
				;}
    break;

  case 63:
#line 1158 "rib.y"
    {
					RiTextureCoordinates((yyvsp[-8].real),(yyvsp[-7].real),(yyvsp[-6].real),(yyvsp[-5].real),(yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real));
				;}
    break;

  case 64:
#line 1166 "rib.y"
    {
					TLight	*nLight	=	new TLight;
					nLight->index	=	(int) (yyvsp[-1].real);
					nLight->name	=	NULL;
					nLight->handle	=	RiLightSourceV((yyvsp[-2].string),numParameters,tokens,vals);					
					nLight->next	=	lights;
					lights			=	nLight;
				;}
    break;

  case 65:
#line 1179 "rib.y"
    {
					TLight	*nLight	=	new TLight;
					nLight->index	=	0;
					nLight->name	=	strdup((yyvsp[-1].string));
					nLight->handle	=	RiLightSourceV((yyvsp[-2].string),numParameters,tokens,vals);					
					nLight->next	=	lights;
					lights			=	nLight;
				;}
    break;

  case 66:
#line 1191 "rib.y"
    {
					RiLightSourceV((yyvsp[-1].string),numParameters,tokens,vals);
				;}
    break;

  case 67:
#line 1199 "rib.y"
    {
					TLight	*nLight	=	new TLight;
					nLight->index	=	(int) (yyvsp[-1].real);
					nLight->name	=	NULL;
					nLight->handle	=	RiAreaLightSourceV((yyvsp[-2].string),numParameters,tokens,vals);					
					nLight->next	=	lights;
					lights			=	nLight;
				;}
    break;

  case 68:
#line 1212 "rib.y"
    {
					TLight	*nLight	=	new TLight;
					nLight->index	=	0;
					nLight->name	=	strdup((yyvsp[-1].string));
					nLight->handle	=	RiAreaLightSourceV((yyvsp[-2].string),numParameters,tokens,vals);					
					nLight->next	=	lights;
					lights			=	nLight;
				;}
    break;

  case 69:
#line 1224 "rib.y"
    {
					TLight	*cLight;
					
					for (cLight=lights;cLight!=NULL;cLight=cLight->next)
						if (cLight->index == (int) (yyvsp[-1].real))	break;
						
					if (cLight != NULL) {
						RiIlluminate(cLight->handle,(int) (yyvsp[0].real));
					} else {
						error(CODE_RANGE,"The light %d is not found",(int) (yyvsp[-1].real));
					}
				;}
    break;

  case 70:
#line 1240 "rib.y"
    {
					TLight	*cLight;
					
					for (cLight=lights;cLight!=NULL;cLight=cLight->next)
						if (cLight->name != NULL) {
							if (strcmp(cLight->name,(yyvsp[-1].string)) == 0) break;
						}
						
					if (cLight != NULL) {
						RiIlluminate(cLight->handle,(int) (yyvsp[0].real));
					} else {
						error(CODE_RANGE,"The light \"%s\" is not found",(yyvsp[-1].string));
					}
				;}
    break;

  case 71:
#line 1258 "rib.y"
    {
					RiSurfaceV((yyvsp[-1].string),numParameters,tokens,vals);
				;}
    break;

  case 72:
#line 1265 "rib.y"
    {
					RiAtmosphereV((yyvsp[-1].string),numParameters,tokens,vals);
				;}
    break;

  case 73:
#line 1272 "rib.y"
    {
					RiInteriorV((yyvsp[-1].string),numParameters,tokens,vals);
				;}
    break;

  case 74:
#line 1279 "rib.y"
    {
					RiExteriorV((yyvsp[-1].string),numParameters,tokens,vals);
				;}
    break;

  case 75:
#line 1285 "rib.y"
    {
					RiShadingRate((yyvsp[0].real));
				;}
    break;

  case 76:
#line 1291 "rib.y"
    {
					RiShadingInterpolation((yyvsp[0].string));
				;}
    break;

  case 77:
#line 1297 "rib.y"
    {
					RiMatte((RtBoolean) (yyvsp[0].real));
				;}
    break;

  case 78:
#line 1310 "rib.y"
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

  case 79:
#line 1330 "rib.y"
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

  case 80:
#line 1352 "rib.y"
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

  case 81:
#line 1372 "rib.y"
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

  case 82:
#line 1390 "rib.y"
    {
					RiDetailRange((yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real),(yyvsp[0].real));
				;}
    break;

  case 83:
#line 1401 "rib.y"
    {
					RiDetailRange((yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real));
				;}
    break;

  case 84:
#line 1408 "rib.y"
    {
					RiGeometricApproximation((yyvsp[-1].string),(yyvsp[0].real));
				;}
    break;

  case 85:
#line 1414 "rib.y"
    {
					RiGeometricRepresentation((yyvsp[0].string));
				;}
    break;

  case 86:
#line 1420 "rib.y"
    {
					RiOrientation((yyvsp[0].string));
				;}
    break;

  case 87:
#line 1425 "rib.y"
    {
					RiReverseOrientation();
				;}
    break;

  case 88:
#line 1431 "rib.y"
    {
					RiSides((int) (yyvsp[0].real));
				;}
    break;

  case 89:
#line 1436 "rib.y"
    {
					RiIdentity();
				;}
    break;

  case 90:
#line 1459 "rib.y"
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

  case 91:
#line 1501 "rib.y"
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

  case 92:
#line 1526 "rib.y"
    {
					RiPerspective((yyvsp[0].real));
				;}
    break;

  case 93:
#line 1534 "rib.y"
    {
					RiTranslate((yyvsp[-2].real),(yyvsp[-1].real),(yyvsp[0].real));
				;}
    break;

  case 94:
#line 1542 "rib.y"
    {
					RiScale((yyvsp[-2].real),(yyvsp[-1].real),(yyvsp[0].real));
				;}
    break;

  case 95:
#line 1551 "rib.y"
    {
					RiRotate((yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real),(yyvsp[0].real));
				;}
    break;

  case 96:
#line 1563 "rib.y"
    {
					RiSkew((yyvsp[-6].real),(yyvsp[-5].real),(yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real),(yyvsp[0].real));
				;}
    break;

  case 97:
#line 1577 "rib.y"
    {
					RiSkew((yyvsp[-7].real),(yyvsp[-6].real),(yyvsp[-5].real),(yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real));
				;}
    break;

  case 98:
#line 1584 "rib.y"
    {
					RiDeformationV((yyvsp[-1].string),numParameters,tokens,vals);
				;}
    break;

  case 99:
#line 1591 "rib.y"
    {
					RiDisplacementV((yyvsp[-1].string),numParameters,tokens,vals);
				;}
    break;

  case 100:
#line 1597 "rib.y"
    {
					RiCoordinateSystem((yyvsp[0].string));
				;}
    break;

  case 101:
#line 1603 "rib.y"
    {
					RiCoordSysTransform((yyvsp[0].string));
				;}
    break;

  case 102:
#line 1608 "rib.y"
    {
					RiTransformBegin();
				;}
    break;

  case 103:
#line 1613 "rib.y"
    {
					RiTransformEnd();
				;}
    break;

  case 104:
#line 1620 "rib.y"
    {
					if (parameterListCheck()) {
						RiAttributeV((yyvsp[-1].string),numParameters,tokens,vals);
					}
				;}
    break;

  case 105:
#line 1628 "rib.y"
    {
					if (parameterListCheck()) {	
						if (sizeCheck(numVertex,0,0,1)) {
							RiPolygonV(numVertex,numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 106:
#line 1639 "rib.y"
    {
					int		*argi	=	getInt(0);

					if (parameterListCheck()) {
						if (sizeCheck(numVertex,0,0,1)) {
							RiGeneralPolygonV((yyvsp[-1].integer),argi,numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 107:
#line 1653 "rib.y"
    {
					int	*argi1		=	getInt(0);
					int	*argi2		=	getInt((yyvsp[-2].integer));
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

  case 108:
#line 1690 "rib.y"
    {
					int	*argi1		=	getInt(0);
					int	*argi2		=	getInt((yyvsp[-3].integer));
					int	*argi3		=	getInt((yyvsp[-2].integer)+(yyvsp[-3].integer));
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

  case 109:
#line 1734 "rib.y"
    {
					RtBasis	*argf1,*argf2;

					if ((getBasis(&argf1,(yyvsp[-3].string))) && (getBasis(&argf2,(yyvsp[-1].string)))) {
						RiBasis(argf1[0],(int) (yyvsp[-2].real), argf2[0],(int) (yyvsp[0].real));
					}
				;}
    break;

  case 110:
#line 1764 "rib.y"
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

  case 111:
#line 1813 "rib.y"
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

  case 112:
#line 1879 "rib.y"
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

  case 113:
#line 1922 "rib.y"
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

  case 114:
#line 1952 "rib.y"
    {
					int	numExpectedVertices;
					int	numuPatches,numvPatches;
					int	nu	=	(int) (yyvsp[-4].real);
					int	nv	=	(int) (yyvsp[-2].real);
					CAttributes	*attributes	=	CRenderer::context->getAttributes(FALSE);
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

  case 115:
#line 2033 "rib.y"
    {
					float	*argf1	=	getFloat(0);
					float	*argf2	=	getFloat((yyvsp[-8].integer));

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

  case 116:
#line 2064 "rib.y"
    {
					int		*argi1	=	getInt(0);
					int		*argi2	=	getInt((yyvsp[-8].integer));
					float	*argf3	=	getFloat(0);
					float	*argf4	=	getFloat((yyvsp[-6].integer));
					float	*argf5	=	getFloat((yyvsp[-5].integer)+(yyvsp[-6].integer));
					int		*argi6	=	getInt((yyvsp[-7].integer)+(yyvsp[-8].integer));
					float	*argf7	=	getFloat((yyvsp[-4].integer)+(yyvsp[-5].integer)+(yyvsp[-6].integer));
					float	*argf8	=	getFloat((yyvsp[-2].integer)+(yyvsp[-4].integer)+(yyvsp[-5].integer)+(yyvsp[-6].integer));
					float	*argf9	=	getFloat((yyvsp[-1].integer)+(yyvsp[-2].integer)+(yyvsp[-4].integer)+(yyvsp[-5].integer)+(yyvsp[-6].integer));

					RiTrimCurve((yyvsp[-8].integer),argi1,argi2,argf3,argf4,argf5,argi6,argf7,argf8,argf9);
				;}
    break;

  case 117:
#line 2084 "rib.y"
    {
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiSphereV((yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real),numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 118:
#line 2100 "rib.y"
    {
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiSphereV((yyvsp[-5].real),(yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 119:
#line 2113 "rib.y"
    {
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiConeV((yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real),numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 120:
#line 2128 "rib.y"
    {
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiConeV((yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 121:
#line 2142 "rib.y"
    {
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiCylinderV((yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real),numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 122:
#line 2158 "rib.y"
    {
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiCylinderV((yyvsp[-5].real),(yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 123:
#line 2175 "rib.y"
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

  case 124:
#line 2203 "rib.y"
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

  case 125:
#line 2226 "rib.y"
    {
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiParaboloidV((yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real),numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 126:
#line 2242 "rib.y"
    {
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiParaboloidV((yyvsp[-5].real),(yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 127:
#line 2255 "rib.y"
    {
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiDiskV((yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real),numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 128:
#line 2270 "rib.y"
    {
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiDiskV((yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 129:
#line 2285 "rib.y"
    {
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiTorusV((yyvsp[-5].real),(yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),(yyvsp[-1].real),numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 130:
#line 2302 "rib.y"
    {
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiTorusV((yyvsp[-6].real),(yyvsp[-5].real),(yyvsp[-4].real),(yyvsp[-3].real),(yyvsp[-2].real),numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 131:
#line 2315 "rib.y"
    {
					int			*argi1		=	getInt(0);
					int			numVertices,numUniforms;
					CAttributes	*attributes	=	CRenderer::context->getAttributes(FALSE);
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

  case 132:
#line 2358 "rib.y"
    {
					if (parameterListCheck()) {
						if (sizeCheck(numVertex,0,0,1)) {
							RiPointsV(numVertex,numParameters,tokens,vals);
						}
					}
				;}
    break;

  case 133:
#line 2375 "rib.y"
    {
					int		*argi1,*argi2,*argi3,*argi4;
					char	**args1;
					float	*argf1;
					int		numVertices,i,j;

					if (parameterListCheck()) {
						argi1	=	getInt(0);
						argi2	=	getInt((yyvsp[-6].integer));
						args1	=	getString(0);
						argi3	=	getInt((yyvsp[-6].integer)+(yyvsp[-5].integer));
						argi4	=	getInt((yyvsp[-6].integer)+(yyvsp[-5].integer)+(yyvsp[-3].integer));
						argf1	=	getFloat(0);

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

  case 134:
#line 2409 "rib.y"
    {
					int		*argi1,*argi2;
					int		numVertices,i,j;

					if (parameterListCheck()) {
						argi1	=	getInt(0);
						argi2	=	getInt((yyvsp[-2].integer));

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

  case 135:
#line 2437 "rib.y"
    {
					// FIXME: Not implemented
				;}
    break;

  case 136:
#line 2444 "rib.y"
    {
					if (parameterListCheck()) {
						RiGeometryV((yyvsp[-1].string),numParameters,tokens,vals);
					}
				;}
    break;

  case 137:
#line 2461 "rib.y"
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
							arg		=	getString(0);

							cData->generator	=	strdup(arg[0]);

							RiProcedural((RtPointer) cData,bound,RiProcDelayedReadArchive,RiProcFree);
						}
					} else if (strcmp((yyvsp[-9].string),RI_PROCRUNPROGRAM) == 0) {
						if ((yyvsp[-8].integer) != 2) {
							error(CODE_MISSINGDATA,"Proc delayed archive expects two arguments (given %d)\n",(yyvsp[-8].integer));
						} else {
							arg		=	getString(0);

							cData->generator	=	strdup(arg[0]);
							cData->helper		=	strdup(arg[1]);

							RiProcedural((RtPointer) cData,bound,RiProcRunProgram,RiProcFree);
						}
					} else if (strcmp((yyvsp[-9].string),RI_PROCDYNAMICLOAD) == 0) {
						if ((yyvsp[-8].integer) != 2) {
							error(CODE_MISSINGDATA,"Proc delayed archive expects two arguments (given %d)\n",(yyvsp[-8].integer));
						} else {
							arg		=	getString(0);

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

  case 138:
#line 2521 "rib.y"
    {
					RiSolidBegin((yyvsp[0].string));
				;}
    break;

  case 139:
#line 2526 "rib.y"
    {
					RiSolidEnd();
				;}
    break;

  case 140:
#line 2532 "rib.y"
    {
					TObject	*nObject	=	new TObject;
					
					nObject->handle	=	RiObjectBegin();
					nObject->index	=	(int) (yyvsp[0].real);
					nObject->next	=	objects;
					objects			=	nObject;
				;}
    break;

  case 141:
#line 2542 "rib.y"
    {
					RiObjectEnd();
				;}
    break;

  case 142:
#line 2548 "rib.y"
    {
					TObject	*cObject;
					
					for (cObject=objects;cObject!=NULL;cObject=cObject->next) {
						if (cObject->index == (int) (yyvsp[0].real))	break;
					}
					
					if (cObject != NULL) {
						RiObjectInstance(cObject->handle);
					} else {
						error(CODE_MISSINGDATA,"Object %d is not found\n",(int) (yyvsp[0].real));
					}
				;}
    break;

  case 143:
#line 2564 "rib.y"
    {
					float	*argf	=	getFloat(0);

					RiMotionBeginV((yyvsp[0].integer),argf);
				;}
    break;

  case 144:
#line 2571 "rib.y"
    {
					RiMotionEnd();
				;}
    break;

  case 145:
#line 2584 "rib.y"
    {
					RtFilterFunc	f;

					if ((f		=	getFilter((yyvsp[-3].string))) != NULL)  {
						RiMakeTextureV((yyvsp[-7].string),(yyvsp[-6].string),(yyvsp[-5].string),(yyvsp[-4].string),f,(yyvsp[-2].real),(yyvsp[-1].real),numParameters,tokens,vals);
					}
				;}
    break;

  case 146:
#line 2596 "rib.y"
    {
					RiMakeTexture3DV((yyvsp[-2].string),(yyvsp[-1].string),numParameters,tokens,vals);
				;}
    break;

  case 147:
#line 2609 "rib.y"
    {
					RtFilterFunc	f;

					if ((f		=	getFilter((yyvsp[-3].string))) != NULL) {
						RiMakeBumpV((yyvsp[-7].string),(yyvsp[-6].string),(yyvsp[-5].string),(yyvsp[-4].string),f,(yyvsp[-2].real),(yyvsp[-1].real),numParameters,tokens,vals);
					}
				;}
    break;

  case 148:
#line 2624 "rib.y"
    {
					RtFilterFunc	f;

					if ((f		=	getFilter((yyvsp[-3].string))) != NULL) {
						RiMakeLatLongEnvironmentV((yyvsp[-5].string),(yyvsp[-4].string),f,(yyvsp[-2].real),(yyvsp[-1].real),numParameters,tokens,vals);
					}
				;}
    break;

  case 149:
#line 2645 "rib.y"
    {
					RtFilterFunc	f;

					if ((f =	getFilter((yyvsp[-3].string))) != NULL) {
						RiMakeCubeFaceEnvironmentV((yyvsp[-11].string),(yyvsp[-10].string),(yyvsp[-9].string),(yyvsp[-8].string),(yyvsp[-7].string),(yyvsp[-6].string),(yyvsp[-5].string),(yyvsp[-4].real),f,(yyvsp[-2].real),(yyvsp[-1].real),numParameters,tokens,vals);
					}
				;}
    break;

  case 150:
#line 2657 "rib.y"
    {
					RiMakeShadowV((yyvsp[-2].string),(yyvsp[-1].string),numParameters,tokens,vals);
				;}
    break;

  case 151:
#line 2664 "rib.y"
    {
					RiArchiveBeginV((yyvsp[-1].string),numParameters,tokens,vals);
				;}
    break;

  case 152:
#line 2669 "rib.y"
    {
					RiArchiveEnd();
				;}
    break;

  case 153:
#line 2674 "rib.y"
    {
					RiResourceBegin();
				;}
    break;

  case 154:
#line 2679 "rib.y"
    {
					RiResourceEnd();
				;}
    break;

  case 155:
#line 2687 "rib.y"
    {
					RiResourceV((yyvsp[-2].string),(yyvsp[-1].string),numParameters,tokens,vals);
				;}
    break;

  case 156:
#line 2694 "rib.y"
    {
					RiIfBeginV((yyvsp[-1].string),numParameters,tokens,vals);
				;}
    break;

  case 157:
#line 2699 "rib.y"
    {
					RiIfEnd();
				;}
    break;

  case 158:
#line 2706 "rib.y"
    {
					RiElseIfV((yyvsp[-1].string),numParameters,tokens,vals);
				;}
    break;

  case 159:
#line 2711 "rib.y"
    {
					RiElse();
				;}
    break;

  case 160:
#line 2717 "rib.y"
    {
					RtErrorHandler 	e	=	getErrorHandler((yyvsp[0].string));

					if (e != NULL) {
						RiErrorHandler(e);
					}
				;}
    break;

  case 161:
#line 2727 "rib.y"
    {
				;}
    break;

  case 162:
#line 2732 "rib.y"
    {
				;}
    break;

  case 163:
#line 2736 "rib.y"
    {
					if (YYRECOVERING() == 0) {
						error(CODE_BADFILE,"Syntax error.\n");
					}
				;}
    break;


      default: break;
    }

/* Line 1126 of yacc.c.  */
#line 4219 "rib.cpp"

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
	  int yytype = YYTRANSLATE (yychar);
	  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
	  YYSIZE_T yysize = yysize0;
	  YYSIZE_T yysize1;
	  int yysize_overflow = 0;
	  char *yymsg = 0;
#	  define YYERROR_VERBOSE_ARGS_MAXIMUM 5
	  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
	  int yyx;

#if 0
	  /* This is so xgettext sees the translatable formats that are
	     constructed on the fly.  */
	  YY_("syntax error, unexpected %s");
	  YY_("syntax error, unexpected %s, expecting %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s or %s");
	  YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
#endif
	  char *yyfmt;
	  char const *yyf;
	  static char const yyunexpected[] = "syntax error, unexpected %s";
	  static char const yyexpecting[] = ", expecting %s";
	  static char const yyor[] = " or %s";
	  char yyformat[sizeof yyunexpected
			+ sizeof yyexpecting - 1
			+ ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
			   * (sizeof yyor - 1))];
	  char const *yyprefix = yyexpecting;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 1;

	  yyarg[0] = yytname[yytype];
	  yyfmt = yystpcpy (yyformat, yyunexpected);

	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
		  {
		    yycount = 1;
		    yysize = yysize0;
		    yyformat[sizeof yyunexpected - 1] = '\0';
		    break;
		  }
		yyarg[yycount++] = yytname[yyx];
		yysize1 = yysize + yytnamerr (0, yytname[yyx]);
		yysize_overflow |= yysize1 < yysize;
		yysize = yysize1;
		yyfmt = yystpcpy (yyfmt, yyprefix);
		yyprefix = yyor;
	      }

	  yyf = YY_(yyformat);
	  yysize1 = yysize + yystrlen (yyf);
	  yysize_overflow |= yysize1 < yysize;
	  yysize = yysize1;

	  if (!yysize_overflow && yysize <= YYSTACK_ALLOC_MAXIMUM)
	    yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg)
	    {
	      /* Avoid sprintf, as that infringes on the user's name space.
		 Don't have undefined behavior even if the translation
		 produced a string with the wrong number of "%s"s.  */
	      char *yyp = yymsg;
	      int yyi = 0;
	      while ((*yyp = *yyf))
		{
		  if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		    {
		      yyp += yytnamerr (yyp, yyarg[yyi++]);
		      yyf += 2;
		    }
		  else
		    {
		      yyp++;
		      yyf++;
		    }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    {
	      yyerror (YY_("syntax error"));
	      goto yyexhaustedlab;
	    }
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror (YY_("syntax error"));
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (0)
     goto yyerrorlab;

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
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK;
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 2743 "rib.y"


#include "lex.rib.cpp"

// Our position in the rib file
static	int		ribStart	=	0;
static	int		ribStep		=	5*(1<<10);	// Parse 5 KB at a time

///////////////////////////////////////////////////////////////////////
// Function				:	riberror
// Description			:	Parser error file
// Return Value			:	-
// Comments				:
void	riberror(char *s,...) {
	warning(CODE_BADFILE,"RIB Parse error\n");
}

///////////////////////////////////////////////////////////////////////
// Function				:	ribParse
// Description			:	Parse a rib file
// Return Value			:	-
// Comments				:
void	ribParse(const char *fileName,void (*c)(const char *)) {


	if (fileName != NULL) {
		

		// Save the environment first
		TLight				*savedLights					=	lights;
		TObject				*savedObjects					=	objects;
		int					savedRibLineno					=	ribLineno;
		void				(*savedCallback)(const char *)	=	callback;
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
	
		// Guard against the depreciated fdopen on windoze	
#ifdef WIN32
#define fdopen _fdopen
#endif
		
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
		objects				=	NULL;
		callback			=	c;
		maxParameter		=	20;
		numParameters		=	0;
		parameters			=	new TParameter[maxParameter];
		tokens				=	new RtToken[maxParameter];
		vals				=	new RtPointer[maxParameter];
		
		if ( ribDepth++ == 0) {
			// outhermost
		} else {
			// create a new lex buffer and switch to it
			
			// Note: there are two stacking methods here,
			//  one is explicitly handled when lexing for ReadArchive
			//	the other uses the return stack (and increments ribDepth)

			rib_switch_to_buffer(rib_create_buffer( ribin, YY_BUF_SIZE ) );	
			ribStack		=	NULL;	// prevent falling out of current ReadArchive
		}
		
		ribFile				=	fileName;
		ribLineno			=	1;

		// Put a checkpoint in the global memory
		// This checkpoint is restored after every RIB command
		memSave(memoryCheckpoint,CRenderer::globalMemory);

		// Parse the RIB
		ribparse();

		// Restore the memory to the latest checkpoint
		memRestore(memoryCheckpoint,CRenderer::globalMemory);
		
		if (ribin != NULL) {
#ifdef HAVE_ZLIB
			gzclose(ribin);
#else
			fclose(ribin);
#endif
		}

		// Clear the lights
		TLight	*cLight;
		while((cLight=lights) != NULL) {
			lights	=	lights->next;
			if (cLight->name != NULL)	free(cLight->name);
			delete cLight;
		}
		
		TObject	*cObject;
		while((cObject=objects) != NULL) {
			objects	=	objects->next;
			delete cObject;
		}
		
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
		lights				=	savedLights;
		objects				=	savedObjects;
		ribLineno			=	savedRibLineno;
		callback			=	savedCallback;
		
		if ((ribDepth = savedRibDepth) == 0) {
			// outhermost
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
void		parserCleanup() {
	rib_delete_buffer(YY_CURRENT_BUFFER);
	yy_init				= 1;
}



