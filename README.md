# 📚 C Language Study

> C언어 학습 기록 저장소입니다.  
> 강의 노트, 코드베이스, Q&A를 체계적으로 정리합니다.

---

## 🗂️ 저장소 구조

```
WS/
├── workspace/          # 실습 C 소스코드
│   ├── Week1/
│   │   ├── Day1/       # main.c, Day1.slnx, Day1.vcxproj
│   │   ├── Day2/       # day2.c, Day2.slnx, Day2.vcxproj
│   │   ├── Day3/
│   │   ├── Day4/
│   │   └── Day5/
│   └── Week2/
│       ├── Day6/       # main.c, Day6.slnx, Day6.vcxproj
│       └── Day7/       # main.c, Day7.slnx, Day7.vcxproj
├── MD/                 # 강의 노트 (Obsidian Markdown)
│   ├── VEDA Study.md   # 전체 학습 목차
│   ├── Week1/
│   │   ├── Day 1/      # 프로그램 만들기 / C언어 소개
│   │   ├── Day 2/      # 상수와 데이터 출력, 변수
│   │   ├── Day 3/      # 데이터 입력, 함수
│   │   ├── Day 4/      # 함수, 배열
<<<<<<< Updated upstream
│   │   └── Day 5/      # (포인터, 배열과 포인터)
=======
│   │   └── Day 5/      # 포인터, 배열과 포인터, 아스키코드
>>>>>>> Stashed changes
│   └── Week2/
│       ├── Day 6/      # 문자열, 변수의 영역, 다차원 배열과 포인터
│       └── Day 7/      # 포인터 배열, 이중 포인터, 동적 할당
└── README.md
```

> 각 Day 폴더 구성:
> - `Day N.md` — 강의 핵심 노트
> - `CodeBase.md` — 예제 코드 정리
> - `QnA.md` — 질문 & 답변

---

## 📅 주차별 학습 내용

### ✅ Week 1

| Day | 주제 | 핵심 내용 |
|-----|------|-----------|
| Day 1 | 프로그램 만들기 | 프로그램과 C언어, 프로그래밍 언어, 컴파일러 |
| Day 2 | 상수와 데이터 출력 | C프로그램 구조, 데이터 출력, 변수 |
| Day 3 | 데이터 입력 / 함수 | scanf, 함수 기초 |
| Day 4 | 함수 / 배열 | 함수 심화, 1차원/다차원 배열 |
<<<<<<< Updated upstream
| Day 5 | 심화 학습 | 포인터, 배열과 포인터, 아스키 코드 및 문자 입출력 |
=======
| Day 5 | 포인터 / 배열과 포인터 | 포인터 변수, const 포인터, call by pointer, 배열-포인터 관계, 아스키코드 |
>>>>>>> Stashed changes

### ✅ Week 2

| Day | 주제 | 핵심 내용 |
|-----|------|-----------|
| Day 6 | 문자열 / 변수 영역 / 다차원 배열 | getchar/putchar, 문자열 함수(gets/fgets/strcpy/strcat/strlen/strcmp), 지역·전역·정적 변수, 2차원 배열 |
| Day 7 | 포인터 배열 / 동적 할당 | 포인터 배열, 이중 포인터, 배열 포인터, 함수 포인터, void 포인터, malloc/free/calloc/realloc |

---

## 🔑 핵심 학습 목표

- ✅ C언어 문법 기초 (변수, 상수, 연산자)
- ✅ 입출력 함수 (`printf`, `scanf`, `getchar`, `putchar`)
- ✅ 함수 설계 및 활용
- ✅ 배열 및 메모리 개념
- ✅ **포인터** (변수, const, call by pointer, 배열-포인터)
- ✅ 문자열 처리 (`strcpy`, `strcat`, `strlen`, `strcmp`)
- ✅ 변수의 영역 (지역·전역·정적·레지스터)
- ✅ 포인터 배열 / 이중 포인터 / 배열 포인터 / 함수 포인터
- ✅ **동적 메모리 할당** (`malloc`, `free`, `calloc`, `realloc`)
- 🔲 **구조체** 및 파일 입출력
- 🔲 C-ASM 연동

---

## 🛠️ 개발 환경

| 항목 | 내용 |
|------|------|
| 언어 | C (C99/C11) |
| IDE | Visual Studio |
| 컴파일러 | MSVC (cl.exe) |
| 노트 도구 | Obsidian |

---

## 📝 노트 작성 규칙

- `Day N.md` : 해당 날 배운 내용 요약 정리
- `CodeBase.md` : 실습 및 예제 코드 모음
- `QnA.md` : 수업 중 나온 질문과 답변

---

## 👤 Author

- **분야**: C언어 시스템 프로그래밍
- **목표**: 포인터, 구조체, 메모리 함수 → C-ASM 수준까지

---

*학습 중인 내용으로, 지속적으로 업데이트됩니다. 🚀*
