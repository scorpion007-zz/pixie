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
		int			average;			// The average item index
		int			child0,child1;		// The children indices
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
							fread(&root,sizeof(int),1,in);
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
							assert(root > 0);
							assert(nodes.numItems > 0);

							// Write the map first
							CMap<T>::write(out);

							// Write the hierarchy next
							fwrite(&nodes.numItems,sizeof(int),1,out);
							fwrite(&root,sizeof(int),1,out);
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
							root	=	cluster(CMap<T>::numItems,tmp);
							assert(root == nodes.numItems-1);

							delete [] tmp;
						}
	
						///////////////////////////////////////////////////////////////////////
						// Class				:	CMapHierarchy
						// Method				:	average
						// Description			:	Average the items given by the indices
						// Return Value			:	-
						// Comments				:
	int					average(int numItems,int *indices) {
							int		i;
							vector	P,N;

							// Average the position/normal
							initv(P,0);
							initv(N,0);
							for (i=0;i<numItems;i++) {
								addvv(P,CMap<T>::items[indices[i]].P);
								addvv(N,CMap<T>::items[indices[i]].N);
							}

							// Normalize the thing
							mulvf(P,1/(float) numItems);
							normalizev(N);

							// Perform further averagining if necessary
							T	*newItem	=	CMap<T>::store(P,N);
							average(newItem,numItems,indices);

							return newItem - CMap<T>::items;
						}

protected:

	int					root;
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
								CMapNode	node;
								node.average	=	average(numItems,indices);
								node.child0		=	-indices[0];
								node.child1		=	-indices[1];
								nodes.push(node);
								return nodes.numItems - 1;

							} else {
								
								// Allocate the memory
								int	*membership,*subItems;
								
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
								
								vector	C0,C1;
								
								// Create random cluster centers
								initv(C0,	_urand()*(bmax[0]-bmin[0]) + bmin[0],
											_urand()*(bmax[1]-bmin[1]) + bmin[1],
											_urand()*(bmax[2]-bmin[2]) + bmin[2]);
								initv(C1,	_urand()*(bmax[0]-bmin[0]) + bmin[0],
											_urand()*(bmax[1]-bmin[1]) + bmin[1],
											_urand()*(bmax[2]-bmin[2]) + bmin[2]);

								int		changed	=	FALSE;
								vector	nC0,nC1;
								int		num0,num1;
																		
								
								// Perform the clustering iterations
								int	iterations;
								for (iterations=0;iterations<5;iterations++) {

									// Clear the data
									initv(nC0,0);
									initv(nC1,0);
									num0	=	0;
									num1	=	0;
									
									for (i=0;i<numItems;i++) {
										vector	D;
										
										subvv(D,CMap<T>::items[indices[i]].P,C0);
										const float d0	=	dotvv(D,D);
										
										subvv(D,CMap<T>::items[indices[i]].P,C1);
										const float d1	=	dotvv(D,D);
										
										if (d0 < d1) {
											if (membership[i] != 0) {
												changed			=	TRUE;
												membership[i]	=	0;
											}

											addvv(nC0,CMap<T>::items[indices[i]].P);
											num0++;
										} else {
											if (membership[i] != 1) {
												changed			=	TRUE;
												membership[i]	=	1;
											}

											addvv(nC1,CMap<T>::items[indices[i]].P);
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

									} else {

										if (changed == FALSE)	break;

										mulvf(C0,nC0,1 / (float) num0);
										mulvf(C1,nC1,1 / (float) num1);
									}

									
								}
								
								while (num0 == 0 || num1 == 0) {
									// clustering failed - probably coincident points
									// make random spilt
									num0 = num1 = 0;
									for (i=0;i<numItems;i++) {
										const int which = _irand()%2;
										if (which)	num1++;
										else		num0++;
										membership[i] = which;
									}
								}
								
								assert((num0 + num1) == numItems);
								CMapNode	node;

								node.average	=	average(numItems,indices);
								
								// OK, split the items into two
								int	j;
								
								for (i=0,j=0;i<numItems;i++)	if (membership[i] == 0)	subItems[j++]	=	indices[i];
								assert(j == num0);
								node.child0	=	cluster(num0,subItems);
								
								for (i=0,j=0;i<numItems;i++)	if (membership[i] == 1)	subItems[j++]	=	indices[i];
								assert(j == num1);
								node.child1	=	cluster(num1,subItems);
								
								nodes.push(node);

								// Reclaim the memory if applicable
								if (numItems >= ALLOCA_MAX_ITEMS)	delete [] membership;

								return nodes.numItems-1;
							}
						}
					
};


void	testFunction(CShadingContext *);

#endif

