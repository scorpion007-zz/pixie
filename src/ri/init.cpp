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
//  File				:	init.cpp
//  Classes				:	-
//  Description			:	This file implements the shading language interpreter that runs the init code
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "shader.h"
#include "slcode.h"
#include "noise.h"
#include "shading.h"
#include "renderer.h"
#include "memory.h"
#include "error.h"
#include "rendererContext.h"
#include "random.h"
#include "ri_config.h"


////////////////////////////////////////////////////////////////////////////////////////////////
//	Prototypes for shading language functions
//	These functions are defined in interpreter.cpp
////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Shading language functions ... (implemented in execute.cpp)
#define	saveLighting(a)						scripterror("Invalid environment function call during init\n")
#define clearLighting()						scripterror("Invalid environment function call during init\n")
#define enterLightingConditional()			scripterror("Invalid environment function call during init\n")
#define exitLightingConditional()			scripterror("Invalid environment function call during init\n")
#define enterFastLightingConditional()		scripterror("Invalid environment function call during init\n")
#define exitFastLightingConditional()		scripterror("Invalid environment function call during init\n")
#define	rendererInfo(a,b)					scripterror("Invalid environment function call during init\n")
#define	emission(a,b)						scripterror("Invalid environment function call during init\n")
#define debugFunction(a)
#define	illuminateBegin(a,b,c,d,e,f)
#define findCoordinateSystem				CRenderer::findCoordinateSystem
#define threadMemory						CRenderer::globalMemory
#define urand()								_urand()

