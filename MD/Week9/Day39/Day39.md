#### 프로세스 교체
* exec 함수
	* 현 수행중인 프로세스를 새 프로세스로 교체하는 경우 exec() 함수 사용
```c
#include <unistd.h>

int execl(const char *path, consst char *argv(), ..., (char*)0);
int execlp(const char *file, consst char *argv(), ..., (char*)0);
int execle(const char *path, consst char *argv(), ..., (char*)0, char *const envp[]);

int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
int execve(const char *path, char * const argv[], char *const envp[]);
```
	* 첫 번째 인수는 실행 파일 저장, 두 번째 인수부터는 실행파일을 실행하는 인수 지정
# exec_ 계열 함수 의미

| 구분  | 의미                                                                                                                                                                                                                  |
| --- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `l` | `list` 함수로 인수들의 목록을 함수의 매개변수에 개별적으로 전달하여 실행하며, 인수들의 개수를 알 수 있을 때 사용한다.<br><br>예)<br>`execl("/bin/ls", "ls", "-l", (char *) 0);`                                                                                     |
| `v` | `vector` 함수로 인수의 목록을 `argv` 시작 주소를 이용하여 전체 전달한다.<br><br>예)<br>`char *const ls_arg[] = { "ls", "-l", 0 };`<br>`execv("/bin/ls", ls_arg);`                                                                            |
| `p` | 쉘의 환경변수 `PATH`에 정의된 경로를 이용하여 실행 파일을 찾아 실행한다. 따라서 첫 번째 인수에 경로 없이 실행 파일 명만 지정하면 된다.<br><br>예)<br>`execlp("ls", "ls", "-l", (char *) 0);`<br>`execvp("ls", ls_arg);`                                                   |
| `e` | 실행 파일 수행 시 필요한 환경 변수를 `envp`로 전달하여 실행한다.<br><br>예)<br>`char *const envp[] = { "PATH=/bin:/usr/bin", "TERM=xterm", 0 };`<br>`execle("/bin/ls", "ls", "-l", (char *) 0, envp);`<br>`execve("/bin/ls", ls_arg, envp);` |
## 시그널
#### 시그널 종류와 사용
* 시스템에서 발생하는 사건을 프로세스에게 알림
* 그에 따른 동작을 수행하도록 하는 메소드
* 사건 
	* 인터럽트, 부동 소수점 오류, 알람
* 시그널에 따라 기본적으로 수행하는 동작을 디폴트 핸들러 설정, 동작 처리

| 핸들러 종류  | 동작                  |
| ------- | ------------------- |
| Term    | 프로세스 종료             |
| Ign     | 시그널 무시              |
| Core    | Core 파일 생성, 프로세스 종료 |
| Stop    | 프로세스 정지             |
| NoCatch | 사용자 핸들러 설정 불가       |
| NoIgn   | 시그널 무시 불가           |
* 사용자 또는 응용프로그램 생성 시그널

| 시그널 명   | 시그널 번호 | 의미                                |
| ------- | ------ | --------------------------------- |
| SIGHUP  | 1      | 행업 신호(데몬 프로세스 초기화)                |
| SIGINT  | 2      | 터미널 인터럽트 신호(Ctrl C)               |
| SIGQUIT | 3      | 터미널 종료 신호(Control \\), Core 파일 생성 |
| SIGABRT | 6      | 프로세스 중단                           |
| SIGKILL | 9      | 종료 신호                             |
| SIGUSR1 | 10     | 사용자 정의 신호                         |
| SIGUSR2 | 12     | 사용자 정의 시그널                        |
| SIGTERM | 15     | 일반적인 종료 신호                        |

* 작업 제어 시그널

| 시그널 명   | 시그널 번호 | 의미                              |
| ------- | ------ | ------------------------------- |
| SIGCHLD | 17     | 자식 프로세스의 정지 혹은 종료               |
| SIGCONT | 18     | 정지 되었던 프로세스 다시 실행               |
| SIGSTOP | 19     | 실행 멈춤                           |
| SIGTSTP | 20     | 터미널에서의 정지 신호                    |
| SIGTTIN | 21     | 백그라운드 프로세스가 읽기 작업 수행 시 발생, 일시중지 |
| SIGTTOU | 22     | 백그라운드 프로세스가 쓰기 작업 수행 시 발생, 일시중지 |

* 에러 탐지 관련 시그널

| 시그널 명   | 시그널 번호 | 의미                |
| ------- | ------ | ----------------- |
| SIGBUS  | 7      | 정의되지 않은 메모리로의 접근  |
| SIGFPE  | 8      | 부동 소수점 연산 오류      |
| SIGILL  | 9      | 허용되지 않는 명령 수행     |
| SIGPIPE | 13     | 읽기 대상이 없는 파이프로 쓰기 |
| SIGSEGV | 11     | 유효하지 않은 메모리로 접근   |
| SIGSYS  | 31     | 잘못된 시스템 콜         |
| SIGXCPU | 24     | CPU 제한시간 초과       |
| SIGXFDZ | 25     | 파일크기 제한 초과        |

