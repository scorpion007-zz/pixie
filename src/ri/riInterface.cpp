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

void		CRiInterface::RiProjectionV(char *name,int n,char *tokens[],void *params[]) {
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

void		CRiInterface::RiImagerV(char *name,int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiQuantize(char * type,int one,int qmin,int qmax,float ampl) {
}

void		CRiInterface::RiDisplayV(char *name,char * type,char * mode,int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiDisplayChannelV(char * channel,int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiHiderV(char * type,int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiColorSamples(int N,float *nRGB,float *RGBn) {
}

void		CRiInterface::RiRelativeDetail(float relativedetail) {
}

void		CRiInterface::RiOptionV(char *name,int n,char *tokens[],void *params[]) {
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

void		*CRiInterface::RiLightSourceV(char *name,int n,char *tokens[],void *params[]) {
	return NULL;
}

void		*CRiInterface::RiAreaLightSourceV(char *name,int n,char *tokens[],void *params[]) {
	return NULL;
}

void		CRiInterface::RiIlluminate(void *light,int onoff) {
}

void		CRiInterface::RiSurfaceV(char *name,int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiAtmosphereV(char *name,int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiInteriorV(char *name,int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiExteriorV(char *name,int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiShadingRate(float size) {
}

void		CRiInterface::RiShadingInterpolation(char * type) {
}

void		CRiInterface::RiMatte(int onoff) {
}

void		CRiInterface::RiBound(float *bound) {
}

void		CRiInterface::RiDetail(float *bound) {
}

void		CRiInterface::RiDetailRange(float minvis,float lowtran,float uptran,float maxvis) {
}

void		CRiInterface::RiGeometricApproximation(char * type,float value) {
}

void		CRiInterface::RiGeometricRepresentation(char * type) {
}

void		CRiInterface::RiOrientation(char * orientation) {
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

void		CRiInterface::RiDeformationV(char *name,int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiDisplacementV(char *name,int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiCoordinateSystem(char * space) {
}

void		CRiInterface::RiCoordSysTransform(char * space) {
}

void		CRiInterface::RiTransformPoints(char * fromspace,char * tospace,int npoints,float points[][3]) {
}

void		CRiInterface::RiTransformBegin(void) {
}

void		CRiInterface::RiTransformEnd(void) {
}

void		CRiInterface::RiAttributeV(char *name,int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiPolygonV(int nvertices,int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiGeneralPolygonV(int nloops,int *nverts,int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiPointsPolygonsV(int npolys,int *nverts,int *verts,int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiPointsGeneralPolygonsV(int npolys,int *nloops,int *nverts,int *verts,int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiBasis(float ubasis[][4],int ustep,float vbasis[][4],int vstep) {
}

void		CRiInterface::RiPatchV(char * type,int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiPatchMeshV(char * type,int nu,char * uwrap,int nv,char * vwrap,int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiNuPatchV(int nu,int uorder,float *uknot,float umin,float umax,int nv,int vorder,float *vknot,float vmin,float vmax,int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiTrimCurve(int nloops,int *ncurves,int *order,float *knot,float *amin,float *amax,int *n,float *u,float *v,float *w) {
}

void		CRiInterface::RiSphereV(float radius,float zmin,float zmax,float thetamax,int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiConeV(float height,float radius,float thetamax,int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiCylinderV(float radius,float zmin,float zmax,float thetamax,int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiHyperboloidV(float *point1,float *point2,float thetamax,int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiParaboloidV(float rmax,float zmin,float zmax,float thetamax,int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiDiskV(float height,float radius,float thetamax,int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiTorusV(float majorrad,float minorrad,float phimin,float phimax,float thetamax,int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiProcedural(void * data,float *bound,void (*subdivfunc)(void *,float),void (*freefunc)(void *)) {
}

void		CRiInterface::RiGeometryV(char * type,int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiCurvesV(char * degree,int ncurves,int nverts[],char * wrap,int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiPointsV(int npts,int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiSubdivisionMeshV(char * scheme,int nfaces,int nvertices[],int vertices[],int ntags,char * tags[],int nargs[],int intargs[],float floatargs[],int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiBlobbyV(int nleaf,int ncode,int code[],int nflt,float flt[],int nstr,char *str[],int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiProcDelayedReadArchive(char * data,float detail) {
}

void		CRiInterface::RiProcRunProgram(char * data,float detail) {
}

void		CRiInterface::RiProcDynamicLoad(char * data,float detail) {
}

void		CRiInterface::RiProcFree(char *) {
}

void		CRiInterface::RiSolidBegin(char * type) {
}

void		CRiInterface::RiSolidEnd(void) {
}

void		*CRiInterface::RiObjectBegin(void) {
	return NULL;
}

void		CRiInterface::RiObjectEnd(void) {
}

void		CRiInterface::RiObjectInstance(void *handle) {
}

void		CRiInterface::RiMotionBeginV(int N,float times[]) {
}

void		CRiInterface::RiMotionEnd(void) {
}

void		CRiInterface::RiMakeTextureV(char *pic,char *tex,char * swrap,char * twrap,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiMakeBumpV(char *pic,char *tex,char * swrap,char * twrap,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiMakeLatLongEnvironmentV(char *pic,char *tex,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiMakeCubeFaceEnvironmentV(char *px,char *nx,char *py,char *ny,char *pz,char *nz,char *tex,float fov,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiMakeShadowV(char *pic,char *tex,int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiMakeBrickMapV(int nb,char **src,char *dest,int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiErrorHandler(void (*handler)(int,int,char *)) {
	errorHandler	=	handler;
}

void		CRiInterface::RiArchiveRecord(char * type,char *format,va_list args) {
}

void		CRiInterface::RiReadArchiveV(char *filename,void (*callback)(const char *,...),int n,char *tokens[],void *params[]) {
}

void		CRiInterface::RiArchiveBeginV(const char *name,int n,char *tokens[],void *parms[]) {
}

void		CRiInterface::RiArchiveEnd(void) {
}
	
void		CRiInterface::RiResourceV(const char *handle,const char *type,int n,char *tokens[],void *parms[]) {
}

void		CRiInterface::RiResourceBegin(void) {
}

void		CRiInterface::RiResourceEnd(void) {
}

void		CRiInterface::RiIfBeginV(const char *expr,int n,char *tokens[],void *parms[]) {
}

void		CRiInterface::RiElseIfV(const char *expr,int n,char *tokens[],void *parms[]) {
}

void		CRiInterface::RiElse(void) {
}

void		CRiInterface::RiIfEnd(void) {
}

void		CRiInterface::RiError(int c,int s,char *m) {
	if (errorHandler != NULL) {
		errorHandler(c,s,m);
	}
}

