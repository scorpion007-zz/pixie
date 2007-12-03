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
//  File				:	shaderPl.h
//  Classes				:	CPLLookup
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#ifndef SHADERPL_H
#define SHADERPL_H

#include "common/global.h"
#include "ri_config.h"
#include "ri.h"

// Forward declarations
struct CShadingScratch;
class CAttributes;

///////////////////////////////////////////////////////////////////////
// Class				:	CPLLookup
// Description			:	This class encapsulates a parameter list
// Comments				:	The shader commands that have a parameter list must derive from this class
class	CPLLookup {
public:
								CPLLookup();
		virtual					~CPLLookup();

								// This function must be overwritten to bind a particular variable
		virtual		void		bind(const char *name,int &opIndex,int step,void *data,CShaderInstance *shader);
								// This function can be overridden to perform initialization not dependant on values
		virtual		void		init(CShadingScratch *scratch,const CAttributes *attributes) { }
								// This function can be overridden to perform initialization dependant on values
		virtual		void		postBind(CShadingScratch *scratch) { }
					void		add(const char *name,int opIndex,int step,void *data,size_t dest);

		const void				*instance;			// The instance that has the PL
		const void				*code;				// The code that has the PL

		///////////////////////////////////////////////////////////////////////
		// Class				:	TParamBinding
		// Description			:	This struct holds a parameter binding
		// Comments				:
		typedef struct TParamBinding {
			const char		*name;					// The name of the variable (used only for debugging)
			int				opIndex;				// The operand index to copy
			int				step;					// The step size
			size_t			dest;					// The destination offset
		} TParamBinding;

		int						numUniforms;		// The number of bindings we have
		TParamBinding			*uniforms;			// The array of bindings

		int						numVaryings;
		TParamBinding			*varyings;

		CPLLookup				*next;				// To maintain a linked list
};





class	CTexture;
class	CEnvironment;
class	CPhotonMap;
class	CTextureInfoBase;
class	CTexture3d;
class	CPointHierarchy;

///////////////////////////////////////////////////////////////////////
// Class				:	CTextureLookup
// Description			:	This class encapsulates a texture lookup
// Comments				:
class	CTextureLookup : public CPLLookup	{
public:
							CTextureLookup();
							~CTextureLookup();

		void				bind(const char *name,int &opIndex,int step,void *data,CShaderInstance *shader);
		void				init(CShadingScratch *scratch,const CAttributes *attributes);

		// static helper for irradiance cache lookups
		static void			staticInit(CShadingScratch *scratch);

		CTexture			*map;
		RtFilterFunc		filter;	
};


///////////////////////////////////////////////////////////////////////
// Class				:	CTraceLookup
// Description			:	For trace/transmission
// Comments				:
class	CTraceLookup : public CPLLookup	{
public:
							CTraceLookup();
							~CTraceLookup();

		void				bind(const char *name,int &opIndex,int step,void *data,CShaderInstance *shader);
		void				init(CShadingScratch *scratch,const CAttributes *attributes);
};

///////////////////////////////////////////////////////////////////////
// Class				:	CEnvironmentLookup
// Description			:	This class encapsulates an environment lookup
// Comments				:	We are derived from trace lookup since we can spawn rays
class	CEnvironmentLookup : public CTraceLookup	{
public:
							CEnvironmentLookup();
							~CEnvironmentLookup();

		void				bind(const char *name,int &opIndex,int step,void *data,CShaderInstance *shader);
		void				init(CShadingScratch *scratch,const CAttributes *attributes);

		CEnvironment		*map;
		RtFilterFunc		filter;	
};


///////////////////////////////////////////////////////////////////////
// Class				:	CPhotonMapLookup
// Description			:	This class encapsulates an environment lookup
// Comments				:
class	CPhotonMapLookup : public CPLLookup	{
public:
							CPhotonMapLookup();
							~CPhotonMapLookup();

