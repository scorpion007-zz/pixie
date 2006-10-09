//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright © 1999 - 2003, Okan Arikan
//
// Contact: okan@cs.berkeley.edu
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
// 
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//
//  File				:	frameFiles.cpp
//  Classes				:	CFrame
//  Description			:
//
////////////////////////////////////////////////////////////////////////
#include <string.h>
#include <math.h>

#include "frame.h"
#include "renderer.h"
#include "error.h"
#include "texture.h"
#include "photonMap.h"
#include "radiance.h"
#include "irradiance.h"
#include "texture3d.h"
#include "remoteChannel.h"
#include "brickmap.h"
#include "pointCloud.h"




///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Method				:	locateFileEx
// Description			:	Locate a file on disk
// Return Value			:	TRUE if found
// Comments				:
// Date last edited		:	8/25/2002
int	CFrame::locateFileEx(char *result,const char *name,const char *extension,TSearchpath *searchpath) {
	if (strchr(name,'.') == NULL) {
		char	tmp[OS_MAX_PATH_LENGTH];

		sprintf(tmp,"%s.%s",name,extension);

		return locateFile(result,tmp,searchpath);
	} else {
		return locateFile(result,name,searchpath);
	}
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Method				:	locateFile
// Description			:	Locate a file on disk
// Return Value			:	TRUE if found
// Comments				:
// Date last edited		:	8/25/2002
int	CFrame::locateFile(char *result,const char *name,TSearchpath *searchpath) {

	if (netClient != INVALID_SOCKET) {
		// check netfile mappings
		CNetFileMapping* mapping;
		if (netFileMappings->find(name,mapping)) {
			name = mapping->to;
		}
	}
	
	// Check if the file exists
	if (osFileExists(name)) {
		strcpy(result,name);
		info(CODE_RESOLUTION,"\"%s\" -> \"%s\"\n",name,name);
		return TRUE;
	}

	
	for (;searchpath!=NULL;searchpath=searchpath->next) {
		sprintf(result,"%s%s",searchpath->directory,name);
		osFixSlashes(result);
		if (osFileExists(result)) {
			info(CODE_RESOLUTION,"\"%s\" -> \"%s\"\n",name,result);
			return TRUE;
		}
	}

	// Unable to find the file, check the network
	// Check the net if we can find the file
	if (netClient != INVALID_SOCKET) {
		if (getFile(result,name) == TRUE) {
			if (osFileExists(result)) {
				info(CODE_RESOLUTION,"\"%s\" -> \"%s\"\n",name,result);
				return TRUE;
			}
		}
	}

	info(CODE_RESOLUTION,"\"%s\" -> ???\n",name);

	return FALSE;
}




///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Method				:	getTexture
// Description			:	Load a texture from file
// Return Value			:
// Comments				:
// Date last edited		:	8/25/2002
CTexture	*CFrame::getTexture(const char *name) {
	CFileResource	*tex;

	if (loadedFiles->find(name,tex) == FALSE){
		// Load the texture
		tex	=	currentRenderer->textureLoad(name,options.texturePath);

		if (tex == NULL)	{
			// Not found, substitude with a dummy one
			error(CODE_NOFILE,"Unable open texture \"%s\"\n",name);
			tex					=	new CTexture(name,128,128,TEXTURE_PERIODIC,TEXTURE_PERIODIC);
		}

		loadedFiles->insert(tex->name,tex);
	}

	return (CTexture *) tex;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Method				:	getEnvironment
// Description			:	Load an environment map (which can also be a shadow map)
// Return Value			:
// Comments				:
// Date last edited		:	8/25/2002
CEnvironment	*CFrame::getEnvironment(const char *name) {
	CFileResource	*tex;

	if (loadedFiles->find(name,tex) == FALSE){
		tex	=	currentRenderer->environmentLoad(name,options.texturePath,toWorld);

		if (tex == NULL)	{
			// Not found, substitude with a dummy one
			error(CODE_NOFILE,"Unable open environment \"%s\"\n",name);
			tex					=	new CEnvironment(name);
		}

		loadedFiles->insert(tex->name,tex);
	}

	return (CEnvironment *) tex;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Method				:	getPhotonMap
// Description			:	Load a photon map
// Return Value			:
// Comments				:
// Date last edited		:	3/11/2003
CPhotonMap		*CFrame::getPhotonMap(const char *name) {
	CFileResource	*map;
	char			fileName[OS_MAX_PATH_LENGTH];
	FILE			*in;

	// Check the cache to see if the file is in the memory
	if (loadedFiles->find(name,map) == FALSE){

		// Locate the file
		if (locateFile(fileName,name,options.texturePath)) {
			// Try to open the file
			in		=	ropen(fileName,"rb",filePhotonMap,TRUE);
		} else {
			in		=	NULL;
		}

		// Read it
		map		=	new CPhotonMap(name,world,in);
		loadedFiles->insert(map->name,map);
	}

	return (CPhotonMap *) map;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Method				:	getCache
// Description			:	Load a cache
// Return Value			:
// Comments				:
// Date last edited		:	3/11/2003
CCache		*CFrame::getCache(const char *name,const char *mode) {
	CFileResource	*cache;
	
	// Check the memory first
	if (loadedFiles->find(name,cache) == FALSE){
		char				fileName[OS_MAX_PATH_LENGTH];
		int					flags;
		char				type[128];
		int					createChannel = FALSE;
		CIrradianceCache	*icache = NULL;
		CRadianceCache		*rcache = NULL;

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
			if (locateFile(fileName,name,options.texturePath)) {
				FILE	*in	=	ropen(fileName,type);

				if (in != NULL) {
					// If we're netrendering and writing, treat specially
					if ((netClient != INVALID_SOCKET) && (flags & CACHE_WRITE)) {
						flags			&=	~CACHE_WRITE;		// don't flush cache to disk
						createChannel	=	TRUE;
						if (strncmp(fileName,options.temporaryPath,strlen(options.temporaryPath)) == 0) {
							// it's a temp file, delete it after we're done
							registerFrameTemporary(fileName,TRUE);
						}
						// always remove the file mapping when writing
						registerFrameTemporary(name,FALSE);
					}
					
					// Create the cache
					if (strcmp(type,fileIrradianceCache) == 0) {
						cache	=	icache	=	new CIrradianceCache(name,flags,worldBmin,worldBmax,world,hierarchy,in);
					} else if (strcmp(type,fileGatherCache) == 0) {
						cache	=	rcache	=	new CRadianceCache(name,flags,worldBmin,worldBmax,hierarchy,in,triangles);
					} else {
						error(CODE_BUG,"This seems to be a Pixie file of unrecognised type (%s)\n",name);
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
			if (options.flags & OPTIONS_FLAGS_USE_RADIANCE_CACHE) {
				cache	=	rcache	=	new CRadianceCache(name,flags,worldBmin,worldBmax,hierarchy,NULL,triangles);
			} else {
				cache	=	icache	=	new CIrradianceCache(name,flags,worldBmin,worldBmax,world,hierarchy,NULL);
			}
		}
		
		// Create channels if possible
		if (createChannel == TRUE) {
			if (icache != NULL) {
				requestRemoteChannel(new CRemoteICacheChannel(icache));
			} else if (rcache != NULL) {
				error(CODE_LIMIT,"Radiancecache file \"%s\" cannot be written to in paralell / network renders\n",name);

				// Prevent crashes caused by unwritable empty cache
				delete cache;
				flags |= CACHE_WRITE;
				osTempname(options.temporaryPath,"rndr",fileName);
				cache = new CRadianceCache(fileName,flags,worldBmin,worldBmax,hierarchy,NULL,triangles);
			}
		}

		loadedFiles->insert(cache->name,cache);
	}

	return (CCache *) cache;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Method				:	getTextureInfo
// Description			:	Load a texture from file
// Return Value			:
// Comments				:
// Date last edited		:	02/22/2006
CTextureInfoBase	*CFrame::getTextureInfo(const char *name) {
	CFileResource	*tex;

	if (loadedFiles->find(name,tex) == FALSE){
		// try environments first
		tex	=	currentRenderer->environmentLoad(name,options.texturePath,toWorld);

		if (tex == NULL)	{
			// else try as textures
			tex	=	currentRenderer->textureLoad(name,options.texturePath);
		}

		if (tex != NULL) {
			// only store the result if found
			loadedFiles->insert(tex->name,tex);
		}
	}

	return (CTextureInfoBase *) tex;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Method				:	getTexture3d
// Description			:	Get a point cloud or brickmap
// Return Value			:
// Comments				:
// Date last edited		:	02/22/2006
CTexture3d			*CFrame::getTexture3d(const char *name,int write,const char* channels,const float *from,const float *to) {
	CFileResource	*texture3d;
	char			fileName[OS_MAX_PATH_LENGTH];
	FILE			*in;

	if (loadedFiles->find(name,texture3d) == FALSE){
	
		CXform *xform = world;
		/*
		if (coordsys != NULL) {
			ECoordinateSystem	esys;
			matrix				*from,*to;
			
			// non worldspace texture
			xform = new CXform();
			findCoordinateSystem(coordsys,from,to,esys);
	
			movmm(xform->from,from[0]);	// construct the transform to put us in the desired system
			movmm(xform->to,to[0]);
		}
		*/
		
		// If we are writing, it must be a point cloud
		if (write == TRUE) {
			
			if (netClient != INVALID_SOCKET) {
				CPointCloud	*cloud	=	new CPointCloud(name,xform,channels,FALSE);
				texture3d			=	cloud;
			
				// Ensure we unmap the file when done.  Do not delete it
				// as we mark the file to never be written in the server
				registerFrameTemporary(name,FALSE);
				requestRemoteChannel(new CRemotePtCloudChannel(cloud));
			} else {
				// alloate a point cloud which will be written to disk
				CXform *dummy = new CXform;
				texture3d	=	new CPointCloud(name,xform,channels,TRUE);
			}
			
		} else {
			// Locate the file
			if (locateFile(fileName,name,options.texturePath)) {
				// Try to open the file
				if ((in	=	ropen(fileName,"rb",filePointCloud,TRUE)) != NULL) {
					CXform *dummy = new CXform;
					texture3d	=	new CPointCloud(name,xform,in);
				} else {
					if ((in	=	ropen(fileName,"rb",fileBrickMap,TRUE)) != NULL) {
						texture3d	=	new CBrickMap(in,name,xform);
					}
				}
			} else {
				in		=	NULL;
			}
			
			if (in == NULL) {
				// allocate a dummy blank-channel point cloud
				error(CODE_BADTOKEN,"Cannot find or open Texture3d file \"%s\"\n",name);
				texture3d	=	new CPointCloud(name,xform,NULL,FALSE);
				// remove the dummy mapping once the frame ends
				registerFrameTemporary(name,FALSE);
			}
		}
		
		// tidy up in case something went wrong
		xform->check();
		
		loadedFiles->insert(texture3d->name,texture3d);
	}

	return (CPointCloud *) texture3d;
}


///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Method				:	getFilter
// Description			:	Return the filter matching the name
// Return Value			:
// Comments				:
// Date last edited		:	8/25/2002
RtFilterFunc			CFrame::getFilter(const char *name) {
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
	}

	return	RiGaussianFilter;
}

///////////////////////////////////////////////////////////////////////
// Class				:	CFrame
// Method				:	getFilter
// Description			:	Return the name matching the filter
// Return Value			:
// Comments				:
// Date last edited		:	8/25/2002
char					*CFrame::getFilter(RtFilterFunc func) {
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
	}

	return	RI_GAUSSIANFILTER;
}




