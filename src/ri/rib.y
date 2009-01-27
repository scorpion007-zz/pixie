%{
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

%}

%union ribval {
	float	real;
	char	*string;
	int		integer;
}

%{
// Some forward definitions
		int						riblex(ribval*);				// Forward definition for stupid yacc
		void					riberror(const char *,...);

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
	char			*name;			// The name of the object (NULL if not named)
	int				index;			// The index of the object (-1 if named)
} TObject;

static	int					ribDepth						=	0;		// The rib parsing stack depth
static	int					numConstant						=	0;		// The number of constant
static	int					numVertex						=	0;		// The number of vertices
static	int					numVarying						=	0;		// The number of varyings
static	int					numFaceVarying					=	0;		// The number of facevaryings
static	int					numUniform						=	0;		// The number of uniforms
static	TLight				*lights							=	NULL;	// The linked list of light handles
static	TObject				*objects						=	NULL;	// The linked list of object handles
static	void				(*callback)(const char *,...)	=	NULL;	// The callback function for the parser

static	TMemCheckpoint		worldCheckpoint;
static	TMemCheckpoint		memoryCheckpoint;						// We use this to put a checkpoint to the memory
static	CArray<float>		floatArgs;								// The array of float arguments
static	CArray<int>			intArgs;								// The array of integer arguments
static	CArray<const char*>	stringArgs;								// The array of string arguments

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
// Description			:	Count the number of variables in the parameter list
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
						error(CODE_BADTOKEN,"Parameter \"%s\" is not declared\n",par->name);
						return FALSE;
					}
				} else {
					// This isn't a globally declared variable
					// Neither is it an inline delcaration
					error(CODE_BADTOKEN,"Parameter \"%s\" is not declared\n",par->name);
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
			error(CODE_BUG,"Unknown container class in parameter list\n");
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
	} else if (strcmp(name,RI_BESSELFILTER) == 0) {
		f = RiBesselFilter;
	} else if (strcmp(name,RI_DISKFILTER) == 0) {
		f = RiDiskFilter;
	} else {
		error(CODE_BADTOKEN,"Filter \"%s\" is not recognized\n",name);
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
		error(CODE_BADTOKEN,"Error handler \"%s\" is not recognized\n",name);
	}

	return f;
}


%}
%pure-parser
%token	RIB_DECLARE
%token	RIB_FRAME_BEGIN
%token	RIB_FRAME_END
%token	RIB_WORLD_BEGIN
%token	RIB_WORLD_END
%token	RIB_FORMAT
%token	RIB_FRAME_ASPECT_RATIO
%token	RIB_SCREEN_WINDOW
%token	RIB_CROP_WINDOW
%token	RIB_PROJECTION
%token	RIB_CLIPPING
%token	RIB_CLIPPING_PLANE
%token	RIB_DEPTH_OF_FIELD
%token	RIB_SHUTTER
%token	RIB_PIXEL_VARIANCE
%token	RIB_PIXEL_SAMPLES
%token	RIB_PIXEL_FILTER
%token	RIB_EXPOSURE
%token	RIB_IMAGER
%token	RIB_QUANTIZE
%token	RIB_DISPLAY
%token	RIB_DISPLAYCHANNEL
%token	RIB_HIDER
%token	RIB_COLOR_SAMPLES
%token	RIB_RELATIVE_DETAIL
%token	RIB_OPTION
%token	RIB_ATTRIBUTE_BEGIN
%token	RIB_ATTRIBUTE_END
%token	RIB_COLOR
%token	RIB_OPACITY
%token	RIB_TEXTURE_COORDINATES
%token	RIB_LIGHT_SOURCE
%token	RIB_AREA_LIGHT_SOURCE
%token	RIB_ILLUMINATE
%token	RIB_SURFACE
%token	RIB_ATMOSPHERE
%token	RIB_INTERIOR
%token	RIB_EXTERIOR
%token	RIB_SHADING_RATE
%token	RIB_SHADING_INTERPOLATION
%token	RIB_MATTE
%token	RIB_BOUND
%token	RIB_DETAIL
%token	RIB_DETAIL_RANGE
%token	RIB_GEOMETRIC_APPROXIMATION
%token	RIB_GEOMETRIC_REPRESENTATION
%token	RIB_ORIENTATION
%token	RIB_REVERSE_ORIENTATION
%token	RIB_SIDES
%token	RIB_IDENTITY
%token	RIB_TRANSFORM
%token	RIB_CONCAT_TRANSFORM
%token	RIB_PERSPECTIVE
%token	RIB_TRANSLATE
%token	RIB_ROTATE
%token	RIB_SCALE
%token	RIB_SKEW
%token	RIB_DEFORMATION
%token	RIB_DISPLACEMENT
%token	RIB_COORDINATE_SYSTEM
%token	RIB_COORDINATE_SYS_TRANSFORM
%token	RIB_TRANSFORM_BEGIN
%token	RIB_TRANSFORM_END
%token	RIB_ATTRIBUTE
%token	RIB_POLYGON
%token	RIB_GENERAL_POLYGON
%token	RIB_POINTS_POLYGONS
%token	RIB_POINTS_GENERAL_POLYGONS
%token	RIB_BASIS
%token	RIB_PATCH
%token	RIB_PATCH_MESH
%token	RIB_NU_PATCH
%token	RIB_TRIM_CURVE
%token	RIB_SPHERE
%token	RIB_CONE
%token	RIB_CYLINDER
%token	RIB_HYPERBOLOID
%token	RIB_PARABOLOID
%token	RIB_DISK
%token	RIB_TORUS
%token	RIB_CURVES
%token	RIB_GEOMETRY
%token	RIB_POINTS
%token	RIB_SUBDIVISION_MESH
%token	RIB_BLOBBY
%token	RIB_PROCEDURAL
%token	RIB_SOLID_BEGIN
%token	RIB_SOLID_END
%token	RIB_OBJECT_BEGIN
%token	RIB_OBJECT_END
%token	RIB_OBJECT_INSTANCE
%token	RIB_MOTION_BEGIN
%token	RIB_MOTION_END
%token	RIB_MAKE_TEXTURE
%token	RIB_MAKE_BRICKMAP
%token	RIB_MAKE_BUMP
%token	RIB_MAKE_LAT_LONG_ENVIRONMENT
%token	RIB_MAKE_CUBE_FACE_ENVIRONMENT
%token	RIB_MAKE_SHADOW
%token	RIB_ARCHIVE_RECORD
%token	RIB_ARCHIVE_BEGIN
%token	RIB_ARCHIVE_END
%token	RIB_RESOURCE
%token	RIB_RESOURCE_BEGIN
%token	RIB_RESOURCE_END
%token	RIB_IFBEGIN
%token	RIB_IFEND
%token	RIB_ELSEIF
%token	RIB_ELSE
%token	RIB_ERROR_HANDLER
%token	RIB_VERSION
%token	RIB_VERSION_STRING
%token	RIB_ARRAY_BEGIN
%token	RIB_ARRAY_END
%left<string>	RIB_TEXT
%token<real>	RIB_FLOAT
%token<string>	RIB_STRUCTURE_COMMENT
%type<integer>	ribFloats
%type<integer>	ribFloatString
%type<integer>	ribFloatArray
%type<integer>	ribIntString
%type<integer>	ribIntArray
%type<integer>	ribTextString
%type<integer>	ribTextArray
%start			start
%%
start:			ribCommands;


