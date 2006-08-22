//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright © 1999 - 2003, Okan Arikan
//
// Contact: okan@cs.berkeley.edu
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
// 
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
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
#include "riInterface.h"
#include "variable.h"

// Textual definitions of predefined coordinate systems
extern	const char	*coordinateCameraSystem;
extern	const char	*coordinateWorldSystem;
extern	const char	*coordinateObjectSystem;
extern	const char	*coordinateShaderSystem;
extern	const char	*coordinateLightSystem;
extern	const char	*coordinateNDCSystem;
extern	const char	*coordinateRasterSystem;
extern	const char	*coordinateScreenSystem;
extern	const char	*coordinateCurrentSystem;

// Textual definitions of the predefined color systems
extern	const char	*colorRgbSystem;
extern	const char	*colorHslSystem;
extern	const char	*colorHsvSystem;
extern	const char	*colorXyzSystem;
extern	const char	*colorYiqSystem;
extern	const char	*colorXyySystem;
extern	const char	*colorCieSystem;

///////////////////////////////////////////////////////////////////////
// Class				:	CNamedCoordinateSystem
// Description			:	Holds a coordinate system
// Comments				:
// Date last edited		:	10/13/2001
class  CNamedCoordinateSystem {
public:
	char				name[64];		// Name of the coordinate system
	ECoordinateSystem	systemType;		// If the system is one of the standard ones
	matrix				from;			// The transformation
	matrix				to;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CDSO
// Description			:	Holds a DSO shader info
// Comments				:
// Date last edited		:	8/05/2002
class	CDSO {
public:
	void				*handle;		// The handle to the module that implements the DSO shader
	dsoInitFunction		init;			// Init function
	dsoExecFunction		exec;			// Execute function
	dsoCleanupFunction	cleanup;		// Cleanup function
	char				*name;			// Name of the DSO shader
	char				*prototype;		// Prototype of the DSO shader
	CDSO				*next;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CGlobalIdentifier
// Description			:	Holds a global identifier
// Comments				:
// Date last edited		:	10/13/2001
class  CGlobalIdentifier {
public:
	char				name[64];		// Name of the identifier
	int					id;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CDisplayChannel
// Description			:	Holds information on a display channel
// Comments				:	if variable is NULL and entry is -1 this is
//						:	one of the standard rgbaz channels
//						:	sampleStart is filled at render time
// Date last edited		:	03/08/2006
class  CDisplayChannel {
public:
	CDisplayChannel();
	~CDisplayChannel();
	CDisplayChannel(const char*,CVariable*,int,int,int entry = -1);
	
	char				name[64];		// Name of the channel
	CVariable			*variable;		// The variable representing channel (may be NULL)
	int					numSamples;		// The size of channel sample
	int					outType;		// The entry index of the variable
	int					sampleStart;	// The offset in the shaded vertex array (-1 is unassigned)
	float				*fill;			// The sample defaults
};

class	COutput;
class	CShadingContext;
class	CIrradianceCache;
class	CPhotonMap;
class	CParticipatingMedium;
class	CDelayedObject;
class	CNetFileMapping;

///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Description			:	Holds the global rendering context
// Comments				:
// Date last edited		:	10/13/2001
class	CRendererContext : public CRiInterface {
public:

						CRendererContext(char *ribName=NULL,char *netString=NULL);
						~CRendererContext();

	///////////////////////////////////////////////////////////////////////
	// Renderer interface
	///////////////////////////////////////////////////////////////////////
	void				RiDeclare(char *,char *);

	void				RiFrameBegin(int);
	void				RiFrameEnd(void);
	void				RiWorldBegin(void);
	void				RiWorldEnd(void);

	void				RiFormat(int xres,int yres,float aspect);
	void				RiFrameAspectRatio(float aspect);
	void				RiScreenWindow(float left,float right,float bot,float top);
	void				RiCropWindow(float xmin,float xmax,float ymin,float ymax);
	void				RiProjectionV(char *name,int n,char *tokens[],void *params[]);
	void				RiClipping(float hither,float yon);
	void				RiClippingPlane(float x,float y,float z,float nx,float ny,float nz);
	void				RiDepthOfField(float fstop,float focallength,float focaldistance);
	void				RiShutter(float smin,float smax);

