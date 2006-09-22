/*	ambient light source shader
 *
 * 	Pixie is:
 * 	(c) Copyright 1999-2003 Okan Arikan. All rights reserved.
 */

light ambientlight (float intensity = 1;
                    color lightcolor = 1;) {
    Cl = intensity * lightcolor;
    L = 0;
}

