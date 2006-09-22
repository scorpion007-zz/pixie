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
//  File				:	photonMap.h
//  Classes				:	CPhotonMap
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef PHOTONMAP_H
#define PHOTONMAP_H

#include "common/global.h"
#include "common/algebra.h"
#include "ray.h"
#include "renderer.h"
#include "output.h"
#include "opengl/opengl.h"


// Macros to pack/unpack directions
#define	dirToPhoton(theta__,phi__,D__)	{						\
	int		t__,p__;											\
	t__	=	(int) (acos(D__[2])*(256.0 / C_PI));				\
	p__	=	(int) (atan2(D__[1],D__[0])*(256.0 / (2.0*C_PI)));	\
	if (t__ > 255)												\
		theta__	=	(unsigned char) 255;						\
	else														\
		theta__	=	(unsigned char) t__;						\
																\
	if (p__ > 255)												\
		phi__		=	(unsigned char) 255;					\
	else if (p__ < 0)											\
		phi__		=	(unsigned char) (p__ + 256);			\
	else														\
		phi__		=	(unsigned char) p__;					\
}

#define	photonToDir(D__,theta__,phi__)	{						\
	D__[0]	=	sintheta[theta__]*cosphi[phi__];				\
	D__[1]	=	sintheta[theta__]*sinphi[phi__];				\
	D__[2]	=	costheta[theta__];								\
}


#define PDEBUG

// Some extern variables defined in photon.cpp
extern	int					inited;
extern	float				costheta[256];
extern	float				sintheta[256];
extern	float				cosphi[256];
extern	float				sinphi[256];

///////////////////////////////////////////////////////////////////////
// Class				:	CTon
// Description			:	Holds a generic particle
// Comments				:
// Date last edited		:	4/1/2002
class	CTon {
public:
	vector			P,N;		// Position and normal
	short			flags;		// Photon flags
};

