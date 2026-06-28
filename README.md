# 📚 VEDA C Language Study

> C언어부터 임베디드 시스템, Linux까지 — VEDA 교육과정 학습 기록 저장소입니다.  
> 브랜치별로 학습 단계가 분리되어 있습니다. 아래에서 원하는 주제를 선택하세요.

---

## 🗺️ 브랜치 구조

```
main (현재)         ← 전체 안내 허브
├── stage/c-cpp     ← C / C++ 기초~OOP 심화
├── stage/qt        ← Qt 프레임워크
├── stage/embedded  ← 임베디드 시스템 (ARM/STM32/RPi)
├── stage/linux     ← Linux & Bash 시스템 프로그래밍
└── group-study     ← 알고리즘 그룹 스터디
```

---

## 🔀 브랜치별 학습 내용

### 🔵 [stage/c-cpp](../../tree/stage/c-cpp) — C / C++ 기초~OOP 심화
> **Week 1 ~ Week 3** | 강의 노트 + 실습 코드

| 핵심 주제 |
|-----------|
| C 기초 문법, 함수, 배열, **포인터**, 동적 메모리 관리 |
| 구조체(`typedef struct`), 공용체, 열거형, 파일 입출력 |
| C++ 레퍼런스, 예외처리, **OOP** (클래스/상속/다형성/가상함수) |
| 복사 생성자, 정적 멤버, **템플릿(Template)**, **STL 컨테이너** |

---

### 🟣 [stage/qt](../../tree/stage/qt) — Qt 프레임워크
> **Week 4** | 강의 노트 + 실습 코드

| 핵심 주제 |
|-----------|
| Qt 아키텍처(MVC), CMake/QMake 빌드, **QMainWindow** |
| QCheckBox, QComboBox, Qt Designer, **Signal/Slot** |
| Layout, QString, QVariant, QMap/QHash |
| **QDialog**, **Model-View 아키텍처**, **QPainter** 2D 그래픽스 |

---

