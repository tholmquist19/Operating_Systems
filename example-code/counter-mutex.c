#include <stdio.h>
#include <pthread.h>

#define NUMCPUS (8) // how many threads to start
#define INCREMENTS  (1000000) // how many times each thread will increment counter
#define EXPECTED (NUMCPUS * INCREMENTS)

typedef struct __counter_t {
    int value;
    pthread_mutex_t lock;
} counter_t;

pthread_t thread[NUMCPUS];

counter_t counter;

void init(counter_t *c) {
    c->value = 0;
    pthread_mutex_init(&c->lock, NULL);
}

void increment(counter_t *c) {
    pthread_mutex_lock(&c->lock);
    c->value++;
    pthread_mutex_unlock(&c->lock);
}

int get(counter_t *c) {
    pthread_mutex_lock(&c->lock);
    const int rc = c->value;
    pthread_mutex_unlock(&c->lock);
    return rc;
}

void *thread_start_routine(void * arg){
    int i;
    for (i = 0; i < INCREMENTS; i++) {
        increment(&counter);
    }
    return NULL;
}

int main(int argc, char *argv[]) {

    init(&counter);

    int i;
    for (i = 0; i < NUMCPUS; i++) {
        pthread_create(&thread[i], NULL, thread_start_routine, NULL);
    }

    for (i = 0; i < NUMCPUS; i++) {
        pthread_join(thread[i], NULL);
    }

    printf("Counter at end: %d\n", get(&counter));
    printf("Expected %d:\n", EXPECTED);

    return 0;
}
