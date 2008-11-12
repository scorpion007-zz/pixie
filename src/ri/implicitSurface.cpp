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
//  File				:	implicitSurface.cpp
//  Classes				:	CImplicit
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "implicitSurface.h"
#include "error.h"
#include "stats.h"
#include "shading.h"
#include "renderer.h"
#include "objectMisc.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CImplicit
// Method				:	CImplicit
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CImplicit::CImplicit(CAttributes *a,CXform *x,int frame,const char *name,float ss,float sf) : CSurface(a,x) {
	handle	=	osLoadModule(name);

	if (handle != NULL) {
		initFunction		=	(implicitInitFunction)			osResolve(handle,"implicitInit");
		evalFunction		=	(implicitEvalFunction)			osResolve(handle,"implicitEval");
		evalNormalFunction	=	(implicitEvalNormalFunction)	osResolve(handle,"implicitEvalNormal");
		tiniFunction		=	(implicitTiniFunction)			osResolve(handle,"implicitTini");

		if (	(initFunction	==	NULL)	||
				(evalFunction	==	NULL)	||
				(tiniFunction	==	NULL)	) {
			error(CODE_BADFILE,"Implicit file \"%s\" is missing some functions\n",name);
			osUnloadModule(handle);
			handle			=	NULL;
		} else {
			data			=	initFunction(frame,bmin,bmax);

			if (data != NULL) {
				xform->transformBound(bmin,bmax);
				stepSize			=	ss;
			} else {
				error(CODE_BADFILE,"Implicit \"%s\" failed to initialize\n",name);
				osUnloadModule(handle);
				handle			=	NULL;
			}
		}
	} else {
		error(CODE_BADFILE,"Failed to load implicit \"%s\": %s\n",name,osModuleError());
	}

	scaleFactor				=	(float) pow((double) fabs(determinantm(xform->from)),1 / 3.0)*sf*(float) 0.5;

	atomicIncrement(&stats.numGprims);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CImplicit
// Method				:	~CImplicit
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CImplicit::~CImplicit() {
	atomicDecrement(&stats.numGprims);

	if (handle != NULL) {
		tiniFunction(data);
		osUnloadModule(handle);
	}
}
	


///////////////////////////////////////////////////////////////////////
// Class				:	CImplicit
// Method				:	intersect
// Description			:	Intersect the surface with the ray
// Return Value			:	-
// Comments				:
void					CImplicit::intersect(CShadingContext *context,CRay *ray) {
	float	tmin,tmax;
	vector	lastP,P;
	float	lastF,F;
	vector	lastdF,dF;

	double	lastT,t,dt;

	// Do the freaking ray martching
	if (! (ray->flags & attributes->flags) )	return;
	
	if (attributes->flags & ATTRIBUTES_FLAGS_LOD) {
		const float importance = attributes->lodImportance;
		if (importance >= 0) {
			if (ray->jimp > importance)			return;
		} else {
			if ((1-ray->jimp) >= -importance)	return;
		}
	}

	if (handle == NULL)	return;

	if (dotvv(ray->dir,ray->dir) < 0)	return;

	tmin	=	ray->tmin;
	tmax	=	ray->t;

	// Find an intersection if any
	if (intersectBox(bmin,bmax,ray->from,ray->dir,ray->invDir,tmin,tmax)) {
		lastT		=	tmin;
		lastP[0]	=	(float) (ray->from[0] + ray->dir[0]*lastT);
		lastP[1]	=	(float) (ray->from[1] + ray->dir[1]*lastT);
		lastP[2]	=	(float) (ray->from[2] + ray->dir[2]*lastT);
		lastF		=	evalFunction(lastdF,data,lastP,ray->time);		

		dt			=	(float) fabs(lastF)*scaleFactor;

martchLoop:;
		t			=	lastT + dt;
		if (t > tmax)	return;

		P[0]		=	(float) (ray->from[0] + ray->dir[0]*t);
		P[1]		=	(float) (ray->from[1] + ray->dir[1]*t);
		P[2]		=	(float) (ray->from[2] + ray->dir[2]*t);
		assert(dotvv(P,P) >= 0);
		F			=	evalFunction(dF,data,P,ray->time);

		if ((lastF*F < 0) && (dt > C_EPSILON)) {		// Did we step through the object ?
			dt		*=	0.5f;

			goto martchLoop;
		} else if (dt > C_EPSILON) {					// Are we still going ?
			dt		=	absf(F)*scaleFactor;

			movvv(lastP,P);
			movvv(lastdF,dF);
			lastT	=	t;
			lastF	=	F;

			goto martchLoop;
		} else {
			// We found an intersection
			ray->object	=	this;
			if (evalNormalFunction != NULL) evalNormalFunction(dF,data,P,ray->time);
			mulmn(ray->N,xform->to,dF);
			ray->t	=	(float) t;
			return;
		}
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CImplicit
// Method				:	sample
// Description			:	Sample the surface
// Return Value			:	-
// Comments				:
void					CImplicit::sample(int,int,float **,float ***,unsigned int &up) const {
	up	&=	~(PARAMETER_P | PARAMETER_NG);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CImplicit
// Method				:	interpolate
// Description			:	Interpolate the surface
// Return Value			:	-
// Comments				:
void					CImplicit::interpolate(int,float **,float ***)	const {
}

///////////////////////////////////////////////////////////////////////
// Class				:	CImplicit
// Method				:	dice
// Description			:	Dice the surface for scan-line rendering
// Return Value			:	-
// Comments				:
void					CImplicit::dice(CShadingContext *) {
}

///////////////////////////////////////////////////////////////////////
// Class				:	CImplicit
// Method				:	instantiate
// Description			:	Create a copy
// Return Value			:	-
// Comments				:
void					CImplicit::instantiate(CAttributes *a,CXform *x,CRendererContext *context) const {
}


///////////////////////////////////////////////////////////////////////
// Class				:	CImplicit
// Method				:	shade
// Description			:	Shade the surface
// Return Value			:	-
// Comments				:
void					CImplicit::shade(CShadingContext *context,int numRays,CRay **rays) {
	float	**varying	=	context->currentShadingState->varying;
	float	*P			=	varying[VARIABLE_P];
	float	*N			=	varying[VARIABLE_NG];
	float	*I			=	varying[VARIABLE_I];
	int		i;

	for (i=numRays;i>0;i--) {
		const CRay	*cRay	=	*rays++;

		P[0]			=	cRay->from[0] + cRay->dir[0]*cRay->t;
		P[1]			=	cRay->from[1] + cRay->dir[1]*cRay->t;
		P[2]			=	cRay->from[2] + cRay->dir[2]*cRay->t;
		movvv(N,cRay->N);
		subvv(I,P,cRay->from);

		P				+=	3;
		N				+=	3;
		I				+=	3;
	}

	if (xform->flip) {
		float	*N			=	varying[VARIABLE_NG];

		for (i=numRays;i>0;i--) {
			mulvf(N,-1);
			N			+=	3;
		}

	}

	context->shade(this,numRays,1,SHADING_0D,0);
}

