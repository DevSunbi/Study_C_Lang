## LED 출력을 위한 GPIO 드라이버 프로그래밍
#### Address
```bash
sunbi@Sunbi:~/kernelHome $ grep gpio /proc/iomem
00000000-00000000 : fe200000.gpio gpio@7e200000
```
```c
#if 0

#define BCM_IO_BASE 0x20000000 /* Raspberry Pi B/B+의 I/O Peripherals 주소 */

#define BCM_IO_BASE 0x3F000000 /* Raspberry Pi 2/3의 I/O Peripherals 주소 */

#else

#define BCM_IO_BASE 0xFE000000 /* Raspberry Pi 4의 I/O Peripherals 주소 */

#endif

  

#define GPIO_BASE (BCM_IO_BASE + 0x200000) /* GPIO 컨트롤러의 주소 */

#define GPIO_SIZE (256) /* 0x7E2000B0 – 0x7E2000000 + 4 = 176 + 4 = 180 */
```
* mmap -> 파일이나 디바이스를 프로세스의 가상 메모리 주소 공간에 직접 연결
* ioremap -> IO 주소 공간을 가상 주소 공간에 할당
#### Kernel GPIO Func
* \<linux/gpio.h> 헤더 파일 사용
* gpio_request 함수는 GPIO 특정 핀의 사용 여부 확인, 결과 반환
	* 핀 이미 사용중이면 -EBUSY, 사용 중이 아니면 0 반환
	* 사용 종료 후 gpio_free를 이용해 반환 가능
* gpio 구조체는 GPIO 포트에 대해 설정하는 구조체
	* 해당 GPIO 포트에 대한 설정 진행 가능
	* gpio 구조체의 flags를 이용, GPIO의 방향을 설정
	* 입력은 GPIOF_IN 매크로 설정
	* 출력은 GPIOF_OUT_INIT_LOW / GPIOF_OUT_INIT_HIGH 매크로 설정
* 여러 GPIO 포트를 동시에 사용하는 경우, gpio 구조체의 배열과 gpio_request_array()와 gpio_free_array() 함수 사용
```c
struct gpio {
    unsigned        gpio;   /* GPIO의 번호 */
    unsigned long   flags;  /* GPIOF_*로 시작되는 GPIO 설정 */
    const char      *label; /* GPIO에 대한 설명 */
};
```
```c
/* GPIO 사용 위한 구조체 설정 */
static struct gpio devices[] = {
    { GPIO_LED,   GPIOF_OUT_INIT_HIGH, "LED"   },
    { GPIO_MOTOR, GPIOF_OUT_INIT_HIGH, "MOTOR" }
};

gpio_request_array(devices, ARRAY_SIZE(devices));

cmd = (!strcmp(msg, "0")) ? 0 : 1;

gpio_set_value(devices[0].gpio, cmd);
gpio_set_value(devices[1].gpio, cmd);

gpio_free_array(devices, ARRAY_SIZE(devices));
```
* 커널 관련 함수

