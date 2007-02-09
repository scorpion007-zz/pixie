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
//  File				:	photon.h
//  Classes				:	CPhotonHider
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef PHOTON_H
#define PHOTON_H

#include "common/global.h"		// The global header file
#include "shading.h"
#include "ray.h"
#include "random.h"
#include "attributes.h"
#include "options.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonHider
// Description			:	This class implements the photon hider
// Comments				:
class	CPhotonHider : public CShadingContext {
public:
									CPhotonHider(int thread,CAttributes *);
			virtual					~CPhotonHider();
			
			static void				preDisplaySetup();
			
			// The main hider interface
			// The following functions are commented out for we want the CShadingContext to handle those
			void					renderingLoop();		// Right after world end to force rendering of the entire frame

			// Since we're not doing any rasterization, the following functions are simple stubs

			// Delayed rendering functions
			void					drawObject(CObject *) { }

			// Primitive creation functions
			void					drawGrid(CSurface *,int,int,float,float,float,float) { }
			void					drawPoints(CSurface *,int) { }
protected:
			void					solarBegin(const float *,const float *);
			void					solarEnd();
			void					illuminateBegin(const float *,const float *,const float *);
			void					illuminateEnd();

			int						numTracedPhotons;
private:
			void					tracePhoton(float *,float *,float *,float);
	
			float					bias;					// The initial intersection bias

			float					powerScale;				// The scaling factor for individual photon powers
			float					minPower;				// The variables to find the range of the illumination
			float					maxPower;				// for the current light
			float					avgPower;
			float					numPower;

			float					photonPower;			// The scale factor for the current batch

			CSobol<4>				gen4;					// 4D random number generator
			CSobol<3>				gen3;					// 3D random number generator
			CSobol<2>				gen2;					// 3D random number generator

			float					worldRadius;			// The radius of the world
			vector					worldCenter;			// The center of the world

			CArray<CPhotonMap *>	balanceList;			// The list of photon maps that need re-balancing

			CSurface				*phony;					// Phony object we used on the light sources
};

#endif

