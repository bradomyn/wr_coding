#ifndef __WR_RS_H__
#define __WR_RS_H__
#include <stdint.h>

#include "gf.h"
#include "rs.h"

extern struct field_db a;
extern struct reed_solomon_op rs_op;

int8_t rs_init(uint8_t m);
int8_t rs_encode(void *eth_payload, void *encoded_data, uint16_t *n);
int8_t rs_decode(void *encoded_data, void *decoded_data);

#endif
