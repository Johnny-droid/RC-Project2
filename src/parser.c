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

    sscanf(arg,"ftp://[%99[^:/ @]:%99[^:/ @]@]%99[^:/ @]/%99[^: @\n]", args->user, args->password, args->host, args->path);
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


    return 0;
}
