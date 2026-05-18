#### 저수준 vs 고수준의 입출력 방식
![[Pasted image 20260518091521.png]]
-> 버퍼 사용 이유
* I/O 디스크에 직접 접근해서 파일 입출력 진행
	* 오버헤드 발생으로 인한 지연 발생 -> 속도 느림
	* 버퍼를 통한 디스크 접근 최소화를 통한 속도 개선
* 보통의 장치 사용 시 Low Level 입출력 진행

| 기준       | 고수준             | 저수준           |
| -------- | --------------- | ------------- |
| 파일 지시자   | 파일 포인터(FILE \*) | 파일 디스크립터(int) |
| 버퍼 사용 유무 | 사용              | 사용 안함         |
| 세밀한 제어   | 어려움             | 쉬움            |
| 입출력 단위   | 스트림             | 바이트           |
| 표준화 여부   | ANSI 표준         | 비 표준          |
* 고수준 입출력 함수
![[Pasted image 20260518092957.png]]
#### 저수준 파일 입출력 함수
```c title="open()"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int open(const char *path, int oflags, (mode_t mode));
int close(int fd)
```
* open함수는 일반 파일이나 장치 파일 등에 대한 접근 경로를 만들어주는 함수
	* 오픈 플래그를 인수로 전달, 접근 경로로 파일 디스크립터를 반환
* close 함수는 파일의 접근 경로를 해제할 때 사용
	* open 함수의 리턴 값인 파일 디스크립터를 인수로 전달
* 파일 입출력은 모두 파일 디스크립터를 이용해 수행
	* 0, 1, 2는 표준 입력, 표준 출력, 표준 오류 장치로 예약
	* 0이상, -1 반환 시 open() 함수 실패 의미
* 오픈 플래그
	* ![[Pasted image 20260518093425.png]]
* 매번 디스크 입출력 요청을 하면 오버헤드 발생
	* 매번 실제 반영도 안되고, 특정 시간 마다 반영
	* 수정하자마자 디스크에 저장해야하는 경우 O_SYNC를 사용
	* 성능 저하 발생 -> 디스크 입출력이 발생
![[Pasted image 20260518094007.png]]
* 두 프로세스 모두 동일한 파일 open 수행 중
* 디스크립터 0, 1, 2 모두 예약 할당, 3번 할당
* 경로 탐색으로 inode를 찾고, 그 inode를 참조하는 open file description을 만들고, 프로세스 fd table이 그 open file description을 가리킨다
* open함수는 하나의 경로의 역할
* 디스크립터 번호 3은 전역 번호가 아닌, 프로세스의 내부 번호
#### 저수준 파일 입출력 함수
* read(), write()
	* open()함수를 이용해 파일 열기 성공하면 파일의 내용을 읽어오거나 저장할 때 read(), write() 함수 사용 가능
```c 
#include <unistd.h>

size_t read(int fd, const void *buf, size_t nbytes);
size_t write(int fd, const void *buf, size_t nbytes);
```
	 * read 함수는 fd로 연결된 파일로부터 nbytes 만큼 데이터 읽어 buf에 저장하는 함수
		* 실제로 읽어들인 크기를 반환
		* 더 이상 읽을 것이 없으면 0, 호출 시 문제 발생된 경우 -1 반환
	 * write 함수는 buf에 있는 내용을 nbytes만큼 fd에 연결된 파일에 저장하는 함수
		* 실제로 저장된 바이트 수 반환
		* 아무것도 저장 하지 않았을 때 0, 저장시 오류가 발생하면 -1 반환
* lseek() 함수
	* 순차적인 접근이 아닌 임의의 접근일 필요한 경우 사용
```c
#include <sys/types.h>
#include <unistd.h>

off_t lseek(int fd, off_t offset, int whence);
```
	* fd는 파일 디스크립터를, offset은 whence를 기준으로 한 옵셋, whence는 기준 위치를 의미
	* whence에 설정 가능한 값은 다음과 같음
		* SEEK_SET-0-파일의 시작 위치
		* SEEK_CUR-1-파일 포인터의 현 위치
		* SEEK_END-2-파일의 마지막 위치
