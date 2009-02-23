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
//  File				:	renderer.h
//  Classes				:	CRendererContext
//  Description			:	This file defines the main renderer interface
//
////////////////////////////////////////////////////////////////////////
#ifndef RENDERER_H
#define RENDERER_H

#include "common/global.h"
#include "common/algebra.h"
#include "shader.h"
#include "rendererc.h"				// Renderer constants
#include "texture.h"
#include "options.h"
#include "shader.h"
#include "object.h"
#include "shadeop.h"
#include "resource.h"
#include "riInterface.h"
#include "variable.h"


class	CShadingContext;
class	CIrradianceCache;
class	CPhotonMap;
class	CParticipatingMedium;
class	CDelayedObject;
class	CDelayedInstance;
class	CNetFileMapping;

///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Description			:	Holds the global rendering context
// Comments				:
class	CRendererContext : public CRiInterface {
public:

						CRendererContext(const char *ribName=NULL,const char *netString=NULL);
						~CRendererContext();

	///////////////////////////////////////////////////////////////////////
	// Renderer interface
	///////////////////////////////////////////////////////////////////////
	void				RiDeclare(const char *,const char *);

	void				RiFrameBegin(int);
	void				RiFrameEnd(void);
	void				RiWorldBegin(void);
	void				RiWorldEnd(void);

	void				RiFormat(int xres,int yres,float aspect);
	void				RiFrameAspectRatio(float aspect);
	void				RiScreenWindow(float left,float right,float bot,float top);
	void				RiCropWindow(float xmin,float xmax,float ymin,float ymax);
	void				RiProjectionV(const char *name,int n,const char *tokens[],const void *params[]);
	void				RiClipping(float hither,float yon);
	void				RiClippingPlane(float x,float y,float z,float nx,float ny,float nz);
	void				RiDepthOfField(float fstop,float focallength,float focaldistance);
	void				RiShutter(float smin,float smax);

	void				RiPixelVariance(float variation);
	void				RiPixelSamples(float xsamples,float ysamples);
	void				RiPixelFilter(float (*function)(float,float,float,float),float xwidth,float ywidth);
	void				RiExposure(float gain,float gamma);
	void				RiImagerV(const char *name,int n,const char *tokens[],const void *params[]);
	void				RiQuantize(const char * type,int one,int qmin,int qmax,float ampl);
	void				RiDisplayV(const char *name,const char * type,const char * mode,int n,const char *tokens[],const void *params[]);
	void				RiCustomDisplayV(const char *name, RtToken mode, RtDisplayStartFunction, RtDisplayDataFunction, RtDisplayFinishFunction, RtInt n, RtToken tokens[], RtPointer params[]);
	void				RiDisplayChannelV(const char * channel,int n,const char *tokens[],const void *params[]);

	void				RiHiderV(const char * type,int n,const char *tokens[],const void *params[]);
	void				RiColorSamples(int N,float *nRGB,float *RGBn);
	void				RiRelativeDetail(float relativedetail);
	void				RiOptionV(const char *name,int n,const char *tokens[],const void *params[]);

	void				RiAttributeBegin(void);
	void				RiAttributeEnd(void);
	void				RiColor(float *Cs);
	void				RiOpacity(float *Cs);
	void				RiTextureCoordinates(float s1,float t1,float s2,float t2,float s3,float t3,float s4,float t4);

	void				*RiLightSourceV(const char *name,int n,const char *tokens[],const void *params[]);
	void				*RiAreaLightSourceV(const char *name,int n,const char *tokens[],const void *params[]);

	void				RiIlluminate(const void *light,int onoff);
	void				RiSurfaceV(const char *name,int n,const char *tokens[],const void *params[]);
	void				RiAtmosphereV(const char *name,int n,const char *tokens[],const void *params[]);
	void				RiInteriorV(const char *name,int n,const char *tokens[],const void *params[]);
	void				RiExteriorV(const char *name,int n,const char *tokens[],const void *params[]);
	void				RiShadingRate(float size);
	void				RiShadingInterpolation(const char * type);
	void				RiMatte(int onoff);

