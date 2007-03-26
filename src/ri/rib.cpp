
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
#define	RIB_ARCHIVE_BEGIN	357
#define	RIB_ARCHIVE_END	358
#define	RIB_RESOURCE	359
#define	RIB_RESOURCE_BEGIN	360
#define	RIB_RESOURCE_END	361
#define	RIB_IFBEGIN	362
#define	RIB_IFEND	363
#define	RIB_ELSEIF	364
#define	RIB_ELSE	365
#define	RIB_ERROR_HANDLER	366
#define	RIB_VERSION	367
#define	RIB_VERSION_STRING	368
#define	RIB_ARRAY_BEGIN	369
#define	RIB_ARRAY_END	370
#define	RIB_TEXT	371
#define	RIB_FLOAT	372
#define	RIB_STRUCTURE_COMMENT	373

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
	char	*string;
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

// Holds information about a parameter
typedef struct {
	char		*name;			// Name of the parameter
	ERIBType	type;			// Type of the parameter
	int			numItems;		// Number of items of type ERIBValue
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
static	CArray<char *>		*permaStrings				=	NULL;	// Strings that have been allocated for the whole rib stack
static	void				(*callback)(const char *)	=	NULL;	// The callback function for the parser

static	CArray<char *>		allStrings;								// Array of all strings (cleared after every command)
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


#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		665
#define	YYFLAG		-32768
#define	YYNTBASE	120

#define YYTRANSLATE(x) ((unsigned)(x) <= 373 ? yytranslate[x] : 133)

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
   107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
   117,   118,   119
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
   850,   852,   854,   856,   861,   865,   867,   871,   873,   876,
   879,   882
};

static const short yyrhs[] = {   130,
     0,   121,   118,     0,   118,     0,   122,   118,     0,   118,
     0,   123,   117,     0,   117,     0,   115,   122,   116,     0,
   115,   116,     0,   124,     0,   122,     0,   115,   121,   116,
     0,   115,   116,     0,   115,   123,   116,     0,   117,     0,
   129,   128,     0,     0,   117,   125,     0,   117,   127,     0,
     0,   130,   131,   132,     0,     0,   119,     0,     3,   117,
   117,     0,     4,     0,     4,   118,     0,     5,     0,     6,
     0,     7,     0,     8,   118,   118,   118,     0,     9,   118,
     0,    10,   118,   118,   118,   118,     0,    10,   115,   118,
   118,   118,   118,   116,     0,    11,   118,   118,   118,   118,
     0,    11,   115,   118,   118,   118,   118,   116,     0,    12,
   117,   128,     0,    13,   118,   118,     0,    14,   118,   118,
   118,   118,   118,   118,     0,    15,   118,   118,   118,     0,
    15,     0,    16,   118,   118,     0,    17,   118,     0,    18,
   118,   118,     0,    19,   117,   118,   118,     0,    20,   118,
   118,     0,    21,   117,   128,     0,    22,   117,   118,   118,
   118,   118,     0,    23,   117,   117,   117,   128,     0,    24,
   117,   128,     0,    25,   117,   128,     0,    26,   125,     0,
    26,   124,   124,     0,    27,   118,     0,    28,   117,   128,
     0,    29,     0,    30,     0,    31,   118,   118,   118,     0,
    32,   118,   118,   118,     0,    31,   115,   118,   118,   118,
   116,     0,    32,   115,   118,   118,   118,   116,     0,    33,
   118,   118,   118,   118,   118,   118,   118,   118,     0,    33,
   115,   118,   118,   118,   118,   118,   118,   118,   118,   116,
     0,    34,   117,   118,   128,     0,    34,   117,   117,   128,
     0,    34,   117,   128,     0,    35,   117,   118,   128,     0,
    35,   117,   117,   128,     0,    36,   118,   118,     0,    36,
   117,   118,     0,    37,   117,   128,     0,    38,   117,   128,
     0,    39,   117,   128,     0,    40,   117,   128,     0,    41,
   118,     0,    42,   117,     0,    43,   118,     0,    44,   115,
   118,   118,   118,   118,   118,   118,   116,     0,    44,   118,
   118,   118,   118,   118,   118,     0,    45,   115,   118,   118,
   118,   118,   118,   118,   116,     0,    45,   118,   118,   118,
   118,   118,   118,     0,    46,   118,   118,   118,   118,     0,
    46,   115,   118,   118,   118,   118,   116,     0,    47,   117,
   118,     0,    48,   117,     0,    49,   117,     0,    50,     0,
    51,   118,     0,    52,     0,    53,   115,   118,   118,   118,
   118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
   118,   118,   118,   116,     0,    54,   115,   118,   118,   118,
   118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
   118,   118,   118,   116,     0,    55,   118,     0,    56,   118,
   118,   118,     0,    58,   118,   118,   118,     0,    57,   118,
   118,   118,   118,     0,    59,   118,   118,   118,   118,   118,
   118,   118,     0,    59,   115,   118,   118,   118,   118,   118,
   118,   118,   116,     0,    60,   117,   128,     0,    61,   117,
   128,     0,    62,   117,     0,    63,   117,     0,    64,     0,
    65,     0,    66,   117,   128,     0,    67,   128,     0,    68,
   126,   128,     0,    69,   126,   126,   128,     0,    70,   126,
   126,   126,   128,     0,    71,   117,   118,   117,   118,     0,
    71,   115,   118,   118,   118,   118,   118,   118,   118,   118,
   118,   118,   118,   118,   118,   118,   118,   118,   116,   118,
   117,   118,     0,    71,   117,   118,   115,   118,   118,   118,
   118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
   118,   118,   118,   116,   118,     0,    71,   115,   118,   118,
   118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
   118,   118,   118,   118,   116,   118,   115,   118,   118,   118,
   118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
   118,   118,   118,   116,   118,     0,    72,   117,   128,     0,
    73,   117,   118,   117,   118,   117,   128,     0,    74,   118,
   118,   124,   118,   118,   118,   118,   124,   118,   118,   128,
     0,    75,   126,   126,   124,   124,   124,   126,   124,   124,
   124,     0,    76,   118,   118,   118,   118,   128,     0,    76,
   115,   118,   118,   118,   118,   116,   128,     0,    77,   118,
   118,   118,   128,     0,    77,   115,   118,   118,   118,   116,
   128,     0,    78,   118,   118,   118,   118,   128,     0,    78,
   115,   118,   118,   118,   118,   116,   128,     0,    79,   118,
   118,   118,   118,   118,   118,   118,   128,     0,    79,   115,
   118,   118,   118,   118,   118,   118,   118,   116,   128,     0,
    80,   118,   118,   118,   118,   128,     0,    80,   115,   118,
   118,   118,   118,   116,   128,     0,    81,   118,   118,   118,
   128,     0,    81,   115,   118,   118,   118,   116,   128,     0,
    82,   118,   118,   118,   118,   118,   128,     0,    82,   115,
   118,   118,   118,   118,   118,   116,   128,     0,    83,   117,
   126,   117,   128,     0,    85,   128,     0,    86,   117,   126,
   126,   127,   126,   126,   124,   128,     0,    86,   117,   126,
   126,   128,     0,    87,   118,   124,   127,   128,     0,    84,
   117,   128,     0,    88,   117,   127,   115,   118,   118,   118,
   118,   118,   118,   116,     0,    89,   117,     0,    90,     0,
    91,   118,     0,    92,     0,    93,   118,     0,    94,   125,
     0,    95,     0,    96,   117,   117,   117,   117,   117,   118,
   118,   128,     0,    97,   117,   117,   128,     0,    98,   117,
   117,   117,   117,   117,   118,   118,   128,     0,    99,   117,
   117,   117,   118,   118,   128,     0,   100,   117,   117,   117,
   117,   117,   117,   117,   118,   117,   118,   118,   128,     0,
   101,   117,   117,   128,     0,   103,   117,   128,     0,   104,
     0,   106,     0,   107,     0,   105,   117,   117,   128,     0,
   108,   117,   128,     0,   109,     0,   110,   117,   128,     0,
   111,     0,   112,   117,     0,   113,   118,     0,   113,   114,
     0,     1,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   609,   612,   618,   627,   633,   641,   647,   655,   661,   670,
   674,   681,   687,   696,   702,   712,   716,   735,   746,   760,
   766,   778,   782,   788,   795,   800,   806,   811,   816,   821,
   829,   835,   844,   855,   864,   875,   882,   889,   900,   908,
   913,   920,   926,   933,   945,   952,   962,   972,   981,   988,
   997,  1011,  1026,  1032,  1041,  1046,  1051,  1065,  1079,  1095,
  1111,  1124,  1139,  1149,  1161,  1168,  1178,  1190,  1199,  1212,
  1219,  1226,  1233,  1240,  1246,  1252,  1258,  1280,  1300,  1322,
  1342,  1351,  1362,  1369,  1375,  1381,  1386,  1392,  1397,  1439,
  1481,  1487,  1495,  1503,  1512,  1524,  1538,  1545,  1552,  1558,
  1564,  1569,  1574,  1583,  1593,  1606,  1642,  1686,  1699,  1748,
  1797,  1876,  1902,  1978,  2011,  2035,  2049,  2065,  2078,  2093,
  2107,  2123,  2149,  2177,  2191,  2207,  2220,  2235,  2250,  2267,
  2313,  2323,  2361,  2389,  2398,  2407,  2476,  2482,  2487,  2495,
  2500,  2510,  2518,  2523,  2540,  2548,  2565,  2580,  2601,  2609,
  2616,  2621,  2626,  2631,  2639,  2646,  2651,  2658,  2663,  2673,
  2678,  2683
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
"RIB_MAKE_SHADOW","RIB_ARCHIVE_RECORD","RIB_ARCHIVE_BEGIN","RIB_ARCHIVE_END",
"RIB_RESOURCE","RIB_RESOURCE_BEGIN","RIB_RESOURCE_END","RIB_IFBEGIN","RIB_IFEND",
"RIB_ELSEIF","RIB_ELSE","RIB_ERROR_HANDLER","RIB_VERSION","RIB_VERSION_STRING",
"RIB_ARRAY_BEGIN","RIB_ARRAY_END","RIB_TEXT","RIB_FLOAT","RIB_STRUCTURE_COMMENT",
"start","ribIntString","ribFloatString","ribTextString","ribFloatArray","ribFloats",
"ribIntArray","ribTextArray","ribPL","ribParameter","ribCommands","@1","ribComm", NULL
};
#endif

