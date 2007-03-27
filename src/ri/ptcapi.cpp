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




PtcPointCloud PtcCreatePointCloudFile(char *filename, int nvars, char **vartypes, char **varnames,float *world2eye, float *world2ndc, float *format) {
		
	PtcPointCloudInternal *ptcInternal = new PtcPointCloudInternal;
	
	ptcInternal->ptc = new CPointCloud(filename,world2eye,world2ndc,nvars,varnames,vartypes,TRUE);
	
	ptcInternal->numPoints		=	0;
	ptcInternal->curPoint		=	0;
	
	return (PtcPointCloud) ptcInternal;
}

void PtcWriteDataPoint(PtcPointCloud pointcloud, float *point, float *normal, float radius, float *data) {
	
	PtcPointCloudInternal *ptcInternal = (PtcPointCloudInternal *) pointcloud;
	
	ptcInternal->ptc->store(data,point,normal,radius);
	
	ptcInternal->numPoints++;
	ptcInternal->curPoint++;
}

void PtcFinishPointCloudFile(PtcPointCloud pointcloud) {
	PtcPointCloudInternal *ptcInternal = (PtcPointCloudInternal *) pointcloud;

	// Will write out the point cloud
	delete	ptcInternal->ptc;
		
	delete	ptcInternal;
}





PtcPointCloud PtcOpenPointCloudFile(char *fileName, int *nvars, char **vartypes, char **varnames) {
	PtcPointCloudInternal *ptcInternal = new PtcPointCloudInternal;
	FILE *in;
	
	if ((in	=	ropen(fileName,"rb",filePointCloud,TRUE)) != NULL) {
		matrix from,to;
		identitym(from);
		identitym(to);
		
		ptcInternal->ptc			=	new CPointCloud(fileName,from,to,in);
		ptcInternal->numPoints		=	0;
		ptcInternal->curPoint		=	0;
		
		ptcInternal->ptc->queryChannels(nvars,vartypes,varnames);
		
		ptcInternal->numPoints	=	ptcInternal->ptc->getNumPoints();
		ptcInternal->curPoint	=	0;
	} else {
		delete ptcInternal;
		return NULL;
	}
}

int PtcGetPointCloudInfo(PtcPointCloud pointcloud, char *request, void *result) {
	PtcPointCloudInternal *ptcInternal = new PtcPointCloudInternal;

	if (strcmp(request,"npoints") == 0) {
		((float*)result)[0] = ptcInternal->numPoints;
	} else if(strcmp(request,"bbox") == 0) {
		float *bmin = ((float*)result);
		float *bmax = bmin + 3;
		ptcInternal->ptc->bound(bmin,bmax);
	} else if(strcmp(request,"datasize") == 0) {
		int *ds = ((int*) result);
		ds[0] = ptcInternal->ptc->getDataSize();		
	} else {
		error(CODE_BADTOKEN,"unknown PtcGetPointCloudInfo request \"%s\"\n",request);
	}
/*	"world2eye"
	"world2ndc"
	"format"
*/
}

int PtcReadDataPoint(PtcPointCloud pointcloud, float *point, float *normal, float *radius, float *data) {
	PtcPointCloudInternal *ptcInternal = new PtcPointCloudInternal;
	
	if (ptcInternal->curPoint < ptcInternal->numPoints) return 1;
	
	ptcInternal->ptc->getPoint(ptcInternal->curPoint++,data,point,normal,radius);
	return 0;
}

void PtcClosePointCloudFile(PtcPointCloud pointcloud) {
		PtcPointCloudInternal *ptcInternal = (PtcPointCloudInternal *) pointcloud;

	// Will write out the point cloud
	delete	ptcInternal->ptc;
		
	delete	ptcInternal;
}
