#include <stdio.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <poll.h>

#define PORT1 60000
#define PORT2 60001
#define MAXDATASIZE 100

/* 쓰레드에 전달할 데이터 구조체 */
struct msg_data {
    char ip[32];
    char message[MAXDATASIZE];
};

void* msg_collect(void* arg);

int main(void)
{
    int sockfd1, sockfd2;
    struct sockaddr_in myaddr1, myaddr2;
    struct pollfd pollfds[2];
    int s_count, i;

    /* 60000 포트 소켓 생성 및 바인드 */
    sockfd1 = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd1 == -1) {
        perror("socket 60000");
        exit(1);
    }
    memset(&myaddr1, 0, sizeof(myaddr1));
    myaddr1.sin_family = AF_INET;
    myaddr1.sin_port = htons(PORT1);
    myaddr1.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sockfd1, (struct sockaddr *)&myaddr1, sizeof(myaddr1)) == -1) {
        perror("bind 60000");
        close(sockfd1);
        exit(1);
    }

    /* 60001 포트 소켓 생성 및 바인드 */
    sockfd2 = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd2 == -1) {
        perror("socket 60001");
        close(sockfd1);
        exit(1);
    }
    memset(&myaddr2, 0, sizeof(myaddr2));
    myaddr2.sin_family = AF_INET;
    myaddr2.sin_port = htons(PORT2);
    myaddr2.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sockfd2, (struct sockaddr *)&myaddr2, sizeof(myaddr2)) == -1) {
        perror("bind 60001");
        close(sockfd1);
        close(sockfd2);
        exit(1);
    }

    printf("UDP server listening on ports %d and %d...\n", PORT1, PORT2);

    /* poll 설정 */
    pollfds[0].fd = sockfd1;
    pollfds[0].events = POLLIN;
    pollfds[1].fd = sockfd2;
    pollfds[1].events = POLLIN;

    while (1) {
        s_count = poll(pollfds, 2, -1);
        if (s_count <= 0) {
            perror("poll");
            break;
        }

        for (i = 0; i < 2; i++) {
            if (pollfds[i].revents & POLLIN) {
                struct sockaddr_in from_addr;
                socklen_t fromlen;
                char recv_msg[MAXDATASIZE];
                int numbytes;
                struct msg_data *data;
                pthread_t thread;

                fromlen = sizeof(from_addr);
                numbytes = recvfrom(
                    pollfds[i].fd,
                    recv_msg,
                    MAXDATASIZE - 1,
                    0,
                    (struct sockaddr *)&from_addr,
                    &fromlen
                );

                if (numbytes == -1) {
                    perror("recvfrom");
                    continue;
                }

                recv_msg[numbytes] = '\0';

                printf("%d bytes from %s:%d (Port: %d)\n",
                       numbytes,
                       inet_ntoa(from_addr.sin_addr),
                       ntohs(from_addr.sin_port),
                       (i == 0) ? PORT1 : PORT2);

                printf("client message: %s\n", recv_msg);

                /* 쓰레드에 전달할 데이터 메모리 할당 */
                data = (struct msg_data *)malloc(sizeof(struct msg_data));
                strcpy(data->ip, inet_ntoa(from_addr.sin_addr));
                strcpy(data->message, recv_msg);

                /* 수신된 메시지를 msg_collect 쓰레드로 전송 */
                pthread_create(&thread, NULL, msg_collect, (void *)data);
                pthread_detach(thread);

                /* 클라이언트에 응답 전송 */
                const char *msg = "Message received by UDP server";
                if (sendto(
                        pollfds[i].fd,
                        msg,
                        strlen(msg),
                        0,
                        (struct sockaddr *)&from_addr,
                        fromlen
                    ) == -1) {
                    perror("sendto");
                }
            }
        }
    }

    close(sockfd1);
    close(sockfd2);
    return 0;
}

/* 수신한 메시지를 포맷팅하여 로그 파일에 저장하는 쓰레드 함수 */
void* msg_collect(void* arg)
{
    struct msg_data *data = (struct msg_data *)arg;
    time_t rawtime;
    struct tm *timeinfo;
    char time_str[100];
    FILE *log_file;

    /* 현재 시간 구하기 */
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    /* 2002년 09월 30일 10:34:36 형식으로 시간 문자열 변환 */
    strftime(time_str, sizeof(time_str), "%Y년 %m월 %d일 %H:%M:%S", timeinfo);

    /* 로그 파일 열기 (이어쓰기 모드) */
    log_file = fopen("msg.log", "a");
    if (log_file != NULL) {
        /* 날짜 IP 클라이언트 메시지 순으로 저장 */
        fprintf(log_file, "%s %s %s\n", time_str, data->ip, data->message);
        fclose(log_file);
    } else {
        perror("fopen (msg.log)");
    }

    /* 할당한 메모리 해제 */
    free(data);
    pthread_exit(NULL);
    return NULL;
}
