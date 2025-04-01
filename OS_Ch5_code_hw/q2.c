#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int) getpid());
    FILE* fptr;
    fptr = fopen("t.txt","w");
    if (fptr == NULL) {
        printf("file failed to open\n");
        exit(0);
    }
    else{
	    printf("the file was succesfully created\n");
    }
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
	if (fptr == NULL) {
        	printf("file failed to open in child\n");
    	}
    	else{
            printf("the file was succesfully created in child\n");
	    fputs("cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc\n",fptr);
    	}

    } else {
        // parent goes down this path (original process)
        //int wc = wait(NULL);
        //printf("hello, I am parent of %d (wc:%d) (pid:%d)\n",
	//       rc, wc, (int) getpid());
	if (fptr == NULL) {
        	printf("file failed to open in parent\n");
    	}
    	else{
            printf("the file was succesfully created in parent\n");
	    fputs("pppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppppp\n",fptr);
    	}

    }
    fclose(fptr);
    return 0;
}
