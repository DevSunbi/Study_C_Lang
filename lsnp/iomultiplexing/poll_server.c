#include <arpa/inet.h> // inet_ntoa() - converts IP to string
#include <fcntl.h>
#include <netdb.h>      // network database (not directly used here)
#include <netinet/in.h> // sockaddr_in, INADDR_ANY
#include <poll.h>
#include <pthread.h> // threads
#include <stdio.h>   // printf, perror
#include <stdlib.h>  // exit()
#include <string.h>  // memset()
#include <sys/select.h>
#include <sys/socket.h> // socket(), bind(), listen(), accept(), send()
#include <sys/types.h>  // type definitions (pid_t, etc.)
#include <sys/wait.h>   // waitpid()
#include <unistd.h>     // fork(), close()
#define BACKLOG 10
#define MAXDATASIZE 100

// void *client_transm_tfunction(void *arg) {
// int *fds = (int *)arg;
// // close(fds[0]); // as child doesn't need to listen

// if (send(fds[1], "Hello CLIENT!\n", 14, 0) == -1) {
//     perror("send");
// } // send 14 bytes to the client
// write(fds[1], "HELLO CLIENT USING WRITE", 14);
// close(fds[1]);
// return NULL;
// }

void chatting(int);

int main(void) {
    printf("[SERVER] SERVER START\n");
    int sockfd,
        new_fd; // listening socket and sockent for incoming flient connection
    struct sockaddr_in
        server_addr; // struct that holds an ip address and port for socket
    struct sockaddr_in client_addr; // struct that holds an ip address and port
                                    // for client socket

    int sin_size; // hold sthe size of client addr, required by accept

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) ==
        -1) { // open socket with IPv4, TCP, returns fd
        perror("socket error");
        exit(1);
    }

    /*
    Configuring the server address
    */
    server_addr.sin_family = AF_INET;    // IPv4
    server_addr.sin_port = htons(60000); // listen on port 60000
    server_addr.sin_addr.s_addr =
        htonl(INADDR_ANY);                    // accept from any interface
    memset(&(server_addr.sin_zero), '\0', 8); // zero out padding bytes 2

    /*
    htons / htonl — convert to network byte order (big-endian). Required because
    different CPUs store bytes differently. INADDR_ANY — binds to all available
    network interfaces (localhost, LAN, etc.)
    */

    if (bind(sockfd, (struct sockaddr *)&server_addr,
             sizeof(struct sockaddr)) ==
        -1) { // assigns the address / port to the socket
        perror("bind");
        exit(1);
    }
    printf("[SERVER] BINDING DONE\n");

    if (listen(sockfd, BACKLOG) ==
        -1) { // marks the socket as passive (accepting connections)
        // backlog is the number of pending connections queued before the os
        // starts refusing new ones.
        perror("listen");
        exit(1);
    }

    while (1) {
        printf("[SERVER] LISTENING.....\n");

        sin_size = sizeof(struct sockaddr_in);

        if ((new_fd = accept(sockfd, (struct sockaddr *)&client_addr,
                             &sin_size)) == -1) {
            // fills client_addr with the client's ip / port, returns
            // new_fd dedicated to that client, and blocks until a client
            // connects
            perror("accept");
            exit(1);
        }
        // prints the connection with
        printf("[SERVER]: got connection from %s \n",
               inet_ntoa(client_addr.sin_addr));
        // ip address of the client
        chatting(new_fd);
        // close(new_fd);
    }

    return 0;
}

void chatting(int sd) {
    struct pollfd pollfds[2];
    pollfds[0].fd = 0;
    pollfds[0].events = POLLIN;

    pollfds[1].fd = sd;
    pollfds[1].events = POLLIN;

    while (1) {
        int s_count = poll(pollfds, 2, -1);
        // printf("HERE!!! %d\n", s_count);
        if (s_count <= 0)
            break;

        char buf[MAXDATASIZE];
        int num_bytes;
        if (pollfds[0].revents & POLLIN) {
            fgets(buf, MAXDATASIZE, stdin);
            buf[strcspn(buf, "\n")] = '\0';
            write(sd, buf, strlen(buf));

        } else if (pollfds[1].revents & POLLIN) {
            // printf("HERE!!!\n");
            num_bytes = recv(sd, buf, MAXDATASIZE, 0);

            if (num_bytes == 0) {
                printf("[SERVER] CLIENT DISCONNECTED\n");
                close(sd);
                return;

            } else if (num_bytes == -1) {
                perror("recv");
                close(sd);
                return;
            }

            buf[num_bytes] = '\0';
            // printf("num_bytes: %d\n", num_bytes);
            printf("[CLIENT HAS SENT A MESSAGE]\n");
            printf("#    MESSAGE: %s\n", buf);

        } else {
            printf("[SERVER] CHATTING FUNCTION ERROR\n");
        }
    }
}