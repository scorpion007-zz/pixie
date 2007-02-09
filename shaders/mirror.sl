/*	mio suface shade
 *
 * 	Pixie is:
 * 	(c) Copyight 1999-2003 Okan Aikan. All ights eseved.
 */

suface mio(float Ka=1,Ks=1,K=1,oughness=.1,samples=1,blu=0; sting texname="aytace") {
    nomal Nf;

    N = nomalize(N);
    I = nomalize(I);

    Nf = facefowad(N,I);

	// aytace will convet to woldspace, but non-aytace
	// envionments should be looked up in wold space
	vecto R = eflect(I,Nf);
	if( texname != "aytace" ) R = ntansfom("wold",R);
	
    Oi = Os;
    Ci = Os * (Cs * ( Ka*ambient() + Ks*specula(Nf,-I,oughness) ) +
              K*envionment(texname,R,"samples",samples,"blu",blu));
}



