---

[UART: A Hardware Communication Protocol Understanding Universal Asynchronous Receiver/Transmitter | Analog Devices](https://www.analog.com/en/resources/analog-dialogue/articles/uart-a-hardware-communication-protocol.html)

### UART?

- UART = Univeral Asynchronous Reciver-Transmitter
- Device to Device communication protocol
- single line, wire를 통해 데이터가 이동함
- 보통 2개의 와이어(Tx, Rx)를 이용해 시리얼 데이터 통신을 한다
- Serial 통신은 적은 회로와 연결 선을 요구하며, 어플리케이션의 시스템 구현 비용절감을 지원한다

### “통신의 가장 큰 문제는 공간의 차지다”

- 통신 프로토콜은 기기 사이에서 구축된 규칙에 따라 실행된다
- 시스템 요구에 의해 다르게 디자인 되어있음
- 성공적인 통신을 위해서 기기 사이에 특정한 규칙을 규정함
- 임베디드 시스템, MCU, 컴퓨터들은 대부분 Device to Device 형태의 하드웨어 통신 사이에서는 UART를 사용한다
- 비동기적 통신을 사용한다

![image.png](attachment:3b381b44-f3fd-4fc1-94f4-5a24e93d1433:image.png)

⇒ Transmitter(Tx), Reciver(Rx)

- 시리얼 통신에서 전송 및 수신을 위해 Tx, Rx를 사용

![image.png](attachment:f70a0ba0-7417-4d71-97d6-98126d1e5036:image.png)

- Tx UART는 컨트롤 병렬 데이터 전송 형태의 데이터 버스와 연결되어있음
- 이렇게 받아온 데이터는 전송선을 통해 일렬, 비트단위로 하나씩 전송
- 데이터를 받은 수신용 UART는 직렬 데이터를 병렬 데이터로 변환, 수신 장치가 사용할 수 있도록 전달
- UART 라인은 데이터를 서로 주고 받기 위한 통신 매체 역할
- UART 장치는 데이터를 전송하거나 수신할 때 전용으로 사용하는 Tx, Rx를 갖고 있다는 점을 기억

### UART 및 대부분의 직렬 통신

- 송수신 장치를 모두 동일한 BaudRate(초당 비트 수)를 설정 해야 함
- 직렬 포트 통신에는 설정된 보드레이트가 1초동안 전송 가능한 최대 비트 수를 결정

|Wires|2|
|---|---|
|Speed|9600, 19200, 38400, 57600, 115200, 230400, 460800, 921600, 1000000, 1500000|
|Methods of Transmission|Asynchronous|
|Maximum Number of Masters|1|
|Maximum Number of Slaves|1|

- UART 인터페이스는 송신기와 수신기 간 동기화를 위해 클록 신호 사용 안함
- 비동기 방식으로 데이터 전송
- 송신기는 내부 클록을 기반으로 Bitstream 생성, 데이터를 전송
- 수신기는 자신 내부 클록 신호를 통해 도착하는 데이터를 샘플링하며 읽음
- 각자 다른 장치가 정확하게 데이터를 주고 받을 수 있도록 동기화 기준을 세움 : 보드레이트
- 송수신기의 보드레이트가 같아야 정확히 데이터 타이밍이 맞음
- 다르면 타이밍이 어긋나 오류 또는 불일치 발생
- 일반적으로 보드레이트는 최대 10%까지 차이가 나도 통신 유지
- 10% 이상 차이 나면 어긋나 정확한 데이터 전송에 어려움

### Data Transmission

- UART에서 송신은 패킷의 형태를 띈다
- 송수신기를 연결하는 부분은 Serial 패킷을 생성
- 패킷이 오가는 물리적인 하드웨어 라인을 제어하는 역할 담당

⇒ 송수신기를 연결하는 회로는 실 데이터를 주고 받는 하드웨어 선까지 제어

- 패킷은 시작 비트, 데이터 프레임, 페리티 비트, 정지 비트를 포함한다

![image.png](attachment:feaff4ce-d3e1-4033-ba90-0b4114c04b41:image.png)

### Start bit

- data 전송 라인은 보통 데이터 전송을 하지 않을 때 높은 전류를 유지
- 데이터 전송을 시작하려면, 송신 UART는 1클록 사이클 동안 전송 라인의 신호를 높은 상태에서 낮은 상태로 내려줌

⇒ 전압을 낮춰 데이터 전송의 개시를 알림

- 수신 UART가 전압의 하강을 감지했다면, 보더레이트만큼 데이터 프레임의 비트를 읽기 시작

![image.png](attachment:a3c58a6c-a8b4-40d7-8f29-c4a11d71aa36:image.png)

### Data Frame

- 실제 전송되는 데이터를 포함함
- 패리티 비트를 사용하는 경우, 5-8bit까지 될 수 있음
- 패리티 비트를 사용하지 않는 경우 최대 9bit까지 가능
- 대부분의 경우, 최하위 비트(Least Significant Bit, LSB)부터 전송
- e.g. ) 13(00001101)의 경우 → 1 - 0 - 1 - 1 - 0 - 0 - 0 - 0 형태로 전송