ribIntString:	ribIntString
				RIB_FLOAT
				{
					intArgs.push((int) $2);
					$$	=	$1	+	1;
				}
				|
				RIB_FLOAT
				{
					intArgs.push((int) $1);
					$$	=	1;
				}
				;


ribFloatString:	ribFloatString
				RIB_FLOAT
				{
					floatArgs.push($2);
					$$	=	$1	+	1;
				}
				|
				RIB_FLOAT
				{
					floatArgs.push($1);
					$$	=	1;
				}
				;

ribTextString:	ribTextString
				RIB_TEXT
				{
					stringArgs.push($2);
					$$	=	$1	+	1;
				}
				|
				RIB_TEXT
				{
					stringArgs.push($1);
					$$	=	1;
				}
				;

ribFloatArray:	RIB_ARRAY_BEGIN
				ribFloatString
				RIB_ARRAY_END
				{
					$$ = $2;
				}
				|
				RIB_ARRAY_BEGIN
				RIB_ARRAY_END
				{
					$$ = 0;
				}
				;


ribFloats:		ribFloatArray
				{
					$$	=	$1;
				}
				|
				ribFloatString
				{
					$$	=	$1;
				}
				;

ribIntArray:	RIB_ARRAY_BEGIN
				ribIntString
				RIB_ARRAY_END
				{
					$$ = $2;
				}
				|
				RIB_ARRAY_BEGIN
				RIB_ARRAY_END
				{
					$$ = 0;
				}
				;


ribTextArray:	RIB_ARRAY_BEGIN
				ribTextString
				RIB_ARRAY_END
				{
					$$	=	$2;
				}
				|
				RIB_TEXT
				{
					stringArgs.push($1);
					$$	= 1;
				}
				;



ribPL:			ribParameter
				ribPL
				{
				}
				|
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
				}
				;

ribParameter:	RIB_TEXT
				ribFloats
				{
					// A parameter is either a float array
					parameters[numParameters].name			=	$1;
					parameters[numParameters].type			=	RT_FLOAT;
					parameters[numParameters].numItems		=	$2;
					parameters[numParameters].valuesStart	=	floatArgs.numItems-$2;
					numParameters++;
					paramCheck();
				}
				|
				RIB_TEXT
				ribTextArray
				{	
					// Or a string array
					parameters[numParameters].name			=	$1;
					parameters[numParameters].type			=	RT_TEXT;
					parameters[numParameters].numItems		=	$2;
					parameters[numParameters].valuesStart	=	stringArgs.numItems-$2;
					numParameters++;
					paramCheck();
				}
				;

ribCommands:	ribCommands
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
				}
				ribComm
				{	
				}
				|
				;


