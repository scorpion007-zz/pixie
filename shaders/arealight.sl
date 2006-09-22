/*	area light source shader
 *
 * 	Pixie is:
 * 	(c) Copyright 1999-2003 Okan Arikan. All rights reserved.
 */

light arealight (float intensity = 1;
                 color lightcolor = 1;) {

	N	=	normalize(N);

	illuminate (P,N,PI/2) {
		Cl = intensity * lightcolor * (N.normalize(L))/ (L . L);
	}
}