///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	convertColorFrom
// Description			:	Do color conversion
// Return Value			:	-
// Comments				:
void		convertColorFrom(float *out,const float *in,ECoordinateSystem s)	{
	switch(s) {
	case COLOR_RGB:
		movvv(out,in);
		break;
	case COLOR_HSL:
		{

#define	HueToRGB(r,m1,m2,h )												\
	if (h<0) h+=1;															\
	if (h>1) h-=1;															\
	if (6.0*h < 1  )		r	= (m1+(m2-m1)*h*6);							\
	else if (2.0*h < 1  )	r	= m2;										\
	else if (3.0*h < 2.0)	r	= (m1+(m2-m1)*((2.0f/3.0f)-h)*6);			\
	else					r	= m1;


			float m1,m2,h;

			if (in[1]==0) initv(out,in[2],in[2],in[2]);
			else {
				if (in[2] <=0.5)	m2 = in[2]*(1+in[1]);
				else				m2 = in[2]+in[1]-in[2]*in[1];
				m1	= 2*in[2]-m2;
				
				h	=	in[0] + (1.0f/3.0f);	HueToRGB(out[0],m1,m2,h);
				h	=	in[0];					HueToRGB(out[1],m1,m2,h);
				h	=	in[0] - (1.0f/3.0f);	HueToRGB(out[2],m1,m2,h);
			}
#undef HueToRGB

		}
		break;
	case COLOR_HSV:
		{
			if (in[1] < -1 || in[1] > 1) {
				if (in[0] == 0) {
					out[0]	=	in[2];
					out[1]	=	in[2];
					out[2]	=	in[2];
				} else {
					out[0]	=	in[0];
					out[1]	=	in[1];
					out[2]	=	in[2];
				}
			} else {
				float	f,p,q,t,h;
				int		i;

				h			=	(float) fmod(in[0],1);
				if (h < 0)	h	+=	1;

				h		*=	6;

				i		=	(int) floor(h);
				f		=	h - i;
				p		=	in[2]*(1-in[1]);
				q		=	in[2]*(1-(in[1]*f));
				t		=	in[2]*(1-(in[1]*(1-f)));

				switch(i) {
				case 0:	out[COMP_R]	=	in[2];	out[COMP_G]	=	t;		out[COMP_B]	=	p;		break;
				case 1:	out[COMP_R]	=	q;		out[COMP_G]	=	in[2];	out[COMP_B]	=	p;		break;
				case 2:	out[COMP_R]	=	p;		out[COMP_G]	=	in[2];	out[COMP_B]	=	t;		break;
				case 3:	out[COMP_R]	=	p;		out[COMP_G]	=	q;		out[COMP_B]	=	in[2];	break;
				case 4:	out[COMP_R]	=	t;		out[COMP_G]	=	p;		out[COMP_B]	=	in[2];	break;
				case 5:	out[COMP_R]	=	in[2];	out[COMP_G]	=	p;		out[COMP_B]	=	q;		break;
				}
			}
		}
		break;
	case COLOR_XYZ:
		out[COMP_R]		=	(float)  (3.24079*in[0]		-	1.537150*in[1]	-	0.498535*in[2]);
		out[COMP_G]		=	(float) (-0.969256*in[0]	+	1.875992*in[1]	+	 0.041556*in[2]);
		out[COMP_B]		=	(float)   (0.055648*in[0]	-	0.204043*in[1]	+	1.057311*in[2]);
		break;
	case COLOR_CIE:
		out[COMP_R]		=	(float)  (3.24079*in[0]		-	1.537150*in[1]	-	0.498535*in[2]);
		out[COMP_G]		=	(float) (-0.969256*in[0]	+	1.875992*in[1]	+	 0.041556*in[2]);
		out[COMP_B]		=	(float)   (0.055648*in[0]	-	0.204043*in[1]	+	1.057311*in[2]);
		break;
	case COLOR_YIQ:
		out[COMP_R]		=	(float) (in[0]	+	0.956*in[1]	+	0.620*in[2]);
		out[COMP_G]		=	(float) (in[0]	-	0.272*in[1]	-	0.647*in[2]);
		out[COMP_B]		=	(float) (in[0]	-	1.108*in[1]	+	1.705*in[2]);
		break;
	case COLOR_XYY:
		vector	tin;

		if (in[2] == 0) {
			tin[0]	=	0;
			tin[1]	=	0;
			tin[2]	=	0;
		} else {
			tin[0]	=	max(in[0]*in[2]/in[1],0);
			tin[1]	=	in[2];
			tin[2]	=	max((1-in[0]-in[1])*in[2]/in[1],0);
		}

		out[COMP_R]		=	(float)  (3.24079*tin[0]		-	1.537150*tin[1]	-	0.498535*tin[2]);
		out[COMP_G]		=	(float) (-0.969256*tin[0]	+	1.875992*tin[1]	+	 0.041556*tin[2]);
		out[COMP_B]		=	(float)   (0.055648*tin[0]	-	0.204043*tin[1]	+	1.057311*tin[2]);

		break;
	default:
		break;
	}
}


