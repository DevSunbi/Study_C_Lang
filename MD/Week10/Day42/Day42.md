## Thread
#### Thread?
* 프로세스를 새로 만든다는 것은 시스템 자원 소모량 증가 행위
* 시스템 자원 소모 최소화 방법이 쓰레드
* 한 프로세스 내에서 동작되는 여러 실행의 흐름
* 프로세스내의 주소 공간이나 자원들을 대부분 공유하며 실행
* RTOS에서는 프로세스와 쓰레드가 다름
* 새로운 프로세스 생성 안함 -> 자원 아낌
* 더 효율적이며 빠른 실행, 동일 프로세스 내에서 동작, 데이터 공유가 쉬움
![[Pasted image 20260526101355.png]]
* 장점
	* 시스템 Throughout 향상
	* 시스템 자원소모 감소
	* 프로그램 응답시간 단축
	* 스레드간 통신 방법 간단
* 단점
	* 한 스레드의 문제가 타 스레드에도 영향 미칠 수 있음
	* 잘못된 메모리 영역 침범 해 프로세스가 죽는 경우 모든 스레드 함께 죽음
	* 디버깅 어려움
![[Pasted image 20260526103943.png]]
-> Makefile을 통한 자동 빌드 설계
#### 스레드 생성자 함수
```c
#include <pthread.h>

int pthread_create(pthread_t *thread, pthread_attr_t *attr, void *(*start_routine(void *)), void *arg);
```
* 첫 번째 인수 - 스레드 ID 변수 주소
* 두 번째 인수 - 스레드 속성 설정
* 세 번째 인수 - 스레드 생성, 수행 코드 드렁가 있는 함수 이름
* 네 번째 인수 - 함수로 전달할 인수 값 설정
* 성공 시 0, 실패 시 에러 코드 반환
```c
void *thread_routine(void)
{
	...
}

pthread_create(&t_id, NULL, thread_routine, NULL);
```
#### 스레드 종료 대기 함수
* pthread_join 함수는 프로세스의 wait 함수와 같이 스레드의 종료 기다리는 함수
```c
#include <pthread.h>

void pthread_join(pthread_join, void **thread_return);
```
* 첫 번째 인수 - 종료를 기다리는 thread id => pthread_create() 함수에서 받아온 값 지정
* 두 번째 인수 - 스레드 종료 시 반환하는 값을 포인터의 포인터 전달
#### 스레드 종료 함수
```c
#include <pthread.h>

void pthread_exit(void *retval);
```
* exit 함수와 비슷
* 호출하는 함수로 retval에 반환 값의 포인터 전달
* 지역 변수 주소를 실어주면 안됨 -> 스레드 종료 시 지역변수 공간 스책 반납 : 참조 불가
* pthread_joint 함수의 두 번째 인자로 전달
* pthread_cleanup_push 정의되어 있으면 pthread_exit 호출 시 cleanup handler 호출
* cleanup handler는 메모리 정리하는 등의 일 실행
![[Pasted image 20260526104944.png]]
#### 스레드 종료 요청 함수
* process에서 kill을 이용해 타 프로세스로 시그널 전송 가능
* 스레드도 타 스레드로 종료 요청 가능
* 종료 요청을 받은 스레드는 동작 여부를 설정 할 수 있음
```c
#include <pthread.h>

int pthread_cancel(pthread_t thread);
```
* thread는 종료 요청을 보낼 스레드의 ID를 나타냄
* 요청을 받은 스레드에서는 다음 함수를 이용, 동작 여부 설정 가능
```c 
#include <pthread.h>

int pthread_setcancelstate(int state, int *oldstate);
```
* state에는 아래 값 설정 가능
	* PTHREAD_CANCEL_ENABLE : 종료 요청 허용
	* PTHREAD_CANCEL_DISABLE : 종료 요청 무시
