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
//  File				:	gi.h
//  Classes				:	-
//  Description			:	The global illumination stuff
//
////////////////////////////////////////////////////////////////////////
#ifndef GI_H
#define GI_H

#include "common/global.h"
#include "common/algebra.h"
#include "common/containers.h"
#include "renderer.h"
#include "map.h"
#include "shading.h"


///////////////////////////////////////////////////////////////////////
// Class				:	CMapHierarchy
// Description			:	Encapsulates a map hierarchy
// Comments				:
template <class T>	class	CMapHierarchy : public CMap<T> {

	///////////////////////////////////////////////////////////////////////
	// Class				:	CMapNode
	// Description			:	Encapsulates a node
	// Comments				:
	class	CMapNode {
	public:
		T			*average;			// The average
		CMapNode	*child0,*child1;	// The children
	};

public:
					CMapHierarchy() {
					}
					
					~CMapHierarchy() {
					}

					// Compute the hierarchy
	void			computeHierarchy(CShadingContext *context) {
						memBegin(context->threadMemory);
	
						int	i;
											
						// Get the item pointers into an array
						T	**tmp	=	(T **) ralloc((CMap<T>::numItems-1)*sizeof(T *),context->threadMemory);
						for (i=1;i<CMap<T>::numItems;i++)	tmp[i-1]	=	CMap<T>::items + i;
	
						memEnd(context->threadMemory);
					}
	
					// The subclasses must overwrite this 
	virtual	T		*average(int numItems,T **items)	=	NULL;

private:

	// Cluster the items
	CMapNode		*cluster(int numItems,T **items,CShadingContext *context) {
						if (numItems == 1) {
							// Create a leaf
						} else if (numItems == 2) {
							// Easy case
							cluster(1,items);
							cluster(1,items+1);
						} else {
							// Perform clustering
							memBegin(context->threadMemory);
							
							// Allocate the memory
							int	*membership	=	(int *) ralloc(numItems*sizeof(int),context->threadMemory);
							int	i;
							
							vector	bmin,bmax;
							initv(bmin,C_INFINITY);
							initv(bmax,-C_INFINITY);
							
							// The membership is dummy
							for (i=0;i<numItems;i++) {
								membership[i]	=	-1;
								addBox(bmin,bmax,items[i]->P);
							}
							
							vector	C0,C1;
							
							// Create random cluster centers
							initv(C0,	context->urand()*(bmax[0]-bmin[0]) + bmin[0],
										context->urand()*(bmax[1]-bmin[1]) + bmin[1],
										context->urand()*(bmax[2]-bmin[2]) + bmin[2]);
							initv(C1,	context->urand()*(bmax[0]-bmin[0]) + bmin[0],
										context->urand()*(bmax[1]-bmin[1]) + bmin[1],
										context->urand()*(bmax[2]-bmin[2]) + bmin[2]);

							int		changed	=	FALSE;
							vector	nC0,nC1;
							int		num0,num1;
								
							// Clear the data
							num0	=	0;
							num1	=	0;
							initv(nC0,0);
							initv(nC1,0);
								
							
							// Perform the clustering iterations
							int	iterations;
							for (iterations=0;iterations<5;iterations++) {
								
								for (i=0;i<numItems;i++) {
									vector	D;
									
									subvv(D,items[i]->P,C0);
									const float d0	=	dotvv(D,D);
									
									subvv(D,items[i]->P,C1);
									const float d1	=	dotvv(D,D);
									
									if (d0 < d1) {
										if (membership[i] != 0) {
											changed	=	TRUE;
											addvv(nC0,items[i]->P);
											num0++;
										}
									} else {
										if (membership[i] != 1) {
											changed	=	TRUE;
											addvv(nC1,items[i]->P);
											num1++;
										}
									}
								}
								
								if ((num0 == 0) || (num1 == 0)) {
									initv(C0,	context->urand()*(bmax[0]-bmin[0]) + bmin[0],
												context->urand()*(bmax[1]-bmin[1]) + bmin[1],
												context->urand()*(bmax[2]-bmin[2]) + bmin[2]);
									initv(C1,	context->urand()*(bmax[0]-bmin[0]) + bmin[0],
												context->urand()*(bmax[1]-bmin[1]) + bmin[1],
												context->urand()*(bmax[2]-bmin[2]) + bmin[2]);

								} else {
									mulvf(C0,nC0,1 / (float) num0);
									mulvf(C1,nC1,1 / (float) num1);
									num0	=	0;
									num1	=	0;
								}
							}
							
							// OK, split the items into two
							T	**subItems	=	(T **) ralloc(max(num0,num1)*sizeof(T *),context->threadMemory);
							int	j;
							
							for (i=0,j=0;i<numItems;i++)	if (membership[i] == 0)	subItems[j++]	=	items[i];
							cluster(num0,subItems,context);
							
							for (i=0,j=0;i<numItems;i++)	if (membership[i] == 1)	subItems[j++]	=	items[i];
							cluster(num1,subItems,context);
							
							memEnd(context->threadMemory);
						}
					}
					
};


///////////////////////////////////////////////////////////////////////
// Class				:	CGI
// Description			:	This class is responsible for the global illumination
// Comments				:
class	CGI {
public:


	///////////////////////////////////////////////////////////////////////
	// Class				:	CPoint
	// Description			:	This holds a light or a gather point
	// Comments				:
	class	CPoint {
	public:
		vector		P,N,C;			// Position, Normal, Irradiance
	};

	///////////////////////////////////////////////////////////////////////
	// Class				:	CNode
	// Description			:	This holds a light/gather tree node
	// Comments				:
	class	CNode {
	public:
		int			front,back;
		int			representative;
	};







					CGI();
	virtual			~CGI();


	// The light and gather points
	CArray<CPoint>	lights;
	CArray<CPoint>	gathers;

	// The light and gather trees (the first entry is the root)
	CArray<CNode>	lightTree,gatherTree;
protected:
	void			cluster(CArray<CNode> &nodes,int numPoints,CPoint *points);
};


#endif

