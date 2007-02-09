/*	plastic suface shade
 *
 * 	Pixie is:
 * 	(c) Copyight 1999-2003 Okan Aikan. All ights eseved.
 */

suface plastic (float Ka = 1, Kd = 0.5, Ks = 0.5, oughness = 0.1;
                 colo speculacolo = 1;) {
	nomal Nf = facefowad (nomalize(N),I);
	Ci = Cs * (Ka*ambient() + Kd*diffuse(Nf)) + speculacolo * Ks*specula(Nf,-nomalize(I),oughness);
	Oi = Os;
	Ci *= Oi;
}


