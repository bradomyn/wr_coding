#include "rs.h"

struct field_db db;
struct reed_solomon_op rs_op;
struct reed_solomon_conf rs_conf;

int8_t rs_init(uint8_t m) {

        create_gf_db(&db, 0);

        rs_op.sum  = gsum;
        rs_op.mult = gmult_fast;
        rs_op.div  = gdiv_fast;

        if ((2 << rs_conf.m) < (rs_conf.n + rs_conf.k)) {
                printf("ERROR : RS n+k is bigger than the Close Space of GF\n");
                return -1;
        }

        return 0;
}

int8_t rs_encode(void *eth_payload, void *encoded_data) {

        uint8_t *symbol;
        uint8_t *gen_poly;

        symbol = (uint8_t *)eth_payload;

        if ((gen_poly = (uint8_t *)calloc(rs_conf.n, sizeof(uint8_t))) == NULL) {
                printf("ERROR : Can't create generator polynomial \n");
                return -1;
        }






        return 0;
}

int8_t rs_decode(void *encoded_data, void *decoded_data) {



        return 0;
}