	void				RiPixelVariance(float variation);
	void				RiPixelSamples(float xsamples,float ysamples);
	void				RiPixelFilter(float (*function)(float,float,float,float),float xwidth,float ywidth);
	void				RiExposure(float gain,float gamma);
	void				RiImagerV(char *name,int n,char *tokens[],void *params[]);
	void				RiQuantize(char * type,int one,int qmin,int qmax,float ampl);
	void				RiDisplayV(char *name,char * type,char * mode,int n,char *tokens[],void *params[]);
	void				RiDisplayChannelV(char * channel,int n,char *tokens[],void *params[]);

	void				RiHiderV(char * type,int n,char *tokens[],void *params[]);
	void				RiColorSamples(int N,float *nRGB,float *RGBn);
	void				RiRelativeDetail(float relativedetail);
	void				RiOptionV(char *name,int n,char *tokens[],void *params[]);

	void				RiAttributeBegin(void);
	void				RiAttributeEnd(void);
	void				RiColor(float *Cs);
	void				RiOpacity(float *Cs);
	void				RiTextureCoordinates(float s1,float t1,float s2,float t2,float s3,float t3,float s4,float t4);

	void				*RiLightSourceV(char *name,int n,char *tokens[],void *params[]);
	void				*RiAreaLightSourceV(char *name,int n,char *tokens[],void *params[]);

	void				RiIlluminate(void *light,int onoff);
	void				RiSurfaceV(char *name,int n,char *tokens[],void *params[]);
	void				RiAtmosphereV(char *name,int n,char *tokens[],void *params[]);
	void				RiInteriorV(char *name,int n,char *tokens[],void *params[]);
	void				RiExteriorV(char *name,int n,char *tokens[],void *params[]);
	void				RiShadingRate(float size);
	void				RiShadingInterpolation(char * type);
	void				RiMatte(int onoff);

	void				RiBound(float *bound);
	void				RiDetail(float *bound);
	void				RiDetailRange(float minvis,float lowtran,float uptran,float maxvis);
	void				RiGeometricApproximation(char * type,float value);
	void				RiGeometricRepresentation(char * type);
	void				RiOrientation(char * orientation),RiReverseOrientation(void);
	void				RiSides(int nsides);

	void				RiIdentity(void);
	void				RiTransform(float transform[][4]);
	void				RiConcatTransform(float transform[][4]);
	void				RiPerspective(float fov);
	void				RiTranslate(float dx,float dy,float dz);
	void				RiRotate(float angle,float dx,float dy,float dz);
	void				RiScale(float dx,float dy,float dz);
	void				RiSkew(float angle,float dx1,float dy1,float dz1,float dx2,float dy2,float dz2);
	void				RiDeformationV(char *name,int n,char *tokens[],void *params[]);
	void				RiDisplacementV(char *name,int n,char *tokens[],void *params[]);
	void				RiCoordinateSystem(char * space);
	void				RiCoordSysTransform(char * space);

	void				RiTransformPoints(char *fromspace,char *tospace,int npoints,float points[][3]);

	void				RiTransformBegin(void);
	void				RiTransformEnd(void);

	void				RiAttributeV(char *name,int n,char *tokens[],void *params[]);

	void				RiPolygonV(int nvertices,int n,char *tokens[],void *params[]);
	void				RiGeneralPolygonV(int nloops,int *nverts,int n,char *tokens[],void *params[]);
	void				RiPointsPolygonsV(int npolys,int *nverts,int *verts,int n,char *tokens[],void *params[]);
	void				RiPointsGeneralPolygonsV(int npolys,int *nloops,int *nverts,int *verts,int n,char *tokens[],void *params[]);
	void				RiBasis(float ubasis[][4],int ustep,float vbasis[][4],int vstep);
	void				RiPatchV(char * type,int n,char *tokens[],void *params[]);
	void				RiPatchMeshV(char * type,int nu,char * uwrap,int nv,char * vwrap,int n,char *tokens[],void *params[]);
	void				RiNuPatchV(int nu,int uorder,float *uknot,float umin,float umax,int nv,int vorder,float *vknot,float vmin,float vmax,int n,char *tokens[],void *params[]);
	void				RiTrimCurve(int nloops,int *ncurves,int *order,float *knot,float *amin,float *amax,int *n,float *u,float *v,float *w);

