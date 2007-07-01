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
//  File				:	rendererc,h
//  Classes				:	-
//  Description			:	This file holds some global types used by the renderer
//
////////////////////////////////////////////////////////////////////////
#ifndef RENDERER_CONSTANTS
#define RENDERER_CONSTANTS

// Possible renderer blocks (Used by sfBegin - sfEnd)
typedef enum {
	BLOCK_OUTSIDE	=	0,			// The initial block before the renderer is initialized
	BLOCK_RENDERER,					// The renderer has been initialized
	BLOCK_FRAME,					// Inside a frame block (equals to a renderman world block)
	BLOCK_OBJECT,					// Inside an object block
	BLOCK_XFORM,					// Inside an xform block
	BLOCK_ATTRIBUTES,				// Inside an attributes block
	BLOCK_OPTIONS					// inside an options block
} ERendererBlock;


// Possible types for a variable (Used by CVariable class)
typedef enum {
	TYPE_FLOAT,							// "u","v","s","t","Pz" ...
	TYPE_COLOR,							// "Cs"
	TYPE_VECTOR,
	TYPE_NORMAL,
	TYPE_POINT,
	TYPE_MATRIX,
	TYPE_QUAD,							// For "Pw"
	TYPE_DOUBLE,
	TYPE_STRING,
	TYPE_INTEGER
} EVariableType;

// Possible network messages
typedef enum {
	NET_CONNECT,
	NET_ACK,
	NET_NACK,
	NET_RENDER_BUCKET,
	NET_RECEIVE_BUCKET,
	NET_FINISH_FRAME,
	NET_SEND_FILE,
	NET_READY,
	NET_CREATE_CHANNEL
} ENetMessage;


// Possible container classes for a variable (Used by CVariable class)
typedef enum {
	CONTAINER_UNIFORM,
	CONTAINER_VERTEX,
	CONTAINER_VARYING,
	CONTAINER_FACEVARYING,
	CONTAINER_CONSTANT
} EVariableClass;

// Possible storage classes for a variable
typedef enum {
	STORAGE_NONE = 0,
	STORAGE_GLOBAL,
	STORAGE_PARAMETER,
	STORAGE_MUTABLEPARAMETER
} EVariableStorage;


// Possible message accessors for shaders
typedef enum {
	ACCESSOR_DISPLACEMENT = 0,
	ACCESSOR_SURFACE,
	ACCESSOR_ATMOSPHERE,
	ACCESSOR_LIGHTSOURCE,
	ACCESSOR_POSTSHADER,
	ACCESSOR_INTERIOR,
	ACCESSOR_EXTERIOR,
	NUM_ACCESSORS
} EMessageAccessor;

// Predefined coordinate systems (Used by sfFindCoordinateSystem)
typedef enum    {
    COORDINATE_OBJECT = 0,
    COORDINATE_CAMERA,
    COORDINATE_WORLD,
    COORDINATE_SHADER,
    COORDINATE_LIGHT,
    COORDINATE_NDC,
    COORDINATE_RASTER,
    COORDINATE_SCREEN,
	COORDINATE_CURRENT,
	COLOR_RGB,
    COLOR_HSL,
    COLOR_HSV,
    COLOR_XYZ,
    COLOR_CIE,
    COLOR_YIQ,
    COLOR_XYY,
    COORDINATE_CUSTOM				// This means the system is user defined
} ECoordinateSystem;

// The directives for pl->shader binding
const	unsigned int		BINDPARAM_SURFACE				=	1;
const	unsigned int		BINDPARAM_DISPLACEMENT			=	2;
const	unsigned int		BINDPARAM_ATMOSPHERE			=	4;

// The bounding box indices
const	unsigned int		BOUND_PXPYPZ					=	0;
const	unsigned int		BOUND_PXPYNZ					=	1;
const	unsigned int		BOUND_PXNYNZ					=	2;
const	unsigned int		BOUND_PXNYPZ					=	3;
const	unsigned int		BOUND_NXPYPZ					=	4;
const	unsigned int		BOUND_NXPYNZ					=	5;
const	unsigned int		BOUND_NXNYNZ					=	6;
const	unsigned int		BOUND_NXNYPZ					=	7;

const	unsigned int		BOUND_PX						=	0;
const	unsigned int		BOUND_NX						=	1;
const	unsigned int		BOUND_PY						=	2;
const	unsigned int		BOUND_NY						=	3;
const	unsigned int		BOUND_PZ						=	4;
const	unsigned int		BOUND_NZ						=	5;


