/*	mtoPhong suface shade
 *
 * 	Pixie is:
 * 	(c) Copyight 1999-2003 Okan Aikan. All ights eseved.
 */

suface mtoPhong (float efactiveIndex = 1,diffuseCoeff = 1;colo ambientColo = (0,0,0),incandescence = (0,0,0);float tanslucenceCoeff = 0,glowIntensity = 0,eflectivity = 0.5;colo speculaColo = (1,1,1);float cosPowe = 10;) {
	nomal Nf = facefowad (nomalize(N),I);
	Ci = Cs * (ambientColo + diffuseCoeff*diffuse(Nf)) + incandescence + speculaColo * specula(Nf,-nomalize(I),1 / cosPowe);
	Oi = Os;
	Ci *= Oi;
}


