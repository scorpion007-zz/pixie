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
//  File				:	hierarchy.cpp
//  Classes				:
//  Description			:	
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "hierarchy.h"
#include "renderer.h"
#include "memory.h"
#include "stats.h"



////////////////////////////////////////////////////////////////////////
//
//
//
//	Implementation
//
//
//
////////////////////////////////////////////////////////////////////////







///////////////////////////////////////////////////////////////////////
// Class				:	CTriangle
// Method				:	CTriangle
// Description			:	Ctor
// Return Value			:	-
// Comments				:	
// Date last edited		:	3/11/2001
// FIXME: Optimize
CTriangle::CTriangle() {
	vector				dv1,dv2;
	unsigned int		majorAxis;
	const CAttributes	*a	=	object->attributes;

	CVertex	*v0	=	(CVertex *) getPointer(v[0]);
	CVertex	*v1	=	(CVertex *) getPointer(v[1]);
	CVertex	*v2	=	(CVertex *) getPointer(v[2]);

	// Compute the normal of the triangle
	subvv(dv1,v1->P,v0->P);
	subvv(dv2,v2->P,v0->P);
	crossvv(N,dv2,dv1);

	// Flip the normal if necessary
	if (a->flags & ATTRIBUTES_FLAGS_INSIDE)	mulvf(N,-1);

	if (dotvv(N,N) == 0)
		initv(N,0);
	else
	normalizev(N);

	// Compute the displacement along the normal vector to the origin
	d	=	-dotvv(N,v0->P);

	// Compute the major axis of the normal of the triangle and store it in
	// the lower 2 bits of v0
	majorAxis	=	COMP_X;
	if (fabs(N[COMP_Y]) > fabs(N[COMP_X]))		majorAxis	=	COMP_Y;
	if (fabs(N[COMP_Z]) > fabs(N[majorAxis]))	majorAxis	=	COMP_Z;

	switch(majorAxis) {
	case COMP_X:
		v[0]	=	(void *) getToken(getPointer(v[0]),COMP_Y);
		v[2]	=	(void *) getToken(getPointer(v[2]),COMP_Z);
		break;
	case COMP_Y:
		v[0]	=	(void *) getToken(getPointer(v[0]),COMP_X);
		v[2]	=	(void *) getToken(getPointer(v[2]),COMP_Z);
		break;
	case COMP_Z:
		v[0]	=	(void *) getToken(getPointer(v[0]),COMP_X);
		v[2]	=	(void *) getToken(getPointer(v[2]),COMP_Y);
		break;
	}

	if (a->nSides == 2) {
		v[1]	=	(void *) getToken(getPointer(v[1]),1);
	} else {
		v[1]	=	(void *) getToken(getPointer(v[1]),0);
	}
}




///////////////////////////////////////////////////////////////////////
// Class				:	CTriangle
// Method				:	bound
// Description			:	Bound the triangle
// Return Value			:	-
// Comments				:
// Date last edited		:	3/11/2001
void	CTriangle::bound(float *bmin,float *bmax) const {	
	movvv(bmin,((CVertex *) getPointer(v[0]))->P);
	movvv(bmax,bmin);
	addBox(bmin,bmax,((CVertex *) getPointer(v[1]))->P);
	addBox(bmin,bmax,((CVertex *) getPointer(v[2]))->P);
}



///////////////////////////////////////////////////////////////////////
// Class				:	CTriangle
// Method				:	intersect
// Description			:	Check if the triangle intersects a given box
// Return Value			:	TRUE if it does, FALSE othervise
// Comments				:
// Date last edited		:	3/11/2001
#define X 0
#define Y 1
#define Z 2

#define CROSS(dest,v1,v2)					\
          dest[0]=v1[1]*v2[2]-v1[2]*v2[1];	\
          dest[1]=v1[2]*v2[0]-v1[0]*v2[2];	\
          dest[2]=v1[0]*v2[1]-v1[1]*v2[0]; 

#define DOT(v1,v2) (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2])

#define SUB(dest,v1,v2)			\
          dest[0]=v1[0]-v2[0];	\
          dest[1]=v1[1]-v2[1];	\
          dest[2]=v1[2]-v2[2]; 

#define FINDMINMAX(x0,x1,x2,min,max) \
  min = max = x0;   \
  if(x1<min) min=x1;\
  if(x1>max) max=x1;\
  if(x2<min) min=x2;\
  if(x2>max) max=x2;

inline int planeBoxOverlap(float normal[3],float d, float maxbox[3]) {
  unsigned int q;
  float vmin[3],vmax[3];
  for(q=X;q<=Z;q++)
  {
    if(normal[q]>0.0f)
    {
      vmin[q]=-maxbox[q];
      vmax[q]=maxbox[q];
    }
    else
    {
      vmin[q]=maxbox[q];
      vmax[q]=-maxbox[q];
    }
  }
  if(DOT(normal,vmin)+d>0.0f) return 0;
  if(DOT(normal,vmax)+d>=0.0f) return 1;
  
  return 0;
}


/*======================== X-tests ========================*/
#define AXISTEST_X01(a, b, fa, fb)			   \
	p0 = a*v0[Y] - b*v0[Z];			       	   \
	p2 = a*v2[Y] - b*v2[Z];			       	   \
        if(p0<p2) {min=p0; max=p2;} else {min=p2; max=p0;} \
	rad = fa * boxhalfsize[Y] + fb * boxhalfsize[Z];   \
	if(min>rad || max<-rad) return 0;

#define AXISTEST_X2(a, b, fa, fb)			   \
	p0 = a*v0[Y] - b*v0[Z];			           \
	p1 = a*v1[Y] - b*v1[Z];			       	   \
        if(p0<p1) {min=p0; max=p1;} else {min=p1; max=p0;} \
	rad = fa * boxhalfsize[Y] + fb * boxhalfsize[Z];   \
	if(min>rad || max<-rad) return 0;

/*======================== Y-tests ========================*/
#define AXISTEST_Y02(a, b, fa, fb)			   \
	p0 = -a*v0[X] + b*v0[Z];		      	   \
	p2 = -a*v2[X] + b*v2[Z];	       	       	   \
        if(p0<p2) {min=p0; max=p2;} else {min=p2; max=p0;} \
	rad = fa * boxhalfsize[X] + fb * boxhalfsize[Z];   \
	if(min>rad || max<-rad) return 0;

#define AXISTEST_Y1(a, b, fa, fb)			   \
	p0 = -a*v0[X] + b*v0[Z];		      	   \
	p1 = -a*v1[X] + b*v1[Z];	     	       	   \
        if(p0<p1) {min=p0; max=p1;} else {min=p1; max=p0;} \
	rad = fa * boxhalfsize[X] + fb * boxhalfsize[Z];   \
	if(min>rad || max<-rad) return 0;

/*======================== Z-tests ========================*/

#define AXISTEST_Z12(a, b, fa, fb)			   \
	p1 = a*v1[X] - b*v1[Y];			           \
	p2 = a*v2[X] - b*v2[Y];			       	   \
        if(p2<p1) {min=p2; max=p1;} else {min=p1; max=p2;} \
	rad = fa * boxhalfsize[X] + fb * boxhalfsize[Y];   \
	if(min>rad || max<-rad) return 0;

