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
//  File				:	noise.cpp
//  Classes				:	-
//  Description			:	The misc noise functions
//
////////////////////////////////////////////////////////////////////////
#include <math.h>

#include "common/algebra.h"
#include "common/os.h"
#include "noise.h"


#define FADE(t) ( t * t * t * ( t * ( t * 6 - 15 ) + 10 ) )
#define FASTFLOOR(x) ( ((x)>0) ? ((int)x) : ((int)x-1 ) )
#define LERP(t, a, b) ((a) + (t)*((b)-(a)))

#include "noiseTables.h"

// Helper gradient functions
template <class T>	T  grad(int hash,T x) {
    int h		= hash & 15;
    T	grad	= (T) 1.0 + (h & 7);
    if (h&8) grad = -grad;
    return ( grad * x );
}

template <class T>	T  grad(int hash,T x,T y) {
    int		h = hash & 7;
    const T	u = h<4 ? x : y;
    const T	v = h<4 ? y : x;
    return ((h&1)? -u : u) + ((h&2)? (T) -2.0*v : (T) 2.0*v);
}

template <class T>	T  grad(int hash,T x,T y ,T z) {
    int		h = hash & 15;
    const T	u = h<8 ? x : y;
    const T	v = h<4 ? y : h==12||h==14 ? x : z;
    return ((h&1)? -u : u) + ((h&2)? -v : v);
}

template <class T>	T  grad(int hash,T x,T y,T z,T t ) {
    int		h = hash & 31;
    const T	u = h<24 ? x : y;
    const T	v = h<16 ? y : z;
    const T	w = h<8 ? z : t;
    return ((h&1)? -u : u) + ((h&2)? -v : v) + ((h&4)? -w : w);
}




/////////////////////////////////////////////////////////////////////////////////
//
//	Noise functions start here
//
/////////////////////////////////////////////////////////////////////////////////




template <class T>	T  noise(T x,const unsigned char *perm) {
    int ix0, ix1;
    T	fx0, fx1;
    T	s, n0, n1;

    ix0 = FASTFLOOR( x );
    fx0 = x - ix0;
    fx1 = fx0 - 1.0f;
    ix1 = ( ix0+1 ) & 0xff;
    ix0 = ix0 & 0xff;

    s	= FADE( fx0 );

    n0	= grad( perm[ ix0 ], fx0 );
    n1	= grad( perm[ ix1 ], fx1 );
    return 0.5f * (1.0f + 0.188f * ( LERP( s, n0, n1 ) ));
}

template <class T>	T	pnoise(T x,int px,const unsigned char *perm) {
    int ix0, ix1;
    T	fx0, fx1;
    T	s, n0, n1;

	px	=	max(px,1);

    ix0 = FASTFLOOR( x );
    fx0 = x - ix0;
    fx1 = fx0 - 1.0f;
    ix1 = (( ix0 + 1 ) % px) & 0xff;
    ix0 = ( ix0 % px ) & 0xff;

    s = FADE( fx0 );

    n0 = grad( perm[ ix0 ], fx0 );
    n1 = grad( perm[ ix1 ], fx1 );
    return 0.5f * (1.0f + 0.188f * ( LERP( s, n0, n1 ) ));
}


template <class T>	T  noise(T x,T y,const unsigned char *perm) {
    int ix0, iy0, ix1, iy1;
    T	fx0, fy0, fx1, fy1;
    T	s, t, nx0, nx1, n0, n1;

    ix0 = FASTFLOOR( x );
    iy0 = FASTFLOOR( y );
    fx0 = x - ix0;
    fy0 = y - iy0;
    fx1 = fx0 - 1.0f;
    fy1 = fy0 - 1.0f;
    ix1 = (ix0 + 1) & 0xff;
    iy1 = (iy0 + 1) & 0xff;
    ix0 = ix0 & 0xff;
    iy0 = iy0 & 0xff;
    
    t = FADE( fy0 );
    s = FADE( fx0 );

    nx0 = grad(perm[ix0 + perm[iy0]], fx0, fy0);
    nx1 = grad(perm[ix0 + perm[iy1]], fx0, fy1);
    n0 = LERP( t, nx0, nx1 );

    nx0 = grad(perm[ix1 + perm[iy0]], fx1, fy0);
    nx1 = grad(perm[ix1 + perm[iy1]], fx1, fy1);
    n1 = LERP(t, nx0, nx1);

    return 0.5f * (1.0f + 0.507f * ( LERP( s, n0, n1 ) ) );
}

