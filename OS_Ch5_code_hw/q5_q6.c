#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int) getpid());
    pid_t rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
	int wc2 = wait(NULL);
	printf("return from child wait is %d\n",wc2);
        printf("hello, I am child (pid:%d)\n", (int) getpid());
	sleep(1);
    } else {
        // parent goes down this path (original process)
        //int wc = wait(NULL);
	int stat;
        pid_t res = waitpid(rc, &stat, 0);
        if (res == -1) {
            perror("waitpid failed");
            exit(EXIT_FAILURE);
        }
	printf("Hello I am parent of %d my pid is %d\n",rc, (int)getpid());
        //printf("hello, I am parent of %d (wc:%d) (pid:%d)\n",
	//       rc, wc, (int) getpid());
    }
    return 0;
}
