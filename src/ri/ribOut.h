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
//  File				:	ribOut.h
//  Classes				:	CRibOut
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef RIBOUT_H
#define RIBOUT_H

#include "common/global.h"		// The global header file
#include "common/containers.h"
#include "riInterface.h"
#include "ri_config.h"

#ifdef HAVE_ZLIB
#include <zlib.h>
#endif

class	CVariable;

///////////////////////////////////////////////////////////////////////
// Class				:	CRibOut
// Description			:	This class implements a RIB file output
// Comments				:
class	CRibOut : public CRiInterface {

	///////////////////////////////////////////////////////////////////////
	// Class				:	CRibAttributes
	// Description			:	The attributes holder for the RIB file output
	// Comments				:
	class	CRibAttributes {
	public:
							CRibAttributes();
							CRibAttributes(CRibAttributes *);
							~CRibAttributes();

		int					uStep,vStep;
		CRibAttributes		*next;
	};


public:
						CRibOut(const char *);
						CRibOut(FILE *);
	virtual				~CRibOut();

	virtual	void		RiDeclare(const char *,const char *);

	virtual	void		RiFrameBegin(int);
	virtual	void		RiFrameEnd(void);
	virtual	void		RiWorldBegin(void);
	virtual	void		RiWorldEnd(void);

	virtual	void		RiFormat(int xres,int yres,float aspect);
	virtual	void		RiFrameAspectRatio(float aspect);
	virtual	void		RiScreenWindow(float left,float right,float bot,float top);
	virtual	void		RiCropWindow(float xmin,float xmax,float ymin,float ymax);
	virtual	void		RiProjectionV(const char *name,int n,const char *tokens[],const void *params[]);
	virtual	void		RiClipping(float hither,float yon);
	virtual	void		RiClippingPlane(float x,float y,float z,float nx,float ny,float nz);
	virtual	void		RiDepthOfField(float fstop,float focallength,float focaldistance);
	virtual	void		RiShutter(float smin,float smax);

	virtual	void		RiPixelVariance(float variation);
	virtual	void		RiPixelSamples(float xsamples,float ysamples);
	virtual	void		RiPixelFilter(float (*function)(float,float,float,float),float xwidth,float ywidth);
	virtual	void		RiExposure(float gain,float gamma);
	virtual	void		RiImagerV(const char *name,int n,const char *tokens[],const void *params[]);
	virtual	void		RiQuantize(const char * type,int one,int qmin,int qmax,float ampl);
	virtual	void		RiDisplayV(const char *name,const char * type,const char * mode,int n,const char *tokens[],const void *params[]);
	virtual	void		RiCustomDisplayV(const char *name, RtToken mode, RtDisplayStartFunction, RtDisplayDataFunction, RtDisplayFinishFunction, RtInt n, RtToken tokens[], RtPointer params[]);
	virtual	void		RiDisplayChannelV(const char * channel,int n,const char *tokens[],const void *params[]);

	virtual	void		RiHiderV(const char * type,int n,const char *tokens[],const void *params[]);
	virtual	void		RiColorSamples(int N,float *nRGB,float *RGBn);
	virtual	void		RiRelativeDetail(float relativedetail);
	virtual	void		RiOptionV(const char *name,int n,const char *tokens[],const void *params[]);

	virtual	void		RiAttributeBegin(void);
	virtual	void		RiAttributeEnd(void);
	virtual	void		RiColor(float *Cs);
	virtual	void		RiOpacity(float *Cs);
	virtual	void		RiTextureCoordinates(float s1,float t1,float s2,float t2,float s3,float t3,float s4,float t4);

	virtual	void		*RiLightSourceV(const char *name,int n,const char *tokens[],const void *params[]);
	virtual	void		*RiAreaLightSourceV(const char *name,int n,const char *tokens[],const void *params[]);

	virtual	void		RiIlluminate(const void *light,int onoff);
	virtual	void		RiSurfaceV(const char *name,int n,const char *tokens[],const void *params[]);
	virtual	void		RiAtmosphereV(const char *name,int n,const char *tokens[],const void *params[]);
	virtual	void		RiInteriorV(const char *name,int n,const char *tokens[],const void *params[]);
	virtual	void		RiExteriorV(const char *name,int n,const char *tokens[],const void *params[]);
	virtual	void		RiShadingRate(float size);
	virtual	void		RiShadingInterpolation(const char * type);
	virtual	void		RiMatte(int onoff);

