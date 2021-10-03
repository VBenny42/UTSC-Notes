// left child code , part (a)
close(rtl[1]);
int fd_read = rtl[0];   // Assign reading end to fd_read
close(ltr[0]);
int fd_write = ltr[1];  // Assign writing end to fd_write
do_left(fd_read, fd_write);
