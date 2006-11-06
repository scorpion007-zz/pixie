//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright � 1999 - 2003, Okan Arikan
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
//  File				:	objectMisc.h
//  Classes				:	-
//  Description			:	Some misc inline functions
//
////////////////////////////////////////////////////////////////////////
#ifndef OBJECTMISC_H
#define OBJECTMISC_H

///////////////////////////////////////////////////////////////////////
// Function				:	transform
// Description			:	Transform bunch of points from one space to another
// Return Value			:
// Comments				:
// Date last edited		:	3/11/2002
inline	void	transform(float *dest,const float *src,int num,const float *from) {
	int	i;

	for (i=num;i>0;i--) {
		mulmp(dest,from,src);
		src		+=	3;
		dest	+=	3;
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	transform
// Description			:	Transform bunch of points from one space to another
// Return Value			:
// Comments				:	In place version of the one above
// Date last edited		:	3/11/2002
inline	void	transform(float *src,int num,const float *from) {
	int		i;

	for (i=num;i>0;i--) {
		mulmp(src,from,src);
		src		+=	3;
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	transform
// Description			:	Transform bunch of points from one space to another
// Return Value			:
// Comments				:	This one also interpolates with a time constant
// Date last edited		:	3/11/2002
inline	void	transform(float *src,int num,const float *from0,const float *from1,const float *time) {
	int		i;
	vector	tmp0,tmp1;

	for (i=0;i<num;i++) {
		mulmp(tmp0,from0,src);
		mulmp(tmp1,from1,src);
		interpolatev(src,tmp0,tmp1,time[i]);
		src		+=	3;
	}
}



///////////////////////////////////////////////////////////////////////
// Function				:	vtransform
// Description			:	Transform bunch of vectors from one space to another
// Return Value			:
// Comments				:
// Date last edited		:	3/11/2002
inline	void	vtransform(float *src,int num,const float *from) {
	int		i;

	for (i=num;i>0;i--) {
		mulmv(src,from,src);
		src		+=	3;
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	vtransform
// Description			:	Transform bunch of vectors from one space to another
// Return Value			:
// Comments				:	This one also interpolates with a time constant
// Date last edited		:	3/11/2002
inline	void	vtransform(float *src,int num,const float *from0,const float *from1,const float *time) {
	vector	tmp0,tmp1;
	int		i;

	for (i=0;i<num;i++) {
		mulmv(tmp0,from0,src);
		mulmv(tmp1,from1,src);
		interpolatev(src,tmp0,tmp1,time[i]);
		src		+=	3;
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	ntransform
// Description			:	Transform bunch of normals from one space to another
// Return Value			:
// Comments				:
// Date last edited		:	3/11/2002
inline	void	ntransform(float *src,int num,const float *to) {
	int		i;

	for (i=num;i>0;i--) {
		mulmn(src,to,src);
		src		+=	3;
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	ntransform
// Description			:	Transform bunch of normals from one space to another
// Return Value			:
// Comments				:	This one also interpolates with a time constant
// Date last edited		:	3/11/2002
inline	void	ntransform(float *src,int num,const float *to0,const float *to1,const float *time) {
	vector	tmp0,tmp1;
	int		i;

	for (i=0;i<num;i++) {
		mulmn(tmp0,to0,src);
		mulmn(tmp1,to1,src);
		interpolatev(src,tmp0,tmp1,time[i]);
		src		+=	3;
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	interpolate
// Description			:	Interpolate bunch of floats
// Return Value			:
// Comments				:
// Date last edited		:	3/11/2002
inline	void	interpolate(int num,float *src0,const float *src1,const float *time) {
	int	i;

	for (i=num;i>0;i--) {
		src0[0]	=	src0[0] * (1-time[0])	+	src1[0] * time[0];
		time++;
		src0++;
		src1++;
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	interpolate
// Description			:	Interpolate bunch of points
// Return Value			:
// Comments				:
// Date last edited		:	3/11/2002
inline	void	interpolate3(int num,float *src0,const float *src1,const float *time) {
	int	i;

	for (i=num;i>0;i--) {
		src0[0]	=	src0[0] * (1-time[0])	+	src1[0] * time[0];
		src0[1]	=	src0[1] * (1-time[0])	+	src1[1] * time[0];
		src0[2]	=	src0[2] * (1-time[0])	+	src1[2] * time[0];
		time++;
		src0+=3;
		src1+=3;
	}
}

#endif





