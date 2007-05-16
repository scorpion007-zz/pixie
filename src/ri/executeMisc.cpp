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
//  File				:	executeMisc.cpp
//  Classes				:	-
//  Description			:	This file implements the main shader execution
//
////////////////////////////////////////////////////////////////////////
#include <math.h>
#include <float.h>

#include "common/global.h"
#include "bundles.h"
#include "memory.h"
#include "attributes.h"
#include "renderer.h"
#include "stats.h"
#include "ri_config.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Misc. derivative functions
//
///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	duFloat
// Description			:	Compute the u derivative
// Return Value			:	-
// Comments				:
void	CShadingContext::duFloat(float *dest,const float *src) {
	switch(currentShadingState->shadingDim) {


		// Du executing on Points or Curves (note that curves are defined along v)
		case SHADING_0D:
		break;


		// Du executing on a 2D grid
		case SHADING_2D_GRID:
		{
			const int	uVertices	=	currentShadingState->numUvertices;
			const int	vVertices	=	currentShadingState->numVvertices;
			int			i,j;
			const float	*u			=	currentShadingState->varying[VARIABLE_U];

			assert(uVertices >= 2);
			assert(vVertices >= 2);
			assert(u[1] > u[0]);

			// These values are constant accross a grid
			double		invDu1		=	1 / (double) (u[1] - u[0]);
			double		invDu2		=	1 / (double) (2*(u[1] - u[0]));			

			// Compute the Du
			for (j=vVertices;j>0;j--) {

				// Forward differencing
				*dest++	=	(float) ((src[1] - src[0]) * invDu1);
				src++;

				// Central differencing
				for (i=uVertices-2;i>0;i--) {
					*dest++	=	(float) ((src[1] - src[-1]) * invDu2);
					src++;
				}

				// Backward differencing
				*dest++	=	(float) ((src[0] - src[-1]) * invDu1);
				src++;
			}
		}
		break;


		// Du executing on a 2D raytraced surface
		case SHADING_2D:
		{
			const int	numRealVertices	=	currentShadingState->numRealVertices;
			const float	*dsrc			=	src + numRealVertices;
			float		*ddest			=	dest + numRealVertices;
			const float	*du				=	currentShadingState->varying[VARIABLE_DU];
			int			i;

			for (i=numRealVertices;i>0;i--) {

				assert(*du != 0);

				const float	val	=	(dsrc[0] - src[0]) / (*du++);

				ddest[0]		=	val;
				ddest[1]		=	val;
				dest[0]			=	val;

				dest++;
				src++;
				ddest			+=	2;
				dsrc			+=	2;
			}
		}
		break;
	}
}




///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	dvFloat
// Description			:	Compute the v derivative
// Return Value			:	-
// Comments				:
void	CShadingContext::dvFloat(float *dest,const float *src) {

	switch(currentShadingState->shadingDim) {

		// Dv executing on Points
		case SHADING_0D:
		{
			for (int i=currentShadingState->numVertices;i>0;i--) {
				*dest++	=	0;
			}
		}
		break;


		// Dv executing on a 2D grid
		case SHADING_2D_GRID:
		{
			const int		uVertices	=	currentShadingState->numUvertices;
			const int		vVertices	=	currentShadingState->numVvertices;
			int				i,j;
			const float		*v			=	currentShadingState->varying[VARIABLE_V];

			assert(uVertices >= 2);
			assert(vVertices >= 2);
			assert(v[uVertices] > v[0]);

			const double	invDv1		=	1 / (double) (v[uVertices] - v[0]);
			const double	invDv2		=	1 / (double) (2*(v[uVertices] - v[0]));

			// Compute the DV
			for (j=0;j<uVertices;j++) {
				float		*cRes	=	dest + j;
				const float	*cOp	=	src + j;

				// Forward differencing
				cRes[0]				=	(float) ((cOp[uVertices] - cOp[0]) * invDv1);
				cRes				+=	uVertices;
				cOp					+=	uVertices;

				// Central differencing
				for (i=vVertices-2;i>0;i--) {
					cRes[0]			=	(float) ((cOp[uVertices] - cOp[-uVertices]) * invDv2);
					cRes			+=	uVertices;
					cOp				+=	uVertices;
				}

				// Backward differencing
				cRes[0]				=	(float) ((cOp[0] - cOp[-uVertices]) * invDv1);
			}
		}
		break;

		// Dv executing on a 2D raytraced surface
		case SHADING_2D:
		{
			const int	numVertices		=	currentShadingState->numVertices;
			const int	numRealVertices	=	currentShadingState->numRealVertices;
			const float	*dsrc			=	src + numRealVertices;
			float		*ddest			=	dest + numRealVertices;
			const float	*dv				=	currentShadingState->varying[VARIABLE_DV];

			assert(numVertices == numRealVertices*3);

			for (int i=numRealVertices;i>0;i--) {

				assert(*dv != 0);

				const float	val	=	(dsrc[1] - src[0]) / (*dv++);

				ddest[0]		=	val;
				ddest[1]		=	val;
				dest[0]			=	val;

				dest++;
				src++;
				ddest			+=	2;
				dsrc			+=	2;
			}
		}
		break;
	}
}


































