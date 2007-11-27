///////////////////////////////////////////////////////////////////////
//
//  File				:	mathSpec.h
//  Description			:	Type independent header
//
////////////////////////////////////////////////////////////////////////




inline	void	initv(SCALAR_TYPE *r,const SCALAR_TYPE x) {
	r[0]	=	x;
	r[1]	=	x;
	r[2]	=	x;
}

inline	void	initv(SCALAR_TYPE *r,const SCALAR_TYPE x,const SCALAR_TYPE y,const SCALAR_TYPE z) {
	r[0]	=	x;
	r[1]	=	y;
	r[2]	=	z;
}

inline	void	addvv(SCALAR_TYPE *result,const SCALAR_TYPE *s1,const SCALAR_TYPE *s2) {
	result[0]	=	s1[0] + s2[0];
	result[1]	=	s1[1] + s2[1];
	result[2]	=	s1[2] + s2[2];
}

inline	void	addvv(SCALAR_TYPE *result,const SCALAR_TYPE *s1) {
	result[0]	+=	s1[0];
	result[1]	+=	s1[1];
	result[2]	+=	s1[2];
}

inline	void	addvf(SCALAR_TYPE *result,const SCALAR_TYPE s1) {
	result[0]	+=	s1;
	result[1]	+=	s1;
	result[2]	+=	s1;
}

inline	void	subvf(SCALAR_TYPE *result,const SCALAR_TYPE s1) {
	result[0]	-=	s1;
	result[1]	-=	s1;
	result[2]	-=	s1;
}

inline	void	addvf(SCALAR_TYPE *result,const SCALAR_TYPE *s1,const SCALAR_TYPE s2) {
	result[0]	=	s1[0] + s2;
	result[1]	=	s1[1] + s2;
	result[2]	=	s1[2] + s2;
}

inline	void	subvf(SCALAR_TYPE *result,const SCALAR_TYPE *s1,const SCALAR_TYPE s2) {
	result[0]	=	s1[0] - s2;
	result[1]	=	s1[1] - s2;
	result[2]	=	s1[2] - s2;
}

inline	void	subvv(SCALAR_TYPE *result,const SCALAR_TYPE *s1,const SCALAR_TYPE *s2) {
	result[0]	=	s1[0] - s2[0];
	result[1]	=	s1[1] - s2[1];
	result[2]	=	s1[2] - s2[2];
}

inline	void	subvv(SCALAR_TYPE *result,const SCALAR_TYPE *s1) {
	result[0]	-=	s1[0];
	result[1]	-=	s1[1];
	result[2]	-=	s1[2];
}

inline	void	mulvf(SCALAR_TYPE *result,const SCALAR_TYPE *v,const SCALAR_TYPE m) {
	result[0]	=	v[0]*m;
	result[1]	=	v[1]*m;
	result[2]	=	v[2]*m;
}

inline	void	mulvf(SCALAR_TYPE *result,const SCALAR_TYPE m) {
	result[0]	*=	m;
	result[1]	*=	m;
	result[2]	*=	m;
}

inline	void	mulvv(SCALAR_TYPE	*result,const SCALAR_TYPE *s1,const SCALAR_TYPE *s2) {
	result[0]	=	s1[0]*s2[0];
	result[1]	=	s1[1]*s2[1];
	result[2]	=	s1[2]*s2[2];
}

inline	void	mulvv(SCALAR_TYPE *result,const SCALAR_TYPE *s1) {
	result[0]	*=	s1[0];
	result[1]	*=	s1[1];
	result[2]	*=	s1[2];
}

inline	void	divvv(SCALAR_TYPE *result,const SCALAR_TYPE *s1,const SCALAR_TYPE *s2) {
	result[0]	=	s1[0] / s2[0];
	result[1]	=	s1[1] / s2[1];
	result[2]	=	s1[2] / s2[2];
}

inline	void	divvv(SCALAR_TYPE *result,const SCALAR_TYPE *s1) {
	result[0]	/=	s1[0];
	result[1]	/=	s1[1];
	result[2]	/=	s1[2];
}

inline	void	crossvv(SCALAR_TYPE *result,const SCALAR_TYPE *s1,const SCALAR_TYPE *s2) {
	result[0]	=	(s1[1]*s2[2] - s1[2]*s2[1]);
	result[1]	=	(s1[2]*s2[0] - s1[0]*s2[2]);
	result[2]	=	(s1[0]*s2[1] - s1[1]*s2[0]);
}

inline	SCALAR_TYPE	dotvv(const SCALAR_TYPE *s1,const SCALAR_TYPE *s2) {
	return (SCALAR_TYPE) (s1[0]*s2[0] + s1[1]*s2[1] + s1[2]*s2[2]);
}

