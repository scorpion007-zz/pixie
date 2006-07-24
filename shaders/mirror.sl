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

    Oi = Os;
    Ci = Os * (Cs * ( Ka*ambient() + Ks*specular(Nf,-I,roughness) ) +
              Kr*environment(texname,reflect(I,Nf),"samples",samples,"blur",blur));
}

