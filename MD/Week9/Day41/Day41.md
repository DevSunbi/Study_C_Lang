#### 통신 프로세스
* 리눅스에서 프로세스 -> 독립적으로 실행되는 객체, 프로세스간의 통신을 위해선 별도 자원 할당
* 리눅스 커널에서는 다음과 같은 IPC 메소드 제공
	* 파이프
	* 메세지 큐
	* 세마포어
	* 공유 메모리
* 메소드 특징

| IPC 메소드 | 통신 방향 | 관련 프로세스       | 특징                             |
| ------- | ----- | ------------- | ------------------------------ |
| 파이프     | 단     | 2개 프로세스 통신    | PIPE(4096 bytes)크기 고려          |
| 메시지 큐   | 양     | 2개 이상 프로세스 통신 | 짧은 메시지(1024 bytes 미만) 교환 적절    |
| 공유 메모리  | 양     | 2개 이상 프로세스 통신 | 긴 메시지 교환에 적절, 통신 시 충돌 문제 해결 필요 |
| 세마포어    | 양     | 2개 이상 프로세스 통신 | 주로 IPC 동기화 요소로 사용              |
#### SYSTEM V IPC / POSIX IPC
* IPC 제어를 위한 시스템 콜(API)에는 두 가지 표준 존재
* System V IPC는 기종간 코드 호환성 보장, API 형식 직관적이지 않아 불편
* POSIX IPC는 직관적 API로 구성, 좀 더 사용하기 쉬움
#### System V IPC 객체
* 메세지 큐, 공유 메모리, 세마포 등
* 한 시스템 내에서 이용 가능
* 프로세스 종료해도 강제로 삭제하지 않는 한 계속 살아있음
* 각 객체는 IPC ID라는 식별자에 의해 구분
* IPC key에 의해 식별자 기준 결정
* xxxget, xxxctl 형식의 시스템 콜에 의해 생성 및 제어
	* msgget - 메시지 큐 객체 생성자 함수
	* shmget - 공유 메모리 객체 생성자 함수
	* semget - 세마포 객체 생성자 함수
* ipcs
	* 현 리눅스 시스템에 존재하는 IPC 객체의 상태 확인 명령
![[Pasted image 20260522092742.png]]
* iprm
	* IPC 통신 프로그램 시험하다 오류 발생 -> 비정상 종료
	* IPC 오브젝트 정상적 반납 불가
	* `$ ipcrm -q <messagequeue_id> [-m <sharedmemory_id> / -s <semaphore_id> ]`

#### 파이프(Anonymous / Named)
* 두 프로세스간에 데이터를 전달하기 위해 사용하는 메소드
* 한 프로세스의 출력 스트림을 다른 프로세스의 입력 스트림으로 연결해주는 방법
![[Pasted image 20260522092951.png]]
* popen(), pclose() 함수 사용
```c
#include <stdio.h>

FILE *popen(const char *command, const char *open_mode);
int pclose(FILE *stream_to_close);
```
* 실행 파일을 open함
#### Anonymous pipe
* 이용
```c
#include <unistd.h>
int pipe(int file_descriptor[2]);
```
* 디스크립터 -> r, w 두 개 필수로 넘겨줌
* 메시지 출력 시 filedescriptor\[0]을 통해 입력 받을 수 있음
![[Pasted image 20260522093757.png]]
#### NAMED PIPE
* 이름 있는 파이프
* 프로세스가 종료 되더라도 여전히 존재, 언제라도 이름으로 파이프 통신 가능한 자원
* 파이프 파일, FIFO 파일
`$ mkfifo <filename>`
`$ mknod <filename> p`
* 시스템 콜 mkfifo() 함수 이용 가능
* 일반 파일 처리 방법과 동일한 방법으로 접근 가능
* open(), read(), write(), close() func...이용, 파이프 통신 가능
#### Message Queue
* IPC 기능 중 메시지 큐는 파이프와 유사
* 양방향 통신 가능, 두 개 이상의 프로세스 간에 통신 가능
* 하나의 메시지 큐를 여러 프로세스가 이용 -> 구분자필요 => 메시지 타입
* 메시지 타입이 일치하는 것만 선택적으로 수신 가능, 혼돈 없이 통신 가능
![[Pasted image 20260522120635.png]]
```c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int msgget(key_t key, int msgflag);
```
* key에 값 전달, 통신하려는 프로세스끼리는 동일한 값 지정
* ftok() 또는 직접 설정
* IPC_PRIVATE 지정하면 현 프로세스만 접근 할 수 있는 메시지 큐 생성
	* 자식 프로세스 생성해서 진행함
