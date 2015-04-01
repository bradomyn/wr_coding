#include <rs.h>
//#include <ldpc.h>
#include "wr_coding.h"

void* create_payload(struct wr_fec_opt *fec_opt) {

        uint16_t payl_l;
        void* buf;

        if((buf = (void *)calloc(fec_opt->payl_l/N_BYTES, sizeof(uint32_t))) == NULL) {
                fprintf (stderr, "No memory, calloc failed %s\n",
                         strerror (errno));
        }

        for (payl_l = 0; payl_l < (fec_opt->payl_l/N_BYTES); payl_l++) {
                memset(buf+(payl_l*N_BYTES), (char)(payl_l+1), N_BYTES);
        }

        return buf;
}

void** init_encoded_data(struct wr_fec_opt *fec_opt) {
        uint16_t esi;
        void** buf;

        if((buf = (void **)calloc(fec_opt->number, sizeof(void *))) == NULL) {
                fprintf (stderr, "No memory, calloc failed %s\n",
                         strerror (errno));
        }

        for (esi = 0; esi < fec_opt->number; esi++) {
                if ((buf[esi] = (char *)calloc(fec_opt->payl_l/N_BYTES, sizeof(uint32_t))) == NULL) {
                        fprintf (stderr, "No memory, calloc failed %s\n",
                                 strerror (errno));
                }
        }

        return buf;
}

void destroy_payload(void *buf) {

        free(buf);

}

void destroy_encoded_data(void **buf, struct wr_fec_opt *fec_opt) {
        uint8_t esi;

        for(esi=0; esi < fec_opt->number; esi++) {
                if(buf[esi])
                        free(buf[esi]);
        }

        free(buf);
};


int8_t init_encoder(struct wr_fec_opt *fec_opt) {

        int8_t res;

        switch(fec_opt->fec_type) {
                case LDPC:
                        //res = ldpc_init(fec_opt);
                        break;
                case REED_SOLOMON:
                        //res = rs_init(fec_opt);
                        break;
                case LT:
                        break;
                default:
                        fprintf (stderr, "No FEC define, encoding failed %s\n",
                                strerror (errno));
                        return -1;
        }

        return res;
}

int8_t create_redundant_payload(void *eth_payload, void *encoded_data, struct wr_fec_opt *fec_opt) {

        int8_t res;

        switch(fec_opt->fec_type) {
                case LDPC:
                        //res = ldpc_encode(eth_payload, encoded_data, fec_opt);
                        break;
                case REED_SOLOMON:
                        //res = rs_encode(eth_payload, encoded_data, fec_opt);
                        break;
                case LT:
                        break;
                default:
                        fprintf (stderr, "No FEC define, encoding failed %s\n",
                                strerror (errno));

                        res = -1;
                        return res;
        }

        return res;
}


void dump_pl(void *buf, uint16_t payl_l) {

        uint16_t i;
        uint32_t *ptr;

        ptr = (uint32_t *)buf;
        for (i = 0; i < payl_l/N_BYTES; i++, ptr++) {
                VERBO("%08x ", *ptr);

                if((i%15 == 0) && (i != 0))
                        printf("\n");
        }
        printf("\n");
}