* 타이머 관련 시그널

| 시그널 명     | 시그널 번호 | 의미                          |
| --------- | ------ | --------------------------- |
| SIGALRM   | 14     | 알람 시계 완료                    |
| SIGVTALRM | 26     | 가상 타이머 완료(프로세스 실행시간 기반 타이머) |
| SIGPROF   | 27     | 프로파일링 타이머 완료                |

* 기타

| 시그널 명   | 시그널 번호 | 의미                       |
| ------- | ------ | ------------------------ |
| SIGTRAP | 5      | 추적 또는 브레이크 포인트 트랩        |
| SIGURG  | 23     | 소켓 out of band 데이터 유효 알림 |

#### 시그널 셋 관리
* 비트로 관리
![[Pasted image 20260519113525.png]]
* sigset_t 자료형의 시그널 집합을 좀 더 쉽게 사용할 수 있도록 시그널 등록, 삭제 할 수 있는 함수 제공
```c
#include <signal.h>

int sigaddset(sigset_t *set, int signo); // 특정 시그널 등록
int sigemptyset(sigset_t *set); // 집합 모두 0으로 초기화
int sigfillset(sigset_t *set); // 집합 모두 1로 설정
int sigdelset(sigset_t *set, int signo); // 특정 시그널 삭제
int sigismember(sigset_t *set, int signo); // 등록 확인
```

#### 시그널 핸들러의 종류
* 프로세스에서 시그널을 받앗을 때 기본적으로 처리하는 방법은 디폴트 핸들러에 기술
* signal(), sigaction() 함수 등을 이용, 시그널 핸들러 재설정 가능
	* 해당 핸들러는 해당 프로세스에서만 유효, 디폴트 핸들러에는 영향 없음
	* SIGKILL, SIGSTOP 시그널에 대해서는 시그널 핸들러 재설정 불가

| 핸들러     | 의미              |
| ------- | --------------- |
| 함수명     | 사용자가 정의한 핸들러 함수 |
| SIG_DFL | 디폴트 핸들러         |
| SIG_IGN | 무시              |
#### 시그널 핸들러 등록 함수
* signal(), sigaction() 함수
```c title=signal()
#include <signal.h>
void(*signal(int sig, void (*func)(int)))(int);

signal(SIGINT, int_handler);
signal(SIGINT, SIG_IGN);
signal(SIGINT, SIG_DFL);
```
* 첫 번째 인수에는 시그널 번호, 두 번째 인수에는 그 시그널에 대한 핸들러 함수 등록

* sigaction() 함수
	* signal 함수와 같이 시그널 핸들러 등록하는 함수
	* 보다 안전한 시그널 핸들러 처리를 위해 설계
```c
#include <signal.h>

int sigaction(int sig, const struct sigaction *act, struct sigaction *oact);

struct sigaction {
	void (*sa_handler)(int); // 핸들러 함수 SIG_IGN, SIG_DFL
	void (*sa_sigaction)(int, siginfo_t*, void*);
	sigset_t sa_mask; // sa_handler에서 블록킹할 시그널 집합
	int sa_flags; // 시그널 처리 동작 변경 플래그
	void (*sa_restorer)(void); // 현재는 사용 x
}
```
* sigaction() 함수는 첫 인자에는 시그널 번호를
* 두 번째 인자에는 그 시그널에 대한 새로운 핸들러
* 세 번째 인자에는 이전에 사용하던 시그널 핸들러에 대한 정보를 읽어오도록 변수의 주소 전달
* 두, 세번째 인자의 자료형인 `struct sigaction` 중 `sa_mask` 멤버에는 시그널 핸들러를 처리하는 동안 블로킹할 시그널의 셋 구성
* 시그널 마스크 값 설정 -> 시그널 핸들러 안전하게 수행 가능

* flags

| 플래그 종류       | 의미                                                                               |
| ------------ | -------------------------------------------------------------------------------- |
| SA_RESETHAND | 시그널 수신하면 핸들러를 디폴트 핸들러로 재설정, 즉 1회성                                                |
| SA_RESTART   | 시그널 핸들러에 의해 중지된 시스템 콜 함수 자동으로 재시작 설정<br>해제 시 시그널 핸들러 수행 후 시스템 콜 함수를 EINTR 에러로 처리 |
| SA_NODEFER   | 시그널 핸들러가 같은 신호의 중복 수신 허용                                                         |
| SA_NOCLDSTOP | 자식 프로세스가 정지하거나 재개할 때 부모 프로세스에게 SIGCHLD 시그널 전송하지 않음                               |
| SA_SIGINFO   | 리얼타임 시그널에서 시그널의 추가 정보를 저장하는 용도로 사용                                               |
## 시그널 응용
#### 프로세스 그룹과 세션
* fork() 함수를 통해 생성되는 일련의 자식 프로세스를 관리하기 위한 그룹
* 하나의 목적을 위해 생성된 프로세스들의 모임을 의미
![[Pasted image 20260519152157.png]]
* PID와 PGID가 같은 프로세스를 프로세스 그룹의 리더라 명칭
* 프로세스 그룹의 리더는 같은 그룹의 프로세스에게 시그널을 전송할 수 있는 기능 가짐
![[Pasted image 20260519153604.png]]
#### getpid()/setpgid()
* 프로세스 그룹을 확인 또는 변경하는 함수
```c
#include <unistd.h>

int getpgid(pid_t pid);
int setpgid(pid_t, pid_t pgid);
```
* getpgid 함수는 인자로 pid를 전달하면 그 프로세스가 속한 프로세스 그룹의 PGID 반환
* Pid를 0으로 전달하면 현 프로세스의 PID를 의미
* setpgid() 함수의 첫 인자인 pid에는 프로세스 그릅을 변경하려는 프로세스의 pid를
* 두 번째 인자인 pgid에는 소속하려는 프로세스 그룹이 pgid를 설정하는 것으로 0으로 설정하면 현 프로세스의 pid를 의미
* setpgid(0,0)은 자기 자신을 새로운 프로세스 그룹의 리더로 설정하는 방법

