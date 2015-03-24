#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "genpoly.h"

int main(int argc, char **argv) {

        uint8_t *gen_poly;
        int8_t c;
        uint32_t i, max_degree;
        uint16_t k, m, n, a;

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

        max_degree = n - k;

        gen_poly = genpoly(n, a, k, m);

        for( i = 0; i <= max_degree ; i++) {
                if ( i == 0 )
                        printf(" %d +", gen_poly[i]);
                else if (i < max_degree)
                        printf(" %dx^^%d +", gen_poly[i], i);
                else
                        printf(" %dx^^%d \n", gen_poly[i], i);
        }

        return 0;
}
