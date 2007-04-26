//////////////////////////////////////////////////////////////////////
//
//                             Pixie
//
// Copyright © 1999 - 2003, Okan Arikan
//
// Contact: okan@cs.utexas.edu
//
//	This library is free software; you can redistribute it and/or
//	modify it under the terms of the GNU Lesser General Public
//	License as published by the Free Software Foundation; either
//	version 2.1 of the License, or (at your option) any later version.
//
//	This library is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//	Lesser General Public License for more details.
//
//	You should have received a copy of the GNU Lesser General Public
//	License along with this library; if not, write to the Free Software
//	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
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
#include "ri/renderer.h"
#include "ri/reyes.h"

typedef struct {
  double * val;
  double * vecI;
  double ** Phi;
  double ** Phi2;
} TEvalStruct;

#define IX(i,j,n) ((i)+(n)*(j))





///////////////////////////////////////////////////////////////////////
// Function				:	precomputeSubdivisionData
// Description			:	create subdivisionData.h header file for the ri
// Return Value			:	TRUE on success, FALSE otherwise
// Comments				:
int	precomputeSubdivisionData() {
	FILE			*out;
	TEvalStruct		**ev;
	FILE			*f;
	int				Nmax,i,N,K;
	double			basis[16];
	int				j,k;

#ifdef _WINDOWS
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
// Function				:	ouputStochasticFuntionName
// Description			:	write out the function name for rasterization functions
// Return Value			:	
// Comments				:
void		ouputStochasticFuntionName(FILE *out, unsigned int i) {
	if (i & RASTER_POINT)
		fprintf(out,"drawPointGrid");
	else
		fprintf(out,"drawQuadGrid");
	
	switch(i >> RASTER_HIGHBITS_SHIFT) {
	case DEPTH_MIN:
		fprintf(out,"Zmin");
		break;
	case DEPTH_MAX:
		fprintf(out,"Zmax");
		break;
	case DEPTH_AVG:
		fprintf(out,"Zavg");
		break;
	case DEPTH_MID:
		fprintf(out,"Zmid");
		break;
	}
	
	if (i & RASTER_UNSHADED)		fprintf(out,"Unshaded");
	if (i & RASTER_MOVING)			fprintf(out,"Moving");
	if (i & RASTER_TRANSPARENT)		fprintf(out,"Transparent");
	if (i & RASTER_FOCALBLUR)		fprintf(out,"DepthBlur");
	if (i & RASTER_EXTRASAMPLES)	fprintf(out,"ExtraSamples");
	if (i & RASTER_MATTE)			fprintf(out,"Matte");
	if (i & RASTER_LOD)				fprintf(out,"LOD");
	if (i & RASTER_UNDERCULL)		fprintf(out,"Undercull");
	if (i & RASTER_XTREME)			fprintf(out,"Xtreme");
}

///////////////////////////////////////////////////////////////////////
// Function				:	precomputeStochasticPrimitivesH
// Description			:	Compute stochastic.h
// Return Value			:	0 on success, 1 on failure
// Comments				:
int		precomputeStochasticPrimitivesH() {
	#ifdef _WINDOWS
		FILE	*out	=	fopen("..\\src\\ri\\stochasticPrimitives.h","w");
	#else
		FILE	*out	=	fopen("../ri/stochasticPrimitives.h","w");
	#endif
	int		i;

	if (out == NULL) return TRUE;
	
	fprintf(out,"//Internally generated header file.\n//Do not mess with it\n\n");

	// Instantiate the dispatch switch
	
	fprintf(out,"#ifdef DEFINE_STOCHASTIC_SWITCH\n");
	
	fprintf(out,"switch((grid->flags & RASTER_GLOBAL_MASK) | (CRenderer::depthFilter << RASTER_HIGHBITS_SHIFT)) {\n");
	const int caseEnumeration = RASTER_GLOBAL_MASK | (RASTER_DEPTHFILT_MASK << RASTER_HIGHBITS_SHIFT);
	for (i=0;i<=caseEnumeration;i++) {
		fprintf(out,"case %d:\n",i);
		
		// Unshaded grids never have RASTER_MATTE or RASTER_TRANSPARENT or RASTER_LOD set
		// but we leave the case in as it can help the compiler generate a fast switch statement
		// Shaded grids never have RASTER_UNDERCULL
		if (i & RASTER_UNSHADED) {
			if ((i & RASTER_MATTE) || (i & RASTER_TRANSPARENT)  || (i & RASTER_LOD)) {
				fprintf(out,"\tbreak;\n");
				continue;
			}
		} else {
			if (i & RASTER_UNDERCULL) {
				fprintf(out,"\tbreak;\n");
				continue;
			}
		}

		// Points do not have xtreme motion
		if (i & RASTER_XTREME) {
			if (i & RASTER_POINT) {
				continue;
			}
		}
		
		// output the function name
		fprintf(out,"\t");
		ouputStochasticFuntionName(out,i);

		fprintf(out,"(grid);\n");

		fprintf(out,"\tbreak;\n");
	}
	fprintf(out,"default:\n");
	fprintf(out,"\tbreak;\n");
	fprintf(out,"}\n");
	
	fprintf(out,"#endif\n");
	
	// Instantiate the functions and the function prototypes
	
	for (int j = 0; j < 2; j++){
		if(j)	fprintf(out,"#ifdef DEFINE_STOCHASTIC_FUNPROTOS\n");
		else	fprintf(out,"#ifdef DEFINE_STOCHASTIC_FUNCTIONS\n");
		
		for (i=0;i<=caseEnumeration;i++) {
			// Unshaded grids never have RASTER_MATTE or RASTER_TRANSPARENT or RASTER_LOD set
			// so we don't have to generate functions for those combinations
			// Unshaded grids are the only ones which can be underculled
			if (i & RASTER_UNSHADED) {
				if ((i & RASTER_MATTE) || (i & RASTER_TRANSPARENT)  || (i & RASTER_LOD)) {
					continue;
				}
			} else {
				if (i & RASTER_UNDERCULL) {
					continue;
				}
			}

			// Points do not have xtreme motion
			if (i & RASTER_XTREME) {
				if (i & RASTER_POINT) {
					continue;
				}
			}
	
			// output the function name
			if (j)	fprintf(out,"void ");
			else	fprintf(out,"void CStochastic::");
			ouputStochasticFuntionName(out,i);
			fprintf(out,"(CRasterGrid *grid)");
			if (j) {
				fprintf(out,";\n");
				continue;
			}
			
			// when instantiating the functions, write out the body			
			fprintf(out,"{\n");
			
			if (i & RASTER_MOVING)			fprintf(out,"\t#define STOCHASTIC_MOVING\n");
			if (i & RASTER_TRANSPARENT)		fprintf(out,"\t#define STOCHASTIC_TRANSPARENT\n");
			if (i & RASTER_UNSHADED)		fprintf(out,"\t#define STOCHASTIC_UNSHADED\n");
			if (i & RASTER_FOCALBLUR)		fprintf(out,"\t#define STOCHASTIC_FOCAL_BLUR\n");
			if (i & RASTER_EXTRASAMPLES)	fprintf(out,"\t#define STOCHASTIC_EXTRA_SAMPLES\n");
			if (i & RASTER_MATTE)			fprintf(out,"\t#define STOCHASTIC_MATTE\n");
			if (i & RASTER_LOD)				fprintf(out,"\t#define STOCHASTIC_LOD\n");
			if (i & RASTER_UNDERCULL)		fprintf(out,"\t#define STOCHASTIC_UNDERCULL\n");
			if (i & RASTER_XTREME)			fprintf(out,"\t#define STOCHASTIC_XTREME\n");

			// Define the depth filter macros
			switch(i >> RASTER_HIGHBITS_SHIFT) {
			case DEPTH_MIN:
				fprintf(out,"\t#define depthFilterIf()\t\tdepthFilterIfZMin()\n");
				fprintf(out,"\t#define depthFilterElse()\tdepthFilterElseZMin()\n");
				break;
			case DEPTH_MAX:
				fprintf(out,"\t#define depthFilterIf()\t\tdepthFilterIfZMax()\n");
				fprintf(out,"\t#define depthFilterElse()\tdepthFilterElseZMax()\n");
				break;
			case DEPTH_AVG:
				fprintf(out,"\t#define depthFilterIf()\t\tdepthFilterIfZAvg()\n");
				fprintf(out,"\t#define depthFilterElse()\tdepthFilterElseZAvg()\n");
				break;
			case DEPTH_MID:
				fprintf(out,"\t#define depthFilterIf()\t\tdepthFilterIfZMid()\n");
				fprintf(out,"\t#define depthFilterElse()\tdepthFilterElseZMid()\n");
				break;
			}
		
			if (i & RASTER_POINT) {
				fprintf(out,"\n\n\t\t#include \"stochasticPoint.h\"\n");
			} else {
				fprintf(out,"\n\n\t\t#include \"stochasticQuad.h\"\n\n\n");
			}
			
			fprintf(out,"\t#undef depthFilterIf\n");
			fprintf(out,"\t#undef depthFilterElse\n");
			
		
			if (i & RASTER_MOVING)			fprintf(out,"\t#undef STOCHASTIC_MOVING\n");
			if (i & RASTER_TRANSPARENT)		fprintf(out,"\t#undef STOCHASTIC_TRANSPARENT\n");
			if (i & RASTER_UNSHADED)		fprintf(out,"\t#undef STOCHASTIC_UNSHADED\n");
			if (i & RASTER_FOCALBLUR)		fprintf(out,"\t#undef STOCHASTIC_FOCAL_BLUR\n");
			if (i & RASTER_EXTRASAMPLES)	fprintf(out,"\t#undef STOCHASTIC_EXTRA_SAMPLES\n");
			if (i & RASTER_MATTE)			fprintf(out,"\t#undef STOCHASTIC_MATTE\n");
			if (i & RASTER_LOD)				fprintf(out,"\t#undef STOCHASTIC_LOD\n");
			if (i & RASTER_UNDERCULL)		fprintf(out,"\t#undef STOCHASTIC_UNDERCULL\n");
			if (i & RASTER_XTREME)			fprintf(out,"\t#undef STOCHASTIC_XTREME\n");
	
			fprintf(out,"}\n");
		}
		
		fprintf(out,"#endif\n");
	}

	fclose(out);
	return FALSE;
}

///////////////////////////////////////////////////////////////////////
// Function				:	main
// Description			:	Do the thing baby
// Return Value			:	0 on success, 1 on failure
// Comments				:
int	main(int argc,char *argv[]) {

	/*
	if (precomputeSubdivisionData() == TRUE) {
		return 1;
	}
	*/

	if (precomputeStochasticPrimitivesH() == TRUE) {
		return 1;
	}

	return 0;
}

