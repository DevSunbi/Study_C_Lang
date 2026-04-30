# 📚 C Language Study

> C언어 학습 기록 저장소입니다.  
> 강의 노트, 코드베이스, Q&A를 체계적으로 정리합니다.

---

## 🗂️ 저장소 구조

```
VEDA/
├── workspace/          # 강의 실습 C/C++ 소스코드
│   ├── Week1/
│   ├── Week2/
│   │   ├── Day6/
│   │   ├── Day7/
│   │   ├── Day8/               # 구조체 실습 (Point, Line)
│   │   ├── CPPSolution/
│   │   │   └── Day8CppApp/     # C++ 기초 입출력 실습
│   │   ├── Day9CppApp/         # C++ 참조자(Reference) & swap 실습
│   │   │   └── ConsoleApplication2/
│   │   │       └── ConsoleApplication2.cpp
│   │   ├── Day10CppAppSolution/   # C++ 클래스 & 캡슐화 실습
│   │   └── Day10CppApp2Solution/  # C++ 상속 & 다형성 실습
│   ├── Week3/
│   │   ├── Day11CppAppSolution/   # C++ 상속, 다형성, 가상함수 실습
│   │   └── Day12CppAppSolution/   # C++ 복사 생성자, 정적 멤버 실습
│   ├── Week4/
│       ├── Day16/               # Qt CMake/QMake 빌드, Widget 기초 실습
│       ├── Day17/               # Qt CheckBox, ComboBox, Designer 활용 실습
│       ├── Day18/               # Qt Layout, Widgets, Container Class 실습
│       └── Day19/               # Qt Dialog, Signal/Slot, QMainWindow 실습
│   ├── Week5/                   # ARM 어셈블리(ASM) 실습
│   │   ├── basic_operators.s    # ARM 기초 연산 ASM
│   │   ├── func_call.s          # ARM 함수 호출 ASM
│   │   ├── is_multiple.s        # ARM 배수 판별 ASM
│   │   ├── advanced_is_multiple.s
│   │   ├── main.s               # ARM main 진입점 ASM
│   │   └── example.c / main.cpp # C/C++ 크로스 개발 예시
│   └── Week6/
│       ├── Day26/               # STM32 LED 프로젝트 (HAL, CMSIS 드라이버)
│       │   ├── STMLedProject/
│       │   └── STMLedProject_2/
│       └── Day27/               # Raspberry Pi GPIO 제어 (wiringPi, LED/버튼 실습)
│           └── led.cpp
├── GroupStudy/             # 그룹 스터디 (알고리즘 및 심화 주제)
│   ├── bubble_sort.cpp
│   ├── selection_sort.cpp
│   ├── Insertion_Sort.cpp
│   ├── practice_2751.c     # BOJ 2751: 버블/선택/삽입 정렬 비교
│   ├── binSearch.cpp        # 이진 탐색(Binary Search) 구현
│   ├── boj1920.c            # BOJ 1920: 이진 탐색으로 수 찾기
│   └── Search.md            # 탐색 알고리즘 정리 노트
├── MD/                     # 강의 노트 (Obsidian Markdown)
│   ├── VEDA Study.md       # 전체 학습 목차
│   ├── Week1/
│   │   ├── Day 1/  → Day 1.md, CodeBase.md, Intro(OT).md, QnA.md
│   │   ├── Day 2/  → Day 2.md, CodeBase.md, QnA.md
│   │   ├── Day 3/  → Day 3.md, CodeBase.md, QnA.md
│   │   ├── Day 4/  → Day 4.md, CodeBase.md, QnA.md
│   │   └── Day 5/  → Day 5.md, CodeBase.md, QnA.md
│   ├── Week2/
│   │   ├── Day 6/  → Day 6.md, CodeBase.md, QnA.md
│   │   ├── Day 7/  → Day 7.md, CodeBase.md, QnA.md
│   │   ├── Day 8/  → Day 8.md, CodeBase.md, QnA.md
│   │   ├── Day 9/  → Day 9.md, CodeBase.md, QnA.md
│   │   └── Day 10/ → Day 10.md, CodeBase.md, QnA.md
│   ├── Week3/
│   │   ├── Day 11/ → Day 11.md, CodeBase.md, QnA.md
│   │   ├── Day 12/ → Day 12.md, CodeBase.md, QnA.md
│   │   ├── Day 13/ → Day 13.md, CodeBase.md
│   │   └── Day 14/ → Day 14.md, CodeBase.md
│   ├── Week4/
│   │   ├── Day 16/ → Day 16.md, CodeBase.md
│   │   ├── Day 17/ → Day 17.md, CodeBase.md
│   │   ├── Day 18/ → Day 18.md
│   │   ├── Day 19/ → Day 19.md  (Signal/Slot, Dialog)
│   │   └── Day 20/ → Day 20.md  (QMainWindow, Model/View, QPainter)
│   ├── Week5/
│   │   ├── Day 21/ → Day 21.md  (Thread Programming, Mutex, DeadLock)
│   │   ├── Day 22/ → Day 22.md
│   │   ├── Day 24/ → Day 24.md  (임베디드 기초, MCU, ARM, RISC/CISC)
│   │   └── Day 25/ → Day 25.md  (크로스 개발환경, g++ options, ASM, Memory Map)
│   ├── Protocol/               # 통신 프로토콜 정리 (UART, SPI, I2C, MCU, SoC, IMU 등)
│   └── Week6/
│       ├── Day26/ → Day26.md  (Protocol 비교, UART/SPI/I2C, STM32 Register/Memory Map)
│       ├── Day27/ → Day27.md  (PullUp/PullDown, Raspberry Pi, 인터럽트 이론 & EXTI)
│       ├── Day28/ → Day28.md  (OS 구조, Kernel, 리눅스 배포판, 터미널/셸 기초)
│       └── Day29/ → Day29.md  (리눅스 명령어, 파일시스템, SoftLink/HardLink, 사용자/권한)
├── .gitignore              # 바이너리 및 로그 제외 설정
└── README.md
```

