## UDP
#### UDP Server/Client
* connectionless protocol
* 서버 동작 중이면 언제든 데이터 송수신 가능
* 속도를 요하는 음성/화상 데이터에 많이 사용
* 일회성 응답 서비스 등에서도 많이 사용
![[Pasted image 20260529094709.png]]
#### 소켓 생성
```c
#include <sys/types.h>
#include <sys/socker.h>

int socket(int domain, int type, int protocol);
```
* 첫 번째 인자 domain
	* AF_UNIX - 유닉스 도메인 소켓(로컬 통신)
	* AF_INET - IPv4 네트워크 도메인 소켓
	* AF_INET6 - IPv6 네트워크 도메인 소켓
* 두 번째 인자 type - 소켓 유형 지정, TCP는 스트림 타입 지정, UDP는 데이터 그램 유형 지정
	* SOCK_STREAM - 스트림 타입, TCP
	* SOCK_DGRAM - 데이터그램 타입, UDP
	* SOCK_RAW - RAW 타입, IP
* 세 번째 인자 protocol - 프로토콜 번호 지정, 통상 0
* 함수 호출 성공 시 소켓 디스크립터 반환, 실패 시 -1 반환
```c
int sockfd;

sockfd=socket(AF_INET, SOCK_DGRAM, 0);
if(sockfd==-1) {
	perror("socket");
	exit(1);
}
```
* 도메인 INET으로 유형 DGRAM => udp
* 성공 시 소켓 디스크립터 반환
#### 주소 설정
```c
#include <sys/types.h>
#include <sys/socket.h>

int bind(int sockfd, struct sockaddr *my_addr, socklen_t addrlen);
```
* 첫 번째 인자 sockfd - socket 함수 반환 값인 소켓 디스크립터 지정
* 두 번째 인자 myaddr - 소켓 주소 정보 가리키는 주소 지정, 소켓 생성 시 도메인 종류에 따라 결정
	* AF_UNIX - `struct sockaddr_un`
	* AF_INET - `struct sockaddr_in`
	* AF_INET6 - `struct sockaddr_in6`
* 세 번째 인자 addrlen - 소켓 주소 길이 지정
* 호출 성공 시 0 반환, 실패 시 -1 반환
```c
struct sockaddr_in myaddrl
my_addr.sin_family = AF_INET;
my_addr.sin_port = htons(60000);
my_addr.sin_addr.s_addr=htonl(INADDR_ANY);
memset(&(my_addr.sin_zero), '\0', 8);

if(bind(sockfd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr))==-1)
{
	perror("bind");
	exit(1);
}
```
#### 데이터 송수신
- sendto(), recvfrom() 함수 사용
```c
#include <sys/types.h>
#include <sys/socket.h>

int sendto(int sockfd, const void *buf, size_t len, int flag, const struct sockaddr *to, socklen_t tolen);

int recvfrom(int sockfd, const void *buf, size_t len, int flag, const struct sockaddr *from, socklen_t *fromlen);
```
- sendto() 함수의 다섯번째 인자 to에는 데이터를 전송할 소켓 주소 변수의 포인터
- 여섯번째 인자 tolen에는 소켓 주소 길이 전달
- recvfrom() 함수의 다섯번째 인자 from에는 데이터 보낸 상대방의 소켓 주소
- 여섯번째 인자 fromlen에는 상대방 소켓 주소의 크기 받아옴
- 두 함수 성공적으로 호출 - 실제로 전송 혹은 수신한 바이트 수 반환, 실패하면 -1 반환
- errno 변수를 확인하면 오류 원인 추적 가능
```c
while(1) {
	if(sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&to_addr, sizeof(to_addr)) == -1) {
	perror("sendto");
	break;	
}
	if((numbytes = recvfrom(sockfd, buf, MAXDATASIZE-1, 0, (struct sockaddr*)&from_addr, &sock_len))==-1) {
	perror("recvfrom");
	break;	
}
}
```
#### 연결 해제
- close, shutdown 이용
```c
int close(int sd);
int shutdown(int sd, int how);
```
- close 함수는 일반 파일 해제하듯이 소켓 디스크립터 전달해 해제
- 호출 시 해당 프로세스와 소켓과의 연결 해제
- 소켓 열어둔 타 프로세스가 있는 경우 모든 프로세스가 해제해야 실제로 소켓 종료 처리
- shutdown은 즉시 소켓 종료, 타 프로세스에 영향
- how
	- SHUT_RD - 읽기 채널 닫기
	- SHUT_WR - 쓰기 채널 닫기
	- SHUT_RDWR - 즉시 종료
## 입출력 다중화
#### 입출력 모드
* 블로킹 모드
	* 소켓 기본 모드로 네트워크로부터 데이서 수신하기 위해 recv() 호출한 경우
	* 상대방으로부터 데이터가 수신되지 않으면 해당 프로세스는 수행을 멈추고 기다림
	* 블록 현상은 각종 IO 함수에서 발생할 수 있으며 시스템 또는 네트워크의 어떤 조건이 만족할 때까지 기다리게 됨
