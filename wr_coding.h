#ifndef __WR_FEC_H__
#define __WR_FEC_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>

#define N_BYTES 4

#ifdef VERBO_PRINT
#define VERBO(...) do{ fprintf( stderr, __VA_ARGS__ ); } while( 0 )
#else
#define VERBO(...) do{ } while ( 0 )
#endif

enum fec_type{ LDPC=0, REED_SOLOMON, LT };

struct wr_fec_opt {
        uint16_t fec_type;
        uint16_t rate;
        uint16_t payl_l;
        uint16_t number;
        uint8_t conf_f[100];
};

int8_t cmd_arg(struct wr_fec_opt *fec_opt, int argc, char **argv);
void* create_payload(struct wr_fec_opt *fec_opt);
void** init_encoded_data(struct wr_fec_opt *fec_opt);
void destroy_payload(void *buf);
void destroy_encoded_data(void **buf, struct wr_fec_opt *fec_opt);
void dump_pl(void *buf, uint16_t payl_l);
int8_t create_redundant_payload(void *eth_payload, void *redundant_payload, struct wr_fec_opt *fec_opt);
int8_t init_encoder(struct wr_fec_opt *fec_opt);

#endif
