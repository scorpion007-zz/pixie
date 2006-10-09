//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright � 1999 - 2003, Okan Arikan
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
//  File				:	pointCloud.h
//  Classes				:
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef POINTCLOUD_H
#define POINTCLOUD_H

#include "common/global.h"
#include "renderer.h"
#include "photonMap.h"
#include "texture3d.h"


///////////////////////////////////////////////////////////////////////
// Class				:	CPointCloudPoint
// Description			:	A point cloud point
// Comments				:
// Date last edited		:	4/1/2002
class	CPointCloudPoint : public CTon {
public:
	float			dP;				// The sample radius
	int				entryNumber;	// The index to find the associated data
};

///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMap
// Description			:	A Photon map
// Comments				:
// Date last edited		:	3/11/2003
class	CPointCloud : public CTexture3d, public CMap<CPointCloudPoint> {
public:
					CPointCloud(const char *,CXform *,const char*,int);
					CPointCloud(const char *,CXform *,FILE *);
					~CPointCloud();

	void			reset();
	void			write();

	void			balance();

	void			store(const float *,const float *,const float *,float);
	void			lookup(float *,const float *,const float *,float);

	void			draw();
	void			bound(float *bmin,float *bmax);

private:
	CMemStack		*memory;			// Storage for the data
	CArray<float*>	*dataPointers;		// data pointers for each sample	
	int				flush;				// Should this be written to disk?
	float			searchRadius;
	
	friend			void	makeTexture3D(const char *,const char *,TSearchpath *,int,char **,void **);
	
	friend class CRemotePtCloudChannel;
};

#endif //POINTCLOUD_H

