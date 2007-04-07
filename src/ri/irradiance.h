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
#include "random.h"
#include "depository.h"

// Forward declarations
class CRemoteICacheChannel;

///////////////////////////////////////////////////////////////////////
// Class				:	CIrradianceCache
// Description			:	Encapsulates an irradiance cache
// Comments				:
class	CIrradianceCache : public CCache {
public:

	///////////////////////////////////////////////////////////////////////
	// Class				:	CIrradiance
	// Description			:	Holds irradiance information on a surface
	// Comments				:
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

								CIrradianceCache(const char *,unsigned int,FILE *);
								~CIrradianceCache();

		void					lookup(float *,const float *,const float *,float,CShadingContext *,const CGlobalIllumLookup *);

		void					draw();
		int						keyDown(int key);
		
		void					bound(float *bmin,float *bmax);
private:
		void					writeNode(FILE *,CCacheNode *);
		CCacheNode				*readNode(FILE *);

		void					sample(float *,const float *,const float *,float,CShadingContext *,const CGlobalIllumLookup *);
		void					clamp(CCacheSample *);

		CMemStack				*memory;

		CCacheNode				*root;
		int						maxDepth;
		
		matrix					from,to;

		TMutex					mutex;
		
		static	int				drawDiscs;					// Which type to draw

		friend class			CRemoteICacheChannel;
};


#endif

