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
//  File				:	ptcapi.h
//  Classes				:
//  Description			:	Point Cloud API
//
////////////////////////////////////////////////////////////////////////
#include "fileResource.h"
#include "pointCloud.h"
#include "error.h"

#include "ptcapi.h"


struct PtcPointCloudInternal {
	CPointCloud			*ptc;
	int					curPoint,numPoints;
};




///////////////////////////////////////////////////////////////////////
// Function				:	PtcCreatePointCloudFile
// Description			:	Create a point cloud file
// Return Value			:
// Comments				:	Handle
PtcPointCloud PtcCreatePointCloudFile(char *filename, int nvars, char **vartypes, char **varnames,float *world2eye, float *world2ndc, float *format) {		
	PtcPointCloudInternal *ptcInternal = new PtcPointCloudInternal;
	
	matrix eye2world;
	invertm(eye2world,world2eye);
	
	ptcInternal->ptc			=	new CPointCloud(filename,eye2world,world2eye,world2ndc,nvars,varnames,vartypes,TRUE);
	ptcInternal->numPoints		=	0;
	ptcInternal->curPoint		=	0;
	
	return (PtcPointCloud) ptcInternal;
}

///////////////////////////////////////////////////////////////////////
// Function				:	PtcWriteDataPoint
// Description			:	Write into a point cloud file
// Return Value			:
// Comments				:
void PtcWriteDataPoint(PtcPointCloud pointcloud, float *point, float *normal, float radius, float *data) {
	PtcPointCloudInternal *ptcInternal = (PtcPointCloudInternal *) pointcloud;
	
	ptcInternal->ptc->store(data,point,normal,radius);
	
	ptcInternal->numPoints++;
	ptcInternal->curPoint++;
}

///////////////////////////////////////////////////////////////////////
// Function				:	PtcFinishPointCloudFile
// Description			:	Close the handle
// Return Value			:
// Comments				:
void PtcFinishPointCloudFile(PtcPointCloud pointcloud) {
	PtcPointCloudInternal *ptcInternal = (PtcPointCloudInternal *) pointcloud;

	// Will write out the point cloud
	delete	ptcInternal->ptc;
		
	delete	ptcInternal;
}





///////////////////////////////////////////////////////////////////////
// Function				:	PtcOpenPointCloudFile
// Description			:	Open an existing point cloud file
// Return Value			:
// Comments				:	Handle
PtcPointCloud PtcOpenPointCloudFile(char *fileName, int *nvars, const char **vartypes, const char **varnames) {
	PtcPointCloudInternal	*ptcInternal = new PtcPointCloudInternal;
	FILE					*in;
	
	if ((in	=	ropen(fileName,"rb",filePointCloud,TRUE)) != NULL) {
		matrix from,to;
		identitym(from);
		identitym(to);
		
		ptcInternal->ptc			=	new CPointCloud(fileName,from,to,in);
		
		ptcInternal->ptc->queryChannels(nvars,vartypes,varnames);
		
		ptcInternal->numPoints		=	ptcInternal->ptc->getNumPoints()-1;
		ptcInternal->curPoint		=	1;	// First point is dummy
	} else {
		delete ptcInternal;
		return NULL;
	}

	return (PtcPointCloud) ptcInternal;
}

///////////////////////////////////////////////////////////////////////
// Function				:	PtcGetPointCloudInfo
// Description			:	Query the point cloud
// Return Value			:
// Comments				:	Handle
int PtcGetPointCloudInfo(PtcPointCloud pointcloud, const char *request, void *result) {
	PtcPointCloudInternal *ptcInternal = (PtcPointCloudInternal *) pointcloud;

	if (strcmp(request,"npoints") == 0) {
		((int*)result)[0] = ptcInternal->numPoints;
	} else if(strcmp(request,"bbox") == 0) {
		float *bmin = ((float*)result);
		float *bmax = bmin + 3;
		ptcInternal->ptc->bound(bmin,bmax);
	} else if(strcmp(request,"datasize") == 0) {
		int *ds = ((int*) result);
		ds[0] = ptcInternal->ptc->getDataSize();		
	} else if(strcmp(request,"world2eye") == 0) {
		float *from = ((float*) result);
		ptcInternal->ptc->getFromMatrix(from);
	} else if(strcmp(request,"world2ndc") == 0) {
		float *tondc = ((float*) result);
		ptcInternal->ptc->getNDCMatrix(tondc);
	} else if(strcmp(request,"format") == 0) {
		float *fmt = ((float*) result);
		fmt[0] = fmt[1] = fmt[2] = 1;
		
		//warning(CODE_UNIMPLEMENT,"format request is not supported\"%s\"\n",request);
		// Don't use warning or error as Ri may not be initialized
		fprintf(stderr,"format request is not supported\n");
	} else {
		//error(CODE_BADTOKEN,"Unknown PtcGetPointCloudInfo request \"%s\"\n",request);
		// Don't use warning or error as Ri may not be initialized
		fprintf(stderr,"Unknown PtcGetPointCloudInfo request \"%s\"\n",request);
	}

	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// Function				:	PtcReadDataPoint
// Description			:	Read data from the point cloud
// Return Value			:
// Comments				:
int PtcReadDataPoint(PtcPointCloud pointcloud, float *point, float *normal, float *radius, float *data) {
	PtcPointCloudInternal *ptcInternal = (PtcPointCloudInternal *) pointcloud;
	
	if (ptcInternal->curPoint >= ptcInternal->numPoints) return FALSE;
	
	ptcInternal->ptc->getPoint(ptcInternal->curPoint++,data,point,normal,radius);
	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// Function				:	PtcClosePointCloudFile
// Description			:	Close the handle
// Return Value			:
// Comments				:
void PtcClosePointCloudFile(PtcPointCloud pointcloud) {
	PtcPointCloudInternal *ptcInternal = (PtcPointCloudInternal *) pointcloud;

	// Will write out the point cloud
	delete	ptcInternal->ptc;
		
	delete	ptcInternal;
}

