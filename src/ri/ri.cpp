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
//  File				:	ri.cpp
//  Classes				:	-
//  Description			:	RenderMan Interface Implementation
//
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
// The RI implementation
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "common/global.h"
#include "common/os.h"
#include "error.h"
#include "ri_config.h"
#include "ri.h"
#include "riInterface.h"
#include "ribOut.h"
#include "delayed.h"
#include "rendererContext.h"

//////////////////////////////////////////////////////////////////
// Token definitions
RtToken		RI_FRAMEBUFFER		=	"framebuffer";
RtToken		RI_FILE				=	"file";

RtToken		RI_RGB				=	"rgb";
RtToken		RI_RGBA				=	"rgba";
RtToken		RI_RGBZ				=	"rgbz";
RtToken		RI_RGBAZ			=	"rgbaz";
RtToken		RI_A				=	"a";
RtToken		RI_Z				=	"z";
RtToken		RI_AZ				=	"az";

RtToken		RI_PERSPECTIVE		=	"perspective";
RtToken		RI_ORTHOGRAPHIC		=	"orthographic";

RtToken		RI_HIDDEN			=	"hidden";
RtToken		RI_PAINT			=	"paint";

RtToken		RI_CONSTANT			=	"constant";
RtToken		RI_SMOOTH			=	"smooth";

RtToken		RI_FLATNESS			=	"flatness";
RtToken		RI_FOV				=	"fov";

RtToken		RI_AMBIENTLIGHT		=	"ambientlight";
RtToken		RI_POINTLIGHT		=	"pointlight";
RtToken		RI_DISTANTLIGHT		=	"distantlight";
RtToken		RI_SPOTLIGHT		=	"spotlight";

RtToken		RI_INTENSITY		=	"intensity";
RtToken		RI_LIGHTCOLOR		=	"lightcolor";
RtToken		RI_FROM				=	"from";
RtToken		RI_TO				=	"to";
RtToken		RI_CONEANGLE		=	"coneangle";
RtToken     RI_CONEDELTAANGLE	=	"conedeltaangle";
RtToken		RI_BEAMDISTRIBUTION	=	"beamdistribution";

RtToken		RI_MATTE			=	"matte";
RtToken		RI_METAL			=	"metal";
RtToken		RI_SHINYMETAL		=	"shinymetal";
RtToken		RI_PLASTIC			=	"plastic";
RtToken		RI_PAINTEDPLASTIC	=	"paintedplastic";

RtToken		RI_KA				=	"Ka";
RtToken		RI_KD				=	"Kd";
RtToken		RI_KS				=	"Ks";
RtToken		RI_ROUGHNESS		=	"roughness";
RtToken		RI_KR				=	"Kr";
RtToken		RI_TEXTURENAME		=	"texturename";
RtToken		RI_SPECULARCOLOR	=	"specularcolor";

RtToken		RI_DEPTHCUE			=	"depthcue";
RtToken		RI_FOG				=	"fog";
RtToken		RI_BUMPY			=	"bumpy";

RtToken		RI_MINDISTANCE		=	"mindistance";
RtToken		RI_BACKGROUND		=	"background";
RtToken		RI_DISTANCE			=	"distance";
RtToken		RI_AMPLITUDE		=	"amplitude";

RtToken		RI_INSIDE			=	"inside";
RtToken		RI_OUTSIDE			=	"outside";
RtToken		RI_LH				=	"lh";
RtToken		RI_RH				=	"rh";

RtToken		RI_P				=	"P";
RtToken		RI_PZ				=	"Pz";
RtToken		RI_PW				=	"Pw";
RtToken		RI_N				=	"N";
RtToken		RI_NP				=	"Np";
RtToken		RI_CS				=	"Cs";
RtToken		RI_OS				=	"Os";
RtToken		RI_S				=	"s";
RtToken		RI_T				=	"t";
RtToken		RI_ST				=	"st";

RtToken		RI_BILINEAR			=	"bilinear";
RtToken		RI_BICUBIC			=	"bicubic";

RtToken		RI_PRIMITIVE		=	"primitive";
RtToken		RI_INTERSECTION		=	"intersection";
RtToken		RI_UNION			=	"union";
RtToken		RI_DIFFERENCE		=	"difference";

RtToken		RI_PERIODIC			=	"periodic";
RtToken		RI_NOWRAP			=	"nowrap";
RtToken		RI_NONPERIODIC		=	"nonperiodic";
RtToken		RI_CLAMP			=	"clamp";
RtToken		RI_BLACK			=	"black";

RtToken		RI_IGNORE			=	"ignore";
RtToken		RI_PRINT			=	"print";
RtToken		RI_ABORT			=	"abort";
RtToken		RI_HANDLER			=	"handler";

RtToken		RI_ORIGIN			=	"origin";
RtToken		RI_IDENTIFIER		=	"identifier";
RtToken		RI_NAME				=	"name";

RtToken		RI_COMMENT			=	"comment";
RtToken		RI_STRUCTURE		=	"structure";
RtToken		RI_VERBATIM			=	"verbatim";

RtToken		RI_LINEAR			=	"linear";
RtToken		RI_CUBIC			=	"cubic";
RtToken		RI_WIDTH			=	"width";
RtToken		RI_CONSTANTWIDTH	=	"constantwidth";

RtToken		RI_CATMULLCLARK		=	"catmull-clark";
RtToken		RI_HOLE				=	"hole";
RtToken		RI_CREASE			=	"crease";
RtToken		RI_CORNER			=	"corner";
RtToken		RI_INTERPOLATEBOUNDARY	=	"interpolateboundary";

RtToken		RI_CURRENT			=	"current";
RtToken		RI_WORLD			=	"world";
RtToken		RI_OBJECT			=	"object";
RtToken		RI_SHADER			=	"shader";
RtToken		RI_RASTER			=	"raster";
RtToken		RI_NDC				=	"ndc";
RtToken		RI_SCREEN			=	"screen";
RtToken		RI_CAMERA			=	"camera";
RtToken		RI_EYE				=	"eye";



////////////////////////////////////////////////////////////////////////
//
//	Filter types
//
////////////////////////////////////////////////////////////////////////
RtToken		RI_BOXFILTER				=	"box";
RtToken		RI_TRIANGLEFILTER			=	"triangle";
RtToken		RI_GAUSSIANFILTER			=	"gaussian";
RtToken		RI_SINCFILTER				=	"sinc";
RtToken		RI_CATMULLROMFILTER			=	"catmull-rom";
RtToken		RI_BLACKMANHARRISFILTER		=	"blackman-harris";
RtToken		RI_MITCHELLFILTER			=	"mitchell";
RtToken		RI_BESSELFILTER				=   "bessel";
RtToken		RI_DISKFILTER				=   "disk";
RtToken		RI_CUSTOM					=	"custom";

RtToken		RI_MIN						=	"min";
RtToken		RI_MAX						=	"max";
RtToken		RI_AVERAGE					=	"average";
RtToken		RI_ZMIN						=	"zmin";
RtToken		RI_ZMAX						=	"zmax";


////////////////////////////////////////////////////////////////////////
//
//	Non-Standard options/attributes entry points
//
////////////////////////////////////////////////////////////////////////
RtToken		RI_LIMITS				=	"limits";
RtToken		RI_SEARCHPATH			=	"searchpath";
RtToken		RI_SHADOW				=	"shadow";
RtToken		RI_RENDER				=	"render";
RtToken		RI_DICE					=	"dice";
RtToken		RI_HINT					=	"hint";
RtToken		RI_TEXTURE				=	"texture";
RtToken		RI_HIDER				=	"hider";
RtToken		RI_STATISTICS			=	"statistics";
RtToken		RI_VISIBILITY			=	"visibility";
RtToken		RI_SHADE				=	"shade";
RtToken		RI_DISPLACEMENTBOUND	=	"displacementbound";
RtToken		RI_IRRADIANCE			=	"irradiance";
RtToken		RI_CULL					=	"cull";
RtToken		RI_COMPRESSION			=	"compression";
RtToken		RI_RIB					=	"rib";
RtToken		RI_SHUTTER				=	"shutter";
RtToken		RI_USER					=	"user";

////////////////////////////////////////////////////////////////////////
//
//	Non-Standard attributes
//
////////////////////////////////////////////////////////////////////////

RtToken		RI_NORMALDEVIATION		=	"normaldeviation";
RtToken		RI_POINTDEVIATION		=	"pointdeviation";


// Dice attributes
RtToken		RI_MINSUBDIVISION		=	"minsubdivision";
RtToken		RI_MAXSUBDIVISION		=	"maxsubdivision";
RtToken		RI_NUMPROBES			=	"numprobes";
RtToken		RI_MINSPLITS			=	"minsplits";
RtToken		RI_BOUNDEXPAND			=	"boundexpand";
RtToken		RI_BINARY				=	"binary";
RtToken		RI_RASTERORIENT			=	"rasterorient";

// Displacementbound attributes
RtToken		RI_SPHERE				=	"sphere";
RtToken		RI_COORDINATESYSYTEM	=	"coordinatesystem";

// Visibility attributes
RtToken		RI_PHOTON				=	"photon";
RtToken		RI_ENVIRONMENT			=	"environment";
RtToken		RI_TRACE				=	"trace";
RtToken		RI_DIFFUSE				=	"diffuse";
RtToken		RI_SPECULAR				=	"specular";
RtToken		RI_TRANSMISSION			=	"transmission";
RtToken		RI_CAUSTICS				=	"caustics";

RtToken		RI_DIFFUSEHITMODE		=	"diffusehitmode";
RtToken		RI_SPECULARHITMODE		=	"specularhitmode";
RtToken		RI_TRANSMISSIONHITMODE	=	"transmissionhitmode";
RtToken		RI_CAMERAHITMODE		=	"camerahitmode";

// Trace attributes
RtToken		RI_BIAS					=	"bias";
RtToken		RI_DISPLACEMENTS		=	"displacements";
RtToken		RI_MAXDIFFUSEDEPTH		=	"maxdiffusedepth";
RtToken		RI_MAXSPECULARDEPTH		=	"maxspeculardepth";
RtToken		RI_SAMPLEMOTION			=	"samplemotion";

// Photon attributes
RtToken		RI_GLOBALMAP			=	"globalmap";
RtToken		RI_CAUSTICMAP			=	"causticmap";
RtToken		RI_ESTIMATOR			=	"estimator";
RtToken		RI_MAXDISTANCE			=	"maxdistance";
RtToken		RI_SHADINGMODEL			=	"shadingmodel";
RtToken		RI_ILLUMINATEFRONT		=	"illuminatefront";
RtToken		RI_IOR					=	"ior";
RtToken		RI_IORRANGE				=	"iorrange";

// Motionfactor attribute
RtToken		RI_MOTIONFACTOR			=	"motionfactor";

// Cull attributes
//RtToken	RI_HIDDEN				=	"hidden";
RtToken		RI_BACKFACING			=	"backfacing";


////////////////////////////////////////////////////////////////////////
//
//	Non-Standard options
//
////////////////////////////////////////////////////////////////////////

// Searchpath options
RtToken		RI_ARCHIVE				=	"archive";
RtToken		RI_PROCEDURAL			=	"procedural";
RtToken		RI_RESOURCE				=	"resource";
RtToken		RI_DISPLAY				=	"display";


// Limits options
RtToken		RI_BUCKETSIZE			=	"bucketsize";
RtToken		RI_METABUCKETS			=	"metabuckets";
RtToken		RI_GRIDSIZE				=	"gridsize";
RtToken		RI_MAXRECURSION			=	"raydepth";
RtToken		RI_TEXTUREMEMORY		=	"texturememory";
RtToken		RI_BRICKMEMORY			=	"brickmemory";
RtToken		RI_EYESPLITS			=	"eyesplits";
RtToken		RI_NUMTHREADS			=	"numthreads";
RtToken		RI_THREADSTRIDE			=	"threadstride";
RtToken		RI_GEOCACHEMEMORY		=	"geocachememory";
RtToken		RI_OTHRESHOLD			=	"othreshold";
RtToken		RI_ZTHRESHOLD			=	"zthreshold";

// Trace options
RtToken		RI_MAXDEPTH				=	"maxdepth";

// Statstics options
RtToken		RI_ENDOFFRAME			=	"endofframe";
RtToken		RI_FILELOG				=	"filelog";
RtToken		RI_PROGRESS				=	"progress";

