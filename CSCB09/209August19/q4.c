#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STR 256

int main()
{
    char buf[MAX_STR];
    if (fgets(buf, MAX_STR, stdin) == NULL) {
        perror("fgets");
        return -1;
    }
    for (int i = 0; i < strlen(buf); i++) {
        printf("%c", isupper(buf[i]) ? tolower(buf[i]) : buf[i]);
    }
    return 0;
}