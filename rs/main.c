#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

#include "rs.h"

struct reed_solomon_conf rs_conf;

int main(int argc, char **argv) {

        int8_t c;
        uint8_t i=0,j;
        uint16_t k, n, N;
        uint8_t m;
        uint8_t *puffy;
        uint8_t *symbols;
        uint8_t *encoded = NULL;
        uint8_t *decoded = NULL;
        uint16_t len;

        if(argc < 2) {
                printf("Usage: %s [OPTION..] STRING_TO_ENCODE \n",argv[0]);

                printf("\n");
                printf("OPTIONS:\n");
                printf("-k, \t\t Length message in Symbols \n");
                printf("-n, \t\t Redundant Symbols \n");
                printf("-m, \t\t Galois Filed index GF(2^m), 4 or 8 \n");
                printf("-s, \t\t String\n");
                return 0;
        }

        while ((c = getopt (argc, argv, "k:n:s:m:")) != -1) {
                switch (c) {
                        case 'k' :
                                rs_conf.k = atoi(optarg);
                                break;
                        case 'n' :
                                rs_conf.n = atoi(optarg);
                                break;
                        case 'm' :
                                rs_conf.m = atoi(optarg);
                                if( rs_conf.m != 4 && rs_conf.m != 8) {
                                        printf("GF(2^m) has to be 4 or 8 \n");
                                        return -1;
                                }
                                break;
                        case 's' :
                                len = 11;

                                if ((symbols = (uint8_t *)calloc(len, sizeof(uint8_t))) == NULL) {
                                        printf("ERROR : Can't create generator polynomial \n");
                                        return -1;
                                }

                                for (j = 0; j < len; j++)
                                        //symbols[j] = j+1;
                                        symbols[j] = len - j;
                                break;
                }
        }

        printf("Length string to encode %d bytes, in GF256 %d symbols, in GF16 %d \n",len,len,2*len);

        for (i = 0; i < len ; i++)
               printf("%d ", symbols[i]);

        rs_init();

        rs_encode((void *)symbols, (void *)encoded);

        //printf("Original msg %s -- redundan symbols %s \n", puffy, encoded);

        rs_decode((void *)encoded, (void *)decoded);

        return 0;
}
