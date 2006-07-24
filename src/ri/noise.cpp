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
//  File				:	noise.cpp
//  Classes				:	-
//  Description			:	The misc noise functions
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "common/algebra.h"
#include "common/os.h"
#include "noise.h"

// Noise tables
#include "noiseTables.h"

// The code is lifted from perlin
#define			s_curve(t) ((float) ( t * t * (3. - 2. * t) ))

#define			lerp(t, a, b) ( a + t * (b - a) )

// FIXME: NOISEMIN is creating a numerical problem here
// FIXME: I don't see any reason to use it
#define			setup(i,b0,b1,r0,r1)	\
	t = ((float) (vec[i]));				\
	b0 = ((int) floor(t)) & NOISEMASK;	\
	b1 = (b0+1) & NOISEMASK;			\
	r0 = t - (int) floor(t);			\
	r1 = ((float) (r0 - 1.));

///////////////////////////////////////////////////////////////////////
// Function				:	noiseFloat1D
// Description			:
// Return Value			:
// Comments				:
// Date last edited		:	3/13/2001
float noiseFloat(float arg) {
	int bx0, bx1;
	float rx0, rx1, sx, t, u, v, vec[1];

	vec[0] = arg;

	setup(0, bx0,bx1, rx0,rx1);

	sx = s_curve(rx0);

	u = rx0 * g1[ p[ bx0 ] ];
	v = rx1 * g1[ p[ bx1 ] ];

	return (lerp(sx, u, v) + (float) 1)*((float) 0.5);
}

///////////////////////////////////////////////////////////////////////
// Function				:	noiseFloat2D
// Description			:
// Return Value			:
// Comments				:
// Date last edited		:	3/13/2001
float noiseFloat(float uarg,float varg)
{
	int bx0, bx1, by0, by1, b00, b10, b01, b11;
	float rx0, rx1, ry0, ry1, *q, sx, sy, a, b, t, u, v, vec[2];
	//register int i, j;
	int i, j;

	vec[0]	=	uarg;
	vec[1]	=	varg;

	setup(0, bx0,bx1, rx0,rx1);
	setup(1, by0,by1, ry0,ry1);

	i = p[ bx0 ];
	j = p[ bx1 ];

	b00 = p[ i + by0 ];
	b10 = p[ j + by0 ];
	b01 = p[ i + by1 ];
	b11 = p[ j + by1 ];

	sx = s_curve(rx0);
	sy = s_curve(ry0);

#define at2(rx,ry) ( rx * q[0] + ry * q[1] )

	q = g2[ b00 ] ; u = at2(rx0,ry0);
	q = g2[ b10 ] ; v = at2(rx1,ry0);
	a = lerp(sx, u, v);

	q = g2[ b01 ] ; u = at2(rx0,ry1);
	q = g2[ b11 ] ; v = at2(rx1,ry1);
	b = lerp(sx, u, v);

	return (lerp(sy, a, b)+(float) 1)*((float) 0.5);
}

///////////////////////////////////////////////////////////////////////
// Function				:	noiseFloat3D
// Description			:
// Return Value			:
// Comments				:
// Date last edited		:	3/13/2001
float noiseFloat(const float *vec)
{
	int bx0, bx1, by0, by1, bz0, bz1, b00, b10, b01, b11;
	float rx0, rx1, ry0, ry1, rz0, rz1, *q, sy, sz, a, b, c, d, t, u, v;
	register int i, j;

	setup(0, bx0,bx1, rx0,rx1);
	setup(1, by0,by1, ry0,ry1);
	setup(2, bz0,bz1, rz0,rz1);

	i = p[ bx0 ];
	j = p[ bx1 ];

	b00 = p[ i + by0 ];
	b10 = p[ j + by0 ];
	b01 = p[ i + by1 ];
	b11 = p[ j + by1 ];

	t  = s_curve(rx0);
	sy = s_curve(ry0);
	sz = s_curve(rz0);

#define at3(rx,ry,rz) ( rx * q[0] + ry * q[1] + rz * q[2] )

	q = g3[ b00 + bz0 ] ; u = at3(rx0,ry0,rz0);
	q = g3[ b10 + bz0 ] ; v = at3(rx1,ry0,rz0);
	a = lerp(t, u, v);

	q = g3[ b01 + bz0 ] ; u = at3(rx0,ry1,rz0);
	q = g3[ b11 + bz0 ] ; v = at3(rx1,ry1,rz0);
	b = lerp(t, u, v);

	c = lerp(sy, a, b);

	q = g3[ b00 + bz1 ] ; u = at3(rx0,ry0,rz1);
	q = g3[ b10 + bz1 ] ; v = at3(rx1,ry0,rz1);
	a = lerp(t, u, v);

	q = g3[ b01 + bz1 ] ; u = at3(rx0,ry1,rz1);
	q = g3[ b11 + bz1 ] ; v = at3(rx1,ry1,rz1);
	b = lerp(t, u, v);

	d = lerp(sy, a, b);

	return (lerp(sz, c, d) + (float) 1)*((float) 0.5);
}

