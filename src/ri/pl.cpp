//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright � 1999 - 2003, Okan Arikan
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
//  File				:	pl.cpp
//  Classes				:	
//  Description			:	Parameter list class implementation
//
////////////////////////////////////////////////////////////////////////
#include <string.h>
#include <math.h>

#include "pl.h"
#include "stats.h"
#include "error.h"
#include "memory.h"
#include "renderer.h"



///////////////////////////////////////////////////////////////////////
// Class				:	CParameter
// Method				:	CParameter
// Description			:	Ctor
// Return Value			:
// Comments				:
CParameter::CParameter(CVariable *v) {
	stats.numParameters++;

	assert(v != NULL);

	variable	=	v;
	next		=	NULL;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CParameter
// Method				:	~CParameter
// Description			:	Dtor
// Return Value			:
// Comments				:
CParameter::~CParameter() {
	stats.numParameters--;

	if (next != NULL)	delete next;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CUniformParameter
// Description			:	Encapsulates a uniform parameter
// Comments				:
class	CUniformParameter : public CParameter {
public:
					CUniformParameter(CVariable *v) : CParameter(v) {
						data	=	NULL;
					}

					~CUniformParameter() {
						assert(data != NULL);

						delete [] data;
					}

	void			dispatch(int numVertices,float **varying,float ***locals) {
						float	*dest;

						if (variable->storage == STORAGE_GLOBAL)	dest	=	varying[variable->entry];
						else if (locals != NULL)					dest	=	locals[variable->accessor][variable->entry];
						else										dest	=	NULL;
						

						
						if (dest != NULL) {
							if ((variable->container == CONTAINER_UNIFORM) || (variable->container == CONTAINER_CONSTANT)) {
								memcpy(dest,data,variable->numFloats*sizeof(float));
							} else {
								// premote
								for (int i=0;i<numVertices;i++) {
									memcpy(dest,data,variable->numFloats*sizeof(float));
									dest += variable->numFloats;
								}
							}
						}

						if (next != NULL)	next->dispatch(numVertices,varying,locals);
					}

	void			dispatch(int start,int numVertices,float **varying,float ***locals) {
						float	*dest;

						if (variable->storage == STORAGE_GLOBAL)	dest	=	varying[variable->entry];
						else if (locals != NULL)					dest	=	locals[variable->accessor][variable->entry];
						else										dest	=	NULL;

						if (dest != NULL) {
							if ((variable->container == CONTAINER_UNIFORM) || (variable->container == CONTAINER_CONSTANT)) {
								memcpy(dest + start*variable->numFloats,data,variable->numFloats*sizeof(float));
							} else {
								// premote
								for (int i=0;i<numVertices;i++) {
									memcpy(dest,data,variable->numFloats*sizeof(float));
									dest += variable->numFloats;
								}
							}
						}

						if (next != NULL)	next->dispatch(start,numVertices,varying,locals);
					}

	CParameter		*clone(CAttributes *a) {
						CUniformParameter	*cUniform;
						
						if (variable->storage == STORAGE_GLOBAL)	cUniform	=	new CUniformParameter(variable);
						else										cUniform	=	new CUniformParameter(a->findParameter(variable->name));

						cUniform->data					=	new float[variable->numFloats];
						memcpy(cUniform->data,data,variable->numFloats*sizeof(float));

						if (next != NULL)	cUniform->next	=	next->clone(a);

						return cUniform;
					}

	float			*data;
};


///////////////////////////////////////////////////////////////////////
// Class				:	CUniformParameter
// Description			:	Encapsulates a varying parameter
// Comments				:
class	CVaryingParameter : public CParameter {
public:
					CVaryingParameter(CVariable *v) : CParameter(v) {
						data	=	NULL;
					}

					~CVaryingParameter() {
						delete [] data;
					}

	void			dispatch(int numVertices,float **varying,float ***locals) {
						float		*dest;

						if (variable->storage == STORAGE_GLOBAL)	dest	=	varying[variable->entry];
						else if (locals != NULL)					dest	=	locals[variable->accessor][variable->entry];
						else										dest	=	NULL;

						if (dest != NULL) {
							int			i,j;
							const int	numFloats	=	variable->numFloats;
							const float	*v0			=	data;
							const float	*v1			=	v0 + numFloats;
							const float	*v2			=	v1 + numFloats;
							const float	*v3			=	v2 + numFloats;
							const float	*u			=	varying[VARIABLE_U];
							const float	*v			=	varying[VARIABLE_V];

							for (i=numVertices;i>0;i--) {
								const float	cu	=	*u++;
								const float	cv	=	*v++;

								for (j=0;j<numFloats;j++) {
									*dest++	=	(v0[j]*(1-cu) + v1[j]*cu)*(1-cv) + (v2[j]*(1-cu) + v3[j]*cu)*cv;
								}
							}
						}

						if (next != NULL)	next->dispatch(numVertices,varying,locals);
					}

	void			dispatch(int start,int numVertices,float **varying,float ***locals) {
						float		*dest;

						if (variable->storage == STORAGE_GLOBAL)	dest	=	varying[variable->entry];
						else if (locals != NULL)					dest	=	locals[variable->accessor][variable->entry];
						else										dest	=	NULL;

						if (dest != NULL) {
							int			i,j;
							const int	numFloats	=	variable->numFloats;
							const float	*v0			=	data;
							const float	*v1			=	v0 + numFloats;
							const float	*v2			=	v1 + numFloats;
							const float	*v3			=	v2 + numFloats;
							const float	*u			=	varying[VARIABLE_U] + start;
							const float	*v			=	varying[VARIABLE_V] + start;

							dest					+=	start*numFloats;
							for (i=numVertices;i>0;i--) {
								const float	cu	=	*u++;
								const float	cv	=	*v++;

								for (j=0;j<numFloats;j++) {
									*dest++	=	(v0[j]*(1-cu) + v1[j]*cu)*(1-cv) + (v2[j]*(1-cu) + v3[j]*cu)*cv;
								}
							}
						}

						if (next != NULL)	next->dispatch(numVertices,varying,locals);
					}

	CParameter		*clone(CAttributes *a) {
						CVaryingParameter	*cVarying;
						
						if (variable->storage == STORAGE_GLOBAL)	cVarying	=	new CVaryingParameter(variable);
						else										cVarying	=	new CVaryingParameter(a->findParameter(variable->name));

						cVarying->data					=	new float[variable->numFloats*4];
						memcpy(cVarying->data,data,variable->numFloats*4*sizeof(float));

						if (next != NULL)	cVarying->next	=	next->clone(a);

						return cVarying;
					}

	float			*data;
};

///////////////////////////////////////////////////////////////////////
// Class				:	CUniformParameter
// Description			:	Encapsulates a varying parameter
// Comments				:
class	CVarying3Parameter : public CParameter {
public:
					CVarying3Parameter(CVariable *v) : CParameter(v) {
						data	=	NULL;
					}

					~CVarying3Parameter() {
						delete [] data;
					}

	void			dispatch(int numVertices,float **varying,float ***locals) {
						float		*dest;

						if (variable->storage == STORAGE_GLOBAL)	dest	=	varying[variable->entry];
						else if (locals != NULL)					dest	=	locals[variable->accessor][variable->entry];
						else										dest	=	NULL;

						if (dest != NULL) {
							int			i,j;
							const int	numFloats	=	variable->numFloats;
							const float	*v0			=	data;
							const float	*v1			=	v0 + numFloats;
							const float	*v2			=	v1 + numFloats;
							const float	*u			=	varying[VARIABLE_U];
							const float	*v			=	varying[VARIABLE_V];

							for (i=numVertices;i>0;i--) {
								const float	cu	=	*u++;
								const float	cv	=	*v++;

								for (j=0;j<numFloats;j++) {
									*dest++	=	v0[j]*(1-cu) + v1[j]*cu*cv + v2[j]*cu*(1-cv);
								}
							}	
						}

						if (next != NULL)	next->dispatch(numVertices,varying,locals);
					}

	void			dispatch(int start,int numVertices,float **varying,float ***locals) {
						float		*dest;

						if (variable->storage == STORAGE_GLOBAL)	dest	=	varying[variable->entry];
						else if (locals != NULL)					dest	=	locals[variable->accessor][variable->entry];
						else										dest	=	NULL;

						if (dest != NULL) {
							int			i,j;
							const int	numFloats	=	variable->numFloats;
							const float	*v0			=	data;
							const float	*v1			=	v0 + numFloats;
							const float	*v2			=	v1 + numFloats;
							const float	*u			=	varying[VARIABLE_U] + start;
							const float	*v			=	varying[VARIABLE_V] + start;

							dest					+=	start*numFloats;

							for (i=numVertices;i>0;i--) {
								const float	cu	=	*u++;
								const float	cv	=	*v++;

								for (j=0;j<numFloats;j++) {
									*dest++	=	v0[j]*(1-cu) + v1[j]*cu*cv + v2[j]*cu*(1-cv);
								}
							}
						}

						if (next != NULL)	next->dispatch(numVertices,varying,locals);
					}

	CParameter		*clone(CAttributes *a) {
						CVarying3Parameter	*cVarying;

						if (variable->storage == STORAGE_GLOBAL)	cVarying	=	new CVarying3Parameter(variable);
						else										cVarying	=	new CVarying3Parameter(a->findParameter(variable->name));

						cVarying->variable				=	variable;
						cVarying->data					=	new float[variable->numFloats*3];
						memcpy(cVarying->data,data,variable->numFloats*3*sizeof(float));

						if (next != NULL)	cVarying->next	=	next->clone(a);

						return cVarying;
					}

	float			*data;
};


///////////////////////////////////////////////////////////////////////
// Class				:	CVarying2Parameter
// Description			:	Encapsulates a varying parameter
// Comments				:
class	CVarying2Parameter : public CParameter {
public:
					CVarying2Parameter(CVariable *v) : CParameter(v) {
						data	=	NULL;
					}

					~CVarying2Parameter() {
						delete [] data;
					}

	void			dispatch(int numVertices,float **varying,float ***locals) {
						float		*dest;

						if (variable->storage == STORAGE_GLOBAL)	dest	=	varying[variable->entry];
						else if (locals != NULL)					dest	=	locals[variable->accessor][variable->entry];
						else										dest	=	NULL;

						if (dest != NULL) {
							int			i,j;
							const int	numFloats	=	variable->numFloats;
							const float	*v0			=	data;
							const float	*v1			=	v0 + numFloats;
							const float	*v			=	varying[VARIABLE_V];

							for (i=numVertices;i>0;i--) {
								const float	cv	=	*v++;

								for (j=0;j<numFloats;j++) {
									*dest++	=	v0[j]*(1-cv) + v1[j]*cv;
								}
							}
						}

						if (next != NULL)	next->dispatch(numVertices,varying,locals);
					}

	void			dispatch(int start,int numVertices,float **varying,float ***locals) {
						float		*dest;

						if (variable->storage == STORAGE_GLOBAL)	dest	=	varying[variable->entry];
						else if (locals != NULL)					dest	=	locals[variable->accessor][variable->entry];
						else										dest	=	NULL;
						
						if (dest != NULL) {
							int			i,j;
							const int	numFloats	=	variable->numFloats;
							const float	*v0			=	data;
							const float	*v1			=	v0 + numFloats;
							const float	*v			=	varying[VARIABLE_V] + start;

							dest					+=	start*numFloats;

							for (i=numVertices;i>0;i--) {
								const float	cv	=	*v++;

								for (j=0;j<numFloats;j++) {
									*dest++	=	v0[j]*(1-cv) + v1[j]*cv;
								}
							}
						}

						if (next != NULL)	next->dispatch(numVertices,varying,locals);
					}

	CParameter		*clone(CAttributes *a) {
						CVarying2Parameter	*cVarying;
						
						if (variable->storage == STORAGE_GLOBAL)	cVarying	=	new CVarying2Parameter(variable);
						else										cVarying	=	new CVarying2Parameter(a->findParameter(variable->name));

						cVarying->data					=	new float[variable->numFloats*2];
						memcpy(cVarying->data,data,variable->numFloats*2*sizeof(float));

						if (next != NULL)	cVarying->next	=	next->clone(a);

						return cVarying;
					}

	float			*data;
};










#define	dispatchData(__src,__dest,__size,__numFloats,__numVertices)				\
	int	__tmp,__tmp2;															\
	switch(__numFloats) {														\
		case 0:																	\
			break;																\
		case 1:																	\
			for (__tmp=__numVertices;__tmp>0;__tmp--,__src+=__size)				\
				*__dest++	=	*__src;											\
			break;																\
		case 2:																	\
			for (__tmp=__numVertices;__tmp>0;__tmp--,__src+=__size) {			\
				*__dest++	=	__src[0];										\
				*__dest++	=	__src[1];										\
			}																	\
			break;																\
		case 3:																	\
			for (__tmp=__numVertices;__tmp>0;__tmp--,__src+=__size) {			\
				*__dest++	=	__src[0];										\
				*__dest++	=	__src[1];										\
				*__dest++	=	__src[2];										\
			}																	\
			break;																\
		default:																\
			for (__tmp=__numVertices;__tmp>0;__tmp--,__src+=__size) {			\
				for (__tmp2=0;__tmp2<__numFloats;__tmp2++) {					\
					*__dest++	=	__src[__tmp2];								\
				}																\
			}																	\
			break;																\
		}



///////////////////////////////////////////////////////////////////////
// Class				:	CVertexData
// Method				:	CVertexData
// Description			:	Ctor
// Return Value			:
// Comments				:
CVertexData::CVertexData() {
	stats.numVertexDatas++;
	stats.gprimCoreMemory	+=	sizeof(CVertexData);

	refCount	=	0;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CVertexData
// Method				:	~CVertexData
// Description			:	Dtor
// Return Value			:
// Comments				:
CVertexData::~CVertexData() {
	stats.numVertexDatas--;
	stats.gprimCoreMemory	-=	(sizeof(CVertexData) + numVariables*sizeof(CVariable *));

	delete [] variables;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CVertexData
// Method				:	dispatch
// Description			:	Dispatch vertex data
// Return Value			:
// Comments				:
void	CVertexData::dispatch(const float *data,int start,int numVertices,float **varying,float ***locals) {
	int			i;
	CVariable	**dispatch	=	variables;

	for (i=numVariables;i>0;i--,dispatch++) {
		const int	numFloats	=	dispatch[0]->numFloats;
		const float	*src		=	data;
		float		*dest;

		if (dispatch[0]->storage == STORAGE_GLOBAL)	dest	=	varying[dispatch[0]->entry] + start*numFloats;
		else if (locals != NULL)					dest	=	locals[dispatch[0]->accessor][dispatch[0]->entry]  + start*numFloats;
		else										dest	=	NULL;

		if (dest != NULL) {
			dispatchData(src,dest,vertexSize,numFloats,numVertices);
		}

		data					+=	numFloats;
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPl
// Method				:	CPl
// Description			:	Ctor
// Return Value			:
// Comments				:
CPl::CPl(int dataSize,int numParameters,CPlParameter *p,float *d0,float *d1) {
	stats.numPls++;
	stats.gprimCoreMemory	+=	sizeof(CPl);

	this->dataSize			=	dataSize;
	this->numParameters		=	numParameters;
	this->parameters		=	p;
	this->data0				=	d0;
	this->data1				=	d1;

}

///////////////////////////////////////////////////////////////////////
// Class				:	CPl
// Method				:	~CPl
// Description			:	Dtor
// Return Value			:
// Comments				:
CPl::~CPl() {
	stats.numPls--;
	stats.gprimCoreMemory	-=	sizeof(CPl);

	if (parameters != NULL)	{
		delete [] parameters;
		stats.gprimCoreMemory	-=	numParameters*sizeof(CPlParameter);
	}

	if (data0 != NULL) {
		delete [] data0;
		stats.gprimCoreMemory	-=	dataSize*sizeof(float);
	}

	if (data1 != NULL) {
		delete [] data1;
		stats.gprimCoreMemory	-=	dataSize*sizeof(float);
	}
}



///////////////////////////////////////////////////////////////////////
// Class				:	CPl
// Method				:	append
// Description			:	Append another data block for the shutter close
// Return Value			:
// Comments				:
void		CPl::append(float *d) {
	if (data1 == NULL) {
		data1					=	new float[dataSize];
		stats.gprimCoreMemory	+=	dataSize*sizeof(float);
	}

	memcpy(data1,d,sizeof(float)*dataSize);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPl
// Method				:	transform
// Description			:	Transform the variables into another coordinaye system
// Return Value			:
// Comments				:
void		CPl::transform(CXform *x,float *cData) {
	if (cData == NULL) {
		if ((x->next != NULL) && (data1 == NULL)) {
			data1	=	new float[dataSize];
			memcpy(data1,data0,dataSize*sizeof(float));
			stats.gprimCoreMemory	+=	dataSize*sizeof(float);
		}

		if (data0 != NULL)	transform(x,data0);
		if (data1 != NULL)	transform(x,data1);
	} else {
		int					i,j;
		float				*src;
		const CPlParameter	*cPl	=	parameters;
		const float			*from,*to;

		if (x->next != NULL) {
			if (cData == data1) {
				from	=	x->next->from;
				to		=	x->next->to;
			} else {
				from	=	x->from;
				to		=	x->to;
			}
		} else {
			from	=	x->from;
			to		=	x->to;
		}

		for (i=numParameters;i>0;i--,cPl++) {
			const CVariable		*cVar	=	cPl->variable;

			switch(cVar->type) {
			case TYPE_FLOAT:
			case TYPE_COLOR:
				// No transformation is required
				break;
			case TYPE_VECTOR:
				// Vector transform
				for (src=cData,j=cPl->numItems;j>0;j--,src+=3) {
					mulmv(src,from,src);
				}
				break;
			case TYPE_NORMAL:
				// Vector transform
				for (src=cData,j=cPl->numItems;j>0;j--,src+=3) {
					mulmn(src,to,src);
				}
				break;
			case TYPE_POINT:
				// Vector transform
				for (src=cData,j=cPl->numItems;j>0;j--,src+=3) {
					mulmp(src,from,src);
				}
				break;
			case TYPE_MATRIX:
				break;
			case TYPE_QUAD:
				// Vector transform
				for (src=cData,j=cPl->numItems;j>0;j--,src+=4) {
					mulmp4(src,from,src);
				}
				break;
			case TYPE_DOUBLE:
			case TYPE_STRING:
			case TYPE_INTEGER:
			case TYPE_BOOLEAN:
				// No transformation is required
				break;
			}

			cData	+=	cPl->numItems*cVar->numFloats;
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPl
// Method				:	vertexData
// Description			:	Extract the vertex data from the parameter list
// Return Value			:
// Comments				:
CVertexData	*CPl::vertexData() {
	int			i,j;
	CVertexData	*vd	=	new CVertexData;
	int			vertexSize;
	int			param;

	// Count the number of vertices we have
	for (j=0,i=0;i<numParameters;i++) {
		if (parameters[i].container == CONTAINER_VERTEX) {
			j++;
		}
	}

	// Allocate the data
	assert(j < 256);
	vd->numVariables		=	(char) j;
	vd->variables			=	new CVariable*[j];
	stats.gprimCoreMemory	+=	j*sizeof(CVariable *);

	// Set the parameters
	vertexSize				=	0;
	param					=	0;
	for (j=0,i=0;i<numParameters;i++) {
		if (parameters[i].container == CONTAINER_VERTEX) {
			vd->variables[j++]	=	parameters[i].variable;
			vertexSize			+=	parameters[i].variable->numFloats;
		}

		param		|=	parameters[i].variable->usageMarker;
	}

	assert(vertexSize < 65536);

	vd->refCount	=	0;
	vd->vertexSize	=	(short) vertexSize;
	vd->parameters	=	param;
	vd->moving		=	(data1 == NULL ? FALSE : TRUE);

	return vd;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPl
// Method				:	vertexData
// Description			:	Extract the vertex data from the parameter list
// Return Value			:
// Comments				:
CPl				*CPl::clone(CAttributes *a) {
	float			*ndata0,*ndata1;
	CPlParameter	*nParameters;
	int				i;

	// Copy the data
	if (data0 != NULL) {
		stats.gprimCoreMemory	+=	dataSize*sizeof(float);

		ndata0	=	new float[dataSize];
		memcpy(ndata0,data0,dataSize*sizeof(float));
	} else {
		ndata0	=	NULL;
	}

	if (data1 != NULL) {
		stats.gprimCoreMemory	+=	dataSize*sizeof(float);

		ndata1	=	new float[dataSize];
		memcpy(ndata1,data1,dataSize*sizeof(float));
	} else {
		ndata1	=	NULL;
	}

	// Allocate a fresh copy of the parameters
	nParameters				=	new CPlParameter[numParameters];	
	memcpy(nParameters,parameters,numParameters*sizeof(CPlParameter));
	stats.gprimCoreMemory	+=	numParameters*sizeof(CPlParameter);

	// Re-link the variables to the latest attributes
	for (i=0;i<numParameters;i++) {
		if (nParameters[i].variable->storage != STORAGE_GLOBAL) {
			nParameters[i].variable	=	a->findParameter(nParameters[i].variable->name);
			assert(nParameters[i].variable != NULL);
		}
	}

	return new CPl(dataSize,numParameters,nParameters,ndata0,ndata1);
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPl
// Method				:	find
// Description			:	Find a variable in the parameter list
// Return Value			:
// Comments				:
CPlParameter	*CPl::find(int t,const float *&d0,const float *&d1) {
	int	i,disp;

	for (disp=0,i=0;i<numParameters;i++) {
		if (parameters[i].variable->entry == t)	{
			d0	=	data0	+	disp;
			d1	=	(data1 == NULL ? NULL : data1 + disp);
			return parameters+i;
		}

		disp	+=	parameters[i].numItems*parameters[i].variable->numFloats;
	}

	return NULL;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPl
// Method				:	vertices
// Description			:	Extract the vertex data
// Return Value			:
// Comments				:
void	CPl::collect(int &size,float *&data,EVariableClass container,CMemPage *page) {
	int			i,j,k;
	const float	*cData		=	data0;
	float		*oData;
	int			vs			=	0;
	int			numItems	=	0;

	for (i=0;i<numParameters;i++) {
		if (parameters[i].container == container) {
			vs			+=	parameters[i].variable->numFloats;
			numItems	=	parameters[i].numItems;
		}
	}

	if (data1 != NULL)	{
		size	=	vs*2;
	} else {
		size	=	vs;
	}

	if (vs == 0)		return;

	assert(numItems > 0);

	// Allocate the memory to keep things around
	if (data == NULL)	{
		assert(page != NULL);
		data	=	(float *) ralloc(size*numItems*sizeof(float),page);
	}

	oData	=	data;

	for (i=0;i<numParameters;i++) {
		const int	numFloats	=	parameters[i].variable->numFloats;

		if (parameters[i].container == container) {
			const float	*sData	=	cData;
			float		*dData	=	oData;

			for (j=parameters[i].numItems;j>0;j--,dData+=(size-numFloats)) {
				for (k=numFloats;k>0;k--)
					*dData++		=	*sData++;
			}

			oData	+=	numFloats;
		}

		cData	+=	parameters[i].numItems*numFloats;
	}

	if (data1 != NULL) {
		cData	=	data1;

		for (i=0;i<numParameters;i++) {
			const int	numFloats	=	parameters[i].variable->numFloats;

			if (parameters[i].container == container) {
				const float	*sData	=	cData;
				float		*dData	=	oData;

				for (j=parameters[i].numItems;j>0;j--,dData+=(size-numFloats)) {
					for (k=numFloats;k>0;k--)
						*dData++		=	*sData++;
				}

				oData	+=	numFloats;
			}

			cData	+=	parameters[i].numItems*numFloats;
		}
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPl
// Method				:	uniform
// Description			:	Extract the vertex data
// Return Value			:
// Comments				:
CParameter		*CPl::uniform(int u,CParameter *p) {
	int				i;
	const	float	*cData		=	data0;
	CPlParameter	*cParameter	=	parameters;

	for (i=numParameters;i>0;i--,cParameter++) {
		CVariable	*cVariable	=	cParameter->variable;
		const	int	numFloats	=	cVariable->numFloats;

		if (cParameter->container == CONTAINER_UNIFORM) {
			CUniformParameter	*np	=	new CUniformParameter(cVariable);

			np->data				=	new float[numFloats];
			memcpy(np->data,cData+u*numFloats,numFloats*sizeof(float));
			np->next				=	p;
			p						=	np;
		} else if (cParameter->container == CONTAINER_CONSTANT) {
			CUniformParameter	*np	=	new CUniformParameter(cVariable);

			np->variable			=	cVariable;
			np->data				=	new float[numFloats];
			memcpy(np->data,cData,numFloats*sizeof(float));
			np->next				=	p;
			p						=	np;
		}

		cData	+=	cParameter->numItems*numFloats;
	}

	return p;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPl
// Method				:	vertices
// Description			:	Extract the vertex data
// Return Value			:
// Comments				:
CParameter		*CPl::varying(int v0,int v1,int v2,int v3,CParameter *p) {
	int				i;
	const	float	*cData		=	data0;
	CPlParameter	*cParameter	=	parameters;

	for (i=numParameters;i>0;i--,cParameter++) {
		CVariable	*cVariable	=	cParameter->variable;
		const	int	numFloats	=	cVariable->numFloats;

		if (cParameter->container == CONTAINER_VARYING) {
			CVaryingParameter	*np	=	new CVaryingParameter(cVariable);

			np->data				=	new float[numFloats*4];
			memcpy(np->data+0*numFloats,cData+v0*numFloats,numFloats*sizeof(float));
			memcpy(np->data+1*numFloats,cData+v1*numFloats,numFloats*sizeof(float));
			memcpy(np->data+2*numFloats,cData+v2*numFloats,numFloats*sizeof(float));
			memcpy(np->data+3*numFloats,cData+v3*numFloats,numFloats*sizeof(float));
			np->next				=	p;
			p						=	np;
		}

		cData	+=	cParameter->numItems*numFloats;
	}

	return p;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPl
// Method				:	vertices
// Description			:	Extract the vertex data
// Return Value			:
// Comments				:
CParameter		*CPl::varying(int v0,int v1,CParameter *p) {
	int				i;
	const	float	*cData		=	data0;
	CPlParameter	*cParameter	=	parameters;

	for (i=numParameters;i>0;i--,cParameter++) {
		CVariable	*cVariable	=	cParameter->variable;
		const	int	numFloats	=	cVariable->numFloats;

		if (cParameter->container == CONTAINER_VARYING) {
			CVarying2Parameter	*np	=	new CVarying2Parameter(cVariable);

			np->data				=	new float[numFloats*2];
			memcpy(np->data+0*numFloats,cData+v0*numFloats,numFloats*sizeof(float));
			memcpy(np->data+1*numFloats,cData+v1*numFloats,numFloats*sizeof(float));
			np->next				=	p;
			p						=	np;
		}

		cData	+=	cParameter->numItems*numFloats;
	}

	return p;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPl
// Method				:	vertices
// Description			:	Extract the vertex data
// Return Value			:
// Comments				:
CParameter		*CPl::varying(float *v0,float *v1,float *v2,float *v3,CParameter *p) {
	int				i;
	CPlParameter	*cParameter	=	parameters;

	for (i=numParameters;i>0;i--,cParameter++) {
		CVariable	*cVariable	=	cParameter->variable;
		const	int	numFloats	=	cVariable->numFloats;

		if (cParameter->container == CONTAINER_VARYING) {
			CVaryingParameter	*np	=	new CVaryingParameter(cVariable);

			np->data				=	new float[numFloats*4];
			memcpy(np->data+0*numFloats,v0,numFloats*sizeof(float));
			memcpy(np->data+1*numFloats,v1,numFloats*sizeof(float));
			memcpy(np->data+2*numFloats,v2,numFloats*sizeof(float));
			memcpy(np->data+3*numFloats,v3,numFloats*sizeof(float));
			np->next				=	p;
			p						=	np;

			v0	+=	numFloats;
			v1	+=	numFloats;
			v2	+=	numFloats;
			v3	+=	numFloats;
		}
	}

	return p;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPl
// Method				:	vertices
// Description			:	Extract the vertex data
// Return Value			:
// Comments				:
CParameter		*CPl::facevarying(int v0,int v1,int v2,int v3,CParameter *p) {
	int				i;
	const	float	*cData		=	data0;
	CPlParameter	*cParameter	=	parameters;

	for (i=numParameters;i>0;i--,cParameter++) {
		CVariable	*cVariable	=	cParameter->variable;
		const	int	numFloats	=	cVariable->numFloats;

		if (cParameter->container == CONTAINER_FACEVARYING) {
			CVaryingParameter	*np	=	new CVaryingParameter(cVariable);

			np->data				=	new float[numFloats*4];
			memcpy(np->data+0*numFloats,cData+v0*numFloats,numFloats*sizeof(float));
			memcpy(np->data+1*numFloats,cData+v1*numFloats,numFloats*sizeof(float));
			memcpy(np->data+2*numFloats,cData+v2*numFloats,numFloats*sizeof(float));
			memcpy(np->data+3*numFloats,cData+v3*numFloats,numFloats*sizeof(float));
			np->next				=	p;
			p						=	np;
		}

		cData	+=	cParameter->numItems*numFloats;
	}

	return p;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPl
// Method				:	vertices
// Description			:	Extract the vertex data
// Return Value			:
// Comments				:
CParameter		*CPl::facevarying(float *v0,float *v1,float *v2,float *v3,CParameter *p) {
	int				i;
	CPlParameter	*cParameter	=	parameters;

	for (i=numParameters;i>0;i--,cParameter++) {
		CVariable	*cVariable	=	cParameter->variable;
		const	int	numFloats	=	cVariable->numFloats;

		if (cParameter->container == CONTAINER_FACEVARYING) {
			CVaryingParameter	*np	=	new CVaryingParameter(cVariable);

			np->data				=	new float[numFloats*4];
			memcpy(np->data+0*numFloats,v0,numFloats*sizeof(float));
			memcpy(np->data+1*numFloats,v1,numFloats*sizeof(float));
			memcpy(np->data+2*numFloats,v2,numFloats*sizeof(float));
			memcpy(np->data+3*numFloats,v3,numFloats*sizeof(float));
			np->next				=	p;
			p						=	np;

			v0	+=	numFloats;
			v1	+=	numFloats;
			v2	+=	numFloats;
			v3	+=	numFloats;
		}
	}

	return p;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CPl
// Method				:	vertices
// Description			:	Extract the vertex data
// Return Value			:
// Comments				:
CParameter		*CPl::facevarying(int v0,int v1,int v2,CParameter *p) {
	int				i;
	const	float	*cData		=	data0;
	CPlParameter	*cParameter	=	parameters;

	for (i=numParameters;i>0;i--,cParameter++) {
		CVariable	*cVariable	=	cParameter->variable;
		const	int	numFloats	=	cVariable->numFloats;

		if (cParameter->container == CONTAINER_FACEVARYING) {
			CVarying3Parameter	*np	=	new CVarying3Parameter(cVariable);

			np->data				=	new float[numFloats*3];
			memcpy(np->data+0*numFloats,cData+v0*numFloats,numFloats*sizeof(float));
			memcpy(np->data+1*numFloats,cData+v1*numFloats,numFloats*sizeof(float));
			memcpy(np->data+2*numFloats,cData+v2*numFloats,numFloats*sizeof(float));
			np->next				=	p;
			p						=	np;
		}

		cData	+=	cParameter->numItems*numFloats;
	}

	return p;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CPl
// Method				:	parameters
// Description			:	Extracts the parameters set by the list
// Return Value			:
// Comments				:
unsigned int CPl::parameterUsage() {
	unsigned int	p;
	int				i;

	for (p=0,i=0;i<numParameters;i++) {
		p	|=	parameters[i].variable->usageMarker;
	}

	return p;
}






///////////////////////////////////////////////////////////////////////
// Function				:	parseParameterList
// Description			:	Parse a parameter list
// Return Value			:	The parsed parameter list
// Comments				:
CPl		*parseParameterList(int numUniform,int numVertex,int numVarying,int numFaceVarying,int numParams,char **params,void **vals,char *required,int flags,CAttributes *attributes) {
	int					i,numDefinedParams = 0;
	CPlParameter		*parameters,*finalParameters;
	int					dataSize;
	float				*data;
	float				*cData;
	void				**paramvals;

	// Resolve the variables
	parameters		=	(CPlParameter *)	alloca(numParams*sizeof(CPlParameter));
	paramvals		=	(void**)			alloca(numParams*sizeof(void*));
	for (dataSize=0,i=0;i<numParams;i++) {
		CVariable		*cVar,*sVar = NULL,tmp;
		int				numItems;
		EVariableClass	container;
		int				declaredParam = FALSE;

		// Fetch the parameter
		cVar	=	CRenderer::retrieveVariable(params[i]);
		if (cVar == NULL) {

			// This may be an inline decl., try to parse it into a temp var
			if (parseVariable(&tmp,NULL,params[i])) {
			
				// Save the declared container and fetch the variable
				container		=	tmp.container;
				declaredParam	=	TRUE;

				cVar			=	CRenderer::retrieveVariable(tmp.name);
				if (cVar == NULL) {
					// No match, query the shaders
					sVar		=	&tmp;
					
					cVar		=	attributes->findParameter(tmp.name);
					
					if (cVar != NULL) {
						// check declaration against the shader parameter
						if (cVar->numFloats != sVar->numFloats || cVar->type != sVar->type ) {							
							// We used the inline declaration to check the number of items, but it turns out it mismatches the shader, do not bind
							// Don't warn either
							//warning(CODE_BADTOKEN,"Parameter \"%s\" mismatches declaration\n",params[i]);
							continue;
						}
					}
				} else if ((cVar->storage != STORAGE_GLOBAL)  && (cVar->usageMarker != (PARAMETER_S|PARAMETER_T))) {
					// It was a declaration, Query the shaders
					sVar		=	&tmp;
					cVar		=	attributes->findParameter(tmp.name);
					
					if (cVar != NULL) {
						// check declaration against the shader parameter
						if (cVar->numFloats != sVar->numFloats || cVar->type != sVar->type ) {							
							// We used the inline declaration to check the number of items, but it turns out it mismatches the shader, do not bind
							// Don't warn either
							//warning(CODE_BADTOKEN,"Parameter \"%s\" mismatches declaration\n",params[i]);
							continue;
						}
					}
				}
			} else {
				// Query the shaders
				cVar		=	attributes->findParameter(params[i]);
				
				if (cVar != NULL) {
					container	=	cVar->container;
				}
			}
		} else if ((cVar->storage != STORAGE_GLOBAL) && (cVar->usageMarker != (PARAMETER_S|PARAMETER_T))) {
			// This is a predeclared type, but not a global, query the shaders
			sVar		=	cVar;
			cVar		=	attributes->findParameter(params[i]);
			
			if (cVar != NULL) {
				
				// check declaration against the shader parameter
				if (cVar->numFloats		!= sVar->numFloats ||
					cVar->type			!= sVar->type ||
					(cVar->container == CONTAINER_UNIFORM || cVar->container == CONTAINER_CONSTANT) &&
					(sVar->container != CONTAINER_UNIFORM) && (sVar->container != CONTAINER_CONSTANT)) {
				
					// We used the global declaration to check the number of items, but it mismatches the shader, do not bind
					// Don't warn either
					//warning(CODE_BADTOKEN,"Parameter \"%s\" mismatches declaration\n",params[i]);
					continue;
				}
				
				container	=	cVar->container;
			}
		} else {
			container	=	cVar->container;
		}
		
		//GSHTODO: bind to multiple shaders
		
		// Did we find the variable ?
		if (cVar == NULL) {
			// We did not, so it must be skipped
			continue;
		}
		
		// Check the container type to prevent varying to uniform assignment
		if ((cVar->container == CONTAINER_UNIFORM || cVar->container == CONTAINER_CONSTANT) &&
			(container != CONTAINER_UNIFORM) && (container != CONTAINER_CONSTANT)) {
			
			// Warn because the variables bound but containers don't match
			warning(CODE_BADTOKEN,"Parameter \"%s\" container mismatches definition\n",params[i]);
			continue;
		}
		
		// Do necessary conversions
		if (flags & PL_VARYING_TO_VERTEX) {
			if (container == CONTAINER_VARYING)
				container	=	CONTAINER_VERTEX;
		}

		if (flags & PL_VERTEX_TO_VARYING) {
			if (container == CONTAINER_VERTEX)
				container	=	CONTAINER_VARYING;
		}

		// Size check
		switch(container) {
			case CONTAINER_UNIFORM:
				numItems	=	numUniform;
				break;
			case CONTAINER_VERTEX:
				numItems	=	numVertex;
				break;
			case CONTAINER_VARYING:
				numItems	=	numVarying;
				break;
			case CONTAINER_FACEVARYING:
				numItems	=	numFaceVarying;
				break;
			case CONTAINER_CONSTANT:
				numItems	=	1;
				break;
			default:
				error(CODE_BUG,"Unknown container class in parameter list.\n");
				numItems	=	1;
				break;
		}

		// Treat "st" differently
		if (strcmp(cVar->name,"st") == 0) {
			CPl		*npl;

			memBegin(CRenderer::globalMemory);

			char	**ntokens	=	(char **) ralloc((numParams+1)*sizeof(char *),CRenderer::globalMemory);
			void	**nvals		=	(void **) ralloc((numParams+1)*sizeof(void *),CRenderer::globalMemory);
			int		j;
			float	*sval,*tval,*src;

			sval				=	(float *) ralloc(numItems*sizeof(float),CRenderer::globalMemory);
			tval				=	(float *) ralloc(numItems*sizeof(float),CRenderer::globalMemory);
			src					=	(float *) vals[i];

			// Separate s and t
			for (j=0;j<numItems;j++) {
				sval[j]			=	*src++;
				tval[j]			=	*src++;
			}


			// Create the new parameter list
			for (j=0;j<i;j++) {
				ntokens[j]	=	params[j];
				nvals[j]	=	vals[j];
			}

			char	*sDecl = RI_S;
			char	*tDecl = RI_T;
			
			if( declaredParam ) { 
				char	*decl;
				
				switch(container) {
					case CONTAINER_UNIFORM:
						decl	=	"uniform float";
						break;
					case CONTAINER_VERTEX:
						decl	=	"vertex float";
						break;
					case CONTAINER_VARYING:
						decl	=	"varying float";
						break;
					case CONTAINER_FACEVARYING:
						decl	=	"facevarying float";
						break;
					case CONTAINER_CONSTANT:
						decl	=	"constant float";
						break;
					default:
						error(CODE_BUG,"Unknown container class in parameter list.\n");
						decl	=	"uniform float";
						break;
				}
				sDecl = (char*) ralloc((int) strlen(decl) + (int) strlen(RI_S) + 2,CRenderer::globalMemory);
				tDecl = (char*) ralloc((int) strlen(decl) + (int) strlen(RI_T) + 2,CRenderer::globalMemory);
				sprintf(sDecl,"%s %s",decl,RI_S);
				sprintf(tDecl,"%s %s",decl,RI_T);
			}
			
			ntokens[j]		=	sDecl;
			nvals[j]		=	sval;
			j++;

			ntokens[j]		=	tDecl;
			nvals[j]		=	tval;
			j++;

			for (i++;i<numParams;i++,j++) {
				ntokens[j]	=	params[i];
				nvals[j]	=	vals[i];
			}

			npl	=	parseParameterList(numUniform,numVertex,numVarying,numFaceVarying,j,ntokens,nvals,required,flags,attributes);

			memEnd(CRenderer::globalMemory);

			return npl;
		}

		// Save the parameter
		parameters[numDefinedParams].variable	=	cVar;
		parameters[numDefinedParams].container	=	container;
		parameters[numDefinedParams].numItems	=	numItems;
		
		paramvals[numDefinedParams]				=	vals[i];
		
		numDefinedParams++;

		// Count the size of the data field we need
		dataSize								+=	numItems*cVar->numFloats;
	}


	// Check the required parameter
	if (required != NULL) {
		for (i=0;i<numDefinedParams;i++) {
			if (strcmp(parameters[i].variable->name,required) == 0)	{

				// Make sure that the first parameter is always the required one
				if (i != 0) {
					CPlParameter	tmp		=	parameters[0];
					void			*vtmp	=	paramvals[0];
					parameters[0]			=	parameters[i];
					paramvals[0]			=	paramvals[i];
					parameters[i]			=	tmp;
					paramvals[i]			=	vtmp;
				}

				break;
			}
		}

		// Required parameter is missing
		if (i == numDefinedParams) {
			error(CODE_MISSINGDATA,"Required parameter \"%s\" is missing\n",required);
			return NULL;
		}
	}

	// Allocate the data field
	cData	=	data	=	new float[dataSize];
	stats.gprimCoreMemory	+=	dataSize*sizeof(float);

	// Save the data
	for (i=0;i<numDefinedParams;i++) {
		CVariable		*cVar		=	parameters[i].variable;
		int				num			=	parameters[i].numItems;

		memcpy(cData,(float *) paramvals[i],sizeof(float)*num*cVar->numFloats);

		cData	+=	num*cVar->numFloats;
	}

	// Create the memory for the final pl
	finalParameters					=	new CPlParameter[numDefinedParams];	
	memcpy(finalParameters,parameters,numDefinedParams*sizeof(CPlParameter));
	stats.gprimCoreMemory			+=	numDefinedParams*sizeof(CPlParameter);
	
	// Return the parameter list
	return	new CPl(dataSize,numDefinedParams,finalParameters,data);

}

