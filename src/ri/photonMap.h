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
//  File				:	photonMap.h
//  Classes				:	CPhotonMap
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef PHOTONMAP_H
#define PHOTONMAP_H

#include "common/global.h"
#include "common/algebra.h"
#include "common/os.h"
#include "gui/opengl.h"
#include "fileResource.h"
#include "ray.h"
#include "xform.h"
#include "map.h"
#include "refCounter.h"




#define PHOTON_LOOKUP_CACHE






///////////////////////////////////////////////////////////////////////
//
//
//	Regular Photon Mapping stuff
//
//
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
// Class				:	CPhoton
// Description			:	A Photon
// Comments				:
class	CPhoton : public CMapItem {
public:
	vector			C;				// The intensity
	unsigned char	theta,phi;		// Photon direction
};


///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonRay
// Description			:	A Photon
// Comments				:
class	CPhotonRay : public CRay {
public:
	vector			intensity;		// The intensity
	float			factor;			// The product of all the factors (used for routian roulette)
};

///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMap
// Description			:	A Photon map
// Comments				:
class	CPhotonMap : public CMap<CPhoton> , public CFileResource, public CView, public CRefCounter {
	
	#ifdef PHOTON_LOOKUP_CACHE
		class	CPhotonSample {
		public:
			vector			C,P,N;
			float			dP;
			CPhotonSample	*next;
		};

		class	CPhotonNode {
		public:
			vector			center;
			float			side;
			CPhotonSample	*samples;
			CPhotonNode		*children[8];
		};
	#endif
	
public:
				CPhotonMap(const char *,FILE *);
				~CPhotonMap();

	void		reset();
	void		write(const CXform *);

	void		lookup(float *,const float *,int);
	void		lookup(float *,const float *,const float *,int);
	void		balance();

	void		store(const float *,const float *,const float *,const float *);

	void		draw();
	void		bound(float *bmin,float *bmax);

	#ifdef PHOTON_LOOKUP_CACHE
		int			probe(float *,const float *,const float *);
		void		insert(const float *,const float *,const float *,float);

		CPhotonNode	*root;
		int			maxDepth;			// The maximum depth of the hierarchy
	#endif

	int			modifying;
	matrix		from,to;
	float		maxPower;			// The maximum photon power
	float		searchRadius;
	TMutex		mutex;				// For synchronization during writing
};



#endif

