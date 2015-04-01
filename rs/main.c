#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "rs.h"
#include <poly_op.h>

static int random_at_most(int max_n) {

        int min = 1;
        srand ( time(NULL) );
        return rand() % (max_n + 1 - min) + min;
}

int main(int argc, char **argv) {

        char *c;
        uint8_t i=0,j;
        rs_poly src_symbols;
        rs_poly miss_symbols;
        rs_poly enc_symbols;
        rs_poly dec_symbols;
        uint8_t num_error, error_loc;

        uint16_t len;

        if(argc < 9) {
                printf("Usage: %s [OPTION..] STRING_TO_ENCODE \n",argv[0]);

                printf("\n");
                printf("OPTIONS:\n");
                printf("-k, \t\t Length message in src_symbols \n");
                printf("-n, \t\t Redundant src_symbols \n");
                printf("-m, \t\t Galois Filed index GF(2^m), 4 or 8 \n");
                printf("-s, \t\t string of 8 bits hex values\n");
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


        num_error = random_at_most(rs_conf.n - rs_conf.k + 1);

        printf("-------SENDING SYMBOLS----- %d SYMBOLS ERASED ----\n",num_error);

        poly_op.init(&miss_symbols, num_error, rs_conf.m, "MISS_SYMB");

        if (num_error > rs_conf.n_k) {
                printf("ERROR: more erasure than RS can fix :(\n");
        }

        for (i = 0; i < num_error; i++) {
                error_loc = random_at_most(rs_conf.n);
                miss_symbols.poly[i] = error_loc+i;
                enc_symbols.poly[error_loc+i] = 0x0;
                printf("ERror in %d %d\n", error_loc+i, enc_symbols.poly[error_loc+i]);
        }

        poly_op.dump("RX_POLY",&enc_symbols);

        rs_decode(&enc_symbols, &dec_symbols, &miss_symbols);

        poly_op.free(&src_symbols);
        poly_op.free(&miss_symbols);
        poly_op.free(&enc_symbols);
        poly_op.free(&dec_symbols);

        rs_close();
        return 0;
}
