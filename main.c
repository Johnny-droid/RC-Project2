#include <stdio.h>
#include "include/macros.h"
#include "include/socket.h"


struct Args
{
    char user[BUFF_SIZE];
    char password[BUFF_SIZE];
    char host[BUFF_SIZE]; 
    char path[BUFF_SIZE];
};


int main(int argc, char **argv) {

    if (argc != 2) {
        printf("use: download ftp://[<user>:<password>@]<host>/<url-path>\n");
    }

    // Instead of this, we need to make a parser
    struct Args args = {
        .user = "anonymous",
        .password = "password",
        .host = "ftp.up.pt",
        .path = "pub/kodi/timestamp.txt"
    };

    struct hostent* h;
    char ip_address[BUFF_SIZE];
    char response[BUFF_SIZE], command[BUFF_SIZE];
    //FILE * socket;
    int sockfd;
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
    
    //  ----------------- OPEN CONNECTION  ----------------- 
    if ((sockfd = openConnection(SERVER_PORT_COMMAND, ip_address)) < 0) {
        perror("Socket 21, used for commands, could not open properly\n");
        return -1;
    };
    

    // Read the response from the server and check if it was successful
    responseCode = readResponse(sockfd, response);
    if (responseCode != SOCKET_SUCCESS) {
        printf("The connection was unsuccessful\n Code returned was: %d\n", responseCode);
        return -1;
    }


    // ----------------- USER COMMAND ----------------- 
    strncpy(command, CMD_USER, CMD_MAX_SIZE); 
    strncat(command, args.user, BUFF_SIZE-CMD_MAX_SIZE-3);
    strcat(command, "\r\n");
    
    if ((bytes = writeCommand(sockfd, command)) < 0) {
        printf("Couldn't write the user");
        return -1;
    }
    
    // Read the response from the server and check if it now asks for a password
    responseCode = readResponse(sockfd, response);
    if (responseCode != SOCKET_ASK_PASSWORD) {
        printf("The connection was unsuccessful \nCould not login \nCode returned was: %d\n", responseCode);
        return -1;
    }



    //  -----------------  PASSWORD COMMAND  ----------------- 
    strncpy(command, CMD_PASSWORD, CMD_MAX_SIZE); 
    strncat(command, args.password, BUFF_SIZE-CMD_MAX_SIZE-3);
    strcat(command, "\r\n");
    
    printf("Command: %s", command);
    if ((bytes = writeCommand(sockfd, command)) < 0) {
        printf("Couldn't write the user");
        return -1;
    }

    // Read the response from the server and check if login was successful
    responseCode = readResponse(sockfd, response);
    if (responseCode != SOCKET_LOGIN_SUCCESS) {
        printf("The connection was unsuccessful \nCould not login \nCode returned was: %d\n", responseCode);
        return -1;
    }



    /*
    char buf[] = "Mensagem de teste na travessia da pilha TCP/IP\n";
    //send a string to the server
    bytes = write(sockfd, buf, strlen(buf));
    if (bytes > 0) {
        printf("Bytes escritos %ld\n", bytes);
        read(sockfd, buf, 40);

    } else {
        perror("write()");
        exit(-1);
    }

    if (close(sockfd)<0) {
        perror("close()");
        exit(-1);
    }

    */
    return 0;
}