template <class T>	T  pnoise(T x,T y, int px, int py,const unsigned char *perm) {
    int ix0, iy0, ix1, iy1;
    T	fx0, fy0, fx1, fy1;
    T	s, t, nx0, nx1, n0, n1;

	px	=	max(px,1);
	py	=	max(py,1);

    ix0 = FASTFLOOR( x );
    iy0 = FASTFLOOR( y );
    fx0 = x - ix0;
    fy0 = y - iy0;
    fx1 = fx0 - 1.0f;
    fy1 = fy0 - 1.0f;
    ix1 = (( ix0 + 1 ) % px) & 0xff;
    iy1 = (( iy0 + 1 ) % py) & 0xff;
    ix0 = ( ix0 % px ) & 0xff;
    iy0 = ( iy0 % py ) & 0xff;
    
    t = FADE( fy0 );
    s = FADE( fx0 );

    nx0 = grad(perm[ix0 + perm[iy0]], fx0, fy0);
    nx1 = grad(perm[ix0 + perm[iy1]], fx0, fy1);
    n0 = LERP( t, nx0, nx1 );

    nx0 = grad(perm[ix1 + perm[iy0]], fx1, fy0);
    nx1 = grad(perm[ix1 + perm[iy1]], fx1, fy1);
    n1 = LERP(t, nx0, nx1);

    return 0.5f * (1.0f + 0.507f * ( LERP( s, n0, n1 ) ) );
}


template <class T>	T  noise(T x,T y,T z,const unsigned char *perm) {
    int ix0, iy0, ix1, iy1, iz0, iz1;
    T	fx0, fy0, fz0, fx1, fy1, fz1;
    T	s, t, r;
    T	nxy0, nxy1, nx0, nx1, n0, n1;

    ix0 = FASTFLOOR( x );
    iy0 = FASTFLOOR( y );
    iz0 = FASTFLOOR( z );
    fx0 = x - ix0;
    fy0 = y - iy0;
    fz0 = z - iz0;
    fx1 = fx0 - 1.0f;
    fy1 = fy0 - 1.0f;
    fz1 = fz0 - 1.0f;
    ix1 = ( ix0 + 1 ) & 0xff;
    iy1 = ( iy0 + 1 ) & 0xff;
    iz1 = ( iz0 + 1 ) & 0xff;
    ix0 = ix0 & 0xff;
    iy0 = iy0 & 0xff;
    iz0 = iz0 & 0xff;
    
    r = FADE( fz0 );
    t = FADE( fy0 );
    s = FADE( fx0 );

    nxy0 = grad(perm[ix0 + perm[iy0 + perm[iz0]]], fx0, fy0, fz0);
    nxy1 = grad(perm[ix0 + perm[iy0 + perm[iz1]]], fx0, fy0, fz1);
    nx0 = LERP( r, nxy0, nxy1 );

    nxy0 = grad(perm[ix0 + perm[iy1 + perm[iz0]]], fx0, fy1, fz0);
    nxy1 = grad(perm[ix0 + perm[iy1 + perm[iz1]]], fx0, fy1, fz1);
    nx1 = LERP( r, nxy0, nxy1 );

    n0 = LERP( t, nx0, nx1 );

    nxy0 = grad(perm[ix1 + perm[iy0 + perm[iz0]]], fx1, fy0, fz0);
    nxy1 = grad(perm[ix1 + perm[iy0 + perm[iz1]]], fx1, fy0, fz1);
    nx0 = LERP( r, nxy0, nxy1 );

    nxy0 = grad(perm[ix1 + perm[iy1 + perm[iz0]]], fx1, fy1, fz0);
    nxy1 = grad(perm[ix1 + perm[iy1 + perm[iz1]]], fx1, fy1, fz1);
    nx1 = LERP( r, nxy0, nxy1 );

    n1 = LERP( t, nx0, nx1 );
    
    return 0.5f * (1.0f + 0.936f * ( LERP( s, n0, n1 ) ) );
}

