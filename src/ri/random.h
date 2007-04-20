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
//  File				:	random.h
//  Classes				:	CSobol, CSphereSampler, CCosineSampler
//  Description			:	Several random generators
//
////////////////////////////////////////////////////////////////////////
#ifndef RANDOM_H
#define RANDOM_H

#include "common/global.h"		// The global header file
#include "common/os.h"
#include "common/algebra.h"

////////////////////////////////////////////////////////////////////////////
//
//
//
//	Random number generators
//
//
//
////////////////////////////////////////////////////////////////////////////


// maximum allowed space dimension
#define SOBOL_MAX_DIMENSION 40

// bit count; assumes sizeof(int) >= 32-bit
#define SOBOL_BIT_COUNT 30


// primitive polynomials in binary encoding
extern const int primitive_polynomials[SOBOL_MAX_DIMENSION];

// degrees of the primitive polynomials
extern const int degree_table[SOBOL_MAX_DIMENSION];

// initial values for direction tables, following
// Bratley+Fox, taken from [Sobol+Levitan, preprint 1976]
extern const int v_init[8][SOBOL_MAX_DIMENSION];

///////////////////////////////////////////////////////////////////////
// Class				:	CSobol
// Description			:	Sobol quasi random generator
// Comments				:
template <int dimension> class CSobol {
public:
					CSobol(int seq = 1) {
						init(seq);
					}

			void	init(int seq = 1) {
						unsigned int	i_dim;
						int				j, k;
						int				ell;

						assert(dimension < SOBOL_MAX_DIMENSION);

						// Initialize direction table in dimension 0.
						for(k=0; k<SOBOL_BIT_COUNT; k++) v_direction[k][0] = 1;

						// Initialize in remaining dimensions.
						for(i_dim=1; i_dim<dimension; i_dim++) {
							const int	poly_index	= i_dim;
							const int	degree_i	= degree_table[poly_index];
							int			includ[8];

							// Expand the polynomial bit pattern to separate
							// components of the logical array includ[].
							int p_i = primitive_polynomials[poly_index];
							for(k = degree_i-1; k >= 0; k--) {
							  includ[k] = ((p_i % 2) == 1);
							  p_i >>= 1;
							}

							// Leading elements for dimension i come from v_init[][].
							for(j=0; j<degree_i; j++) v_direction[j][i_dim] = v_init[j][i_dim];

							// Calculate remaining elements for this dimension,
							// as explained in Bratley+Fox, section 2.
							for(j=degree_i; j<SOBOL_BIT_COUNT; j++) {
							  int newv = v_direction[j-degree_i][i_dim];
							  ell = 1;
							  for(k=0; k<degree_i; k++) {
								ell *= 2;
								if(includ[k]) newv ^= (ell * v_direction[j-k-1][i_dim]);
							  }
							  v_direction[j][i_dim] = newv;
							}
						}

						// Multiply columns of v by appropriate power of 2.
						ell = 1;
						for(j=SOBOL_BIT_COUNT-1-1; j>=0; j--) {
							ell *= 2;
							for(i_dim=0; i_dim<dimension; i_dim++) {
							  v_direction[j][i_dim] *= ell;
							}
						}

						// 1/(common denominator of the elements in v_direction)
						last_denominator_inv = (float) (1.0 /(2.0 * ell));

						// final setup 
						sequence_count = seq;
						for(i_dim=0; i_dim<dimension; i_dim++) last_numerator_vec[i_dim] = 0;
					}



	void			get(float *v) {
						unsigned int i_dimension;

						// Find the position of the least-significant zero in count.
						int ell = 0;
						int c = sequence_count;
						while(1) {
							++ell;
							if((c % 2) == 1) c >>= 1;
							else break;
						}

						for(i_dimension=0; i_dimension<dimension; i_dimension++) {
							const int direction_i     = v_direction[ell-1][i_dimension];
							const int old_numerator_i = last_numerator_vec[i_dimension];
							const int new_numerator_i = old_numerator_i ^ direction_i;
							last_numerator_vec[i_dimension] = new_numerator_i;
							v[i_dimension] = new_numerator_i * last_denominator_inv;
						}

						sequence_count++;
						if (sequence_count >= (1 << SOBOL_BIT_COUNT)) {
							sequence_count	=	0;
						}
					}

	unsigned int	sequence_count;
	float			last_denominator_inv;
	int				last_numerator_vec[SOBOL_MAX_DIMENSION];
	int				v_direction[SOBOL_BIT_COUNT][SOBOL_MAX_DIMENSION];
};








// Different sampling functions
void	sampleHemisphere(float *R,const float *Z,const float theta,CSobol<4> &generator);
void	sampleCosineHemisphere(float *R,const float *Z,const float theta,CSobol<4> &generator);
void	sampleSphere(float *P,CSobol<3> &generator);


///////////////////////////////////////////////////////////////////////
// rand() replacements
///////////////////////////////////////////////////////////////////////

// TODO: rand() and random() are not thread safe

#ifndef HAVE_RANDOM
// rand() does not return random lower-order bits, so fix it up since this
// platform doesn't have random().

	#ifdef _WINDOWS
	static inline long int random() {
		// On Windows RAND_MAX is less than 0x7fffffff
		return rand();
	}
	#else
	static inline long int random() {
		long int retval;

		// Note that we are assuming RAND_MAX >= 0x7fffffff
		// If you're on an arch with sizeof(int) <= 2, this won't work
		// but then again, why would you be rendering there...

		retval  = (rand() >> 15) & 0x0000ffff;
		retval |=  rand()        & 0x7fff0000;

		return retval;
	}
	#endif
#endif

// The variants of urand and irand that work without a shading context

// Note that RAND_MAX is specific to rand().  random() always has a max
// of 0x7fffffff
static inline float _urand(){
	return random() / (float) 0x7fffffff;
}

static inline long int _irand() {
	return random();
}

#endif
