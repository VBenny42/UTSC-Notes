// Changed code beginning at line 14

    while (1) {
        len = sizeof q;
        if ((clientfd = accept(fd, (struct sockaddr *)&q, &len)) < 0) { 
            perror ("accept" );
            return(1);
        }
        switch (read(clientfd, &c, 1)) { 
            case -1:
                perror("read");
                return(1);
            case 1:
                if (c == 2) {
                    char *ha = "ha!\n"
                    if (write(clientfd, ha, 4) != 4) {
                        perror("write");
                    }
                }
                if ((c != 2) && (write(clientfd, &c, 1) != 1))
                    perror("write");
            }
            close(clientfd);
    }
}