///////////////////////////////////////////////////////////////////////
// Class				:	CShadingContext
// Method				:	convertColorTo
// Description			:	Do color conversion
// Return Value			:	-
// Comments				:
void		convertColorTo(float *out,const float *in,ECoordinateSystem s) {
	switch(s) {
	case COLOR_RGB:
		movvv(out,in);
		break;
	case COLOR_HSL:
		{
			float	mi	=	min(in[0],min(in[1],in[2]));
			float	ma	=	max(in[0],max(in[1],in[2]));

			out[2]		=	(mi + ma) / 2;
			if (ma == mi) {
				out[0]	=	100;// install value out of -1 to 1 range
				out[1]	=	0;
			} else {
				float	d	=	ma - mi;

				if (out[2] < 0.5) {
					out[1]	=	d / (ma + mi);
				} else {
					out[1]	=	d / (2 - (ma + mi));
				}

				if (in[COMP_R]	==	ma) {
					out[0]	=	(in[COMP_G] - in[COMP_B])/d;
				} else if (in[COMP_G] == ma) {
					out[0]	=	2 + (in[COMP_B] - in[COMP_R])/d;
				} else {
					out[0]	=	4 + (in[COMP_R] - in[COMP_G])/d;
				}

				out[0]	/=	(float) 6;

				if (out[0] < 0) out[0] +=	1;
			}
		}
		break;
	case COLOR_HSV:
		{
			float	ma	=	max(in[0],max(in[1],in[2]));
			float	mi	=	min(in[0],min(in[1],in[2]));

			out[2]		=	ma;
			out[1]		=	(ma - mi) / ma;
			if (ma == 0) {
				out[0]	=	100;// install value out of -1 to 1 range
			} else {
				float	d	=	ma	-	mi;

				if (in[COMP_R]	==	ma) {
					out[0]	=	(in[COMP_G] - in[COMP_B])	/	d;
				} else if (in[COMP_G] == ma) {
					out[0]	=	2 + (in[COMP_B] - in[COMP_R])	/	d;
				} else {
					out[0]	=	4 + (in[COMP_R] - in[COMP_G])	/	d;
				}

				out[0]		/=	(float) 6;
				if (out[0] < 0)		out[0]	+=	1;
			}
		}
		break;
	case COLOR_XYZ:
		out[0]	=	(float) (0.412453 * in[COMP_R]	+	0.357580 * in[COMP_G]	+	0.180423 * in[COMP_B]);
		out[1]	=	(float) (0.212671 * in[COMP_R]	+	0.715160 * in[COMP_G]	+	0.072169 * in[COMP_B]);
		out[2]	=	(float) (0.019334 * in[COMP_R]	+	0.119193 * in[COMP_G]	+	0.950227 * in[COMP_B]);
		break;
	case COLOR_CIE:
		out[0]	=	(float) (0.412453 * in[COMP_R]	+	0.357580 * in[COMP_G]	+	0.180423 * in[COMP_B]);
		out[1]	=	(float) (0.212671 * in[COMP_R]	+	0.715160 * in[COMP_G]	+	0.072169 * in[COMP_B]);
		out[2]	=	(float) (0.019334 * in[COMP_R]	+	0.119193 * in[COMP_G]	+	0.950227 * in[COMP_B]);
		break;
	case COLOR_YIQ:
		out[0]	=	(float) (0.299 * in[COMP_R]	+	0.587 * in[COMP_G]	+	0.114 * in[COMP_B]);
		out[1]	=	(float) (0.596 * in[COMP_R]	-	0.275 * in[COMP_G]	-	0.321 * in[COMP_B]);
		out[2]	=	(float) (0.212 * in[COMP_R]	-	0.523 * in[COMP_G]	+	0.311 * in[COMP_B]);
		break;
	case COLOR_XYY:
		vector	tin;
		float	sum;

		tin[0]	=	(float) (0.412453 * in[COMP_R]	+	0.357580 * in[COMP_G]	+	0.180423 * in[COMP_B]);
		tin[1]	=	(float) (0.212671 * in[COMP_R]	+	0.715160 * in[COMP_G]	+	0.072169 * in[COMP_B]);
		tin[2]	=	(float) (0.019334 * in[COMP_R]	+	0.119193 * in[COMP_G]	+	0.950227 * in[COMP_B]);

		sum		=	tin[0] + tin[1] + tin[2];
		if (sum == 0) {
			initv(out,0,0,0);
		} else {
			out[0]	=	tin[0] / sum;
			out[1]	=	tin[1] / sum;
			out[2]	=	tin[2];
		}
		break;
	default:
		break;
	}
}


///////////////////////////////////////////////////////////////////////
// Function				:	sfInit
// Description			:	Execute the current shader's init code
// Return Value			:	-
// Comments				:
void	CRendererContext::init(CProgrammableShaderInstance *currentShaderInstance) {
// At this point, the shader sends us the arrays for parameters/constants/variables/uniforms for the shader

#define		scripterror(mes)				{																	\
												error(CODE_SCRIPT,"\"%s\", (nullified)\n",mes);					\
												currentShaderInstance->parent->codeEntryPoint	=	-1;			\
												currentShaderInstance->parent->initEntryPoint	=	-1;			\
												goto	execEnd;												\
											}
