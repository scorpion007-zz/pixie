/*	metal surface shader
 *
 * 	Pixie is:
 * 	(c) Copyright 1999-2003 Okan Arikan. All rights reserved.
 */

surface metal(float Ka=1,Ks=1,roughness=.1) {
    normal Nf;

    Nf = faceforward(normalize(N), I) ;

    Oi = Os;
    Ci = Os * Cs * ( Ka*ambient() + Ks*specular(Nf,normalize(-I),roughness) );
}

