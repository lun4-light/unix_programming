#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    pid_t pid;

    for (int i = 0 ; i < 3; i++){
        if ((pid = fork()) < 0) { // if fork error occured, exit
            perror("fork");
            exit(1);
        }

        if (pid == 0) {            // if this process is child, print pid and ppid and exit.
            printf("my pid is %d and ppid is %d\n", (int)getpid(), (int)getppid());
            return 0;
        }
    }

    return 0;
}