static const short yyr1[] = {     0,
   120,   121,   121,   122,   122,   123,   123,   124,   124,   125,
   125,   126,   126,   127,   127,   128,   128,   129,   129,   131,
   130,   130,   132,   132,   132,   132,   132,   132,   132,   132,
   132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
   132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
   132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
   132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
   132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
   132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
   132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
   132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
   132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
   132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
   132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
   132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
   132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
   132,   132
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
     2,     2,     1,     9,     4,     9,     7,    13,     4,     3,
     1,     1,     1,     4,     3,     1,     3,     1,     2,     2,
     2,     1
};

static const short yydefact[] = {    22,
    20,     0,   162,     0,    25,    27,    28,    29,     0,     0,
     0,     0,     0,     0,     0,    40,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,    55,
    56,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    86,     0,    88,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,   101,   102,     0,    17,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    17,     0,     0,     0,     0,
   138,     0,   140,     0,     0,   143,     0,     0,     0,     0,
     0,     0,     0,   151,     0,   152,   153,     0,   156,     0,
   158,     0,     0,    23,    21,     0,    26,     0,    31,     0,
     0,     0,     0,    17,     0,     0,     0,     0,    42,     0,
     0,     0,    17,     0,     0,    17,    17,     0,     5,    11,
    10,    51,    53,    17,     0,     0,     0,     0,     0,     0,
    17,     0,     0,     0,    17,    17,    17,    17,    74,    75,
    76,     0,     0,     0,     0,     0,     0,     0,    84,    85,
    87,     0,     0,    91,     0,     0,     0,     0,     0,    17,
    17,    99,   100,    17,     0,   104,    17,     0,    17,     0,
     0,     0,     0,    17,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,    17,   131,     0,     0,     0,   137,   139,   141,
    10,   142,     0,     0,     0,     0,     0,     0,    17,     0,
    17,    17,   159,   161,   160,    24,     0,     0,     0,     0,
     0,    36,    37,     0,     0,    41,    43,     0,    45,    46,
     0,     0,    49,    50,     9,     0,     4,    52,    54,     0,
     0,     0,     0,     0,     0,    17,    17,    65,    17,    17,
    69,    68,    70,    71,    72,    73,     0,     0,     0,     0,
     0,     0,    83,     0,     0,     0,     0,     0,     0,     0,
    97,    98,   103,     0,    15,    18,    19,    16,    13,     3,
     0,   105,    17,     0,     0,     0,   112,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,   135,     0,     0,     0,     0,
     0,    17,     0,     0,     0,    17,   150,    17,   155,   157,
    30,     0,     0,     0,     0,     0,    39,    44,     0,    17,
     8,     0,    57,     0,    58,     0,     0,    15,    64,    63,
    67,    66,     0,     0,     0,     0,     0,     0,     0,     0,
    92,     0,    93,     0,     0,     7,     0,    12,     2,   106,
    17,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    17,     0,     0,     0,     0,     0,     0,     0,    17,     0,
     0,    17,    17,    17,     0,     0,   145,     0,     0,     0,
   149,   154,     0,    32,     0,    34,     0,     0,    48,     0,
     0,     0,     0,     0,     0,     0,     0,     0,    81,     0,
     0,    94,     0,     0,    14,     6,   107,     0,     0,   108,
     0,     0,     0,     0,    17,     0,   118,     0,    17,     0,
     0,     0,    17,     0,   126,     0,     0,   130,     0,   133,
   134,     0,     0,     0,     0,     0,     0,     0,     0,    47,
    59,    60,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    17,     0,     0,     0,   116,
    17,     0,   120,     0,     0,     0,   124,    17,     0,    17,
     0,     0,     0,     0,    17,     0,    33,    35,    38,     0,
     0,     0,    78,     0,    80,    82,     0,     0,     0,     0,
     0,     0,   113,     0,     0,    17,   119,    17,     0,     0,
    17,   127,     0,   128,     0,     0,     0,     0,   147,     0,
     0,     0,     0,     0,     0,     0,     0,    95,     0,     0,
     0,     0,   117,   121,     0,    17,   125,    17,    17,     0,
    17,    17,     0,     0,    61,    77,    79,     0,     0,     0,
     0,     0,     0,     0,     0,   122,   129,   132,     0,   144,
   146,     0,     0,     0,     0,    96,     0,     0,     0,   115,
    17,     0,     0,    62,     0,     0,     0,     0,    17,   123,
   136,     0,     0,     0,     0,     0,   114,    17,     0,     0,
     0,     0,   148,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,    89,    90,     0,     0,     0,     0,     0,
     0,     0,     0,   109,   110,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,   111,     0,     0,     0
};

