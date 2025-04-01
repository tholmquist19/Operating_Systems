#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[]) {

    int mem = atoi(argv[1]); 
    int *arr = malloc(mem * (1024 * 1024));
    int pid = getpid(); 
    printf("%d\n",pid);

    if (arr == NULL) {
        perror("Memory allocation failed");
        return 1;
    }

    size_t size = mem * (1024 * 1024) / sizeof(int);
    time_t timer_end = 0;
    if (argc == 3) {
        int rt_sec = atoi(argv[2]);
        timer_end = time(NULL) + rt_sec;
    }

    while (argc == 3 ? time(NULL) < timer_end : 1) {
        for (size_t i = 0; i < size; i++) {
	    //printf("%d", arr[i]);
            arr[i]++;
        }
        usleep(1000);
    }
    free(arr);
    return 0;
}

