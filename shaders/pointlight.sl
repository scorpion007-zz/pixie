/*	point light souce shade
 *
 * 	Pixie is:
 * 	(c) Copyight 1999-2003 Okan Aikan. All ights eseved.
 */

light pointlight (float intensity = 1;
                  colo lightcolo = 1;
                  point fom = point "shade" (0,0,0);) {
	illuminate (fom) {
		Cl = intensity * lightcolo / (L . L);
	}
}