inline	void	interpolatev(SCALAR_TYPE *result,const SCALAR_TYPE *s1,const SCALAR_TYPE *s2,const SCALAR_TYPE alpha) {
	result[0]	=	(float) (s1[0]*(1.0-(double)alpha) + s2[0]*(double)alpha);
	result[1]	=	(float) (s1[1]*(1.0-(double)alpha) + s2[1]*(double)alpha);
	result[2]	=	(float) (s1[2]*(1.0-(double)alpha) + s2[2]*(double)alpha);
}

inline	SCALAR_TYPE	interpolatea(const SCALAR_TYPE s1,const SCALAR_TYPE s2,const SCALAR_TYPE alpha) {
	if (s2 >= s1) {
		SCALAR_TYPE		d	=	fmod((SCALAR_TYPE) (s2 - s1),(SCALAR_TYPE) (2*C_PI));
		if (d > C_PI) {
			return	s2	+	(SCALAR_TYPE) ((2*C_PI - d)*(1-alpha));
		} else {
			return	s1	+	(SCALAR_TYPE) (d*alpha);
		}
		

		
	} else {
		return interpolatea(s2,s1,1-alpha);
	}
}

inline	void	movvv(SCALAR_TYPE *dest,const SCALAR_TYPE *src) {
	dest[0]		=	src[0];
	dest[1]		=	src[1];
	dest[2]		=	src[2];
}

inline	SCALAR_TYPE	lengthv(const SCALAR_TYPE *v) {
	return SQRT(dotvv(v,v));
}

inline	void	normalizev(SCALAR_TYPE *r,const SCALAR_TYPE *v) {
	const double	l	=	1 / sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);

	r[0]	=	(SCALAR_TYPE) (v[0]*l);
	r[1]	=	(SCALAR_TYPE) (v[1]*l);
	r[2]	=	(SCALAR_TYPE) (v[2]*l);
}

inline	void	normalizev(SCALAR_TYPE *v) {
	const double	l	=	1 / sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);

	v[0]	=	(SCALAR_TYPE) (v[0]*l);
	v[1]	=	(SCALAR_TYPE) (v[1]*l);
	v[2]	=	(SCALAR_TYPE) (v[2]*l);
}

inline	void	mulmm(SCALAR_TYPE *result,const SCALAR_TYPE *s1,const SCALAR_TYPE *s2) {
	int i,j,k;

	for (i=0;i<4;i++)
		for (j=0;j<4;j++) {
				double		dest		=	0;

				for (k=0;k<4;k++) dest	+=	s1[element(i,k)]*s2[element(k,j)];

				result[element(i,j)]	=	(SCALAR_TYPE) dest;
		}
}

inline	void	mulmm(SCALAR_TYPE *result,const SCALAR_TYPE *s1,const SCALAR_TYPE *s2,const SCALAR_TYPE *s3) {
	MATRIX_TYPE	mtmp;

	mulmm(mtmp,s1,s2);
	mulmm(result,mtmp,s3);
}

inline	void	mulmp(SCALAR_TYPE *result,const SCALAR_TYPE *s1,const SCALAR_TYPE *s2) {
	const	SCALAR_TYPE	x		=	s1[element(0,0)]*s2[0]+s1[element(0,1)]*s2[1]+s1[element(0,2)]*s2[2]+s1[element(0,3)];
	const	SCALAR_TYPE	y		=	s1[element(1,0)]*s2[0]+s1[element(1,1)]*s2[1]+s1[element(1,2)]*s2[2]+s1[element(1,3)];
	const	SCALAR_TYPE	z		=	s1[element(2,0)]*s2[0]+s1[element(2,1)]*s2[1]+s1[element(2,2)]*s2[2]+s1[element(2,3)];
	const	SCALAR_TYPE	w		= 	s1[element(3,0)]*s2[0]+s1[element(3,1)]*s2[1]+s1[element(3,2)]*s2[2]+s1[element(3,3)];
	

	if (w != 1) {
		const double	l	=	1 / (double) w;

		result[0]	=	(SCALAR_TYPE) (x*l);
		result[1]	=	(SCALAR_TYPE) (y*l);
		result[2]	=	(SCALAR_TYPE) (z*l);
	} else {
		result[0]	=	x;
		result[1]	=	y;
		result[2]	=	z;
	}
}

inline	void	mulmv(SCALAR_TYPE *result,const SCALAR_TYPE *s1,const SCALAR_TYPE *s2) {
	const	SCALAR_TYPE	x		=	s1[element(0,0)]*s2[0]+s1[element(0,1)]*s2[1]+s1[element(0,2)]*s2[2];
	const	SCALAR_TYPE	y		=	s1[element(1,0)]*s2[0]+s1[element(1,1)]*s2[1]+s1[element(1,2)]*s2[2];
	const	SCALAR_TYPE	z		=	s1[element(2,0)]*s2[0]+s1[element(2,1)]*s2[1]+s1[element(2,2)]*s2[2];
	
	result[0]	=	x;
	result[1]	=	y;
	result[2]	=	z;
}

