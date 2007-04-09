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
//  File				:	map.h
//  Classes				:	CMap
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef MAP_H
#define MAP_H

#include "common/global.h"
#include "common/algebra.h"
#include "common/os.h"

// Macros to pack/unpack directions
#define	dirToItem(theta__,phi__,D__)	{						\
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

#define	itemToDir(D__,theta__,phi__)	{						\
	D__[0]	=	sintheta[theta__]*cosphi[phi__];				\
	D__[1]	=	sintheta[theta__]*sinphi[phi__];				\
	D__[2]	=	costheta[theta__];								\
}


// Debug and build options
//#define PHOTON_DEBUG

// Some extern variables defined in photon.cpp
extern	const float				costheta[];
extern	const float				sintheta[];
extern	const float				cosphi[];
extern	const float				sinphi[];

///////////////////////////////////////////////////////////////////////
// Class				:	CMapItem
// Description			:	Holds a generic point
// Comments				:
class	CMapItem {
public:
	vector			P,N;		// Position and normal of the item
	short			flags;		// Item flags
};

///////////////////////////////////////////////////////////////////////
// Class				:	CMap
// Description			:	Holds a generic map
// Comments				:	A map stores spatial data
template <class T> class	CMap {
public:

				///////////////////////////////////////////////////////////////////////
				// Class				:	CMap
				// Method				:	CMap
				// Description			:	Ctor
				// Return Value			:
				// Comments				:
				CMap() {
					numItems	=	0;
					maxItems	=	0;
					items		=	NULL;
					stepSize	=	10000;
					initv(bmin,C_INFINITY,C_INFINITY,C_INFINITY);
					initv(bmax,-C_INFINITY,-C_INFINITY,-C_INFINITY);
				}

				///////////////////////////////////////////////////////////////////////
				// Class				:	CMap
				// Method				:	~CMap
				// Description			:	Dtor
				// Return Value			:
				// Comments				:
		virtual	~CMap() {
					if (items != NULL)	delete [] items;
				}

				///////////////////////////////////////////////////////////////////////
				// Class				:	CMap
				// Method				:	read
				// Description			:	Read the photonmap from a file
				// Return Value			:
				// Comments				:
		void	read(FILE *in) {
					fread(&numItems,sizeof(int),1,in);
					fread(&maxItems,sizeof(int),1,in);
					items		=	new T[maxItems+1];
					fread(items,sizeof(T),numItems+1,in);
					fread(bmin,sizeof(float),3,in);
					fread(bmax,sizeof(float),3,in);

					numItemsh			=	numItems >> 1;
				}

				///////////////////////////////////////////////////////////////////////
				// Class				:	CMap
				// Method				:	write
				// Description			:	Append the photon map into a file
				// Return Value			:
				// Comments				:
		void	write(FILE *out) {
					fwrite(&numItems,sizeof(int),1,out);
					fwrite(&maxItems,sizeof(int),1,out);
					fwrite(items,sizeof(T),numItems+1,out);
					fwrite(bmin,sizeof(float),3,out);
					fwrite(bmax,sizeof(float),3,out);
				}

				///////////////////////////////////////////////////////////////////////
				// Class				:	CMap
				// Method				:	reset
				// Description			:	Reset the photonmap
				// Return Value			:
				// Comments				:
		void	reset() {
					if (items != NULL)	delete items;

					numItems	=	0;
					maxItems	=	0;
					items		=	NULL;
					initv(bmin,C_INFINITY,C_INFINITY,C_INFINITY);
					initv(bmax,-C_INFINITY,-C_INFINITY,-C_INFINITY);
				}

				///////////////////////////////////////////////////////////////////////
				// Class				:	CMap
				// Method				:	store
				// Description			:	Store a photon
				// Return Value			:
				// Comments				:
		T		*store(const float *P,const float *N) {
					if (numItems < maxItems) {
						T	*photon	=	&items[++numItems];

						movvv(photon->P,P);
						movvv(photon->N,N);
						addBox(bmin,bmax,P);
						photon->flags	=	0;

						return	photon;
					} else {
						T	*newitems;

						maxItems	+=	stepSize;
						stepSize	*=	2;
						newitems	=	new T[maxItems+1];
						if (numItems > 0)		{
							memcpy(newitems,items,(numItems+1)*sizeof(T));
							delete [] items;
						}
						items		=	newitems;

						T	*photon	=	&items[++numItems];

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
		T		*store(const T *item) {
					if (numItems < maxItems) {
						T	*photon	=	&items[++numItems];

						photon[0]	=	item[0];
						addBox(bmin,bmax,item->P);

						return	photon;
					} else {
						T	*newitems;

						maxItems	+=	stepSize;
						stepSize	*=	2;
						newitems	=	new T[maxItems+1];
						if (numItems > 0)		{
							memcpy(newitems,items,(numItems+1)*sizeof(T));
							delete [] items;
						}
						items		=	newitems;

						T	*photon	=	&items[++numItems];

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
virtual	void	balance() {
					if (numItems == 0)	return;

					T	**ar1	=	new T*[numItems+1];
					T	**ar2	=	new T*[numItems+1];
					int	i;
					T	*finalitems;

					for (i=0;i<=numItems;i++) {
						ar2[i]	=	&items[i];
					}

					balance(ar1,ar2,1,1,numItems);

					delete [] ar2;

					finalitems		=	new T[numItems+1];
					for (i=1;i<=numItems;i++) {
						finalitems[i]	=	ar1[i][0];
					}

					delete [] ar1;
					delete [] items;
					maxItems			=	numItems;
					items				=	finalitems;
					numItemsh			=	numItems >> 1;
				}


	vector		bmin,bmax;
protected:

	class		CLookup {
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


#ifdef PHOTON_DEBUG
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
						// Description			:	Locate the nearest maxFoundPhoton items
						// Return Value			:	Internally used
						// Comments				:
				void	lookupWithN(CLookup *l,int index) {
							const T		*photon	=	&items[index];
							float		d,t;
							vector		D;
							int			axis	=	photon->flags;

							if (index < numItemsh) {
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
								insert(l,d,photon);
							}
						}

						///////////////////////////////////////////////////////////////////////
						// Class				:	CMap
						// Method				:	lookup
						// Description			:	Locate the nearest maxFoundPhoton items
						// Return Value			:	Internally used
						// Comments				:
				void	lookup(CLookup *l,int index) {
							const T		*photon	=	&items[index];
							float		d;
							vector		D;
							int			axis	=	photon->flags;

							if (index < numItemsh) {
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
								insert(l,d,photon);
							}
						}

						///////////////////////////////////////////////////////////////////////
						// Class				:	CMap
						// Method				:	insert
						// Description			:	Insert an item into the list of founf items
						// Return Value			:	Internally used
						// Comments				:
		void			insert(CLookup *l,const float d,const T *photon) {
							if (l->numFound < l->maxFound) {
								l->numFound++;
								l->distances[l->numFound]	=	d;
								l->indices[l->numFound]		=	photon;
							} else {
								int	j,parent;


								if (l->gotHeap == FALSE) {
									int		halfitems	=	l->numFound >> 1;
									int		k;
									float	dtmp;
									const T	*ptmp;

									for (k=halfitems;k>=1;k--) {
										parent	=	k;
										ptmp	=	l->indices[k];
										dtmp	=	l->distances[k];

										while(parent <= halfitems) {
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

		T				*items;
		int				numItems;
		int				maxItems;
		int				numItemsh;
		int				stepSize;
};




#endif