![image.png](attachment:e52a90cf-2e16-4e80-b4cf-9c1432820936:image.png)

### Parity

- 값이 변했는지 수신 UART가 확인하기 위해 사용
- 전자기파 간섭, 보드레이트 불일치, 장거리 전송의 이유로 비트값의 변화
- 수신용 UART는 데이터를 전부 읽은 후 1(High)의 개수를 셈
- 합이 odd/even 검사
- 패리티 0 → 짝수, 1의 개수 짝수
- 패리티 1 → 홀수, 1의 개수 홀수
- 개수 일치 → 오류 없이 데이터의 정상 도착을 의미
- 다르면 손상

![image.png](attachment:923c0932-c165-4fa1-9093-83dc8361af8b:image.png)

### Stop Bits

- 데이터 패킷의 전송의 끝을 알림
- 송신용 UART는 전송 라인의 전압을 Low→High 전환
- 1-2bit 길이 동안 유지

![image.png](attachment:b7d3f56d-b09d-4bf1-a8ca-fd9d62a3b828:image.png)

### Steps of UART Transmission

1. 송신용 UART는 데이터버스로부터 병렬 형태의 데이터를 받음

![image.png](attachment:fcca6bdf-ca61-4046-9e40-4d152e6ddccc:image.png)

1. 송신용 UART는 Start Bit, Parity Bit, Stop Bit를 데이터 프레임에 추가

![image.png](attachment:ae95b6e7-ef7c-4595-bd0c-938d4bc9f5c2:image.png)

1. 전체 패킷은 Start Bit부터 Stop Bit까지 Serial 방식으로 전송, 수신 UART는 설정된 Baudrate에 맞춰 데이터 라인을 샘플링

![image.png](attachment:38c7947f-d7a2-406a-86a4-3d2979f44ee0:image.png)

⇒ 이 때 Start, Parity, Stop Bit 해석

1. 수신 UART는 Start Bit, Parity Bit, Stop Bit을 데이터 프레임에서 제거(무시)

![image.png](attachment:470b9d06-447a-448c-9018-b45dc83c3b7a:image.png)

1. 수신 UART는 Serial 데이터를 다시 병렬 데이터로 변환, 수신측의 데이터 버스로 전달

![image.png](attachment:39d80e60-6c3f-4945-b5c3-44f54d85a4b9:image.png)

### Frame Protocol

- UART에서 사용할 수 있지만 완전히 활용되지 않은 핵심 기능 중 하나
- 각 장치에 대해 보안성과 보호 기능 추가 제공
- 동일한 UART 프레임 프로토콜 사용 → 설정은 확인안하고 같은 UART에 연결하면 서로 다른 핀에 연결, 시스템 오작동 발발 가능
- 구현 시 : 수신한 정보를 설계된 프레임 프로토콜에 맞춰 파싱 ⇒ 보안성 확보
- 헤더, 트레일러 설정 가능
- 필요에 따라 CRC 등 포함시켜 장치별로 차별화할 수 있음

⇒ 메모리 맵에서 UART 주소 확인

![image.png](attachment:c6f8256a-862e-4e52-a65d-a205411c7d91:image.png)

- 그림 기준, 각 장치에 고유한 헤더, 트레일러, CRC 설정 가능
    
- 헤더 1 (H1 : 0xAB)과 (H2: 0xCD)
    
    - 헤더는 올바른 장치와 통신하고 있는지를 식별하기 위한 고유 식별자
- 명령어(command, CMD) 선택
    
    - 명령어는 두 장치 간 통신을 위해 설계된 명령어 리스트에 따라 결정
- 명령어별 데이터 길이(Data Length, DL)
    
    - 데이터 길이는 선택된 명령어에 따라 결정
    - 명령어에 따라 전송 가능한 데이터의 길이 최대화 가능, 데이터 길이 가변적
- 데이터 n (가변 데이터, Varying Data)
    
    - 데이터는 장치 간 전송되는 실제 페이로드
- 트레일러 1 (T1: 0xE1)과 트레일러 2 (T2: 0xE2)
    
    - 트레일러는 데이터 전송이 완료된 후 추가되는 데이터
    - 헤더와 마찬가지로 고유 식별자로 설정 가능
- 순환 중복 검사(Cyclic Redundancy Checking, CRC 공식)
    
    - 원시 데이터의 우발적인 변경을 감지하기 위한 추가적인 오류 검출 방식
    - 송신 장치의 CRC 값은 항상 수신 장치에서 계산된 CRC 값과 일치
