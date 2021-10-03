#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    int fd, clientfd; 
    socklen_t len;
    struct sockaddr_in r, q; 
    char c;

    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
        perror("socket");
        return(1);
    }

    memset(&r, '\0 ', sizeof r); 
    r.sin_family = AF_INET; 
    r.sin_addr.s_addr = INADDR_ANY; 
    r.sin_port = htons(2000);

    if (bind(fd, (struct sockaddr *)&r, sizeof r) < 0) { 
        perror("bind");
        return(1);
    }
    if (listen(fd, 5)) { 
        perror("listen"); 
        return(l);
    }

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
                if (write(clientfd, &c, 1) != 1)
                    perror("write");
            }
            close(clientfd);
    }
}
