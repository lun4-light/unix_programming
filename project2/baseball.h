#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int attack(int opponent) {
    int gameChecker = 1, turnCounter = 0, rlen;
    char atkbuf[256], balls[6];

    printf("=== ATTACK ===\n");
    printf("Wait for Defence input balls . . . \n");

    while (gameChecker && turnCounter < 10) {
        turnCounter++;
        printf("Turn #%d . . .\n", turnCounter); 

        printf("Guess opponent player's balls . . .\n");

        printf("BALLS ==> ");

        scanf("%s", balls);
        while (getchar() != '\n');
        
        sprintf(atkbuf, "%s", balls);
            
        if (send(opponent, atkbuf, sizeof(atkbuf) + 1, 0) == -1) {
            perror("send");
            exit(1);
        }

        while(1) {        
            if ((rlen = recv(opponent, atkbuf, sizeof(atkbuf), 0)) == -1) {
                perror("recv");
                exit(1);
            }

            if (rlen > 1)
                break;
        }

        if (atkbuf[0] == '4') {
            printf("=== Player gets all strikes at turn #%d! ===\n", turnCounter);
            gameChecker = 0;
        }
        else {
            printf("You get %c Strikes, %c Balls, and %c outs.\n", atkbuf[0], atkbuf[1], atkbuf[2]);
        }
    }

    return 0;
}

int defence(int opponent) {
    int gameChecker = 1, turnCounter = 0, rlen;
    char playerBalls[4];

    printf("=== DEFENCE ===\n");
    printf("Input your balls. . .\n");

    printf("BALLS ==> ");
    scanf("%s", playerBalls);
    while (getchar() != '\n');
    
    while (gameChecker && turnCounter < 10) {
        char defbuf[256], opponentBalls[4];
        int ball = 0, strike = 0, out = 4;
        turnCounter++;
        printf("Turn #%d . . . waiting opponent player.\n", turnCounter);

        while (1) {
            if ((rlen = recv(opponent, defbuf, sizeof(defbuf), 0)) == -1){
                perror("recv");
                exit(1);
            }

            if (rlen > 1)
                break;
        }

        for (int i = 0 ; i < 4 ; i++){
            opponentBalls[i] = defbuf[i];
            printf("%c", opponentBalls[i]);
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
        else {
            printf("Opponent player gets %d Strikes, %d Balls, and %d outs.\n", strike, ball, out);
        }

        sprintf(defbuf, "%d%d%d", strike, ball, out);
        
        if (send(opponent, defbuf, sizeof(defbuf) + 1, 0) == -1) {
            perror("send");
            exit(1);
        }
    }

    return 0;
}