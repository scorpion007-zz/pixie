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
//  File				:	irradiance.cpp
//  Classes				:	CIrradianceCache
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "irradiance.h"
#include "error.h"
#include "memory.h"
#include "shading.h"
#include "bundles.h"
#include "photonMap.h"
#include "stats.h"


const	float	weightNormalDenominator	=	(float) (1 / (1 - cos(radians(10))));



///////////////////////////////////////////////////////////////////////
//
//
//		Irradiance Cache Implementation
//
//
///////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////
// Class				:	CIrradianceCache
// Method				:	CIrradianceCache
// Description			:	Ctor
// Return Value			:
// Comments				:
// Date last edited		:	10/15/2003
CIrradianceCache::CIrradianceCache(const char *name,unsigned int f,const float *bmin,const float *bmax,CXform *w,CHierarchy *h,FILE *in) : CCache(name,f) {
	int	i;

	memory				=	new CMemStack;		// Where we allocate our memory from
	root				=	NULL;
	maxDepth			=	1;
	hierarchy			=	h;

	// Are we reading from file ?
	if (flags & CACHE_READ) {
		if (in == NULL)	in	=	ropen(name,"rb",fileIrradianceCache);

		if (in != NULL) {
			fread(fromWorld,	sizeof(matrix),1,in);
			fread(toWorld,		sizeof(matrix),1,in);

			// Read the samples
			fread(&maxDepth,	sizeof(int),1,in);
			root	=	readNode(in);

			fclose(in);

			mulmm(from,fromWorld,w->to);
			mulmm(to,w->from,toWorld);
		}
	}

	// Are we creating a fresh cache ?
	if (root == NULL) {
		vector	center;

		root			=	(CCacheNode *) memory->alloc(sizeof(CCacheNode));
		for (i=0;i<8;i++)	root->children[i]	=	NULL;
		addvv(center,bmin,bmax);
		mulvf(center,1 / (float) 2);
		movvv(root->center,center);
		root->side		=	max(max(bmax[0] - bmin[0],bmax[1] - bmin[1]),bmax[2] - bmin[2]);
		root->samples	=	NULL;

		movmm(fromWorld,w->from);
		movmm(toWorld,w->to);
		identitym(from);
		identitym(to);
	}
}