* msgflag에는 IPC_CREAT와 메시지 큐 사용 권한을 비트 OR해 지정
* 성공 : ID 반환, 실패 -1
```c
int msgsnd(int msgid, const void* msg_ptr, size_t msg_sz, int msg_flg);
```
* msgid - msgget에서 반환 받은 메시지 큐 오브젝트 ID
* msg_ptr - 메시지 큐에 전송하려는 메시지 주소
* msg_sz - 메시지 길이 지정
* msg_flg - 0 / IPC_NOWAIT 플래그 설정
	* 0 - 큐 full일 경우 블록, 프로세스 수행 정지
	* IPC_NOWAIT - 큐 full일 경우 다른 처리 진행
		* 반환값 -1, errno EAGIN 설정
```c
int msgrcv(int msgid, void* msg_ptr, size_t msg_sz, ling msgtype, int msgflg);
```
* msgtype - 수신 할 메시지 타입 지정
	* 0 - 큐에 등록된 순서대로 수신
	* >0 - 해당 타입에 해당하는 메시지만 선택적 수신
* msgflg - 0 / IPC_NOWAIT
	* 0 - 비면 프로세스 수행 멈추고 타 프로세스에서 메시지 전송 할 때까지 대기
	* IPC_NOWAIT - 큐 비어있어도 프로세스 수행 멈추지 않고 진행
		* 반환 -1, errno ENOMSG
```c
int msgctl(int msgid, int command, struct msqid_ds *buf);

struct msqid_ds{
	uid_t msg_perm.uid;
	uid_t msg_perm.gid;
	mode_t msg_perm.mode;
}
```
* msgid - msgget() 함수 반환 값 : message queue object id
* command - 제어 명령 지정
	* IPC_STAT : 큐에 관련된 정보 세번째 인수로 읽어옴
	* IPC_SET : 큐에 관련된 세번째 인수에 전달한 값으로 설정
	* IPC_RMID : 삭제
![[Pasted image 20260522121817.png]]
#### 공유 메모리
* 프로세스가 다르면 메모리 공간도 다름
* IPC 기능 중 프로세스간에 메모리를 공유할 수 있게 해주는 공유 메모리 기능 존재
* 메모리 일부 영역을 각 프로세스가 수행되는 가상 주소 공간에 매핑
* 해당 주소에 접근해 데이터 R, W로 통신
![[Pasted image 20260522123723.png]]
```c
#include <sys/shm.h>
#include <sys/ipc.h>

int shmget(key_t key, size_t size, int shmflg);
```
* 동일 키를 이용해 메모리 공유
* 첫 번째 인수에 key
* 두 번째 인수 size에는 메모리 크기 바이트 단위
* 세 번째 인수 shmflg - IPC_CREAT 플래그와 사용권한 비트 OR 지정
	* 동일한 키 공유 오브젝트 이미 생성 시 IPC_CREAT 플래그 무시, ID만 반환
	* 성공 시 IPC ID, 실패 시 -1
	* IPC_CREAT + IPC_EXCL -> 지정 키 값의 공유 메모리 존재 할 경우 함수 호출 실패
```c
void *shmat(int shm_id, const void* shm_addr, int shmflg);

int shmdt(const void *shmaddr);
```
* 첫 번째 인수 shm_id는 shmget()함수에서 반환 받은 값인 공유 메모리 오브젝트 ID 전달
* 두 번째 인수 shm_addr은 할당된 공유 메모리를 프로세스에 매핑할 주소 지정
	* NULL 지정 시 시스템에서 주소 정해 반환
	* 사용자가 프로세스 내의 주소를 모두 알기는 불가능 -> NULL 이용
* 세 번째 인수 shmflg에는 0/SHM_RDONLY
	* 읽기 쓰기 가능/읽기 전용 공간
	* 성공시 메모리 주소, 실패 시 01 반환
* shmdt는 shmat에서 받아온 주소를 인수로 전달, 프로세스로부터 메모리 공간 분리
* 완전 삭제가 아닌 접근만 막음
```c
int shmctl(int shm_id, int command, struct shmid_ds *buf);
```
* 첫 번째 인수에는 shmget 반환 값인 공유 메모리 오브젝트 id 지정
* 두 번째 인수 command에는 공유 메모리 제어 명령 지정
* 세 번째 인수 buf에는 제어 명령에 따라 구조체 포인터 변수 지정
	* 성공 0 실패 -1
