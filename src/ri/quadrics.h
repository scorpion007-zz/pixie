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
class	CSphere : public CSurface {
public:
						CSphere(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float,float);
						CSphere(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float,float,float,float,float,float);
						~CSphere();

		void			intersect(CShadingContext *,CRay *);
		int				moving() const													{	return (nextData != NULL) | (xform->next != NULL);		}
		void			sample(int,int,float **,float ***,unsigned int &) const;
		void			interpolate(int,float **,float ***) const;
		void			instantiate(CAttributes *,CXform *,CRendererContext *) const;

		int				getDicingStats(int depth, int &minDivU,int &minDivV) const { minDivU = minDivV = max(3-depth,1); return 0; }				

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
class	CDisk : public CSurface {
public:
						CDisk(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float);
						CDisk(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float,float,float,float);
						~CDisk();

		void			intersect(CShadingContext *,CRay *);
		int				moving() const													{	return (nextData != NULL) | (xform->next != NULL);		}
		void			sample(int,int,float **,float ***,unsigned int &) const;
		void			interpolate(int,float **,float ***) const;
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
class	CCone : public CSurface {
public:
						CCone(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float);
						CCone(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float,float,float,float);
						~CCone();

		void			intersect(CShadingContext *,CRay *);
		int				moving() const													{	return (nextData != NULL) | (xform->next != NULL);		}
		void			sample(int,int,float **,float ***,unsigned int &) const;
		void			interpolate(int,float **,float ***) const;
		void			instantiate(CAttributes *,CXform *,CRendererContext *) const;
		
		int				getDicingStats(int depth, int &minDivU,int &minDivV) const { minDivU = max(3-depth,1); minDivV = 1; return 0; }

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
class	CParaboloid : public CSurface {
public:
						CParaboloid(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float,float);
						CParaboloid(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float,float,float,float,float,float);
						~CParaboloid();

		void			intersect(CShadingContext *,CRay *);
		int				moving() const													{	return (nextData != NULL) | (xform->next != NULL);		}
		void			sample(int,int,float **,float ***,unsigned int &) const;
		void			interpolate(int,float **,float ***) const;
		void			instantiate(CAttributes *,CXform *,CRendererContext *) const;
		
		int				getDicingStats(int depth, int &minDivU,int &minDivV) const { minDivU = minDivV = max(3-depth,1); return 0; }

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
class	CCylinder : public CSurface {
public:
						CCylinder(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float,float);
						CCylinder(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float,float,float,float,float,float);
						~CCylinder();

		void			intersect(CShadingContext *,CRay *);
		int				moving() const													{	return (nextData != NULL) | (xform->next != NULL);		}
		void			sample(int,int,float **,float ***,unsigned int &) const;
		void			interpolate(int,float **,float ***) const;
		void			instantiate(CAttributes *,CXform *,CRendererContext *) const;
		
		int				getDicingStats(int depth, int &minDivU,int &minDivV) const { minDivU = max(3-depth,1); minDivV = 1; return 0; }

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
class	CHyperboloid : public CSurface {
public:
						CHyperboloid(CAttributes *,CXform *,CParameter *,unsigned int,const float *,const float *,float);
						CHyperboloid(CAttributes *,CXform *,CParameter *,unsigned int,const float *,const float *,float,const float *,const float *,float);
						~CHyperboloid();

		void			intersect(CShadingContext *,CRay *);
		int				moving() const													{	return (nextData != NULL) | (xform->next != NULL);		}
		void			sample(int,int,float **,float ***,unsigned int &) const;
		void			interpolate(int,float **,float ***) const;
		void			instantiate(CAttributes *,CXform *,CRendererContext *) const;
		
		int				getDicingStats(int depth, int &minDivU,int &minDivV) const { minDivU = minDivV = max(3-depth,1); return 0; }

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
class	CToroid : public CSurface {
public:
						CToroid(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float,float,float);
						CToroid(CAttributes *,CXform *,CParameter *,unsigned int,float,float,float,float,float,float,float,float,float,float);
						~CToroid();

		void			intersect(CShadingContext *,CRay *);
		int				moving() const													{	return (nextData != NULL) | (xform->next != NULL);		}
		void			sample(int,int,float **,float ***,unsigned int &) const;
		void			interpolate(int,float **,float ***) const;
		void			instantiate(CAttributes *,CXform *,CRendererContext *) const;
		
		int				getDicingStats(int depth, int &minDivU,int &minDivV) const { minDivU = minDivV = max(3-depth,1); return 2; }

private:
		CParameter		*parameters;
		unsigned int	parametersF;
		float			rmin,rmax,vmin,vmax,umax;
		float			*nextData;

		void			computeObjectBound(float *,float *,float,float,float,float,float);
};

#endif

