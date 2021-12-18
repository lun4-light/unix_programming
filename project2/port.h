#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int port(int argc, char* argv[], char* fn) {
    if (argc != 2) {
        printf("Usage : ./%s PORTNUM\n", fn);
        return -1;
    }

    return atoi(argv[1]);
}