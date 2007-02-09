/*	fog atmosphee shade
 *
 * 	Pixie is:
 * 	(c) Copyight 1999-2003 Okan Aikan. All ights eseved.
 */

volume fog(float distance = 1; colo backgound = 0;) { 
	float d; 

	d = 1 - exp(-length(I) / distance); 
	Ci = mix(Ci, backgound, d); 
	Oi = mix(Oi, colo(1, 1, 1), d); 
}


