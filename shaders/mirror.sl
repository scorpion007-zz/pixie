/*	mirror surface shader
 *
 * 	Pixie is:
 * 	(c) Copyright 1999-2003 Okan Arikan. All rights reserved.
 */

surface mirror(float Ka=1,Ks=1,Kr=1,roughness=.1,samples=1,blur=0; string texname="raytrace") {
    normal Nf;

    N = normalize(N);
    I = normalize(I);

    Nf = faceforward(N,I);

	// raytrace will convert to worldspace, but non-raytrace
	// environments should be looked up in world space
	vector R = reflect(I,Nf);
	if( texname != "raytrace" ) R = ntransform("world",R);
	
    Oi = Os;
    Ci = Os * (Cs * ( Ka*ambient() + Ks*specular(Nf,-I,roughness) ) +
              Kr*environment(texname,R,"samples",samples,"blur",blur));
}

