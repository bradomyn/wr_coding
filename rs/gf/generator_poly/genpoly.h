#ifndef __GEN_POLY__
#define __GEN_POLY__

#include <stdint.h>
#include <string.h>
//#include "../galois.h"

typedef uint8_t generator_poly[255];

/* n .- encoded symbols length
 * k .- source symbols length
 * alpha .- g(x) = (x + alpha^0)(x + alpha^1)...(x + alpha^(n-k))
 * m .- GF(2^m)
 */
uint8_t *genpoly(uint8_t n, uint8_t alpha, uint8_t k, uint8_t m);

#endif