///////////////////////////////////////////////////////////////////////
// Function				:	noiseVector1D
// Description			:
// Return Value			:
// Comments				:
// Date last edited		:
void noiseVector(float *r,float arg)
{
	int bx0, bx1;
	float rx0, rx1, sx, t, u, v, vec[1];

	vec[0] = arg;

	setup(0, bx0,bx1, rx0,rx1);

	sx = s_curve(rx0);

	u = rx0 * g1[ p[ bx0 ] ];
	v = rx1 * g1[ p[ bx1 ] ];

	r[0] =  (lerp(sx, u, v) + (float) 1)*((float) 0.5);

	u = rx0 * g1[ p2[ bx0 ] ];
	v = rx1 * g1[ p2[ bx1 ] ];

	r[1] =  (lerp(sx, u, v) + (float) 1)*((float) 0.5);

	u = rx0 * g1[ p3[ bx0 ] ];
	v = rx1 * g1[ p3[ bx1 ] ];

	r[2] =  (lerp(sx, u, v) + (float) 1)*((float) 0.5);
}

///////////////////////////////////////////////////////////////////////
// Function				:	noiseVector2D
// Description			:
// Return Value			:
// Comments				:
// Date last edited		:
void noiseVector(float *r,float uarg,float varg)
{
	int bx0, bx1, by0, by1, b00, b10, b01, b11;
	float rx0, rx1, ry0, ry1, *q, sx, sy, a, b, t, u, v, vec[2];
	register int i, j;

	vec[0]	=	uarg;
	vec[1]	=	varg;

	setup(0, bx0,bx1, rx0,rx1);
	setup(1, by0,by1, ry0,ry1);

	i = p[ bx0 ];
	j = p[ bx1 ];

	b00 = p[ i + by0 ];
	b10 = p[ j + by0 ];
	b01 = p[ i + by1 ];
	b11 = p[ j + by1 ];

	sx = s_curve(rx0);
	sy = s_curve(ry0);

	q = g2[ b00 ] ; u = at2(rx0,ry0);
	q = g2[ b10 ] ; v = at2(rx1,ry0);
	a = lerp(sx, u, v);

	q = g2[ b01 ] ; u = at2(rx0,ry1);
	q = g2[ b11 ] ; v = at2(rx1,ry1);
	b = lerp(sx, u, v);

	r[0] = (lerp(sy, a, b) + (float) 1)*((float) 0.5);

	i = p2[ bx0 ];
	j = p2[ bx1 ];

	b00 = p2[ i + by0 ];
	b10 = p2[ j + by0 ];
	b01 = p2[ i + by1 ];
	b11 = p2[ j + by1 ];

	sx = s_curve(rx0);
	sy = s_curve(ry0);

	q = g2[ b00 ] ; u = at2(rx0,ry0);
	q = g2[ b10 ] ; v = at2(rx1,ry0);
	a = lerp(sx, u, v);

	q = g2[ b01 ] ; u = at2(rx0,ry1);
	q = g2[ b11 ] ; v = at2(rx1,ry1);
	b = lerp(sx, u, v);

	r[1] = (lerp(sy, a, b) + (float) 1)*((float) 0.5);

	i = p3[ bx0 ];
	j = p3[ bx1 ];

	b00 = p3[ i + by0 ];
	b10 = p3[ j + by0 ];
	b01 = p3[ i + by1 ];
	b11 = p3[ j + by1 ];

	sx = s_curve(rx0);
	sy = s_curve(ry0);

	q = g2[ b00 ] ; u = at2(rx0,ry0);
	q = g2[ b10 ] ; v = at2(rx1,ry0);
	a = lerp(sx, u, v);

	q = g2[ b01 ] ; u = at2(rx0,ry1);
	q = g2[ b11 ] ; v = at2(rx1,ry1);
	b = lerp(sx, u, v);

	r[2] = (lerp(sy, a, b) + (float) 1)*((float) 0.5);
}