---

## 📅 학습 및 활동 내용

### 🛡️ Group Study: 알고리즘
- **정렬 알고리즘 구현 (C++)**
  - `Bubble Sort` (버블 정렬): 구현 및 테스트 완료.
  - `Selection Sort` (선택 정렬): 무한 루프 버그 수정 및 구현 완료.
  - `Insertion Sort` (삽입 정렬): 구현 및 테스트 완료.
- **BOJ 2751 풀이 (`practice_2751.c`)**
  - 버블/선택/삽입 정렬 3가지 방법으로 구현 비교 (C언어)
  - 시간복잡도 O(n²) — TLE 확인 및 알고리즘 한계 분석
- **기타**
  - C++ 환경에서의 빌드 및 실행 테스트 (`g++` 사용)

### ✅ 강의 커리큘럼
| 주차 | 일차 | 주제 | 핵심 내용 |
|-----|------|------|-----------|
| **Week 1** | Day 1~5 | 기초 및 포인터 | 기초 문법, 함수, 배열, **포인터**(핵심), 아스키코드 |
| **Week 2** | Day 6~7 | 심화 및 메모리 | 문자열 함수, 변수 영역(static 등), **이중 포인터**, **동적 할당**(malloc/free) |
| **Week 2** | Day 8 | 구조체 & C++ 입출력 | `typedef struct` 정의, **Point / Line** 구조체 실습, C++ `cin/cout` 기초 |
| **Week 2** | Day 9 | C++ 심화 & OOP 입문 | **레퍼런스(Reference)**, 동적할당(`new/delete`), 연산자 오버로딩, **예외처리**(try/catch/throw), **프로그래밍 패러다임**(절차적 → OOP) |
| **Week 2** | Day 10 | 객체지향 프로그래밍 | **클래스(class)** 설계, **캡슐화**(접근지정자/getter/setter), **추상화**, **상속**(Is-a/Has-a), **다형성**, UML 다이어그램, `this` 포인터 |
| **Week 3** | Day 11 | 상속과 다형성(C++) | **상속**(단일/다중), **다형성**, 오버라이딩, **가상 함수(`virtual`)**, 정적/동적 바인딩, 클래스 치환 |
| **Week 3** | Day 12 | 복사 생성자와 정적 멤버 | **복사 생성자(Copy Constructor)**, 얕은 복사/깊은 복사, **정적 멤버(`static`)**, 동적 할당 클래스 관리 |
| **Week 3** | Day 13 | 템플릿 & 표준 라이브러리 | **함수/클래스 템플릿**, 템플릿 특수화, `string` 표준 라이브러리, 파일 시스템, 난수(`mt19937`) |
| **Week 3** | Day 14 | STL 컨테이너 & 알고리즘 | **Vector**, **List**, **Deque**, **Set**, **Map**, 반복자(iterator), 컨테이너 어댑터(Stack/Queue), STL 알고리즘 |
| **Week 4** | Day 16 | Qt 입문 & 기초 | **Qt 아키텍처**(MVC), CMake/QMake 빌드, **QMainWindow**, 이벤트 처리, Signal/Slot |
| **Week 4** | Day 17 | Qt 위젯 & 디자이너 | **QCheckBox**, **QComboBox**, Qt Designer 활용, connect 함수, resources 에셋 처리 |
| **Week 4** | Day 18 | Qt 레이아웃 & 데이터 타입 | **Layout**(QHBox/QVBox/QGrid/QForm), **QString/QChar**, QVariant, QMap/QHash, QSet |
| **Week 4** | Day 19 | Qt Signal/Slot 심화 & Dialog | **Signal/Slot** 심화, emit, **QDialog**(QInputDialog/QFileDialog/QMessageBox), Modal/Modeless |
| **Week 4** | Day 20 | QMainWindow & Model/View & QPainter | **QMainWindow** 구조, Stream(Text/Data), **Model-View** 아키텍처, **QPainter** 2D 그래픽스 |
| **Week 5** | Day 21 | Thread Programming | **멀티스레드** 개념, Thread Pool/Ready Pool, Race Condition, **Mutex**, **DeadLock** |
| **Week 5** | Day 22 | Qt 계좌 관리 프로그램 | Qt 기반 계좌 관리 시스템 실습 |
| **Week 5** | Day 24 | 임베디드 기초 & MCU HW | **임베디드 시스템** 개요, NTCR, MCU 구조, DMA/Timer/RTC/GPIO, **Register**, **인터럽트** |
| **Week 5** | Day 25 | 크로스 개발환경 & ARM ASM | **크로스 컴파일**, g++ options, **ARM(RISC) vs CISC**, **Cortex-M4**, **Branch 명령어**, Memory Map |
| **Week 6** | Day 26 | 통신 프로토콜 & STM32 기초 | **UART/SPI/I2C** 비교, VCC/GND/PullUp/PullDown, Rising/Falling Edge, STM32 Cortex-M4 Register & Memory Map, Nucleo401RE Pin Map |
| **Week 6** | Day 27 | Raspberry Pi GPIO & 인터럽트 | PullUp/PullDown 회로, RPi4B pinout, **인터럽트** 동작원리, ISR, NVIC, **EXTI** 설정, wiringPi LED/Button 실습 |
| **Week 6** | Day 28 | OS 구조 & 리눅스 기초 | **운영체제** 구조, Kernel/Device Driver/File System/Network System, 멀티태스킹, **리눅스 배포판**, 터미널/셸(Bash) |
| **Week 6** | Day 29 | 리눅스 파일시스템 & 권한 관리 | ls/cd/nano/cp 명령어, 파일 종류, 루트 디렉터리, **SoftLink/HardLink**(inode/dentry), 사용자 계정(root/sudo), 파일 소유권/권한(chown) |

