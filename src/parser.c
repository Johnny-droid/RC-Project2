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

 //           if(sscanf(arg,"ftp://%99[^:/ @]/%99[^: @\n]", args->host, args->path)!=)

// --------------- ARGUMENT PARSER -----------------
int argParser(struct Args *args, char *arg){
        
      printf("parsing arguments\n");

      if(sscanf(arg,"ftp://%99[^:/ @]:%99[^:/ @]@%99[^:/ @]/%99[^: @\n]", args->user, args->password, args->host, args->path)==4){

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

      }else if(sscanf(arg,"ftp://%99[^:/ @]/%99[^: @\n]", args->host, args->path)==2){

            char rev[BUFF_SIZE];
            strcpy(rev, args->path);
            strcpy(rev, strrev(rev));
            sscanf(rev,"%99[^:/ @]/",rev);
            strcpy(rev, strrev(rev));
            strcpy(args->name, rev);
            strcpy(args->user, DEFAULT_USER);
            strcpy(args->password, DEFAULT_PASS);
            printf("user = \"%s\"\n", args->user);
            printf("password = \"%s\"\n", args->password);
            printf("host = \"%s\"\n", args->host);
            printf("path = \"%s\"\n", args->path);
            printf("name = \"%s\"\n", args->name);
            

      }else{
            printf("Incorrect input format\n");
            return -1;
      }

    return 0;
}
