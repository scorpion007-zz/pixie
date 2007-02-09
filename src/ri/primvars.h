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
#ifndef PRIMVARS_H
#define PRIMVARS_H


class	CPrimitiveVariables {
public:
		CPrimitiveVariables() {
			refCount		=	0;
			vertexDispatch	=	NULL;
			varyingDispatch	=	NULL;
			uniformDispatch	=	NULL;
		}

		~CPrimitiveVariables() {
			if (vertexDispatch != NULL)	delete [] vertexDispatch;
			if (varyingDispatch	!= NULL)	delete [] varyingDispatch
		}

	int	refCount;
	int	vertexSize;
	int	varyingSize;
	int	uniformSize;
	int	*vertexDispatch;
	int	*varyingDispatch;
	int	*uniformDispatch;
};

inline	CPrimitiveVariables	*parseList(	float	*&vertices,
										float	*&varyings,
										float	*&uniforms,
										int		numParams,
										char	**vars,
										void	**vals) {

	CPrimitiveVariables	*variables	=	new CPrimitiveVariables;
}


#endif





