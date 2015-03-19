#include "gf.h"

uint8_t gsum(uint8_t a, uint8_t b) {
        return a ^ b;
}

uint8_t gmult(uint8_t a, uint8_t b) {
        uint8_t prod = 0;
        uint8_t c,h;

         for (c = 0; c < 8; c++)
            {
              if ((b & 1) == 1)
                prod ^= a;
              h = (a & 0x80);
              a <<= 1;
              if (h == 0x80)
                a ^= 0x1b;
              b >>= 1;
            }

        return prod;
}

uint8_t gmult_fast(uint8_t a, uint8_t b, struct field_db *gf_db) {

        return gf_db->exp[gf_db->log[a] + gf_db->log[b]];
}

uint8_t gdiv_fast(uint8_t a, uint8_t b,struct field_db *gf_db) {

        return gf_db->exp[gf_db->log[a] - gf_db->log[b]];
}

void create_gf_db(struct field_db *gf_db, uint8_t debug) {

        uint8_t x = 1;
        uint16_t i;
        //uint8_t alpha = 0xFF;
        uint8_t alpha = 0x03;

        memset (&gf_db->exp, 0x0, sizeof(gf_db->exp));
        memset (&gf_db->log, 0x0, sizeof(gf_db->log));

        for (i = 0; i < 256; i++) {
                if (i == 0) {
                        gf_db->exp[i] = 0x01;
                } else {
                        x = gf_db->exp[i] = gmult(alpha, x);
                        gf_db->exp[i] = x;
                }
        }

        for (i = 0; i < 256; i++)
                gf_db->log[gf_db->exp[i]] = i;

        if (debug == 1) {

                for(i=0; i<256; i++) {
                        if((i%8 == 0) && (i != 0) )
                                printf("\n");

                        printf("0x%02x ", gf_db->exp[i]);
                }

                printf("\n");
                printf("\n");

                for(i=0; i<256; i++) {
                        if((i%8 == 0) && (i != 0) )
                                printf("\n");

                        printf("0x%02x ", gf_db->log[i]);
                }
        }

}
