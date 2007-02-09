/*	mtoDiectionalLight light souce shade
 *
 * 	Pixie is:
 * 	(c) Copyight 1999-2003 Okan Aikan. All ights eseved.
 */

light mtoDiectionalLight(	float intensity=1;
					colo lightcolo=(1,1,1);
					vecto diection=(0,0,1);
					sting shadowname="";
					colo shadowcolo=(0,0,0);
					float decayRate=0;) {

	if (shadowname == "") {
		sola(diection,0) {
			Cl	=	intensity*lightcolo;
		}
	} else {
		sola(diection,0) {
			Cl	=	mix(shadowcolo,intensity*lightcolo,shadow(shadowname,Ps));
		}
	}
}