	void				RiSphereV(float radius,float zmin,float zmax,float thetamax,int n,char *tokens[],void *params[]);
	void				RiConeV(float height,float radius,float thetamax,int n,char *tokens[],void *params[]);
	void				RiCylinderV(float radius,float zmin,float zmax,float thetamax,int n,char *tokens[],void *params[]);
	void				RiHyperboloidV(float *point1,float *point2,float thetamax,int n,char *tokens[],void *params[]);
	void				RiParaboloidV(float rmax,float zmin,float zmax,float thetamax,int n,char *tokens[],void *params[]);
	void				RiDiskV(float height,float radius,float thetamax,int n,char *tokens[],void *params[]);
	void				RiTorusV(float majorrad,float minorrad,float phimin,float phimax,float thetamax,int n,char *tokens[],void *params[]);
	void				RiProcedural(void * data,float *bound,void (*subdivfunc)(void *,float),void (*freefunc)(void *));
	void				RiGeometryV(char * type,int n,char *tokens[],void *params[]);

	void				RiCurvesV(char * degree,int ncurves,int nverts[],char * wrap,int n,char *tokens[],void *params[]);
	void				RiPointsV(int npts,int n,char *tokens[],void *params[]);
	void				RiSubdivisionMeshV(char * scheme,int nfaces,int nvertices[],int vertices[],int ntags,char * tags[],int nargs[],int intargs[],float floatargs[],int n,char *tokens[],void *params[]);
	void				RiBlobbyV(int nleaf,int ncode,int code[],int nflt,float flt[],int nstr,char *str[],int n,char *tokens[],void *params[]);

	void				RiSolidBegin(char * type);
	void				RiSolidEnd(void);
	void				*RiObjectBegin(void);

	void				RiObjectEnd(void);
	void				RiObjectInstance(void *handle);
	void				RiMotionBeginV(int N,float times[]);
	void				RiMotionEnd(void);

	void				RiMakeTextureV(char *pic,char *tex,char * swrap,char * twrap,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,char *tokens[],void *params[]);
	void				RiMakeBumpV(char *pic,char *tex,char * swrap,char * twrap,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,char *tokens[],void *params[]);
	void				RiMakeLatLongEnvironmentV(char *pic,char *tex,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,char *tokens[],void *params[]);
	void				RiMakeCubeFaceEnvironmentV(char *px,char *nx,char *py,char *ny,char *pz,char *nz,char *tex,float fov,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,char *tokens[],void *params[]);
	void				RiMakeShadowV(char *pic,char *tex,int n,char *tokens[],void *params[]);
	void				RiMakeTexture3DV(char *src,char *dest,int n,char *tokens[],void *params[]);

	void				RiArchiveRecord(char * type,char *format,va_list args);
	void				RiReadArchiveV(char *filename,void (*callback)(const char *),int n,char *tokens[],void *params[]);

	void				RiTrace(int,float [][3],float [][3],float [][3]);
	void				RiTrace(int,float [][3],float [][3],float [][3],float []);
	void				RiVisibility(int,float [][3],float [][3],float [][3]);

	void				RiError(int,int,char *);


	// The following functions provide access to the graphics state
	CXform				*getXform(int);											// Get the active XForm
	CAttributes			*getAttributes(int);									// Get the active Attributes
	COptions			*getOptions();											// Get the active Options
	CShaderInstance		*getShader(const char *,int,int,char **,void **);		// Load a shader
	RtFilterFunc		getFilter(const char *);								// Get a filter
	char				*getFilter(RtFilterFunc);								// The other way around
	int					getDSO(char *,char *,void *&,dsoExecFunction &);		// Find a DSO

	CTexture			*textureLoad(const char *,TSearchpath *);				// Load a new texture map
	CEnvironment		*environmentLoad(const char *,TSearchpath *,float *);	// Load a new environment map

																				// Delayed object junk
	void				processDelayedObject(CDelayedObject *,void	(*subdivisionFunction)(void *,float),void *,const float *,const float *,CRay *ray = NULL);

	void				addObject(CObject *);									// Add an object into the scene
	void				addInstance(void *);									// Add an instance into the scene

																				// Coordinate system functions
	void				defineCoordinateSystem(const char *,matrix &,matrix &,ECoordinateSystem type = COORDINATE_CUSTOM);
	int					findCoordinateSystem(const char *,matrix *&,matrix *&,ECoordinateSystem &);
																				// Variable management
	CVariable			*declareVariable(const char *,const char *,int um = 0);
	void				makeGlobalVariable(CVariable *);
	CVariable			*retrieveVariable(const char *);
	
