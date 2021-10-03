#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Incorrect number of arguments\n");
        return -1;
    }
    int times;
    if ((times = atoi(argv[2])) == -1) {
        perror("atoi");
        return -1;
    }
    for (int i = 0; i < times; i++) {
        printf("%s\n", argv[1]);
    }
    return 0;
}