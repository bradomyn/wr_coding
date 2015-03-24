#include "genpoly.h"

uint8_t *genpoly(uint8_t n, uint8_t alpha, uint8_t k, uint8_t m) {

        static uint8_t gen_poly[255];
        uint8_t tmp_poly[255];
        uint8_t new_poly[3];
        uint8_t tmp_mult;
        uint16_t i, l, j;
        uint16_t max_degree;
        uint16_t index;
        uint16_t tmp_max_degree;

        // init poly (x + 2^0)(x + 2^1)
        gen_poly[0] = 2;
        gen_poly[1] = 3;
        gen_poly[2] = 1;

        max_degree = 2;
        tmp_max_degree = 2;

        new_poly[0] = 2;
        new_poly[1] = 1;

        //printf("Generator Poly degree %d \n", n-k);

        for ( i = 2; i < (n-k); i++) {
                new_poly[0] = galois_single_multiply(new_poly[0],2,m);

                memset(tmp_poly, 0, sizeof(tmp_poly));

                for ( l = 0; l <= 1; l++) {
                        for ( j = 0; j <= max_degree; j++) {
                                index = l + j;
                                //printf("Max degree %d degree %d = gen pol %d + new pol %d \n", max_degree, index, j, l);

                                if (index > max_degree) {
                                        //printf("Max Degree %d \n", index);
                                        tmp_max_degree = index;
                                }

                                tmp_mult = galois_single_multiply(new_poly[l], gen_poly[j], m);
                                //printf(" (gen_poly %d * new_poly %d) =  %d", gen_poly[j], new_poly[l], tmp_mult);
                                //printf(" + gen_poly(%d) %d = ", index, tmp_poly[index]);

                                tmp_poly[index] = tmp_mult ^ tmp_poly[index];

                                //printf("%d -- degree %d \n", tmp_poly[index], index);

                        }

                        max_degree = tmp_max_degree;

                //printf("--------------\n");
                }
                for ( j = 0; j <= max_degree; j++) {
                        gen_poly[j] =  tmp_poly[j];
                }

        //printf("*******************\n");
        }

        /*for( i = 0; i <= max_degree ; i++) {
                if (i < max_degree)
                        printf(" %dx^^%d +", gen_poly[i], i);
                else
                        printf(" %dx^^%d \n", gen_poly[i], i);
        }*/

        return gen_poly;
}
