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
//  File				:	pl.h
//  Classes				:	
//  Description			:	Parameter list class
//
////////////////////////////////////////////////////////////////////////
#ifndef PL_H
#define PL_H

#include "common/global.h"
#include "rendererc.h"
#include "variable.h"
#include "xform.h"
#include "attributes.h"

const	unsigned int	PL_VARYING_TO_VERTEX	=	1;	// Force varying variables to be vertex
const	unsigned int	PL_VERTEX_TO_VARYING	=	2;	// Force vertex variables to be varying

///////////////////////////////////////////////////////////////////////
// Class				:	CVertexData
// Description			:	Holds vertex data
// Comments				:
// Date last edited		:	8/17/2003
class	CVertexData {
public:
							CVertexData();
							~CVertexData();

	void					attach()		{	refCount++;	}
	void					detach()		{	if (--refCount == 0)	delete this;	}

	void					dispatch(const float *,int,int,float **);

	int						refCount;				// The reference counter
	int						parameters;				// The parameters that the user attached (includes varying/uniform/facevarying parameters)
	char					numVariables;			// The number of vertex variables
	char					moving;					// TRUE if the vertices are moving
	short					vertexSize;				// Size of a vertex
	CVariable				**variables;			// The vertex variables
};


///////////////////////////////////////////////////////////////////////
// Class				:	CParameter
// Description			:	Encapsulates a parameter
// Comments				:
// Date last edited		:	8/17/2003
class	CParameter {
public:
							CParameter(CVariable *);
	virtual					~CParameter();


	virtual	void			dispatch(int,float **)			=	0;	// Dispatch the parameter
	virtual	void			dispatch(int,int,float **)		=	0;	// Dispatch the parameter
	virtual	CParameter		*clone(CAttributes *)			=	0;	// Clone the parameter

	CVariable				*variable;
	CParameter				*next;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CPlParameter
// Description			:	Encapsulates a parameter
// Comments				:
// Date last edited		:	8/17/2003
class CPlParameter {
public:
	CVariable				*variable;			// The variable
	EVariableClass			container;			// The container that the user specified
	int						numItems;			// The number of items in this class



							///////////////////////////////////////////////////////////////////////
							// Class				:	CPlParameter
							// Description			:	This function is used to obtain the variable to write to
							// Comments				:
							// Date last edited		:	5/28/2006
	float					*resolve(float **varying) const {
								if (variable->storage == STORAGE_GLOBAL)	return varying[variable->entry];
								else {
									float	*value	=	variable->value;
									variable->value	=	NULL;
									return value;
								}
							}
};

///////////////////////////////////////////////////////////////////////
// Class				:	CPl
// Description			:	Holds a parameter list
// Comments				:
// Date last edited		:	5/28/2006
class	CPl {
public:
							CPl(int,int,CPlParameter *,float *,float *d1 = NULL);
							~CPl();

	void					transform(CXform *,float *d=NULL);
	void					append(float *);
	CPl						*clone(CAttributes *);
	CPlParameter			*find(int,const float *&,const float *&);

	CVertexData				*vertexData();
	void					collect(int &,float *&,EVariableClass);

	CParameter				*uniform(int,CParameter *);
	CParameter				*varying(int,int,int,int,CParameter *);
	CParameter				*varying(float *,float *,float *,float *,CParameter *);
	CParameter				*varying(int,int,CParameter *);
	CParameter				*facevarying(int,int,int,int,CParameter *);
	CParameter				*facevarying(int,int,int,CParameter *);
	CParameter				*facevarying(float *,float *,float *,float *,CParameter *);
	unsigned int			parameterUsage();

	float					*data0,*data1;			// Data
	int						dataSize;				// Size of the data
	int						numParameters;			// Number of parameters
	CPlParameter			*parameters;			// Parameters
};

CPl		*parseParameterList(int numUniform,int numVertex,int numVarying,int numFaceVarying,int numParams,char **params,void **vals,char *required,int flags,CAttributes *attributes);

#endif





