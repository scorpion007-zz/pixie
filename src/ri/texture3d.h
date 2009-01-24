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


class	CShadingContext;

///////////////////////////////////////////////////////////////////////
// Class				:	CTexture3d
// Description			:	Base class for 3d textures
// Comments				:
class	CTexture3d : public CFileResource, public CView {
protected:

	///////////////////////////////////////////////////////////////////////
	// Class				:	CChannel
	// Description			:	A 3d texture channel
	// Comments				:
	class	CChannel {
	public:
		char					name[64];		// Name of the channel
		int						numSamples;		// The size of channel sample
		int						sampleStart;	// Offset of the sample in the stack
		float					*fill;			// The sample defaults
		EVariableType			type;			// The funamental type
	};

public:
							CTexture3d(const char *name,const float *from,const float *to,const float *tondc=NULL,int numChannels=0,CChannel *channels=NULL);
	virtual					~CTexture3d();

							// For storing/querying data with radius
	virtual	void			lookup(float *,const float *,const float *,float)		= 0;	
	virtual	void			store(const float *,const float *,const float *,float)	= 0;

							// For irradiance cache type of queries
	virtual	void			lookup(float *,const float *,const float *,const float *,const float *,CShadingContext *)		= 0;

							// Resolve the names to channels
	void					resolve(int n,const char **names,int *entry,int *size);
	
							// ptcAPI interface
	void					queryChannels(int *,const char **,const char **);
	int						getDataSize()			{ return dataSize; }
	void					getFromMatrix(float *m) { movmm(m,from); }
	void					getToMatrix(float *m)	{ movmm(m,to); }
	void					getNDCMatrix(float *m)	{ movmm(m,toNDC); }

	int						dataSize;			// The size of each data sample
protected:
	void					defineChannels(const char *);
	void					defineChannels(int,char **,char **);
	void					writeChannels(FILE *);
	void					readChannels(FILE *);
	
	matrix					from,to;			// The transformation to the coordinate system
	matrix					toNDC;				// The viewing transform
	float					dPscale;			// The amount we need to scale dP by
	int						numChannels;		// Number of channels
	CChannel				*channels;			// List of channels
	
	friend class CRemotePtCloudChannel;
};


///////////////////////////////////////////////////////////////////////
// Function				:	texture3Dflatten
// Description			:	Flatten the channel datas into a vector
// Return Value			:	-
// Comments				:
inline	void	texture3Dflatten(float *dest,int n,const float **data,int *entry,int *size) {
	int	i;
	
	// For every channel
	for (i=0;i<n;i++) {
		const float	*src	=	*data++;
		
		// Unroll for the common cases
		switch (size[i]) {
		case 0:
			// This can happen if the channel was not found
			break;
		case 1:
			dest[entry[i]]		=	*src;
			break;
		case 2:
			dest[entry[i]]		=	*src++;
			dest[entry[i]+1]	=	*src;
			break;
		case 3:
			movvv(dest + entry[i],src);
			break;
		default:
			for (int j=0;j<size[i];j++) dest[entry[i]+j]	=	*src++;
			break;
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	texture3DflattenInterpolated
// Description			:	Flatten the channel datas into a vector
// Return Value			:	-
// Comments				:
inline	void	texture3DflattenInterpolated(float *dest,int n,const float **data,int *entry,int *size, int uVertices) {
	int	i;
		
	// For every channel
	for (i=0;i<n;i++) {
		const float	*src	=	*data++;
		
		// Unroll for the common cases
		switch (size[i]) {
		case 0:
			// This can happen if the channel was not found
			break;
		case 1:
			dest[entry[i]]		=	0.25f*(src[0] + src[1] + src[uVertices] + src[uVertices+1]);
			break;
		case 2:
			dest[entry[i]]		=	0.25f*(src[0] + src[1] + src[uVertices] + src[uVertices+1]);
			dest[entry[i]+1]	=	0.25f*(src[1] + src[2] + src[uVertices*2+1] + src[uVertices*2+2]);
			break;
		case 3:
			initv(dest + entry[i],0);
			addvv(dest + entry[i],src);
			addvv(dest + entry[i],src+3);
			addvv(dest + entry[i],src+uVertices*3);
			addvv(dest + entry[i],src+uVertices*3+3);
			mulvf(dest + entry[i],0.25f);
			break;
		default:
			for (int j=0;j<size[i];j++)	dest[entry[i]+j]	=	0;
			for (int j=0;j<size[i];j++) dest[entry[i]+j]	+=	src[j];
			for (int j=0;j<size[i];j++) dest[entry[i]+j]	+=	src[j+size[i]];
			for (int j=0;j<size[i];j++) dest[entry[i]+j]	+=	src[j+uVertices*size[i]];
			for (int j=0;j<size[i];j++) dest[entry[i]+j]	+=	src[j+uVertices*size[i]+size[i]];
			for (int j=0;j<size[i];j++)	dest[entry[i]+j]	*=	0.25f;
			break;
		}
	}
}
///////////////////////////////////////////////////////////////////////
// Function				:	texture3Dunpack
// Description			:	Unpack the data from a flat array
// Return Value			:	-
// Comments				:
inline	void	texture3Dunpack(const float *src,int n,float **data,int *entry,int *size) {
	int	i;
	
	// For every channel
	for (i=0;i<n;i++) {
		float	*dest	=	*data++;
		
		// Unroll for the common cases
		switch (size[i]) {
		case 0:
			// This can happen is the channel was not found
			break;
		case 1:
			*dest		=	src[entry[i]];
			break;
		case 2:
			dest[0]		=	src[entry[i]];
			dest[1]		=	src[entry[i]+1];
			break;
		case 3:
			movvv(dest,src + entry[i]);
			break;
		default:
			for (int j=0;j<size[i];j++) dest[j]	=	src[entry[i]+j];
			break;
		}
	}
}


#endif //TEXTURE3D_H

