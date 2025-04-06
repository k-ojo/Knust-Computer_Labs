#include "server.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

#include <time.h>

server_t *server_init(uint16_t domain, int service, int protocol, uint32_t interface, uint16_t port, int backlog){
        server_t *server = (server_t *)malloc(sizeof(server_t));
        if (server == NULL){
            perror("Failed allocating memory...");
            exit(EXIT_FAILURE);
        }
        server->service = service;
        server->domain = domain;
        server->domain = interface;
        server->port = port;
        server->backlog = backlog;

        server->address.sin_family = domain;
        server->address.sin_port = htons(port);
        server->address.sin_addr.s_addr = htonl(interface);

        server->sockfd = socket(domain, service, protocol);
        if (server->sockfd == 0){
            perror("Failed to connect socket..");
            exit(EXIT_FAILURE);
        }

        server->timeout.tv_sec = 5;
        server->timeout.tv_usec = 0;

        for (int i = 0; i < FD_SETSIZE; i++)
            server->clients[i] = -1;

        server->n_of_clients = 0;

        return server;
}

void rm_client(server_t *server, int i){

    FD_CLR(server->clients[i], &server->fr);
    FD_CLR(server->clients[i], &server->fe);
    FD_CLR(server->clients[i], &server->fw);
    server->clients[i] = -1;
    server->n_of_clients -= 1;
}

int respond(server_t *server, int i){

    int sockfd = server->clients[i];
    char res[] = "HTTP/1.1 200 OK\r\n"
    "Date: Mon, 27 Jul 2019 12:28:53 GMT\r\n"
    "Server: Apache/2.2.34 (Win32)\r\n"
    "Last-Modified: Fri, 4 May 2009 19:15:56 GMT\r\n"
    "Content-Length: 29\r\n"
    "Content-Type: text/html\r\n"
    "Connection: Closed\r\n"
    "\r\n"
    "<html><body><h1>Gavivi</h1></body></html>";

    if (send(sockfd, res, strlen(res), MSG_NOSIGNAL) == -1 ){
        if (errno == EPIPE || errno == ECONNRESET){
            close(sockfd);
            server->clients[i] = -1;
            server->n_of_clients -= 1;
        }
        else
            perror("send()");
        return -1;
    }
    return 0;
}

char *handle_read(server_t *server, int i){
    char buf[1024];
    int sockfd = server->clients[i];
    ssize_t len = recv(sockfd, buf, sizeof(buf) - 1, 0);

    if (len < 0){
        perror("recv");
        close(server->clients[i]);
        rm_client(server, i);
        return NULL;
    }

    if (len == 0){
        rm_client(server, i);
        return NULL;
    }

    buf[len] = '\0';

    printf("%s", buf);
    respond(server, i);

    return NULL;
}

int handle_client(server_t *server){

    for (int i = 0; i < FD_SETSIZE; i++){

        if (server->clients[i] <= 0)
            continue;
        if (FD_ISSET(server->clients[i], &server->fr)){
                handle_read(server, i);
        }
    }
    return (0);
}

void event_loop(server_t *server){

    int nRet, max_len = server->sockfd;
    while(TRUE){

        FD_ZERO(&server->fr);

        FD_SET(server->sockfd, &server->fr);

        for (int i = 0; i < FD_SETSIZE; i++){
            int fd = server->clients[i];
            if (fd > 0 && fd != server->sockfd){
                if (fd > max_len)
                    max_len = fd;
                FD_SET(server->clients[i], &server->fr);
            }
        }

        nRet = select(max_len + 1, &server->fr, &server->fw, &server->fe, &server->timeout);
        
        if (nRet > 0)
        {
            if (FD_ISSET(server->sockfd, &server->fr)){
                socklen_t len = sizeof(server->c_address);
                int new_sock = accept(server->sockfd, (struct sockaddr *)&server->c_address, &len);
                if (new_sock < 0) {
                    perror("Accept failed");
                    exit(EXIT_FAILURE);
                }

                for (int i = 0; i < FD_SETSIZE; i++){
                    if (server->clients[i] == -1){
                        server->clients[i] = new_sock;
                        server->n_of_clients += 1;
                    }
                }
            }
            handle_client(server);
        }

        else if (nRet == 0)
            continue;//printf("No socket ready...\n");
        else{
            perror("Select()\n");
            exit(EXIT_FAILURE);
        }
    }
}

void start_server(server_t *server){

    if (bind(server->sockfd, (struct sockaddr *)&server->address, sizeof(server->address)) < 0){
        perror("Failed to bind socket...");
        exit(EXIT_FAILURE);
    }

    if(listen(server->sockfd, server->backlog) < 0){
        perror("Failed to start listening...");
    }
    printf("Server is listening on port 8080\n");
}

int main() {    

    server_t *server = server_init(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8080, 10);
    start_server(server);
    event_loop(server);
    printf("break\n");
    free(server);

    return 0;
}
