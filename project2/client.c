#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "port.h"
#include "baseball.h"

char* fileName = "client";

int main(int argc, char* argv[]) {
    struct sockaddr_in sin;
    int portNum, sd, position, gameStatus = 1;
    char pos[256];

    if ((portNum = port(argc, argv, fileName)) == -1){
        return 0;
    }

    memset((char *)&sin, '\0', sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(portNum);
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket");
        exit(1);
    }

    if (connect(sd, (struct sockaddr *)&sin, sizeof(sin))) {
        perror("connect");
        exit(1);
    }

    printf("=== Server connecting is success on PORT %d ===\n",portNum);
    printf("=== Server owner is selecting position ===\n");

    if (recv(sd, pos, strlen(pos), 0) == -1) {
        perror("recv");
        exit(1);
    }

    printf("pos : %s\n", pos);

    if (pos[0] - '0' == 1) {
        position = 2;
    }
    else {
        position = 1;
    }

    while (gameStatus) {
        switch (position) {
            case 1:
                gameStatus = attack(sd);
                sleep(1);
                break;
            case 2:
                gameStatus = defence(sd);
                sleep(1);
                break;
        }
    }

    close(sd);
    return 0;
}