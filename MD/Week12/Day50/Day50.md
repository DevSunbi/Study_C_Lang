## 리눅스 커널과 디바이스 드라이버
#### 커널
* 역할
	* 자원 관리, 하드웨어와의 인터페이스, 사용자 공간 프로그램에게 유용한 수준의 추상화 API 제공
![[Pasted image 20260608091907.png]]
* HW -> Interrupt -> C-Lib
#### 커널 선택
* 벤더 지원
	* SoC나 보드의 벤더로부터 임눅스 지원 여부 및 지원 수준 확인 필요
* 라이선스
	* 리눅스 소스 코드 : GPL v2(소스 공개)
	* 사용자 공간에서 시스템 호출하는 프로그램은 이 라이선스 적용 안됨
	* 커널의 모듈에 관련된 소스 코드 부분은 논쟁이 되는 부분 존재, 대체적으로 라이선스 적용 안되고 있음, 확인 필
* 종류
	* 모놀리닉 커널
	* 마하 커널
	* 하이브리드 커널
![[Pasted image 20260608092622.png]]
* 리눅스 커널
	* Monolithic 커널 구조를 가지고 있어 속도 면에서의 성능은 Micro로 커널에 비해 상대적으로 좋으나 업그레이드가 어렵다는 단점
	* 리눅스는 커널 모듈이란 것을 지원함으로써 Micro 커널과 같은 확장성이나 모듈성을 증가 
	* 모듈은 실행 중에 커널로 링크할 수 있는 객체 파일을 의미.
	* 리눅스에서는 디바이스 드라이버를 비롯한 여러 기능들을 모듈로 만들어 관리
```bash
sunbi@Sunbi:/lib/modules $ ls
6.12.75+rpt-rpi-2712  6.18.29+rpt-rpi-2712
6.12.75+rpt-rpi-v8    6.18.29+rpt-rpi-v8
sunbi@Sunbi:/lib/modules $ uname -r
6.18.29+rpt-rpi-v8

sunbi@Sunbi:/lib/modules $ cd $(uname -r)
sunbi@Sunbi:/lib/modules/6.18.29+rpt-rpi-v8 $ ls
build              modules.builtin.alias.bin  modules.order
dtb                modules.builtin.bin        modules.softdep
kernel             modules.builtin.modinfo    modules.symbols
modules.alias      modules.dep                modules.symbols.bin
modules.alias.bin  modules.dep.bin            modules.weakdep
modules.builtin    modules.devname            source

sunbi@Sunbi:/lib/modules/6.18.29+rpt-rpi-v8/kernel $ ls
arch  crypto  drivers  fs  kernel  lib  net  sound
sunbi@Sunbi:/lib/modules/6.18.29+rpt-rpi-v8/kernel/arch $ ls
arm64
sunbi@Sunbi:/lib/modules/6.18.29+rpt-rpi-v8/kernel/arch $ cd arm64
sunbi@Sunbi:/lib/modules/6.18.29+rpt-rpi-v8/kernel/arch/arm64 $ ls
crypto  lib
```
* .ko file -> Kernel Object file -> 커널에 올라가야 실행 가능 (모듈 LKM)
#### 커널 영역과 사용자 영역
* 사용자 영역
	* ls, ps, mount와 같은 리눅스 일반적인 명령어들과 컴파일된 프로그램 등이 수행되는 모드
* 커널 영역
	* 디바이스 드라이버, 인터럽트 처리 메커니즘 등 커널 함수 이용, HW와 통신하고 시스템 호출 인터페이스 이용
	* 사용자 수준 응용프로그램과 통신
	* 커널은 특권 레벨로 실행, 프로그래밍 시 주의 요
![[Pasted image 20260608094933.png]]
![[Pasted image 20260608094940.png]]
* 커널은 가상 주소를 이용, 자원에 접근
* 실 하드웨어 디바이스로 접근하려면 물리 주소를 가상 주소(커널 영역) 매핑하여 사용
* 디바이스 드라이버
	* 하드웨어를 제어하기 위한 하드웨어 특성이나 레지스터 설정 등 디바이스 제어를 위한 기능을 구현해놓은 SW, 커널 안에 구현
	* 디바이스 추상화 -> 어플리케이션에서 시스템 콜을 이용해 호출
