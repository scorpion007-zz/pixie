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
//  File				:	irradiance.cpp
//  Classes				:	CIrradianceCache
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef IRRADIANCE_H
#define IRRADIANCE_H

#include "common/global.h"
#include "common/os.h"
#include "common/algebra.h"
#include "options.h"
#include "shader.h"
#include "cache.h"
#include "hierarchy.h"
#include "random.h"
#include "depository.h"

// Forward declarations
class CRemoteICacheChannel;

///////////////////////////////////////////////////////////////////////
// Class				:	CIrradianceCache
// Description			:	Encapsulates an irradiance cache
// Comments				:
// Date last edited		:	10/15/2005
class	CIrradianceCache : public CCache {
public:

	///////////////////////////////////////////////////////////////////////
	// Class				:	CIrradiance
	// Description			:	Holds irradiance information on a surface
	// Comments				:
	// Date last edited		:	10/15/2005
	class	CCacheSample {
	public:
		vector				P;					// Point
		vector				N;					// Normal
		vector				irradiance;			// Irradiance
		float				coverage;			// Coverage
		vector				envdir;				// The unoccluded direction

		float				gP[7*3];			// The translational gradient
		float				gR[7*3];			// The rotational gradient

		float				dP;					// Mean radius
		CCacheSample		*next;				// Next irradiance in the list
	};

	///////////////////////////////////////////////////////////////////////
	// Class				:	CIrradianceNode
	// Description			:	Holds information about incident illumination
	// Comments				:
	// Date last edited		:	10/15/2005
	class	CCacheNode {
	public:
							CCacheNode(const float *);
							CCacheNode(FILE *);
							~CCacheNode();

		void				write(FILE *);

		CCacheSample		*samples;			// Linked list of samples
		CCacheNode			*children[8];		// Pointers to the children
		vector				center;				// The center of the node
		float				side;				// The side length of the node
	};

public:

								CIrradianceCache(const char *,unsigned int,const float *,const float *,CXform *,CHierarchy *,FILE *);
								~CIrradianceCache();

		void					lookup(float *,const float *,const float *,const CGlobalIllumLookup *);
		void					cachesample(float *,const float *,const float *,float);

		void					draw();
		void					bound(float *bmin,float *bmax);
private:
		void					writeNode(FILE *,CCacheNode *);
		CCacheNode				*readNode(FILE *);

		void					sample(float *,const float *,const float *,const CGlobalIllumLookup *);

		CMemStack				*memory;

		CHierarchy				*hierarchy;

		CCacheNode				*root;
		int						maxDepth;

		matrix					fromWorld,toWorld;
		matrix					from,to;
		
		friend class			CRemoteICacheChannel;
};


#endif
