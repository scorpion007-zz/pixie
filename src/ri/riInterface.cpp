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
//  File				:	riInterface.cpp
//  Classes				:	CRiInterface
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include <stdarg.h>

#include "riInterface.h"
#include "common/os.h"
#include "ri_config.h"
#include "ri.h"

CRiInterface::CRiInterface() {
	errorHandler	=	RiErrorPrint;
	renderMan		=	this;
}

CRiInterface::~CRiInterface() {
}

void		CRiInterface::RiDeclare(const char *,const char *) {
}

void		CRiInterface::RiFrameBegin(int) {
}

void		CRiInterface::RiFrameEnd(void) {
}

void		CRiInterface::RiWorldBegin(void) {
}

void		CRiInterface::RiWorldEnd(void) {
}

void		CRiInterface::RiFormat(int xres,int yres,float aspect) {
}

void		CRiInterface::RiFrameAspectRatio(float aspect) {
}

void		CRiInterface::RiScreenWindow(float left,float right,float bot,float top) {
}

void		CRiInterface::RiCropWindow(float xmin,float xmax,float ymin,float ymax) {
}

void		CRiInterface::RiProjectionV(const char *name,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiClipping(float hither,float yon) {
}

void		CRiInterface::RiClippingPlane(float x,float y,float z,float nx,float ny,float nz) {
}

void		CRiInterface::RiDepthOfField(float fstop,float focallength,float focaldistance) {
}

void		CRiInterface::RiShutter(float smin,float smax) {
}

void		CRiInterface::RiPixelVariance(float variance) {
}

void		CRiInterface::RiPixelSamples(float xsamples,float ysamples) {
}

void		CRiInterface::RiPixelFilter(float (*function)(float,float,float,float),float xwidth,float ywidth) {
}

void		CRiInterface::RiExposure(float gain,float gamma) {
}

void		CRiInterface::RiImagerV(const char *name,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiQuantize(const char * type,int one,int qmin,int qmax,float ampl) {
}

void		CRiInterface::RiDisplayV(const char *name,const char * type,const char * mode,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiCustomDisplayV(const char *name, RtToken mode, RtDisplayStartFunction, RtDisplayDataFunction, RtDisplayFinishFunction, RtInt n, RtToken tokens[], RtPointer params[]) {
}

void		CRiInterface::RiDisplayChannelV(const char * channel,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiHiderV(const char * type,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiColorSamples(int N,float *nRGB,float *RGBn) {
}

void		CRiInterface::RiRelativeDetail(float relativedetail) {
}

void		CRiInterface::RiOptionV(const char *name,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiAttributeBegin(void) {
}

void		CRiInterface::RiAttributeEnd(void) {
}

void		CRiInterface::RiColor(float *Cs) {
}

void		CRiInterface::RiOpacity(float *Cs) {
}

void		CRiInterface::RiTextureCoordinates(float s1,float t1,float s2,float t2,float s3,float t3,float s4,float t4) {
}

void		*CRiInterface::RiLightSourceV(const char *name,int n,const char *tokens[],const void *params[]) {
	return NULL;
}

void		*CRiInterface::RiAreaLightSourceV(const char *name,int n,const char *tokens[],const void *params[]) {
	return NULL;
}

void		CRiInterface::RiIlluminate(const void *light,int onoff) {
}

void		CRiInterface::RiSurfaceV(const char *name,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiAtmosphereV(const char *name,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiInteriorV(const char *name,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiExteriorV(const char *name,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiShadingRate(float size) {
}

void		CRiInterface::RiShadingInterpolation(const char * type) {
}

void		CRiInterface::RiMatte(int onoff) {
}

void		CRiInterface::RiBound(float *bound) {
}

void		CRiInterface::RiDetail(float *bound) {
}

void		CRiInterface::RiDetailRange(float minvis,float lowtran,float uptran,float maxvis) {
}

void		CRiInterface::RiGeometricApproximation(const char * type,float value) {
}

void		CRiInterface::RiGeometricRepresentation(const char * type) {
}

void		CRiInterface::RiOrientation(const char * orientation) {
}

void		CRiInterface::RiReverseOrientation(void) {
}

void		CRiInterface::RiSides(int nsides) {
}

void		CRiInterface::RiIdentity(void) {
}

void		CRiInterface::RiTransform(float transform[][4]) {
}

void		CRiInterface::RiConcatTransform(float transform[][4]) {
}

void		CRiInterface::RiPerspective(float fov) {
}

void		CRiInterface::RiTranslate(float dx,float dy,float dz) {
}

void		CRiInterface::RiRotate(float angle,float dx,float dy,float dz) {
}

void		CRiInterface::RiScale(float dx,float dy,float dz) {
}

void		CRiInterface::RiSkew(float angle,float dx1,float dy1,float dz1,float dx2,float dy2,float dz2) {
}

void		CRiInterface::RiDeformationV(const char *name,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiDisplacementV(const char *name,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiCoordinateSystem(const char * space) {
}

void		CRiInterface::RiCoordSysTransform(const char * space) {
}

RtPoint *		CRiInterface::RiTransformPoints(const char * fromspace,const char * tospace,int npoints,RtPoint *points) {
	return NULL;
}

void		CRiInterface::RiTransformBegin(void) {
}

void		CRiInterface::RiTransformEnd(void) {
}

void		CRiInterface::RiAttributeV(const char *name,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiPolygonV(int nvertices,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiGeneralPolygonV(int nloops,int *nverts,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiPointsPolygonsV(int npolys,int *nverts,int *verts,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiPointsGeneralPolygonsV(int npolys,int *nloops,int *nverts,int *verts,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiBasis(float ubasis[][4],int ustep,float vbasis[][4],int vstep) {
}

void		CRiInterface::RiPatchV(const char * type,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiPatchMeshV(const char * type,int nu,const char * uwrap,int nv,const char * vwrap,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiNuPatchV(int nu,int uorder,float *uknot,float umin,float umax,int nv,int vorder,float *vknot,float vmin,float vmax,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiTrimCurve(int nloops,int *ncurves,int *order,float *knot,float *amin,float *amax,int *n,float *u,float *v,float *w) {
}

void		CRiInterface::RiSphereV(float radius,float zmin,float zmax,float thetamax,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiConeV(float height,float radius,float thetamax,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiCylinderV(float radius,float zmin,float zmax,float thetamax,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiHyperboloidV(float *point1,float *point2,float thetamax,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiParaboloidV(float rmax,float zmin,float zmax,float thetamax,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiDiskV(float height,float radius,float thetamax,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiTorusV(float majorrad,float minorrad,float phimin,float phimax,float thetamax,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiProcedural(void * data,float *bound,void (*subdivfunc)(void *,float),void (*freefunc)(void *)) {
}

void		CRiInterface::RiGeometryV(const char * type,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiCurvesV(const char * degree,int ncurves,int nverts[],const char * wrap,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiPointsV(int npts,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiSubdivisionMeshV(const char * scheme,int nfaces,int nvertices[],int vertices[],int ntags,const char * tags[],int nargs[],int intargs[],float floatargs[],int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiBlobbyV(int nleaf,int ncode,int code[],int nflt,float flt[],int nstr,const char *str[],int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiProcDelayedReadArchive(const char * data,float detail) {
}

void		CRiInterface::RiProcRunProgram(const char * data,float detail) {
}

void		CRiInterface::RiProcDynamicLoad(const char * data,float detail) {
}

void		CRiInterface::RiProcFree(const char *) {
}

void		CRiInterface::RiSolidBegin(const char * type) {
}

void		CRiInterface::RiSolidEnd(void) {
}

void		*CRiInterface::RiObjectBegin(void) {
	return NULL;
}

void		CRiInterface::RiObjectEnd(void) {
}

void		CRiInterface::RiObjectInstance(const void *handle) {
}

void		CRiInterface::RiMotionBeginV(int N,float times[]) {
}

void		CRiInterface::RiMotionEnd(void) {
}

void		CRiInterface::RiMakeTextureV(const char *pic,const char *tex,const char * swrap,const char * twrap,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiMakeBumpV(const char *pic,const char *tex,const char * swrap,const char * twrap,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiMakeLatLongEnvironmentV(const char *pic,const char *tex,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiMakeCubeFaceEnvironmentV(const char *px,const char *nx,const char *py,const char *ny,const char *pz,const char *nz,const char *tex,float fov,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiMakeShadowV(const char *pic,const char *tex,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiMakeBrickMapV(int nb,const char **src,const char *dest,int n,const char *tokens[],const void *params[]) {
}

void		CRiInterface::RiErrorHandler(void (*handler)(int,int,const char *)) {
	errorHandler	=	handler;
}

void		CRiInterface::RiArchiveRecord(const char * type,const char *format,va_list args) {
}

void		CRiInterface::RiReadArchiveV(const char *filename,void (*callback)(const char *,...),int n,const char *tokens[],const void *params[]) {
}

void		*CRiInterface::RiArchiveBeginV(const char *name,int n,const char *tokens[],const void *parms[]) {
	return NULL;
}

void		CRiInterface::RiArchiveEnd(void) {
}
	
void		CRiInterface::RiResourceV(const char *handle,const char *type,int n,const char *tokens[],const void *parms[]) {
}

void		CRiInterface::RiResourceBegin(void) {
}

void		CRiInterface::RiResourceEnd(void) {
}

void		CRiInterface::RiIfBeginV(const char *expr,int n,const char *tokens[],const void *parms[]) {
}

void		CRiInterface::RiElseIfV(const char *expr,int n,const char *tokens[],const void *parms[]) {
}

void		CRiInterface::RiElse(void) {
}

void		CRiInterface::RiIfEnd(void) {
}

void		CRiInterface::RiError(int c,int s,const char *m) {
	if (errorHandler != NULL) {
		errorHandler(c,s,m);
	}
}

