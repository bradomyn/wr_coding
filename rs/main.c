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
        uint16_t k, n, N;
        uint8_t m;
        uint8_t *puffy;
        uint8_t *symbols;
        uint8_t *encoded = NULL;
        uint8_t *decoded = NULL;
        uint16_t len;

        if(argc < 9) {
                printf("Usage: %s [OPTION..] STRING_TO_ENCODE \n",argv[0]);

                printf("\n");
                printf("OPTIONS:\n");
                printf("-k, \t\t Length message in Symbols \n");
                printf("-n, \t\t Redundant Symbols \n");
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
                                //if( rs_conf.m != 4 && rs_conf.m != 8) {
                                //        printf("GF(2^m) has to be 4 or 8 \n");
                                //        return -1;
                                //}
                                break;
                        case 's' :
                                len = argc - i - 1;
                                printf("Source Symbols Length %d \n", len);

                                if ((symbols = (uint8_t *)calloc(len - 1, sizeof(uint8_t))) == NULL) {
                                        printf("ERROR : Can't create generator polynomial \n");
                                        return -1;
                                }

                                for (j = 0, i++; i < argc; j++,i++) {
                                        //symbols[j] = atoi(argv[i]);

                                        symbols[j] = (uint8_t)strtol(argv[i], NULL, 0);
                                }
                                break;
                }

        }

        printf("Source Symbols : ");
        for ( i = 0; i < rs_conf.k; i++)
                printf("%x ", symbols[i]);

        printf("\n");

        printf("Length string to encode %d bytes, in GF256 %d symbols, in GF16 %d \n",len,len,2*len);

        rs_init();

        if ((encoded = (uint8_t *)calloc(rs_conf.n, sizeof(uint8_t))) == NULL) {
                printf("ERROR : Can't create generator polynomial \n");
                return -1;
        }


        rs_encode(symbols, encoded);

        printf("Original msg: ");
        for ( i = 0; i < rs_conf.k; i++)
                printf(" %x ", symbols[i]);

        printf("\n");

        printf("Encoded msg: ");

        for ( i = 0; i < rs_conf.n; i++) {
                if ( i >= rs_conf.n - rs_conf.k)
                        encoded[i] = symbols[i - (rs_conf.n - rs_conf.k)];

                        printf("%x ", encoded[i]);

        }

        printf("\n");

        rs_decode(encoded, decoded);

        return 0;
}
