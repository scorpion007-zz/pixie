
/*  A Bison parser, made from rib.y
    by GNU Bison version 1.28  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse ribparse
#define yylex riblex
#define yyerror riberror
#define yylval riblval
#define yychar ribchar
#define yydebug ribdebug
#define yynerrs ribnerrs
#define	RIB_DECLARE	257
#define	RIB_FRAME_BEGIN	258
#define	RIB_FRAME_END	259
#define	RIB_WORLD_BEGIN	260
#define	RIB_WORLD_END	261
#define	RIB_FORMAT	262
#define	RIB_FRAME_ASPECT_RATIO	263
#define	RIB_SCREEN_WINDOW	264
#define	RIB_CROP_WINDOW	265
#define	RIB_PROJECTION	266
#define	RIB_CLIPPING	267
#define	RIB_CLIPPING_PLANE	268
#define	RIB_DEPTH_OF_FIELD	269
#define	RIB_SHUTTER	270
#define	RIB_PIXEL_VARIANCE	271
#define	RIB_PIXEL_SAMPLES	272
#define	RIB_PIXEL_FILTER	273
#define	RIB_EXPOSURE	274
#define	RIB_IMAGER	275
#define	RIB_QUANTIZE	276
#define	RIB_DISPLAY	277
#define	RIB_DISPLAYCHANNEL	278
#define	RIB_HIDER	279
#define	RIB_COLOR_SAMPLES	280
#define	RIB_RELATIVE_DETAIL	281
#define	RIB_OPTION	282
#define	RIB_ATTRIBUTE_BEGIN	283
#define	RIB_ATTRIBUTE_END	284
#define	RIB_COLOR	285
#define	RIB_OPACITY	286
#define	RIB_TEXTURE_COORDINATES	287
#define	RIB_LIGHT_SOURCE	288
#define	RIB_AREA_LIGHT_SOURCE	289
#define	RIB_ILLUMINATE	290
#define	RIB_SURFACE	291
#define	RIB_ATMOSPHERE	292
#define	RIB_INTERIOR	293
#define	RIB_EXTERIOR	294
#define	RIB_SHADING_RATE	295
#define	RIB_SHADING_INTERPOLATION	296
#define	RIB_MATTE	297
#define	RIB_BOUND	298
#define	RIB_DETAIL	299
#define	RIB_DETAIL_RANGE	300
#define	RIB_GEOMETRIC_APPROXIMATION	301
#define	RIB_GEOMETRIC_REPRESENTATION	302
#define	RIB_ORIENTATION	303
#define	RIB_REVERSE_ORIENTATION	304
#define	RIB_SIDES	305
#define	RIB_IDENTITY	306
#define	RIB_TRANSFORM	307
#define	RIB_CONCAT_TRANSFORM	308
#define	RIB_PERSPECTIVE	309
#define	RIB_TRANSLATE	310
#define	RIB_ROTATE	311
#define	RIB_SCALE	312
#define	RIB_SKEW	313
#define	RIB_DEFORMATION	314
#define	RIB_DISPLACEMENT	315
#define	RIB_COORDINATE_SYSTEM	316
#define	RIB_COORDINATE_SYS_TRANSFORM	317
#define	RIB_TRANSFORM_BEGIN	318
#define	RIB_TRANSFORM_END	319
#define	RIB_ATTRIBUTE	320
#define	RIB_POLYGON	321
#define	RIB_GENERAL_POLYGON	322
#define	RIB_POINTS_POLYGONS	323
#define	RIB_POINTS_GENERAL_POLYGONS	324
#define	RIB_BASIS	325
#define	RIB_PATCH	326
#define	RIB_PATCH_MESH	327
#define	RIB_NU_PATCH	328
#define	RIB_TRIM_CURVE	329
#define	RIB_SPHERE	330
#define	RIB_CONE	331
#define	RIB_CYLINDER	332
#define	RIB_HYPERBOLOID	333
#define	RIB_PARABOLOID	334
#define	RIB_DISK	335
#define	RIB_TORUS	336
#define	RIB_CURVES	337
#define	RIB_GEOMETRY	338
#define	RIB_POINTS	339
#define	RIB_SUBDIVISION_MESH	340
#define	RIB_BLOBBY	341
#define	RIB_PROCEDURAL	342
#define	RIB_SOLID_BEGIN	343
#define	RIB_SOLID_END	344
#define	RIB_OBJECT_BEGIN	345
#define	RIB_OBJECT_END	346
#define	RIB_OBJECT_INSTANCE	347
#define	RIB_MOTION_BEGIN	348
#define	RIB_MOTION_END	349
#define	RIB_MAKE_TEXTURE	350
#define	RIB_MAKE_TEXTURE3D	351
#define	RIB_MAKE_BUMP	352
#define	RIB_MAKE_LAT_LONG_ENVIRONMENT	353
#define	RIB_MAKE_CUBE_FACE_ENVIRONMENT	354
#define	RIB_MAKE_SHADOW	355
#define	RIB_ARCHIVE_RECORD	356
#define	RIB_ERROR_HANDLER	357
#define	RIB_VERSION	358
#define	RIB_VERSION_STRING	359
#define	RIB_ARRAY_BEGIN	360
#define	RIB_ARRAY_END	361
#define	RIB_TEXT	362
#define	RIB_IDENTIFIER	363
#define	RIB_FLOAT	364
#define	RIB_STRUCTURE_COMMENT	365

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
#include "config.h"

#include <math.h>
#include <string.h>
#include <stdarg.h>


#ifdef HAVE_ZLIB
#include <zlib.h>
#endif


#line 58 "rib.y"
typedef union ribval {
	float	real;
	char	string[2048];
	int		integer;
} YYSTYPE;
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
static	CTrie<char *>		*lightNames					=	NULL;	// Name -> handle mapping for lights (we define it as char * to avoid the annoying gcc warning)
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


#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		647
#define	YYFLAG		-32768
#define	YYNTBASE	112

#define YYTRANSLATE(x) ((unsigned)(x) <= 365 ? yytranslate[x] : 125)

static const char yytranslate[] = {     0,
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
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     3,     4,     5,     6,
     7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
    17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
    27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
    37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
    47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
    57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
    67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
    77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
    87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
    97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
   107,   108,   109,   110,   111
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     5,     7,    10,    12,    15,    17,    21,    24,
    26,    28,    32,    35,    39,    41,    44,    45,    48,    51,
    52,    56,    57,    59,    63,    65,    68,    70,    72,    74,
    79,    82,    88,    96,   102,   110,   114,   118,   126,   131,
   133,   137,   140,   144,   149,   153,   157,   164,   170,   174,
   178,   181,   185,   188,   192,   194,   196,   201,   206,   213,
   220,   230,   242,   247,   252,   256,   261,   266,   270,   274,
   278,   282,   286,   290,   293,   296,   299,   309,   317,   327,
   335,   341,   349,   353,   356,   359,   361,   364,   366,   386,
   406,   409,   414,   419,   425,   434,   445,   449,   453,   456,
   459,   461,   463,   467,   470,   474,   479,   485,   491,   514,
   537,   577,   581,   589,   602,   613,   620,   629,   635,   643,
   650,   659,   669,   681,   688,   697,   703,   711,   719,   729,
   735,   738,   748,   754,   760,   764,   776,   779,   781,   784,
   786,   789,   792,   794,   804,   809,   819,   827,   841,   846,
   849,   852,   855
};

static const short yyrhs[] = {   122,
     0,   113,   110,     0,   110,     0,   114,   110,     0,   110,
     0,   115,   108,     0,   108,     0,   106,   114,   107,     0,
   106,   107,     0,   116,     0,   114,     0,   106,   113,   107,
     0,   106,   107,     0,   106,   115,   107,     0,   108,     0,
   121,   120,     0,     0,   108,   117,     0,   108,   119,     0,
     0,   122,   123,   124,     0,     0,   111,     0,     3,   108,
   108,     0,     4,     0,     4,   110,     0,     5,     0,     6,
     0,     7,     0,     8,   110,   110,   110,     0,     9,   110,
     0,    10,   110,   110,   110,   110,     0,    10,   106,   110,
   110,   110,   110,   107,     0,    11,   110,   110,   110,   110,
     0,    11,   106,   110,   110,   110,   110,   107,     0,    12,
   108,   120,     0,    13,   110,   110,     0,    14,   110,   110,
   110,   110,   110,   110,     0,    15,   110,   110,   110,     0,
    15,     0,    16,   110,   110,     0,    17,   110,     0,    18,
   110,   110,     0,    19,   108,   110,   110,     0,    20,   110,
   110,     0,    21,   108,   120,     0,    22,   108,   110,   110,
   110,   110,     0,    23,   108,   108,   108,   120,     0,    24,
   108,   120,     0,    25,   108,   120,     0,    26,   117,     0,
    26,   116,   116,     0,    27,   110,     0,    28,   108,   120,
     0,    29,     0,    30,     0,    31,   110,   110,   110,     0,
    32,   110,   110,   110,     0,    31,   106,   110,   110,   110,
   107,     0,    32,   106,   110,   110,   110,   107,     0,    33,
   110,   110,   110,   110,   110,   110,   110,   110,     0,    33,
   106,   110,   110,   110,   110,   110,   110,   110,   110,   107,
     0,    34,   108,   110,   120,     0,    34,   108,   108,   120,
     0,    34,   108,   120,     0,    35,   108,   110,   120,     0,
    35,   108,   108,   120,     0,    36,   110,   110,     0,    36,
   108,   110,     0,    37,   108,   120,     0,    38,   108,   120,
     0,    39,   108,   120,     0,    40,   108,   120,     0,    41,
   110,     0,    42,   108,     0,    43,   110,     0,    44,   106,
   110,   110,   110,   110,   110,   110,   107,     0,    44,   110,
   110,   110,   110,   110,   110,     0,    45,   106,   110,   110,
   110,   110,   110,   110,   107,     0,    45,   110,   110,   110,
   110,   110,   110,     0,    46,   110,   110,   110,   110,     0,
    46,   106,   110,   110,   110,   110,   107,     0,    47,   108,
   110,     0,    48,   108,     0,    49,   108,     0,    50,     0,
    51,   110,     0,    52,     0,    53,   106,   110,   110,   110,
   110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
   110,   110,   110,   107,     0,    54,   106,   110,   110,   110,
   110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
   110,   110,   110,   107,     0,    55,   110,     0,    56,   110,
   110,   110,     0,    58,   110,   110,   110,     0,    57,   110,
   110,   110,   110,     0,    59,   110,   110,   110,   110,   110,
   110,   110,     0,    59,   106,   110,   110,   110,   110,   110,
   110,   110,   107,     0,    60,   108,   120,     0,    61,   108,
   120,     0,    62,   108,     0,    63,   108,     0,    64,     0,
    65,     0,    66,   108,   120,     0,    67,   120,     0,    68,
   118,   120,     0,    69,   118,   118,   120,     0,    70,   118,
   118,   118,   120,     0,    71,   108,   110,   108,   110,     0,
    71,   106,   110,   110,   110,   110,   110,   110,   110,   110,
   110,   110,   110,   110,   110,   110,   110,   110,   107,   110,
   108,   110,     0,    71,   108,   110,   106,   110,   110,   110,
   110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
   110,   110,   110,   107,   110,     0,    71,   106,   110,   110,
   110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
   110,   110,   110,   110,   107,   110,   106,   110,   110,   110,
   110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
   110,   110,   110,   107,   110,     0,    72,   108,   120,     0,
    73,   108,   110,   108,   110,   108,   120,     0,    74,   110,
   110,   116,   110,   110,   110,   110,   116,   110,   110,   120,
     0,    75,   116,   116,   116,   116,   116,   116,   116,   116,
   116,     0,    76,   110,   110,   110,   110,   120,     0,    76,
   106,   110,   110,   110,   110,   107,   120,     0,    77,   110,
   110,   110,   120,     0,    77,   106,   110,   110,   110,   107,
   120,     0,    78,   110,   110,   110,   110,   120,     0,    78,
   106,   110,   110,   110,   110,   107,   120,     0,    79,   110,
   110,   110,   110,   110,   110,   110,   120,     0,    79,   106,
   110,   110,   110,   110,   110,   110,   110,   107,   120,     0,
    80,   110,   110,   110,   110,   120,     0,    80,   106,   110,
   110,   110,   110,   107,   120,     0,    81,   110,   110,   110,
   120,     0,    81,   106,   110,   110,   110,   107,   120,     0,
    82,   110,   110,   110,   110,   110,   120,     0,    82,   106,
   110,   110,   110,   110,   110,   107,   120,     0,    83,   108,
   118,   108,   120,     0,    85,   120,     0,    86,   108,   118,
   118,   119,   118,   118,   116,   120,     0,    86,   108,   118,
   118,   120,     0,    87,   110,   116,   119,   120,     0,    84,
   108,   120,     0,    88,   108,   119,   106,   110,   110,   110,
   110,   110,   110,   107,     0,    89,   108,     0,    90,     0,
    91,   110,     0,    92,     0,    93,   110,     0,    94,   117,
     0,    95,     0,    96,   108,   108,   108,   108,   108,   110,
   110,   120,     0,    97,   108,   108,   120,     0,    98,   108,
   108,   108,   108,   108,   110,   110,   120,     0,    99,   108,
   108,   108,   110,   110,   120,     0,   100,   108,   108,   108,
   108,   108,   108,   108,   110,   108,   110,   110,   120,     0,
   101,   108,   108,   120,     0,   103,   108,     0,   104,   110,
     0,   104,   105,     0,     1,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   612,   615,   622,   632,   639,   648,   657,   668,   674,   683,
   687,   694,   700,   709,   715,   728,   732,   752,   763,   777,
   783,   791,   795,   801,   808,   813,   819,   824,   829,   834,
   842,   848,   857,   868,   877,   888,   895,   902,   913,   921,
   926,   933,   939,   946,   958,   965,   975,   985,   994,  1001,
  1010,  1024,  1039,  1045,  1054,  1059,  1064,  1078,  1092,  1108,
  1124,  1137,  1152,  1162,  1174,  1181,  1191,  1203,  1212,  1225,
  1232,  1239,  1246,  1253,  1259,  1265,  1271,  1293,  1313,  1335,
  1355,  1364,  1375,  1382,  1388,  1394,  1399,  1405,  1410,  1452,
  1494,  1500,  1508,  1516,  1525,  1537,  1551,  1558,  1565,  1571,
  1577,  1582,  1587,  1596,  1606,  1619,  1655,  1699,  1712,  1761,
  1810,  1889,  1915,  1991,  2024,  2048,  2062,  2078,  2091,  2106,
  2120,  2136,  2162,  2190,  2204,  2220,  2233,  2248,  2263,  2280,
  2326,  2336,  2374,  2402,  2411,  2420,  2489,  2495,  2500,  2508,
  2513,  2523,  2531,  2536,  2553,  2561,  2578,  2593,  2614,  2622,
  2632,  2637,  2642
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","RIB_DECLARE",
"RIB_FRAME_BEGIN","RIB_FRAME_END","RIB_WORLD_BEGIN","RIB_WORLD_END","RIB_FORMAT",
"RIB_FRAME_ASPECT_RATIO","RIB_SCREEN_WINDOW","RIB_CROP_WINDOW","RIB_PROJECTION",
"RIB_CLIPPING","RIB_CLIPPING_PLANE","RIB_DEPTH_OF_FIELD","RIB_SHUTTER","RIB_PIXEL_VARIANCE",
"RIB_PIXEL_SAMPLES","RIB_PIXEL_FILTER","RIB_EXPOSURE","RIB_IMAGER","RIB_QUANTIZE",
"RIB_DISPLAY","RIB_DISPLAYCHANNEL","RIB_HIDER","RIB_COLOR_SAMPLES","RIB_RELATIVE_DETAIL",
"RIB_OPTION","RIB_ATTRIBUTE_BEGIN","RIB_ATTRIBUTE_END","RIB_COLOR","RIB_OPACITY",
"RIB_TEXTURE_COORDINATES","RIB_LIGHT_SOURCE","RIB_AREA_LIGHT_SOURCE","RIB_ILLUMINATE",
"RIB_SURFACE","RIB_ATMOSPHERE","RIB_INTERIOR","RIB_EXTERIOR","RIB_SHADING_RATE",
"RIB_SHADING_INTERPOLATION","RIB_MATTE","RIB_BOUND","RIB_DETAIL","RIB_DETAIL_RANGE",
"RIB_GEOMETRIC_APPROXIMATION","RIB_GEOMETRIC_REPRESENTATION","RIB_ORIENTATION",
"RIB_REVERSE_ORIENTATION","RIB_SIDES","RIB_IDENTITY","RIB_TRANSFORM","RIB_CONCAT_TRANSFORM",
"RIB_PERSPECTIVE","RIB_TRANSLATE","RIB_ROTATE","RIB_SCALE","RIB_SKEW","RIB_DEFORMATION",
"RIB_DISPLACEMENT","RIB_COORDINATE_SYSTEM","RIB_COORDINATE_SYS_TRANSFORM","RIB_TRANSFORM_BEGIN",
"RIB_TRANSFORM_END","RIB_ATTRIBUTE","RIB_POLYGON","RIB_GENERAL_POLYGON","RIB_POINTS_POLYGONS",
"RIB_POINTS_GENERAL_POLYGONS","RIB_BASIS","RIB_PATCH","RIB_PATCH_MESH","RIB_NU_PATCH",
"RIB_TRIM_CURVE","RIB_SPHERE","RIB_CONE","RIB_CYLINDER","RIB_HYPERBOLOID","RIB_PARABOLOID",
"RIB_DISK","RIB_TORUS","RIB_CURVES","RIB_GEOMETRY","RIB_POINTS","RIB_SUBDIVISION_MESH",
"RIB_BLOBBY","RIB_PROCEDURAL","RIB_SOLID_BEGIN","RIB_SOLID_END","RIB_OBJECT_BEGIN",
"RIB_OBJECT_END","RIB_OBJECT_INSTANCE","RIB_MOTION_BEGIN","RIB_MOTION_END","RIB_MAKE_TEXTURE",
"RIB_MAKE_TEXTURE3D","RIB_MAKE_BUMP","RIB_MAKE_LAT_LONG_ENVIRONMENT","RIB_MAKE_CUBE_FACE_ENVIRONMENT",
"RIB_MAKE_SHADOW","RIB_ARCHIVE_RECORD","RIB_ERROR_HANDLER","RIB_VERSION","RIB_VERSION_STRING",
"RIB_ARRAY_BEGIN","RIB_ARRAY_END","RIB_TEXT","RIB_IDENTIFIER","RIB_FLOAT","RIB_STRUCTURE_COMMENT",
"start","ribIntString","ribFloatString","ribTextString","ribFloatArray","ribFloats",
"ribIntArray","ribTextArray","ribPL","ribParameter","ribCommands","@1","ribComm", NULL
};
#endif

static const short yyr1[] = {     0,
   112,   113,   113,   114,   114,   115,   115,   116,   116,   117,
   117,   118,   118,   119,   119,   120,   120,   121,   121,   123,
   122,   122,   124,   124,   124,   124,   124,   124,   124,   124,
   124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
   124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
   124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
   124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
   124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
   124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
   124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
   124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
   124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
   124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
   124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
   124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
   124,   124,   124
};

static const short yyr2[] = {     0,
     1,     2,     1,     2,     1,     2,     1,     3,     2,     1,
     1,     3,     2,     3,     1,     2,     0,     2,     2,     0,
     3,     0,     1,     3,     1,     2,     1,     1,     1,     4,
     2,     5,     7,     5,     7,     3,     3,     7,     4,     1,
     3,     2,     3,     4,     3,     3,     6,     5,     3,     3,
     2,     3,     2,     3,     1,     1,     4,     4,     6,     6,
     9,    11,     4,     4,     3,     4,     4,     3,     3,     3,
     3,     3,     3,     2,     2,     2,     9,     7,     9,     7,
     5,     7,     3,     2,     2,     1,     2,     1,    19,    19,
     2,     4,     4,     5,     8,    10,     3,     3,     2,     2,
     1,     1,     3,     2,     3,     4,     5,     5,    22,    22,
    39,     3,     7,    12,    10,     6,     8,     5,     7,     6,
     8,     9,    11,     6,     8,     5,     7,     7,     9,     5,
     2,     9,     5,     5,     3,    11,     2,     1,     2,     1,
     2,     2,     1,     9,     4,     9,     7,    13,     4,     2,
     2,     2,     1
};

static const short yydefact[] = {    22,
    20,     0,   153,     0,    25,    27,    28,    29,     0,     0,
     0,     0,     0,     0,     0,    40,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,    55,
    56,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    86,     0,    88,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,   101,   102,     0,    17,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    17,     0,     0,     0,     0,
   138,     0,   140,     0,     0,   143,     0,     0,     0,     0,
     0,     0,     0,     0,    23,    21,     0,    26,     0,    31,
     0,     0,     0,     0,    17,     0,     0,     0,     0,    42,
     0,     0,     0,    17,     0,     0,    17,    17,     0,     5,
    11,    10,    51,    53,    17,     0,     0,     0,     0,     0,
     0,    17,     0,     0,     0,    17,    17,    17,    17,    74,
    75,    76,     0,     0,     0,     0,     0,     0,     0,    84,
    85,    87,     0,     0,    91,     0,     0,     0,     0,     0,
    17,    17,    99,   100,    17,     0,   104,    17,     0,    17,
     0,     0,     0,     0,    17,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,    17,   131,     0,     0,     0,   137,   139,
   141,    10,   142,     0,     0,     0,     0,     0,     0,   150,
   152,   151,    24,     0,     0,     0,     0,     0,    36,    37,
     0,     0,    41,    43,     0,    45,    46,     0,     0,    49,
    50,     9,     0,     4,    52,    54,     0,     0,     0,     0,
     0,     0,    17,    17,    65,    17,    17,    69,    68,    70,
    71,    72,    73,     0,     0,     0,     0,     0,     0,    83,
     0,     0,     0,     0,     0,     0,     0,    97,    98,   103,
     0,    15,    18,    19,    16,    13,     3,     0,   105,    17,
     0,     0,     0,   112,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,   135,     0,     0,     0,     0,     0,    17,     0,
     0,     0,    17,    30,     0,     0,     0,     0,     0,    39,
    44,     0,    17,     8,     0,    57,     0,    58,     0,     0,
    15,    64,    63,    67,    66,     0,     0,     0,     0,     0,
     0,     0,     0,    92,     0,    93,     0,     0,     7,     0,
    12,     2,   106,    17,     0,     0,     0,     0,     0,     0,
     0,     0,     0,    17,     0,     0,     0,     0,     0,     0,
     0,    17,     0,     0,    17,    17,    17,     0,     0,   145,
     0,     0,     0,   149,     0,    32,     0,    34,     0,     0,
    48,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    81,     0,     0,    94,     0,     0,    14,     6,   107,     0,
     0,   108,     0,     0,     0,     0,    17,     0,   118,     0,
    17,     0,     0,     0,    17,     0,   126,     0,     0,   130,
     0,   133,   134,     0,     0,     0,     0,     0,     0,     0,
     0,    47,    59,    60,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,    17,     0,     0,
     0,   116,    17,     0,   120,     0,     0,     0,   124,    17,
     0,    17,     0,     0,     0,     0,    17,     0,    33,    35,
    38,     0,     0,     0,    78,     0,    80,    82,     0,     0,
     0,     0,     0,     0,   113,     0,     0,    17,   119,    17,
     0,     0,    17,   127,     0,   128,     0,     0,     0,     0,
   147,     0,     0,     0,     0,     0,     0,     0,     0,    95,
     0,     0,     0,     0,   117,   121,     0,    17,   125,    17,
    17,     0,    17,    17,     0,     0,    61,    77,    79,     0,
     0,     0,     0,     0,     0,     0,     0,   122,   129,   132,
     0,   144,   146,     0,     0,     0,     0,    96,     0,     0,
     0,   115,    17,     0,     0,    62,     0,     0,     0,     0,
    17,   123,   136,     0,     0,     0,     0,     0,   114,    17,
     0,     0,     0,     0,   148,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    89,    90,     0,     0,     0,
     0,     0,     0,     0,     0,   109,   110,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,   111,     0,     0,     0
};

static const short yydefgoto[] = {   645,
   288,   131,   360,   212,   283,   180,   284,   177,   178,     1,
     2,   106
};

static const short yypact[] = {-32768,
    46,   527,-32768,   -55,   -50,-32768,-32768,-32768,   -44,   -39,
   -91,   -89,   -20,   -31,    -8,    -6,    -2,     0,     2,     1,
     5,     8,     9,    10,    12,    13,   -86,    14,    15,-32768,
-32768,   -84,   -83,   -81,    17,    18,  -100,    19,    20,    21,
    22,    23,    24,    26,   -78,   -75,   -73,    29,    31,    32,
-32768,    33,-32768,    16,    25,    34,    35,    36,    37,   -72,
    40,    41,    42,    43,-32768,-32768,    44,    45,    28,    28,
    28,   -24,    47,    48,    49,    52,   -70,   -65,   -62,   -59,
   -54,   -52,   -51,    54,    55,    45,    56,    50,    57,    58,
-32768,    60,-32768,    63,   -86,-32768,    59,    66,    67,    68,
    69,    70,    71,   -98,-32768,-32768,    73,-32768,    74,-32768,
    75,    76,    77,    78,    45,    79,    80,    81,    82,-32768,
    83,    84,    85,    45,    86,    89,    45,    45,   -35,-32768,
    88,    52,-32768,-32768,    45,    90,    91,    92,    93,    94,
    96,   -25,   -19,    97,    98,    45,    45,    45,    45,-32768,
-32768,-32768,    99,   100,   101,   102,   103,   104,   105,-32768,
-32768,-32768,   106,   107,-32768,   108,   109,   110,   111,   112,
    45,    45,-32768,-32768,    45,   -97,-32768,    45,   -34,    45,
    28,    28,   114,   115,    45,   116,   117,    52,   118,   119,
   120,   121,   122,   123,   125,   126,   127,   129,   130,   131,
   132,   133,    28,    45,-32768,    28,    52,   -14,-32768,-32768,
-32768,-32768,-32768,   136,   137,   139,   141,   142,   143,-32768,
-32768,-32768,-32768,   144,   145,   146,   147,   148,-32768,-32768,
   149,   150,-32768,-32768,   151,-32768,-32768,   152,   155,-32768,
-32768,-32768,   -30,-32768,-32768,-32768,   154,   156,   157,   158,
   161,   162,   -92,    45,-32768,    45,    45,-32768,-32768,-32768,
-32768,-32768,-32768,   163,   164,   165,   166,   167,   168,-32768,
   170,   171,   172,   173,   174,   175,   176,-32768,-32768,-32768,
   -40,-32768,-32768,-32768,-32768,-32768,-32768,   -29,-32768,    45,
    28,   177,   -10,-32768,   180,    52,    52,   181,   182,   183,
   184,   185,   186,   188,   189,   193,   194,   195,   196,   197,
   198,   201,-32768,    28,   -14,   202,   159,   203,    45,   204,
   205,   206,    45,-32768,   207,   208,   209,   210,   211,-32768,
-32768,   212,    45,-32768,   213,-32768,   214,-32768,   215,   216,
   -41,-32768,-32768,-32768,-32768,   217,   218,   219,   220,   221,
   222,   223,   224,-32768,   225,-32768,   226,   227,-32768,    -1,
-32768,-32768,-32768,    45,   228,   229,   230,   231,   234,    52,
   235,   237,   238,    45,   239,   241,   242,   243,   244,   245,
   246,    45,   247,   248,    45,    -9,    45,   249,   252,-32768,
   253,   254,   255,-32768,   256,-32768,   257,-32768,   258,   259,
-32768,   263,   264,   262,   265,   266,   267,   268,   269,   270,
-32768,   271,   272,-32768,   274,   275,-32768,-32768,-32768,   276,
   277,-32768,   281,   280,    52,   282,    45,   284,-32768,   283,
    45,   286,   289,   290,    45,   287,-32768,   291,   293,-32768,
    28,-32768,-32768,   294,   297,   298,   299,   300,   303,   304,
   302,-32768,-32768,-32768,   306,   307,   308,   309,   310,   311,
   315,   314,   316,   317,   319,   320,   321,    45,   322,    52,
   326,-32768,    45,   327,-32768,   325,   328,   329,-32768,    45,
   330,    45,    28,   331,   332,   334,    45,   305,-32768,-32768,
-32768,   335,   336,   337,-32768,   338,-32768,-32768,   339,   340,
   341,   342,   344,   347,-32768,   350,    52,    45,-32768,    45,
   351,   352,    45,-32768,   356,-32768,    52,   354,   355,   357,
-32768,   358,   359,   360,   361,   364,   362,   363,   365,-32768,
   366,   367,    52,    52,-32768,-32768,   368,    45,-32768,    45,
    45,   369,    45,    45,   371,   372,-32768,-32768,-32768,   373,
   374,   378,   376,   377,   379,    52,   384,-32768,-32768,-32768,
   382,-32768,-32768,   385,   387,   388,   389,-32768,   390,   391,
   392,-32768,    45,   396,   394,-32768,   398,   399,   400,   401,
    45,-32768,-32768,   402,   403,   404,   405,   406,-32768,    45,
   407,   408,   409,   410,-32768,   411,   412,   413,   414,   415,
   416,   417,   519,   522,   523,   524,   525,   526,   529,   530,
   531,   535,   536,   537,   538,-32768,-32768,   539,   540,    -5,
   544,   542,   543,   545,   546,-32768,-32768,   547,   548,   549,
   550,   551,   552,   553,   554,   555,   556,   557,   558,   559,
   560,   564,   562,-32768,   199,   437,-32768
};

static const short yypgoto[] = {-32768,
-32768,  -124,-32768,   -27,   -21,   -68,  -204,   -85,-32768,-32768,
-32768,-32768
};


#define	YYLAST		672


static const short yytable[] = {   132,
   205,   181,   182,   317,   243,   133,   221,   144,   281,   145,
   282,   222,   130,   281,   111,   341,   113,   130,   112,   129,
   114,   136,   138,   130,   140,   137,   139,   153,   141,   229,
   155,   154,   157,   169,   156,   189,   158,   170,   237,   190,
   191,   240,   241,   193,   192,    -1,   195,   194,   188,   246,
   196,   197,   107,   199,   201,   198,   255,   200,   202,   108,
   260,   261,   262,   263,   281,   109,   242,   359,   130,   130,
   110,   242,   286,   213,   130,   287,   334,   361,   116,   244,
   362,   183,   253,   184,   254,   278,   279,   115,   256,   280,
   257,   316,   285,   282,   289,   366,   316,   367,   341,   294,
   622,   117,   623,   118,   245,   417,   418,   119,   122,   120,
   387,   121,   290,   291,   123,   124,   125,   126,   313,   127,
   128,   163,   135,   134,   142,   143,   146,   147,   148,   149,
   164,   151,   150,   179,   312,   152,   159,   314,   160,   161,
     0,     0,   162,   165,   166,   167,   168,   171,   172,   173,
   174,   175,   176,     0,   185,   186,   243,   129,   187,   207,
   297,   203,   204,   206,   208,   209,   214,   342,   343,   210,
   344,   345,   211,   215,   216,   217,   218,   219,   220,   315,
   223,   441,     0,   224,   225,   226,   227,   228,   230,   231,
   232,   233,   234,   235,   236,   238,   239,   244,   646,   247,
   248,   249,   250,   251,   363,   252,   258,   259,   264,   265,
   266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
   276,   277,   364,   292,   293,   295,   296,   298,   299,   300,
   301,   302,   303,   390,   304,   305,   306,   394,   307,   308,
   309,   310,   311,   318,   319,   386,   320,   401,   321,   322,
   323,     0,     0,   324,   325,   326,   327,   328,   329,   330,
   331,   332,   333,   335,   388,   336,   337,   338,   369,   370,
   339,   340,   346,   347,   348,   349,   350,   351,   419,   352,
   353,   354,   355,   356,   357,   358,   365,   368,   429,     0,
   371,   372,   373,   374,   375,   376,   437,   377,   378,   440,
   442,   443,   379,   380,   381,   382,   383,   384,   385,   359,
   389,   391,   392,   393,     0,     0,   395,   396,   397,   398,
   399,   400,   402,   403,   404,   405,   406,   407,   408,   409,
   410,   411,   412,   413,   414,   415,   416,   420,   421,   422,
   423,   472,   425,   424,   426,   475,   427,   428,   430,   479,
   431,   432,   433,   434,   435,   436,   438,   439,   444,   445,
   446,     0,   448,   447,     0,   449,   450,   451,   452,   453,
   454,   455,   483,     0,   456,   457,   458,   459,   460,   461,
   462,   463,   505,   464,   465,   466,   467,   509,   468,   469,
   473,   471,   474,   480,   514,   476,   516,   470,   477,   478,
   481,   521,   482,   484,   485,   486,     0,   488,   487,   489,
   490,   491,   522,     0,   517,   492,   493,   494,   495,   496,
   497,   498,   535,   499,   536,   500,   501,   539,   502,   503,
   504,   506,   508,   510,   511,   513,   647,   512,     0,   515,
   518,   519,   507,   520,   523,   524,   525,   526,   527,   528,
   529,   530,   558,   531,   559,   560,   532,   562,   563,   533,
   537,   538,   540,   542,   543,   545,   544,   548,   546,   547,
   549,   550,   551,     0,   552,   553,   554,   557,   561,   534,
   564,   565,   566,   567,   568,   569,   570,   582,   571,   541,
   573,   574,   575,   576,     0,   589,     0,   577,   578,   579,
   580,   581,   583,   584,   595,   555,   556,   585,   586,   587,
   588,   590,   591,   592,   593,   594,   596,   597,   598,   599,
   600,   601,   602,   603,   604,   605,   606,     3,   572,     4,
     5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
    15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
    25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
    35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
    45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
    55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
    65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
    75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
    85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
    95,    96,    97,    98,    99,   100,   101,   102,   607,   103,
   104,   608,   609,   610,   611,   612,     0,   105,   613,   614,
   615,   616,   617,   618,     0,     0,     0,   619,   620,   621,
   624,   625,   626,     0,   627,   628,   629,   630,   631,   632,
   633,   634,   635,   636,   637,   638,   639,   640,   641,   642,
   643,   644
};

static const short yycheck[] = {    27,
    86,    70,    71,   208,   129,    27,   105,   108,   106,   110,
   108,   110,   110,   106,   106,   108,   106,   110,   110,   106,
   110,   106,   106,   110,   106,   110,   110,   106,   110,   115,
   106,   110,   106,   106,   110,   106,   110,   110,   124,   110,
   106,   127,   128,   106,   110,     0,   106,   110,    76,   135,
   110,   106,   108,   106,   106,   110,   142,   110,   110,   110,
   146,   147,   148,   149,   106,   110,   107,   108,   110,   110,
   110,   107,   107,    95,   110,   110,   107,   107,   110,   110,
   110,   106,   108,   108,   110,   171,   172,   108,   108,   175,
   110,   106,   178,   108,   180,   106,   106,   108,   108,   185,
   106,   110,   108,   110,   132,   107,   108,   110,   108,   110,
   315,   110,   181,   182,   110,   108,   108,   108,   204,   108,
   108,   106,   108,   110,   108,   108,   108,   108,   108,   108,
   106,   108,   110,   106,   203,   110,   108,   206,   108,   108,
    -1,    -1,   110,   110,   110,   110,   110,   108,   108,   108,
   108,   108,   108,    -1,   108,   108,   281,   106,   110,   110,
   188,   108,   108,   108,   108,   108,   108,   253,   254,   110,
   256,   257,   110,   108,   108,   108,   108,   108,   108,   207,
   108,   386,    -1,   110,   110,   110,   110,   110,   110,   110,
   110,   110,   110,   110,   110,   110,   108,   110,     0,   110,
   110,   110,   110,   110,   290,   110,   110,   110,   110,   110,
   110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
   110,   110,   291,   110,   110,   110,   110,   110,   110,   110,
   110,   110,   110,   319,   110,   110,   110,   323,   110,   110,
   110,   110,   110,   108,   108,   314,   108,   333,   108,   108,
   108,    -1,    -1,   110,   110,   110,   110,   110,   110,   110,
   110,   110,   108,   110,   106,   110,   110,   110,   296,   297,
   110,   110,   110,   110,   110,   110,   110,   110,   364,   110,
   110,   110,   110,   110,   110,   110,   110,   108,   374,    -1,
   110,   110,   110,   110,   110,   110,   382,   110,   110,   385,
   386,   387,   110,   110,   110,   110,   110,   110,   108,   108,
   108,   108,   108,   108,    -1,    -1,   110,   110,   110,   110,
   110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
   110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
   110,   427,   370,   110,   110,   431,   110,   110,   110,   435,
   110,   110,   110,   110,   110,   110,   110,   110,   110,   108,
   108,    -1,   108,   110,    -1,   110,   110,   110,   110,   107,
   107,   110,   441,    -1,   110,   110,   110,   110,   110,   110,
   110,   110,   468,   110,   110,   110,   110,   473,   108,   110,
   107,   110,   110,   107,   480,   110,   482,   425,   110,   110,
   110,   487,   110,   110,   108,   108,    -1,   108,   110,   107,
   107,   110,   108,    -1,   483,   110,   110,   110,   110,   110,
   110,   107,   508,   110,   510,   110,   110,   513,   110,   110,
   110,   110,   107,   107,   110,   107,     0,   110,    -1,   110,
   110,   110,   470,   110,   110,   110,   110,   110,   110,   110,
   110,   110,   538,   110,   540,   541,   110,   543,   544,   110,
   110,   110,   107,   110,   110,   108,   110,   107,   110,   110,
   107,   110,   110,    -1,   110,   110,   110,   110,   110,   507,
   110,   110,   110,   110,   107,   110,   110,   573,   110,   517,
   107,   110,   108,   107,    -1,   581,    -1,   110,   110,   110,
   110,   110,   107,   110,   590,   533,   534,   110,   110,   110,
   110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
   110,   110,   110,   110,   110,   110,   110,     1,   556,     3,
     4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
    14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
    24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
    34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
    44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
    54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
    64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
    74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
    84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
    94,    95,    96,    97,    98,    99,   100,   101,   110,   103,
   104,   110,   110,   110,   110,   110,    -1,   111,   110,   110,
   110,   107,   107,   107,    -1,    -1,    -1,   110,   110,   110,
   107,   110,   110,    -1,   110,   110,   110,   110,   110,   110,
   110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
   107,   110
};
#define YYPURE 1

/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison.simple"
/* This file comes from bison-1.28.  */

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

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

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