///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	duVector
// Description			:	Compute the u derivative
// Return Value			:	-
// Comments				:
void	CShadingContext::duVector(float *dest,const float *src) {
	switch(currentShadingState->shadingDim) {


		// Du executing on Points or Curves (note that curves are defined along v)
		case SHADING_0D:
		break;


		// Du executing on a 2D grid
		case SHADING_2D_GRID:
		{
			const int		uVertices	=	currentShadingState->numUvertices;
			const int		vVertices	=	currentShadingState->numVvertices;
			int				i,j;
			const float		*u			=	currentShadingState->varying[VARIABLE_U];

			assert(uVertices >= 2);
			assert(vVertices >= 2);
			assert(u[1] > u[0]);

			const double	invDu1		=	1 / (double) (u[1] - u[0]);		
			const double	invDu2		=	1 / (double) (2*(u[1] - u[0]));

			for (j=vVertices;j>0;j--) {

				// Use forward difference
				*dest++	=	(float) ((src[3] - src[0]) * invDu1);
				*dest++	=	(float) ((src[4] - src[1]) * invDu1);
				*dest++	=	(float) ((src[5] - src[2]) * invDu1);
				src		+=	3;

				// Use central difference
				for (i=uVertices-2;i>0;i--) {
					*dest++	=	(float) ((src[3] - src[-3]) * invDu2);
					*dest++	=	(float) ((src[4] - src[-2]) * invDu2);
					*dest++	=	(float) ((src[5] - src[-1]) * invDu2);
					src		+=	3;
				}

				// Use backward difference
				*dest++	=	(float) ((src[0] - src[-3]) * invDu1);
				*dest++	=	(float) ((src[1] - src[-2]) * invDu1);
				*dest++	=	(float) ((src[2] - src[-1]) * invDu1);
				src		+=	3;
			}
		}
		break;


		// Du executing on a 2D raytraced surface
		case SHADING_2D:
		{
			const int	numRealVertices	=	currentShadingState->numRealVertices;
			const float	*dsrc			=	src + numRealVertices*3;
			float		*ddest			=	dest + numRealVertices*3;
			const float	*du				=	currentShadingState->varying[VARIABLE_DU];
			int			i;

			for (i=numRealVertices;i>0;i--) {

				assert(*du != 0);

				const float	invDu	=	1 / (*du++);
				const float	val0	=	(dsrc[0] - src[0]) * invDu;
				const float	val1	=	(dsrc[1] - src[1]) * invDu;
				const float	val2	=	(dsrc[2] - src[2]) * invDu;

				ddest[0]		=	val0;
				ddest[1]		=	val1;
				ddest[2]		=	val2;
				ddest[3]		=	val0;
				ddest[4]		=	val1;
				ddest[5]		=	val2;
				dest[0]			=	val0;
				dest[1]			=	val1;
				dest[2]			=	val2;

				assert(dotvv(dest,dest) >= 0);

				dest			+=	3;
				src				+=	3;
				ddest			+=	6;
				dsrc			+=	6;
			}
		}
		break;
	}
}