// Irradiance options
RtToken		RI_HANDLE				=	"handle";
RtToken		RI_FILEMODE				=	"filemode";
RtToken		RI_MAXERROR				=	"maxerror";
RtToken		RI_MAXPIXELDIST			=	"maxpixeldist";
RtToken		RI_MINSAMPLEDISTANCE	=	"minsampledistance";
RtToken		RI_MAXSAMPLEDISTANCE	=	"maxsampledistance";

// Hider options
RtToken		RI_JITTER				=	"jitter";
RtToken		RI_FALSECOLOR			=	"falsecolor";
RtToken		RI_EMIT					=	"emit";
RtToken		RI_SAMPLESPECTRUM		=	"samplespectrum";
RtToken		RI_DEPTHFILTER			=	"depthfilter";
RtToken		RI_RADIANCECACHE		=	"radiancecache";

// IO options
RtToken		RI_MASKRESOLUTION		=	"maskresolution";
RtToken		RI_MASKPRINTF			=	"maskprintf";
RtToken		RI_MASKLOG				=	"masklog";
RtToken		RI_MASKPROGRESS			=	"maskprogress";
RtToken		RI_MASKSTATS			=	"maskstats";
RtToken		RI_INHERITATTRIBUTES	=	"inheritattributes";

// Shutter options
RtToken		RI_OFFSET				=	"offset";

// Misc junk
RtToken		RI_DEFAULTSURFACE		=	"defaultsurface";

// Error handling
RtInt		RiLastError				=	RIE_NOERROR;

////////////////////////////////////////////////////////////////////////
// The cubic spline basis definition
RtBasis		RiCatmullRomBasis	= {
	{(float)  (-1.0/2.0),	(float)  ( 3.0/2.0),	(float)  (-3.0/2.0),	(float)  ( 1.0/2.0)},
	{(float)  ( 2.0/2.0),	(float)  (-5.0/2.0),	(float)  ( 4.0/2.0),	(float)  (-1.0/2.0)},
	{(float)  (-1.0/2.0),	(float)  ( 0.0/2.0),	(float)  ( 1.0/2.0),	(float)  ( 0.0/2.0)},
	{(float)  ( 0.0/2.0),	(float)  ( 2.0/2.0),	(float)  ( 0.0/2.0),	(float)  ( 0.0/2.0)}};


RtBasis		RiBezierBasis		= { 
	{(float) -1,	(float)	3,		(float)	-3,		(float)	1},
	{(float) 3,		(float)	-6,		(float)	3,		(float)	0},
	{(float) -3,	(float)	3,		(float)	0,		(float)	0},
	{(float) 1,		(float)	0,		(float)	0,		(float)	0 }};

RtBasis		RiBSplineBasis		= {
	{(float) (-1.0/6.0),	(float) (3.0/6.0),	(float) (-3.0/6.0),	(float)  (1.0/6.0)},
	{(float) (3.0/6.0),		(float) -(6.0/6.0),	(float) (3.0/6.0),	(float)  (0.0/6.0)},
	{(float) (-3.0/6.0),	(float) (0.0/6.0),	(float) (3.0/6.0),	(float)  (0.0/6.0)},
	{(float) (1.0/6.0),		(float) (4.0/6.0),	(float) (1.0/6.0),	(float)  (0.0/6.0)}};

RtBasis		RiHermiteBasis		= { 
	{(float) 1 ,	(float) 1 ,		(float)	-3 ,	(float)	1},
	{(float) -1 ,	(float) -2 ,	(float)	4 ,		(float)	-1},
	{(float) -1,	(float) 1 ,		(float)	0 ,		(float)	0},
	{(float) 1 ,	(float) 0 ,		(float)	0 ,		(float)	0}};

RtBasis		RiPowerBasis		= {
	{(float)  1,	(float)	0,		(float)	0,		(float)	0},
	{(float)  0,	(float)	1,		(float)	0,		(float)	0},
	{(float)  0,	(float)	0,		(float)	1,		(float)	0},
	{(float)  0,	(float)	0,		(float)	0,		(float)	1 }};

RtBasis		RiLinearBasis		= {
	{(float)  0,	(float)	0,		(float)	0,		(float)	0},
	{(float)  0,	(float)	0,		(float)	0,		(float)	0},
	{(float)  0,	(float)	0,		(float)	1,		(float)	0},
	{(float)  0,	(float)	0,		(float)	0,		(float)	1 }};


////////////////////////////////////////////////////////////////////////
//
// Action begins here
//
////////////////////////////////////////////////////////////////////////
const	unsigned int		RENDERMAN_BLOCK						=	1;
const	unsigned int		RENDERMAN_XFORM_BLOCK				=	RENDERMAN_BLOCK << 1;
const	unsigned int		RENDERMAN_ATTRIBUTE_BLOCK			=	RENDERMAN_XFORM_BLOCK << 1;
const	unsigned int		RENDERMAN_WORLD_BLOCK				=	RENDERMAN_ATTRIBUTE_BLOCK << 1;
const	unsigned int		RENDERMAN_FRAME_BLOCK				=	RENDERMAN_WORLD_BLOCK << 1;
const	unsigned int		RENDERMAN_OBJECT_BLOCK				=	RENDERMAN_FRAME_BLOCK << 1;
const	unsigned int		RENDERMAN_MOTION_BLOCK				=	RENDERMAN_OBJECT_BLOCK << 1;		
const	unsigned int		RENDERMAN_SOLID_PRIMITIVE_BLOCK		=	RENDERMAN_MOTION_BLOCK << 1;
const	unsigned int		RENDERMAN_SOLID_INTERSECTION_BLOCK	=	RENDERMAN_SOLID_PRIMITIVE_BLOCK << 1;
const	unsigned int		RENDERMAN_SOLID_DIFFERENCE_BLOCK	=	RENDERMAN_SOLID_INTERSECTION_BLOCK << 1;
const	unsigned int		RENDERMAN_SOLID_UNION_BLOCK			=	RENDERMAN_SOLID_DIFFERENCE_BLOCK << 1;
const	unsigned int		RENDERMAN_RESOURCE_BLOCK			=	RENDERMAN_SOLID_UNION_BLOCK << 1;
const	unsigned int		RENDERMAN_ARCHIVE_BLOCK				=	RENDERMAN_RESOURCE_BLOCK << 1;

const	unsigned int		RENDERMAN_ALL_BLOCKS				=	RENDERMAN_BLOCK
																	| RENDERMAN_XFORM_BLOCK
																	| RENDERMAN_ATTRIBUTE_BLOCK
																	| RENDERMAN_WORLD_BLOCK
																	| RENDERMAN_FRAME_BLOCK
																	| RENDERMAN_OBJECT_BLOCK
																	| RENDERMAN_MOTION_BLOCK
																	| RENDERMAN_SOLID_PRIMITIVE_BLOCK
																	| RENDERMAN_SOLID_INTERSECTION_BLOCK
																	| RENDERMAN_SOLID_DIFFERENCE_BLOCK
																	| RENDERMAN_SOLID_UNION_BLOCK
																	| RENDERMAN_RESOURCE_BLOCK
																	| RENDERMAN_ARCHIVE_BLOCK;


// This is the blocks that options can be changed
const	unsigned int		VALID_OPTION_BLOCKS					=	RENDERMAN_BLOCK | RENDERMAN_FRAME_BLOCK | RENDERMAN_ARCHIVE_BLOCK;

// This is the blocks that attributes can be changed
const	unsigned int		VALID_ATTRIBUTE_BLOCKS				=	RENDERMAN_BLOCK | RENDERMAN_FRAME_BLOCK | RENDERMAN_WORLD_BLOCK | RENDERMAN_ARCHIVE_BLOCK | RENDERMAN_ATTRIBUTE_BLOCK | RENDERMAN_XFORM_BLOCK | RENDERMAN_SOLID_PRIMITIVE_BLOCK | RENDERMAN_OBJECT_BLOCK | RENDERMAN_MOTION_BLOCK | RENDERMAN_RESOURCE_BLOCK;																

// This is the blocks that xforms can be changed
const	unsigned int		VALID_XFORM_BLOCKS					=	RENDERMAN_BLOCK | RENDERMAN_FRAME_BLOCK | RENDERMAN_WORLD_BLOCK | RENDERMAN_ARCHIVE_BLOCK | RENDERMAN_ATTRIBUTE_BLOCK | RENDERMAN_XFORM_BLOCK | RENDERMAN_SOLID_PRIMITIVE_BLOCK | RENDERMAN_OBJECT_BLOCK | RENDERMAN_MOTION_BLOCK | RENDERMAN_RESOURCE_BLOCK;

// This is the blocks that primitives can be issued
const	unsigned int		VALID_PRIMITIVE_BLOCKS				=	RENDERMAN_WORLD_BLOCK | RENDERMAN_ARCHIVE_BLOCK | RENDERMAN_ATTRIBUTE_BLOCK | RENDERMAN_XFORM_BLOCK | RENDERMAN_SOLID_PRIMITIVE_BLOCK | RENDERMAN_OBJECT_BLOCK | RENDERMAN_MOTION_BLOCK | RENDERMAN_RESOURCE_BLOCK;

// Global variables to convert calls to the vector form
static	int					initialized			=	FALSE;
static	int					nTokens,mTokens;							// Parameter list info
static	RtToken				*tokens				=	NULL;
static	RtPointer			*values				=	NULL;
static	CArray<int>			blocks;										// The block stack
static	int					framebufferOnly		=	FALSE;
static	int					frameRangeActive	=	FALSE;
static	int					frameBegin			=	0;
static	int					frameEnd			=	0;
static	int					frameStep			=	0;
static	int					ignoreFrame			=	FALSE;
static	int					currentBlock		=	0;
static	int					raytracingInited	=	FALSE;
static	int					allowedCommands		=	RENDERMAN_ALL_BLOCKS;
static	int					archiveNesting		=	0;

		CRiInterface		*savedRenderMan		=	NULL;	// This variable contains the parent context for arhiving
		CRiInterface		*renderMan			=	NULL;	// This variable is exported for error reporting
		int					ignoreCommand		=	FALSE;	// This variable can be set to force ignore ri commands (used for conditional execution)
		int					insideRunProgram	=	FALSE;	// Are we running inside a runprogram context


