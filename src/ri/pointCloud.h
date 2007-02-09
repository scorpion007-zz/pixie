//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright © 1999 - 2003, Okan Arikan
//
// Contact: okan@cs.utexas.edu
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
//  File				:	pointCloud.h
//  Classes				:
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef POINTCLOUD_H
#define POINTCLOUD_H

#include "common/global.h"
#include "common/containers.h"
#include "photonMap.h"
#include "texture3d.h"
#include "options.h"


///////////////////////////////////////////////////////////////////////
// Class				:	CPointCloudPoint
// Description			:	A point cloud point
// Comments				:
class	CPointCloudPoint : public CTon {
public:
	float			dP;				// The sample radius
	int				entryNumber;	// The index to find the associated data
};

///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMap
// Description			:	A Photon map
// Comments				:
class	CPointCloud : public CTexture3d, public CMap<CPointCloudPoint> {
public:
							CPointCloud(const char *,const float *from,const float *to,const char*,int);
							CPointCloud(const char *,const float *from,const float *to,FILE *);
							~CPointCloud();

	void					reset();
	void					write();

	void					balance();

	void					store(const float *,const float *,const float *,float);
	void					lookup(float *,const float *,const float *,float);

	void					draw();
	int						keyDown(int);
	
	void					bound(float *bmin,float *bmax);

private:
	CMemStack				*memory;			// Storage for the data
	CArray<float*>			*dataPointers;		// data pointers for each sample	
	int						flush;				// Should this be written to disk?
	float					searchRadius;
	
	TMutex					mutex;
	
	static	int				drawDiscs;					// Which type to draw
	
	friend			void	makeTexture3D(const char *,const char *,TSearchpath *,int,char **,void **);
	
	friend class CRemotePtCloudChannel;
};

#endif //POINTCLOUD_H

