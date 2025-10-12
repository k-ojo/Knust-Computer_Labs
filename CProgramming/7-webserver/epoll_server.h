#include <stdlib.h>
#include <stdint.h>
#include<sys/epoll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_EVENTS 1024

typedef struct _server{

    struct epoll_event events[MAX_EVENTS];
    struct epoll_event ev;

    struct sockaddr_in conn_addr;
    struct sockaddr_in listen_addr;

    socklen_t addr_size;

    int listen_sock;
    int conn_sock;
    int nfds;
    int epollfd;
    int domain;
    int type;
    int protocol;

}server_t;
