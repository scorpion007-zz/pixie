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
//  File				:	shader.h
//  Classes				:	CShader
//							CShaderInstance
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef SHADER_H
#define SHADER_H

#include "common/global.h"
#include "common/containers.h"
#include "common/os.h"
#include "xform.h"
#include "rendererc.h"
#include "fileResource.h"
#include "ri_config.h"
#include "ri.h"
#include "variable.h"
#include "refCounter.h"

// Forward references
class	CShader;
class	CShaderInstance;
class	CMemPage;
class	CShadingContext;
class	CAttributes;
class	CDSO;

// Meanings of the accessor field of TArgument
const	unsigned int	SL_IMMEDIATE_OPERAND	=	0;	// Constants
const	unsigned int	SL_GLOBAL_OPERAND		=	1;	// Global variable references
const	unsigned int	SL_VARYING_OPERAND		=	2;	// Local variable references (this includes parameters)

// This structure holds an argument for a code
typedef struct {
	unsigned	char	numItems;				// The number of items to step for this variable (0 for constants,parameters, cardinality for variables,globals)
	unsigned	char	accessor;				// The type of the variable (SL_IMMEDIATE,SL_PARAMETER,SL_VARIABLE,SL_GLOBAL)
	unsigned	char	bytesPerItem;			// The number of bytes per item
 	unsigned	char	varyingStep;			// Used to store whether operand is uniform (step 0) or varying (step) ... important PADDING also
	unsigned	int		index;					// The index of the variable in the corresponding entry array
} TArgument;

// This structure holds a code
// In the future, we may want to make this a class 
//    and have the shading language opcodes subclass from it
typedef struct {
	int					opcode;					// The opcode
	unsigned	char	uniform;				// TRUE if all the arguments are uniform
	unsigned	char	numArguments;			// The number of stack arguments
	unsigned	char	padding0;				// PADDING ... Not used ... PADDING
	unsigned	char	padding1;				// PADDING ... Not used ... PADDING
	TArgument			*arguments;				// The array of arguments
	CDSO				*dso;					// If this is a DSO, points to the DSO function
} TCode;

// Shader types
const	unsigned int		SL_SURFACE						=	0;
const	unsigned int		SL_LIGHTSOURCE					=	1;
const	unsigned int		SL_DISPLACEMENT					=	2;
const	unsigned int		SL_ATMOSPHERE					=	3;
const	unsigned int		SL_IMAGER						=	4;

// Shader flags
const	unsigned int		SHADERFLAGS_NONAMBIENT			=	1;
const	unsigned int		SHADERFLAGS_NONDIFFUSE			=	2;
const	unsigned int		SHADERFLAGS_NONSPECULAR			=	4;



///////////////////////////////////////////////////////////////////////
// Class				:	CShaderData
// Description			:	This class records extra data for a shader instance
// Comments				:
class CShaderData {
public:
			CShaderData()  { }
	virtual ~CShaderData() { }
};

///////////////////////////////////////////////////////////////////////
// Class				:	CLightShaderData
// Description			:	This class records data for a light
// Comments				:
class CLightShaderData : public CShaderData {
public:
	int		nonDiffuseIndex;
	int		nonDiffuseStep;
	int		nonSpecularIndex;
	int		nonSpecularStep;

	CLightShaderData() {
		nonDiffuseIndex		= -1;
		nonSpecularIndex	= -1;
		nonDiffuseStep		= 0;
		nonSpecularStep		= 0;
	}
};



///////////////////////////////////////////////////////////////////////
// Class				:	CShader
// Description			:	This class encapsulates a shader
// Comments				:
class	CShader	: public CFileResource {
public:
								CShader(const char *);
								~CShader();

		int						type;							// Type of the shader

		CVariable				*parameters;					// List of parameters

		void					*memory;						// The memory base allocated for this shader
		TCode					*codeArea;						// The code array

		void					**constantEntries;				// The constant entries

		int						*varyingSizes;					// The size of a variable (if negative, it is uniform)

		char					**strings;						// Strings used by the shader

		int						numGlobals;						// Number of global parameters
		int						numStrings;						// Number of strings
		int						numVariables;					// Number of variables

		int						codeEntryPoint;					// Index into code array where the actual code starts
		int						initEntryPoint;					// Index into code array where the init code starts

		int						usedParameters;
		
		unsigned int			flags;							// shadows of parent data (to support hcShaders)
		CShaderData				*data;							// Additional data (owned by CShader)

		friend	CShader			*parseShader(const char *,const char *);
		void					analyse();
};



///////////////////////////////////////////////////////////////////////
// Class				:	CShaderInstance
// Description			:	This class encapsulates an instance of a shader
// Comments				:
class	CShaderInstance : public CRefCounter {
public:
								CShaderInstance(CAttributes *,CXform *);
		virtual					~CShaderInstance();

		virtual	void			illuminate(CShadingContext *,float **)					=	0;
		virtual	void			setParameters(int,const char **,const void **)			=	0;
		virtual int				getParameter(const char *,void *,CVariable**,int*)		=	0;
		virtual	void			execute(CShadingContext *,float **)						=	0;
		virtual	unsigned int	requiredParameters()									=	0;
		virtual	const char		*getName()												=	0;
		virtual	float			**prepare(CMemPage*&,float **,int)						=	0;
		
		void					createCategories();

		CVariable				*parameters;				// The list of parameter (cloned from the parent)
		CXform					*xform;
		int						*categories;				// Categories for light shaders
		unsigned int			flags;
		CShaderData				*data;						// Extra non-instance data
															// simply referenced here (not owned)
};

///////////////////////////////////////////////////////////////////////
// Class				:	CProgrammableShaderInstance
// Description			:	This class encapsulates an instance of a programmable shader
// Comments				:
class	CProgrammableShaderInstance : public CShaderInstance {

	///////////////////////////////////////////////////////////////////////
	// Class				:	CAllocatedString
	// Description			:	We use this class to keep track of the allocated strings for parameters
	// Comments				:
	class	CAllocatedString {
	public:
			char				*string;
			CAllocatedString	*next;
	};
public:
									CProgrammableShaderInstance(CShader *,CAttributes *,CXform *);
		virtual						~CProgrammableShaderInstance();

		void						illuminate(CShadingContext *,float **);
		void						setParameters(int,const char **,const void **);
		int							getParameter(const char *,void *,CVariable**,int*);	// Get the value of a parameter
		void						execute(CShadingContext *,float **);				// Execute the shader
		unsigned int				requiredParameters();
		const char					*getName();
		float						**prepare(CMemPage*&,float **,int);


		CAllocatedString			*strings;					// The strings we allocated for parameters
		CShader						*parent;					// The parent shader
private:
		int							setParameter(const char *,const void *);
};

#endif

