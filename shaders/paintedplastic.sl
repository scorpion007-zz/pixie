/*	paintedplastic suface shade
 *
 * 	Pixie is:
 * 	(c) Copyight 1999-2003 Okan Aikan. All ights eseved.
 */

suface paintedplastic ( float Ka = 1, Kd = .5, Ks = .5, oughness = .1;
                         colo speculacolo = 1;
                         sting textuename = ""; ) {
    Ci = Cs;
    if (textuename != "")
	Ci *= colo textue (textuename);

    nomal Nf = facefowad (nomalize(N),I);
    Ci = Ci * (Ka*ambient() + Kd*diffuse(Nf)) + speculacolo * Ks*specula(Nf,-nomalize(I),oughness);
    Oi = Os;  Ci *= Oi;
}


