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
//  File				:	ribOut.cpp
//  Classes				:	CRibOut
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include <string.h>
#include <time.h>
#include <math.h>

#include "ribOut.h"
#include "common/os.h"
#include "ri_config.h"
#include "ri.h"
#include "error.h"
#include "variable.h"

// This is the size of the temporary buffer we use before going to the file
const	int	ribOutScratchSize	=	1000;

// Options for rib
int	preferCompressedRibOut		=	FALSE;


static	const char	*getFilter(float (*function)(float,float,float,float)) {
	if (function == RiGaussianFilter) {
		return	RI_GAUSSIANFILTER;
	} else if (function == RiBoxFilter) {
		return	RI_BOXFILTER;
	} else if (function == RiTriangleFilter) {
		return	RI_TRIANGLEFILTER;
	} else if (function == RiCatmullRomFilter) {
		return	RI_CATMULLROMFILTER;
	} else if (function == RiBlackmanHarrisFilter) {
		return	RI_BLACKMANHARRISFILTER;
	} else if (function == RiMitchellFilter) {
		return	RI_MITCHELLFILTER;
	} else if (function == RiSincFilter) {
		return	RI_SINCFILTER;
	} else if (function == RiBesselFilter) {
		return  RI_BESSELFILTER;
	} else if (function == RiDiskFilter) {
		return  RI_DISKFILTER;
	} else {
		return	RI_GAUSSIANFILTER;
	}
}

CRibOut::CRibAttributes::CRibAttributes() {
	uStep	=	3;
	vStep	=	3;
	next	=	NULL;
}

CRibOut::CRibAttributes::CRibAttributes(CRibAttributes *a) {
	this[0]		=	a[0];
	this->next	=	a;
}

CRibOut::CRibAttributes::~CRibAttributes() {
}

CRibOut::CRibOut(const char *n) : CRiInterface() {
	struct tm	*newtime;
	time_t		aclock;

	time( &aclock );
	newtime				=	localtime( &aclock );

	outName				=	strdup(n);
	if (*outName == '|') {
		outFile				=	popen(outName+1,"w");
		outputCompressed	=	FALSE;
		outputIsPipe		=	TRUE;
	} else {

#ifdef HAVE_ZLIB

		if (	(strstr(outName,".Z") != NULL)		|| 
				(strstr(outName,".zip") != NULL)	|| 
				(strstr(outName,".z") != NULL)		||
				(preferCompressedRibOut == TRUE) ) {
			outFile				=	(FILE *) gzopen(outName,"wb");
			outputCompressed	=	TRUE;
		} else {
			outFile				=	fopen(outName,"w");
			outputCompressed	=	FALSE;
		}
#else
		outFile				=	fopen(outName,"w");
		outputCompressed	=	FALSE;
#endif
		
		outputIsPipe		=	FALSE;
	}
	declaredVariables	=	new CTrie<CVariable *>;
	numLightSources		=	1;
	numObjects			=	1;
	attributes			=	new CRibAttributes;
	scratch				=	new char[ribOutScratchSize];

	// Write a header
	out("## Pixie %d.%d.%d\n",VERSION_RELEASE,VERSION_BETA,VERSION_ALPHA);
	out("## Generated %s\n",asctime(newtime));

	declareDefaultVariables();
}

CRibOut::CRibOut(FILE *o) : CRiInterface() {
	struct tm	*newtime;
	time_t		aclock;

	time( &aclock );
	newtime				=	localtime( &aclock );

	outName				=	NULL;
	outFile				=	o;
	outputCompressed	=	FALSE;
	outputIsPipe		=	FALSE;
	declaredVariables	=	new CTrie<CVariable *>;
	numLightSources		=	1;
	numObjects			=	1;
	attributes			=	new CRibAttributes;
	scratch				=	new char[ribOutScratchSize];

	// Write a header
	out("## Pixie %d.%d.%d\n",VERSION_RELEASE,VERSION_BETA,VERSION_ALPHA);
	out("## Generated %s\n",asctime(newtime));

	declareDefaultVariables();
}

CRibOut::~CRibOut() {

	if (outName != NULL) {
		if (outputIsPipe) {
			pclose(outFile);
		} else {

#ifdef HAVE_ZLIB
			if (outputCompressed) {
				gzclose(outFile);
			} else {
				fclose(outFile);
			}
#else
			fclose(outFile);
#endif
		}

		free((void *) outName);
	}

	assert(attributes->next == NULL);

	delete attributes;
	declaredVariables->destroy();

	delete [] scratch;
}

void		CRibOut::RiDeclare(const char *name,const char *type) {
	out("Declare \"%s\" \"%s\"\n",name,type);
	declareVariable(name,type);
}

void		CRibOut::RiFrameBegin(int number) {
	out("FrameBegin %d\n",number);
}

void		CRibOut::RiFrameEnd(void) {
	out("FrameEnd\n");
}

void		CRibOut::RiWorldBegin(void) {
	out("WorldBegin\n");
}

void		CRibOut::RiWorldEnd(void) {
	out("WorldEnd\n");
}

void		CRibOut::RiFormat(int xres,int yres,float aspect) {
	out("Format %d %d %g\n",xres,yres,aspect);
}

void		CRibOut::RiFrameAspectRatio(float aspect) {
	out("FrameAspectRatio %g\n",aspect);
}

void		CRibOut::RiScreenWindow(float left,float right,float bot,float top) {
	out("ScreenWindow %g %g %g %g\n",left,right,bot,top);
}

void		CRibOut::RiCropWindow(float xmin,float xmax,float ymin,float ymax) {
	out("CropWindow %g %g %g %g\n",xmin,xmax,ymin,ymax);
}

void		CRibOut::RiProjectionV(const char *name,int n,const char *tokens[],const void *params[]) {
	out("Projection \"%s\" ",name);
	writePL(n,tokens,params);
}

void		CRibOut::RiClipping(float hither,float yon) {
	out("Clipping %g %g\n",hither,yon);
}

void		CRibOut::RiClippingPlane(float x,float y,float z,float nx,float ny,float nz) {
	out("ClippingPlane %g %g %g %g %g %g\n",x,y,z,nx,ny,nz);
}

void		CRibOut::RiDepthOfField(float fstop,float focallength,float focaldistance) {
	out("DepthOfField %g %g %g\n",fstop,focallength,focaldistance);
}

void		CRibOut::RiShutter(float smin,float smax) {
	out("Shutter %g %g\n",smin,smax);
}

void		CRibOut::RiPixelVariance(float variance) {
	out("PixelVariance %g\n",variance);
}

void		CRibOut::RiPixelSamples(float xsamples,float ysamples) {
	out("PixelSamples %g %g\n",xsamples,ysamples);
}

void		CRibOut::RiPixelFilter(float (*function)(float,float,float,float),float xwidth,float ywidth) {
	if (function == RiGaussianFilter) {
		out("PixelFilter \"%s\" %g %g\n",RI_GAUSSIANFILTER,xwidth,ywidth);
	} else if (function == RiBoxFilter) {
		out("PixelFilter \"%s\" %g %g\n",RI_BOXFILTER,xwidth,ywidth);
	} else if (function == RiTriangleFilter) {
		out("PixelFilter \"%s\" %g %g\n",RI_TRIANGLEFILTER,xwidth,ywidth);
	} else if (function == RiCatmullRomFilter) {
		out("PixelFilter \"%s\" %g %g\n",RI_CATMULLROMFILTER,xwidth,ywidth);
	} else if (function == RiBlackmanHarrisFilter) {
		out("PixelFilter \"%s\" %g %g\n",RI_BLACKMANHARRISFILTER,xwidth,ywidth);
	} else if (function == RiMitchellFilter) {
		out("PixelFilter \"%s\" %g %g\n",RI_MITCHELLFILTER,xwidth,ywidth);
	} else if (function == RiSincFilter) {
		out("PixelFilter \"%s\" %g %g\n",RI_SINCFILTER,xwidth,ywidth);
	} else if (function == RiBesselFilter) {
		out("PixelFilter \"%s\" %g %g\n",RI_BESSELFILTER,xwidth,ywidth);
	} else if (function == RiDiskFilter) {
		out("PixelFilter \"%s\" %g %g\n",RI_DISKFILTER,xwidth,ywidth);
	} else {
		errorHandler(RIE_BADHANDLE,RIE_ERROR,"Failed to write custom filter function\n");
	}
}

