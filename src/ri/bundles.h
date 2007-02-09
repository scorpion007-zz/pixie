//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright © 1999 - 2003, Okan Arikan
//
// Contact: okan@cs.utexas.edu
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
//  File				:	bundles.h
//  Classes				:	
//  Description			:	Special ray bundle classes
//
////////////////////////////////////////////////////////////////////////
#ifndef BUNDLES_H
#define BUNDLES_H

#include "common/global.h"		// The global header file
#include "ray.h"
#include "shading.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CTraceRay
// Description			:	Expands the ray for "trace" shading language command
// Comments				:
class	CTraceRay : public CRay {
public:
		vector					opacity;
		vector					color;
		float					*dest;
		float					multiplier;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CTraceBundle
// Description			:	Encapsulates a bundle of rays
// Comments				:
class	CTraceBundle : public CRayBundle {
public:
		int						postTraceAction();
		void					postShade(int,CRay **,float **);
		void					postShade(int,CRay **);
		void					post();
};









///////////////////////////////////////////////////////////////////////
// Class				:	CTraceRay
// Description			:	Expands the ray for "transmission" shading language command
// Comments				:	Note that we do not have color
class	CTransmissionRay : public CRay {
public:
		vector					opacity;
		float					*dest;
		float					multiplier;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CTraceBundle
// Description			:	Encapsulates a bundle of rays
// Comments				:
class	CTransmissionBundle : public CRayBundle {
public:
		int						postTraceAction();
		void					postShade(int,CRay **,float **);
		void					postShade(int,CRay **);
		void					post();
};






///////////////////////////////////////////////////////////////////////
// Class				:	CGatherRay
// Description			:	The ray used for gathering
// Comments				:
class	CGatherRay : public CRay {
public:
	int				*tags;		// The tag
	int				index;		// The ray index (the ray number)

	vector			gatherDir;	// Gather direction
};



///////////////////////////////////////////////////////////////////////
// Class				:	CGatherBundle
// Description			:	Bundle of gather rays
// Comments				:
class	CGatherBundle : public CRayBundle {
public:

					CGatherBundle();
					~CGatherBundle();

	int				postTraceAction();
	void			postShade(int nr,CRay **r,float **varying);
	void			postShade(int nr,CRay **r);
	void			post();

	CGatherRay		*raysBase;
	CRay			**raysStorage;
	TCode			**outputs;				// The array of outputs
	TCode			**nonShadeOutputs;		// The array of non-shade outputs
	CGatherLookup	*lookup;				// The parameters for this bundle
	const float		*ab;					// The ray differential
	int				numMisses;				// The number of missed rays
	int				remainingSamples;		// The number of remaining samples
};


#endif
