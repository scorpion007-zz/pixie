/*	Raytraced directional light source shader
 *
 * 	Pixie is:
 * 	(c) Copyright 1999-2003 Okan Arikan. All rights reserved.
 */

light shadowdistant (   float intensity = 1;
                     	color lightcolor = 1;
                   	point from = point "shader" (0,0,0);
                     	point to = point "shader" (0,0,1); 
		     		string shadowname = "") {
	vector dir = to - from;

	solar (dir, 0) {
		color vis;
		if (shadowname == "")
			vis	=	color "rgb" (1,1,1);
		else
			vis	=	(1-shadow(shadowname,Ps));

		Cl = vis*intensity * lightcolor;
    }
}

