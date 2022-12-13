#include "../include/parser.h"
    
char *strrev(char *str){
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}

// --------------- ARGUMENT PARSER -----------------
int argParser(struct Args *args, char *arg){
        
      printf("parsing arguments\n");
            
      // ------ check if input is valid
      regex_t regex;
      int comp_status;
      comp_status = regcomp(&regex,"123",0);
      if(comp_status!=0){
            printf("regular expression compilation error\n");
            return -1;
      }
      
      int argument_valid;
      argument_valid = regexec(&regex, "123", 0, NULL, 0);
      if(argument_valid!=0){
            printf("Incorrect input format\n");
            return -1;
      }

      // ------ if input does not have login info

      comp_status = regcomp(&regex,"^(ftp:/)?/?([^:/ @]+)/([^: @]+)$",0);
      if(comp_status!=0){
            printf("regular expression compilation error\n");
            return -1;
      }
      
      argument_valid = regexec(&regex, arg, 0, NULL, 0);
      if(argument_valid!=0){
            printf("Incorrect input format\n");
            return -1;
      }else{

            sscanf(arg,"ftp://%99[^:/ @]/%99[^: @\n]", args->host, args->path);
            char rev[BUFF_SIZE];
            strcpy(rev, args->path);
            strcpy(rev, strrev(rev));
            sscanf(rev,"%99[^:/ @]/",rev);
            strcpy(rev, strrev(rev));
            strcpy(args->name, rev);
            printf("host = \"%s\"\n", args->host);
            printf("path = \"%s\"\n", args->path);
            printf("name = \"%s\"\n", args->name);

      }

      // ------ if input does not have login info

      comp_status = regcomp(&regex,"^(ftp:/)?/?(([^:/ @]+):([^:/ @]+)@)([^:/ @]+)/([^: @]+)$",0);
      if(comp_status!=0){
            printf("regular expression compilation error\n");
            return -1;
      }
      
      argument_valid = regexec(&regex, arg, 0, NULL, 0);
      if(argument_valid!=0){
            printf("Incorrect input format\n");
            return -1;
      }else{

            sscanf(arg,"ftp://%99[^:/ @]:%99[^:/ @]@%99[^:/ @]/%99[^: @\n]", args->user, args->password, args->host, args->path);
            char rev[BUFF_SIZE];
            strcpy(rev, args->path);
            strcpy(rev, strrev(rev));
            sscanf(rev,"%99[^:/ @]/",rev);
            strcpy(rev, strrev(rev));
            strcpy(args->name, rev);
            printf("user = \"%s\"\n", args->user);
            printf("password = \"%s\"\n", args->password);
            printf("host = \"%s\"\n", args->host);
            printf("path = \"%s\"\n", args->path);
            printf("name = \"%s\"\n", args->name);

      }



    return 0;
}
