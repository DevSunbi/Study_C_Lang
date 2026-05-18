## 커널
#### 리눅스 커널과 시스템 콜
* 리눅스 시스템과 네트워크 프로그램
	* 리눅스 커널에서 제공하는 기능을 각종 시스템 콜(API)을 이용해 구현하는 것을 의미
	* 커널 -> 자원 동작/관리, 사용자 응용 프로그램 효율적으로 실행 될 수 있는 환경 제공 자원관리 프로그램
		* H/W
			* Cpu, Memory, Disk, Terminal, Network 등 시스템 구성 물리 장치
		* S/W
			* process, thread, segment, page, file, inode, protocol, socket 등
![[Pasted image 20260515094431.png]]
* 커널 구조
![[Pasted image 20260515094918.png]]
* interrupt를 통해 트랩을 통한 시스템 콜 찾음(라이브러리에 SW interrupt, systemcall num를 보고 찾음)
#### 라이브러리 함수와 시스템 콜
* 시스템 콜
	* 커널이 제공하는 서비스, 응용 프로그램의 요청에 따라 커널에 접근하기 위한 인터페이스 함수
	* 사용자 모드에서 실행되다 인터럽트를 통해 커널 모드로 전환, 실행
* 라이브러리 함수
	* 자주 사용할 만한 기능의 프로그램 미리 함수로 작성, 라이브러리 함수가 많으면 프로그램 개발 속도 증가
	* 사용자 모드에서 계속 실행
=> time() vs ctime()
매뉴얼 참조
man 2 systemcall_name -> 커널 모드, 메모리 할당 필요 
man 3 libfunc_name -> 사용자 모드, 함수에서 할당된 메모리 이용 가능
## 리눅스 시스템 프로그래밍
#### 오류 처리
* errno 변수
	* 시스템 콜 오류 시 리턴 값 : -1
	* errno 변수에 오류의 원인을 확인할 수 있는 구체적인 값 설정
```c
extern int errno;

extern const chat *sys_errlist[];
extern int sys_nerr;
```
```c
#define EPERM 1 /* Operation not permitted */ 
#define ENOENT 2 /* No such file or directory */ 
#define ESRCH 3 /* No such process */ 
#define EINTR 4 /* Interrupted system call */ 
#define EIO 5 /* I/O error */ ..................................................................... 
#define EREMOTEIO 121 /* Remote I/O error */ 
#define EDQUOT 122 /* Quota exceeded */ 
#define ENOMEDIUM 123 /* No medium found */ 
#define EMEDIUMTYPE 124 /* Wrong medium type */
```
#### 환경변수
* 쉘을 통해 명령을 실행 -> 쉘에 환경 변수가 있어 명령이나 프로그램 수행에 필요한 정보 지님
* PATH 환경변수에는 명령에 대한 실행 파일 위치 포함, 사용자 명령 입력 시 PATH 변수에 등록된 경로에 따라 실행 파일을 찾아내 커널로 실행 요청
* 변수
	* HOME, PATH, PS1, MAIL, MANPATH, USERNAME
* getenv(), putenv()
	* getenv -> 환경변수 불러오기
	* putenv -> 프로세스 수행 동안만 환경변수 수정 유지, 프로세스 종료 시 복원
#### 호스트정보
* uname(), gethostname()
	* 시스템 사양에 대한 정보 알 수 있음
```c
struct utsname { char sysname[SYS_NMLN]; // OS 종류 
    char nodename[SYS_NMLN]; // 호스트 명 
    char release[SYS_NMLN]; // 커널 릴리즈 번호 
    char version[SYS_NMLN]; // 커널 빌드 정보 
    char machine[SYS_NMLN]; // 하드웨어 사양 
}
```
* sys/utsname.h 선언 내용
#### 시간 정보
* time(), gettimeofday()
	* 초단위/마이크로 초 단위
* times()
	* 프로그램의 실행 시간, 프로세스의 시간 정보를 필요로 하는 경우 사용
