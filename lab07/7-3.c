#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void) {
    int pd[2];      // read, write file descriptor
    char str[] = "Pipe test";   // test array
    char buf[BUFSIZ];
    int len, status;

    if (pipe(pd) == -1){
        perror("pipe");
        exit(1);
    }
    /*  write test string from pipe descriptor */
    write(pd[1], str, strlen(str)); 
    printf("%d writes %s to the pipe.\n", (int)getpid(), str);
    /*  read string from pipe descriptor */
    len = read(pd[0], buf, BUFSIZ); 
    printf("%d reads %s from the pipe.\n", (int)getpid(), buf);

    close(pd[0]);
    close(pd[1]);

    return 0;
}