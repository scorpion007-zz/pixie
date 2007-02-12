//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright � 1999 - 2003, Okan Arikan
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
//  File				:	quadrics.cpp
//  Classes				:	CSphere
//							CDisk
//							CCone ...
//  Description			:	Implementation
//
//	FIXME: The quadrics implementation has not been heavily optimized
//	FIXME: Re-optimize
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "quadrics.h"
#include "common/os.h"
#include "object.h"
#include "stats.h"
#include "surface.h"
#include "memory.h"
#include "shading.h"
#include "renderer.h"
#include "rendererContext.h"
#include "objectMisc.h"
#include "common/polynomial.h"


#define	checkRay(rv)											\
	if (! (rv->flags & attributes->flags) )	return;				\
																\
	if (attributes->flags & ATTRIBUTES_FLAGS_LOD) {				\
		const float importance = attributes->lodImportance;		\
		if (importance >= 0) {									\
			if (rv->jimp > importance)			return;			\
		} else {												\
			if ((1-rv->jimp) >= -importance)	return;			\
		}														\
	}															\
																\
	if ((attributes->displacement != NULL) && (attributes->flags & ATTRIBUTES_FLAGS_DISPLACEMENTS)) {						\
		/* Do we have a grid ? */								\
		if (children == NULL) {									\
			osLock(CRenderer::tesselateMutex);					\
																\
			if (children == NULL) {								\
				osLock(CRenderer::refCountMutex);				\
				CTesselationPatch	*tesselation	=	new CTesselationPatch(attributes,xform,this,0,1,0,1,0,0,-1);	\
				osUnlock(CRenderer::refCountMutex);				\
				tesselation->initTesselation(context);			\
				tesselation->attach();							\
				children				=	tesselation;		\
			}													\
			osUnlock(CRenderer::tesselateMutex);				\
		}														\
		return;													\
	}															\
																\
	vector	oFrom,oDir;											\
	transform(oFrom,oDir,xform,rv);



#define	transformPoints()																			\
	if ((xform->next != NULL) && (!(up & (PARAMETER_BEGIN_SAMPLE | PARAMETER_END_SAMPLE)))) {		\
																									\
		transform(&varying[VARIABLE_P][start*3],numVertices,xform->from,xform->next->from,&varying[VARIABLE_TIME][start]);	\
																									\
		if (up & PARAMETER_DPDU) {																	\
			vtransform(&varying[VARIABLE_DPDU][start*3],numVertices,xform->from,xform->next->from,&varying[VARIABLE_TIME][start]);	\
		}																							\
																									\
		if (up & PARAMETER_DPDV) {																	\
			vtransform(&varying[VARIABLE_DPDV][start*3],numVertices,xform->from,xform->next->from,&varying[VARIABLE_TIME][start]);	\
		}																							\
																									\
		if (up & PARAMETER_NG) {																		\
			ntransform(&varying[VARIABLE_NG][start*3],numVertices,xform->to,xform->next->to,&varying[VARIABLE_TIME][start]);	\
		}																							\
	} else {																						\
		float	*from	=	xform->from;															\
		float	*to		=	xform->to;																\
																									\
		if ((up & PARAMETER_END_SAMPLE) && (xform->next != NULL))	{								\
			from	=	xform->next->from;															\
			to		=	xform->next->to;															\
		}																							\
																									\
																									\
		transform(&varying[VARIABLE_P][start*3],numVertices,from);									\
																									\
		if (up & PARAMETER_DPDU) {																	\
			vtransform(&varying[VARIABLE_DPDU][start*3],numVertices,from);							\
		}																							\
																									\
		if (up & PARAMETER_DPDV) {																	\
			vtransform(&varying[VARIABLE_DPDV][start*3],numVertices,from);							\
		}																							\
																									\
		if (up & PARAMETER_NG) {																	\
			ntransform(&varying[VARIABLE_NG][start*3],numVertices,to);								\
		}																							\
	}




#define	normalFix()	{																				\
	float		*Ng	=	varying[VARIABLE_NG];														\
	int			i;																					\
																									\
	for (i=numVertices;i>0;i--,Ng+=3) {																\
		if (dotvv(Ng,Ng) == 0) {																	\
			const float	*u		=	varying[VARIABLE_U];											\
			const float	*v		=	varying[VARIABLE_V];											\
			const float	*cNg	=	varying[VARIABLE_NG];											\
			const float	cu		=	u[numVertices-i];												\
			const float	cv		=	v[numVertices-i];												\
			float		cd		=	C_INFINITY;														\
			const float	*closest=	NULL;															\
			int			j;																			\
																									\
			for (j=numVertices;j>0;j--,cNg+=3,u++,v++) {											\
				if (dotvv(cNg,cNg) > 0) {															\
					const float	du	=	cu - u[0];													\
					const float	dv	=	cv - v[0];													\
					float		d;																	\
																									\
					d	=	du*du + dv*dv;															\
					if (d < cd) {																	\
						cd		=	d;																\
						closest	=	cNg;															\
					}																				\
				}																					\
			}																						\
																									\
			assert(cd < C_INFINITY);																\
			assert(closest != NULL);																\
			movvv(Ng,closest);																		\
		}																							\
	}																								\
}

