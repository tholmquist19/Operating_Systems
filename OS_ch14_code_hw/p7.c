#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    int *arr = (int *)malloc(10 * sizeof(int));
    arr[3]=12;
    printf("%d\n", arr[3]);
    free(&arr[3]);
    return 0;
}
