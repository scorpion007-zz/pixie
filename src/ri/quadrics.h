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
//  File				:	quadrics.h
//  Classes				:	Quadric surfaces
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef QUADRICS_H
#define QUADRICS_H

#include "common/global.h"
#include "common/algebra.h"
#include "object.h"
#include "shader.h"
#include "hierarchy.h"
#include "renderer.h"
#include "pl.h"


///////////////////////////////////////////////////////////////////////
// Class				:	CSphere
// Description			:	Encapsulates a sphere
// Comments				:
// Date last edited		:	6/28/2001
class	CSphere : public CSurface , public CTracable {
public:
						CSphere(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float,float);
						CSphere(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float,float,float,float,float,float);
						~CSphere();

		int				intersect(const float *,const float *) const;
		int				intersect(CRay *);
		void			bound(float *,float *) const;
		void			tesselate(CShadingContext *);
		int				moving() const													{	return (nextData != NULL) | (xform->next != NULL);		}
		void			sample(int,int,float **,unsigned int &) const;
		void			interpolate(int,float **) const;
		void			copy(CAttributes *,CXform *,CRendererContext *) const;

private:
		CParameter		*parameters;
		unsigned int	parametersF;
		float			r,umax,vmin,vmax;
		float			*nextData;
		vector			bmin,bmax;

		void			computeObjectBound(float *,float *,float,float,float,float);
};


///////////////////////////////////////////////////////////////////////
// Class				:	CDisk
// Description			:	Encapsulates a disk
// Comments				:
// Date last edited		:	6/28/2001
class	CDisk : public CSurface , public CTracable {
public:
						CDisk(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float);
						CDisk(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float,float,float,float);
						~CDisk();

		int				intersect(const float *,const float *) const;
		int				intersect(CRay *);
		void			bound(float *,float *) const;
		void			tesselate(CShadingContext *);
		int				moving() const													{	return (nextData != NULL) | (xform->next != NULL);		}
		void			sample(int,int,float **,unsigned int &) const;
		void			interpolate(int,float **) const;
		void			copy(CAttributes *,CXform *,CRendererContext *) const;

private:
		CParameter		*parameters;
		unsigned int	parametersF;
		float			r,z,umax;
		float			*nextData;
		vector			bmin,bmax;

		void			computeObjectBound(float *,float *,float,float,float);
};


///////////////////////////////////////////////////////////////////////
// Class				:	CCone
// Description			:	Encapsulates a cone
// Comments				:
// Date last edited		:	6/28/2001
class	CCone : public CSurface , public CTracable {
public:
						CCone(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float);
						CCone(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float,float,float,float);
						~CCone();

		int				intersect(const float *,const float *) const;
		int				intersect(CRay *);
		void			bound(float *,float *) const;
		void			tesselate(CShadingContext *);
		int				moving() const													{	return (nextData != NULL) | (xform->next != NULL);		}
		void			sample(int,int,float **,unsigned int &) const;
		void			interpolate(int,float **) const;
		void			copy(CAttributes *,CXform *,CRendererContext *) const;

private:
		CParameter		*parameters;
		unsigned int	parametersF;
		float			r,height,umax;
		float			*nextData;
		vector			bmin,bmax;

		void			computeObjectBound(float *,float *,float,float,float);
};


///////////////////////////////////////////////////////////////////////
// Class				:	CParaboloid
// Description			:	Encapsulates a paraboloid
// Comments				:
// Date last edited		:	6/28/2001
class	CParaboloid : public CSurface , public CTracable {
public:
						CParaboloid(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float,float);
						CParaboloid(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float,float,float,float,float,float);
						~CParaboloid();

		int				intersect(const float *,const float *) const;
		int				intersect(CRay *);
		void			bound(float *,float *) const;
		void			tesselate(CShadingContext *);
		int				moving() const													{	return (nextData != NULL) | (xform->next != NULL);		}
		void			sample(int,int,float **,unsigned int &) const;
		void			interpolate(int,float **) const;
		void			copy(CAttributes *,CXform *,CRendererContext *) const;

private:
		CParameter		*parameters;
		unsigned int	parametersF;
		float			r,zmin,zmax,umax;
		float			*nextData;
		vector			bmin,bmax;

		void			computeObjectBound(float *,float *,float,float,float,float);
};


///////////////////////////////////////////////////////////////////////
// Class				:	CCylinder
// Description			:	Encapsulates a cylinder
// Comments				:
// Date last edited		:	6/28/2001
class	CCylinder : public CSurface , public CTracable {
public:
						CCylinder(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float,float);
						CCylinder(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float,float,float,float,float,float);
						~CCylinder();

		int				intersect(const float *,const float *) const;
		int				intersect(CRay *);
		void			bound(float *,float *) const;
		void			tesselate(CShadingContext *);
		int				moving() const													{	return (nextData != NULL) | (xform->next != NULL);		}
		void			sample(int,int,float **,unsigned int &) const;
		void			interpolate(int,float **) const;
		void			copy(CAttributes *,CXform *,CRendererContext *) const;

private:
		CParameter		*parameters;
		unsigned int	parametersF;
		float			r,zmin,zmax,umax;
		float			*nextData;
		vector			bmin,bmax;

		void			computeObjectBound(float *,float *,float,float,float,float);
};

///////////////////////////////////////////////////////////////////////
// Class				:	CHyperboloid
// Description			:	Encapsulates a hyperboloid
// Comments				:
// Date last edited		:	6/28/2001
class	CHyperboloid : public CSurface , public CTracable {
public:
						CHyperboloid(CAttributes *,CXform *,CParameter *,unsigned int,const float *,const float *,float);
						CHyperboloid(CAttributes *,CXform *,CParameter *,unsigned int,const float *,const float *,float,const float *,const float *,float);
						~CHyperboloid();

		int				intersect(const float *,const float *) const;
		int				intersect(CRay *);
		void			bound(float *,float *) const;
		void			tesselate(CShadingContext *);
		int				moving() const													{	return (nextData != NULL) | (xform->next != NULL);		}
		void			sample(int,int,float **,unsigned int &) const;
		void			interpolate(int,float **) const;
		void			copy(CAttributes *,CXform *,CRendererContext *) const;

private:
		CParameter		*parameters;
		unsigned int	parametersF;
		vector			p1,p2;
		float			umax;
		float			*nextData;
		vector			bmin,bmax;

		void			computeObjectBound(float *,float *,float *,float *,float);
};


///////////////////////////////////////////////////////////////////////
// Class				:	CToroid
// Description			:	Encapsulates a torus
// Comments				:
// Date last edited		:	6/28/2001
class	CToroid : public CSurface , public CTracable {
public:
						CToroid(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float,float,float);
						CToroid(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float,float,float,float,float,float,float,float);
						~CToroid();

		int				intersect(const float *,const float *) const;
		int				intersect(CRay *);
		void			bound(float *,float *) const;
		void			tesselate(CShadingContext *);
		int				moving() const													{	return (nextData != NULL) | (xform->next != NULL);		}
		void			sample(int,int,float **,unsigned int &) const;
		void			interpolate(int,float **) const;
		void			copy(CAttributes *,CXform *,CRendererContext *) const;

private:
		CParameter		*parameters;
		unsigned int	parametersF;
		float			rmin,rmax,vmin,vmax,umax;
		float			*nextData;
		vector			bmin,bmax;

		void			computeObjectBound(float *,float *,float,float,float,float,float);
};

#endif