## 특수 파일 제어
#### 터미널 장치의 속성 제어
* 리눅스에서 장치 드라이버를 개발하는 경우 파일 입출력 함수 이외에 ioctl() 함수에 대응되는 장치 제어 함수 만들음
* 각 속성을 제어하기 위한 명령 구현 필요
* 사용자들은 ioctl() 함수를 통해 약속된 명령을 전달, 장치의 속성 제어 가능
```c title=ioctl
#include <termio.h>
int ioctl(int fd, int request, struct termios *tbuf);
```
* request 종류
	* TCGETA : 터미널 속성 정보를 termio 구조체 변수 tbuf에 읽어 옴
	* TCSETA : tbuf에 지정된 값을 터미널 장치에 설정
	* TCSETAW : 새로운 속성정보를 설정하기 전에 출력이 완전히 끝나기를 기다림
	* TCSETAF : 입출력 버퍼에 있는 데이터를 모두 처리한 후 새로운 속성 정보로 설정
* ![[Pasted image 20260518113442.png]]
* termio 구조체 자료형
* Canonical Mode -> 줄 단위 처리, Enter 이전까지 자체 편집 가능, 제어 문자 활성화
* Non-Canonical Mode : 키를 누르는 즉시 문자 인식, vi 등에서 사용
* 플래그들
* ![[Pasted image 20260518113808.png]]
* ![[Pasted image 20260518114543.png]]
* Canonical Mode에서 사용하는 제어 문자들
* ![[Pasted image 20260518114601.png]]
* Non-Canonical Mode에서 사용
	* Canonical Mode에서는 EOF, Enter를 활용해 명령어 입력
	* Non-Canonical Mode에서는 입력 문자는 최소 Min, 1/10s TIME 배의 시간이 경과하면 입력 문자가 프로그램에 전달
#### 파일 중첩
* 서로 다른 파일 디스크립터가 동일한 파일을 접근 할 서 있게
* dup(), dup2() 함수가 해당 기능 찹재
* 파이프를 이용한 프로세스 간의 통신이나 소켓 통신에도 적용해 사용 가능
```c
#include <unistd.h>
int dup(int fd);
int dup2(int tofd, int formfd); // fd2 먼저 close, 이후 fd1 clsoe
```
* 유용한 파일 디스크립터 중 가장 낮은 번호의 파일 디스크립터 찾음
* 인수로 전달할 파일 디스크립터에 설정된 정보를 앞서 찾아낸 디스크립터로 복사
* 하나의 파일을 두 개의 디스크립터로 중첩 시킴
* file open 재사용 가능 및 socket에서 파일 디스크립터 받아오는 등 활용 가능
![[Pasted image 20260518121204.png]]
## 디렉토리 제어
#### 디렉토리 구조
```c
struct dirent {
	ino_t d_ino; // inode num
	off_t d_off; // dir stream 위치
	unsigned short d_reclen; // record total size
	char d_name[256]; // file name
}
```
* opendir(), closedir()
	* opendir 함수는 디렉토리 파일에 접근이 가능하게 해주는 함수
```c
#include <sys/types.h>
#include <dirent.h>

DIR *opendir(const char *name);
int closedir(DIR* dirp);
```
	* 성공 시 디렉토리 파일을 읽을 수 있는 DIR \*의 포인터 반환
	* 실패 시 NULL
	* 접근 해제 시 closedir()함수 사용, opendir의 반환 값을 인수로 전달
* readdir()
	* 디렉토리 파일 안에 있는 엔트리 읽을 수 있음
```c
#include <sys/types.h>
#include <dirent.h>

struct dirent *readdir(DIR* dirp);
```
	* 디렉토리 엔트리 순차적으로 읽어 반환, 끝까지 다 읽으면 NULL 반환
	* 엔트리로 읽어온 각 파일에 대한 세부 항목은 stat 함수를 이용해 알 수 있음
- mkdir(), rmdir()
	- 디렉토리 생성/삭제
```c
#include <sys/stat.h>
int mkdir(const char* path, mode_t mode);

#include <unistd.h>
int rmdir(const char* path);
```
	* unlink와 달리 하위 디렉토리 및 파일이 있으면 rm 실패
* chdir(), getcwd()
	* 프로그램 수행하다 타 디렉토리로 이동하는 경우 chdir 사용
	* 현 작업 디렉토리 경로 확인 시 getcwd() 함수
