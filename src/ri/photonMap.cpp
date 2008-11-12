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
//  File				:	photonMap.cpp
//  Classes				:
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "photonMap.h"
#include "object.h"
#include "raytracer.h"
#include "tiffio.h"
#include "tiff.h"
#include "stats.h"
#include "memory.h"
#include "random.h"
#include "error.h"

// Precomputed conversion tables for the sin/cosine
const float		costheta[]	=	{	1.000000f,0.999925f,0.999699f,0.999322f,0.998795f,0.998118f,0.997290f,0.996313f,0.995185f,0.993907f,0.992480f,0.990903f,0.989177f,0.987301f,0.985278f,0.983105f,0.980785f,0.978317f,0.975702f,0.972940f,0.970031f,0.966976f,0.963776f,0.960431f,0.956940f,0.953306f,0.949528f,0.945607f,0.941544f,0.937339f,0.932993f,0.928506f,0.923880f,0.919114f,0.914210f,0.909168f,0.903989f,0.898674f,0.893224f,0.887640f,0.881921f,0.876070f,0.870087f,0.863973f,0.857729f,0.851355f,0.844854f,0.838225f,0.831470f,0.824589f,0.817585f,0.810457f,0.803208f,0.795837f,0.788346f,0.780737f,0.773010f,0.765167f,0.757209f,0.749136f,0.740951f,0.732654f,0.724247f,0.715731f,0.707107f,0.698376f,0.689541f,0.680601f,0.671559f,0.662416f,0.653173f,0.643832f,0.634393f,0.624859f,0.615232f,0.605511f,0.595699f,0.585798f,0.575808f,0.565732f,0.555570f,0.545325f,0.534998f,0.524590f,0.514103f,0.503538f,0.492898f,0.482184f,0.471397f,0.460539f,0.449611f,0.438616f,0.427555f,0.416430f,0.405241f,0.393992f,0.382683f,0.371317f,0.359895f,0.348419f,0.336890f,0.325310f,0.313682f,0.302006f,0.290285f,0.278520f,0.266713f,0.254866f,0.242980f,0.231058f,0.219101f,0.207111f,0.195090f,0.183040f,0.170962f,0.158858f,0.146730f,0.134581f,0.122411f,0.110222f,0.098017f,0.085797f,0.073565f,0.061321f,0.049068f,0.036807f,0.024541f,0.012272f,0.000000f,-0.012272f,-0.024541f,-0.036807f,-0.049068f,-0.061321f,-0.073565f,-0.085797f,-0.098017f,-0.110222f,-0.122411f,-0.134581f,-0.146730f,-0.158858f,-0.170962f,-0.183040f,-0.195090f,-0.207111f,-0.219101f,-0.231058f,-0.242980f,-0.254866f,-0.266713f,-0.278520f,-0.290285f,-0.302006f,-0.313682f,-0.325310f,-0.336890f,-0.348419f,-0.359895f,-0.371317f,-0.382683f,-0.393992f,-0.405241f,-0.416430f,-0.427555f,-0.438616f,-0.449611f,-0.460539f,-0.471397f,-0.482184f,-0.492898f,-0.503538f,-0.514103f,-0.524590f,-0.534998f,-0.545325f,-0.555570f,-0.565732f,-0.575808f,-0.585798f,-0.595699f,-0.605511f,-0.615232f,-0.624859f,-0.634393f,-0.643832f,-0.653173f,-0.662416f,-0.671559f,-0.680601f,-0.689541f,-0.698376f,-0.707107f,-0.715731f,-0.724247f,-0.732654f,-0.740951f,-0.749136f,-0.757209f,-0.765167f,-0.773010f,-0.780737f,-0.788346f,-0.795837f,-0.803208f,-0.810457f,-0.817585f,-0.824589f,-0.831470f,-0.838225f,-0.844854f,-0.851355f,-0.857729f,-0.863973f,-0.870087f,-0.876070f,-0.881921f,-0.887640f,-0.893224f,-0.898674f,-0.903989f,-0.909168f,-0.914210f,-0.919114f,-0.923880f,-0.928506f,-0.932993f,-0.937339f,-0.941544f,-0.945607f,-0.949528f,-0.953306f,-0.956940f,-0.960431f,-0.963776f,-0.966976f,-0.970031f,-0.972940f,-0.975702f,-0.978317f,-0.980785f,-0.983105f,-0.985278f,-0.987301f,-0.989177f,-0.990903f,-0.992480f,-0.993907f,-0.995185f,-0.996313f,-0.997290f,-0.998118f,-0.998795f,-0.999322f,-0.999699f,-0.999925f	};
const float		sintheta[]	=	{	0.000000f,0.012272f,0.024541f,0.036807f,0.049068f,0.061321f,0.073565f,0.085797f,0.098017f,0.110222f,0.122411f,0.134581f,0.146730f,0.158858f,0.170962f,0.183040f,0.195090f,0.207111f,0.219101f,0.231058f,0.242980f,0.254866f,0.266713f,0.278520f,0.290285f,0.302006f,0.313682f,0.325310f,0.336890f,0.348419f,0.359895f,0.371317f,0.382683f,0.393992f,0.405241f,0.416430f,0.427555f,0.438616f,0.449611f,0.460539f,0.471397f,0.482184f,0.492898f,0.503538f,0.514103f,0.524590f,0.534998f,0.545325f,0.555570f,0.565732f,0.575808f,0.585798f,0.595699f,0.605511f,0.615232f,0.624859f,0.634393f,0.643832f,0.653173f,0.662416f,0.671559f,0.680601f,0.689541f,0.698376f,0.707107f,0.715731f,0.724247f,0.732654f,0.740951f,0.749136f,0.757209f,0.765167f,0.773010f,0.780737f,0.788346f,0.795837f,0.803208f,0.810457f,0.817585f,0.824589f,0.831470f,0.838225f,0.844854f,0.851355f,0.857729f,0.863973f,0.870087f,0.876070f,0.881921f,0.887640f,0.893224f,0.898674f,0.903989f,0.909168f,0.914210f,0.919114f,0.923880f,0.928506f,0.932993f,0.937339f,0.941544f,0.945607f,0.949528f,0.953306f,0.956940f,0.960431f,0.963776f,0.966976f,0.970031f,0.972940f,0.975702f,0.978317f,0.980785f,0.983105f,0.985278f,0.987301f,0.989177f,0.990903f,0.992480f,0.993907f,0.995185f,0.996313f,0.997290f,0.998118f,0.998795f,0.999322f,0.999699f,0.999925f,1.000000f,0.999925f,0.999699f,0.999322f,0.998795f,0.998118f,0.997290f,0.996313f,0.995185f,0.993907f,0.992480f,0.990903f,0.989177f,0.987301f,0.985278f,0.983105f,0.980785f,0.978317f,0.975702f,0.972940f,0.970031f,0.966976f,0.963776f,0.960431f,0.956940f,0.953306f,0.949528f,0.945607f,0.941544f,0.937339f,0.932993f,0.928506f,0.923880f,0.919114f,0.914210f,0.909168f,0.903989f,0.898674f,0.893224f,0.887640f,0.881921f,0.876070f,0.870087f,0.863973f,0.857729f,0.851355f,0.844854f,0.838225f,0.831470f,0.824589f,0.817585f,0.810457f,0.803208f,0.795837f,0.788346f,0.780737f,0.773010f,0.765167f,0.757209f,0.749136f,0.740951f,0.732654f,0.724247f,0.715731f,0.707107f,0.698376f,0.689541f,0.680601f,0.671559f,0.662416f,0.653173f,0.643832f,0.634393f,0.624859f,0.615232f,0.605511f,0.595699f,0.585798f,0.575808f,0.565732f,0.555570f,0.545325f,0.534998f,0.524590f,0.514103f,0.503538f,0.492898f,0.482184f,0.471397f,0.460539f,0.449611f,0.438616f,0.427555f,0.416430f,0.405241f,0.393992f,0.382683f,0.371317f,0.359895f,0.348419f,0.336890f,0.325310f,0.313682f,0.302006f,0.290285f,0.278520f,0.266713f,0.254866f,0.242980f,0.231058f,0.219101f,0.207111f,0.195090f,0.183040f,0.170962f,0.158858f,0.146730f,0.134581f,0.122411f,0.110222f,0.098017f,0.085797f,0.073565f,0.061321f,0.049068f,0.036807f,0.024541f,0.012272f	};
const float		cosphi[]	=	{	1.000000f,0.999699f,0.998795f,0.997290f,0.995185f,0.992480f,0.989177f,0.985278f,0.980785f,0.975702f,0.970031f,0.963776f,0.956940f,0.949528f,0.941544f,0.932993f,0.923880f,0.914210f,0.903989f,0.893224f,0.881921f,0.870087f,0.857729f,0.844854f,0.831470f,0.817585f,0.803208f,0.788346f,0.773010f,0.757209f,0.740951f,0.724247f,0.707107f,0.689541f,0.671559f,0.653173f,0.634393f,0.615232f,0.595699f,0.575808f,0.555570f,0.534998f,0.514103f,0.492898f,0.471397f,0.449611f,0.427555f,0.405241f,0.382683f,0.359895f,0.336890f,0.313682f,0.290285f,0.266713f,0.242980f,0.219101f,0.195090f,0.170962f,0.146730f,0.122411f,0.098017f,0.073565f,0.049068f,0.024541f,0.000000f,-0.024541f,-0.049068f,-0.073565f,-0.098017f,-0.122411f,-0.146730f,-0.170962f,-0.195090f,-0.219101f,-0.242980f,-0.266713f,-0.290285f,-0.313682f,-0.336890f,-0.359895f,-0.382683f,-0.405241f,-0.427555f,-0.449611f,-0.471397f,-0.492898f,-0.514103f,-0.534998f,-0.555570f,-0.575808f,-0.595699f,-0.615232f,-0.634393f,-0.653173f,-0.671559f,-0.689541f,-0.707107f,-0.724247f,-0.740951f,-0.757209f,-0.773010f,-0.788346f,-0.803208f,-0.817585f,-0.831470f,-0.844854f,-0.857729f,-0.870087f,-0.881921f,-0.893224f,-0.903989f,-0.914210f,-0.923880f,-0.932993f,-0.941544f,-0.949528f,-0.956940f,-0.963776f,-0.970031f,-0.975702f,-0.980785f,-0.985278f,-0.989177f,-0.992480f,-0.995185f,-0.997290f,-0.998795f,-0.999699f,-1.000000f,-0.999699f,-0.998795f,-0.997290f,-0.995185f,-0.992480f,-0.989177f,-0.985278f,-0.980785f,-0.975702f,-0.970031f,-0.963776f,-0.956940f,-0.949528f,-0.941544f,-0.932993f,-0.923880f,-0.914210f,-0.903989f,-0.893224f,-0.881921f,-0.870087f,-0.857729f,-0.844854f,-0.831470f,-0.817585f,-0.803208f,-0.788346f,-0.773010f,-0.757209f,-0.740951f,-0.724247f,-0.707107f,-0.689541f,-0.671559f,-0.653173f,-0.634393f,-0.615232f,-0.595699f,-0.575808f,-0.555570f,-0.534998f,-0.514103f,-0.492898f,-0.471397f,-0.449611f,-0.427555f,-0.405241f,-0.382683f,-0.359895f,-0.336890f,-0.313682f,-0.290285f,-0.266713f,-0.242980f,-0.219101f,-0.195090f,-0.170962f,-0.146730f,-0.122411f,-0.098017f,-0.073565f,-0.049068f,-0.024541f,-0.000000f,0.024541f,0.049068f,0.073565f,0.098017f,0.122411f,0.146730f,0.170962f,0.195090f,0.219101f,0.242980f,0.266713f,0.290285f,0.313682f,0.336890f,0.359895f,0.382683f,0.405241f,0.427555f,0.449611f,0.471397f,0.492898f,0.514103f,0.534998f,0.555570f,0.575808f,0.595699f,0.615232f,0.634393f,0.653173f,0.671559f,0.689541f,0.707107f,0.724247f,0.740951f,0.757209f,0.773010f,0.788346f,0.803208f,0.817585f,0.831470f,0.844854f,0.857729f,0.870087f,0.881921f,0.893224f,0.903989f,0.914210f,0.923880f,0.932993f,0.941544f,0.949528f,0.956940f,0.963776f,0.970031f,0.975702f,0.980785f,0.985278f,0.989177f,0.992480f,0.995185f,0.997290f,0.998795f,0.999699f	};
const float		sinphi[]	=	{	0.000000f,0.024541f,0.049068f,0.073565f,0.098017f,0.122411f,0.146730f,0.170962f,0.195090f,0.219101f,0.242980f,0.266713f,0.290285f,0.313682f,0.336890f,0.359895f,0.382683f,0.405241f,0.427555f,0.449611f,0.471397f,0.492898f,0.514103f,0.534998f,0.555570f,0.575808f,0.595699f,0.615232f,0.634393f,0.653173f,0.671559f,0.689541f,0.707107f,0.724247f,0.740951f,0.757209f,0.773010f,0.788346f,0.803208f,0.817585f,0.831470f,0.844854f,0.857729f,0.870087f,0.881921f,0.893224f,0.903989f,0.914210f,0.923880f,0.932993f,0.941544f,0.949528f,0.956940f,0.963776f,0.970031f,0.975702f,0.980785f,0.985278f,0.989177f,0.992480f,0.995185f,0.997290f,0.998795f,0.999699f,1.000000f,0.999699f,0.998795f,0.997290f,0.995185f,0.992480f,0.989177f,0.985278f,0.980785f,0.975702f,0.970031f,0.963776f,0.956940f,0.949528f,0.941544f,0.932993f,0.923880f,0.914210f,0.903989f,0.893224f,0.881921f,0.870087f,0.857729f,0.844854f,0.831470f,0.817585f,0.803208f,0.788346f,0.773010f,0.757209f,0.740951f,0.724247f,0.707107f,0.689541f,0.671559f,0.653173f,0.634393f,0.615232f,0.595699f,0.575808f,0.555570f,0.534998f,0.514103f,0.492898f,0.471397f,0.449611f,0.427555f,0.405241f,0.382683f,0.359895f,0.336890f,0.313682f,0.290285f,0.266713f,0.242980f,0.219101f,0.195090f,0.170962f,0.146730f,0.122411f,0.098017f,0.073565f,0.049068f,0.024541f,0.000000f,-0.024541f,-0.049068f,-0.073565f,-0.098017f,-0.122411f,-0.146730f,-0.170962f,-0.195090f,-0.219101f,-0.242980f,-0.266713f,-0.290285f,-0.313682f,-0.336890f,-0.359895f,-0.382683f,-0.405241f,-0.427555f,-0.449611f,-0.471397f,-0.492898f,-0.514103f,-0.534998f,-0.555570f,-0.575808f,-0.595699f,-0.615232f,-0.634393f,-0.653173f,-0.671559f,-0.689541f,-0.707107f,-0.724247f,-0.740951f,-0.757209f,-0.773010f,-0.788346f,-0.803208f,-0.817585f,-0.831470f,-0.844854f,-0.857729f,-0.870087f,-0.881921f,-0.893224f,-0.903989f,-0.914210f,-0.923880f,-0.932993f,-0.941544f,-0.949528f,-0.956940f,-0.963776f,-0.970031f,-0.975702f,-0.980785f,-0.985278f,-0.989177f,-0.992480f,-0.995185f,-0.997290f,-0.998795f,-0.999699f,-1.000000f,-0.999699f,-0.998795f,-0.997290f,-0.995185f,-0.992480f,-0.989177f,-0.985278f,-0.980785f,-0.975702f,-0.970031f,-0.963776f,-0.956940f,-0.949528f,-0.941544f,-0.932993f,-0.923880f,-0.914210f,-0.903989f,-0.893224f,-0.881921f,-0.870087f,-0.857729f,-0.844854f,-0.831470f,-0.817585f,-0.803208f,-0.788346f,-0.773010f,-0.757209f,-0.740951f,-0.724247f,-0.707107f,-0.689541f,-0.671559f,-0.653173f,-0.634393f,-0.615232f,-0.595699f,-0.575808f,-0.555570f,-0.534998f,-0.514103f,-0.492898f,-0.471397f,-0.449611f,-0.427555f,-0.405241f,-0.382683f,-0.359895f,-0.336890f,-0.313682f,-0.290285f,-0.266713f,-0.242980f,-0.219101f,-0.195090f,-0.170962f,-0.146730f,-0.122411f,-0.098017f,-0.073565f,-0.049068f,-0.024541f	};

