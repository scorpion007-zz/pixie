//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright © 1999 - 2003, Okan Arikan
//
// Contact: okan@cs.berkeley.edu
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
// 
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
// 
// You should have received a copy of the GNU General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//
//  File				:	precomp.cpp
//  Classes				:	-
//  Description			:	This program is used to create misc data
//							in header files for the ri.
//
////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "common/global.h"
#include "common/algebra.h"
#include "ri/reyes.h"

typedef struct {
  double * val;
  double * vecI;
  double ** Phi;
  double ** Phi2;
} TEvalStruct;

#define IX(i,j,n) ((i)+(n)*(j))

#define NOISESIZE 0x100
#define NOISEMASK 0xff
#define NOISEMIN 0x100


#define	MIN_TEMPERATURE		1000
#define	MAX_TEMPERATURE		3500
#define	NUM_TEMPERATURES	10000

// CIE color matching functions
static	double fColorMatch[][3]={
         {0.0014, 0.0000, 0.0065},
         {0.0022, 0.0001, 0.0105},
         {0.0042, 0.0001, 0.0201},
         {0.0076, 0.0002, 0.0362},
         {0.0143, 0.0004, 0.0679},
         {0.0232, 0.0006, 0.1102},
         {0.0435, 0.0012, 0.2074},
         {0.0776, 0.0022, 0.3713},
         {0.1344, 0.0040, 0.6456},
         {0.2148, 0.0073, 1.0391},
         {0.2839, 0.0116, 1.3856},
         {0.3285, 0.0168, 1.6230},
         {0.3483, 0.0230, 1.7471},
         {0.3481, 0.0298, 1.7826},
         {0.3362, 0.0380, 1.7721},
         {0.3187, 0.0480, 1.7441},
         {0.2908, 0.0600, 1.6692},
         {0.2511, 0.0739, 1.5281},
         {0.1954, 0.0910, 1.2876},
         {0.1421, 0.1126, 1.0419},
         {0.0956, 0.1390, 0.8130},
         {0.0580, 0.1693, 0.6162},
         {0.0320, 0.2080, 0.4652},
         {0.0147, 0.2586, 0.3533},
         {0.0049, 0.3230, 0.2720},
         {0.0024, 0.4073, 0.2123},
         {0.0093, 0.5030, 0.1582},
         {0.0291, 0.6082, 0.1117},
         {0.0633, 0.7100, 0.0782},
         {0.1096, 0.7932, 0.0573},
         {0.1655, 0.8620, 0.0422},
         {0.2257, 0.9149, 0.0298},
         {0.2904, 0.9540, 0.0203},
         {0.3597, 0.9803, 0.0134},
         {0.4334, 0.9950, 0.0087},
         {0.5121, 1.0000, 0.0057},
         {0.5945, 0.9950, 0.0039},
         {0.6784, 0.9786, 0.0027},
         {0.7621, 0.9520, 0.0021},
         {0.8425, 0.9154, 0.0018},
         {0.9163, 0.8700, 0.0017},
         {0.9786, 0.8163, 0.0014},
         {1.0263, 0.7570, 0.0011},
         {1.0567, 0.6949, 0.0010},
         {1.0622, 0.6310, 0.0008},
         {1.0456, 0.5668, 0.0006},
         {1.0026, 0.5030, 0.0003},
         {0.9384, 0.4412, 0.0002},
         {0.8544, 0.3810, 0.0002},
         {0.7514, 0.3210, 0.0001},
         {0.6424, 0.2650, 0.0000},
         {0.5419, 0.2170, 0.0000},
         {0.4479, 0.1750, 0.0000},
         {0.3608, 0.1382, 0.0000},
         {0.2835, 0.1070, 0.0000},
         {0.2187, 0.0816, 0.0000},
         {0.1649, 0.0610, 0.0000},
         {0.1212, 0.0446, 0.0000},
         {0.0874, 0.0320, 0.0000},
         {0.0636, 0.0232, 0.0000},
         {0.0468, 0.0170, 0.0000},
         {0.0329, 0.0119, 0.0000},
         {0.0227, 0.0082, 0.0000},
         {0.0158, 0.0057, 0.0000},
         {0.0114, 0.0041, 0.0000},
         {0.0081, 0.0029, 0.0000},
         {0.0058, 0.0021, 0.0000},
         {0.0041, 0.0015, 0.0000},
         {0.0029, 0.0010, 0.0000},
         {0.0020, 0.0007, 0.0000},
         {0.0014, 0.0005, 0.0000},
         {0.0010, 0.0004, 0.0000},
         {0.0007, 0.0002, 0.0000},
         {0.0005, 0.0002, 0.0000},
         {0.0003, 0.0001, 0.0000},
         {0.0002, 0.0001, 0.0000},
         {0.0002, 0.0001, 0.0000},
         {0.0001, 0.0000, 0.0000},
         {0.0001, 0.0000, 0.0000},
         {0.0001, 0.0000, 0.0000},
         {0.0000, 0.0000, 0.0000}};