- 주의 :
    
    - UART 장치에 대해 프레임 프로토콜을 구현, 보안을 강화하는 것이 권장
    - 프레임 프로토콜은 송신기와 수신기 양쪽 모두에서 동일한 설정으로 구성

### UART 작업 절차

- 하드웨어 통신 프로토콜을 사용할 때는 반드시 데이터시트와 하드웨어 참조 매뉴얼을 먼저 확인
    
- 첫번째 :
    
    - 장치의 데이터시트 인터페이스를 확인

![image.png](attachment:51eb2909-eaf3-4767-ac92-b236ba5b5c56:image.png)

- 세번째 :
    
    - UART 포트의 운용 모드, 데이터 비트 길이, 패리티 비트, 정지 비트와 같은 구체적인 설정 사항 확인 → 현 데이터 시트에서 UART 포트 세부 정보의 예시는 다음과 같음 : UART Port
    - 샘플 MMCU들은 풀 듀플렉스 UART 포트 제공, 이는 PC 표준 UART와 완전히 호환
    - UART 포트는 다른 주변 장치나 호스트와의 연결을 위해 단순화된 UART 인터페이스 제공
    - 풀 듀플렉스, DMA, 그리고 비동기 직렬 데이터 전송 지원
    - UART 포트는 5-8비트 데이터 길이, 패리티 없음, 짝수, 홀수 패리티 지원
    - 하나의 프레임은 1.5비트 또는 2비트 정지 비트로 종료
- 네번째 :
    
    - 보오율(baud rate) 계산을 포함, UART 동작 세부 사항 확인
        
    - 아래 예시 공식으로 설정, MCU에 따라 공식 가변
        
    - UART 동작 세부사항 예시
        
        - 데이터 비트 : 5-8bit
        - 정지 비트 : 1, 2 | 1.5 bit
        - 패리티 : None, Even, Odd
        - 오버 샘플 비율 : 4, 8, 16, 32 중 프로그래밍 가능
    - 보오율 공식
        
        $\text{Baud rate} = \frac{\text{PCLK}}{\left( M + \frac{N}{2048} \right) \times 2^{\text{OSR}} + 2 \times \text{DIV}}$
        
        - OSR(oversample rate) : UART_LCR2.OSR 값 : 0-3
        - DIV(baud rate divider) : UART_DIV 값 : 1-65535
        - M(DIVIM fractional baud rate M) : UART_FBR.DIVM 값 : 1-3
        - N(DIVN fractional baud rate N) : UART_FBR.DIVN 값 : 0-2047
- 다섯번째 :
    
    - 보오율 설정 시 어떤 주변 장치 클록(PCLK)을 사용할지 반드시 확인
    - 해당 예시에서는 26MHz PCLK와 16MHz PCLK 사용 가능
    - 또한 **OSR**, **DIV**, **DIVM**, **DIVN** 값은 **기기마다 다르다**는 점에 유의해야 합니다.

![image.png](attachment:eff84081-6aa4-4a69-ab0e-2c3d0d9157f2:image.png)

![image.png](attachment:72745aa8-c793-43b2-a3b0-95fe2a4a284e:image.png)

- 여섯번째
    - 다음 단계는 UART 설정을 위한 세부 레지스터 확인
    - 보오율 계산에 사용되는 UART_LCR2, UART_DIV, UART_FBR와 같은 파라미터 살펴보기

![image.png](attachment:7faceed2-3367-4d95-88e2-858132ac41fe:image.png)

- 일곱번째
    - 각 레지스터 항목에서 세부 필드와 값 확인
    - 그 값을 보오율 계산식에 대입, 보오율 산출
    - 그 다음 UART 구현(초기화/설정) 시작

### 왜 중요함?

- UART 통신 프로토콜에 익숙해지는 것 → 견고/품질 중심의 제품 개발에 유리
- 단 두 가닥의 선으로 데이터 전송하는 방법과, 전체 데이터 패킷 또는 페이로드 전송하는 방법 이해 → 데이터 오류 없이 송수신 보장 도움
- 가장 널리 사용되는 HW 통신 프로토콜, 유연한 디자인 가능

### 활용 사례

- 디버깅 : 시스템 발생 메시지 캡처, 과정 지원 가능
- 제조 기능 수준 추적 : 생산 라인에서 무슨 일이 일어나는지 작업자에게 알려줌, 기능 판단에 도움
- 고객/클라이언트 업데이트 : SW 업데이트는 매우 중요, 업데이트가 가능한 SW와 이를 지원하는 완전하고 유연한 HW를 갖추는 것은 완성도 높은 시스템을 위해 필수
- 테스트/검증 : 제품이 제조 공정을 마치기 전 검증하는 것은 고객에게 가능한 최고의 품질의 제품을 제공하는데 도움