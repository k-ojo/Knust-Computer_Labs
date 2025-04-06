#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdint.h>
#include <semaphore.h>
#include <syslog.h>

uint64_t counter = 0;
pthread_mutex_t lock;
pthread_spinlock_t spinlock;
sem_t semaphore;


void *increment(){
    for (size_t i = 0; i < 10; i++){
        //pthread_mutex_lock(&lock);
        pthread_spin_lock(&spinlock);
        //sem_wait(&semaphore);
        printf("Self: %lu\n", pthread_self());
        counter++;
        //pthread_mutex_unlock(&lock);
        pthread_spin_unlock(&spinlock);
        //sem_post(&semaphore);
    }
    return NULL;
}

int main(){

    int policy;
    struct sched_param param;
    FILE *fd = stdout;

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setschedpolicy(&attr, SCHED_RR); 

    pthread_attr_getschedpolicy(&attr, &policy);
    param.sched_priority = 0x5;

    pthread_attr_setschedparam(&attr, &param);

    pthread_t t1, t2;
    pthread_spin_init(&spinlock, 0);
    //sem_init(&semaphore, 0, 1);
    //pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, &attr, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    //pthread_mutex_destroy(&lock);
    pthread_spin_destroy(&spinlock);
    //sem_destroy(&semaphore);
    return (0);
}