#### setsid()
* 새로운 세션을 구성할 때 이용하는 함수
```c
#include <unistd.h>

pid_t getsid(pid_t pid);
pid_t setsid(void);
```
* getsid() 함수는 인자로 전달되는 pid의 SID를 반환하는 함수
* setsid() 함수는 새로운 새션을 생성할 때 호출하는 함수, 성공 시 해당 프로세스가 세션의 리더가 되며 새로운 프로세스 그룹을 자동으로 생성

#### 시그널 마스크 등록
* 프로그램이 수행되는 동안 블로킹 할 시그널 셋을 의미
* 프로세스나 쓰레드의 시그널 마스크를 등록하는 함수
```c
#include <signal.h>

int sigprocmask(int how, const sigset_t *set, sigset_t *oset);
int pthread_sigmask(int how, const sigset_t *set, sigset_t *oset);
```
* c첫 인자인 how의 설정에 따라 프로세스의 시그널 마스크 동작 방식 설정 가능
* set에는 새로운 시그널 마스크 값 등록
* 세번째 인수 oset에는 현재의 시그널 마스크 받아올 수 있음

| SIG_BLOCK   | set의 시그널들이 시그널 마스크에 추가  |
| ----------- | ----------------------- |
| SIG_SETMASK | 시그널 마스크 값을 set으로 설정     |
| SIG_UNBLOCK | set의 시그널을 시그널 마스크로부터 삭제 |
#### sigpending 함수
* 프로세스 수행 중 시그널 마스크에 포함된 시그널이 도착되면
* 해당 시그널은 보류 상태로 남아 있게 된다
```c
#include <signal.h>
int sigpending(sigset_t *set);
```
* 함수 호출 시 현재 보류되어 있는 시그널들을 set으로 전달
* 성공 - 0, 실패 - -1

#### sigsuspend() 함수
* 시그널 집합에 포함되어있는 시그널이 프로세스에 도착할 때까지 수행을 멈추는 함수
```c
#include <signal.h>
int sigsuspend(const sigset_t *sigmask);
```
* 시그널 마스크가 sigmask로 바뀌며 프로세스의 실행을 일시적으로 중단
* 시그널 도착 시 그 시그널의 핸들러 수행 후 프로세스 실행 재개
* 정상 종료 : 반환값 없음, 종료 안되면 -1 반환 => errno EINTR 설정

## 시그널과 타이머
#### alarm
* 특정 시간 후 SIGALRM 시그널 발생
* 일정 시간 후 처리해야 할 일 있을 때 사용
```c
#include <unistd.h>
unsigned int alarm(unsigned int seconds);
```
* 인수로 넘겨주는 시간 후에 SIGALRM 시그널 발생
* 인수에 0을 넘겨주면 알람 요청 취소
#### 인터벌 타이머
* alarm 시그널은 한번 리셋되면 재설정 필요
* getitimer/settitimer 함수를 이용해 인터벌 타이머 설정
```c
#include <sys/time.h>

int getitimer(int which, struct itimerval *val);
int setitimer(int which, const struct itimerval *val, struct itimerval *oval);
```
* which
	* ITIMER_REAL : 실시간 타이머, 만료 후 SIGALRM 시그널 발생
	* ITIMER_VIRTUAL : 프로세스 가상 타이머, 만료 후 SIGVTALRM 시그널 발생
	* ITIMER_PROF : 프로세스 가상 시간 및 실행시간에 기반, 만료 후 SIG_PROF 시그널 발생, 주로 CPU 소모 시간을 측정하는 프로파일링 측정 시 이용
* 두번째 인자에는 현 타이머 설정 값을 읽어오거나 새로 설정할 타이머 전달
* 세번째 인자에는 새로운 타이머 설정 시 이전 사용하던 타이머 설정 받아 올 수 있음
```c title=struct_itimerval
struct itmerval {
	struct timeval it_interval;
	struct timeval it_value;
};

struct timeval {
	time_t tv_sec;
	time_t tv_usec;
}
```
