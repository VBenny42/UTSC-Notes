#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 256

void translate(char *tr_set, char *replace, FILE *input)
{
    char buf[MAX_SIZE];
    while (fgets(buf, MAX_SIZE, input) != NULL) {
        for (int i = 0; i<strlen(buf); i++) {
            if (strchr(tr_set, buf[i]) != NULL) {   // Char exists in set, so must replace
                printf("%c", replace[0]);
            }
            else {
                printf("%c", buf[i]);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "Not enough arguments\n");
        return -1;
    }
    if (argc == 3) {
        translate(argv[1], argv[2], stdin);
    }
    else {
        for (int i = 3; i<argc; i++) {
            FILE *input = fopen(argv[i], "r");
            translate(argv[1], argv[2], input);
            if (fclose(input) == -1) {
                perror("fclose");
                return -1;
            }
        }
    }
}