static const short yydefgoto[] = {   663,
   301,   140,   377,   221,   296,   189,   297,   186,   187,     1,
     2,   115
};

static const short yypact[] = {-32768,
     3,   545,-32768,  -108,   -62,-32768,-32768,-32768,   -55,   -28,
   -99,   -95,   -29,   -18,   -15,   -14,   -12,   -11,    -9,    -6,
    -5,    -1,     1,     2,     4,     5,   -94,     8,     6,-32768,
-32768,   -93,   -89,   -88,    10,    11,   -43,    12,    13,    15,
    16,    17,    19,    20,   -87,   -83,   -82,    22,    23,    24,
-32768,    25,-32768,   -23,   -16,    26,    27,    29,    30,   -81,
    34,    37,    38,    39,-32768,-32768,    41,    42,    -3,    -3,
    -3,   -53,    43,    44,    45,    -3,   -77,   -76,   -75,   -71,
   -69,   -67,   -65,    47,    48,    42,    49,    50,    52,    53,
-32768,    54,-32768,    55,   -94,-32768,    57,    58,    59,    60,
    61,    62,    63,-32768,    64,-32768,-32768,    65,-32768,    66,
-32768,    67,  -106,-32768,-32768,    68,-32768,    75,-32768,    76,
    77,    78,    79,    42,    80,    81,    82,    83,-32768,    84,
    85,    86,    42,    87,    69,    42,    42,   -50,-32768,    88,
    56,-32768,-32768,    42,    89,    90,    91,    92,    93,    94,
   -24,   -22,    95,    96,    42,    42,    42,    42,-32768,-32768,
-32768,    97,    98,    99,   100,   101,   102,   103,-32768,-32768,
-32768,   104,   105,-32768,   107,   108,   109,   110,   111,    42,
    42,-32768,-32768,    42,  -104,-32768,    42,   -49,    42,    -3,
    -3,   112,   113,    42,   114,   115,    -3,   116,   117,   118,
   119,   121,   122,   123,   124,   125,   126,   127,   128,   129,
   130,    -3,    42,-32768,    -3,    56,   -44,-32768,-32768,-32768,
-32768,-32768,   132,   133,   134,   135,   137,   138,    42,   139,
    42,    42,-32768,-32768,-32768,-32768,   140,   142,   144,   145,
   146,-32768,-32768,   147,   148,-32768,-32768,   149,-32768,-32768,
   150,   152,-32768,-32768,-32768,   -36,-32768,-32768,-32768,   154,
   155,   156,   157,   158,   159,  -100,    42,-32768,    42,    42,
-32768,-32768,-32768,-32768,-32768,-32768,   160,   161,   162,   163,
   166,   167,-32768,   168,   169,   170,   171,   172,   173,   174,
-32768,-32768,-32768,   -57,-32768,-32768,-32768,-32768,-32768,-32768,
   -35,-32768,    42,    -3,   175,   -31,-32768,   153,    56,    56,
   176,   177,   178,   179,   180,   181,   182,   183,   185,   186,
   187,   188,   189,   190,   192,-32768,    -3,   -44,   193,   196,
   197,    42,   198,   199,   200,    42,-32768,    42,-32768,-32768,
-32768,   195,   201,   203,   204,   208,-32768,-32768,   209,    42,
-32768,   210,-32768,   211,-32768,   212,   213,   -63,-32768,-32768,
-32768,-32768,   214,   215,   216,   217,   218,   219,   220,   221,
-32768,   222,-32768,   223,   224,-32768,   -19,-32768,-32768,-32768,
    42,   225,   226,   227,   228,   229,    56,   230,   231,   232,
    42,   233,   234,   235,   236,   237,   238,   239,    42,   240,
   241,    42,   -30,    42,   243,   245,-32768,   246,   247,   250,
-32768,-32768,   251,-32768,   253,-32768,   254,   255,-32768,    21,
    46,   257,   258,   259,   260,   261,   262,   263,-32768,   264,
   265,-32768,   266,   267,-32768,-32768,-32768,   268,   269,-32768,
   271,   272,    56,   273,    42,    51,-32768,   274,    42,   276,
   277,   278,    42,   202,-32768,   279,   280,-32768,    -3,-32768,
-32768,   281,   283,   284,   285,   287,   248,   252,   288,-32768,
-32768,-32768,   290,   291,   292,   293,   295,   296,   286,   297,
   299,   300,   302,   305,   306,    42,   307,    -3,   289,-32768,
    42,   311,-32768,   310,   312,   313,-32768,    42,   314,    42,
    -3,   315,   316,   318,    42,   320,-32768,-32768,-32768,   321,
   322,   323,-32768,   324,-32768,-32768,   325,   326,   327,   328,
   330,   332,-32768,   333,    56,    42,-32768,    42,   335,   336,
    42,-32768,   339,-32768,    56,   338,   340,   341,-32768,   343,
   344,   345,   348,   349,   350,   351,   352,-32768,   353,   354,
    56,    56,-32768,-32768,   355,    42,-32768,    42,    42,   356,
    42,    42,   357,   358,-32768,-32768,-32768,   360,   363,   368,
   367,   369,   370,    56,   373,-32768,-32768,-32768,   372,-32768,
-32768,   374,   376,   375,   377,-32768,   378,   379,   381,-32768,
    42,   384,   383,-32768,   385,   386,   387,   388,    42,-32768,
-32768,   389,   391,   392,   393,   395,-32768,    42,   396,   397,
   398,   399,-32768,   400,   401,   403,   404,   405,   408,   409,
   410,   412,   413,   414,   415,   416,   417,   418,   419,   422,
   423,   424,   425,-32768,-32768,   426,   427,   -26,   531,   541,
   542,   543,   544,-32768,-32768,   547,   548,   549,   550,   551,
   552,   553,   554,   555,   556,   557,   558,   559,   560,   563,
   562,-32768,   120,   431,-32768
};

static const short yypgoto[] = {-32768,
-32768,  -137,-32768,   -27,   -25,   -66,  -211,   -79,-32768,-32768,
-32768,-32768
};


#define	YYLAST		680