inline	void	mulmn(SCALAR_TYPE *result,const SCALAR_TYPE *s1,const SCALAR_TYPE *s2) {
	const	SCALAR_TYPE	x		=	s1[element(0,0)]*s2[0]+s1[element(1,0)]*s2[1]+s1[element(2,0)]*s2[2];
	const	SCALAR_TYPE	y		=	s1[element(0,1)]*s2[0]+s1[element(1,1)]*s2[1]+s1[element(2,1)]*s2[2];
	const	SCALAR_TYPE	z		=	s1[element(0,2)]*s2[0]+s1[element(1,2)]*s2[1]+s1[element(2,2)]*s2[2];

	result[0]	=	x;
	result[1]	=	y;
	result[2]	=	z;
}

inline	void	mulmp4(SCALAR_TYPE *result,const SCALAR_TYPE *s1,const SCALAR_TYPE *s2) {
	const	SCALAR_TYPE	x		=	s1[element(0,0)]*s2[0]+s1[element(0,1)]*s2[1]+s1[element(0,2)]*s2[2]+s1[element(0,3)]*s2[3];
	const	SCALAR_TYPE	y		=	s1[element(1,0)]*s2[0]+s1[element(1,1)]*s2[1]+s1[element(1,2)]*s2[2]+s1[element(1,3)]*s2[3];
	const	SCALAR_TYPE	z		=	s1[element(2,0)]*s2[0]+s1[element(2,1)]*s2[1]+s1[element(2,2)]*s2[2]+s1[element(2,3)]*s2[3];
	const	SCALAR_TYPE	w		= 	s1[element(3,0)]*s2[0]+s1[element(3,1)]*s2[1]+s1[element(3,2)]*s2[2]+s1[element(3,3)]*s2[3];
	

	result[0]	=	x;
	result[1]	=	y;
	result[2]	=	z;
	result[3]	=	w;
}


inline	void	mulmv4(SCALAR_TYPE *result,const SCALAR_TYPE *s1,const SCALAR_TYPE *s2) {
	const	SCALAR_TYPE	x		=	s1[element(0,0)]*s2[0]+s1[element(0,1)]*s2[1]+s1[element(0,2)]*s2[2];
	const	SCALAR_TYPE	y		=	s1[element(1,0)]*s2[0]+s1[element(1,1)]*s2[1]+s1[element(1,2)]*s2[2];
	const	SCALAR_TYPE	z		=	s1[element(2,0)]*s2[0]+s1[element(2,1)]*s2[1]+s1[element(2,2)]*s2[2];
	const	SCALAR_TYPE	w		= 	s1[element(3,0)]*s2[0]+s1[element(3,1)]*s2[1]+s1[element(3,2)]*s2[2];
	
	result[0]	=	x;
	result[1]	=	y;
	result[2]	=	z;
	result[3]	=	w;
}

inline	void	mulmn4(SCALAR_TYPE *result,const SCALAR_TYPE *s1,const SCALAR_TYPE *s2) {
	const	SCALAR_TYPE	x		=	s1[element(0,0)]*s2[0]+s1[element(1,0)]*s2[1]+s1[element(2,0)]*s2[2];
	const	SCALAR_TYPE	y		=	s1[element(0,1)]*s2[0]+s1[element(1,1)]*s2[1]+s1[element(2,1)]*s2[2];
	const	SCALAR_TYPE	z		=	s1[element(0,2)]*s2[0]+s1[element(1,2)]*s2[1]+s1[element(2,2)]*s2[2];
	const	SCALAR_TYPE	w		= 	s1[element(0,3)]*s2[0]+s1[element(1,3)]*s2[1]+s1[element(2,3)]*s2[2];

	result[0]	=	x;
	result[1]	=	y;
	result[2]	=	z;
	result[3]	=	w;
}

