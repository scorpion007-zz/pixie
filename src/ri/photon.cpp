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
//  File				:	photon.cpp
//  Classes				:	CPhotonHider
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "photon.h"
#include "memory.h"
#include "object.h"
#include "random.h"
#include "photonMap.h"
#include "stats.h"
#include "error.h"


static vector spectrumSpline[] = {		{ 0, 0, 0},
											{ 0, 0, 0},
											{ 1, 0, 0},
											{ 1, 0.72f, 0},
											{ 0, 1, 0},
											{ 0, 0.72f, 1},
											{ 0, 0, 1},
											{ 0, 0, 0},
											{ 0, 0, 0}
										};


///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonHider
// Method				:	CPhotonHider
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	3/7/2003
CPhotonHider::CPhotonHider(COptions *o,CXform *x,SOCKET s,CAttributes *a) : CShadingContext(o,x,s,HIDER_NEEDS_RAYTRACING | HIDER_NODISPLAY | HIDER_ILLUMINATIONHOOK | HIDER_PHOTONMAP_OVERWRITE) {
	bias		=	a->shadowBias;
	phony		=	new CSurface(a,x);
	phony->attach();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonHider
// Method				:	~CPhotonHider
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	3/7/2003
CPhotonHider::~CPhotonHider() {
	CPhotonMap	*cMap;

	// Balance the maps that have been modified
	while((cMap = balanceList.pop()) != NULL) {
		cMap->modifying	=	FALSE;
		cMap->write(world);
	}

	phony->detach();
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonHider
// Method				:	renderFrame
// Description			:	Renders the frame
// Return Value			:	-
// Comments				:
// Date last edited		:	3/7/2003
void		CPhotonHider::renderFrame(){  
	memBegin();

	const int		numLights	=	allLights->numItems;
	CShaderInstance	**lights	=	allLights->array;
	int				i,j;
	vector			tmp;
	const	char	*previousActivity	=	stats.activity;

	stats.activity	=	"Photonmap construction";

	// Compute the world bounding sphere
	addvv(worldCenter,worldBmin,worldBmax);
	mulvf(worldCenter,1 / (float) 2);
	subvv(tmp,worldBmax,worldCenter);
	worldRadius	=	lengthv(tmp);

	// The actual photon tracing stage
	stage						=	PHOTON_TRACE;
	for (i=0;i<numLights;i++) {
		CShaderInstance	*cLight						=	lights[i];
		CShadedLight	**lights					=	&currentShadingState->lights;
		CShadedLight	**alights					=	&currentShadingState->alights;
		CShadedLight	**currentLight				=	&currentShadingState->currentLight;
		CShadedLight	**freeLights				=	&currentShadingState->freeLights;
		int				*tags						=	currentShadingState->tags;
		int				emit;
		float			*Clsave;
		T64				shaderVarCheckpoint[3];

		// Figure out how much we want to emit
		emit										=	numEmitPhotons;

		if (emit > 0) {
			photonPower								=	1 / (float) emit;

			while(emit > 0) {
				const int	numVertices					=	min(maxGridSize,emit);

				currentShadingState->numVertices		=	numVertices;
				currentShadingState->numRealVertices	=	numVertices;
				currentShadingState->numUvertices		=	-1;
				currentShadingState->numVvertices		=	-1;
				currentShadingState->numActive			=	numVertices;
				currentShadingState->numPassive			=	0;
				currentShadingState->shadingDim			=	SHADING_0D;
				currentShadingState->currentObject		=	phony;
				currentShadingState->lightCategory		=	0;
				
				// Ensure there's space for the ambient lights
				
				*alights					=		(CShadedLight*)	ralloc(sizeof(CShadedLight));
				(*alights)->savedState		=		(float**)		ralloc(2*sizeof(CShadedLight));
				(*alights)->savedState[1]	=		(float*)		ralloc(3*sizeof(float)*numVertices);
				(*alights)->savedState[0]	=		NULL;			/* ambient lights do not use tags or save L */
				(*alights)->lightTags		=		NULL;
				(*alights)->instance		=		NULL;
				(*alights)->next			=		NULL;
				
				// Reset the state
				
				*lights						=	NULL;			// Lights			:	Cool
				*currentLight				=	NULL;			// Light iterator	:	Cool
				*freeLights					=	NULL;			// Free light lits	:	Cool
				
				Clsave						= (*alights)->savedState[1];
				
				for (j=0;j<numVertices;j++) {
					initv(Clsave,0,0,0);						// Ambient lights	:	Cool
					tags[j]		=	0;							// Exec tags		:	Cool
					Clsave	+=	3;
				}

				// Execute the light source shader
				memBegin();
	            memSave(shaderVarCheckpoint,shaderStateMemory);
				
				currentShadingState->locals[ACCESSOR_LIGHTSOURCE] = cLight->prepare(shaderStateMemory,currentShadingState->varying,numVertices);
				cLight->illuminate(this,currentShadingState->locals[ACCESSOR_LIGHTSOURCE]);

				memRestore(shaderVarCheckpoint,shaderStateMemory);
				memEnd();

				emit									-=	numVertices;
			}
		}
	}

	stats.activity	=	previousActivity;

	memEnd();
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonHider
// Method				:	solarBegin
// Description			:	Solar begin hook
// Return Value			:	-
// Comments				:
// Date last edited		:	3/7/2003
void		CPhotonHider::solarBegin(const float *L,const float *theta) {
	if (L == NULL) {
		// FIXME: Don't know how to handle this
	} else {
		float	**varying	=	currentShadingState->varying;
		float	*shaderL	=	varying[VARIABLE_L];
		float	*shaderPs	=	varying[VARIABLE_PS];
		int		numVertices	=	currentShadingState->numVertices;
		float	xy[2];
		vector	cX;
		double	r;
		double	theta;
		vector	X,Y;

		powerScale			=	(float) (C_PI*worldRadius*worldRadius);

		initv(Y,1,2,3);
		crossvv(X,L,Y);
		crossvv(Y,X,L);
		normalizev(X);
		normalizev(Y);
		mulvf(X,worldRadius);
		mulvf(Y,worldRadius);

		// Generate the solar samples
		for (;numVertices>0;numVertices--,shaderL+=3,shaderPs+=3) {
			gen2.get(xy);

			r		=	sqrtf(xy[0]);
			theta	=	xy[1]*2*C_PI;

			mulvf(cX,X,(float) (r*cos(theta)));
			mulvf(shaderPs,Y,(float) (r*sin(theta)));
			addvv(shaderPs,cX);
			addvv(shaderPs,worldCenter);
			normalizev(shaderL,L);
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonHider
// Method				:	solarEnd
// Description			:	Solar end hook
// Return Value			:	-
// Comments				:
// Date last edited		:	3/7/2003
void		CPhotonHider::solarEnd() {
	int			numVertices	=	currentShadingState->numVertices;
	float		**varying	=	currentShadingState->varying;

	if (stage == PHOTON_ESTIMATE) {
		// Estimation
		const float	*Cl			=	varying[VARIABLE_CL];

		// Solar lights are easy, just do the averaging
		for (;numVertices>0;numVertices--,Cl+=3) {
			const float power	=	(Cl[0] + Cl[1] + Cl[2]) / (float) 3;

			minPower	=	min(minPower,power);
			maxPower	=	max(maxPower,power);
			avgPower	+=	power;
			numPower++;
		}
	} else {
		// Photon casting
		float	*Ps	=	varying[VARIABLE_PS];
		float	*L	=	varying[VARIABLE_L];
		float	*Cl	=	varying[VARIABLE_CL];
		int		i;

		if (flags & OPTIONS_FLAGS_SAMPLESPECTRUM) {
			vector		T;
			vector		Ce,Cc;
			float*		ubasis			=	(float*) RiBSplineBasis;
			const int	numPoints		=	sizeof(spectrumSpline)/(sizeof(float)*3);
			const int	step			=	1;
			const int	n				=	(numPoints-4)/step+1;
			
			for (i=numVertices;i>0;i--,Ps+=3,L+=3,Cl+=3) {	
				
				float		wavelen			=	urand();
				int			piece			=	(int) floor(wavelen * n);
				int			pieceid			=	piece*step;
				float		u				=	wavelen*n - piece;
				
				float		tmp[4];
				float		ub[4];
				
				ub[3] = 1;
				ub[2] =	u;
				ub[1] =	u*u;
				ub[0] =	u*ub[2];
				
				tmp[0]	=	ub[0]*ubasis[element(0,0)] + ub[1]*ubasis[element(0,1)] + ub[2]*ubasis[element(0,2)] + ub[3]*ubasis[element(0,3)];
				tmp[1]	=	ub[0]*ubasis[element(1,0)] + ub[1]*ubasis[element(1,1)] + ub[2]*ubasis[element(1,2)] + ub[3]*ubasis[element(1,3)];
				tmp[2]	=	ub[0]*ubasis[element(2,0)] + ub[1]*ubasis[element(2,1)] + ub[2]*ubasis[element(2,2)] + ub[3]*ubasis[element(2,3)];
				tmp[3]	=	ub[0]*ubasis[element(3,0)] + ub[1]*ubasis[element(3,1)] + ub[2]*ubasis[element(3,2)] + ub[3]*ubasis[element(3,3)];
				
				Ce[0]		=	tmp[0]*spectrumSpline[pieceid+0][0] +
								tmp[1]*spectrumSpline[pieceid+1][0] +
								tmp[2]*spectrumSpline[pieceid+2][0] +
								tmp[3]*spectrumSpline[pieceid+3][0];
				Ce[1]		=	tmp[0]*spectrumSpline[pieceid+0][1] +
								tmp[1]*spectrumSpline[pieceid+1][1] +
								tmp[2]*spectrumSpline[pieceid+2][1] +
								tmp[3]*spectrumSpline[pieceid+3][1];
				Ce[2]		=	tmp[0]*spectrumSpline[pieceid+0][2] +
								tmp[1]*spectrumSpline[pieceid+1][2] +
								tmp[2]*spectrumSpline[pieceid+2][2] +
								tmp[3]*spectrumSpline[pieceid+3][2];
				mulvv(Cc,Cl,Ce);
	
				mulvf(T,L,worldRadius);
				subvv(Ps,T);
				mulvf(Cc,powerScale*photonPower);
				tracePhoton(Ps,L,Cc,wavelen);
			}
		} else {
			for (i=numVertices;i>0;i--,Ps+=3,L+=3,Cl+=3) {
				vector	T;
	
				mulvf(T,L,worldRadius);
				subvv(Ps,T);
				mulvf(Cl,powerScale*photonPower);
				tracePhoton(Ps,L,Cl,0.5);
			}
		}
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonHider
// Method				:	illuminateBegin
// Description			:	Illuminate begin hook
// Return Value			:	-
// Comments				:
// Date last edited		:	3/7/2003
void		CPhotonHider::illuminateBegin(const float *P,const float *N,const float *theta) {
	float	**varying	=	currentShadingState->varying;
	int		numVertices	=	currentShadingState->numVertices;
	float	*shaderPs	=	varying[VARIABLE_PS];
	float	*shaderL	=	varying[VARIABLE_L];

	if (theta == NULL) {
		// We must be a point light source
		powerScale		=	(float) (4*C_PI);

		for (;numVertices>0;numVertices--,shaderPs+=3,shaderL+=3) {
			// Sample a direction in the unit sphere
			do {
				gen3.get(shaderL);

				shaderL[0]	=	2*shaderL[0] - 1;
				shaderL[1]	=	2*shaderL[1] - 1;
				shaderL[2]	=	2*shaderL[2] - 1;
			} while(dotvv(shaderL,shaderL) > 1);

			// Compute the point being shaded
			normalizev(shaderL);
			addvv(shaderPs,P,shaderL);
		}
	} else {
		// We must be an area light source
		powerScale		=	(float) (2*C_PI);

		assert(N != NULL);

		if (theta == NULL) {
			// FIXME: Don't know how to handle this
		} else {

			for (;numVertices>0;numVertices--,shaderPs+=3,shaderL+=3) {
				// Sample a direction in the unit sphere
				sampleHemisphere(shaderL,N,theta[0],gen4);

				// Compute the point being shaded	
				normalizev(shaderL);
				addvv(shaderPs,P,shaderL);
			}
		}
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonHider
// Method				:	illuminateEnd
// Description			:	Illuminate end hook
// Return Value			:	-
// Comments				:
// Date last edited		:	3/7/2003
void		CPhotonHider::illuminateEnd() {
	int			numVertices	=	currentShadingState->numVertices;
	float		**varying	=	currentShadingState->varying;

	if (stage == PHOTON_ESTIMATE) {
		// Estimation
		const float	*Cl			=	varying[VARIABLE_CL];
		const float	*Ps			=	varying[VARIABLE_PS];
		const float	*L			=	varying[VARIABLE_L];
		CRay		ray;

		for (;numVertices>0;numVertices--,Cl+=3,L+=3,Ps+=3) {
			movvv(ray.dir,L);
			subvv(ray.from,Ps,L);
			movvv(ray.to,Ps);

			ray.flags				=	ATTRIBUTES_FLAGS_PRIMARY_VISIBLE;
			ray.tmin				=	bias;
			ray.invDir[COMP_X]		=	1/ray.dir[COMP_X];
			ray.invDir[COMP_Y]		=	1/ray.dir[COMP_Y];
			ray.invDir[COMP_Z]		=	1/ray.dir[COMP_Z];
			ray.t					=	C_INFINITY;
			ray.time				=	0;
			ray.jimp				=	urand();
			ray.lastXform			=	NULL;
			ray.object				=	NULL;

			hierarchy->intersect(&ray);

			if (ray.object != NULL) {
				const float power = (Cl[0] + Cl[1] + Cl[2]) / (3*ray.t*ray.t);

				minPower	=	min(minPower,power);
				maxPower	=	max(maxPower,power);
				avgPower	+=	power;
				numPower++;
			}
		}
	} else {
		float	*Ps	=	varying[VARIABLE_PS];
		float	*L	=	varying[VARIABLE_L];
		float	*Cl	=	varying[VARIABLE_CL];
		int		i;

		if (flags & OPTIONS_FLAGS_SAMPLESPECTRUM) {
			vector		Ce,Cc;
			float*		ubasis			=	(float*) RiBSplineBasis;
			const int	numPoints		=	sizeof(spectrumSpline)/(sizeof(float)*3);
			const int	step			=	1;
			const int	n				=	(numPoints-4)/step+1;
			
			for (i=numVertices;i>0;i--,Ps+=3,L+=3,Cl+=3) {				
				float		wavelen			=	urand();
				int			piece			=	(int) floor(wavelen * n);
				int			pieceid			=	piece*step;
				float		u				=	wavelen*n - piece;
				
				float		tmp[4];
				float		ub[4];
				
				ub[3] = 1;
				ub[2] =	u;
				ub[1] =	u*u;
				ub[0] =	u*ub[2];
				
				tmp[0]	=	ub[0]*ubasis[element(0,0)] + ub[1]*ubasis[element(0,1)] + ub[2]*ubasis[element(0,2)] + ub[3]*ubasis[element(0,3)];
				tmp[1]	=	ub[0]*ubasis[element(1,0)] + ub[1]*ubasis[element(1,1)] + ub[2]*ubasis[element(1,2)] + ub[3]*ubasis[element(1,3)];
				tmp[2]	=	ub[0]*ubasis[element(2,0)] + ub[1]*ubasis[element(2,1)] + ub[2]*ubasis[element(2,2)] + ub[3]*ubasis[element(2,3)];
				tmp[3]	=	ub[0]*ubasis[element(3,0)] + ub[1]*ubasis[element(3,1)] + ub[2]*ubasis[element(3,2)] + ub[3]*ubasis[element(3,3)];
				
				Ce[0]		=	tmp[0]*spectrumSpline[pieceid+0][0] +
								tmp[1]*spectrumSpline[pieceid+1][0] +
								tmp[2]*spectrumSpline[pieceid+2][0] +
								tmp[3]*spectrumSpline[pieceid+3][0];
				Ce[1]		=	tmp[0]*spectrumSpline[pieceid+0][1] +
								tmp[1]*spectrumSpline[pieceid+1][1] +
								tmp[2]*spectrumSpline[pieceid+2][1] +
								tmp[3]*spectrumSpline[pieceid+3][1];
				Ce[2]		=	tmp[0]*spectrumSpline[pieceid+0][2] +
								tmp[1]*spectrumSpline[pieceid+1][2] +
								tmp[2]*spectrumSpline[pieceid+2][2] +
								tmp[3]*spectrumSpline[pieceid+3][2];
				mulvv(Cc,Cl,Ce);
				
				subvv(Ps,L);
				mulvf(Cc,powerScale*photonPower);
				tracePhoton(Ps,L,Cc,wavelen);
			}
		} else {
			for (i=numVertices;i>0;i--,Ps+=3,L+=3,Cl+=3) {
				subvv(Ps,L);
				mulvf(Cl,powerScale*photonPower);
				tracePhoton(Ps,L,Cl,0.5);
			}

		}
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonHider
// Method				:	tracePhotons
// Description			:	Trace the photons generated by a light source
// Return Value			:	-
// Comments				:
// Date last edited		:	3/11/2003
void		CPhotonHider::tracePhoton(float *P,float *L,float *C,float wavelength) {
	CRay				ray;
	vector				Cl,Pl,Nl;
	CAttributes			*attributes;
	const float			*surfaceColor;
	int					numDiffuseBounces,numSpecularBounces,lastBounceSpecular;

	ray.flags				=	ATTRIBUTES_FLAGS_PRIMARY_VISIBLE;

	// The L must be unit vector
	assert((dotvv(L,L) - 1)*(dotvv(L,L) - 1) < 0.00001);

	//if (dotvv(C,C) < EPSILON)	return;

	movvv(ray.from,P);
	movvv(ray.dir,L);
	addvv(ray.to,P,L);

	movvv(Cl,C);

	// The maximum number of diffuse and specular bounces
	numDiffuseBounces		=	0;
	numSpecularBounces		=	0;
	lastBounceSpecular		=	FALSE;

	// The intersection bias
	ray.tmin				=	bias;

processBounce:;

	// Set misc variables
	ray.invDir[COMP_X]		=	1/ray.dir[COMP_X];
	ray.invDir[COMP_Y]		=	1/ray.dir[COMP_Y];
	ray.invDir[COMP_Z]		=	1/ray.dir[COMP_Z];
	ray.t					=	C_INFINITY;
	ray.time				=	0;
	ray.lastXform			=	NULL;
	ray.object				=	NULL;

	// Trace the ray in the scene
	hierarchy->intersect(&ray);

	// Do we have an intersection ?
	if (ray.object != NULL) {
		attributes				=	ray.object->attributes;
		surfaceColor			=	attributes->surfaceColor;

		if (attributes->flags & ATTRIBUTES_FLAGS_ILLUMINATE_FRONT_ONLY) {
			if (dotvv(ray.N,ray.dir) > 0) return;
		}

		mulvf(Pl,ray.dir,ray.t);
		addvv(Pl,ray.from);

		// Process this hit
		switch(attributes->shadingModel) {


		// Matte surface
		case SM_MATTE:
			{
				CPhotonMap	*globalMap;
				CPhotonMap	*causticMap;

				// Compute the normalized normal vector at the intersection
				normalizev(Nl,ray.N);
				if (dotvv(ray.dir,Nl) > 0) {
					mulvf(Nl,-1);
				}
				
				// Save the photon
				if ((globalMap=attributes->globalMap) != NULL) {
					if (globalMap->modifying == FALSE) {
						globalMap->modifying	=	TRUE;
						globalMap->reset();
						balanceList.push(globalMap);
					}

					globalMap->store(Pl,Nl,ray.dir,Cl);
				}

				if ((causticMap=attributes->causticMap) != NULL) {
					if (lastBounceSpecular) {
						if (causticMap->modifying == FALSE) {
							causticMap->modifying	=	TRUE;
							causticMap->reset();
							balanceList.push(causticMap);
						}
	
						causticMap->store(Pl,Nl,ray.dir,Cl);

						return;
					}
				}

				// Check if we hit the maximum number of bounces
				if (numDiffuseBounces >= attributes->maxDiffuseDepth) return;
				numDiffuseBounces++;

				// Sample the reflection direction
				sampleCosineHemisphere(ray.dir,Nl,(float) (C_PI / 2.0),gen4);
				assert(dotvv(Nl,ray.dir) > 0);
				normalizev(ray.dir);
				
				// Bounce the photon
				mulvv(Cl,surfaceColor);

				// Process the current hit
				movvv(ray.from,Pl);
				addvv(ray.to,ray.from,ray.dir);
				ray.tmin				=	attributes->shadowBias;
				lastBounceSpecular		=	FALSE;

				goto processBounce;
			}

			break;
		case SM_TRANSLUCENT:
			//HACKBEGIN
			//
			// Find spans across solid
			// Work out if we should have scattered before the hit
			// if so, use phase function to determine it
			// else store exit photon and quit
			{
				CPhotonMap	*globalMap;
				CPhotonMap	*causticMap;
				
				// Compute the normalized normal vector at the intersection
				normalizev(Nl,ray.N);
				if (dotvv(ray.dir,Nl) > 0) {
					mulvf(Nl,-1);
				}
				
				// Save the photon on entry to the material
				if ((globalMap=attributes->globalMap) != NULL) {
					if (globalMap->modifying == FALSE) {
						globalMap->modifying	=	TRUE;
						globalMap->reset();
						balanceList.push(globalMap);
					}

					globalMap->store(Pl,Nl,ray.dir,Cl);
				}

				if ((causticMap=attributes->causticMap) != NULL) {
					if (lastBounceSpecular) {
						if (causticMap->modifying == FALSE) {
							causticMap->modifying	=	TRUE;
							causticMap->reset();
							balanceList.push(causticMap);
						}
	
						causticMap->store(Pl,Nl,ray.dir,Cl);

						return;
					}
				}

				// Check if we hit the maximum number of bounces
				if (numDiffuseBounces >= attributes->maxDiffuseDepth) return;
				numDiffuseBounces++;
				
				// Bounce the photon
				vector red = {1,0,0};
		//		mulvv(Cl,surfaceColor);
				mulvv(Cl,red);

				normalizev(ray.dir);
				
				// Process the current hit
				ray.tmin				=	attributes->shadowBias;
				lastBounceSpecular		=	FALSE;

				int scatters			=	0;
				float pathLength		=	0;
				CObject *curObject		=	ray.object;
				
				processScatter:;
				
				{
					// Set misc variables
					movvv(ray.from,Pl);
					addvv(ray.to,ray.from,ray.dir);
			
					ray.invDir[COMP_X]		=	1/ray.dir[COMP_X];
					ray.invDir[COMP_Y]		=	1/ray.dir[COMP_Y];
					ray.invDir[COMP_Z]		=	1/ray.dir[COMP_Z];
					ray.t					=	C_INFINITY;
					ray.time				=	0;
					ray.lastXform			=	NULL;
					ray.object				=	NULL;
				
					// Trace the ray in the scene
					hierarchy->intersect(&ray);
					
					// Bail if we hit nothing
					if (ray.object == NULL) {
//						printf("ff\n");
						return;
					}
					
					// Did we exit the object yet?
					//if (ray.object == curObject) {
					//if (dotvv(ray.dir,ray.N) < 0) {
					if (1){
						// Keep scattering until we are 'close' enough
						// to the surface to exit
																		
						const float kScatter = 0.01f;
						const float kExtinct = 0.2f;//0.7;
						//float 		tScatter = kScatter*urand();
						float 		tScatter = -kScatter*log(urand()+C_EPSILON);
//						printf("%f\n",ray.t);
						// Test for scattering event
						vector d;
						mulvf(d,ray.dir,ray.t);
						if(ray.t-bias > tScatter) {
							// calculate point of scatter event
							mulvf(Pl,ray.dir,tScatter);
							addvv(Pl,ray.from);
						
							/*if ((globalMap=attributes->globalMap) != NULL) {
								if (globalMap->modifying == FALSE) {
									globalMap->modifying	=	TRUE;
									globalMap->reset();
									balanceList.push(globalMap);
								}
			
								// zero normal?
								globalMap->store(Pl,ray.dir,ray.dir,Cl);
							}*/
							
					//		if(scatters >= attributes->maxDiffuseDepth*40) return;
							scatters++;
							pathLength += tScatter;
//							printf("%d   (%f)  %f %f %f\n",scatters,tScatter,ray.dir[0],ray.dir[1],ray.dir[2]);
							
							vector D;
							sampleHemisphere(D,ray.dir,(float) (C_PI / 2.0)/8,gen4);
							// decide on forward or back
							//if(urand() > 0.8) {
							//	normalizev(ray.dir,D);
							//	mulvf(ray.dir,-1);
							//} else {
								normalizev(ray.dir,D);
							//}
					
							goto processScatter;
						}
//						printf(">> %d\n",scatters);
						// fall-out.  We exited the object
						
						mulvf(Pl,ray.dir,ray.t);
						addvv(Pl,ray.from);
				
						// compute the normal at the intersection
						normalizev(Nl,ray.N);
						if (dotvv(ray.dir,Nl) < 0) {		// on the reverse
							mulvf(Nl,-1);
						}
						
						if ((globalMap=attributes->globalMap) != NULL) {
							if (globalMap->modifying == FALSE) {
								globalMap->modifying	=	TRUE;
								globalMap->reset();
								balanceList.push(globalMap);
							}
		
							// zero normal?
							vector g = {0,1,0};
							float ext = exp(-pathLength*kExtinct);
							mulvf(Cl,ext);
							globalMap->store(Pl,Nl,ray.dir,Cl);
						}
					} else {
						// We hit something else, go re-trace it
						// Do not reset the ray
//						printf("ee\n");
													
						goto processBounce;
					}
				}
				
				// go trace this as normal ray
				movvv(ray.from,Pl);
				addvv(ray.to,ray.from,ray.dir);
				
			//	lastBounceSpecular = TRUE;
				
				goto processBounce;
			}
			//HACKEND
			
			break;
		case SM_CHROME:
			{
				vector	Ll;

				// Check if we hit the maximum number of bounces
				if (numSpecularBounces >= attributes->maxSpecularDepth) return;
				numSpecularBounces++;

				// Sample the reflection direction
				normalizev(Nl,ray.N);
				if (dotvv(ray.dir,Nl) > 0) {
					mulvf(Nl,-1);
				}

				movvv(Ll,ray.dir);
				reflect(ray.dir,Ll,Nl);

				// Modulate by surface color
				mulvv(Cl,surfaceColor);
				
				// Bounce the photon
				movvv(ray.from,Pl);
				addvv(ray.to,ray.from,ray.dir);
				ray.tmin				=	attributes->shadowBias;
				lastBounceSpecular		=	TRUE;

				goto processBounce;
			}
			break;
		case SM_GLASS:
			{
				float	eta;
				float	Kr,Kt;
				vector	R,T;

				// Check if we hit the maximum number of bounces
				if (numSpecularBounces >= attributes->maxSpecularDepth) return;
				numSpecularBounces++;

				// Sample the reflection direction
				normalizev(Nl,ray.N);
				if (dotvv(ray.dir,Nl) > 0) {
					mulvf(Nl,-1);
					eta	=	1 / (float) 1.5;
				} else {
					eta	=	(float) 1.5;
				}

				assert(dotvv(ray.dir,Nl) < 0);
				fresnel(ray.dir,Nl,eta,Kr,Kt,R,T);


				// Decide on reflection or refraction
				if (urand() <= Kr) {
					assert(dotvv(R,R) > 0);
					normalizev(ray.dir,R);
				} else {
					assert(dotvv(T,T) > 0);
					normalizev(ray.dir,T);
					// Modulate by surface color for transmitted photons
					mulvv(Cl,surfaceColor);
				}

				// Bounce the photon
				movvv(ray.from,Pl);
				addvv(ray.to,ray.from,ray.dir);
				ray.tmin				=	attributes->shadowBias;
				lastBounceSpecular		=	TRUE;

				goto processBounce;
			}
			break;
		case SM_WATER:
			{
				float	eta;
				float	Kr,Kt;
				vector	R,T;

				// Check if we hit the maximum number of bounces
				if (numSpecularBounces >= attributes->maxSpecularDepth) return;
				numSpecularBounces++;

				// Sample the reflection direction
				normalizev(Nl,ray.N);
				if (dotvv(ray.dir,Nl) > 0) {
					mulvf(Nl,-1);
					eta	=	1 / (float) 1.3333333;
				} else {
					eta	=	(float) 1.3333333;
				}

				assert(dotvv(ray.dir,Nl) < 0);
				fresnel(ray.dir,Nl,eta,Kr,Kt,R,T);


				// Decide on reflection or refraction
				if (urand() <= Kr) {
					assert(dotvv(R,R) > 0);
					normalizev(ray.dir,R);
				} else {
					assert(dotvv(T,T) > 0);
					normalizev(ray.dir,T);
					// Modulate by surface color for transmitted photons
					mulvv(Cl,surfaceColor);
				}

				// Bounce the photon
				movvv(ray.from,Pl);
				addvv(ray.to,ray.from,ray.dir);
				ray.tmin				=	attributes->shadowBias;
				lastBounceSpecular		=	TRUE;

				goto processBounce;
			}
			break;
		case SM_DIELECTRIC:
			{
				float	eta;
				float	Kr,Kt;
				vector	R,T;

				// Check if we hit the maximum number of bounces
				if (numSpecularBounces >= attributes->maxSpecularDepth) return;
				numSpecularBounces++;
				
				// Calculate the effective ior
				float iorR = attributes->photonIor[0];
				float iorB = attributes->photonIor[1];
				
				float ior = (wavelength*iorR + (1.0f-wavelength)*iorB);

				// Sample the reflection direction
				normalizev(Nl,ray.N);
				if (dotvv(ray.dir,Nl) > 0) {
					mulvf(Nl,-1);
					eta	=	1 / ior;
				} else {
					eta	=	ior;
				}

				assert(dotvv(ray.dir,Nl) < 0);
				fresnel(ray.dir,Nl,eta,Kr,Kt,R,T);


				// Decide on reflection or refraction
				if (urand() <= Kr) {
					assert(dotvv(R,R) > 0);
					normalizev(ray.dir,R);
				} else {
					assert(dotvv(T,T) > 0);
					normalizev(ray.dir,T);
					// Modulate by surface color for transmitted photons
					mulvv(Cl,surfaceColor);
				}

				// Bounce the photon
				movvv(ray.from,Pl);
				addvv(ray.to,ray.from,ray.dir);
				ray.tmin				=	attributes->shadowBias;
				lastBounceSpecular		=	TRUE;

				goto processBounce;
			}
			break;
		case SM_TRANSPARENT:
			{
				vector	tmp;

				// Just keep on tracing the ray
				mulvf(tmp,ray.dir,ray.t);
				addvv(ray.from,tmp);
				Cl[0]	*=	(1-attributes->surfaceOpacity[0]);
				Cl[1]	*=	(1-attributes->surfaceOpacity[1]);
				Cl[2]	*=	(1-attributes->surfaceOpacity[2]);
			}
			break;
		}
	}
}



