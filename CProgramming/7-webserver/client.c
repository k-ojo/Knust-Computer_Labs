#include <stdio.h>
#include <sys/select.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define TRUE 1

#define MAX_CLIENTS 1024

int clnt_fd[MAX_CLIENTS];


void init_clients(){
    for (int i = 0; i < MAX_CLIENTS; i++){
        clnt_fd[i] = -1;
    }

}

void ProcessTheRequest(int sockfd, fd_set fr){
    if (FD_ISSET(sockfd, &fr)){
        int nLen = sizeof(struct sockaddr);
        int new_sockfd = accept(sockfd, NULL, (socklen_t *)&nLen);
        if (new_sockfd > 0){
            for (int i = 0; i < 5; i++){

            }
        }
    }
}
int main(void){


    int retval;
    fd_set fr, fw, fe;
    struct timeval timeout;

    timeout.tv_sec = 5;
    timeout.tv_usec = 0;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in sever_address;
    sever_address.sin_family = AF_INET;
    sever_address.sin_port = htons(8080);
    sever_address.sin_addr.s_addr = INADDR_ANY;

    if(bind(sockfd, (struct sockaddr *)&sever_address, sizeof(sever_address)) < 0){
        perror("bind()");
        exit(EXIT_FAILURE);
    }

    if(listen(sockfd, 10) < 0 ){
        perror("listen()");
        exit(EXIT_FAILURE);
    }

    int nMaxFd = sockfd;
    int nRet;

    while(TRUE){

        FD_ZERO(&fr);
        FD_ZERO(&fw); 
        FD_ZERO(&fe);

        FD_SET(sockfd, &fr);
        FD_SET(sockfd, &fw);
        FD_SET(sockfd, &fe);

        nRet = select(nMaxFd + 1, &fr, &fw, &fe, &timeout);

        if (nRet > 0){
            printf("Data on port...Processing now...\n");
            if(FD_ISSET(sockfd, &fe))
                printf("There is an exception. Just get away from here\n");
            if (FD_ISSET(sockfd, &fw))
                printf("Ready to write something\n");
            if (FD_ISSET(sockfd, &fr))
                printf("Ready to read.\n");
            break;
        }
        else if (nRet == 0){
            printf("No data available\n");
        }
        else{
            perror("select()");
            exit(EXIT_FAILURE);
        }
    }

    return 0;

}