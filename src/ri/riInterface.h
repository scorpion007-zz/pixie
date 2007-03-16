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
//  File				:	riInterface.h
//  Classes				:	CRiInterface
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef RIINTERFACE_H
#define RIINTERFACE_H

#include <stdio.h>
#include <stdarg.h>

///////////////////////////////////////////////////////////////////////
// Class				:	CRiInterface
// Description			:	This is the virtual class that implements the RenderMan interface
// Comments				:
class	CRiInterface {
public:
						CRiInterface();
	virtual				~CRiInterface();

	virtual	void		RiDeclare(const char *,const char *);

	virtual	void		RiFrameBegin(int);
	virtual	void		RiFrameEnd(void);
	virtual	void		RiWorldBegin(void);
	virtual	void		RiWorldEnd(void);

	virtual	void		RiFormat(int xres,int yres,float aspect);
	virtual	void		RiFrameAspectRatio(float aspect);
	virtual	void		RiScreenWindow(float left,float right,float bot,float top);
	virtual	void		RiCropWindow(float xmin,float xmax,float ymin,float ymax);
	virtual	void		RiProjectionV(char *name,int n,char *tokens[],void *params[]);
	virtual	void		RiClipping(float hither,float yon);
	virtual	void		RiClippingPlane(float x,float y,float z,float nx,float ny,float nz);
	virtual	void		RiDepthOfField(float fstop,float focallength,float focaldistance);
	virtual	void		RiShutter(float smin,float smax);

	virtual	void		RiPixelVariance(float variation);
	virtual	void		RiPixelSamples(float xsamples,float ysamples);
	virtual	void		RiPixelFilter(float (*function)(float,float,float,float),float xwidth,float ywidth);
	virtual	void		RiExposure(float gain,float gamma);
	virtual	void		RiImagerV(char *name,int n,char *tokens[],void *params[]);
	virtual	void		RiQuantize(char * type,int one,int qmin,int qmax,float ampl);
	virtual	void		RiDisplayV(char *name,char * type,char * mode,int n,char *tokens[],void *params[]);
	virtual	void		RiDisplayChannelV(char * channel,int n,char *tokens[],void *params[]);

	virtual	void		RiHiderV(char * type,int n,char *tokens[],void *params[]);
	virtual	void		RiColorSamples(int N,float *nRGB,float *RGBn);
	virtual	void		RiRelativeDetail(float relativedetail);
	virtual	void		RiOptionV(char *name,int n,char *tokens[],void *params[]);

	virtual	void		RiAttributeBegin(void);
	virtual	void		RiAttributeEnd(void);
	virtual	void		RiColor(float *Cs);
	virtual	void		RiOpacity(float *Cs);
	virtual	void		RiTextureCoordinates(float s1,float t1,float s2,float t2,float s3,float t3,float s4,float t4);

	virtual	void		*RiLightSourceV(char *name,int n,char *tokens[],void *params[]);
	virtual	void		*RiAreaLightSourceV(char *name,int n,char *tokens[],void *params[]);

	virtual	void		RiIlluminate(void *light,int onoff);
	virtual	void		RiSurfaceV(char *name,int n,char *tokens[],void *params[]);
	virtual	void		RiAtmosphereV(char *name,int n,char *tokens[],void *params[]);
	virtual	void		RiInteriorV(char *name,int n,char *tokens[],void *params[]);
	virtual	void		RiExteriorV(char *name,int n,char *tokens[],void *params[]);
	virtual	void		RiShadingRate(float size);
	virtual	void		RiShadingInterpolation(char * type);
	virtual	void		RiMatte(int onoff);

	virtual	void		RiBound(float *bound);
	virtual	void		RiDetail(float *bound);
	virtual	void		RiDetailRange(float minvis,float lowtran,float uptran,float maxvis);
	virtual	void		RiGeometricApproximation(char * type,float value);
	virtual	void		RiGeometricRepresentation(char * type);
	virtual	void		RiOrientation(char * orientation),RiReverseOrientation(void);
	virtual	void		RiSides(int nsides);

	virtual	void		RiIdentity(void);
	virtual	void		RiTransform(float transform[][4]);
	virtual	void		RiConcatTransform(float transform[][4]);
	virtual	void		RiPerspective(float fov);
	virtual	void		RiTranslate(float dx,float dy,float dz);
	virtual	void		RiRotate(float angle,float dx,float dy,float dz);
	virtual	void		RiScale(float dx,float dy,float dz);
	virtual	void		RiSkew(float angle,float dx1,float dy1,float dz1,float dx2,float dy2,float dz2);
	virtual	void		RiDeformationV(char *name,int n,char *tokens[],void *params[]);
	virtual	void		RiDisplacementV(char *name,int n,char *tokens[],void *params[]);
	virtual	void		RiCoordinateSystem(char * space);
	virtual	void		RiCoordSysTransform(char * space);

	virtual	void		RiTransformPoints(char * fromspace,char * tospace,int npoints,float points[][3]);

	virtual	void		RiTransformBegin(void);
	virtual	void		RiTransformEnd(void);

	virtual	void		RiAttributeV(char *name,int n,char *tokens[],void *params[]);
	