```c
#inlcude <unistd.h>

int chdir(const char* path);

char* getcwd(char *buf, size_t size);
```
	* chdir()에는 변경하고자 하는 경로 명을 인수로 전달
	* 성공 시 0, 실패시 -1, 오류 원인은 errno 변수에 설정
	* getcwd()는 현 경로 위치를 첫 인수 buf에 전달
	* 두 번째 인수 size로 전달하는 크기보다 경로명이 긴 경우 NULL 반환
	* 오류 원인은 errno 변수에 설정
## 프로세스
#### 프로세스 정의
* 실행중인 프로그램을 프로세스라 함
* 프로그램을 실행하는데 필요한 모든 환경을 통틀어 말하는 것
* 해당 환경을 이미지 또는 컨텍스트라고 함
* 프로그램과 그 실행 환경, 이미지를 구성하고 있는 요소들
![[Pasted image 20260518150122.png|314]]
* 사실 파일 디스크립터는 구조체로 구성되어있음
* task structer
	* 구조체 안에 구조체 존재
	* 개발자에게는 단순화 시켜 보여줌
	* 이를 context, image라고 말함
* 리눅스 OS는 여러 사용자가 동시에 엑세스 가능한 멀티유저 시스템
* 여러 프로그램이 동작되거나 같은 프로그램이 동시에 여러 프로세스로 수행될 수도 있음
* 리눅스 시스템에서는 코드 영역과 라이브러리는 프로세스간 공유
* 메모리 내에 코드와 라이브러리는 하나만 존재
![[Pasted image 20260518150426.png]]
* 일반적으로 리눅스에서 프로세스는 부모 프로세스에 의해 생성
* 가장 조상이 되는 프로세스는 systemd로 PID가 1
* 자식 프로세스를 생성해 프로그램을 수행하는 방법은 fork, wait, exec 함수 이용 구현
* <프로세스 상태 코드>

| 상태코드 | 의미               |
| ---- | ---------------- |
| D    | 중단 시킬 수 없는 대기 상태 |
| R    | 준비 또는 실행 상태      |
| S    | 대기 상태            |
| T    | 멈춤 상태            |
| W    | 페이징 중            |
| X    | 종료               |
| Z    | 좀비               |
```
PROCESS STATE CODES
       Here are the different values that the s, stat and state output
       specifiers (header "STAT" or "S") will display to describe the
       state of a process:

               D    uninterruptible sleep (usually IO)
               I    Idle kernel thread
               R    running or runnable (on run queue)
               S    interruptible sleep (waiting for an event to
                    complete)
               T    stopped by job control signal
               t    stopped by debugger during the tracing
               W    paging (not valid since the 2.6.xx kernel)
               X    dead (should never be seen)
               Z    defunct ("zombie") process, terminated but not
                    reaped by its parent
```
#### 프로세스 생성
* system(), fork() 사용
* system() func
	* 새로운 명령이나 프로그램 수행
```c
#include <stdlib.h>
int system(const char *string);
```
	* string에 명시한 명령이나 프로그램 수행 후 종료 대기
	* system()함수 리턴 값은 string에 표햔된 명령의 수행 결과를 의미
	* 0 반환 시 정상, 0이 아닌 값 반환 시 비정상

* fork() func
	* 프로세스 여러 개 동시에 수행하면 여러 작업 한번에 처리 가능
```c
#include <unistd.h>
pid_t fork(void);
```
	* fork 함수 수행 시 리눅스 커널에서는 함수를 호출한 프로세스와 동일하게 구성된 새 프로세스 생성
	* 호출한 쪽을 부모 프로세스, 새로 생성된 쪽을 자식 프로세스라 함

![[Pasted image 20260518152945.png]]
- fork()는 현재 프로세스가 커널에 요청하여 자식 프로세스를 생성하는 시스템 콜

- 자식 프로세스는 부모 프로세스와 거의 같은 실행 상태에서 시작함
  - 같은 프로그램 코드/주소공간 내용을 가진 상태로 생성됨
  - 단, 부모와 자식은 서로 독립된 프로세스이며 별도의 가상 주소 공간을 가짐

