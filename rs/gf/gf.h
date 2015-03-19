#ifndef __WR_FEC_H__
#define __WR_FEC_H__

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#define POLY 0x11B

struct field_db {
        uint8_t log[256];
        uint8_t exp[256];
};

struct reed_solomon_op {
        uint8_t (*sum)(uint8_t a, uint8_t b);
        uint8_t (*mult)(uint8_t a, uint8_t b, struct field_db *gf_db);
        uint8_t (*div)(uint8_t a, uint8_t b, struct field_db *gf_db);
};


enum operation {MULT=0, SUM, DIV};

uint8_t gsum(uint8_t a, uint8_t b);
uint8_t gmult(uint8_t a, uint8_t b);
uint8_t gmult_fast(uint8_t a, uint8_t b,struct field_db *gf_db);
uint8_t gdiv_fast(uint8_t a, uint8_t b,struct field_db *gf_db);
void    create_gf_db(struct field_db *gf_db, uint8_t debug);
#endif
