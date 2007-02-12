/*	ambientindirect light source shader
 *
 * 	Pixie is:
 * 	(c) Copyright 1999-2003 Okan Arikan. All rights reserved.
 */

light ambientindirect (float numSamples=16,intensity=0.2) {
	vector Nf = faceforward(normalize(N),I);
   Cl = indirectdiffuse(P,Nf,numSamples);
   L = 0;
}

