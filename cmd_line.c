#include "wr_fec.h"

struct cmd_line_arg {
        char *arg;
        char *help;
};

static struct cmd_line_arg cmd_line_list[] = {
        {"-?", "show this page"},
        {"-c FEC", "set the Packet Erasure FEC to use LDPC = 0, Reed Solomon = 1, Raptor = 2"},
        {"-k K  ", "number of symbols to send"},
        {"-n N  ", "rate"},
        {"-l L  ", "lenth of the block"},
        {"-f FILE  ", "configuration file"},
        {NULL, NULL}

};

static void print_help(void){
        int pos = 0;

        printf("\n Usage: wr_ldpc [OPTION]\n\n");

        while (1) {
                struct cmd_line_arg *opt = &cmd_line_list[pos];
                if(opt->arg == NULL)
                        break;
                printf("%s\n\t%s\n", opt->arg, opt->help);
                pos++;
        }
}

static int8_t cmd_file_read(FILE *conf_f,struct wr_fec_opt *fec_opt) {
        char line[100];
        char *pch;

        while( fgets (line, 100, conf_f) != NULL )
        {
                if (line[0] == '#')
                        continue;

                pch = strtok (line,"-");

                while (pch != NULL) {
                        switch (pch[0]) {
                        case 'c':
                                fec_opt ->fec_type = atoi(pch+2);
                                break;
                        case 'k':
                                fec_opt->rate = atoi(pch+2);
                                break;
                        case 'n':
                                fec_opt->number = atoi(pch+2);
                                break;
                        case 'l':
                                fec_opt->payl_l = atoi(pch+2);
                                break;
                        case 'f':
                                printf("Calling a config file, from a config file... \n");
                                return -1;
                        default :
                                break;
                        }
                        pch = strtok (NULL, "-");
                }
        }

        fclose(conf_f);

        return 0;
}

int8_t cmd_arg(struct wr_fec_opt *fec_opt, int argc, char **argv) {

        int8_t i, err = 0;
        char *line_arg;
        FILE *conf_f;


        for (i = 1; i < argc; i++) {
                line_arg = argv[i];
                if(line_arg[0] != '-')
                        err = 1;
                else if(line_arg[1] == '?')
                        err = 1;
                else if(line_arg[1] && line_arg[2])
                        err = 1;
                if (err) {
                        print_help();
                        return -1;
                }

                switch (line_arg[1]) {
                case 'c':
                        fec_opt->fec_type = (uint16_t) strtol(argv[++i],NULL, 10);
                        break;
                case 'k':
                        fec_opt->rate = (uint16_t) strtol(argv[++i],NULL, 10);
                        break;
                case 'n':
                        fec_opt->number = (uint16_t) strtol(argv[++i],NULL, 10);
                        break;
                case 'f':
                        if (argc > 3) {
                                printf("PARSING ERROR : You can't set the flags from command line AND from a file \n");
                                print_help();
                                return -1;
                        }

                        if ( ( conf_f = fopen( argv[++i], "r" )) == NULL) {
                                printf( "PARSING ERROR : Can't open input file \n");
                                return -1;
                        }

                        if(cmd_file_read(conf_f, fec_opt) < 0)
                                return -1;

                        break;
                default :
                        print_help();
                        return -1;
                }
        }

        return 0;

}