static const short yytable[] = {   141,
   256,   142,    -1,   190,   191,   330,   214,   234,   116,   197,
   294,   235,   295,   139,   294,   120,   358,   139,   121,   122,
   138,   145,   123,   139,   146,   147,   149,   162,   148,   150,
   163,   164,   166,   178,   165,   167,   179,   198,   200,   202,
   199,   201,   203,   204,   242,   206,   205,   208,   207,   210,
   209,   294,   211,   250,   139,   117,   253,   254,   255,   376,
   139,   192,   118,   193,   259,   255,   299,   139,   300,   222,
   329,   268,   295,   153,   154,   273,   274,   275,   276,   351,
   378,   257,   379,   383,   329,   384,   358,   124,   640,   119,
   641,   172,   266,   267,   269,   270,   435,   436,   173,   125,
   291,   292,   126,   127,   293,   128,   129,   298,   130,   302,
   131,   188,   132,   258,   307,   133,   404,   134,   135,   664,
   136,   137,   144,   303,   304,   143,   151,   152,   155,   156,
   310,   157,   158,   326,   159,   160,   471,   161,   168,   169,
   170,     0,   171,   174,   175,   325,   176,   177,   327,   337,
   180,   339,   340,   181,   182,   183,   256,   184,   185,   194,
   195,   472,   196,   212,   213,   215,   491,   216,   217,   218,
   138,   219,   220,   223,   224,   225,   226,   227,   228,   229,
   230,   231,   232,   233,   236,   252,   359,   360,   328,   361,
   362,   459,   237,   238,   239,   240,   241,   243,   244,   245,
   246,   247,   248,   249,   251,   257,   260,   261,   262,   263,
   264,   265,   271,   272,   277,   278,   279,   280,   281,   282,
   283,   284,   285,   380,   286,   287,   288,   289,   290,   305,
   306,   308,   309,   311,   312,   313,   314,   381,   315,   316,
   317,   318,   319,   320,   321,   322,   323,   324,   331,   332,
   333,   334,   407,   335,   336,   338,   411,   341,   412,   342,
   403,   343,   344,   345,   346,   347,   348,   349,   350,   385,
   419,   352,   353,   354,   355,   356,   357,   363,   364,   365,
   366,   386,   387,   367,   368,   369,   370,   371,   372,   373,
   374,   375,   382,   388,   389,   390,   391,   392,   393,   394,
   395,   437,   396,   397,   398,   399,   400,   401,   402,   376,
   405,   447,   413,   406,   408,   409,   410,   498,   414,   455,
   415,   416,   458,   460,   461,   417,   418,   420,   421,   422,
   423,   424,   425,   426,   427,   428,   429,   430,   431,   432,
   433,   434,   438,   439,   440,   441,   442,   444,   445,   446,
   448,   449,   450,   451,   452,   453,   454,   456,   457,   443,
   462,   463,   464,   507,   465,   490,   466,   508,   467,   493,
   468,   469,   470,   497,   473,   474,   475,   476,   477,   478,
   479,   480,   481,   482,   483,   484,   485,   486,     0,   487,
   489,   492,   501,   494,   495,   496,   499,   500,   502,   503,
   504,   516,   505,   506,   526,   509,   523,   510,   511,   512,
   513,   527,   514,   515,   517,   488,   518,   519,   532,   520,
   534,   525,   521,   522,   524,   539,   528,   529,   531,   530,
   665,   533,   536,   537,   535,   538,   540,     0,   541,   542,
   543,   544,   545,   546,   547,   548,   553,   549,   554,   550,
   551,   557,   555,   556,   558,   560,     0,   561,   562,   563,
     0,   564,   565,   566,   567,     0,     0,   568,   569,   570,
   571,   572,   575,   579,   582,   583,   576,   584,   577,   578,
   585,   580,   581,   586,   587,     0,   588,   589,   591,   592,
   593,   594,   595,     0,   596,   597,   598,   552,   599,   601,
   602,     0,   603,   604,   605,   606,   608,   559,   609,   610,
   611,   600,   612,   614,   615,   616,   617,   618,   619,   607,
   620,   621,   622,   573,   574,   623,   624,   625,   613,   626,
   627,   628,   629,   630,   631,   632,   633,   634,   635,   636,
     0,     0,   637,   638,   639,     3,   590,     4,     5,     6,
     7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
    17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
    27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
    37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
    47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
    57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
    67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
    77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
    87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
    97,    98,    99,   100,   101,   102,   642,   103,   104,   105,
   106,   107,   108,   109,   110,   111,   112,   113,   643,   644,
   645,   646,     0,   114,   647,   648,   649,   650,   651,   652,
   653,   654,   655,   656,   657,   658,   659,   660,   661,   662
};

static const short yycheck[] = {    27,
   138,    27,     0,    70,    71,   217,    86,   114,   117,    76,
   115,   118,   117,   118,   115,   115,   117,   118,   118,   115,
   115,   115,   118,   118,   118,   115,   115,   115,   118,   118,
   118,   115,   115,   115,   118,   118,   118,   115,   115,   115,
   118,   118,   118,   115,   124,   115,   118,   115,   118,   115,
   118,   115,   118,   133,   118,   118,   136,   137,   116,   117,
   118,   115,   118,   117,   144,   116,   116,   118,   118,    95,
   115,   151,   117,   117,   118,   155,   156,   157,   158,   116,
   116,   118,   118,   115,   115,   117,   117,   117,   115,   118,
   117,   115,   117,   118,   117,   118,   116,   117,   115,   118,
   180,   181,   118,   118,   184,   118,   118,   187,   118,   189,
   117,   115,   118,   141,   194,   117,   328,   117,   117,     0,
   117,   117,   117,   190,   191,   118,   117,   117,   117,   117,
   197,   117,   117,   213,   118,   117,   116,   118,   117,   117,
   117,    -1,   118,   118,   118,   212,   118,   118,   215,   229,
   117,   231,   232,   117,   117,   117,   294,   117,   117,   117,
   117,   116,   118,   117,   117,   117,   116,   118,   117,   117,
   115,   118,   118,   117,   117,   117,   117,   117,   117,   117,
   117,   117,   117,   117,   117,   117,   266,   267,   216,   269,
   270,   403,   118,   118,   118,   118,   118,   118,   118,   118,
   118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
   118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
   118,   118,   118,   303,   118,   118,   118,   118,   118,   118,
   118,   118,   118,   118,   118,   118,   118,   304,   118,   118,
   118,   118,   118,   118,   118,   118,   118,   118,   117,   117,
   117,   117,   332,   117,   117,   117,   336,   118,   338,   118,
   327,   118,   118,   118,   118,   118,   118,   118,   117,   117,
   350,   118,   118,   118,   118,   118,   118,   118,   118,   118,
   118,   309,   310,   118,   118,   118,   118,   118,   118,   118,
   118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
   118,   381,   118,   118,   118,   118,   118,   118,   117,   117,
   115,   391,   118,   117,   117,   117,   117,   116,   118,   399,
   118,   118,   402,   403,   404,   118,   118,   118,   118,   118,
   118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
   118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
   118,   118,   118,   118,   118,   118,   118,   118,   118,   387,
   118,   117,   117,   116,   118,   445,   117,   116,   118,   449,
   118,   118,   118,   453,   118,   118,   118,   118,   118,   118,
   118,   118,   118,   118,   118,   118,   118,   117,    -1,   118,
   118,   118,   459,   118,   118,   118,   118,   118,   118,   117,
   117,   116,   118,   117,   116,   118,   486,   118,   118,   118,
   118,   491,   118,   118,   118,   443,   118,   118,   498,   118,
   500,   488,   118,   118,   118,   505,   116,   118,   116,   118,
     0,   118,   118,   118,   501,   118,   117,    -1,   118,   118,
   118,   118,   118,   118,   118,   118,   526,   118,   528,   118,
   118,   531,   118,   118,   116,   118,    -1,   118,   118,   117,
    -1,   118,   118,   116,   116,    -1,    -1,   118,   118,   118,
   118,   118,   118,   118,   118,   118,   556,   118,   558,   559,
   118,   561,   562,   116,   118,    -1,   118,   118,   116,   118,
   117,   116,   118,    -1,   118,   118,   118,   525,   118,   116,
   118,    -1,   118,   118,   118,   118,   118,   535,   118,   118,
   118,   591,   118,   118,   118,   118,   118,   118,   118,   599,
   118,   118,   118,   551,   552,   118,   118,   118,   608,   118,
   118,   118,   118,   118,   118,   118,   118,   116,   116,   116,
    -1,    -1,   118,   118,   118,     1,   574,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
    36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
    46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
    56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
    66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
    76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
    86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
    96,    97,    98,    99,   100,   101,   116,   103,   104,   105,
   106,   107,   108,   109,   110,   111,   112,   113,   118,   118,
   118,   118,    -1,   119,   118,   118,   118,   118,   118,   118,
   118,   118,   118,   118,   118,   118,   118,   118,   116,   118
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
#line 614 "rib.y"
{
					intArgs.push((int) yyvsp[0].real);
					yyval.integer	=	yyvsp[-1].integer	+	1;
				;
    break;}
case 3:
#line 620 "rib.y"
{
					intArgs.push((int) yyvsp[0].real);
					yyval.integer	=	1;
				;
    break;}
case 4:
#line 629 "rib.y"
{
					floatArgs.push(yyvsp[0].real);
					yyval.integer	=	yyvsp[-1].integer	+	1;
				;
    break;}
case 5:
#line 635 "rib.y"
{
					floatArgs.push(yyvsp[0].real);
					yyval.integer	=	1;
				;
    break;}
case 6:
#line 643 "rib.y"
{
					stringArgs.push(yyvsp[0].string);
					yyval.integer	=	yyvsp[-1].integer	+	1;
				;
    break;}
case 7:
#line 649 "rib.y"
{
					stringArgs.push(yyvsp[0].string);
					yyval.integer	=	1;
				;
    break;}
case 8:
#line 658 "rib.y"
{
					yyval.integer = yyvsp[-1].integer;
				;
    break;}
case 9:
#line 664 "rib.y"
{
					yyval.integer = 0;
				;
    break;}
case 10:
#line 671 "rib.y"
{
					yyval.integer	=	yyvsp[0].integer;
				;
    break;}
case 11:
#line 676 "rib.y"
{
					yyval.integer	=	yyvsp[0].integer;
				;
    break;}
case 12:
#line 684 "rib.y"
{
					yyval.integer = yyvsp[-1].integer;
				;
    break;}
case 13:
#line 690 "rib.y"
{
					yyval.integer = 0;
				;
    break;}
case 14:
#line 699 "rib.y"
{
					yyval.integer	=	yyvsp[-1].integer;
				;
    break;}
case 15:
#line 704 "rib.y"
{
					stringArgs.push(yyvsp[0].string);
					yyval.integer	= 1;
				;
    break;}
case 16:
#line 714 "rib.y"
{
				;
    break;}
case 17:
#line 717 "rib.y"
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
				;
    break;}
