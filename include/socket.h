#include <stdio.h>
#include <sys/socket.h>
#include <ctype.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "macros.h"


int openConnection(int port, char* ip_address);
int readResponse(int sockfd, char* response);
int writeCommand(int sockfd, char* command);