///////////////////////////////////////////////////////////////////////
// Function				:	noiseVector3D
// Description			:
// Return Value			:
// Comments				:
// Date last edited		:
void noiseVector(float *r,const float *vec)
{
	int bx0, bx1, by0, by1, bz0, bz1, b00, b10, b01, b11;
	float rx0, rx1, ry0, ry1, rz0, rz1, *q, sy, sz, a, b, c, d, t, u, v;
	register int i, j;

	setup(0, bx0,bx1, rx0,rx1);
	setup(1, by0,by1, ry0,ry1);
	setup(2, bz0,bz1, rz0,rz1);

	i = p[ bx0 ];
	j = p[ bx1 ];

	b00 = p[ i + by0 ];
	b10 = p[ j + by0 ];
	b01 = p[ i + by1 ];
	b11 = p[ j + by1 ];

	t  = s_curve(rx0);
	sy = s_curve(ry0);
	sz = s_curve(rz0);

	q = g3[ b00 + bz0 ] ; u = at3(rx0,ry0,rz0);
	q = g3[ b10 + bz0 ] ; v = at3(rx1,ry0,rz0);
	a = lerp(t, u, v);

	q = g3[ b01 + bz0 ] ; u = at3(rx0,ry1,rz0);
	q = g3[ b11 + bz0 ] ; v = at3(rx1,ry1,rz0);
	b = lerp(t, u, v);

	c = lerp(sy, a, b);

	q = g3[ b00 + bz1 ] ; u = at3(rx0,ry0,rz1);
	q = g3[ b10 + bz1 ] ; v = at3(rx1,ry0,rz1);
	a = lerp(t, u, v);

	q = g3[ b01 + bz1 ] ; u = at3(rx0,ry1,rz1);
	q = g3[ b11 + bz1 ] ; v = at3(rx1,ry1,rz1);
	b = lerp(t, u, v);

	d = lerp(sy, a, b);

	r[0] = (lerp(sz, c, d) + (float) 1)*((float) 0.5);

	i = p2[ bx0 ];
	j = p2[ bx1 ];

	b00 = p2[ i + by0 ];
	b10 = p2[ j + by0 ];
	b01 = p2[ i + by1 ];
	b11 = p2[ j + by1 ];

	t  = s_curve(rx0);
	sy = s_curve(ry0);
	sz = s_curve(rz0);

	q = g3[ b00 + bz0 ] ; u = at3(rx0,ry0,rz0);
	q = g3[ b10 + bz0 ] ; v = at3(rx1,ry0,rz0);
	a = lerp(t, u, v);

	q = g3[ b01 + bz0 ] ; u = at3(rx0,ry1,rz0);
	q = g3[ b11 + bz0 ] ; v = at3(rx1,ry1,rz0);
	b = lerp(t, u, v);

	c = lerp(sy, a, b);

	q = g3[ b00 + bz1 ] ; u = at3(rx0,ry0,rz1);
	q = g3[ b10 + bz1 ] ; v = at3(rx1,ry0,rz1);
	a = lerp(t, u, v);

	q = g3[ b01 + bz1 ] ; u = at3(rx0,ry1,rz1);
	q = g3[ b11 + bz1 ] ; v = at3(rx1,ry1,rz1);
	b = lerp(t, u, v);

	d = lerp(sy, a, b);

	r[1] = (lerp(sz, c, d) + (float) 1)*((float) 0.5);

	i = p3[ bx0 ];
	j = p3[ bx1 ];

	b00 = p3[ i + by0 ];
	b10 = p3[ j + by0 ];
	b01 = p3[ i + by1 ];
	b11 = p3[ j + by1 ];

	t  = s_curve(rx0);
	sy = s_curve(ry0);
	sz = s_curve(rz0);

	q = g3[ b00 + bz0 ] ; u = at3(rx0,ry0,rz0);
	q = g3[ b10 + bz0 ] ; v = at3(rx1,ry0,rz0);
	a = lerp(t, u, v);

	q = g3[ b01 + bz0 ] ; u = at3(rx0,ry1,rz0);
	q = g3[ b11 + bz0 ] ; v = at3(rx1,ry1,rz0);
	b = lerp(t, u, v);

	c = lerp(sy, a, b);

	q = g3[ b00 + bz1 ] ; u = at3(rx0,ry0,rz1);
	q = g3[ b10 + bz1 ] ; v = at3(rx1,ry0,rz1);
	a = lerp(t, u, v);

	q = g3[ b01 + bz1 ] ; u = at3(rx0,ry1,rz1);
	q = g3[ b11 + bz1 ] ; v = at3(rx1,ry1,rz1);
	b = lerp(t, u, v);

	d = lerp(sy, a, b);

	r[2] = (lerp(sz, c, d) + (float) 1)*((float) 0.5);
}


