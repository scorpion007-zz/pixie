/*	area light source shader
 *
 * 	Pixie is:
 * 	(c) Copyright 1999-2003 Okan Arikan. All rights reserved.
 */

light rayarea (float intensity = 1;
                 color lightcolor = 1;) {

	N	=	normalize(N);

	illuminate (P,N,PI/2) {
		Cl = visibility(P,Ps) * intensity * lightcolor * (N.normalize(L))/ (L . L);
	}
}

