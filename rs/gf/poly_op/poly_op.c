#include <galois.h>
#include "poly_op.h"

void dump_poly(char *str, rs_poly *poly) {
        uint8_t j;

        printf("%s: \t",str);
        for (j=0; j <= poly->degree; j++) {
                        printf("%d ",poly->poly[j]);
        }

        printf("\n");
}
void gf_free_poly(rs_poly *poly) {

        free(poly->poly);
}

int8_t gf_init_poly(rs_poly *poly, uint8_t degree, uint8_t base, char *str) {

        if((poly->poly = (gf_poly)calloc(degree, sizeof(gf_poly))) == NULL) {
                printf("ERROR ALLOC, can't alloc for %s poly\n", str);
                return -1;
        }

        poly->degree = degree;
        poly->base = base;

        return 0;
}

int8_t gf_gen_poly(rs_poly *gen_poly, uint8_t alpha) {

        uint8_t i, j;
        rs_poly g_poly;
        rs_poly mult_poly;

        gf_init_poly(&g_poly, 1, gen_poly->base, "G_POLY");

        gf_init_poly(&mult_poly, gen_poly->degree, gen_poly->base, "G_POLY");

        /*g(x) = (x + alpha^0)(x + alpha^1)...(x + alpha^(n-k))*/
        g_poly.poly[1] = 1; /* it's always degree 1 */
        gen_poly->poly[0] = 1;

        for (i=0; i < gen_poly->degree; i++) {
                g_poly.poly[0] = galois_ilog(i,gen_poly->base);

                //memset(mult_poly.poly,0,mult_poly.degree + 1);
                gf_poly_mult(gen_poly, &g_poly, &mult_poly);

                for (j=0; j <= gen_poly->degree; j++)
                        gen_poly->poly[j] = mult_poly.poly[j];
        }

        gf_free_poly(&g_poly);
        gf_free_poly(&mult_poly);

        return 0;
}

uint8_t gf_poly_eval(rs_poly *poly, uint8_t value) {

        uint8_t poly_eval;
        int16_t i;

        poly_eval = poly->poly[poly->degree];

        /* method */
        for (i = poly->degree - 1; i >= 0; i--)
                poly_eval = galois_single_multiply(poly_eval, value, poly->base) ^ poly->poly[i];

        return poly_eval;
}

int8_t gf_poly_mult(rs_poly *a_poly, rs_poly *b_poly, rs_poly *mult_poly) {

        uint16_t i,j;

        if (a_poly->base != b_poly->base) {
                printf("ERROR MULT, two poly with different GF base can't be mult\n");
                return -1;
        } else {
                mult_poly->base = a_poly->base;
        }

        memset(mult_poly->poly,0,mult_poly->degree + 1);

        for (j = 0; j <= b_poly->degree; j++) {
                for (i = 0; i <= a_poly->degree; i++) {
                        mult_poly->poly[i+j] ^= galois_single_multiply(a_poly->poly[i], b_poly->poly[j], mult_poly->base);
                }
        }
        return 0;
}

struct polynomial_op poly_op = {
        .init = gf_init_poly,
        .free = gf_free_poly,
        .dump = dump_poly,
        .gen_poly = gf_gen_poly,
        .eval = gf_poly_eval,
        .mult = gf_poly_mult,
};

