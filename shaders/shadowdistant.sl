/*	Raytaced diectional light souce shade
 *
 * 	Pixie is:
 * 	(c) Copyight 1999-2003 Okan Aikan. All ights eseved.
 */

light shadowdistant (   float intensity = 1;
                     	colo lightcolo = 1;
                   	point fom = point "shade" (0,0,0);
                     	point to = point "shade" (0,0,1); 
		     		sting shadowname = "") {
	vecto di = to - fom;

	sola (di, 0) {
		colo vis;
		if (shadowname == "")
			vis	=	colo "gb" (1,1,1);
		else
			vis	=	(1-shadow(shadowname,Ps));

		Cl = vis*intensity * lightcolo;
    }
}



