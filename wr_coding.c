#include "wr_coding.h"

struct wr_fec_opt fec_opt= {
        .fec_type = 0,
        .rate = 0,
        .number = 1,
        .payl_l = 0,
        .conf_f = ""
};

int main(int argc, char **argv) {

        void    *eth_payload = NULL;
        void    **encoded_data = NULL;
        uint8_t i;

        if(cmd_arg(&fec_opt,argc, argv) < 0)
                return -1;

        printf("WR FEC running: \n\t FEC \t\t %d \n\t Rate \t\t %d \n\t Number \t %d \n\t length \t %d \n",
                fec_opt.fec_type, fec_opt.rate, fec_opt.number, fec_opt.payl_l);

        printf("Creating packet %d bytes payload: \n", fec_opt.payl_l);

        if((eth_payload = create_payload(&fec_opt)) == NULL)
                return -1;

        if((encoded_data = init_encoded_data(&fec_opt)) == NULL)
                return -1;

        dump_pl(eth_payload, fec_opt.payl_l);

        if(init_encoder(&fec_opt) < 0)
                return -1;

        for ( i = 0; i < fec_opt.number ; i++ ) {
                if(create_redundant_payload(eth_payload, encoded_data[i], &fec_opt) < 0)
                        return -1;

        }

        destroy_payload(eth_payload);
        destroy_encoded_data(encoded_data, &fec_opt);

        return 0;
}

