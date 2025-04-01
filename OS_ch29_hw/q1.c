#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main() {
  struct timeval start, end;
  
  gettimeofday(&start, NULL);
  usleep(1000000);
  gettimeofday(&end, NULL);
  
  double sec = (end.tv_sec - start.tv_sec) + (double)(end.tv_usec - start.tv_usec)  / 1000000;
  printf("The code ran for %f seconds. \n", sec);

  return 0;
}
