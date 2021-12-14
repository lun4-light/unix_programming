#include <stdio.h>
#include <stdlib.h>
#include <sys/signal.h>

void handler (int signo) {
    return;
}

int main(void) {
    short i = 0;
    struct sigaction act;

    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGQUIT);

    act.sa_flags = 0;
    act.sa_handler = handler;
    
    if (sigaction(SIGINT, &act, (struct sigaction *)NULL) < 0) {
        perror("sigaction");
        exit(1);
    }

    while(1) {
        if (i < 0)
            i = 0;
        printf("%d\r", i++);
    }

    return 0;
}