///////////////////////////////////////////////////////////////////////
// Class				:	CMap
// Description			:	Holds a generic map
// Comments				:
// Date last edited		:	4/1/2002
template <class T> class	CMap {
public:

				///////////////////////////////////////////////////////////////////////
				// Class				:	CMap
				// Method				:	CMap
				// Description			:	Ctor
				// Return Value			:
				// Comments				:
				// Date last edited		:	4/1/2002
				CMap() {
					numPhotons	=	0;
					maxPhotons	=	0;
					photons		=	NULL;
					stepSize	=	10000;
					initv(bmin,C_INFINITY,C_INFINITY,C_INFINITY);
					initv(bmax,-C_INFINITY,-C_INFINITY,-C_INFINITY);

					if (inited == FALSE) {
						int	i;

						inited	=	TRUE;

						for (i=0;i<256;i++) {
							const double	angle	=	(double) i * (1.0 / 256.0) * C_PI;
							costheta[i]		=	(float) cos(angle);
							sintheta[i]		=	(float) sin(angle);
							cosphi[i]		=	(float) cos(2 * angle);
							sinphi[i]		=	(float) sin(2 * angle);
						}
					}
				}

				///////////////////////////////////////////////////////////////////////
				// Class				:	CMap
				// Method				:	~CMap
				// Description			:	Dtor
				// Return Value			:
				// Comments				:
				// Date last edited		:	4/1/2002
		virtual	~CMap() {
					if (photons != NULL)	delete [] photons;
				}

				///////////////////////////////////////////////////////////////////////
				// Class				:	CMap
				// Method				:	read
				// Description			:	Read the photonmap from a file
				// Return Value			:
				// Comments				:
				// Date last edited		:	9/10/2002
		void	read(FILE *in) {
					fread(&numPhotons,1,sizeof(int),in);
					fread(&maxPhotons,1,sizeof(int),in);
					photons		=	new T[maxPhotons+1];
					fread(photons,numPhotons+1,sizeof(T),in);
					fread(bmin,3,sizeof(float),in);
					fread(bmax,3,sizeof(float),in);

					numPhotonsh			=	numPhotons >> 1;
				}

				///////////////////////////////////////////////////////////////////////
				// Class				:	CMap
				// Method				:	write
				// Description			:	Append the photon map into a file
				// Return Value			:
				// Comments				:
				// Date last edited		:	9/10/2002
		void	write(FILE *out) {
					fwrite(&numPhotons,1,sizeof(int),out);
					fwrite(&maxPhotons,1,sizeof(int),out);
					fwrite(photons,numPhotons+1,sizeof(T),out);
					fwrite(bmin,3,sizeof(float),out);
					fwrite(bmax,3,sizeof(float),out);
				}

				///////////////////////////////////////////////////////////////////////
				// Class				:	CMap
				// Method				:	reset
				// Description			:	Reset the photonmap
				// Return Value			:
				// Comments				:
				// Date last edited		:	9/10/2002
		void	reset() {
					if (photons != NULL)	delete photons;

					numPhotons	=	0;
					maxPhotons	=	0;
					photons		=	NULL;
					initv(bmin,C_INFINITY,C_INFINITY,C_INFINITY);
					initv(bmax,-C_INFINITY,-C_INFINITY,-C_INFINITY);
				}

				///////////////////////////////////////////////////////////////////////
				// Class				:	CMap
				// Method				:	store
				// Description			:	Store a photon
				// Return Value			:
				// Comments				:
				// Date last edited		:	4/1/2002
		T		*store(const float *P,const float *N) {
					if (numPhotons < maxPhotons) {
						T	*photon	=	&photons[++numPhotons];

						movvv(photon->P,P);
						movvv(photon->N,N);
						addBox(bmin,bmax,P);
						photon->flags	=	0;

						return	photon;
					} else {
						T	*newPhotons;

						maxPhotons	+=	stepSize;
						stepSize	*=	2;
						newPhotons	=	new T[maxPhotons+1];
						if (numPhotons > 0)		{
							memcpy(newPhotons,photons,(numPhotons+1)*sizeof(T));
							delete [] photons;
						}
						photons		=	newPhotons;

						T	*photon	=	&photons[++numPhotons];

						movvv(photon->P,P);
						movvv(photon->N,N);
						addBox(bmin,bmax,P);
						photon->flags	=	0;

						return	photon;
					}
				}


				///////////////////////////////////////////////////////////////////////
				// Class				:	CMap
				// Method				:	store
				// Description			:	Store a photon
				// Return Value			:
				// Comments				:
				// Date last edited		:	4/1/2002
		T		*store(const T *item) {
					if (numPhotons < maxPhotons) {
						T	*photon	=	&photons[++numPhotons];

						photon[0]	=	item[0];
						addBox(bmin,bmax,item->P);

						return	photon;
					} else {
						T	*newPhotons;

						maxPhotons	+=	stepSize;
						stepSize	*=	2;
						newPhotons	=	new T[maxPhotons+1];
						if (numPhotons > 0)		{
							memcpy(newPhotons,photons,(numPhotons+1)*sizeof(T));
							delete [] photons;
						}
						photons		=	newPhotons;

						T	*photon	=	&photons[++numPhotons];

						photon[0]	=	item[0];
						addBox(bmin,bmax,item->P);

						return	photon;
					}
				}

				///////////////////////////////////////////////////////////////////////
				// Class				:	CMap
				// Method				:	balance
				// Description			:	Balance the map
				// Return Value			:	-
				// Comments				:	Must be called before the map is used
				// Date last edited		:	4/1/2002
	virtual	void	balance() {
				if (numPhotons == 0)	return;

				T	**ar1	=	new T*[numPhotons+1];
				T	**ar2	=	new T*[numPhotons+1];
				int	i;
				T	*finalPhotons;

				for (i=0;i<=numPhotons;i++) {
					ar2[i]	=	&photons[i];
				}

				balance(ar1,ar2,1,1,numPhotons);

				delete [] ar2;

				finalPhotons		=	new T[numPhotons+1];
				for (i=1;i<=numPhotons;i++) {
					finalPhotons[i]	=	ar1[i][0];
				}

				delete [] ar1;
				delete [] photons;
				maxPhotons			=	numPhotons;
				photons				=	finalPhotons;
				numPhotonsh			=	numPhotons >> 1;
			}


	vector	bmin,bmax;
protected:

	class	CLookup {
			public:
				int			maxFound;
				int			numFound;
				int			gotHeap;
				vector		P,N;
				float		*distances;
				const T		**indices;
			};

			///////////////////////////////////////////////////////////////////////
			// Class				:	CMap
			// Method				:	balance
			// Description			:	Balance a particular subset
			// Return Value			:	Internally used by balance
			// Comments				:
			// Date last edited		:	4/1/2002
	void	balance(T **ar1,T **ar2,int index,int start,int end) {
				int	median	=	1;

				while((4*median) <= (end-start+1))	median	+=	median;

				if ((3*median) <= (end-start+1)) {
					median	+=	median;
					median	+=	start-1;
				} else
					median	=	end-median+1;

				int	axis	=	2;
				if (((bmax[0] - bmin[0]) > (bmax[1] - bmin[1]))  && ((bmax[0] - bmin[0]) > (bmax[2] - bmin[2])))
					axis	=	0;
				else if ((bmax[1] - bmin[1]) > (bmax[2] - bmin[2]))
					axis	=	1;

				{
#define	swap(item1,item2)	{			\
	T		*tmp	=	ar2[item1];		\
	ar2[item1]		=	ar2[item2];		\
	ar2[item2]		=	tmp;			\
}

					int	left	=	start;
					int	right	=	end;

					while(right > left) {
						const	float	v	=	ar2[right]->P[axis];
						int				i	=	left-1;
						int				j	=	right;

						for(;;) {
							while(ar2[++i]->P[axis] < v);
							while((ar2[--j]->P[axis] > v) && (j>left));

							if (i >= j)	break;

							swap(i,j);
						}

						swap(i,right);
						if (i >= median)	right	=	i-1;
						if (i <= median)	left	=	i+1;
					}


#ifdef PDEBUG
					// FIXME: Remove
					int	i;
					for (i=start;i<median;i++) {
						assert(ar2[i]->P[axis] <= ar2[median]->P[axis]);
					}

					for (i=median+1;i<=end;i++) {
						assert(ar2[i]->P[axis] >= ar2[median]->P[axis]);
					}
					// FIXME: Remove
#endif

#undef swap
				}

				ar1[index]			=	ar2[median];
				ar1[index]->flags	=	(short) axis;

				if (median > start) {
					if (start < (median-1)) {
						const	float	tmp	=	bmax[axis];
						bmax[axis]			=	ar1[index]->P[axis];
						balance(ar1,ar2,2*index,start,median-1);
						bmax[axis]			=	tmp;
					} else {
						ar1[2*index]		=	ar2[start];
					}
				}

				if (median < end) {
					if ((median+1) < end) {
						const	float	tmp	=	bmin[axis];
						bmin[axis]			=	ar1[index]->P[axis];
						balance(ar1,ar2,2*index+1,median+1,end);
						bmin[axis]			=	tmp;
					} else {
						ar1[2*index+1]		=	ar2[end];
					}
				}
			}

