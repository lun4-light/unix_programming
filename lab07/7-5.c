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
    int pd1[2], pd2[2];      // read, write file descriptor
    char parent[] = "from parent";   // parent array
    char child[] = "from child"; // child array
    char buf[BUFSIZ];
    int len, status;
    pid_t pid;

    if (pipe(pd1) == -1 || pipe(pd2) == -1){
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
            close(pd2[0]);
            close(pd1[1]);
            
            write(pd2[1], child, strlen(parent));
            len = read(pd1[0], buf, BUFSIZ);
            printf("%s\n", buf);

            close(pd1[1]);
            close(pd2[0]);
            break;
        default :
            close(pd2[1]);
            close(pd1[0]);
            
            write(pd1[1], parent, strlen(parent));
            len = read(pd2[0], buf, BUFSIZ);
            printf("%s\n", buf);

            close(pd2[0]);
            close(pd1[1]);
            waitpid(pid, &status, 0);
            break;
    }

    return 0;
}