![[Pasted image 20260522124908.png]]
![[Pasted image 20260522124921.png]]
#### 세마포어
* 동시에 같은 자원을 접근하는 문제 해결을 위함
* 뮤텍스, 스핀락, 세마포어 등 여러 메소드 존재
* SystemV IPC 기능의 하나인 세마포어를 통해 동기화 문제 해결
* P(세마포어 변수) : 세마포어 변수가 0보다 크면 감소, 0이면 프로세스의 실행을 0보다 커질 때까지 중지
* V(세마포어 변수) : 세마포어 변수 증가시켜 변수를 기다리며 중지된 프로세스가 있으면 그 프로세스의 실행 재개
* 임계영역 진입 전 P 연산을 임계 영역을 지나면 V연산, 대문역할
![[Pasted image 20260522142105.png]]
* 프로세스간 통신보다 통신 시 일어날 수 있는 충돌 문제 해결을 위한 동기화 메소드
* 연산의 개념 존재
	* 감소 P연산, 증가 V연산
	* 한 프로세스에서 임계 영역을 빠져나온 후 V연산 진행 -> 타 프로세스에서 P연산을 통해 임계 영역으로 진입이 가능하도록 설계, 동기화 진행
```c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int semget(key_t key, int num num_sems, int sem_flags);
```
* key에는 같은 세마포어를 이용하려는 프로세스끼리 동일한 값 지정
* num_sems에는 세마포어 갯수 지정, 통상 1 지정
	* 공유할 데이터 종류에 따라 각각을 따로 관리해야하는 경우 개수 지정
* sem_flags에는 IPC_Creat와 함께 세마포의 접근 권한을 비트 OR해 표현
* 성공 시 오브젝트 ID, 실패 시 -1 반환
* IPC_CREAT + IPC_EXCL 사용 시 이미 지정한 키 값의 세마포가 존재하면 호출 실패
```c
int semop(int sem_id, struct sembuf* sem_ops, size_t num_sem_ops);

struct sembuf {
	short sem_num;
	short sem_op;
	short sem_flg;
}
```
* sem_id에는 semget에서 반환받은 오브젝트의 ID 지정
* sem_ops는 구조체 자료형 sembuf의 멤버 이용해 표현
![[Pasted image 20260522142847.png]]
-> P, V 연산임
```c
int semctl(int sem_id, int sem_num, int command, ...);
```
* 초기화 필수
* command
![[Pasted image 20260522143147.png]]
![[Pasted image 20260522143231.png]]
#### POSIX IPC
* shm_open - 공유메모리의 파일 기술자 얻음(생성)
* mmap - 공유 메모리의 파일 기술자를 메모리 맵으로 맵핑
* shm_unlink - 공유 메모리 제거
`int shm_open(const char *name, int oflg, mode_t mode`
* name : shm을 생성할 파일 경로명
* oflg : 오픈 시 사용할 플래그
![[Pasted image 20260522162034.png]]
* mode : 접근권한 - open()과 동일
`int shm_unlink(const char *name)`
* POSIX SHM은 따로 detach하는 과정 거치지 않음
#### mmap
* 파일, 장치를 메모리와 대응
	* SVR4에서 파일과 프로세스의 1:n 대응 오버헤드 해결책
	* 프로세스간의 데이터나 파일:메모리의 동기화로 사용
* 메모리 맵 특징
	* 대응된 mmap은 포인터로 접근
	* 파일로 연결하면 메모리와 파일 사이의 동기화가 편리
	* 파일 - 메모리 동기화와 크리티컬 섹션 보호에 신경
	* mmap의 크기를 넘어서는 경우에 파일에는 영향 안 줌
![[Pasted image 20260522162238.png]]
=> Shared/Private 두 가지 존재
* mmap은 파일 먼저 열고 메모리에 동기화
`void* mmap(void *start, size_t length, int prot, int flags, int fd, off_t offset);`
* 시작 번지 보통 NULL
* 대응 시킬 길이
* mmap을 만들 열려진 파일의 파일기술자
* 대응시킬 파일의 위치 offset
`int msync(void* start, size_t length, int flags);`
* 동기화 시킬 주소
* 동기화 시킬 길이
![[Pasted image 20260522162504.png]]
`int munmap(void* start, size_t length);'
* 동기화 시킬 주소, 길이
