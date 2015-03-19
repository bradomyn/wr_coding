#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "gf.h"


int main(int argc, char **argv) {
        struct  field_db db;
        int8_t c;
        uint8_t debug;
        uint8_t i=0;
        uint8_t num1, num2, result;
        enum operation oper;

        if(argc < 2) {
                printf("Usage: %s [OPTION..] [OPERATION] num1 num2 \n",argv[0]);

                printf("\n");
                printf("OPTIONS:\n");
                printf("-p, \t\t print Log Exp Table \n");

                printf("\n");
                printf("OPERATIONS:\n");
                printf("-m, \t\t multiplication \n");
                printf("-s, \t\t sum \n");
                printf("-d, \t\t division \n");
                return 0;
        }

        while ((c = getopt (argc, argv, "pm:s:d:")) != -1) {
                switch (c) {
                        case 'p' :
                                oper = 0XFE0;
                                debug = 1;
                                break;
                        case 'm' :
                                oper = MULT;
                                num1 = atoi(argv[i+2]);
                                num2 = atoi(argv[i+3]);
                                break;
                        case 's' :
                                oper = SUM;
                                num1 = atoi(argv[i+2]);
                                num2 = atoi(argv[i+3]);
                                break;
                        case 'd' :
                                oper = DIV;
                                num1 = atoi(argv[i+2]);
                                num2 = atoi(argv[i+3]);
                                break;
                }
                i+=1;
        }

        printf("Galois Field %s \n",strcmp(argv[0],"./gf256") ? "16" : "256");

        create_gf_db(&db, debug);

        switch (oper) {
                case MULT :
                        result = gmult_fast(num1, num2, &db);
                        printf("Multiplication %d x %d = %d", num1, num2, result);
                        break;
                case DIV :
                        result = gdiv_fast(num1, num2, &db);
                        printf("Division %d x %d = %d", num1, num2, num2);
                        break;
                case SUM :
                        result = gsum(num1, num2);
                        printf("Sum %d x %d = %x", num1, num2, num2);
                        break;
        }

        return 0;
}
