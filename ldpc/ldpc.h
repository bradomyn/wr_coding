#ifndef __WR_LDPC_H__
#define __WR_LDPC_H__

int8_t ldpc_init(struct wr_fec_opt *fec_opt);
int8_t ldpc_encode(void *eth_payload, void *encoded_data, struct wr_fec_opt *fec_opt);
int8_t ldpc_matrix_init();

#endif

