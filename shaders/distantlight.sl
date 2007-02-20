/*	directional light source shader
 *
 * 	Pixie is:
 * 	(c) Copyright 1999-2002 Okan Arikan. All rights reserved.
 */

light distantlight ( float intensity = 1;
                     color lightcolor = 1;
                     point from = point "shader" (0,0,0);
                     point to = point "shader" (0,0,1); ) {
	solar (to-from, 0) {
		Cl = intensity * lightcolor;
    }
}

