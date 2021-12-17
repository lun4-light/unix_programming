#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <port.h>
#include <baseball.h>

char* fileName = "server";

int main(int argc, char* argv[]) {
    struct sockaddr_in sin, cli;
    int portNum, sd, ns, position, clientlen = sizeof(cli);
    char pos[10];

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

    if (bind(sd, (struct sockaddr *)&sin, sizeof(sin))) {
        perror("bind");
        exit(1);
    }

    if (listen(sd, 5)){
        perror("listen");
        exit(1);
    }

    printf("=== Server is running on PORT %d ===\n",portNum);

    while (1) {
        printf("=== Choice attack or defence === (attack : 1, defence : 2) : ");
        scanf("%d", &position);

        if (position > 0 && position < 3)
            break;

        printf("=== Position error. Please retry. ===\n");
    }
    memset(pos, '\0', sizeof(pos));

    pos[0] = position - '0';
    
    while(1) {
        if ((ns = accept(sd, (struct sockaddr *)&cli, &clientlen)) == -1){
            perror("accept");
            exit(1);
        }

        if (send(opponent, pos, strlen(buf) + 1, 0) == -1) {
            perror(send);
            exit(1);
        }

        switch(fork()) {
            case 0:
                int gameStatus = 1;
                close(sd);

                while (gameStatus) {
                    switch (position) {
                        case 1:
                            gameStatus = attack(ns);
                            break;
                        case 2:
                            gameStatus = defence(ns);
                            break;
                    }
                }
                break;
        }
    }

    return 0;
}