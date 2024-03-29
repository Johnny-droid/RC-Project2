#ifndef MACROS_H
#define MACROS_H

#define BUFF_SIZE 10000
#define CMD_MAX_SIZE 10

#define SERVER_PORT_COMMAND 21
#define SERVER_PORT_DATA 20

#define SOCKET_OPEN_DATA_SUCCESS 150
#define SOCKET_SUCCESS 220
#define SOCKET_TRANSFER_COMPLETE 226
#define SOCKET_LOGIN_SUCCESS 230
#define SOCKET_PASSIVE_SUCCESS 227
#define SOCKET_ASK_PASSWORD 331


#define CMD_USER "user "
#define CMD_PASSWORD "pass "
#define CMD_PASSIVE "pasv "
#define CMD_RETRIEVE "retr "

#define DEFAULT_USER "anonymous"
#define DEFAULT_PASS "password"

#endif
