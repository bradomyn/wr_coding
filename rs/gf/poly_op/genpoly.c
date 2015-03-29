#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "poly_op.h"

int main(int argc, char **argv) {

        rs_poly gen_poly;
        int8_t c;
        uint32_t i;
        uint8_t a, k, n, m;

        if(argc < 2) {
                printf("Usage: %s -k -m -n -a \n",argv[0]);

                printf("-k, \t\t source symbols \n");
                printf("-n, \t\t encoded symbols \n");
                printf("-m, \t\t GF(2^m) \n");
                printf("-a, \t\t alpha, base of the G(x) \n");
                return 0;
        }

        while ((c = getopt (argc, argv, "k:m:n:a:")) != -1) {
                switch (c) {
                        case 'k' :
                                k = atoi(optarg);
                                break;
                        case 'm' :
                                m = atoi(optarg);
                                break;
                        case 'n' :
                                n = atoi(optarg);
                                break;
                        case 'a' :
                                a = atoi(optarg);
                                break;
                }
        }

        gf_init_poly(&gen_poly, n - k, m, "GEN_POL");
        gf_gen_poly(&gen_poly, a);

        for( i = 0; i <= gen_poly.degree; i++) {
                if ( i == 0 )
                        printf(" %d +", gen_poly.poly[i]);
                else if (i < gen_poly.degree)
                        printf(" %dx^%d +", gen_poly.poly[i], i);
                else
                        printf(" %dx^%d \n", gen_poly.poly[i], i);
        }

        gf_free_poly(&gen_poly);

        return 0;
}
