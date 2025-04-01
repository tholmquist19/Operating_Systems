#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <x86intrin.h>

#define NUMCPUS (8) // how many threads to start
#define INCREMENTS  (1000000) // how many times each thread will increment counter
#define EXPECTED (NUMCPUS * INCREMENTS)

typedef struct __counter_t {
    int             global;         // global count
    pthread_mutex_t glock;          // global lock
    int             local[NUMCPUS]; // per-CPU count
    int             threshold;
} counter_t;

pthread_t thread[NUMCPUS];

counter_t counter;

void init(counter_t *c, int threshold) {
    c->global = 0;
    c->threshold = threshold;
    pthread_mutex_init(&c->glock, NULL);
    int i;
    for (i = 0; i < NUMCPUS; i++) {
        c->local[i] = 0;
    }
}

void increment(counter_t *c, int threadID) {
    c->local[threadID]++;
    if (c->local[threadID] >= c->threshold) {
        pthread_mutex_lock(&c->glock);
        c->global += c->local[threadID];
        pthread_mutex_unlock(&c->glock);
        c->local[threadID] = 0;
    }
}

int get(counter_t *c) {
    pthread_mutex_lock(&c->glock);
    const int rc = c->global;
    pthread_mutex_unlock(&c->glock);
    return rc;
}

void *thread_start_routine(void * arg){
    const int my_threadID = (int)(long)arg;
    int i;
    for (i = 0; i < INCREMENTS; i++) {
        increment(&counter, my_threadID);
    }
    return NULL;
}

int main(int argc, char *argv[]) {

    const int threshold = atoi(argv[1]);

    init(&counter, threshold);

    const unsigned long start = __builtin_ia32_rdtsc();
    int i;
    for (i = 0; i < NUMCPUS; i++) {
        pthread_create(&thread[i], NULL, thread_start_routine, (void *)(long)i);
    }

    for (i = 0; i < NUMCPUS; i++) {
        pthread_join(thread[i], NULL);
    }
    const unsigned long end = __builtin_ia32_rdtsc();

    printf("Counter at end: %d\n", get(&counter));
    printf("Expected %d:\n", EXPECTED);
    printf("Took %lu clocks.\n", end - start);

    return 0;
}
