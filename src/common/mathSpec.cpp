///////////////////////////////////////////////////////////////////////
//
//  File				:	mathSpec.cpp
//  Classes				:	-
//  Description			:	This file implements some basic algebra operations
//
////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////
// Function				:	det4x4
// Description			:	4 by 4 determinant computation
// Return Value			:	Determinant
// Comments				:
// Matrix:
// | a1 a2 a3 a4 |
// | b1 b2 b3 b4 |
// | c1 c2 c3 c4 |
// | d1 d2 d3 d4 |
static	inline double det4x4( const SCALAR_TYPE *m ) {
    double a1, a2, a3, a4, b1, b2, b3, b4, c1, c2, c3, c4, d1, d2, d3, d4;

	a1 = m[element(0,0)]; b1 = m[element(0,1)]; 
	c1 = m[element(0,2)]; d1 = m[element(0,3)];

	a2 = m[element(1,0)]; b2 = m[element(1,1)]; 
	c2 = m[element(1,2)]; d2 = m[element(1,3)];

	a3 = m[element(2,0)]; b3 = m[element(2,1)]; 
	c3 = m[element(2,2)]; d3 = m[element(2,3)];

	a4 = m[element(3,0)]; b4 = m[element(3,1)]; 
	c4 = m[element(3,2)]; d4 = m[element(3,3)];

    return	  a1 * det3x3( b2, b3, b4, c2, c3, c4, d2, d3, d4)
			- b1 * det3x3( a2, a3, a4, c2, c3, c4, d2, d3, d4)
			+ c1 * det3x3( a2, a3, a4, b2, b3, b4, d2, d3, d4)
			- d1 * det3x3( a2, a3, a4, b2, b3, b4, c2, c3, c4);
}

///////////////////////////////////////////////////////////////////////
// Function				:	adjoint
// Description			:	Compute the adjoint of a 4 by 4 matrix
// Return Value			:	-
// Comments				:
// Construct the adjoint matrix
// | a1 a2 a3 a4 |
// | b1 b2 b3 b4 |
// | c1 c2 c3 c4 |
// | d1 d2 d3 d4 |

static	inline void adjoint( SCALAR_TYPE *out,const SCALAR_TYPE *in) {
    SCALAR_TYPE a1, a2, a3, a4, b1, b2, b3, b4;
    SCALAR_TYPE c1, c2, c3, c4, d1, d2, d3, d4;

	a1 = in[element(0,0)]; b1 = in[element(0,1)]; 
	c1 = in[element(0,2)]; d1 = in[element(0,3)];

	a2 = in[element(1,0)]; b2 = in[element(1,1)]; 
	c2 = in[element(1,2)]; d2 = in[element(1,3)];

	a3 = in[element(2,0)]; b3 = in[element(2,1)];
	c3 = in[element(2,2)]; d3 = in[element(2,3)];

	a4 = in[element(3,0)]; b4 = in[element(3,1)]; 
	c4 = in[element(3,2)]; d4 = in[element(3,3)];

    out[element(0,0)]  = (SCALAR_TYPE)  det3x3( b2, b3, b4, c2, c3, c4, d2, d3, d4);
    out[element(1,0)]  = (SCALAR_TYPE) -det3x3( a2, a3, a4, c2, c3, c4, d2, d3, d4);
    out[element(2,0)]  = (SCALAR_TYPE)  det3x3( a2, a3, a4, b2, b3, b4, d2, d3, d4);
    out[element(3,0)]  = (SCALAR_TYPE) -det3x3( a2, a3, a4, b2, b3, b4, c2, c3, c4);
        
    out[element(0,1)]  = (SCALAR_TYPE) -det3x3( b1, b3, b4, c1, c3, c4, d1, d3, d4);
    out[element(1,1)]  = (SCALAR_TYPE)  det3x3( a1, a3, a4, c1, c3, c4, d1, d3, d4);
    out[element(2,1)]  = (SCALAR_TYPE) -det3x3( a1, a3, a4, b1, b3, b4, d1, d3, d4);
    out[element(3,1)]  = (SCALAR_TYPE)  det3x3( a1, a3, a4, b1, b3, b4, c1, c3, c4);
        
    out[element(0,2)]  = (SCALAR_TYPE)  det3x3( b1, b2, b4, c1, c2, c4, d1, d2, d4);
    out[element(1,2)]  = (SCALAR_TYPE) -det3x3( a1, a2, a4, c1, c2, c4, d1, d2, d4);
    out[element(2,2)]  = (SCALAR_TYPE)  det3x3( a1, a2, a4, b1, b2, b4, d1, d2, d4);
    out[element(3,2)]  = (SCALAR_TYPE) -det3x3( a1, a2, a4, b1, b2, b4, c1, c2, c4);
        
    out[element(0,3)]  = (SCALAR_TYPE) -det3x3( b1, b2, b3, c1, c2, c3, d1, d2, d3);
    out[element(1,3)]  = (SCALAR_TYPE)  det3x3( a1, a2, a3, c1, c2, c3, d1, d2, d3);
    out[element(2,3)]  = (SCALAR_TYPE) -det3x3( a1, a2, a3, b1, b2, b3, d1, d2, d3);
    out[element(3,3)]  = (SCALAR_TYPE)  det3x3( a1, a2, a3, b1, b2, b3, c1, c2, c3);
}