void		CRibOut::RiExposure(float gain,float gamma) {
	out("Exposure %g %g\n",gain,gamma);
}

void		CRibOut::RiImagerV(const char *name,int n,const char *tokens[],const void *params[]) {
	out("Imager \"%s\" ",name);
	writePL(n,tokens,params);
}

void		CRibOut::RiQuantize(const char * type,int one,int qmin,int qmax,float ampl) {
	out("Quantize \"%s\" %d %d %d %g\n",type,one,qmin,qmax,ampl);
}

void		CRibOut::RiDisplayV(const char *name,const char * type,const char * mode,int n,const char *tokens[],const void *params[]) {
	out("Display \"%s\" \"%s\" \"%s\" ",name,type,mode);
	writePL(n,tokens,params);
}

void		CRibOut::RiCustomDisplayV(const char *name, RtToken mode, RtDisplayStartFunction, RtDisplayDataFunction, RtDisplayFinishFunction, RtInt n, RtToken tokens[], RtPointer params[]) {
	error(CODE_INCAPABLE,"Can not serialize custom displays.\n");
}

void		CRibOut::RiDisplayChannelV(const char *channel,int n,const char *tokens[],const void *params[]) {
	out("Display \"%s\" ",channel);
	writePL(n,tokens,params);
}

void		CRibOut::RiHiderV(const char * type,int n,const char *tokens[],const void *params[]) {
	out("Hider \"%s\" ",type);
	writePL(n,tokens,params);
}

void		CRibOut::RiColorSamples(int N,float *nRGB,float *RGBn) {
	int	i;

	out("ColorSamples [ ");

	for (i=0;i<N*3;i++) {
		out("%g ",nRGB[i]);
	}

	out("] [ ");

	for (i=0;i<N*3;i++) {
		out("%g ",RGBn[i]);
	}

	out("]\n");
}

void		CRibOut::RiRelativeDetail(float relativedetail) {
	out("RelativeDetail %g\n",relativedetail);
}



#define	optionCheckInt(__name,__num)																		\
	} else if (strcmp(tokens[i],__name) == 0) {																\
		const int		*val	=	(const int *) params[i];																\
		int		k;																							\
		out("Option \"%s\" \"%s\" [%i",name,tokens[i],val[0]);									\
		for (k=1;k<__num;k++) {																				\
			out(" %i",val[k]);																	\
		}																									\
		out("]\n");


#define	optionCheckFloat(__name,__num)																		\
	} else if (strcmp(tokens[i],__name) == 0) {																\
		const float	*val	=	(const float *) params[i];															\
		int		k;																							\
		out("Option \"%s\" \"%s\" [%g",name,tokens[i],val[0]);									\
		for (k=1;k<__num;k++) {																				\
			out(" %g",val[k]);																	\
		}																									\
		out("]\n");


#define	optionCheckString(__name)																			\
	} else if (strcmp(tokens[i],__name) == 0) {																\
		const char	*val	=	((const char **) params[i])[0];														\
		out("Option \"%s\" \"%s\" \"%s\"\n",name,tokens[i],val);

#define	optionEndCheck																						\
	} else {																								\
		CVariable	var;																					\
		if (parseVariable(&var,NULL,tokens[i]) == TRUE) {													\
			RiOption(name,var.name,params[i],RI_NULL);														\
		} else {																							\
			error(CODE_BADTOKEN,"Unknown %s option: \"%s\"\n",name,tokens[i]);								\
		}																									\
	}