template <class T>	T   pnoise(T x,T y,T z,int px,int py,int pz,const unsigned char *perm) {
    int ix0, iy0, ix1, iy1, iz0, iz1;
    T fx0, fy0, fz0, fx1, fy1, fz1;
    T s, t, r;
    T nxy0, nxy1, nx0, nx1, n0, n1;

	px	=	max(px,1);
	py	=	max(py,1);
	pz	=	max(pz,1);

    ix0 = FASTFLOOR( x );
    iy0 = FASTFLOOR( y );
    iz0 = FASTFLOOR( z );
    fx0 = x - ix0;
    fy0 = y - iy0;
    fz0 = z - iz0;
    fx1 = fx0 - 1.0f;
    fy1 = fy0 - 1.0f;
    fz1 = fz0 - 1.0f;
    ix1 = (( ix0 + 1 ) % px ) & 0xff;
    iy1 = (( iy0 + 1 ) % py ) & 0xff;
    iz1 = (( iz0 + 1 ) % pz ) & 0xff;
    ix0 = ( ix0 % px ) & 0xff;
    iy0 = ( iy0 % py ) & 0xff;
    iz0 = ( iz0 % pz ) & 0xff;
    
    r = FADE( fz0 );
    t = FADE( fy0 );
    s = FADE( fx0 );

    nxy0 = grad(perm[ix0 + perm[iy0 + perm[iz0]]], fx0, fy0, fz0);
    nxy1 = grad(perm[ix0 + perm[iy0 + perm[iz1]]], fx0, fy0, fz1);
    nx0 = LERP( r, nxy0, nxy1 );

    nxy0 = grad(perm[ix0 + perm[iy1 + perm[iz0]]], fx0, fy1, fz0);
    nxy1 = grad(perm[ix0 + perm[iy1 + perm[iz1]]], fx0, fy1, fz1);
    nx1 = LERP( r, nxy0, nxy1 );

    n0 = LERP( t, nx0, nx1 );

    nxy0 = grad(perm[ix1 + perm[iy0 + perm[iz0]]], fx1, fy0, fz0);
    nxy1 = grad(perm[ix1 + perm[iy0 + perm[iz1]]], fx1, fy0, fz1);
    nx0 = LERP( r, nxy0, nxy1 );

    nxy0 = grad(perm[ix1 + perm[iy1 + perm[iz0]]], fx1, fy1, fz0);
    nxy1 = grad(perm[ix1 + perm[iy1 + perm[iz1]]], fx1, fy1, fz1);
    nx1 = LERP( r, nxy0, nxy1 );

    n1 = LERP( t, nx0, nx1 );
    
    return 0.5f * (1.0f + 0.936f * ( LERP( s, n0, n1 ) ) );
}


