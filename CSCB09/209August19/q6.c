#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    FILE *file;
    char buf[10];
    char hashtest[2];
    int sum = 0;
    for (int i = 1; i < 101; i++) {
        sprintf(buf, "%d", i);
        if ((file = fopen(buf, "r")) == NULL) {
            continue;
        }
        if (fgets(hashtest, 2, file) == NULL) {
            fclose(file);
            continue;
        }
        if (*hashtest == '#') {
            sum++;
        }
        fclose(file);
    }
    printf("%d\n", sum);
}