	virtual	void		RiBound(float *bound);
	virtual	void		RiDetail(float *bound);
	virtual	void		RiDetailRange(float minvis,float lowtran,float uptran,float maxvis);
	virtual	void		RiGeometricApproximation(const char * type,float value);
	virtual	void		RiGeometricRepresentation(const char * type);
	virtual	void		RiOrientation(const char * orientation),RiReverseOrientation(void);
	virtual	void		RiSides(int nsides);

	virtual	void		RiIdentity(void);
	virtual	void		RiTransform(float transform[][4]);
	virtual	void		RiConcatTransform(float transform[][4]);
	virtual	void		RiPerspective(float fov);
	virtual	void		RiTranslate(float dx,float dy,float dz);
	virtual	void		RiRotate(float angle,float dx,float dy,float dz);
	virtual	void		RiScale(float dx,float dy,float dz);
	virtual	void		RiSkew(float angle,float dx1,float dy1,float dz1,float dx2,float dy2,float dz2);
	virtual	void		RiDeformationV(const char *name,int n,const char *tokens[],const void *params[]);
	virtual	void		RiDisplacementV(const char *name,int n,const char *tokens[],const void *params[]);
	virtual	void		RiCoordinateSystem(const char * space);
	virtual	void		RiCoordSysTransform(const char * space);

	virtual	RtPoint *		RiTransformPoints(const char * fromspace,const char * tospace,int npoints,RtPoint *points);

	virtual	void		RiTransformBegin(void);
	virtual	void		RiTransformEnd(void);

	virtual	void		RiAttributeV(const char *name,int n,const char *tokens[],const void *params[]);

	
	virtual	void		RiPolygonV(int nvertices,int n,const char *tokens[],const void *params[]);
	virtual	void		RiGeneralPolygonV(int nloops,int *nverts,int n,const char *tokens[],const void *params[]);
	virtual	void		RiPointsPolygonsV(int npolys,int *nverts,int *verts,int n,const char *tokens[],const void *params[]);
	virtual	void		RiPointsGeneralPolygonsV(int npolys,int *nloops,int *nverts,int *verts,int n,const char *tokens[],const void *params[]);
	virtual	void		RiBasis(float ubasis[][4],int ustep,float vbasis[][4],int vstep);
	virtual	void		RiPatchV(const char * type,int n,const char *tokens[],const void *params[]);
	virtual	void		RiPatchMeshV(const char * type,int nu,const char * uwrap,int nv,const char * vwrap,int n,const char *tokens[],const void *params[]);
	virtual	void		RiNuPatchV(int nu,int uorder,float *uknot,float umin,float umax,int nv,int vorder,float *vknot,float vmin,float vmax,int n,const char *tokens[],const void *params[]);
	virtual	void		RiTrimCurve(int nloops,int *ncurves,int *order,float *knot,float *amin,float *amax,int *n,float *u,float *v,float *w);

	virtual	void		RiSphereV(float radius,float zmin,float zmax,float thetamax,int n,const char *tokens[],const void *params[]);
	virtual	void		RiConeV(float height,float radius,float thetamax,int n,const char *tokens[],const void *params[]);
	virtual	void		RiCylinderV(float radius,float zmin,float zmax,float thetamax,int n,const char *tokens[],const void *params[]);
	virtual	void		RiHyperboloidV(float *point1,float *point2,float thetamax,int n,const char *tokens[],const void *params[]);
	virtual	void		RiParaboloidV(float rmax,float zmin,float zmax,float thetamax,int n,const char *tokens[],const void *params[]);
	virtual	void		RiDiskV(float height,float radius,float thetamax,int n,const char *tokens[],const void *params[]);
	virtual	void		RiTorusV(float majorrad,float minorrad,float phimin,float phimax,float thetamax,int n,const char *tokens[],const void *params[]);
	virtual	void		RiProcedural(void * data,float *bound,void (*subdivfunc)(void *,float),void (*freefunc)(void *));
	virtual	void		RiGeometryV(const char * type,int n,const char *tokens[],const void *params[]);

	virtual	void		RiCurvesV(const char * degree,int ncurves,int nverts[],const char * wrap,int n,const char *tokens[],const void *params[]);
	virtual	void		RiPointsV(int npts,int n,const char *tokens[],const void *params[]);
	virtual	void		RiSubdivisionMeshV(const char * scheme,int nfaces,int nvertices[],int vertices[],int ntags,const char * tags[],int nargs[],int intargs[],float floatargs[],int n,const char *tokens[],const void *params[]);
	virtual	void		RiBlobbyV(int nleaf,int ncode,int code[],int nflt,float flt[],int nstr,const char *str[],int n,const char *tokens[],const void *params[]);

