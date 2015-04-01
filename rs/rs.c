#include "rs.h"


struct reed_solomon_conf rs_conf;

rs_poly gen_poly;
rs_poly synd;

void rs_calc_sydrom(rs_poly *enc_symbols) {

        int16_t i;

        for (i = 0; i < rs_conf.n_k; i++)
                synd.poly[i] = poly_op.eval(enc_symbols, rs_op.exp(i, rs_conf.m));
}

int8_t rs_init() {

        rs_conf.n_k = rs_conf.n - rs_conf.k;

        if ((2 << rs_conf.m) < (rs_conf.n_k)) {
                printf("ERROR : RS n+k is bigger than the Close Space of GF\n");
                return -1;
        }

        /* poly init */
        poly_op.init(&gen_poly, rs_conf.n_k, rs_conf.m, "GEN_POLY");

        /* generator poly */
        poly_op.gen_poly(&gen_poly, 2);

        poly_op.init(&synd, rs_conf.n_k, rs_conf.m, "SYND_POLY");

        return 0;
}

void rs_close() {

        poly_op.free(&gen_poly);
        poly_op.free(&synd);
}

int8_t rs_encode(rs_poly *src_symbols, rs_poly *enc_symbols) {

        int16_t  i, j, degree_enc, degree_gen;
        uint8_t coef;

        degree_enc = enc_symbols->degree;
        degree_gen = gen_poly.degree;

        for (i = 0; i <= degree_enc; i++) {
                enc_symbols->poly[i + degree_gen] = src_symbols->poly[i];
        }

        for (i = degree_enc - 1; i >= degree_gen; --i) {
                coef = enc_symbols->poly[i];
                if (coef != 0) {
                        for (j = degree_gen - 1; j >= 0; --j)
                                enc_symbols->poly[i + j - degree_gen] ^=
                                        rs_op.mult(gen_poly.poly[j], coef, gen_poly.base);
                }
        }

        for (i = 0; i <= src_symbols->degree; i++) {
                enc_symbols->poly[i+degree_gen] = src_symbols->poly[i];
        }

        return 0;
}


int8_t rs_decode(rs_poly *enc_symbols, rs_poly *decoded_data, rs_poly *miss_poly) {

        rs_calc_sydrom(enc_symbols);

        poly_op.dump("SYND_PO", &synd);

        rs_erase(enc_symbols, &synd, miss_poly);

        return 0;
}

int8_t rs_erase(rs_poly *enc_symbols, rs_poly *synd, rs_poly *miss_poly) {
        uint8_t y, z, t;

        rs_poly x;
        rs_poly p;
        rs_poly q;
        rs_poly mult;
        rs_poly qprime;
        int16_t i, j;

        poly_op.init(&x, 2, synd->base, "X_POLY");
        poly_op.init(&q, miss_poly->degree + 1, synd->base, "OMEGA_POLY");
        poly_op.init(&qprime, miss_poly->degree - 1, synd->base, "OMEGA_PRIM_POLY");
        poly_op.init(&mult, miss_poly->degree + 1, synd->base, "MULT_POLY");
        poly_op.init(&p, 2*miss_poly->degree, synd->base, "LAMBDA_POLY");


        q.poly[0] = 1;
        x.poly[0] = 1;

        /* calculate error locator polynomial */
        for (i = 0; i < miss_poly->degree; i++) {
                x.poly[1] = rs_op.exp(miss_poly->poly[i], rs_conf.m);
                poly_op.mult(&q, &x, &mult);

                for(j = 0; j < mult.degree; j++)
                        q.poly[j] = mult.poly[j];
        }

        /* calculate error evaluator polynomial */
        for (i = 0; i < miss_poly->degree; i++)
                p.poly[i] = synd->poly[i];

        p.degree = miss_poly->degree;

        poly_op.free(&mult);
        poly_op.init(&mult, miss_poly->degree + q.degree - 1, q.base, "MULT");

        poly_op.mult(&p, &q, &mult);

        for (i = 0; i <= miss_poly->degree; i++) {
                p.poly[i] = mult.poly[i];
        }

        p.degree = miss_poly->degree - 1;

        /* derivate error locator polynomial, even degree 0 */
        for (j=0, i=0; i <= q.degree; i++){
                if(i&0x1) {
                        qprime.poly[j] = q.poly[i];
                        j++;
                }
        }

        qprime.degree = j;

        /* compute correction */
        for (i = 0; i < miss_poly->degree; i++) {
                t = rs_op.exp(255 - miss_poly->poly[i], rs_conf.m);
                y = poly_op.eval(&p, t);
                z = poly_op.eval(&qprime, rs_op.mult(t,t,rs_conf.m));
                enc_symbols->poly[miss_poly->poly[i]] ^= rs_op.div(y, rs_op.mult(t,z,rs_conf.m), rs_conf.m);
        }

        poly_op.dump("DECO_POLY",enc_symbols);

        poly_op.free(&x);
        poly_op.free(&q);
        poly_op.free(&qprime);
        poly_op.free(&mult);
        poly_op.free(&p);

        return 0;
}

