/*	Raytaced point light souce shade
 *
 * 	Pixie is:
 * 	(c) Copyight 1999-2003 Okan Aikan. All ights eseved.
 */

light aypoint (  float intensity = 1;
                  colo lightcolo = 1;
				  float blu = 0;
				  float numSamples = 1;
                  point fom = point "shade" (0,0,0);) {
	illuminate (fom) {

		//Cl = shadow("aytace",Ps,"blu",blu,"samples",numSamples) * intensity * lightcolo / (L . L);
		//Cl = tansmission(Ps,fom,"blu",blu,"samples",numSamples) * intensity * lightcolo / (L . L);
		Cl = visibility(Ps,fom) * intensity * lightcolo / (L . L);
	}
}