	virtual	void		RiProcDelayedReadArchive(const char * data,float detail);
	virtual	void		RiProcRunProgram(const char * data,float detail);
	virtual	void		RiProcDynamicLoad(const char * data,float detail);

	virtual	void		RiProcFree(const char *);

	virtual	void		RiSolidBegin(const char * type);
	virtual	void		RiSolidEnd(void);
	virtual	void		*RiObjectBegin(void);

	virtual	void		RiObjectEnd(void);
	virtual	void		RiObjectInstance(const void *handle);
	virtual	void		RiMotionBeginV(int N,float times[]);
	virtual	void		RiMotionEnd(void);

	virtual	void		RiMakeTextureV(const char *pic,const char *tex,const char * swrap,const char * twrap,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,const char *tokens[],const void *params[]);
	virtual	void		RiMakeBumpV(const char *pic,const char *tex,const char * swrap,const char * twrap,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,const char *tokens[],const void *params[]);
	virtual	void		RiMakeLatLongEnvironmentV(const char *pic,const char *tex,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,const char *tokens[],const void *params[]);
	virtual	void		RiMakeCubeFaceEnvironmentV(const char *px,const char *nx,const char *py,const char *ny,const char *pz,const char *nz,const char *tex,float fov,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,const char *tokens[],const void *params[]);
	virtual	void		RiMakeShadowV(const char *pic,const char *tex,int n,const char *tokens[],const void *params[]);
	virtual	void		RiMakeBrickMapV(int n,const char **src,const char *dest,int numTokens,const char *tokens[],const void *params[]);

	virtual	void		RiErrorHandler(void (*handler)(int,int,const char *));

	virtual	void		RiArchiveRecord(const char * type,const char *format,va_list args);
	virtual	void		RiReadArchiveV(const char *filename,void (*callback)(const char *,...),int n,const char *tokens[],const void *params[]);

	virtual	void		*RiArchiveBeginV(const char *name, int n,const char *tokens[],const void *parms[]);
	virtual	void		RiArchiveEnd(void);
	
	virtual	void		RiResourceV(const char *handle,const char *type,int n,const char *tokens[],const void *parms[]);
	virtual	void		RiResourceBegin(void);
	virtual	void		RiResourceEnd(void);

	virtual	void		RiIfBeginV(const char *expr,int n,const char *tokens[],const void *parms[]);
	virtual	void		RiElseIfV(const char *expr,int n,const char *tokens[],const void *parms[]);
	virtual	void		RiElse(void);
	virtual	void		RiIfEnd(void);

private:
	void				writePL(int,const char *[],const void *[]);
	void				writePL(int numVertex,int numVarying,int numFaceVarying,int numUniform,int,const char *[],const void *[]);
	void				declareVariable(const char *,const char *);
	void				declareDefaultVariables();

	const	char							*outName;
	FILE									*outFile;
	int										outputCompressed;
	int										outputIsPipe;
	CDictionary<const char *,CVariable *>	*declaredVariables;			// Declared variables
	int										numLightSources;
	int										numObjects;
	CRibAttributes							*attributes;
	char									*scratch;

											///////////////////////////////////////////////////////////////////////
											// Class				:	CRibOut
											// Method				:	vout
											// Description			:	Write a variable argument list
											// Return Value			:	-
											// Comments				:
	void									vout(const char *mes,va_list args) {
												const int	l	=	vsprintf(scratch,mes,args);

												#ifdef HAVE_ZLIB
													if (outputCompressed)	gzwrite(outFile,scratch,l);
													else					fwrite(scratch,1,l,outFile);
												#else
													fwrite(scratch,1,l,outFile);
												#endif
											}

											///////////////////////////////////////////////////////////////////////
											// Class				:	CRibOut
											// Method				:	out
											// Description			:	Write an argument list
											// Return Value			:	-
											// Comments				:
	void									out(const char *mes,...) {
												va_list	args;

												va_start(args,mes);

												const int l	=	vsprintf(scratch,mes,args);

												#ifdef HAVE_ZLIB
													if (outputCompressed)	gzwrite(outFile,scratch,l);
													else					fwrite(scratch,1,l,outFile);
												#else
													fwrite(scratch,1,l,outFile);
												#endif

												va_end(args);
											}

};


#endif