	void				RiBound(float *bound);
	void				RiDetail(float *bound);
	void				RiDetailRange(float minvis,float lowtran,float uptran,float maxvis);
	void				RiGeometricApproximation(const char * type,float value);
	void				RiGeometricRepresentation(const char * type);
	void				RiOrientation(const char * orientation),RiReverseOrientation(void);
	void				RiSides(int nsides);

	void				RiIdentity(void);
	void				RiTransform(float transform[][4]);
	void				RiConcatTransform(float transform[][4]);
	void				RiPerspective(float fov);
	void				RiTranslate(float dx,float dy,float dz);
	void				RiRotate(float angle,float dx,float dy,float dz);
	void				RiScale(float dx,float dy,float dz);
	void				RiSkew(float angle,float dx1,float dy1,float dz1,float dx2,float dy2,float dz2);
	void				RiDeformationV(const char *name,int n,const char *tokens[],const void *params[]);
	void				RiDisplacementV(const char *name,int n,const char *tokens[],const void *params[]);
	void				RiCoordinateSystem(const char * space);
	void				RiCoordSysTransform(const char * space);

	RtPoint				*RiTransformPoints(const char *fromspace,const char *tospace,int npoints,RtPoint *points);

	void				RiTransformBegin(void);
	void				RiTransformEnd(void);

	void				RiAttributeV(const char *name,int n,const char *tokens[],const void *params[]);

	void				RiPolygonV(int nvertices,int n,const char *tokens[],const void *params[]);
	void				RiGeneralPolygonV(int nloops,int *nverts,int n,const char *tokens[],const void *params[]);
	void				RiPointsPolygonsV(int npolys,int *nverts,int *verts,int n,const char *tokens[],const void *params[]);
	void				RiPointsGeneralPolygonsV(int npolys,int *nloops,int *nverts,int *verts,int n,const char *tokens[],const void *params[]);
	void				RiBasis(float ubasis[][4],int ustep,float vbasis[][4],int vstep);
	void				RiPatchV(const char * type,int n,const char *tokens[],const void *params[]);
	void				RiPatchMeshV(const char * type,int nu,const char * uwrap,int nv,const char * vwrap,int n,const char *tokens[],const void *params[]);
	void				RiNuPatchV(int nu,int uorder,float *uknot,float umin,float umax,int nv,int vorder,float *vknot,float vmin,float vmax,int n,const char *tokens[],const void *params[]);
	void				RiTrimCurve(int nloops,int *ncurves,int *order,float *knot,float *amin,float *amax,int *n,float *u,float *v,float *w);

	void				RiSphereV(float radius,float zmin,float zmax,float thetamax,int n,const char *tokens[],const void *params[]);
	void				RiConeV(float height,float radius,float thetamax,int n,const char *tokens[],const void *params[]);
	void				RiCylinderV(float radius,float zmin,float zmax,float thetamax,int n,const char *tokens[],const void *params[]);
	void				RiHyperboloidV(float *point1,float *point2,float thetamax,int n,const char *tokens[],const void *params[]);
	void				RiParaboloidV(float rmax,float zmin,float zmax,float thetamax,int n,const char *tokens[],const void *params[]);
	void				RiDiskV(float height,float radius,float thetamax,int n,const char *tokens[],const void *params[]);
	void				RiTorusV(float majorrad,float minorrad,float phimin,float phimax,float thetamax,int n,const char *tokens[],const void *params[]);
	void				RiProcedural(void * data,float *bound,void (*subdivfunc)(void *,float),void (*freefunc)(void *));
	void				RiGeometryV(const char * type,int n,const char *tokens[],const void *params[]);

	void				RiCurvesV(const char * degree,int ncurves,int nverts[],const char * wrap,int n,const char *tokens[],const void *params[]);
	void				RiPointsV(int npts,int n,const char *tokens[],const void *params[]);
	void				RiSubdivisionMeshV(const char * scheme,int nfaces,int nvertices[],int vertices[],int ntags,const char * tags[],int nargs[],int intargs[],float floatargs[],int n,const char *tokens[],const void *params[]);
	void				RiBlobbyV(int nleaf,int ncode,int code[],int nflt,float flt[],int nstr,const char *str[],int n,const char *tokens[],const void *params[]);

	void				RiSolidBegin(const char * type);
	void				RiSolidEnd(void);
	void				*RiObjectBegin(void);