```c
struct tms { 
     clock_t tms_utime; /* 사용자 모드의 시간 */ 
     clock_t tms_stime; /* 시스템 모드의 시간 */ 
     clock_t tms_cutime; /* 자식 프로세스의 사용자 모드 시간 */ 
     clock_t tms_cstime; /* 자식 프로세스의 시스템 모드 시간 */
};
```
* 프로세스의 시간을 사용자 모드와 시스템 모드에서 측정하고 실제 수행시간 리턴
* 시간 단위 : 시스템 부팅 후 계산된 클럭 틱의 값
#### 자원 제한치 확인 및 변경
* getrlimit(), setrlimit()
	* 리눅스 시스템에서 사용되는 자원에는 제한치 설정되어있음
	* 파일 크기, CPU 시간 등
```c
#include <sys/resource.h> 
int getrlimit(int resource, struct rlimit *r_limit); 
int setrlimit(int resource, const struct rlimit *r_limit); 
struct rlimit { 
    rlim_t rlim_cur; // 현재 설정된 소프트 제한 값 
    rlim_t rlim_max; // 절대적 제한치 
}
```
* getrlimit() 함수는 시스템 자원의 제한치를 확인할 때
* setrlimit()는 제한치를 변경할 때 사용
* resource 종류
	* RLIMIT_CPU : 초 단위 CPU 시간
	* RLIMIT_FSIZE : 최대 파일 크기
	* RLIMIT_DATA : 최대 데이터 크기
	* RLIMIT_STACK : 최대 스택 크기
	* RLIMIT_CORE : 최대 코어 파일 크기
	* RLIMIT_NPROC : 최대 프로세스 수
	* RLIMIT_NOFILE : 동시에 열 수 있는 최대 파일의 수
	* RLIMIT_MEMLOCK : lock된 기억 공간의 최대 크기
	* RLIMIT_AS : 가상 주소 공간의 제한 값
## MYSHELL
#### Shell?
* 하나의 프로그램, 로그인하게 되면 커널이 사용자에게 제공하는 무한 루프 프로그램
![[Pasted image 20260515140842.png]]
* 역할
	* 운영체제의 커널과 사용자 사이 인터페이스 역할
	* 입력한 명령어 쉘에 의해 타당성 여부 검증
	* 타당하면 자식 프로세스 생성, 해당 명령어 수행
	* 타당 X -> 에러 메시지를 출력하는 며열ㅇ어 번역기 프로그램(Command Interpreter)
![[Pasted image 20260515140939.png]]
* 일반적으로 리눅스에서 프로세스는 부모 프로세스에 의해 생성
* 리눅스에 있는 모든 프로세스는 부모와 자시그이 관계를 이루며 수행
* 프로세스 상세 정보에는 PID, PPID, CPU 소모 시간, 프로세스 상태 존재
* fork(), wait(), exec()등의 함수를 이용해 구현 => 프로그램 수행
#### 나의 쉘 만들기
* 목표 기능
	* 명령어 실행 기능
	* 빌트인 명령 기능
	* 리다이렉트 기능
	* 파이프 기능
## 파일시스템
#### 파일의 종류와 구조
![[Pasted image 20260515153456.png]]
* 파일의 종류
	* 일반 파일 - 문서 파일, 실행 파일
	* 디렉토리
	* 장치 파일 - 블록 파일, 문자 장치 파일
	* 파이프 파일
	* 심볼릭 링크 파일
	* 소켓 파일
* 디렉토리 및 블록 장치를 제외하고 모든 파일을 동일하게 제어 가능
* 프로세스의 구조 중 파일 디스크립터 테이블을 통해 파일을 제어
* 프로세스 안에서는 동일한 시스템 콜을 통해 파일들을 이용 가능
![[Pasted image 20260515154705.png]]
* 각 파티션은 파일을 체계적으로 부트 블록, 수퍼 블록, inode 리스트, 데이터 블록 등으로 구성
![[Pasted image 20260515154734.png]]
* 하나의 루트 디렉토리 아래에 모든 파티션들의 파일 구성 -> 파일 트리 구성
* 하나의 디스크를 파티션으로 구분해 각 영역을 별도로 관리
#### 파일의 정보 확인
* inode 리스트에는 각 파일에 대한 정보 보관
* inode 리스트에서 특정 파일에 대한 정보를 조회하기 위한 함소로는 stat(), lstat(), fstat() 등 존재
* inode 리스트의 정보를 확인할 수 있는 시스템 콜로그 원형은 아래와 같음
![[Pasted image 20260515154919.png]]
