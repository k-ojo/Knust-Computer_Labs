#include <stdio.h>
#include <pthread.h>

void *thread_func(){
    printf("Hello from thread%ld\n", pthread_self());
    return NULL;
}

int main(){
    pthread_t thread;
    pthread_create(&thread, NULL, thread_func, NULL);
    pthread_join(thread, NULL);
    return (0);
}