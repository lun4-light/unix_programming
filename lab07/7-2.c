#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    int fd;
    pid_t pid;
    caddr_t addr;
    struct stat buf;
    
    /* if there are less than two arguments, print error message and exit */
    if (argc != 2) {
        fprintf(stderr, "Usage : %s filename\n", argv[0]);
        exit(1);
    }

    /* if stat error, print error message and exit */
    if (stat(argv[1], &buf) == -1){
        perror("stat");
        exit(1);
    }

    /* if open error, print error message and exit */
    if ((fd = open(argv[1], O_RDWR)) == -1) {
        perror("open");
        exit(1);
    }

    /* mapping memory. if it fail, exit */        
    addr = mmap(NULL, buf.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, (off_t)0);

   if (addr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    switch(pid = fork()) {
        case -1: /* fork failed */
            perror("fork");
            exit(1);
            break;
        case 0:  /* child process, print */
            printf("%s", addr);
            break;
        default: /* parent process */
            /* file close */
            close(fd);
            break;
    }

    return 0;
}