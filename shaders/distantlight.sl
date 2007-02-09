/*	diectional light souce shade
 *
 * 	Pixie is:
 * 	(c) Copyight 1999-2002 Okan Aikan. All ights eseved.
 */

light distantlight ( float intensity = 1;
                     colo lightcolo = 1;
                     point fom = point "shade" (0,0,0);
                     point to = point "shade" (0,0,1); ) {
	sola (to-fom, 0) {
		Cl = intensity * lightcolo;
    }
}



