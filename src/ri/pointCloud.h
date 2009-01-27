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
//  File				:	pointCloud.h
//  Classes				:
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef POINTCLOUD_H
#define POINTCLOUD_H

#include "common/global.h"
#include "common/containers.h"
#include "map.h"
#include "texture3d.h"
#include "options.h"


///////////////////////////////////////////////////////////////////////
// Class				:	CPointCloudPoint
// Description			:	A point cloud point
// Comments				:
class	CPointCloudPoint : public CMapItem {
public:
	float					dP;				// The sample radius
	int						entryNumber;	// The index to find the associated data in the "data" array
};

///////////////////////////////////////////////////////////////////////
// Class				:	CPointCloud
// Description			:	A collection of points
// Comments				:
class	CPointCloud : public CTexture3d, public CMap<CPointCloudPoint> {
public:
							CPointCloud(const char *name,const float *from,const float *to,const float *toNDC,const char*,int);
							CPointCloud(const char *name,const float *from,const float *to,const float *toNDC,int,char **,char **,int);
							CPointCloud(const char *name,const float *from,const float *to,FILE *);
							~CPointCloud();

							// Misc interface
	void					reset();
	void					write();
	void					balance();

							// Store/Lookup interface
	void					store(const float *,const float *,const float *,float);
	void					lookup(float *,const float *,const float *,float);
	void					lookup(float *,const float *,const float *,const float *,const float *,CShadingContext *) {	assert(FALSE);	}

							// CView interface for drawing
	void					draw();
	int						keyDown(int);
	void					bound(float *bmin,float *bmax);
	
							// ptcApi interface
	int						getNumPoints() { return numItems; }
	void					getPoint(int i,float *C,float *P,float *N,float *dP);

private:


							///////////////////////////////////////////////////////////////////////
							// Class				:	CPointLookup
							// Description			:	Extend the CLookup to include extra info
							// Comments				:
							class	CPointLookup : public CLookup {
							public:
								int				ignoreNormal;
							};
		
							///////////////////////////////////////////////////////////////////////
							// Class				:	CMap
							// Method				:	lookup
							// Description			:	Locate the nearest valid points
							// Return Value			:	Internally used
							// Comments				:
					void	lookup(CPointLookup *l,int index,const float scale) {
								const CPointCloudPoint	*photon	=	&items[index];
								float					d;
								vector					D;
								int						axis	=	photon->flags;

								if (index < numItemsh) {
									d	=	l->P[axis] - photon->P[axis];

									if (d > 0) {
										lookup(l,2*index+1,scale);

										if (d*d < l->distances[0]) {
											lookup(l,2*index,scale);
										}

									} else {
										lookup(l,2*index,scale);

										if (d*d < l->distances[0]) {
											lookup(l,2*index+1,scale);
										}
									}
								}

								subvv(D,photon->P,l->P);
								d	=	dotvv(D,D);
								const float t	=	dotvv(D,l->N);
								d	+=	t*t*16;


								// If the item is valid, insert it
								if (d < l->distances[0]) {
									if (d < (photon->dP*photon->dP*scale*scale)) {
									
										// Note that we do the opposite to photonmaps
										// only entries coherent with N contribute
										// but l.N is reversed...
										if ((dotvv(photon->N,l->N) < 0) || l->ignoreNormal) {
											insert(l,d,photon);
										}
									}
								}
							}
						
	CArray<float>			data;				// This is where we actually keep the data
	int						flush;				// Should this be written to disk?
	TMutex					mutex;				// To synchronize updates
	float					maxdP;
	
	static	int				drawDiscs;			// Which type to draw
	static	int				drawChannel;		// Which channel to draw
	
	friend			void	makeBrickMap(int n,const char **,const char *,TSearchpath *,int,const char **,const void **);
	
	friend class CRemotePtCloudChannel;
};

#endif //POINTCLOUD_H

