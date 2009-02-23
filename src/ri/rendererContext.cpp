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
//  File				:	rendererContext.cpp
//  Classes				:	-
//  Description			:	Renderer implementation
//
////////////////////////////////////////////////////////////////////////
#include <math.h>
#include <float.h>
#include <string.h>
#include <stdarg.h>

#include "common/algebra.h"
#include "common/containers.h"
#include "common/os.h"
#include "ray.h"
#include "object.h"
#include "xform.h"
#include "shader.h"
#include "texture.h"
#include "raytracer.h"
#include "stochastic.h"
#include "zbuffer.h"
#include "rendererContext.h"
#include "patches.h"
#include "ri.h"
#include "rib.h"
#include "shadeop.h"
#include "noise.h"
#include "stats.h"
#include "memory.h"
#include "photonMap.h"
#include "photon.h"
#include "polygons.h"
#include "quadrics.h"
#include "patches.h"
#include "subdivisionCreator.h"
#include "irradiance.h"
#include "random.h"
#include "points.h"
#include "curves.h"
#include "delayed.h"
#include "dso.h"
#include "bundles.h"
#include "texmake.h"
#include "pl.h"
#include "error.h"
#include "hcshader.h"
#include "implicitSurface.h"
#include "dlobject.h"
#include "show.h"
#include "brickmap.h"
#include "displayChannel.h"
#include "ribOut.h"

// include "isfinite" macro on Windows systems
#if defined(_WINDOWS) && (!defined(isfinite))
#define isfinite(x)	_finite(x)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////
// The global variables are defined here
extern	int				ribCommandLineno;					// Defined in rib.y
extern	const char		*ribFile;							// Defined in rib.y
extern	int				ignoreCommand;						// Defined in ri.cpp
extern	CRiInterface	*savedRenderMan;					// Defined in ri.cpp
extern	CRiInterface	*renderMan;							// Defined in ri.cpp

///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	CRendererContext
// Description			:	Ctor
// Return Value			:
// Comments				:
CRendererContext::CRendererContext(const char *ribFile,const char *riNetString) {

	// Initiate the renderer
	CRenderer::beginRenderer(this,ribFile,riNetString);

	// Init the graphics state
	savedXforms						=	new CArray<CXform *>;
	savedAttributes					=	new CArray<CAttributes *>;
	savedOptions					=	new CArray<COptions *>;
	savedResources					=	new CArray<CResource *>;

	// Init the object stack
	instance						=	NULL;
	delayed							=	NULL;
	instanceStack					=	new CArray<CInstance *>;

	// Init the object instance junk
	allocatedInstances				=	new CArray<CInstance *>;

	// Allocate the initial graphics state
	currentResource					=	NULL;
	currentOptions					=	new COptions;
	currentXform					=	new CXform;
	currentAttributes				=	new CAttributes;
	currentXform->attach();
	currentAttributes->attach();

	// Some misc data used in the RI interface
	numExpectedMotions				=	1;
	numMotions						=	0;
	keyTimes						=	NULL;
	motionParameters				=	NULL;
	maxMotionParameters				=	0;
	lastCommand						=	NULL;
	riExecTag						=	0;
}



