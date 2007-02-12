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
//  File				:	depository.cpp
//  Classes				:	CDepository
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include <math.h>
#include "common/os.h"
#include "depository.h"




///////////////////////////////////////////////////////////////////////
// Class				:	CDepository
// Method				:	CDepository
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CDepository::CDepository() : CMap<CDepositorySample>() {
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDepository
// Method				:	~CDepository
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CDepository::~CDepository() {
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDepository
// Method				:	lookup
// Description			:	Lookup function
// Return Value			:	-
// Comments				:
void		CDepository::lookup(float *C,const float *P,const float *N) {
	int						numFound	=	0;
	int						maxFound	=	5;
	const CDepositorySample	**indices	=	(const CDepositorySample **)	alloca((maxFound+1)*sizeof(CDepositorySample *)); 
	float					*distances	=	(float	*)						alloca((maxFound+1)*sizeof(float)); 
	CLookup					l;
	float					totalWeight;

	distances[0]	=	C_INFINITY;

	l.maxFound		=	maxFound;
	l.numFound		=	0;
	movvv(l.P,P);
	movvv(l.N,N);
	l.gotHeap		=	FALSE;
	l.indices		=	indices;
	l.distances		=	distances;

	CMap<CDepositorySample>::lookupWithN(&l,1);

	numFound		=	l.numFound;

	totalWeight		=	0;

	C[0]			=	0;
	C[1]			=	0;
	C[2]			=	0;
	C[3]			=	0;

	for (int i=1;i<=numFound;i++) {
		const		CDepositorySample	*p	=	indices[i];
		const float	t1						=	distances[i] / (distances[0] + C_EPSILON);
		const float	t2						=	sqrtf(max(1 - dotvv(N,p->N),0));
		float		weight					=	1 / (t1 + 10*t2 + C_EPSILON);

		if (weight < C_EPSILON) weight = C_EPSILON;

		assert(distances[i] <= distances[0]);

		C[0]		+=	p->C[0]*weight;
		C[1]		+=	p->C[1]*weight;
		C[2]		+=	p->C[2]*weight;
		C[3]		+=	p->C[3]*weight;
		totalWeight	+=	weight;						
	}

	if (totalWeight > 0) {
		assert(totalWeight > 0);

		// Normalize the sum
		totalWeight		=	1 / totalWeight;
		C[0]			*=	totalWeight;
		C[1]			*=	totalWeight;
		C[2]			*=	totalWeight;
		C[3]			*=	totalWeight;
	}
}