case 18:
#line 737 "rib.y"
{
					// A parameter is either a float array
					parameters[numParameters].name			=	yyvsp[-1].string;
					parameters[numParameters].type			=	RT_FLOAT;
					parameters[numParameters].numItems		=	yyvsp[0].integer;
					parameters[numParameters].valuesStart	=	floatArgs.numItems-yyvsp[0].integer;
					numParameters++;
					paramCheck();
				;
    break;}
case 19:
#line 749 "rib.y"
{	
					// Or a string array
					parameters[numParameters].name			=	yyvsp[-1].string;
					parameters[numParameters].type			=	RT_TEXT;
					parameters[numParameters].numItems		=	yyvsp[0].integer;
					parameters[numParameters].valuesStart	=	stringArgs.numItems-yyvsp[0].integer;
					numParameters++;
					paramCheck();
				;
    break;}
case 20:
#line 761 "rib.y"
{
					// Save the line number in case we have an error
					ribCommandLineno		=	ribLineno;
				;
    break;}
case 21:
#line 766 "rib.y"
{
				
					// Reset the number of parameters
					floatArgs.numItems		=	0;
					intArgs.numItems		=	0;
					stringArgs.numItems		=	0;
					numParameters			=	0;
					
					// Delete the strings we allocated for this command
					char	*currentString;
					while((currentString=allStrings.pop()) != NULL)	free(currentString);
				;
    break;}
case 23:
#line 783 "rib.y"
{
					if (callback != NULL) {
						callback(yyvsp[0].string);
					}
				;
    break;}
case 24:
#line 792 "rib.y"
{
					RiDeclare(yyvsp[-1].string,yyvsp[0].string);
				;
    break;}
case 25:
#line 797 "rib.y"
{
					RiFrameBegin(0);
				;
    break;}
case 26:
#line 803 "rib.y"
{
					RiFrameBegin((int) yyvsp[0].real);
				;
    break;}
case 27:
#line 808 "rib.y"
{
					RiFrameEnd();
				;
    break;}
case 28:
#line 813 "rib.y"
{
					RiWorldBegin();
				;
    break;}
case 29:
#line 818 "rib.y"
{
					RiWorldEnd();
				;
    break;}
case 30:
#line 826 "rib.y"
{
					RiFormat((int) yyvsp[-2].real,(int) yyvsp[-1].real,yyvsp[0].real);
				;
    break;}
case 31:
#line 832 "rib.y"
{
					RiFrameAspectRatio(yyvsp[0].real);
				;
    break;}
case 32:
#line 841 "rib.y"
{
					RiScreenWindow(yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real,yyvsp[0].real);
				;
    break;}
case 33:
#line 852 "rib.y"
{
					RiScreenWindow(yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real);
				;
    break;}
case 34:
#line 861 "rib.y"
{
					RiCropWindow(yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real,yyvsp[0].real);
				;
    break;}
case 35:
#line 872 "rib.y"
{
					RiCropWindow(yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real);
				;
    break;}
case 36:
#line 879 "rib.y"
{
					RiProjectionV(yyvsp[-1].string,numParameters,tokens,vals);
				;
    break;}
case 37:
#line 886 "rib.y"
{
					RiClipping(yyvsp[-1].real,yyvsp[0].real);
				;
    break;}
case 38:
#line 897 "rib.y"
{
					RiClippingPlane(yyvsp[-5].real,yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real,yyvsp[0].real);
				;
    break;}
case 39:
#line 905 "rib.y"
{
					RiDepthOfField(yyvsp[-2].real,yyvsp[-1].real,yyvsp[0].real);
				;
    break;}
case 40:
#line 910 "rib.y"
{
					RiDepthOfField(C_INFINITY,1,1);
				;
    break;}
case 41:
#line 917 "rib.y"
{
					RiShutter(yyvsp[-1].real,yyvsp[0].real);
				;
    break;}
case 42:
#line 923 "rib.y"
{
					RiPixelVariance(yyvsp[0].real);
				;
    break;}
case 43:
#line 930 "rib.y"
{
					RiPixelSamples(yyvsp[-1].real,yyvsp[0].real);
				;
    break;}
case 44:
#line 938 "rib.y"
{
					RtFilterFunc	f;

					if ((f = getFilter(yyvsp[-2].string)) != NULL) {
						RiPixelFilter(f,yyvsp[-1].real,yyvsp[0].real);
					}
				;
    break;}
