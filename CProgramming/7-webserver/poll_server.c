#include <stdio.h>
#include <poll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>


#define MAX_FDS 5
#define TRUE 1

int respond(struct pollfd *fds, int i, int *n){

    int sockfd = fds[i].fd;
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
            close(sockfd);
            fds[i].fd = -1;
            *n -= 1;
        }

        else
            perror("send()");
        return -1;
    }
   
    return 0;
}

int main(void){

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(client_addr);
    struct pollfd fds[MAX_FDS];
    int n = 0;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(80);

    if (bind(sockfd, (struct sockaddr *)&server_addr, (socklen_t)sizeof(server_addr)) == -1){
        perror("bind:");
        exit(EXIT_FAILURE);
    }


    for (int i = 0; i < MAX_FDS; i++){
        fds[i].fd = -1;
        fds[i].events = POLLIN;
    }

    fds[n].fd = sockfd;
    n++;

    if(listen(sockfd, 10) == -1){
        perror("listen error:");
        exit(EXIT_FAILURE);
    }

    while (TRUE){

        if (poll(fds, MAX_FDS, 100) == 0){
            perror("No data ready:");
            continue;
        }

        for (int i = 0; i < MAX_FDS; i++){
            if (fds[i].fd == -1) continue;
            if (fds[i].fd == sockfd && (POLLIN & fds[i].revents)){
                int new_sock = accept(sockfd, (struct sockaddr *)&client_addr, &addr_size);
                for (int j = 0; j < MAX_FDS; j++){
                    if (fds[j].fd == -1){
                        fds[j].fd = new_sock;
                        break;
                    }
                }
            }
            else if (fds[i].revents & POLLIN){
                respond(fds, i, &n);
            }
        }
    }


    return (0);
}