///////////////////////////////////////////////////////////////////////
// Function				:	noiseFloat4D
// Description			:
// Return Value			:
// Comments				:
// Date last edited		:
float	noiseFloat(const float *argu,float argv) {
	int bx0, bx1, by0, by1, bz0, bz1, bw0, bw1, b00, b10, b01, b11;
	float rx0, rx1, ry0, ry1, rz0, rz1, rw0, rw1, *q, sy, sz, sw, a, b, c, d, e, t, u, v, vec[4];
	register int i, j;

	vec[0]	=	argu[0];
	vec[1]	=	argu[1];
	vec[2]	=	argu[2];
	vec[3]	=	argv;

	setup(0, bx0,bx1, rx0,rx1);
	setup(1, by0,by1, ry0,ry1);
	setup(2, bz0,bz1, rz0,rz1);
	setup(3, bw0,bw1, rw0,rw1);

	i = p[ bx0 ];
	j = p[ bx1 ];

	b00 = p[ i + by0 ];
	b10 = p[ j + by0 ];
	b01 = p[ i + by1 ];
	b11 = p[ j + by1 ];

	t  = s_curve(rx0);
	sy = s_curve(ry0);
	sz = s_curve(rz0);
	sw = s_curve(rw0);

#define at4(rx,ry,rz,rw) ( rx * q[0] + ry * q[1] + rz * q[2] + rw * q[3])

	q = g4[ b00 + bz0 ] ; u = at4(rx0,ry0,rz0,rw0);
	q = g4[ b10 + bz0 ] ; v = at4(rx1,ry0,rz0,rw0);
	a = lerp(t, u, v);

	q = g4[ b01 + bz0 ] ; u = at4(rx0,ry1,rz0,rw0);
	q = g4[ b11 + bz0 ] ; v = at4(rx1,ry1,rz0,rw0);
	b = lerp(t, u, v);

	c = lerp(sy, a, b);

	q = g4[ b00 + bz1 ] ; u = at4(rx0,ry0,rz1,rw0);
	q = g4[ b10 + bz1 ] ; v = at4(rx1,ry0,rz1,rw0);
	a = lerp(t, u, v);

	q = g4[ b01 + bz1 ] ; u = at4(rx0,ry1,rz1,rw0);
	q = g4[ b11 + bz1 ] ; v = at4(rx1,ry1,rz1,rw0);
	b = lerp(t, u, v);

	d = lerp(sy, a, b);
	d = lerp(sz, c, d);

	q = g4[ b00 + bz0 ] ; u = at4(rx0,ry0,rz0,rw1);
	q = g4[ b10 + bz0 ] ; v = at4(rx1,ry0,rz0,rw1);
	a = lerp(t, u, v);

	q = g4[ b01 + bz0 ] ; u = at4(rx0,ry1,rz0,rw1);
	q = g4[ b11 + bz0 ] ; v = at4(rx1,ry1,rz0,rw1);
	b = lerp(t, u, v);

	c = lerp(sy, a, b);

	q = g4[ b00 + bz1 ] ; u = at4(rx0,ry0,rz1,rw1);
	q = g4[ b10 + bz1 ] ; v = at4(rx1,ry0,rz1,rw1);
	a = lerp(t, u, v);

	q = g4[ b01 + bz1 ] ; u = at4(rx0,ry1,rz1,rw1);
	q = g4[ b11 + bz1 ] ; v = at4(rx1,ry1,rz1,rw1);
	b = lerp(t, u, v);

	e = lerp(sy, a, b);
	e = lerp(sz, c, e);

	return (lerp(sw, d, e) + (float) 1)*((float) 0.5);
}

