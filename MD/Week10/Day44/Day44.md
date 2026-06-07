## TCP/IP Protocol
#### Protocol?
* 서로 다른 컴퓨터 사이에서 정보를 전송하기 위한 통신 규약
* OSI 7 Layer 발표, 각 Layer를 기능별로 독립
* 각 Layer와 Layer 사이에 상호 연결성과 호환성 확보
* Architecture, OS와 상관 없이 원활한 Data 전송이 가능하도록 표준안 근거
* 가장 널리 사용되고 있는 프로토콜은 인터넷의 기본 프로토콜인 TCP/IP 프로토콜
![[Pasted image 20260528103518.png]]
![[Pasted image 20260528103623.png]]
##### TCP/IP 프로토콜 스택
* TCP(Transmission Control Protocol)
	* Connection-Oriented Protocol
		* 3-way handshake
		* Virtual Circuit
		* Data 전송 전 반드시 논리적인 연결 수립
	* 메시지 일련번호(Sequence Number)와 응답 번호(Acknowledgement Number)를 이용한 신뢰성 있는 전송
	* Windows Size 이용한 흐름 제어
	* 데이터 전달 확인 가능 -> 신뢰성
#### TCP Header Format
![[Pasted image 20260528110054.png]]
#### UDP Protocol
* Connectionless Protocol
	* 사전 절차 불필요
* 데이터 전달 확인 불가 -> 신뢰성 저하
* 응용 계층과의 오버헤드 없음 -> 신속한 처리 장점
![[Pasted image 20260528110143.png]]
![[Pasted image 20260528110225.png]]
## 네트워크 설정 파일과 도구
#### 네트워크 설정 파일
* /etc/hostname
	* 호스트 명 저장
* /etc/hosts
	* 호스트명, IP 주소에 대한 테이블 등록
* /etc/resolv.conf
	* DNS서버 IP주소 등록
* /etc/services
	* TCP/UDP 프로토콜의 각종 서비스 명과 포트 번호 저장
#### 네트워크 진단도구
* 네트워크 인터페이스 정보 확인 및 변경 도구
* ifconfig
	* ifconfig \[interface_name] \[ip addr] \[netmask subnet addr] up/down
![[Pasted image 20260528112908.png]]
* 네트워크 상태 확인 도구
	* ss \[option]
![[Pasted image 20260528113058.png]]
#### TCP 상태 천이도
![[Pasted image 20260528113143.png]]
![[Pasted image 20260528113149.png]]
* 패킷 수집 도구 - tcpdump, wireshark
	* 네트워크 상에서 주고받는 패킷 분석 도구
	* text -> tcpdump
	* gui -> wireshark
![[Pasted image 20260528120047.png]]
![[Pasted image 20260528120100.png]]
## Socket
#### socket
* 네트워크를 통해 요구되는 다양한 정보의 송수신 서비스를 위해 생성되는 논리적인 인터페이스, TCP/IP 프로토콜 기반
![[Pasted image 20260528124106.png]]
#### Socket의 Domain 유형
* 소켓은 크게 도메인과 유형으로 구분
* 도메인 - 소켓으로 통신이 가능한 영역
* 유형 - 전송 방식에 관련된 구분
![[Pasted image 20260528124147.png]]
![[Pasted image 20260528124158.png]]
![[Pasted image 20260528124525.png]]
* 범용 자료형
```c
struct sockaddr {
	sa_family_t sin_family;
	char sa_data[];
};

struct sockaddr_storage {
	sa_family_t sin_family;
	//정렬을 위한 패딩 추가
}
```
#### 소켓주소
```c
struct sockaddr_in server_addr;

if(connect(socksd, (struct sockaddr*)&server_addr),
sizeof(server_addr)==-1){
	perror("connect");
	return 1;
}
```
* server_addr 변수는 소켓 주소의 자료형인 struct sockaddr_in으로 선언된 변수
* connect 함수 원형에 맞춰 두 번째 인자로 전달 시 struct sockaddr 자료형으로 캐스팅해 전달
## 소켓 정보 관련 함수
#### 바이트 순서 변환 함수
* CPU 아키텍처에 따라 저장/읽어오는 순서 편이
* 호스트 바이트 순서라 함
* 빅/리틀 엔디안 존재
* 빅 - 낮은 번지에서부터 데이터 저장
* 리틀 - 높은 번지에서부터 저장
![[Pasted image 20260528140525.png]]
* 빅엔디안 - 가독성 좋음, 대소비교 빠름
* 리틀 엔디안 - 산술 연산 빠름
## 리눅스 네트워크 프로그래밍
#### TCP Server/Client
* TCP는 connection oriented 프로토콜
* 서버는 클라이언트의 연결 요청을 기다리는 상태가 되어 있어야 함
* 서버 상태가 준비되어있다면 클라이언트에서 요청 시 연결 수립
* 데이터 송수신 가능
* 수신 완료되면 일반적으로 클라이언트에서 연결 종료, 서버는 무한 루프 구조 반복

