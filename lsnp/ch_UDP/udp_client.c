#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXDATASIZE 100
#define PORT 60000

int main(int argc, char *argv[])
{
    int sockfd;
    int numbytes;
    socklen_t addr_len;
    char buf[MAXDATASIZE];

    struct hostent *he;
    struct sockaddr_in server_addr;

    if (argc != 2) {
        fprintf(stderr, "usage: %s hostname\n", argv[0]);
        exit(1);
    }

    he = gethostbyname(argv[1]);
    if (he == NULL) {
        herror("gethostbyname");
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr = *((struct in_addr *)he->h_addr);

    printf("server ip: %s\n", inet_ntoa(server_addr.sin_addr));

    const char *msg = "Hello UDP server";

    if (sendto(sockfd,
               msg,
               strlen(msg),
               0,
               (struct sockaddr *)&server_addr,
               sizeof(server_addr)) == -1) {
        perror("sendto");
        close(sockfd);
        exit(1);
    }

    printf("message sent: %s\n", msg);

    addr_len = sizeof(server_addr);

    numbytes = recvfrom(sockfd,
                        buf,
                        MAXDATASIZE - 1,
                        0,
                        (struct sockaddr *)&server_addr,
                        &addr_len);

    if (numbytes == -1) {
        perror("recvfrom");
        close(sockfd);
        exit(1);
    }

    buf[numbytes] = '\0';

    printf("received %d bytes from %s:%d\n",
           numbytes,
           inet_ntoa(server_addr.sin_addr),
           ntohs(server_addr.sin_port));

    printf("server message: %s\n", buf);

    close(sockfd);
    return 0;
}