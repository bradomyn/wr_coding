#ifndef __WR_RS_H__
#define __WR_RS_H__
#include <stdint.h>
#include <galois.h>
#include <genpoly.h>

#include "rs.h"

struct reed_solomon_op {
        uint8_t *(*gen_poly)(uint8_t n, uint8_t alpha, uint8_t k, uint8_t m);
        int (*sum)(int a, int b, int w);
        int (*mult)(int a, int b, int w);
        int (*div)(int a, int b, int w);
};

struct reed_solomon_conf {
        uint16_t n;
        uint16_t k;
        uint16_t m;
};

extern struct reed_solomon_conf rs_conf;

int8_t rs_init();
int8_t rs_encode(uint8_t *eth_payload, uint8_t *encoded_data);
int8_t rs_decode(uint8_t *encoded_data, uint8_t *decoded_data);

#endif
