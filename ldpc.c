#include "wr_fec.h"
#include "ldpc.h"


int8_t ldpc_init(struct wr_fec_opt *fec_opt) {

        return 0;
}

int8_t ldpc_encode(void *eth_payload, void *encoded_data, struct wr_fec_opt *fec_opt) {

        void **matrix_ldpc;

        //ldpc_matrix()

        //calloc

        //create_redundant

        return 0;
}


int8_t ldpc_matrix_init(void **matrix_ldpc, struct wr_fec_opt *fec_opt) {

        uint32_t row;
        uint32_t column;
        uint32_t i;

        row = fec_opt->rate - fec_opt->number;
        column = fec_opt->rate;

        if ((matrix_ldpc = (void**) calloc(row,sizeof(void*))) == NULL) {
                fprintf (stderr, "No memory, calloc failed LDPC matrix %s\n",
                         strerror (errno));
                return -1;
        }

        for (i = 0; i < column; i++) {
                if ((matrix_ldpc[i] = (char *)calloc(row,sizeof(uint32_t))) == NULL) {
                        fprintf (stderr, "No memory, calloc failed LDPC matrix - %d %s\n",
                                i, strerror (errno));
                        return -1;
                }
        }

        return 0;
}

