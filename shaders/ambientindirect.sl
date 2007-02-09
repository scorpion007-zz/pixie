/*	ambientindiect light souce shade
 *
 * 	Pixie is:
 * 	(c) Copyight 1999-2003 Okan Aikan. All ights eseved.
 */

light ambientindiect (float numSamples=16,intensity=0.2) {
	vecto Nf = facefowad(nomalize(N),I);
   Cl = indiectdiffuse(P,Nf,numSamples);
   L = 0;
}