inline	void	mulpm(SCALAR_TYPE  *result,const SCALAR_TYPE *s1,const SCALAR_TYPE *s2) {
	const	SCALAR_TYPE	x		=	s1[0]*s2[element(0,0)] + s1[1]*s2[element(1,0)] + s1[2]*s2[element(2,0)] + s2[element(3,0)];
	const	SCALAR_TYPE	y		=	s1[0]*s2[element(0,1)] + s1[1]*s2[element(1,1)] + s1[2]*s2[element(2,1)] + s2[element(3,1)];
	const	SCALAR_TYPE	z		=	s1[0]*s2[element(0,2)] + s1[1]*s2[element(1,2)] + s1[2]*s2[element(2,2)] + s2[element(3,2)];
	const	SCALAR_TYPE	w		=	s1[0]*s2[element(0,3)] + s1[1]*s2[element(1,3)] + s1[2]*s2[element(2,3)] + s2[element(3,3)];

	if (w != 1) {
		const double	l	=	1 / (double) w;

		result[0]	=	(SCALAR_TYPE) (x*l);
		result[1]	=	(SCALAR_TYPE) (y*l);
		result[2]	=	(SCALAR_TYPE) (z*l);
	} else {
		result[0]	=	x;
		result[1]	=	y;
		result[2]	=	z;
	}
}

inline	void	mulpm4(SCALAR_TYPE *result,const SCALAR_TYPE *s1,const SCALAR_TYPE *s2) {
	const	SCALAR_TYPE	x		=	s1[0]*s2[element(0,0)] + s1[1]*s2[element(1,0)] + s1[2]*s2[element(2,0)] + s1[3]*s2[element(3,0)];
	const	SCALAR_TYPE	y		=	s1[0]*s2[element(0,1)] + s1[1]*s2[element(1,1)] + s1[2]*s2[element(2,1)] + s1[3]*s2[element(3,1)];
	const	SCALAR_TYPE	z		=	s1[0]*s2[element(0,2)] + s1[1]*s2[element(1,2)] + s1[2]*s2[element(2,2)] + s1[3]*s2[element(3,2)];
	const	SCALAR_TYPE	w		=	s1[0]*s2[element(0,3)] + s1[1]*s2[element(1,3)] + s1[2]*s2[element(2,3)] + s1[3]*s2[element(3,3)];
	

	result[0]	=	x;
	result[1]	=	y;
	result[2]	=	z;
	result[3]	=	w;
}


inline	void	mulvm(SCALAR_TYPE  *result,const SCALAR_TYPE *s1,const SCALAR_TYPE *s2) {
	const	SCALAR_TYPE	x		=	s1[0]*s2[element(0,0)] + s1[1]*s2[element(1,0)] + s1[2]*s2[element(2,0)];
	const	SCALAR_TYPE	y		=	s1[0]*s2[element(0,1)] + s1[1]*s2[element(1,1)] + s1[2]*s2[element(2,1)];
	const	SCALAR_TYPE	z		=	s1[0]*s2[element(0,2)] + s1[1]*s2[element(1,2)] + s1[2]*s2[element(2,2)];

	result[0]	=	x;
	result[1]	=	y;
	result[2]	=	z;
}

inline	void	mulmf(SCALAR_TYPE  *result,const SCALAR_TYPE *s,const SCALAR_TYPE t) {
	int	i;

	for (i=0;i<16;i++)
		result[i]	=	s[i]*t;
}

inline	void	mulmf(SCALAR_TYPE  *result,const SCALAR_TYPE t) {
	int	i;

	for (i=0;i<16;i++)
		result[i]	*=	t;
}

inline	void	addmm(SCALAR_TYPE  *result,const SCALAR_TYPE *s1,const SCALAR_TYPE *s2) {
	int	i;

	for (i=0;i<16;i++)
		result[i]	=	s1[i] + s2[i];
}

inline	void	submm(SCALAR_TYPE  *result,const SCALAR_TYPE *s1,const SCALAR_TYPE *s2) {
	int	i;

	for (i=0;i<16;i++)
		result[i]	=	s1[i] - s2[i];
}

inline	void	addmm(SCALAR_TYPE  *result,const SCALAR_TYPE *s) {
	int	i;

	for (i=0;i<16;i++)
		result[i]	+=	s[i];
}

inline	void	submm(SCALAR_TYPE  *result,const SCALAR_TYPE *s) {
	int	i;

	for (i=0;i<16;i++)
		result[i]	-=	s[i];
}


inline	void	movmm(SCALAR_TYPE *dest,const SCALAR_TYPE *src) {
	int i;

	for (i=0;i<16;i++)
		dest[i]	=	src[i];
}

inline void		transposem(SCALAR_TYPE *dest,const SCALAR_TYPE *src) {
	int i,j;

	for (i=0;i<4;i++) {
		for (j=0;j<4;j++) {
			dest[element(i,j)] = src[element(j,i)];
		}
	}
}

inline	SCALAR_TYPE	area(SCALAR_TYPE x1,SCALAR_TYPE y1,SCALAR_TYPE x2,SCALAR_TYPE y2,SCALAR_TYPE x3,SCALAR_TYPE y3) {
	const double	acx = x1 - x3;
	const double	bcx = x2 - x3;
	const double	acy = y1 - y3;
	const double	bcy = y2 - y3;
	return (SCALAR_TYPE) (acx * bcy - acy * bcx);
}

