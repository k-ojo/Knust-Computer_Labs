#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t counter = 0;
void *increment(){
    for (int i = 0; i < 10000000000; i++){
        counter++;
    }
    return NULL;
}

int main(){

    pthread_t t1, t2;
    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return (0);
}