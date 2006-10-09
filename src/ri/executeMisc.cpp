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
//  File				:	executeMisc.cpp
//  Classes				:	-
//  Description			:	This file implements the main shader execution
//
////////////////////////////////////////////////////////////////////////
#include <math.h>
#include <float.h>

#include "common/global.h"
#include "bundles.h"
#include "executeMisc.h"
#include "memory.h"
#include "attributes.h"


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
// Date last edited		:	2/4/2003
void	CShadingContext::duFloat(float *dest,const float *src) {
	switch(currentShadingState->shadingDim) {


		// Du executing on Points or Curves (note that curves are defined along v)
		case SHADING_0D:
		case SHADING_1D_GRID:
		case SHADING_1D:
		{
			int		i;
			
			for (i=currentShadingState->numVertices;i>0;i--) {
				*dest++	=	0;
			}
		}
		break;


		// Du executing on a 2D grid
		case SHADING_2D_GRID:
		{
			int			uVertices	=	currentShadingState->numUvertices;
			int			vVertices	=	currentShadingState->numVvertices;
			int			i,j;
			const float	*u			=	currentShadingState->varying[VARIABLE_U];

			for (j=vVertices;j>0;j--) {
				*dest++	=	(src[1] - src[0]) / (u[1] - u[0]);
				src++;
				u++;
				for (i=uVertices-2;i>0;i--) {
					*dest++	=	(src[1] - src[-1]) / (u[1] - u[-1]);
					src++;
					u++;
				}
				*dest++	=	(src[0] - src[-1]) / (u[0] - u[-1]);
				src++;
				u++;
			}
		}
		break;


		// Du executing on a 2D raytraced surface
		case SHADING_2D:
		{
			int			numRealVertices	=	currentShadingState->numRealVertices;
			const float	*dsrc			=	src + numRealVertices;
			float		*ddest			=	dest + numRealVertices;
			const float	*du				=	currentShadingState->varying[VARIABLE_DU];
			int			i;

			for (i=numRealVertices;i>0;i--) {
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
// Date last edited		:	2/4/2003
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

		// Dv executing on Curves
		case SHADING_1D_GRID:
		{
			int			vVertices	=	currentShadingState->numVvertices;
			int			i;
			const float	*v			=	currentShadingState->varying[VARIABLE_V];

			*dest++	=	(src[1] - src[0]) / (v[1] - v[0]);
			src++;
			v++;
			for (i=vVertices-2;i>0;i--) {
				*dest++	=	(src[1] - src[-1]) / (v[1] - v[-1]);
				src++;
				v++;
			}
			*dest	=	(src[0] - src[-1]) / (v[0] - v[-1]);
		}
		break;


		// Dv executing on Curves
		case SHADING_1D:
		{
			int			numVertices		=	currentShadingState->numVertices;
			int			numRealVertices	=	currentShadingState->numRealVertices;
			const float	*dsrc			=	src + numRealVertices;
			float		*ddest			=	dest + numRealVertices;
			const float	*dv				=	currentShadingState->varying[VARIABLE_DV];
			int			i;

			assert(numVertices == numRealVertices*3);

			for (i=numRealVertices;i>0;i--) {
				const float	val	=	(dsrc[0] - src[0]) / (*dv++);

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


		// Dv executing on a 2D grid
		case SHADING_2D_GRID:
		{
			int			uVertices	=	currentShadingState->numUvertices;
			int			vVertices	=	currentShadingState->numVvertices;
			int			i,j;
			const float	*v			=	currentShadingState->varying[VARIABLE_V];

			for (j=0;j<uVertices;j++) {
				float		*cRes	=	dest + j;
				const float	*cOp	=	src + j;
				const float	*cv		=	v + j;
				cRes[0]				=	(cOp[uVertices] - cOp[0]) / (cv[uVertices] - cv[0]);
				cRes				+=	uVertices;
				cOp					+=	uVertices;
				cv					+=	uVertices;

				for (i=vVertices-2;i>0;i--) {
					cRes[0]		=	(cOp[uVertices] - cOp[-uVertices]) / (cv[uVertices] - cv[-uVertices]);
					cRes		+=	uVertices;
					cOp			+=	uVertices;
					cv			+=	uVertices;
				}

				cRes[0]			=	(cOp[0] - cOp[-uVertices]) / (cv[0] - cv[-uVertices]);
			}
		}
		break;

		// Dv executing on a 2D raytraced surface
		case SHADING_2D:
		{
			int			numVertices		=	currentShadingState->numVertices;
			int			numRealVertices	=	currentShadingState->numRealVertices;
			const float	*dsrc			=	src + numRealVertices;
			float		*ddest			=	dest + numRealVertices;
			const float	*dv				=	currentShadingState->varying[VARIABLE_DV];

			assert(numVertices == numRealVertices*3);

			for (int i=numRealVertices;i>0;i--) {
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
// Date last edited		:	2/4/2003
void	CShadingContext::duVector(float *dest,const float *src) {
	switch(currentShadingState->shadingDim) {


		// Du executing on Points or Curves (note that curves are defined along v)
		case SHADING_0D:
		case SHADING_1D_GRID:
		case SHADING_1D:
		{
			int		i;
			
			for (i=currentShadingState->numVertices;i>0;i--) {
				*dest++	=	0;
			}
		}
		break;


		// Du executing on a 2D grid
		case SHADING_2D_GRID:
		{
			int			uVertices	=	currentShadingState->numUvertices;
			int			vVertices	=	currentShadingState->numVvertices;
			int			i,j;
			const float	*u			=	currentShadingState->varying[VARIABLE_U];

			for (j=vVertices;j>0;j--) {
				float	invDu	=	1 / (u[1] - u[0]);
				*dest++	=	(src[3] - src[0]) * invDu;
				*dest++	=	(src[4] - src[1]) * invDu;
				*dest++	=	(src[5] - src[2]) * invDu;
				src		+=	3;
				u++;
				for (i=uVertices-2;i>0;i--) {
					invDu	=	1 / (u[1] - u[-1]);
					*dest++	=	(src[3] - src[-3]) * invDu;
					*dest++	=	(src[4] - src[-2]) * invDu;
					*dest++	=	(src[5] - src[-1]) * invDu;
					src		+=	3;
					u++;
				}

				invDu	=	1 / (u[0] - u[-1]);
				*dest++	=	(src[0] - src[-3]) * invDu;
				*dest++	=	(src[1] - src[-2]) * invDu;
				*dest++	=	(src[2] - src[-1]) * invDu;
				src		+=	3;
				u++;
			}
		}
		break;


		// Du executing on a 2D raytraced surface
		case SHADING_2D:
		{
			int			numRealVertices	=	currentShadingState->numRealVertices;
			const float	*dsrc			=	src + numRealVertices*3;
			float		*ddest			=	dest + numRealVertices*3;
			const float	*du				=	currentShadingState->varying[VARIABLE_DU];
			int			i;

			for (i=numRealVertices;i>0;i--) {
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
// Date last edited		:	2/4/2003
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

		// Dv executing on Curves
		case SHADING_1D_GRID:
		{
			int			vVertices	=	currentShadingState->numVvertices;
			int			i;
			const float	*v			=	currentShadingState->varying[VARIABLE_V];
			float		invDv;

			assert(currentShadingState->numUvertices == 1);
			assert(vVertices > 0);

			invDv	=	1 / (v[1] - v[0]);
			*dest++	=	(src[3] - src[0]) * invDv;
			*dest++	=	(src[4] - src[1]) * invDv;
			*dest++	=	(src[5] - src[2]) * invDv;
			src		+=	3;
			v++;

			for (i=vVertices-2;i>0;i--) {
				invDv	=	1 / (v[1] - v[-1]);
				*dest++	=	(src[3] - src[-3]) * invDv;
				*dest++	=	(src[4] - src[-2]) * invDv;
				*dest++	=	(src[5] - src[-1]) * invDv;
				src		+=	3;
				v++;
			}

			invDv	=	1 / (v[0] - v[-1]);
			*dest++	=	(src[0] - src[-3]) * invDv;
			*dest++	=	(src[1] - src[-2]) * invDv;
			*dest++	=	(src[2] - src[-1]) * invDv;
		}
		break;


		// Dv executing on Curves
		case SHADING_1D:
		{
			int			numVertices		=	currentShadingState->numVertices;
			int			numRealVertices	=	currentShadingState->numRealVertices;
			const float	*dsrc			=	src + numRealVertices*3;
			float		*ddest			=	dest + numRealVertices*3;
			const float	*dv				=	currentShadingState->varying[VARIABLE_DV];
			int			i;

			assert(numVertices == numRealVertices*3);

			for (i=numRealVertices;i>0;i--) {
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


		// Dv executing on a 2D grid
		case SHADING_2D_GRID:
		{
			int			uVertices	=	currentShadingState->numUvertices;
			int			vVertices	=	currentShadingState->numVvertices;
			int			i,j;
			const float	*v			=	currentShadingState->varying[VARIABLE_V];

			for (j=0;j<uVertices;j++) {
				float		invDv;
				float		*cRes	=	dest + j*3;
				const float	*cOp	=	src + j*3;
				const float	*cv		=	v + j;

				invDv				=	1 / (cv[uVertices] - cv[0]);

				cRes[0]				=	(cOp[uVertices*3+0] - cOp[0]) * invDv;
				cRes[1]				=	(cOp[uVertices*3+1] - cOp[1]) * invDv;
				cRes[2]				=	(cOp[uVertices*3+2] - cOp[2]) * invDv;
				cRes				+=	uVertices*3;
				cOp					+=	uVertices*3;
				cv					+=	uVertices;

				for (i=vVertices-2;i>0;i--) {
					invDv			=	1 / (cv[uVertices] - cv[-uVertices]);

					cRes[0]			=	(cOp[uVertices*3+0] - cOp[-uVertices*3+0]) * invDv;
					cRes[1]			=	(cOp[uVertices*3+1] - cOp[-uVertices*3+1]) * invDv;
					cRes[2]			=	(cOp[uVertices*3+2] - cOp[-uVertices*3+2]) * invDv;
					cRes			+=	uVertices*3;
					cOp				+=	uVertices*3;
					cv				+=	uVertices;
				}

				invDv				=	1 / (cv[0] - cv[-uVertices]);
				cRes[0]				=	(cOp[0] - cOp[-uVertices*3+0]) * invDv;
				cRes[1]				=	(cOp[1] - cOp[-uVertices*3+1]) * invDv;
				cRes[2]				=	(cOp[2] - cOp[-uVertices*3+2]) * invDv;
			}
		}
		break;

		// Dv executing on a 2D raytraced surface
		case SHADING_2D:
		{
			int			numVertices		=	currentShadingState->numVertices;
			int			numRealVertices	=	currentShadingState->numRealVertices;
			const float	*dsrc			=	src + numRealVertices*3;
			float		*ddest			=	dest + numRealVertices*3;
			const float	*dv				=	currentShadingState->varying[VARIABLE_DV];
			int			i;

			assert(numVertices == numRealVertices*3);

			for (i=numRealVertices;i>0;i--) {
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


///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	traceTransmission
// Description			:	Trace transmission rays
// Return Value			:	-
// Comments				:
// Date last edited		:	3/23/2003
void	CShadingContext::traceTransmission(float *dest,const float *from,const float *L,int numVertices,int *tags,CTextureLookup *lookup) {
	CTransmissionRay	*rayBase;
	CTransmissionRay	**raysBase;
	CTransmissionRay	*cRay,**cRays;
	const int			numSamples		=	lookup->numSamples;
	const float			bias			=	lookup->shadowBias;
	const int			shootStep		=	min(this->shootStep,numVertices*numSamples);
	const float			coneAngle		=	lookup->coneAngle;
	const float			maxDist			=	lookup->maxDist;
	int					numRemaining	=	shootStep;
	const float			multiplier		=	1 / (float) lookup->numSamples;
	int					currentSample;
	int					i;
	CTransmissionBundle	bundle;
	vector				dir;

	if (lookup->label == NULL)	bundle.label	=	rayLabelTransmission;
	else						bundle.label	=	lookup->label;

	// Allocate the memory for the transmission rays
	cRay	=	rayBase		=	(CTransmissionRay *) ralloc(shootStep*sizeof(CTransmissionRay));
	cRays	=	raysBase	=	(CTransmissionRay **) ralloc(shootStep*sizeof(CTransmissionRay*));

	inShadow		=	TRUE;					// We're in shadow

	// Create the rays
	for (i=currentShadingState->numRealVertices;i>0;i--,tags++) {
		if (*tags == 0) {
			const	float	d	=	lengthv(L);
			mulvf(dir,L,-1/d);

			initv(dest,0,0,0);	// Clear the transmission

			// Create the samples
			for (currentSample=numSamples;currentSample>0;currentSample--) {
				// Sample a point in the cone
				sampleHemisphere(cRay->dir,dir,coneAngle,transmissionGenerator);
				movvv(cRay->from,from);
				cRay->t				=	min(maxDist,d) - bias;
				cRay->tmin			=	bias;
				cRay->time			=	urand();
				cRay->flags			=	ATTRIBUTES_FLAGS_TRANSMISSION_VISIBLE;
				cRay->dest			=	dest;
				cRay->multiplier	=	multiplier;
				*cRays++			=	cRay++;
				if (--numRemaining == 0) {
					bundle.numRays	=	shootStep;
					bundle.rays		=	(CRay **) raysBase;
					bundle.depth	=	0;
					bundle.last		=	0;
					bundle.postShader	=	NULL;
					traceEx(&bundle);
					cRay			=	rayBase;
					cRays			=	raysBase;
					numRemaining	=	shootStep;
				}
			}
		}
		dest	+=	3;
		from	+=	3;
		L		+=	3;
	}

	if (numRemaining != shootStep) {
		bundle.numRays	=	shootStep-numRemaining;
		bundle.rays		=	(CRay **) raysBase;
		bundle.depth	=	0;
		bundle.last		=	0;
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
// Date last edited		:	3/23/2003
void	CShadingContext::traceReflection(float *dest,const float *from,const float *dir,int numVertices,int *tags,CTextureLookup *lookup) {
	CTraceRay			*rayBase;
	CTraceRay			**raysBase;
	CTraceRay			*cRay,**cRays;
	const int			numSamples		=	lookup->numSamples;
	const float			bias			=	lookup->shadowBias;
	const int			shootStep		=	min(this->shootStep,numVertices*numSamples);
	const float			coneAngle		=	lookup->coneAngle;
	int					numRemaining	=	shootStep;
	const float			multiplier		=	1 / (float) lookup->numSamples;
	int					currentSample;
	int					i;
	CTraceBundle		bundle;
	vector				D;

	if (lookup->label == NULL)	bundle.label	=	rayLabelTransmission;
	else						bundle.label	=	lookup->label;

	cRay	=	rayBase		=	(CTraceRay *) ralloc(shootStep*sizeof(CTraceRay));
	cRays	=	raysBase	=	(CTraceRay **) ralloc(shootStep*sizeof(CTraceRay*));

	for (i=currentShadingState->numRealVertices;i>0;i--,tags++) {
		if (*tags == 0) {
			normalizev(D,dir);

			initv(dest,0,0,0);
			for (currentSample=numSamples;currentSample>0;currentSample--) {
				sampleHemisphere(cRay->dir,D,coneAngle,traceGenerator);
				movvv(cRay->from,from);
				cRay->time			=	urand();
				cRay->t				=	C_INFINITY;
				cRay->tmin			=	bias;
				cRay->flags			=	ATTRIBUTES_FLAGS_TRACE_VISIBLE;
				cRay->dest			=	dest;
				cRay->multiplier	=	multiplier;
				*cRays++			=	cRay++;
				if (--numRemaining == 0) {
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
		dest	+=	3;
		from	+=	3;
		dir		+=	3;
	}

	if (numRemaining != shootStep) {
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
// Method				:	traceTransmission
// Description			:	Trace transmission rays
// Return Value			:	-
// Comments				:
// Date last edited		:	3/23/2003
void	CShadingContext::traceTransmission(int numVertices,CRaySample *samples,CTextureLookup *lookup) {
	CTransmissionRay	*rayBase;
	CTransmissionRay	**raysBase;
	CTransmissionRay	*cRay,**cRays;
	const int			numSamples		=	lookup->numSamples;
	const float			bias			=	lookup->shadowBias;
	const int			shootStep		=	min(this->shootStep,numVertices*numSamples);
	const float			coneAngle		=	lookup->coneAngle;
	const float			maxDist			=	lookup->maxDist;
	int					numRemaining	=	shootStep;
	const float			multiplier		=	1 / (float) lookup->numSamples;
	int					currentSample;
	int					i;
	CTransmissionBundle	bundle;
	vector				L,D;

	// Set the label
	if (lookup->label == NULL)	bundle.label	=	rayLabelTransmission;
	else						bundle.label	=	lookup->label;

	// Allocate the memory for the transmission rays
	cRay	=	rayBase		=	(CTransmissionRay *) ralloc(shootStep*sizeof(CTransmissionRay));
	cRays	=	raysBase	=	(CTransmissionRay **) ralloc(shootStep*sizeof(CTransmissionRay*));

	// We're in shadow
	inShadow				=	TRUE;

	// Create the rays
	for (i=numVertices;i>0;i--,samples++) {
		subvv(L,samples->to,samples->from);
		const	float	d	=	lengthv(L);
		mulvf(D,L,1/d);

		// Clear the transmission
		initv(samples->res,0,0,0);

		// Create the samples
		for (currentSample=numSamples;currentSample>0;currentSample--) {
			// Sample a point in the cone
			sampleCosineHemisphere(cRay->dir,D,coneAngle,transmissionGenerator);
			movvv(cRay->from,samples->from);
			cRay->t				=	min(maxDist,d) - bias;
			cRay->tmin			=	bias;
			cRay->time			=	urand();
			cRay->flags			=	ATTRIBUTES_FLAGS_TRANSMISSION_VISIBLE;
			cRay->dest			=	samples->res;
			cRay->multiplier	=	multiplier;
			*cRays++			=	cRay++;
			if (--numRemaining == 0) {
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

	// Shoot the remaining rays
	if (numRemaining != shootStep) {
		bundle.numRays		=	shootStep-numRemaining;
		bundle.rays			=	(CRay **) raysBase;
		bundle.depth		=	0;
		bundle.last			=	0;
		bundle.postShader	=	NULL;
		traceEx(&bundle);
	}

	// We're not in shadow anymore
	inShadow		=	FALSE;
}



///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	traceReflection
// Description			:	Trace reflection rays
// Return Value			:	-
// Comments				:
// Date last edited		:	3/23/2003
void	CShadingContext::traceReflection(int numVertices,CRaySample *samples,CTextureLookup *lookup) {
	CTraceRay			*rayBase;
	CTraceRay			**raysBase;
	CTraceRay			*cRay,**cRays;
	const int			numSamples		=	lookup->numSamples;
	const float			bias			=	lookup->shadowBias;
	const int			shootStep		=	min(this->shootStep,numVertices*numSamples);
	const float			coneAngle		=	lookup->coneAngle;
	int					numRemaining	=	shootStep;
	const float			multiplier		=	1 / (float) lookup->numSamples;
	int					currentSample;
	int					i;
	CTraceBundle		bundle;
	vector				D;

	// Set the label
	if (lookup->label == NULL)	bundle.label	=	rayLabelTransmission;
	else						bundle.label	=	lookup->label;

	// Allocate the memory
	cRay	=	rayBase		=	(CTraceRay *) ralloc(shootStep*sizeof(CTraceRay));
	cRays	=	raysBase	=	(CTraceRay **) ralloc(shootStep*sizeof(CTraceRay*));

	// Shoot the rays
	for (i=numVertices;i>0;i--,samples++) {
		subvv(D,samples->to,samples->from);
		normalizev(D);
		initv(samples->res,0);

		for (currentSample=numSamples;currentSample>0;currentSample--) {
			sampleCosineHemisphere(cRay->dir,D,coneAngle,traceGenerator);
			movvv(cRay->from,samples->from);
			cRay->time			=	urand();
			cRay->t				=	C_INFINITY;
			cRay->tmin			=	bias;
			cRay->flags			=	ATTRIBUTES_FLAGS_TRACE_VISIBLE;
			cRay->dest			=	samples->res;
			cRay->multiplier	=	multiplier;
			*cRays++			=	cRay++;
			if (--numRemaining == 0) {
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

	// Shoot any remaining rays
	if (numRemaining != shootStep) {
		bundle.numRays		=	shootStep-numRemaining;
		bundle.rays			=	(CRay **) raysBase;
		bundle.depth		=	0;
		bundle.last			=	0;
		bundle.postShader	=	NULL;
		traceEx(&bundle);
	}

}