///////////////////////////////////////////////////////////////////////
// Function				:	noiseVector4D
// Description			:
// Return Value			:
// Comments				:
// Date last edited		:	3/13/2001
void	noiseVector(float *r,const float *argu,float argv) {
	int bx0, bx1, by0, by1, bz0, bz1, bw0, bw1, b00, b10, b01, b11;
	float rx0, rx1, ry0, ry1, rz0, rz1, rw0, rw1, *q, sy, sz, sw, a, b, c, d, e, t, u, v, vec[4];
	register int i, j;

	vec[0]	=	argu[0];
	vec[1]	=	argu[1];
	vec[2]	=	argu[2];
	vec[3]	=	argv;

	setup(0, bx0,bx1, rx0,rx1);
	setup(1, by0,by1, ry0,ry1);
	setup(2, bz0,bz1, rz0,rz1);
	setup(3, bw0,bw1, rw0,rw1);

	i = p[ bx0 ];
	j = p[ bx1 ];

	b00 = p[ i + by0 ];
	b10 = p[ j + by0 ];
	b01 = p[ i + by1 ];
	b11 = p[ j + by1 ];

	t  = s_curve(rx0);
	sy = s_curve(ry0);
	sz = s_curve(rz0);
	sw = s_curve(rw0);

	q = g4[ b00 + bz0 ] ; u = at4(rx0,ry0,rz0,rw0);
	q = g4[ b10 + bz0 ] ; v = at4(rx1,ry0,rz0,rw0);
	a = lerp(t, u, v);

	q = g4[ b01 + bz0 ] ; u = at4(rx0,ry1,rz0,rw0);
	q = g4[ b11 + bz0 ] ; v = at4(rx1,ry1,rz0,rw0);
	b = lerp(t, u, v);

	c = lerp(sy, a, b);

	q = g4[ b00 + bz1 ] ; u = at4(rx0,ry0,rz1,rw0);
	q = g4[ b10 + bz1 ] ; v = at4(rx1,ry0,rz1,rw0);
	a = lerp(t, u, v);

	q = g4[ b01 + bz1 ] ; u = at4(rx0,ry1,rz1,rw0);
	q = g4[ b11 + bz1 ] ; v = at4(rx1,ry1,rz1,rw0);
	b = lerp(t, u, v);

	d = lerp(sy, a, b);
	d = lerp(sz, c, d);

	q = g4[ b00 + bz0 ] ; u = at4(rx0,ry0,rz0,rw1);
	q = g4[ b10 + bz0 ] ; v = at4(rx1,ry0,rz0,rw1);
	a = lerp(t, u, v);

	q = g4[ b01 + bz0 ] ; u = at4(rx0,ry1,rz0,rw1);
	q = g4[ b11 + bz0 ] ; v = at4(rx1,ry1,rz0,rw1);
	b = lerp(t, u, v);

	c = lerp(sy, a, b);

	q = g4[ b00 + bz1 ] ; u = at4(rx0,ry0,rz1,rw1);
	q = g4[ b10 + bz1 ] ; v = at4(rx1,ry0,rz1,rw1);
	a = lerp(t, u, v);

	q = g4[ b01 + bz1 ] ; u = at4(rx0,ry1,rz1,rw1);
	q = g4[ b11 + bz1 ] ; v = at4(rx1,ry1,rz1,rw1);
	b = lerp(t, u, v);

	e = lerp(sy, a, b);
	e = lerp(sz, c, e);

	r[0] = (lerp(sw, d, e) + (float) 1)*((float) 0.5);

	i = p2[ bx0 ];
	j = p2[ bx1 ];

	b00 = p2[ i + by0 ];
	b10 = p2[ j + by0 ];
	b01 = p2[ i + by1 ];
	b11 = p2[ j + by1 ];

	t  = s_curve(rx0);
	sy = s_curve(ry0);
	sz = s_curve(rz0);
	sw = s_curve(rw0);

	q = g4[ b00 + bz0 ] ; u = at4(rx0,ry0,rz0,rw0);
	q = g4[ b10 + bz0 ] ; v = at4(rx1,ry0,rz0,rw0);
	a = lerp(t, u, v);

	q = g4[ b01 + bz0 ] ; u = at4(rx0,ry1,rz0,rw0);
	q = g4[ b11 + bz0 ] ; v = at4(rx1,ry1,rz0,rw0);
	b = lerp(t, u, v);

	c = lerp(sy, a, b);

	q = g4[ b00 + bz1 ] ; u = at4(rx0,ry0,rz1,rw0);
	q = g4[ b10 + bz1 ] ; v = at4(rx1,ry0,rz1,rw0);
	a = lerp(t, u, v);

	q = g4[ b01 + bz1 ] ; u = at4(rx0,ry1,rz1,rw0);
	q = g4[ b11 + bz1 ] ; v = at4(rx1,ry1,rz1,rw0);
	b = lerp(t, u, v);

	d = lerp(sy, a, b);
	d = lerp(sz, c, d);

	q = g4[ b00 + bz0 ] ; u = at4(rx0,ry0,rz0,rw1);
	q = g4[ b10 + bz0 ] ; v = at4(rx1,ry0,rz0,rw1);
	a = lerp(t, u, v);

	q = g4[ b01 + bz0 ] ; u = at4(rx0,ry1,rz0,rw1);
	q = g4[ b11 + bz0 ] ; v = at4(rx1,ry1,rz0,rw1);
	b = lerp(t, u, v);

	c = lerp(sy, a, b);

	q = g4[ b00 + bz1 ] ; u = at4(rx0,ry0,rz1,rw1);
	q = g4[ b10 + bz1 ] ; v = at4(rx1,ry0,rz1,rw1);
	a = lerp(t, u, v);

	q = g4[ b01 + bz1 ] ; u = at4(rx0,ry1,rz1,rw1);
	q = g4[ b11 + bz1 ] ; v = at4(rx1,ry1,rz1,rw1);
	b = lerp(t, u, v);

	e = lerp(sy, a, b);
	e = lerp(sz, c, e);

	r[1] = (lerp(sw, d, e) + (float) 1)*((float) 0.5);

	i = p3[ bx0 ];
	j = p3[ bx1 ];

	b00 = p3[ i + by0 ];
	b10 = p3[ j + by0 ];
	b01 = p3[ i + by1 ];
	b11 = p3[ j + by1 ];

	t  = s_curve(rx0);
	sy = s_curve(ry0);
	sz = s_curve(rz0);
	sw = s_curve(rw0);

	q = g4[ b00 + bz0 ] ; u = at4(rx0,ry0,rz0,rw0);
	q = g4[ b10 + bz0 ] ; v = at4(rx1,ry0,rz0,rw0);
	a = lerp(t, u, v);

	q = g4[ b01 + bz0 ] ; u = at4(rx0,ry1,rz0,rw0);
	q = g4[ b11 + bz0 ] ; v = at4(rx1,ry1,rz0,rw0);
	b = lerp(t, u, v);

	c = lerp(sy, a, b);

	q = g4[ b00 + bz1 ] ; u = at4(rx0,ry0,rz1,rw0);
	q = g4[ b10 + bz1 ] ; v = at4(rx1,ry0,rz1,rw0);
	a = lerp(t, u, v);

	q = g4[ b01 + bz1 ] ; u = at4(rx0,ry1,rz1,rw0);
	q = g4[ b11 + bz1 ] ; v = at4(rx1,ry1,rz1,rw0);
	b = lerp(t, u, v);

	d = lerp(sy, a, b);
	d = lerp(sz, c, d);

	q = g4[ b00 + bz0 ] ; u = at4(rx0,ry0,rz0,rw1);
	q = g4[ b10 + bz0 ] ; v = at4(rx1,ry0,rz0,rw1);
	a = lerp(t, u, v);

	q = g4[ b01 + bz0 ] ; u = at4(rx0,ry1,rz0,rw1);
	q = g4[ b11 + bz0 ] ; v = at4(rx1,ry1,rz0,rw1);
	b = lerp(t, u, v);

	c = lerp(sy, a, b);

	q = g4[ b00 + bz1 ] ; u = at4(rx0,ry0,rz1,rw1);
	q = g4[ b10 + bz1 ] ; v = at4(rx1,ry0,rz1,rw1);
	a = lerp(t, u, v);

	q = g4[ b01 + bz1 ] ; u = at4(rx0,ry1,rz1,rw1);
	q = g4[ b11 + bz1 ] ; v = at4(rx1,ry1,rz1,rw1);
	b = lerp(t, u, v);

	e = lerp(sy, a, b);
	e = lerp(sz, c, e);

	r[2] = (lerp(sw, d, e) + (float) 1)*((float) 0.5);
}



