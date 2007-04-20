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
//  File				:	mapHierarchy.h
//  Classes				:	CMapHierarchy
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef MAPHIERARCHY_H
#define MAPHIERARCHY_H

#include "common/global.h"
#include "common/algebra.h"
#include "common/containers.h"
#include "renderer.h"
#include "map.h"
#include "shading.h"
#include "random.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CMapHierarchy
// Description			:	Encapsulates a map hierarchy
// Comments				:
template <class T>	class	CMapHierarchy : public CMap<T> {
protected:

	///////////////////////////////////////////////////////////////////////
	// Class				:	CMapNode
	// Description			:	Encapsulates a node
	// Comments				:
	class	CMapNode {
	public:
		vector		P,N;				// The center of the node
		float		dP,dN;				// The average radius and maximum normal deviation (cosine)
		int			child0,child1;		// The children indices (>=0 if internal nodes < if leaf)
	};

public:
						///////////////////////////////////////////////////////////////////////
						// Class				:	CMapHierarchy
						// Method				:	CMapHierarchy
						// Description			:	CTor
						// Return Value			:	-
						// Comments				:
						CMapHierarchy()	{
						}
						
						///////////////////////////////////////////////////////////////////////
						// Class				:	CMapHierarchy
						// Method				:	~CMapHierarchy
						// Description			:	DTor
						// Return Value			:	-
						// Comments				:
						~CMapHierarchy() {
						}


						///////////////////////////////////////////////////////////////////////
						// Class				:	CMap
						// Method				:	read
						// Description			:	Read the photonmap from a file
						// Return Value			:
						// Comments				:
	void				read(FILE *in) {

							// Read the map first
							CMap<T>::read(in);

							// Read the hierarchy next
							int	numNodes;
							fread(&numNodes,sizeof(int),1,in);
							nodes.reserve(numNodes);
							fread(nodes.array,sizeof(T),numNodes,in);
							nodes.numItems	=	numNodes;
						}

						///////////////////////////////////////////////////////////////////////
						// Class				:	CMap
						// Method				:	write
						// Description			:	Append the photon map into a file
						// Return Value			:
						// Comments				:
	void				write(FILE *out) {
							assert(nodes.numItems > 0);

							// Write the map first
							CMap<T>::write(out);

							// Write the hierarchy next
							fwrite(&nodes.numItems,sizeof(int),1,out);
							fwrite(nodes.array,sizeof(T),nodes.numItems,out);
						}


						///////////////////////////////////////////////////////////////////////
						// Class				:	CMapHierarchy
						// Method				:	computeHierarchy
						// Description			:	Constructs a hierarchy of the stored items
						// Return Value			:	-
						// Comments				:
	void				computeHierarchy() {
			
							// Get the item pointers into a temporary array
							int	i;
							int	*tmp	=	new int[CMap<T>::numItems];
							
							for (i=1;i<=CMap<T>::numItems;i++)	tmp[i-1]	=	i;
		
							// Compute the map hierarchy
							int	root	=	cluster(CMap<T>::numItems,tmp);

							// Root is always the first item in the array
							assert(root == 0);

							// Ditch the temp memory
							delete [] tmp;
						}
	
						///////////////////////////////////////////////////////////////////////
						// Class				:	CMapHierarchy
						// Method				:	average
						// Description			:	Create an internal node by averaging the point data
						// Return Value			:	-
						// Comments				:
	int					average(int numItems,int *indices) {
							int			i;
							CMapNode	node;

							// PASS 1:	Average the position/normal
							initv(node.P,0);
							initv(node.N,0);
							for (i=0;i<numItems;i++) {
								const T	*item	=	CMap<T>::items + indices[i];
								addvv(node.P,item->P);
								addvv(node.N,item->N);
							}

							// Normalize the thing
							assert(numItems > 0);
							mulvf(node.P,1/(float) numItems);
							normalizev(node.N);

							// PASS 2:	Compute the maximum deviation
							node.dP		=	0;
							node.dN		=	1;
							for (i=0;i<numItems;i++) {
								vector	D;
								const T	*item	=	CMap<T>::items + indices[i];

								subvv(D,node.P,item->P);
								node.dP		+=	max((item->dP*item->dP*dotvv(node.N,item->N)),0);
								node.dN		=	min(node.dN,dotvv(node.N,item->N));
							}
							node.dP		=	sqrtf(node.dP);

							// Create the node
							nodes.push(node);
							return nodes.numItems - 1;
						}

protected:

	CArray<CMapNode>	nodes;					// This is where we keep the internal nodes


						///////////////////////////////////////////////////////////////////////
						// Class				:	CMapHierarchy
						// Method				:	average
						// Description			:	Average the extra data stored in the items
						// Return Value			:	-
						// Comments				:
	virtual	void		average(T *dest,int numItems,int *indices)	=	0;


						///////////////////////////////////////////////////////////////////////
						// Class				:	CMapHierarchy
						// Method				:	cluster
						// Description			:	Cluster the items
						// Return Value			:	-
						// Comments				:
	int					cluster(int numItems,int *indices) {

							assert(numItems > 0);

							if (numItems == 1) {
								// Create a leaf
								return -indices[0];

							} else if (numItems == 2) {
								// Easy case
								int			nodeIndex	=	average(numItems,indices);
								CMapNode	*node		=	nodes.array + nodeIndex;
								node->child0			=	-indices[0];
								node->child1			=	-indices[1];
								return nodeIndex;

							} else {
								
								// Allocate temp memory
								int	*membership,*subItems;
								
								// Use alloca if the allocation size is low enough
								if (numItems >= ALLOCA_MAX_ITEMS)	membership	=	new int[numItems*2];
								else								membership	=	(int *) alloca(numItems*2*sizeof(int));

								subItems	=	membership	+	numItems;

								int		i;
								vector	bmin,bmax;

								initv(bmin,C_INFINITY);
								initv(bmax,-C_INFINITY);
								
								// The membership is dummy
								for (i=0;i<numItems;i++) {
									membership[i]	=	-1;
									addBox(bmin,bmax,CMap<T>::items[indices[i]].P);
								}
								
								vector	C0,C1;		// The cluster centers
								vector	N0,N1;		// The cluster normals
								
								// Create random cluster centers
								initv(C0,	_urand()*(bmax[0]-bmin[0]) + bmin[0],
											_urand()*(bmax[1]-bmin[1]) + bmin[1],
											_urand()*(bmax[2]-bmin[2]) + bmin[2]);
								initv(C1,	_urand()*(bmax[0]-bmin[0]) + bmin[0],
											_urand()*(bmax[1]-bmin[1]) + bmin[1],
											_urand()*(bmax[2]-bmin[2]) + bmin[2]);

								// Create random cluster normals
								initv(N0,	_urand()*2-1,	_urand()*2-1,	_urand()*2-1);
								initv(N1,	_urand()*2-1,	_urand()*2-1,	_urand()*2-1);
								normalizevf(N0);
								normalizevf(N1);
								
								// Perform the clustering iterations
								int		num0,num1;
								int		iterations;
								for (iterations=0;iterations<5;iterations++) {

									int		changed	=	FALSE;
									vector	nC0,nC1;
									vector	nN0,nN1;

									// Clear the data
									initv(nC0,0);
									initv(nC1,0);
									num0	=	0;
									num1	=	0;
									
									for (i=0;i<numItems;i++) {
										vector	D;
										const	T	*cItem	=	CMap<T>::items + indices[i];
										
										// Compute the distance to the first cluster
										subvv(D,cItem->P,C0);
										const float d0	=	dotvv(D,D) / max(dotvv(N0,cItem->N),C_EPSILON);
										
										// Compute the distance to the second cluster
										subvv(D,cItem->P,C1);
										const float d1	=	dotvv(D,D) / max(dotvv(N1,cItem->N),C_EPSILON);;
										
										// Change the membership
										if (d0 < d1) {
											if (membership[i] != 0) {
												changed			=	TRUE;
												membership[i]	=	0;
											}

											addvv(nC0,cItem->P);
											addvv(nN0,cItem->N);
											num0++;
										} else {
											if (membership[i] != 1) {
												changed			=	TRUE;
												membership[i]	=	1;
											}

											addvv(nC1,cItem->P);
											addvv(nN1,cItem->N);
											num1++;
										}
									}
									
									if ((num0 == 0) || (num1 == 0)) {
										initv(C0,	_urand()*(bmax[0]-bmin[0]) + bmin[0],
													_urand()*(bmax[1]-bmin[1]) + bmin[1],
													_urand()*(bmax[2]-bmin[2]) + bmin[2]);
										initv(C1,	_urand()*(bmax[0]-bmin[0]) + bmin[0],
													_urand()*(bmax[1]-bmin[1]) + bmin[1],
													_urand()*(bmax[2]-bmin[2]) + bmin[2]);

										initv(N0,	_urand()*2-1,	_urand()*2-1,	_urand()*2-1);
										initv(N1,	_urand()*2-1,	_urand()*2-1,	_urand()*2-1);
										normalizevf(N0);
										normalizevf(N1);
									} else {

										if (changed == FALSE)	break;

										mulvf(C0,nC0,1 / (float) num0);
										mulvf(C1,nC1,1 / (float) num1);

										// Normalize the normal vectors
										normalizevf(N0,nN0);
										normalizevf(N1,nN1);
									}	
								}
								
								// Do we have a bad clustering?
								while (num0 == 0 || num1 == 0) {

									// Clustering failed - probably coincident points, make an arbitrary split
									num0 = num1 = 0;
									for (i=0;i<numItems;i++) {
										const int which = i & 1;
										if (which)	num1++;
										else		num0++;
										membership[i] = which;
									}
								}
								
								assert((num0 + num1) == numItems);

								int			nodeIndex	=	average(numItems,indices);
								
								// OK, split the items into two
								int	j;
								
								for (i=0,j=0;i<numItems;i++)	if (membership[i] == 0)	subItems[j++]	=	indices[i];
								assert(j == num0);
								int	child0	=	cluster(num0,subItems);
								
								for (i=0,j=0;i<numItems;i++)	if (membership[i] == 1)	subItems[j++]	=	indices[i];
								assert(j == num1);
								int	child1	=	cluster(num1,subItems);
								
								CMapNode *cNode	=	nodes.array + nodeIndex;
								cNode->child0	=	child0;
								cNode->child1	=	child1;

								// Reclaim the memory if applicable
								if (numItems >= ALLOCA_MAX_ITEMS)	delete [] membership;

								// Return the index of the node
								return nodeIndex;
							}
						}
					
};


void	testFunction(CShadingContext *);

#endif

