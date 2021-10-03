#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 

#define MAX_SIZE 256

int main()
{
    // create socket
    int listen_soc = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_soc == -1) {
        perror("server: socket");
        exit(1);
    }


    // initialize server address    
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(2000);  
    memset(&server.sin_zero, 0, 8);
    
    // server.sin_addr.s_addr = INADDR_ANY;
    if (inet_aton("127.0.0.1", &server.sin_addr) == 0) {
        fprintf(stderr, "Address not valid\n"); 
        exit(1);
    }

    // bind socket to an address
    if (bind(listen_soc, (struct sockaddr *) &server, sizeof(struct sockaddr_in)) == -1) {
      perror("server: bind");
      close(listen_soc);
      exit(1);
    } 

    // Still needed the listen line or accept wouldn't work
    if (listen(listen_soc, 5) < 0) {
        perror("listen");
        exit(1);
    }

    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(struct sockaddr_in);
    client_addr.sin_family = AF_INET;

    char name[MAX_SIZE];

    for (;;) {
        int client_socket = accept(listen_soc, (struct sockaddr *) &client_addr, &client_len);
        if (client_socket == -1) {
            perror("accept");
            exit(1);
        }
        FILE *socfd = fdopen(client_socket, "r");
        for (;;) {
            // close(listen_soc);
            if (fgets(name, MAX_SIZE, socfd) == NULL) {
                fprintf(stderr, "Client disconnected\n");
                close(client_socket);
                fclose(socfd);
                break;
            }
            else {
                printf("%s", name);
            }
        }
    }
    return 0;
}