#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int f1, f2;
    if ((f1 = open(argv[1], O_RDONLY | O_CLOEXEC)) == -1) {
        perror("open");
        return -1;
    }
    if ((f2 = open(argv[2], O_WRONLY | O_CLOEXEC | O_CREAT, 00666)) == -1) {
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
            dup2(f1, STDIN_FILENO);
            close(f1);
            dup2(f2, STDOUT_FILENO);
            close(f2);
            execl("/usr/bin/tr", "/usr/bin/tr", "e", "f", (char *) NULL);
            break;
        default:
            wait(&status);
            if (WIFEXITED(status)) {
                printf("child process exit status was %d\n", WEXITSTATUS(status));
            }
            exit(0);
            break;
    }
    return 0;
}