	CDisplayChannel		*declareDisplayChannel(const char *);					// Display channel management
	CDisplayChannel		*declareDisplayChannel(CVariable *);
	CDisplayChannel		*retrieveDisplayChannel(const char *);
	void				resetDisplayChannelUsage();
	
	void				registerFrameTemporary(const char *,int);				// Register file for end-of-frame deletion

	int					getGlobalID(const char *);								// Global ID management

																				// Locate (download) a file
	int					locateFileEx(char *,const char *,const char *extension=NULL,TSearchpath *search=NULL);
	int					locateFile(char *,const char *,TSearchpath *search=NULL);

																				// The following functions are about texture management and are implemented in texture.cpp
	void				rendererThread(void *);

private:
	CDictionary<const char *,CNamedCoordinateSystem *>	*definedCoordinateSystems;	// This holds the named coordinate systems defined for this context
	CDictionary<const char *,CVariable *>				*declaredVariables;			// Declared variables
	CDictionary<const char *,CFileResource  *>			*loadedFiles;				// Files that have been loaded
	CDictionary<const char *,CGlobalIdentifier *>		*globalIdHash;				// This holds global string to id mappings (light categories for example)
	CDictionary<const char *,CNetFileMapping *>			*netFileMappings;			// This holds name->name mappings of files
	CArray<const char*>									*frameTemporaryFiles;		// This hold the name of temporary files
	int													numKnownGlobalIds;
	CVariable											*variables;					// List of all defined variables
	int													numGlobalVariables;			// The number of global variables
	CDictionary<const char *,CDisplayChannel *>			*declaredChannels;			// The declared display channels
	CArray<CDisplayChannel*>							*displayChannels;			// The list of all desclared display channels
	CArray<CXform *>									*savedXforms;				// Used to save/restore the graphics state
	CArray<CAttributes *>								*savedAttributes;
	CArray<COptions *>									*savedOptions;
	CArray<CObject *>									*objects;					// The list of all objects recorded so far
	CArray<CArray<CObject *> *>							*objectsStack;				// The stack of object lists
	CArray<CArray<CObject *> *>							*allocatedInstances;		// The list of allocated object instances
	CXform				*currentXform;											// The current graphics state
	CAttributes			*currentAttributes;
	COptions			*currentOptions;
	CDSO				*dsos;													// The list of DSO's that have been loaded
	SOCKET				netClient;												// The client that we're serving (-1 if client)
	int					netNumServers;											// The number of servers (0 if server)
	SOCKET				*netServers;											// The array of servers that are serving us
	TMutex				commitMutex;											// The mutex that controls job dispatch
	CShadingContext		*renderer;												// The renderer doing the current world block
	int					userRaytracing;											// TRUE if we're raytracing for the user
	int					numNetrenderedBuckets;									// The number of netrendered buckets

																				// Some RenderMan Interface related variables
	int					numExpectedMotions;										// The number of expected motions in a motion block
	int					numMotions;												// The number of motions so far
	float				*keyTimes;												// The key times
	float				*motionParameters;										// The arrays of motion parameters
	int					maxMotionParameters;									// The maximum number of motion parameters that can be stored
	char				*lastCommand;											// The text of the last motion command

	void				netSetup(char *,char *);								// Setup the network for rendering
	void				sendFile(int,char *,int,int);							// Send a particular file
	int					getFile(char *,const char *);							// Get a particular file from network
	int					getFile(FILE *,const char *,int start=0,int size=0);	// Get a particular file from network
	void				clientRenderFrame();									// Isn't that obvious
	void				processServerRequest(T32,int);							// Process a request from the server
	void				init(CProgrammableShaderInstance *);					// Execute the init code of a shader
	int					loadDSO(char *,char *,TSearchpath *,dsoInitFunction *,dsoExecFunction *,dsoCleanupFunction *);	// Find/load a DSO shader
	int					addMotion(float *parameters,int parameterSize,char *name,float *&p0,float *&p1);
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	The global variables
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern	CRendererContext	*currentRenderer;

// Some global functions
void	rcSend(SOCKET,char *,int,int net = TRUE);								// Send data
void	rcRecv(SOCKET,char *,int,int net = TRUE);								// Recv data


#endif


