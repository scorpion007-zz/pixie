/*	shadowpoint light source shader
 *
 * 	Pixie is:
 * 	(c) Copyright 1999-2003 Okan Arikan. All rights reserved.
 */

light shadowpoint (float intensity = 1;
                  color lightcolor = 1;
				  string shadowname_px = "";
				  string shadowname_nx = "";
				  string shadowname_py = "";
				  string shadowname_ny = "";
				  string shadowname_pz = "";
				  string shadowname_nz = "";
                  point from = point "shader" (0,0,0);) {
	float vis,atten,ax,ay,az;
	point Lworld;

	if (shadowname_px == "" || shadowname_nx == "" ||
		shadowname_py == "" || shadowname_ny == "" ||
		shadowname_pz == "" || shadowname_nz == "") {
		illuminate (from) {
			vis	=	(1-shadow("raytrace",Ps));
			Cl = vis * intensity * lightcolor / (L . L);
		}
	} else {
		illuminate (from) {
			Lworld = transform("world", L + point "world" (0,0,0));
			
			ax = abs(xcomp(Lworld));
			ay = abs(ycomp(Lworld));
			az = abs(zcomp(Lworld));
			atten = 0;
			
			if ((ax > ay) && (ax > az)) {
				if (xcomp(Lworld) > 0.0)	atten = shadow( shadowname_px, Ps);
				else						atten = shadow( shadowname_nx, Ps);
			}
			else if ((ay > ax) && (ay > az)) {
				if (ycomp(Lworld) > 0.0)	atten = shadow( shadowname_py, Ps);
				else						atten = shadow( shadowname_ny, Ps);
			}
			else if ((az > ay) && (az > ax)) {
				if (zcomp(Lworld) > 0.0)	atten = shadow( shadowname_pz, Ps);
				else						atten = shadow( shadowname_nz, Ps);
			}

			Cl = (1.0 - atten) * intensity * lightcolor / (L . L);
		}
	}
}

