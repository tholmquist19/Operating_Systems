#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>

int global_counter = 0;
pthread_mutex_t lock;
int itr = 1000000;
#define THRESHOLD 1000

typedef struct{
  int local_count;
  }thread_count;

void* increment(void* arg) {
  thread_count* data = (thread_count*)arg;
  int* local_count = &data->local_count;
  for (int i = 0; i < itr; i++) {
    (*local_count)++;
    if(*local_count >= THRESHOLD){
        pthread_mutex_lock(&lock);
        global_counter += *local_count;
        pthread_mutex_unlock(&lock);
        
        *local_count=0;
    }
  }
  
  pthread_mutex_lock(&lock);
  global_counter += *local_count;
  pthread_mutex_unlock(&lock);
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
        thread_count thread_arg[num_threads];
        global_counter = 0; 

        gettimeofday(&start, NULL);

        for (int i = 0; i < num_threads; i++) {
          thread_arg[i].local_count = 0;
          pthread_create(&threads[i], NULL, increment, &thread_arg[i]);
        }
        
        for (int i = 0; i < num_threads; i++) {
            pthread_join(threads[i], NULL);
        }

        gettimeofday(&end, NULL);

        double elapsed_time = (end.tv_sec - start.tv_sec) + (double)(end.tv_usec - start.tv_usec) / 1000000.0;

        printf("Number of threads: %d\nElapsed time: %f\nCounter: %d\nExpected: %d\n\n", num_threads, elapsed_time, global_counter, itr*num_threads);
    }

    pthread_mutex_destroy(&lock);

    return 0;
}