///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	~CRendererContext
// Description			:	Dtor
// Return Value			:
// Comments				:
CRendererContext::~CRendererContext() {

	// Destroy the misc stuff
	if (keyTimes != NULL)			delete [] keyTimes;
	if (motionParameters != NULL)	delete [] motionParameters;
		

	// Ditch the instance objects created
	CInstance	*cInstance;
	for (cInstance=allocatedInstances->pop();cInstance!=NULL;cInstance=allocatedInstances->pop()) {
		CObject	*cObject;

		// Detach from the objects
		while((cObject = cInstance->objects) != NULL) {
			cInstance->objects	=	cObject->sibling;
			cObject->detach();
		}

		// Get rid of the instance
		delete cInstance;
	}

	// Ditch the allocated instances array
	delete allocatedInstances;

	// Delete the object stack
	assert(instanceStack !=	NULL);
	assert(instanceStack->numItems	==	0);
	delete instanceStack;
	
	// Ditch the current graphics state
	assert(currentOptions				!=	NULL);
	assert(currentXform					!=	NULL);
	assert(currentAttributes			!=	NULL);
	delete currentOptions;
	currentXform->detach();
	currentAttributes->detach();

	assert(savedXforms					!=	NULL);	
	assert(savedAttributes				!=	NULL);	
	assert(savedOptions					!=	NULL);	
	assert(savedResources				!=	NULL);
	assert(savedXforms->numItems		==	0);
	assert(savedAttributes->numItems	==	0);
	assert(savedOptions->numItems		==	0);
	assert(savedResources->numItems		==	0);
	delete savedXforms;
	delete savedAttributes;
	delete savedOptions;
	delete savedResources;

	// Terminate the renderer
	CRenderer::endRenderer();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	getXform
// Description			:	Return the active Xform
// Return Value			:
// Comments				:
CXform		*CRendererContext::getXform(int modify) {
	assert(currentXform	!=	NULL);

	if ((modify) && (currentXform->refCount > 1)) {
		CXform	*nXform	=	new CXform(currentXform);

		currentXform->detach();
		currentXform	=	nXform;

		nXform->attach();
	}

	return currentXform;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	getAttributes
// Description			:	Return the active attributes
// Return Value			:
// Comments				:
CAttributes	*CRendererContext::getAttributes(int modify) {
	assert(currentAttributes	!=	NULL);

	if ((modify) && (currentAttributes->refCount > 1)) {
		CAttributes	*nAttributes	=	new CAttributes(currentAttributes);

		currentAttributes->detach();
		currentAttributes	=	nAttributes;

		nAttributes->attach();
	}

	return currentAttributes;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	getOptions
// Description			:	Return the active options
// Return Value			:
// Comments				:
COptions	*CRendererContext::getOptions() {
	assert(currentOptions	!=	NULL);

	return currentOptions;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	getShader
// Description			:	Create an instance of a shader
// Return Value			:
// Comments				:
CShaderInstance		*CRendererContext::getShader(const char *name,int type,int np,const char **params,const void **vals) {
	CShaderInstance	*cInstance	=	NULL;

	if (strcmp(name,"null") == 0)	return	NULL;

	CShader			*cShader	=	CRenderer::getShader(name,currentOptions->shaderPath);

	if (cShader != NULL) {
		CProgrammableShaderInstance	*instance;

		if (cShader->type != type) {
			error(CODE_NOSHADER,"Shader \"%s\" is not of the expected type\n",name);
			return NULL;
		}

		instance	= new CProgrammableShaderInstance(cShader,currentAttributes,currentXform);
		
		if (type == SL_LIGHTSOURCE) {
			// fill in lighting category
			instance->createCategories();
			
			// Add the new light into the active lights list for the frame
			CRenderer::allLights->push(instance);
		}

		assert(instance != NULL);

		// Execute the init code of the shader
		memBegin(CRenderer::globalMemory);
		init(instance);
		memEnd(CRenderer::globalMemory);

		cInstance	=	instance;
	}

	if (cInstance == NULL) {
		// Look into the hardcoded shaders
		if (strcmp(name,"spherelight") == 0) {
			cInstance	=	new CSphereLight(currentAttributes,currentXform);

			// Add the new light into the active lights list for the frame
			CRenderer::allLights->push(cInstance);
		} else if (strcmp(name,"quadlight") == 0) {
			cInstance	=	new CQuadLight(currentAttributes,currentXform);

			// Add the new light into the active lights list for the frame
			CRenderer::allLights->push(cInstance);
		}
	}

	// If not found, error out
	if (cInstance == NULL) {
		error(CODE_NOSHADER,"Failed to find shader \"%s\"\n",name);
		return NULL;
	}

	// Set the shader parameters
	cInstance->setParameters(np,params,vals);

	return	cInstance;
}





///////////////////////////////////////////////////////////////////////
// Function				:	screenArea
// Description			:	Compute the screen space area of a box
// Return Value			:	The area
// Comments				:
static	float	screenArea(CXform *x,const float *bmin,const float *bmax) {
	float	P[8*3];
	float	t,a;

	// Transform the points
	initv(P	+	0*3,bmin[0],bmin[1],bmin[2]);	mulmp(P + 0*3,x->from,P + 0*3);
	initv(P	+	1*3,bmin[0],bmax[1],bmin[2]);	mulmp(P + 1*3,x->from,P + 1*3);
	initv(P	+	2*3,bmax[0],bmax[1],bmin[2]);	mulmp(P + 2*3,x->from,P + 2*3);
	initv(P	+	3*3,bmax[0],bmin[1],bmin[2]);	mulmp(P + 3*3,x->from,P + 3*3);
	initv(P	+	4*3,bmin[0],bmin[1],bmax[2]);	mulmp(P + 4*3,x->from,P + 4*3);
	initv(P	+	5*3,bmin[0],bmax[1],bmax[2]);	mulmp(P + 5*3,x->from,P + 5*3);
	initv(P	+	6*3,bmax[0],bmax[1],bmax[2]);	mulmp(P + 6*3,x->from,P + 6*3);
	initv(P	+	7*3,bmax[0],bmin[1],bmax[2]);	mulmp(P + 7*3,x->from,P + 7*3);
	
	// Do the projection
	//camera2screen(8,P);
	camera2pixels(8,P);
	
	a		=	0;

#define	sumArea(__i1,__i2,__i3)																				\
	if ((P[__i1*3 + 2] > 0) && (P[__i2*3 + 2] > 0) && (P[__i3*3 + 2] > 0)) {								\
		if ((t = area(P[__i1*3+0],P[__i1*3+1],P[__i2*3+0],P[__i2*3+1],P[__i3*3+0],P[__i3*3+1])) > 0) {		\
			a	+=	t;																						\
		}																									\
	} else return C_INFINITY;

	sumArea(0,3,2);
	sumArea(0,2,1);
	sumArea(4,7,3);
	sumArea(4,3,0);
	sumArea(7,6,2);
	sumArea(7,2,3);
	sumArea(5,4,0);	
	sumArea(5,0,1);
	sumArea(6,5,1);
	sumArea(6,1,2);
	sumArea(5,6,7);
	sumArea(5,7,4);

#undef sumArea

	return (float) (a * 0.5);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	processDelayedObject
// Description			:	Process a delayed primitive
//							i.e. : Raytrace it or add it to the graphics state
// Return Value			:
// Comments				:
void		CRendererContext::processDelayedObject(CShadingContext *context,CDelayedObject *cDelayed,void	(*subdivisionFunction)(void *,float),void *data,const float *bmin,const float *bmax) {

	// Save the current graphics state
	CAttributes	*savedAttributes	=	currentAttributes;
	CXform		*savedXform			=	currentXform;

	// Overwrite the current graphics state
	delayed				=	cDelayed;
	currentAttributes	=	new CAttributes(cDelayed->attributes);	// Duplicate the graphics state of the delayed object
	currentXform		=	new CXform(cDelayed->xform);
	currentAttributes->attach();
	currentXform->attach();

	// Execute the subdivision
	subdivisionFunction(data,screenArea(cDelayed->xform,bmin,bmax));

	// Restore the graphics state back
	currentAttributes->detach();									// Restore the graphics state of the delayed object
	currentXform->detach();
	currentAttributes	=	savedAttributes;
	currentXform		=	savedXform;
	delayed				=	NULL;

	// Create the hierarchy
	cDelayed->setChildren(context,cDelayed->children);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	processDelayedObject
// Description			:	Process a delayed primitive
//							i.e. : Raytrace it or add it to the graphics state
// Return Value			:
// Comments				:
void		CRendererContext::processDelayedInstance(CShadingContext *context,CDelayedInstance *cDelayed) {
	
	// Set the delayed object
	delayed	=	cDelayed;
	
	//CAttributes		*cAttributes	=	cDelayed->attributes;
	CAttributes		*cAttributes	=	NULL;
	if (currentOptions->flags & OPTIONS_FLAGS_INHERIT_ATTRIBUTES) {
		cAttributes		=	getAttributes(FALSE);
	}

	// Instantiate the objects
	CObject	*cObject;
	for (cObject=cDelayed->instance;cObject!=NULL;cObject=cObject->sibling)	cObject->instantiate(cAttributes,cDelayed->xform,this);

	// We're not processing a delayed object anymore
	delayed	=	NULL;

	// Create the hierarchy
	cDelayed->setChildren(context,cDelayed->children);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	addObject
// Description			:	Add an object into the scene
// Return Value			:
// Comments				:
void	CRendererContext::addObject(CObject *o) {
	assert(currentAttributes	!= NULL);
	assert(o					!= NULL);

	// Are we inside objectBegin/objectEnd ?
	if (instance != NULL) {
		o->sibling			=	instance->objects;
		instance->objects	=	o;
		return;
	}

	// Are we processing a delayed object ?
	if (delayed != NULL) {

		// Maintain the object if it is raytraced
		if (o->raytraced())	o->attach();

		// Add the object to the hirarchy
		o->sibling			=	delayed->children;
		delayed->children	=	o;

		return;
	}

	// Make sure we don't delete the object
	o->attach();

	// Are we in the world block ?
	if (CRenderer::world != NULL) {

		// Render the object
		CRenderer::render(o);
	}

	// Processing is done
	o->detach();
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	addInstance
// Description			:	Add an instance of a compound object
// Return Value			:
// Comments				:
void	CRendererContext::addInstance(const void *d) {
	const CInstance		*cInstance		=	(const CInstance *) d;
	if (cInstance->objects != NULL) {
		CXform			*cXform			=	getXform(FALSE);
		CAttributes		*cAttributes	=	getAttributes(FALSE);

		// Instanciate the instance
		addObject(new CDelayedInstance(cAttributes,cXform,cInstance->objects));
	}
}



























///////////////////////////////////////////////////////////////////////
// Function				:	addMotion
// Description			:	Make sure the command is good to go
// Return Value			:	The processing type (see below)
// Comments				:
//	0	-	skip
//	1	-	process single
//	2	-	process double
int		CRendererContext::addMotion(float *parameters,int parameterSize,const char *name,float *&p0,float *&p1) {
	if (numExpectedMotions == 1)	{
		p0	=	parameters;
		return	1;
	}

	// Make sure we have enough memory to hold motion parameters
	if ((parameterSize*numExpectedMotions) > maxMotionParameters) {
		if (motionParameters != NULL) delete [] motionParameters;

		maxMotionParameters	=	parameterSize*numExpectedMotions;
		motionParameters	=	new float[maxMotionParameters];
	}

	// Sanity check
	if (numMotions == 0) {
		lastCommand			=	name;
	} else {
		if (numMotions >= numExpectedMotions) {
			error(CODE_NESTING,"%s: Too many motions in motion block\n",name);
			return 0;
		}

		if (lastCommand != name) {
			error(CODE_NESTING,"%s: Different commands in motion block\n",name);
			return 0;
		}
	}

	memcpy(motionParameters+parameterSize*numMotions,parameters,parameterSize*sizeof(float));
	numMotions++;

	if (numExpectedMotions == numMotions) {
		int			i;

		p0						=	motionParameters;
		p1						=	&motionParameters[parameterSize*(numMotions-1)];

		// Interpolate the motion parameters between the shutter open and shutter close
		for (i=0;i<parameterSize;i++) {
			float	s,e,d;

			d		=	(p1[i] - p0[i]) / (keyTimes[numMotions-1] - keyTimes[0]);
			s		=	p0[i] + (currentOptions->shutterOpen - keyTimes[0])*d;
			e		=	p1[i] + (currentOptions->shutterClose - keyTimes[numMotions-1])*d;
			p0[i]	=	s;
			p1[i]	=	e;
		}

		return	2;
	}

	return 0;
}





////////////////////////////////////////////////////////////////////////////////
// Some misc macros used to manage the graphics state
////////////////////////////////////////////////////////////////////////////////
#define	xformBegin()												\
	savedXforms->push(currentXform);								\
	currentXform	=	new CXform(currentXform);					\
	currentXform->attach();


#define	xformEnd()													\
	{																\
		int oflip			=	currentXform->flip;					\
		currentXform->detach();										\
		currentXform		=	savedXforms->pop();					\
		if (oflip != currentXform->flip) {							\
			CAttributes	*attributes	=	getAttributes(TRUE);		\
			attributes->flags	^=	ATTRIBUTES_FLAGS_INSIDE;		\
		}															\
	}

#define	attributeBegin()											\
	savedAttributes->push(currentAttributes);						\
	currentAttributes = new CAttributes(currentAttributes);			\
	currentAttributes->attach();

#define	attributeEnd()												\
	currentAttributes->detach();									\
	currentAttributes			=	savedAttributes->pop();

#define	optionBegin()												\
	savedOptions->push(currentOptions);								\
	currentOptions	=	new COptions(currentOptions);

#define	optionEnd()													\
	delete currentOptions;											\
	currentOptions			=	savedOptions->pop();


#define	getOptions(a)	currentOptions

#define	checkGeometryOrDiscard()									\
	if (attributes->flags & ATTRIBUTES_FLAGS_DISCARD_GEOMETRY)		\
		return;



////////////////////////////////////////////////////////////////////////////////
//	Renderer Interface
////////////////////////////////////////////////////////////////////////////////
void	CRendererContext::RiDeclare(const char *name,const char *declaration) {
	CRenderer::declareVariable(name,declaration);
}
   
// FrameBegin - End stuff
void	CRendererContext::RiFrameBegin(int number) {
	COptions	*options;

	optionBegin();
	attributeBegin();
	xformBegin();

	options			=	getOptions(TRUE);
	options->frame	=	number;

	stats.sequenceNumber++;
}

void	CRendererContext::RiFrameEnd(void) {

	xformEnd();
	attributeEnd();
	optionEnd();
}

// WorldBegin - End stuff
void	CRendererContext::RiWorldBegin(void) {
	optionBegin();
	attributeBegin();
	xformBegin();

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//		The frame initialization		
	assert(currentOptions	!=	NULL);

	// Init the stats
	stats.progress						=	0;

	// Define the world coordinate system
	CRenderer::defineCoordinateSystem(coordinateWorldSystem,currentXform->from,currentXform->to,COORDINATE_WORLD);

	// Start the renderer
	CRenderer::beginFrame(currentOptions,currentAttributes,currentXform);

	// Update the sequence number
	stats.runningSequenceNumber++;
}

void	CRendererContext::RiWorldEnd(void) {
	////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//
	//
	//
	//
	//
	//
	//	This call causes the rendering to happen
	//
	//
	//
	//
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Do the thing baby


	// Render the frame
	CRenderer::renderFrame();

	// Cleanup the frame
	CRenderer::endFrame();
	
	// Restore the graphics state
	xformEnd();
	attributeEnd();
	optionEnd();
}

void	CRendererContext::RiFormat(int xres,int yres,float aspect) {
	COptions	*options;

	if ((xres <= 0) || (yres <= 0)) {
		error(CODE_RANGE,"Resolution too small (%dx%d)\n",xres,yres);
		return;
	}

	options				= getOptions(TRUE);
	options->xres		= xres;
	options->yres		= yres;
	if (aspect > 0) {
		options->pixelAR	= aspect;
	}
	options->flags		|= OPTIONS_FLAGS_CUSTOM_RESOLUTION;
}

void	CRendererContext::RiFrameAspectRatio(float aspect) {
	COptions	*options;

	if (aspect == 0) {
		error(CODE_RANGE,"Invalid frame aspect ratio: %f\n",aspect);
		return;
	}

	options						= getOptions(TRUE);
	options->frameAR			= aspect;
	options->flags				|= OPTIONS_FLAGS_CUSTOM_FRAMEAR;
}

void	CRendererContext::RiScreenWindow(float left,float right,float bot,float top) {
	COptions	*options;

	options						=	getOptions(TRUE);
	options->screenLeft			=	left;
	options->screenRight		=	right;
	options->screenTop			=	top;
	options->screenBottom		=	bot;
	options->flags				|=	OPTIONS_FLAGS_CUSTOM_SCREENWINDOW;
}

void	CRendererContext::RiCropWindow(float xmin,float xmax,float ymin,float ymax) {
	COptions	*options;

	if ((xmin < 0) || (xmin > 1) || (ymin < 0) || (ymax > 1) || (xmax <= xmin) || (ymax <= ymin)) {
		error(CODE_RANGE,"Invalid crop window boundary: (%.3f,%.3f,%.3f,%.3f)\n",xmin,xmax,ymin,ymax);
		return;
	}

	options						=	getOptions(TRUE);
	options->cropLeft			=	xmin;
	options->cropRight			=	xmax;
	options->cropTop			=	ymin;
	options->cropBottom			=	ymax;
}

void	CRendererContext::RiProjectionV(const char *name,int n,const char *tokens[],const void *params[]) {
	COptions	*options;

	options	=	getOptions(TRUE);

	if (strcmp(name,RI_PERSPECTIVE) == 0) {
		int	i;
		options->projection = OPTIONS_PROJECTION_PERSPECTIVE;
		for (i=0;i<n;i++) {
			if (strcmp(tokens[i],RI_FOV) == 0) 
				options->fov	=	((float **) params)[i][0];
			else 
				error(CODE_BADTOKEN,"Invalid perspective projection parameter: %s\n",tokens[i]);
		}
	} else if (strcmp(name,RI_ORTHOGRAPHIC) == 0) {
		int	i;
		options->projection = OPTIONS_PROJECTION_ORTHOGRAPHIC;
		for (i=0;i<n;i++) {
			error(CODE_BADTOKEN,"Invalid orthographic projection parameter: %s\n",tokens[i]);
		}
	} else {
		error(CODE_BADTOKEN,"Invalid projection type: %s\n",name);
	}
}

void	CRendererContext::RiClipping(float hither,float yon) {
	COptions	*options;

	if ((yon < hither)  || (hither < 0) || (yon < 0)) {
		error(CODE_RANGE,"Invalid clipping boundary: (%.3f,%.3f)\n",hither,yon);
		return;
	}

	options				=	getOptions(TRUE);
	options->clipMin	=	max(hither,C_EPSILON);
	options->clipMax	=	yon;
	options->flags		|=	OPTIONS_FLAGS_CUSTOM_CLIPPING;
}

void	CRendererContext::RiClippingPlane(float x,float y,float z,float nx,float ny,float nz) {
	COptions				*options;
	CXform					*xform;
	COptions::CClipPlane	*newPlane;
	vector					p,n,tmp;

	options		=	getOptions(TRUE);
	xform		=	getXform(FALSE);
	newPlane	=	new COptions::CClipPlane;

	initv(tmp,x,y,z);
	mulmp(p,xform->from,tmp);

	initv(tmp,nx,ny,nz);
	mulmn(n,xform->to,tmp);

	movvv(newPlane->normal,n);
	newPlane->d			=	-dotvv(n,p);

	newPlane->next		=	options->clipPlanes;
	options->clipPlanes	=	newPlane;
}

void	CRendererContext::RiDepthOfField(float fstop,float focallength,float focaldistance) {
	COptions	*options;

	if (fstop < 0) {
		error(CODE_RANGE,"Invalid fstop: %f\n",fstop);
		return;
	}

	if (focallength < 0) {
		error(CODE_RANGE,"Invalid focal length: %f\n",focallength);
		return;
	}

	if (focaldistance < 0) {
		error(CODE_RANGE,"Invalid focal distance: %f\n",focaldistance);
		return;
	}

	options					=	getOptions(TRUE);
	options->fstop			=	fstop;
	options->focallength	=	focallength;
	options->focaldistance	=	focaldistance;
}

void	CRendererContext::RiShutter(float smin,float smax) {
	COptions	*options;

	if (smax < smin) {
		error(CODE_RANGE,"Invalid shutter interval: [%f %f]\n",smin,smax);
		return;
	}

	options					=	getOptions(TRUE);
	options->shutterOpen	=	smin + options->shutterOffset;
	options->shutterClose	=	smax + options->shutterOffset;
}


void	CRendererContext::RiPixelVariance(float variation) {
	COptions	*options;

	options					=	getOptions(TRUE);
	options->pixelVariance	=	variation;
}

void	CRendererContext::RiPixelSamples(float xsamples,float ysamples) {
	COptions	*options;

	if ((xsamples < 1) || (ysamples < 1)) {
		error(CODE_RANGE,"Invalid pixel samples: (%f,%f)\n",xsamples,ysamples);
		return;
	}

	options					=	getOptions(TRUE);
	options->pixelXsamples	=	(int) xsamples;
	options->pixelYsamples	=	(int) ysamples;
}

void	CRendererContext::RiPixelFilter(float (*function)(float,float,float,float),float xwidth,float ywidth) {
	COptions	*options;

	if ((xwidth < 0) || (ywidth < 0)) {
		warning(CODE_RANGE,"Invalid filter dimensions: (%f,%f)\n",xwidth,ywidth);
		return;
	}

	if ((xwidth < 1) || (ywidth < 1)) {
		warning(CODE_RANGE,"Filter width less than a pixel: (%f,%f)\n",xwidth,ywidth);
	}

	options							=	getOptions(TRUE);
	options->pixelFilter			=	function;
	options->pixelFilterWidth		=	xwidth;
	options->pixelFilterHeight		=	ywidth;
}

void	CRendererContext::RiExposure(float gain,float gamma) {
	COptions	*options;

	if (gamma <= C_EPSILON) {
		error(CODE_RANGE,"Invalid gamma: %f\n",gamma);
		return;
	}

	if (gain <= C_EPSILON) {
		error(CODE_RANGE,"Invalid gain: %f\n",gain);
		return;
	}

	options			=	getOptions(TRUE);
	options->gamma	=	gamma;
	options->gain	=	gain; 
}

void	CRendererContext::RiImagerV (const char *name,int n,const char *tokens[],const void *params[]) {
	error(CODE_INCAPABLE,"Imager shaders are not currently supported\n");
}

void	CRendererContext::RiQuantize(const char *type,int one,int qmin,int qmax,float ampl) {
	COptions	*options;

	options	=	getOptions(TRUE);

	if (strcmp(type,RI_RGBA) == 0) {
		options->colorQuantizer[0]	=	0;
		options->colorQuantizer[1]	=	(float) one;
		options->colorQuantizer[2]	=	(float) qmin;
		options->colorQuantizer[3]	=	(float) qmax;
		options->colorQuantizer[4]	=	(float) ampl;
	} else if (strcmp(type,RI_Z) == 0) {
		options->depthQuantizer[0]	=	0;
		options->depthQuantizer[1]	=	(float) one;
		options->depthQuantizer[2]	=	(float) qmin;
		options->depthQuantizer[3]	=	(float) qmax;
		options->depthQuantizer[4]	=	(float) ampl;
	} else if (strcmp(type,RI_CUSTOM) == 0) {
		COptions::CDisplay	*cDisplay	=	options->displays;
		if (cDisplay != NULL) {
			cDisplay->quantizer[0]	=	0;
			cDisplay->quantizer[1]	=	(float) one;
			cDisplay->quantizer[2]	=	(float) qmin;
			cDisplay->quantizer[3]	=	(float) qmax;
			cDisplay->quantizer[4]	=	(float) ampl;
		}
	} else {
		error(CODE_BADTOKEN,"Unknown quantizer type: %s\n",type);
	}
}


void	CRendererContext::RiDisplayV(const char *name,const char *type,const char *mode,int n,const char *tokens[],const void *params[]) {
	COptions	*options;

	if (strcmp(mode,RI_RGBZ) == 0) {
		char	tmp[OS_MAX_PATH_LENGTH];
		char	*extensionPos;

		strcpy(tmp,name);
		if ((extensionPos = strchr(tmp,'.')) != NULL) {
			sprintf(extensionPos,"_z");
			strcat(tmp,strchr(name,'.'));
		} else {
			strcat(tmp,"_z");
		}

		RiDisplayV(name,type,RI_RGB,n,tokens,params);
		RiDisplayV(tmp,type,RI_Z,n,tokens,params);
		return;
	} else if (strcmp(mode,RI_RGBAZ) == 0) {
		char	tmp[OS_MAX_PATH_LENGTH];
		char	*extensionPos;

		strcpy(tmp,name);
		if ((extensionPos = strchr(tmp,'.')) != NULL) {
			sprintf(extensionPos,"_z");
			strcat(tmp,strchr(name,'.'));
		} else {
			strcat(tmp,"_z");
		}

		RiDisplayV(name,type,RI_RGBA,n,tokens,params);
		RiDisplayV(tmp,type,RI_Z,n,tokens,params);
		return;
	}

	options	=	getOptions(TRUE);
	if (name[0] == '+') {
		name++;
	} else {
		// Ditch the previously assigned junk
		if (options->displays != NULL) {
			COptions::CDisplay	*cDisplay,*nDisplay;

			for (cDisplay=options->displays;cDisplay!=NULL;) {
				nDisplay	=	cDisplay->next;
				delete cDisplay;
				cDisplay	=	nDisplay;
			}
			options->displays	=	NULL;
		}
	}

	COptions::CDisplay	*cDisplay	=	new COptions::CDisplay;
	cDisplay->outDevice				=	strdup(type);
	cDisplay->outName				=	strdup(name);
	cDisplay->outSamples			=	strdup(mode);
	cDisplay->next					=	options->displays;
	options->displays				=	cDisplay;

	if (n > 0) {
		int i,j;

		cDisplay->numParameters			=	n;
		cDisplay->parameters			=	new COptions::CDisplay::TDisplayParameter[n];

		for (j=0,i=0;i<n;i++) {
			CVariable	*cVar;
			CVariable	tVar;

			cVar						=	CRenderer::retrieveVariable(tokens[i]);
			if (cVar == NULL)
				if (parseVariable(&tVar,NULL,tokens[i]) == TRUE) {
					cVar	=	&tVar;
				}

			if (cVar != NULL) {
				cDisplay->parameters[j].name		=	strdup(cVar->name);
				cDisplay->parameters[j].numItems	=	cVar->numItems;
				switch(cVar->type) {
				case TYPE_FLOAT:
					cDisplay->parameters[j].type	=	FLOAT_PARAMETER;
					cDisplay->parameters[j].data	=	new float[cVar->numItems];
					memcpy(cDisplay->parameters[j].data,params[i],cVar->numItems*sizeof(float));
					break;
				case TYPE_COLOR:
				case TYPE_VECTOR:
				case TYPE_NORMAL:
				case TYPE_POINT:
					cDisplay->parameters[j].type	=	VECTOR_PARAMETER;
					cDisplay->parameters[j].data	=	new float[cVar->numItems*3];
					memcpy(cDisplay->parameters[j].data,params[i],cVar->numItems*sizeof(float)*3);
					break;
				case TYPE_MATRIX:
					cDisplay->parameters[j].type	=	MATRIX_PARAMETER;
					cDisplay->parameters[j].data	=	new float[cVar->numItems*16];
					memcpy(cDisplay->parameters[j].data,params[i],cVar->numItems*sizeof(float)*16);
					break;
				case TYPE_QUAD:
				case TYPE_DOUBLE:
					break;
				case TYPE_STRING:
					cDisplay->parameters[j].type	=	STRING_PARAMETER;
					cDisplay->parameters[j].data	=	strdup(((char **) params[i])[0]);
					break;
				case TYPE_INTEGER:
					{
						int		k;
						float	*src;
						int		*dst;
						cDisplay->parameters[j].type	=	INTEGER_PARAMETER;
						cDisplay->parameters[j].data	=	new int[cVar->numItems];
						dst = (int*)	cDisplay->parameters[j].data;
						src	= (float*)	params[i];
						for(k=0;k<cVar->numItems;k++)	*dst++ = (int) *src++;
					}
					break;
				}
				j++;
			} else {
				error(CODE_BADTOKEN,"Display parameter \"%s\" not defined\n",tokens[i]);
			}
		}
		cDisplay->numParameters	=	j;
	}
}

void	CRendererContext::RiCustomDisplayV(const char *name, RtToken mode, RtDisplayStartFunction startFunction, RtDisplayDataFunction dataFunction, RtDisplayFinishFunction finishFunction, RtInt n, RtToken tokens[], RtPointer params[]) {
	COptions	*options			=	getOptions(TRUE);
	COptions::CDisplay	*cDisplay	=	new COptions::CDisplay;
	cDisplay->outDevice				=	strdup("custom");
	cDisplay->outName				=	strdup(name);
	cDisplay->outSamples			=	strdup(mode);
	cDisplay->next					=	options->displays;
	cDisplay->startFunction			=	startFunction;
	cDisplay->dataFunction			=	dataFunction;
	cDisplay->finishFunction		=	finishFunction;
	options->displays				=	cDisplay;
}

void	CRendererContext::RiDisplayChannelV(const char *channel,int n,const char *tokens[],const void *params[]) {
	int i,j;
	
	CDisplayChannel *nChannel = CRenderer::declareDisplayChannel(channel);
	
	if (nChannel != NULL) {
		for (j=0,i=0;i<n;i++) {
			CVariable	*cVar;
			CVariable	tVar;

			cVar						=	CRenderer::retrieveVariable(tokens[i]);
			if (cVar == NULL)
				if (parseVariable(&tVar,NULL,tokens[i]) == TRUE) {
					cVar	=	&tVar;
				}

			if (cVar != NULL) {
				if (strcmp(cVar->name,"fill") == 0) {
					if ((cVar->numFloats == nChannel->numSamples) &&
						(cVar->type == nChannel->variable->type)) {
						nChannel->fill = new float[nChannel->numSamples];
						memcpy(nChannel->fill,params[i],nChannel->numSamples*sizeof(float));
					} else {
						error(CODE_BADTOKEN,"Invalid number of items for fill\n");
					}
				} else if (strcmp(cVar->name,"matte") == 0) {
					if (cVar->type == TYPE_INTEGER) {
						nChannel->matteMode = (int) ((float*)params[i])[0];
					} else {
						error(CODE_BADTOKEN,"Invalid type for AOV matte mode\n");
					}
				} else if (strcmp(cVar->name,"filter") == 0) {
					if (cVar->type == TYPE_STRING) {
						const char *filt = ((char**)params[i])[0];
						nChannel->filterType = CRenderer::getAOVFilter(filt);
					} else {
						error(CODE_BADTOKEN,"Invalid type for AOV filter mode\n");
					}
				} else if (strcmp(cVar->name,"quantize") == 0) {
					// intentionally empty for compatibility
					warning(CODE_UNIMPLEMENT,"Display channel parameter \"%s\" is not currently supported\n",cVar->name);
				} else if (strcmp(cVar->name,"dither") == 0) {
					// intentionally empty for compatibility
					warning(CODE_UNIMPLEMENT,"Display channel parameter \"%s\" is not currently supported\n",cVar->name);
				} else {
					error(CODE_BADTOKEN,"Invalid display channel parameter: %s\n",tokens[i]);
				}
				j++;
			} else {
				error(CODE_BADTOKEN,"Display channel parameter \"%s\" not defined\n",tokens[i]);
			}
		}
	}
}

void	CRendererContext::RiHiderV(const char *type,int n,const char *tokens[],const void *params[]) {
	COptions	*options;

	options	=	getOptions(TRUE);

	if (options->hider != NULL)	free(options->hider);

	if (strcmp(type,RI_HIDDEN) == 0)	options->hider	=	strdup("stochastic");
	else								options->hider	=	strdup(type);

	if (n > 0) {
		CRendererContext::RiOptionV(RI_HIDER,n,tokens,params);
	}
}

void	CRendererContext::RiColorSamples(int N,float *nRGB,float *RGBn) {
	COptions	*options;

	if (N < 1) {
		error(CODE_RANGE,"Invalid number of color samples: %d\n",N);
		return;
	}

	options					=	getOptions(TRUE);
	options->nColorComps	=	N;
	
	if (options->fromRGB != NULL) 
		delete [] options->fromRGB;
	if (options->toRGB != NULL) 
		delete [] options->toRGB;

	options->fromRGB	=	new float[N*3];
	options->toRGB		=	new float[N*3];

	memcpy(options->fromRGB,RGBn,N*3*sizeof(float));
	memcpy(options->toRGB,nRGB,N*3*sizeof(float));
}

void	CRendererContext::RiRelativeDetail(float relativedetail) {
	COptions	*options;

	if (relativedetail < 0) {
		error(CODE_RANGE,"Invalid relative detail: %4.2f\n",relativedetail);
		return;
	}

	options					=	getOptions(TRUE);
	options->relativeDetail	=	relativedetail;
}


#define	optionCheck(__name,__dest,__min,__max,__type)														\
	} else if (strcmp(tokens[i],__name) == 0) {																\
		__type	*val	=	(__type *) params[i];															\
		if ((val[0] < __min) || (val[0] > __max)) {															\
			error(CODE_RANGE,"Invalid value for \"%s\"\n",__name);											\
		} else {																							\
			__dest	=	val[0];																				\
		}

#define	optionCheckFlag(__name,__dest,__flag)																\
	} else if (strcmp(tokens[i],__name) == 0) {																\
		int	*val	=	(int *) params[i];																	\
		if (val[0] != 0)	__dest	|=	__flag;																\
		else				__dest	&=	~(__flag);															\

#define	optionCheckString(__name,__dest)																	\
	} else if (strcmp(tokens[i],__name) == 0) {																\
		char	*val	=	((char **) params[i])[0];														\
		if (__dest != NULL) free(__dest);																	\
		if (val[0] == '\0') __dest	=	NULL;																\
		else				__dest	=	strdup(val);

#define	optionCheckColor(__name,__dest,__min,__max)															\
	} else if (strcmp(tokens[i],__name) == 0) {																\
		float	*val	=	(float *) params[i];															\
		if ((val[0] < __min) || (val[1] > __max)  || (val[1] < __min) || (val[1] > __max) || (val[1] < __min) || (val[0] > __max)) { \
			error(CODE_RANGE,"Invalid value for \"%s\"\n",__name);											\
		} else {																							\
			movvv(__dest,val);																				\
		}

#define	optionEndCheck																						\
	} else {																								\
		CVariable	var;																					\
		if (parseVariable(&var,NULL,tokens[i]) == TRUE) {													\
			RiOption(name,var.name,params[i],RI_NULL);														\
		} else {																							\
			error(CODE_BADTOKEN,"Unknown %s option: \"%s\"\n",name,tokens[i]);								\
		}																									\
	}


void	CRendererContext::RiOptionV(const char *name,int n,const char *tokens[],const void *params[]) {
	int			i;
	COptions	*options;

	options	=	getOptions(TRUE);

	// Check the searchpath options
	if (strcmp(name,RI_SEARCHPATH) == 0) {
		for (i=0;i<n;i++) {
			char	*paths	=	((char **) params[i])[0];

			if (strcmp(tokens[i],RI_ARCHIVE) == 0) {
				options->archivePath	=	optionsGetSearchPath(paths,options->archivePath);
			} else if (strcmp(tokens[i],RI_PROCEDURAL) == 0) {
				options->proceduralPath	=	optionsGetSearchPath(paths,options->proceduralPath);
			} else if (strcmp(tokens[i],RI_TEXTURE) == 0) {
				options->texturePath	=	optionsGetSearchPath(paths,options->texturePath);
			} else if (strcmp(tokens[i],RI_SHADER) == 0) {
				options->shaderPath		=	optionsGetSearchPath(paths,options->shaderPath);
			} else if (strcmp(tokens[i],RI_DISPLAY) == 0) {
				options->displayPath	=	optionsGetSearchPath(paths,options->displayPath);
			} else if (strcmp(tokens[i],RI_RESOURCE) == 0) {
				options->shaderPath		=	optionsGetSearchPath(paths,options->shaderPath);
				options->texturePath	=	optionsGetSearchPath(paths,options->texturePath);
			optionEndCheck
		}
	// Check the limit options
	} else if (strcmp(name,RI_LIMITS) == 0) {
		for (i=0;i<n;i++) {

			if (strcmp(tokens[i],RI_BUCKETSIZE) == 0) {
				int	*val	=	(int *) params[i];
				if ((val[0] < 0) || (val[1] < 0)) {
					error(CODE_RANGE,"Invalid bucket size: %dx%d\n",val[0],val[1]);
				} else {
					options->bucketWidth	=	val[0];
					options->bucketHeight	=	val[1];
				}
			} else if (strcmp(tokens[i],RI_METABUCKETS) == 0) {
				int	*val	=	(int *) params[i];
				if ((val[0] < 0) || (val[1] < 0)) {
					error(CODE_RANGE,"Invalid meta bucket size: %dx%d\n",val[0],val[1]);
				} else {
					options->netXBuckets	=	val[0];
					options->netYBuckets	=	val[1];
				}
			optionCheckFlag(RI_INHERITATTRIBUTES,options->flags,					OPTIONS_FLAGS_INHERIT_ATTRIBUTES)
			optionCheck(RI_GRIDSIZE,			options->maxGridSize,				128,100000,int)
			optionCheck(RI_EYESPLITS,			options->maxEyeSplits,				1,100000,int)
			optionCheck(RI_TEXTUREMEMORY,		options->maxTextureSize,			0,(2*1024*1024),int)
				options->maxTextureSize	*=	1000;								// Convert into bytes
			optionCheck(RI_BRICKMEMORY,			options->maxBrickSize,				0,100000,int)
				options->maxBrickSize	*=	1000;								// Convert into bytes
			optionCheck(RI_NUMTHREADS,			options->numThreads,				1,32,int)
			optionCheck(RI_THREADSTRIDE,		options->threadStride,				1,32,int)
			optionCheck(RI_GEOCACHEMEMORY,		options->geoCacheMemory,			0,500000,int)
				options->geoCacheMemory	*=	1000;								// Convert into bytes
			optionCheckColor(RI_OTHRESHOLD,		options->opacityThreshold,			0,1)
			optionCheckColor(RI_ZTHRESHOLD,		options->zvisibilityThreshold,		0,1)
				options->geoCacheMemory	*=	1000;								// Convert into bytes
			optionEndCheck
		}
	// Check the hider options
	} else if (strcmp(name,RI_HIDER) == 0) {
		for (i=0;i<n;i++) {
			if (FALSE) {
			optionCheck(RI_JITTER,				options->jitter,					0,1,float)
				if (options->jitter > (float) 0.99)	options->jitter	=	(float) 0.99;
			optionCheckFlag(RI_FALSECOLOR,		options->flags,						OPTIONS_FLAGS_FALSECOLOR_RAYTRACES)
			optionCheckFlag(RI_RADIANCECACHE,	options->flags,						OPTIONS_FLAGS_USE_RADIANCE_CACHE)
			optionCheck(RI_EMIT,				options->numEmitPhotons,			0,100000000,int)
			optionCheckFlag(RI_SAMPLESPECTRUM,	options->flags,						OPTIONS_FLAGS_SAMPLESPECTRUM)
			optionCheckFlag(RI_SAMPLEMOTION,	options->flags,						OPTIONS_FLAGS_SAMPLEMOTION)
			} else if (strcmp(tokens[i],RI_DEPTHFILTER) == 0) {
				char	*val	=	((char **) params[i])[0];
				if		(strcmp(val,"min") == 0)		options->depthFilter	=	DEPTH_MIN;
				else if (strcmp(val,"max") == 0)		options->depthFilter	=	DEPTH_MAX;
				else if (strcmp(val,"average") == 0)	options->depthFilter	=	DEPTH_AVG;
				else if (strcmp(val,"midpoint") == 0)	options->depthFilter	=	DEPTH_MID;
				else error(CODE_BADTOKEN,"Unknown depth filter: \"%s\"\n",val);
			optionEndCheck
		}

	// Check the trace options
	} else if (strcmp(name,RI_TRACE) == 0) {
		for (i=0;i<n;i++) {
			if (FALSE) {
			optionCheck(RI_MAXDEPTH,			options->maxRayDepth,				0,100000,int)
			optionEndCheck
		}

	// Check the io options
	} else if (strcmp(name,RI_STATISTICS) == 0) {
		for (i=0;i<n;i++) {
			if (FALSE) {
			optionCheck(RI_ENDOFFRAME,			options->endofframe,				0,3,int)
			optionCheckString(RI_FILELOG,		options->filelog)
			optionCheckFlag(RI_PROGRESS,		options->flags,						OPTIONS_FLAGS_PROGRESS)
			optionEndCheck
		}
	} else if (strcmp(name,RI_SHUTTER) == 0) {
		for (i=0;i<n;i++) {
			if (FALSE) {
			optionCheck(RI_OFFSET,				options->shutterOffset,				0,C_INFINITY,float);
			optionEndCheck
		}
	} else if (strcmp(name,RI_USER) == 0) {
		CVariable var;
		
		for(i=0;i<n;i++) {
			if (parseVariable(&var,NULL,tokens[i])) {
				// got an inline declaration
				options->userOptions.insert(&var,params[i]);
			} else {
				CVariable *cVar = CRenderer::retrieveVariable(tokens[i]);
				
				if (cVar != NULL) {
					options->userOptions.insert(cVar,params[i]);
				} else {
					error(CODE_BADTOKEN,"User option: \"%s\" is predeclared declared or declared inline\n",name);
				}
			}
		}
	} else {
		error(CODE_BADTOKEN,"Unknown option: \"%s\"\n",name);
	}
}

#undef optionCheck
#undef optionCheckFlag
#undef optionCheckString
#undef optionEnd

void	CRendererContext::RiAttributeBegin (void) {
	attributeBegin();
	xformBegin();
}

void	CRendererContext::RiAttributeEnd (void) {
	xformEnd();
	attributeEnd();
}

void	CRendererContext::RiColor(float * Cs) {
	COptions		*options;
	CAttributes		*attributes;
	vector			color;
	float			*p0,*p1;

	if (CRenderer::netNumServers > 0)	return;

	attributes	=	getAttributes(TRUE);
	options		=	getOptions(TRUE);

	options->convertColor(color,Cs);

	switch(addMotion(color,3,"CRendererContext::RiColor",p0,p1)) {
	case 0:
		break;
	case 1:
		movvv(attributes->surfaceColor,p0);
		if (attributes->next != NULL)	movvv(attributes->next->surfaceColor,p0);
		break;
	case 2:
		movvv(attributes->surfaceColor,p0);
		if (attributes->next == NULL)	attributes->next	=	new CAttributes(attributes);
		movvv(attributes->next->surfaceColor,p1);
		break;
	default:
		break;
	}
}

void	CRendererContext::RiOpacity (float * Cs) {
	COptions		*options;
	CAttributes		*attributes;
	vector			color;
	float			*p0,*p1;

	if (CRenderer::netNumServers > 0)	return;

	attributes	=	getAttributes(TRUE);
	options		=	getOptions(TRUE);

	options->convertColor(color,Cs);

	switch(addMotion(color,3,"CRendererContext::RiOpacity",p0,p1)) {
	case 0:
		break;
	case 1:
		movvv(attributes->surfaceOpacity,p0);
		if (attributes->next != NULL)	movvv(attributes->next->surfaceOpacity,p0);
		break;
	case 2:
		movvv(attributes->surfaceOpacity,p0);
		if (attributes->next == NULL)	attributes->next	=	new CAttributes(attributes);
		movvv(attributes->next->surfaceOpacity,p1);
		break;
	default:
		break;
	}
}

void	CRendererContext::RiTextureCoordinates(float s1,float t1,float s2,float t2,float s3,float t3,float s4,float t4) {
	CAttributes	*attributes;
	float		*p0,*p1;
	float		data[8];

	if (CRenderer::netNumServers > 0)	return;

	attributes	=	getAttributes(TRUE);

	data[0]	=	s1;
	data[1]	=	s2;
	data[2]	=	s3;
	data[3]	=	s4;
	data[4]	=	t1;
	data[5]	=	t2;
	data[6]	=	t3;
	data[7]	=	t4;

	switch(addMotion(data,8,"CRendererContext::RiTextureCoordinates",p0,p1)) {
	case 0:
		break;
	case 1:
		attributes->s[0] = p0[0];
		attributes->s[1] = p0[1];
		attributes->s[2] = p0[2];
		attributes->s[3] = p0[3];
		attributes->t[0] = p0[4];
		attributes->t[1] = p0[5];
		attributes->t[2] = p0[6];
		attributes->t[3] = p0[7];
		attributes->flags |= ATTRIBUTES_FLAGS_CUSTOM_ST;

		if (attributes->next != NULL) {
			attributes->next->s[0] = p0[0];
			attributes->next->s[1] = p0[1];
			attributes->next->s[2] = p0[2];
			attributes->next->s[3] = p0[3];
			attributes->next->t[0] = p0[4];
			attributes->next->t[1] = p0[5];
			attributes->next->t[2] = p0[6];
			attributes->next->t[3] = p0[7];
		}
		
		break;
	case 2:
		attributes->s[0] = p0[0];
		attributes->s[1] = p0[1];
		attributes->s[2] = p0[2];
		attributes->s[3] = p0[3];
		attributes->t[0] = p0[4];
		attributes->t[1] = p0[5];
		attributes->t[2] = p0[6];
		attributes->t[3] = p0[7];
		attributes->flags |= ATTRIBUTES_FLAGS_CUSTOM_ST;

		if (attributes->next == NULL)	attributes->next	=	new CAttributes(attributes);
		
		attributes->next->s[0] = p1[0];
		attributes->next->s[1] = p1[1];
		attributes->next->s[2] = p1[2];
		attributes->next->s[3] = p1[3];
		attributes->next->t[0] = p1[4];
		attributes->next->t[1] = p1[5];
		attributes->next->t[2] = p1[6];
		attributes->next->t[3] = p1[7];
		break;
	default:
		break;
	}
}



void	*CRendererContext::RiLightSourceV(const char *name,int n,const char *tokens[],const void *params[]) {
	CAttributes			*attributes;
	CShaderInstance		*cShader;

	if (CRenderer::netNumServers > 0)	return NULL;

	attributes	=	getAttributes(TRUE);
	cShader		=	getShader(name,SL_LIGHTSOURCE,n,tokens,params);

	if (cShader != NULL) {
		attributes->addLight(cShader);

		return cShader;
	}

	return NULL;
}

void	*CRendererContext::RiAreaLightSourceV(const char *name,int n,const char *tokens[],const void *params[]) {
	CAttributes			*attributes;
	CShaderInstance		*cShader;

	if (CRenderer::netNumServers > 0)	return NULL;

	attributes	=	getAttributes(TRUE);
	cShader		=	getShader(name,SL_LIGHTSOURCE,n,tokens,params);

	if (cShader != NULL) {
		attributes->addLight(cShader);

		return cShader;
	}

	return NULL;
}


void	CRendererContext::RiIlluminate (const void *light,int onoff) {
	CShaderInstance	*cInstance	=	(CShaderInstance *) light;
	CAttributes		*attributes;

	if (CRenderer::netNumServers > 0)				return;
	if (cInstance == NULL)	return;

	attributes	=	getAttributes(TRUE);
	if (onoff)
		attributes->addLight(cInstance);
	else
		attributes->removeLight(cInstance);
}

void	CRendererContext::RiSurfaceV(const char *name,int n,const char *tokens[],const void *params[]) {
	CAttributes		*attributes;
	CShaderInstance	*cShader;

	if (CRenderer::netNumServers > 0)	return;

	attributes	=	getAttributes(TRUE);
	cShader		=	getShader(name,SL_SURFACE,n,tokens,params);

	if (attributes->surface != NULL)
		attributes->surface->detach();

	attributes->surface = cShader;
	attributes->checkParameters();
}

void	CRendererContext::RiAtmosphereV(const char *name,int n,const char *tokens[],const void *params[]) {
	CAttributes		*attributes;
	CShaderInstance	*cShader;

	if (CRenderer::netNumServers > 0)	return;

	attributes	=	getAttributes(TRUE);
	cShader		=	getShader(name,SL_ATMOSPHERE,n,tokens,params);

	if (attributes->atmosphere != NULL)
		attributes->atmosphere->detach();

	attributes->atmosphere = cShader;
	attributes->checkParameters();
}

void	CRendererContext::RiInteriorV(const char *name,int n,const char *tokens[],const void *params[]) {
	CAttributes		*attributes;
	CShaderInstance	*cShader;

	if (CRenderer::netNumServers > 0)	return;

	attributes	=	getAttributes(TRUE);
	cShader		=	getShader(name,SL_ATMOSPHERE,n,tokens,params);

	if (attributes->interior != NULL)
		attributes->interior->detach();

	attributes->interior = cShader;
	attributes->checkParameters();
}

void	CRendererContext::RiExteriorV (const char *name,int n,const char *tokens[],const void *params[]) {
	CAttributes		*attributes;
	CShaderInstance	*cShader;

	if (CRenderer::netNumServers > 0)	return;

	attributes	=	getAttributes(TRUE);
	cShader		=	getShader(name,SL_ATMOSPHERE,n,tokens,params);

	if (attributes->exterior != NULL)
		attributes->exterior->detach();

	attributes->exterior = cShader;
	attributes->checkParameters();
}

void	CRendererContext::RiShadingRate(float size) {
	CAttributes			*attributes;

	if (CRenderer::netNumServers > 0)	return;

	if (size < C_EPSILON) {
		error(CODE_RANGE,"Invalid shading rate: %f\n",size);
		return;
	}

	// Note: we're converting area to distance here!
	// _all_ other sr calculations are by edge length
	attributes				=	getAttributes(TRUE);
	attributes->shadingRate	=	sqrtf(size);
}

void	CRendererContext::RiShadingInterpolation(const char *type) {
}

void	CRendererContext::RiMatte(int onoff) {
	CAttributes	*attributes;

	if (CRenderer::netNumServers > 0)	return;

	attributes	=	getAttributes(TRUE);
	if (onoff) 
		attributes->flags	|=	ATTRIBUTES_FLAGS_MATTE;
	else {
		attributes->flags	&=	~ATTRIBUTES_FLAGS_MATTE;
	}
}


void	CRendererContext::RiBound(float *bound) {
	CAttributes	*attributes;
	CXform		*xform;

	if (CRenderer::netNumServers > 0)	return;

	xform							=	getXform(FALSE);
	attributes						=	getAttributes(TRUE);
	attributes->flags				|=	ATTRIBUTES_FLAGS_CUSTOM_BOUND;
	attributes->bmin[COMP_X]		=	bound[0];
	attributes->bmax[COMP_X]		=	bound[1];
	attributes->bmin[COMP_Y]		=	bound[2];
	attributes->bmax[COMP_Y]		=	bound[3];
	attributes->bmin[COMP_Z]		=	bound[4];
	attributes->bmax[COMP_Z]		=	bound[5];
	xform->transformBound(attributes->bmin,attributes->bmax);
}

void	CRendererContext::RiDetail(float *bound) {
	CAttributes	*attributes;
	CXform		*xform;
	vector		bmin,bmax;
	
	if (CRenderer::netNumServers > 0)	return;

	xform				=	getXform(FALSE);
	attributes			=	getAttributes(TRUE);
	
	bmin[COMP_X]		=	bound[0];
	bmax[COMP_X]		=	bound[1];
	bmin[COMP_Y]		=	bound[2];
	bmax[COMP_Y]		=	bound[3];
	bmin[COMP_Z]		=	bound[4];
	bmax[COMP_Z]		=	bound[5];
	
	// project the bound to screen space and calculate size	
	
	attributes->lodSize = screenArea(xform,bmin,bmax);
}

void	CRendererContext::RiDetailRange(float minvis,float lowtran,float uptran,float maxvis) {
	CAttributes	*attributes;
	
	if (CRenderer::netNumServers > 0)	return;

	attributes				=	getAttributes(TRUE);
	
	attributes->lodRange[0] =	minvis;
	attributes->lodRange[1] =	lowtran;
	attributes->lodRange[2] =	uptran;
	attributes->lodRange[3] =	maxvis;
	
	if ((attributes->lodSize < minvis)	|| (attributes->lodSize > maxvis)) {
		// out of rance, discard all geometry
		attributes->flags		|=	ATTRIBUTES_FLAGS_DISCARD_GEOMETRY;
	} else {
		// Ensure we're no longer discarding geometry
		
		attributes->flags		&=	~(ATTRIBUTES_FLAGS_DISCARD_GEOMETRY | ATTRIBUTES_FLAGS_LOD);
		
		if (attributes->lodSize <= lowtran) {
			// fade in
			attributes->lodImportance = (attributes->lodSize-minvis)/(lowtran-minvis);
			
			attributes->flags		|=	ATTRIBUTES_FLAGS_LOD;
		}
		
		if (attributes->lodSize > uptran) {
			// fade out
			attributes->lodImportance = -(1.0f-(attributes->lodSize-uptran)/(maxvis-uptran));
			attributes->flags		|=	ATTRIBUTES_FLAGS_LOD;
		}
	}
}

void	CRendererContext::RiGeometricApproximation(const char *type,float value) {
	CAttributes	*attributes;

	if (CRenderer::netNumServers > 0)	return;

	attributes	=	getAttributes(TRUE);

	if (strcmp(type,RI_NORMALDEVIATION) == 0) {
		warning(CODE_BADTOKEN,"Deprecated GeometricApproximation \"%s\" will be ignored\n",type);
	} else if (strcmp(type,RI_POINTDEVIATION) == 0) {
		warning(CODE_BADTOKEN,"Deprecated GeometricApproximation \"%s\" will be ignored\n",type);
	} else if (strcmp(type,RI_FLATNESS) == 0) {
		warning(CODE_BADTOKEN,"Deprecated GeometricApproximation \"%s\" will be ignored\n",type);
	} else if (strcmp(type,RI_MOTIONFACTOR) == 0) {
		attributes->motionFactor		=	value;
	} else {
		error(CODE_BADTOKEN,"Unknown geometric approximation: %s\n",type);
	}
}

void	CRendererContext::RiGeometricRepresentation(const char *type) {
	if (CRenderer::netNumServers > 0)	return;

	error(CODE_INCAPABLE,"Arbitrary geometric representation is not currently supported\n");

	return;
}

void	CRendererContext::RiOrientation(const char *orientation) {
	CAttributes	*attributes;

	if (CRenderer::netNumServers > 0)	return;

	attributes	=	getAttributes(TRUE);

	if ((strcmp(orientation,RI_OUTSIDE) == 0) || (strcmp(orientation,RI_LH) == 0)) {
		attributes->flags	&=	~ATTRIBUTES_FLAGS_INSIDE;
	} else if ((strcmp(orientation,RI_INSIDE) == 0) || (strcmp(orientation,RI_RH) == 0)) {
		attributes->flags	|=	ATTRIBUTES_FLAGS_INSIDE;
	} else
		error(CODE_BADTOKEN,"Invalid orientation: %s\n",orientation);
}

void	CRendererContext::RiReverseOrientation(void) {
	CAttributes	*attributes;

	if (CRenderer::netNumServers > 0)	return;

	attributes			=	getAttributes(TRUE);
	attributes->flags	^= ATTRIBUTES_FLAGS_INSIDE;
}

void	CRendererContext::RiSides(int nsides) {
	CAttributes	*attributes;

	if (CRenderer::netNumServers > 0)	return;

	if (!((nsides == 1) || (nsides == 2)))
		error(CODE_RANGE,"Invalid number of sides: %d\n",nsides);
	else {

		attributes			=	getAttributes(TRUE);

		if (nsides == 1)	attributes->flags	&=	~ATTRIBUTES_FLAGS_DOUBLE_SIDED;
		else				attributes->flags	|=	ATTRIBUTES_FLAGS_DOUBLE_SIDED;
	}
}


void	CRendererContext::RiIdentity(void) {
	CXform	*xform;
	float	*p0,*p1;
	int		nflip;

	switch(addMotion(NULL,0,"CRendererContext::RiIdentity",p0,p1)) {
	case 0:
		break;
	case 1:
		xform	=	getXform(TRUE);

		if (CRenderer::world == NULL) {

			xform->identity();

			if (xform->next != NULL)	{
				delete xform->next;
				xform->next	=	NULL;
			}
		} else {

			movmm(xform->from,CRenderer::world->from);
			movmm(xform->to,CRenderer::world->to);

			if (CRenderer::world->next == NULL) {
				if (xform->next != NULL)	{
					delete xform->next;
					xform->next	=	NULL;
				}
			} else {
				if (xform->next == NULL)
					xform->next	=	new CXform(xform);

				movmm(xform->next->from,CRenderer::world->next->from);
				movmm(xform->next->to,CRenderer::world->next->to);
			}
		}

		// Orientation check
		if (determinantm(xform->from) < 0)	nflip	=	1;
		else								nflip	=	0;

		if (nflip != xform->flip) {
			CAttributes	*attributes	=	getAttributes(TRUE);

			attributes->flags	^=	ATTRIBUTES_FLAGS_INSIDE;

			xform->flip	=	nflip;
		}

		break;
	case 2:
		xform	=	getXform(TRUE);

		if (CRenderer::world == NULL) {
			xform->identity();
			if (xform->next != NULL)	{
				delete xform->next;
				xform->next	=	NULL;
			}
		} else {

			movmm(xform->from,CRenderer::world->from);
			movmm(xform->to,CRenderer::world->to);

			if (CRenderer::world->next == NULL) {
				movmm(xform->next->from,CRenderer::world->from);
				movmm(xform->next->to,CRenderer::world->to);

				if (xform->next != NULL)	{
					delete xform->next;
					xform->next	=	NULL;
				}
			} else {
				if (xform->next == NULL)
					xform->next	=	new CXform(xform);
				movmm(xform->next->from,CRenderer::world->next->from);
				movmm(xform->next->to,CRenderer::world->next->to);
			}
		}

		// Orientation check
		if (determinantm(xform->from) < 0)	nflip	=	1;
		else								nflip	=	0;

		if (nflip != xform->flip) {
			CAttributes	*attributes	=	getAttributes(TRUE);

			attributes->flags	^=	ATTRIBUTES_FLAGS_INSIDE;

			xform->flip	=	nflip;
		}
	default:
		break;
	}
}

void	CRendererContext::RiTransform(float transform[][4]) {
	CXform		*xform;
	matrix		to0,to1,from;
	float		*p0,*p1;
	int			nflip;

	// Save the elements
	from[element(0,0)]	=	transform[0][0];
	from[element(1,0)]	=	transform[0][1];
	from[element(2,0)]	=	transform[0][2];
	from[element(3,0)]	=	transform[0][3];
	from[element(0,1)]	=	transform[1][0];
	from[element(1,1)]	=	transform[1][1];
	from[element(2,1)]	=	transform[1][2];
	from[element(3,1)]	=	transform[1][3];
	from[element(0,2)]	=	transform[2][0];
	from[element(1,2)]	=	transform[2][1];
	from[element(2,2)]	=	transform[2][2];
	from[element(3,2)]	=	transform[2][3];
	from[element(0,3)]	=	transform[3][0];
	from[element(1,3)]	=	transform[3][1];
	from[element(2,3)]	=	transform[3][2];
	from[element(3,3)]	=	transform[3][3];

	switch(addMotion(from,16,"CRendererContext::RiTransform",p0,p1)) {
	case 0:
		break;
	case 1:
		if (invertm(to0,p0) == TRUE) {
			error(CODE_MATH,"Singular transformation matrix detected\n");
		} else {
			xform			=	getXform(TRUE);

			if (CRenderer::world == NULL) {
				movmm(xform->from,p0);
				movmm(xform->to,to0);

				if (xform->next != NULL)	{
					delete xform->next;
					xform->next	=	NULL;
				}
			} else {
				CXform	*world	=	CRenderer::world;

				mulmm(xform->from,world->from,p0);
				mulmm(xform->to,to0,world->to);

				if (world->next == NULL) {
					if (xform->next != NULL)	{
						delete xform->next;
						xform->next	=	NULL;
					}
				} else {
					if (xform->next == NULL)	{
						xform->next	=	new CXform(xform);
					}

					mulmm(xform->next->from,world->next->from,p0);
					mulmm(xform->next->to,to0,world->next->to);
				}
			}
		}

		// Orientation check
		if (determinantm(xform->from) < 0)	nflip	=	1;
		else								nflip	=	0;

		if (nflip != xform->flip) {
			CAttributes	*attributes	=	getAttributes(TRUE);

			attributes->flags	^=	ATTRIBUTES_FLAGS_INSIDE;

			xform->flip	=	nflip;
		}
		break;
	case 2:
		if ((invertm(to0,p0) == TRUE) || (invertm(to1,p1) == TRUE)) {
			error(CODE_MATH,"Singular transformation matrix detected\n");
		} else {
			xform			=	getXform(TRUE);

			if (CRenderer::world == NULL) {
				movmm(xform->from,p0);
				movmm(xform->to,to0);
				if (xform->next == NULL)	{
					xform->next	=	new CXform(xform);
				}
				movmm(xform->next->from,p1);
				movmm(xform->next->to,to1);
			} else {
				CXform	*world	=	CRenderer::world;

				mulmm(xform->from,CRenderer::world->from,p0);
				mulmm(xform->to,to0,CRenderer::world->to);
				if (xform->next == NULL)	{
					xform->next	=	new CXform(xform);
				}

				if (world->next == NULL) {
					mulmm(xform->next->from,world->from,p1);
					mulmm(xform->next->to,to1,world->to);
				} else {
					mulmm(xform->next->from,world->next->from,p1);
					mulmm(xform->next->to,to1,world->next->to);
				}
			}
		}

		// Orientation check
		if (determinantm(xform->from) < 0)	nflip	=	1;
		else								nflip	=	0;

		if (nflip != xform->flip) {
			CAttributes	*attributes	=	getAttributes(TRUE);

			attributes->flags	^=	ATTRIBUTES_FLAGS_INSIDE;

			xform->flip	=	nflip;
		}
		break;
	default:
		break;
	}
}

void	CRendererContext::RiConcatTransform(float transform[][4]) {
	CXform	*xform;
	matrix	tmp;
	matrix	to0,to1,from;
	float	*p0,*p1;
	int		nflip;

	// Save the elements
	from[element(0,0)]	=	transform[0][0];
	from[element(1,0)]	=	transform[0][1];
	from[element(2,0)]	=	transform[0][2];
	from[element(3,0)]	=	transform[0][3];
	from[element(0,1)]	=	transform[1][0];
	from[element(1,1)]	=	transform[1][1];
	from[element(2,1)]	=	transform[1][2];
	from[element(3,1)]	=	transform[1][3];
	from[element(0,2)]	=	transform[2][0];
	from[element(1,2)]	=	transform[2][1];
	from[element(2,2)]	=	transform[2][2];
	from[element(3,2)]	=	transform[2][3];
	from[element(0,3)]	=	transform[3][0];
	from[element(1,3)]	=	transform[3][1];
	from[element(2,3)]	=	transform[3][2];
	from[element(3,3)]	=	transform[3][3];

	switch(addMotion(from,16,"CRendererContext::RiConcatTransform",p0,p1)) {
	case 0:
		break;
	case 1:
		if (invertm(to0,p0) == TRUE) {
			error(CODE_MATH,"Singular transformation matrix detected\n");
		} else {
			xform	=	getXform(TRUE);
			mulmm(tmp,xform->from,p0);
			movmm(xform->from,tmp);

			mulmm(tmp,to0,xform->to);
			movmm(xform->to,tmp);

			if (xform->next != NULL)	{
				mulmm(tmp,xform->next->from,p0);
				movmm(xform->next->from,tmp);

				mulmm(tmp,to0,xform->next->to);
				movmm(xform->next->to,tmp);
			}
		}

		// Orientation check
		if (determinantm(xform->from) < 0)	nflip	=	1;
		else								nflip	=	0;

		if (nflip != xform->flip) {
			CAttributes	*attributes	=	getAttributes(TRUE);

			attributes->flags	^=	ATTRIBUTES_FLAGS_INSIDE;

			xform->flip	=	nflip;
		}
		break;
	case 2:
		if ((invertm(to0,p0) == TRUE) || (invertm(to1,p1) == TRUE)) {
			error(CODE_MATH,"Singular transformation matrix detected\n");
		} else {
			xform	=	getXform(TRUE);

			if (xform->next == NULL)	{
				xform->next	=	new CXform(xform);
			}


			mulmm(tmp,xform->from,p0);
			movmm(xform->from,tmp);

			mulmm(tmp,to0,xform->to);
			movmm(xform->to,tmp);

			mulmm(tmp,xform->next->from,p1);
			movmm(xform->next->from,tmp);

			mulmm(tmp,to1,xform->next->to);
			movmm(xform->next->to,tmp);
		}

		// Orientation check
		if (determinantm(xform->from) < 0)	nflip	=	1;
		else								nflip	=	0;

		if (nflip != xform->flip) {
			CAttributes	*attributes	=	getAttributes(TRUE);

			attributes->flags	^=	ATTRIBUTES_FLAGS_INSIDE;

			xform->flip	=	nflip;
		}
		break;
	default:
		break;
	}
}

void	CRendererContext::RiPerspective(float fov) {
	CXform	*xform;
	matrix	to,from,tmp;
	double	d;
	float	p;
	float	*p0,*p1;

	p	=	fov;

	switch(addMotion(&p,1,"CRendererContext::RiPerspective",p0,p1)) {
	case 0:
		break;
	case 1:
		xform				=	getXform(TRUE);

		d					=	1 / tan(p0[0]*C_PI/(double) 360);

		from[element(0,0)]	=	(float) d;
		from[element(0,1)]	=	(float) 0;
		from[element(0,2)]	=	(float) 0;
		from[element(0,3)]	=	(float) 0;

		from[element(1,0)]	=	(float) 0;
		from[element(1,1)]	=	(float) d;
		from[element(1,2)]	=	(float) 0;
		from[element(1,3)]	=	(float) 0;

		from[element(2,0)]	=	(float) 0;
		from[element(2,1)]	=	(float) 0;
		from[element(2,2)]	=	(float) 1;
		from[element(2,3)]	=	(float) 0;

		from[element(3,0)]	=	(float) 0;
		from[element(3,1)]	=	(float) 0;
		from[element(3,2)]	=	(float) 1;
		from[element(3,3)]	=	(float) 0;

		identitym(to);
		
		mulmm(tmp,xform->from,from);
		movmm(xform->from,from);

		mulmm(tmp,to,xform->to);
		movmm(xform->to,tmp);

		if (xform->next != NULL)	{
			mulmm(tmp,xform->next->from,from);
			movmm(xform->next->from,from);

			mulmm(tmp,to,xform->next->to);
			movmm(xform->next->to,tmp);
		}

		break;
	case 2:
		xform				=	getXform(TRUE);
		if (xform->next == NULL)	xform->next	=	new CXform(xform);

		d					=	1 / tan(p0[0]*C_PI/(double) 360);

		from[element(0,0)]	=	(float) d;
		from[element(0,1)]	=	(float) 0;
		from[element(0,2)]	=	(float) 0;
		from[element(0,3)]	=	(float) 0;
		from[element(1,0)]	=	(float) 0;
		from[element(1,1)]	=	(float) d;
		from[element(1,2)]	=	(float) 0;
		from[element(1,3)]	=	(float) 0;
		from[element(2,0)]	=	(float) 0;
		from[element(2,1)]	=	(float) 0;
		from[element(2,2)]	=	(float) 1;
		from[element(2,3)]	=	(float) 0;
		from[element(3,0)]	=	(float) 0;
		from[element(3,1)]	=	(float) 0;
		from[element(3,2)]	=	(float) 1;
		from[element(3,3)]	=	(float) 0;

		invertm(to,from);

		mulmm(tmp,xform->from,from);
		movmm(xform->from,from);

		mulmm(tmp,to,xform->to);
		movmm(xform->to,tmp);

		d					=	1 / tan(p1[0]*C_PI/(double) 360);

		from[element(0,0)]	=	(float) d;
		from[element(0,1)]	=	(float) 0;
		from[element(0,2)]	=	(float) 0;
		from[element(0,3)]	=	(float) 0;
		from[element(1,0)]	=	(float) 0;
		from[element(1,1)]	=	(float) d;
		from[element(1,2)]	=	(float) 0;
		from[element(1,3)]	=	(float) 0;
		from[element(2,0)]	=	(float) 0;
		from[element(2,1)]	=	(float) 0;
		from[element(2,2)]	=	(float) 1;
		from[element(2,3)]	=	(float) 0;
		from[element(3,0)]	=	(float) 0;
		from[element(3,1)]	=	(float) 0;
		from[element(3,2)]	=	(float) 1;
		from[element(3,3)]	=	(float) 0;

		invertm(to,from);

		mulmm(tmp,xform->next->from,from);
		movmm(xform->next->from,from);

		mulmm(tmp,to,xform->next->to);
		movmm(xform->next->to,tmp);
		break;
	default:
		break;
	}
}

void	CRendererContext::RiTranslate(float dx,float dy,float dz) {
	CXform	*xform;
	vector	par;
	float	*p0,*p1;

	par[COMP_X]	=	dx;
	par[COMP_Y]	=	dy;
	par[COMP_Z]	=	dz;

	switch(addMotion(par,3,"CRendererContext::RiTranslate",p0,p1)) {
	case 0:
		break;
	case 1:
		xform	=	getXform(TRUE);
		xform->translate(p0[COMP_X],p0[COMP_Y],p0[COMP_Z]);
		if (xform->next != NULL)	xform->next->translate(p0[COMP_X],p0[COMP_Y],p0[COMP_Z]);
		break;
	case 2:
		xform	=	getXform(TRUE);
		if (xform->next == NULL) xform->next	=	new CXform(xform);

		xform->translate(p0[COMP_X],p0[COMP_Y],p0[COMP_Z]);
		xform->next->translate(p1[COMP_X],p1[COMP_Y],p1[COMP_Z]);
		break;
	default:
		break;
	}

	// Note that there's no orientation check as translation can not change the determinant
}

void	CRendererContext::RiRotate(float angle,float dx,float dy,float dz) {
	CXform	*xform;
	float	tmp[4];
	float	*p0,*p1;

	tmp[0]	=	dx;
	tmp[1]	=	dy;
	tmp[2]	=	dz;
	tmp[3]	=	angle;

	switch(addMotion(tmp,4,"CRendererContext::RiRotate",p0,p1)) {
	case 0:
		break;
	case 1:
		xform	=	getXform(TRUE);
		xform->rotate(p0[3],p0[0],p0[1],p0[2]);
		if (xform->next != NULL)	xform->next->rotate(p0[3],p0[0],p0[1],p0[2]);
		break;
	case 2:
		xform	=	getXform(TRUE);
		if (xform->next == NULL)	xform->next	=	new CXform(xform);
		xform->rotate(p0[3],p0[0],p0[1],p0[2]);
		xform->next->rotate(p1[3],p1[0],p1[1],p1[2]);
		break;
	default:
		break;
	}

	// Rotation does not change determinant's sign
}

void	CRendererContext::RiScale(float dx,float dy,float dz) {
	CXform		*xform;
	vector		tmp;
	float		*p0,*p1;
	int			nflip;

	if ((dx == 0) || (dy == 0) || (dz == 0)) {
		error(CODE_MATH,"The matrix is uninvertible (scale(%f,%f,%f))\n",dx,dy,dz);
		return;
	}

	tmp[COMP_X]	=	dx;
	tmp[COMP_Y]	=	dy;
	tmp[COMP_Z]	=	dz;

	switch(addMotion(tmp,3,"CRendererContext::RiScale",p0,p1)) {
	case 0:
		break;
	case 1:
		if ((p0[0] == 0) || (p0[1] == 0) || (p0[2] == 0)) {
			error(CODE_MATH,"The matrix is uninvertible (scale(%f,%f,%f))\n",p0[0],p0[1],p0[2]);
			return;
		}

		xform	=	getXform(TRUE);
		xform->scale(p0[0],p0[1],p0[2]);
		if (xform->next != NULL)	xform->next->scale(p0[0],p0[1],p0[2]);

		// Orientation check
		if (determinantm(xform->from) < 0)	nflip	=	1;
		else								nflip	=	0;

		if (nflip != xform->flip) {
			CAttributes	*attributes	=	getAttributes(TRUE);

			attributes->flags	^=	ATTRIBUTES_FLAGS_INSIDE;

			xform->flip	=	nflip;
		}
		break;
	case 2:
		if ((p0[0] == 0) || (p0[1] == 0) || (p0[2] == 0)) {
			error(CODE_MATH,"The matrix is uninvertible (scale(%f,%f,%f))\n",p0[0],p0[1],p0[2]);
			return;
		}

		if ((p0[0] == 0) || (p0[1] == 0) || (p0[2] == 0)) {
			error(CODE_MATH,"The matrix is uninvertible (scale(%f,%f,%f))\n",p1[0],p1[1],p1[2]);
			return;
		}

		xform	=	getXform(TRUE);
		if (xform->next == NULL)	xform->next	=	new CXform(xform);
		xform->scale(p0[0],p0[1],p0[2]);
		xform->next->scale(p1[0],p1[1],p1[2]);

		// Orientation check
		if (determinantm(xform->from) < 0)	nflip	=	1;
		else								nflip	=	0;

		if (nflip != xform->flip) {
			CAttributes	*attributes	=	getAttributes(TRUE);

			attributes->flags	^=	ATTRIBUTES_FLAGS_INSIDE;

			xform->flip	=	nflip;
		}
		break;
	default:
		break;
	}
}

void	CRendererContext::RiSkew(float angle,float dx1,float dy1,float dz1,float dx2,float dy2,float dz2) {
	CXform	*xform;
	float	tmp[7];
	float	*p0,*p1;
	int		nflip;

	tmp[0]	=	angle;
	tmp[1]	=	dx1;
	tmp[2]	=	dy1;
	tmp[3]	=	dz1;
	tmp[4]	=	dx2;
	tmp[5]	=	dy2;
	tmp[6]	=	dz2;

	switch(addMotion(tmp,7,"CRendererContext::RiSkew",p0,p1)) {
	case 0:
		break;
	case 1:
		xform	=	getXform(TRUE);
		xform->skew(p0[0],p0[1],p0[2],p0[3],p0[4],p0[5],p0[6]);
		if (xform->next != NULL)	xform->next->skew(p0[0],p0[1],p0[2],p0[3],p0[4],p0[5],p0[6]);

		// Orientation check
		if (determinantm(xform->from) < 0)	nflip	=	1;
		else								nflip	=	0;

		if (nflip != xform->flip) {
			CAttributes	*attributes	=	getAttributes(TRUE);

			attributes->flags	^=	ATTRIBUTES_FLAGS_INSIDE;

			xform->flip	=	nflip;
		}
		break;
	case 2:
		xform	=	getXform(TRUE);
		if (xform->next == NULL)	xform->next	=	new CXform(xform);

		xform->skew(p0[0],p0[1],p0[2],p0[3],p0[4],p0[5],p0[6]);
		xform->next->skew(p1[0],p1[1],p1[2],p1[3],p1[4],p1[5],p1[6]);

		// Orientation check
		if (determinantm(xform->from) < 0)	nflip	=	1;
		else								nflip	=	0;

		if (nflip != xform->flip) {
			CAttributes	*attributes	=	getAttributes(TRUE);

			attributes->flags	^=	ATTRIBUTES_FLAGS_INSIDE;

			xform->flip	=	nflip;
		}
		break;
	default:
		break;
	}
}

void	CRendererContext::RiDeformationV(const char *name,int n,const char *tokens[],const void *params[]) {
	if (CRenderer::netNumServers > 0)	return;

	error(CODE_INCAPABLE,"Arbitrary deformations are not currently supported\n");

	return;
}


void	CRendererContext::RiDisplacementV(const char *name,int n,const char *tokens[],const void *params[]) {
	CAttributes		*attributes;
	CShaderInstance	*cShader;

	if (CRenderer::netNumServers > 0)	return;

	attributes	=	getAttributes(TRUE);
	cShader		=	getShader(name,SL_DISPLACEMENT,n,tokens,params);

	if (attributes->displacement != NULL)
		attributes->displacement->detach();

	attributes->displacement = cShader;
	attributes->checkParameters();
}

void	CRendererContext::RiCoordinateSystem(const char *space) {
	CXform	*xform;

	xform	=	getXform(FALSE);

	CRenderer::defineCoordinateSystem(space,xform->from,xform->to);
}

void	CRendererContext::RiCoordSysTransform(const char *space) {
	const float			*from,*to;
	ECoordinateSystem	cSystem;
	CXform				*xform;

	xform	=	getXform(TRUE);

	if (xform != NULL) {
		CRenderer::findCoordinateSystem(space,from,to,cSystem);

		movmm(xform->from,from);
		movmm(xform->to,to);
	}
}

RtPoint *	CRendererContext::RiTransformPoints(const char *fromspace,const char *tospace,int npoints,RtPoint *points) {
	const float			*from1,*to1;
	const float			*from2,*to2;
	ECoordinateSystem	cSystem1,cSystem2;

	if (!CRenderer::findCoordinateSystem(fromspace,from1,to1,cSystem1))
		return NULL;
	if (!CRenderer::findCoordinateSystem(tospace,from2,to2,cSystem2))
		return NULL;

	matrix tmp;
	mulmm(tmp, to2, from1);
	for (int i=0;i<16;i++)
		if (!isfinite(tmp[i]))
			return NULL;

	for (int i=0;i<npoints;i++)
		mulmp(points[i], tmp, points[i]);
	
	return points;
}

void	CRendererContext::RiTransformBegin (void) {
	xformBegin();
}

void	CRendererContext::RiTransformEnd (void) {
	xformEnd();
}

#define	attributeCheck(__name,__dest,__min,__max,__type)													\
	} else if (strcmp(tokens[i],__name) == 0) {																\
		const __type	*val	=	(const __type *) params[i];															\
		if ((val[0] < __min) || (val[0] > __max)) {															\
			error(CODE_RANGE,"Invalid value for \"%s\"\n",__name);											\
		} else {																							\
			__dest	=	val[0];																				\
		}

#define	attributeCheckFlag(__name,__dest,__flag)															\
	} else if (strcmp(tokens[i],__name) == 0) {																\
		const int	*val	=	(const int *) params[i];																	\
		if (val[0] != 0)	__dest	|=	__flag;																\
		else				__dest	&=	~(__flag);															\

#define	attributeCheckInvertFlag(__name,__dest,__flag)														\
	} else if (strcmp(tokens[i],__name) == 0) {																\
		const int	*val	=	(const int *) params[i];																	\
		if (val[0] != 0)	__dest	&=	~(__flag);															\
		else				__dest	|=	__flag;																\

#define	attributeCheckString(__name,__dest)																	\
	} else if (strcmp(tokens[i],__name) == 0) {																\
		const char	*val	=	((const char **) params[i])[0];														\
		if (__dest != NULL) free(__dest);																	\
		if (val[0] == '\0') __dest	=	NULL;																\
		else				__dest	=	strdup(val);

#define	attributeEndCheck																					\
	} else {																								\
		CVariable	var;																					\
		if (parseVariable(&var,NULL,tokens[i]) == TRUE) {													\
			RiAttribute(name,var.name,params[i],RI_NULL);													\
		} else {																							\
			error(CODE_BADTOKEN,"Unknown %s attribute: \"%s\"\n",name,tokens[i]);							\
		}																									\
	}



void	CRendererContext::RiAttributeV(const char *name,int n,const char *tokens[],const void *params[]) {
	int			i,dummy;
	CAttributes	*attributes;

	if (CRenderer::netNumServers > 0)	return;

	attributes	=	getAttributes(TRUE);

	if (attributes != NULL) {
		if (strcmp(name,RI_DICE) == 0) {
			for (i=0;i<n;i++) {
				if (strcmp(tokens[i],RI_NUMPROBES) == 0) {
					int		*val	=	(int *) params[i];

					if ((val[0] < 0) || (val[1] < 0)) error(CODE_RANGE,"Invalid number of probes: %dx%d\n",val[0],val[1]);
					else {
						attributes->numUProbes	=	val[0];
						attributes->numVProbes	=	val[1];
					}
				attributeCheck(RI_MINSUBDIVISION,			dummy,				1, 100000,int)
					warning(CODE_BADTOKEN,"Deprecated attribute \"%s\" will be ignored\n",tokens[i]);
				attributeCheck(RI_MAXSUBDIVISION,			dummy,				1, 100000,int)
					warning(CODE_BADTOKEN,"Deprecated attribute \"%s\" will be ignored\n",tokens[i]);
				attributeCheck(RI_MINSPLITS,				attributes->minSplits,					0, 100000,int)
				attributeCheck(RI_BOUNDEXPAND,				attributes->rasterExpand,				-C_INFINITY, C_INFINITY,float)				
				attributeCheckFlag(RI_BINARY,				attributes->flags,						ATTRIBUTES_FLAGS_BINARY_DICE)
				attributeCheckInvertFlag(RI_RASTERORIENT,	attributes->flags,						ATTRIBUTES_FLAGS_NONRASTERORIENT_DICE)
				attributeEndCheck
			}
		} else if (strcmp(name,RI_DISPLACEMENTBOUND) == 0) {
			for (i=0;i<n;i++) {
				if (strcmp(tokens[i],RI_SPHERE) == 0) {
					float	*val	=	(float *) params[i];

					attributes->maxDisplacement	=	val[0];
				} else if (strcmp(tokens[i],RI_COORDINATESYSYTEM) == 0) {
					char	*val	=	((char **) params[i])[0];

					if (attributes->maxDisplacementSpace != NULL)	free(attributes->maxDisplacementSpace);

					attributes->maxDisplacementSpace	=	strdup(val);
				attributeEndCheck
			}

		} else if (strcmp(name,RI_TRACE) == 0) {
			for (i=0;i<n;i++) {
				if (FALSE) {
				attributeCheckFlag(RI_DISPLACEMENTS,	attributes->flags,							ATTRIBUTES_FLAGS_DISPLACEMENTS)
				attributeCheck(RI_BIAS,					attributes->bias,							-C_INFINITY,C_INFINITY,float)
				attributeCheck(RI_MAXDIFFUSEDEPTH,		attributes->maxDiffuseDepth,				0,C_INFINITY,int)
				attributeCheck(RI_MAXSPECULARDEPTH,		attributes->maxSpecularDepth,				0,C_INFINITY,int)
				attributeCheckFlag(RI_SAMPLEMOTION,		attributes->flags,							ATTRIBUTES_FLAGS_SAMPLEMOTION)
				attributeEndCheck
			}
		// Check the irradiance cache options
		} else if (strcmp(name,RI_IRRADIANCE) == 0) {
			for (i=0;i<n;i++) {
				if (FALSE) {
				attributeCheckString(RI_HANDLE,			attributes->irradianceHandle)
				attributeCheckString(RI_FILEMODE,		attributes->irradianceHandleMode)
				attributeCheck(RI_MAXERROR,				attributes->irradianceMaxError,				0,C_INFINITY,float)
				attributeCheck(RI_MAXPIXELDIST,			attributes->irradianceMaxPixelDistance,		0,C_INFINITY,float)
				attributeEndCheck
			}
		} else if (strcmp(name,RI_PHOTON) == 0) {
			for (i=0;i<n;i++) {
				if (strcmp(tokens[i],RI_GLOBALMAP) == 0) {
					if (attributes->globalMapName != NULL) free(attributes->globalMapName);
					attributes->globalMapName	=	strdup(((char **) params[i])[0]);
				} else if (strcmp(tokens[i],RI_CAUSTICMAP) == 0) {
					if (attributes->causticMapName != NULL) free(attributes->causticMapName);
					attributes->causticMapName	=	strdup(((char **) params[i])[0]);
				} else if (strcmp(tokens[i],RI_SHADINGMODEL) == 0) {
					attributes->shadingModel	=	CAttributes::findShadingModel(((const char **) params[i])[0]);
				} else if (strcmp(tokens[i],RI_IOR) == 0) {
					float	*val	=	(float *) params[i];
					if (val[0] < 0) {
						error(CODE_RANGE,"Invalid value for \"%s\"\n",RI_IOR);
					} else {
						attributes->photonIor[0] = attributes->photonIor[1]	= val[0];
					}
				}  else if (strcmp(tokens[i],RI_IORRANGE) == 0) {
					float	*val	=	(float *) params[i];
					if ((val[0] < 0) || (val[1] < 0)) {
						error(CODE_RANGE,"Invalid value for \"%s\"\n",RI_IORRANGE);
					} else {
						attributes->photonIor[0] 	=	val[0];
						attributes->photonIor[1]	=	val[1];
					}
				attributeCheck(RI_ESTIMATOR,			attributes->photonEstimator,					1,C_INFINITY,int)
				attributeCheckFlag(RI_ILLUMINATEFRONT,	attributes->flags,								ATTRIBUTES_FLAGS_ILLUMINATE_FRONT_ONLY)
				attributeEndCheck
			}
		} else if (strcmp(name,RI_VISIBILITY) == 0) {
			for (i=0;i<n;i++) {
				if (FALSE) {
				attributeCheckFlag(RI_TRANSMISSION,		attributes->flags,	ATTRIBUTES_FLAGS_TRANSMISSION_VISIBLE)
				attributeCheckFlag(RI_CAMERA,			attributes->flags,	ATTRIBUTES_FLAGS_PRIMARY_VISIBLE)
				attributeCheckFlag(RI_DIFFUSE,			attributes->flags,	ATTRIBUTES_FLAGS_DIFFUSE_VISIBLE)
				attributeCheckFlag(RI_SPECULAR,			attributes->flags,	ATTRIBUTES_FLAGS_SPECULAR_VISIBLE)
				attributeCheckFlag(RI_PHOTON,			attributes->flags,	ATTRIBUTES_FLAGS_PHOTON_VISIBLE)
				attributeEndCheck
			}
		} else if (strcmp(name,RI_SHADE) == 0) {
			for (i=0;i<n;i++) {
				if (strcmp(tokens[i],RI_TRANSMISSIONHITMODE) == 0)	{
					attributes->transmissionHitMode = CAttributes::findHitMode(((const char **) params[i])[0]);
				} else if (strcmp(tokens[i],RI_DIFFUSEHITMODE) == 0) {
					attributes->diffuseHitMode = CAttributes::findHitMode(((const char **) params[i])[0]);
					if (attributes->diffuseHitMode != 'p') warning(CODE_UNIMPLEMENT,"shading of diffuse rays not currently supported\n");
				} else if (strcmp(tokens[i],RI_SPECULARHITMODE) == 0) {
					attributes->specularHitMode = CAttributes::findHitMode(((const char **) params[i])[0]);
				} else if (strcmp(tokens[i],RI_CAMERAHITMODE) == 0) {
					attributes->cameraHitMode = CAttributes::findHitMode(((const char **) params[i])[0]);
				attributeEndCheck
			}
		} else if (strcmp(name,RI_IDENTIFIER) == 0) {
			for (i=0;i<n;i++) {
				if (FALSE) {
				attributeCheckString(RI_NAME,			attributes->name)
				attributeEndCheck
			}
		 } else if (strcmp(name,RI_CULL) == 0) {
			for (i=0;i<n;i++) {
				if (FALSE) {
				attributeCheckInvertFlag(RI_HIDDEN,		attributes->flags,	ATTRIBUTES_FLAGS_SHADE_HIDDEN)
				attributeCheckInvertFlag(RI_BACKFACING,	attributes->flags,	ATTRIBUTES_FLAGS_SHADE_BACKFACE)
				attributeEndCheck
			}
		} else if (strcmp(name,RI_USER) == 0) {
			CVariable var;
			
			for(i=0;i<n;i++) {
				if (parseVariable(&var,NULL,tokens[i])) {
					// got an inline declaration
					attributes->userAttributes.insert(&var,params[i]);
				} else {
					CVariable *cVar = CRenderer::retrieveVariable(tokens[i]);
					
					if (cVar != NULL) {
						attributes->userAttributes.insert(cVar,params[i]);
					} else {
						error(CODE_BADTOKEN,"User attribute: \"%s\" is predeclared declared or declared inline\n",name);
					}
				}
			}
		} else {
			error(CODE_BADTOKEN,"Unknown attribute: \"%s\"\n",name);
		}
	}
}

#undef	attributeCheck
#undef	attributeCheckFlag
#undef	attributeCheckString
#undef	attributeEndCheck

void	CRendererContext::RiPolygonV(int nvertices,int n,const char *tokens[],const void *params[]) {
	CXform			*xform;
	CAttributes		*attributes;
	float			*p0,*p1;
	CPl				*pl;
	
	if (CRenderer::netNumServers > 0)	return;

	xform			=	getXform(FALSE);
	attributes		=	getAttributes(FALSE);
	
	checkGeometryOrDiscard();
	
	pl				=	parseParameterList(1,nvertices,0,nvertices,n,tokens,params,RI_P,PL_VARYING_TO_VERTEX,attributes);
	if (pl == NULL)	return;

	// We have the core
	switch(addMotion(pl->data0,pl->dataSize,"RiPolygon",p0,p1)) {
	case 0:
		delete pl;
		return;
		break;
	case 1:
		// Restore the parameters
		if (pl->data0 != p0)
			memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);			
		break;
	case 2:
		// Restore the parameters
		memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);
		pl->append(p1);
		break;
	}

	int	*vertices		=	(int *) alloca(nvertices*sizeof(int));
	int	i;

	for (i=0;i<nvertices;i++) {
		vertices[i]	=	i;
	}

	i	=	1;

	addObject(new CPolygonMesh(attributes,xform,pl,1,&i,&nvertices,vertices));
}


void	CRendererContext::RiGeneralPolygonV(int nloops,int *nverts,int n,const char *tokens[],const void *params[]) {
	CXform			*xform;
	CAttributes		*attributes;
	float			*p0,*p1;
	CPl				*pl;
	int				i,nvertices;

	if (CRenderer::netNumServers > 0)	return;

	xform			=	getXform(FALSE);
	attributes		=	getAttributes(FALSE);
	
	checkGeometryOrDiscard();

	nvertices=0;
	for (i=0;i<nloops;i++) {
		nvertices	+=	nverts[i];
	}
	
	pl				=	parseParameterList(1,nvertices,0,nvertices,n,tokens,params,RI_P,PL_VARYING_TO_VERTEX,attributes);
	if (pl == NULL)	return;

	// We have the core
	switch(addMotion(pl->data0,pl->dataSize,"RiGeneralPolygon",p0,p1)) {
	case 0:
		delete pl;
		return;
		break;
	case 1:
		if (pl->data0 != p0)
			memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);
		break;
	case 2:
		memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);
		pl->append(p1);
		break;
	}

	// Get the core and allocate the polygon
	int	*vertices		=	(int *) alloca(nvertices*sizeof(int));

	for (i=0;i<nvertices;i++) {
		vertices[i]	=	i;
	}


	addObject(new CPolygonMesh(attributes,xform,pl,1,&nloops,nverts,vertices));
}

void	CRendererContext::RiPointsPolygonsV(int npolys,int *nverts,int *verts,int n,const char *tokens[],const void *params[]) {
	CXform			*xform;
	CAttributes		*attributes;
	float			*p0,*p1;
	CPl				*pl;
	int				i,nvertices,mvertex;

	if (CRenderer::netNumServers > 0)	return;

	xform			=	getXform(FALSE);
	attributes		=	getAttributes(FALSE);
	
	checkGeometryOrDiscard();

	nvertices	=	0;
	mvertex		=	0;

	for (i=0;i<npolys;i++) {
		nvertices	+=	nverts[i];
	}

	for (i=0;i<nvertices;i++) {
		mvertex		=	max(mvertex,verts[i]);
	}

	pl				=	parseParameterList(npolys,mvertex+1,0,nvertices,n,tokens,params,RI_P,PL_VARYING_TO_VERTEX,attributes);
	if (pl == NULL)	return;

	// We have the core
	switch(addMotion(pl->data0,pl->dataSize,"RiPointsPolygons",p0,p1)) {
	case 0:
		delete pl;
		return;
		break;
	case 1:
		// Restore the parameters
		if (pl->data0 != p0)
			memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);

		break;
	case 2:
		// Restore the parameters
		memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);
		pl->append(p1);

		break;
	default:
		break;
	}	

	// Get the core and allocate the polygon
	memBegin(CRenderer::globalMemory);

	int	*nloops		=	(int *) ralloc(npolys*sizeof(int),CRenderer::globalMemory);
	int	i;

	for (i=0;i<npolys;i++) {
		nloops[i]	=	1;
	}

	addObject(new CPolygonMesh(attributes,xform,pl,npolys,nloops,nverts,verts));

	memEnd(CRenderer::globalMemory);
}

void	CRendererContext::RiPointsGeneralPolygonsV(int npolys,int *nloops,int *nverts,int *verts,int n,const char *tokens[],const void *params[]) {
	CXform			*xform;
	CAttributes		*attributes;
	float			*p0,*p1;
	CPl				*pl;
	int				i,j,k;

	int				sloops;				// The size of the loops array
	int				snverts;			// The size of the nverts array
	int				sverts;				// The size of the verts array
	int				numVertices;		// The number of vertices

	if (CRenderer::netNumServers > 0)	return;

	xform			=	getXform(FALSE);
	attributes		=	getAttributes(FALSE);
	
	checkGeometryOrDiscard();

	sloops		=	npolys;
	snverts		=	0;
	sverts		=	0;
	numVertices	=	0;
	k			=	0;

	for (i=0;i<sloops;i++) {
		snverts	+=	nloops[i];
		for (j=0;j<nloops[i];j++,k++) {
			sverts	+=	nverts[k];
		}
	}

	for (i=0;i<sverts;i++) {
		numVertices	=	max(numVertices,verts[i]);
	}
	
	pl				=	parseParameterList(npolys,numVertices+1,0,sverts,n,tokens,params,RI_P,PL_VARYING_TO_VERTEX,attributes);
	if (pl == NULL)	return;

	// We have the core
	switch(addMotion(pl->data0,pl->dataSize,"RiPointsGeneralPolygons",p0,p1)) {
	case 0:
		delete pl;
		return;
		break;
	case 1:
		// Restore the parameters
		if (pl->data0 != p0)
			memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);

		break;
	case 2:
		// Restore the parameters
		memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);
		pl->append(p1);

		break;
	default:
		break;
	}

	addObject(new CPolygonMesh(attributes,xform,pl,npolys,nloops,nverts,verts));
}

void	CRendererContext::RiBasis(float ubasis[][4],int ustep,float vbasis[][4],int vstep) {
	CAttributes *attributes;
	matrix		mtmp;
	int			i,j;

	// This is used in the client to parse the rib so we
	//  must not bail out when neterendering...

	attributes	=	getAttributes(TRUE);

	attributes->uStep	=	ustep;
	attributes->vStep	=	vstep;

	for (i=0;i<4;i++)
		for (j=0;j<4;j++)
			mtmp[element(i,j)]	=	ubasis[j][i];
	movmm(attributes->uBasis,mtmp);

	for (i=0;i<4;i++)
		for (j=0;j<4;j++)
			mtmp[element(i,j)]	=	vbasis[j][i];
	movmm(attributes->vBasis,mtmp);
}

#define	correct3begin(xv,yv)													\
{																				\
	int			i;																\
	const char	**newTokens	=	(const char **) ralloc(n*sizeof(char *),CRenderer::globalMemory);					\
	memcpy(newTokens,tokens,n*sizeof(char *));									\
	tokens				=	newTokens;											\
	for (i=0;i<n;i++) {															\
		if (strcmp(tokens[i],RI_PZ) == 0)	{									\
			float	*newData	=	(float *) ralloc(xv*yv*3*sizeof(float),CRenderer::globalMemory);	\
			float	*oldData	=	(float *) params[i];						\
			int		x,y;														\
			params[i]			=	(char *) newData;							\
			tokens[i]			=	(char *) RI_P;								\
																				\
			for (y=0;y<yv;y++) {												\
				for (x=0;x<xv;x++) {											\
					*newData++		=	x / (float) (xv-1);						\
					*newData++		=	y / (float) (yv-1);						\
					*newData++		=	*oldData++;								\
				}																\
			}																	\
		} else if (strcmp(tokens[i],RI_PW) == 0)	{							\
			float	*newData	=	(float *) ralloc(xv*yv*3*sizeof(float),CRenderer::globalMemory);	\
			float	*oldData	=	(float *) params[i];						\
			int		x,y;														\
			params[i]			=	(char *) newData;							\
			tokens[i]			=	(char *) RI_P;								\
																				\
			for (y=0;y<yv;y++) {												\
				for (x=0;x<xv;x++) {											\
					*newData++		=	oldData[0] / oldData[3];				\
					*newData++		=	oldData[1] / oldData[3];				\
					*newData++		=	oldData[2] / oldData[3];				\
					oldData			+=	4;										\
				}																\
			}																	\
		}																		\
	}																			\
}

#define correct3cbegin(xv)														\
{																				\
	int			i;																\
	const char	**newTokens	=	(const char **) ralloc(n*sizeof(char *),CRenderer::globalMemory);					\
	memcpy(newTokens,tokens,n*sizeof(char *));									\
	tokens				=	newTokens;											\
	for (i=0;i<n;i++) {															\
		if (strcmp(tokens[i],RI_PW) == 0)	{									\
			float	*newData	=	(float *) ralloc(xv*3*sizeof(float),CRenderer::globalMemory);		\
			float	*oldData	=	(float *) params[i];						\
			int		x;															\
			params[i]			=	(char *) newData;							\
			tokens[i]			=	(char *) RI_P;								\
																				\
			for (x=0;x<xv;x++) {												\
				*newData++		=	oldData[0] / oldData[3];					\
				*newData++		=	oldData[1] / oldData[3];					\
				*newData++		=	oldData[2] / oldData[3];					\
				oldData			+=	4;											\
			}																	\
		}																		\
	}																			\
}

#define	correct4begin(xv,yv)													\
{																				\
	int			i;																\
	const char	**newTokens	=	(const char **) ralloc(n*sizeof(char *),CRenderer::globalMemory);					\
	memcpy(newTokens,tokens,n*sizeof(char *));									\
	tokens				=	newTokens;											\
	for (i=0;i<n;i++) {															\
		if (strcmp(tokens[i],RI_PZ) == 0)	{									\
			float	*newData	=	(float *) ralloc(xv*yv*4*sizeof(float),CRenderer::globalMemory);	\
			float	*oldData	=	(float *) params[i];						\
			int		x,y;														\
			params[i]			=	(char *) newData;							\
			tokens[i]			=	(char *) RI_PW;								\
																				\
			for (y=0;y<yv;y++) {												\
				for (x=0;x<xv;x++) {											\
					*newData++		=	x / (float) (xv-1);						\
					*newData++		=	y / (float) (yv-1);						\
					*newData++		=	*oldData++;								\
					*newData++		=	1;										\
				}																\
			}																	\
																				\
		} else if (strcmp(tokens[i],RI_P) == 0) {								\
			float	*newData	=	(float *) ralloc(xv*yv*4*sizeof(float),CRenderer::globalMemory);	\
			float	*oldData	=	(float *) params[i];						\
			int		x,y;														\
			params[i]			=	(char *) newData;							\
			tokens[i]			=	(char *) RI_PW;								\
																				\
			for (y=0;y<yv;y++) {												\
				for (x=0;x<xv;x++) {											\
					*newData++		=	*oldData++;								\
					*newData++		=	*oldData++;								\
					*newData++		=	*oldData++;								\
					*newData++		=	1;										\
				}																\
			}																	\
		}																		\
	}																			\
}


void	CRendererContext::RiPatchV(const char * type,int n,const char *tokens[],const void *params[]) {
	CXform			*xform;
	CAttributes		*attributes;
	float			*p0,*p1;
	int				uver,vver;
	int				degree;
	CPl				*pl;

	if (CRenderer::netNumServers > 0)	return;

	xform			=	getXform(FALSE);
	attributes		=	getAttributes(FALSE);
	
	checkGeometryOrDiscard();

	if (strcmp(type,RI_BILINEAR) == 0)			{
		degree	=	1;
		uver	=	2;
		vver	=	2;
	} else if (strcmp(type,RI_BICUBIC) == 0)	{
		degree	=	3;
		uver	=	4;	
		vver	=	4;
	} else {
		error(CODE_BADTOKEN,"Unknown patch type: %s\n",type);
		return;
	}

	memBegin(CRenderer::globalMemory);

	correct3begin(uver,vver);
	
	pl				=	parseParameterList(1,uver*vver,4,0,n,tokens,params,RI_P,0,attributes);

	if (pl != NULL) {
		// We have the core
		switch(addMotion(pl->data0,pl->dataSize,"RiPatch",p0,p1)) {
		case 0:
			delete pl;
			break;
		case 1:
			// Restore the parameters
			if (pl->data0 != p0)
				memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);

			addObject(new CPatchMesh(attributes,xform,pl,degree,uver,vver,FALSE,FALSE));

			break;
		case 2:
			// Restore the parameters
			memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);
			pl->append(p1);

			addObject(new CPatchMesh(attributes,xform,pl,degree,uver,vver,FALSE,FALSE));
			break;
		default:
			break;
		}	
	}

	memEnd(CRenderer::globalMemory);
}


void	CRendererContext::RiPatchMeshV(const char *type,int nu,const char * uwrap,int nv,const char *vwrap,int n,const char *tokens[],const void *params[]) {
	CXform			*xform;
	CAttributes		*attributes;
	float			*p0,*p1;
	int				uw,vw;
	int				upatches,vpatches;
	CPl				*pl;
	int				numVertex,numVarying,numUniform;
	int				degree;

	if (CRenderer::netNumServers > 0)	return;

	attributes		=	getAttributes(FALSE);
	
	checkGeometryOrDiscard();

	if (strcmp(uwrap,RI_PERIODIC) == 0) {
		uw	=	TRUE;
	} else if ((strcmp(uwrap,RI_NONPERIODIC) == 0) || (strcmp(uwrap,RI_NOWRAP) == 0)) {
		uw	=	FALSE;
	} else {
		error(CODE_BADTOKEN,"Wrapping mode unrecognized: \"%s\"\n",uwrap);
		return;
	}

	if (strcmp(vwrap,RI_PERIODIC) == 0) {
		vw	=	TRUE;
	} else if ((strcmp(vwrap,RI_NONPERIODIC) == 0) || (strcmp(vwrap,RI_NOWRAP) == 0)) {
		vw	=	FALSE;
	} else {
		error(CODE_BADTOKEN,"Wrapping mode unrecognized: \"%s\"\n",vwrap);
		return;
	}

	if (strcmp(type,RI_BICUBIC) == 0) {
		degree	=	3;

		if (uw)		{
			if ((nu % attributes->uStep) != 0) {
				error(CODE_MISSINGDATA,"Unexpected number of u vertices\n");
				return;
			}

			upatches	=	(nu) / attributes->uStep;
		} else {
			if (((nu - 4) % attributes->uStep) != 0) {
				error(CODE_MISSINGDATA,"Unexpected number of u vertices\n");
				return;
			}

			upatches	=	((nu - 4) / attributes->uStep)+1;
		}

		if (vw)		{
			if ((nv % attributes->vStep) != 0) {
				error(CODE_MISSINGDATA,"Unexpected number of v vertices\n");
				return;
			}

			vpatches	=	(nv) / attributes->vStep;
		} else {
			if (((nv - 4) % attributes->vStep) != 0) {
				error(CODE_MISSINGDATA,"Unexpected number of v vertices\n");
				return;
			}

			vpatches	=	((nv - 4) / attributes->vStep)+1;
		}

		numVertex		=	nu*nv;
		numVarying		=	(upatches+1-uw)*(vpatches+1-vw);
		numUniform		=	upatches*vpatches;
	} else if (strcmp(type,RI_BILINEAR) == 0) {
		degree	=	1;
		if (uw)
			upatches	=	nu;
		else
			upatches	=	nu-1;

		if (vw)
			vpatches	=	nv;
		else
			vpatches	=	nv-1;

		numVertex		=	nu*nv;
		numVarying		=	nu*nv;
		numUniform		=	upatches*vpatches;
	} else {
		error(CODE_BADTOKEN,"Unknown patch type: %s\n",type);
		return;
	}

	memBegin(CRenderer::globalMemory);

	correct3begin(nu,nv);

	xform			=	getXform(FALSE);
	pl				=	parseParameterList(numUniform,numVertex,numVarying,0,n,tokens,params,RI_P,0,attributes);

	if (pl != NULL) {
		// We have the core
		switch(addMotion(pl->data0,pl->dataSize,"RiPatchMesh",p0,p1)) {
		case 0:
			delete pl;
			break;
		case 1:
			// Restore the parameters
			if (pl->data0 != p0)
				memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);

 			addObject(new CPatchMesh(attributes,xform,pl,degree,nu,nv,uw,vw));

			break;
		case 2:
			memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);
			pl->append(p1);

			addObject(new CPatchMesh(attributes,xform,pl,degree,nu,nv,uw,vw));

			break;
		}	
	}

	memEnd(CRenderer::globalMemory);
}

void	CRendererContext::RiNuPatchV(int nu,int uorder,float *uknot,float umin,float umax,int nv,int vorder,float *vknot,float vmin,float vmax,int n,const char *tokens[],const void *params[]) {
	CXform			*xform;
	CAttributes		*attributes;
	float			*p0,*p1;
	int				upatches,vpatches;
	CPl				*pl;

	if (CRenderer::netNumServers > 0)	return;

	xform			=	getXform(FALSE);
	attributes		=	getAttributes(FALSE);
	
	checkGeometryOrDiscard();

	memBegin(CRenderer::globalMemory);

	correct4begin(nu,nv);

	upatches		=	nu - uorder + 1;
	vpatches		=	nv - vorder + 1;
	
	pl				=	parseParameterList(upatches*vpatches,nu*nv,(upatches+1)*(vpatches+1),0,n,tokens,params,RI_PW,0,attributes);

	if (pl != NULL) {
		// We have the core
		switch(addMotion(pl->data0,pl->dataSize,"RiNuPatch",p0,p1)) {
		case 0:
			delete pl;
			break;
		case 1:
			// Restore the parameters
			if (pl->data0 != p0)
				memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);

			addObject(new CNURBSPatchMesh(attributes,xform,pl,nu,nv,uorder,vorder,uknot,vknot));

			break;
		case 2:
			memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);
			pl->append(p1);

			addObject(new CNURBSPatchMesh(attributes,xform,pl,nu,nv,uorder,vorder,uknot,vknot));

			break;
		default:
			break;
		}	
	}

	memEnd(CRenderer::globalMemory);
}

void	CRendererContext::RiTrimCurve (int nloops,int *ncurves,int *order,float *knot,float *amin,float *amax,int *n,float *u,float *v,float *w) {
	if (CRenderer::netNumServers > 0)	return;

	error(CODE_INCAPABLE,"Trim curves are not currently supported\n");
}

void	CRendererContext::RiCurvesV(const char *d,int ncurves,int nverts[],const char *w,int n,const char *tokens[],const void *params[]) {
	CAttributes	*attributes;
	CXform		*xform;
	float		*p0,*p1;
	int			numVertices,numSegments,numVaryings;
	int			i;
	int			degree,wrap;
	CPl			*pl;

	if (CRenderer::netNumServers > 0)	return;

	attributes		=	getAttributes(FALSE);
	
	checkGeometryOrDiscard();
	
	xform			=	getXform(FALSE);

	if (strcmp(d,RI_LINEAR) == 0) {
		degree	=	1;

		if (strcmp(w,RI_PERIODIC) == 0) {
			for (numVertices=0,numSegments=0,numVaryings=0,i=0;i<ncurves;i++) {
				numVertices	+=	nverts[i];
				numSegments	+=	nverts[i];
				numVaryings	+=	nverts[i];
			}

			wrap		=	TRUE;
		} else {
			for (numVertices=0,numSegments=0,numVaryings=0,i=0;i<ncurves;i++) {
				numVertices	+=	nverts[i];
				numSegments	+=	nverts[i] - 1;
				numVaryings	+=	nverts[i];
			}

			wrap		=	FALSE;
		}
	} else if (strcmp(d,RI_CUBIC) == 0) {
		degree	=	3;

		if (strcmp(w,RI_PERIODIC) == 0) {
			for (numVertices=0,numSegments=0,numVaryings=0,i=0;i<ncurves;i++) {
				numVertices	+=	nverts[i];
				numSegments	+=	(nverts[i] - 4) / attributes->vStep + 1;
				numVaryings	+=	(nverts[i] - 4) / attributes->vStep + 1;
			}

			wrap		=	TRUE;
		} else {
			for (numVertices=0,numSegments=0,numVaryings=0,i=0;i<ncurves;i++) {
				numVertices	+=	nverts[i];
				numSegments	+=	nverts[i] / attributes->vStep;
				numVaryings	+=	(nverts[i] - 4) / attributes->vStep + 2;
			}

			wrap		=	FALSE;
		}
	} else {
		error(CODE_BADTOKEN,"Unknown curve degree: \"%s\"\n",d);
		return;
	}

	memBegin(CRenderer::globalMemory);
	
	correct3cbegin(numVertices);
	
	pl				=	parseParameterList(ncurves,numVertices,numVaryings,0,n,tokens,params,RI_P,0,attributes);
	if (pl == NULL)	return;
	

	// We have the core
	switch(addMotion(pl->data0,pl->dataSize,"CRendererContext::RiCurves",p0,p1)) {
	case 0:
		if (pl != NULL)	delete pl;
		break;
	case 1:
		if (p0 != pl->data0)
			memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);

		addObject(new CCurveMesh(attributes,xform,pl,degree,numVertices,ncurves,nverts,wrap));

		break;
	case 2:
		// Restore the parameters
		memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);
		pl->append(p1);

		addObject(new CCurveMesh(attributes,xform,pl,degree,numVertices,ncurves,nverts,wrap));

		break;
	default:
		break;
	}	

	memEnd(CRenderer::globalMemory);

}

#undef correct3begin
#undef correct4begin
#undef correct3cbegin

void	CRendererContext::RiSphereV(float radius,float zmin,float zmax,float thetamax,int n,const char *tokens[],const void *params[]) {
	CXform			*xform;
	CAttributes		*attributes;
	float			*p0,*p1;
	float			*data;
	int				dataSize;
	CPl				*pl;
	CParameter		*parameters;
	unsigned int	parametersF;
	float			tmp;

	if (CRenderer::netNumServers > 0)	return;

	attributes		=	getAttributes(FALSE);
	xform			=	getXform(FALSE);
	
	checkGeometryOrDiscard();
	
	pl				=	parseParameterList(1,0,4,0,n,tokens,params,NULL,PL_VERTEX_TO_VARYING,attributes);

	memBegin(CRenderer::globalMemory);

	if (pl == NULL) {
		data		=	(float *) ralloc(4*sizeof(float),CRenderer::globalMemory);
		dataSize	=	4;
		parametersF	=	0;
	} else {
		data		=	(float *) ralloc((pl->dataSize+4)*sizeof(float),CRenderer::globalMemory);
		dataSize	=	4+pl->dataSize;
		memcpy(&data[4],pl->data0,pl->dataSize*sizeof(float));
		parametersF	=	pl->parameterUsage();
	}

	data[0]			=	radius;
	data[1]			=	zmin;
	data[2]			=	zmax;
	data[3]			=	thetamax;

	// We have the core
	switch(addMotion(data,dataSize,"CRendererContext::RiSphere",p0,p1)) {
	case 0:
		break;
	case 1:

		// Do we have a sphere ?
		if (	(p0[0] != 0)		&&
				(p0[1] != p0[2])	&&
				(p0[3] != 0)	) {

			if (pl != NULL)	memcpy(pl->data0,&p0[4],sizeof(float)*pl->dataSize);

			parameters	=	pl->uniform(0,NULL);
			parameters	=	pl->varying(0,1,2,3,parameters);;

			tmp			=	absf(p0[0]);
			p0[1]		=	min(max(p0[1],-tmp),tmp);
			p0[2]		=	min(max(p0[2],-tmp),tmp);
			p0[1]		=	(float) asin(p0[1] / p0[0]);
			p0[2]		=	(float) asin(p0[2] / p0[0]);

			addObject(new CSphere(attributes,xform,parameters,parametersF,p0[0],p0[1],p0[2],(float) radians(p0[3])));
		}
		break;
	case 2:

		// Do we have a moving sphere ?
		if (	((p0[0] != 0)		||	(p1[0] != 0))		&&
				((p0[1] != p0[2])	||	(p1[1] != p1[2]))	&&
				((p0[3] != 0)		||	(p1[3] != 0))) {

			// Restore the parameters
			if (pl != NULL)	{
				memcpy(pl->data0,&p0[4],sizeof(float)*pl->dataSize);
				pl->append(p1+4);
			}

			parameters	=	pl->uniform(0,NULL);
			parameters	=	pl->varying(0,1,2,3,parameters);;

			tmp			=	absf(p0[0]);
			p0[1]		=	min(max(p0[1],-tmp),tmp);
			p0[2]		=	min(max(p0[2],-tmp),tmp);
			p0[1]		=	(float) asin(p0[1] / p0[0]);
			p0[2]		=	(float) asin(p0[2] / p0[0]);

			tmp			=	absf(p0[1]);
			p1[1]		=	min(max(p1[1],-tmp),tmp);
			p1[2]		=	min(max(p1[2],-tmp),tmp);
			p1[1]		=	(float) asin(p1[1] / p1[0]);
			p1[2]		=	(float) asin(p1[2] / p1[0]);

			addObject(new CSphere(attributes,xform,parameters,parametersF,p0[0],p0[1],p0[2],(float) radians(p0[3]),p1[0],p1[1],p1[2],(float) radians(p1[3])));
		}
		break;
	default:
		break;
	}	

	if (pl != NULL)	delete pl;

	memEnd(CRenderer::globalMemory);
}

void	CRendererContext::RiConeV (float height,float radius,float thetamax,int n,const char *tokens[],const void *params[]) {
	CXform			*xform;
	CAttributes		*attributes;
	float			*p0,*p1;
	float			*data;
	int				dataSize;
	CPl				*pl;
	CParameter		*parameters;
	unsigned int	parametersF;

	if (CRenderer::netNumServers > 0)	return;

	attributes		=	getAttributes(FALSE);
	
	checkGeometryOrDiscard();
	
	xform			=	getXform(FALSE);
	pl				=	parseParameterList(1,0,4,0,n,tokens,params,NULL,PL_VERTEX_TO_VARYING,attributes);

	memBegin(CRenderer::globalMemory);

	if (pl == NULL) {
		data		=	(float *) ralloc(3*sizeof(float),CRenderer::globalMemory);
		dataSize	=	3;
		parametersF	=	0;
	} else {
		data		=	(float *) ralloc((pl->dataSize+3)*sizeof(float),CRenderer::globalMemory);
		dataSize	=	3+pl->dataSize;
		memcpy(&data[3],pl->data0,pl->dataSize*sizeof(float));
		parametersF	=	pl->parameterUsage();
	}

	data[0]			=	radius;
	data[1]			=	height;
	data[2]			=	thetamax;

	// We have the core
	switch(addMotion(data,dataSize,"CRendererContext::RiCone",p0,p1)) {
	case 0:
		break;
	case 1:

		// Do we have a cone ?
		if (	(p0[0] != 0)	&&
				(p0[2] != 0)	) {
			if (pl != NULL)	memcpy(pl->data0,&p0[3],sizeof(float)*pl->dataSize);

			parameters	=	pl->uniform(0,NULL);
			parameters	=	pl->varying(0,1,2,3,parameters);;

			addObject(new CCone(attributes,xform,parameters,parametersF,p0[0],p0[1],(float) radians(p0[2])));
		}
		break;
	case 2:

		// Do we have a moving cone ?
		if (	((p0[0] != 0)	||	(p1[0] != 0))	&&
				((p0[2] != 0)	||	(p1[2] != 0))) {
			// Restore the parameters
			if (pl != NULL)	{
				memcpy(pl->data0,&p0[3],sizeof(float)*pl->dataSize);
				pl->append(p1+3);
			}

			parameters	=	pl->uniform(0,NULL);
			parameters	=	pl->varying(0,1,2,3,parameters);;

			addObject(new CCone(attributes,xform,parameters,parametersF,p0[0],p0[1],(float) radians(p0[2]),p1[0],p1[1],(float) radians(p1[2])));
		}
		break;
	default:
		break;
	}	

	if (pl != NULL)	delete pl;

	memEnd(CRenderer::globalMemory);
}

void	CRendererContext::RiCylinderV (float radius,float zmin,float zmax,float thetamax,int n,const char *tokens[],const void *params[]) {
	CXform			*xform;
	CAttributes		*attributes;
	float			*p0,*p1;
	float			*data;
	int				dataSize;
	CPl				*pl;
	CParameter		*parameters;
	unsigned int	parametersF;

	if (CRenderer::netNumServers > 0)	return;

	attributes		=	getAttributes(FALSE);
	
	checkGeometryOrDiscard();
	
	xform			=	getXform(FALSE);
	pl				=	parseParameterList(1,0,4,0,n,tokens,params,NULL,PL_VERTEX_TO_VARYING,attributes);

	memBegin(CRenderer::globalMemory);

	if (pl == NULL) {
		data		=	(float *) ralloc(4*sizeof(float),CRenderer::globalMemory);
		dataSize	=	4;
		parametersF	=	0;
	} else {
		data		=	(float *) ralloc((pl->dataSize+4)*sizeof(float),CRenderer::globalMemory);
		dataSize	=	4+pl->dataSize;
		memcpy(&data[4],pl->data0,pl->dataSize*sizeof(float));
		parametersF	=	pl->parameterUsage();
	}

	data[0]			=	radius;
	data[1]			=	zmin;
	data[2]			=	zmax;
	data[3]			=	thetamax;

	// We have the core
	switch(addMotion(data,dataSize,"CRendererContext::RiCylinder",p0,p1)) {
	case 0:
		break;
	case 1:

		// Do we have a cylinder ?
		if (	(p0[0] != 0)		&&
				(p0[1] != p0[2])	&&
				(p0[3] != 0)	) {

			if (pl != NULL)	memcpy(pl->data0,&p0[4],sizeof(float)*pl->dataSize);

			parameters	=	pl->uniform(0,NULL);
			parameters	=	pl->varying(0,1,2,3,parameters);;

			addObject(new CCylinder(attributes,xform,parameters,parametersF,p0[0],p0[1],p0[2],(float) radians(p0[3])));
		}
		break;
	case 2:

		// Do we have a moving cylinder ?
		if (	((p0[0] != 0)		||	(p1[0] != 0))		&&
				((p0[1] != p0[2])	||	(p1[1] != p1[2]))	&&
				((p0[3] != 0)		||	(p1[3] != 0))) {

			// Restore the parameters
			if (pl != NULL)	{
				memcpy(pl->data0,&p0[4],sizeof(float)*pl->dataSize);
				pl->append(p1+4);
			}

			parameters	=	pl->uniform(0,NULL);
			parameters	=	pl->varying(0,1,2,3,parameters);;

			addObject(new CCylinder(attributes,xform,parameters,parametersF,p0[0],p0[1],p0[2],(float) radians(p0[3]),p1[0],p1[1],p1[2],(float) radians(p1[3])));
		}
		break;
	default:
		break;
	}	

	if (pl != NULL)	delete pl;

	memEnd(CRenderer::globalMemory);
}

void	CRendererContext::RiHyperboloidV (float *point1,float *point2,float thetamax,int n,const char *tokens[],const void *params[]) {
	CXform			*xform;
	CAttributes		*attributes;
	float			*p0,*p1;
	float			*data;
	int				dataSize;
	CPl				*pl;
	CParameter		*parameters;
	unsigned int	parametersF;
	vector			D0,D1;

	if (CRenderer::netNumServers > 0)	return;

	attributes		=	getAttributes(FALSE);
	
	checkGeometryOrDiscard();
	
	xform			=	getXform(FALSE);
	pl				=	parseParameterList(1,0,4,0,n,tokens,params,NULL,PL_VERTEX_TO_VARYING,attributes);

	memBegin(CRenderer::globalMemory);

	if (pl == NULL) {
		data		=	(float *) ralloc(7*sizeof(float),CRenderer::globalMemory);
		dataSize	=	7;
		parametersF	=	0;
	} else {
		data		=	(float *) ralloc((pl->dataSize+7)*sizeof(float),CRenderer::globalMemory);
		dataSize	=	7+pl->dataSize;
		memcpy(&data[7],pl->data0,pl->dataSize*sizeof(float));
		parametersF	=	pl->parameterUsage();
	}

	data[0]			=	point1[0];
	data[1]			=	point1[1];
	data[2]			=	point1[2];
	data[3]			=	point2[0];
	data[4]			=	point2[1];
	data[5]			=	point2[2];
	data[6]			=	thetamax;

	// We have the core
	switch(addMotion(data,dataSize,"CRendererContext::RiHyperboloid",p0,p1)) {
	case 0:
		break;
	case 1:

		// Do we have a hyperboloid ?
		subvv(D0,p0+3,p0);
		if (	(dotvv(D0,D0) != 0)	&&
				(p0[6] != 0)	) {

			if (pl != NULL)	memcpy(pl->data0,&p0[7],sizeof(float)*pl->dataSize);

			parameters	=	pl->uniform(0,NULL);
			parameters	=	pl->varying(0,1,2,3,parameters);;

			addObject(new CHyperboloid(attributes,xform,parameters,parametersF,&p0[0],&p0[3],(float) radians(p0[6])));
		}
		break;
	case 2:

		// Do we have a moving hyperboloid ?
		subvv(D0,p0+3,p0);
		subvv(D1,p1+3,p1);
		if (	((dotvv(D0,D0) != 0)	||	(dotvv(D1,D1) != 0))	&&
				((p0[6] != 0)			||	(p1[6] != 0))	) {

			// Restore the parameters
			if (pl != NULL)	{
				memcpy(pl->data0,&p0[7],sizeof(float)*pl->dataSize);
				pl->append(p1+7);
			}

			parameters	=	pl->uniform(0,NULL);
			parameters	=	pl->varying(0,1,2,3,parameters);;

			addObject(new CHyperboloid(attributes,xform,parameters,parametersF,&p0[0],&p0[3],(float) radians(p0[6]),&p1[0],&p1[3],(float) radians(p1[6])));
		}
		break;
	default:
		break;
	}	

	if (pl != NULL) delete pl;

	memEnd(CRenderer::globalMemory);
}

void	CRendererContext::RiParaboloidV(float radius,float zmin,float zmax,float thetamax,int n,const char *tokens[],const void *params[]) {
	CXform			*xform;
	CAttributes		*attributes;
	float			*p0,*p1;
	float			*data;
	int				dataSize;
	CPl				*pl;
	CParameter		*parameters;
	unsigned int	parametersF;

	if (CRenderer::netNumServers > 0)	return;

	attributes		=	getAttributes(FALSE);
	
	checkGeometryOrDiscard();
	
	xform			=	getXform(FALSE);
	pl				=	parseParameterList(1,0,4,0,n,tokens,params,NULL,PL_VERTEX_TO_VARYING,attributes);

	memBegin(CRenderer::globalMemory);

	if (pl == NULL) {
		data		=	(float *) ralloc(4*sizeof(float),CRenderer::globalMemory);
		dataSize	=	4;
		parametersF	=	0;
	} else {
		data		=	(float *) ralloc((pl->dataSize+4)*sizeof(float),CRenderer::globalMemory);
		dataSize	=	4+pl->dataSize;
		memcpy(&data[4],pl->data0,pl->dataSize*sizeof(float));
		parametersF	=	pl->parameterUsage();
	}

	data[0]			=	radius;
	data[1]			=	zmin;
	data[2]			=	zmax;
	data[3]			=	thetamax;

	// We have the core
	switch(addMotion(data,dataSize,"CRendererContext::RiParaboloid",p0,p1)) {
	case 0:
		break;
	case 1:

		// Do we have a paraboloid ?
		if (	(p0[0] != 0)		&&
				(p0[1] != p0[2])	&&
				(p0[3] != 0)	) {

			if (pl != NULL)	memcpy(pl->data0,&p0[4],sizeof(float)*pl->dataSize);

			parameters	=	pl->uniform(0,NULL);
			parameters	=	pl->varying(0,1,2,3,parameters);;

			if (p0[1] != p0[2])
				addObject(new CParaboloid(attributes,xform,parameters,parametersF,p0[0],p0[1],p0[2],(float) radians(p0[3])));
		}
		break;
	case 2:

		// Do we have a moving paraboloid ?
		if (	((p0[0] != 0)		||	(p1[0] != 0))		&&
				((p0[1] != p0[2])	||	(p1[1] != p1[2]))	&&
				((p0[3] != 0)		||	(p1[3] != 0))) {

			// Restore the parameters
			if (pl != NULL)	{
				memcpy(pl->data0,&p0[4],sizeof(float)*pl->dataSize);
				pl->append(p1+4);
			}

			parameters	=	pl->uniform(0,NULL);
			parameters	=	pl->varying(0,1,2,3,parameters);;

			if ((p0[1] != p0[2]) || (p1[1] != p1[2]))
				addObject(new CParaboloid(attributes,xform,parameters,parametersF,p0[0],p0[1],p0[2],(float) radians(p0[3]),p1[0],p1[1],p1[2],(float) radians(p1[3])));
		}
		break;
	default:
		break;
	}	

	if (pl != NULL)	delete pl;

	memEnd(CRenderer::globalMemory);
}

void	CRendererContext::RiDiskV (float height,float radius,float thetamax,int n,const char *tokens[],const void *params[]) {
	CXform			*xform;
	CAttributes		*attributes;
	float			*p0,*p1;
	float			*data;
	int				dataSize;
	CPl				*pl;
	CParameter		*parameters;
	unsigned int	parametersF;

	if (CRenderer::netNumServers > 0)			return;

	attributes		=	getAttributes(FALSE);
	
	checkGeometryOrDiscard();
	
	xform			=	getXform(FALSE);
	pl				=	parseParameterList(1,0,4,0,n,tokens,params,NULL,PL_VERTEX_TO_VARYING,attributes);

	memBegin(CRenderer::globalMemory);

	if (pl == NULL) {
		data		=	(float *) ralloc(3*sizeof(float),CRenderer::globalMemory);
		dataSize	=	3;
		parametersF	=	0;
	} else {
		data		=	(float *) ralloc((pl->dataSize+3)*sizeof(float),CRenderer::globalMemory);
		dataSize	=	3+pl->dataSize;
		memcpy(&data[3],pl->data0,pl->dataSize*sizeof(float));
		parametersF	=	pl->parameterUsage();
	}


	data[0]			=	radius;
	data[1]			=	height;
	data[2]			=	thetamax;

	// We have the core
	switch(addMotion(data,dataSize,"CRendererContext::RiDisk",p0,p1)) {
	case 0:
		break;
	case 1:

		// Do we have a disk ?
		if (	(p0[0]	!= 0)	&&
				(p0[2]	!= 0)) {

			if (pl != NULL)	memcpy(pl->data0,&p0[3],sizeof(float)*pl->dataSize);

			parameters	=	pl->uniform(0,NULL);
			parameters	=	pl->varying(0,1,2,3,parameters);;

			addObject(new CDisk(attributes,xform,parameters,parametersF,p0[0],p0[1],(float) radians(p0[2])));
		}
		break;
	case 2:

		// Do we have a moving disk ?
		if (	((p0[0]	!= 0)	||	(p1[0]	!= 0))	&&
				((p0[2]	!= 0)	|	(p1[2]	!= 0))) {

			// Restore the parameters
			if (pl != NULL)	{
				memcpy(pl->data0,&p0[3],sizeof(float)*pl->dataSize);
				pl->append(p1+3);
			}

			parameters	=	pl->uniform(0,NULL);
			parameters	=	pl->varying(0,1,2,3,parameters);;

			addObject(new CDisk(attributes,xform,parameters,parametersF,p0[0],p0[1],(float) radians(p0[2]),p1[0],p1[1],(float) radians(p1[2])));
		}
		break;
	default:
		break;
	}	

	if (pl != NULL)	delete pl;

	memEnd(CRenderer::globalMemory);
}

void	CRendererContext::RiTorusV (float majorrad,float minorrad,float phimin,float phimax,float thetamax,int n,const char *tokens[],const void *params[]) {
	CXform			*xform;
	CAttributes		*attributes;
	float			*p0,*p1;
	float			*data;
	int				dataSize;
	CPl				*pl;
	CParameter		*parameters;
	unsigned int	parametersF;

	if (CRenderer::netNumServers > 0)	return;

	attributes		=	getAttributes(FALSE);
	
	checkGeometryOrDiscard();
	
	xform			=	getXform(FALSE);
	pl				=	parseParameterList(1,0,4,0,n,tokens,params,NULL,PL_VERTEX_TO_VARYING,attributes);

	memBegin(CRenderer::globalMemory);

	if (pl == NULL) {
		data		=	(float *) ralloc(5*sizeof(float),CRenderer::globalMemory);
		dataSize	=	5;
		parametersF	=	0;
	} else {
		data		=	(float *) ralloc((pl->dataSize+5)*sizeof(float),CRenderer::globalMemory);
		dataSize	=	5+pl->dataSize;
		memcpy(&data[5],pl->data0,pl->dataSize*sizeof(float));
		parametersF	=	pl->parameterUsage();
	}

	data[0]			=	minorrad;
	data[1]			=	majorrad;
	data[2]			=	phimin;
	data[3]			=	phimax;
	data[4]			=	thetamax;

	// We have the core
	switch(addMotion(data,dataSize,"CRendererContext::RiTorus",p0,p1)) {
	case 0:
		break;
	case 1:
		// Do we have a torus ?
		if (	(p0[0] != p0[1]) && 
				(p0[2] != p0[3]) && 
				(p0[4] != 0)) {

			if (pl != NULL)	memcpy(pl->data0,&p0[5],sizeof(float)*pl->dataSize);

			parameters	=	pl->uniform(0,NULL);
			parameters	=	pl->varying(0,1,2,3,parameters);;

			addObject(new CToroid(attributes,xform,parameters,parametersF,p0[0],p0[1],(float) radians(p0[2]),(float) radians(p0[3]),(float) radians(p0[4])));
		}
		break;
	case 2:
		// Do we have a torus ?
		if (	((p0[0] != p0[1]) || (p1[0] != p1[1])) &&
				((p0[2] != p0[3]) || (p1[2] != p1[3])) &&
				((p0[4] != 0)	  || (p1[4] != 0))) {

			// Restore the parameters
			if (pl != NULL)	{
				memcpy(pl->data0,&p0[5],sizeof(float)*pl->dataSize);
				pl->append(p1+5);
			}

			parameters	=	pl->uniform(0,NULL);
			parameters	=	pl->varying(0,1,2,3,parameters);;

			addObject(new CToroid(attributes,xform,parameters,parametersF,p0[0],p0[1],(float) radians(p0[2]),(float) radians(p0[3]),(float) radians(p0[4]),p1[0],p1[1],(float) radians(p1[2]),(float) radians(p1[3]),(float) radians(p1[4])));
		}
		break;
	default:
		break;
	}	

	if (pl != NULL)	delete pl;

	memEnd(CRenderer::globalMemory);
}


void	CRendererContext::RiProcedural(void *data,float *bound,void (*subdivfunc) (void *,float),void (*freefunc) (void *)) {
	CDelayedObject	*cObject;
	CXform			*xform;
	CAttributes		*attributes;
	vector			bmin,bmax;

	if (CRenderer::netNumServers > 0)	return;

	xform		=	getXform(FALSE);
	attributes	=	getAttributes(FALSE);
	
	checkGeometryOrDiscard();

	if ((xform != NULL) && (attributes != NULL)) {
		bmin[COMP_X]	=	bound[0];
		bmax[COMP_X]	=	bound[1];
		bmin[COMP_Y]	=	bound[2];
		bmax[COMP_Y]	=	bound[3];
		bmin[COMP_Z]	=	bound[4];
		bmax[COMP_Z]	=	bound[5];

		cObject	=	new CDelayedObject(attributes,xform,bmin,bmax,subdivfunc,freefunc,data);

		addObject(cObject);
	}
}


void	CRendererContext::RiGeometryV(const char *type,int n,const char *tokens[],const void *params[]) {
	if (CRenderer::netNumServers > 0)	return;
		
	if (strcmp(type,"implicit") == 0) {
		int				i;
		const char		*name				=	NULL;
		int				frame				=	currentOptions->frame;
		float			stepSize			=	(float) 0.1;
		float			scaleFactor			=	(float) 0.5;
		CAttributes		*attributes			=	getAttributes(FALSE);
		
		checkGeometryOrDiscard();

		for (i=0;i<n;i++) {
			if (strcmp(tokens[i],"file") == 0) {
				name				=	((const char **) params[i])[0];
			} else if (strcmp(tokens[i],"frame") == 0) {
				frame				=	(int) ((float *) params[i])[0];
			} else if (strcmp(tokens[i],"stepSize") == 0) {
				stepSize			=	((float *) params[i])[0];
			} else if (strcmp(tokens[i],"scaleFactor") == 0) {
				scaleFactor	=	((float *) params[i])[0];
			} else {
				CVariable	var;

				if (parseVariable(&var,NULL,tokens[i])) {
					tokens[i]	=	var.name;
					i--;
				} else {
					error(CODE_BADTOKEN,"Unrecognized implicit parameter: %s\n",tokens[i]);
				}
			}
		}

		if (name == NULL)	{
			error(CODE_BADTOKEN,"Implicit geometry requires a DSO name\n");
		} else {
			char	location[OS_MAX_PATH_LENGTH];

			if (CRenderer::locateFileEx(location,name,osModuleExtension,currentOptions->proceduralPath)) {
				CObject	*cObject	=	new CImplicit(getAttributes(FALSE),getXform(FALSE),frame,location,stepSize,scaleFactor);

				addObject(cObject);
			} else {
				error(CODE_NOFILE,"Failed to find \"%s\" in the procedural path\n",name);
			}
		}
	} else if (strcmp(type,"dlo") == 0) {
		int				i;
		const char		*name				=	NULL;
		int				frame				=	currentOptions->frame;
		CAttributes		*attributes			=	getAttributes(FALSE);
		
		checkGeometryOrDiscard();
		
		for (i=0;i<n;i++) {
			if (strcmp(tokens[i],"file") == 0) {
				name				=	(const char *) params[i];
			} else {
				CVariable	var;

				if (parseVariable(&var,NULL,tokens[i])) {
					tokens[i]	=	var.name;
					i--;
				} else {
					error(CODE_BADTOKEN,"Unrecognized implicit parameter: %s\n",tokens[i]);
				}
			}
		}

		if (name == NULL)	{
			error(CODE_BADTOKEN,"Dynamic object requires a DSO name\n");
		} else {
			char	location[OS_MAX_PATH_LENGTH];

			if (CRenderer::locateFileEx(location,name,osModuleExtension,currentOptions->proceduralPath)) {
				void	*handle,*data;
				vector	bmin,bmax;

				handle		=	osLoadModule(name);

				if (handle != NULL) {
					dloInitFunction				initFunction		=	(dloInitFunction)		osResolve(handle,"dloInit");
					dloIntersectFunction		intersectFunction	=	(dloIntersectFunction)	osResolve(handle,"dloIntersect");
					dloTiniFunction				tiniFunction		=	(dloTiniFunction)		osResolve(handle,"dloTini");

					if (initFunction != NULL) {
						if (intersectFunction != NULL) {
							if (tiniFunction != NULL) {
								data	=	initFunction(frame,bmin,bmax);

								if (data != NULL) {
									addObject(new CDLObject(getAttributes(FALSE),getXform(FALSE),handle,data,bmin,bmax,initFunction,intersectFunction,tiniFunction));
								} else {
									error(CODE_BADFILE,"DLO \"%s\" failed to initialize\n",name);
								}
							} else {
								error(CODE_BADFILE,"Missing \"dloTini\" in DLO \"%s\"\n",name);
							}
						} else {
							error(CODE_BADFILE,"Missing \"dloIntersect\" in DLO \"%s\"\n",name);
						}
					} else {
						error(CODE_BADFILE,"Missing \"dloInit\" in DLO \"%s\"\n",name);
					}
				} else {
					error(CODE_BADFILE,"Failed to load DLO \"%s\"\n",name);
				}
			} else {
				error(CODE_NOFILE,"Failed to load \"%s\": %s\n",name,osModuleError());
			}
		}
	} else {
		error(CODE_BADTOKEN,"Unknown geometry: \"%s\"\n",type);
	}
}


void	CRendererContext::RiPointsV(int npts,int n,const char *tokens[],const void *params[]) {
	CAttributes	*attributes;
	CXform		*xform;
	float		*p0,*p1;
	CPl			*pl;

	if (CRenderer::netNumServers > 0)	return;

	attributes		=	getAttributes(FALSE);
	
	checkGeometryOrDiscard();
	
	xform			=	getXform(FALSE);
	pl				=	parseParameterList(1,npts,0,0,n,tokens,params,RI_P,PL_VARYING_TO_VERTEX,attributes);
	if (pl == NULL)	return;

	memBegin(CRenderer::globalMemory);

	// We have the core
	switch(addMotion(pl->data0,pl->dataSize,"CRendererContext::RiPoints",p0,p1)) {
	case 0:
		if (pl != NULL)	delete pl;
		break;
	case 1:
		if (p0 != pl->data0)
			memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);

		addObject(new CPoints(attributes,xform,pl,npts));
		break;
	case 2:
		// Restore the parameters
		memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);
		pl->append(p1);

		addObject(new CPoints(attributes,xform,pl,npts));
		break;
	default:
		break;
	}	

	memEnd(CRenderer::globalMemory);
}

void	CRendererContext::RiSubdivisionMeshV(const char * scheme,int nfaces,int nvertices[],int vertices[],int ntags,const char * tags[],int nargs[],int intargs[],float floatargs[],int n,const char *tokens[],const void *params[]) {
	int			i,j;
	int			numVertices;
	CPl			*pl;
	CAttributes	*attributes;
	CXform		*xform;
	float		*p0,*p1;

	if (CRenderer::netNumServers > 0)	return;

	xform		=	getXform(FALSE);
	attributes	=	getAttributes(FALSE);

	checkGeometryOrDiscard();

	// Only catmull clark is supported for the time being
	if (strcmp(scheme,RI_CATMULLCLARK) != 0) {
		error(CODE_INCAPABLE,"Unknown subdivision scheme: %s\n",scheme);
		return;
	}
			
	// Count the number of faces / vertices
	for (i=0,j=0;i<nfaces;j+=nvertices[i],i++);

	for (numVertices=-1,i=0;i<j;i++) {
		if (vertices[i] > numVertices)	numVertices	=	vertices[i];
	}
	numVertices++;

	// Create the core
	pl		=	parseParameterList(nfaces,numVertices,numVertices,j,n,tokens,params,RI_P,PL_VARYING_TO_VERTEX,attributes);
	if (pl == NULL)	return;

	switch(addMotion(pl->data0,pl->dataSize,"RiSubdivisionMesh",p0,p1)) {
	case 0:
		// Clean up the unneeded pl
		delete pl;
		// Get out of here
		return;
		break;
	case 1:
		if (p0 != pl->data0)
			memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);
		break;
	case 2:
		// Restore the parameters
		memcpy(pl->data0,p0,sizeof(float)*pl->dataSize);
		pl->append(p1);
		break;
	default:
		break;
	}

	// Create the object
	addObject(new CSubdivMesh(attributes,xform,pl,nfaces,nvertices,vertices,ntags,tags,nargs,intargs,floatargs));
}

void	CRendererContext::RiBlobbyV(int nleaf,int ncode,int code[],int nflt,float flt[],int nstr,const char *str[],int n,const char *tokens[],const void *params[]) {

	if (CRenderer::netNumServers > 0)	return;

	error(CODE_INCAPABLE,"Blobby primitives are not currently supported\n");
}


void	CRendererContext::RiSolidBegin(const char *type) {
	if (CRenderer::netNumServers > 0)	return;

	error(CODE_OPTIONAL,"CSG is not currently supported\n");
}

void	CRendererContext::RiSolidEnd(void) {
	if (CRenderer::netNumServers > 0)	return;
}

void	*CRendererContext::RiObjectBegin (void) {
	CXform	*xForm;

	if (CRenderer::netNumServers > 0)	return NULL;

	// Reset the xform so that all the objects defined relative to the beginning of the block
	xformBegin();
	
	xForm	=	getXform(TRUE);
	xForm->identity();
	if (xForm->next != NULL)	xForm->next->identity();

	// Create a new object
	instanceStack->push(instance);
	instance			=	new CInstance;
	instance->objects	=	NULL;
	return	instance;
}


void	CRendererContext::RiObjectEnd(void) {
	if (CRenderer::netNumServers > 0)	return;

	CObject	*cObject;

	// Attach to the instanciated objects so that we don't loose them later
	for (cObject=instance->objects;cObject!=NULL;cObject=cObject->sibling)	cObject->attach();

	allocatedInstances->push(instance);
	instance	=	instanceStack->pop();
	xformEnd();
}


void	CRendererContext::RiObjectInstance(const void *handle) {
	if (CRenderer::netNumServers > 0)	return;

	addInstance(handle);
}

void	CRendererContext::RiMotionBeginV(int N,float times[]) {
	COptions *options =	getOptions(FALSE);

	int	i;
	
	numExpectedMotions	=	N;
	numMotions			=	0;
	keyTimes			=	new float[numExpectedMotions];
	for (i=0;i<numExpectedMotions;i++) {
		keyTimes[i]	=	times[i] + options->shutterOffset;
	}
}

void	CRendererContext::RiMotionEnd(void) {
	numExpectedMotions	=	1;
	delete [] keyTimes;
	keyTimes			=	NULL;
}

void	CRendererContext::RiMakeTextureV(const char *pic,const char *tex,const char *swrap,const char *twrap,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,const char *tokens[],const void *params[]) {
	COptions	*options;

	if (CRenderer::netClient != INVALID_SOCKET)	return;

	options	=	getOptions(FALSE);
	makeTexture(pic,tex,options->texturePath,swrap,twrap,filterfunc,swidth,twidth,n,tokens,params);
}

void	CRendererContext::RiMakeBumpV(const char *pic,const char *tex,const char *swrap,const char *twrap,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,const char *tokens[],const void *params[]) {
	COptions	*options;

	if (CRenderer::netClient != INVALID_SOCKET)	return;

	options	=	getOptions(FALSE);
	makeTexture(pic,tex,options->texturePath,swrap,twrap,filterfunc,swidth,twidth,n,tokens,params);
}

void	CRendererContext::RiMakeLatLongEnvironmentV(const char *pic,const char *tex,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,const char *tokens[],const void *params[]) {
	COptions	*options;

	if (CRenderer::netClient != INVALID_SOCKET)	return;

	options	=	getOptions(FALSE);
	makeCylindericalEnvironment(pic,tex,options->texturePath,RI_PERIODIC,RI_CLAMP,filterfunc,swidth,twidth,n,tokens,params);
}

void	CRendererContext::RiMakeCubeFaceEnvironmentV(const char *px,const char *nx,const char *py,const char *ny, const char *pz,const char *nz,const char *tex,float fov,float (*filterfunc)(float,float,float,float),float swidth,float twidth,int n,const char *tokens[],const void *params[]) {
	COptions	*options;

	if (CRenderer::netClient != INVALID_SOCKET)	return;

	options	=	getOptions(FALSE);
	makeCubicEnvironment(px,py,pz,nx,ny,nz,tex,RI_CLAMP,RI_CLAMP,options->texturePath,filterfunc,swidth,twidth,n,tokens,params,FALSE);
}


void	CRendererContext::RiMakeShadowV(const char *pic,const char *tex,int n,const char *tokens[],const void *params[]) {
	COptions	*options;

	if (CRenderer::netClient != INVALID_SOCKET)	return;

	options	=	getOptions(FALSE);
	makeSideEnvironment(pic,tex,options->texturePath,RI_CLAMP,RI_CLAMP,RiBoxFilter,1,1,n,tokens,params,TRUE);
}

void	CRendererContext::RiMakeBrickMapV(int nb,const char **src,const char *dest,int n,const char *tokens[],const void *params[]) {
	COptions	*options;

	if (CRenderer::netClient != INVALID_SOCKET)	return;

	options	=	getOptions(FALSE);
	makeBrickMap(nb,src,dest,options->texturePath,n,tokens,params);
}

void	CRendererContext::RiArchiveRecord(const char * type,const char *format,va_list args) {
	// We're not archiving
}

void	CRendererContext::RiReadArchiveV(const char *filename,void (*callback)(const char *,...),int n,const char *tokens[],const void *params[]) {
	char	tmp[OS_MAX_PATH_LENGTH];

	if ((filename[0] != '-') && (filename[0] != '|')) {
		COptions	*options	=	getOptions(FALSE);

		// Try locating the file
		if (CRenderer::locateFile(tmp,filename,options->archivePath)) {

			// Success, parse the file
			ribParse(tmp,callback);
		} else {
			error(CODE_BADFILE,"Failed to find \"%s\"\n",filename);
		}
	} else {
		ribParse(filename,callback);
	}
}

void	*CRendererContext::RiArchiveBeginV(const char *name,int n,const char *tokens[],const void *parms[]) {

	// Make sure we have the temporary directory created
	if (!osFileExists(CRenderer::temporaryPath))	osCreateDir(CRenderer::temporaryPath);

	char	fileName[OS_MAX_PATH_LENGTH];
	strcpy(fileName,CRenderer::temporaryPath);
	strcat(fileName,name);

	// Save the interface
	savedRenderMan	=	renderMan;
	renderMan		=	new CRibOut(fileName);

	return NULL;
}

void	CRendererContext::RiArchiveEnd(void) {
	savedRenderMan	=	NULL;
}
	
void	CRendererContext::RiResourceV(const char *handle,const char *type,int n,const char *tokens[],const void *parms[]) {
	
	// Check the parameters
	if (n == 0) {
		error(CODE_BADTOKEN,"Was expecting arguments with resource");
		return;
	}

	// Does PrMan support anything other than attribute ?
	if (strcmp(type,"attributes") != 0) {
		error(CODE_BADTOKEN,"Don't know how to handle this type\nPlease tell us know what this type means at the Pixie forums\n");
		return;
	}
	
	int			i;
	CVariable	tmp;
	CVariable	*cVariable;	
	int			save					=	FALSE;
	int			transform				=	TRUE;
	int			shading					=	TRUE;
	int			geometrymodification	=	TRUE;
	int			geometrydefinition		=	TRUE;
	int			hiding					=	TRUE;
	
	// Parse the parameter list
	for (i=0;i<n;i++) {

		// Get the variable
		cVariable	=	CRenderer::retrieveVariable(tokens[i]);
		
		// Parse if necessary
		if (cVariable == NULL) {
			parseVariable(&tmp,NULL,tokens[i]);
			cVariable = &tmp;
		}
		
		// Do we have something?
		if (cVariable != NULL) {
			if (strcmp(cVariable->name,"operation") == 0) {
				const char *operation = ((const char **) parms[i])[0];
				if (strcmp(operation,"save") == 0)			save	=	TRUE;
				else if (strcmp(operation,"restore") == 0)	save	=	FALSE;
				else {
					error(CODE_BADTOKEN,"Invalid operation for resource: %s\n",operation);
					return;
				}
			} else if (strcmp(cVariable->name,"subset") == 0) {
				// subset, so don't do anything by default
				transform				=	FALSE;
				shading					=	FALSE;
				geometrymodification	=	FALSE;
				geometrydefinition		=	FALSE;
				hiding					=	FALSE;

				const char *subset = ((const char **)parms[i])[0];
				
				if (strcmp(subset,"shading") == 0)						shading					=	TRUE;
				else if (strcmp(subset,"geometrymodification") == 0)	geometrymodification	=	TRUE;
				else if (strcmp(subset,"geometrydefinition") == 0)		geometrydefinition		=	TRUE;
				else if (strcmp(subset,"hiding") == 0)					hiding					=	TRUE;
				else if (strcmp(subset,"transform") == 0)				transform				=	TRUE;
				else if (strcmp(subset,"all") == 0) {
					transform				=	TRUE;
					shading					=	TRUE;
					geometrymodification	=	TRUE;
					geometrydefinition		=	TRUE;
					hiding					=	TRUE;
				}
				else {
					error(CODE_BADTOKEN,"Invalid subset for resource: %s\n",subset);
					return;
				}
			} else {
				error(CODE_BADTOKEN,"Unrecognized parameter in resource: %s\n",(const char *) tokens[i]);
				return;
			}
		} else {
			error(CODE_BADTOKEN,"Unrecognized parameter in resource: %s\n",(const char *) tokens[i]);
			return;
		}
	}
	
	// Are we saving ?
	if (save) {
		CResource	*nResource	=	new CResource(handle,currentAttributes,currentXform);
		
		nResource->next	=	currentResource;
		currentResource	=	nResource;
	} else {
		CResource	*cResource	=	NULL;
		int			i;
		
		// Remporarily push the current resource list into the stack to make our life easier
		savedResources->push(currentResource);
		
		// Search the saved resources for the handle we're looking for
		for (i=savedResources->numItems;i>0;i--) {
			for (cResource=savedResources->array[i-1];cResource!=NULL;cResource=cResource->next) {
			
				// Did we find a match ?
				if (strcmp(cResource->name,handle) == 0)	break;
			}
			
			if (cResource != NULL)	break;
		}
		savedResources->pop();
		
		if (cResource == NULL) error(CODE_NOTATTRIBS,"Named resource \"%s\" not found\n",handle);
		else {

			if (shading | geometrymodification | geometrydefinition | hiding) {
				CAttributes	*cAttributes;

				cAttributes	=	getAttributes(FALSE);
				cAttributes->restore(cResource->attributes,shading,geometrymodification,geometrydefinition,hiding);
			}

			if (transform) {
				CXform		*cXform;

				cXform		=	getXform(FALSE);
				cXform->restore(cResource->xform);
			}
		}
	}
}

void	CRendererContext::RiResourceBegin(void) {

	// Save the resources
	savedResources->push(currentResource);
}

void	CRendererContext::RiResourceEnd(void) {
	
	// Delete the resources
	CResource	*cResource;
	while((cResource = currentResource) != NULL) {
		currentResource	=	currentResource->next;
		delete cResource;
	}
	
	// Restore the resources
	currentResource	=	savedResources->pop();
}

void	CRendererContext::RiIfBeginV(const char *expr,int n,const char *tokens[],const void *parms[]) {

	if (riExecTag == 0) {
		if (ifParse(expr)) {
			// We're executing ...
		} else {
			ignoreCommand	=	TRUE;
			riExecTag++;
		}
	} else {
		assert(ignoreCommand == TRUE);
		riExecTag++;
	}
}

void	CRendererContext::RiElseIfV(const char *expr,int n,const char *tokens[],const void *parms[]) {
	
	if (riExecTag == 0) {
		ignoreCommand	=	TRUE;
		riExecTag++;
	} else if (riExecTag == 1) {
		if (ifParse(expr)) {
			// We're executing
			riExecTag--;
			ignoreCommand	=	FALSE;
		} else {
			// We're already ignoring
			assert(ignoreCommand == TRUE);
		}
	} else {
		// We're already ignoring
		assert(ignoreCommand == TRUE);
	}
}

void	CRendererContext::RiElse(void) {
	if (riExecTag == 0) {
		ignoreCommand	=	TRUE;
		riExecTag++;
	} else if (riExecTag == 1) {
		riExecTag--;
		ignoreCommand	=	FALSE;
	} else {
		// We're already ignoring
		assert(ignoreCommand == TRUE);
	}
}

void	CRendererContext::RiIfEnd(void) {
	if (riExecTag == 0) {
	} else {
		riExecTag--;
		if (riExecTag == 0)	ignoreCommand	=	FALSE;
	}
}

void	CRendererContext::RiError(int code,int severity,const char *mes) {
	char		*tmp		=	NULL;
	CAttributes	*attributes	=	NULL;

	if (CRenderer::offendingObject != NULL) {
		attributes	=	CRenderer::offendingObject->attributes;
	}

	if (attributes == NULL)	attributes	=	currentAttributes;

	int len = strlen(mes)+1;                // '\0'
	if (severity != RIE_INFO && ribFile)
		len += strlen(ribFile)+11;          // ' (999999): '
	if (attributes && attributes->name)
		len += strlen(attributes->name)+3;  // '() '
	tmp = (char*)malloc(len);
	tmp[0] = '\0';

	if (severity != RIE_INFO && ribFile)    
		sprintf(tmp,"%s (%d): ",ribFile,ribCommandLineno);

	if (attributes && attributes->name) {
		strcat(tmp,"(");
		strcat(tmp,attributes->name);
		strcat(tmp,") ");
	}

	strcat(tmp,mes);

	// Log the file
	if (code == RIE_LOG) {
		if ((currentOptions != NULL) && (currentOptions->filelog != NULL)) {
			FILE	*out	=	fopen(currentOptions->filelog,"a");

			if (out != NULL) {
				fprintf(out,tmp);

				fclose(out);
			}
		}
	} else {
		if (errorHandler != NULL) {
			errorHandler(code,severity,tmp);
		}
	}
	free(tmp);
}


