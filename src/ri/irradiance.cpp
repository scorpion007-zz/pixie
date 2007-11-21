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
#include <math.h>

#include "irradiance.h"
#include "error.h"
#include "memory.h"
#include "shading.h"
#include "bundles.h"
#include "photonMap.h"
#include "surface.h"
#include "stats.h"
#include "texture.h"
#include "renderer.h"
#include "ri_config.h"
#include "debug.h"
#include "pointHierarchy.h"
#include "shaderPl.h"

const	float	weightNormalDenominator	=	(float) (1 / (1 - cos(radians(10))));
const	float	horizonCutoff			=	(float) cosf((float) radians(80));

///////////////////////////////////////////////////////////////////////
//
//
//		Irradiance Cache Implementation
//
//
///////////////////////////////////////////////////////////////////////

int						CIrradianceCache::drawDiscs			=	TRUE;
CTexture3d::CChannel	CIrradianceCache::cacheChannels[3]	=	{
	{	"irradiance",		3,	0,	NULL,	TYPE_COLOR	},
	{	"occlusion",		1,	3,	NULL,	TYPE_FLOAT	},
	{	"environmentdir",	3,	4,	NULL,	TYPE_VECTOR	}};

///////////////////////////////////////////////////////////////////////
// Class				:	CIrradianceCache
// Method				:	CIrradianceCache
// Description			:	Ctor
// Return Value			:
// Comments				:
CIrradianceCache::CIrradianceCache(const char *name,unsigned int f,FILE *in,const float *from,const float *to,const float *tondc) : CTexture3d(name,from,to,tondc,3,cacheChannels) {
	int	i;

	assert(dataSize == 7);
	assert(numChannels == 3);
	
	memory				=	new CMemStack;		// Where we allocate our memory from
	root				=	NULL;
	maxDepth			=	1;
	flags				=	f;
	osCreateMutex(mutex);

	// Are we reading from file ?
	if (flags & CACHE_READ) {
		if (in == NULL)	in	=	ropen(name,"rb",fileIrradianceCache);

		if (in != NULL) {
		
			// Read the samples
			fread(&maxDepth,	sizeof(int),1,in);
			root	=	readNode(in);

			// Close the file
			fclose(in);
		}
	}

	// Are we creating a fresh cache ?
	if (root == NULL) {
		vector	center,bmin,bmax;

		// Transform the bounding box to the world
		transformBound(bmin,bmax,to,CRenderer::worldBmin,CRenderer::worldBmax);

		root			=	(CCacheNode *) memory->alloc(sizeof(CCacheNode));
		for (i=0;i<8;i++)	root->children[i]	=	NULL;
		addvv(center,bmin,bmax);
		mulvf(center,0.5f);
		movvv(root->center,center);
		subvv(bmax,bmin);
		root->side		=	max(max(bmax[0],bmax[1]),bmax[2]);
		root->samples	=	NULL;
	}
}




