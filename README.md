# 📟 stage/embedded-linux — 임베디드 리눅스 시스템 & 디바이스 제어 학습 노트

> VEDA 교육과정 中 **리눅스 커널 모듈, 캐릭터 디바이스 드라이버, GPIO 제어, U-Boot 부트로더 포팅, Yocto Project 기반 OS 빌드, ftrace 디버깅 및 OpenCV 영상 처리**를 다루는 브랜치입니다.

---

## 📁 브랜치 구조

```
stage/embedded-linux/
├── MD/
│   ├── Week12/
│   │   ├── Day50/   ← 리눅스 커널 구조, 모듈형 디바이스 드라이버 개요
│   │   ├── Day51/   ← 장치 파일 생성(mknod), 가상 디바이스 드라이버 개발
│   │   ├── Day52/   ← LED/스위치 제어를 위한 GPIO 드라이버 설계 및 MMIO
│   │   └── Day53/   ← sysfs 및 인터럽트 연동 커널 모듈 작성
│   ├── Week13/
│   │   ├── Day54/   ← 임베디드 리눅스 아키텍처 개요, 빌드 툴체인
│   │   ├── Day55/   ← U-Boot 부트로더 커스텀 보드 포팅 및 부팅 흐름
│   │   ├── Day56/   ← Yocto Project 기본 개념 및 환경 설정
│   │   └── Day58/   ← Poky 배포판, BitBake 레시피 작성 및 루트 파일시스템 빌드
│   ├── Week14/
│   │   ├── Day59/   ← ftrace를 이용한 커널 디버깅 및 프로파일링
│   │   ├── Day60/   ← OpenCV 영상 처리 개요, HSV/RGB 컬러 모델
│   │   ├── Day61/   ← 픽셀 수준 이진화(Threshold) 및 룩업테이블 적용
│   │   └── Day62/   ← 기하학적 투영 변환(Perspective Transform) 및 필터링
│   └── Protocol/    ← UART, SPI, I2C 통신 프로토콜 정리
├── Week12_13_시험대비_정리.md  ← 시험 대비 핵심 요약 단권화 문서
└── README.md
```

---

## 📚 학습 내용

### 🔌 Week 12 — 리눅스 디바이스 드라이버

#### Day50 — 리눅스 커널 & 모듈 프로그래밍
| 핵심 주제 |
|-----------|
| **리눅스 커널 구조** — 자원 관리, 가상 파일시스템(VFS), 유저 영역과의 API 추상화 |
| **커널 모듈** — 동적 모듈 적재 및 커널 확장, `module_init()`, `module_exit()` |
| **모듈 명령어** — `insmod`(적재), `rmmod`(제거), `lsmod`(조회), `modinfo`(정보 확인) |
| **디렉터리 및 slab** — 커널 메모리 동적 할당 (`kmalloc`, `<linux/slab.h>`) |

#### Day51 — 캐릭터 디바이스 드라이버 & 장치 파일
| 핵심 주제 |
|-----------|
| **장치 파일 생성** — `mknod` 장치 파일 수동 생성 (`/dev`), 주 번호(Major) 및 부 번호(Minor) |
| **file_operations 구조체** — `open`, `read`, `write`, `unlocked_ioctl` 등 시스템 콜 함수 포인터 매핑 |
| **유저-커널 데이터 교환** — `copy_to_user()` (커널→유저), `copy_from_user()` (유저→커널) |
| **동적 디바이스 드라이버 등록** — `alloc_chrdev_region()`, `cdev_init()`, `cdev_add()` 및 `class_create()`, `device_create()` 자동 생성 |

#### Day52 — GPIO 드라이버 & MMIO 제어
| 핵심 주제 |
|-----------|
| **BCM2711 레지스터** — 라즈베리파이 4 GPIO 컨트롤러, MMIO 가상 주소 매핑 |
| **레지스터 가상 매핑** — `ioremap()`, `iounmap()` 함수를 통한 물리 주소 접근 |
| **GPIO 입력/출력 설정** — 함수 선택 레지스터(GPFSEL), 출력 설정(GPSET), 출력 해제(GPCLR) |
| **GPIO 드라이버 구현** — 유저 영역 write 요청을 통해 LED On/Off를 수행하는 드라이버 코드 실습 |

#### Day53 — 드라이버 활용 & 모듈 배포
| 핵심 주제 |
|-----------|
| **커널 모듈 종속성** — `depmod -a` 명령어로 모듈 종속성 파일 생성 |
| **자동 모듈 적재** — `/etc/modules` 등록 혹은 `modprobe`를 활용한 의존성 자동 로드 |

---

### 🔩 Week 13 — 임베디드 리눅스 & Yocto 빌드 시스템

