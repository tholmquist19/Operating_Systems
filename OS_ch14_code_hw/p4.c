#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[]) {

    int *ptr = (int *)malloc(15 * sizeof(int));
    printf("finished.\n");

    return 0;
}