#define AXISTEST_Z0(a, b, fa, fb)			   \
	p0 = a*v0[X] - b*v0[Y];				   \
	p1 = a*v1[X] - b*v1[Y];			           \
        if(p0<p1) {min=p0; max=p1;} else {min=p1; max=p0;} \
	rad = fa * boxhalfsize[X] + fb * boxhalfsize[Y];   \
	if(min>rad || max<-rad) return 0;


int		CTriangle::intersect(const float *bmin,const float *bmax) const {
   float	v0[3],v1[3],v2[3];
   float	min,max,d,p0,p1,p2,rad,fex,fey,fez;  
   float	normal[3],e0[3],e1[3],e2[3];
   vector	boxcenter,boxhalfsize;

	float	*ver0	=	((CVertex *) getPointer(v[0]))->P;
	float	*ver1	=	((CVertex *) getPointer(v[1]))->P;
	float	*ver2	=	((CVertex *) getPointer(v[2]))->P;

	addvv(boxcenter,bmin,bmax);
	subvv(boxhalfsize,bmax,bmin);

	mulvf(boxcenter,0.5);
	mulvf(boxhalfsize,0.5);

   /* This is the fastest branch on Sun */
   /* move everything so that the boxcenter is in (0,0,0) */
   SUB(v0,ver0,boxcenter);
   SUB(v1,ver1,boxcenter);
   SUB(v2,ver2,boxcenter);

   /* compute triangle edges */
   SUB(e0,v1,v0);      /* tri edge 0 */
   SUB(e1,v2,v1);      /* tri edge 1 */
   SUB(e2,v0,v2);      /* tri edge 2 */

   /* Bullet 3:  */
   /*  test the 9 tests first (this was faster) */
   fex = absf(e0[X]);
   fey = absf(e0[Y]);
   fez = absf(e0[Z]);
   AXISTEST_X01(e0[Z], e0[Y], fez, fey);
   AXISTEST_Y02(e0[Z], e0[X], fez, fex);
   AXISTEST_Z12(e0[Y], e0[X], fey, fex);

   fex = absf(e1[X]);
   fey = absf(e1[Y]);
   fez = absf(e1[Z]);
   AXISTEST_X01(e1[Z], e1[Y], fez, fey);
   AXISTEST_Y02(e1[Z], e1[X], fez, fex);
   AXISTEST_Z0(e1[Y], e1[X], fey, fex);

   fex = absf(e2[X]);
   fey = absf(e2[Y]);
   fez = absf(e2[Z]);
   AXISTEST_X2(e2[Z], e2[Y], fez, fey);
   AXISTEST_Y1(e2[Z], e2[X], fez, fex);
   AXISTEST_Z12(e2[Y], e2[X], fey, fex);

   /* Bullet 1: */
   /*  first test overlap in the {x,y,z}-directions */
   /*  find min, max of the triangle each direction, and test for overlap in */
   /*  that direction -- this is equivalent to testing a minimal AABB around */
   /*  the triangle against the AABB */

   /* test in X-direction */
   FINDMINMAX(v0[X],v1[X],v2[X],min,max);
   if(min>boxhalfsize[X] || max<-boxhalfsize[X]) return 0;

   /* test in Y-direction */
   FINDMINMAX(v0[Y],v1[Y],v2[Y],min,max);
   if(min>boxhalfsize[Y] || max<-boxhalfsize[Y]) return 0;

   /* test in Z-direction */
   FINDMINMAX(v0[Z],v1[Z],v2[Z],min,max);
   if(min>boxhalfsize[Z] || max<-boxhalfsize[Z]) return 0;

   /* Bullet 2: */
   /*  test if the box intersects the plane of the triangle */
   /*  compute plane equation of triangle: normal*x+d=0 */
   CROSS(normal,e0,e1);
   d=-DOT(normal,v0);  /* plane eq: normal.x+d=0 */
   if(!planeBoxOverlap(normal,d,boxhalfsize)) return 0;

   return 1;   /* box and triangle overlaps */
}




