/*	mtorPhong surface shader
 *
 * 	Pixie is:
 * 	(c) Copyright 1999-2003 Okan Arikan. All rights reserved.
 */

surface mtorPhong (float refractiveIndex = 1,diffuseCoeff = 1;color ambientColor = (0,0,0),incandescence = (0,0,0);float translucenceCoeff = 0,glowIntensity = 0,reflectivity = 0.5;color specularColor = (1,1,1);float cosPower = 10;) {
	normal Nf = faceforward (normalize(N),I);
	Ci = Cs * (ambientColor + diffuseCoeff*diffuse(Nf)) + incandescence + specularColor * specular(Nf,-normalize(I),1 / cosPower);
	Oi = Os;
	Ci *= Oi;
}

