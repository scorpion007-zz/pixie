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
//  File				:	sdr.h
//  Classes				:	-
//  Description			:	The shader library interface
//
////////////////////////////////////////////////////////////////////////
#ifndef SDR_H
#define SDR_H

#ifndef LIB_EXPORT
#ifdef _WINDOWS
#define	LIB_EXPORT				__declspec(dllexport)
#else
#define	LIB_EXPORT				extern
#endif
#endif

// Variable type
typedef enum {
	TYPE_FLOAT,
	TYPE_VECTOR,
	TYPE_NORMAL,
	TYPE_POINT,
	TYPE_COLOR,
	TYPE_MATRIX,
	TYPE_STRING
} ESdrType;

// Shader type
typedef enum {
	SHADER_SURFACE,
	SHADER_DISPLACEMENT,
	SHADER_VOLUME,
	SHADER_LIGHT,
	SHADER_IMAGER
} ESdrShaderType;

// Container class
typedef enum {
	CONTAINER_CONSTANT,
	CONTAINER_UNIFORM,
	CONTAINER_VARYING,
	CONTAINER_VERTEX
} ESdrContainer;

// Default value holder
typedef union UDefaultVal *UDefaultValPtr;
typedef union UDefaultVal {
	float					*matrix;
	float					*vector;
	float					scalar;
	char					*string;
	UDefaultValPtr			array;
} UDefaultVal;

// Linked list of shader parameters
typedef struct TSdrParameter {
	char					*name;					// Name of the parameter
	ESdrType				type;					// Type of the parameter
	ESdrContainer			container;				// COntainer class of the parameter
	int						writable;				// Is it an output
	int						numItems;				// Number of items (the number of items if an array, 1 otherwise)
	char					*space;					// The space that the default value is expressed in
	UDefaultVal				defaultValue;			// The default value
	struct TSdrParameter	*next;					// The next parameter
	
} TSdrParameter;

// Shader class
typedef struct TSdrShader {
	char					*name;					// Name of the shader
	ESdrShaderType			type;					// Type of the shader
	struct TSdrParameter	*parameters;			// A linked list of parameters to the shader
} TSdrShader;



// The library interface
#ifdef __cplusplus
extern "C" {
#endif

	LIB_EXPORT	TSdrShader		*sdrGet(const char *,const char *);	// Query a shader
	LIB_EXPORT	void			sdrDelete(TSdrShader *);			// Delete a shader

#ifdef __cplusplus
}
#endif


#endif