///////////////////////////////////////////////////////////////////////
// Function				:	pnoiseFloat1D
// Description			:	I cheaply use the other noise function
// Return Value			:
// Comments				:
// Date last edited		:	3/13/2001
float	pnoiseFloat(float u,float uperiod) {
	return noiseFloat((float) fmod(u,uperiod));
}


///////////////////////////////////////////////////////////////////////
// Function				:	pnoiseFloat2D
// Description			:
// Return Value			:
// Comments				:
// Date last edited		:	3/13/2001
float	pnoiseFloat(float u,float v,float uperiod,float vperiod) {
	return noiseFloat((float) fmod(u,uperiod),(float) fmod(v,vperiod));
}

///////////////////////////////////////////////////////////////////////
// Function				:	pnoiseFloat3D
// Description			:
// Return Value			:
// Comments				:
// Date last edited		:	3/13/2001
float	pnoiseFloat(const float *arg,const float *periods) {
	float	vec[3];
	vec[0]	=	(float) fmod(arg[0],periods[0]);
	vec[1]	=	(float) fmod(arg[1],periods[1]);
	vec[2]	=	(float) fmod(arg[2],periods[2]);
	return noiseFloat(vec);
}

///////////////////////////////////////////////////////////////////////
// Function				:	pnoiseFloat4D
// Description			:
// Return Value			:
// Comments				:
// Date last edited		:	3/13/2001
float	pnoiseFloat(const float *arg,float w,const float *periods,float wperiod) {
	float	vec[3];
	vec[0]	=	(float) fmod(arg[0],periods[0]);
	vec[1]	=	(float) fmod(arg[1],periods[1]);
	vec[2]	=	(float) fmod(arg[2],periods[2]);
	return noiseFloat(vec,(float) fmod(w,wperiod));
}