///////////////////////////////////////////////////////////////////////
// Class				:	CTriangle
// Method				:	intersect
// Description			:	-
// Return Value			:	TRUE if it does, FALSE othervise
// Comments				:	
// Date last edited		:	3/11/2001
// FIXME: Optimize
void	CTriangle::intersect(CRay *cRay)	{	// Do the triangle/ray intersection test here
	CVertex			*ver0,*ver1,*ver2;
	vector			intersection;
	float			t;
	float			*v0,*v1,*v2;
	float			a,uc,vc;
	unsigned int	major,minor;

	if (! (cRay->flags & object->attributes->flags) )	return;

	if (object->attributes->flags & ATTRIBUTES_FLAGS_LOD) {
		float importance = object->attributes->lodImportance;
		if (cRay->jimp < 0) cRay->jimp = urand();
		if (importance >= 0) {
			if (cRay->jimp > importance)			return;
		} else {
			if ((1-cRay->jimp) >= -importance)		return;
		}
	}
							// Operate on the camera space coordinates
	if ((t = dotvv(cRay->dir,N)) == 0)	return;

	if (getData(v[1]) == 0) {
		if (t > 0)	return;
	}

	t	=	(- d - dotvv(cRay->from,N)) / t;

	if (t <= cRay->tmin)	return;
	if (t >= cRay->t)	return;

	mulvf(intersection,cRay->dir,t);
	addvv(intersection,cRay->from);

	ver0	=	(CVertex *) getPointer(v[0]);
	ver1	=	(CVertex *) getPointer(v[1]);
	ver2	=	(CVertex *) getPointer(v[2]);

	v0		=	ver0->P;
	v1		=	ver1->P;
	v2		=	ver2->P;

	major	=	getData(v[0]);
	minor	=	getData(v[2]);

	if ((a = area(v0[major],v0[minor],v1[major],v1[minor],v2[major],v2[minor])) > 0) {
		if ((uc = area(v0[major],v0[minor],v1[major],v1[minor],intersection[major],intersection[minor])) < 0)	return;
		if ((vc = area(v1[major],v1[minor],v2[major],v2[minor],intersection[major],intersection[minor])) < 0)	return;
		if ((uc + vc) > a)	return;
	} else {
		if ((uc = area(v0[major],v0[minor],v1[major],v1[minor],intersection[major],intersection[minor])) > 0)	return;
		if ((vc = area(v1[major],v1[minor],v2[major],v2[minor],intersection[major],intersection[minor])) > 0)	return;
		if ((uc + vc) < a)	return;
	}

	uc				/=	a;
	vc				/=	a;

	cRay->t			=	t;
	cRay->u			=	ver0->u*vc + ver1->u*(1-uc-vc) + ver2->u*uc;
	cRay->v			=	ver0->v*vc + ver1->v*(1-uc-vc) + ver2->v*uc;
	cRay->object	=	object;
	cRay->N[0]		=	ver0->N[0]*vc + ver1->N[0]*(1-uc-vc) + ver2->N[0]*uc;
	cRay->N[1]		=	ver0->N[1]*vc + ver1->N[1]*(1-uc-vc) + ver2->N[1]*uc;
	cRay->N[2]		=	ver0->N[2]*vc + ver1->N[2]*(1-uc-vc) + ver2->N[2]*uc;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPtriangle
// Method				:	intersect
// Description			:	-
// Return Value			:	TRUE if it does, FALSE othervise
// Comments				:	
// Date last edited		:	3/11/2001
// FIXME: Optimize
void	CPtriangle::intersect(CRay *cRay)	{	// Do the triangle/ray intersection test here
	CVertex			*ver0,*ver1,*ver2;
	vector			intersection;
	float			t;
	float			*v0,*v1,*v2;
	double			a,uc,vc;
	unsigned int	major,minor;

	if (! (cRay->flags & object->attributes->flags) )	return;
	
	if (object->attributes->flags & ATTRIBUTES_FLAGS_LOD) {
		float importance = object->attributes->lodImportance;
		if (cRay->jimp < 0) cRay->jimp = urand();
		if (importance >= 0) {
			if (cRay->jimp > importance)			return;
		} else {
			if ((1-cRay->jimp) >= -importance)		return;
		}
	}
	
							// Operate on the camera space coordinates
	if ((t = dotvv(cRay->dir,N)) == 0)	return;

	if (getData(v[1]) == 0) {
		if (t > 0)	return;
	}

	t	=	(- d - dotvv(cRay->from,N)) / t;

	if (t <= cRay->tmin)	return;
	if (t >= cRay->t)		return;

	mulvf(intersection,cRay->dir,t);
	addvv(intersection,cRay->from);

	ver0	=	(CVertex *) getPointer(v[0]);
	ver1	=	(CVertex *) getPointer(v[1]);
	ver2	=	(CVertex *) getPointer(v[2]);

	v0		=	ver0->P;
	v1		=	ver1->P;
	v2		=	ver2->P;

	major	=	getData(v[0]);
	minor	=	getData(v[2]);

	if ((a = area(v0[major],v0[minor],v1[major],v1[minor],v2[major],v2[minor])) > 0) {
		if ((uc = area(v0[major],v0[minor],v1[major],v1[minor],intersection[major],intersection[minor])) < 0)	return;
		if ((vc = area(v1[major],v1[minor],v2[major],v2[minor],intersection[major],intersection[minor])) < 0)	return;
		if ((uc + vc) > a)	return;
	} else {
		if ((uc = area(v0[major],v0[minor],v1[major],v1[minor],intersection[major],intersection[minor])) > 0)	return;
		if ((vc = area(v1[major],v1[minor],v2[major],v2[minor],intersection[major],intersection[minor])) > 0)	return;
		if ((uc + vc) < a)	return;
	}


	cRay->t			=	t;
	cRay->u			=	(float) (1 - vc / a);
	cRay->v			=	(float) (1 - uc / (a - vc));
	cRay->object	=	object;
	cRay->N[0]		=	ver0->N[0]*(1-cRay->u) + ver1->N[0]*cRay->u*cRay->v + ver2->N[0]*cRay->u*(1-cRay->v);
	cRay->N[1]		=	ver0->N[1]*(1-cRay->u) + ver1->N[1]*cRay->u*cRay->v + ver2->N[1]*cRay->u*(1-cRay->v);
	cRay->N[2]		=	ver0->N[2]*(1-cRay->u) + ver1->N[2]*cRay->u*cRay->v + ver2->N[2]*cRay->u*(1-cRay->v);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CMovingTriangle
// Method				:	CMovingTriangle
// Description			:	Ctor
// Return Value			:	-
// Comments				:	
// Date last edited		:	3/11/2001
// FIXME: Optimize
CMovingTriangle::CMovingTriangle() {
	vector			dv1,dv2;
	unsigned int	majorAxis;
	const CAttributes	*a	=	object->attributes;

	CMovingVertex	*v0	=	(CMovingVertex *) getPointer(v[0]);
	CMovingVertex	*v1	=	(CMovingVertex *) getPointer(v[1]);
	CMovingVertex	*v2	=	(CMovingVertex *) getPointer(v[2]);

	// Compute the normal of the triangle
	subvv(dv1,v1->P[0],v0->P[0]);
	subvv(dv2,v2->P[0],v0->P[0]);
	crossvv(N[0],dv2,dv1);
	if (dotvv(N[0],N[0]) == 0)
		initv(N[0],0);
	else
	normalizev(N[0]);

	// Compute the major axis of the normal of the triangle and store it in
	// the lower 2 bits of v0
	majorAxis	=	COMP_X;
	if (fabs(N[0][COMP_Y]) > fabs(N[0][COMP_X]))		majorAxis	=	COMP_Y;
	if (fabs(N[0][COMP_Z]) > fabs(N[0][majorAxis]))		majorAxis	=	COMP_Z;

	switch(majorAxis) {
	case COMP_X:
		v[0]	=	(void *) getToken(getPointer(v[0]),COMP_Y);
		v[2]	=	(void *) getToken(getPointer(v[2]),COMP_Z);
		break;
	case COMP_Y:
		v[0]	=	(void *) getToken(getPointer(v[0]),COMP_X);
		v[2]	=	(void *) getToken(getPointer(v[2]),COMP_Z);
		break;
	case COMP_Z:
		v[0]	=	(void *) getToken(getPointer(v[0]),COMP_X);
		v[2]	=	(void *) getToken(getPointer(v[2]),COMP_Y);
		break;
	}

	// Compute the displacement along the normal vector to the origin
	d[0]	=	-dotvv(N[0],v0->P[0]);

	if (a->nSides == 2) {
		v[1]	=	(void *) getToken(getPointer(v[1]),1);
	} else {
		v[1]	=	(void *) getToken(getPointer(v[1]),0);
	}

	// Compute the normal of the triangle
	subvv(dv1,v1->P[1],v0->P[1]);
	subvv(dv2,v2->P[1],v0->P[1]);
	crossvv(N[1],dv2,dv1);
	if (dotvv(N[1],N[1]) == 0)
		initv(N[1],0);
	else
	normalizev(N[1]);

	// Compute the displacement along the normal vector to the origin
	d[1]	=	-dotvv(N[1],v0->P[1]);

	if (a->flags & ATTRIBUTES_FLAGS_INSIDE)	{
		mulvf(N[0],-1);
		mulvf(N[1],-1);
		d[0]	*=	-1;
		d[1]	*=	-1;
	}
}




///////////////////////////////////////////////////////////////////////
// Class				:	CMovingTriangle
// Method				:	bound
// Description			:	Bound the triangle
// Return Value			:	-
// Comments				:
// Date last edited		:	3/11/2001
void	CMovingTriangle::bound(float *bmin,float *bmax)	const {	
	movvv(bmin,((CMovingVertex *) getPointer(v[0]))->P[0]);
	movvv(bmax,bmin);
	addBox(bmin,bmax,((CMovingVertex *) getPointer(v[1]))->P[0]);
	addBox(bmin,bmax,((CMovingVertex *) getPointer(v[2]))->P[0]);

	addBox(bmin,bmax,((CMovingVertex *) getPointer(v[0]))->P[1]);
	addBox(bmin,bmax,((CMovingVertex *) getPointer(v[1]))->P[1]);
	addBox(bmin,bmax,((CMovingVertex *) getPointer(v[2]))->P[1]);
}



///////////////////////////////////////////////////////////////////////
// Class				:	CMovingTriangle
// Method				:	intersect
// Description			:	Check if the triangle intersects a given box
// Return Value			:	TRUE if it does, FALSE othervise
// Comments				:
// Date last edited		:	3/11/2001
int		CMovingTriangle::intersect(const float *bmin,const float *bmax)	const {
	float	*ver0	=	((CMovingVertex *) getPointer(v[0]))->P[0];
	float	*ver1	=	((CMovingVertex *) getPointer(v[1]))->P[0];
	float	*ver2	=	((CMovingVertex *) getPointer(v[2]))->P[0];

	vector	tmin,tmax;

	movvv(tmin,ver0);
	movvv(tmax,ver0);
	addBox(tmin,tmax,ver1);
	addBox(tmin,tmax,ver2);

	ver0	=	((CMovingVertex *) getPointer(v[0]))->P[1];
	ver1	=	((CMovingVertex *) getPointer(v[1]))->P[1];
	ver2	=	((CMovingVertex *) getPointer(v[2]))->P[1];

	addBox(tmin,tmax,ver0);
	addBox(tmin,tmax,ver1);
	addBox(tmin,tmax,ver2);

	return	intersectBox(bmin,bmax,tmin,tmax);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CMovingTriangle
// Method				:	intersect
// Description			:	-
// Return Value			:	TRUE if it does, FALSE othervise
// Comments				:	
// Date last edited		:	3/11/2001
// FIXME: Optimize
void	CMovingTriangle::intersect(CRay *cRay)	{	// Do the triangle/ray intersection test here
	CMovingVertex	*ver0,*ver1,*ver2;
	vector			intersection;
	float			t;
	vector			v0;
	vector			v1;
	vector			v2;
	double			a,uc,vc;
	unsigned int	major,minor;
	vector			normal;
	float			d;

	if (! (cRay->flags & object->attributes->flags) )	return;

	if (object->attributes->flags & ATTRIBUTES_FLAGS_LOD) {
		float importance = object->attributes->lodImportance;
		if (cRay->jimp < 0) cRay->jimp = urand();
		if (importance >= 0) {
			if (cRay->jimp > importance)			return;
		} else {
			if ((1-cRay->jimp) >= -importance)		return;
		}
	}
	
	interpolatev(normal,this->N[0],this->N[1],cRay->time);

	if ((t = dotvv(cRay->dir,normal)) == 0)	return;

	if(getData(v[1]) == 0) {
		if (t > 0)	return;
	}

	d	=	this->d[0]*(1-cRay->time) + this->d[1]*cRay->time;

	t	=	-(d + dotvv(cRay->from,normal)) / dotvv(cRay->dir,normal);

	if (t <= cRay->tmin)	return;
	if (t >= cRay->t)	return;

	mulvf(intersection,cRay->dir,t);
	addvv(intersection,cRay->from);

	ver0	=	(CMovingVertex *) getPointer(v[0]);
	ver1	=	(CMovingVertex *) getPointer(v[1]);
	ver2	=	(CMovingVertex *) getPointer(v[2]);

	interpolatev(v0,ver0->P[0],ver0->P[1],cRay->time);
	interpolatev(v1,ver1->P[0],ver1->P[1],cRay->time);
	interpolatev(v2,ver2->P[0],ver2->P[1],cRay->time);

	major		=	getData(v[0]);
	minor		=	getData(v[2]);

	if ((a = area(v0[major],v0[minor],v1[major],v1[minor],v2[major],v2[minor])) > 0) {
		if ((uc = area(v0[major],v0[minor],v1[major],v1[minor],intersection[major],intersection[minor])) < 0)	return;
		if ((vc = area(v1[major],v1[minor],v2[major],v2[minor],intersection[major],intersection[minor])) < 0)	return;
		if ((uc + vc) > a)	return;
	} else {
		if ((uc = area(v0[major],v0[minor],v1[major],v1[minor],intersection[major],intersection[minor])) > 0)	return;
		if ((vc = area(v1[major],v1[minor],v2[major],v2[minor],intersection[major],intersection[minor])) > 0)	return;
		if ((uc + vc) < a)	return;
	}

	uc				/=	a;
	vc				/=	a;

	cRay->t			=	t;
	cRay->u			=	(float) (ver0->u*vc + ver1->u*(1-uc-vc) + ver2->u*uc);
	cRay->v			=	(float) (ver0->v*vc + ver1->v*(1-uc-vc) + ver2->v*uc);
	cRay->object	=	object;
	cRay->N[0]		=	(float) (ver0->N[0][0]*vc + ver1->N[0][0]*(1-uc-vc) + ver2->N[0][0]*uc);
	cRay->N[1]		=	(float) (ver0->N[0][1]*vc + ver1->N[0][1]*(1-uc-vc) + ver2->N[0][1]*uc);
	cRay->N[2]		=	(float) (ver0->N[0][2]*vc + ver1->N[0][2]*(1-uc-vc) + ver2->N[0][2]*uc);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CMovingTriangle
// Method				:	intersect
// Description			:	-
// Return Value			:	TRUE if it does, FALSE othervise
// Comments				:	
// Date last edited		:	3/11/2001
// FIXME: Optimize
void	CPmovingTriangle::intersect(CRay *cRay)	{	// Do the triangle/ray intersection test here
	CMovingVertex	*ver0,*ver1,*ver2;
	vector			intersection;
	float			t;
	vector			v0;
	vector			v1;
	vector			v2;
	double			a,uc,vc;
	unsigned int	major,minor;
	vector			normal;
	float			d;

	if (! (cRay->flags & object->attributes->flags) )	return;

	if (object->attributes->flags & ATTRIBUTES_FLAGS_LOD) {
		float importance = object->attributes->lodImportance;
		if (cRay->jimp < 0) cRay->jimp = urand();
		if (importance >= 0) {
			if (cRay->jimp > importance)			return;
		} else {
			if ((1-cRay->jimp) >= -importance)		return;
		}
	}
	
	interpolatev(normal,this->N[0],this->N[1],cRay->time);

	if ((t = dotvv(cRay->dir,normal)) == 0)	return;

	if(getData(v[1]) == 0) {
		if (t > 0)	return;
	}

	d	=	this->d[0]*(1-cRay->time) + this->d[1]*cRay->time;

	t	=	-(d + dotvv(cRay->from,normal)) / dotvv(cRay->dir,normal);

	if (t <= cRay->tmin)	return;
	if (t >= cRay->t)	return;

	mulvf(intersection,cRay->dir,t);
	addvv(intersection,cRay->from);

	ver0	=	(CMovingVertex *) getPointer(v[0]);
	ver1	=	(CMovingVertex *) getPointer(v[1]);
	ver2	=	(CMovingVertex *) getPointer(v[2]);

	interpolatev(v0,ver0->P[0],ver0->P[1],cRay->time);
	interpolatev(v1,ver1->P[0],ver1->P[1],cRay->time);
	interpolatev(v2,ver2->P[0],ver2->P[1],cRay->time);

	major		=	getData(v[0]);
	minor		=	getData(v[2]);

	if ((a = area(v0[major],v0[minor],v1[major],v1[minor],v2[major],v2[minor])) > 0) {
		if ((uc = area(v0[major],v0[minor],v1[major],v1[minor],intersection[major],intersection[minor])) < 0)	return;
		if ((vc = area(v1[major],v1[minor],v2[major],v2[minor],intersection[major],intersection[minor])) < 0)	return;
		if ((uc + vc) > a)	return;
	} else {
		if ((uc = area(v0[major],v0[minor],v1[major],v1[minor],intersection[major],intersection[minor])) > 0)	return;
		if ((vc = area(v1[major],v1[minor],v2[major],v2[minor],intersection[major],intersection[minor])) > 0)	return;
		if ((uc + vc) < a)	return;
	}
	
	cRay->t			=	t;
	cRay->u			=	(float) (1 - vc / a);
	cRay->v			=	(float) (1 - uc / (a - vc));
	cRay->object	=	object;
	cRay->N[0]		=	ver0->N[0][0]*(1-cRay->u) + ver1->N[0][0]*cRay->u*cRay->v + ver2->N[0][0]*cRay->u*(1-cRay->v);
	cRay->N[1]		=	ver0->N[0][1]*(1-cRay->u) + ver1->N[0][1]*cRay->u*cRay->v + ver2->N[0][1]*cRay->u*(1-cRay->v);
	cRay->N[2]		=	ver0->N[0][2]*(1-cRay->u) + ver1->N[0][2]*cRay->u*cRay->v + ver2->N[0][2]*cRay->u*(1-cRay->v);
}



///////////////////////////////////////////////////////////////////////
// Function				:	hierarchyDelete
// Description			:	Delete a hierarchy node and all children
// Return Value			:
// Comments				:
// Date last edited		:	12/23/2001
void		CHierarchy::deleteNode(void *cNode) {
	CHInternal			*cInternal;
	CHUncomputed		*cUncomputed;
	CHStack				*hierarchyStack		=	singleStack;
	CHStack				*hierarchyStackTop	=	hierarchyStack;

	hierarchyStackTop->node	=	cNode;
	hierarchyStackTop++;

	// tmin/tmax are not used
	while(hierarchyStackTop > hierarchyStack) {
		hierarchyStackTop--;

		switch(getData(hierarchyStackTop->node)) {
		case HIERARCHY_LEAF_NODE:
			stats.numHierarchyLeaves--;
			break;
		case HIERARCHY_INTERNAL_NODE:
			cInternal		=	(CHInternal *)	getPointer(hierarchyStackTop->node);
			hierarchyStackTop->node	=	cInternal->front;	hierarchyStackTop++;
			hierarchyStackTop->node	=	cInternal->back;	hierarchyStackTop++;
			stats.numHierarchyInternals--;
			break;
		case HIERARCHY_UNCOMPUTED_NODE:
			cUncomputed		=	(CHUncomputed *) getPointer(hierarchyStackTop->node);
			if (cUncomputed->items != NULL)	delete [] cUncomputed->items;
			delete cUncomputed;
			stats.numHierarchyUncomputeds--;
			break;
		case HIERARCHY_EMPTY_NODE:
			// Do nothing
			break;
		default:
			break;
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	hierarchyCompute
// Description			:	Compute an uncomputed node (called lazily)
// Return Value			:
// Comments				:
// Date last edited		:	12/23/2001
void		*CHierarchy::compute(CHUncomputed *cUncomputed) {
	void	*nNode;

	// Should I be an internal node ?
	if ((cUncomputed->depth < maxDepth) && (cUncomputed->numItems > maxObjects)) {
		vector				d;
		int					i,j,last,k;
		int					numItems		=	cUncomputed->numItems;
		CTracable			**items			=	cUncomputed->items;
		unsigned int		splitAxis;
		float				splitCoordinate;
		int					splitOrder[3];
		CTracable			**frontItems,**backItems;
		int					numFront,numBack;
		vector				fbmin,fbmax,bbmin,bbmax;

		memBegin();

		// Allocate a temporary memory to hold the items we partitioned
		frontItems				=	(CTracable **) ralloc(numItems*2*sizeof(CTracable *));
		backItems				=	frontItems + numItems;

		// Sort the coordinates
		subvv(d,cUncomputed->bmax,cUncomputed->bmin);
		if (d[COMP_X] > d[COMP_Y]) {
			// X > Y

			if (d[COMP_Y] > d[COMP_Z]) {
				// Y > Z
				splitOrder[0]	=	COMP_X;
				splitOrder[1]	=	COMP_Y;
				splitOrder[2]	=	COMP_Z;
			} else {
				// Y < Z

				if (d[COMP_Z] > d[COMP_X]) {
					// Z > X
					splitOrder[0]	=	COMP_Z;
					splitOrder[1]	=	COMP_X;
					splitOrder[2]	=	COMP_Y;
				} else {
					// X > Z
					splitOrder[0]	=	COMP_X;
					splitOrder[1]	=	COMP_Z;
					splitOrder[2]	=	COMP_Y;
				}
			}
		} else {
			// Y > X

			if (d[COMP_X] > d[COMP_Z]) {
				// X > Z
				splitOrder[0]	=	COMP_Y;
				splitOrder[1]	=	COMP_X;
				splitOrder[2]	=	COMP_Z;
			} else {
				// X < Z

				if (d[COMP_Y] > d[COMP_Z]) {
					// Y > Z
					splitOrder[0]	=	COMP_Y;
					splitOrder[1]	=	COMP_Z;
					splitOrder[2]	=	COMP_X;
				} else {
					// Y < Z
					splitOrder[0]	=	COMP_Z;
					splitOrder[1]	=	COMP_Y;
					splitOrder[2]	=	COMP_X;
				}
			}
		}

		// Try to partition the objects
		for (k=0;k<3;k++) {
			splitAxis		=	splitOrder[k];
			splitCoordinate	=	(cUncomputed->bmax[splitAxis] + cUncomputed->bmin[splitAxis]) * (float) 0.5;

			// Compute the bounds for the children
			movvv(fbmax,cUncomputed->bmax);
			movvv(fbmin,cUncomputed->bmin);
			fbmin[splitAxis]	=	splitCoordinate;

			movvv(bbmax,cUncomputed->bmax);
			movvv(bbmin,cUncomputed->bmin);
			bbmax[splitAxis]	=	splitCoordinate;

			// Partition the items
			for (i=0,last=0;i<numItems;i++) {
				if (items[i]->intersect(fbmin,fbmax)) {
					CTracable	*tItem	=	items[i];
					items[i]			=	items[last];
					items[last++]		=	tItem;
				}
			}
			numFront	=	last;
			memcpy(frontItems,items,numFront*sizeof(CTracable *));


			for (j=last,i=0,last=0;i<j;i++) {
				if (!items[i]->intersect(bbmin,bbmax)) {
					CTracable	*tItem	=	items[i];
					items[i]			=	items[last];
					items[last++]		=	tItem;
				}
			}
			numBack			=	numItems - last;
			memcpy(backItems,items+last,numBack*sizeof(CTracable *));

			if ((numFront != numItems) || (numBack != numItems)) break;
		}

		if (k == 3) {
			CHLeaf				*newNode;

			// We do not have a good split, create a leaf node
			newNode						=	(CHLeaf *) memory->alloc(sizeof(CHLeaf));
			stats.numHierarchyLeaves++;
			newNode->numItems			=	numItems;
			newNode->items				=	(CTracable **)	memory->alloc(sizeof(CTracable *)*numItems);
			memcpy(newNode->items,items,sizeof(CTracable *)*numItems);

			// We don't need this node anymore
			delete [] cUncomputed->items;
			delete cUncomputed;
			stats.numHierarchyUncomputeds--;

			nNode						=	(void *) getToken(newNode,HIERARCHY_LEAF_NODE);
			
		} else {
			CHInternal			*newNode;
			CHUncomputed		*front,*back;

			// We have a good split, create an internal node
			newNode						=	(CHInternal *) memory->alloc(sizeof(CHInternal));
			stats.numHierarchyInternals++;
			newNode->splitAxis			=	splitAxis;
			newNode->splitCoordinate	=	splitCoordinate;


			if (numFront > 0) {
				front					=	new CHUncomputed;
				stats.numHierarchyUncomputeds++;
				front->parent			=	newNode;
				front->depth			=	cUncomputed->depth+1;
				front->numItems			=	numFront;
				front->items			=	new CTracable*[numFront];
				movvv(front->bmin,fbmin);
				movvv(front->bmax,fbmax);
				for (j=0;j<numFront;j++)	{
					front->items[j]		=	frontItems[j];
				}
				newNode->front			=	(void *) getToken(front,HIERARCHY_UNCOMPUTED_NODE);
			} else {
				newNode->front			=	(void *) getToken(NULL,HIERARCHY_EMPTY_NODE);
			}


			if (numBack > 0) {
				back					=	new CHUncomputed;
				stats.numHierarchyUncomputeds++;
				back->parent			=	newNode;
				back->depth				=	cUncomputed->depth+1;
				back->numItems			=	numBack;
				back->items				=	new CTracable*[numBack];
				movvv(back->bmin,bbmin);
				movvv(back->bmax,bbmax);
				for (j=0;j<numBack;j++)	{
					back->items[j]		=	backItems[j];
				}
				newNode->back			=	(void *) getToken(back,HIERARCHY_UNCOMPUTED_NODE);
			} else {
				newNode->back			=	(void *) getToken(NULL,HIERARCHY_EMPTY_NODE);
			}

			// We don't need this node anymore
			delete [] cUncomputed->items;
			delete cUncomputed;
			stats.numHierarchyUncomputeds--;

			nNode						=	(void *) getToken(newNode,HIERARCHY_INTERNAL_NODE);
		}

		memEnd();
	} else {
		// We should be a leaf ...
		CHLeaf	*newNode;

		stats.numHierarchyUncomputeds--;
		stats.numHierarchyLeaves++;
		stats.numLeafItems	+=	cUncomputed->numItems;

		newNode				=	(CHLeaf *)		memory->alloc(sizeof(CHLeaf));
		newNode->numItems	=	cUncomputed->numItems;
		newNode->items		=	(CTracable **)	memory->alloc(sizeof(CTracable *)*newNode->numItems);
		memcpy(newNode->items,cUncomputed->items,sizeof(CTracable *)*newNode->numItems);

		nNode				=	(void *) getToken(newNode,HIERARCHY_LEAF_NODE);

		delete [] cUncomputed->items;
		delete cUncomputed;
	}

	return nNode;
}

///////////////////////////////////////////////////////////////////////
// Function				:	hierarchyIntersect
// Description			:	Intersection computation
// Return Value			:
// Comments				:
// Date last edited		:	12/23/2001
void		CHierarchy::intersect(void *r,CRay *ray,float tmin,float tmax) {
	int							i;
	CHLeaf						*cLeaf;
	CHInternal					*cInternal;
	CHUncomputed				*cUncomputed;
	float						t;
	CTracable					**items;
	void						*nNode;
	unsigned int				splitAxis;
	float						splitCoordinate;
	const float					*from				=	ray->from;
	const float					*to					=	ray->to;
	const float					*invDir				=	ray->invDir;
	CHStack						*hierarchyStack		=	singleStack;
	CHStack						*hierarchyStackTop	=	hierarchyStack;

	hierarchyStackTop->node		=	r;
	hierarchyStackTop->tmin		=	tmin;
	hierarchyStackTop->tmax		=	tmax;
	hierarchyStackTop++;

	while(hierarchyStackTop > hierarchyStack) {
		hierarchyStackTop--;

		switch(getData(hierarchyStackTop->node)) {
		case HIERARCHY_LEAF_NODE:
			cLeaf		=	(CHLeaf *)	getPointer(hierarchyStackTop->node);
			items		=	cLeaf->items;

			for (i=cLeaf->numItems-1;i>=0;i--) {
				// Mailbox check
				if (items[i]->ID == ray->ID) {
					continue;
				}

				items[i]->ID = ray->ID;

				items[i]->intersect(ray);
			}

			if (ray->t < hierarchyStackTop->tmax) {
				// We have an intersection
				return;
			}

			break;
		case HIERARCHY_INTERNAL_NODE:
			cInternal		=	(CHInternal *)	getPointer(hierarchyStackTop->node);

			tmin			=	hierarchyStackTop->tmin;
			tmax			=	hierarchyStackTop->tmax;

			splitAxis		=	cInternal->splitAxis;
			splitCoordinate	=	cInternal->splitCoordinate;

			if (to[splitAxis] == from[splitAxis]) {
				if (from[splitAxis] > splitCoordinate) {
					hierarchyStackTop->node	=	cInternal->front;
					hierarchyStackTop->tmin	=	tmin;
					hierarchyStackTop->tmax	=	tmax;
					hierarchyStackTop++;
				} else {
					hierarchyStackTop->node	=	cInternal->back;
					hierarchyStackTop->tmin	=	tmin;
					hierarchyStackTop->tmax	=	tmax;
					hierarchyStackTop++;
				}
			} else {
				t	=	(splitCoordinate - from[splitAxis]) * invDir[splitAxis];

				if (from[splitAxis] > splitCoordinate) {
					if (t > tmin) {
						if (t > tmax) {
							hierarchyStackTop->node	=	cInternal->front;
							hierarchyStackTop->tmin	=	tmin;
							hierarchyStackTop->tmax	=	tmax;
							hierarchyStackTop++;
						} else {
							hierarchyStackTop->node	=	cInternal->back;
							hierarchyStackTop->tmin	=	t;
							hierarchyStackTop->tmax	=	tmax;
							hierarchyStackTop++;

							hierarchyStackTop->node	=	cInternal->front;
							hierarchyStackTop->tmin	=	tmin;
							hierarchyStackTop->tmax	=	t;
							hierarchyStackTop++;
						}
					} else {
						if (t > 0) {
							hierarchyStackTop->node	=	cInternal->back;
							hierarchyStackTop->tmin	=	tmin;
							hierarchyStackTop->tmax	=	tmax;
							hierarchyStackTop++;
						} else {
							hierarchyStackTop->node	=	cInternal->front;
							hierarchyStackTop->tmin	=	tmin;
							hierarchyStackTop->tmax	=	tmax;
							hierarchyStackTop++;
						}
					}
				} else if (from[splitAxis] < splitCoordinate) {
					if (t > tmin) {
						if (t > tmax) {
							hierarchyStackTop->node	=	cInternal->back;
							hierarchyStackTop->tmin	=	tmin;
							hierarchyStackTop->tmax	=	tmax;
							hierarchyStackTop++;
						} else {
							hierarchyStackTop->node	=	cInternal->front;
							hierarchyStackTop->tmin	=	t;
							hierarchyStackTop->tmax	=	tmax;
							hierarchyStackTop++;

							hierarchyStackTop->node	=	cInternal->back;
							hierarchyStackTop->tmin	=	tmin;
							hierarchyStackTop->tmax	=	t;
							hierarchyStackTop++;
						}
					} else {
						if (t > 0) {
							hierarchyStackTop->node	=	cInternal->front;
							hierarchyStackTop->tmin	=	tmin;
							hierarchyStackTop->tmax	=	tmax;
							hierarchyStackTop++;
						} else {
							hierarchyStackTop->node	=	cInternal->back;
							hierarchyStackTop->tmin	=	tmin;
							hierarchyStackTop->tmax	=	tmax;
							hierarchyStackTop++;
						}
					}
				} else {
					if (invDir[splitAxis] > 0) {
						hierarchyStackTop->node	=	cInternal->front;
						hierarchyStackTop->tmin	=	tmin;
						hierarchyStackTop->tmax	=	tmax;
						hierarchyStackTop++;
					} else {
						hierarchyStackTop->node	=	cInternal->back;
						hierarchyStackTop->tmin	=	tmin;
						hierarchyStackTop->tmax	=	tmax;
						hierarchyStackTop++;
					}
				}
			}
			break;
		case HIERARCHY_UNCOMPUTED_NODE:
			cUncomputed		=	(CHUncomputed *)	getPointer(hierarchyStackTop->node);
			cInternal		=	cUncomputed->parent;
			nNode			=	compute(cUncomputed);

			if (cInternal == NULL) {
				root	=	nNode;
			} else {
				if (cInternal->front == hierarchyStackTop->node)
					cInternal->front	=	nNode;
				if (cInternal->back == hierarchyStackTop->node)
					cInternal->back		=	nNode;
			}

			hierarchyStackTop->node	=	nNode;
			hierarchyStackTop++;

			break;
		case HIERARCHY_EMPTY_NODE:
			// Do nothing
			break;
		default:
			break;
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	collect
// Description			:	Find the items near a point
// Return Value			:
// Comments				:
// Date last edited		:	12/23/2001
int			CHierarchy::collect(CTracable **n,const float *P,float dP) {
	int							i;
	CHLeaf						*cLeaf;
	CHInternal					*cInternal;
	CHUncomputed				*cUncomputed;
	CTracable					**items;
	void						*nNode;
	unsigned int				splitAxis;
	float						splitCoordinate;
	CHStack						*hierarchyStack		=	singleStack;
	CHStack						*hierarchyStackTop	=	hierarchyStack;
	int							numCollected		=	0;

	currentRayID++;

	hierarchyStackTop->node		=	root;
	hierarchyStackTop++;

	while(hierarchyStackTop > hierarchyStack) {
		hierarchyStackTop--;

		switch(getData(hierarchyStackTop->node)) {
		case HIERARCHY_LEAF_NODE:
			cLeaf		=	(CHLeaf *)	getPointer(hierarchyStackTop->node);
			items		=	cLeaf->items;

			for (i=cLeaf->numItems-1;i>=0;i--) {
				// Mailbox check
				if (items[i]->ID == currentRayID) {
					continue;
				}

				items[i]->ID	= currentRayID;
				*n++			=	items[i];
				numCollected++;

			}

			break;
		case HIERARCHY_INTERNAL_NODE:
			cInternal		=	(CHInternal *)	getPointer(hierarchyStackTop->node);

			splitAxis		=	cInternal->splitAxis;
			splitCoordinate	=	cInternal->splitCoordinate;

			if (P[splitAxis] > splitCoordinate) {
				hierarchyStackTop->node	=	cInternal->front;
				hierarchyStackTop++;

				if (	(P[splitAxis] - dP) < splitCoordinate) {
					hierarchyStackTop->node	=	cInternal->back;
					hierarchyStackTop++;
				}
			} else {
				hierarchyStackTop->node	=	cInternal->back;
				hierarchyStackTop++;

				if (	(P[splitAxis] + dP) > splitCoordinate) {
					hierarchyStackTop->node	=	cInternal->front;
					hierarchyStackTop++;
				}
			}
			break;
		case HIERARCHY_UNCOMPUTED_NODE:
			cUncomputed		=	(CHUncomputed *)	getPointer(hierarchyStackTop->node);
			cInternal		=	cUncomputed->parent;
			nNode			=	compute(cUncomputed);

			if (cInternal == NULL) {
				root	=	nNode;
			} else {
				if (cInternal->front == hierarchyStackTop->node)
					cInternal->front	=	nNode;
				if (cInternal->back == hierarchyStackTop->node)
					cInternal->back		=	nNode;
			}

			hierarchyStackTop->node	=	nNode;
			hierarchyStackTop++;

			break;
		case HIERARCHY_EMPTY_NODE:
			// Do nothing
			break;
		default:
			break;
		}
	}

	return numCollected;
}


///////////////////////////////////////////////////////////////////////
// Function				:	hierarchyAdd
// Description			:	Add bunch of tracables into the scene
// Return Value			:
// Comments				:
// Date last edited		:	12/23/2001
void		CHierarchy::add(void *node,CHInternal *parent,int depth,int numItems,CTracable **items,float *bmin,float *bmax) {
	int							i,j;
	CHLeaf						*cLeaf;
	CHInternal					*cInternal;
	CHUncomputed				*cUncomputed;
	void						*newNode;

	switch(getData(node)) {
	case HIERARCHY_LEAF_NODE:
		cLeaf					=	(CHLeaf *)	getPointer(node);
		cUncomputed				=	new CHUncomputed;
	
		cUncomputed->parent		=	parent;
		cUncomputed->depth		=	depth;
		cUncomputed->numItems	=	numItems + cLeaf->numItems;
		cUncomputed->items		=	new CTracable*[cUncomputed->numItems];
		movvv(cUncomputed->bmin,bmin);
		movvv(cUncomputed->bmax,bmax);

		for (i=0,j=0;i<cLeaf->numItems;i++,j++) {
			cUncomputed->items[j]	=	cLeaf->items[i];
		}

		for (i=0;i<numItems;i++,j++) {
			cUncomputed->items[j]	=	items[i];
		}

		newNode					=	(void *) getToken(cUncomputed,HIERARCHY_UNCOMPUTED_NODE);

		if (parent == NULL) {
			root				=	newNode;
		} else {
			if (parent->front == node)	parent->front	=	newNode;
			if (parent->back == node)	parent->back	=	newNode;
		}

		stats.numHierarchyUncomputeds++;
		stats.numHierarchyLeaves--;
		break;
	case HIERARCHY_INTERNAL_NODE:
		cInternal		=	(CHInternal *)	getPointer(node);

		vector			bmi,bma;
		int				last,j;

		movvv(bmi,bmin);
		movvv(bma,bmax);

		bmi[cInternal->splitAxis]	=	cInternal->splitCoordinate;

		for (i=0,last=0;i<numItems;i++) {
			if (items[i]->intersect(bmi,bma)) {
				CTracable	*cItem	=	items[last];
				items[last++]		=	items[i];
				items[i]			=	cItem;
			}
		}

		add(cInternal->front,cInternal,depth+1,last,items,bmi,bma);


		bmi[cInternal->splitAxis]	=	bmin[cInternal->splitAxis];
		bma[cInternal->splitAxis]	=	cInternal->splitCoordinate;

		for (j=last,i=0,last=0;i<j;i++) {
			if (!items[i]->intersect(bmi,bma)) {
				CTracable	*cItem	=	items[last];
				items[last++]		=	items[i];
				items[i]			=	cItem;
			}
		}

		items		+=	last;
		numItems	-=	last;
		add(cInternal->back,cInternal,depth+1,numItems,items,bmi,bma);
	break;
	case HIERARCHY_UNCOMPUTED_NODE:
		cUncomputed		=	(CHUncomputed *)	getPointer(node);
		CTracable		**newItems;
		
		newItems		=	new CTracable*[numItems + cUncomputed->numItems];

		for (i=0;i<cUncomputed->numItems;i++) {
			newItems[i]	=	cUncomputed->items[i];
		}

		for (j=i,i=0;i<numItems;i++,j++) {
			newItems[j]	=	items[i];
		}

		delete [] cUncomputed->items;
		cUncomputed->items		=	newItems;
		cUncomputed->numItems	+=	numItems;
	break;
	case HIERARCHY_EMPTY_NODE:
		cUncomputed				=	new CHUncomputed;

		cUncomputed->numItems	=	numItems;
		cUncomputed->items		=	new CTracable*[numItems];
		for (i=0;i<numItems;i++) cUncomputed->items[i]	=	items[i];
		cUncomputed->depth		=	depth;
		cUncomputed->parent		=	parent;
		movvv(cUncomputed->bmin,bmin);
		movvv(cUncomputed->bmax,bmax);

		newNode					=	(void *) getToken(cUncomputed,HIERARCHY_UNCOMPUTED_NODE);

		if (parent == NULL) {
			root				=	newNode;
		} else {
			if (parent->front == node)	parent->front	=	newNode;
			if (parent->back == node)	parent->back	=	newNode;
		}

		stats.numHierarchyUncomputeds++;
		break;
	default:
		break;
	}
}


///////////////////////////////////////////////////////////////////////
// Function				:	hierarchyRemove
// Description			:	Remove a tracable from the hierarchy
// Return Value			:
// Comments				:
// Date last edited		:	12/23/2001
void		CHierarchy::remove(void *node,const CTracable *item,float *bmin,float *bmax,float *ibmin,float *ibmax) {
	int							i,j;
	CHLeaf						*cLeaf;
	CHInternal					*cInternal;
	CHUncomputed				*cUncomputed;

	switch(getData(node)) {
	case HIERARCHY_LEAF_NODE:
		cLeaf					=	(CHLeaf *)	getPointer(node);

		for (i=0;i<cLeaf->numItems;i++) {
			if (cLeaf->items[i] == item) {
				for (j=i+1;j<cLeaf->numItems;j++) {
					cLeaf->items[j-1]	=	cLeaf->items[j];
				}
				cLeaf->numItems--;
				return;
			}
		}
	break;
	case HIERARCHY_INTERNAL_NODE:
		cInternal				=	(CHInternal *)	getPointer(node);
		vector	bmi,bma;

		movvv(bmi,bmin);
		movvv(bma,bmax);
		bmi[cInternal->splitAxis]	=	cInternal->splitCoordinate;
		if (intersectBox(bmi,bma,ibmin,ibmax)) {
			remove(cInternal->front,item,bmi,bma,ibmin,ibmax);
		}

		bmi[cInternal->splitAxis]	=	bmin[cInternal->splitAxis];
		bma[cInternal->splitAxis]	=	cInternal->splitCoordinate;
		if (intersectBox(bmi,bma,ibmin,ibmax)) {
			remove(cInternal->back,item,bmi,bma,ibmin,ibmax);
		}

	break;
	case HIERARCHY_UNCOMPUTED_NODE:
		cUncomputed				=	(CHUncomputed *)	getPointer(node);

		for (i=0;i<cUncomputed->numItems;i++) {
			if (cUncomputed->items[i] == item) {
				for (j=i+1;j<cUncomputed->numItems;j++) {
					cUncomputed->items[j-1]	=	cUncomputed->items[j];
				}
				cUncomputed->numItems--;
				return;
			}
		}
	break;
	case HIERARCHY_EMPTY_NODE:
	break;
	default:
		break;
	}

}





















///////////////////////////////////////////////////////////////////////
// Function				:	hierarchyInit
// Description			:	Init the hierarchy
// Return Value			:	-
// Comments				:
// Date last edited		:	12/23/2001
CHierarchy::CHierarchy(int numItems,CTracable **items,const float *tmin,const float *tmax,COptions *options,CMemStack *mem) {
	int						i;
	CTracable				**hitems	=	new CTracable*[numItems];
	CHUncomputed			*hroot		=	new CHUncomputed;

	memory				=	mem;

	for (i=0;i<numItems;i++) {
		items[i]->ID	=	-1;
		hitems[i]		=	items[i];
	}

	movvv(bmin,tmin);
	movvv(bmax,tmax);

	hroot->depth		=	0;
	hroot->parent		=	NULL;
	movvv(hroot->bmin,bmin);
	movvv(hroot->bmax,bmax);
	hroot->items		=	hitems;
	hroot->numItems		=	numItems;
	stats.numHierarchyUncomputeds++;


	root				=	(void *) getToken(hroot,HIERARCHY_UNCOMPUTED_NODE);
	
	// Set the default values
	maxDepth			=	options->maxHierarchyDepth;
	maxObjects			=	options->maxHierarchyLeafObjects;

	// Allocate the traversal stack
	singleStack			=	(CHStack *) memory->alloc(sizeof(CHStack)*maxDepth*2);
	currentRayID		=	0;
}


///////////////////////////////////////////////////////////////////////
// Function				:	hierarchyAdd
// Description			:	Add some tracables into the hierarchy
// Return Value			:	-
// Comments				:
// Date last edited		:	12/23/2001
void	CHierarchy::add(int numItems,CTracable **items) {
	add(root,NULL,0,numItems,items,bmin,bmax);
}

///////////////////////////////////////////////////////////////////////
// Function				:	hierarchyRemove
// Description			:	Remove occurances to an object from the hierarchy
// Return Value			:	-
// Comments				:
// Date last edited		:	12/23/2001
void	CHierarchy::remove(const CTracable *item,float *ibmin,float *ibmax) {
	remove(root,item,bmin,bmax,ibmin,ibmax);
}

///////////////////////////////////////////////////////////////////////
// Function				:	hierarchyTini
// Description			:	Destroy the hierarchy
// Return Value			:	-
// Comments				:
// Date last edited		:	12/23/2001
CHierarchy::~CHierarchy() {
	if (root != NULL)			deleteNode(root);
}

///////////////////////////////////////////////////////////////////////
// Function				:	hierarchyIntersect
// Description			:	Hierarchy traversal for intersection
// Return Value			:	-
// Comments				:
// Date last edited		:	12/23/2001
void	CHierarchy::intersect(CRay *ray) {
	float			tnear	=	ray->tmin;
	float			tfar	=	ray->t;
	float			t1,t2;
	unsigned int	i;
	float			*F		=	ray->from;
	float			*T		=	ray->to;
	float			*D		=	ray->invDir;

	for (i=0;i<3;i++) {
		if (F[i] == T[i]) {
			if ((F[i] > bmax[i]) || (F[i] < bmin[i])) return;
		} else {
			t1		=	(bmin[i] - F[i]) * D[i];
			t2		=	(bmax[i] - F[i]) * D[i];

			if (t1 < t2) {
				if (t1 > tnear)	tnear	= t1;
				if (t2 < tfar)	tfar	= t2;
			} else {
				if (t2 > tnear)	tnear	= t2;
				if (t1 < tfar)	tfar	= t1;
			}

			if (tnear > tfar) return;
		}
	}

	ray->ID		=	currentRayID++;
	intersect(root,ray,tnear,tfar);
}