![[Pasted image 20260608095359.png]]
#### 커널 소스 디렉토리
![[Pasted image 20260608102835.png]]

| dir    | 설명                                                                                                                                                                                                                                                                                                                                                                                         |
| ------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| kernel | 프로세스 생성 소멸, 프로그램 실행, 스케줄링, 시그널 처리 등 기능 구현되어있음<br>문맥 교환과 같은 HW 종속적인 프로세스 관리 부분은 arch/arm/kernel에 구현                                                                                                                                                                                                                                                                                         |
| arch   | HW 종속적인 부분이 구현된 디렉, CPU 종류에 따라 하위 디렉으로 재구분<br>ARM CPU 구현한 arch/arm 디렉은 몇 개의 하위 디렉으로 구분<br>arch/arm/boot - 시스템 초기화 때 사용되는 부트스트랩 코드 구현, 리눅스 커널인 vmlinuz 파일 생성 위치<br>arch/arm/kernel - 프로세스 관리자 중 문맥 교환이나 스레드 관리 같은 HW 종속적인 부분 구현<br>arch/arm/mm - 메모리 관리자 중 페이지 부재 결함 처리 같은 HW 종속적인 부분 구현<br>arch/arm/lib - 커널이 사용하는 lib 함수 구현<br>arch/arm/ math-emu - FPU(Floating Point Unit)에 대한 에뮬레이터 구현 |
| fd     | 리눅스에서 지원하는 다양한 파일 시스템들과 open(), read(), write() 등의 시스템 호출이 구현된 디렉으로 ext2, nfs, ufs, msdos 등 다양한 파일 시스템들을 사용자가 일관된 인터페이스로 접근할 수 있도록 하기 위해 리눅스에는 시스템 호출과 각 파일 시스템 간에 추상화된 VFS(Virtual File System)를 구현                                                                                                                                                                                       |
| mm     | 메모리 관리자가 구현된 디렉토리<br>가상 메모리, 프로세스마다 할당되는 메모리 객체 관리, 커널 메모리 할당자등의 기능 구현                                                                                                                                                                                                                                                                                                                     |
| driver | 리눅스에서 지원하는 디바이스 드라이버가 구현된 디렉<br>버퍼 캐시를 통해 접근하며 임의 접근이 가능한 블록 디바이스 드라이버는 driver/block이라는 이름의 하위 디렉에 구현<br>순차적으로 접근되는 문자 디바이스 드라이버는 driver/char 하위 디렉에 구현<br>네트워크 카드를 위한 드라이버는 driver/net<br>그 외 cdrom, sound, video 카드를 위한 드라이버는 각각 이름의 하위 디렉에 구현                                                                                                                                           |
| net    | 통신 프로토콜 구현된 디렉터리<br>TCP/IP, UNIX 도메인 통신 프로토콜, WAN-X.25 등 구현                                                                                                                                                                                                                                                                                                                                |
| ipc    | 프로세스간 통신 기능 구현 디렉<br>파이프, 시그널, SVR4 IPC, 소켓 등<br>SVR4 IPC인 메시지 패싱, 공유 메모리, 세마포어 구현                                                                                                                                                                                                                                                                                                         |
| init   | 커널 초기화 부분 - 커널 메인 시작 함수 구현 디렉<br>HW 종속 초기화 수행 후 커널의 메인 시작 함수 호출<br>init/main.c에 구현된 start_kernel() 함수<br>디바이스 드라이버 초기화, 커널 내부 자료 구조 할당 및 초기화<br>프로세스0, 1 생성 등 수행<br>이후 init 프로세스가 초기화 담당, 각종 데몬의 생성, 파일 시스템 마운트 및 초기화, 터미널 초기화, 네트워크 초기화, 로그인 프로세스 등 작업 수행                                                                                                                                 |
#### 리눅스 커널의 개요
* 프로세스 관리 - 프로세스와 스레드
	* 프로세스 : 실행 중인 프로개름
		* 독자적인 가상 메모리를 갖고 있는 태스크
		* 자원을 독점해 사용하는 것으로 생각하며 수행
	* 스레드 : 프로세스 내에 활동을 가진 객체
		* 스케줄링의 최소 단위
		* 하나의 가상 메모리를 여러 태스크들이 공유
