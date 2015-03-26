#include "rs.h"

#define DEGREE(x) (sizeof(x) / sizeof(x[0]))

struct reed_solomon_op rs_op = {
        .gen_poly = genpoly,
        .sum = galois_single_sum,
        .mult = galois_single_multiply,
        .div  = galois_single_divide,
};

struct reed_solomon_conf rs_conf;

int8_t rs_init() {

        if ((2 << rs_conf.m) < (rs_conf.n + rs_conf.k)) {
                printf("ERROR : RS n+k is bigger than the Close Space of GF\n");
                return -1;
        }

        return 0;
}

int8_t rs_encode(void *eth_payload, void *encoded_data) {

        uint8_t *symbol;
        uint8_t *tmp;
        uint8_t *gen_poly;
        uint8_t *remainder;
        uint8_t *quotient;
        uint16_t i, j, k;
        uint16_t gen_poly_l;
        uint16_t dg_dividend;
        uint16_t dg_divisor;
        uint16_t dg_remainder;
        uint16_t dg_quotient;

        if ((symbol = (uint8_t *)calloc(15, sizeof(uint8_t))) == NULL) {
                printf("ERROR : Can't create generator polynomial \n");
                return -1;
        }

        if ((quotient = (uint8_t *)calloc(11, sizeof(uint8_t))) == NULL) {
                printf("ERROR : Can't create generator polynomial \n");
                return -1;
        }

        // generator poly
        gen_poly = rs_op.gen_poly(rs_conf.n, 2, rs_conf.k, rs_conf.m);
        gen_poly_l = rs_conf.n - rs_conf.k + 1;

        // 1) source * x^(m-k)
        // it is done moving the pointer X symbols
        memset(symbol, 0, 15*sizeof(uint8_t));

        tmp = (uint8_t *)eth_payload;
        symbol = tmp-4;

        printf("Symbol vector * x^(m-k): ");
        for (i = 0; i < 15 ; i++)
               printf("%d ", symbol[i]);
        printf("\n");


        // 2) rs = (source * x^(m-k)) / gen_poly
        dg_dividend = 14;
        dg_divisor  = gen_poly_l-1;

        printf("\nSymbols L %d Gen Poly L %d \n",dg_dividend, dg_divisor);

        for ( i = 0; i < rs_conf.n - gen_poly_l + 1; i++) {
                for ( j = 0; j < gen_poly_l; j++) {
                        if ( j == 0) {

                                quotient[i] = (uint8_t)symbol[dg_dividend-i];
                                symbol[dg_dividend-i] = 0;

                                printf("quotient %d \n", quotient[i]);

                        } else {

                                printf("symbol %d - (gen_pol %d * %d) \n", symbol[dg_dividend-i-j],
                                                                            gen_poly[dg_divisor - j],
                                                                            quotient[i]);

                                symbol[dg_dividend-i-j] = rs_op.sum(symbol[dg_dividend-i-j],
                                                                rs_op.mult(quotient[i],
                                                                gen_poly[dg_divisor - j], 4), 4);

                                printf("--> %d \n", symbol[dg_dividend-i-j]);

                        }
                }
                printf("--------- \n");
                for (k = 0; k < 15 ; k++)
                        printf("%d ", symbol[k]);

                printf("\n --------- \n");
        }

        return 0;
}

int8_t rs_decode(void *encoded_data, void *decoded_data) {



        return 0;
}
