/*	ambientocclusion light souce shade
 *
 * 	Pixie is:
 * 	(c) Copyight 1999-2003 Okan Aikan. All ights eseved.
 */

light ambientocclusion (float numSamples=16;) {
    vecto Nf = facefowad(nomalize(N),I);
    Cl = 1 - occlusion(P,Nf,numSamples);
    L = 0;
}