case 45:
#line 949 "rib.y"
{
					RiExposure(yyvsp[-1].real,yyvsp[0].real);
				;
    break;}
case 46:
#line 956 "rib.y"
{
					// No parameter list checking is performed for the shaders
					if (parameterListCheck()) {
						RiImagerV(yyvsp[-1].string,numParameters,tokens,vals);
					}
				;
    break;}
case 47:
#line 969 "rib.y"
{
					RiQuantize(yyvsp[-4].string,(int) yyvsp[-3].real,(int) yyvsp[-2].real,(int) yyvsp[-1].real,yyvsp[0].real);
				;
    break;}
case 48:
#line 978 "rib.y"
{
					RiDisplayV(yyvsp[-3].string,yyvsp[-2].string,yyvsp[-1].string,numParameters,tokens,vals);
				;
    break;}
case 49:
#line 985 "rib.y"
{
					RiDisplayChannelV(yyvsp[-1].string,numParameters,tokens,vals);
				;
    break;}
case 50:
#line 992 "rib.y"
{
					if (parameterListCheck()) {
						RiHiderV(yyvsp[-1].string,numParameters,tokens,vals);
					}
				;
    break;}
case 51:
#line 1000 "rib.y"
{
					if ((floatArgs.numItems & 1) || ((floatArgs.numItems % 6) != 0)) {
						error(CODE_MISSINGDATA,"ColorSamples: Invalid number of arguments (\"%d\") \n",floatArgs.numItems);
					} else {
						int		n		=	floatArgs.numItems/6;
						float	*argf1	=	getFloat(0);
						float	*argf2	=	getFloat(n*3);

						RiColorSamples(n,argf1,argf2);
					}
				;
    break;}
case 52:
#line 1015 "rib.y"
{
					if ((yyvsp[-1].integer != yyvsp[0].integer) || ((floatArgs.numItems % 6) != 0)) {
						error(CODE_MISSINGDATA,"ColorSamples: Invalid number of arguments (\"%d\") \n",floatArgs.numItems);
					} else {
						int		n		=	floatArgs.numItems/6;
						float	*argf1	=	getFloat(0);
						float	*argf2	=	getFloat(n*3);

						RiColorSamples(n,argf1,argf2);
					}
				;
    break;}
case 53:
#line 1029 "rib.y"
{
					RiRelativeDetail(yyvsp[0].real);	
				;
    break;}
case 54:
#line 1036 "rib.y"
{
					if (parameterListCheck()) {
						RiOptionV(yyvsp[-1].string,numParameters,tokens,vals);
					}
				;
    break;}
case 55:
#line 1043 "rib.y"
{
					RiAttributeBegin();
				;
    break;}
case 56:
#line 1048 "rib.y"
{
					RiAttributeEnd();
				;
    break;}
case 57:
#line 1056 "rib.y"
{
					RtColor	color;

					color[0]	=	yyvsp[-2].real;
					color[1]	=	yyvsp[-1].real;
					color[2]	=	yyvsp[0].real;

					RiColor(color);
				;
    break;}
case 58:
#line 1070 "rib.y"
{
					RtColor	color;

					color[0]	=	yyvsp[-2].real;
					color[1]	=	yyvsp[-1].real;
					color[2]	=	yyvsp[0].real;

					RiOpacity(color);
				;
    break;}
case 59:
#line 1086 "rib.y"
{
					RtColor	color;

					color[0]	=	yyvsp[-3].real;
					color[1]	=	yyvsp[-2].real;
					color[2]	=	yyvsp[-1].real;

					RiColor(color);
				;
    break;}
case 60:
#line 1102 "rib.y"
{
					RtColor	color;

					color[0]	=	yyvsp[-3].real;
					color[1]	=	yyvsp[-2].real;
					color[2]	=	yyvsp[-1].real;

					RiOpacity(color);
				;
    break;}
case 61:
#line 1121 "rib.y"
{
					RiTextureCoordinates(yyvsp[-7].real,yyvsp[-6].real,yyvsp[-5].real,yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real,yyvsp[0].real);
				;
    break;}
case 62:
#line 1136 "rib.y"
{
					RiTextureCoordinates(yyvsp[-8].real,yyvsp[-7].real,yyvsp[-6].real,yyvsp[-5].real,yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real);
				;
    break;}
case 63:
#line 1144 "rib.y"
{
					if (lights == NULL)	lights	=	new CArray<RtLightHandle>;

					(*lights)[(int) yyvsp[-1].real]	=	RiLightSourceV(yyvsp[-2].string,numParameters,tokens,vals);
				;
    break;}
case 64:
#line 1154 "rib.y"
{
					if (lightNames == NULL)	lightNames	=	new CTrie<char *>;
					
					char *lName = strdup(yyvsp[-1].string);
					permaStrings->push(lName);
					lightNames->insert(lName,(char *) RiLightSourceV(yyvsp[-2].string,numParameters,tokens,vals));
				;
    break;}
case 65:
#line 1165 "rib.y"
{
					RiLightSourceV(yyvsp[-1].string,numParameters,tokens,vals);
				;
    break;}
case 66:
#line 1173 "rib.y"
{
					if (lights == NULL)	lights	=	new CArray<RtLightHandle>;

					(*lights)[(int) yyvsp[-1].real]	=	RiAreaLightSourceV(yyvsp[-2].string,numParameters,tokens,vals);
				;
    break;}
case 67:
#line 1183 "rib.y"
{
					if (lightNames == NULL)	lightNames	=	new CTrie<char *>;
					
					char *lName = strdup(yyvsp[-1].string);
					permaStrings->push(lName);
					lightNames->insert(lName,(char *) RiLightSourceV(yyvsp[-2].string,numParameters,tokens,vals));
				;
    break;}
case 68:
#line 1194 "rib.y"
{
					if (lights == NULL)	lights	=	new CArray<RtLightHandle>;

					RiIlluminate((*lights)[(int) yyvsp[-1].real],(int) yyvsp[0].real);
				;
    break;}
case 69:
#line 1203 "rib.y"
{
					if (lightNames == NULL)	lightNames	=	new CTrie<char *>;
					
					char	*lightHandle = NULL;
					
					if(lightNames->find(yyvsp[-1].string,lightHandle)){
						RiIlluminate((RtPointer) lightHandle,(int) yyvsp[0].real);
					}
				;
    break;}
case 70:
#line 1216 "rib.y"
{
					RiSurfaceV(yyvsp[-1].string,numParameters,tokens,vals);
				;
    break;}
case 71:
#line 1223 "rib.y"
{
					RiAtmosphereV(yyvsp[-1].string,numParameters,tokens,vals);
				;
    break;}
case 72:
#line 1230 "rib.y"
{
					RiInteriorV(yyvsp[-1].string,numParameters,tokens,vals);
				;
    break;}
case 73:
#line 1237 "rib.y"
{
					RiExteriorV(yyvsp[-1].string,numParameters,tokens,vals);
				;
    break;}
case 74:
#line 1243 "rib.y"
{
					RiShadingRate(yyvsp[0].real);
				;
    break;}
case 75:
#line 1249 "rib.y"
{
					RiShadingInterpolation(yyvsp[0].string);
				;
    break;}