#ifndef YYSTACK_USE_ALLOCA
#ifdef alloca
#define YYSTACK_USE_ALLOCA
#else /* alloca not defined */
#ifdef __GNUC__
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi) || (defined (__sun) && defined (__i386))
#define YYSTACK_USE_ALLOCA
#include <alloca.h>
#else /* not sparc */
/* We think this test detects Watcom and Microsoft C.  */
/* This used to test MSDOS, but that is a bad idea
   since that symbol is in the user namespace.  */
#if (defined (_MSDOS) || defined (_MSDOS_)) && !defined (__TURBOC__)
#if 0 /* No need for malloc.h, which pollutes the namespace;
	 instead, just don't use alloca.  */
#include <malloc.h>
#endif
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
/* I don't know what this was needed for, but it pollutes the namespace.
   So I turned it off.   rms, 2 May 1997.  */
/* #include <malloc.h>  */
 #pragma alloca
#define YYSTACK_USE_ALLOCA
#else /* not MSDOS, or __TURBOC__, or _AIX */
#if 0
#ifdef __hpux /* haible@ilog.fr says this works for HPUX 9.05 and up,
		 and on HPUX 10.  Eventually we can turn this on.  */
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#endif /* __hpux */
#endif
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc */
#endif /* not GNU C */
#endif /* alloca not defined */
#endif /* YYSTACK_USE_ALLOCA not defined */

