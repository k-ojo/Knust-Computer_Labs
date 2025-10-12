#include "epoll_server.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int setnonblocking(int fd){
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) return -1;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

int handle_read(server_t *server, int n){
    char buf[1024];
    for(;;){
        ssize_t bytes = read(server->events[n].data.fd, buf, sizeof(buf));
        if (bytes == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
                break;
            else{
                return EXIT_FAILURE;
            }
        }
        else if (bytes == 0){
                break;
            }
        else{
            printf("%s\n", buf);
        }
    }
    return EXIT_SUCCESS;
}

int respond(server_t *server, int n){

    int sockfd = server->events[n].data.fd;
    handle_read(server, n);

    char res[] = "HTTP/1.1 200 OK\r\n"
    "Date: Mon, 27 Jul 2019 12:28:53 GMT\r\n"
    "Server: Apache/2.2.34 (Win32)\r\n"
    "Last-Modified: Fri, 4 May 2009 19:15:56 GMT\r\n"
    "Content-Length: 39\r\n"
    "Content-Type: text/html\r\n"
    "Connection: Closed\r\n"
    "\r\n"
    "<html><body><h1>Gavivi</h1></body></html>";

    if (send(sockfd, res, strlen(res), MSG_NOSIGNAL) == -1 ){

        if (errno == EPIPE || errno == ECONNRESET){
            epoll_ctl(server->epollfd, EPOLL_CTL_DEL, sockfd, NULL);
            close(sockfd);
        }

        else{
            perror("send()");
            return -1;
        }
        
    }

    epoll_ctl(server->epollfd, EPOLL_CTL_DEL, sockfd, NULL);
    close(sockfd);
   
    return 0;
}

server_t *init_server(int domain, int type, int protocol, uint32_t port){
    server_t *server = (server_t *)malloc(sizeof(server_t));
    server->domain = domain;
    server->type = type;
    server->protocol = protocol;
    server->addr_size = sizeof(server->listen_addr);

    server->listen_addr.sin_family = domain;
    server->listen_addr.sin_addr.s_addr = INADDR_ANY;
    server->listen_addr.sin_port = htons(port);


    server->listen_sock = socket(domain, type, protocol);

    if (server->listen_sock == -1){
        perror("socket: listen_sock");
        free(server);
        exit(EXIT_FAILURE);
    }

    if(bind(server->listen_sock, (struct sockaddr *)&server->listen_addr, server->addr_size) == -1){
        perror("bind");
        free(server);
        exit(EXIT_FAILURE);
    }

    if(listen(server->listen_sock, 10) == -1){
        perror("listen");
        free(server);
        exit(EXIT_FAILURE);
    }
    printf("Started listening...\n");
    return server;
}

int main(void){

    server_t *server = init_server(AF_INET, SOCK_STREAM, 0, 8080);
    server->epollfd = epoll_create1(0);

    if (server->epollfd == -1){
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }

    server->ev.events = EPOLLIN;
    server->ev.data.fd = server->listen_sock;
    if(epoll_ctl(server->epollfd, EPOLL_CTL_ADD, server->listen_sock, &server->ev) == -1){
        perror("epoll_ctl: listen_sock");
        exit(EXIT_FAILURE);
    }

    for (;;){
        server->nfds = epoll_wait(server->epollfd, server->events, MAX_EVENTS, -1); //checking for events on sockets

        if (server->nfds == -1){
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }

        for (int n = 0; n < server->nfds; ++n){
            if (server->events[n].data.fd == server->listen_sock){
                server->conn_sock = accept(server->listen_sock, (struct sockaddr *)&server->conn_addr, &server->addr_size);
                if (server->conn_sock == -1){
                    perror("accept");
                    exit(EXIT_FAILURE);
                }
                setnonblocking(server->conn_sock);
                server->ev.events = EPOLLIN | EPOLLET;
                server->ev.data.fd = server->conn_sock;
                if (epoll_ctl(server->epollfd, EPOLL_CTL_ADD, server->conn_sock, &server->ev) == -1){
                    perror("epoll_ctl: conn_sock");
                    exit(EXIT_FAILURE);
                }
            }
            else{
                printf("Received a request...\n");
                respond(server, n);
            }
        }
    }

    free(server);
    return 0;
    
}