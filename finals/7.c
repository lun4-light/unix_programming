#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/ipc.h>

int main(void) {
    int shmid, i;
    char *addr, *addr2;
    shmid = shmget(IPC_PRIVATE, 40, IPC_CREAT|0644);    

    if (shmid == -1){
        perror("shmget");
        exit(1);
    }

    switch(fork()) {
        case -1:
            perror("fork");
            exit(1);
            break;
        case 0:
            printf("= Child begins\n");
            addr = (char *)shmat(shmid, (char *)NULL, 0);
            strcpy(addr, "Message from ");
            sprintf(addr, "%s %d\n", addr, (int)getpid());
            printf("= Child ends\n");
            shmdt((char *)addr);
            exit(0);
            break;
        default:
            wait(0);
            printf("= Parent begins\n");
            addr2 = (char *)shmat(shmid, (char *)NULL, 0);
            printf("%s", addr2);
            shmdt((char*)addr2);
            shmctl(shmid, IPC_RMID, (struct shmid_ds *)NULL);
            printf("= Parent ends\n");
            break;
    }

    return 0;
}