//	Allocate temporary memory for the string and save it
#define		savestring(r,n)					{																	\
												int		strLen	=	(int) strlen(n) + 1;						\
												int		strSize	=	(strLen & ~3) + 4;							\
												char	*strmem	=	(char *) ralloc(strSize,threadMemory);		\
												strcpy(strmem,n);												\
												r				=	strmem;										\
											}

//	Begin a conditional block execution
#define		beginConditional()				if (conditionals == NULL) {											\
												conditionals		=	new CConditional;						\
												conditionals->next	=	NULL;									\
												conditionals->prev	=	NULL;									\
											}																	\
																												\
											conditionals->prev		=	lastConditional;						\
											lastConditional			=	conditionals;							\
											conditionals			=	lastConditional->next;
											

//	End a conditional block execution
#define		endConditional()				lastConditional->next	=	conditionals;							\
											conditionals			=	lastConditional;						\
											lastConditional			=	lastConditional->prev;

//	Retrieve a pointer to an operand and obtain it's size
#define		operand(i,n,t)					{																	\
												const TArgument	ref	=	code->arguments[i];						\
												n	= (t) stuff[ref.accessor][ref.index];						\
											}

	//	Retrieve an operand's size
#define		operandSize(i,n,s,t)			{																	\
												const TArgument	ref	=	code->arguments[i];						\
												n	= (t) stuff[ref.accessor][ref.index];						\
												s	= ref.numItems;												\
											}

#define		operandNumItems(i)				code->arguments[i].numItems

#define		operandBytesPerItem(i)			code->arguments[i].bytesPerItem

#define		operandVaryingStep(i)			code->arguments[i].varyingStep

//	Retrieve an integer operand (label references are integer)
#define		argument(i)						code->arguments[i].index

//	Retrieve the number of arguments
#define		argumentcount(n)				n = code->numArguments

//	Control transfer
#define		jmp(n)							{																	\
												code	=	currentShader->codeArea + n;						\
												goto execStart;													\
											}



//	Run the light source shaders for the lP
#define		runAmbientLights()				scripterror("Light source exec during init code\n");

//	Run the light source shaders for the lP
#define		runLights(lP,lN,lT)				scripterror("Light source exec during init code\n");
#define		runCategoryLights(lP,lN,lT,lC)	scripterror("Light source exec during init code\n");

// The misc macros
#define		DEFLINKOPCODE(name,text,nargs)				case OPCODE_##name:		
#define		DEFLINKFUNC(name,text,prototype,par)		case FUNCTION_##name:

// Break the shader execution
#define		BREAK							goto execEnd;



//	The	shading variables and junk
	void						**stuff[3];			// Where we keep pointers to the variables
	CConditional				*lastConditional;	// The last conditional
	int							numActive;
	int							numPassive;
	int							*tags;
	int							*tagStart;
	CShader						*currentShader			=	currentShaderInstance->parent;
	const TCode					*code;
	int							tmpTags;
	int							numVertices;
	float						**varying;
	CShadedLight				**lights;
	CShadedLight				**alights;
	CShadedLight				**currentLight;
	CConditional				*conditionals			=	NULL;
	CConditional				*cConditional;
	int							i;
	CVariable					*cParameter;

	code									=	currentShader->codeArea + currentShader->initEntryPoint;

	numVertices								=	1;
	tagStart								=	&tmpTags;
	tmpTags									=	0;

	// Setup local variables
	stuff[SL_VARYING_OPERAND]				=	(void **) ralloc(currentShader->numVariables*sizeof(void *),threadMemory);	// Shader varying variables
	for (i=0;i<currentShader->numVariables;i++) {											// Allocate memory for every varying variable
		int	size							=	currentShader->varyingSizes[i];

		if (size != 0) {
			if (size < 0)	size				=	-size;
			stuff[SL_VARYING_OPERAND][i]		=	(void *) ralloc(size,threadMemory);
		}
	}

	// Now go thru the parameters and replace the corresponding variables with their default values
	for (cParameter=currentShaderInstance->parameters;cParameter!=NULL;cParameter=cParameter->next) {
		assert(cParameter->defaultValue != NULL);

		stuff[SL_VARYING_OPERAND][cParameter->entry]	=	(TCode *) cParameter->defaultValue;

		// Relink the entry point to the global, we already verified the match
		if (cParameter->storage == STORAGE_GLOBAL) {
			CVariable	*cVar	=	CRenderer::retrieveVariable(cParameter->name);
			cParameter->entry	=	cVar->entry;
		}
	}


	varying									=	NULL;
	lights									=	NULL;
	alights									=	NULL;
	currentLight							=	NULL;

	// Set the access arrays
	stuff[SL_IMMEDIATE_OPERAND]				=	currentShader->constantEntries;				// Immediate operands
	stuff[SL_GLOBAL_OPERAND]				=	(void **) varying;							// Varying globals

	numActive								=	numVertices;
	numPassive								=	0;
	lastConditional							=	NULL;										// The last conditional block

	// Execute
