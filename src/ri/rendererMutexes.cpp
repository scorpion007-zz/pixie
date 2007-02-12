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
//  File				:	rendererMutexes.cpp
//  Classes				:	CRenderer
//  Description			:
//
////////////////////////////////////////////////////////////////////////

#include "renderer.h"


/////////////////////////////////////////////////////////////
//   This mutex serializes the job assignments.
//   
//  VERIFIED
/////////////////////////////////////////////////////////////
TMutex							CRenderer::jobMutex;


/////////////////////////////////////////////////////////////
//	This mutex is used to serialize job assignment of buckets
//	It is also used to serialize receiving of remote channels
//	- each dispatch of a job must be mutexed so
//	  that it goes to one thread only
//	- in a network render context, all recieves and commits
//	  of remote channels and bucket data must lock this mutex
//	
//	FIXME - usage doesn't seem clear
/////////////////////////////////////////////////////////////
TMutex							CRenderer::commitMutex;



/////////////////////////////////////////////////////////////
//  This mutex is used to make sure we unload a display driver
//  only once
//	
//  VERIFIED
/////////////////////////////////////////////////////////////
TMutex							CRenderer::displayKillMutex;



/////////////////////////////////////////////////////////////
//	This mutex is used to serialize usage of network resources
//	in the global space.
//
//  Only the servers actually use this mutex:
//   - To ask for bucket index to render from the client
//   - To send rendered bucket data to the renderer
//   - To receive a file from the client
//
//  VERIFIED
/////////////////////////////////////////////////////////////
TMutex							CRenderer::networkMutex;



/////////////////////////////////////////////////////////////
//	This mutex is used to ensure only one thread attempts to create
//	subobjects for a mesh (eg. CPolygonMesh)
//	
//	TODO - this could be done per object
//
//	VERIFIED
/////////////////////////////////////////////////////////////
TMutex							CRenderer::hierarchyMutex;



/////////////////////////////////////////////////////////////
//	Used to ensure we serialize creation of CTesselationPatch objects
//	so the list of tesselations is maintained.  This also means that
//	we must lock the mutex whilst examining the list in purge
//	
//	Also used to ensure we only have one thread re-tesselating a level if 
//	TESSELATION_LOCK_PER_ENTRY is not enabled (but it is by default)
//
//	VERIFIED
/////////////////////////////////////////////////////////////
TMutex							CRenderer::tesselateMutex;



/////////////////////////////////////////////////////////////
//	Used to ensure we serialize purging of texture blocks
//  The serial creation of blocks is handled by the fact that
//	textures are loaded on request from shader PL references
//  shader PL unpacking is serialized.
//	
//	Also used to ensure we only have one thread loading a block if 
//	PERBLOCK_LOCK is not enabled (but it is by default)
//
//	Note: if we change shaderMutex usage, we will need to ensure
//	creation of texture blocks is serialized
//
//	VERIFIED
/////////////////////////////////////////////////////////////
TMutex							CRenderer::textureMutex;



/////////////////////////////////////////////////////////////
//	Used to ensure that  each CObject's refCount is only altered
//	by one thread at a time.
//	- every attach() and detach() of a CObject must be mutexed
/////////////////////////////////////////////////////////////
TMutex							CRenderer::refCountMutex;



/////////////////////////////////////////////////////////////
//	Used to ensure that each shader PL gets unpacked by one
//	thread only
//	Note: if we change this, we'll need to mutex other
//	operations like texture loading
//	- all PL modifications in execute must be mutexed
//
//	TODO - we can get away without locking most of the time
//	if we use a check-lock-check idiom as elsewhere
//
//	VERIFIED
/////////////////////////////////////////////////////////////
TMutex							CRenderer::shaderMutex;



/////////////////////////////////////////////////////////////
//	Used to ensure that we manage the list of dirty shaders
//	in a thread safe manner.  We cannot simply use the
//	shaderMutex because we also manage the dirty shader list
//	when a shader gets deleted because the attribute block
//	is no longer referenced.
//	- all modifications of the dirty shader array must be
//	  mutexed
//
//	VERIFIED
/////////////////////////////////////////////////////////////
TMutex							CRenderer::dirtyShaderMutex;



/////////////////////////////////////////////////////////////
//	Used to ensure that only one thread at a time is expanding
//	delayed objects - so we have only one thread in rib parse
//	and only one thread executing a DynamicLoad Procedural
//	
//	FIXME - there are still some remaining issues that can
//	be caused by a thread in rib parse whilst others continue
//	see memoryMutex
/////////////////////////////////////////////////////////////
TMutex							CRenderer::delayedMutex;



/////////////////////////////////////////////////////////////
//	Used to ensure all writes to the deep shadow file are 
//	serialized
//
//	VERIFIED
/////////////////////////////////////////////////////////////
TMutex							CRenderer::deepShadowMutex;



// TODO: Comment on
// Per block mutexes for textures, tesselations, grid objects



///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	beginMutexes
// Description			:	Create the synchronization mutexes
// Return Value			:	-
// Comments				:
void							CRenderer::initMutexes() {
	osCreateMutex(jobMutex);
	osCreateMutex(commitMutex);
	osCreateMutex(displayKillMutex);
	osCreateMutex(networkMutex);
	osCreateMutex(hierarchyMutex);
	osCreateMutex(tesselateMutex);
	osCreateMutex(textureMutex);
	osCreateMutex(refCountMutex);
	osCreateMutex(shaderMutex);
	osCreateMutex(dirtyShaderMutex);
	osCreateMutex(delayedMutex);
	osCreateMutex(deepShadowMutex);
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	endMutexes
// Description			:	Delete the synchronization mutexes
// Return Value			:	-
// Comments				:
void							CRenderer::shutdownMutexes() {
	osDeleteMutex(jobMutex);
	osDeleteMutex(commitMutex);
	osDeleteMutex(displayKillMutex);
	osDeleteMutex(networkMutex);
	osDeleteMutex(hierarchyMutex);
	osDeleteMutex(tesselateMutex);
	osDeleteMutex(textureMutex);
	osDeleteMutex(refCountMutex);
	osDeleteMutex(shaderMutex);
	osDeleteMutex(dirtyShaderMutex);
	osDeleteMutex(delayedMutex);
	osDeleteMutex(deepShadowMutex);
}

