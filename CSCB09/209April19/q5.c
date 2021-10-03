#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int my_pipe[2];
    
    if ((pipe(my_pipe)) == -1) {
        perror("pipe");
        exit(1);
    }
    int a, b, a_status, b_status;
    switch (a = fork())     // A process
    {
        case -1:
            perror("fork");
            exit(1);
            break;
        case 0:
            close(my_pipe[0]); // Won't be reading from pipe
            foo_a();
            break;
        default:
            waitpid(a, &a_status, 0);
            break;
    }
    switch (b = fork())     // B process
    {
        case -1:
            perror("fork");
            exit(1);
            break;
        case 0:
            close(my_pipe[1]); // Won't be writing to pipe
            foo_b();
            break;
        default:
            waitpid(b, &b_status, 0);
            break;
    }
}