ribComm:		RIB_STRUCTURE_COMMENT
				{
					if (callback != NULL) {
						callback($1);
					}
				}
				|
				RIB_DECLARE
				RIB_TEXT
				RIB_TEXT
				{
					RiDeclare($2,$3);
				}
				|
				RIB_FRAME_BEGIN
				{
					RiFrameBegin(0);
				}
				|
				RIB_FRAME_BEGIN
				RIB_FLOAT
				{
					RiFrameBegin((int) $2);
				}
				|
				RIB_FRAME_END
				{
					RiFrameEnd();
				}
				|
				RIB_WORLD_BEGIN
				{
					// Save the checkpoint
					worldCheckpoint		=	memoryCheckpoint;
					
					// Call the worldbegin
					RiWorldBegin();
					
					// Create a new checkpoint because we allocate some stuff in RiWorldBegin
					memSave(memoryCheckpoint,CRenderer::globalMemory);
					
				}
				|
				RIB_WORLD_END
				{
					RiWorldEnd();
					
					// Restore the checkpoint to that before the world begin
					memoryCheckpoint	=	worldCheckpoint;
				}
				|
				RIB_FORMAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				{
					RiFormat((int) $2,(int) $3,$4);
				}
				|
				RIB_FRAME_ASPECT_RATIO
				RIB_FLOAT
				{
					RiFrameAspectRatio($2);
				}
				|
				RIB_SCREEN_WINDOW
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				{
					RiScreenWindow($2,$3,$4,$5);
				}
				|
				RIB_SCREEN_WINDOW
				RIB_ARRAY_BEGIN
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_ARRAY_END
				{
					RiScreenWindow($3,$4,$5,$6);
				}
				|
				RIB_CROP_WINDOW
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				{
					RiCropWindow($2,$3,$4,$5);
				}
				|
				RIB_CROP_WINDOW
				RIB_ARRAY_BEGIN
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_ARRAY_END
				{
					RiCropWindow($3,$4,$5,$6);
				}
				|
				RIB_PROJECTION
				RIB_TEXT
				ribPL
				{
					RiProjectionV($2,numParameters,tokens,vals);
				}
				|
				RIB_CLIPPING
				RIB_FLOAT
				RIB_FLOAT
				{
					RiClipping($2,$3);
				}
				|
				RIB_CLIPPING_PLANE
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				{
					RiClippingPlane($2,$3,$4,$5,$6,$7);
				}
				|
				RIB_DEPTH_OF_FIELD
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				{
					RiDepthOfField($2,$3,$4);
				}
				|
				RIB_DEPTH_OF_FIELD
				{
					RiDepthOfField(C_INFINITY,1,1);
				}
				|
				RIB_SHUTTER
				RIB_FLOAT
				RIB_FLOAT
				{
					RiShutter($2,$3);
				}
				|
				RIB_PIXEL_VARIANCE
				RIB_FLOAT
				{
					RiPixelVariance($2);
				}
				|
				RIB_PIXEL_SAMPLES
				RIB_FLOAT
				RIB_FLOAT
				{
					RiPixelSamples($2,$3);
				}
				|
				RIB_PIXEL_FILTER
				RIB_TEXT
				RIB_FLOAT
				RIB_FLOAT
				{
					RtFilterFunc	f;

					if ((f = getFilter($2)) != NULL) {
						RiPixelFilter(f,$3,$4);
					}
				}
				|
				RIB_EXPOSURE
				RIB_FLOAT
				RIB_FLOAT
				{
					RiExposure($2,$3);
				}
				|
				RIB_IMAGER
				RIB_TEXT
				ribPL
				{
					// No parameter list checking is performed for the shaders
					if (parameterListCheck()) {
						RiImagerV($2,numParameters,tokens,vals);
					}
				}
				|
				RIB_QUANTIZE
				RIB_TEXT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				{
					RiQuantize($2,(int) $3,(int) $4,(int) $5,$6);
				}
				|
				RIB_DISPLAY
				RIB_TEXT
				RIB_TEXT
				RIB_TEXT
				ribPL
				{
					RiDisplayV($2,$3,$4,numParameters,tokens,vals);
				}
				|
				RIB_DISPLAYCHANNEL
				RIB_TEXT
				ribPL
				{
					RiDisplayChannelV($2,numParameters,tokens,vals);
				}
				|
				RIB_HIDER
				RIB_TEXT
				ribPL
				{
					if (parameterListCheck()) {
						RiHiderV($2,numParameters,tokens,vals);
					}
				}
				|
				RIB_COLOR_SAMPLES
				ribFloats
				{
					if ((floatArgs.numItems & 1) || ((floatArgs.numItems % 6) != 0)) {
						error(CODE_MISSINGDATA,"ColorSamples: Invalid number of arguments (\"%d\")\n",floatArgs.numItems);
					} else {
						int		n		=	floatArgs.numItems/6;
						float	*argf1	=	getFloat(0);
						float	*argf2	=	getFloat(n*3);

						RiColorSamples(n,argf1,argf2);
					}
				}
				|
				RIB_COLOR_SAMPLES
				ribFloatArray
				ribFloatArray
				{
					if (($2 != $3) || ((floatArgs.numItems % 6) != 0)) {
						error(CODE_MISSINGDATA,"ColorSamples: Invalid number of arguments (\"%d\")\n",floatArgs.numItems);
					} else {
						int		n		=	floatArgs.numItems/6;
						float	*argf1	=	getFloat(0);
						float	*argf2	=	getFloat(n*3);

						RiColorSamples(n,argf1,argf2);
					}
				}
				|
				RIB_RELATIVE_DETAIL
				RIB_FLOAT
				{
					RiRelativeDetail($2);	
				}
				|
				RIB_OPTION
				RIB_TEXT
				ribPL
				{
					if (parameterListCheck()) {
						RiOptionV($2,numParameters,tokens,vals);
					}
				}
				|
				RIB_ATTRIBUTE_BEGIN
				{
					RiAttributeBegin();
				}
				|
				RIB_ATTRIBUTE_END
				{
					RiAttributeEnd();
				}
				|
				RIB_COLOR
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				{
					RtColor	color;

					color[0]	=	$2;
					color[1]	=	$3;
					color[2]	=	$4;

					RiColor(color);
				}
				|
				RIB_OPACITY
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				{
					RtColor	color;

					color[0]	=	$2;
					color[1]	=	$3;
					color[2]	=	$4;

					RiOpacity(color);
				}
				|
				RIB_COLOR
				RIB_ARRAY_BEGIN
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_ARRAY_END
				{
					RtColor	color;

					color[0]	=	$3;
					color[1]	=	$4;
					color[2]	=	$5;

					RiColor(color);
				}
				|
				RIB_OPACITY
				RIB_ARRAY_BEGIN
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_ARRAY_END
				{
					RtColor	color;

					color[0]	=	$3;
					color[1]	=	$4;
					color[2]	=	$5;

					RiOpacity(color);
				}
				|
				RIB_TEXTURE_COORDINATES
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				{
					RiTextureCoordinates($2,$3,$4,$5,$6,$7,$8,$9);
				}
				|
				RIB_TEXTURE_COORDINATES
				RIB_ARRAY_BEGIN
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_ARRAY_END
				{
					RiTextureCoordinates($3,$4,$5,$6,$7,$8,$9,$10);
				}
				|
				RIB_LIGHT_SOURCE
				RIB_TEXT
				RIB_FLOAT
				ribPL
				{
					TLight	*nLight	=	new TLight;
					nLight->index	=	(int) $3;
					nLight->name	=	NULL;
					nLight->handle	=	RiLightSourceV($2,numParameters,tokens,vals);					
					nLight->next	=	lights;
					lights			=	nLight;
				}
				|
				RIB_LIGHT_SOURCE
				RIB_TEXT
				RIB_TEXT
				ribPL
				{
					TLight	*nLight	=	new TLight;
					nLight->index	=	0;
					nLight->name	=	strdup($3);
					nLight->handle	=	RiLightSourceV($2,numParameters,tokens,vals);					
					nLight->next	=	lights;
					lights			=	nLight;
				}
				|
				RIB_LIGHT_SOURCE
				RIB_TEXT
				ribPL
				{
					RiLightSourceV($2,numParameters,tokens,vals);
				}
				|
				RIB_AREA_LIGHT_SOURCE
				RIB_TEXT
				RIB_FLOAT
				ribPL
				{
					TLight	*nLight	=	new TLight;
					nLight->index	=	(int) $3;
					nLight->name	=	NULL;
					nLight->handle	=	RiAreaLightSourceV($2,numParameters,tokens,vals);					
					nLight->next	=	lights;
					lights			=	nLight;
				}
				|
				RIB_AREA_LIGHT_SOURCE
				RIB_TEXT
				RIB_TEXT
				ribPL
				{
					TLight	*nLight	=	new TLight;
					nLight->index	=	0;
					nLight->name	=	strdup($3);
					nLight->handle	=	RiAreaLightSourceV($2,numParameters,tokens,vals);					
					nLight->next	=	lights;
					lights			=	nLight;
				}
				|
				RIB_ILLUMINATE
				RIB_FLOAT
				RIB_FLOAT
				{
					TLight	*cLight;
					
					for (cLight=lights;cLight!=NULL;cLight=cLight->next)
						if (cLight->index == (int) $2)	break;
						
					if (cLight != NULL) {
						RiIlluminate(cLight->handle,(int) $3);
					} else {
						error(CODE_RANGE,"The light %d is not found",(int) $2);
					}
				}
				|
				RIB_ILLUMINATE
				RIB_TEXT
				RIB_FLOAT
				{
					TLight	*cLight;
					
					for (cLight=lights;cLight!=NULL;cLight=cLight->next)
						if (cLight->name != NULL) {
							if (strcmp(cLight->name,$2) == 0) break;
						}
						
					if (cLight != NULL) {
						RiIlluminate(cLight->handle,(int) $3);
					} else {
						error(CODE_RANGE,"The light \"%s\" is not found",$2);
					}
				}
				|
				RIB_SURFACE
				RIB_TEXT
				ribPL
				{
					RiSurfaceV($2,numParameters,tokens,vals);
				}
				|
				RIB_ATMOSPHERE
				RIB_TEXT
				ribPL
				{
					RiAtmosphereV($2,numParameters,tokens,vals);
				}
				|
				RIB_INTERIOR
				RIB_TEXT
				ribPL
				{
					RiInteriorV($2,numParameters,tokens,vals);
				}
				|
				RIB_EXTERIOR
				RIB_TEXT
				ribPL
				{
					RiExteriorV($2,numParameters,tokens,vals);
				}
				|
				RIB_SHADING_RATE
				RIB_FLOAT
				{
					RiShadingRate($2);
				}
				|
				RIB_SHADING_INTERPOLATION
				RIB_TEXT
				{
					RiShadingInterpolation($2);
				}
				|
				RIB_MATTE
				RIB_FLOAT
				{
					RiMatte((RtBoolean) $2);
				}
				|
				RIB_BOUND
				RIB_ARRAY_BEGIN
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_ARRAY_END
				{
					RtBound	bound;

					bound[0]	=	$3;
					bound[1]	=	$4;
					bound[2]	=	$5;
					bound[3]	=	$6;
					bound[4]	=	$7;
					bound[5]	=	$8;

					RiBound(bound);
				}
				|
				RIB_BOUND
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				{
					RtBound	bound;

					bound[0]	=	$2;
					bound[1]	=	$3;
					bound[2]	=	$4;
					bound[3]	=	$5;
					bound[4]	=	$6;
					bound[5]	=	$7;

					RiBound(bound);
				}
				|
				RIB_DETAIL
				RIB_ARRAY_BEGIN
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_ARRAY_END
				{
					RtBound	bound;

					bound[0]	=	$3;
					bound[1]	=	$4;
					bound[2]	=	$5;
					bound[3]	=	$6;
					bound[4]	=	$7;
					bound[5]	=	$8;

					RiDetail(bound);
				}
				|
				RIB_DETAIL
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				{
					RtBound	bound;

					bound[0]	=	$2;
					bound[1]	=	$3;
					bound[2]	=	$4;
					bound[3]	=	$5;
					bound[4]	=	$6;
					bound[5]	=	$7;

					RiDetail(bound);
				}
				|
				RIB_DETAIL_RANGE
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				{
					RiDetailRange($2,$3,$4,$5);
				}
				|
				RIB_DETAIL_RANGE
				RIB_ARRAY_BEGIN
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_ARRAY_END
				{
					RiDetailRange($3,$4,$5,$6);
				}
				|
				RIB_GEOMETRIC_APPROXIMATION
				RIB_TEXT
				RIB_FLOAT
				{
					RiGeometricApproximation($2,$3);
				}
				|
				RIB_GEOMETRIC_REPRESENTATION
				RIB_TEXT
				{
					RiGeometricRepresentation($2);
				}
				|
				RIB_ORIENTATION
				RIB_TEXT
				{
					RiOrientation($2);
				}
				|
				RIB_REVERSE_ORIENTATION
				{
					RiReverseOrientation();
				}
				|
				RIB_SIDES
				RIB_FLOAT
				{
					RiSides((int) $2);
				}
				|
				RIB_IDENTITY
				{
					RiIdentity();
				}
				|
				RIB_TRANSFORM
				RIB_ARRAY_BEGIN
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_ARRAY_END
				{
					RtMatrix	tmp;

					tmp[0][0]	=	$3;
					tmp[0][1]	=	$4;
					tmp[0][2]	=	$5;
					tmp[0][3]	=	$6;
					tmp[1][0]	=	$7;
					tmp[1][1]	=	$8;
					tmp[1][2]	=	$9;
					tmp[1][3]	=	$10;
					tmp[2][0]	=	$11;
					tmp[2][1]	=	$12;
					tmp[2][2]	=	$13;
					tmp[2][3]	=	$14;
					tmp[3][0]	=	$15;
					tmp[3][1]	=	$16;
					tmp[3][2]	=	$17;
					tmp[3][3]	=	$18;

					RiTransform(tmp);
				}
				|
				RIB_CONCAT_TRANSFORM
				RIB_ARRAY_BEGIN
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_ARRAY_END
				{
					RtMatrix	tmp;

					tmp[0][0]	=	$3;
					tmp[0][1]	=	$4	;
					tmp[0][2]	=	$5;
					tmp[0][3]	=	$6;
					tmp[1][0]	=	$7;
					tmp[1][1]	=	$8;
					tmp[1][2]	=	$9;
					tmp[1][3]	=	$10;
					tmp[2][0]	=	$11;
					tmp[2][1]	=	$12;
					tmp[2][2]	=	$13;
					tmp[2][3]	=	$14;
					tmp[3][0]	=	$15;
					tmp[3][1]	=	$16;
					tmp[3][2]	=	$17;
					tmp[3][3]	=	$18;

					RiConcatTransform(tmp);
				}
				|
				RIB_PERSPECTIVE
				RIB_FLOAT
				{
					RiPerspective($2);
				}
				|
				RIB_TRANSLATE
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				{
					RiTranslate($2,$3,$4);
				}
				|
				RIB_SCALE
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				{
					RiScale($2,$3,$4);
				}
				|
				RIB_ROTATE
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				{
					RiRotate($2,$3,$4,$5);
				}
				|
				RIB_SKEW
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				{
					RiSkew($2,$3,$4,$5,$6,$7,$8);
				}
				|
				RIB_SKEW
				RIB_ARRAY_BEGIN
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_ARRAY_END
				{
					RiSkew($3,$4,$5,$6,$7,$8,$9);
				}
				|
				RIB_DEFORMATION
				RIB_TEXT
				ribPL
				{
					RiDeformationV($2,numParameters,tokens,vals);
				}
				|
				RIB_DISPLACEMENT
				RIB_TEXT
				ribPL
				{
					RiDisplacementV($2,numParameters,tokens,vals);
				}
				|
				RIB_COORDINATE_SYSTEM
				RIB_TEXT
				{
					RiCoordinateSystem($2);
				}
				|
				RIB_COORDINATE_SYS_TRANSFORM
				RIB_TEXT
				{
					RiCoordSysTransform($2);
				}
				|
				RIB_TRANSFORM_BEGIN
				{
					RiTransformBegin();
				}
				|
				RIB_TRANSFORM_END
				{
					RiTransformEnd();
				}
				|
				RIB_ATTRIBUTE
				RIB_TEXT
				ribPL
				{
					if (parameterListCheck()) {
						RiAttributeV($2,numParameters,tokens,vals);
					}
				}
				|
				RIB_POLYGON
				ribPL
				{
					if (parameterListCheck()) {	
						if (sizeCheck(numVertex,0,0,1)) {
							RiPolygonV(numVertex,numParameters,tokens,vals);
						}
					}
				}
				|
				RIB_GENERAL_POLYGON
				ribIntArray
				ribPL
				{
					int		*argi	=	getInt(0);

					if (parameterListCheck()) {
						if (sizeCheck(numVertex,0,0,1)) {
							RiGeneralPolygonV($2,argi,numParameters,tokens,vals);
						}
					}
				}
				|
				RIB_POINTS_POLYGONS
				ribIntArray
				ribIntArray
				ribPL
				{
					int	*argi1		=	getInt(0);
					int	*argi2		=	getInt($2);
					int	nvertices	=	0;
					int	i;
					int	maxVertex	=	0;


					// Find out how many items are in verts array
					for (i=0;i<$2;i++) {
						nvertices	+=	argi1[i];
					}

					if (nvertices != $3) {
						error(CODE_MISSINGDATA,"Vertex count mismatch (%d != %d)\n",nvertices,$3);
					} else {
						// Find out the number of vertices required
						for (i=0,maxVertex=0;i<nvertices;i++) {
							if (argi2[i] > maxVertex)
								maxVertex	=	argi2[i];
						}

						maxVertex++;

						if (parameterListCheck()) {
							if (sizeCheck(maxVertex,0,nvertices,$2)) {
								RiPointsPolygonsV($2,argi1,argi2,numParameters,tokens,vals);
							}
						}
					}
				}
				|
				RIB_POINTS_GENERAL_POLYGONS
				ribIntArray
				ribIntArray
				ribIntArray
				ribPL
				{
					int	*argi1		=	getInt(0);
					int	*argi2		=	getInt($2);
					int	*argi3		=	getInt($3+$2);
					int	numvertices	=	0;
					int	numloops	=	0;
					int	maxVertex	=	0;
					int	i;

					for (i=0;i<$2;i++) {
						numloops	+=	argi1[i];
					}

					if (numloops != $3) {
						error(CODE_MISSINGDATA,"Loop count mismatch (%d != %d)\n",numloops,$3);
					} else {
						for (i=0;i<$3;i++) {
							numvertices	+=	argi2[i];
						}

						if (numvertices != $4) {
							error(CODE_MISSINGDATA,"Vertex count mismatch (%d != %d)\n",numvertices,$4);
						} else {
							for (i=0;i<numvertices;i++) {
								if (argi3[i] > maxVertex)
									maxVertex	=	argi3[i];
							}

							maxVertex++;

							if (parameterListCheck()) {
								if (sizeCheck(maxVertex,0,numvertices,$2)) {
									RiPointsGeneralPolygonsV($2,argi1,argi2,argi3,numParameters,tokens,vals);
								}
							}
						}
					}
				}
				|
				RIB_BASIS
				RIB_TEXT
				RIB_FLOAT
				RIB_TEXT
				RIB_FLOAT
				{
					RtBasis	*argf1,*argf2;

					if ((getBasis(&argf1,$2)) && (getBasis(&argf2,$4))) {
						RiBasis(argf1[0],(int) $3, argf2[0],(int) $5);
					}
				}
				|
				RIB_BASIS
				RIB_ARRAY_BEGIN
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_ARRAY_END				
				RIB_FLOAT
				RIB_TEXT
				RIB_FLOAT
				{
					RtBasis	*argf2;

					if (getBasis(&argf2,$21)) {
						RtBasis	tmp;
					
						tmp[0][0]	=	$3;
						tmp[0][1]	=	$4;
						tmp[0][2]	=	$5;
						tmp[0][3]	=	$6;
						tmp[1][0]	=	$7;
						tmp[1][1]	=	$8;
						tmp[1][2]	=	$9;
						tmp[1][3]	=	$10;
						tmp[2][0]	=	$11;
						tmp[2][1]	=	$12;
						tmp[2][2]	=	$13;
						tmp[2][3]	=	$14;
						tmp[3][0]	=	$15;
						tmp[3][1]	=	$16;
						tmp[3][2]	=	$17;
						tmp[3][3]	=	$18;
										
						RiBasis(tmp,(int) $20,argf2[0],(int) $22);
					}
				}
				|
				RIB_BASIS
				RIB_TEXT
				RIB_FLOAT
				RIB_ARRAY_BEGIN
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_ARRAY_END
				RIB_FLOAT
				{
					RtBasis	*argf1;

					if (getBasis(&argf1,$2)) {
						RtBasis	tmp;
					
						tmp[0][0]	=	$5;
						tmp[0][1]	=	$6;
						tmp[0][2]	=	$7;
						tmp[0][3]	=	$8;
						tmp[1][0]	=	$9;
						tmp[1][1]	=	$10;
						tmp[1][2]	=	$11;
						tmp[1][3]	=	$12;
						tmp[2][0]	=	$13;
						tmp[2][1]	=	$14;
						tmp[2][2]	=	$15;
						tmp[2][3]	=	$16;
						tmp[3][0]	=	$17;
						tmp[3][1]	=	$18;
						tmp[3][2]	=	$19;
						tmp[3][3]	=	$20;

						RiBasis(argf1[0],(int) $3,tmp,(int) $22);
					}
				}
				|
				RIB_BASIS
				RIB_ARRAY_BEGIN
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_ARRAY_END
				RIB_FLOAT
				RIB_ARRAY_BEGIN
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_ARRAY_END
				RIB_FLOAT
				{
					RtBasis	b1,b2;

					b1[0][0]	=	$3;
					b1[0][1]	=	$4;
					b1[0][2]	=	$5;
					b1[0][3]	=	$6;
					b1[1][0]	=	$7;
					b1[1][1]	=	$8;
					b1[1][2]	=	$9;
					b1[1][3]	=	$10;
					b1[2][0]	=	$11;
					b1[2][1]	=	$12;
					b1[2][2]	=	$13;
					b1[2][3]	=	$14;
					b1[3][0]	=	$15;
					b1[3][1]	=	$16;
					b1[3][2]	=	$17;
					b1[3][3]	=	$18;

					b2[0][0]	=	$22;
					b2[0][1]	=	$23;
					b2[0][2]	=	$24;
					b2[0][3]	=	$25;
					b2[1][0]	=	$26;
					b2[1][1]	=	$27;
					b2[1][2]	=	$28;
					b2[1][3]	=	$29;
					b2[2][0]	=	$30;
					b2[2][1]	=	$31;
					b2[2][2]	=	$32;
					b2[2][3]	=	$33;
					b2[3][0]	=	$34;
					b2[3][1]	=	$35;
					b2[3][2]	=	$36;
					b2[3][3]	=	$37;

					RiBasis(b1,(int) $20,b2,(int) $39);
				}
				|
				RIB_PATCH
				RIB_TEXT
				ribPL
				{
					int	numExpectedVertices;
					int	numExpectedPatches	=	1;


					if (strcmp($2,RI_BILINEAR) == 0) {
						numExpectedVertices	=	4;
					} else if (strcmp($2,RI_BICUBIC) == 0) {
						numExpectedVertices	=	16;
					} else {
						error(CODE_BADTOKEN,"Unknown patch type: \"%s\"\n",$2);
						numExpectedVertices	=	0;
					}

					if (numExpectedVertices > 0) {
						if (parameterListCheck()) {
							if (sizeCheck(numExpectedVertices,4,4,1)) {
								RiPatchV($2,numParameters,tokens,vals);
							}
						}
					}
				}
				|
				RIB_PATCH_MESH
				RIB_TEXT
				RIB_FLOAT
				RIB_TEXT
				RIB_FLOAT
				RIB_TEXT
				ribPL
				{
					int	numExpectedVertices;
					int	numuPatches,numvPatches;
					int	nu	=	(int) $3;
					int	nv	=	(int) $5;
					CAttributes	*attributes	=	CRenderer::context->getAttributes(FALSE);
					int	uw,vw;
					int	numVaryings;

					if (strcmp($4,RI_PERIODIC) == 0) {
						uw	=	TRUE;
					} else {
						uw	=	FALSE;
					}

					if (strcmp($6,RI_PERIODIC) == 0) {
						vw	=	TRUE;
					} else {
						vw	=	FALSE;
					}

					if (strcmp($2,RI_BILINEAR) == 0) {
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
					} else if (strcmp($2,RI_BICUBIC) == 0) {
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
						error(CODE_BADTOKEN,"Unknown patch type: \"%s\"\n",$2);
						numExpectedVertices	=	0;
					}

					if (numExpectedVertices > 0) {
						if (parameterListCheck()) {
							if (sizeCheck(numExpectedVertices,numVaryings,numuPatches*numvPatches*4,numuPatches*numvPatches)) {
								RiPatchMeshV($2,(int) $3,$4,(int) $5,$6,numParameters,tokens,vals);
							}
						}
					}
				}
				|
				RIB_NU_PATCH
				RIB_FLOAT
				RIB_FLOAT
				ribFloatArray
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				ribFloatArray
				RIB_FLOAT
				RIB_FLOAT
				ribPL
				{
					float	*argf1	=	getFloat(0);
					float	*argf2	=	getFloat($4);

					int		uPoints	=	(int) $2;
					int		uOrder	=	(int) $3;
					int		vPoints	=	(int) $7;
					int		vOrder	=	(int) $8;

					int		uPatches	=	uPoints - uOrder+1;
					int		vPatches	=	vPoints - vOrder+1;

					int		numExpectedVertices	=	uPoints*vPoints;

					if (parameterListCheck()) {
						if (sizeCheck(numExpectedVertices,(uPoints-uOrder+2)*(vPoints-vOrder+2),uPatches*vPatches*4,uPatches*vPatches)) {
							RiNuPatchV((int) $2,(int) $3,argf1,$5,$6,(int) $7,(int) $8,argf2,$10,$11,numParameters,tokens,vals);
						}
					}
				}
				|
				RIB_TRIM_CURVE
				ribIntArray
				ribIntArray
				ribFloatArray
				ribFloatArray
				ribFloatArray
				ribIntArray
				ribFloatArray
				ribFloatArray
				ribFloatArray
				{
					int		*argi1	=	getInt(0);
					int		*argi2	=	getInt($2);
					float	*argf3	=	getFloat(0);
					float	*argf4	=	getFloat($4);
					float	*argf5	=	getFloat($5+$4);
					int		*argi6	=	getInt($3+$2);
					float	*argf7	=	getFloat($6+$5+$4);
					float	*argf8	=	getFloat($8+$6+$5+$4);
					float	*argf9	=	getFloat($9+$8+$6+$5+$4);

					RiTrimCurve($2,argi1,argi2,argf3,argf4,argf5,argi6,argf7,argf8,argf9);
				}
				|
				RIB_SPHERE
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				ribPL
				{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiSphereV($2,$3,$4,$5,numParameters,tokens,vals);
						}
					}
				}
				|
				RIB_SPHERE
				RIB_ARRAY_BEGIN
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_ARRAY_END
				ribPL
				{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiSphereV($3,$4,$5,$6,numParameters,tokens,vals);
						}
					}
				}
				|
				RIB_CONE
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				ribPL
				{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiConeV($2,$3,$4,numParameters,tokens,vals);
						}
					}
				}
				|
				RIB_CONE
				RIB_ARRAY_BEGIN
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_ARRAY_END
				ribPL
				{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiConeV($3,$4,$5,numParameters,tokens,vals);
						}
					}
				}
				|
				RIB_CYLINDER
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				ribPL
				{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiCylinderV($2,$3,$4,$5,numParameters,tokens,vals);
						}
					}
				}
				|
				RIB_CYLINDER
				RIB_ARRAY_BEGIN
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_ARRAY_END
				ribPL
				{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiCylinderV($3,$4,$5,$6,numParameters,tokens,vals);
						}
					}
				}
				|
				RIB_HYPERBOLOID
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				ribPL
				{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RtPoint	p1,p2;

							p1[0]	=	$2;
							p1[1]	=	$3;
							p1[2]	=	$4;
							p2[0]	=	$5;
							p2[1]	=	$6;
							p2[2]	=	$7;

							RiHyperboloidV(p1,p2,$8,numParameters,tokens,vals);
						}
					}
				}
				|
				RIB_HYPERBOLOID
				RIB_ARRAY_BEGIN
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_ARRAY_END
				ribPL
				{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RtPoint	p1,p2;

							p1[0]	=	$3;
							p1[1]	=	$4;
							p1[2]	=	$5;
							p2[0]	=	$6;
							p2[1]	=	$7;
							p2[2]	=	$8;

							RiHyperboloidV(p1,p2,$9,numParameters,tokens,vals);
						}
					}
				}
				|
				RIB_PARABOLOID
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				ribPL
				{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiParaboloidV($2,$3,$4,$5,numParameters,tokens,vals);
						}
					}
				}
				|
				RIB_PARABOLOID
				RIB_ARRAY_BEGIN
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_ARRAY_END
				ribPL
				{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiParaboloidV($3,$4,$5,$6,numParameters,tokens,vals);
						}
					}
				}
				|
				RIB_DISK
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				ribPL
				{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiDiskV($2,$3,$4,numParameters,tokens,vals);
						}
					}
				}
				|
				RIB_DISK
				RIB_ARRAY_BEGIN
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_ARRAY_END
				ribPL
				{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiDiskV($3,$4,$5,numParameters,tokens,vals);
						}
					}
				}
				|
				RIB_TORUS
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				ribPL
				{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiTorusV($2,$3,$4,$5,$6,numParameters,tokens,vals);
						}
					}
				}
				|
				RIB_TORUS
				RIB_ARRAY_BEGIN
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_ARRAY_END
				ribPL
				{
					if (parameterListCheck()) {
						if (sizeCheck(0,4,4,1)) {
							RiTorusV($3,$4,$5,$6,$7,numParameters,tokens,vals);
						}
					}
				}
				|
				RIB_CURVES
				RIB_TEXT
				ribIntArray
				RIB_TEXT
				ribPL
				{
					int			*argi1		=	getInt(0);
					int			numVertices,numUniforms;
					CAttributes	*attributes	=	CRenderer::context->getAttributes(FALSE);
					int			wrap;
					int			numVaryings,i;

					if (strcmp($4,RI_PERIODIC) == 0) {
						wrap	=	TRUE;
					} else {
						wrap	=	FALSE;
					}

					if (strcmp($2,RI_LINEAR) == 0) {
						for (i=0,numVertices=0;i<$3;i++) {
							numVertices	+=	argi1[i];
						}

						numVaryings		=	numVertices;
						numUniforms		=	$3;
					} else if (strcmp($2,RI_CUBIC) == 0) {
						for (i=0,numVertices=0,numVaryings=0,numUniforms=0;i<$3;i++) {
							int	j		=	(argi1[i] - 4) / attributes->vStep + 1;
							numVertices	+=	argi1[i];
							numVaryings	+=	j + (1 - wrap);
						}
						numUniforms		=	$3;
					} else {
						error(CODE_BADTOKEN,"Unknown patch type: \"%s\"\n",$2);
						numVertices	=	0;
					}

					if (numVertices > 0) {
						if (parameterListCheck()) {
							if (sizeCheck(numVertices,numVaryings,0,numUniforms)) {
								RiCurvesV($2,$3,argi1,$4,numParameters,tokens,vals);
							}
						}
					}
				}
				|
				RIB_POINTS
				ribPL
				{
					if (parameterListCheck()) {
						if (sizeCheck(numVertex,0,0,1)) {
							RiPointsV(numVertex,numParameters,tokens,vals);
						}
					}
				}
				|
				RIB_SUBDIVISION_MESH
				RIB_TEXT
				ribIntArray
				ribIntArray
				ribTextArray
				ribIntArray
				ribIntArray
				ribFloatArray
				ribPL
				{
					int			*argi1,*argi2,*argi3,*argi4;
					const char	**args1;
					float		*argf1;
					int			numVertices,i,j;

					if (parameterListCheck()) {
						argi1	=	getInt(0);
						argi2	=	getInt($3);
						args1	=	getString(0);
						argi3	=	getInt($3+$4);
						argi4	=	getInt($3+$4+$6);
						argf1	=	getFloat(0);

						// Count the number of faces / vertices
						for (i=0,j=0;i<$3;j+=argi1[i],i++);

						for (numVertices=-1,i=0;i<j;i++) {
							if (argi2[i] > numVertices)	numVertices	=	argi2[i];
						}
						numVertices++;


						if (sizeCheck(numVertices,numVertices,j,$3)) {
							RiSubdivisionMeshV($2,$3,argi1,argi2,$5,args1,argi3,argi4,argf1,numParameters,tokens,vals);
						}
					}
				}
				|
				RIB_SUBDIVISION_MESH
				RIB_TEXT
				ribIntArray
				ribIntArray
				ribIntArray
				ribIntArray
				ribIntArray
				ribFloatArray
				ribPL
				{
					// Support for no tags (parsed as int array for arg 5)
					int			*argi1,*argi2,*argi3,*argi4;
					const char	**args1;
					float		*argf1;
					int			numVertices,i,j;

					if (parameterListCheck()) {
						argi1	=	getInt(0);
						argi2	=	getInt($3);
						args1	=	getString(0);
						argi3	=	getInt($3+$4);
						argi4	=	getInt($3+$4+$6);
						argf1	=	getFloat(0);

						if ($5 == 0) {
							// Count the number of faces / vertices
							for (i=0,j=0;i<$3;j+=argi1[i],i++);

							for (numVertices=-1,i=0;i<j;i++) {
								if (argi2[i] > numVertices)	numVertices	=	argi2[i];
							}
							numVertices++;


							if (sizeCheck(numVertices,numVertices,j,$3)) {
								RiSubdivisionMeshV($2,$3,argi1,argi2,0,args1,argi3,argi4,argf1,numParameters,tokens,vals);
							}
						} else {
							error(CODE_BADTOKEN,"Subdivision surface expected string array (tags) for argument 5\n");
						}
					}
				}
				/* REMOVED for non-standard
				|
				RIB_SUBDIVISION_MESH
				RIB_TEXT
				ribIntArray
				ribIntArray
				ribPL
				{
					int		*argi1,*argi2;
					int		numVertices,i,j;

					if (parameterListCheck()) {
						argi1	=	getInt(0);
						argi2	=	getInt($3);

						// Count the number of faces / vertices
						for (i=0,j=0;i<$3;j+=argi1[i],i++);

						for (numVertices=-1,i=0;i<j;i++) {
							if (argi2[i] > numVertices)	numVertices	=	argi2[i];
						}
						numVertices++;


						if (sizeCheck(numVertices,numVertices,j,$3)) {
							RiSubdivisionMeshV($2,$3,argi1,argi2,0,NULL,NULL,NULL,NULL,numParameters,tokens,vals);
						}
					}
				}
				*/
				|
				RIB_BLOBBY
				RIB_FLOAT
				ribIntArray
				ribFloatArray
				ribPL
				{
					// FIXME: Not implemented
				}
				|
				RIB_BLOBBY
				RIB_FLOAT
				ribIntArray
				ribFloatArray
				ribTextArray
				ribPL
				{
					// FIXME: Not implemented
				}
				|
				RIB_GEOMETRY
				RIB_TEXT
				ribPL
				{
					if (parameterListCheck()) {
						RiGeometryV($2,numParameters,tokens,vals);
					}
				}
				|
				RIB_PROCEDURAL
				RIB_TEXT
				ribTextArray
				RIB_ARRAY_BEGIN
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_FLOAT
				RIB_ARRAY_END
				{
					RtBound			bound;
					CDelayedData	*cData	=	new CDelayedData;
					const char		**arg;

					bound[0]	=	$5;
					bound[1]	=	$6;
					bound[2]	=	$7;
					bound[3]	=	$8;
					bound[4]	=	$9;
					bound[5]	=	$10;

					cData->bmin[COMP_X]	=	$5;
					cData->bmax[COMP_X]	=	$6;
					
					cData->bmin[COMP_Y]	=	$7;
					cData->bmax[COMP_Y]	=	$8;
					
					cData->bmin[COMP_Z]	=	$9;
					cData->bmax[COMP_Z]	=	$10;

					if (strcmp($2,RI_PROCDELAYEDREADARCHIVE) == 0) {
						if ($3 != 1) {
							error(CODE_MISSINGDATA,"Procedure delayed archive expects one argument (given %d)\n",$3);
						} else {
							arg		=	getString(0);

							cData->generator	=	strdup(arg[0]);

							RiProcedural(cData,bound,RiProcDelayedReadArchive,RiProcFree);
						}
					} else if (strcmp($2,RI_PROCRUNPROGRAM) == 0) {
						if ($3 != 2) {
							error(CODE_MISSINGDATA,"Procedure run program expects two arguments (given %d)\n",$3);
						} else {
							arg		=	getString(0);

							cData->generator	=	strdup(arg[0]);
							cData->helper		=	strdup(arg[1]);

							RiProcedural(cData,bound,RiProcRunProgram,RiProcFree);
						}
					} else if (strcmp($2,RI_PROCDYNAMICLOAD) == 0) {
						if ($3 != 2) {
							error(CODE_MISSINGDATA,"Procedure dynamic load expects two arguments (given %d)\n",$3);
						} else {
							arg		=	getString(0);

							cData->generator	=	strdup(arg[0]);
							cData->helper		=	strdup(arg[1]);

							RiProcedural(cData,bound,RiProcDynamicLoad,RiProcFree);
						}
					} else {
						error(CODE_BADTOKEN,"Unknown procedural: %s\n",$2);
						delete cData;
					}
				}
				|
				RIB_SOLID_BEGIN
				RIB_TEXT
				{
					RiSolidBegin($2);
				}
				|
				RIB_SOLID_END
				{
					RiSolidEnd();
				}
				|
				RIB_OBJECT_BEGIN
				RIB_FLOAT
				{
					TObject	*nObject	=	new TObject;
					
					nObject->handle		=	RiObjectBegin();
					nObject->index		=	(int) $2;
					nObject->name		=	NULL;
					nObject->next		=	objects;
					objects				=	nObject;
				}
				|
				RIB_OBJECT_BEGIN
				RIB_TEXT
				{
					TObject	*nObject	=	new TObject;
					
					nObject->handle		=	RiObjectBegin();
					nObject->index		=	-1;
					nObject->name		=	strdup($2);
					nObject->next		=	objects;
					objects				=	nObject;
				}
				|
				RIB_OBJECT_END
				{
					RiObjectEnd();
				}
				|
				RIB_OBJECT_INSTANCE
				RIB_FLOAT
				{
					TObject	*cObject;
					
					for (cObject=objects;cObject!=NULL;cObject=cObject->next) {
						if (cObject->index == (int) $2)	break;
					}
					
					if (cObject != NULL) {
						RiObjectInstance(cObject->handle);
					} else {
						error(CODE_MISSINGDATA,"Object %d is not found\n",(int) $2);
					}
				}
				|
				RIB_OBJECT_INSTANCE
				RIB_TEXT
				{
					TObject	*cObject;
					
					for (cObject=objects;cObject!=NULL;cObject=cObject->next) {
						if (strcmp(cObject->name,$2) == 0)	break;
					}
					
					if (cObject != NULL) {
						RiObjectInstance(cObject->handle);
					} else {
						error(CODE_MISSINGDATA,"Object \"%s\" is not found\n",$2);
					}
				}
				|
				RIB_MOTION_BEGIN
				ribFloats
				{
					float	*argf	=	getFloat(0);

					RiMotionBeginV($2,argf);
				}
				|
				RIB_MOTION_END
				{
					RiMotionEnd();
				}
				|
				RIB_MAKE_TEXTURE
				RIB_TEXT
				RIB_TEXT
				RIB_TEXT
				RIB_TEXT
				RIB_TEXT
				RIB_FLOAT
				RIB_FLOAT
				ribPL
				{
					RtFilterFunc	f;

					if ((f		=	getFilter($6)) != NULL)  {
						RiMakeTextureV($2,$3,$4,$5,f,$7,$8,numParameters,tokens,vals);
					}
				}
				|
				RIB_MAKE_BRICKMAP
				ribTextArray
				RIB_TEXT
				ribPL
				{
					RiMakeBrickMapV($2,getString(0),$3,numParameters,tokens,vals);
				}
				|
				RIB_MAKE_BUMP
				RIB_TEXT
				RIB_TEXT
				RIB_TEXT
				RIB_TEXT
				RIB_TEXT
				RIB_FLOAT
				RIB_FLOAT
				ribPL
				{
					RtFilterFunc	f;

					if ((f		=	getFilter($6)) != NULL) {
						RiMakeBumpV($2,$3,$4,$5,f,$7,$8,numParameters,tokens,vals);
					}
				}
				|
				RIB_MAKE_LAT_LONG_ENVIRONMENT
				RIB_TEXT
				RIB_TEXT
				RIB_TEXT
				RIB_FLOAT
				RIB_FLOAT
				ribPL
				{
					RtFilterFunc	f;

					if ((f		=	getFilter($4)) != NULL) {
						RiMakeLatLongEnvironmentV($2,$3,f,$5,$6,numParameters,tokens,vals);
					}
				}
				|
				RIB_MAKE_CUBE_FACE_ENVIRONMENT
				RIB_TEXT
				RIB_TEXT
				RIB_TEXT
				RIB_TEXT
				RIB_TEXT
				RIB_TEXT
				RIB_TEXT
				RIB_FLOAT
				RIB_TEXT
				RIB_FLOAT
				RIB_FLOAT
				ribPL
				{
					RtFilterFunc	f;

					if ((f =	getFilter($10)) != NULL) {
						RiMakeCubeFaceEnvironmentV($2,$3,$4,$5,$6,$7,$8,$9,f,$11,$12,numParameters,tokens,vals);
					}
				}
				|
				RIB_MAKE_SHADOW
				RIB_TEXT
				RIB_TEXT
				ribPL
				{
					RiMakeShadowV($2,$3,numParameters,tokens,vals);
				}
				|
				RIB_ARCHIVE_BEGIN
				RIB_TEXT
				ribPL
				{
					RiArchiveBeginV($2,numParameters,tokens,vals);
				}
				|
				RIB_ARCHIVE_END
				{
					RiArchiveEnd();
				}
				|
				RIB_RESOURCE_BEGIN
				{
					RiResourceBegin();
				}
				|
				RIB_RESOURCE_END
				{
					RiResourceEnd();
				}
				|
				RIB_RESOURCE
				RIB_TEXT
				RIB_TEXT
				ribPL
				{
					RiResourceV($2,$3,numParameters,tokens,vals);
				}
				|
				RIB_IFBEGIN
				RIB_TEXT
				ribPL
				{
					RiIfBeginV($2,numParameters,tokens,vals);
				}
				|
				RIB_IFEND
				{
					RiIfEnd();
				}
				|
				RIB_ELSEIF
				RIB_TEXT
				ribPL
				{
					RiElseIfV($2,numParameters,tokens,vals);
				}
				|
				RIB_ELSE
				{
					RiElse();
				}
				|
				RIB_ERROR_HANDLER
				RIB_TEXT
				{
					RtErrorHandler 	e	=	getErrorHandler($2);

					if (e != NULL) {
						RiErrorHandler(e);
					}
				}
				|
				RIB_VERSION
				RIB_FLOAT
				{
				}
				|
				RIB_VERSION
				RIB_VERSION_STRING
				{
				}
				|
				error
				{
					if (YYRECOVERING() == 0) {
						error(CODE_BADFILE,"Syntax error\n");
					}
				}
				;

