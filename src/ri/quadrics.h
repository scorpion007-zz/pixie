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
#include "pl.h"


///////////////////////////////////////////////////////////////////////
// Class				:	CSphere
// Description			:	Encapsulates a sphere
// Comments				:
// Date last edited		:	6/28/2001
class	CSphere : public CSurface {
public:
						CSphere(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float,float);
						CSphere(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float,float,float,float,float,float);
						~CSphere();

		void			intersect(CShadingContext *,CRay *);
		int				moving() const													{	return (nextData != NULL) | (xform->next != NULL);		}
		void			sample(int,int,float **,unsigned int &) const;
		void			interpolate(int,float **) const;
		void			instantiate(CAttributes *,CXform *,CRendererContext *) const;

private:
		CParameter		*parameters;
		unsigned int	parametersF;
		float			r,umax,vmin,vmax;
		float			*nextData;

		void			computeObjectBound(float *,float *,float,float,float,float);
};


///////////////////////////////////////////////////////////////////////
// Class				:	CDisk
// Description			:	Encapsulates a disk
// Comments				:
// Date last edited		:	6/28/2001
class	CDisk : public CSurface {
public:
						CDisk(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float);
						CDisk(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float,float,float,float);
						~CDisk();

		void			intersect(CShadingContext *,CRay *);
		int				moving() const													{	return (nextData != NULL) | (xform->next != NULL);		}
		void			sample(int,int,float **,unsigned int &) const;
		void			interpolate(int,float **) const;
		void			instantiate(CAttributes *,CXform *,CRendererContext *) const;

private:
		CParameter		*parameters;
		unsigned int	parametersF;
		float			r,z,umax;
		float			*nextData;

		void			computeObjectBound(float *,float *,float,float,float);
};


///////////////////////////////////////////////////////////////////////
// Class				:	CCone
// Description			:	Encapsulates a cone
// Comments				:
// Date last edited		:	6/28/2001
class	CCone : public CSurface {
public:
						CCone(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float);
						CCone(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float,float,float,float);
						~CCone();

		void			intersect(CShadingContext *,CRay *);
		int				moving() const													{	return (nextData != NULL) | (xform->next != NULL);		}
		void			sample(int,int,float **,unsigned int &) const;
		void			interpolate(int,float **) const;
		void			instantiate(CAttributes *,CXform *,CRendererContext *) const;

private:
		CParameter		*parameters;
		unsigned int	parametersF;
		float			r,height,umax;
		float			*nextData;

		void			computeObjectBound(float *,float *,float,float,float);
};


///////////////////////////////////////////////////////////////////////
// Class				:	CParaboloid
// Description			:	Encapsulates a paraboloid
// Comments				:
// Date last edited		:	6/28/2001
class	CParaboloid : public CSurface {
public:
						CParaboloid(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float,float);
						CParaboloid(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float,float,float,float,float,float);
						~CParaboloid();

		void			intersect(CShadingContext *,CRay *);
		int				moving() const													{	return (nextData != NULL) | (xform->next != NULL);		}
		void			sample(int,int,float **,unsigned int &) const;
		void			interpolate(int,float **) const;
		void			instantiate(CAttributes *,CXform *,CRendererContext *) const;

private:
		CParameter		*parameters;
		unsigned int	parametersF;
		float			r,zmin,zmax,umax;
		float			*nextData;

		void			computeObjectBound(float *,float *,float,float,float,float);
};


///////////////////////////////////////////////////////////////////////
// Class				:	CCylinder
// Description			:	Encapsulates a cylinder
// Comments				:
// Date last edited		:	6/28/2001
class	CCylinder : public CSurface {
public:
						CCylinder(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float,float);
						CCylinder(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float,float,float,float,float,float);
						~CCylinder();

		void			intersect(CShadingContext *,CRay *);
		int				moving() const													{	return (nextData != NULL) | (xform->next != NULL);		}
		void			sample(int,int,float **,unsigned int &) const;
		void			interpolate(int,float **) const;
		void			instantiate(CAttributes *,CXform *,CRendererContext *) const;

private:
		CParameter		*parameters;
		unsigned int	parametersF;
		float			r,zmin,zmax,umax;
		float			*nextData;

		void			computeObjectBound(float *,float *,float,float,float,float);
};

///////////////////////////////////////////////////////////////////////
// Class				:	CHyperboloid
// Description			:	Encapsulates a hyperboloid
// Comments				:
// Date last edited		:	6/28/2001
class	CHyperboloid : public CSurface {
public:
						CHyperboloid(CAttributes *,CXform *,CParameter *,unsigned int,const float *,const float *,float);
						CHyperboloid(CAttributes *,CXform *,CParameter *,unsigned int,const float *,const float *,float,const float *,const float *,float);
						~CHyperboloid();

		void			intersect(CShadingContext *,CRay *);
		int				moving() const													{	return (nextData != NULL) | (xform->next != NULL);		}
		void			sample(int,int,float **,unsigned int &) const;
		void			interpolate(int,float **) const;
		void			instantiate(CAttributes *,CXform *,CRendererContext *) const;

private:
		CParameter		*parameters;
		unsigned int	parametersF;
		vector			p1,p2;
		float			umax;
		float			*nextData;

		void			computeObjectBound(float *,float *,float *,float *,float);
};


///////////////////////////////////////////////////////////////////////
// Class				:	CToroid
// Description			:	Encapsulates a torus
// Comments				:
// Date last edited		:	6/28/2001
class	CToroid : public CSurface {
public:
						CToroid(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float,float,float);
						CToroid(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float,float,float,float,float,float,float,float);
						~CToroid();

		void			intersect(CShadingContext *,CRay *);
		int				moving() const													{	return (nextData != NULL) | (xform->next != NULL);		}
		void			sample(int,int,float **,unsigned int &) const;
		void			interpolate(int,float **) const;
		void			instantiate(CAttributes *,CXform *,CRendererContext *) const;

private:
		CParameter		*parameters;
		unsigned int	parametersF;
		float			rmin,rmax,vmin,vmax,umax;
		float			*nextData;

		void			computeObjectBound(float *,float *,float,float,float,float,float);
};

#endif





