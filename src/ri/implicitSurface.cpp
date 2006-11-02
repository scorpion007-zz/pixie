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

///////////////////////////////////////////////////////////////////////
// Class				:	CImplicit
// Method				:	CImplicit
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	11/7/2003
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
			error(CODE_BADFILE,"Implicit file %s is missing some functions\n",name);
			osUnloadModule(handle);
			handle			=	NULL;
		} else {
			data			=	initFunction(frame,bmin,bmax);

			if (data != NULL) {
				movvv(cameraBmin,bmin);
				movvv(cameraBmax,bmax);
				xform->transformBound(cameraBmin,cameraBmax);
				stepSize			=	ss;
			} else {
				error(CODE_BADFILE,"Implicit %s failed to initialise\n",name);
				osUnloadModule(handle);
				handle			=	NULL;
			}
		}
	} else {
		error(CODE_BADFILE,"Unable to load implicit %s (%s)\n",name,osModuleError());
	}

	scaleFactor				=	(float) pow((double) fabs(determinantm(xform->from)),1 / 3.0)*sf*(float) 0.5;

	stats.numGprims++;
	stats.gprimMemory		+=	sizeof(CImplicit);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CImplicit
// Method				:	~CImplicit
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	11/7/2003
CImplicit::~CImplicit() {
	stats.numGprims--;
	stats.gprimMemory		-=	sizeof(CImplicit);

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
// Date last edited		:	11/7/2003
void				CImplicit::intersect(CRay *ray,int &) {
	float	tmin,tmax;
	vector	lastP,P;
	float	lastF,F;
	vector	lastdF,dF;

	double	lastT,t,dt;

	// Do the freaking ray martching
	if (! (ray->flags & attributes->flags) )	return;
	
	if (attributes->flags & ATTRIBUTES_FLAGS_LOD) {
		float importance = attributes->lodImportance;
		if (ray->jimp < 0) ray->jimp = urand();
		if (importance >= 0) {
			if (ray->jimp > importance)			return;
		} else {
			if ((1-ray->jimp) >= -importance)	return;
		}
	}

	if (handle == NULL)	return;

	if (dotvv(ray->dir,ray->dir) < 0)	return;

	// Transform to object space
	if (ray->lastXform != xform) {
		if (xform->next != NULL) {
			vector	tmp[4];
			vector	to;
			addvv(to,ray->from,ray->dir);

			mulmp(tmp[0],xform->to,ray->from);
			mulmp(tmp[1],xform->to,to);

			mulmp(tmp[2],xform->next->to,ray->from);
			mulmp(tmp[3],xform->next->to,to);

			interpolatev(ray->oFrom,tmp[0],tmp[2],ray->time);
			interpolatev(ray->oTo,tmp[1],tmp[3],ray->time);
			subvv(ray->oDir,ray->oTo,ray->oFrom);
		} else {
			vector	to;
			addvv(to,ray->from,ray->dir);

			mulmp(ray->oFrom,xform->to,ray->from);
			mulmp(ray->oTo,xform->to,to);
			subvv(ray->oDir,ray->oTo,ray->oFrom);
		}

		ray->lastXform	=	xform;
	}

	tmin	=	ray->tmin;
	tmax	=	ray->t;

	// Find an intersection if any
	if (hierarchyIntersectBox(bmin,bmax,ray->oFrom,ray->oTo,tmin,tmax)) {
		lastT		=	tmin;
		lastP[0]	=	(float) (ray->oFrom[0] + ray->oDir[0]*lastT);
		lastP[1]	=	(float) (ray->oFrom[1] + ray->oDir[1]*lastT);
		lastP[2]	=	(float) (ray->oFrom[2] + ray->oDir[2]*lastT);
		lastF		=	evalFunction(lastdF,data,lastP,ray->time);		

		dt			=	(float) fabs(lastF)*scaleFactor;

martchLoop:;
		t			=	lastT + dt;
		if (t > tmax)	return;

		P[0]		=	(float) (ray->oFrom[0] + ray->oDir[0]*t);
		P[1]		=	(float) (ray->oFrom[1] + ray->oDir[1]*t);
		P[2]		=	(float) (ray->oFrom[2] + ray->oDir[2]*t);
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
// Method				:	intersect
// Description			:	Intersect the object with a box
// Return Value			:	-
// Comments				:
// Date last edited		:	11/7/2003
int						CImplicit::intersect(const float *bmin,const float *bmax) const {
	return intersectBox(bmin,bmax,cameraBmin,cameraBmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CImplicit
// Method				:	bound
// Description			:	Bound the surface
// Return Value			:	-
// Comments				:
// Date last edited		:	11/7/2003
void					CImplicit::bound(float *bmin,float *bmax) const {
	movvv(bmin,cameraBmin);
	movvv(bmax,cameraBmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CImplicit
// Method				:	sample
// Description			:	Sample the surface
// Return Value			:	-
// Comments				:
// Date last edited		:	11/7/2003
void					CImplicit::sample(int,int,float **,unsigned int &up) const {
	up	&=	~(PARAMETER_P | PARAMETER_NG);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CImplicit
// Method				:	interpolate
// Description			:	Interpolate the surface
// Return Value			:	-
// Comments				:
// Date last edited		:	11/7/2003
void					CImplicit::interpolate(int,float **)	const {
}

///////////////////////////////////////////////////////////////////////
// Class				:	CImplicit
// Method				:	tesselate
// Description			:	Tesselate the surface
// Return Value			:	-
// Comments				:
// Date last edited		:	11/7/2003
void					CImplicit::tesselate(CShadingContext *context) {
	context->addTracable(this,this);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CImplicit
// Method				:	dice
// Description			:	Dice the surface for scan-line rendering
// Return Value			:	-
// Comments				:
// Date last edited		:	11/7/2003
void					CImplicit::dice(CShadingContext *) {
}


///////////////////////////////////////////////////////////////////////
// Class				:	CImplicit
// Method				:	copy
// Description			:	Create a copy
// Return Value			:	-
// Comments				:
// Date last edited		:	11/7/2003
void					CImplicit::copy(CAttributes *a,CXform *x,CRendererContext *context) const {
}


///////////////////////////////////////////////////////////////////////
// Class				:	CImplicit
// Method				:	shade
// Description			:	Shade the surface
// Return Value			:	-
// Comments				:
// Date last edited		:	11/7/2003
void					CImplicit::shade(CShadingContext *context,int numRays,CRay **rays) {
	float	**varying	=	context->currentShadingState->varying;
	float	*P			=	varying[VARIABLE_P];
	float	*N			=	varying[VARIABLE_NG];
	float	*from		=	varying[VARIABLE_I];
	int		i;

	for (i=numRays;i>0;i--) {
		const CRay	*cRay	=	*rays++;

		P[0]			=	cRay->from[0] + cRay->dir[0]*cRay->t;
		P[1]			=	cRay->from[1] + cRay->dir[1]*cRay->t;
		P[2]			=	cRay->from[2] + cRay->dir[2]*cRay->t;
		movvv(N,cRay->N);
		movvv(from,cRay->from);

		P				+=	3;
		N				+=	3;
		from			+=	3;
	}

	if (xform->flip) {
		float	*N			=	varying[VARIABLE_NG];

		for (i=numRays;i>0;i--) {
			mulvf(N,-1);
			N			+=	3;
		}

	}

	context->shade(this,numRays,1,-1,0);
}
