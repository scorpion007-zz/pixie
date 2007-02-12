/*	matte surface shader
 *
 * 	Pixie is:
 * 	(c) Copyright 1999-2003 Okan Arikan. All rights reserved.
 */

surface matte (float Ka = 1, Kd = 1) {
    normal Nf = faceforward (normalize(N),I);
    Ci = Cs * (Ka * ambient() + Kd * diffuse(Nf));
    Oi = Os;  Ci *= Oi;
}

