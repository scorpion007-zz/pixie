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
	void					lookup(float *,const float *,const float *,float,CShadingContext *,const CTexture3dLookup *) {	assert(FALSE);	}

							// CView interface for drawing
	void					draw();
	int						keyDown(int);
	void					bound(float *bmin,float *bmax);
	
							// ptcApi interface
	int						getNumPoints() { return numItems; }
	void					getPoint(int i,float *C,float *P,float *N,float *dP);

private:
	CArray<float>			data;				// This is where we actually keep the data
	int						flush;				// Should this be written to disk?
	TMutex					mutex;				// To synchronize updates
	
	static	int				drawDiscs;			// Which type to draw
	static	int				drawChannel;		// Which channel to draw
	
	friend			void	makeTexture3D(const char *,const char *,TSearchpath *,int,char **,void **);
	
	friend class CRemotePtCloudChannel;
};

#endif //POINTCLOUD_H