* 프로세스 관리 - 프로세스 기술자와 태스크 구조체
![[Pasted image 20260608104940.png]]
* 프로세스 관리 - 프로세스 상태 천이
![[Pasted image 20260608105020.png]]
* 프로세스 관리 - fork() 시스템 호출에 따른 자식 프로세스 생성
![[Pasted image 20260608105041.png]]
* 프로세스 관리 - 스케줄링
	* 멀티태스킹 운영 체제의 기본 요소
	* 수행 가능 프로세스 중에서 다음 실행할 프로세스 선택
	* 리눅스 스케줄링 기법
		* IO 중심의 프로세스 - 높은 우선순위
		* 프로세스 중심의 프로세스 - 낮은 우선순위
	* 스케줄링 정책에 따라 선택
		* SCHED_RR - 정적 우선순위의 실시간 프로세스, 가장 우선순위가 높은 프로세스 선택, 선점 불가
		* SCHED_FIFO - 동적 우선순위의 실시간 프로세스
		* SCHED_OTHER - 일반적인 time sharing 프로세스, 실행 시간이 길수록 우선순위가 낮아짐
	* 문맥 교환
![[Pasted image 20260608105702.png]]
* 메모리 관리
	* 페이지
		* 메모리 관리의 기본 단위, MMU 처리 단위
		* 32비트 아키텍처 - 4KB
		* 64비트 아키텍처 - 8KB
		* 페이지 구조체 struct page 선언 - <linux/mm.h>
	* 리눅스에서 주소 타입
		* User Virtual Address - 일반적으로 사용자 프로그램에서 사용하는 주소
		* Physical Address : CPU와 시스템의 물리적 메모리가 사용하는 주소
		* Linear Address : 커널 내부 함수 kmalloc()에 따라 할당되는 메모리의 주소
![[Pasted image 20260608105827.png]]
![[Pasted image 20260608105832.png]]
* 리눅스 파일 시스템 관리
	* 리눅스에서 모든 것을 파일 개념으로 취급
	* 다양한 파일 시스템 지원(Virtual File System)
	* 주요 오브젝트
		* 슈퍼 블록 객체
		* inode 객체
		* 파일 객체
		* dentry 객체
	* Block I/O를 위한 버커 캐시 이용
	* 파일 시스템 종류
		* ext2/ext3/ext4
		* cramfs
		* xfs
		* jffs2
![[Pasted image 20260608105942.png]]
* 커널과 디바이스 통신
	* 커널은 사용자와 HW 사이 존재
	* HW 관리하고 이에 대한 서비스 사용자에게 제공
	* 디바이스 드라이버와 인터업트 처리 메커니즘 등을 이용, HW와 통신
	* 시스템 호출 인터페이스를 이용, 사용자 수준 응용과 통신
	* 디바이스 드라이버가 제공하는 시스템 호출은 없다
	* 리눅스 커널에서 디바이스 드라이버는 사용자 수준 응용을 이용해 직접 호출 되지 않음
	* 파일 시스템을 거쳐 디바이스 드라이버의 서비스 호출