public:


			///////////////////////////////////////////////////////////////////////
			// Class				:	CMap
			// Method				:	lookup
			// Description			:	Locate the nearest maxFoundPhoton photons
			// Return Value			:	Internally used
			// Comments				:
			// Date last edited		:	4/1/2002
	void	lookupWithN(CLookup *l,int index) {
				const T		*photon	=	&photons[index];
				float		d,t;
				vector		D;
				int			axis	=	photon->flags;

				if (index < numPhotonsh) {
					d	=	l->P[axis] - photon->P[axis];

					if (d > 0) {
						lookupWithN(l,2*index+1);

						if (d*d < l->distances[0]) {
							lookupWithN(l,2*index);
						}

					} else {
						lookupWithN(l,2*index);

						if (d*d < l->distances[0]) {
							lookupWithN(l,2*index+1);
						}
					}
				}

				subvv(D,photon->P,l->P);
				d	=	dotvv(D,D);
				t	=	dotvv(D,l->N);
				d	+=	t*t*16;

				if (d < l->distances[0]) {

					if (l->numFound < l->maxFound) {


						l->numFound++;
						l->distances[l->numFound]	=	d;
						l->indices[l->numFound]		=	photon;
					} else {
						int	j,parent;


						if (l->gotHeap == FALSE) {
							int		halfPhotons	=	l->numFound >> 1;
							int		k;
							float	dtmp;
							const T	*ptmp;

							for (k=halfPhotons;k>=1;k--) {
								parent	=	k;
								ptmp	=	l->indices[k];
								dtmp	=	l->distances[k];

								while(parent <= halfPhotons) {
									j	=	parent + parent;
									if ((j < l->numFound) && (l->distances[j] < l->distances[j+1])) j++;
									if (dtmp >= l->distances[j])	break;

									l->distances[parent]	=	l->distances[j];
									l->indices[parent]		=	l->indices[j];
									parent					=	j;
								}

								l->distances[parent]		=	dtmp;
								l->indices[parent]			=	ptmp;
							}

							l->gotHeap	=	TRUE;
						}


						for (parent=1,j=2;j<=l->numFound;) {
							if ((j < l->numFound) && (l->distances[j] < l->distances[j+1]))
								j++;

							if (d > l->distances[j]) break;

							l->distances[parent]	=	l->distances[j];
							l->indices[parent]		=	l->indices[j];
							parent	=	j;
							j		+=	j;
						}

						l->distances[parent]	=	d;
						l->indices[parent]		=	photon;
						assert(l->distances[1] <= l->distances[0]);
						l->distances[0]			=	l->distances[1];
					}
				}
			}

			///////////////////////////////////////////////////////////////////////
			// Class				:	CMap
			// Method				:	lookup
			// Description			:	Locate the nearest maxFoundPhoton photons
			// Return Value			:	Internally used
			// Comments				:
			// Date last edited		:	4/1/2002
	void	lookup(CLookup *l,int index) {
				const T		*photon	=	&photons[index];
				float		d;
				vector		D;
				int			axis	=	photon->flags;

				if (index < numPhotonsh) {
					d	=	l->P[axis] - photon->P[axis];

					if (d > 0) {
						lookup(l,2*index+1);

						if (d*d < l->distances[0]) {
							lookup(l,2*index);
						}

					} else {
						lookup(l,2*index);

						if (d*d < l->distances[0]) {
							lookup(l,2*index+1);
						}
					}
				}

				subvv(D,photon->P,l->P);
				d	=	dotvv(D,D);

				if (d < l->distances[0]) {

					if (l->numFound < l->maxFound) {


						l->numFound++;
						l->distances[l->numFound]	=	d;
						l->indices[l->numFound]		=	photon;
					} else {
						int	j,parent;


						if (l->gotHeap == FALSE) {
							int		halfPhotons	=	l->numFound >> 1;
							int		k;
							float	dtmp;
							const T	*ptmp;

							for (k=halfPhotons;k>=1;k--) {
								parent	=	k;
								ptmp	=	l->indices[k];
								dtmp	=	l->distances[k];

								while(parent <= halfPhotons) {
									j	=	parent + parent;
									if ((j < l->numFound) && (l->distances[j] < l->distances[j+1])) j++;
									if (dtmp >= l->distances[j])	break;

									l->distances[parent]	=	l->distances[j];
									l->indices[parent]		=	l->indices[j];
									parent					=	j;
								}

								l->distances[parent]		=	dtmp;
								l->indices[parent]			=	ptmp;
							}

							l->gotHeap	=	TRUE;
						}


						for (parent=1,j=2;j<=l->numFound;) {
							if ((j < l->numFound) && (l->distances[j] < l->distances[j+1]))
								j++;

							if (d > l->distances[j]) break;

							l->distances[parent]	=	l->distances[j];
							l->indices[parent]		=	l->indices[j];
							parent	=	j;
							j		+=	j;
						}

						l->distances[parent]	=	d;
						l->indices[parent]		=	photon;
						assert(l->distances[1] <= l->distances[0]);
						l->distances[0]			=	l->distances[1];
					}
				}
			}

		T				*photons;
		int				numPhotons;
		int				maxPhotons;
		int				numPhotonsh;
		int				stepSize;
};


















