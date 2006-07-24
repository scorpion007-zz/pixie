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
//  File				:	hcshader.h
//  Classes				:	-
//  Description			:	This file holds the hardcoded shaders
//
////////////////////////////////////////////////////////////////////////
#ifndef HCSHADER_H
#define HCSHADER_H

#include "common/global.h"
#include "shader.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CQuadLight
// Description			:	This is a quadratic area light source
// Comments				:
// Date last edited		:	11/2/2003
class	CQuadLight : public CShaderInstance {
public:
								CQuadLight(CAttributes *,CXform *);
		virtual					~CQuadLight();

		void					illuminate(CShadingContext *);
		void					setParameters(int,char **,void **);
		int						getParameter(const char *,void *,CVariable**,int*);
		void					execute(CShadingContext *);
		unsigned int			requiredParameters();
		void					registerDefaults(CAttributes *,CActiveLight *) { }
		const char				*getName();
		void					prepareCache(CShadingContext *,int,float***) { }
private:
		vector					corners[4];
		vector					lightColor;		// The color of the light
		float					intensity;		// The intensity of the light
		int						numSamples;		// The number of samples to take
		int						reverse;		// TRUE if the orientation needs to be swapped
		vector					N;				// The normal vector for the plane
};

///////////////////////////////////////////////////////////////////////
// Class				:	CSphereLight
// Description			:	This is a spherical area light source
// Comments				:
// Date last edited		:	11/2/2003
class	CSphereLight : public CShaderInstance {
public:
								CSphereLight(CAttributes *,CXform *);
		virtual					~CSphereLight();

		void					illuminate(CShadingContext *);
		void					setParameters(int,char **,void **);
		int						getParameter(const char *,void *,CVariable**,int*);
		void					execute(CShadingContext *);
		unsigned int			requiredParameters();
		void					registerDefaults(CAttributes *,CActiveLight *) { }
		const char				*getName();
		void					prepareCache(CShadingContext *,int,float***) { }
private:
		vector					from;			// The location of the light
		float					radius;			// The radius of the light
		vector					lightColor;		// The color of the light
		float					intensity;		// The intensity of the light
		int						numSamples;		// The number of samples to take
};


#endif





