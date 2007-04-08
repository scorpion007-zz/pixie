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
//  File				:	shadeop.h
//  Classes				:
//  Description			:	Defines misc macros for the DSO shadeops
//
////////////////////////////////////////////////////////////////////////
#ifndef SHADEOP_H
#define SHADEOP_H


typedef struct {
	char	*definition;
	char	*init;
	char	*cleanup;
} SHADEOP_SPEC;


#ifdef _WINDOWS

#define	SHADEOP_TABLE(__shadeopname)	extern "C" __declspec(dllexport) SHADEOP_SPEC	__shadeopname##_shadeops[]

#define	SHADEOP_INIT(__shadeopname)		extern "C" void __declspec(dllexport) *__shadeopname(int ctx, void *texturectx) 

#define	SHADEOP(__shadeopname)			extern "C" void __declspec(dllexport) __shadeopname(void *initdata,int argc,char *argv[])

#define	SHADEOP_CLEANUP(__shadeopname)	extern "C" void __declspec(dllexport) __shadeopname(void *initdata)

#else

#define	SHADEOP_TABLE(__shadeopname)	extern "C" SHADEOP_SPEC __shadeopname##_shadeops[]; SHADEOP_SPEC __shadeopname##_shadeops[]

#define	SHADEOP_INIT(__shadeopname)		extern "C" void *__shadeopname(int ctx, void *texturectx) 

#define	SHADEOP(__shadeopname)			extern "C" void __shadeopname(void *initdata,int argc,char *argv[])

#define	SHADEOP_CLEANUP(__shadeopname)	extern "C" void __shadeopname(void *initdata)

#endif

// The function prototypes for the DSO shaders
typedef void	*(*dsoInitFunction)(int,void *);
typedef void	(*dsoExecFunction)(void *,int,void *[]);
typedef void	(*dsoCleanupFunction)(void *);


#endif