//	Entry points for the global variables
//	Varying variables (this includes variables declared as vertex too)
const	unsigned	int		VARIABLE_P					=	0;
const	unsigned	int		VARIABLE_PS					=	1;
const	unsigned	int		VARIABLE_N					=	2;
const	unsigned	int		VARIABLE_NG					=	3;
const	unsigned	int		VARIABLE_DPDU				=	4;
const	unsigned	int		VARIABLE_DPDV				=	5;
const	unsigned	int		VARIABLE_L					=	6;
const	unsigned	int		VARIABLE_CS					=	7;
const	unsigned	int		VARIABLE_OS					=	8;
const	unsigned	int		VARIABLE_CL					=	9;
const	unsigned	int		VARIABLE_OL					=	10;
const	unsigned	int		VARIABLE_CI					=	11;
const	unsigned	int		VARIABLE_OI					=	12;
const	unsigned	int		VARIABLE_S					=	13;
const	unsigned	int		VARIABLE_T					=	14;
const	unsigned	int		VARIABLE_DU					=	15;
const	unsigned	int		VARIABLE_DV					=	16;
const	unsigned	int		VARIABLE_U					=	17;
const	unsigned	int		VARIABLE_V					=	18;
const	unsigned	int		VARIABLE_I					=	19;
const	unsigned	int		VARIABLE_E					=	20;
const	unsigned	int		VARIABLE_ALPHA				=	21;
const	unsigned	int		VARIABLE_TIME				=	22;
const	unsigned	int		VARIABLE_PW					=	23;
const	unsigned	int		VARIABLE_NCOMPS				=	24;
const	unsigned	int		VARIABLE_DTIME				=	25;
const	unsigned	int		VARIABLE_DPDTIME			=	26;
const	unsigned	int		VARIABLE_WIDTH				=	27;
const	unsigned	int		VARIABLE_CONSTANTWIDTH		=	28;

//	Some shader parameters
const	unsigned	int		PARAMETER_DERIVATIVE		=	1 << 14;
const	unsigned	int		PARAMETER_S					=	1;
const	unsigned	int		PARAMETER_T					=	1 << 1;
const	unsigned	int		PARAMETER_U					=	1 << 2;
const	unsigned	int		PARAMETER_V					=	1 << 3;		//			.
const	unsigned	int		PARAMETER_DU				=	(1 << 4) | PARAMETER_DERIVATIVE;
const	unsigned	int		PARAMETER_DV				=	(1 << 5) | PARAMETER_DERIVATIVE;
const	unsigned	int		PARAMETER_TIME				=	1 << 6;
const	unsigned	int		PARAMETER_DTIME				=	1 << 7;
const	unsigned	int		PARAMETER_NCOMPS			=	1 << 8;
const	unsigned	int		PARAMETER_ALPHA				=	1 << 9;
const	unsigned	int		PARAMETER_P					=	1 << 10;
const	unsigned	int		PARAMETER_PS				=	1 << 11;
const	unsigned	int		PARAMETER_DPDU				=	1 << 12;
const	unsigned	int		PARAMETER_DPDV				=	1 << 13;
const	unsigned	int		PARAMETER_DPDTIME			=	1 << 15;
const	unsigned	int		PARAMETER_NG				=	1 << 16;
const	unsigned	int		PARAMETER_N					=	(1 << 17) | PARAMETER_NG;
const	unsigned	int		PARAMETER_CI				=	1 << 18;
const	unsigned	int		PARAMETER_OI				=	1 << 19;
const	unsigned	int		PARAMETER_CL				=	1 << 20;
const	unsigned	int		PARAMETER_OL				=	1 << 21;
const	unsigned	int		PARAMETER_CS				=	1 << 22;
const	unsigned	int		PARAMETER_OS				=	1 << 23;
const	unsigned	int		PARAMETER_E					=	1 << 24;
const	unsigned	int		PARAMETER_I					=	1 << 25;
const	unsigned	int		PARAMETER_L					=	1 << 26;
const	unsigned	int		PARAMETER_BEGIN_SAMPLE		=	1 << 27;
const	unsigned	int		PARAMETER_END_SAMPLE		=	1 << 28;
const	unsigned	int		PARAMETER_RAYTRACE			=	1 << 29;	// Requires raytracing
const	unsigned	int		PARAMETER_NONAMBIENT		=	1 << 30;	// A non-ambient light source
const	unsigned	int		PARAMETER_MESSAGEPASSING	=	1 << 31;	// Shader calls message passing functions



#endif

