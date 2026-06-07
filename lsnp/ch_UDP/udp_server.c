#include <stdio.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define PORT 60000
#define MAXDATASIZE 100

int main(void)
{
    int sockfd;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in myaddr;
    memset(&myaddr, 0, sizeof(myaddr));

    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(PORT);
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr *)&myaddr, sizeof(myaddr)) == -1) {
        perror("bind");
        close(sockfd);
        exit(1);
    }

    printf("UDP server listening on port %d...\n", PORT);

    struct sockaddr_in from_addr;
    socklen_t fromlen;
    char recv_msg[MAXDATASIZE];
    int numbytes;

    while (1) {
        fromlen = sizeof(from_addr);

        numbytes = recvfrom(
            sockfd,
            recv_msg,
            MAXDATASIZE - 1,
            0,
            (struct sockaddr *)&from_addr,
            &fromlen
        );

        if (numbytes == -1) {
            perror("recvfrom");
            break;
        }

        recv_msg[numbytes] = '\0';

        printf("%d bytes from %s:%d\n",
               numbytes,
               inet_ntoa(from_addr.sin_addr),
               ntohs(from_addr.sin_port));

        printf("client message: %s\n", recv_msg);

        const char *msg = "Message received by UDP server";

        if (sendto(
                sockfd,
                msg,
                strlen(msg),
                0,
                (struct sockaddr *)&from_addr,
                fromlen
            ) == -1) {
            perror("sendto");
            break;
        }
    }

    close(sockfd);
    return 0;
}