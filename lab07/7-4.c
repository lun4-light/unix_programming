#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(void) {
    int pd[2];      // read, write file descriptor
    char str[] = "Pipe test";   // test array
    char buf[BUFSIZ];
    int len, status;
    pid_t pid;

    if (pipe(pd) == -1){
        perror("pipe");
        exit(1);
    }

    switch (pid = fork()) {
        case -1 :
            perror("fork");
            exit(1);
            break;
        case 0 : 
            /*  read string from pipe descriptor */
            close(pd[1]);
            len = read(pd[0], buf, BUFSIZ); 
            printf("%d reads %s from the pipe.\n", (int)getpid(), buf);
            close(pd[0]);
            break;
        default :
            close(pd[0]);

            /*  write test string from pipe descriptor */
            write(pd[1], str, strlen(str)); 
            printf("%d writes %s to the pipe.\n", (int)getpid(), str);
            close(pd[1]);
            waitpid(pid, &status, 0);
            break;
    }
    return 0;
}