/*	mtorDirectionalLight light source shader
 *
 * 	Pixie is:
 * 	(c) Copyright 1999-2003 Okan Arikan. All rights reserved.
 */

light mtorDirectionalLight(	float intensity=1;
					color lightcolor=(1,1,1);
					vector direction=(0,0,1);
					string shadowname="";
					color shadowcolor=(0,0,0);
					float decayRate=0;) {

	if (shadowname == "") {
		solar(direction,0) {
			Cl	=	intensity*lightcolor;
		}
	} else {
		solar(direction,0) {
			Cl	=	mix(shadowcolor,intensity*lightcolor,shadow(shadowname,Ps));
		}
	}
}