///////////////////////////////////////////////////////////////////////
// Function				:	blackBody
// Description			:	Evaluate black bolor for a temperature
// Return Value			:	The XYZ color in xyz
// Comments				:
// Date last edited		:	10/15/2002
static	inline	void	blackBody(float *xyz,double temperature) {
    double	XX=0.0,YY=0.0,ZZ=0.0;
    double	dis,wavelength,weight;
    short	band, nbands=81;
	double	m;

	const	double	width	=	5.0 * 1e-9;
    for(wavelength=380.0,band=0;band<nbands;band++,wavelength+=5.0) {
		double	lam	=	wavelength*1e-9;
        weight=1.0;
        if((band==0)||(band==nbands-1)) weight=0.5;

		dis	=	3.74183e-16*(1.0/pow(lam,5))/(exp(1.4388e-2/(lam*temperature))-1.);

        XX	=	XX+weight*dis*fColorMatch[band][0]*width;
        YY	=	YY+weight*dis*fColorMatch[band][1]*width;
        ZZ	=	ZZ+weight*dis*fColorMatch[band][2]*width;
    }

	m		=	max(XX,YY);
	m		=	max(m,ZZ);

	if (TRUE) {
		xyz[0]	=	(float) XX;
		xyz[1]	=	(float) YY;
		xyz[2]	=	(float) ZZ;
	} else {
		if (m < 1) {
			xyz[0]	=	(float) (XX);
			xyz[1]	=	(float) (YY);
			xyz[2]	=	(float) (ZZ);
		} else {
			xyz[0]	=	(float) (XX/m);
			xyz[1]	=	(float) (YY/m);
			xyz[2]	=	(float) (ZZ/m);
		}
	}
}


///////////////////////////////////////////////////////////////////////
// Function				:	xyzTorgb
// Description			:	Convert a color from XYZ to RGB
// Return Value			:	The rgb in rgb
// Comments				:	-
// Date last edited		:	10/7/2002
static	inline	void	xyzTorgb(float *rgb,const float *xyz) {
	if (FALSE) {
		rgb[COMP_R]		=	(float)	(3.24079*xyz[0]		-	1.537150*xyz[1]	-	0.498535*xyz[2]);
		rgb[COMP_G]		=	(float) (-0.969256*xyz[0]	+	1.875992*xyz[1]	+	0.041556*xyz[2]);
		rgb[COMP_B]		=	(float)	(0.055648*xyz[0]	-	0.204043*xyz[1]	+	1.057311*xyz[2]);
	} else {
		rgb[COMP_R]		=	(float)	(2.739*xyz[0]		-	1.145*xyz[1]	-	0.424*xyz[2]);
		rgb[COMP_G]		=	(float) (-1.119*xyz[0]		+	2.029*xyz[1]	+	0.033*xyz[2]);
		rgb[COMP_B]		=	(float)	(0.138*xyz[0]		-	0.333*xyz[1]	+	1.105*xyz[2]);
	}
}



///////////////////////////////////////////////////////////////////////
// Function				:	noiseNormalize2
// Description			:
// Return Value			:
// Comments				:
// Date last edited		:	3/13/2001
static void	noiseNormalize2(float v[2]) {
	float s;

	s = sqrtf(v[0] * v[0] + v[1] * v[1]);
	v[0] = v[0] / s;
	v[1] = v[1] / s;
}

///////////////////////////////////////////////////////////////////////
// Function				:	noiseNormalize3
// Description			:
// Return Value			:
// Comments				:
// Date last edited		:	3/13/2001
static	void noiseNormalize3(float v[3]) {
	float s;

	s = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	v[0] = v[0] / s;
	v[1] = v[1] / s;
	v[2] = v[2] / s;
}