///////////////////////////////////////////////////////////////////////
// Function				:	invert
// Description			:	invert a 4 by 4 matrix
// Return Value			:	Determinant
// Comments				:
int			invertm(SCALAR_TYPE *d,const SCALAR_TYPE *s)	{
	int		i;
    double	det;

    adjoint(d,s);

    det = det4x4(s);

	if (det == 0) {
		identitym(d);
        return TRUE;
	}

    for (i=0; i<16; i++)
		d[i]		=	(SCALAR_TYPE) (d[i] / det);

	return FALSE;
}

///////////////////////////////////////////////////////////////////////
// Function				:	skewsymm
// Description			:	compute the skewed symmetic matrix
// Return Value			:	-
// Comments				:
void	skewsymm(SCALAR_TYPE *dest,const SCALAR_TYPE *src) {
	identitym(dest);

	dest[element(0,0)]	=	0;
	dest[element(1,1)]	=	0;
	dest[element(2,2)]	=	0;
	dest[element(0,1)]	=	-src[2];
	dest[element(0,2)]	=	src[1];
	dest[element(1,2)]	=	-src[0];
	dest[element(1,0)]	=	src[2];
	dest[element(2,0)]	=	-src[1];
	dest[element(2,1)]	=	src[0];
}

///////////////////////////////////////////////////////////////////////
// Function				:	determinantm
// Description			:	4 by 4 determinant computation
// Return Value			:	Determinant
// Comments				:
SCALAR_TYPE	determinantm(const SCALAR_TYPE *r) {
	return (SCALAR_TYPE) det4x4(r);
}

///////////////////////////////////////////////////////////////////////
// Function				:	identitym
// Description			:	create identity matrix
// Return Value			:	-
// Comments				:
void	identitym(SCALAR_TYPE *r) {
	int i;

	for (i=0;i<16;i++) r[i]	=	0;

	r[element(0,0)]	=	1;
	r[element(1,1)]	=	1;
	r[element(2,2)]	=	1;
	r[element(3,3)]	=	1;
}

///////////////////////////////////////////////////////////////////////
// Function				:	translatem
// Description			:	create translation matrix
// Return Value			:	-
// Comments				:
void	translatem(SCALAR_TYPE *r,const SCALAR_TYPE tx,const SCALAR_TYPE ty,const SCALAR_TYPE tz) {
	identitym(r);

	r[element(0,3)]	=	tx;
	r[element(1,3)]	=	ty;
	r[element(2,3)]	=	tz;
}

///////////////////////////////////////////////////////////////////////
// Function				:	scalem
// Description			:	create scale matrix
// Return Value			:	Determinant
// Comments				:
void	scalem(SCALAR_TYPE *r,const SCALAR_TYPE sx,const SCALAR_TYPE sy,const SCALAR_TYPE sz) {
	identitym(r);

	r[element(0,0)]	=	sx;
	r[element(1,1)]	=	sy;
	r[element(2,2)]	=	sz;
}

///////////////////////////////////////////////////////////////////////
// Function				:	rotatem
// Description			:	create a rotation matrix
// Return Value			:	-
// Comments				:	the angle is in degrees
void	rotatem(SCALAR_TYPE *r,const SCALAR_TYPE *v,const SCALAR_TYPE angle) {
	rotatem(r,v[0],v[1],v[2],angle);
}

///////////////////////////////////////////////////////////////////////
// Function				:	rotatem
// Description			:	create a rotation matrix
// Return Value			:	-
// Comments				:	the angle is in degrees
void	rotatem(SCALAR_TYPE *r,SCALAR_TYPE x,SCALAR_TYPE y,SCALAR_TYPE z,const SCALAR_TYPE angle) {
	double	s	=	cos(angle/2);
	double	sp	=	sin(angle/2);
	double	l	=	sqrt(x*x + y*y + z*z);

	// If this is a zero rotation, set the identity matrix
	if ((l == 0) || (angle==0)) identitym(r);
	else {
		double	a	=	x*sp/l;
		double	b	=	y*sp/l;
		double	c	=	z*sp/l;
		l			=	sqrt(a*a + b*b + c*c + s*s);
		a			/=	l;
		b			/=	l;
		c			/=	l;
		s			/=	l;

		r[element(0,0)] = (SCALAR_TYPE) (1-2*b*b-2*c*c);
		r[element(0,1)] = (SCALAR_TYPE) (2*a*b-2*s*c);
		r[element(0,2)] = (SCALAR_TYPE) (2*a*c+2*s*b);
		r[element(0,3)] = 0;
		r[element(1,0)] = (SCALAR_TYPE) (2*a*b+2*s*c);
		r[element(1,1)] = (SCALAR_TYPE) (1-2*a*a-2*c*c);
		r[element(1,2)] = (SCALAR_TYPE) (2*b*c-2*s*a);
		r[element(1,3)] = 0;
		r[element(2,0)] = (SCALAR_TYPE) (2*a*c-2*s*b);
		r[element(2,1)] = (SCALAR_TYPE) (2*b*c+2*s*a);
		r[element(2,2)] = (SCALAR_TYPE) (1-2*a*a-2*b*b);
		r[element(2,3)] = 0;
		r[element(3,0)] = 0;
		r[element(3,1)] = 0;
		r[element(3,2)] = 0;
		r[element(3,3)] = 1;
	}
}