///////////////////////////////////////////////////////////////////////
// Function				:	pnoiseVector1D
// Description			:
// Return Value			:
// Comments				:
// Date last edited		:	3/13/2001
void	pnoiseVector(float *r,float u,float uperiod) {
	noiseVector(r,(float) fmod(u,uperiod));
}

///////////////////////////////////////////////////////////////////////
// Function				:	pnoiseVector2D
// Description			:
// Return Value			:
// Comments				:
// Date last edited		:	3/13/2001
void	pnoiseVector(float *r,float u,float v,float uperiod,float vperiod) {
	noiseVector(r,(float) fmod(u,uperiod),(float) fmod(v,vperiod));
}

///////////////////////////////////////////////////////////////////////
// Function				:	pnoiseVector3D
// Description			:
// Return Value			:
// Comments				:
// Date last edited		:	3/13/2001
void	pnoiseVector(float *r,const float *arg,const float *periods) {
	float	vec[3];
	vec[0]	=	(float) fmod(arg[0],periods[0]);
	vec[1]	=	(float) fmod(arg[1],periods[1]);
	vec[2]	=	(float) fmod(arg[2],periods[2]);
	noiseVector(r,vec);
}

///////////////////////////////////////////////////////////////////////
// Function				:	pnoiseVector4D
// Description			:
// Return Value			:
// Comments				:
// Date last edited		:	3/13/2001
void	pnoiseVector(float *r,const float *arg,float w,const float *periods,float wperiod) {
	float	vec[3];
	vec[0]	=	(float) fmod(arg[0],periods[0]);
	vec[1]	=	(float) fmod(arg[1],periods[1]);
	vec[2]	=	(float) fmod(arg[2],periods[2]);
	noiseVector(r,vec,(float) fmod(w,wperiod));
}

///////////////////////////////////////////////////////////////////////
// Function				:	cellNoiseFloat1D
// Description			:	Fast cell noise implementation
// Return Value			:
// Comments				:
// Date last edited		:	3/13/2001
float	cellNoiseFloat(float arg) {
	int		bx0;
	int		index;

	bx0		=	((int) (arg + NOISEMIN)) & NOISEMASK;
	index	=	p[bx0];

	return (g1[index] + 1)*(float) 0.5;
}

///////////////////////////////////////////////////////////////////////
// Function				:	cellNoiseFloat2D
// Description			:
// Return Value			:
// Comments				:
// Date last edited		:	3/13/2001
float	cellNoiseFloat(float u,float v) {
	int		bx0, by0;
	int		index;


	bx0		=	((int) (u + NOISEMIN)) & NOISEMASK;
	by0		=	((int) (v + NOISEMIN)) & NOISEMASK;
	index	=	p[(p[bx0] + p[by0]) & NOISEMASK];

	return (g1[index] + 1)*(float) 0.5;
}

