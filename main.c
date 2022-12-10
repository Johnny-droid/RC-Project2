#include <stdio.h>
#include "include/macros.h"
#include "include/socket.h"


int main(int argc, char **argv) {

    if (argc > 1)
        printf("**** No arguments needed. They will be ignored. Carrying ON.\n");

    openConnection(SERVER_PORT);

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


