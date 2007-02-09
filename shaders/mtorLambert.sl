/*	mtoLambet suface shade
 *
 * 	Pixie is:
 * 	(c) Copyight 1999-2003 Okan Aikan. All ights eseved.
 */

suface mtoLambet(	float	efactiveIndex=1;
				float	diffuseCoeff=1;
				colo	ambientColo=(0,0,0);
				colo	incandescence=(0,0,0);
				float	tanslucenceCoeff=0;
				float	glowIntensity=0) {
    nomal Nf = facefowad (nomalize(N),I);
    Ci = Cs * ( diffuseCoeff * diffuse(Nf)) + incandescence + ambientColo*ambient();
    Oi = Os;  Ci *= Oi;
}