///////////////////////////////////////////////////////////////////////
// Class				:	CIrradianceCache
// Method				:	~CIrradianceCache
// Description			:	Dtor
// Return Value			:
// Comments				:
// Date last edited		:	10/15/2003
CIrradianceCache::~CIrradianceCache() {
	// Are we writing the file out ?
	if (flags & CACHE_WRITE) {
		FILE	*out	=	ropen(name,"wb",fileIrradianceCache);

		if (out != NULL) {
			fwrite(fromWorld,	sizeof(matrix),1,out);
			fwrite(toWorld,		sizeof(matrix),1,out);

			// Write the samples
			fwrite(&maxDepth,	sizeof(int),1,out);
			writeNode(out,root);

			fclose(out);
		}
	}

	// Delete the memory pool
	delete memory;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CIrradianceCache
// Method				:	writeNode
// Description			:	Write a node into a file
// Return Value			:
// Comments				:
// Date last edited		:	10/15/2003
void			CIrradianceCache::writeNode(FILE *out,CCacheNode *cNode) {
	int				numSamples,i;
	CCacheSample	*cSample;

	fwrite(cNode->center,	sizeof(vector),1,out);
	fwrite(&cNode->side,	sizeof(float),1,out);

	for (cSample=cNode->samples,numSamples=0;cSample!=NULL;cSample=cSample->next,numSamples++);

	fwrite(&numSamples,		sizeof(int),1,out);

	for (cSample=cNode->samples;cSample!=NULL;cSample=cSample->next) {
		fwrite(cSample,		sizeof(CCacheSample),1,out);
	}

	fwrite(cNode->children,	sizeof(CCacheNode *),8,out);
	for (i=0;i<8;i++) {
		if (cNode->children[i] != NULL)	writeNode(out,cNode->children[i]);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CIrradianceCache
// Method				:	readNode
// Description			:	Read a node from file
// Return Value			:
// Comments				:
// Date last edited		:	10/15/2003
CIrradianceCache::CCacheNode		*CIrradianceCache::readNode(FILE *in) {
	int				numSamples,i;
	CCacheNode		*cNode	=	(CCacheNode *) memory->alloc(sizeof(CCacheNode));

	fread(cNode->center,	sizeof(vector),1,in);
	fread(&cNode->side,		sizeof(float),1,in);

	fread(&numSamples,		sizeof(int),1,in);
	
	for(cNode->samples=NULL;numSamples>0;numSamples--) {
		CCacheSample	*cSample	=	(CCacheSample *) memory->alloc(sizeof(CCacheSample));
		fread(cSample,sizeof(CCacheSample),1,in);
		cSample->next				=	cNode->samples;
		cNode->samples				=	cSample;
	}

	fread(cNode->children,	sizeof(CCacheNode *),8,in);
	for (i=0;i<8;i++) {
		if (cNode->children[i] != NULL)	cNode->children[i]	=	readNode(in);
	}

	return cNode;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CIrradianceCache
// Method				:	lookup
// Description			:	Lookup da cache
// Return Value			:
// Comments				:
// Date last edited		:	10/15/2003
void	CIrradianceCache::lookup(float *C,const float *cP,const float *cN,const CGlobalIllumLookup *lookup) {
	vector				P,N;
	CCacheSample		*cSample;
	CCacheNode			*cNode;
	float				totalWeight		=	0;
	CCacheNode			**stackBase		=	(CCacheNode **)	alloca(maxDepth*sizeof(CCacheNode *)*8);
	CCacheNode			**stack;
	int					i;
	float				coverage;
	vector				irradiance,envdir;
	const float			maxError		=	lookup->maxError;
	int					numSummed		=	0;
	
	// Convert the query point into the right coordinate system
	mulmp(P,from,cP);
	mulmn(N,to,cN);

	// Init the result
	coverage	=	0;
	initv(irradiance,0);
	initv(envdir,0);

	stack		=	stackBase;
	*stack++	=	root;
	while(stack > stackBase) {
		cNode	=	*(--stack);

		// Sum the values in this level
		for (cSample=cNode->samples;cSample!=NULL;cSample=cSample->next) {
			vector	D;
			float	e1,e2;
			float	w;

			// D = vector from sample to query point
			subvv(D,P,cSample->P);

			// Ignore sample in the front
			if (dotvv(D,cSample->N) > C_EPSILON)	continue;

			// The blending weight computation

			// Positional weight
			e1		=	lengthv(D) / cSample->dP;

			// Directional weight
			e2		=	1 - dotvv(N,cSample->N);
			if (e2 < 0)	e2	=	0;
			e2		=	sqrtf(e2 * weightNormalDenominator);

			// Are we writing ?
			w		=	1 - maxError * max(e1,e2);
			if (w > 0) {
				vector	ntmp;

				crossvv(ntmp,N,cSample->N);

				totalWeight		+=	w;
				coverage		+=	w*(cSample->coverage		+ dotvv(cSample->gP+0*3,D) + dotvv(cSample->gR+0*3,ntmp));
				irradiance[0]	+=	w*(cSample->irradiance[0]	+ dotvv(cSample->gP+1*3,D) + dotvv(cSample->gR+1*3,ntmp));
				irradiance[1]	+=	w*(cSample->irradiance[1]	+ dotvv(cSample->gP+2*3,D) + dotvv(cSample->gR+2*3,ntmp));
				irradiance[2]	+=	w*(cSample->irradiance[2]	+ dotvv(cSample->gP+3*3,D) + dotvv(cSample->gR+3*3,ntmp));
				envdir[0]		+=	w*(cSample->envdir[0]		+ dotvv(cSample->gP+4*3,D) + dotvv(cSample->gR+4*3,ntmp));
				envdir[1]		+=	w*(cSample->envdir[1]		+ dotvv(cSample->gP+5*3,D) + dotvv(cSample->gR+5*3,ntmp));
				envdir[2]		+=	w*(cSample->envdir[2]		+ dotvv(cSample->gP+6*3,D) + dotvv(cSample->gR+6*3,ntmp));

				numSummed++;
			}
		}

		// Check the children
		for (i=0;i<8;i++) {
			CCacheNode	*tNode;

			if ((tNode = cNode->children[i]) != NULL) {
				const float	tSide	=	tNode->side;

				if (	((tNode->center[0] + tSide) > P[0])	&&
						((tNode->center[1] + tSide) > P[1])	&&
						((tNode->center[2] + tSide) > P[2])	&&
						((tNode->center[0] - tSide) < P[0])	&&
						((tNode->center[1] - tSide) < P[1])	&&
						((tNode->center[2] - tSide) < P[2])) {
					*stack++	=	tNode;
				}
			}
		}
	}

	if (totalWeight > C_EPSILON) {
		double	normalizer	=	1 / totalWeight;

		normalizevf(envdir);

		C[0]			=	(float) (irradiance[0]*normalizer);
		C[1]			=	(float) (irradiance[1]*normalizer);
		C[2]			=	(float) (irradiance[2]*normalizer);
		C[3]			=	(float) (coverage*normalizer);
		C[4]			=	envdir[0];
		C[5]			=	envdir[1];
		C[6]			=	envdir[2];
	} else {
		if (flags & CACHE_SAMPLE) {
			sample(C,cP,cN,lookup);
		} else {
			C[0]	=	0;
			C[1]	=	0;
			C[2]	=	0;
			C[3]	=	0;
			C[4]	=	0;
			C[5]	=	0;
			C[6]	=	0;
		}
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CIrradianceCache
// Method				:	sample
// Description			:	Check if there's a nearby sample
// Return Value			:	-
// Comments				:
// Date last edited		:	10/6/2003
void	CIrradianceCache::cachesample(float *C,const float *cP,const float *cN,float dP) {
	CCacheSample	*cSample;
	CCacheNode		*cNode;
	CCacheNode		**stackBase		=	(CCacheNode **)	alloca(maxDepth*sizeof(CCacheNode *)*8);
	CCacheNode		**stack			=	stackBase;
	int				i;
	vector			P,N,Pn;

	// Convert the query point into the right coordinate system
	mulmp(P,from,cP);
	mulmn(N,to,cN);
	normalizev(Pn,P);

	*stack++	=	root;
	while(stack > stackBase) {
		cNode	=	*(--stack);

		// Sum the values in this level
		for (cSample=cNode->samples;cSample!=NULL;cSample=cSample->next) {
			float	d	=	dotvv(Pn,cSample->P);
			float	q	=	dotvv(cSample->P,cSample->P) - d*d;

			if (q < dP*dP) {
				C[0]	=	1;
				return;
			}
		}

		// Check the children
		for (i=0;i<8;i++) {
			CCacheNode	*tNode;

			if ((tNode = cNode->children[i]) != NULL) {
				const float	tSide	=	tNode->side+dP;

				if (	((tNode->center[0] + tSide) > P[0])	&&
						((tNode->center[1] + tSide) > P[1])	&&
						((tNode->center[2] + tSide) > P[2])	&&
						((tNode->center[0] - tSide) < P[0])	&&
						((tNode->center[1] - tSide) < P[1])	&&
						((tNode->center[2] - tSide) < P[2])) {
					*stack++	=	tNode;
				}
			}
		}
	}

	C[0]	=	0;
}














///////////////////////////////////////////////////////////////////////
// Class				:	CHemisphereSample
// Description			:	This class is used to hold data about a hemisphere sample
// Comments				:	-
// Date last edited		:	5/15/2004
class	CHemisphereSample {
public:
		vector	dir;			// Direction in the camera coordinate system
		float	invDepth;		// 1 / intersection depth
		float	depth;			// The depth
		float	coverage;		// Coverage amount {0,1}
		vector	envdir;			// The envdir amount
		vector	irradiance;		// The irradiance amount
};





///////////////////////////////////////////////////////////////////////
// Function				:	posGradient
// Description			:	Compute the positional gradient for bunch of data points
// Return Value			:	-
// Comments				:
// Date last edited		:	5/15/2004
inline	void	posGradient(float *dP,int np,int nt,CHemisphereSample *h) {
	int					i,j,k;
	double				nextsine, lastsine, d;
	double				mag0[7], mag1[7];
	double				phi, cosp, sinp, xd[7], yd[7];
	CHemisphereSample  *dp;

	for (k=0;k<7;k++) {	xd[k]	= yd[k] = 0.0;	}

	for (j=0;j<np;j++) {
		dp			=	h + j;

		for (k=0;k<7;k++) {	
			mag0[k]		=	mag1[k]	= 0.0;
		}

		lastsine	=	0.0;

		for (i=0;i<nt;i++) {
			if (i > 0) {
				assert((dp - np) >= h);

				d		=	dp[-np].invDepth;
				if (dp[0].invDepth > d) d = dp[0].invDepth;

				d		*= lastsine * (1.0 - (double)i/(double) nt);
				mag0[0]	+= d*(dp->coverage - dp[-np].coverage);
				mag0[1]	+= d*(dp->irradiance[0] - dp[-np].irradiance[0]);
				mag0[2]	+= d*(dp->irradiance[1] - dp[-np].irradiance[1]);
				mag0[3]	+= d*(dp->irradiance[2] - dp[-np].irradiance[2]);
				mag0[4]	+= d*(dp->envdir[0] - dp[-np].envdir[0]);
				mag0[5]	+= d*(dp->envdir[1] - dp[-np].envdir[1]);
				mag0[6]	+= d*(dp->envdir[2] - dp[-np].envdir[2]);
			}

			nextsine = sqrt((double)(i+1)/(double) nt);

			if (j > 0) {
				assert((dp-1) >= h);

				d		=	dp[-1].invDepth;
				if (dp[0].invDepth > d) d = dp[0].invDepth;

				d		*=	(nextsine - lastsine);

				mag1[0]	+= d*(dp->coverage - dp[-1].coverage);
				mag1[1]	+= d*(dp->irradiance[0] - dp[-1].irradiance[0]);
				mag1[2]	+= d*(dp->irradiance[1] - dp[-1].irradiance[1]);
				mag1[3]	+= d*(dp->irradiance[2] - dp[-1].irradiance[2]);
				mag1[4]	+= d*(dp->envdir[0] - dp[-1].envdir[0]);
				mag1[5]	+= d*(dp->envdir[1] - dp[-1].envdir[1]);
				mag1[6]	+= d*(dp->envdir[2] - dp[-1].envdir[2]);

			} else {
				assert((dp+np-1) < h+np*nt);

				d		= dp[np-1].invDepth;
				if (dp[0].invDepth > d) d = dp[0].invDepth;

				d		*=	(nextsine - lastsine);

				mag1[0]	+= d*(dp->coverage - dp[np-1].coverage);
				mag1[1]	+= d*(dp->irradiance[0] - dp[np-1].irradiance[0]);
				mag1[2]	+= d*(dp->irradiance[1] - dp[np-1].irradiance[1]);
				mag1[3]	+= d*(dp->irradiance[2] - dp[np-1].irradiance[2]);
				mag1[4]	+= d*(dp->envdir[0] - dp[np-1].envdir[0]);
				mag1[5]	+= d*(dp->envdir[1] - dp[np-1].envdir[1]);
				mag1[6]	+= d*(dp->envdir[2] - dp[np-1].envdir[2]);

			}

			dp			+=	np;
			lastsine	=	nextsine;
		}

		for (k=0;k<7;k++)	mag0[k]	*=	2.0*C_PI / (double) np;

		phi		=	2.0*C_PI * (double)j/(double) np;
		cosp	=	cos(phi);
		sinp	=	sin(phi);

		for (k=0;k<7;k++) {
			xd[k]		+=	mag0[k]*cosp - mag1[k]*sinp;
			yd[k]		+=	mag0[k]*sinp + mag1[k]*cosp;
		}
	}

	d			=	1 / C_PI;

	for (k=0;k<7;k++) {
		dP[k*3 + COMP_X]	=	(float) (yd[k]*d);
		dP[k*3 + COMP_Y]	=	(float) (xd[k]*d);
		dP[k*3 + COMP_Z]	=	0;
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	rotGradient
// Description			:	Compute the rotational gradient for bunch of data points
// Return Value			:	-
// Comments				:
// Date last edited		:	5/15/2004
inline	void	rotGradient(float *dP,int np,int nt,CHemisphereSample *h) {
	int					i,j,k;
	double				mag[7];
	double				phi, xd[7], yd[7],cosphi,sinphi;
	CHemisphereSample	*dp;

	for (i=0;i<7;i++)	{	xd[i] = yd[i] = 0.0;	}

	for (j=0;j<np;j++) {
		dp	= h + j;

		for (k=0;k<7;k++) mag[k] = 0.0;

		for (i=0;i<nt;i++) {
			const double	tmp	=	1 / sqrt(nt/(i+.5) - 1.0);
			mag[0]	+= dp->coverage*tmp;
			mag[1]	+= dp->irradiance[0]*tmp;
			mag[2]	+= dp->irradiance[1]*tmp;
			mag[3]	+= dp->irradiance[2]*tmp;
			mag[4]	+= dp->envdir[0]*tmp;
			mag[5]	+= dp->envdir[1]*tmp;
			mag[6]	+= dp->envdir[2]*tmp;
			dp		+= np;
		}
		phi		=	2.0*C_PI * (j+.5)/np + C_PI/2.0;
		cosphi	=	cos(phi);
		sinphi	=	sin(phi);

		for (k=0;k<7;k++) {
			xd[k]	+=	mag[k] * cosphi;
			yd[k]	+=	mag[k] * sinphi;
		}
	}

	cosphi		=	1 / (double) (nt*np);

	for (i=0;i<7;i++) {
		dP[i*3 + COMP_X]	=	(float) (yd[i]*cosphi);
		dP[i*3 + COMP_Y]	=	(float) (xd[i]*cosphi);
		dP[i*3 + COMP_Z]	=	0;
	}
}




///////////////////////////////////////////////////////////////////////
// Class				:	CIrradianceCache
// Method				:	sample
// Description			:	Sample the occlusion
// Return Value			:
// Comments				:
// Date last edited		:	10/15/2003
void		CIrradianceCache::sample(float *C,const float *P,const float *N,const CGlobalIllumLookup *lookup) {
	CCacheSample		*cSample;
	int					i,j;
	int					numSamples		=	lookup->numSamples;
	float				coverage;
	vector				irradiance;
	vector				envdir;
	float				rMean;
	float				rMeanMin;
	CRay				ray;
	int					nt,np;
	vector				X,Y;
	CHemisphereSample	*hemisphere;
	CCacheNode			*cNode;
	int					depth;
	float				tmp;
	CTextureLookup		*texLookup;
	const float			footprint	=	P[COMP_Z]*lookup->lengthA + lookup->lengthB;

	// Allocate memory
	nt								=	(int) (sqrtf(numSamples / C_PI) + 0.5);
	np								=	(int) (C_PI*nt + 0.5);
	numSamples						=	nt*np;
	hemisphere						=	(CHemisphereSample *) alloca(numSamples*sizeof(CHemisphereSample));

	if(lookup->environment != NULL){
		texLookup = (CTextureLookup*) alloca(sizeof(CTextureLookup));
		texLookup->filter		= RiGaussianFilter;
		texLookup->blur			= 0;
		texLookup->swidth		= 1;
		texLookup->twidth		= 1;
		texLookup->numSamples	= 1;
		texLookup->channel		= 0;
		texLookup->fill			= 0;
		texLookup->shadowBias	= lookup->bias;
		texLookup->maxDist		= C_INFINITY;
		texLookup->coneAngle	= 0;
		texLookup->label		= NULL;
		texLookup->lookupFloat	= FALSE;
		texLookup->texture		= NULL;
		texLookup->environment	= lookup->environment;
	}
						
	// Create an orthanormal coordinate system
	crossvv(X,N,P);
	normalizevf(X);
	crossvv(Y,N,X);

	// Sample the hemisphere
	coverage						=	0;
	initv(irradiance,0);
	initv(envdir,0);
	rMean							=	0;
	rMeanMin						=	C_INFINITY;

	if (lookup->occlusion == TRUE) {

		// We're shading for occlusion
		stats.numOcclusionRays			+=	numSamples;
		stats.numOcclusionSamples++;

		for (i=0;i<nt;i++) {
			for (j=0;j<np;j++,hemisphere++) {
				float		tmp			=	sqrtf((i+urand()) / (float) nt);
				const float	phi			=	(float) (2*C_PI*(j+urand()) / (float) np);
				const float	cosPhi		=	(cosf(phi)*tmp);
				const float	sinPhi		=	(sinf(phi)*tmp);
				const float	dx			=	(2*urand()-1)*footprint;
				const float	dy			=	(2*urand()-1)*footprint;

				tmp						=	sqrtf(1 - tmp*tmp);

				ray.dir[0]				=	X[0]*sinPhi + Y[0]*cosPhi + N[0]*tmp;
				ray.dir[1]				=	X[1]*sinPhi + Y[1]*cosPhi + N[1]*tmp;
				ray.dir[2]				=	X[2]*sinPhi + Y[2]*cosPhi + N[2]*tmp;

				ray.from[COMP_X]		=	P[COMP_X] + X[COMP_X]*dx + Y[COMP_X]*dy;
				ray.from[COMP_Y]		=	P[COMP_Y] + X[COMP_Y]*dx + Y[COMP_Y]*dy;
				ray.from[COMP_Z]		=	P[COMP_Z] + X[COMP_Z]*dx + Y[COMP_Z]*dy;

				addvv(ray.to,ray.from,ray.dir);

				ray.flags				=	ATTRIBUTES_FLAGS_TRACE_VISIBLE;
				ray.tmin				=	lookup->bias;
				ray.invDir[COMP_X]		=	1/ray.dir[COMP_X];
				ray.invDir[COMP_Y]		=	1/ray.dir[COMP_Y];
				ray.invDir[COMP_Z]		=	1/ray.dir[COMP_Z];
				ray.t					=	lookup->maxDistance;
				ray.time				=	0;
				ray.jimp				=	-1.0f;
				ray.lastXform			=	NULL;
				ray.object				=	NULL;

				hierarchy->intersect(&ray);

				// Do we have an intersection ?
				if (ray.object != NULL) {
					const float	*color		=	ray.object->attributes->surfaceColor;

					// Yes
					coverage++;
					addvv(irradiance,color);

					hemisphere->coverage	=	1;
					initv(hemisphere->envdir,0);
					movvv(hemisphere->irradiance,color);
				} else {
					// No
					hemisphere->coverage	=	0;
					addvv(envdir,ray.dir);
					movvv(hemisphere->envdir,ray.dir);
					
					// GSH : Texture lookup for misses
					if(lookup->environment != NULL){
						CEnvironment *tex = lookup->environment;
						vector D0,D1,D2,D3;
						vector color;

						// GSHTODO: Add in the dCosPhi and dSinPhi
						movvv(D0,ray.dir);
						movvv(D1,ray.dir);
						movvv(D2,ray.dir);
						movvv(D3,ray.dir);
						
						tex->lookup(color,D0,D1,D2,D3,texLookup);
						addvv(irradiance,color);
						movvv(hemisphere->irradiance,color);
					} else{
						initv(hemisphere->irradiance,0);
					}
				}

				rMean						+=	1 / ray.t;
				rMeanMin					=	min(rMeanMin,ray.t);

				hemisphere->depth			=	ray.t;
				hemisphere->invDepth		=	1 / ray.t;
				movvv(hemisphere->dir,ray.dir);

				assert(hemisphere->invDepth > 0);
			}
		}
	} else {

		// We're shading for indirectdiffuse
		stats.numIndirectDiffuseRays	+=	numSamples;
		stats.numIndirectDiffuseSamples++;

		for (i=0;i<nt;i++) {
			for (j=0;j<np;j++,hemisphere++) {
				float		tmp			=	sqrtf((i+urand()) / (float) nt);
				const float	phi			=	(float) (2*C_PI*(j+urand()) / (float) np);
				const float	cosPhi		=	(cosf(phi)*tmp);
				const float	sinPhi		=	(sinf(phi)*tmp);
				const float	dx			=	(2*urand()-1)*footprint;
				const float	dy			=	(2*urand()-1)*footprint;

				tmp						=	sqrtf(1 - tmp*tmp);

				ray.dir[0]				=	X[0]*sinPhi + Y[0]*cosPhi + N[0]*tmp;
				ray.dir[1]				=	X[1]*sinPhi + Y[1]*cosPhi + N[1]*tmp;
				ray.dir[2]				=	X[2]*sinPhi + Y[2]*cosPhi + N[2]*tmp;

				ray.from[COMP_X]		=	P[COMP_X] + X[COMP_X]*dx + Y[COMP_X]*dy;
				ray.from[COMP_Y]		=	P[COMP_Y] + X[COMP_Y]*dx + Y[COMP_Y]*dy;
				ray.from[COMP_Z]		=	P[COMP_Z] + X[COMP_Z]*dx + Y[COMP_Z]*dy;

				addvv(ray.to,ray.from,ray.dir);

				ray.flags				=	ATTRIBUTES_FLAGS_TRACE_VISIBLE;
				ray.tmin				=	lookup->bias;
				ray.invDir[COMP_X]		=	1/ray.dir[COMP_X];
				ray.invDir[COMP_Y]		=	1/ray.dir[COMP_Y];
				ray.invDir[COMP_Z]		=	1/ray.dir[COMP_Z];
				ray.t					=	lookup->maxDistance;
				ray.time				=	0;
				ray.jimp				=	-1.0f;
				ray.lastXform			=	NULL;
				ray.object				=	NULL;

				hierarchy->intersect(&ray);

				// Do we have an intersection ?
				if (ray.object != NULL) {
					vector		P,N,C;
					CAttributes	*attributes	=	ray.object->attributes;
					CPhotonMap	*globalMap;

					if ((globalMap = attributes->globalMap) != NULL) {
						normalizev(N,ray.N);
						mulvf(P,ray.dir,ray.t);
						addvv(P,ray.from);
						
						if(dotvv(ray.dir,N) > 0)
							mulvf(N,-1);

						globalMap->lookup(C,P,N,attributes->photonEstimator);

						// HACK: Avoid too bright spots
						tmp	=	max(max(C[0],C[1]),C[2]);
						if (tmp > lookup->maxBrightness)	mulvf(C,lookup->maxBrightness/tmp);
						
						mulvv(C,attributes->surfaceColor);
						addvv(irradiance,C);
						movvv(hemisphere->irradiance,C);

						stats.numIndirectDiffusePhotonmapLookups++;
					} else {
						initv(hemisphere->irradiance,0);
					}

					// Yes
					coverage++;

					hemisphere->coverage	=	1;
					initv(hemisphere->envdir,0);
				} else {
					// No
					hemisphere->coverage	=	0;
					addvv(envdir,ray.dir);
					movvv(hemisphere->envdir,ray.dir);
					
					// GSH : Texture lookup for misses
					if(lookup->environment != NULL){
						CEnvironment *tex = lookup->environment;
						vector D0,D1,D2,D3;
						vector color;

						// GSHTODO: Add in the dCosPhi and dSinPhi
						movvv(D0,ray.dir);
						movvv(D1,ray.dir);
						movvv(D2,ray.dir);
						movvv(D3,ray.dir);
						
						tex->lookup(color,D0,D1,D2,D3,texLookup);
						addvv(irradiance,color);
						movvv(hemisphere->irradiance,color);
					} else{
						movvv(hemisphere->irradiance,lookup->backgroundColor);
						addvv(irradiance,lookup->backgroundColor);
					}
				}

				rMean						+=	1 / ray.t;
				rMeanMin					=	min(rMeanMin,ray.t);

				hemisphere->depth			=	ray.t;
				hemisphere->invDepth		=	1 / ray.t;
				movvv(hemisphere->dir,ray.dir);

				assert(hemisphere->invDepth > 0);
			}
		}
	}
	hemisphere				-=	np*nt;

	// Normalize
	tmp						=	1 / (float) numSamples;
	coverage				*=	tmp;
	mulvf(irradiance,tmp);
	mulvf(envdir,tmp);
	normalizevf(envdir);

	// Record the value
	C[0]					=	irradiance[0];
	C[1]					=	irradiance[1];
	C[2]					=	irradiance[2];
	C[3]					=	coverage;
	C[4]					=	envdir[0];
	C[5]					=	envdir[1];
	C[6]					=	envdir[2];

	// Should we save it ?
	if (lookup->maxError != 0) {
		float	gP[7*3],gR[7*3];

		// Compute the radius of validity
		rMean					=	rMeanMin / 2;
		rMean					=	max(rMean, lookup->lengthA*lookup->minFGRadius + lookup->lengthB);
		rMean					=	min(rMean, lookup->lengthA*lookup->maxFGRadius + lookup->lengthB);

		// Create the sample
		cSample					=	(CCacheSample *) memory->alloc(sizeof(CCacheSample));

		// Compute the gradients
		posGradient(gP,np,nt,hemisphere);
		rotGradient(gR,np,nt,hemisphere);
		for (i=0;i<7;i++) {
			cSample->gP[i*3 + COMP_X]	=	X[COMP_X]*gP[i*3 + COMP_X] + Y[COMP_X]*gP[i*3 + COMP_Y];
			cSample->gP[i*3 + COMP_Y]	=	X[COMP_Y]*gP[i*3 + COMP_X] + Y[COMP_Y]*gP[i*3 + COMP_Y];
			cSample->gP[i*3 + COMP_Z]	=	X[COMP_Z]*gP[i*3 + COMP_X] + Y[COMP_Z]*gP[i*3 + COMP_Y];

			cSample->gR[i*3 + COMP_X]	=	X[COMP_X]*gR[i*3 + COMP_X] + Y[COMP_X]*gR[i*3 + COMP_Y];
			cSample->gR[i*3 + COMP_Y]	=	X[COMP_Y]*gR[i*3 + COMP_X] + Y[COMP_Y]*gR[i*3 + COMP_Y];
			cSample->gR[i*3 + COMP_Z]	=	X[COMP_Z]*gR[i*3 + COMP_X] + Y[COMP_Z]*gR[i*3 + COMP_Y];
		}

		// Record the data
		movvv(cSample->P,P);
		movvv(cSample->N,N);
		cSample->dP				=	rMean;
		cSample->coverage		=	coverage;
		movvv(cSample->envdir,envdir);
		movvv(cSample->irradiance,irradiance);

		// Insert the new sample into the cache
		rMean					=	rMean/lookup->maxError;
		cNode					=	root;
		depth					=	0;
		while(cNode->side > (2*rMean)) {
			depth++;

			for (j=0,i=0;i<3;i++) {
				if (P[i] > cNode->center[i]) {
					j			|=	1 << i;
				}
			}

			if (cNode->children[j] == NULL)	{
				CCacheNode	*nNode	=	(CCacheNode *) memory->alloc(sizeof(CCacheNode));

				for (i=0;i<3;i++) {
					if (P[i] > cNode->center[i]) {
						nNode->center[i]	=	cNode->center[i] + cNode->side / (float) 4;
					} else {
						nNode->center[i]	=	cNode->center[i] - cNode->side / (float) 4;
					}
				}

				cNode->children[j]	=	nNode;
				nNode->side			=	cNode->side / (float) 2;
				nNode->samples		=	NULL;
				for (i=0;i<8;i++)	nNode->children[i]	=	NULL;
			}

			cNode			=	cNode->children[j];
		}

		cSample->next	=	cNode->samples;
		cNode->samples	=	cSample;
		maxDepth		=	max(depth,maxDepth);
	}
}




///////////////////////////////////////////////////////////////////////
// Class				:	CIrradianceCache
// Method				:	draw
// Description			:	Draw the irradiance cache
// Return Value			:
// Comments				:
// Date last edited		:	9/22/2006
void		CIrradianceCache::draw() {
	CCacheSample		*cSample;
	CCacheNode			*cNode;
	CCacheNode			**stackBase		=	(CCacheNode **)	alloca(maxDepth*sizeof(CCacheNode *)*8);
	CCacheNode			**stack;
	int					i,j;
	float				P[chunkSize*3];
	float				C[chunkSize*3];
	float				*cP,*cC;

	j			=	chunkSize;
	cP			=	P;
	cC			=	C;
	stack		=	stackBase;
	*stack++	=	root;
	while(stack > stackBase) {
		cNode	=	*(--stack);

		// Sum the values in this level
		for (cSample=cNode->samples;cSample!=NULL;cSample=cSample->next,j--) {
			if (j == 0)	{
				drawPoints(chunkSize,P,C);
				cP	=	P;
				cC	=	C;
				j	=	chunkSize;
			}

			// FIXME: Maybe we should draw disks instead of points here
			movvv(cP,cSample->P);
			movvv(cC,cSample->irradiance);
		}

		// Check the children
		for (i=0;i<8;i++) {
			CCacheNode	*tNode;

			if ((tNode = cNode->children[i]) != NULL) {
				*stack++	=	tNode;
			}
		}
	}

	if (j != chunkSize)	drawPoints(chunkSize-j,P,C);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CIrradianceCache
// Method				:	bound
// Description			:	Bound the irradiance cache
// Return Value			:
// Comments				:
// Date last edited		:	9/22/2006
void		CIrradianceCache::bound(float *bmin,float *bmax) {
	assert(root != NULL);

	bmin[0]	=	root->center[0] - root->side*0.5f;
	bmin[1]	=	root->center[1] - root->side*0.5f;
	bmin[2]	=	root->center[2] - root->side*0.5f;

	bmax[0]	=	root->center[0] + root->side*0.5f;
	bmax[1]	=	root->center[1] + root->side*0.5f;
	bmax[2]	=	root->center[2] + root->side*0.5f;
}



