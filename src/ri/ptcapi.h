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
#ifndef _PTCAPI_H_
#define _PTCAPI_H_

#ifndef LIB_EXPORT
#ifdef _WINDOWS
#define	LIB_EXPORT				__declspec(dllexport)
#else
#define	LIB_EXPORT				extern
#endif
#endif


typedef void *PtcPointCloud;

#ifdef __cplusplus
extern "C" {
#endif

	// Create a blank point cloud with nvars channels
	LIB_EXPORT	PtcPointCloud PtcCreatePointCloudFile(char *filename, int nvars, const char **vartypes, const char **varnames,
			   	float *world2eye, float *world2ndc, float *format);

	// Write a point to the file
	LIB_EXPORT	void PtcWriteDataPoint(PtcPointCloud pointcloud, float *point, float *normal, float radius, float *data);

	// Finish an close the file
	LIB_EXPORT	void PtcFinishPointCloudFile(PtcPointCloud pointcloud);

	// Open an existing point cloud
	LIB_EXPORT	PtcPointCloud PtcOpenPointCloudFile(char *filename, int *nvars, char **vartypes, char **varnames);

	// Get info on the point cloud
	LIB_EXPORT	int PtcGetPointCloudInfo(PtcPointCloud pointcloud, const char *request, void *result);

	// Read a single point
	LIB_EXPORT	int PtcReadDataPoint(PtcPointCloud pointcloud, float *point, float *normal, float *radius, float *data);

	// Close the file
	LIB_EXPORT	void PtcClosePointCloudFile(PtcPointCloud pointcloud);

#ifdef __cplusplus
};
#endif

#endif //_PTCAPI_H_

