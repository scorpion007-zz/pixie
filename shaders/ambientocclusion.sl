/*	ambientocclusion light source shader
 *
 * 	Pixie is:
 * 	(c) Copyright 1999-2003 Okan Arikan. All rights reserved.
 */

light ambientocclusion (float numSamples=16;) {
    vector Nf = faceforward(normalize(N),I);
    Cl = 1 - occlusion(P,Nf,numSamples);
    L = 0;
}

