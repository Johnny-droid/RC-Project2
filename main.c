#include <stdio.h>
#include <regex.h>
#include "include/macros.h"
#include "include/socket.h"


struct Args
{
    char user[BUFF_SIZE];
    char password[BUFF_SIZE];
    char host[BUFF_SIZE]; 
    char path[BUFF_SIZE];
    char name[BUFF_SIZE];
};


int main(int argc, char **argv) {

    if (argc != 2) {
        printf("use: download ftp://[<user>:<password>@]<host>/<url-path>\n");
    }

    // TODO: Instead of this, we need to make a parser
    // All the parser needs to do is take the URL in argv[1], 
    // and separate the information into the args struct
    struct Args args;
    argParser(&args, argv[1]); 

    struct hostent* h;
    char ip_address[BUFF_SIZE];
    char response[BUFF_SIZE], command[BUFF_SIZE];
    //FILE * socket;
    int sockfd, sockfd_data;
    int responseCode;
    int bytes;

    // Get the ip address of the host by name
    if ((h = gethostbyname(args.host)) == NULL) {
        perror("Can't find corresponding IP. gethostbyname() failed");
        return -1;
    }

    // Convert the IP address into a string format
    strncpy(ip_address, inet_ntoa(*((struct in_addr *) h->h_addr)), BUFF_SIZE-1);
    printf("IP %s\n", ip_address);
    fflush(stdout);
    
    //  ----------------- OPEN CONNECTION COMMANDS  ----------------- 
    if ((sockfd = openConnection(SERVER_PORT_COMMAND, ip_address)) < 0) {
        perror("Socket 21, used for commands, could not open properly\n");
        return -1;
    };
    

    // Check if it was successful
    responseCode = readResponse(sockfd, response);
    if (responseCode != SOCKET_SUCCESS) {
        printf("The connection was unsuccessful\n Code returned was: %d\n", responseCode);
        return -1;
    }


    // ------------------- USER COMMAND ------------------- 
    buildCommand(command, CMD_USER, args.user);
    
    if ((bytes = writeCommand(sockfd, command)) < 0) {
        printf("Couldn't write the user");
        return -1;
    }
    
    // Check if it was successful
    responseCode = readResponse(sockfd, response);
    if (responseCode != SOCKET_ASK_PASSWORD) {
        printf("The connection was unsuccessful \nWrong user \nCode returned was: %d\n", responseCode);
        return -1;
    }



    //  -----------------  PASSWORD COMMAND  ----------------- 
    buildCommand(command, CMD_PASSWORD, args.password);
    
    if ((bytes = writeCommand(sockfd, command)) < 0) {
        printf("Couldn't write the password");
        return -1;
    }

    // Check if it was successful
    responseCode = readResponse(sockfd, response);
    if (responseCode != SOCKET_LOGIN_SUCCESS) {
        printf("The connection was unsuccessful \nWrong password \nCode returned was: %d\n", responseCode);
        return -1;
    }


    //  -----------------  PASSIVE COMMAND  ----------------- 
    buildCommand(command, CMD_PASSIVE, "");

    if ((bytes = writeCommand(sockfd, command)) < 0) {
        printf("Couldn't write the passive command");
        return -1;
    }

    // Check if it was successful
    responseCode = readResponse(sockfd, response);
    if (responseCode != SOCKET_PASSIVE_SUCCESS) {
        printf("The connection was unsuccessful \nSomething wrong with passive mode \nCode returned was: %d\n", responseCode);
        return -1;
    }

    int newPort = parsePassiveResponse(response);

    
    //  ----------------- OPEN CONNECTION DATA  ----------------- 
    if ((sockfd_data = openConnection(newPort, ip_address)) < 0) {
        perror("Socket used for data transmission could not open properly\n");
        return -1;
    };


    //  --------------- RETRIEVE FILE COMMAND  ----------------- 
    buildCommand(command, CMD_RETRIEVE, args.path);
    
    if ((bytes = writeCommand(sockfd, command)) < 0) {
        printf("Couldn't write the user");
        return -1;
    }

    // Check if it was successful
    responseCode = readResponse(sockfd, response);
    if (responseCode != SOCKET_OPEN_DATA_SUCCESS) {
        printf("The connection was unsuccessful \nSomething wrong with opening file \nCode returned was: %d\n", responseCode);
        return -1;
    }
    


    //  --------------- DOWNLOAD FILE  ----------------- 
    readDataFile(sockfd_data, args.name);

    // Check if it was successful
    responseCode = readResponse(sockfd, response);
    if (responseCode != SOCKET_TRANSFER_COMPLETE) {
        printf("The transfer was unsuccessful \nCode returned was: %d\n", responseCode);
        return -1;
    }

    return 0;



    // --------------- ARGUMENT PARSER -----------------
    int argParser(struct Args *args, char *arg){
        
        printf("parsing arguments\n");

        sscanf(&arg,"ftp://[%99[^:/ @]:%99[^:/ @]@]%99[^:/ @]/%99[^:/ @\n]", args.user, args.password, args.host, args.path);
        char rev[99] = args.path;
        rev = strrev(rev);
        sscanf(rev,"%99[^:/ @]/",rev);
        rev = strrev(rev);
        args.name = rev;
        printf("user = \"%s\"\n", args.user);
        printf("password = \"%s\"\n", args.password);
        printf("host = \"%s\"\n", args.host);
        printf("path = \"%s\"\n", args.path);
        printf("name = \"%s\"\n", args.name);

    }
}


