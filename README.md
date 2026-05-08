# 🟢 stage/linux — Linux & Bash 시스템 프로그래밍 학습 노트

> VEDA 교육과정 中 **Linux 운영체제 구조, Bash 스크립팅, 프로세스 관리, systemd**를 다루는 브랜치입니다.

---

## 🗂️ 브랜치 구조

```
stage/linux/
└── MD/
    ├── Week6/
    │   ├── Day28/  # OS 구조, Kernel, 리눅스 배포판, 터미널/셸 기초
    │   └── Day29/  # 리눅스 명령어, 파일시스템, SoftLink/HardLink, 사용자/권한
    └── Week7/
        ├── Day30/  # 프로세스 관리, IPC, 시그널, Bash 조건문/반복문/함수/배열
        ├── Day31/  # Bash 확장, 리디렉션, 파이프라인, 필수 CLI 툴
        └── Day32/  # 패키지 관리, awk, systemd/systemctl, bashrc, alias
```

> **Note:** 실습 코드는 각 MD 파일 내의 코드 블록(Bash 스크립트)으로 포함되어 있습니다.

---

## 📅 학습 커리큘럼

| 주차 | 일차 | 주제 | 핵심 내용 |
|------|------|------|-----------|
| **Week 6** | Day 28 | OS 구조 & 리눅스 기초 | **운영체제** 구조, Kernel/Device Driver/File System/Network Stack, 멀티태스킹, **리눅스 배포판**, 터미널/셸(Bash) |
| **Week 6** | Day 29 | 리눅스 파일시스템 & 권한 관리 | ls/cd/nano/cp 명령어, 파일 종류, 루트 디렉터리, **SoftLink/HardLink**(inode/dentry), 사용자 계정(root/sudo), 파일 권한(rwx/stickyBit) |
| **Week 7** | Day 30 | 프로세스 관리 & Bash 기초 | **프로세스**(init/좀비/고아), **IPC**(파이프/메시지큐/소켓/공유메모리/세마포어), 시그널, Bash 변수/조건문/반복문/함수/배열 |
| **Week 7** | Day 31 | Bash 심화 & 리디렉션 | Bash **확장**(중괄호/틸데/명령어치환/산술/패턴치환/대소문자), **리디렉션**(`>`/`>>`/`<`), here documents, **파이프라인**, 필수 CLI 툴(grep/find/stat/wc/tar/tr) |
| **Week 7** | Day 32 | 시스템 관리 & bashrc | **패키지 관리**(apt/awk), **systemd** 유닛파일/서비스 타입, **systemctl**(start/stop/status), **bashrc** 초기화 스크립트, alias 설정 |

---

## 🔑 핵심 학습 목표

- ✅ **운영체제(OS) 구조** — Kernel, Device Driver, File System, Network Stack, GUI/CLI
- ✅ **리눅스 기초** — 배포판(Ubuntu/CentOS/RedHat), 터미널, Bash 셸, 기본 명령어
- ✅ **리눅스 파일시스템** — 파일 종류, 루트 디렉터리 구조, Network FS, Pseudo FS
- ✅ **SoftLink & HardLink** — inode, dentry, 데이터 블록, 심볼릭 vs 하드링크
- ✅ **리눅스 사용자/권한 관리** — /etc/passwd, /etc/group, sudo/su, chown, rwx/stickyBit
- ✅ **프로세스 관리** — 생애주기, PCB, 컨텍스트 스위칭, 멀티태스킹, 좀비/고아 프로세스
- ✅ **IPC(프로세스 간 통신)** — 파이프, 메시지 큐, 소켓, 공유 메모리, 세마포어
- ✅ **시그널** — 시그널 개념/이름/번호, SIGCHLD/SIGSTOP/SIGTERM/SIGKILL
- ✅ **Bash 스크립트** — 변수/할당/쿼팅, 산술연산(let/expr), 조건문/반복문/함수/배열
- ✅ **Bash 확장** — 중괄호/틸데/명령어치환/산술/패턴치환, 변수 값 조건 확장, 간접 확장
- ✅ **리디렉션 & 파이프라인** — 출력/입력 리디렉션, here documents/strings, 파이프(`|`/`|&`)
- ✅ **필수 CLI 툴** — grep, find, stat, wc, df, tar, read, tr, tail, head
- ✅ **패키지 관리** — apt(install/remove/autoremove), awk(레코드 선택/패턴 매칭)
- ✅ **systemd & systemctl** — 데몬 프로세스, 유닛파일(Unit/Service/Install), ExecStart/Restart
- ✅ **bashrc & 셸 설정** — bashrc 초기화, source 명령어, 환경변수/alias, 셸 옵션(set/shopt)

---

## 🔗 관련 브랜치

| 브랜치 | 내용 |
|--------|------|
| [`main`](../../tree/main) | 전체 프로젝트 소개 |
| [`stage/c-cpp`](../../tree/stage/c-cpp) | C / C++ 기초~OOP (Week1~3) |
| [`stage/qt`](../../tree/stage/qt) | Qt 프레임워크 (Week4) |
| [`stage/embedded`](../../tree/stage/embedded) | 임베디드 시스템 (Week5~6) |
| [`group-study`](../../tree/group-study) | 알고리즘 스터디 |