///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	dvVector
// Description			:	Compute the v derivative
// Return Value			:	-
// Comments				:
void	CShadingContext::dvVector(float *dest,const float *src) {
	switch(currentShadingState->shadingDim) {

		// Dv executing on Points
		case SHADING_0D:
		{
			for (int i=currentShadingState->numVertices;i>0;i--) {
				*dest++	=	0;
			}
		}
		break;
		
		// Dv executing on a 2D grid
		case SHADING_2D_GRID:
		{
			const int		uVertices	=	currentShadingState->numUvertices;
			const int		vVertices	=	currentShadingState->numVvertices;
			int				i,j;
			const float		*v			=	currentShadingState->varying[VARIABLE_V];

			assert(uVertices >= 2);
			assert(vVertices >= 2);
			assert(v[uVertices] > v[0]);

			const double	invDv1		=	1 / (double) (v[uVertices] - v[0]);
			const double	invDv2		=	1 / (double) (2*(v[uVertices] - v[0]));

			
			for (j=0;j<uVertices;j++) {
				float		*cRes	=	dest + j*3;
				const float	*cOp	=	src + j*3;

				// Forward differencing
				cRes[0]				=	(float) ((cOp[uVertices*3+0] - cOp[0]) * invDv1);
				cRes[1]				=	(float) ((cOp[uVertices*3+1] - cOp[1]) * invDv1);
				cRes[2]				=	(float) ((cOp[uVertices*3+2] - cOp[2]) * invDv1);
				cRes				+=	uVertices*3;
				cOp					+=	uVertices*3;

				// Central differencing
				for (i=vVertices-2;i>0;i--) {
					cRes[0]			=	(float) ((cOp[uVertices*3+0] - cOp[-uVertices*3+0]) * invDv2);
					cRes[1]			=	(float) ((cOp[uVertices*3+1] - cOp[-uVertices*3+1]) * invDv2);
					cRes[2]			=	(float) ((cOp[uVertices*3+2] - cOp[-uVertices*3+2]) * invDv2);
					cRes			+=	uVertices*3;
					cOp				+=	uVertices*3;
				}

				// Backward differencing
				cRes[0]				=	(float) ((cOp[0] - cOp[-uVertices*3+0]) * invDv1);
				cRes[1]				=	(float) ((cOp[1] - cOp[-uVertices*3+1]) * invDv1);
				cRes[2]				=	(float) ((cOp[2] - cOp[-uVertices*3+2]) * invDv1);
			}
		}
		break;

		// Dv executing on a 2D raytraced surface
		case SHADING_2D:
		{
			const int	numVertices		=	currentShadingState->numVertices;
			const int	numRealVertices	=	currentShadingState->numRealVertices;
			const float	*dsrc			=	src + numRealVertices*3;
			float		*ddest			=	dest + numRealVertices*3;
			const float	*dv				=	currentShadingState->varying[VARIABLE_DV];
			int			i;

			assert(numVertices == numRealVertices*3);

			for (i=numRealVertices;i>0;i--) {

				assert(*dv > 0);

				const float	invDv	=	1 / (*dv++);
				const float	val0	=	(dsrc[3] - src[0]) * invDv;
				const float	val1	=	(dsrc[4] - src[1]) * invDv;
				const float	val2	=	(dsrc[5] - src[2]) * invDv;

				ddest[0]		=	val0;
				ddest[1]		=	val1;
				ddest[2]		=	val2;
				ddest[3]		=	val0;
				ddest[4]		=	val1;
				ddest[5]		=	val2;
				dest[0]			=	val0;
				dest[1]			=	val1;
				dest[2]			=	val2;

				dest			+=	3;
				src				+=	3;
				ddest			+=	6;
				dsrc			+=	6;
			}
		}
		break;
	}
}









//////////////////////////////////////////////////////////////////////////////////////////////
//
//
//		New stuff begins


// Common code for trace transmission and trace reflection
#define	computeRayDifferentials																	\
	const float	da	=	(lengthv(rays->dPdu) + lengthv(rays->dPdv))*0.5f;						\
	const float	db	=	((lengthv(rays->dDdu) + lengthv(rays->dDdv))*0.5f) / lengthv(rays->D);

