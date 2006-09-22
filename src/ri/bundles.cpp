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
//  File				:	bundles.cpp
//  Classes				:	CRayBundle
//  Description			:	Implementation
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "bundles.h"
#include "renderer.h"
#include "error.h"
#include "stats.h"






///////////////////////////////////////////////////////////////////////
// Class				:	CTraceBundle
// Method				:	postTraceAction
// Description			:	Make sure we trace the rays
// Return Value			:	-
// Comments				:
// Date last edited		:	3/21/2003
int		CTraceBundle::postTraceAction() {
	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CTraceBundle
// Method				:	postShade
// Description			:	Make sure we trace the rays
// Return Value			:	-
// Comments				:
// Date last edited		:	3/21/2003
void	CTraceBundle::postShade(int nr,CRay **r,float **varying) {
	float	*Ci	=	varying[VARIABLE_CI];
	float	*Oi	=	varying[VARIABLE_OI];
	int		i;
	T32		one;
	T32		*opacity;

	stats.numShadingRays	+=	nr;

	one.real	=	1.0f;

	if (depth == 0) {
		// First hit
		for (i=nr;i>0;i--,Ci+=3,Oi+=3) {
			CTraceRay	*cRay	=	(CTraceRay *) (*r++);

			opacity	=	(T32 *) Oi;
			if (	(opacity[0].integer ^ one.integer) |
					(opacity[1].integer ^ one.integer) |
					(opacity[2].integer ^ one.integer)) {
				// We hit a transparent surface
				movvv(cRay->color,Ci);		// Save the color and opacity as we'll need those
				movvv(cRay->opacity,Oi);
				rays[last++]	=	cRay;
			} else {
				const	float	multiplier	=	cRay->multiplier;
				// We hit an opaque surface
				cRay->dest[0]	+=	Ci[0]*multiplier;
				cRay->dest[1]	+=	Ci[1]*multiplier;
				cRay->dest[2]	+=	Ci[2]*multiplier;
			}
		}
	} else {
		// Transparency hit
		for (i=nr;i>0;i--,Ci+=3,Oi+=3) {
			CTraceRay	*cRay		=	(CTraceRay *) (*r++);

			opacity	=	(T32 *) Oi;

			const	int		transparent	=	(opacity[0].integer ^ one.integer) | (opacity[1].integer ^ one.integer) | (opacity[2].integer ^ one.integer);
			const	float	*backOpacity	=	cRay->opacity;

			Ci[0]	*=	1 - backOpacity[0];
			Ci[1]	*=	1 - backOpacity[1];
			Ci[2]	*=	1 - backOpacity[2];
			Oi[0]	*=	1 - backOpacity[0];
			Oi[1]	*=	1 - backOpacity[1];
			Oi[2]	*=	1 - backOpacity[2];
			addvv(cRay->color,Ci);
			addvv(cRay->opacity,Oi);

			if (transparent) {
				// We hit a transparent surface again, keep tracing
				rays[last++]		=	cRay;
			} else {
				const	float	multiplier	=	cRay->multiplier;
				// We hit an opaque surface
				cRay->dest[0]	+=	cRay->color[0]*multiplier;
				cRay->dest[1]	+=	cRay->color[1]*multiplier;
				cRay->dest[2]	+=	cRay->color[2]*multiplier;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CTraceBundle
// Method				:	postShade
// Description			:	Called for the rays that don't hit anything
// Return Value			:	-
// Comments				:
// Date last edited		:	3/21/2003
void	CTraceBundle::postShade(int nr,CRay **r) {
	stats.numShadingRays	+=	nr;

	if (depth > 0) {
		int	i;

		for (i=nr;i>0;i--) {
			CTraceRay		*cRay		=	(CTraceRay *) (*r++);
			const	float	multiplier	=	cRay->multiplier;

			cRay->dest[0]	+=	cRay->color[0]*multiplier;
			cRay->dest[1]	+=	cRay->color[1]*multiplier;
			cRay->dest[2]	+=	cRay->color[2]*multiplier;
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CTraceBundle
// Method				:	post
// Description			:	Called after the first pass
// Return Value			:	-
// Comments				:
// Date last edited		:	3/21/2003
void	CTraceBundle::post() {
	numRays	=	last;
	last	=	0;
	depth++;
}











///////////////////////////////////////////////////////////////////////
// Class				:	CTraceExBundle
// Method				:	postTraceAction
// Description			:	Make sure we trace the rays
// Return Value			:	-
// Comments				:
// Date last edited		:	3/21/2003
int		CTraceExBundle::postTraceAction() {
	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CTraceExBundle
// Method				:	postShade
// Description			:	Make sure we trace the rays
// Return Value			:	-
// Comments				:
// Date last edited		:	3/21/2003
void	CTraceExBundle::postShade(int nr,CRay **r,float **varying) {
	float	*Ci	=	varying[VARIABLE_CI];
	float	*Oi	=	varying[VARIABLE_OI];
	int		i;
	T32		one;
	T32		*opacity;

	stats.numShadingRays	+=	nr;

	one.real	=	1.0f;

	if (depth == 0) {
		// First hit
		for (i=nr;i>0;i--,Ci+=3,Oi+=3) {
			CTraceExRay	*cRay	=	(CTraceExRay *) (*r++);

			*(cRay->destT)	=	cRay->t;

			opacity	=	(T32 *) Oi;
			if (	(opacity[0].integer ^ one.integer) |
					(opacity[1].integer ^ one.integer) |
					(opacity[2].integer ^ one.integer)) {
				// We hit a transparent surface
				movvv(cRay->color,Ci);		// Save the color and opacity as we'll need those
				movvv(cRay->opacity,Oi);
				rays[last++]	=	cRay;
			} else {
				const	float	multiplier	=	cRay->multiplier;
				// We hit an opaque surface
				cRay->dest[0]	+=	Ci[0]*multiplier;
				cRay->dest[1]	+=	Ci[1]*multiplier;
				cRay->dest[2]	+=	Ci[2]*multiplier;
			}
		}
	} else {
		// Transparency hit
		for (i=nr;i>0;i--,Ci+=3,Oi+=3) {
			CTraceRay	*cRay		=	(CTraceRay *) (*r++);

			opacity	=	(T32 *) Oi;

			const	int		transparent		=	(opacity[0].integer ^ one.integer) | (opacity[1].integer ^ one.integer) | (opacity[2].integer ^ one.integer);
			const	float	*backOpacity	=	cRay->opacity;

			Ci[0]	*=	1 - backOpacity[0];
			Ci[1]	*=	1 - backOpacity[1];
			Ci[2]	*=	1 - backOpacity[2];
			Oi[0]	*=	1 - backOpacity[0];
			Oi[1]	*=	1 - backOpacity[1];
			Oi[2]	*=	1 - backOpacity[2];
			addvv(cRay->color,Ci);
			addvv(cRay->opacity,Oi);

			if (transparent) {
				// We hit a transparent surface again, keep tracing
				rays[last++]		=	cRay;
			} else {
				const	float	multiplier	=	cRay->multiplier;
				// We hit an opaque surface
				cRay->dest[0]	+=	cRay->color[0]*multiplier;
				cRay->dest[1]	+=	cRay->color[1]*multiplier;
				cRay->dest[2]	+=	cRay->color[2]*multiplier;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CTraceExBundle
// Method				:	postShade
// Description			:	Called for the rays that don't hit anything
// Return Value			:	-
// Comments				:
// Date last edited		:	3/21/2003
void	CTraceExBundle::postShade(int nr,CRay **r) {
	stats.numShadingRays	+=	nr;

	if (depth > 0) {
		int	i;

		for (i=nr;i>0;i--) {
			CTraceExRay		*cRay		=	(CTraceExRay *) (*r++);
			const	float	multiplier	=	cRay->multiplier;

			cRay->dest[0]	+=	cRay->color[0]*multiplier;
			cRay->dest[1]	+=	cRay->color[1]*multiplier;
			cRay->dest[2]	+=	cRay->color[2]*multiplier;
		}
	}	
}

///////////////////////////////////////////////////////////////////////
// Class				:	CTraceExBundle
// Method				:	post
// Description			:	Called after the first pass
// Return Value			:	-
// Comments				:
// Date last edited		:	3/21/2003
void	CTraceExBundle::post() {
	numRays	=	last;
	last	=	0;
	depth++;
}


























///////////////////////////////////////////////////////////////////////
// Class				:	CIrradianceBundle
// Method				:	postTraceAction
// Description			:	Make sure we trace the rays
// Return Value			:	-
// Comments				:
// Date last edited		:	3/21/2003
int		CIrradianceBundle::postTraceAction() {
	return shade;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CIrradianceBundle
// Method				:	postShade
// Description			:	Make sure we trace the rays
// Return Value			:	-
// Comments				:
// Date last edited		:	3/21/2003
void	CIrradianceBundle::postShade(int nr,CRay **r,float **varying) {
	float	*Ci	=	varying[VARIABLE_CI];
	int		i;

	stats.numShadingRays	+=	nr;

	for (i=nr;i>0;i--,Ci+=3) {
		CIrradianceRay	*cRay	=	(CIrradianceRay *) (*r++);

		movvv(cRay->dest,Ci);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CIrradianceBundle
// Method				:	postShade
// Description			:	Called for the rays that don't hit anything
// Return Value			:	-
// Comments				:
// Date last edited		:	3/21/2003
void	CIrradianceBundle::postShade(int nr,CRay **r) {
	stats.numShadingRays	+=	nr;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CIrradianceBundle
// Method				:	post
// Description			:	Called after the first pass
// Return Value			:	-
// Comments				:
// Date last edited		:	3/21/2003
void	CIrradianceBundle::post() {
	numRays	=	last;
	last	=	0;
	depth++;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CTransmissionBundle
// Method				:	postTraceAction
// Description			:	Make sure we trace the rays
// Return Value			:	-
// Comments				:
// Date last edited		:	3/21/2003
int		CTransmissionBundle::postTraceAction() {
	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CTransmissionBundle
// Method				:	postShade
// Description			:	Make sure we trace the rays
// Return Value			:	-
// Comments				:
// Date last edited		:	3/21/2003
void	CTransmissionBundle::postShade(int nr,CRay **r,float **varying) {
	float	*Ci	=	varying[VARIABLE_CI];
	float	*Oi	=	varying[VARIABLE_OI];
	int		i;
	T32		one;
	T32		*opacity;

	stats.numShadowRays	+=	nr;

	one.real	=	1.0f;

	if (depth == 0) {
		// First hit
		for (i=nr;i>0;i--,Ci+=3,Oi+=3) {
			CTransmissionRay	*cRay	=	(CTransmissionRay *) (*r++);

			opacity	=	(T32 *) Oi;
			if (	(opacity[0].integer ^ one.integer) |
					(opacity[1].integer ^ one.integer) |
					(opacity[2].integer ^ one.integer)) {
				// We hit a transparent surface
				movvv(cRay->opacity,Oi);
				rays[last++]	=	cRay;
			}
		}
	} else {
		// Transparency hit
		for (i=nr;i>0;i--,Ci+=3,Oi+=3) {
			CTransmissionRay	*cRay	=	(CTransmissionRay *) (*r++);

			opacity	=	(T32 *) Oi;

			const	int	transparent	=	(opacity[0].integer ^ one.integer) | (opacity[1].integer ^ one.integer) | (opacity[2].integer ^ one.integer);

			Oi[0]		*=	1 - cRay->opacity[0];
			Oi[1]		*=	1 - cRay->opacity[1];
			Oi[2]		*=	1 - cRay->opacity[2];
			addvv(cRay->opacity,Oi);

			if (transparent) {
				// Still transparent
				rays[last++]		=	cRay;
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CTransmissionBundle
// Method				:	postShade
// Description			:	Called for the rays that don't hit anything
// Return Value			:	-
// Comments				:
// Date last edited		:	3/21/2003
void	CTransmissionBundle::postShade(int nr,CRay **r) {
	int	i;

	stats.numShadowRays	+=	nr;

	if (depth == 0) {
		for (i=nr;i>0;i--) {
			CTransmissionRay	*cRay		=	(CTransmissionRay *) (*r++);
			const	float		multiplier	=	cRay->multiplier;

			cRay->dest[0]	+=	multiplier;
			cRay->dest[1]	+=	multiplier;
			cRay->dest[2]	+=	multiplier;
		}
	} else {
		for (i=nr;i>0;i--) {
			CTransmissionRay	*cRay		=	(CTransmissionRay *) (*r++);
			const	float		multiplier	=	cRay->multiplier;
			const	float		*opacity	=	cRay->opacity;

			cRay->dest[0]	+=	(1-opacity[0])*multiplier;
			cRay->dest[1]	+=	(1-opacity[1])*multiplier;
			cRay->dest[2]	+=	(1-opacity[2])*multiplier;
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CTraceBundle
// Method				:	post
// Description			:	Called after the first pass
// Return Value			:	-
// Comments				:
// Date last edited		:	3/21/2003
void	CTransmissionBundle::post() {
	numRays	=	last;
	last	=	0;
	depth++;
}







///////////////////////////////////////////////////////////////////////
// Class				:	CGatherBundle
// Method				:	CGatherBundle
// Description			:	Ctor
// Return Value			:	-
// Comments				:
// Date last edited		:	3/23/2003
CGatherBundle::CGatherBundle() {
}

///////////////////////////////////////////////////////////////////////
// Class				:	CGatherBundle
// Method				:	~CGatherBundle
// Description			:	Dtor
// Return Value			:	-
// Comments				:
// Date last edited		:	3/23/2003
CGatherBundle::~CGatherBundle() {
}

///////////////////////////////////////////////////////////////////////
// Class				:	CGatherBundle
// Method				:	postTraceAction
// Description			:
// Return Value			:	TRUE if needs shading
// Comments				:
// Date last edited		:	3/23/2003
int		CGatherBundle::postTraceAction() {
	CGatherVariable	*cVariable;
	int				i;

	// Dispatch the outputs that don't need shading
	for (cVariable=lookup->nonShadeOutputs;cVariable!=NULL;cVariable=cVariable->next) {
		cVariable->record(numRays,(CGatherRay **) rays,NULL);
	}

	// Adjust the tags
	for (i=0;i<numRays;i++) {
		CGatherRay	*cRay	=	(CGatherRay *) rays[i];

		if (cRay->object == NULL) {
			numMisses++;
			(*cRay->tags)++;
		}
	}

	return lookup->outputs != NULL;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CGatherBundle
// Method				:	postShade
// Description			:
// Return Value			:	-
// Comments				:
// Date last edited		:	3/23/2003
void	CGatherBundle::postShade(int nr,CRay **r,float **varying) {
	CGatherVariable	*cVariable;

	stats.numShadingRays	+=	nr;

	for (cVariable=lookup->outputs;cVariable!=NULL;cVariable=cVariable->next) {
		cVariable->record(nr,(CGatherRay **) r,varying);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CGatherBundle
// Method				:	postShade
// Description			:
// Return Value			:	-
// Comments				:
// Date last edited		:	3/23/2003
void	CGatherBundle::postShade(int nr,CRay **r) {
	stats.numShadingRays	+=	nr;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CGatherBundle
// Method				:	post
// Description			:
// Return Value			:	-
// Comments				:
// Date last edited		:	3/23/2003
void	CGatherBundle::post() {
	numRays	=	last;
	numRays	=	0;
	last	=	0;
	depth++;
}


