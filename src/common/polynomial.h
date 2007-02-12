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
//  File				:	polynomial.h
//  Description			:	Various polynimial related functions
//
////////////////////////////////////////////////////////////////////////
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H



////////////////////////////////////////////////////////////////////////////
//
//
//
//	Misc polynomial solving. Defined with templates.
//
//
//
////////////////////////////////////////////////////////////////////////////
#define     cbrt(x)     ((x) > 0.0 ? pow(x, 1.0/3.0) : \
						((x) < 0.0 ? -pow(-x, 1.0/3.0) : 0.0))

template <class T> inline	int	solveQuadric(T a,T b,T c,T *r) {
	

	if (a != 0) {
		const double	delta	=	b*b - 4*a*c;

		if (delta < 0)	return	0;
		else if (delta == 0) {
			r[0]	=	(T) (- b) / (2*a);
			return 1;
		} else {
			double	sqrtDelta	=	sqrt(delta);

			r[0]	=	(T) (-sqrtDelta - b) / (2*a);
			r[1]	=	(T) (sqrtDelta - b) / (2*a);

			return 2;
		}
	} else if (b != 0) {
		r[0]	=	-c/b;
		return 1;
	} else {
		return 0;
	}
}

template <class T> inline	int solveCubic(T c[4],T s[3]) {
    int     i, num;
    double	sub;
    double	A, B, C;
    double	sq_A, p, q;
    double	cb_p, D;
	double	sd[3];

    A		= c[2] / c[3];
    B		= c[1] / c[3];
    C		= c[0] / c[3];

    sq_A	= A * A;
    p		= (1.0/3 * (- 1.0/3 * sq_A + B));
    q		= (1.0/2 * (2.0/27 * A * sq_A - 1.0/3 * A * B + C));

    cb_p	= p * p * p;
    D		= q * q + cb_p;

    if (D == 0) {
		if (q == 0) {
			sd[0]		= 0;
			num			= 1;
		} else 	{
			double u	= (cbrt(-q));
			sd[0]		= 2 * u;
			sd[1]		= -u;
			num			= 2;
		}
    } else if (D < 0) {
		double phi		= (1.0/3 * acos(-q / sqrt(-cb_p)));
		double t		= (2 * sqrt(-p));

		sd[0]			=   t * cos(phi);
		sd[1]			= - t * cos(phi + C_PI / 3);
		sd[2]			= - t * cos(phi - C_PI / 3);
		num				= 3;
    } else {
		double sqrt_D	= sqrt(D);
		double u		= cbrt(sqrt_D - q);
		double v		= -cbrt(sqrt_D + q);

		sd[0]			= (u + v);
		num				= 1;
    }

    sub = (1.0/3 * A);

    for (i=0;i<num;++i)
		s[i] = (T) (sd[i] - sub);

    return num;
}


template <class T> inline	int solveQuartic(T c[5],T s[4]) {
    double		coeffs[4];
    double		z, u, v, sub;
    double		A, B, C, D;
    double		sq_A, p, q, r;
    int			i, num;
	double		sd[4];

    A = c[ 3 ] / c[ 4 ];
    B = c[ 2 ] / c[ 4 ];
    C = c[ 1 ] / c[ 4 ];
    D = c[ 0 ] / c[ 4 ];


    sq_A	= A * A;
    p		= (- 3.0/8 * sq_A + B);
    q		= (1.0/8 * sq_A * A - 1.0/2 * A * B + C);
    r		= (-3.0/256*sq_A*sq_A + 1.0/16*sq_A*B - 1.0/4*A*C + D);

    if (r == 0) {
		coeffs[ 0 ] = q;
		coeffs[ 1 ] = p;
		coeffs[ 2 ] = 0;
		coeffs[ 3 ] = 1;

		num			= solveCubic<double>(coeffs, sd);

		sd[num++]	= 0;
    } else {
		coeffs[ 0 ] = 1.0/2 * r * p - 1.0/8 * q * q;
		coeffs[ 1 ] = - r;
		coeffs[ 2 ] = - 1.0/2 * p;
		coeffs[ 3 ] = 1;

		solveCubic<double>(coeffs, sd);

		z = sd[ 0 ];

		u = z * z - r;
		v = 2 * z - p;

		if (u == 0)
			u = 0;
		else if (u > 0)
			u = sqrt(u);
		else
			return 0;

		if (v == 0)
			v = 0;
		else if (v > 0)
			v = sqrt(v);
		else
			return 0;

		coeffs[ 0 ] = z - u;
		coeffs[ 1 ] = q < 0 ? -v : v;
		coeffs[ 2 ] = 1;

		num = solveQuadric<double>(coeffs[2],coeffs[1],coeffs[0],sd);

		coeffs[ 0 ]= z + u;
		coeffs[ 1 ] = q < 0 ? v : -v;
		coeffs[ 2 ] = 1;

		num += solveQuadric<double>(coeffs[2],coeffs[1],coeffs[0],sd + num);
    }

    sub = 1.0/4 * A;

    for (i = 0; i < num; ++i) {
		s[i] = (T) (sd[i] - sub);
	}

    return num;
}


#endif

