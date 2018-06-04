#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "param_validation.h"
     
bool valid_adress(char* argument){
    int segments = 1;
    int curr_numb = 0;
    int flag = 0; //0 if previous character was a dot, 1 if number
    int number_streak = 0;
    int current_number = 0;
    int value = 0;
    int len = strlen(argument);
    for(int i = 0; i < len; i++){
        if(argument[i] == '.'){
            if(flag == 0)
                return false;
            flag = 0;
            segments++;
            if(segments > 4)
                return false;
            number_streak = 0;
            if(value >=256)
                return false;
            value = 0;
        }
        else if(argument[i] >= '0' && argument[i] <= '9'){
            flag = 1;
            number_streak++;
            if(number_streak >= 4)
                return false;
            current_number = argument[i] - '0';
            if(current_number == 0 && number_streak >= 2 && value == 0)
                return false;
            value = 10 * value + current_number;
        }
        else
            return false;
    }
    if(flag == 0)
        return false;
    if(segments != 4)
        return false;
    if(value >=256)
        return false;       
    return (segments==4);
}

char* valid_a(int iter, int argc, char *argv[]){
    if(iter + 1 >= argc){
        fprintf(stderr, "MCAST_ADDR param does not exist\n");
        return NULL;
    }
    else if(valid_adress(argv[iter + 1])){
        return argv[iter + 1];
    }
    else{
        fprintf(stderr, "MCAST_ADDR param is incorrect\n");
        return NULL;
    }
}

//FLAG STANDS FOR 0 - PORT ADDRES  1 - BYTES SIZE
char* valid_number(int iter, int argc, char *argv[], int flag){
    if(iter + 1 >= argc){
        fprintf(stderr, "Port number does not exist\n");
        return NULL;
     }
    else{
        long long int sum = 0;
        int curr = 0;
        for(int i = 0; i < strlen(argv[iter + 1]); i++){
            if(argv[iter + 1][i] >= '0' && argv[iter + 1][i] <= '9'){
                curr = argv[iter + 1][i] - '0';
                if(i == 1 && sum == 0 && curr == 0){
                    fprintf(stderr, "Port number is incorrect\n");
                    return NULL;   
                }
                sum += sum * 10 + curr;
                if(sum >= 65536 && !flag){
                    fprintf(stderr, "Port number is greather than 65536\n");
                    return NULL;   
                }
            }
            else{
                fprintf(stderr, "Port number is incorrect\n");
                return NULL;
            }
        }
    }
    return argv[iter + 1];    
}

static bool exist_repeted_element(char *used_params, unsigned int number_of_used){
    for(int i = 0; i <= number_of_used; i++){
        for(int j = i + 1; j <= number_of_used; j++){
            if(used_params[i] == used_params[j])
                return true;
        } 
    }
    return false;
}

static void failed_arg(struct params_s *params, char* messege, int *a, int b){
    if (b != 0)
        *a = b;
    (*params).valid = false;
    fprintf(stderr, "%s", messege);
}


static bool check_elements(char *used_params, unsigned int *number_of_used, char p){
    used_params[*number_of_used] = p;
    (*number_of_used)++;
    return exist_repeted_element(used_params, *number_of_used - 1);
}

static char* name_validation(int *iter, int argc, char *argv[]){
    bool name_loading = true;
    if(*iter + 1 >= argc)
        return NULL;
    else{
        (*iter)++;
        while(*iter < argc && name_loading){
            /*
                CODE
            /*
            (*iter)++; 
        }
    }
    return NULL;
}


void arg_setting_up(int argc, char *argv[], struct params_s *params){
    char used_params[6];
    unsigned int number_of_used = 0;
    if(argc <= 2)
        failed_arg(params, "Number of arguments is to low!", 0, 0);
    else{
        int i = 1;
        char p;
        char *copy_number;
        bool was_a = false;
        bool previous_d = false;
        while(i < argc){
            if(argv[i][0] == '-'){
                if(strlen(argv[i]) != 2)
                    failed_arg(params, "Wrong argument!\n", &i, argc);
                else{
                    if(i + 1 >= argc)
                        failed_arg(params, "Argument has no value!\n", &i, argc);
                    else{    
                        switch(argv[i][1]){
                            case 'a':
                                p = 'a';
                                was_a = true;
                                (*params).MCAST_ADDR = valid_a(i, argc, argv);
                                if((*params).MCAST_ADDR == NULL)
                                     failed_arg(params, "", &i, argc);                            
                                break;
                            case 'P':
                                p = 'P';
                                copy_number = valid_number(i, argc, argv, 0);
                                if(copy_number == NULL)
                                     failed_arg(params, "Check DATA_PORT\n", &i, argc);
                                else
                                    (*params).DATA_PORT = atoi(copy_number);
                                break;
                            case 'C':
                                p = 'C';
                                copy_number = valid_number(i, argc, argv, 0);
                                if(copy_number == NULL)
                                     failed_arg(params, "Check CTRL_PORT\n", &i, argc);
                                else
                                    (*params).CTRL_PORT = atoi(copy_number);
                                break;
                            case 'p':
                                p = 'p';
                                copy_number = valid_number(i, argc, argv, 1);
                                if(copy_number == NULL)
                                     failed_arg(params, "Check PSIZE\n", &i, argc);
                                else
                                    (*params).PSIZE = atoi(copy_number);
                                break;
                            case 'f':
                                p = 'f';
                                copy_number = valid_number(i, argc, argv, 1);
                                if(copy_number == NULL)
                                     failed_arg(params, "Check FSIZE\n", &i, argc);
                                else
                                    (*params).FSIZE = atoi(copy_number);
                                break;
                            case 'n':
                                p = 'n';
                                break;                               
                            default:
                                failed_arg(params, "No such parametr avalible!\n", &i, argc);
                                break; 
                        }
                        if(check_elements(used_params, &number_of_used, p) && (*params).valid)
                            failed_arg(params, "Repeted parametr!\n", &i, argc);
                    }
                }
            }
            i++;
        }
    }
}
/*
void arg_setting_up(int argc, char *argv[]){
    char used_params[6];
    unsigned int number_of_used = 0;
    if(argc <= 2){
        fprintf(stderr, "Number of arguments is to low!\n");
        failed = true;
    }else{
        int i = 1;
        bool was_a = false;
        bool previous_d = false;
        while(i < argc){
            if(argv[i][0] == '-'){
                if(strlen(argv[i]) != 2){
                    fprintf(stderr, "Wrong argument!\n");
                }else{
                    switch(argv[i][1]){
                        case 'a':
                            //printf("a\n");
                            was_a = true;
                            break;                        
                        default:
                            fprintf(stderr, "No such param avalible\n");
                            i = argc;
                            failed = true;
                            break; 
                    }                
                }
            }
            i++;
        }
    }
}
*/
