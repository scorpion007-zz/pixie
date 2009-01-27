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
//  File				:	rendererFiles.cpp
//  Classes				:	CRenderer
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include <string.h>
#include <math.h>

#include "renderer.h"
#include "error.h"
#include "texture.h"
#include "photonMap.h"
#include "irradiance.h"
#include "texture3d.h"
#include "remoteChannel.h"
#include "brickmap.h"
#include "pointCloud.h"
#include "dso.h"
#include "rendererContext.h"
#include "shadeop.h"
#include "options.h"
#include "netFileMapping.h"
#include "pointHierarchy.h"


// This one is defined in sdr.y
CShader			*parseShader(const char *,const char *);


///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	initFiles
// Description			:	Init the files
// Return Value			:
// Comments				:
void		CRenderer::initFiles() {

	// The loaded shaders
	globalFiles							=	new CTrie<CFileResource *>;

	// Temporary files we store per frame
	frameTemporaryFiles					=	NULL;

	// DSO init
	dsos								=	NULL;
}

///////////////////////////////////////////////////////////////////////
// Function				:	sfClearTemp
// Description			:	This callback function is used to remove the temporary files
// Return Value			:
// Comments				:
static int	rcClearTemp(const char *fileName,void *userData) {
	osDeleteFile(fileName);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	shutdownFiles
// Description			:	Shutdown the files
// Return Value			:
// Comments				:
void		CRenderer::shutdownFiles() {

	// Ditch the temporary files created
	if (osFileExists(temporaryPath)) {
		char	tmp[OS_MAX_PATH_LENGTH];

		sprintf(tmp,"%s*",temporaryPath);
		osFixSlashes(tmp);
		osEnumerate(tmp,rcClearTemp,NULL);
		osDeleteDir(temporaryPath);
	}
	
	// Ditch the DSO shaders that have been loaded
	CDSO	*cDso;
	for (cDso=dsos;cDso!=NULL;) {
		CDSO	*nDso	=	cDso->next;
		// Call DSO's cleanup
		if(cDso->cleanup != NULL) cDso->cleanup(cDso->handle);
		free(cDso->name);
		free(cDso->prototype);
		delete cDso;
		cDso	=	nDso;
	}	

	// Ditch the loaded files
	assert(globalFiles != NULL);
	globalFiles->destroy();
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	locateFileEx
// Description			:	Locate a file on disk
// Return Value			:	TRUE if found
// Comments				:
int			CRenderer::locateFileEx(char *result,const char *name,const char *extension,TSearchpath *searchpath) {
	const char *dotpos	=	strchr(name,'.');
	const char *seppos	=	strchr(name,OS_DIR_SEPERATOR);
	if (dotpos < seppos || dotpos == NULL) {
		char	tmp[OS_MAX_PATH_LENGTH];

		sprintf(tmp,"%s.%s",name,extension);

		return locateFile(result,tmp,searchpath);
	} else {
		return locateFile(result,name,searchpath);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	locateFile
// Description			:	Locate a file on disk
// Return Value			:	TRUE if found
// Comments				:
int	CRenderer::locateFile(char *result,const char *name,TSearchpath *searchpath) {

	if (netClient != INVALID_SOCKET) {
		// check netfile mappings
		CNetFileMapping* mapping;
		if (netFileMappings->find(name,mapping)) {
			name = mapping->to;
		}
	}
	
	if (strchr(name,OS_DIR_SEPERATOR)) {
		// Supplied path
	// Check if the file exists
	if (osFileExists(name)) {
		strcpy(result,name);
		info(CODE_RESOLUTION,"\"%s\" -> \"%s\"\n",name,name);
		return TRUE;
	}
	} else {
		// Only filename
	// Look at the search path
	for (;searchpath!=NULL;searchpath=searchpath->next) {
		sprintf(result,"%s%s",searchpath->directory,name);
		osFixSlashes(result);
		if (osFileExists(result)) {
			info(CODE_RESOLUTION,"\"%s\" -> \"%s\"\n",name,result);
			return TRUE;
		}
	}

	// Last resort, look into the temporary directory
	sprintf(result,"%s%s",temporaryPath,name);
	osFixSlashes(result);
	if (osFileExists(result)) {
		info(CODE_RESOLUTION,"\"%s\" -> \"%s\"\n",name,result);
		return TRUE;
	}
	}

	// Unable to find the file, check the network
	// Check the net if we can find the file
	if (netClient != INVALID_SOCKET) {

		// Lock the network
		osLock(networkMutex);

		if (getFile(result,name) == TRUE) {
			if (osFileExists(result)) {
				info(CODE_RESOLUTION,"\"%s\" -> \"%s\"\n",name,result);
				osUnlock(networkMutex);
				return TRUE;
			}
		}

		// Unlock the network
		osUnlock(networkMutex);
	}

	info(CODE_RESOLUTION,"\"%s\" -> ???\n",name);

	return FALSE;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	getTexture
// Description			:	Load a texture from file
// Return Value			:
// Comments				:
CTexture	*CRenderer::getTexture(const char *name) {
	CFileResource	*tex;

	assert(name != NULL);
	assert(frameFiles != NULL);
	
	if (frameFiles->find(name,tex) == FALSE) {
	
		// Load the texture
		tex	=	textureLoad(name,texturePath);

		if (tex == NULL)	{
			// Not found, substitude with a dummy one
			if (*name != 0) error(CODE_NOFILE,"Failed open texture \"%s\"\n",name);
			tex					=	new CDummyTexture(name);
		}

		frameFiles->insert(tex->name,tex);
	}

	return (CTexture *) tex;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	getEnvironment
// Description			:	Load an environment map (which can also be a shadow map)
// Return Value			:
// Comments				:
CEnvironment	*CRenderer::getEnvironment(const char *name) {
	CFileResource	*tex;

	assert(name != NULL);
	assert(frameFiles != NULL);
	
	if (frameFiles->find(name,tex) == FALSE) {
	
		tex	=	environmentLoad(name,texturePath,toWorld);

		if (tex == NULL)	{
			// Not found, substitude with a dummy one
			error(CODE_NOFILE,"Failed open environment \"%s\"\n",name);
			tex					=	new CDummyEnvironment(name);
		}

		frameFiles->insert(tex->name,tex);
	}

	return (CEnvironment *) tex;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	getPhotonMap
// Description			:	Load a photon map
// Return Value			:
// Comments				:
CPhotonMap		*CRenderer::getPhotonMap(const char *name) {
	CFileResource	*map;
	char			fileName[OS_MAX_PATH_LENGTH];
	FILE			*in;

	assert(name != NULL);
	assert(frameFiles != NULL);

	// Check the cache to see if the file is in the memory
	if (frameFiles->find(name,map) == FALSE){

		// Locate the file
		if (locateFile(fileName,name,texturePath)) {
			// Try to open the file
			in		=	ropen(fileName,"rb",filePhotonMap,TRUE);
		} else {
			in		=	NULL;
		}

		// Read it
		map		=	new CPhotonMap(name,in);
		frameFiles->insert(map->name,map);
	}

	return (CPhotonMap *) map;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	getCache
// Description			:	Load a cache
// Return Value			:
// Comments				:
CTexture3d		*CRenderer::getCache(const char *name,const char *mode,const float *from,const float *to) {
	CFileResource	*cache;

	assert(name != NULL);
	assert(frameFiles != NULL);
	
	// Check the memory first
	if (frameFiles->find(name,cache) == FALSE){
		char				fileName[OS_MAX_PATH_LENGTH];
		int					flags;
		char				type[128];
		int					createChannel = FALSE;

		// Process the file mode
		if (strcmp(mode,"r") == 0) {
			flags	=	CACHE_READ| CACHE_SAMPLE;
		} else if (strcmp(mode,"w") == 0) {
			flags	=	CACHE_WRITE | CACHE_SAMPLE;
		} else if (strcmp(mode,"R") == 0) {
			flags	=	CACHE_READ | CACHE_RDONLY;
		} else if (strcmp(mode,"rw") == 0) {
			flags	=	CACHE_READ | CACHE_WRITE | CACHE_SAMPLE;
		} else {
			flags	=	CACHE_SAMPLE;
		}
		
		// Try to read the file
		cache		=	NULL;
		if (flags & CACHE_READ) {

			// Locate the file
			if (locateFile(fileName,name,texturePath)) {
				FILE	*in	=	ropen(fileName,type);

				if (in != NULL) {
					// If we're netrendering and writing, treat specially
					if ((netClient != INVALID_SOCKET) && (flags & CACHE_WRITE)) {
						flags			&=	~CACHE_WRITE;		// don't flush cache to disk
						createChannel	=	TRUE;
						if (strncmp(fileName,temporaryPath,strlen(temporaryPath)) == 0) {
							// it's a temp file, delete it after we're done
							registerFrameTemporary(fileName,TRUE);
						}
						// always remove the file mapping when writing
						registerFrameTemporary(name,FALSE);
					}
					
					// Create the cache
					if (strcmp(type,fileIrradianceCache) == 0) {
						cache	=	new CIrradianceCache(name,flags,in,from,to,NULL);
					} else {
						error(CODE_BUG,"Unable to recognize the file format of \"%s\"\n",name);
						fclose(in);
					}
				}
			}
		}

		// If there is no cache, create it
		if (cache == NULL) {
			// If we're netrendering and writing, treat specially
			if ((netClient != INVALID_SOCKET) && (flags & CACHE_WRITE)) {
				flags			&=	~CACHE_WRITE;		// don't flush cache to 
				createChannel	=	TRUE;
				// always remove the file mapping when writing
				registerFrameTemporary(name,FALSE);
			}
			
			// go ahead and create the cache
			cache	=	new CIrradianceCache(name,flags,NULL,from,to,CRenderer::toNDC);
		}
		
		// Create channels if possible
		if (createChannel == TRUE) {
			if (cache != NULL) {
				requestRemoteChannel(new CRemoteICacheChannel((CIrradianceCache *) cache));
			}
		}

		frameFiles->insert(cache->name,cache);
	}

	return (CTexture3d *) cache;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	getTextureInfo
// Description			:	Load a texture from file
// Return Value			:
// Comments				:
CTextureInfoBase	*CRenderer::getTextureInfo(const char *name) {
	CFileResource	*tex;

	assert(name != NULL);
	assert(frameFiles != NULL);
	
	if (frameFiles->find(name,tex) == FALSE){
		// try environments first
		tex	=	environmentLoad(name,texturePath,toWorld);

		if (tex == NULL)	{
			// else try as textures
			tex	=	textureLoad(name,texturePath);
		}

		if (tex != NULL) {
			// only store the result if found
			frameFiles->insert(tex->name,tex);
		}
	}

	return (CTextureInfoBase *) tex;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	getTexture3d
// Description			:	Get a point cloud or brickmap
// Return Value			:
// Comments				:
CTexture3d			*CRenderer::getTexture3d(const char *name,int write,const char* channels,const float *from,const float *to,int hierarchy) {
	CFileResource	*texture3d;
	char			fileName[OS_MAX_PATH_LENGTH];
	FILE			*in;

	assert(name != NULL);
	assert(frameFiles != NULL);
	
	if (frameFiles->find(name,texture3d) == FALSE){

		if (from == NULL) {
			from	=	world->from;
			to		=	world->to;
		}
		
		// If we are writing, it must be a point cloud
		if (write == TRUE) {
			
			if (netClient != INVALID_SOCKET) {
				CPointCloud	*cloud	=	new CPointCloud(name,world->from,world->to,CRenderer::toNDC,channels,FALSE);
				texture3d			=	cloud;
			
				// Ensure we unmap the file when done.  Do not delete it
				// as we mark the file to never be written in the server
				registerFrameTemporary(name,FALSE);
				requestRemoteChannel(new CRemotePtCloudChannel(cloud));
			} else {
				// alloate a point cloud which will be written to disk
				texture3d	=	new CPointCloud(name,from,to,CRenderer::toNDC,channels,TRUE);
			}
			
		} else {
			// Locate the file
			if (locateFile(fileName,name,texturePath)) {
				// Try to open the file
				if ((in	=	ropen(fileName,"rb",filePointCloud,TRUE)) != NULL) {
					if (hierarchy == TRUE) {
						texture3d	=	new CPointHierarchy(name,from,to,in);
					} else {
						texture3d	=	new CPointCloud(name,from,to,in);
					}
				} else {
					if ((in	=	ropen(fileName,"rb",fileBrickMap,TRUE)) != NULL) {
						texture3d	=	new CBrickMap(in,name,from,to);
					}
				}
			} else {
				in		=	NULL;
			}
			
			if (in == NULL) {
				// allocate a dummy blank-channel point cloud
				error(CODE_BADTOKEN,"Cannot find or open Texture3D file \"%s\"\n",name);
				texture3d	=	new CPointCloud(name,world->from,world->to,NULL,NULL,FALSE);
				// remove the dummy mapping once the frame ends
				registerFrameTemporary(name,FALSE);
			}
		}
				
		frameFiles->insert(texture3d->name,texture3d);
	}

	return (CPointCloud *) texture3d;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRendererContext
// Method				:	getShader
// Description			:	Create an instance of a shader
// Return Value			:
// Comments				:
CShader		*CRenderer::getShader(const char *name,TSearchpath *path) {
	CShader			*cShader;
	CFileResource	*file;

	assert(name != NULL);
	if (strcmp(name,RI_DEFAULTSURFACE) == 0)	name	=	RI_MATTE;

	assert(globalFiles != NULL);
	
	// Check if we already loaded this shader before ...
	cShader		=	NULL;
	if (globalFiles->find(name,file)) {
		cShader		=	(CShader *) file;
	} else {
		char	shaderLocation[OS_MAX_PATH_LENGTH];

		if (CRenderer::locateFileEx(shaderLocation,name,"sdr",path) == TRUE) {
			cShader	=	parseShader(name,shaderLocation);

			if (cShader != NULL) {
				globalFiles->insert(cShader->name,cShader);
			}
		}
	}

	return cShader;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	getFilter
// Description			:	Return the filter matching the name
// Return Value			:
// Comments				:
RtFilterFunc			CRenderer::getFilter(const char *name) {
	if (strcmp(name,RI_GAUSSIANFILTER) == 0) {
		return	RiGaussianFilter;
	} else if (strcmp(name,RI_BOXFILTER) == 0) {
		return	RiBoxFilter;
	} else if (strcmp(name,RI_TRIANGLEFILTER) == 0) {
		return	RiTriangleFilter;
	} else if (strcmp(name,RI_SINCFILTER) == 0) {
		return	RiSincFilter;
	} else if (strcmp(name,RI_CATMULLROMFILTER) == 0) {
		return	RiCatmullRomFilter;
	} else if (strcmp(name,RI_BLACKMANHARRISFILTER) == 0) {
		return	RiBlackmanHarrisFilter;
	} else if (strcmp(name,RI_MITCHELLFILTER) == 0) {
		return	RiMitchellFilter;
	} else if (strcmp(name,RI_BESSELFILTER) == 0) {
		return  RiBesselFilter;
	} else if (strcmp(name,RI_DISKFILTER) == 0) {
		return  RiDiskFilter;
	}

	return	RiGaussianFilter;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	getFilter
// Description			:	Return the name matching the filter
// Return Value			:
// Comments				:
const char					*CRenderer::getFilter(RtFilterFunc func) {
	if (func == RiGaussianFilter) {
		return	RI_GAUSSIANFILTER;
	} else if (func == RiBoxFilter) {
		return	RI_BOXFILTER;
	} else if (func == RiTriangleFilter) {
		return	RI_TRIANGLEFILTER;
	} else if (func == RiSincFilter) {
		return	RI_SINCFILTER;
	} else if (func == RiCatmullRomFilter) {
		return	RI_CATMULLROMFILTER;
	} else if (func == RiBlackmanHarrisFilter) {
		return	RI_BLACKMANHARRISFILTER;
	} else if (func == RiMitchellFilter) {
		return	RI_MITCHELLFILTER;
	} else if (func == RiBesselFilter) {
		return  RI_BESSELFILTER;
	} else if (func == RiDiskFilter) {
		return  RI_DISKFILTER;
	}

	return	RI_GAUSSIANFILTER;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	getStepFilter
// Description			:	Return the filter matching the name
// Return Value			:
// Comments				:
RtStepFilterFunc		CRenderer::getStepFilter(const char *name) {
	if (strcmp(name,RI_GAUSSIANFILTER) == 0) {
		return	RiGaussianStepFilter;
	} else if (strcmp(name,RI_BOXFILTER) == 0) {
		return	RiBoxStepFilter;
	} else if (strcmp(name,RI_TRIANGLEFILTER) == 0) {
		return	RiTriangleStepFilter;
/*	} else if (strcmp(name,RI_SINCFILTER) == 0) {
		return	RiSincFilter;*/
	} else if (strcmp(name,RI_CATMULLROMFILTER) == 0) {
		return	RiCatmullRomStepFilter;
/*	} else if (strcmp(name,RI_BLACKMANHARRISFILTER) == 0) {
		return	RiBlackmanHarrisFilter;*/
	} else if (strcmp(name,RI_MITCHELLFILTER) == 0) {
		return	RiMitchellStepFilter;
	}

	return	RiGaussianStepFilter;
}


///////////////////////////////////////////////////////////////////////
// Function				:	dsoLoadCallback
// Description			:	This function will be called for each module
// Return Value			:
// Comments				:
static	int	dsoLoadCallback(const char *file,void *ud) {
	void	*module		=	osLoadModule(file);

	if (module != NULL) {
		int				i;
		void			**userData	=	(void **) ud;
		char			*name		=	(char *) userData[0];
		char			*prototype	=	(char *) userData[1];
		SHADEOP_SPEC	*shadeops;

		{
			char	tmp[OS_MAX_PATH_LENGTH];

			sprintf(tmp,"%s_shadeops",name);

			shadeops	=	(SHADEOP_SPEC *)	osResolve(module,tmp);
		}

		if (shadeops != NULL) {
			for (i=0;;i++) {
				char	*dsoName,*dsoPrototype;

				if (strcmp(shadeops[i].definition,"") == 0)	break;

				if (dsoParse(shadeops[i].definition,dsoName,dsoPrototype) == TRUE) {
					if (strcmp(dsoPrototype,prototype) == 0) {
						dsoInitFunction		*init		=	(dsoInitFunction *) userData[2];
						dsoExecFunction		*exec		=	(dsoExecFunction *) userData[3];
						dsoCleanupFunction	*cleanup	=	(dsoCleanupFunction *) userData[4];

						// Bingo
						init[0]		=	(dsoInitFunction)		osResolve(module,shadeops[i].init);
						exec[0]		=	(dsoExecFunction)		osResolve(module,dsoName);
						cleanup[0]	=	(dsoCleanupFunction)	osResolve(module,shadeops[i].cleanup);

						if (exec != NULL) {
							free(dsoName);
							free(dsoPrototype);

							// We have found the DSO
							return FALSE;
						}
					}

					free(dsoName);
					free(dsoPrototype);
				}
			}
		}

		osUnloadModule(module);
	} else {
		error(CODE_SYSTEM,"Failed to load DSO \"%s\": %s\n",file,osModuleError());
	}

	// Continue iterating
	return TRUE;
}




///////////////////////////////////////////////////////////////////////
// Class				:	CRenderer
// Method				:	getDSO
// Description			:	Load a DSO matching the prototyoe
// Return Value			:
// Comments				:	This function does not need to be thread safe
CDSO				*CRenderer::getDSO(const char *name,const char *prototype) {
	CDSO				*cDso;

	assert(name != NULL);
	
	// Check if the DSO had been loaded before
	for (cDso=dsos;cDso!=NULL;cDso=cDso->next) {
		if (strcmp(cDso->name,name) == 0) {
			if (strcmp(cDso->prototype,prototype) == 0) {
				return	cDso;
			}
		}
	}	
	
	dsoInitFunction		init;
	dsoExecFunction		exec;
	dsoCleanupFunction	cleanup;

	init		=	NULL;
	exec		=	NULL;
	cleanup		=	NULL;

	void	*userData[5];
	userData[0]	=	(void *) name;
	userData[1]	=	(void *) prototype;
	userData[2]	=	&init;
	userData[3]	=	&exec;
	userData[4]	=	&cleanup;

	// Go over the directories
	TSearchpath			*inPath	=	proceduralPath;
	char				searchPath[OS_MAX_PATH_LENGTH];
	for (;inPath!=NULL;inPath=inPath->next) {
		sprintf(searchPath,"%s*.%s",inPath->directory,osModuleExtension);
		osEnumerate(searchPath,dsoLoadCallback,userData);
	}

	if (exec != NULL) {
		void	*handle;

		// OK, we found the shader
		if (init !=	NULL)	handle	=	init(0,NULL);
		else				handle	=	NULL;

		// Save the DSO
		cDso			=	new CDSO;
		cDso->init		=	init;
		cDso->exec		=	exec;
		cDso->cleanup	=	cleanup;
		cDso->handle	=	handle;
		cDso->name		=	strdup(name);
		cDso->prototype	=	strdup(prototype);
		cDso->next		=	CRenderer::dsos;
		CRenderer::dsos	=	cDso;

		return cDso;
	}

	return NULL;
}