case 76:
#line 1255 "rib.y"
{
					RiMatte((RtBoolean) yyvsp[0].real);
				;
    break;}
case 77:
#line 1268 "rib.y"
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
#line 1288 "rib.y"
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
#line 1310 "rib.y"
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
#line 1330 "rib.y"
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
#line 1348 "rib.y"
{
					RiDetailRange(yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real,yyvsp[0].real);
				;
    break;}
case 82:
#line 1359 "rib.y"
{
					RiDetailRange(yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real);
				;
    break;}
case 83:
#line 1366 "rib.y"
{
					RiGeometricApproximation(yyvsp[-1].string,yyvsp[0].real);
				;
    break;}
case 84:
#line 1372 "rib.y"
{
					RiGeometricRepresentation(yyvsp[0].string);
				;
    break;}
case 85:
#line 1378 "rib.y"
{
					RiOrientation(yyvsp[0].string);
				;
    break;}
case 86:
#line 1383 "rib.y"
{
					RiReverseOrientation();
				;
    break;}
case 87:
#line 1389 "rib.y"
{
					RiSides((int) yyvsp[0].real);
				;
    break;}
case 88:
#line 1394 "rib.y"
{
					RiIdentity();
				;
    break;}
case 89:
#line 1417 "rib.y"
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
#line 1459 "rib.y"
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
#line 1484 "rib.y"
{
					RiPerspective(yyvsp[0].real);
				;
    break;}
case 92:
#line 1492 "rib.y"
{
					RiTranslate(yyvsp[-2].real,yyvsp[-1].real,yyvsp[0].real);
				;
    break;}
case 93:
#line 1500 "rib.y"
{
					RiScale(yyvsp[-2].real,yyvsp[-1].real,yyvsp[0].real);
				;
    break;}
case 94:
#line 1509 "rib.y"
{
					RiRotate(yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real,yyvsp[0].real);
				;
    break;}
case 95:
#line 1521 "rib.y"
{
					RiSkew(yyvsp[-6].real,yyvsp[-5].real,yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real,yyvsp[0].real);
				;
    break;}
case 96:
#line 1535 "rib.y"
{
					RiSkew(yyvsp[-7].real,yyvsp[-6].real,yyvsp[-5].real,yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real);
				;
    break;}
case 97:
#line 1542 "rib.y"
{
					RiDeformationV(yyvsp[-1].string,numParameters,tokens,vals);
				;
    break;}
case 98:
#line 1549 "rib.y"
{
					RiDisplacementV(yyvsp[-1].string,numParameters,tokens,vals);
				;
    break;}
case 99:
#line 1555 "rib.y"
{
					RiCoordinateSystem(yyvsp[0].string);
				;
    break;}
case 100:
#line 1561 "rib.y"
{
					RiCoordSysTransform(yyvsp[0].string);
				;
    break;}
case 101:
#line 1566 "rib.y"
{
					RiTransformBegin();
				;
    break;}
case 102:
#line 1571 "rib.y"
{
					RiTransformEnd();
				;
    break;}
case 103:
#line 1578 "rib.y"
{
					if (parameterListCheck()) {
						RiAttributeV(yyvsp[-1].string,numParameters,tokens,vals);
					}
				;
    break;}