///////////////////////////////////////////////////////////////////////
//
//
//	Regular Photon Mapping stuff
//
//
///////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////
// Class				:	CPhoton
// Description			:	A Photon
// Comments				:
// Date last edited		:	4/1/2002
class	CPhoton : public CTon {
public:
	vector			C;				// The intensity
	unsigned char	theta,phi;		// Photon direction
};


///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonRay
// Description			:	A Photon
// Comments				:
// Date last edited		:	4/1/2002
class	CPhotonRay : public CRay {
public:
	vector			intensity;		// The intensity
	float			factor;			// The product of all the factors (used for routian roulette)
};

///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMap
// Description			:	A Photon map
// Comments				:
// Date last edited		:	3/11/2003
class	CPhotonMap : public CMap<CPhoton> , public CFileResource, public CView {

	class	CPhotonSample {
	public:
		vector			C,P,N;
		float			dP;
		CPhotonSample	*next;
	};

	class	CPhotonNode {
	public:
		vector			center;
		float			side;
		CPhotonSample	*samples;
		CPhotonNode		*children[8];
	};

public:
				CPhotonMap(const char *,const CXform *,FILE *);
				~CPhotonMap();

	void		attach()	{	refCount++;	}
	void		detach()	{	refCount--; if (refCount == 0) delete this; }
	void		check()		{	if (refCount == 0)	delete this;			}

	void		reset();
	void		write(const CXform *);

	int			probe(float *,const float *,const float *);
	void		insert(const float *,const float *,const float *,float);

	void		lookup(float *,const float *,int);
	void		lookup(float *,const float *,const float *,int);
	void		balance();

	void		store(const float *,const float *,const float *,const float *);

	void		draw();
	void		bound(float *bmin,float *bmax);

	CPhotonNode	*root;
	int			maxDepth;			// The maximum depth of the hierarchy
	int			refCount;
	int			modifying;
	matrix		toCamera,fromCamera;
	float		maxPower;			// The maximum photon power
	float		searchRadius;
};



#endif




