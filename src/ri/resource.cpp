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
//  File				:	resource.cpp
//  Classes				:	CResource
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include "resource.h"


///////////////////////////////////////////////////////////////////////
// Class				:	CResource
// Method				:	CResource
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CResource::CResource(const char *name,CAttributes *attributes,CXform *xform) {
	this->name			=	strdup(name);
	this->attributes	=	new CAttributes(attributes);
	this->xform			=	new CXform(xform);
	next				=	NULL;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CResource
// Method				:	CResource
// Description			:	Ctor
// Return Value			:	-
// Comments				:
CResource::~CResource() {
	free(name);
	delete attributes;
	delete xform;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CResource
// Method				:	restore
// Description			:	Restore whatever that was saved in this resource
// Return Value			:	-
// Comments				:
void	CResource::restore(CAttributes *attributes,CXform *xform) {
}
