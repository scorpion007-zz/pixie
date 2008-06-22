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
#include "surface.h"
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
		{
			for (int j=currentShadingState->numVertices;j>0;--j) {
				*dest++ = 0;
			}
		}
		break;


		// Du executing on a 2D grid
		case SHADING_2D_GRID:
		{
			const int	uVertices	=	currentShadingState->numUvertices;
			const int	vVertices	=	currentShadingState->numVvertices;
			const float	*u			=	currentShadingState->varying[VARIABLE_U];

			assert(uVertices >= 2);
			assert(vVertices >= 2);
			assert(u[1] > u[0]);

			// These values are constant accross a grid
			const double	invDu1		=	1.0 / ((double)u[1] - (double)u[0]);
			const double	invDu2		=	1.0 / (2.0*((double)u[1] - (double)u[0]));

			// Compute the Du
			for (int j=vVertices;j>0;--j) {

				// Forward differencing
				*dest++	=	(float) (((double)src[1] - (double)src[0]) * invDu1);
				++src;

				// Central differencing
				for (int i=uVertices-2;i>0;--i) {
					*dest++	=	(float) (((double)src[1] - (double)src[-1]) * invDu2);
					++src;
				}

				// Backward differencing
				*dest++	=	(float) (((double)src[0] - (double)src[-1]) * invDu1);
				++src;
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

			for (int i=numRealVertices;i>0;--i) {

				assert(*du != 0);

				const float	val	=	(float) (((double)dsrc[0] - (double)src[0]) / ((double)*du++));

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
// Method				:	DuFloat
// Description			:	Compute the u differences
// Return Value			:	-
// Comments				:
void	CShadingContext::DuFloat(float *dest,const float *src) {
	switch(currentShadingState->shadingDim) {


		// Du executing on Points or Curves (note that curves are defined along v)
		case SHADING_0D:
		{
			for (int j=currentShadingState->numVertices;j>0;--j) {
				*dest++ = 0;
			}
		}
		break;


		// Du executing on a 2D grid
		case SHADING_2D_GRID:
		{
			const int	uVertices	=	currentShadingState->numUvertices;
			const int	vVertices	=	currentShadingState->numVvertices;

			assert(uVertices >= 2);
			assert(vVertices >= 2);

			// Compute the Du
			for (int j=vVertices;j>0;--j) {

				// Forward differencing
				*dest++	=	(float) ((double)src[1] - (double)src[0]);
				src++;

				// Central differencing
				for (int i=uVertices-2;i>0;--i) {
					*dest++	=	(float) (((double)src[1] - (double)src[-1]) * 0.5);
					src++;
				}

				// Backward differencing
				*dest++	=	(float) ((double)src[0] - (double)src[-1]);
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

			for (int i=numRealVertices;i>0;--i) {

				const float	val	=	(float) ((double)dsrc[0] - (double)src[0]);

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
// Description			:	Compute the v derivatives
// Return Value			:	-
// Comments				:
void	CShadingContext::dvFloat(float *dest,const float *src) {

	switch(currentShadingState->shadingDim) {

		// Dv executing on Points
		case SHADING_0D:
		{
			for (int i=currentShadingState->numVertices;i>0;--i) {
				*dest++	=	0;
			}
		}
		break;


		// Dv executing on a 2D grid
		case SHADING_2D_GRID:
		{
			const int		uVertices	=	currentShadingState->numUvertices;
			const int		vVertices	=	currentShadingState->numVvertices;
			const float		*v			=	currentShadingState->varying[VARIABLE_V];

			assert(uVertices >= 2);
			assert(vVertices >= 2);
			assert(v[uVertices] > v[0]);

			const double	invDv1		=	1.0 / ((double)v[uVertices] - (double)v[0]);
			const double	invDv2		=	1.0 / (2.0*((double)v[uVertices] - (double)v[0]));

			// Compute the DV
			for (int j=0;j<uVertices;++j) {
				float		*cRes	=	dest + j;
				const float	*cOp	=	src + j;

				// Forward differencing
				cRes[0]				=	(float) ((double)(cOp[uVertices] - (double)cOp[0]) * invDv1);
				cRes				+=	uVertices;
				cOp					+=	uVertices;

				// Central differencing
				for (int i=vVertices-2;i>0;--i) {
					cRes[0]			=	(float) (((double)cOp[uVertices] - (double)cOp[-uVertices]) * invDv2);
					cRes			+=	uVertices;
					cOp				+=	uVertices;
				}

				// Backward differencing
				cRes[0]				=	(float) (((double)cOp[0] - (double)cOp[-uVertices]) * invDv1);
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

			for (int i=numRealVertices;i>0;--i) {

				assert(*dv != 0);

				const float	val	=	(float) (((double)dsrc[1] - (double)src[0]) / ((double)*dv++));

				ddest[0]		=	val;
				ddest[1]		=	val;
				dest[0]			=	val;

				++dest;
				++src;
				ddest			+=	2;
				dsrc			+=	2;
			}
		}
		break;
	}
}




///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	DvFloat
// Description			:	Compute the v differences
// Return Value			:	-
// Comments				:
void	CShadingContext::DvFloat(float *dest,const float *src) {

	switch(currentShadingState->shadingDim) {

		// Dv executing on Points
		case SHADING_0D:
		{
			for (int i=currentShadingState->numVertices;i>0;--i) {
				*dest++	=	0;
			}
		}
		break;


		// Dv executing on a 2D grid
		case SHADING_2D_GRID:
		{
			const int		uVertices	=	currentShadingState->numUvertices;
			const int		vVertices	=	currentShadingState->numVvertices;

			assert(uVertices >= 2);
			assert(vVertices >= 2);

			// Compute the DV
			for (int j=0;j<uVertices;++j) {
				float		*cRes	=	dest + j;
				const float	*cOp	=	src + j;

				// Forward differencing
				cRes[0]				=	(float) ((double)cOp[uVertices] - (double)cOp[0]);
				cRes				+=	uVertices;
				cOp					+=	uVertices;

				// Central differencing
				for (int i=vVertices-2;i>0;--i) {
					cRes[0]			=	(float) (((double)cOp[uVertices] - (double)cOp[-uVertices]) * 0.5);
					cRes			+=	uVertices;
					cOp				+=	uVertices;
				}

				// Backward differencing
				cRes[0]				=	(float) ((double)cOp[0] - (double)cOp[-uVertices]);
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

			assert(numVertices == numRealVertices*3);

			for (int i=numRealVertices;i>0;--i) {

				const float	val	=	(float) ((double)dsrc[1] - (double)src[0]);

				ddest[0]		=	val;
				ddest[1]		=	val;
				dest[0]			=	val;

				++dest;
				++src;
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
		{
			for (int j=currentShadingState->numVertices;j>0;--j) {
				initv(dest,0);
				dest+=3;
			}
		}
		break;


		// Du executing on a 2D grid
		case SHADING_2D_GRID:
		{
			const int		uVertices	=	currentShadingState->numUvertices;
			const int		vVertices	=	currentShadingState->numVvertices;
			const float		*u			=	currentShadingState->varying[VARIABLE_U];

			assert(uVertices >= 2);
			assert(vVertices >= 2);
			assert(u[1] > u[0]);

			const double	invDu1		=	1.0 / ((double)u[1] - (double)u[0]);
			const double	invDu2		=	1.0 / (2.0*((double)u[1] - (double)u[0]));			

			for (int j=vVertices;j>0;--j) {

				// Use forward difference
				*dest++	=	(float) (((double)src[3] - (double)src[0]) * invDu1);
				*dest++	=	(float) (((double)src[4] - (double)src[1]) * invDu1);
				*dest++	=	(float) (((double)src[5] - (double)src[2]) * invDu1);
				src		+=	3;

				// Use central difference
				for (int i=uVertices-2;i>0;--i) {
					*dest++	=	(float) (((double)src[3] - (double)src[-3]) * invDu2);
					*dest++	=	(float) (((double)src[4] - (double)src[-2]) * invDu2);
					*dest++	=	(float) (((double)src[5] - (double)src[-1]) * invDu2);
					src		+=	3;
				}

				// Use backward difference
				*dest++	=	(float) (((double)src[0] - (double)src[-3]) * invDu1);
				*dest++	=	(float) (((double)src[1] - (double)src[-2]) * invDu1);
				*dest++	=	(float) (((double)src[2] - (double)src[-1]) * invDu1);
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

			for (int i=numRealVertices;i>0;--i) {

				assert(*du != 0);

				const double invDu	=	1 / ((double)*du++);
				const float	val0	=	(float) (((double)dsrc[0] - (double)src[0]) * invDu);
				const float	val1	=	(float) (((double)dsrc[1] - (double)src[1]) * invDu);
				const float	val2	=	(float) (((double)dsrc[2] - (double)src[2]) * invDu);

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
// Method				:	DuVector
// Description			:	Compute the u differences
// Return Value			:	-
// Comments				:
void	CShadingContext::DuVector(float *dest,const float *src) {
	switch(currentShadingState->shadingDim) {


		// Du executing on Points or Curves (note that curves are defined along v)
		case SHADING_0D:
		{
			for (int j=currentShadingState->numVertices;j>0;--j) {
				initv(dest,0);
				dest+=3;
			}
		}
		break;


		// Du executing on a 2D grid
		case SHADING_2D_GRID:
		{
			const int		uVertices	=	currentShadingState->numUvertices;
			const int		vVertices	=	currentShadingState->numVvertices;

			assert(uVertices >= 2);
			assert(vVertices >= 2);

			for (int j=vVertices;j>0;--j) {

				// Use forward difference
				*dest++	=	(float) ((double)src[3] - (double)src[0]);
				*dest++	=	(float) ((double)src[4] - (double)src[1]);
				*dest++	=	(float) ((double)src[5] - (double)src[2]);
				src		+=	3;

				// Use central difference
				for (int i=uVertices-2;i>0;--i) {
					*dest++	=	(float) (((double)src[3] - (double)src[-3]) * 0.5);
					*dest++	=	(float) (((double)src[4] - (double)src[-2]) * 0.5);
					*dest++	=	(float) (((double)src[5] - (double)src[-1]) * 0.5);
					src		+=	3;
				}

				// Use backward difference
				*dest++	=	(float) ((double)src[0] - (double)src[-3]);
				*dest++	=	(float) ((double)src[1] - (double)src[-2]);
				*dest++	=	(float) ((double)src[2] - (double)src[-1]);
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

			for (int i=numRealVertices;i>0;--i) {

				const float	val0	=	(float) ((double)dsrc[0] - (double)src[0]);
				const float	val1	=	(float) ((double)dsrc[1] - (double)src[1]);
				const float	val2	=	(float) ((double)dsrc[2] - (double)src[2]);

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
			for (int i=currentShadingState->numVertices;i>0;--i) {
				initv(dest,0);
				dest+=3;
			}
		}
		break;
		
		// Dv executing on a 2D grid
		case SHADING_2D_GRID:
		{
			const int		uVertices	=	currentShadingState->numUvertices;
			const int		vVertices	=	currentShadingState->numVvertices;
			const float		*v			=	currentShadingState->varying[VARIABLE_V];

			assert(uVertices >= 2);
			assert(vVertices >= 2);
			assert(v[uVertices] > v[0]);

			const double	invDv1		=	1.0 / ((double)v[uVertices] - (double)v[0]);
			const double	invDv2		=	1.0 / (2.0*((double)v[uVertices] - (double)v[0]));
			
			for (int j=0;j<uVertices;++j) {
				float		*cRes	=	dest + j*3;
				const float	*cOp	=	src + j*3;

				// Forward differencing
				cRes[0]				=	(float) (((double)cOp[uVertices*3+0] - (double)cOp[0]) * invDv1);
				cRes[1]				=	(float) (((double)cOp[uVertices*3+1] - (double)cOp[1]) * invDv1);
				cRes[2]				=	(float) (((double)cOp[uVertices*3+2] - (double)cOp[2]) * invDv1);
				cRes				+=	uVertices*3;
				cOp					+=	uVertices*3;

				// Central differencing
				for (int i=vVertices-2;i>0;--i) {
					cRes[0]			=	(float) (((double)cOp[uVertices*3+0] - (double)cOp[-uVertices*3+0]) * invDv2);
					cRes[1]			=	(float) (((double)cOp[uVertices*3+1] - (double)cOp[-uVertices*3+1]) * invDv2);
					cRes[2]			=	(float) (((double)cOp[uVertices*3+2] - (double)cOp[-uVertices*3+2]) * invDv2);
					cRes			+=	uVertices*3;
					cOp				+=	uVertices*3;
				}

				// Backward differencing
				cRes[0]				=	(float) (((double)cOp[0] - (double)cOp[-uVertices*3+0]) * invDv1);
				cRes[1]				=	(float) (((double)cOp[1] - (double)cOp[-uVertices*3+1]) * invDv1);
				cRes[2]				=	(float) (((double)cOp[2] - (double)cOp[-uVertices*3+2]) * invDv1);
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

			assert(numVertices == numRealVertices*3);

			for (int i=numRealVertices;i>0;--i) {

				assert(*dv > 0);

				const double invDv	=	1 / ((double)*dv++);
				const float	val0	=	(float) (((double)dsrc[3] - (double)src[0]) * invDv);
				const float	val1	=	(float) (((double)dsrc[4] - (double)src[1]) * invDv);
				const float	val2	=	(float) (((double)dsrc[5] - (double)src[2]) * invDv);

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
// Method				:	DvVector
// Description			:	Compute the v differences
// Return Value			:	-
// Comments				:
void	CShadingContext::DvVector(float *dest,const float *src) {
	switch(currentShadingState->shadingDim) {

		// Dv executing on Points
		case SHADING_0D:
		{
			for (int i=currentShadingState->numVertices;i>0;--i) {
				initv(dest,0);
				dest+=3;
			}
		}
		break;
		
		// Dv executing on a 2D grid
		case SHADING_2D_GRID:
		{
			const int		uVertices	=	currentShadingState->numUvertices;
			const int		vVertices	=	currentShadingState->numVvertices;

			assert(uVertices >= 2);
			assert(vVertices >= 2);

			for (int j=0;j<uVertices;++j) {
				float		*cRes	=	dest + j*3;
				const float	*cOp	=	src + j*3;

				// Forward differencing
				cRes[0]				=	(float) ((double)cOp[uVertices*3+0] - (double)cOp[0]);
				cRes[1]				=	(float) ((double)cOp[uVertices*3+1] - (double)cOp[1]);
				cRes[2]				=	(float) ((double)cOp[uVertices*3+2] - (double)cOp[2]);
				cRes				+=	uVertices*3;
				cOp					+=	uVertices*3;

				// Central differencing
				for (int i=vVertices-2;i>0;--i) {
					cRes[0]			=	(float) (((double)cOp[uVertices*3+0] - (double)cOp[-uVertices*3+0]) * 0.5);
					cRes[1]			=	(float) (((double)cOp[uVertices*3+1] - (double)cOp[-uVertices*3+1]) * 0.5);
					cRes[2]			=	(float) (((double)cOp[uVertices*3+2] - (double)cOp[-uVertices*3+2]) * 0.5);
					cRes			+=	uVertices*3;
					cOp				+=	uVertices*3;
				}

				// Backward differencing
				cRes[0]				=	(float) ((double)cOp[0] - (double)cOp[-uVertices*3+0]);
				cRes[1]				=	(float) ((double)cOp[1] - (double)cOp[-uVertices*3+1]);
				cRes[2]				=	(float) ((double)cOp[2] - (double)cOp[-uVertices*3+2]);
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

			assert(numVertices == numRealVertices*3);

			for (int i=numRealVertices;i>0;--i) {

				const float	val0	=	(float) ((double)dsrc[3] - (double)src[0]);
				const float	val1	=	(float) ((double)dsrc[4] - (double)src[1]);
				const float	val2	=	(float) ((double)dsrc[5] - (double)src[2]);

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









// Common code for trace transmission and trace reflection
// Note: we are including the cone angle tangent here because
// there's no point finely tesselating if we have a large coneangle blur
#define	computeRayDifferentials																		\
	const float lD	=	lengthv(rays->D);															\
	const float	da	=	((lengthv(rays->dDdu) + lengthv(rays->dDdv))*0.5f + lD*tanConeAngle) / lD;	\
	const float	db	=	(lengthv(rays->dPdu) + lengthv(rays->dPdv))*0.5f;

// Should we be using only ray-orthogonal components?
/*
	vector t1,t2,nD;																				\
	mulvf(t1,rays->dDdu,dotvv(rays->dDdu,rays->D)/lD);												\
	subvv(t1,rays->dDdu,t1);																		\
	mulvf(t2,rays->dDdv,dotvv(rays->dDdv,rays->D)/lD);												\
	subvv(t2,rays->dDdv,t2);																		\
	const float	da	=	((lengthv(t1) + lengthv(t2))*0.5f + lD*tanConeAngle) / lD;	\
	const float	db	=	(lengthv(rays->dPdu) + lengthv(rays->dPdv))*0.5f;
*/

#define	sampleRay(__from,__dir)				\
	vector	tmp0,tmp1;						\
	mulvf(tmp0,rays->dPdu,(urand()-0.5f)*rays->sampleBase);	\
	mulvf(tmp1,rays->dPdv,(urand()-0.5f)*rays->sampleBase);	\
	addvv(__from,tmp0,tmp1);				\
	addvv(__from,rays->P);					\
	mulvf(tmp0,rays->dDdu,urand()-0.5f);	\
	mulvf(tmp1,rays->dDdv,urand()-0.5f);	\
	addvv(__dir,tmp0,tmp1);					\
	addvv(__dir,rays->D);

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	traceTransmission
// Description			:	Trace transmission rays
// Return Value			:	-
// Comments				:
void	CShadingContext::traceTransmission(int numRays,CTraceLocation *rays,int probeOnly) {
	CTransmissionRay		*rayBase;
	CTransmissionRay		**raysBase;
	CTransmissionRay		*cRay,**cRays;
	const CShadingScratch	*scratch		=	&(currentShadingState->scratch);
	const int				shootStep		=	CRenderer::shootStep;
	int						numRemaining	=	shootStep;
	CTransmissionBundle		bundle;

	// Set the ray label we're tracing
	if ((bundle.label = scratch->traceParams.label) == NULL)	bundle.label	=	rayLabelTransmission;

	// Allocate temp memory
	cRay	=	rayBase		=	(CTransmissionRay *) ralloc(shootStep*sizeof(CTransmissionRay),threadMemory);
	cRays	=	raysBase	=	(CTransmissionRay **) ralloc(shootStep*sizeof(CTransmissionRay*),threadMemory);

	// We can not be in shadow at this stage
	assert(inShadow == FALSE);

	// We're in shadow
	inShadow		=	TRUE;

	// Are we sampling the motion in the reflections?
	const int	sampleMotion	=	currentShadingState->currentObject->attributes->flags & ATTRIBUTES_FLAGS_SAMPLEMOTION;
	
	// For each ray
	for (int i=numRays;i>0;--i,++rays) {
		const int			numSamples		=	rays->numSamples;
		const float			coneAngle		=	rays->coneAngle;
		const float			tanConeAngle	=	min(fabsf(tanf(coneAngle)),1.0f);
		const float			multiplier		=	1 / (float) numSamples;

		// Compute the ray differentials
		computeRayDifferentials;

		// Clear the transmission
		initv(rays->C,0,0,0);
		rays->t	=	0;

		// Sample
		for (int currentSample=numSamples;currentSample>0;--currentSample) {
			vector	from,L,dir;

			// Sample the ray
			sampleRay(from,L);
			subvv(L,from);
			const	float	d	=	lengthv(L);
			mulvf(dir,L,1/d);

			// Sample a point in the cone
			sampleHemisphere(cRay->dir,dir,coneAngle,random4d);
			if (dotvv(cRay->dir,cRay->dir) > C_EPSILON) {

				movvv(cRay->from,from);
				cRay->t				=	min(rays->maxDist,d) - rays->bias;
				cRay->tmin			=	rays->bias;
				if (sampleMotion)	cRay->time	=	(urand() + currentSample - 1) * multiplier;
				else				cRay->time	=	rays->time;
				cRay->flags			=	ATTRIBUTES_FLAGS_TRANSMISSION_VISIBLE;
				cRay->dest			=	rays->C;
				cRay->multiplier	=	multiplier;
				cRay->da			=	da;		// The ray differential
				cRay->db			=	db;

				// Are we shooting this ray for real?
				if (probeOnly) {

					// No, just query an intersection and record the distance
					trace(cRay);
					rays->t					+=	cRay->t*multiplier;
				} else {
					*cRays++				=	cRay++;
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
	}

	// Finish the bundle
	if (numRemaining != shootStep) {
		numTransmissionRays	+=	shootStep-numRemaining;
		bundle.numRays		=	shootStep-numRemaining;
		bundle.rays			=	(CRay **) raysBase;
		bundle.depth		=	0;
		bundle.last			=	0;
		bundle.postShader	=	NULL;
		traceEx(&bundle);
	}
	
	inShadow		=	FALSE;			// We're no longer in shadow
}

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	traceReflection
// Description			:	Trace reflected rays
// Return Value			:	-
// Comments				:
void	CShadingContext::traceReflection(int numRays,CTraceLocation *rays,int probeOnly) {
	CTraceRay				*interiorRayBase,*cInteriorRay;
	CTraceRay				*exteriorRayBase,*cExteriorRay;
	CTraceRay				**interiorRaysBase,**exteriorRaysBase,**cInteriorRays,**cExteriorRays;
	const CShadingScratch	*scratch				=	&(currentShadingState->scratch);
	const int				shootStep				=	CRenderer::shootStep;
	int						numInteriorRemaining	=	shootStep;
	int						numExteriorRemaining	=	shootStep;
	CTraceBundle			interiorBundle,exteriorBundle;

	// Verify atmosphere shaders
	CAttributes *cAttr				=	currentShadingState->currentObject->attributes;
	CShaderInstance *interiorShader	=	cAttr->interior;
	CShaderInstance *exteriorShader	=	cAttr->exterior;
	
	// Set the ray label
	if (scratch->traceParams.label == NULL)	{
		exteriorBundle.label	=	rayLabelTransmission;
		interiorBundle.label	=	rayLabelTransmission;
	} else {
		exteriorBundle.label	=	scratch->traceParams.label;
		interiorBundle.label	=	scratch->traceParams.label;
	}
	
	// Allocate temp memory
	cExteriorRay	=	exteriorRayBase			=	(CTraceRay *) ralloc(shootStep*sizeof(CTraceRay),threadMemory);
	cExteriorRays	=	exteriorRaysBase		=	(CTraceRay **) ralloc(shootStep*sizeof(CTraceRay*),threadMemory);
	
	if (interiorShader != exteriorShader) {
		cInteriorRay	=	interiorRayBase		=	(CTraceRay *) ralloc(shootStep*sizeof(CTraceRay),threadMemory);
		cInteriorRays	=	interiorRaysBase	=	(CTraceRay **) ralloc(shootStep*sizeof(CTraceRay*),threadMemory);
	}
	
	// Are we sampling the motion in the reflections?
	const int	sampleMotion	=	cAttr->flags & ATTRIBUTES_FLAGS_SAMPLEMOTION;
	
	// For each ray
	for (int i=numRays;i>0;--i,++rays) {
		const int			numSamples		=	rays->numSamples;
		const float			coneAngle		=	rays->coneAngle;
		const float			tanConeAngle	=	min(fabsf(tanf(coneAngle)),1.0f);
		const float			multiplier		=	1 / (float) numSamples;
		
		// Compute the ray differentials
		computeRayDifferentials;

		// Clear the reflection
		initv(rays->C,0,0,0);
		rays->t	=	0;

		// Sample
		for (int currentSample=numSamples;currentSample>0;--currentSample) {
			vector	from,D,dir;
			
			sampleRay(from,D);

			normalizev(D);

			sampleHemisphere(dir,D,coneAngle,random4d);
			if (dotvv(dir,dir) > C_EPSILON) {
				CTraceRay *cRay;
				int isExterior = (dotvv(dir,rays->N) > 0) || (interiorShader == exteriorShader);			
				
				if (isExterior) cRay = cExteriorRay;
				else			cRay = cInteriorRay;
				
				movvv(cRay->dir,dir);
				movvv(cRay->from,from);
				if (sampleMotion)	cRay->time		=	(urand() + currentSample - 1) * multiplier;
				else				cRay->time		=	rays->time;
				cRay->t				=	C_INFINITY;
				cRay->tmin			=	rays->bias;
				cRay->flags			=	ATTRIBUTES_FLAGS_SPECULAR_VISIBLE;
				cRay->dest			=	rays->C;
				cRay->multiplier	=	multiplier;
				cRay->da			=	da;
				cRay->db			=	db;
				if (probeOnly) {

					// No, just query an intersection and record the distance
					trace(cRay);
					rays->t					+=	cRay->t*multiplier;
				} else {
					if (isExterior) {
						*cExteriorRays++	=	cRay;
						cExteriorRay++;
						
						if (--numExteriorRemaining == 0) {
							numReflectionRays			+=	shootStep;
							exteriorBundle.numRays		=	shootStep;
							exteriorBundle.rays			=	(CRay **) exteriorRaysBase;
							exteriorBundle.depth		=	0;
							exteriorBundle.last			=	0;
							exteriorBundle.postShader	=	exteriorShader;
							traceEx(&exteriorBundle);	
							cExteriorRay				=	exteriorRayBase;
							cExteriorRays				=	exteriorRaysBase;
							numExteriorRemaining		=	shootStep;
						}
					} else {
						*cInteriorRays++	=	cRay;
						cInteriorRay++;
						
						if (--numInteriorRemaining == 0) {
							numReflectionRays	+=	shootStep;
							interiorBundle.numRays		=	shootStep;
							interiorBundle.rays			=	(CRay **) interiorRaysBase;
							interiorBundle.depth		=	0;
							interiorBundle.last			=	0;
							interiorBundle.postShader	=	interiorShader;
							traceEx(&interiorBundle);
							cInteriorRay				=	interiorRayBase;
							cInteriorRays				=	interiorRaysBase;
							numInteriorRemaining		=	shootStep;
						}
					}
				}
			}
		}
	}

	// Finish the bundles
	if (numExteriorRemaining != shootStep) {
		numReflectionRays			+=	shootStep-numExteriorRemaining;
		exteriorBundle.numRays		=	shootStep-numExteriorRemaining;
		exteriorBundle.rays			=	(CRay **) exteriorRaysBase;
		exteriorBundle.depth		=	0;
		exteriorBundle.last			=	0;
		exteriorBundle.postShader	=	exteriorShader;
		traceEx(&exteriorBundle);	
	}
	if (numInteriorRemaining != shootStep) {
		numReflectionRays			+=	shootStep-numInteriorRemaining;
		interiorBundle.numRays		=	shootStep-numInteriorRemaining;
		interiorBundle.rays			=	(CRay **) interiorRaysBase;
		interiorBundle.depth		=	0;
		interiorBundle.last			=	0;
		interiorBundle.postShader	=	interiorShader;
		traceEx(&interiorBundle);	
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