%%

#include "lex.rib.cpp"

// Our position in the rib file
static	int		ribStart	=	0;
static	int		ribStep		=	5*(1<<10);	// Parse 5 KB at a time

///////////////////////////////////////////////////////////////////////
// Function				:	riberror
// Description			:	Parser error file
// Return Value			:	-
// Comments				:
void	riberror(const char *s,...) {
	warning(CODE_BADFILE,"RIB Parse error\n");
}

///////////////////////////////////////////////////////////////////////
// Function				:	ribParse
// Description			:	Parse a rib file
// Return Value			:	-
// Comments				:
void	ribParse(const char *fileName,void (*c)(const char *,...)) {


	if (fileName != NULL) {
		

		// Save the environment first
		TLight				*savedLights						=	lights;
		TObject				*savedObjects						=	objects;
		int					savedRibLineno						=	ribLineno;
		void				(*savedCallback)(const char *,...)	=	callback;
		int					savedNumParameters					=	numParameters;
		int					savedMaxParameter					=	maxParameter;
		TParameter			*savedParameters					=	parameters;
		RtToken				*savedTokens						=	tokens;
		RtPointer			*savedVals							=	vals;
		int					savedRibDepth						=	ribDepth;
		YY_BUFFER_STATE		savedLexState						=	YY_CURRENT_BUFFER;
		TRibFile			*savedRibStack						=	ribStack;
		const char			*savedRibFile						=	ribFile;
		FILE				*savedRibIn							=	ribin;
	
		// Guard against the depreciated fdopen on windoze	
#ifdef _WINDOWS
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
		
		// Clear the objects
		TObject	*cObject;
		while((cObject=objects) != NULL) {
			objects	=	objects->next;
			if (cObject->name != NULL)	free(cObject->name);
			delete cObject;
		}
		
		// Clear the parameters
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

