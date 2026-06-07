#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/ioctl.h>

int main(int argc, char **argv)
{
    struct sockaddr_in serveraddr, clientaddr;
    int sockfd;
    int client_sd;
    int  socklen;
    int n, i;
    int readn;
    struct epoll_event ev,*client_list;
    int efd;
    char buf_in[256];
    int client_fds[100];
    int client_cnt = 0;

    client_list = (struct epoll_event *)malloc(sizeof(*client_list) * 20);
    if ((efd = epoll_create(100)) < 0) {
            perror("epoll_create");
            exit(1);
    }
    socklen = sizeof(clientaddr);
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0))==-1) {
        perror("socket error :");
        close(sockfd);
        return 1;
    }
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(60000);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind (sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1) {
        close(sockfd);
        return 1;
    }
    listen(sockfd, 5);
    ev.events = EPOLLIN;
    ev.data.fd = sockfd;
    epoll_ctl(efd, EPOLL_CTL_ADD, sockfd, &ev);
    while(1) {
        if((n = epoll_wait(efd, client_list, 20, -1))==-1) { // 이벤트 발생
            perror("epoll_wait");
        }
        for (i = 0;i < n; i++){
            if (client_list[i].data.fd == sockfd) {
                printf("Accept\n");
                client_sd = accept(sockfd, (struct sockaddr *)&clientaddr, & socklen);
                client_fds[client_cnt++] = client_sd;
                ev.events = EPOLLIN;
                ev.data.fd = client_sd;
                epoll_ctl(efd, EPOLL_CTL_ADD, client_sd, &ev);
            } else {
                readn = read(client_list[i].data.fd, buf_in, 255);
                if(readn <= 0){
                    epoll_ctl(efd, EPOLL_CTL_DEL, client_list[i].data.fd, client_list);
                    close(client_list[i].data.fd);
                    printf("Close fd\n");
                } else {
                    buf_in[readn] = '\0';
                    printf("read data %s\n", buf_in);
                    // write(client_list[i].data.fd, buf_in, readn);
                    for(int i = 0; i < client_cnt; i++){
                        write(client_fds[i], buf_in, readn);
                    }
                    if(strncmp(buf_in, "quit", 4) == 0) {
                        close(client_list[i].data.fd);
                    }
                }
            }   // else-end
         } // for-end
    } // while -end
    return 0;
}