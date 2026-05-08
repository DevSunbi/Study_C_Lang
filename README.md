# 🟠 stage/embedded — 임베디드 시스템 학습 노트 & 실습 코드

> VEDA 교육과정 中 **멀티스레드, ARM 어셈블리, MCU, STM32, Raspberry Pi, 통신 프로토콜**을 다루는 브랜치입니다.

---

## 🗂️ 브랜치 구조

```
stage/embedded/
├── MD/
│   ├── Week5/          # 스레드, ARM ASM, 임베디드 HW 강의 노트
│   │   ├── Day 21/     # Thread Programming, Mutex, DeadLock
│   │   ├── Day 22/     # Qt 계좌 관리 실습
│   │   ├── Day 24/     # 임베디드 기초, MCU, ARM, RISC/CISC
│   │   └── Day 25/     # 크로스 개발환경, g++ options, ASM, Memory Map
│   ├── Week6/
│   │   ├── Day26/      # UART/SPI/I2C 비교, STM32 Register/Memory Map
│   │   └── Day27/      # Raspberry Pi GPIO, 인터럽트, EXTI
│   └── Protocol/       # 통신 프로토콜 상세 정리 (UART, SPI, I2C, MCU, IMU)
└── workspace/
    ├── Week5/          # ARM 어셈블리 실습 (.s 파일)
    └── Week6/
        ├── Day26/      # STM32 LED 프로젝트 (HAL, CMSIS 드라이버)
        │   ├── STMLedProject/
        │   └── STMLedProject_2/
        └── Day27/      # Raspberry Pi GPIO 제어 (wiringPi)
            └── led.cpp
```

---

## 📅 학습 커리큘럼

| 주차 | 일차 | 주제 | 핵심 내용 |
|------|------|------|-----------|
| **Week 5** | Day 21 | Thread Programming | **멀티스레드** 개념, Thread Pool/Ready Pool, Race Condition, **Mutex**, **DeadLock** 4조건 |
| **Week 5** | Day 22 | Qt 계좌 관리 프로그램 | Qt 기반 계좌 관리 시스템 실습 |
| **Week 5** | Day 24 | 임베디드 기초 & MCU HW | **임베디드 시스템** 개요, NTCR, MCU 구조, DMA/Timer/RTC/GPIO, **Register**, **인터럽트** |
| **Week 5** | Day 25 | 크로스 개발환경 & ARM ASM | **크로스 컴파일**, g++ options, **ARM(RISC) vs CISC**, **Cortex-M4**, Branch 명령어, Memory Map |
| **Week 6** | Day 26 | 통신 프로토콜 & STM32 기초 | **UART/SPI/I2C** 비교, VCC/GND/PullUp/PullDown, STM32 Cortex-M4 Register & Memory Map |
| **Week 6** | Day 27 | Raspberry Pi GPIO & 인터럽트 | PullUp/PullDown 회로, RPi4B pinout, **인터럽트** 동작원리, ISR, NVIC, **EXTI** 설정 |

---

## 🔑 핵심 학습 목표

- ✅ **멀티스레드(Thread)** — Thread Pool, Race Condition, Mutex(lock/unlock), DeadLock 4조건
- ✅ **임베디드 시스템 기초** — NTCR(Nature/Time/Constraint/Reliability), MCU 구조, firmware
- ✅ **임베디드 HW** — DMA Controller, Timer, RTC, GPIO, Register(PC/LR/SP), 인터럽트 벡터
- ✅ **크로스 개발환경** — PC(CISC) vs Embedded(ARM RISC), 크로스 컴파일 5단계(pre-process→hex)
- ✅ **ARM 어셈블리(ASM)** — `.arm/.text/.global`, MOV/ADD/CMP/BEQ/BL/BX, Cortex-M4, Branch
- ✅ **ARM 메모리 맵** — Code(ROM)/Data(RAM) 영역, Stack, 파이프라이닝(F-D-E-W)
- ✅ **통신 프로토콜** — UART(비동기/Start-Stop bit), SPI(SCLK/MOSI/MISO/SS), I2C(마스터/슬레이브/주소 기반)
- ✅ **STM32 임베디드** — Cortex-M4 Register, STM32 Memory Map, Nucleo401RE Pin Map, HAL/CMSIS 기반 LED
- ✅ **인터럽트 심화** — 인터럽트 소스/컨트롤러(NVIC), ISR, 우선순위, Tail-Chaining, EXTI, Masking/NMI
- ✅ **Raspberry Pi GPIO** — wiringPi 라이브러리, PullUp/PullDown 회로, RPi4B pinout, LED/버튼 제어

---

## 🔗 관련 브랜치

| 브랜치 | 내용 |
|--------|------|
| [`main`](../../tree/main) | 전체 프로젝트 소개 |
| [`stage/c-cpp`](../../tree/stage/c-cpp) | C / C++ 기초~OOP (Week1~3) |
| [`stage/qt`](../../tree/stage/qt) | Qt 프레임워크 (Week4) |
| [`stage/linux`](../../tree/stage/linux) | Linux / Bash (Week6~7) |
| [`group-study`](../../tree/group-study) | 알고리즘 스터디 |