### 🟠 [stage/embedded](../../tree/stage/embedded) — 임베디드 시스템
> **Week 5 ~ Week 6 (Day26~27)** + **Protocol/** | 강의 노트 + 실습 코드

| 핵심 주제 |
|-----------|
| **멀티스레드**, Mutex, DeadLock, Race Condition |
| **ARM 어셈블리(ASM)**, Cortex-M4, 크로스 컴파일 환경 |
| MCU 구조, DMA/Timer/GPIO, **인터럽트**(NVIC/ISR/EXTI) |
| **UART/SPI/I2C** 통신 프로토콜, STM32 HAL/CMSIS |
| Raspberry Pi GPIO, wiringPi LED/버튼 제어 |

---

### 🟢 [stage/linux](../../tree/stage/linux) — Linux & Bash 시스템 프로그래밍
> **Week 6 (Day28~29) ~ Week 9** | 강의 노트 (실습 코드: MD 내 코드블록)

| 핵심 주제 |
|-----------|
| 운영체제 구조, Kernel, 리눅스 배포판, 파일시스템 |
| SoftLink/HardLink(inode), 사용자/권한 관리(chmod/chown) |
| **프로세스 관리**, PCB, IPC(파이프/소켓/공유메모리/세마포어) |
| **Bash 스크립팅** (변수/조건문/반복문/함수/확장/리디렉션/파이프라인) |
| **systemd**, systemctl, bashrc, alias, CLI 툴(grep/find/awk) |

---

### 🔷 [stage/linux-sys](../../tree/stage/linux-sys) — Linux 시스템 프로그래밍 심화
> **Week 8~9 (Day34, 36, 37, 38)** | 강의 노트 + 실습 코드

| 핵심 주제 |
|-----------|
| **GCC** 컴파일 파이프라인 (전처리/컴파일/어셈블/링킹), ELF 포맷 |
| **정적/공유/동적 라이브러리** (.a, .so, dlopen) |
| **GDB** 디버거 — break/watch/step/backtrace, core 파일 분석 |
| **CMake** 빌드 시스템 — 타깃 기반 모던 CMake, find_package |
| **Docker** 컨테이너 — 이미지/컨테이너 구조, Dockerfile, 아키텍처 |
| **Linux 시스템 콜** — errno, 환경변수, My Shell 구현 (fork/exec/wait) |
| **저수준 파일 I/O** — open/read/write/lseek, 파일 디스크립터, ioctl |
| **디렉토리 제어** — opendir/readdir/mkdir/chdir, dup/dup2 |
| **프로세스 제어** — fork/system/wait/waitpid/exit, 좀비 프로세스 |

---

### 🟤 [main](../../tree/main) — 임베디드 리눅스 시스템 & 디바이스 제어 (Week 10 ~ Week 14)
> **Week 10 ~ Week 14** | 강의 노트 + 실습 코드 + 시험 대비 정리

| 핵심 주제 |
|-----------|
| **멀티스레드 & 네트워크** — TCP/UDP 소켓 프로그래밍, epoll I/O 멀티플렉싱 |
| **디바이스 드라이버** — 리눅스 커널 구조, mknod 디바이스 파일 생성, LED GPIO 제어 |
| **임베디드 리눅스 빌드** — U-Boot 부트로더 포팅, Yocto Project (Poky, BitBake) 구축 |
| **디버깅 & 영상처리** — ftrace 커널 트레이싱, OpenCV 기반 컬러 제어 및 영상 처리 |

---

### 🔴 [group-study](../../tree/group-study) — 알고리즘 그룹 스터디
> 교육과정 外 알고리즘 스터디 | C/C++ 구현 코드

| 분류 | 내용 |
|------|------|
| **정렬** | 버블/선택/삽입/셸(Shell)/병합(Merge) 정렬 |
| **탐색** | 이진 탐색 (Binary Search), BOJ 1920 |
| **재귀** | 재귀 기초, 합계 계산, 피보나치 수열 |
| **BOJ** | 2751 (정렬 비교 TLE 분석), 1920 (이진 탐색) |

---

## 📅 전체 커리큘럼 개요

| 단계 | 주차 | 내용 | 브랜치 |
|------|------|------|--------|
| 1️⃣ | Week 1~3 | C 기초 → C++ OOP 심화 | `stage/c-cpp` |
| 2️⃣ | Week 4 | Qt 프레임워크 | `stage/qt` |
| 3️⃣ | Week 5~6 | 임베디드 시스템 & ARM | `stage/embedded` |
| 4️⃣ | Week 6~7 | Linux & Bash | `stage/linux` |
| 5️⃣ | Week 8~9 | GCC/GDB/CMake/Docker, 시스템 프로그래밍, 프로세스 제어 | `stage/linux-sys` |
| 6️⃣ | Week 10~11 | 네트워크 프로토콜 (TCP/UDP), 멀티스레드, epoll 멀티플렉싱 | `main` |
| 7️⃣ | Week 12 | 리눅스 커널 모듈 & GPIO 디바이스 드라이버 | `main` |
| 8️⃣ | Week 13 | 부트로더(U-Boot) 포팅 & Yocto 빌드 시스템 구축 | `main` |
| 9️⃣ | Week 14 | ftrace 커널 디버깅 & OpenCV 영상 처리 | `main` |
| ➕ | - | 알고리즘 그룹 스터디 | `group-study` |

---

## 📝 시험 대비 정리

- [Week 12-13 시험 대비 정리](Week12_13_시험대비_정리.md): Week 12~13 범위 (리눅스 커널, 디바이스 드라이버, U-Boot, Yocto)의 내용을 단권화하여 정리한 요약본입니다.

---

## 🛠️ 개발 환경

| 항목 | 내용 |
|------|------|
| 언어 | C (C99/C11), C++, Bash |
| IDE | Visual Studio, VS Code, Qt Creator, STM32CubeIDE |
| 컴파일러 | MSVC (cl.exe), GCC/G++, Qt (MSVC/MinGW), arm-none-eabi-gcc |
| 플랫폼 | Windows, Linux (WSL2), STM32 Nucleo401RE, Raspberry Pi 4B |

---

## 👤 Author

- **분야**: C언어 시스템 프로그래밍 / 임베디드 / 알고리즘
- **목표**: 하드웨어 제어부터 시스템 프로그래밍까지 가능한 시스템 전문가

---

*학습 중인 내용으로, 지속적으로 업데이트됩니다. 🚀*
