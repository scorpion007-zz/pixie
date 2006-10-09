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
//  File				:	texture3d.h
//  Classes				:
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef TEXTURE3D_H
#define TEXTURE3D_H

#include "common/global.h"
#include "fileResource.h"
#include "xform.h"
#include "gui/opengl.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CTexture3dChannel
// Description			:	A point cloud channel
// Comments				:
// Date last edited		:	4/1/2002
class	CTexture3dChannel {
public:
	char					name[64];		// Name of the channel
	int						numSamples;		// The size of channel sample
	int						sampleStart;	// Offset of the sample in the stack
	float					*fill;			// The sample defaults
};

///////////////////////////////////////////////////////////////////////
// Class				:	CTexture3d
// Description			:	Base class for 3d textures
// Comments				:
// Date last edited		:	4/1/2002
class	CTexture3d : public CFileResource, public CView {
public:
							CTexture3d(const char *,CXform *,int numChannels=0,CTexture3dChannel *channels=NULL);
	virtual					~CTexture3d();
	
	void					attach()	{	refCount++;	}
	void					detach()	{	refCount--; if (refCount == 0) delete this; }
	void					check()		{	if (refCount == 0)	delete this;			}
	
	virtual	void			lookup(float *,const float *,const float *,float) = 0;
	virtual	void			store(const float *,const float *,const float *,float) = 0;
	int						bindChannelNames(int&,const char **,CTexture3dChannel ***);
	void					prepareSample(float*,float **,CTexture3dChannel **);
	void					unpackSample(float*,float **,CTexture3dChannel **);

protected:
	void					defineChannels(const char *);
	void					writeChannels(FILE *);
	void					readChannels(FILE *);
	
	int						refCount;
	int						dataSize;			// The size of each data sample
	CTexture3dChannel		*channels;			// List of channels
	int						numChannels;
	CXform					*world;				// The world xform
	float					dPscale;			// The amount we need to scale dP by
	
	friend class CRemotePtCloudChannel;
};

#endif //TEXTURE3D_H
