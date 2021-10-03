#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    char buf[24];
    strcpy(buf, "good morning");
    printf("%d\n", strlen(buf+1));
    write(1, buf, strlen(buf+1));
    printf("\n");
}