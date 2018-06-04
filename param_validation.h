#ifndef _PARAM_VALIDATION_
#define _PARAM_VALIDATION_

typedef int bool;
#define true 1
#define false 0

#define student_id 790

struct params_s{
    char *MCAST_ADDR;
    unsigned int DATA_PORT;
    unsigned int CTRL_PORT;
    unsigned long int PSIZE;
    unsigned long int FSIZE;
    char *NAZWA;
    bool valid;
};

extern bool valid_adress(char *argument);

extern void arg_setting_up(int argc, char *argv[], struct params_s *params);

extern char* valid_a(int iter, int argc, char *argv[]);

extern char* valid_number(int iter, int argc, char *argv[], int flag);




#endif //_PARAM_VALIDATION_
