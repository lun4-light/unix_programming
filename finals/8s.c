#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 9000
#define LENGTH 256

int main(void) {
    char buf[LENGTH];

    struct sockaddr_in sin, cli;
    int sd, ns, clientlen = sizeof(sin);
    int getmsglen;

    memset((char*)&sin, '\0', sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT);
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket");
        exit(1);
    }

    if (bind(sd, (struct sockaddr *)&sin, sizeof(sin))) {
        perror("bind");
        exit(1);
    }

    if (listen(sd, 5)) {
        perror("listen");
        exit(1); 
    }

    while (1) {
        if ((ns = accept(sd, (struct sockaddr *)&cli, &clientlen)) == -1) {
            perror("accept");
            exit(1);
        }

        if ((getmsglen = recv(ns, buf, LENGTH, 0) == -1) {
            perror("recv");
            exit(1);
        } 

        for (int i = 0; i < getmsglen ; i++) {
            if ((buf[i] - 'A' >= 0 && buf[i] - 'A' < 26)
                buf[i] = buf[i] + 32;
            else if (buf[i] - 'a' >= 0 && buf[i] - 'a' < 26)
                buf[i] = buf[i] - 32;
        }

        if (send(ns, buf, strlen(buf), 0) == -1){
            perror("send");
            exit(1);
        }
        close(ns);
    }

    close(sd);

    return 0;
}