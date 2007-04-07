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
//  File				:	pointHierarchy.h
//  Classes				:
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef POINTHIERARCHY_H
#define POINTHIERARCHY_H

#include "common/global.h"
#include "common/containers.h"
#include "map.h"
#include "texture3d.h"
#include "options.h"
#include "pointCloud.h"
#include "mapHierarchy.h"

///////////////////////////////////////////////////////////////////////
// Class				:	CPointHierarchy
// Description			:	A hierarchy of points
// Comments				:
class	CPointHierarchy : public CTexture3d, public CMapHierarchy<CPointCloudPoint> {
public:
							CPointHierarchy(const char *,const float *from,const float *to,FILE *);
							~CPointHierarchy();

	void					store(const float *,const float *,const float *,float);
	void					lookup(float *,const float *,const float *,float);

protected:
	CArray<float>			data;				// This is where we actually keep the data

	void					draw() { }
	void					bound(float *bmin,float *bmax) { }

	void					write();

							// Overwritten from CMapHierarchy class to perform averaging of the points
	void					average(CPointCloudPoint *dest,int numItems,int *indices) {

								dest->dP	=	0;
								for (int i=0;i<numItems;i++) {
									dest->dP	+=	items[indices[i]].dP;
								}
								dest->dP	/=	(float) numItems;
							}
};

#endif