#define	PHOTON_CAUSTICS		1
#define	PHOTON_EXPLOSION	2
#define	PHOTON_POINT		4
#define	PHOTON_DISTANT		8
#define	PHOTON_AREA			16


///////////////////////////////////////////////////////////////////////
//
//
//	Regular Photon Mapping stuff
//
//
///////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMap
// Method				:	CPhotonMap
// Description			:	Ctor
// Return Value			:
// Comments				:
CPhotonMap::CPhotonMap(const char *n,FILE *in) : CMap<CPhoton>() , CFileResource(n) {

	#ifdef PHOTON_LOOKUP_CACHE
		root			=	NULL;
		maxDepth		=	1;
	#endif
	attach();	// Count the fileResource reference
	modifying		=	FALSE;
	maxPower		=	0;
	osCreateMutex(mutex);

	identitym(from);
	identitym(to);

	// Try to read the photonmap
	if (in != NULL) {
		matrix	fromWorld,toWorld;

		CMap<CPhoton>::read(in);

		// Read the transformation matrices
		fread(fromWorld,sizeof(matrix),1,in);
		fread(toWorld,sizeof(matrix),1,in);
		fread(&maxPower,sizeof(float),1,in);

		mulmm(to,fromWorld,CRenderer::toWorld);
		mulmm(from,CRenderer::fromWorld,toWorld);
		
		#ifdef PHOTON_LOOKUP_CACHE
			// Initialize the lookup octree
			root			=	new CPhotonNode;
			addvv(root->center,bmin,bmax);
			mulvf(root->center,1 / (float) 2);
			root->side		=	max(max(bmax[0]-bmin[0],bmax[1] - bmin[1]),bmax[2] - bmin[2]);
			root->samples	=	NULL;
			for (int i=0;i<8;i++) root->children[i]	=	NULL;
		#endif
	} else {
	
		// Make sure we have a root
		balance();
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMap
// Method				:	~CPhotonMap
// Description			:	Dtor
// Return Value			:
// Comments				:
CPhotonMap::~CPhotonMap() {
	#ifdef PHOTON_LOOKUP_CACHE
		if (root != NULL) {
			CPhotonNode		**stackBase	=	(CPhotonNode **)	alloca(maxDepth*sizeof(CPhotonNode *)*8);
			CPhotonNode		**stack;
			CPhotonNode		*cNode;
			CPhotonSample	*cSample;
			int			i;
	
			stack		=	stackBase;
			*stack++	=	root;
			while(stack > stackBase) {
				cNode	=	*(--stack);
	
				while((cSample=cNode->samples) != NULL) {
					cNode->samples	=	cSample->next;
					delete cSample;
				}
	
				for (i=0;i<8;i++) {
					if (cNode->children[i] != NULL) *stack++	=	cNode->children[i];
				}
	
				delete cNode;
			}
		}
	#endif

	osDeleteMutex(mutex);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMap
// Method				:	reset
// Description			:	Reset the photonmap
// Return Value			:
// Comments				:
void	CPhotonMap::reset() {
	CMap<CPhoton>::reset();
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMap
// Method				:	write
// Description			:	Write the photon map into a file
// Return Value			:
// Comments				:
void	CPhotonMap::write(const CXform *world) {
	// Note: write is multithread safe, though it will
	// only ever be called in a single-threaded state
	// we do this so it manages the modifying state properly
	
	if (modifying == TRUE) {
		// Flush the photonmap
		FILE		*out		=	ropen(name,"wb",filePhotonMap);
	
		if (out != NULL) {
	
			// Balance the map
			balance();
	
			// Write the map
			CMap<CPhoton>::write(out);
	
			// Write the matrices
			fwrite(CRenderer::fromWorld,sizeof(matrix),1,out);
			fwrite(CRenderer::toWorld,sizeof(matrix),1,out);
			maxPower	=	sqrtf(maxPower);
			fwrite(&maxPower,sizeof(float),1,out);
	
			fclose(out);
		} else {
			error(CODE_BADFILE,"Failed to open \"%s\" for writing\n",name);
		}
		
		// We are no longer modifying this map
		modifying = FALSE;
	}
}




#ifdef PHOTON_LOOKUP_CACHE

///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMap
// Method				:	lookup
// Description			:	Locate the nearest maxFoundPhoton photons
// Return Value			:
// Comments				:	
int		CPhotonMap::probe(float *C,const float *P,const float *N) {
	CPhotonNode			*cNode;
	CPhotonNode			**stackBase	=	(CPhotonNode **)	alloca(maxDepth*sizeof(CPhotonNode *)*8);
	CPhotonNode			**stack;
	CPhotonSample		*cSample;
	float				totalWeight	=	0;
	int					i;
	
	// Note: if word-stores are atomic, we don't need to lock when doing this
	
	if (root == NULL) return FALSE;

	stack			=	stackBase;
	*stack++		=	root;
	initv(C,0,0,0);
	while(stack > stackBase) {
		cNode	=	*(--stack);

		// Iterate over the samples
		for (cSample=cNode->samples;cSample!=NULL;cSample=cSample->next) {
			vector	D;
			float	d;
			
			subvv(D,cSample->P,P);

			d	=	dotvv(D,D);

			if (d < (cSample->dP*cSample->dP)) {
				d	=	sqrtf(d);
				d	+=	absf(dotvv(D,cSample->N))*16;

				if (dotvv(cSample->N,N) < 0) {
					// if N=0, this should not operate anything out.  verify
					d = C_INFINITY;
				}
			
				if (d < cSample->dP) {
					float	weight	=	1 - d / cSample->dP;

					totalWeight		+=	weight;
					C[0]			+=	cSample->C[0]*weight;
					C[1]			+=	cSample->C[1]*weight;
					C[2]			+=	cSample->C[2]*weight;
				}
			}
		}

		// Check the children
		for (i=0;i<8;i++) {
			CPhotonNode	*tNode	=	cNode->children[i];

			if (tNode != NULL) {
				const	float	tSide	=	tNode->side;

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

	if (totalWeight > 0) {
		mulvf(C,1 / totalWeight);
		return TRUE;
	}

	return FALSE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMap
// Method				:	insert
// Description			:	Insert a sample
// Return Value			:
// Comments				:	
void	CPhotonMap::insert(const float *C,const float *P,const float *N,float dP) {
	CPhotonSample	*cSample	=	new CPhotonSample;
	CPhotonNode		*cNode		=	root;
	int				depth		=	0;
	int				i,j;

	// lock the mutex so we're thread safe
	osLock(mutex);
	
	movvv(cSample->C,C);
	movvv(cSample->P,P);
	movvv(cSample->N,N);
	cSample->dP	=	dP;

	while(cNode->side > (2*dP)) {
		depth++;

		for (j=0,i=0;i<3;i++) {
			if (P[i] > cNode->center[i]) {
				j			|=	1 << i;
			}
		}

		if (cNode->children[j] == NULL)	{
			CPhotonNode	*nNode	=	(CPhotonNode *) new CPhotonNode;

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
	maxDepth		=	max(maxDepth,depth);
	
	// unlock the mutex
	osUnlock(mutex);
}

#endif

///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMap
// Method				:	lookup
// Description			:	Locate the nearest maxFoundPhoton photons
// Return Value			:
// Comments				:	Nl	must be normalized
//							Il	must be normalized
void	CPhotonMap::lookup(float *Cl,const float *Pl,const float *Nl,int maxFound) {
	int				numFound;
	const CPhoton	**indices	=	(const CPhoton **)	alloca((maxFound+1)*sizeof(CPhoton *)); 
	float			*distances	=	(float	*)			alloca((maxFound+1)*sizeof(float)); 
	CLookup			l;

	searchRadius		=	(sqrtf(maxFound*maxPower / 0.05f) / (float) C_PI)*0.5f;

	// Lookup the photonmap at the location of the photon
	distances[0]		=	searchRadius*searchRadius;
	l.maxFound			=	maxFound;
	l.numFound			=	0;
	mulmp(l.P,to,Pl);
	mulmn(l.N,from,Nl);
	l.gotHeap			=	FALSE;
	l.indices			=	indices;
	l.distances			=	distances;

	#ifdef PHOTON_LOOKUP_CACHE
	if (!probe(Cl,l.P,l.N)) {
	#endif
		CMap<CPhoton>::lookupWithN(&l,1);
	
		initv(Cl,0);
	
		if ((numFound = l.numFound) < 2)	return;
	
		// Accumulate the irradiance
		for (int i=1;i<=numFound;i++) {
			const	CPhoton	*p	=	indices[i];
			vector	I;
	
			assert(distances[i] <= distances[0]);
	
			itemToDir(I,p->theta,p->phi);
	
			if (dotvv(I,l.N) < 0) {
				addvv(Cl,p->C);
			}
		}
	
		// Normalize the result
		mulvf(Cl,(float) (1.0 / (C_PI*distances[0])));
	
	#ifdef PHOTON_LOOKUP_CACHE
		// Insert it into the probe 
		insert(Cl,l.P,l.N,sqrtf(distances[0])*(float) 0.2);
	}
	#endif
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMap
// Method				:	lookup
// Description			:	Locate the nearest maxFoundPhoton photons
// Return Value			:
// Comments				:	Nl	must be normalized
//							Il	must be normalized
void	CPhotonMap::lookup(float *Cl,const float *Pl,int maxFound) {
	int				numFound	=	0;
	const CPhoton	**indices	=	(const CPhoton **)	alloca((maxFound+1)*sizeof(CPhoton *)); 
	float			*distances	=	(float	*)			alloca((maxFound+1)*sizeof(float)); 
	CLookup			l;

	searchRadius		=	(sqrtf(maxFound*maxPower / 0.05f) / (float) C_PI)*0.5f;

	distances[0]		=	searchRadius*searchRadius;

	l.maxFound			=	maxFound;
	l.numFound			=	0;
	mulmp(l.P,to,Pl);
	initv(l.N,0,0,0);
	l.gotHeap			=	FALSE;
	l.indices			=	indices;
	l.distances			=	distances;

	#ifdef PHOTON_LOOKUP_CACHE
	if (!probe(Cl,l.P,l.N)) {
	#endif
		CMap<CPhoton>::lookup(&l,1);
	
		initv(Cl,0,0,0);
	
		if (l.numFound < 2)	return;
	
		numFound	=	l.numFound;
	
		for (int i=1;i<=numFound;i++) {
			const	CPhoton	*p	=	indices[i];
	
			assert(distances[i] <= distances[0]);
	
			addvv(Cl,p->C);
		}
		
		// Normalize the result
		mulvf(Cl,(float) (1.0 / (C_PI*distances[0])));
	
	#ifdef PHOTON_LOOKUP_CACHE
		// Insert it into the probe 
		insert(Cl,l.P,l.N,sqrtf(distances[0])*(float) 0.2);
	}
	#endif
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMap
// Method				:	balance
// Description			:	Balance the map
// Return Value			:
// Comments				:
void	CPhotonMap::balance() {
	// If we have no photons in the map, add a dummy one to avoid an if statement during the lookup
	if (numItems == 0) {
		vector	P		=	{0,0,0};
		vector	I		=	{0,0,1};
		CPhoton	*photon	=	CMap<CPhoton>::store(P,I);
		initv(photon->C,0,0,0);
	}

	CMap<CPhoton>::balance();
}



///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMap
// Method				:	store
// Description			:	Store a photon
// Return Value			:
// Comments				:
void	CPhotonMap::store(const float *P,const float *N,const float *I,const float *C) {

	osLock(mutex);
	CPhoton	*ton	=	CMap<CPhoton>::store(P,N);
	dirToItem(ton->theta,ton->phi,I);
	movvv(ton->C,C);
	maxPower	=	max(maxPower,dotvv(C,C));
	osUnlock(mutex);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMap
// Method				:	bound
// Description			:	Bound the data
// Return Value			:
// Comments				:
void	CPhotonMap::bound(float *bmin,float *bmax) {
	int	i;

	initv(bmin,C_INFINITY);
	initv(bmax,-C_INFINITY);

	for (i=1;i<numItems;i++)	addBox(bmin,bmax,items[i].P);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMap
// Method				:	draw
// Description			:	Draw the photonmap
// Return Value			:
// Comments				:
void	CPhotonMap::draw() {
	float		P[chunkSize*3];
	float		C[chunkSize*3];
	int			i,j;
	float		*cP	=	P;
	float		*cC	=	C;
	CPhoton		*cT	=	items+1;

	// Collect and dispatch the photons
	for (i=numItems-1,j=chunkSize;i>0;i--,cT++,cP+=3,cC+=3,j--) {
		if (j == 0)	{
			drawPoints(chunkSize,P,C);
			cP	=	P;
			cC	=	C;
			j	=	chunkSize;
		}

		float maxChannel	=	max(max(cT->C[0],cT->C[1]),cT->C[2]);
		
		movvv(cP,cT->P);
		mulvf(cC,cT->C,1 / maxChannel);
	}

	if (j != chunkSize)	drawPoints(chunkSize-j,P,C);
}