inline	void	mulmvv(SCALAR_TYPE *dest,const SCALAR_TYPE *s1,const SCALAR_TYPE *s2) {
	dest[element(0,0)]	=	s1[0]*s2[0];
	dest[element(1,0)]	=	s1[1]*s2[0];
	dest[element(2,0)]	=	s1[2]*s2[0];
	dest[element(3,0)]	=	0;
	dest[element(0,1)]	=	s1[0]*s2[1];
	dest[element(1,1)]	=	s1[1]*s2[1];
	dest[element(2,1)]	=	s1[2]*s2[1];
	dest[element(3,1)]	=	0;
	dest[element(0,2)]	=	s1[0]*s2[2];
	dest[element(1,2)]	=	s1[1]*s2[2];
	dest[element(2,2)]	=	s1[2]*s2[2];
	dest[element(3,2)]	=	0;
	dest[element(0,3)]	=	0;
	dest[element(1,3)]	=	0;
	dest[element(2,3)]	=	0;
	dest[element(3,3)]	=	1;
}

inline	SCALAR_TYPE	clampf(const SCALAR_TYPE mi,const SCALAR_TYPE l,const SCALAR_TYPE ma) {
	return (l < mi ? mi : (l > ma ? ma : l));
}

inline	void	clampv(const SCALAR_TYPE *mi,SCALAR_TYPE *l,const SCALAR_TYPE *ma) {
	l[0]	=	(l[0] < mi[0] ? mi[0] : (l[0] > ma[0] ? ma[0] : l[0]));
	l[1]	=	(l[1] < mi[1] ? mi[1] : (l[1] > ma[1] ? ma[1] : l[1]));
	l[2]	=	(l[2] < mi[2] ? mi[2] : (l[2] > ma[2] ? ma[2] : l[2]));
}





////////////////////////////////////////////////////////////////////////////
//
//
//
//	Misc box routines
//
//
//
////////////////////////////////////////////////////////////////////////////




// True if point v is inside the box (bmin,bmax)
inline	int		inBox(const SCALAR_TYPE *bmin,const SCALAR_TYPE *bmax,const SCALAR_TYPE *v) {
	int	i;

	for (i=0;i<3;i++) {
		if ((v[i] < bmin[i]) || (v[i] > bmax[i])) return FALSE;
	}

	return TRUE;
}



// Expand the box (bmin,bmax) so that point v is inside it
inline	void	addBox(SCALAR_TYPE *bmin,SCALAR_TYPE *bmax,const SCALAR_TYPE *v) {
	int	i;

	for (i=0;i<3;i++) {
		if (v[i] < bmin[i])	bmin[i]	=	v[i];
		if (v[i] > bmax[i]) bmax[i] =	v[i];
	}
}

// True if two given boxes intersect
inline	int		intersectBox(const SCALAR_TYPE *bmin1,const SCALAR_TYPE *bmax1,const SCALAR_TYPE *bmin2,const SCALAR_TYPE *bmax2) {
	int	i;

	for (i=0;i<3;i++) {
		if ((bmin1[i] > bmax2[i]) || (bmax1[i] < bmin2[i]))	return	FALSE;
	}

	return	TRUE;
}

// True if a ray intersects a box
inline	int		intersectBox(const SCALAR_TYPE *bmin,const SCALAR_TYPE *bmax,const SCALAR_TYPE *F,const SCALAR_TYPE *D,const double *invD,SCALAR_TYPE &tmin,SCALAR_TYPE &tmax) {
	SCALAR_TYPE		tnear,tfar;
	SCALAR_TYPE		t1,t2;
	unsigned int	i;

	tnear	=	tmin;
	tfar	=	tmax;

	for (i=0;i<3;i++) {
		if (D[i] == 0) {
			if ((F[i] > bmax[i]) || (F[i] < bmin[i])) return FALSE;
		} else {
			t1		=	(SCALAR_TYPE) ((bmin[i] - F[i]) * invD[i]);
			t2		=	(SCALAR_TYPE) ((bmax[i] - F[i]) * invD[i]);

			if (t1 < t2) {
				if (t1 > tnear)	tnear = t1;
				if (t2 < tfar)	tfar = t2;
			} else {
				if (t2 > tnear)	tnear = t2;
				if (t1 < tfar)	tfar = t1;
			}

			if (tnear > tfar) return FALSE;
		}
	}

	tmin	=	tnear;
	tmax	=	tfar;

	return TRUE;
}




