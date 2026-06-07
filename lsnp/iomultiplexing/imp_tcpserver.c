#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <pthread.h>

#define BACKLOG 10

void chatting(int sd)
{
    fd_set fdset, fdset1;
    FD_ZERO(&fdset);
    FD_SET(0, &fdset);
    FD_SET(sd, &fdset);
    fdset1 = fdset;
    int MAX = 100;
    char buf[MAX];
    int numbytes;

    while(1)
    {
        fdset = fdset1;
        select(sd+1, &fdset, NULL, NULL, NULL);
        if(FD_ISSET(0, &fdset)){
            fgets(buf, MAX, stdin);
            send(sd, buf, strlen(buf), 0);
        }else if (FD_ISSET(sd, &fdset)){
            numbytes = recv(sd, buf, MAX-1, 0);
            if(numbytes == 0) {
                printf("connection closed\n");
                break;
            }
            else if (numbytes == -1) {
                perror("recv");
                exit(1);
            }
            buf[numbytes] = '\0';
            printf("client: %s", buf);
        }else {
            perror("select");
            exit(1);
        }
        printf("input your message : ");
        fflush(stdout);
    }
}

int main(void)
{
    struct sockaddr_in myaddr; // 서버 소켓 선언
    struct sockaddr_in client_addr; // 클라이언트 소켓 선언
    pthread_t tid; // 스레드 식별자 선언

    int sockfd; // 서버 소켓 파일 디스크립터 선언
    int newfd; // 클라이언트 소켓 파일 디스크립터 선언
    socklen_t sin_size; // accept 인자로 쓰기 위한 accept 구조체 크기 변수 선언 -> accept 두번째 인수는 클라이언트의 소켓 주소를 받아올 공간의 주소 요구


    sockfd = socket(AF_INET, SOCK_STREAM, 0); // AF_INET은 IP, SOCK_STERAM은 TCP, 0은 프로토콜 -> 성공시 0 이상 반환(파일 디스크립터)
    if (sockfd == -1) {
        perror("socket");
        exit(1);
    }

    memset(&myaddr, 0, sizeof(myaddr)); // 구조체를 초기화함 <- bind 성공 시 두 번째 인자
    myaddr.sin_family = AF_INET; // IP 버전을 명시 => sin_family는 도메인의 종류를 지정함
    myaddr.sin_port = htons(60000); // 16비트의 포트 번호를 명시
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY); // 32비트 IP주소 명시 <- any는 현재 서버가 실행되고 있는 컴퓨터의 모든 IP를 의미
    //htonl은 long 자료형의 데이터를 네트워크 바이트 순서에서 호스트 바이트 순서로 변환함
    //Host Byte Order : Cpu architecture에 따라 편이함 -> 리틀/빅 엔디안
    //Network Byte Order : 네트워크 순서는 항상 빅 엔디안을 사용하기로 약속(프로토콜 규약)
    //htons은 short 자료형의 데이터를 네트워크 바이트 순서에서 호스트 바이트 순서로 변환함
    //ntohl, ntohs은 호스트 바이트 순서에서 네트워크 바이트 순서로 변환

    if (bind(sockfd, (struct sockaddr *)&myaddr, sizeof(myaddr)) == -1) { //bind 성공 시 2번째 인자에서 네트워크 정보 받아옴
        perror("bind");
        close(sockfd);
        exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1) { // 연결 요청 큐 설정, BACKLOG는 대기열의 최대 크기를 명시
        perror("listen");
        close(sockfd);
        exit(1);
    }

    while (1) {
        sin_size = sizeof(client_addr); // accept 인자로 쓰기 위한 accept 구조체 크기 변수 선언, accept는 포트를 성공적으로 받아오면 client_addr에 클라이언트의 정보를 담음

        newfd = accept(sockfd, (struct sockaddr *)&client_addr, &sin_size); // accept는 클라이언트가 연결 요청을 보내면 새로운 통로를 뚫어줌
        if (newfd == -1) {
            perror("accept");
            continue;
        }

        printf("server: got connection from %s\n",
               inet_ntoa(client_addr.sin_addr));

        chatting(newfd);
    }

    close(sockfd);
    return 0;
}