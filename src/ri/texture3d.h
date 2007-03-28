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
//  File				:	texture3d.h
//  Classes				:
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef TEXTURE3D_H
#define TEXTURE3D_H

#include "common/global.h"
#include "common/os.h"

#include "fileResource.h"
#include "rendererc.h"
#include "xform.h"

#include "gui/opengl.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CTexture3dChannel
// Description			:	A point cloud channel
// Comments				:
class	CTexture3dChannel {
public:
	char					name[64];		// Name of the channel
	int						numSamples;		// The size of channel sample
	int						sampleStart;	// Offset of the sample in the stack
	EVariableType			type;			// The funamental type
	float					*fill;			// The sample defaults
};

///////////////////////////////////////////////////////////////////////
// Class				:	CTexture3d
// Description			:	Base class for 3d textures
// Comments				:
class	CTexture3d : public CFileResource, public CView {
public:
							CTexture3d(const char *,const float *from,const float *to,const float *tondc=NULL,int numChannels=0,CTexture3dChannel *channels=NULL);
	virtual					~CTexture3d();

	virtual	void			lookup(float *,const float *,const float *,float) = 0;
	virtual	void			store(const float *,const float *,const float *,float) = 0;
	int						bindChannelNames(int&,const char **,CTexture3dChannel ***);
	void					prepareSample(float*,float **,CTexture3dChannel **);
	void					prepareInterpolatedSample(float*,float **,CTexture3dChannel **,int,int);
	void					unpackSample(float*,float **,CTexture3dChannel **);
	void					queryChannels(int *,char **,char **);
	
	// ptcAPI interface
	int						getDataSize()			{ return dataSize; }
	void					getFromMatrix(float *m) { movmm(m,from); }
	void					getToMatrix(float *m)	{ movmm(m,to); }
	void					getNDCMatrix(float *m)	{ movmm(m,toNDC); }

protected:
	void					defineChannels(const char *);
	void					defineChannels(int,char **,char **);
	void					writeChannels(FILE *);
	void					readChannels(FILE *);
	
	int						dataSize;			// The size of each data sample
	matrix					from,to;			// The transformation to the coordinate system
	matrix					toNDC;				// the viewing transform
	float					dPscale;			// The amount we need to scale dP by
	int						numChannels;		// Number of channels
	CTexture3dChannel		*channels;			// List of channels
	
	friend class CRemotePtCloudChannel;
};

#endif //TEXTURE3D_H