		void				bind(const char *name,int &opIndex,int step,void *data,CShaderInstance *shader);
		void				init(CShadingScratch *scratch,const CAttributes *attributes);

		CPhotonMap			*map;
};


///////////////////////////////////////////////////////////////////////
// Class				:	CMapInfoLookup
// Description			:	This class encapsulates an environment lookup
// Comments				:
class	CMapInfoLookup : public CPLLookup	{
public:
							CMapInfoLookup();
							~CMapInfoLookup();

		CTextureInfoBase	*map;
};


///////////////////////////////////////////////////////////////////////
// Class				:	CGlobalIllumLookup
// Description			:	This class encapsulates a global illumination lookup
// Comments				:
class	CTexture3dLookup : public CPLLookup {
public:
							CTexture3dLookup();
							~CTexture3dLookup();

		void				bind(const char *name,int &opIndex,int step,void *data,CShaderInstance *shader);
		void				init(CShadingScratch *scratch,const CAttributes *attributes);
		void				postBind(CShadingScratch *scratch);
		
		CTexture3d			*map;									// The texture we're lookup up
		int					numChannels;							// The number of channels bake3d provides
		const char			*channelName[TEXTURE3D_MAX_CHANNELS];
		int					channelIndex[TEXTURE3D_MAX_CHANNELS];
		int					channelEntry[TEXTURE3D_MAX_CHANNELS];
		int					channelSize[TEXTURE3D_MAX_CHANNELS];	// Entry points for every channel
};


///////////////////////////////////////////////////////////////////////
// Class				:	CGlobalIllumLookup
// Description			:	This class encapsulates a global illumination lookup
// Comments				:	We are derived from texture3D since we're a 3D texture
class	COcclusionLookup : public CTexture3dLookup {
public:
							COcclusionLookup();
							~COcclusionLookup();

		void				bind(const char *name,int &opIndex,int step,void *data,CShaderInstance *shader);
		void				init(CShadingScratch *scratch,const CAttributes *attributes);
		void				postBind(CShadingScratch *scratch);

		CEnvironment		*environment;							// The environment map to use
		CTexture3d			*pointHierarchy;						// The point hierarchy to use
};



///////////////////////////////////////////////////////////////////////
// Class				:	CTextureLookup
// Description			:	This class holds information about a particular texture lookup
// Comments				:
class	CFilterLookup : public CPLLookup	{
public:
							CFilterLookup();
							~CFilterLookup();

		void				bind(const char *name,int &opIndex,int step,void *data,CShaderInstance *shader);
		void				init(CShadingScratch *scratch,const CAttributes *attributes);

		RtStepFilterFunc	filter;						// The filter function
};









class	CGatherRay;


///////////////////////////////////////////////////////////////////////
// Class				:	CGatherVariable
// Description			:	Encapsulates a variable to be saved
// Comments				:
class	CGatherVariable {
public:
	virtual			~CGatherVariable() { }
	virtual	void	record(float *,int,CGatherRay **,float **varying)	=	0;

	CGatherVariable	*next;		// The next item in the linked list
	int				shade;		// TRUE if this variable requires shading
	int				destIndex;	// The destination index
};



///////////////////////////////////////////////////////////////////////
// Class				:	CGatherLookup
// Description			:	Lookup parameters for the gather
// Comments				:
class	CGatherLookup : public CPLLookup {
public:
							CGatherLookup();
							~CGatherLookup();

	void					addOutput(const char *,int,CShaderInstance *shader);
	void					bind(const char *name,int &opIndex,int step,void *data,CShaderInstance *shader);
	void					init(CShadingScratch *scratch,const CAttributes *attributes);

	CGatherVariable			*outputs;				// These are the outputs that require shading
	int						numOutputs;				// The number of outputs
	CGatherVariable			*nonShadeOutputs;		// These are the outputs that do not require shading
	int						numNonShadeOutputs;		// The number of outputs that don't need shading
};


#endif