template <class T>	T  noise(T x,T y,T z,T w,const unsigned char *perm) {
    int ix0, iy0, iz0, iw0, ix1, iy1, iz1, iw1;
    T fx0, fy0, fz0, fw0, fx1, fy1, fz1, fw1;
    T s, t, r, q;
    T nxyz0, nxyz1, nxy0, nxy1, nx0, nx1, n0, n1;

    ix0 = FASTFLOOR( x );
    iy0 = FASTFLOOR( y );
    iz0 = FASTFLOOR( z );
    iw0 = FASTFLOOR( w );
    fx0 = x - ix0;
    fy0 = y - iy0;
    fz0 = z - iz0;
    fw0 = w - iw0;
    fx1 = fx0 - 1.0f;
    fy1 = fy0 - 1.0f;
    fz1 = fz0 - 1.0f;
    fw1 = fw0 - 1.0f;
    ix1 = ( ix0 + 1 ) & 0xff;
    iy1 = ( iy0 + 1 ) & 0xff;
    iz1 = ( iz0 + 1 ) & 0xff;
    iw1 = ( iw0 + 1 ) & 0xff;
    ix0 = ix0 & 0xff;
    iy0 = iy0 & 0xff;
    iz0 = iz0 & 0xff;
    iw0 = iw0 & 0xff;

    q = FADE( fw0 );
    r = FADE( fz0 );
    t = FADE( fy0 );
    s = FADE( fx0 );

    nxyz0 = grad(perm[ix0 + perm[iy0 + perm[iz0 + perm[iw0]]]], fx0, fy0, fz0, fw0);
    nxyz1 = grad(perm[ix0 + perm[iy0 + perm[iz0 + perm[iw1]]]], fx0, fy0, fz0, fw1);
    nxy0 = LERP( q, nxyz0, nxyz1 );
        
    nxyz0 = grad(perm[ix0 + perm[iy0 + perm[iz1 + perm[iw0]]]], fx0, fy0, fz1, fw0);
    nxyz1 = grad(perm[ix0 + perm[iy0 + perm[iz1 + perm[iw1]]]], fx0, fy0, fz1, fw1);
    nxy1 = LERP( q, nxyz0, nxyz1 );
        
    nx0 = LERP ( r, nxy0, nxy1 );

    nxyz0 = grad(perm[ix0 + perm[iy1 + perm[iz0 + perm[iw0]]]], fx0, fy1, fz0, fw0);
    nxyz1 = grad(perm[ix0 + perm[iy1 + perm[iz0 + perm[iw1]]]], fx0, fy1, fz0, fw1);
    nxy0 = LERP( q, nxyz0, nxyz1 );
        
    nxyz0 = grad(perm[ix0 + perm[iy1 + perm[iz1 + perm[iw0]]]], fx0, fy1, fz1, fw0);
    nxyz1 = grad(perm[ix0 + perm[iy1 + perm[iz1 + perm[iw1]]]], fx0, fy1, fz1, fw1);
    nxy1 = LERP( q, nxyz0, nxyz1 );

    nx1 = LERP ( r, nxy0, nxy1 );

    n0 = LERP( t, nx0, nx1 );

    nxyz0 = grad(perm[ix1 + perm[iy0 + perm[iz0 + perm[iw0]]]], fx1, fy0, fz0, fw0);
    nxyz1 = grad(perm[ix1 + perm[iy0 + perm[iz0 + perm[iw1]]]], fx1, fy0, fz0, fw1);
    nxy0 = LERP( q, nxyz0, nxyz1 );
        
    nxyz0 = grad(perm[ix1 + perm[iy0 + perm[iz1 + perm[iw0]]]], fx1, fy0, fz1, fw0);
    nxyz1 = grad(perm[ix1 + perm[iy0 + perm[iz1 + perm[iw1]]]], fx1, fy0, fz1, fw1);
    nxy1 = LERP( q, nxyz0, nxyz1 );

    nx0 = LERP ( r, nxy0, nxy1 );

    nxyz0 = grad(perm[ix1 + perm[iy1 + perm[iz0 + perm[iw0]]]], fx1, fy1, fz0, fw0);
    nxyz1 = grad(perm[ix1 + perm[iy1 + perm[iz0 + perm[iw1]]]], fx1, fy1, fz0, fw1);
    nxy0 = LERP( q, nxyz0, nxyz1 );
        
    nxyz0 = grad(perm[ix1 + perm[iy1 + perm[iz1 + perm[iw0]]]], fx1, fy1, fz1, fw0);
    nxyz1 = grad(perm[ix1 + perm[iy1 + perm[iz1 + perm[iw1]]]], fx1, fy1, fz1, fw1);
    nxy1 = LERP( q, nxyz0, nxyz1 );

    nx1 = LERP ( r, nxy0, nxy1 );

    n1 = LERP( t, nx0, nx1 );

    return 0.5f * (1.0f + 0.87f * ( LERP( s, n0, n1 ) ) );
}