- 자식 프로세스는 고유한 PID를 가짐
- 자식 프로세스의 PPID는 부모 프로세스의 PID로 설정됨

- fork() 반환값
  - 부모 프로세스: 자식 프로세스의 PID 반환
  - 자식 프로세스: 0 반환
  - 실패 시: -1 반환, 자식 프로세스 생성 안 됨

- fork() 이후 부모와 자식은 fork() 호출 직후 지점부터 각각 실행됨
  - fork 이전 코드로 되돌아가서 다시 실행하지 않음
  - 둘 중 어느 프로세스가 먼저 실행될지는 보장되지 않음

- 데이터/힙/스택은 부모와 같은 값으로 복사된 것처럼 시작하지만 이후 독립적으로 동작함
  - Linux에서는 보통 Copy-on-Write 방식으로 실제 복사를 지연함

- 파일 디스크립터 테이블은 자식에게 복사됨
  - 단, 각 fd는 부모와 같은 open file description을 참조함
  - 따라서 파일 offset, open status flag 등은 부모/자식이 공유할 수 있음

- signal handler 설정과 signal mask는 상속됨
  - 단, pending signal은 상속되지 않음

- 부모와 자식은 fork() 반환값으로 구분함

- system(command)는 쉘을 통해 command를 실행하고 명령 종료까지 기다림
  - 내부적으로 fork + exec + wait 흐름으로 이해 가능

* fork 실패 시 -1 반환 -> 메모리 부족, 자식 프로세스 개수 제한
	* 전자의 경우 eerrno 변수에 ENOMEM, 후자의 경우 EAGAIN 설정

![[Pasted image 20260518160732.png]]
* 자식 프로세스가 보낸 시그널을 부모 프로세스가 받지 못하게 되면 자식 프로세스는 좀비
* 좀비 상태에 있는 프로세스가 문제는 없음, 점점 늘어나면 생성 할 수 없는 경우 발생
* 리눅스에는 최대 프로세스 개수 설정
* 프로세스 전체 개수가 최대치에 이르게 되면 더 이상 작업 수행 불가
#### 프로세스 종료
* wait, waitpid, exit
* wait 함수
```c
#include <sys/types.h>
#include <sys/wait.h>

pid_t wait(int* stat_loc);
```
* wait 함수를 호출하며 자식 프로세스가 시그널을 보낼 때까지 부모 프로세스의 수행 중지
* 자식 프로세스로부터 시그널이 도착하면 함수를 빠져나오면서 시그널을 보낸 자식 프로세스의 PID를 반환
* 존재하지 않는 경우 -1 반환, errno 변수에 ECHILD 설정
![[Pasted image 20260518161546.png]]

* waitpid() 함수
	* 자식 프로세스로부터 신호가 오기 전에 부모 프로세스에서 수행해야 할 내용이 있다면 waitpid 함수 이용
```c
#include <sys/types.h>
#include <sys/wait.h>

pid_t waitpid(pid_t pid, int *stat_loc, int option);
```
![[Pasted image 20260518162616.png]]
	- waitpid() 함수에서는 wait()함수에서 설정할 수 없었던 특정 프로세스에 대한 설정이나 자식 프로세스로부터 시그널이 도착될 때까지 동작 조정 가능
	- 사용 예시
		- `waitpid(1023, NULL, WNOHANG);`
		- 종료 신호를 보내지 않은 경우 0 반환(현재 실행 중)
		- 오류 발생 시 -1 반환, errno 변수에 다음과 같은 값 설정
![[Pasted image 20260518162845.png]]

* exit() 함수
	* 자신을 종료할 때 사용하는 함수
```c
#include <stdlib.h>
void exit(int status);
```

	- exit 함수의 인수 status는 wait이나 waitpid 함수를 이용해 자식 프로세스의 종료를 기다리는 부모 프로세스에 전달
	- 일반적으로 정상적인 종료일 때 status에 0, 비정상적인 종료일 때는 0-255값
	- 지금까지 사용하던 입출력 버퍼 비우고, open 되어있는 파일 디스크립터 모두 close, 마지막에 부모 프로세스에 SIGCHLD 시그널 전송
	- wait 또는 waitpid를 이용해 시그널 처리해줘야 함
