#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

int f() {
    return 69;
}

int g() {
    return 420;
}

int main()
{
    int chpipe[2];
    if (pipe(chpipe) == -1) {
        perror("pipe");
        return -1;
    }
    switch (fork()) 
    {
        case -1:
            perror("fork");
            exit(1);
            break;
        case 0:
            close(chpipe[0]); // Will not be reading from pipe in child
            int fret_val = f();
            write(chpipe[1], &fret_val, sizeof(fret_val));
            break;
        default:
            close(chpipe[1]); // Will not be writing to pipe in parent
            int gret_val = g();
            int ffret_val;
            read(chpipe[0], &ffret_val, sizeof(fret_val));
            printf("%d\n", ffret_val+gret_val);
            break;
    }
    return 0;
}