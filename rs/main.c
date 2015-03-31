#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

#include "rs.h"

struct reed_solomon_conf rs_conf;

int main(int argc, char **argv) {

        char *c;
        uint8_t i=0,j;
        rs_poly src_symbols;
        rs_poly miss_symbols;
        rs_poly enc_symbols;
        rs_poly dec_symbols;

        uint16_t len;

        if(argc < 9) {
                printf("Usage: %s [OPTION..] STRING_TO_ENCODE \n",argv[0]);

                printf("\n");
                printf("OPTIONS:\n");
                printf("-k, \t\t Length message in src_symbols \n");
                printf("-n, \t\t Redundant src_symbols \n");
                printf("-m, \t\t Galois Filed index GF(2^m), 4 or 8 \n");
                printf("-s, \t\t String\n");
                return 0;
        }

        for( i = 1; i < argc; i++ ) {
                c = argv[i];

                switch (c[1]) {
                        case 'k' :
                                rs_conf.k = atoi(argv[++i]);
                                break;
                        case 'n' :
                                rs_conf.n = atoi(argv[++i]);
                                break;
                        case 'm' :
                                rs_conf.m = atoi(argv[++i]);
                                if( rs_conf.m != 4 && rs_conf.m != 8) {
                                        printf("GF(2^m) has to be 4 or 8 \n");
                                        return -1;
                                }
                                break;
                        case 's' :
                                len = argc - i - 1;
                                printf("Source src_symbols Length %d \n", len);
                                poly_op.init(&src_symbols, len-1, rs_conf.m, "SRC_SYMB");

                                for (j = 0, i++; i < argc; j++,i++)
                                        src_symbols.poly[j] = (uint8_t)strtol(argv[i], NULL, 0);
                                break;
                }

        }

        poly_op.dump("SRC_SYMB", &src_symbols);

        /* sanity checks and init the rs polynom */
        if (rs_init() < 0)
                return -1;

        poly_op.dump("GEN_POLY", &gen_poly);

        /* init enc_symbols */
        poly_op.init(&enc_symbols, rs_conf.n, rs_conf.m, "ENC_SYMB");

        /* encoded */
        rs_encode(&src_symbols, &enc_symbols);

        poly_op.dump("ENC_POLY", &enc_symbols);

        poly_op.init(&dec_symbols, rs_conf.k, rs_conf.m, "DEC_SYMB");

        //enc_symbols.poly[24] = 0;
        //enc_symbols.poly[23] = 0;
        //poly_op.init(&miss_symbols, 2, rs_conf.m, "MISS_SYMB");
        //miss_symbols.poly[0] = 24;
        //miss_symbols.poly[1] = 23;
        
        enc_symbols.poly[25] = 0;
        poly_op.init(&miss_symbols, 1, rs_conf.m, "MISS_SYMB");
        miss_symbols.poly[0] = 25;

        //poly_op.init(&miss_symbols, 2, rs_conf.m, "MISS_SYMB");
        //miss_symbols.poly[0] = 2;
        //miss_symbols.poly[1] = 9;
        //enc_symbols.poly[2] = 1;
        //enc_symbols.poly[9] = 11;

        poly_op.dump("RX_POLY",&enc_symbols);

        rs_decode(&enc_symbols, &dec_symbols, &miss_symbols);

        return 0;
}
