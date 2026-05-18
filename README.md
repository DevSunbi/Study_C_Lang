# 🐧 stage/linux-sys — Linux 시스템 프로그래밍 학습 노트

> VEDA 교육과정 中 **GCC/GDB 빌드 환경, CMake, Docker, Linux 저수준 시스템 프로그래밍, 프로세스 제어**를 다루는 브랜치입니다.

---

## 📁 브랜치 구조

```
stage/linux-sys/
├── MD/
│   ├── Week8/
│   │   ├── Day34/   ← GCC 컴파일 파이프라인, GDB 디버거
│   │   ├── Day36/   ← CMake 빌드 시스템, Docker, Git
│   │   └── Day37/   ← Linux 커널/시스템 콜, My Shell 구현, 파일시스템
│   └── Week9/
│       └── Day38/   ← 저수준 파일 I/O, 디렉토리 제어, 프로세스
└── README.md
```

---

## 📚 학습 내용

### 🔧 Week 8 — GCC 빌드 시스템 & 시스템 프로그래밍

#### Day34 — GCC & GDB
| 핵심 주제 |
|-----------|
| **GCC 컴파일 파이프라인** — 전처리(cpp0) → 컴파일(cc1) → 어셈블(as) → 링킹(collect2) |
| **ELF 포맷** — 목적 파일/실행 파일 구조, readelf, 심볼 테이블 |
| **GCC 주요 옵션** — -E/-S/-c/-g, 최적화 레벨 O0~O3, volatile |
| **정적 라이브러리** (.a) — ar archiver, 컴파일 시 링크 |
| **공유 라이브러리** (.so) — 실행 시 동적 링크, ldd |
| **동적 라이브러리** — dlopen/dlsym/dlclose, 플러그인 구현 |
| **GDB 디버거** — break/watch/step/next/backtrace/continue |
| **Core 파일 분석** — ulimit, gdb로 SIGSEGV/SIGABRT 원인 추적 |
| **proc 파일시스템** — 커널 파라미터, core_pattern |

#### Day36 — CMake & Docker & Git
| 핵심 주제 |
|-----------|
| **CMake** — Out-of-Source 빌드, CMakeLists.txt 기본 구조 |
| **모던 CMake** — 타깃 기반 접근, target_include_directories, PRIVATE/PUBLIC/INTERFACE |
| **외부 라이브러리** — find_package, CTest + GoogleTest 단위 테스트 |
| **Docker** — 컨테이너 vs VM, 이미지/컨테이너 구조, Dockerfile |
| **Docker 아키텍처** — daemon/containerd/runc/shim 계층 |
| **Git** — DVCS 개념, 파일 저장 단계 (작업트리 → 스테이지 → 커밋) |

#### Day37 — Linux 커널 & Shell 구현 & 파일시스템
| 핵심 주제 |
|-----------|
| **리눅스 커널 구조** — H/W 자원 관리, 시스템 콜 인터페이스 |
| **시스템 콜 vs 라이브러리 함수** — man 2 / man 3, errno 오류 처리 |
| **환경변수** — getenv/putenv, PATH, HOME |
| **시스템 정보** — uname/gethostname, time/gettimeofday, getrlimit/setrlimit |
| **My Shell 구현** — fork/exec/wait, 빌트인 명령, 리다이렉트, 파이프 |
| **파일시스템 구조** — 파일 종류, 파티션 구조 (부트/수퍼블록/inode/데이터) |
| **inode** — stat/lstat/fstat로 파일 정보 조회 |

---

### 🔩 Week 9 — 저수준 파일 I/O & 프로세스 제어

#### Day38 — 파일 I/O & 프로세스
| 핵심 주제 |
|-----------|
| **고수준 vs 저수준 I/O** — FILE\*/파일 디스크립터, 버퍼 유무 비교 |
| **저수준 파일 함수** — open/close/read/write/lseek, 오픈 플래그 |
| **파일 디스크립터** — 0(stdin)/1(stdout)/2(stderr) 예약, O_SYNC |
| **터미널 제어** — ioctl, termio 구조체, Canonical/Non-Canonical 모드 |
| **파일 중첩** — dup/dup2, 파이프·소켓 응용 |
| **디렉토리 제어** — opendir/readdir/mkdir/rmdir/chdir/getcwd |
| **프로세스 구조** — task_struct, context/image, 프로세스 상태 코드 |
| **프로세스 생성** — fork() 동작 원리, Copy-on-Write, 반환값 구분 |
| **좀비 프로세스** — wait/waitpid로 SIGCHLD 처리 |
| **프로세스 종료** — exit(), 입출력 버퍼 비우기, 파일 디스크립터 close |

---

## 🛠️ 개발 환경

| 항목 | 내용 |
|------|------|
| OS | Ubuntu 22.04 (WSL2) |
| 컴파일러 | GCC/G++ (gnu), arm-none-eabi-gcc |
| 빌드 도구 | CMake 3.22+, Make |
| 디버거 | GDB 12.1 |
| 컨테이너 | Docker |
| 플랫폼 | x86_64 Linux, STM32/RPi (크로스 빌드) |

---

## 🔗 연관 브랜치

| 브랜치 | 내용 |
|--------|------|
| [main](../../tree/main) | 전체 허브 |
| [stage/linux](../../tree/stage/linux) | Linux OS 구조, Bash 스크립팅, systemd (Week 6~7) |
| [stage/embedded](../../tree/stage/embedded) | ARM 임베디드, UART/SPI/I2C (Week 5~6) |

---

*지속적으로 업데이트됩니다. 🚀*
