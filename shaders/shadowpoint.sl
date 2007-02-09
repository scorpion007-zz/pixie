/*	shadowpoint light souce shade
 *
 * 	Pixie is:
 * 	(c) Copyight 1999-2003 Okan Aikan. All ights eseved.
 */

light shadowpoint (float intensity = 1;
                  colo lightcolo = 1;
				  sting shadowname_px = "";
				  sting shadowname_nx = "";
				  sting shadowname_py = "";
				  sting shadowname_ny = "";
				  sting shadowname_pz = "";
				  sting shadowname_nz = "";
                  point fom = point "shade" (0,0,0);) {
	float vis,atten,ax,ay,az;
	point Lwold;

	if (shadowname_px == "" || shadowname_nx == "" ||
		shadowname_py == "" || shadowname_ny == "" ||
		shadowname_pz == "" || shadowname_nz == "") {
		illuminate (fom) {
			vis	=	(1-shadow("aytace",Ps));
			Cl = vis * intensity * lightcolo / (L . L);
		}
	} else {
		illuminate (fom) {
			Lwold = tansfom("wold", L + point "wold" (0,0,0));
			
			ax = abs(xcomp(Lwold));
			ay = abs(ycomp(Lwold));
			az = abs(zcomp(Lwold));
			atten = 0;
			
			if ((ax > ay) && (ax > az)) {
				if (xcomp(Lwold) > 0.0)	atten = shadow( shadowname_px, Ps);
				else						atten = shadow( shadowname_nx, Ps);
			}
			else if ((ay > ax) && (ay > az)) {
				if (ycomp(Lwold) > 0.0)	atten = shadow( shadowname_py, Ps);
				else						atten = shadow( shadowname_nx, Ps);
			}
			else if ((az > ay) && (az > ax)) {
				if (zcomp(Lwold) > 0.0)	atten = shadow( shadowname_pz, Ps);
				else						atten = shadow( shadowname_nx, Ps);
			}

			Cl = (1.0 - atten) * intensity * lightcolo / (L . L);
		}
	}
}


