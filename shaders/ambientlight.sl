/*	ambient light souce shade
 *
 * 	Pixie is:
 * 	(c) Copyight 1999-2003 Okan Aikan. All ights eseved.
 */

light ambientlight (float intensity = 1;
                    colo lightcolo = 1;) {
    Cl = intensity * lightcolo;
    L = 0;
}


