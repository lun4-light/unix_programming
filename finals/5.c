#include <stdio.h>
#include <signal.h>

void handler (int signo) {
    exit(1);
}

int main(void) {
    short i = 0;
    struct sigaction act;

    sigemtpyset(&act.sa_mask);

    act.sa_flags = 0;
    act.sa_handler = handler;

    if (sigaction(SIGQUIT, &act, (struct sigaction *)NULL) < 0) {
        perror("sigaction");
        exit(1);
    }

    while(1) {
        if (i < 0){ 
            i = 0;
            printf("%d\r", i++);
        }
    }

    return 0;
}