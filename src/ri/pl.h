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
#include "refCounter.h"

const	unsigned int	PL_VARYING_TO_VERTEX	=	1;	// Force varying variables to be vertex
const	unsigned int	PL_VERTEX_TO_VARYING	=	2;	// Force vertex variables to be varying

///////////////////////////////////////////////////////////////////////
// Class				:	CVertexData
// Description			:	Holds vertex data
// Comments				:
class	CVertexData : public CRefCounter {
public:
							CVertexData();
							~CVertexData();

	void					dispatch(const float *,int,int,float **,float ***);

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
class	CParameter {
public:
							CParameter(CVariable *);
	virtual					~CParameter();


	virtual	void			dispatch(int,float **,float ***)		=	0;	// Dispatch the parameter
	virtual	void			dispatch(int,int,float **,float ***)	=	0;	// Dispatch the parameter
	virtual	CParameter		*clone(CAttributes *)					=	0;	// Clone the parameter

	CVariable				*variable;
	CParameter				*next;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CPlParameter
// Description			:	Encapsulates a parameter
// Comments				:
class CPlParameter {
public:
	CVariable				*variable;			// The variable
	int						numItems;			// The number of items in this class
	int						index;				// The index in the data array for this variable
	EVariableClass			container;			// The container that the user specified



							///////////////////////////////////////////////////////////////////////
							// Class				:	CPlParameter
							// Description			:	This function is used to obtain the variable to write to
							// Comments				:
	float					*resolve(float **varying,float ***locals) const {
								if (variable->storage == STORAGE_GLOBAL)		return varying[variable->entry];
								else if (locals[variable->accessor] != NULL)	return locals[variable->accessor][variable->entry];
								return NULL;
							}
};

///////////////////////////////////////////////////////////////////////
// Class				:	CPl
// Description			:	Holds a parameter list
// Comments				:
class	CPl {
public:
							CPl(int,int,CPlParameter *,float *,float *d1 = NULL);
							~CPl();

	void					transform(CXform *,float *d=NULL);
	void					append(float *);
	CPl						*clone(CAttributes *);
	CPlParameter			*find(int,const float *&,const float *&);

	CVertexData				*vertexData();
	void					collect(int &,float *&,EVariableClass,CMemPage *);

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

CPl		*parseParameterList(int numUniform,int numVertex,int numVarying,int numFaceVarying,int numParams,const char **params,const void **vals,const char *required,int flags,CAttributes *attributes);

#endif