execStart:
	const ESlCode	opcode	=	(ESlCode)	code->opcode;

	tags	=	tagStart;

#define		INIT_SHADING
#define		DEFOPCODE(name,text,nargs,expr_pre,expr,expr_update,expr_post,param)			\
	case OPCODE_##name:																		\
	{																						\
		expr_pre;																			\
		expr;																				\
		expr_post																			\
		code++;																				\
		goto execStart;																		\
	}																						\
	break;

#define		DEFSHORTOPCODE(name,text,nargs,expr_pre,expr,expr_update,expr_post,param)		\
	case OPCODE_##name:																		\
	{																						\
		expr_pre;																			\
		expr;																				\
		expr_post																			\
		code++;																				\
		goto execStart;																		\
	}																						\
	break;


#define		DEFFUNC(name,text,prototype,expr_pre,expr,expr_update,expr_post,par)			\
	case FUNCTION_##name:																	\
	{																						\
		expr_pre;																			\
		expr;																				\
		expr_post																			\
		code++;																				\
		goto execStart;																		\
	}																						\
	break;

#define		DEFLIGHTFUNC(name,text,prototype,expr_pre,expr,expr_update,expr_post,par)		\
	case FUNCTION_##name:																	\
	{																						\
		expr_pre;																			\
		expr;																				\
		expr_post																			\
		code++;																				\
		goto execStart;																		\
	}																						\
	break;


#define		DEFSHORTFUNC(name,text,prototype,expr_pre,expr,expr_update,expr_post,par)		\
	case FUNCTION_##name:																	\
	{																						\
		expr_pre;																			\
		expr;																				\
		expr_post																			\
		code++;																				\
		goto execStart;																		\
	}																						\
	break;

	switch(opcode) {

#include "scriptOpcodes.h"

#include "scriptFunctions.h"

	default:
		goto execEnd;
	}

	code++;
	goto execStart;
#undef	DEFOPCODE
#undef	DEFFUNC
#undef	DEFLIGHTFUNC
#undef	INIT_SHADING



	goto execStart;
execEnd:

	// Delete the conditionals
	while((cConditional=conditionals) != NULL) {
		conditionals	=	cConditional->next;
		delete cConditional;
	}

	assert(numActive	== numVertices);
	assert(numPassive	== 0);

// Undefine junk
#undef		savestring
#undef		allocbuffer
#undef		freebuffer
#undef		beginConditional
#undef		endConditional
#undef		operand
#undef		argument
#undef		argumentcount
#undef		jmp
#undef		runAmbientLights
#undef		runCategoryLights
#undef		runLights
#undef		firstLight
#undef		nextLight
#undef		allLights
#undef		currentLight
#undef		saveLight
#undef		uniformGlobal
#undef		varyingGlobal
#undef		DEFOPCODE
#undef		DEFFUNC
#undef		DEFLINKOPCODE
#undef		DEFLINKFUNC
#undef		BREAK
}

