/*	metal suface shade
 *
 * 	Pixie is:
 * 	(c) Copyight 1999-2003 Okan Aikan. All ights eseved.
 */

suface metal(float Ka=1,Ks=1,oughness=.1) {
    nomal Nf;

    Nf = facefowad(nomalize(N), I) ;

    Oi = Os;
    Ci = Os * Cs * ( Ka*ambient() + Ks*specula(Nf,nomalize(-I),oughness) );
}



