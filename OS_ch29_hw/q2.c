#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>

int counter = 0;
pthread_mutex_t lock;
int itr = 1000000;

void* increment(void* arg) {
    for (int i = 0; i < itr; i++) {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_mutex_init(&lock, NULL);

    int thread_counts[] = {1, 2, 4, 8, 16};
    int num_tests = sizeof(thread_counts) / sizeof(thread_counts[0]);
    struct timeval start, end;

    for (int t = 0; t<num_tests; t++) {
        int num_threads = thread_counts[t];
        pthread_t threads[num_threads];
        counter = 0; 

        gettimeofday(&start, NULL);

        for (int i = 0; i < num_threads; i++) {
            pthread_create(&threads[i], NULL, increment, NULL);
        }
        
        for (int i = 0; i < num_threads; i++) {
            pthread_join(threads[i], NULL);
        }

        gettimeofday(&end, NULL);

        double elapsed_time = (end.tv_sec - start.tv_sec) + (double)(end.tv_usec - start.tv_usec) / 1000000.0;

        printf("Number of threads: %d\nElapsed time: %f\nCounter: %d\nExpected: %d\n\n", num_threads, elapsed_time, counter, itr*num_threads);
    }

    pthread_mutex_destroy(&lock);

    return 0;
}

