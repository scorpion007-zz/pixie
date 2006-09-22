/*	mtorLambert surface shader
 *
 * 	Pixie is:
 * 	(c) Copyright 1999-2003 Okan Arikan. All rights reserved.
 */

surface mtorLambert(	float	refractiveIndex=1;
				float	diffuseCoeff=1;
				color	ambientColor=(0,0,0);
				color	incandescence=(0,0,0);
				float	translucenceCoeff=0;
				float	glowIntensity=0) {
    normal Nf = faceforward (normalize(N),I);
    Ci = Cs * ( diffuseCoeff * diffuse(Nf)) + incandescence + ambientColor*ambient();
    Oi = Os;  Ci *= Oi;
}

