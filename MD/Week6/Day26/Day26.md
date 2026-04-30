## Protocol
[[UART, SPI, I2C 비교]]
#### VCC & GND
![[Pasted image 20260427110428.png]]
* 전류는 높->낮
-> Switch Off => 0
-> Switch On => 1
* V=IR => 저항에 따라 전압 세기 조절
* Pull-up / Pull-down
	* 전선 자체에 저항 존재
	* 과전류 방지를 위해 저항 부착
	* 저항 부착 위치
		* PullUp -> VCC
		* PullDown -> GND
* Rising Edge / Falling Edge
	* 누르는 동안(stable)?
	* 누르고 나서?
	* 떼고 나서?
	* 신호의 변화를 기준으로 신호 규정
#### Serial(Uart, Usart) Protocol
![[Pasted image 20260427111352.png]]
* 데이터를 보낸다
	* 버튼을 누른다/땐다의 파형이 오가는 것
* 통신 시 충돌 발생 가능 => Recive, Transmit의 분리를 통한 통신선 분리
* Start Bit / Stop Bit을 통한 시작/끝 지점 명시 가능
* 데이터 송수신 시 baudrate 존재
#### USART -> Uart + Timer
* 신호 전송 시 Timer Signal 존재, 각 Timer의 Tick마다 상태를 읽음

#### SPI
![[Pasted image 20260427112837.png]]
* Data Line + Contoll Line 따로 존재
* SCLK / MOSI / MISO / SS(CS)

#### I2C
![[Pasted image 20260427113635.png|412]]
* SPI와 달리 I2C는 마스터/슬레이브의 구조가 동일함
* I2C 버스 내부에서 주소만 다르게 진행하기에 효율적

### UART / SPI / I2C
| 구분          | **UART**                              | **SPI**                                     | **I²C**                                |
| ----------- | ------------------------------------- | ------------------------------------------- | -------------------------------------- |
| **배선**      | TX, RX (2선, GND 제외)                   | MOSI, MISO, SCLK, CS (4선+장치당 CS 추가, GND 제외) | SCL, SDA (2선, GND 제외)                  |
| **통신 방식**   | 비동기 (Start/Stop bit, Baud rate 맞춤 필요) | 동기 (클록 공유, 풀 듀플렉스)                          | 동기 (클록 공유, 반이중, 멀티마스터 지원)              |
| **속도**      | 수백 kbps ~ 수 Mbps (보통 1~2 Mbps 내외)     | 수 MHz ~ 수십 MHz (10~50 MHz 이상도 가능)           | 표준 100 kbps, 패스트 400 kbps, 고속 3.4 Mbps |
| **장치 연결**   | 1:1 전용 통신                             | 1:N (CS 핀 개수만큼 확장)                          | 1:N (주소 기반, 최대 127개 슬레이브)              |
| **데이터 전송**  | 반이중(Full-duplex 아님), 단순               | 풀 듀플렉스                                      | 반이중                                    |
| **하드웨어 요구** | 단순, 거의 모든 MCU 내장                      | 클록·라인 많음, 회로 복잡                             | 풀업 저항 필요, 버스 공유                        |
| **에러 검출**   | 패리티 비트 가능, 비교적 단순                     | 기본적으론 없음(상위 프로토콜 필요)                        | ACK/NACK 신호 제공                         |
| **주요 사용처**  | PC ↔ MCU, 디버깅, GPS, 블루투스 모듈           | 센서(고속), 디스플레이, 플래시 메모리                      | 저속 센서, RTC, EEPROM, 주변기기 제어            |
#### STM32 Coretex-M4 Register
![[Pasted image 20260427120920.png]]
#### STM32 Coretec-M4 Memory Map
![[Pasted image 20260427121010.png]]
#### Nucleo401RE Pin Map
![[Pasted image 20260427121031.png]]
![[Pasted image 20260427121041.png]]
