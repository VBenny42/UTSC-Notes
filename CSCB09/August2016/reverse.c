#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char *buf, char *arg) {
    int index = strlen(arg);
    for (int i = 0; i<index; i++){
        buf[i] = arg[(index-1) - i];
    }
}

int main(int argc, char **argv)
{
    char buf[256];
    for (int i = 1; i<argc; i++) {
        strcpy(buf, argv[i]);
        reverse(buf, argv[i]);
        printf("%s\n", buf);
    }
}