// If a ray intersects a box, returned t is < tmax (the same as above but takes inverse of the direction)
inline	SCALAR_TYPE		nearestBox(const SCALAR_TYPE *bmin,const SCALAR_TYPE *bmax,const SCALAR_TYPE *F,const double *invD,SCALAR_TYPE tmin,SCALAR_TYPE tmax) {
	SCALAR_TYPE		tnear,tfar;
	SCALAR_TYPE		t1,t2;
	unsigned int	i;

	tnear	=	tmin;
	tfar	=	tmax;

	for (i=0;i<3;i++) {
		t1		=	(SCALAR_TYPE) ((bmin[i] - F[i]) * invD[i]);
		t2		=	(SCALAR_TYPE) ((bmax[i] - F[i]) * invD[i]);

		if (t1 < t2) {
			if (t1 > tnear)	tnear = t1;
			if (t2 < tfar)	tfar = t2;
		} else {
			if (t2 > tnear)	tnear = t2;
			if (t1 < tfar)	tfar = t1;
		}

		if (tnear > tfar) return C_INFINITY;
	}
	
	// return nearest t if we're external
	return (SCALAR_TYPE) tnear;
}



// Reflect I around N
inline	void	reflect(SCALAR_TYPE *r,const SCALAR_TYPE *I,const SCALAR_TYPE *N) {
	mulvf(r,N,-2*dotvv(N,I));
	addvv(r,I);
}

// Refrect I around N
inline	void	refract(SCALAR_TYPE *r,const SCALAR_TYPE *I,const SCALAR_TYPE *N,SCALAR_TYPE eta) {
	VECTOR_TYPE	vtmp;
	SCALAR_TYPE	IdotN,k;
	IdotN	=	dotvv(N,I); 
	k		=	1 - eta*eta*(1-IdotN*IdotN);
	if (k <= 0) {
		//initv(r,0);
		movvv(r,I);
	} else	{
		mulvf(vtmp,N,(eta*IdotN+SQRT(k)));
		mulvf(r,I,eta);
		subvv(r,vtmp);
	}
}

// The fresnel function
inline	void	fresnel(const SCALAR_TYPE *I,const SCALAR_TYPE *N,SCALAR_TYPE eta,SCALAR_TYPE &Kr,SCALAR_TYPE &Kt,SCALAR_TYPE *R,SCALAR_TYPE *T) {
	const SCALAR_TYPE	e		=	1 / eta;
	const SCALAR_TYPE	c		=	-dotvv(I,N);
	const SCALAR_TYPE	t		=	e*e+c*c-1;
	const SCALAR_TYPE	g		=	SQRT(max(t,0));
	const SCALAR_TYPE	a		=	(g - c) / (g + c);
	const SCALAR_TYPE	b		=	(c*(g+c) - 1) / (c*(g-c) + 1);

	Kr			=	0.5f*a*a*(1 + b*b);
	Kr			=	min(Kr,1);
	Kr			=	max(Kr,0);
	Kt			=	1 - Kr;
	reflect(R,I,N);
	refract(T,I,N,eta);
}

inline SCALAR_TYPE ptlined(SCALAR_TYPE *A,SCALAR_TYPE *B,SCALAR_TYPE *P) {
	SCALAR_TYPE vtmp[3],vtmp2[3],vtmp3[3];
	SCALAR_TYPE l;

	subvv(vtmp,P,B);
	subvv(vtmp2,A,B);
	if (dotvv(vtmp,vtmp2) <= 0) {
		l	=	SQRT(dotvv(vtmp,vtmp));
	} else {
		mulvf(vtmp2,-1);
		subvv(vtmp,P,A);
		if (dotvv(vtmp,vtmp2) <= 0) {
			l = SQRT(dotvv(vtmp,vtmp));
		} else {
			subvv(vtmp,B,A);
			subvv(vtmp2,B,P);
			crossvv(vtmp3,vtmp,vtmp2);
			l = SQRT(dotvv(vtmp3,vtmp3))/SQRT(dotvv(vtmp,vtmp));
		}
	}
	return l;
}













