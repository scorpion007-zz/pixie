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





