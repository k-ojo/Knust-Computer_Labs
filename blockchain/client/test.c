#include "test.h"

int main(void){

    int sock = 0;

    struct sockaddr_in serv_addr;
    char *msg = "Hello Server";

    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "172.18.0.2", &serv_addr.sin_addr);

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1){ 
        printf("Break\n");
        return (-1);
    }
    
    printf("%d\n", sock);
    send(sock, msg, strlen(msg), 0);
    printf("Done\n");

    return (0);

}