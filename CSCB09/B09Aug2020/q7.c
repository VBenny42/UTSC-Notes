#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
#include <ctype.h>

void do_left(int fd_read, int fd_write)
{
    #define BUF_SIZE 512
    char buf[BUF_SIZE];
    int read_val;
    fd_set read_fds;
    for(;;) {
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);
        FD_SET(fd_read, &read_fds);
        if (select(fd_read + 1, &read_fds, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(1);
        }
        if (FD_ISSET(fd_read, &read_fds)) {     // fd_read ready for reading
            // EOF or Error
            if (((read_val = read(fd_read, buf, BUF_SIZE)) == 0) || (read_val == -1)) {
                exit(0);
            }
            // No error checking because assuming write is successful
            write(STDOUT_FILENO, buf, read_val);
        }
        else if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            // EOF or Error
            if (((read_val = read(STDIN_FILENO, buf, BUF_SIZE)) == 0) || (read_val == -1)) {
                exit(0);
            }
            char charbuf;
            for (int i = 0; i < read_val; i++) {
                charbuf = (char) toupper(buf[i]);
                write(fd_write, &charbuf, 1);
            }
        }
    }
}