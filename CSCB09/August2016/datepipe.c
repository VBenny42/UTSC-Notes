#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int fd[2];

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }
    switch (fork())
    {
        case -1:
            perror("fork");
            exit(1);
            break;
        case 0: // Child process runs "/bin/date"
            // Close reading end of pipe
            if (close(fd[0]) == -1) {
                perror("close");
                exit(1);
            }
            // Set stdout so that writing to stdout goes to pipe
            if (dup2(fd[1], STDOUT_FILENO) == -1) {
                perror("dup2");
                exit(1);
            }
            // Close duplicate fd of writing end of pipe
            if (close(fd[1]) == -1) {
                perror("close");
                exit(1);
            }
            execl("/bin/date", "/bin/date", (char *) NULL);
            fprintf(stderr, "ERROR: exec should not return \n"); // This line is only reached when exec fails somehow
            break;
        default:
            // Closes writing end because process never writes to pipe
            if (close(fd[1]) == -1) {
                perror("close");
                exit(1);
            }
            char buf[5];
            // Reads 5 bytes from pipe
            if (read(fd[0], buf, 5) == -1) {
                perror("read");
                exit(1);
            }
            printf("%c\n", buf[4]);
            exit(0);
            break;
    }
    return 0;
}