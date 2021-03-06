#ifndef __WR_RS_H__
#define __WR_RS_H__
#include <stdint.h>
#include <galois.h>
#include <poly_op.h>

struct reed_solomon_conf {
        uint16_t n;
        uint16_t k;
        uint16_t m;
        uint16_t n_k;
};

extern struct reed_solomon_conf rs_conf;
extern struct reed_solomon_op rs_op;
extern struct polynomial_op poly_op;

extern rs_poly gen_poly;
extern rs_poly synd;

int8_t rs_init();
void   rs_close();
int8_t rs_encode(rs_poly *src_symbols, rs_poly *enc_symbols);
int8_t rs_decode(rs_poly *encoded_data, rs_poly *decoded_data, rs_poly *miss_poly);
int8_t rs_erase(rs_poly *enc_symbols, rs_poly *synd, rs_poly *miss_poly);
void   rs_calc_sydrom(rs_poly *enc_symbols);

#endif
