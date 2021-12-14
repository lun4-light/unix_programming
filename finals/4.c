#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

int main(void) {
    int pd[2];
    pid_t pid;

    /* 파이프 생성 */
    if (pipe(pd) == -1) {
        perror("pipe");
        exit(1);
    }

    /* fork */
    switch(pid = fork()) {
        case -1:
            perror("fork");
            exit(1);
            break;
        case 0:     /* 자식 프로세스 */
            close(fd[1]);
            if (fd[0] != 0) {
                dup(fd[0], 0);
                close(fd[0]);
            }
            execlp("grep", "grep", "c", (char *)NULL);
            wait(NULL);
            break;
        default:    /* 부모 프로세스 */
            close(fd[0]);
            if (fd[1] != 1) {
                dup2(fd[1], 1);
                close(fd[1]);
            }
            execlp("ls", "ls", "-l", (char *)NULL);
            wait(NULL);
            break;
    }

    return 0;
}