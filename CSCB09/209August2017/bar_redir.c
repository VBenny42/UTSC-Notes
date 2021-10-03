#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int bar;
    if ((bar = open("bar", O_WRONLY | O_CLOEXEC | O_CREAT, 00666)) == -1) {
        perror("open");
        return -1;
    }
    int status;
    switch (fork())
    {
        case -1:
            perror("fork");
            exit(1);
            break;
        case 0:
            dup2(bar, 7);   
            close(bar);
            execl("/local/t3", "/local/t3", (char *) NULL);
            break;
        default:
            wait(&status);
            exit(0);
            break;
    }
    return 0;
}