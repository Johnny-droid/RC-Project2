#include <stdio.h>   
#include <stdlib.h> 
#include <string.h>  
#include <regex.h>
#include "../include/macros.h"

struct Args
{
    char user[BUFF_SIZE];
    char password[BUFF_SIZE];
    char host[BUFF_SIZE]; 
    char path[BUFF_SIZE];
    char name[BUFF_SIZE];
};

 char *strrev(char *str);
 int argParser(struct Args *args, char *arg);