#ifdef YYSTACK_USE_ALLOCA
#define YYSTACK_ALLOC alloca
#else
#define YYSTACK_ALLOC malloc
#endif

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Define __yy_memcpy.  Note that the size argument
   should be passed with type unsigned int, because that is what the non-GCC
   definitions require.  With GCC, __builtin_memcpy takes an arg
   of type size_t, but it can handle unsigned int.  */

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     unsigned int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, unsigned int count)
{
  register char *t = to;
  register char *f = from;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 217 "/usr/share/bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
#ifdef YYPARSE_PARAM
int yyparse (void *);
#else
int yyparse (void);
#endif
#endif

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;
  int yyfree_stacks = 0;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  if (yyfree_stacks)
	    {
	      free (yyss);
	      free (yyvs);
#ifdef YYLSP_NEEDED
	      free (yyls);
#endif
	    }
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
#ifndef YYSTACK_USE_ALLOCA
      yyfree_stacks = 1;
#endif
      yyss = (short *) YYSTACK_ALLOC (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1,
		   size * (unsigned int) sizeof (*yyssp));
      yyvs = (YYSTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1,
		   size * (unsigned int) sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1,
		   size * (unsigned int) sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 2:
#line 617 "rib.y"
{
					args[numArguments++].integer				=	(int) yyvsp[0].real;
					argCheck();
					yyval.integer	=	yyvsp[-1].integer	+	1;
				;
    break;}
case 3:
#line 624 "rib.y"
{
					args[numArguments++].integer				=	(int) yyvsp[0].real;
					argCheck();
					yyval.integer	=	1;
				;
    break;}
case 4:
#line 634 "rib.y"
{
					args[numArguments++].real					=	yyvsp[0].real;
					argCheck();
					yyval.integer	=	yyvsp[-1].integer	+	1;
				;
    break;}
case 5:
#line 641 "rib.y"
{
					args[numArguments++].real					=	yyvsp[0].real;
					argCheck();
					yyval.integer	=	1;
				;
    break;}
case 6:
#line 650 "rib.y"
{
					char	*theString	=	strdup(yyvsp[0].string);
					args[numArguments++].string					=	theString;
					allocatedStrings->push(theString);
					argCheck();
					yyval.integer	=	yyvsp[-1].integer	+	1;
				;
    break;}
case 7:
#line 659 "rib.y"
{
					char	*theString	=	strdup(yyvsp[0].string);
					args[numArguments++].string					=	theString;
					allocatedStrings->push(theString);
					argCheck();
					yyval.integer	=	1;
				;
    break;}
case 8:
#line 671 "rib.y"
{
					yyval.integer = yyvsp[-1].integer;
				;
    break;}
case 9:
#line 677 "rib.y"
{
					yyval.integer = 0;
				;
    break;}
case 10:
#line 684 "rib.y"
{
					yyval.integer	=	yyvsp[0].integer;
				;
    break;}
case 11:
#line 689 "rib.y"
{
					yyval.integer	=	yyvsp[0].integer;
				;
    break;}
case 12:
#line 697 "rib.y"
{
					yyval.integer = yyvsp[-1].integer;
				;
    break;}
case 13:
#line 703 "rib.y"
{
					yyval.integer = 0;
				;
    break;}
case 14:
#line 712 "rib.y"
{
					yyval.integer	=	yyvsp[-1].integer;
				;
    break;}
case 15:
#line 717 "rib.y"
{
					char	*theString	=	strdup(yyvsp[0].string);
					args[numArguments++].string					=	theString;
					allocatedStrings->push(theString);
					argCheck();
					yyval.integer	= 1;
				;
    break;}
case 16:
#line 730 "rib.y"
{
				;
    break;}
case 17:
#line 733 "rib.y"
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
				;
    break;}
case 18:
#line 754 "rib.y"
{
					// A parameter is either a float array
					parameters[numParameters].name			=	yyvsp[-1].string;
					parameters[numParameters].type			=	RT_FLOAT;
					parameters[numParameters].numItems		=	yyvsp[0].integer;
					parameters[numParameters].valuesStart	=	numArguments-yyvsp[0].integer;
					numParameters++;
					paramCheck();
				;
    break;}
case 19:
#line 766 "rib.y"
{	
					// Or a string array
					parameters[numParameters].name			=	yyvsp[-1].string;
					parameters[numParameters].type			=	RT_TEXT;
					parameters[numParameters].numItems		=	yyvsp[0].integer;
					parameters[numParameters].valuesStart	=	numArguments-yyvsp[0].integer;
					numParameters++;
					paramCheck();
				;
    break;}
case 20:
#line 778 "rib.y"
{
					// Save the line number in case we have an error
					ribCommandLineno	=	ribLineno;
				;
    break;}
case 21:
#line 783 "rib.y"
{
					char	*currentString;
					numArguments	=	0;
					numParameters	=	0;
					while((currentString=allocatedStrings->pop()) != NULL)
						free(currentString);

				;
    break;}
case 23:
#line 796 "rib.y"
{
					if (callback != NULL) {
						callback(yyvsp[0].string);
					}
				;
    break;}
case 24:
#line 805 "rib.y"
{
					RiDeclare(yyvsp[-1].string,yyvsp[0].string);
				;
    break;}
case 25:
#line 810 "rib.y"
{
					RiFrameBegin(0);
				;
    break;}
case 26:
#line 816 "rib.y"
{
					RiFrameBegin((int) yyvsp[0].real);
				;
    break;}
case 27:
#line 821 "rib.y"
{
					RiFrameEnd();
				;
    break;}
case 28:
#line 826 "rib.y"
{
					RiWorldBegin();
				;
    break;}
case 29:
#line 831 "rib.y"
{
					RiWorldEnd();
				;
    break;}
case 30:
#line 839 "rib.y"
{
					RiFormat((int) yyvsp[-2].real,(int) yyvsp[-1].real,yyvsp[0].real);
				;
    break;}
case 31:
#line 845 "rib.y"
{
					RiFrameAspectRatio(yyvsp[0].real);
				;
    break;}
case 32:
#line 854 "rib.y"
{
					RiScreenWindow(yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real,yyvsp[0].real);
				;
    break;}
case 33:
#line 865 "rib.y"
{
					RiScreenWindow(yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real);
				;
    break;}
case 34:
#line 874 "rib.y"
{
					RiCropWindow(yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real,yyvsp[0].real);
				;
    break;}
case 35:
#line 885 "rib.y"
{
					RiCropWindow(yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real);
				;
    break;}
case 36:
#line 892 "rib.y"
{
					RiProjectionV(yyvsp[-1].string,numParameters,tokens,vals);
				;
    break;}
case 37:
#line 899 "rib.y"
{
					RiClipping(yyvsp[-1].real,yyvsp[0].real);
				;
    break;}
case 38:
#line 910 "rib.y"
{
					RiClippingPlane(yyvsp[-5].real,yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real,yyvsp[0].real);
				;
    break;}
case 39:
#line 918 "rib.y"
{
					RiDepthOfField(yyvsp[-2].real,yyvsp[-1].real,yyvsp[0].real);
				;
    break;}
case 40:
#line 923 "rib.y"
{
					RiDepthOfField(C_INFINITY,1,1);
				;
    break;}
case 41:
#line 930 "rib.y"
{
					RiShutter(yyvsp[-1].real,yyvsp[0].real);
				;
    break;}
case 42:
#line 936 "rib.y"
{
					RiPixelVariance(yyvsp[0].real);
				;
    break;}
case 43:
#line 943 "rib.y"
{
					RiPixelSamples(yyvsp[-1].real,yyvsp[0].real);
				;
    break;}
case 44:
#line 951 "rib.y"
{
					RtFilterFunc	f;

					if ((f = getFilter(yyvsp[-2].string)) != NULL) {
						RiPixelFilter(f,yyvsp[-1].real,yyvsp[0].real);
					}
				;
    break;}
case 45:
#line 962 "rib.y"
{
					RiExposure(yyvsp[-1].real,yyvsp[0].real);
				;
    break;}
case 46:
#line 969 "rib.y"
{
					// No parameter list checking is performed for the shaders
					if (parameterListCheck()) {
						RiImagerV(yyvsp[-1].string,numParameters,tokens,vals);
					}
				;
    break;}
case 47:
#line 982 "rib.y"
{
					RiQuantize(yyvsp[-4].string,(int) yyvsp[-3].real,(int) yyvsp[-2].real,(int) yyvsp[-1].real,yyvsp[0].real);
				;
    break;}
case 48:
#line 991 "rib.y"
{
					RiDisplayV(yyvsp[-3].string,yyvsp[-2].string,yyvsp[-1].string,numParameters,tokens,vals);
				;
    break;}
case 49:
#line 998 "rib.y"
{
					RiDisplayChannelV(yyvsp[-1].string,numParameters,tokens,vals);
				;
    break;}
case 50:
#line 1005 "rib.y"
{
					if (parameterListCheck()) {
						RiHiderV(yyvsp[-1].string,numParameters,tokens,vals);
					}
				;
    break;}
case 51:
#line 1013 "rib.y"
{
					if ((numArguments & 1) || ((numArguments % 6) != 0)) {
						error(CODE_MISSINGDATA,"ColorSamples: Invalid number of arguments (\"%d\") \n",numArguments);
					} else {
						int		n		=	numArguments/6;
						float	*argf1	=	(float *) get(0);
						float	*argf2	=	(float *) get(n*3);

						RiColorSamples(n,argf1,argf2);
					}
				;
    break;}
case 52:
#line 1028 "rib.y"
{
					if ((yyvsp[-1].integer != yyvsp[0].integer) || ((numArguments % 6) != 0)) {
						error(CODE_MISSINGDATA,"ColorSamples: Invalid number of arguments (\"%d\") \n",numArguments);
					} else {
						int		n		=	numArguments/6;
						float	*argf1	=	(float *) get(0);
						float	*argf2	=	(float *) get(n*3);

						RiColorSamples(n,argf1,argf2);
					}
				;
    break;}
case 53:
#line 1042 "rib.y"
{
					RiRelativeDetail(yyvsp[0].real);	
				;
    break;}
case 54:
#line 1049 "rib.y"
{
					if (parameterListCheck()) {
						RiOptionV(yyvsp[-1].string,numParameters,tokens,vals);
					}
				;
    break;}
case 55:
#line 1056 "rib.y"
{
					RiAttributeBegin();
				;
    break;}
case 56:
#line 1061 "rib.y"
{
					RiAttributeEnd();
				;
    break;}
case 57:
#line 1069 "rib.y"
{
					RtColor	color;

					color[0]	=	yyvsp[-2].real;
					color[1]	=	yyvsp[-1].real;
					color[2]	=	yyvsp[0].real;

					RiColor(color);
				;
    break;}
case 58:
#line 1083 "rib.y"
{
					RtColor	color;

					color[0]	=	yyvsp[-2].real;
					color[1]	=	yyvsp[-1].real;
					color[2]	=	yyvsp[0].real;

					RiOpacity(color);
				;
    break;}
case 59:
#line 1099 "rib.y"
{
					RtColor	color;

					color[0]	=	yyvsp[-3].real;
					color[1]	=	yyvsp[-2].real;
					color[2]	=	yyvsp[-1].real;

					RiColor(color);
				;
    break;}
case 60:
#line 1115 "rib.y"
{
					RtColor	color;

					color[0]	=	yyvsp[-3].real;
					color[1]	=	yyvsp[-2].real;
					color[2]	=	yyvsp[-1].real;

					RiOpacity(color);
				;
    break;}
case 61:
#line 1134 "rib.y"
{
					RiTextureCoordinates(yyvsp[-7].real,yyvsp[-6].real,yyvsp[-5].real,yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real,yyvsp[0].real);
				;
    break;}
case 62:
#line 1149 "rib.y"
{
					RiTextureCoordinates(yyvsp[-8].real,yyvsp[-7].real,yyvsp[-6].real,yyvsp[-5].real,yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real);
				;
    break;}
case 63:
#line 1157 "rib.y"
{
					if (lights == NULL)	lights	=	new CArray<RtLightHandle>;

					(*lights)[(int) yyvsp[-1].real]	=	RiLightSourceV(yyvsp[-2].string,numParameters,tokens,vals);
				;
    break;}
case 64:
#line 1167 "rib.y"
{
					if (lightNames == NULL)	lightNames	=	new CTrie<char *>;
					
					char *lName = strdup(yyvsp[-1].string);
					permaStrings->push(lName);
					lightNames->insert(lName,(char *) RiLightSourceV(yyvsp[-2].string,numParameters,tokens,vals));
				;
    break;}
case 65:
#line 1178 "rib.y"
{
					RiLightSourceV(yyvsp[-1].string,numParameters,tokens,vals);
				;
    break;}
case 66:
#line 1186 "rib.y"
{
					if (lights == NULL)	lights	=	new CArray<RtLightHandle>;

					(*lights)[(int) yyvsp[-1].real]	=	RiAreaLightSourceV(yyvsp[-2].string,numParameters,tokens,vals);
				;
    break;}
case 67:
#line 1196 "rib.y"
{
					if (lightNames == NULL)	lightNames	=	new CTrie<char *>;
					
					char *lName = strdup(yyvsp[-1].string);
					permaStrings->push(lName);
					lightNames->insert(lName,(char *) RiLightSourceV(yyvsp[-2].string,numParameters,tokens,vals));
				;
    break;}
case 68:
#line 1207 "rib.y"
{
					if (lights == NULL)	lights	=	new CArray<RtLightHandle>;

					RiIlluminate((*lights)[(int) yyvsp[-1].real],(int) yyvsp[0].real);
				;
    break;}
case 69:
#line 1216 "rib.y"
{
					if (lightNames == NULL)	lightNames	=	new CTrie<char *>;
					
					char	*lightHandle = NULL;
					
					if(lightNames->find(yyvsp[-1].string,lightHandle)){
						RiIlluminate((RtPointer) lightHandle,(int) yyvsp[0].real);
					}
				;
    break;}
case 70:
#line 1229 "rib.y"
{
					RiSurfaceV(yyvsp[-1].string,numParameters,tokens,vals);
				;
    break;}
case 71:
#line 1236 "rib.y"
{
					RiAtmosphereV(yyvsp[-1].string,numParameters,tokens,vals);
				;
    break;}
case 72:
#line 1243 "rib.y"
{
					RiInteriorV(yyvsp[-1].string,numParameters,tokens,vals);
				;
    break;}
case 73:
#line 1250 "rib.y"
{
					RiExteriorV(yyvsp[-1].string,numParameters,tokens,vals);
				;
    break;}
case 74:
#line 1256 "rib.y"
{
					RiShadingRate(yyvsp[0].real);
				;
    break;}
case 75:
#line 1262 "rib.y"
{
					RiShadingInterpolation(yyvsp[0].string);
				;
    break;}
case 76:
#line 1268 "rib.y"
{
					RiMatte((RtBoolean) yyvsp[0].real);
				;
    break;}
case 77:
#line 1281 "rib.y"
{
					RtBound	bound;

					bound[0]	=	yyvsp[-6].real;
					bound[1]	=	yyvsp[-5].real;
					bound[2]	=	yyvsp[-4].real;
					bound[3]	=	yyvsp[-3].real;
					bound[4]	=	yyvsp[-2].real;
					bound[5]	=	yyvsp[-1].real;

					RiBound(bound);
				;
    break;}
case 78:
#line 1301 "rib.y"
{
					RtBound	bound;

					bound[0]	=	yyvsp[-5].real;
					bound[1]	=	yyvsp[-4].real;
					bound[2]	=	yyvsp[-3].real;
					bound[3]	=	yyvsp[-2].real;
					bound[4]	=	yyvsp[-1].real;
					bound[5]	=	yyvsp[0].real;

					RiBound(bound);
				;
    break;}
case 79:
#line 1323 "rib.y"
{
					RtBound	bound;

					bound[0]	=	yyvsp[-6].real;
					bound[1]	=	yyvsp[-5].real;
					bound[2]	=	yyvsp[-4].real;
					bound[3]	=	yyvsp[-3].real;
					bound[4]	=	yyvsp[-2].real;
					bound[5]	=	yyvsp[-1].real;

					RiDetail(bound);
				;
    break;}
case 80:
#line 1343 "rib.y"
{
					RtBound	bound;

					bound[0]	=	yyvsp[-5].real;
					bound[1]	=	yyvsp[-4].real;
					bound[2]	=	yyvsp[-3].real;
					bound[3]	=	yyvsp[-2].real;
					bound[4]	=	yyvsp[-1].real;
					bound[5]	=	yyvsp[0].real;

					RiDetail(bound);
				;
    break;}
case 81:
#line 1361 "rib.y"
{
					RiDetailRange(yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real,yyvsp[0].real);
				;
    break;}
case 82:
#line 1372 "rib.y"
{
					RiDetailRange(yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real);
				;
    break;}
case 83:
#line 1379 "rib.y"
{
					RiGeometricApproximation(yyvsp[-1].string,yyvsp[0].real);
				;
    break;}
case 84:
#line 1385 "rib.y"
{
					RiGeometricRepresentation(yyvsp[0].string);
				;
    break;}
case 85:
#line 1391 "rib.y"
{
					RiOrientation(yyvsp[0].string);
				;
    break;}
case 86:
#line 1396 "rib.y"
{
					RiReverseOrientation();
				;
    break;}
case 87:
#line 1402 "rib.y"
{
					RiSides((int) yyvsp[0].real);
				;
    break;}
case 88:
#line 1407 "rib.y"
{
					RiIdentity();
				;
    break;}
case 89:
#line 1430 "rib.y"
{
					RtMatrix	tmp;

					tmp[0][0]	=	yyvsp[-16].real;
					tmp[0][1]	=	yyvsp[-15].real;
					tmp[0][2]	=	yyvsp[-14].real;
					tmp[0][3]	=	yyvsp[-13].real;
					tmp[1][0]	=	yyvsp[-12].real;
					tmp[1][1]	=	yyvsp[-11].real;
					tmp[1][2]	=	yyvsp[-10].real;
					tmp[1][3]	=	yyvsp[-9].real;
					tmp[2][0]	=	yyvsp[-8].real;
					tmp[2][1]	=	yyvsp[-7].real;
					tmp[2][2]	=	yyvsp[-6].real;
					tmp[2][3]	=	yyvsp[-5].real;
					tmp[3][0]	=	yyvsp[-4].real;
					tmp[3][1]	=	yyvsp[-3].real;
					tmp[3][2]	=	yyvsp[-2].real;
					tmp[3][3]	=	yyvsp[-1].real;

					RiTransform(tmp);
				;
    break;}
case 90:
#line 1472 "rib.y"
{
					RtMatrix	tmp;

					tmp[0][0]	=	yyvsp[-16].real;
					tmp[0][1]	=	yyvsp[-15].real	;
					tmp[0][2]	=	yyvsp[-14].real;
					tmp[0][3]	=	yyvsp[-13].real;
					tmp[1][0]	=	yyvsp[-12].real;
					tmp[1][1]	=	yyvsp[-11].real;
					tmp[1][2]	=	yyvsp[-10].real;
					tmp[1][3]	=	yyvsp[-9].real;
					tmp[2][0]	=	yyvsp[-8].real;
					tmp[2][1]	=	yyvsp[-7].real;
					tmp[2][2]	=	yyvsp[-6].real;
					tmp[2][3]	=	yyvsp[-5].real;
					tmp[3][0]	=	yyvsp[-4].real;
					tmp[3][1]	=	yyvsp[-3].real;
					tmp[3][2]	=	yyvsp[-2].real;
					tmp[3][3]	=	yyvsp[-1].real;

					RiConcatTransform(tmp);
				;
    break;}
case 91:
#line 1497 "rib.y"
{
					RiPerspective(yyvsp[0].real);
				;
    break;}
case 92:
#line 1505 "rib.y"
{
					RiTranslate(yyvsp[-2].real,yyvsp[-1].real,yyvsp[0].real);
				;
    break;}
case 93:
#line 1513 "rib.y"
{
					RiScale(yyvsp[-2].real,yyvsp[-1].real,yyvsp[0].real);
				;
    break;}
case 94:
#line 1522 "rib.y"
{
					RiRotate(yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real,yyvsp[0].real);
				;
    break;}
case 95:
#line 1534 "rib.y"
{
					RiSkew(yyvsp[-6].real,yyvsp[-5].real,yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real,yyvsp[0].real);
				;
    break;}
case 96:
#line 1548 "rib.y"
{
					RiSkew(yyvsp[-7].real,yyvsp[-6].real,yyvsp[-5].real,yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real);
				;
    break;}
case 97:
#line 1555 "rib.y"
{
					RiDeformationV(yyvsp[-1].string,numParameters,tokens,vals);
				;
    break;}
case 98:
#line 1562 "rib.y"
{
					RiDisplacementV(yyvsp[-1].string,numParameters,tokens,vals);
				;
    break;}
case 99:
#line 1568 "rib.y"
{
					RiCoordinateSystem(yyvsp[0].string);
				;
    break;}
case 100:
#line 1574 "rib.y"
{
					RiCoordSysTransform(yyvsp[0].string);
				;
    break;}
case 101:
#line 1579 "rib.y"
{
					RiTransformBegin();
				;
    break;}
case 102:
#line 1584 "rib.y"
{
					RiTransformEnd();
				;
    break;}
case 103:
#line 1591 "rib.y"
{
					if (parameterListCheck()) {
						RiAttributeV(yyvsp[-1].string,numParameters,tokens,vals);
					}
				;
    break;}
case 104:
#line 1599 "rib.y"
{
					if (parameterListCheck()) {	
						if (sizeCheck(numVertex,0,0,1)) {
							RiPolygonV(numVertex,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 105:
#line 1610 "rib.y"
{
					int		*argi	=	(int *) get(0);

					if (parameterListCheck()) {
						if (sizeCheck(numVertex,0,0,1)) {
							RiGeneralPolygonV(yyvsp[-1].integer,argi,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 106:
#line 1624 "rib.y"
{
					int	*argi1		=	(int *) get(0);
					int	*argi2		=	(int *) get(yyvsp[-2].integer);
					int	nvertices	=	0;
					int	i;
					int	maxVertex	=	0;


					// Find out how many items are in verts array
					for (i=0;i<yyvsp[-2].integer;i++) {
						nvertices	+=	argi1[i];
					}

					if (nvertices != yyvsp[-1].integer) {
						error(CODE_MISSINGDATA,"Vertex count mismatch (%d != %d)\n",nvertices,yyvsp[-1].integer);
					} else {
						// Find out the number of vertices required
						for (i=0,maxVertex=0;i<nvertices;i++) {
							if (argi2[i] > maxVertex)
								maxVertex	=	argi2[i];
						}

						maxVertex++;

						if (parameterListCheck()) {
							if (sizeCheck(maxVertex,0,nvertices,yyvsp[-2].integer)) {
								RiPointsPolygonsV(yyvsp[-2].integer,argi1,argi2,numParameters,tokens,vals);
							}
						}
					}
				;
    break;}
case 107:
#line 1661 "rib.y"
{
					int	*argi1		=	(int *) get(0);
					int	*argi2		=	(int *) get(yyvsp[-3].integer);
					int	*argi3		=	(int *) get(yyvsp[-2].integer+yyvsp[-3].integer);
					int	numvertices	=	0;
					int	numloops	=	0;
					int	maxVertex	=	0;
					int	i;

					for (i=0;i<yyvsp[-3].integer;i++) {
						numloops	+=	argi1[i];
					}

					if (numloops != yyvsp[-2].integer) {
						error(CODE_MISSINGDATA,"Loop count mismatch (%d != %d)\n",numloops,yyvsp[-2].integer);
					} else {
						for (i=0;i<yyvsp[-2].integer;i++) {
							numvertices	+=	argi2[i];
						}

						if (numvertices != yyvsp[-1].integer) {
							error(CODE_MISSINGDATA,"Vertex count mismatch (%d != %d)\n",numvertices,yyvsp[-1].integer);
						} else {
							for (i=0;i<numvertices;i++) {
								if (argi3[i] > maxVertex)
									maxVertex	=	argi3[i];
							}

							maxVertex++;

							if (parameterListCheck()) {
								if (sizeCheck(maxVertex,0,numvertices,yyvsp[-3].integer)) {
									RiPointsGeneralPolygonsV(yyvsp[-3].integer,argi1,argi2,argi3,numParameters,tokens,vals);
								}
							}
						}
					}
				;
    break;}
case 108:
#line 1705 "rib.y"
{
					RtBasis	*argf1,*argf2;

					if ((getBasis(&argf1,yyvsp[-3].string)) && (getBasis(&argf2,yyvsp[-1].string))) {
						RiBasis(argf1[0],(int) yyvsp[-2].real, argf2[0],(int) yyvsp[0].real);
					}
				;
    break;}
case 109:
#line 1735 "rib.y"
{
					RtBasis	*argf2;

					if (getBasis(&argf2,yyvsp[-1].string)) {
						RtBasis	tmp;
					
						tmp[0][0]	=	yyvsp[-19].real;
						tmp[0][1]	=	yyvsp[-18].real;
						tmp[0][2]	=	yyvsp[-17].real;
						tmp[0][3]	=	yyvsp[-16].real;
						tmp[1][0]	=	yyvsp[-15].real;
						tmp[1][1]	=	yyvsp[-14].real;
						tmp[1][2]	=	yyvsp[-13].real;
						tmp[1][3]	=	yyvsp[-12].real;
						tmp[2][0]	=	yyvsp[-11].real;
						tmp[2][1]	=	yyvsp[-10].real;
						tmp[2][2]	=	yyvsp[-9].real;
						tmp[2][3]	=	yyvsp[-8].real;
						tmp[3][0]	=	yyvsp[-7].real;
						tmp[3][1]	=	yyvsp[-6].real;
						tmp[3][2]	=	yyvsp[-5].real;
						tmp[3][3]	=	yyvsp[-4].real;
										
						RiBasis(tmp,(int) yyvsp[-2].real,argf2[0],(int) yyvsp[0].real);
					}
				;
    break;}
case 110:
#line 1784 "rib.y"
{
					RtBasis	*argf1;

					if (getBasis(&argf1,yyvsp[-20].string)) {
						RtBasis	tmp;
					
						tmp[0][0]	=	yyvsp[-17].real;
						tmp[0][1]	=	yyvsp[-16].real;
						tmp[0][2]	=	yyvsp[-15].real;
						tmp[0][3]	=	yyvsp[-14].real;
						tmp[1][0]	=	yyvsp[-13].real;
						tmp[1][1]	=	yyvsp[-12].real;
						tmp[1][2]	=	yyvsp[-11].real;
						tmp[1][3]	=	yyvsp[-10].real;
						tmp[2][0]	=	yyvsp[-9].real;
						tmp[2][1]	=	yyvsp[-8].real;
						tmp[2][2]	=	yyvsp[-7].real;
						tmp[2][3]	=	yyvsp[-6].real;
						tmp[3][0]	=	yyvsp[-5].real;
						tmp[3][1]	=	yyvsp[-4].real;
						tmp[3][2]	=	yyvsp[-3].real;
						tmp[3][3]	=	yyvsp[-2].real;

						RiBasis(argf1[0],(int) yyvsp[-19].real,tmp,(int) yyvsp[0].real);
					}
				;
    break;}
case 111:
#line 1850 "rib.y"
{
					RtBasis	b1,b2;

					b1[0][0]	=	yyvsp[-36].real;
					b1[0][1]	=	yyvsp[-35].real;
					b1[0][2]	=	yyvsp[-34].real;
					b1[0][3]	=	yyvsp[-33].real;
					b1[1][0]	=	yyvsp[-32].real;
					b1[1][1]	=	yyvsp[-31].real;
					b1[1][2]	=	yyvsp[-30].real;
					b1[1][3]	=	yyvsp[-29].real;
					b1[2][0]	=	yyvsp[-28].real;
					b1[2][1]	=	yyvsp[-27].real;
					b1[2][2]	=	yyvsp[-26].real;
					b1[2][3]	=	yyvsp[-25].real;
					b1[3][0]	=	yyvsp[-24].real;
					b1[3][1]	=	yyvsp[-23].real;
					b1[3][2]	=	yyvsp[-22].real;
					b1[3][3]	=	yyvsp[-21].real;

					b2[0][0]	=	yyvsp[-17].real;
					b2[0][1]	=	yyvsp[-16].real;
					b2[0][2]	=	yyvsp[-15].real;
					b2[0][3]	=	yyvsp[-14].real;
					b2[1][0]	=	yyvsp[-13].real;
					b2[1][1]	=	yyvsp[-12].real;
					b2[1][2]	=	yyvsp[-11].real;
					b2[1][3]	=	yyvsp[-10].real;
					b2[2][0]	=	yyvsp[-9].real;
					b2[2][1]	=	yyvsp[-8].real;
					b2[2][2]	=	yyvsp[-7].real;
					b2[2][3]	=	yyvsp[-6].real;
					b2[3][0]	=	yyvsp[-5].real;
					b2[3][1]	=	yyvsp[-4].real;
					b2[3][2]	=	yyvsp[-3].real;
					b2[3][3]	=	yyvsp[-2].real;

					RiBasis(b1,(int) yyvsp[-19].real,b2,(int) yyvsp[0].real);
				;
    break;}
case 112:
#line 1893 "rib.y"
{
					int	numExpectedVertices;
					int	numExpectedPatches	=	1;


					if (strcmp(yyvsp[-1].string,RI_BILINEAR) == 0) {
						numExpectedVertices	=	4;
					} else if (strcmp(yyvsp[-1].string,RI_BICUBIC) == 0) {
						numExpectedVertices	=	16;
					} else {
						error(CODE_BADTOKEN,"Unknown patch type: \"%s\"\n",yyvsp[-1].string);
						numExpectedVertices	=	0;
					}

					if (numExpectedVertices > 0) {
						if (parameterListCheck()) {
							if (sizeCheck(numExpectedVertices,4,4,1)) {
								RiPatchV(yyvsp[-1].string,numParameters,tokens,vals);
							}
						}
					}
				;
    break;}
case 113:
#line 1923 "rib.y"
{
					int	numExpectedVertices;
					int	numuPatches,numvPatches;
					int	nu	=	(int) yyvsp[-4].real;
					int	nv	=	(int) yyvsp[-2].real;
					CAttributes	*attributes	=	CRenderer::context->getAttributes(FALSE);
					int	uw,vw;
					int	numVaryings;

					if (strcmp(yyvsp[-3].string,RI_PERIODIC) == 0) {
						uw	=	TRUE;
					} else {
						uw	=	FALSE;
					}

					if (strcmp(yyvsp[-1].string,RI_PERIODIC) == 0) {
						vw	=	TRUE;
					} else {
						vw	=	FALSE;
					}

					if (strcmp(yyvsp[-5].string,RI_BILINEAR) == 0) {
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
					} else if (strcmp(yyvsp[-5].string,RI_BICUBIC) == 0) {
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
						error(CODE_BADTOKEN,"Unknown patch type: \"%s\"\n",yyvsp[-5].string);
						numExpectedVertices	=	0;
					}

					if (numExpectedVertices > 0) {
						if (parameterListCheck()) {
							if (sizeCheck(numExpectedVertices,numVaryings,numuPatches*numvPatches*4,numuPatches*numvPatches)) {
								RiPatchMeshV(yyvsp[-5].string,(int) yyvsp[-4].real,yyvsp[-3].string,(int) yyvsp[-2].real,yyvsp[-1].string,numParameters,tokens,vals);
							}
						}
					}
				;
    break;}
case 114:
#line 2004 "rib.y"
{
					float	*argf1	=	(float *) get(0);
					float	*argf2	=	(float *) get(yyvsp[-8].integer);

					int		uPoints	=	(int) yyvsp[-10].real;
					int		uOrder	=	(int) yyvsp[-9].real;
					int		vPoints	=	(int) yyvsp[-5].real;
					int		vOrder	=	(int) yyvsp[-4].real;

					int		uPatches	=	uPoints - uOrder+1;
					int		vPatches	=	vPoints - vOrder+1;

					int		numExpectedVertices	=	uPoints*vPoints;

					if (parameterListCheck()) {
						if (sizeCheck(numExpectedVertices,(uPoints-uOrder+2)*(vPoints-vOrder+2),uPatches*vPatches*4,uPatches*vPatches)) {
							RiNuPatchV((int) yyvsp[-10].real,(int) yyvsp[-9].real,argf1,yyvsp[-7].real,yyvsp[-6].real,(int) yyvsp[-5].real,(int) yyvsp[-4].real,argf2,yyvsp[-2].real,yyvsp[-1].real,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 115:
#line 2035 "rib.y"
{
					int		*argi1	=	(int *)		get(0);
					int		*argi2	=	(int *)		get(yyvsp[-8].integer);
					float	*argf3	=	(float *)	get(yyvsp[-7].integer+yyvsp[-8].integer);
					float	*argf4	=	(float *)	get(yyvsp[-6].integer+yyvsp[-7].integer+yyvsp[-7].integer);
					float	*argf5	=	(float *)	get(yyvsp[-5].integer+yyvsp[-6].integer+yyvsp[-7].integer+yyvsp[-8].integer);
					int		*argi6	=	(int *)		get(yyvsp[-4].integer+yyvsp[-5].integer+yyvsp[-6].integer+yyvsp[-7].integer+yyvsp[-8].integer);
					float	*argf7	=	(float *)	get(yyvsp[-3].integer+yyvsp[-4].integer+yyvsp[-5].integer+yyvsp[-6].integer+yyvsp[-7].integer+yyvsp[-8].integer);
					float	*argf8	=	(float *)	get(yyvsp[-2].integer+yyvsp[-3].integer+yyvsp[-4].integer+yyvsp[-5].integer+yyvsp[-6].integer+yyvsp[-7].integer+yyvsp[-8].integer);
					float	*argf9	=	(float *)	get(yyvsp[-1].integer+yyvsp[-2].integer+yyvsp[-3].integer+yyvsp[-4].integer+yyvsp[-5].integer+yyvsp[-6].integer+yyvsp[-7].integer+yyvsp[-8].integer);

					RiTrimCurve(yyvsp[-8].integer,argi1,argi2,argf3,argf4,argf5,argi6,argf7,argf8,argf9);
				;
    break;}
case 116:
#line 2055 "rib.y"
{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiSphereV(yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 117:
#line 2071 "rib.y"
{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiSphereV(yyvsp[-5].real,yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 118:
#line 2084 "rib.y"
{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiConeV(yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 119:
#line 2099 "rib.y"
{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiConeV(yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 120:
#line 2113 "rib.y"
{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiCylinderV(yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 121:
#line 2129 "rib.y"
{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiCylinderV(yyvsp[-5].real,yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 122:
#line 2146 "rib.y"
{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RtPoint	p1,p2;

							p1[0]	=	yyvsp[-7].real;
							p1[1]	=	yyvsp[-6].real;
							p1[2]	=	yyvsp[-5].real;
							p2[0]	=	yyvsp[-4].real;
							p2[1]	=	yyvsp[-3].real;
							p2[2]	=	yyvsp[-2].real;

							RiHyperboloidV(p1,p2,yyvsp[-1].real,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 123:
#line 2174 "rib.y"
{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RtPoint	p1,p2;

							p1[0]	=	yyvsp[-8].real;
							p1[1]	=	yyvsp[-7].real;
							p1[2]	=	yyvsp[-6].real;
							p2[0]	=	yyvsp[-5].real;
							p2[1]	=	yyvsp[-4].real;
							p2[2]	=	yyvsp[-3].real;

							RiHyperboloidV(p1,p2,yyvsp[-2].real,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 124:
#line 2197 "rib.y"
{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiParaboloidV(yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 125:
#line 2213 "rib.y"
{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiParaboloidV(yyvsp[-5].real,yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 126:
#line 2226 "rib.y"
{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiDiskV(yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 127:
#line 2241 "rib.y"
{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiDiskV(yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 128:
#line 2256 "rib.y"
{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiTorusV(yyvsp[-5].real,yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 129:
#line 2273 "rib.y"
{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiTorusV(yyvsp[-6].real,yyvsp[-5].real,yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 130:
#line 2286 "rib.y"
{
					int			*argi1		=	(int *) get(0);
					int			numVertices,numUniforms;
					CAttributes	*attributes	=	CRenderer::context->getAttributes(FALSE);
					int			wrap;
					int			numVaryings,i;

					if (strcmp(yyvsp[-1].string,RI_PERIODIC) == 0) {
						wrap	=	TRUE;
					} else {
						wrap	=	FALSE;
					}

					if (strcmp(yyvsp[-3].string,RI_LINEAR) == 0) {
						for (i=0,numVertices=0;i<yyvsp[-2].integer;i++) {
							numVertices	+=	argi1[i];
						}

						numVaryings		=	numVertices;
						numUniforms		=	yyvsp[-2].integer;
					} else if (strcmp(yyvsp[-3].string,RI_CUBIC) == 0) {
						for (i=0,numVertices=0,numVaryings=0,numUniforms=0;i<yyvsp[-2].integer;i++) {
							int	j		=	(argi1[i] - 4) / attributes->vStep + 1;
							numVertices	+=	argi1[i];
							numVaryings	+=	j + (1 - wrap);
						}
						numUniforms		=	yyvsp[-2].integer;
					} else {
						error(CODE_BADTOKEN,"Unknown patch type: \"%s\"\n",yyvsp[-3].string);
						numVertices	=	0;
					}

					if (numVertices > 0) {
						if (parameterListCheck()) {
							if (sizeCheck(numVertices,numVaryings,0,numUniforms)) {
								RiCurvesV(yyvsp[-3].string,yyvsp[-2].integer,argi1,yyvsp[-1].string,numParameters,tokens,vals);
							}
						}
					}
				;
    break;}
case 131:
#line 2329 "rib.y"
{
					if (parameterListCheck()) {
						if (sizeCheck(numVertex,0,0,1)) {
							RiPointsV(numVertex,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 132:
#line 2346 "rib.y"
{
					int		*argi1,*argi2,*argi3,*argi4;
					char	**args1;
					float	*argf1;
					int		numVertices,i,j;

					if (parameterListCheck()) {
						argi1	=	(int *)		get(0);
						argi2	=	(int *)		get(yyvsp[-6].integer);
						args1	=	(char **)	get(yyvsp[-6].integer+yyvsp[-5].integer);
						argi3	=	(int *)		get(yyvsp[-6].integer+yyvsp[-5].integer+yyvsp[-4].integer);
						argi4	=	(int *)		get(yyvsp[-6].integer+yyvsp[-5].integer+yyvsp[-4].integer+yyvsp[-3].integer);
						argf1	=	(float *)	get(yyvsp[-6].integer+yyvsp[-5].integer+yyvsp[-4].integer+yyvsp[-3].integer+yyvsp[-2].integer);

						// Count the number of faces / vertices
						for (i=0,j=0;i<yyvsp[-6].integer;j+=argi1[i],i++);

						for (numVertices=-1,i=0;i<j;i++) {
							if (argi2[i] > numVertices)	numVertices	=	argi2[i];
						}
						numVertices++;


						if (sizeCheck(numVertices,numVertices,j,yyvsp[-6].integer)) {
							RiSubdivisionMeshV(yyvsp[-7].string,yyvsp[-6].integer,argi1,argi2,yyvsp[-4].integer,args1,argi3,argi4,argf1,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 133:
#line 2380 "rib.y"
{
					int		*argi1,*argi2;
					int		numVertices,i,j;

					if (parameterListCheck()) {
						argi1	=	(int *) get(0);
						argi2	=	(int *) get(yyvsp[-2].integer);

						// Count the number of faces / vertices
						for (i=0,j=0;i<yyvsp[-2].integer;j+=argi1[i],i++);

						for (numVertices=-1,i=0;i<j;i++) {
							if (argi2[i] > numVertices)	numVertices	=	argi2[i];
						}
						numVertices++;


						if (sizeCheck(numVertices,numVertices,j,yyvsp[-2].integer)) {
							RiSubdivisionMeshV(yyvsp[-3].string,yyvsp[-2].integer,argi1,argi2,0,NULL,NULL,NULL,NULL,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 134:
#line 2408 "rib.y"
{
					// FIXME: Not implemented
				;
    break;}
case 135:
#line 2415 "rib.y"
{
					if (parameterListCheck()) {
						RiGeometryV(yyvsp[-1].string,numParameters,tokens,vals);
					}
				;
    break;}
case 136:
#line 2432 "rib.y"
{
					RtBound			bound;
					CDelayedData	*cData	=	new CDelayedData;
					char			**arg;

					bound[0]	=	yyvsp[-6].real;
					bound[1]	=	yyvsp[-5].real;
					bound[2]	=	yyvsp[-4].real;
					bound[3]	=	yyvsp[-3].real;
					bound[4]	=	yyvsp[-2].real;
					bound[5]	=	yyvsp[-1].real;

					cData->bmin[COMP_X]	=	yyvsp[-6].real;
					cData->bmin[COMP_Y]	=	yyvsp[-5].real;
					cData->bmin[COMP_Z]	=	yyvsp[-4].real;

					cData->bmax[COMP_X]	=	yyvsp[-3].real;
					cData->bmax[COMP_Y]	=	yyvsp[-2].real;
					cData->bmax[COMP_Z]	=	yyvsp[-1].real;

					if (strcmp(yyvsp[-9].string,RI_PROCDELAYEDREADARCHIVE) == 0) {
						if (yyvsp[-8].integer != 1) {
							error(CODE_MISSINGDATA,"Proc delayed archive expects one argument (given %d)\n",yyvsp[-8].integer);
						} else {
							arg		=	(char **) get(0);

							cData->generator	=	strdup(arg[0]);

							RiProcedural((RtPointer) cData,bound,RiProcDelayedReadArchive,RiProcFree);
						}
					} else if (strcmp(yyvsp[-9].string,RI_PROCRUNPROGRAM) == 0) {
						if (yyvsp[-8].integer != 2) {
							error(CODE_MISSINGDATA,"Proc delayed archive expects two arguments (given %d)\n",yyvsp[-8].integer);
						} else {
							arg		=	(char **) get(0);

							cData->generator	=	strdup(arg[0]);
							cData->helper		=	strdup(arg[1]);

							RiProcedural((RtPointer) cData,bound,RiProcRunProgram,RiProcFree);
						}
					} else if (strcmp(yyvsp[-9].string,RI_PROCDYNAMICLOAD) == 0) {
						if (yyvsp[-8].integer != 2) {
							error(CODE_MISSINGDATA,"Proc delayed archive expects two arguments (given %d)\n",yyvsp[-8].integer);
						} else {
							arg		=	(char **) get(0);

							cData->generator	=	strdup(arg[0]);
							cData->helper		=	strdup(arg[1]);

							RiProcedural((RtPointer) cData,bound,RiProcDynamicLoad,RiProcFree);
						}
					} else {
						error(CODE_BADTOKEN,"Unknown procedural: %s\n",yyvsp[-9].string);
						delete cData;
					}
				;
    break;}
case 137:
#line 2492 "rib.y"
{
					RiSolidBegin(yyvsp[0].string);
				;
    break;}
case 138:
#line 2497 "rib.y"
{
					RiSolidEnd();
				;
    break;}
case 139:
#line 2503 "rib.y"
{
					if (ribObjects == NULL)	ribObjects	=	new CArray<RtPointer>;

					(*ribObjects)[(int) yyvsp[0].real]	=	RiObjectBegin();
				;
    break;}
case 140:
#line 2510 "rib.y"
{
					RiObjectEnd();
				;
    break;}
case 141:
#line 2516 "rib.y"
{
					if (ribObjects != NULL) {
						RiObjectInstance((*ribObjects)[(int) yyvsp[0].real]);
					} else {
						error(CODE_MISSINGDATA,"Object %d is not found\n",(int) yyvsp[0].real);
					}
				;
    break;}
case 142:
#line 2526 "rib.y"
{
					float	*argf	=	(float *) get(0);

					RiMotionBeginV(yyvsp[0].integer,argf);
				;
    break;}
case 143:
#line 2533 "rib.y"
{
					RiMotionEnd();
				;
    break;}
case 144:
#line 2546 "rib.y"
{
					RtFilterFunc	f;

					if ((f		=	getFilter(yyvsp[-3].string)) != NULL)  {
						RiMakeTextureV(yyvsp[-7].string,yyvsp[-6].string,yyvsp[-5].string,yyvsp[-4].string,f,yyvsp[-2].real,yyvsp[-1].real,numParameters,tokens,vals);
					}
				;
    break;}
case 145:
#line 2558 "rib.y"
{
					RiMakeTexture3DV(yyvsp[-2].string,yyvsp[-1].string,numParameters,tokens,vals);
				;
    break;}
case 146:
#line 2571 "rib.y"
{
					RtFilterFunc	f;

					if ((f		=	getFilter(yyvsp[-3].string)) != NULL) {
						RiMakeBumpV(yyvsp[-7].string,yyvsp[-6].string,yyvsp[-5].string,yyvsp[-4].string,f,yyvsp[-2].real,yyvsp[-1].real,numParameters,tokens,vals);
					}
				;
    break;}
case 147:
#line 2586 "rib.y"
{
					RtFilterFunc	f;

					if ((f		=	getFilter(yyvsp[-3].string)) != NULL) {
						RiMakeLatLongEnvironmentV(yyvsp[-5].string,yyvsp[-4].string,f,yyvsp[-2].real,yyvsp[-1].real,numParameters,tokens,vals);
					}
				;
    break;}
case 148:
#line 2607 "rib.y"
{
					RtFilterFunc	f;

					if ((f =	getFilter(yyvsp[-3].string)) != NULL) {
						RiMakeCubeFaceEnvironmentV(yyvsp[-11].string,yyvsp[-10].string,yyvsp[-9].string,yyvsp[-8].string,yyvsp[-7].string,yyvsp[-6].string,yyvsp[-5].string,yyvsp[-4].real,f,yyvsp[-2].real,yyvsp[-1].real,numParameters,tokens,vals);
					}
				;
    break;}
case 149:
#line 2619 "rib.y"
{
					RiMakeShadowV(yyvsp[-2].string,yyvsp[-1].string,numParameters,tokens,vals);
				;
    break;}
case 150:
#line 2625 "rib.y"
{
					RtErrorHandler 	e	=	getErrorHandler(yyvsp[0].string);

					if (e != NULL) {
						RiErrorHandler(e);
					}
				;
    break;}
case 151:
#line 2635 "rib.y"
{
				;
    break;}
case 152:
#line 2640 "rib.y"
{
				;
    break;}
case 153:
#line 2644 "rib.y"
{
					if (YYRECOVERING() == 0) {
						error(CODE_BADFILE,"Syntax error.\n");
					}
				;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 543 "/usr/share/bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;

 yyacceptlab:
  /* YYACCEPT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 0;

 yyabortlab:
  /* YYABORT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 1;
}
#line 2651 "rib.y"


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
		CArray<RtPointer>	*savedLights					=	lights;
		CTrie<char *>		*savedLightNames				=	lightNames;
		CArray<RtPointer>	*savedObjects					=	ribObjects;
		CArray<char *>		*savedAllocatedStrings			=	allocatedStrings;
		int					savedRibLineno					=	ribLineno;
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
		lightNames			=	NULL;
		ribObjects			=	NULL;
		allocatedStrings	=	new CArray<char *>;
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
		
		ribFile				=	fileName;
		ribLineno			=	1;

		ribparse();

		if (ribin != NULL) {
#ifdef HAVE_ZLIB
			gzclose(ribin);
#else
			fclose(ribin);
#endif
		}

		if (lights		!= NULL)	delete lights;
		if (lightNames	!= NULL)	delete lightNames;
		if (ribObjects	!= NULL)	delete ribObjects;
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
void		parserCleanup() {
	rib_delete_buffer(YY_CURRENT_BUFFER);
	yy_init				= 1;
}