case 104:
#line 1586 "rib.y"
{
					if (parameterListCheck()) {	
						if (sizeCheck(numVertex,0,0,1)) {
							RiPolygonV(numVertex,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 105:
#line 1597 "rib.y"
{
					int		*argi	=	getInt(0);

					if (parameterListCheck()) {
						if (sizeCheck(numVertex,0,0,1)) {
							RiGeneralPolygonV(yyvsp[-1].integer,argi,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 106:
#line 1611 "rib.y"
{
					int	*argi1		=	getInt(0);
					int	*argi2		=	getInt(yyvsp[-2].integer);
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
#line 1648 "rib.y"
{
					int	*argi1		=	getInt(0);
					int	*argi2		=	getInt(yyvsp[-3].integer);
					int	*argi3		=	getInt(yyvsp[-2].integer+yyvsp[-3].integer);
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
#line 1692 "rib.y"
{
					RtBasis	*argf1,*argf2;

					if ((getBasis(&argf1,yyvsp[-3].string)) && (getBasis(&argf2,yyvsp[-1].string))) {
						RiBasis(argf1[0],(int) yyvsp[-2].real, argf2[0],(int) yyvsp[0].real);
					}
				;
    break;}
case 109:
#line 1722 "rib.y"
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
#line 1771 "rib.y"
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
#line 1837 "rib.y"
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
#line 1880 "rib.y"
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
#line 1910 "rib.y"
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
#line 1991 "rib.y"
{
					float	*argf1	=	getFloat(0);
					float	*argf2	=	getFloat(yyvsp[-8].integer);

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
#line 2022 "rib.y"
{
					int		*argi1	=	getInt(0);
					int		*argi2	=	getInt(yyvsp[-8].integer);
					float	*argf3	=	getFloat(0);
					float	*argf4	=	getFloat(yyvsp[-6].integer);
					float	*argf5	=	getFloat(yyvsp[-5].integer+yyvsp[-6].integer);
					int		*argi6	=	getInt(yyvsp[-7].integer+yyvsp[-8].integer);
					float	*argf7	=	getFloat(yyvsp[-4].integer+yyvsp[-5].integer+yyvsp[-6].integer);
					float	*argf8	=	getFloat(yyvsp[-2].integer+yyvsp[-4].integer+yyvsp[-5].integer+yyvsp[-6].integer);
					float	*argf9	=	getFloat(yyvsp[-1].integer+yyvsp[-2].integer+yyvsp[-4].integer+yyvsp[-5].integer+yyvsp[-6].integer);

					RiTrimCurve(yyvsp[-8].integer,argi1,argi2,argf3,argf4,argf5,argi6,argf7,argf8,argf9);
				;
    break;}
case 116:
#line 2042 "rib.y"
{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiSphereV(yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 117:
#line 2058 "rib.y"
{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiSphereV(yyvsp[-5].real,yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 118:
#line 2071 "rib.y"
{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiConeV(yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 119:
#line 2086 "rib.y"
{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiConeV(yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 120:
#line 2100 "rib.y"
{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiCylinderV(yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 121:
#line 2116 "rib.y"
{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiCylinderV(yyvsp[-5].real,yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 122:
#line 2133 "rib.y"
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
#line 2161 "rib.y"
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
#line 2184 "rib.y"
{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiParaboloidV(yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 125:
#line 2200 "rib.y"
{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiParaboloidV(yyvsp[-5].real,yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 126:
#line 2213 "rib.y"
{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiDiskV(yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 127:
#line 2228 "rib.y"
{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiDiskV(yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 128:
#line 2243 "rib.y"
{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiTorusV(yyvsp[-5].real,yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,yyvsp[-1].real,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 129:
#line 2260 "rib.y"
{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiTorusV(yyvsp[-6].real,yyvsp[-5].real,yyvsp[-4].real,yyvsp[-3].real,yyvsp[-2].real,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 130:
#line 2273 "rib.y"
{
					int			*argi1		=	getInt(0);
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
#line 2316 "rib.y"
{
					if (parameterListCheck()) {
						if (sizeCheck(numVertex,0,0,1)) {
							RiPointsV(numVertex,numParameters,tokens,vals);
						}
					}
				;
    break;}
case 132:
#line 2333 "rib.y"
{
					int		*argi1,*argi2,*argi3,*argi4;
					char	**args1;
					float	*argf1;
					int		numVertices,i,j;

					if (parameterListCheck()) {
						argi1	=	getInt(0);
						argi2	=	getInt(yyvsp[-6].integer);
						args1	=	getString(0);
						argi3	=	getInt(yyvsp[-6].integer+yyvsp[-5].integer);
						argi4	=	getInt(yyvsp[-6].integer+yyvsp[-5].integer+yyvsp[-3].integer);
						argf1	=	getFloat(0);

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
#line 2367 "rib.y"
{
					int		*argi1,*argi2;
					int		numVertices,i,j;

					if (parameterListCheck()) {
						argi1	=	getInt(0);
						argi2	=	getInt(yyvsp[-2].integer);

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
#line 2395 "rib.y"
{
					// FIXME: Not implemented
				;
    break;}
case 135:
#line 2402 "rib.y"
{
					if (parameterListCheck()) {
						RiGeometryV(yyvsp[-1].string,numParameters,tokens,vals);
					}
				;
    break;}
case 136:
#line 2419 "rib.y"
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
							arg		=	getString(0);

							cData->generator	=	strdup(arg[0]);

							RiProcedural((RtPointer) cData,bound,RiProcDelayedReadArchive,RiProcFree);
						}
					} else if (strcmp(yyvsp[-9].string,RI_PROCRUNPROGRAM) == 0) {
						if (yyvsp[-8].integer != 2) {
							error(CODE_MISSINGDATA,"Proc delayed archive expects two arguments (given %d)\n",yyvsp[-8].integer);
						} else {
							arg		=	getString(0);

							cData->generator	=	strdup(arg[0]);
							cData->helper		=	strdup(arg[1]);

							RiProcedural((RtPointer) cData,bound,RiProcRunProgram,RiProcFree);
						}
					} else if (strcmp(yyvsp[-9].string,RI_PROCDYNAMICLOAD) == 0) {
						if (yyvsp[-8].integer != 2) {
							error(CODE_MISSINGDATA,"Proc delayed archive expects two arguments (given %d)\n",yyvsp[-8].integer);
						} else {
							arg		=	getString(0);

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
#line 2479 "rib.y"
{
					RiSolidBegin(yyvsp[0].string);
				;
    break;}
case 138:
#line 2484 "rib.y"
{
					RiSolidEnd();
				;
    break;}
case 139:
#line 2490 "rib.y"
{
					if (ribObjects == NULL)	ribObjects	=	new CArray<RtPointer>;

					(*ribObjects)[(int) yyvsp[0].real]	=	RiObjectBegin();
				;
    break;}
case 140:
#line 2497 "rib.y"
{
					RiObjectEnd();
				;
    break;}
case 141:
#line 2503 "rib.y"
{
					if (ribObjects != NULL) {
						RiObjectInstance((*ribObjects)[(int) yyvsp[0].real]);
					} else {
						error(CODE_MISSINGDATA,"Object %d is not found\n",(int) yyvsp[0].real);
					}
				;
    break;}
case 142:
#line 2513 "rib.y"
{
					float	*argf	=	getFloat(0);

					RiMotionBeginV(yyvsp[0].integer,argf);
				;
    break;}
case 143:
#line 2520 "rib.y"
{
					RiMotionEnd();
				;
    break;}
case 144:
#line 2533 "rib.y"
{
					RtFilterFunc	f;

					if ((f		=	getFilter(yyvsp[-3].string)) != NULL)  {
						RiMakeTextureV(yyvsp[-7].string,yyvsp[-6].string,yyvsp[-5].string,yyvsp[-4].string,f,yyvsp[-2].real,yyvsp[-1].real,numParameters,tokens,vals);
					}
				;
    break;}
case 145:
#line 2545 "rib.y"
{
					RiMakeTexture3DV(yyvsp[-2].string,yyvsp[-1].string,numParameters,tokens,vals);
				;
    break;}
case 146:
#line 2558 "rib.y"
{
					RtFilterFunc	f;

					if ((f		=	getFilter(yyvsp[-3].string)) != NULL) {
						RiMakeBumpV(yyvsp[-7].string,yyvsp[-6].string,yyvsp[-5].string,yyvsp[-4].string,f,yyvsp[-2].real,yyvsp[-1].real,numParameters,tokens,vals);
					}
				;
    break;}
case 147:
#line 2573 "rib.y"
{
					RtFilterFunc	f;

					if ((f		=	getFilter(yyvsp[-3].string)) != NULL) {
						RiMakeLatLongEnvironmentV(yyvsp[-5].string,yyvsp[-4].string,f,yyvsp[-2].real,yyvsp[-1].real,numParameters,tokens,vals);
					}
				;
    break;}
case 148:
#line 2594 "rib.y"
{
					RtFilterFunc	f;

					if ((f =	getFilter(yyvsp[-3].string)) != NULL) {
						RiMakeCubeFaceEnvironmentV(yyvsp[-11].string,yyvsp[-10].string,yyvsp[-9].string,yyvsp[-8].string,yyvsp[-7].string,yyvsp[-6].string,yyvsp[-5].string,yyvsp[-4].real,f,yyvsp[-2].real,yyvsp[-1].real,numParameters,tokens,vals);
					}
				;
    break;}
case 149:
#line 2606 "rib.y"
{
					RiMakeShadowV(yyvsp[-2].string,yyvsp[-1].string,numParameters,tokens,vals);
				;
    break;}
case 150:
#line 2613 "rib.y"
{
					RiArchiveBeginV(yyvsp[-1].string,numParameters,tokens,vals);
				;
    break;}
case 151:
#line 2618 "rib.y"
{
					RiArchiveEnd();
				;
    break;}
case 152:
#line 2623 "rib.y"
{
					RiResourceBegin();
				;
    break;}
case 153:
#line 2628 "rib.y"
{
					RiResourceEnd();
				;
    break;}
case 154:
#line 2636 "rib.y"
{
					RiResourceV(yyvsp[-2].string,yyvsp[-1].string,numParameters,tokens,vals);
				;
    break;}
case 155:
#line 2643 "rib.y"
{
					RiIfBeginV(yyvsp[-1].string,numParameters,tokens,vals);
				;
    break;}
case 156:
#line 2648 "rib.y"
{
					RiIfEnd();
				;
    break;}
case 157:
#line 2655 "rib.y"
{
					RiElseIfV(yyvsp[-1].string,numParameters,tokens,vals);
				;
    break;}
case 158:
#line 2660 "rib.y"
{
					RiElse();
				;
    break;}
case 159:
#line 2666 "rib.y"
{
					RtErrorHandler 	e	=	getErrorHandler(yyvsp[0].string);

					if (e != NULL) {
						RiErrorHandler(e);
					}
				;
    break;}
case 160:
#line 2676 "rib.y"
{
				;
    break;}
case 161:
#line 2681 "rib.y"
{
				;
    break;}
case 162:
#line 2685 "rib.y"
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
#line 2692 "rib.y"


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
		lightNames			=	NULL;
		ribObjects			=	NULL;
		callback			=	c;
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
		lightNames			=	savedLightNames;
		lights				=	savedLights;
		ribObjects			=	savedObjects;
		ribLineno			=	savedRibLineno;
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

