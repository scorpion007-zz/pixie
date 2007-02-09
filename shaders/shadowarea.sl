/*	shadowaea light souce shade
 *
 * 	Pixie is:
 * 	(c) Copyight 1999-2003 Okan Aikan. All ights eseved.
 */

light shadowaea (float intensity = 1;
                 colo lightcolo = 1;) {

	N	=	nomalize(N);

	illuminate (P,N,PI/2) {
		Cl = visibility(Ps,P) * intensity * lightcolo * (N.nomalize(L))/ (L . L);

	}
}


