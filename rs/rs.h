#ifndef __WR_RS_H__
#define __WR_RS_H__
#include <stdint.h>
#include <galois.h>
#include <poly_op.h>

struct reed_solomon_op {
        int (*sum)(int a, int b, int w);
        int (*mult)(int a, int b, int w);
        int (*div)(int a, int b, int w);
        int (*exp)(int a, int w);
        int (*log)(int a, int w);
};

struct reed_solomon_conf {
        uint16_t n;
        uint16_t k;
        uint16_t m;
        uint16_t n_k;
};

extern struct reed_solomon_conf rs_conf;

struct polynomial_op {
        int8_t (*init)(rs_poly *poly, uint8_t degree, uint8_t base, char *str);
        void (*free)(rs_poly *poly);
        void (*dump)(char *str, rs_poly *poly);
        int8_t (*gen_poly)(rs_poly *gen_poly, uint8_t alpha);
        uint8_t (*eval)(rs_poly *poly, uint8_t value);
        int8_t (*mult)(rs_poly *a_poly, rs_poly *b_poly, rs_poly *mult_poly);
};

extern struct polynomial_op poly_op;

extern rs_poly gen_poly;
extern rs_poly synd;

int8_t rs_init();
int8_t rs_encode(rs_poly *src_symbols, rs_poly *enc_symbols);
int8_t rs_decode(rs_poly *encoded_data, rs_poly *decoded_data, rs_poly *miss_poly);
int8_t rs_erase(rs_poly *enc_symbols, rs_poly *synd, rs_poly *miss_poly);
void   rs_calc_sydrom(rs_poly *enc_symbols);

#endif
