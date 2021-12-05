#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void) {
    int pd, n;
    char msg[] = "Hello, FIFO";

    printf("Server ===== \n");

    if (mkfifo("./TESTFIFO",0666) == -1){
        perror("mkfifo");
        exit(1);
    }

    if ((pd = open("./TESTFIFO", O_WRONLY)) == -1) {
        perror("open");
        exit(1);
    }

    printf("To Client : %s\n", msg);

    n = write(pd, msg, strlen(msg) + 1);

    if (n == -1) {
        perror("write");
        exit(1);
    }

    close(pd);

    return 0;
}