///////////////////////////////////////////////////////////////////////
// Function				:	noiseNormalize4
// Description			:
// Return Value			:
// Comments				:
// Date last edited		:	3/13/2001
static void noiseNormalize4(float v[4]) {
	float s;

	s = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + v[3] * v[3]);
	v[0] = v[0] / s;
	v[1] = v[1] / s;
	v[2] = v[2] / s;
	v[3] = v[3] / s;
}


///////////////////////////////////////////////////////////////////////
// Function				:	precomputeNoiseData
// Description			:	create noiseTables.h header file for the ri
// Return Value			:	TRUE on success, FALSE otherwise
// Comments				:
// Date last edited		:	10/27/2002
int	precomputeNoiseData() {
	int		p[NOISESIZE + NOISESIZE + 2];
	int		p2[NOISESIZE + NOISESIZE + 2];
	int		p3[NOISESIZE + NOISESIZE + 2];
	float	g4[NOISESIZE + NOISESIZE + 2][4];
	float	g3[NOISESIZE + NOISESIZE + 2][3];
	float	g2[NOISESIZE + NOISESIZE + 2][2];
	float	g1[NOISESIZE + NOISESIZE + 2];
	int		i,j,k;

	#ifdef _WIN32
		FILE	*noiseTables	=	fopen("..\\src\\ri\\noiseTables.h","w");
	#else
		FILE	*noiseTables	=	fopen("../ri/noiseTables.h","w");
	#endif	

	if (noiseTables == NULL)	return FALSE;

	for (i = 0 ; i < NOISESIZE ; i++) {
		p[i] = i;
		p2[i] = i;
		p3[i] = i;

		g1[i] = (float)((rand() % (NOISESIZE + NOISESIZE)) - NOISESIZE) / NOISESIZE;

		for (j = 0 ; j < 2 ; j++)
			g2[i][j] = (float)((rand() % (NOISESIZE + NOISESIZE)) - NOISESIZE) / NOISESIZE;
		noiseNormalize2(g2[i]);

		for (j = 0 ; j < 3 ; j++)
			g3[i][j] = (float)((rand() % (NOISESIZE + NOISESIZE)) - NOISESIZE) / NOISESIZE;
		noiseNormalize3(g3[i]);

		for (j = 0 ; j < 4 ; j++)
			g4[i][j] = (float)((rand() % (NOISESIZE + NOISESIZE)) - NOISESIZE) / NOISESIZE;
		noiseNormalize3(g4[i]);
	}

	while (--i) {
		k = p[i];
		p[i] = p[j = rand() % NOISESIZE];
		p[j] = k;
	}

	i = NOISESIZE;
	while (--i) {
		k = p2[i];
		p2[i] = p2[j = rand() % NOISESIZE];
		p2[j] = k;
	}

	i = NOISESIZE;
	while (--i) {
		k = p3[i];
		p3[i] = p3[j = rand() % NOISESIZE];
		p3[j] = k;
	}

	for (i = 0 ; i < NOISESIZE + 2 ; i++) {
		p[NOISESIZE + i] = p[i];
		p2[NOISESIZE + i] = p2[i];
		p3[NOISESIZE + i] = p3[i];
		g1[NOISESIZE + i] = g1[i];
		for (j = 0 ; j < 2 ; j++)
			g2[NOISESIZE + i][j] = g2[i][j];
		for (j = 0 ; j < 3 ; j++)
			g3[NOISESIZE + i][j] = g3[i][j];
		for (j = 0 ; j < 4 ; j++)
			g4[NOISESIZE + i][j] = g4[i][j];
	}

	fprintf(noiseTables,"// Internally generated noise data...\n// Do not mess with it\n\n");
	fprintf(noiseTables,"#define NOISESIZE %d\n",NOISESIZE);
	fprintf(noiseTables,"#define NOISEMASK %d\n",NOISEMASK);
	fprintf(noiseTables,"#define NOISEMIN %d\n",NOISEMIN);
	fprintf(noiseTables,"\n\n");

	fprintf(noiseTables,"static	int		p[NOISESIZE + NOISESIZE + 2] = {\n");
	for (i=0;i<NOISESIZE + NOISESIZE + 2;i++) {
		if (i == 0)
			fprintf(noiseTables,"\t %d \n",p[i]);
		else
			fprintf(noiseTables,"\t , %d \n",p[i]);
	}
	fprintf(noiseTables,"};\n\n\n");

	fprintf(noiseTables,"static	int		p2[NOISESIZE + NOISESIZE + 2] = {\n");
	for (i=0;i<NOISESIZE + NOISESIZE + 2;i++) {
		if (i == 0)
			fprintf(noiseTables,"\t %d \n",p2[i]);
		else
			fprintf(noiseTables,"\t , %d \n",p2[i]);
	}
	fprintf(noiseTables,"};\n\n\n");

	fprintf(noiseTables,"static	int		p3[NOISESIZE + NOISESIZE + 2] = {\n");
	for (i=0;i<NOISESIZE + NOISESIZE + 2;i++) {
		if (i == 0)
			fprintf(noiseTables,"\t %d \n",p3[i]);
		else
			fprintf(noiseTables,"\t , %d \n",p3[i]);
	}
	fprintf(noiseTables,"};\n\n\n");

	fprintf(noiseTables,"static	float	g4[NOISESIZE + NOISESIZE + 2][4] = {\n");
	for (i=0;i<NOISESIZE + NOISESIZE + 2;i++) {
		if (i == 0)
			fprintf(noiseTables,"\t {(float) %f,(float) %f,(float) %f,(float) %f} \n",g4[i][0],g4[i][1],g4[i][2],g4[i][3]);
		else
			fprintf(noiseTables,"\t ,{(float) %f,(float) %f,(float) %f,(float) %f} \n",g4[i][0],g4[i][1],g4[i][2],g4[i][3]);
	}
	fprintf(noiseTables,"};\n\n\n");

	fprintf(noiseTables,"static	float	g3[NOISESIZE + NOISESIZE + 2][3] = {\n");
	for (i=0;i<NOISESIZE + NOISESIZE + 2;i++) {
		if (i == 0)
			fprintf(noiseTables,"\t {(float) %f,(float) %f,(float) %f} \n",g3[i][0],g3[i][1],g3[i][2]);
		else
			fprintf(noiseTables,"\t ,{(float) %f,(float) %f,(float) %f} \n",g3[i][0],g3[i][1],g3[i][2]);
	}
	fprintf(noiseTables,"};\n\n\n");

	fprintf(noiseTables,"static	float	g2[NOISESIZE + NOISESIZE + 2][2] = {\n");
	for (i=0;i<NOISESIZE + NOISESIZE + 2;i++) {
		if (i == 0)
			fprintf(noiseTables,"\t {(float) %f,(float) %f} \n",g2[i][0],g2[i][1]);
		else
			fprintf(noiseTables,"\t ,{(float) %f,(float) %f} \n",g2[i][0],g2[i][1]);
	}
	fprintf(noiseTables,"};\n\n\n");

	fprintf(noiseTables,"static	float	g1[NOISESIZE + NOISESIZE + 2] = {\n");
	for (i=0;i<NOISESIZE + NOISESIZE + 2;i++) {
		if (i == 0)
			fprintf(noiseTables,"\t (float) %f \n",g1[i]);
		else
			fprintf(noiseTables,"\t ,(float) %f \n",g1[i]);
	}
	fprintf(noiseTables,"};\n\n\n");

	fclose(noiseTables);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// Function				:	precomputeSubdivisionData
// Description			:	create subdivisionData.h header file for the ri
// Return Value			:	TRUE on success, FALSE otherwise
// Comments				:
// Date last edited		:	10/27/2002
int	precomputeSubdivisionData() {
	FILE			*out;
	TEvalStruct		**ev;
	FILE			*f;
	int				Nmax,i,N,K;
	double			basis[16];
	int				j,k;

#ifdef _WIN32
	if (!(f=fopen("ccdata50NT.dat","rb"))) {
		fprintf(stderr,"Unable to open ccdata50NT.dat\n");
		return TRUE;
	}
	out				=	fopen("..\\src\\ri\\subdivisionData.h","w");
#else
	if (!(f=fopen("ccdata50.dat","r"))) {
		fprintf(stderr,"Unable to open ccdata50.dat\n");
		return TRUE;
	}
	out				=	fopen("../ri/subdivisionData.h","w");
#endif
	if(out == NULL) return FALSE;

	basis[0]		=	-1	/6.0;
	basis[1]		=	3	/6.0;
	basis[2]		=	-3	/6.0;
	basis[3]		=	1	/6.0;

	basis[4]		=	3	/6.0;
	basis[5]		=	-6	/6.0;
	basis[6]		=	0	/6.0;
	basis[7]		=	4	/6.0;

	basis[8]		=	-3	/6.0;
	basis[9]		=	3	/6.0;
	basis[10]		=	3	/6.0;
	basis[11]		=	1	/6.0;

	basis[12]		=	1	/6.0;
	basis[13]		=	0	/6.0;
	basis[14]		=	0	/6.0;
	basis[15]		=	0	/6.0;

	fread ( &Nmax, sizeof(int), 1, f );

	ev = (TEvalStruct **) malloc ( (Nmax-2)*sizeof(TEvalStruct *) );

	for ( i=0 ; i<Nmax-2 ; i++ ) {
		N = i+3;
		K = 2*N+8;

		ev[i] = (TEvalStruct *) malloc ( sizeof(TEvalStruct) );
		ev[i]->val = (double *) malloc ( K*sizeof(double) );
		ev[i]->vecI = (double *) malloc ( K*K*sizeof(double) );
		ev[i]->Phi = (double **) malloc ( 3*sizeof(double *) );
		ev[i]->Phi2 = (double **) malloc ( 3*sizeof(double *) );
		ev[i]->Phi[0] = (double *) malloc ( K*16*sizeof(double) );
		ev[i]->Phi[1] = (double *) malloc ( K*16*sizeof(double) );
		ev[i]->Phi[2]	= (double *) malloc ( K*16*sizeof(double) );
		ev[i]->Phi2[0] = (double *) malloc ( K*16*sizeof(double) );
		ev[i]->Phi2[1] = (double *) malloc ( K*16*sizeof(double) );
		ev[i]->Phi2[2] = (double *) malloc ( K*16*sizeof(double) );

		fread ( ev[i]->val, sizeof(double), K, f );
		fread ( ev[i]->vecI, sizeof(double), K*K, f );
		fread ( ev[i]->Phi[0], sizeof(double), K*16, f );
		fread ( ev[i]->Phi[1], sizeof(double), K*16, f );
		fread ( ev[i]->Phi[2], sizeof(double), K*16, f );

		{
		  int	oi,oj,ok;

			for (oi=0;oi<3;oi++) {
				for (oj=0;oj<K;oj++) {
					double	*coef	=	ev[i]->Phi[oi]+oj;
					double	*dest	=	ev[i]->Phi2[oi]+oj*16;
					int		ox,oy;

					for (ok=0;ok<16;ok++) {
					  dest[ok]		=	0;
					}

					for (ok=0;ok<16;ok++) {
					int	om	=	ok / 4;
					int	on	=	ok % 4;

						for (ox=0;ox<4;ox++) {
							for (oy=0;oy<4;oy++) {
								dest[oy*4+ox]	+=	coef[ok*K]*basis[om*4+ox]*basis[on*4+oy];
							}
						}
					}
				}
			}
		}
	}

	fprintf(out,"// Internally generated subdivision data...\n// Do not mess with it\n\n");
	fprintf(out,"#define NMAX %d\n\n",Nmax);
	fprintf(out,"class CEigenBasis {\n");
	fprintf(out,"public:\n");
	fprintf(out,"\tfloat *evals;\n");
	fprintf(out,"\tfloat *evecs;\n");
	fprintf(out,"\tfloat *basis[3];\n");
	fprintf(out,"};\n\n");

	{
		for (i=0;i<Nmax-2;i++) {
			N = i+3;
			K = 2*N+8;

			fprintf(out,"static float valence%dData[] = {0\n",i);

			for (j=0;j<K;j++) {
				fprintf(out,",(float) %f\n",ev[i]->val[j]);
			}

			for (j=0;j<K*K;j++) {
				fprintf(out,",(float) %f\n",ev[i]->vecI[j]);
			}

			for (k=0;k<3;k++) {
				for (j=0;j<K*16;j++) {
					fprintf(out,",(float) %f\n",ev[i]->Phi2[k][j]);
				}
			}

			fprintf(out,"};\n\n");
		}


		fprintf(out,"static CEigenBasis basisData[] = {\n");
		fprintf(out,"{NULL,NULL,{NULL,NULL,NULL}}\n");
		fprintf(out,",{NULL,NULL,{NULL,NULL,NULL}}\n");
		fprintf(out,",{NULL,NULL,{NULL,NULL,NULL}}\n");
		for (i=0;i<Nmax-2;i++) {
			N = i+3;
			K = 2*N+8;

			int	valStart	=	1;
			int	vecStart	=	valStart	+	K;
			int	basis0Start	=	vecStart	+	K*K;
			int	basis1Start	=	basis0Start	+	K*16;
			int	basis2Start	=	basis1Start	+	K*16;

			fprintf(out,",{valence%dData + %d, valence%dData + %d,{valence%dData + %d, valence%dData + %d, valence%dData + %d}}\n",i,valStart,i,vecStart,i,basis0Start,i,basis1Start,i,basis2Start);
		}
		fprintf(out,"};\n");
	}

	fclose(out);
	return FALSE;
}


///////////////////////////////////////////////////////////////////////
// Function				:	precomputeExplosionData
// Description			:	create subdivisionData.h header file for the ri
// Return Value			:	TRUE on success, FALSE otherwise
// Comments				:
// Date last edited		:	10/27/2002
int	precomputeExplosionData() {
	#ifdef _WIN32
		FILE	*out	=	fopen("..\\src\\ri\\experimental\\explosionData.h","w");
	#else
		FILE	*out	=	fopen("../ri/experimental/explosionData.h","w");
	#endif
	int		i;

	if (out == NULL)	return TRUE;

	fprintf(out,"//Internally generated explosion data.\n//Do not mess with it\n\n");
	fprintf(out,"#define	MIN_TEMPERATURE		%d\n",MIN_TEMPERATURE);
	fprintf(out,"#define	MAX_TEMPERATURE		%d\n",MAX_TEMPERATURE);
	fprintf(out,"#define	NUM_TEMPERATURES	%d\n",NUM_TEMPERATURES);
	fprintf(out,"\n\n");


	fprintf(out,"static vector	bb[%d] = {\n",NUM_TEMPERATURES);
	for (i=0;i<NUM_TEMPERATURES;i++) {
		double	t	=	(MAX_TEMPERATURE - MIN_TEMPERATURE)*i / (float) NUM_TEMPERATURES + MIN_TEMPERATURE;
		vector	tmp,tmp2;

		blackBody(tmp,t);
		xyzTorgb(tmp2,tmp);

		if (i == 0)	fprintf(out,"{(float) %f,(float) %f,(float) %f}\n",tmp2[0],tmp2[1],tmp2[2]);
		else		fprintf(out,",{(float) %f,(float) %f,(float) %f}\n",tmp2[0],tmp2[1],tmp2[2]);
		
	}
	fprintf(out,"};\n");

	fprintf(out,"\n\n\n");
	fprintf(out,"#define	emission(__dest,__temp)	{\\\n");
	fprintf(out,"	int	bIndex			=	(int) (NUM_TEMPERATURES*((__temp) - MIN_TEMPERATURE) / (float) (MAX_TEMPERATURE - MIN_TEMPERATURE));\\\n");
	fprintf(out,"	bIndex				=	max(bIndex,0);\\\n");
	fprintf(out,"	bIndex				=	min(bIndex,NUM_TEMPERATURES-1);\\\n");
	fprintf(out,"	movvv(__dest,bb[bIndex]);\\\n");
	fprintf(out,"}\n\n");

	fclose(out);

	return FALSE;
}



///////////////////////////////////////////////////////////////////////
// Function				:	main
// Description			:	Do the thing baby
// Return Value			:	0 on success, 1 on failure
// Comments				:
// Date last edited		:	10/27/2002
int		genUnroll(const char *fileName,int numConditions,char **conditions,char **definitions,char **undefinitions,const char *code) {
	FILE	*out	=	fopen(fileName,"w");
	int		i,j,k;

	if (out == NULL)	return FALSE;

	fprintf(out,"#ifdef PROTOTYPE\n");
	for (i=0;i<(1<<numConditions);i++) 	fprintf(out,"void	stochastic%d(CRasterGrid *);\n",i);
	fprintf(out,"#endif\n");

	fprintf(out,"#ifdef DISPATCH\n");
	fprintf(out,"\tint	conditionTracker=0;\n");
	for (i=0;i<numConditions;i++) fprintf(out,"\t%s conditionTracker |= %d;\n",conditions[i],1<<i);
	fprintf(out,"\tswitch(conditionTracker) {\n");
	for (j=0;j<(1<<i);j++) {
		fprintf(out,"\t\tstochastic%d(grid);\n",j);
		fprintf(out,"\t\tbreak;\n");
	}
	fprintf(out,"\t}\n");
	fprintf(out,"#endif\n");


	fprintf(out,"#ifdef CODE\n");
	for (j=0;j<(1<<i);j++) {
		fprintf(out,"void CStochastic::stochastic%d(CRasterGrid *grid){\n",j);
		for (k=0;k<i;k++)	if (j & (1 << k))	fprintf(out,"\t\t%s\n",definitions[k]);
		fprintf(out,"\n\n\t\t%s\t\n\n\n",code);
		for (k=0;k<i;k++)	if (j & (1 << k))	fprintf(out,"\t\t%s\n",undefinitions[k]);
		fprintf(out,"}\n");
	}
	fprintf(out,"#endif\n");


	fclose(out);

	return TRUE;
}

///////////////////////////////////////////////////////////////////////
// Function				:	main
// Description			:	Do the thing baby
// Return Value			:	0 on success, 1 on failure
// Comments				:
// Date last edited		:	10/27/2002
int	main(int argc,char *argv[]) {

	memInit();

	/*
	if (precomputeSubdivisionData() == TRUE) {
		return 1;
	}

	if (precomputeNoiseData() == TRUE) {
		return 1;
	}

	if (precomputeExplosionData() == TRUE) {
		return 1;
	}
	*/

	{
		const	int		numCond	=	13;
		char	*cond[numCond]	=	{	"if (grid->flags & RASTER_TRANSPARENT)	",
										"if (grid->flags & RASTER_UNSHADED)		",
										"if (grid->flags & RASTER_EXTRASAMPLES)	",
										"if (grid->flags & RASTER_MOVING)		",
										"if (grid->flags & RASTER_POINT)			",
										"if (grid->flags & RASTER_FOCALBLUR)		",
										"if (grid->flags & RASTER_MATTE)			",
										"if (grid->flags & RASTER_LOD)			",
										"if (grid->flags & RASTER_UNDERCULL)		",
										"if (depthFilter == DEPTH_MIN)		",
										"if (depthFilter == DEPTH_MAX)		",
										"if (depthFilter == DEPTH_AVG)		",
										"if (depthFilter == DEPTH_MID)		"	};

		char	*def[numCond]	=	{	"#define	HIDDEN_TRANSPARENT",
										"#define	HIDDEN_UNSHADED",
										"#define	HIDDEN_EXTRASAMPLES",
										"#define	HIDDEN_MOVING",
										"#define	HIDDEN_POINT",
										"#define	HIDDEN_FOCALBLUR",
										"#define	HIDDEN_MATTE",
										"#define	HIDDEN_LOD",
										"#define	HIDDEN_UNDERCULL",
										"#define	depthFilterIf()	depthFilterIfMin()\n\t\t#define	depthFilterElse()	depthFilterElseMin()",	
										"#define	depthFilterIf()	depthFilterIfMax()\n\t\t#define	depthFilterElse()	depthFilterElseMax()",	
										"#define	depthFilterIf()	depthFilterIfAvf()\n\t\t#define	depthFilterElse()	depthFilterElseAvg()",	
										"#define	depthFilterIf()	depthFilterIfMid()\n\t\t#define	depthFilterElse()	depthFilterElseMid()",			
																		};

		char	*undef[numCond]	=	{	"#undef	HIDDEN_TRANSPARENT",
										"#undef	HIDDEN_UNSHADED",
										"#undef	HIDDEN_EXTRASAMPLES",
										"#undef	HIDDEN_MOVING",
										"#undef	HIDDEN_POINT",
										"#undef	HIDDEN_FOCALBLUR",
										"#undef	HIDDEN_MATTE",
										"#undef	HIDDEN_LOD",
										"#undef	HIDDEN_UNDERCULL",
										"#undef	depthFilterIf\n\t\t#undef	depthFilterElse",
										"#undef	depthFilterIf\n\t\t#undef	depthFilterElse",
										"#undef	depthFilterIf\n\t\t#undef	depthFilterElse",
										"#undef	depthFilterIf\n\t\t#undef	depthFilterElse"	};
		
		genUnroll("..\\src\\ri\\stochasticSwitch.h",numCond,cond,def,undef,"#include \"stochasticFragment.h\"");
	}


	memShutdown();

	return 0;
}