///////////////////////////////////////////////////////////////////////
// Class				:	CIrradianceCache
// Method				:	~CIrradianceCache
// Description			:	Dtor
// Return Value			:
// Comments				:
CIrradianceCache::~CIrradianceCache() {

	osDeleteMutex(mutex);

	// Are we writing the file out ?
	if (flags & CACHE_WRITE) {
		if (name[0] != 0) {
			FILE	*out	=	ropen(name,"wb",fileIrradianceCache);

			if (out != NULL) {
			
				// Write the samples
				fwrite(&maxDepth,	sizeof(int),1,out);
				writeNode(out,root);

				fclose(out);
			}
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
void	CIrradianceCache::lookup(float *C,const float *cP,const float *cdPdu,const float *cdPdv,const float *cN,CShadingContext *context) {
	const CShadingScratch	*scratch		=	&(context->currentShadingState->scratch);

	// Is this a point based lookup?
	if ((scratch->occlusionParams.pointbased) && (scratch->occlusionParams.pointHierarchy != NULL)) {
		int	i;

		for (i=0;i<7;i++)	C[i]	=	0;

		scratch->occlusionParams.pointHierarchy->lookup(C,cP,cdPdu,cdPdv,cN,context);
	} else {
		CCacheSample		*cSample;
		CCacheNode			*cNode;
		float				totalWeight		=	0;
		CCacheNode			**stackBase		=	(CCacheNode **)	alloca(maxDepth*sizeof(CCacheNode *)*8);
		CCacheNode			**stack;
		int					i;
		float				coverage;
		vector				irradiance,envdir;
		vector				P,N;
		
		// A small value for discard-smoothing of irradiance
		const float			smallSampleWeight = (flags & CACHE_SAMPLE) ? 0.1f : 0.0f;

		// Transform the lookup point to the correct coordinate system
		mulmp(P,to,cP);
		mulmn(N,from,cN);
		
		// Init the result
		coverage	=	0;
		initv(irradiance,0);
		initv(envdir,0);

		// The weighting algorithm is that described in [Tabellion and Lamorlette 2004]
		// We need to convert the max error as in Wald to Tabellion 
		// The default value of maxError is 0.4f
		const float			K		=	0.4f / scratch->occlusionParams.maxError;

		// Note, we do not need to lock the data for reading
		// if word-writes are atomic
		
		// Prepare for the non recursive tree traversal
		stack		=	stackBase;
		*stack++	=	root;
		while(stack > stackBase) {
			cNode	=	*(--stack);

			// Sum the values in this level
			for (cSample=cNode->samples;cSample!=NULL;cSample=cSample->next) {
				vector	D;

				// D = vector from sample to query point
				subvv(D,P,cSample->P);

				// Ignore sample in the front
				float	a	=	dotvv(D,cSample->N);
				if ((a*a / (dotvv(D,D) + C_EPSILON)) > 0.1)	continue;

				// Positional error
				float	e1 = sqrtf(dotvv(D,D)) / cSample->dP;

				// Directional error
				float	e2 =	1 - dotvv(N,cSample->N);
				if (e2 < 0)	e2	=	0;
				e2		=	sqrtf(e2*weightNormalDenominator);

				// Compute the weight
				float	w		=	1 - K*max(e1,e2);
				if (w > context->urand()*smallSampleWeight) {
					vector	ntmp;

					crossvv(ntmp,cSample->N,N);
					
					// Sum the sample
					totalWeight		+=	w;
					coverage		+=	w*(cSample->coverage		+ dotvv(cSample->gP+0*3,D) + dotvv(cSample->gR+0*3,ntmp));
					irradiance[0]	+=	w*(cSample->irradiance[0]	+ dotvv(cSample->gP+1*3,D) + dotvv(cSample->gR+1*3,ntmp));
					irradiance[1]	+=	w*(cSample->irradiance[1]	+ dotvv(cSample->gP+2*3,D) + dotvv(cSample->gR+2*3,ntmp));
					irradiance[2]	+=	w*(cSample->irradiance[2]	+ dotvv(cSample->gP+3*3,D) + dotvv(cSample->gR+3*3,ntmp));
					envdir[0]		+=	w*(cSample->envdir[0]		+ dotvv(cSample->gP+4*3,D) + dotvv(cSample->gR+4*3,ntmp));
					envdir[1]		+=	w*(cSample->envdir[1]		+ dotvv(cSample->gP+5*3,D) + dotvv(cSample->gR+5*3,ntmp));
					envdir[2]		+=	w*(cSample->envdir[2]		+ dotvv(cSample->gP+6*3,D) + dotvv(cSample->gR+6*3,ntmp));
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

		// Do we have anything ?
		if (totalWeight > C_EPSILON) {
			double	normalizer	=	1 / totalWeight;

			normalizevf(envdir);

			C[0]			=	(float) (irradiance[0]*normalizer);
			C[1]			=	(float) (irradiance[1]*normalizer);
			C[2]			=	(float) (irradiance[2]*normalizer);
			C[3]			=	(float) (coverage*normalizer);
			mulmv(C+4,from,envdir);		// envdir is stored in the target coordinate system
		} else {
			// Are we sampling the cache ?
			if (flags & CACHE_SAMPLE) {
				vector	dPdu,dPdv;

				// Convert the tangent space
				mulmv(dPdu,to,cdPdu);
				mulmv(dPdv,to,cdPdv);

				// Create a new sample
				sample(C,P,dPdu,dPdv,N,context);
				mulmv(C+4,from,C+4);	// envdir is stored in the target coordinate system
			} else {

				// No joy
				C[0]	=	0;
				C[1]	=	0;
				C[2]	=	0;
				C[3]	=	1;
				C[4]	=	0;
				C[5]	=	0;
				C[6]	=	0;
			}
		}

		// Make sure we don't have NaNs
		assert(dotvv(C,C) >= 0);
	}
}
















///////////////////////////////////////////////////////////////////////
// Class				:	CHemisphereSample
// Description			:	This class is used to hold data about a hemisphere sample
// Comments				:	-
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
inline	void	posGradient(float *dP,int np,int nt,CHemisphereSample *h,const float *X,const float *Y) {
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
				mag0[0]	+= d*(dp->coverage		- dp[-np].coverage);
				mag0[1]	+= d*(dp->irradiance[0] - dp[-np].irradiance[0]);
				mag0[2]	+= d*(dp->irradiance[1] - dp[-np].irradiance[1]);
				mag0[3]	+= d*(dp->irradiance[2] - dp[-np].irradiance[2]);
				mag0[4]	+= d*(dp->envdir[0]		- dp[-np].envdir[0]);
				mag0[5]	+= d*(dp->envdir[1]		- dp[-np].envdir[1]);
				mag0[6]	+= d*(dp->envdir[2]		- dp[-np].envdir[2]);
			}

			nextsine = sqrt((double)(i+1)/(double) nt);

			if (j > 0) {
				assert((dp-1) >= h);

				d		=	dp[-1].invDepth;
				if (dp[0].invDepth > d) d = dp[0].invDepth;

				d		*=	(nextsine - lastsine);

				mag1[0]	+= d*(dp->coverage		- dp[-1].coverage);
				mag1[1]	+= d*(dp->irradiance[0] - dp[-1].irradiance[0]);
				mag1[2]	+= d*(dp->irradiance[1] - dp[-1].irradiance[1]);
				mag1[3]	+= d*(dp->irradiance[2] - dp[-1].irradiance[2]);
				mag1[4]	+= d*(dp->envdir[0]		- dp[-1].envdir[0]);
				mag1[5]	+= d*(dp->envdir[1]		- dp[-1].envdir[1]);
				mag1[6]	+= d*(dp->envdir[2]		- dp[-1].envdir[2]);

			} else {
				assert((dp+np-1) < h+np*nt);

				d		= dp[np-1].invDepth;
				if (dp[0].invDepth > d) d = dp[0].invDepth;

				d		*=	(nextsine - lastsine);

				mag1[0]	+= d*(dp->coverage		- dp[np-1].coverage);
				mag1[1]	+= d*(dp->irradiance[0] - dp[np-1].irradiance[0]);
				mag1[2]	+= d*(dp->irradiance[1] - dp[np-1].irradiance[1]);
				mag1[3]	+= d*(dp->irradiance[2] - dp[np-1].irradiance[2]);
				mag1[4]	+= d*(dp->envdir[0]		- dp[np-1].envdir[0]);
				mag1[5]	+= d*(dp->envdir[1]		- dp[np-1].envdir[1]);
				mag1[6]	+= d*(dp->envdir[2]		- dp[np-1].envdir[2]);

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

	d			=	1.0f / C_PI;

	for (i=0;i<7;i++) {
		dP[i*3 + COMP_X]	=	(float) ((xd[i]*X[COMP_X] + yd[i]*Y[COMP_X])*d);
		dP[i*3 + COMP_Y]	=	(float) ((xd[i]*X[COMP_Y] + yd[i]*Y[COMP_Y])*d);
		dP[i*3 + COMP_Z]	=	(float) ((xd[i]*X[COMP_Z] + yd[i]*Y[COMP_Z])*d);
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	rotGradient
// Description			:	Compute the rotational gradient for bunch of data points
// Return Value			:	-
// Comments				:
inline	void	rotGradient(float *dP,int np,int nt,CHemisphereSample *h,const float *X,const float *Y) {
	int					i,j,k;
	double				mag[7];
	double				xd[7], yd[7];
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

		const double	phi		=	2.0*C_PI * (j+.5)/np + C_PI/2.0;
		const double	cosphi	=	cos(phi);
		const double	sinphi	=	sin(phi);

		for (k=0;k<7;k++) {
			xd[k]	+=	mag[k] * cosphi;
			yd[k]	+=	mag[k] * sinphi;
		}
	}

	// Normalize the gradient
	const double	d		=	1 / (double) (nt*np);

	for (i=0;i<7;i++) {
		dP[i*3 + COMP_X]	=	(float) ((xd[i]*X[COMP_X] + yd[i]*Y[COMP_X])*d);
		dP[i*3 + COMP_Y]	=	(float) ((xd[i]*X[COMP_Y] + yd[i]*Y[COMP_Y])*d);
		dP[i*3 + COMP_Z]	=	(float) ((xd[i]*X[COMP_Z] + yd[i]*Y[COMP_Z])*d);
	}
}




///////////////////////////////////////////////////////////////////////
// Class				:	CIrradianceCache
// Method				:	sample
// Description			:	Sample the occlusion
// Return Value			:
// Comments				:
void		CIrradianceCache::sample(float *C,const float *P,const float *dPdu,const float *dPdv,const float *N,CShadingContext *context) {
	CCacheSample			*cSample;
	int						i,j;
	float					coverage;
	vector					irradiance;
	vector					envdir;
	float					rMean;
	CRay					ray;
	vector					X,Y;
	CCacheNode				*cNode;
	int						depth;

	// Allocate memory
	const CShadingScratch	*scratch		=	&(context->currentShadingState->scratch);
	const int				nt				=	(int) (sqrtf(scratch->traceParams.samples / (float) C_PI) + 0.5);
	const int				np				=	(int) (C_PI*nt + 0.5);
	const int				numSamples		=	nt*np;
	CHemisphereSample		*hemisphere		=	(CHemisphereSample *) alloca(numSamples*sizeof(CHemisphereSample));
	
	// initialize texture lookups if needed
	if (scratch->occlusionParams.environment) {
		CTextureLookup::staticInit(&(context->currentShadingState->scratch));
	}
	
	// Create an orthanormal coordinate system
	if (dotvv(dPdu,dPdu) > 0) {
		normalizevf(X,dPdu);
		crossvv(Y,N,X);
	} else if (dotvv(dPdv,dPdv) > 0) {
		normalizevf(X,dPdv);
		crossvv(Y,N,X);
	} else {
		// At this point, we're pretty screwed, so why not use the P
		normalizevf(X,P);
		crossvv(Y,N,X);
	}

	// Sample the hemisphere
	coverage						=	0;
	initv(irradiance,0);
	initv(envdir,0);
	rMean							=	C_INFINITY;
	
	// Calculate the ray differentials (use average spread in theta and phi)
	const float da					=	tanf((float) C_PI/(2*(nt+np)));
	const float db					=	(lengthv(dPdu) + lengthv(dPdv))*0.5f;
	
	if (scratch->occlusionParams.occlusion == TRUE) {

		// We're shading for occlusion
		context->numOcclusionRays			+=	numSamples;
		context->numOcclusionSamples++;

		for (i=0;i<nt;i++) {
			for (j=0;j<np;j++,hemisphere++) {
				float rv[2];
				context->random2d.get(rv);

				float		tmp			=	sqrtf((i+context->urand()) / (float) nt);
				const float	phi			=	(float) (2*C_PI*(j+context->urand()) / (float) np);
				const float	cosPhi		=	(cosf(phi)*tmp);
				const float	sinPhi		=	(sinf(phi)*tmp);

				tmp						=	sqrtf(1 - tmp*tmp);

				ray.dir[0]				=	X[0]*cosPhi + Y[0]*sinPhi + N[0]*tmp;
				ray.dir[1]				=	X[1]*cosPhi + Y[1]*sinPhi + N[1]*tmp;
				ray.dir[2]				=	X[2]*cosPhi + Y[2]*sinPhi + N[2]*tmp;

				const float originJitterX = (rv[0] - 0.5f)*scratch->traceParams.sampleBase;
				const float originJitterY = (rv[1] - 0.5f)*scratch->traceParams.sampleBase;
				
				ray.from[COMP_X]		=	P[COMP_X] + originJitterX*dPdu[0] + originJitterY*dPdv[0];
				ray.from[COMP_Y]		=	P[COMP_Y] + originJitterX*dPdu[1] + originJitterY*dPdv[1];
				ray.from[COMP_Z]		=	P[COMP_Z] + originJitterX*dPdu[2] + originJitterY*dPdv[2];

				ray.flags				=	ATTRIBUTES_FLAGS_DIFFUSE_VISIBLE;
				ray.tmin				=	scratch->traceParams.bias;
				ray.t					=	scratch->traceParams.maxDist;
				ray.time				=	0;
				ray.da					=	da;
				ray.db					=	db;

				// Transform the ray into the right coordinate system
				mulmp(ray.from,from,ray.from);
				mulmv(ray.dir,from,ray.dir);

				context->trace(&ray);

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
					if(scratch->occlusionParams.environment != NULL){
						CEnvironment *tex = scratch->occlusionParams.environment;
						vector D0,D1,D2,D3;
						vector color;

						// GSHTODO: Add in the dCosPhi and dSinPhi
						movvv(D0,ray.dir);
						movvv(D1,ray.dir);
						movvv(D2,ray.dir);
						movvv(D3,ray.dir);
						
						float savedSamples = scratch->traceParams.samples;
						context->currentShadingState->scratch.traceParams.samples = 1;
						tex->lookup(color,D0,D1,D2,D3,context);
						context->currentShadingState->scratch.traceParams.samples = savedSamples;
						
						addvv(irradiance,color);
						movvv(hemisphere->irradiance,color);
					} else{
						initv(hemisphere->irradiance,0);
					}
				}

				hemisphere->depth			=	ray.t;
				hemisphere->invDepth		=	1 / ray.t;

				if (tmp > horizonCutoff)	rMean =	min(rMean,ray.t);
				
				movvv(hemisphere->dir,ray.dir);

				assert(hemisphere->invDepth > 0);
			}
		}
	} else {

		// We're shading for indirectdiffuse
		context->numIndirectDiffuseRays	+=	numSamples;
		context->numIndirectDiffuseSamples++;

		for (i=0;i<nt;i++) {
			for (j=0;j<np;j++,hemisphere++) {
				float rv[2];
				context->random2d.get(rv);
				
				float		tmp			=	sqrtf((i+context->urand()) / (float) nt);
				const float	phi			=	(float) (2*C_PI*(j+context->urand()) / (float) np);
				const float	cosPhi		=	(cosf(phi)*tmp);
				const float	sinPhi		=	(sinf(phi)*tmp);

				tmp						=	sqrtf(1 - tmp*tmp);

				ray.dir[0]				=	X[0]*cosPhi + Y[0]*sinPhi + N[0]*tmp;
				ray.dir[1]				=	X[1]*cosPhi + Y[1]*sinPhi + N[1]*tmp;
				ray.dir[2]				=	X[2]*cosPhi + Y[2]*sinPhi + N[2]*tmp;

				const float originJitterX = (rv[0] - 0.5f)*scratch->traceParams.sampleBase;
				const float originJitterY = (rv[1] - 0.5f)*scratch->traceParams.sampleBase;
				
				ray.from[COMP_X]		=	P[COMP_X] + originJitterX*dPdu[0] + originJitterY*dPdv[0];
				ray.from[COMP_Y]		=	P[COMP_Y] + originJitterX*dPdu[1] + originJitterY*dPdv[1];
				ray.from[COMP_Z]		=	P[COMP_Z] + originJitterX*dPdu[2] + originJitterY*dPdv[2];

				ray.flags				=	ATTRIBUTES_FLAGS_DIFFUSE_VISIBLE;
				ray.tmin				=	scratch->traceParams.bias;
				ray.t					=	scratch->traceParams.maxDist;
				ray.time				=	0;
				ray.da					=	da;
				ray.db					=	db;

				// Transform the ray into the right coordinate system
				mulmp(ray.from,from,ray.from);
				mulmv(ray.dir,from,ray.dir);

				context->trace(&ray);

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
						if (tmp > scratch->occlusionParams.maxBrightness)	mulvf(C,scratch->occlusionParams.maxBrightness/tmp);
						
						mulvv(C,attributes->surfaceColor);
						addvv(irradiance,C);
						movvv(hemisphere->irradiance,C);

						context->numIndirectDiffusePhotonmapLookups++;
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
					if(scratch->occlusionParams.environment != NULL){
						CEnvironment *tex = scratch->occlusionParams.environment;
						vector D0,D1,D2,D3;
						vector color;

						// GSHTODO: Add in the dCosPhi and dSinPhi
						movvv(D0,ray.dir);
						movvv(D1,ray.dir);
						movvv(D2,ray.dir);
						movvv(D3,ray.dir);
						
						float savedSamples = scratch->traceParams.samples;
						context->currentShadingState->scratch.traceParams.samples = 1;
						tex->lookup(color,D0,D1,D2,D3,context);
						context->currentShadingState->scratch.traceParams.samples = savedSamples;
						
						addvv(irradiance,color);
						movvv(hemisphere->irradiance,color);
					} else{
						movvv(hemisphere->irradiance,scratch->occlusionParams.environmentColor);
						addvv(irradiance,scratch->occlusionParams.environmentColor);
					}
				}

				hemisphere->depth			=	ray.t;
				hemisphere->invDepth		=	1 / ray.t;

				if (tmp > horizonCutoff)	rMean =	min(rMean,ray.t);

				movvv(hemisphere->dir,ray.dir);

				assert(hemisphere->invDepth > 0);
			}
		}
	}
	hemisphere				-=	np*nt;
	
	// Normalize
	const float	tmp			=	1 / (float) numSamples;
	coverage				*=	tmp;
	mulvf(irradiance,tmp);
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
	if ((scratch->occlusionParams.maxError != 0) && (coverage < 1-C_EPSILON)) {

		// We're modifying, lock the thing
		osLock(mutex);
		
		// Create the sample
		cSample					=	(CCacheSample *) memory->alloc(sizeof(CCacheSample));

		// Compute the gradients of the illumination
		posGradient(cSample->gP,np,nt,hemisphere,X,Y);
		rotGradient(cSample->gR,np,nt,hemisphere,X,Y);
		
		// Compute the radius of validity
		rMean					*=	0.5f;

		// Clamp the radius of validity
		rMean					=	min(rMean,db*scratch->occlusionParams.maxPixelDist);
		
		// Record the data (in the target coordinate system)
		movvv(cSample->P,P);
		movvv(cSample->N,N);
		cSample->dP				=	rMean;
		cSample->coverage		=	coverage;
		movvv(cSample->envdir,envdir);
		movvv(cSample->irradiance,irradiance);
		
		// Do the neighbour clamping trick
		clamp(cSample);
		rMean	=	cSample->dP;	// copy dP back so we get the right place in the octree
		
		// The error multiplier
		const float		K		=	0.4f / scratch->occlusionParams.maxError;
		rMean					/=	K;
		
		// Insert the new sample into the cache
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
						nNode->center[i]	=	cNode->center[i] + cNode->side*0.25f;
					} else {
						nNode->center[i]	=	cNode->center[i] - cNode->side*0.25f;
					}
				}

				cNode->children[j]	=	nNode;
				nNode->side			=	cNode->side*0.5f;
				nNode->samples		=	NULL;
				for (i=0;i<8;i++)	nNode->children[i]	=	NULL;
			}

			cNode			=	cNode->children[j];
		}

		cSample->next	=	cNode->samples;
		cNode->samples	=	cSample;
		maxDepth		=	max(depth,maxDepth);

		osUnlock(mutex);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CIrradianceCache
// Method				:	clamp
// Description			:	Clamp the radius
// Return Value			:
// Comments				:
void		CIrradianceCache::clamp(CCacheSample *nSample) {
	CCacheSample	*cSample;
	CCacheNode		*cNode;
	CCacheNode		**stackBase		=	(CCacheNode **)	alloca(maxDepth*sizeof(CCacheNode *)*8);
	CCacheNode		**stack			=	stackBase;
	int				i;

	*stack++	=	root;
	while(stack > stackBase) {
		cNode	=	*(--stack);

		// Sum the values in this level
		for (cSample=cNode->samples;cSample!=NULL;cSample=cSample->next) {
			vector	D;

			subvv(D,cSample->P,nSample->P);
			//const float	l	=	lengthv(D);
			// Avoid issues with coincident points
			const float 	l	= 	(dotvv(D,D) > C_EPSILON) ? lengthv(D) : C_EPSILON;

			nSample->dP		=	min(nSample->dP,cSample->dP + l);
			cSample->dP		=	min(cSample->dP,nSample->dP + l);
		}

		// Check the children
		for (i=0;i<8;i++) {
			CCacheNode	*tNode;

			if ((tNode = cNode->children[i]) != NULL) {
				const float	tSide	=	tNode->side*4;

				if (	((tNode->center[0] + tSide) > nSample->P[0])	&&
						((tNode->center[1] + tSide) > nSample->P[1])	&&
						((tNode->center[2] + tSide) > nSample->P[2])	&&
						((tNode->center[0] - tSide) < nSample->P[0])	&&
						((tNode->center[1] - tSide) < nSample->P[1])	&&
						((tNode->center[2] - tSide) < nSample->P[2])) {
					*stack++	=	tNode;
				}
			}
		}
	}
}



///////////////////////////////////////////////////////////////////////
// Class				:	CIrradianceCache
// Method				:	draw
// Description			:	Draw the irradiance cache
// Return Value			:
// Comments				:
void		CIrradianceCache::draw() {
	CCacheSample		*cSample;
	CCacheNode			*cNode;
	CCacheNode			**stackBase		=	(CCacheNode **)	alloca(maxDepth*sizeof(CCacheNode *)*8);
	CCacheNode			**stack;
	int					i,j;
	float				P[chunkSize*3];
	float				C[chunkSize*3];
	float				N[chunkSize*3];
	float				dP[chunkSize];
	float				*cP,*cC,*cN,*cdP;

	j			=	chunkSize;
	cP			=	P;
	cC			=	C;
	cN			=	N;
	cdP			=	dP;
	stack		=	stackBase;
	*stack++	=	root;
	while(stack > stackBase) {
		cNode	=	*(--stack);

		// Sum the values in this level
		for (cSample=cNode->samples;cSample!=NULL;cSample=cSample->next,j--,cP+=3,cN+=3,cdP++,cC+=3) {
			if (j == 0)	{
				if (drawDiscs)		drawDisks(chunkSize,P,dP,N,C);
				else			 	drawPoints(chunkSize,P,C);
				cP	=	P;
				cC	=	C;
				cN	=	N;
				cdP	=	dP;
				j	=	chunkSize;
			}

			movvv(cP,cSample->P);
			movvv(cN,cSample->N);
			*cdP		=	cSample->dP;
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

	if (j != chunkSize) {
		if (drawDiscs)		drawDisks(chunkSize-j,P,dP,N,C);
		else			 	drawPoints(chunkSize-j,P,C);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CIrradianceCache
// Method				:	keyDown
// Description			:	handle keypresses
// Return Value			:	-
// Comments				:
int			CIrradianceCache::keyDown(int key) {
	if ((key == 'd') || (key == 'D')) {
		drawDiscs = TRUE;
		return TRUE;
	} else if ((key == 'p') || (key == 'P')) {
		drawDiscs = FALSE;
		return TRUE;
	}

	return FALSE;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CIrradianceCache
// Method				:	bound
// Description			:	Bound the irradiance cache
// Return Value			:
// Comments				:
void		CIrradianceCache::bound(float *bmin,float *bmax) {
	assert(root != NULL);

	bmin[0]	=	root->center[0] - root->side*0.5f;
	bmin[1]	=	root->center[1] - root->side*0.5f;
	bmin[2]	=	root->center[2] - root->side*0.5f;

	bmax[0]	=	root->center[0] + root->side*0.5f;
	bmax[1]	=	root->center[1] + root->side*0.5f;
	bmax[2]	=	root->center[2] + root->side*0.5f;
}