![[Pasted image 20260608110301.png]]
#### 주요 커널 함수
| 함수                 | 내용                                                                                                       | 헤더 파일              |
| ------------------ | -------------------------------------------------------------------------------------------------------- | ------------------ |
| `printk()`         | 콘솔에 로그를 출력한다.<br>`int printk(const char *fmt, ...);`                                                     | `<linux/kernel.h>` |
| `kmalloc()`        | 메모리를 할당한다.<br>`void *kmalloc(size_t size, int priority);`                                                | `<linux/malloc.h>` |
| `kfree()`          | 할당된 메모리를 해제한다.<br>`void kfree(void *__ptr);`                                                             | `<linux/malloc.h>` |
| `get_user()`       | 사용자 영역에서 커널 영역으로 데이터를 가져온다.<br>`err = get_user(x, ptr);`                                                 | `<asm/uaccess.h>`  |
| `put_user()`       | 커널 영역에서 사용자 영역으로 데이터를 보내준다.<br>`err = put_user(x, ptr);`                                                 | `<asm/uaccess.h>`  |
| `copy_from_user()` | 사용자 영역에서 커널 영역으로 메모리 블록을 복사한다.<br>`bytes = copy_from_user(void *to, const void *from, unsigned long n);` | `<asm/uaccess.h>`  |
| `copy_to_user()`   | 커널 영역에서 사용자 영역으로 메모리 블록을 복사한다.<br>`bytes = copy_to_user(void *to, const void *from, unsigned long n);`   | `<asm/uaccess.h>`  |
| `access_ok()`      | 사용자 영역을 접근할 수 있는지 확인한다.<br>`access_ok(addr, size);`                                                      | `<asm/uaccess.h>`  |
| `cli()`            | 인터럽트를 지운다(비활성화한다).<br>`extern void cli();`                                                               | `<asm/system.h>`   |
| `sti()`            | 인터럽트를 설정한다(활성화한다).<br>`extern void sti();`                                                               | `<asm/system.h>`   |
#### 모듈의 동적 사용

* 리눅스 커널 모듈 관련 명령어(mod-utils)

| 명령어 | 내용 |
|---|---|
| `lsmod` | 현재 커널에 올라와 있는 커널 모듈의 리스트를 표시한다. |
| `insmod` | 해당 커널 모듈을 올린다(load). |
| `rmmod` | 해당 커널 모듈을 내린다(unload). |
| `modprobe` | 해당 커널 모듈을 올릴 때 필요한 의존관계가 있는 모든 모듈들을 올린다. |
| `depmod` | `modprobe` 명령어를 위해 모듈들의 의존관계 리스트를 출력한다. |
| `modinfo` | 현재 모듈에 대한 정보를 출력한다. |
#### 모듈 프로그래밍
* module_init(함수명) : 모듈 초기화 함수
* module_exit(함수명) : 모듈 해제 함수

```c title="hello_module.c"
#include <linux/init.h>
#include <linux/module.h>
MODULE_LICENSE("GPL");

static int_init hello_init(void) {
	printk(KERN_NOTICE"Hello, World#2\n");
	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_NOTICE "Goodbye\n");
}

module_init(hello_init);
module_init(hello_exit);
```
![[Pasted image 20260608144408.png]]
```makefile 
obj-m := hello_module.o

KDIR := /usr/src/linux

default:

    make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -C$(KDIR) M=$(shell pwd) modules

clean:

    make -C$(KDIR) M=$(shell pwd) clean
```
```bash
sunbi@Sunbi:~/kernelHome $ sudo insmod hello_module.ko
[sudo] password for sunbi: 
sunbi@Sunbi:~/kernelHome $ lsmod | grep hello
hello_module           12288  0
sunbi@Sunbi:~/kernelHome $ dmesg
[ 7392.274107] hello_module: loading out-of-tree module taints kernel.
[ 7392.277059] Hello, World#2
[ 7439.257443] Goodbye
```
## 디바이스 드라이버
#### 디바이스 드라이버 관점에서 본 리눅스 구조
![[Pasted image 20260608151321.png]]
#### 응용프로그램 관점에서 본 리눅스 구조
![[Pasted image 20260608151335.png]]
#### 커널 메시지 출력
* printk()
	* 커널의 메시지 출력 및 관리 특성
		* 메시지 기록을 위한 로그 레벨의 지정
		* 원형 큐 구조의 관리
		* 출력 디바이스 다중 지정
		* 콘솔에서 확인하거나 dmesg 명령을 이용해 로그 파일 확인

