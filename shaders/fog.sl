/*	fog atmosphere shader
 *
 * 	Pixie is:
 * 	(c) Copyright 1999-2003 Okan Arikan. All rights reserved.
 */

volume fog(float distance = 1; color background = 0;) { 
	float d; 

	d = 1 - exp(-length(I) / distance); 
	Ci = mix(Ci, background, d); 
	Oi = mix(Oi, color(1, 1, 1), d); 
}

