# 📚 C Language Study

> C언어 학습 기록 저장소입니다.  
> 강의 노트, 코드베이스, Q&A를 체계적으로 정리합니다.

---

## 🗂️ 저장소 구조

```
VEDA/
├── workspace/          # 강의 실습 C 소스코드
│   ├── Week1/
│   └── Week2/
│       ├── Day6/
│       ├── Day7/
│       ├── Day8/           # 구조체 실습 (Point, Line)
│       └── CPPSolution/
│           └── Day8CppApp/ # C++ 기초 입출력 실습
├── GroupStudy/             # 그룹 스터디 (알고리즘 및 심화 주제)
│   ├── bubble_sort.cpp
│   ├── selection_sort.cpp
│   ├── Insertion_Sort.cpp
│   └── practice_2751.c     # BOJ 2751: 버블/선택/삽입 정렬 비교
├── MD/                     # 강의 노트 (Obsidian Markdown)
│   ├── VEDA Study.md       # 전체 학습 목차
│   ├── Week1/
│   │   ├── Day 1/  → Day 1.md, CodeBase.md, Intro(OT).md, QnA.md
│   │   ├── Day 2/  → Day 2.md, CodeBase.md, QnA.md
│   │   ├── Day 3/  → Day 3.md, CodeBase.md, QnA.md
│   │   ├── Day 4/  → Day 4.md, CodeBase.md, QnA.md
│   │   └── Day 5/  → Day 5.md, CodeBase.md, QnA.md
│   └── Week2/
│       ├── Day 6/  → Day 6.md, CodeBase.md, QnA.md
│       ├── Day 7/  → Day 7.md, CodeBase.md, QnA.md
│       └── Day 8/  → Day 8.md, CodeBase.md, QnA.md
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

---

## 🔑 핵심 학습 목표

- ✅ C언어 문법 기초 및 입출력
- ✅ 함수 설계 및 다차원 배열 활용
- ✅ **포인터 및 메모리 구조 이해** (변수, 배열, 함수 포인터 등)
- ✅ **동적 메모리 관리** 및 효율적인 자원 사용
- ✅ **알고리즘 구현**을 통한 로직 훈련 (정렬 등)
- ✅ **구조체(struct)** 기초 실습 (Point, Line 타입 정의)
- 🔲 구조체 심화 및 파일 입출력
- 🔲 C-ASM(어셈블리) 연동

---

## 🛠️ 개발 환경

| 항목 | 내용 |
|------|------|
| 언어 | C (C99/C11), C++ |
| IDE | Visual Studio, VS Code |
| 컴파일러 | MSVC (cl.exe), GCC / G++ |
| OS | Windows |

---

## 👤 Author

- **분야**: C언어 시스템 프로그래밍 / 알고리즘
- **목표**: 하드웨어 제어부터 메모리 최적화까지 가능한 시스템 전문가

---

*학습 중인 내용으로, 지속적으로 업데이트됩니다. 🚀*