* oldstate에는 이전 상태 얻어올 수 있음
#### 스레드 ID 확인 함수
* 현 수행되는 스레드의 ID를 확인하는 함수 - pthread_self
```c
#include <pthread.h>

pthread_t pthread_self(void);
```
* 함수를 호출한 스레드 ID를 반환
#### 스레드 분리 함수
* 스레드의 기본 속성은 joinable
* 해당 속성으로 생성된 스레드는 main 스레드에서 pthread_join 함수를 호출해야 사용하던 자원 반납
* pthread_join 함수 호출 -> main 스레드는 블록, 타 작업 수행 불가
* 스래드 수행 중 상태에서 새 이벤트 발생되어 스레드 새로 생성해야 되는 경우 문제 발생
* pthread_detach 함수를 이용해 해결
```c
#include <pthread.h>

int pthread_detach(pthread_t thread);
```
* 스레드 ID가 thread인 스레드를 main 스레드에서 분리기키는 함수
* 해당 스레드 종료 즉시 모든 자원 반납
* detach 상태가 아닐 경우 스레드가 종료한다 해도 pthread_join()을 호출하지 않는 한 자원 되돌려주지 않음
* detach 상태로 되어있는 경우 해당 스레드에 대해 pthread_join 함수 호출하면 실패
* 성공하면 0, 실패하면 0이 아닌 값 반환
#### 스레드간의 통신
* 데이터 세그먼트는 전역변수나 static 변수가 할당된느 공간으로 전역변수 선언 시 스레드간에 공유 메모리 공간으로 사용 가능
## 동기화
![[Pasted image 20260526115839.png]]
#### 뮤텍스
* 코드 임계 영역을 한 순간 특정 스레드 하나만 사용할 수 있도록
* 임계 영역에 진입할 때마다 뮤텍스 lock, 빠져 나올 때마다 뮤텍스 release하는 방법으로 동기화
```c
#include <pthread.h>

int pthread_mutex_init(pthread_mutex_t *mutex,
const pthread_mutexattr_t *mutexattr);
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutext_t *mutex);
int pthread_mutex_destroy(pthread_mutext_t *mutex);
```
#### 뮤텍스 생성 및 초기화
```c
int pthread_mutex_init(phtread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr);
```
* 첫 번째 인수에 뮤텍스 객체의 ID
* 두 번째 인수에는 뮤텍스 속성 설정
![[Pasted image 20260526120218.png]]
`pthread_mutex_t mutexid=PTHREAD_MUTEX_INITIALIZER;`
`pthread_mutex mutexid; pthread_mutex_init(&mutexid, NULL);` <- 권장
#### 뮤텍스 잠금 및 해제
```c
int pthread_mutex_lock(pthread_mutex_t* mutex);
int pthread_mutex_trylock(pthread_mutex_t* mutex);
int pthread_mutex_unlock(pthread_mutex_t* mutex);
```
* mutex id만 인자로 넘김
* trylock은 타 스레드에 의해 뮤텍스가 잠겨있는 경우 함수 안에서 블록되지 않고 즉시 반환
* 반환 값은 EBUSY
`if((ret_value=pthread_mutex_lock(&mutexid))!=) fprintf(stderrm "errno:%d:", ret_value)`
`if((ret_value=pthread_mutex_unlock(&mutexid))!=0) fprintf(stderr, "errno:%d\n", ret_value);`
## 세마포어
* 임계 영역에 진입할 때마다 세마포의 값 확인, 세마포어를 얻을 수 없을 때에는 임계영역 진입 불가
* 세마포어를 얻을 수 있을 때에만 세마포의 값을 줄이고 임계 영역으로 들어감
```c
#include <semaphore.h>

int sem_init(sem_t *sem, int pshared, insigned int value);
int sem_wait(sem_t *sem);
int sem_trywait(sem_t *sem);
int sem_post(sem_t *sem);
int sem_destroy(sem_t *sem);
```
#### 세마포어 초기화
`int sem_init(sem_t *sem, int pshared, unsigned int value);`
* 첫 번째 인수 sem에는 객체의 ID 받아올 변수 주소 전달
* 두 번째 인수 pshared에는 세마포 공유 타입 지정
	* 공유 타입에는 한 프로세스 내의 스레드 간에 세마포를 사용하는 경우에는 0
	* 타 프로세스와 함게 사용하는 경우 0이 아닌 값을 지정
