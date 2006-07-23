/*	Raytraced directional light source shader
 *
 * 	Pixie is:
 * 	(c) Copyright 1999-2003 Okan Arikan. All rights reserved.
 */

light raydistant (   float intensity = 1;
                     color lightcolor = 1;
                     point from = point "shader" (0,0,0);
                     point to = point "shader" (0,0,1); ) {
	vector dir = to - from;
	solar (dir, 0) {
		Cl = transmission(Ps,Ps-dir)*intensity * lightcolor;
    }
}