template <class T>	T  pnoise(T x,T y,T z, float w,int px,int py,int pz,int pw,const unsigned char *perm) {
    int ix0, iy0, iz0, iw0, ix1, iy1, iz1, iw1;
    T fx0, fy0, fz0, fw0, fx1, fy1, fz1, fw1;
    T s, t, r, q;
    T nxyz0, nxyz1, nxy0, nxy1, nx0, nx1, n0, n1;

	px	=	max(px,1);
	py	=	max(py,1);
	pz	=	max(pz,1);
	pw	=	max(pw,1);

    ix0 = FASTFLOOR( x );
    iy0 = FASTFLOOR( y );
    iz0 = FASTFLOOR( z );
    iw0 = FASTFLOOR( w );
    fx0 = x - ix0;
    fy0 = y - iy0;
    fz0 = z - iz0;
    fw0 = w - iw0;
    fx1 = fx0 - 1.0f;
    fy1 = fy0 - 1.0f;
    fz1 = fz0 - 1.0f;
    fw1 = fw0 - 1.0f;
    ix1 = (( ix0 + 1 ) % px ) & 0xff;
    iy1 = (( iy0 + 1 ) % py ) & 0xff;
    iz1 = (( iz0 + 1 ) % pz ) & 0xff;
    iw1 = (( iw0 + 1 ) % pw ) & 0xff;
    ix0 = ( ix0 % px ) & 0xff;
    iy0 = ( iy0 % py ) & 0xff;
    iz0 = ( iz0 % pz ) & 0xff;
    iw0 = ( iw0 % pw ) & 0xff;

    q = FADE( fw0 );
    r = FADE( fz0 );
    t = FADE( fy0 );
    s = FADE( fx0 );

    nxyz0 = grad(perm[ix0 + perm[iy0 + perm[iz0 + perm[iw0]]]], fx0, fy0, fz0, fw0);
    nxyz1 = grad(perm[ix0 + perm[iy0 + perm[iz0 + perm[iw1]]]], fx0, fy0, fz0, fw1);
    nxy0 = LERP( q, nxyz0, nxyz1 );
        
    nxyz0 = grad(perm[ix0 + perm[iy0 + perm[iz1 + perm[iw0]]]], fx0, fy0, fz1, fw0);
    nxyz1 = grad(perm[ix0 + perm[iy0 + perm[iz1 + perm[iw1]]]], fx0, fy0, fz1, fw1);
    nxy1 = LERP( q, nxyz0, nxyz1 );
        
    nx0 = LERP ( r, nxy0, nxy1 );

    nxyz0 = grad(perm[ix0 + perm[iy1 + perm[iz0 + perm[iw0]]]], fx0, fy1, fz0, fw0);
    nxyz1 = grad(perm[ix0 + perm[iy1 + perm[iz0 + perm[iw1]]]], fx0, fy1, fz0, fw1);
    nxy0 = LERP( q, nxyz0, nxyz1 );
        
    nxyz0 = grad(perm[ix0 + perm[iy1 + perm[iz1 + perm[iw0]]]], fx0, fy1, fz1, fw0);
    nxyz1 = grad(perm[ix0 + perm[iy1 + perm[iz1 + perm[iw1]]]], fx0, fy1, fz1, fw1);
    nxy1 = LERP( q, nxyz0, nxyz1 );

    nx1 = LERP ( r, nxy0, nxy1 );

    n0 = LERP( t, nx0, nx1 );

    nxyz0 = grad(perm[ix1 + perm[iy0 + perm[iz0 + perm[iw0]]]], fx1, fy0, fz0, fw0);
    nxyz1 = grad(perm[ix1 + perm[iy0 + perm[iz0 + perm[iw1]]]], fx1, fy0, fz0, fw1);
    nxy0 = LERP( q, nxyz0, nxyz1 );
        
    nxyz0 = grad(perm[ix1 + perm[iy0 + perm[iz1 + perm[iw0]]]], fx1, fy0, fz1, fw0);
    nxyz1 = grad(perm[ix1 + perm[iy0 + perm[iz1 + perm[iw1]]]], fx1, fy0, fz1, fw1);
    nxy1 = LERP( q, nxyz0, nxyz1 );

    nx0 = LERP ( r, nxy0, nxy1 );

    nxyz0 = grad(perm[ix1 + perm[iy1 + perm[iz0 + perm[iw0]]]], fx1, fy1, fz0, fw0);
    nxyz1 = grad(perm[ix1 + perm[iy1 + perm[iz0 + perm[iw1]]]], fx1, fy1, fz0, fw1);
    nxy0 = LERP( q, nxyz0, nxyz1 );
        
    nxyz0 = grad(perm[ix1 + perm[iy1 + perm[iz1 + perm[iw0]]]], fx1, fy1, fz1, fw0);
    nxyz1 = grad(perm[ix1 + perm[iy1 + perm[iz1 + perm[iw1]]]], fx1, fy1, fz1, fw1);
    nxy1 = LERP( q, nxyz0, nxyz1 );

    nx1 = LERP ( r, nxy0, nxy1 );

    n1 = LERP( t, nx0, nx1 );

    return 0.5f * (1.0f + 0.87f * ( LERP( s, n0, n1 ) ) );
}
















