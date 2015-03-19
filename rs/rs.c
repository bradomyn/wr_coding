#include "rs.h"

struct  field_db db;
struct reed_solomon_op rs_op;

int8_t rs_init(uint8_t m) {

        create_gf_db(&db, 0);

        // if ( m == 4 ) --> GF(16)
        rs_op.sum = gsum;
        rs_op.mult = gmult_fast;
        rs_op.div = gdiv_fast;

        return 0;
}

int8_t rs_encode(void *eth_payload, void *encoded_data, uint16_t *n) {



        return 0;
}

int8_t rs_decode(void *encoded_data, void *decoded_data) {



        return 0;
}
