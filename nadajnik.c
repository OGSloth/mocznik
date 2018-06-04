#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "err.h"
#include "param_validation.h"

void params_debug(struct params_s par){
    printf("param MCAST_ADDR = %s\n", par.MCAST_ADDR);
    printf("param DATA_PORT = %d\n", par.DATA_PORT);
    printf("param CTRL_PORT = %d\n", par.CTRL_PORT);
    printf("param PSIZE = %d\n", par.PSIZE);
    printf("param FSIZE = %d\n", par.FSIZE);
    printf("param NAZWA = %s\n", par.NAZWA);
    printf("param validation = %d\n", par.valid);

}

int main(int argc, char *argv[]) {
    struct params_s params_values = {NULL, (20000 + student_id), (30000 + student_id),
         512, 65536 * 2, "Nienazwany Nadajnik", true};
    arg_setting_up(argc, argv, &params_values);
    params_debug(params_values);
 
     /*
    printf("%d\n",valid_adress("12.12.12.12"));
    printf("%d\n",valid_adress(".12.12.12"));
    printf("%d\n",valid_adress("12.250.12.256"));
    printf("%d\n",valid_adress("127.0.1.1"));
    */
    return 0;
    
}