| 상수 선언문 | 의미 |
|---|---|
| `#define KERN_EMERG` | `<0>` 시스템이 동작하지 않는다 |
| `#define KERN_ALERT` | `<1>` 항상 출력된다 |
| `#define KERN_CRIT` | `<2>` 치명적인 정보 |
| `#define KERN_ERR` | `<3>` 오류 정보 |
| `#define KERN_WARNING` | `<4>` 경고 정보 |
| `#define KERN_NOTICE` | `<5>` 정상적인 정보 |
| `#define KERN_INFO` | `<6>` 시스템 정보 |
| `#define KERN_DEBUG` | `<7>` 디버깅 정보 |
* 로그 레벨 지정
	* 로그 레벨은 printk() 함수에 전달되는 문자열 선두 문자에 <1>과 같이 숫자로 등급 표현
	* linux/kernel.h에 정의된 선언문을 이용이 바람직
* 리눅스 커널에서 로그(메시지)를 출력할 때 사용하는 최신 표준 매크로 함수

| 매크로 함수명      | 의미                        |
| ------------ | ------------------------- |
| `pr_info()`  | 일반적인 정보 알림 (Information)  |
| `pr_err()`   | 시스템에 문제가 생긴 에러 상황 (Error) |
| `pr_warn()`  | 주의가 필요한 경고 상황 (Warning)   |
| `pr_debug()` | 쓰는 디버깅용 로그 (Debug)        |
<사용 가능한 형식지정자>
* %s - 문자열 출력
* %d 또는 %i - 부호 있는 16/32비트 정수 출력
* %u - 부호 없는 정수 출력
* %x - 16진수 소문자 출력
* %X - 16진수 대문자 출력
<커널만의 특별한 확장 지정자>
* %p - 메모리 주소 출력(실 주소 아닌 암호화된 해시값)
* %px - 실제 메모리 주소 그대로 출력
* %plSn  - 네트워크 IP 주소 출력
* %ph - 버퍼에 담긴 바이트 배열을 16진수 문자열로 한 번에 출력
<주의사항>
* 소수점(실수) 사용 불가, 64비트 정수는 %ld 사용

* /proc/kmsg
	* 커널 메시지 발생할 때마다 관찰 가능
	* cat /proc/kmsg
* printk()  pr_info() 주의 점
	* 출력 함수 과도 사용 엄금 -> 실행시간 긺
	* 개행 문자가 있어야 출력 시작 -> '\n' 문자 꼭 포함
## 캐릭터 디바이스
#### 캐릭터 디바이스 드라이버 구현
* 캐릭터 디바이스
	* 키보드 같은 디바이스는 바이트 단위로 처리되고 써넣은 데이터는 보존될 수도, 보존되지 않을 수도 있다
	* 시간에 따라 연속적으로 발생할 수도 있고, 발생한 데이터의 끝을 알 수 없다
	* fs/char_dev.c에 정의
	* `struct char_device_struct chrdevs[CHRDEV_MAJOR_HASH_SIZE]`
![[Pasted image 20260608153441.png]]
```c title=sk.c
/***************************************

 * Filename: sk.c

 * Title: Skeleton Device

 * Desc: module_init, module_exit

 ***************************************/

#include <linux/module.h>

#include <linux/init.h>

  

/* 모듈 메타데이터 설정 */

MODULE_LICENSE("GPL");

MODULE_AUTHOR("Your Name");  

MODULE_DESCRIPTION("Skeleton Device Driver");

  

/* 모듈이 커널에 로드될 때 호출되는 함수 */

static int __init sk_init(void)

{

    pr_info("SK Module is up...\n");

    return 0;

}

  

/* 모듈이 커널에서 제거될 때 호출되는 함수 */

static void __exit sk_exit(void)

{

    pr_info("The module is down...\n");

}

  

module_init(sk_init);  

module_exit(sk_exit);
```

#### Character Device Driver 구조

* User Space

