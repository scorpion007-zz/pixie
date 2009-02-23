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
//  File				:	rimain.h
//  Classes				:	-
//  Description			:	RenderMan Header
//
////////////////////////////////////////////////////////////////////////
#ifndef PIXIE
#define PIXIE

#ifdef __cplusplus
extern "C" {
#endif

#ifdef RENDERER
#if defined(_WINDOWS) || defined(WIN32)
#define	EXTERN(type)	extern __declspec(dllexport) type
#else
#define EXTERN(type)	extern type
#endif
#else
#if defined(_WINDOWS) || defined(WIN32)
#define	EXTERN(type)	extern __declspec(dllimport) type
#else
#define EXTERN(type)	extern type
#endif
#endif


////////////////////////////////////////////////////////////////////////
//
//	Type definitions
//
////////////////////////////////////////////////////////////////////////
typedef short		RtBoolean;
typedef int			RtInt;
typedef float		RtFloat;
typedef const char	*RtToken;
typedef	void		RtVoid;
typedef const char	*RtString;
typedef const void	*RtPointer;
typedef RtFloat		RtColor[3];
typedef RtFloat		RtPoint[3];
typedef RtFloat		RtMatrix[4][4];
typedef RtFloat		RtBasis[4][4];
typedef RtFloat		RtBound[6];
typedef RtPointer	RtObjectHandle;
typedef RtPointer	RtLightHandle;
typedef RtPointer	RtContextHandle;
typedef RtString	RtArchiveHandle;
typedef RtString	RtShaderHandle;
typedef RtFloat		(*RtFilterFunc)(RtFloat, RtFloat, RtFloat, RtFloat);
typedef RtFloat		(*RtStepFilterFunc)(RtFloat, RtFloat, RtFloat);
typedef RtVoid		(*RtErrorHandler)(RtInt code, RtInt severity,const char *msg);
typedef RtVoid		(*RtFunc)(const char *);
typedef RtVoid		(*RtArchiveCallback)(const char *,...);

typedef void		*(*RtDisplayParameterFunction)(const char *,int,int);
typedef	void		*(*RtDisplayStartFunction)(const char *,int,int,int,const char *,RtDisplayParameterFunction);
typedef int			(*RtDisplayDataFunction)(void *,int,int,int,int,float *);
typedef int			(*RtDisplayRawDataFunction)(void *,int,int,int,int,void *);
typedef void		(*RtDisplayFinishFunction)(void *);


#define RI_FALSE    0
#define RI_TRUE     1
#define RI_INFINITY (RtFloat)1.0e38
#define RI_EPSILON  (RtFloat)1.0e-10

#define RI_NULL		((RtToken)0)


////////////////////////////////////////////////////////////////////////
//
//	Standard tokens
//
////////////////////////////////////////////////////////////////////////
EXTERN(RtToken)	 RI_FRAMEBUFFER, RI_FILE;
EXTERN(RtToken)  RI_RGB, RI_RGBA, RI_RGBZ, RI_RGBAZ, RI_A, RI_Z, RI_AZ;
EXTERN(RtToken)  RI_PERSPECTIVE, RI_ORTHOGRAPHIC;
EXTERN(RtToken)  RI_HIDDEN, RI_PAINT;
EXTERN(RtToken)  RI_CONSTANT, RI_SMOOTH;
EXTERN(RtToken)  RI_FLATNESS, RI_FOV;
EXTERN(RtToken)  RI_AMBIENTLIGHT, RI_POINTLIGHT, RI_DISTANTLIGHT, RI_SPOTLIGHT;
EXTERN(RtToken)  RI_INTENSITY, RI_LIGHTCOLOR, RI_FROM, RI_TO, RI_CONEANGLE, RI_CONEDELTAANGLE, RI_BEAMDISTRIBUTION;
EXTERN(RtToken)  RI_MATTE, RI_METAL, RI_SHINYMETAL, RI_PLASTIC, RI_PAINTEDPLASTIC;
EXTERN(RtToken)  RI_KA, RI_KD, RI_KS, RI_ROUGHNESS, RI_KR, RI_TEXTURENAME, RI_SPECULARCOLOR;
EXTERN(RtToken)  RI_DEPTHCUE, RI_FOG, RI_BUMPY;
EXTERN(RtToken)  RI_MINDISTANCE, RI_BACKGROUND, RI_DISTANCE, RI_AMPLITUDE;
EXTERN(RtToken)  RI_RASTER, RI_SCREEN, RI_CAMERA, RI_WORLD, RI_OBJECT;
EXTERN(RtToken)  RI_INSIDE, RI_OUTSIDE, RI_LH, RI_RH;
EXTERN(RtToken)  RI_P, RI_PZ, RI_PW, RI_N, RI_NP, RI_CS, RI_OS, RI_S, RI_T, RI_ST;
EXTERN(RtToken)  RI_BILINEAR, RI_BICUBIC;
EXTERN(RtToken)  RI_PRIMITIVE, RI_INTERSECTION, RI_UNION, RI_DIFFERENCE;
EXTERN(RtToken)  RI_PERIODIC, RI_NOWRAP, RI_NONPERIODIC, RI_CLAMP, RI_BLACK;
EXTERN(RtToken)  RI_IGNORE, RI_PRINT, RI_ABORT, RI_HANDLER;
EXTERN(RtToken)  RI_ORIGIN, RI_IDENTIFIER, RI_NAME;
EXTERN(RtToken)  RI_COMMENT, RI_STRUCTURE, RI_VERBATIM;
EXTERN(RtToken)  RI_LINEAR, RI_CUBIC, RI_WIDTH, RI_CONSTANTWIDTH;
EXTERN(RtToken)	 RI_CATMULLCLARK,RI_HOLE,RI_CREASE,RI_CORNER,RI_INTERPOLATEBOUNDARY;
EXTERN(RtToken)  RI_CURRENT, RI_WORLD, RI_OBJECT, RI_SHADER;
EXTERN(RtToken)  RI_RASTER, RI_NDC, RI_SCREEN, RI_CAMERA, RI_EYE;


////////////////////////////////////////////////////////////////////////
//
//	Recognized filter types
//
////////////////////////////////////////////////////////////////////////
EXTERN(RtToken)	RI_BOXFILTER;
EXTERN(RtToken)	RI_TRIANGLEFILTER;
EXTERN(RtToken)	RI_GAUSSIANFILTER;
EXTERN(RtToken)	RI_SINCFILTER;
EXTERN(RtToken)	RI_CATMULLROMFILTER;
EXTERN(RtToken)	RI_BLACKMANHARRISFILTER;
EXTERN(RtToken)	RI_MITCHELLFILTER;
EXTERN(RtToken)	RI_BESSELFILTER;
EXTERN(RtToken)	RI_DISKFILTER;
EXTERN(RtToken)	RI_CUSTOM;

EXTERN(RtToken)	RI_MIN;
EXTERN(RtToken)	RI_MAX;
EXTERN(RtToken)	RI_AVERAGE;
EXTERN(RtToken)	RI_ZMIN;
EXTERN(RtToken)	RI_ZMAX;




////////////////////////////////////////////////////////////////////////
//
//	Non-Standard options/attributes entry points
//
////////////////////////////////////////////////////////////////////////
EXTERN(RtToken)		RI_LIMITS;
EXTERN(RtToken)		RI_SEARCHPATH;
EXTERN(RtToken)		RI_SHADOW;
EXTERN(RtToken)		RI_RENDER;
EXTERN(RtToken)		RI_DICE;
EXTERN(RtToken)		RI_HINT;
EXTERN(RtToken)		RI_TEXTURE;
EXTERN(RtToken)		RI_HIDER;
EXTERN(RtToken)		RI_STATISTICS;
EXTERN(RtToken)		RI_VISIBILITY;
EXTERN(RtToken)		RI_SHADE;
EXTERN(RtToken)		RI_DISPLACEMENTBOUND;
EXTERN(RtToken)		RI_IRRADIANCE;
EXTERN(RtToken)		RI_CULL;
EXTERN(RtToken)		RI_COMPRESSION;
EXTERN(RtToken)		RI_RIB;
EXTERN(RtToken)		RI_SHUTTER;
EXTERN(RtToken)		RI_USER;

////////////////////////////////////////////////////////////////////////
//
//	Non-Standard attributes
//
////////////////////////////////////////////////////////////////////////

// The geometric approximation types
EXTERN(RtToken)		RI_NORMALDEVIATION;
EXTERN(RtToken)		RI_POINTDEVIATION;

// Dice attributes
EXTERN(RtToken)		RI_MINSUBDIVISION;
EXTERN(RtToken)		RI_MAXSUBDIVISION;
EXTERN(RtToken)		RI_NUMPROBES;
EXTERN(RtToken)		RI_MINSPLITS;
EXTERN(RtToken)		RI_BOUNDEXPAND;
EXTERN(RtToken)		RI_BINARY;
EXTERN(RtToken)		RI_RASTERORIENT;

// Displacementbound attributes
EXTERN(RtToken)		RI_SPHERE;
EXTERN(RtToken)		RI_COORDINATESYSYTEM;

// Visibility attributes
EXTERN(RtToken)		RI_PHOTON;
EXTERN(RtToken)		RI_SHADOW;
EXTERN(RtToken)		RI_ENVIRONMENT;
EXTERN(RtToken)		RI_DIFFUSE;
EXTERN(RtToken)		RI_SPECULAR;
EXTERN(RtToken)		RI_TRACE;
EXTERN(RtToken)		RI_TRANSMISSION;
EXTERN(RtToken)		RI_CAUSTICS;

// Shade attributes
EXTERN(RtToken)		RI_DIFFUSEHITMODE;
EXTERN(RtToken)		RI_SPECULARHITMODE;
EXTERN(RtToken)		RI_TRANSMISSIONHITMODE;
EXTERN(RtToken)		RI_CAMERAHITMODE;

// Photon map attributes
EXTERN(RtToken)		RI_GLOBALMAP;
EXTERN(RtToken)		RI_CAUSTICMAP;
EXTERN(RtToken)		RI_ESTIMATOR;
EXTERN(RtToken)		RI_MAXDISTANCE;
EXTERN(RtToken)		RI_SHADINGMODEL;
EXTERN(RtToken)		RI_ILLUMINATEFRONT;
EXTERN(RtToken)		RI_IOR;
EXTERN(RtToken)		RI_IORRANGE;

// Trace attributes
EXTERN(RtToken)		RI_BIAS;
EXTERN(RtToken)		RI_DISPLACEMENTS;
EXTERN(RtToken)		RI_MAXDIFFUSEDEPTH;
EXTERN(RtToken)		RI_MAXSPECULARDEPTH;
EXTERN(RtToken)		RI_SAMPLEMOTION;

// Motionfactor attribute
EXTERN(RtToken)		RI_MOTIONFACTOR;

// Cull attributes
//EXTERN(RtToken)	RI_HIDDEN;
EXTERN(RtToken)		RI_BACKFACING;

////////////////////////////////////////////////////////////////////////
//
//	Non-Standard options
//
////////////////////////////////////////////////////////////////////////

// Searchpath options
EXTERN(RtToken)		RI_ARCHIVE;
EXTERN(RtToken)		RI_PROCEDURAL;
EXTERN(RtToken)		RI_RESOURCE;
EXTERN(RtToken)		RI_DISPLAY;

// Limits options
EXTERN(RtToken)		RI_BUCKETSIZE;
EXTERN(RtToken)		RI_METABUCKETS;
EXTERN(RtToken)		RI_GRIDSIZE;
EXTERN(RtToken)		RI_MAXRECURSION;
EXTERN(RtToken)		RI_TEXTUREMEMORY;
EXTERN(RtToken)		RI_BRICKMEMORY;
EXTERN(RtToken)		RI_EYESPLITS;
EXTERN(RtToken)		RI_NUMTHREADS;
EXTERN(RtToken)		RI_THREADSTRIDE;
EXTERN(RtToken)		RI_GEOCACHEMEMORY;
EXTERN(RtToken)		RI_OTHRESHOLD;
EXTERN(RtToken)		RI_ZTHRESHOLD;

// Trace options
EXTERN(RtToken)		RI_MAXDEPTH;

// Statistics options
EXTERN(RtToken)		RI_ENDOFFRAME;
EXTERN(RtToken)		RI_FILELOG;
EXTERN(RtToken)		RI_PROGRESS;

// Irradiance options
EXTERN(RtToken)		RI_HANDLE;
EXTERN(RtToken)		RI_FILEMODE;
EXTERN(RtToken)		RI_MAXERROR;
EXTERN(RtToken)		RI_MAXPIXELDIST;
EXTERN(RtToken)		RI_MINSAMPLEDISTANCE;
EXTERN(RtToken)		RI_MAXSAMPLEDISTANCE;

// Hider options
EXTERN(RtToken)		RI_JITTER;
EXTERN(RtToken)		RI_FALSECOLOR;
EXTERN(RtToken)		RI_EMIT;
EXTERN(RtToken)		RI_SAMPLESPECTRUM;
EXTERN(RtToken)		RI_DEPTHFILTER;
EXTERN(RtToken)		RI_RADIANCECACHE;

// IO options
EXTERN(RtToken)		RI_MASKRESOLUTION;
EXTERN(RtToken)		RI_MASKPRINTF;
EXTERN(RtToken)		RI_MASKLOG;
EXTERN(RtToken)		RI_MASKPROGRESS;
EXTERN(RtToken)		RI_MASKSTATS;
EXTERN(RtToken)		RI_INHERITATTRIBUTES;

// Shutter options
EXTERN(RtToken)		RI_OFFSET;

// Misc junk
EXTERN(RtToken)		RI_DEFAULTSURFACE;

EXTERN(RtInt)		RiLastError;

EXTERN(RtBasis)		RiBezierBasis, RiBSplineBasis, RiCatmullRomBasis, RiHermiteBasis, RiPowerBasis, RiLinearBasis;

#define RI_BEZIERSTEP       ((RtInt)3)
#define RI_BSPLINESTEP      ((RtInt)1)
#define RI_CATMULLROMSTEP   ((RtInt)1)
#define RI_HERMITESTEP      ((RtInt)2)
#define RI_POWERSTEP        ((RtInt)4)


////////////////////////////////////////////////////////////////////////
//
//	Delarations of All of the RenderMan Interface Subroutines
//
////////////////////////////////////////////////////////////////////////

EXTERN(RtToken)
    RiDeclare (const char *name,const char *declaration);

EXTERN(RtContextHandle)
	RiGetContext(void);

EXTERN(RtVoid)
	RiContext(RtContextHandle);

EXTERN(RtVoid)
    RiBegin (RtToken name), RiEnd (void),
    RiFrameBegin (RtInt number), RiFrameEnd (void),
    RiWorldBegin (void), RiWorldEnd (void);

EXTERN(RtVoid)
    RiFormat (RtInt xres, RtInt yres, RtFloat aspect),
    RiFrameAspectRatio (RtFloat aspect),
    RiScreenWindow (RtFloat left, RtFloat right, RtFloat bot, RtFloat top),
    RiCropWindow (RtFloat xmin, RtFloat xmax, RtFloat ymin, RtFloat ymax),
    RiProjection (const char *name, ...),
    RiProjectionV (const char *name, RtInt n, RtToken tokens[], RtPointer params[]),
    RiClipping (RtFloat hither, RtFloat yon),
	RiClippingPlane(RtFloat x,RtFloat y,RtFloat z,RtFloat nx,RtFloat ny,RtFloat nz),
    RiDepthOfField (RtFloat fstop, RtFloat focallength, RtFloat focaldistance),
    RiShutter (RtFloat smin, RtFloat smax);

EXTERN(RtVoid)
    RiPixelVariance (RtFloat variation),
    RiPixelSamples (RtFloat xsamples, RtFloat ysamples),
    RiPixelFilter (RtFilterFunc function, RtFloat xwidth, RtFloat ywidth),
    RiExposure (RtFloat gain, RtFloat gamma),
    RiImager (const char *name, ...),
    RiImagerV (const char *name, RtInt n, RtToken tokens[], RtPointer params[]),
    RiQuantize (RtToken type, RtInt one, RtInt qmin, RtInt qmax, RtFloat ampl),
    RiDisplay (const char *name, RtToken type, RtToken mode, ...),
    RiDisplayV (const char *name, RtToken type, RtToken mode, RtInt n, RtToken tokens[], RtPointer params[]),
	RiCustomDisplay (const char *name, RtToken mode, RtDisplayStartFunction, RtDisplayDataFunction, RtDisplayFinishFunction, ...),
    RiCustomDisplayV (const char *name, RtToken mode, RtDisplayStartFunction, RtDisplayDataFunction, RtDisplayFinishFunction, RtInt n, RtToken tokens[], RtPointer params[]),
	RiDisplayChannel (RtToken channel, ...),
    RiDisplayChannelV (RtToken channel,RtInt n, RtToken tokens[], RtPointer params[]);

EXTERN(RtFloat)
    RiGaussianFilter (RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth),
    RiBoxFilter (RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth),
    RiTriangleFilter (RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth),
	RiMitchellFilter( RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth),
    RiCatmullRomFilter (RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth),
    RiBlackmanHarrisFilter (RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth),
    RiSincFilter (RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth),
    RiBesselFilter (RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth),
    RiDiskFilter (RtFloat x, RtFloat y, RtFloat xwidth, RtFloat ywidth);

EXTERN(RtFloat)
    RiGaussianStepFilter (RtFloat t, RtFloat edge, RtFloat width),
    RiBoxStepFilter (RtFloat t, RtFloat edge, RtFloat width),
    RiTriangleStepFilter (RtFloat t, RtFloat edge, RtFloat width),
	RiMitchellStepFilter (RtFloat t, RtFloat edge, RtFloat width),
    RiCatmullRomStepFilter (RtFloat t, RtFloat edge, RtFloat width);

EXTERN(RtVoid)
    RiHider (RtToken type, ...),
    RiHiderV (RtToken type, RtInt n, RtToken tokens[], RtPointer params[]),
    RiColorSamples (RtInt N, RtFloat *nRGB, RtFloat *RGBn),
    RiRelativeDetail (RtFloat relativedetail),
    RiOption (const char *name, ...),
    RiOptionV (const char *name, RtInt n, RtToken tokens[], RtPointer params[]);

EXTERN(RtVoid)
    RiAttributeBegin (void), RiAttributeEnd (void),
    RiColor (RtColor Cs), RiOpacity (RtColor Cs),
    RiTextureCoordinates (RtFloat s1, RtFloat t1, RtFloat s2, RtFloat t2, RtFloat s3, RtFloat t3, RtFloat s4, RtFloat t4);

EXTERN(RtLightHandle)
    RiLightSource (const char *name, ...),
    RiLightSourceV (const char *name, RtInt n, RtToken tokens[], RtPointer params[]),
    RiAreaLightSource (const char *name, ...),
    RiAreaLightSourceV (const char *name, RtInt n, RtToken tokens[], RtPointer params[]);

EXTERN(RtVoid)
    RiIlluminate (RtLightHandle light, RtBoolean onoff),
    RiSurface (const char *name, ...),
    RiSurfaceV (const char *name, RtInt n, RtToken tokens[], RtPointer params[]),
    RiAtmosphere (const char *name, ...),
    RiAtmosphereV (const char *name, RtInt n, RtToken tokens[], RtPointer params[]),
    RiInterior (const char *name, ...),
    RiInteriorV (const char *name, RtInt n, RtToken tokens[], RtPointer params[]),
    RiExterior (const char *name, ...),
    RiExteriorV (const char *name, RtInt n, RtToken tokens[], RtPointer params[]),
    RiShadingRate (RtFloat size),
    RiShadingInterpolation (RtToken type),
    RiMatte (RtBoolean onoff);

EXTERN(RtVoid)
    RiBound (RtBound bound), RiDetail (RtBound bound),
    RiDetailRange (RtFloat minvis, RtFloat lowtran, RtFloat uptran, RtFloat maxvis),
    RiGeometricApproximation (RtToken type, RtFloat value),
    RiGeometricRepresentation (RtToken type),
    RiOrientation (RtToken orientation), RiReverseOrientation (void),
    RiSides (RtInt nsides);

EXTERN(RtVoid)
    RiIdentity (void),
    RiTransform (RtMatrix transform), RiConcatTransform (RtMatrix transform),
    RiPerspective (RtFloat fov),
    RiTranslate (RtFloat dx, RtFloat dy, RtFloat dz),
    RiRotate (RtFloat angle, RtFloat dx, RtFloat dy, RtFloat dz),
    RiScale (RtFloat dx, RtFloat dy, RtFloat dz),
    RiSkew (RtFloat angle, RtFloat dx1, RtFloat dy1, RtFloat dz1, RtFloat dx2, RtFloat dy2, RtFloat dz2),
    RiDeformation (const char *name, ...),
    RiDeformationV (const char *name, RtInt n, RtToken tokens[], RtPointer params[]),
    RiDisplacement (const char *name, ...),
    RiDisplacementV (const char *name, RtInt n, RtToken tokens[], RtPointer params[]),
    RiCoordinateSystem (RtToken space),
    RiCoordSysTransform (RtToken space);

EXTERN(RtPoint *) 
	RiTransformPoints (RtToken fromspace, RtToken tospace, RtInt npoints, RtPoint *points);

EXTERN(RtVoid) 
	RiTransformBegin (void), 
	RiTransformEnd (void);

EXTERN(RtVoid)
    RiAttribute (const char *name, ...),
    RiAttributeV (const char *name, RtInt n, RtToken tokens[], RtPointer params[]);

EXTERN(RtVoid)
    RiPolygon (RtInt nvertices, ...),
    RiPolygonV (RtInt nvertices, RtInt n, RtToken tokens[], RtPointer params[]),
    RiGeneralPolygon (RtInt nloops, RtInt *nverts, ...),
    RiGeneralPolygonV (RtInt nloops, RtInt *nverts, RtInt n, RtToken tokens[], RtPointer params[]),
    RiPointsPolygons (RtInt npolys, RtInt *nverts, RtInt *verts, ...),
    RiPointsPolygonsV (RtInt npolys, RtInt *nverts, RtInt *verts, RtInt n, RtToken tokens[], RtPointer params[]),
    RiPointsGeneralPolygons (RtInt npolys, RtInt *nloops, RtInt *nverts, RtInt *verts, ...),
    RiPointsGeneralPolygonsV (RtInt npolys, RtInt *nloops, RtInt *nverts, RtInt *verts, RtInt n, RtToken tokens[], RtPointer params[]),
    RiBasis (RtBasis ubasis, RtInt ustep, RtBasis vbasis, RtInt vstep),
    RiPatch (RtToken type, ...),
    RiPatchV (RtToken type, RtInt n, RtToken tokens[], RtPointer params[]),
    RiPatchMesh (RtToken type, RtInt nu, RtToken uwrap, RtInt nv, RtToken vwrap, ...),
    RiPatchMeshV (RtToken type, RtInt nu, RtToken uwrap, RtInt nv, RtToken vwrap, RtInt n, RtToken tokens[], RtPointer params[]),
    RiNuPatch (RtInt nu, RtInt uorder, RtFloat *uknot, RtFloat umin, RtFloat umax, RtInt nv, RtInt vorder, RtFloat *vknot, RtFloat vmin, RtFloat vmax, ...),
    RiNuPatchV (RtInt nu, RtInt uorder, RtFloat *uknot, RtFloat umin, RtFloat umax, RtInt nv, RtInt vorder, RtFloat *vknot, RtFloat vmin, RtFloat vmax, RtInt n, RtToken tokens[], RtPointer params[]),
    RiTrimCurve (RtInt nloops, RtInt *ncurves, RtInt *order, RtFloat *knot, RtFloat *amin, RtFloat *amax, RtInt *n, RtFloat *u, RtFloat *v, RtFloat *w);

EXTERN(RtVoid)
    RiSphere (RtFloat radius, RtFloat zmin, RtFloat zmax, RtFloat thetamax, ...),
    RiSphereV (RtFloat radius, RtFloat zmin, RtFloat zmax, RtFloat thetamax, RtInt n, RtToken tokens[], RtPointer params[]),
    RiCone (RtFloat height, RtFloat radius, RtFloat thetamax, ...),
    RiConeV (RtFloat height, RtFloat radius, RtFloat thetamax, RtInt n, RtToken tokens[], RtPointer params[]),
    RiCylinder (RtFloat radius, RtFloat zmin, RtFloat zmax, RtFloat thetamax, ...),
    RiCylinderV (RtFloat radius, RtFloat zmin, RtFloat zmax, RtFloat thetamax, RtInt n, RtToken tokens[], RtPointer params[]),
    RiHyperboloid (RtPoint point1, RtPoint point2, RtFloat thetamax, ...),
    RiHyperboloidV (RtPoint point1, RtPoint point2, RtFloat thetamax, RtInt n, RtToken tokens[], RtPointer params[]),
    RiParaboloid (RtFloat rmax, RtFloat zmin, RtFloat zmax, RtFloat thetamax, ...),
    RiParaboloidV (RtFloat rmax, RtFloat zmin, RtFloat zmax, RtFloat thetamax, RtInt n, RtToken tokens[], RtPointer params[]),
    RiDisk (RtFloat height, RtFloat radius, RtFloat thetamax, ...),
    RiDiskV (RtFloat height, RtFloat radius, RtFloat thetamax, RtInt n, RtToken tokens[], RtPointer params[]),
    RiTorus (RtFloat majorrad, RtFloat minorrad, RtFloat phimin, RtFloat phimax, RtFloat thetamax, ...),
    RiTorusV (RtFloat majorrad, RtFloat minorrad, RtFloat phimin, RtFloat phimax, RtFloat thetamax, RtInt n, RtToken tokens[], RtPointer params[]),
    RiCurves (RtToken degree, RtInt ncurves, RtInt nverts[], RtToken wrap, ...),
    RiCurvesV (RtToken degree, RtInt ncurves, RtInt nverts[], RtToken wrap, RtInt n, RtToken tokens[], RtPointer params[]),
    RiProcedural (void *data, RtBound bound, RtVoid (*subdivfunc) (void *, RtFloat), RtVoid (*freefunc) (void *)),
    RiGeometry (RtToken type, ...),
    RiGeometryV (RtToken type, RtInt n, RtToken tokens[], RtPointer params[]);

EXTERN(RtVoid)
    RiCurves (RtToken degree, RtInt ncurves, RtInt nverts[], RtToken wrap, ...),
    RiCurvesV (RtToken degree, RtInt ncurves, RtInt nverts[], RtToken wrap, RtInt n, RtToken tokens[], RtPointer params[]),
    RiPoints (RtInt npts,...),
    RiPointsV (RtInt npts, RtInt n, RtToken tokens[], RtPointer params[]),
    RiSubdivisionMesh (RtToken scheme, RtInt nfaces, RtInt nvertices[], RtInt vertices[], RtInt ntags, RtToken tags[], RtInt nargs[], RtInt intargs[], RtFloat floatargs[], ...),
    RiSubdivisionMeshV (RtToken scheme, RtInt nfaces, RtInt nvertices[], RtInt vertices[], RtInt ntags, RtToken tags[], RtInt nargs[], RtInt intargs[], RtFloat floatargs[], RtInt n, RtToken tokens[], RtPointer params[]),
    RiBlobby (RtInt nleaf, RtInt ncode, RtInt code[], RtInt nflt, RtFloat flt[], RtInt nstr, RtString str[], ...),
    RiBlobbyV (RtInt nleaf, RtInt ncode, RtInt code[], RtInt nflt, RtFloat flt[], RtInt nstr, RtString str[], RtInt n, RtToken tokens[], RtPointer params[]);

EXTERN(RtVoid) 
	RiProcDelayedReadArchive (void *data, RtFloat detail),
    RiProcRunProgram (void *data, RtFloat detail),
    RiProcDynamicLoad (void *data, RtFloat detail),
	RiProcFree(void *);

EXTERN(RtVoid)
	RiSolidBegin(RtToken type), 
	RiSolidEnd(void);

EXTERN(RtObjectHandle) 
	RiObjectBegin (void);

EXTERN(RtVoid)
    RiObjectEnd (void),
    RiObjectInstance (RtObjectHandle handle),
    RiMotionBegin (RtInt N, ...),
    RiMotionBeginV (RtInt N, RtFloat times[]),
    RiMotionEnd (void);

EXTERN(RtVoid)
    RiMakeTexture (const char *pic, const char *tex, RtToken swrap, RtToken twrap, RtFilterFunc filterfunc, RtFloat swidth, RtFloat twidth, ...),
    RiMakeTextureV (const char *pic, const char *tex, RtToken swrap, RtToken twrap, RtFilterFunc filterfunc, RtFloat swidth, RtFloat twidth, RtInt n, RtToken tokens[], RtPointer params[]),
    RiMakeBump (const char *pic, const char *tex, RtToken swrap, RtToken twrap, RtFilterFunc filterfunc, RtFloat swidth, RtFloat twidth, ...),
    RiMakeBumpV (const char *pic, const char *tex, RtToken swrap, RtToken twrap, RtFilterFunc filterfunc, RtFloat swidth, RtFloat twidth, RtInt n, RtToken tokens[], RtPointer params[]),
    RiMakeLatLongEnvironment (const char *pic, const char *tex, RtFilterFunc filterfunc, RtFloat swidth, RtFloat twidth, ...),
    RiMakeLatLongEnvironmentV (const char *pic, const char *tex, RtFilterFunc filterfunc, RtFloat swidth, RtFloat twidth, RtInt n, RtToken tokens[], RtPointer params[]),
    RiMakeCubeFaceEnvironment (const char *px, const char *nx, const char *py, const char *ny, const char *pz, const char *nz, const char *tex, RtFloat fov, RtFilterFunc filterfunc, RtFloat swidth, RtFloat twidth, ...),
    RiMakeCubeFaceEnvironmentV (const char *px, const char *nx, const char *py, const char *ny, const char *pz, const char *nz, const char *tex, RtFloat fov, RtFilterFunc filterfunc, RtFloat swidth, RtFloat twidth, RtInt n, RtToken tokens[], RtPointer params[]),
    RiMakeShadow (const char *pic, const char *tex, ...),
    RiMakeShadowV (const char *pic, const char *tex, RtInt n, RtToken tokens[], RtPointer params[]),
	RiMakeBrickMap (int n,const char **src, const char *dest, ...),
	RiMakeBrickMapV(int n,const char **src, const char *dest,RtInt numTokens, RtToken tokens[], RtPointer params[]);

EXTERN(RtVoid)
    RiErrorHandler (RtErrorHandler handler),
    RiErrorIgnore (RtInt code, RtInt severity, const char *message),
    RiErrorPrint (RtInt code, RtInt severity, const char *message),
    RiErrorAbort (RtInt code, RtInt severity, const char *message);

EXTERN(RtVoid)
	RiResource(RtToken handle, RtToken type, ...),
	RiResourceV(RtToken handle, RtToken type,RtInt n, RtToken tokens[], RtPointer parms[]),
	RiResourceBegin(void),
	RiResourceEnd(void);

EXTERN(RtArchiveHandle)
	RiArchiveBegin(RtToken name, ...),
	RiArchiveBeginV(RtToken name, RtInt n, RtToken tokens[], RtPointer parms[]);

EXTERN(RtVoid)
	RiArchiveEnd(void);

EXTERN(RtVoid)
	RiIfBegin(const char *expr, ...),
	RiIfBeginV(const char *expr, RtInt n, RtToken tokens[], RtPointer parms[]),
	RiElseIf(const char *expr, ...),
	RiElseIfV(const char *expr, RtInt n, RtToken tokens[], RtPointer parms[]),
	RiElse(void),
	RiIfEnd(void);

EXTERN(RtVoid)
    RiArchiveRecord (RtToken type, const char *format, ...),
    RiReadArchive (RtString filename, RtArchiveCallback callback, ...),
    RiReadArchiveV (RtString filename, RtArchiveCallback callback, int n, RtToken tokens[], RtPointer params[]);

			


/*
    Error codes

     1 - 10     System and File errors
    11 - 20     Program Limitations
    21 - 40     State Errors
    41 - 60     Parameter and Protocol Errors
    61 - 80     Execution Errors
*/

#define RIE_NOERROR         0

#define RIE_NOMEM           1       /* Out of memory */
#define RIE_SYSTEM          2       /* Miscellaneous system error */
#define RIE_NOFILE          3       /* File nonexistant */
#define RIE_BADFILE         4       /* Bad file format */
#define RIE_VERSION         5       /* File version mismatch */

#define RIE_INCAPABLE      11       /* Optional RI feature */
#define RIE_OPTIONAL       11       /* Optional RI feature */
#define RIE_UNIMPLEMENT    12       /* Unimplemented feature */
#define RIE_LIMIT          13       /* Arbitrary program limit */
#define RIE_BUG            14       /* Probably a bug in renderer */

#define RIE_NOTSTARTED     23       /* RiBegin not called */
#define RIE_NESTING        24       /* Bad begin-end nesting */
#define RIE_NOTOPTIONS     25       /* Invalid state for options */
#define RIE_NOTATTRIBS     26       /* Invalid state for attributes */
#define RIE_NOTPRIMS       27       /* Invalid state for primitives */
#define RIE_ILLSTATE       28       /* Other invalid state */
#define RIE_BADMOTION      29       /* Badly formed motion block */
#define RIE_BADSOLID       30       /* Badly formed solid block */

#define RIE_BADTOKEN       41       /* Invalid token for request */
#define RIE_RANGE          42       /* Parameter out of range */
#define RIE_CONSISTENCY    43       /* Parameters inconsistent */
#define RIE_BADHANDLE      44       /* Bad object/light handle */
#define RIE_NOSHADER       45       /* Can't load requested shader */
#define RIE_MISSINGDATA    46       /* Required parameters not provided */
#define RIE_SYNTAX         47       /* Declare type syntax error */

#define RIE_MATH           61       /* Zerodivide, noninvert matrix, etc. */

#define	RIE_LOG				62
#define	RIE_PROGRESS		63
#define	RIE_PRINTF			64
#define RIE_SCRIPT			65
#define	RIE_BEGIN			66
#define RIE_END				67
#define	RIE_STATS			68

/* Error severity levels */
#define RIE_INFO            0       /* Rendering stats & other info */
#define RIE_WARNING         1       /* Something seems wrong, maybe okay */
#define RIE_ERROR           2       /* Problem.  Results may be wrong */
#define RIE_SEVERE          3       /* So bad you should probably abort */

#ifdef __cplusplus
}
#endif


#endif  /* RI_H */

