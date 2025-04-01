#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define NUMCPUS (8) // how many threads to start
#define INSERTS (1000) // each thread does this many inserts + lookups

typedef struct __node_t {
    int              key;
    struct __node_t  *next;
} node_t;

typedef struct __list_t {
    node_t              *head;
    pthread_mutex_t    lock;
} list_t;

pthread_t thread[NUMCPUS];

list_t  list;

void init(list_t *l) {
    l->head = NULL;
    pthread_mutex_init(&l->lock, NULL);
}

int insert(list_t *l, int key) {
    pthread_mutex_lock(&l->lock);
    node_t *new = malloc(sizeof(node_t));
    int res = -1;
    if (new == NULL) {
        perror("malloc");
        goto out;
    }
    new->key = key;
    new->next = l->head;
    l->head = new;
    res = 0; // success
out:
    pthread_mutex_unlock(&l->lock);
    return res;
}

int lookup(list_t *l, int key) {
    pthread_mutex_lock(&l->lock);
    node_t *curr = l->head;
    while (curr) {
        if (curr->key == key) {
            pthread_mutex_unlock(&l->lock);
            return 0; // success
        }
        curr = curr->next;
    }
    pthread_mutex_unlock(&l->lock);
    return -1; // not found
}

void *thread_start_routine(void * arg) {
    const int my_threadID = (int)(long)arg;
    const int key_offs = my_threadID * INSERTS;

    int i;
    for (i = 0; i < INSERTS; i++) {
        insert(&list, i + key_offs);
    }
    for (i = 0; i < INSERTS; i++) {
        lookup(&list, i + key_offs);
    }
    return NULL;
}

int main(int argc, char *argv[]) {

    const long unsigned t0 = __builtin_ia32_rdtsc();
    int i;
    for (i = 0; i < NUMCPUS; i++) {
        pthread_create(&thread[i], NULL, thread_start_routine, (void *)(long)i);
    }

    for (i = 0; i < NUMCPUS; i++) {
        pthread_join(thread[i], NULL);
    }
    const long unsigned t1 = __builtin_ia32_rdtsc();
    printf("Took %ld clocks.\n", t1 - t0);

    return 0;
}
