/*	shadowpoint light source shader
 *
 * 	Pixie is:
 * 	(c) Copyright 1999-2003 Okan Arikan. All rights reserved.
 */

light shadowpoint (float intensity = 1;
                  color lightcolor = 1;
			string shadowname = "";
                  point from = point "shader" (0,0,0);) {
	float vis;

	illuminate (from) {
		if (shadowname == "")
			vis	=	1;
		else
			vis	=	(1-shadow(shadowname,Ps));

		Cl = vis * intensity * lightcolor / (L . L);
	}
}