* TCP server
socket() -> blind() -> listen() -> accept() -> send()/recv -> listen-accept
* TCP Client
socker() -> connect() = 연결요청 - accept() ->

#### TCP Socket API
* 소켓 생성
```c
#include <sys/types.h>
#include <sys/socket.h>

int socket(int domain, int type, int protocol);
```
* 첫 번째 인자 domain에 사용하는 도메인 종류 지정
	* AF_UNIX : 유닉스 도메인 소켓
	* AF_INET : IPv4 네트워크 도메인 소켓
	* AF_INET6 : IPv6 네트워크 도메인 소켓
* 두 번째 인자인 type에는 소켓 유형 지정
	* SOCK_STREAM : 스트림 타입, TCP
	* SOCK_DGRAM : 데이터그램 타입, UDP
	* SOCK_RAW : RAW 타입, IP
* 세 번째 인자인 protocol에는 번호 지정 (통상 0)
	* 성공 시 소켓 디스크립터, 실패시 -1 반환
```c
int sockfd;

sockfd = socket(AF_INET, SOCK_STREAM, 0);
if(sockfd == -1) {
	perror("socket");
	exit(1);
}
```

* 주소 설정
```c
#include <sys/types.h>
#include <sys/socket.h>

int bind(int sockfd, struct sockaddr *my_addr, socklen_t addrlen);
```
* 클라이언트 -> 서버 연결 요청 시 서버 특정 소켓에서 응답하려면 IP 주소와 포트 번호 지정
* 첫 번째 인자 sockfd - socket() 함수의 반환 값, 소켓 디스크립터 지정
* 두 번째 인자 myaddr - 소켓 주소의 저옵 가리키는 주소 지정
	* AF_UNIX : struct sockaddr_un
	* AF_INET : struct sockadd_in
	* AF_INET6 : struct sockaddr_in6
	* 소켓 주소의 자료형 다름 -> 범용 자료형 struct sockaddr로 캐스팅
* 세 번째 인자 addrlen은 소켓 주소 길이 지정
	* 성공 0, 실패 -1
```c
struct sockaddr_in myaddr;
my_addr.sin_family = AF_INET;
my_addr.sin_port = htons(60000);
my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
memset(&(my_addr.sin_zero), '\0', 8);

if(bind(sockfd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr))==-1) {
	perror("bind");
	exit(1);
}
```

* 백 로그(backlog) 큐 생성
```c
#include <sys/socket.h>

int listen(int sockfd, int backlog);
```
* listen() 함수는 서버에서 클라이언트의 요청을 받아들이기 위해 준비하는 함수
* 백로그 큐 생성 -> 연결을 요청한 클라이언트의 정보 저장
* 첫 번째 인수 sockfd - 소켓 디스크립터 지정
* 두 번째 인수 backlog - 백 로그 큐의 크기 지정
* 함수 호출 성공 시 0 반환, 실패 시 -1 반환

* 연결 수립
```c
#include <sys/types.h>
#include <sys/socket.h>

int accept(int sockfd, struct sockaddr *client_addr, socklen_t *addrlen);
```
* 첫 번째 인수 sockfd에는 소켓 디스크립터 지정
* 두 번째 인수 client_addr에는 연결을 요청한 클라이언트 소켓 주소 받아올 공간 주소 전달
* 세 번째 인수 addrlen에는 클라이언트의 소켓 주소 길이를 받아올 공간의 주소 전달
* 성공적 호출 -> 새로운 소켓 디스크립터 반환
	* 소켓 디스크립터로 데이터 송수신
	* socket() 함수에서 반환 소켓 디스크립터는 타 클라이언트의 연결을 대기하는 디스크립터로 사용
```c
their_addr.sin_family=AF_INET;
their_addr.sin_addr.s_addr = inet_addr("192.168.1.10");
memset(&(their_addr.sin_zero), '\0', 8);
if(connect(sockfd, (struct sockaddr*)&their_addr, sizeof(struct sockaddr))==-1) {
	perror("connect");
	exit(1);
}
```

* 데이터 송수신
```c
#include <sys/types.h>
#include <sys/socket.h>

int send(int sockfd, const void *buf, size_t len, int flag);
int recv(int sockfd, const void *buf, size_t len, int flag);
```
![[Pasted image 20260528152640.png]]

* 연결 해제
```
int close(int sd);
int shutdown(int sd, int how);
```
![[Pasted image 20260528152715.png]]