#define	sampleRay(__from,__dir)			\
	vector	tmp0,tmp1;					\
	mulvf(tmp0,rays->dPdu,urand());		\
	mulvf(tmp1,rays->dPdv,urand());		\
	addvv(__from,tmp0,tmp1);			\
	addvv(__from,rays->P);				\
	mulvf(tmp0,rays->dDdu,urand());		\
	mulvf(tmp1,rays->dDdv,urand());		\
	addvv(__dir,tmp0,tmp1);				\
	addvv(__dir,rays->D);

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	traceTransmission
// Description			:	Trace transmission rays
// Return Value			:	-
// Comments				:
void	CShadingContext::traceTransmission(int numRays,CTraceLocation *rays,CTextureLookup *lookup) {
	CTransmissionRay	*rayBase;
	CTransmissionRay	**raysBase;
	CTransmissionRay	*cRay,**cRays;
	const int			numSamples		=	lookup->numSamples;
	const float			bias			=	lookup->shadowBias;
	const int			shootStep		=	min(CRenderer::shootStep,numRays*numSamples);
	const float			coneAngle		=	lookup->coneAngle;
	const float			maxDist			=	lookup->maxDist;
	int					numRemaining	=	shootStep;
	const float			multiplier		=	1 / (float) numSamples;
	int					currentSample;
	int					i;
	CTransmissionBundle	bundle;
	vector				dir;

	if (lookup->label == NULL)	bundle.label	=	rayLabelTransmission;
	else						bundle.label	=	lookup->label;

	// Allocate the memory for the transmission rays
	cRay	=	rayBase		=	(CTransmissionRay *) ralloc(shootStep*sizeof(CTransmissionRay),threadMemory);
	cRays	=	raysBase	=	(CTransmissionRay **) ralloc(shootStep*sizeof(CTransmissionRay*),threadMemory);

	assert(inShadow == FALSE);

	inShadow		=	TRUE;					// We're in shadow

	// Create the rays
	for (i=numRays;i>0;i--,rays++) {
		
		// Compute the ray differentials
		computeRayDifferentials;

		// Clear the transmission
		initv(rays->C,0,0,0);

		// Create the samples
		for (currentSample=numSamples;currentSample>0;currentSample--) {
			vector	from,L;

			// Sample the ray
			sampleRay(from,L);
			const	float	d	=	lengthv(L);
			mulvf(dir,L,-1/d);

			// Sample a point in the cone
			sampleHemisphere(cRay->dir,dir,coneAngle,random4d);
			if (dotvv(cRay->dir,cRay->dir) > C_EPSILON) {

				movvv(cRay->from,from);
				cRay->t				=	min(maxDist,d) - bias;
				cRay->tmin			=	bias;
				cRay->time			=	(urand() + currentSample - 1) * multiplier;
				cRay->flags			=	ATTRIBUTES_FLAGS_TRANSMISSION_VISIBLE;
				cRay->dest			=	rays->C;
				cRay->multiplier	=	multiplier;
				cRay->da			=	da;		// The ray differential
				cRay->db			=	db;
				*cRays++			=	cRay++;
				if (--numRemaining == 0) {
					numTransmissionRays	+=	shootStep;
					bundle.numRays		=	shootStep;
					bundle.rays			=	(CRay **) raysBase;
					bundle.depth		=	0;
					bundle.last			=	0;
					bundle.postShader	=	NULL;
					traceEx(&bundle);
					cRay				=	rayBase;
					cRays				=	raysBase;
					numRemaining		=	shootStep;
				}
			}
		}
	}

	if (numRemaining != shootStep) {
		numTransmissionRays	+=	shootStep-numRemaining;
		bundle.numRays		=	shootStep-numRemaining;
		bundle.rays			=	(CRay **) raysBase;
		bundle.depth		=	0;
		bundle.last			=	0;
		bundle.postShader	=	NULL;
		traceEx(&bundle);
	}

	inShadow		=	FALSE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	traceReflection
// Description			:	Trace reflected rays
// Return Value			:	-
// Comments				:
void	CShadingContext::traceReflection(int numRays,CTraceLocation *rays,CTextureLookup *lookup) {
	CTraceRay			*rayBase;
	CTraceRay			**raysBase;
	CTraceRay			*cRay,**cRays;
	const int			numSamples		=	lookup->numSamples;
	const float			bias			=	lookup->shadowBias;
	const int			shootStep		=	min(CRenderer::shootStep,numRays*numSamples);
	const float			coneAngle		=	lookup->coneAngle;
	int					numRemaining	=	shootStep;
	const float			multiplier		=	1 / (float) lookup->numSamples;
	int					currentSample;
	int					i;
	CTraceBundle		bundle;

	if (lookup->label == NULL)	bundle.label	=	rayLabelTransmission;
	else						bundle.label	=	lookup->label;

	cRay	=	rayBase		=	(CTraceRay *) ralloc(shootStep*sizeof(CTraceRay),threadMemory);
	cRays	=	raysBase	=	(CTraceRay **) ralloc(shootStep*sizeof(CTraceRay*),threadMemory);


	for (i=numRays;i>0;i--,rays++) {
		
		// Compute the ray differentials
		computeRayDifferentials;

		initv(rays->C,0,0,0);	// Clear the reflection

		for (currentSample=numSamples;currentSample>0;currentSample--) {
			vector	from,D;
			
			sampleRay(from,D);

			normalizev(D);

			sampleHemisphere(cRay->dir,D,coneAngle,random4d);
			if (dotvv(cRay->dir,cRay->dir) > C_EPSILON) {
				movvv(cRay->from,from);
				cRay->time			=	(urand() + currentSample - 1) * multiplier;
				cRay->t				=	C_INFINITY;
				cRay->tmin			=	bias;
				cRay->flags			=	ATTRIBUTES_FLAGS_TRACE_VISIBLE;
				cRay->dest			=	rays->C;
				cRay->multiplier	=	multiplier;
				cRay->da			=	da;
				cRay->db			=	db;
				*cRays++			=	cRay++;
				if (--numRemaining == 0) {
					numReflectionRays	+=	shootStep;
					bundle.numRays		=	shootStep;
					bundle.rays			=	(CRay **) raysBase;
					bundle.depth		=	0;
					bundle.last			=	0;
					bundle.postShader	=	NULL;
					traceEx(&bundle);
					cRay				=	rayBase;
					cRays				=	raysBase;
					numRemaining		=	shootStep;
				}
			}
		}
	}

	if (numRemaining != shootStep) {
		numReflectionRays	+=	shootStep-numRemaining;
		bundle.numRays		=	shootStep-numRemaining;
		bundle.rays			=	(CRay **) raysBase;
		bundle.depth		=	0;
		bundle.last			=	0;
		bundle.postShader	=	NULL;
		traceEx(&bundle);
	}
}


//		New stuff end
//
//
//////////////////////////////////////////////////////////////////////////////////////////////





















///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	traceTransmission
// Description			:	Trace transmission rays
// Return Value			:	-
// Comments				:
void	CShadingContext::traceTransmission(float *dest,const float *from,const float *L,int numVertices,int *tags,CTextureLookup *lookup) {
	CTransmissionRay	*rayBase;
	CTransmissionRay	**raysBase;
	CTransmissionRay	*cRay,**cRays;
	const int			numSamples		=	lookup->numSamples;
	const float			bias			=	lookup->shadowBias;
	const int			shootStep		=	min(CRenderer::shootStep,numVertices*numSamples);
	const float			coneAngle		=	lookup->coneAngle;
	const float			maxDist			=	lookup->maxDist;
	int					numRemaining	=	shootStep;
	const float			multiplier		=	1 / (float) numSamples;
	int					currentSample;
	int					i;
	CTransmissionBundle	bundle;
	vector				dir;

	if (lookup->label == NULL)	bundle.label	=	rayLabelTransmission;
	else						bundle.label	=	lookup->label;

	// Allocate the memory for the transmission rays
	cRay	=	rayBase		=	(CTransmissionRay *) ralloc(shootStep*sizeof(CTransmissionRay),threadMemory);
	cRays	=	raysBase	=	(CTransmissionRay **) ralloc(shootStep*sizeof(CTransmissionRay*),threadMemory);

	assert(inShadow == FALSE);

	inShadow		=	TRUE;					// We're in shadow

	// Compute the ray differential
	const float	*ab				=	rayDiff(from,L,NULL);
	const float angleDeviation	=	tanf(coneAngle + C_EPSILON);

	// Create the rays
	for (i=currentShadingState->numRealVertices;i>0;i--,tags++,ab+=2) {
		if (*tags == 0) {
			const	float	d	=	lengthv(L);
			mulvf(dir,L,-1/d);

			initv(dest,0,0,0);	// Clear the transmission

			// Create the samples
			for (currentSample=numSamples;currentSample>0;currentSample--) {
				// Sample a point in the cone
				sampleHemisphere(cRay->dir,dir,coneAngle,random4d);
				if (dotvv(cRay->dir,cRay->dir) > C_EPSILON) {
					movvv(cRay->from,from);
					cRay->t				=	min(maxDist,d) - bias;
					cRay->tmin			=	bias;
					cRay->time			=	(urand() + currentSample - 1) * multiplier;
					cRay->flags			=	ATTRIBUTES_FLAGS_TRANSMISSION_VISIBLE;
					cRay->dest			=	dest;
					cRay->multiplier	=	multiplier;
					cRay->da			=	ab[0] + angleDeviation;		// The ray differential
					cRay->db			=	ab[1];
					*cRays++			=	cRay++;
					if (--numRemaining == 0) {
						numTransmissionRays	+=	shootStep;
						bundle.numRays		=	shootStep;
						bundle.rays			=	(CRay **) raysBase;
						bundle.depth		=	0;
						bundle.last			=	0;
						bundle.postShader	=	NULL;
						traceEx(&bundle);
						cRay				=	rayBase;
						cRays				=	raysBase;
						numRemaining		=	shootStep;
					}
				}
			}
		}
		dest	+=	3;
		from	+=	3;
		L		+=	3;
	}

	if (numRemaining != shootStep) {
		numTransmissionRays	+=	shootStep-numRemaining;
		bundle.numRays		=	shootStep-numRemaining;
		bundle.rays			=	(CRay **) raysBase;
		bundle.depth		=	0;
		bundle.last			=	0;
		bundle.postShader	=	NULL;
		traceEx(&bundle);
	}

	inShadow		=	FALSE;
}



///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	traceReflection
// Description			:	Trace reflection rays
// Return Value			:	-
// Comments				:
void	CShadingContext::traceReflection(float *dest,const float *from,const float *dir,int numVertices,int *tags,CTextureLookup *lookup) {
	CTraceRay			*rayBase;
	CTraceRay			**raysBase;
	CTraceRay			*cRay,**cRays;
	const int			numSamples		=	lookup->numSamples;
	const float			bias			=	lookup->shadowBias;
	const int			shootStep		=	min(CRenderer::shootStep,numVertices*numSamples);
	const float			coneAngle		=	lookup->coneAngle;
	int					numRemaining	=	shootStep;
	const float			multiplier		=	1 / (float) lookup->numSamples;
	int					currentSample;
	int					i;
	CTraceBundle		bundle;
	vector				D;

	if (lookup->label == NULL)	bundle.label	=	rayLabelTransmission;
	else						bundle.label	=	lookup->label;

	cRay	=	rayBase		=	(CTraceRay *) ralloc(shootStep*sizeof(CTraceRay),threadMemory);
	cRays	=	raysBase	=	(CTraceRay **) ralloc(shootStep*sizeof(CTraceRay*),threadMemory);

	// Compute the ray differential
	const float	*ab				=	rayDiff(from,dir,NULL);
	const float angleDeviation	=	tanf(coneAngle + C_EPSILON);

	for (i=currentShadingState->numRealVertices;i>0;i--,tags++,ab+=2) {
		if (*tags == 0) {
			normalizev(D,dir);

			initv(dest,0,0,0);
			for (currentSample=numSamples;currentSample>0;currentSample--) {
				sampleHemisphere(cRay->dir,D,coneAngle,random4d);
				if (dotvv(cRay->dir,cRay->dir) > C_EPSILON) {
					movvv(cRay->from,from);
					cRay->time			=	(urand() + currentSample - 1) * multiplier;
					cRay->t				=	C_INFINITY;
					cRay->tmin			=	bias;
					cRay->flags			=	ATTRIBUTES_FLAGS_TRACE_VISIBLE;
					cRay->dest			=	dest;
					cRay->multiplier	=	multiplier;
					cRay->da			=	ab[0] + angleDeviation;		// The ray differential
					cRay->db			=	ab[1];
					*cRays++			=	cRay++;
					if (--numRemaining == 0) {
						numReflectionRays	+=	shootStep;
						bundle.numRays		=	shootStep;
						bundle.rays			=	(CRay **) raysBase;
						bundle.depth		=	0;
						bundle.last			=	0;
						bundle.postShader	=	NULL;
						traceEx(&bundle);
						cRay				=	rayBase;
						cRays				=	raysBase;
						numRemaining		=	shootStep;
					}
				}
			}
		}
		dest	+=	3;
		from	+=	3;
		dir		+=	3;
	}

	if (numRemaining != shootStep) {
		numReflectionRays	+=	shootStep-numRemaining;
		bundle.numRays		=	shootStep-numRemaining;
		bundle.rays			=	(CRay **) raysBase;
		bundle.depth		=	0;
		bundle.last			=	0;
		bundle.postShader	=	NULL;
		traceEx(&bundle);
	}
}








///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	rayDiff
// Description			:	Compute the ray differentials
// Return Value			:	-
// Comments				:
float		*CShadingContext::rayDiff(const float *from,const float *dir,const float *to) {

	// Allocate the return value
	const int	numVertices	=	currentShadingState->numVertices;
	float		*ab			=	(float *) ralloc(numVertices*2*sizeof(float),threadMemory);

	// Compute the direction vector if not already computed
	if (dir == NULL) {
		int		i;

		float	*D		=	(float *) ralloc(numVertices*3*sizeof(float),threadMemory);
		for (i=numVertices;i>0;i--,D+=3,from+=3,to+=3)	subvv(D,to,from);

		D		-=	numVertices*3;
		from	-=	numVertices*3;
		to		-=	numVertices*3;
		dir		=	D;
	}


	switch(currentShadingState->shadingDim) {





		// Dv executing on Points
		case SHADING_0D:
		{

			// Set anyway
			for (int i=numVertices;i>0;i--) {
				*ab++	=	DEFAULT_RAY_DA;
				*ab++	=	DEFAULT_RAY_DB;
			}

			return	ab - numVertices*2;
		}
		break;








		// Dv executing on a 2D grid
		case SHADING_2D_GRID:
		{
			const int	uVertices	=	currentShadingState->numUvertices;
			const int	vVertices	=	currentShadingState->numVvertices;
			int			i,j;

			for (j=0;j<vVertices;j++) {
				for (i=0;i<uVertices;i++) {
					
					const int	ii		=	min(i,uVertices-2);
					const int	jj		=	min(j,vVertices-2);

					// The 4 corners of the current quad
					const float	*cFrom0	=	from + jj*uVertices*3 + ii*3;
					const float	*cFrom1	=	cFrom0 + 3;
					const float	*cFrom2	=	cFrom0 + uVertices*3;
					const float	*cFrom3	=	cFrom2 + 3;

					ab[0]				=	0;
					ab[1]				=	0;

					vector		tmp;
					subvv(tmp,cFrom1,cFrom0);
					ab[1]				+=	lengthv(tmp);
					subvv(tmp,cFrom2,cFrom0);
					ab[1]				+=	lengthv(tmp);
					subvv(tmp,cFrom1,cFrom3);
					ab[1]				+=	lengthv(tmp);
					subvv(tmp,cFrom2,cFrom3);
					ab[1]				+=	lengthv(tmp);

					// The directions at 4 corners of the quad
					const float	*cDir0	=	dir + jj*uVertices*3 + ii*3;
					const float	*cDir1	=	cDir0 + 3;
					const float	*cDir2	=	cDir0 + uVertices*3;
					const float	*cDir3	=	cDir2 + 3;

					float a				=	dotvv(cDir1,cDir0);
					ab[0]				+=	acosf(sqrtf(a*a / (dotvv(cDir0,cDir0)*dotvv(cDir1,cDir1) + C_EPSILON)));

					a					=	dotvv(cDir2,cDir0);
					ab[0]				+=	acosf(sqrtf(a*a / (dotvv(cDir0,cDir0)*dotvv(cDir2,cDir2) + C_EPSILON)));

					a					=	dotvv(cDir3,cDir1);
					ab[0]				+=	acosf(sqrtf(a*a / (dotvv(cDir3,cDir3)*dotvv(cDir1,cDir1) + C_EPSILON)));

					a					=	dotvv(cDir2,cDir3);
					ab[0]				+=	acosf(sqrtf(a*a / (dotvv(cDir2,cDir2)*dotvv(cDir3,cDir3) + C_EPSILON)));

					ab[0]				*=	0.25f;
					ab[1]				*=	0.25f;

					ab[0]				=	tanf(min(ab[0],((float) C_PI)*0.5f - C_EPSILON));
					ab[0]				=	min(ab[0],DEFAULT_RAY_DA);
					
					// guard against bad differentials
				
					if(ab[0] != ab[0]) ab[0]	= 	DEFAULT_RAY_DA;
				
					assert(ab[0] >= 0);
					assert(ab[1] >= 0);

					ab					+=	2;
				}
			}
			
			return ab - uVertices*vVertices*2;
		}
		break;







		// Dv executing on a 2D raytraced surface
		case SHADING_2D:
		{
			const int	numRealVertices	=	currentShadingState->numRealVertices;
			const float	*dfrom			=	from + numRealVertices*3;
			const float	*ddir			=	dir + numRealVertices*3;
			int			i;

			assert(numVertices == numRealVertices*3);

			for (i=numRealVertices;i>0;i--) {
				vector	tmp;

				ab[0]				=	0;
				ab[1]				=	0;

				subvv(tmp,dfrom,from);
				ab[1]				+=	lengthv(tmp);
				subvv(tmp,dfrom + 3,from);
				ab[1]				+=	lengthv(tmp);

				float a;
				a					=	dotvv(dir,ddir);
				ab[0]				+=	acosf(sqrtf(a*a / (dotvv(dir,dir)*dotvv(ddir,ddir) + C_EPSILON)));
				a					=	dotvv(dir,ddir+3);
				ab[0]				+=	acosf(sqrtf(a*a / (dotvv(dir,dir)*dotvv(ddir+3,ddir+3) + C_EPSILON)));
				
				ab[0]				*=	0.5f;
				ab[1]				*=	0.5f;
				ab[0]				=	tanf(min(ab[0],((float) C_PI)*0.5f - C_EPSILON));
				ab[0]				=	min(ab[0],DEFAULT_RAY_DA);
				
				// guard against bad differentials
				
				if(ab[0] != ab[0]) ab[0]	= 	DEFAULT_RAY_DA;

				assert(ab[0] >= 0);
				assert(ab[1] >= 0);

				ab					+=	2;
				from				+=	3;
				dir					+=	3;
				dfrom				+=	6;
				ddir				+=	6;
			}

			return ab - numRealVertices*2;
		}
		break;
	}

	assert(FALSE);
	return NULL;
}



///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	rayDiff
// Description			:	Compute the ray differentials
// Return Value			:	-
// Comments				:
float		*CShadingContext::rayDiff(const float *from) {

	// Allocate the return value
	const int	numVertices	=	currentShadingState->numVertices;
	float		*b			=	(float *) ralloc(numVertices*sizeof(float),threadMemory);


	switch(currentShadingState->shadingDim) {





		// Dv executing on Points
		case SHADING_0D:
		{
			// Set anyway
			for (int i=numVertices;i>0;i--) {
				*b++	=	DEFAULT_RAY_DB;
			}

			return	b - numVertices;
		}
		break;








		// Dv executing on a 2D grid
		case SHADING_2D_GRID:
		{
			const int	uVertices	=	currentShadingState->numUvertices;
			const int	vVertices	=	currentShadingState->numVvertices;
			int			i,j;

			for (j=0;j<vVertices;j++) {
				for (i=0;i<uVertices;i++) {
					
					const int	ii		=	min(i,uVertices-2);
					const int	jj		=	min(j,vVertices-2);

					// The 4 corners of the current quad
					const float	*cFrom0	=	from + jj*uVertices*3 + ii*3;
					const float	*cFrom1	=	cFrom0 + 3;
					const float	*cFrom2	=	cFrom0 + uVertices*3;
					const float	*cFrom3	=	cFrom2 + 3;

					b[0]				=	0;

					vector		tmp;
					subvv(tmp,cFrom1,cFrom0);
					b[0]				+=	lengthv(tmp);
					subvv(tmp,cFrom2,cFrom0);
					b[0]				+=	lengthv(tmp);
					subvv(tmp,cFrom1,cFrom3);
					b[0]				+=	lengthv(tmp);
					subvv(tmp,cFrom2,cFrom3);
					b[0]				+=	lengthv(tmp);

					b[0]				*=	0.25f;
					b++;
				}
			}
			
			return b - uVertices*vVertices;
		}
		break;







		// Dv executing on a 2D raytraced surface
		case SHADING_2D:
		{
			const int	numRealVertices	=	currentShadingState->numRealVertices;
			const float	*dfrom			=	from + numRealVertices*3;
			int			i;

			assert(numVertices == numRealVertices*3);

			for (i=numRealVertices;i>0;i--) {
				vector	tmp;

				b[0]				=	0;

				subvv(tmp,dfrom,from);
				b[0]				+=	lengthv(tmp);
				subvv(tmp,dfrom + 3,from);
				b[0]				+=	lengthv(tmp);
				b[0]				*=	0.5f;

				b++;
				from				+=	3;
				dfrom				+=	6;
			}

			return b - numRealVertices;
		}
		break;
	}

	assert(FALSE);
	return NULL;
}