| 디바이스 파일      | 사용자 함수                                                  |
| ------------ | ------------------------------------------------------- |
| `/dev/mydev` | `open()` / `read()` / `write()` / `ioctl()` / `close()` |

* Kernel Space

| 함수 / 구조체                                              | 의미                               |
| ----------------------------------------------------- | -------------------------------- |
| `register_chrdev_region()`<br>`alloc_chrdev_region()` | `major` / `minor` 번호 할당          |
| `cdev_init()`                                         | `cdev` 초기화                       |
| `cdev_add()`                                          | 커널에 등록                           |
| `class_create()`                                      | `sysfs` class 생성                 |
| `device_create()`                                     | `/dev` 노드 생성                     |
| `file_operations`                                     | `read` / `write` / `ioctl` 함수 연결 |
#### 드라이버 로드/언로드
![[Pasted image 20260608154537.png]]
#### User space와의 연계 : file_operations
![[Pasted image 20260608155454.png]]
#### 캐릭터 디바이스 등록
* 구형 문자 디바이스 등록 함수
	* `int register_chrdev(unsigned int majot, const char *name, struct file_operations *fops);`
		* major - 요청할 major 번호 : 기존 것과 겹치지 않는 번호 이용
		* name - 디바이스 이름, /proc/devices에 나타남
		* fops - file operation function pointer
		* 문자 디바이스 드라이버 테이블 chrdevs\[]의 인덱스로 사용

* 최근 문자 디바이스 등록
	* `int register_chrdev_region(dev_t dev, unsigned int count, const char* name);`
		* dev : 디바이스 번호, major 번호와 minor 번호가 합쳐진 dev_t로 보통 MKDEV 매크로로 생성
		* count : 요청할 minor 번호 개수
		* name : /proc/devices에 표시될 장치명
		* 문자 디바이스 드라이버의 주 번호와 부 번호 미리 등록할 때 사용
	* `int alloc_chrdev_region(dev_t *dev, unsigned baseminor, unsigned count, const char *name);`
		* dev : major/minor 번호가 저장될 dev_t 자료형의 주소
		* baseminor : 시작 minor 번호(보통 0)
		* count : 필요한 minor 개수
		* name : /proc/devices에 표시될 이름
		* char device의 major/minor 번호를 커널에 요청
		* major 번호 자동 배정
		* cdev_add()에서 사용할 dev_t 값을 만들어 줌
		* 성공 시 0 반환, 실패시 음수 오류 코드 반환
* 문자 디바이스 초기화
	* `void cdev_init(struct cdev *cdev, const struct file_operations *fops);`
		* cdev : cdev 구조체 변수의 주소(전역변수로 선언)
		* fops : file_operations 구조체의 주소
		* 문자 디바이스 구조체를 초기화 하는 함수, file_operations와 연결
```c
static struct cdev my_cdev; 
static struct file_operations my_fops = { 
	.owner = THIS_MODULE, 
	.read = mydev_read, }; 
	. . . 
cdev_init(&my_cdev, &my_fops); // cdev 초기화
```
* 커널에 문자 디바이스 cdev 등록
	* `int cdev_add(struct cdev *cdev, dev_t dev, unsigned count);`
		* cdev : cdev 구조체 변수 주소
		* dev : 디바이스 번호
		* count : minor 개수
		* 커널에 char device 등록하는 함수
		* 디바이스 번호와 연결
		* 반환값 : 성공하면 0, 실패하면 음수 에러 코드 반환
```c
cdev_init(&my_cdev, &my_fops); 
cdev_add(&my_cdev, my_dev, 1);
```
* 캐릭터 디바이스 해제
	* `void cdev_del(struct cdev *cdev);`
		* 제거할 cdev 구조체의 포인터
	* `void unregister_chrdev_region(dev_t unsigned int count);`
		* dev : 할당 받았던 디바이스 번호
		* count : 등록할 때 요청했던 minor 번호 개수
![[Pasted image 20260608162637.png]]
![[Pasted image 20260608162642.png]]
