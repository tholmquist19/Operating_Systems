#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "common_threads.h"

sem_t s; 

void *child(void *arg) {
    printf("child\n");
    sleep(1);
    printf("child finished\n");
    // use semaphore here
    sem_post(&s);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    printf("parent: begin\n");
    // init semaphore here
    sem_init(&s, 0, 0);
    Pthread_create(&p, NULL, child, NULL);
    // use semaphore here
    sem_wait(&s);
    sem_destroy(&s);
    
    printf("parent: end\n");
    return 0;
}