////////////////////////////////////////////////////////////////////////////
//
//
//
//	Misc matrix operations that are too long to implement as inline
//	These are defined in algebra.cpp
//
//
//
////////////////////////////////////////////////////////////////////////////
void	skewsymm(SCALAR_TYPE *,const SCALAR_TYPE *);										// Create a skew symmetric matrix from matrix
SCALAR_TYPE	determinantm(const SCALAR_TYPE *);												// Take the determinant of a 4x4 matrix
void	identitym(SCALAR_TYPE *);															// Construct identity matrix
void	translatem(SCALAR_TYPE *,const SCALAR_TYPE,const SCALAR_TYPE,const SCALAR_TYPE);	// Construct translate matrix
void	scalem(SCALAR_TYPE *,const SCALAR_TYPE,const SCALAR_TYPE,const SCALAR_TYPE);		// Construct scale matrix
void	rotatem(SCALAR_TYPE *,const SCALAR_TYPE *,const SCALAR_TYPE);						// Construct rotate matrix (the second argument is the rotation vector)
void	rotatem(SCALAR_TYPE *,SCALAR_TYPE,SCALAR_TYPE,SCALAR_TYPE,const SCALAR_TYPE);		// Construct rotate matrix (the arguments are: result,x,y,z coordinates of the rotation vector and angle to rotate)
void	rotatem(SCALAR_TYPE *,const SCALAR_TYPE *);
void	skewm(SCALAR_TYPE *,const SCALAR_TYPE,const SCALAR_TYPE,const SCALAR_TYPE,const SCALAR_TYPE,const SCALAR_TYPE,const SCALAR_TYPE,const SCALAR_TYPE);
int		invertm(SCALAR_TYPE *,const SCALAR_TYPE *);											// Invert a matrix. Returns 0 if the inversion is successful 1 otherwise (i.e. matrix is singular)







///////////////////////////////////////////////////////////////////////
// Invert a rigid body transformation
inline	void	invertRigid(SCALAR_TYPE *dest,const SCALAR_TYPE *src) {
	MATRIX_TYPE	R,Rt,T;

	movmm(Rt,src);
	Rt[element(0,3)]	=	0;
	Rt[element(1,3)]	=	0;
	Rt[element(2,3)]	=	0;
	transposem(R,Rt);

	identitym(T);
	T[element(0,3)]		=	-src[element(0,3)];
	T[element(1,3)]		=	-src[element(1,3)];
	T[element(2,3)]		=	-src[element(2,3)];

	mulmm(dest,R,T);
}

///////////////////////////////////////////////////////////////////////
// Make a matrix a rotation
inline	void	makeRotation(SCALAR_TYPE *M) {
	VECTOR_TYPE	vx,vy,vz;
	VECTOR_TYPE	ux,uy,uz;

	initv(vx,M[element(0,0)],M[element(1,0)],M[element(2,0)]);
	initv(vy,M[element(0,1)],M[element(1,1)],M[element(2,1)]);
	initv(vz,M[element(0,2)],M[element(1,2)],M[element(2,2)]);

	while(TRUE) {
		SCALAR_TYPE	x,y,z;

		crossvv(ux,vy,vz);
		crossvv(uy,vz,vx);
		crossvv(uz,vx,vy);

		normalizev(ux);
		normalizev(uy);
		normalizev(uz);

		addvv(vx,ux);
		addvv(vy,uy);
		addvv(vz,uz);

		mulvf(vx,0.5f);
		mulvf(vy,0.5f);
		mulvf(vz,0.5f);

		x	=	dotvv(vx,vy);
		y	=	dotvv(vy,vz);
		z	=	dotvv(vz,vx);

		if ((x*x + y*y + z*z) < (SCALAR_TYPE) 0.000001)	break;
	}

	M[element(0,0)]	=	vx[0];
	M[element(1,0)]	=	vx[1];
	M[element(2,0)]	=	vx[2];

	M[element(0,1)]	=	vy[0];
	M[element(1,1)]	=	vy[1];
	M[element(2,1)]	=	vy[2];

	M[element(0,2)]	=	vz[0];
	M[element(1,2)]	=	vz[1];
	M[element(2,2)]	=	vz[2];
}





////////////////////////////////////////////////////////////////////////////
//
//
//
//	Misc quaternion operations
//
//
//
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
// Initialize a quaternion
inline	void	normalizeq(SCALAR_TYPE *q) {
	const double	l	=	1 / SQRT(q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3]);
	q[0]	=	(SCALAR_TYPE) (q[0]*l);
	q[1]	=	(SCALAR_TYPE) (q[1]*l);
	q[2]	=	(SCALAR_TYPE) (q[2]*l);
	q[3]	=	(SCALAR_TYPE) (q[3]*l);
}


////////////////////////////////////////////////////////////////////////////
// move a quaternion
inline	void	movqq(SCALAR_TYPE *dest,const SCALAR_TYPE *src) {
	dest[0]	=	src[0];
	dest[1]	=	src[1];
	dest[2]	=	src[2];
	dest[3]	=	src[3];
}

////////////////////////////////////////////////////////////////////////////
// Initialize a quaternion
inline	void	initq(SCALAR_TYPE *q,const SCALAR_TYPE x) {
	q[0]	=	x;
	q[1]	=	x;
	q[2]	=	x;
	q[3]	=	x;

	normalizeq(q);
}

