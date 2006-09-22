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
// Date last edited		:	3/21/2003
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
// Date last edited		:	3/21/2003
class	CTraceBundle : public CRayBundle {
public:
				int				postTraceAction();
				void			postShade(int,CRay **,float **);
				void			postShade(int,CRay **);
				void			post();
};





///////////////////////////////////////////////////////////////////////
// Class				:	CTraceRay
// Description			:	Expands the ray for "trace" shading language command
// Comments				:
// Date last edited		:	3/21/2003
class	CTraceExRay : public CRay {
public:
		vector					opacity;
		vector					color;
		float					*dest;
		float					*destT;
		float					multiplier;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CTraceBundle
// Description			:	Encapsulates a bundle of rays
// Comments				:
// Date last edited		:	3/21/2003
class	CTraceExBundle : public CRayBundle {
public:
				int				postTraceAction();
				void			postShade(int,CRay **,float **);
				void			postShade(int,CRay **);
				void			post();
};





///////////////////////////////////////////////////////////////////////
// Class				:	CTraceRay
// Description			:	Expands the ray for "transmission" shading language command
// Comments				:	Note that we do not have color
// Date last edited		:	3/21/2003
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
// Date last edited		:	3/21/2003
class	CTransmissionBundle : public CRayBundle {
public:
				int				postTraceAction();
				void			postShade(int,CRay **,float **);
				void			postShade(int,CRay **);
				void			post();
};

///////////////////////////////////////////////////////////////////////
// Class				:	CIrradianceRay
// Description			:	Expands the ray for "transmission" shading language command
// Comments				:	Note that we do not have color
// Date last edited		:	3/21/2003
class	CIrradianceRay : public CRay {
public:
		float					*dest;
};



///////////////////////////////////////////////////////////////////////
// Class				:	CIrradianceBundle
// Description			:	Encapsulates an irradiance bundle
// Comments				:
// Date last edited		:	3/21/2003
class	CIrradianceBundle : public CRayBundle {
public:
				int				postTraceAction();
				void			postShade(int,CRay **,float **);
				void			postShade(int,CRay **);
				void			post();

				int				shade;
};
///////////////////////////////////////////////////////////////////////
// Class				:	CGatherRay
// Description			:	The ray used for gathering
// Comments				:
// Date last edited		:	3/23/2003
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
// Date last edited		:	3/23/2003
class	CGatherBundle : public CRayBundle {
public:

					CGatherBundle();
					~CGatherBundle();

			int		postTraceAction();
			void	postShade(int nr,CRay **r,float **varying);
			void	postShade(int nr,CRay **r);
			void	post();

	CGatherRay		*raysBase;
	CRay			**raysStorage;
	CGatherLookup	*lookup;				// The parameters for this bundle
	int				numMisses;				// The number of missed rays
	int				remainingSamples;		// The number of remaining samples
};


#endif