///////////////////////////////////////////////////////////////////////
// Function				:	check
// Description			:	Make sure the command is good for a given nesting
// Return Value			:	TRUE if the command should be ignored
// Comments				:
static	inline int		check(const char *fun,int scope) {
	if (ignoreFrame | ignoreCommand)	return TRUE;

	if (scope & currentBlock & allowedCommands)	return FALSE;

	if (allowedCommands != RENDERMAN_FRAME_BLOCK) {
		if (renderMan != NULL) {
			error(CODE_NESTING,"Bad scope for \"%s\"\n",fun);
		}
	}

	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// Function				:	extract
// Description			:	Extract a parameter from the command string
// Return Value			:
// Comments				:
static	inline int		extract(char *dest,const char *tag,const char *src) {
	const char	*tmp,*tmpEnd;
	int			length;

	if ((tmp = strstr(src,tag)) != NULL) {
		if ((tmpEnd	= strchr(tmp+1,' ')) == NULL)	tmpEnd	=	tmp + strlen(tmp);

		length	=	(int) (tmpEnd - tmp - strlen(tag));

		strncpy(dest,tmp+strlen(tag),length);
		dest[length]	=	'\0';
		return	TRUE;
	} else {
		return	FALSE;
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	getArgs
// Description			:	Read the parameter list and set nTokens,tokens,values
// Return Value			:
// Comments				:
static	inline	void	getArgs(va_list args) {
	RtToken		tmp;
	tmp			= va_arg(args,RtToken);
    nTokens		= 0;
    while (tmp != RI_NULL) {
		tokens[nTokens] = tmp;
		values[nTokens] = va_arg(args,RtPointer);
		nTokens++;
		if (nTokens == mTokens) {
			RtToken		*ttokens	=	new RtToken[mTokens + 50];
			RtPointer	*tvalues	=	new RtPointer[mTokens + 50];
			int			i;

			for (i=0;i<nTokens;i++) {
				ttokens[i] = tokens[i];
				tvalues[i] = values[i];
			}

			delete [] tokens;
			delete [] values;

			tokens	=	ttokens;
			values	=	tvalues;

			mTokens += 50;
		}
		tmp = va_arg(args,RtToken);
    }
}

///////////////////////////////////////////////////////////////////////
// Function				:	RiInit
// Description			:	Init the static variables
// Return Value			:
// Comments				:
static	void RiInit() {
	if (initialized)	return;
	
	nTokens				=	0;
	mTokens				=	0;
	tokens				=	NULL;
	values				=	NULL;
	currentBlock		=	0;

	nTokens				=	0;
	mTokens				=	50;
	tokens				=	new RtToken[mTokens];
	values				=	new RtPointer[mTokens];
	currentBlock		=	RENDERMAN_BLOCK;
	initialized			=	TRUE;
}

///////////////////////////////////////////////////////////////////////
// Function				:	RiTini
// Description			:	Ditch the allocated static variables
// Return Value			:
// Comments				:
static	void RiTini() {
	if (tokens != NULL)				delete [] tokens;
	if (values != NULL)				delete [] values;
	initialized	= FALSE;
}





///////////////////////////////////////////////////////////////////////
//
// RenderMan Interface begins here
//
///////////////////////////////////////////////////////////////////////
EXTERN(RtToken) RiDeclare (const char *name,const char *declaration) {
	if (check("RiDeclare",RENDERMAN_ALL_BLOCKS)) return RI_NULL;

	renderMan->RiDeclare(name,declaration);

	return (RtToken) name;
}

EXTERN(RtContextHandle)	RiGetContext(void) {
	if (check("RiGetContext",RENDERMAN_BLOCK)) return RI_NULL;

	return (RtContextHandle) renderMan;
}


EXTERN(RtVoid)
RiContext(RtContextHandle handle) {
	if (check("RiContext",RENDERMAN_BLOCK)) return;

	renderMan	=	(CRiInterface *) handle;
}


EXTERN(RtVoid)
RiBegin (RtToken name) {
	if (renderMan != NULL) {
		error(CODE_NESTING,"Already started\n");
		return;
	}

	// Parse the net string
	if (name != NULL) {
		if (name[0] == '#') {
			char	riRibFile[OS_MAX_PATH_LENGTH];
			char	riNetString[OS_MAX_PATH_LENGTH];
			int		riRib,riNet;

			if (extract(riRibFile,	"fbonly:"	,name))	framebufferOnly	=	TRUE;
			
			if (extract(riRibFile,	"frames:"	,name))	{	
				if		(sscanf(riRibFile,"%d:%d:%d",&frameBegin,&frameStep,&frameEnd) == 3) {
					frameRangeActive	=	TRUE;	
				} else if (sscanf(riRibFile,"%d:%d",&frameBegin,&frameEnd) == 2){
					frameStep			=	0;
					frameRangeActive	=	TRUE;	
				} else if (sscanf(riRibFile,"%d",&frameBegin) == 1) {
					frameEnd			=	frameBegin;
					frameStep			=	0;
					frameRangeActive	=	TRUE;	
				}
			}
			
			riRib	=	extract(riRibFile,		"rib:"		,name);
			riNet	=	extract(riNetString,	"net:"		,name);

			if (riRib & riNet)	renderMan	=	new CRendererContext(riRibFile,riNetString);
			else				renderMan	=	new CRendererContext();

		} else {
			renderMan	=	new CRibOut(name);
		}
	} else {
		char *runProgEnv = osEnvironment("PIXIE_RUNPROGRAM");
		if (runProgEnv != NULL) {
			// If we're a runprogram, we should be writing out to stdout
			renderMan	=	new CRibOut(stdout);
			insideRunProgram = TRUE;
		} else {
			renderMan	=	new CRendererContext();
		}
	}

	// Init the renderer
	RiInit();
	
	// Alter the state if we're inside a runprogram
	if (insideRunProgram) {
		// We're also inside the world block already
		currentBlock = RENDERMAN_WORLD_BLOCK;
	}


	if (framebufferOnly) {
		framebufferOnly	=	FALSE;
		RiDisplay("ri",RI_FRAMEBUFFER,RI_RGB,RI_NULL);
		framebufferOnly	=	TRUE;
	}
}

EXTERN(RtVoid)
RiEnd (void) {

	// Alter the state if we're inside a runprogram
	if (insideRunProgram) {
		RiArchiveRecord(RI_VERBATIM,"\n\377");
		fflush(stdout);
		// We're also inside the world block already
		currentBlock = RENDERMAN_BLOCK;
	}
	
	if (check("RiEnd",RENDERMAN_BLOCK)) return;

	if (currentBlock != RENDERMAN_BLOCK) {
		error(CODE_NESTING,"Matching RiBegin not found\n");
	}

	currentBlock	=	blocks.pop();

	// Ditch the statics
	RiTini();

	delete renderMan;
	renderMan	=	NULL;
}
   
// FrameBegin - End stuff
EXTERN(RtVoid)
RiFrameBegin (RtInt number) {
	if (check("RiFrameBegin",RENDERMAN_BLOCK | RENDERMAN_ARCHIVE_BLOCK)) return;

	if (frameRangeActive) {
		if ((number < frameBegin) || (number > frameEnd))	ignoreFrame	=	TRUE;
		else if (frameStep > 1) {
			if (((number - frameBegin) % frameStep) != 0)	ignoreFrame	=	TRUE;
		}
	}

	renderMan->RiFrameBegin(number);

	blocks.push(currentBlock);
	currentBlock	=	RENDERMAN_FRAME_BLOCK;
}

EXTERN(RtVoid)
RiFrameEnd (void) {

	ignoreFrame	=	FALSE;

	if (check("RiFrameEnd",RENDERMAN_FRAME_BLOCK)) return;

	if (currentBlock != RENDERMAN_FRAME_BLOCK) {
		error(CODE_NESTING,"Matching RiFrameBegin not found\n");
		return;
	}

	renderMan->RiFrameEnd();

	currentBlock	=	blocks.pop();

	if (allowedCommands == RENDERMAN_FRAME_BLOCK)	allowedCommands		=	RENDERMAN_ALL_BLOCKS;
}

// WorldBegin - End stuff
EXTERN(RtVoid)
RiWorldBegin (void) {
	if (check("RiWorldBegin",RENDERMAN_BLOCK | RENDERMAN_FRAME_BLOCK | RENDERMAN_ARCHIVE_BLOCK)) return;

	renderMan->RiWorldBegin();

	blocks.push(currentBlock);
	currentBlock	=	RENDERMAN_WORLD_BLOCK;
}

EXTERN(RtVoid)
RiWorldEnd (void) {

	if (check("RiWorldEnd",RENDERMAN_WORLD_BLOCK)) return;

	if (currentBlock != RENDERMAN_WORLD_BLOCK) {
		error(CODE_NESTING,"Matching RiWorldBegin not found\n");
		return;
	}

	renderMan->RiWorldEnd();

	currentBlock		=	blocks.pop();
}

EXTERN(RtVoid)
RiFormat (RtInt xres, RtInt yres, RtFloat aspect) {
	if (check("RiFormat",VALID_OPTION_BLOCKS)) return;

	renderMan->RiFormat(xres,yres,aspect);
}

EXTERN(RtVoid)
RiFrameAspectRatio (RtFloat aspect) {
	if (check("RiFrameAspectRatio",VALID_OPTION_BLOCKS)) return;

	renderMan->RiFrameAspectRatio(aspect);
}

EXTERN(RtVoid)
RiScreenWindow (RtFloat left, RtFloat right, RtFloat bot, RtFloat top) {
	if (check("RiScreenWindow",VALID_OPTION_BLOCKS)) return;

	renderMan->RiScreenWindow(left,right,bot,top);
}

EXTERN(RtVoid)
RiCropWindow (RtFloat xmin, RtFloat xmax, RtFloat ymin, RtFloat ymax) {
	if (check("RiCropWindow",VALID_OPTION_BLOCKS)) return;

	renderMan->RiCropWindow(xmin,xmax,ymin,ymax);
}

EXTERN(RtVoid)
RiProjection (const char *name, ...) {
	va_list	args;
	va_start(args,name);
	getArgs(args);
	RiProjectionV(name,nTokens,tokens,values);
	va_end(args);

}

EXTERN(RtVoid)
RiProjectionV (const char *name, RtInt n, RtToken tokens[], RtPointer params[]) {
	if (check("RiProjection",VALID_OPTION_BLOCKS)) return;

	renderMan->RiProjectionV(name,n,tokens,params);
}

EXTERN(RtVoid)
RiClipping (RtFloat hither, RtFloat yon) {
	if (check("RiClipping",VALID_OPTION_BLOCKS)) return;

	renderMan->RiClipping(hither,yon);
}

EXTERN(RtVoid)
RiClippingPlane(RtFloat x,RtFloat y,RtFloat z,RtFloat nx,RtFloat ny,RtFloat nz) {
	if (check("RiClippingPlane",VALID_OPTION_BLOCKS)) return;

	renderMan->RiClippingPlane(x,y,z,nx,ny,nz);
}

EXTERN(RtVoid)
RiDepthOfField (RtFloat fstop, RtFloat focallength, RtFloat focaldistance) {
	if (check("RiDepthOfField",VALID_OPTION_BLOCKS)) return;

	renderMan->RiDepthOfField(fstop,focallength,focaldistance);
}

EXTERN(RtVoid)
RiShutter (RtFloat smin, RtFloat smax) {
	if (check("RiShutter",VALID_OPTION_BLOCKS)) return;

	renderMan->RiShutter(smin,smax);
}

EXTERN(RtVoid)
RiPixelVariance (RtFloat variation) {
	if (check("RiPixelVariance",VALID_OPTION_BLOCKS)) return;

	renderMan->RiPixelVariance(variation);
}

EXTERN(RtVoid)
RiPixelSamples (RtFloat xsamples, RtFloat ysamples) {
	if (check("RiPixelSamples",VALID_OPTION_BLOCKS)) return;

	renderMan->RiPixelSamples(xsamples,ysamples);
}

EXTERN(RtVoid)
RiPixelFilter (RtFilterFunc function, RtFloat xwidth, RtFloat ywidth) {
	if (check("RiPixelFilter",VALID_OPTION_BLOCKS)) return;

	renderMan->RiPixelFilter(function,xwidth,ywidth);
}

EXTERN(RtVoid)
RiExposure (RtFloat gain, RtFloat gamma) {
	if (check("RiExposure",VALID_OPTION_BLOCKS)) return;

	renderMan->RiExposure(gain,gamma);
}

EXTERN(RtVoid)
RiImager (const char *name, ...) {
	va_list	args;

	va_start(args,name);
	getArgs(args);
	RiImagerV(name,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)
RiImagerV (const char *name, RtInt n, RtToken tokens[], RtPointer params[]) {
	if (check("RiImager",VALID_OPTION_BLOCKS)) return;

	renderMan->RiImagerV(name,n,tokens,params);
}

EXTERN(RtVoid)
RiQuantize (RtToken type, RtInt one, RtInt qmin, RtInt qmax, RtFloat ampl) {
	if (check("RiQuantize",VALID_OPTION_BLOCKS)) return;

	renderMan->RiQuantize(type,one,qmin,qmax,ampl);
}

EXTERN(RtVoid)
RiDisplay (const char *name, RtToken type, RtToken mode, ...) {
	va_list	args;

	va_start(args,mode);
	getArgs(args);
	RiDisplayV(name,type,mode,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)
RiDisplayV (const char *name, RtToken type, RtToken mode,
			RtInt n, RtToken tokens[], RtPointer params[]) {
	if (check("RiDisplay",VALID_OPTION_BLOCKS)) return;

	if (framebufferOnly) return;

	renderMan->RiDisplayV(name,type,mode,n,tokens,params);
}

EXTERN(RtVoid)
RiCustomDisplay (const char *name, RtToken mode, RtDisplayStartFunction startFunc, RtDisplayDataFunction dataFunc, RtDisplayFinishFunction endFunc, ...) {
	va_list	args;

	va_start(args,endFunc);
	getArgs(args);
	RiCustomDisplayV(name,mode,startFunc,dataFunc,endFunc,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)
RiCustomDisplayV (const char *name, RtToken mode, RtDisplayStartFunction startFunc, RtDisplayDataFunction dataFunc, RtDisplayFinishFunction endFunc, RtInt n, RtToken tokens[], RtPointer params[]) {
	if (check("RiCustomDisplay",VALID_OPTION_BLOCKS)) return;

	if (framebufferOnly) return;

	renderMan->RiCustomDisplayV(name,mode,startFunc,dataFunc,endFunc,n,tokens,params);
}

EXTERN(RtVoid)
RiDisplayChannel (RtToken channel, ...) {
	va_list	args;

	va_start(args,channel);
	getArgs(args);
	RiDisplayChannelV(channel,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)
RiDisplayChannelV (RtToken channel,RtInt n, RtToken tokens[], RtPointer params[]) {
	if (check("RiDisplayChannel",VALID_OPTION_BLOCKS)) return;

	renderMan->RiDisplayChannelV(channel,n,tokens,params);
}


// Various filters

EXTERN(RtFloat)
RiGaussianFilter (RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth) {
	x		=	2*x / xwidth;
	y		=	2*y / ywidth;

	return expf(-2 * (x*x + y*y));
}

EXTERN(RtFloat)
RiBoxFilter (RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth) {
	return 1;
}

EXTERN(RtFloat)
RiTriangleFilter (RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth) {
	if (x<0.0) x = -x;
    if (y<0.0) y = -y;

	xwidth	*=	0.5f;
	ywidth	*=	0.5f;

	if (x > y) {
		return (RtFloat) (xwidth-x) / xwidth;
	} else {
		return (RtFloat) (ywidth-y) / ywidth;
	}

    
}

EXTERN(RtFloat)
RiCatmullRomFilter (RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth) {
   float r2 = (x*x + y*y);
   float r = sqrtf(r2);

   if (r < 1.0f) {
	   return	(float) (1.5f*r*r2 - 2.5f*r2 + 1.0f);
   } else if (r < 2.0f) {
	   return	(float) (-0.5f*r*r2 + 2.5f*r2 - 4.0f*r + 2.0f);
   } else {
	   return 0;
   }
}

EXTERN(RtFloat)
RiBlackmanHarrisFilter (RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth) {
   float xc = x/xwidth;
   float yc = y/ywidth;
   float r2 = (xc*xc + yc*yc);
   float r = 0.5f-sqrtf(r2);
   
   const float N  = 1;
   const float a0 = 0.35875f;
   const float a1 = 0.48829f;
   const float a2 = 0.14128f;
   const float a3 = 0.01168f;
   
   if (r <= N*0.5f) {
	   return	(float) (a0 - a1*cosf(2*((float) C_PI)*r/N) + a2*cosf(4*((float) C_PI)*r/N) - a3*cosf(6*((float) C_PI)*r/N));
   } else {
       return	0;
   }
}

EXTERN(RtFloat)
RiMitchellFilter( RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth ) {
	x	/=	xwidth;
	y	/=	ywidth;

#define	B	1/3.0f
#define	C	1/3.0f

	x	=	fabsf(2.f * x);
	if (x > 1.f)	x	= ((-B - 6*C) * x*x*x + (6*B + 30*C) * x*x + (-12*B - 48*C) * x + (8*B + 24*C)) * (1.f/6.f);
	else			x	= ((12 - 9*B - 6*C) * x*x*x + (-18 + 12*B + 6*C) * x*x + (6 - 2*B)) * (1.f/6.f);

	y	=	fabsf(2.f * y);
	if (y > 1.f)	y	= ((-B - 6*C) * y*y*y + (6*B + 30*C) * y*y + (-12*B - 48*C) * y + (8*B + 24*C)) * (1.f/6.f);
	else			y	= ((12 - 9*B - 6*C) * y*y*y + (-18 + 12*B + 6*C) * y*y + (6 - 2*B)) * (1.f/6.f);

#undef B
#undef C

	return	x*y;
}

EXTERN(RtFloat)
RiSincFilter (RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth) {
	
	if ( x != 0.0 )	{
		x *= (float) C_PI;
		x = cosf( 0.5f * x / xwidth ) * sinf( x ) / x;
	} else {
		x = 1.0;
	}

	if ( y != 0.0 ) {
		y *= (float) C_PI;
		y = cosf( 0.5f * y / ywidth ) * sinf( y ) / y;
	} else {
		y = 1.0;
	}

	return x*y;
}

EXTERN(RtFloat)
RiBesselFilter (RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth) {
	const float x2 = x * x;
	const float y2 = y * y;
	
	if ( x2+y2 < 0.0001f )
		return 1.0f;

	const float w = x2 / ( xwidth * xwidth ) + y2 / ( ywidth * ywidth );
	const float d = sqrtf( x2 + y2 );
	return (float) (j1( d*2 )/d);
}


EXTERN(RtFloat)
RiDiskFilter (RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth) {
	const float xc = x / xwidth;
	const float yc = y / ywidth;
	const float d = xc * xc + yc * yc;

	return ( d <= 0.25f )? 1.0f : 0.0f;
}

#ifdef _WINDOWS
//
// Computation of the complementary error function erfc(x).
//
// The algorithm is based on a Chebyshev fit as denoted in
// Numerical Recipes 2nd ed. on p. 214 (W.H.Press et al.).
//
// The fractional error is always less than 1.2e-7.
//
//
// The parameters of the Chebyshev fit
//
inline double erfc(double x) {
	const double a1 = -1.26551223, a2 = 1.00002368,
	a3 = 0.37409196, a4 = 0.09678418,
	a5 = -0.18628806, a6 = 0.27886807,
	a7 = -1.13520398, a8 = 1.48851587,
	a9 = -0.82215223, a10 = 0.17087277;
	//
	double v = 1; // The return value
	double z = fabs(x);
	//
	if (z <= 0) return v; // erfc(0)=1
	//
	double t = 1/(1+0.5*z);
	//
	v = t*exp((-z*z) +a1+t*(a2+t*(a3+t*(a4+t*(a5+t*(a6+t*(a7+t*(a8+t*(a9+t*a10)))))))));
	//
	if (x < 0) v = 2-v; // erfc(-x)=2-erfc(x)
	//
	return v;
}
#endif


EXTERN(RtFloat)
RiGaussianStepFilter(RtFloat _t,RtFloat _edge,RtFloat _w) {
	const double t = _t,edge = _edge,w = _w;
	double res = 0.0;

	res = (1.0/2.0)*erfc( (2.0*sqrt(2.0)*(edge-t))/w );

	return (RtFloat) res;
}

EXTERN(RtFloat)
RiCatmullRomStepFilter(RtFloat _t,RtFloat _edge,RtFloat _w) {
	const double t = _t,edge = _edge,w = _w;
	double res = 0.0;

	if (edge==t && edge>=(t+w) && edge<(t+2.0*w)) {
		res = -1.0/24.0;
	} else if (edge<t && (edge+w)<=t && (edge+2.0*w)<=t) {
		res = 1.0;	
	} else if ((edge+w)==t && (edge+2.0*w)>t && edge<t) {
		res = 25.0/24.0;
	} else if (edge>t && edge>(t+w) && edge<(t+2.0*w)) {
		res = ((3.0*edge-3.0*t-2.0*w) * pow(edge-t-2.0*w,3.0)) / (24.0*pow(w,4.0));
	} else if ((edge+2.0*w)>t && edge<t && (edge+w)<t) {
		res = (-3.0*pow(edge-t,4.0) - 20.0*pow(edge-t,3.0)*w - 48.0*pow(edge-t,2.0)*w*w + 
				 48.0*(-edge+t)*pow(w,3.0) + 8.0*pow(w,4.0))/(24.0*pow(w,4.0));
	} else if ((edge+w)>t && edge<t && (edge+2.0*w)<=t) {
		res	= (-edge+t)/w		+ (3.0*pow(edge-t,4))/(8.0*pow(w,4.0))
								+ (5.0*pow(edge-t,3))/(6.0*pow(w,3.0))
								+ (11.0)/24.0;
	} else if (edge<(t+w) && (edge>t || (edge>=t && edge<(t+2.0*w)))) {
		res = (-edge+t)/w		- (3.0*pow(edge-t,4))/(8.0*pow(w,4.0))
								+ (5.0*pow(edge-t,3))/(6.0*pow(w,3.0))
								+ 1.0/2.0;
	} else if ((edge+w)>t && (edge+2.0*w)>t && edge<t) {
		res = (-edge+t)/w		+ (3.0*pow(edge-t,4))/(8.0*pow(w,4.0))
								+ (5.0*pow(edge-t,3))/(6.0*pow(w,3.0))
								+ 1.0/2.0;
	} else if (edge==t && edge>=(t+2.0*w) && edge<(t+w)) {
		res = 13.0/24.0;
	}
	
	return (RtFloat) res;
}

EXTERN(RtFloat)
RiMitchellStepFilter(RtFloat _t,RtFloat _edge,RtFloat _w) {
	const double t = _t,edge = _edge,w = _w;
	double res = 0.0;

	if (edge==t && edge>=(t+w) && edge<(t+2.0*w)) {
		res = -1.0/72.0;
	} else if (edge<t && (edge+w)<=t && (edge+2.0*w)<=t) {
		res = 1.0;	
	} else if ((edge+w)==t && (edge+2.0*w)>t && edge<t) {
		res = 73.0/72.0;
	} else if (edge>t && edge>(t+w) && edge<(t+2.0*w)) {
		res = ((7.0*edge-7.0*t-6.0*w) * pow(edge-t-2.0*w,3.0)) / (72.0*pow(w,4.0));
	} else if ((edge+2.0*w)>t && edge<t && (edge+w)<t) {
		res = (-7.0*pow(edge-t,4.0) - 48.0*pow(edge-t,3.0)*w - 120.0*pow(edge-t,2.0)*w*w + 
				 128.0*(-edge+t)*pow(w,3.0) + 24.0*pow(w,4.0))/(72.0*pow(w,4.0));
	} else if ((edge+w)>t && edge<t && (edge+2.0*w)<=t) {
		res	= (64.0*(-edge+t)/(w*72.0)) + (35.0/72.0)
								+ ( (21.0*pow(edge-t,4))
								+   (48.0*w*pow(edge-t,3)) ) /(72.0*pow(w,4.0));
	} else if (edge<(t+w) && (edge>t || (edge>=t && edge<(t+2.0*w)))) {
		res	= (64.0*(-edge+t)/(w*72.0)) + (36.0/72.0)
								+ ( (-21.0*pow(edge-t,4))
								+   (48.0*w*pow(edge-t,3)) ) /(72.0*pow(w,4.0));
	} else if ((edge+w)>t && (edge+2.0*w)>t && edge<t) {
		res	= (64.0*(-edge+t)/(w*72.0)) + (36.0/72.0)
								+ ( (21.0*pow(edge-t,4))
								+   (48.0*w*pow(edge-t,3)) ) /(72.0*pow(w,4.0));
	} else if (edge==t && edge>=(t+2.0*w) && edge<(t+w)) {
		res = 37.0/72.0;
	}
	
	return (RtFloat) res;
}


EXTERN(RtFloat)
RiTriangleStepFilter(RtFloat _t,RtFloat _edge,RtFloat _w) {
	const double t = _t,edge = _edge,w = _w;
	double res = 0.0;
	
	if ((edge-t+w)<= 0 && (edge-t) < 0) {
		res = 1.0;
	} else if ((edge-t)<0 && (edge-t+w) > 0) {
		res = (-edge*edge + 2.0*edge*t - t*t - 2.0*edge*w + 2.0*t*w + w*w)/(2.0*w*w);
	} else if ((edge-t)>=0 && (edge-t-w) < 0) {
		res = ( edge*edge - 2.0*edge*t + t*t - 2.0*edge*w + 2.0*t*w + w*w)/(2.0*w*w);
	}

	return (RtFloat) res;
}

EXTERN(RtFloat)
RiBoxStepFilter(RtFloat _t,RtFloat _edge,RtFloat _w) {
	const double t = _t,edge = _edge,w = _w;
	double res = 0.0;
	
	if ((edge-t)<0 && (2.0*edge-2*t+w) <= 0) {
		res = 1.0;
	} else if (((2.0*edge-2.0*t+w)>0 && (edge-t)<0) || ((edge-t)>=0 && (2.0*edge-2.0*t-w)<0)) {
		res = (-2.0*edge + 2.0*t + w)/(2.0*w);
	}

	return (RtFloat) res;
}



EXTERN(RtVoid)
RiHider (RtToken type, ...) {
	va_list	args;

	va_start(args,type);
	getArgs(args);
	RiHiderV(type,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)
RiHiderV (RtToken type, RtInt n, RtToken tokens[], RtPointer params[]) {
	if (check("RiHider",VALID_OPTION_BLOCKS)) return;

	renderMan->RiHiderV(type,n,tokens,params);
}

EXTERN(RtVoid)
RiColorSamples (RtInt N, RtFloat *nRGB, RtFloat *RGBn) {
	if (check("RiColorSamples",VALID_OPTION_BLOCKS)) return;

	renderMan->RiColorSamples(N,nRGB,RGBn);
}

EXTERN(RtVoid)
RiRelativeDetail (RtFloat relativedetail) {
	if (check("RiRelativeDetail",VALID_OPTION_BLOCKS)) return;

	renderMan->RiRelativeDetail(relativedetail);
}

EXTERN(RtVoid)
RiOption (const char *name, ...) {
	va_list	args;

	// init if necessary (for gz options)
	if (!initialized) RiInit();
	
	va_start(args,name);
	getArgs(args);
	RiOptionV(name,nTokens,tokens,values);
	va_end(args);
}


EXTERN(RtVoid)
RiOptionV (const char *name, RtInt n, RtToken tokens[], RtPointer params[]) {

	// This section allows us to parse RibOut options before RiBegin, to match the standard
	if (renderMan == NULL) {
		extern int preferCompressedRibOut;
		
		// Check the rib format options
		if (strcmp(name,RI_RIB) == 0) {
			for (int i=0;i<n;i++) {
				if (strcmp(tokens[i],RI_COMPRESSION) == 0) {
					char	*val	=	((char **) params[i])[0];
					if (strcmp(val,"gzip") == 0) {
						preferCompressedRibOut	=	TRUE;
					} else if (strcmp(val,"none") == 0) {
						preferCompressedRibOut	=	FALSE;
					} else {
						error(CODE_BADTOKEN,"Unknown compression type \"%s\"\n",val);
					}
				}
			}
		}
		return;
	}
	
	if (check("RiOption",VALID_OPTION_BLOCKS)) return;

	renderMan->RiOptionV(name,n,tokens,params);
}


EXTERN(RtVoid)
RiAttributeBegin (void) {
	if (check("RiAttributeBegin",RENDERMAN_BLOCK | RENDERMAN_FRAME_BLOCK | RENDERMAN_WORLD_BLOCK | RENDERMAN_ATTRIBUTE_BLOCK | RENDERMAN_XFORM_BLOCK | RENDERMAN_SOLID_PRIMITIVE_BLOCK | RENDERMAN_RESOURCE_BLOCK | RENDERMAN_ARCHIVE_BLOCK)) return;

	renderMan->RiAttributeBegin();

	blocks.push(currentBlock);
	currentBlock	=	RENDERMAN_ATTRIBUTE_BLOCK;
}

EXTERN(RtVoid)
RiAttributeEnd (void) {
	if (check("RiAttributeEnd",RENDERMAN_ATTRIBUTE_BLOCK)) return;

	if (currentBlock != RENDERMAN_ATTRIBUTE_BLOCK) {
		error(CODE_NESTING,"Matching RiAttributeBegin not found\n");
		return;
	}

	renderMan->RiAttributeEnd();

	currentBlock	=	blocks.pop();
}

EXTERN(RtVoid)
RiColor (RtColor Cs) {
	if (check("RiColor",VALID_ATTRIBUTE_BLOCKS)) return;

	renderMan->RiColor(Cs);
}

EXTERN(RtVoid)
RiOpacity (RtColor Cs) {
	if (check("RiOpacity",VALID_ATTRIBUTE_BLOCKS)) return;

	renderMan->RiOpacity(Cs);
}

EXTERN(RtVoid)
RiTextureCoordinates (RtFloat s1, RtFloat t1, RtFloat s2, RtFloat t2,
					  RtFloat s3, RtFloat t3, RtFloat s4, RtFloat t4) {
	if (check("RiTextureCoordinates",VALID_ATTRIBUTE_BLOCKS)) return;

	renderMan->RiTextureCoordinates(s1,t1,s2,t2,s3,t3,s4,t4);
}


EXTERN(RtLightHandle)
RiLightSource (const char *name, ...) {
	RtLightHandle	handle;
	va_list			args;

	va_start(args,name);
	getArgs(args);
	handle	=	RiLightSourceV(name,nTokens,tokens,values);
	va_end(args);

	return handle;
}

EXTERN(RtLightHandle)
RiLightSourceV (const char *name, RtInt n, RtToken tokens[], RtPointer params[]) {
	if (check("RiLightSource",VALID_ATTRIBUTE_BLOCKS)) return NULL;

	return (RtLightHandle) renderMan->RiLightSourceV(name,n,tokens,params);
}

EXTERN(RtLightHandle)
RiAreaLightSource (const char *name, ...) {
	RtLightHandle	handle;
	va_list			args;

	va_start(args,name);
	getArgs(args);
	handle	=	RiAreaLightSourceV(name,nTokens,tokens,values);
	va_end(args);

	return handle;
}

EXTERN(RtLightHandle)
RiAreaLightSourceV (const char *name, RtInt n,
					RtToken tokens[], RtPointer params[]) {
	if (check("RiAreaLightSource",VALID_ATTRIBUTE_BLOCKS)) return NULL;

	return (RtLightHandle) renderMan->RiAreaLightSourceV(name,n,tokens,params);
}


EXTERN(RtVoid)
RiIlluminate (RtLightHandle light, RtBoolean onoff) {
	if (check("RiIlluminate",VALID_ATTRIBUTE_BLOCKS)) return;

	renderMan->RiIlluminate(light,onoff);
}

EXTERN(RtVoid)
RiSurface (const char *name, ...) {
	va_list			args;

	va_start(args,name);
	getArgs(args);
	RiSurfaceV(name,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)
RiSurfaceV (const char *name, RtInt n, RtToken tokens[], RtPointer params[]) {
	if (check("RiSurface",VALID_ATTRIBUTE_BLOCKS)) return;

	renderMan->RiSurfaceV(name,n,tokens,params);
}

EXTERN(RtVoid)
RiAtmosphere (const char *name, ...) {
	va_list			args;

	va_start(args,name);
	getArgs(args);
	RiAtmosphereV(name,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)
RiAtmosphereV (const char *name, RtInt n, RtToken tokens[], RtPointer params[]) {
	if (check("RiAtmosphere",VALID_ATTRIBUTE_BLOCKS)) return;

	renderMan->RiAtmosphereV(name,n,tokens,params);
}

EXTERN(RtVoid)
RiInterior (const char *name, ...) {
	va_list			args;

	va_start(args,name);
	getArgs(args);
	RiInteriorV(name,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)
RiInteriorV (const char *name, RtInt n, RtToken tokens[], RtPointer params[]) {
	if (check("RiInterior",VALID_ATTRIBUTE_BLOCKS)) return;

	renderMan->RiInteriorV(name,n,tokens,params);
}

EXTERN(RtVoid)
RiExterior (const char *name, ...) {
	va_list			args;

	va_start(args,name);
	getArgs(args);
	RiExteriorV(name,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)
RiExteriorV (const char *name, RtInt n, RtToken tokens[], RtPointer params[]) {
	if (check("RiExterior",VALID_ATTRIBUTE_BLOCKS)) return;

	renderMan->RiExteriorV(name,n,tokens,params);
}

EXTERN(RtVoid)
RiShadingRate (RtFloat size) {
	if (check("RiShadingRate",VALID_ATTRIBUTE_BLOCKS)) return;

	renderMan->RiShadingRate(size);
}

EXTERN(RtVoid)
RiShadingInterpolation (RtToken type) {
	if (check("RiShadingInterpolation",VALID_ATTRIBUTE_BLOCKS)) return;

	renderMan->RiShadingInterpolation(type);
}

EXTERN(RtVoid)
RiMatte (RtBoolean onoff) {
	if (check("RiMatte",VALID_ATTRIBUTE_BLOCKS)) return;

	renderMan->RiMatte(onoff);
}


EXTERN(RtVoid)
RiBound (RtBound bound) {
	if (check("RiBound",VALID_ATTRIBUTE_BLOCKS)) return;

	renderMan->RiBound(bound);
}

EXTERN(RtVoid)
RiDetail (RtBound bound) {
	if (check("RiDetail",VALID_ATTRIBUTE_BLOCKS)) return;

	renderMan->RiDetail(bound);
}

EXTERN(RtVoid)
RiDetailRange (RtFloat minvis, RtFloat lowtran,
			   RtFloat uptran, RtFloat maxvis) {
	if (check("RiDetailRange",VALID_ATTRIBUTE_BLOCKS)) return;

	renderMan->RiDetailRange(minvis,lowtran,uptran,maxvis);
}

EXTERN(RtVoid)
RiGeometricApproximation (RtToken type, RtFloat value) {
	if (check("RiGeometricApproximation",VALID_ATTRIBUTE_BLOCKS)) return;

	renderMan->RiGeometricApproximation(type,value);
}

EXTERN(RtVoid)
RiGeometricRepresentation (RtToken type) {
	if (check("RiGeometricRepresentation",VALID_ATTRIBUTE_BLOCKS)) return;

	renderMan->RiGeometricRepresentation(type);
}

EXTERN(RtVoid)
RiOrientation (RtToken orientation) {
	if (check("RiOrientation",VALID_ATTRIBUTE_BLOCKS)) return;

	renderMan->RiOrientation(orientation);
}

EXTERN(RtVoid)
RiReverseOrientation (void) {
	if (check("RiReverseOrientation",VALID_ATTRIBUTE_BLOCKS)) return;

	renderMan->RiReverseOrientation();
}

EXTERN(RtVoid)
RiSides (RtInt nsides) {
	if (check("RiSides",VALID_ATTRIBUTE_BLOCKS)) return;

	renderMan->RiSides(nsides);
}


EXTERN(RtVoid)
RiIdentity (void) {
	if (check("RiIdentity",VALID_XFORM_BLOCKS)) return;

	renderMan->RiIdentity();
}

EXTERN(RtVoid)
RiTransform (RtMatrix transform) {
	if (check("RiTransform",VALID_XFORM_BLOCKS)) return;

	renderMan->RiTransform(transform);
}

EXTERN(RtVoid)
RiConcatTransform (RtMatrix transform) {
	if (check("RiConcatTransform",VALID_XFORM_BLOCKS)) return;

	renderMan->RiConcatTransform(transform);
}

EXTERN(RtVoid)
RiPerspective (RtFloat fov) {
	if (check("RiPerspective",VALID_XFORM_BLOCKS)) return;

	renderMan->RiPerspective(fov);
}

EXTERN(RtVoid)
RiTranslate (RtFloat dx, RtFloat dy, RtFloat dz) {
	if (check("RiTranslate",VALID_XFORM_BLOCKS)) return;

	renderMan->RiTranslate(dx,dy,dz);
}

EXTERN(RtVoid)
RiRotate (RtFloat angle, RtFloat dx, RtFloat dy, RtFloat dz) {
	if (check("RiRotate",VALID_XFORM_BLOCKS)) return;

	renderMan->RiRotate(angle,dx,dy,dz);
}

EXTERN(RtVoid)
RiScale (RtFloat dx, RtFloat dy, RtFloat dz) {
	if (check("RiScale",VALID_XFORM_BLOCKS)) return;

	renderMan->RiScale(dx,dy,dz);
}

EXTERN(RtVoid)
RiSkew (RtFloat angle, RtFloat dx1, RtFloat dy1, RtFloat dz1,
		RtFloat dx2, RtFloat dy2, RtFloat dz2) {
	if (check("RiSkew",VALID_XFORM_BLOCKS)) return;

	renderMan->RiSkew(angle,dx1,dy1,dz1,dx2,dy2,dz2);
}

EXTERN(RtVoid)
RiDeformation (const char *name, ...) {
	va_list			args;

	va_start(args,name);
	getArgs(args);
	RiDeformationV(name,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)
RiDeformationV (const char *name, RtInt n, RtToken tokens[], RtPointer params[]) {
	if (check("RiDeformation",VALID_XFORM_BLOCKS)) return;

	renderMan->RiDeformationV(name,n,tokens,params);
}

EXTERN(RtVoid)
RiDisplacement (const char *name, ...) {
	va_list			args;

	va_start(args,name);
	getArgs(args);
	RiDisplacementV(name,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)
RiDisplacementV (const char *name, RtInt n, RtToken tokens[], RtPointer params[]) {

	// We treat displacement as an attribute, not an xform
	if (check("RiDisplacement",VALID_ATTRIBUTE_BLOCKS)) return;

	renderMan->RiDisplacementV(name,n,tokens,params);
}

EXTERN(RtVoid)
RiCoordinateSystem (RtToken space) {
	if (check("RiCoordinateSystem",VALID_XFORM_BLOCKS)) return;

	renderMan->RiCoordinateSystem(space);
}

EXTERN(RtVoid)
RiCoordSysTransform (RtToken space) {
	if (check("RiCoordSysTransform",VALID_XFORM_BLOCKS)) return;

	renderMan->RiCoordSysTransform(space);
}


EXTERN(RtPoint *)
RiTransformPoints (RtToken fromspace, RtToken tospace,
							RtInt npoints, RtPoint *points) {
	if (check("RiTransformPoints",RENDERMAN_ALL_BLOCKS)) return NULL;

	return renderMan->RiTransformPoints(fromspace,tospace,npoints,points);
}


EXTERN(RtVoid)
RiTransformBegin (void) {
	if (check("RiTransformBegin",VALID_XFORM_BLOCKS)) return;
	
	renderMan->RiTransformBegin();

	blocks.push(currentBlock);
	currentBlock	=	RENDERMAN_XFORM_BLOCK;
}

EXTERN(RtVoid)
RiTransformEnd (void) {
	if (check("RiTransformEnd",RENDERMAN_XFORM_BLOCK)) return;

	if (currentBlock != RENDERMAN_XFORM_BLOCK) {
		error(CODE_NESTING,"Matching RiTransformBegin not found\n");
		return;
	}

	renderMan->RiTransformEnd();

	currentBlock		=	blocks.pop();
}


EXTERN(RtVoid)
RiAttribute (const char *name, ...) {
	va_list			args;

	va_start(args,name);
	getArgs(args);
	RiAttributeV(name,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)
RiAttributeV (const char *name, RtInt n, RtToken tokens[], RtPointer params[]) {
	if (check("RiAttribute",VALID_ATTRIBUTE_BLOCKS)) return;

	renderMan->RiAttributeV(name,n,tokens,params);
}

EXTERN(RtVoid)
RiPolygon (RtInt nvertices, ...) {
	va_list			args;

	va_start(args,nvertices);
	getArgs(args);
	RiPolygonV(nvertices,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)
RiPolygonV (RtInt nvertices, RtInt n, RtToken tokens[], RtPointer params[]) {
	if (check("RiPolygon",VALID_PRIMITIVE_BLOCKS)) return;

	renderMan->RiPolygonV(nvertices,n,tokens,params);
}

EXTERN(RtVoid)
RiGeneralPolygon (RtInt nloops, RtInt *nverts, ...) {
	va_list			args;

	va_start(args,nverts);
	getArgs(args);
	RiGeneralPolygonV(nloops,nverts,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)
RiGeneralPolygonV (RtInt nloops, RtInt *nverts,
				   RtInt n, RtToken tokens[], RtPointer params[]) {
	if (check("RiGeneralPolygon",VALID_PRIMITIVE_BLOCKS)) return;

	renderMan->RiGeneralPolygonV(nloops,nverts,n,tokens,params);
}

EXTERN(RtVoid)
RiPointsPolygons (RtInt npolys, RtInt *nverts, RtInt *verts, ...) {
	va_list			args;

	va_start(args,verts);;
	getArgs(args);
	RiPointsPolygonsV(npolys,nverts,verts,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)
RiPointsPolygonsV (RtInt npolys, RtInt *nverts, RtInt *verts, 
				   RtInt n, RtToken tokens[], RtPointer params[]) {
	if (check("RiPointsPolygons",VALID_PRIMITIVE_BLOCKS)) return;

	renderMan->RiPointsPolygonsV(npolys,nverts,verts,n,tokens,params);
}

EXTERN(RtVoid)
RiPointsGeneralPolygons (RtInt npolys, RtInt *nloops,
						 RtInt *nverts, RtInt *verts, ...) {
	va_list			args;

	va_start(args,verts);
	getArgs(args);
	RiPointsGeneralPolygonsV(npolys,nloops,nverts,verts,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)
RiPointsGeneralPolygonsV (RtInt npolys, RtInt *nloops,
			     RtInt *nverts, RtInt *verts, 
				 RtInt n, RtToken tokens[], RtPointer params[]) {
	if (check("RiPointsGeneralPolygons",VALID_PRIMITIVE_BLOCKS)) return;

	renderMan->RiPointsGeneralPolygonsV(npolys,nloops,nverts,verts,n,tokens,params);
}

EXTERN(RtVoid)
RiBasis (RtBasis ubasis, RtInt ustep, RtBasis vbasis, RtInt vstep) {
	if (check("RiBasis",VALID_ATTRIBUTE_BLOCKS)) return;

	renderMan->RiBasis(ubasis,ustep,vbasis,vstep);
}

EXTERN(RtVoid)
RiPatch (RtToken type, ...) {
	va_list	args;

	va_start(args,type);
	getArgs(args);
	RiPatchV(type,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)
RiPatchV (RtToken type, RtInt n, RtToken tokens[], RtPointer params[]) {
	if (check("RiPatch",VALID_PRIMITIVE_BLOCKS)) return;

	renderMan->RiPatchV(type,n,tokens,params);
}

EXTERN(RtVoid)
RiPatchMesh (RtToken type, RtInt nu, RtToken uwrap,
			 RtInt nv, RtToken vwrap, ...) {
	va_list	args;

	va_start(args,vwrap);
	getArgs(args);
	RiPatchMeshV(type,nu,uwrap,nv,vwrap,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)
    RiPatchMeshV (RtToken type, RtInt nu, RtToken uwrap, RtInt nv,
		  RtToken vwrap, RtInt n, RtToken tokens[], RtPointer params[]) {
	if (check("RiPatchMesh",VALID_PRIMITIVE_BLOCKS)) return;

	renderMan->RiPatchMeshV(type,nu,uwrap,nv,vwrap,n,tokens,params);
}

EXTERN(RtVoid)
    RiNuPatch (RtInt nu, RtInt uorder, RtFloat *uknot,
	       RtFloat umin, RtFloat umax, RtInt nv, RtInt vorder,
		   RtFloat *vknot, RtFloat vmin, RtFloat vmax, ...) {
	va_list	args;

	va_start(args,vmax);
	getArgs(args);
	RiNuPatchV(nu,uorder,uknot,umin,umax,nv,vorder,vknot,vmin,vmax,nTokens,tokens,values);
	va_end(args);

}

EXTERN(RtVoid)
    RiNuPatchV (RtInt nu, RtInt uorder, RtFloat *uknot,
		RtFloat umin, RtFloat umax, RtInt nv, RtInt vorder,
		RtFloat *vknot, RtFloat vmin, RtFloat vmax, 
		RtInt n, RtToken tokens[], RtPointer params[]) {
	if (check("RiNuPatch",VALID_PRIMITIVE_BLOCKS)) return;

	renderMan->RiNuPatchV(nu,uorder,uknot,umin,umax,nv,vorder,vknot,vmin,vmax,n,tokens,params);
}

EXTERN(RtVoid)
    RiTrimCurve (RtInt nloops, RtInt *ncurves, RtInt *order,
		 RtFloat *knot, RtFloat *amin, RtFloat *amax,
		 RtInt *n, RtFloat *u, RtFloat *v, RtFloat *w) {

	// Trim curve is an attribute
	if (check("RiTrimCurve",VALID_ATTRIBUTE_BLOCKS)) return;

	renderMan->RiTrimCurve(nloops,ncurves,order,knot,amin,amax,n,u,v,w);
}

EXTERN(RtVoid)
    RiSphere (RtFloat radius, RtFloat zmin,
	RtFloat zmax, RtFloat thetamax, ...) {
	va_list	args;

	va_start(args,thetamax);
	getArgs(args);
	RiSphereV(radius,zmin,zmax,thetamax,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)
    RiSphereV (RtFloat radius, RtFloat zmin, RtFloat zmax, RtFloat thetamax,
	RtInt n, RtToken tokens[], RtPointer params[]) {
	if (check("RiSphere",VALID_PRIMITIVE_BLOCKS)) return;

	renderMan->RiSphereV(radius,zmin,zmax,thetamax,n,tokens,params);
}

EXTERN(RtVoid)
RiCone (RtFloat height, RtFloat radius, RtFloat thetamax, ...) {
	va_list	args;

	va_start(args,thetamax);
	getArgs(args);
	RiConeV(height,radius,thetamax,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)
    RiConeV (RtFloat height, RtFloat radius, RtFloat thetamax, 
	RtInt n, RtToken tokens[], RtPointer params[]) {
	if (check("RiCone",VALID_PRIMITIVE_BLOCKS)) return;

	renderMan->RiConeV(height,radius,thetamax,n,tokens,params);
}

EXTERN(RtVoid)
    RiCylinder (RtFloat radius, RtFloat zmin, RtFloat zmax, 
	RtFloat thetamax, ...) {
	va_list	args;

	va_start(args,thetamax);
	getArgs(args);
	RiCylinderV(radius,zmin,zmax,thetamax,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)
    RiCylinderV (RtFloat radius, RtFloat zmin, RtFloat zmax, RtFloat thetamax,
	RtInt n, RtToken tokens[], RtPointer params[]) {
	if (check("RiCylinder",VALID_PRIMITIVE_BLOCKS)) return;

	renderMan->RiCylinderV(radius,zmin,zmax,thetamax,n,tokens,params);
}

EXTERN(RtVoid)
RiHyperboloid (RtPoint point1, RtPoint point2, RtFloat thetamax, ...) {
	va_list	args;

	va_start(args,thetamax);
	getArgs(args);
	RiHyperboloidV(point1,point2,thetamax,nTokens,tokens,values);
	va_end(args);

}

EXTERN(RtVoid)
    RiHyperboloidV (RtPoint point1, RtPoint point2, RtFloat thetamax, 
	RtInt n, RtToken tokens[], RtPointer params[]) {
	if (check("RiHyperboloid",VALID_PRIMITIVE_BLOCKS)) return;

	renderMan->RiHyperboloidV(point1,point2,thetamax,n,tokens,params);
}

EXTERN(RtVoid)
    RiParaboloid (RtFloat rmax, RtFloat zmin,
		  RtFloat zmax, RtFloat thetamax, ...) {
	va_list	args;

	va_start(args,thetamax);
	getArgs(args);
	RiParaboloidV(rmax,zmin,zmax,thetamax,nTokens,tokens,values);
	va_end(args);

}

EXTERN(RtVoid)
    RiParaboloidV (RtFloat radius, RtFloat zmin, RtFloat zmax, RtFloat thetamax, 
	RtInt n, RtToken tokens[], RtPointer params[]) {
	if (check("RiParaboloid",VALID_PRIMITIVE_BLOCKS)) return;

	renderMan->RiParaboloidV(radius,zmin,zmax,thetamax,n,tokens,params);
}

EXTERN(RtVoid)
RiDisk (RtFloat height, RtFloat radius, RtFloat thetamax, ...) {
	va_list	args;

	va_start(args,thetamax);
	getArgs(args);
	RiDiskV(height,radius,thetamax,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)
    RiDiskV (RtFloat height, RtFloat radius, RtFloat thetamax, 
	RtInt n, RtToken tokens[], RtPointer params[]) {
	if (check("RiDisk",VALID_PRIMITIVE_BLOCKS)) return;

	renderMan->RiDiskV(height,radius,thetamax,n,tokens,params);
}

EXTERN(RtVoid)
    RiTorus (RtFloat majorrad, RtFloat minorrad, RtFloat phimin,
	RtFloat phimax, RtFloat thetamax, ...) {
	va_list	args;

	va_start(args,thetamax);
	getArgs(args);
	RiTorusV(majorrad,minorrad,phimin,phimax,thetamax,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)
    RiTorusV (RtFloat majorrad, RtFloat minorrad, RtFloat phimin,
	     RtFloat phimax, RtFloat thetamax,
		 RtInt n, RtToken tokens[], RtPointer params[]) {
	if (check("RiTorus",VALID_PRIMITIVE_BLOCKS)) return;

	renderMan->RiTorusV(majorrad,minorrad,phimin,phimax,thetamax,n,tokens,params);
}

EXTERN(RtVoid)
RiCurves (RtToken degree, RtInt ncurves, RtInt nverts[], RtToken wrap, ...) {
	va_list	args;

	va_start(args,wrap);
	getArgs(args);
	RiCurvesV(degree,ncurves,nverts,wrap,nTokens,tokens,values);
	va_end(args);
}


EXTERN(RtVoid)
RiCurvesV (RtToken degree, RtInt ncurves, RtInt nverts[], RtToken wrap, 
		   RtInt n, RtToken tokens[], RtPointer params[]) {
	if (check("RiCurves",VALID_PRIMITIVE_BLOCKS)) return;

	renderMan->RiCurvesV(degree,ncurves,nverts,wrap,n,tokens,params);
}

EXTERN(RtVoid)
    RiProcedural (void *data, RtBound bound,
		  RtVoid (*subdivfunc) (void *, RtFloat),RtVoid (*freefunc) (void *)) {
	if (check("RiProcedural",VALID_PRIMITIVE_BLOCKS)) return;

	renderMan->RiProcedural(data,bound,subdivfunc,freefunc);
}


EXTERN(RtVoid)
RiGeometry (RtToken type, ...) {
	va_list	args;

	va_start(args,type);
	getArgs(args);
	RiGeometryV(type,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)
RiGeometryV (RtToken type, RtInt n, RtToken tokens[], RtPointer params[]) {
	if (check("RiGeometry",VALID_PRIMITIVE_BLOCKS)) return;

	renderMan->RiGeometryV(type,n,tokens,params);
}

EXTERN(RtVoid)
RiPoints (RtInt npts,...) {
	va_list	args;

	va_start(args,npts);
	getArgs(args);
	RiPointsV(npts,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)
RiPointsV (RtInt npts, RtInt n, RtToken tokens[], RtPointer params[]) {
	if (check("RiPoints",VALID_PRIMITIVE_BLOCKS)) return;

	renderMan->RiPointsV(npts,n,tokens,params);
}

EXTERN(RtVoid)
    RiSubdivisionMesh (RtToken scheme, RtInt nfaces,
		       RtInt nvertices[], RtInt vertices[],
		       RtInt ntags, RtToken tags[], RtInt nargs[],
			   RtInt intargs[], RtFloat floatargs[], ...) {
	va_list	args;

	va_start(args,floatargs);
	getArgs(args);
	RiSubdivisionMeshV(scheme,nfaces,nvertices,vertices,ntags,tags,nargs,intargs,floatargs,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)
    RiSubdivisionMeshV (RtToken scheme, RtInt nfaces,
		       RtInt nvertices[], RtInt vertices[],
		       RtInt ntags, RtToken tags[], RtInt nargs[],
		       RtInt intargs[], RtFloat floatargs[], 
			   RtInt n, RtToken tokens[], RtPointer params[]) {
	if (check("RiSubdivisionMesh",VALID_PRIMITIVE_BLOCKS)) return;

	renderMan->RiSubdivisionMeshV(scheme,nfaces,nvertices,vertices,ntags,tags,nargs,intargs,floatargs,n,tokens,params);
}

EXTERN(RtVoid)
    RiBlobby (RtInt nleaf, RtInt ncode, RtInt code[],
	RtInt nflt, RtFloat flt[], RtInt nstr, RtString str[], ...) {
	va_list	args;

	va_start(args,str);
	getArgs(args);
	RiBlobbyV(nleaf,ncode,code,nflt,flt,nstr,str,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)
    RiBlobbyV (RtInt nleaf, RtInt ncode, RtInt code[],
	       RtInt nflt, RtFloat flt[], RtInt nstr, RtString str[],
		   RtInt n, RtToken tokens[], RtPointer params[]) {

	if (check("RiBlobby",VALID_PRIMITIVE_BLOCKS)) return;

	renderMan->RiBlobbyV(nleaf,ncode,code,nflt,flt,nstr,str,n,tokens,params);
}


EXTERN(RtVoid)
RiProcDelayedReadArchive (void *data, RtFloat detail) {
	CDelayedData	*delayed	=	(CDelayedData *) data;

	renderMan->RiReadArchiveV(delayed->generator,NULL,0,NULL,NULL);
	
#if 0
	int			cubePoints[]	=	{	0, 0, 0,
										1, 0, 0,
										1, 0, 1,
										0, 0, 1,
										
										0, 1, 0,
										1, 1, 0,
										1, 1, 1,
										0, 1, 1,
										
										0, 0, 0,
										1, 0, 0,
										1, 1, 0,
										0, 1, 0,
										
										0, 0, 1,
										1, 0, 1,
										1, 1, 1,
										0, 1, 1,
										
										0, 0, 0,
										0, 1, 0,
										0, 1, 1,
										0, 0, 1,
										
										1, 0, 0,
										1, 1, 0,
										1, 1, 1,
										1, 0, 1
										};
	
	vector bmin,bmax;
	interpolatev(bmin,delayed->bmin,delayed->bmax,0.05);
	interpolatev(bmax,delayed->bmin,delayed->bmax,0.95);
	
	float	*P = (float*) alloca(6*4*3*sizeof(float));
	int 	*Ind = (int*) alloca(6*4*sizeof(int));
	int 	*NV = (int*) alloca(6*sizeof(int));
	
	int		*cInd = Ind;
	float	*cP = P;
	
	#define pt() 							\
		*cP++ = cp[0] ? bmin[0] : bmax[0];	\
		*cP++ = cp[1] ? bmin[1] : bmax[1];	\
		*cP++ = cp[2] ? bmin[2] : bmax[2];	\
		*cInd++ = i;						\
		cp += 3;
	
	int *cp = cubePoints;
	for(int i=0;i<6*4;i++) {
		pt();
	}
	for(int i=0;i<6;i++)
		NV[i] = 4;
	
	RiAttributeBegin();
	vector Cs,Os;
	initv(Cs,rand()/((float)RAND_MAX),rand()/((float)RAND_MAX),rand()/((float)RAND_MAX));
	initv(Os,0.2);
	RiOpacity(Os);
	RiColor(Cs);
	RiSides(2);
	RiPointsPolygons( 6, NV, Ind, "P", P, NULL);
	RiAttributeEnd();
#endif
}


EXTERN(RtVoid)
RiProcRunProgram (void *data, RtFloat detail) {
	CDelayedData	*delayed	=	(CDelayedData *) data;
	
	// GSHTODO: cache the open pipes and close on last RunProgram
	
#ifdef _WINDOWS
	char			progString[256];
	char			tmpFile[512];

	// GSHTODO: do proper redirection.  See
	// http://support.microsoft.com/default.aspx?scid=kb;en-us;190351
	
	tmpnam(tmpFile);
	sprintf(progString,"echo %f [%s] | %s > %s",detail,delayed->helper,delayed->generator,tmpFile);
	system(progString);
	renderMan->RiReadArchiveV(tmpFile,NULL,0,NULL,NULL);
	osDeleteFile(tmpFile);
#else
	int				fdin[2];
	int				fdout[2];
	
	if ((pipe(fdin) != -1) && (pipe(fdout) != -1)) {
		int cpid;
		
		if ( (cpid = fork()) >= 0) {
			
			if (cpid != 0) {
				char	tmp[128];

				// we are the parent rndr
				
				close(fdout[0]);			// close the ends the client uses
				close(fdin[1]);
				
				// repoen as files, close the fd versions
				sprintf(tmp,"|%d",fdin[0]);
				FILE	*out	= fdopen(fdout[1],"wb");
				
				if (out != NULL) {
					// This write may SIGPIPE out - so guard against it
					void (*oldHandler)(int) = signal(SIGPIPE,SIG_IGN);
					
					fprintf(out,"%f [%s]\n",detail,delayed->helper);
					fflush(out);		// ensure the output is synchronized
					fclose(out);		// send eof (remove this when we keep pipe open)
					out = NULL;
					
					signal(SIGPIPE,oldHandler);
					
					renderMan->RiReadArchiveV(tmp,NULL,0,NULL,NULL);
				} else {
					error(CODE_SYSTEM,"Failed to redirect input or output for \"%s\"\n",delayed->generator);
				}
				// close the output handle (it may already be shut)
				if (out	!= NULL) fclose(out);
			} else {
				// We are the child process
				
				close(fdout[1]);		// we'll read from fdout[0], fdout[1] belongs to parent
				close(fdin[0]);			// we'll write to fdin[1], fdin[0] belongs to parent
				
				dup2(fdout[0],STDIN_FILENO);	close(fdout[0]);// remap stdin and stdout
				dup2(fdin[1],STDOUT_FILENO);	close(fdin[1]);
				
				putenv((char *) "PIXIE_RUNPROGRAM=1");
				
				// launch the program (via shell to do cmdline parsing / breaking up!)
				if (system(delayed->generator) != 0) {
					error(CODE_SYSTEM,"Failed to execute \"%s\"\n",delayed->generator);
				}
				
				_exit(0);	// call _exit() NOT exit() to avoid flushing stdio twice
			}
		} else {
			error(CODE_SYSTEM,"Failed to execute \"%s\"\n",delayed->generator);
			close(fdin[0]);
			close(fdin[1]);
			close(fdout[0]);
			close(fdout[1]);
		}
	} else {
		error(CODE_SYSTEM,"Failed to open communication for \"%s\"\n",delayed->generator);
		close(fdin[0]);
		close(fdin[1]);
		close(fdout[0]);
		close(fdout[1]);
	}
#endif
}

EXTERN(RtVoid)
RiProcDynamicLoad (void *data, RtFloat detail) {
	CDelayedData	*delayed	=	(CDelayedData *) data;
	void			*module;

	module	=	osLoadModule(delayed->generator);

	if (module != NULL) {
		// Extract information
		RtPointer			blindData;

		typedef	RtPointer	(*FunConvertParameter)(char *);
		typedef	void		(*FunSubdivide)(RtPointer,RtFloat);
		typedef	void		(*FunFree)(RtPointer);

		FunConvertParameter	ConvertParameter;
		FunSubdivide		Subdivide;
		FunFree				Free;

		ConvertParameter	=	(FunConvertParameter)	osResolve(module,"ConvertParameters");
		Subdivide			=	(FunSubdivide)			osResolve(module,"Subdivide");
		Free				=	(FunFree)				osResolve(module,"Free");

		blindData			=	NULL;
		if (ConvertParameter	!= NULL)	blindData	=	ConvertParameter(delayed->helper);
		if (Subdivide			!= NULL)	Subdivide(blindData,detail);
		if (Free				!= NULL)	Free(blindData);

		//osUnloadModule(module);
	} else {
		error(CODE_NOFILE,"The delayed module \"%s\" is not found: %s\n",delayed->generator,osModuleError());
	}
}

EXTERN(RtVoid)	RiProcFree(void *data) {
	CDelayedData	*delayed	=	(CDelayedData *) data;

	delete delayed;
}

EXTERN(RtVoid)
RiSolidBegin (RtToken type) {
	if (check("RiSolidBegin",RENDERMAN_WORLD_BLOCK | RENDERMAN_ATTRIBUTE_BLOCK | RENDERMAN_XFORM_BLOCK | RENDERMAN_SOLID_PRIMITIVE_BLOCK | RENDERMAN_RESOURCE_BLOCK | RENDERMAN_ARCHIVE_BLOCK)) return;

	renderMan->RiSolidBegin(type);
}

EXTERN(RtVoid)
RiSolidEnd(void) {
	if (check("RiSolidEnd",RENDERMAN_WORLD_BLOCK | RENDERMAN_ATTRIBUTE_BLOCK | RENDERMAN_XFORM_BLOCK | RENDERMAN_SOLID_PRIMITIVE_BLOCK | RENDERMAN_RESOURCE_BLOCK | RENDERMAN_ARCHIVE_BLOCK)) return;

	renderMan->RiSolidEnd();
}

EXTERN(RtObjectHandle)
RiObjectBegin (void) {
	if (check("RiObjectBegin",RENDERMAN_BLOCK | RENDERMAN_FRAME_BLOCK | RENDERMAN_WORLD_BLOCK | RENDERMAN_ATTRIBUTE_BLOCK | RENDERMAN_XFORM_BLOCK | RENDERMAN_SOLID_PRIMITIVE_BLOCK | RENDERMAN_RESOURCE_BLOCK | RENDERMAN_ARCHIVE_BLOCK)) return NULL;

	blocks.push(currentBlock);
	currentBlock	=	RENDERMAN_OBJECT_BLOCK;
	
	return (RtObjectHandle) renderMan->RiObjectBegin();
}


EXTERN(RtVoid)
RiObjectEnd (void) {
	if (check("RiObjectBegin",RENDERMAN_OBJECT_BLOCK)) return;	

	if (currentBlock != RENDERMAN_OBJECT_BLOCK) {
		error(CODE_NESTING,"Matching RiObjectBegin not found\n");
		return;
	}

	renderMan->RiObjectEnd();

	currentBlock	=	blocks.pop();	
}


EXTERN(RtVoid)
RiObjectInstance (RtObjectHandle handle) {
	if (check("RiObjectInstance",VALID_PRIMITIVE_BLOCKS)) return;

	renderMan->RiObjectInstance(handle);
}

EXTERN(RtVoid)
RiMotionBegin (RtInt N, ...) {
	va_list	args;
	float	*keys;
	int		i;

	keys	=	(float *) alloca(sizeof(float)*N);
	va_start(args,N);

	for (i=0;i<N;i++) {
		keys[i]	=	(float) (va_arg(args,double));
	}

	va_end(args);

	RiMotionBeginV(N,keys);
}

EXTERN(RtVoid)
RiMotionBeginV (RtInt N, RtFloat times[]) {
	if (check("RiMotionBegin",RENDERMAN_BLOCK | RENDERMAN_FRAME_BLOCK | RENDERMAN_WORLD_BLOCK | RENDERMAN_ATTRIBUTE_BLOCK | RENDERMAN_XFORM_BLOCK | RENDERMAN_SOLID_PRIMITIVE_BLOCK | RENDERMAN_RESOURCE_BLOCK | RENDERMAN_ARCHIVE_BLOCK)) return;	
	
	renderMan->RiMotionBeginV(N,times);

	blocks.push(currentBlock);
	currentBlock	=	RENDERMAN_MOTION_BLOCK;
}

EXTERN(RtVoid)
RiMotionEnd (void) {
	if (check("RiMotionEnd",RENDERMAN_MOTION_BLOCK)) return;	

	if (currentBlock != RENDERMAN_MOTION_BLOCK) {
		error(CODE_NESTING,"Expecting a motion block\n");
		return;
	}

	renderMan->RiMotionEnd();

	currentBlock	=	blocks.pop();
}

EXTERN(RtVoid)
    RiMakeTexture (const char *pic, const char *tex, RtToken swrap, RtToken twrap,
	RtFilterFunc filterfunc, RtFloat swidth, RtFloat twidth, ...) {

	va_list	args;

	va_start(args,twidth);
	getArgs(args);
	RiMakeTextureV(pic,tex,swrap,twrap,filterfunc,swidth,twidth,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)
    RiMakeTextureV (const char *pic, const char *tex, RtToken swrap, RtToken twrap,
		    RtFilterFunc filterfunc, RtFloat swidth, RtFloat twidth,
			RtInt n, RtToken tokens[], RtPointer params[]) {
	if (check("RiMakeTexture",RENDERMAN_ALL_BLOCKS)) return;	

	renderMan->RiMakeTextureV(pic,tex,swrap,twrap,filterfunc,swidth,twidth,n,tokens,params);
}

EXTERN(RtVoid)
    RiMakeBump (const char *pic, const char *tex, RtToken swrap, RtToken twrap,
	RtFilterFunc filterfunc, RtFloat swidth, RtFloat twidth, ...) {
	va_list	args;

	va_start(args,twidth);
	getArgs(args);
	RiMakeBumpV(pic,tex,swrap,twrap,filterfunc,swidth,twidth,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)
    RiMakeBumpV (const char *pic, const char *tex, RtToken swrap, RtToken twrap,
		 RtFilterFunc filterfunc, RtFloat swidth, RtFloat twidth,
		 RtInt n, RtToken tokens[], RtPointer params[]) {
	if (check("RiMakeBump",RENDERMAN_ALL_BLOCKS)) return;	

	renderMan->RiMakeBumpV(pic,tex,swrap,twrap,filterfunc,swidth,twidth,n,tokens,params);
}

EXTERN(RtVoid)
    RiMakeLatLongEnvironment (const char *pic, const char *tex, RtFilterFunc filterfunc,
	RtFloat swidth, RtFloat twidth, ...) {
	va_list	args;

	va_start(args,twidth);
	getArgs(args);
	RiMakeLatLongEnvironmentV(pic,tex,filterfunc,swidth,twidth,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)
    RiMakeLatLongEnvironmentV (const char *pic, const char *tex, RtFilterFunc filterfunc,
			      RtFloat swidth, RtFloat twidth,
				  RtInt n, RtToken tokens[], RtPointer params[]) {
	if (check("RiMakeLatLongEnvironment",RENDERMAN_ALL_BLOCKS)) return;	

	renderMan->RiMakeLatLongEnvironmentV(pic,tex,filterfunc,swidth,twidth,n,tokens,params);
}

EXTERN(RtVoid)
    RiMakeCubeFaceEnvironment (const char *px, const char *nx, const char *py,
			       const char *ny, const char *pz, const char *nz,
			       const char *tex, RtFloat fov, RtFilterFunc filterfunc,
				   RtFloat swidth, RtFloat twidth, ...) {
	va_list	args;

	va_start(args,twidth);
	getArgs(args);
	RiMakeCubeFaceEnvironmentV(px,nx,py,ny,pz,nz,tex,fov,filterfunc,swidth,twidth,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)
    RiMakeCubeFaceEnvironmentV (const char *px, const char *nx, const char *py,
				const char *ny, const char *pz, const char *nz,
				const char *tex, RtFloat fov, RtFilterFunc filterfunc,
				RtFloat swidth, RtFloat twidth,
				RtInt n, RtToken tokens[], RtPointer params[]) {

	if (check("RiMakeCubeFaceEnvironmentV",RENDERMAN_ALL_BLOCKS)) return;	

	renderMan->RiMakeCubeFaceEnvironmentV(px,nx,py,ny,pz,nz,tex,fov,filterfunc,swidth,twidth,n,tokens,params);
}

EXTERN(RtVoid)
RiMakeShadow (const char *pic, const char *tex, ...) {
	va_list	args;

	va_start(args,tex);
	getArgs(args);
	RiMakeShadowV(pic,tex,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)
    RiMakeShadowV (const char *pic, const char *tex,
	RtInt n, RtToken tokens[], RtPointer params[]) {

	if (check("RiMakeShadow",RENDERMAN_ALL_BLOCKS)) return;	

	renderMan->RiMakeShadowV(pic,tex,n,tokens,params);
}

EXTERN(RtVoid)
	RiMakeBrickMap (int n,const char **src, const char *dest, ...) {
	va_list	args;

	va_start(args,dest);
	getArgs(args);
	RiMakeBrickMapV(n,src,dest,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)
	RiMakeBrickMapV(int nb,const char **src, const char *dest,RtInt n, RtToken tokens[], RtPointer params[]) {

	if (check("RiMakeBrickMap",RENDERMAN_ALL_BLOCKS)) return;	

	renderMan->RiMakeBrickMapV(nb,src,dest,n,tokens,params);
}

EXTERN(RtVoid)
RiErrorHandler (const RtErrorHandler handler) {
	renderMan->RiErrorHandler(handler);
}

EXTERN(RtVoid)
RiErrorIgnore (RtInt code, RtInt severity, const char *message) {
	if ((severity == RIE_ERROR) || (severity == RIE_SEVERE)) {
		RiLastError = code;
	}
}

EXTERN(RtVoid)
RiErrorPrint (RtInt code, RtInt severity, const char *message) {
	if (severity == RIE_SEVERE) {
		// Severe errors must still abort

		fprintf(stderr,"%s",message);
		fflush(stderr);

		RiLastError = code;

		exit(-1);
	} else if (severity == RIE_ERROR) {
		fprintf(stderr,"%s",message);
		fflush(stderr);
		
		RiLastError = code;
	} else {
		fprintf(stdout,"%s",message);
		fflush(stdout);
	}
}

EXTERN(RtVoid)
RiErrorAbort (RtInt code, RtInt severity, const char *message) {
	if ((severity == RIE_ERROR) || (severity == RIE_SEVERE)) {
		RiLastError = code;
		
		exit(-1);
	}
}


///////////////////////////////////////////////////////////////////////////////////////
//
//  Resource related functions
//
EXTERN(RtVoid)	RiResource(RtToken handle, RtToken type,...) {
	va_list	args;

	va_start(args,type);
	getArgs(args);
	RiResourceV(handle,type,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)	RiResourceV(RtToken handle, RtToken type,RtInt n, RtToken tokens[], RtPointer parms[]) {
	if (check("RiResource",VALID_ATTRIBUTE_BLOCKS | VALID_XFORM_BLOCKS)) return;

	renderMan->RiResourceV(handle,type,n,tokens,parms);
}

EXTERN(RtVoid)	RiResourceBegin(void) {
	if (check("RiResourceBegin",VALID_ATTRIBUTE_BLOCKS | VALID_XFORM_BLOCKS)) return;

	blocks.push(currentBlock);
	currentBlock	=	RENDERMAN_RESOURCE_BLOCK;
	
	renderMan->RiResourceBegin();
}


EXTERN(RtVoid)	RiResourceEnd(void) {
	if (check("RiResourceEnd",RENDERMAN_RESOURCE_BLOCK)) return;

	if (currentBlock != RENDERMAN_RESOURCE_BLOCK) {
		error(CODE_NESTING,"Matching RiResourceBegin not found\n");
		return;
	}

	renderMan->RiResourceEnd();

	currentBlock	=	blocks.pop();	
}

///////////////////////////////////////////////////////////////////////////////////////
//
//  Archieving functions
//
EXTERN(RtArchiveHandle)	RiArchiveBegin(RtToken name, ...) {
	RtArchiveHandle	handle;
	va_list			args;

	va_start(args,name);
	getArgs(args);
	handle	=	RiArchiveBeginV(name,nTokens,tokens,values);
	va_end(args);

	return handle;
}

EXTERN(RtArchiveHandle)	RiArchiveBeginV(RtToken name, RtInt n, RtToken tokens[], RtPointer parms[]) {

	//if (check("RiArchiveBegin",RENDERMAN_FRAME_BLOCK | RENDERMAN_WORLD_BLOCK | RENDERMAN_ATTRIBUTE_BLOCK | RENDERMAN_XFORM_BLOCK | RENDERMAN_SOLID_PRIMITIVE_BLOCK | RENDERMAN_RESOURCE_BLOCK | RENDERMAN_ARCHIVE_BLOCK)) return NULL;
	// Archives should be allowed anywhere
	if (check("RiArchiveBegin",RENDERMAN_ALL_BLOCKS)) return NULL;


	blocks.push(currentBlock);
	currentBlock	=	RENDERMAN_ARCHIVE_BLOCK;
	
	// Keep track of the nesting count
	archiveNesting++;

	// Always call the current renderMan
	return (RtArchiveHandle) renderMan->RiArchiveBeginV(name,n,tokens,parms);
}

EXTERN(RtVoid)			RiArchiveEnd(void) {
	
	if (check("RiArchiveEnd",RENDERMAN_ARCHIVE_BLOCK)) return;

	if (currentBlock != RENDERMAN_ARCHIVE_BLOCK) {
		error(CODE_NESTING,"Matching RiResourceBegin not found\n");
		return;
	}

	// Decrease the nesting and recover the original context
	archiveNesting--;
	if (archiveNesting == 0) {
		if (savedRenderMan != NULL)	{
			delete renderMan;
			renderMan	=	savedRenderMan;
		}
	}

	renderMan->RiArchiveEnd();
	
	currentBlock	=	blocks.pop();	
}

///////////////////////////////////////////////////////////////////////////////////////
//
//  Conditional evaluation functions
//
EXTERN(RtVoid)			RiIfBegin(const char *expr, ...) {
	va_list	args;

	va_start(args,expr);
	getArgs(args);
	RiIfBeginV(expr,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)			RiIfBeginV(const char *expr, RtInt n, RtToken tokens[], RtPointer parms[]) {
	
	// Do not check for scope
	renderMan->RiIfBeginV(expr,n,tokens,parms);
}

EXTERN(RtVoid)			RiElseIf(const char *expr, ...) {
	va_list	args;

	va_start(args,expr);
	getArgs(args);
	RiElseIfV(expr,nTokens,tokens,values);
	va_end(args);
}

EXTERN(RtVoid)			RiElseIfV(const char *expr, RtInt n, RtToken tokens[], RtPointer parms[]) {
	
	// Do not check for scope
	renderMan->RiElseIfV(expr,n,tokens,parms);}

EXTERN(RtVoid)			RiElse(void) {

	// Do not check for scope
	renderMan->RiElse();
}

EXTERN(RtVoid)			RiIfEnd(void) {
	
	// Do not check for scope
	renderMan->RiIfEnd();
}





///////////////////////////////////////////////////////////////////////////////////////
//
//  Archieve reading functions
//
EXTERN(RtVoid)
RiArchiveRecord (RtToken type, const char *format, ...) {
	va_list	args;

	va_start(args,format);

	renderMan->RiArchiveRecord(type,format,args);

	va_end(args);
}

EXTERN(RtVoid)
RiReadArchive (RtString filename, RtArchiveCallback callback, ...) {
	va_list	args;

	va_start(args,callback);
	getArgs(args);
	RiReadArchiveV(filename,callback,nTokens,tokens,values);
	va_end(args);

}

EXTERN(RtVoid)
    RiReadArchiveV (RtString filename, RtArchiveCallback callback,
	int n, RtToken tokens[], RtPointer params[]) {

	if (check("RiReadArchive",RENDERMAN_ALL_BLOCKS)) return;

	renderMan->RiReadArchiveV(filename,callback,n,tokens,params);
}