///////////////////////////////////////////////////////////////////////
// Function				:	noiseFloat1D
// Description			:
// Return Value			:
// Comments				:
float noiseFloat(float arg) {
	return	noise<float>(arg,permX);
}

///////////////////////////////////////////////////////////////////////
// Function				:	noiseFloat2D
// Description			:
// Return Value			:
// Comments				:
float noiseFloat(float uarg,float varg) {
	return	noise<float>(uarg,varg,permX);
}

///////////////////////////////////////////////////////////////////////
// Function				:	noiseFloat3D
// Description			:
// Return Value			:
// Comments				:
float noiseFloat(const float *vec) {
	return	noise<float>(vec[0],vec[1],vec[2],permX);
}

///////////////////////////////////////////////////////////////////////
// Function				:	noiseFloat4D
// Description			:
// Return Value			:
// Comments				:
float	noiseFloat(const float *argu,float argv) {
	return	noise<float>(argu[0],argu[1],argu[2],argv,permX);
}

///////////////////////////////////////////////////////////////////////
// Function				:	noiseVector1D
// Description			:
// Return Value			:
// Comments				:
void noiseVector(float *r,float arg) {
	r[0]	=	noise<float>(arg,permX);
	r[1]	=	noise<float>(arg,permY);
	r[2]	=	noise<float>(arg,permZ);
}

///////////////////////////////////////////////////////////////////////
// Function				:	noiseVector2D
// Description			:
// Return Value			:
// Comments				:
void noiseVector(float *r,float uarg,float varg) {
	r[0]	=	noise<float>(uarg,varg,permX);
	r[1]	=	noise<float>(uarg,varg,permY);
	r[2]	=	noise<float>(uarg,varg,permZ);
}

