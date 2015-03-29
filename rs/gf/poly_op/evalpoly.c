#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "poly_op.h"

int main(int argc, char **argv) {

        rs_poly eval_poly;
        int8_t c;
        uint8_t v;
        uint16_t i, len, result;
        char *p;

        if(argc < 2) {
                printf("Usage: %s -p -v \n",argv[0]);

                printf("-p, \t\t poly \n");
                printf("-v, \t\t var \n");
                return 0;
        }

        while ((c = getopt (argc, argv, "p:v:")) != -1) {
                switch (c) {
                        case 'p' :
                                p = optarg;
                                break;
                        case 'v' :
                                v = atoi(optarg);
                                break;
                }
        }

        len = strlen(p);

        gf_init_poly(&eval_poly, len, 8, "EVAL_POLY");

        for (i = 0; i < len; i++)
                eval_poly.poly[i] = p[i] - '0';

        dump_poly("EVAL_POLY", &eval_poly);

        result = gf_poly_eval(&eval_poly, v);

        gf_free_poly(&eval_poly);

        printf("Eval p(%d) = %d\n", v, result);

        return 0;
}