	void				RiObjectEnd(void);
	void				RiObjectInstance(const void *handle);
	void				RiMotionBeginV(int N,float times[]);
	void				RiMotionEnd(void);

	void				RiMakeTextureV(const char *pic,const char *tex,const char * swrap,const char * twrap,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,const char *tokens[],const void *params[]);
	void				RiMakeBumpV(const char *pic,const char *tex,const char * swrap,const char * twrap,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,const char *tokens[],const void *params[]);
	void				RiMakeLatLongEnvironmentV(const char *pic,const char *tex,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,const char *tokens[],const void *params[]);
	void				RiMakeCubeFaceEnvironmentV(const char *px,const char *nx,const char *py,const char *ny,const char *pz,const char *nz,const char *tex,float fov,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,const char *tokens[],const void *params[]);
	void				RiMakeShadowV(const char *pic,const char *tex,int n,const char *tokens[],const void *params[]);
	void				RiMakeBrickMapV(int nb,const char **src,const char *dest,int n,const char *tokens[],const void *params[]);

	void				RiArchiveRecord(const char * type,const char *format,va_list args);
	void				RiReadArchiveV(const char *filename,void (*callback)(const char *,...),int n,const char *tokens[],const void *params[]);

	void				*RiArchiveBeginV(const char *name, int n,const char *tokens[],const void *parms[]);
	void				RiArchiveEnd(void);
	
	void				RiResourceV(const char *handle,const char *type,int n,const char *tokens[],const void *parms[]);
	void				RiResourceBegin(void);
	void				RiResourceEnd(void);

	void				RiIfBeginV(const char *expr,int n,const char *tokens[],const void *parms[]);
	void				RiElseIfV(const char *expr,int n,const char *tokens[],const void *parms[]);
	void				RiElse(void);
	void				RiIfEnd(void);

	void				RiError(int,int,const char *);


	// The following functions provide access to the graphics state
	CXform				*getXform(int);										// Get the active XForm
	CAttributes			*getAttributes(int);								// Get the active Attributes
	COptions			*getOptions();										// Get the active Options
	CShaderInstance		*getShader(const char *,int,int,const char **,const void **);	// Load a shader

																			// Delayed object junk
	void				processDelayedObject(CShadingContext *context,CDelayedObject *,void	(*subdivisionFunction)(void *,float),void *,const float *,const float *);
	void				processDelayedInstance(CShadingContext *context,CDelayedInstance *instance);

	void				addObject(CObject *);								// Add an object into the scene
	void				addInstance(const void *);								// Add an instance into the scene
	void				rendererThread(const void *);

private:

	///////////////////////////////////////////////////////////////////////
	// Class				:	CInstance
	// Description			:	This class is allocated at objectBegin only to hold
	//							a list of objects
	// Comments				:
	class	CInstance {
	public:
			CObject			*objects;
	};

	CArray<CXform *>			*savedXforms;				// Used to save/restore the graphics state
	CArray<CAttributes *>		*savedAttributes;			// Saved attributes
	CArray<COptions *>			*savedOptions;				// Saved options
	CArray<CResource *>			*savedResources;			// Saved resources
	CInstance					*instance;					// The current instance object
	CObject						*delayed;					// The current delayed object
	CArray<CInstance *>			*instanceStack;				// The stack of object lists
	CArray<CInstance *>			*allocatedInstances;		// The list of allocated object instances
	CXform						*currentXform;				// The current graphics state
	CAttributes					*currentAttributes;
	COptions					*currentOptions;
	CResource					*currentResource;
															// Some RenderMan Interface related variables
	int							numExpectedMotions;			// The number of expected motions in a motion block
	int							numMotions;					// The number of motions so far
	float						*keyTimes;					// The key times
	float						*motionParameters;			// The arrays of motion parameters
	int							maxMotionParameters;		// The maximum number of motion parameters that can be stored
	const char					*lastCommand;				// The text of the last motion command
	int							riExecTag;					// The exec tag count for the RI interface

	void						init(CProgrammableShaderInstance *);		// Execute the init code of a shader
	int							ifParse(const char *expr);	// Evaluate a condition
	int							addMotion(float *parameters,int parameterSize,const char *name,float *&p0,float *&p1);
};


#endif

