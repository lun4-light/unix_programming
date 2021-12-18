#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int attack(int opponent) {
    int gameChecker = 1, turnCounter = 0;
    int balls[4];
    char buf[256];
    printf("=== ATTACK ===\n");
    printf("Wait for Defence input balls . . . \n");

    while (gameChecker) {
        turnCounter++;
        printf("Turn #%d . . .\n", turnCounter); 

        printf("Guess opponent player's balls . . .\n");

        for (int i = 0 ; i < 4; i++) {
            printf("BALL #%d ==> ", i + 1);
            scanf("%d", &balls[i]);
            getchar();
        }

        sprintf(buf, "%d%d%d%d", balls[0], balls[1], balls[2], balls[3]);

        if (send(opponent, buf, strlen(buf) + 1, 0) == -1) {
            perror("send");
            exit(1);
        }

        if (recv(opponent, buf, strlen(buf), 0) == -1) {
            perror("recv");
            exit(1);
        }

        if ((buf[0] - '0') == 4) {
            printf("=== Player gets all strikes at turn #%d! ===\n", turnCounter);
            gameChecker = 0;
        }
        else {
            printf("You get %c Strikes, %c Balls, and %c outs.\n", buf[0], buf[1], buf[2]);
        }
    }

    return 0;
}

int defence(int opponent) {
    int playerBalls[4], opponentBalls[4], gameChecker = 1, turnCounter = 0;
    char buf[256];
    printf("=== DEFENCE ===\n");
    printf("Input your balls. . .\n");

    for (int i = 0 ; i < 4 ; i++) {
        printf("BALL #%d ==> ", i + 1);
        scanf("%d", &playerBalls[i]);
        getchar();
    }

    while (gameChecker || turnCounter < 10) {
        turnCounter++;
        printf("Turn #%d . . . waiting opponent player.\n", turnCounter);
        int ball = 0, strike = 0, out = 4;

        if (recv(opponent, buf, strlen(buf), 0) == -1){
            perror("recv");
            exit(1);
        }

        printf("%s\n", buf);

        for (int i = 0 ; i < 4 ; i++) {
            opponentBalls[i] = buf[i] - '0';
            printf("%d", opponentBalls[i]);
        }

        printf("\n");

        for (int i = 0 ; i < 4 ; i++) {
            for (int j = 0 ; j < 4; j++) {
                if (playerBalls[i] == opponentBalls[j]) {
                    if (i == j)
                        strike++;
                    else
                        ball++;
                    out--;
                    break;
                }
            }
        }
        if (strike == 4) {
            printf("=== Opponent gets all strikes at turn #%d! ===\n", turnCounter);
            gameChecker = 0;
        }
        else
            printf("Opponent player gets %d Strikes, %d Balls, and %d outs.\n", strike, ball, out);

        sprintf(buf, "%d%d%d", strike, ball, out);
        
        if (send(opponent, buf, strlen(buf) + 1, 0) == -1) {
            perror("send");
            exit(1);
        }
    }

    return 0;
}