///////////////////////////////////////////////////////////////////////
// Function				:	noiseVector3D
// Description			:
// Return Value			:
// Comments				:
void noiseVector(float *r,const float *vec) {
	r[0]	=	noise<float>(vec[0],vec[1],vec[2],permX);
	r[1]	=	noise<float>(vec[0],vec[1],vec[2],permY);
	r[2]	=	noise<float>(vec[0],vec[1],vec[2],permZ);
}


///////////////////////////////////////////////////////////////////////
// Function				:	noiseVector4D
// Description			:
// Return Value			:
// Comments				:
void	noiseVector(float *r,const float *argu,float argv) {
	r[0]	=		noise<float>(argu[0],argu[1],argu[2],argv,permX);
	r[1]	=		noise<float>(argu[0],argu[1],argu[2],argv,permY);
	r[2]	=		noise<float>(argu[0],argu[1],argu[2],argv,permZ);
}



///////////////////////////////////////////////////////////////////////
// Function				:	pnoiseFloat1D
// Description			:
// Return Value			:
// Comments				:
float	pnoiseFloat(float u,float uperiod) {
	return pnoise<float>(u,(int) uperiod,permX);
}


///////////////////////////////////////////////////////////////////////
// Function				:	pnoiseFloat2D
// Description			:
// Return Value			:
// Comments				:
float	pnoiseFloat(float u,float v,float uperiod,float vperiod) {
	return pnoise<float>(u,v,(int) uperiod,(int) vperiod,permX);
}

///////////////////////////////////////////////////////////////////////
// Function				:	pnoiseFloat3D
// Description			:
// Return Value			:
// Comments				:
float	pnoiseFloat(const float *arg,const float *periods) {
	return pnoise<float>(arg[0],arg[1],arg[2],(int) periods[0],(int) periods[1],(int) periods[2],permX);
}

///////////////////////////////////////////////////////////////////////
// Function				:	pnoiseFloat4D
// Description			:
// Return Value			:
// Comments				:
float	pnoiseFloat(const float *arg,float w,const float *periods,float wperiod) {
	return pnoise<float>(arg[0],arg[1],arg[2],w,(int) periods[0],(int) periods[1],(int) periods[2],(int) wperiod,permX);
}

///////////////////////////////////////////////////////////////////////
// Function				:	pnoiseVector1D
// Description			:
// Return Value			:
// Comments				:
void	pnoiseVector(float *r,float u,float uperiod) {
	r[0]	=	pnoise<float>(u,(int) uperiod,permX);
	r[1]	=	pnoise<float>(u,(int) uperiod,permY);
	r[2]	=	pnoise<float>(u,(int) uperiod,permZ);
}

///////////////////////////////////////////////////////////////////////
// Function				:	pnoiseVector2D
// Description			:
// Return Value			:
// Comments				:
void	pnoiseVector(float *r,float u,float v,float uperiod,float vperiod) {
	r[0]	=	pnoise<float>(u,v,(int) uperiod,(int) vperiod,permX);
	r[1]	=	pnoise<float>(u,v,(int) uperiod,(int) vperiod,permY);
	r[2]	=	pnoise<float>(u,v,(int) uperiod,(int) vperiod,permZ);
}

///////////////////////////////////////////////////////////////////////
// Function				:	pnoiseVector3D
// Description			:
// Return Value			:
// Comments				:
void	pnoiseVector(float *r,const float *arg,const float *periods) {
	r[0]	=	pnoise<float>(arg[0],arg[1],arg[2],(int) periods[0],(int) periods[1],(int) periods[2],permX);
	r[1]	=	pnoise<float>(arg[0],arg[1],arg[2],(int) periods[0],(int) periods[1],(int) periods[2],permY);
	r[2]	=	pnoise<float>(arg[0],arg[1],arg[2],(int) periods[0],(int) periods[1],(int) periods[2],permZ);
}

