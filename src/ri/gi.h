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
//  File				:	gi.h
//  Classes				:	-
//  Description			:	The global illumination stuff
//
////////////////////////////////////////////////////////////////////////
#ifndef GI_H
#define GI_H

#include "common/global.h"
#include "common/containers.h"
#include "renderer.h"


///////////////////////////////////////////////////////////////////////
// Class				:	CGI
// Description			:	This class is responsible for the global illumination
// Comments				:
class	CGI {
public:


	///////////////////////////////////////////////////////////////////////
	// Class				:	CPoint
	// Description			:	This holds a light or a gather point
	// Comments				:
	class	CPoint {
	public:
		vector		P,N,C;			// Position, Normal, Irradiance
	};

	///////////////////////////////////////////////////////////////////////
	// Class				:	CNode
	// Description			:	This holds a light/gather tree node
	// Comments				:
	class	CNode {
	public:
		int			front,back;
		int			representative;
	};







					CGI();
	virtual			~CGI();


	// The light and gather points
	CArray<CPoint>	lights;
	CArray<CPoint>	gathers;

	// The light and gather trees (the first entry is the root)
	CArray<CNode>	lightTree,gatherTree;
protected:
	void			cluster(CArray<CNode> &nodes,int numPoints,CPoint *points);
};


#endif




