/* basic poly operation for Reed Solomon algorithm.
 * Multiplication, substitution and Generator Poly.
 * The polynomials are store in arrays, the index
 * of the array corresponds with the degree of the poly
 * x^0 = array[0]
 */

#ifndef __GEN_POLY__
#define __GEN_POLY__

#include <stdint.h>
#include <string.h>
#include <galois.h>

typedef uint8_t *gf_poly;

struct  rs_polynomial {
        gf_poly poly;
        uint8_t degree;
        uint8_t base;
};

typedef struct rs_polynomial rs_poly;

struct polynomial_op {
        int8_t  (*init)(rs_poly *poly, uint8_t degree, uint8_t base, char *str);
        void    (*free)(rs_poly *poly);
        void    (*dump)(char *str, rs_poly *poly);
        int8_t  (*gen_poly)(rs_poly *gen_poly, uint8_t alpha);
        uint8_t (*eval)(rs_poly *poly, uint8_t value);
        int8_t  (*mult)(rs_poly *a_poly, rs_poly *b_poly, rs_poly *mult_poly);
};


/* n .- encoded symbols length
 * k .- source symbols length
 * alpha .- g(x) = (x + alpha^0)(x + alpha^1)...(x + alpha^(n-k))
 * m .- GF(2^m)
 */

int8_t gf_gen_poly(rs_poly *gen_poly, uint8_t alpha);
int8_t gf_poly_mult(rs_poly *a_poly, rs_poly *b_poly, rs_poly *mult_poly);
uint8_t gf_poly_eval(rs_poly *poly, uint8_t value);
void dump_poly(char * str, rs_poly *poly);
int8_t gf_init_poly(rs_poly *poly, uint8_t degree, uint8_t base, char *str);
void gf_free_poly(rs_poly *poly);
#endif

