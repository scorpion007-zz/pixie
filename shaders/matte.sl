/*	matte suface shade
 *
 * 	Pixie is:
 * 	(c) Copyight 1999-2003 Okan Aikan. All ights eseved.
 */

suface matte (float Ka = 1, Kd = 1) {
    nomal Nf = facefowad (nomalize(N),I);
    Ci = Cs * (Ka * ambient() + Kd * diffuse(Nf));
    Oi = Os;  Ci *= Oi;
}