	virtual	void		RiPolygonV(int nvertices,int n,char *tokens[],void *params[]);
	virtual	void		RiGeneralPolygonV(int nloops,int *nverts,int n,char *tokens[],void *params[]);
	virtual	void		RiPointsPolygonsV(int npolys,int *nverts,int *verts,int n,char *tokens[],void *params[]);
	virtual	void		RiPointsGeneralPolygonsV(int npolys,int *nloops,int *nverts,int *verts,int n,char *tokens[],void *params[]);
	virtual	void		RiBasis(float ubasis[][4],int ustep,float vbasis[][4],int vstep);
	virtual	void		RiPatchV(char * type,int n,char *tokens[],void *params[]);
	virtual	void		RiPatchMeshV(char * type,int nu,char * uwrap,int nv,char * vwrap,int n,char *tokens[],void *params[]);
	virtual	void		RiNuPatchV(int nu,int uorder,float *uknot,float umin,float umax,int nv,int vorder,float *vknot,float vmin,float vmax,int n,char *tokens[],void *params[]);
	virtual	void		RiTrimCurve(int nloops,int *ncurves,int *order,float *knot,float *amin,float *amax,int *n,float *u,float *v,float *w);

	virtual	void		RiSphereV(float radius,float zmin,float zmax,float thetamax,int n,char *tokens[],void *params[]);
	virtual	void		RiConeV(float height,float radius,float thetamax,int n,char *tokens[],void *params[]);
	virtual	void		RiCylinderV(float radius,float zmin,float zmax,float thetamax,int n,char *tokens[],void *params[]);
	virtual	void		RiHyperboloidV(float *point1,float *point2,float thetamax,int n,char *tokens[],void *params[]);
	virtual	void		RiParaboloidV(float rmax,float zmin,float zmax,float thetamax,int n,char *tokens[],void *params[]);
	virtual	void		RiDiskV(float height,float radius,float thetamax,int n,char *tokens[],void *params[]);
	virtual	void		RiTorusV(float majorrad,float minorrad,float phimin,float phimax,float thetamax,int n,char *tokens[],void *params[]);
	virtual	void		RiProcedural(void * data,float *bound,void (*subdivfunc)(void *,float),void (*freefunc)(void *));
	virtual	void		RiGeometryV(char * type,int n,char *tokens[],void *params[]);

	virtual	void		RiCurvesV(char * degree,int ncurves,int nverts[],char * wrap,int n,char *tokens[],void *params[]);
	virtual	void		RiPointsV(int npts,int n,char *tokens[],void *params[]);
	virtual	void		RiSubdivisionMeshV(char * scheme,int nfaces,int nvertices[],int vertices[],int ntags,char * tags[],int nargs[],int intargs[],float floatargs[],int n,char *tokens[],void *params[]);
	virtual	void		RiBlobbyV(int nleaf,int ncode,int code[],int nflt,float flt[],int nstr,char *str[],int n,char *tokens[],void *params[]);

	virtual	void		RiProcDelayedReadArchive(char * data,float detail);
	virtual	void		RiProcRunProgram(char * data,float detail);
	virtual	void		RiProcDynamicLoad(char * data,float detail);

	virtual	void		RiProcFree(char *);

	virtual	void		RiSolidBegin(char * type);
	virtual	void		RiSolidEnd(void);
	virtual	void		*RiObjectBegin(void);

	virtual	void		RiObjectEnd(void);
	virtual	void		RiObjectInstance(void *handle);
	virtual	void		RiMotionBeginV(int N,float times[]);
	virtual	void		RiMotionEnd(void);

	virtual	void		RiMakeTextureV(char *pic,char *tex,char * swrap,char * twrap,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,char *tokens[],void *params[]);
	virtual	void		RiMakeBumpV(char *pic,char *tex,char * swrap,char * twrap,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,char *tokens[],void *params[]);
	virtual	void		RiMakeLatLongEnvironmentV(char *pic,char *tex,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,char *tokens[],void *params[]);
	virtual	void		RiMakeCubeFaceEnvironmentV(char *px,char *nx,char *py,char *ny,char *pz,char *nz,char *tex,float fov,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,char *tokens[],void *params[]);
	virtual	void		RiMakeShadowV(char *pic,char *tex,int n,char *tokens[],void *params[]);
	virtual	void		RiMakeTexture3DV(char *src,char *dest,int n,char *tokens[],void *params[]);

	virtual	void		RiErrorHandler(void (*handler)(int,int,char *));

	virtual	void		RiArchiveRecord(char * type,char *format,va_list args);
	virtual	void		RiReadArchiveV(char *filename,void (*callback)(const char *),int n,char *tokens[],void *params[]);

	virtual	void		*RiArchiveBeginV(const char *name, int n, char *tokens[], void *parms[]);
	virtual	void		RiArchiveEnd(void);
	
	virtual	void		RiResourceV(const char *handle,const char *type,int n, char *tokens[],void *parms[]);
	virtual	void		RiResourceBegin(void);
	virtual	void		RiResourceEnd(void);

	virtual	void		RiIfBeginV(const char *expr,int n, char *tokens[], void *parms[]);
	virtual	void		RiElseIfV(const char *expr,int n, char *tokens[], void *parms[]);
	virtual	void		RiElse(void);
	virtual	void		RiIfEnd(void);
		
	virtual	void		RiError(int,int,char *);

protected:
	void				(*errorHandler)(int,int,char *);
};


extern	CRiInterface	*renderMan;		// This is the global variable that's implementing the RenderMan interface

#endif

