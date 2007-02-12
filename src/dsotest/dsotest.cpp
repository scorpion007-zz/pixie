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
//  File				:	dsotest
//  Classes				:	-
//  Description			:	Just a sample DSO file
//
//
//
//
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "common/global.h"
#include "common/algebra.h"
#include "ri/shadeop.h"


// Just returns a red color
SHADEOP_TABLE(red) =	{
	{"color	red1()",	"",	""},
	{""}
};

SHADEOP(red1) {
	float	*result	=	(float *) argv[0];

	result[0]	=	1;
	result[1]	=	0;
	result[2]	=	0;
}


// Just returns a green color
SHADEOP_TABLE(green) =	{
	{"color	green1()",	"",	""},
	{""}
};

SHADEOP(green1) {
	float	*result	=	(float *) argv[0];

	result[0]	=	0;
	result[1]	=	1;
	result[2]	=	0;
}

