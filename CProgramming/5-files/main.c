#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


int main(void){
    char buf[1024];

    int fd = open("name.txt", O_RDWR | O_CREAT);
    if (fd == -1){
        perror("Open");
        close(fd);
        exit(EXIT_FAILURE);
    }

    lseek(fd, 6, SEEK_SET);
    lseek(fd, 0, SEEK_SET);

    ssize_t n_of_bytes = read(fd, buf, 1024);
    if (n_of_bytes == -1 ){
        perror("Read");
        exit(EXIT_FAILURE);
    }

    buf[n_of_bytes] = '\0';
    printf("%li\t%s", n_of_bytes, buf);

    close(fd);
    n_of_bytes = read(fd, buf, 1024);
    perror("Error");

    return 0;

}

