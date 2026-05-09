#### Pullup / PullDown
![[Pasted image 20260428091358.png]]
* Pull up -> 스위치 열린 상태에서는 Input이 1(High)
	* 스위치가 닫힌 상태에선 GND로 전류가 흐름 -> input이 0(Low)
	* 상대적으로 Input(MCU)가 더 높은 상태, GND로 전류가 흐름
* Pull Down -> 스위치가 열린 상태에서 Input에서 GND로 전류가 흐름 -> 0 (Low)
	* 스위치가 닫힌 상태에선 저항으로 인해 Input으로 전류가 흐름 -> 1(High)
![[Pasted image 20260428093442.png]]
```bash
sunbi@Sunbi:~ $ pinout
Description        : Raspberry Pi 4B rev 1.5
Revision           : c03115
SoC                : BCM2711
RAM                : 4GB
Storage            : MicroSD
USB ports          : 4 (of which 2 USB3)
Ethernet ports     : 1 (1000Mbps max. speed)
Wi-fi              : True
Bluetooth          : True
Camera ports (CSI) : 1
Display ports (DSI): 1

,--------------------------------.
| oooooooooooooooooooo J8   +======
| 1ooooooooooooooooooo  J14 |   Net
|  Wi                    12 +======
|  Fi  Pi Model 4B  V1.5 oo      |
| |D     ,---. +---+          +====
| |S     |SoC| |RAM|          |USB3
| |I     `---' +---+          +====
| |0                C|           |
| oo1 J2            S|        +====
|                   I| |A|    |USB2
| pwr   |hd|   |hd| 0| |u|    +====
`-| |---|m0|---|m1|----|x|-------'

J8:
   3V3  (1) (2)  5V    
 GPIO2  (3) (4)  5V    
 GPIO3  (5) (6)  GND   
 GPIO4  (7) (8)  GPIO14
   GND  (9) (10) GPIO15
GPIO17 (11) (12) GPIO18
GPIO27 (13) (14) GND   
GPIO22 (15) (16) GPIO23
   3V3 (17) (18) GPIO24
GPIO10 (19) (20) GND   
 GPIO9 (21) (22) GPIO25
GPIO11 (23) (24) GPIO8 
   GND (25) (26) GPIO7 
 GPIO0 (27) (28) GPIO1 
 GPIO5 (29) (30) GND   
 GPIO6 (31) (32) GPIO12
GPIO13 (33) (34) GND   
GPIO19 (35) (36) GPIO16
GPIO26 (37) (38) GPIO20
   GND (39) (40) GPIO21

J2:
GLOBAL ENABLE (1)
          GND (2)
          RUN (3)

J14:
TR01 TAP (1) (2) TR00 TAP
TR03 TAP (3) (4) TR02 TAP

For further information, please refer to https://pinout.xyz/
```
## interrupt
* 사전적 의미 : 방해하다, 중단시키다
* CPU의 실행을 방해하는 것을 의미 
	* 타의에 의해 신호를 받아 잠시 현 작업을 중단하고 다른 작업을 수행
* 인터럽트 발생 주체 -> 인터럽트 소스
	* 버튼, GPIO의 입력
	* MCU에는 다양한 주변장치 내장, 주변장치는 인터럽트 소스로서의 기능 존재
	* 사건(Event)이 일어나면 인터럽트 발생했다 명칭
	* SW적으로도 인터럽트 발생 가능
* 인터럽트 컨트롤러
	* 사건 발생 여부를 프로그램 상에서 폴링으로 관찰할 경우 타 작업 수행 불가 문제 발생
	* 각 인터럽트 소스들을 관찰, IRQ 발생 시 CPU에 알려주는 역할을 하는 별도의 주변장치 존재 -> 인터럽트 컨트롤러
	* Cortex processor 경우 NVIC(Nested Vectored Interrupt Controller) 주변 장치 존재
* 인터럽트 처리
	1. 현재 실행중인 명령어 완료
	2. CPU에서 해당 인터럽트가 마스킹(ignore) 되었는지 확인, 마스킹 되어 있는 경우 인터럽트 무시
	3. 인터럽트 벡터를 읽어 ISR 주소 값을 읽음
	4. 프로그램 카운터(PC), 사용 중인 레지스터의 값 등을 스택에 저장하고 ISR의 주소를 PC에 저장해 ISR로 점프
	5. ISR 실행
	6. ISR 실행 종료 시 스택에 저장된 레지스터 값들을 복원
	7. 인터럽트 해제(플래그를 클리어)하고 원래 PC 값을 복원, 이전 실행 위치부터 계속 수행
* ISR(Interrupt Service Routine)
	* 인터럽트 요청이 들어왔을 때 수행하는 프로그램 코드로 인터럽트 핸들러라고도 부름
	* 요청 발생 후 ISR이 실행하기까지 수십 사이클의 시간 걸림 -> 인터럽트 지연 시간
* 인터럽트 우선순위
	* 우선 순위에 따라 동시에 발생한 인터럽트 처리
	* Push->ISR1->Pop->Push->ISR2->Pop
	* ISR1과 ISR2 사이의 과정을 테일 체이닝이라는 HW 기법으로 더욱 줄임(Cortex-M)
* 인터럽트 활성화와 비활성화
	* 인터럽트 소스에 대해 IRQ가 발생하는 경우 인터럽트 활성화
	* 인터럽트 소스에 대해 IRQ가 발생하지 않는 경우 인터럽트 비활성화
	* 인터럽트 비활성화 경우 해당 인터럽트에 대해 MASK를 씌웠다 함
	* 활성화 한 경우 Unmask라고 부름
	* 마스크 설정 불가능 경우 존재 -> NMI(non-maskable interrupt)
		* 반드시 처리, 무시 할 경우 치명적인 문제 발생
		* NMI가 타 마스크 가능한 인터럽트에 비해 우선순위 높음
* background / foreground
	* background : 인터럽트 없이 동작하는 SW task -> main() func의 무한루프 상 처리 과정
	* foreground : 인터럽트에 의한 처리 task
		* 전면에 나와 동작하고 있다 취급
#### External Interrupt
* EXTI 입력 라인은 이벤트/인터럽트 요청을 생성하기 위한 edge detector로 구성
* Low -> High 상승 edge, High->Low 하강 edge 둘 중 하나에서 인터럽트 요청
* 양쪽 모두에서 인터럽트 요청 또한 가능
* 각 입력 라인은 유형과 해당 트리거 이벤트를 선택하도록 독립적 구성 가능
* 각 입력 라인은 인터럽트 사용 여부에 따라 독립적으로 마스킹 가능
![[Pasted image 20260428152703.png]]
![[Pasted image 20260428152907.png]]
=> 인터럽트를 통한 간접 제어 가능