* 세 번째 인수 value에는 세마포어의 초기 값 지정
`is(sem_init(&semid, 0, 1)!=0) fprintf(stderr, "semid=%d is fail\n");`
#### 세마포어 연산
``` c
int sem_wait(sem_t *sem);
int sem_trywait(sem_t *sem);
int sem_post(sem_t *sem);
```
* sem_wait은 세마포어 값 1 감소
	* 호출 시 세마포어 값이 0이면 타 스레드에서 sem_post()함수에 의해 값을 증가시킬 때 까지 대기
* sem_post는 세마포어 값 1 증가
* sem_trywait은 wait함수와 기능 동일, 실패하면 즉시 반환
	* errno : EAGAIN
`if(sem_wait(&semid)==-1) perror("sem_wait());`
#### 세마포어 소멸
`int sem_destory(sem_t *sem);`
* 세마포어 삭제
#### 클린업 필요성
* 스레드가 뮤텍스 잠금 상태, 동적 메모리 할당에서 강제/비정상 종료에 의해 종료되면 메모리 문제 발생
#### 클린업 함수
```c
#include <pthread.h>
void pthread_cleanup_push(void (*routine)(void *), void *arg);
void phtread_cleanup_pop(int execute);
```
* 첫 인자 - 핸들러 함수 이름
* 두 번째 인자 - 핸들러 함수 수행 시 인자 전달 내용 지정
* pthread_cleanup_pop 함수는 pthread_cleanup_push 함수로 등록했던 핸들러 함수를 삭제하는 함수로 등록한 순서 역순 삭제
* 함수 호출 시 인자로 0을 전달하면 핸들러 함수 수행하지 않고 삭제
* 1을 주면 핸들러 함수 수행 후 삭제
#### 스레드와 시그널
* 멀티스레드 환경에서의 시그널
	* 한 프로세스에서 타 프로세스로 비동기적으로 발생하는 이벤트를 알리기 위한 수단
	* 멀티스레드 환경에서 시그널은 프로세스와는 달리 어떤 스레드에서 처리할지 예측 불가
	* 별도의 시그널 처리 필요
* 시그널 처리 방법
	* 각 스레드별로 시그널 블록 마스크 다르게 설정
	* 시그널 전담 처리 스레드 운영
#### 시그널 블록 마스크 설정 함수
```c
#include <pthread.h>
#include <signal.h>

int pthread_sigmask(int how, const sigset_t  *newmask, sigset_t *oldmask);
```
* 첫번째 인자 how - SIG_BLOCK, SIG_UNBLOCK, SIG_SETMASK 중 하나로 설정
	* SIG_BLOCK -  시그널 마스크에 new mask 추가
	* SIG_UNBLOCK - 시그널 마스크에서 newmask 삭제
	* SIG_SETMASK - 현재 시그널 마스크를 newmask로 변경
* 세 번째 인자 - oldmask에는 기존 시그널 받아올 수 있음
#### 타 스레드로 시그널 전송
```c
#include <pthread.h>
#include <signal.h>

int pthread_kill(pthread_t thread, int signo);
```
* 스레드간 시그널 전송을 위함
* 첫 번째 인자 thread - 시그널 전송할 스레드 ID
* 두 번째 인자 signo - 전송할 시그널 번호 지정
#### 시그널 수신
```c
#include <pthread.h>
#include <signal.h>

int sigwait(const sigset_t *set, int *signo);
```
* 첫 번째 인자의 set - set에 설정된 시그널 중 하나가 수신될 때까지 블록 상태로 대기
* 시그널 수신 받으면 두번째 인자인 signo에 시그널 번호 반환
* 성공하면 0, 실패 시 에러코드
#### 시그널 전담 스레드
![[Pasted image 20260526143343.png]]
