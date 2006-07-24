//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright � 1999 - 2003, Okan Arikan
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
//  File				:	hcshader.cpp
//  Classes				:	-
//  Description			:	This file holds the hardcoded shaders
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "common/os.h"
#include "hcshader.h"
#include "shading.h"
#include "memory.h"
#include "attributes.h"
#include "hierarchy.h"
#include "object.h"


///////////////////////////////////////////////////////////////////////
// Class				:	CSphereLight
// Method				:	CSphereLight
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	11/2/2003
CSphereLight::CSphereLight(CAttributes *a,CXform *x) : CShaderInstance(a,x) {
	vector	P;

	initv(P,0,0,0);
	mulmp(from,xform->from,P);
	initv(lightColor,1,1,1);
	intensity	=	1;
	radius		=	0;
	numSamples	=	1;
	flags		=	SHADERFLAGS_NONAMBIENT;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSphereLight
// Method				:	~CSphereLight
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	11/2/2003
CSphereLight::~CSphereLight() {
}


///////////////////////////////////////////////////////////////////////
// Class				:	CSphereLight
// Method				:	illuminate
// Description			:	Called chen we need to illuminate a point
// Return Value			:	-
// Comments				:
// Date last edited		:	11/2/2003
void					CSphereLight::illuminate(CShadingContext *context) {
	CShadingState	*currentShadingState	=	context->currentShadingState;
	
	if (context->hiderFlags & HIDER_ILLUMINATIONHOOK) {
		const int	numVertices	=	currentShadingState->numVertices;
		float		*Pf			=	(float *) alloca(numVertices*3*sizeof(float));
		float		*Nf			=	(float *) alloca(numVertices*3*sizeof(float));
		float		*thetaf		=	(float *) alloca(numVertices*sizeof(float));
		int			i;
		float		*cP			=	Pf;
		float		*cN			=	Nf;
		float		*L;
		float		*CL;

		// Generate points on the surface
		for (i=numVertices;i>0;i--,cP+=3,cN+=3) {
			sampleSphere(cP);
			normalizev(cP);
			movvv(cN,cP);
			mulvf(cP,radius);
			addvv(cP,from);
		}

		// Call the hook handle
		context->illuminateBegin(Pf,Nf,thetaf);

		// Compute the intensity
		L			=	currentShadingState->varying[VARIABLE_L];
		CL			=	currentShadingState->varying[VARIABLE_CL];
		for (i=numVertices;i>0;i--,L+=3,CL+=3,Nf+=3) {
			// The L must be unit vector
			assert((dotvv(L,L) - 1)*(dotvv(L,L) - 1) < 0.00001);
			assert(dotvv(Nf,L) >= 0);

			mulvf(CL,lightColor,intensity);
			mulvf(CL,dotvv(Nf,L));
		}

		// Call the hook handle
		context->illuminateEnd();
	} else {
		CShadedLight	**lights				=	&currentShadingState->lights;
		const int		*tags					=	currentShadingState->tags;
		float			*Ps						=	currentShadingState->varying[VARIABLE_PS];
		CHierarchy		*hierarchy				=	context->hierarchy;
		int				j;
		CRay			ray;
		const float		bias					=	currentShadingState->currentObject->attributes->shadowBias;
		int				numVertices				=	currentShadingState->numRealVertices;
		CShadedLight	*cLight;
		float			*L,*Cl;
		
		if (currentShadingState->numActive == 0)
			return;
		
		cLight						=	(CShadedLight*) ralloc(sizeof(CShadedLight));
		cLight->lightTags			=	(int*)			ralloc(sizeof(int)*numVertices);
		cLight->savedState			=	(float**)		ralloc(2*sizeof(float*));
		cLight->savedState[0]		=	(float*)		ralloc(3*sizeof(float)*numVertices);
		cLight->savedState[1]		=	(float*)		ralloc(3*sizeof(float)*numVertices);
		cLight->instance			=	this;
		cLight->next				=	*lights;
		*lights						=	cLight;
		memcpy(cLight->lightTags,tags,sizeof(int)*numVertices);
		L							=	cLight->savedState[0];
		Cl							=	cLight->savedState[1];

		for (int i=numVertices;i>0;i--,Ps+=3){
			if (*tags++ == 0) {
				vector			P;
				float			visibility	=	0;
				
				for (j=numSamples;j>0;j--) {
					sampleSphere(P);
					normalizev(P);
					mulvf(P,radius);
					addvv(P,from);

					// Evaluate visibility between P and Ps
					movvv(ray.from,Ps);
					movvv(ray.to,P);
					subvv(ray.dir,P,Ps);
					const float	len	=	lengthv(ray.dir);
					mulvf(ray.dir,1 / len);

					ray.flags				=	ATTRIBUTES_FLAGS_TRANSMISSION_VISIBLE;
					ray.tmin				=	bias;
					ray.invDir[COMP_X]		=	1/ray.dir[COMP_X];
					ray.invDir[COMP_Y]		=	1/ray.dir[COMP_Y];
					ray.invDir[COMP_Z]		=	1/ray.dir[COMP_Z];
					ray.t					=	len - bias;
					ray.time				=	0;
					ray.jimp				=	-1.0f;
					ray.lastXform			=	NULL;
					ray.object				=	NULL;

					hierarchy->intersect(&ray);

					if (ray.object == NULL) {
						subvv(P,Ps);
						visibility	+=	intensity / dotvv(P,P);
					}
				}

				visibility	/=	(float) numSamples;

				subvv(L,from,Ps);
				normalizev(L);
				mulvf(Cl,lightColor,visibility);
			}
			L	+=	3;
			Cl	+=	3;
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSphereLight
// Method				:	setParameters
// Description			:	Set shader parameters
// Return Value			:	-
// Comments				:
// Date last edited		:	11/2/2003
void					CSphereLight::setParameters(int n,char **params,void **vals) {
	int	i;

	for (i=0;i<n;i++) {
		if (strcmp(params[i],"from") == 0) {
			const float	*val	=	(const float *) vals[i];

			mulmp(from,xform->from,val);
		} else if (strcmp(params[i],"radius") == 0) {
			const float	*val	=	(const float *) vals[i];

			radius	=	val[0]*powf(determinantm(xform->from),1.0f / 3.0f);
		} else if (strcmp(params[i],"lightcolor") == 0) {
			const float	*val	=	(const float *) vals[i];

			movvv(lightColor,val);
		} else if (strcmp(params[i],"intensity") == 0) {
			const float	*val	=	(const float *) vals[i];

			intensity	=	val[0];
		} else if (strcmp(params[i],"numSamples") == 0) {
			const float	*val	=	(const float *) vals[i];

			numSamples	=	(int) val[0];
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSphereLight
// Method				:	getParameter
// Description			:	Query a shader parameter
// Return Value			:	-
// Comments				:
// Date last edited		:	11/2/2003
int						CSphereLight::getParameter(const char *param,void *val,CVariable**,int*) {
	if (strcmp(param,"from") == 0) {
		float	*cval	=	(float *) val;

		movvv(cval,from);
		return TRUE;
	} else if (strcmp(param,"radius") == 0) {
		float	*cval	=	(float *) val;

		cval[0]	=	radius;
		return TRUE;
	} else if (strcmp(param,"lightcolor") == 0) {
		float	*cval	=	(float *) val;

		movvv(cval,lightColor);
		return TRUE;
	} else if (strcmp(param,"intensity") == 0) {
		float	*cval	=	(float *) val;

		cval[0]	=	intensity;
		return TRUE;
	} else if (strcmp(param,"numSamples") == 0) {
		float	*cval	=	(float *) val;

		cval[0]	=	(float) numSamples;
		return TRUE;
	}

	return FALSE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSphereLight
// Method				:	execute
// Description			:	Execute the shader
// Return Value			:	-
// Comments				:	Should never be called
// Date last edited		:	11/2/2003
void					CSphereLight::execute(CShadingContext *context) {
	// Should never be called
	assert(FALSE);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSphereLight
// Method				:	requiredParameters
// Description			:	Get the required parameters
// Return Value			:	-
// Comments				:
// Date last edited		:	11/2/2003
unsigned int			CSphereLight::requiredParameters() {
	return 0;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSphereLight
// Method				:	getName
// Description			:	Get the name of the shader
// Return Value			:	-
// Comments				:
// Date last edited		:	11/2/2003
const char				*CSphereLight::getName() {
	return "spherelight";
}
























///////////////////////////////////////////////////////////////////////
// Class				:	CQuadLight
// Method				:	CQuadLight
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	11/2/2003
CQuadLight::CQuadLight(CAttributes *a,CXform *x) : CShaderInstance(a,x) {
	vector	P;
	vector	D0,D1;

	initv(P,-1,-1,0);
	mulmp(corners[0],xform->from,P);
	initv(P,1,-1,0);
	mulmp(corners[1],xform->from,P);
	initv(P,-1,1,0);
	mulmp(corners[2],xform->from,P);
	initv(P,1,1,0);
	mulmp(corners[3],xform->from,P);

	initv(lightColor,1,1,1);
	intensity	=	1;
	numSamples	=	1;
	reverse		=	(a->flags & ATTRIBUTES_FLAGS_INSIDE);
	flags		=	SHADERFLAGS_NONAMBIENT;
	
	subvv(D0,corners[1],corners[0]);
	subvv(D1,corners[2],corners[0]);
	crossvv(N,D0,D1);
	normalizev(N);

	if (reverse)	mulvf(N,-1);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CQuadLight
// Method				:	~CQuadLight
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	11/2/2003
CQuadLight::~CQuadLight() {
}


///////////////////////////////////////////////////////////////////////
// Class				:	CQuadLight
// Method				:	illuminate
// Description			:	Called chen we need to illuminate a point
// Return Value			:	-
// Comments				:
// Date last edited		:	11/2/2003
void					CQuadLight::illuminate(CShadingContext *context) {
	CShadingState	*currentShadingState	=	context->currentShadingState;

	if (context->hiderFlags & HIDER_ILLUMINATIONHOOK) {
		const int	numVertices	=	currentShadingState->numVertices;
		float		*Pf			=	(float *) alloca(numVertices*3*sizeof(float));
		float		*Nf			=	(float *) alloca(numVertices*3*sizeof(float));
		float		*thetaf		=	(float *) alloca(numVertices*sizeof(float));
		int			i;
		float		*cP			=	Pf;
		float		*cN			=	Nf;
		float		*cTheta		=	thetaf;
		float		*L;
		float		*CL;

		// Generate points on the surface
		for (i=numVertices;i>0;i--,cP+=3,cN+=3) {
			vector			P0,P1;
			const float		u	=	urand();
			const float		v	=	urand();

			interpolatev(P0,corners[0],corners[1],u);
			interpolatev(P1,corners[2],corners[3],u);
			interpolatev(cP,P0,P1,v);

			movvv(cN,N);

			*cTheta++	=	(float) (C_PI / 2.0);
		}

		// Call the hook handle
		context->illuminateBegin(Pf,Nf,thetaf);

		// Compute the intensity
		L			=	currentShadingState->varying[VARIABLE_L];
		CL			=	currentShadingState->varying[VARIABLE_CL];
		for (i=numVertices;i>0;i--,L+=3,CL+=3) {
			// The L must be unit vector
			assert((dotvv(L,L) - 1)*(dotvv(L,L) - 1) < 0.00001);
			assert(dotvv(N,L) >= 0);

			mulvf(CL,lightColor,intensity);
			mulvf(CL,dotvv(N,L));
		}

		// Call the hook handle
		context->illuminateEnd();
	} else {
		CShadedLight	**lights				=	&currentShadingState->lights;
		CShadedLight	**freeLights			=	&currentShadingState->freeLights;
		const int		*tags					=	currentShadingState->tags;
		float			*Ps						=	currentShadingState->varying[VARIABLE_PS];
		CRay			ray;
		CHierarchy		*hierarchy				=	context->hierarchy;
		const float		bias					=	currentShadingState->currentObject->attributes->shadowBias;
		vector			D;
		int				j;
		vector			center;
		int				numVertices				=	currentShadingState->numRealVertices;
		int				numLitPoints			=	0;
		CShadedLight	*cLight;
		int				*lightTags;
		float			*L,*Cl;
		
		if (currentShadingState->numActive == 0)
			return;
		
		cLight						=	(CShadedLight*) ralloc(sizeof(CShadedLight));
		cLight->lightTags			=	(int*)			ralloc(sizeof(int)*numVertices);
		cLight->savedState			=	(float**)		ralloc(2*sizeof(float*));
		cLight->savedState[0]		=	(float*)		ralloc(3*sizeof(float)*numVertices);
		cLight->savedState[1]		=	(float*)		ralloc(3*sizeof(float)*numVertices);
		cLight->instance			=	this;
		memcpy(cLight->lightTags,tags,sizeof(int)*numVertices);
		L							=	cLight->savedState[0];
		Cl							=	cLight->savedState[1];
		
		// GSHTODO: do something to check Ps vs N angle before allocating light
		
		addvv(center,corners[0],corners[1]);
		addvv(center,corners[2]);
		addvv(center,corners[3]);
		mulvf(center,1 / (float) 4);
		
		lightTags = cLight->lightTags;
		for (int i=currentShadingState->numRealVertices;i>0;i--,Ps+=3) {
			if (*lightTags == 0) {
				subvv(D,Ps,center);
				if (dotvv(D,N) > 0) {
					vector			P,P0,P1;
					float			visibility	=	0;

					for (j=numSamples;j>0;j--) {
						const float	u	=	urand();
						const float	v	=	urand();

						interpolatev(P0,corners[0],corners[1],u);
						interpolatev(P1,corners[2],corners[3],u);
						interpolatev(P,P0,P1,v);
						
						// Evaluate visibility between P and Ps
						movvv(ray.from,Ps);
						movvv(ray.to,P);
						subvv(ray.dir,P,Ps);
						const float	len	=	lengthv(ray.dir);
						mulvf(ray.dir,1 / len);

						ray.flags				=	ATTRIBUTES_FLAGS_TRANSMISSION_VISIBLE;
						ray.tmin				=	bias;
						ray.invDir[COMP_X]		=	1/ray.dir[COMP_X];
						ray.invDir[COMP_Y]		=	1/ray.dir[COMP_Y];
						ray.invDir[COMP_Z]		=	1/ray.dir[COMP_Z];
						ray.t					=	len - bias;
						ray.time				=	0;
						ray.jimp				=	-1.0f;
						ray.lastXform			=	NULL;
						ray.object				=	NULL;

						hierarchy->intersect(&ray);

						if (ray.object == NULL) {
							visibility++;
						}
					}

					visibility			/=	(float) numSamples;
					subvv(L,center,Ps);
					visibility			/=	dotvv(L,L);
					normalizev(L);
					visibility			*=	-dotvv(N,L)*intensity;
					mulvf(Cl,lightColor,visibility);
					numLitPoints++;
				} else {
					(*lightTags)++;
				}
				lightTags++;
				L	+=	3;
				Cl	+=	3;
			}
		}
		
		if (numLitPoints > 0) {
			// Only save the light if it has active points
			cLight->next				=	*lights;
			*lights						=	cLight;
		} else {
			// Otherwise put it on the free list
			cLight->next				=	*freeLights;
			*freeLights					=	cLight;
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CQuadLight
// Method				:	setParameters
// Description			:	Set shader parameters
// Return Value			:	-
// Comments				:
// Date last edited		:	11/2/2003
void					CQuadLight::setParameters(int n,char **params,void **vals) {
	int	i;

	for (i=0;i<n;i++) {
		if (strcmp(params[i],"P0") == 0) {
			const float	*val	=	(const float *) vals[i];

			mulmp(corners[0],xform->from,val);
		} else if (strcmp(params[i],"P1") == 0) {
			const float	*val	=	(const float *) vals[i];

			mulmp(corners[1],xform->from,val);
		} else if (strcmp(params[i],"P2") == 0) {
			const float	*val	=	(const float *) vals[i];

			mulmp(corners[2],xform->from,val);
		} else if (strcmp(params[i],"P3") == 0) {
			const float	*val	=	(const float *) vals[i];

			mulmp(corners[3],xform->from,val);
		} else if (strcmp(params[i],"direction") == 0) {
			const float	*val	=	(const float *) vals[i];

			mulmn(N,xform->to,val);
		} else if (strcmp(params[i],"lightcolor") == 0) {
			const float	*val	=	(const float *) vals[i];

			movvv(lightColor,val);
		} else if (strcmp(params[i],"intensity") == 0) {
			const float	*val	=	(const float *) vals[i];

			intensity	=	val[0];
		} else if (strcmp(params[i],"numSamples") == 0) {
			const float	*val	=	(const float *) vals[i];

			numSamples	=	(int) val[0];
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CQuadLight
// Method				:	getParameter
// Description			:	Query a shader parameter
// Return Value			:	-
// Comments				:
// Date last edited		:	11/2/2003
int						CQuadLight::getParameter(const char *param,void *val,CVariable**,int*) {
	if (strcmp(param,"P0") == 0) {
		float	*cval	=	(float *) val;

		movvv(cval,corners[0]);
		return TRUE;
	} else if (strcmp(param,"P1") == 0) {
		float	*cval	=	(float *) val;

		movvv(cval,corners[1]);
		return TRUE;
	} else if (strcmp(param,"P2") == 0) {
		float	*cval	=	(float *) val;

		movvv(cval,corners[1]);
		return TRUE;
	} else if (strcmp(param,"P3") == 0) {
		float	*cval	=	(float *) val;

		movvv(cval,corners[1]);
		return TRUE;
	} else if (strcmp(param,"direction") == 0) {
		float	*cval	=	(float *) val;

		movvv(cval,N);
		return TRUE;
	} else if (strcmp(param,"lightColor") == 0) {
		float	*cval	=	(float *) val;

		movvv(cval,lightColor);
		return TRUE;
	} else if (strcmp(param,"intensity") == 0) {
		float	*cval	=	(float *) val;

		cval[0]	=	intensity;
		return TRUE;
	} else if (strcmp(param,"numSamples") == 0) {
		float	*cval	=	(float *) val;

		cval[0]	=	(float) numSamples;
		return TRUE;
	}

	return FALSE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CQuadLight
// Method				:	execute
// Description			:	Execute the shader
// Return Value			:	-
// Comments				:	Should never be called
// Date last edited		:	11/2/2003
void					CQuadLight::execute(CShadingContext *context) {
	// Should never be called
	assert(FALSE);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CQuadLight
// Method				:	requiredParameters
// Description			:	Get the required parameters
// Return Value			:	-
// Comments				:
// Date last edited		:	11/2/2003
unsigned int			CQuadLight::requiredParameters() {
	return 0;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CQuadLight
// Method				:	getName
// Description			:	Get the name of the shader
// Return Value			:	-
// Comments				:
// Date last edited		:	11/2/2003
const char				*CQuadLight::getName() {
	return "quadlight";
}

