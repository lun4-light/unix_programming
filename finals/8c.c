#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 9000
#define LENGTH 256

int main(int argc, char* argv[]) {
    int sd;
    char buf[LENGTH];

    struct sockaddr_in sin;

    if (argc == 1) {
        printf("Input arguments is not exist. \n");
        exit(0);
    }

    for (int i = 1 ; i < argc ; i++) {
        strcat(&buf, argv[i]);
        strcat(&buf, " ");
    }

    memset((char *)&sin, '\0', sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT);
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    if (connect(sd, (struct sockaddr *)&sin, sizeof(sin))) {
        perror("connect");
        exit(1);
    }

    if (send(sd, buf, sizeof(buf) + 1, 0) == -1) {
        perror("send");
        exit(1);
    }

    if (recv(sd, buf, sizeof(buf), 0) == -1) {
        perror("recv");
        exit(1);
    }

    printf("From Server : %s\n", buf);

    close(sd);

    return 0;
}