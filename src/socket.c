#include "../include/socket.h"

int openConnection(int port, char* ip_address) {
    int sockfd;
    struct sockaddr_in server_addr;

    /*server address handling*/
    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip_address);    /*32 bit Internet address network byte ordered*/
    server_addr.sin_port = htons(port);        /*server TCP port must be network byte ordered */

    /*open a TCP socket*/
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket()");
        return -1;
    }
    printf("Opened socket\n");

    /*connect to the server*/
    if (connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("connect()");
        return -1;
    }
    printf("Connected to Server\n");

    return sockfd;
}



// Reads the response to the buf and returns the code found
int readResponse(int sockfd, char* response) {
	
    //memset()
    int state = 0, responseCode = -1;
    size_t bytes = 0, total_bytes = 0;
    
    printf("Starting to read response\n");
    fflush(stdout);

    
    char buf[2];
    
    while ((bytes = read(sockfd, buf, 1)) > 0 ) {
        response[total_bytes] = buf[0];
        total_bytes += 1;

        switch (state) {
            case 0:
                if (isdigit(buf[0])) state++;
                break;
            case 1:
                if (isdigit(buf[0])) state++;
                else state = 0;
                break;
            case 2:
                if (isdigit(buf[0])) state++;
                else state = 0;
                break;
            case 3:
                if (buf[0] == ' ') state++;
                else state = 0;
                break;
            case 4:
                if (buf[0] == '\n') state++;
                break;
            default:
                state = 0;
                break;
        }
        
        if (total_bytes > BUFF_SIZE-1 || bytes == 0 || state == 5) break;
    }
    

    response[total_bytes] = '\0';
    printf("Response: %s\n", response);
    sscanf(response, "%d", &responseCode);
    printf("Response Code: %d\n", responseCode);
    

    
    /*
    char* buf;

	//FILE * socket_file = fdopen(sockfd, "r");

	while (getline(&buf, &bytes, socket_file) > 0) {
		strncat(response, buf, bytes - 1);

		if (bytes > 3 && buf[3] == ' ') {
			sscanf(buf, "%d", &responseCode);
			break;
		}
    }
    printf("Response: %s\n", response);
    printf("Response Code: %d\n", responseCode);
    */

    
   

    return responseCode;
}

// Write any command to the socket
int writeCommand(int sockfd, char* command) {

    int bytes = 0;

    printf("Write command: %s\n", command);
    
    //FILE* socket_file = fdopen(sockfd, "w");
    //bytes = (int) fwrite(command, sizeof(char), strlen(command), socket_file);
    
    bytes = write(sockfd, command, strlen(command));

    printf("%d bytes writen\n", bytes);

    printf("After write\n");
    fflush(stdout);

    return bytes;
}


void buildCommand(char* command, char* arg1, char* arg2) {

    strncpy(command, arg1, CMD_MAX_SIZE); 
    strncat(command, arg2, BUFF_SIZE-CMD_MAX_SIZE-3);
    strcat(command, "\r\n");

}


int parsePassiveResponse(char* response) {
    char n1[10]; //n1 is last 
    char n2[10]; // n2 is second last
    int comma_pos1 = 0, comma_pos2 = 0;


    for (int i = strlen(response)-1; i > 0; i--) {
        
        if (response[i] != ',') continue;

        // found the last comma
        if (comma_pos1 == 0) {
            comma_pos1 = i;
        
        // found the second last comma
        } else {
            comma_pos2 = i;
            break;
        }
    }

    /*
    printf("Response length: %d\n", strlen(response));
    printf("Comma1 position: %d\n", comma_pos1);
    printf("Comma2 position: %d\n", comma_pos2);
    */

    strncpy(n1, response+comma_pos1+1, strlen(response)-comma_pos1-5); n1[strlen(response)-comma_pos1-5] = '\0';
    strncpy(n2, response+comma_pos2+1, comma_pos1-comma_pos2-1); n2[comma_pos1-comma_pos2-1] = '\0';

    printf("N1: %s\n", n1);
    printf("N2: %s\n", n2);

    return atoi(n2)*256 + atoi(n1);
}