////////////////////////////////////////////////////////////////////////////
// Initialize a quaternion
inline	void	initq(SCALAR_TYPE *q,const SCALAR_TYPE x,const SCALAR_TYPE y,const SCALAR_TYPE z,const SCALAR_TYPE s) {
	q[0]	=	x;
	q[1]	=	y;
	q[2]	=	z;
	q[3]	=	s;

	normalizeq(q);
}

////////////////////////////////////////////////////////////////////////////
// Multiply two quaternions
inline	void	mulqq(SCALAR_TYPE *res,const SCALAR_TYPE *q1,const SCALAR_TYPE *q2) {
	res[0] = q1[3] * q2[0] + q1[0] * q2[3] + q1[1] * q2[2] - q1[2] * q2[1];
	res[1] = q1[3] * q2[1] - q1[0] * q2[2] + q1[1] * q2[3] + q1[2] * q2[0];
	res[2] = q1[3] * q2[2] + q1[0] * q2[1] - q1[1] * q2[0] + q1[2] * q2[3];
	res[3] = q1[3] * q2[3] - q1[0] * q2[0] - q1[1] * q2[1] - q1[2] * q2[2];
}

////////////////////////////////////////////////////////////////////////////
// Compute the rotation matrix corresponding to a quaternion
inline	void	qtoR(SCALAR_TYPE *R,const SCALAR_TYPE *q) {
#define	a	q[0]
#define	b	q[1]
#define	c	q[2]
#define	s	q[3]


	R[element(0,0)] = (SCALAR_TYPE) (1-2*b*b-2*c*c);
	R[element(0,1)] = (SCALAR_TYPE) (2*a*b-2*s*c);
	R[element(0,2)] = (SCALAR_TYPE) (2*a*c+2*s*b);
	R[element(0,3)] = 0;
	R[element(1,0)] = (SCALAR_TYPE) (2*a*b+2*s*c);
	R[element(1,1)] = (SCALAR_TYPE) (1-2*a*a-2*c*c);
	R[element(1,2)] = (SCALAR_TYPE) (2*b*c-2*s*a);
	R[element(1,3)] = 0;
	R[element(2,0)] = (SCALAR_TYPE) (2*a*c-2*s*b);
	R[element(2,1)] = (SCALAR_TYPE) (2*b*c+2*s*a);
	R[element(2,2)] = (SCALAR_TYPE) (1-2*a*a-2*b*b);
	R[element(2,3)] = 0;
	R[element(3,0)] = 0;
	R[element(3,1)] = 0;
	R[element(3,2)] = 0;
	R[element(3,3)] = 1;

#undef a
#undef b
#undef c
#undef s
}


////////////////////////////////////////////////////////////////////////////
// Compute the quaternion corresponding to a rotation matrix
inline	void	qfromR(SCALAR_TYPE *q,const SCALAR_TYPE *R) {
	double	trace = R[element(0,0)] + R[element(1,1)] + R[element(2,2)] + 1.0;
	double	a,b,c,d;

	if( trace > C_EPSILON ) {
		d = sqrt(trace)*0.5;
		a = (R[element(2,1)] - R[element(1,2)]) / (4*d);
		b = (R[element(0,2)] - R[element(2,0)]) / (4*d);
		c = (R[element(1,0)] - R[element(0,1)]) / (4*d);
	} else {
		if ((R[element(0,0)] > R[element(1,1)]) && (R[element(0,0)] > R[element(2,2)])) {
			a = sqrt( 1.0 + R[element(0,0)] - R[element(1,1)] - R[element(2,2)])*0.5;
			b = (R[element(0,1)] + R[element(1,0)] ) / (4*a);
			c = (R[element(0,2)] + R[element(2,0)] ) / (4*a);
			d = (R[element(2,1)] - R[element(1,2)] ) / (4*a);
		} else if (R[element(1,1)] > R[element(2,2)]) {
			b = sqrt( 1.0 + R[element(1,1)] - R[element(0,0)] - R[element(2,2)])*0.5;
			a = (R[element(0,1)] + R[element(1,0)] ) / (4*b);
			c = (R[element(1,2)] + R[element(2,1)] ) / (4*b);
			d = (R[element(0,2)] - R[element(2,0)] ) / (4*b); 
		} else {
			c = sqrt(1.0 + R[element(2,2)] - R[element(0,0)] - R[element(1,1)])*0.5;
			a = (R[element(0,2)] + R[element(2,0)] ) / (4*c);
			b = (R[element(1,2)] + R[element(2,1)] ) / (4*c);			
			d = (R[element(1,0)] - R[element(0,1)] ) / (4*c);
		}
	}

	q[0]	=	(SCALAR_TYPE) a;
	q[1]	=	(SCALAR_TYPE) b;
	q[2]	=	(SCALAR_TYPE) c;
	q[3]	=	(SCALAR_TYPE) d;
}

