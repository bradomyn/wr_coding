#include "rs.h"

#define DEGREE(x) (sizeof(x) / sizeof(x[0]))

struct reed_solomon_op rs_op = {
        .gen_poly = genpoly,
        .sum = galois_single_sum,
        .mult = galois_single_multiply,
        .div  = galois_single_divide,
};

struct reed_solomon_conf rs_conf;

static uint8_t gf_poly_eval(uint8_t *code, uint8_t value, uint8_t len) {

        uint8_t poly;
        uint16_t i;

        poly = code[0];

        for (i=1; i < len; i++) {

                poly = rs_op.mult(poly, value, 8) ^ code[i];
        }

        return poly;
}

static void rs_calc_sydrom( uint8_t *encoded, uint8_t *synd) {

        int16_t i;
        for (i = rs_conf.n - rs_conf.k; i >= 0 ; i++) {  /// be carefull with the order
                synd[i] = gf_poly_eval(encoded, galois_ilog(i, rs_conf.m), rs_conf.n);
        }
}

int8_t rs_init() {

        if ((2 << rs_conf.m) < (rs_conf.n + rs_conf.k)) {
                printf("ERROR : RS n+k is bigger than the Close Space of GF\n");
                return -1;
        }

        return 0;
}

int8_t rs_encode(uint8_t *eth_payload, uint8_t *encoded_data) {

        uint8_t *gen_poly;
        uint8_t *quotient;
        int16_t i, j, t;

        uint16_t gen_poly_l;
        uint16_t dg_dividend;
        uint16_t dg_divisor;

        if ((quotient = (uint8_t *)calloc(rs_conf.k, sizeof(uint8_t))) == NULL) {
                printf("ERROR : Can't create generator polynomial \n");
                return -1;
        }

        // generator poly
        gen_poly = rs_op.gen_poly(rs_conf.n, 2, rs_conf.k, rs_conf.m);

        printf("Generator Poly: ");

        for(i = 0; i < rs_conf.n - rs_conf.k + 1; i++)
                printf("%x ", gen_poly[i]);

        printf("\n");


        gen_poly_l = rs_conf.n - rs_conf.k + 1;

        // 1) source * x^(m-k)
        // it is done moving the pointer X symbols
        memset(encoded_data, 0, rs_conf.n * sizeof(uint8_t));

        for (i = rs_conf.n, t = rs_conf.k; t <= 0, (i >= rs_conf.n - rs_conf.k); i--, t--)
                 encoded_data[i] = *(((uint8_t *)eth_payload)+t);

        printf("Step 1) Symbol vector * x^(m-k): ");
        for (i = 0; i < rs_conf.n ; i++)
               printf("%x ", encoded_data[i]);
        printf("\n");

        // 2) rs = (source * x^(m-k)) / gen_poly
        printf("Step 2) rs = (source * x^(m-k)) / gen_poly \n");

        dg_dividend = rs_conf.n - 1;
        dg_divisor  = gen_poly_l - 1;

        //printf("\nSymbols L %d Gen Poly L %d \n",dg_dividend, dg_divisor);

        for ( i = 0; i < rs_conf.n - gen_poly_l + 1; i++) {
                for ( j = 0; j < gen_poly_l; j++) {
                        if ( j == 0) {

                                quotient[i] = (uint8_t)encoded_data[dg_dividend-i];
                                encoded_data[dg_dividend-i] = 0;

                                printf("quotient %x \n", quotient[i]);

                        } else {

                                printf("encoded_data %x - (gen_pol %x * %x) \n", encoded_data[dg_dividend-i-j],
                                                                            gen_poly[dg_divisor - j],
                                                                            quotient[i]);

                                encoded_data[dg_dividend-i-j] = rs_op.sum(encoded_data[dg_dividend-i-j],
                                                                rs_op.mult(quotient[i],
                                                                gen_poly[dg_divisor - j], rs_conf.m), rs_conf.m);

                                printf("--> %x \n", encoded_data[dg_dividend-i-j]);

                        }
                }
                printf("------------ \n");
                for (t = 0; t < rs_conf.n ; t++)
                        printf("%x ", encoded_data[t]);

                printf("\n --------- \n");
        }

        printf("Enconded Symbols : \n");
        for (t = 0; t < rs_conf.n - rs_conf.k ; t++) {

                if ( t != 0 )
                        printf("+ %x x^%d ", encoded_data[t],t);
                else
                        printf("%x ", encoded_data[t]);
        }

        printf("\n");


        return 0;
}

int8_t rs_decode(uint8_t *encoded_data, uint8_t *decoded_data) {

        uint8_t *synd;
        uint8_t l, i;

        l = rs_conf.n - rs_conf.k;

        synd = (uint8_t *) calloc( l, sizeof(uint8_t));

        rs_calc_sydrom( encoded_data, synd);

        for(i = 0; i < l; i++)
                printf("%d ", synd[i]);

        printf("\n");

        return 0;
}