#### Day54 — 임베디드 리눅스 개요
| 핵심 주제 |
|-----------|
| **임베디드 리눅스 아키텍처** — 툴체인, 부트로더, 커널, 루트 파일시스템, 어플리케이션 계층 구조 |
| **리눅스 부팅 프로세스** — SoC ROM code → SPL → U-Boot → Linux Kernel → Systemd(Init) |

#### Day55 — U-Boot 부트로더
| 핵심 주제 |
|-----------|
| **U-Boot** — 오픈소스 임베디드 부트로더 기능, 메모리 적재 및 디바이스 커맨드 제어 |
| **부팅 인자** — `bootargs` 커널 부팅 파라미터(rootfs 위치, 콘솔 터미널 설정 등) 전달 |
| **커스텀 보드 포팅** — 신규 보드 구성을 위한 보드 초기화 소스코드 분석 및 환경설정 |

#### Day56 — Yocto Project 기초
| 핵심 주제 |
|-----------|
| **Yocto Project** — 커스텀 임베디드 Linux OS 빌드 시스템 개념, 메타데이터 구조 |
| **주요 구성요소** — 레시피(`.bb`, `.bbappend`), 레이어(`meta-`), BitBake 빌드 엔진 |
| **빌드 과정** — Source Fetch → Patch → Compile → Package → Image 생성 흐름 |

#### Day58 — Poky & BitBake 심화
| 핵심 주제 |
|-----------|
| **Poky 레퍼런스 시스템** — Poky에 포함된 OE-Core, BitBake, 메타데이터 구조 |
| **BitBake 변수** — `PV`, `PR`, `DEPENDS`, `RDEPENDS`, `FILES` 등 주요 문법 |
| **루트 파일시스템 빌드** — 빌드 디렉토리 구성(`conf/local.conf`, `conf/bblayers.conf`) 및 빌드 프로세스 실행 |

---

### 🧵 Week 14 — 커널 디버깅 & OpenCV 영상 처리

#### Day59 — ftrace 커널 트레이싱
| 핵심 주제 |
|-----------|
| **ftrace 개념** — 커널 내부 동작을 기록 및 추적하는 리눅스 공식 트레이서 |
| **debugfs 마운트** — `/sys/kernel/debug/tracing` 을 통한 가상 파일 인터페이스 접근 |
| **트레이서 활용** — `function`, `function_graph` 필터링 및 trace 로그 분석 |

#### Day60 — OpenCV 영상처리 기초
| 핵심 주제 |
|-----------|
| **영상처리 시스템 구조** — 카메라 렌즈 입력 -> 센서 -> 영상처리 ISP -> 처리 영상 데이터 출력 |
| **컬러 모델** — RGB(빛의 삼원색) 및 HSV(색상 Hue, 채도 Saturation, 명도 Value) 색 공간 분석 |

#### Day61 — 영상 픽셀 제어 & 이진화
| 핵심 주제 |
|-----------|
| **픽셀 엑세스** — OpenCV `Mat` 클래스 행렬 데이터를 활용한 픽셀값 변환 |
| **이진화(Threshold)** — 특정 임계값을 기준으로 0과 255 값으로 단순화하는 기법 |
| **룩업테이블(LUT)** — 입력 화소값을 출력 화소값으로 고속 매핑하는 배열 활용 |

#### Day62 — 기하학적 투영 변환
| 핵심 주제 |
|-----------|
| **투영 변환** — 어핀 변환과의 차이, 4점 매칭을 이용한 `getPerspectiveTransform` 과 `warpPerspective` |

---

## 🛠️ 개발 환경

| 항목 | 내용 |
|------|------|
| OS | Ubuntu 22.04 (WSL2), Raspberry Pi OS Lite (64-bit) |
| 컴파일러 | GCC/G++, arm-none-eabi-gcc, aarch64-linux-gnu-gcc (크로스 컴파일러) |
| 빌드 도구 | Make, BitBake (Yocto Project Kirkstone) |
| 라이브러리 | OpenCV 4.x |
| 대상 하드웨어 | Raspberry Pi 4B, STM32 Nucleo401RE |

---

## 🔗 연관 브랜치

| 브랜치 | 내용 |
|--------|------|
| [main](../../tree/main) | 전체 허브 |
| [stage/linux](../../tree/stage/linux) | Linux OS 구조, Bash 스크립팅, systemd (Week 6~7) |
| [stage/linux-sys](../../tree/stage/linux-sys) | GCC/GDB, CMake, 프로세스/스레드, epoll (Week 8~11) |
| [stage/embedded](../../tree/stage/embedded) | ARM 임베디드, MCU(STM32) 베어메탈/HAL 펌웨어 (Week 5~6) |

---

*지속적으로 업데이트됩니다. 🚀*