void		CRibOut::RiOptionV(const char *name,int n,const char *tokens[],const void *params[]) {
	int	i;

	// Check the searchpath options
	if (strcmp(name,RI_SEARCHPATH) == 0) {
		for (i=0;i<n;i++) {
			if (FALSE) {
			optionCheckString(RI_ARCHIVE)
			optionCheckString(RI_PROCEDURAL)
			optionCheckString(RI_TEXTURE)
			optionCheckString(RI_SHADER)
			optionCheckString(RI_DISPLAY)
			optionCheckString(RI_RESOURCE)
			optionEndCheck
		}

	// Check the limit options
	} else if (strcmp(name,RI_LIMITS) == 0) {
		for (i=0;i<n;i++) {
			if (FALSE) {
			optionCheckInt(RI_BUCKETSIZE,2)
			optionCheckInt(RI_METABUCKETS,2)
			optionCheckInt(RI_INHERITATTRIBUTES,1)
			optionCheckInt(RI_GRIDSIZE,1)
			optionCheckInt(RI_EYESPLITS,1)
			optionCheckInt(RI_TEXTUREMEMORY,1)
			optionCheckInt(RI_BRICKMEMORY,1)
			optionEndCheck
		}
	// Check the hider options
	} else if (strcmp(name,RI_HIDER) == 0) {
		for (i=0;i<n;i++) {
			if (FALSE) {
			optionCheckFloat(RI_JITTER,1)	//GSHTODO: should be INT
			optionCheckInt(RI_FALSECOLOR,1)
			optionCheckInt(RI_EMIT,1)
			optionCheckString(RI_DEPTHFILTER)
			optionEndCheck
		}

	// Check the trace options
	} else if (strcmp(name,RI_TRACE) == 0) {
		for (i=0;i<n;i++) {
			if (FALSE) {
			optionCheckInt(RI_MAXDEPTH,1)
			optionEndCheck
		}

	// Check the io options
	} else if (strcmp(name,RI_STATISTICS) == 0) {
		for (i=0;i<n;i++) {
			if (FALSE) {
			optionCheckInt(RI_ENDOFFRAME,1)
			optionCheckString(RI_FILELOG)
			optionCheckInt(RI_PROGRESS,1)
			optionEndCheck
		}
	// Check for rib compression / output options
	} else if (strcmp(name,RI_RIB) == 0) {
		for (i=0;i<n;i++) {
			if (FALSE) {
			} else if (strcmp(tokens[i],RI_COMPRESSION) == 0) {
				const char	*val	=	((const char **) params[i])[0];
				if (strcmp(val,"gzip") == 0) {
					preferCompressedRibOut	=	TRUE;
				} else if (strcmp(val,"none") == 0) {
					preferCompressedRibOut	=	FALSE;
				} else {
					error(CODE_BADTOKEN,"Unknown compression type \"%s\"\n",val);
				}
			optionEndCheck
		}
	} else {
		error(CODE_BADTOKEN,"Unknown option: \"%s\"\n",name);
	}
}

#undef optionCheckInt
#undef optionCheckFloat
#undef optionCheckString
#undef optionEnd


void		CRibOut::RiAttributeBegin(void) {
	out("AttributeBegin\n");

	attributes	=	new CRibAttributes(attributes);
}

void		CRibOut::RiAttributeEnd(void) {
	CRibAttributes	*old	=	attributes;

	out("AttributeEnd\n");

	attributes		=	attributes->next;
	delete old;
}

void		CRibOut::RiColor(float *Cs) {
	out("Color [%g %g %g]\n",Cs[0],Cs[1],Cs[2]);
}

void		CRibOut::RiOpacity(float *Cs) {
	out("Opacity [%g %g %g]\n",Cs[0],Cs[1],Cs[2]);
}

void		CRibOut::RiTextureCoordinates(float s1,float t1,float s2,float t2,float s3,float t3,float s4,float t4) {
	out("TextureCoordinates [%g %g %g %g %g %g %g %g]\n",s1,t1,s2,t2,s3,t3,s4,t4);
}

void		*CRibOut::RiLightSourceV(const char *name,int n,const char *tokens[],const void *params[]) {
	out("LightSource \"%s\" %d ",name,numLightSources);
	writePL(n,tokens,params);

	return (void *) (uintptr_t) numLightSources++;
}

void		*CRibOut::RiAreaLightSourceV(const char *name,int n,const char *tokens[],const void *params[]) {
	out("AreaLightSource \"%s\" %d ",name,numLightSources);
	writePL(n,tokens,params);

	return (void *) (uintptr_t) numLightSources++;
}

void		CRibOut::RiIlluminate(const void *light,int onoff) {
	out("Illuminate %d %d\n",light,onoff);
}

void		CRibOut::RiSurfaceV(const char *name,int n,const char *tokens[],const void *params[]) {
	out("Surface \"%s\" ",name);
	writePL(n,tokens,params);
}

void		CRibOut::RiAtmosphereV(const char *name,int n,const char *tokens[],const void *params[]) {
	out("Atmosphere \"%s\" ",name);
	writePL(n,tokens,params);
}

void		CRibOut::RiInteriorV(const char *name,int n,const char *tokens[],const void *params[]) {
	out("Interior \"%s\" ",name);
	writePL(n,tokens,params);
}

void		CRibOut::RiExteriorV(const char *name,int n,const char *tokens[],const void *params[]) {
	out("Exterior \"%s\" ",name);
	writePL(n,tokens,params);
}

void		CRibOut::RiShadingRate(float size) {
	out("ShadingRate %g\n",size);
}

void		CRibOut::RiShadingInterpolation(const char * type) {
	out("ShadingInterpolation \"%s\"\n",type);
}

void		CRibOut::RiMatte(int onoff) {
	out("Matte %d\n",onoff);
}

void		CRibOut::RiBound(float *bound) {
	out("Bound [%g %g %g %g %g %g]\n",bound[0],bound[1],bound[2],bound[3],bound[4],bound[5]);
}

void		CRibOut::RiDetail(float *bound) {
	out("Detail [%g %g %g %g %g %g]\n",bound[0],bound[1],bound[2],bound[3],bound[4],bound[5]);
}

void		CRibOut::RiDetailRange(float minvis,float lowtran,float uptran,float maxvis) {
	out("DetailRange %g %g %g %g\n",minvis,lowtran,uptran,maxvis);
}

void		CRibOut::RiGeometricApproximation(const char * type,float value) {
	out("GeometricApproximation \"%s\" %g\n",type,value);
}

void		CRibOut::RiGeometricRepresentation(const char * type) {
	out("GeometricRepresentation \"%s\"\n",type);
}

void		CRibOut::RiOrientation(const char * orientation) {
	out("Orientation \"%s\"\n",orientation);
}

void		CRibOut::RiReverseOrientation(void) {
	out("ReverseOrientation\n");
}

void		CRibOut::RiSides(int nsides) {
	out("Sides %d\n",nsides);
}

void		CRibOut::RiIdentity(void) {
	out("Identity\n");
}

void		CRibOut::RiTransform(float transform[][4]) {
	out("Transform [%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g]\n",transform[0][0],transform[0][1],transform[0][2],transform[0][3]
																					,transform[1][0],transform[1][1],transform[1][2],transform[1][3]
																					,transform[2][0],transform[2][1],transform[2][2],transform[2][3]
																					,transform[3][0],transform[3][1],transform[3][2],transform[3][3]);
}

void		CRibOut::RiConcatTransform(float transform[][4]) {
	out("ConcatTransform [%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g]\n",transform[0][0],transform[0][1],transform[0][2],transform[0][3]
																					,transform[1][0],transform[1][1],transform[1][2],transform[1][3]
																					,transform[2][0],transform[2][1],transform[2][2],transform[2][3]
																					,transform[3][0],transform[3][1],transform[3][2],transform[3][3]);
}

void		CRibOut::RiPerspective(float fov) {
	out("Perspective %g\n",fov);
}

void		CRibOut::RiTranslate(float dx,float dy,float dz) {
		out("Translate %g %g %g\n",dx,dy,dz);
}

void		CRibOut::RiRotate(float angle,float dx,float dy,float dz) {
	out("Rotate %g %g %g %g\n",angle,dx,dy,dz);
}

void		CRibOut::RiScale(float dx,float dy,float dz) {
	out("Scale %g %g %g\n",dx,dy,dz);
}

void		CRibOut::RiSkew(float angle,float dx1,float dy1,float dz1,float dx2,float dy2,float dz2) {
	out("Skew %g %g %g %g %g %g %g\n",angle,dx1,dy1,dz1,dx2,dy2,dz2);
}

void		CRibOut::RiDeformationV(const char *name,int n,const char *tokens[],const void *params[]) {
	out("Deformation \"%s\" ",name);
	writePL(n,tokens,params);
}

void		CRibOut::RiDisplacementV(const char *name,int n,const char *tokens[],const void *params[]) {
	out("Displacement \"%s\" ",name);
	writePL(n,tokens,params);
}

void		CRibOut::RiCoordinateSystem(const char * space) {
	out("CoordinateSystem \"%s\"\n",space);
}

void		CRibOut::RiCoordSysTransform(const char * space) {
	out("CoordSysTransform \"%s\"\n",space);
}

RtPoint *		CRibOut::RiTransformPoints(const char * fromspace,const char * tospace,int npoints,RtPoint *points) {
	errorHandler(RIE_SYSTEM,RIE_ERROR,"Failed to output TransformPoints\n");
	return NULL;
}

void		CRibOut::RiTransformBegin(void) {
	out("TransformBegin\n");
}

void		CRibOut::RiTransformEnd(void) {
	out("TransformEnd\n");
}


#define	attributeCheckInt(__name,__num)																		\
	} else if (strcmp(tokens[i],__name) == 0) {																\
		const int	*val	=	(const int *) params[i];																\
		int			k;																							\
		out("Attribute \"%s\" \"%s\" [%i",name,tokens[i],val[0]);								\
		for (k=1;k<__num;k++) {																				\
			out(" %i",val[k]);																	\
		}																									\
		out("]\n");


#define	attributeCheckFloat(__name,__num)																	\
	} else if (strcmp(tokens[i],__name) == 0) {																\
		const float	*val	=	(const float *) params[i];															\
		int			k;																							\
		out("Attribute \"%s\" \"%s\" [%g",name,tokens[i],val[0]);								\
		for (k=1;k<__num;k++) {																				\
			out(" %g",val[k]);																	\
		}																									\
		out("]\n");


#define	attributeCheckString(__name)																		\
	} else if (strcmp(tokens[i],__name) == 0) {																\
		const char	*val	=	((const char **) params[i])[0];														\
		out("Attribute \"%s\" \"%s\" \"%s\"\n",name,tokens[i],val);

#define	attributeEndCheck																					\
	} else {																								\
		CVariable	var;																					\
		if (parseVariable(&var,NULL,tokens[i]) == TRUE) {													\
			RiAttribute(name,var.name,params[i],RI_NULL);													\
		} else {																							\
			error(CODE_BADTOKEN,"Unknown %s option: \"%s\"\n",name,tokens[i]);								\
		}																									\
	}



void		CRibOut::RiAttributeV(const char *name,int n,const char *tokens[],const void *params[]) {
	int	i;

	if (strcmp(name,RI_DICE) == 0) {
		for (i=0;i<n;i++) {
			if (FALSE) {
			attributeCheckInt(RI_NUMPROBES,2)
			attributeCheckInt(RI_MINSUBDIVISION,1)
			attributeCheckInt(RI_MAXSUBDIVISION,1)				
			attributeCheckInt(RI_MINSPLITS,1)				
			attributeCheckFloat(RI_BOUNDEXPAND,1)				
			attributeCheckInt(RI_BINARY,1)
			attributeCheckInt(RI_RASTERORIENT,1)
			attributeEndCheck
		}
	} else if (strcmp(name,RI_DISPLACEMENTBOUND) == 0) {
		for (i=0;i<n;i++) {
			if (FALSE) {
			attributeCheckFloat(RI_SPHERE,1)
			attributeCheckString(RI_COORDINATESYSYTEM)
			attributeEndCheck
		}
	} else if (strcmp(name,RI_TRACE) == 0) {
		for (i=0;i<n;i++) {
			if (FALSE) {
			attributeCheckInt(RI_DISPLACEMENTS,1)
			attributeCheckFloat(RI_BIAS,1)
			attributeCheckInt(RI_MAXDIFFUSEDEPTH,1)
			attributeCheckInt(RI_MAXSPECULARDEPTH,1)
			attributeEndCheck
		}
	// Check the irradiance cache options
	} else if (strcmp(name,RI_IRRADIANCE) == 0) {
		for (i=0;i<n;i++) {
			if (FALSE) {
			attributeCheckString(RI_HANDLE)
			attributeCheckString(RI_FILEMODE)
			attributeCheckFloat(RI_MAXERROR,1)
			attributeEndCheck
		}
	} else if (strcmp(name,RI_PHOTON) == 0) {
		for (i=0;i<n;i++) {
			if (FALSE) {
			attributeCheckString(RI_GLOBALMAP)
			attributeCheckString(RI_CAUSTICMAP)
			attributeCheckString(RI_SHADINGMODEL)
			attributeCheckFloat(RI_IOR,1)
			attributeCheckInt(RI_ESTIMATOR,1)
			attributeCheckInt(RI_ILLUMINATEFRONT,1)
			attributeEndCheck
		}
	} else if (strcmp(name,RI_VISIBILITY) == 0) {
		for (i=0;i<n;i++) {
			if (FALSE) {
			attributeCheckInt(RI_TRANSMISSION,1)
			attributeCheckInt(RI_DIFFUSE,1)
			attributeCheckInt(RI_SPECULAR,1)
			attributeCheckInt(RI_CAMERA,1)
			attributeCheckInt(RI_TRACE,1)
			attributeCheckInt(RI_PHOTON,1)
			attributeEndCheck
		}
	} else if (strcmp(name,RI_SHADE) == 0) {
		for (i=0;i<n;i++) {
			if (FALSE) {
			attributeCheckString(RI_TRANSMISSIONHITMODE)
			attributeCheckString(RI_DIFFUSEHITMODE)
			attributeCheckString(RI_SPECULARHITMODE)
			attributeEndCheck
		}
	} else if (strcmp(name,RI_IDENTIFIER) == 0) {
		for (i=0;i<n;i++) {
			if (FALSE) {
			attributeCheckString(RI_NAME)
			attributeEndCheck
		}
	} else if (strcmp(name,RI_CULL) == 0) {
		for (i=0;i<n;i++) {
			if (FALSE) {
			attributeCheckInt(RI_HIDDEN,1)
			attributeCheckInt(RI_BACKFACING,1)
			attributeEndCheck
		}
	}
}


#undef	attributeCheckInt
#undef	attributeCheckFloat
#undef	attributeCheckString
#undef	attributeEndCheck


void		CRibOut::RiPolygonV(int nvertices,int n,const char *tokens[],const void *params[]) {
	out("Polygon ");
	writePL(nvertices,nvertices,nvertices,1,n,tokens,params);
}

void		CRibOut::RiGeneralPolygonV(int nloops,int *nverts,int n,const char *tokens[],const void *params[]) {
	int	i;
	int	nvertices=0;

	out("GeneralPolygon [");
	for (i=0;i<nloops;i++) {
		nvertices	+=	nverts[i];
		out("%d ",nverts[i]);
	}
	out("] ");

	writePL(nvertices,nvertices,nvertices,1,n,tokens,params);
}

void		CRibOut::RiPointsPolygonsV(int npolys,int *nverts,int *verts,int n,const char *tokens[],const void *params[]) {
	int	i;
	int	nvertices		=	0;
	int	mvertex			=	0;

	out("PointsPolygons [");

	for (i=0;i<npolys;i++) {
		nvertices	+=	nverts[i];
		out("%d ",nverts[i]);
	}
	out("] ");

	out("[");
	for (i=0;i<nvertices;i++) {
		mvertex		=	max(mvertex,verts[i]);
		out("%d ",verts[i]);
	}
	out("] ");
	mvertex++;

	writePL(mvertex,mvertex,nvertices,npolys,n,tokens,params);
}

void		CRibOut::RiPointsGeneralPolygonsV(int npolys,int *nloops,int *nverts,int *verts,int n,const char *tokens[],const void *params[]) {
	int	i,j;
	int	snverts		=	0;
	int	sverts		=	0;
	int	nvertices	=	0;
	int	k			=	0;

	out("PointsGeneralPolygons [");
	for (i=0;i<npolys;i++) {
		snverts	+=	nloops[i];
		out("%d ",nloops[i]);
		for (j=0;j<nloops[i];j++,k++) {
			sverts	+=	nverts[k];
		}
	}
	out("] ");

	out("[");
	for (k=0,i=0;i<npolys;i++) {
		for (j=0;j<nloops[i];j++,k++) {
			out("%d ",nverts[k]);
		}
	}
	out("] ");

	out("[");
	for (i=0;i<sverts;i++) {
		nvertices	=	max(nvertices,verts[i]+1);
		out("%d ",verts[i]);
	}
	out("] ");

	writePL(nvertices,nvertices,sverts,npolys,n,tokens,params);
}

void		CRibOut::RiBasis(float ubasis[][4],int ustep,float vbasis[][4],int vstep) {
	if ((ubasis == RiBezierBasis || ubasis == RiBSplineBasis || ubasis == RiCatmullRomBasis || ubasis == RiHermiteBasis || ubasis == RiPowerBasis) &&
		(vbasis == RiBezierBasis || vbasis == RiBSplineBasis || vbasis == RiCatmullRomBasis || vbasis == RiHermiteBasis || vbasis == RiPowerBasis)) {
	
		const char *ubasis_str;
		if (ubasis == RiBezierBasis)
			ubasis_str = "bezier";
		else if (ubasis == RiBSplineBasis)
			ubasis_str = "b-spline";
		else if (ubasis == RiCatmullRomBasis)
			ubasis_str = "catmull-rom";
		else if (ubasis == RiHermiteBasis)
			ubasis_str = "hermite";
		else if (ubasis == RiPowerBasis)
			ubasis_str = "power";
		
		const char *vbasis_str;
		if (vbasis == RiBezierBasis)
			vbasis_str = "bezier";
		else if (vbasis == RiBSplineBasis)
			vbasis_str = "b-spline";
		else if (vbasis == RiCatmullRomBasis)
			vbasis_str = "catmull-rom";
		else if (vbasis == RiHermiteBasis)
			vbasis_str = "hermite";
		else if (vbasis == RiPowerBasis)
			vbasis_str = "power";
		
		out("Basis \"%s\" %d \"%s\" %d\n",
			ubasis_str,ustep,
			vbasis_str,vstep);
		attributes->uStep	=	ustep;
		attributes->vStep	=	vstep;
		return;
	}
	out("Basis [%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g] %d [%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g] %d\n"
		,ubasis[0][0],ubasis[0][1],ubasis[0][2],ubasis[0][3]
		,ubasis[1][0],ubasis[1][1],ubasis[1][2],ubasis[1][3]
		,ubasis[2][0],ubasis[2][1],ubasis[2][2],ubasis[2][3]
		,ubasis[3][0],ubasis[3][1],ubasis[3][2],ubasis[3][3],ustep
		,vbasis[0][0],vbasis[0][1],vbasis[0][2],vbasis[0][3]
		,vbasis[1][0],vbasis[1][1],vbasis[1][2],vbasis[1][3]
		,vbasis[2][0],vbasis[2][1],vbasis[2][2],vbasis[2][3]
		,vbasis[3][0],vbasis[3][1],vbasis[3][2],vbasis[3][3],vstep);
	attributes->uStep	=	ustep;
	attributes->vStep	=	vstep;
}

void		CRibOut::RiPatchV(const char * type,int n,const char *tokens[],const void *params[]) {
	int	uver,vver;

	if (strcmp(type,RI_BILINEAR) == 0)		{	uver	=	2;	vver	=	2;	}
	else if (strcmp(type,RI_BICUBIC) == 0)	{	uver	=	4;	vver	=	4;	}
	else {
		char	tmp[512];

		sprintf(tmp,"Unknown patch type: \"%s\"\n",type);
		errorHandler(RIE_BADTOKEN,RIE_ERROR,tmp);
		return;
	}

	out("Patch \"%s\" ",type);
	writePL(uver*vver,4,4,1,n,tokens,params);
}

void		CRibOut::RiPatchMeshV(const char *type,int nu,const char * uwrap,int nv,const char * vwrap,int n,const char *tokens[],const void *params[]) {
	int	uw,vw;
	int	uver,vver;
	int	upatches,vpatches;

	if (strcmp(uwrap,RI_PERIODIC) == 0) {
		uw	=	TRUE;
	} else if ((strcmp(uwrap,RI_NONPERIODIC) == 0) || (strcmp(uwrap,RI_NOWRAP) == 0)) {
		uw	=	FALSE;
	} else {
		errorHandler(RIE_BADTOKEN,RIE_ERROR,"Wrapping mode unrecognized\n");
		return;
	}

	if (strcmp(vwrap,RI_PERIODIC) == 0) {
		vw	=	TRUE;
	} else if ((strcmp(vwrap,RI_NONPERIODIC) == 0) || (strcmp(vwrap,RI_NOWRAP) == 0)) {
		vw	=	FALSE;
	} else {
		errorHandler(RIE_BADTOKEN,RIE_ERROR,"Wrapping mode unrecognized\n");
		return;
	}

	uver	=	nu;
	vver	=	nv;

	if (strcmp(type,RI_BICUBIC) == 0) {
		if (uw)		{
			if ((uver % attributes->uStep) != 0) {
				errorHandler(RIE_CONSISTENCY,RIE_ERROR,"Unexpected number of u vertices\n");
				return;
			}

			upatches	=	(uver ) / attributes->uStep;
		} else {
			if (((uver - 4) % attributes->uStep) != 0) {
				errorHandler(RIE_CONSISTENCY,RIE_ERROR,"Unexpected number of u vertices\n");
				return;
			}

			upatches	=	((uver - 4) / attributes->uStep)+1;
		}

		if (vw)		{
			if ((vver % attributes->vStep) != 0) {
				errorHandler(RIE_CONSISTENCY,RIE_ERROR,"Unexpected number of v vertices\n");
				return;
			}

			vpatches	=	(vver) / attributes->vStep;
		} else {
			if (((vver - 4) % attributes->vStep) != 0) {
				errorHandler(RIE_CONSISTENCY,RIE_ERROR,"Unexpected number of v vertices\n");
				return;
			}

			vpatches	=	((vver - 4) / attributes->vStep)+1;
		}
	} else {
		if (uw)
			upatches	=	uver;
		else
			upatches	=	uver-1;

		if (vw)
			vpatches	=	vver;
		else
			vpatches	=	vver-1;
	}

	out("PatchMesh \"%s\" %i \"%s\" %i \"%s\" ",type,nu,uwrap,nv,vwrap);
	writePL(uver*vver,uver*vver,uver*vver,upatches*vpatches,n,tokens,params);
}

void		CRibOut::RiNuPatchV(int nu,int uorder,float *uknot,float umin,float umax,int nv,int vorder,float *vknot,float vmin,float vmax,int n,const char *tokens[],const void *params[]) {
	int	upatches		=	nu - uorder + 1;
	int	vpatches		=	nv - vorder + 1;
	int	i,uk,vk;

	out("NuPatch ");

	// Print the knot sequence
	uk = nu + uorder;
	vk = nv + vorder;
	out("%i %i [%g",nu,uorder,uknot[0]);
	for (i=1;i<uk;i++) out(" %g",uknot[i]);
	out("] %g %g ",umin,umax);

	out("%i %i [%g",nv,vorder,vknot[0]);
	for (i=1;i<vk;i++) out(" %g",vknot[i]);
	out("] %g %g ",vmin,vmax);

	writePL(nu*nv,(nu-uorder+2)*(nv-vorder+2),(nu-uorder+2)*(nv-vorder+2),upatches*vpatches,n,tokens,params);
}

void		CRibOut::RiTrimCurve(int nloops,int *ncurves,int *order,float *knot,float *amin,float *amax,int *n,float *u,float *v,float *w) {
	int	i,j,k,numCurves;

	// Write the ncurves
	out("TrimCurve [%d",ncurves[0]);
	numCurves	=	ncurves[0];
	for (i=1;i<nloops;i++) {
		out(" %d",ncurves[i]);
		numCurves	+=	ncurves[i];
	}

	// Print the order for each curve
	out("] [%d",order[0]);
	for (i=1;i<numCurves;i++) out(" %d",order[i]);

	// Print the knot vector for each curve
	out("] [");
	for (k=0,i=0;i<numCurves;i++) {

		for (j=n[i]+order[i];j>0;j--,k++) {
			if (k == 0) {
				out("%g",knot[k]);
			} else {
				out(" %g",knot[k]);
			}
		}
	}

	// Print the parametric range for each curve
	out("] [%g",amin[0]);
	for (i=1;i<numCurves;i++) {
		out(" %g",amin[i]);
	}

	out("] [%g",amax[0]);
	for (i=1;i<numCurves;i++) {
		out(" %g",amax[i]);
	}

	// Print the number of vertices for each curve
	out("] [%d",n[0]);
	for (i=1;i<numCurves;i++) {
		out(" %d",n[i]);
	}

	// Print the vertices for each curve
	out("] [");
	for (k=0,i=0;i<numCurves;i++) {

		for (j=n[i];j>0;j--,k++) {
			if (k == 0) {
				out("%g",u[k]);
			} else {
				out(" %g",u[k]);
			}
		}
	}

	out("] [");
	for (k=0,i=0;i<numCurves;i++) {

		for (j=n[i];j>0;j--,k++) {
			if (k == 0) {
				out("%g",v[k]);
			} else {
				out(" %g",v[k]);
			}
		}
	}

	out("] [");
	for (k=0,i=0;i<numCurves;i++) {

		for (j=n[i];j>0;j--,k++) {
			if (k == 0) {
				out("%g",w[k]);
			} else {
				out(" %g",w[k]);
			}
		}
	}

	out("]\n");
}

void		CRibOut::RiSphereV(float radius,float zmin,float zmax,float thetamax,int n,const char *tokens[],const void *params[]) {
	out("Sphere %g %g %g %g ",radius,zmin,zmax,thetamax);
	writePL(4,4,4,1,n,tokens,params);
}

void		CRibOut::RiConeV(float height,float radius,float thetamax,int n,const char *tokens[],const void *params[]) {
	out("Cone %g %g %g ",height,radius,thetamax);
	writePL(4,4,4,1,n,tokens,params);
}

void		CRibOut::RiCylinderV(float radius,float zmin,float zmax,float thetamax,int n,const char *tokens[],const void *params[]) {
	out("Cylinder %g %g %g %g ",radius,zmin,zmax,thetamax);
	writePL(4,4,4,1,n,tokens,params);
}

void		CRibOut::RiHyperboloidV(float *point1,float *point2,float thetamax,int n,const char *tokens[],const void *params[]) {
	out("Hyperboloid %g %g %g %g %g %g %g ",point1[0],point1[1],point1[2],point2[0],point2[1],point2[2],thetamax);
	writePL(4,4,4,1,n,tokens,params);
}

void		CRibOut::RiParaboloidV(float rmax,float zmin,float zmax,float thetamax,int n,const char *tokens[],const void *params[]) {
	out("Paraboloid %g %g %g %g ",rmax,zmin,zmax,thetamax);
	writePL(4,4,4,1,n,tokens,params);
}

void		CRibOut::RiDiskV(float height,float radius,float thetamax,int n,const char *tokens[],const void *params[]) {
	out("Disk %g %g %g ",height,radius,thetamax);
	writePL(4,4,4,1,n,tokens,params);
}

void		CRibOut::RiTorusV(float majorrad,float minorrad,float phimin,float phimax,float thetamax,int n,const char *tokens[],const void *params[]) {
	out("Torus %g %g %g %g %g",majorrad,minorrad,phimin,phimax,thetamax);
	writePL(4,4,4,1,n,tokens,params);
}

void		CRibOut::RiProcedural(void * data,float *bound,void (*subdivfunc)(void *,float),void (*freefunc)(void *)) {
	errorHandler(RIE_UNIMPLEMENT,RIE_ERROR,"Failed to output procedural geometry\n");
}

void		CRibOut::RiGeometryV(const char * type,int n,const char *tokens[],const void *params[]) {
	errorHandler(RIE_UNIMPLEMENT,RIE_ERROR,"Failed to output optional geometry\n");
}

void		CRibOut::RiCurvesV(const char * degree,int ncurves,int nverts[],const char * wrap,int n,const char *tokens[],const void *params[]) {
	int	i;
	int	nvertices	=	0;
	int	nvaryings	=	0;
	int	wrapadd;
	
	if (strcmp(wrap,RI_PERIODIC) == 0) {
		wrapadd	=	0;
	} else {
		wrapadd	=	1;
	}
					
	out("Curves \"%s\" [",degree);

	if (strcmp(degree,RI_LINEAR) == 0) {
		for (i=0;i<ncurves;i++) {
			nvertices	+=	nverts[i];
			out("%d ",nverts[i]);
		}

		nvaryings		=	nvertices;
	} else if (strcmp(degree,RI_CUBIC) == 0) {
		for (i=0;i<ncurves;i++) {
			int j		=	(nverts[i] - 4) / attributes->vStep + 1;
			nvertices	+=	nverts[i];
			nvaryings	+=	j + wrapadd;
			out("%d ",nverts[i]);
		}
	}

	out("] \"%s\" ",wrap);

	writePL(nvertices,nvaryings,nvaryings,ncurves,n,tokens,params);
}

void		CRibOut::RiPointsV(int npts,int n,const char *tokens[],const void *params[]) {
	out("Points ");
	writePL(npts,npts,npts,1,n,tokens,params);
}

void		CRibOut::RiSubdivisionMeshV(const char * scheme,int nfaces,int nvertices[],int vertices[],int ntags,const char * tags[],int nargs[],int intargs[],float floatargs[],int n,const char *tokens[],const void *params[]) {
	int	numVertices;
	int	i,j;
	int	numInt,numFloat;
	int	numFacevaryings;

	for (i=0,j=0;i<nfaces;j+=nvertices[i],i++);
	numFacevaryings	=	j;

	for (numVertices=-1,i=0;i<j;i++) {
		if (vertices[i] > numVertices)	numVertices	=	vertices[i];
	}
	numVertices++;

	out("SubdivisionMesh \"%s\" [ ",scheme);
	for (i=0;i<nfaces;i++) {
		out("%d ",nvertices[i]);
	}

	out("] [ ");
	for (i=0;i<j;i++) {
		out("%d ",vertices[i]);
	}

	out("] [");
	for (i=0;i<ntags;i++) {
		out(" \"%s\" ",tags[i]);
	}

	out("] [");
	numInt		=	0;
	numFloat	=	0;
	for (i=0;i<ntags;i++) {
		out(" %d %d ",nargs[0],nargs[1]);
		numInt		+=	nargs[0];
		numFloat	+=	nargs[1];
		nargs		+=	2;
	}

	out("] [ ");
	for (i=0;i<numInt;i++) {
		out("%d ",intargs[i]);
	}

	out("] [ ");
	for (i=0;i<numFloat;i++) {
		out("%g ",floatargs[i]);
	}
	out("] ");

	writePL(numVertices,numVertices,numFacevaryings,nfaces,n,tokens,params);
}

void		CRibOut::RiBlobbyV(int nleaf,int ncode,int code[],int nflt,float flt[],int nstr,const char *str[],int n,const char *tokens[],const void *params[]) {
	errorHandler(RIE_UNIMPLEMENT,RIE_ERROR,"Blobby primitive is not implemented\n");
}

void		CRibOut::RiProcDelayedReadArchive(const char * data,float detail) {
}

void		CRibOut::RiProcRunProgram(const char * data,float detail) {
}

void		CRibOut::RiProcDynamicLoad(const char * data,float detail) {
}

void		CRibOut::RiProcFree(const char *) {
}

void		CRibOut::RiSolidBegin(const char * type) {
	out("SolidBegin \"%s\"\n",type);
}

void		CRibOut::RiSolidEnd(void) {
	out("SolidEnd\n");
}

void		*CRibOut::RiObjectBegin(void) {
	out("ObjectBegin %d\n",numObjects);

	return (void *) (uintptr_t) numObjects++;
}

void		CRibOut::RiObjectEnd(void) {
	out("ObjectEnd\n");
}

void		CRibOut::RiObjectInstance(const void *handle) {
	out("ObjectInstance %d\n",handle);
}

void		CRibOut::RiMotionBeginV(int N,float times[]) {
	int	i;

	out("MotionBegin [ ");
	for (i=0;i<N;i++) {
		out(" %g ",times[i]);
	}
	out("]\n");
}

void		CRibOut::RiMotionEnd(void) {
	out("MotionEnd\n");
}

void		CRibOut::RiMakeTextureV(const char *pic,const char *tex,const char * swrap,const char * twrap,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,const char *tokens[],const void *params[]) {
	out("MakeTexture \"%s\" \"%s\" \"%s\" \"%s\" \"%s\" %g %g ",pic,tex,swrap,twrap,getFilter(filterfunc),swidth,twidth);
	writePL(n,tokens,params);
}

void		CRibOut::RiMakeBumpV(const char *pic,const char *tex,const char * swrap,const char * twrap,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,const char *tokens[],const void *params[]) {
	out("MakeBump \"%s\" \"%s\" \"%s\" \"%s\" \"%s\" %g %g ",pic,tex,swrap,twrap,getFilter(filterfunc),swidth,twidth);
	writePL(n,tokens,params);
}

void		CRibOut::RiMakeLatLongEnvironmentV(const char *pic,const char *tex,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,const char *tokens[],const void *params[]) {
	out("MakeBump \"%s\" \"%s\" \"%s\" %g %g",pic,tex,getFilter(filterfunc),swidth,twidth);
	writePL(n,tokens,params);
}

void		CRibOut::RiMakeCubeFaceEnvironmentV(const char *px,const char *nx,const char *py,const char *ny,const char *pz,const char *nz,const char *tex,float fov,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,const char *tokens[],const void *params[]) {
	out("MakeCubeFaceEnvironment \"%s\" \"%s\" \"%s\" \"%s\" \"%s\" \"%s\" \"%s\" %g \"%s\" %g %g ",px,nx,py,ny,pz,nz,tex,fov,getFilter(filterfunc),swidth,twidth);
	writePL(n,tokens,params);
}

void		CRibOut::RiMakeShadowV(const char *pic,const char *tex,int n,const char *tokens[],const void *params[]) {
	out("MakeShadow \"%s\" \"%s\" ",pic,tex);
	writePL(n,tokens,params);
}

void		CRibOut::RiMakeBrickMapV(int n,const char **src,const char *dest,int numTokens,const char *tokens[],const void *params[]) {
	out("MakeBrickMap [");
	for(int i=0;i<n;i++) out("\"%s\" ",src[i]);
	out("] \"%s\" ",dest);
	writePL(numTokens,tokens,params);
}

void		CRibOut::RiErrorHandler(void (*handler)(int,int,const char *)) {
	errorHandler	=	handler;
}

void		CRibOut::RiArchiveRecord(const char * type,const char *format,va_list args) {
	if (strcmp(type,RI_COMMENT) == 0) {
		out("#");
		vout(format,args);
		out("\n");
	} else if (strcmp(type,RI_STRUCTURE) == 0) {
		out("##");
		vout(format,args);
		out("\n");
	} else if (strcmp(type,RI_VERBATIM) == 0) {
		vout(format,args);
		out("\n");
	} else {
		error(CODE_BADTOKEN,"Unknown record type: \"%s\"\n",type);
	}
}

void		CRibOut::RiReadArchiveV(const char *filename,void (*callback)(const char *,...),int n,const char *tokens[],const void *params[]) {
	out("ReadArchive \"%s\"\n",filename);
}

void		*CRibOut::RiArchiveBeginV(const char *name,int n,const char *tokens[],const void *parms[]) {
	out("ArchiveBegin \"%s\" ",name);
	writePL(n,tokens,parms);
	return NULL;
}

void		CRibOut::RiArchiveEnd(void) {
	out("ArchiveEnd\n");
}
	
void		CRibOut::RiResourceV(const char *handle,const char *type,int n,const char *tokens[],const void *parms[]) {
	out("Resource \"%s\" \"%s\" ",handle,type);
	writePL(n,tokens,parms);
}

void		CRibOut::RiResourceBegin(void) {
	out("ResourceBegin\n");
}

void		CRibOut::RiResourceEnd(void) {
	out("ResourceEnd\n");
}

void		CRibOut::RiIfBeginV(const char *expr,int n,const char *tokens[],const void *parms[]) {
	out("IfBegin \"%s\" ",expr);
	writePL(n,tokens,parms);
}

void		CRibOut::RiElseIfV(const char *expr,int n,const char *tokens[],const void *parms[]) {
	out("ElseIf \"%s\" ",expr);
	writePL(n,tokens,parms);
}

void		CRibOut::RiElse(void) {
	out("Else\n");
}

void		CRibOut::RiIfEnd(void) {
	out("IfEnd\n");
}


void		CRibOut::writePL(int numParameters,const char *tokens[],const void *vals[]) {
	int			i,j;
	const float	*f;
	const int	*iv;
	const char	**s;

	for (i=0;i<numParameters;i++) {
		CVariable	tmpVar;
		CVariable	*variable;

		if (declaredVariables->find(tokens[i],variable) == TRUE) {
retry:;

			out(" \"%s\" [",tokens[i]);

			switch(variable->type) {
			case TYPE_FLOAT:

				f	=	(float *) vals[i];
				for (j=variable->numItems;j>0;j--,f++) {
					out("%g ",f[0]);
				}
				break;
			case TYPE_COLOR:
			case TYPE_VECTOR:
			case TYPE_NORMAL:
			case TYPE_POINT:

				f	=	(float *) vals[i];
				for (j=variable->numItems;j>0;j--,f+=3) {
					out("%g %g %g ",f[0],f[1],f[2]);
				}
				break;
			case TYPE_MATRIX:

				f	=	(float *) vals[i];
				for (j=variable->numItems;j>0;j--,f+=16) {
					out("%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g ",f[0],f[1],f[2],f[3],f[4],f[5],f[6],f[7],f[8],f[9],f[10],f[11],f[12],f[13],f[14],f[15]);
				}
				break;
			case TYPE_QUAD:

				f	=	(float *) vals[i];
				for (j=variable->numItems;j>0;j--,f+=4) {
					out("%g %g %g %g ",f[0],f[1],f[2],f[3]);
				}
				break;
			case TYPE_DOUBLE:

				f	=	(float *) vals[i];
				for (j=variable->numItems;j>0;j--,f+=2) {
					out("%g %g ",f[0],f[1]);
				}
				break;
			case TYPE_STRING:

				s	=	(const char **) vals[i];
				for (j=variable->numItems;j>0;j--,s++) {
					out("\"%s\" ",s[0]);
				}

				break;
			case TYPE_INTEGER:
				iv	=	(int *) vals[i];
				for (j=variable->numItems;j>0;j--,iv++) {
					out("%d ",iv[0]);
				}
				break;
			default:
				break;
			}

			out("] ");
		} else {
			if (parseVariable(&tmpVar,NULL,tokens[i])) {
				variable	=	&tmpVar;
				goto retry;
			} else {
				char		tmp[512];

				sprintf(tmp,"Parameter \"%s\" not found\n",tokens[i]);
				errorHandler(RIE_BADTOKEN,RIE_ERROR,tmp);
			}
		}
	}

	// Print the final newline
	out("\n");
}

void		CRibOut::writePL(int numVertex,int numVarying,int numFaceVarying,int numUniform,int numParameters,const char *tokens[],const void *vals[]) {
	int			i,j;
	const float	*f;
	const char	**s;

#define	numItems(__dest,__var)						\
	switch(variable->container) {					\
	case CONTAINER_UNIFORM:							\
		__dest	=	__var->numItems*numUniform;		\
		break;										\
	case CONTAINER_VERTEX:							\
		__dest	=	__var->numItems*numVertex;		\
		break;										\
	case CONTAINER_VARYING:							\
		__dest	=	__var->numItems*numVarying;		\
		break;										\
	case CONTAINER_FACEVARYING:						\
		__dest	=	__var->numItems*numFaceVarying;	\
		break;										\
	case CONTAINER_CONSTANT:						\
		__dest	=	__var->numItems;				\
		break;										\
	default:										\
		error(CODE_BUG,"Unknown container in writePL\n");	\
		__dest	=	1;								\
	}



	for (i=0;i<numParameters;i++) {
		CVariable	tmpVar;
		CVariable	*variable;

		if (declaredVariables->find(tokens[i],variable) == TRUE) {
retry:;
			out(" \"%s\" [",tokens[i]);

			switch(variable->type) {
			case TYPE_FLOAT:

				f	=	(float *) vals[i];
				numItems(j,variable);
				for (;j>0;j--,f++) {
					out("%g ",f[0]);
				}
				break;
			case TYPE_COLOR:
			case TYPE_VECTOR:
			case TYPE_NORMAL:
			case TYPE_POINT:

				f	=	(float *) vals[i];
				numItems(j,variable);
				for (;j>0;j--,f+=3) {
					out("%g %g %g ",f[0],f[1],f[2]);
				}
				break;
			case TYPE_MATRIX:

				f	=	(float *) vals[i];
				numItems(j,variable);
				for (;j>0;j--,f+=16) {
					out("%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g ",f[0],f[1],f[2],f[3],f[4],f[5],f[6],f[7],f[8],f[9],f[10],f[11],f[12],f[13],f[14],f[15]);
				}
				break;
			case TYPE_QUAD:

				f	=	(float *) vals[i];
				numItems(j,variable);
				for (;j>0;j--,f+=4) {
					out("%g %g %g %g ",f[0],f[1],f[2],f[3]);
				}
				break;
			case TYPE_DOUBLE:

				f	=	(float *) vals[i];
				numItems(j,variable);
				for (;j>0;j--,f+=2) {
					out("%g %g ",f[0],f[1]);
				}
				break;
			case TYPE_STRING:

				s	=	(const char **) vals[i];
				for (j=variable->numItems;j>0;j--,s++) {
					out("\"%s\" ",s[0]);
				}
				break;
			case TYPE_INTEGER:
				break;
			default:
				break;
			}

			out("] ");
		} else {
			if (parseVariable(&tmpVar,NULL,tokens[i])) {
				variable	=	&tmpVar;
				goto retry;
			} else {
				char	tmp[512];

				sprintf(tmp,"Parameter \"%s\" not found\n",tokens[i]);
				errorHandler(RIE_BADTOKEN,RIE_ERROR,tmp);
			}
		}
	}

	// Print the final newline
	out("\n");

#undef numItems
}

void		CRibOut::declareVariable(const char *name,const char *decl) {
	CVariable	cVariable,*nVariable;

	assert(declaredVariables	!=	NULL);

	if (parseVariable(&cVariable,name,decl) == TRUE) {
		// Parse successful, insert the variable into the dictionary
		CVariable	*oVariable;

		if (declaredVariables->erase(cVariable.name,oVariable)) {
			delete oVariable;
		};

		// Add the new variable into the variables list
		nVariable							=	new CVariable;
		nVariable[0]						=	cVariable;

		// Insert the variable into the variables trie
		declaredVariables->insert(nVariable->name,nVariable);
	}
}


void		CRibOut::declareDefaultVariables() {
	// Define the options
	declareVariable(RI_ARCHIVE,				"string");
	declareVariable(RI_PROCEDURAL,			"string");
	declareVariable(RI_TEXTURE,				"string");
	declareVariable(RI_SHADER,				"string");
	declareVariable(RI_DISPLAY,				"string");
	declareVariable(RI_RESOURCE,			"string");

	declareVariable(RI_BUCKETSIZE,			"int[2]");
	declareVariable(RI_METABUCKETS,			"int[2]");
	declareVariable(RI_INHERITATTRIBUTES,	"int");
	declareVariable(RI_GRIDSIZE,			"int");
	declareVariable(RI_EYESPLITS,			"int");
	declareVariable(RI_TEXTUREMEMORY,		"int");
	declareVariable(RI_BRICKMEMORY,			"int");

	declareVariable(RI_RADIANCECACHE,		"int");
	declareVariable(RI_JITTER,				"float");
	declareVariable(RI_FALSECOLOR,			"int");
	declareVariable(RI_EMIT,				"int");
	declareVariable(RI_DEPTHFILTER,			"string");

	declareVariable(RI_MAXDEPTH,			"int");

	declareVariable(RI_ENDOFFRAME,			"int");
	declareVariable(RI_FILELOG,				"string");
	declareVariable(RI_PROGRESS,			"int");


	// Define the attributes
	declareVariable(RI_NUMPROBES,			"int[2]");
	declareVariable(RI_MINSUBDIVISION,		"int");
	declareVariable(RI_MAXSUBDIVISION,		"int");
	declareVariable(RI_MINSPLITS,			"int");
	declareVariable(RI_BOUNDEXPAND,			"float");
	declareVariable(RI_BINARY,				"int");
	declareVariable(RI_RASTERORIENT,		"int");

	declareVariable(RI_SPHERE,				"float");
	declareVariable(RI_COORDINATESYSYTEM,	"string");

	declareVariable(RI_DISPLACEMENTS,		"int");
	declareVariable(RI_BIAS,				"float");
	declareVariable(RI_MAXDIFFUSEDEPTH,		"int");
	declareVariable(RI_MAXSPECULARDEPTH,	"int");
	declareVariable(RI_SAMPLEMOTION,		"int");

	declareVariable(RI_HANDLE,				"string");
	declareVariable(RI_FILEMODE,			"string");
	declareVariable(RI_MAXERROR,			"float");

	declareVariable(RI_GLOBALMAP,			"string");
	declareVariable(RI_CAUSTICMAP,			"string");
	declareVariable(RI_SHADINGMODEL,		"string");
	declareVariable(RI_ESTIMATOR,			"int");
	declareVariable(RI_ILLUMINATEFRONT,		"int");

	declareVariable(RI_TRANSMISSION,		"int");
	declareVariable(RI_CAMERA,				"int");
	declareVariable(RI_SPECULAR,			"int");
	declareVariable(RI_DIFFUSE,				"int");
	declareVariable(RI_PHOTON,				"int");

	declareVariable(RI_DIFFUSEHITMODE,		"string");
	declareVariable(RI_SPECULARHITMODE,		"string");
	declareVariable(RI_TRANSMISSIONHITMODE,	"string");
	declareVariable(RI_CAMERAHITMODE,		"string");

	declareVariable(RI_NAME,				"string");
	
	declareVariable(RI_HIDDEN,				"int");
	declareVariable(RI_BACKFACING,			"backfacing");


	// File display variables
	declareVariable("quantize",				"float[4]");
	declareVariable("dither",				"float");
	declareVariable("gamma",				"float");
	declareVariable("gain",					"float");
	declareVariable("near",					"float");
	declareVariable("far",					"float");
	declareVariable("Software",				"string");
	declareVariable("compression",			"string");
	declareVariable("NP",					"float[16]");
	declareVariable("Nl",					"float[16]");
	
	// Declare the rest
	declareVariable("P",	"global vertex point");
	declareVariable("Ps",	"global vertex point");
	declareVariable("N",	"global varying normal");
	declareVariable("Ng",	"global varying normal");
	declareVariable("dPdu",	"global vertex vector");
	declareVariable("dPdv",	"global vertex vector");
	declareVariable("L",	"global varying vector");
	declareVariable("Cs",	"global varying color");
	declareVariable("Os",	"global varying color");
	declareVariable("Cl",	"global varying color");
	declareVariable("Ol",	"global varying color");
	declareVariable("Ci",	"global varying color");
	declareVariable("Oi",	"global varying color");
	declareVariable("s",	"global varying float");
	declareVariable("t",	"global varying float");
	declareVariable("st",	"varying float[2]");
	declareVariable("du",	"global varying float");
	declareVariable("dv",	"global varying float");
	declareVariable("u",	"global varying float");
	declareVariable("v",	"global varying float");
	declareVariable("I",	"global varying vector");
	declareVariable("E",	"global varying point");
	declareVariable("alpha","global varying float");
	declareVariable("time",	"global varying float");
	declareVariable("Pw",	"global vertex htpoint");
	declareVariable("Pz",	"vertex float");
	declareVariable("width","vertex float");
	declareVariable("constantwidth","constant float");

	// Define uniform variables
	declareVariable("ncomps","global uniform float");
	declareVariable("dtime","global uniform float");
	declareVariable("Np","uniform normal");

	// Misc. variables
	declareVariable("fov",	"float");
	
	// Standard RI variables
	declareVariable("Ka",				"float");
	declareVariable("Kd",				"float");
	declareVariable("Kr",				"float");
	declareVariable("Ks",				"float");
	declareVariable("amplitude",		"float");
	declareVariable("background",		"color");
	declareVariable("beamdistribution",	"float");
	declareVariable("coneangle",		"float");
	declareVariable("conedeltangle",	"float");
	declareVariable("distance",			"float");
	declareVariable("from",				"point");
	declareVariable("intensity",		"float");
	declareVariable("lightcolor",		"color");
	declareVariable("maxdistance",		"float");
	declareVariable("mindistance",		"float");
	declareVariable("roughness",		"float");
	declareVariable("specularcolor",	"color");
	declareVariable("texturename",		"string");
	declareVariable("to",				"point");
}

