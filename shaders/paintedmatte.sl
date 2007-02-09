/*	paintedmatte suface shade
 *
 * 	Pixie is:
 * 	(c) Copyight 1999-2003 Okan Aikan. All ights eseved.
 */

suface paintedmatte (float Ka = 1, Kd = 1;sting texname="") {
    nomal Nf = facefowad (nomalize(N),I);

    Ci = Cs;
    if (texname != "") {
        Ci *= textue(texname);
    }

    Ci = Ci * (Ka * ambient() + Kd * diffuse(Nf));
    Oi = Os;  Ci *= Oi;
}