---

## 🔑 핵심 학습 목표

- ✅ C언어 문법 기초 및 입출력
- ✅ 함수 설계 및 다차원 배열 활용
- ✅ **포인터 및 메모리 구조 이해** (변수, 배열, 함수 포인터 등)
- ✅ **동적 메모리 관리** 및 효율적인 자원 사용
- ✅ **알고리즘 구현**을 통한 로직 훈련 (정렬 등)
- ✅ **구조체(struct) 기초** — `typedef struct`, Point / Line 타입 정의
- ✅ **구조체 심화** — 패딩/바이트 정렬, `#pragma pack`, 구조체 포인터(`->`), 자기참조 구조체, 공용체(`union`), 열거형(`enum`)
- ✅ **파일 입출력** — `fopen/fclose`, `fgetc/fputc`, `fread/fwrite`, `fscanf/fprintf`, 개방 모드, `fseek/rewind/feof`
- ✅ **전처리 지시자** — `#define` 매크로 함수, 조건부 컴파일(`#ifdef`), 분할 컴파일, `extern/static`
- ✅ **C++ 입문** — namespace, `cin/cout`, `wchar_t`
- ✅ **C++ 심화** — 레퍼런스(`&`), 동적할당(`new/delete`), 연산자 오버로딩, L-value/R-value, `static_cast` 등 형 변환
- ✅ **예외 처리** — `try/catch/throw`, 스택 풀기, `noexcept`, `set_terminate`
- ✅ **프로그래밍 패러다임** — 비구조적/절차적/객체지향 프로그래밍 개념 및 OOP 필요성
- ✅ **OOP 클래스 설계** — 클래스/인스턴스/객체 구분, 멤버 변수·함수, 생성자/소멸자, `this` 포인터
- ✅ **캡슐화(Encapsulation)** — 접근 지정자(`public/private/protected`), getter/setter, 정보 은닉
- ✅ **추상화(Abstraction)** — 공통 특성 추출, 불필요 요소 제거, 물리적·행위적 특성 분류
- ✅ **상속(Inheritance)** — Is-a / Has-a 관계, 부모(Base)/자식(Derived) 클래스, 업캐스팅/다운캐스팅
- ✅ **다형성(Polymorphism)** — 자식 객체가 부모 대체 가능, `virtual` 함수
- ✅ **복사 생성자(Copy Constructor)** — 얕은 복사(Shallow) vs 깊은 복사(Deep)
- ✅ **정적 멤버(Static)** — 클래스 전역 공유 변수 및 메서드
- ✅ **UML** — 클래스/객체/시퀀스/상태 다이어그램
- ✅ **템플릿(Template)** — 함수/클래스 템플릿, 특수화, 인스턴스화, 중첩 클래스 템플릿
- ✅ **표준 라이브러리(STL)** — `string`, `wstring`, 파일 시스템(`ifstream`), 난수(`mt19937`), 수학 함수(`cmath`)
- ✅ **STL 컨테이너** — `vector`, `list`, `deque`, `array`, `set`, `map`, `multimap`, `stack`, `queue`
- ✅ **반복자(Iterator)** — `begin/end`, `const_iterator`, `reverse_iterator`, 범위형 for
- ✅ **Qt 프레임워크** — MVC 아키텍처, CMake/QMake 빌드, QMainWindow, Signal/Slot
- ✅ **Qt 위젯** — QLabel, QPushButton, QCheckBox, QComboBox, QGroupBox, QLCDNumber, QTabWidget
- ✅ **Qt 데이터 타입** — QString, QChar, QLatin1String, QVariant, QByteArray
- ✅ **Qt 컨테이너** — QMap, QHash, QPair, QList, QSet
- ✅ **Qt Signal/Slot 심화** — emit, Old/New Style connect, 시그널 전파
- ✅ **Qt Dialog** — QInputDialog, QFileDialog, QMessageBox, Modal/Modeless
- ✅ **Qt Model/View 아키텍처** — QAbstractItemModel, QStringListModel, QListView, Delegate
- ✅ **Qt Stream & File I/O** — QTextStream, QDataStream, QFileDialog
- ✅ **QPainter 2D 그래픽스** — paintEvent, QPainter begin/end, setPen, drawLine
- ✅ **멀티스레드(Thread)** — Thread Pool, Race Condition, Mutex(lock/unlock), DeadLock 4조건
- ✅ **임베디드 시스템 기초** — NTCR(Nature/Time/Constraint/Reliability), MCU 구조, firmware
- ✅ **임베디드 HW** — DMA Controller, Timer, RTC, GPIO, Register(PC/LR/SP), 인터럽트 벡터
- ✅ **크로스 개발환경** — PC(CISC) vs Embedded(ARM RISC), 크로스 컴파일 5단계(pre-process→hex)
- ✅ **g++ 컴파일 옵션** — `-o`, `-c`, `-S`, `-std`, `-Werror/-Wall`, `-l <lib>`
- ✅ **ARM 어셈블리(ASM)** — `.arm/.text/.global`, MOV/ADD/CMP/BEQ/BL/BX, Cortex-M4, Branch
- ✅ **ARM 메모리 맵** — Code(ROM)/Data(RAM) 영역, Stack, 파이프라이닝(F-D-E-W)
- ✅ **이진 탐색(Binary Search)** — 구현 및 BOJ 1920 적용 (GroupStudy)
- ✅ **통신 프로토콜** — UART(비동기/Start-Stop bit), SPI(SCLK/MOSI/MISO/SS), I2C(마스터/슬레이브/주소 기반), 프로토콜 비교표
- ✅ **STM32 임베디드** — Cortex-M4 Register, STM32 Memory Map, Nucleo401RE Pin Map, HAL/CMSIS 드라이버 기반 LED 프로젝트
- ✅ **인터럽트 심화** — 인터럽트 소스/컨트롤러(NVIC), ISR, 인터럽트 우선순위, Tail-Chaining, EXTI(External Interrupt), Masking/NMI
- ✅ **Raspberry Pi GPIO** — wiringPi 라이브러리, PullUp/PullDown 회로, RPi4B pinout, LED/버튼 제어 실습
- ✅ **운영체제(OS) 구조** — Kernel, Device Driver, File System, Network Stack, 프로세스/멀티태스킹, GUI/CLI
- ✅ **리눅스 기초** — 배포판(Ubuntu/CentOS/RedHat), 터미널, Bash 셸, 기본 명령어(ls/cd/nano/cp)
- ✅ **리눅스 파일시스템** — 파일 종류(일반/디렉/심링크/블록/문자/파이프/소켓), 루트 디렉터리 구조, Network FS, Pseudo FS
- ✅ **SoftLink & HardLink** — inode, dentry, 데이터 블록, 소프트링크(심볼릭) vs 하드링크 비교
- ✅ **리눅스 사용자/권한 관리** — root/시스템/일반 사용자, /etc/passwd, /etc/group, sudo/su/runuser, chown, 파일 권한(rwx/stickyBit)
- 🔲 순수 가상함수 & 추상 클래스
- 🔲 RTOS / 임베디드 실전 프로젝트

---

## 🛠️ 개발 환경

| 항목 | 내용 |
|------|------|
| 언어 | C (C99/C11), C++ |
| IDE | Visual Studio, VS Code, Qt Creator |
| 컴파일러 | MSVC (cl.exe), GCC / G++, Qt (MSVC/MinGW) |
| OS | Windows |

---

## 👤 Author

- **분야**: C언어 시스템 프로그래밍 / 알고리즘
- **목표**: 하드웨어 제어부터 메모리 최적화까지 가능한 시스템 전문가

---

*학습 중인 내용으로, 지속적으로 업데이트됩니다. 🚀*
