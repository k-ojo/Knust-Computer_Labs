#ifndef _SERVER_H
#define _SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdint.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>
#include <stdbool.h>

#define LOG_FILE "server.log"
#define TRUE 1

typedef struct _server{

    int clients[FD_SETSIZE];
    fd_set fr, fw, fe;
    struct timeval timeout;

    struct sockaddr_in address;
    struct sockaddr_in c_address;

    int service;
    int protocol;
    int backlog;
    int sockfd;
    uint32_t n_of_clients;

    uint32_t interface;
    uint16_t domain;
    uint16_t port;

}server_t;

#endif