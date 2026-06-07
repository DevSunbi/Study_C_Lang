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
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // newfd는 여러 스레드가 접근하면 꼬임 -> mutex로 잠궈두기

void* message_thread(void* arg)
{
    int newfd = *(int *)arg; // fd는 int형임 함수 자체의 리턴은 없으니까 타입 변환
    
    const char *msg = "Hello Client!"; // 불변, 포인터 변수 메세지 선언 -> send 자체가 보낼 데이터가 들어있는 메모리 주소를 요구
    if (send(newfd, msg, strlen(msg), 0) == -1) { // accept로 받은 newfd를 이용, msg를 길이만큼 전송
        perror("send");
    }
    close(newfd); // 클라이언트 소켓 닫기
    return NULL; // 스레드 리턴(void)
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

        pthread_mutex_lock(&mutex); // newfd 쓰는 동안 다른 애들이 못건드리게 잠굼
        newfd = accept(sockfd, (struct sockaddr *)&client_addr, &sin_size); // accept는 클라이언트가 연결 요청을 보내면 새로운 통로를 뚫어줌
        if (newfd == -1) {
            perror("accept");
            continue;
        }

        printf("server: got connection from %s\n",
               inet_ntoa(client_addr.sin_addr));
            
        if(pthread_create(&tid, NULL, message_thread, &newfd)) { // 클라이언트에게서 받아온 newfd를 인자로 thread 실행
            perror("pthread_create");
            exit(1);
        }
        pthread_mutex_unlock(&mutex); // 다 썼으니 유기
    }

    close(sockfd);
    return 0;
}