//////////////////////////////////////////// S P H E R E ///////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////
// Class				:	CSphere
// Method				:	CSphere
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CSphere::CSphere(CAttributes *a,CXform *x,CParameter *c,unsigned int pf,float ra,float vmina,float vmaxa,float anglea) : CSurface(a,x)  {
	stats.gprimMemory	+=	sizeof(CSphere);
	stats.numGprims++;

	r			=	ra;
	vmin		=	vmina;
	vmax		=	vmaxa;
	umax		=	anglea;

	parameters	=	c;
	parametersF	=	PARAMETER_P | PARAMETER_NG | PARAMETER_DPDU | PARAMETER_DPDV | pf;

	nextData	=	NULL;

	computeObjectBound(bmin,bmax,r,vmin,vmax,umax);
	xform->transformBound(bmin,bmax);
	makeBound(bmin,bmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSphere
// Method				:	CSphere
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CSphere::CSphere(CAttributes *a,CXform *x,CParameter *c,unsigned int pf,float r0,float vmin0,float vmax0,float angle0,float r1,float vmin1,float vmax1,float angle1) : CSurface(a,x) {
	vector	tbmin,tbmax;

	stats.gprimMemory	+=	sizeof(CSphere);
	stats.gprimMemory	+=	sizeof(float)*4;
	stats.numGprims++;

	r			=	r0;
	vmin		=	vmin0;
	vmax		=	vmax0;
	umax		=	angle0;

	parameters	=	c;
	parametersF	=	PARAMETER_P | PARAMETER_NG | PARAMETER_DPDU | PARAMETER_DPDV | pf;

	nextData	=	new float[4];
	nextData[0]	=	r1;
	nextData[1]	=	vmin1;
	nextData[2]	=	vmax1;
	nextData[3]	=	angle1;

	computeObjectBound(bmin,bmax,r,vmin,vmax,umax);
	computeObjectBound(tbmin,tbmax,nextData[0],nextData[1],nextData[2],nextData[3]);
	addBox(bmin,bmax,tbmin);
	addBox(bmin,bmax,tbmax);
	xform->transformBound(bmin,bmax);
	makeBound(bmin,bmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSphere
// Method				:	~CSphere
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CSphere::~CSphere() {
	stats.gprimMemory	-=	sizeof(CSphere);
	stats.gprimMemory	-=	(nextData != NULL ? 4*sizeof(float) : 0);
	stats.numGprims--;

	if (parameters	!= NULL)	delete parameters;
	if (nextData	!= NULL)	delete [] nextData;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CSphere
// Method				:	intersect
// Description			:	Compute the intersection with a ray
// Return Value			:	TRUE if intersects
// Comments				:
void	CSphere::intersect(CShadingContext *context,CRay *rv) {
	unsigned int	ns,i;
	double			s[2];
	double			r,umax,vmin,vmax;

	checkRay(rv);

	if (nextData != NULL) {
		r		=	this->r		* (1-rv->time) + nextData[0] * rv->time;
		vmin	=	this->vmin	* (1-rv->time) + nextData[1] * rv->time;
		vmax	=	this->vmax	* (1-rv->time) + nextData[2] * rv->time;
		umax	=	this->umax	* (1-rv->time) + nextData[3] * rv->time;
	} else {
		r		=	this->r;
		vmin	=	this->vmin;
		vmax	=	this->vmax;
		umax	=	this->umax;
	}
	

	const double a	=	dotvv(oDir,oDir);
	const double b	=	2*dotvv(oDir,oFrom);
	const double c	=	dotvv(oFrom,oFrom) - r*r;

	if ((ns		=	solveQuadric<double>(a,b,c,s)) == 0) return;

	for (i=0;i<ns;i++) {
		double	P[3];
		float	t;
		double	u,v;
		vector	tmp;

		t		=	(float) s[i];

		if (t	<=	rv->tmin)		continue;
		if (t	>=	rv->t)			return;

		P[0]	=	oDir[0]*t + oFrom[0];
		P[1]	=	oDir[1]*t + oFrom[1];
		P[2]	=	oDir[2]*t + oFrom[2];

		if (r > 0) {
			u									=	atan2(P[COMP_Y],P[COMP_X]);
			if (P[COMP_Z] < -r)		P[COMP_Z]	=	-r;
			if (P[COMP_Z] > r)		P[COMP_Z]	=	r;
		} else {
			u									=	atan2(-P[COMP_Y],-P[COMP_X]);
			if (P[COMP_Z] < r)		P[COMP_Z]	=	r;
			if (P[COMP_Z] > -r)		P[COMP_Z]	=	-r;
		}

		if (u < 0) u	=	2*C_PI + u;

		if (umax < 0) {
			u			=	u - 2*C_PI;
			if (u < umax)	continue;
		} else {
			if (u > umax)	continue;
		}

		v				=	asin(P[COMP_Z] / r);
		v				=	(v - vmin) / (vmax - vmin);
		if (v < 0)	continue;
		if (v > 1)	continue;

		const double f	=	r*umax*(vmax-vmin);
		P[0]			*=	f;
		P[1]			*=	f;
		P[2]			*=	f;

		if ((attributes->flags & ATTRIBUTES_FLAGS_INSIDE) ^ xform->flip) {
			P[0]	=	-P[0];
			P[1]	=	-P[1];
			P[2]	=	-P[2];
		}

		if (attributes->nSides == 1) {
			if ((oDir[0]*P[0] + oDir[1]*P[1] + oDir[2]*P[2]) > 0) continue;
		}

		tmp[0]			=	(float) P[0];
		tmp[1]			=	(float) P[1];
		tmp[2]			=	(float) P[2];

		rv->object		=	this;
		rv->u			=	(float) (u	/	umax);
		rv->v			=	(float) v;
		rv->t			=	(float) t;
		mulmn(rv->N,xform->to,tmp);
		return;
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CSphere
// Method				:	sample
// Description			:	See object.h
// Return Value			:	-
// Comments				:
void			CSphere::sample(int start,int numVertices,float **varying,float ***locals,unsigned int &up) const {
	int				currentVertex;
	float			*dest;
	const float		*u		=	varying[VARIABLE_U] + start;
	const float		*v		=	varying[VARIABLE_V] + start;
	float			*sinu;
	float			*cosu;
	float			*sinv;
	float			*cosv;
	float			*memBase;

	memBase			=	(float *)	alloca(numVertices*4*sizeof(float));
	sinu			=	memBase;
	cosu			=	sinu + numVertices;
	sinv			=	cosu + numVertices;
	cosv			=	sinv + numVertices;

	if ((nextData != NULL) && (!(up & (PARAMETER_BEGIN_SAMPLE | PARAMETER_END_SAMPLE)))) {
		const float	*time	=	&varying[VARIABLE_TIME][start];
		float		*r,*umax,*vmax,*vmin;

		memBase			=	(float *)	alloca(numVertices*4*sizeof(float));
		r				=	memBase;
		umax			=	r + numVertices;
		vmax			=	umax + numVertices;
		vmin			=	vmax + numVertices;
		dest			=	varying[VARIABLE_P] + start;

		// Precompute sinu cosu sinv and cosv
		for (currentVertex = 0; currentVertex < numVertices; currentVertex++) {
			const float ctime		=	*time++;
			const float	cumax		=	umax[currentVertex]		=	this->umax * (1 - ctime)	+ nextData[3] * ctime;
			const float	cvmax		=	vmax[currentVertex]		=	this->vmax * (1 - ctime)	+ nextData[2] * ctime;
			const float	cvmin		=	vmin[currentVertex]		=	this->vmin * (1 - ctime)	+ nextData[1] * ctime;
			r[currentVertex]		=	this->r * (1 - ctime)		+ nextData[0] * ctime;

			// Precompute sinu cosu sinv and cosv
			const float	cu			=	*u++;
			const float	cv			=	*v++;
			const float	uAngle		=	cumax*cu;
			const float	vAngle		=	cvmax*cv + cvmin*(1-cv);
			sinu[currentVertex]		=	sinf(uAngle);
			cosu[currentVertex]		=	cosf(uAngle);
			sinv[currentVertex]		=	sinf(vAngle);
			cosv[currentVertex]		=	cosf(vAngle);

			const float	tmp			=	r[currentVertex]*cosv[currentVertex];
			dest[COMP_Z]			=	r[currentVertex]*sinv[currentVertex];
			dest[COMP_X]			=	tmp*cosu[currentVertex];
			dest[COMP_Y]			=	tmp*sinu[currentVertex];
			dest					+=	3;
		}

			// Set dPdu
		if (up & PARAMETER_DPDU) {
			float	*src	=	&varying[VARIABLE_P][start*3];
					dest	=	&varying[VARIABLE_DPDU][start*3];

			for (currentVertex = 0; currentVertex < numVertices; currentVertex++) {
				dest[COMP_X]	=	-umax[currentVertex]*src[COMP_Y];
				dest[COMP_Y]	=	umax[currentVertex]*src[COMP_X];
				dest[COMP_Z]	=	0;
				dest			+=	3;
				src				+=	3;
			}
		}

		// Set dPdv
		if (up & PARAMETER_DPDV) {
			dest	=	&varying[VARIABLE_DPDV][start*3];

			for (currentVertex = 0; currentVertex < numVertices; currentVertex++) {
				dest[COMP_X]	=	-r[currentVertex]*cosu[currentVertex]*sinv[currentVertex]*(vmax[currentVertex]-vmin[currentVertex]);
				dest[COMP_Y]	=	-r[currentVertex]*sinu[currentVertex]*sinv[currentVertex]*(vmax[currentVertex]-vmin[currentVertex]);
				dest[COMP_Z]	=	r[currentVertex]*cosv[currentVertex]*(vmax[currentVertex]-vmin[currentVertex]);
				dest			+=	3;
			}
		}
	} else {
		float	r		=	this->r;
		float	umax	=	this->umax;
		float	vmin	=	this->vmin;
		float	vmax	=	this->vmax;

		if ((up & PARAMETER_END_SAMPLE) && (nextData != NULL)) {
			r		=	nextData[0];
			vmin	=	nextData[1];
			vmax	=	nextData[2];
			umax	=	nextData[3];
		}

		// Precompute sinu cosu sinv and cosv
		dest	=	&varying[VARIABLE_P][start*3];
		for (currentVertex = 0; currentVertex < numVertices; currentVertex++) {
			const float	uAngle	=	umax*u[currentVertex];
			const float	vAngle	=	vmax*v[currentVertex] + vmin*(1-v[currentVertex]);
			sinu[currentVertex]	=	sinf(uAngle);
			cosu[currentVertex]	=	cosf(uAngle);
			sinv[currentVertex]	=	sinf(vAngle);
			cosv[currentVertex]	=	cosf(vAngle);

			const float	tmp		=	r*cosv[currentVertex];
			dest[COMP_Z]		=	r*sinv[currentVertex];
			dest[COMP_X]		=	tmp*cosu[currentVertex];
			dest[COMP_Y]		=	tmp*sinu[currentVertex];
			dest				+=	3;
		}

			// Set dPdu
		if (up & PARAMETER_DPDU) {
			const float	*src	=	&varying[VARIABLE_P][start*3];
						dest	=	&varying[VARIABLE_DPDU][start*3];


			for (currentVertex = 0; currentVertex < numVertices; currentVertex++) {
				dest[COMP_X]	=	-umax*src[COMP_Y];
				dest[COMP_Y]	=	umax*src[COMP_X];
				dest[COMP_Z]	=	0;
				dest			+=	3;
				src				+=	3;
			}
		}

		// Set dPdv
		if (up & PARAMETER_DPDV) {
			dest	=	&varying[VARIABLE_DPDV][start*3];

			for (currentVertex = 0; currentVertex < numVertices; currentVertex++) {
				dest[COMP_X]	=	-r*cosu[currentVertex]*sinv[currentVertex]*(vmax-vmin);
				dest[COMP_Y]	=	-r*sinu[currentVertex]*sinv[currentVertex]*(vmax-vmin);
				dest[COMP_Z]	=	r*cosv[currentVertex]*(vmax-vmin);
				dest			+=	3;
			}
		}

	}

	// Set Ng
	if (up & PARAMETER_NG) {
		float		*N	=	varying[VARIABLE_NG] + start*3;
		const float	*P	=	varying[VARIABLE_P] + start*3;
		float		f	=	r*umax*(vmax-vmin);

		if (xform->flip)	f	*=	-1;

		for (int i=numVertices;i>0;i--,N+=3,P+=3) {
			mulvf(N,P,f);
		}
	}

	// Transform the points
	transformPoints();

	up	&=	~parametersF;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSphere
// Method				:	interpolate
// Description			:	See object.h
// Return Value			:	-
// Comments				:
void			CSphere::interpolate(int numVertices,float **varying,float ***locals) const {
	if (parameters != NULL)	parameters->dispatch(numVertices,varying,locals);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSphere
// Method				:	instantiate
// Description			:	See object.h
// Return Value			:	-
// Comments				:
void	CSphere::instantiate(CAttributes *a,CXform *x,CRendererContext *cx) const {
	CXform		*nx	=	new CXform(x);

	nx->concat(xform);	// Concetenate the local xform

	if (a == NULL)	a	=	attributes;

	if (nextData == NULL)
		cx->addObject(new CSphere(a,nx,(parameters == NULL ? NULL : parameters->clone(a)),parametersF,r,vmin,vmax,umax));
	else
		cx->addObject(new CSphere(a,nx,(parameters == NULL ? NULL : parameters->clone(a)),parametersF,r,vmin,vmax,umax,nextData[0],nextData[1],nextData[2],nextData[3]));
}

///////////////////////////////////////////////////////////////////////
// Class				:	CSphere
// Method				:	computeObjectBound
// Description			:	Compute the bounding box in the object space
// Return Value			:	-
// Comments				:
void			CSphere::computeObjectBound(float *bmin,float *bmax,float r,float vmin,float vmax,float umax) {
	float	maxRadius;
	float	vmi		=	min(vmin,vmax);
	float	vma		=	max(vmin,vmax);
	float	zmin;
	float	zmax;

	r				=	absf(r);

	zmin			=	r*sinf(vmin);
	zmax			=	r*sinf(vmax);

	if (vmi > 0) {
		maxRadius	=	(float) cos(vmi)*r;
	} else if (vma < 0) {
		maxRadius	=	(float) cos(vma)*r;
	} else {
		maxRadius	=	r;
	}

	initv(bmin,-maxRadius,-maxRadius,min(zmin,zmax));
	initv(bmax,maxRadius,maxRadius,max(zmin,zmax));
}























//////////////////////////////////////////// D I S K ///////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
// Class				:	CDisk
// Method				:	CDisk
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CDisk::CDisk(CAttributes *a,CXform *x,CParameter *c,unsigned int pf,float ra,float za,float anglea) : CSurface(a,x)  {
	stats.gprimMemory	+=	sizeof(CDisk);
	stats.numGprims++;

	r				=	ra;
	z				=	za;
	umax			=	anglea;

	parameters		=	c;
	parametersF		=	PARAMETER_P | PARAMETER_NG | PARAMETER_DPDU | PARAMETER_DPDV | pf;

	nextData		=	NULL;

	computeObjectBound(bmin,bmax,r,z,umax);
	xform->transformBound(bmin,bmax);
	makeBound(bmin,bmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDisk
// Method				:	CDisk
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CDisk::CDisk(CAttributes *a,CXform *x,CParameter *c,unsigned int pf,float r0,float z0,float angle0,float r1,float z1,float angle1) : CSurface(a,x) {
	vector	tbmin,tbmax;

	stats.gprimMemory	+=	sizeof(CDisk);
	stats.gprimMemory	+=	sizeof(float)*3;
	stats.numGprims++;

	r			=	r0;
	z			=	z0;
	umax		=	angle0;

	parameters	=	c;
	parametersF	=	PARAMETER_P | PARAMETER_NG | PARAMETER_DPDU | PARAMETER_DPDV | pf;

	nextData	=	new float[3];
	nextData[0]	=	r1;
	nextData[1]	=	z1;
	nextData[2]	=	angle1;

	computeObjectBound(bmin,bmax,r,z,umax);
	computeObjectBound(tbmin,tbmax,nextData[0],nextData[1],nextData[2]);
	addBox(bmin,bmax,tbmin);
	addBox(bmin,bmax,tbmax);
	xform->transformBound(bmin,bmax);
	makeBound(bmin,bmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDisk
// Method				:	~CDisk
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CDisk::~CDisk() {
	stats.gprimMemory	-=	sizeof(CDisk);
	stats.gprimMemory	-=	(nextData != NULL ? 3*sizeof(float) : 0);
	stats.numGprims--;

	if (parameters	!= NULL)	delete parameters;
	if (nextData	!= NULL)	delete [] nextData;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CDisk
// Method				:	intersect
// Description			:	Compute the intersection with a ray
// Return Value			:	TRUE if intersects
// Comments				:
void	CDisk::intersect(CShadingContext *context,CRay *rv) {
	float	t;
	double	u;
	double	x,y;
	double	r,z,umax;
	vector	Nt;

	checkRay(rv);

	// Convert to the object coordinate system
	if (nextData != NULL) {
		r		=	this->r		* (1-rv->time) + nextData[0] * rv->time;
		z		=	this->z		* (1-rv->time) + nextData[1] * rv->time;
		umax	=	this->umax	* (1-rv->time) + nextData[2] * rv->time;
	} else {
		r		=	this->r;
		z		=	this->z;
		umax	=	this->umax;
	}

	t	=	(float) (z - oFrom[COMP_Z])/oDir[COMP_Z];

	if ((t <= rv->tmin) || (t >= rv->t)) return;

	x	=	oFrom[COMP_X] + oDir[COMP_X]*t;
	y	=	oFrom[COMP_Y] + oDir[COMP_Y]*t;
	if ((x*x+y*y) > r*r) return;

	if (r < 0)	u	=	atan2(-y,-x);
	else		u	=	atan2(y,x);

	if (u < 0)	u	=	2*C_PI + u;

	if (umax < 0) {
		u	=	u - 2*C_PI;
		if (u < umax) return;
	} else {
		if (u > umax) return;
	}

	initv(Nt,0,0,(float) umax);

	if ((attributes->flags & ATTRIBUTES_FLAGS_INSIDE) ^ xform->flip) {
		mulvf(Nt,-1);
	}

	if (attributes->nSides == 1) {
		if (dotvv(oDir,Nt) > 0) {
			return;
		}
	}

	rv->object	=	this;
	rv->u		=	(float) (u / umax);
	if (r > 0) {
		rv->v	=	(float) (((r-sqrt(x*x + y*y))) / r);
	} else {
		rv->v	=	(float) (((r+sqrt(x*x + y*y))) / r);
	}
	rv->t		=	(float) t;
	mulmn(rv->N,xform->to,Nt);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDisk
// Method				:	sample
// Description			:	See object.h
// Return Value			:	-
// Comments				:
void			CDisk::sample(int start,int numVertices,float **varying,float ***locals,unsigned int &up) const {
	float			*sinu;
	float			*cosu;
	int				i;
	const float		*u		=	&varying[VARIABLE_U][start];
	const float		*v		=	&varying[VARIABLE_V][start];
	float			*dest;
	float			*memBase;

	// Allocate memory for precomputing sin(u) , cos(u)
	memBase	=	(float *)	alloca(numVertices*2*sizeof(float));
	sinu	=	memBase;
	cosu	=	sinu + numVertices;

	if ((nextData != NULL) && (!(up & (PARAMETER_BEGIN_SAMPLE | PARAMETER_END_SAMPLE)))) {
		const float	*time	=	&varying[VARIABLE_TIME][start];
		float		*r;
		float		*z;
		float		*umax;

		memBase				=	(float *)	alloca(numVertices*3*sizeof(float));
		r					=	memBase;
		z					=	r + numVertices;
		umax				=	z + numVertices;
		dest				=	varying[VARIABLE_P] + start*3;

		// Precompute sinu cosu sinv and cosv
		for (i=0;i<numVertices;i++,dest+=3) {
			const float ctime	=	*time++;

			r[i]			=	this->r * (1 - ctime)		+ nextData[0] * ctime;
			z[i]			=	this->z * (1 - ctime)		+ nextData[1] * ctime;
			umax[i]			=	this->umax * (1 - ctime)	+ nextData[2] * ctime;
			cosu[i]			=	cosf(u[i]*umax[i]);
			sinu[i]			=	sinf(u[i]*umax[i]);

			dest[COMP_X]	=	r[i]*(1-v[i])*cosu[i];
			dest[COMP_Y]	=	r[i]*(1-v[i])*sinu[i];
			dest[COMP_Z]	=	z[i];
		}

		// Set dPdu/dPdv if needed
		if (up & (PARAMETER_DPDU | PARAMETER_DPDU)) {
			float	*dPdu	=	&varying[VARIABLE_DPDU][start*3];
			float	*dPdv	=	&varying[VARIABLE_DPDV][start*3];

			for (i=0;i<numVertices;i++) {
				dPdu[COMP_X]	=	-umax[i]*r[i]*(1-v[i])*sinu[i];
				dPdu[COMP_Y]	=	umax[i]*r[i]*(1-v[i])*cosu[i];
				dPdu[COMP_Z]	=	0;
				dPdv[COMP_X]	=	-r[i]*cosu[i];
				dPdv[COMP_Y]	=	-r[i]*sinu[i];
				dPdv[COMP_Z]	=	0;
				dPdu			+=	3;
				dPdv			+=	3;
			}
		}
	} else {
		float	r		=	this->r;
		float	z		=	this->z;
		float	umax	=	this->umax;

		if ((up & PARAMETER_END_SAMPLE) && (nextData != NULL)) {
			r		=	nextData[0];
			z		=	nextData[1];
			umax	=	nextData[2];
		}

		// Precompute the sin/cos for u points
		dest			=	varying[VARIABLE_P] + start*3;
		for (i=0;i<numVertices;i++,dest+=3) {
			cosu[i]			=	cosf(u[i]*umax);
			sinu[i]			=	sinf(u[i]*umax);
			dest[COMP_X]	=	r*(1-v[i])*cosu[i];
			dest[COMP_Y]	=	r*(1-v[i])*sinu[i];
			dest[COMP_Z]	=	z;
		}

		// Set dPdu/dPdv if needed
		if (up & (PARAMETER_DPDU | PARAMETER_DPDU)) {
			float	*dPdu	=	&varying[VARIABLE_DPDU][start*3];
			float	*dPdv	=	&varying[VARIABLE_DPDV][start*3];

			for (i=0;i<numVertices;i++) {
				dPdu[COMP_X]	=	-umax*r*(1-v[i])*sinu[i];
				dPdu[COMP_Y]	=	umax*r*(1-v[i])*cosu[i];
				dPdu[COMP_Z]	=	0;
				dPdv[COMP_X]	=	-r*cosu[i];
				dPdv[COMP_Y]	=	-r*sinu[i];
				dPdv[COMP_Z]	=	0;
				dPdu			+=	3;
				dPdv			+=	3;
			}
		}
	}

	// Set Ng if needed
	if (up & PARAMETER_NG) {
		float	*Ng		=	&varying[VARIABLE_NG][start*3];
		float	f		=	umax;

		if (xform->flip)	f	=	-umax;

		for (i=numVertices;i>0;i--,Ng+=3) {
			initv(Ng,0,0,f);
		}
	}
	
	// Transform the points
	transformPoints();

	up	&=	~parametersF;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDisk
// Method				:	interpolate
// Description			:	See object.h
// Return Value			:	-
// Comments				:
void			CDisk::interpolate(int numVertices,float **varying,float ***locals) const {
	if (parameters != NULL)	parameters->dispatch(numVertices,varying,locals);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDisk
// Method				:	instantiate
// Description			:	See object.h
// Return Value			:	-
// Comments				:
void			CDisk::instantiate(CAttributes *a,CXform *x,CRendererContext *cx) const {
	CXform		*nx	=	new CXform(x);

	nx->concat(xform);	// Concetenate the local xform

	if (a == NULL)	a	=	attributes;

	if (nextData == NULL)
		cx->addObject(new CDisk(a,nx,parameters,parametersF,r,z,umax));
	else
		cx->addObject(new CDisk(a,nx,parameters,parametersF,r,z,umax,nextData[0],nextData[1],nextData[2]));
}

///////////////////////////////////////////////////////////////////////
// Class				:	CDisk
// Method				:	computeObjectBound
// Description			:	Compute the bounding box in the object space
// Return Value			:	-
// Comments				:
void			CDisk::computeObjectBound(float *bmin,float *bmax,float r,float z,float umax) {
	r	=	absf(r);

	initv(bmin,-r,-r,z);
	initv(bmax,r,r,z);
}
























//////////////////////////////////////////// C O N E ///////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////
// Class				:	CCone
// Method				:	CCone
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CCone::CCone(CAttributes *a,CXform *x,CParameter *c,unsigned int pf,float ra,float heighta,float anglea) : CSurface(a,x)  {
	stats.gprimMemory	+=	sizeof(CCone);
	stats.numGprims++;

	r				=	ra;
	height			=	heighta;
	umax			=	anglea;

	parameters		=	c;
	parametersF		=	PARAMETER_P | PARAMETER_NG | PARAMETER_DPDU | PARAMETER_DPDV | pf;

	nextData		=	NULL;

	computeObjectBound(bmin,bmax,r,height,umax);
	xform->transformBound(bmin,bmax);
	makeBound(bmin,bmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CCone
// Method				:	CCone
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CCone::CCone(CAttributes *a,CXform *x,CParameter *c,unsigned int pf,float r0,float height0,float angle0,float r1,float height1,float angle1) : CSurface(a,x) {
	vector	tbmin,tbmax;

	stats.gprimMemory	+=	sizeof(CCone);
	stats.gprimMemory	+=	sizeof(float)*3;
	stats.numGprims++;

	r				=	r0;
	height			=	height0;
	umax			=	angle0;

	parameters		=	c;
	parametersF		=	PARAMETER_P | PARAMETER_NG | PARAMETER_DPDU | PARAMETER_DPDV | pf;

	nextData		=	new float[3];
	nextData[0]		=	r1;
	nextData[1]		=	height1;
	nextData[2]		=	angle1;

	computeObjectBound(bmin,bmax,r,height,umax);
	computeObjectBound(tbmin,tbmax,nextData[0],nextData[1],nextData[2]);
	addBox(bmin,bmax,tbmin);
	addBox(bmin,bmax,tbmax);
	xform->transformBound(bmin,bmax);
	makeBound(bmin,bmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CCone
// Method				:	~CCone
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CCone::~CCone() {
	stats.gprimMemory	-=	sizeof(CCone);
	stats.gprimMemory	-=	(nextData != NULL ? 3*sizeof(float) : 0);
	stats.numGprims--;

	if (parameters	!= NULL)	delete parameters;
	if (nextData	!= NULL)	delete [] nextData;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CCone
// Method				:	intersect
// Description			:	Compute the intersection with a ray
// Return Value			:	TRUE if intersects
// Comments				:
void	CCone::intersect(CShadingContext *context,CRay *rv) {
	float			*from;
	float			*dir;
	double			s[2];
	unsigned int	ns,i;
	double			height,r,umax;
	vector			Nt;

	checkRay(rv);

	from	=	oFrom;
	dir		=	oDir;

	if (nextData != NULL) {
		r		=	this->r *		(1-rv->time) + nextData[0] * rv->time;
		height	=	this->height *	(1-rv->time) + nextData[1] * rv->time;
		umax	=	this->umax *	(1-rv->time) + nextData[2] * rv->time;
	} else {
		r		=	this->r;
		height	=	this->height;
		umax	=	this->umax;
	}


	if (height*height < C_EPSILON) {
		// We're a disc
		ns		=	1;
		s[0]	=	-from[COMP_Z] / dir[COMP_Z];
	} else {
		const double	a		=	height*height*(dir[COMP_X]*dir[COMP_X] + dir[COMP_Y]*dir[COMP_Y]) - r*r*dir[COMP_Z]*dir[COMP_Z];
		const double	b		=	height*height*2*(from[COMP_X]*dir[COMP_X] + from[COMP_Y]*dir[COMP_Y]) - r*r*2*(from[COMP_Z]-height)*dir[COMP_Z];
		const double	c		=	height*height*(from[COMP_X]*from[COMP_X] + from[COMP_Y]*from[COMP_Y]) - r*r*(from[COMP_Z]-height)*(from[COMP_Z]-height);

		if ((ns	= solveQuadric<double>(a,b,c,s)) == 0) return;
	}


	for (i=0;i<ns;i++) {
		float	t	=	(float) s[i];
		double	u,v;
		double	P[3];

		if (t <= rv->tmin)	continue;
		if (t >= rv->t)		return;

		P[COMP_Z]	=	oDir[COMP_Z]*t + oFrom[COMP_Z];

		if (height < 0) {
			if (P[COMP_Z] < height) continue;
			if (P[COMP_Z] > 0)		continue;
		} else if (height > 0) {
			if (P[COMP_Z] > height) continue;
			if (P[COMP_Z] < 0) 		continue;
		}

		P[COMP_X]					=	oDir[COMP_X]*t + oFrom[COMP_X];
		P[COMP_Y]					=	oDir[COMP_Y]*t + oFrom[COMP_Y];

		if (r > 0) 	u				=	atan2(P[COMP_Y],P[COMP_X]);
		else 		u				=	atan2(-P[COMP_Y],-P[COMP_X]);

		if (u < 0)	u				=	2*C_PI + u;
		if (umax < 0) {
			u	=	u - 2*C_PI;
			if (u < umax) {
				continue;
			}
		} else {
			if (u > umax) {
				continue;
			}
		}

		if (r*r > height*height)	v			=	1 - sqrt((P[COMP_X]*P[COMP_X] + P[COMP_Y]*P[COMP_Y]) / (r*r));
		else						v			=	P[COMP_Z] / height;

		if (v < 0)	{
			continue;
		}

		Nt[COMP_X]					=	(float) (P[COMP_X]*height*umax);
		Nt[COMP_Y]					=	(float) (P[COMP_Y]*height*umax);
		Nt[COMP_Z]					=	(float) (r*r*umax*(1 - v));
		if ((attributes->flags & ATTRIBUTES_FLAGS_INSIDE) ^ xform->flip) {
			mulvf(Nt,-1);
		}

		if (attributes->nSides == 1) {
			if (dotvv(oDir,Nt) > 0) {
				continue;
			}
		}

		rv->object	=	this;
		rv->u		=	(float) (u / umax);
		rv->v		=	(float) v;
		rv->t		=	(float) t;
		mulmn(rv->N,xform->to,Nt);
		return;
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CCone
// Method				:	sample
// Description			:	See object.h
// Return Value			:	-
// Comments				:
void			CCone::sample(int start,int numVertices,float **varying,float ***locals,unsigned int &up) const {
	float		*cosu;
	float		*sinu;
	int			i;
	const float	*u		=	varying[VARIABLE_U] + start;
	const float	*v		=	varying[VARIABLE_V] + start;
	float		*dest;
	float		*memBase;

	// Allocate memory for precomputing sin(u) , cos(u)
	memBase	=	(float *)	alloca(numVertices*2*sizeof(float));
	sinu	=	memBase;
	cosu	=	sinu + numVertices;


	// Precompute the sin/cos for u points
	for (i=0;i<numVertices;i++) {
		cosu[i]	=	cosf(u[i]*umax);
		sinu[i]	=	sinf(u[i]*umax);
	}

	if ((nextData != NULL) && (!(up & (PARAMETER_BEGIN_SAMPLE | PARAMETER_END_SAMPLE)))) {
		const float	*time		=	varying[VARIABLE_TIME] + start;
		float		*r;
		float		*height;
		float		*umax;

		memBase			=	(float *)	alloca(numVertices*sizeof(float));
		r				=	memBase;
		height			=	r + numVertices;
		umax			=	height + numVertices;

		// Precompute sinu cosu sinv and cosv
		dest			=	varying[VARIABLE_P] + start*3;
		for (i=0;i<numVertices;i++,dest+=3) {
			r[i]			=	this->r * (1 - time[i])			+ nextData[0] * time[i];
			height[i]		=	this->height * (1 - time[i])	+ nextData[1] * time[i];
			umax[i]			=	this->umax * (1 - time[i])		+ nextData[2] * time[i];
			dest[COMP_X]	=	r[i]*(1-v[i])*cosu[i];
			dest[COMP_Y]	=	r[i]*(1-v[i])*sinu[i];
			dest[COMP_Z]	=	v[i]*height[i];
		}

		// Set Ng if needed
		if (up & PARAMETER_NG) {
			float		*Ng		=	varying[VARIABLE_NG] + start*3;
			const float	*P		=	varying[VARIABLE_P] + start*3;

			for (i=0;i<numVertices;i++) {
				Ng[COMP_X]	=	P[COMP_X]*umax[i]*height[i];
				Ng[COMP_Y]	=	P[COMP_Y]*umax[i]*height[i];
				Ng[COMP_Z]	=	r[i]*r[i]*umax[i]*(1-v[i]);
				Ng			+=	3;
				P			+=	3;
			}
		}

		// Set dPdu/dPdv if needed
		if (up & (PARAMETER_DPDU | PARAMETER_DPDU)) {
			float	*dPdu	=	&varying[VARIABLE_DPDU][start*3];
			float	*dPdv	=	&varying[VARIABLE_DPDV][start*3];

			for (i=0;i<numVertices;i++) {
				dPdu[COMP_X]	=	-umax[i]*r[i]*(1-v[i])*sinu[i];
				dPdu[COMP_Y]	=	umax[i]*r[i]*(1-v[i])*cosu[i];
				dPdu[COMP_Z]	=	0;
				dPdv[COMP_X]	=	-r[i]*cosu[i];
				dPdv[COMP_Y]	=	-r[i]*sinu[i];
				dPdv[COMP_Z]	=	height[i];
				dPdu			+=	3;
				dPdv			+=	3;
			}
		}
	} else {
		float	r		=	this->r;
		float	height	=	this->height;
		float	umax	=	this->umax;

		if ((up & PARAMETER_END_SAMPLE) && (nextData != NULL)) {
			r			=	nextData[0];
			height		=	nextData[1];
			umax		=	nextData[2];
		}

		// Set u/v/P
		for (i=0,dest=&varying[VARIABLE_P][start*3];i<numVertices;i++) {
			dest[COMP_X]	=	r*(1-v[i])*cosu[i];
			dest[COMP_Y]	=	r*(1-v[i])*sinu[i];
			dest[COMP_Z]	=	v[i]*height;
			dest			+=	3;
		}

		// Set Ng if needed
		if (up & PARAMETER_NG) {
			float		*Ng		=	varying[VARIABLE_NG] + start*3;
			const float	*P		=	varying[VARIABLE_P] + start*3;

			for (i=0;i<numVertices;i++) {
				Ng[COMP_X]	=	P[COMP_X]*height*umax;
				Ng[COMP_Y]	=	P[COMP_Y]*height*umax;
				Ng[COMP_Z]	=	r*r*umax*(1-v[i]);
				Ng			+=	3;
				P			+=	3;
			}
		}

		// Set dPdu/dPdv if needed
		if (up & (PARAMETER_DPDU | PARAMETER_DPDU)) {
			float	*dPdu	=	&varying[VARIABLE_DPDU][start*3];
			float	*dPdv	=	&varying[VARIABLE_DPDV][start*3];

			for (i=0;i<numVertices;i++) {
				dPdu[COMP_X]	=	-umax*r*(1-v[i])*sinu[i];
				dPdu[COMP_Y]	=	umax*r*(1-v[i])*cosu[i];
				dPdu[COMP_Z]	=	0;
				dPdv[COMP_X]	=	-r*cosu[i];
				dPdv[COMP_Y]	=	-r*sinu[i];
				dPdv[COMP_Z]	=	height;
				dPdu			+=	3;
				dPdv			+=	3;
			}
		}
	}

	if (xform->flip == 1) {
		float	*N	=	varying[VARIABLE_NG] + start*3;

		for (int i=numVertices;i>0;i--,N+=3) {
			mulvf(N,-1);
		}
	}

	// Transform the points
	transformPoints();

	up	&=	~parametersF;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CCone
// Method				:	interpolate
// Description			:	See object.h
// Return Value			:	-
// Comments				:
void			CCone::interpolate(int numVertices,float **varying,float ***locals) const {
	if (parameters != NULL)	parameters->dispatch(numVertices,varying,locals);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CCone
// Method				:	instantiate
// Description			:	See object.h
// Return Value			:	-
// Comments				:
void			CCone::instantiate(CAttributes *a,CXform *x,CRendererContext *cx) const {
	CXform		*nx	=	new CXform(x);

	nx->concat(xform);	// Concetenate the local xform

	if (a == NULL)	a	=	attributes;

	if (nextData == NULL)
		cx->addObject(new CCone(a,nx,parameters,parametersF,r,height,umax));
	else
		cx->addObject(new CCone(a,nx,parameters,parametersF,r,height,umax,nextData[0],nextData[1],nextData[2]));
}


///////////////////////////////////////////////////////////////////////
// Class				:	CCone
// Method				:	computeObjectBound
// Description			:	Compute the bounding box in the object space
// Return Value			:	-
// Comments				:
void			CCone::computeObjectBound(float *bmin,float *bmax,float r,float height,float umax) {

	r	=	absf(r);

	initv(bmin,-r,-r,min(height,0));
	initv(bmax,r,r,max(height,0));
}





























//////////////////////////////////////////// P A R A B O L O I D ///////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
// Class				:	CParaboloid
// Method				:	CParaboloid
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CParaboloid::CParaboloid(CAttributes *a,CXform *x,CParameter *c,unsigned int pf,float ra,float zmina,float zmaxa,float anglea) : CSurface(a,x)  {
	stats.gprimMemory	+=	sizeof(CParaboloid);
	stats.numGprims++;

	r				=	ra;
	zmin			=	zmina;
	zmax			=	zmaxa;
	umax			=	anglea;

	parameters		=	c;
	parametersF		=	PARAMETER_P | PARAMETER_NG | PARAMETER_DPDU | PARAMETER_DPDV | pf;

	nextData		=	NULL;

	computeObjectBound(bmin,bmax,r,zmin,zmax,umax);
	xform->transformBound(bmin,bmax);
	makeBound(bmin,bmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CParaboloid
// Method				:	CParaboloid
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CParaboloid::CParaboloid(CAttributes *a,CXform *x,CParameter *c,unsigned int pf,float r0,float zmin0,float zmax0,float angle0,float r1,float zmin1,float zmax1,float angle1) : CSurface(a,x) {
	vector	tbmin,tbmax;

	stats.gprimMemory	+=	sizeof(CParaboloid);
	stats.gprimMemory	+=	sizeof(float)*4;
	stats.numGprims++;

	r			=	r0;
	zmin		=	zmin0;
	zmax		=	zmax0;
	umax		=	angle0;


	parameters	=	c;
	parametersF	=	PARAMETER_P | PARAMETER_NG | PARAMETER_DPDU | PARAMETER_DPDV | pf;

	nextData	=	new float[4];
	nextData[0]	=	r1;
	nextData[1]	=	zmin1;
	nextData[2]	=	zmax1;
	nextData[3]	=	angle1;

	computeObjectBound(bmin,bmax,r,zmin,zmax,umax);
	computeObjectBound(tbmin,tbmax,nextData[0],nextData[1],nextData[2],nextData[3]);
	addBox(bmin,bmax,tbmin);
	addBox(bmin,bmax,tbmax);
	xform->transformBound(bmin,bmax);
	makeBound(bmin,bmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CParaboloid
// Method				:	~CParaboloid
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CParaboloid::~CParaboloid() {
	stats.gprimMemory	-=	sizeof(CParaboloid);
	stats.gprimMemory	-=	(nextData != NULL ? 4*sizeof(float) : 0);
	stats.numGprims--;

	if (parameters	!= NULL)	delete parameters;
	if (nextData	!= NULL)	delete [] nextData;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CParaboloid
// Method				:	intersect
// Description			:	Compute the intersection with a ray
// Return Value			:	TRUE if intersects
// Comments				:
void	CParaboloid::intersect(CShadingContext *context,CRay *rv) {
	vector	Nt;

	checkRay(rv);

	float	*from	=	oFrom;
	float	*dir	=	oDir;
	double	a,b,c,s[2];
	unsigned int		ns,i;
	float	zmi,zma;
	float	zmin,zmax;
	float	r,umax;

	if (nextData != NULL) {
		zmin	=	this->zmin * (1 - rv->time) + nextData[1] * rv->time;
		zmax	=	this->zmax * (1 - rv->time) + nextData[2] * rv->time;
		r		=	this->r * (1 - rv->time)	+ nextData[0] * rv->time;
		umax	=	this->umax * (1 - rv->time) + nextData[3] * rv->time;
	} else {
		zmin	=	this->zmin;
		zmax	=	this->zmax;
		r		=	this->r;
		umax	=	this->umax;
	}

	a		=	dir[COMP_X]*dir[COMP_X] + dir[COMP_Y]*dir[COMP_Y];
	b		=	2*dir[COMP_X]*from[COMP_X] + 2*dir[COMP_Y]*from[COMP_Y] - r*r*dir[COMP_Z]/zmax;
	c		=	from[COMP_X]*from[COMP_X] + from[COMP_Y]*from[COMP_Y] - r*r*from[COMP_Z]/zmax;

	if (a < C_EPSILON) {
		if (b == 0) return;
		s[0]	=	-c/b;
		ns		=	1;
	} else {
		if ((ns = solveQuadric<double>(a,b,c,s)) == 0) return;
	}

	if (zmin < zmax)	{
		zmi		=	zmin;
		zma		=	zmax;
	} else {
		zmi		=	zmax;
		zma		=	zmin;
	}

	for (i=0;i<ns;i++) {
		double	t	=	s[i];
		double	u;
		double	P[3];

		if (t <= rv->tmin)	continue;
		if (t >= rv->t)		return;

		P[0]	=	from[0] + dir[0]*t;
		P[1]	=	from[1] + dir[1]*t;
		P[2]	=	from[2] + dir[2]*t;

		if (P[COMP_Z] <	zmi)		continue;
		if (P[COMP_Z] > zma)		continue;

		if (r > 0)	u	=	atan2(P[COMP_Y],P[COMP_X]);
		else		u	=	atan2(-P[COMP_Y],-P[COMP_X]);

		if (u < 0) u	=	2*C_PI + u;

		if (umax < 0) {
			u	=	u - 2*C_PI;
			if (u < umax) continue;
		} else {
			if (u > umax) continue;
		}

		const float	tmp	=	umax*(zmax-zmin);
		Nt[COMP_X]	=	(float) (P[COMP_X]*tmp);
		Nt[COMP_Y]	=	(float) (P[COMP_Y]*tmp);
		Nt[COMP_Z]	=	(float) (-r*r*tmp / (2*zmax));

		if ((attributes->flags & ATTRIBUTES_FLAGS_INSIDE) ^ xform->flip) {
			mulvf(Nt,-1);
		}

		if (attributes->nSides == 1) {
			if (dotvv(oDir,Nt) > 0) continue;
		}

		rv->object	=	this;
		rv->u		=	(float) (u / umax);
		rv->v		=	(float) ((P[COMP_Z]	-	zmin) / (zmax - zmin));
		rv->t		=	(float) t;
		mulmn(rv->N,xform->to,Nt);
		return;
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CParaboloid
// Method				:	sample
// Description			:	See object.h
// Return Value			:	-
// Comments				:
void			CParaboloid::sample(int start,int numVertices,float **varying,float ***locals,unsigned int &up) const {
	float	*cosu;
	float	*sinu;
	float	*sqrtz;
	int		i;
	float	*u		=	&varying[VARIABLE_U][start];
	float	*v		=	&varying[VARIABLE_V][start];
	float	*dest;

	// Allocate memory for precomputing sin(u) , cos(u)
	sinu	=	(float *)	alloca(numVertices*sizeof(float));
	cosu	=	(float *)	alloca(numVertices*sizeof(float));
	sqrtz	=	(float *)	alloca(numVertices*sizeof(float));


	if ((nextData != NULL) && (!(up & (PARAMETER_BEGIN_SAMPLE | PARAMETER_END_SAMPLE)))) {
		float	*r		=	(float *)	alloca(numVertices*sizeof(float));
		float	*umax	=	(float *)	alloca(numVertices*sizeof(float));
		float	*zmax	=	(float *)	alloca(numVertices*sizeof(float));
		float	*zmin	=	(float *)	alloca(numVertices*sizeof(float));
		float	*time	=	&varying[VARIABLE_TIME][start];

		// Precompute the sin/cos for u points
		dest			=				varying[VARIABLE_P] + start*3;
		for (i=0;i<numVertices;i++) {
			r[i]			=	this->r * (1 - time[i])	   + nextData[0] * time[i];
			zmin[i]			=	this->zmin * (1 - time[i]) + nextData[1] * time[i];
			zmax[i]			=	this->zmax * (1 - time[i]) + nextData[2] * time[i];
			umax[i]			=	this->umax * (1 - time[i]) + nextData[3] * time[i];
			cosu[i]			=	cosf(u[i]*umax[i]);
			sinu[i]			=	sinf(u[i]*umax[i]);
			sqrtz[i]		=	sqrtf(((zmax[i]-zmin[i])*v[i]+zmin[i])/zmax[i]);
			
			dest[COMP_Z]	=	(zmax[i] - zmin[i])*v[i] + zmin[i];
			dest[COMP_X]	=	r[i]*sqrtz[i]*cosu[i];
			dest[COMP_Y]	=	r[i]*sqrtz[i]*sinu[i];
			dest			+=	3;
		}

		// Set Ng if needed
		if (up & PARAMETER_NG) {
			float	*Ng		=	&varying[VARIABLE_NG][start*3];
			float	*P		=	&varying[VARIABLE_P][start*3];

			for (i=0;i<numVertices;i++) {
				float	tmp2	=	umax[i]*(zmax[i]-zmin[i]);
				Ng[COMP_X]		=	P[COMP_X]*tmp2;
				Ng[COMP_Y]		=	P[COMP_Y]*tmp2;
				Ng[COMP_Z]		=	-r[i]*r[i]*tmp2 / (2*zmax[i]);
				Ng				+=	3;
				P				+=	3;
			}
		}

		// Set dPdu/dPdv if needed
		if (up & (PARAMETER_DPDU | PARAMETER_DPDU)) {
			float	*dPdu	=	&varying[VARIABLE_DPDU][start*3];
			float	*dPdv	=	&varying[VARIABLE_DPDV][start*3];

			for (i=0;i<numVertices;i++) {
				dPdu[COMP_X]	=	-umax[i]*sqrtz[i]*sinu[i];
				dPdu[COMP_Y]	=	umax[i]*sqrtz[i]*cosu[i];
				dPdu[COMP_Z]	=	0;
				dPdv[COMP_X]	=	r[i]*(zmax[i]-zmin[i])*cosu[i] / (2*zmax[i]*sqrtz[i]);
				dPdv[COMP_Y]	=	r[i]*(zmax[i]-zmin[i])*sinu[i] / (2*zmax[i]*sqrtz[i]);
				dPdv[COMP_Z]	=	zmax[i] - zmin[i];
				dPdu			+=	3;
				dPdv			+=	3;
			}
		}
	} else {
		float	r		=	this->r;
		float	zmin	=	this->zmin;
		float	zmax	=	this->zmax;
		float	umax	=	this->umax;

		if ((up & PARAMETER_END_SAMPLE) && (nextData != NULL)) {
			r			=	nextData[0];
			zmin		=	nextData[1];
			zmax		=	nextData[2];
			umax		=	nextData[3];
		}

		// Precompute the sin/cos for u points
		dest			=	varying[VARIABLE_P] + start*3;
		for (i=0;i<numVertices;i++) {
			cosu[i]			=	cosf(u[i]*umax);
			sinu[i]			=	sinf(u[i]*umax);
			sqrtz[i]		=	sqrtf(((zmax-zmin)*v[i]+zmin)/zmax);

			dest[COMP_Z]	=	(zmax - zmin)*v[i] + zmin;
			dest[COMP_X]	=	r*sqrtz[i]*cosu[i];
			dest[COMP_Y]	=	r*sqrtz[i]*sinu[i];
			dest			+=	3;
		}

		// Set Ng if needed
		if (up & PARAMETER_NG) {
			float	*Ng		=	&varying[VARIABLE_NG][start*3];
			float	*P		=	&varying[VARIABLE_P][start*3];
			float	tmp2	=	umax*(zmax-zmin);

			for (i=0;i<numVertices;i++) {
				Ng[COMP_X]	=	P[COMP_X]*tmp2;
				Ng[COMP_Y]	=	P[COMP_Y]*tmp2;
				Ng[COMP_Z]	=	-r*r*tmp2 / (2*zmax);
				Ng			+=	3;
				P			+=	3;
			}
		}

		// Set dPdu/dPdv if needed
		if (up & (PARAMETER_DPDU | PARAMETER_DPDU)) {
			float	*dPdu	=	&varying[VARIABLE_DPDU][start*3];
			float	*dPdv	=	&varying[VARIABLE_DPDV][start*3];

			for (i=0;i<numVertices;i++) {
				dPdu[COMP_X]	=	-umax*sqrtz[i]*sinu[i];
				dPdu[COMP_Y]	=	umax*sqrtz[i]*cosu[i];
				dPdu[COMP_Z]	=	0;
				dPdv[COMP_X]	=	r*(zmax-zmin)*cosu[i] / (2*zmax*sqrtz[i]);
				dPdv[COMP_Y]	=	r*(zmax-zmin)*sinu[i] / (2*zmax*sqrtz[i]);
				dPdv[COMP_Z]	=	zmax - zmin;
				dPdu			+=	3;
				dPdv			+=	3;
			}
		}
	}

	if (xform->flip == 1) {
		float	*N	=	varying[VARIABLE_NG] + start*3;

		for (int i=numVertices;i>0;i--,N+=3) {
			mulvf(N,-1);
		}
	}

	// Transform the points
	transformPoints();

	up	&=	~parametersF;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CParaboloid
// Method				:	interpolate
// Description			:	See object.h
// Return Value			:	-
// Comments				:
void			CParaboloid::interpolate(int numVertices,float **varying,float ***locals) const {
	if (parameters != NULL)	parameters->dispatch(numVertices,varying,locals);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CParaboloid
// Method				:	instantiate
// Description			:	See object.h
// Return Value			:	-
// Comments				:
void		CParaboloid::instantiate(CAttributes *a,CXform *x,CRendererContext *cx) const {
	CXform		*nx	=	new CXform(x);

	nx->concat(xform);	// Concetenate the local xform

	if (a == NULL)	a	=	attributes;

	if (nextData == NULL)
		cx->addObject(new CParaboloid(a,nx,parameters,parametersF,r,zmin,zmax,umax));
	else
		cx->addObject(new CParaboloid(a,nx,parameters,parametersF,r,zmin,zmax,umax,nextData[0],nextData[1],nextData[2],nextData[3]));
}

///////////////////////////////////////////////////////////////////////
// Class				:	CParaboloid
// Method				:	computeObjectBound
// Description			:	Compute the bounding box in the object space
// Return Value			:	-
// Comments				:
void			CParaboloid::computeObjectBound(float *bmin,float *bmax,float r,float zmin,float zmax,float umax) {
	r	=	absf(r);

	initv(bmin,-r,-r,min(zmin,zmax));
	initv(bmax,r,r,max(zmin,zmax));
}




















//////////////////////////////////////////// C Y L I N D E R  ///////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////
// Class				:	CCylinder
// Method				:	CCylinder
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CCylinder::CCylinder(CAttributes *a,CXform *x,CParameter *c,unsigned int pf,float ra,float zmina,float zmaxa,float anglea) : CSurface(a,x)  {
	stats.gprimMemory	+=	sizeof(CCylinder);
	stats.numGprims++;

	r			=	ra;
	zmin		=	zmina;
	zmax		=	zmaxa;
	umax		=	anglea;


	parameters	=	c;
	parametersF	=	PARAMETER_P | PARAMETER_NG | PARAMETER_DPDU | PARAMETER_DPDV | pf;

	nextData	=	NULL;

	computeObjectBound(bmin,bmax,r,zmin,zmax,umax);
	xform->transformBound(bmin,bmax);
	makeBound(bmin,bmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CCylinder
// Method				:	CCylinder
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CCylinder::CCylinder(CAttributes *a,CXform *x,CParameter *c,unsigned int pf,float r0,float zmin0,float zmax0,float angle0,float r1,float zmin1,float zmax1,float angle1) : CSurface(a,x) {
	vector	tbmin,tbmax;

	stats.gprimMemory	+=	sizeof(CCylinder);
	stats.gprimMemory	+=	sizeof(float)*4;
	stats.numGprims++;

	r			=	r0;
	zmin		=	zmin0;
	zmax		=	zmax0;
	umax		=	angle0;

	parameters	=	c;
	parametersF	=	PARAMETER_P | PARAMETER_NG | PARAMETER_DPDU | PARAMETER_DPDV | pf;

	nextData	=	new float[4];
	nextData[0]	=	r1;
	nextData[1]	=	zmin1;
	nextData[2]	=	zmax1;
	nextData[3]	=	angle1;

	computeObjectBound(bmin,bmax,r,zmin,zmax,umax);
	computeObjectBound(tbmin,tbmax,nextData[0],nextData[1],nextData[2],nextData[3]);
	addBox(bmin,bmax,tbmin);
	addBox(bmin,bmax,tbmax);
	xform->transformBound(bmin,bmax);
	makeBound(bmin,bmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CCylinder
// Method				:	~CCylinder
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CCylinder::~CCylinder() {
	stats.gprimMemory	-=	sizeof(CCylinder);
	stats.gprimMemory	-=	(nextData != NULL ? 4*sizeof(float) : 0);
	stats.numGprims--;

	if (parameters	!= NULL)	delete parameters;
	if (nextData	!= NULL)	delete [] nextData;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CCylinder
// Method				:	intersect
// Description			:	Compute the intersection with a ray
// Return Value			:	TRUE if intersects
// Comments				:
void	CCylinder::intersect(CShadingContext *context,CRay *rv) {
	vector	Nt;

	checkRay(rv);

	float	*from	=	oFrom;
	float	*dir	=	oDir;
	double	a,b,c,s[2];
	unsigned int		ns,i;
	float	r,zmin,zmax,umax;

	if (nextData != NULL) {
		zmin	=	this->zmin * (1 - rv->time) + nextData[1] * rv->time;
		zmax	=	this->zmax * (1 - rv->time) + nextData[2] * rv->time;
		r		=	this->r * (1 - rv->time) + nextData[0] * rv->time;
		umax	=	this->umax * (1 - rv->time) + nextData[3] * rv->time;
	} else {
		zmin	=	this->zmin;
		zmax	=	this->zmax;
		r		=	this->r;
		umax	=	this->umax;
	}

	a		=	dir[COMP_X]*dir[COMP_X] + dir[COMP_Y]*dir[COMP_Y];
	b		=	2*dir[COMP_X]*from[COMP_X] + 2*dir[COMP_Y]*from[COMP_Y];
	c		=	from[COMP_X]*from[COMP_X] + from[COMP_Y]*from[COMP_Y] - r*r;

	if (a == 0) {
		if (b == 0)	return;

		s[0]	=	-c/b;
		ns		=	1;
	} else {
		if ((ns = solveQuadric<double>(a,b,c,s)) == 0) return;
	}

	for (i=0;i<ns;i++) {
		float	t	=	(float) s[i];
		double	u;
		double	P[3];

		if (t	<=	rv->tmin)	continue;
		if (t	>=	rv->t)		return;

		P[0]	=	from[0] + dir[0]*t;
		P[1]	=	from[1] + dir[1]*t;
		P[2]	=	from[2] + dir[2]*t;
	
		if (zmin < zmax) {
			if (P[COMP_Z] < zmin)	continue;
			if (P[COMP_Z] > zmax)	continue;
		} else {
			if (P[COMP_Z] < zmax)	continue;
			if (P[COMP_Z] > zmin)	continue;
		}

		if (r > 0)		u				=	atan2(P[COMP_Y],P[COMP_X]);
		else			u				=	atan2(-P[COMP_Y],-P[COMP_X]);

		if (u < 0) u	=	2*C_PI + u;
		if (umax < 0) {
			u	=	u - 2*C_PI;
			if (u < umax) continue;
		} else {
			if (u > umax) continue;
		}

		Nt[COMP_X]	=	(float) (P[COMP_X]*umax*(zmax-zmin));
		Nt[COMP_Y]	=	(float) (P[COMP_Y]*umax*(zmax-zmin));
		Nt[COMP_Z]	=	0;

		if ((attributes->flags & ATTRIBUTES_FLAGS_INSIDE) ^ xform->flip) {
			mulvf(Nt,-1);
		}

		if (attributes->nSides == 1) {
			if (dotvv(oDir,Nt) > 0) continue;
		}

		rv->object	=	this;
		rv->u		=	(float) (u/umax);
		rv->v		=	(float) (P[COMP_Z] - zmin) / (zmax - zmin);
		rv->t		=	(float) t;
		mulmn(rv->N,xform->to,Nt);
		return;
	}

}


///////////////////////////////////////////////////////////////////////
// Class				:	CCylinder
// Method				:	sample
// Description			:	See object.h
// Return Value			:	-
// Comments				:
void			CCylinder::sample(int start,int numVertices,float **varying,float ***locals,unsigned int &up) const {
	float	*cosu;
	float	*sinu;
	int		i;
	float	*u		=	varying[VARIABLE_U];
	float	*v		=	varying[VARIABLE_V];
	float	*dest;

	// Allocate memory for precomputing sin(u) , cos(u)
	sinu	=	(float *)	alloca(numVertices*sizeof(float));
	cosu	=	(float *)	alloca(numVertices*sizeof(float));

	if ((nextData != NULL) && (!(up & (PARAMETER_BEGIN_SAMPLE | PARAMETER_END_SAMPLE)))) {
		float	*r		=	(float *)	alloca(numVertices*sizeof(float));
		float	*umax	=	(float *)	alloca(numVertices*sizeof(float));
		float	*zmax	=	(float *)	alloca(numVertices*sizeof(float));
		float	*zmin	=	(float *)	alloca(numVertices*sizeof(float));
		float	*time	=	&varying[VARIABLE_TIME][start];

		// Precompute the sin/cos for u points
		dest			=	varying[VARIABLE_P] + start*3;
		for (i=0;i<numVertices;i++) {
			r[i]		=	this->r * (1 - time[i])		+ nextData[0] * time[i];
			zmin[i]		=	this->zmin * (1 - time[i])  + nextData[1] * time[i];
			zmax[i]		=	this->zmax * (1 - time[i])  + nextData[2] * time[i];
			umax[i]		=	this->umax * (1 - time[i])  + nextData[3] * time[i];
			cosu[i]		=	(cosf(u[i]*umax[i]))*r[i];
			sinu[i]		=	(sinf(u[i]*umax[i]))*r[i];

			dest[COMP_X]	=	cosu[i];
			dest[COMP_Y]	=	sinu[i];
			dest[COMP_Z]	=	(zmax[i] - zmin[i])*v[i] + zmin[i];
			dest			+=	3;
		}

		// Set Ng if needed
		if (up & PARAMETER_NG) {
			float	*Ng		=	varying[VARIABLE_NG] + start*3;
			float	*P		=	varying[VARIABLE_P] + start*3;

			for (i=0;i<numVertices;i++) {
				const float	tmp2	=	umax[i]*(zmax[i]-zmin[i]);
				Ng[COMP_X]	=	P[COMP_X]*tmp2;
				Ng[COMP_Y]	=	P[COMP_Y]*tmp2;
				Ng[COMP_Z]	=	0;
				Ng			+=	3;
				P			+=	3;
			}
		}

		// Set dPdu/dPdv if needed
		if (up & (PARAMETER_DPDU | PARAMETER_DPDU)) {
			float	*dPdu	=	varying[VARIABLE_DPDU] + start*3;
			float	*dPdv	=	varying[VARIABLE_DPDV] + start*3;

			for (i=0;i<numVertices;i++) {
				dPdu[COMP_X]	=	-umax[i]*sinu[i];
				dPdu[COMP_Y]	=	umax[i]*cosu[i];
				dPdu[COMP_Z]	=	0;
				dPdv[COMP_X]	=	0;
				dPdv[COMP_Y]	=	0;
				dPdv[COMP_Z]	=	zmax[i] - zmin[i];
				dPdu			+=	3;
				dPdv			+=	3;
			}
		}
	} else {
		float	r		=	this->r;
		float	zmin	=	this->zmin;
		float	zmax	=	this->zmax;
		float	umax	=	this->umax;

		if ((up & PARAMETER_END_SAMPLE) && (nextData != NULL)) {
			r			=	nextData[0];
			zmin		=	nextData[1];
			zmax		=	nextData[2];
			umax		=	nextData[3];
		}

		// Precompute the sin/cos for u points
		for (i=0;i<numVertices;i++) {
			cosu[i]		=	(cosf(u[i]*umax))*r;
			sinu[i]		=	(sinf(u[i]*umax))*r;
		}

		// Set u/v/P
		for (i=0,dest=varying[VARIABLE_P] + start*3;i<numVertices;i++) {
			dest[COMP_X]	=	cosu[i];
			dest[COMP_Y]	=	sinu[i];
			dest[COMP_Z]	=	(zmax - zmin)*v[i] + zmin;
			dest			+=	3;
		}

		// Set Ng if needed
		if (up & PARAMETER_NG) {
			float		*Ng		=	varying[VARIABLE_NG] + start*3;
			float		*P		=	varying[VARIABLE_P] + start*3;
			const float	tmp2	=	umax*(zmax-zmin);

			for (i=0;i<numVertices;i++) {
				Ng[COMP_X]	=	P[COMP_X]*tmp2;
				Ng[COMP_Y]	=	P[COMP_Y]*tmp2;
				Ng[COMP_Z]	=	0;
				Ng			+=	3;
				P			+=	3;
			}
		}

		// Set dPdu/dPdv if needed
		if (up & (PARAMETER_DPDU | PARAMETER_DPDU)) {
			float	*dPdu	=	varying[VARIABLE_DPDU] + start*3;
			float	*dPdv	=	varying[VARIABLE_DPDV] + start*3;

			for (i=0;i<numVertices;i++) {
				dPdu[COMP_X]	=	-umax*sinu[i];
				dPdu[COMP_Y]	=	umax*cosu[i];
				dPdu[COMP_Z]	=	0;
				dPdv[COMP_X]	=	0;
				dPdv[COMP_Y]	=	0;
				dPdv[COMP_Z]	=	zmax - zmin;
				dPdu			+=	3;
				dPdv			+=	3;
			}
		}
	}

	if (xform->flip) {
		float	*N	=	varying[VARIABLE_NG] + start*3;

		for (int i=numVertices;i>0;i--,N+=3) {
			mulvf(N,-1);
		}
	}

	// Transform the points
	transformPoints();

	up	&=	~parametersF;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CCylinder
// Method				:	interpolate
// Description			:	See object.h
// Return Value			:	-
// Comments				:
void			CCylinder::interpolate(int numVertices,float **varying,float ***locals) const {
	if (parameters != NULL)	parameters->dispatch(numVertices,varying,locals);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CCylinder
// Method				:	instantiate
// Description			:	See object.h
// Return Value			:	-
// Comments				:
void	CCylinder::instantiate(CAttributes *a,CXform *x,CRendererContext *cx) const {
	CXform		*nx	=	new CXform(x);

	nx->concat(xform);	// Concetenate the local xform

	if (a == NULL)	a	=	attributes;

	if (nextData == NULL)
		cx->addObject(new CCylinder(a,nx,parameters,parametersF,r,zmin,zmax,umax));
	else
		cx->addObject(new CCylinder(a,nx,parameters,parametersF,r,zmin,zmax,umax,nextData[0],nextData[1],nextData[2],nextData[3]));
}

///////////////////////////////////////////////////////////////////////
// Class				:	CCylinder
// Method				:	computeObjectBound
// Description			:	Compute the bounding box in the object space
// Return Value			:	-
// Comments				:
void			CCylinder::computeObjectBound(float *bmin,float *bmax,float r,float zmin,float zmax,float umax) {
	r	=	absf(r);

	initv(bmin,-r,-r,min(zmin,zmax));
	initv(bmax,r,r,max(zmin,zmax));
}




















//////////////////////////////////////////// H Y P E R B O L O I D  ///////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
// Class				:	CHyperboloid
// Method				:	CHyperboloid
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CHyperboloid::CHyperboloid(CAttributes *a,CXform *x,CParameter *c,unsigned int pf,const float *p1a,const float *p2a,float anglea) : CSurface(a,x)  {
	stats.gprimMemory	+=	sizeof(CHyperboloid);
	stats.numGprims++;

	umax	=	anglea;
	movvv(p1,p1a);
	movvv(p2,p2a);


	parameters	=	c;
	parametersF	=	PARAMETER_P | PARAMETER_NG | PARAMETER_DPDU | PARAMETER_DPDV | pf;

	nextData	=	NULL;

	computeObjectBound(bmin,bmax,p1,p2,umax);
	xform->transformBound(bmin,bmax);
	makeBound(bmin,bmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CHyperboloid
// Method				:	CHyperboloid
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CHyperboloid::CHyperboloid(CAttributes *a,CXform *x,CParameter *c,unsigned int pf,const float *p10,const float *p20,float angle0,const float *p11,const float *p21,float angle1) : CSurface(a,x) {
	vector	tbmin,tbmax;

	stats.gprimMemory	+=	sizeof(CHyperboloid);
	stats.gprimMemory	+=	sizeof(float)*7;
	stats.numGprims++;

	umax	=	angle0;
	movvv(p1,p10);
	movvv(p2,p20);


	parameters	=	c;
	parametersF	=	PARAMETER_P | PARAMETER_NG | PARAMETER_DPDU | PARAMETER_DPDV | pf;

	nextData	=	new float[7];
	movvv(&nextData[0],p11);
	movvv(&nextData[3],p21);
	nextData[6]	=	angle1;

	computeObjectBound(bmin,bmax,p1,p2,umax);
	computeObjectBound(tbmin,tbmax,&nextData[0],&nextData[3],nextData[6]);
	addBox(bmin,bmax,tbmin);
	addBox(bmin,bmax,tbmax);
	xform->transformBound(bmin,bmax);
	makeBound(bmin,bmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CHyperboloid
// Method				:	~CHyperboloid
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CHyperboloid::~CHyperboloid() {
	stats.gprimMemory	-=	sizeof(CHyperboloid);
	stats.gprimMemory	-=	(nextData != NULL ? 7*sizeof(float) : 0);
	stats.numGprims--;

	if (parameters	!= NULL)	delete parameters;
	if (nextData	!= NULL)	delete [] nextData;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CHyperboloid
// Method				:	intersect
// Description			:	Compute the intersection with a ray
// Return Value			:	TRUE if intersects
// Comments				:
void	CHyperboloid::intersect(CShadingContext *context,CRay *rv) {

	checkRay(rv);

	float	*from	=	oFrom;
	float	*dir	=	oDir;
	unsigned int		ns,i;
	double	ts[2];
	double	P[3];
	double	a,b,c;
	vector	p1,p2;
	float	umax;
	vector	Nt;

	if (nextData != NULL) {
		interpolatev(p1,this->p1,&nextData[0],rv->time);
		interpolatev(p2,this->p2,&nextData[3],rv->time);
		umax	=	this->umax * (1 - rv->time) + nextData[6] * rv->time;
	} else {
		movvv(p1,this->p1);
		movvv(p2,this->p2);
		umax	=	this->umax;
	}

	const double	dx		=	p2[COMP_X] - p1[COMP_X];
	const double	dy		=	p2[COMP_Y] - p1[COMP_Y];
	const double	dz		=	p2[COMP_Z] - p1[COMP_Z];

	if (p1[COMP_Z] == p2[COMP_Z]) {
		// We're a disc
		ns			=	1;
		ts[0]		=	(p1[COMP_Z] - from[COMP_Z]) / dir[COMP_Z];
	} else {
		double	x;
		double	y;
		double	zmin,d,dmin;

		if ((dx*dx + dy*dy) < C_EPSILON) {	// Make sure we don't crash if we're a cylinder
			x		=	p1[COMP_X];
			y		=	p1[COMP_Y];
			zmin	=	p1[COMP_Z];
		} else {
			double	tmin	=	(-dx*p1[COMP_X] - dy*p1[COMP_Y]) / (dx*dx + dy*dy);	// Nearest we come to the  z axis
			x		=	p1[COMP_X]	+	dx*tmin;
			y		=	p1[COMP_Y]	+	dy*tmin;
			zmin	=	p1[COMP_Z]	+	dz*tmin;
		}

		dmin		=	sqrt(x*x + y*y);

		if (fabs(p2[COMP_Z]-zmin) > fabs(p1[COMP_Z]-zmin)) {
			d				=	sqrt((p2[COMP_X]*p2[COMP_X] + p2[COMP_Y]*p2[COMP_Y]) - dmin*dmin)/(p2[COMP_Z]-zmin);
		} else {
			d				=	sqrt((p1[COMP_X]*p1[COMP_X] + p1[COMP_Y]*p1[COMP_Y]) - dmin*dmin)/(p1[COMP_Z]-zmin);
		}

		a		=	dir[COMP_X]*dir[COMP_X] + dir[COMP_Y]*dir[COMP_Y] - dir[COMP_Z]*dir[COMP_Z]*d*d;
		b		=	2*dir[COMP_X]*from[COMP_X] + 2*dir[COMP_Y]*from[COMP_Y] - 2*dir[COMP_Z]*(from[COMP_Z]-zmin)*d*d;
		c		=	from[COMP_X]*from[COMP_X] + from[COMP_Y]*from[COMP_Y] - dmin*dmin - (from[COMP_Z]-zmin)*(from[COMP_Z]-zmin)*d*d;

		if (a == 0) {
			if (b == 0)	return;

			ns		=	1;
			ts[0]	=	-c / b;
		} else {
			if ((ns	=	solveQuadric<double>(a,b,c,ts)) == 0) return;
		}
	}

	for (i = 0;i < ns;i++) {
		double	t	=	ts[i];
		double	x,y;
		double	ustart;
		double	u,v;

		if (t >= rv->t)		return;
		if (t <= rv->tmin)	continue;

		P[0]	=	from[0] + dir[0]*t;
		P[1]	=	from[1] + dir[1]*t;
		P[2]	=	from[2] + dir[2]*t;

		if (p1[COMP_Z] < p2[COMP_Z]) {
			if (P[COMP_Z] < p1[COMP_Z])	continue;
			if (P[COMP_Z] > p2[COMP_Z])	continue;
			v			=	(P[COMP_Z] - p1[COMP_Z]) / (p2[COMP_Z] - p1[COMP_Z]);
		} else if (p1[COMP_Z] > p2[COMP_Z]) {
			if (P[COMP_Z] < p2[COMP_Z])	continue;
			if (P[COMP_Z] > p1[COMP_Z])	continue;
			v			=	(P[COMP_Z] - p1[COMP_Z]) / (p2[COMP_Z] - p1[COMP_Z]);
		} else {
			const double	r1	=	sqrt(p1[COMP_X]*p1[COMP_X] + p1[COMP_Y]*p1[COMP_Y]);
			const double	r2	=	sqrt(p2[COMP_X]*p2[COMP_X] + p2[COMP_Y]*p2[COMP_Y]);
			const double	r	=	sqrt(P[COMP_X]*P[COMP_X] + P[COMP_Y]*P[COMP_Y]);

			// We're a disc
			v					=	(r - r1) / (r2 - r1);
			if (v < 0)	continue;

			if (v > 1)	continue;
		}
		
		x			=	p1[COMP_X]*(1-v) + p2[COMP_X]*v;
		y			=	p1[COMP_Y]*(1-v) + p2[COMP_Y]*v;

		u			=	atan2(P[COMP_Y],P[COMP_X]);
		ustart		=	atan2(y,x);

		if (u < 0) u			=	2*C_PI + u;
		if (ustart < 0) ustart	=	2*C_PI + ustart;

		u						-=	ustart;
		if (u < 0)	u			=	2*C_PI + u;
		if (umax < 0) {
			u	=	u - 2*C_PI;
			if (u < umax) continue;
		} else {
			if (u > umax) continue;
		}

		{
			Nt[COMP_X]	=	(float) ((p2[COMP_Z] - p1[COMP_Z])*umax*P[COMP_X]);
			Nt[COMP_Y]	=	(float) ((p2[COMP_Z] - p1[COMP_Z])*umax*P[COMP_Y]);
			Nt[COMP_Z]	=	(float) (-umax*(		(-1+v)*p1[COMP_X]*p1[COMP_X]	+
										p1[COMP_X]*(p2[COMP_X] - 2*v*p2[COMP_X]) +
										v*(p2[COMP_X]*p2[COMP_X] + (p2[COMP_Y]-p1[COMP_Y])*(p2[COMP_Y]-p1[COMP_Y])) +
										p1[COMP_Y]*(p2[COMP_Y] - p1[COMP_Y])));

			if ((attributes->flags & ATTRIBUTES_FLAGS_INSIDE) ^ xform->flip) {
				mulvf(Nt,-1);
			}

			if (attributes->nSides == 1) {
				if (dotvv(oDir,Nt) > 0) continue;
			}
		}

		rv->object	=	this;
		rv->u		=	(float) (u / umax);
		rv->v		=	(float) (v);
		rv->t		=	(float) t;
		mulmn(rv->N,xform->to,Nt);

		return;
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CHyperboloid
// Method				:	sample
// Description			:	See object.h
// Return Value			:	-
// Comments				:
void			CHyperboloid::sample(int start,int numVertices,float **varying,float ***locals,unsigned int &up) const {
	float	*cosu;
	float	*sinu;
	int		i;
	float	*u		=	&varying[VARIABLE_U][start];
	float	*v		=	&varying[VARIABLE_V][start];
	float	*dest;

	sinu	=	(float *)	alloca(numVertices*sizeof(float));
	cosu	=	(float *)	alloca(numVertices*sizeof(float));

	if ((nextData != NULL) && (!(up & (PARAMETER_BEGIN_SAMPLE | PARAMETER_END_SAMPLE)))) {
		float	*umax	=	(float *)	alloca(numVertices*sizeof(float));
		float	*p1		=	(float *)	alloca(numVertices*sizeof(float)*3);
		float	*p2		=	(float *)	alloca(numVertices*sizeof(float)*3);
		float	*dx		=	(float *)	alloca(numVertices*sizeof(float));
		float	*dy		=	(float *)	alloca(numVertices*sizeof(float));
		float	*dz		=	(float *)	alloca(numVertices*sizeof(float));
		const	float	*tp1	=	this->p1;
		float	*np1	=	&nextData[0];
		const	float	*tp2	=	this->p2;
		float	*np2	=	&nextData[3];
		float	*cp1	=	p1;
		float	*cp2	=	p2;
		float	*time	=	&varying[VARIABLE_TIME][start];

		// Precompute the sin/cos for u points
		for (i=0;i<numVertices;i++) {
			umax[i]		=	this->umax * (1 - time[i]) + nextData[6] * time[i];
			cp1[COMP_X]	=	tp1[COMP_X] * (1 - time[i]) + np1[COMP_X] * time[i];
			cp1[COMP_Y]	=	tp1[COMP_Y] * (1 - time[i]) + np1[COMP_Y] * time[i];
			cp1[COMP_Z]	=	tp1[COMP_Z] * (1 - time[i]) + np1[COMP_Z] * time[i];
			cp2[COMP_X]	=	tp2[COMP_X] * (1 - time[i]) + np2[COMP_X] * time[i];
			cp2[COMP_Y]	=	tp2[COMP_Y] * (1 - time[i]) + np2[COMP_Y] * time[i];
			cp2[COMP_Z]	=	tp2[COMP_Z] * (1 - time[i]) + np2[COMP_Z] * time[i];
			dx[i]		=	cp2[COMP_X]	-	cp1[COMP_X];
			dy[i]		=	cp2[COMP_Y]	-	cp1[COMP_Y];
			dz[i]		=	cp2[COMP_Z]	-	cp1[COMP_Z];
			cosu[i]		=	cosf(u[i]*umax[i]);
			sinu[i]		=	sinf(u[i]*umax[i]);
			cp1			+=	3;
			cp2			+=	3;
		}

		// Set u/v/P
		cp1	=	p1;
		cp2	=	p2;
		for (i=0,dest=&varying[VARIABLE_P][start*3];i<numVertices;i++) {
			const float x	=	cp1[COMP_X] + dx[i]*v[i];
			const float y	=	cp1[COMP_Y] + dy[i]*v[i];
			const float z	=	cp1[COMP_Z] + dz[i]*v[i];

			dest[COMP_X]	=	(x*cosu[i] - y*sinu[i]);
			dest[COMP_Y]	=	(x*sinu[i] + y*cosu[i]);
			dest[COMP_Z]	=	z;
			dest			+=	3;
			cp1				+=	3;
			cp2				+=	3;
		}

		// Set dPdu/dPdv/Ng if needed
		if (up & (PARAMETER_DPDU | PARAMETER_DPDU | PARAMETER_NG)) {
			float	*dPdu	=	&varying[VARIABLE_DPDU][start*3];
			float	*dPdv	=	&varying[VARIABLE_DPDV][start*3];
			float	*Ng		=	&varying[VARIABLE_NG][start*3];

			cp1	=	p1;
			cp2	=	p2;
			for (i=0;i<numVertices;i++) {

				const float x	=	cp1[COMP_X] + dx[i]*v[i];
				const float y	=	cp1[COMP_Y] + dy[i]*v[i];
				const float z	=	cp1[COMP_Z] + dz[i]*v[i];

				dPdu[COMP_X]	=	-x*umax[i]*sinu[i] - y*umax[i]*cosu[i];
				dPdu[COMP_Y]	=	x*umax[i]*cosu[i] - y*umax[i]*sinu[i];
				dPdu[COMP_Z]	=	0;

				dPdv[COMP_X]	=	dx[i]*cosu[i] - dy[i]*sinu[i];
				dPdv[COMP_Y]	=	dx[i]*sinu[i] + dy[i]*cosu[i];
				dPdv[COMP_Z]	=	dz[i];

				crossvv(Ng,dPdu,dPdv);

				dPdu			+=	3;
				dPdv			+=	3;
				Ng				+=	3;
			}
		}
	} else {
		const	float	*p1		=	this->p1;
		const	float	*p2		=	this->p2;
		float	umax	=	this->umax;

		if ((up & PARAMETER_END_SAMPLE) && (nextData != NULL)) {
			p1			=	&nextData[0];
			p2			=	&nextData[3];
			umax		=	nextData[6];
		}

		const float	dx		=	p2[COMP_X] - p1[COMP_X];
		const float	dy		=	p2[COMP_Y] - p1[COMP_Y];
		const float	dz		=	p2[COMP_Z] - p1[COMP_Z];

		// Precompute the sin/cos for u points
		for (i=0;i<numVertices;i++) {
			cosu[i]	=	cosf(u[i]*umax);
			sinu[i]	=	sinf(u[i]*umax);
		}

		// Set u/v/P
		for (i=0,dest=&varying[VARIABLE_P][start*3];i<numVertices;i++) {
			const float x	=	p1[COMP_X] + dx*v[i];
			const float y	=	p1[COMP_Y] + dy*v[i];
			const float z	=	p1[COMP_Z] + dz*v[i];

			dest[COMP_X]	=	(x*cosu[i] - y*sinu[i]);
			dest[COMP_Y]	=	(x*sinu[i] + y*cosu[i]);
			dest[COMP_Z]	=	z;
			dest			+=	3;
		}

		// Set dPdu/dPdv/Ng if needed
		if (up & (PARAMETER_DPDU | PARAMETER_DPDU | PARAMETER_NG)) {
			float	*dPdu	=	&varying[VARIABLE_DPDU][start*3];
			float	*dPdv	=	&varying[VARIABLE_DPDV][start*3];
			float	*Ng		=	&varying[VARIABLE_NG][start*3];

			for (i=0;i<numVertices;i++) {
				const float x	=	p1[COMP_X] + dx*v[i];
				const float y	=	p1[COMP_Y] + dy*v[i];
				const float z	=	p1[COMP_Z] + dz*v[i];

				dPdu[COMP_X]	=	-x*umax*sinu[i] - y*umax*cosu[i];
				dPdu[COMP_Y]	=	x*umax*cosu[i] - y*umax*sinu[i];
				dPdu[COMP_Z]	=	0;

				dPdv[COMP_X]	=	dx*cosu[i] - dy*sinu[i];
				dPdv[COMP_Y]	=	dx*sinu[i] + dy*cosu[i];
				dPdv[COMP_Z]	=	dz;

				crossvv(Ng,dPdu,dPdv);

				dPdu			+=	3;
				dPdv			+=	3;
				Ng				+=	3;
			}
		}
	}

	if (xform->flip == 1) {
		float	*N	=	varying[VARIABLE_NG] + start*3;

		for (int i = numVertices;i>0;i--,N+=3) {
			mulvf(N,-1);
		}
	}

	// Transform the points
	transformPoints();

	up	&=	~parametersF;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CHyperboloid
// Method				:	interpolate
// Description			:	See object.h
// Return Value			:	-
// Comments				:
void			CHyperboloid::interpolate(int numVertices,float **varying,float ***locals) const {
	if (parameters != NULL)	parameters->dispatch(numVertices,varying,locals);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CHyperboloid
// Method				:	instantiate
// Description			:	See object.h
// Return Value			:	-
// Comments				:
void			CHyperboloid::instantiate(CAttributes *a,CXform *x,CRendererContext *cx) const {
	CXform		*nx	=	new CXform(x);

	nx->concat(xform);	// Concetenate the local xform

	if (a == NULL)	a	=	attributes;

	if (nextData == NULL)
		cx->addObject(new CHyperboloid(a,nx,parameters,parametersF,p1,p2,umax));
	else
		cx->addObject(new CHyperboloid(a,nx,parameters,parametersF,p1,p2,umax,nextData,nextData+3,nextData[6]));
}

///////////////////////////////////////////////////////////////////////
// Class				:	CHyperboloid
// Method				:	computeObjectBound
// Description			:	Compute the bounding box in the object space
// Return Value			:	-
// Comments				:
void			CHyperboloid::computeObjectBound(float *bmin,float *bmax,float *p1,float *p2,float umax) {
	float	d	=	p1[COMP_X] * p1[COMP_X] + p1[COMP_Y] * p1[COMP_Y];
	float	d2	=	p2[COMP_X] * p2[COMP_X] + p2[COMP_Y] * p2[COMP_Y];

	if (d2 > d)	d	=	d2;

	d				=	sqrtf(d);

	// FIXME: smaller bound is possible
	bmin[COMP_X]	=	-d;
	bmin[COMP_Y]	=	-d;
	bmin[COMP_Z]	=	min(p1[COMP_Z],p2[COMP_Z]);
	bmax[COMP_X]	=	+d;
	bmax[COMP_Y]	=	+d;
	bmax[COMP_Z]	=	max(p1[COMP_Z],p2[COMP_Z]);
}




















//////////////////////////////////////////// T O R O I D  ///////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
// Class				:	CToroid
// Method				:	CToroid
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CToroid::CToroid(CAttributes *a,CXform *x,CParameter *c,unsigned int pf,float rmina,float rmaxa,float vmina,float vmaxa,float umaxa) : CSurface(a,x)  {
	stats.gprimMemory	+=	sizeof(CToroid);
	stats.numGprims++;

	rmin		=	rmina;
	rmax		=	rmaxa;
	vmin		=	vmina;
	vmax		=	vmaxa;
	umax		=	umaxa;

	parameters	=	c;
	parametersF	=	PARAMETER_P | PARAMETER_NG | PARAMETER_DPDU | PARAMETER_DPDV | pf;

	nextData	=	NULL;

	computeObjectBound(bmin,bmax,rmin,rmax,vmin,vmax,umax);
	xform->transformBound(bmin,bmax);
	makeBound(bmin,bmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CToroid
// Method				:	CToroid
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CToroid::CToroid(CAttributes *a,CXform *x,CParameter *c,unsigned int pf,float rmin0,float rmax0,float vmin0,float vmax0,float umax0,float rmin1,float rmax1,float vmin1,float vmax1,float umax1) : CSurface(a,x) {
	vector	tbmin,tbmax;

	stats.gprimMemory	+=	sizeof(CToroid);
	stats.gprimMemory	+=	sizeof(float)*5;
	stats.numGprims++;

	rmin		=	rmin0;
	rmax		=	rmax0;
	vmin		=	vmin0;
	vmax		=	vmax0;
	umax		=	umax0;


	parameters	=	c;
	parametersF	=	PARAMETER_P | PARAMETER_NG | PARAMETER_DPDU | PARAMETER_DPDV | pf;

	nextData	=	new float[5];
	nextData[0]	=	rmin1;
	nextData[1]	=	rmax1;
	nextData[2]	=	vmin1;
	nextData[3]	=	vmax1;
	nextData[4]	=	umax1;

	computeObjectBound(bmin,bmax,rmin,rmax,vmin,vmax,umax);
	computeObjectBound(tbmin,tbmax,nextData[0],nextData[1],nextData[2],nextData[3],nextData[4]);
	addBox(bmin,bmax,tbmin);
	addBox(bmin,bmax,tbmax);
	xform->transformBound(bmin,bmax);
	makeBound(bmin,bmax);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CToroid
// Method				:	~CToroid
// Description			:	Dtor
// Return Value			:	-
// Comments				:
CToroid::~CToroid() {
	stats.gprimMemory	-=	sizeof(CToroid);
	stats.gprimMemory	-=	(nextData != NULL ? 5*sizeof(float) : 0);
	stats.numGprims--;

	if (parameters	!= NULL)	delete parameters;
	if (nextData	!= NULL)	delete [] nextData;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CToroid
// Method				:	intersect
// Description			:	Compute the intersection with a ray
// Return Value			:	TRUE if intersects
// Comments				:
void	CToroid::intersect(CShadingContext *context,CRay *rv) {

	checkRay(rv);

	double	rmin,rmax,umax,vmin,vmax;


	if (nextData != NULL) {
		rmin	=	this->rmin * (1 - rv->time) + nextData[0] * rv->time;
		rmax	=	this->rmax * (1 - rv->time) + nextData[1] * rv->time;
		umax	=	this->umax * (1 - rv->time) + nextData[2] * rv->time;
		vmax	=	this->vmax * (1 - rv->time) + nextData[3] * rv->time;
		vmin	=	this->vmin * (1 - rv->time) + nextData[4] * rv->time;
	} else {
		rmin	=	this->rmin;
		rmax	=	this->rmax;
		umax	=	this->umax;
		vmax	=	this->vmax;
		vmin	=	this->vmin;
	}

	{
		int			ns;
		double		s[5];
		double		c[5];
		int			i;
		const float	*from	=	oFrom;
		const float	*dir	=	oDir;

		double		R2		=	rmax*rmax;
		double		r2		=	rmin*rmin;
		double		Py2		=	from[COMP_Y] * from[COMP_Y];
		double		Dy2		=	dir[COMP_Y] * dir[COMP_Y];
		double		PDy2	=	from[COMP_Y] * dir[COMP_Y];
		double		k1		=	from[COMP_X] * from[COMP_X] + from[COMP_Z] * from[COMP_Z] + Py2 - R2 - r2;
		double		k2		=	from[COMP_X] * dir[COMP_X] + from[COMP_Z] * dir[COMP_Z] + PDy2;
		c[4]				=	1.0;
		c[3]				=	4.0 * k2;
		c[2]				=	2.0 * (k1 + 2.0 * (k2 * k2 + R2 * Dy2));
		c[1]				=	4.0 * (k2 * k1 + 2.0 * R2 * PDy2);
		c[0]				=	k1 * k1 + 4.0 * R2 * (Py2 - r2);

		/*
		double		ab	=	dotvv(from,dir);
		double		aa	=	dotvv(from,from);
		double		K	=	aa - rmin*rmin - rmax*rmax;

		c[4]	=	1;
		c[3]	=	4*ab;
		c[2]	=	2*(2*ab*ab + K + 2*rmax*rmax*dir[COMP_Z]*dir[COMP_Z]);
		c[1]	=	4*(K*ab + 2*rmax*rmax*from[COMP_Z]*dir[COMP_Z]);
		c[0]	=	K*K + 4*rmax*rmax*(from[COMP_Z]*from[COMP_Z] - rmin*rmin);
		*/

		// Solve the polynomial
		ns		=	solveQuartic<double>(c,s);

		for (i=0;i<ns;i++) {
			float	t;
			double	P[3];
			int		j,k;
			double	u,v,r;
			vector	Nt;
		
			// Extract the minimum intersection (the intersections are not sorted)
			t	=	C_INFINITY;
			for (j=0;j<ns;j++) {
				if (s[j] < t)	{
					t	=	(float) s[j];
					k	=	j;
				}
			}
			s[k]	=	C_INFINITY;

			v	=	c[4]*t*t*t*t + c[3]*t*t*t + c[2]*t*t + c[1]*t + c[0];
			assert(v*v < C_EPSILON);


			//if (t <= rv->tmin)	continue;
			//if (t >= rv->t)		return;

			P[0]	=	from[0] + dir[0]*t;
			P[1]	=	from[1] + dir[1]*t;
			P[2]	=	from[2] + dir[2]*t;

			if (rmax > 0)	u		=	atan2(P[COMP_Y],P[COMP_X]);
			else			u		=	atan2(-P[COMP_Y],-P[COMP_X]);
			if (u < 0)		u		=	2*C_PI + u;

			if (umax < 0) {
				u					=	u - 2*C_PI;
				//if (u < umax) continue;
			} else {
				//if (u > umax) continue;
			}



			r						=	sqrt(P[COMP_X]*P[COMP_X] + P[COMP_Y]*P[COMP_Y]) - fabs(rmax);

			if (rmin > 0)	v		=	atan2(P[COMP_Z],r);
			else			v		=	atan2(-P[COMP_Z],-r);
			if (v < 0)		v		=	2*C_PI + v;

			if (vmin < vmax) {
				//if (v < vmin)	continue;
				//if (v > vmax)	continue;
			} else {
				//if (v < vmax)	continue;
				//if (v > vmin)	continue;
			}

			// compute the normal vector
			Nt[COMP_X]				=	(float) (rmin*umax*(vmax-vmin)*cos(u)*cos(v)*(rmax + rmin*cos(v)));
			Nt[COMP_Y]				=	(float) (rmin*umax*(vmax-vmin)*cos(v)*(rmax + rmin*cos(v))*sin(u));
			Nt[COMP_Z]				=	(float) (rmin*umax*(vmax-vmin)*(rmax + rmin*cos(v))*sin(v));

			if ((attributes->flags & ATTRIBUTES_FLAGS_INSIDE) ^ xform->flip) {
				mulvf(Nt,-1);
			}

			if (attributes->nSides == 1) {
				//if (dotvv(oDir,Nt) > 0) continue;
			}

			u						=	u / umax;
			v						=	(v - vmin) / (vmax - vmin);

			rv->object				=	this;
			rv->u					=	(float) u;
			rv->v					=	(float) v;
			rv->t					=	(float) t;
			mulmn(rv->N,xform->to,Nt);


			return;
		}
	}

}

///////////////////////////////////////////////////////////////////////
// Class				:	CToroid
// Method				:	sample
// Description			:	See object.h
// Return Value			:	-
// Comments				:
void			CToroid::sample(int start,int numVertices,float **varying,float ***locals,unsigned int &up) const {
	float	*cosu;
	float	*sinu;
	float	*sinv;
	float	*cosv;
	int		i;
	float	*u		=	&varying[VARIABLE_U][start];
	float	*v		=	&varying[VARIABLE_V][start];
	float	*dest;

	sinu	=	(float *)	alloca(numVertices*sizeof(float));
	cosu	=	(float *)	alloca(numVertices*sizeof(float));
	sinv	=	(float *)	alloca(numVertices*sizeof(float));
	cosv	=	(float *)	alloca(numVertices*sizeof(float));


	if ((nextData != NULL) && (!(up & (PARAMETER_BEGIN_SAMPLE | PARAMETER_END_SAMPLE)))) {
		float	*rmin	=	(float *)	alloca(numVertices*sizeof(float));
		float	*rmax	=	(float *)	alloca(numVertices*sizeof(float));
		float	*vmin	=	(float *)	alloca(numVertices*sizeof(float));
		float	*vmax	=	(float *)	alloca(numVertices*sizeof(float));
		float	*umax	=	(float *)	alloca(numVertices*sizeof(float));
		float	*time	=	&varying[VARIABLE_TIME][start];

		// Precompute the sin/cos for u points
		for (i=0;i<numVertices;i++) {
			rmin[i]	=	this->rmin * (1 - time[i]) + nextData[0] * time[i];
			rmax[i]	=	this->rmax * (1 - time[i]) + nextData[1] * time[i];
			vmin[i]	=	this->vmin * (1 - time[i]) + nextData[2] * time[i];
			vmax[i]	=	this->vmax * (1 - time[i]) + nextData[3] * time[i];
			umax[i]	=	this->umax * (1 - time[i]) + nextData[4] * time[i];

			cosu[i]	=	cosf(u[i]*umax[i]);
			sinu[i]	=	sinf(u[i]*umax[i]);
			cosv[i]	=	cosf(v[i]*(vmax[i]-vmin[i]) + vmin[i]);
			sinv[i]	=	sinf(v[i]*(vmax[i]-vmin[i]) + vmin[i]);
		}

		// Set u/v/P
		for (i=0,dest=&varying[VARIABLE_P][start*3];i<numVertices;i++) {
			float	r		=	rmin[i]*cosv[i];
			dest[COMP_Z]	=	rmin[i]*sinv[i];
			dest[COMP_X]	=	(rmax[i]+r)*cosu[i];
			dest[COMP_Y]	=	(rmax[i]+r)*sinu[i];

			dest			+=	3;
		}

		// Set Ng if needed
		if (up & (PARAMETER_NG | PARAMETER_DPDU | PARAMETER_DPDV)) {
			float	*Ng		=	&varying[VARIABLE_NG][start*3];
			float	*dPdu	=	&varying[VARIABLE_DPDU][start*3];
			float	*dPdv	=	&varying[VARIABLE_DPDV][start*3];

			for (i=0;i<numVertices;i++) {
				float		r	=	rmin[i]*cosv[i];
				dPdu[COMP_Z]	=	0;
				dPdu[COMP_X]	=	-(rmax[i]+r)*sinu[i]*umax[i];
				dPdu[COMP_Y]	=	(rmax[i]+r)*cosu[i]*umax[i];
				dPdv[COMP_Z]	=	rmin[i]*cosv[i]*(vmax[i] - vmin[i]);
				dPdv[COMP_X]	=	(-rmin[i]*sinv[i]*(vmax[i] - vmin[i]))*cosu[i];
				dPdv[COMP_Y]	=	(-rmin[i]*sinv[i]*(vmax[i] - vmin[i]))*sinu[i];
				crossvv(Ng,dPdu,dPdv);
				Ng				+=	3;
				dPdu			+=	3;
				dPdv			+=	3;
			}
		}
	} else {
		float	rmin	=	this->rmin;
		float	rmax	=	this->rmax;
		float	vmin	=	this->vmin;
		float	vmax	=	this->vmax;
		float	umax	=	this->umax;

		if ((up & PARAMETER_END_SAMPLE) && (nextData != NULL)) {
			rmin		=	nextData[0];
			rmax		=	nextData[1];
			vmin		=	nextData[2];
			vmax		=	nextData[3];
			umax		=	nextData[4];
		}

		// Precompute the sin/cos for u points
		for (i=0;i<numVertices;i++) {
			cosu[i]	=	cosf(u[i]*umax);
			sinu[i]	=	sinf(u[i]*umax);
			cosv[i]	=	cosf(v[i]*(vmax-vmin) + vmin);
			sinv[i]	=	sinf(v[i]*(vmax-vmin) + vmin);
		}

		// Set u/v/P
		for (i=0,dest=&varying[VARIABLE_P][start*3];i<numVertices;i++) {
			float	r		=	rmin*cosv[i];
			dest[COMP_Z]	=	rmin*sinv[i];
			dest[COMP_X]	=	(rmax+r)*cosu[i];
			dest[COMP_Y]	=	(rmax+r)*sinu[i];

			dest			+=	3;
		}

		// Set Ng if needed
		if (up & (PARAMETER_NG | PARAMETER_DPDU | PARAMETER_DPDV)) {
			float	*Ng		=	&varying[VARIABLE_NG][start*3];
			float	*dPdu	=	&varying[VARIABLE_DPDU][start*3];
			float	*dPdv	=	&varying[VARIABLE_DPDV][start*3];

			for (i=0;i<numVertices;i++) {
				float		r	=	rmin*cosv[i];
				dPdu[COMP_Z]	=	0;
				dPdu[COMP_X]	=	-(rmax+r)*sinu[i]*umax;
				dPdu[COMP_Y]	=	(rmax+r)*cosu[i]*umax;
				dPdv[COMP_Z]	=	rmin*cosv[i]*(vmax - vmin);
				dPdv[COMP_X]	=	(-rmin*sinv[i]*(vmax - vmin))*cosu[i];
				dPdv[COMP_Y]	=	(-rmin*sinv[i]*(vmax - vmin))*sinu[i];
				crossvv(Ng,dPdu,dPdv);

				Ng				+=	3;
				dPdu			+=	3;
				dPdv			+=	3;
			}
		}
	}

	if (xform->flip == 1) {
		float	*N	=	varying[VARIABLE_NG] + start*3;

		for (int i=numVertices;i>0;i--,N+=3) {
			mulvf(N,-1);
		}
	}

	// Transform the points
	transformPoints();

	// Note that the normals are computed by dPdu x dPdv, meaning that the normal vector may be degenerate
	normalFix();

	up	&=	~parametersF;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CToroid
// Method				:	interpolate
// Description			:	See object.h
// Return Value			:	-
// Comments				:
void			CToroid::interpolate(int numVertices,float **varying,float ***locals) const {
	if (parameters != NULL)	parameters->dispatch(numVertices,varying,locals);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CToroid
// Method				:	instantiate
// Description			:	See object.h
// Return Value			:	-
// Comments				:
void	CToroid::instantiate(CAttributes *a,CXform *x,CRendererContext *cx) const {
	CXform		*nx	=	new CXform(x);

	nx->concat(xform);	// Concetenate the local xform

	if (a == NULL)	a	=	attributes;

	if (nextData == NULL)
		cx->addObject(new CToroid(a,nx,parameters,parametersF,rmin,rmax,vmin,vmax,umax));
	else
		cx->addObject(new CToroid(a,nx,parameters,parametersF,rmin,rmax,vmin,vmax,umax,nextData[0],nextData[1],nextData[2],nextData[3],nextData[4]));
}

///////////////////////////////////////////////////////////////////////
// Class				:	CToroid
// Method				:	computeObjectBound
// Description			:	Compute the bounding box in the object space
// Return Value			:	-
// Comments				:
void			CToroid::computeObjectBound(float *bmin,float *bmax,float rmin,float rmax,float vmin,float vmax,float umax) {
	float	r	=	absf(rmin) + absf(rmax);

	bmin[COMP_X]		=	-r;
	bmin[COMP_Y]		=	-r;
	bmax[COMP_X]		=	r;
	bmax[COMP_Y]		=	r;
	bmin[COMP_Z]		=	-absf(rmin);
	bmax[COMP_Z]		=	absf(rmin);
}

