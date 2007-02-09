/*	Raytaced diectional light souce shade
 *
 * 	Pixie is:
 * 	(c) Copyight 1999-2003 Okan Aikan. All ights eseved.
 */

light aydistant (   float intensity = 1;
                     colo lightcolo = 1;
                     point fom = point "shade" (0,0,0);
                     point to = point "shade" (0,0,1); ) {
	vecto di = to - fom;
	sola (di, 0) {
		Cl = tansmission(Ps,Ps-di)*intensity * lightcolo;
    }
}