///////////////////////////////////////////////////////////////////////
// Function				:	pnoiseVector4D
// Description			:
// Return Value			:
// Comments				:
void	pnoiseVector(float *r,const float *arg,float w,const float *periods,float wperiod) {
	r[0]	=	pnoise<float>(arg[0],arg[1],arg[2],w,(int) periods[0],(int) periods[1],(int) periods[2],(int) wperiod,permX);
	r[1]	=	pnoise<float>(arg[0],arg[1],arg[2],w,(int) periods[0],(int) periods[1],(int) periods[2],(int) wperiod,permY);
	r[2]	=	pnoise<float>(arg[0],arg[1],arg[2],w,(int) periods[0],(int) periods[1],(int) periods[2],(int) wperiod,permZ);
}

// Musc macro to permute the inputs
#define	permute(__val)																\
	if (__val < 0)	i = permN[	(i + ((unsigned int) (__val - 1))) & 4095	];		\
	else			i = permN[	(i + ((unsigned int) __val)) & 4095	];

///////////////////////////////////////////////////////////////////////
// Function				:	cellNoiseFloat1D
// Description			:	Fast cell noise implementation
// Return Value			:
// Comments				:
float	cellNoiseFloat(float arg) {
	unsigned int	i	=	0;

	permute(arg);

	return	randN[i];
}

///////////////////////////////////////////////////////////////////////
// Function				:	cellNoiseFloat2D
// Description			:
// Return Value			:
// Comments				:
float	cellNoiseFloat(float u,float v) {
	unsigned int	i	=	0;

	permute(u);
	permute(v);

	return	randN[i];
}

///////////////////////////////////////////////////////////////////////
// Function				:	cellNoiseFloat3D
// Description			:
// Return Value			:
// Comments				:
float	cellNoiseFloat(const float *arg) {
	unsigned int	i	=	0;

	permute(arg[0]);
	permute(arg[1]);
	permute(arg[2]);

	return	randN[i];
}

///////////////////////////////////////////////////////////////////////
// Function				:	cellNoiseFloat4D
// Description			:
// Return Value			:
// Comments				:
float	cellNoiseFloat(const float *arg,float w) {
	unsigned int	i	=	0;

	permute(arg[0]);
	permute(arg[1]);
	permute(arg[2]);
	permute(w);

	return	randN[i];
}

///////////////////////////////////////////////////////////////////////
// Function				:	cellNoiseVector1D
// Description			:
// Return Value			:
// Comments				:
void	cellNoiseVector(float *r,float arg) {
	unsigned int	i	=	0;

	permute(arg);

	r[0]	=	randN[i];
	r[1]	=	randN[permN[i]];
	r[2]	=	randN[permN[permN[i]]];
}

///////////////////////////////////////////////////////////////////////
// Function				:	cellNoiseVector2D
// Description			:
// Return Value			:
// Comments				:
void	cellNoiseVector(float *r,float u,float v) {
	unsigned int	i	=	0;

	permute(u);
	permute(v);

	r[0]	=	randN[i];
	r[1]	=	randN[permN[i]];
	r[2]	=	randN[permN[permN[i]]];
}

///////////////////////////////////////////////////////////////////////
// Function				:	cellNoiseVector3D
// Description			:
// Return Value			:
// Comments				:
void	cellNoiseVector(float *r,const float *arg) {
	unsigned int	i	=	0;

	permute(arg[0]);
	permute(arg[1]);
	permute(arg[2]);

	r[0]	=	randN[i];
	r[1]	=	randN[permN[i]];
	r[2]	=	randN[permN[permN[i]]];
}

///////////////////////////////////////////////////////////////////////
// Function				:	cellNoiseVector4D
// Description			:
// Return Value			:
// Comments				:
void	cellNoiseVector(float *r,const float *arg,float w) {
	unsigned int	i	=	0;

	permute(arg[0]);
	permute(arg[1]);
	permute(arg[2]);
	permute(w);

	r[0]	=	randN[i];
	r[1]	=	randN[permN[i]];
	r[2]	=	randN[permN[permN[i]]];
}
