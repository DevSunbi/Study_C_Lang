![[Pasted image 20260611115844.png]]
-> 해당 파일에 모듈 이름 적재 => 부팅마다 자동으로 올라감

sudo cp ~/modules/08_led_switch_drivers/led_driver.ko .
sudo depmod -a

복사해주고 dependency 알아 조사하게 하면 modules.dep에 자동 저장 됨

디렉토리에 모듈 갖다 박으면
sudo modprobe \[-r]module name 하면 잘 감


## 리눅스 커널 프로그래밍
#### 커널의 시스템 호출 함수
* 시스템 호출 번호
	* `/usr/include/arm-linux-gnueabihf/asm/unistd-common.h`에 정의
	* 시스템 호출 함수는 `sys_funcname`으로 되어있음
	* 특권 모드 사용을 위해 SW 인터럽트 발생, 시스템 호출 번호와 대응하는 함수 호출
![[Pasted image 20260611141020.png]]
```c title=include/uapi/asm-gernic/unistd.h
#define __NR_###### 451
__SYSCALL(__NR_######, sys_######) // 시스템콜 번호 정의

//add a plus one at total number
#define __NR_syscalls 452
```
