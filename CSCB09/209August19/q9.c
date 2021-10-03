#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int null;
    if ((null = open("/dev/null", O_RDWR)) == -1) {
        perror("open");
        return -1;
    }
    if (dup2(null, STDOUT_FILENO) == -1) {
        perror("dup2");
        return -1;
    }
    close(STDOUT_FILENO);
    if (dup2(null, STDIN_FILENO) == -1) {
        perror("dup2");
        return -1;
    }
    close(STDIN_FILENO);
    if (dup2(null, STDERR_FILENO) == -1) {
        return -1;
    }
    close(STDERR_FILENO);
    if (execl("/u/ajr/crazy", "/u/ajr/crazy", (char *) NULL) == -1) {
        exit(1);
    }
}