* 넌 블로킹 모드
	* 입출력 함수를 이용해 데이터 송수신 할 수 있으면 즉시 실행
	* 불가한 경우에도 함수 안에서 블로킹 되지 않고 즉시 빠져나와 타 작업 수행할 수 있게 해주는 모드
	* 반환값을 이용해 오류 발생 여부 확인 가능
* 다중화 IO 모드
	* 입출력이 동시에 다중적으로/연속적으로 일어나는 경우
	* 시스템에서 이벤트 감지할 때 마다 입출력 함수를 수행하도록 하는 입출력 방법
#### 다중적인 입출력 해결
* 멀티 프로세스
	* 클라이언트 요청이 있을 때마다 fork() 시스템 콜 호출, 동시에 서비스가 이뤄지도록 구성
![[Pasted image 20260529120308.png]]
* 멀티 스레드
	* 클라이언트 요청이 있을 때마다 pthread_create() 함수 호출, 동시에 서비스 이뤄지도록 구성
![[Pasted image 20260529120339.png]]
* IO Multiplexing 함수
	* 각 소켓의 IO 이벤트 발생 검출
	* 별도의 프로세스나 스레드를 이용하지 않아 메모리 사용률 낮춤
	* 문맥 교환에도 영향을 주지 않아 시스템 성능 향상
![[Pasted image 20260529120424.png]]
#### IO Multiplexing - SELECT 방식
* 데이터 송수신을 위해 직접 입출력 함수 호출에 앞서 어떤 소켓에 입출력 이벤트가 일어났는지 모니터링
* 해당 소켓으로부터 데이터 송수신 방법
```c
#include <unistd.h>
#include <fcntl.h>

int select(int maxfd, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *tvptr);
```
* 첫 번째 인자인 maxfd에는 최대 파일(소켓) 디스크립터의 번호 + 1 지정
* 두 번째 인자 readfds에는 읽기 이벤트를 모니터링 할 파일 디스크립터 집합의 주소
* 세 번째 인자 writefds에는 쓰기 이벤트를 모니터링 할 파일 디스크립터 집합의 주소(통상 지정 안함)
* 네 번째 인자 exceptfds는 예외(오류) 이벤트를 모니터링 할 파일 디스크립터 집합 주소 지정
* 두 번째부터 네 번째 인자 사용 시 주의할 점
	* 함수 탈출 시 실제로 이벤트 발생한 디스크립터를 인자로 되돌려줌
	* 호출 시 전달된 값이 함수가 종료된 이후에 유지되지 않음
* 다섯번째 인자 tvptr에는 select 함수의 타임아웃 값에 대한 주소 지정
	* NULL 지정 시 이벤트 발생할 때까지 계속 모니터링
* 함수 성공 시 이벤트 발생된 파일 디스크립터의 개수 반환, 실패 시 -1
![[Pasted image 20260529120823.png]]
![[Pasted image 20260529120833.png]]
* select와 함께 사용되는 매크로 함수
	* FD_ZERO(fd_set \*fdset) - fdset 변수 초기화
	* FD_SET(int fd, fd_Set \*fdset) - fdset 변수에 fd 등록
	* FD_CLR(int fd, fd_set \*fdset) - fdset 변수로부터 fd 삭제
	* FD_ISSET(int fd, fd_set \*fdset) - fdset 중 fd가 설정 되어있는지 확인, select() 함수에서 벗어나 어떤 파일 디스크립터에 이벤트가 일어났는지 확인할 때 사용
## IOMultiplexing-POLL 방식
- poll() 함수는 모니터링 하고 싶은 디스크립터와 이벤트 종류를 미리 등록
- 등록된 디스크립터만 모니터링
```c
#include <poll.h>

int poll(struct pollfd *ufds, unsigned int nfds, int timeout);
```
* 첫 번째 인수 ufds - 이벤트 감지를 원하는 파일 디스크립터에 관한 정보 저장
```c
struct pollfd {
	int fd; // 감지를 원하는 디스크립터
	short events; // 감지할 이벤트 종류
	short revents; // 실제로 발생한 이벤트
}
```
* 이벤트 종류는 아래와 같음
	* POLLIN : 수신 데이터
	* POLLPRI : 긴급하게 읽을 데이터
	* POLLOUT : 송신 데이터
	* POLLERR : 오류 발생
	* POLLHUP : 연결이 끊어짐
	* POLLNVAL : 잘못된 요청
* 여러 이벤트를 지정해야 할 때는 events 멤버에 비트 OR 연산자인 |를 이용해 추가 가능
* revents 멤버는 실제로 발생된 이벤트를 받아오는 멤버
* 두 번째 인자 nfds : 이벤트 검출을 원하는 파일 디스크립터 개수 지정
* 세 번째 인자 timeout : select 함수의 time out과 유사한 의미 가짐
	* -1인 경우 이벤트 검출될 때까지 블록
	* 0인 경우 이벤트 발생된 파일 디스크립터 확인만 하고 즉시 반환
	* 양수인 경우 지정된 초 수 만큼 이벤트 모니터링
* 반환 값이 -1인 경우 함수가 실패
* 0인 경우 이벤트 발생된 파일 디스크립터 없이 타임아웃된 경우
* 양수인 경우 이벤트가 감지된 파일 디스크립터 개수
