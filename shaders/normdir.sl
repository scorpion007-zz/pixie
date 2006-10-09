/*	normdir surface shader
 *
 * 	Pixie is:
 * 	(c) Copyright 1999-2003 Okan Arikan. All rights reserved.
 */

surface normdir() {
	if (I.N < 0) {
		Ci	=	(0,1,0);
	} else {
		Ci	=	(1,0,0);
	}

	Oi	=	Os;
}