///////////////////////////////////////////////////////////////////////
// Function				:	cellNoiseFloat3D
// Description			:
// Return Value			:
// Comments				:
// Date last edited		:	3/13/2001
float	cellNoiseFloat(const float *arg) {
	int		bx0, by0, bz0;
	int		index;

	bx0		=	((int) (arg[0] + NOISEMIN)) & NOISEMASK;
	by0		=	((int) (arg[1] + NOISEMIN)) & NOISEMASK;
	bz0		=	((int) (arg[2] + NOISEMIN)) & NOISEMASK;
	index	=	p[(p[bx0] + p[by0] + p[bz0]) & NOISEMASK];

	return (g1[index] + 1)*(float) 0.5;
}

///////////////////////////////////////////////////////////////////////
// Function				:	cellNoiseFloat4D
// Description			:
// Return Value			:
// Comments				:
// Date last edited		:	3/13/2001
float	cellNoiseFloat(const float *arg,float w) {
	int		bx0, by0, bz0, bw0;
	int		index;

	bx0		=	((int) (arg[0] + NOISEMIN)) & NOISEMASK;
	by0		=	((int) (arg[1] + NOISEMIN)) & NOISEMASK;
	bz0		=	((int) (arg[2] + NOISEMIN)) & NOISEMASK;
	bw0		=	((int) (w + NOISEMIN)) & NOISEMASK;
	index	=	p[(p[bx0] + p[by0] + p[bz0] + p[bw0]) & NOISEMASK];
	
	return (g1[index] + 1)*(float) 0.5;
}

///////////////////////////////////////////////////////////////////////
// Function				:	cellNoiseVector1D
// Description			:
// Return Value			:
// Comments				:
// Date last edited		:	3/13/2001
void	cellNoiseVector(float *r,float arg) {
	int		bx0;
	int		index;

	bx0		=	((int) (arg + NOISEMIN)) & NOISEMASK;
	index	=	p[bx0];

	r[0]	=	(g3[index][0]+1)*(float) 0.5;
	r[1]	=	(g3[index][1]+1)*(float) 0.5;
	r[2]	=	(g3[index][2]+1)*(float) 0.5;
}

///////////////////////////////////////////////////////////////////////
// Function				:	cellNoiseVector2D
// Description			:
// Return Value			:
// Comments				:
// Date last edited		:	3/13/2001
void	cellNoiseVector(float *r,float u,float v) {
	int		bx0, by0;
	int		index;


	bx0		=	((int) (u + NOISEMIN)) & NOISEMASK;
	by0		=	((int) (v + NOISEMIN)) & NOISEMASK;
	index	=	p[(p[bx0] + p[by0]) & NOISEMASK];

	r[0]	=	(g3[index][0]+1)*(float) 0.5;
	r[1]	=	(g3[index][1]+1)*(float) 0.5;
	r[2]	=	(g3[index][2]+1)*(float) 0.5;
}

///////////////////////////////////////////////////////////////////////
// Function				:	cellNoiseVector3D
// Description			:
// Return Value			:
// Comments				:
// Date last edited		:	3/13/2001
void	cellNoiseVector(float *r,const float *arg) {
	int		bx0, by0, bz0;
	int		index;

	bx0		=	((int) (arg[0] + NOISEMIN)) & NOISEMASK;
	by0		=	((int) (arg[1] + NOISEMIN)) & NOISEMASK;
	bz0		=	((int) (arg[2] + NOISEMIN)) & NOISEMASK;
	index	=	p[(p[bx0] + p[by0] + p[bz0]) & NOISEMASK];

	r[0]	=	(g3[index][0]+1)*(float) 0.5;
	r[1]	=	(g3[index][1]+1)*(float) 0.5;
	r[2]	=	(g3[index][2]+1)*(float) 0.5;
}

///////////////////////////////////////////////////////////////////////
// Function				:	cellNoiseVector4D
// Description			:
// Return Value			:
// Comments				:
// Date last edited		:	3/13/2001
void	cellNoiseVector(float *r,const float *arg,float w) {
	int		bx0, by0, bz0, bw0;
	int		index;

	bx0		=	((int) (arg[0] + NOISEMIN)) & NOISEMASK;
	by0		=	((int) (arg[1] + NOISEMIN)) & NOISEMASK;
	bz0		=	((int) (arg[2] + NOISEMIN)) & NOISEMASK;
	bw0		=	((int) (w + NOISEMIN)) & NOISEMASK;
	index	=	p[(p[bx0] + p[by0] + p[bz0] + p[bw0]) & NOISEMASK];
	
	r[0]	=	(g3[index][0]+1)*(float) 0.5;
	r[1]	=	(g3[index][1]+1)*(float) 0.5;
	r[2]	=	(g3[index][2]+1)*(float) 0.5;
}