| 함수                          | 내용                                                                                |
| --------------------------- | --------------------------------------------------------------------------------- |
| `gpio_direction_input()`    | GPIO 입력과 관련된 방향을 설정한다.                                                            |
|                             | `int gpio_direction_input(unsigned gpio);`                                        |
| `gpio_direction_output()`   | GPIO 출력과 관련된 초기값을 설정한다.                                                           |
|                             | `int gpio_direction_output(unsigned gpio, int value);`                            |
| `gpio_set_value()`          | GPIO에 값을 또는 1을 출력한다.                                                              |
|                             | `void gpio_set_value(unsigned gpio, int value);`                                  |
| `gpio_get_value()`          | GPIO에서 값을 가져온다.                                                                   |
|                             | `int gpio_get_value(unsigned gpio);`                                              |
| `gpio_export()`             | GPIO를 sysfs의 사용자 영역에서 제어할 수 있도록 한다.                                               |
|                             | `int gpio_export(unsigned gpio, bool direction_may_change);`                      |
| `set_irq_type()`            | GPIO의 인터럽트를 활성화한다.                                                                |
|                             | `int set_irq_type(unsigned int irq, unsigned int type);`                          |
| 함수                          | 내용                                                                                |
| `inb()`                     | 해당 포트로부터 1바이트의 값을 읽어온다.                                                           |
|                             | `unsigned char inb(unsigned short port);`                                         |
| `inb_p()`                   | 해당 포트로부터 1바이트를 읽을 때까지 기다렸다가(pause) 읽어온다.                                          |
|                             | `unsigned char inb_p(unsigned short port);`                                       |
| `outb()`                    | 해당 포트에 1바이트를 출력한다.                                                                |
|                             | `void outb(unsigned char value, unsigned short int port);`                        |
| `outb_p()`                  | 해당 포트에 1바이트를 쓸 때까지 기다렸다가(pause) 쓴다.                                               |
|                             | `void outb_p(unsigned char value, unsigned short int port);`                      |
| `inw(), inw_p()`            | 해당 포트로부터 2바이트(short int)의 값을 읽어온다.                                                |
|                             | `unsigned short int inw(unsigned short int port);`                                |
|                             | `unsigned short int inw_p(unsigned short int port);`                              |
| `outw(), outw_p()`          | 해당 포트에 2바이트(short int) 값을 출력한다.                                                   |
|                             | `void outw(unsigned short int value, unsigned short int port);`                   |
|                             | `void outw_p(unsigned short int value, unsigned short int port);`                 |
| `inl(), inl_p()`            | 해당 포트로부터 4바이트(long int)의 값을 읽어온다.                                                 |
|                             | `unsigned int inl(unsigned short int port);`                                      |
|                             | `unsigned int inl_p(unsigned short int port);`                                    |
| `outl(), outl_p()`          | 해당 포트에 4바이트(long int) 값을 출력한다.                                                    |
|                             | `void outl(unsigned int value, unsigned short int port);`                         |
|                             | `void outl_p(unsigned int value, unsigned short int port);`                       |
| `insb(), insw(), insl()`    | 해당 포트에서 특정 크기(count)의 데이터를 읽어서 해당 메모리(addr)에 저장한다.                                |
|                             | `void insb(unsigned short int port, void *addr, unsigned long int count);`        |
|                             | `void insw(unsigned short int port, void *addr, unsigned long int count);`        |
|                             | `void insl(unsigned short int port, void *addr, unsigned long int count);`        |
| `outsb(), outsw(), outsl()` | 해당 메모리(addr)에서 특정 크기(count)의 데이터를 해당 포트로 출력한다.                                    |
|                             | `void outsb(unsigned short int port, const void *addr, unsigned long int count);` |
|                             | `void outsw(unsigned short int port, const void *addr, unsigned long int count);` |
|                             | `void outsl(unsigned short int port, const void *addr, unsigned long int count);` |
#### request 유의
![[Pasted image 20260610121922.png]]
-> 직접 레지스터에 접근하는 것이 아닌 API로 접근을 하면 핀을 바라보는 번호가 달라짐
=> `sudo cat /sys/kernel/debug/gpio`를 이용해 GPIO 핀 번호 확인
#### 인터럽트 처리
* polling 방식 사용 -> 커널은 인터럽트 처리 과정 사용
* `gpio_to_irq()` 함수는 GPIO 핀 번호를 IRQ 번호로 매핑해주는 매크로 함수
* `set_irq_type()` 함수
	* 첫 번째 인자 irq에 대한 값, 현 디바이스에서 사용하는 인터럽트에 대한 처리 사항 설정
		* 해당 처리 사항의 값은 `IRQ_GPIO`로 알아올 수 있음
	* 두 번째 인자 type
		* `IRQT_RISING`, `IRQT_FALLING`, `IRQT_BOTHEDGE`, `IRQT_LOW`, `LRQT_HIGH`의 값 사용 가능
#### 애플리케이션으로의 시그널 전달
* 커널에서의 직접 처리가 아닌 애플리케이션에서 처리하는 경우 시그널 사용
* 현 프로세스의 ID를 사용, write 함수를 통해 해당 애플리케이션의 PID를 커널로 전달

|함수|내용|
|---|---|
|`task_pid()`|태스크의 PID 정보를 가지고 있는 `pid` 구조체를 반환한다.|
|`pid_task()`|`pid`와 관련된 첫 번째 태스크의 구조체를 반환한다.|
|`task_tgid()`|커널 스레드 그룹 리더의 PID 정보를 가지는 `pid` 구조체를 반환한다.|
|`task_pgrp()`|프로세스 그룹 리더의 PID 정보를 가지는 `pid` 구조체를 반환한다.|
|`task_session()`|세션 리더의 PID 정보를 가지는 `pid` 구조체를 반환한다.|
|`pid_nr()`|`pid` 구조체로부터 전역(global) PID를 반환한다.|
|`pid_vnr()`|`pid` 구조체로부터 가상(virtual) PID를 반환한다.|
|`pid_nr_ns()`|`pid` 구조체로부터 지정된 네임스페이스(namespace)에 속한 PID를 반환한다.|
|`find_vpid()`|가상(virtual) PID에 해당하는 `pid` 구조체를 반환한다.|
|`find_pid_ns()`|지정된 네임스페이스에 속한 PID에 해당하는 `pid` 구조체를 반환한다.|
