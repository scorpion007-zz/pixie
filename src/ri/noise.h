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
//  File				:	noise.h
//  Classes				:	-
//  Description			:	The misc noise functions
//
////////////////////////////////////////////////////////////////////////
#ifndef NOISE_H
#define NOISE_H

#include "common/global.h"

void							noiseNormalize2(float *);
void							noiseNormalize3(float *);
void							noiseNormalize4(float *);

float							noiseFloat(float);
float							noiseFloat(float,float);
float							noiseFloat(const float *);
float							noiseFloat(const float *,float);
void							noiseVector(float *,float);
void							noiseVector(float *,float,float);
void							noiseVector(float *,const float *);
void							noiseVector(float *,const float *,float);

float							pnoiseFloat(float,float);
float							pnoiseFloat(float,float,float,float);
float							pnoiseFloat(const float *,const float *);
float							pnoiseFloat(const float *,float,const float *,float);
void							pnoiseVector(float *,float,float);
void							pnoiseVector(float *,float,float,float,float);
void							pnoiseVector(float *,const float *,const float *);
void							pnoiseVector(float *,const float *,float,const float *,float);

float							cellNoiseFloat(float);
float							cellNoiseFloat(float,float);
float							cellNoiseFloat(const float *);
float							cellNoiseFloat(const float *,float);
void							cellNoiseVector(float *,float);
void							cellNoiseVector(float *,float,float);
void							cellNoiseVector(float *,const float *);
void							cellNoiseVector(float *,const float *,float);


#endif