///////////////////////////////////////////////////////////////////////
// Function				:	skewm
// Description			:	create a skew matrix
// Return Value			:	-
// Comments				:	the angle is in degrees
void	skewm(SCALAR_TYPE *r,const SCALAR_TYPE angle,const SCALAR_TYPE dx1,const SCALAR_TYPE dy1,const SCALAR_TYPE dz1,const SCALAR_TYPE dx2,const SCALAR_TYPE dy2,const SCALAR_TYPE dz2) {
	VECTOR_TYPE	v1,v2,d;
	MATRIX_TYPE	R,S,tmp,tmp2;
	SCALAR_TYPE	costheta,sintheta,skew;

	v1[0]	=	dx1;
	v1[1]	=	dy1;
	v1[2]	=	dz1;
	normalizev(v1);
	
	v2[0]	=	dx2;
	v2[1]	=	dy2;
	v2[2]	=	dz2;
	normalizev(v2);

	crossvv(d,v1,v2);
	normalizev(d);

	costheta	=	dotvv(v1,v2);
	sintheta	=	sqrt(1 - costheta*costheta);
	skew		=	tan((SCALAR_TYPE) angle + (SCALAR_TYPE) acos(sintheta))*sintheta - costheta;

	crossvv(v1,d,v2);
	normalizev(v1);

	R[element(0,0)]	=	d[0];
	R[element(1,0)]	=	d[1];
	R[element(2,0)]	=	d[2];
	R[element(3,0)]	=	0;
	R[element(0,1)]	=	v1[0];
	R[element(1,1)]	=	v1[1];
	R[element(2,1)]	=	v1[2];
	R[element(3,1)]	=	0;
	R[element(0,2)]	=	v2[0];
	R[element(1,2)]	=	v2[1];
	R[element(2,2)]	=	v2[2];
	R[element(3,2)]	=	0;
	R[element(0,3)]	=	0;
	R[element(1,3)]	=	0;
	R[element(2,3)]	=	0;
	R[element(3,3)]	=	1;

	identitym(S);
	S[element(2,1)]	=	-skew;

	transposem(tmp,R);
	mulmm(tmp2,S,tmp);
	mulmm(r,R,tmp2);
}


#define	S		0
#define	VX		1
#define	VY		2
#define	VZ		3

///////////////////////////////////////////////////////////////////////
// Function				:	rotatem
// Description			:	create a rotation matrix
// Return Value			:	-
// Comments				:
void	rotatem(SCALAR_TYPE *to,const SCALAR_TYPE *from) {
	to[element(0,0)]	=	1-2*from[VY]*from[VY] - 2*from[VZ]*from[VZ];
	to[element(0,1)]	=	2*from[VX]*from[VY] - 2*from[S]*from[VZ];
	to[element(0,2)]	=	2*from[VX]*from[VZ] + 2*from[S]*from[VY];
	to[element(1,0)]	=	2*from[VX]*from[VY] + 2*from[S]*from[VZ];
	to[element(1,1)]	=	1-2*from[VX]*from[VX] - 2*from[VZ]*from[VZ];
	to[element(1,2)]	=	2*from[VY]*from[VZ] - 2*from[S]*from[VX];
	to[element(2,0)]	=	2*from[VX]*from[VZ] - 2*from[S]*from[VY];
	to[element(2,1)]	=	2*from[VY]*from[VZ] + 2*from[S]*from[VX];
	to[element(2,2)]	=	1-2*from[VX]*from[VX] - 2*from[VY]*from[VY];
	to[element(0,3)]	=	0;
	to[element(1,3)]	=	0;
	to[element(2,3)]	=	0;
	to[element(3,3)]	=	1;
	to[element(3,0)]	=	0;
	to[element(3,1)]	=	0;
	to[element(3,2)]	=	0;
}

#undef S
#undef VX
#undef VY
#undef VZ

