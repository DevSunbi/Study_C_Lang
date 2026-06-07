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

void chatting(int);
int main(int argc, char *argv[]) {
    int sockfd, numbytes;
    socklen_t addr_len;
    char buf[MAXDATASIZE];
    struct hostent *he;
    struct sockaddr_in server_addr;

    if (argc != 2) {
        fprintf(stderr, "usage : client hostname \n");
        exit(1);
    }
    // printf("HERE\n");
    if ((he = gethostbyname(argv[1])) == NULL) {
        printf("FUCK\n");
        perror("gethostbyname");
        exit(1);
    }
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(60000);
    server_addr.sin_addr = *((struct in_addr *)he->h_addr_list[0]);
    printf("[ %s ]\n", (char *)inet_ntoa(server_addr.sin_addr));
    memset(&(server_addr.sin_zero), '\0', 8);
    if (connect(sockfd, (struct sockaddr *)&server_addr,
                sizeof(struct sockaddr)) == -1) {
        perror("connect");
        exit(1);
    }

    chatting(sockfd);
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
            continue;
        char buf[MAXDATASIZE];
        int num_bytes;
        if (pollfds[0].revents & POLLIN) {
            // printf("HERE!!!\n");
            fgets(buf, MAXDATASIZE, stdin);
            buf[strcspn(buf, "\n")] = '\0';

            if (!strcmp(buf, "quit")) {
                return;
            }
            write(sd, buf, strlen(buf));

        } else if (pollfds[1].revents & POLLIN) {
            // printf("HERE!!!\n");
            num_bytes = recv(sd, buf, MAXDATASIZE, 0);

            if (num_bytes == 0) {
                printf("[CLIENT] SERVER DISCONNECTED\n");
                close(sd);
                return;
            } else if (num_bytes == -1) {
                perror("recv");
                close(sd);
                return;
            }

            buf[num_bytes] = '\0';
            // printf("num_bytes: %d\n", num_bytes);
            printf("[SERVER HAS SENT A MESSAGE]\n");
            printf("#    MESSAGE: %s\n", buf);
        } else {
            printf("[CLIENT] CHATTING FUNCTION ERROR\n");
            return;
        }
    }
}